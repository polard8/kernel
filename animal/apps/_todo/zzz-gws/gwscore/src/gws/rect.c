/*
 * rect.c 
 * 
 * 
 * 
 */



#include <api.h>
#include <gws.h>


/* 
 * rectBackbufferDrawRectangle:
 *     Draw a rectangle on backbuffer. 
 */

void 
rectBackbufferDrawRectangle ( unsigned long x, 
                              unsigned long y, 
                              unsigned long width, 
                              unsigned long height, 
                              unsigned long color )
{

	//#BUGBUG
	//TEMOS UM PROBLEMÃO AQUI.
	//Estamos usando um ponteiro sem ao menos
	//termos alocado memória para sua estrutura.
	//>> para contornar, vamos tentar usar sem
	//ponteiro.

    //api02
    struct rect_d rect;

    rect.bg_color = color;
   
    //Dimensions.
    rect.x = 0;        
    rect.y = 0;         
    rect.width = width;   
    rect.height = height;    


    //Margins.
    rect.left = x;    
    rect.top = y;
    rect.right = rect.left + rect.width;
    rect.bottom = rect.top + rect.height; 


    //Limits.
	//@todo: Repensar os limites para uma janela.
	// Uma janela poderá ser maior que as dimensões de um dispositivo.
	// mas não poderá ser maior que as dimensões do backbuffer.
	// Ou seja: O dedicated buffer de uma janela deve ser menor que
	// o backbuffer.
	
	//#todo: Usar variável para largura.


    if ( rect.right > 800 )
    {
        rect.right = 800;
    }


    //if ( rect.right > SavedX )
	//{
    //    rect.right = SavedX;
	//}	
	

	/* @todo:
    if( rect->bottom > SavedY ){
        rect->bottom = SavedY;
	};
    */	
  	
    // Draw lines on backbuffer.
	
    while (height--)
    {
        lineBackbufferDrawHorizontalLine ( rect.left, 
            y, 
            rect.right, 
            rect.bg_color );
       
       y++;
    };    
}


