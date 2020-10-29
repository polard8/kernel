/*
[ Input ]
The Window Server has basically two kinds of input:
The first one is the hardware input that come from the kernel or from the device drivers.
And the second one is the requests that come from the clients.
---
The hardware input will affect the window with focus. So it will affect the client that this window belongs to. So, we need to put this kind of message into the client's queue.
When a client  request the next event, the window server will check the queue that belong to this client.
*/

char __system_message_buffer[512];


// get system message
// it comes from the kernel.
// it is hardware events.
// send the message to the active client queue.
// the event affects the window with focus and its client.

/*
int 
gwssrv_get_system_message(void);

int 
gwssrv_get_system_message(void)
{
    unsigned long *message_buffer = (unsigned long *) &__system_message_buffer[0];   

    
    int ClientWithFocus;
    int WindowWithFocus;

    ClientWithFocus = gwssrv_get_client_with_focus();
    WindowWithFocus = gwssrv_get_window_with_focus();
    
    //
    // Get system message
    //    

    // Get message from kernel.
    gde_enter_critical_section();
    gramado_system_call ( 111,
        (unsigned long) &message_buffer[0],
        (unsigned long) &message_buffer[0],
        (unsigned long) &message_buffer[0] );
    gde_exit_critical_section();


   //
   // Put the message into the client's queue
   //

    struct gws_client_d *client;
        
    //ponteiro para a estrutura do cliente com o foco
    client = (void*) clientList[ClientWithFocus];
    
    client->window[tail] = message_buffer[0];
    client->msg[tail]    = message_buffer[1];
    client->long1[tail]   = message_buffer[2];
    client->long2[tail] = message_buffer[3];
    //
    
    //#todo
    // circular o offset
    tail++
    if(tail >?)tail=0;
    
}
*/



