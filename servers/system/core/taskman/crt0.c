
// crt0.c


//usado para inicializar a rt na libc99


#include "tm.h"




static char *argv[] = { "-init",NULL };
//static char *envp[] = { "ROOT=root:/volume0", NULL };


extern int main ( int argc, char *argv[] ); 

//
// # Entry point #
//


void crt0 (){
	
    int ExitCode;	
	
    //Inicializando o suporte a alocação dinâmica de memória.
	//Inicializando o suporte ao fluxo padrão.

	libcInitRT();
    stdioInitialize();	
		
	ExitCode = (int) main ( 1, argv ); 
	
	// Chama kill ou exit de acordo com o problema ocorrido em main.
	// o erro pode vir no retorno ou implementa-se uma forma de pegar a execessão 
	// ocorrida durante a execussão de main.
	
	exit ( ExitCode );
	
	while (1){
		asm ("pause");
	};
}

