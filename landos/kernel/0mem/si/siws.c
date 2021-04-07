/*
 * File: siws.c 
 * 
 *     Service Interface - window system service.
 */


#include <kernel.h>




/*
 ******************************* 
 * ipc_send_to_ws:
 * 
 *     Let's send a message to the registered window server.
 *     For it's control thread.
 * 
 */

// #bugbug
// Now the window server is using unix-like sockets.

// Called by KEYBOARD_SEND_MESSAGE() in ps2kbd.c

// OUT:
// <= 0 - The ws is present and we sent the message to it.
// > 0  - The ws PID.

int
si_send_message_to_ws ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{

    struct process_d *__p;

    // #todo
    // Se o ws está rodando, então mandaremos a mensagem para 
    // à fila de mensagem dele.
    // #isso funcionou.
    // O ws recebeu a mensagem de teclado.
    // E é rápido.

    if ( (void *) CurrentDesktop == NULL ){
        debug_print ("si_send_message_to_ws: CurrentDesktop\n");
        return (int) (-1);
    }
        
  
    if ( CurrentDesktop->desktopUsed != 1 || 
         CurrentDesktop->desktopMagic != 1234 )
    {
        debug_print ("si_send_message_to_ws: CurrentDesktop validation\n");
        return (int) (-1);
    }

    //
    // PID
    //
    
    // The ws PID.
    // #bugbug: Is it a valid PID? range?
    if (CurrentDesktop->ws <= 0){
        debug_print ("si_send_message_to_ws: ws PID\n");
        return (int) (-1);
    }

    // The ws process.
    // #todo: 
    // Process validation.

    __p = (struct process_d *) processList[ CurrentDesktop->ws ];
      
    if ( (void *) __p == NULL ){
        debug_print ("si_send_message_to_ws: __p\n");
        return (int) (-1);
    } 

    // used ? magic ?


    // Emergency keys.
    // Sending these keys to the system procedure.
    // See: ps2kbd.c

    switch (msg){

        case MSG_SYSKEYUP:
            
            switch (long1){
                
                case VK_F5:  
                case VK_F6:  
                case VK_F7: 
                case VK_F8:
                    debug_print ("si_send_message_to_ws: >>>> [MSG_SYSKEYUP] to system procedure\n");  
                    __kgwm_ps2kbd_procedure ( 
                        window, 
                        (int) msg, 
                        (unsigned long) long1, 
                        (unsigned long) long2 );  
                    return 0;
                    break;
            };
            break;
    };


    // Send and rotate the queue.

    __p->control->window_list[ __p->control->tail_pos ] = window;
    __p->control->msg_list[ __p->control->tail_pos ]    = msg;
    __p->control->long1_list[ __p->control->tail_pos ]  = long1;
    __p->control->long2_list[ __p->control->tail_pos ]  = long2;

    __p->control->tail_pos++;
    if ( __p->control->tail_pos >= 31 )
    {
        __p->control->tail_pos = 0;
    }

    // Ok.
    return 0;
}



/*
 ******************************* 
 * si_send_longmessage_to_ws:
 * 
 *     Let's send a  long message to the registered window server.
 *     For it's control thread.
 */

// Called by ??

int
si_send_longmessage_to_ws ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2,
    unsigned long long3,
    unsigned long long4 )
{

    struct process_d *__p;

    // #todo
    // Se o ws está rodando, então mandaremos a mensagem para 
    // à fila de mensagem dele.
    // #isso funcionou.
    // O ws recebeu a mensagem de teclado.
    // E é rápido.

    if ( (void *) CurrentDesktop == NULL ){
        debug_print ("si_send_longmessage_to_ws: CurrentDesktop\n");
        return (int) (-1);
    }
        
  
    if ( CurrentDesktop->desktopUsed != 1 || 
         CurrentDesktop->desktopMagic != 1234 )
    {
        debug_print ("si_send_longmessage_to_ws: CurrentDesktop validation\n");
        return (int) (-1);
    }

    //
    // PID
    //
    
    // The ws PID.
    // #bugbug: Is it a valid PID? range?
    if (CurrentDesktop->ws <= 0){
        debug_print ("si_send_longmessage_to_ws: ws PID\n");
        return (int) (-1);
    }

    // The ws process.
    // #todo: 
    // Process validation.

    __p = (struct process_d *) processList[ CurrentDesktop->ws ];
      
    if ( (void *) __p == NULL ){
        debug_print ("si_send_longmessage_to_ws: __p\n");
        return (int) (-1);
    } 

    // used ? magic ?

    // Emergency keys.
    // Sending these keys to the system procedure.
    // See: ps2kbd.c

    switch (msg){

        case MSG_SYSKEYUP:
            
            switch (long1){

                case VK_F5:
                case VK_F6:
                case VK_F7:
                case VK_F8:
                    debug_print ("si_send_longmessage_to_ws: >>>> [MSG_SYSKEYUP] to system procedure\n");  
                    __kgwm_ps2kbd_procedure ( 
                        window, 
                        (int) msg, 
                        (unsigned long) long1, 
                        (unsigned long) long2 );  
                    return 0;
                    break;
            };
            break;
    };


    // Send and rotate the queue.

    __p->control->window_list[ __p->control->tail_pos ] = window;
    __p->control->msg_list[ __p->control->tail_pos ]    = msg;

    __p->control->long1_list[ __p->control->tail_pos ]  = long1;
    __p->control->long2_list[ __p->control->tail_pos ]  = long2;
    __p->control->long3_list[ __p->control->tail_pos ]  = long3;
    __p->control->long4_list[ __p->control->tail_pos ]  = long4;


    __p->control->tail_pos++;
    if ( __p->control->tail_pos >= 31 )
    {
        __p->control->tail_pos = 0;
    }   
 
    // Ok.
    return 0;
}


//
// End.
//



