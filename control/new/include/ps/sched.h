
// sched.h

#ifndef __SCHED_H
#define __SCHED_H    1


//#define NR_TASKS ??
//#define FIRST_TASK ?
//#define LAST_TASK ? 

// Status do scheduler.
#define LOCKED    0
#define UNLOCKED  1  

/*
 * Scheduling policies
 */

#define SCHED_RR    0
//#define SCHED_??    1
// ...

struct scheduler_info_d
{
    int initialized;
    int policy;
    unsigned long rr_round_counter;
    unsigned long flags;
};

extern struct scheduler_info_d  SchedulerInfo;


// Hz padrão. 100Hz. 
// Uma interrupção a cada 10ms.
// #bugbug: Isso ja esta definido em coisas do pit.
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


// ==========================================
// Input responder
// See: schedi.c
int flagUseThisInputResponder;
int input_responder_tid;
int check_for_input_responder(void);
void set_input_responder_tid(int tid);
// ==========================================


//
// == prototypes ============
//

int init_scheduler (unsigned long sched_flags);

// ::core
tid_t scheduler (void);

void scheduler_lock (void);
void scheduler_unlock (void);
unsigned long scheduler_get_status (void);

void cut_round( struct thread_d *last_thread );

// ===

tid_t KiScheduler (void);

void do_thread_blocked (int tid);
void do_thread_dead (int tid);
void do_thread_initialized (int tid);
void do_thread_ready (int tid);
void do_thread_running (int tid);
void do_thread_standby (int tid);
void do_thread_waiting (int tid);
void do_thread_zombie (int tid);

int do_waitpid (pid_t pid, int *status, int options);

int get_current_thread (void);
void set_current_thread (int tid);

void wait_for_a_reason ( int tid, int reason );
int wakeup_thread_reason ( int tid, int reason );
int wakeup_scan_thread_reason ( int reason );
void wakeup_thread (int tid);
void yield (tid_t tid);

void check_for_standby (void);

#endif    



















