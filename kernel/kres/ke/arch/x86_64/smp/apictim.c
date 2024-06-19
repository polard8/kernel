
// apictim.c
// APIC timer.
// 2023 - Ported from Sirius OS, Created by Nelson Cole.

#include <kernel.h>

#define APIC_TIMER_NULL  0

#define APIC_TIMER_CONFIG_DATA_LVT(TimerMode,Mask,TriggerMode,Remote,InterruptInput,DeliveryMode,Vector)(\
(((unsigned int)(TimerMode) &0x3 ) << 17) |\
(((unsigned int)(Mask) &0x1 ) << 16) |\
(((unsigned int)(TriggerMode) &0x1 ) << 15) |\
(((unsigned int)(Remote) &0x1 ) << 14) |\
(((unsigned int)(InterruptInput) &0x1 ) << 13) |\
(((unsigned int)(DeliveryMode) &0x7 ) << 8) |\
((unsigned int)(Vector) &0xff )\
)



static unsigned int apic_timer_ticks=0;

static unsigned int __apictim_read_command(unsigned short addr);
static void __apictim_write_command(unsigned short addr,unsigned int val);

// #todo: Move from this document.
static void __pit_prepare_sleep(int hz);
static void __pit_perform_sleep(void);

//---------------------------------

static void __pit_prepare_sleep(int hz)
{

// Initialize PIT Ch 2 in one-shot mode
// waiting 1 sec could slow down boot time considerably,
// so we'll wait 1/100 sec, and multiply the counted ticks

    int val = 0;

    unsigned int divisor = 1193182/hz;
    
    val = (in8(0x61) & 0xfd) | 0x1;
    out8(0x61, val);
    out8(0x43, 0xb2);

    out8(0x42,(unsigned char)(divisor & 0xFF));		// LSB
    in8(0x60); // Short delay
    out8(0x42,(unsigned char)(divisor >> 8) & 0xFF); // MSB
}

static void __pit_perform_sleep(void)
{
    
    // Reset PIT one-short counter (start counting)
    int val = 0;
    val = (in8(0x61) & 0xfe);
    out8(0x61, val); // gate low
    val = val | 1;
    out8(0x61, val); // gate high

// Now wait until PIT counter reaches zero
    while((in8(0x61) & 0x20) == 0)
    {
    };
}

// #todo: 
// Definir porta 70h usada nesse arquivo. ??
static unsigned int __apictim_read_command(unsigned short addr)
{
    if( (void *) LAPIC.lapic_va == NULL ){
        panic("__apictim_read_command: LAPIC.lapic_va\n");
    }

    return *( (volatile unsigned int *)(LAPIC.lapic_va + addr));
}

static void __apictim_write_command(unsigned short addr,unsigned int val)
{
    if( (void *) LAPIC.lapic_va == NULL ){
        panic("__apictim_write_command: LAPIC.lapic_va\n");
    }

    *( (volatile unsigned int *)(LAPIC.lapic_va + addr)) = val;
}

void apic_initial_count_timer(int value)
{
    __apictim_write_command( 
        LAPIC_INITIAL_COUNT_TIMER, 
        value);
}

void apic_timer_umasked(void)
{
    unsigned int data = 
        __apictim_read_command(LAPIC_LVT_TIMER);

    __apictim_write_command( 
        LAPIC_LVT_TIMER, 
        data & 0xFFFEFFFF );

	//Divide Configuration Register, to divide by 128 0xA divide by 32 0x8
	//local_apic_write_command( APIC_DIVIDE_TIMER, 0xA);

	// Initial Count Register
	//local_apic_write_command( APIC_INITIAL_COUNT_TIMER, 12345);
	
}

void apic_timer_masked(void)
{
	unsigned int data = __apictim_read_command(LAPIC_LVT_TIMER);
	__apictim_write_command( LAPIC_LVT_TIMER, data | 1 << 16);
}


int apic_timer(void)
{
// Called by enable_apic() in apic.c.

// #todo #bugbug
// e o timer precisa mudar o vetor 
// pois 32 ja esta sendo usado pela redirection table.


// --------------------------------------------------
// Map APIC timer to an interrupt, and 
// by that enable it in one-shot mode.
    unsigned int val = 
        APIC_TIMER_CONFIG_DATA_LVT(
            0  /*one-shot mode*/,
            0  /*umasked*/,
            APIC_TIMER_NULL,
            APIC_TIMER_NULL,
            0,
            APIC_TIMER_NULL,
            0x20  /*vetor*/ );  //32
    __apictim_write_command(LAPIC_LVT_TIMER, val);

// --------------------------------------------------
// Divide Configuration Register, 
// to divide by 16
    __apictim_write_command(LAPIC_DIVIDE_TIMER, 0x3);

// --------------------------------------------------
// Prepare the PIT to sleep for 10ms (10000µs)
// 1193180/100 Hz
    __pit_prepare_sleep(100);
    //__pit_prepare_sleep(1000);

// --------------------------------------------------
// Rest APIC Timer (set counter to -1)
    __apictim_write_command( 
        LAPIC_INITIAL_COUNT_TIMER, 
        0xFFFFFFFF);

// --------------------------------------------------
// Perform PIT-supported sleep
    __pit_perform_sleep();

// --------------------------------------------------
// Stop APIC Timer
    __apictim_write_command( 
        LAPIC_LVT_TIMER, 
        1 << 16 );

// --------------------------------------------------
// Now do the math...
// Get current counter value.
    apic_timer_ticks = 
        __apictim_read_command(LAPIC_CURRENT_COUNT_TIMER);
    // It is counted down from -1, make it positive
    apic_timer_ticks = 0xFFFFFFFF - apic_timer_ticks;
    apic_timer_ticks++;

    //printk("apic_timer_ticks %d\n", apic_timer_ticks);
    printk("Current count: {%d}\n", apic_timer_ticks);

    apic_timer_ticks = 1000;

// ----------------------------------------------
// Finally re-enable timer in periodic mode. But masked.
	val = 
	    APIC_TIMER_CONFIG_DATA_LVT(
	        1  /*periodic mode*/,
	        1  /*masked*/,
	        APIC_TIMER_NULL,
	        APIC_TIMER_NULL,
	        0,
	        APIC_TIMER_NULL,
	        0x20/*vetor*/);
    __apictim_write_command(LAPIC_LVT_TIMER, val);

    // Setting divide value register again not needed by the manuals
    // Although I have found buggy hardware that required it
    __apictim_write_command(LAPIC_DIVIDE_TIMER, 0xa/*0x3*/);

    // Now eax holds appropriate number of ticks, use it as APIC timer counter initializer
    __apictim_write_command(LAPIC_INITIAL_COUNT_TIMER, apic_timer_ticks);

    return 0;
}


