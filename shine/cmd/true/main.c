/*
 * File: main.c
 * 
 * return true;
 */


#include <types.h>
#include <stdio.h>
 
 
 
int main ( int argc, char *argv[] )
{

    int ____this_tty_id = -1;
    char buf[128]; 
    

    // link by pid
    // #todo: Create the function link_by_pid()
    // Obs: Os sistemas costumam criar um tty e 'linkar'
    // quando chamam fork, pois fork faz o filho herdar os 
    // arquivos abertos.
    
    gramado_system_call ( 267,
        getpid(),    // master (shell?)
        getppid(),   // slave pai (terminal? init?)
        0 );

    
    
    ____this_tty_id = gramado_system_call ( 266, getpid(), 0, 0 );
    printf ("The tty for this process is %d\n", ____this_tty_id);

    int nwrite = -1; // bytes escritos.
    size_t __w_size2;
    
    while(1)
    {
        // Escrevendo na tty desse processo e na tty slave pra leitura.
        nwrite = write_ttyList ( ____this_tty_id, 
                     buf, 
                     __w_size2 = sprintf (buf,"THIS IS A MAGIC STRING\n")  );
    
        if (nwrite > 0)
           goto __ok;
    }


__ok:

	/*
	int c;
    while(1){
        //printf ("test\n");
        //c = fgetc(stdin);
        //if(c != EOF){
        //    printf("%c",c);
        //    fflush(stdout);
        //}
    }
    */
    
    return 1;  //true.
}


//
// End.
//


