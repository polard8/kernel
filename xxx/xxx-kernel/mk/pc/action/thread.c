/*
 * File: pc\action\thread.c
 *
 * Descrição:
 *     TM - Thread Manager (Parte fundamental do Kernel Base).
 *     Rotinas com threads. 
 *     Criar, deletar ...
 *
 * Obs: As threads podem acessar o espaço virtual do processo ao qual 
 * pertencem, mas não podem acessar memória de outro processo.
 *      Existe a memória compartilhada entre processos. Nesse caso
 * uma thread vai acessar uma memória sua que também pertence a outro 
 * processo. 
 *
 * #bugbug
 * Obs: Nesse arquivo há uma mistura de inicialização independente de
 * de arquitetura e inicialização da arquitetura i386. Essas inicializações
 * precisam estar em arquivos e diretórios diferentes.
 * 
 * History:
 *     2015 - Create by Fred Nora.
 *     2016 - Revision.
 */


#include <kernel.h>


/*
 * Obs:
 * Uma forma de proteger a estrutura de thread é deixa-la aqui 
 * restringindo o acesso à ela.
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
 ***********************************************************************
 * create_thread:
 *     Cria um thread para rodar em user mode. (just Ring 3) 
 *
 * @todo: O processo ao qual o thread vai ser atribuído deve ser passado 
 * via argumento, se o argumento for nulo, então usa-se o 
 * processo atual como dono do thread.
 *
 * Obs: Essa rotina deve fazer a inicialização da parte independente
 * da arquitetura e chamar as rotinas referentes à inicializaçções
 * dependentes da arquitetura, que ficarão em outro diretório.
 *
 * IN:
 *     @todo: Esses argumentos presisam ser melhorados.
 *
 * OUT:
 *     Retorno do tipo ponteiro de estrutura.
 *     Retorna o endereço da estrutura da thread.
 *     Retorna NULL se der errado.
 *
 * 2015, Created - Fred Nora.
 * 2016, Revisão - FN.
 */		
 
