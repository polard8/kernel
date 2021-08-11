/*
 * File: pit.c 
 *  
 * Descrição:
 *     Arquivo principal do driver do PIT. 
 *     Trara a irq0.
 *     Rotinas envolvendo tempo.
 *
 *  Ambiente: 
 *     (RING 0).
 *      Módulo interno, dentro do kernenel base.
 *
 * @todo: Criar funções que criam a estrutura timer ...
 * que será usada peloa aplicativos na forma de objeto .
 * elas devem ter um contador que enviará mensagens para o 
 * aplicativo sempre que se esgota a contagem.
 *
 * Histórico:
 *     Versão: 1.0, 2013 - Esse arquivo foi criado por Fred Nora.
 */

 
/*
I/O port     Usage
0x40         Channel 0 data port (read/write)
0x41         Channel 1 data port (read/write)
0x42         Channel 2 data port (read/write)
0x43         Mode/Command register (write only, a read is ignored)

Bits         Usage
 6 and 7      Select channel :
                 0 0 = Channel 0
                 0 1 = Channel 1
                 1 0 = Channel 2
                 1 1 = Read-back command (8254 only)
 4 and 5      Access mode :
                 0 0 = Latch count value command
                 0 1 = Access mode: lobyte only
                 1 0 = Access mode: hibyte only
                 1 1 = Access mode: lobyte/hibyte
 1 to 3       Operating mode :
                 0 0 0 = Mode 0 (interrupt on terminal count)
                 0 0 1 = Mode 1 (hardware re-triggerable one-shot)
                 0 1 0 = Mode 2 (rate generator)
                 0 1 1 = Mode 3 (square wave generator)
                 1 0 0 = Mode 4 (software triggered strobe)
                 1 0 1 = Mode 5 (hardware triggered strobe)
                 1 1 0 = Mode 2 (rate generator, same as 010b)
                 1 1 1 = Mode 3 (square wave generator, same as 011b)
 0            BCD/Binary mode: 0 = 16-bit binary, 1 = four-digit BCD
*/ 
 
 
 
/*
 PIT info:
 ========
 PIT: mode=2 count=0x48d3 (18643) - 64.00 Hz (ch=0)
 PIT: mode=3 count=0x10000 (65536) - 18.20 Hz (ch=0) (Oracle, Virtualbox).
 PIT: mode=3 count=0x2e9a (11930) - 100.01 Hz (ch=0) (Oracle, Virtualbox).
 PIT: mode=3 count=0x2e9b (11931) - 100.00 Hz (ch=0) (Oracle, Virtualbox).
 */ 




#include <kernel.h>  



//Status do módulo.
int timerStatus;

//Contador de ticks.
//unsigned long timerTicks;

//??  
int timerColor;

//??
unsigned long timerLine;

//??
unsigned long timerIdleState;

//??
int timerLock;

//??
int timerError;

// Text cursor

int timerShowTextCursor;  



//??
//unsigned long timerCountSeconds;  //Count Seconds.
//...





/*
 ************************************
 * irq0_TIMER:
 *     Chama o handler do kernel que está no kernel base.
 * #todo: Observar alguns procedimentos antes de chamar a rotina.
 */

// Called by:
// _irq0 in hw.asm


// See: pic.h
__VOID_IRQ 
irq0_TIMER (void)
{
    DeviceInterface_PIT();
}


// Presence of God!
void DeviceInterface_PIT(void)
{

//
// Gramado Alone
//

    jiffies++;

    // Used for debug
    // debug_print ("  -- TICK --  \n");
}



// Main globals.
int timerTimer (void)
{
    // total ticks
    jiffies = 0;

    // por quantos segundos o sistema esta rodando
    // jiffies/sys_time_hz
    seconds = 0; 

    // Por quantos ms o sistema esta rodando.
    sys_time_ms = 0; 

    // pit frequency
    sys_time_hz = 0;


//
// Profiler
//
    profiler_ticks_count = 0;
    profiler_ticks_limit = PROFILER_TICKS_DEFAULT_LIMIT;

    // ...

    return 0;
}

