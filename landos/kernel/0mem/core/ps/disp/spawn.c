

#include <kernel.h>  


void spawn_thread (int tid)
{
    debug_print ("spawn_thread: [TODO] \n");
}

// KiSpawnTask:
// Interface to spawn a thread.

void KiSpawnThread (int tid){

    if ( tid < 0 || tid >= THREAD_COUNT_MAX )
    {
        printf ("KiSpawnThread: TID=%d\n", tid );
        die ();
    }

    spawn_thread (tid);

    panic ("KiSpawnThread\n");
}











