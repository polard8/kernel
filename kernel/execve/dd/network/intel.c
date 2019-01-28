/*
 * File: intel.c   
 *
 * Descrição:
 *     Network interface controller
 *     Network card driver.
 *     Algum gerenciamento de adaptador de network.
 *     Esse é o header do driver da placa de rede.
 *
 * 8086/100e network controller encontrado na oracle virtual box.
 * 
 * History:
 *     2016 - Created by Fred Nora.
 *     2018 - Credits: Ítalo Lima Marconato Matias, Chicago OS.
 */

 /*
   wikipedia - NIC
   A network interface controller 
   (NIC, also known as a network interface card, network adapter, 
   LAN adapter or physical network interface,[1] and by similar terms) 
   is a computer hardware component that connects a computer to a computer network.[2]
  
Connects to Motherboard via one of:
    Integrated, PCI Connector, ISA Connector, PCI-E, FireWire, USB, Thunderbolt.

Network via one of:
    Ethernet, Wi-Fi, Fibre Channel, ATM, FDDI, Token ring.

Speeds:
    10 Mbit/s, 100 Mbit/s, 1 Gbit/s, 10 Gbit/s, up to 160 Gbit/s.

Common manufacturers:
    Intel, Realtek, Broadcom, Marvell Technology Group, QLogic, Mellanox.
 
techniques:
    Polling, Interrupt-driven I/O, Programmed input/output, Direct memory access.
 
 */
 
 
#include <kernel.h>


//irq
void 
PCIRegisterIRQHandler ( uint16_t bus, 
						uint8_t slot, 
						uint8_t func, 
						unsigned long handler,
						void *priv ) 
{
	
	//#debug 
	printf("intel-PCIRegisterIRQHandler:");
	refresh_screen();
	while(1){}	
};



/*
 *****************************************************
 * e1000_init_nic:
 *     Inicializando o controlador NIC da Intel.
 */

