

#include <kernel.h>  

// prototype
void *gde_extra_services ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 );


// Services abouve 256.
// Helper function called by sci0().
void *gde_extra_services ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{
	//nothing
	return NULL;
}




void *sci0 ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{

    struct process_d *p;

    unsigned long *message_address = (unsigned long *) arg2;

    unsigned long *a2 = (unsigned long*) arg2;
    unsigned long *a3 = (unsigned long*) arg3;
    unsigned long *a4 = (unsigned long*) arg4;

    char *aa2 = (char *) arg2;
    char *aa3 = (char *) arg3;
    char *aa4 = (char *) arg4;

    int desktopID=0;


    // #debug
    debug_print("sc0:\n");
    printf("sc0:\n");
    refresh_screen();

    g_profiler_ints_gde_services++;

    // Profiling in the process structure.

    if (current_process<0)
        panic("sci0: current_process\n");

    p = (struct process_d *) processList[current_process];

    if ( (void*) p == NULL )
        panic("sci0: p\n");

    // Counting ...
    p->syscalls_counter++;


// extra services

    if ( number > 256 ){
        //return (void *) gde_extra_services(number,arg2,arg3,arg4);
        return NULL;
    }


// Switch

    switch (number){
    default: return NULL;
    };

done:
    return NULL;
}



void *sci1 ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{
	//nothing
	return NULL;
}

void *sci2 ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{
	//nothing
	return NULL;
}




void nothing4(void){}
void nothing5(void){}
void nothing6(void){}
void nothing7(void){}
void nothing41(void){}
void nothing51(void){}
void nothing61(void){}
void nothing71(void){}



















