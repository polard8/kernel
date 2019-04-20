/*
 * File: create.c
 *
 * Cria as threads que serão usadas pelos servidores do ambiente system.
 * init/shell/taskman.
 *
 * Descrição:
 *     Rotinas de criação de processos e threads.
 *     Faz parte do Process Manager, parte fundamental 
 * do Kernel Base.
 *     ?? Criar, cria a estrutura. ??
 *     ?? Inicializar inicializa estrutura passada por 
 * argumento. ??
 *
 * @todo: 
 *     Separar as rotinas de criação de inicialização 
 * de threads e processos, pois assim pode haver algum 
 * tipo de reaproveitamento, apenas reinicializando 
 * a thread.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - Revision.
 *     ...
 */

 
#include <kernel.h>

 

/*
 *******************************************************************
 * KiCreateIdle:
 *     Criando Idle thread manualmente.
 *     #bugbug Essa idle fica em user mode.
 *
 * *IMPORTANTE: Na verdade esse processos e threads devem ser criados 
 * com uma funçao que passe os parametros via argumento, tipo 
 * create_process create_thread. Exceto a idle que pode ser feita manualmente. 
 *
 * Obs: Criar idle thread com prioridade alta. TID=0 Idle (RING 3).
 * @todo: Mudar o nome para createCreateIdleThread()
 */

