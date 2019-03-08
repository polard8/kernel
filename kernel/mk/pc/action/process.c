/*
 * File: pc/process.c 
 *
 * Descrição:
 *     Gerenciamento de processos.
 *     PM - Process Manager (Parte fundamental do Kernel Base).
 *     Interfaces para o kernel chamar as rotinas de gerenciamento de
 * processos. 
 *     As rotinas aqui são independentes da arquitetura, quem se preocupa
 * com a arquitetura são as rotinas de inicialização comecadas por Ki.
 *     'Ki' para módulos internos do kernel.
 *
 * Atribuições:
 *     Rotinas de gerenciamento das processos, criação, inicialização,
 * finalização, task switch e outros.
 *
 *    Tipos de Processos:
 *
 *    PB - Processos incluídos no Kernel Base.
 *    P0 - Processos em ring0.
 *    P1 - Processos em ring1.
 *    P2 - Processos em ring2.
 *    P3 - Processos em ring3, User Mode.	
 *
 * @todo: 
 * Essas interfaces devem ser padronizadas, obedecendo roteiros de abertura, 
 * fechamento, salvamento e restauração de pilha ou argumento.
 * +Criar a função get_current_pid. (obs: Isso já existe)
 *
 * In this file:
 * ============
 *     +processSendSignal
 *     +create_process 
 *     +CloseAllProcesses
 *     +show_process_information
 *     +muitas outras rotinas...
 *
 * History:
 *     2015 - Create by Fred Nora.
 */
 
 
/*
    Fluxo padrão:
	
	The Standard Streams.
	
	Every process is initialized with three open file descriptors, 
	stdin, stdout, and stderr. 
	stdin is an abstraction for accepting input (from the keyboard or from pipes) and 
	stdout is an abstraction for giving output (to a file, to a pipe, to a console).

    That's a very simplified explanation but true nonetheless. 
	Those three file descriptors are collectively called 'The Standard Streams'.	
    
	Standard input - this is the file handle that your process reads to 
	get information from you.
    Standard output - your process writes normal information to this file handle.
    Standard error - your process writes error information here.
	
    Quando um programa inicia, 
	o sistema operacional automaticamente define quem é 
	a entrada padrão (geralmente o teclado) e quem é 
	a saída padrão (geralmente a tela).
*/ 
 
 
#include <kernel.h>



//
// Funções importadas.
//

extern unsigned long get_page_dir();


//
// Variáveis internas.
//

//int processmanagerStatus;
//int processmanagerError;
//...

int caller_process_id;

int processNewPID;   


//
//...
//

/*
 ***************************************
 * do_fork_process
 *     (Função em desenvolvimento)
 *     Clona um processo sem thread.
 *     Clona o processo atual.
 *     Retorna o PID do clone.
 */
 
pid_t do_fork_process (){
	
	int PID;
	
	struct process_d *Clone;
	struct process_d *Current;
	
	int Ret = -1;
	
	
	//printf("\n");
	printf("do_fork_process: Cloning the current process ...\n");
	
	
	// ## Current ##
	// Checando a validade do processo atual.
	
	//if ( current_process < 0 )
	//    return 0;
	
	Current = (struct process_d *) processList[current_process];
	
	if ( (void *) Current == NULL )
	{
		printf("do_fork_process: current, struct \n");
		goto fail;
	
	}else{
		
		if ( Current->used != 1 || Current->magic != 1234 ){
		    
			printf("do_fork_process: current, validation \n");
			goto fail;		
		}
		
	    //#debug
	    //printf(">>> check current process: %d %d \n", current_process, Current->pid );		
		goto do_clone;
		//...
	};
	
	
	//
	// ## Clone ##
	//
	
do_clone:
	
	//Cria uma estrutura do tipo processo, mas não inicializada.
	
	Clone = (struct process_d *) processObject();
	
	if ( (void *) Clone == NULL )
	{
		printf("do_fork_process: Clone struct fail \n");
		
		goto fail;
	
	} else {
		
		
		// Obtêm um índice para um slot vazio na lista de processos.
		
	    PID = (int) getNewPID ();
		
		//if ( PID <= 0 ){
			
		if ( PID == -1 || PID == 0 )
		{	
			printf("do_fork_process: getNewPID fail %d \n", PID);
			goto fail;
		}
		
		Clone->pid = PID;
		
		Clone->used = 1;
		Clone->magic = 1234;
		
		//#obs: Na hora de copiar o processo, a estrutura do clone 
		//receberá os valores da estrutura do processo atual,
		//até mesmo o endereço do diretório de páginas.
		
		//...
		
		//Salvando na lista.
		
		processList[PID] = (unsigned long) Clone;
		
		//
		// ## clone  ##
		//
		
		// Clona efetivamente. 
		
		// #bugbug:
		// Essa rotina tem que ter um retorno, para falharmos 
		// caso ela falhe.
		
		Ret = processCopyProcess ( Current->pid, Clone->pid );
		
		if ( Ret != 0 )
		{
			printf("do_fork_process: processCopyProcess fail \n");
		    goto fail;	
		}
		    
		// Ok, retornando o número do processo clonado.
		
		printf ("do_fork_process: done\n");
		
		return (pid_t) PID;	
	};

    // Fail.	
    	
fail:
    return (pid_t) -1;	
}


/*
 * processObject:
 *     Cria uma estrutura do tipo processo, mas não inicializada.
 */
 
struct process_d *processObject (){
	
	struct process_d *p;
	
	p = (void *) malloc ( sizeof(struct process_d) );
	
