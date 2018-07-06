/*
 * Arquivo: tasks.h
 *
 * Descrição:
 *    Header principal dos recursos do kernel envolvendo PROCESSOS.
 *    #bugbug: Tarefas são processos. Não threads.
 *    Esse módulos oferece algumas
 */



/*
 *  O que segue são as variáveis usadas com maior frequência.
 */
 
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
//

void spawn_task(int id);
void init_tasks();
int init_task(int id);
unsigned long executa_tarefa(int id, unsigned long *task_address);
void start_task(unsigned long id, unsigned long *task_address);

//
// Usadas durante a criação de threads e processos.
//
int fork();

 
				 

//
//outras
//
void switch_to_user_mode(); //??
void reload_current_task(); //??
void save_context_of_new_task(int id, unsigned long *task_address); //??	
	
 
	
/*
 * Ki={Kernel Internal}
 *     Protótipos para interfaces de rotinas internas do kernel.
 */	
void KiTaskSwitch();
void KiCpuFaults(unsigned long fault_number);
void KiSpawnTask(int id);
int KiCheckTaskContext(int thread_id);
void KiInitTasks();	


int KiInitTask(int id);	
int KiFork();	
unsigned long KiExecutaTarefa(int id, unsigned long *task_address);
void KiSwitchToUserMode();

  

 

void KiSaveCurrentContext();
void KiRestoreCurrentContext();	
void KiNewTaskScheduler();
int KiSetPriority();
int KiIncreasePriority(int pid);
void KiSetCurrent(int id);
int KiGetCurrent();
int KiGetCurrentTask();
void KiSetTaskStatus(unsigned long status);
unsigned long KiGetTaskStatus();
void KiSaveContextOfNewTask(int id, unsigned long *task_address);
void KiReloadCurrentTask();
void KiSetQuantum( unsigned long q);
unsigned long KiGetQuantum();
void KiSetCurrentQuantum( unsigned long q);
unsigned long KiGetCurrentQuantum();
void KiSetNextQuantum( unsigned long q);
unsigned long KiGetNextQuantum();
void KiSetFocus(int pid);
int KiGetFocus();
void KiDebugBreakpoint();
void KiShowTasksParameters();
void KiMostraSlots();
void KiMostraSlot(int id);
void KiMostraReg(int id);
void KiShowPreemptedTask();	

 

//quantum
void set_quantum( unsigned long q);
unsigned long get_quantum();
void set_current_quantum( unsigned long q);
unsigned long get_current_quantum();
void set_next_quantum( unsigned long q);
unsigned long get_next_quantum();


 
 
//
// O que segue são rotinas usadas com menor frequência.
// 

//Protótipos de algumas tarefas em RING 0.
void task0(); 
void task1();
void task2();
void task3();


//debug de tarefas.
void debug_breakpoint();
void show_tasks_parameters();
void mostra_slots();
void mostra_slot(int id);
void mostra_reg(int id);
void show_preempted_task();

//
//fim.
//

