/*
 * Arquivo: menu.h
 *
 * Descrição:
 *     Header para gerenciamento de menus.
 *
 *
 * Menus:
 * ======
 *     São três os componentes principais: 
 *     (MenuItem < Menu < MenuBar).
 *
 *
 * Control Menu:
 * =============
 *     O control menu aparece apenas na janela ativa.
 *     @todo: Sua estrutura de indica em quan janela ele está aparecento. 
 *            Sua estrutura deve indical qual é o seu procedimento.
 *            O control menu deve enviar mensagem para a janela com o resultado
 *            da interação do usuário com o menu ?!
 *
 * Versão 1.0, 2015, 2016.
 */
 
 
 
#define MENU_COUNT_MAX      256 
#define MENUITEM_COUNT_MAX  16



/*
 * MENUITEM:
 *     Estrutura para menuitem.
 *
 */
typedef struct menuitem_d menuitem_t;
struct menuitem_d
{
	object_type_t objectType;
	object_class_t objectClass;
	
    int Id;          //Id do menu.	
	
	int Used;        //Se está sendo usado.
	int Magic;       //Se o slot não está corrompido.
	
	int Selected;    //Flag. Selecionado ou não.
	
    unsigned long color_bg;    //cor.
    unsigned long x;           //deslocamento x.
    unsigned long y;           //deslocamento y.
    unsigned long left;        //margem esquerda. 
    unsigned long top;         //margem superior.
    unsigned long right;       //margem direita.  
    unsigned long bottom;      //margem inferior.       
    unsigned long width;       //largura.
    unsigned long height;      //altura.
	
	//
	// @todo: Strings.
	//
	unsigned char *string;
	
    int windowId;               //Id da janela que o menu pertence. 	
	struct window_d *window;    //Janela que possui o menu (bg).
    

	//Quando um item abre um submenu.
	//esse é um ponteiro para a estrutura do dubmenu 
	//que o item abre.
	struct menu_d *next;
	
	//todo: pode ter uma estrutura pra retangulo ... tipo, cor ...
	struct menuitem_d *next_menuitem;
	//...

};
menuitem_t *menuitemDefault;
//menuitem_t *menuitem;
//menuitem_t *MenuItem;
//menuitem_t *CurrentMenuItem;
//...



/*
 * MENU:
 *     Estrutura para menu.
 *
 * (todo menu tem uma janela que recebe as mensagens,
 *   e a janela tem seu procedimento de janela).
 */
typedef struct menu_d menu_t;
struct menu_d
{
	object_type_t objectType;
	object_class_t objectClass;
	
    int Id;              //Id do menu.
	int selectedItem;    //Id do item selecionado.

	int itemCount;       //Número total de itens. 
	int itemMax;         //Número maximo de itens. (menuitemList[]).
	
	unsigned long newitemLeft;
	unsigned long newitemTop;
	
	int Type;      //Vertical ou horizontal.
    int Style;	   //Enfeites, formatos ... aparência.
	
	//lista de ítens.
	//array de ponteiros para estruturas de menuitem.
	struct menuitem_d *Items; 

	//linked list. ( a linked list do menu).
	struct linkedlist_d *linkedlist;	

	
	//o menu é uma janela.
    int menuId;                    //id da janela que o menu é.
	struct window_d *menuWindow;   //o menu sendo uma janela.
	
	//
	// *IMPORTANTE: O menu está em uma janela. No caso do control menu
	//              ele aparecerá na janela ativa.
	//
	
	//janela mae do menu,(que é uma janela)
    int windowId;                  //id da janela que o menu pertence. 	
	struct window_d *parentWindow; //Janela que possui o menu.
    
	
	
	//background do menu.(suspenso)
	//int backgroundId;
	//struct window_d *background;
	
	//unsigned long menuitemList[16]; //lista de itens do menu.
	
	//...
   
};
//menu_t *ControlMenu;   //O menu da janela com foco de entrada.
menu_t *logonMenu;
menu_t *guiMenu;
menu_t *menubarDefault;
menu_t *menuDefault;
//menu_t *menu;
//menu_t *Menu;
//menu_t *CurrentMenu;
//...



/*
 * Lista de Menus.
 *
 */ 
unsigned long menuList[MENU_COUNT_MAX];




/*
 * Contagem de menus.
 *
 */
int menus_count;

  

/*
 * CURRENT MENU:
 *     Estrutura para o menu atual, (ativo).
 *
 */
typedef struct current_menu_d current_menu_t;
struct current_menu_d
{
    unsigned long menuId;    //Id do menu ativo, (índice na lista de menus).
    struct menu_d *menu;
	//window...
	//desktop...
	//...
};
//current_menu_t *CurrentMenu;

//
// MenuBar struct.
//
/*
typedef struct menu_bar_d menu_bar_t;
struct menu_bar_d
{
    struct window_d *window;	
};
menu_bar_t *MenuBar;
menu_bar_t *CurrentMenuBar;
*/



/*
typedef struct menu_info_d menu_info_t;
struct menu_info_d
{
	struct window_d *Window;
    struct menu_bar_d *MenuBar;
    struct menu_d     *Menu;
	struct menuitem_d *MenuItem;
};
menu_info_t *MenuInfo;
menu_info_t *CurrentMenuInfo;
*/


//
// Menubar globals.
//

//unsigned long g_menubarWindow;
//unsigned long g_menubarMenu;



//Protótipos.

int init_menus();
void set_current_menu(struct menu_d *menu);
void *get_current_menu();
int RegisterMenu(struct menu_d *menu);
void initmenuArray(struct menu_d *a, int initialSize);


/*
 * MainMenu:
 *     Cria o menu principal.
 *     Nada mais na tela, apenas um menu centralizado.
 */
int MainMenu();    //o main menu é o control menu.
int ControlMenu(); //control menu


/*
 * MainMenuProcedure:
 *    Main menu. inicialização de ambientes.
 *    //test
 */																
unsigned long MainMenuProcedure( struct window_d *window, 
                                int msg, 
								unsigned long long1, 
								unsigned long long2);

/*
 * create_menu_item:
 *     Menus são verticais.
 *  
 */
int create_menu_item(struct menu_d *menu, unsigned char *string, int status);


int select_menubar_item(int n);
int unselect_menubar_item(int n);

int get_menubar_selected_item();
int redraw_menubar_item( int n);


void *create_menu( struct window_d *pwindow,    //Parent window. 
                   unsigned long iCount,        //Contagem de ítems. 
				   unsigned long sCount,        //Contagem de espaçadores.
				   int type,                    //Horizontal ou vertical.
				   int style );                 //Estilo.

				   
				   			   
unsigned long MenuBarProcedure( struct window_d *window, 
                                int msg, 
								unsigned long long1, 
								unsigned long long2); 
//
//fim.
//

