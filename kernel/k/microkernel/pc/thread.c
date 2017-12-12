/*
 * File: thread.c
 *
 * Descrição:
 *     TM - Thread Manager.
 *     Rotinas com threads. 
 *     Criar, deletar ...
 *
 * Obs: As threads podem acessar o espaço virtual do processo ao qual 
 * pertencem. mas não podem acessar memória de outro processo.
 *
 * Obs: Nesse arquivo há uma mistura de inicialização independente de
 * de arquitetura e inicialização da arquitetura i386. Essas inicializações
 * precisam estar em arquivos e diretórios diferentes.
 * 
 * Historico:
 *     Versão: 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *     Versão: 1.0, 2016 - Revisão.
 */


#include <kernel.h>


/*
 * Uma forma de proteger a estrutura de thread é deixa-la aqui restringindo o acesso à ela.
 *
 */

//
// Variáveis internas.
// 

//int threadmanagerStatus;
//int threadmanagerError;
//...
 
 
/*
struct thread_d *threadNew();
struct thread_d *threadNew()
{
    struct thread_d *New;	
	
	//@todo: Implementar.
	//Cria uma thread genérica e retorna o ponteiro.
	
	//
done:	
	return (struct thread_d *) New;
};
*/

/*
 * create_thread:
 *     Cria um thread para rodar em user mode. 
 *
 * @todo: O processo ao qual o thread vai ser atribuído deve ser 
 * passado via argumento, se o argumento for nulo, então usa-se o 
 * processo atual como dono do thread.
 *
 * Obs:
 *     Retorno do tipo ponteiro de estrutura.
 *     Retorna o endereço da estrutura da tarefa.
 *     Retorna NULL se der errado.
 *
 * Obs: Essa rotina deve fazer a inicialização da parte independente
 * da arquitetura e chamar as rotinas referentes à inicializaçções
 * dependentes da arquitetura, que ficarão em outro diretório.
 *
 * @todo: Esses argumentos presisam ser revistos. Escolher um conjunto 
 * melhor de argumentos.
 *
 * 2015, Created - Fred Nora.
 * 2016, Revisão - FN.
 */								 
