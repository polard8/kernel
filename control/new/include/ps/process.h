
// process.h

#ifndef __PROCESS_H
#define __PROCESS_H    1


extern int copy_process_in_progress;

//#bugbug
//talvez aqui nao seja o melhor lugar pra definir isso.
#define gramado_pid_t  pid_t

#define PROCESS_MAGIC  1234



#define PERSONALITY_GRAMADO  1000
#define PERSONALITY_GWS      1001
// ...


// Processes:
// Os processos BATCH são BACKGROUND.
// Os processos GWS são FOREGROUND.
#define BACKGROUND_PROCESS  1 
#define FOREGROUND_PROCESS  2



// Image. 
// (Base da imagem de um processo de usuário).
// virtual address
#define UPROCESS_IMAGE_BASE  0x200000 


//Process Limit. (User process) 
//(O limite é o início do kernel).
#define UPROCESS_PROCESS_LIMIT  0x30000000 

// Heap.
// Base default do heap do processo.
// "Endere�o virtual de onde come�a o heap de um processo,
//  evidentemente, cada processo ter� seu heap em um 
//  endere�o f�sico diferente".

// #bugbug
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


//
// Main priority sets
//

// class 1: Normal
#define PRIORITY_P1  1
#define PRIORITY_P2  2
#define PRIORITY_P3  3
// class 2: Real time
#define PRIORITY_P4  4
#define PRIORITY_P5  5
#define PRIORITY_P6  6

#define PRIORITY_BOOST  (PRIORITY_P6*3)

// Class 1: Normal
#define PRIORITY_LOW       PRIORITY_P1
#define PRIORITY_NORMAL    PRIORITY_P2
#define PRIORITY_HIGH      PRIORITY_P3
// Class 2: Real time
#define PRIORITY_LOW_RT       PRIORITY_P4
#define PRIORITY_NORMAL_RT    PRIORITY_P5
#define PRIORITY_HIGH_RT      PRIORITY_P6


// Class 1: Normal threashold
#define PRIORITY_THRESHOLD       PRIORITY_LOW
// Class 2: Real time threashold
#define PRIORITY_THRESHOLD_RT    PRIORITY_LOW_RT
// Class 1: Normal time critical
#define PRIORITY_TIME_CRITICAL       PRIORITY_LOW_RT
// Class 2: Real time time critical
#define PRIORITY_TIME_CRITICAL_RT    PRIORITY_HIGH_RT


// Class 1: Normal
#define PRIORITY_BATCH        PRIORITY_LOW
#define PRIORITY_INTERACTIVE  PRIORITY_NORMAL
#define PRIORITY_SYSTEM       PRIORITY_HIGH
// Class 1: Real time
#define PRIORITY_BATCH_RT        PRIORITY_LOW_RT
#define PRIORITY_INTERACTIVE_RT  PRIORITY_NORMAL_RT
#define PRIORITY_SYSTEM_RT       PRIORITY_HIGH_RT

#define PRIORITY_MIN       PRIORITY_P1
#define PRIORITY_MAX       (PRIORITY_P6 + PRIORITY_BOOST)

// ##
// A prioridade no escalonamento não afetara os créditos.

// ----------------------------------------------------

//
// Flags for cloning a process.
//

// Used in copy_process();

#define CLONE_THREAD    1
// ...


typedef enum {

    PROCESS_TYPE_NULL,
    PROCESS_TYPE_SYSTEM,       // high priority
    PROCESS_TYPE_INTERACTIVE,  // medium priority
    PROCESS_TYPE_BATCH,        // low priority
}process_type_t;


/*
 * process_state_t
 *     Status de um processo.
 *     @todo: Pode-se usar mais status.
 *            como estado de transi��o.
 *  Os status de um processo s�o diferentes do status de uma thread.
 */ 
// canonical.
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
    APPMODE_WINDOW,    // O kernel não cria janela de terminal para o aplicativo
}appmode_t;




// PCB - Process Control Block

struct process_d 
{
    object_type_t  objectType;
    object_class_t objectClass;

    int used;
    int magic;

    int personality;
    
    int exit_in_progress;

    process_type_t type;

// #todo
// Usage, in percentage.
// How much this process is using the shared system resources.

