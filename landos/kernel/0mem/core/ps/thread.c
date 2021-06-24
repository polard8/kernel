

#include <kernel.h>

// Thread stats
unsigned long __GetThreadStats ( int tid, int index ){

    struct thread_d  *t;

    //#todo:
    //checar validade dos argumentos.
    
    // safety
    if ( tid < 0 || index < 0 )
    {
       return 0;
    }


    //Struct.
    t = (void *) threadList[tid];

    if ( (void *) t == NULL ){
        // ?? refresh
        printf ("__GetThreadStats: struct \n");
        return 0; 

    } else {
        // Checar validade
        // ...
    };

    // See: 
    // https://en.wikipedia.org/wiki/Processor_affinity
    // ...
 
    switch ( index ){

        case 1:  return (unsigned long) t->tid;  break;
        case 2:  return (unsigned long) t->ownerPID;  break; 
        case 3:  return (unsigned long) t->type;  break; 
        case 4:  return (unsigned long) t->state;  break; 
        case 5:  return (unsigned long) t->plane;  break; 
        case 6:  return (unsigned long) t->cpu;  break; 
        case 7:  return (unsigned long) t->affinity;  break;
        
        // #bugbug: repetido. 6.
        case 8:  return (unsigned long) t->cpu;  break;   
        
        case 9:  return (unsigned long) t->next_cpu;  break; 
        
        // #
        case 10:  
            //return (unsigned long) t->DirectoryPA; 
            return (unsigned long) t->pml4_PA;  
            break; 
        
        case 11:  return (unsigned long) t->iopl;  break; 
        case 12:  return (unsigned long) t->base_priority;  break; 
        case 13:  return (unsigned long) t->priority;  break;          

        case 14:
            return (unsigned long) 0;
            //return (unsigned long) t->pagefaultCount;
            break;          

        case 15:  return (unsigned long) t->preempted;  break;
        case 16:  return (unsigned long) t->saved;  break;
        case 17:  return (unsigned long) t->Heap;  break;
        case 18:  return (unsigned long) t->Stack;  break;
        case 19:  return (unsigned long) t->HeapSize;  break;
        case 20:  return (unsigned long) t->StackSize;  break;
        case 21:  return (unsigned long) t->step;  break;
        case 22:  return (unsigned long) t->initial_time_ms;  break;
        case 23:  return (unsigned long) t->total_time_ms;  break;
        case 24:  return (unsigned long) t->quantum;  break;
        case 25:  return (unsigned long) t->quantum_limit;  break;
        case 26:  return (unsigned long) t->standbyCount;  break;
        case 27:  return (unsigned long) t->runningCount;  break;
        case 28:  return (unsigned long) t->runningCount_ms;  break;
        case 29:  return (unsigned long) t->readyCount;  break;
        case 30:  return (unsigned long) t->ready_limit;  break;
        case 31:  return (unsigned long) t->waitingCount;  break;
        case 32:  return (unsigned long) t->waiting_limit; break;
        case 33:  return (unsigned long) t->blockedCount;  break;
        case 34:  return (unsigned long) t->blocked_limit;  break;
        case 35:  return (unsigned long) t->ticks_remaining;  break;
        
        case 36:  
            return (unsigned long) t->profiler_percentage_running;
            break;
            
        case 37:
            return (unsigned long) t->profiler_percentage_running_res;
            break;

        case 38:
            return (unsigned long) t->profiler_percentage_running_mod;
            break;
         
        case 39:
            return (unsigned long) t->profiler_ticks_running;
            break;

        case 40:
            return (unsigned long) t->profiler_last_ticks;
            break;

        case 41:  return (unsigned long) t->PreviousMode;  break;
        case 42:  return (unsigned long) t->signal;  break;
        case 43:  return (unsigned long) t->umask;  break;
        
        //#todo
        //default:
            //break;
    };

    return 0;
}

// Get thread name.
int getthreadname ( int tid, char *buffer )
{
    struct thread_d  *t;

    char *name_buffer = (char *) buffer;

    //#todo
    //checar validade dos argumentos.

    // safety
    if ( tid < 0  )
    {
       return 0;
    }

 
    t = (struct thread_d *) threadList[tid]; 

    if ( (void *) t == NULL ){
        // msg
        return -1;

    }else{
    
        if ( t->used != TRUE || t->magic != 1234 ){
            //msg
            return -1;
        }
        
        // 64 bytes
        strcpy ( name_buffer, (const char *) t->__threadname );       
        
        return (int) t->threadName_len;
    };

    return -1;
}

/*
 ************************
 * FindReadyThread:
 *     Pega a primeira thread READY que encontrar.
 *     E se não encontrar nenhuma, retorna NULL.
 */

// OUT:
// Return a pointer to the found thread.

