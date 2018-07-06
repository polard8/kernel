/*
 * File: abort.c
 *
 * Descrição:
 *     Rotina de aborto do kernel em caso de erro grave.
 *
 *    Versão 1.0, 2015, 2016. 
 */

 
#include <kernel.h>


/*
 * KeAbort:
 *     Interface para chamar módulo externo.
 *     Aborta o sistema atravéz de chamada à módulo externo.
 *     Chama um módulo externo para operações de finalização
 *     do sistema.
 *     Chama módulo externo (Server em user mode).
 */
void KeAbort() 
{
    printf("KeAbort:");
    die();
};


/*
 * systemAbort:
 *     Chama interface pra abortar todo o sistema
 *     inclusive o kernel.
 */
void systemAbort()
{
	//
	// @todo: Aborta o sistema operacional, nao somente o kernel. ??
	//
	
    KiAbort(); 
    
	//
	// Sem retorno !
	//
};



/*
 * KiAbort:
 *     Interface para abortar o kernel..
 *     Sem retorno !
 */
void KiAbort() 
{
    abort();	
};


/*
 ***********************************************************
 * abort:
 *     Módulo interno do tipo MB. Faz parte do Kernel Base.
 *     Aborta o kernel e mostra o erro.
 *     Aborta o kernel devido a falhas do kernel.
 *
 *     @todo: Pode-se criar um arquivo de log de erro.
 *           //...
 */ 
void abort()
{   
	asm(" cli ");
	save_current_context();
	
	if(KernelStatus != KERNEL_ABORTED)
	{
        KernelStatus = KERNEL_ABORTED;
	    scheduler_lock();  //@todo: tirar daqui.
		//...
	};
	
	//scheduler_lock();
	
	/*
	 * Daqui pra baixo são mensagens.
	 */    
	printf("abort: Kernel aborted!\n");
	
	//Confere a fase de inicialização. Se todas as foses foram cumpridas.
	if(KeInitPhase < 3){
	    printf("KeAbort: KeInitPhase={%d}\n",KeInitPhase);
	};
	
	
    // Mostra o número do último erro.
	
	 
    switch(errno)
	{
	    case 0:
		    printf("erro %d\n", errno);
		    break;

	    //tempo esgotado pra uma tarefa sensível ao tempo.		 
	    case 1:        
		    printf("Acabou o tempo da Thread={%d}\n",current_thread);
		    break;

	    case 2:
		    printf("erro %d\n", errno);
		    break;
			
		//...
		
		default:
		    printf("default errno %d\n", errno);
		    break;
	};
    		
	mostra_slot(current_thread);
	mostra_reg(current_thread);
	
	
    //  Final message !
    
	 
	
	//@todo: Usar apenas uma printf.
	
	printf("* \n");                    //Bullet!
    printf("System Halted!\n");        //Message.
	
	if(VideoBlock.useGui == 1){
	    refresh_screen();
	};
	

    
	/*
     *  No return.
     */	     	
	while(1){         //Wait forever.
		
	asm("cli");
	asm("hlt");                        //Halt system.
	
	};                          
};

//
// End.
//

