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
 

// Funcionou.
 
int main ( int argc, char *argv[] ){

    FILE *fp;
    register int c;
    
    char buffer[1024];
    
    
    // #todo
    // validation
    
    
    // fopen.
    // Ok. O arquivo á carregado em ring0.
    // temos que ler com base do fd usando read();
    
    fp = fopen ( (char *) argv[1], "r+" );
    
    if ( (void *) fp == NULL )
    {
        printf("cat: fopen fail\n");
        exit(-1);
        //return -1;     
    }




    read ( fileno(fp), buffer, sizeof(buffer) );

    printf (">>>> %s \n",buffer);
    
    // show
    
    //while ( (c = fgetc(fp)) >= 0 )
        //printf ("%c", c);




    return 0;
    
    
    //
    //  =====  tests  =======
    //

    /*
     
    //testando open()
    int fd = -1;
    
    char *buffer = (char *) calloc(100, sizeof(char));     
    
    
    fd = open ("init.ini", O_RDONLY | O_CREAT, 0);  
    if ( fd < 0 ){
        printf ("cat: open() fail \n");
        exit(-1);
    }
    printf("opened the fd = %d\n", fd); 
    
 
    int sz = (int) read (fd, buffer, 10); 
    
    printf("called read ( %d, buffer, 10).  returned that"
         " %d bytes  were read.\n", fd, sz); 
    
    buffer[sz] = '\0'; 
    printf("Those bytes are as follows: %s \n", buffer); 

   //...
   
    sprintf(buffer,"MAGIC STRING \n ... ");
    write (fd, buffer, strlen(buffer));


    int sz2 = (int) read (fd, buffer, 10); 
    
    printf("called read ( %d, buffer, 10).  returned that"
         " %d bytes  were read.\n", fd, sz2); 
    
    buffer[sz2] = '\0'; 
    printf("Those bytes are as follows: %s \n", buffer); 
    
    //close(fd);
    printf("fim do teste...\n");
    return 0;

    */
    
}




//
// End.
//