int e1000_init_nic ( unsigned char bus, unsigned char dev, unsigned char fun, struct pci_device_d *pci_device ){
	
	//pci info.    
	uint32_t data;
	
	unsigned long phy_address;
	
 
    //#debug
	//printf("\n");
	//printf("e1000_init_nic: Probing PCI..\n");
	printf("e1000_init_nic:\n");	
	debug_print("e1000_init_nic:\n");
	
	// #pci	
	// # get info
	// Pegaremos mais informações e colocaremos na estrutura de 
	// dispositivo pci.

	//#importante
	//devemos falhar antes de alocarmos memória para a estrutura.
	
	// 8086:100e
	// 82540EM Gigabit Ethernet Controller
	
	data = (uint32_t) diskReadPCIConfigAddr ( bus, dev, fun, 0 );
	
	unsigned short Vendor = (unsigned short) (data & 0xffff);
	unsigned short Device = (unsigned short) (data >> 16 & 0xffff);	
	
    if ( Vendor != 0x8086 || Device != 0x100E )	
	{
	    return -1;
	}
		
	//#debug
	printf("Vendor=%x \n", (data       & 0xffff) );
	printf("Device=%x \n", (data >> 16 & 0xffff) );

	
	//pci device struct
	//passado via argumento. 
	
	if ( (void *) pci_device ==  NULL )
    {
		
		printf("init_nic: #debug pci_device struct\n");
		die ();
		//return (int) -1;
	
	}else{
		
		pci_device->deviceUsed = 1;
		pci_device->deviceMagic = 1234;
		
		pci_device->bus = (unsigned char) bus;
		pci_device->dev = (unsigned char) dev;
		pci_device->func = (unsigned char) fun;
		
		pci_device->Vendor = (unsigned short) (data & 0xffff);
		pci_device->Device = (unsigned short) (data >> 16 & 0xffff);
		
		
		// #IMPORTANTE
		// #bugbug:
		// Esse driver é para placa Intel, vamos cancelar a inicialização 
		// do driver se a placa não for Intel.
		
	    // 8086:100e
	    // 82540EM Gigabit Ethernet Controller		
		
		if ( pci_device->Vendor != 0x8086 || pci_device->Device != 0x100E )
		{
		    
			printf("#debug breakpoint\n");
			printf("e1000_init_nic: 82540EM not found!\n");
		    refresh_screen();
			while(1){}
			
			return -1;
		}
		
		pci_device->BAR0 = (unsigned long) diskReadPCIConfigAddr ( bus, dev, fun, 0x10 );
		pci_device->BAR1 = (unsigned long) diskReadPCIConfigAddr ( bus, dev, fun, 0x14 ); 
		pci_device->BAR2 = (unsigned long) diskReadPCIConfigAddr ( bus, dev, fun, 0x18 );
		pci_device->BAR3 = (unsigned long) diskReadPCIConfigAddr ( bus, dev, fun, 0x1C );
		pci_device->BAR4 = (unsigned long) diskReadPCIConfigAddr ( bus, dev, fun, 0x20 );
		pci_device->BAR5 = (unsigned long) diskReadPCIConfigAddr ( bus, dev, fun, 0x24 );
		
		
	    // ## IRQ ##
	    pci_device->irq_line = (uint8_t) pciConfigReadByte( bus, dev, fun, 0x3C );   //irq
	    pci_device->irq_pin = (uint8_t) pciConfigReadByte( bus, dev, fun, 0x3D );    //letras	
		
		
        // ##importante:
	    // Grab the Base I/O Address of the device
	    // Aqui nós pegamos o endereço dos registadores na BAR0,
        // Então mapeamos esse endereço físico para termos um endereço virtual 
	    // para manipularmos os registradores. 	
	
	    phy_address = (pci_device->BAR0 & 0xFFFFFFF0);
		
		//...
	}
	
	//
	// ## Base address ##
	//
	
	//mapeando para obter o endereço virtual que o kernel pode manipular.
	unsigned long virt_address = mapping_nic0_device_address ( phy_address );
	
	//endereço base.
	unsigned char *base_address = (unsigned char *) virt_address;
	unsigned long *base_address32 = (unsigned long *) virt_address;

	
	// #debug
	//printf("phy_address = %x\n", phy_address );
	//printf("virt_address = %x\n", virt_address );		
	//refresh_screen();
	//while(1){}
	
    //
	//  NIC
	//
	
	unsigned short tmp16;
	
	currentNIC = (void *) malloc ( sizeof( struct intel_nic_info_d ) );
	
	if ( (void *) currentNIC ==  NULL )
	{
		printf("init_nic: currentNIC struct\n");
	    return (int) -1;	
		
	} else {
		
		currentNIC->used = 1;
		currentNIC->magic = 1234;
		
		currentNIC->pci = (struct pci_device_d *) pci_device;
		
		//salvando o endereço para outras rotinas usarem.
		currentNIC->registers_base_address = (unsigned long) &base_address[0];
		currentNIC->mem_base = (uint32_t) &base_address[0];
		
		currentNIC->use_io = 0; //False;
		
		//
		// #### Get Info ####
		//
		
		//device status
		currentNIC->DeviceStatus = base_address[0x8];		
		
		//
	    // ## EEPROM ##
	    //
		
		//False;
		//Como ainda não sabemos, vamos dizer que não.
		currentNIC->eeprom = 0; 
		
		uint32_t i; 
	    for ( i=0; i < 1000 && !currentNIC->eeprom; i++ ) 
	    {
		    // Let's try to discover reading the status field!
		    uint32_t val = E1000ReadCommand ( currentNIC, 0x14 );									
		
		    // We have?
		    if ( (val & 0x10) == 0x10) 
		    {
                // Yes :)  				
			    currentNIC->eeprom = 1;														
		    }
	    };

		//
		// ## MAC ##
		//
		
	    // Let's read the MAC Address!		

		
		
	    // We can use the EEPROM!
	    if (currentNIC->eeprom == 1) 
	    {
            //printf("MAC from eeprom \n");  
			//refresh_screen();
			//while(1){}
			 
		    uint32_t tmp = E1000ReadEEPROM ( currentNIC, 0 );										
		
		    currentNIC->mac_address[0] = (uint8_t)(tmp & 0xFF);
		    currentNIC->mac_address[1] = (uint8_t)(tmp >> 8);
		
		    tmp = E1000ReadEEPROM ( currentNIC, 1);
		
		    currentNIC->mac_address[2] = (uint8_t)(tmp & 0xFF);
		    currentNIC->mac_address[3] = (uint8_t)(tmp >> 8);
		
		    tmp = E1000ReadEEPROM ( currentNIC, 2);
		
		    currentNIC->mac_address[4] = (uint8_t)(tmp & 0xFF);
		    currentNIC->mac_address[5] = (uint8_t)(tmp >> 8);
		
		
		// We can't use the EEPROM :(
	    }else{
			
			//printf("MAC from registers \n"); 
			//refresh_screen();
			//while(1){}
		    
			//mac
		    //pegando o mac nos registradores.
		    currentNIC->mac_address[0] = base_address[ 0x5400 + 0 ];
		    currentNIC->mac_address[1] = base_address[ 0x5400 + 1 ];
		    currentNIC->mac_address[2] = base_address[ 0x5400 + 2 ];
		    currentNIC->mac_address[3] = base_address[ 0x5400 + 3 ];
		    currentNIC->mac_address[4] = base_address[ 0x5400 + 4 ];
		    currentNIC->mac_address[5] = base_address[ 0x5400 + 5 ];
	    };	
	};	
	
	
    //
	// ## bus mastering ##
	//
	
	// Let's enable bus mastering!
	// #define PCI_COMMAND 0x04
	// We really need to do it?
    // Yes, set the bus mastering bit
	// And write back 		
		
	//( bus, slot, func, PCI_COMMAND )
	uint16_t cmd = pciConfigReadWord ( (unsigned char) bus, 
	                (unsigned char) dev, 
					(unsigned char) fun, 
					(unsigned char) 0x04 );
	
	if ((cmd & 0x04) != 0x04) 
	{
		cmd |= 0x04;
		
		//(bus, slot, func, PCI_COMMAND, cmd);
		diskWritePCIConfigAddr ( (int) bus, (int) dev, (int) fun, 
			(int) 0x04, (int) cmd ); 		
	};
	
	printf("done\n");
		
    return 0;	
}



/*
 *******************************************
 * xxxe1000handler:
 *     e1000 handler :)
 */

 
