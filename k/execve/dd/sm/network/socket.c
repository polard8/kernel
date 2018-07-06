
#include <kernel.h>

//socket.c 


//cria um socket
struct socket_d *create_socket( unsigned long ip, unsigned short port )
{
	//@todo
	
	struct socket_d *s;
	
	s = (void *) malloc( sizeof( struct socket_d ) );
	
	if( (void*) s ==  NULL ){
		return NULL;
	}else{
		
		s->ip_address = ip;
		s->port = port;
	};
	
    return (struct socket_d *) s;	
}


