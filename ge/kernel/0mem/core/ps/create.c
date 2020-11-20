/*
 * File: ps/create.c
 *
 *   cria a thread idle do processo init;
 */

 
#include <kernel.h>

 

/*
 *******************************************************************
 * createCreateInitThread:
 * 
 *     Criando init-thread manualmente.
 *     Essa eh a thread do processo init. (init.bin)
 */

// It has the lowest priority.
// ...

void *createCreateInitThread (void)
{

    // loops
    register int r=0;    // Wait reason.
    register int i=0;    // Message queue.
    register int q=0;    // Message queue.

    char *ThreadName = "init-thread"; 

    // Stack pointer.
    void *__initStack;   


    // The init process.
    if ( (void *) InitProcess == NULL ){
            panic ("createCreateInitThread: InitProcess\n");
    }

    // ??
    // e a validade da estrutura de processo? 

    // Struct.

    InitThread = (void *) kmalloc ( sizeof(struct thread_d) );

    if ( (void *) InitThread == NULL ){
        panic ("createCreateInitThread: InitThread\n");

    } else {

        // Validation.
        if ( (void *) InitProcess == NULL ){
            panic ("createCreateInitThread: InitProcess\n");

        }else{

            // ??
            // e a validade da estrutura de processo? 

            //Indica a qual processo a thread pertence.
            InitThread->process = (void *) InitProcess;
       
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
        panic ("createCreateInitThread: __initStack\n");
    }


	// #todo: 
	// Eh poss�vel usar a fun��o create_thread nesse momento.
	// Mas � mais veloz fazer o m�ximo em uma fun��o s�.
	// Mas por enquanto ser�o feitas � m�o essas primeiras threads. 

	// #todo: 
	// objectType, objectClass, appMode


    InitThread->used = 1;
    InitThread->magic = 1234;

    InitThread->tid = 1;
    InitThread->ownerPID = (int) InitProcess->pid; 

    InitThread->name_address = (unsigned long) ThreadName; 

    // Obs: 
    // Já fizemos isso no início da rotina.
    InitThread->process = (void *) InitProcess;

    // Execution plane.
    InitThread->plane = BACKGROUND;

    // Page Directory

    InitThread->DirectoryPA = (unsigned long ) InitProcess->DirectoryPA;
    
    if ( InitThread->DirectoryPA == 0 ){
        panic("createCreateInitThread: InitThread->DirectoryPA\n");
    }

    // loop
    // Clean the 'wait reason'.
    for ( r=0; r<8; ++r ){ InitThread->wait_reason[r] = (int) 0; };

    // ??
    // The system window procedure used by this thread.
    // This is a dialog inside the base kernel.

    InitThread->procedure = (unsigned long) &system_procedure;


    // Single message;
    //Argumentos do procedimento de janela.	
    InitThread->window = NULL; //window;//arg1.
    InitThread->msg   = 0;     //arg2.
    InitThread->long1 = 0;     //arg3.
    InitThread->long2 = 0;     //arg4.
    //InitThread->long
    //InitThread->long
    //...

    // loop
    // Clean the message queue.
    for ( i=0; i<32; ++i )
    {
        InitThread->window_list[i] = 0;
        InitThread->msg_list[i]    = 0;
        InitThread->long1_list[i]  = 0;
        InitThread->long2_list[i]  = 0;
        InitThread->long3_list[i]  = 0;
        InitThread->long4_list[i]  = 0;
    };
    InitThread->head_pos = 0;
    InitThread->tail_pos = 0;

    // loop
    // Message queue.
    for ( q=0; q<32; ++q ){ InitThread->MsgQueue[q] = 0; };
    InitThread->MsgQueueHead = 0;
    InitThread->MsgQueueTail = 0;


    // Caracteristicas.
    InitThread->type = TYPE_IDLE;    //TYPE_SYSTEM.
    InitThread->iopl = RING3;        //Idle thread � uma thread de um processo em user mode.
    InitThread->state = INITIALIZED;   

    // Priorities.
    // The idle thread has the lowest priority possible.

    InitThread->base_priority = PRIORITY_MIN;    // Static
    InitThread->priority      = PRIORITY_MIN;    // Dynamic


    InitThread->saved = 0; 
    InitThread->preempted = UNPREEMPTABLE; 

    // Temporizadores.
    InitThread->step = 0; 
        
    //InitThread->quantum  = QUANTUM_BASE;
    InitThread->quantum  = ( InitThread->priority * TIMESLICE_MULTIPLIER);

    // QUANTUM_LIMIT  (PRIORITY_MAX *TIMESLICE_MULTIPLIER)
    InitThread->quantum_limit = QUANTUM_LIMIT;


    // Contadores.
    InitThread->standbyCount = 0;
    InitThread->runningCount = 0;    //Tempo rodando antes de parar.
    InitThread->readyCount = 0;      //Tempo de espera para retomar a execu��o.

    InitThread->initial_time_ms = get_systime_ms ();
    InitThread->total_time_ms = 0;

    // Quantidade de tempo rodando dado em ms.
    InitThread->runningCount_ms = 0;

    InitThread->ready_limit = READY_LIMIT;
    InitThread->waitingCount  = 0;
    InitThread->waiting_limit = WAITING_LIMIT;
    InitThread->blockedCount = 0;    //Tempo bloqueada.
    InitThread->blocked_limit = BLOCKED_LIMIT;

    InitThread->ticks_remaining = 1000;

    // Signal
    InitThread->signal = 0;
    InitThread->umask = 0;

    //
    // #obs: 
    // Essa parte eh dependente da arquitetura, 
    // deveria estar em uma pasta, por exemplo, x86/.
    // if(MachineType == i386Type){...};
    //


    // Context.
    
    // #todo: 
    // Isso deve ser uma estrutura de contexto.

    // Stack frame.

    InitThread->ss     = 0x23; 
    InitThread->esp    = (unsigned long) CONTROLTHREAD_STACK; 
    InitThread->eflags = 0x3200;    // #atencao!
    InitThread->cs     = 0x1B;  
    InitThread->eip    = (unsigned long) CONTROLTHREAD_ENTRYPOINT; 

    InitThread->ds = 0x23;
    InitThread->es = 0x23;
    InitThread->fs = 0x23;
    InitThread->gs = 0x23;

    InitThread->eax = 0;
    InitThread->ebx = 0;
    InitThread->ecx = 0;
    InitThread->edx = 0;

    InitThread->esi = 0;
    InitThread->edi = 0;
    InitThread->ebp = 0;
    // ...

    // O endereço incial, para controle.
    InitThread->initial_eip = (unsigned long) InitThread->eip; 


	//#bugbug
	//Obs: As estruturas precisam j� estar devidamente inicializadas.
	//IdleThread->root = (struct _iobuf *) file_root;
	//IdleThread->pwd  = (struct _iobuf *) file_pwd;

	
	//CPU configuration.
	//IdleThread->cpuID = 0;              //Qual processador.
	//IdleThread->confined = 1;           //Flag, confinado ou n�o.
	//IdleThread->CurrentProcessor = 0;   //Qual processador.
	//IdleThread->NextProcessor = 0;      //Pr�ximo processador. 

    InitThread->next = NULL;
    
    // Coloca na lista de estruturas.
    threadList[ InitThread->tid ] = (unsigned long) InitThread;


    //
    // == Conductor ===================================
    //

    // #todo
    // We can use a method in the scheduler for this.

    rootConductor = (struct thread_d *) InitThread;


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
    
    queue_insert_data ( queue, 
        (unsigned long) InitThread, QUEUE_INITIALIZED );


    //
    // == Execution ===============================
    //

    // #todo
    // This method really need a prefix.

    // * MOVEMENT 1 ( Initialized ---> Standby ).
    SelectForExecution (InitThread);    

    return (void *) InitThread;
}


//
// End.
//

