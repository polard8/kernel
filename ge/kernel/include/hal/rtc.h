/*
 * File: rtc.h
 *
 * Descrição:
 *     Header file for rtc controller.
 *     Ring 0.
 *
 * 2015 - Created by Fred Nora.
 */ 


#ifndef ____RTC_H
#define ____RTC_H



#define  RTC_IRQ   8 
 
 
//ports 
#define RTC_ADDRESS_PORT 0x70 
#define RTC_DATA_PORT    0x71

unsigned short rtcGetBaseMemory (void);




//Time
#define  RTC_SEC    0x00  //*RTC seconds. 
#define  RTC_MIN    0x02  //*RTC minutes. 
#define  RTC_HOUR   0x04  //*RTC hours. 
#define  RTC_WDAY   0x06  //RTC weekday. 
#define  RTC_MDAY   0x07  //*RTC day of month. 
#define  RTC_MON    0x08  //*RTC month. 
#define  RTC_YEAR   0x09  //*RTC year. 

//Status
#define  RTC_STATUS_A   0x0A  //RTC status register A. 
#define  RTC_STATUS_B   0x0B  //RTC status register B. 
#define  RTC_STATUS_C   0x0C  //RTC status register C. 
#define  RTC_STATUS_D   0x0D  //RTC status register D. 

//Memory
#define RTC_LOWBYTE_BASEMEMORY       0x15  //Low. (Low base memory byte)
#define RTC_HIGHBYTE_BASEMEMORY      0x16  //High. (High base memory byte)
#define RTC_LOWBYTE_EXTENDEDMEMORY   0x30  //Low. (Low extended memory byte)
#define RTC_HIGHBYTE_EXTENDEDMEMORY  0x31  //High. (High extended memory byte)

//0x0e até 0x7f 114 bytes de used ram. ?? (intel) ep0579 us15w

//Outros
#define  RTC_STATUS_A_UPDATE_IN_PROGRESS  0x80  //RTC update in progress bit. 
#define  RTC_STATUS_B_24_HOUR  0x02  //RTC 24 hour format bit. 
#define  RTC_STATUS_B_BINARY   0x04  //RTC binary mode bit. 
#define  RTC_STATUS_B_PIE      0x40  //RTC Periodic Interrupt Enabled bit. 
//...




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

struct rtc_d *Rtc;
struct rtc_d *rtc;	

//rtc_t *Rtc;
//rtc_t *rtc;


//
// IRQ8.
//

void rtc_irq (void);


//
// Prototypes.
//

int init_clock (void);

unsigned long read_cmos_bcd(unsigned reg);

unsigned long get_time (void);

unsigned long get_date (void);

void *get_cmos_info (void); 


unsigned short rtcGetExtendedMemory (void);
unsigned short rtcGetMaseMemory (void);


#endif   


//
// End.
//

