
// thread.h

#ifndef __PS_THREAD_H
#define __PS_THREAD_H    1

// =================================
// System threads: (canonical)
// The first system thread is '0'. It is the ring 3 init thread.
// The first user thread is '100'.
// We're gonna give less privilegies for those threads 
// equal and above 100. 

// -----------------------------------------
// The system's thread counter starts here.
#define SYSTEM_THRESHOLD_TID  0
#define INIT_TID    SYSTEM_THRESHOLD_TID
//...

// -----------------------------------------
// The user's thread counter starts here.
#define USER_THRESHOLD_TID    100


// --------------------------------

#define THREAD_MAGIC  1234

// Stock:
// The structure can be reused.
//#define THREAD_STOCK  4321

//
// Preempt support.
//

// Se pode ou não entrar em preempção. 
#define PREEMPTABLE    TRUE   // Yes
#define UNPREEMPTABLE  FALSE  // No




// Threads:
// Entre as janelas overlapped, a que estiver ativa,
// deve mudar o plano da thread para FOREGROUND.
#define BACKGROUND_THREAD  1 
#define FOREGROUND_THREAD  2



//#importante
//razões para esperar
	//#todo: isso precisa ser inicializado.
	//@todo: tem que fazer um enum para enumerar as razões.
	//o índice é o selecionador da razão pela 
	//qual a thread está esperando.
	//existem umas 20 razões pra esperar.
	// 0 - esperando por mensagem.(presa num loop)
	// 1 - esperando outra thread finalizar. wait4tid
	// 2 - esperando um processo finalizar. wait4pid
	// 3 - esperando um objeto. (BLOCKED)(espera genérica)
	// ...

// #importante
// isso será usado na estrutura de thread em wait_reason[]
// Com limite de 10 por enquanto.

typedef enum {
	WAIT_REASON_NULL,
	WAIT_REASON_LOOP,           
	WAIT_REASON_EXIT,
	WAIT_REASON_BLOCKED,
	WAIT_REASON_PREMMPTED,      // ?? Esperando a preempção de thread de menor prio.
	WAIT_REASON_SEMAPHORE,      // ?? Semáforo.
	WAIT_REASON_WAIT4PID,       // Esperando o processo filho morrer.
	WAIT_REASON_WAIT4TID,       // Esperando uma thread morrer.
	WAIT_REASON_TEST            // # Usada pelo desenvolvedor para testes.
	// ...
}thread_wait_reason_t;



/*
 * thread_type_t:
 *     Enumerando os tipos de threads:
 */
// priority class
typedef enum {
    THREAD_TYPE_NULL,
    THREAD_TYPE_SYSTEM,       // high priority
    THREAD_TYPE_INTERACTIVE,  // medium priority (first plane)
    THREAD_TYPE_BATCH,        // low priority
}thread_type_t;



/*
This part is about input redirection ...
What is the place where i need to send the 
input that came from the hardware?
If the input model is an unix-like stuff, 
so i need to send the input to a file and 
an application will read this file.
if the input model is windows-like, 
so i will send the input to an event queue in the raw input thread.
*/

/*
 // #suspenso. Vamos usar as flags em 't->input_flags'
typedef enum {
    THREAD_INPUTMODEL_NULL,      // Not defined.
    THREAD_INPUTMODEL_KERNEL,    // Kernel thread running in ring0.
    THREAD_INPUTMODEL_COMMAND,   // Command running on console or terminal.
    THREAD_INPUTMODEL_UNIXLIKE,  // Send the input to a file.
    THREAD_INPUTMODEL_KGWS,      // Running on Setup environment and using kgws.
    THREAD_INPUTMODEL_LOADABLEWINDOWSERVER   // Using the current loadable window server.
}thread_inputmodel_t;
*/




