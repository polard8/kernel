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

