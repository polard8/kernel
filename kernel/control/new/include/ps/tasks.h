
// tasks.h 

#ifndef __TASKS_H
#define __TASKS_H    1


//Status do mecanismo de task switch. 
unsigned long task_switch_status;
 
//Status do scheduler.	
unsigned long g_scheduler_status;
 
//usada no salvamento de contexto de tarefa.
unsigned long old; //*importante!  

//new task variables.
unsigned long start_new_task_status;
int start_new_task_id;
unsigned long start_new_task_address;
 

/*
 * quantum - quanto tempo fica rodando uma tarefa ate ser interrompida.
 *
 *
 */
unsigned long quantum;
unsigned long current_quantum;
unsigned long next_quantum;


/*
 *  O que segue são as variáveis usadas com menor frequência.
 */
int task_color;
unsigned long forkid;
unsigned long newtask_EIP;    
unsigned long next_address; 

//
//outras
//
	
unsigned long task_waiting;   //?espera
unsigned long preempted_task;
unsigned long running_tasks;   //numero de tarefas rodando. //esta em estrutura agora.
unsigned long task_count;      //contador de tarefas criadas.






//
// == prototypes =========================
//




#endif    






