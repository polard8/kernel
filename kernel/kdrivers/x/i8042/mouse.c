/*
 * File: i8042/mouse.c
 *
 * env:
 *     Ring 0. Kernel base persistent code.
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

//*importante:
// Estamos no driver de mouse.
// Chamaremos o mouse handler dentro do kernel base.
//ps2mouse.c

void mouse_handler (void)
{	
    mouseHandler ();	
}


//
// End.
//


