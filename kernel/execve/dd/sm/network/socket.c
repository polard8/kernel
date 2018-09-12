//socket.c 

// @todo:
// +registrar o soquete criado em uma lista para o processo
// manipular o descritor.
// +função para deletar um soquete.
// ...


#include <kernel.h>


//cria um socket

struct socket_d *create_socket ( unsigned long ip, unsigned short port )
{	
	struct socket_d *s;
	
	//@todo
	
	s = (void *) malloc ( sizeof( struct socket_d ) );
	
	if ( (void *) s ==  NULL )
	{
		//printf("create_socket: allocation fail");
		return NULL;
		
	}else{
		
		s->ip_address = ip;
		
		s->port = port;
	};
	
    return (struct socket_d *) s;	
};


