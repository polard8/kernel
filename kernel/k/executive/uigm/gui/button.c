/*
 * Arquivo: button.c
 *
 * Descrição:
 *     Rotinas de criação e gerenciamento de botões. 
 *     Faz parte do módulo Window Manager do tipo MB.
 *
 * Versão 1.0, 2015.
 */


#include <kernel.h>


/*
 * draw_button:
 *     Desenha um botão dado um tipo.
 *     @todo: Medir o tamanho da string da tag.
 *
 */
void draw_button( struct window_d *window,
                  unsigned char *string,
                  unsigned long type, 
                  unsigned long x, 
                  unsigned long y, 
                  unsigned long width, 
                  unsigned long height, 
                  unsigned long color)
{
    int i;
	int Selected;
	unsigned long board1;
    unsigned long board2;
	
	//validade da janela onde o botão está.
	if((void*) window == NULL){
	    return;
	};
		
    if(type == 0){
        return;
    };    
	
    switch(type)
    {
        //Não pressionado.
        case BN_DOWN:
		    Selected = 0;
		    board1 = COLOR_BUTTONHIGHLIGHT;
			board2 = COLOR_BUTTONSHADOW;
            goto do_draw_button;			
			break;
                                    
        //Precionado.
        case BN_UP:
		    Selected = 0;
		    board1 = COLOR_BUTTONSHADOW;
			board2 = COLOR_BUTTONHIGHLIGHT;
            goto do_draw_button;			
            break;
                       
         //Selecionado. (highlight)
        case BN_SELECTED:
		    Selected = 1;
		    board1 = COLOR_BUTTONHIGHLIGHT;
			board2 = COLOR_BUTTONSHADOW;
            goto do_draw_button;			
            break;
        
		default:  
		    return; 
            break;    
    };  

//
// Do draw the button.
//
	
do_draw_button:
    
	//bg
	drawDataRectangle( window->left +x, window->top +y, width, height, color);
    
	//board1, borda de cima e esquerda.
	drawDataRectangle( window->left +x, window->top +y, width, 1, board1);
	drawDataRectangle( window->left +x, window->top +y, 1, height, board1);

	//board2, borda direita e baixo.
	drawDataRectangle( window->left +x +width -1, 
	                   window->top +y, 
					   1, 
					   height, 
					   board2);
					   
	drawDataRectangle( window->left +x, 
	                   window->top  +y +height -1, 
					   width, 
					   1,
					   board2);

//
// Do draw label.
//
					   
do_draw_label:

	//button label								   
    if(Selected == 1){
	    draw_string( window->left + x +8, window->top + y +8, COLOR_WHITE, string);	
    }else{
	    draw_string( window->left + x +8, window->top + y +8, COLOR_WINDOWTEXT, string);	
	};
	
	//
	// @todo: Algo mais?
	//
	
// Done! 
done:
    return;          
};


/*
int buttonInit()
{}
*/

//
// Fim.
//
