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



//
// Variáveis internas.
//

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


//
// Text cursor
//

int timerShowTextCursor;  



//??
//unsigned long timerCountSeconds;  //Count Seconds.
//...


//
// Funções internas.
//


//Rotina principal.
void pitTimer(void); 
// ...


/*
 ************************************
 * irq0_TIMER:
 *     Chama o handler do kernel que está no kernel base.
 * #todo: Observar alguns procedimentos antes de chamar a rotina.
 */
 
__VOID_IRQ 
irq0_TIMER (void)
{

    // Se o timer não estiver inicializado !
    if ( __breaker_timer_initialized == 0 )
        return;


	//
	// Profiler
	//

	// Contando as interrupções desse tipo.
    g_profiler_ints_irq0++;


	//#debug
	//vamos checar se o primeiro iret está trazendo
	//o fluxo para cá.
	//quando não houver falha vai fazer uma bagunça...
	//mas no caso de falha vai ficar limpo.
	//também podemos usar o debug via porta serial.
	//kprintf ("#debug KiTimer ");
	//refresh_screen();
	//refresh_screen();
	//while(1){}

    pitTimer();
}



/*
 *****************************************************
 * pitTimer: 
 *     Handler chamado pelo ISR do timer (IRQ 0).
 *     (Contagem de tempo, tempo das tarefas, 
 * quantum ...).
 *     (tick tick tick)
 */

void pitTimer (void){

    // Timers.
    int i = 0;

    struct timer_d  *Timer;

    struct thread_d *Thread;


    /*
    // #delete
    // I was used by the old blinking cursor support.
    unsigned long __cWidth  = gwsGetCurrentFontCharWidth();
    unsigned long __cHeight = gwsGetCurrentFontCharHeight();
    if ( __cWidth == 0  ||  __cHeight == 0 ){
        panic ("pitTimer: char size\n");
    }
    */


    //#bugbug
    //This is just for test
    //mensagem para todas as threads quando estao rodando.
    //Thread = (struct thread_d *) threadList[current_thread];

    //
    // Jiffies.
    //

    // Contador de ticks.
    // Incrementa o Tempo total de funcionamento do kernel.

    jiffies++;



    
    if (sys_time_hz != 0 )
    {
        // por quantos segundos o sistema esta rodando
        // jiffies/sys_time_hz
        seconds = (jiffies/sys_time_hz);
    
        //sys_time_ms = sys_time_ms + 10;  //100 hz
        //sys_time_ms = sys_time_ms + 1;   //1000 hz
        sys_time_ms = (unsigned long) sys_time_ms + (1000/sys_time_hz);
    }


	//
	// ## threads time ##
	//

	//Atribui um número de request a ser atendido futuramente.
	//Tratará o tempo das tarefas de acordo com o tipo.
	//#obs: Isso poderia ser usado para atualizar o time dos processos.
	
	//#suspenso
	//estou repensando isso.
	
	//kernel_request = KR_TIME;  
	
	
	//
	// Working set support.
	//
    
    // #todo
    // As variáveis de working set estão em timer.h
	

	//Working set and profiler support.
	
	//apenas incremente.
	thread_profiler (1);
	    
    if ( jiffies % profiler_ticks_limit == 0 )
	{   
	    //quantidade de frames num determinado período de tempo.
	    // mm_profiler (); 
	    
	    //calcule.
	    thread_profiler (2);
	    //process_profiler (?);    
	}


    // Whatch dogs
    if ( jiffies % 100 == 0 )
    {
       // Incrementa o tempo em que o usuário está sem digitar.
        ____whatchdog_ps2_keyboard++;
        
        // Incrementa o tempo em que o usuário está sem usar o mouse. 
        ____whatchdog_ps2_mouse++;
        
        
        if ( ____whatchdog_ps2_keyboard > 100 )
        {
            ____whatchdog_ps2_keyboard = 0;
            //printf ("whatchdog timer: keyboard!\n");
            //mostra_slot (current_thread);
            //mostra_reg (current_thread);
            //refresh_screen();

            // Isso não surtiu efeito na máquina real.
            // printf ("whatchdog timer: Reinitializing ps2 controller ...\n");
            // refresh_screen();
            // ps2 ();

            // mostra os registrador da thread, em sua fase ring0.
            //asm ("int $3 \n");
        }

        if ( ____whatchdog_ps2_mouse > 200 )
        {
            ____whatchdog_ps2_mouse = 0;
            //printf ("whatchdog timer: mouse!\n");
            //refresh_screen();        
        }
        
    }



	//
	//  ## extra ## 
	//
	
	// Aciona uma flag para que o ts.c realize atividades extras,
	// como gc, dead thread collector, request.

    // #todo
    // Podemos fazer isso com menos frequência.

    if ( jiffies % 100 == 0 ){ extra = 1; }



    //
    // The blinking cursor.
    //
    
    // #test
    // The goal:
    // Show the blinking cursor on a virtual console in fullscreen mode.
    // Ok. It is working on qemu
    // See: user/console.c

    /*
    //if ( (jiffies % mouse_cursor_hz) == 0 )
    if ( (jiffies % (1000/2) ) == 0 )
    {
        if (timerShowTextCursor == TRUE){
            consoleBlinkTextCursor();
        }
    }
    */
    

    //
    // Timers
    //


    // Lista de timers.
    // Podemos percorrer a lista de timer e decrementar,
    // quando um timer chegar a 0, mandamos uma mensagem
    // para a thread associada à esse timer..

    // #todo
    // Call a helper function for that.


    for ( i=0; i<32; i++ )
    {
        // pega um da lista
        Timer = (struct timer_d *) timerList[i];

        if ( (void *) Timer != NULL )
        {
            if ( Timer->used == TRUE && Timer->magic == 1234 )
            {
                if ( Timer->count_down > 0 )
                {
                    Timer->count_down--;
                    
                    // Chegamos ao 0.
                    if ( Timer->count_down == 0 )
                    {
                        // Enviamos a mensagem para a thread 
                        // que é dona do timer.
                        // #todo:
                        // Create a helper function for that.

                        //Thread = (struct thread_d *) Timer->thread;
                        Thread = (struct thread_d *) threadList[ Timer->tid ];

                        if ( (void *) Thread != NULL )
                        {
                            if ( Thread->used == TRUE && Thread->magic == 1234 )
                            {
                                // Send system message to the thread.
                                Thread->window_list[ Thread->tail_pos ] = Timer->window;  //#bugbug:fail
                                Thread->msg_list[    Thread->tail_pos ] = MSG_TIMER;    
                                Thread->long1_list[  Thread->tail_pos ] = Timer->times;   //quantas vezes esse timer se esgotou.
                                Thread->long2_list[  Thread->tail_pos ] = Timer->status;  //status.

                                Thread->tail_pos++;
                                if ( Thread->tail_pos >= 31 ){
                                    Thread->tail_pos = 0;
                                }
                                //#debug
                                //printf("*"); refresh_screen();
                            }
                        }

						//analisando o tipo.
						//dependendo do tipo, devemos parar ou recomeçar.
						//one shot or intermitente

                        if ( Timer->type == 1 ){ Timer->count_down = 0; }
                        if ( Timer->type == 2 ){ Timer->count_down = Timer->initial_count_down; }
                        //...
                    }
                }
            }
        }
    };


done:
    return;
//fail:
    //return;
}


