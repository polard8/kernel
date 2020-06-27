/*
 * File: sched/sched.h
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
#define LOCKED    0
#define UNLOCKED  1  

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
 

void init_scheduler (void);
 

//Interfaces. 
int KiScheduler (void);

int KiFindHigherPriority (void); 

int KiSelectNextThread (int current);




// Obs: 
// Manipuladores de troca de thread. 
// Fazem sentido estarem no scheduler. 

struct thread_d *pick_next_thread (void);


int scheduler (void);

void scheduler_start (void);

void scheduler_lock (void);

void scheduler_unlock (void);

void preempt (void);



//waitpid
int do_waitpid (pid_t pid, int *status, int options);


//Espera por um motivo.
void wait_for_a_reason ( int tid, int reason );

//bloqueia por um motivo
void block_for_a_reason (int tid, int reason);

//acordar uma determinada thread se ela estiver 
//esperando por um evento desse tipo.
int wakeup_thread_reason( int tid, int reason );

//procura alguma thread que esteja esperando 
//por um evento desse tipo e acorda ela.
int wakeup_scan_thread_reason( int reason );

//@todo, enviar isso para dispatch.h
void dispatch_thread2 (void);

unsigned long scheduler_get_status (void);

int find_higher_priority (void);

int SelectNextThread(int current);

void set_current(int id);

int get_current (void);

int get_current_task (void);

int set_priority (void);


void wakeup_thread(int tid);

void set_task_status (unsigned long status);
unsigned long get_task_status (void);   //ts.c



//0
void do_thread_initialized (int tid);
//1
void do_thread_standby (int tid);
//2
void do_thread_zombie (int tid);
//3
void do_thread_dead (int tid);
//4
void do_thread_ready (int tid);
//5
void do_thread_running (int tid);
//6
void do_thread_waiting (int tid);
//7
void do_thread_blocked (int tid);



// Desiste do tempo de processamento.
// cooperativo.
// Muda o seu tempo executando para: Próximo de acabar.

void yield (int tid);

void check_for_standby (void);

int check_quantum (void);


//
// End.
//
