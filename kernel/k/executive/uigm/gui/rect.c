/*
 * File: rect.c
 *
 * Descrição:
 *     Rotina de pintura de retangulos.
 *     Faz parte do módulo Window Manager do tipo MB.
 *
 * Versão 1.0, 2015.
 */



#include <kernel.h>

//
// @todo: Criar uma estrutura para o elemento gráfico. entre os elementos da estrutura
// pode ter os buffer para o char. backbuffer, frontbuffer, dedicatedbuffer.
//
//

/*
 * rectDrawRectangleWindowBuffer:
 *     Pinta um retângulo no buffer da janela.
 *     Serve para pintar janelas que irão direto do seu buffer para o LFB da 
 * memória de vídeo, sem passar pelo back buffer. (OVERLAPPED)
 *
 */
/*
void rectDrawRectangleWindowBuffer(struct window_d *window, 
                                   unsigned long x, 
                                   unsigned long y, 
						           unsigned long width, 
						           unsigned long height, 
						           unsigned long color ); 
void rectDrawRectangleWindowBuffer(struct window_d *window, 
                                   unsigned long x, 
                                   unsigned long y, 
						           unsigned long width, 
						           unsigned long height, 
						           unsigned long color )
{
    return;	
}
*/

 
/*
 * drawDataRectangle:
 *     Cria um retângulo no Backbuffer. Em qualquer posição do Backbuffer
 * dado o limite do tamanho da tela.
 *     @todo: Criar rotina para pintar um retângulo em um buffer dedicado.
 *            Toda janela tem um buffer dedicado. O BackBuffer é o buffer
 * dedicado da janela principal. 'gui->main'
 */
void drawDataRectangle( unsigned long x, 
                        unsigned long y, 
						unsigned long width, 
						unsigned long height, 
						unsigned long color )
{  
    struct window_d *rect;

    //gui->current.buffer.start -> inicio do buffer da janela atual.    
    
	//bg
    rect->color_bg = color;
   
    //Dimensões.
	rect->x = 0;        
    rect->y = 0;         
    rect->width = width;   
    rect->height = height;    
   
    //Margens.
    rect->left = x;    
    rect->top  = y;
    rect->right = rect->left + rect->width;
    rect->bottom = rect->top + rect->height; 

    //Limits.
	//@todo: Repensar os limites para uma janela.
	// Uma janela poderá ser maior que as dimensões de um dispositivo.
	// mas não poderá ser maior que as dimensões do backbuffer.
	// Ou seja: O dedicated buffer de uma janela deve ser menor que
	// o backbuffer.
    if( rect->right > 800 ){
        rect->right = 800;
	};	

	/* @todo:
    if( rect->bottom > 600 ){
        rect->bottom = 600;
	};
    */	
  	
    //Pinta as linhas no Backbuffer.  
	while(height--){
	    my_buffer_horizontal_line( rect->left, y, rect->right, rect->color_bg);
		y++;
    };    
  
done: 
    return;
};
  
  
  
/*
 * getClientAreaRect:
 *     Obtém o ponteiro da estrutura do retângulo  
 *     da área de cliente da janela ativa.
 *     @todo: oferecer esse serviço para a api.
 */  
void *getClientAreaRect()
{
    return (void *) rectClientArea;	
};

/*
 * setClientAreaRect:
 *     Inicializa a estrutura do retângulo
 *     da área de cliente da janela ativa.
 *
 */
void setClientAreaRect( unsigned long x, 
                        unsigned long y, 
						unsigned long cx, 
						unsigned long cy )
{
    struct rect_d *r;

	r->x = x;
	r->y = y;
	r->cx = cx;
	r->cy = cy;
	
	//Se a estrutura ainda não foi inicializada.
    if((void*) rectClientArea == NULL){
	    return;
	};
	 
    rectClientArea = (void *) r;
    return;	
};

/*
int rectInit()
{}  
*/

//
// End.
//
