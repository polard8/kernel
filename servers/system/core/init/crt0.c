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
//static char *envp[] = { "ROOT=root:/volume0", NULL };


extern int main ( int argc, char *argv[] );


/*
 ****************************
 * crt0:
 *     #importante:
 *     Esse é o ponto de entrada em user mode, pois é a primeira
 *     thread se o kernel passar o comando para o init.
 *     Porém antes de termos alguma mensagem, temos que inicializar
 *     os recursos da biblioteca.
 *     ? O que acontece se falhar na hora de inicializar a biblioteca 
 *     nesse aplicativo.  ?
 *     Como esse momento é bem importante, então vamos monitor a 
 *     inicialização da biblioteca, principalmente a inicialização
 *     feita nessa trhead.
 */

void crt0 (){
	
    int ExitCode;	

	// Inicializando o suporte a alocação dinâmica de memória.
	// Inicializando o suporte ao fluxo padrão.
    // Call main().	
	
	libcInitRT ();
	stdioInitialize ();	

	
	ExitCode = (int) main ( 1, argv );
	
	// Chama kill ou exit de acordo com o problema ocorrido em main.
	// O erro pode vir no retorno ou implementa-se uma forma de pegar a execessão 
	// ocorrida durante a execussão de main.
	
	switch (ExitCode)
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
}

