/*
 * File: dtext.c
 *
 * Descrição:
 *     Escreve um texto dentro de uma janela.
 *     Faz parte do módulo Window Manager do tipo MB.
 *
 * 2015 - Created by Fred Nora.
 */


#include <kernel.h>


/* 
 * draw_text:
 *     Draw text on a window.
 *
 * #test: 
 *     Como opção, se nenhuma janela for especificada, 
 *     então pintaremos na janela principal.
 */

void 
draw_text ( 
    struct window_d *window,
    unsigned long x,
    unsigned long y,
    unsigned long color,
    unsigned char *string )
{ 

    if ( (void *) window == NULL ){
        draw_string ( gui->main->left +x, gui->main->top +y, color, string );
        return;
        
    }else{
        draw_string ( window->left +x, window->top +y, color, string );
    };
}


/* draw_string:
 *     Draw a string on the screen. 
 */

void 
draw_string ( 
    unsigned long x,
    unsigned long y,
    unsigned long color,
    unsigned char *string )
{

    // loop
    register int Index=0;

    int cWidth = get_char_width ();
    //int cHeight = get_char_height ();


    //if ( cWidth == 0 || cHeight == 0 )
    if ( cWidth == 0 ){
        panic ("dtext-draw_string: cWidth");
    }
    
    // #bugbug
    // There is something not good with this routine.
    
    for ( Index=0; string[Index] != 0; Index++ )
    {
        d_drawchar_transparent ( x, y, color, string[Index] );

        x += cWidth;
    };
}


//
// End.
//

