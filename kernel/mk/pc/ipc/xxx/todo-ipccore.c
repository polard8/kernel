
// icpcore.c

// Gerenciar a comunicação entre os processos e os
// servidores que fazem parte do Gramado Core.

// Gramado Core:
// +/init/core/init    (ramdom)
// +/init/core/shell   (gws)
// +/init/core/taskman (task serviçes)


//#importante
//conjunto pequeno de processos especiais.


// 4 = Número máximo de processos que podem fazer parte do Gramado Core.

typedef enum {

    gramado_core_init,
	gramado_core_shell,
	gramado_core_taskman,
	0
		
}gramado_core_t;




struct gramado_core_server_d
{
	int id;
	
	int used;
	int magic;
	
	//0 = disconnected
	//1 = connected;
	int status;
	
	//esse é o processo conectado ao servidor do gramado core.
    struct process_d *sender_process;
	struct thread_d *sender_thread;      
	
    struct process_d *receiver_process;
	struct thread_d *receiver_thread;      	
	
	//simple message
	struct window_d *window;
	int msg;
	unsigned long long1;
	unsigned long long2;
	
	//extra message
	unsigned long long3;
	unsigned long long4;
	unsigned long long5;
	unsigned long long6;
	
	//super message.
	FILE *stream;                 //mensagem na forma de stream.
}

// Assim não precisa alocar memória para a estrutura.
struct gramado_core_server_d GRAMADOCORE[4];




// open communication.
// Um proceso deseja se conectar ao gramado core.
int ipccore_open ( int pid, int server_pid )
{
	struct process_d *p;
	
	if ( pid < 0 )
		return -1;
	
	
	//todo: test limits.
	
	//testando a validade do processo.
	
	p = (void *) processList[pid]
	
	if ( (void *) p  == NULL )
	{
	     return -1;
	}else{
	
	     if ( p->used != 1 || p->magic != 1234 )
		     return -1;	
	
	
	
	    //conectando ao servidor shell.
		//#todo: testar a validade do processo shell (gws);
		
	    //se ele já está conectado.
	    if ( GRAMADOCORE[server_pid].status == 1 )
	    {
	        return -1;
	    }else{
		    
		    //conectando...

			
		    //inicializando ...
			GRAMADOCORE[server_pid].id = server_pid;
			GRAMADOCORE[server_pid].used = 1;
			GRAMADOCORE[server_pid].magic = 1234;

	        GRAMADOCORE[server_pid]->sender_process = p;
			//GRAMADOCORE[server_pid]->receiver_process = ???;
			
			//pode ser a thread primária dos processos,
			//GRAMADOCORE[server_pid]->sender_thread = 
			//GRAMADOCORE[server_pid]->receiver_thread = 
				
			//status = conectado.
			GRAMADOCORE[server_pid].status = 1;
			
			//ok
			return 0;
		};	
	};
	
	//fail
    return -1;
}



// close communication.
// um processo deseja desconectar-se do gramado core.
int ipccore_close ( int pid, int server_pid )
{
	struct process_d *p;
	
	if ( pid < 0 )
		return -1;
	
	
	//todo: test limits.
	
	//testando a validade do processo.
	
	p = (void *) processList[pid]
	
	if ( (void *) p  == NULL )
	{
	     return -1;
	}else{
	
	     if ( p->used != 1 || p->magic != 1234 )
		     return -1;	
	
	
	
	    //conectando ao servidor shell.
		//#todo: testar a validade do processo shell (gws);
		
		
		//OK
	    //se ele não está conectado, então não há o que desconectar.
	    if ( GRAMADOCORE[server_pid].status == 0 )
			return 0;
		
		
	    //se ele está conectado, então vamos desconectar.
	    if ( GRAMADOCORE[server_pid].status == 1 )
	    {
			
		    //inicializando ...
			GRAMADOCORE[server_pid].id = 0;
			GRAMADOCORE[server_pid].used = 0;
			GRAMADOCORE[server_pid].magic = 0;

	        GRAMADOCORE[server_pid]->sender_process = NULL;
			GRAMADOCORE[server_pid]->receiver_process = NULL;
			
			GRAMADOCORE[server_pid]->sender_thread = NULL;
			GRAMADOCORE[server_pid]->receiver_thread = NULL; 
				
			//Status = desconectado.
			GRAMADOCORE[server_pid].status = 0;
			
			//OK
			return 0;
		};	
	};
	
	//fail
    return -1;
}






