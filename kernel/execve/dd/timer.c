/*
 * File: unb\timer.c 
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
 *     Versão: 1.0, 2014 - Revisão. 
 *     Versão: 1.0, 2015 - Aprimoramento geral das rotinas básicas.
 *     Versão: 1.0, 2016 - Revisão.
 *     ...
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



int timerShowTextCursor;     //se tá habilitado ou não
int timerTextCursorStatus;   //0=apaga 1=acende 

//??
//unsigned long timerCountSeconds;  //Count Seconds.
//...


//
// Funções internas.
//


//Rotina principal.
void timer();        
//...



/*
 * KeTimer:
 *     Chama o handler do kernel que está no modulo externo.
 *     @todo Isso deve sair daqui.
 *           Com essa função o kernel chamará o handler do modulo externo.
 * Obs:
 *     Apenas a ISR0, _irq0, pode chamar essa rotina.
 *     #bugbug deletar essa rotina.
 */
void KeTimer (){
    
	// A estrutura para o dispositivo
	// tem informações sobre o driver.
	// parte das rotinas de timer podem
	// ser implementadas em user mode
	// ou módulo externo do kernel.
	
	KiTimer ();	//#suspensa. (usando o handler do kernel base.)
};



/*
 * KiTimer:
 *     Chama o handler do kernel que está no kernel base.
 */
void KiTimer (){

	// Observar alguns procedimentos antes de chamar a rotina.

	timer ();
};



    
	
void timerEnableTextCursor (){
	
    timerShowTextCursor = 1;	
};

void timerDisableTextCursor (){
	
    timerShowTextCursor = 0;	
};	
	

/*
 *****************************************************
 * timer: 
 *     Handler chamado pelo ISR do timer (IRQ 0).
 *     (Contagem de tempo, tempo das tarefas, 
 * quantum ...).
 *     (tick tick tick)
 */
void timer (){
	
	
	//
	// ## ticks total ##
	//

	
    //Contador de ticks.
	//Incrementa o Tempo total de funcionamento do kernel.
	
	//timerTicks++; 
    sys_time_ticks_total++;	

	//
	// ## sys time ##
	//
	
	//Mais 10ms para um sistema funcionando a 100HZ
    //sys_time_ms = sys_time_ms + 10;
	
	sys_time_ms = (unsigned long) sys_time_ms + (1000/sys_time_hz);	

	
	//
	// ## threads time ##
	//

	//Atribui um número de request a ser atendido futuramente.
	//Tratará o tempo das tarefas de acordo com o tipo.
	//#obs: Isso poderia ser usado para atualizar o time dos processos.
	
	kernel_request = KR_TIME;  



	//
	// ## mouse blink ##
	//
	
	
	//de tempos em tempos atualiza o cursor
	if ( sys_time_ticks_total % 64 == 0 )	
	{
		//Se o cursor piscante está habilitado.
		//Essa flag é acionada pelo aplicativo.
		if (timerShowTextCursor == 1)
		{
		    if ( timerTextCursorStatus != 1 )
		    { 
	            //apaga
	            refresh_rectangle ( (g_cursor_x + 1)  *8, g_cursor_y*8, 16, 16 );	
                timerTextCursorStatus = 1;
		        goto mouseExit;
		    }
	
		    if ( timerTextCursorStatus == 1 )
            {			
		        //acende
                bmpDisplayCursorBMP ( cursorIconBuffer, (g_cursor_x + 1) * 8, g_cursor_y*8 );		
		        timerTextCursorStatus = 0;
			    goto mouseExit;
		    }
		};
	};
mouseExit:	

    //Nothing for now ...	
	 

done:
    	
	//#todo
	//if(time_out > 0){
	//	time_out--;
	//};
	
	return;
};


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
	
	unsigned short periodHZ = (unsigned short) hz;
	
	unsigned short period =  ( (3579545L/3) / periodHZ );
	//static const unsigned short period = (3579545L/3)/HZ;
	//static const unsigned short period = (3579545L/3)/hz;
	
	outportb(0x43, 0x36);			  //Canal 0, LSB/MSB, modo 3, contar em binário.
	outportb(0x40, period & 0xFF);    //LSB.
	outportb(0x40, period >> 8);	  //MSB.
	
	//#BUGBUG Não faremos isso aqui,
	//faremos quando ermos spawn da idle thread.
	//irq_enable(0x00); // Timer
	
	// #importante
	// Isso será uma variável para fazermos testes de desempenho. 
	//
	//sys_time_hz = HZ;
	
	sys_time_hz = (unsigned long) hz;
};


