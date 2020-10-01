/*
 * File: panic.c
 *
 * History:
 *     2015 - Created by Fred Nora.
 */


#include <kernel.h>


// #todo
// We need to define some messages here.



/*
 *************************************************
 * panic:
 *     This function shows a formated string and 
 * hang the system.
 */

// Isso funciona em todas as fases e em todos os runlevels.
// porque print nao analisa flags.

void panic ( const char *format, ... )
{
    register int *varg = (int *) (&format);

    printf ("panic: KERNEL PANIC\n");
    print ( 0, varg );
    die();
}


//
// End.
//

