/*
 * Arquivo: messages.h
 *
 * Descrição:
 *     Gerenciamento de mensagens.
 * 
 *    "Uma mensagem pode ser dividida em vários pacotes."
 *
 */
 
//int zicaaa;


//char kernel_banner[] = "\n";

//@todo Criar estrutura e objeto.

/*
 * @todo: 
 * Estrutura básica para mensagens trocadas entre processos.
 * Uma Mensagem de teclado é uma mensagem trocada entre o 
 * processo kernel e o processo da ajanela com o focod e entrada.
 *
 */ 
 
typedef struct message_d message_t;
struct message_d
{
	object_type_t objectType;
	object_class_t objectClass;
	
	int used;
	int magic; 
	int empty;
	
	struct window_d *window;
	int msg;
	unsigned long long1;
	unsigned long long2;
};


/*
typedef struct current_message_consumer_d current_message_consumer_t;
struct current_message_consumer_d
{
	//object 
	
	struct process_d * process;
	struct thread_d *thread;

	//quanto tempo estamos esperando ele consumir a mensagem??
	//esta responpondendo ou não???
	
	struct message_d *message;	
}
current_message_consumer_t *CurrentMessageConsumer;
*/



#define SYSTEM_MESSAGE_QUEUE_MAX 32

//index
int system_message_write;
int system_message_read;

//guarda os ponteiros para estruturas de mensagens.
unsigned long system_message_queue[SYSTEM_MESSAGE_QUEUE_MAX];


void initialize_system_message_queue (void);





