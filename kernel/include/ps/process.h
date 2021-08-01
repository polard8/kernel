// process.h


#ifndef __PROCESS_H
#define __PROCESS_H    1



#define PROCESS_MAGIC  1234


// #alternative
// Position.
// Position in cell.
// Main classes for the processes and threads.

#define KING           1
#define SPECIAL_GUEST  2
#define BETA           3


//#bugbug
//talvez aqui nao seja o melhor lugar pra definir isso.
#define gramado_pid_t pid_t


// Image. 
// (Base da imagem de um processo de usu�rio).
//
// "Todo processo ter� seu pr�prio diret�rio de p�ginas
//  e ser� carregado no endere�o virtual 0x400000, logicamente
//  cada processo ser� carregado em um endere�o f�sico diferente."

// old, used in gramado 32bit
//#define UPROCESS_IMAGE_BASE  0x400000
// new, used in gramado 64bit
#define UPROCESS_IMAGE_BASE  0x200000 


//Process Limit. (User process) 
//(O limite � o in�cio do kernel).
//#define UPROCESS_PROCESS_LIMIT 0xC0000000    
#define UPROCESS_PROCESS_LIMIT 0x30000000    

// Heap.
// Base default do heap do processo.
// "Endere�o virtual de onde come�a o heap de um processo,
//  evidentemente, cada processo ter� seu heap em um 
//  endere�o f�sico diferente".

#define UPROCESS_DEFAULT_HEAP_BASE  0x80000000 
//Tamanho default do heap do processo.  
#define UPROCESS_DEFAULT_HEAP_SIZE  0x2000     

//Stack.
//Deslocamento default do in�cio da pilha em rela��o ao in�cio do kernel. #bugbug
#define UPROCESS_DEFAULT_STACK_OFFSET 0x2000   
//Base default da pilha do processo.
#define UPROCESS_DEFAULT_STACK_BASE ( UPROCESS_PROCESS_LIMIT - UPROCESS_DEFAULT_STACK_OFFSET )  
//Tamanho da pilha do processo.   
#define UPROCESS_DEFAULT_STACK_SIZE 0x2000    



//
// Bases para a contagem de processos, do sistema e de usu�rios.
// 
 
//Primeiro �ndice na contagem das processos do sistema.
#define SYSTEM_BASE_PID 0
//Primeiro �ndice na contagem das processos dos usu�rios.  
#define USER_BASE_PID 100    


//
// == Priorities ==================================================
//

// Priority levels.
// Used by processes and threads.

// Classes:
// 1 ~ 5 = variable.
// 6 ~ 9 = realtime.
//
// variable:
//     Can be changed on the fly.
// realtime:
//     Can't be changed on the fly. (maior que o normal)
//
// # ps:
// The base priority is never changed. It's used to classify
// the priority level.
// The priority can't be changed to a level below the base priority.
//

#define PRIORITY_LOW4      1  // 4
#define PRIORITY_LOW3      2  // 3
#define PRIORITY_LOW2      3  // 2
#define PRIORITY_LOW1      4  // 1 
#define PRIORITY_NORMAL    5  // 0 (Normal).
#define PRIORITY_HIGH1     6  // 1
#define PRIORITY_HIGH2     7  // 2
#define PRIORITY_HIGH3     8  // 3
#define PRIORITY_HIGH4     9  // 4

// Aliases.

#define PRIORITY_MIN       PRIORITY_LOW4
#define PRIORITY_MAX       PRIORITY_HIGH4
#define PRIORITY_LOW       PRIORITY_LOW1
#define PRIORITY_HIGH      PRIORITY_HIGH1 


//
// == Multiplier =========================
//

// #todo: Criar uma vari�vel para esse multiplicador.
// para fazermos testes;
//unsigned long g_timeslice_multiplier;
//#define TIMESLICE_MULTIPLIER 1
//#define TIMESLICE_MULTIPLIER 2
#define TIMESLICE_MULTIPLIER 3
//...


