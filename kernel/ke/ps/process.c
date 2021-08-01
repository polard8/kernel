

#include <kernel.h>


int caller_process_id;
int processNewPID;

// Quando criamos um novo processo.
//int NewProcessInitialized = FALSE;


int GetCurrentPID (void)
{
    return (int) current_process;
}



struct process_d *GetCurrentProcess(void)
{
    struct process_d *p;
    
    if ( current_process < 0 || 
         current_process >= PROCESS_COUNT_MAX )
    {
        return NULL;
    }

    p = (struct process_d *) processList[current_process];

    return (struct process_d *) p;
}


unsigned long __GetProcessStats ( int pid, int index ){

    struct process_d *p;


    if (pid<0){
        panic ("__GetProcessStats: pid \n");
    }

    // Process

    p = (void *) processList[pid];

    if ( (void *) p == NULL ){
        printf ("__GetProcessStats: struct \n");
        return 0; 

    } else {
        //checar validade.
		//...
    };


    switch (index){

        case 1:  return (unsigned long) p->pid;  break; 
        case 2:  return (unsigned long) p->ppid;  break; 
        case 3:  return (unsigned long) p->uid;  break; 
        case 4:  return (unsigned long) p->gid;  break; 
        case 5:  return (unsigned long) p->state;  break; 
        case 6:  return (unsigned long) p->plane;  break; 
        case 7:  return (unsigned long) p->input_type;  break; 
        case 8:  return (unsigned long) p->personality;  break; 
        case 9:  return (unsigned long) p->appMode;  break; 

        case 10:  
            return (unsigned long) p->private_memory_size;
            break;  

        case 11:
            return (unsigned long) p->shared_memory_size;
            break;          

        case 12:
            return (unsigned long) p->workingset_size;
            break;          

        case 13:
            return (unsigned long) p->workingset_peak_size;
            break;          

        case 14:
            return (unsigned long) p->pagefaultCount;
            break;          

        //case 15:  return (unsigned long) p->DirectoryPA;  break;
        //case 16:  return (unsigned long) p->DirectoryVA;  break;
        
        case 17:  return (unsigned long) p->Image;  break;
        case 18:  return (unsigned long) p->ImagePA;  break;
        case 19:  return (unsigned long) p->childImage;  break;
        case 20:  return (unsigned long) p->childImage_PA;  break;
        case 21:  return (unsigned long) p->Heap;  break;
        case 22:  return (unsigned long) p->HeapEnd;  break;
        case 23:  return (unsigned long) p->HeapSize;  break;
        case 24:  return (unsigned long) p->HeapPointer;  break;
        case 25:  return (unsigned long) p->HeapLastValid;  break;
        case 26:  return (unsigned long) p->HeapLastSize;  break;
        case 27:  return (unsigned long) p->Stack;  break;
        case 28:  return (unsigned long) p->StackEnd;  break;
        case 29:  return (unsigned long) p->StackSize;  break;
        case 30:  return (unsigned long) p->StackOffset;  break;
        case 31:  return (unsigned long) p->iopl;  break;
        case 32:  return (unsigned long) p->base_priority;  break;
        case 33:  return (unsigned long) p->priority;  break;
        case 34:  return (unsigned long) p->step;  break;
        case 35:  return (unsigned long) p->quantum;  break;
        case 36:  return (unsigned long) p->timeout;  break;
        case 37:  return (unsigned long) p->ticks_remaining;  break;
        
        case 38:  
            return (unsigned long) p->profiler_percentage_running;
            break;

        case 39:
            return (unsigned long) p->profiler_ticks_running;
            break;

        case 40:
            return (unsigned long) p->profiler_last_ticks;
            break;

        case 41:  return (unsigned long) p->thread_count;  break;
        case 42:  return (unsigned long) p->bound_type;  break;
        case 43:  return (unsigned long) p->preempted;  break;
        case 44:  return (unsigned long) p->saved;  break;
        case 45:  return (unsigned long) p->PreviousMode;  break;
        case 46:  return (unsigned long) p->wait4pid;  break;
        case 47:  return (unsigned long) p->exit_code;  break;
        case 48:  return (unsigned long) p->signal;  break;
        case 49:  return (unsigned long) p->umask;  break;
        case 50:  return (unsigned long) p->dialog_address; break;
        case 51:  return (unsigned long) p->ImageSize;  break;
           
        // #todo:
        // Precisamos da quantidade de p�ginas usadas.
    
        // ...
    };

    return 0;
}

// Systemcall 882.
// Pega o nome do processo.
// OUT: string len.
int getprocessname ( int pid, char *buffer ){

    struct process_d  *p;

    char *name_buffer = (char *) buffer;

    //#todo
    //checar validade dos argumentos.

    if (pid<0){
        debug_print ("getprocessname: [FAIL] pid\n");
        goto fail;
    }

    //#todo
    //buffer validation
 
    p = (struct process_d *) processList[pid]; 

    if ( (void *) p == NULL ){
        debug_print ("getprocessname: [FAIL] p\n");
        goto fail;
    }

    if ( p->used != TRUE || p->magic != 1234 )
    {
        debug_print ("getprocessname: [FAIL] Validation\n");
        goto fail;
    }

    // 64 bytes
    strcpy ( name_buffer, (const char *) p->__processname );  

//done:

    // #bugbug: 
    // Provavelmente isso ainda nem foi calculado.

    // Return the len.
    return (int) p->processName_len;

fail:
    return (int) (-1);
}


