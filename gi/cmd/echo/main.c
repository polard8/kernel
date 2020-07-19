// echo for Animal.


#include <stdio.h>



int main ( int argc, char *argv[] ){

    register int i, start, nflg;

    start = 1;
    nflg = 0;

    // echo -n 
    // NO new line.
    if ( argc > 1 && 
         argv[1][0] == '-' && 
         argv[1][1] == 'n')
    {
        start++;
        nflg++;
        argc--;
        //argv++;
    }


    for (i=start; i<argc; i++)
    {
        fputs (argv[i], stdout);

        if (i < argc-1)
            putchar(' ');
    }

    // new line and flush
    if (nflg == 0){
        putchar('\n');
    
    // just flush.
    }else{
        fflush(stdout);
    };

    exit(0);
}


