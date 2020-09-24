/*
 * File: thread.h
 *
 *    Thread support.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2018 - Revision.
 */


#define THREAD_MAGIC  1234



//O primeiro índice na contagem das threads do sistema e o
//primeiro índice na contagem das threads dos usuários.
#define SYSTEM_BASE_TID  0  
#define USER_BASE_TID    100  


//
// Preempt support.
//

//?? Se pode ou não entrar em preempção. 
#define PREEMPTABLE    1    //PODE ENTRAR
#define UNPREEMPTABLE  0    //NAO PODE ENTRAR EM PREEMPÇÃO


// ??
// #bugbug: rever isso!
// Identificadores de thread.
#define IDLE_ID        0 
#define IDLE           IDLE_ID 
#define THREAD_IDLE    IDLE_ID  
// ... 


 
/*
 * Globais.
 */ 
 
 
 
/*
 * Estruturas para threads.
 */


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

	//continua... @todo
}thread_wait_reason_t;




/*
 * thread_type_t:
 *     Enumerando os tipos de threads:
 *
 *   idle     - Threads do tipo idle.     
 *   rr       - Threads do tipo round robin.
 *   periodic - Threads do tipo periódicas. 
 *   system   - Threads do tipo system.
 *   ...
 *
 * Ordem de implantação:
 * ====================
 *     (De acordo com a ordem de construção de um sistema).
 *
 *    TYPE_NULL     0
 *    TYPE_SYSTEM   1  // Fundamentais para o funcionamento do sistema.  
 *                     // Primeiras tarefas rodando quando o O.S. está sendo criado.
 *                    
 *    TYPE_IDLE     2  // Exclusivo para Threads do tipo idle. 
 *                     // ( Vários tipos de rotinas podem ser realizadas durante o período
 *                     // que o processador estiver ocioso. O usuário pode configurar
 *                     // o que o sistema deve fazer nesses momentos de ociosidade).
 *
 *    TYPE_PERIODIC 3  // Tarefas periódicas. 
 *                     // (Rodam de tempos em tempos, como o deadthread collector).
 *
 *    TYPE_RR       4  // Threads tipo round robin. 
 *                     //(Confinadas em um processador, Não importa a prioridade, nem o deadline).
 *
 *    TYPE_REALTIME 5  // Realtime + round robin. 
 *                     // (Confinadas em um processador, Importa a prioridade o dead line, o step
 *                     //  principalmente é sistemicamente importante que se cumpra a execução em tempo.) 
 *
 *    TYPE_UI       6  // UI user interface thread @todo:
 * 
 *    TYPE_IO       7  // i/o thread @todo
 *
 *    Continua ...
 */
 
typedef enum {

	TYPE_NULL,
	TYPE_SYSTEM,     // first-come-first-served.
	TYPE_IDLE,       // 
	TYPE_PERIODIC,   // periodic threads with predefined intervals.
	TYPE_RR,         // first-come-first-served cooperative.
	TYPE_REALTIME,
	//TYPE_UI, //@todo
	//TYPE_IO, //@todo
	//...

}thread_type_t;


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
 *  DEAD,	        //Earth, Deleted.	
 
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
 
typedef enum {

	INITIALIZED,    //0 Earth, Criado o contexto e parâmetros.
	STANDBY,        //1 Earth, Pronta para rodar pela primeira vez. Ir para o 'espaço'.
	ZOMBIE,         //2 Earth, Terminou a execução. Voltou para a 'terra'.
	DEAD,           //3 Earth, Deleted.
	READY,          //4 Space, Thread is ready to run again.
	RUNNING,        //5 Space, Thread is currently running.
	WAITING,        //6 Space, Thread is waiting.
	BLOCKED,        //7 Space, Thread is blocked by an event.

}thread_state_t;


/*
 ***********************************************************
 * thread_d: 
 *
 *    TCB - Thread Control Block.
 *    In the end of the struct we find the elements 
 *    not frequently used.
 */

struct thread_d 
{
    // Object control.
    object_type_t  objectType;
    object_class_t objectClass;
    struct object_d *object;

    int used;
    int magic;

    // Other process can't take some actions on this thread
    // if it is protected. ex: It can't be killed by another process.
    int _protected;


    //
    // Identifiers
    //

    // Thread id and owner process id.

    int tid;

    // Owner process.    
    struct process_d *process; 
    int ownerPID;


    // type: 
    // Tipo de tarefa.
    // (SYSTEM, PERIODIC, RR, IDLE).
    thread_type_t type;

    //flag, Estado atual da tarefa. ( RUNNING, DEAD ...).
    thread_state_t state;    