/*
 * processObject:
 *     Cria uma estrutura do tipo processo, mas não inicializada.
 *     #todo: Criar a mesma rotina para threads e janelas.
 */

// OUT:
// Pointer to a new structure.
// NULL if it fails.

struct process_d *processObject (void){

    struct process_d  *Tmp;

    Tmp = (void *) kmalloc( sizeof(struct process_d) );
    if ( (void *) Tmp == NULL ){
        return NULL;
    }
    // #todo
    // Maybe we can clean up the structure
    // or initialize some basic elements.
    return (struct process_d *) Tmp;
}


/*
 * getNewPID:
 *     Pegar um slot vazio na lista de processos.
 *     +Isso pode ser usado para clonar um processo.
 */

// Começaremos a busca onde começa o range de IDs 
// de processos de usuário.
// Se encontramos um slot vazio, retornaremos o índice.
 
pid_t getNewPID (void){

    int i = USER_BASE_PID;
    struct process_d  *p;

    while ( i < PROCESS_COUNT_MAX ){

        p = (struct process_d *) processList[i];

        if ( (void *) p == NULL ){ return (pid_t) i; }
        
        i++;
    };

    debug_print ("getNewPID: fail\n");

    return (pid_t) (-1);
}


/*
 * processTesting:
 *     Testando se o processo � v�lido. Se for v�lido retorna 1234.
 *     @todo: repensar os valores de retorno. 
 * system call (servi�o 88.)
 */

int processTesting (int pid){

    struct process_d  *P;

    P = (void *) processList[pid];

    if ( (void *) P == NULL ){
        return 0;
    }else{
        if ( P->used == 1 && P->magic == 1234 ){ return (int) 1234; }
    };

    return 0;
}



/*
 * processSendSignal:
 *     Envia um sinal para um processo.
 *     Se o sinal e o processo forem v�lidos, um sinal � colocado
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
    }

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
 ***********************************************************
 * init_processes:
 *    Inicaliza o process manager.
 *   #todo: rever esse nome, pois na verdade estamos inicializando variaveis 
 * usadas no gerenciamento de processo.
 */

// Called by init_microkernel in mk.c

void init_processes (void){

    register int i=0;

    debug_print("init_processes:\n");

    // Globals

	kernel_request = 0;    // O que fazer com a tarefa atual.
	
	
	// ?? Contagem de tempo de execu��o da tarefa atual.
	//n�o precisa, isso � atualizado pelo request()
	//kernel_tick = 0;                                 

    kernel_switch = 0;     // ?? Ativa o kernel switch do scheduler.

    current_process = 0;

    // Clear process list.
    i=0;
    while (i < PROCESS_COUNT_MAX){
        processList[i] = (unsigned long) 0;
        i++;
    };

    // More ?
}


/*
 * CloseAllProcesses:
 *     Bloqueia todos os processos da lista de processos.
 *     Menos o processo '0'.
 *     processCloseAllProcesses();    
 */

void CloseAllProcesses (void)
{
    int i=0;
    struct process_d  *P;

	// #importante:
	// Menos o 0, pois � o kernel. 

    //Pega, bloqueia e tira da lista.
    for ( i=1; i < PROCESS_COUNT_MAX; i++ )
    {
        P = (void *) processList[i];
        P->state = PROCESS_BLOCKED;
        
        // Not kernel.
        if (i != 100){
            processList[i] = (unsigned long) 0;
        }
    };

    //Check process 0.
    P = (void *) processList[0];

    if ( (void *) P == NULL ){
        panic ("CloseAllProcesses: P\n");
    }

    // #bugbug
    // The kernel is process 100.

    P = (void *) processList[100];

    if ( (void *) P == NULL ){
        panic ("CloseAllProcesses: kernel\n");
    }
}


// Worker for create_process.
// Do not check parameters validation.
void
__ps_initialize_process_common_elements(
    struct process_d *p )
{
    register int i=0;


    p->objectType  = ObjectTypeProcess;
    p->objectClass = ObjectClassKernelObjects;

    // Signal
    p->signal = 0;
    p->umask = 0;

    p->uid  = (int) GetCurrentUserId(); 
    p->gid  = (int) GetCurrentGroupId(); 

    p->syscalls_counter = 0;


//
// Threads
//

    // The control thread.
    p->control = NULL;
    
    // List of threads.
    p->threadListHead = NULL;


    // Absolute pathname and relative pathname. 

    p->file_root = (file *) 0;
    p->file_cwd  = (file *) 0;
    p->inode_root = (struct inode_d *) 0;
    p->inode_cwd  = (struct inode_d *) 0;

    // wait4pid: 
    // O processo esta esperando um processo filho fechar.
    // Esse � o PID do processo que ele est� esperando fechar.

    p->wait4pid = (pid_t) 0;
        
    // Número de processos filhos.
    p->nchildren = 0;

    p->zombieChildListHead = NULL;
    p->exit_code = 0;



// ==========

