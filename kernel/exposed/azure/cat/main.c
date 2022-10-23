// 'cat' command for Gramado.
// 2022 - Fred Nora.

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
    int bufsize = (4*1024);  //4KB
    //char buffer[1024];
    char buffer[bufsize];
    
    int fd=-1;
// Counters.
    register int nreads = 0;
    register int nwrites = 0;
    size_t size=0;
    //int fdInput = -1;
    //int fdOutput = -1;
    //int i=0;
    //int Max = argc;
    //char *p;

    printf("CAT.BIN: argc %d | argv[0] %s | argv[1] %s\n", 
        argc,       // quantos argumentos 
        argv[0],    // CAT.BIN
        argv[1] );  // FILE.TXT

    if( argc <= 0 ){
        printf("cat: No args\n");
        exit(1);
    }

    if( argc == 1 ){
        printf("cat: We need mor args\n");
        //call usage()
        exit(1);
    }


    // pula o primeiro porque eh o nome do programa.
    
    //for (i=1; i<Max; i++)
    //{
    //    p = argv[i];
    //    if ( *p == '&' )
    //        return 0;


        // Open
        //fp = fopen ( (char *) argv[i], "r+" );
        //fp = (FILE *) fopen ( (char *) argv[1], "a+" );
        //fp = fopen ( "TEST1   ASM", "r+" );
        //if ( (void *) fp == NULL )
        //{
            //printf ("cat: fopen fail\n");
            //perror ("cat: fopen fail  ... testing perror\n");
            //exit (-1);
        //}

        fd = (int) open( (char *) argv[1],0, "a+" );

        //if (fd<0){
        //    return -1;
        //}
            
        // Poisiona no início do arquivo.
        //rewind(fp);

       
        // #todo
        // Deveriamos pegar o tamanho do arquivo e ler somente o 
        // tamanho do arquivo e nao o buffer todo. ??

        // Read
        
        //printf("fd %d \n",fileno(fp) );

        // Get file size.
        //fseek (fp, 0, SEEK_END);
        //int size = ftell (fp);
        //fseek (fp, 0, SEEK_SET);
        //printf (">> size %d \n",size);
        
        //#todo: Create ltell()
        
        lseek(fd,0,SEEK_SET);  //do inicio
        //lseek(fd,200,SEEK_SET);    // do meio
        
        //#todo
        // Precisamos saber o tamanho do arquivo.
        
        //nreads = read( fileno(fp), buffer, sizeof(buffer) );
        //nreads = read( fileno(fp), buffer,  );  //#bugbug: Defined limitation
        nreads = read( fd, buffer, 511 );  
        //nreads = read( fd, buffer, 1500 );
        if (nreads <= 0)
        {
            printf ("cat: read fail\n");
            //exit (-1);
        }

        //#test
        //fgets(buffer,512,fp);

        //int i=0;
        //int C=0;
        //for(i=0; i<32; i++){
        //    C = fgetc(fp);
        //    if(C >= 0x20 && C <= 0x7F)
        //        printf("%c",C);
        //};
        //fflush(stdout);

        // Get file size.
        //fseek (fp, 0, SEEK_END);
        //size = ftell (fp);
        //fseek (fp, 0, SEEK_SET);
        //printf (">> size %d \n",size);

        // Write
        // Write on stdout.
        nwrites = write ( 1, buffer, sizeof(buffer) );
        if (nwrites <= 0)
        {
            printf ("cat: write fail\n");
            //exit(-1);
        }

        //fprintf(stdout,buffer);
        //fflush(stdout);
        
        //printf("OUTPUT: %s \n",buffer);

        // close() ??
        // vai salvar ??

   // };

    return 0;
}