/*
 ******************************************
 * timerInit8253:
 *    @todo: Compreender melhor isso.
 *
 * Seta a frequência de funcionamento do 
 * controlador 8253. "3579545 / 3" 
 * instead of 1193182 Hz. 
 * Pois o valor é mais preciso, considera até os 
 * quebrados. 
 * Reprograma o timer 8253 para operar 
 * à uma frequencia de "HZ".
 * Obs: Essa rotina substitui a rotina init_8253.
 */
 
//#importante 
//Essa rotina poderá ser chamada de user mode,
//talvez precisaremos de mais argumentos. 
 
void timerInit8253 ( unsigned long hz )
{
	// #todo:
	// podemos fazer filtros.

    unsigned short clocks_per_sec = (unsigned short) hz;

    unsigned short period =  ( (3579545L/3) / clocks_per_sec );

    // Canal 0, LSB/MSB, modo 3, contar em binário.
    out8 ( 0x43, 0x36 );

    // LSB.
    out8 ( 0x40, period & 0xFF ); 
    //out8 ( 0x40, 0xA9 );  //test 1000

    // MSB.
    out8 ( 0x40, period >> 8 );
    //out8 ( 0x40, 0x04 );   // test 1000


	//#BUGBUG Não faremos isso aqui,
	//faremos quando ermos spawn da idle thread.
	//irq_enable(0x00); // Timer
	
	// #importante
	// Isso será uma variável para fazermos testes de desempenho. 

    // #??
    // Onde isso foi definido.
    // Podemos ter uma variável global com nome melhor?

    sys_time_hz = (unsigned long) hz;
}

// set_timeout: #todo 
void set_timeout ( unsigned long ticks )
{
    time_out = (unsigned long) ticks;
}

// get_timeout: #todo
unsigned long get_timeout (void)
{
    return (unsigned long) time_out;
}

// set_quantum:
void set_quantum ( unsigned long q)
{
    quantum = (unsigned long) q;
}

// get_quantum:
unsigned long get_quantum (void)
{
    return (unsigned long ) quantum;
}


// set_current_quantum: 
void set_current_quantum (unsigned long q)
{
    current_quantum = (unsigned long) q;
}

// get_current_quantum:
unsigned long get_current_quantum (void)
{
    return (unsigned long ) current_quantum;
}

// set_next_quantum:
void set_next_quantum (unsigned long q)
{
    next_quantum = (unsigned long) q;
}

// get_next_quantum:
unsigned long get_next_quantum (void)
{
    return (unsigned long ) next_quantum;
}  


void set_systime_hz ( unsigned long hz )
{
    sys_time_hz = hz;
}

// systime hz
unsigned long get_systime_hz (void)
{
    return (unsigned long) sys_time_hz;
}


// systime in ms
unsigned long get_systime_ms (void)
{
    return (unsigned long) sys_time_ms;
}


// get_systime_totalticks:
unsigned long get_systime_totalticks (void)
{
    return (unsigned long) jiffies;
}


/*
 ***********************
 * get_systime_info:
 * 
 */

    // #todo 
    // Criar um enum para isso.
    // Comentar uma descrição em cada item.

unsigned long get_systime_info (int n){

    switch (n){
    case 1: return (unsigned long) get_systime_hz();          break;
    case 2: return (unsigned long) get_systime_ms();          break;
    case 3: return (unsigned long) get_systime_totalticks();  break;
    // ...
    default:  
        return (unsigned long) 0;  
        break;
    };

    // fail.
    return (unsigned long) 0;
}


int new_timer_id (void)
{
    int i=0;
    unsigned long new=0;


    for ( i=0; i<32; i++ )
    {
        new = (unsigned long) timerList[i];

        if ( new == 0 ){ return (int) i; }
    };

	// fail
    return (int) -1;
}

