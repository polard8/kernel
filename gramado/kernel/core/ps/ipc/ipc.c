/*
 * File: ps/ipc/ipc.c 
 *
 * 
 * Description:
 *     IPC - ( Inter-Process Comunication ).    
 *     ring 0
 * 
 * History:
 *     2015 - Created by Fred Nora.
 */


// See:
// https://www.drdobbs.com/interprocess-communication-the-l4-micro/184402030
// ...



#include <kernel.h>


// Encapsulation.
int ipcStatus; 





int
ipc_send_longmessage_to_ws ( 
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
        debug_print ("ipc_send_to_ws: CurrentDesktop\n");
        return -1;
    }
        
  
    if ( CurrentDesktop->desktopUsed != 1 || 
         CurrentDesktop->desktopMagic != 1234 )
    {
        debug_print ("ipc_send_to_ws: CurrentDesktop validation\n");
        return -1;
    }

    //
    // PID
    //
    
    // The ws PID.
    // #bugbug: Is it a valid PID? range?
    if (CurrentDesktop->ws <= 0){
        debug_print ("ipc_send_to_ws: ws PID\n");
        return (int) (-1);
    }

    // The ws process.
    // #todo: 
    // Process validation.

    __p = (struct process_d *) processList[ CurrentDesktop->ws ];
      
    if ( (void *) __p == NULL ){
        debug_print ("ipc_send_to_ws: __p\n");
        return (int) (-1);
    } 

    // used ? magic ?
    
  
    switch (msg)
    {
        case MSG_SYSKEYUP:
            
            switch (long1){
                
                // Emergency keys.
                // Sending these keys to the system procedure.
                case VK_F5: 
                case VK_F6: 
                case VK_F7: 
                case VK_F8:
                    debug_print ("ipc_send_to_ws: >>>> [MSG_SYSKEYUP] to system procedure\n");  
                    __local_ps2kbd_procedure ( window, 
                        (int) msg, 
                        (unsigned long) long1, 
                        (unsigned long) long2 );  
                    return 0;
                    break;
            };
            break;
    };
    
    
    //
    // Send
    //
    
    __p->control->window_list[ __p->control->tail_pos ] = window;
    __p->control->msg_list[ __p->control->tail_pos ]    = msg;

    __p->control->long1_list[ __p->control->tail_pos ]  = long1;
    __p->control->long2_list[ __p->control->tail_pos ]  = long2;
    __p->control->long3_list[ __p->control->tail_pos ]  = long3;
    __p->control->long4_list[ __p->control->tail_pos ]  = long4;



    __p->control->tail_pos++;
    if ( __p->control->tail_pos >= 31 )
        __p->control->tail_pos = 0;
        
 
    //
    // Ok.
    // 

    return 0;
}





/*
 ********************************************
 * ipc_send_to_ws:
 *     Send a message to the ws if it is present.
 * 
 */

// #bugbug
// Now the window server is using unix-like sockets.

// OUT:
// <= 0 - The ws is present and we sent the message to it.
// > 0  - The ws PID.

int
ipc_send_to_ws ( 
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
        debug_print ("ipc_send_to_ws: CurrentDesktop\n");
        return -1;
    }
        
  
    if ( CurrentDesktop->desktopUsed != 1 || 
         CurrentDesktop->desktopMagic != 1234 )
    {
        debug_print ("ipc_send_to_ws: CurrentDesktop validation\n");
        return -1;
    }

    //
    // PID
    //
    
    // The ws PID.
    // #bugbug: Is it a valid PID? range?
    if (CurrentDesktop->ws <= 0){
        debug_print ("ipc_send_to_ws: ws PID\n");
        return (int) (-1);
    }

    // The ws process.
    // #todo: 
    // Process validation.

    __p = (struct process_d *) processList[ CurrentDesktop->ws ];
      
    if ( (void *) __p == NULL ){
        debug_print ("ipc_send_to_ws: __p\n");
        return (int) (-1);
    } 

    // used ? magic ?
    
  
    switch (msg)
    {
        case MSG_SYSKEYUP:
            
            switch (long1){
                
                // Emergency keys.
                // Sending these keys to the system procedure.
                case VK_F5: 
                case VK_F6: 
                case VK_F7: 
                case VK_F8:
                    debug_print ("ipc_send_to_ws: >>>> [MSG_SYSKEYUP] to system procedure\n");  
                    __local_ps2kbd_procedure ( window, 
                        (int) msg, 
                        (unsigned long) long1, 
                        (unsigned long) long2 );  
                    return 0;
                    break;
            };
            break;
    };
    
    
    //
    // Send
    //
    
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


