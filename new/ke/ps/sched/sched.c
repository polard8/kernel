
#include <kernel.h>  


/*
 *********************************************************
 * scheduler:
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

int scheduler (void)
{
    int FirstTID = -1;

    // loop
    register int i=0;


    struct thread_d  *TmpThread;


    if ( system_state != SYSTEM_RUNNING )
        panic ("scheduler: system_state\n");

    system_state = SYSTEM_SCHEDULING;

    //debug_print ("scheduler: [not tested] \n");

#ifdef SERIAL_DEBUG_VERBOSE
    debug_print(" SCHEDULER: ");
#endif


//
// rootConductor: 
// The ring0 idle thread.
//

    rootConductor = (void *) ____IDLE;

    // Check
    if ( (void*) rootConductor == NULL )
        panic ("scheduler: rootConductor\n");

    if (rootConductor->used != TRUE || rootConductor->magic != 1234)
        panic ("scheduler: rootConductor validation\n");

    FirstTID = (int) rootConductor->tid;

    if ( FirstTID < 0 || FirstTID >= THREAD_COUNT_MAX )
        panic ("scheduler: FirstTID\n");

//
// rootConductor->next: 
// The control thread of the ring3 init process.
//

    if ( (void*) InitProcess == NULL )
        panic ("scheduler: InitProcess\n");

    if ( (void*) InitProcess->control == NULL )
        panic ("scheduler: InitProcess->control\n");

    rootConductor->next = (void*) InitProcess->control;

    // Check
    if ( (void*) rootConductor->next == NULL )
        panic ("scheduler: rootConductor->next\n");

//
// Conductor
//

    Conductor = (void *) rootConductor;

//
// Conductor->next
//

    Conductor->next = (void *) rootConductor;

//
// tmpConductor
//

    tmpConductor = (void *) rootConductor;

//
// tmpConductor->next
//

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
            // Single shot
            if ( TmpThread->used  == TRUE && 
                 TmpThread->magic == 1234 && 
                 TmpThread->state == READY )
            {
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
    tmpConductor->next = NULL;


// done:

    system_state = SYSTEM_RUNNING;

    // Start with the idle thread.

    return (int) FirstTID;
}


void schedulerCompositor(void)
{
    int i=0;
    struct thread_d *TmpThread;

    unsigned long deviceWidth  = (unsigned long) screenGetWidth();
    unsigned long deviceHeight = (unsigned long) screenGetHeight();

    if ( deviceWidth == 0 || deviceHeight == 0 )
    {
        debug_print ("schedulerCompositor: w h\n");
        panic       ("schedulerCompositor: w h\n");
    }

// ============================

    /*
    struct rect_d RectTest;
    RectTest.left = 0;
    RectTest.top = 0;
    RectTest.width = 28;
    RectTest.height = 28;
    RectTest.used = TRUE;
    RectTest.magic = 1234;
    RectTest.ready_to_refresh = TRUE;

    if ( (void*) InitThread != NULL )
    {
        if ( InitThread->used == TRUE && InitThread->magic == 1234 ){
            InitThread->surface = (struct rect_d *) &RectTest;
        }
    }
    */
    
// ============================


    for ( i=0; i < THREAD_COUNT_MAX; ++i )
    {
        TmpThread = (void *) threadList[i];

        if ( (void *) TmpThread != NULL )
        {
            if ( TmpThread->used  == TRUE && 
                 TmpThread->magic == 1234 && 
                 TmpThread->state == READY )
            {
                // #test 
                debug_print("  ----  Compositor  ----  \n");
                
                if ( (void *) TmpThread->surface != NULL )
                {
                    if( TmpThread->surface->used == TRUE && 
                        TmpThread->surface->magic == 1234 )
                    {
                        //drawDataRectangle( 0, 0, deviceWidth, 28, COLOR_BLUE );
                        //draw_string(8,8,COLOR_YELLOW," surface found ");
                        
                        if( TmpThread->surface->ready_to_refresh == TRUE ){
                        drawDataRectangle( 
                            TmpThread->surface->left, 
                            TmpThread->surface->top, 
                            TmpThread->surface->width, 
                            TmpThread->surface->height, 
                            COLOR_RED );
                            
                        TmpThread->surface->ready_to_refresh = FALSE;
                        refresh_screen();
                        }
                    }
                }
            }
        }
    };

// #test

//
// Fake bar
//

    //drawDataRectangle( 0, 0, deviceWidth, 28, COLOR_BLUE );
    //draw_string(8,8,COLOR_YELLOW," Compositor ");
    //refresh_screen();
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

// Called by init_microkernel in mk.c

void init_scheduler (void)
{
    debug_print ("init_scheduler: [TODO]\n");
    // ...
    
    scheduler_lock();
    
    // #bugbug
    // Maybe there is no IDLE defined 
    // at this point of the initialization.
    
    //set_current (IDLE);
}


// lets end this round putting a given thread at the end
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




