void *KiCreateIdle (void){
	
    void *idleStack;                    // Stack pointer.
	char *ThreadName = "idlethread";    // Name.
	
    int r;
	
	//struct.
	
	IdleThread = (void *) malloc ( sizeof(struct thread_d) );	
	
	if ( (void *) IdleThread == NULL )
	{
	    printf("pc-action-create-KiCreateIdle: IdleThread\n");
		die();
		
	} else {
		
	    //Ver se a estrutura do processo é válida.
		if( (void *) InitProcess == NULL ){
	        printf("pc-action-create-KiCreateIdle: InitProcess\n");
		    die();
	    }else{
			
			//#todo
			//checar validade ??
			
			//Indica à qual processo a thread pertence.
	        IdleThread->process = (void *) InitProcess;
		};		
		
	    //Continua...
	};


	// @todo: 
	// #bugbug: #importante
	// A stack da idle não deve ficar no heap do kernel.
	// Pois a idle está em user mode e deve ter sua stack 
	// em user mode para ter permissão de acesso.
	// Mas ficará aqui por enquanto.
	// Obs: Mais abaixo a pilha foi configurada manualmente 
	// no lugar certo.
	
	//IdleThread->Heap = ?;
	//IdleThread->HeapSize = ?;
	//IdleThread->Stack = ?;
	//IdleThread->StackSize = ?;	
	
	//Stack. @todo: A stack deve ser a que está na TSS
	//#BugBug.
	// Estamos alocando mas não etamos usando.
	//# podemos usar o alocador de páginas e alocar uma página para isso.
	
	idleStack = (void *) malloc (4*1024);
	
	if ( (void *) idleStack == NULL )
	{
	    printf("pc-action-create-KiCreateIdle: idleStack\n");
		die();
	};
	
	
	
	//#debug
	//Ok isso funconou, vamos avançar e econtrar qual e1 o problema com essa rotina.
	
	//printf("pc-action-create-KiCreateIdle: struct OK\n");
	//refresh_screen();
	//while(1){}
	
	// @todo: 
	//     É possível usar a função create_thread nesse momento.
	//     Mas é mais veloz fazer o máximo em uma função só.
	//     Mas por enquanto serão feitas à mão essas primeiras threads. 
	
	//@todo: objectType, objectClass, appMode
	
    //Identificadores.
	IdleThread->tid = 0;
	IdleThread->ownerPID = (int) InitProcess->pid;  
	
	
	//#debug
	//testando ... usar as informaç~oes da estrutura de processo.
	//ok isso funcionou ... vamo prosseguir.
	
	//printf("pc-action-create-KiCreateIdle:  OK\n");
	//refresh_screen();
	//while(1){}

	
	
	IdleThread->used = 1;
	IdleThread->magic = 1234;
	IdleThread->name_address = (unsigned long) ThreadName;   //Funciona.

	IdleThread->process = (void *) InitProcess;
	
	
	//
	//  ## Directory ##
	//
	
	IdleThread->DirectoryPA = (unsigned long ) InitProcess->DirectoryPA;	
	
	
	for ( r=0; r<8; r++ ){
		IdleThread->wait_reason[r] = (int) 0;
	}	
	
	
	IdleThread->plane = BACKGROUND;

	// Procedimento de janela.
    //O procedimento.
	IdleThread->procedure = (unsigned long) &system_procedure;
	
    //Argumentos do procedimento de janela.	
	IdleThread->window = NULL; //window;//arg1.
	IdleThread->msg   = 0;     //arg2.
	IdleThread->long1 = 0;     //arg3.
	IdleThread->long2 = 0;     //arg4.
	
	//Características.
	IdleThread->type = TYPE_IDLE;    //TYPE_SYSTEM.
	IdleThread->iopl = RING3;        //Idle thread é uma thread de um processo em user mode.
	IdleThread->state = INITIALIZED;   
	    
    IdleThread->base_priority = KernelProcess->base_priority;  //básica.  
	//IdleThread->base_priority = PRIORITY_NORMAL;
	
	//#debug
	//testando se d'a problemas usar a estrtutura do processo kernel
	//printf("pc-action-create-KiCreateIdle:  >>>> OK\n");
	//refresh_screen();
	//while(1){}
	
	
  	IdleThread->priority = IdleThread->base_priority;          //dinâmica.
	
	IdleThread->saved = 0; 
	IdleThread->preempted = UNPREEMPTABLE; 
	
	//Temporizadores.
	IdleThread->step = 0;          
	IdleThread->quantum = QUANTUM_BASE;
	IdleThread->quantum_limit = QUANTUM_LIMIT;

	IdleThread->standbyCount = 0;
	IdleThread->runningCount = 0;    //Tempo rodando antes de parar.
	
	IdleThread->readyCount = 0;      //Tempo de espera para retomar a execução.
	
	IdleThread->initial_time_ms = get_systime_ms();
	IdleThread->total_time_ms = 0;
	
	//quantidade de tempo rodando dado em ms.
	IdleThread->runningCount_ms = 0;
	
	IdleThread->ready_limit = READY_LIMIT;
	IdleThread->waitingCount  = 0;
	IdleThread->waiting_limit = WAITING_LIMIT;
	IdleThread->blockedCount = 0;    //Tempo bloqueada.		
	IdleThread->blocked_limit = BLOCKED_LIMIT;
	
	
	IdleThread->ticks_remaining = 1000;
	
	//signal
	//Sinais para threads.
	IdleThread->signal = 0;
	IdleThread->signalMask = 0;
	
	//...
	
	//
	// Obs: Essa parte é dependente da arquitetura, deveria estar em 
	//      uma pasta, por exemplo, microkernel\i386.
	//	
	
	//if(MachineType == i386Type){...};
	
	//Context.
	//@todo: Isso deve ser uma estrutura de contexto.
	IdleThread->ss  = 0x23;                          //RING 3.
	IdleThread->esp = (unsigned long) GRAMADOCORE_IDLETHREAD_STACK; //0x0044FFF0;    //idleStack; (*** RING 3)
	IdleThread->eflags = 0x3200;  //0x3202, pois o bit 1 é reservado e está sempre ligado.
	IdleThread->cs = 0x1B;                                
	IdleThread->eip = (unsigned long) GRAMADOCORE_IDLETHREAD_ENTRYPOINT; //0x00401000;     	                                               
	IdleThread->ds = 0x23; 
	IdleThread->es = 0x23; 
	IdleThread->fs = 0x23; 
	IdleThread->gs = 0x23; 
	IdleThread->eax = 0;
	IdleThread->ebx = 0;
	IdleThread->ecx = 0;
	IdleThread->edx = 0;
	IdleThread->esi = 0;
	IdleThread->edi = 0;
	IdleThread->ebp = 0;
	//...
	
	//O endereço incial, para controle.
	IdleThread->initial_eip = (unsigned long) IdleThread->eip; 	
	
	//#bugbug
	//Obs: As estruturas precisam já estar devidamente inicializadas.
	//IdleThread->root = (struct _iobuf *) file_root;
	//IdleThread->pwd  = (struct _iobuf *) file_pwd;

	
	//CPU configuration.
	//IdleThread->cpuID = 0;              //Qual processador.
	//IdleThread->confined = 1;           //Flag, confinado ou não.
	//IdleThread->CurrentProcessor = 0;   //Qual processador.
	//IdleThread->NextProcessor = 0;      //Próximo processador. 
	
	//Coloca na lista de estruturas.
	threadList[0] = (unsigned long) IdleThread;
	
	rootConductor = (struct thread_d *) IdleThread;
	
	// #importante
	// # current idle thread #
	//current_idle_thread = IdleThread->tid;
	
	//Próxima thread.
	IdleThread->Next = NULL;
	//IdleThread->Next = (void*) IdleThread;    //Opção.
	
	// #importante
    // Contador de threads
    // Vamos atualizar o contador de threads, 
	// pois mais uma thread existe, mesmo que não esteja rodando ainda.
	
	//#importante 
	//nesse caso o contador foi configurado manualmente. 
	//isso acontece com as threads do gramado core.

	// #importante
	// A criação da thread idle vai inicializar o contador,
	// para depois só incrementarmos.
	
    ProcessorBlock.threads_counter = (int) 1;
	
    
    // #bugbug
	// Não há a necessidade de colocar na fila de inicializadas
	// se logo em seguida estamos selecionando para execução 
	// colocando no estado standby.
    
	queue_insert_data ( queue, (unsigned long) IdleThread, QUEUE_INITIALIZED );
    
	// * MOVEMENT 1 ( Initialized ---> Standby ).
	SelectForExecution (IdleThread);    
   	
	return (void *) IdleThread;
}


