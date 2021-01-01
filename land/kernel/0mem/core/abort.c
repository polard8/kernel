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
 * KiAbort:
 *     Interface to abort the system.
 */

void KiAbort (void)
{
    abort ();
    
    // Not reached!
}


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

void abort (void){
	
	asm (" cli ");
	
	debug_print("abort:\n");	
	
	save_current_context();


    if (KernelStatus != KERNEL_ABORTED)
    {
        KernelStatus = KERNEL_ABORTED;
	    scheduler_lock();  //@todo: tirar daqui.
		//...
    }
	
	//scheduler_lock();
	
	/*
	 * Daqui pra baixo são mensagens.
	 */    
	
	printf ("abort: Kernel aborted\n");
	
	//Confere a fase de inicialização. Se todas as foses foram cumpridas.
	if(KeInitPhase < 3){
	    printf("KeAbort: KeInitPhase={%d}\n",KeInitPhase);
	};
	
	
    // Mostra o número do último erro.
	
	 
    switch (errno)
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
    		
	show_slot (current_thread);
	show_reg (current_thread);
	
	
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


	while (1){ 
	    asm("cli");
	    asm("hlt");  
	}; 
}


//
// End.
//

