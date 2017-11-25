/*
 * Frile: process.h
 *
 * Descrição:
 *     Header principal para as rotinas de gerenciamento de processos.
 *
 * Classes de processos (tipo de nível):
 * ====================================
 *    PB - Processos incluídos no Kernel Base.
 *    P0 - Processos em ring0.
 *    P1 - Processos em ring1.
 *    P2 - Processos em ring2.
 *    P3 - Processos em ring3, User Mode.
 *
 *
 * @todo: Taskman e outros programas gerenciadores de tarefas precisam de informações
 * sobre os processos. A barra de tarefas também precisa.
 * @todo: Contagem de processos.
 * @todo: Contar a quantidade de objetos alocados para um processo.
 *        contar a quantidade de objetos por classe de objetos.
 *        Saber a classe dos objetos alocados é importante, pois isso
 *        oferece informações sobre o comportamento do processo. 
 * @todo: Fazer contagem de faltas de página.
 * @todo: suporte a workset.(quantidade de memória numa faixa de tempo.)
 * +em qual cpi o processo está.?
 * + com qual cpu o processo tem afinidade?.
 * + o processo está confinado ou não.?
 * +prioridade básica e atual?
 * medir quantidade de operações de leitura e saída.
 * +name, pathname e cmd(command line).
 *
 * Histórico:
 *     Versão: 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *     Versão: 1.0, 2016 - Aprimoramento geral das rotinas básicas.
 *     ...
 */


typedef int pid_t; 
typedef int ppid_t;
 
//
//#define FIRST_PROCESS processList[0]
//#define LAST_PROCESS  processList[PROCESS_COUNT_MAX-1] 

 
//
// Endereços virtuais usados pelos processos.
//


// Image. 
// (Base da imagem de um processo de usuário).
//
// "Todo processo terá seu próprio diretório de páginas
//  e será carregado no endereço virtual 0x400000, logicamente
//  cada processo será carregado em um endereço físico diferente."
// 
#define UPROCESS_IMAGE_BASE 0x400000 

//Process Limit. (User process) 
//(O limite é o início do kernel).
#define UPROCESS_PROCESS_LIMIT 0xC0000000    



// Heap.
// Base default do heap do processo.
// "Endereço virtual de onde começa o heap de um processo,
//  evidentemente, cada processo terá seu heap em um 
//  endereço físico diferente".
//
#define UPROCESS_DEFAULT_HEAP_BASE  0x80000000 
//Tamanho default do heap do processo.  
#define UPROCESS_DEFAULT_HEAP_SIZE  0x2000     

//Stack.
//Deslocamento default do início da pilha em relação ao início do kernel.
#define UPROCESS_DEFAULT_STACK_OFFSET 0x2000   
//Base default da pilha do processo.
#define UPROCESS_DEFAULT_STACK_BASE ( UPROCESS_PROCESS_LIMIT - UPROCESS_DEFAULT_STACK_OFFSET )  
//Tamanho da pilha do processo.   
#define UPROCESS_DEFAULT_STACK_SIZE 0x2000    
 
 
//Limite para criação de processos. 
#define PROCESS_COUNT_MAX 256 
 
//
// Bases para a contagem de processos, do sistema e de usuários.
// 
 
//Primeiro índice na contagem das processos do sistema.
#define SYSTEM_BASE_PID 0
//Primeiro índice na contagem das processos dos usuários.  
#define USER_BASE_PID 100    
 
 
/*
 * Constantes para níveis de prioridade.
 */
 
//Definições principais. 
#define PRIORITY_LOW4      1  //4
#define PRIORITY_LOW3      2  //3
#define PRIORITY_LOW2      3  //2
#define PRIORITY_LOW1      4  //1 
#define PRIORITY_NORMAL    5  //*0 (Normal).
#define PRIORITY_HIGH1     6  //1
#define PRIORITY_HIGH2     7  //2
#define PRIORITY_HIGH3     8  //3
#define PRIORITY_HIGH4     9  //4
//Definições secundárias.
#define PRIORITY_LOW        PRIORITY_LOW1
#define PRIORITY_SUPERLOW   PRIORITY_LOW4
#define PRIORITY_MIN        PRIORITY_SUPERLOW
#define PRIORITY_HIGH       PRIORITY_HIGH1 
#define PRIORITY_SUPERHIGH  PRIORITY_HIGH4
#define PRIORITY_MAX        PRIORITY_SUPERHIGH    
//Definição especial.
#define PRIORITY_REALTIME  10    



