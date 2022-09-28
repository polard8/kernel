//socket.c 

// @todo:
// +registrar o soquete criado em uma lista para o processo
// manipular o descritor.
// +função para deletar um soquete.
// ...


#include <kernel.h>


//cria um socket
//retorna o ponteiro para a estrutura.

struct socket_d *create_socket ( unsigned long ip, unsigned short port )
{	
	struct socket_d *s;
	
	//@todo
	
	s = (void *) malloc ( sizeof( struct socket_d ) );
	
	if ( (void *) s ==  NULL )
	{
		printf ( "create_socket: allocation fail \n");
		return NULL;
		
	}else{
		
		s->ip_long = ip;
		
		s->port = port;
	};
	
    return (struct socket_d *) s;	
};



unsigned long getSocketIP ( struct socket_d *socket )
{
    if ( (void *) socket ==  NULL )
	{
		return 0;
	}else{
		
	    return (unsigned long) socket->ip_long;	
	};
};



unsigned long getSocketPort ( struct socket_d *socket )
{
    if ( (void *) socket ==  NULL )
	{
		return 0;
	}else{
		
	    return (unsigned long) socket->port;	
	};
};



int update_socket ( struct socket_d *socket, unsigned long ip, unsigned short port )
{
	
    if ( (void *) socket ==  NULL )
	{
		return 1; //fail
	}else{
		
		socket->ip_long = (unsigned long) ip;
		
		socket->port = (unsigned short) port;
		
		return 0; //ok
	};
};