    // Standard stream.
    // See: kstdio.c for the streams initialization.
    // #todo: We need a flag.
    
    // #todo
    // Melhorar esse nome.
    
    if (kstdio_standard_streams_initialized != TRUE )
    {
        panic ("__ps_initialize_process_common_elements: [ERROR] Standard stream is not initialized\n");
    }
    
    for ( i=0; i<32; ++i ){ p->Objects[i] = 0; }

    if ( (void *) stdin == NULL ){
        panic ("__ps_initialize_process_common_elements: [TEST] stdin");
    }

    if ( (void *) stdout == NULL ){
        panic ("__ps_initialize_process_common_elements: [TEST] stdout");
    }

    if ( (void *) stderr == NULL ){
        panic ("__ps_initialize_process_common_elements: [TEST] stderr");
    }

    p->Objects[0] = (unsigned long) stdin;
    p->Objects[1] = (unsigned long) stdout;
    p->Objects[2] = (unsigned long) stderr;

// ==============

//
// == Socket ===================================
//

    // loop
    // pending connections;
    // Lista de conexoes pendentes do processo servidor.

    for ( 
        i=0; 
        i < SOCKET_MAX_PENDING_CONNECTIONS; 
        ++i )
    {
        p->socket_pending_list[i] = 0; 
    };

    p->socket_pending_list_head = 0;
    p->socket_pending_list_tail = 0;
    p->socket_pending_list_max  = 0;  // atualizado pelo listen();

//
// tty support
//

    //printf ("create_process: calling tty_create[DEBUG]\n");

    p->tty = ( struct tty_d *) tty_create(); 

    if ( (void *) p->tty == NULL ){
        panic ("create_process: Couldn't create tty\n");
    }
    tty_start(p->tty);



    // ...

    return;
}



