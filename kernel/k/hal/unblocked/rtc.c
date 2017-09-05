/*
 * Arquivo: rtc.c 
 *
 * Descrição:
 *     Real Time Controller ?!!
 *     Controlador RTC, Data e Hora.
 *     
 * Ambiente: (RING 0).
 *
 *  Versão: 1.0 - 2013, 2014, 2015.
 */


/*
 A typical OS will use the APIC or PIT for timing purposes. However, the RTC works just as well.
 RTC stands for Real Time Clock. It is the chip that keeps your computer's clock up-to-date. 
 Within the chip is also the 64 bytes of CMOS RAM.
 osdev.
*/ 
 
 
#include <kernel.h>


//unsigned long rtcTicks;
//int rtcStatus;
//int rtcError;
//...


/*
    070 CMOS RAM/RTC, also NMI enable/disable (AT,PS/2, see RTC)
	071 CMOS RAM data  (AT,PS/2)
*/


//
//  @todo:    
//      As portas do controlador ainda estão subutilizadas.
//      fazer um driver mais completo utilizando melhor o controlador.
//




//
// Variáveis internas.
//
//int rtcStatus;
//int rtcError;
//...
 

 
/*
 * KiRtcIrq:
 *     irq8 interrupt handler.
 *     System CMOS, Realtime clock.
 *     Isso é uma interface para chamar a rotina verdadeira.
 */
void KiRtcIrq()
{
	//...
	
done:
    rtc_irq();
    return;	
}; 
 
 
 
/*
 * rtc_irq: 
 *     irq8 interrupt handler.
 *     System CMOS, Realtime clock. 
 */
void rtc_irq()
{
	unsigned i;

    /* 
	 * Increment char in upper left corner of screen on 
	 * every timer tick. 
	 */
	g_ticks++;
	

	
	//_BLINK; ??
	
    /* save contents of I/O port 0x70 */
	i = inportb(0x70);
    
	/* acknowledge IRQ 8 at the RTC by reading register C */
	outportb(0x70, 0x0C);
	(void)inportb(0x71);
	outportb(0x70, i);
    
	/* acknowledge IRQ 8 at the PICs */
	//outportb(0xA0, 0x20);
	//outportb(0x20, 0x20);
	
done:
	return;
};



/* Lê da CMOS um determinado registro. */
unsigned long read_cmos_bcd(unsigned reg)
{
	unsigned long high_digit, low_digit;

	outportb(0x70, (inportb(0x70) & 0x80) | (reg & 0x7F));
	high_digit = low_digit = inportb(0x71);

	/* Converte BCD para binário. */
	high_digit >>= 4;

	high_digit &= 0x0F;
	low_digit  &= 0x0F;

	return (unsigned long) (10*high_digit) + low_digit;
};



/* 
 * Pega o horário armazenado na CMOS.
 * Formato: Cada unidade representa 1 segundo. 
 *
 * todo: Essa função pode ser trabalhada sem riscos ao sistema.
 *
 */
unsigned long get_time()
{
	unsigned long time;

	time  = read_cmos_bcd(0);
	time += read_cmos_bcd(2)*60;
	time += read_cmos_bcd(4)*(60*60);	
	return (unsigned long) time;
};


/* 
 * Pega a data armazenada na CMOS. 
 * Formato(bytes): YYMD 
 *
 * todo: Essa função pode ser trabalhada sem riscos ao sistema.
 *
 */
unsigned long get_date()
{
	unsigned long date;

	date  = read_cmos_bcd(9);
	date += read_cmos_bcd(8)*31;
	date += read_cmos_bcd(7)*(31*12);
	return (unsigned long) date;
};

 
 
unsigned short GetTotalMemory()
{
    unsigned short total;
    unsigned char lowmem;
	unsigned char highmem;
 
    //Low. 
    outportb(0x70, 0x30);
    lowmem = inportb(0x71);
    
	//High.
	outportb(0x70, 0x31);
    highmem = inportb(0x71);
	
    //Total.
    total = lowmem | highmem << 8;
	
done:	
    return (unsigned short) total;
};



/*
 * get_cmos_info:
 *
 */
void *get_cmos_info()
{
	//
	// Alocando memória toda vez que chama a função.
	// Issa alocação deveria ser feita apenas uma vez
	// na inicialização, depois somente atualizados os valores.
	//
	
	Rtc = (void*) malloc( sizeof(struct rtc_d) );
    if( (void*) Rtc == NULL)
	{
	    printf("get_cmos_info fail: Struct\n");
		refresh_screen();
		free(Rtc);
		return NULL;
	}
	else
	{
	    //time
	    Rtc->Seconds = read_cmos_bcd(0);  // Seconds.
	    Rtc->Minutes = read_cmos_bcd(2);  // Minutes.
	    Rtc->Hours   = read_cmos_bcd(4);  // Hours.

	    //date.
	    Rtc->Year       = read_cmos_bcd(9);    
	    Rtc->Year = (2000 + Rtc->Year);
		Rtc->Month      = read_cmos_bcd(8);    
	    Rtc->DayOfMonth = read_cmos_bcd(7);    
			
		//@todo: put on structure.
    };
	
	//struct
	if( (void*) Hardware == NULL)
	{
		//erro
	    printf("get_cmos_info fail: Hardware struct\n");
		refresh_screen();
		//free(Rtc);
		return NULL;		 
	}else{
		Hardware->Rtc = Rtc;	//Save.	
	};

show_message:	
	printf("Time={%d:%d:%d}\n",Rtc->Hours      ,Rtc->Minutes ,Rtc->Seconds);
	printf("Date={%d/%d/%d}\n",Rtc->DayOfMonth ,Rtc->Month   ,Rtc->Year);
done:
	return (void*) Rtc;
};


/*
int init_rtc();
int init_rtc()
{
init_clock();
    return 0;
};
*/




/*
 * init_clock: 
 *     Inicia a data e a hora do controlador.
 *
 * @todo: 
 *     Essa função não deveria mostrar informações na tela.
 * tem que criar função pra isso.
 * essa aqui so deveria pegar as informações e colocar em estrutura.
 *
 */
int init_clock()
{
	
	/*
	 * @todo: criar uma estrutura para RTC.
	 */
	 
	 /*
	  *@todo:
	  * alocar memoria para a estrutura rtc.
	  * inicializar algumas variaveis da estrutura rtc.
	  */
	
	//unsigned long Time, Date; 
	
	//Time = get_time();
	//Date = get_date();
		  
	//printf("CLOCK INFORMATION:\n");
	//printf("Time=%d Date=%d\n", Time, Date);
	
Done:
    g_driver_rtc_initialized = (int) 1;	
	printf("Done!\n");	
	return 0;
};


/*
int rtcInit()
{};
*/

//
//fim.
//

