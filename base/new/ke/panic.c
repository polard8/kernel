


#include <kernel.h>    



// This function shows a formated string and 
// hang the system.

void panic ( const char *format, ... )
{
    register int *varg = (int *) (&format);


// Se podemos usar o dispositivo serial para log.
    if ( Initialization.serial_log == TRUE )
    {
        debug_print("panic: \n");
    }

// Se podemos usar o console virtual para log.
    if ( Initialization.console_log == TRUE )
    {
        printf ("panic: KERNEL PANIC\n");
        print ( 0, varg );
    }

// hang
    die();
}