void timerEnableTextCursor (void)
{
    timerShowTextCursor = TRUE;
}

void timerDisableTextCursor (void)
{
    timerShowTextCursor = FALSE;
}

// systime in ms
unsigned long now (void)
{
    return (unsigned long) get_systime_ms();
}


// fake
void sleep (unsigned long ms)
{
    unsigned long t=1;


    if ( ms == 0 ){
        ms=1;
    }

    // #bugbug
    // Is there a limit?

    t = (unsigned long) ( ms * 512 );

    while (t > 0)
    {
        t--;
    };
}


/*
 ********************************************
 * timerInit:
 *     Inicializa o driver de timer.
 *     Inicializa as variáveis do timer.
 *     @todo: KiTimerInit 
 * (unsigned long CallBackExemplo); 
 */

int timerInit (void)
{
    int i=0;

    // g_driver_timer_initialized = FALSE;

//
// Breaker
//
    __breaker_timer_initialized = FALSE;


    timerTimer();

    for ( i=0; i<32; i++ ){
        timerList[i] = (unsigned long) 0;
    }


    // timerLock = 0;

    //set handler.
   
    //
    // @todo: Habilitar esse configuração pois é mais precisa.
    //
   
    //config frequências...
    //@todo: Isso poderia ser por último.
    //?? Isso pertence a i386 ??
    //?? Quais máquinas possuem esse controlador ??
    
	// #importante
	// Começaremos com 100 HZ
	// Mas o timer poderá ser atualizado por chamada.
	// e isso irá atualizar a variável que inicializamos agora.

    sys_time_hz = (unsigned long) HZ;

    timerInit8253 ( sys_time_hz );



	// #todo:
	// alocar memoria para a estrutura do timer.
	// inicializar algumas variaveis do timer.
	// por enquanto estamos usando variaveis globais.
	// ?? Não se se ja foi configurado o timer.
	// ou devemos chamr init_8253() agora. ou depois.


    //timerCountSeconds = 0;


    // Quantum

    set_current_quantum (QUANTUM_MIN);
    set_next_quantum (QUANTUM_MIN);
    set_quantum (QUANTUM_MIN);

    // Timeout 

    set_timeout(0);

//
// Whatchdogs
//
    // Initializing whatchdogs.
    // Eles serão zerados pelas interrupções dos dipositivos e
    // incrementados pelo timer.
    // A condição crítica é alcançar um limite, um timeout.

    ____whatchdog_ps2_keyboard = 0;
    ____whatchdog_ps2_mouse    = 0;
    //...


	//Continua...


//
// breaker
//
    __breaker_timer_initialized = TRUE;

// Done
    g_driver_timer_initialized = TRUE;
    return 0;
}

/*
 ***********************************
 * early_timer_init:
 *     Inicialização prévia do módulo timer.
 *     Uma outra inicialização mais aourada poderá ser feita
 * posteriormente.
 *     Porém ainda existe uma inicialização feita em Assembly
 * quando o kernel é inicialazado.
 * 
 */

int early_timer_init (void)
{
    int i=0;

    //g_driver_timer_initialized = FALSE;

//
// Breaker
//
    __breaker_timer_initialized = FALSE;

    timerTimer();

    for ( i=0; i<32; i++ ){
        timerList[i] = (unsigned long) 0;
    };


//
// == Hz ============================================
//

    // Let's setup the variable sys_time_hz.
    // And setup the controler.
    // We can use the default variable. 
    // See> config.h

    // Changing the variable.
    // set_systime_hz ( HZ * 4 );     // Slow
    // set_systime_hz ( HZ * 6 );     // Normal
    set_systime_hz ( DEFAULT_HZ );    // See: config.h

    // Setup the controller.
    timerInit8253 ( sys_time_hz );


    // Quantum

    set_current_quantum (QUANTUM_MIN);
    set_next_quantum (QUANTUM_MIN);
    set_quantum (QUANTUM_MIN);

    // Timeout 

    set_timeout(0);


    // Whatchdogs

    // Initializing whatchdogs.
    // Eles serão zerados pelas interrupções dos dipositivos e
    // incrementados pelo timer.
    // A condição crítica é alcançar um limite, um timeout.
    ____whatchdog_ps2_keyboard = 0;
    ____whatchdog_ps2_mouse    = 0;
    //...


    // Continua...


//
// Breaker
//
    __breaker_timer_initialized = TRUE;

// Done
    g_driver_timer_initialized = TRUE;
    return 0;
}