// Create process
struct process_d *create_process ( 
    struct room_d    *room,
    struct desktop_d *desktop,
    struct window_d  *window,
    unsigned long base_address, 
    unsigned long priority, 
    int ppid, 
    char *name, 
    unsigned long iopl,
    unsigned long pml4_va,
    unsigned long pdpt0_va,
    unsigned long pd0_va )
{

    struct process_d  *Process;
    pid_t PID = -1;

    // Para a entrada vazia no array de processos.
    struct process_d *EmptyEntry; 


    unsigned long BasePriority=0;
    unsigned long Priority=0;



    debug_print ("create_process: #todo\n");
    printf      ("create_process: #todo\n");


    //=================================
    // check parameters

    if( (void*) room == NULL ){
        debug_print ("create_process: [FIXME] room parameter is NULL\n");
    }
    
    if( (void*) desktop == NULL ){
        debug_print ("create_process: [FIXME] desktop parameter is NULL\n");
    }
    
    if( (void*) window == NULL ){
        debug_print ("create_process: [FIXME] window parameter is NULL\n");
    }

    // #todo
    // Maybe the virtual 0 is n option in the future. Maybe.
    if( base_address == 0 ){
        panic ("create_process: [ERROR] base_address\n");
    }

    if( ppid < 0 ){
        panic ("create_process: [ERROR] ppid\n");
    }
  
    if( (void*) name == NULL ){
        panic ("create_process: [ERROR] name\n");
    }
  
    if( *name == 0 ){
        panic ("create_process: [ERROR] *name\n");
    }

//===============================

    if( pml4_va == 0 ){
        panic ("create_process: [ERROR] pml4_va\n");
    }

    if( pdpt0_va == 0 ){
        panic ("create_process: [ERROR] pdpt0_va\n");
    }

    if( pd0_va == 0 ){
        panic ("create_process: [ERROR] pd0_va\n");
    }

    // ...
    //=================================

	// @todo:
	// Melhorar esse esquema de numera��o e 
	// contagem de processos criados.
	// processNewPID � global ?

    if ( processNewPID < USER_BASE_PID || 
         processNewPID >= PROCESS_COUNT_MAX )
    {
        processNewPID = (int) USER_BASE_PID;
    }

    // Base priority.
    // Please, don't inherit base priority!

    BasePriority = (unsigned long) PRIORITY_NORMAL; 
    Priority     = (unsigned long) priority;

//
// Process
//
    Process = (void *) kmalloc ( sizeof(struct process_d) );

    // #todo: 
    // Aqui pode retornar NULL.
    if ( (void *) Process == NULL ){
        panic ("create_process: Process\n");
    }

//get_next:

	// Get empty.
	// Obt�m um �ndice para um slot vazio na lista de processos.
	// Se o slot estiver ocupado tentaremos o pr�ximo.
	// Na verdade podemos usar aquela fun��o que procura por um vazio. 

    while (1){

        PID = (int) getNewPID();

        if ( PID <= 0 || PID >= PROCESS_COUNT_MAX )
        {
            debug_print ("create_process: [FAIL] getNewPID \n");
            printf      ("create_process: [FAIL] getNewPID %d \n", PID);
            goto fail;
        }

        EmptyEntry = (void *) processList[PID];
 
        if ( (void *) EmptyEntry == NULL ){ break; }
    };
 
// ====================

// Worker
// Initializing the elements common for 
// all types of processes.

    __ps_initialize_process_common_elements( (struct process_d *) Process );

    //Process->objectType  = ObjectTypeProcess;
    //Process->objectClass = ObjectClassKernelObjects;

    // foi para o fim.
    //Process->used  = TRUE;
    //Process->magic = PROCESS_MAGIC;

    // Undefined
    Process->position = 0;

    Process->iopl = iopl; 

    // Not a protected process!
    Process->_protected = 0;

    processNewPID = (int) PID;
        
    // Identificadores.
    // PID. PPID. UID. GID.
    Process->pid  = (int) PID; 
    Process->ppid = (int) ppid; 


    // sessão crítica.
    Process->_critical = 0;

    //foi para o fim.
    //State of process
    //Process->state = INITIALIZED;  

    //@TODO: ISSO DEVERIA VIR POR ARGUMENTO
     Process->plane = FOREGROUND;

    //Error.
    //Process->error = 0;


//
// Name
//

    //Name.
    Process->name = (char *) name; //@todo: usar esse.
    //Process->cmd = NULL;  //nome curto que serve de comando.
    //Process->pathname = NULL;
 
    //#test
    //64 bytes max.
    strcpy ( Process->__processname, (const char *) name); 

    Process->processName_len = sizeof(Process->__processname);


    //Process->terminal =

//
// Banco de dados
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
		// frame pool, o que � equivalente a 4MB. (uma parti��o)
		// Obs: Um framepool indica onde � a �rea de mem�ria fisica
		// que ser� usada para mapeamento das p�ginas usadas pelo processo.

    Process->framepoolListHead = NULL;

		//Thread inicial.
		//Process->thread =
		
		//Process->processImageMemory =
		//Process->processHeapMemory =
		//Process->processStackMemory =

        // ORDEM: 
        // O que segue � referenciado durante o processo de task switch.

		// Page Directory: 
		//     Alocar um endere�o f�sico para o diret�rio de p�ginas do 
		// processo a ser criado, depois chamar a fun��o que cria o diret�rio.
		//
		// @todo:
		// *IMPORTANTE: Por enquanto os processos s�o criadas usando o 
		// diret�rio de p�ginas do processo Kernel. Mas temos que criar 
		// um diret�rio novo pra cada processo criado.
		// O diret�rio de todos os processos de usu�rio ser�o iguais. 
		// Ter�o uma �rea de us�rio particular e uma �rea compartilhada 
		// em kernel mode.
		//
		//@todo: Alocar um endere�o f�sico antes, depois chamar a fun��o que 
		// cria o pagedirectory.
		//@todo: 
        //op��o: KERNEL_PAGEDIRECTORY; //@todo: Usar um pra cada processo.

		// #obs:
		// Vari�vel recebida via argumento.


//
// pml4_va
//

    if (pml4_va == 0)
    {
        debug_print("create_process: [FAIL] pml4_va\n");
        printf     ("create_process: [FAIL] pml4_va\n");
        goto fail;
        //return NULL;
    }


// pml4
    Process->pml4_VA = (unsigned long) pml4_va;
    Process->pml4_PA = (unsigned long) virtual_to_physical ( 
                                               pml4_va, 
                                               gKernelPML4Address );


// pdpt0
    Process->pdpt0_VA = (unsigned long) pdpt0_va;
    Process->pdpt0_PA = (unsigned long) virtual_to_physical ( 
                                               pdpt0_va, 
                                               gKernelPML4Address );

//pd0
    Process->pd0_VA = (unsigned long) pd0_va;
    Process->pd0_PA = (unsigned long) virtual_to_physical ( 
                                               pd0_va, 
                                               gKernelPML4Address );



		// cancelados. 
		// Process->mmBlocks[32]
		// Process->mmblockList[32]

		// Process->processMemoryInfo

		// #todo: 
		// Precisa alocar espa�o na mem�ria f�sica.
		// Precisa criar page tables para essas areas de cada processo.
		// Os endere�os virtuais dessas areas dos processos s�o sempre os mesmos.
		// mas os endere�os f�sicos dessas areas variam de processo pra processo.

		// Imagem do processo.
		// ?? Provavelmente esse endere�o � virtual.
		// Queremos que esse endere�o seja padronizado e que todos 
		// os processos usem o mesmo endere�o.
		
		// #bugbug
		// Todos os processos de usu�rio come�am no mesmo endere�o virtual.
		// Por�m temos os processos em kernel mode e os processos do gramado core
		// que usam endere�os virtuais diferentes.
		// #todo: Rever isso.
		// #todo: estamos suspendendo essa informa��o.
		
		//
		// # IMPORTANTE 
		//
		
		// Base da imagem do processo.
		// Na verdade precisamos aceitar o endere�o passado via 
		// argumento, pois nem todos processos come�am no endere�o 
		// default.

//
// Image
//

    // Endere�o virtual e endere�o f�sico.
    Process->Image   = (unsigned long) base_address;  
    Process->ImagePA = (unsigned long) virtual_to_physical ( 
                                           Process->Image, 
                                           gKernelPML4Address ); 
                                               


//
// Child image
//

    // Endere�o virtual e endere�o f�sico de um processo filho.
    // Isso � usado durante a clonagem.
    Process->childImage = 0;
    Process->childImage_PA = 0;


    // #todo
    // Precisamos saber o tamanho da imagem do processo para
    // calcularmos quantas p�ginas ele vai usar.
    // Precisamos dividir a imagem em code, data, heap e stack
    // Pois a �rea de dados poder� sofrer swap.

    // Tamanho da imagem do processo.
    // Temos que chamar a fun��o que pega o tamanho de um arquivo,
    // #bugbug: Porem, no momento o kernel n�o consegue ler arquivos
    // que est�o em subdiret�rios corretamente e os programas est�o 
    // em subdiret�rios.
    // #obs: O tamanho tamb�m poderia ser passado por arguemento.
    // #ou um argumento com ponteiro pra estrutura de informa��o 
    // sobre uma imagem.

    Process->ImageSize = 0;

    // #todo: 
    // Estrutura com informa��es sobre a imagem do processo.
    
    Process->image_info = NULL;


//
// == Heap and Stack ===========
//

    // #obs: 
    // O 'endereço virtual' do heap e da stack dos processos serão 
    // os mesmos para todos os processos, assim como o 'endereço virtual' 
    // de carregamento da imagem.

    // #todo:
    // #bugbug: 
    // O Heap e a Stack devem estar dentro da 
    // área de memória do processo.
    // #wrong: Uma pagetable do diretório é para o heap e outra para a stack.
    // #wrong: Cada pagetable no diretório do processo é pra uma coisa.

    // ## HEAP ##

    // directory va, index, region pa
    //CreatePageTable ( Process->DirectoryVA, 512, 0 );

    //Process->Heap = (unsigned long) 0x00400000; //funciona
    //Process->Heap = (unsigned long) 0xC0C00000; //funciona

    // g_heappool_va
    // endere�o virtual do pool de heaps.
    // os heaps nessa �rea ser�o dados para os processos.
    // base + (n*size)

    if ( g_heap_count < 0 || 
         g_heap_count >= g_heap_count_max )
    {
        debug_print ("create_process: [FIXME] g_heap_count limits\n");
        //panic ("create_process: [FAIL] g_heap_count limits\n");
    }

    // #atenção
    // Estamos usando o heappool pra pegarmos esses endereços.
    // me parece que isso é memória compartilhada em ring3
    // e que o malloc da libc está usando isso sem problemas.

    // #todo: 
    // #test: A stack de um process recem criado
    // poderia ficar no fim de seu heap ???

    if (g_heappool_va == 0){
        debug_print ("clone_and_execute_process: g_heappool_va\n");
        panic ("clone_and_execute_process: g_heappool_va\n");
    }

    // Ignoraremos esse pois vai falhar na criacao do primeiro heap.
    //if (g_heap_count == 0)
        //panic("clone_and_execute_process: g_heap_count");

    if (g_heap_size == 0){
        debug_print ("clone_and_execute_process: g_heap_size\n");
        panic ("clone_and_execute_process: g_heap_size\n");
    }

    // #bugbug
    // There is a limit here. End we will have a huge problem 
    // when reach it.

    Process->Heap     = (unsigned long) g_heappool_va + (g_heap_count * g_heap_size);
    Process->HeapSize = (unsigned long) g_heap_size;
    Process->HeapEnd  = (unsigned long) (Process->Heap + Process->HeapSize); 
    g_heap_count++;


    // Endere�o do in�cio da Stack do processo.
    // Endere�o do fim da stack do processo.
    // Tamanho da pilha, dada em KB.
    // #importante: 
    // Deslocamento do endere�o do in�cio da pilha em rela��o 
    // ao in�cio do processo. 

    // #bugbug
    // Isso indica que a stack será no endereço virtual tradicional,
    // porém qual é o endereço físico da stack do processo criado
    // com essa rotina.
    // #bugbug: Com esse erro todos os processo criados
    // estão usando a mesma stack, pois todas apontam para o mesmo
    // endereço físico.


//
// #bugbug #bugbug #bugbug #bugbug
//

    // Wrong !!!!!!!!!!!!!!!!!!!!

    Process->Stack       = (unsigned long) UPROCESS_DEFAULT_STACK_BASE; 
    Process->StackSize   = (unsigned long) UPROCESS_DEFAULT_STACK_SIZE; //?? usamos isso na hora de criar a stack?? 
    Process->StackEnd    = (unsigned long) (Process->Stack - Process->StackSize);  
    Process->StackOffset = (unsigned long) UPROCESS_DEFAULT_STACK_OFFSET;  //??


//
// PPL - (Process Permition Level).(gdef.h)
//

    // Determina as camadas de software que um processo ter� acesso irrestrito.
    // Process->ppl = pplK0;

    //Process->callerq          //head of list of procs wishing to send.
    //Process->sendlink;        //link to next proc wishing to send.
    //Process->message_bufffer  //pointer to message buffer.
    //Process->getfrom_pid      //from whom does process want to receive.
    //Process->sendto_pid       //pra quem.

    //Signal
    //Process->signal = 0;
    //Process->signalMask = 0;

    //cancelada.
    //Process->process_message_queue[8]

//
// Priority
//
    Process->base_priority = (unsigned long) BasePriority;
    Process->priority      = (unsigned long) Priority;

    //Que tipo de scheduler o processo utiliza. (rr, realtime ...).
    //Process->scheduler_type = ; 
    

    // #todo
    // Counters

    //Process->step
    //Process->quantum
    //Process->timeout
    //Process->ticks_remaining

    //As threads do processo iniciam com esse quantum.
    //Process->ThreadQuantum   

    //Process->event

    // #importante
    // user session, room and desktop.

    // #bugbug: 
    // N�o temos informa��o sobre a user session, 
    // devemos pegar a estrutura de current user session. 
    // Para isso ela deve ser configurada na inicializa��o do gws,
    // antes da cria��o dos processo.

//
// Security
//

    Process->usession = CurrentUserSession;  // Current.
    Process->room     = room;                // Passado via argumento.
    Process->desktop  = desktop;             // Passado via argumento.


//
// Navigation
//
    Process->prev = NULL; 
    Process->next = NULL; 

    // Register
    // List
    // Coloca o processo criado na lista de processos.

    processList[PID] = (unsigned long) Process;

    // #todo
    // last_created = PID;
    
    Process->state = INITIALIZED;

    // Validation.
    Process->used  = TRUE;
    Process->magic = PROCESS_MAGIC;

    // #debug
    debug_print ("create_process: done\n");
    printf      ("create_process: done\n");

    // ok
    return (void *) Process;

// Fail

fail:
    //Process = NULL;
    refresh_screen();
    return NULL;
}