void xxxe1000handler (){
		
	//structs
	struct ipv6_header_d *ipv6_h;
	struct ether_header *eh;
	struct ether_arp *arp_h;
	
    int i;	
	
	// #flag !!
	// Essa flag precisa ser acionada para a rotina funcionar.
	// F6 tem acionado essa flag.
	
	if ( e1000_interrupt_flag != 1 )
		return;	
	
	//intel.h
	e1000_irq_count++;
	
	
	//printf("xxxe1000handler: #debug e1000\n");
	//refresh_screen();	
	
	// Without this, the card may spam interrupts...
	E1000WriteCommand( currentNIC, 0xD0, 1);		
	
	//status
	uint32_t status = E1000ReadCommand ( currentNIC, 0xC0 ); 

	// Linkup
	if (status & 0x04) 
	{															
		uint32_t val = E1000ReadCommand ( currentNIC, 0 );
		E1000WriteCommand( currentNIC, 0, val | 0x40 );
		return;
	
	} else if (status & 0x80){
		
	    //printf("xxxe1000handler: handler for NIC e1000");
		//printf("e1000 handler ");
	    //refresh_screen();
		
		
		while ( (currentNIC->legacy_rx_descs[currentNIC->rx_cur].status & 0x01) == 0x01 ) 
		{
			uint16_t old = currentNIC->rx_cur;
			uint32_t len = currentNIC->legacy_rx_descs[old].length;
			
			// Our Net layer should handle it
			//NetHandlePacket(dev->ndev, len, (PUInt8)dev->rx_descs_virt[old]);

            //printf(">"); 			
			
			currentNIC->legacy_rx_descs[old].status = 0;
			currentNIC->rx_cur = (currentNIC->rx_cur + 1) % 32;
			
			//??
			E1000WriteCommand ( currentNIC, 0x2818, old );
		}		
		
	};
	
	//
	// =================== ## Reagir ## ================================
	//
	

	//pega o buffer 0 de rx 
	//unsigned char *buffer = (unsigned char *) currentNIC->rx_descs_virt[0];
	
	//#esse funcionou.
	//unsigned char *buffer = (unsigned char *) currentNIC->rx_descs_virt[1];	
	
	//#todo
	//mas vamos tentar ler o rx current
	unsigned char *buffer = (unsigned char *) currentNIC->rx_descs_virt[old];	
	
	//
	// ## eth header ##
	//
	
	//ethernet header
	eh = (void *) &buffer[0];
	
	if ( (void *) eh == NULL ){
		printf("intel-xxxe1000handler: eh");
		die();
	}
	
	//printf("src: ");
    //for( i=0; i<6; i++)
	//	printf("%x ",eh->src[i]);
	
	//printf("dst: ");
    //for( i=0; i<6; i++)
	//	printf("%x ",eh->dst[i]);
	
	//printf("type={%x} ",eh->type);	
	
	//
	// ## type ##
	//
	
	
	//printf("+");
	//refresh_screen();
	
	uint16_t type = FromNetByteOrder16(eh->type);
	
	switch ( (uint16_t) type)
	{
		//0x0800	Internet Protocol version 4 (IPv4)
		case 0x0800:
		   //printf("todo: Internet Protocol version 4 (IPv4)\n");
		   //printf("IPv4 ");
		   //refresh_screen();
		   return;
		   break;
		   
		//0x0806	Address Resolution Protocol (ARP)
		case 0x0806:
		    //printf("\nARP ");
			arp_h = (void *) &buffer[14];
		    //printf("todo: Address Resolution Protocol (ARP) ");
			if ( arp_h->op == ToNetByteOrder16(ARP_OPC_REPLY) )
			{
				//#debug
				//printf("REPLY received\n");
	            //printf("src: ");
                //for( i=0; i<4; i++)
	            //	printf("%x ",arp_h->arp_spa[i]);				
				//refresh_screen();
                return;				
			}
			if ( arp_h->op == ToNetByteOrder16(ARP_OPC_REQUEST) )
			{
				//#debug
				printf("REQUEST received ");
                for( i=0; i<6; i++){ printf("%x ",eh->src[i]); }
                printf(" | ");
				for( i=0; i<6; i++){ printf("%x ",eh->dst[i]); }
                printf(" | ");
				for( i=0; i<4; i++){ printf("%d ",arp_h->arp_spa[i]); }								
				 printf(" | ");
				for( i=0; i<4; i++){ printf("%d ",arp_h->arp_tpa[i]); }
				//refresh_screen();
				//cache
				for (i=0; i<32; i++)
				{
				    //livre
					if ( currentNIC->arp_cache[i].used == 1 && currentNIC->arp_cache[i].magic == 1234 )
					{
						//compara o ip
					    if ( strncmp( (char *) &currentNIC->arp_cache[i].ipv4_address[0], (char *) &arp_h->arp_spa[0], 4 ) == 0 )
						{
							memcpy ( (void*) &currentNIC->arp_cache[i].mac_address[0] , (const void *) &eh->src[0], 6);
							
							//sinaliza que está em uso.
							currentNIC->arp_cache[i].magic = 4321;
						}
							
					}
				}
				
				uint16_t arp_tx_old = currentNIC->tx_cur;
			    uint32_t arp_tx_len = currentNIC->legacy_tx_descs[arp_tx_old].length;
			
				//muda para REPLAY.
				arp_h->op = ToNetByteOrder16(ARP_OPC_REPLY);
				
                //reenvia os mesmos dados, mas modificados para replay.
				//essa rotina vai copiar de um buffer para outro.
			    E1000Send ( (void *) currentNIC, (uint32_t) arp_tx_len, (uint8_t *) &buffer[0]);	
			    
				printf("\n");
				refresh_screen();
				return;
			} 
		    return;
			break;
			
		//0x86DD	Internet Protocol Version 6 (IPv6)
		case 0x86DD:
			//printf("IPv6 ");
		    ipv6_h = (void *) &buffer[14];
		    //
			handle_ipv6 ( (struct intel_nic_info_d *) currentNIC, 
			    (struct ipv6_header_d *) ipv6_h );
			//refresh_screen();
			return;	
		    break;
	    
		default:
		    //printf("default ethernet type\n");
		    //refresh_screen();
			return;
			break;
	};
 

//done:

	//printf("\n");
	//refresh_screen();
	
	return;
	//while(1){}
};


