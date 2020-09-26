
/*
 * File: stubs.c 
 * 
 *    stubs and system calls.
 */

// Stubs are nop functions.
// It's used in dinlink.


// #bugbug: It is not properly stub routines,
// used by shared libraries. It's is o.s. dependent routines.


#include <stdio.h>
#include <types.h> 
#include <stdarg.h> 
#include <stddef.h>


//system calls.
#include <stubs/gramado.h> 

#include <sysdeps/gramado/syscall.h>



void *gramado_system_call ( 
    unsigned long a, 
    unsigned long b, 
    unsigned long c, 
    unsigned long d )
{
    int __Ret = 0;

    //System interrupt.

    asm volatile ( " int %1 \n"
                 : "=a"(__Ret)
                 : "i"(0x80), "a"(a), "b"(b), "c"(c), "d"(d) );

    return (void *) __Ret; 
}



//P (Proberen) testar.
void rtl_enter_critical_section (void){

    int S=0;

    // Pega o valor do spinlock rpincipal.
    while (1){
        S = (int) gramado_system_call ( SYSTEMCALL_GET_KERNELSEMAPHORE, 
                      0, 0, 0 );
                      
		// Se deixou de ser 0 então posso entrar.
		// Se ainda for 0, continuo no while.
        if ( S == 1 ){ goto done; }
        
        //#wait
        gramado_system_call (265,0,0,0); //yield thread.
    };

    //Nothing

done:
    //Muda para zero para que ninguém entre.
    gramado_system_call ( SYSTEMCALL_CLOSE_KERNELSEMAPHORE, 0, 0, 0 );
    return;
}


//V (Verhogen)incrementar.
void rtl_exit_critical_section (void)
{
	//Hora de sair. Mudo para 1 para que outro possa entrar.
    gramado_system_call ( SYSTEMCALL_OPEN_KERNELSEMAPHORE, 0, 0, 0 );
}


//vamos escrever em uma janela indefinida. NULL.
//provavelmente a janela principal.
int 
rtl_draw_text ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long color, 
    char *string )
{

    unsigned long msg[8];

    msg[0] = (unsigned long) 0; //window;
    msg[1] = (unsigned long) x;
    msg[2] = (unsigned long) y;
    msg[3] = (unsigned long) color;
    msg[4] = (unsigned long) string;
    // ...

    return (int) gramado_system_call ( SYSTEMCALL_DRAWTEXT, 
                    (unsigned long) &msg[0], 
                    (unsigned long) &msg[0], 
                    (unsigned long) &msg[0] );
}


/*
 *************************************
 * rtl_show_backbuffer:
 *     Refresh Screen.
 *     Passa o conteúdo do backbuffer para o lfb. 
 */

void rtl_show_backbuffer (void)
{
    // #todo
    // trocar o nome dessa systemcall.
    // refresh screen será associado à refresh all windows.
    
    gramado_system_call ( SYSTEMCALL_REFRESHSCREEN, 0, 0, 0 );
}