    //int memory_usage_in_percentage;
    //int cpu_usage_in_percentage;
    //int disk_usage_in_percentage;
    //int network_usage_in_percentage;


// Other process can't take some actions on this process 
// if it is protected. ex: It can't be killed by another process.
    int _protected;

// Open files.
    unsigned long Objects[64];

// PID, (Process Identification), 
// PPID, (Parent Process Identification),
// UID, (User Identification),
// GID, (Group Identification),

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

    //process group.
    int pgrp;

// State.
// flag ?
    process_state_t state; 


// Plano de execuçao.
// Processes:
// Os processos BATCH são BACKGROUND.
// Os processos GWS são FOREGROUND.

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

// #test
// Assim fica mais facil enviar para o aplicativo.
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

// Essa é a tty do processo.
// Ela será master se o processo for um shell e
// Será slave se o processo for um terminal.
// O terminal(slave) encontrará o shell(master) em tty->link.

    struct tty_d  *tty;

// Um buffer no app en ring3
// onde o driver de rede pode colocar conte�do e depois
// avisar o processo via mensagem.

    char *net_buffer;

// Importante:
// isso substituir� a flag 'terminal'
// APPMODE_TERMINAL = O kernel cria uma estrutura de terminal 
// com uma janela associada a essa estrutura, essa janela ser� a 
// janela de terminal para o aplicativo.
// APPMODE_WINDOW = O kernel n�o cria estrutura de terminal para 
// esse processo e o processo criar� janelas.

    appmode_t appMode;

// Banco de dados
// #??
// This is a work in progress.
// Memory management.
// Obs: 
// Um processo � um cliente de banco de dados.
// Um processo tem contas conjuntas e pessoais.
// Um processo poder� compartilhar esses objetos.

// BANCOS:
// Acesso ao banco de dados do kernel. (n�o � uma lista).
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

// Process Page Table. (PPT)
// Quais s�o as p�ginas que o processo est� usando e onde elas est�o.
// na tabela tem que ter: O n�mero da p�gina. onde ela est�, se no disco ou se na mem�ria
// qual � o n�mero do pageframe da p�gina e qual o status de modifica��o
// Bom, acho que pra isso, o processo deve trabalhar em um n�mero limitado de pagetables
// pois o n�mero do frame deve ser o �ndice da pte dentro da page table.
// Uma pagetable tem 1024 entradas, garantindo um n�mero de 1024 frames, o que d� 4MB.
// Mas se um processo tiver mais que 4MB? Ent�o o diret�rio de p�ginas do processo
// ter� que ter mais de uma page table.
// Obs: 
// O kernel deve manter uma lista de frames que podem ser usados.
// na hora de criar uma pagetable pra um page directory de um processo
// � necess�rio pegar na lista de frames 1024 frames livres ou quanto for necess�rio.
// IMPORTANTE
// Uma lista de framepool. (Lista de parti��es de mem�ria f�sica).
// Cada framepool � composto de 1024 frames.
// Obs: IMPORTANTE: Quando um processo � criado, pelo menos um framepool 
// deve ser atribu�do a ele, mesmo antes de mapear os frames desse 
// framepool em alguma pagetable do page directory do processo.

// See: 
// mm/x64mm.h

    struct frame_pool_d *framepoolListHead;


// Quantidade de mem�ria f�sica usada pelo processo que n�o pode ser compartilhada
// com outros processos. (em KB).
    unsigned long private_memory_size;

// Quantidade de mem�ria f�sica usada pelo processo que pode ser compartilhada
// com outros processos. (em KB).
    unsigned long shared_memory_size;

// Quantidade de mem�ria usada por um processo em determinado espa�o de tempo.
// workset = (private + shared);
    unsigned long workingset_size;
    unsigned long workingset_peak_size;

// Qualquer pagefault deve ser registrada na estrutura do processo corrente.
// ?? n�o seria na thread ??
    unsigned long pagefaultCount;

	//...