//=======================================================
// Setup nic irq 
//
// #importante
// Isso é usado por uma hotina em headlib.s para 
// configurar uma nova entrada na idt. 
//

//o assembly tem que pegar aqui.
uint8_t nic_idt_entry_new_number;
uint32_t nic_idt_entry_new_address;

void e1000_setup_irq (){
	
	
	debug_print("e1000_setup_irq\n");

    //Essa é a rotina em assembly que cria uma entrada na idt para 
    //o nic, com base nas variáveis que são importadas pelo assembly.
	//headlib.s
	
	extern void asm_nic_create_new_idt_entry();
	
	//pegando o númeo da irq
    uint8_t irq = (uint8_t) currentNIC->pci->irq_line;
	uint32_t handler = (uint32_t) &xxxe1000handler;//test
	
	//#debug 
	//printf("PCIRegisterIRQHandler: irq={%d}\n",irq);
	//printf("PCIRegisterIRQHandler: handler={%x}\n", handler);
	//printf("PCIRegisterIRQHandler: pin={%d}\n",currentNIC->pci->irq_pin);//shared INTA#
	//refresh_screen();
	//while(1){}

	//transformando irq em numero de interrupção.
	uint8_t idt_num = (irq + 32);
	
	// Chamando asm:
	// número e endereço.
	
	nic_idt_entry_new_number = (uint8_t) idt_num;   
	nic_idt_entry_new_address = (unsigned long) handler; 
	
	asm_nic_create_new_idt_entry();			
};



//====================================================
// ## reset ##
//

