
// crt0.c


//usado para inicializar a rt na libc99


/* libc */
#include <types.h>
#include <stdio.h> 
#include <stddef.h>   
#include <stdlib.h>  



extern int appMain ( int argc, char *argv[] ); 


//
// # Entry point #
//


void crt0 (){
	
    int ExitCode;	

//initRT:	

    //Inicializando o suporte a alocação dinâmica de memória.
	libcInitRT();

	//Inicializando o suporte ao fluxo padrão.
    stdioInitialize();	
	
	ExitCode = (int) appMain ( 0, 0 ); 
	
	// Chama kill ou exit de acordo com o problema ocorrido em main.
	// o erro pode vir no retorno ou implementa-se uma forma de pegar a execessão 
	// ocorrida durante a execussão de main.
	
	exit ( ExitCode );
	
	while (1){
		asm ("pause");
	};
};