thread_descriptor_t *create_thread( struct wstation_d *window_station,
                                    struct desktop_d  *desktop,
                                    struct window_d *window,
                                    unsigned long init_eip, 
                                    unsigned long init_stack, 
									int pid, 
									char *name)
{	
    //Structures.	
	struct process_d *Process;    //Process.
	struct thread_d *Thread;      //Thread.
	struct thread_d *Empty;       //Empty slot.

	//Identificadores.
	int ProcessID;	
	int i = USER_BASE_TID;		
	
	//
	// Limits da thread atual.
	//
	// @todo: Não sei pra que isso. A thread atual não importa.
	//        deletar isso. 
	//
	if(current_thread < 0 || current_thread >= THREAD_COUNT_MAX ){
		return NULL;
	};
	
	//@todo:
	//Checar se a prioridade é um argumento válido.
	//if( priority == 0 ){}
	
	
	//
	// Filtrar o processo ao qual a thread pertencerá.
	//
	ProcessID = (int) pid;
	
	if( ProcessID < 0 || ProcessID >= PROCESS_COUNT_MAX ){
		ProcessID = current_process;
	};

	Process = (void*) processList[ProcessID]; 		
	if( (void*) Process == NULL ){
		printf("create_thread: Process struct\n");
		refresh_screen();
		while(1){}
	};
	
	//Alocando memória para a estrutura da thread.
	//Obs: Estamos alocando memória dentro do heap do kernel.
	Thread = (void*) malloc( sizeof(struct thread_d) );	
	if( (void*) Thread == NULL ){
	    printf("create_thread:");
		refresh_screen();
		while(1){}
	}else{  
	    //Indica à qual proesso a thread pertence.
	    //Thread->process = (void*) Process;
	};
	
	//Nothing.
	
//Loop.	
get_next:	
	
	//BugBug: Isso pode virar um loop infinito!
	
	i++;
	if(i >= THREAD_COUNT_MAX){
		i = USER_BASE_TID;    //Recomeça o loop na base para id de usuários.
	};
	
	//Get empty.
	Empty = (void*) threadList[i];
    
	//Se o slot estiver ocupado.
	if( (void*) Empty != NULL ){
        goto get_next;
    }else{
		
		//Object.
		Thread->objectType = ObjectTypeThread;
		Thread->objectClass = ObjectClassKernelObjects;
	
		//c,Put in list.
		Thread->tid = (int) i;
		
		//if( Thread->tid < 0 ){
		    //fail	
		//};		
		
		Thread->ownerPID = (int) pid;  //ID do processo ao qual o thread pertence.
	    Thread->used = 1;
	    Thread->magic = 1234;
		Thread->name_address = (unsigned long) name;  //Name.   
		//@todo: Usar Thread->name. 
		//Thread->cmd @todo.

        //Thread->process = (void*) Process;

		//Procedimento de janela.
	    Thread->procedure = (unsigned long) &system_procedure;
		//Msg support. //Argumentos.
		Thread->window = NULL;        //arg1.
	    Thread->msg = 0;              //arg2.
	    Thread->long1 = 0;            //arg3.
	    Thread->long2 = 0;            //arg4.		

        //Caracteristicas.
	    Thread->type = TYPE_SYSTEM; //TYPE_IDLE;    //?? //Type...@todo: Rever. 
	    Thread->state = INITIALIZED;  
		//Apenas Initialized, pois a função SelectForExecution
		//seleciona uma thread para a execução colocando ela no
		//state Standby.	
		
		//A prioridade básica da thread é igual a prioridade básica do processo.
		Thread->base_priority = (unsigned long) KernelProcess->base_priority; //Process->base_priority;
		Thread->priority = (unsigned long) Thread->base_priority; // priority; //A prioridade dinâmica da thread foi passada por argumento.			
		
		//IOPL.
		//Se ela vai rodar em kernel mode ou user mode.
		//@todo: herdar o mesmo do processo.
		Thread->iopl = RING3;  //Process->iopl;  		
		Thread->saved = 0;                //Saved flag.	
		Thread->preempted = PREEMPTABLE;  //Se pode ou não sofrer preempção.
		
		//Heap and Stack.
	    //Thread->Heap;
	    //Thread->HeapSize;
	    //Thread->Stack;
	    //Thread->StackSize;

        //Temporizadores.  		
	    Thread->step = 0;                           //Quantas vezes ela usou o processador no total.
        Thread->quantum =  QUANTUM_BASE;            //QUANTUM_BASE
        Thread->quantum_limit = QUANTUM_LIMIT; //(9*2);  //O boost não deve ultrapassar o limite. QUANTUM_LIMIT			
		
		
		
        Thread->standbyCount = 0;
	    Thread->runningCount = 0;    //Tempo rodando antes de parar.
	    Thread->readyCount = 0;      //Tempo de espera para retomar a execução.
	    Thread->ready_limit = READY_LIMIT;
	    Thread->waitingCount  = 0;
	    Thread->waiting_limit = WAITING_LIMIT;
	    Thread->blockedCount = 0;    //Tempo bloqueada.		
	    Thread->blocked_limit = BLOCKED_LIMIT;
		
	    Thread->ticks_remaining = 1000;    //Not used now.	


	    //signal
	    //Sinais para threads.
	    Thread->signal = 0;
        Thread->signalMask = 0;	


        //
		// @todo: Essa parte é dependente da arquitetura i386.
		//        poderá ir pra outro arquivo.
		//
		
		//
		// #BUGBUG 
		// **** NÃO TEMOS UMA PILHA ****
		// Precisamos de uma pilha para user mode.
		// Colocaremos uma pilha simulada para teste ..
		// isso funcionará em apenas uma thread...
		// na proxima vai dat problema.
		//
		
		//Context.
	    Thread->ss = 0x23;    //RING 3.
	    Thread->esp = (unsigned long) init_stack;//@todo: 
	    Thread->eflags = 0x3200;
	    Thread->cs = 0x1B;                                
	    Thread->eip = (unsigned long) init_eip;  
        ////OBS: eip Aceita endereços inválidos, a thread fecha nesses casos por PG fault.		
	    Thread->ds = 0x23; 
	    Thread->es = 0x23; 
	    Thread->fs = 0x23; 
	    Thread->gs = 0x23; 
	    Thread->eax = 0;
	    Thread->ebx = 0;
	    Thread->ecx = 0;
	    Thread->edx = 0;
	    Thread->esi = 0;
	    Thread->edi = 0;
	    Thread->ebp = 0;	
		
		
		//cpu.
		//Thread->cpuID = 0;
		//Thread->confined = 0;
		//Thread->CurrentProcessor = 0;
		//Thread->NextProcessor = 0;
		
		//Page Directory. (#CR3).
		//Estamos usando o page directory do processo.
		//page directory do processo ao qual a thread pertence.
		Thread->Directory = (unsigned long ) Process->Directory; 



		
		
		

		
	
		
		 
	    

		//@todo: Por enquanto as threads são criadas usando o diretório de páginas do kernel.
		


        //ServiceTable ..

        //Ticks ...
        //DeadLine ... 

	 

	
		
		//Thread->PreviousMode  //ring???
		
		//Thread->idealprocessornumber
		
		//Thread->event
		
  	
	
	
	
	
	    //
	    // ORDEM: O que segue é referenciado com pouca frequencia.
	    //

	    Thread->waitingCount = 0;    //Tempo esperando algo.
	    Thread->blockedCount = 0;    //Tempo bloqueada.	
	
        //À qual processo pertence a thread.  
		Thread->process = (void*) Process; 	 	                      
        
		//Thread->window_station
		//Thread->desktop
         


	

		
		//Thread->control_menu_procedure
		
		//Thread->wait4pid =

		//...
        //@todo:
        //herdar o quantum do processo.
        //herdar a afinidade do processo.(cpu affinity) 


        Thread->exit_code = 0;
	    

		//@todo: Incrementar a contagem de threads no processo.
		//Process->threadCount++;
		
		//Próxima thread da lista.
		Thread->Next = NULL;
		
		//Coloca na lista.
		threadList[i] = (unsigned long) Thread;	
	};

	//
	// Running tasks.
	//
	
	//ProcessorBlock.running_tasks = 2;
    //@todo: isso deve ir pra outro lugar.
	//talvez dentro de SelectForExecution.
		
//
// Done.
//
	
done:
    
	//
	// Warning !!! (NÃO COLOCAR PARA EXECUÇÃO, OUTRA FUNÇÃO DEVE COLOCAR PARA EXECUÇÃO)
	//
	
    //SelectForExecution(t);  //***MOVEMENT 1 (Initialized ---> Standby)
    return (void*) Thread;
};