void timerEnableTextCursor (void)
{
    timerShowTextCursor = TRUE;
}


void timerDisableTextCursor (void)
{
    timerShowTextCursor = FALSE;
}


int new_timer_id (void){

    int i=0;
    unsigned long new=0;


    for ( i=0; i<32; i++ )
    {
		new = (unsigned long) timerList[i];
		
        if ( new == 0 ){ return (int) i; }
	};
	
	//fail
	return (int) -1;
}



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
 
void timerInit8253 ( unsigned long hz ){
	
	//#todo:
	//podemos fazer filtros.

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

// systime in ms
unsigned long now (void)
{
    return (unsigned long) get_systime_ms();
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


//#todo
/*
unsigned long get_jiffies (void);
unsigned long get_jiffies (void)
{
    return (unsigned long) jiffies;
}
*/


/*
 ***********************
 * get_systime_info:
 * 
 */

unsigned long get_systime_info (int n){

    // #todo 
    // Criar um enum para isso.
    // Comentar uma descrição em cada item.

    switch (n){

    case 1:
    return (unsigned long) get_systime_hz();
    break;

    case 2:
    return (unsigned long) get_systime_ms();
    break;

    case 3:
    return (unsigned long) get_systime_totalticks();
    break;

    // ...

    default:
    return (unsigned long) 0;
    break;
    
    };

    // fail.
    return (unsigned long) 0;
}


/*
 ***************************************
 * sleep: 
 * 
 * #todo
 *     Apenas uma espera, um delay.
 *     Essa não é a função que coloca uma 
 * tarefa pra dormir no caso de evento.
 *   #todo: Usar o ms do contador do sys_time
 */

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


/*
 **************************************
 * timerTimer: 
 *     Constructor.
 *     Inciaialização de variáveis do módulo.
 */

int timerTimer (void){


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
 ********************************************
 * timerInit:
 *     Inicializa o driver de timer.
 *     Inicializa as variáveis do timer.
 *     @todo: KiTimerInit 
 * (unsigned long CallBackExemplo); 
 */

int timerInit (void){

    int i=0;

    //
    // Breaker
    //

    __breaker_timer_initialized = FALSE;



	//Constructor.
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


    // quantum support

    set_current_quantum (QUANTUM_BASE);
    set_next_quantum (QUANTUM_BASE);
    set_quantum (QUANTUM_BASE);


    // timeout 

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
 * early_timer_init:
 *     Inicialização prévia do módulo timer.
 *     Uma outra inicialização mais aourada poderá ser feita
 * posteriormente.
 *     Porém ainda existe uma inicialização feita em Assembly
 * quando o kernel é inicialazado.
 * 
 */

int early_timer_init (void){

    int i=0;

    //
    // Breaker
    //

    __breaker_timer_initialized = FALSE;


	//Constructor.
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


    //
    // == Quantum =======================================
    //

    set_current_quantum (QUANTUM_BASE);
    set_next_quantum (QUANTUM_BASE);
    set_quantum (QUANTUM_BASE);


    //
    // == Timeout =======================================
    //

    //timeout 

    set_timeout(0);

	
    // Initializing whatchdogs.
    // Eles serão zerados pelas interrupções dos dipositivos e
    // incrementados pelo timer.
    // A condição crítica é alcançar um limite, um timeout.
    ____whatchdog_ps2_keyboard = 0;
    ____whatchdog_ps2_mouse    = 0;
    //...


	
	//Continua...
	


//#ifdef EXECVE_VERBOSE
//    printf("timerInit: Done\n");
//#endif


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


//
// End.
//

