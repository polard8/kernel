/*
 * File: menubar.c
 *
 * Descrição:
 *     Rotinas de criação e gerenciamento de menubar.
 *     Faz parte do módulo Window Manager do tipo MB.
 *
 * Sobre menubar:
 *     Menu bar é a barra que fica logo abaixo da 
 *     barra de título de uma janela em sistemas como windows/linux.
 *
 *     Opcionalmente um sistema operacional pode ter apenas uma barra de menu 
 *     no topo da tela. Essa barra oferece um conjunto de menus para
 *     a manipulação do processo com o a janela ativa.
 *     Um indicador na barra pode mostrar qual é o processo com a janela ativa.
 *     como acontece no MAC.
 *     
 *
 * " Apple: The single menu bar at the top of the main display screen provides a home 
 * for the top-level menus in your app. 
 * In addition to system-provided and user-assigned items, 
 * you determine the menus that appear in the menu bar. "
 *
 * *Importate: ter apenas uma menubar no topo ao invés de ter uma menubar em cada janela
 *             pode trazer mais velocidade para o sistema.
 *
 * *IMPORTANTE: Toda janela tem menubar e o item '0' é o control menu da janela.
 *              Se a menubar esta desabilitada, pelo menos o item '0' está disponível. 
 *
 * Versão 1.0, 2015.
 */


 
#include <kernel.h>



/*
 * create_menu_bar:
 *     Cria a menu bar.
 *     Aquela barra simples abaixo da barra de título da janela.
 *     Argumento: Janela mãe.
 *     Retorna a janela (menubar).
 */
void *create_menubar(struct window_d *pwindow)
{	
    struct window_d *mWindow; 
    struct linkedlist_d *mb_linkedlist;
   
	//Parent window.	
    if( (void*) pwindow == NULL ){
	    printf("create_menubar:\n");
		refresh_screen();
	    //while(1){};
        return NULL;
    };
	
	// Size.
    unsigned long x      = pwindow->left; 
    unsigned long y      = pwindow->top;
	unsigned long width  = (unsigned long) pwindow->width; 
	unsigned long height = (unsigned long) (8*3);    //@todo: declarar constante.

	//
	// @todo: Checar limites.
	//
	
    // Cria uma janela para a menubar.
	mWindow = (void*) CreateWindow( 1, 0, 0, "Menubar", 
	                               x, y, width, height, 
							       pwindow, 0, 0, COLOR_GRAY); 
	if( (void*) mWindow == NULL ){
		printf("create_menubar error: Struct.\n");
		refresh_screen();
	    while(1){};
		//return NULL;	    
	}else{
	    RegisterWindow(mWindow);
	};
	
	//
	// @todo: Chacar se a estrutura está inicializada.
	//
	
	//
	// gui->mb é a menubar atual.
	//
	
	// Menu structure. (Cria uma estrutura para o menu da menubar).
	gui->mb = (void*) malloc(sizeof(struct menu_d));
    if( (void*) gui->mb == NULL ){
	    printf("create_menubar error: Menu struct.\n");
		refresh_screen();
		while(1){}	
	}
	else
	{
	   //Registra na estrutura de menu a janela que é o menu.
	    gui->mb->menuWindow = mWindow;

		//Registra na estrutura a janela à qual o menu pertence.(parent window)
		gui->mb->parentWindow = pwindow;
		
		//registrao menu da janela.
		mWindow->barMenu = gui->mb; 
		
		RegisterMenu(gui->mb);
		
		//@todo: menu id ... contagem ...
	};
	
	// Array para items.
	gui->mb->Items = (void*) malloc( sizeof(struct menuitem_d) * 16 );
    if( (void*) gui->mb->Items == NULL){
	    printf("create_menubar error: Menu array struct.\n");
		refresh_screen();
		while(1){}        
	};
	
    // Linked list. (linked list na menubar).	
    mb_linkedlist = (void*) malloc( sizeof(struct linkedlist_d));
    if( (void*) mb_linkedlist == NULL){
	    printf("create_menubar error: linked list struct.\n");
		refresh_screen();
		while(1){}        
	}
	else
	{  
	    //registra na estrutura da janela.
	    mWindow->linkedlist = mb_linkedlist;
	};
	
	
// Done ~ Retorna a janela (menubar).
done:     
    return (void*) mWindow;
};