	if ( (void *) p == NULL )
	{
	    printf("processObject: fail");
		die();
	};	
	
	return (struct process_d *) p;
}


/*
 * getNewPID:
 *     Pegar um slot vazio na lista de processos.
 *     +Isso pode ser usado para clonar um processo.
 */
 
pid_t getNewPID (){
	
	struct process_d *p;
	
	
	// Começaremos a busca onde começa o range de IDs de processos de usuário.
	
	int i = USER_BASE_PID;
	
	while ( i < PROCESS_COUNT_MAX )
	{
		
	    p = (struct process_d *) processList[i];	
		
		// Se encontramos um slot vazio.
		// retornaremos o índice.
		
		if ( (void *) p == NULL )
		{	
			return (pid_t) i;
		}
		
		i++;
	};
	
	// Fail.
	
    return (pid_t) -1;	
}


/*
 * processTesting:
 *     Testando se o processo é válido. Se for válido retorna 1234.
 *     @todo: repensar os valores de retorno. 
 * system call (serviço 88.)
 */

int processTesting (int pid){
	
	struct process_d *P;
	
	P = (void *) processList[pid];
	
	if ( (void *) P == NULL )
	{
		return (int) 0;
	}else{		
		
		if ( P->used == 1 && P->magic == 1234 ){
	        return (int) 1234;			
		}
	};
	
//fail:
	return 0;
}


/*
 * processSendSignal:
 *     Envia um sinal para um processo.
 *     Se o sinal e o processo forem válidos, um sinal é colocado
 * no PCB do processo.
 *     @todo: Rotinas envolvendo sinais devem ir para outro arquivo.
 */

int processSendSignal (struct process_d *p, unsigned long signal){
	
	//SIGNAL_COUNT_MAX
	
	//Limit
    //if(signal >= 32){
	//	return 1;
	//}
	
	if (signal == 0)
	{
		return 1;
	};
	
	//struct fail
	//if( (void*) p == NULL ){
	//	return 1;
	//}		
	
//ok:	
	//Ok
	if ( (void*) p != NULL )
	{	
		p->signal = (unsigned long) signal;
		return 0; //(int) signalSend(p,signal);
	}
	
	//...
	
//fail:
	
	return 1;
}


/*
 ****************************************
 * processCopyProcess
 *     copiar um processo.
 *     isso será usado por fork.
 */
 
int processCopyProcess ( pid_t p1, pid_t p2 ){
	
	int Status = 0;
	
    struct process_d *Process1;	
	struct process_d *Process2;
	
	if ( p1 == p2 ){
		goto fail;
	}
	
	//Check limits
	//if( p1 < 1 ...
	//if( p2 < 1 ...
	
	Process1 = (struct process_d *) processList[p1];
	Process2 = (struct process_d *) processList[p2];
	
	
	if ( (void *) Process1 == NULL )
	{
		printf("processCopyProcess: Process1\n");
		goto fail;
		
	}else{
		
		if( Process1->used != 1 || Process1->magic != 1234 )
		{
		   printf("processCopyProcess: Process1 used magic \n");
		   goto fail;			
		}	
	};
	
	if ( (void *) Process2 == NULL )
	{
		printf("processCopyProcess: Process1\n");
		goto fail;
	}else{

		if( Process2->used != 1 || Process2->magic != 1234 )
		{
		   printf("processCopyProcess: Process2 used magic \n");
		   goto fail;			
		}	
	};
	
	
	//copy
//copy:	

	Process2->objectType = Process1->objectType;
	Process2->objectClass = Process1->objectClass;	
	
	//Identificadores.
	Process2->pid  = (int) p2;       //PID.
    Process2->ppid = Process1->ppid; //PPID. 
	Process2->uid  = Process1->uid;  //UID. 
    Process2->gid  = Process1->gid;  //GID. 
		
	//State of process
	Process2->state = Process1->state;  
	
	//Plano de execução.
    Process2->plane = Process1->plane;		
		
	Process2->used = Process1->used;
	Process2->magic = Process1->magic;			
		
	//Process->name_address = NULL;
	
	Process2->framepoolListHead = Process1->framepoolListHead;
	
	//
	// * page directory address
	//
	
	Process2->DirectoryPA = Process1->DirectoryPA;
	
	Process2->Image = Process1->Image;
	
    //heap
	Process2->Heap = Process1->Heap;    
	Process2->HeapEnd = Process1->HeapEnd; 
	Process2->HeapSize = Process1->HeapSize;  	
	
	//stack
	Process2->Stack = Process1->Stack;   
	Process2->StackEnd = Process1->StackEnd; 
	Process2->StackSize = Process1->StackSize;   	
	Process2->StackOffset = Process1->StackOffset; 	
	
	
	Process2->iopl = Process1->iopl;
	
	
	
	Process2->base_priority = Process1->base_priority;
	Process2->priority = Process1->priority;	
	
	//?? herda a lista de threads ??
	Process2->threadListHead = Process1->threadListHead;
	
	Process2->zombieChildListHead = Process1->zombieChildListHead;
		
	Process2->exit_code = Process1->exit_code;
	
	Process2->dialog_address = Process1->dialog_address;
	
	//message support.
	Process2->window = Process1->window;  //arg1. 
	Process2->msg    = Process1->msg;     //arg2.
	Process2->long1  = Process1->long1;   //arg3.
	Process2->long2  = Process1->long2;   //arg4.		
	
	Process2->prev = Process1->prev; 		
	Process2->next = Process1->next; 

	Status = 0;
	goto done;	
	
fail:
	Status = 1;
    printf("processCopyProcess: fail:\n");
done:
    return (int) Status;	
};