int e1000_reset_controller (){
	
	int i=0;
	
	
	debug_print("e1000_reset_controller\n");
	
	//unsigned long tmp;
	
	//#debug
	//printf("nic_i8254x_reset: Reseting controller ... \n");
	
	/*
	if ( (void *) currentNIC ==  NULL )
	{
		printf("nic_i8254x_reset: currentNIC struct\n");
	    return (int) 1;	
		
	}	
    */
	
	//#todo: precisamos checar a validade dessa estrutura e do endereço.
	
    //esse será o endereço oficial.
	//currentNIC->mem_base	
	
	if ( currentNIC->mem_base == 0 )
	{
		printf("nic_i8254x_reset: currentNIC->mem_base fail");
		refresh_screen();
		while(1){}
	}
	
	//endereço base.
	//unsigned char *base_address = (unsigned char *) currentNIC->registers_base_address;
	//unsigned long *base_address32 = (unsigned long *) currentNIC->registers_base_address;	

	//unsigned char *base_address = (unsigned char *) currentNIC->mem_base;
	//unsigned long *base_address32 = (unsigned long *) currentNIC->mem_base;	
		
	//
	//===========================================
	//
	
	//
	//    ## TX ##
	//
	
	
    // And alloc the phys/virt address of the transmit buffer
	
	currentNIC->tx_descs_phys = E1000AllocCont (0x1000, (uint32_t *)(&currentNIC->legacy_tx_descs));	
	
	// We failed, unmap everything
	if (currentNIC->tx_descs_phys == 0) 
	{
		
		printf("E1000Init: currentNIC->tx_descs_phys fail");
			
		refresh_screen();
		while(1){};	
	};
	
	//tx
	//i já foi declarado
	
	for ( i=0; i < 8; i++ ) 
	{
		// Alloc the phys/virt address of this transmit desc
		// alocamos memória para o buffer, salvamos o endereço físico do buffer e 
        //obtemos o endereço virtual do buffer.		
		currentNIC->legacy_tx_descs[i].addr = E1000AllocCont ( 0x3000, &currentNIC->tx_descs_virt[i] );		
		currentNIC->legacy_tx_descs[i].addr2 = 0;
		
		// We failed, unmap everything
		if (currentNIC->legacy_tx_descs[i].addr == 0) 
		{
			
		    printf("E1000Init: dev->rx_descs[i].addr fail");
			
		    refresh_screen();
		    while(1){};	
		}
		
		//cmd: bits
		//IDE VLE DEXT RSV RS IC IFCS EOP
        //IDE (bit 7) - Interrupt Delay Enable
        //VLE (bit 6) - VLAN Packet Enable
        //DEXT (bit 5) - Descriptor extension (#importante: '0' for legacy mode)
        //RSV (bit 4) - Reserved
        //RS (bit 3) - Report status
        //IC (bit 2) - Insert checksum
        //IFCS (bit 1) - Insert FCS (CRC)
        //EOP (bit 0) - End of packet		
		currentNIC->legacy_tx_descs[i].cmd = 0;
		currentNIC->legacy_tx_descs[i].status = 1;
	};	

	//#debug 
	//Vamos imprimir os endereços usados pelos buffers para teste.	
	//for ( i=0; i < 8; i++ )
    //    printf ("PA={%x} VA={%x} \n",currentNIC->legacy_tx_descs[i].addr, currentNIC->tx_descs_virt[i]);
	
	//#debug 
	//breakpoint
	//refresh_screen();
	//while(1){}
	
	//
	//=============================================
	//
	
	//
	//    ## RX ##
	//
	
	
    // And alloc the phys/virt address of the transmit buffer
	
	currentNIC->rx_descs_phys = E1000AllocCont (0x1000, (uint32_t *)(&currentNIC->legacy_rx_descs));	
	
	// We failed, unmap everything
	if (currentNIC->rx_descs_phys == 0) 
	{
		
		printf("E1000Init: currentNIC->rx_descs_phys fail");
			
		refresh_screen();
		while(1){};	
	};
	
	//rx
	//i já foi declarado
	
	for ( i=0; i < 32; i++ ) 
	{
		// Alloc the phys/virt address of this transmit desc
		currentNIC->legacy_rx_descs[i].addr = E1000AllocCont ( 0x3000, (uint32_t *) &currentNIC->rx_descs_virt[i] );		
		currentNIC->legacy_rx_descs[i].addr2 = 0;
		
		// We failed, unmap everything
		if (currentNIC->legacy_rx_descs[i].addr == 0) 
		{
			
		    printf("E1000Init: dev->rx_descs[i].addr fail");
			
		    refresh_screen();
		    while(1){};	
		}
		
		currentNIC->legacy_rx_descs[i].status = 0;
		
	};	

	//#debug 
	//Vamos imprimir os endereços edereços físicos dos buffers 
	//e os edereços virtuais dos descritores.
	//for ( i=0; i < 32; i++ )
    //    printf ("PA={%x} VA={%x} \n",currentNIC->legacy_rx_descs[i].addr, currentNIC->rx_descs_virt[i]);
	
	//#debug 
	//breakpoint
	//refresh_screen();
	//while(1){}	
	
	
	//
	// ???
	//	
	
	//i já foi declarado
	for (i=0; i < 0x80; i++){
		E1000WriteCommand ( currentNIC, 0x5200 + (i * 4), 0 );
	}
	
	currentNIC->rx_cur = currentNIC->tx_cur = 0;
	
	//irq #todo
	//PCIRegisterIRQHandler ( bus, dev, fun, (unsigned long) E1000Handler, currentNIC );
	
	
    /** Transmit Enable. */
    //#define E1000_REG_TCTL_EN	(1 << 1)

    /** Pad Short Packets. */
    //#define E1000_REG_TCTL_PSP	(1 << 3)
	
   //#define E1000_ICR      0x000C0  /* Interrupt Cause Read - R/clr */
   //#define E1000_ITR      0x000C4  /* Interrupt Throttling Rate - RW */
   //#define E1000_ICS      0x000C8  /* Interrupt Cause Set - WO */
   //#define E1000_IMS      0x000D0  /* Interrupt Mask Set - RW */
   //#define E1000_IMC      0x000D8  /* Interrupt Mask Clear - WO */
   //#define E1000_IAM      0x000E0  /* Interrupt Acknowledge Auto Mask */	
   
   // #define E1000_IAC      0x04100  /* Interrupt Assertion Count */
   //#define E1000_ICRXPTC  0x04104  /* Interrupt Cause Rx Packet Timer Expire Count */
   //#define E1000_ICRXATC  0x04108  /* Interrupt Cause Rx Absolute Timer Expire Count */
  //#define E1000_ICTXPTC  0x0410C  /* Interrupt Cause Tx Packet Timer Expire Count */
  //#define E1000_ICTXATC  0x04110  /* Interrupt Cause Tx Absolute Timer Expire Count */
  //#define E1000_ICTXQEC  0x04118  /* Interrupt Cause Tx Queue Empty Count */
  //#define E1000_ICTXQMTC 0x0411C  /* Interrupt Cause Tx Queue Minimum Threshold Count */
  //#define E1000_ICRXDMTC 0x04120  /* Interrupt Cause Rx Descriptor Minimum Threshold Count */
  //#define E1000_ICRXOC   0x04124  /* Interrupt Cause Receiver Overrun Count */  
	
   
   // (*((uint32_t *) (start + E1000_IMS))) |= E1000_IMS_RXT0;
    //(*((uint32_t *) (start + E1000_IMS))) |= E1000_IMS_RXO;
   // (*((uint32_t *) (start + E1000_IMS))) |= E1000_IMS_RXDMT0;
   // (*((uint32_t *) (start + E1000_IMS))) |= E1000_IMS_RXSEQ;
   // (*((uint32_t *) (start + E1000_IMS))) |= E1000_IMS_LSC;	
	
	//E1000WriteCommand(currentNIC, 0xD0, E1000_IMS_RXT0 | E1000_IMS_RXO );
	
	// Enable interrupts
	//0xD0 Message Control (0x0080) Next Pointer (0xE0) Capability ID (0x05)
	//    0000 0001  1111 0111  0000   0010  1101   0111
	//1f72d7
	//E1000WriteCommand(currentNIC, 0xD0, 0x1f72d7);
	E1000WriteCommand(currentNIC, 0xD0, 0x1F6DC);											
	//E1000WriteCommand(currentNIC, 0xD0, 0xFB);
	E1000ReadCommand(currentNIC, 0xC0);
	
	
	// ## RX ##
	
	//receive
	//Setup the (receive) ring registers.
	// Pass the physical address (and some other informations) of the receive buffer
	E1000WriteCommand(currentNIC, 0x2800, currentNIC->rx_descs_phys );	//low							
	E1000WriteCommand(currentNIC, 0x2804, 0);                           //high 
	E1000WriteCommand(currentNIC, 0x2808, 512);                         //32*16
	E1000WriteCommand(currentNIC, 0x2810, 0);    //head
	E1000WriteCommand(currentNIC, 0x2818, 31);   //tail
	E1000WriteCommand(currentNIC, 0x100, 0x602801E); //RCTL	= 0x0100,	/* Receive Control */
	
	
	// ## TX ##
	
	//transmit
	//Setup the (transmit) ring registers.
	// Pass the physical address (and some other informations) of the transmit buffer
	
	//TDBAL	= 0x3800,	/* Tx Descriptor Base Address Low */
	//TDBAH	= 0x3804,	/* Tx Descriptor Base Address High */
	
	E1000WriteCommand(currentNIC, 0x3800, currentNIC->tx_descs_phys );	//low (endereço do ring)							
	E1000WriteCommand(currentNIC, 0x3804, 0);                           //high
	
	E1000WriteCommand(currentNIC, 0x3808, 128);                         //8*16
	E1000WriteCommand(currentNIC, 0x3810, 0);  //head
	E1000WriteCommand(currentNIC, 0x3818, 0);  //tail
	
	//#define E1000_TCTL     0x00400  /* TX Control - RW */
    //• CT = 0x0F (16d collision)
    //• COLD: HDX = 511 (0x1FF); FDX = 63 (0x03F)
    //• PSP = 1b
    //• EN=1b
    //• All other fields 0b	
     /* Transmit Control */
    //#define E1000_TCTL_RST    0x00000001    /* software reset */
    //#define E1000_TCTL_EN     0x00000002    /* enable tx */
    //#define E1000_TCTL_BCE    0x00000004    /* busy check enable */
    //#define E1000_TCTL_PSP    0x00000008    /* pad short packets */
    //#define E1000_TCTL_CT     0x00000ff0    /* collision threshold */
    //#define E1000_TCTL_COLD   0x003ff000    /* collision distance */
    //#define E1000_TCTL_SWXOFF 0x00400000    /* SW Xoff transmission */
    //#define E1000_TCTL_PBE    0x00800000    /* Packet Burst Enable */
    //#define E1000_TCTL_RTLC   0x01000000    /* Re-transmit on late collision */
    //#define E1000_TCTL_NRTU   0x02000000    /* No Re-transmit on underrun */
    //#define E1000_TCTL_MULR   0x10000000    /* Multiple request support */

	//habilita esses dois campos e o resto é zero.
    //• GRAN = 1b (descriptors)
    //• WTHRESH = 1b
    //• All other fields 0b.	
	//#define E1000_TXDCTL_WTHRESH 0x003F0000 /* TXDCTL Writeback Threshold */
	//#define E1000_TXDCTL_GRAN    0x01000000 /* TXDCTL Granularity */
	//#define E1000_TXDCTL   0x03828  /* TX Descriptor Control - RW */
    E1000WriteCommand(currentNIC, 0x3828, (0x01000000 | 0x003F0000)); 

	
    E1000WriteCommand ( currentNIC,  0x400, ( 0x00000ff0 | 0x003ff000 | 0x00000008 | 0x00000002) ); 	
	//E1000WriteCommand(currentNIC, 0x400, 0x10400FA);  //TCTL	= 0x0400,	/* Transmit Control */
	//E1000WriteCommand(currentNIC, 0x400, 0x3003F0FA);
	//E1000WriteCommand(currentNIC, 0x400, (1 << 1) | (1 << 3) );
 
    //• IPGT = 8
    //• IPGR1 = 2
    //• IPGR2 = 10
    //#define E1000_TIPG     0x00410  /* TX Inter-packet gap -RW */	
	 E1000WriteCommand ( currentNIC,  0x410, (  0x0000000A | 0x00000008 | 0x00000002) ); 	


	//talvez ja fizemos isso. 
	//Initialize the transmit descriptor registers (TDBAL, TDBAH, TDL, TDH, and TDT).


    //eth_write(base_addr, REG_ADDR_MAC_CONF,
	//	  /* Set the RMII speed to 100Mbps */
	//	  MAC_CONF_14_RMII_100M |
	//	  /* Enable full-duplex mode */
	//	  MAC_CONF_11_DUPLEX |
	//	  /* Enable transmitter */
	//	  MAC_CONF_3_TX_EN |
	//	  /* Enable receiver */
	//	  MAC_CONF_2_RX_EN);	
    
	
	//iow32(dev, TCTL, TCTL_EN);
	
	//printf("nic_i8254x_reset: Done\n");
	//refresh_screen();	
	
	//endereço físico  dos rings;
	//printf("tx_ring_pa=%x rx_ring_pa=%x \n", 
	//    currentNIC->rx_descs_phys, 
	//	currentNIC->tx_descs_phys );
	

	// Linkup
	uint32_t val = E1000ReadCommand(currentNIC, 0);											
	E1000WriteCommand(currentNIC, 0, val | 0x40);	//(1 << 6)
		
	return 0;
}


