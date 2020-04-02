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



#include <fcntl.h> 
#include <errno.h> 

// #obs
// Talvez essa rotina não possa ser interrompida.
// Podemos entrar na sessão crítica, mas precisamos 
// implementar isso na libc.

//Talvez precisemos configurar o stdout.
 


// #test
// usar ftell e fseek pra calcular o tamanho do arquivo.
// provavlemente fasm esta usando isso e essas funções ainda não funcionam.
 
int main ( int argc, char *argv[] ){

    FILE *fp;
    register int c;
    
    char buffer[1024];
    int nreads = 0;
    int nwrites = 0;



    // fopen.
    // Ok. O arquivo á carregado em ring0.
    // temos que ler com base do fd usando read();
    
    fp = fopen ( (char *) argv[1], "r+" );
    if ( (void *) fp == NULL ){
        printf ("cat: fopen fail\n");
        exit(-1);
    }

    nreads = read ( fileno(fp), buffer, sizeof(buffer) );
    
    if (nreads <=0 ){
        printf ("read fail\n");
        exit(-1);
    }
    
    //
    // Testing size.
    //
    
    fseek(fp, 0, SEEK_END);  // seek to end of file
    size_t size = ftell(fp); // get current file pointer
    fseek(fp, 0, SEEK_SET);  // seek back to beginning of file
    printf (">>>> size %d \n",size);  


    //printf (">>>> %s \n",buffer);        
    
    // 1 = stdout = virtual console.
    nwrites = write ( 1, buffer, sizeof(buffer) );
    
    if (nwrites <=0 ){
        printf ("write fail\n");
        exit(-1);
    }

    return 0;
}




//
// End.
//


