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
 * History:
 *     2016 - Created by Fred Nora.
 *
 */
 
 
 //#todo:
 // +++ fazer os rings de transmissão e de recepção 
 // +++ providenciar buffers. 
 // +++ criar os descritores.
 
 
// >> The register at offset 0x00 is the "IOADDR" window. 
// >> The register at offset 0x04 is the "IODATA" window. 

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

/*
void nicHandler();
void nicHandler()
{
	return;
}
*/


/*
 * init_network:
 *     Inicializa o módulo gerenciador de rede.
 *     @todo: deletar: Usar nicInit()
 *
 * ## bugbug: problemas no mapeamento do endereço encontrado em BAR0
 */
 
//intel_init_nic() 
 
int init_nic (){
	
	//pci info.
	uint32_t data; 
	unsigned char bus;
	unsigned char dev;
	unsigned char fun;			


	printf("\n");
	printf("init_nic: Probing PCI ...\n");
	
	// #test 
	// Encontrar placa de rede.
	
	data = (uint32_t) diskPCIScanDevice (PCI_CLASSCODE_NETWORK);
	
	if ( data == -1 )
	{
		printf("init_nic: Controller not found\n");
		//refresh_screen();
		
		return (int) 1;
	
	} else {
	    
		bus = ( data >> 8 & 0xff );
        dev = ( data >> 3 & 31 );
        fun = ( data & 7 );
	};

	
	// # get info
	// #pci
	// Pegaremos mais informações e colocaremos na estrutura de 
	// dispositivo pci.
	
	data = (uint32_t) diskReadPCIConfigAddr ( bus, dev, fun, 0 );

	//#debug
	printf("Vendor=%x \n", (data & 0xffff) );
	printf("Device=%x \n", (data >> 16 &0xffff) );
	
	// 8086:100e
	// 82540EM Gigabit Ethernet Controller
	
	struct pci_device_d *pci_device;
	
	pci_device = (void *) malloc ( sizeof( struct pci_device_d  ) );
	
	if ( (void *) pci_device ==  NULL )
    {
		
		printf("init_nic: pci_device struct\n");
		return (int) 1;
	
	}else{
		
		pci_device->deviceUsed = 1;
		pci_device->deviceMagic = 1234;
		
		pci_device->bus = (unsigned char) bus;
		pci_device->dev = (unsigned char) dev;
		pci_device->func = (unsigned char) fun;
		
		pci_device->Vendor = (unsigned short) (data & 0xffff);
		pci_device->Device = (unsigned short) (data >> 16 & 0xffff);
		
		//if ( pci_device->Vendor != 0x8086 ){
		//	printf("init_nic: fail \n");
		//	pci_device->deviceUsed = 0;
		//	free(pci_device);	
		//	return (int) 1;
		//}
		
		pci_device->BAR0 = (unsigned long) diskReadPCIConfigAddr ( bus, dev, fun, 0x10 );
		pci_device->BAR1 = (unsigned long) diskReadPCIConfigAddr ( bus, dev, fun, 0x14 ); 
		pci_device->BAR2 = (unsigned long) diskReadPCIConfigAddr ( bus, dev, fun, 0x18 );
		pci_device->BAR3 = (unsigned long) diskReadPCIConfigAddr ( bus, dev, fun, 0x1C );
		pci_device->BAR4 = (unsigned long) diskReadPCIConfigAddr ( bus, dev, fun, 0x20 );
		pci_device->BAR5 = (unsigned long) diskReadPCIConfigAddr ( bus, dev, fun, 0x24 );
		
		//#todo:
		//Temos que pegar o número da interrupção.
		
		//...
	};
	
	//
	// ## Base address ##
	//
	
    // ##importante:
	// Grab the Base I/O Address of the device
	// Aqui nós pegamos o endereço dos registadores na BAR0,
    // Então mapeamos esse endereço físico para termos um endereço virtual 
	// para manipularmos os registradores. 	
	
	unsigned long phy_address = (pci_device->BAR0 & 0xFFFFFFF0);
	
	//mapeando para obter o endereço virtual que o kernel pode manipular.
	unsigned long virt_address = mapping_nic0_device_address ( phy_address );
	
	//endereço base.
	unsigned char *base_address = (unsigned char *) virt_address;
	unsigned long *base_address32 = (unsigned long *) virt_address;

	//se for 0 temos que pegar de outro jeito.
	//if ( base_address[0x5400 + 0] == 0 &&
	//     base_address[0x5400 + 1] == 0 &&
	//	 base_address[0x5400 + 2] == 0 &&
    //     base_address[0x5400 + 3] == 0 &&
    //     base_address[0x5400 + 4] == 0 &&
    //     base_address[0x5400 + 5] == 0  )
	//{
		//pegar em outro lugar.	 
	//}  		 
	
	//ok, os endereços estão certos.
	//printf("phy_address = %x\n", phy_address );
	//printf("virt_address = %x\n", virt_address );
	
	//int z;
	
	//for( z=0; z<50; z++ )
	//{
	//    printf("%x \n",base_address32[z]);		
	//}
	
	//printf("%x ",base_address32[0]);
	//printf("%x ",base_address32[0]);
	//printf("%x ",base_address32[0]);
	//printf("%x ",base_address32[0]);
	//printf("%x ",base_address32[0]);
	//printf("%x ",base_address32[0]);
		
	//refresh_screen();
	//while(1){}
	
    //
	//  NIC
	//
	
	unsigned short tmp16;
	
	currentNIC = (void *) malloc ( sizeof( struct nic_info_d ) );
	
	if ( (void *) currentNIC ==  NULL )
	{
		printf("init_nic: currentNIC struct\n");
	    return (int) 1;	
		
	} else {
		
		currentNIC->used = 1;
		currentNIC->magic = 1234;
		
		currentNIC->pci = (struct pci_device_d *) pci_device;
		
		//salvando o endereço para outras rotinas usarem.
		currentNIC->registers_base_address = (unsigned long) &base_address[0];
		
		
		//
		// #### Get Info ####
		//
		
		//device status
		currentNIC->DeviceStatus = base_address[0x8];
		
		
		//mac
		//pegando o mac nos registradores.
		currentNIC->mac0 = base_address[ 0x5400 + 0 ];
		currentNIC->mac1 = base_address[ 0x5400 + 1 ];
		currentNIC->mac2 = base_address[ 0x5400 + 2 ];
		currentNIC->mac3 = base_address[ 0x5400 + 3 ];
		currentNIC->mac4 = base_address[ 0x5400 + 4 ];
		currentNIC->mac5 = base_address[ 0x5400 + 5 ];
		
		
        //Read MAC address using eeprom
        //## BUGBUG ##		
        //fail: travando no loop		
		
		//#debug
		//printf("#debug reading eeprom\n");
        //refresh_screen();
		//tmp16 = e1000_eeprom_read_8254x( (unsigned long) &base_address[0], 0);
        //currentNIC->mac0 = (unsigned char) tmp16 & 0xff;
        //currentNIC->mac1 = (unsigned char) (tmp16 >> 8) & 0xff;
		//tmp16 = e1000_eeprom_read_8254x( (unsigned long) &base_address[0], 1);
        //currentNIC->mac2 = (unsigned char) tmp16 & 0xff;
        //currentNIC->mac3 = (unsigned char) (tmp16 >> 8) & 0xff;
		//tmp16 = e1000_eeprom_read_8254x( (unsigned long) &base_address[0], 2);
        //currentNIC->mac4 = (unsigned char) tmp16 & 0xff;
        //currentNIC->mac5 = (unsigned char) (tmp16 >> 8) & 0xff;		
		//#debug
		//printf("#debug reading eeprom ok\n");
		//refresh_screen();
		
		//...
		
	};	
	
	
	//reset
	nic_i8254x_reset ();
	
	printf("init_nic: done\n");		

    return (int) 0;	
};



