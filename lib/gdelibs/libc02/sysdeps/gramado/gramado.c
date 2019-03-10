#include <stdio.h>
#include <types.h> 
#include <stdarg.h> 

#include <stddef.h>

//system calls.
#include "gramado.h" 

void *gramado_system_call ( unsigned long ax, 
                            unsigned long bx, 
				            unsigned long cx, 
				            unsigned long dx )
{
    int __ret = 0;	
	
    //System interrupt.
 	
	asm volatile ( " int %1 \n"
		           : "=a"(__ret)	
		           : "i"(0x80), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );

	return (void *) __ret; 
}



