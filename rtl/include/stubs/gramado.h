
// gramado system calls.

// #bugbug: It is not properly stub routines,
// used by shared libraries. It's is o.s. dependent routines.
//


#ifndef __GRAMADO_CALL
#define __GRAMADO_CALL 1



void *gramado_system_call ( 
    unsigned long a, 
    unsigned long b, 
    unsigned long c, 
    unsigned long d );



void rtl_enter_critical_section (void);
void rtl_exit_critical_section (void);

//vamos escrever em uma janela indefinida. NULL.
//provavelmente a janela principal.
int 
rtl_draw_text ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long color, 
    char *string );
    
void rtl_show_backbuffer (void);



#endif


