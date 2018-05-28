/*
 * File: gui\statusbar.c
 *
 * Descrição:
 *     Cria uma status bar em uma janela.
 *     Faz parte do módulo Window Manager do tipo MB.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2017 - Small changes.
 *     //...
 */

 
#include <kernel.h>


/*
 ************************************************
 * StatusBar:
 *     Desenha uma status bar, dada a janela, 
 * encontramos o retângula da área de cliente.
 *     @todo: Acrescentar uma borda delicada, 
 * usar outra cor, próximo do branco.
 */
int 
StatusBar( struct window_d *window, 
           unsigned char *string1, 
		   unsigned char *string2 )
{
	struct window_d *hWnd;
	unsigned long StatusBarColor;	
	int desktopID; 
	
	if( (void*) window == NULL ){
        return (int) 1;
    }
	
	//
	// A Status bar é um elemento dentro da janela.
	// não podemos considerar as bordas e a barra de títulos.
	//
	
	if( (void*) window->rcClient == NULL ){
		return (int) 1;
	}
	
	if( window->rcClient->used != 1 || 
	    window->rcClient->magic != 1234 )
	{
		return (int) 1;
	}

	// Set Up Sizes.
	// Começa 32pixels antes do fim.
	// Mesma largura da janela.
	unsigned long x = (unsigned long) window->rcClient->left;        
	unsigned long y = (unsigned long) window->rcClient->bottom -32;  
	unsigned long width  = (unsigned long) window->rcClient->width;       
	unsigned long height = (unsigned long) 32;                           
	
	//
	// @todo: Checar limites.
	//
	
    //Desenha a barra.
//draw_bar:

	//
	// *Importante: Checando se o esquema de cores está funcionando.
	//
	
	if( (void*) CurrentColorScheme == NULL )
	{
		printf("StatusBar: CurrentColorScheme");
		die();
		//refresh_screen();
		//while(1){}
	}else{
		
		if( CurrentColorScheme->used != 1 || 
		    CurrentColorScheme->magic != 1234 )
		{
		    printf("StatusBar: CurrentColorScheme validation");
		    die();
			//refresh_screen();
		    //while(1){}			
		};
		//Nothing.
	};
	
	
	
	// Configurando as cores usadas na status bar.
	

	StatusBarColor = (unsigned long) CurrentColorScheme->elements[csiStatusBar];  
	
	desktopID = (int) get_current_desktop_id();	

 
	hWnd = (void*) CreateWindow( 1, 0, 0, "StatusBar", 
	                             x, y, width, height, 
								 window, desktopID, StatusBarColor, StatusBarColor); 
	
	if( (void*) hWnd == NULL )
	{
        return (int) 1;
    }	 
	
	//
	// @todo: Registrar! 
	// (Sabendo quem é janela mãe pode-se liberar memória depois).
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

