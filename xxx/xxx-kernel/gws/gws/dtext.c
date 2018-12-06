/*
 * File: gui\dtext.c
 *
 * Descrição:
 *     Escreve um texto dentro de uma janela.
 *     Faz parte do módulo Window Manager do tipo MB.
 *
 * Versão 1.0, 2015.
 */


#include <kernel.h>


/*
 * draw_text:
 *     Escreve um texto em uma dada janela.
 */				
void draw_text ( struct window_d *window,
                 unsigned long x,  
                 unsigned long y,  
				 unsigned long color, 
				 unsigned char *string )
{ 
	if ( (void *) window == NULL )
	{
        return; 
    }else{    
		draw_string ( window->left +x, window->top +y, color, string );		
	}; 
};


/*
 * draw_string:
 *     Desenha uma string.
 *     //@todo: Talvez possa usar string formatada.(printf)
 */
void draw_string ( unsigned long x,  
                   unsigned long y,  
				   unsigned long color, 
				   unsigned char *string )
{	
	int Index;
	
	int cWidth = get_char_width ();
	//int cHeight = get_char_height ();
	
	//if ( cWidth == 0 || cHeight == 0 )
	if ( cWidth == 0 )
	{
		//#debug
		printf("gws-dtext-draw_string: fail w ");
		die();
	}
      
    for ( Index=0; string[Index] != 0; Index++ )
	{
		//@todo: 
		//   Conflito de tipo no argumento 4.
		//   gcharWidth.
		//my_buffer_char_blt( x, y, color, string[Index]);
		drawchar_transparent ( x, y, color, string[Index] );
        
		//#todo: Tamanho do char. Usr variável.
		
		x += cWidth;
    };   
};

//
// End.
//

