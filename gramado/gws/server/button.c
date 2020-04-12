
#include <api.h>
#include <gws.h>



/*
 *****************************************
 * gws_draw_button:
 *     Desenha um botão dado um tipo.
 *     
 * @todo: Medir o tamanho da string da tag.
 * @todo: O botão precisa de uma etiqueta, que pode ser uma string ou uma imagem.
 * Talvez uma estrutura de botão seja necessário, para armazenas coisas como 
 * deslocamento dentro da janela e endereço da imagem carregada como etiqueta.
 *
 * #importante: 
 * Retorna o ponteiro pra estrutura do botão.
 */
    

void *
gws_draw_button ( 
    unsigned char *string,
    int style,
    int state,
    int type, 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height, 
    unsigned long color )
{

    int Focus;    //(precisa de borda)
    int Selected;
    unsigned long border1;
    unsigned long border2;

    struct gws_button_d *b;


	// Validade da janela onde o botão está.
	// #todo: cheacr used, magic.
	
	//if ( (void *) window == NULL )
	//{
	//    return NULL;
	//}
	
	// Alocando memória para a estrutura do botão.
	// Inicializando a estrutura.

    b = (void *) malloc ( sizeof(struct gws_button_d) );

    if ( (void *) b == NULL ){
        gde_debug_print ("gws: draw_button. b fail\n");
        return NULL;

    }else{

        // Object.
        //b->objectType = ObjectTypeButton;
        //b->objectClass = ObjectClassGuiObjects;

        b->used = 1;
        b->magic = 1234;

        // button states:
        // 1. Default
        // 2. Focus
        // 3. Expanded/Toggled/Selected
        // 4. Disabled
        // 5. Hover and Active

        b->state = (int) state;

        //b->window = (void *) window; 
        b->string = string; 

        b->x = x;
        b->y = y;
        b->width = width;
        b->height = height;
 
        b->color = color; 
 
        b->Next = NULL; 

        // ...
    };


	//Devemos colocar o ponteiro na lista encadeada de botões 
	//dentro da estrutura da janela.
	//if( (void*) window->buttonList == NULL ){
	//	window->buttonList = (void*)b;
	//}


	//
	//  ## State ##
	//

	// #todo: 
	// Usar esquema padrão de cores.
	
    //button states:
    //0. NULL.
	//1. Default 
    //2. Focus
    //3. Expanded/Toggled/Selected
    //4. Disabled
    //5. Hover and Active

    switch (state)
    {
        case BS_NULL:
            break;

        // Não pressionado.
        case BS_DEFAULT:
            Selected = 0;
            b->selected = 0;
            border1 = GWS_COLOR_BUTTONHIGHLIGHT3;
            border2 = GWS_COLOR_BUTTONSHADOW3;
            b->border1 = GWS_COLOR_BUTTONHIGHLIGHT3;
            b->border2 = GWS_COLOR_BUTTONSHADOW3;
            break;

        case BS_FOCUS:
            border1 = COLOR_BLUE;
            border2 = COLOR_BLUE;
            b->border1 = COLOR_BLUE;
            b->border2 = COLOR_BLUE;
            break;
 
         // Pressionado.
        case BS_PRESS:
            Selected = 1;
            b->selected = 1;
            border1 = GWS_COLOR_BUTTONHIGHLIGHT3;
            border2 = GWS_COLOR_BUTTONSHADOW3;
            b->border1 = GWS_COLOR_BUTTONSHADOW3;
            b->border2 = GWS_COLOR_BUTTONHIGHLIGHT3;
            break;

        case BS_HOVER:
            b->color = (b->color + 20);
            break;
        
        case BS_DISABLED:
		    //Selected = 0;
			//b->selected = 0;
            border1 = COLOR_GRAY;
            border2 = COLOR_GRAY;
            b->border1 = COLOR_GRAY;
            b->border2 = COLOR_GRAY;
            b->color = COLOR_GRAY; 
            break;


        case BS_PROGRESS:
            break;

        // Valor inválido.
        default:  
            return NULL; 
            break;    
    };  
    


//
// Do draw the button.
//
	
//do_draw_button:

	// Usaremos retângulos para desenharmos o botão.
   
    // Temos a intenção de usar estilos diferentes, como flat design,
	// por exemplo.
	
	//
	// ## bg ##
	//
	
	rectBackbufferDrawRectangle ( x, y, width, height, color );

	//
	// ## 4 bordas ##
	//

	// #todo
	// As cores das bordas deve estar no esquema de cores.
	
	//board1, borda de cima e esquerda.
	rectBackbufferDrawRectangle ( x, y, width, 1, border1 );
	rectBackbufferDrawRectangle ( x, y, 1, height, border1 );

	//board2, borda direita e baixo.
	rectBackbufferDrawRectangle ( x +width -1, y, 1, height, border2 );
	rectBackbufferDrawRectangle ( x, y +height -1, width, 1, border2 );

	
    //
    // Do draw label.
    //
	
	// Se vamos usar uma imagem ao invés de uma string.
	//if(useImage == 1{ ... goto done;}
	
    //usado para calcular o tamanho de uma string.
     size_t tmp_size = (size_t) strlen ( (const char *) string );
	
	//if ( tmp_size > (width/8) )
	//{
	//    printf("fail");
	//}
	
	
    gde_debug_print ("button: >>> text\n");


    /*    
	//(a largura do botão menos a largura da string)/2
    unsigned long offset = ( ( (unsigned long) width - ( (unsigned long) tmp_size * (unsigned long) gcharWidth) ) / 2 );

	//button label
    if (Selected == 1)
    {
        dtextDrawString ( x +offset,y +8, COLOR_WHITE, string );

    }else{

		//b->width
		//b->height
		// (window->left +x) left 
		// (largura do botão, menos a largura da string)/2

        dtextDrawString ( x +offset, y +8, COLOR_TERMINALTEXT, string );

    };
    */
    
    // #debug: rotina provisória
    dtextDrawString ( x +20, y +20, COLOR_TERMINALTEXT, string );

    gde_debug_print ("button: >>> text ok\n");
    
	//Retornando o ponteiro para a estrutura do botão.
    return (void *) b;  
}



