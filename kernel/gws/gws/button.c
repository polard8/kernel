/*
 * File: gws\button.c
 *
 * Descrição:
 *     Rotinas de criação e gerenciamento de botões. 
 *     Faz parte do módulo Window Manager do tipo MB.
 *
 * Refletindo:
 *    Talvez seja certo criar opções de rotinas de criação de botões.
 * Por exemplo: draw_3d_button e draw_flat_button 
 * seria muito confuso uma rotina só que acione o tipo via argumento.
 *
 *  #todo: precisamos de uma função de redraw button 
 *         para o caso de redraw da janela do tipo botão.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2018 - redraw_button created. #todo  
 */


#include <kernel.h>



/*
 * draw_button:
 *     Desenha um botão dado um tipo.
 *     
 * @todo: Medir o tamanho da string da tag.
 * @todo: O botão precisa de uma etiqueta, que pode ser uma string ou uma imagem.
 * Talvez uma estrutura de botão seja necessário, para armazenas coisas como 
 * deslocamento dentro da janela e endereço da imagem carregada como etiqueta.
 *
 * #importante: 
 * Retorna o ponteiro pra estrutura do botão.
 *
 */
void *draw_button ( struct window_d *window,
                    unsigned char *string,
                    unsigned long type, 
                    unsigned long x, 
                    unsigned long y, 
                    unsigned long width, 
                    unsigned long height, 
                    unsigned long color )
{
	int Selected;
	unsigned long border1;
    unsigned long border2;
	
	struct button_d *b;
	
	//validade da janela onde o botão está.
	if ( (void *) window == NULL )
	{
	    return NULL;
	}
	
	//Alocando memória para a estrutura do botão.
	b = (void *) malloc ( sizeof(struct button_d) );
    
	if ( (void *) b == NULL )
	{
		return NULL;
		
	}else{
		
		// Object.
		b->objectType = ObjectTypeButton;
		b->objectClass = ObjectClassGuiObjects;
		
	    b->used = 1;	
	    b->magic = 1234;
		
		b->string = string;  //Label.
        b->type = type;
        b->x = x;
        b->y = y;
        b->width = width;
        b->height = height;
		
        b->window = (void *) window;
        b->color = color; 	
        b->Next = NULL;		 
		//...
	};
	
	//Devemos colocar o ponteiro na lista encadeada de botões 
	//dentro da estrutura da janela.
	//if( (void*) window->buttonList == NULL ){
	//	window->buttonList = (void*)b;
	//}
	
	//Todo: Usar esquema padrão de cores.
	
    //Quem chamou precisa saber ao menos o tipo de botão que quer.	
    if (type == 0)
	{
		//printf("draw_button: The button needs a type.\n");
		//refresh_screen();
        return NULL;
    };    
	
    switch (type){
		
        //Não pressionado.
        case BN_DOWN:
		    Selected = 0;
			b->selected = 0;
		    border1 = COLOR_BUTTONHIGHLIGHT2;
			border2 = COLOR_BUTTONSHADOW2;
			b->border1 = COLOR_BUTTONHIGHLIGHT2;
			b->border2 = COLOR_BUTTONSHADOW2;
            goto do_draw_button;			
			break;
                                    
        //Precionado.
        case BN_UP:
		    Selected = 0;
		    b->selected = 0;
			border1 = COLOR_BUTTONSHADOW2;
			border2 = COLOR_BUTTONHIGHLIGHT2;
            b->border1 = COLOR_BUTTONSHADOW2;
			b->border2 = COLOR_BUTTONHIGHLIGHT2;
			goto do_draw_button;			
            break;
                       
         //Selecionado. (highlight)
        case BN_SELECTED:
		    Selected = 1;
			b->selected = 1;
		    border1 = COLOR_BUTTONHIGHLIGHT2;
			border2 = COLOR_BUTTONSHADOW2;
            b->border1 = COLOR_BUTTONHIGHLIGHT2;
			b->border2 = COLOR_BUTTONSHADOW2;
			goto do_draw_button;			
            break;
        
		default:  
		    return NULL; 
            break;    
    };  

//
// Do draw the button.
//
	
do_draw_button:

	// Usaremos retângulos para desenharmos o botão.
   
    // Temos a intenção de uar estilos diferentes, como flat design,
	// por exemplo.
	
	//bg
	drawDataRectangle ( window->left +x, window->top +y, 
	    width, height, color );
    
	//board1, borda de cima e esquerda.
	drawDataRectangle ( window->left +x, window->top +y, 
	    width, 1, border1 );
		
	drawDataRectangle ( window->left +x, window->top +y, 
	    1, height, border1 );

	//board2, borda direita e baixo.
	drawDataRectangle ( window->left +x +width -1, window->top +y, 
		1, height, border2 );
					   
	drawDataRectangle ( window->left +x, window->top +y +height -1, 
		width, 1, border2 );

//
// Do draw label.
//
					   
do_draw_label:

	
	// Se vamos usar uma imagem ao invés de uma string.
	//if(useImage == 1{ ... goto done;}
	
	//button label								   
    if (Selected == 1)
	{
	    draw_string ( window->left +x +8, window->top +y +8, 
			COLOR_WHITE, string );	
			
    }else{
		
		
	    //draw_string( window->left +x +8, 
		//             window->top  +y +8, 
		//			 COLOR_WINDOWTEXT, 
		//			 string);	

	    draw_string ( window->left +x +8, window->top +y +8, 
			COLOR_TERMINALTEXT, string );	
	};
	
	//
	// @todo: Algo mais?
	//
	
// Done! 
done:
    
	//Retornando o ponteiro para a estrutura do botão.
    return (void *) b;          
};


/*
int buttonInit()
{}
*/


//
// End.
//

