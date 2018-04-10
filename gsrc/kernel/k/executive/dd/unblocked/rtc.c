/*
 * File: unblocked\rtc.c 
 *
 * Descrição:
 *     Real Time Controller ?!!
 *     Controlador RTC, Data e Hora.
 * @todo: Criar métodos para acessar os valores salvos na estrutura Rtc.
 *     
 * Ambiente: (RING 0).
 *
 * "CMOS" is a tiny bit of very low power static memory that lives on the same 
 * chip as the Real-Time Clock. (osdev)
 *
 * History:
 *     2013 - Created by Fred Nora.
 *     2017 - Revision.
 */


/*
 A typical OS will use the APIC or PIT for timing purposes. However, the RTC 
 works just as well. RTC stands for Real Time Clock. It is the chip that keeps 
 your computer's clock up-to-date. Within the chip is also the 64 bytes of 
 CMOS RAM. (osdev).
*/ 
/*
    070 CMOS RAM/RTC, also NMI enable/disable (AT,PS/2, see RTC)
	071 CMOS RAM data  (AT,PS/2)
*/
 
 
#include <kernel.h>

//Internas.
unsigned long rtcTicks;
int rtcStatus;
int rtcError;
//...


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
 *******************************************
 * rtc_irq: 
 *     irq8 interrupt handler.
 *     System CMOS, Realtime clock. 
 */
void rtc_irq()
{
	unsigned i;

	g_ticks++;
	
	//_BLINK; ??
	
    // Save contents of I/O port 0x70.
	i = inportb(0x70);
    
	// acknowledge IRQ 8 at the RTC by reading register C.
	outportb(0x70, 0x0C);
	(void)inportb(0x71); //??
	outportb(0x70, i);
    
	// @todo: Checar esse EOI.
	// acknowledge IRQ 8 at the PICs
	//outportb(0xA0, 0x20);
	//outportb(0x20, 0x20);
	
done:
	return;
};


/* 
 * read_cmos_bcd:
 *     Lê da CMOS um determinado registro. 
 */
unsigned long read_cmos_bcd( unsigned reg )
{
	unsigned long high_digit, low_digit;

	outportb( 0x70, ( inportb(0x70) & 0x80) | (reg & 0x7F) );
	high_digit = low_digit = inportb(0x71);

	// Converte BCD para binário. 
	high_digit >>= 4;

	high_digit &= 0x0F;
	low_digit  &= 0x0F;

	return (unsigned long) (10*high_digit) + low_digit;
};



/* 
 * get_time:
 * Pega o horário armazenado na CMOS.
 * Formato: Cada unidade representa 1 segundo. 
 *
 * todo: Essa função pode ser trabalhada sem riscos ao sistema.
 * STATUS: Não funciona muito bem. @todo: rever isso
 * Obs: Na verdade pode estar funcionando e o relógio da máquina virtual
 * está desatualizado.
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
 * get_date: 
 * Pega a data armazenada na CMOS. 
 * Formato(bytes): YYMD 
 *
 * todo: Essa função pode ser trabalhada sem riscos ao sistema.
 * sTATUS: fUNCIONA BEM.
 */
unsigned long get_date()
{
	unsigned long date;

	date  = read_cmos_bcd(9);
	date += read_cmos_bcd(8)*31;
	date += read_cmos_bcd(7)*(31*12);
	return (unsigned long) date;
};


/* 
 * rtcGetExtendedMemory:
 *     Get total memory info via CMOS. 
 *
 *  15h		Low byte of base memory size
 *				100h = 256k
 *				200h = 512k
 *				280h = 640k
 *	16h		High byte of 15h above
 *	17h		Low expansion memory byte
 *	18h		High expansion memory byte
 *				200h = 512k
 *				400h = 1024k
 *				600h-3C00h = 1536-15,360k
 *	19h		Extended type byte: Hard drive 1
 *	1Ah		Extended type byte: Hard drive 2
 *	1Bh-2Dh		reserved
 *	2Eh		check-sum for addresses 10h-2Dh  (word)
 *	2Fh		  see above
 *	30h		Low expansion memory byte
 *	31h		High expansion memory byte
 *				200h = 512k
 *				400h = 1024k
 *				600h-3C00h = 1536-15,360k
 *				
 *	Limite de uma 'word' ??			
 */
