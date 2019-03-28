/*
 * File: gws\gws\grid.c
 *
 *     # grid support #
 *
 * History:
 *     2015 - Created by Fred Nora.
 */


#include <kernel.h>


/*
 ********************************************
 * InitializeGrid:
 *     Desenha o grid  
 *
 */
int 
InitializeGrid ( struct window_d *window, 
                 struct grid_d *g, 
                 int n, 
				 int view )
{	
	struct window_d *gridWindow;        //bg.
	struct window_d *griditemWindow;    //item.
	
    int i = 0;
	unsigned long x, y, cx, cy;
	
	unsigned long WindowLeft = 0;
	unsigned long WindowTop = 0;
	unsigned long WindowWidth = 0;
    unsigned long WindowHeight = 0;
	
	//quantidade de itens.
	unsigned long ItensCount = (unsigned long) n; 

	// dimensões dos botões.
	x = 0; //deslocamento em relação à margem da janela de background 
	y = 0; //deslocamento em relação à margem da janela de background 
	
	
	if ( (void *) g == NULL )
	{
		printf("InitializeGrid: g\n");
		goto fail;
	}else{
		
	    if ( g->used != 1 || g->magic != 1234 ){
		    printf("InitializeGrid: g validation\n");
		    goto fail;
	    }
		//...
	};
	
	
	if ( (void *) window == NULL )
	{
		//fail;
		printf("InitializeGrid: window\n");
		goto fail;
		
	}else{
		
		//fail.
		if ( window->used != 1 || window->magic != 1234 ){
            printf("InitializeGrid: validation\n");
            goto fail; 			
		}
		
		//@todo: filtros.
		
		if ( view == GRID_HORIZONTAL )
	    {
		    WindowLeft = window->left;
	 	    WindowTop = window->top;
		    WindowWidth = (window->width); //menos margens laterais.
	        WindowHeight = (window->height);
		    
			cx = (unsigned long) (WindowWidth/ItensCount);    //largura do ítem.
	        cy = (unsigned long) (WindowHeight);              //altura do ítem.
		
	        //horizontal..
		    //muda o posicionamento e o tamanho.
			//mas temos que atuar em uma janela já registrada.
			//estamos atuando sobre a janela main modificando o tamanho dela 
			//de acordo com o grid criado. Mas não é isso que queromos por enquanto.
			
	        //replace_window( gui->main, 0, WindowHeight );        //left, top
	        //resize_window( gui->main, 800, (600-WindowHeight) ); //width, height
	    };

	    if( view == GRID_VERTICAL )
	    {
		    WindowLeft = window->left;
	 	    WindowTop = window->top;
		    WindowWidth = (window->width /4);    //docked LEFT
	        WindowHeight = window->height;
	        
			cx = (unsigned long) (WindowWidth);                 //largura do ítem.
	        cy = (unsigned long) (WindowHeight/ItensCount);     //altura do ítem.
		
		    //vertical.
		    //muda o posicionamento e o tamanho.
			//mas temos que atuar em uma janela já registrada.
			//estamos atuando sobre a janela main modificando o tamanho dela 
			//de acordo com o grid criado. Mas não é isso que queromos por enquanto.
			
	        //replace_window( gui->main, WindowWidth, 0 );        //left, top
	        //resize_window( gui->main, (800-WindowWidth), 600 ); //width, height
	    };		
		
	    //...	
	};
	
	// Background do grid da janela principal.
		 
	//o grid pertence a janela principal. 
	
	gridWindow = (void *) CreateWindow ( 1, 0, 0, "Grid Bg", 
	                        WindowLeft, WindowTop, WindowWidth, WindowHeight, 
							window, 0, COLOR_BACKGROUND, 0 ); 
							
    if( (void*) gridWindow == NULL )
	{
	    printf("drawScreenGrid: gridWindow\n");
		goto fail;
	}else{
		RegisterWindow(gridWindow);
	};	
	
	// Pintando os ítens.
	
	// * Nessa hora devemos pegar o nome dos processos e 
	// colocar como etiqueta do ítem.
	
	unsigned char *string; //label.
	string = "$";
	
	//Os processos de usuário começam em 100.
	i = 100;
	ItensCount += 100;
	
	//draw (horizontal.)
    while (i < ItensCount)
    {		
		//grid item 
		//#bugbug tem que usar create window.
	    //griditemWindow = (void*) draw_button( gridWindow, string, 1, x, y, cx, cy, COLOR_BUTTONFACE);    						                 						
        
	    griditemWindow = (void *) CreateWindow ( WT_BUTTON, 0, 0, "Item", 
	                                x, y, cx, cy, 
							        gridWindow, 0, COLOR_TERMINAL, COLOR_TERMINAL ); 		
									   
		if ( (void *) griditemWindow == NULL )
		{
	        printf("drawScreenGrid fail: ítem\n");
		    goto fail;		    
	    }else{
			
			RegisterWindow (griditemWindow);
		}
		
		//@todo: fazer a lista encadeada de botões.
		//g->b = (void*) griditemWindow;
		
		if( view == GRID_HORIZONTAL ){
		    x = (unsigned long) x + cx + 2; //horizontal.	
		}
		
		if( view == GRID_VERTICAL ){
			y = (unsigned long) y + cy;   //vertical.
		}   
				
		i++;			
	};
		
	
//done:

    refresh_rectangle ( WindowLeft, WindowTop, WindowWidth, WindowHeight );
		
    return (int) 0;
fail:
    refresh_screen();
    return (int) 1;
};


/*
 *******************************************************
 * CreateGrid:
 *     Create Grid Object,
 *     Inicializa a estrutura do grid da janela principal. 
 * Área de trabalho.
 * @todo: #define gridObject CreateGrid
 */
void *CreateGrid (){
	
	struct grid_d *g;
	
	g = (void *) malloc ( sizeof( struct grid_d) );
	
	if ( (void *) g == NULL )
	{
		//@todo: Message.
		return NULL;
		
	} else {
		
		//Object.
		g->objectType = ObjectTypeGrid;
		g->objectClass = ObjectClassGuiObjects;
		
		g->used = 1;
		g->magic = 1234;
		g->window = NULL;
		g->b = NULL;
		g->count = 0;
		//...
		
		g->next = NULL;
	};
    return (void *) g;
};


//função para criar o grid do kernel.
//gerenciado pelo procedimento de janela do sistema.
int grid( struct window_d *window, 
          int n, 
		  int view )
{
	int Status = 1;  //erro
	struct grid_d *g;
	
	//Cria o objeto grid. 
	//apenas a estrutura.
	g = (void *) CreateGrid ();
	
	//se o objeto for válido.
	if( (void *) g != NULL )
	{
		//Ele será o grid do kernel.
		GRID = (void *) g;
		
		//Inicializaremos a estrutura e pintaremos o grid.
	    Status = (int) InitializeGrid ( window, g, n, view );	
	};	
		
	return (int) Status; 	
};


//
// End.
//
