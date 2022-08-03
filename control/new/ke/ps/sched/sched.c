
// sched.c
// Core scheduler code and related routines.
// ...

#include <kernel.h>


struct scheduler_info_d  SchedulerInfo;

//
// == Private functions: prototypes =============
//

static tid_t __scheduler_rr(unsigned long sched_flags);


// =======================================

/*
 * __scheduler_rr:
 *    Troca a thread atual, escolhe uma nova thread atual 
 * para rodar no momento.
 *    O método é cooperativo, Round Robing.
 * Ordem de escolha:
 * ================
 *  +fase 1 - Pega a próxima indicada na estrutura.
 *  +fase 2 - Pega nos slots a de maior prioridade.
 *  +fase 3 - Pega a Idle. 
 *            @todo: Nessa fase devemos usar a idle atual, 
 *            indicada em current_idle_thread.  
 *  //...
 * Obs:
 *     O que estamos fazendo aqui é incrementar a tarefa atual e 
 * olhando se a próxima tarefa da lista threadList[] está pronta pra rodar.
 * Obs:
 *     Pega na fila ReadyQueue.
 *     O scheduler deve sempre pegar da fila do dispatcher.
 */
// #todo
// Podemos contar os rounds.
// Obs: 
// ## IMPORTANTE  ##
// A thread idle somente é usada quando o sistema 
// estiver ocioso ou quando ela for a única thread.
// E é importante que a thread idle seja usada, pois 
// ela tem as instruções sti/hlt que atenua a utilização 
// da CPU, reduzindo o consumo de energia.
// OUT: next tid.

static tid_t __scheduler_rr(unsigned long sched_flags)
{
    struct thread_d *TmpThread;
    register int i=0;
    tid_t FirstTID = -1;

// System state

    if ( system_state != SYSTEM_RUNNING ){
        panic ("__scheduler_rr: system_state\n");
    }
    system_state = SYSTEM_SCHEDULING;

    //debug_print ("scheduler: [not tested] \n");

// rootConductor: 
// The ring0 idle thread.

// BSP - bootstrap processor
// The linked list for the BSP will always start with the
// ____IDLE thread. 
// #todo:
// We need to create another hook for the AP cores.


// ===============================================
// The idle thread is the current thread of the
// first ring0 module. MOD0.BIN.

    if ( (void*) ____IDLE == NULL ){
        panic ("__scheduler_rr: ____IDLE\n");
    }
    if ( ____IDLE->used != TRUE || 
         ____IDLE->magic != 1234 )
    {
        panic ("__scheduler_rr: ____IDLE validation\n");
    }
    // Estabiliza a idle thread.
    ____IDLE->base_priority = PRIORITY_SYSTEM_THREAD;
    ____IDLE->priority = PRIORITY_SYSTEM_THREAD;
    ____IDLE->quantum = QUANTUM_MIN;  // Credits.
    rootConductor = (void *) ____IDLE;

// First TID.
// The TID of the ____IDLE thread.

    FirstTID = (tid_t) rootConductor->tid;

    if ( FirstTID < 0 || 
         FirstTID >= THREAD_COUNT_MAX )
    {
        panic ("__scheduler_rr: FirstTID\n");
    }

// ===============================================
// The control thread of the ring3 init process.
// INIT.BIN
// rootConductor->next: 

    if ( (void*) InitThread == NULL ){
        panic ("__scheduler_rr: InitThread\n");
    }
    if ( InitThread->used != TRUE || 
         InitThread->magic != 1234 )
    {
        panic ("__scheduler_rr: InitThread validation\n");
    }
    // Estabiliza a init thread.
    InitThread->base_priority = PRIORITY_SYSTEM_THREAD;
    InitThread->priority = PRIORITY_SYSTEM_THREAD;
    InitThread->quantum = QUANTUM_MIN;  // Credits.
    rootConductor->next = (void*) InitThread;

// ===============================================

// Conductor
    Conductor       = (void *) rootConductor;
    Conductor->next = (void *) rootConductor;

// tmpConductor
    tmpConductor       = (void *) rootConductor;
    tmpConductor->next = (void *) rootConductor;  // The list starts here.


// Walking
// READY threads in the threadList[].

    for ( i=0; i<THREAD_COUNT_MAX; ++i )
    {
        TmpThread = (void *) threadList[i];

        if ( (void *) TmpThread != NULL )
        {
            // Scheduler.
            // A thread esta pronta.
            if ( TmpThread->used  == TRUE && 
                 TmpThread->magic == 1234 && 
                 TmpThread->state == READY )
            {
                // Recreate the linked list.
                // The tmpConductor and it's next.
                tmpConductor       = (void *) tmpConductor->next; 
                tmpConductor->next = (void *) TmpThread;

                // Initialize counters.
                TmpThread->runningCount = 0;
                TmpThread->runningCount_ms = 0;

                // Checa se temos problemas com a prioridade base.
                // Estabiliza.
                if (TmpThread->base_priority < PRIORITY_MIN){
                    TmpThread->base_priority=PRIORITY_NORMAL;
                }
                if (TmpThread->base_priority > PRIORITY_MAX){
                    TmpThread->base_priority=PRIORITY_NORMAL;
                }
                // Voltamos para a base depois de checada a base.
                // Caso tenha havido algum problema na 
                // prioridade base, então ela foi para o equilíbrio.
                TmpThread->priority = TmpThread->base_priority;
                
                // #test
                // Se alguma thread teve seus créditos aumentados,
                // então devemos reequilibrar os creditos novamente.
                //TmpThread->quantum = QUANTUM_BALANCE;
                //if (TmpThread->base_priority == PRIORITY_MAX){
                //    TmpThread->quantum = QUANTUM_MAX;
                //}
            }

            // A thread esta esperando.
            if ( TmpThread->used  == TRUE && 
                 TmpThread->magic == 1234 && 
                 TmpThread->state == WAITING )
            {
                // Check alarm
                if ( jiffies > TmpThread->alarm ){
                    //TmpThread->signal = ?
                    TmpThread->alarm=0;
                }
                // Wake up
                //if ( TmpThread->signal ){
                //    TmpThread->state = READY;
                //}
            }
        }
    };

// #todo
// Let's try some other lists.

// Finalizing the list.
// The tmpConductor and it's next.
    tmpConductor       = (void *) tmpConductor->next; 
    tmpConductor->next = NULL;               // Reescalona ao fim do round.

// done:
    system_state = SYSTEM_RUNNING;

// Start with the idle thread.
    return (tid_t) FirstTID;
}


