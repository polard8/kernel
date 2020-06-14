/*
 * File: channel.c 
 *
 *     Channel manager. 
 *     A communication channel has two sockets. 
 *     A socket has an IP and a port.
 *
 * History:
 *     2015 - Created by Fred Nora.
 */


#include <kernel.h>



/*
 ****************************************************
 * CreateChannel:
 *     Create a communication channel.
 */

//#todo: arguments.
void *CreateChannel (void)
{
	debug_print ("CreateChannel: [TODO]\n");
    return NULL;
}



/*
 *******************************************
 * DestroyChannel:
 *     ...
 */

int DestroyChannel (struct channel_d *channel){

    if ( (void *) channel == NULL ){
        return 0;   

    }else{

        //channel = NULL;
        //...

    };

    return 0;
}



/*
 * OpenChannel:
 */

//#todo: arguments.
int OpenChannel ( void ){

	debug_print ("OpenChannel: [TODO]\n");
    return -1;
}



/*
 * CloseChannel:
 *     Libera o canal.
 *     Mas não destroi.
 */

int CloseChannel (struct channel_d *channel){

    if ( (void *) channel == NULL ){
        return (int) 1;

    }else{
        //channel->state = 0;
    };


    return 0;
}


//
// End.
//

