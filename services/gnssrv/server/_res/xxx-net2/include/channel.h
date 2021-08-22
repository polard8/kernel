/*
 * File: channel.h 
 *
 * Descrição:
 *     Header for channel manager.
 *     Channel manager. 
 *     Gerenciamento de canais Client/Server para troca de mensagens entre 
 * processos.
 *    " Um canal de comunicação é composto de dois soquetes, um para o cliente 
 * e outro para o servidor. "
 *
 * ?? isso não deveria fazer parte do /pc/ipc
 *
 * Versão 1.0, 2015, 2016.    
 */



/*
#define  LISTEN_CHANNEL 0x1
#define MESSAGE_CHANNEL 0x2

typedef enum _ECHANNEL_STATE {
    ClientIdle,
    ClientSendWaitReply,
    ClientShutdown,
    ServerIdle,
    ServerReceiveMessage,
    ServerShutdown
} ECHANNEL_STATE;
*/



/*
 * Estrutura para canal.
 * Serve para estabelecer uma conexão,
 * ?? pelo jeito não serve para 
 * trocar mensagens, somente para estabelecer a 
 * conexão.
 * Obs: Essa estrutura é aceitável, está em conformidade 
 * com os padrões encontrados
 */
typedef struct channel_d channel_t;
struct channel_d
{
	object_type_t objectType;
	object_class_t objectClass;
	
    int Used;
	int Magic;
	
	int Type;
	
    int State;    //Aberto ou fechado.
    int InUse;    //Em uso ou não.	
		
    struct process_d *OwnerProcess;
	
    struct thread_d *ClientThread;
    struct thread_d *ServerThread;
	
	
	//Os dois soquetes do canal de comunicação.
	struct socket_d *clientSocket;
	struct socket_d *serverSocket;
	
	//#importante:
	//context ??
	//me parece que um ponteiro pra uma estrutura do 
	//tipo context é necessário 
	//context deve conter os elementos necessários 
	//para a transmissão da mensagem. Como o buffer 
	//de memória compartilhada.
	//
    
	//?? O que é isso ???
	//me parece que é necessário.
	//struct channel_d *serverchannel;
};
channel_t *defaultChannel;
channel_t *CurrentChannel;
//...


unsigned long channelList[32];

//
// Prototypes.
//

void *CreateChannel(struct process_d *OwnerProcess,
				    struct thread_d *ClientThread,
				    struct thread_d *ServerThread);
					
int DestroyChannel(struct channel_d *channel);

int OpenChannel(struct channel_d *channel, 
                struct process_d *OwnerProcess,
				struct thread_d *ClientThread,
				struct thread_d *ServerThread);
				
int CloseChannel(struct channel_d *channel);



//
// Fim.
//

