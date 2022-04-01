// 'cat' command for Gramado.

// rtl
#include <rtl/gramado.h>
#include <types.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


int main ( int argc, char *argv[] )
{
    FILE *fp;
    char buffer[1024];
    //char buffer[2048];

    // Counters.
    register int nreads  = 0;
    register int nwrites = 0;

    size_t size=0;
    
    //int fdInput = -1;
    //int fdOutput = -1;
    
    //int i=0;
    //int Max = argc;
    //char *p;

    // pula o primeiro porque eh o nome do programa.
    
    //for (i=1; i<Max; i++)
    //{
    //    p = argv[i];
    //    if ( *p == '&' )
    //        return 0;

        // Open
        //fp = fopen ( (char *) argv[i], "r+" );
        fp = fopen ( (char *) argv[1], "r+" );
        if ( (void *) fp == NULL )
        {
            printf ("cat: fopen fail\n");
            //perror ("cat: fopen fail  ... testing perror\n");
            exit (-1);
        }
        
       
        // #todo
        // Deveriamos pegar o tamanho do arquivo e ler somente o 
        // tamanho do arquivo e nao o buffer todo. ??

        // Read
        nreads = read ( fileno(fp), buffer, sizeof(buffer) );
        if ( nreads <= 0 ){
            printf ("cat: read fail\n");
            exit (-1);
        }

        // Get file size.
        fseek (fp, 0, SEEK_END);
        size = ftell (fp);
        fseek (fp, 0, SEEK_SET);
        printf (">> size %d \n",size);

        // Write
        nwrites = write ( 1, buffer, sizeof(buffer) );
        if ( nwrites <= 0 ){
            printf ("cat: write fail\n");
            exit(-1);
        }

        // close() ??
        // vai salvar ??

   // };

    return 0;
}


