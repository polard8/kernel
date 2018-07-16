/*
 * File: mk\faults.c
 * 
 *     x86 faults.
 *
 * History:
 *     2015 - Created by Fred Nora.
 */


#include <kernel.h>


extern unsigned long get_page_fault_adr();

//
// # Flags #
//

// Paginação sob demanda.
// Se essa flag estiver acionada, estamos avisando que devemos 
// continuar com o sistema pois estamos apenas alocando uma página faltante.
int demand_paging_flag;

// Estamos fechando uma thread que apresentou problemas.
int thread_failed_flag;


// Estamos sinalizando que não há mais o que fazer.
// Devemos parar.
int fatal_error_flag;


//Protótipo de função interna.
void do_pagefault();


/*
 *****************************************
 * faults:
 *    #importante:
 *    +Quem chamou isso, pois temos a intenção de retornar,
 *     inicializando outra a mesma thread, as agora com a inclusão da 
 *     página faltante, ou reinicializar com outra thread, pois fechamos 
 *     a que estava com problemas.  Por fim ainda temos o caso em quan não iremos retornar.
 *
 */
void faults( unsigned long number )
{
	
//Setup:	

    struct thread_d *t;
	
	// # Disable interrupts # 
	asm( "cli" );

	t = (void *) threadList[current_thread];
	
	if( (void *) t == NULL )
	{
		printf("mk-faults-faults: struct\n");
		printf("No current thread\n");
		goto fail;
	}
	
	if( (void *) t != NULL )
	{
	    //Salva o contexto se a tarefa já esteve rodando.
	    if( ProcessorBlock.threads_counter >= 1 && 
		    t->step > 0 )
		{
            //printf("faults: Saving context\n");
			save_current_context();    
	    }
	};
	
	
//Messages:
	
	printf("*FAULTS:\n");
	printf("Number ## %d  ## \n", number);               
    printf("Init Phase %d \n", KeInitPhase);
	printf("logonStatus %d guiStatus %d \n", logonStatus, guiStatus );
	printf("Running Threads %d \n", ProcessorBlock.threads_counter );
	printf(" TID %d Step %d \n", current_thread, t->step );			
	
	//Mostra erro de acordo com o número.
    switch(number)
	{
	    //EXCEPTION
		case 1:
		case 3:
		    printf("EXCEPTION\n");
		    mostra_reg(current_thread);
			break;
		
		//DOUBLE FAULT
	    case 8:
			printf("DOUBLE FAULT\n");
			mostra_slot(current_thread);
		    break;

	    //STACK
	    case 12:
			printf("STACK FAULT\n");
			mostra_reg(current_thread);
		    break;

	    //GP
	    case 13:
		    printf("GP\n");
			mostra_reg(current_thread);
		    break;
		
		//PAGE FAULT
		//Obs: é o contrário de page hit.
	    case 14:
		    do_pagefault();
		    break;
	    
	    default:			
			printf("Default number\n");
            mostra_reg(current_thread);			
			break;
	};

	
	//
	// # Flags #
	//
	
	if( fatal_error_flag == 1 ){
        
		// We can't do anything else.
		goto done;			
	}else if ( demand_paging_flag == 1 ){
		
		// Uma página faltante foi atribuída à uma threa.
		goto tryagain;
	}else if ( thread_failed_flag == 1 ) {
		
		// Uma thread falhou, então fechamos ela e vamos tentar continuar.
		goto tryagain;
	};
	
    //
	// * DIE.
	//
	
done:	
    printf("done");
    die();
	
fail:
    printf("# FAIL #");
    die();	
	
tryagain:
    //refresh_screen();
	
	// #debug
	// Não estamos continuando por enquanto pois 
	// ainda estamos iplementando isso.
	die();
    
	return;	
};


/*
 ***********************************************
 * KiCpuFaults:
 *     Interface para chamar a rotina de faults.
 */
void 
KiCpuFaults( unsigned long number )
{
    faults(number);
	die();
};


/*
 ******************************
 * do_pagefault:
 *     14 PAGE FAULT.
 *     Obs: Podemos apenas fechar a thread atual e 
 * retomar o sistema.
 * 
 */
void do_pagefault()
{
	
//Setup:	

	unsigned long page_fault_address;
	
	// We can't close idle thread.
	// Se a thread que apresentou problemas foi a idle.
	// uma opção é tentar recriá-la.
	if( current_thread == idle )
	{
		printf("do_pagefault: We can't close idle thread \n");
		fatal_error_flag = 1;
		goto fail;
	};
	
	
	//
	// #importante
    // Devemos ter informações na estrutura da thread que indiquem 
	// se todas as páginas foram atribuídas à ela ou não na hora 
	// do carregamento ...
    // Pois assim a rotina de pagefault poderá saber se deve 
	// realizar a paginação sob demanda ou fechar a thread.
	//
	
//Messages:	
    
	printf("do_pagefault:\n");
	
	// #todo:
	// +Checar se a current é uma thread válida.
	// +Checar se a current está esperando por paginação sob demanda.
	// +Pegar o endereço.
	// +Realizar o mapeamento da página faltante.
	// 
	
	//Page Fault Linear Address (PFLA).
	page_fault_address = (unsigned long) get_page_fault_adr();
	
	// Se o endereço for igual a 0 é porque o eip está perdido.
	// Devemos fechar a thread.
	if( page_fault_address == 0 )
	{
		printf("Killing thread %d \n" ,current_thread );
	    kill_thread( current_thread );
        current_thread = idle;
        thread_failed_flag = 1;
		goto done;		
	}
	
	printf("Address={%x}\n", (unsigned long) page_fault_address);
	mostra_reg(current_thread);
	mostra_slots();
	
	//@todo alert.
	printf("do_pagefault: @todo: alloc page.\n");
	
done:	
	return;
fail:
    return;
}



//
// End.
//

