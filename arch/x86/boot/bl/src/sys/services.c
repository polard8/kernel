/*
 * File: services.c 
 * 
 * Descrição:
 *     Alguns serviços internos oferecidos pelo Boot Loader.
 *     Obs: 
 *     O Boot Loader deve oferecer serviços, funcionando como
 * módulo do kernel em kernel mode.
 *
 * Versão 1.0, 2015.
 */

 
#include <bootloader.h>


void *blServices ( unsigned long arg1, 
                   unsigned long arg2,
				   unsigned long arg3,
				   unsigned long arg4 )
{
	switch (arg1)
	{
		case 1:
		    break;
			
		case 2:
		    break;
		//...
	}
	return NULL;
}

/*
 * system_services:
 *     int 200 - Serviços do Boot Loader.
 */
void system_services (){
	
    //Nothing.
	return;   
};

//
// fim.
//

