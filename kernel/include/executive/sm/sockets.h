/*
 * Arquivo: sockets.h
 *
 * Descrição:
 *     Header para gerenciamento de sockets.
 *
 *    "Um soquete é composto por um endereço de ip,
 *     concatenado com um número de porta, ip_addres:port"
 *
 * Versão 1.0, 2016.
 */


/*
 * struct sockets_d:
 *     ex: 192.168.1.1:80
 */
typedef struct sockets_d sockets_t;
struct sockets_d
{
	object_type_t objectType;
	object_class_t objectClass;
	
	unsigned long ip_address;
    short port;	
	
	//struct ip_address_d *ip_address;    //@todo: deletar.
};
sockets_t *CurrentSocket;



//unsigned long socketList[16];


//
//fim.
//

