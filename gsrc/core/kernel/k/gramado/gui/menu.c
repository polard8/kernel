/*
 * File: gui\menu.c 
 *
 * Descrição:
 *     Criação e gerenciamento de menus.
 *     Faz parte do módulo Window Manager do tipo MB.
 *
 * History:
 *     2015 -  Created by Fred Nora.
 */

 
#include <kernel.h>


/*
 * menuIsMenu:
 *     Testa através do handle passado, se é uma menu ou não.
 *     0 = Yes; 1 = Not; 
 */
/* 
int menuIsMenu(struct menu_d *menu);
int menuIsMenu(struct menu_d *menu)
{
	//@todo:Implementar.
	return 0;
};
*/


/*
 ******************************************************************
 * create_menu:
 *     Cria um menu e retorna o ponteiro pra janela do menu.
 */
void *create_menu( struct window_d *pwindow,    //Parent window. 
                   unsigned long iCount,        //Contagem de ítems. 
				   unsigned long sCount,        //Contagem de espaçadores.
				   int type,                    //Horizontal ou vertical
				   int style )                  //Estilo.
{ 
	struct window_d *hWindow;           //Window.
	struct linkedlist_d *LinkedList;    //Linked list.
	
	unsigned long iHeight;    //Altura do ítem.
    unsigned long sHeight;    //Altura do espaçador.
	unsigned long x;
	unsigned long y;
	unsigned long width;
	unsigned long height;
	
	// Structure.
    if( (void*) pwindow == NULL )
	{
	    //@todo: Devemos retornar e mostrar mensagem de erro.
		printf("create_menu:");
		refresh_screen();
	    while(1){};
       // return NULL;
    }else{
	    
		// Size.
	    iHeight = (unsigned long) (8*3);    //Altura do ítem.
	    sHeight = (unsigned long) (3);      //Altura do espaçador.
	
        x      = (unsigned long)  pwindow->left; 
        y      = (unsigned long)  pwindow->top;
	    width  = (unsigned long) (pwindow->width / 4);  //(640/4); 
	    height = (unsigned long) (pwindow->height);     //(iHeight*iCount)+(sHeight*sCount); 
		//...
	};

	
	//
	// @todo: Checar limites.
	//
	
	
    //
    // Create.
    //	
	
	//@todo: Criar as definições de tipos de menu.
	
	switch(style)
	{ 
	    case 0:  
		    width  = (unsigned long) (pwindow->width);
		    height = (unsigned long) ( (iHeight*iCount) + (sHeight*sCount) ); 
		    goto do_create;
            break;

	    case 1:  
		    width  = (unsigned long) (pwindow->width);
		    height = (unsigned long) ( (iHeight*iCount) + (sHeight*sCount) ); 
		    goto do_create;
            break;

	    case 2: 
            width  = (unsigned long) (pwindow->width); 		
		    height = (unsigned long) ( (iHeight*iCount) + (sHeight*sCount) ); 
			goto do_create;
            break;							
			
		//...	
		
        //Normal tipo control menu.		
		default:
		    width  = (unsigned long) (pwindow->width);
		    height = (unsigned long) ( (iHeight*iCount) + (sHeight*sCount) ); 
		    goto do_create;
            break;

	};
	
	//
	// Do create ~ Efetua a criação da janela que conterá itens.
	//
	
do_create:

    hWindow = (void*) CreateWindow( 1, 0, 0, "Menu",
	                                x, y, width, height,
						           pwindow, 0, 0, COLOR_BLACK );
	if( (void*) hWindow == NULL )
	{
		
		printf("create_menu: hWindow\n");
		refresh_screen();
	    while(1){};
		//return NULL;  
	}else{
		RegisterWindow( hWindow );
	};
	
		
	//
	// Menu structure. (Cria uma estrutura para o menu).
	//
	
	menuDefault = (void*) malloc( sizeof(struct menu_d) );  
	if( (void*) menuDefault == NULL )
	{
	    printf("create_menu: menuDefault\n");
		refresh_screen();
		while(1){};
		
	}else{
		
	    //Registra na estrutura de menu a janela que é o menu.
	    menuDefault->menuWindow = (void*) hWindow;

		//Registra na estrutura a janela à qual o menu pertence.(parent window)
		menuDefault->parentWindow = (void*) pwindow;
		
		//horizontal ou vertical
		menuDefault->Type = type;
		
		//estilo de menu, aparencia. detalhes.
		menuDefault->Style = style;
		
		//Posicionamento do próximo ítem a ser criado.
		//no caso o primeiro ítem.
		//vamos usar a janela do menu como referencia.
		menuDefault->newitemLeft =  hWindow->left;
		menuDefault->newitemTop  =  hWindow->top;
		
		//Zerar a contagem de itens quando cria um menu.
		menuDefault->itemCount = 0;
		
		//@todo: menu id ... contagem ...
	};

	//registrao menu da janela.
	hWindow->defaultMenu = (void*) menuDefault; 
	
    //
	// Array para items.
	//
	
	//Limits.
	if(iCount < 1){
		iCount = 1;
	};
	
	
	//Limits.
	if(iCount >= MENUITEM_COUNT_MAX)
	{
	    iCount = (MENUITEM_COUNT_MAX-1);
		printf("create_menu error: Itens limits!\n");		
	};
	
	
	
	/*
	 * O array pode ser inicializado depois.
	 *
	    menuDefault->Items = malloc( sizeof(struct menuitem_d) * iCount );
        if( (void*) menuDefault->Items == NULL)
	    {
	        printf("create_menu error: Menu array struct.\n");
		    refresh_screen();
		   while(1){}        
	    };
	*/	
 
    //
    // Linked list. (linked list no menu)	
    //
		
    LinkedList = (void*) malloc( sizeof(struct linkedlist_d) );
    if( (void*) LinkedList == NULL )
	{
	    printf("create_menu: LinkedList\n");
		refresh_screen();
		while(1){}        
	}
	else
	{  
	    //registra na estrutura da janela.
	    hWindow->linkedlist = (void*) LinkedList;
	};
	
	
//
// Done ~ Retorna a janela (menubar) que é um menu.
//	
done:  
    RegisterMenu(menuDefault);
    SetFocus(hWindow);   
    return (void*) hWindow;
};


