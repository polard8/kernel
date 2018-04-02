//mouse.c 

//isso aqui está no kernel base, mas deverá ser um driver.


#include <kernel.h>



/*
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