	// flag. 
	// 1 = Sinaliza que a thread está dando a preferência
	// e que deve sair quando for seguro fazer isso.
    int _yield;


	// error. @todo:
	//unsigned long error;
	
	//ext.

    //plano de execução.
    int plane;

	//
	// Names
	//

    //char *name;  //@todo: Usar isso.
    unsigned long name_address;
    unsigned long name_pointer; 
    char short_name[4];
    char *cmd;

    //#test
    //Assim fica mais fácil enviar para o aplicativo.
    char __threadname[64];    // HOSTNAME_BUFFER_SIZE
    size_t threadName_len;    // len 


    //
    // == CPU =========================================
    //

    // What processor the thread is running.
    int cpu;
    
    // What will be the next processor for this thread.
    int next_cpu;
    
    // Processor affinity.
    // See: https://en.wikipedia.org/wiki/Processor_affinity
    int affinity;


	//
	// ORDEM: 
	// O que segue é referenciado durante a interrupção de timer.
	//

	
	//...
	
	//
	// ORDEM: 
	// O que segue é referenciado durante o processo de task switch.
	//
	

	//
	// == Directory =======================================
	//

    // COLOCAR O DIRETÓRIO DE PÁGINAS QUE A THREAD USA, 
    // ISSO AJUDA NA HORA DO TASKSWITCH.

    unsigned long DirectoryPA;


    // ring.
    unsigned long iopl;
    unsigned long PreviousMode;


	// Context. 
	// #todo: 
	// Usars uma estrutura.
	// #todo: 
	// Isso deve virar um ponteiro de estrutura.

	//stack frame;
    unsigned short ss;
    unsigned long  esp;
    unsigned long  eflags;
    unsigned short cs;
    unsigned long  eip;    //usado com o pd do processo


	// para o kernel saltar para o novo processo.
    unsigned long ring0_eip;  //usado com o pd do kernel
    unsigned long eipPA;

    unsigned short ds;
    unsigned short es;
    unsigned short fs;
    unsigned short gs;

    unsigned long eax;
    unsigned long ebx;
    unsigned long ecx;
    unsigned long edx;
    unsigned long esi;
    unsigned long edi;
    unsigned long ebp;
	//continua o contexto ...

	//O endereço incial, para controle.
    unsigned long initial_eip;

	//#todo
	//isso é muito necessário.
    struct i386tss_d *tss;

	//
	// ORDEM: 
	// O que segue é referenciado durante o processo de scheduler.
	//


    //
    // == Priorities ==================================================
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
    //

    unsigned long base_priority;  // static 
    unsigned long priority;       // dinamic


    // preempted:
    // flag ~ Sinaliza que uma tarefa pode ou não sofrer preempção.
    // Uma tarefa de menor prioridade pode deixar o estado running 
    // para assumir o estado ready em favor de uma tarefa de maior prioridade
    // que assumirá o estado running.
    // todo: isso pode ser int, bool ou char.

    unsigned long preempted;


	//
	// ORDEM: 
	// O que segue é referenciado durante o processo de dispatch.
	//

	/*
	 * save 
	 * Sinaliza que a tarefa teve o seu contexto salvo.
	 * #todo: 
	 * Isso pode ser int, bool ou char.
	 */

    unsigned long saved;


    //
    //  == Heap ==========================================
    //

    unsigned long Heap;
    unsigned long HeapSize;

    //todo: Usar a estrutura. 
    //struct heap_d *heap;

    //
    //  == Stack ==========================================
    //

    unsigned long Stack;
    unsigned long StackSize;


	//Endereço de um array contendo ponteiros para variso serviços
	//que a thread pode usar.
	//unsigned long ServiceTable;

    //
    // == Time ===================================
    //

    //
    // #todo: 
    // Ticks and Deadline.
    //

	// Quanto tempo passou, mesmo quando a tarefa não esteve rodando.
	// Quando tempo a tarefa tem para que ela complete a sua execução.
	//
	//unsigned long Ticks;
    //unsigned long DeadLine.

    // step: 
    // Quantas vezes ela já rodou no total.
    unsigned long step; 

	// sys time inicial da thread.
	// quando ela foi criada.
    unsigned long initial_time_ms;
	
	//ms total..
    unsigned long total_time_ms; 
	
	
	//Quantum. (time-slice, igual cota) 
    unsigned long quantum;         //tempo que a thread tem.
    unsigned long quantum_limit;   //limite quando dado boost. tempo limite rodando. 		
	
	//unsigned long  RemainingTime;  //??
	
    unsigned long standbyCount;

    // runningCount: 
    // Quanto tempo ela está rodando antes de parar.
    unsigned long runningCount; 

	//ms rodando antes de parar.
    unsigned long runningCount_ms; 

