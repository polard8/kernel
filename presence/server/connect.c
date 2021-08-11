// connect.c
// Register the window server in the system.

#include <gws.h>


// Registered ?
int __ws_registered = -1;

// Destop structure.
// Essa estrutura é válida??
// Talvez a gente nem tenha isso para o servidor.
//struct desktop_d *__ws_desktop;
void *__ws_desktop;

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
// == Desktop ==================
//

    // Desktop 
    // Getting the current desktop structure pointer.

    __ws_desktop = (void *) gramado_system_call (519,0,0,0);
    if ( (void *) __ws_desktop == NULL ){
        gwssrv_debug_print ("register_ws: [FAIL] __ws_desktop fail\n");
        
        // #debug
        printf ("register_ws: [FAIL] __ws_desktop fail\n");
        exit(1);
        
        return (int) (-1);
    }

//
// == Register =====================
//

    // PID
    // Get the PID of the server.
    __ws_pid = (int) getpid();
    if ( __ws_pid < 0 ){
        
        gwssrv_debug_print ("register_ws: [FAIL] __ws_pid fail \n");

        // #debug
        printf ("register_ws: [FAIL] __ws_pid fail \n");
        exit(1);

        return (int) (-1);
    }

    // Register this PID of the current window server.
    // #todo
    // We need to check the return value.
    // int Status = -1;
    
    gramado_system_call ( 
        513, 
        __ws_desktop, 
        __ws_pid, 
        __ws_pid );

    // flag.
    __ws_registered = TRUE;

    // O = OK.
    return 0;
}


//
// End.
//





