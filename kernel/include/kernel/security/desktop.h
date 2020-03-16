/*
 * Arquivo: desktop.h 
 *
 * Descrição:
 *     Header para o módulo gerenciador de desktops.
 *     Um desktop pertence à uma window station.
 *     Um desktop contém janelas, menus e outras coisas.
 *     ...
 *
 * #importante:
 * Cada desktop deve ter seu backbuffer.
 * Um ponteiro para o backbuffer deve ser criado na estrutura de desctop.
 *
 *     WINDOW -> DESKTOP -> WINDOW STATION -> USER SECTION.
 * Versão 1.0, 2015.
 */
 
 

/*
 * desktop_d:
 *     Desktop structure.
 */

struct desktop_d
{
    object_type_t objectType;
    object_class_t objectClass;

    //object control
    struct object_d *object;



    int desktopId;

    int desktopUsed;
    int desktopMagic;

    // usando o mesmo esquema do usuário.
    char __name[64];
    int name_lenght;

    // The window server and the window manager for this desktop.
    int ws;
    int wm;
    
  
    // #todo
    // A estrutura de eventos também desve estar associado
    // a um desktop;
    // Cada wm poderá pegar eventos em um desktop específico.
    // Dessa forma poderemos ter vários wm, um para cada desktop.
    // no desktop 0 ficam o ws e o wm que pertencem ao base kernel.
    // kgws e kgwm, :)
    


	// #importante
	// #quantidades
	// Isso limita as quantidades que podem ser criadas em um desktop.
	// permitindo o fácil gerenciamento de drivers em desktops específicos.
	// Pois alguns desktops podem ter seus próprios gerenciadores de servidores.
	// Como o caso do gramado core. Que fica a cargo apenas do kernel 
	// gerenciar esses servidores especiais.
	
	
	int drivers_max;
	int servers_max;
	int apps_max;
	
	
	

	// #importante
	//unsigned long backbuffer_address;
	
	
	int userID;
	
	
	//prompt de comandos. ??
	//int terminal_TID; 
	
	
	//Heap do desktop.
	struct heap_d *heap;
	
    //
	// Control Menu.
	//
		
    struct window_d *menuWindow;   //Ponteiro para a janela do menu.
	struct menu_d *sysMenu;        //control menu do sistema.(no icone da janela.)
    struct menu_d *dialogsysMenu;  //control menu para dialogo. (todos outros control menus)
    struct menu_d *menuHScroll;    //menu genérico horizontal. (usado no momento) ??
    struct menu_d *menuVScroll;    //menu genérico vertical.   (usado no momento) ??

    
	//
	// Janelas.
	//
	
	//Parametros da janela ativa.
	int active_window;             //Id da janela ativa.  
	struct window_d *activeWindow;    //Ponteiro da estrutura da janela ativa.
	
	//Parâmetros da janela com o foco de entrada.
	int window_with_focus;            //Id da janela com foco de entrada.
	struct window_d *focusWindow;     //Ponteiro da estrutura da janela com foco de entrada.
	unsigned long procedure;          //Procedimento da janela ativa.	
	
	
	struct window_d *foregroundWindow;    //A janela que em cima das outras.
	struct window_d *messageWindow;       //Janelinha amarela de mensagem. 
	                                      //(tem botão fechar)
										  //(NÃO é uma message box). 
	
	//Janela para uma tray do sistema (bandeija atual). 
	//( bandeija de uma janela) 
	//(uma janela pode ter mais de uma badeija).
    struct window_d *trayWindow;         
	
	//Janelinha de informação sobre itens 
	//que o mouse repousa em cima. (quadrado).	
    struct window_d *tooltipWindow;      
	
	
	//OBS:
	//O TAB troca a bandeija.
	//As SETAS trocam o item dentro da bandeija.
	//As bandeijas podem estar ligadas por *next.
	
	
	
	//struct window_d *arrayWindow;    //Ponteiro para um array de estruturas de janelas.
	//struct window_d *desktop;
	//struct window_d *shell; 
	//struct window_d *taskmanager;
	//struct window_d *programmanager;
	
	
    unsigned long windows[256];    //@todo: Usar alocação dinâmica, igual nos menus.
    unsigned long menus[256];      //@todo: Usar alocação dinâmica, igual nos menus.
	//Continua ...
	
	//Linked List. 
	//( a linked list de janelas no desktop ).
	//struct linkedlist_d *linkedlist;
	

	//Window Station. 
	//( à qual window station pertence esse desktop ? ).
	//struct wstation_d *wstation;
	
	struct room_d *room;
	
	//Lista de processos nessse desktop.
	//unsigned long processList[32];
	//struct process_d processes[32];
	
	//
	// @todo: user ??, Something more ??
	//
	
    struct desktop_d *next;
};

// This is the desktop used by the base kernel.
// So, the kgws and the kgwm can be here. 

struct desktop_d *desktop0;

// O desktop atual.
struct desktop_d *CurrentDesktop;




//List.
unsigned long desktopList[DESKTOP_COUNT_MAX];


/*
 * desktop_info_d:
 *
 */
typedef struct desktop_info_d desktop_info_t;
struct desktop_info_d 
{
    struct window_d *wnd; 
    int processId;        
    int threadId;        
};
//desktop_info_t *DesktopInfo;



/*
 * Contagem de desktops.
 */
//movido para gws.h 
//int desktops_count;  



void init_desktop (void);

void init_desktop_list (void);

int RegisterDesktop(struct desktop_d *d); 
void set_current_desktop(struct desktop_d *desktop);

void *get_current_desktop (void);

int get_current_desktop_id (void);


void *CreateDesktop (struct room_d *room);


void 
set_current_menuwindow ( struct desktop_d *desktop, 
                         struct window_d *window ); 

void 
set_current_foreground ( struct desktop_d *desktop, 
                         struct window_d *window ); 

void 
set_current_messagewindow ( struct desktop_d *desktop, 
                            struct window_d *window ); 

void 
set_current_traywindow ( struct desktop_d *desktop, 
                         struct window_d *window ); 

void 
set_current_tooltipwindow ( struct desktop_d *desktop, 
                            struct window_d *window ); 

void 
change_foreground (struct desktop_d *desktop);

void 
set_current_sysMenu ( struct desktop_d *desktop, 
                      struct menu_d *menu );

void 
set_current_dialogsysMenu ( struct desktop_d *desktop, 
                            struct menu_d *menu );
                            
void 
set_current_menuHScroll ( struct desktop_d *desktop, 
                          struct menu_d *menu );
                          
void 
set_current_menuVScroll ( struct desktop_d *desktop, 
                          struct menu_d *menu );


int desktop_setup_ws ( struct desktop_d *desktop, int ws_pid );
int desktop_setup_wm ( struct desktop_d *desktop, int wm_pid );


//
// End.
//


