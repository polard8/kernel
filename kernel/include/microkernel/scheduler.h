/*
 * File: scheduler.h
 *
 * Descrição:
 *     Header do scheduler. 
 *     Parte do módulo microkernel do kernel base.
 *
 * @todo: 
 *     Fazem sentido estarem aqui todos os manipuladores de estado da thread ?
 *
 * Versão: 1.0, 2015.
 */


//Status do scheduler.
#define LOCKED   0                            
#define UNLOCKED 1  

//Tipo de scheduler.
#define SCHEDULER_NULL   0
#define SCHEDULER_RR     1
#define SCHEDULER_READY  2


//
// Tipos diferentes de scheduler. 
// Usado pelo desenvolvedor.
// RR. Priority ....
//

int schedulerType;


//@todo: deletar isso, usa-se a fila do dispatcher. 
unsigned long schedulerQueue[4]; 



//
// Protótipos:
//
 
 
 
void init_scheduler();
 

//Interfaces. 
void KiScheduler();
int KiFindHigherPriority(); 
int KiSelectNextThread(int current);
void KiDispatchTask();	

//Interaface para manipulação de estado de thread.
void KiDoThreadReady(int id);
void KiDoThreadRunning(int id);
void KiDoThreadSleeping(int id);
void KiDoThreadZombie(int id);
void KiDoThreadDead(int id);


//
// Obs: Manipuladores de troca de thread. 
//      Fazem sentido estarem no scheduler. 
//

int scheduler();
void scheduler_start();
void scheduler_lock();
void scheduler_unlock();
void preempt();
void dispatch_task();
unsigned long scheduler_get_status();
int find_higher_priority();
int SelectNextThread(int current);
void set_current(int id);
int get_current();
int get_current_task();
void new_task_scheduler(); //cancelada
int set_priority();
void taskexit();
void kill_task(int id);
void wakeup_thread(int tid);
void set_task_status(unsigned long status);
unsigned long get_task_status();


void do_thread_ready(int id);
void do_thread_running(int id);
void do_thread_sleeping(int id);
void do_thread_zombie(int id);
void do_thread_dead(int id);

void check_for_standby();
int check_quantum();


//
// Fim.
//
