

#include <kernel.h>  



int init_logoff (int mode)
{
	return 0;
}

// See: gpid.h
int register_logoff_process ( pid_t pid ){

    if (pid<0 || pid >= PROCESS_COUNT_MAX ){
        debug_print("register_logoff_process: pid fail\n");
        return -1;
    }

    // Global variable.

    if ( __gpidLogoff != 0 ){
        debug_print("register_logoff_process:\n");
        return -1;
    }

    __gpidLogoff = (pid_t) pid;
    
    return 0;
}