void E1000WriteCommand ( struct intel_nic_info_d *d, uint16_t addr, uint32_t val ){
	
	
	// Use the IO ports?
	//if (dev->use_io) 
	//{
	//  Yes
	//	PortOutLong(dev->io_base, addr);											
	//	PortOutLong(dev->io_base + 4, val);
	//} else {
	//  No
	//	*( (volatile unsigned int *)(d->mem_base + addr)) = val;							
	//}
	
	*( (volatile unsigned int *)(d->mem_base + addr)) = val;
}


uint32_t E1000ReadCommand(struct intel_nic_info_d *d, uint16_t addr){
	
	// Use the IO ports?
	//if (dev->use_io) 
	//{	
	//  Yes
	//	PortOutLong(dev->io_base, addr);											
	//	return PortInLong(dev->io_base + 4);
	//} else {
	//  No
	//	return *( (volatile unsigned int *) (d->mem_base + addr));							
	//}
	
	return *( (volatile unsigned int *) (d->mem_base + addr));
}


/*
 * E1000AllocCont: ??
 * retorna o endereço fisico e coloca o virtual em *virt
 * ah ... então eu vou alocar usando endereços virtuais
 * ... e traduzir para físico 
 * ... colocar o virtual em *virt e retornar o físico.
 */

uint32_t E1000AllocCont ( uint32_t amount, uint32_t *virt ){
	
	uint32_t va = (uint32_t) malloc ( (uint32_t) amount );
	
	*virt = va;
	
	if (*virt == 0)
	{
		printf("E1000AllocCont: falha ao alocar endereco virtual");
		refresh_screen();
		while(1){}
	}
	
	uint32_t pa = (uint32_t) virtual_to_physical ( va, gKernelPageDirectoryAddress ); 
	
	if (pa == 0)
	{
		printf("E1000AllocCont: pa fail");
		refresh_screen();
		while(1){}		
	}
	
	return pa;
}


