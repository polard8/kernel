/*
 * Arquivo: queue.h
 *
 * Descrição:
 *     Header para queue.
 *     No fim da fila a prioridade é maior.
 *     OS ÚLTIMOS SERÃO OS PRIMEIROS.
 */

 
#define QUEUE_NULL     0
#define QUEUE_STANDBY  1
#define QUEUE_RUNNING  2
#define QUEUE_READY    3
#define QUEUE_WAITING  4
#define QUEUE_BLOCKED  5
#define QUEUE_ZOMBIE   6
#define QUEUE_DEAD     7
#define QUEUE_INITIALIZED 8
#define QUEUE_SYSCOOP  9    // Sistema, cooperação.   
#define QUEUE_USERCOOP 10   // Usuário, cooperação.   
#define QUEUE_SYSCONC  11   // Sistema, concorrência. 
#define QUEUE_USERCONC 12   // Usuário, concorrencia.  
#define QUEUE_REALTIME 13 
#define QUEUE_DEFAULT  14

// Niveis de prioridade.
#define QUEUE_LEVEL_MIN 15
#define QUEUE_LEVEL_MED 16
#define QUEUE_LEVEL_MAX 17


//filas
/*
unsigned long queue[256];  //...>fila 
unsigned long queue_head;  //...>head
unsigned long queue_tail;  //...>tail
unsigned long queue_size;  //número totas de espaços na fila (256).
unsigned long queue_total; //número total de tarefas presentes na fila.		
unsigned long queue_index;
unsigned long queue_first;
unsigned long queue_last;
*/
 
 
 
 
/*
 * IMPORTANTE
 *
 * @todo: usar array de estrutura dinamico. (alocado)
 * pois essa estrutura esta disperdiçando espaço com array estáticos.
 */
typedef struct queue_d queue_t;
struct queue_d
{
    /*
	 * @todo: Informações sobre o objeto.
	 */
	 // Type         
	 // Size
	 //...

    //
	// Filas de movimento das threads. 1 À 10
	//
   	
	//Movimento 1, initialized --> standby. 
    int standbyHead; 
    int standbyTail;
    int standbyMax;
    unsigned long standbyList[PRIORITY_MAX+1];    


	//Movimento 2, standby --> running.
	//Movimento 4, ready   --> running.    
	//*** deve estar em sintonia com a fila do dispatcher.	
    int runningHead; 
    int runningTail;
    int runningMax;
    unsigned long runningList[PRIORITY_MAX+1];    
	
	//Movimento 3, running --> ready.
	//Movimento 6, waiting --> ready.
	//Movimento 8, blocked --> ready.	
    int readyHead; 
    int readyTail;
    int readyMax;
    unsigned long readyList[PRIORITY_MAX+1];     
	 
	 
	//Movimento 5, ready --> waiting.
    //Esperando para retomar a execução.	
    int waitingHead;
    int waitingTail;
    int waitingMax;
    unsigned long waitingList[PRIORITY_MAX+1];
	  
	  
	//Movimento 7, running --> blocked.	
    int blockedHead;
    int blockedTail;
    int blockedMax;
    unsigned long blockedList[PRIORITY_MAX+1];
	  
	//Movimento 9, running --> zombie.	
    int zombieHead;
    int zombieTail;
    int zombieMax;
    unsigned long zombieList[PRIORITY_MAX+1];
	  
	  
	//Movimento 10, zombie --> dead.
    int deadHead;
    int deadTail;
    int deadMax;
    unsigned long deadList[PRIORITY_MAX+1];    

	//Movimento 11, zombie --> initalized.
    //Movimento 0,       x --> initalized. (created)	
    int initializedHead;
    int initializedTail;
    int initializedMax;
    unsigned long initializedList[PRIORITY_MAX+1];
	
	
	/*
     * RACE: 
	 *    Filas do loop do sistema. 
	 *    Cooperação e Concorrência.
	 *    
     */ 
	  
	  
    //Cooperação, sistema.
    int syscoopHead; 
    int syscoopTail;
    int syscoopMax;
    unsigned long syscoopList[PRIORITY_MAX+1];   

	//Concorrência, sistema.
    int sysconcHead; 
    int sysconcTail;
    int sysconcMax;
    unsigned long sysconcList[PRIORITY_MAX+1];

	/*
     * RACE: Filas do loop do usuário. Cooperação e Concorrência.
     */ 

	
	//Cooperação, usuário.
    int usercoopHead; 
    int usercoopTail;
    int usercoopMax;
    unsigned long usercoopList[PRIORITY_MAX+1];  	

	//Concorrência, usuário.
    int userconcHead; 
    int userconcTail;
    int userconcMax;
    unsigned long userconcList[PRIORITY_MAX+1];   

	
    /*
     * PITSTOP: Outras filas.
     */ 

   //realtime tasks queue. 
    int realtimeHead; 
    int realtimeTail;
    int realtimeMax;
    unsigned long realtimeList[PRIORITY_MAX+1];  //real time rr. 
	
	
    //default queue
    int defaultHead;
    int defaultTail;
    int defaultMax;
    unsigned long defaultList[PRIORITY_MAX+1]; 
	
	//
	// 3 níveis de prioridade para threads no estado READY.
	//
	
	
	//Mínimo = 'level <= DISPATCHER_PRIORITY_LOW'
    int minHead; 
    int minTail;
    int minMax;
    unsigned long minList[128];
	
	//Médio == 'DISPATCHER_PRIORITY_LOW > level <= DISPATCHER_PRIORITY_NORMAL'
    int medHead; 
    int medTail;
    int medMax;
    unsigned long medList[128];
    
	//Màximo = ' level > DISPATCHER_PRIORITY_NORMAL '
	int maxHead; 
    int maxTail;
    int maxMax;
    unsigned long maxList[128];
	
};
//queue_t *Queue;
queue_t *queue;






unsigned long queueList[8]; //nao usar.





/*
 *  
 */ 
 // Estrutura que descreve uma fila
typedef struct d_wait_queue wait_queue_t;
struct d_wait_queue
{
	//fila de tamanho fixo, 2, um usando e outro esperando.
	struct thread_d *head;
	struct thread_d *tail;
	//int head;
	//int tail;
};



//
// Protótipos.
//

int init_queue(struct queue_d *q);
/*
 * queue_insert_head:
 *     Coloca um dado no fim da fila. (LIFO)
 */
int queue_insert_head(struct queue_d *q, unsigned long data, int type);
int queue_insert_data(struct queue_d *q, unsigned long data, int type);
void *queue_get_data(struct queue_d *q, int type);
void show_queue_information(struct queue_d *q);
void ScanReadyQueue(struct queue_d *q);
void feed_ready_queue(struct queue_d *q, int type);

