/*
 * File: microkernel\pc\create.c
 *
 * Descrição:
 *     Rotinas de criação de processos e threads.
 *     Faz parte do Process Manager, parte fundamental do Kernel Base.
 *     ?? Criar, cria a estrutura. ??
 *     ?? Inicializar inicializa estrutura passada por argumento. ??
 *
 * @todo: 
 *     Separar as rotinas de criação de inicialização de threads e processos, 
 * pois assim pode haver algum tipo de reaproveitamento, apenas reinicializando 
 * a thread.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - Revision.
 *     ...
 */

 
#include <kernel.h>


// Funções importadas.
extern unsigned long get_page_dir();



/*
 * KeCreateProcess:
 *     Interface para criação de um processo.
 * @todo: 
 *     Erro. Rotinas começadas com 'Ke_' servem para chamar serviços de 
 * módulos externos.
 */
void *KeCreateProcess( struct wstation_d *window_station,
                       struct desktop_d  *desktop,
                       struct window_d *window,
                       unsigned long init_eip, 
                       unsigned long priority, 
					   int ppid, 
					   char *name,
					   unsigned long iopl,
                       unsigned long directory_address  )
{
    //
	// @todo: Create some interface routine.
	//
	
	//@todo: Filtros para ponteiros NULL.
	
   
   
	// Create process.
	
createProcess:
    return (void*) create_process( window_station, 
	                               desktop, window, 
								   init_eip, 
								   priority, 
								   ppid, 
								   name, 
								   iopl, 
								   (unsigned long) directory_address );
};


/*
 * KeCreateThread:
 *    Interface para criação de uma thread.
 * @todo: 
 * #Erro. Rotinas começadas com 'Ke_' servem para chamar serviços de 
 * módulos externos.
 */
void *KeCreateThread( struct wstation_d *window_station,
                      struct desktop_d  *desktop,
                      struct window_d *window,
                      unsigned long init_eip, 
                      unsigned long priority, 
					  int ppid, 
					  char *name )
{
    //
	// @todo: Create some interface routine.
	//
	
	//@todo filtros, para ponteiros NULL.
	
  
 // Create thread.
 
createThread:
    return (void*) create_thread( window_station, 
	                              desktop, 
								  window, 
								  init_eip, 
								  priority, 
								  ppid, 
								  name );   
};



/*
 * dofork:
 *     Implementa a rotinca de clonagem de processo.
 *     Essa rotina será chamada por fork().
 *
 */
//int dofork(); 
//int dofork(){
//	return 0;
//};


/*
 * fork: 
 *
 * @todo:
 *     Semelhante ao unix, isso deve criar um processo filho fazendo uma cópia 
 * dos parâmetros presentes no PCB do processo pai. Um tipo de clonagem. 
 * Depois obviamente a imagem do processo filho será carregada em um endereço 
 * físico diferente da imagem do processo pai.
 * Essa não precisa ser a rotina, pode ser apenas uma interface, que chama a 
 * rotina dofork() e outras se necessário.
 *
 */
int fork()
{  
    //struct process_t *p;
	
	//p = (void *) processList[current_process];
	
	//...
	
	//dofork();
	
done:	
	//return (int) p->pid;
	return (int) 0;    //Ainda não implementada. 
};


/*
 * create_task:
 *     @todo: Criar um processo.
 *     Cria tarefas para ring 3.
 *     Seta o contexto dos registradores para a nova tarefa, 
 * atribui id, nome, pilha ...
 *
 * @todo: 
 *     Alocar pilha dinamicamente.
 *     Criar filtro de quantidade de tarefas criadas.
 *     Mudar o nome para createProcess(....);
 * Retorna o id da task.
 * Retorno 0 se falhar.
 *
 */
int create_task( int task_id, 
                 unsigned long *task_eip, 
				 unsigned long *task_stack, 
				 unsigned long prior )
{
    //int ProcessId = task_id;
    
	/*
    create_process( window_station, desktop, window, 
	                init_eip, priority, ppid, name);
	*/
	
done:	
	return (int) 0;
};


/*
 * KiFork:
 *    Inicio do módulo interno que chama a função fork.
 *    Isso é uma interface para a chamada à rotina fork.
 *    @todo: As funções relativas às rotinas de fork
 *           podem ir para um arquivo que será compilado junto com o kernel.
 *           ex: fork.c
 */
