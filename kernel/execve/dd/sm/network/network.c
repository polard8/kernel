/*
 * File: network.c
 *
 * Descrição:
 *     Parte principal do módulo sm/network.
 *
 * 2016 - Created by Fred Nora.
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
};	


int networkGetStatus (){
    
	return (int) network_status;	
};
 
 
 
/*
 **********************************************************
 * networkInit:
 *     Inicializa todos os recursos de rede, inclusive 
 * os drivers dos adaptadores de rede.
 *
 */ 
int networkInit (){
	
	//
	// Status
	//
	
	//zera status.
	networkSetstatus (0);
	
	
	//
	// Host info struct
	//
	
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
	


	//
	// NIC
	//
	
    init_nic ();

	
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
	    printf("Host name {%s}\n ", HostInfo->hostName );
	    printf("IP {%s}\n        ", HostInfo->hostIP );
	    printf("MAC {%s}\n       ", HostInfo->hostMAC );	
	    //...
	};
	

	
	//nic
	show_current_nic_info ();
	
};

//
// End
//


