/*
 * File: dd/timer.c 
 * Descrição:
 *     Handler da irq0 para o Boot Loader.
 * ATENÇÃO:
 *    O timer no Boot Loader não faz task switch.
 *    O timer será usado principalmente para timeout de driver.
 *    O timer pode ser usado para contar tempo de inicialização.
 * 2015 - Created by Fred Nora.
 */


#include <bootloader.h>


unsigned long timerTicks=0;


// irq handler.
// Increment jiffies.

void timer()
{
    timerTicks++;

    //if ( timerTicks % 100 == 0 )
    //{
        // Nothing ...
    //}
}


/*
 * BltimerInit:
 *     Inicializa o módulo timer.
 */

int BltimerInit()
{
    int Status=0;

    timerTicks = 0;
    //...
    return (int) Status;
}


//
// End.
//

