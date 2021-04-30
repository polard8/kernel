/*
 * File: window.h
 * 
 * History:
 *     2020 - Created by Fred Nora.
 */

#ifndef ____WINDOW_H
#define ____WINDOW_H    1


#define IS_OPAQUE       1000
#define IS_TRANSPARENT  2000
#define IS_ICON         3000


//apresentação.
#define VIEW_NULL      0
#define VIEW_FULL      1000
#define VIEW_MAXIMIZED 1001
#define VIEW_MINIMIZED 1002
#define VIEW_NORMAL    1003 //Normal (restaurada)
//...


// button
// #todo: Check these numbers.

#define BN_CLICKED  200
#define BN_DOWN     1
#define BN_UP       2
#define BN_SELECTED 3
// ...



//
// ## botoes  ##
//

//button state
#define BS_NULL      0 
#define BS_DEFAULT   1
#define BS_FOCUS     2
#define BS_PRESS     3
#define BS_HOVER     4
#define BS_DISABLED  5
#define BS_PROGRESS  6
// ...


#define WINDOW_LOCKED    1
#define WINDOW_UNLOCKED  0



// window status
#define WINDOW_STATUS_ACTIVE       1
#define WINDOW_STATUS_INACTIVE     0


//window relationship status. (seu status em relação as outras janelas.)
//Obs: tem uma estreita ligação com o status da thread que está trabalahndo com ela 
//e com a prioridade dessa thread e do processo que a possui.
// *** RELAÇÃO IMPLICA PRIORIDADE ***
#define WINDOW_REALATIONSHIPSTATUS_FOREGROUND     1000
#define WINDOW_REALATIONSHIPSTATUS_BACKGROUND     2000
#define WINDOW_REALATIONSHIPSTATUS_OWNED          3000  //Possuida por outra janela.
#define WINDOW_REALATIONSHIPSTATUS_ZAXIS_TOP      4000
#define WINDOW_REALATIONSHIPSTATUS_ZAXIS_BOTTOM   6000
//...


//
// == prototypes =======================================
//



// Contagem de janelas existentes.
// precisa ser inicializada.
unsigned long windows_count;

int active_window;

int window_with_focus;

int top_window;

// ...


int show_fps_window;


/*
 *************************************
 * gws_button_d:
 *     Structure for button object.
 *     Env: gws in ring3.
 */

struct gws_button_d
{
    //object_type_t   objectType;
    //object_class_t  objectClass;

    int used;
    int magic;

    // ??
    // Ordem dos botões que pertencam à mesma janela.
    // A qual janela o botão pertence.
    // Esse índice pode trabalhar junto com 
    // a lista encadeada de 'next'.

    //int index;	
    struct gws_window_d *window; 
    
	// label
	// #todo: mudar o tipo para (char *)
    unsigned char *string; 
	
	// Estilo de design.
	// 3D, flat ...
    int style;
	
	
    //button states:
    //1. Default
    //2. Focus
    //3. Expanded/Toggled/Selected
    //4. Disabled
    //5. Hover and Active	
    int state;


	//Check Boxes
	//Group Boxes
	//Push Buttons
	//Radio Buttons

    int type;

    int selected;
	
	// Border color
    // Isso é para o caso do estilo 3D.
	// Ou para causar alguns efito em outros estilos.

    unsigned long border1;
    unsigned long border2;


    // Deslocamento em relação ao left da janela
    // Deslocamento em relação ao top da janela

    unsigned long x;    
    unsigned long y;   
    unsigned long width; 
    unsigned long height;

    // Background color.
    unsigned long color;

	//More ??
	//...

    // Next button.    
    struct gws_button_d *Next;  
};





/*
 **************************************************
 * rect_d:
 *     Estrutura para gerenciamento de retângulos.
 *     Um retângulo pertence à uma janela.
 */

struct gws_rect_d 
{
	//object_type_t objectType;
	//object_class_t objectClass;

