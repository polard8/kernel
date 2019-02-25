

// socket.c
// suporte a socket da klibc.


#include <kernel.h>


int socket ( int family, int type, int protocol ){
	
	//#todo:
	//vai retornar o descritor de uma stream.
	
	printf ("klibc: socket: #todo:\n");
    return -1;	
}


// Essa rotina sera' chamada se os serviços forem superios a 7000 ou inferiores a 8000
unsigned long socket_services ( unsigned long number, unsigned long arg2, unsigned long arg3, unsigned long arg4 )
{
	
	printf ("klibc:  socket_services: number=%d \n", number);
	
	if ( number < 7000 || number >= 8000 )
		return 0;
	
	// nu'mero do serviço.
	switch (number)
	{
		//socket(...)	
		//family, type, protocol
		//vai retornar o descritor de uma stream.	
		case 7000:
			return (unsigned long) socket ( (int) arg2, (int) arg3, (int) arg4 );
			break;
			
		//send	
		//case 7001:
		//	return (unsigned long) 1; 
		//	break;
			
		//...
			
	    default:
			printf ("klibc: socket_services: Default\n");
			break;
	}
	
    return 1;
}