/*
 ***********************************************************************
 * create_process:
 *     Cria process para ring 3.
 *     Preenche o PCB (Process Control Block).
 *
 * @todo: 
 *     Um processo na verdade inclui tudo sobre a tarefa,
 *     Desde o nome do arquivo até o carregamento, registro e execução.
 *
 * Obs:
 *     Um job é um conjunto de processos.
 *     Tudo depende do tipo (funcionalidade): 
 *     SYSTEM, PERIODIC, ROUND_ROBIN, IDLE.
 *
 *    Classes de processos (tipo de nível):
 *
 *    PB - Processos incluídos no Kernel Base.
 *    P0 - Processos em ring0.
 *    P1 - Processos em ring1.
 *    P2 - Processos em ring2.
 *    P3 - Processos em ring3, User Mode.
 *
 *
 * @todo: 
 * Esse função deve chamar uma rotina de criação de diretório. 
 * Quando um processo é criado deve-se criar o seu diretório e criar 
 * as pagetables que o processo vai usar de acordo com o tamanho do 
 * processo. 
 *
 * @todo: processCreateProcess(...)
 *
 * @todo: 
 * Aumetar o número de argumentos para dar o suporte necessário para 
 * criar um processo do jeito que for necessário
 */

struct process_d *create_process ( struct room_d *room,
                                   struct desktop_d *desktop,
                                   struct window_d *window,
                                   unsigned long base_address, 
                                   unsigned long priority, 
                                   int ppid, 
                                   char *name, 
                                   unsigned long iopl,
                                   unsigned long directory_address )
{
  
	int i=0;
	
	pid_t PID;
	
    struct process_d *Process;

    // Para a entrada vazia no array de processos.
    struct process_d *Empty;      	

    // @todo:
    // Melhorar esse esquema de numeração e 
	// contagem de processos criados.
	
    if ( processNewPID < USER_BASE_PID || processNewPID >= PROCESS_COUNT_MAX )
	{
		processNewPID = (int) USER_BASE_PID;	
	};
	
	PID = (int) processNewPID;
	
	Process = (void *) malloc ( sizeof(struct process_d) );
	
	if ( (void *) Process == NULL )
	{
	    printf("pc-process-create_process: Process");
		die();
		
		//@todo: Aqui pode retornar NULL.
	};


    //Loop.	
	// #BugBug: 
	// Isso pode virar um loop infinito.
	
get_next:
	
/*	
	i++;
	
	if ( i >= PROCESS_COUNT_MAX )
	{
		// #bugbug: 
		// Isso deixa o sistema devagar caso não apareça 
		// a mensagem.
		
		printf("pc-process-create_process: End of list");
        refresh_screen();
		
		return NULL;
		//while(1){}
	};
	
*/	
	
	// Get empty.
		// Obtêm um índice para um slot vazio na lista de processos.
		
	PID = (int) getNewPID ();
			
	if ( PID == -1 || PID == 0 )
	{	
		printf("do_fork_process: getNewPID fail %d \n", PID);
		refresh_screen();
		return NULL;
	}
		
	Empty = (void *) processList[PID];
	
	//Se o slot estiver ocupado tentaremos o próximo.
	//Na verdade podemos usar aquela função que procura por um vazio. 
   	
	
    if ( (void *) Empty != NULL )
	{
		
		goto get_next;
		
	}else{
		
		//Object.
		Process->objectType = ObjectTypeProcess;
		Process->objectClass = ObjectClassKernelObjects;
		
		processNewPID = (int) PID;
		
		//Identificadores.
		Process->pid  = (int) PID;                  //PID.
        Process->ppid = (int) ppid;                 //PPID. 
		Process->uid  = (int) GetCurrentUserId();   //UID. 
        Process->gid  = (int) GetCurrentGroupId();  //GID. 

		//State of process
		Process->state = INITIALIZED;  

		//@TODO: ISSO DEVERIA VIR POR ARGUMENTO
        Process->plane = FOREGROUND;		
		
		//Error.
		//Process->error = 0;
		
		Process->used = 1;
		Process->magic = 1234;	
		
		//Name.
		//Process->name = name; //@todo: usar esse.
		//Process->cmd = NULL;  //nome curto que serve de comando.
		Process->name_address = (unsigned long) name;
		
		//lista de streams...
		//#todo temos que zerar essa lista e criarmos 3 streams para o processo.
		for ( i=0; i< NUMBER_OF_FILES; i++ ){
		    Process->Streams[i] = 0;
	    }
		
		//Process->terminal =
		
		//
	    //    ****  Banco de dados ****
		//
		
		//bancos de dados e contas do processo.
		//Process->kdb =
		//Process->gdbListHead =
		//Process->ldbListHead =
		//Process->aspaceSharedListHead =
		//Process->aspacePersonalListHead =
		//Process->dspaceSharedListHead =
		//Process->dspacePersonalListHead =
		
		// Inicializando a lista de framepools do processo.
		// @todo: Todo processo deve ser criado com pelo menos um 
		// frame pool, o que é equivalente a 4MB. (uma partição)
		// Obs: Um framepool indica onde é a área de memória fisica
		// que será usada para mapeamento das páginas usadas pelo processo.
		
		Process->framepoolListHead = NULL;
		
		
		//Thread inicial.
		//Process->thread =
		
		//Process->processImageMemory =
		//Process->processHeapMemory =
		//Process->processStackMemory =
		
	    //
	    // ORDEM: O que segue é referenciado durante o processo de task switch.
	    //

		//
		// Page Directory: 
		//     Alocar um endereço físico para o diretório de páginas do 
		// processo a ser criado, depois chamar a função que cria o diretório.
		//
		// @todo:
		// *IMPORTANTE: Por enquanto os processos são criadas usando o 
		// diretório de páginas do processo Kernel. Mas temos que criar 
		// um diretório novo pra cada processo criado.
		// O diretório de todos os processos de usuário serão iguais. 
		// Terão uma área de usário particular e uma área compartilhada 
		// em kernel mode.
		//
		//@todo: Alocar um endereço físico antes, depois chamar a função que 
		// cria o pagedirectory.
		//@todo: 
        //opção: KERNEL_PAGEDIRECTORY; //@todo: Usar um pra cada processo.

        if (directory_address == 0)
        {
			printf("create_process: page directory address fail\n");
			return NULL;
		}			
		
		//Process->Directory = (unsigned long ) directory_address; 
		
		Process->DirectoryVA = (unsigned long ) directory_address;
		Process->DirectoryPA = (unsigned long) virtual_to_physical ( directory_address, gKernelPageDirectoryAddress );
		
        //cancelados. 
		//Process->mmBlocks[32]
		//Process->mmblockList[32]
		
		
		//Process->processMemoryInfo
		
		
		// #todo: 
		// Precisa alocar espaço na memória física.
        // Precisa criar page tables para essas areas de cada processo.		
		// Os endereços virtuais dessas areas dos processos são sempre os mesmos.
		// mas os endereços físicos dessas areas variam de processo pra processo.

		// Imagem do processo.
		// ?? Provavelmente esse endereço é virtual.
		// Queremos que esse endereço seja padronizado e que todos 
		// os processos usem o mesmo endereço.
		
		// #bugbug
		// Todos os processos de usuário começam no mesmo endereço virtual.
		// Porém temos os processos em kernel mode e os processos do gramado core
		// que usam endereços virtuais diferentes.
		// #todo: Rever isso.
		// #todo: estamos suspendendo essa informação.
		
		//
		// ## IMPORTANTE ##
		//
		
		// Base da imagem do processo.

		
		//Na verdade precisamos aceitar o endereço passado via argumento,
		//pois nem todos processos começam no endereço default.
		
		//UPROCESS_IMAGE_BASE;
		Process->Image = base_address;   
		
		// Tamanho da imagem do processo.
		// Temos que chamar a função que pega o tamanho de um arquivo,
		// #bugbug: Porem, no momento o kernel não consegue ler arquivos
		// que estão em subdiretórios corretamente e os programas estão em subdiretórios.
		// #obs: O tamanho também poderia ser passado por arguemento.
		// #ou um argumento com ponteiro pra estrutura de informação sobre uma imagem.
		Process->ImageSize = 0;              	    
		
		//#todo: estrutura com informações sobre a imagem do processo.
		Process->image_info = NULL;
		
		// Heap e Stack:
		//
		// @todo: #BugBug 
		// O Heap e a Stack devem estar dentro da área de memória do processo.
		// Uma pagetable do diretório é para o heap e outra para a stack.
        // Cada pagetable no diretório do processo é pra uma coisa.
        //
		// Obs: O endereço virtual do heap e da stack dos processos serão 
		// os mesmos para todos os processos, assim como o endereço virtual 
		// de carregamento da imagem.
		
		// Heap and Stack. 
		// #importante: (Endereços virtuais).
		// Por isso pode ser o mesmo para todos os processos.
		
		
		// #### HEAP ####
		
		//CreatePageTable ( Process->DirectoryVA, 512, 0 );
		
		
		//Process->Heap = (unsigned long) 0x00400000; //funciona
		//Process->Heap = (unsigned long) 0xC0C00000; //funciona
		
		// g_heappool_va
        // endereço virtual do pool de heaps.
        // os heaps nessa área serão dados para os processos.
		// base + (n*size)
		if (g_heap_count < 0 || g_heap_count >= g_heap_count_max)
		{
			//erro 
			printf("create_process: g_heap_count limits");
			die();
			//refresh_screen();
			//while(1){ asm ("hlt"); };
		}
		
		Process->Heap = (unsigned long) g_heappool_va + (g_heap_count * g_heap_size);
		Process->HeapSize = (unsigned long) g_heap_size;
		Process->HeapEnd = (unsigned long) (Process->Heap + Process->HeapSize); 
		
		g_heap_count++;
		
		//Process->Heap = (unsigned long) allocPages (64); 

        //Process->Heap = (unsigned long) malloc (1024*32); //32kb		
		
		// Endereço do início do Heap do processo.
		// #bubug: Endereço do fim do heap.
		// Tamanho do heap, dado em KB.
	    //Process->Heap = UPROCESS_DEFAULT_HEAP_BASE;    
	    //Process->HeapEnd = 0; // @todo: (UPROCESS_DEFAULT_HEAP_BASE + UPROCESS_DEFAULT_HEAP_SIZE);
		//Process->HeapSize = (UPROCESS_DEFAULT_HEAP_SIZE/1024);    

		//Process->HeapPointer
		//Process->HeapLastValid
		//Process->HeapLastSize
	    
		// Endereço do início da Stack do processo.
		// Endereço do fim da stack do processo.
		// Tamanho da pilha, dada em KB.
		// #importante: Deslocamento do endereço do início da pilha em relação 
		// ao início do processo. 
		
		Process->Stack = UPROCESS_DEFAULT_STACK_BASE;   
	    Process->StackEnd = 0; // @todo: (UPROCESS_DEFAULT_STACK_BASE+UPROCESS_DEFAULT_STACK_SIZE);
		Process->StackSize = (UPROCESS_DEFAULT_STACK_SIZE/1024);   	
	    Process->StackOffset = UPROCESS_DEFAULT_STACK_OFFSET; 
	    

		//ring.
		Process->iopl = iopl; 
        
		
	    //PPL - (Process Permition Level).(gdef.h)
        //Determina as camadas de software que um processo terá acesso irrestrito.
	    //Process->ppl = pplK0;
		

		
	    //Process->callerq	   //head of list of procs wishing to send.
        //Process->sendlink;    //link to next proc wishing to send.
        //Process->message_bufffer		   //pointer to message buffer.
        //Process->getfrom_pid		       //from whom does process want to receive.
        //Process->sendto_pid	               //pra quem.

	    //Signal
	    //Process->signal = 0;
	    //Process->signalMask = 0;
		
		//cancelada.
		//Process->process_message_queue[8]
		
		//Outras coisas.
		
		//Prioridade.
		Process->base_priority = (unsigned long) priority;
		Process->priority = (unsigned long)  Process->base_priority;
		
	    //Que tipo de scheduler o processo utiliza. (rr, realtime ...).
	    //Process->scheduler_type = ;   		
		
		
		//Process->step
		//Process->quantum
		//Process->timeout
		//Process->ticks_remaining
		
		//Process->ThreadQuantum   //As threads do processo iniciam com esse quantum.
		
		
		//Process->threadCount = 0;    //Número de threads do processo.
		
		//Process->tList[32] 
		
		//Lista de threads.
		Process->threadListHead = NULL;
		
		Process->control = NULL;

        //Process->window_id 		
		
		
		//Process->event
		
	
        // #importante
		// user session, room and desktop.
		
		// #bugbug: 
		// Não temos informação sobre a user session, 
		// devemos pegar a estrutura de current user session. 
		// Para isso ela deve ser configurada na inicialização do gws,
		// antes da criação dos processo.
		
		Process->usession = CurrentUserSession;  // Current.
		Process->room = room;                    // Passado via argumento.
		Process->desktop = desktop;              // Passado via argumento.
		
		//Process->base_priority
		
		
		
		
	    // wait4pid: 
        // O processo esta esperando um processo filho fechar.
	    // Esse é o PID do processo que ele está esperando fechar.
		
		Process->wait4pid = (pid_t) 0;
		
		Process->zombieChildListHead = NULL;
		
		Process->exit_code = 0;
		

		//procedimento eem ring 0 por enquanto.
		Process->dialog_address = (unsigned long) &system_procedure;

		Process->signal = 0;
		Process->signal_mask = 0;
		
		//Msg support.
		//Argumentos do procedimento de janela.
		//@todo: Isso pode ser um ponteiro de estrutura,
		//a fila de mensgens pode ser uma fila de ponteiros.
		Process->window = NULL;    //arg1. 
	    Process->msg = 0;          //arg2.
	    Process->long1 = 0;        //arg3.
	    Process->long2 = 0;        //arg4.			
		
		Process->prev = NULL; 
		Process->next = NULL; 

		//Coloca o processo criado na lista de processos.
		processList[PID] = (unsigned long) Process;		
		//Nothing.
	};	

	
	//
	// ?? O que falta mais aqui. ??
	//
	
    // ...	
	
//Done.
done:
    return (void *) Process;
};

 
/*
 * CloseAllProcesses:
 *     Bloqueia todos os processos da lista de processos.
 *     Menos o processo '0'.
 *     processCloseAllProcesses();    
 */