//testando controlador ... 
//encontrando o controlador e identificando vendor e device.
void nic_test1 (){
	
/*	
	//pci info.
	uint32_t data; 
	unsigned char bus;
	unsigned char dev;
	unsigned char fun;		
	
	printf("\n");
	printf("probing pci ...\n");
					
	data = (uint32_t) diskPCIScanDevice ( PCI_CLASSCODE_NETWORK);
	
	//#test: testando encontrar placa de rede.
	if( data == -1 )
	{
		printf("**fail**\n");
		refresh_screen();
	}
					
	bus = ( data >> 8 &0xff );
    dev = ( data >> 3 &31 );
    fun = ( data &7 );
					
	data = (uint32_t) diskReadPCIConfigAddr( bus, dev, fun, 0 );
					
	printf("Vendor=%x \n", (data & 0xffff) );
	printf("Device=%x \n", (data >> 16 &0xffff) );
	printf("done\n");	
*/

};


void nic_i8254x_reset (){
	
	//unsigned long tmp;
	
	printf("nic_i8254x_reset: Reseting controller ... \n");

	//#todo: precisamos checar a validade dessa estrutura e do endereço.
	
	//endereço base.
	unsigned char *base_address = (unsigned char *) currentNIC->registers_base_address;
	unsigned long *base_address32 = (unsigned long *) currentNIC->registers_base_address;	
	
	
	//
	// ## BUGBUG ##
	// Erro ao aplicar o deslocamento em bytes num array de dwords.
	//
	
	//; Disable all interrupt causes
	//; Interrupt Mask Clear Register
	//0xFFFFFFFF;
	base_address[0x00D8 + 0] = 0xFF;
	base_address[0x00D8 + 1] = 0xFF;
	base_address[0x00D8 + 2] = 0xFF;
	base_address[0x00D8 + 3] = 0xFF;
	
	
	//#todo: 0x00C0 clear pending interrupts;
	
	//Disable interrupt throttling logic
	//Interrupt Throttling Register
	//0; 
	base_address[0x00C4 + 0] = 0;
	base_address[0x00C4 + 1] = 0;
	base_address[0x00C4 + 2] = 0;
	base_address[0x00C4 + 3] = 0;
	
	//PBA: set the RX buffer size to 48KB (TX buffer is calculated as 64-RX buffer)
	//Transmit Configuration Word
	//0x00000030; 
	base_address[0x1000 + 0] = 0x30; 
	base_address[0x1000 + 1] =  0;
	base_address[0x1000 + 2] =  0; 
	base_address[0x1000 + 3] =  0;
	
	//; TXCW: set ANE, TxConfigWord (Half/Full duplex, Next Page Request)
	//0x80008060 
	base_address[0x0178 + 0] = 0x60; 
	base_address[0x0178 + 1] = 0x80;
	base_address[0x0178 + 2] =  0; 
	base_address[0x0178 + 3] =  0x80;
	
	//#todo:
	//rever esses bits;
	// CTRL: clear LRST, set SLU and ASDE, clear RSTPHY, VME, and ILOS
	//0x0000
	//limpar alguns bit so Control
	//; LRST = 0        3
	//; SLU = 1         6
	//; ASDE = 1        5
	//; PHY_RST = 0     31
	//; VME = 0 (Disable 802.1Q)   30
	//; ILOS = 0                   7
	
	//#todo
	//0011 1111 1111 1111 1111 1111 0111 0111
	//2    f    f    f    f    f    7    7 
	//0x2fffff77
	
	//#bugbug: precisamos setar alguns bits;
	//pegamos modificamos e salvamos.
	unsigned long tmp = base_address32[0];
	//base_address32[0] = (tmp & 0x2fffff77);
    //base_address32[0] = (tmp | 0x2fffff77);	
	base_address32[0] = 0x2fffff77;	
	
	
	//; MTA: reset
	//; Multicast Table Array
	//0x5200
	//0xFFFFFFFF;
	base_address[0x5200 + 0] = 0xff; 
	base_address[0x5200 + 1] = 0xff;
	base_address[0x5200 + 2] = 0xff;
	base_address[0x5200 + 3] = 0xff;
	
	base_address[0x5204 + 0] = 0xff; 
	base_address[0x5204 + 1] = 0xff;
	base_address[0x5204 + 2] = 0xff;
	base_address[0x5204 + 3] = 0xff;

	base_address[0x5208 + 0] = 0xff; 
	base_address[0x5208 + 1] = 0xff;
	base_address[0x5208 + 2] = 0xff;
	base_address[0x5208 + 3] = 0xff;

	base_address[0x520c + 0] = 0xff; 
	base_address[0x520c + 1] = 0xff;
	base_address[0x520c + 2] = 0xff;
	base_address[0x520c + 3] = 0xff;	
	
	//
	// ## TX RING ##
	//
	
	//configurar a recepção.
	
	//#todo: talvez tenha que fazer isso.
	// TXCW: set ANE, TxConfigWord (Half/Full duplex, Next Page Request)
	//0x80008060
	
	// TDBAL
	//; Transmit Descriptor Base Address Low
	//0x0080000;  //low
	base_address[0x3800 + 0] = 0;     //low
	base_address[0x3800 + 1] = 0;
	base_address[0x3800 + 2] = 0x80;
	base_address[0x3800 + 3] = 0;
    base_address[0x3800 + 4] = 0;     //high
    base_address[0x3800 + 5] = 0;
    base_address[0x3800 + 6] = 0;
    base_address[0x3800 + 7] = 0;	
	
	//TX Descriptor Length 256 = 0x0100
	//(32 * 8);	
	base_address[0x3808 + 0] = 0; 
	base_address[0x3808 + 1] = 0x01; 
	base_address[0x3808 + 2] = 0; 
	base_address[0x3808 + 3] = 0; 
	base_address[0x3808 + 4] = 0; 
	base_address[0x3808 + 5] = 0; 
	base_address[0x3808 + 6] = 0; 
	base_address[0x3808 + 7] = 0; 
	
	
	//TDH - Transmit Descriptor Head
	//0;
	base_address[0x3810 + 0] = 0;
	base_address[0x3810 + 1] = 0;
	base_address[0x3810 + 2] = 0;
	base_address[0x3810 + 3] = 0;
	base_address[0x3810 + 4] = 0;
	base_address[0x3810 + 5] = 0;
	base_address[0x3810 + 6] = 0;
	base_address[0x3810 + 7] = 0;
	
	//TDL - Transmit Descriptor Tail
    //1;
	base_address[0x3818 + 0] = 1;
	base_address[0x3818 + 1] = 0;
	base_address[0x3818 + 2] = 0;
	base_address[0x3818 + 3] = 0;
	base_address[0x3818 + 4] = 0;
	base_address[0x3818 + 5] = 0;
	base_address[0x3818 + 6] = 0;
	base_address[0x3818 + 7] = 0;

	
	//; Enabled, Pad Short Packets, 15 retries, 64-byte COLD, Re-transmit on Late Collision
	//; Transmit Control Register	
	//0x 01 04 00 FA;
	base_address[0x0400 + 0] = 0xfa;
	base_address[0x0400 + 1] = 0;
	base_address[0x0400 + 2] = 0x04;
	base_address[0x0400 + 3] = 0x01;
	
	//; IPGT 10, IPGR1 8, IPGR2 6
	//; Transmit IPG Register
	//; Transmit Inter Packet Gap
	//0x0060200A	0x0410
	//0x 00 60 20 0A;
	base_address[0x0410 + 0] = 0x0A;
	base_address[0x0410 + 1] = 0x20;
	base_address[0x0410 + 2] = 0x60;
	base_address[0x0410 + 3] = 0;
	
	//; Clear the Receive Delay Timer Register 0x2820 RX Delay Timer Register
	// Clear the Receive Interrupt Absolute Delay Timer 0x282C RX Int. Absolute Delay Timer
	// Clear the Receive Small Packet Detect Interrupt 0x2C00  RX Small Packet Detect Interrupt
	
	//0;
    base_address[0x2820 + 0] = 0;
	base_address[0x2820 + 1] = 0;
	base_address[0x2820 + 2] = 0;
	base_address[0x2820 + 3] = 0;

	//0; 
	base_address[0x282C + 0] = 0;
	base_address[0x282C + 1] = 0;
	base_address[0x282C + 2] = 0;
	base_address[0x282C + 3] = 0;
	
	
	//0; 
	base_address[0x2C00 + 0] = 0;
	base_address[0x2C00 + 1] = 0;
	base_address[0x2C00 + 2] = 0;
	base_address[0x2C00 + 3] = 0;
	
	//#bugbug: essa parte pode ser complicada.
	//; Temp enable all interrupt types
	//; Enable interrupt types
	//Interrupt Mask Set/Read Register
	//base_address32[0x00D0] =  0x1F6DC ; // enable all interrupts (and clear existing pending ones)
	//0x 0 1 FF FF; 
	base_address[0x00D0 + 0] = 0xFF; 
	base_address[0x00D0 + 1] = 0xFF;
	base_address[0x00D0 + 2] = 0x01;
	base_address[0x00D0 + 3] = 0;
	
	printf("nic_i8254x_reset: Done\n");
	//refresh_screen();
};



