/*
 * File: rtc.h
 *
 * Descrição:
 *     Header file for rtc controller.
 *     Ring 0.
 *
 * Versão 1.0, 2015.
 */ 
 
//
// Globals.
//

static volatile unsigned long g_ticks;

 
//
// RTC Structure.
//
 
typedef struct rtc_d rtc_t;
struct rtc_d
{

	object_type_t objectType;
	object_class_t objectClass;
	
	//unsigned long callback; //d
	

	//unsigned long ticks; //c
	unsigned long Seconds; //b
	unsigned long Minutes; //a
	unsigned long Hours;   //g

	unsigned long flag; //f
	unsigned long error; //e Error
	
	//ext ...
    unsigned long time;         //ext1
	unsigned long date;         //ext2
	unsigned long DayOfMonth;   //ext3
	unsigned long Month;        //ext4
	unsigned long Year;         //ext5 (cowboy).
	
	
	//unsigned long rtc_handler_address;
	
	//Monsters ...
	//...
};
rtc_t *Rtc;
rtc_t *rtc;




//
// IRQ8.
//

void KiRtcIrq(); 
void rtc_irq();


//
// Prototypes.
//

int init_clock();
unsigned long read_cmos_bcd(unsigned reg);
unsigned long get_time();
unsigned long get_date();
unsigned short GetTotalMemory();
void *get_cmos_info(); 

//
// End.
//

