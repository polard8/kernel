/*
 * Arquivo: semaphore.h
 *
 * Descrição:
 *     Header do módulo semaphore do microkernel.
 *     M0.
 *     Rotinas de Down e Up.
 *     Os processos entram e saem da sua região crítica
 *     utilizando as rotinas de Down e Up. 
 *
 * Versão 1.0, 2015.
 */


 
#define SEMAPHORE_MAX 256    //Número máximo de semáforos por enquanto.
#define VERMELHO 0
#define VERDE    1
#define BASE_COUNT 0
#define MAX_COUNT  8


/*
 * estruturas.
 */
 


 
/*
 * semaphore_d:
 *     Estrutura para criação de um semáforo.        
 *
 *     Pode-se criar vários semáforos. Cada semáforo é usado para
 * controlar o fluxo em um determinado recurso.
 * 
 */ 
typedef struct semaphore_d semaphore_descriptor_t;
struct semaphore_d 
{
	object_type_t objectType;
	object_class_t objectClass;
    
    //call back. @todo: Create.
	//unsigned long callback; //d
	
	//Identificadores do semáforo.   	
	int id;         //c
	int used;       //b
	int magic;      //a
	int taskId;    	//g, A tarefa que esta usando o dispositivo. 
	
	//Estado do semáforo. (verde, vermelho)
	int color;          //G
	int status;         //F Flag.
	unsigned int count; //>=0   //E
   
    //...
	
    //@todo: corrigir o nome dessa estrututras.
	//struct d_wait_queue *sema_wait;   //ext1
    //struct wait_queue_d *sema_wait;   //ext1 	
	//...	
};
semaphore_descriptor_t *current_semaphore; 

unsigned long semaphoreList[32+1];


//
// Variáveis.
//
unsigned long semaforo_priority;
unsigned long semaforo_color;



/*
 * Semaphore support.
 */

/*
 * Down:
 *     Quando um processo vai entrar na sua região crítica
 *     ele executa um Down.
 *     Se o semáforo estiver com zero, significa que
 *     o recurso já está bloqueado por outro processo 
 *     então o processo que está tentando utilizar o recurso
 *     deve esperar, mudando o estado para waiting.
 */  

int Down (struct semaphore_d *s);


/*
 * Up:
 *     Quando um processo sai da sua região crítica
 *     ele dá um Up no semáforo, mudando seu valor pra 1.
 *     Isso libera o recurso pra outro processo.
 */ 

int Up (struct semaphore_d *s);


/*
 * Semaphore support.
 */

int init_semaphore(struct semaphore_d *s, unsigned int count); 

void semaphore_down(struct semaphore_d *s);

void semaphore_up(struct semaphore_d *s); 

void *create_semaphore (void); 

void delete_semaphore(struct semaphore_d *s);

void open_semaphore(struct semaphore_d *s);

void close_semaphore(struct semaphore_d *s);

//
// End.
//



