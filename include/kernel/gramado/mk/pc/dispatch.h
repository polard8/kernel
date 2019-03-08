/*
 * Arquivo: dispatch.h
 *
 * Descrição:
 *     Header do módulo dispatcher do kernel base.
 *
 * Histórico:
 *     Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 */


/*
 * Tipos de dispatcher.
 */ 
#define DISPATCHER_NULL      0 
#define DISPATCHER_SYSCOOP   1  // Sistema, cooperação.   (64)*rr
#define DISPATCHER_USERCOOP  2  // Usuário, cooperação.   (32)
#define DISPATCHER_SYSCONC   3  // Sistema, concorrência. (16)
#define DISPATCHER_USERCONC  4  // Usuário, concorrência.  (8)
#define DISPATCHER_SYSTEM    5  // Primeiras tarefas rodando.
#define DISPATCHER_IDLE      6  // Esclusivo para tarefas idle.(mais de uma)
#define DISPATCHER_PERIODIC  7  // Tarefas periodicas. (rodam de tempos em tempos)(como o dead taskcollector.)
#define DISPATCHER_RR        8  // Round robin. (confinadas em um processador...Nao importa a prioridade)
#define DISPATCHER_REALTIME  9  // Realtime ,round robin. (confinadas em um processador...Importa a prioridade)
#define DISPATCHER_CURRENT  10  // Dispacha a tarefa atual. 
#define DISPATCHER_READY    11  // A fila do dispatcher.



//Enumerador de criterio de seleção de thread.
#define SELECT_IDLE_COUNT         1
#define SELECT_INITIALIZED_COUNT  2
#define SELECT_NEXT_COUNT         3 
#define SELECT_CURRENT_COUNT      4  
#define SELECT_ANY_COUNT          5
#define SELECT_IDEAL_COUNT        6
#define SELECT_DISPATCHER_COUNT   7

/*
 * Seleciona o tipo de dispatcher sendo usado no momento.
 */
int dispatcherType;
int dispatcherQueueIndex;


//
// Contador de dispatch por categoria de dispatch.
//
typedef struct dispatch_count_d dispatch_count_t;
struct dispatch_count_d
{	
	//Quando selecionamos a idle.
	unsigned long SelectIdleCount;
	
	//Quando selecionamos uma thread no momento de sua inicialização.
	unsigned long SelectInitializedCount;
	
	//Quando selecionamos a próxima indicada na estrutura da thead.
    unsigned long SelectNextCount;
	
	unsigned long SelectCurrentCount;

    //Quando selecionamos uma procurando por ela.	
    unsigned long SelectAnyCount;

	//selecionamos a melhor possivel.
    unsigned long SelectIdealCount;	

	//Quando selecionamos a proxima na fila do dispatcher.
	unsigned long SelectDispatcherQueueCount;
	
	//...
 	
};
dispatch_count_t *DispatchCountBlock;





// exemplo:
// KiDispatcherReadyListHead - This is an array of type list entry. The
//      elements of the array are indexed by priority. Each element is a list
//      head for a set of threads that are in a ready state for the respective
//      priority. This array is used by the find next thread code to speed up
//      search for a ready thread when a thread becomes unrunnable. See also
//      KiReadySummary.
//

/*
 * dispatcherReadyList:
 *
 *    **** SHORT-TERM SCHEDULER FOR THREADS****
 *
 *     Esta é a lista do dispatcher.
 *     Lista ponteiros para as heads de listas.
 *     as listas são para threads, uma lista para cada prioridade.
 *
 *     *IMPORTANTE. 
 *     As threads aqui estão no estado READY e
 *     ordenadas por prioridade.
 *     
 *     A última thread da lista é a thread de maior prioridade.
 *
 *     Cada elemento dessa lita é o olemento que está na HEAD de uma lista
 *     Cada uma dessas lista é uma lista para uma prioridade específica.
 * 
 *     Apenas a head de cada uma das listas é colocada aqui nessa lista do dispacher.
 *
 *     OBS: Nesse momento essa lista do dispacher não está sendo usada.  
 *          o kernel esta usando a lista de threads criadas. threadList[]
 *          não considerando a prioridade. ;)
 */ 

unsigned long dispatcherReadyList[PRIORITY_MAX +1];



/*
 * dispatcher:
 *     Função principal do dispatcher.
 *
 */ 
void dispatcher(int type);

int init_dispatcher();
void IncrementDispatcherCount( int type );

//
// Fim.
//