	//Obs: A soma das 3 esperas é a soma do tempo de espera
	//depois que ela rodou pela primeira vez.
	
    //Contando o tempo nos estados de espera.
    unsigned long readyCount;   //tempo de espera para retomar a execução.
    unsigned long ready_limit;

    //Esperando por eventos.
    unsigned long waitingCount; //tempo esperando algo.	
    unsigned long waiting_limit;   //tempo limite que uma tarefa ready fica sem rodar.
    
    unsigned long blockedCount;
    unsigned long blocked_limit;

    //Ticks remaining. (tempo para a tarefa chegar ao fim, tempo total-tempo percorrito)
    unsigned long ticks_remaining; //rt, quanto tempo a tarefa tem disponível para ser concluida.


    //
    // == Profiler ==================================
    //


    //quanto por cento do tempo o processo ficou rodando.
    //é a soma do quanto ficou rodando todas as suas threads.
    unsigned long profiler_percentage_running;
    unsigned long profiler_percentage_running_res;
    unsigned long profiler_percentage_running_mod;
    unsigned long profiler_ticks_running;
    unsigned long profiler_last_ticks;


    //Tempo para o próximo alarme, dado em ticks.
    //unsigned long alarm; 


	//
	// ORDEM: 
	// O que segue é referenciado com pouca frequencia.
	//
	
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
	//
	//struct _iobuf *root;  // 4 root directory
    //struct _iobuf *pwd;     // 5 (print working directory) 
	//...
		
	
	//@todo: Uma thread pode estar esperando varias outras por motivos diferenes.
	//struct wait_d WaitBlock;
	
	
	//
	// tty support
	//

    // ID da tty usada.
    int tty_id;


    // #importante
    // Isso é usado para gerência de memória e ... 
    
    //struct usession_d *usession;  //#todo
    struct room_d     *room;        // (Window Station) da thread.
    struct desktop_d  *desktop;     // Desktop da thread.


    // ?? procedimento de janela.
    unsigned long procedure; //Endereço do procedimento de janela da tarefa. 
	//unsigned long control_menu_procedure; //procedimento do control menu.

	
	// #ORDEM: 
	// O que segue é referenciado durante as trocas de mensagens.
	// utilização de canais e IPC.

    //
    // Single system message.
    //

    // 4 argumentos padrão;
    struct window_d *window;    //arg1.
    int msg;                    //arg2.
    unsigned long long1;        //arg3.
    unsigned long long2;        //arg4.
    // Flag avisando que tem nova mensagem.
    int newmessageFlag;         



    //
    // Queue. (list)
    //

    // #todo
    // Essas longs extras podem ajudar ...
    // Por exemplo: O mouse pode mandar um pacote com 3 longs
    // para o ws em ring3.
    // Mas ser'a que a system call consegue pegar todos esses argumentos ???
    
    struct window_d *window_list[32];
    int msg_list[32];
    unsigned long long1_list[32];
    unsigned long long2_list[32];
    unsigned long long3_list[32];
    unsigned long long4_list[32];
    int tail_pos;
    int head_pos;

    // Vamos alocar um buffer do tamanho de uma pagina.
    // Se esse buffer estiver no espaço de memmoria
    // do processo, entao o processo podera ler, sem precisar copiar
    // mas copiar n~ao seir uma problema.
    
    //void *msg_buffer;


    //
    // Message Queue
    //

    // Coloca-se em tail, quande chegar ao fim do buffer, recomeça.
    // Se o tail encontrar o head é porque o processo não está 
    // respondendo.
    unsigned long MsgQueue[32];
    int MsgQueueHead;  //retira. 
    int MsgQueueTail;  //coloca.



    // Quando um processo só pode receber mensagens de um 
    // determinado processo. Ou de qualquer um.
    // Ex: ANY=-1, PID ...
    // pid_t receive_from_pid;



	//?? mensagens pendentes.
	//struct thread_d *sendersList; //Lista encadeada de threads querendo enviar mensagem
	//struct thread_d *nextSender;  //próxima thread a enviar mensagem.
	


    //
    // == Wait ======================================
    //

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
	// 3 - esperando um objeto. (espera genérica)
	// ...

    int wait_reason[10]; 

    int wait4pid;   //id do processo que a thread está esperando morrer.
    int wait4tid;   //id da thread que a thread está esperando morrer.

	// Objeto pelo qual a thread está esperando.
	// #todo: mudar esses nomes, pode confundir com o header no início da 
	// estrutura. (waiting_object_type ...  woType woClass )
    object_type_t   woType;   //obType;   //woType
    object_class_t  woClass;  //obClass;  //woClass


    //
    // == Signal ======================================
    //
    
