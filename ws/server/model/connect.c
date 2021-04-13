// connect.c



#include <gws.h>



// Registered ?
int __ws_registered = -1;

// Destop structure.
struct desktop_d *__ws_desktop;

// Our PID.
int __ws_pid;


/*
 *****************************************************
 * register_ws:
 *     This routine is gonna register this window server.
 *     It's gonna change the kernel input mode.
 *     Service 519: Get the current desktop structure pointer.
 *     Service 513: Register this window server.
 */


// OUT:
// 0   = Ok   
// < 0 =  fail.

int register_ws (void){

    // Desktop
    // Getting current desktop;

    // Register.
    // Register window server as the current server for this
    // desktop.


    //
    // == Desktop =================================================
    //

    // Desktop 
    // Getting the current desktop structure pointer.
    __ws_desktop = (struct desktop_d *) gramado_system_call (519,0,0,0);
    
    if ( (void *) __ws_desktop == NULL ){
        gwssrv_debug_print ("register_ws: __ws_desktop fail\n");
        return (int) (-1);
    }

    //
    // == Register =================================================
    //

    // PID
    __ws_pid = (int) getpid();

    if ( __ws_pid < 0 ){
        gwssrv_debug_print ("register_ws: __ws_pid fail \n");
        return (int) (-1);
    }

    // Register this pid as ws.
    gramado_system_call ( 513, __ws_desktop, __ws_pid, __ws_pid );

    // flag.
    __ws_registered = 1;
    
    // O = OK.
    return 0;
}


//
// End.
//