/*
void NetSendEthPacket ( PNetworkDevice dev, 
                        uint8_t dest[6], 
						uint16_t type, 
						uint32_t len, 
						uint8_t *buf )
{
	
	//if ((dev == Null) || (dev->send == Null) || (dest == Null)) 
	//{																					// Sanity checks
	//	return;
	//}
	
	// Let's build our ethernet frame!
	//PEthFrame frame = (PEthFrame) MemAllocate ( sizeof(EthFrame) + len);	
	PEthFrame frame = (PEthFrame) malloc ( sizeof(EthFrame) + len);	
	
	// Failed :(
	//if (frame == Null) {
	//	return;			
	//}
	
	//StrCopyMemory(frame->dst, dest, 6);			// Copy the dest mac address
	//StrCopyMemory(frame->src, dev->mac_address, 6);	// The src mac address (our mac address)
	
	//StrCopyMemory((uint8_t *)(((uint32_t)frame) + sizeof(EthFrame)), buf, len);	// Copy the data/payload
	
	frame->type = ToNetByteOrder16(type);			// Set the type
	
	//void (*send)( void *, uint32_t, uint8_t );
	dev->send ( dev->priv, sizeof(EthFrame) + len, (uint8_t *) frame );		// SEND!
	
	//MemFree((uint32_t)frame);					// Free our eth frame
};
*/

 
//dispositivo, tamanho, dados a serem copiados no buffer.
void E1000Send ( void *ndev, uint32_t len, uint8_t *data ){
	
	//printf("E1000Send: GO!!! \n");
	//refresh_screen();	
	
	//
	// ## dev ##
	//
	
	struct intel_nic_info_d *dev = (struct intel_nic_info_d *) ndev;
	
	if ( (void *) dev == NULL )
		return;
	
	//
	// ## quem ? ##
	//
	
	uint16_t old = dev->tx_cur;
	
	
	// ## Copiando o pacote no buffer ##
	//com base no comprimento indicado no argmento.
	//pegando o endereço virtual do buffer na estrutura do dispositivo.	

	unsigned char *buffer = (unsigned char *) currentNIC->tx_descs_virt[old];
	unsigned char *src_data = (unsigned char *) data; 	

	if(len==0)
		return;	
	
	uint32_t i;
	
	//copiando o header ethernet
	for(i=0; i<len; i++){
		buffer[i] = src_data[i];
	}	
	
	
	
	//void *memcpy(void *v_dst, const void *v_src, unsigned long c);
	//StrCopyMemory((PUInt8)(dev->tx_descs_virt[old]), data, len);
	
	//memcpy( (void *)(dev->tx_descs_virt[old]), (const void *) data, (unsigned long) len);
	
	
    dev->legacy_tx_descs[old].length = len;

	dev->legacy_tx_descs[old].cmd = 0x1B;
	dev->legacy_tx_descs[old].status = 0;	
	
	dev->tx_cur = ( dev->tx_cur + 1 ) % 8;
	
	*( (volatile unsigned int *)(dev->mem_base + 0x3818)) = dev->tx_cur;	

	//#debug
	printf("sending broadcast arp(while)\n");
	refresh_screen();	
		
	while ( !(dev->legacy_tx_descs[old].status & 0xFF) )
	{
		//nothing
	}
	
	printf("E1000Send: done\n");
	refresh_screen();	
};