/*
 * Constantes para níveis de quantum.
 * Tempo de processamento atribuido pelo scheduler à cada processo.
 */
#define QUANTUM_BASE  10
#define QUANTUM_LIMIT 19


//Limite de tempo esperando.
#define READY_LIMIT 19
#define WAITING_LIMIT 19
#define BLOCKED_LIMIT 19
 
//Lista de status na criação de um processo.     
#define ERRO_SLOT_OCUPADO  0xfffff    //Slot ocupado.      
#define ERRO_DEFAULT       0xffffe
//...


//Process runtime stack.
//??? Deve ser o limite máximo para a pilha de um processo.
#define MAXSTACK 128    //dwords.
 
//Número total de slots para criação de processo.
//@todo: deletar, definido em threads. ??? 
#define NUMERO_TOTAL_DE_SLOTS 256   
 
#define PROCESS_MAGIC 1234
 
/*
 * Globais.
 *
 * @todo: Talvez o certo é não ter globais aqui, e
 *        as estruturas e variáveis relativas ao gerenciamento
 *        de processos fique dentro do arquivo process.c.
 *        Encapsulamento.?? 
 */ 
 
 

/*
 * process_state_t
 *     Status de um processo.
 *     @todo: Pode-se usar mais status.
 *            como estado de transição.
 *
 *  Os status de um processo são diferentes do status de uma thread.
 *
 */ 
typedef enum {
	PROCESS_CREATED,
	PROCESS_INITIALIZED,
	PROCESS_RUNNING,
	PROCESS_BLOCKED,
	PROCESS_TERMINATED,
    PROCESS_IN_MEMORY,        //O processo está carregado na memória.
	PROCESS_OUT_OF_MEMORY,    //O processo não está carregado na memória.
	//...
}process_state_t;


/* 
 appmode_t
 
 Importante:
 
 APPMODE_TERMINAL = O kernel cria uma estrutura de terminal 
 com uma janela associada a essa estrutura, essa janela será a 
 janela de terminal para o aplicativo.
 APPMODE_WINDOW = O kernel não cria estrutura de terminal para 
 esse processo e o processo criará janelas.
 */
typedef enum {
    APPMODE_NULL,      // Isso se aplica ao processo kernel e ao processo idle por exemplo.	
    APPMODE_TERMINAL,  // O kernel cria uma janela de terminal para o aplicativo.
	APPMODE_WINDOW,    // o kernel não cria janela de terminal para o aplicativo
}appmode_t;

/*
 * Estruturas para processos.
 */

  
/*
 * process_d: 
 *    Process Control Block, PCB.
 *    Estruturas para processos.
 *    Estrutura onde se guarda informações sobre os processos.
 *    Cada estrutura terá informações necessárias para
 *    gerenciar um processo específico.
 *    São os SLOTS. 
 *
 *    Obs:
 *        Devem ter informações sobre o carregamento,
 *        se estão na memoria ou não, 
 *        se estão em processo de transição. etc.
 *        *IMPOTANTE: Uso de cotas de recursos.
 *
 *    @todo: 
 *        Deve-se começar listando os recursos que o processo usa.
 *        Ex: Lista de arquivos, 
 *            lista de recursos que pretende usar.
 *            permissões, acessos, 
 *            (isso tem a ver com o usuário, dono do processo).
 *
 *     Obs: Fica por último o que for referenciado com menor frequência.
 *          Onde ficarão os diretórios e as páginas dos processos.(mm)
 *          O kernel precisa aloca memoria para os PDs PTs.
 *          O kernel precisa alocar memória para Heap e Stack dos processos.
 *          //...
 */
