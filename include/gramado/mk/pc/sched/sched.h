/*
 * File: sched\sched.h
 *
 * Descrição:
 *     Header do scheduler. 
 *     Parte do módulo microkernel do kernel base.
 *
 * @todo: 
 *     Fazem sentido estarem aqui todos os manipuladores de 
 * estado da thread ?
 *
 * Obs: Esse modo deve estar associado ao sistema de arquivos
 * e ao gerenciador de memória.
 *
 * History:
 *     2015 - Created by Fred Nora.
 */

 
//#define NR_TASKS ??
//#define FIRST_TASK ?
//#define LAST_TASK ? 

//Status do scheduler.
#define LOCKED   0                            
#define UNLOCKED 1  

//Tipo de scheduler.
#define SCHEDULER_NULL   0
#define SCHEDULER_RR     1
#define SCHEDULER_READY  2


//Hz padrão. 100Hz. Uma interrupção a cada 10ms.
#define HZ 100
//#define LATCH (1193180/HZ)

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
int KiScheduler();

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

//wait
int do_wait ( int *status );

//bloqueia por um motivo
void block_for_a_reason (int tid, int reason);

//acordar uma determinada thread se ela estiver 
//esperando por um evento desse tipo.
int wakeup_thread_reason( int tid, int reason );

//procura alguma thread que esteja esperando 
//por um evento desse tipo e acorda ela.
int wakeup_scan_thread_reason( int reason );

//@todo, enviar isso para dispatch.h
void dispatch_thread2();

unsigned long scheduler_get_status();
int find_higher_priority();
int SelectNextThread(int current);
void set_current(int id);
int get_current();
int get_current_task();
void new_task_scheduler(); //cancelada
int set_priority();


void wakeup_thread(int tid);

void set_task_status(unsigned long status);
unsigned long get_task_status();



void do_thread_initialized (int id);
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
