/*
 * File: main.c
 * 
 * return true;
 */


#include <types.h>
#include <stdio.h>
 
 
 
int main ( int argc, char *argv[] )
{
	return 1;
	

    //#todo
    //undefined references.

    /*
    char ____buf[512];
    while(1)
    {
         fseek(stderr, 0, SEEK_SET);
         sprintf(____buf,"true: THIS IS A MAGIC STRING!\n");
         fputs((const char *) ____buf,stderr);
    }
    */

	/*
    
    int ____this_tty_id = -1;
    char buf2[128]; 
    
    // link by pid
    // #todo: Create the function link_by_pid()
    // Obs: Os sistemas costumam criar um tty e 'linkar'
    // quando chamam fork, pois fork faz o filho herdar os 
    // arquivos abertos.
    
    gramado_system_call ( 267,
        getpid(), 
        getppid(), //terminal
        0 );


    ____this_tty_id = gramado_system_call ( 266, getpid(), 0, 0 );
    printf ("The tty for this process is %d\n", ____this_tty_id);



    
    int nwrite = -1; // bytes escritos.
    size_t __w_size2=0;
    while(1)
    {
        // Escrevendo na tty desse processo e na tty slave pra leitura.
        nwrite = write_ttyList ( ____this_tty_id, 
                     buf2, 
                     __w_size2 = sprintf (buf2,"THIS IS A MAGIC STRING\n")  );
    
        if (nwrite > 0)
           return 0;//goto __ok;
    
        //yield
    }
    */

    /*
    int nread=-1;
    size_t __r_size2=0;
    while(1)
    {
        // Escrevendo na tty desse processo e na tty slave pra leitura.
        nread = read_ttyList ( ____this_tty_id, 
                     buf2, 
                     sizeof(buf2) );
    
        if (nread > 0){
            printf("%s\n",buf2);  //stdout
        }
    }
    */
 
    //
    // ==================== cut =================
    //

//__ok:
    /*
    FILE *fp;
    
    fp = fopen ("gramado.txt", "w+");
    if(!fp){
        printf("true: fp\n"); return 1;
    }

	printf ("true: test\n");
    char buf[512];
    while(1){

        //#bugbug
        //Se não usar o fseek dá um bug sinistro ...
        //provavelmente começamos escrever na memória para
        //além do buffer da stream ...

        fseek(fp, 0, SEEK_SET);   // seek back to beginning of file    
        //fprintf(fp,"true: THIS IS A MAGIC STRING!\n");
        sprintf(buf,"true: THIS IS A MAGIC STRING!\n");
        fputs((const char *) buf,fp);
    }
	printf ("true: done\n");    
    return 0;
    */
    
    /*
    
    int c;
    while(1){
		
		fseek(fp, 0, SEEK_SET);   // seek back to beginning of file
        //printf ("test\n");
        c = fgetc(fp);
        if(c != EOF){
            printf("%c",c);
            fflush(stdout);
        }
    }
    
    
    return 1;  //true.
    */
}


//
// End.
//