// Wrapper for __scheduler();
// Esperamos que o worker construa um round e
// que a primeira tid seja a idle.
// OUT: next tid.

tid_t scheduler(void)
{
    tid_t first_tid = (-1);

    //#todo: Create a method for this.
    int Policy = SchedulerInfo.policy;

    //#todo: Create a method for this.
    unsigned long sched_flags = (unsigned long) SchedulerInfo.flags;

    if (SchedulerInfo.initialized != TRUE){
        panic("scheduler: SchedulerInfo.initialized\n");
    }

    if (Policy != SCHED_RR){
        panic("scheduler: Invalid Policy\n");
    }

// #todo: 
// Pegaremos a sched_flags de uma variavel global
// pois eh configuravel.
// IN: sched_flags

    if (Policy == SCHED_RR){
        first_tid = (tid_t) __scheduler_rr(0);
    }

    if ( (void *) ____IDLE == NULL ){
        panic("scheduler: ____IDLE\n");
    }

    if ( ____IDLE->magic != 1234 ){
        panic("scheduler: ____IDLE validation\n");
    }

    if ( first_tid != ____IDLE->tid ){
        panic("scheduler: first_tid != ____IDLE->tid\n");
    }

// Return tid.
    return (tid_t) first_tid;
}












// Lock scheduler
void scheduler_lock (void){
    g_scheduler_status = (unsigned long) LOCKED;
}

// Unlock scheduler
void scheduler_unlock (void){
    g_scheduler_status = (unsigned long) UNLOCKED;
}

/*
 * scheduler_get_status:
 *     Pega o status do scheduler, se ele está travado ou não.
 */
 
unsigned long scheduler_get_status (void)
{
    return (unsigned long) g_scheduler_status;
}

/*
 ********************************
 * init_scheduler:
 *    Inicaliza o scheduler.
 *    @todo: Mudar para schedulerInit()
 *    #burbug: faz o mesmo que scheduler_start.
 */

	// #todo: 
	// Implementar inicialização de variaveis do scheduler.
	// O nome poderia ser schedulerInit().
	// Formato de classes.Init é um método. 

// Called by init_microkernel in ps/mk.c

int init_scheduler (unsigned long sched_flags)
{
    debug_print ("init_scheduler: [TODO]\n");
    // ...

    scheduler_lock();

// Input responder.
    flagUseThisInputResponder = FALSE;
    input_responder_tid = -1;


//
// Scheduler policies
//

// See:
// sched.h

    SchedulerInfo.policy = SCHED_RR;
    SchedulerInfo.flags  = (unsigned long) sched_flags;
    SchedulerInfo.initialized = TRUE;

    return 0;
}


// Lets end this round putting a given thread at the end
// of this round.
void cut_round( struct thread_d *last_thread )
{
    struct thread_d *Current;


// The current thread.

    if ( current_thread < 0 || current_thread >= THREAD_COUNT_MAX )
    {
        return;
    }

    Current = (struct thread_d *) threadList[current_thread];

    if ( (void *) Current == NULL )
    {
        return;
    }
    
    if ( Current->used != TRUE || Current->magic != 1234 )
    {
        return;
    }

// ==========================

//
// last thread
//

    if ( (void *) last_thread == NULL )
    {
        return;
    }
    
    if ( last_thread->used != TRUE || last_thread->magic != 1234 )
    {
        return;
    }

// ==========================

//
// Cut round
// 

    // The last thread of this round

    Current->next = (struct thread_d *) last_thread;

    last_thread->next = NULL; 

    return;
}





//
// End.
//




































