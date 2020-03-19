/*
 * File: dtext.c 
 * 
 * 
 * 
 * 
 * 
 */


#include <api.h>
#include <gws.h>



/* 
 * dtextDrawString:
 *     Draw a string on the screen. 
 */

void 
dtextDrawString ( unsigned long x,
                  unsigned long y,
                  unsigned long color,
                  unsigned char *string )
{

    int Index=0;

    int cWidth = 8;   //#bugbug  determinando


	//int cWidth = get_char_width ();
	//int cHeight = get_char_height ();
	
	//if ( cWidth == 0 || cHeight == 0 )
	if ( cWidth == 0 )
	{
		//panic ("dtext-draw_string: cWidth");
	    
	    //#debug
	    gde_message_box (3, "xxx","dtext-draw_string: cWidth");
	    while(1){}
	}
      
    for ( Index=0; string[Index] != 0; Index++ )
	{
		//@todo: 
		//   Conflito de tipo no argumento 4.
		//   gcharWidth.
		//my_buffer_char_blt( x, y, color, string[Index]);
        
        //drawchar_transparent ( x, y, color, string[Index] );
        charBackbufferDrawcharTransparent ( x, y, color, string[Index] );
        
        
		//#todo: Tamanho do char. Usr variável.
		
        x += cWidth;
    };
}


/* 
 * dtextDrawText:
 *     Draw text on a window.
 *
 * #test: 
 *     Como opção, se nenhuma janela for especificada, 
 *     então pintaremos na janela principal.
 */

void 
dtextDrawText ( struct window_d *window,
                unsigned long x,
                unsigned long y,
                unsigned long color,
                unsigned char *string )
{ 

    struct window_d * __w;


    __w = (struct window_d *) gui->screen;
	
    if ( (void *) window == NULL )
    {
        dtextDrawString ( __w->left +x, __w->top +y, color, string );
        return;
        
    }else{
        dtextDrawString ( window->left +x, window->top +y, color, string );
    };
}