/*
 * Constantes para n�veis de quantum.
 * Tempo de processamento atribuido pelo scheduler � cada processo.
 * dado em quantidades de ticks ...
 * para saber quanto tempo tem que multiplicar por 10ms ... que � 
 * o tempo de cada interrup��o ... e somar o tempo perdido com taskswitch ...
 *  100ms + 5ms(que o timer fica esperando o kernel habilitar as interrup��es).
 */

// #test
#define QUANTUM_BASE   (PRIORITY_NORMAL*TIMESLICE_MULTIPLIER)
#define QUANTUM_LIMIT  (PRIORITY_MAX *TIMESLICE_MULTIPLIER)

// #test
// Limite de tempo esperando.
#define READY_LIMIT   (PRIORITY_MAX *TIMESLICE_MULTIPLIER)
#define WAITING_LIMIT (PRIORITY_MAX *TIMESLICE_MULTIPLIER)
#define BLOCKED_LIMIT (PRIORITY_MAX *TIMESLICE_MULTIPLIER)
 
 
//Lista de status na cria��o de um processo.     
#define ERRO_SLOT_OCUPADO  0xfffff    //Slot ocupado.      
#define ERRO_DEFAULT       0xffffe
//...


//Process runtime stack.
//??? Deve ser o limite m�ximo para a pilha de um processo.
#define MAXSTACK 128    //dwords.
 
//N�mero total de slots para cria��o de processo.
//@todo: deletar, definido em threads. ??? 
#define NUMERO_TOTAL_DE_SLOTS 256   



/*
 * process_state_t
 *     Status de um processo.
 *     @todo: Pode-se usar mais status.
 *            como estado de transi��o.
 *  Os status de um processo s�o diferentes do status de uma thread.
 */ 

typedef enum {
    PROCESS_CREATED,
    PROCESS_INITIALIZED,
    PROCESS_RUNNING,
    PROCESS_BLOCKED,
    PROCESS_TERMINATED,
    PROCESS_IN_MEMORY,        //O processo est� carregado na mem�ria.
    PROCESS_OUT_OF_MEMORY,    //O processo n�o est� carregado na mem�ria.
	//...
}process_state_t;


/* 
 appmode_t
 
 Importante:
 
 APPMODE_TERMINAL = O kernel cria uma estrutura de terminal 
 com uma janela associada a essa estrutura, essa janela ser� a 
 janela de terminal para o aplicativo.
 APPMODE_WINDOW = O kernel n�o cria estrutura de terminal para 
 esse processo e o processo criar� janelas.
 */

typedef enum {
    APPMODE_NULL,      // Isso se aplica ao processo kernel e ao processo idle por exemplo.
    APPMODE_TERMINAL,  // O kernel cria uma janela de terminal para o aplicativo.
    APPMODE_WINDOW,    // O kernel n�o cria janela de terminal para o aplicativo
}appmode_t;



struct process_d 
{
    // Object control
    object_type_t  objectType;
    object_class_t objectClass;
    //struct object_d *object;

    int used;
    int magic;
    
    int position;


    // Other process can't take some actions on this process 
    // if it is protected. ex: It can't be killed by another process.
    int _protected;

    // Arquivos abertos.
    // Objetos abertos pelo processo.
    unsigned long Objects[64];

	//  Identificadores.
	//PID, (Process Identification), 
	//PPID, (Parent Process Identification),
	//UID, (User Identification),
	//GID, (Group Identification),

    //process group.
    int pgrp;

    // process
    pid_t  pid;
    pid_t  ppid;
    
    // user
    uid_t  uid;
    uid_t  euid;
    uid_t  ruid;
    uid_t  suid;
    
    // group
    gid_t  gid;
    gid_t  egid;
    gid_t  rgid;
    gid_t  sgid;

	// State.
	// flag ?
    process_state_t state; 

	//plano de execuçao.
    int plane;

	// error.
	//unsigned long error; 

//
// Name
//

	// @todo:
	// +name     (Nome=EXEMPLO.BIN)
	// +pathname (Caminho=/root/boot/EXEMPLO.BIN)
	// +cmd      (linha de comando ex:EXEM ) 

	//char *pathname;              //@todo: Incluir.	
    char *cmd;                     //Nome curto que serve de comando.
    char *name;                    //Nome do processo. 
	//unsigned long name_address;    //@todo: n�o usar isso.

