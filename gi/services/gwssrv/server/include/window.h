/*
 * File: window.h
 * 
 * History:
 *     2020 - Created by Fred Nora.
 */

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


/*
 ***********************************************
 * Messages.
 * mensagens para procedimentos de janelas e 
 * para diálogos dentro do gws.
 * Obs: Isso refere-se principalmente à janelas.
 */

 
 //??tipos de mensagens ??
#define MSG_NULL          0 
#define SIGNAL_NULL       0 
#define STREAM_MSG_NULL   0 
#define BUFFER_MSG_NULL   0 
#define CAT_MSG_NULL      0  

 
//window (1-19)  
#define MSG_CREATE        1
#define MSG_DESTROY       2
#define MSG_MOVE          3 
#define MSG_SIZE          4
#define MSG_RESIZE        5
//#define MSG_OPEN        6
#define MSG_CLOSE         7
#define MSG_PAINT         8
#define MSG_SETFOCUS      9
#define MSG_KILLFOCUS     10
#define MSG_ACTIVATE      11
#define MSG_SHOWWINDOW    12 
#define MSG_SETCURSOR     13
#define MSG_HIDE          14
#define MSG_MAXIMIZE      15
#define MSG_RESTORE       16
#define MSG_SHOWDEFAULT   17

//keyboard (20-29)
#define MSG_KEYDOWN       20
#define MSG_KEYUP         21
#define MSG_SYSKEYDOWN    22
#define MSG_SYSKEYUP      23

//mouse (30 - 39)
//tem uma lista de eventos de mouse em events.h
#define MSG_MOUSEKEYDOWN  30
#define MSG_MOUSEKEYUP    31
#define MSG_MOUSEBUTTONDOWN	30
#define MSG_MOUSEBUTTONUP	31 
#define MSG_MOUSEMOVE	    32
#define MSG_MOUSEOVER	    33
#define MSG_MOUSEWHEEL	    34
#define MSG_MOUSEPRESSED	  35
#define MSG_MOUSERELEASED	  36
#define MSG_MOUSECLICKED	  37
#define MSG_MOUSEENTERED	  38    //?? capturou ??
#define MSG_MOUSEEXITED	       39   //?? descapturou ??
//#define MSG_MOUSEMOVEBYOFFSET
//#define MSG_MOUSEMOVETOELEMENT

//outros (40 - ...)
#define MSG_COMMAND       40
#define MSG_CUT           41
#define MSG_COPY          42
#define MSG_PASTE         43
#define MSG_CLEAR         44 
#define MSG_UNDO          45
#define MSG_INSERT        46
#define MSG_RUN_PROCESS   47
#define MSG_RUN_THREAD    48
//Quando um comando é enviado para o console. ele será atendido pelo
//módulo /sm no procedimento de janela do sistema.
//Todas as mensagens de console serão atencidas pelo procedimento de janela 
//nessa mensagem.
#define MSG_CONSOLE_COMMAND   49
#define MSG_CONSOLE_SHUTDOWN  50
#define MSG_CONSOLE_REBOOT    51
#define MSG_DEVELOPER         52


//UM TIMER SE ESGOTOU,
//#todo>: incluir isso na api.
#define MSG_TIMER 53   
//...




//
// Variables.
//



// Contagem de janelas existentes.
// precisa ser inicializada.
unsigned long windows_count;

int window_with_focus;

int active_window;

int top_window;

// ...



/*
 *************************************
 * button_d:
 *     Structure for button object.
 *     Env: gws in ring3.
 */

struct gws_button_d
{
    object_type_t   objectType;
    object_class_t  objectClass;

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
	
	//int validated;
	//int focus;

    unsigned long x;
    unsigned long y;
    unsigned long cx;
    unsigned long cy;


    unsigned long width;
    unsigned long height;

    unsigned long left;
    unsigned long top;	
    unsigned long right;
    unsigned long bottom;

    unsigned long bg_color; //color_bg;

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



/*
 ********************************
 * gws_window_d:
 * 
 *     The window structure.
 */

struct gws_window_d 
{

    unsigned long id;    //Window Id. 

    char *name;          //Window name.

    unsigned long type;  //tipo ... (editbox, normal, ...)  style???

    // Security and memory management.
    int used;
    int magic;


	// Características dessa janela..


	// Estado: (Full,Maximized,Minimized...)
    int view; 


    // Margins. (position)
    unsigned long left;        //margem esquerda 
    unsigned long top;         //margem superior
    unsigned long right;       //margem direita  
    unsigned long bottom;      //margem inferior  

    // Dimension.
    unsigned long width;       //largura
    unsigned long height;      //altura   


    // Offset inside the window.
    // Can be used by the rectangles.
    unsigned long x;           //deslocamento x
    unsigned long y;           //deslocamento y 

    // Windows's bg.
    unsigned long bg_color; 


// 
//==================================================

    // ??
    // Um alerta de que exite uma mensagem para essa janela.
    int msgAlert;  


    // ??
    int sendOffset;
    int receiveOffset;


	//Filas para uma janela receber mensagens.
	//São os quatro argumentos de um procedimento de janela padrão.


	//
	// CURRENT MESSAGE!
	// 

    // Standard layout of simple messages.
    // It's used by the window procedure.
    // arg1, arg2, arg3, arg4
    
    // O aplicativo depois de pegar os 4 elementos, autoriza o 
    // kernel a colocar uma nova mensagem.
    // '0' indica que não temos uma mensagem válida.
    // '1' indica que temos uma nova mensagem.	
    
    struct gws_window_d *msg_window; 
    int msg; 
    unsigned long long1; 
    unsigned long long2; 

    int newmessageFlag;



	//
	// MESSAGE QUEUE!
	//

