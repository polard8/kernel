

#ifndef __SCHED_H
#define __SCHED_H    1


//#define NR_TASKS ??
//#define FIRST_TASK ?
//#define LAST_TASK ? 

// Status do scheduler.
#define LOCKED    0
#define UNLOCKED  1  

// Tipo de scheduler.
#define SCHEDULER_NULL   0
#define SCHEDULER_RR     1
#define SCHEDULER_READY  2

// Hz padrão. 100Hz. 
// Uma interrupção a cada 10ms.
#define HZ  100

// Tranca
// #define LATCH (1193180/HZ)

// Tranca
// #define LATCH (1193180/HZ)

// Tipos diferentes de scheduler. 
// Usado pelo desenvolvedor.
// RR. Priority ....

int schedulerType;

// @todo: 
// deletar isso, usa-se a fila do dispatcher. 
unsigned long schedulerQueue[4]; 



//
// == prototypes ============
//


int scheduler (void);
void scheduler_lock (void);
void scheduler_unlock (void);
unsigned long scheduler_get_status (void);

void init_scheduler (void);

// ===

int KiScheduler (void);
void do_thread_blocked (int tid);
void do_thread_dead (int tid);
void do_thread_initialized (int tid);
void do_thread_ready (int tid);
void do_thread_running (int tid);
void do_thread_standby (int tid);
void do_thread_waiting (int tid);
void do_thread_zombie (int tid);

int do_waitpid (pid_t pid, int *status, int options);

int get_current (void);
void set_current (int id);

void wait_for_a_reason ( int tid, int reason );
int wakeup_thread_reason ( int tid, int reason );
int wakeup_scan_thread_reason ( int reason );
void wakeup_thread (int tid);
void yield (int tid);

void check_for_standby (void);

#endif    



















