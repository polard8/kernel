/*
 * File: callout.c
 *     O Kernel chama uma rotina em user mode.
 */


/*
    O callout chamará uma rotina em user mode através de um iret.
    Acessamos s rotinas de um servidor que está em user mode através
	de um iret e quando ele terminar ele aciona uma interrupção, que é um
	callback.
*/
 
 
#include <kernel.h>



void KiCalloutTest()
{
	//
	// @todo: reproduzier o spawn para chamar uma rotina de um servidor em user mode.
	// depois ele responde com uma interrupção do tipo call back.
	//
	
	//iret
	return;
};


//
// End.
//

