/*
 * File: sins.c 
 * 
 *     Service Interface - Network service. 
 */


#include <kernel.h>



/*
 ********************************************
 * si_send_to_ns:
 *     Send a message to the ns if it is present.
 * 
 */

// #bugbug
// Now the window server is using unix-like sockets.

// OUT:
// <= 0 - The ns is present and we sent the message to it.
// > 0  - The ns PID.

int
si_send_to_ns ( 
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

    if ( (void *) CurrentDesktop == NULL )
    {
        debug_print ("si_send_to_ns: [FAIL] CurrentDesktop\n");
        return -1;
    }
        
  
    if ( CurrentDesktop->desktopUsed != 1 || 
         CurrentDesktop->desktopMagic != 1234 )
    {
        debug_print ("si_send_to_ns: [FAIL] CurrentDesktop validation\n");
        return -1;
    }

    //
    // PID
    //
    
    // The ns PID.
    // #bugbug: Is it a valid PID? range?
    if (CurrentDesktop->ns <= 0)
    {
        debug_print ("si_send_to_ns: ns PID\n");
        return (int) (-1);
    }

    // The ws process.
    // #todo: 
    // Process validation.

    __p = (struct process_d *) processList[ CurrentDesktop->ns ];
      
    if ( (void *) __p == NULL )
    {
        debug_print ("si_send_to_ns: __p\n");
        return (int) (-1);
    } 

    // used ? magic ?
    
    __p->control->window_list[ __p->control->tail_pos ] = window;
    __p->control->msg_list[ __p->control->tail_pos ]    = msg;
    __p->control->long1_list[ __p->control->tail_pos ]  = long1;
    __p->control->long2_list[ __p->control->tail_pos ]  = long2;


    __p->control->tail_pos++;
    if ( __p->control->tail_pos >= 31 )
        __p->control->tail_pos = 0;
        
 
    //
    // Ok.
    // 

    return 0;
}