    unsigned long signal;
    unsigned long umask;

    //
    // == Exit ======================================
    //

    //Motivo da thread fechar.
    int exit_code;

    // Navigation

    struct thread_d *prev;
    struct thread_d *next;
};



// Ponteiro para a idle thread atual
// Sempre que mudar a idle thread devemos usar esse ponteiro
// para mostrar qual será a nova idle thread.
// Cada idle thread pode prestar um serviço diferente, como o
// gerenciamento de energia.
struct thread_d *____IDLE;


// Essa é a criada para o processo kernel.
// Ela roda em ring0 e será usada como idle.
// RING0 IDLE Thread. TID=3
struct thread_d *RING0IDLEThread;    


// Essa é a thread de controle do processo init2.bin
// É o primeiro processo em ring3.
// Idle Thread. TID=0
struct thread_d *InitThread;         


// Ponteiro para a thread usada na hora da clonagem de processos.
struct thread_d *ClonedThread;





/* 
 * Listas encadeadas de threads.
 * Usadas no gerenciamento de rounds 
 */

// The fixed conductor to mark the start.
struct thread_d *Conductor;
// The flexible conductor to create the list.
struct thread_d *tmpConductor;  //Conductor2;
// The created root conductor.
struct thread_d *rootConductor;

int conductorIndex;



// #todo
// Podemos planejar o uso de listas nesse formato.
// Mas estamos trabalhando em filas de tamanho fixo no formato de array.
//struct thread_d *blocked_list_head;
//struct thread_d *waiting_list_head;
//struct thread_d *ready_list_head;




/*
 * threadList:
 * 
 */

// #Atenção
// Esse é a lista principal. Contém todas as threads.
 
// Número máximo de threads.
#define THREAD_COUNT_MAX 1024  

unsigned long threadList[THREAD_COUNT_MAX];



struct thread_list_d 
{
    struct thread_d *Threads;    //List.
    unsigned long priority;      //Prioridade.
    // ...
};

//struct thread_list_d *DispatcherList[10]; //list
//struct thread_list_d *DispathcerPriorityQueue[10];
//unsigned long DispatcherList[10];
//DispatcherList[2].Threads[4].tid



//clona uma thread e retorna o ponteira da clone.
struct thread_d *threadCopyThread ( struct thread_d *thread );


/* 
 ******************************
 * create_thread: 
 *    Create thread.
 */ 

struct thread_d *create_thread ( 
    struct room_d *room,
    struct desktop_d *desktop,
    struct window_d *window,
    unsigned long init_eip, 
    unsigned long init_stack, 
    int pid, 
    char *name );


void *GetCurrentThread (void);

void *FindReadyThread (void);

int GetThreadState (struct thread_d *Thread);
int GetThreadType (struct thread_d *Thread);
void dispatch_thread (struct thread_d *thread);
void set_thread_priority (struct thread_d *t, unsigned long priority);


// ## Page directory support ## 

// Pega o endereço do diretório de páginas usado pela thread.
unsigned long GetThreadDirectory( struct thread_d *thread );

// Altera o endereço do diretório de páginas de uma thread.
void SetThreadDirectory ( struct thread_d *thread, unsigned long Address );

/* Thread heap support. */
unsigned long GetThreadHeapStart (struct thread_d *thread);
//...

/*
 * Thread Stack support.
 */
unsigned long GetThreadStackStart(struct thread_d *thread);
//...

void SelectForExecution (struct thread_d *Thread);



// Show info about all threads.
void show_slots (void);

// Show info about a thread.
void show_slot(int tid);

// Show the register of the context.
void show_reg (int tid);



void show_thread_information (void); 

int init_threads (void);

int GetCurrentThreadId (void);


// Usadas durante a inicialização e execução de uma thread.
// @todo: mudar apenas o protótipo para thread.h
void spawn_thread (int id);


// ## Finalizações ##


// Liberar uma thread que estava bloqueada ou esperando.
void release ( int tid );


//Torna zumbi uma thread.
void exit_thread ( int tid );       


//Destrói uma thread.
void kill_thread (int tid);       


void dead_thread_collector (void);


void kill_all_threads (void);


int thread_getchar (void);


// se a flag estiver habilitada, então devemos acorar a
// thread do dead thread collector.
void check_for_dead_thread_collector (void);

int thread_profiler( int service );


// pegar a porcentagem de vezes que a thread rodou durante um determinado
//período.
unsigned long 
thread_get_profiler_percentage ( struct thread_d *thread);

void thread_show_profiler_info (void);


int getthreadname ( int tid, char *buffer );


unsigned long __GetThreadStats ( int tid, int index );

//
// End.
//


