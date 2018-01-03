/*
 * File: network.c
 *
 * Descrição:
 *     Parte principal do módulo executive/network.
 *
 * Versão: 1.0, 2016 - Created.
 */



#include <kernel.h>


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

int networkTesting;

 

int networkInit()
{
	//criando socket para local host porta 80
	
	LocalHostHTTPSocket = (struct socket_d *) create_socket( 0x0100007F, 80 );  /* Localhost (127.0.0.1):80 */
	CurrentSocket = (struct socket_d *) LocalHostHTTPSocket;
	//...
	
	return 0;
}
 


//
// Fim
//


