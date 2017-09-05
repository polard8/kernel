/*
 * File: background.c 
 *
 * Descrição:
 *     Rotinas de configuração do background de um desktop.
 *     O background de um desktop é onde fica a imagem de pano de fundo.
 * Também é conhecido como Backbuffer.
 *
 *     Faz parte do módulo Window Manager do tipo MB.
 *
 * Histórico:
 *     Version: 1.0, 2013 - Created.
 *     Version: 1.0, 2014-2016 - Revisão.
 */


#include <kernel.h>

 
/*
 * backgroundDraw:
 *     Pinta um background em modo gráfico.
 *     Limpa a tela em modo texto. 
 */
void backgroundDraw(unsigned long color)
{
    unsigned long i;

	//Modo gráfico.
	if(VideoBlock.useGui == 1)
	{
	    
		//
		// @todo: Usar variável global. 
		// Ou variável presente na estrutura 'gui->'
		//
		
		//backgroundSetColor( (unsigned long) color);
		
		for(i=0; i<600; i++){
			my_buffer_horizontal_line( 0, i, 800, color);
		};
        goto done; 		
	};
	
	//Modo texto.
	if(VideoBlock.useGui == 0)
	{
		kclear(0);
		goto done; 
	};
	
	//Nothing
done:		
	//Cursor.
	g_cursor_x = 0;
	g_cursor_y = 0; 
    return;
};


/*
 * backgroundSetColor:
 *     Set background color in graphic mode.
 */
void backgroundSetColor(unsigned long color)
{
    if(gui->backgroundStatus == 0){
        return;
    };	

	if( (void*) gui->background != NULL ){
	    gui->background->color_bg = (unsigned long) color;
	};
	
done:
    return;
}


/*
 * backgroundRedraw:
 *     Redraw bg.
 */
void backgroundRedraw(unsigned long color)
{
    if(gui->backgroundStatus == 0){
        return;
    };
	
	if( (void*) gui->background != NULL ){
	   backgroundDraw(color);	
	};
 
done: 
	return;
};

//Constructor.
void backgroundBackground()
{
	//Cursor.
	g_cursor_x = 0;
	g_cursor_y = 0; 
	
	return; //Ainda não implementada.	
};

//Init.
int backgroundInit()
{
	backgroundBackground();
	//...
	
	return 0; //Ainda não implementada.
};	


//
//End.
//