    int used;
    int magic;

    int flag;

    //estilo de design
    int style;

    // Filled or not.
    int is_empty;

    int dirty;

    // ??
    unsigned long left;
    unsigned long top;
    unsigned long right;
    unsigned long bottom;

    unsigned long width;
    unsigned long height;

    unsigned long bg_color;


    //Essa é  ajanela à qual o retângulo pertence.
    struct gws_window_d *window;   //mudar. #todo


    struct gws_rect_d *next;
};


	//
	// Window Class support.
	//
	
 
//enumerando classe de janela 
typedef enum {
    gws_WindowClassNull,
	gws_WindowClassClient,  //1 cliente
	gws_WindowClassKernel,  //2 kernel
	gws_WindowClassServer,  //3 servidor
}gws_wc_t;


//classes de janelas controladas pelos aplicativos.
typedef enum {
    gws_WindowClassApplicationWindow,	
	//...
}gws_client_window_classes_t;

//??bugbug: tá errado.
//classes de janelas controladas exclusivamente pelo kernel.
typedef enum {
    gws_WindowClassKernelWindow,    //janelas criadas pelo kernel ... coma a "tela azul da morte"
    gws_WindowClassTerminal,  //janela de terminal usada pelos aplicativos que não criam janela e gerenciada pelo kernel	
    gws_WindowClassButton,
    gws_WindowClassComboBox,
    gws_WindowClassEditBox,
    gws_WindowClassListBox,
	gws_WindowClassScrollBar,
	gws_WindowClassMessageOnly, //essa janela não é visível, serve apenas para troca de mensagens ...
	gws_WindowClassMenu,
	gws_WindowClassDesktopWindow,
	gws_WindowClassDialogBox,
	gws_WindowClassMessageBox,
	gws_WindowClassTaskSwitchWindow,
	gws_WindowClassIcons,
	gws_WindowClassControl,   //??
    gws_WindowClassDialog,
    gws_WindowClassInfo,
    //...	
}gws_kernel_window_classes_t;

//classes de janelas controladas pelos servidores.
typedef enum {
    gws_WindowClassServerWindow,
    //...	
}gws_server_window_classes_t;



//estrutura para window class
struct gws_window_class_d
{
	
	//Que tipo de window class.
	// do sistema, dos processos ...
    //tipo de classe.
	
    gws_wc_t windowClass; 

	//1
    gws_client_window_classes_t	clientClass;
	
	//2
    gws_kernel_window_classes_t	kernelClass;
	
	//3
    gws_server_window_classes_t	serverClass;
	
	//Endereço do procedimento de janela.
	//(eip da thread primcipal do app)
    unsigned long procedure;
    
    // ...
};


// Input pointer device type.
typedef enum {

    IP_DEVICE_NULL,
    IP_DEVICE_KEYBOARD,
    IP_DEVICE_MOUSE
    // ... 
} gws_ip_device_t;



/*
 ********************************
 * gws_window_d:
 * 
 *     The window structure.
 */

struct gws_window_d 
{

    int id;
    int used;
    int magic;


    char *name;          //Window name.

    unsigned long type;  //tipo ... (editbox, normal, ...)  style???


    // Hierarquia. 
    // parent->level + 1;
    // Não é z-order.

    int level;

    // The window belongs to this client.
    // Talvez a tid da control thread do cliente 
    // pode ficar nessa estrutura.
    struct gws_client_d  *client;

    // #todo
    // Para sabermos quem receberá o reply no caso
    // de eventos.
    // Quando um cliente solicitar por eventos em uma dada janela
    // com foco, então essa janela deve registrar qual é o fd do
    // cliente que receberá o reply com informações sobre o evento.

    int client_fd;

    // #test
    // tid da control thread do cliente.
    int client_pid;
    int client_tid;

	// Características dessa janela..


	// Estado: (Full,Maximized,Minimized...)
    int view; 
    