int KiFork()
{
	
	//@todo Criar interface
	
	return (int) fork();
};


/*
 * KiCreateTask:
 *     Interface para chamar a rotina que cria um processo.
 *     
 */
int KiCreateProcess(unsigned long type, unsigned long *task_eip)
{
	//@todo:
	
	return (int) 0;
};


/*
 * KiCreateTask:
 *     Interface para chamar a rotina que cria um processo.
 *     @todo: Mudar para KiCreateProcess(...).
 */
int KiCreateTask( int task_id, 
                  unsigned long *task_eip, 
				  unsigned long *task_stack, 
				  unsigned long prior )
{
	
	//@todo: Criar interface e filtrar argumentos.
	
	return (int) KiCreateProcess(0, task_eip);
};

 
 

/*
 * KiCreateKernelProcess:
 *    Criando manualmente o processo do Kernel.
 *    #suspensa: Agora o processo kernel é criado com a mesma rotina 
 * que é usda para criar os outros processos.
 */
void *KiCreateKernelProcess()
{
	/*
	 * #SUSPENSA !!
     *	 
	
	struct process_d *p;
	char *ProcessName = "KERNEL PROCESS";
	
	//KernelProcess 
	
	p = (void *) malloc( sizeof(struct process_d) );
	
	if( (void*) p == NULL ){
	    printf("KiCreateKernelProcess:");
		refresh_screen();
		while(1){}
	}else{
		
		//Directory (endereço físico?). (cr3).
		p->Directory = (unsigned long ) KERNEL_PAGEDIRECTORY;
		//p->Directory = (unsigned long ) get_page_dir();
		
		//Inicializando a lista de framepools do processo.
		//@todo: Todo processo deve sr criado com pelo menos um 
		//frame pool, o que é equivalente a 4MB.(uma partição)
		//Obs: Um framepool indica onde é a área de memória fisica
		//que será usada para mapeamento das páginas usadas pelo processo.
		p->framepoolListHead = NULL;

		//Image info.
	    p->Image       = KERNEL_IMAGE_BASE;   // Base da imagem do processo.
	    p->ImageSize = 0;       //@todo: Tamanho da imagem do processo.				
		
		//Heap and Stack. (endereços físicos = endereços virtuais).
	    p->Heap        = KERNEL_HEAP_START;   // Endereço do início do Heap do processo.
		p->HeapEnd     = KERNEL_HEAP_END;
	    p->HeapSize    = (KERNEL_HEAP_SIZE/1024);    // Tamanho do heap, dado em KB.
	    p->Stack       = KERNEL_STACK_START;  // Endereço do início da Stack do processo.
	    p->StackEnd    = KERNEL_STACK_END;
		p->StackSize   = (KERNEL_STACK_SIZE/1024);   // Tamanho da pilha, dado em KB.	
	    p->StackOffset = 0;     // Deslocamento da pilha em relação ao início do kernel. 

	    
		//@todo: objectType, objectClass, appMode
		
		//Identifications.
		p->pid  = (int) 0;                   //PID.
	    p->ppid = (int) p->pid;              //PPID, Criado por ele mesmo.	 
		p->uid  = (int) GetCurrentUserId();  //UID.
		p->gid  = (int) 0;                   //GID.
		
		p->used = 1;
		p->magic = 1234;	

		p->name_address = (unsigned long) ProcessName;
	    p->iopl = RING0;                        //Kernel mode.
		p->base_priority = PRIORITY_MAX;  //básica.
		p->priority = p->base_priority;   //dinâmica.
		
		//ppl = K0
		//p->pplK0;
		
		//Lista de threads
		p->threadListHead = NULL;
		
		//Sinal para processo.
		p->signal = 0;
		p->signalMask = 0;
		//Continua ...
		
		
		p->Next = NULL;                         //(void*) KernelProcess;	
		
		
		//
		// @todo: Cuidado com esses ponteiros.
		//
		
		//Atualizando o ponteiro global para estrutura do processo kernel.
		KernelProcess = (void*) p;
		
		processList[0] = (unsigned long) KernelProcess;
		
		//Processor struct. 
		processor->CurrentProcess = (void*) KernelProcess;
		processor->NextProcess    = (void*) KernelProcess;	
	}; 
	
//Done.
done:
    return (void*) KernelProcess;
	
	*/
    return NULL;
};


