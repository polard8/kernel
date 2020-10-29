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


// Clena and panic.
void panic2 ( const char *format, ... )
{
    register int *varg = (int *) (&format);

    // #todo
    // Poderia existir uma flag que indicasse
    // se ja podemos usar esse tipo de recurso grafico.

    backgroundDraw ( (unsigned long) COLOR_RED ); 
    
    printf ("panic: KERNEL PANIC\n");
    print ( 0, varg );
    die();
}


//
// End.
//

