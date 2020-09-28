//low level input support

//gerenciamento de eventos e arquivos de input, tanto para o terminal, quanto
//para o emergency shell.

// mensagens (eventos) MSG_
// arquivos.
// loops ??

#include "noraterm.h" 


// IN: buffer = endereço do buffer que queremos que o kernel coloque os 4 elementos
// da mensagem.

// pegando mensagem no kernel

int host_get_message ( unsigned long buffer ){

    unsigned long *b = (unsigned long *) buffer;
	
	
		//#obs: O retorno será 1 se tiver mensagem e 0 se não tiver.
		gde_enter_critical_section (); 
		system_call ( 111,
		    (unsigned long) buffer,
			(unsigned long) buffer,
			(unsigned long) buffer );
		gde_exit_critical_section (); 
	
	    //se não temos mensagem
		if ( b[1] == 0 )
		{
		    return 0;
		}
	
    //se temos mensagem.
    return 1;
}