/*
 * KiCreateIdle:
 *     Criando Idle thread manualmente.
 * *IMPORTANTE: Na verdade esse processos e threads devem ser criados 
 * com uma funçao que passe os parametros via argumento, tipo 
 * create_process create_thread. Exceto a idle que pode ser feita manualmente. 
 *
 * Obs: Criar idle thread com prioridade alta. TID=0 Idle (RING 3).
 * @todo: Mudar o nome para createCreateIdleThread()
 */
void *KiCreateIdle()
{
    void *idleStack;                    // Stack pointer.
	char *ThreadName = "idlethread";    // Name.
	
    //Aloca memória mara a estrutura.
	IdleThread = (void*) malloc( sizeof(struct thread_d) );	
	if( (void*) IdleThread == NULL ){
	    printf("pc-create-KiCreateIdle: IdleThread\n");
		die();
	}
	else
	{ 
	    //Ver se a estrutura do processo é válida.
		if( (void*) KernelProcess == NULL ){
	        printf("pc-create-KiCreateIdle: KernelProcess\n");
		    die();
	    }else{
			//Indica à qual processo a thread pertence.
	        IdleThread->process = (void*) KernelProcess;
		};		
		
	    //Continua...
	};

	//
	// @todo: bugbug; A stack da idle não deve ficar no heap do kernel.
	//                Pois a idle está em user mode e 
	//                deve ter sua stack em user mode
	//                para ter permissão de acesso.
	//                Mas ficará aqui por enquanto.
	//                Obs: Mais abaixo a pilha foi configurada 
	//                     manualmente no lugar certo.
	//
	
	//IdleThread->Heap = ?;
	//IdleThread->HeapSize = ?;
	//IdleThread->Stack = ?;
	//IdleThread->StackSize = ?;	
	
	//Stack. @todo: A stack deve ser a que está na TSS
	//#BugBug.
	// Estamos alocando mas não etamos usando.
	idleStack = (void*) malloc(4*1024);
	if( (void*) idleStack == NULL ){
	    printf("pc-create-KiCreateIdle: idleStack\n");
		die();
	};
	
	//
	// @todo: 
	//     É possível usar a função create_thread nesse momento.
	//     Mas é mais veloz fazer o máximo em uma função só.
	//     Mas por enquanto serão feitas à mão essas primeiras threads. 
	//
	
	//@todo: objectType, objectClass, appMode
	
    //Identificadores.
	IdleThread->tid = 0;
	IdleThread->ownerPID = (int) KernelProcess->pid;  
	IdleThread->used = 1;
	IdleThread->magic = 1234;
	IdleThread->name_address = (unsigned long) ThreadName;   //Funciona.

	IdleThread->process = (void*) KernelProcess;
	
	
	IdleThread->Directory = (unsigned long ) KERNEL_PAGEDIRECTORY;
	
	//
	// Procedimento de janela.
	//  

    //O procedimento.
	IdleThread->procedure = (unsigned long) &system_procedure;
	
    //Argumentos do procedimento de janela.	
	IdleThread->window = NULL; //window;//arg1.
	IdleThread->msg   = 0;     //arg2.
	IdleThread->long1 = 0;     //arg3.
	IdleThread->long2 = 0;     //arg4.
	
	//Características.
	IdleThread->type  = TYPE_IDLE;    //TYPE_SYSTEM.
	IdleThread->iopl  = RING3;        //Idle thread é uma thread de um processo em user mode.
	IdleThread->state = INITIALIZED;   
	
	IdleThread->base_priority = KernelProcess->base_priority;  //básica.   
  	IdleThread->priority = IdleThread->base_priority;          //dinâmica.
	
	IdleThread->saved = 0; 
	IdleThread->preempted = UNPREEMPTABLE;    // Não pode sofrer preempção.
	
	//Temporizadores.
	IdleThread->step = 0;          
	IdleThread->quantum       = QUANTUM_BASE;
	IdleThread->quantum_limit = QUANTUM_LIMIT;

	IdleThread->standbyCount = 0;
	IdleThread->runningCount = 0;    //Tempo rodando antes de parar.
	IdleThread->readyCount = 0;      //Tempo de espera para retomar a execução.
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
	IdleThread->esp = (unsigned long) 0x0044FFF0;    //idleStack; (*** RING 3)
	IdleThread->eflags = 0x3200;
	IdleThread->cs = 0x1B;                                
	IdleThread->eip = (unsigned long) 0x00401000;     	                                               
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
	
	//#bugbug
	//Obs: As estruturas precisam já estar decidamente inicializadas.
	IdleThread->root = (struct _iobuf *) file_root;
	IdleThread->pwd  = (struct _iobuf *) file_pwd;

	
	//CPU configuration.
	//IdleThread->cpuID = 0;              //Qual processador.
	//IdleThread->confined = 1;           //Flag, confinado ou não.
	//IdleThread->CurrentProcessor = 0;   //Qual processador.
	//IdleThread->NextProcessor = 0;      //Próximo processador. 
	
	//Coloca na lista de estruturas.
	threadList[0]  = (unsigned long) IdleThread;
	
	//Próxima thread.
	IdleThread->Next = NULL;
	//IdleThread->Next = (void*) IdleThread;    //Opção.
	
	// Running tasks. (Quantas threads estão rodando).
    ProcessorBlock.running_threads = (int) 1;
	
	//@todo: setar a idle como current.
	
	//if( ProcessorBlock.running_tasks == 1 ){
	//	current_thread = IdleThread->tid;
	//};
	
// Done.	
done:
    //#bugbug
	//Não há a necessidade de colocar na fila de inicializadas
	//se logo em seguida estamos selecionando para execução 
	//colocando no estado standby.
    queue_insert_data(queue, (unsigned long) IdleThread, QUEUE_INITIALIZED);
    SelectForExecution(IdleThread);    // * MOVEMENT 1 ( Initialized ---> Standby ).
   	return (void*) IdleThread;
};



