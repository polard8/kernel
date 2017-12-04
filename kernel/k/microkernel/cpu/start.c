/*
 * File: start.c
 *
 * Descrição:
 *     Rotinas de execução de thread e processos.
 *     Faz parte do Process Manager, uma parte fundamental do Kernel Base.
 *
 * Versão 1.0, 2015, 2016. 
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
void KeStartShell(){
    panic("KeStartShell:");    //Cancelada! 	
	while(1){}; 
};


/*
 * KeStartTaskManager:
 *     Executa o programa TASKMAN.BIN.
 */
void KeStartTaskManager(){
    panic("KeStartTaskManager:");    //Cancelada! 	
	while(1){};
};


/*
 * start_task: 
 *     Habilita uma tarefa para ser executada pela primeira vez, alertando 
 * sobre a presença dela.
 *
 * @todo: 
 *     Poderia ser um kernel request?!
 *
 */
void start_task(unsigned long id, unsigned long *task_address)
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
void reload_current_task(){
    return;    //Cancelada!
};


/*
 * switch_to_user_mode:     
 */
void switch_to_user_mode(){ 
    panic("switch_to_user_mode:");    //Cancelada!	
	while(1){};
}; 


/*
 * executa_tarefa:
 *     Executa uma nova thread.
 *     @todo: Mudar o nome. startExecuteThread(...)
 *          
 */
//unsigned long startExecuteThread(int tid, unsigned long *thread_address)

unsigned long executa_tarefa(int id, unsigned long *task_address)
{
    struct thread_d *t;
	
    //
	// OBS: A thread a ser executada, precisa ser a current.   
    //
	
	if(current_thread != id)
	{
        printf("executa_tarefa: current_thread = %d | new task = %d ",current_thread, id);
        refresh_screen();
		while(1){};
		//return 1;
	};	

	
    //
    // Structure.
    //
	
	t = (void *) threadList[id];	
	if( (void *) t == NULL)
	{
	    panic("executa_tarefa error: Structure!\n");
	    while(1){};
	}
    else
    {
        // Status.	
	    if(t->state != READY){
	        panic("executa_tarefa error: State!\n",id);
            while(1){}; 	    
	    }else{
	        t->state = RUNNING;
	    };
	
	    //...
	};	
   
	//
	// Running tasks ~ Incrementa o número de tarefas que estão rodando.
	//
	
    ProcessorBlock.running_tasks++;   
	
	IncrementDispatcherCount(SELECT_ANY_COUNT);

	//verbose.	
    // printf("executa_tarefa: Executando %d \n",current_thread);
	//refresh_screen();
	
	//pilha
	unsigned long eflags = 0x3200;
	unsigned short cs = 0x1B;            
	unsigned long eip = (unsigned long ) task_address;
			
	//segmento de dados.
	asm(" movw $0x0010, %ax ");	   
	asm(" movw %ax, %ds ");
	asm(" movw %ax, %es ");
	asm(" movw %ax, %fs ");
	asm(" movw %ax, %gs ");
	
    asm(" pushl %0" :: "r" (eflags): "%esp");  
    asm(" pushw %0" :: "r" (cs)    : "%esp");             
    asm(" pushl %0" :: "r" (eip)   : "%esp");  
	
    outb(0x20,0x20); 
	asm("sti");
    asm("iret");
	//Nothing.	
fail:
    panic("executa_tarefa error: Return!");
    while(1){};    
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

