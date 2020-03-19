/*
 * Fle: main.c
 * 
 * crash app for atacama.
 */
 
// #todo
// O comando crash realizará quedas controladas diferentes
// acionadas com as flags da linha de comando.
// outro comando poderá ler amensagem de debug. #todo


#include <types.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>


// #obs
// Talvez essa rotina não possa ser interrompida.
// Podemos entrar na sessão crítica, mas precisamos 
// implementar isso na libc.

//Talvez precisemos configurar o stdout.
 
 
int main ( int argc, char *argv[] ){

    FILE *fp;
    register int c;


    printf ("cat: Initializing ...\n");

    fp = fopen ( (char *) argv[1], "r+" );

    if ( (void *) fp == NULL )
        return -1;     


    //libc_set_output_mode (LIBC_NORMAL_MODE);

	//get current tty stdou_ring0
    //stdout = (FILE *) system_call ( 1000, 0, 0, 0 );


    while ( (c = fgetc(fp)) >= 0 )
        printf ("%c", c);


    printf ("cat: Done.\n");

    return 0;
}

//
// End.
//