/*
 * KiCreateShell:
 *     Criando Thread Shell manualmente.
 * @todo: Mudar o nome para createCreateShellThread()
 */
void *KiCreateShell()
{
    void *shellStack;                    // Stack pointer. 
	struct thread_d *t;
	char *ThreadName = "shellthread";    // Name.


   /*
    *@todo: checar o tipo de processador antes de configurar o contexto.
	*
	*/

   /*
	* PID=1 Shell (RING 3).
	*/  

	 
    //Process.
	/*
	struct process_d *p;
	p = (void*) malloc( sizeof(struct process_d) );	
	if( (void*) p == NULL)
	{
	    printf("KiCreateShell: Process fail.\n");
		refresh_screen();
		while(1){}
	};
	*/
	if( (void*) KernelProcess == NULL ){
	    printf("pc-create-KiCreateShell: KernelProcess\n");
		die();
	};	
	
	//Thread.
	t = (void*) malloc( sizeof(struct thread_d) );	
	if( (void*) t == NULL ){
	    printf("pc-create-KiCreateShell: t \n");
		die();
	}
	else
	{  
	    //Indica à qual proesso a thread pertence.
	    t->process = (void*) TaskManProcess; //KernelProcess;
	};

	//Stack.
	shellStack = (void*) malloc(4*1024);
	if( (void*) shellStack == NULL ){
	    printf("pc-create-KiCreateShell: shellStack\n");
		die();
	};
	
	//@todo: objectType, objectClass, appMode

    //Identificadores.       	
	t->tid = 1;     
	t->ownerPID = (int) KernelProcess->pid;         
	t->used = 1;
	t->magic = 1234;
	t->name_address = (unsigned long) ThreadName;    //Funciona.
	
	t->process = (void*) ShellProcess; //KernelProcess;
	
	t->Directory = (unsigned long ) KERNEL_PAGEDIRECTORY;
	
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
	t->preempted = PREEMPTABLE;    //PREEMPT_PODE; //pode.
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


	//Context.
	t->ss  = 0x23;                          //RING 3.
	t->esp = (unsigned long) 0x0049FFF0;    //shellStack;//  //RING 3 (pilha do app2)(shell?). 
	t->eflags = 0x3200;
	t->cs = 0x1B;                                
	t->eip = (unsigned long) 0x00451000;     	                                               
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
	
	//#bugbug
	//Obs: As estruturas precisam já estar decidamente inicializadas.
	IdleThread->root = (struct _iobuf *) file_root;
	IdleThread->pwd  = (struct _iobuf *) file_pwd;	
	
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
	
	ProcessorBlock.running_threads = 2;

	
// Done.
done:
    queue_insert_data(queue, (unsigned long) t, QUEUE_INITIALIZED);
    SelectForExecution(t);    // * MOVEMENT 1 (Initialized --> Standby).
    return (void*) t;
};



