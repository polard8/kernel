/*
 * File: draw.c
 *
 * Descrição:
 *     Rotinas para desenhar no buffer alguns tipos de janelas. 
 *     o propósito é desenhar a janela no buffer dedicado da janela.
 * Por enquanto essas rotinas desenham a janela no backbuffer da tela.
 * 
 *     Usado pela função CreateWindow.
 *     Usado pela função redraw_window.
 *     10 tipos.
 *     Obs:  Pinta janela de um tipo para
 *           uma estrutura válida.
 *
 * Faz parte do módulo Window Manager do tipo MB.
 *
 * #bugbug: Esse módulo está suspenso. Mas as rotinas aqui poderão ser chamadas 
 * por CreateWindow ou qualquer outra rotina de criação de elementos gráficos.
 * aqui deve ser primitivas que fazem trabalho bruto, como é o caso de 
 * putpixel, draw line ...
 *          
 */


#include <kernel.h>


/*
 * do_draw:
 *     Adiciona os items à janela.( barras ...)
 *     É suporte à função create window.
 */
void do_draw(struct window_d *window, int type)
{
	return; //#cancelada
};



//
// Draw a popup window. ( WT_POPUP ).
//
void DrawPopUpWindow( struct window_d *w,
                      unsigned long x,  
                      unsigned long y,  
					  unsigned long width,  
					  unsigned long height,  
					  unsigned long color)
{   
	if( (void*) w == NULL ){
        return;
	};		

    // Sombra.
    drawDataRectangle( w->left +1, w->top +1, w->width, w->height, COLOR_BLACK);        
					   
    // Bg. 
	w->color_bg = COLOR_WINDOW;
	
	if( (unsigned long) w->type == WT_SIMPLE){
	    w->color_bg = color;
	};
	
    drawDataRectangle( w->left, 
	                   w->top, 
	                   w->width, 
					   w->height, 
					   w->color_bg );
    //Nothing.
    return;
};


//
// DrawEditBoxWindow. ( WT_EDITBOX ).
//
void DrawEditBoxWindow( struct window_d *w,
                        unsigned long x, 
                        unsigned long y, 
						unsigned long width, 
						unsigned long height, 
						unsigned long color)
{ 
	if( (void*) w == NULL ){
        return;
	};		

    // Sombra.
    drawDataRectangle( w->left +1, w->top +1, w->width, w->height, COLOR_BLACK);        
					   
    // Bg. 
	w->color_bg = COLOR_WINDOW;
	
	if( (unsigned long) w->type == WT_SIMPLE){
	    w->color_bg = color;
	};
	
    drawDataRectangle( w->left, 
	                   w->top, 
	                   w->width, 
					   w->height, 
					   w->color_bg );
    //Nothing.
    return;
};

 
// NORMAL ( bg + client area ,borda)  ( WT_OVERLAPPED )
//Completa para aplicativos.
void DrawNormalWindow( struct window_d *w,
                       char* titulo, 
                       unsigned long x, 
					   unsigned long y, 
					   unsigned long width, 
					   unsigned long height, 
					   unsigned long color)
{
	if( (void*) w == NULL ){
        return;
	};		

    // Sombra.
    drawDataRectangle( w->left +1, w->top +1, w->width, w->height, COLOR_BLACK);        
					   
    // Bg. 
	w->color_bg = COLOR_WINDOW;
	
	if( (unsigned long) w->type == WT_SIMPLE){
	    w->color_bg = color;
	};
	
    drawDataRectangle( w->left, 
	                   w->top, 
	                   w->width, 
					   w->height, 
					   w->color_bg );
					   
	//titulo + borda

	// Sem foco de entrada.
	if(w->id != window_with_focus){
	    w->color_bg = COLOR_GRAY;
	};
	
	// Com foco de entrada.
	if(w->id == window_with_focus){
	    w->color_bg = COLOR_BLACK;
	};
		
    drawDataRectangle( w->left, w->top, w->width, w->height, w->color_bg);        
	draw_string( w->left +8 +16 +8, w->top +8, COLOR_WHITE, titulo); 



    //client area
	
	w->color_bg = COLOR_WINDOW;
    drawDataRectangle( w->left +1, 
	                   w->top +24, 
					   w->width   -2, 
					   w->height -25, 
					   w->color_bg );

		
					   
    //Nothing.
    return;
};


//
// 4 DrawNormalEditWindow
//
void DrawNormalEditWindow( struct window_d *w,
                           unsigned long x, 
                           unsigned long y, 
						   unsigned long width, 
						   unsigned long height, 
						   unsigned long color)
{    
    //@todo:
    DrawEditBoxWindow( w, x, y, width, height, color);
	return;  
};



//
// 5 DrawMenuBarWindow
//
void DrawMenuBarWindow( struct window_d *w,
                        unsigned long x, 
                        unsigned long y, 
						unsigned long width, 
						unsigned long height, 
						unsigned long color)
{
	if( (void*) w == NULL ){
        return;
	};	
    create_menubar(w);  
    return;
};


//
// 6 DrawToolBarWindow
//
void DrawToolBarWindow( struct window_d *w,
                        unsigned long x, 
                        unsigned long y, 
						unsigned long width, 
						unsigned long height, 
						unsigned long color)
{   
	if( (void*) w == NULL){
        return;
	}else{
		
        w->x = 0;        
        w->y = 0;         
        w->width  = width;   
        w->height = height;    
  
        w->left = x;    
        w->top  = y;
        w->right  = (unsigned long) w->left + w->width;
        w->bottom = (unsigned long) w->top  + w->height;     		
	};

draw_window:
	
    // Sombra.
    drawDataRectangle( w->left, w->top, w->width, w->height, COLOR_BLACK);        
					   
    //'bg' 
	w->color_bg = color;
    drawDataRectangle( w->left +1, 
                       w->top  +1, 
                       w->width  -2, 
                       w->height -2, 
                       w->color_bg);

    //More?!
	
done:	
	return;  
};


//
// 7 DrawStatusBarWindow
//
void DrawStatusBarWindow( struct window_d *w,
                          unsigned char *string1, 
                          unsigned char *string2,
                          unsigned long x, 
                          unsigned long y, 
                          unsigned long width, 
                          unsigned long height, 
                          unsigned long color)
{
	if( (void*) w == NULL ){
        return;
	};
    StatusBar( w, string1, string2); 		
    return;
};


//
// 8 DrawTaskBarWindow
//
void DrawTaskBarWindow( struct window_d *w,
                        unsigned long x, 
                        unsigned long y, 
						unsigned long width, 
						unsigned long height, 
						unsigned long color)
{
	if( (void*) w == NULL ){
        return;
	};	
	
    //aviso - não é pra inicializar é so pra pintar
    // test_criar_task_bar();
   
done:
    return;
};


//
//DrawControlMenuWindow
//
void DrawControlMenuWindow( struct window_d *w,
                            unsigned long x, 
                            unsigned long y, 
							unsigned long width, 
							unsigned long height, 
							unsigned long color)
{
	if( (void*) w == NULL ){
        return;
	};	
	
	//@todo: Rotina ainda não implementada.
	
done:
    return; 
};


//app window (bg + client + menubar + status) 
void DrawAppWindow( struct window_d *w,
                    char* titulo, 
                    unsigned long x, 
					unsigned long y, 
					unsigned long width, 
					unsigned long height, 
					unsigned long color)
{
    DrawNormalWindow( w, titulo, x, y, width, height, color);                  
    return;
};

//
//fim.
//
