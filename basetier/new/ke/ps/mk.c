
// ps/mk.c


#include <kernel.h> 


// Called by I_init().

int init_microkernel (void)
{
    int Status = FALSE;

    debug_print ("init_microkernel:\n");

//#ifdef KERNEL_VERBOSE
    //printf ("MICROKERNEL:\n");
//#endif

    // Init scheduler.
    // See: sched/sched.c

    init_scheduler(0);


    // Init processes, threads, 
    // See: process.c and thread.c

    init_processes();
    init_threads();    

    // Init IPC and Semaphore.
    // See: ??

    //ipc_init ();
    //create_semaphore(); 

//
// queue
//
    // #deprecated

    queue = NULL;


/*
    // Inicializar as filas que alimentar�o a lista do dispatcher.

    queue = kmalloc ( sizeof( struct queue_d ) );

    if( (void *) queue == NULL ){
        panic ("init_microkernel: queue\n");
    }else{

        // Inicializa todas as filas do microkernel.
        init_queue(queue);

        // Initializing the dispatcher list.
        // See: disp/dispatch.c
        //init_dispatcher();

        // ...
    };
*/


    // ...


//
// Dispatch Count Block
//
    DispatchCountBlock = (void *) kmalloc ( sizeof( struct dispatch_count_d ) );

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



//#ifdef PS_VERBOSE
    //printf ("Done\n");
//#endif


#ifdef BREAKPOINT_TARGET_AFTER_MK
    //#debug 
	//a primeira mensagem só aparece após a inicialização da runtime.
	//por isso não deu pra limpar a tela antes.
    printf (">>>debug hang: after init_microkernel");
    die();
#endif

    Initialization.microkernel = TRUE;

    return TRUE;
}


// Se o processo ou thread estiver em background o retorno será -1
// indicando que ele não pode pegar input de teclado.

int jobcheck ( int type, int id )
{
    struct process_d  *p;
    struct thread_d   *t;

    switch(type){
    case PROCESS:  goto do_process;  break;
    case THREAD:   goto do_thread;   break;
    default:
        goto fail;
        break;
    };

do_process:	
    if( id <0 || id >= PROCESS_COUNT_MAX ){
		goto fail;
	}else{

		p = (struct process_d*) processList[id];
		if( (void*) p == NULL ){
			goto fail;
		}else{
			
			if( p->used != 1 || p->magic != 1234 ){
				goto fail;
			}
			
			//Pode pegar input de teclado
			if( p->plane == FOREGROUND ){
				goto done;;
			//Está impedido de pegar input de teclado.
			}else{
				goto done;
			};
		};	
		
	};
	
do_thread:
    if( id <0 || id >= THREAD_COUNT_MAX ){
		goto fail;
	}else{
	
		t = (struct thread_d*) threadList[id];
		if( (void*) t == NULL ){
			goto fail;
		}else{
			
			if( t->used != 1 || t->magic != 1234 ){
				goto fail;
			}
			
			//Pode pegar input de teclado
			if( t->plane == FOREGROUND ){
				goto done;;
			//Está impedido de pegar input de teclado.
			}else{
				goto done;
			};
		};
	
	};

fail:
    return (int) -1;

done:
    return 0;
}


// Coloca um processo ou thread em um dos planos de execução

int jobcontrol ( int type, int id, int plane ){

    struct process_d  *p;
    struct thread_d   *t;

    switch (type){
    case PROCESS: goto do_process; break;
    case THREAD:  goto do_thread;  break;
    default:
       goto fail;
       break;
    };

    goto fail;

do_process:

    if ( id <0 || id >= PROCESS_COUNT_MAX )
    {
        goto fail;
    }else{

        p = (struct process_d*) processList[id];

        if ( (void*) p == NULL )
        {
            goto fail;
        }else{

			if ( p->used != 1 || p->magic != 1234 ){
				goto fail;
			}

			if( plane == FOREGROUND ){
			    p->plane = (int) plane;
			}else{
				//Default
				p->plane = (int) BACKGROUND;
			};
			goto done;
		};
    };

do_thread:

    if( id <0 || id >= THREAD_COUNT_MAX ){
		goto fail;
	}else{
		
		t = (struct thread_d*) threadList[id];
		if( (void*) t == NULL ){
			goto fail;
		}else{
			
			if( t->used != 1 || t->magic != 1234 ){
				goto fail;
			}
			if( plane == FOREGROUND ){
			    t->plane = (int) plane;	
			}else{
				//Default
				t->plane = (int) BACKGROUND;
			};
			goto done;
		};
	};	


fail:
    debug_print("jobcontrol: [FAIL] \n");
    return (int) -1;
done:
    return (int) 0;	
}