/*
 * thread_state_t:
 *    Enumeram os estados de uma threads, (8 estados).
 *    Existem 2 grupos, 'Earth' e 'Space'.
 *    Obs: Rodam no 'espaço'.
 *
 * Earth: (INITIALIZED, STANDBY, ZOMBIE, DEAD).
 * Space: (READY, RUNNING, WAITING, BLOCKED).
 *
 *  INITIALIZED,    //Earth, Criado o contexto e parâmetros.
 *  STANDBY,        //Earth, Pronta para rodar pela primeira vez. Ir para o 'espaço'.
 *  ZOMBIE,         //Earth, Terminou a execução. Voltou para a 'terra'.
 *  DEAD,           //Earth, Deleted.
 * 
 *  READY,          //Space, Thread is ready to run again.
 *  RUNNING,        //Space, Thread is currently running.
 *  WAITING,        //Space, Thread is waiting.	
 *  BLOCKED,        //Space, Thread is blocked by an event.
 *
 * Obs: 
 *     Na prática, a troca de status está seguindo um organograma de 
 * movimentos. 
 *     @todo: Descrever esses movimentos na documentação. Incluir a 
 * visualização através do gráfico.
 */

// canonical.
typedef enum {

//0 Earth, Criado o contexto e parâmetros.
    INITIALIZED,
//1 Earth, Pronta para rodar pela primeira vez. 
//         Ir para o 'espaço'.
    STANDBY,
//2 Earth, Terminou a execução. Voltou para a 'terra'.
    ZOMBIE,
//3 Earth, Deleted.
    DEAD,

//----

//4 Space, Thread is ready to run again.
    READY,
//5 Space, Thread is currently running.
    RUNNING,
//6 Space, Thread is waiting.
    WAITING,
//7 Space, Thread is blocked by an event.
    BLOCKED,

}thread_state_t;


// Input model
// t->input_flags
// Com essa flag o kernel deve enviar input de teclado
// para stdin.
#define INPUT_MODEL_STDIN         1
// Com essa flag o kernel deve enviar input para
// a fila de mensagens na current thread.
#define INPUT_MODEL_MESSAGEQUEUE  2


// t->flags:
#define BLOCKED_SENDING      0x1000
#define BLOCKED_RECEIVING    0x2000
// ...


// --------------------------------

#define MSG_QUEUE_MAX  64

// TCB - Thread Control Block

struct thread_d 
{
    object_type_t objectType;
    object_class_t objectClass;
    int used;
    int magic;
// type:
// (SYSTEM, INTERACTIVE, BATCH)
    thread_type_t type;

// Thread ID.
    tid_t tid;

// 1000=GRAMADO 1001=GWS
    int personality;
// We are waiting the right time to close a thread.
// The scheduler will do this job.
    int exit_in_progress;

// flags:
// 1000 - Blocked when trying to send.
// 2000 - Blocked when trying to receive.
// ...

    unsigned long flags;

// Input model
// Setup the input model for this thread ...
// So the kernel will know where are the places
// to send the input when this is the current thread.
// #todo:
// NOT_RECEIVING

    unsigned long input_flags;


// #suspenso. 
// Vamos usar as flags em 't->input_flags'

    //thread_inputmodel_t input_model;

// Surface
    struct rect_d *surface_rect;

// #todo
// Other process can't take some actions on this thread
// if it is protected. 
// ex: It can't be killed by another process.

    int _protected;

//
// Identifiers
//

// Owner process
    struct process_d  *owner_process;
    pid_t owner_pid;

// ========================================================
// ORDEM: 
// O que segue é referenciado durante o processo de scheduler.

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
// The base priority is static and the current priority is dynamic.

    unsigned long base_priority;  // static 
    unsigned long priority;       // dynamic


// flag, Estado atual da tarefa. ( RUNNING, DEAD ... ).
    thread_state_t state;    

// The is the control thread of a new clone process.
    int new_clone;

// #todo
// Identifica uma thread como sendo uma thread que 
// pertence à um servidor. Então as threads desse tipo 
// ganham mais prioridade e mais tempo de processamento.

    // int isServerThread;

// flag. 
// 1 = Sinaliza que a thread está dando a preferência
// e que deve sair quando for seguro fazer isso.
    int yield_in_progress;