/*
 * create_menubar_item:
 *    Os ítens são barras horizontais e o tamanho se adapta à string. 
 */
int create_menubar_item(struct menu_d *menu, unsigned char *string, int status)
{
	int Selected = 0;
	unsigned long Color = COLOR_WINDOW;    
	struct window_d *miWindow; 
	
    if( (void*) menu == NULL){
        return (int) 1;
    };

	// Count.	
	menu->itemCount++;
	
	if( menu->itemCount > 16){
		printf("create_menu_item error: Limits.");
		refresh_screen();
		return 1;
	};	

	//Selected.
	if(status == 0 || status == 1){
	    Selected = status;	
	}else{
		Selected = 0;
	};
		
	gui->mb->Items[menu->itemCount].Selected = (int) Selected;
	
    //
	// Menuitem structure. 
	//

    //os itens foram criados previamente.
		/*
	 * Ver se não está corrompido
	*/
	
	/* Validate
	if( menu->Items[i].Used != 1)
	{
	    printf("menu item not Used\n");
		return 1;
	};
	*/
	
	
	//
	// @todo:
	//     Checar o número de itens existentes.
	//     Checar o número máximo possivel.
	//     Checar o id do proximo menuitem.
	//     Checar a posição x do próximo item.
	//     Continua ...
	//
 
	// Ajust string.
    const char *s = (const char*) string; //Usar tipo const char.	

    // Dimensões.	
	unsigned long x = menu->menuWindow->left;
	unsigned long y = menu->menuWindow->top;

	menu->newitemLeft = x;
	menu->newitemTop  = y;
	
    //Largura e Altura.
	unsigned long width  = (unsigned long) strlen(s);
	width = (unsigned long) (width*8)+(2*8);  //char size = 8.um espaco de cada lado.	
	unsigned long height = (8*3);
 
    gui->mb->Items[menu->itemCount].x = (unsigned long) x;
    gui->mb->Items[menu->itemCount].y = (unsigned long) y;	
    gui->mb->Items[menu->itemCount].left   = (unsigned long) menu->newitemLeft;
    gui->mb->Items[menu->itemCount].top    = (unsigned long) menu->newitemTop;
    gui->mb->Items[menu->itemCount].width  = (unsigned long) width;
    gui->mb->Items[menu->itemCount].height = (unsigned long) height;
    gui->mb->Items[menu->itemCount].string = (unsigned char *) string;    //test.
    
	//
    // Create.
    //	
   
   //selected?
    if( Selected == 1){
        gui->mb->selectedItem = (int) menu->itemCount;
    };
   
  	//
	// Draw.
	//
	
draw_item:

    if(Selected == 1){	
        Color = COLOR_BLUE;
    }else{
	    Color = COLOR_WINDOW;
	};   
	
	miWindow = (void*) CreateWindow( 1, 0, 0, "MenubarItem", 
	                                 x, y, width, height, 
							         menu->menuWindow, 0, 0, Color);
	if( (void*) miWindow == NULL){
		printf("create_menubar_item error: Struct.\n");
		refresh_screen();
	    //while(1){};
		return (int) 1;	    
	}
	else
	{
	    RegisterWindow(miWindow);
	};
	
	// String.
strings:

	if(Selected == 1){	
        Color = COLOR_WHITE;	
    }else{
	    Color = COLOR_WINDOWTEXT; 
	};	
	
	draw_string( menu->newitemLeft +8, menu->newitemTop +8, Color, string); 

    // Ajust next.	
	menu->menuWindow->left = (unsigned long) x + width;
	menu->menuWindow->top  = (unsigned long) y;
	
	//continua...	
		
done:     
    return (int) 0;
};


//@todo: errado: o certo seria mb_selectmenu()
int select_menubar_item(int n)
{
    if(n < 0){
	   return (int) 1;
	};
    gui->mb->Items[n].Selected = 1;
    return (int) 0;
};

//@todo: errado: o certo seria mb_unselectmenu()
int unselect_menubar_item(int n)
{
    if(n < 0){
	   return (int) 1;
	};
    gui->mb->Items[n].Selected = 0;
    return (int) 0;
};


