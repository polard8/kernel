
// process.c

#include <kernel.h>


// GLOBAL
// ------
// Process used by the console during the job control.
// #hackhack: 
// For now we are using the control thread associated with the
// window with focus.
// #todo
// But we need to use the control thread of the foreground process
// associated with the console TTY.
pid_t foreground_process;
// This is the process with the active thread.
pid_t active_process;    
// [Processing time]
// Only these can read the keyboard input.
// Sometime it's the terminal.
// It's child will read into a file.
// See: ps/process.c
pid_t criticalsection_pid;
// ------


//
// current pid
//

// PRIVATE
static pid_t __current_pid = (pid_t) (-1);  //fail
static pid_t caller_process_id=0;





//
// IPC
//

// Global:
// #todo: It needs to be atomic.
// see: gspin.h
int __spinlock_ipc=0;
//...


void set_current_process( pid_t pid )
{
    __current_pid = (pid_t) pid;
}

pid_t get_current_process(void)
{
    return (pid_t) __current_pid;
}


// Quando criamos um novo processo.
//int NewProcessInitialized = FALSE;


int GetCurrentPID (void)
{
    //return (int) current_process;
    return (pid_t) get_current_process();
}



struct process_d *GetCurrentProcess(void)
{
    struct process_d *p;
    
    pid_t current_process = (pid_t) get_current_process();
    
    if ( current_process < GRAMADO_PID_BASE || 
         current_process >= PROCESS_COUNT_MAX )
    {
        return NULL;
    }

    p = (struct process_d *) processList[current_process];

    return (struct process_d *) p;
}