    int sleep_in_progress;
    unsigned long desired_sleep_ms;

    int _its_my_party_and_ill_cry_if_i_want_to;


    int waiting_for_timeout;

// error. @todo:
    //unsigned long error;


// Plano de execução.
// Threads:
// Entre as janelas overlapped, a que estiver ativa,
// deve mudar o plano da thread para FOREGROUND.

    int plane;

//
// Names
//

    //char *name;  //@todo: Usar isso.
    unsigned long name_address;
    unsigned long name_pointer; 
    char short_name[4];
    char *cmd;
    
    // #test
    // estamos usando esse aqui.
    // Assim fica mais fácil enviar para o aplicativo.
    char __threadname[64];    // HOSTNAME_BUFFER_SIZE
    size_t threadName_len;    // len 

//
// == CPU =========================================
//

// What processor the thread is running now.
    int current_processor;
// What will be the next processor for this thread.
    int next_processor;
// Processor affinity. (CPU pinning)
// The thread will execute only on the designated CPU.
// See: https://en.wikipedia.org/wiki/Processor_affinity
    int affinity_processor;

// ORDEM: 
// O que segue é referenciado durante a interrupção de timer.

    //...

// ORDEM: 
// O que segue é referenciado durante o processo de task switch.

//
// == pml4 =======================================
//

// #todo
// COLOCAR O DIRETÓRIO DE PÁGINAS QUE A THREAD USA, 
// ISSO AJUDA NA HORA DO TASKSWITCH.

// The pml4
    unsigned long pml4_VA;
    unsigned long pml4_PA;
// The first pdpt
    unsigned long pdpt0_VA;
    unsigned long pdpt0_PA;
// The first pd
    unsigned long pd0_VA;
    unsigned long pd0_PA;


// cpl
// The initial privilege level.
// The current privilege level.

    unsigned int cpl;
    unsigned int rflags_initial_iopl;
    unsigned int rflags_current_iopl;


// The thread is running in the ring0 phase
// after the isr request.
//    int in_syscall;


// Is preemptable or not.
    int is_preemptable;

// ========================================================
// ORDEM: 
// O que segue é referenciado durante o processo de dispatch.

// The context is already saved or not?
    int saved;

// Heap and Stack
// #todo: Is it a virtual address?
    unsigned long HeapStart;
    unsigned long HeapSize;
    unsigned long StackStart;
    unsigned long StackSize;

// Service table?
// Endereço de um array contendo ponteiros para varios serviços
// que a thread pode usar.
    // unsigned long ServiceTable;


// ========================================================
// ORDEM: 
// Timer stuff

//
// == Time =============================
//

// ?
// Podemos criar a estrutura 'thread_time_d' t->time.step

// stime and utime.
// Quando o timer interrompe uma thread,
// ela pode esta qualquer um dos ambientes.
// temos que incrementar conforme o ambiente que ela estava 
// quando foi interrompida
// cpl - current privilege level
// See:

    unsigned long stime;   // supervisor ticks
    unsigned long utime;   // usermode ticks.


// Quanto tempo passou, 
// mesmo quando a tarefa não esteve rodando.

    // unsigned long jiffies_alive;
    // unsigned long total_jiffies;

// step: 
// How many jiffies. 
// total_jiffies.
// Quantas vezes ela já rodou no total.
// Tempo total dado em jiffies.

// initial_jiffie: Spawn jiffie. Jiffie at spawn moment.
// ready_jiffie:   Time when the thred became ready.
// waiting_jiffie: Time when the thread started to wait.
// blocked_jiffie: Time when blocked.
// zombie_jiffie:  Time when the thread became a zombie.

    unsigned long initial_jiffy;
    unsigned long ready_jiffy;
    unsigned long waiting_jiffy;
    unsigned long blocked_jiffy;
    unsigned long zombie_jiffy;

// Time when the thread needs to wakeup.
    unsigned long wake_jiffy;

// How much jiffies until now.
    unsigned long step;

// Quando ela foi criada.
// systime inicial da thread.
// Tempo total dado em milisegundos.