/*
 * set_quantum:
 * ?? Provavelmente alguma configuração de quantum 
 * padrão para o sistema. 
 * Isso poderá ser usado por rotinas que lidam 
 * com tempo.
 */
void set_quantum( unsigned long q)
{
    quantum = (unsigned long) q;
	//return;
};


/*
 **************************************
 * get_quantum
 * ??
 */
unsigned long get_quantum()
{
    return (unsigned long ) quantum;
}; 


/*
 *******************************************
 * set_current_quantum
 * ??
 */
void set_current_quantum( unsigned long q)
{
    current_quantum = (unsigned long) q;
	//return;
};


/*
 **********************************************
 * get_current_quantum  
 * ??
 */
unsigned long get_current_quantum()
{
    return (unsigned long ) current_quantum;
}; 


/*
 *************************************
 * set_next_quantum   
 * ??
 */
void set_next_quantum( unsigned long q)
{
    next_quantum = (unsigned long) q;
	//return;
};


/*
 **********************************
 * get_next_quantum   
 * ??
 */
unsigned long get_next_quantum()
{
    return (unsigned long ) next_quantum;
}; 


/*
 ******************************************
 * now   
 */
unsigned long now (){
	
    return (unsigned long) get_systime_ms ();
};



unsigned long get_systime_hz(){
	
    return (unsigned long) sys_time_hz;
};


/*
 * get_systime_ms:
 */
unsigned long get_systime_ms(){
	
    return (unsigned long) sys_time_ms;
};


/*
 * get_systime_totalticks:
 */
unsigned long get_systime_totalticks(){
	
    return (unsigned long) sys_time_ticks_total;
};



unsigned long get_systime_info (int n){
	
    switch (n)
    {
		//#todo criar um enum para isso.
		
		case 1:
		    return (unsigned long) get_systime_hz();
            break;
			
		case 2:
		    return (unsigned long) get_systime_ms();
            break;
			
		case 3:
		    return (unsigned long) get_systime_totalticks();
			break;
		
		//...
		
		default:
		    return (unsigned long) 0;
		    break;
	}	
};

/*
 ***************************************
 * sleep:
 *     Apenas uma espera, um delay.
 *     Essa não é a função que coloca uma 
 * tarefa pra dormir no caso de evento.
 *   #todo: Usar o ms do contador do sys_time
 */
void sleep (unsigned long ms) 
{
    unsigned long t = (unsigned long) ( ms * 512 );
	
	while(t > 0){
		t--;
	}
//done:	
//	return;
};


/*
unsigned long timerGetTicks();
unsigned long timerGetTicks()
{
    return (unsigned long) timerTicks;	
};
*/


/*
 ****************************************
 * set_timeout:
 *
 *
 */
void set_timeout( unsigned long ticks ){

	time_out = (unsigned long) ticks;
};


/*
 ****************************************
 * get_timeout
 */
unsigned long get_timeout (){
	
	return (unsigned long) time_out;
};


/*
 **************************************
 * timerTimer: 
 *     Constructor.
 *     Inciaialização de variáveis do módulo.
 */
int timerTimer (){
	
	//apenas inicializando, isso será atualizado.   
	sys_time_hz = 0;

	//ms
    sys_time_ms = 0;	
	
	//Inicializa ticks.    
	sys_time_ticks_total = 0;	
    
    //...
	
	return (int) 0;
};


/*
 ********************************************
 * timerInit:
 *     Inicializa o driver de timer.
 *     Inicializa as variáveis do timer.
 *     @todo: KiTimerInit 
 * (unsigned long CallBackExemplo); 
 */
int timerInit (){
	
	
	//Constructor.
	timerTimer();
	
	
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
   
   
   /*
    * @todo: criar a estrutura do timer.
	*/

	//
	//@todo:
	//    alocar memoria para a estrutura do timer.
	//    inicializar algumas variaveis do timer.
	//    por enquanto estamos usando variaveis globais.
	//    ?? Não se se ja foi configurado o timer.
	// ou devemos chamr init_8253() agora. ou depois.
	//
	
	

	
	//timerCountSeconds = 0;
	
	//Configura quantum.
	set_current_quantum(QUANTUM_BASE);
	set_next_quantum(QUANTUM_BASE);
    set_quantum(QUANTUM_BASE);

	
	set_timeout(0);
	
	//Continua...
	
//Done.
done:
    g_driver_timer_initialized = (int) 1;
	
#ifdef EXECVE_VERBOSE
    printf("timerInit: Done\n");
#endif
	
	return (int) 0;
};


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

