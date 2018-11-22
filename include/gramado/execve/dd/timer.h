/*
 * File: timer.h
 *
 * Descrição:
 *     Header para o módulo timer. irq0.
 *     @todo: strucs ... definições de frequências ...
 *
 * Versão 1.0, 2015.
 */
 
 
//
// Count support variables.
//

#define	HZ 100	

//Usado no Linux. 
//#define CT_TO_SECS(x)	((x) / HZ)
//#define CT_TO_USECS(x)	(((x) % HZ) * 1000000/HZ) 
//... 


//
//  ## sys time ##
//

unsigned long sys_time_hz;

unsigned long sys_time_ms;

//Saving the total ticks the kernel is running.
//unsigned long kernel_tick_total;
unsigned long sys_time_ticks_total;


//Counting how much ticks the kernel is running.
//unsigned long kernel_tick;
 
// #extra
// Aciona uma flag para que o ts.c realize atividades extras,
// como gc, dead thread collector, request.
	
int extra; 

 
 
//PIT. 
#define TIMER_DRIVER_PATHNAME "root:/volume2/drivers/timer.bin"  
 
 
/*
    040-05F = 8253 or 8254 Programmable Interval Timer (PIT, see ~8253~)
	040     = 8253 channel 0, counter divisor
	041     = 8253 channel 1, RAM refresh counter
	042     = 8253 channel 2, Cassette and speaker functions
	043     = 8253 mode control  (see 8253)
	044     = 8254 PS/2 extended timer
	047     = 8254 Channel 3 control byte
*/	
 
/*
 * Como o linux define um Quantum (time slice) para tasks RR.
 */
/*
 * default timeslice is 100 msecs (used only for SCHED_RR tasks).
 * Timeslices get refilled after they expire.
 */
//#define RR_TIMESLICE            (100 * HZ / 1000)

//a flag indica se o cursor está habilitado ou não.
int timer_cursor_used;

//status do cursor.
int timer_cursor_status;

unsigned long time_out;

unsigned long timer_handler_address;    //global _irq0:



/*
 *******************************************************
 * timer_d:
 * Estrutura do objeto timer que será usado pelos aplicativos.
 * 
 * Precisamos identificar quem está usando para podermos enviar 
 * mensagem para quem possui o timer.
 *
 */

//typedef struct timer_d timer_t; 
struct timer_d 
{
	//Object.
	object_type_t objectType;
	object_class_t objectClass;
	
	int id;
	
	int used;
	int magic;
	
	//1 = one shot 
	//2 = intermitent
	
	int type;
	
	//owner.
    struct process_d *process;
	struct thread_d *thread;
	struct window_d *window;

	
	int count_down;     //--
	int initial_count_down; //base fixa
	
	//quantas vezes o timer se esgotou.
	unsigned long times;
	
	int status;  //??
	
	unsigned long flag; //f
	unsigned long error; //e
	
	//Navegação.
	struct timer_d *next;
};
//timer_t *Timer;


//lista de timers.
unsigned long timerList[32];


/*
 * KiTimer:
 * Interface chamada pelo handler da irq0 para um rotina num módulo dentro do 
 * kernel base.
 */
void KiTimer(); 

//Global para inicialização do módulo interno.
int timerInit();
int timerTimer();

void timerInit8253 ( unsigned long hz ); 

//...

//Global para acesso ao tempo imediatamente agora.
unsigned long now();

unsigned long get_timeout();
void set_timeout(unsigned long ticks);

unsigned long get_systime_hz();
unsigned long get_systime_ms();
unsigned long get_systime_totalticks();

void timerEnableTextCursor ();
void timerDisableTextCursor ();

unsigned long get_systime_info (int n);

struct timer_d *create_timer ( struct window_d *window, unsigned long ms, int type  );
//#todo destroy timer.

int new_timer_id ();

//
// End.
//

