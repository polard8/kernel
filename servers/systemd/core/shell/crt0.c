/*
 * Gramado Operating System - The main file for the shell.
 * (c) Copyright 2015~2019 - Fred Nora.
 *
 * File: crt0.c
 *
 * Environment: Gramado Core.
 *
 */


#include "shell.h" 



static char *argv[] = { 
	"Gramado Core Shell - GWS",    // 0 - Nome do shell
	"-f",	                       // 1 - File flag.
	"test.sh",                     // 2 - File name for the script.
    "--interactive",               // 3 - Shell interativo
	"--login",                     // 4 - Login
	"--headless",                  // 5 - headless	
	"--notaskbar",                 // 6 - Taskbar        --taskbar --notaskbar
	"--gws",                       // 7 - Modo servidor. --gws
	"--nodesktop",                 // 8 - Modo desktop.  --desktop --nodesktop
	NULL 
};


// Fake environment.
/*
static char *envp[] = { 
    "VFSROOT=root:/volume0",           //root dir do vfs
    "BOOTVOLUMEROOT=root:/volume1",    //root dir do volume de boot
    "SYSTEMVOLUMEROOT=root:/volume2",  //root dir do volume do sistema
	NULL 
};
*/

extern int main ( int argc, char *argv[] );


//
// Main function in C part.
// The entry point is in head.s
//


// #todo
// O crt0 deve pegar a string na memória compartilhada,
// pois alguns argumentos determinam como o shell deve inicializar.

void crt0 (){
	
	int Response;
	
	//char **empty_string_pool;
	

    // Inicializando o suporte a alocação dinâmica de memória.
	// Inicializando o suporte ao fluxo padrão.
    // Call main().	
	
	libcInitRT ();
	stdioInitialize ();	


	Response = (int) main ( 3, argv ); 
								
			
	// Chama kill ou exit de acordo com o problema ocorrido em main.
	// O erro pode vir no retorno ou implementa-se uma forma de pegar a execessão 
	// ocorrida durante a execussão de main.
	
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
	
	while (1){
		
		asm ("pause");
		asm ("pause");
		asm ("pause");
		asm ("pause");
	};
}

