/*
 * File: main.c
 * 
 * #todo: Porting fasm to Gramado.
 */


// rtl
#include <types.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> 
#include <errno.h> 



// #obs
// Talvez essa rotina não possa ser interrompida.
// Podemos entrar na sessão crítica, mas precisamos 
// implementar isso na libc.

//Talvez precisemos configurar o stdout.
 

extern void fasm_main (int argc, char *argv[]);


//
// main
//
 
int main ( int argc, char *argv[] ){


    printf ("fasm: Initializing ...\n");
    
    
    // See:
    // fasm.asm
    //
    // IN: 
    // It needs to be in: [esp+4] and [esp+8]
    
    fasm_main (argc,argv);
    
    printf ("fasm: Done\n");


    /*
    FILE *fp;
    register int c;
    
    char buffer[1024];
    int nreads = 0;
    int nwrites = 0;
   */


   /*

    // fopen.
    // Ok. O arquivo á carregado em ring0.
    // temos que ler com base do fd usando read();
    
    fp = fopen ( (char *) argv[1], "r+" );
    if ( (void *) fp == NULL ){
        printf ("fasm: fopen fail\n");
        exit(-1);
    }

    nreads = read ( fileno(fp), buffer, sizeof(buffer) );
    
    if (nreads <=0 ){
        printf ("read fail\n");
        exit(-1);
    }

    //printf (">>>> %s \n",buffer);        
    
    // 1 = stdout = virtual console.
    nwrites = write ( 1, buffer, sizeof(buffer) );
    
    if (nwrites <=0 ){
        printf ("write fail\n");
        exit(-1);
    }

    */

    return 0;
}




//
// End.
//