    unsigned long initial_time_ms;
    unsigned long total_time_ms; 


// Credits:
// Quantum. 
// time-slice or quota. 
// Quantos jiffies a thread pode rodar em um round.
// Quantidade limite de jiffies que uma thread pode rodar em um round.
// Limite do quantum quando dado boost. 
// Ou seja, podemos aumentar o quantum de um thread até esse limite.
    unsigned long quantum;
    unsigned long quantum_limit_min;
    unsigned long quantum_limit_max;
    
// #todo: Can we boost the credits?
    //int disable_boost;

// Quantos jiffies a thread ficou no estado e espera para
// pronta para rodar.
    unsigned long standbyCount;
    unsigned long standbyCount_ms;

// Quantos jiffies ela está rodando antes de parar.
    unsigned long runningCount; 
    unsigned long runningCount_ms; 

// obs: 
// ??
// A soma das 3 esperas é a soma do tempo de espera
// depois que ela rodou pela primeira vez.

//
// Contando o tempo nos estados de espera.
//

// Tempo de espera para retomar a execução.
// Limite esperando para rodar novamente.
// Talvez essa contagem nao precise agora. 
    unsigned long readyCount;
    unsigned long readyCount_ms;
    unsigned long ready_limit;

// Quantos jiffies esperando por algum evento.
// Quantos jiffies a thread pode esperar no maximo.
    unsigned long waitingCount; 
    unsigned long waitingCount_ms; 
    unsigned long waiting_limit;

// Quantos jiffies ficou bloqueada.
// Qauntos jiffies a thread pode esperar bloqueada.
    unsigned long blockedCount;
    unsigned long blockedCount_ms;
    unsigned long blocked_limit;


// How many times it was scheduled.
    unsigned long scheduledCount;

// Zombie ?


// #todo: 
// Deadline.
// Quando tempo a tarefa tem para que ela complete a sua execução.
// unsigned long DeadLine.
// unsigned long RemainingTime; 
// Ticks remaining. (Deadline)
// Contagem do prazo limite.
// Contagem regressiva.
// Isso eh usado por threads 'real-time'
    unsigned long ticks_remaining;

// Alarm
// Used by the alarm() standard syscall.
    unsigned long alarm;

//
// == Profiler ==================================
//

// Quanto por cento do tempo a thread ficou rodando.
// No caso do processo, é a soma do quanto ficou rodando 
// todas as suas threads.

// ? these names are not good.
    unsigned long profiler_percentage_running;
    unsigned long profiler_percentage_running_res;
    unsigned long profiler_percentage_running_mod;
    unsigned long profiler_ticks_running;
    unsigned long profiler_last_ticks;

// ORDEM: 
// O que segue é referenciado com pouca frequencia.

//lista de arquivos ??
//fluxo padrão. stdio, stdout, stderr
	//unsigned long iob[8];
    
//#bugbug: o vetor Stream[] conterá essas stream também.
//ponteiros para as streams do fluxo padrão.
//O processo tem streams ... Stream[] ...
//cada tread pode ter suas stream ... mesmo que herde streams 
//de processo ...
// ?? threads diferentes do mesmo processo podem atuar em streams 
// diferentes ??
	//unsigned long standard_streams[3];
	//unsigned long Streams[8];

//Obs: Cada processo está atuando em um diretório,
// mas será cada thread precisa atuar em um diretório diferente??
    //struct _iobuf *root;  // 4 root directory
    //struct _iobuf *pwd;   // 5 (print working directory) 
    //...

//
// == tty ==========================
//

// ID da tty usada.
    int tty_id;

//
// Security
//

// #importante
// Isso é usado para gerência de memória e 
// para privilégios de acesso.