    //#test
    //Assim fica mais f�cil enviar para o aplicativo.
    char __processname[64];    // HOSTNAME_BUFFER_SIZE
    size_t processName_len;    // len 

//
// Input
//
    
    // #importante
    // De onde vem o o input do processo. (stdin)
    // O stdin pode vim de um terminal. Pois um terminal
    // pode estar gerenciando o input de teclado ou mouse e
    // transferindo os dados para o processo atrav�s de uma 
    // disciplina de linhas.
    // ex: #todo INPUTTYPE_TTY INPUTTYPE_RAW ...
    int input_type;

//
// tty 
//
    
    // Essa � a tty do processo.
    // Ela ser� master se o processo for um shell e
    // Ser� slave se o processo for um terminal.
    // O terminal(slave) encontrar� o shell(master) em tty->link.
    struct tty_d  *tty;

    // Um buffer no app en ring3
    // onde o driver de rede pode colocar conte�do e depois
    // avisar o processo via mensagem.
    char *net_buffer;
 
    // Qual � apersonalidade do processo.
    // Ele deve agir como unix-like, gramado-like, etc ?
    int personality;

	//Importante:
	//isso substituir� a flag 'terminal'
	//APPMODE_TERMINAL = O kernel cria uma estrutura de terminal 
	//com uma janela associada a essa estrutura, essa janela ser� a 
	//janela de terminal para o aplicativo.
	//APPMODE_WINDOW = O kernel n�o cria estrutura de terminal para 
	//esse processo e o processo criar� janelas.

    appmode_t appMode;

//
//  Banco de dados
//

    // #??
    // This is a work in progress.
    // Memory management.

	// Obs: 
	// Um processo � um cliente de banco de dados.
	// Um processo tem contas conjuntas e pessoais.
	// Um processo poder� compartilhar esses objetos.	

	//
	// BANCOS
	//

	//Acesso ao banco de dados do kernel. (n�o � uma lista).
    //struct bank_d *kdb;

	//Lista de acessos � bancos de contas conjuntas.
    //struct bank_d *gdbListHead;

	//Lista de acessos � bancos de contas pessoais.
    //struct bank_d *ldbListHead;


//
// CONTAS
//

	//Lista de contas conjuntas que o processo tem.
    //struct aspace_d *aspaceSharedListHead;

	//Lista de contas pessoais que o processo tem.
    //struct aspace_d *aspacePersonalListHead;

	//Lista de contas conjuntas que o processo tem.
    //struct dspace_d *dspaceSharedListHead;

	//Lista de contas pessoais que o processo tem.
    //struct dspace_d *dspacePersonalListHead;

//
// Frame pool
//

	//Testing...
	//Process Page Table. (PPT)
	//Quais s�o as p�ginas que o processo est� usando e onde elas est�o.
	//na tabela tem que ter: O n�mero da p�gina. onde ela est�, se no disco ou se na mem�ria
	//qual � o n�mero do pageframe da p�gina e qual o status de modifica��o
	// Bom, acho que pra isso, o processo deve trabalhar em um n�mero limitado de pagetables
	// pois o n�mero do frame deve ser o �ndice da pte dentro da page table.
	// Uma pagetable tem 1024 entradas, garantindo um n�mero de 1024 frames, o que d� 4MB.
	// Mas se um processo tiver mais que 4MB? Ent�o o diret�rio de p�ginas do processo
	// ter� que ter mais de uma page table.
	// Obs: O kernel deve manter uma lista de frames que podem ser usados.
	//      na hora de criar uma pagetable pra um page directory de um processo
	// � necess�rio pegar na lista de frames 1024 frames livres ou quanto for necess�rio.

	// **** IMPORTANTE ****
	// Uma lista de framepool. (Lista de parti��es de mem�ria f�sica).
	// Cada framepool � composto de 1024 frames.
	// Obs: *IMPORTANTE: Quando um processo � criado, pelo menos um framepool 
	// deve ser atribu�do a ele, mesmo antes de mapear os frames desse 
	// framepool em alguma pagetable do page directory do processo.

    // See: mm/x64mm.h

    struct frame_pool_d *framepoolListHead;

