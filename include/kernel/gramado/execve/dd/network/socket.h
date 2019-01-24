/*
 * File: socket.h
 *
 * Descrição:
 *     Header para gerenciamento de sockets.
 *
 *    "Um soquete é composto por um endereço de ip,
 *     concatenado com um número de porta, ip_addres:port"
 *
 * History:
 *     2016 -  Created by Fred Nora.
 */


int current_socket;


/*
 * socket_d:
 *     Socket strutuct.
 */

struct socket_d
{
	object_type_t objectType;
	object_class_t objectClass;
	
	
	unsigned long ip_long;
	
	//unsigned char ip[4];
	unsigned short port;	
	
	//podemos fazer mais coisa aqui.
	//...
};
struct socket_d *CurrentSocket;
struct socket_d *LocalHostHTTPSocket;
//...


//@todo: refazer esse limite proviório
#define SOCKET_COUNT_MAX 32

unsigned long socketList[SOCKET_COUNT_MAX];



struct socket_d *create_socket ( unsigned long ip, unsigned short port );

unsigned long getSocketIP ( struct socket_d *socket );
unsigned long getSocketPort ( struct socket_d *socket );
int update_socket ( struct socket_d *socket, unsigned long ip, unsigned short port );


//
// End.
//

