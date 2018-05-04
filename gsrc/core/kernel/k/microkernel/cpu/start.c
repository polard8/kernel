/*
 * File: start.c
 *
 * Descrição:
 *     Rotinas de execução de thread e processos.
 *     Faz parte do Process Manager, uma parte fundamental do Kernel Base.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - Revision. 
 */


#include <kernel.h>


//
// Funções importadas.
//

extern void turn_task_switch_on();




/*
 * KeStartShell:
 *     Executa o programa SHELL.BIN.
 */
void KeStartShell()
{
    panic("KeStartShell:");    //Cancelada! 	
    die();
};


/*
 * KeStartTaskManager:
 *     Executa o programa TASKMAN.BIN.
 */
void KeStartTaskManager()
{
    panic("KeStartTaskManager:");    //Cancelada! 	
	die();
};


/*
 ****************************************************************
 * start_task: 
 *     Habilita uma tarefa para ser executada pela primeira vez, 
 * alertando sobre a presença dela.
 *
 * @todo: 
 *     Poderia ser um kernel request?!
 *
 */
void start_task( unsigned long id, 
                 unsigned long *task_address )
{     	
	
	//@todo: filtrar argumentos.
	
	/*
	 * start_new_task_status:
	 *     É uma FLAG. Indica que existe uma thread querendo ser executada 
	 * pela primeira vez.
	 *
	 * @todo: 
	 *     Isso poderia estar na estrutura 'ProcessorBlock' ?!
	 *
	 */
	 
	start_new_task_status = 1; 
    
    //Id e Address.
	start_new_task_id = (int) id; 
    start_new_task_address = (unsigned long) task_address;

    //Só isso ??!!	
	
//Done.
done:	
	return;
};


/*
 * reload_current_task:
 */
void reload_current_task()
{
    return;    //Cancelada!
};


/*
 * switch_to_user_mode:     
 */
void switch_to_user_mode()
{ 
    panic("switch_to_user_mode:");    //Cancelada!	
    die();
}; 


/*
 ***************************************************
 * executa_tarefa:
 *     Executa uma nova thread.
 *     @todo: Mudar o nome. startExecuteThread(...)
 *          
 */
//unsigned long startExecuteThread(int tid, unsigned long *thread_address)

unsigned long executa_tarefa( int id, 
                              unsigned long *task_address )
{
    struct thread_d *t;
	
    //
	// OBS: A thread a ser executada, precisa ser a current.   
    //
	
	if( current_thread != id )
	{
        printf("executa_tarefa: current_thread = %d | new task = %d ",
		    current_thread, id );
			
        die();
		//refresh_screen();
		//while(1){};
		//return 1;
	};	

	
    //
    // Structure.
    //
	
	t = (void *) threadList[id];	
	if( (void *) t == NULL )
	{
	    panic("start-executa_tarefa: t\n");
	    die();
	}
    else
    {
        // Status.	
	    if( t->state != READY ){
	        panic("start-executa_tarefa: state",id);
            die();
			//while(1){}; 	    
	    }else{
			
	        t->state = RUNNING;
			
	    };
	
	    //...
	};	
   
	//
	// Running tasks ~ Incrementa o número de tarefas que estão rodando.
	//
	
    ProcessorBlock.running_threads++;   
	
	IncrementDispatcherCount(SELECT_ANY_COUNT);

	//verbose.	
    // printf("executa_tarefa: Executando %d \n",current_thread);
	//refresh_screen();
	
	//pilha
	unsigned long eflags = 0x3200;
	unsigned short cs = 0x1B;            
	unsigned long eip = (unsigned long ) task_address;			 
			
	// ?? #bugbug ?? rever ?? é esse mesmo o seletor que queremos para ring3 ???		
	//segmento de dados.
	asm(" movw $0x0010, %ax ");	   
	asm(" movw %ax, %ds ");
	asm(" movw %ax, %es ");
	asm(" movw %ax, %fs ");
	asm(" movw %ax, %gs ");
	
    asm(" pushl %0" :: "r" (eflags): "%esp");  
    asm(" pushw %0" :: "r" (cs)    : "%esp");             
    asm(" pushl %0" :: "r" (eip)   : "%esp");  
	
    //#bugbug ... isso realmente não é necessário ... @todo: deletar.
	outb(0x20,0x20); 
	
	asm("sti");
    asm("iret");
	//Nothing.	
	
	/*
	 *@todo: Observar os seletores usado... o de cima não deveria ser igua ???
  asm volatile(" cli \n"   
                 " mov $0x23, %ax  \n" 
                 " mov %ax, %ds  \n"
                 " mov %ax, %es  \n"
                 " mov %ax, %fs  \n"
                 " mov %ax, %gs  \n"
                 " pushl $0x23            \n"    //ss.
                 " movl $0x0044FFF0, %eax \n"
                 " pushl %eax             \n"    //esp.
                 " pushl $0x3200          \n"    //eflags.
                 " pushl $0x1B            \n"    //cs.
                 " pushl $0x00401000      \n"    //eip. 
                 " iret \n" );
*/		
	
fail:
    panic("start-executa_tarefa: fail");
    die();
	//while(1){};    
};


void KiSwitchToUserMode()
{
    //
	//@todo: Fazer rotina de interface.
	//
	
	switch_to_user_mode();
	//while(1){};    
};


unsigned long KiExecutaTarefa(int id, unsigned long *task_address){
    return 0;  //Cancelada.
};


int KiInitTask(int id)
{
	//@todo: Algum filtro.
	if(id < 0){
	    return (int) 0;	
	};
	//Nothing.
	return (int) init_task(id);
};



void KiInitTasks(){
    init_tasks();
    return;	
};

//
//fim.
//

