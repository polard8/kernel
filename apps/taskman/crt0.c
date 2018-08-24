
// crt0.c - testando a implementação do crt no processo shell.bin 


//usado para inicializar a rt na libc99


/* libc */
#include <types.h>
#include <stdio.h> 
#include <stddef.h>   
#include <stdlib.h>  



extern int appMain( int argc, char *argv[] ); 


//
// # Entry point #
//

void crt0 (){
	
    int ExitCode;	

//initRT:	

    //inicializando o suporte a alocação dinâmica de memória.
	libcInitRT();

	//inicializando o suporte ao fluxo padrão.
    stdioInitialize();	
	
	ExitCode = (int) appMain( 0, 0); 
	
	//
	// Chama kill ou exit de acordo com o problema ocorrido em main.
	// o erro pode vir no retorno ou implementa-se uma forma de pegar a execessão 
	// ocorrida durante a execussão de main.
	//
	
	exit( ExitCode );
	
	while(1){
		asm ("pause");
	};
};

