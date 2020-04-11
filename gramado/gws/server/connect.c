
#include <api.h>
#include <gws.h>

// Registered ?
int __ws_registerd = -1;

// Our desktop;
// This structure is defined in the libgui.
struct desktop_d *__ws_desktop;

// Our PID.
int __ws_pid;



// OUT:
// 0   = Ok   
// < 0 =  fail.
int register_ws (void)
{
    // Desktop
    // Getting current desktop;

    // Register.
    // Register window server as the current server for this
    // desktop.
    
    __ws_desktop = (struct desktop_d *) gramado_system_call (519,0,0,0);
    
    __ws_pid = (int) getpid();

    
    // Filter.
    if ( (void*) __ws_desktop == NULL ){
        gde_debug_print ("register_ws: __ws_desktop fail\n");
        return -1;
    }
    
    if ( __ws_pid < 0 ){
        gde_debug_print ("register_ws: __ws_pid fail \n");
        return -1;
    }
    
    // Register.
    
    gramado_system_call ( 513, 
        __ws_desktop, 
        __ws_pid, 
        __ws_pid );


    __ws_registerd = 1;
    
    // O = OK.
    return 0;
}


//
// End.
//





