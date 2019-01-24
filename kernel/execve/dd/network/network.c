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



//manipular o pacote ipv6 recebido pelo handle do e1000.
int handle_ipv6 ( struct nic_info_d *nic, struct ipv6_header_d *header ){

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


//chamada por F6 no procedimento de janela do sistema.
void testNIC()
{
	printf("testNIC: setup flag and test send arp request \n");
    //init_nic ();
    //e1000_setup_irq();
	//e1000_reset_controller(); 
	
	//testando apens o send 
	
	e1000_interrupt_flag = 1;
	
	testSend();	
	
	
	//se tivermos informações para mostrar é sinal que a inicialização do kernel 
	//funcionou. 
	
	//show_current_nic_info ();
	
	printf("testNIC: Done\n");
}

//
// End
//