/*
 * create_menu_item:
 *     Create a menu item. 
 *     Obs: Os menus são verticais.
 */
int create_menu_item( struct menu_d *menu, 
                      unsigned char *string, 
					  int status )
{
    int Selected = 0;
	unsigned long Color = COLOR_WINDOW;
	struct window_d *hWindow;
	
	// Menu structure.
    if( (void*) menu == NULL ){
        return (int) 1;
    }
	
	menu->itemCount++;	 
	
	//Limits.
	if( menu->itemCount >= MENUITEM_COUNT_MAX )
	{
		printf("create_menu_item:\n");
		refresh_screen();
		while(1){};
		//return 1;
	};
	
	//Selected.
	Selected = status;	
	menu->Items[menu->itemCount].Selected = (int) Selected;

    /*
	 * Validate item
	 *
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
    const char *s = (const char*) string;    //@todo: Usar tipo 'const char'.	

    // Dimensões.
	unsigned long x = (unsigned long) menu->menuWindow->left;
	unsigned long y = (unsigned long) menu->newitemTop;
	unsigned long width;
	unsigned long height;
	
	menu->newitemLeft = (unsigned long) x;
	menu->newitemTop  = (unsigned long) y;
	
	
	//menu window.
	if( (void*) menu->menuWindow == NULL )
	{
	    printf("menu window fail.\n");
		return (int) 1;
	}
	else
	{
		height = (unsigned long) (8*3);
		
		//...
		
		if(menu->Type == 0)
		{		
		    width  = (unsigned long) menu->menuWindow->width; 
            //height = (unsigned long) menu->menuWindow->height;			
	        goto draw_window;
		};
		
	    //@todo: Deve ser dividido pelo número de ítens.
	    if(menu->Type == 1)
		{
	        width  = (unsigned long) (menu->menuWindow->width / 4);
			//height = (unsigned long) menu->menuWindow->height;
            goto draw_window;			
	    };
		
		//...
		
	};
	   

	//
	// Draw.
	//
	
draw_window:
	
    if(Selected == 1){	
        Color = COLOR_BLUE;
    }else{
	    Color = COLOR_BLACK; //COLOR_WINDOW;
	};	
    
    //Window.	
	hWindow = (void*) CreateWindow( 1, 0, 0, "MenuItem", 
	                                x, y, width, height, 
							        menu->parentWindow, 0, 0, Color);
	if( (void*) hWindow == NULL )
	{
		printf("create_menu_item error: Struct.\n");
		refresh_screen();
	    //while(1){};
		return (int) 1;	    	    
	}
	else{
	    RegisterWindow(hWindow);
		SetFocus(hWindow);  
	};

	// String.
strings:
  
	if(Selected == 1){	
        Color = COLOR_WHITE;
    }else{
	    Color = COLOR_GRAY; 
	};	

    draw_string( menu->newitemLeft +8, menu->newitemTop +8, Color, string); 	
    
    // Ajust next.
ajust_next:
	
	if(menu->Type == 0){
	    menu->newitemLeft = (unsigned long) x;
	    menu->newitemTop  = (unsigned long) y + height;
    };
	
	if(menu->Type == 1){
	    menu->menuWindow->left = (unsigned long) x + width;
	    menu->menuWindow->top  = (unsigned long) y;
    };
	
    // Continua...	
	
done:     
    return (int) 0;
};


/*
 * set_current_menu:
 *
 */
void set_current_menu(struct menu_d *menu)
{
    //Check.
	if( (void*) menu == NULL ){
	    return;
    };  
    
	current_menu = (int) menu->Id;

done:
    return;
};



/*
 * get_current_menu:
 *
 */
void *get_current_menu()
{
    if(current_menu < 0){
	    return NULL;
	};
	
    return (void *) menuList[current_menu];
};



/*
 * RegisterMenu:
 *     Registrando um menu numa lista de menus.
 *
 */
int RegisterMenu(struct menu_d *menu)
{
    struct menu_d *Empty;     //empty  

    if( (void*) menu == NULL ){
        return (int) 1;    //Erro.
    };
 	
//Loop.	
get_next:

	menus_count++;
	
	if(menus_count >= MENU_COUNT_MAX){
	    printf("RegisterMenu error: Limits.");
		refresh_screen();
		while(1){}
	};
    
	//Get empty.
 	Empty = (void*) menuList[menus_count]; 
    
	if( (void*) Empty != NULL ){
        goto get_next;
    }else{
		
	    //Onde está vazio, registra o argumento.
		//coloca o endereço da estrutura na lista de endereços de estrutura.
		
	    menuList[menus_count] = (unsigned long) menu; 	
	};  	
	
done:
    return (int) 0;
};


/*
 * initmenuArray:
 *     Cria um array de itens para um menu.
 *
 */
void initmenuArray( struct menu_d *a, int initialSize )
{
	int i;
		
	//Struct.
    if( (void *) a == NULL ){
	    return;
	};
	
	//Size limits.
	if(initialSize <= 0){
		initialSize = 1; 
	};

	//@todo Limits.
	if(initialSize > 8){
		initialSize = 8; 
	};
	
	//
	// Aloca espaço para o array de estruturas.
	// Contém o espaço de várias estruturas para ítem.
	//
	
    a->Items = (void*) malloc( sizeof(struct menuitem_d) * initialSize);	
	if( (void*) a->Items == NULL )
	{
	   return;
	}
	

	// Inicializa todos os ítens do menu. Lembrando que o ítem '0' é o ítem 
	// que aciona o control menu para a janela.
	
    for( i=0; i < initialSize; i++ )
    {
        a->Items[i].Used = 1;
		a->Items[i].Magic = 1234;
		a->Items[i].Selected = 0;
		
		//a->next = NULL;             //Next menu (cascade)
		//a->next_menuitem = NULL;    //Next menu item.
		//...
    };
	
	//
	// Control Menu:
	// ============
	//
	// O ítem '0' sempre seleciona o control menu para a
	// janela atual, mas ele nunca aparece.
	// ele é representado pelo ícone na parte superior dad janela.
    //	
	a->Items[0].Used = 1;
	a->Items[0].Magic = 1234;
	a->Items[0].Selected = 0;
	
	
	
	
	//Continua ...
	
done:
	return;
};


/*
// Add element to array
void insertArray( Array *a, Student element) 
{
    if( a->used == a->size )
    {
        a->size *= 2;
        a->array = (Student *)realloc(a->array, a->size * sizeof(Student));
    }

    // Copy name
    a->array[a->used].name = (char*)malloc(strlen(element.name) + 1);
    strcpy(a->array[a->used].name, element.name);

    // Copy ID
    a->array[a->used].ID=element.ID;

    a->used++;
}
*/


/*
void freeArray(Array *a) 
{
    // Free all name variables of each array element first
    for(int i=0; i<a->used; i++)
    {
        free(a->array[0].name);
        a->array[0].name=NULL;
    }

    // Now free the array 
    free(a->array);
    a->array = NULL;

    a->used = 0;
    a->size = 0;
}
*/


/*
 * ControlMenu:
 *     É o menu que gerencia a janela ativa com o foco de
 *     entrada.
 *     Aparece no canto superior esquerdo de uma janela ou 
 *     quando se clica com o botão direito do mouse.
 *      menuControlMenu();
 */
int ControlMenu()
{
	//@todo: Rever isso aqui.
    return (int) MainMenu();	
};


/*
 * MainMenu:
 *     Cria o menu principal.
 *     Nada mais na tela, apenas um menu centralizado.
 *     É o control menu.
 */
int MainMenu()
{
	int Focus;    //id da janela com foco de entrada.
	struct window_d *cmWindow;
	struct window_d *pWindow;
	
	// Pega o id da janela com foco de entrada.
	Focus = (int) GetFocus();
	pWindow = (void *) windowList[Focus];
	
	
	// Se a estrutura não for uma estrutura válida, utilizaremos a janela 
	// 'gui->screen' por enquanto. Somente para fins de teste. 	
    if( (void*) pWindow == NULL )
	{
		pWindow = (void *) gui->screen;
        //return (int) 1;
    };	
	
	
	//Usando a janela screen anteriormente criada.
    //if( (void*) gui->screen == NULL ){
    //    return (int) 1;
    //};	
		
    //limpa a tela		
	//kbackground(COLOR_BLACK);	
	
	
	//if ( (void*) gui->ClientArea == NULL )
	//{
	//	gui->ClientArea = (void*) gui->screen;
		
	//	//No Screen.
	//	if( (void*) gui->ClientArea == NULL ){
	//		return (int) 1; //erro.
	//	};		
	//};

	
		
	//
    // Cria a janela e o menu. 
	// isso cria estrutura de menu com 4 ítens e nenhum espaçador.
	// (o argumento é a janela mae)
	//  a janela mae tem o foco de entrada.
    // o retorno é a janela do menu.	
	//
	
	//
	// @todo: A janela do control menu deve aparecer no canto
	//        superior esquerdo da janela ativa com e com o foco
    //        de entrada, ou próxima ao ponteiro do mouse quando	
	//        clicado o botão direito.
	
    cmWindow = (void *) create_menu( pWindow, 4, 0, 0, 0 );
	if( (void *) cmWindow == NULL )
	{
	    printf("MainMenu error: struct.\n");
		refresh_screen();
		while(1){}	
	};
	
	
	initmenuArray( cmWindow->defaultMenu, 4);
	
	//
	// Cria um menuitem, dado um menu da janela.
	//
	
	create_menu_item( cmWindow->defaultMenu, "Maximizar" , 0 );
    create_menu_item( cmWindow->defaultMenu, "Minimizar" , 0 );
	create_menu_item( cmWindow->defaultMenu, "Fechar   " , 1 );
	//create_menu_item( cmWindow->defaultMenu, "cmitem3" , 0 );
	
	
	//draw_text( gui->screen, 2*(640/3), 2*(480/3) , COLOR_WINDOWTEXT, "MAIN MENU"); 
	//StatusBar(gui->screen, "Status Bar", "MAIN MENU");
	
	SetProcedure( (unsigned long) &MainMenuProcedure );	

done: 
    SetFocus(cmWindow);
	return (int) 0;
};


/*
 **********************************************
 * MainMenuProcedure:
 *     Procedimento de janela do 'main menu'.
 *     #test
 */																
unsigned long 
MainMenuProcedure( struct window_d *window, 
                   int msg, 
  				   unsigned long long1, 
				   unsigned long long2 ) 
{
    switch(msg)
	{	
        case MSG_KEYDOWN:
            switch(long1)
            {
                case VK_ESCAPE:
                   //KillFocus(window);				
				    SetProcedure( (unsigned long) &system_procedure);
                   	return (unsigned long) 0; 			   
				    break;
				   
                default:
                    break; 
            };
        break;
		
		case MSG_SYSKEYDOWN:                 
            switch(long1)	       
            {   
				//Screen
				case VK_F1:
				    StatusBar( gui->screen, "Status Bar screen", "F1");
                    break;
					
				//Background
                case VK_F2:
				    StatusBar( gui->background, "Status Bar bg", "F2");
                    break;
					
				//Logo
                case VK_F3:
				    StatusBar( gui->logo, "Status Bar logo", "F3");
                    break;

				//TaskBar
                case VK_F4:
				    StatusBar( gui->taskbar, "Status Bar taskbar", "F4");
                    break;
					
				//Main Window
                case VK_F5:
				    StatusBar( gui->main, "Status Bar main", "F5");
                    break;	    

				//Navigation Bar
                case VK_F6:
				    StatusBar( gui->navigationbar, "Status Bar navigationbar", "F6");
                    break;
					
				default:
                    return (unsigned long) 0;	
				    break;
		    };              
        break;
		
	    case MSG_SYSKEYUP:
           //Nothing.		
        break;
		
		default:
		    //Nothing.
		    break;
	};
	
// Done.
done:
    refresh_screen();
	return (unsigned long) 0;
};


/*
 **************************************
 * init_menus:
 *     Inicializa a lista de menus.
 */
int init_menus()
{
	int i=0;
	
	printf("init_menus:\n");  	

	while( i < MENU_COUNT_MAX )
	{
	    menuList[i] = (unsigned long) 0;
        ++i;
	};
	
	// Set current.
	set_current_menu(NULL);
	
	menus_count = 0;

	// Continua ...

done:	
    //printf("Done.\n");
	return (int) 0;
};


/*
int menuInit()
{}
*/


//
//fim.
//