void *FindReadyThread (void)
{
    register int i=0;
    struct thread_d *Thread;

    for ( i=0; i<THREAD_COUNT_MAX; ++i )
    {
        Thread = (void *) threadList[i];

        if ( (void *) Thread != NULL )
        {
            if ( Thread->used  == TRUE && 
                 Thread->magic == 1234 && 
                 Thread->state == READY )
            {
                return (void *) Thread;
            }
        }
    };

    // Nenhuma foi encontrada.   
    // #todo: Message ??

    return NULL;
}

// Get State 
// (Zero e' tipo NULL?).
int GetThreadState (struct thread_d *thread){

    if ( (void *) thread == NULL ){
        // Message
        return 0;   //#bugbug: This is a valid state.
    }

    return (int) thread->state;
}

// Get Type
// (Zero e' tipo NULL?).
int GetThreadType (struct thread_d *thread){

    if ( (void *) thread == NULL ){
        //Message
        return 0;   // #bugbug: This is a valid type.
    }
  
    return (int) thread->type;
}

/*
 *******************************************************
 * init_threads:
 *     Inicializa o thread manager.
 *     Inicializa as estruturas e vari�veis 
 *     que lidam com threads.
 */

// Called by init_microkernel in mk.c

int init_threads (void){

    int i=0;


    debug_print("init_threads:\n");

	//Globais.
	current_thread = 0;  //Atual. 
	
	//ProcessorBlock.threads_counter = (int) 0;  //N�mero de threads no processador.	
	UPProcessorBlock.threads_counter = (int) 0;  //N�mero de threads no processador.	
	
    old = 0;                                   //?
    forkid = 0;                                //
    task_count = (unsigned long) 0;            //Zera o contador de tarefas criadas.
	//...
	
	// @todo: Porque essas vari�veis usam o termo 'task'?
	//        task � sinonimo de process.
	
	//Vari�veis usadas na inicializa��o de uma nova tarefa.	
	start_new_task_status  = (unsigned long) 0;    //Se h� uma nova tarefa.
	start_new_task_id = (int) 0;                   //Id d� nova tarefa.
	start_new_task_address = (unsigned long) 0;    //Endere�o da nova tarefa.
	
	//@todo: H� mais vari�veis para serem inicializadas??!!


    // Clear thread list.
    i=0;
    while ( i < THREAD_COUNT_MAX ){
        threadList[i] = (unsigned long) 0; 
        i++;
    };


	//
	// @todo: Nada mais?
	//

    return 0;
}

/*
 *****************************
 * GetCurrentThreadId
 *     Pega o id da thread atual.
 */

int GetCurrentThreadId (void)
{
    return (int) current_thread;
}

/*
 * GetCurrentThread:
 *     Retorna o endere�o da estrutura da thread atual.
 */

void *GetCurrentThread (void){

    struct thread_d *Current;


    if (current_thread < 0 || 
        current_thread >= THREAD_COUNT_MAX )
    {
        return NULL;
    }

    Current = (void *) threadList[current_thread];

    if ( (void *) Current == NULL ){  return NULL; }

    return (void *) Current;
}

/*
 ********************************************************
 * SelectForExecution:
 *     Um thread entra em standby, sinalizando que está pronto 
 * para entrar em execução.
 * 
 *     Nesse caso, durante a rotina de taskswitch, checar-se-a se 
 * existe um thread em estado standby, caso haja, a thread é colocada 
 * pra executar pelo método spawn. 
 * Esse m�todo de spawn j� foi testado, segundo a contagem, duas thread 
 * come�aram a rodas atrav�s desse m�todo de spawn. 
 * Provavelmente as threads 'shell' e 'taskman', pois a thread 'idle' � 
 * chamada com um spawn exclusivo para ela, o que � desnecess�rio e 
 * poder� ser revisto. @todo
 *     
 *  *** MOVIMENTO 1, (Initialized --> Standby).
 */

void SelectForExecution ( struct thread_d *Thread ){


    if ( (void *) Thread == NULL){
        debug_print ("SelectForExecution: Thread fail\n");
        return;
    } 
    
    // #todo
    // Validation ??
    

	// @todo: if initialized ---> Standby.
	// @todo: if zombie ---> Standby.
	//
	// Talvez aqui seja necess�rio checar o estado da thread.
	// Quem pode entrar no estado standby??
	// >> Uma thread no estado initialized pode entrar no estado standby 
	// >> Uma thread no estado zombie pode entrar no estado standby.
	// >> @todo: se uma thread estiver em qualquer um dos outros estados ela 
	// n�o pode entrar em stadby.


//setState:
    
	//*MOVIMENTO 1, (Initialized --> Standby).
    
    Thread->state = (int) STANDBY;
    queue_insert_data ( queue, (unsigned long) Thread, QUEUE_STANDBY );
}








