    int status;
    
    int dirty;

    // Margins. (position)
    // Deslocamento em relação à tela. (screen)
    unsigned long left;        //margem esquerda 
    unsigned long top;         //margem superior
    unsigned long right;       //margem direita  
    unsigned long bottom;      //margem inferior  

    // Dimension.
    unsigned long width;       //largura
    unsigned long height;      //altura   


    // Offset inside the window.
    // Can be used by the rectangles.
    // Deslocamento em relação a janela mãe.
    unsigned long x;
    unsigned long y; 


    // Windows's bg.
    unsigned long bg_color; 
    
    
    // #todo    
    //unsigned long border_color;
    //unsigned long border_width;


    // Cliente area in chars.
    //unsigned long client_area_width;
    //unsigned long client_area_height;

    //
    // == input pointer =========================================
    //
    
    // Valido apenas para essa janela.
    
    // Esta ligado?
    int ip_on;
    
    // Qual eh o dispositivo de input.
    gws_ip_device_t ip_device;

    // para input do typo teclado
    unsigned long ip_x;
    unsigned long ip_y;
    unsigned long ip_color;
    unsigned long ip_type;
    // ...

    // para input do typo teclado
    unsigned long ip_pixel_x;
    unsigned long ip_pixel_y;

// 
//==================================================


    // In the window stack we have two major components:
    // + The frame (top frame and bottom frame).
    // + The Client area.
    

    // Top frame has: title bar, tool bar, menu bar ...
    
    unsigned long top_frame_Height;
    unsigned long client_area_Height;
    unsigned long bottom_frame_Height;


    //
    // == window stack ================================
    //

    // This is a stack of elements to build 
    // an application window.
    // Some kinds of window do not use all these elements.

    // 1
    // Shadow

    int shadow_style;
    int shadowUsed;


    // 2
    // Background

    int background_style;
    int backgroundUsed;


    // 3
    // Titlebar

    struct gws_window_d  *titlebar;
    struct gws_window_d  *tb_minimize;
    struct gws_window_d  *tb_maximize;
    struct gws_window_d  *tb_close;
    int isMinimize;
    int isMaximize;
    int isClose;
    unsigned long titlebar_height;
    int titlebarHasIcon;     // If the title bar uses or not an icon.
    int titlebar_style;
    int titlebarUsed;

    // 4
    // Controls

    int minimizebuttonUsed;
    int maximizebuttonUsed;
    int closebuttonUsed;
    int controls_style;
    int controlsUsed;

    // 5
    // Borders

    unsigned long border_size;
    unsigned long border_color;
    int border_style;
    int borderUsed;

    // 6
    // Menubar

    struct gws_window_d *menubar;
    unsigned long menubar_height;
    int menubar_style;
    int menubarUsed; 

    // 7
    // Toolbar

    struct gws_window_d *toolbar;
    unsigned long toolbar_height;
    int toolbar_style;
    int toolbarUsed;
 
    // 8
    // Client window

    struct gws_window_d *client_window; 
    struct gws_rect_d *rcClient;     
    unsigned long clientrect_bg_color; //cor do retângulo da área do cliente.
    unsigned long clientwindow_height;
    int clientarea_style;
    int clientAreaUsed;


    // 9
    // Scrollbar

    // vertical scrollbar
    // The wm will call the window server to create this 
    // kind of control.
    struct gws_window_d *scrollbar;
    struct gws_window_d *scrollbar_button1;
    struct gws_window_d *scrollbar_button2;
    struct gws_window_d *scrollbar_button3;
    int isScrollBarButton1;
    int isScrollBarButton2;
    int isScrollBarButton3;
    unsigned long scrollbar_height;
    // int scrollbarOrientation;  //horizontal or vertical
    int scrollbar_style;
    int scrollbarUsed;

    // 10
    // Statusbar

