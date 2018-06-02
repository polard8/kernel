/*
 * File: unblocked\timer.c 
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
// Constantes internas.
//

#define	HZ 100	


//
// Variáveis internas.
//

//Status do módulo.
int timerStatus;

//Contador de ticks.
unsigned long timerTicks;

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
void KeTimer()
{
    
	//
	// A estrutura para o dispositivo
	// tem informações sobre o driver.
	// parte das rotinas de timer podem
	// ser implementadas em user mode
	// ou módulo externo do kernel.
	//
	
	
	KiTimer();	//#suspensa. (usando o handler do kernel base.)
    //return;
};



/*
 ********************************************************
 * KiTimer:
 *     Chama o handler do kernel que está no kernel base.
 */
void KiTimer()
{

    //
	// Observar alguns procedimentos antes de 
	// chamar a rotina.
	//
	
done:
	timer();
    //return;
};




/*
 ***********************************************
 * timer: 
 *     Handler chamado pelo ISR do timer (IRQ 0).
 *     (Contagem de tempo, tempo das tarefas, 
 * quantum ...).
 *     (tick tick tick)
 */
void timer()
{		
    //Contador de ticks.
	timerTicks++;    

	//Atribui um número de request a ser atendido futuramente.
	//Tratará o tempo das tarefas de acordo com o tipo.
	kernel_request = KR_TIME;  

	
	//if(time_out > 0){
	//	time_out--;
	//};
	

	
	//
	// @todo: Tentando clacular os segundos.
	//

    //sempre apaga o cursor.
	//printf("%c", (char) 219 );   	
	//refresh_rectangle( g_cursor_x*8, g_cursor_y*8, 8, 8 );
	//g_cursor_x--;			

	
	// De tempos em tempos.
	//if( timerTicks % 18 == 0 )  
	if( timerTicks % 9 == 0 )	 
    {   
        //Incrementa a contagem de tempo de funcionamento do kernel.	
		kernel_tick++;   
			
		//REALTIME: Limite para funcionamento do kernel.		
		if( kernel_tick > 0xffff0000 ){
			kernel_request = KR_TIMER_LIMIT;
		};
		
		//cursor ativado
		//if( timer_cursor_used == 1 )
		//{	
		    //acende a cada múltiplo de 9
		//    printf("%c", (char) '_');   	
		//	refresh_rectangle( g_cursor_x*8, g_cursor_y*8, 8, 8 );
		//	g_cursor_x--;			
        //};
		
		
		//printf("One second ...\n");
		//refresh_screen();
		
		//timerCountSeconds++;
		
		
		goto done;    
    };
	
	/*
	 * @todo: Isso pode ir para task switch, para que o timer nao tenha nenhuma operação com threads.
	struct thread_d *t;
	int i;
	
	for(i = 0; i < 256; i++)
	{
	    t = (void*) threadList[i];
		if ((void*) t != NULL)
		{
		    if(t->Used == 1 && t->Magic == 1234)
			{
				t->Ticks++;
				//analizar qual tarefa esta mais perto da sua deadline.
			};	
			
		};
	};
    */
     
	 
// Done.
done:
    //Incrementa o Tempo total de funcionamento do kernel.
    kernel_tick_total++; 			
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
void timerInit8253()
{
	static const unsigned short period = (3579545L/3)/HZ;
	
	outportb(0x43, 0x36);			  //Canal 0, LSB/MSB, modo 3, contar em binário.
	outportb(0x40, period & 0xFF);    //LSB.
	outportb(0x40, period >> 8);	  //MSB.
	//irq_enable(0x00); // Timer
    
    //More?!
	
	//return;
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
 * ?? Obs: Estou reavaliando isso.
 */
unsigned long now()
{
	//??
    return (unsigned long) get_tick_count(); 
};


/*
 * get_tick_count:
 */
unsigned long get_tick_count()
{
    return (unsigned long) timerTicks;
};


/*
 ***************************************
 * sleep:
 *     Apenas uma espera, um delay.
 *     Essa não é a função que coloca uma 
 * tarefa pra dormir no caso de evento.
 */
void sleep(unsigned long ms) 
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
void set_timeout( unsigned long ticks )
{
	//??
	time_out = (unsigned long) ticks;
};


/*
 ****************************************
 * get_timeout
 */
unsigned long get_timeout()
{
	return (unsigned long) time_out;
};


/*
 **************************************
 * timerTimer: 
 *     Constructor.
 *     Inciaialização de variáveis do módulo.
 */
int timerTimer()
{
	//Inicializa ticks.
    timerTicks = 0;
    kernel_tick = 0;
    kernel_tick_total = 0;	
	
	
done:
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
int timerInit()
{
   // timerLock = 0;

   //set handler.
   
   //
   // @todo: Habilitar esse configuração pois é mais precisa.
   //
   
   //config frequências...
   //@todo: Isso poderia ser por último.
   //?? Isso pertence a i386 ??
   //?? Quais máquinas possuem esse controlador ??
    timerInit8253();
   
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
	
	
	//Constructor.
	timerTimer();
	
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
	
#ifdef KERNEL_VERBOSE
    printf("timerInit: Done.\n");
#endif
	
	return (int) 0;
};


//
// End.
//