/*
 * GetCurrentThreadId
 *     Pega o id da thread atual.
 *     Obs: current_thread já é o id.
 */
int GetCurrentThreadId(){
	return (int) current_thread;
};


/*
 * GetCurrentThread:
 *     Retorna o endereço da estrutura da thread atual.
 *
 */
void *GetCurrentThread()
{
    struct thread_d *Current;
	
	//Limits.
	if(current_thread < 0 || current_thread >= THREAD_COUNT_MAX ){
		return NULL;
	};
	
	Current = (void*) threadList[current_thread];	
	if( (void*) Current == NULL ){
        return NULL;
	};
//Done.
done:
	return (void*) Current;
};


/*
 * FindReadyThread:
 *     Pega a primeira thread READY que encontrar.
 *     E se não encontrar nenhuma, retorna NULL.
 */
void *FindReadyThread()
{
	int Index;
    struct thread_d *Thread;  
    
	for(Index=0; Index<THREAD_COUNT_MAX; Index++)
	{
	    Thread = (void *) threadList[Index];	
		
		if( (void*) Thread != NULL )
		{
            if( Thread->used == 1 && 
			    Thread->magic == 1234 && 
				Thread->state == READY )
			{
				//Done.
	            return (void *) Thread;
			};
			//Nothing.
	    };
        //Nothing.		
	};
//Nenhuma foi encontrada.   
fail:
    return NULL;
};



