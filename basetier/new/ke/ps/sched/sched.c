
// sched.c
// Core scheduler code and related routines.
// ...

#include <kernel.h>


/*
 * __scheduler_rr:
 *    Troca a thread atual, escolhe uma nova thread atual 
 * para rodar no momento.
 *    O método é cooperativo, Round Robing.
 *
 * Ordem de escolha:
 * ================
 *  +fase 1 - Pega a próxima indicada na estrutura.
 *  +fase 2 - Pega nos slots a de maior prioridade.
 *  +fase 3 - Pega a Idle. 
 *            @todo: Nessa fase devemos usar a idle atual, 
 *            indicada em current_idle_thread.  
 *  //...
 *
 * Obs:
 *     O que estamos fazendo aqui é incrementar a tarefa atual e olhando se a
 * próxima tarefa da lista threadList[] está pronta pra rodar.
 *
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

int __scheduler_rr (unsigned long sched_flags)
{
    int FirstTID = -1;

    // loop
    register int i=0;


    struct thread_d  *TmpThread;


    if ( system_state != SYSTEM_RUNNING )
        panic ("__scheduler_rr: system_state\n");

    system_state = SYSTEM_SCHEDULING;

    //debug_print ("scheduler: [not tested] \n");

//#ifdef SERIAL_DEBUG_VERBOSE
    //debug_print(" SCHEDULER \n");
    //printf     (" SCHEDULER \n"); refresh_screen();
//#endif


//
// rootConductor: 
// The ring0 idle thread.
//

// BSP - bootstrap processor
// The linked list for the BSP will always start with the
// ____IDLE thread. 
// #todo:
// We need to create another hook for the AP cores.

    // O Window server é o idle.
    rootConductor = (void *) ____IDLE;

    // Check
    if ( (void*) rootConductor == NULL )
        panic ("__scheduler_rr: rootConductor\n");

    if (rootConductor->used != TRUE || rootConductor->magic != 1234)
        panic ("__scheduler_rr: rootConductor validation\n");

    FirstTID = (int) rootConductor->tid;

    if ( FirstTID < 0 || FirstTID >= THREAD_COUNT_MAX )
        panic ("__scheduler_rr: FirstTID\n");

//
// rootConductor->next: 
// The control thread of the ring3 init process.
//

    //if ( (void*) InitProcess == NULL )
        //panic ("__scheduler_rr: InitProcess\n");

    if ( (void*) InitThread == NULL )
        panic ("__scheduler_rr: InitThread\n");

    rootConductor->next = (void*) InitThread;

    // Check
    if ( (void*) rootConductor->next == NULL )
        panic ("__scheduler_rr: rootConductor->next\n");

// ===============================================

//
// Conductor
//

    Conductor       = (void *) rootConductor;
    Conductor->next = (void *) rootConductor;

//
// tmpConductor
//

    tmpConductor       = (void *) rootConductor;
    tmpConductor->next = (void *) rootConductor;


//
// Walking ...
//

// READY threads in the threadList[].

    for ( i=0; i < THREAD_COUNT_MAX; ++i )
    {
        TmpThread = (void *) threadList[i];

        if ( (void *) TmpThread != NULL )
        {
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

            // Scheduler.

            // A thread esta pronta.
            if ( TmpThread->used  == TRUE && 
                 TmpThread->magic == 1234 && 
                 TmpThread->state == READY )
            {
                // Initialize counters.
                TmpThread->runningCount = 0;
                TmpThread->runningCount_ms = 0;
                
                // A prioridade nunca pode ser menor que sua prioridade b
                //if(TmpThread->priority < TmpThread->base_priority)
                    //TmpThread->priority = TmpThread->base_priority;
                
                //if (TmpThread->priority == PRIORITY_MAX)
                    //TmpThread->quantum = QUANTUM_MAX;
                
                // The tmpConductor and it's next.
                tmpConductor       = (void *) tmpConductor->next; 
                tmpConductor->next = (void *) TmpThread;
            }
        }
    };


    // #todo
    // Let's try some other lists.





// Finalizing the list.
// The tmpConductor and it's next.
    tmpConductor       = (void *) tmpConductor->next; 
    tmpConductor->next = NULL;               // Reescalona ao fim do round.
    //tmpConductor->next = (void *) ____IDLE;  // Reescalona quando o scheduler for chamado pelo timer.


// done:
    system_state = SYSTEM_RUNNING;

    // Start with the idle thread.

    return (int) FirstTID;
}



// Wrapper for __scheduler();
// Esperamos que o worker construa um round e
// que a primeira tid seja a idle.
int scheduler(void)
{
    int first_tid = (-1);
    int policy = SchedulerInfo.policy;
    unsigned long sched_flags = (unsigned long) SchedulerInfo.flags;

//
// #filter
//

    if (policy != SCHED_RR)
        panic("scheduler: Invalid policy\n");


// #todo: 
// Pegaremos a sched_flags de uma variavel global
// pois eh configuravel.
// IN: sched_flags

    if (policy == SCHED_RR)
        first_tid = (int) __scheduler_rr(0);


    if ( (void *) ____IDLE == NULL )
        panic("scheduler: ____IDLE");

    if ( ____IDLE->magic != 1234 )
        panic("scheduler: ____IDLE validation");

    if ( first_tid != ____IDLE->tid )
        panic("scheduler: first_tid != ____IDLE->tid");

    return (int) first_tid;
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




































