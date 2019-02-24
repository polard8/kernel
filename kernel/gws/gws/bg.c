/*
 * File: gws/gws/bg.c 
 *
 * Descrição:
 *     Rotinas de configuração do background de um desktop.
 *     O background de um desktop é onde fica a imagem de pano de fundo.
 * Também é conhecido como Backbuffer.
 *
 * Window server.
 *
 * History:
 *     2013 - Created by Fred Nora.
 *     2016 - Revision.
 */


#include <kernel.h>



//Herdadas do Boot Loader.
// De onde vem isso ?? head.s
// @todo: Devemos chamar o módulo hal para obtermos esses valores.
//depois salvamos em variáveis internas usadas pela gui.
extern unsigned long SavedBootBlock;
extern unsigned long SavedLFB;
extern unsigned long SavedX;
extern unsigned long SavedY;
extern unsigned long SavedBPP; 

 
/*
 * backgroundDraw:
 *     Draw device screen in graphics mode.
 *     Clear the screen in text mode.
 *     #todo get device info.
 */

void backgroundDraw (unsigned long color){
	
    unsigned long i;
		
    if (VideoBlock.useGui != 1)
	    return;
	

    for ( i=0; i<SavedY; i++ ){			
        my_buffer_horizontal_line ( 0, i, SavedX, color );
	}
	
	//#bugbug
	//estamos determinando as dimensoes do char.
	//?? ja' podemos usar a varia'vel. ??
	
	//Cursor.
	g_cursor_x = 0;
	g_cursor_y = 0;
	g_cursor_right = (SavedX/8);
	g_cursor_bottom = (SavedY/8);
	
	backgroundSetColor (color);
}


/* backgroundSetColor:
 *     Set background color in graphics mode. */

void backgroundSetColor (unsigned long color){
	
    if ( gui->backgroundStatus == 0 ){
		
        return;
    }

	if ( (void *) gui->background != NULL ){
		
	    gui->background->bg_color = (unsigned long) color;
	}
}


/*
 * backgroundRedraw:
 *     Redraw bg. */

void backgroundRedraw (unsigned long color){
	
    if ( gui->backgroundStatus == 0 ){
		
        return;
    };
	
	if ( (void *) gui->background != NULL ){
		
	   backgroundDraw (color);	
	}
}


//Constructor.
void backgroundBackground (){
	
	g_cursor_x = 0;
	g_cursor_y = 0; 
}


//Init.
int backgroundInit (){
	
	unsigned long *lfb = (unsigned long *) BACKBUFFER_VA;
	int i=0;
	
	//#test velocidade?
	for ( i=0; i< 800*600; i++ )
		lfb[i] = COLOR_BLACK;
	
	// #todo:
	// Ainda não implementada.
	
	backgroundBackground ();
	//...
	
	return (int) 0; 
}


//
//End.
//

