/*
 * File: ps/create.c
 *
 *   cria a thread idle do processo init;
 */

#include <kernel.h>


/*
 ******************************************************
 * KiCreateRing0Idle:
 *    Criando manualmente uma thread em ring 0.
 *    Para o processador ficar em hlt quando não tiver outra 
 * thread rodando.
 */

void *create_CreateRing0IdleThread(void)
{
    
    struct thread_d  *kThread;
    
    int TID = 0;


    // loops
    register int r=0;    // Wait reason.
    register int i=0;    // Message queue.
    register int q=0;    // Message queue.


    char *ThreadName = "Ring0IdleThread";

    // Stack pointer.
    void *ring0IdleStack; 


    // The kernel process.

    if ( (void *) KernelProcess == NULL ){
        panic ("create_CreateRing0IdleThread: KernelProcess\n");
    }

    // ??
    // e a validade da estrutura de processo? 


    // Struct.
    // Começamos a inicializaçao da estrtutura.

    kThread = (void *) kmalloc ( sizeof(struct thread_d) );

    if ( (void *) kThread == NULL ){
        panic ("create_CreateRing0IdleThread: kThread \n");
    }else{  

        // #todo
        // Object support.

        // Identificadores 

        kThread->used  = TRUE;
        kThread->magic = 1234;

        kThread->position = KING;

        kThread->tid = TID;

        // #bugbug: 
        // Is this a valid pointer?
        // is this a valid pid?
        kThread->ownerPID     = (int) KernelProcess->pid;
        
        kThread->name_address = (unsigned long) ThreadName; 
        kThread->process      = (void *) KernelProcess;

        // Características.
        kThread->iopl  = RING0;
        kThread->type  = THREAD_TYPE_SYSTEM; 
        kThread->state = INITIALIZED; 

        // Execution plane.
        kThread->plane = BACKGROUND;    

        // ...
    };


    // Stack.

    // #bugbug
    // estamos alocando uma stack dentro do heap do kernel.
    // nesse caso serve para a thread idle em ring 0.
    // 8KB

    ring0IdleStack = (void *) kmalloc (8*1024);

    if ( (void *) ring0IdleStack == NULL ){
        panic ("create_CreateRing0IdleThread: ring0IdleStack\n");
    }


    // Page Directory

    kThread->DirectoryPA = (unsigned long ) KernelProcess->DirectoryPA;

    if ( kThread->DirectoryPA == 0 ){
        panic("create_CreateRing0IdleThread: kThread->DirectoryPA\n");
    }

    // loop
    // Clean the 'wait reason'.
    for ( r=0; r<8; ++r ){ kThread->wait_reason[r] = (int) 0; };

    // ??
    // The system window procedure used by this thread.
    // This is a dialog inside the base kernel.

    kThread->procedure = (unsigned long) &system_procedure;

    //
    // == message support =============
    //

    // Single kernel event

    kThread->ke_window = NULL;
    kThread->ke_msg    = 0;
    kThread->ke_long1  = 0;
    kThread->ke_long2  = 0;

    kThread->ke_newmessageFlag =  FALSE;


    // loop
    // Message queue.  
    for ( i=0; i<32; ++i )
    {
        kThread->window_list[i] = 0;
        kThread->msg_list[i]    = 0;
        kThread->long1_list[i]  = 0;
        kThread->long2_list[i]  = 0;
        kThread->long3_list[i]  = 0;
        kThread->long4_list[i]  = 0;
    };
    kThread->head_pos = 0;
    kThread->tail_pos = 0;

    // loop
    // Message queue.
    for ( q=0; q<32; ++q ){ kThread->MsgQueue[q] = 0; }
    kThread->MsgQueueHead = 0;
    kThread->MsgQueueTail = 0;


    // Priorities.
    // This is a ring0 thread, only used for sti/hlt.
    // Maybe it is gonna be a idle thread to manage the energy.

    kThread->base_priority = PRIORITY_MIN;    // Static
    kThread->priority      = PRIORITY_MIN;    // Dynamic

    kThread->saved = FALSE;
    kThread->preempted = UNPREEMPTABLE;


    // Temporizadores.
    
    kThread->step = 0;
    

    // QUANTUM_BASE   (PRIORITY_NORMAL*TIMESLICE_MULTIPLIER)
    //kThread->quantum = QUANTUM_BASE;
    kThread->quantum  = ( kThread->priority * TIMESLICE_MULTIPLIER);
    
    // QUANTUM_LIMIT  (PRIORITY_MAX *TIMESLICE_MULTIPLIER)
    kThread->quantum_limit = QUANTUM_LIMIT;


    // Contadores.

    kThread->standbyCount = 0;
    kThread->runningCount = 0;  //Tempo rodando antes de parar.
    kThread->readyCount   = 0;  //Tempo de espera para retomar a execução.

    kThread->initial_time_ms = get_systime_ms();
    kThread->total_time_ms = 0;

    // Quantidade de tempo rodadndo dado em ms.
    kThread->runningCount_ms = 0;

    kThread->ready_limit = READY_LIMIT;
    kThread->waitingCount  = 0;
    kThread->waiting_limit = WAITING_LIMIT;
    kThread->blockedCount = 0;    //Tempo bloqueada.
    kThread->blocked_limit = BLOCKED_LIMIT;

    kThread->ticks_remaining = 1000;

    // Signal
    kThread->signal = 0;
    kThread->umask = 0;

    //
    // #obs: 
    // Essa parte eh dependente da arquitetura, 
    // deveria estar em uma pasta, por exemplo, x86/.
    // if(MachineType == i386Type){...};
    //

    // x86 Context.
    // Isso deve ir para uma estrutura de contexto.
    // Obs: eflags 0x0200.
    // Queremos que esse thread rode em ring0.

    // Stack frame.
    kThread->ss     = 0x10 | 0; 
    kThread->esp    = (unsigned long) ( ring0IdleStack + (8*1024) );  //Stack
    kThread->eflags = 0x0200;    // # Atenção !!  
    kThread->cs     = 8 | 0; 
    kThread->eip    = (unsigned long) ring0_IdleThread;  //See: main.c

    kThread->ds = 0x10 | 0;
    kThread->es = 0x10 | 0;
    kThread->fs = 0x10 | 0;
    kThread->gs = 0x10 | 0;
    
    kThread->eax = 0;
    kThread->ebx = 0;
    kThread->ecx = 0;
    kThread->edx = 0;

    kThread->esi = 0;
    kThread->edi = 0;
    kThread->ebp = 0;
    // ...

    // O endereço incial, para controle.
    kThread->initial_eip = (unsigned long) kThread->eip; 


	//#bugbug
	//Obs: As estruturas precisam já estar decidamente inicializadas.
	//kThread->root = (struct _iobuf *) file_root;
	//kThread->pwd  = (struct _iobuf *) file_pwd;	

	//CPU stuffs.
	//kThread->cpuID = 0;              //Qual processador.
	//kThread->confined = 1;           //Flag, confinado ou não.
	//kThread->CurrentProcessor = 0;   //Qual processador.
	//kThread->NextProcessor = 0;      //Próximo processador. 

    kThread->next = NULL;

    // Coloca na lista de estruturas.
    threadList[TID] = (unsigned long) kThread;

    //
    // == counter =================================
    //

	// #bugbug
	// Se deixarmos de criar alguma das threads esse contador falha.
	// #todo: Deveríamos apenas incrementá-lo.

    UPProcessorBlock.threads_counter++;

    //
    // == Queue =====================================
    //

    queue_insert_data ( 
        queue, 
        (unsigned long) kThread, 
        QUEUE_INITIALIZED );

    //
    // == Execution ===============================
    //

    // #todo
    // This method really need a prefix.
    
    // With this movement, this thread is gonna run in the next
    // task switch.
    
    // * MOVEMENT 1 (Initialized --> Standby).
    SelectForExecution(kThread); 

    return (void *) kThread;
}



