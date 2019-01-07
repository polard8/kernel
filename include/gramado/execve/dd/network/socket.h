/*
 * File: sockets.h
 *
 * Descrição:
 *     Header para gerenciamento de sockets.
 *
 *    "Um soquete é composto por um endereço de ip,
 *     concatenado com um número de porta, ip_addres:port"
 *
 * Versão 1.0, 2016.
 */

int current_socket;

/*
 * struct socket_d:
 *     ex: 192.168.1.1:80
 *         127.0.0.1:80  
 */
struct socket_d
{
	object_type_t objectType;
	object_class_t objectClass;
	
	unsigned long ip_long;
	unsigned short port;	
	
	//podemos fazer mais coisa aqui.
	//...
};
struct socket_d*CurrentSocket;
struct socket_d*LocalHostHTTPSocket;
//...


#define SOCKET_COUNT_MAX 32
//@todo: refazer esse limite proviório
unsigned long socketList[SOCKET_COUNT_MAX];




struct socket_d *create_socket( unsigned long ip, unsigned short port );

unsigned long getSocketIP ( struct socket_d *socket );
unsigned long getSocketPort ( struct socket_d *socket );
int update_socket ( struct socket_d *socket, unsigned long ip, unsigned short port );

//
//fim.
//