// helper
unsigned long GetProcessStats ( int pid, int index )
{
    struct process_d *p;


    if (pid<0){
        panic ("GetProcessStats: pid \n");
    }

    // Process

    p = (void *) processList[pid];

    if ( (void *) p == NULL ){
        printf ("GetProcessStats: struct \n");
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

        case 21:  return (unsigned long) p->HeapStart;  break;
        case 22:  return (unsigned long) p->HeapEnd;    break;
        case 23:  return (unsigned long) p->HeapSize;   break;

        case 24:  return (unsigned long) p->HeapPointer;  break;
        case 25:  return (unsigned long) p->HeapLastValid;  break;
        case 26:  return (unsigned long) p->HeapLastSize;  break;

        case 27:  return (unsigned long) p->StackStart;  break;
        case 28:  return (unsigned long) p->StackEnd;    break;
        case 29:  return (unsigned long) p->StackSize;   break;

        case 30:  return (unsigned long) p->StackOffset;  break;
        
        case 31:
            return (unsigned long) (p->rflags_iopl & 0xF);
            break;

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
 * copy_process_struct
 *     + Copia os elementos da estrutura de processo.
 *     + Cria um diret�rio de p�ginas e salva os endere�os 
 *       virtual e f�sico dele na estrutura de processo.
 *     Isso � chamado por do_fork_process.
 */
// Called by clone_and_execute_process at clone.c
// #
// It will also copy the control thread.
// IN:
// p1 = atual.
// p2 = clone. 
// OUT:
// 0 = ok
// 1 = fail

int 
copy_process_struct(
    struct process_d *p1,
    struct process_d *p2 )
{
    struct process_d  *Process1;
    struct process_d  *Process2;

    int Status=0;
    int i=0;

// Balancing the priority.
// Please, don't inherit base priority!
// The priority for the clone.
    unsigned long CloneBasePriority=PRIORITY_NORMAL;
    unsigned long ClonePriority=PRIORITY_NORMAL;

    /*
    if ( p1 == p2 ){
        printf ("copy_process_struct: [FAIL] same PID\n");  goto fail;
    }

    if ( p1 < 0 ){
        printf ("copy_process_struct: [FAIL] p1 limits\n"); goto fail;
    }

    if ( p2 < 0 ){
        printf ("copy_process_struct: [FAIL] p2 limits\n"); goto fail;
    }
    */


    // ===========================
    // Check process 1.
    //Process1 = (struct process_d *) processList[p1];

    Process1 = (struct process_d *) p1;

    // Check Process1
    if ( (void *) Process1 == NULL ){
        printf ("copy_process_struct: Process1\n"); goto fail;
    }else{
        if ( Process1->used != 1 || Process1->magic != 1234 )
        {
           printf ("copy_process_struct: Process1 validation \n");
           goto fail;
        }
    };

    // ===========================
    // Check process 2.
    //Process2 = (struct process_d *) processList[p2];
 
    Process2 = (struct process_d *) p2;
     
    if ( (void *) Process2 == NULL ){
        printf ("copy_process_struct: Process1\n"); goto fail; 
    }else{
        if ( Process2->used != 1 || Process2->magic != 1234 )
        {
           printf ("copy_process_struct: Process2 validation \n");
           goto fail;
        }
    };


//
// Copy
//

// Object.
    Process2->objectType  = Process1->objectType;
    Process2->objectClass = Process1->objectClass;

    Process2->base_priority = (unsigned long) CloneBasePriority;
    Process2->priority      = (unsigned long) ClonePriority;


// O clone não inicializa na seção crítica, pois senão teríamos
// dois processos na sessão crítica.
    Process2->_critical = 0;

// Identificadores.

    Process2->pid  = (pid_t) p2->pid;         // PID.  O pid do clone.
    Process2->ppid = (pid_t) Process1->pid;   // PPID. O parent do clone é o pid do pai. 
    
    Process2->uid  = (uid_t) Process1->uid;   // UID. 
    Process2->euid = (uid_t) Process1->euid;  // EUID. 
    Process2->ruid = (uid_t) Process1->ruid;  // RUID. 
    Process2->suid = (uid_t) Process1->suid;  // SUID. 
    
    Process2->gid  = (gid_t) Process1->gid;   // GID. 
    Process2->egid = (gid_t) Process1->egid;  // EGID. 
    Process2->rgid = (gid_t) Process1->rgid;  // RGID. 
    Process2->sgid = (gid_t) Process1->sgid;  // SGID. 
    Process2->pgrp = Process1->pgrp;

// validation.
    Process2->used  = Process1->used;
    Process2->magic = Process1->magic;

// State of process
    Process2->state = Process1->state;  

// Plano de execução.
    Process2->plane = Process1->plane;

    //Process->name_address = NULL;

    Process2->framepoolListHead = Process1->framepoolListHead;

//
// pml4
//

// #bugbug
// Precisamos clonar o diret�rio de p�ginas
// sen�o alguma altera��o feita na pagetable da imagem pode
// corromper o processo que est� sendo clonado.
// #importante:
// Deve retornar o endere�o do diret�rio de p�ginas criado,
// que � um clone do diret�rio de p�ginas do kernel.
// Retornaremos o endere�o virtual, para que a fun��o create_process 
// possa usar tanto o endere�o virtual quanto o f�sico.
// #bugbug
// Na verdade precisamos clonar o diret�rio do processo e n�o o 
// diret�rio do kernel.
// #importante
// Isso clona o diret�rio de p�ginas do kernel. Isso facilita as coisas.
// Retorna o endere�o virtual do novo diret�rio de p�ginas.
// #importante:
// Vamos converter porque precisamos de endere�o f�sico para colocarmos no cr3.
// Mas o taskswitch faz isso pegando o endere�o que estiver na thread, ent�o
// esse endere�o precisa ir pra thread.


/*
// ========
// pml4
    Process2->pml4_VA = (unsigned long) CloneKernelPML4();

    if ( (void *) Process2->pml4_VA == NULL ){
        panic ("processCopyProcess: [FAIL] pml4_VA\n");
    }

    Process2->pml4_PA = (unsigned long) virtual_to_physical ( 
                                              Process2->pml4_VA, 
                                              gKernelPML4Address ); 
*/

/*
// ========
//pdpt0
    Process2->pdpt0_VA = Process1->pdpt0_VA;
    Process2->pdpt0_PA = Process1->pdpt0_PA;
*/

/*
// ========
// pd0
    Process2->pd0_VA = Process1->pd0_VA;
    Process2->pd0_PA = Process1->pd0_PA;
*/

// #bugbug
// Lembrando que na rotina de fork() nos obtemos
// os endereços físicos da imagem do clone e de sua pilha.
// precisamos mapear esses endereços em 0x400000, caso contrário
// o processo filho apontará para a imagem do processo pai,
// como estava antes de copiarmos o diretório de páginas do kernel.
// ??
// #bugbug
// Se o endere�o for virtual, ok fazer isso. 
// Usaremos o mesmo endere�o virtual da imagem.
// #importante: se bem que esse endere�o virtual de imagem
// pode ser diferente para o kernel. Pois no momento
// que ele alocar mem�ria para a imagem ele ter� o
// endere�o l�gico retornado pelo alocador.
// #bugbug
// Conseguimos o endere�o da imagem copiada,
// mas teremos que refazer isso mais a frente quando
// carregarmos, (isso no caso da rotina de clonagem)
// Isso � v�lido s� para o fork.
// Atenção
// O processo pai armazenava o  novo endereço da imagem do processo
// filho. Isso foi criado durante a alocação de memória
// para o processo filho.
// porém esse endereço virtual não aponta para o 
// entry point da imagem do processo filho, e sim para
// o endereço virtual obtido na alocação.

    Process2->Image   = (unsigned long) Process1->childImage; // #bugbug: Esse endereço não é 0x400000
    Process2->ImagePA = (unsigned long) Process1->childImage_PA;
    Process2->childImage    = 0;
    Process2->childImage_PA = 0;

// #bugbug
// We simply can't do this!
// Every process need your own heap!
// The function that called up is gonna fix this later. :)
// Simply initialize for now!

//#bugbug
// Não inicialize com 0, pois esses valores foram
// configurados por um worker chamado antes desse.

    /*
    //heap
    Process2->Heap     = (unsigned long) 0; //Process1->Heap;    
    Process2->HeapEnd  = (unsigned long) 0; // Process1->HeapEnd; 
    Process2->HeapSize = (unsigned long) 0; // Process1->HeapSize;
    //stack
    Process2->Stack       = (unsigned long) 0; // Process1->Stack;   
    Process2->StackEnd    = (unsigned long) 0; // Process1->StackEnd; 
    Process2->StackSize   = (unsigned long) 0; // Process1->StackSize;
    Process2->StackOffset = (unsigned long) 0; // Process1->StackOffset;
    */


// cpl
    Process2->cpl = Process1->cpl;

// iopl
    Process2->rflags_iopl = Process1->rflags_iopl;

// Security: 
// usersession, room and desktop.

    Process2->usession = Process1->usession;
    Process2->room     = Process1->room;
    Process2->desktop  = Process1->desktop;

// Absolute pathname and relative pathname. 

    Process2->file_root  = Process1->file_root;
    Process2->file_cwd   = Process1->file_cwd;

    Process2->inode_root = Process1->inode_root;
    Process2->inode_cwd  = Process1->inode_cwd;

// =============
// #IMPORTANTE
// Herdar todos arquivos.
// #bugbug: 
// Lembrando que o fd 1 tem sido usado como dispositivo 
// console virtual.

// #bugbug
// Imagine um processo que fechou um dos três arquivos e agora
// vamos clonar sem o fluxo padrão em ordem.

    file *__f;

    for (i=0; i<NUMBER_OF_FILES; i++)
    {
        // Copy
        Process2->Objects[i] = Process1->Objects[i];
        
        // Updating the referency counter.
        // ??limits
        __f = (void*) Process2->Objects[i];

        // Quantos descritores de arquivo apontam para essa mesma estrutura.
        if ( (void *)__f != NULL )
        {
            __f->fd_counter++;
        }
    };

// O fluxo padrão foi criando antes em klib/kstdio.c
// #todo: 
// Checar as características desses arquivos.

    Process2->Objects[0] = (unsigned long) stdin;
    Process2->Objects[1] = (unsigned long) stdout;
    Process2->Objects[2] = (unsigned long) stderr;

//
// ========================
// Thread de controle
//

// Vamos clonar a thread de controle do processo pai.
// obs:
// Me parece que a fun��o que clona apenas a thread de controle 
// chama-se fork1. #todo
// #todo: Precisamos copiar todas as threads
// vamos come�ar pela thread de controle.
// teoriacamente elas precisam ter o mesmo endere�o virtual ...
// mas est�o em endere�os f�sicos diferentes.
// #bugbug precisamos clonar a thread.
// ############### #IMPORTANTE #################
// #bugbug
// Ainda n�o temos um salvamento de contexto apropriado para essa system call.
// S� o timer tem esse tipo de salvamento.
// Precisamos salvar o contexto antes de chamarmos o servi�o fork()
// Pois se n�o iremos retomar a thread clone em um ponto antes de 
// chamarmos o fork, que � onde est� o �ltimo ponto de salvamento.

//#todo: review

//?? herda a lista de threads ??
    Process2->threadListHead = Process1->threadListHead;
    Process2->zombieChildListHead = Process1->zombieChildListHead;
    Process2->dialog_address = Process1->dialog_address;

//
// == TTY ======================
//

// Vamos criar uma tty para o processo clone.
// Ela será uma tty privada, mas precisa ter
// uma estrutura de arquivo que aponte para ela
// e um fd na lista de objetos abertos pelo processo.

    // panic()
    debug_print ("copy_process_struct: [FIXME] No slot for tty\n");
 
__OK:
    Process2->exit_code = Process1->exit_code;
    Process2->prev = Process1->prev; 
    Process2->next = Process1->next; 
    //Status = 0;
    return (int) 0;

// Fail

fail:
    Status = 1;  //-1 ??
    printf ("copy_process_struct: Fail\n");
    return (int) Status;
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
 
pid_t getNewPID (void)
{

// See:
// gpid.h

    // GRAMADO_PID_BASE = GRAMADO_PID_KERNEL = 0.
    
    int i = GRAMADO_PID_BASE;
    
    //register int i=10;
    
    struct process_d  *p;

    while ( i < PROCESS_COUNT_MAX )
    {
        p = (struct process_d *) processList[i];

        if ( (void *) p == NULL )
        { 
            // return the new pid.
            return (pid_t) i; 
        }
        
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
 * init_processes:
 *    Inicaliza o process manager.
 *    #todo: rever esse nome, pois na verdade estamos 
 * inicializando variaveis usadas no gerenciamento de processo.
 */

// Called by init_microkernel in mk.c

void init_processes (void)
{
    register int i=0;

    debug_print("init_processes:\n");

// Globals

// O que fazer com a tarefa atual.
    kernel_request = 0;

// ?? Contagem de tempo de execu��o da tarefa atual.
// n�o precisa, isso � atualizado pelo request()
    //kernel_tick = 0;

// ?? Ativa o kernel switch do scheduler.
    kernel_switch = 0;

    set_current_process(0);
    //current_process = 0;

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
// Pega, bloqueia e tira da lista.

    for ( i=1; i < PROCESS_COUNT_MAX; i++ )
    {
        P = (void *) processList[i];
        P->state = PROCESS_BLOCKED;
        
        // Not kernel.
        //#bugbug: review
        if (i != 100){
            processList[i] = (unsigned long) 0;
        }
    };

// Check process 0.
    P = (void *) processList[0];
    if ( (void *) P == NULL ){
        panic ("CloseAllProcesses: P\n");
    }

// #todo: validation?

// #bugbug
// The kernel is process 100. #bugbug
//#bugbug: review
    
    P = (void *) processList[100];

    if ( (void *) P == NULL ){
        panic ("CloseAllProcesses: kernel\n");
    }
}


// Worker for create_process.
// Do not check parameters validation.
void ps_initialize_process_common_elements( struct process_d *p )
{
    register int i=0;

    //if( (void*) p == NULL )
        //return;

    p->objectType  = ObjectTypeProcess;
    p->objectClass = ObjectClassKernelObjects;
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
// See: 
// kstdio.c for the streams initialization.
// #todo: We need a flag.
// #todo: Melhorar esse nome.

    if (kstdio_standard_streams_initialized != TRUE ){
        panic ("ps_initialize_process_common_elements: [ERROR] Standard stream is not initialized\n");
    }

    for ( i=0; i<NUMBER_OF_FILES; ++i ){ p->Objects[i] = (unsigned long) 0; }

    if ( (void *) stdin == NULL ){
        panic ("ps_initialize_process_common_elements: [TEST] stdin");
    }

    if ( (void *) stdout == NULL ){
        panic ("ps_initialize_process_common_elements: [TEST] stdout");
    }

    if ( (void *) stderr == NULL ){
        panic ("ps_initialize_process_common_elements: [TEST] stderr");
    }

    p->Objects[0] = (unsigned long) stdin;
    p->Objects[1] = (unsigned long) stdout;
    p->Objects[2] = (unsigned long) stderr;

// ==============

//
// tty support
//

    //printf ("ps_initialize_process_common_elements: calling tty_create[DEBUG]\n");

//++
    p->tty = ( struct tty_d *) tty_create(); 

    if ( (void *) p->tty == NULL )
    {
        panic ("ps_initialize_process_common_elements: Couldn't create tty\n");
    }
    tty_start(p->tty);
//--

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
    ppid_t ppid, 
    char *name, 
    unsigned int cpl,
    unsigned long pml4_va,
    unsigned long pdpt0_va,
    unsigned long pd0_va,
    int personality )
{
    struct process_d  *Process;
    pid_t PID = -1;

    // Para a entrada vazia no array de processos.
    struct process_d *EmptyEntry; 

    unsigned long BasePriority=0;
    unsigned long Priority=0;


    int Personality = personality;


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

    //if ( processNewPID < GRAMADO_PID_BASE || 
    //     processNewPID >= PROCESS_COUNT_MAX )
    //{
    //    processNewPID = (int) GRAMADO_PID_BASE;
    //}


    BasePriority = (unsigned long) priority; 
    Priority     = (unsigned long) priority;

//
// Process
//

    Process = (void *) kmalloc( sizeof(struct process_d) );

    if ( (void *) Process == NULL ){
        panic ("create_process: Process\n");
    }

    memset( Process, 0, sizeof(struct process_d) );


    Process->personality = (int) Personality;

    Process->exit_in_progress = FALSE;

    Process->base_priority = BasePriority;
    Process->priority = Priority;


//get_next:

// Get empty.
// Obt�m um �ndice para um slot vazio na lista de processos.
// Se o slot estiver ocupado tentaremos o pr�ximo.
// Na verdade podemos usar aquela fun��o que procura por um vazio. 

    while (1){

        PID = (int) getNewPID();

        if ( PID < GRAMADO_PID_BASE || PID >= PROCESS_COUNT_MAX )
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

    ps_initialize_process_common_elements( (struct process_d *) Process );

    //Process->objectType  = ObjectTypeProcess;
    //Process->objectClass = ObjectClassKernelObjects;

 
// cpl
    Process->cpl = (unsigned int) cpl;

    if (cpl!=RING0 && cpl!=RING3)
        panic("create_process: cpl\n");

// iopl
// Qual é o privilágio padrão?
// weak protection!
    Process->rflags_iopl = (unsigned int) 3;  //weak protection 



    // Not a protected process!
    Process->_protected = 0;

    //processNewPID = (int) PID;
        
    // Identificadores.
    // PID. PPID. UID. GID.
    Process->pid  = (int) PID; 
    Process->ppid = (int) ppid; 

    // sessão crítica.
    Process->_critical = 0;

    //foi para o fim.
    //State of process
    //Process->state = INITIALIZED;  

// #todo: Via argument
     Process->plane = FOREGROUND_PROCESS;

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

// Page Directory: (em 64bit agora é pml4)
//     Alocar um endere�o f�sico para o diret�rio de p�ginas do 
// processo a ser criado, depois chamar a fun��o que cria o diret�rio.
// @todo:
// IMPORTANTE: Por enquanto os processos s�o criadas usando o 
// diret�rio de p�ginas do processo Kernel. Mas temos que criar 
// um diret�rio novo pra cada processo criado.
// O diret�rio de todos os processos de usu�rio ser�o iguais. 
// Ter�o uma �rea de us�rio particular e uma �rea compartilhada 
// em kernel mode.
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
// pd0
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
// # IMPORTANTE 
// Base da imagem do processo.
// Na verdade precisamos aceitar o endere�o passado via 
// argumento, pois nem todos processos come�am no endere�o 
// default.

//
// Image
//

// Endereço virtual e endere�o f�sico.

    Process->Image   = (unsigned long) base_address;  
    Process->ImagePA = (unsigned long) virtual_to_physical ( 
                                           Process->Image, 
                                           gKernelPML4Address ); 
                                               

//
// Child image
//

// Endereço virtual e endere�o f�sico de um processo filho.
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

    Process->HeapStart = (unsigned long) g_heappool_va + (g_heap_count * g_heap_size);
    Process->HeapSize  = (unsigned long) g_heap_size;
    Process->HeapEnd   = (unsigned long) (Process->HeapStart + Process->HeapSize); 
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

    Process->StackStart  = (unsigned long) UPROCESS_DEFAULT_STACK_BASE; 
    Process->StackSize   = (unsigned long) UPROCESS_DEFAULT_STACK_SIZE; //?? usamos isso na hora de criar a stack?? 
    Process->StackEnd    = (unsigned long) (Process->StackStart - Process->StackSize);  
    Process->StackOffset = (unsigned long) UPROCESS_DEFAULT_STACK_OFFSET;  //??


//
// PPL - (Process Permition Level).(gdef.h)
//

// Determina as camadas de software que um processo 
// tera acesso irrestrito.

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

// Que tipo de scheduler o processo utiliza. (rr, realtime ...).
    //Process->scheduler_type = ; 

// #todo
// Counters

    //Process->step
    //Process->quantum
    //Process->timeout
    //Process->ticks_remaining

// As threads do processo iniciam com esse quantum.

    //Process->ThreadQuantum   

    //Process->event

// #importante
// user session, room and desktop.
// #bugbug: 
// Nao temos informaçao sobre a user session, 
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

// #debug
    debug_print ("GetProcessHeapStart:\n");
    //printf ("GetProcessHeapStart: [DEBUG] pid %d\n", pid);
    //refresh_screen();

// pid.

    if ( pid < GRAMADO_PID_BASE || 
         pid >= PROCESS_COUNT_MAX )
    {
        debug_print ("pid\n");
        goto fail; 
    }

// process structure.

    process = (struct process_d *) processList[pid];

    if ( (void *) process == NULL ){
        debug_print ("process\n");
        goto fail;
    }

   if ( process->used != TRUE || 
        process->magic != 1234 )
   {
       debug_print ("process validation\n");
       goto fail;
   }

// OUT: 
// The start address of the heap of a process.
    return (unsigned long) process->HeapStart;

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
 * init_process_manager:
 *     Initialize process manager.
 *     processInitializeProcessManager();
 */

int init_process_manager (void)
{
    caller_process_id = (int) 0;

    //processNewPID = (int) GRAMADO_PID_BASE;

    //...

    return 0;
}


/*
 * alloc_memory_for_image_and_stack:
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
// Explicando:
// Copia a imagem do processo atual e salva o endereço
// da copia num elemento da estrutura passada como argumento.
// OUT:
// #bugbug: 
// Na verdade não estamos mais copiando e 
// sim criando um endereçamento novo.

int alloc_memory_for_image_and_stack( struct process_d *process )
{
    unsigned long __new_base=0;   // base
    unsigned long __new_stack=0;  // stack

    if ( (void *) process == NULL ){
        panic ("alloc_memory_for_image_and_stack: [FAIL] process \n");
    }


// ==================================================

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

/*
     #bugbug
     Os aplicativos estão ficando grandes e a falta de
     memória pra a criação deles esta causando problemas.
     Estamos usando 300KB de memória para a criação do processo
     pois 200KB já não é o bastante e causa falha na inicialização
     do processo.
     Lembrando que precisamos de memória para a imagem do processo
     e para sua pilha.
     Os aplicativos estão com tamanhos que variam de 100KB à 200KB.
*/

// 300KB
// Quantas páginas temos em 300KB?

    //int imagesize_in_kb = 300;
    int imagesize_in_kb = 320;

    int number_of_pages=0;
    //number_of_pages = (int) (200*1024)/4096;   // #bugbug: Not enough.
    number_of_pages = (int) (imagesize_in_kb*1024)/4096;     // 

    __new_base = (unsigned long) allocPages(number_of_pages); 

    if ( __new_base == 0 )
    {
        // #important
        panic ("alloc_memory_for_image_and_stack: [FAIL] __new_base\n");
    }

// ==================================================



// ==================================================

//
// Image stack
//

// 32 KB.
// Allocating memory for the process's stack.
// #todo: We need this size.
// Retorna um endereço virtual.
// Mas usaremos apenas o endereço físico extraído desse endereço.

// 32 KB
// Quantas páginas temos em 32KB?

    number_of_pages = (int) (32*1024)/4096;     // original
    //number_of_pages = (int) (128*1024)/4096;  // teste

    __new_stack = (unsigned long) allocPages(number_of_pages); 

    if ( __new_stack == 0 )
    {
        // #important
        panic ("alloc_memory_for_image_and_stack: [FAIL] __new_stack\n");
    }

// ==================================================


//
// == Copying memory ==========
//

// #todo
// Faremos isso somente se a flag indicar 
// que queremos realizar um fork()

    //if ( clone_flags & DO_FORK ){ ... }

// Copying base and stack.
// Copiando do processo atual para o buffer que alocamos
// logo acima.

// #bugbug: So precisamos copiar 
// se tivermos fazendo uma rotina de fork()
// que pessa pra copiar. A clonagem nao copia.
// Copia a imagem do processo.
// Copia do início da imagem. 200KB.
    
    //if( ... ){
    memcpy ( 
        (void *) __new_base,  
        (const void *) CONTROLTHREAD_ENTRYPOINT, 
        (imagesize_in_kb*1024) );
    //}

// Copia a pilha do process.
// Copia do fim da stack. 32KB.
    memcpy ( 
        (void *) __new_stack, 
        (const void *) ( CONTROLTHREAD_STACK-(32*1024) ), 
        (32*1024) );

    //memcpy ( 
        //(void *) __new_stack, 
        //(const void *) ( CONTROLTHREAD_STACK-(128*1024) ), 
        //(128*1024) );

//
// Getting the physical addresses.
//

// Obtendo o edereço físico da base da imagem e da pilha.

    unsigned long new_base_PA  = 
        (unsigned long) virtual_to_physical ( __new_base, gKernelPML4Address ); 

    unsigned long new_stack_PA = 
        (unsigned long) virtual_to_physical ( __new_stack, gKernelPML4Address ); 

    if ( new_base_PA == 0 )
    {
        //printf("processCopyMemory: new_base_PA\n");
        //refresh_screen();

        panic("alloc_memory_for_image_and_stack: new_base_PA\n");
        
        return -1;
    }
    
    if ( new_stack_PA == 0 )
    {
        //printf("processCopyMemory: new_stack_PA\n");
        //refresh_screen();

        printf("alloc_memory_for_image_and_stack: new_stack_PA\n");
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

// Salvando os endereços virtuais onde 
// carregamos a imagem e a pilha.

    process->childImage  = (unsigned long) __new_base;
    process->childStack  = (unsigned long) __new_stack;

// Salvando endereços físicos obtidos anteriormente.  
// Esses endereços representam a base da imagem e o inicio da pilha.

    process->childImage_PA = (unsigned long) new_base_PA;
    process->childStackPA  = (unsigned long) new_stack_PA;

// #debug
// Showing the addresses of base and stack pointers.

    //printf("processCopyMemory: new base PA %x | new stack PA %x \n",
        //new_base_PA, new_stack_PA );

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

// #todo: max limit
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

// #todo
// max limit

    if (pid<0){
        panic ("process_open_gate: pid \n");
    }

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

// #todo: max limit

    if ( pid < 0){
        return NULL;
    }

    // Get process pointer.
    p = (struct process_d *) processList[ pid ];

    //#todo: Check process validation.

// #todo: max limit

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
//#todo: IN: pid, fd
file *process_get_file ( int fd )
{

    pid_t current_process = (pid_t) get_current_process();

// #todo: max limit
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

    if ( pid < 0 || pid >= PROCESS_COUNT_MAX )
    {
        return (int) (-EINVAL);
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


// OUT: process struture pointer.
struct process_d *create_and_initialize_process_object(void)
{
    pid_t NewPID = (pid_t) (-1);  //fail

    struct process_d  *new_process;
    register int i=0;

// process structure.

    new_process = (struct process_d *) processObject();
    if ( (void *) new_process == NULL )
    {
        debug_print ("create_and_initialize_process_object: [FAIL] new_process\n");
        printf      ("create_and_initialize_process_object: [FAIL] new_process\n");
        goto fail;
    }
    
    //no personality yet
    new_process->personality = 0;

// Get PID.
// Obtêm um índice para um slot vazio na lista de processos.
// Precisa estar dentro do range válido para processos
// em ring3.

    // Invalidate.
    new_process->pid = -1;

// Get new pid.
// #:: We have a valid range here!
// #todo: Change to generate_new_pid();

    NewPID = (pid_t) getNewPID();
    
    if ( NewPID < GRAMADO_PID_BASE || 
         NewPID >= PROCESS_COUNT_MAX )
    {
        debug_print ("create_and_initialize_process_object: [FAIL] NewPID\n");
        printf      ("create_and_initialize_process_object: [FAIL] NewPID={%d}\n", 
            NewPID );
        goto fail;
    }

// Initializing the process structure.
// Saving the process pointer in the list.

    new_process->pid = (pid_t) NewPID;  // :)

    new_process->uid = (uid_t) current_user;
    new_process->gid = (gid_t) current_group;
    new_process->syscalls_counter = 0;


// tty
//++
    new_process->tty = ( struct tty_d *) tty_create();

    if ( (void *) new_process->tty == NULL )
    {
         panic ("create_and_initialize_process_object: Couldn't create TTY\n");
    }
    
    tty_start(new_process->tty);
//--





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
        panic("create_and_initialize_process_object: g_heappool_va\n");
    }
    if (g_heap_count == 0){
        panic("create_and_initialize_process_object: g_heap_count\n");
    }
    if (g_heap_size == 0){
        panic("create_and_initialize_process_object: g_heap_size\n");
    }

// #bugbug
// There is a limit here. End we will have a huge problem 
// when reach it.

//===========================================================

//
// Heap
//

    new_process->HeapStart = 
        (unsigned long) (g_heappool_va + (g_heap_count * g_heap_size));
    new_process->HeapSize = 
        (unsigned long) g_heap_size;
    new_process->HeapEnd = 
        (unsigned long) (new_process->HeapStart + new_process->HeapSize); 
    
    g_heap_count++;

//#debug
    //printf ("clone_and_execute_process: HeapStart %x | HeadSize %x | HeapEnd %x \n",
    //    new_process->HeapStart, new_process->HeapSize, new_process->HeapEnd );

//#breakpoint
    //refresh_screen();
    //while(1){}

//===========================================================

//
// Stack
//

// Stack for the clone. 

    new_process->control->rsp = (unsigned long) CONTROLTHREAD_STACK;

    new_process->StackStart = 
        (unsigned long) CONTROLTHREAD_STACK;
    new_process->StackSize = 
        (unsigned long) (32*1024);  // Isso foi usado na rotina de alocação.
    new_process->StackEnd = 
        (unsigned long) ( new_process->StackStart - new_process->StackSize );

//#todo
//#debug: print stack info.


// #todo: Explain it better.
    new_process->Image = (unsigned long) CONTROLTHREAD_BASE;  // 0x200000 

    new_process->used = TRUE;
    new_process->magic = 1234;
    
// :)
    processList[ NewPID ] = (unsigned long) new_process;

// OUT:
// Pointer for a structure of a new process.
    return (struct process_d *) new_process;
fail:
    return NULL;
}


