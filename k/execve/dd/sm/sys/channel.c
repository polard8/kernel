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
 * Versão 1.0, 2015, 2016.
 */


#include <kernel.h>




/*
 * CreateChannel:
 *     Cria um canal.
 *
 */
void *CreateChannel( struct process_d *OwnerProcess,
				     struct thread_d *ClientThread,
				     struct thread_d *ServerThread )
{
    struct channel_d *NewChannel;

	NewChannel = (void*) malloc(sizeof(struct channel_d));
    
	if((void*) NewChannel == NULL ){
	    return NULL;
	}else{
	    NewChannel->OwnerProcess = (void*) OwnerProcess;
		NewChannel->ClientThread = (void*) ClientThread;
		NewChannel->ServerThread = (void*) ServerThread;
	    NewChannel->State = 0;
	};	
	//Nothing.
done:
    return (void*) NewChannel;
};


/*
 * DestroyChannel:
 *     Destroy um canal.
 *     +libera a memoria.
 *     +destrói a estrutura.
 *     ...
 */
int DestroyChannel(struct channel_d *channel)
{
	if((void*) channel == NULL ){
	    return (int) 0;    //Nothing to do.	    	
	};
    
	
	//@todo? ...
	
done:
    return (int) 0;	
};



/*
 * OpenChannel:
 *     Abrir o canal para uso.
 *
 */
int OpenChannel( struct channel_d *channel, 
                 struct process_d *OwnerProcess,
				 struct thread_d *ClientThread,
				 struct thread_d *ServerThread)
{
	if((void*) channel == NULL )
	{
	    return (int) 1;    //Fail.
	}else{
	   
	   /*
	    if( channel->OwnerProcess != OwnerProcess || 
		    channel->ClientThread != ClientThread || 
			channel->ServerThread != ServerThread)
		{
		    return 1;
		};
	    */
	    channel->State = 1;
	};
done:
    return (int) 0;	
};


/*
 * CloseChannel:
 *     Libera o canal.
 *     Mas não destroi.
 */
int CloseChannel(struct channel_d *channel)
{
    if((void*) channel == NULL ){
	    return (int) 1;
	}else{
	    channel->State = 0;
	};
    return (int) 0;	
};


//
// Fim.
//

