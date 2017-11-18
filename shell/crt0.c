
// crt0.c - testando a implementação do crt no processo shell.bin 


//usado para inicializar a rt na libc99

#include "types.h"
#include "stddef.h"   
#include "stdlib.h"  



extern void *GramadoMain( int, char*, unsigned long , int );
//extern int libcInitRT();


//
//
//

void crt0()
{
    int mainret;	

//initRT:	
	libcInitRT(); 
	
	mainret = (int) GramadoMain(0,0,0,0);
	
	//
	// Chama kill ou exit de acordo com o problema ocorrido em main.
	// o erro pode vir no retorno ou implementa-se uma forma de pegar a execessão 
	// ocorrida durante a execussão de main.
	//
	
	while(1){}
}

