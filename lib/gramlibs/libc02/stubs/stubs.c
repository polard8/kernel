#include <stdio.h>
#include <types.h> 
#include <stdarg.h> 

#include <stddef.h>

//system calls.
#include <stubs/gramado.h> 

void *gramado_system_call ( unsigned long ax, 
                            unsigned long bx, 
				            unsigned long cx, 
				            unsigned long dx )
{
    int Ret = 0;	
	
    //System interrupt.
 	
	asm volatile ( " int %1 \n"
		           : "=a"(Ret)	
		           : "i"(0x80), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );

	return (void *) Ret; 
}



