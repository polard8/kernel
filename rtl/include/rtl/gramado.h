
// gramado system calls.

// #bugbug: It is not properly stub routines,
// used by shared libraries. It's is o.s. dependent routines.
// We need to change the name of this document, and change
// the name in ALL apllications.
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

void *
rtl_create_thread ( 
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

#endif