typedef struct process_d process_descriptor_t;
struct process_d 
{
	object_type_t objectType;
	object_class_t objectClass;
	
	//callback ,d.
	
    /*
	 * Identificadores.
	 */
	 
	//PID, (Process Identification), 
	//c, Número que identifica unicamente um processo.	
	int pid;
	//PPID, (Parent Process Identification),
    //b, Número de identificação do processo pai.	
	int ppid;                
	//UID, (User Identification),
	//a, Número de identificação do usuário que criou o processo.
	int uid;
	//GID, (Group Identification),
	//g, Número do grupo do dono do processo.
	int gid;
	
	
	//State.
	process_state_t state; //f, flag,

    //unsigned long error; //e. error.	

	unsigned long used;     //@todo: Poderia ser short.
    unsigned long magic;    //@todo: Poderia ser short.
	
	
	//
	// @todo:
	// +name     (Nome=EXEMPLO.BIN)
	// +pathname (Caminho=/root/boot/EXEMPLO.BIN)
	// +cmd      (linha de comando ex:EXEM ) 
	//
	
	unsigned long name_address;  //@todo: não usar isso.
	char *name;             //Nome do processo. 
	//char *pathname;       //@todo: Incluir.
	char *cmd;              //Nome curto que serve de comando.



	
	//Se o processo é ou não um processo de terminal.
	//que aparece no terminal.
	int terminal;
	
    //Importante:
	//isso substituirá a flag 'terminal'
    //APPMODE_TERMINAL = O kernel cria uma estrutura de terminal 
    //com uma janela associada a essa estrutura, essa janela será a 
    //janela de terminal para o aplicativo.
    //APPMODE_WINDOW = O kernel não cria estrutura de terminal para 
    //esse processo e o processo criará janelas.
	appmode_t appMode;
	
	//
	//    ****  Banco de dados ****
	//
	
	//
	//Obs: Um processo é um cliente de banco de dados.
	//     Um processo tem contas conjuntas e pessoais.
    //     um processo poderá compartilhar esses objetos.	
    //

	//
	// BANCOS
	//
	
	//Acesso ao banco de dados do kernel. (não é uma lista).
	struct bank_d *kdb;
	
	//Lista de acessos à bancos de contas conjuntas.
	struct bank_d *gdbListHead;
	
	//Lista de acessos à bancos de contas pessoais.
	struct bank_d *ldbListHead;
	
	
	//
	// CONTAS
	//
	
	//Lista de contas conjuntas que o processo tem.
	struct aspace_d *aspaceSharedListHead;
	
	//Lista de contas pessoais que o processo tem.
	struct aspace_d *aspacePersonalListHead;


	//Lista de contas conjuntas que o processo tem.
	struct dspace_d *dspaceSharedListHead;
	
	//Lista de contas pessoais que o processo tem.
	struct dspace_d *dspacePersonalListHead;
	
	//Testing...
	//Process Page Table. (PPT)
	//Quais são as páginas que o processo está usando e onde elas estão.
	//na tabela tem que ter: O número da página. onde ela está, se no disco ou se na memória
	//qual é o número do pageframe da página e qual o status de modificação
	// Bom, acho que pra isso, o processo deve trabalhar em um número limitado de pagetables
	// pois o número do frame deve ser o índice da pte dentro da page table.
	// Uma pagetable tem 1024 entradas, garantindo um número de 1024 frames, o que dá 4MB.
	// Mas se um processo tiver mais que 4MB? Então o diretório de páginas do processo
	// terá que ter mais de uma page table.
	// Obs: O kernel deve manter uma lista de frames que podem ser usados.
	//      na hora de criar uma pagetable pra um page directory de um processo
	// é necessário pegar na lista de frames 1024 frames livres ou quanto for necessário.
	//
	