struct thread_d *create_thread( struct wstation_d *window_station,
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
	
	//wait reasons
	int w;
	
	//
	// Limits da thread atual.
	//
	// #bugbug: 
	// Não sei pra que isso. 
	// Pois a thread atual não importa.
	// @todo: deletar isso. 
	//
	
	
	//#bugbug
	//@deletar
	if( current_thread < 0 || 
	    current_thread >= THREAD_COUNT_MAX )
	{
		return NULL;
	}
	
	//@todo:
	//Checar se a prioridade é um argumento válido.
	//if( priority == 0 ){}
	
	
	// Filtrar o processo ao qual a thread pertencerá.
	
	ProcessID = (int) pid;
	
	if( ProcessID < 0 || 
	    ProcessID >= PROCESS_COUNT_MAX )
	{
		// #bugbug:
		// Não sabemos a condição do processo atual para 
		// permitirmos que ele seja o dono da thread.
		ProcessID = current_process;
	}
	
	// Já temos um PID para o processo que é dono da thread.

	Process = (void *) processList[ProcessID]; 		
	if( (void *) Process == NULL )
	{
		printf("pc-action-thread-create_thread: Process\n");
		die();
	}
	
	//Alocando memória para a estrutura da thread.
	//Obs: Estamos alocando memória dentro do heap do kernel.
	Thread = (void *) malloc( sizeof(struct thread_d) );	
	
	if ( (void *) Thread == NULL )
	{
	    printf("pc-action-thread-create_thread: Thread\n");
		die();
	}else{  
	    //Indica à qual proesso a thread pertence.
	    //Thread->process = (void*) Process;
	};
	
	//Nothing.
	
//Loop.	
get_next:	
	
	//BugBug: Isso pode virar um loop infinito!
	
	i++;
	if( i >= THREAD_COUNT_MAX )
	{
		// Recomeça o loop na base para id de usuários.
		i = USER_BASE_TID;    
	};
	
	//Get empty.
	Empty = (void *) threadList[i];
    
	//Se o slot estiver ocupado.
	if( (void *) Empty != NULL )
	{
		// Voltamos.
		// #bugbug: Isso pode não parar nunca.
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
		
		//ID do processo ao qual o thread pertence.
		Thread->ownerPID = (int) pid; //#bugbug: Deve ser (ProcessID).  
	    
		Thread->used = 1;
	    Thread->magic = 1234;
		Thread->name_address = (unsigned long) name;  //Name.   
		//@todo: Usar Thread->name. 
		//Thread->cmd @todo.

        //Thread->process = (void*) Process;

		// Procedimento de janela.
	    Thread->procedure = (unsigned long) &system_procedure;
		
		// Msg support. //Argumentos.
		Thread->window = NULL;        //arg1.
	    Thread->msg = 0;              //arg2.
	    Thread->long1 = 0;            //arg3.
	    Thread->long2 = 0;            //arg4.		

        // Caracteristicas.
		// TYPE_IDLE;    //?? //Type...@todo: Rever. 
	    Thread->type = TYPE_SYSTEM; 
	    Thread->state = INITIALIZED;  
		//Apenas Initialized, pois a função SelectForExecution
		//seleciona uma thread para a execução colocando ela no
		//state Standby.	
		
		//@TODO: ISSO DEVERIA VIR POR ARGUMENTO
        Thread->plane = FOREGROUND;	
		
		// A prioridade básica da thread é igual a prioridade básica do processo.
		// Process->base_priority;
		// priority; A prioridade dinâmica da thread foi passada por argumento.
		Thread->base_priority = (unsigned long) KernelProcess->base_priority; 
		Thread->priority = (unsigned long) Thread->base_priority; 			
		
		//IOPL.
		//Se ela vai rodar em kernel mode ou user mode.
		//@todo: herdar o mesmo do processo.
		Thread->iopl = RING3;             // Process->iopl;  		
		Thread->saved = 0;                // Saved flag.	
		Thread->preempted = PREEMPTABLE;  // Se pode ou não sofrer preempção.
		
		//Heap and Stack.
	    //Thread->Heap;
	    //Thread->HeapSize;
	    //Thread->Stack;
	    //Thread->StackSize;

        // Temporizadores. 
        // step - Quantas vezes ela usou o processador no total.  		
	    // quantum_limit - (9*2);  O boost não deve ultrapassar o limite. 
		Thread->step = 0;                           
        Thread->quantum = QUANTUM_BASE;    
        Thread->quantum_limit = QUANTUM_LIMIT; 			
		
		
		// runningCount - Tempo rodando antes de parar.
		// readyCount - Tempo de espera para retomar a execução.
		// blockedCount - Tempo bloqueada.
        Thread->standbyCount = 0;
	    
		Thread->runningCount = 0;   
		
		Thread->initial_time_ms = get_systime_ms();
		Thread->total_time_ms = 0;
		
		
	    //quantidade de tempo rodadndo dado em ms.
	    Thread->runningCount_ms = 0;
		
	    Thread->readyCount = 0;      
	    Thread->ready_limit = READY_LIMIT;
	    Thread->waitingCount = 0;
	    Thread->waiting_limit = WAITING_LIMIT;
	    Thread->blockedCount = 0;    		
	    Thread->blocked_limit = BLOCKED_LIMIT;
		
	    // Not used now. But it works fine.
		Thread->ticks_remaining = 1000;    	

	    // Signal
	    // Sinais para threads.
	    Thread->signal = 0;
        Thread->signalMask = 0;	


		// @todo: 
		// Essa parte é dependente da arquitetura i386.
		// Poderá ir pra outro arquivo.
		
		// init_stack:
		// O endereço de início da pilha é passado via argumento.
		// Então quem chama precisa alocar memória para a pilha.
		// @todo: Podemos checar a validade dessa pilha ou é problema 
		// na certa.
		
		// init_eip:
		// O endereço início da sessão de código da thread é 
		// passado via argumento. Então quem chama essa rotina 
		// deve providendiar um endereço válido.
		// Obs: init_eip Aceita endereços inválidos pois a thread 
		// fecha nesses casos por PG fault. Mas o sistema pode travar 
		// se for a única thread e um único processo. 
		
		//if( init_stack == 0 ){ ... }
		//if( init_eip == 0 ){ ... }
		
		// Contexto x86 usado pela thread.
		
		//Context.
		// ss (0x20 | 3)
		// cs (0x18 | 3)
	    Thread->ss = 0x23;    //RING 3.
	    Thread->esp = (unsigned long) init_stack; 
	    Thread->eflags = 0x3200;
	    Thread->cs = 0x1B;                                
	    Thread->eip = (unsigned long) init_eip; 
		
		//O endereço incial, para controle.
		Thread->initial_eip = (unsigned long) init_eip; 
		
		// (0x20 | 3)
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
		
		// @todo: 
        // O processo dono da thread precisa ter um diretório 
		// de páginas válido.
		
		// #bugbug
		// Page Directory. (#CR3).
		// Estamos usando o page directory do processo.
		// Page directory do processo ao qual a thread pertence.
		
		Thread->DirectoryPA = (unsigned long ) Process->DirectoryPA; 


        //ServiceTable ..
        //Ticks ...
        //DeadLine ... 

		
		//Thread->PreviousMode  //ring???
		
		//Thread->idealprocessornumber
		
		//Thread->event
		
	    // ORDEM: 
		// O que segue é referenciado com pouca frequência.

	    Thread->waitingCount = 0;    //Tempo esperando algo.
	    Thread->blockedCount = 0;    //Tempo bloqueada.	
	
        //À qual processo pertence a thread.  
		Thread->process = (void *) Process; 	 	                      
        
		//Thread->window_station
		//Thread->desktop
         
		
		//Thread->control_menu_procedure
		
		//Thread->wait4pid =

		//razões para esperar.
		for ( w=0; w<8; w++ ){
			Thread->wait_reason[w] = (int) 0;
		}
		
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

 
	// #importante
    // Contador de threads
    // Vamos atualizar o contador de threads, 
	// pois mais uma thread existe, mesmo que não esteja rodando ainda.
	
	ProcessorBlock.threads_counter++;
	
	//limits 
	
	if ( ProcessorBlock.threads_counter >= THREAD_COUNT_MAX )
	{
	    printf ("create_thread: counter fail, cant create thread\n");
        die();
		//return NULL; 		
	};

		
// Done.
done:
    
	// Warning !!! 
	// ( NÃO COLOCAR PARA EXECUÇÃO, 
	//   OUTRA FUNÇÃO DEVE COLOCAR PARA EXECUÇÃO )
	
    //SelectForExecution(t);  //***MOVEMENT 1 (Initialized ---> Standby)
    return (void *) Thread;
};


/*
 *********************************************
 * GetCurrentThreadId
 *     Pega o id da thread atual.
 *     Obs: current_thread já é o id.
 */
int GetCurrentThreadId (){
	
	return (int) current_thread;
};


/*
 ********************************************************
 * GetCurrentThread:
 *     Retorna o endereço da estrutura da thread atual.
 *
 */
void *GetCurrentThread (){
	
    struct thread_d *Current;
	
	if (current_thread < 0 || current_thread >= THREAD_COUNT_MAX ){
		return NULL;
	}
	
	Current = (void *) threadList[current_thread];	
	
	if ( (void *) Current == NULL ){
        return NULL;
	}
	
	return (void *) Current;
};


/*
 *******************************************************
 * FindReadyThread:
 *     Pega a primeira thread READY que encontrar.
 *     E se não encontrar nenhuma, retorna NULL.
 */
void *FindReadyThread (){
	
	int Index;
    struct thread_d *Thread;  
    
	for ( Index=0; Index<THREAD_COUNT_MAX; Index++ )
	{
	    Thread = (void *) threadList[Index];	
		
		if ( (void*) Thread != NULL )
		{
            if ( Thread->used == 1 && 
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
//fail:
    return NULL;
};


/*
 ********************************************************
 * SelectForExecution:
 *     Um thread entra em standby, sinalizando que está pronto para entrar 
 * em execução.
 *     Nesse caso, durante a rotina de taskswitch, checar-se-a se existe um 
 * thread em estado standby, caso haja, a thread é colocada pra executar pelo 
 * método spawn. 
 * Esse método de spawn já foi testado, segundo a contagem, duas thread 
 * começaram a rodas através desse método de spawn. 
 * Provavelmente as threads 'shell' e 'taskman', pois a thread 'idle' é 
 * chamada com um spawn exclusivo para ela, o que é desnecessário e 
 * poderá ser revisto. @todo
 *     
 *  *** MOVIMENTO 1, (Initialized --> Standby).
 */
 
void SelectForExecution ( struct thread_d *Thread ){
	
	if ( (void *) Thread == NULL)
	{
        return;
	} 

	// @todo: if initialized ---> Standby.
	// @todo: if zombie ---> Standby.
	//
	// Talvez aqui seja necessário checar o estado da thread.
	// Quem pode entrar no estado standby??
	// >> Uma thread no estado initialized pode entrar no estado standby 
	// >> Uma thread no estado zombie pode entrar no estado standby.
	// >> @todo: se uma thread estiver em qualquer um dos outros estados ela 
	// não pode entrar em stadby.
	
//setState:
    
	//*MOVIMENTO 1, (Initialized --> Standby).
    
	Thread->state = (int) STANDBY;
	queue_insert_data ( queue, (unsigned long) Thread, QUEUE_STANDBY );	
};


//Get State. (Zero é tipo NULL?).
int GetThreadState (struct thread_d *Thread){
	
	if ( (void *) Thread == NULL ){
        return (int) 0;
	}
	return (int) Thread->state;
};


//Get Type. (Zero é tipo NULL?).
int GetThreadType (struct thread_d *Thread){
	
	if( (void *) Thread == NULL ){
        return (int) 0;
	}  
    return (int) Thread->type;
};



/*
 ********************************************
 * show_thread_information:
 *     Mostra informações sobre as threads.
 */
void show_thread_information (){
	
	struct thread_d *Current;	
	
	printf("show_thread_information:\n");		
	
	//Limits.
	if ( current_thread < 0 || current_thread >= THREAD_COUNT_MAX ){
		
		return;
	}
	
	Current = (void *) threadList[current_thread];
	
	if( (void *) Current == NULL )
	{
	    printf("pc-thread-show_thread_information:\n");	
	    return;
		
	} else {
	    
		printf("currentTID={%d}\n",current_thread);
		//...
	};
	
	printf("idle={%d}\n",idle);

	//Mostra Slots. 
	//threadi.c
    mostra_slots ();    
	
	/*
	 * @todo: 
	 *     Mostra filas: Ready, Waiting ...
	 *     checar estruturas de filas no debug.
	 *     Erro: Mostrar filas não deve fazer parte dessa rotina.
	 */
	//show_queue_information(queue);
	
	//Nothing for now!
	

    printf("Done\n");
	refresh_screen ();
};



/*
 *******************************************************
 * init_threads:
 *     Inicializa o thread manager.
 *     Inicializa as estruturas e variáveis 
 *     que lidam com threads.
 *
 */
int init_threads (){
	
	//Globais.	 
	current_thread = 0;                        //Atual. 
	ProcessorBlock.threads_counter = (int) 0;  //Número de threads no processador.	
	old = 0;                                   //?
    forkid = 0;                                //
    task_count = (unsigned long) 0;            //Zera o contador de tarefas criadas.
	//...
	
	// @todo: Porque essas variáveis usam o termo 'task'?
	//        task é sinonimo de process.
	
	//Variáveis usadas na inicialização de uma nova tarefa.	
	start_new_task_status  = (unsigned long) 0;    //Se há uma nova tarefa.
	start_new_task_id = (int) 0;                   //Id dá nova tarefa.
	start_new_task_address = (unsigned long) 0;	   //Endereço da nova tarefa.
	
	//@todo: Há mais variáveis para serem inicializadas??!!
	
	
	//Zerando a lista de threads.
	int i=0;
	while ( i < THREAD_COUNT_MAX ){
	    threadList[i] = (unsigned long) 0;   
        ++i;
	}
	
	//
	// @todo: Nada mais?
	//

	return (int) 0;
};



/*
 **********************************************************
 * thread_getchar:
 *
 * Esse é o serviço 137.
 * Isso é usado pela biblioteca stdio em user mode na função getchar().
 */

int thread_getchar (){
	
	unsigned char SC;
	int save;
	
	//pode ser que esse aplicativo não tenha janela,
	//mas esteja rodando na janela do shell.
	struct window_d *wFocus;
	
	struct thread_d *t;
	
	//
	// Bloqueia pra que nenhum aplicativo pegue mensagens 
	// na estrutura de janela até que window_getch termine.
	//
	
	//window_getch_lock = 1;
	
	//
	// Pegamos um scancode na fila do teclado,
	// transformamos ela em mensagem e colocamos a 
	// mensagem na estrutura da janela com o foco de entrada.
	//
	

	SC = (unsigned char) keybuffer[keybuffer_head];
	
	//Limpa o offset na fila de teclado 
	//onde pegamos o scancode.
	
	keybuffer[keybuffer_head] = 0;
	
	//Circulamos a fila de teclado.
	keybuffer_head++;
	if( keybuffer_head >= 128 ){
	    keybuffer_head = 0;	
	}

 
    //isso coloca a mensagem na fila da thread atual.
	
	KEYBOARD_LINE_DISCIPLINE ( SC );	

	
 	
	//
	// Agora vamos pegar a somente a parte da mensagem 
	// que nos interessa, que é o caractere armazenado em long1.
	// Obs: Somente queremos o KEYDOWN. Vamos ignorar as outras 
	// digitações.
	//
	
	//fast way 
	//@todo: melhorar isso
	wFocus = (void *) windowList[window_with_focus];
	
	if ( (void *) wFocus == NULL )
	{
		//fail 
		//free(wFocus);
		goto fail;
		
	} else {
		
		if ( wFocus->used != 1 || wFocus->magic != 1234 )
		{
			goto fail;
		}
		
		//#importante
		//Essa é a thread de input da janela com o foco de entrada.
		//ou seja, somente o aplicativo que tiver o foco de entrada vai pegar 
		//mensagens aqui.
		
		t = (void *) wFocus->InputThread;
		
		if ( (void *) t == NULL  )
		{
		    goto fail;	
		}
		
		
		if ( t->used != 1 || t->magic != 1234 )
		{
			goto fail;
		}
		
		
		//Aqui temos uma thread válida e uma janela válida.
		
		// A mensagem precisa ser MSG_KEYDOWN, ou seja, é válida 
        // apenas para teclas pressionadas.
		
		if ( t->msg != MSG_KEYDOWN )
		{
		    goto fail;	
		}		
		
		save = (int) t->long1;
		
		//limpa
		
		t->window = 0;
		t->msg = 0;
		t->long1 = 0;
		t->long2 = 0;
					
	    //sinaliza que a mensagem foi consumida, 
		//e que não temos nova mensagem.
	    
		t->newmessageFlag = 0;
	
	    //window_getch_lock = 0;
		return (int) save;
	};

	
fail:
done:
   // window_getch_lock = 0;
	return (int) -1; //erro	
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

