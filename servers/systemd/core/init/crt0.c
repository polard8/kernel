/*
 * \o/
 * Gramado Operating System - The main file for the shell.
 * (c) Copyright 2015~2018 - Fred Nora.
 *
 * File: apps\shell\crt0.c
 *
 * Environment: Gramado Core.
 * Usado para inicializar a rt na libc99
 */


#include "init.h" 


static char *argv[] = { "-init",NULL };
static char *envp[] = { "ROOT=root:/volume0", NULL };


extern int main ( int argc, char *argv[] );


//
// Main function in C part.
//

void crt0 (){
	
	int Response;
	
	//char **empty_string_pool;
	

    // Inicializando o suporte a alocação dinâmica de memória.
	// Inicializando o suporte ao fluxo padrão.
    // Call main().	
	
	libcInitRT ();
	stdioInitialize ();	


	Response = (int) main ( 1, argv );
	
	//while(1){}
								
									
	//
	// Chama kill ou exit de acordo com o problema ocorrido em main.
	// O erro pode vir no retorno ou implementa-se uma forma de pegar a execessão 
	// ocorrida durante a execussão de main.
	//
	
	switch (Response)
	{
	    case 0:
		    exit (0);
            break;
 
        default:
		    //exit(app_response);
			//exit(1);
			//die ("crt0: EXIT ERROR! \n");
            break;		
	};
	
	//
	// ## ERROR ##
	//
	
hang:	
    printf("crt0: EXIT ERROR! \n");
    printf("crt0: *Hang!\n");
	while(1)
	{
		asm("pause");
		asm("pause");
		asm("pause");
		asm("pause");
	};
};