	// **** IMPORTANTE ****
	// Uma lista de framepool. (Lista de partições de memória física).
	// Cada framepool é composto de 1024 frames.
	// Obs: *IMPORTANTE: Quando um processo é criado, pelo menos um framepool 
	// deve ser atribuído a ele, mesmo antes de mapear os frames desse 
	// framepool em alguma pagetable do page directory do processo.
	//
	struct frame_pool_d *framepoolListHead;
	
	
	//Quantidade de memória física usada pelo processo que não pode ser compartilhada
	//com outros processos. (em KB).
	unsigned long private_memory_size;
	
	//Quantidade de memória física usada pelo processo que pode ser compartilhada
	//com outros processos. (em KB).
	unsigned long shared_memory_size;
	
	//Quantidade de memória usada por um processo em determinado espaço de tempo.
	// workset = (private + shared);
	unsigned long workingset_size;
	unsigned long workingset_peak_size;	
	
	
	
	//
	//files.
	//
	//struct FILE Files; lista de arquivos usados por um processo.	

	//file descriptors.
	//struct file_t *files; //poteiro para array de estruturas de arquivos.
	
	//inicial thread.
	//struvt thread_d *thread; 
	
	//
	// MEMORY !!!  Image + Heap + Stack 
	//
	
	//struct image_t *processImageMemory;  // process image.(binario)
	//struct heap_t  *processHeapMemory;   //process heap
	//struct stack_t *processStackMemory;  //process stack.
	
    	
	//
	// ORDEM: O que segue é referenciado durante o processo de task switch.
	//

	/*
	 * Page directory information:
	 * ==========================
	 *
	 *     Todo processo deve ter seu próprio diretório.
	 *
	 *     As threads usam o diretório do processo ao qual pertencem.
	 *     O endereço do diretório é carregado no CR3.
	 *
	 */
	unsigned long Directory;                  //endereço do diretório do processo.
    struct page_directory_d *page_directory;  //ponteiro para a estrutura do diretório do processo.

	//
	// Teste: Blocos de memoria usados pelo processo.
	//
	
	//struct mmblock_d mmBlocks[32];    //estruturas 
	//unsigned long mmblockList[32];    //ponteiros para estruturas.
	
	//Muitas informações sobre a memória usada pro um processo.
	//struct process_memory_info_d *processMemoryInfo;
	
	/*
	 * Heap. 
	 */
	//struct heap_d *processHeap; //@todo: Usar essa estrutura.

	unsigned long Heap;           //Endereço do início do Heap do processo.
	unsigned long HeapSize;       //Tamanho do heap.
	unsigned long HeapPointer;    //Ponteiro do heap do processo para o próxima alocação.
	unsigned long HeapLastValid;  //Último ponteiro válido.
	unsigned long HeapLastSize;   //Último tamanho alocado..	
	
	/*
	 *  Stack and ImageAddres. 
	 */	
	//struct stack_d *processStack;  //@todo: Criar essa estrutura.
	
	unsigned long StackOffset;    //Deslocamento da pilha em relação ao início do kernel.
	unsigned long Stack;          //Endereço do início da Stack do processo.
	unsigned long StackSize;      //Tamanho da pilha.	
	unsigned long Image;          //Base da imagem do processo.
	unsigned long ImageSize;      //Tamanho da imagem do processo.
	
	
	//IOPL of the task. (ring).
	unsigned long iopl;      

	//PPL - (Process Permition Level).(gdef.h)
    //Determina as camadas de software que um processo terá acesso irrestrito.	
	process_permition_level_t ppl;

	//
	// Os procedimentos são pontos de entrada npos processos via iret.
	// o kernel utiliza eles para se comunicar com os processos.
	// Podemos ter vários pontos de entrada em um processo.
	// Configurados de diversas maneiras. Esses procedimentos ipc
	// são configurados pelo próprio processo na hora de sua inicialização.
	// Se o processo não configurá-los, o valor atribuído será NULL e eles
	// ficarão inválidos. Mas um programa não será fechado se perdermos
	// a referencia à um de seus procedimentos do tipo ipc. esses procedimentos
	// poderão ser configurados pelo programa a qualquer hora, em tempo de execução.
	// Já um procedimento de janela não pode ser fechado. Perdendo o procedimento de
	//  janela o programa fica comprometido, perdendo completamente o controle
	// que ele tinha sobre si próprio, ficando por conta do sistema operacional
	// todo o controle sobre o programa agora sem procedimento de janela.
	//
	
	
	//
	// Procedimentos IPC;    
	//