unsigned long GetProcessPML4_PA ( struct process_d *process )
{
    if( (void *) process != NULL )
    {
        //@todo: checar used e magic.
        return (unsigned long) process->pml4_PA;
    }

    // fail
    return (unsigned long) 0;
}

unsigned long GetProcessPML4_VA ( struct process_d *process )
{
    if( (void *) process != NULL )
    {
        //@todo: checar used e magic.
        return (unsigned long) process->pml4_VA;
    }

    // fail
    return (unsigned long) 0;
}


// VA, I guess.
unsigned long GetProcessHeapStart ( pid_t pid )
{
    struct process_d  *process;


    debug_print ("GetProcessHeapStart:\n");

    // #debug
    printf ("GetProcessHeapStart: [DEBUG] pid %d\n", pid);
    refresh_screen();

    // Limits

    if ( pid < 0 || pid >= PROCESS_COUNT_MAX )
    {
        debug_print ("pid\n");
        goto fail; 
    }

    process = (struct process_d *) processList[pid];
    
    if ( (void *) process == NULL )
    {
        debug_print ("process\n");
        goto fail;
    }else{

        if ( process->used != 1 || process->magic != 1234 )
        {
            debug_print ("process validation\n");
            goto fail;
        }

        // Ok.
        return (unsigned long) process->Heap;
    };

fail:
    debug_print ("GetProcessHeapStart: fail\n");
    panic       ("GetProcessHeapStart: fail\n");
    return (unsigned long) 0;
}