void CloseAllProcesses (){
	
	int Index;
    struct process_d *P;

	// #importante:
	// Menos o 0, pois é o kernel. 
    
	for ( Index = 1; Index < PROCESS_COUNT_MAX; Index++ )
	{
		//Pega, bloqueia e tira da lista.
		P = (void*) processList[Index];
		P->state = PROCESS_BLOCKED;
        processList[Index] = (unsigned long) 0;		
	};		
	
	//Check process 0.
	P = (void *) processList[0];
	
	if ( (void *) P == NULL )
	{
		panic("CloseAllProcesses: P\n");
	};
}


/*
 * KeSaveCurrentContext:
 *     Interface para chamar rotina de salvamento de contexto de registradores.
  * obs: Não usaremos inicial Ke_
 */
void KeSaveCurrentContext()
{
   //sendo uma interface pode chamar a rotina de acordo com a arquitetura presente.
   //para isso pode-se usar hal.
    return;
};

/*
 * KeRestoreCurrentContext:
 *     Interface para chamar rotina de restauração de contexto de registradores.
  * obs: Não usaremos inicial Ke_
 */
void KeRestoreCurrentContext()
{
   //sendo uma interface pode chamar a rotina de acordo com a arquitetura presente.
   //para isso pode-se usar hal.
    return;
};
 
 
/*
 * KeCpuFaults:
 *     Interface para chamar a rotina de tratamento das fault de CPU.
 *     @todo: Talvez essa rotina possa ir para cpu.c
 *  * obs: Não usaremos inicial Ke_
 */ 

