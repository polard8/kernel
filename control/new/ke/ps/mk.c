
// ps/mk.c
// microkernel

#include <kernel.h> 


// Called by I_init().

int init_microkernel (void)
{
    int Status = FALSE;

    Initialization.microkernel_checkpoint = TRUE;

    debug_print ("init_microkernel:\n");


// Init scheduler.
// See: sched/sched.c
    init_scheduler(0);

// Init processes and threads, 
// See: process.c and thread.c
    init_processes();
    init_threads();    

// #todo: Init IPC and Semaphore.
    //ipc_init();
    //create_semaphore(); 

// queue
// #deprecated ?

    queue = NULL;

// Dispatch Count Block
// see: dispatch.c

    DispatchCountBlock = 
        (void *) kmalloc ( sizeof( struct dispatch_count_d ) );

    if ( (void *) DispatchCountBlock == NULL ){
        printf ("init_microkernel: DispatchCountBlock\n");
        return FALSE;
    }

    DispatchCountBlock->SelectIdleCount = 0;
    DispatchCountBlock->SelectInitializedCount = 0;
    DispatchCountBlock->SelectNextCount = 0;
    DispatchCountBlock->SelectCurrentCount = 0;
    DispatchCountBlock->SelectAnyCount = 0;
    DispatchCountBlock->SelectIdealCount = 0;
    DispatchCountBlock->SelectDispatcherQueueCount = 0;
    // ...
    DispatchCountBlock->used=TRUE;
    DispatchCountBlock->magic=1234;
    DispatchCountBlock->initialized = TRUE;

    Initialization.microkernel_checkpoint = TRUE;

// #debug 
// A primeira mensagem só aparece após a inicialização da runtime
// por isso não deu pra limpar a tela antes.

#ifdef BREAKPOINT_TARGET_AFTER_MK
    printf ("#breakpoint: after init_microkernel");
    die();
#endif

    return TRUE;
}