    // Queue:
    // wnd, msg, long1, long2.
    unsigned long hwndList[32];
    unsigned long msgList[32];
    unsigned long long1List[32];
    unsigned long long2List[32];


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

	// Client window support.
    
    // É a janela propriamente dita, 
	// excluindo a moldura e a barra de rolagem.
	// Tudo o que há dentro da janela menos o frame.
	// É a parte que é exibida quando a janela está em full screen.
    
    struct gws_window_d *client_window; 
    struct gws_rect_d *rcClient;     

	//cor do retângulo da área do cliente.
    unsigned long clientrect_bg_color;    



// 
//==================================================

    unsigned long CursorX;
    unsigned long CursorY;
    unsigned long CursorColor;


// 
//==================================================	

	// Bars support.
	// Cada tipo de janela tem seus itens específicos.
	// Esses são os status dos ítens. Se eles estão presentes ou não.

    // #bugbug
    // Remember: Now we will have a ws and a wm.
    // The wm will create the controls.

    int backgroundUsed;
    int shadowUsed;
    int titlebarUsed;
    int menubarUsed; 
    int toolbarUsed;
    int clientAreaUsed;
    int statusbarUsed;
    int scrollbarUsed;
    int minimizebuttonUsed;
    int maximizebuttonUsed;
    int closebuttonUsed;
    int borderUsed;
    //...
    
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
//==================================================


    // Navegation.
    struct gws_window_d *prev; 
    struct gws_window_d *next; 


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


    // scroll bar
    // The wm will call the window server to create this 
    // kind of control.
    struct gws_window_d *scrollbar;
    struct gws_window_d *scrollbar_button1;
    struct gws_window_d *scrollbar_button2;
    struct gws_window_d *scrollbar_button3;

    int isScrollBarButton1;
    int isScrollBarButton2;
    int isScrollBarButton3;
 

    // status bar
    struct window_d *statusbar;


	// Buffer para mensagens pequenas.
    // Será usado pelo produtor e pelo consumidor.
    // char read_buf[WINDOW_MSG_BUFFER_SIZE];
    //
	//
	
	
    //
	//@todo: rever esse cursor, pois ja existe na versão 0.1 acima.
	
	//Posição do cursor para texto dentro da janela.
	//Obs: Deve ser multiplo da altura e largura do caractere.
	//Obs: Para cada janela o cursor pode estar em uma posição diferente.
	//@todo: Deletar isso e começar usar a estrutura.

    // #bugbug
    // Cursor again ??
    unsigned long cursor_x;
    unsigned long cursor_y;



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


    //
    // Client area!
    //

	// ?? Se mudar para Rect pode deletar alguns elementos acima
	// como x, y, width ...
    struct gws_rect_d *rcWindow;

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


	//?? Qual janela o menu usará.
    struct window_d *menu_window;   //Menu Window.

    struct menu_d *sysMenu;         //menu de sistema.(control menu)
    struct menu_d *barMenu;         //menu da barra de menu.
    struct menu_d *defaultMenu;     //menu da janela (*importante)
    //...
	
   // Flag par indicar se a janela é um item de menu ou um botão.
    int isMenu;   
    int isMenuItem;
    
    int isControl;  // Window control ...
    int isButton;  //#importante: Indica que a janela é um botão.
    int isEditBox; //#importante: Indica que a janela é um editbox.
    int isCheckBox;
    int isIcon;

    //
    // button
    //

	// suspenso
	// Se a flag indicar que a janela é um botão, então 
	// essa será a estrutura para o botão.
	//struct button_d *button;


    int selected;         //seleção  de item de menu.
    const char *text;     // 


    // Controls.
    // ps: The wm will create the controls.
    // It will not be used anymore.
    struct gws_window_d *minimize;
    struct gws_window_d *maximize;
    struct gws_window_d *close;


    int isMinimize;
    int isMaximize;
    int isClose;

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
};

struct gws_window_d *ROOT;
//struct gws_window_d *testxxxxxxx;   
//...

// #todo
// We need to define the root window.
// Maybe it will the the screen window.
// Or each screen will have its own root window.



//
// Window list.
//

// This is gonna be used to register the windows.
// These indexes will be returned to the caller.

// #bugbug
// Is it enough ?

#define WINDOW_COUNT_MAX 1024

unsigned long windowList[WINDOW_COUNT_MAX];
//unsigned long gwssrvWindowList[1024]


//
// ================================================================
//





// #todo
// Precisamos usar o esquema de cores.
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
    unsigned long color );




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
    unsigned long color );

int gws_show_window_rect (struct gws_window_d *window);

// #importante
// >>> Criaremos a barra de títulos depois que a janela estiver pronta.
            
int 
createwDrawTitleBar ( 
    struct gws_window_d *window,
    unsigned long x,
    unsigned long y,
    unsigned long width,
    unsigned long height,
    int style,
    char *string );



// In: style = estilo do frame.
int 
createwDrawFrame ( 
    struct gws_window_d *window,
    unsigned long x,
    unsigned long y,
    unsigned long width,
    unsigned long height,
    int style );          



void *
createwCreateWindow2 ( 
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

void *
createwCreateWindow ( 
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
int get_active_window ();
void set_active_window (int id);
int get_zorder ( struct window_d *window );
int get_top_window ();
void set_top_window (int id);

int 
gws_resize_window ( 
    struct gws_window_d *window, 
    unsigned long cx, 
    unsigned long cy );


int 
gws_replace_window ( 
    struct gws_window_d *window, 
    unsigned long x, 
    unsigned long y );
    

void gwsWindowLock (struct gws_window_d *window);
void gwsWindowUnlock (struct gws_window_d *window);

int gwsDefineInitialRootWindow ( struct gws_window_d *window );

int gwssrv_init_windows(void);


//
// End.
//