void 
SetProcessPML4_VA ( 
    struct process_d *process, 
    unsigned long va )
{
    if ( (void *) process != NULL ){
        process->pml4_VA = (unsigned long) va;  
    }
}

void 
SetProcessPML4_PA ( 
    struct process_d *process, 
    unsigned long pa )
{
    if ( (void *) process != NULL ){
        process->pml4_PA = (unsigned long) pa;  
    }
}

int get_caller_process_id (void)
{
    return (int) caller_process_id;
}

void set_caller_process_id (int pid)
{
    caller_process_id = (int) pid;
}

/*
 *************************************************
 * init_process_manager:
 *     Initialize process manager.
 *     processInitializeProcessManager();
 */

int init_process_manager (void)
{
    caller_process_id = (int) 0;
    processNewPID = (int) USER_BASE_PID;

	//...

    return 0;
}



/*
 ****************************
 * processCopyMemory:
 * 
 *     Copia a imagem de um processo.
 *     Isso é usado na implementação de fork() e
 * na implementação da rotina de clonagem.
 *     Isso é usado por clone_and_execute_process()
 */

// O que copiar?
// >> code, data, bss, heap and stack.
// For now, all the processes has 4MB,
// and the stack begins at CONTROLTHREAD_STACK.
// We just use the control thread.

// #bugbug
// Imagem com limite de 200KB. (fail)
// heap ?? Depois              (fail)
// Stack de 32KB.              (ok)
// 




// Explicando:
// Copia a imagem do processo atual e salva o endereço
// da copia num elemento da estrutura passada como argumento.

// OUT:
// 

