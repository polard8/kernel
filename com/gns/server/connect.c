// connect.c



#include <gns.h>



// Registered ?
int __ns_registerd = -1;

// Our desktop;
// This structure is defined in the libgui.
struct desktop_d *__ns_desktop;

// Our PID.
int __ns_pid;



// OUT:
// 0   = Ok   
// < 0 =  fail.
int register_ns (void){

    // Desktop
    // Getting current desktop;

    // Register.
    // Register network server as the current server for this
    // desktop.


    // Desktop    
    __ns_desktop = (struct desktop_d *) gramado_system_call (519,0,0,0);
    
    if ( (void *) __ns_desktop == NULL ){
        debug_print ("register_ns: __ns_desktop fail\n");
        return (int) (-1);
    }

    // PID
    __ns_pid = (int) getpid();

    if ( __ns_pid < 0 ){
        debug_print ("register_ns: __ns_pid fail \n");
        return (int) (-1);
    }

    // Register this pid as ns.
    gramado_system_call ( 
        (unsigned long) 521, 
        (unsigned long) __ns_desktop, 
        (unsigned long) __ns_pid, 
        (unsigned long) __ns_pid );

    __ns_registerd = TRUE;
    
    // O = OK.
    return 0;
}


//
// End.
//