/*
 **************************************************************
 * KiCreateShell:
 *     Criando Thread Shell manualmente.
 * @todo: Mudar o nome para createCreateShellThread()
 */

void *KiCreateShell (void){
	
    void *shellStack;                    // Stack pointer. 
	struct thread_d *t;
	char *ThreadName = "shellthread";    // Name.

    int r;
	
    // todo: checar o tipo de processador antes de configurar o contexto.

	// PID=1 Shell (RING 3).  
	
	if ( (void *) ShellProcess == NULL )
	{
	    printf("pc-create-KiCreateShell: ShellProcess\n");
		die();
	};	
	
	//Thread.
	t = (void *) malloc ( sizeof(struct thread_d) );
	
	if ( (void *) t == NULL ){
	    printf("pc-create-KiCreateShell: t \n");
		die();
	}else{  
	    //Indica à qual proesso a thread pertence.
	    t->process = (void*) ShellProcess; 
	};

	//Stack.
	shellStack = (void*) malloc(4*1024);
	
	if ( (void *) shellStack == NULL )
	{
	    printf("pc-create-KiCreateShell: shellStack\n");
		die();
	};
	
	//@todo: objectType, objectClass, appMode

    //Identificadores.       	
	t->tid = 1;     
	t->ownerPID = (int) ShellProcess->pid;         
	t->used = 1;
	t->magic = 1234;
	t->name_address = (unsigned long) ThreadName;    //Funciona.
	
	t->plane = FOREGROUND;
	
	t->process = (void *) ShellProcess;  
	
	
	// ## Directory  ## 
	
	t->DirectoryPA = (unsigned long ) ShellProcess->DirectoryPA;
	
	for ( r=0; r<8; r++ ){
		t->wait_reason[r] = (int) 0;
	}	
	
	//Procedimento de janela.
	t->procedure = (unsigned long) &system_procedure;
	t->window = NULL;  //window;  //arg1
	t->msg = 0;        //arg2
	t->long1 = 0;      //arg3
	t->long2 = 0;      //arg4	
	
	//Caracteristicas.
	t->state = INITIALIZED;  
	
	t->base_priority = KernelProcess->base_priority;  //básica.   
  	t->priority = t->base_priority;                   //dinâmica.
	
	t->iopl = RING3;  
	t->type = TYPE_SYSTEM;   
	t->saved = 0;
	t->preempted = PREEMPTABLE; 
	
	
	//t->Heap;
	//t->HeapSize;
	//t->Stack;
	//t->StackSize;
	
	//Temporizadores.
	t->step = 0;
	
	//O shel é o thread mais interativo de todos.
	//Deixaremos o quantum dele no limite.
	t->quantum       = QUANTUM_LIMIT;  //QUANTUM_BASE;
	t->quantum_limit = QUANTUM_LIMIT;
	
	
	t->standbyCount = 0;
	t->runningCount = 0;    //Tempo rodando antes de parar.
	
	t->readyCount = 0;      //Tempo de espera para retomar a execução.
	
	t->initial_time_ms = get_systime_ms();
	t->total_time_ms = 0;
	
	//quantidade de tempo rodadndo dado em ms.
	t->runningCount_ms = 0;
	
	t->ready_limit = READY_LIMIT;
	t->waitingCount  = 0;
	t->waiting_limit = WAITING_LIMIT;
	t->blockedCount = 0;    //Tempo bloqueada.		
	t->blocked_limit = BLOCKED_LIMIT;
	
	
	t->ticks_remaining = 1000;	
	
	//signal
	//Sinais para threads.
	t->signal = 0;
	t->signalMask = 0;


	// Context.
	// RING 3.
	// 0x0049FFF0;    //shellStack;//  //RING 3 (pilha do app2)(shell?). 
	// 0x00451000; 
	
	t->ss  = 0x23;                         
	t->esp = (unsigned long) GRAMADOCORE_SHELLTHREAD_STACK; 
	t->eflags = 0x3200;
	t->cs = 0x1B;                                
	t->eip = (unsigned long) GRAMADOCORE_SHELLTHREAD_ENTRYPOINT;     	                                               
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
	//...
	
	//O endereço incial, para controle.
	t->initial_eip = (unsigned long) t->eip; 		
	
	
	//CPU stuffs.
	//t->cpuID = 0;              //Qual processador.
	//t->confined = 1;           //Flag, confinado ou não.
	//t->CurrentProcessor = 0;   //Qual processador.
	//t->NextProcessor = 0;      //Próximo processador. 	
	
	//coloca na lista de estruras.
	threadList[1] = (unsigned long) t;
	
	t->Next = NULL;


	//
	// Running tasks.
	//
	
	//ProcessorBlock.threads_counter = 2;
	ProcessorBlock.threads_counter++;
	
    queue_insert_data ( queue, (unsigned long) t, QUEUE_INITIALIZED );
	
	// * MOVEMENT 1 (Initialized --> Standby).
    SelectForExecution (t);
	
    return (void *) t;
}