/*
struct timer_d *timerObject();
struct timer_d *timerObject()
{
	//@todo: criar uma estrutura e retornar o ponteiro.
	return (struct timer_d *) x;
}
*/

/*
 ******************** 
 * create_timer:
 * 
 */

// IN: pid, ms, type

struct timer_d *create_timer ( 
    pid_t pid, 
    unsigned long ms, 
    int type )
{

    struct timer_d   *Timer;
    struct process_d *Process;
    struct thread_d  *Thread;


    int ID = -1;  //erro;


    debug_print("=============\n");
    debug_print("create_timer:\n");
    
    //printf     ("create_timer: pid=%d ms=%d type=%d\n",
    //    pid,ms,type);

    if (pid<0){
        debug_print("create_timer: [FAIL] pid\n");
        return NULL;
    }
    
    Process = (struct process_d *) processList[pid];
    if ( (void*) Process == NULL ){
        debug_print("create_timer: [FAIL] Process\n");
        return NULL;
    }

    // Thread de controle.
    //Thread = (struct thread_d *) Process->control;
    Thread = (struct thread_d *) threadList[current_thread];
    if ( (void*) Thread == NULL ){
        debug_print("create_timer: [FAIL] Thread\n");
        return NULL;
    }


	// limits
	// limite de 1 tick.

    // ms
    if (ms < (1000/sys_time_hz) )
    {
        printf ("create_timer: Ajust ms\n");
        ms = (1000/sys_time_hz);
    }

    // type
    if ( type < 1 || type > 10 )
    {
        panic ("create_timer: type fail\n");
        //printf("create_timer: type fail\n");
        //refresh_screen ();
        //return NULL;
    }

    //
    // Structure.
    //

    Timer = (void *) kmalloc( sizeof(struct timer_d) );

    if ( (void *) Timer == NULL ){
        panic ("create_timer: Timer fail \n");
        //printf ("create_timer: Timer fail \n");
        //refresh_screen ();
        //return NULL; 

    }else{

        // ??
        // List?
        ID = (int) new_timer_id();

        // Erro ao obter um novo id.
        if (  ID < 0 || ID > 32 ){
            panic ("create_timer: ID fail \n");
            //printf("create_timer: ID fail \n");
            //refresh_screen ();
            //return NULL;

        }else{

            Timer->used  = TRUE;
            Timer->magic = 1234;
            Timer->id = ID;
            
            // ms/(ms por tick)
            Timer->initial_count_down = (unsigned long) ( ms / (1000/sys_time_hz) );
            Timer->count_down = Timer->initial_count_down;

            //1 = one shot 
            //2 = intermitent
            Timer->type = (int) type;
            
            // Pegamos logo acima.
            Timer->process = (struct process_d *) Process;
            Timer->thread  = (struct thread_d *)  Thread;
            Timer->pid     = pid;
            Timer->tid     = current_thread;

            //printf("create_timer: done t={%d} :) \n",
            //    Timer->initial_count_down);

            // Coloca na lista.
            timerList[ID] = (unsigned long) Timer;
        };
    };

    // #debug
    debug_print("create_timer: done\n");
    refresh_screen ();

    return (struct timer_d *) Timer;

fail:
    debug_print("create_timer: [FAIL]\n");
    printf     ("create_timer: [FAIL]\n");
    refresh_screen ();
    return NULL;
}




















