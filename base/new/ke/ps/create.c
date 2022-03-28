

#include <kernel.h>  


// create_tid0:
//     This is the control thread of the window server.
//     See: gwssrv.bin.
// 0x0000000030A00000
void *create_tid0(void)
{

    struct thread_d  *kThread;
    int TID = WS_TID;

    // loops
    register int r=0;    // Wait reason.
    register int i=0;    // Message queue.
    register int q=0;    // Message queue.

    char *ThreadName = "ws-thread";

    // Stack pointer.
    void *earlyRing0IdleStack; 


    debug_print ("create_tid0:\n");


    debug_print ("[1]\n");
    // The kernel process.
    if ( (void *) KernelProcess == NULL )
    {
        debug_print ("create_tid0: KernelProcess\n");
        panic       ("create_tid0: KernelProcess\n");
    }

    // ??
    // e a validade da estrutura de processo? 


    // Struct.
    // Começamos a inicializaçao da estrtutura.

    debug_print ("[2]\n");

    kThread = (void *) kmalloc ( sizeof(struct thread_d) );

    if ( (void *) kThread == NULL ){
        debug_print ("create_tid0: kThread\n");
        panic       ("create_tid0: kThread\n");
    }

    kThread->objectType  = ObjectTypeThread;
    kThread->objectClass = ObjectClassKernelObjects;
    kThread->type = THREAD_TYPE_SYSTEM; 
    kThread->surface_rect = NULL;

    // #todo
    // #important
    // This will affect the input model

//
// Input
//

 // #suspenso. Vamos usar as flags em 't->input_flags'
    //kThread->input_model = THREAD_INPUTMODEL_KERNEL;

    kThread->input_flags = (unsigned long) (INPUT_MODEL_STDIN | INPUT_MODEL_MESSAGEQUEUE );



    kThread->position = KING;


//
// TID
//

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

    // #todo
    // Execution plane.

    kThread->plane = BACKGROUND;    

    // ...


    // Stack.

    // #bugbug
    // estamos alocando uma stack dentro do heap do kernel.
    // nesse caso serve para a thread idle em ring 0.
    // 8KB

    debug_print ("[3]\n");

    int StackSize = (8*1024);

    earlyRing0IdleStack = (void *) kmalloc (StackSize);

    if ( (void *) earlyRing0IdleStack == NULL ){
        debug_print ("create_tid0: earlyRing0IdleStack\n");
        panic       ("create_tid0: earlyRing0IdleStack\n");
    }

    // #todo
    // Clear stack

    // Page Directory
    //kThread->DirectoryPA = (unsigned long ) KernelProcess->DirectoryPA;
    //if ( kThread->DirectoryPA == 0 ){
    //    panic("create_CreateEarlyRing0IdleThread: kThread->DirectoryPA\n");
    //}

    debug_print ("[4]\n");

    // pml4 physical address
    kThread->pml4_PA = (unsigned long ) KernelProcess->pml4_PA;
    if ( kThread->pml4_PA == 0 ){
        debug_print ("create_tid0: kThread->pml4_PA\n");
        panic       ("create_tid0: kThread->pml4_PA\n");
    }


// Clean the 'wait reason'.
    for ( r=0; r<8; ++r ){ kThread->wait_reason[r] = (int) 0; };

    // ??
    // The system window procedure used by this thread.
    // This is a dialog inside the base kernel.

    // #suspended  Gramado X will not use this for now.
    // kThread->procedure = (unsigned long) &system_procedure;

//
// == message support =============
//

// Single kernel event
    kThread->ke_window = NULL;
    kThread->ke_msg    = 0;
    kThread->ke_long1  = 0;
    kThread->ke_long2  = 0;
    kThread->ke_newmessageFlag =  FALSE;


/*
// ===========================================================
// Message queue
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
// ===========================================================
*/

// ===========================================================
// Message queue.
    for ( q=0; q<32; ++q ){ kThread->MsgQueue[q] = 0; }
    kThread->MsgQueueHead = 0;
    kThread->MsgQueueTail = 0;


// Create all the 32 pointers.
    struct msg_d  *tmp;

    for ( i=0; i<32; ++i )
    {
        tmp = (struct msg_d *) kmalloc( sizeof( struct msg_d ) );
        if( (void*) tmp == NULL )
            panic("create_tid0: tmp");

        tmp->window = NULL;
        tmp->msg = 0;
        tmp->long1 = 0;
        tmp->long2 = 0;
        tmp->long3 = 0;
        tmp->long4 = 0;

        tmp->used = TRUE;
        tmp->magic = 1234;
        
        // Coloca o ponteiro que criamos na lista de ponteiros.
        kThread->MsgQueue[i] = (unsigned long) tmp;
    }

// =================================================



// Priorities
// This is a ring0 thread, only used for sti/hlt.
// Maybe it is gonna be a idle thread to manage the energy.
    kThread->base_priority = PRIORITY_MIN;    // Static
    kThread->priority      = PRIORITY_MIN;    // Dynamic

// Pode sofrer preempção por tempo.
    kThread->preempted = PREEMPTABLE;


// Temporizadores.
// Counters

    kThread->step = 0;

    kThread->quantum           = QUANTUM_MIN;
    kThread->quantum_limit_min = QUANTUM_MIN;
    kThread->quantum_limit_max = QUANTUM_MAX;
    
    kThread->standbyCount = 0;

    kThread->runningCount = 0;
    kThread->runningCount_ms = 0;

    kThread->readyCount  = 0;
    kThread->ready_limit = READY_LIMIT;

    kThread->waitingCount  = 0;
    kThread->waiting_limit = WAITING_LIMIT;

    kThread->blockedCount  = 0;
    kThread->blocked_limit = BLOCKED_LIMIT;

    kThread->ticks_remaining = 1000;

    kThread->initial_time_ms = get_systime_ms();
    kThread->total_time_ms = 0;

// Unix signal support.
    kThread->signal = 0;
    kThread->umask = 0;

// #obs: 
// Essa parte eh dependente da arquitetura, 
// deveria estar em uma pasta, por exemplo, x86/.
    // if(MachineType == i386Type){...};
    //

// x86_64 Context:
// Isso deve ir para uma estrutura de contexto.
// Obs: rflags 0x0202.
// Queremos que esse thread rode em ring0.
// WS_ENTRYPOINT_VA

// Stack frame
    kThread->ss     = 0x10 | 0; 
    kThread->rsp    = (unsigned long) ( earlyRing0IdleStack + (8*1024) );  //Stack
    kThread->rflags = 0x0202;    // # Atenção !!  
    kThread->cs     = 0x8 | 0; 
    kThread->rip    = (unsigned long) 0x30A01000; //SMALLSYSTEM_EXTRAHEAP3_START+ 0x1000;  

    kThread->initial_rip = (unsigned long) kThread->rip; 

    kThread->ds = 0x10 | 0;
    kThread->es = 0x10 | 0;
    kThread->fs = 0x10 | 0;
    kThread->gs = 0x10 | 0;
    
    kThread->rax = 0;
    kThread->rbx = 0;
    kThread->rcx = 0;
    kThread->rdx = 0;

    kThread->rsi = 0;
    kThread->rdi = 0;
    kThread->rbp = 0;
    // ...

    kThread->r8 = 0;
    kThread->r9 = 0;
    kThread->r10 = 0;
    kThread->r11 = 0;
    kThread->r12 = 0;
    kThread->r13 = 0;
    kThread->r14 = 0;
    kThread->r15 = 0;



    kThread->saved = FALSE;

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


// This function is wrong .... 
// Maybe it is putting values outside the vector.

    //debug_print ("create_tid0: [FIXME] Overflow in queue_insert_data() \n");


//
// #bugbug      OVERFLOW !!!!!
//
    
    //queue_insert_data ( 
    //    queue, 
    //    (unsigned long) kThread, 
    //    QUEUE_INITIALIZED );


//
// == Select for execution ================
//

    debug_print ("[5]\n");


    kThread->used  = TRUE;
    kThread->magic = 1234;


// #todo
// This method really need a prefix.

// With this movement, this thread is gonna run in the next
// task switch.
// :::: MOVEMENT 1 (Initialized --> Standby).

    SelectForExecution(kThread); 

// Done
    debug_print ("create_tid0: done\n");

    return (void *) kThread;
}