/*
 ***************************************************************
 * KiCreateTaskManager:
 *     Criando thread task manager manualmente.
 * @todo: Mudar o nome para createCreateTaskmanThread()
 */

void *KiCreateTaskManager (void){
	
    void *taskmanStack;                    // Stack pointer. 	
	struct thread_d *t;
	char *ThreadName = "taskmanthread";    // Name.
	
	int r;
	
	// #todo: Checar o tipo de processador antes de configurar o contexto.
	
	// PID=2 taskmanager (RING 3).
	
	
	if ( (void *) TaskManProcess == NULL )
	{
	    printf("pc-create-KiCreatetaskManager: TaskManProcess\n");
		die();
	};	

    //Thread.
	//Alocando memória para a estrutura da thread.
	
	t = (void *) malloc ( sizeof(struct thread_d) );	
	
	if( (void *) t == NULL )
	{
	    printf("pc-create-KiCreateTaskManager: t \n");
		die();
	}else{  
	    //Indica à qual proesso a thread pertence.
	    t->process = (void *) TaskManProcess;
	};
	
	//Stack.
	//#bugbug
	//estamos alocando uma stack dentro do heap do kernel.
	taskmanStack = (void *) malloc (4*1024);
	
	if ( (void *) taskmanStack == NULL )
	{
	    printf("pc-create-KiCreateTaskManager: taskmanStack\n");
		die();
	};
  	
	//@todo: object
	
    //Identificadores      
	t->tid = 2;     
	t->ownerPID = (int) TaskManProcess->pid;         
	t->used = 1;
	t->magic = 1234;	
	t->name_address = (unsigned long) ThreadName;   //Funciona.
	
	t->process = (void *) TaskManProcess;
	
	t->plane = BACKGROUND;
	
	
	// # Directory #
	
	t->DirectoryPA = (unsigned long ) TaskManProcess->DirectoryPA; 

	for ( r=0; r<8; r++ ){
		t->wait_reason[r] = (int) 0;
	}	
	
	//Procedimento de janela.
    
	t->procedure = (unsigned long) &system_procedure;
	
	t->window = NULL;    //arg1.
	t->msg = 0;          //arg2.
	t->long1 = 0;        //arg3.
	t->long2 = 0;        //arg4.	

    //Características.	
	t->type = TYPE_SYSTEM;  
	t->state = INITIALIZED; 

	t->base_priority = KernelProcess->base_priority;  //básica.   
  	t->priority = t->base_priority;                   //dinâmica.
	
	t->iopl = RING3;   
	t->saved = 0;
	t->preempted = PREEMPTABLE; 
	
	//t->Heap;
	//t->HeapSize;
	//t->Stack;
	//t->StackSize;

	//Temporizadores.
	t->step = 0;
	t->quantum       = QUANTUM_BASE;
	t->quantum_limit = QUANTUM_LIMIT;	


	t->standbyCount = 0;
	t->runningCount = 0;    //Tempo rodando antes de parar.
	
	t->readyCount = 0;      //Tempo de espera para retomar a execução.
	
	t->initial_time_ms = get_systime_ms();
	t->total_time_ms = 0;
	
	//quantidade de tempo rodadndo dado em ms.
	t->runningCount_ms = 0;
	
	t->ready_limit = READY_LIMIT;
	t->waitingCount  = 0;
	t->waiting_limit = WAITING_LIMIT;
	t->blockedCount = 0;    //Tempo bloqueada.		
	t->blocked_limit = BLOCKED_LIMIT;

	t->ticks_remaining = 1000;
	
	//signal
	//Sinais para threads.
	t->signal = 0;
	t->signalMask = 0;
	
	// Context.
	// RING 3.
	// 0x004FFFF0; 
	// 0x004A1000; 
	
	t->ss  = 0x23;                          
	t->esp = (unsigned long) GRAMADOCORE_TASKMANTHREAD_STACK;     
	t->eflags = 0x3200;
	t->cs = 0x1B;                                
	t->eip = (unsigned long) GRAMADOCORE_TASKMANTHREAD_ENTRYPOINT;     	                                               
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
	//...
	
	//O endereço incial, para controle.
	t->initial_eip = (unsigned long) t->eip; 		
	
	//#bugbug
	//Obs: As estruturas precisam já estar decidamente inicializadas.
	//IdleThread->root = (struct _iobuf *) file_root;
	//IdleThread->pwd  = (struct _iobuf *) file_pwd;	

	//CPU stuffs.
	//t->cpuID = 0;              //Qual processador.
	//t->confined = 1;           //Flag, confinado ou não.
	//t->CurrentProcessor = 0;   //Qual processador.
	//t->NextProcessor = 0;      //Próximo processador. 
	
	//Coloca na lista de estruturas.
	threadList[2] = (unsigned long) t;
	
	t->Next = NULL;
	
	//
	// Running tasks.
	//
	
	//ProcessorBlock.threads_counter = 3;
	ProcessorBlock.threads_counter++;
		
    queue_insert_data ( queue, (unsigned long) t, QUEUE_INITIALIZED );
	
	// * MOVEMENT 1 (Initialized --> Standby).
    SelectForExecution (t);
	
    return (void *) t;
}


//
// End.
//