// transmit:
// temos que configurar os campos referentes a transmissão.
// base address, lenght, head, tail
void nic_i8254x_transmit(){
	
	printf("nic_i8254x_transmit: Transmitting ... \n");

	//#todo: precisamos checar a validade dessa estrutura e do endereço.
	
	//endereço base.
	unsigned char *base_address = (unsigned char *) currentNIC->registers_base_address;
	unsigned long *base_address32 = (unsigned long *) currentNIC->registers_base_address;	
	
	//
	// ## Configurando o ring de transmissão ##
	//
	
	
	//o endereço base aponta para o início do array de descritores.
	//depois lenght, head, tail.
	
	//o endereço indica o início do ring
	
	//antes, na hora da inicialização, temos que criar o array de descritores ...
	//o endereço base desse array será usado aqui. 
	//#importante: ; Transmit Descriptor Base Address. Me parece que pode ser um 
	//endereço virtual normal.
	//já cada descritor terá um endereço físico para um buffer.
	
	
	//base address. 
	//intel_transmission_ring_base_address
	
	// TDBAL
	//0x80000;
	base_address[0x3800 + 0] = 0;     //low
	base_address[0x3800 + 1] = 0;
	base_address[0x3800 + 2] = 0x80;
	base_address[0x3800 + 3] = 0;
    base_address[0x3800 + 4] = 0;     //high
    base_address[0x3800 + 5] = 0;
    base_address[0x3800 + 6] = 0;
    base_address[0x3800 + 7] = 0;	
	
	// TDH - Transmit Descriptor Head
	//0;
	base_address[0x3810 + 0] = 0;
	base_address[0x3810 + 1] = 0;
	base_address[0x3810 + 2] = 0;
	base_address[0x3810 + 3] = 0;
	base_address[0x3810 + 4] = 0;
	base_address[0x3810 + 5] = 0;
	base_address[0x3810 + 6] = 0;
	base_address[0x3810 + 7] = 0;	
	
	// TDL - Transmit Descriptor Tail
    //1;
	base_address[0x3818 + 0] = 1;
	base_address[0x3818 + 1] = 0;
	base_address[0x3818 + 2] = 0;
	base_address[0x3818 + 3] = 0;
	base_address[0x3818 + 4] = 0;
	base_address[0x3818 + 5] = 0;
	base_address[0x3818 + 6] = 0;
	base_address[0x3818 + 7] = 0;	
	
	
	printf("nic_i8254x_transmit: Done\n");
	//refresh_screen();
};



