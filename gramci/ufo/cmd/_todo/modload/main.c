
/*
  
# modload for gramado
# vamos carregar e ligar dinamicamente e inicializar um modulo do kernel. 
# (ring0)
*   
 */

/*
 * Fle: main.c
 * 
 * cat command for Gramado.
 */


#include <types.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>



/*
int load_module ( char *name );
int load_module ( char *name )
{
    //todo system call	
    return -1;
}
*/

/*
int unload_module ( char *name );
int unload_module ( char *name )
{
    //todo system call
    return -1;
}
*/

// #obs
// Talvez essa rotina não possa ser interrompida.
// Podemos entrar na sessão crítica, mas precisamos 
// implementar isso na libc.

//Talvez precisemos configurar o stdout.
 
 
int main ( int argc, char *argv[] ){

    FILE *fp;
    register int c;


    printf ("modload: Initializing ...\n");

    fp = fopen ( (char *) argv[1], "r+" );

    if ( (void *) fp == NULL )
        return -1;     


    //libc_set_output_mode (LIBC_NORMAL_MODE);

	//get current tty stdou_ring0
    //stdout = (FILE *) system_call ( 1000, 0, 0, 0 );


    //while ( (c = fgetc(fp)) >= 0 )
       // printf ("%c", c);


    printf ("modload: Done.\n");

    return 0;
}

//
// End.
//