void KeCpuFaults (unsigned long fault_number){ 
		
	KiCpuFaults (fault_number);
}



/*
 * KeSpawnTask:
 *     Interface para rotina que executa pela primeira vez
 * uma tarefa em user mode.
 * @todo: deletar.  * obs: Não usaremos inicial Ke_
 */
void KeSpawnTask(int id)
{
    KiSpawnTask(id);
	//no return.
};




/*
 * KeSelectNextThread:
 *     Interface para chamar a rotina que seleciona a proxima tarefa para
 * rodar, baseado em criterios.
 * * obs: Não usaremos inicial Ke_
 */
int KeSelectNextThread(int current)
{
    
	//@todo: analizar o retorno.
	return (int) KiSelectNextThread(current);
}


/*
 * KeCheckTaskContext:
 *     Interface para chamar uma rotina de análise de contexto.
  * obs: Não usaremos inicial Ke_
 */
int KeCheckTaskContext( int task_id )
{
	//#bugbug Aqui estamos chamando uma rotina detro do 
	//kernel base, não é essa a ideia.
	// e se alguma rotina dentro do kernel estava chamando essa 
	// função é bom substituir a chamada por KiCheckTaskContext
    //@todo: preparação antes de chamar.filtros.
	return (int) KiCheckTaskContext(task_id);
};



