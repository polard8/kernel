
// callback.c

#include "gwsint.h"

static unsigned long callback_counter=0;

static inline void do_restorer(void);
static void callback_compose(void);
static void callback_procedure(void);

//========================================================


//========================================================
// The callback restorer.
static inline void do_restorer(void)
{
    asm ("int $198");
}

static void callback_compose(void)
{
    if (__compose_lock == TRUE)
        return;

    __compose_lock = TRUE;
    compose();
    __compose_lock = FALSE;
}

//========================================================
// Callback procedure.
static void callback_procedure(void)
{
// #bugbug
// We don't wanna mess with the variables 
// in use by the window server.
// Changing the state of some variable can cause problems.
// + Use locks.
// + Use encapsulation.
// + Don't call compose() if the window server is running in the
//   midle of this routine.

    callback_counter++;

    if ( (void*) window_server == NULL ){
        goto restore;
    }
    if (window_server->initialized != TRUE){
        goto restore;
    }

// gui
    if ( (void*) gui == NULL ){
        goto restore;
    }
// window server
    if ( (void*) window_server == NULL ){
        goto restore;
    }
    if (window_server->graphics_initialization_status != TRUE){
        goto restore;
    }
// window manager
    if (WindowManager.initialized != TRUE){
        goto restore;
    }

//
// Compose
//

// #bugbug
// This is external routine called by the procedure,
// In this routine we're gonna find all the variables
// affected by the routine.
// Maybe we need a sort of lock here to synchronize it.
    callback_compose();

restore:
    do_restorer();
//fail
    while (1){
        printf("."); 
        fflush(stdout);
    }
}
//========================================================


void callbackInitialize(void)
{
    unsigned long address = (unsigned long) &callback_procedure;
    int pid = getpid();
    unsigned long lpid = (pid & 0xFFFFFFFF);

// Each 16 ms. 60fps
    //unsigned long ms = 2;        // 500 fps
    unsigned long ms = 16;   // 60 fps
    //unsigned long ms = 500;
    //unsigned long ms = 999;

    sc82(
        44000,
        (unsigned long) address,  // ring 3 address
        (unsigned long) lpid,         // pid
        (unsigned long) ms );       // desired ms.
}

