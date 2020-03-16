
#include <kernel.h>


// #todo
// Definir as várias opções de mensagens que podem ser exibidas.
// O que mostrar em caso de erro fatal?


/*
 *************************************************
 * panic:
 *     klibc function to show a formated string and hang the system.
 */
 
void panic ( const char *format, ... ){

    register int *varg = (int *) (&format);

    printf ("panic: KERNEL PANIC\n");
    print ( 0, varg );
    die ();
}




