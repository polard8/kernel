
/*
 * File: stubs.c 
 * 
 *    stubs and system calls.
 */

// Stubs are nop functions.
// It's used in dinlink.

#include <stdio.h>
#include <types.h> 
#include <stdarg.h> 
#include <stddef.h>


//system calls.
#include <stubs/gramado.h> 



void *gramado_system_call ( unsigned long a, 
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


