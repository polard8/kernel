//isso pertence ao shell,
//mas pode muito bem virar uma lib.

#include "sh.h"




//solicitando operações genéricas que podem ser feitas
//atenção: estamos pasando um ponteiro de estrutura par ao kernel
//então o kernel tem que ter uma estrutura igual a nossa.
int netStream ( FILE *stream, int option )
{
    return (int) system_call ( 164, (unsigned long) stream, option, option );	
};

//solicitando operações genéricas que podem ser feitas
//atenção: estamos pasando um ponteiro de estrutura par ao kernel
//então o kernel tem que ter uma estrutura igual a nossa.
int netSocket ( struct socket_d *socket, int option )
{
    return (int) system_call ( 164, (unsigned long) socket, option, option );	
};


int netBuffer ( unsigned long buffer_address, int option )
{
    return (int) system_call ( 166, buffer_address, option, option );	
};


//rotina de testes de socket
void shellSocketTest()
{
	//#todo: isso precisa ser um porteiro de estrutura.
	void *socketHandle;
	
	//lembre-se: NÃO podemos acessr a estrura do kernel.
	//se ele configurar a nossa, está tudo bem.
	//pra isso temos que passar o endereço dela.
	//struct socket_d *socket;
	
	unsigned long iplong;
	unsigned long port; //short
	
	unsigned char ip[4];
	
    printf("\n");
    printf("shellSocketTest: Testing socket stuff ...\n");

	
	//
	// Creating socket
	//
	
	printf("Creating socket ...\n");
	socketHandle = (void *) system_call ( 160, (unsigned long) 0xC0A80164, (unsigned long) 0, (unsigned long) 0x22C3 );
	
	printf("Updating socket ...\n");
	system_call ( 163, (unsigned long) socketHandle, (unsigned long) 0xC0A80165, (unsigned long) 0x22C2 );
	
	printf("Getting ip from socket ...\n");
	iplong = (unsigned long) system_call ( 161, (unsigned long) socketHandle, (unsigned long) socketHandle, (unsigned long) socketHandle);
	
	printf("Getting port from socket ...\n");
	port = (unsigned long) system_call ( 162, (unsigned long) socketHandle, (unsigned long) socketHandle, (unsigned long) socketHandle);
	
	//
	// output
	//
	unsigned long tmp;
	
	tmp = iplong;
	ip[3] = (char) ( tmp & 0x000000FF ); 
	
	tmp = iplong;
	tmp = (tmp >> 8);
	ip[2] = (char) ( tmp & 0x000000FF );
	
	tmp = iplong;
	tmp = (tmp >> 16);
	ip[1] = (char) ( tmp & 0x000000FF );
	
	tmp = iplong;
	tmp = (tmp >> 24);
	ip[0] = (char) ( tmp & 0x000000FF );
	
	printf("\n");
	//printf("iplong=%x\n",iplong);
	printf ("Socket: ( %d.%d.%d.%d:%d )\n", 
		ip[0], ip[1], ip[2], ip[3], port );
	
	printf("done\n");
};



