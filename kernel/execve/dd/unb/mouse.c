/*
 * File: unb\mouse.c
 *
 * Isso aqui está no kernel base.
 * 
 * History:
 * 2017 - Created by Fred Nora. 
 */


#include <kernel.h>



/*
 ********************************************
 * mouse_handler:
 *     Mouse handler do driver de mouse.
 *     #importante: Essa rotina vai ficar no driver de 
 * mouse carregado em ring0 e provavelmente enviará mensagens 
 * para o kernel.
 *    talvez pertenã ao driver do controlador 8042
 */
void mouse_handler (){
	
	//#debug
	printf(".");
	refresh_screen();
	return;
	
	//*importante:
	// Estamos no driver de mouse.
	// Chamaremos o mouse handler dentro do kernel base.
	
//callMouseHandler:

    //Obs: Essa função ainda está em ldisc.c
    mouseHandler ();	
};


//
// End.
//


