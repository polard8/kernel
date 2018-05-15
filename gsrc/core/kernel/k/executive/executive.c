/*
 * Gramado Executive - The main file for the Executive module in the 
 * kernel base. 
 * (c) Copyright 2015-2016 Fred Nora.
 *
 * File: k\executive.c 
 * 
 */
 
 
#include <kernel.h>
//#include "eidata.h"  //Executive Internal Data.

//unsigned char  EcecutiveName[] = "EXECUTIVE LAYER";


//rotina interna de support.
//isso deve ir para bibliotecas depois.
//não tem protótipo ainda.
// Credits: Luiz Felipe
/*
void executive_fntos(char *name)
{
    int  i, ns = 0;
    char ext[4];
    //const char ext[4];
	
    //transforma em maiúscula
	while(*name && *name != '.')
	{
        if(*name >= 'a' && *name <= 'z')
            *name -= 0x20;

        name++;
        ns++;
    }

    // aqui name[0] é o ponto.
	// então constroi a extensão.
	for(i=0; i < 3 && name[i+1]; i++)
	{
        if(name[i+1] >= 'a' && name[i+1] <= 'z')
            name[i+1] -= 0x20;

        ext[i] = name[i+1];
    }

    while(ns < 8){
        *name++ = ' ';
        ns++;
    }

    for(i=0; i < 3; i++)
        *name++ = ext[i];

    *name = '\0';
};
*/

/*
 *****************************************************************
 * executive_gramado_core_init_execve:
 *     Executa um programa no processo INIT 
 * dentro do ambiente Gramado Core. 
 * #obs: Isso funcionou.
 */
int executive_gramado_core_init_execve( int i,              //serviço
                                        const char *arg1,   //file name
                                        const char *arg2,   //arg
                                        const char *arg3 )  //env
{
	struct thread_d *Thread;
    
	//fail.
	int Status = 1;
	
	//Esse é o primeiro argumento.
	int Plane;
	char *s;
	
	
	//printf("0=%s ",&argv[0]);
    //printf("1=%s ",&argv[1]);
    
	//## teste
	//
	//if( ! strcmp( (char*)argv[0], "-f" ) ) 
	//if( strncmp( (char*) &argv[1], "-f", 2 ) == 0 )
	//{
	//	printf("executive_gramado_core_init_execve: FOREGROUND\n");
    //    Plane = FOREGROUND;
    //}else{
	//	printf("executive_gramado_core_init_execve: BACKGROUND\n");
	//	Plane = BACKGROUND;
	//};
	
	//fail.
	//if( (const char *) filename == NULL ){
	//	return 1;
	//}
	
	//
	// Testando carregar um programa para 
	// rodar no processo INIT, usando a thread 
	// primária do processo !
	//
	
	printf("\nexecutive_gramado_core_init_execve: testing ...\n\n");
	
	printf(">>>fileneme={%s}\n",arg1);
	printf(">>>arg={%s}\n",arg2);
	printf(">>>env={%s}\n\n",arg3);
	
	//
	// Pegar o ponteiro da thread primária do processo 
	// INIT.
	//
	
	Thread = (struct thread_d *) threadList[0];
	if( (void*) Thread == NULL )
	{
		goto fail;
	}else{
		
		if( Thread->used != 1 || Thread->magic != 1234 ){
			goto fail;
		}
		
		// Significa que o contexto nunca foi salvo ...
		// isso é importante, pois o spawn não funciona em thread 
		// com o contexto salvo.
		Thread->saved = 0; 
		
		Thread->plane = Plane;
		
	    //Context.
	    //@todo: Isso deve ser uma estrutura de contexto.
	    Thread->ss  = 0x23;                          //RING 3.
	    Thread->esp = (unsigned long) 0x0044FFF0;    //idleStack; (*** RING 3)
	    Thread->eflags = 0x3200;  //0x3202, pois o bit 1 é reservado e está sempre ligado.
	    Thread->cs = 0x1B;                                
	    Thread->eip = (unsigned long) 0x00401000;   //entry point  	                                               
	    Thread->ds = 0x23; 
	    Thread->es = 0x23; 
	    Thread->fs = 0x23; 
	    Thread->gs = 0x23; 
	    Thread->eax = 0;
	    Thread->ebx = 0;
	    Thread->ecx = 0;
	    Thread->edx = 0;
	    Thread->esi = 0;
	    Thread->edi = 0;
	    Thread->ebp = 0;
		
		
		Thread->Next = NULL;
		
		//
		// Load file.
		//
 		
		
		//#bugbug
		//string lenght
		//devemos ver se a string não passa dos limites.
		//Como essa rotina é para executar um arquivo .bin,
		//caso não exista uma extensão .bin e o nome seja 
		//menor que 8 podemos adicionar a extensão .bin.
		
		size_t l;
		l = (size_t) strlen( (char*) arg1);
		
		if( l > 11 )
		{
		    printf("executive_gramado_core_init_execve: File too long!\n");	
		}else{
			
			
			 
			//se não existe um ponto entre os oito primeiros chars,
            //então colocamos a extensão .bin logo após o nome passado.
            //e ele é pelo menos menor que 11, mas deveria ser menor que oito.			
			if( arg1[0] != '.' || 
			    arg1[1] != '.' || 
                arg1[2] != '.' || 
                arg1[3] != '.' || 
                arg1[4] != '.' || 
                arg1[5] != '.' || 
                arg1[6] != '.' || 
                arg1[7] != '.' )
				{ 
				    l = (size_t) strlen( (char*) arg1);
                    if( l > 8 )
					{
						printf("executive_gramado_core_init_execve: File without ext is too long!\n");
					}
					
					char bin_string[] = ".bin";
		            strcat( (char *)arg1, (const char *)bin_string);
			    };
			 
		};
		
		//
		// #bugbug
		// #importante Precisamos do ponteiro válido para filename.
		// Não podemos auterá-lo e depois usá-lo.
		//
		
		//#importante: Isso precisa ser nesse momento e não antes,
		//pois pode corromper o espaço destinado aos argumentos 
		//dentro do vetor ao acrescentar zeros.
		//executive_fntos( (char *) arg1);
		read_fntos( (char *) arg1);
		
		//fs/read.c
	    // "FILE    BIN"
        Status = (int) fsLoadFile( (unsigned char *) arg1, 
		                           (unsigned long) 0x00400000 );

        //fail
		if( Status == 1 )
		{
			// @todo:
			// Configurar estrutura.
			goto fail;
		};
		
		// Se deu certo.
		if( Status == 0 )
		{
		    queue_insert_data(queue, (unsigned long) Thread, QUEUE_INITIALIZED);
            SelectForExecution(Thread);    // * MOVEMENT 1 ( Initialized ---> Standby ).
            goto done; 
        };	
         
        //fail		 
	};
	
	//fail
	
fail:
    printf("fail ");
done:
    printf("done\n");	
	refresh_screen();
	return (int) Status;	
};