// #bugbug: na verdade não estamos mais copiando e sim criando um endereçamento novo.
int __alloc_memory_for_image_and_stack( struct process_d *process )
{
    unsigned long __new_base=0;    // base
    unsigned long __new_stack=0;   // stack

    if ( (void *) process == NULL )
    {
        printf ("processCopyMemory: [FAIL] process \n");
        refresh_screen();
        return (int) (-1);
    }

//
// Image base
//

    // #bugbug
    // Precisamos de memória física para a imagem e para a pilha.
    // 4mb de memória física nos permite criarmos um processo
    // com sua pilha no topo dos 4mb.
    // Por isso que precisamos de um alocador de frames,
    // que considere a memória ram inteira.
    // E precisamos de uma rotina que mapeie esses frames individualmente,
    // mesmos que eles sejam pegos esparçamente.

    // #bugbug
    // Esse alocador abaixo está limitado à uma região de 4MB,
    // previamente mapeado.

    // #obs:
    // A não ser que a pilha possa ficar em endereço
    // virtual aleatório.
    // Me parece que endereço virtual aleatório é
    // usado por questão de segurança.
    // Podemos tentar usar pilha com endereço virtual aleatório.

    // 200 KB.   200kb/4096 =  quantidade de páginas.
    // Allocating memory for the process's image.
    // #todo: We need this size.
    // 1024*200 = 200k
    // 50 páginas.
    
    // Retorna um endereço virtual.
    // Mas usaremos apenas o endereço físico extraído desse endereço.

    int number_of_pages = 0;

    // Quantas páginas temos em 200KB?
    number_of_pages = (int) (200*1024)/4096;

    __new_base = (unsigned long) allocPages(number_of_pages); 
    if ( __new_base == 0 )
    {
        printf ("processCopyMemory: __new_base fail\n");
        refresh_screen();
        return (int) (-1);
    }

//
// Image stack
//

    // 32 KB.
    // Allocating memory for the process's stack.
    // #todo: We need this size.

    // Retorna um endereço virtual.
    // Mas usaremos apenas o endereço físico extraído desse endereço.

    // Quantas páginas temos em 32KB?
    number_of_pages = (int) (32*1024)/4096;

    __new_stack = (unsigned long) allocPages(number_of_pages); 

    if ( __new_stack == 0 )
    {
        printf ("processCopyMemory: __new_stack fail\n");
        refresh_screen();
        return (int) (-1);
    }


//
// == Copying memory ======================================
//

    // Copying base and stack.
    // Copiando do processo atual para o buffer que alocamos
    // logo acima.

    // Copia a imagem do processo.
    // Copia do início da imagem. 200KB.
    memcpy ( 
        (void *) __new_base,  
        (const void *) CONTROLTHREAD_ENTRYPOINT, 
        (200*1024) );

    // Copia a pilha do process.
    // Copia do fim da stack. 32KB.
    memcpy ( 
        (void *) __new_stack, 
        (const void *) ( CONTROLTHREAD_STACK-(32*1024) ), 
        (32*1024) );

//
// Getting the physical addresses.
//

// Obtendo o edereço físico da base da imagem e da pilha.

    unsigned long new_base_PA  = (unsigned long) virtual_to_physical ( __new_base, gKernelPML4Address ); 
    unsigned long new_stack_PA = (unsigned long) virtual_to_physical ( __new_stack, gKernelPML4Address ); 

    if ( new_base_PA == 0 ){
        printf("processCopyMemory: new_base_PA\n");
        refresh_screen();
        return -1;
    }
    
    if ( new_stack_PA == 0 ){
        printf("processCopyMemory: new_stack_PA\n");
        refresh_screen();
        return -1;
    }

    // #debug
    //refresh_screen();
    //while(1){}
    
    // #todo
    // Agora temos que fazer esses endereços físicos serem
    // mapeados em 0x400000 do diretório de páginas do processo filho.
    // Lembrando que o diretório de páginas do processo filho
    // será uma cópia do diretório do processo pai.
    // Como a cópia do diretórios anda não foi feita,
    // vamos salvar esses endereços para mapearmos depois.

    // virtual
    // Esse endereço virtual não nos server mais.
    // precisamos substituir pelo endereço virtual padrão 
    // para aplicativos. Faremos isso em clone.c quando retornarmos.

    // Salvando os endereços virtuais onde carregamos a imagem e a pilha.
    process->childImage  = (unsigned long) __new_base;
    process->childStack  = (unsigned long) __new_stack;

    // Salvando endereços físicos obtidos anteriormente.  
    // Esses endereços representam a base da imagem e o inicio da pilha.
    process->childImage_PA = (unsigned long) new_base_PA;
    process->childStackPA  = (unsigned long) new_stack_PA;

    // #debug
    // Showing the addresses of base and stack pointers.

    printf("processCopyMemory: new base PA %x | new stack PA %x \n",
        new_base_PA, new_stack_PA );

// Done.
    //#debug
    //printf ("processCopyMemory: ok\n");
    //refresh_screen ();
    return 0;
}



// Service 227
// Entering critical section.
// Close gate. Turn it FALSE.
void process_close_gate(int pid)
{
    struct process_d  *p;

    if (pid<0){
        panic ("process_close_gate: pid \n");
    }

// Process

    p = (void *) processList[pid];

    if ( (void *) p == NULL ){
        panic ("process_close_gate: p \n");
    } else {

        // todo: validation
        
        __spinlock_ipc = __GATE_CLOSED;  //0;
        criticalsection_pid = (pid_t) 0;
        p->_critical = FALSE;  //0;
    };
}


// Service 228
// Exiting critical section
// Open gate. Turn it TRUE.
void process_open_gate (int pid)
{
    struct process_d  *p;

    if (pid<0)
        panic ("process_open_gate: pid \n");

    // Process.

    p = (void *) processList[pid];

    if ( (void *) p == NULL ){
        panic ("process_open_gate: p \n");
    } else {

        // todo: validation
        
        __spinlock_ipc = __GATE_OPEN; //1;
        criticalsection_pid = (pid_t) pid;
        p->_critical = TRUE; //1;
    };
}