/*
 * KeExecProcess:
 *     Interface para chamar a rotina que executa uma tarefa, dado
 * nome e endereço.
 *
 */
int KeExecProcess(int pid, unsigned long *process_address)
{
    return 0;
};


/*
 * KeDispatchProcess:
 *     Interface para chamr uma rotina para despachar uma thread.
 *     Server em user mode.
 */
void KeDispatchProcess(){
    return;
}

void KeDoProcessReady(int pid){
    return;
};

void KeDoProcessRunning(int pid){
    return;
};

void KeDoProcessSleeping(int pid){
    return;
};

void KeDoProcessZombie(int pid){
    return;
};

void KeDoProcessDead(int pid){
    return;
};


/*
 * KeStartTask:
 *     Interface para chamar uma rotina de execução de um processo,
 * dado seu id e seu endereço.
 */
void KeStartProcess(unsigned long pid, unsigned long *task_address){
    return;
};

 
 
/*
 * KeAcordarTarefa:
 *     Interface para chamar uma rotina de acordar um processo..
 */ 
void KeWakeupProcess(int pid)
{
    return;
}; 
 
  
/*
 * KeProcessExit:
 *     Interface para chamar uma rotina de 
 *     tratamento de fechamento de um processo.
 *     Chama um módulo externo para sair de uma tarefa.
 *     Chama um Server em user mode.
 */ 
void KeProcessExit()
{
    return;
};

/*
 * KeKillProcess:
 *     Chama um server em user mode pra
 *     fechar um processo.
 *       
 */ 
void KeKillProcess(int pid)
{
    return;
};

void KeNewProcessScheduler()
{
    return; 
}


int KeSetPriority()
{
    return 0;
}

//Aumenta a prioridade de um processo.
int KeIncreasePriority(int pid)
{
    return 0;
};

void KeSaveContextOfNewTask(int id, unsigned long *task_address)
{
    return;
};


void KeReloadCurrentTask()
{
    return;
};


void KeSetQuantum( unsigned long q)
{
    return;
};

unsigned long KeGetQuantum()
{ 
    return 0; 
};

void KeSetCurrentQuantum( unsigned long q)
{
    return;
};

unsigned long KeGetCurrentQuantum()
{ 
    return 0; 
};

void KeSetNextQuantum( unsigned long q)
{
    return;
};

unsigned long KeGetNextQuantum()
{ 
    return 0; 
};


//@todo: Não faz sentido chamar um módulo externo
//para setar o foco.
void KeSetFocus(int pid)
{
    return;
};

//@todo: Não faz sentido chamar um módulo externo
//para pegar o foco.
int KeGetFocus()
{ 
    return (int) 0; 
};

void KeDebugBreakpoint()
{
    //return;
};

void KeShowTasksParameters()
{
    //return;
};

void KeMostraSlots()
{
    //return;
};

void KeMostraSlot(int id)
{
    //return;
};

void KeMostraReg(int id)
{
    //return;
};

void KeShowPreemptedTask()
{
    //return;
};


void show_currentprocess_info (){
	
    struct process_d *Current;		
	
	if( current_process < 0 || 
	    current_process >= PROCESS_COUNT_MAX )
	{
		//printf("show_process_information: current_process fail\n");
		return;
	};

	//Struct.
	Current = (void *) processList[current_process];
	
	if ( (void *) Current == NULL )
	{
	    printf("show_process_information: Struct fail\n");
        return; 		
	
	} else {
		
		//Index.
		printf ("PID={%d} PPID={%d} UID={%d} GID={%d} \n",
		    Current->pid, Current->ppid, Current->uid, Current->gid );
	    //Name
		printf("Name={%s} \n", Current->name_address );
		
		//Image Address.
		printf("ImageAddress={%x} \n", Current->Image );
		
		//Directory Address. *IMPORTANTE.
		printf (">>DirectoryPA={%x} \n", Current->DirectoryPA );		
		printf (">>DirectoryVA={%x} \n", Current->DirectoryVA );
		//Heap and stack.
		printf("Heap={%x}  HeapSize={%d KB}  \n", Current->Heap, 
		    Current->HeapSize );
												  
		printf("Stack={%x} StackSize={%d KB} \n", Current->Stack, 
		    Current->StackSize );
		
		//...
	};
	
	refresh_screen();
};