unsigned short rtcGetExtendedMemory()
{
    unsigned short total;
    unsigned char lowmem;
	unsigned char highmem;
 
    //Low. (Low extended memory byte)
    outportb(0x70, RTC_LOWBYTE_EXTENDEDMEMORY);
    lowmem = inportb(0x71);
    
	//High. (High extended memory byte)
	outportb(0x70, RTC_HIGHBYTE_EXTENDEDMEMORY);
    highmem = inportb(0x71);
	
    //Total.
    total = lowmem | highmem << 8;
	
done:	
    return (unsigned short) total;
};



/* 
 * rtcGetBaseMemory:
 *     Get base memory info via CMOS. 
 *
 *  15h		Low byte of base memory size
 *				100h = 256k
 *				200h = 512k
 *				280h = 640k
 *	16h		High byte of 15h above
 *	17h		Low expansion memory byte
 *	18h		High expansion memory byte
 *				200h = 512k
 *				400h = 1024k
 *				600h-3C00h = 1536-15,360k
 *	19h		Extended type byte: Hard drive 1
 *	1Ah		Extended type byte: Hard drive 2
 *	1Bh-2Dh		reserved
 *	2Eh		check-sum for addresses 10h-2Dh  (word)
 *	2Fh		  see above
 *	30h		Low expansion memory byte
 *	31h		High expansion memory byte
 *				200h = 512k
 *				400h = 1024k
 *				600h-3C00h = 1536-15,360k
 *				
 *	Limite de uma 'word' ??			
 */
unsigned short rtcGetBaseMemory()
{
    unsigned short total;
    unsigned char lowmem;
	unsigned char highmem;
 
    //Low. (Low base memory byte)
    outportb(0x70, RTC_LOWBYTE_BASEMEMORY);
    lowmem = inportb(0x71);
    
	//High. (High base memory byte)
	outportb(0x70, RTC_HIGHBYTE_BASEMEMORY);
    highmem = inportb(0x71);
	
    //Total.
    total = lowmem | highmem << 8;
	
done:	
    return (unsigned short) total;
};


/*
 * get_cmos_info:
 *     Obs: Essa função deve ser chamada apenas uma vez na inicialização
 * do módulo. @todo: Criar métodos que pegam esses valores salvos na 
 * estrutura.
 */
void *get_cmos_info()
{
	//
	// #bugbug
	// Alocando memória toda vez que chama a função.
	// Issa alocação deveria ser feita apenas uma vez
	// na inicialização, depois somente atualizados os valores.
	//
	
	Rtc = (void*) malloc( sizeof(struct rtc_d) );
    if( (void*) Rtc == NULL)
	{
	    printf("get_cmos_info fail: Struct\n");
		refresh_screen();
		//free(Rtc);
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
	    Rtc->Year       = (2000 + Rtc->Year);
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
	
	get_cmos_info();
	
Done:
    g_driver_rtc_initialized = (int) 1;	
	printf("Done!\n");	
	return (int) 0;
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
int rtcInit();
int rtcInit()
{
    rtcTicks = 0;
    rtcStatus = 0;
    rtcError = 0;


	init_clock();
	
	//Essa rotina deve ser chamada apenas uma vez na inicialização 
	//do módulo.
    //get_cmos_info()
	
					//rtc test.
					init_clock();
					get_cmos_info();
					printf("ExtendedMemory={%d} KB\n", rtcGetExtendedMemory());
					printf("time={%d}\n", get_time());
					printf("date={%d}\n", get_date());	
	
    return (int) 0;	
};
*/

//
//fim.
//

