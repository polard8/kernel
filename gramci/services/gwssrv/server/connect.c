// connect.c

//#include <api.h>

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
int register_ws (void){

    // Desktop
    // Getting current desktop;

    // Register.
    // Register window server as the current server for this
    // desktop.


    // Desktop    
    __ws_desktop = (struct desktop_d *) gramado_system_call (519,0,0,0);
    
    if ( (void *) __ws_desktop == NULL ){
        gwssrv_debug_print ("register_ws: __ws_desktop fail\n");
        return (int) (-1);
    }

    // PID
    __ws_pid = (int) getpid();

    if ( __ws_pid < 0 ){
        gwssrv_debug_print ("register_ws: __ws_pid fail \n");
        return (int) (-1);
    }

    // Register this pid as ws.
    gramado_system_call ( 513, __ws_desktop, __ws_pid, __ws_pid );


    __ws_registerd = 1;
    
    // O = OK.
    return 0;
}


//
// End.
//





