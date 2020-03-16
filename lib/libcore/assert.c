//Credits: serenity os

#include <assert.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//extern "C" {

#ifdef DEBUG

void 
__assertion_failed ( const char* msg, 
                     const char* file, 
                     unsigned line, 
                     const char* func )
{
    printf ("USERSPACE(%d) ASSERTION FAILED: ", getpid() );
    printf (" %s \n %s:%u in %s \n",  msg, file, line, func );
    
    stdlib_die ( "__assertion_failed: *hang");
    // Suspended.
    // fprintf (stderr, "ASSERTION FAILED: %s\n%s:%u in %s\n", msg, file, line, func);
    //abort ();
    //for (;;)
        
}

#endif


//}