	//Quantidade de mem�ria f�sica usada pelo processo que n�o pode ser compartilhada
	//com outros processos. (em KB).
    unsigned long private_memory_size;

	//Quantidade de mem�ria f�sica usada pelo processo que pode ser compartilhada
	//com outros processos. (em KB).
    unsigned long shared_memory_size;

	//Quantidade de mem�ria usada por um processo em determinado espa�o de tempo.
	// workset = (private + shared);
    unsigned long workingset_size;
    unsigned long workingset_peak_size;


	//Qualquer pagefault deve ser registrada na estrutura do processo corrente.
	//?? n�o seria na thread ??
    unsigned long pagefaultCount;
	//...
	//ticks running ..
	//unsigned long Cycles;  // ?? double ??  
	
	//quantas vezes no total o dispacher atuou sobre ele.
	//Essa contagem n�o deve ser feita na thread.
	//Ou colocaremos aqui o total de todos os context switches das threads ??
	//unsigned long ContextSwitches;   

	// Importante:
	// working set support.
	// The working set of a process is the set of pages in the 
	// virtual address space of the process that are currently 
	// resident in physical memory. 
	// Quantas trocas de context sofreu durante um determinado tempo de an�lise.
	// Esse deve ser o mesmo tempo de an�lise usado para calcular o working set.


	//unsigned long ContextSwitchesDelta;  

//
// MEMORY SUPPORT
//

	// image = Imagem do programa principal do processo.
	// heap  = Heap do processo.
	// stack = Stack do proceso.

	// #bugbug
	// Me parece que isso considera que o processo s� tem um programa.
	// Como ficaria no caso do processo ter v�rios programas.
	// Podemos fazer aqui s� as informa��es para o programa principal.
	// Para os outros programas teremos apenas uma lista de ponteiros
	// para as estruturas que gerenciam eles.

	// ORDEM: 
	// O que segue � referenciado durante o processo de task switch.

//
// == pml4 ==============================
//

    // The pml4 table
    unsigned long pml4_VA;
    unsigned long pml4_PA;

    // The first pdpt
    unsigned long pdpt0_VA;
    unsigned long pdpt0_PA;

    // The first pd
    unsigned long pd0_VA;
    unsigned long pd0_PA;


	// Page directory information:
	// ==========================
	//     Todo processo deve ter seu pr�prio diret�rio.
	//     As threads usam o diret�rio do processo ao qual pertencem.
	//     O endere�o do diret�rio � carregado no CR3.

    // Ponteiro para a estrutura do diret�rio de p�ginas do processo.
    //struct page_directory_d *page_directory;  

    // #bugbug: Do not use this!
    //unsigned long DirectoryVA;
    //unsigned long DirectoryPA;


//
// Image support.
//

	// #IMPORTANTE
	// Com base na origem da imagem e no seu tamanho podemos
	// determinar a quantidade de p�ginas que o programa principal do processo
	// est� usando.
	// Como o programa foi caregado pelo boot loader, ainda n�o temos a lista
	// de p�ginas usadas por esse processo.
	// #obs: A lista � grande. Ent�o devemos fazer apenas um ponteiro para 
	// ela, ou colocarmos um ponteiro de estrutura head de uma lista encadeada.
	// #importante: esssa estrutura tem que ser simples. Com poucos elementos.
	// Poderemos usar essas informa��es para clonar o processo.

	// Base da imagem do processo.
	// Tamanho da imagem do processo.
	// Quantas p�ginas foram usadas por essa imagem. ImageSize/PageSize
 
    unsigned long Image;        // VA?
    unsigned long ImagePA;      // PA
    unsigned long ImageSize;    // ?? in bytes ??
    //unsigned long ImageSizeInBytes;
    //unsigned long ImageSizeInKB;
    unsigned long PagesPerImage; 


    // Usado durante fork().
    unsigned long childImage; 
    unsigned long childImage_PA; 
    unsigned long childStack; 
    unsigned long childStackPA; 


    //#todo: estrutura com informa��es sobre a imagem do processo.
    //see: image.h

    struct image_info_d *image_info;


	//#test
	//struct page_control_t *page_list_head;

//
// Heap
//

