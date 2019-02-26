//signal.c 


#include <signal.h>
//system calls.
#include <stubs/gramado.h> 


//POSIX.1-2001, POSIX.1-2008, C89, C99.
sighandler_t signal (int signum, sighandler_t handler)
{
    return handler;  //#todo
}

int sigaction ( int signum, 
			    const struct sigaction *act,
                struct sigaction *oldact )
{
    return -1; //#todo
}





