
// create.c

#include <kernel.h>  

// ==================================================
// create_init_thread:
// The control thread of the first ring3 process.
// This is the init thread.

struct thread_d *create_init_thread (void)
{
    struct thread_d *t;
// This is the first thread.
// See: thread.h
    tid_t TID = (tid_t) INIT_TID;
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

    t->objectType  = ObjectTypeThread;
    t->objectClass = ObjectClassKernelObjects;
    t->personality = (int) PERSONALITY_GRAMADO;

    t->exit_in_progress = FALSE;

// INIT process control thread.
// type: system
// priority: low

    t->type = THREAD_TYPE_SYSTEM;
    t->base_priority = PRIORITY_SYSTEM_THRESHOLD;  // Static
    t->priority      = PRIORITY_SYSTEM_THRESHOLD;  // Dynamic

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

    t->owner_process = (void *) InitProcess;
    t->owner_pid = (pid_t) InitProcess->pid; 

    t->name_address = (unsigned long) ThreadName; 

    t->state = INITIALIZED;

    // Execution plane.
    t->plane = BACKGROUND_THREAD;


    t->surface_rect = NULL;

    // ...

    t->input_mode = IM_MESSAGE_INPUT;


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


// Stack. @todo: A stack deve ser a que est� na TSS
// #BugBug.
// Estamos alocando mas n�o etamos usando.
// #podemos usar o alocador de p�ginas e alocar uma p�gina para isso.
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
    //for ( r=0; r<8; ++r ){ t->wait_reason[r] = (int) 0; };

    t->flags = 0;

//
// == Message =========
//

// ===============================
// Message queue.

    for ( q=0; q<MSG_QUEUE_MAX; ++q ){ t->MsgQueue[q] = 0; };
    t->MsgQueueHead = 0;
    t->MsgQueueTail = 0;

// Allocate memory for all the 32 structures.
// Add the pointers in the list.

    struct msg_d  *tmp;

    for ( i=0; i<MSG_QUEUE_MAX; ++i )
    {
        tmp = (struct msg_d *) kmalloc( sizeof( struct msg_d ) );
        if ( (void*) tmp == NULL ){
            debug_print("create_tid3: tmp\n");
            panic      ("create_tid3: tmp\n");
        }
        
        tmp->opaque_window = NULL;
        tmp->msg = 0;
        tmp->long1 = 0;
        tmp->long2 = 0;
        
        tmp->long3 = 0;
        tmp->long4 = 0;
        tmp->used = TRUE;
        tmp->magic = 1234;
        t->MsgQueue[i] = (unsigned long) tmp;
    };
// ============================================

// Pode sofrer preempção por tempo.
    t->is_preemptable = PREEMPTABLE;

// Temporizadores.

    // Jiffies
    t->step = 0; 

    t->quantum           = QUANTUM_NORMAL_THRESHOLD;
    t->quantum_limit_min = QUANTUM_MIN;
    t->quantum_limit_max = QUANTUM_MAX;

    t->standbyCount = 0;

    t->runningCount = 0;
    t->runningCount_ms = 0;

    t->readyCount  = 0;
    t->ready_limit = QUANTUM_MAX;

    t->waitingCount  = 0;
    t->waiting_limit = QUANTUM_MAX;

    t->blockedCount  = 0;    //Tempo bloqueada.
    t->blocked_limit = QUANTUM_MAX;

    t->ticks_remaining = 1000;

    t->initial_time_ms = get_systime_ms();
    t->total_time_ms   = 0;

// Signal
    t->signal = 0;
    t->umask  = 0;

    t->yield_in_progress =  FALSE;
    t->sleep_in_progress =  FALSE;
    t->desired_sleep_ms = 0;

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
// cpl and iopl
// #bugbug: weak protection for threads in ring 3.
// 0x3202
// Os processos em ring 3 chamam uma interrupção especial
// que mudam seu iopl para 0. int 199.

    t->cpl = (unsigned int) RING3;
    t->rflags_initial_iopl = (unsigned int) 3; 
    t->rflags_current_iopl = (unsigned int) 3; 

    t->ss     = 0x23;
    t->rsp    = (unsigned long) CONTROLTHREAD_STACK; 
    t->rflags = 0x3202;
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

// Conductor
// #todo
// We can use a method in the scheduler for this.

    //rootConductor = (struct thread_d *) t;

// counter
// #importante
// Contador de threads
// Vamos atualizar o contador de threads, 
// pois mais uma thread existe, mesmo que n�o esteja rodando ainda.
// #importante 
// nesse caso o contador foi configurado manualmente. 
// isso acontece com as threads do gramado core.
// #importante
// A cria��o da thread idle vai inicializar o contador,
// para depois s� incrementarmos.


// Usado pelo scheduler.
// See: sched.c
    Conductor = (struct thread_d *) t;

// The Idle thread for this processor.
    UPProcessorBlock.IdleThread = (struct thread_d *) t;

// The Next thread for this processor.
    UPProcessorBlock.NextThread = (struct thread_d *) t;

// The thread counter for this processor.
// This is the first thread.
    UPProcessorBlock.threads_counter = (int) 1; // :)

//
// == Queue =====================================
//
 
    // #bugbug
	// N�o h� a necessidade de colocar na fila de inicializadas
	// se logo em seguida estamos selecionando para execu��o 
	// colocando no estado standby.

//
// #bugbug: Overflow
//

    //queue_insert_data ( queue, (unsigned long) t, QUEUE_INITIALIZED );

    t->used = TRUE;
    t->magic = 1234;


// == Execution ===============================
// #todo
// This method really need a prefix.
// :::: MOVEMENT 1 ( Initialized ---> Standby ).

    SelectForExecution(t);    

    //debug_print ("create_tid3: done\n");

    return (struct thread_d *) t;
}


//
// End.
//





