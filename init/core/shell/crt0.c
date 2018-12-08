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


#include "sh.h" 


	//#arguments	
	//argv[0] = -cmd comandos; -f use file; -hl headless; -gui use gui; ...  
	//argv[1] = -interative
	//argv[2] = -login
	//argv[3] = Nome do arquivo de script.
	//argv[4] = Nome do shell.
	
//cmd	
static char *argv[] = { 
	"-cmd",                  // Shell para digitar comandos.     
    "-interactive",          // -interactive Shell interativo.
	"-login",                // -login Login.
	"nofile",                // Nome do arquivo de script.
	"Gramado Core Shell",    // Nome do shell.
	NULL 
};


/*
//file
static char *argv[] = { 
	"-f",                  // Shell para digitar comandos.     
    "",                    // -interactive Shell interativo.
	"",                    // -login Login.
	"test1.sh1",           // Nome do arquivo de script.
	"Gramado Core Shell",  // Nome do shell.
	NULL 
};
*/


// Fake environment.
// #obs: Não estamos passando isso por enquanto.
static char *envp[] = { 
    "VFSROOT=root:/volume0",           //root dir do vfs
    "BOOTVOLUMEROOT=root:/volume1",    //root dir do volume de boot
    "SYSTEMVOLUMEROOT=root:/volume2",  //root dir do volume do sistema
	NULL 
};


extern int shmain ( int argc, char **argv );	


//
// Main function in C part.
// The entry point is in head.s
//

void crt0 (){
	
	int Response;
	
	//char **empty_string_pool;
	

    // Inicializando o suporte a alocação dinâmica de memória.
	// Inicializando o suporte ao fluxo padrão.
    // Call main().	
	
	libcInitRT ();
    
	stdioInitialize ();	


	Response = (int) shmain ( 5, argv ); 
								
									
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
			die ("crt0: EXIT ERROR! \n");
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