int redraw_menubar_item(int n)
{
    int Selected;
	
    if(n<0){
	    return (int) 1;
	};

    unsigned long x = (unsigned long) gui->mb->Items[n].x; 
    unsigned long y = (unsigned long) gui->mb->Items[n].y;
	//unsigned long width  = 60; 
	unsigned long width  = (unsigned long) gui->mb->Items[n].width;
	unsigned long height = (unsigned long) gui->mb->Items[n].height;
   
    Selected = (int) gui->mb->Items[n].Selected; 
    
	//Desenha o item.
    if(Selected == 1){
	    drawDataRectangle( x, y, width, height, COLOR_BLUE);  
    }else{
	    drawDataRectangle( x, y, width, height, COLOR_WINDOW);  	
	};
	
	//Escreve.	
strings:
	draw_string( gui->mb->Items[n].left, 
	             gui->mb->Items[n].top, 
				 COLOR_WINDOWTEXT, 
				 gui->mb->Items[n].string );
				 
done:
    return (int) 0;
};




int get_menubar_selected_item()
{
    return (int) gui->mb->selectedItem;
};




/*
 * menubarX:
 *     Cria uma menubar na janela screen.
 *     Usanda para teste de criação de menubars.
 */
int menubarX()
{
	//Usando a janela screen anteriormente criada.
    if( (void*) gui->screen == NULL ){
        return (int) 1;
    };		
	
	//
    // Cria a janela e o menu. 
	// (o argumento é a janela mãe)
	// (retorna a janela da menubar)
    //	
	
	//o handle da menubar window.
    gui->mbhWindow = (void *) create_menubar(gui->screen);
	if( (void *) gui->mbhWindow == NULL ){
	    printf("menubarX:");
		refresh_screen();
		while(1){}	
	};
	
	
	initmenuArray( gui->mbhWindow->barMenu, 4);
	
	// Cria um menuitem, dado um menu da janela.
	create_menubar_item(gui->mbhWindow->barMenu,"Control Panel",1); //painel
    create_menubar_item(gui->mbhWindow->barMenu,"Computer"     ,0); //files and folders
	create_menubar_item(gui->mbhWindow->barMenu,"File"         ,0); //gerencia arquivos
	create_menubar_item(gui->mbhWindow->barMenu,"Window"       ,0); //control menu da janela.
	
	
	//More?!
	
done:
    SetProcedure( (unsigned long) &MenuBarProcedure);	 
    return (int) 0;
};


/*
 * MenuBarProcedure:
 *     O procedimento de janela da menu bar do desktop.
 *     seleciona os ítens da menubar. 
 */																
unsigned long MenuBarProcedure( struct window_d *window, 
                                int msg, 
								unsigned long long1, 
								unsigned long long2) 
{
    int n;
	
    n = (int) get_menubar_selected_item();
	
	//Limits.
	if(n < 0 || n >= 4){
		n = 0;
	};
		
	unselect_menubar_item(n);
    
	
	//Talvez deva implementar esse filtro.
    //if( (void*) window == NULL ){return 0;}
	
	switch(msg)
	{	
	
        case MSG_KEYDOWN:
            switch(long1)
            {
                case VK_ESCAPE:	
				   SetProcedure( (unsigned long) &system_procedure);						
				   break;
				   
                default:
                    break; 
            };
        break;
	
		case MSG_SYSKEYDOWN:                 
            switch(long1)	       
            {   
				case VK_F1: n--; break;  //left (circula)
                case VK_F2: n++; break;  //right  (circula)										
				default:  break;
		    };              
        break;
		
		default:
		    //Nothing.
		    break;
	};
	
    select_menubar_item(n);
    redraw_menubar_item(n);
    //refresh_screen(); 	

	n = (int) get_menubar_selected_item();

	switch(n)
	{
		case 0:
		    ControlMenu();
		    break;
	    
		default:
		   //menuAction(n);
		   break;
	
	};
	
	
// Done.
done:
	//Refresh screen. 
	if(VideoBlock.useGui == 1){
	    refresh_screen();
	};

	return (unsigned long) 0;
};

/*
int menubarInit()
{}
*/

//
// End.
//