    // ticks
    // jiffies.
    // Soma dos ticks de todas as suas threads.
    //unsigned long steps;

// quantas vezes no total o dispacher atuou sobre ele.
// Essa contagem n�o deve ser feita na thread.
// Ou colocaremos aqui o total de todos os context switches das threads?
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

// #todo
// Precisamos rever esses nomes e criar nomes
// que reflitam com propriedade os endereços usados pela imagem do processo.
// >> E se o processo estiver usando mais que uma imagem?
 
    unsigned long Image;        // VA?
    unsigned long ImagePA;      // PA
    unsigned long ImageSize;    // ?? in bytes ??
    //unsigned long ImageSizeInBytes;
    //unsigned long ImageSizeInKB;
    unsigned long PagesPerImage; 

// Usado durante fork().
// Essas variáveis são usadas para facilitar a rotina 
// de clonagem de processo.
// Talvez isso seja provisório.

    unsigned long childImage; 
    unsigned long childImage_PA; 
    unsigned long childStack; 
    unsigned long childStackPA; 


// #todo: 
// Estrutura com informações sobre a imagem do processo.
// See: image.h
// #bugbug
// O problema é que tem processo que tem mais de uma imagem.
// Como é caso do processo kernel, que tem KERNEL.BIN e GWSSRV.BIN.
// #obs: A segunda imagem do kernel é considerada um módulo.

    struct image_info_d  *image_info;

//#test
    //struct page_control_t *page_list_head;

// =================================
// Heap
// #important
// Isso é endereço virtual, 
// usado o espaço de endereçamento do kernel.

    unsigned long HeapStart;      // Início do heap.
    unsigned long HeapEnd;        // Fim do heap.
    unsigned long HeapSize;       // Tamanho do heap.
    unsigned long HeapPointer;    // Ponteiro do heap do processo para o pr�xima aloca��o.
    unsigned long HeapLastValid;  // ultimo ponteiro v�lido.
    unsigned long HeapLastSize;   // ultimo tamanho alocado..
    //struct heap_d *processHeap; // @todo: Usar essa estrutura.

// =================================
// Stack
// #important
// Isso é endereço virtual, 
// usado o espaço de endereçamento do kernel.
// Lembrando que a pilha é invertida. Que o início da pilha
// fica no endereço mais alto e o fim fica no endereço mais baixo.

// #bugbug
// Precisamos rever cuidadosamente os endereços usados
// pela stack dos processos.
// Lembrando que o processo kernel tem mais de uma imagem?

// The stack for the process.
// Maybe it needs to reflect only the control thread.

    unsigned long StackStart;  // Início da stack.
    unsigned long StackEnd;    // Fim da stack;
    unsigned long StackSize;   // Tamanho da stack.

// Deslocamento da stack em relação ao início do kernel.
    unsigned long StackOffset;

// Teste: 
// Blocos de memoria usados pelo processo.
// Lista de ponteiros de estruturas do tipo mmblock_d.
    //unsigned long mmblockList[32];

// ??
// Muitas informaçoes sobre a meméria 
// usada pro um processo.
    //struct process_memory_info_d *processMemoryInfo;

//
// Environment.
//

    unsigned int cpl;

// #todo: use 'unsigned int'
// IOPL of the task. (ring).
    unsigned int rflags_iopl; 


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

// Que tipo de scheduler o processo utiliza. 
// (rr, realtime ...).
    //int scheduler_type;    

// syscalls counter.
    unsigned long syscalls_counter;

//
// Timer
//

// Temporização da tarefa. 
    unsigned long step;             // Quantas vezes a tarefa usou o processador. 
    unsigned long quantum;          // thread quantum
    unsigned long timeout;          // Tempo em modo de espera. 
    unsigned long ticks_remaining;  // rt, quanto tempo a tarefa tem dispon�vel para ser concluida.

// As threads do processo iniciam com esse quantum.
    //unsigned long ThreadQuantum;

// QUANTUM:
// Quantum é a cota atrituida � cada processo pelo
// scheduler. (time slice) 
// Esse é o tempo limite imposto pelo scheduler para
// execuçao de um processo. Ocorre ent�o uma preemp��o por tempo.
// 'ProcessingTime' é atribu�do pelo processo. � o quanto
// ele precisa. o quanto ele deseja.


//
// Working set support.
//