	//#importante 
	unsigned long Heap;            //Endere�o do in�cio do Heap do processo.
	unsigned long HeapEnd;
	unsigned long HeapSize;        //Tamanho do heap.
	
	//?? Isso serve para manipula��o do heap do processo.
	unsigned long HeapPointer;     //Ponteiro do heap do processo para o pr�xima aloca��o.
	unsigned long HeapLastValid;   //�ltimo ponteiro v�lido.
	unsigned long HeapLastSize;    //�ltimo tamanho alocado..	
	//struct heap_d *processHeap;  //@todo: Usar essa estrutura.

//
// Stack
//

	unsigned long Stack;          //Endere�o do in�cio da Stack do processo.
	unsigned long StackEnd;
	unsigned long StackSize;      //Tamanho da pilha.	
	unsigned long StackOffset;    //Deslocamento da pilha em rela��o ao in�cio do kernel.	
	//struct stack_d *processStack;  //@todo: Criar essa estrutura.

	// Teste: 
	// Blocos de memoria usados pelo processo.

	//struct mmblock_d mmBlocks[32];    //estruturas 
	//unsigned long mmblockList[32];    //ponteiros para estruturas.

	//Muitas informa��es sobre a mem�ria usada pro um processo.
	//struct process_memory_info_d *processMemoryInfo;


	//
	//  Environment.
	//


	//IOPL of the task. (ring).
    unsigned long iopl; 

//
// == Priorities ============
//

    // Priority levels.
    // Used by processes and threads.
    // Classes:
    // 1 ~ 5 = variable.
    // 6 ~ 9 = realtime.
    // variable:
    //     Can be changed on the fly.
    // realtime:
    //     Can't be changed on the fly.
    // # ps:
    // The base priority is never changed. It's used to classify
    // the priority level.
    // The priority can't be changed to a level below the base priority.
    // The base priority is static and the current priority is dinamic.

    unsigned long base_priority;  // static 
    unsigned long priority;       // dinamic

	//Que tipo de scheduler o processo utiliza. (rr, realtime ...).
	//int scheduler_type;    

    // syscalls counter.

    unsigned long syscalls_counter;

//
// Timer
//

	// Temporização da tarefa. 
	unsigned long step;               //Quantas vezes a tarefa usou o processador. 
	unsigned long quantum;            //thread quantum
	unsigned long timeout;            //Tempo em modo de espera. 
	unsigned long ticks_remaining;    //rt, quanto tempo a tarefa tem dispon�vel para ser concluida.

	//unsigned long alarm;            //Tempo para o pr�ximo alarme, dado em ticks.

	//unsigned long ThreadQuantum;    //As threads do processo iniciam com esse quantum.

	/*
	 * QUANTUM:
	 * =======
	 *     Quantum � a cota atrituida � cada processo pelo
	 *     scheduler. (time slice) 
	 *     Esse � o tempo limite imposto pelo scheduler para
	 *     execu��o de um processo. Ocorre ent�o uma preemp��o por tempo.
	 *      
	 *     'ProcessingTime' � atribu�do pelo processo. � o quanto
	 *     ele precisa. o quanto ele deseja.
	 */

//
// Working set support.
//

	//unsigned long ws_number_of_frames; 
	//...


//
// profiler
//
	//quanto por cento do tempo o processo ficou rodando.
	//� a soma do quanto ficou rodando todas as suas threads.
	unsigned long profiler_percentage_running;
	unsigned long profiler_ticks_running;
	unsigned long profiler_last_ticks;

//
// == Thread =================================
//

	// Tipo de thread
	// 0 = cpu-bound
	// 1 = i/o bound.

    int bound_type;

    // preempted:
    // flag ~ Sinaliza que um processo pode ou nao sofrer preempçao.
    // Uma tarefa de menor prioridade pode deixar o estado running 
    // para assumir o estado ready em favor de uma tarefa 
    // de maior prioridade que assumir o estado running.
    // Como na verdade quem sofre preempcao eh a thread, entao
    // esse marcador devera ser herdado pelos threads desse processo.

    unsigned long preempted;

