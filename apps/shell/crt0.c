
// crt0.c - testando a implementação do crt no processo shell.bin 


//usado para inicializar a rt na libc99

#include <types.h>
#include <stdio.h>   
#include <stddef.h>   
#include <stdlib.h>  

extern int shmain ( int argc, char **argv );	


static char *argv[] = { 
    "-interactive",        //shell interativo
	"-login",              //login
	"Gramado Core Shell",  //nome do shell
	"test.sh",             //nome do arquivo de script.
	NULL 
};

/*fake*/
static char *envp[] = { 
    "VFSROOT=root:/volume0",         //root dir do vfs
    "BOOTVOLUMEROOT=root:/volume1",  //root dir do volume de boot
    "SYSTEMVOLUMEROOT=root:/volume2", //root dir do volume do sistema
	NULL 
};


//
// Main function in C part.
// The entry point is in head.s
//

void crt0 (){
	
	//char **empty_string_pool;
    int Response;	

//initRT:	

    // Inicializando o suporte a alocação dinâmica de memória.
	libcInitRT();

	// Inicializando o suporte ao fluxo padrão.
    stdioInitialize();	

    // Call main().	
	Response = (int) shmain ( 3, argv ); 
								
									
	//
	// Chama kill ou exit de acordo com o problema ocorrido em main.
	// o erro pode vir no retorno ou implementa-se uma forma de pegar a execessão 
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

