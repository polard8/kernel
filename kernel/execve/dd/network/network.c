/*
 * File: dd/network/network.c
 *     
 *     Network sopport.
 *
 * History:
 *     2016 - Created by Fred Nora.
 */


/*
 @todo:
 Network packet
 Network topology
 Network links
 Network nodes
 Network interfaces
 Repeaters and hubs
 Bridges
 Switches
 Routers
 Firewalls
 Common layouts
 Overlay network
 Communications protocols
 IEEE 802
 Ethernet
 Wireless LAN
 Internet Protocol Suite
 Asynchronous Transfer Mode
 Personal area network
 Local area network
 Home area network
 Storage area network
 Backbone network
 Wide area network
 Enterprise private network
 Virtual private network
 Intranet
 Extranet
 Internetwork
 Internet
 Darknet
 Routing
 Network service *
 service protocol
 Network security
*/



#include <kernel.h>


//0 - uninitialized
//1 - initialized

int network_status;

 
void networkSetstatus (int status){

	if ( status < 0 || status > 1 )
		return;
	
	network_status = (int) status;
}


int networkGetStatus (){

	return (int) network_status;
}
 
 
/*
 **********************************************************
 * networkInit:
 *     Inicializa todos os recursos de rede, inclusive os drivers dos 
 * adaptadores de rede.
 *
 * #todo:
 *     Quanto aos adaptadores, poderíamos iniciá-los formorme forem encontrados 
 * sondando a interface pci.
 */ 

int networkInit (){
	
	// Status
	
	//zera status.
	networkSetstatus (0);
	
	
	// Host info struct
	// host.h
	
	HostInfo = (struct host_info_d *) malloc ( sizeof( struct host_info_d ) ); 

	if ( (void *) HostInfo == NULL )
	{
		printf ("networkInit: HostInfo");
		die();
	
	}else{
		
		//#todo object header
		
		HostInfo->used = 1;
		HostInfo->magic = 1234;
		
		HostInfo->hostName = NULL;
		HostInfo->hostVersion = NULL;
		
	    HostInfo->hostVersionMajor = 0;
	    HostInfo->hostVersionMinor = 0; 
	    HostInfo->hostVersionRevision = 0;
        HostInfo->hostArchitecture = 0; 		
		
		//...
		
	};		
	
	//criando socket para local host porta 80
	
	// Localhost (127.0.0.1):80 
	LocalHostHTTPSocket = (struct socket_d *) create_socket ( 0, 0 );  
	
	CurrentSocket = (struct socket_d *) LocalHostHTTPSocket;
	//...
	

	//
	// Status
	//
	
	//ok
	//todos os componentes da rede estão inicializados.
	
	//Obs: #todo: Só acionaremos essa flag quando realmente tudo estiver 
	//inicializado.
	
	//networkSetstatus (1);
	
	return (int) 0;
};


void show_network_info (){
	
	printf("show_network_info:\n");
	
	if ( network_status == 1 )
	    printf ("Network initialized\n");

	if ( network_status == 0 )
	    printf ("Network uninitialized\n");
	
	
	if ( (void *) HostInfo == NULL )
	{
		printf ("show_network_info: HostInfo");
		return;	
	}else{

	    //#todo: 
	    printf("Host name %s\n ", HostInfo->hostName );
	    printf("IP %s \n ", HostInfo->hostIP );
	    printf("MAC %s \n ", HostInfo->hostMAC );	
	    //...
	};
	

	//nic
	show_current_nic_info ();
	
};



void show_current_nic_info (){
	
	
	printf("show_current_nic_info:\n");

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

	//refresh_screen();
}



//manipular o pacote ipv6 recebido pelo handle do e1000.
int handle_ipv6 ( struct intel_nic_info_d *nic, struct ipv6_header_d *header ){

    //printf("\n");
    //printf("handle_ipv6: Initializing ...\n");

    if ( (void *) nic == NULL )
	{
		printf("handle_ipv6: nic fail\n");
		return -1;
	}
	
    if ( (void *) header == NULL )
	{
		printf("handle_ipv6: header fail\n");
		return -2;
	}else{
		
		//printf("ver_tc_label=%x len=%d next_header=%x hop_limit=%d \n",
		//    header->ver_tc_label,
        //    header->len,
        //    header->next_header,
        //    header->hop_limit );

		//32bit
		//printf("ver=%d ", header->ver_tc_label & 0xF0000000 );
		//printf("tc=%d ", header->ver_tc_label  & 0x0FF00000 );
		//printf("label=%d ", header->ver_tc_label  & 0x000FFFFF );
	    
		//16bit
		//printf("len=%d ", header->len  & 0xFFFF );
		
		//8bit
		//printf("next=%d ", header->next_header & 0xFF );

		//8bit
		//printf("hop_limit=%d \n", header->hop_limit & 0xFF );
		
		//...
		
		return 0;
	};
	
	
    return 1;	
};