    //saved ~ Sinaliza que a tarefa teve o seu contexto salvo.
    unsigned long saved;

    unsigned long PreviousMode;


    // Quantas threads o processo tem.
    int thread_count;

    // Thread de controle
    // Usada para input de mensagens e sinais.
    // Se fechar ela, tem que fechar o processo.
    struct thread_d *control;

    // Isso pode funcionar em parceria com control, 
    // quando criarmos novos processos ou clonarmos.
    struct thread_d *extra;  

    // Lista com ponteiros de estrutura das threads do processo.
    // O indice dessa lista serve para enumeralas. 
    // @todo: Usar array de estruturas din�mico. (Alocar).

	unsigned long tList[32];      //@todo: deletar  
	//struct thread_d *Threads;   //@todo: usar esse.
	//struct thread_d CurrentThread;

	//A primeira thead de uma lista linkada.
	struct thread_d *threadListHead;
	//struct thread_d *threadReadyListHead;
	//...


	/*
	 * event: 
	 *    Tipo de evento que fazem a tarefa entrar em modo de espera. 
	 */
	//event_type_t event;

//
// == Security ============================
//

    // User session, room (window station), desktop.

    struct usession_d  *usession;  //user session
    struct room_d      *room;      //room (Window Station) do processo.  
    struct desktop_d   *desktop;   //Desktop do processo.        

	// ORDEM: 
	// O que segue eh referenciado com pouca frequencia.

	//lista de arquivos ??
	//fluxo padr�o. stdio, stdout, stderr
	//unsigned long iob[8];

	//ponteiros para as streams do fluxo padr�o.
    unsigned long standard_streams[3];


//
// == fs ===============
//
    
    // #important
    // This is gonna help us to navigate in the levels of the pathname.
    // See: get_dir() on namei.c on linux 0.01
    
    // #todo
    // NOT initialized yet!
    
    // #todo #test
    // Colocando um pouco de simetria nos simbolos.

    // absolute pathname and relative pathname. 

    file *file_root;
    file *file_cwd;
    struct inode_d *inode_root;
    struct inode_d *inode_cwd;

	// #todo #bugbug
	// Size ?? 
	// Esse tamanho deve ser igual ao 
	// encontrado no modulo /fs.
 
    char root_string[32];
    char  cwd_string[32];

    // ===================================================

    // ===================================================

    // The search paths for a process.
    // It's a list of pointer to strings.
    // Each string has a path for a different directory.

    //char **search_paths;

	// @todo:
	// Outros:
	//tempo de cpu.
	//prioridade b�sica. //Obs: prioridade poderia ser uma estrutura.
	//contagem de threads usadas no momento.
	//path name - Endere�o completo do arquivo ex:/root/users/fred/text.bin
	//comando. - Comando que abre o programa.
	//Contagem de objetos sendo usado. (estatisticas ajudam melhorar o sistema.)
	//i/o read count - Contagem de leituras de disco feitas pelo processo.
	//i/o write count - Contagem de grava��es de disco feitas pelo processo.
	//generic i/o - Outras opera��es de i/o que n�o s�o leitura e escrita em disco.
	//todal de bytes lidos do disco pelo processo.
	//total de bytes gravados no disco pelo processo.
	//generic bytes i/o. contagem de bytes para opera��es gen�ricas de i/o, excluindo disco.
	

	// wait4pid: 
	// O processo esta esperando um processo filho fechar.
	// Esse � o PID do processo que ele est� esperando fechar.

    pid_t wait4pid;

	// N�mero de processos filhos.
    int nchildren;
	
	// Lista de processos filhos que est�o no estado zumbi.
	// List of terminated childs
	struct process_d *zombieChildListHead;           
	
	//?? mensagens pendentes.	
	//struct thread_d *sendersList; //Lista encadeada de processos querendo enviar mensagem
	//struct thread_d *nextSender;  //pr�ximo processo a enviar mensagem.

	//
	//   ## IPC ##
	//


    // Signal
    // See: include/klib/signal.h
    unsigned long signal;
    unsigned long umask;
    //struct sigaction sigaction[32];

    
    unsigned long alarm;
    
    
    // Critical section;
    // Devemos checar isso quando um processo terminar,
    // para que ele não fique em sua sessão crítica 
    // evitando que outros possam entrar.
    int _critical;