    struct usession_d *usession;  // user session.
    struct room_d     *room;      // room. A kind of 'Window Station'.
    struct desktop_d  *desktop;   // desktop.

// Callback:
// The main procedure for a ring 3 application.
// It is a callback, and the kernel will call this procedure
// right after a timer interrupt.
    //unsigned long user_procedure_va;

// #ORDEM:  
// O que segue é referenciado durante as trocas de mensagens.
// utilização de canais e IPC.

//
// LIS - Local Input State
//

// #important
// Here we have some elements to handle the input events
// in this thread.
// + We have a block for single shot event.
// + We have a block for a queue of events.
// + We have a set of variables to handle the flow.
// ...
// Keyboard input and window focus information:
// + Which window has keyboard focus?
// + Which window is active?
// + Which keys are considered pressed down?
// + The state of the caret.
// Mouse cursor management information
// + Which window has mouse capture?
// + The shape of the mouse cursor?
// + The visibility of the mouse cursor.
// ...
// #todo
// We don't need to have a window as an element in the event.
// We can include this window later when the app calls get_message().
// When the thread calls GetMessage(), 
// the keyboard event is removed from the queue and 
// assigned to the window that currently has input focus.
// #test
// Sending a message to the kernel.
// no queue.
// Flag avisando que tem nova mensagem.
// O kernel deve checar essa flag. Se ela estiver acionada,
// significa que o kernel deve processar essa mensagem.

//
// == Event queue ===========================================
//

// This is the event queue.
// It is used by the ring 3 processes.
// #todo: 
// We can put all these into a structure.
// Lists:
// window_list: pointer to window structure.
// msg_list:    event type.
// long1_list:  data 1
// long2_list:  data 2
// long3_list:  data 3
// long4_list:  data 4
// MAXEVENTS
// See: events.h

// ====================================================
// Message Queue
// For the msg_d structure,
// see: window.h
    unsigned long MsgQueue[MSG_QUEUE_MAX];
    int MsgQueueHead;
    int MsgQueueTail;
// ====================================================

// #test
// Contador de mensagens enviadas.
// Também podemos contar alguns tipos de mensagens.

    //unsigned long post_message_counter;

// Waiting for a child:
// id do processo que a thread está esperando morrer.
    int wait4pid;
// id da thread que a thread está esperando morrer.
    int wait4tid;
// Signal support:
    unsigned long signal;
    unsigned long umask;
// Exit:
// Reason to close the thread.
    int exit_code;

//
// == Context ======================= 
//

// #todo: 
// Usars uma estrutura.
// #todo: 
// Isso deve virar um ponteiro de estrutura.
// ?? O que faremos, pois temos mais de uma arquitetura.

    // struct x86_context_d  *context;

// stack frame;
    unsigned short ss;
    unsigned long  rsp;
    unsigned long  rflags;
    unsigned short cs;
    unsigned long  rip;    //usado com o pd do processo?

// para o kernel saltar para o novo processo.
    unsigned long ring0_rip;  //usado com o pd do kernel?
    unsigned long ripPA;

    unsigned short ds;
    unsigned short es;
    unsigned short fs;
    unsigned short gs;

    unsigned long rax;
    unsigned long rbx;
    unsigned long rcx;
    unsigned long rdx;
    unsigned long rsi;
    unsigned long rdi;
    unsigned long rbp;
    
    unsigned long r8;
    unsigned long r9;
    unsigned long r10;
    unsigned long r11;
    unsigned long r12;
    unsigned long r13;
    unsigned long r14;
    unsigned long r15;

//continua o contexto ...

//O endereço incial, para controle.
    unsigned long initial_rip;

// #todo
// 512 bytes, alinhados em 16.
// unsigned char fxsave[512]__atribute_aligned(...);
    unsigned char fpu_buffer[512];

//
//  tss
//

// #todo
// isso é muito necessário.
// #todo: Create the structure.
    //struct x64tss_d *tss;

// Navigation
    struct thread_d *prev;
    struct thread_d *next;
};

// See: thread.c
extern struct thread_d  *InitThread;
extern struct thread_d  *ClonedThread;
// Linked lists
// See: sched.c
extern struct thread_d  *Conductor;
extern struct thread_d  *tmpConductor;