/*
### exemplo
Hirochika Asai  <asai@jar.jp>

static __inline__ volatile u32
mmio_read32(u64 base, u64 offset)
{
    return *(volatile u32 *)(base + offset);
}

static __inline__ void
mmio_write32(u64 base, u64 offset, volatile u32 value)
{
    *(volatile u32 *)(base + offset) = value;
}
*/


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
		
		
/* 
    #todo: Device Status 
	
#define E1000_STATUS_FD         0x00000001	// Full duplex.0=half,1=full 
#define E1000_STATUS_LU         0x00000002	// Link up.0=no,1=link 
#define E1000_STATUS_FUNC_MASK  0x0000000C	// PCI Function Mask 
#define E1000_STATUS_FUNC_SHIFT 2
#define E1000_STATUS_FUNC_0     0x00000000	// Function 0 
#define E1000_STATUS_FUNC_1     0x00000004	// Function 1 
#define E1000_STATUS_TXOFF      0x00000010	// transmission paused 
#define E1000_STATUS_TBIMODE    0x00000020	// TBI mode 
#define E1000_STATUS_SPEED_MASK 0x000000C0
#define E1000_STATUS_SPEED_10   0x00000000	//Speed 10Mb/s 
#define E1000_STATUS_SPEED_100  0x00000040	// Speed 100Mb/s 
#define E1000_STATUS_SPEED_1000 0x00000080	// Speed 1000Mb/s 
#define E1000_STATUS_LAN_INIT_DONE 0x00000200	// Lan Init Completion  by EEPROM/Flash 
#define E1000_STATUS_ASDV       0x00000300	// Auto speed detect value 
#define E1000_STATUS_DOCK_CI    0x00000800	// Change in Dock/Undock state. Clear on write '0'. 
#define E1000_STATUS_GIO_MASTER_ENABLE 0x00080000	// Status of Master requests. 
#define E1000_STATUS_MTXCKOK    0x00000400	// MTX clock running OK 
#define E1000_STATUS_PCI66      0x00000800	// In 66Mhz slot 
#define E1000_STATUS_BUS64      0x00001000	// In 64 bit slot 
#define E1000_STATUS_PCIX_MODE  0x00002000	// PCI-X mode 
#define E1000_STATUS_PCIX_SPEED 0x0000C000	// PCI-X bus speed 
#define E1000_STATUS_BMC_SKU_0  0x00100000	// BMC USB redirect disabled 
#define E1000_STATUS_BMC_SKU_1  0x00200000	// BMC SRAM disabled 
#define E1000_STATUS_BMC_SKU_2  0x00400000	// BMC SDRAM disabled 
#define E1000_STATUS_BMC_CRYPTO 0x00800000	// BMC crypto disabled 
#define E1000_STATUS_BMC_LITE   0x01000000	// BMC external code execution disabled 
#define E1000_STATUS_RGMII_ENABLE 0x02000000	// RGMII disabled 
#define E1000_STATUS_FUSE_8       0x04000000
#define E1000_STATUS_FUSE_9       0x08000000
#define E1000_STATUS_SERDES0_DIS  0x10000000	// SERDES disabled on port 0 
#define E1000_STATUS_SERDES1_DIS  0x20000000	// SERDES disabled on port 1 

// Constants used to interpret the masked PCI-X bus speed. 
#define E1000_STATUS_PCIX_SPEED_66  0x00000000	// PCI-X bus speed  50-66 MHz 
#define E1000_STATUS_PCIX_SPEED_100 0x00004000	// PCI-X bus speed  66-100 MHz 
#define E1000_STATUS_PCIX_SPEED_133 0x00008000	// PCI-X bus speed 100-133 MHz 

*/		
		
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
		    currentNIC->mac0, currentNIC->mac1, currentNIC->mac2,
            currentNIC->mac3, currentNIC->mac4, currentNIC->mac5 );
		
		//...
		
	};	    
	
};

    //## BUGBUG ##		
    //fail: travando no loop
unsigned short e1000_eeprom_read_8254x (unsigned long mmio, unsigned char addr)
{
    unsigned long data;
	
	unsigned char *base = (unsigned char *) mmio;

	//#todo:
	
	return (unsigned short) 0;
};

/*
u16
e1000_eeprom_read(u64 mmio, u8 addr)
{
    u16 data;
    u32 tmp;

    // Start 
    *(u32 *)(mmio + E1000_REG_EERD) = ((u32)addr << 2) | 1;

    // Until it's done 
    while ( !((tmp = *(u32 *)(mmio + E1000_REG_EERD)) & (1<<1)) ) {
        pause();
    }
    data = (u16)((tmp >> 16) & 0xffff);

    return data;
}
*/




/*
int nicInit()
{};
*/

//
// End.
//


