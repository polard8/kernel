
// gramado system calls.

// #bugbug: It is not properly stub routines,
// used by shared libraries. It's is o.s. dependent routines.
// We need to change the name of this document, and change
// the name in ALL apllications.
//


#ifndef __GRAMADO_CALL
#define __GRAMADO_CALL 1



// Modes.
#define GRAMADO_JAIL        0x00
#define GRAMADO_P1          0x01
#define GRAMADO_HOME        0x02
#define GRAMADO_P2          0x03
#define GRAMADO_CASTLE      0x04
#define GRAMADO_CALIFORNIA  0x05
// ...


// system call
void *gramado_system_call ( 
    unsigned long a, 
    unsigned long b, 
    unsigned long c, 
    unsigned long d );




// input mode
int rtl_get_input_mode(void);
void rtl_set_input_mode(int mode);



//
// == events ===========================================
//

// System messages in the thread's event queue.

#define RTL_WAIT_FOR_EVENTS  1
#define RTL_POOL_FOR_EVENTS  2

//  The buffer for the event elements.
unsigned long RTLEventBuffer[32];

// Get an event from the thread's event queue.
// That old 'get system message'
// Using a buffer
int rtl_get_event (void);

// ===========================================================





void rtl_enter_critical_section (void);
void rtl_exit_critical_section (void);

//
// == thread ===============================
//

void *rtl_create_thread ( 
    unsigned long init_eip, 
    unsigned long init_stack, 
    char *name );

void rtl_start_thread (void *thread);


//vamos escrever em uma janela indefinida. NULL.
//provavelmente a janela principal.
int 
rtl_draw_text ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long color, 
    char *string );
    
void rtl_show_backbuffer (void);



unsigned long rtl_get_system_metrics (int index);

// ms
// tempo total em ms.
// usado para calcular o tempo de execuçao de uma funcao.
unsigned long rtl_get_progress_time(void);


// #bugbug
// Not tested yet.
int 
rtl_copy_text ( 
    unsigned long src, 
    unsigned long dest, 
    int width, 
    int height );

void rtl_reboot(void);

#endif


