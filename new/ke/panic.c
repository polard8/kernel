


#include <kernel.h>    



// This function shows a formated string and 
// hang the system.

void panic ( const char *format, ... )
{
    register int *varg = (int *) (&format);

    printf ("panic: KERNEL PANIC\n");
    print ( 0, varg );
    die();
}



