/*
 * File: vsync.c
 *
 * Descrição:
 *     Sincronisa o retraço vertical.
 *
 *     Na hora de enviar os dados para o LFB é
 * necessário sincronizar com o retraço vertical do monitor.
 *
 *     Pertence ao hal.
 *     Não sei se pertence a x86. ???!!!
 *
 * History:
 *     2015 - Created by Fred Nora.
 */

 
#include <kernel.h>


//
// Definições.
#define VSYNC_INPORT 0x3DA


//
// Funções internas.
char vsync_inb(int port);


/*
 * vsync:
 *     Sincroniza a pintura com o retraço vertical. 
 */
void vsync()
{
    /* wait until any previous retrace has ended */
    do{
	//nothing
    }while( vsync_inb(VSYNC_INPORT) & 8 );

    /* wait until a new retrace has just begun */
    do{
	//nothing
    }while( !(vsync_inb(VSYNC_INPORT) & 8) );
	
done:
    return;
};


/*
 * vsync_inb: 
 *     Pega um byte na porta.
 */
char vsync_inb(int port)
{
    char Value = 0;
	
    Value = (char) inportb(port); 
	
	asm(" nop \n");
	asm(" nop \n");
	asm(" nop \n");
	asm(" nop \n");
	return (char) Value;    
};


//
// End.
//

