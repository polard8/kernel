/*
 * File: statusbar.c
 *
 * Descrição:
 *     Cria uma status bar em uma janela.
 *     Faz parte do módulo Window Manager do tipo MB.
 *
 * Histórico:
 *     Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *     //...
 */

 
#include <kernel.h>


/*
 * StatusBar:
 *     Desenha uma status bar, dada a janela.
 *     @todo: Acrescentar uma borda delicada, usar outra cor, próximo do 
 * branco.
 */
int StatusBar( struct window_d *window, 
               unsigned char *string1, 
			   unsigned char *string2 )
{     
	struct window_d *hWnd;
		
	if( (void*) window == NULL ){
        return (int) 1;
    };

	// Set Up Sizes.
	unsigned long x      = (unsigned long) window->left +1;    //Compensa a borda. 
	unsigned long y      = (unsigned long) window->bottom -32;
	unsigned long width  = (unsigned long) window->width -2;   //Compensa 
	unsigned long height = (unsigned long) 32;
	
	//
	// @todo: Checar limites.
	//
	
    //Desenha a barra.
draw_bar:
    hWnd = (void*) CreateWindow( 1, 0, 0, "StatusBar", x, y, width, height, window, 0, 0, COLOR_STATUSBAR); 
	if( (void*) hWnd == NULL ){
        return (int) 1;
    };	 
	
	//
	// @todo: Registrar! (Sabendo quem é janela mãe pode-se liberar memória depois).
	//
	
	RegisterWindow(hWnd);
    //set_active_window(hWnd);
	//SetFocus(hWnd);	
	
	
	//Escreve as strings.
draw_strings:	
	draw_text( hWnd, 0 * (width/2), 1* (height/3), COLOR_WINDOWTEXT, string1);
	draw_text( hWnd, 1 * (width/2), 1* (height/3), COLOR_WINDOWTEXT, string2);
	
	//More?!
	
done:     
    return (int) 0;
};



/*
int statusbarInit()
{}
*/

//
//fim
//