extern struct thread_d *timeout_thread;


// Maximum number of kernel threads in the system.
#define THREAD_COUNT_MAX  1024 
//#define THREAD_COUNT_MAX  4096

// Cada lista poderá usasr uma prioridadr diferente,
// um quantum diferente e talvez ter uma frequencia de timer diferente.

// All the threads
// see: thread.c
extern unsigned long threadList[THREAD_COUNT_MAX];
// Threads doing some kind of i/o operations.
//unsigned long io_threadList[THREAD_COUNT_MAX];
// Interactive threads.
// Just like keyboard and windows with focus.
//unsigned long interactive_threadList[THREAD_COUNT_MAX];


//
// == prototypes ===========================
//

// Service 111.
// Get a message from the current thread and 
// put it into the given buffer.
// The message has 6 standard elements.
// See: thread.c

void *sys_get_message(unsigned long ubuf);
void *sys_get_message2(unsigned long ubuf, int index, int restart);

int init_threads(void);

// See: main.c
void early_ring0_IdleThread(void);

// Create the init thread.
// This is the first thread ever.
// See: create.c

struct thread_d *create_init_thread(void); 

// From thread.c

// helper
unsigned long GetThreadStats( int tid, int index );

int getthreadname ( int tid, char *buffer );
void *FindReadyThread (void);
int GetThreadState (struct thread_d *thread);
int GetThreadType (struct thread_d *thread);

int GetCurrentTID(void);

void *GetThreadByTID (int tid);
void *GetCurrentThread(void);
void *GetForegroundThread(void);
void *GetWSThread(void);

// From threadi.c
void show_slot(int tid);
void show_slots(void);
void show_reg(int tid);

void 
set_thread_priority ( 
    struct thread_d *t, 
    unsigned long priority );
    
void threadi_power(
    struct thread_d *t, 
    unsigned long priority );

void release(tid_t tid);

void SelectForExecution ( struct thread_d *Thread );

unsigned long 
thread_get_profiler_percentage (struct thread_d *thread);

void show_thread_information (void);

void thread_show_profiler_info(void);
int thread_profiler(int service);

//
// Creation
//

struct thread_d *copy_thread_struct (struct thread_d *thread);

struct thread_d *create_thread ( 
    struct room_d     *room,
    struct desktop_d  *desktop,
    struct window_d   *window,
    unsigned long init_rip, 
    unsigned long init_stack, 
    pid_t pid, 
    char *name,
    unsigned int cpl,
    int personality );

// =====

//
// Exit
//

void exit_thread(int tid);
void exit_current_thread(void);

// ===

void 
SetThread_PML4PA ( 
    struct thread_d *thread, 
    unsigned long pa );

void check_for_dead_thread_collector (void);
void dead_thread_collector (void);

void kill_thread(tid_t tid);
void kill_all_threads(void);
void kill_zombie_threads(void);

// ==

// The spawn routine need to make a eoi.
void spawn_set_eoi_state(void);
// The spawn routine do not need to make a eoi.
void spawn_reset_eoi_state(void);

void 
spawn_enter_usermode( 
    int eoi, 
    unsigned long entry_va, 
    unsigned long rsp3_va );

void 
spawn_enter_kernelmode( 
    int eoi, 
    unsigned long entry_va,
    unsigned long rsp0_va );

void spawn_thread (int tid);
void KiSpawnThread (int tid);

void spawn_pid(pid_t pid);
void spawn_tid(int tid);

int 
gramado_post( 
    tid_t sender_tid,
    tid_t receiver_tid,
    struct msg_d *message );

int
post_message_to_tid ( 
    tid_t sender_tid,
    tid_t receiver_tid, 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );

int
post_message_to_ws( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );

int
post_message_to_foreground_thread ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );

// service 112
unsigned long
sys_post_message_to_tid( 
    int tid, 
    unsigned long message_buffer );

#endif    























