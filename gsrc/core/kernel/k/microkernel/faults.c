/*
 * File: faults.c
 * 
 * x86 faults.
 *
 * History:
 *     2015 - Created by Fred Nora.
 */


#include <kernel.h>


extern unsigned long get_page_fault_adr();

//Protótipo de finção interna.

void do_pagefault();


/*
 * faults:
 *
 */
void faults(unsigned long number)
{
    struct thread_d *t;
	
	asm( "cli" );
	
	//kbackground(COLOR_BLACK);
	//set_up_cursor(0,0);
	
	if(VideoBlock.useGui == 0){
		kclear(0);
	};
	
	printf("*FAULTS:\n");

	t = (void *) threadList[current_thread];
	if( (void*) t != NULL )
	{
	    //Salva o conxtexto se a tarefa já esteve rodando.
	    if( ProcessorBlock.running_threads >= 1 && t->step > 0 ){
            printf("faults: Saving context\n");
			save_current_context();    
	    }else{	
	        printf("faults: Don't save context\n");
	    };
	}
    else
    {	
	    printf("faults: No context to save\n");
	};
	
	//Info. 
	//(@todo: window station, desktop ...).
	printf("logonStatus={%d}\n",logonStatus);
	printf("guiStatus={%d}\n",guiStatus);
	printf("RunningThreads={%d}\n",ProcessorBlock.running_threads);	
    printf("t->tid={%d} t->step={%d}\n",current_thread,t->step);			
	printf("FaultNumber={%d}\n",number);                   
    printf("KeInitPhase={%d}\n",KeInitPhase);
	
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
			printf("faults: Default number.\n");
            mostra_reg(current_thread);			
			break;
	};

    //
	// * DIE.
	//
	
done:	
    die();	
};


/*
 * KiCpuFaults:
 *     Interface para chamar a rotina de faults.
 */
void KiCpuFaults(unsigned long number){
    faults(number);
	die();
};


// 14 PAGE FAULT
void do_pagefault()
{
	unsigned long page_fault_address;
	
    printf("PAGE FAULT\n");
	
	//Page Fault Linear Address (PFLA).
	page_fault_address = (unsigned long) get_page_fault_adr();
	
	printf("Address={%x}\n", (unsigned long) page_fault_address);
	mostra_reg(current_thread);
	mostra_slots();
	
	//@todo alert.
	printf("do_pagefault: @todo: alloc page.\n");
	
done:	
	return;
}



//
// End.
//

