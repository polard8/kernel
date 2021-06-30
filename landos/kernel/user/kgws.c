
// kgws.c

#include <kernel.h>  

static int EnableKGWS = TRUE;

int kgws_status;
int kgws_ws_PID;
int kgws_ws_status;


// ==========================================================

void kgws_enable(void)
{
    debug_print("kgws_enable: Enable KGWS\n");
         printf("kgws_enable: Enable KGWS\n");
    refresh_screen();
    
    // Sending event messages to the thread associated with the wwf.
    //current_input_mode = INPUT_MODE_SETUP;
    IOControl.useEventQueue = TRUE;
    
    EnableKGWS = TRUE;
}

void kgws_disable(void)
{
    debug_print("kgws_disable: Disable KGWS\n");
         printf("kgws_disable: Disable KGWS\n");

    backgroundDraw(COLOR_RED);

    refresh_screen();
        
    // Using unix-like TTY mode for input.
    // using the stdin.
    // current_input_mode = INPUT_MODE_TTY;
    
    // #bugbug: This is a test yet.
    //IOControl.useEventQueue = FALSE;
    
    EnableKGWS = FALSE;
}




// called by x86_64/x64init.c
// #todo
// Maybe we can use some parametes here.

int KGWS_initialize(void)
{
    debug_print("KGWS_initialize:[TODO]\n");

    //#todo
    //init_logon_manager();
    
    return 0;
}

// ?? Not used yet ??
// Registrar um window server.
int kgwsRegisterWindowServer (int pid)
{
    int Status = 0;

    // ?? Where ??
    if ( kgws_status != 1 )
    {
        Status = 1;
        goto fail;
    }else{
        kgws_ws_PID = (int) pid;
        kgws_ws_status = 1;
        goto done;
    };

fail:
    printf("kgwsRegisterWindowServer: fail\n");
done:
    return 0;
}

// Registrando o processo do window server.
// See: gpid.h
int register_ws_process ( pid_t pid )
{

    if ( pid<0 || pid >= PROCESS_COUNT_MAX )
    {
        debug_print("register_ws_process: [FAIL] pid\n");
        return -1;
    }

    if ( __gpidWindowServer != 0 ){
        debug_print("register_ws_process: [FAIL] __gpidWindowServer\n");
        return -1;
    }

    __gpidWindowServer = (pid_t) pid;

    return 0;
}












