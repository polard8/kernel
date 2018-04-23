/*
 * File: gramado\gui\grid.c
 *
 *     ****    KERNEL GRID    ****
 * 
 * Descrição:
 *     Um pequeno grid no topo da tela.
 *     O objetivo é oferecer acesso aos principais programas do 
 * sistema, mesmo quando o gerenciador de prrogramas não esteja em uso.
 *     Em outras palavras é um "MINI GERENCIADOR DE PROGRAMAS" dentro do 
 * kernel base.
 *
 * Esse mini gerenciador de programas se chamará 'Kernel Grid'.
 * +Uma janela simples será o backgroundo do Kernel Grid e servirá de 
 * referência para o posicionamento dos ítens.
 * +Cada ítem é um link para um programa em user mode que esteja rodando
 * no momento. 
 * +Clicar no ítem restaura a janela do aplicativo se ele estiver minimizado,
 * ou minimiza se ele estiver em outro estado.
 * 
 * Obs: Podemos usa botões para os ítens do grid.
 *
 * Versão 1.0, 2015.
 */


#include <kernel.h>



/*
 * InitializeGrid:
 *     Desenha o grid  
 *
 */
int InitializeGrid(struct grid_d *g, int n, int view)
{	
	struct window_d *gridWindow;   //janela.
	struct button_d *griditemWindow; //botão
	
    int i = 0;
	unsigned long x, y, cx, cy;
	
	unsigned long WindowLeft;
	unsigned long WindowTop;
	unsigned long WindowWidth;
    unsigned long WindowHeight;
	unsigned long ItensCount = (unsigned long) n; //quantidade de itens.

	// dimensões dos botões.
	x = 0; //deslocamento em relação à margem da janela de background 
	y = 0; //deslocamento em relação à margem da janela de background 
	
	
	if( (void*) g == NULL ){
		return 1;
	}
	
	if( g->used != 1 || g->magic != 1234 ){
		return 1;
	}
	
	if( view == GRID_HORIZONTAL)
	{
		WindowLeft = 10;
		WindowTop = 10;
		WindowWidth = (800-20); //menos margens laterais.
	    WindowHeight = (600/8);
		cx = (unsigned long) (WindowWidth/ItensCount);    //largura do ítem.
	    cy = (unsigned long) (WindowHeight);              //altura do ítem.
		
	    //horizontal..
		//métrica da área de trabalho.
	    replace_window(gui->main, 0, WindowHeight);           //left, top
	    resize_window(gui->main, 800, (600-WindowHeight));	 //width, height
	
	};

	if( view == GRID_VERTICAL)
	{
		WindowLeft = 0;
		WindowTop = 0;
		WindowWidth = (800/4);    //docked right
	    WindowHeight = 600;
	    cx = (unsigned long) (WindowWidth);                 //largura do ítem.
	    cy = (unsigned long) (WindowHeight/ItensCount);       //altura do ítem.
		
		//vertical.
	    //métrica da área de trabalho.
	    replace_window(gui->main, WindowWidth, 0);           //left, top
	    resize_window(gui->main, (800-WindowWidth), 600);	 //width, height
	
	};
	
	//
	// Background do grid da janela principal.
	//
	 
	//o grid pertence a janela principal. 
	
	gridWindow = (void*) CreateWindow( 1, 0, 0, "Grid Bg", 
	                                   WindowLeft, WindowTop, WindowWidth, WindowHeight, 
							           gui->main, 0, COLOR_BACKGROUND, 0 ); //popup						
    if( (void*) gridWindow == NULL)
	{
	    printf("drawScreenGrid fail: bg.\n");
		refresh_screen();
	    while(1){};
	}else{
		RegisterWindow(gridWindow);
	};	
	
	
	// Pintando os ítens.
	
	//
	// * Nessa hora devemos pegar o nome dos processos e colocar como etiqueta do ítem.
	//
	
	unsigned char *string; //label.
	string = "$";
	
	
	//Os processos de usuário começam em 100.
	i = 100;
	ItensCount += 100;
	
	//draw (horizontal.)
    while(i < ItensCount)
    {		
		//grid item 
	    griditemWindow = (void*) draw_button( gridWindow, string, 1, x, y, cx, cy, COLOR_BUTTONFACE);    						                 						
        if((void*) griditemWindow == NULL){
	        printf("drawScreenGrid fail: ítem.\n");
		    refresh_screen();
			while(1){};		    
	    };
		
		//@todo: fazer a lista encadeada de botões.
		//g->b = (void*) griditemWindow;
		
		if( view == GRID_HORIZONTAL ){
		    x = (unsigned long) x + cx; //horizontal.	
		}
		
		if( view == GRID_VERTICAL ){
			y = (unsigned long) y + cy;   //vertical.
		}
		    
				
		i++;			
	};
		
	
done:
    return (int) 0;
};


/*
 * CreateGrid:
 *     Inicializa a estrutura do grid da janela principal. 
 * Área de trabalho.
 *
 */
void *CreateGrid()
{
	struct grid_d *g;
	
	g = (void*) malloc( sizeof( struct grid_d) );
	
	if( (void*) g == NULL ){
		return NULL;
	}else{
		
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
    return (void*) g;
};


//função para criar o grid do kernel.
//gerenciado pelo procedimento de janela do sistema.
int grid(int view)
{
	int Status = 1;  //erro
	struct grid_d *g;
	int n = 8;
	
	g = (void*) CreateGrid();
	
	//se o objeto for válido.
	if( (void*) g != NULL )
	{
		//Ele será o grid do kernel.
		GRID = (void*) g;
		
		//Inicializaremos a estrutura e pintaremos o grid.
	    Status = (int) InitializeGrid( g, n, view);	
	};	
		
	return (int) Status; 	
}

//
//fim.
//