/*
 ********************************************************
 * show_process_information:
 *     Mostra informações sobre os processos. 
 *     #todo: na verdade um aplicativo em user mode deve fazer esse trabalho
 * solicitando informações sobre cada processo através de chamadas.
 */

// Mostrar informações sobre os processos da lista.
// obs: as imagens são carregadas em endereços virtuais diferentes
// e o endereço mostrado é em relação ao diretório de páginas do kernel
// pois o kernel é que controla o posicionamento das imagens.

void show_process_information (){
	
	int i=0;
	
	struct process_d *p;	
    
	printf("show_process_information: \n\n");
	
	for ( i=0; i<PROCESS_COUNT_MAX; i++ )
    {
	    p = (void *) processList[i];
		
		if ( (void *) p != NULL && 
		           p->used == 1 && 
				   p->magic == 1234 )
	    {   
			printf ("PID=%d PPID=%d State=%d BaseAddress=%x ImageSize=%d DirectoryPA=%x DirectoryVA=%x iopl=%d prio=%d wait4pid=%d Name={%s}\n\n", 
				p->pid, 
			    p->ppid,
				p->state,
				p->Image,
				p->ImageSize,	
				p->DirectoryPA,
				p->DirectoryVA,	
				p->iopl,
				p->priority,
				p->wait4pid,	
				p->name_address );
	    }
		//Nothing.
    };	
	
    printf ("done\n");
	refresh_screen ();
}


/*
 **************************************************************
 * SetProcessDirectory:
 *     Configura o endereço do diretório de páginas do processo.
 *     @todo: Isso pode ser um serviço oferecido pelo kernel,
 * para um gerenciador de processos em user mode usar.
 * @todo: processSetDirectory(...)
 */

void SetProcessDirectory ( struct process_d *process, unsigned long Address ){
	
    if ( (void *) process != NULL )
	{
        process->DirectoryPA = (unsigned long) Address;        
	};
}


/*
 ************************************************************
 * GetProcessDirectory:
 *     Pega o endereço do diretório de páginas do processo.
 *     @todo: Isso pode ser um serviço oferecido pelo kernel,
 * para um gerenciador de processos em user mode usar.
 * @todo: processGetDirectory(...)
 */

unsigned long GetProcessDirectory( struct process_d *process )
{
    if( (void*) process != NULL )
	{
		//@todo: checar used e magic.
        return (unsigned long) process->DirectoryPA;
	};
	return (unsigned long) 0;
};


/*
 *********************************************************
 * GetPageDirValue:
 *     Pega o endereço do diretório de páginas do processo.
 *     processGetPageDirValue()
 */
unsigned long GetPageDirValue()
{
    return (unsigned long ) get_page_dir();
};



/*
 ***************************************************************
 * init_task:
 *     Inicia um processo.
 *     @todo: Mudar o nome para init_process().
 *            Inicializa a estrutura de um processo criado.
 *            Quando cria o processo, cria apenas sua estrutura,
 *            ficando a cargo dessa rotina inicializar a estrutura criada. 
 */ 

int init_task(int id)
{ 
    //@todo: inicializar uma estrutura para um processo criado.
	//obs: ja tem essa rotina feita em aalgum lugar..
	
    return (int) 0;   
};



/*
 *************************************************************
 * init_tasks: 
 *     Inicia as variáveis.
 *
 * @todo: 
 *     Bug bug, problemas na inicialização das estruturas.
 *     Implementar a alocação dinâmica na criação das tarefas.
 */

//#bugbug
//rever e deletar, se poss'ivel.

void init_tasks ()
{
    init_processes();	
};



/*
 ***********************************************************
 * init_processes:
 *    Inicaliza o process manager.
 *   #todo: rever esse nome, pois na verdade estamos inicializando variaveis 
 * usadas no gerenciamento de processo.
 */
 
void init_processes (){
	
    int i;	
	
	//
	// Iniciando variáveis globais.
	//
	
	kernel_request = 0;    // O que fazer com a tarefa atual.
	
	
	// ?? Contagem de tempo de execução da tarefa atual.	
	//não precisa, isso é atualizado pelo request()
	//kernel_tick = 0;                                 
	
	kernel_switch = 0;     // ?? Ativa o kernel switch do scheduler.
    
	current_process = 0;
	
	//
	// Inicializando a lista de processos.
	//
	
	i=0;
	while(i < PROCESS_COUNT_MAX){
	    processList[i] = (unsigned long) 0;
        ++i;
	};


	//
	// @todo: mais algo??
	//
	
Done:	
	return;
};


/*
 **********************************************************************
 * exit_process:
 *
 *     Exit process.
 *     Coloca o processo no estado PROCESS_TERMINATED, mas não destrói a 
 * estrutura do processo. Outra rotina destruirá as informações.
 *
 * @todo: 
 * Liberar a memória e os recursos usado pelo processo. Ou ainda apenas 
 * sinalizar a flag magic para que o GC a reutilize.
 *
 * @todo: 
 * Fechar as threads seguindo a lista encadeada.
 */