//#IMPORTANTE
//chamada por F6 no procedimento de janela do sistema.
void testNIC()
{
	
	//printf("\n\ntestNIC:\n\n"); 
	
	printf("testNIC: Setup flag \n");
	printf("testNIC: Sending arp request \n");

	printf ("\n\n #debug: e1000_irq_count=%d \n\n",e1000_irq_count);
	
		
	//testando apens o send 
	
	e1000_interrupt_flag = 1;	
	
	
	
	uint8_t source_ip_address[4];
	source_ip_address[0] = 192;
	source_ip_address[1] = 168;
	source_ip_address[2] = 1;   
	source_ip_address[3] = 112; 

	uint8_t target_ip_address[4];
	target_ip_address[0] = 192;
	target_ip_address[1] = 168;
	target_ip_address[2] = 1;     
	target_ip_address[3] = 111;   
	
	uint8_t target_mac_address[6];
	target_mac_address[0] = 0xFF;
	target_mac_address[1] = 0xFF;
	target_mac_address[2] = 0xFF;
	target_mac_address[3] = 0xFF;
	target_mac_address[4] = 0xFF;
	target_mac_address[5] = 0xFF;		
	
	//tests
	
	//mudar network.
	//tem que ter uma abstração que selecione o nic atual
	SendARP ( source_ip_address, target_ip_address, target_mac_address );
	

	//==============================================
	// ## data ##
	//		
                
	char xxxdata[32];			       	
    xxxdata[0] = 1;
	xxxdata[1] = 2;
	xxxdata[2] = 3;
	xxxdata[3] = 4;	
	
	//#todo: testar isso;
	SendIPV4 ( source_ip_address, target_ip_address, target_mac_address, xxxdata );
	
	//se tivermos informações para mostrar é sinal que a inicialização do kernel 
	//funcionou. 
	
	//printf("\n\n");
	//show_current_nic_info ();
	
	//printf("\n\n");
	//pciInfo ();
	
	printf("testNIC: Done\n");
	refresh_screen();
}