/*
 * SelectForExecution:
 *     Um thread entra em standby, sinalizando que está pronto para entrar 
 * em execução.
 *     Nesse caso, durante a rotina de taskswitch, checar-se-a se existe 
 * um thread em estado standby, caso haja, a thread é colocada pra executar 
 * pelo método spawn. Esse método de spawn já foi testado, segundo a contagem,
 * duas thread começaram a rodas através desse método de spawn. provavelmente 
 * as threads 'shell' e 'taskman', pois a thread 'idle' é chamada com um 
 * spawn exclusivo para ela, o que é desnecessário e poderá ser revisto. @todo
 *     
 *  *** MOVIMENTO 1, (Initialized --> Standby).
 */
void SelectForExecution(struct thread_d *Thread)
{ 
	if( (void*) Thread == NULL){
        return;
	};  

	//
	// @todo: if initialized ---> Standby.
	// @todo: if zombie ---> Standby.
	//
	// Talvez aqui seja necessário checar o estado da thread.
	// Quem pode entrar no estado standby??
	// >> Uma thread no estado initialized pode entrar no estado standby 
	// >> Uma thread no estado zombie pode entrar no estado standby.
	// >> @todo: se uma thread estiver em qualquer um dos outros estados ela 
	// não pode entrar em stadby.
	//
	
setState:
    //*MOVIMENTO 1, (Initialized --> Standby).
    Thread->state = (int) STANDBY;
	queue_insert_data(queue, (unsigned long) Thread, QUEUE_STANDBY);	
	return;
};


//Get State. (Zero é tipo NULL?).
int GetThreadState(struct thread_d *Thread)
{ 
	if( (void*) Thread == NULL){
        return (int) 0;
	};  
	return (int) Thread->state;
};

//Get Type. (Zero é tipo NULL?).
int GetThreadType(struct thread_d *Thread)
{
	if( (void*) Thread == NULL){
        return (int) 0;
	};  
    return (int) Thread->type;
};



/*
 * show_thread_information:
 *     Mostra informações sobre as threads.
 */
void show_thread_information()
{
	struct thread_d *Current;	
	
	printf("Threads info:\n\n");		
	
	//Limits.
	if(current_thread < 0 || current_thread >= THREAD_COUNT_MAX ){
		return;
	};	
	
	Current = (void*) threadList[current_thread];
	if( (void*) Current == NULL){
	    printf("show_thread_information:\n");	
	    return;
	}else{
	    
		printf("CurrentThreadId={%d}\n",current_thread);
		//...
	};

    mostra_slots();    //Mostra Slots.
	
	/*
	 * @todo: 
	 *     Mostra filas: Ready, Waiting ...
	 *     checar estruturas de filas no debug.
	 *     Erro: Mostrar filas não deve fazer parte dessa rotina.
	 */
	//show_queue_information(queue);
	
	//Nothing for now!
	
//Done.	
done:	
    printf("Done.\n");
	return;
};



/*
 * init_threads:
 *     Inicializa o thread manager.
 *     Inicializa as estruturas e variáveis 
 *     que lidam com threads.
 *
 */
int init_threads()
{ 
	//Globais.	 
	current_thread = 0;                        //Atual. 
	ProcessorBlock.running_threads = (int) 0;    //Número de tarefas rodando.	
	old = 0;                                   //?
    forkid = 0;                                //
    task_count = (unsigned long) 0;            //Zera o contador de tarefas criadas.
	//...
	
	//
	// @todo: Porque essas variáveis usam o termo 'task'?
	//        task é sinonimo de process.
	//	
	
	//Variáveis usadas na inicialização de uma nova tarefa.	
	start_new_task_status  = (unsigned long) 0;    //Se há uma nova tarefa.
	start_new_task_id = (int) 0;                   //Id dá nova tarefa.
	start_new_task_address = (unsigned long) 0;	   //Endereço da nova tarefa.
	
	//@todo: Há mais variáveis para serem inicializadas??!!
	
	
	//Zerando a lista de threads.
	int i=0;
	while(i < THREAD_COUNT_MAX){
	    threadList[i] = (unsigned long) 0;    //NULL.
        ++i;
	};
	
	//
	// @todo: Nada mais?
	//
	
//Done.	
done:
	return (int) 0;
};


/*
 *Constructor.
int threadmanagerProcessmanager()
{};
*/

/*
int threadmanagerInit()
{};
*/


//
//fim.
//

