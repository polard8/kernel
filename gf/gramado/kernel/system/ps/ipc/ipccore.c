/*
 * File: ps/ipc/icpcore.c
 * 
 *    ?? What 
 *  
 *    2019 - Created by Fred Nora.
 */

// #todo
// Repensar a finalidade disso.
// Me parece um gerenciamento de um grupo de componentes do sistema.

#include <kernel.h>



// ??
// 4 = Número máximo de processos que podem fazer parte do Gramado Core.

typedef enum {

    gramado_core_init,
    gramado_core_shell,
    gramado_core_taskman

}gramado_core_t;



// ??
struct gramado_core_server_d
{
    int id;

	//gramado_core_t server_index;

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
	//mensagem na forma de stream.
    file *stream;                 
};


//
// #importante
// Isso é um ambiente. ele deverá ser um desktop se possível.
// Para isso vamos associar esses processos ao desktop gramado core
// Usando a esturtura de desktop antes inicializada.
//

// Assim não precisa alocar memória para a estrutura.
struct gramado_core_server_d GRAMADOCORE[4];



// ??
// Essa rotina sera' chamada se os serviços forem superios a 8000 ou inferiores a 9000
unsigned long 
ipccore_services ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{

    //#debug
    //printf ("ipcore_services: number=%d \n", number);

    if ( number < 8000 || number >= 9000 ){
        debug_print ("ipccore_services: fail\n");
        return 0;
    }


    switch (number){

		//open	
        case 8000:
			// pid, server index
			return (unsigned long) ipccore_open ( (int) arg2, (int) arg3 );
			break;
			
		//close	
        case 8001:
			// pid, server index
			return (unsigned long) ipccore_close ( (int) arg2, (int) arg3 );
			break;


        default:
            debug_print ("ipccore_services: default\n");
            break;
    };


    return 1;
}


// open communication.
// Um proceso deseja se conectar ao gramado core.

int ipccore_open ( int pid, int server_index ){

    struct process_d *p;

    debug_print ("ipccore_open: \n");

    if ( pid < 0 )
        return 1;

	
	//todo: test limits.
	
	//testando a validade do processo.
	
    p = (void *) processList[pid];

    if ( (void *) p  == NULL ){
         return 1;

    }else{

	     if ( p->used != 1 || p->magic != 1234 )
		     return 1;	
	
	
	
	    //conectando ao servidor shell.
		//#todo: testar a validade do processo shell (gws);
		
	    //se ele já está conectado.
	    if ( GRAMADOCORE[server_index].status == 1 )
	    {
	        return 1;
	    }else{
		    
		    //conectando...

			
		    //inicializando ...
			GRAMADOCORE[server_index].id = server_index;
			GRAMADOCORE[server_index].used = 1;
			GRAMADOCORE[server_index].magic = 1234;

	        GRAMADOCORE[server_index].sender_process = p;
			//GRAMADOCORE[server_index].receiver_process = ???;
			
			//pode ser a thread primária dos processos,
			//GRAMADOCORE[server_index].sender_thread = 
			//GRAMADOCORE[server_index].receiver_thread = 
				
			//status = conectado.
			GRAMADOCORE[server_index].status = 1;
			
			printf ("OK\n");
			refresh_screen();			
			
			//ok
			return 0;
		};	
	};


    //fail
    return 1;
}



// close communication.
// um processo deseja desconectar-se do gramado core.

int ipccore_close ( int pid, int server_index ){

    struct process_d *p;

    debug_print("ipccore_close: \n");

    if ( pid < 0 )
        return 1;

	
	//todo: test limits.
	
	//testando a validade do processo.
	
    p = (void *) processList[pid];

    if ( (void *) p  == NULL ){
        return 1;

    }else{

	     if ( p->used != 1 || p->magic != 1234 )
		     return 1;	
	
	
	
	    //conectando ao servidor shell.
		//#todo: testar a validade do processo shell (gws);
		
		
		//OK
	    //se ele não está conectado, então não há o que desconectar.
	    if ( GRAMADOCORE[server_index].status == 0 )
			return 0;
		
		
	    //se ele está conectado, então vamos desconectar.
	    if ( GRAMADOCORE[server_index].status == 1 )
	    {
			
		    //inicializando ...
			GRAMADOCORE[server_index].id = 0;
			GRAMADOCORE[server_index].used = 0;
			GRAMADOCORE[server_index].magic = 0;

	        GRAMADOCORE[server_index].sender_process = NULL;
			GRAMADOCORE[server_index].receiver_process = NULL;
			
			GRAMADOCORE[server_index].sender_thread = NULL;
			GRAMADOCORE[server_index].receiver_thread = NULL; 
				
			//Status = desconectado.
			GRAMADOCORE[server_index].status = 0;
			
			printf ("OK\n");
			refresh_screen();
			//OK
			return 0;
		};	
	};


	//fail
    return 1;
}


//registra um dos servidores do gramado core.
int 
ipccore_register ( 
    int server_index, 
    struct process_d *process, 
    struct thread_d *thread )
{

    debug_print ("ipccore_register:\n");


    if ( server_index < 0 || server_index >= 4 )
        return -1;


    if ( (void *) process == NULL || (void *) thread == NULL  )
        return -1;


    //inicializando ...
	GRAMADOCORE[server_index].id = server_index;
	GRAMADOCORE[server_index].used = 1;
	GRAMADOCORE[server_index].magic = 1234;

	GRAMADOCORE[server_index].sender_process = NULL;
	GRAMADOCORE[server_index].receiver_process = process;
			
	GRAMADOCORE[server_index].sender_thread = NULL;
	GRAMADOCORE[server_index].receiver_thread = thread; 
				
	//Status = desconectado.
	GRAMADOCORE[server_index].status = 0;	


    return 0;
}


//
// End.
//