void SendIPV4 ( uint8_t source_ip[4], uint8_t target_ip[4], uint8_t target_mac[6], uint8_t data[32] ){
	
	
	int i=0;
	
	struct ether_header *eh;
	struct  ether_arp *h;
	struct ipv4_header_d *ipv4;
	struct udp_header_d *udp;
	
	if ( currentNIC == NULL )
	{
		printf ("SendIPV4: currentNIC\n");
		return;		
	}
	
	//configurando a estrutura do dispositivo,

	currentNIC->ip_address[0] = source_ip[0];  //192;
	currentNIC->ip_address[1] = source_ip[1];  //168;
	currentNIC->ip_address[2] = source_ip[2];  //1;    	
	currentNIC->ip_address[3] = source_ip[3];  //112;  	
	
	
	//
	// ====================== ## ETH HEADER ## ====================
	//
	
	eh = (void *) malloc ( sizeof(struct ether_header ) );
	
	if ( (void*) eh == NULL)
	{
		printf("struct eh fail");
		die();
	}
	
	for( i=0; i<6; i++)
	{
		eh->src[i] = currentNIC->mac_address[i];    //source ok
		eh->dst[i] = target_mac[i];                 //dest. (broadcast)	
	}	
	
	eh->type = (uint16_t) ToNetByteOrder16(ETH_TYPE_ARP);
	
	
	
    //==============================================
	// ## ipv4 ##
	//
	
	ipv4 = (void *) malloc ( sizeof(struct ipv4_header_d) );
	
	if ( (void *) ipv4 == NULL)
	{
		printf(": ipv4 fail");
		die();
	}else{

        // IPv4 common header
	    ipv4->Version_IHL = 0x45;
	    ipv4->DSCP_ECN = 0x00;
	    ipv4->Identification = 0x0100; 
	    ipv4->Flags_FragmentOffset = 0x0000;
	    ipv4->TimeToLive = 0x40;
	    
		//default protocol: UDP
 	    //#define IPV4_PROT_UDP 0x11
		ipv4->Protocol = 0x11; //IPV4_PROT_UDP;
 	    
		memcpy ( (void*) &ipv4->SourceIPAddress[0],      (const void *) &source_ip[0], 4);
	    memcpy ( (void*) &ipv4->DestinationIPAddress[0], (const void *) &target_ip[0], 4);    	
	};


	//==============================================
	// ## udp ##
	//
	
	udp = (void *) malloc ( sizeof(struct udp_header_d) );
	
	if( (void *) udp == NULL)
	{
		printf(": udp fail");
		die();
	}else{
    
	    udp->SourcePort = 0;   
        udp->DestinationPort = 0;
        udp->Length = 0;
        udp->Checksum = 0; 		
    }
	
	
	
	
	// ## quem ? ##
	uint16_t old = currentNIC->tx_cur;
	

	// ## Copiando o pacote no buffer ##
	
	//pegando o endereço virtual do buffer na estrutura do dispositivo.	
	unsigned char *buffer = (unsigned char *) currentNIC->tx_descs_virt[old];	
		
	unsigned char *src_ethernet = (unsigned char *) eh; 
	unsigned char *src_ipv4 = (unsigned char *) ipv4; 
	unsigned char *src_udp = (unsigned char *) udp; 
	
	
	int j=0;
	
        //copia o header ethernet
		for ( j=0; j<ETHERNET_HEADER_LENGHT; j++ )
		{
			buffer[j] = src_ethernet[j];
		}
		
		//copia o ipv4
		for ( j=0; j<IPV4_HEADER_LENGHT; j++ )
		{
			buffer[j + ETHERNET_HEADER_LENGHT] = src_ipv4[j];
		}

		//copia o udp
		for ( j=0; j<UDP_HEADER_LENGHT; j++ )
		{
			buffer[j + ETHERNET_HEADER_LENGHT +IPV4_HEADER_LENGHT] = src_udp[j];
		}
		
		//copia o xxxdata
		for ( j=0; j<32; j++ )
		{
			buffer[j + ETHERNET_HEADER_LENGHT +IPV4_HEADER_LENGHT + UDP_HEADER_LENGHT] = data[j];
		}		
	
	
	
	//len;
	currentNIC->legacy_tx_descs[old].length = (ETHERNET_HEADER_LENGHT + IPV4_HEADER_LENGHT + UDP_HEADER_LENGHT + 32);		
	
	
	currentNIC->legacy_tx_descs[old].cmd = 0x1B;
	currentNIC->legacy_tx_descs[old].status = 0;	
	
	currentNIC->tx_cur = ( currentNIC->tx_cur + 1 ) % 8;
	
	
	*( (volatile unsigned int *)(currentNIC->mem_base + 0x3818)) = currentNIC->tx_cur;	
	
	
	//#debug
	printf("sending ipv4 (while)\n");
	refresh_screen();	
	
	//checamos o status do old pra ver se ele foi enviado.
	//fica travado aqui até que seja envidao.
	//poderia ter um timemout??.
	while ( !(currentNIC->legacy_tx_descs[old].status & 0xFF) )
	{
		//nothing
	}
	
}
	
	
void SendARP ( uint8_t source_ip[4], uint8_t target_ip[4], uint8_t target_mac[6] ){
	
	int i=0;
	struct ether_header *eh;
	struct  ether_arp *h;
	
	
	if ( currentNIC == NULL )
	{
		printf ("SendARP: currentNIC\n");
		return;		
	}

	
	//configurando a estrutura do dispositivo,

	currentNIC->ip_address[0] = source_ip[0];  //192;
	currentNIC->ip_address[1] = source_ip[1];  //168;
	currentNIC->ip_address[2] = source_ip[2];  //1;    	
	currentNIC->ip_address[3] = source_ip[3];  //112;  			

	//
	// ====================== ## ETH HEADER ## ====================
	//
	
	eh = (void *) malloc ( sizeof(struct ether_header ) );
	
	if ( (void*) eh == NULL)
	{
		printf("struct eh fail");
		die();
	}
	
	for( i=0; i<6; i++)
	{
		eh->src[i] = currentNIC->mac_address[i];    //source ok
		eh->dst[i] = target_mac[i];                 //dest. (broadcast)	
	}	
	
	eh->type = (uint16_t) ToNetByteOrder16(ETH_TYPE_ARP);

    
	
	//==================================
	//#debug
	//show ethernet header
	/*
	printf("\n\n");
	printf("[ethernet header]\n\n");
	
	printf("src: ");
    for( i=0; i<6; i++)
		printf("%x ",eh->src[i]);
	
	printf("dst: ");
    for( i=0; i<6; i++)
		printf("%x ",eh->dst[i]);
	
	printf("type={%x} ",eh->type);
	*/
	//==================================
	
	
	//#debug
	//printf("debug *hang");
	//refresh_screen();
	//while(1){}
	
	//
	// ==================== ## ARP ## ==========================
	//

	h = (void *) malloc ( sizeof(struct  ether_arp) );
	
	if ( (void*) h == NULL)
	{
		printf("struct h fail");
		die();
	}
	
    //Hardware type (HTYPE)
	h->type = 0x0100; // (00 01)
	
	//Protocol type (PTYPE)
	h->proto = 0x0008;  //(08 00)    
	
	//Hardware address length (MAC)
	h->hlen = 6;
	
	////Protocol address length (IP)
	h->plen = 4;
	
	
	//Operation (OPER) (dois bytes invertidos)
	//h->op = ToNetByteOrder16(ARP_OPC_REPLY);  	
    h->op = ToNetByteOrder16(ARP_OPC_REQUEST);
	
	//mac
	for( i=0; i<6; i++)
	{
		h->arp_sha[i] = currentNIC->mac_address[i];  //sender mac
		h->arp_tha[i] = target_mac[i];               //target mac
	}	
	
	//ip
	for ( i=0; i<4; i++)
	{
		h->arp_spa[i] = source_ip[i];    //sender ip
		h->arp_tpa[i] = target_ip[i];    //target ip
	}		
	
	//==================================
	//#debug
    //show arp
	/*
	printf("\n\n");
	printf("[arp]\n\n");
	printf("type={%x} proto={%x} hlen={%d} plen={%d} op={%x} \n", 
	    h->type ,h->proto ,h->hlen ,h->plen ,h->op);
	
	printf("\n sender: mac ");
	for( i=0; i<6; i++){
	    printf("%x ",h->arp_sha[i]);	
	}
	printf("\n sender: ip ");
	for( i=0; i<4; i++){
	    printf("%d ",h->arp_spa[i]);	
	}
	printf("\n target: mac ");
	for( i=0; i<6; i++){
	    printf("%x ",h->arp_tha[i]);	
	}
	printf("\n target: ip ");
	for( i=0; i<4; i++){
	    printf("%d ",h->arp_tpa[i]);	
	}
	*/
	//==================================
	
	
	//#debug
	//printf("\n debug *hang");
	//refresh_screen();
	//while(1){}	
	
  	

	// ## quem ? ##
	uint16_t old = currentNIC->tx_cur;
	

	// ## Copiando o pacote no buffer ##
	
	//pegando o endereço virtual do buffer na estrutura do dispositivo.	
	unsigned char *buffer = (unsigned char *) currentNIC->tx_descs_virt[old];
	
	unsigned char *src_ethernet = (unsigned char *) eh; 
	unsigned char *src_arp      = (unsigned char *) h;
	
	//copiando o header ethernet
	//copiando o arp logo após do header ethernet
	
	for(i=0; i<14;i++){
		buffer[i] = src_ethernet[i];
	}

	for(i=0; i<28;i++){
		buffer[i + 14] = src_arp[i];
	}
	

    // Ethernet frame length = ethernet header (MAC + MAC + ethernet type) + ethernet data (ARP header)
	//O comprimento deve ser o tamanho do header etherne + o tamanho do arp.
	
	//len;
	currentNIC->legacy_tx_descs[old].length = (ETHERNET_HEADER_LENGHT + ARP_HEADER_LENGHT);	
	//currentNIC->legacy_tx_descs[old].length = 14 + 28;
	
	//??
	//currentNIC->legacy_tx_descs[0].cso
	
	//cmd ok
	//currentNIC->legacy_tx_descs[0].cmd = TDESC_CMD_IFCS | TDESC_CMD_RS | TDESC_CMD_EOP;
	//currentNIC->legacy_tx_descs[0].cmd = TDESC_EOP | TDESC_RS; //intel code
	
	currentNIC->legacy_tx_descs[old].cmd = 0x1B;
	currentNIC->legacy_tx_descs[old].status = 0;	
	
	currentNIC->tx_cur = ( currentNIC->tx_cur + 1 ) % 8;
	
	//??
	//currentNIC->legacy_tx_descs[0].css
	
	//??
	//currentNIC->legacy_tx_descs[0].special
	
	
	//
	// ## SHOW INFO ##
	//
	
	//#importante #todo
	
	//device info
	//isso pode ficar pra depois.
    	
	//ethernet header 
	
	//arp header
	
	//
	// ## SEND ##
	//

	
	//#importante 
	//diga ao controlador qual é o índice do descritor a ser usado para  
	//transmitir dados.,
	
	//current
	//TDH	= 0x3810,	/* Tx Descriptor Head */
	//*( (volatile unsigned int *)(currentNIC->mem_base + 0x3810)) = 0;
	//TDT	= 0x3818,	/* Tx Descriptor Tail */
	*( (volatile unsigned int *)(currentNIC->mem_base + 0x3818)) = currentNIC->tx_cur;	

	//#debug
	printf("sending broadcast arp(while)\n");
	refresh_screen();	
	
	//checamos o status do old pra ver se ele foi enviado.
	//fica travado aqui até que seja envidao.
	//poderia ter um timemout??.
	while ( !(currentNIC->legacy_tx_descs[old].status & 0xFF) )
	{
		//nothing
	}
}



//
// End
//


