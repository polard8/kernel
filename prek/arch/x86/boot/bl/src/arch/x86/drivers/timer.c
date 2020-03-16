/*
 * File: x86/drivers/timer.c 
 *
 * Descrição:
 *     Handler da irq0 para o Boot Loader.
 *
 * ATENÇÃO:
 *    O timer no Boot Loader não faz task switch.
 *    O timer será usado principalmente para timeout de driver.
 *    O timer pode ser usado para contar tempo de inicialização.
 *    
 * 2015 - Created by Fred Nora.
 */

 
#include <bootloader.h>


unsigned long timerTicks;


/*
 * timer:
 *     Timer handler for Boot Loader.
 *     #bugbug: Nem sei se devemos habilitar o timer durante o boot loader.
 */

// Incrementa o contador.
// De tempos em tempos, faz alguma coisa.

void timer (){

    timerTicks++;

    if ( timerTicks % 100 == 0 )
    {
    }
}


/*
 * BltimerInit:
 *     Inicializa o módulo timer.
 */

int BltimerInit (){

    int Status = 0;

    timerTicks = 0;

	//...

    return (int) Status;
}


//
// End.
//

