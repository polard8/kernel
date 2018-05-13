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


/*
 *****************************************************************
 * executive_gramado_core_init_execve:
 *     Executa um programa no processo INIT 
 * dentro do ambiente Gramado Core. 
 * #obs: Isso funcionou.
 */
int executive_gramado_core_init_execve( int i,
                                        const char *arg1, //file name
                                        const char *arg2, 
                                        const char *arg3 )
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
	
	printf("\nexecutive_gramado_core_init_execve: testing ...\n");
	printf("fileneme={%s}\n",arg1);
	printf("arg1={%s}\n",arg2);
	printf("arg2={%s}\n",arg3);
	//printf("arg={%x}\n",argv[0]);
	//printf("env={%x}\n",envp[0]);
	
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
 		
		
		//
		// #bugbug
		// #importante Precisamos do ponteiro válido para filename.
		// Não podemos auterá-lo e depois usá-lo.
		//
		
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