    struct window_d *statusbar;
    unsigned long statusbar_height;
    int statusbar_style;
    int statusbarUsed;

    // ...

// ======================================================

    // Flag par indicar se a janela é um item de menu ou um botão.
    int isMenu;   
    int isMenuItem;
    int isControl;  // Window control ...
    int isButton;  //#importante: Indica que a janela é um botão.
    int isEditBox; //#importante: Indica que a janela é um editbox.
    int isCheckBox;
    int isIcon;
    // ...
    
// ======================================================

    // ??
    // Um alerta de que exite uma mensagem para essa janela.
    int msgAlert;  


    // ??
    // #todo: 
    // Deletar isso. Isso deve fazer parte da estrutura window class.
    unsigned long procedure; 


    int active;    //FAST FLAG. Essa será a flag de ativa ou não. (decidindo isso)
    int focus;     //Se tem o foco de entrada ou não.

// 
//==================================================


    // Parent support
    unsigned long parentid;       //(Número da janela mãe).
    struct gws_window_d *parent;	  //Parent window.	


    // Child support.
    // obs: gosto mais de arrays.
    struct gws_window_d *childListHead;  //Lista encadeada de janelas filhas.
    int childCount;                  //Tamanho da lista.

// 
//==================================================	

   // #test
   // This is a test. Not implemented yet.

	// Buffer.
	// DedicatedBuffer
	// DedicatedBuffer --> LFB.
	// Endereço de memória onde a janela foi pintada.
	// Obs: Toda janela deve ter seu próprio buffer de pintura para poder 
	// passar a janela direto de seu próprio buffer para o LFB, sem passar 
	// pelo Backbuffer.

    void *DedicatedBuffer;  //Qual buffer dedicado a janela usa.
    void *BackBuffer;       //Qual backbuffer a janela usa.
    void *FrontBuffer;      //Qual frontbuffer a janela usa. (LFB).	


// 
//==================================================

	// Desktop support.
	// A que desktop a janela pertence??

    int desktop_id;
	//struct desktop_d *desktop;   //suspenso.

// 


	// If locked we can't change a simple thing. 
	// It must affect the input events for the specified window.
    int locked; 


// 
//==================================================

    // parent window. 
    // ?? again ??
    struct gws_window_d *owner;
    
    // child window;
    // ?? again ??
    struct gws_window_d *child; 


// 
//==================================================
 



	// Buffer para mensagens pequenas.
    // Será usado pelo produtor e pelo consumidor.
    // char read_buf[WINDOW_MSG_BUFFER_SIZE];



	//
	// Window Class support.
	//


    struct gws_window_class_d *window_class;

    // ?? wtf
    // unsigned long scancodeList[32];	



	//
	// TERMINAL SUPPORT
	//


    // Obs: 
    // Essas variáveis só serão inicializadas se o 
    // aplicativo decidir que conterá um terminal em sua janela.
    // Um aplicativo só poderá ter um terminal dentro de cada janela.
    // Ou seja, se um aplicativo quiser ter mais de um terminal virtual, 
    // vai precisar de uma janela para cada terminal dentro do aplicativo.
    // isso permite facilmente que um mesmo aplicativo rode vários
    // programas, um em cada aba.
    // Ao invés de criar um frame para cada aplicativo que rode em terminal,
    // é só criar uma nova aba no gerenciador de terminais virtuais ...
    // esse gerenciador de terminais virtuais poderia ser o shell.bin	


	//flags

	//configura o status do terminal dentro da janela
    int terminal_used;     //Se é um terminal ou não.


	//validade e reusabilidade das variáveis de terminal 
	//dentro da estrutura de janela.	
    int terminal_magic;

	//tab
	//número da tab.
	//indica qual tab o terminal está usando.
	//@todo:
	// Criar uma forma de contar as tabs de terminal 
	// dentro do gerenciador de terminais.
    int terminal_tab; // em qual tab do gerenciador de terminais está o terminal.

