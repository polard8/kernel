
// newos.c
// The interface for the kernel services.
// Probably some of these sysbols will be exported.

#include    "newos.h"


// unsigned long newos_exported_symbols[1024];


void newos_reboot(unsigned long reboot_flags)
{
    sys_reboot();
    //hal_reboot();
}


// See: kgwm.c
int 
newos_register_ws_callbacks(
    pid_t pid,
    unsigned long callback0,
    unsigned long callback1,
    unsigned long callback2 )
{

// Who can do this?
// Only the gwssrv.bin.

    if(pid != KernelProcess->pid){
        panic("newos_register_ws_callbacks: pid");
    }

    //#todo: filter parameters
    wmRegisterWSCallbacks(
        (unsigned long) callback0,
        (unsigned long) callback1,
        (unsigned long) callback2 );

    return 0;
}


unsigned long newos_get_system_metrics(int index)
{
    if(index<0){
        return 0;
    }

    return (unsigned long) sys_get_system_metrics ( (int) index );
}

pid_t newos_getpid(void)
{
    return (pid_t) sys_getpid();
}


// REAL (coloca a thread em standby para executar pela primeira vez.)
// MOVEMENT 1 (Initialized --> Standby).
int newos_start_thread( struct thread_d *thread )
{
    if( (void*) thread == NULL )
        return (-1);

    if(thread->used != TRUE)
        return (-1);

    if(thread->magic != 1234)
        return (-1);

    SelectForExecution ( (struct thread_d *) thread );
    return 0;
}


int newos_get_current_runlevel(void)
{
    return (int) current_runlevel;
}


unsigned long newos_get_memory_size_mb(void)
{
    unsigned long __mm_size_mb=0;
    
    __mm_size_mb = (unsigned long) ( memorysizeTotal/0x400);

    return (unsigned long) __mm_size_mb;
}

// Usado pelo malloc em ring3.

void *newos_alloc_shared_ring3_pages(pid_t pid, int number_of_bytes)
{
    int number_of_pages=0;

// #todo
// pid premission

// #todo
// Check max limit

    if ( number_of_bytes < 0 )
        number_of_bytes = 4096;

    if ( number_of_bytes <= 4096 ){
        return (void *) allocPages(1);
    }

// Alinhando para cima.
    number_of_pages = (int) ((number_of_bytes/4096) + 1);

    return (void *) allocPages(number_of_pages);
}


// 34 - Setup cursor for the current virtual console.
// See: core/system.c
// IN: x,y
// #todo: Essa rotina dever pertencer ao user/

void newos_set_cursor( unsigned long x, unsigned long y )
{

// #todo
// Maybe check some limits.

    set_up_cursor ( 
        (unsigned long) x, 
        (unsigned long) y );
}

