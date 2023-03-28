
// msgloop.c

#include "init.h"

#define __MSG_COMMAND  40

// The tid of the caller.
// Sent us a system message.
static int caller_tid =-1;

//-----------------------------------------

static int __idlethread_loop(void);
static void do_hello(int src_tid);

// local
static int 
__Procedure ( 
    void *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );

// ===========================

// #test Hello.
// Responding the hello.
// Hey init, are you up?
static void do_hello(int src_tid)
{
    int dst_tid = src_tid;

    //printf("init.bin: 44888 received | sender=%d receiver=%d\n",
    //    RTLEventBuffer[8],   //sender (the caller)
    //    RTLEventBuffer[9] ); //receiver

    printf("init.bin: [44888] Hello received from %d\n", 
        src_tid );

    //if (dst_tid<0)
        //return;

// -------------
// Reply: 
// Sending response
// Sending back the same message found into the buffer.
// message back to caller.
    rtl_post_system_message( 
        (int) dst_tid,
        (unsigned long) &RTLEventBuffer[0] );
}


// local
// #todo: change this name.
static int 
__Procedure ( 
    void *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{
    if (msg<0){
        return -1;
    }

    switch (msg){

// Start a client.
// It's gonna wor only if the is already running.
// range: 4001~4009 

    case __MSG_COMMAND:
        //printf("init.bin: MSG_COMMAND %d \n",long1);
        switch (long1)
        {
            case 4001:  //app1
                printf("init.bin: 4001\n");
                rtl_clone_and_execute("terminal.bin");
                break;
            case 4002:  //app2
                printf("init.bin: 4002\n");
                rtl_clone_and_execute("gdm.bin");
                break;
            case 4003:  //app3
                printf("init.bin: 4003\n");
                rtl_clone_and_execute("editor.bin");
                break;
            case 4004:  //app4
                //printf("init.bin: 4004\n");
                //rtl_clone_and_execute("reboot.bin");
                break;
            case 4005:  //app5
                //printf("init.bin: 4005\n");
                //rtl_clone_and_execute("terminal.bin");
                break;
            case 4006:  //app6
                //printf("init.bin: 4006\n");
                //rtl_clone_and_execute("gdm.bin");
                break;
            case 4007:  //app7
                //printf("init.bin: 4007\n");
                //rtl_clone_and_execute("editor.bin");
                break;
            case 4008:  //app8
                //printf("init.bin: 4008\n");
                //rtl_clone_and_execute("reboot.bin");
                break;
            default:
                break;
        };
        break;

    // 'Hello' received. Let's respond.
    case 44888:
        do_hello(caller_tid);
        break;

    case 55888:
        //rtl_reboot();
        break;

    // #todo
    //case MSG_YIELD:
        //rtl_yield();
        //break;

    // ...

    default:
        break;
    };
    
    return 0;
}


static int __idlethread_loop(void)
{
// Get input from idlethread.

// #todo
// Get the id of the caller.
// Get the message code.
// Who can call us?

// Nessa hora ja não nos preocupamos mais com essa thread.
// Ele receberá algumas mensagens eventualmente.
    while (TRUE){
        //if( isTimeToQuit == TRUE )
            //break;
        if ( rtl_get_event() == TRUE )
        {
            // Get caller's tid.
            caller_tid = (int) ( RTLEventBuffer[8] & 0xFFFF );
            // Dispatch.
            __Procedure ( 
                (void*) RTLEventBuffer[0], 
                RTLEventBuffer[1], 
                RTLEventBuffer[2], 
                RTLEventBuffer[3] );
            //#test
            //rtl_yield();
        }
    };

    return 0;
}


// We're not using the unix-sockets
// just like in a regular Gramado server. 
// We're just getting messages in the threads message queue.
int run_server(void)
{
    int IdleLoopStatus = -1;

    //# no focus!
    //rtl_focus_on_this_thread();

    IdleLoopStatus = (int) __idlethread_loop();
    if (IdleLoopStatus<0){
        printf ("init.bin: loop fail\n");
    }

    return 0;
}


