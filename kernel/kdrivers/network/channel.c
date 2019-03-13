/*
 * File: channel.c 
 *
 * Descrição: 
 *     Channel manager. 
 *     Gerenciamento de canais Client/Server para 
 *     troca de mensagens entre processos.
 *
 * Obs: Um canal de comunicação é composto por dois sockets.
 *
 * isso ficara aqui porque estamos lidando com comunicaç~ao cliente servidor.
 * atrav'es da rede, essa 'e a ideia.
 *
 * Versão 1.0, 2015, 2016.
 */


#include <kernel.h>




/*
 ****************************************************
 * CreateChannel:
 *     Cria um canal.
 */

void *CreateChannel ( struct process_d *OwnerProcess,
				      struct thread_d *SenderThread,
				      struct thread_d *ReceiverThread )
{
    struct channel_d *NewChannel;

	NewChannel = (void *) malloc ( sizeof(struct channel_d) );
    
	if( (void *) NewChannel == NULL )
	{
	    return NULL;
	}else{
		
	    NewChannel->OwnerProcess = (void *) OwnerProcess;
		
		NewChannel->SenderThread = (void *) SenderThread;
		NewChannel->ReceiverThread = (void *) ReceiverThread;
	    
		NewChannel->State = 0;
	};
	
    return (void *) NewChannel;
}


/*
 *******************************************
 * DestroyChannel:
 *     Destroy um canal.
 *     +libera a memória.
 *     +destrói a estrutura.
 *     ...
 */

int DestroyChannel (struct channel_d *channel){
	
	if((void *) channel == NULL )
	{
	    return (int) 0;    //Nothing to do.	    	
	};
    
	
	//@todo? ...
	
//done:
	
    return (int) 0;	
};



/*
 * OpenChannel:
 *     Abrir o canal para uso.
 */

int OpenChannel ( struct channel_d *channel, 
                  struct process_d *OwnerProcess,
				  struct thread_d *SenderThread,
				  struct thread_d *ReceiverThread)
{
	if((void*) channel == NULL )
	{
	    return (int) 1;    //Fail.
	}else{
		
	    channel->State = 1;
	};
	
    return (int) 0;	
}



/*
 * CloseChannel:
 *     Libera o canal.
 *     Mas não destroi.
 */

int CloseChannel (struct channel_d *channel){
	
    if ( (void*) channel == NULL ){
	    return (int) 1;
	}else{
	    channel->State = 0;
	};
	
    return (int) 0;	
}

//
// End.
//