	//O endereço do procedimento de ipc de um processo.
	unsigned long ipc_procedure;
	unsigned long ipc_procedureEx;	
	//@todo: Criar esses e outros pontos de entrada nos processos.
	//unsigned long ipc_procedureFast;             //Só um argumento.
	//unsigned long ipc_procedureInitializeDriver; //Só um argumento.	
	//...
	
	//
	// Os procedimentos de janelas atual somente sobre a janela
	// que receber ou pegar a mensagem via chamada de procedimento.
	// Normalmente a janela ativa do programa tem o procedimento de
    // janela que comanda tudo dentro do programa; Se fecharmos
    // a janela ativa, perdemos a estrutura de janela que nos
    // dá acesso ao procedimento de janela que controla o programa
    // então o programa deve ser fechado.
	// Um procedimento de janela não pode ser fechado. Perdendo o procedimento de
	//  janela o programa fica comprometido, perdendo completamente o controle
	// que ele tinha sobre si próprio, ficando por conta do sistema operacional
	// todo o controle sobre o programa agora sem procedimento de janela.	
	//
	
	//
	// Procedimentos de janela.
	//
	
	//Endereço do procedimento de janela da processo. 
	unsigned long procedure;  
	
	//Argumentos para o procedimento de janela.
	struct window_d *window;    //arg1.
	int msg;                    //arg2.
	unsigned long long1;        //arg3.
	unsigned long long2;        //arg4.

		
	//struct process_d *callerq;	   //head of list of procs wishing to send.
    //struct process_d *sendlink;    //link to next proc wishing to send.
    //void *message_bufffer;		   //pointer to message buffer.
    //int getfrom_pid;		       //from whom does process want to receive.
    //int sendto_pid;	               //pra quem.
	
	//
	// @todo: Criar uma fila de mensagens.
	//
	

	
	//@todo: mailBox, sockets ... (IPC).
	
	
    //
	// @todo: Criar fila de mensagens do processo.
	//        Pois cada processo tem sua fila de mensagens.
	//        O procedimento de janela do processo pega mensagens aqui.
    //
	
	//unsigned char process_message_queue[8];
	

	/*
	 * Priority.
     * ========
     * Um processo tem uma prioridade básica estática e também uma prioridade 
	 * atual dinâmica, que pode ser incrementada ou decrementada. Se afastando 
	 * ou se aproximando da prioridade básica. Isso acontece no OpenVMS e no NT.
	 */
	unsigned long base_priority; //básica. 
	unsigned long priority;      //dinâmica.
	
	//Que tipo de scheduler o processo utiliza. (rr, realtime ...).
	//int scheduler_type;    
	
	/* 
	 * Temporização da tarefa. 
	 */
	
	unsigned long step;               //Quantas vezes a tarefa usou o processador. 
	unsigned long quantum;            //thread quantum
	unsigned long timeout;            //Tempo em modo de espera. 
	unsigned long ticks_remaining;    //rt, quanto tempo a tarefa tem disponível para ser concluida.
	
	//unsigned long alarm;            //Tempo para o próximo alarme, dado em ticks.
	
	//unsigned long ThreadQuantum;    //As threads do processo iniciam com esse quantum.
	
	/*
	 * QUANTUM:
	 * =======
	 *     Quantum é a cota atrituida à cada processo pelo
	 *     scheduler. (time slice) 
	 *     Esse é o tempo limite imposto pelo scheduler para
	 *     execução de um processo. Ocorre então uma preempção por tempo.
	 *      
	 *     'ProcessingTime' é atribuído pelo processo. É o quanto
	 *     ele precisa. o quanto ele deseja.
	 */
	
