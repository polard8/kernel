/*
 * File: timer.c 
 *
 * Descrição:
 *     Handler da irq0 para o Boot Loader.
 *
 * ATENÇÃO:
 *    O timer no Boot Loader não faz task switch.
 *    O timer será usado principalmente para timeout de driver.
 *    O timer pode ser usado para contar tempo de inicialização.
 *    
 * Versão 1.0, 2015.
 */

 
#include <bootloader.h>


unsigned long timerTicks;


/*
 * timer:
 *     Timer handler for Boot Loader.
 */
void timer()
{
    timerTicks++;    //Incrementa o contador.
	
    if(timerTicks % 100 == 0){		
        //De tempos em tempos.
    };
    
    //Nothing for now.
	
done:
    return;      
};


/*
 * BltimerInit:
 *     Inicializa o módulo timer.
 */
int BltimerInit()
{
    int Status = 0;
	
	timerTicks = 0;
    
	//...
	
done:	
	return (int) Status;	
};

//
//Fim.
//

