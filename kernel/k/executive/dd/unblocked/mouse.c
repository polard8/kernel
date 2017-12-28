


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
    mouseHandler();	
	return;
};


//
//fim.
//