	// Terminal's rectangle.
    unsigned long teminal_left;
    unsigned long teminal_top;
    unsigned long teminal_width;
    unsigned long teminal_height;

    unsigned long teminal_right;
    unsigned long teminal_bottom;

	//...



	//@todo: isso deve pertencer a uma janela.
	//se uma janela tiver o foco de entrada e for um terminal 
	//a disciplica de linhas poderá usar essas carcterística do terminal.
	
	//suspenso.
	//struct terminal_d *wTerminal; //dd\uitm\terminal.h
	//struct console_d *console;   //dd\uitm\console.h	



    // Tabs:
    // Número da aba do navegador que a janela está.
    // Se for 0, então a janela está no desktop.
    
    int tab;


    // style: 
    // Isso poderia ser estilo de design ...
    // Qualquer janela pode ter vários estilos de design 
    // ex: um editbox poderá ser de vários estilos.
    // window style:
    // WINDOW_STYLE_FLOATING (flutuante) 
    // WINDOW_STYLE_DOCKING   (atracada em algum canto)

    int style;   


    // Again ??
    // This is a nice structure.
    // We can use this one!
    //struct msg_d *msg;


    // ?? again ??
    // unsigned long Background;


    //
	// Características dessa janela..
	//

	//*full screen mode = modo tela cheia. 
	//( utiliza a resolução atual do dispositivo )
	// deve ser a janela em primeiro plano. acima de todas as outras.
	//mas podemos configurar para que uma jenela esteja em full screen 
	//enquanto outra janela é a janela ativa e ainda outra tenha o foco de entrada.
	//uma janela em modo full screen pode conter barras de rolagem.
	//*embedded mode = dentro de uma janela ou de um navegador. 


    // ATIVA OU NÃO.
    // unsigned long status;                
    
    
    // Seu status de relacionamento com outras janelas.
    unsigned long relationship_status;   
    
     
    //
    // z-order.
    //
    
    // Ordem na pilha de janelas do eixo z.
    // A janela mais ao topo é a janela foreground.

    int zIndex;    

	//z-order global.
	//Sua ordem em relação a janela gui->main.    

	// suspenso .... isso é muito importante.
    // struct zorder_d *zorder;
    
    
    // ?? again ??
    // Qual buffer dedicado a janela usa.
    // void *buffer;        



    // rects.

	// Lista encadeada dos retângulos que pertencem a essa janela.
	// Quando uma janela for deletada, devemos desalocar toda a memória 
	// usada por esses recursos.
	struct gws_rect_d *rectList;


	//
	// Buffers support.
	//

    //   ??
    //   wtf
    
	// Um ponteiro para um array de ponteiros de estruturas de linhas
	// Explicando: Nesse endereço teremos um array. 
	// Cada ponteiro armazenado nesse array é um ponteiro para uma 
	// estrutura de linha.
	// Obs: @todo: Todos esses elementos podem formar uma estrutura e 
	// ficaria aqui apenas um ponteiro para ela.
	
    void *LineArray;
    int LineArrayIndexTotal;    //Total de índices presentes nesse array.
    int LineArrayIndexMax;      //Número máximo de índices permitidos no array de linhas.
    int LineArrayTopLineIndex;  //Indice para a linha que ficará no topo da página.
    int LineArrayPointerX;      //Em qual linha o ponteiro está. 	
    int LineArrayPointerY;      //em qual coluna o ponteiro está.



    // #importante
    // Estrutura de process e estrutura de thread
    // pertencem a api. Isso justifica a inclusão da api.


    //suspenso
    // #importante: thread de input
    //struct thread_d *InputThread;

    //suspenso
    //  Process support. A que processo a janela pertence??
    //struct process_d *process;	


	//
	// Menus.
	//


    // O menu para gerenciamento dessa janela se ela for overlapped.
    struct gws_window_d *menu_window;
    struct gwsssrv_menu_d  *defaultMenu;     //menu da janela (*importante)
    
