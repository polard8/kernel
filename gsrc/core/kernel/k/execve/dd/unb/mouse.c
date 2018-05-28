/*
 * File: unblocked\mouse.c
 *
 * Isso aqui está no kernel base, mas deverá ser um driver.
 * 
 * History:
 * 2017 - Created by fred Nora. 
 *
 */


#include <kernel.h>



/*
 ********************************************
 * mouse_handler:
 *     Mouse handler do driver de mouse.
 */
void mouse_handler()
{
	//
	//*importante:
	// Estamos no driver de mouse.
	// Chamaremos o mouse handler dentro do kernel base.
	//
	
callMouseHandler:

    //Obs: Essa função ainda está em ldisc.c
    mouseHandler();	
	return;
};


//
//fim.
//


