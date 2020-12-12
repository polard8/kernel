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
 * irq12_MOUSE:
 * 
 *     Mouse handler do driver de mouse.
 *     #importante: Essa rotina vai ficar no driver de 
 * mouse carregado em ring0 e provavelmente enviará mensagens 
 * para o kernel.
 *    talvez perteça ao driver do controlador 8042
 */

//*importante:
// Estamos no driver de mouse.
// Chamaremos o mouse handler dentro do kernel base.
// ps2mouse.c

__VOID_IRQ 
irq12_MOUSE (void)
{

    // Se o mouse ps2 não estiver inicializado !
    if ( __breaker_ps2mouse_initialized == 0 )
        return;


	// Contando as interrupções desse tipo.
    g_profiler_ints_irq12++;


    mouseHandler();

	 
	 //#bugbug
	 /*
	//int status;

    //status = get_ps2_mouse_status ();
    
    //if ( status == 1 )
    //   mouseHandler ();
    */
}





//
// End.
//