/*
 * KiCreateTaskManager:
 *     Criando thread task manager manualmente.
 * @todo: Mudar o nome para createCreateTaskmanThread()
 */
void *KiCreateTaskManager()
{
    void *taskmanStack;                    // Stack pointer. 	
	struct thread_d *t;
	char *ThreadName = "taskmanthread";    // Name.
	
   /*
    * @todo: 
	*     Checar o tipo de processador antes de configurar o contexto.
	*
	*/


   /*
	* PID=2 taskmanager (RING 3).
	*/  
	
	//Process.
	/*
	struct process_d *p;
	p = (void*) malloc( sizeof(struct process_d) );	
	if( (void*) p == NULL)
	{
	    printf("KiCreateTaskManager: Process fail.\n");
		refresh_screen();
		while(1){}
	};
	*/
	if( (void*) KernelProcess == NULL ){
	    printf("pc-create-KiCreatetaskManager: KernelProcess\n");
		die();
	};	

    //Thread.
	//Alocando memória para a estrutura da thread.
	t = (void*) malloc( sizeof(struct thread_d) );	
	if( (void*) t == NULL ){
	    printf("pc-create-KiCreateTaskManager: t \n");
		die();
	}else{  
	    //Indica à qual proesso a thread pertence.
	    t->process = (void*) KernelProcess;
	};
	
	//Stack.
	//#bugbug
	//estamos alocando uma stack dentro do heap do kernel.
	taskmanStack = (void*) malloc(4*1024);
	if( (void*) taskmanStack == NULL ){
	    printf("pc-create-KiCreateTaskManager: taskmanStack\n");
		die();
	};
  	
	//@todo: object
	
    //Identificadores      
	t->tid = 2;     
	t->ownerPID = (int) KernelProcess->pid;         
	t->used = 1;
	t->magic = 1234;	
	t->name_address = (unsigned long) ThreadName;   //Funciona.
	
	t->process = (void*) KernelProcess;
	
	t->Directory = (unsigned long ) KERNEL_PAGEDIRECTORY;

	//Procedimento de janela.
    t->procedure = (unsigned long) &system_procedure;	
	t->window = NULL;  //window;  //arg1.
	t->msg = 0;        //arg2.
	t->long1 = 0;      //arg3.
	t->long2 = 0;      //arg4.	

    //Características.	
	t->type = TYPE_SYSTEM;  
	t->state = INITIALIZED; 

	t->base_priority = KernelProcess->base_priority;  //básica.   
  	t->priority = t->base_priority;                   //dinâmica.
	
	t->iopl = RING3;   
	t->saved = 0;
	t->preempted = PREEMPTABLE;    //PREEMPT_NAOPODE; //nao pode.	
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
	
	//Context.
	t->ss  = 0x23;                          //RING 3.
	t->esp = (unsigned long) 0x004FFFF0;    //taskmanStack;//0x0045FFF0;  //pilha. 
	t->eflags = 0x3200;
	t->cs = 0x1B;                                
	t->eip = (unsigned long) 0x004A1000;     	                                               
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
	
	//#bugbug
	//Obs: As estruturas precisam já estar decidamente inicializadas.
	IdleThread->root = (struct _iobuf *) file_root;
	IdleThread->pwd  = (struct _iobuf *) file_pwd;	

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
	
	ProcessorBlock.running_threads = 3;
	
// Done.
done:
    queue_insert_data(queue, (unsigned long) t, QUEUE_INITIALIZED);
    SelectForExecution(t);    // * MOVEMENT 1 (Initialized --> Standby).
    return (void*) t;
};


//
// Fim.
//