    // Outros menus.
    struct gwsssrv_menu_d  *sysMenu;         //menu de sistema.(control menu)
    struct gwsssrv_menu_d  *barMenu;         //menu da barra de menu.

    // ...

    //
    // button
    //

	// suspenso
	// Se a flag indicar que a janela é um botão, então 
	// essa será a estrutura para o botão.

	//struct button_d *button;

    int selected;         //seleção  de item de menu.
    const char *text;     // 


    //
    // Actions
    //

    int draw;     
    int redraw;
    int show;   //se precisa ou não mostrar a janela.	
    // Continua ...



	//
	// Text Cursor support.
	//


	//fica para uma versão estendida da estrutura.
	//Estrutura de cursor para a janela.
    //struct cursor_d	*cursor;
	
	//unsigned long bgcolor;		// Background color.
	//unsigned long fgcolor;		// Foreground color. 
	
	//struct button_d *current_button;  //Botão atual.      
    //struct button_d *buttonList;      //Lista encadeada de botões em uma janela.


	
	//
	// Mouse cursor support ???
	//
	
	//
	// Abaixo ficam os elementos referenciados com menor frequência.
	//
	
    //
	// ?? rever isso 
	// Status do puxador da janela.
	// Se está aberta ou não.
	// HANDLE_STATUS_OPEN ou HANDLE_STATUS_CLOSE
	//

    // ??
    // What ?
    int handle_status;

//==================================================
    // Navigation.
    struct gws_window_d  *prev; 
    struct gws_window_d  *next; 
};

// Windows.

struct gws_window_d  *__root_window; 
// If the window server has a taskbar.
// maybe we don't need that.
struct gws_window_d  *__taskbar_window; 
struct gws_window_d  *__taskbar_button; 

struct gws_window_d  *keyboard_window;  // keyboard focus.
struct gws_window_d  *mouse_window;     // ??

struct gws_window_d  *cursor_window;  // Where cursor came from.
struct gws_window_d  *button_window;  // Where button was pressed.
// ...


// #todo
// We need to define the root window.
// Maybe it will the the screen window.
// Or each screen will have its own root window.



//
// == Window list =============================
//

// This is gonna be used to register the windows.
// These indexes will be returned to the caller.

#define WINDOW_COUNT_MAX 1024

unsigned long windowList[WINDOW_COUNT_MAX];
//unsigned long gwssrvWindowList[1024]

//
// == z order list =============================
//

#define ZORDER_MAX 1024
#define ZORDER_TOP (ZORDER_MAX-1)
#define ZORDER_BOTTOM 0
//...

#define TOP_WINDOW    ZORDER_TOP
#define BOTTOM_WINDOW 0
// ...


unsigned long zList[ZORDER_MAX];

//
// ================================================================
//



//
// == prototypes =====================================================
//



void wm_process_windows(void);


void yellow_status( char *string );


int 
is_within ( 
    struct gws_window_d *window, 
    unsigned long x, 
    unsigned long y );


//refaz zorder.
void reset_zorder(void);
void invalidate_window (struct gws_window_d *window);


// #todo
// Precisamos usar o esquema de cores.
void *gws_draw_button ( 
    unsigned char *string,
    int style,
    int state,
    int type, 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height, 
    unsigned long color );


int rect_validate_size( struct gws_rect_d *rect );
int rect_validate_size2( struct gws_rect_d *rect );


int 
rect_contains_vertically ( 
    struct gws_rect_d *rect,  
    unsigned long y );
    
int 
rect_contains_horizontally ( 
    struct gws_rect_d *rect,
    unsigned long x );



void 
rect_set_left ( 
    struct gws_rect_d *rect, 
    unsigned long value );

void 
rect_set_top ( 
    struct gws_rect_d *rect, 
    unsigned long value );