	//unsigned long ws_number_of_frames; 
	//...

// profiler
// quanto por cento do tempo o processo ficou rodando.
// é a soma do quanto ficou rodando todas as suas threads.

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


// ==============
// #todo: The thread list.

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

// ==============

// event: 
// Tipo de evento que fazem a tarefa entrar em modo de espera. 

    //event_type_t event;

//
// == Security ============================
//

// User session, room (window station), desktop.

    struct usession_d  *usession;  //user session
    struct room_d      *room;      //room (Window Station) do processo.  
    struct desktop_d   *desktop;   //Desktop do processo.        

// ============================================

// ORDEM: 
// O que segue eh referenciado com pouca frequencia.

// Ponteiros para as streams do fluxo padrão
// stdin, stdout, stderr.
// For now, all the processes are using the same 
// standard stream. The same three files.

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

// The search paths for a process.
// It's a list of pointer to strings.
// Each string has a path for a different directory.
// #bugbug: I don't wanna see a double pointer here.

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

// Número de processos filhos.
    int nchildren;

// Lista de processos filhos que estao no estado zumbi.
// List of terminated childs
    struct process_d  *zombieChildListHead;

//
// IPC - Inter-Process Communication.
//

// Signal
// See: include/lib/signal.h

    unsigned long signal;
    unsigned long umask;
    //struct sigaction sigaction[32];

// ??
// Tempo para o proximo alarme, dado em ticks.
    unsigned long alarm;

// Critical section;
// Devemos checar isso quando um processo terminar,
// para que ele não fique em sua sessão crítica 
// evitando que outros possam entrar.
// #bugbug: Talvez isso deva pertencer à 
// estrutura de threads.

    int _critical;

// Quando um processo só pode receber mensagens de um 
// determinado processo. Ou de qualquer um.
// Ex: ANY=-1, PID ...
    // pid_t receive_from_pid;

// diálogo com o processo.
// importante no caso de servidores e drivers
// é como um procedimento de janelas.

    unsigned long dialog_address;


//
// == Socket ================================== 
//

// Opaque
// O socket privado do processo.
// Vamos colocar aqui a estrutura de socket.
    void *priv;
    //void *private_socket;

// list of sockets to accept connection.
    //int accept[5];
    //file *file_accept;   //aceitando através de ponteiro de arquivo.

// #todo
// Precisamos de uma lista de conexoes pendentes.
// O cliente invocou a conexao apenas uma vez
// e precisa uasr o servidor varias vezes
 
// Lista de ponteiros para estruturas de sockets.
// max =  32 cliente com conexoes pendentes.
// See: rtl/net/gdef.h
// See: rtl/net/socket.h

// Motivo do processo fechar.
    int exit_code;

    struct process_d  *prev;
    struct process_d  *next;
};

struct process_d  *KernelProcess;  // Base kernel.
struct process_d  *InitProcess;    // Init process.


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


void set_current_process( pid_t pid );
pid_t get_current_process(void);


//==============
// clone.c

int 
copy_process_struct(
    struct process_d *p1,
    struct process_d *p2 );

pid_t copy_process ( const char *filename, pid_t pid, unsigned long clone_flags );

//==============
// plib.c
void show_currentprocess_info (void);
void show_process_information (void);

int GetCurrentPID (void);
struct process_d *GetCurrentProcess(void);

//helper
unsigned long GetProcessStats ( int pid, int index );

int getprocessname ( int pid, char *buffer );
struct process_d *processObject (void);
pid_t getNewPID (void);
int processTesting (int pid);
int processSendSignal (struct process_d *p, unsigned long signal);
void init_processes (void);
void CloseAllProcesses (void);

// ===

// Worker for create_process.
void ps_initialize_process_common_elements( struct process_d *p );
    
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
    int personality );

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

int alloc_memory_for_image_and_stack ( struct process_d *process );

// Critical section
#define __GATE_CLOSED    0
#define __GATE_OPEN      1
void process_close_gate(int pid);   //227 close
void process_open_gate(int pid);    //228 open

file *process_get_file_from_pid ( pid_t pid, int fd );
file *process_get_file ( int fd );

int process_get_tty (int pid);

// Create and initialize a process structure.
struct process_d *create_and_initialize_process_object(void);


#endif    


