	//
	//  +++++ Thread support +++++
	//
	
	int threadCount;    //Número de threads do processo. 
	
	/*
	 * threadList:
	 *     Lista com ponteiros de estrutura das threads do processo.
	 *     O indice dessa lista serve para enumerálas.
     *	 
	 *     @todo: Usar array de estruturas dinâmico. (Alocar).
	 */ 
	unsigned long tList[32];      //@todo: deletar  
	//struct thread_d *Threads;   //@todo: usar esse.
	//struct thread_d CurrentThread;
	
	//A primeira thead de uma lista linkada.
	struct thread_d *threadListHead;
	//struct thread_d *threadReadyListHead;
	//...	
	
	//@todo: estatística de tempo de uso de cpi.
	
	//@todo: Tipo cpu-bound, i/o bound.
	
	/*
	 * window:
	 *    ID da janela mãe da tarefa.
	 *    Na estrutura de janela terá várias informações importantes. como:
	 * procedimento de janela, menus, procedimentos de menus ... etc.
	 *   @todo: criar variável.
	 *
	 */
	//int window_id;
	
	/*
	 * preempted:
	 *     flag ~ Sinaliza que uma tarefa pode ou não sofrer preempção.
     *	   Uma tarefa de menor prioridade pode deixar o estado running 
	 * para assumir o estado ready em favor de uma tarefa de maior prioridade
	 * que assumirá o estado running.
	 *
	 */
	unsigned long preempted;
	
	//saved ~ Sinaliza que a tarefa teve o seu contexto salvo.
	unsigned long saved;
	
	//??
	unsigned long PreviousMode;	

	
	/*
	 * Contexto.
	 *  @todo: Usar uma estrutura de contexto.
	 */
	unsigned short ss;
    unsigned long esp;
    unsigned long eflags;
    unsigned short cs;
    unsigned long eip;	
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
	//Continua o contexto ...
	
	
	/*
	 * event: 
	 *    Tipo de evento que fazem a tarefa entrar em modo de espera. 
	 */	
    //event_type_t event;
	

	
	
	/*
	 * Windows. (Janelas)
	 */
	
	//user session, window station e desktop. 
	//Obs: A estrutura de user session contem muitas informações.
	//@todo: usar processWindowStation processDesktop;
	//struct usession_d *processUserSession;
	struct wstation_d *window_station;    //Window Station do processo.  
	struct desktop_d  *desktop;           //Desktop do processo.        
	

	//
	// ORDEM: O que segue é referenciado com pouca frequência.
	//
	
	
	//fluxo padrão. etdio, stdout, stderr
	//unsigned long iob[3];
	
	// @todo:
	// Outros:
	//tempo de cpu.
	//prioridade básica. //Obs: prioridade poderia ser uma estrutura.
	//contagem de threads usadas no momento.
	//path name - Endereço completo do arquivo ex:/root/users/fred/text.bin
	//comando. - Comando que abre o programa.
	//Contagem de objetos sendo usado. (estatisticas ajudam melhorar o sistema.)
	//i/o read count - Contagem de leituras de disco feitas pelo processo.
	//i/o write count - Contagem de gravações de disco feitas pelo processo.
	//generic i/o - Outras operações de i/o que não são leitura e escrita em disco.
	//todal de bytes lidos do disco pelo processo.
	//total de bytes gravados no disco pelo processo.
	//generic bytes i/o. contagem de bytes para operações genéricas de i/o, excluindo disco.
	
	/*
	 * wait4pid: 
     * O processo pode estar esperando um processo filho fechar. 
	 * Para que ele prossiga.
	 */
	unsigned long wait4pid; 
	
	//Motivo da thread fechar.
	int exit_code;
	
	//Lista de processos filhos que estão no estado zumbi.
	// List of terminated childs
	struct process_d *zombieChildListHead;           
	
    //?? mensagens pendentes.	
	//struct thread_d *sendersList; //Lista encadeada de processos querendo enviar mensagem
	//struct thread_d *nextSender;  //próximo processo a enviar mensagem.
	