/*
 ********************************************
 * ipc_send_to_ns:
 *     Send a message to the ns if it is present.
 * 
 */

// #bugbug
// Now the window server is using unix-like sockets.

// OUT:
// <= 0 - The ns is present and we sent the message to it.
// > 0  - The ns PID.

int
ipc_send_to_ns ( 
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
        debug_print ("ipc_send_to_ns: CurrentDesktop\n");
        return -1;
    }
        
  
    if ( CurrentDesktop->desktopUsed != 1 || 
         CurrentDesktop->desktopMagic != 1234 )
    {
        debug_print ("ipc_send_to_ns: CurrentDesktop validation\n");
        return -1;
    }

    //
    // PID
    //
    
    // The ns PID.
    // #bugbug: Is it a valid PID? range?
    if (CurrentDesktop->ns <= 0){
        debug_print ("ipc_send_to_ns: ns PID\n");
        return (int) (-1);
    }

    // The ws process.
    // #todo: 
    // Process validation.

    __p = (struct process_d *) processList[ CurrentDesktop->ns ];
      
    if ( (void *) __p == NULL ){
        debug_print ("ipc_send_to_ws: __p\n");
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




/*
 *********************
 * ipc_send_message_to_process:
 * 
 *     Sends a message to a control thread of a given process.
 */

// #ok
// This method is very good.
// But we have some more methods.

void 
ipc_send_message_to_process ( 
    unsigned long msg_buffer, 
    int pid )
{
    struct process_d  *p;
    struct thread_d   *t;


	//#debug
	//printf ("ipc_send_message_to_process: PID=%d \n", pid );
	//refresh_screen ();

    if ( pid < 0 || pid >= PROCESS_COUNT_MAX ){
        debug_print ("ipc_send_message_to_process: pid \n");
        return;
    }


    // Process structure.

    p = ( void *) processList[pid];

    if ( (void *) p == NULL ){
        debug_print ("ipc_send_message_to_process: p \n");
        return;

    }else{

         if ( p->used != 1 || p->magic != 1234 ){
             debug_print ("ipc_send_message_to_process: p validation \n");
             return;
         }

		 //
		 // Thread de controle.
		 //

         t = p->control; 

         if ( (void *) t == NULL ){
             debug_print ("ipc_send_message_to_process: t \n");
             return;

         }else{

            if ( t->used != 1 || t->magic != 1234 ){
                debug_print ("ipc_send_message_to_process: t validation \n");
                return;
            }

			//
			// Send message to the control thread.
			//
 
             ipc_send_message_to_thread ( (unsigned long) msg_buffer, 
                 (int) t->tid );   
        }
    };
}


/*
 ****************
 * ipc_send_message_to_thread:
 * 
 *     Sends a message to a given thread.
 */

void 
ipc_send_message_to_thread ( 
    unsigned long msg_buffer, 
    int tid )
{

    struct thread_d *t;

    unsigned long *buffer = (unsigned long *) msg_buffer;


	//printf ("ipc_send_message_to_thread: TID=%d \n", tid);
	//refresh_screen ();	

    //
    // TID
    //

    if ( tid < 0 || tid >= THREAD_COUNT_MAX ){
        printf ("ipc_send_message_to_thread: TID \n");
        refresh_screen ();
        return;
    }


	//
	// BUFFER
	//


	// #importante
	// Temos que checar o endereço andes de acessá-lo.

    if ( &buffer[0] == 0 ){
        printf ("ipc_send_message_to_thread: buffer\n");
        refresh_screen ();
        return;

    }else{

        t = (void *) threadList[tid];

        if ( (void *) t != NULL )
        {
            if ( t->used != 1 && t->magic != 1234 ){
                printf ("ipc_send_message_to_thread: validation\n");
                refresh_screen ();
                return;
            }

            t->window_list[ t->tail_pos ] = (struct window_d *) buffer[0];
            t->msg_list[ t->tail_pos ]    = (int) buffer[1];
            t->long1_list[ t->tail_pos ]  = (unsigned long) buffer[2];
            t->long2_list[ t->tail_pos ]  = (unsigned long) buffer[3];
        
            t->tail_pos++;
            if ( t->tail_pos >= 31 )
                t->tail_pos = 0;
        }
    };
}



/*
 *************************
 * ipc_init:
 */

int ipc_init (void)
{
    debug_print ("ipc_init: [TODO]\n");  
    return -1;   //#todo.
}


//
// End.
//

