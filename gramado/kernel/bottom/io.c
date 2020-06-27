/*
 * File: io.c
 *
 * Descrição:
 *     Arquivo principal do I/O Manager.
 *     I/O control. 
 *     Obs: Note que o I/O Manager está fora do executive, mas faz parte 
 *          do Kernel Base.
 *
 * Todo gerenciamento de dispositivos, toda concessão de acesso passará por 
 * esse gerenciador, que faz parte da camada de abstração de hardware 
 * oferecida pelo kernel base.
 * Essa parte do gerenciamento de i/o está no kernel base em kernel mode. 
 * Porem haverá outras partes. Haverá um subsistema em user mode, e talvez 
 * um módulo externo do kernel em kernel mode.
 *
 * I/O system: Inclui I/O manager
 *
 *  @todo: Cria funções para gerenciar ioBuffers.
 * The actual fileList modules lives in kernel space on Unix, and are 
 * installed (pushed) and removed (popped) by the ioctl system call.
 * 
 *    2016 - Created by Fred Nora.
 */


#include <kernel.h> 


/*
 * ioServices:
 * Serviços de i/o oferecidos pelo kernel base.
 * Quando o módulo 'service.c' receber chamadas para serviços de i/o 
 * ele pode desviar as chamadas para serem atendidas por essa rotina.
 */

void *ioServices ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{

    struct process_d *P;

    int Caller_Process_ID=0;


	// #todo: 
	// O subsistema em user mode deve fazer algum tipo de filtragem
	// pra autorizar ou não um processo à usar o sistema de i/o.
	// Porém aqui também é feito alguma filtragem pra conferir autorização.
	// @todo:
	// Checar a token do processo, se a token do tipo HAL está habilitada
	// para o processo que chama a rotina.	

	//
	// Id do processo que está chamando a rotina de i/o.
	//


	// todo: 
	// Filtrar argumentos.

    Caller_Process_ID = (int) get_caller_process_id();

    if ( Caller_Process_ID <0 || 
         Caller_Process_ID >= PROCESS_COUNT_MAX )
    {
        debug_print ("ioServices: Caller_Process_ID\n");
        return NULL;
    }


    P = (void *) processList[Caller_Process_ID];

    if ( (void *) P == NULL )
    {
        debug_print ("ioServices: P\n");
        return NULL;
    }

	//
	// Chama o serviço solicitado.
	//
	
	switch (number)
    {
        case 0:
		    //Nothing.
            break;

        case 1:
            //Nothing.
            //sys_ioctl ( int fd, unsigned long request, char *arg );
            break; 
        //...

        default:
            debug_print ("ioServices: default\n");
            break;
    };

	// ...

    return NULL;
}



/*
 ********************************
 * ioInit:
 *     Initialize i/o manager.
 */

int ioInit(void){

    int Status = 0;


    debug_print ("ioInit: [TODO]\n");
    
    // ...

    return (int) Status;
}


//
// End.
//