    //
    //Next.
    //	
	
    //PID do próximo processo. 
    //(@todo: usar next_process). 	
	int next_task;  //@todo deletar isso.
    //int next_process;
    //struct process_d *NextInitialized;    //Próximo pronto pra rodar.		
	//struct process_d *Parent;
	//struct process_d *Prev;
	
	
	
	//Signal
	unsigned long signal;
	unsigned long signalMask;
	
	struct process_d *Next;
};

//Os quatro principais processos.
process_descriptor_t *KernelProcess;     //PID=0.   Ok.
process_descriptor_t *IdleProcess;       //PID=100. ?
process_descriptor_t *ShellProcess;      //PID=101. ?
process_descriptor_t *TaskManProcess;    //PID=103. ?

//Outros.
process_descriptor_t *Process;           //Current.
process_descriptor_t *idle_proc;           //Iddle. //@todo: deletar
process_descriptor_t *cur_process;         //Current.

//Lista encadeada de processos.
process_descriptor_t *process_Conductor2;
process_descriptor_t *process_Conductor;
process_descriptor_t *process_rootConductor;
process_descriptor_t *CurrentProcess;    //Current.

//Genérico.
//process_descriptor_t *PCB;
//...


/*
 *    processList:
 *        Tabela de processos.
 *
 *    **** LONG-TERM SCHEDULER FOR PROCESSES ****
 *
 *     Essa é a thread job list, ou job queue.
 *     Armazena todos os processos do sistema.
 *     os que estão residentes na memoria ram e as que não estão.
*/  
unsigned long processList[PROCESS_COUNT_MAX];


//
// @todo: Aqui pode haver outras tabelas de processos:
//

//unsigned long running_processList[8];
//unsigned long running_processList[8];
//unsigned long running_processList[8];
//unsigned long running_processList[8];
//...




/*
 * Lista de processos:
 *   Em forma de fila.
 *
 */
typedef struct proc_list_d proc_list_t;
struct proc_list_d
{
	unsigned long len;
	process_descriptor_t *head;
	process_descriptor_t *tail;
	
}; 
proc_list_t *system_procs;      //Processos do sistema.
proc_list_t *periodic_procs;    //Processos periódicos.
proc_list_t *rr_procs;          //Processos do tipo round robin.
proc_list_t *waiting_procs;     //Processos que estão esperando.
  




/*
 * process_info_d:
 *
 *
 */
struct process_info_d process_info_t; 
struct process_info_d 
{
	int processId;
	struct process_d *process; 	
    
	int threadId;
	struct thread_d  *thread; 	
};
//process_info_t *process_info;



/* 
 * Linux style.
#define invalidate() \
 asm("movl %%eax,%%cr3"::"a" (0))
*/

//
// Protótipos de função.
//

int processSendSignal(struct process_d *p, unsigned long signal);


//
// Page directory support.
//
 
unsigned long GetPageDirValue();
unsigned long GetProcessDirectory(struct process_d *process);
void SetProcessDirectory(struct process_d *process, unsigned long Address);


//
// Process support.
//

int processTesting(int pid);

void init_processes();
void show_process_information();
process_descriptor_t *create_process( struct wstation_d *window_station,
                                    struct desktop_d  *desktop,
                                    struct window_d *window,
                                    unsigned long init_eip, 
                                    unsigned long priority, 
									int ppid, 
									char *name);
									
//Finalizações.
void CloseAllProcesses();									
void dead_task_collector();    
//@todo: mudar para dead_process_collector().
//void dead_process_collector();

/*
 * exit_process:
 *     exit process..
 *
 *     Torna o estado PROCESS_TERMINATED.
 *     mas não destrói a estrutura DO PROCESSO.
 *     Outra rotina destruirá as informações.
 *     liberara a memória.     
 */
void exit_process(int pid, int code);

void set_caller_process_id(int pid);
int get_caller_process_id();

int init_process_manager();

									
//
// Fim.
//