//=============

// Pega uma stream na lista de arquivos dado o fd.

file *process_get_file_from_pid ( pid_t pid, int fd )
{
    struct process_d *p;
    file *fp;

    if ( pid < 0){
        return NULL;
    }

    // Get process pointer.
    p = (struct process_d *) processList[ pid ];

    if (fd<0){
        return NULL;
    }

    // Get fp from list of open files.
    // #bugbug: Overflow.
    
    return ( file * ) p->Objects[fd];  
}

// Return the file pointer from a given fd.
// the fd represents a index in the object list of the
// current process.

file *process_get_file ( int fd )
{
    if( fd<0){
        return NULL;
    }

    return (file *) process_get_file_from_pid (current_process, fd );
}

// Get tty id.
// Pega o número da tty de um processo, dado o pid.
// Serviço: 266.

int process_get_tty (int pid)
{
    // Usada para debug.
  
    struct process_d *p;
    struct tty_d *tty;

    //#debug
    //printf ("process_get_tty: pid %d \n", pid);
    //refresh_screen();


    // #todo
    // Overflow ?
    
    if ( pid < 0 )
    {
        debug_print ("process_get_tty: pid \n");
        //printf ("pid fail\n");
        //refresh_screen();
        return -1;
    }


    p = (struct process_d *) processList[pid];

    if ( (void *) p == NULL )
    {
        debug_print ("process_get_tty: p \n");
        //printf ("p fail\n");
        //refresh_screen();
        return -1;
    }

    // Get the private tty.
    
    tty = p->tty;    

    if ( (void *) tty == NULL )
    {
        debug_print ("process_get_tty: tty fail\n");
        //printf ("tty fail\n");
        //refresh_screen();
        return -1;
    }


    //printf ("tty %d belongs to %d\n", tty->index, p->pid );
    //refresh_screen ();

    // #bugbug
    // Isso precisa ser o fd na lista de arquivos abertos 
    // pelo processo.
    //file *f;
    
    //f = ()

    return (int) tty->index;
}


struct process_d *__create_and_initialize_process_object(void)
{
    struct process_d *New;
    int PID=-1;

    New = (struct process_d *) processObject();
    if ( (void *) New == NULL )
    {
        debug_print ("__create_and_initialize_process_object: [FAIL] New\n");
        printf      ("__create_and_initialize_process_object: [FAIL] New\n");
        goto fail;
    }

// Get PID.
// Obtêm um índice para um slot vazio na lista de processos.
// Precisa estar dentro do range válido para processos
// em ring3.

    // Invalidate.
    New->pid = -1;

    // Get new pid.
    PID = (int) getNewPID();
    if ( PID <= 0 || PID < USER_BASE_PID )
    {
        debug_print ("clone_and_execute_process: [FAIL] getNewPID\n");
        printf      ("clone_and_execute_process: [FAIL] getNewPID %d \n", 
            PID );
        goto fail;
    }

    // Initializing the process structure.
    // Saving the process pointer in the list.

    New->pid = (pid_t) PID;
    New->uid = (uid_t) current_user;
    New->gid = (gid_t) current_group;
    

    // syscall counter
    New->syscalls_counter = 0;


        // #bugbug
        // #todo
        // Ok mesma coisa precisa ser feito para o endereço
        // virtual da pilha.

        // #Cuidado
        // Heap for Clone.
        // Essa é a rotina usada na criação de processo 
        // pra gerar um heap para ele.
        // Vamos tentar usar isso na rotina de clonagem.


    if (g_heappool_va == 0){
        panic("clone_and_execute_process: g_heappool_va\n");
    }

    if (g_heap_count == 0){
        panic("clone_and_execute_process: g_heap_count\n");
    }

    if (g_heap_size == 0){
        panic("clone_and_execute_process: g_heap_size\n");
    }

    // #bugbug
    // There is a limit here. End we will have a huge problem 
    // when reach it.

//
// Heap
//

    New->Heap     = (unsigned long) g_heappool_va + (g_heap_count * g_heap_size);
    New->HeapSize = (unsigned long) g_heap_size;
    New->HeapEnd  = (unsigned long) (New->Heap + New->HeapSize); 
    g_heap_count++;

//
// Stack
//

    // Stack for the clone. 
    New->control->rsp = CONTROLTHREAD_STACK;
    New->Stack        = CONTROLTHREAD_STACK;
    New->StackSize = (32*1024);    //isso foi usado na rotina de alocação.
    New->StackEnd = ( New->Stack - New->StackSize );






//
// Socket ============
//

    int sIndex=0;

    for (sIndex=0; sIndex<32; ++sIndex){
        New->socket_pending_list[sIndex] = 0; 
    };

    New->socket_pending_list_head = 0;
    New->socket_pending_list_tail = 0;
    New->socket_pending_list_max  = 0; //atualizado pelo listen();

    New->Image        = (unsigned long) CONTROLTHREAD_BASE;        // 0x200000 
    
    New->used  = TRUE;
    New->magic = 1234;
    processList[PID] = (unsigned long) New;

    // ok
    return (struct process_d *) New;
    
fail:
    return NULL;
}




































































































