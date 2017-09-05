/*
 * Arquivo: faults.c
 *
 * Faz parte do Process Manager, parte fundamental do Kernel Base.
 *
 * Descrição:
 *     Rotinas para atender as faults da cpu x86.    
 *
 * @todo: Fazer rotinas para todas as faults.
 *
 *     As faults de páginas são usadas para as rotinas de memóvia virtual. 
 * Swap. Então, quando ouver uma falta de página, os módulos ou drivers 
 * apropriados devem ser acionados à partir daqui.
 *
 * Obs:
 *     No caso de exceções de falta de página, por exemplo, o núcleo tem 
 * informação suficiente para tratar completamente o evento e continuar a 
 * execução do processo. Porém, em outros tipos de exceção, 
 * o núcleo não consegue preceder de maneira inteligente e tem que 
 * transferir o tratamento da exceção para um processo de tratamento 
 * de falha. Esta transferência é realizada através do mecanismo 
 * de sinais, no qual o núcleo envia ao processo, um sinal 
 * correspondente a exceção ocorrida. (Wikipedia).
 *
 * Versão 1.0, 2015.
 */


#include <kernel.h>


extern unsigned long get_page_fault_adr();


/*
 * faults:
 *     Tratamento de faults.
 */
void faults(unsigned long number)
{
    struct thread_d *t;
	unsigned long page_fault_address;
	
	asm( "cli" );
	
	//kbackground(COLOR_BLACK);
	//set_up_cursor(0,0);
	
	if(VideoBlock.useGui == 0){
		kclear(0);
	};
	
	printf("*FAULTS:\n");
	//printf("=======\n");

	t = (void *) threadList[current_thread];
	if( (void*) t != NULL )
	{
	    //Salva o conxtexto se a tarefa já esteve rodando.
	    if( ProcessorBlock.running_tasks >= 1 && t->step > 0 )
	    {
            printf("cpu_falts: Salvando contexto\n");
			save_current_context();    
	    }
        else
        {	
	        printf("cpu_falts: Nao salva contexto.\n");
	    };
	}
    else
    {	
	    printf("cpu_falts: Nao ha contexto para salvar.\n");
	};
	
	//Info. (todo: window station, desktop ...).
	printf("logonStatus={%d} \n",logonStatus);
	printf("guiStatus={%d} \n",guiStatus);
	printf("RunningTasks={%d} \n",ProcessorBlock.running_tasks);	
    printf("t->tid={%d} t->step={%d} \n",current_thread,t->step);			
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
		    printf("PAGE FAULT\n");
			//Page Fault Linear Address (PFLA).
			page_fault_address = (unsigned long) get_page_fault_adr();
			printf("Address={%x}\n", (unsigned long) page_fault_address);
			mostra_reg(current_thread);
			mostra_slots();
		    break;
	    
	    default:			
			printf("cpu_falts: Default number.\n");
            mostra_reg(current_thread);			
			break;
	};
	
//Done.
done:	
    // Final message!	
    printf("* System Halted!");    //Bullet.  
	
	// Refresh.
	if(VideoBlock.useGui == 1){
	    refresh_screen();
	};
	
	// HALT.
	asm("hlt");   
	while(1){};                      
    
	//
    //  No return. " ... e então o veremos face à face ... ".
    //	      
};


/*
 * KiCpuFaults:
 *     Interface para chamar a rotina de faults.
 */
void KiCpuFaults(unsigned long fault_number){
    faults(fault_number);
	while(1){} 
};


//
//fim.
//

