/*
 * File: tasks.h
 *     ??
 *     #bugbug: There is a lot of deprecated things here.
 */


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
// O que segue são os protótipos das funçções usadas com maior frequência.
//

//
// Sempre. (idle stuffs)
//


	
//
// Usadas durante a troca de threads.
//

 


//
// Usadas durante a inicialização e execução de uma thread.
// @todo: mudar apenas o protótipo para thread.h
//void spawn_thread(int id);


//#bugbug
//os conceitos de tasks ainda estão misturados, hora é thread e hora é processo

void init_tasks (void);

int init_task (int id);

unsigned long executa_tarefa(int id, unsigned long *task_address);

void start_task(unsigned long id, unsigned long *task_address);


 
//
// Outras
//

void switch_to_user_mode (void); //??

void save_context_of_new_task (int id, unsigned long *task_address); //??	

	
/*
 * Ki={Kernel Internal}
 *     Protótipos para interfaces de rotinas internas do kernel.
 * #todo: mover tudo para o arquivo ki.h ??   
 */	



void KiCpuFaults(unsigned long fault_number);

void KiSpawnTask(int id);

int KiCheckTaskContext(int thread_id);

void KiInitTasks (void);	

int KiInitTask (int id);	

int KiFork (void);	

unsigned long KiExecutaTarefa (int id, unsigned long *task_address);

void KiSwitchToUserMode (void); 

void KiSaveCurrentContext (void);

void KiRestoreCurrentContext (void);

int KiSetPriority (void);

int KiIncreasePriority (int pid);

void KiSetCurrent (int id);

int KiGetCurrent (void);

int KiGetCurrentTask (void);

void KiSetTaskStatus(unsigned long status);

unsigned long KiGetTaskStatus (void);

void KiSaveContextOfNewTask(int id, unsigned long *task_address);

void KiSetQuantum( unsigned long q);

unsigned long KiGetQuantum (void);

void KiSetCurrentQuantum( unsigned long q);

unsigned long KiGetCurrentQuantum (void);

void KiSetNextQuantum( unsigned long q);

unsigned long KiGetNextQuantum (void);

void KiSetFocus(int pid);

int KiGetFocus (void);

void KiDebugBreakpoint (void);

void KiShowTasksParameters (void);

void KiShowPreemptedTask (void);

 
//
// Quantum
//

void set_quantum( unsigned long q);

unsigned long get_quantum (void);

void set_current_quantum( unsigned long q);

unsigned long get_current_quantum (void);

void set_next_quantum( unsigned long q);

unsigned long get_next_quantum (void);

 
 
//
// O que segue são rotinas usadas com menor frequência.
// 

//Protótipos de algumas tarefas em RING 0.

void task0 (void); 
void task1 (void);


//debug de tarefas.

void show_tasks_parameters (void);


void show_preempted_task (void);


#endif    



//
// End.
//