    // Quando um processo só pode receber mensagens de um 
    // determinado processo. Ou de qualquer um.
    // Ex: ANY=-1, PID ...
    // pid_t receive_from_pid;


	// di�logo com o processo.
	// importante no caso de servidores e drivers
	unsigned long dialog_address;


//
// == Socket ================================== 
//

    // list of sockets to accept connection.
    //int accept[5];
    //file *file_accept;   //aceitando através de ponteiro de arquivo.

    // Vamos colocar aqui a estrutura de socket.
    void *priv;

    // #todo
    // Precisamos de uma lista de conexoes pendentes.
    // O cliente invocou a conexao apenas uma vez
    // e precisa uasr o servidor varias vezes
    
    // Lista de ponteiros para estruturas de sockets.
    // max =  32 cliente com conexoes pendentes.
    // See: rtl/net/gdef.h
    // See: rtl/net/socket.h

    unsigned long socket_pending_list[SOCKET_MAX_PENDING_CONNECTIONS];

    int socket_pending_list_head;
    int socket_pending_list_tail;
    
    //listen() will setup this thing.
    //nao pode ser mais que 32. que eh o tamanho do array
    // SOCKET_MAX_PENDING_CONNECTIONS is the limit for this.
    int socket_pending_list_max;    

    //========================================



    //Motivo do processo fechar.
    int exit_code;

    // Navigation

    struct process_d *prev;
    struct process_d *next;
};

struct process_d *KernelProcess;     // Base kernel
struct process_d *InitProcess;       // init process.

/*
 *    processList:
 *        Tabela de processos.
 *
 *    **** LONG-TERM SCHEDULER FOR PROCESSES ****
 *
 *     Essa � a thread job list, ou job queue.
 *     Armazena todos os processos do sistema.
 *     os que est�o residentes na memoria ram e as que n�o est�o.
 */ 

// Max number of processes.
#define  PROCESS_COUNT_MAX  1024 

unsigned long processList[PROCESS_COUNT_MAX];


// Invalidate pml4.
// Linux style. 

#define invalidate() \
    asm ("movq %%rax, %%cr3"::"a" (0))


//
// == Prototypes =====================================================
//




//==============
// clone.c
int copy_process_structure( pid_t p1, pid_t p2 );
pid_t copy_process( const char *filename, unsigned long clone_flags );
int processCopyProcess ( pid_t p1, pid_t p2 );

pid_t clone_and_execute_process ( const char *filename, pid_t pid );


//==============
// plib.c
void show_currentprocess_info (void);
void show_process_information (void);


int GetCurrentPID (void);
struct process_d *GetCurrentProcess(void);


unsigned long __GetProcessStats ( int pid, int index );
int getprocessname ( int pid, char *buffer );
struct process_d *processObject (void);
pid_t getNewPID (void);
int processTesting (int pid);
int processSendSignal (struct process_d *p, unsigned long signal);
void init_processes (void);
void CloseAllProcesses (void);

// ===

// Worker for create_process.
void
__ps_initialize_process_common_elements(
    struct process_d *p );
    
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
    unsigned long pd0_va );

// ===

unsigned long GetProcessPML4_PA ( struct process_d *process );
unsigned long GetProcessPML4_VA ( struct process_d *process );

unsigned long GetProcessHeapStart ( pid_t pid );


void 
SetProcessPML4_VA ( 
    struct process_d *process, 
    unsigned long va );

void 
SetProcessPML4_PA ( 
    struct process_d *process, 
    unsigned long pa );


int get_caller_process_id (void);
void set_caller_process_id (int pid);

int init_process_manager (void);

int processCopyMemory ( struct process_d *process );


// Critical section
#define __GATE_CLOSED    0
#define __GATE_OPEN      1
void process_close_gate(int pid);   //227 close
void process_open_gate(int pid);    //228 open

file *process_get_file_from_pid ( pid_t pid, int fd );
file *process_get_file ( int fd );


int process_get_tty (int pid);

struct process_d *__create_and_initialize_process_object(void);


#endif    


















