/*
 * File: reboot.c
 *
 * History:
 *     2015 - Created by Fred Nora.
 */


#include <kernel.h>



/*
 * reboot: 
 *     Reboot system via keyboard port.
 *
 * *IMPORTANTE: a interface fechou o que tinha qe fechar,
 * hal chamou essa hotina para efetuar a parte de hardware reboot apenas.
 * @todo: Atribuições.
 *
 * Atribuições: 
 *     + Desabilitar as interrupções.
 *     + Salvar registros.
 *     + Salvar programas abertos e não salvos.
 *     + Fechar todas tarefas antes.
 *     + Efetuar o tipo de reboot especificado.
 *    + Outras ...
 */
 
void reboot (void){
    
    //@todo: 
	// +criar uma variavel global que especifique o tipo de reboot.
    // +criar um switch para efetuar os tipos de reboot.
	// +criar rota de fuga para reboot abortado.
	// +Identificar o uso da gui antes de apagar a tela.
	//  modo grafico ou modo texto.
	//
	
	//
	// Video.
	//
	
	/*
	sleep(2000);
    set_up_cursor(0,0);	
    set_up_text_color(0x0f, 0x09);
	printf("\n\n REBOOTING ...\n\n");


	//
	// Scheduler stuffs.
	//
	
	sleep(1000);
	printf("locking scheduler ...\n");
	scheduler_lock();
	
	//
	// Tasks.
	//
	
	//@todo: fazer função com while. semelhante ao dead task collector.
	
	sleep(1000);
	printf("killing tasks ...\n");
	//kill_thread(current_task); 
	
	//
	// Final message.
	//
	
	sleep(1000);
	printf("turning off ...\n");
    
	
	refresh_screen();
	
	//
	// Interruoções.
	//
	
	sleep(7000);
	asm("cli");
	
	*/
	
	
	// @todo: disable();
	
    // Done.

    // Rotina de alto nível que irá desalocar recursos
    // antes de reiniciar.
    systemReboot ();   
    die ();
}

//
// End.
//