// 0x0000000030C00000
void *create_tid1 (void)
{
    return NULL;
}

// 0x0000000030E00000
void *create_tid2 (void)
{
    return NULL;
}

// ==================================================
// create_tid3:
// The control thread of the first ws's client.
// See: gws.bin

void *create_tid3 (void)
{
    struct thread_d  *t;
    int TID = (int)(INIT_TID & 0xFFFF);

    // loops
    register int r=0;    // Wait reason.
    register int i=0;    // Message queue.
    register int q=0;    // Message queue.

    char *ThreadName = "Ring3InitThread";

    // Stack pointer.
    void *__initStack;   


    debug_print ("create_tid3:\n");


    // The init process.

    if ( (void *) InitProcess == NULL ){
        panic ("create_tid3: InitProcess\n");
    }

    // ??
    // e a validade da estrutura de processo? 

    // Struct.

    t = (void *) kmalloc( sizeof(struct thread_d) );

    if ( (void *) t == NULL ){
        panic ("create_tid3: t\n");
    } 

    // #todo
    // Object header.

    // #todo
    // #bugbug
    // We need to review that thing!

//
// TID
//

    t->tid = (int) (TID & 0xFFFF);

    // #bugbug: 
    // Is this a valid pointer?
    // is this a valid pid?

    t->ownerPID  = (int) InitProcess->pid; 
    t->process   = (void *) InitProcess;

    t->name_address = (unsigned long) ThreadName; 

    t->position = SPECIAL_GUEST;

    t->iopl  = RING3; 
    t->type  = THREAD_TYPE_IDLE;
    t->state = INITIALIZED;

    // Execution plane.
    t->plane = BACKGROUND;


    t->surface_rect = NULL;

    // ...

    t->input_flags = (unsigned long) (INPUT_MODEL_STDIN | INPUT_MODEL_MESSAGEQUEUE );

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

    // #bugbug
    // Essa stack está em ring0.
    // Se o processo precisa de uma stack em ring 0 então usaremos essa.

    __initStack = (void *) kmalloc (8*1024);

    if ( (void *) __initStack == NULL ){
        panic ("create_tid3: __initStack\n");
    }

//
// pml4
//

    // pml4 physical address
    t->pml4_PA = (unsigned long ) InitProcess->pml4_PA;
    if ( t->pml4_PA == 0 ){
        panic("create_tid3: t->pml4_PA\n");
    }

    // Clean the 'wait reason'.
    for ( r=0; r<8; ++r ){ t->wait_reason[r] = (int) 0; };

    // ??
    // The system window procedure used by this thread.
    // This is a dialog inside the base kernel.

    //t->procedure = (unsigned long) &system_procedure;


//
// == Message =========
//

    // Single kernel event.

    t->ke_window = NULL;
    t->ke_msg    = 0;
    t->ke_long1  = 0;
    t->ke_long2  = 0;

    t->ke_newmessageFlag =  FALSE;


/*
//====================
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
//====================
*/


// ===============================
// Message queue.

    for ( q=0; q<32; ++q ){ t->MsgQueue[q] = 0; };
    t->MsgQueueHead = 0;
    t->MsgQueueTail = 0;

// Create all the 32 pointers.
    struct msg_d  *tmp;

    for ( i=0; i<32; ++i )
    {
        tmp = (struct msg_d *) kmalloc( sizeof( struct msg_d ) );
        if( (void*) tmp == NULL )
            panic("create_tid3: tmp");

        tmp->window = NULL;
        tmp->msg = 0;
        tmp->long1 = 0;
        tmp->long2 = 0;
        tmp->long3 = 0;
        tmp->long4 = 0;

        tmp->used = TRUE;
        tmp->magic = 1234;
        
        // Coloca o ponteiro que criamos na lista de ponteiros.
        t->MsgQueue[i] = (unsigned long) tmp;
    }
// ============================================


    // Priorities.
    // The idle thread has the lowest priority possible.

    t->base_priority = PRIORITY_MIN;    // Static
    t->priority      = PRIORITY_MIN;    // Dynamic

    t->preempted = UNPREEMPTABLE; 

// Temporizadores.

    // Jiffies
    t->step = 0; 

    t->quantum           = QUANTUM_MIN;
    t->quantum_limit_min = QUANTUM_MIN;
    t->quantum_limit_max = QUANTUM_MAX;

    t->standbyCount = 0;

    t->runningCount = 0;
    t->runningCount_ms = 0;

    t->readyCount  = 0;
    t->ready_limit = READY_LIMIT;

    t->waitingCount  = 0;
    t->waiting_limit = WAITING_LIMIT;

    t->blockedCount  = 0;    //Tempo bloqueada.
    t->blocked_limit = BLOCKED_LIMIT;

    t->ticks_remaining = 1000;

    t->initial_time_ms = get_systime_ms();
    t->total_time_ms   = 0;

// Signal
    t->signal = 0;
    t->umask  = 0;

    //
    // #obs: 
    // Essa parte eh dependente da arquitetura, 
    // deveria estar em uma pasta, por exemplo, x86/.
    // if(MachineType == i386Type){...};
    //


//
// == Context ===================
//

    // #todo: 
    // Isso deve ser uma estrutura de contexto.

    // #
    // 0x3200 é o estado inicial de eflags.
    // Existe um spawn especial para essa thread,
    // onde eflags inicia com o valor 0x3000.
    // See: x86init.c


// Stack frame.
// See: gva.h
    t->ss     = 0x23;
    t->rsp    = (unsigned long) CONTROLTHREAD_STACK; 
    t->rflags = 0x3202;    // #atenção! Change to 0x3202
    t->cs     = 0x1B;
    t->rip    = (unsigned long) CONTROLTHREAD_ENTRYPOINT; 

    t->ds = 0x23;  
    t->es = 0x23;
    t->fs = 0x23;
    t->gs = 0x23;

    t->rax = 0;
    t->rbx = 0;
    t->rcx = 0;
    t->rdx = 0;

    t->rsi = 0;
    t->rdi = 0;
    t->rbp = 0;
    // ...

    t->r8 = 0;
    t->r9 = 0;
    t->r10 = 0;
    t->r11 = 0;
    t->r12 = 0;
    t->r13 = 0;
    t->r14 = 0;
    t->r15 = 0;


    // O endereço incial, para controle.
    t->initial_rip = (unsigned long) t->rip; 

    t->saved = FALSE; 

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



    //debug_print ("create_CreateRing3InitThread: [FIXME] Overflow\n");
 
    // #bugbug
	// N�o h� a necessidade de colocar na fila de inicializadas
	// se logo em seguida estamos selecionando para execu��o 
	// colocando no estado standby.

//
// #bugbug: Overflow
//

    //queue_insert_data ( queue, (unsigned long) t, QUEUE_INITIALIZED );


    t->used  = TRUE;
    t->magic = 1234;


// == Execution ===============================
// #todo
// This method really need a prefix.
// :::: MOVEMENT 1 ( Initialized ---> Standby ).

    SelectForExecution(t);    

    debug_print ("create_tid3: done\n");

    return (void *) t;
}


//
// End.
//