void 
rect_set_right ( 
    struct gws_rect_d *rect, 
    unsigned long value );

void 
rect_set_bottom ( 
    struct gws_rect_d *rect, 
    unsigned long value );




int is_rect_null( struct gws_rect_d *rect );

int is_rect_empty( struct gws_rect_d *rect );

int is_rect_dirty( struct gws_rect_d *rect );


void *rect_memcpy32 ( void *v_dst, const void *v_src, unsigned long c );


int gwssrv_refresh_this_rect( struct gws_rect_d *rect );

void 
gws_refresh_rectangle ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height );



void 
rectBackbufferDrawRectangle ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height, 
    unsigned long color,
    int fill );

int
set_rect ( 
    struct gws_rect_d *rect, 
    unsigned long left, 
    unsigned long top,
    unsigned long width,
    unsigned long height );

void 
inflate_rect ( 
    struct gws_rect_d *rect, 
    unsigned long cx, 
    unsigned long cy );

void 
copy_inflate_rect ( 
    struct gws_rect_d *rectDest, 
    struct gws_rect_d *rectSrc, 
    unsigned long cx, 
    unsigned long cy );

void 
offset_rect ( 
    struct gws_rect_d *rect, 
    unsigned long cx, 
    unsigned long cy );
    
void 
copy_offset_rect ( 
    struct gws_rect_d *rectDest, 
    struct gws_rect_d *rectSrc, 
    unsigned long cx, 
    unsigned long cy ); 
    
int gws_show_window_rect (struct gws_window_d *window);


void demoTerry(void);

struct gws_window_d *createwCreateRootWindow(void);


// #important: 
// O frame de uma janela deve fazer parte do window manager
// e não das primitivas do window server.
// Estamos falando da parte do ws que opera como wm,
// ou oferece recursos que serão usados pelo wm.
// In: style = estilo do frame.
int 
wmDrawFrame ( 
    struct gws_window_d *parent,
    struct gws_window_d *window,
    unsigned long x,
    unsigned long y,
    unsigned long width,
    unsigned long height,
    int style );          


void *createwCreateWindow2 ( 
    unsigned long type, 
    unsigned long status, 
    unsigned long view, 
    char *windowname, 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height, 
    struct gws_window_d *pWindow, 
    int desktopid, 
    unsigned long clientcolor, 
    unsigned long color ) ;




// Essa será a função que atenderá a interrupção
//esse é o serviço de criação da janela.
// talvez ampliaremos o número de argumentos

void *createwCreateWindow ( 
    unsigned long type, 
    unsigned long status, 
    unsigned long view, 
    char *windowname, 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height, 
    struct gws_window_d *pWindow, 
    int desktopid, 
    unsigned long clientcolor, 
    unsigned long color ); 



void 
dtextDrawString ( 
    unsigned long x,
    unsigned long y,
    unsigned long color,
    unsigned char *string );
              
void 
dtextDrawText ( 
    struct gws_window_d *window,
    unsigned long x,
    unsigned long y,
    unsigned long color,
    unsigned char *string );


int gwsRegisterWindow (struct gws_window_d *window);

int get_active_window (void);
void set_active_window (int id);


int get_window_with_focus(void);
int set_window_with_focus(int id);


int get_top_window (void);
void set_top_window (int id);

int get_zorder ( struct gws_window_d *window );


int 
gws_resize_window ( 
    struct gws_window_d *window, 
    unsigned long cx, 
    unsigned long cy );


int 
gwssrv_change_window_position ( 
    struct gws_window_d *window, 
    unsigned long x, 
    unsigned long y );


int gwssrv_redraw_window (struct gws_window_d *window, unsigned long flags ); 

void gwsWindowLock (struct gws_window_d *window);
void gwsWindowUnlock (struct gws_window_d *window);

int gwsDefineInitialRootWindow ( struct gws_window_d *window );

int gwssrv_init_windows(void);



#endif    



//
// End.
//

