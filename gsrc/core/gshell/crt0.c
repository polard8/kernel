
// crt0.c - testando a implementação do crt no processo shell.bin 


//usado para inicializar a rt na libc99

#include "types.h"
#include "stdio.h"   
#include "stddef.h"   
#include "stdlib.h"  


extern int GramadoMain( int argc, 
                        char *argv[], 
				        unsigned long long1, 
				        unsigned long long2 );


static char *argv[] = { "-a", "-b", NULL };
static char *envp[] = { 
    "VFSROOT=root:/volume0",
    "BOOTVOLUMEROOT=root:/volume1",
    "SYSTEMVOLUMEROOT=root:/volume2", 
	NULL 
};


//
//
//
void crt0()
{
    int app_response;	

//initRT:	

    //inicializando o suporte a alocação dinâmica de memória.
	libcInitRT();

	//inicializando o suporte ao fluxo padrão.
    stdioInitialize();	
	
	app_response = (int) GramadoMain( 3,     // Quantidade de argumentos.
	                                  argv,  // Vetor de argumentos.
									  0,     // Long1
									  0 );   // Long2
	
	//
	// Chama kill ou exit de acordo com o problema ocorrido em main.
	// o erro pode vir no retorno ou implementa-se uma forma de pegar a execessão 
	// ocorrida durante a execussão de main.
	//
	
	switch(app_response)
	{
	    case 0:
		    exit(0);
            break;
 
        default:
		    //exit(1);
			die("crt0: EXIT ERROR! \n");
            break;		
	};
	
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