//enviar um pacote ipv4
//configuramos o buffer
//e arotina de sent faz o trabalho. 
//mas pecisamos passar o tamanho do buffer como argumento.
//o tamanho dobuffer é a soma do ethernet header e a strutura de ipv4.
//14+20 bytes

void 
send_ipv4_packet ( struct intel_nic_info_d *dev, 
                   uint32_t len, 
				   uint8_t *data )
{
	
	if ( (void *) dev == NULL )
	    return;
	
	E1000Send ( (void *) dev, (uint32_t) len , (uint8_t *) &data[0]);	
};


//#deletar isso
// transmit:
void nic_i8254x_transmit(){
	printf("nic_i8254x_transmit:\n");  //cancelada; fizemos outra.
};


/*
void show_current_nic_info (){

	if ( (void *) currentNIC ==  NULL )
	{
		printf("show_current_nic_info: struct fail\n");
	    return;	
	}else{
		
		if ( currentNIC->used != 1 || currentNIC->magic != 1234 )
		{
		    printf("show_current_nic_info: validation fail\n");
	        return;				
		}
		
		if ( (void *) currentNIC->pci == NULL )
		{
		    printf("show_current_nic_info: pci struct fail\n");
	        return;				
		}

        //messages  		
		printf("NIC device info:\n");
		printf("Vendor %x Device %x \n", 
		    currentNIC->pci->Vendor, currentNIC->pci->Device );
			
			
		//bars	
		printf("BAR0 %x\n",currentNIC->pci->BAR0);
		printf("BAR1 %x\n",currentNIC->pci->BAR1);
		printf("BAR2 %x\n",currentNIC->pci->BAR2);
		printf("BAR3 %x\n",currentNIC->pci->BAR3);
		printf("BAR4 %x\n",currentNIC->pci->BAR4);
		printf("BAR5 %x\n \n",currentNIC->pci->BAR5);
		
		//
		// ## Device status ##
		//
		
		
        //To test your mapping, try printing out the device status register 
		//(section 13.4.2). This is a 4 byte register that starts at byte 8 
		//of the register space. You should get 0x80080783, which indicates 
		//a full duplex link is up at 1000 MB/s, among other things.		
		
		
 
		
		printf("Device status %x \n", currentNIC->DeviceStatus );
		
		// Full duplex.0=half,1=full 
		if (currentNIC->DeviceStatus & 1)
		{
			printf("Full duplex \n");
		}

        // Link up.0=no,1=link  		
		if (currentNIC->DeviceStatus & 2)
		{
			printf("link up \n");
		}
		
		// transmission paused
		if (currentNIC->DeviceStatus & 0x10)
		{
			printf("transmission paused\n");
		}
		
		// TBI mode 
		if (currentNIC->DeviceStatus & 0x20)
		{
			printf("TBI mode\n");
		}
		
		
		// Speed 1000Mb/s 
		if (currentNIC->DeviceStatus & 0x80)
		{
			//currentNIC->speed #todo
			printf("1000Mbs\n");
		}	

		//
		// ## MAC ##
		//
		
		printf ("MAC %x %x %x %x %x %x \n", 
		    currentNIC->mac_address[0], 
			currentNIC->mac_address[1], 
			currentNIC->mac_address[2],
            currentNIC->mac_address[3], 
			currentNIC->mac_address[4], 
			currentNIC->mac_address[5] );

		//
		// ## IP ##
		//
			
		printf ("IP %d %d %d %d \n", 
		    currentNIC->ip_address[0], 
			currentNIC->ip_address[1], 
			currentNIC->ip_address[2],
            currentNIC->ip_address[3] );
			
			
        printf("int_line={%d} int_pin={%d}\n",
		    currentNIC->pci->irq_line,     //irq
			currentNIC->pci->irq_pin );    //shared INTA#			
			
		//...
		
	};	    
	
};
*/


uint32_t E1000ReadEEPROM ( struct intel_nic_info_d *d, uint8_t addr ){
	
	uint32_t data = 0;

	// We have the EEPROM?
    
	//#debug
	//printf("E1000ReadEEPROM:\n");
	
    // Yes :)	
	if (d->eeprom == 1) 
	{
		
		E1000WriteCommand ( d, 0x14, 1 | (addr << 8) );

        //#bugbug
		//#obs: loop		
		while (( (data = E1000ReadCommand( d, 0x14)) & 0x10 ) != 0x10 );
		
	// Nope...	
	} else {
		
		E1000WriteCommand ( d, 0x14, 1 | (addr << 2) );								
		
		//#bugbug
		//#obs: loop
		while (( (data = E1000ReadCommand(d, 0x14)) & 0x01 ) != 0x01 );
	}
	
	return (data >> 16) & 0xFFFF; 
}


//
// End.
//