/*
void executiveMain();
void executiveMain(){
	return;
};
*/

/*
 * executive_config_exported_functions:
 *
 *     Configura a tabela do Kernel de funções exportadas
 *	   e a tabela de ponteiros para tabelas dos outros programas em Kernel Mode.
 *
 */
/*
int executive_config_exported_functions(); 
int executive_config_exported_functions()
{
	
    ring0_exported = (void*) malloc(sizeof(struct ring0_exported_d));
	
	if( (void*) ring0_exported == NULL )
	{
	    return (int) 1;
	}
	else
	{
	    //ring0_exported->bm_exported  = ( ponteiro para a tabela de funções exportadas pelo boot manager)
		//ring0_exported->bl_exported  = ( ponteiro para a tabela de funções exportadas pelo boot loader)
		//ring0_exported->bk_exported  = ( ponteiro para a tabela de funções exportadas pelo kernel)
		
		
		//@todo: Criar a tabela do kernel e salvar o ponteiro nessa estrutura ai.
		//       Pegar os ponteiros de bootmanager e bootloader e colocar ai.
		
	};
	
	
	// @todo: Nothing more?
	
done:
    return (int) 0;
};

*/

/*
 * sys_showkernelinfo:
 *     Show kernel info.
 */
void sys_showkernelinfo()
{
	KiInformation();
	return;
};


/*
 * init_executive:
 *     Initialize the kernel executive.
 *     Archtecture (independent) inicialization. 
 */
int init_executive()
{
    int Status = 0;
	
	printf("EXECUTIVE:\n");
	
	//  PCI - Pega informações da PCI.
	init_pci();
	
	// CLOCK - Pega informações de Hora e Data.
    init_clock();
	
	//configura a tabela do kernel de funções exportadas
	//e tabela de ponteiros para tabelas dos outros programas em kernel mode.
    //Status = (int) executive_config_exported_functions();

	//Continua ...
	
Done:
    
	//@todo: Checar a validade de 'Initialization' ??

    Initialization.executive = 1;	
	printf("Done!\n");	
	return (int) Status;
};


/*
int executiveInit()
{};
*/

//
// End.
//