void exit_process ( pid_t pid, int code ){
	
	int i;
    struct process_d *Process;
	
    struct thread_d *Threads;
	struct thread_d *Next;	
	//...

	// Não fechar o processo 0. Ele é o kernel.
	if ( pid == 0 ){
		return;
	}
	
	//Limits. 
	if ( pid < 0 || pid >= PROCESS_COUNT_MAX ){
	    return;	
	}
	
	// Mais limites ??

#ifdef MK_VERBOSE	
	//Debug:
	printf ("exit_process: Terminating process %d\n", pid );
	refresh_screen();
#endif	
	

	// Pega o ponteiro para a estrutura, muda o código de saída 
	// e o status.
	
	Process = (void *) processList[pid];
	
	if( (void *) Process == NULL )
	{
		//printf ("Invalid PID\n");
		return;
	
	}else{	

		// Se estiver corrompida.
        if( Process->used != 1 || 
		    Process->magic != PROCESS_MAGIC )
		{
			return;
		};
		
		Process->exit_code = (int) code;    
		Process->state = PROCESS_TERMINATED; 
		//...
	};
		
#ifdef MK_VERBOSE
	//Debug:
	printf("exit_process: Terminating threads..\n");
	refresh_screen();
#endif		

	// Agora temos que terminar as threads que estão na lista 
	// de threads do processo.
	// Pegaremos a primeira da lista.
	// Se o head da list não foi inicializado corretamente 
	// dá page fault.
	
	Thread = (void *) Process->threadListHead;
		
	// Se não há nada na head.	
	if( Thread == NULL )
	{
		// @todo: Talvez haja mais o que fazer.
	    goto done;	
	}else{
		
		//used, magic ??
	};	
		
	
	// Se a primeira thread da lista é válida, então tentaremos
	// fechar toda a lista.
	
	while (1)
	{
		// ?? Qual deve fechar depois. ??
		
		printf(".\n");
		refresh_screen();
		
		// Salva o ponteiro para o próximo thread.
		Next = (void*) Thread->Next;
		
		// Confere se chegamos ao fim da lista.
		// 'Thread' fecha agora.
		
        if( Thread == NULL )
		{
		    goto done;	
		
		}else{
    
#ifdef MK_VERBOSE    
		    //fecha a thread.
		    printf ("exit_process: Killing thread %d.\n", Thread->tid );
#endif			
			
			// Kill !
			
			kill_thread ( Thread->tid );  					
		    
			// Prepara qual deve fechar agora.
		    // Havíamos salvo e agora é vez dela.
		    // Obs: Estamos reusando o ponteiro.
			
			Thread = (void *) Next;
		 };
        //Nothing.
	};		
	//nothing
done:
	
	
	//@todo:
	//    Escalonar o processo atual. Se o processo fechado foi o processo 
	// atual, precisamos de um novo processo atual. Usaremos o processo zero 
	// por enquanto. Obs: Devemos fazer aqui apenas escalonameto de processo
	// e não de thread.	

	//Zerando por enquanto.

	//?? Analizar essa parte.	
    //@todo: Select next process (idle)
	
	current_process = 0;	
    current_thread = 0;    //@todo: Deletar isso.	
	

	//Process->used = 0;
	//Process->magic = 0;
	//Process = NULL;
	
	
	//#todo: chamar o scheduler.
	//scheduler ();
	return;
}


// ??
int get_caller_process_id()
{
	return (int) caller_process_id;
};



// ??
void set_caller_process_id(int pid)
{
	caller_process_id = (int) pid;
};


/*
 *************************************************
 * init_process_manager:
 *     Initialize process manager.
 *     processInitializeProcessManager();
 */

int init_process_manager (){
	
	caller_process_id = (int) 0;
	
	processNewPID = (int) USER_BASE_PID;
	
	//...
		
	return (int) 0;
}


/*
 *Constructor.
int processmanagerProcessmanager(){
	;
};
*/


/*
int processmanagerInit(){
	;
};
*/


/*
 * GetProcessHeapStart:
 *     Pega o endereço do heap do processo.
 */

unsigned long GetProcessHeapStart ( pid_t pid ){
	
	struct process_d *process;
	
	//Limits.
	
	if ( pid < 0 || pid >= PROCESS_COUNT_MAX )
	{
		goto fail; 
	}
	
	process = (struct process_d *) processList[pid];
    
	if ( (void *) process == NULL )
	{
		goto fail;
		 
	}else{
		
		if ( process->used != 1 || process->magic != 1234 )
		{
			goto fail;
		}
		
		//Ok.
		return (unsigned long) process->Heap;
	};
	
fail:	
    return (unsigned long) 0;
}


/*
 * GetProcessPageDirectoryAddress:
 *
 */

unsigned long GetProcessPageDirectoryAddress ( pid_t pid ){
	
	struct process_d *process;
	
	//Limits.
	
	if( pid < 0 || pid >= PROCESS_COUNT_MAX )
	{
		goto fail; 
	};
	
	
	process = (struct process_d *) processList[pid];
    
	if ( (void *) process == NULL )
	{
		goto fail;
		 
	}else{
		
		if ( process->used != 1 || process->magic != 1234 ){
			goto fail;
		}
		
		return (unsigned long) process->DirectoryPA;
	};
	
fail:	
    return (unsigned long) 0;
}


//#todo
//encontrar um slot vazio em Process->Streams[]
//retornar o indice.
/*
int process_find_empty_stream_slot ( struct process_d *process );
int process_find_empty_stream_slot ( struct process_d *process ){

 	int i = 0;
	
	if ( (void *) process == NULL )
	{
		return -1;
		 
	}else{
		
		if ( process->used != 1 || process->magic != 1234 ){
			
			return -1;
		}
		
	    for ( i=0; i< NUMBER_OF_FILES; i++ )
	    {
	        if ( Process->Streams[i] == 0 )
		    {
		        return i;
		    }
	    }		
	};  
	
	return -1;
} 
*/

//
// End.
//