/*
 *******************************************************************
 * createCreateInitThread:
 * 
 *     Criando init-thread manualmente.
 *     Essa eh a thread do processo init. (init.bin)
 */

// It has the lowest priority.
// ...

void *create_CreateRing3InitThread (void)
{

    struct thread_d  *t;
    int TID = 1;


    // loops
    register int r=0;    // Wait reason.
    register int i=0;    // Message queue.
    register int q=0;    // Message queue.

    char *ThreadName = "Ring3InitThread"; 

    // Stack pointer.
    void *__initStack;   

    // The init process.

    if ( (void *) InitProcess == NULL ){
        panic ("create_CreateRing3InitThread: InitProcess\n");
    }

    // ??
    // e a validade da estrutura de processo? 

    // Struct.

    t = (void *) kmalloc ( sizeof(struct thread_d) );

    if ( (void *) t == NULL ){
        panic ("create_CreateRing3InitThread: t\n");
    } else {
        if ( (void *) InitProcess == NULL ){
            panic ("create_CreateRing3InitThread: InitProcess\n");
        }else{

            // #todo
            // Object header.
            
            // Identificadores 
            
            t->used  = TRUE;
            t->magic = 1234;

            t->position = SPECIAL_GUEST;

            t->tid = TID;

            // #bugbug: 
            // Is this a valid pointer?
            // is this a valid pid?
            t->ownerPID     = (int) InitProcess->pid; 
            
            t->name_address = (unsigned long) ThreadName; 
            t->process      = (void *) InitProcess;
      
            // Caracteristicas.
            t->iopl  = RING3; 
            t->type  = THREAD_TYPE_IDLE;
            t->state = INITIALIZED;

            // Execution plane.
            t->plane = BACKGROUND;
            // ...
        };
        // ...
    };


	// @todo: 
	// #bugbug: #importante
	// A stack da idle n�o deve ficar no heap do kernel.
	// Pois a idle est� em user mode e deve ter sua stack 
	// em user mode para ter permiss�o de acesso.
	// Mas ficar� aqui por enquanto.
	// Obs: Mais abaixo a pilha foi configurada manualmente 
	// no lugar certo.
	
	//InitThread->Heap = ?;
	//InitThread->HeapSize = ?;
	//InitThread->Stack = ?;
	//InitThread->StackSize = ?;
	
	//Stack. @todo: A stack deve ser a que est� na TSS
	//#BugBug.
	// Estamos alocando mas n�o etamos usando.
	//# podemos usar o alocador de p�ginas e alocar uma p�gina para isso.

    // Stack.
    
    // #bugbug
    // Não estamos usando isso.
    // 8KB.

    __initStack = (void *) kmalloc (8*1024);

    if ( (void *) __initStack == NULL ){
        panic ("create_CreateRing3InitThread: __initStack\n");
    }

    // Page Directory

    t->DirectoryPA = (unsigned long ) InitProcess->DirectoryPA;
    
    if ( t->DirectoryPA == 0 ){
        panic("create_CreateRing3InitThread: t->DirectoryPA\n");
    }

    // loop
    // Clean the 'wait reason'.
    for ( r=0; r<8; ++r ){ t->wait_reason[r] = (int) 0; };

    // ??
    // The system window procedure used by this thread.
    // This is a dialog inside the base kernel.

    t->procedure = (unsigned long) &system_procedure;


    // Single kernel event.

    t->ke_window = NULL;
    t->ke_msg    = 0;
    t->ke_long1  = 0;
    t->ke_long2  = 0;

    t->ke_newmessageFlag =  FALSE;

    // loop
    // Clean the message queue.
    for ( i=0; i<32; ++i )
    {
        t->window_list[i] = 0;
        t->msg_list[i]    = 0;
        t->long1_list[i]  = 0;
        t->long2_list[i]  = 0;
        t->long3_list[i]  = 0;
        t->long4_list[i]  = 0;
    };
    t->head_pos = 0;
    t->tail_pos = 0;

    // loop
    // Message queue.
    for ( q=0; q<32; ++q ){ t->MsgQueue[q] = 0; };
    t->MsgQueueHead = 0;
    t->MsgQueueTail = 0;

    // Priorities.
    // The idle thread has the lowest priority possible.

    t->base_priority = PRIORITY_MIN;    // Static
    t->priority      = PRIORITY_MIN;    // Dynamic


    t->saved = 0; 
    t->preempted = UNPREEMPTABLE; 

    // Temporizadores.
    InitThread->step = 0; 
        
    //t->quantum  = QUANTUM_BASE;
    t->quantum  = ( t->priority * TIMESLICE_MULTIPLIER);

    // QUANTUM_LIMIT  (PRIORITY_MAX *TIMESLICE_MULTIPLIER)
    t->quantum_limit = QUANTUM_LIMIT;


    // Contadores.
    t->standbyCount = 0;
    t->runningCount = 0;  // Tempo rodando antes de parar.
    t->readyCount   = 0;  // Tempo de espera para retomar a execu��o.

    t->initial_time_ms = get_systime_ms();
    t->total_time_ms   = 0;

    // Quantidade de tempo rodando dado em ms.
    t->runningCount_ms = 0;

    t->ready_limit   = READY_LIMIT;
    t->waitingCount  = 0;
    t->waiting_limit = WAITING_LIMIT;
    t->blockedCount  = 0;    //Tempo bloqueada.
    t->blocked_limit = BLOCKED_LIMIT;

    t->ticks_remaining = 1000;

    // Signal
    t->signal = 0;
    t->umask  = 0;

    //
    // #obs: 
    // Essa parte eh dependente da arquitetura, 
    // deveria estar em uma pasta, por exemplo, x86/.
    // if(MachineType == i386Type){...};
    //


    // Context.
    
    // #todo: 
    // Isso deve ser uma estrutura de contexto.

    // #
    // 0x3200 é o estado inicial de eflags.
    // Existe um spawn especial para essa thread,
    // onde eflags inicia com o valor 0x3000.
    // See: x86init.c

    // Stack frame.

    t->ss     = 0x23; 
    t->esp    = (unsigned long) CONTROLTHREAD_STACK; 
    t->eflags = 0x3200;    // #atenção!
    t->cs     = 0x1B;  
    t->eip    = (unsigned long) CONTROLTHREAD_ENTRYPOINT; 

    t->ds = 0x23;
    t->es = 0x23;
    t->fs = 0x23;
    t->gs = 0x23;

    t->eax = 0;
    t->ebx = 0;
    t->ecx = 0;
    t->edx = 0;

    t->esi = 0;
    t->edi = 0;
    t->ebp = 0;
    // ...

    // O endereço incial, para controle.
    t->initial_eip = (unsigned long) t->eip; 


	//#bugbug
	//Obs: As estruturas precisam j� estar devidamente inicializadas.
	//IdleThread->root = (struct _iobuf *) file_root;
	//IdleThread->pwd  = (struct _iobuf *) file_pwd;

	
	//CPU configuration.
	//IdleThread->cpuID = 0;              //Qual processador.
	//IdleThread->confined = 1;           //Flag, confinado ou n�o.
	//IdleThread->CurrentProcessor = 0;   //Qual processador.
	//IdleThread->NextProcessor = 0;      //Pr�ximo processador. 

    t->next = NULL;
    
    // Coloca na lista de estruturas.
    threadList[TID] = (unsigned long) t;


    //
    // == Conductor ===================================
    //

    // #todo
    // We can use a method in the scheduler for this.

    rootConductor = (struct thread_d *) t;


    //
    // == counter =================================
    //


    // #importante
    // Contador de threads
    // Vamos atualizar o contador de threads, 
    // pois mais uma thread existe, mesmo que n�o esteja rodando ainda.

	//#importante 
	//nesse caso o contador foi configurado manualmente. 
	//isso acontece com as threads do gramado core.

	// #importante
	// A cria��o da thread idle vai inicializar o contador,
	// para depois s� incrementarmos.
	
    //ProcessorBlock.threads_counter = (int) 1;
    UPProcessorBlock.threads_counter++;


    //
    // == Queue =====================================
    //
 
 
    // #bugbug
	// N�o h� a necessidade de colocar na fila de inicializadas
	// se logo em seguida estamos selecionando para execu��o 
	// colocando no estado standby.
    
    queue_insert_data ( queue, (unsigned long) t, QUEUE_INITIALIZED );


    // == Execution ===============================
    // #todo
    // This method really need a prefix.
    // * MOVEMENT 1 ( Initialized ---> Standby ).
    
    SelectForExecution(t);    

    return (void *) t;
}


//
// End.
//

