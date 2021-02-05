/*
 * File: window.h 
 *
 * 
 * Descrição:
 *    Funções e parâmetros para o kernel controlar a interface gráfica 
 * e as operações com vídeo.
 *
 *     WINDOW -> DESKTOP -> ROOM (WINDOW STATION) -> USER SECTION.
 *
 * 
 * History:
 *     2014 - Created by Fred Nora.
 *     2016 - Review.
 */

 
// z order support.

#define KGWS_ZORDER_BOTTOM  0 
#define KGWS_ZORDER_TOP     1023   //top window
#define KGWS_ZORDER_MAX     1024   //max

 
unsigned long Windows[KGWS_ZORDER_MAX];


// pega a janela que está mais ao topo da zorder e que
// corresponda às cordenadas do mouse.
// retorna window id
int top_at ( int x, int y );

//
// =========
// 
 
 
 //id da janela que o mouse está em cima.
int window_mouse_over; 
 
//
//  ## Ponteiros para ícones ##
// 
 
// Ponteiros para o endereço onde os ícones 
// foram carregados.

// queremos saber se o endereço alocado eh compartilhado ...
// para o window server usar ... entao chamaremos de sharedbufferIcon.

void *shared_buffer_app_icon;  //1
void *shared_buffer_file_icon; 
void *shared_buffer_folder_icon;
void *shared_buffer_terminal_icon;
void *shared_buffer_cursor_icon;
// ... 


void *ui_get_system_icon( int n );

//testando ... devemos chamar isso
//somente depois que todas as estruturas 
//necessárias estiverem inicializadas.
//como filsystem. 

int windowLoadGramadoIcons (void); 
 
//test: suporte a getch();

int window_getch (void); 




//
// #importante:
// Tipos de mensagem de comunicação nos diálogos 
// e procesimento de janelas:
// 
// SIGNAL_       Sinal. Não contém argumentos.
// MSG_          Message. Contém os argumentos padrão.
// STREAMMSG_    Streams. O argumento é um ponteiro para uma stream.
// BUFFER_MSG_   Buffer. O argumento é um ponteiro para um buffer.
// CAT_MSG_      Concatenate. Os argumentos long1 e long devem ser concatenados.
//
 
//
// Window handle status
// Se uma janela está aberta ou não. 
//
#define HANDLE_STATUS_CLOSE 0
#define HANDLE_STATUS_OPEN 1
 
 
//used
#define WINDOW_NOTUSED   0
#define WINDOW_USED      1
#define WINDOW_GC        216   //Sinalizada para o GC.
//...

//magic
#define WINDOW_NOTMAGIC  0
#define WINDOW_MAGIC     1234 
#define WINDOW_CLOSED    4321
//... 
 
 
//desktop window. (Área de trabalho) 
//#define MAINWINDOW_DEFAULTX  ?
//#define MAINWINDOW_DEFAULTY  ?
 

 

 
// Número máximo de janelas.
//@todo: Aumentar esse tamanho.


// # window lock support #
#define WINDOW_LOCKED 1
#define WINDOW_UNLOCKED 0


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
#define MSG_HIDE          14  // ?? (MIN)
//#define MSG_MINIMIZE    14  // ?? (MIN)
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

//Quando um comando é enviado para o terminal. ele será atendido pelo
//módulo /sm no procedimento de janela do sistema.
//Todas as mensagens de terminal serão atencidas pelo procedimento de janela 
//nessa mensagem.
//#bugbug: temos outro grupo de mensagems abordadndo esse tema logo abaixo.

#define MSG_TERMINAL_COMMAND 49
#define MSG_TERMINAL_SHUTDOWN 50
#define MSG_TERMINAL_REBOOT   51

#define MSG_DEVELOPER 52


//UM TIMER SE ESGOTOU,
#define MSG_TIMER 53   
//...


//o servidor de rede se comunica com o processo.
#define MSG_AF_INET 54
#define MSG_NET_DATA_IN 55

//o driver de network está notificando um processo em ring3.
#define MSG_NETWORK_NOTIFY_PROCESS 56


//
// mouse support: continuação ...
//
#define MSG_MOUSE_DOUBLECLICKED   60
#define MSG_MOUSE_DRAG            61
#define MSG_MOUSE_DROP            62
//...

//
//  terminal commands
//

#define MSG_TERMINALCOMMAND      100
#define TERMINALCOMMAND_PRINTCHAR 1000
//#define TERMINALCOMMAND_PRINT??? 1001
//...


// o evento de rolagem aconteceu ...
// O número do evento será entregue em long1.
#define MSG_HSCROLL 2000
#define MSG_VSCROLL 2001



// 
// ==== Window Type ====
//

#define WT_NULL          0 
#define WT_SIMPLE        1
// Igual simples, mais uma bordinha preta.
#define WT_EDITBOX       2
// Sobreposta (completa)(barra de titulo + borda +client area). 
#define WT_OVERLAPPED    3  
// Um tipo especial de sobreposta, usada em dialog ou message box. 
// (com ou sem barra de titulo ou borda)
#define WT_POPUP         4
// Caixa de seleção. Caixa de verificação. 
// Quadradinho.  
#define WT_CHECKBOX      5
// Cria uma scroll bar. 
// Para ser usada como janela filha.  
#define WT_SCROLLBAR     6  
#define WT_EDITBOX_MULTIPLE_LINES 7
#define WT_BUTTON        8   
#define WT_STATUSBAR     9
// Pequeno retângulo com uma imagem bmp e talvez texto.
#define WT_ICON          10
#define WT_TITLEBAR 11
//... 



// window style
#define WINDOW_STYLE_FLOATING 1000 
#define WINDOW_STYLE_DOCKING  2000  //(atracada em algum canto.)
//...


// window status
#define WINDOW_STATUS_ACTIVE       1
#define WINDOW_STATUS_INACTIVE     0
//...

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




//apresentação.
#define VIEW_NULL      0
#define VIEW_FULL      1000  // * Full screen.
#define VIEW_MAXIMIZED 1001  
#define VIEW_MINIMIZED 1002
#define VIEW_NORMAL    1003  //Normal (restaurada)
//...

//
// ## botoes  ##
//

//button state
#define BS_NULL 0 
#define BS_DEFAULT 1
#define BS_FOCUS   2
#define BS_PRESS   3
#define BS_HOVER   4
#define BS_DISABLED 5
#define BS_PROGRESS 6
//...


    //button states:
    //0. NULL.
	//1. Default 
    //2. Focus
    //3. Expanded/Toggled/Selected
    //4. Disabled
    //5. Hover and Active	

//#define BN_CLICKED  200
//#define BN_DOWN     1
//#define BN_UP       2
//#define BN_SELECTED 3



 
//@todo: what ??? 
//?? um handle para o desktop. 
#define HWND_DESKTOP 0


 
 
/*
 * Dimensões: 
 * 
 * Parametro principal para dimensões de janela.
 * todos os outros tomam esse como refêrencia.
 * depende do modo que estiver usando.
 *
 * vesa 112:
 *
 * 640x480x24bit - (3 bytes por pixel)
 * 
 * @todo, o kernel usará dimensões 640x480 no modo gráfico.
 */   
#define KERNEL_COL_MAX 640 
#define KERNEL_LIN_MAX 480 

#define	BAR_STEPS   46
#define LINE KERNEL_COL_MAX 

//dimensões - provisorio
#define COL_MAX   KERNEL_COL_MAX 
#define LINHA_MAX KERNEL_LIN_MAX  






/*
 * Constants para a task bar.
 */
 
//#define TASKBUTTONS_BASE 40
//#define CLOCK_BASE  (KERNEL_COL_MAX-40)


//=========================================
//    ****    KERNEL WINDOW    ****
//Definições padronizadas para janelas do kernel usadas para 
//fornecer informações sobre o sistema.
// (Retângulo grande no topo da tela.)
// #bugbug
// Isso não é uma coisa boa.

#define KERNEL_WINDOW_DEFAULT_LEFT 0
#define KERNEL_WINDOW_DEFAULT_TOP  0
#define KERNEL_WINDOW_DEFAULT_WIDTH  800
#define KERNEL_WINDOW_DEFAULT_HEIGHT (600/4) 
#define KERNEL_WINDOW_DEFAULT_CLIENTCOLOR  xCOLOR_GRAY2
#define KERNEL_WINDOW_DEFAULT_BGCOLOR      xCOLOR_GRAY1
//...



//
// ******** ESSA VARIÁVEL BLOQUEIA O FOCO NA JANELA DO DESENVOLVEDOR   *****
//
int _lockfocus;


// ESSA SERÁ USADA DEPOIS QUANDO A INTERFACE GRÁFICA ESTIVER MAIS ROBUSTA;
int gFocusBlocked;   



// #todo: deletar.
unsigned long g_mainwindow_width;
unsigned long g_mainwindow_height;
unsigned long g_navigationbar_width;
unsigned long g_navigationbar_height;


/*
 *************************************
 * button_d:
 *     Structure for button object.
 */

struct button_d
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
    struct window_d *window; 
    
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
    struct button_d *Next;  
};

//Botões na janela principal. 
struct button_d *mainButton1;  
struct button_d *mainButton2;  
struct button_d *mainButton3;  
//...


/*
 *************************************************
 * taskbar_d: 
 * Estrutura para a task bar.
 * Essa estrutura é marcador oficial das dimensões da barra de tarefas.    
 * Essa é a barra de tarefas tradicional, aquela que normalmente fica 
 * em baixo e contêm ícones dos programas abertos.
 * Porém essa barra na verdade é uma janela e pode ser redimensionada 
 * ou movida.
 * O kernel terá registro disso para salvar as dimensões da
 * área de trabalho, que é o tamanho da tela menos o tamanho da barra.
 */

// #bugbug
// Lembrando que a taskbar deve ser um app.

struct taskbar_d
{
	object_type_t objectType;
	object_class_t objectClass;
	
    int used;
    int magic;
	
	//estilo de design.
	int style;

    unsigned long Left;
    unsigned long Top;
    unsigned long Width;
    unsigned long Height;
}; 
struct taskbar_d *TaskBar;    //*Importante: Sem Ponteiro.


/*
 *******************************************
 * menubar_d: 
 *     Estrutura para a menu bar.
 *
 *     Essa estrutura é marcador oficial das dimensões
 *     da barra de menu.    
 *
 *     Essa é a barra de menu tradicional,
 *     que aparece no topo da tela e oferece
 *     um conjunto de menus para manipular
 *     o porcesso com a janela ativa.
 */

struct menubar_d
{
	object_type_t objectType;
	object_class_t objectClass;	
	
    int used;
    int magic;
	
	//estilo de design.
	int style;
	
    unsigned long Left;
    unsigned long Top;
    unsigned long Width;
    unsigned long Height;
}; 
struct menubar_d *MenuBar;    //*Importante: Sem Ponteiro.

 

/*
 * window_procedure_d:
 *     Estrutura para procedimento de janela.
 */ 

struct window_procedure_d
{

	object_type_t objectType;
	object_class_t objectClass;
	
    //4 argumentos do procedimento
	struct window_d *window;  //à qual janela pertence o procedimento.
    int msg;	
	unsigned long long1;
	unsigned long long2;
	
	//Parametros extras.
	
	struct d_process *process; //à qual processo pertence o procedimento.
	struct d_thread  *thread;  //à qual thread pertence o procedimento.
	
	int msgStatus;
	int active_window;      //Id da janela ativa.
	int window_with_focus;  //Id da janela com o foco de entrada.

	//...
};
struct window_procedure_d *CurrentProcedure;
struct window_procedure_d *WindowProcedure;
//... 
 


/*
 **************************************************
 * rect_d:
 *     Estrutura para gerenciamento de retângulos.
 *     Um retângulo pertence à uma janela.
 */

// #todo
// Usar isso para lidar com dirty rectangles.

struct rect_d 
{
	object_type_t objectType;
	object_class_t objectClass;

    int used;
	int magic;
	
	int flag;
	
	//estilo de design
	int style;
	
	//int validated;
	//int focus;
	
	//int dirty;
	
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
	struct window_d *window;
	
	struct rect_d *next;
};
struct rect_d *rect;
//Retângulo da área de cliente da janela ativa.
struct rect_d *rectClientArea;   
//...


/* rgba */
struct tagRGBA
{
	object_type_t objectType;
	object_class_t objectClass;	
	
   char red;
   char green;
   char blue;
   char alpha;
};
struct tagRGBA *RGBA;


	//
	// Window Class support.
	//

// ?? rever. 
// Enumerando classe de janela 
typedef enum {
    WindowClassNull,
	WindowClassClient,    // 1 cliente
	WindowClassKernel,    // 2 kernel
	WindowClassServer,    // 3 servidor
}wc_t;



//classes de janelas controladas pelos aplicativos.
typedef enum {
    WindowClassApplicationWindow,	
	//...
}client_window_classes_t;


//??bugbug: tá errado.
//classes de janelas controladas exclusivamente pelo kernel.
typedef enum {
	WindowClassKernelWindow,    //janelas criadas pelo kernel ... coma a "tela azul da morte"
    WindowClassTerminal,  //janela de terminal usada pelos aplicativos que não criam janela e gerenciada pelo kernel	
    WindowClassButton,
	WindowClassComboBox,
	WindowClassEditBox,
	WindowClassListBox,
	WindowClassScrollBar,
	WindowClassMessageOnly, //essa janela não é visível, serve apenas para troca de mensagens ...
	WindowClassMenu,
	WindowClassDesktopWindow,
	WindowClassDialogBox,
	WindowClassMessageBox,
	WindowClassTaskSwitchWindow,
	WindowClassIcons,
	WindowClassControl,   //??
    WindowClassDialog,
    WindowClassInfo,
    //...	
}kernel_window_classes_t;


//classes de janelas controladas pelos servidores.
typedef enum {
    WindowClassServerWindow,
    //...	
}server_window_classes_t;



//estrutura para window class
struct window_class_d
{
	
	//Que tipo de window class.
	// do sistema, dos processos ...
    //tipo de classe.
	
	wc_t windowClass; 

	//1
    client_window_classes_t	clientClass;
	
	//2
	kernel_window_classes_t	kernelClass;
	
	//3
	server_window_classes_t	serverClass;
	
	//Endereço do procedimento de janela.
	//(eip da thread primcipal do app)
	unsigned long procedure;
    //...
};


// usada nas filas de mensagens que existem nas estruturas de thread.
struct msg_d 
{
    int used;
    int magic;
    
    struct window_d *window;
    int msg;
    unsigned long long1;
    unsigned long long2;
};


 
/*
 ********************************************************
 * window_d:
 *     Window - nível 1. 
 *     Estrutura para janelas.
 *
 * terminal:
 *     Toda estrutura de janela poderá ter apenas 
 * um terminal.
 *     Colocar um terminal dentro da estrutura de janela 
 * não impede o sistema de ter as estruturas tradicionais 
 * de terminal, porém pode trazer algumas vantagens na hora 
 * da manipulação do retângulo que compreende tanto a tela
 * do terminal quanto a área de cliente da janela.
 *    Porém um terminal pode ser full screen e não 
 * pertencer a uma janela. Para isso ele considera apenas 
 * as dimensões da tela. Nesse caso o terminal seria 
 * gerenciado por uma estrutura tradicional de terminal.
 *
 */


// Deve estar em conformidade com a estrutura em user mode.
//=========================================================

struct window_d
{
    // Identificadores.
    object_type_t objectType;
    object_class_t objectClass;


	//object control
    struct object_d *object;


    unsigned long id;    //Window Id. 

    char *name;          //Window name.
    unsigned long type;  //tipo ... (editbox, normal, ...)  style???


	//Segurança.
    int used;
    int magic;


	// Características dessa janela..

	//Estado: (Full,Maximized,Minimized...)
    int view; 


	//dimensões e margens.
	
	//#bugbug 
	//Esses conceitos estão sob revisão.
	//Estou aprendendo ...

	//+margem é o deslocamento até encontrar a borda.
	//+padding é o deslocamento entre a borda e a janela.

    unsigned long left;        //margem esquerda 
    unsigned long top;         //margem superior
    unsigned long right;       //margem direita  
    unsigned long bottom;      //margem inferior  


    unsigned long width;
    unsigned long height;

	// ??
	// Deslocamento dentro da janela?
    unsigned long x;           //deslocamento x
    unsigned long y;           //deslocamento y 
    int z;                     // z order.
    
    //invalidadas.
    //indica que precisamos repintar essa quando
    //chamarmos a rotina redraw_windows ou redraw_screen
    //See wm.c
    int invalidated;               

    // Background color.
    // Em user mode estamos usando color_bg.
    unsigned long bg_color;  

//==================================================

    // Alertartando que exite uma mensagem para essa janela.
    int msgAlert;  

    //?? rever
    int sendOffset;
    int receiveOffset;


	//Filas para uma janela receber mensagens.
	//São os quatro argumentos de um procedimento de janela padrão.


	//
	// CURRENT MESSAGE !!!
	// 

	//shared by producer and consumer 
    struct window_d *msg_window;  //arg1.
    int msg;                      //arg2.
    unsigned long long1;          //arg3.
    unsigned long long2;          //arg4.

    //O aplicativo depois de pegar os 4 elementos, autoriza o 
    //kernel a colocar uma nova mensagem.
    //'0' indica que não temos uma mensagem válida.
    //'1' indica que temos uma nova mensagem.
    int newmessageFlag;


    // MESSAGE QUEUE !!!
    //shared by producer and consumer
    unsigned long hwndList[32];
    unsigned long msgList[32];
    unsigned long long1List[32];
    unsigned long long2List[32];

    //struct msg_d *msg;

	// procedure support. 
	//(poderia ser um argumento ou elemento da classe.)
    unsigned long procedure;               //procedimento da janela
    struct window_procedure_d *wProcedure; //procedure struct

//==================================================
    int active;    //FAST FLAG. Essa será a flag de ativa ou não. (decidindo isso)
    int focus;     //Se tem o foco de entrada ou não.

	// Parent support
    unsigned long parentid;       //(Número da janela mãe).
    struct window_d *parent;      //Parent window.


	// Child support.
    struct window_d *childListHead;  //Lista encadeada de janelas filhas.
    int childCount;                  //Tamanho da lista.

//==================================================


	// Client window support.

	// É a janela propriamente dita, 
	// excluindo a moldura e a barra de rolagem.
	// Tudo o que há dentro da janela menos o frame.
	// É a parte que é exibida quando a janela está em full screen.

    struct window_d  *client_window; 
    struct rect_d    *rcClient; 


	//cor do retângulo da área do cliente.
    unsigned long clientrect_bg_color; 

//==================================================

    // Cursor
    // #remember: 
    // We want to use the cursor structure.
    // We are using the current console structure.

    // Cursor position inside the window in chars.
    unsigned long CursorX;
    unsigned long CursorY;

    // #maybe
    //unsigned long CursorXInPixels;
    //unsigned long CursorYInPixels;

    unsigned long CursorColor;
    //int CursorIconIndex;
    //unsigned long CursorIconAddress;
    // ...

//==================================================

	// Bars support.
	// Cada tipo de janela tem seus itens específicos.
	// Esses são os status dos ítens. Se eles estão presentes ou não.

    int backgroundUsed;
    int shadowUsed;
    int titlebarUsed;
    int menubarUsed; 
    int toolbarUsed;
    int clientAreaUsed;
    int statusbarUsed;
    int minimizebuttonUsed;
    int maximizebuttonUsed;
    int closebuttonUsed;
    int borderUsed;
	// ...


//==================================================

	// Buffer.
	// DedicatedBuffer
	// DedicatedBuffer --> LFB.
	// Endereço de memória onde a janela foi pintada.
	// Obs: Toda janela deve ter seu próprio buffer de pintura para poder 
	// passar a janela direto de seu próprio buffer para o LFB, sem passar 
	// pelo Backbuffer.

    void *DedicatedBuffer;  // Qual buffer dedicado a janela usa.
    void *BackBuffer;       // Qual backbuffer a janela usa.
    void *FrontBuffer;      // Qual frontbuffer a janela usa. (LFB).

//==================================================

	// Desktop support.
	// A que desktop a janela pertence??

    int desktop_id;
    struct desktop_d *desktop; 


// Gramado v 0.1 usa essa estrutura somente até aqui.
//==================================================

//
// Update 
//

//==================================================

	// Relação entre janelas.
    struct window_d *owner;
    struct window_d *child; 

    //Configuramos isso quando efetuamos um raise_window
    //colocando a janela acima das outras.
    struct window_d *child_with_focus; 


 
//==================================================
    struct window_d *statusbar;
    struct window_d *toolbar;


//==================================================

    // Buffer para mensagens pequenas.
    // Será usado pelo produtor e pelo consumidor.
    // char read_buf[WINDOW_MSG_BUFFER_SIZE];


//==================================================

	// Window Class
    struct window_class_d *window_class;
    
//==================================================

    //unsigned long scancodeList[32];

//==================================================

	// ID da tty usada.
    int tty_id;

//==================================================

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
	
	//rect
    unsigned long terminal_left;
    unsigned long terminal_top;
    unsigned long terminal_width;
    unsigned long terminal_height;

    unsigned long terminal_right;
    unsigned long terminal_bottom;

	//...

	//@todo: isso deve pertencer a uma janela.
	//se uma janela tiver o foco de entrada e for um terminal 
	//a disciplica de linhas poderá usar essas carcterística do terminal.
    struct terminal_d *wTerminal; //dd\uitm\terminal.h
 
//==================================================
 
    // ??
    int tab;

//==================================================

    // style: 
    // Isso poderia ser estilo de design ...
    // Qualquer janela pode ter vários estilos de design 
    // ex: um editbox poderá ser de vários estilos.	

	//window style:
	//WINDOW_STYLE_FLOATING (flutuante) 
	//WINDOW_STYLE_DOCKING   (atracada em algum canto)
    int style;   

//==================================================

    //unsigned long Background;

//==================================================

    //int instance; 

//==================================================


	//*full screen mode = modo tela cheia. 
	//( utiliza a resolução atual do dispositivo )
	// deve ser a janela em primeiro plano. acima de todas as outras.
	//mas podemos configurar para que uma jenela esteja em full screen 
	//enquanto outra janela é a janela ativa e ainda outra tenha o foco de entrada.
	//uma janela em modo full screen pode conter barras de rolagem.
	//*embedded mode = dentro de uma janela ou de um navegador. 

    //unsigned long status;              //ATIVA OU NÃO.

//==================================================    

    // Seu estatus de relacionamento com outras janelas.
    unsigned long relationship_status;   

//==================================================    

	//ordem na pilha de janelas do eixo z.
	//A janela mais ao topo é a janela foreground.
    //int zIndex;    

	//z-order global.
	//Sua ordem em relação a janela gui->main.    
    //struct zorder_d *zorder;

//==================================================    

    //Qual buffer dedicado a janela usa.
    //void *buffer;        

//==================================================    

	//?? Se mudar para Rect pode deletar alguns elementos acima
	//como x, y, width ...
    struct rect_d *rcWindow;

	//Lista encadeada dos retângulos que pertencem a essa janela.
	//Quando uma janela for deletada, devemos desalocar toda a memória 
	//uada por esses recursos.
    struct rect_d *rectList;

//==================================================    

	//
	// CLists
	//

	// Um ponteiro para um array de ponteiros de estruturas de linhas
	// Explicando: 
	// Nesse endereço teremos um array. Cada ponteiro armazenado
	// nesse array é um ponteiro para uma estrutura de linha.
	// Obs: 
	// #todo: 
	// Todos esses elementos podem formar uma estrutura e ficaria aqui 
	// apenas um ponteiro para ela.

    void *LineArray;
    int LineArrayIndexTotal;    //Total de índices presentes nesse array.
    int LineArrayIndexMax;      //Número máximo de índices permitidos no array de linhas.
    int LineArrayTopLineIndex;  //Indice para a linha que ficará no topo da página.
    int LineArrayPointerX;      //Em qual linha o ponteiro está. 	
    int LineArrayPointerY;      //em qual coluna o ponteiro está.
	//...

//==================================================    

	//thread de controle
	//Usada para input de mensagens e sinais.
    struct thread_d *control;

//==================================================    

    //  A que processo a janela pertence??
    struct process_d *process;

//==================================================    

	//
	// Menus support.
	//

	//?? Qual janela o menu usará.
    struct window_d *menu_window;   //Menu Window.

    struct menu_d *sysMenu;         //menu de sistema.(control menu)
    struct menu_d *barMenu;         //menu da barra de menu.
    struct menu_d *defaultMenu;     //menu da janela (*importante)
	//...

    int selected;     //seleção  de item de menu.

//==================================================    

    // Flag par indicar se a janela é um item de menu ou um botão.
    int isMenu;   
    int isMenuItem;
    
    int isControl;  // Window control ...
    int isButton;  //#importante: Indica que a janela é um botão.
    int isEditBox; //#importante: Indica que a janela é um editbox.
    int isCheckBox;
    int isIcon;
     
	//...

//==================================================    

	// Se a janela for do tipo botão, então essa será a 
	// estrutura para o gerenciamento do botão.
    struct button_d *button;
    
//==================================================    

    // ??
    const char *text; 

//==================================================    

    struct window_d *minimize;
    struct window_d *maximize;
    struct window_d *close;
    
    //#teste
    int isMinimize;
    int isMaximize;
    int isClose;

//==================================================    

    // Qual janela é um ícone para essa janela.
    // Por exemplo, o ícone que fica na área de trabalho.
    struct window_d *icon;

//==================================================    

    //
    // Actions.
    //

    int draw; 
    int redraw;
    int show;   //se precisa ou não mostrar a janela.	
    // Continua ...

//==================================================    

	// Text Cursor support.
	// fica para uma versão estendida da estrutura.
	// Estrutura de cursor para a janela.
    struct cursor_d *cursor;

//==================================================    

	//unsigned long bgcolor;		// Background color.
	//unsigned long fgcolor;		// Foreground color. 

//==================================================    

    struct button_d *current_button;  //Botão atual.      
    struct button_d *buttonList;      //Lista encadeada de botões em uma janela.

//==================================================    

	// ??
	// Status do puxador da janela.
	// Se está aberta ou não.
	// HANDLE_STATUS_OPEN ou HANDLE_STATUS_CLOSE
	int handle_status;

//==================================================

	// Trava. Se travada, não pode mudar nada.
	// Enables or disables mouse and keyboard input to the 
	// specified window or control.
    int locked; 

//==================================================

    //
    // Terminal.
    //
    
    int isTerminal;
    struct vt_d *terminal;

    // Navegation.
    struct window_d *prev; 
    struct window_d *next; 
};

struct window_d *CurrentWindow;    //Janela atual
struct window_d *ActiveWindow;     //Janela atual.
struct window_d *WindowWithFocus;  //Janela com o foco de entrada.   
//...

// Lista encadeada de janelas.
struct window_d *window_Conductor2;
struct window_d *window_Conductor;
struct window_d *window_rootConductor;
//...



 /*
 * Lista de janelas.
 * @todo: Na verdade poderia ser alocação dinâmica
 * pois o numero de janelas é muito grande. isso deixaria o kernel grande demais.
 */ 
unsigned long windowList[WINDOW_COUNT_MAX];

//
// Browser support. (SHELL.BIN)
//

//#define TABWINDOW_COUNT_MAX 12  //F1 à F12.

/* Essa é a aba onde os lementos devem ser criados ...
quando um aplicativo chamar serviços do kernel para criar elementos na aba.*/
//int current_tab;

//#cancelada
//struct window_d *BROWSERWINDOW;    //Ponteiro para a janela do navegador.
//struct window_d *TABWINDOW;        //ponteiro para a janela da tab atual..

//janela full screen que será usada pelo navegador...
//essa janela deve ter as dimensões da tela...
//Obs: já existe uma janela com essas características ... que é a janela 
//gui->screen ... lenbrando que não queremos que a janela gui->screen tenha 
//os valores de sua estrutura alterados ... pois refletem as características do dispositivo.
//Importante: Estragar essa estrutura pode causar muitos problemas.
struct window_d *FULLSCREEN_TABWINDOW;   



//
// z order support
//

//#define ZORDER_COUNT_MAX  128  //??PROVISÓRIO   

int zorder;

//esses tipo indicam algum posicionamento dentro da xorder.
typedef enum {
	zordertypeNull,     //ignorado
    zordertypeTop,      //acima de todas
    zordertypeBottom,   //abaixo de rodas.
    //...	
}zorder_type_t;



//essas são as camadas onde os objetos gráficos ficam ...
//estão associadas com formulários e containers.
typedef enum {
	zorderlayerNull,     //ignorado
    zorderlayerBack,     //back layer. é a área onde os métodos invocarão a construção de objetos gráficos.
    zorderlayerMiddle,   //middle layer. é onde os objetos gráficos e as etiquetas de controle são colocadas.
	zorderlayerFront,    //front layer. são colocados os controles não gráficos como: 
	                     //CommandButton, CheckBox e ListBox 
    //...	
}zorder_layer_t;


int zorderCounter;         //contador de janelas incluidas nessa lista.   
int zorderTopWindow;
//...

//
//Estrutura para controlar um índice de janela 
//ponteiros de instãncias dessa estrutura ficarão na lista zorderList[].
// Obs: uma estrutura de janela pode ter um poteiro para essa 
// estrutura que controlará todas as propriedades de zorder relaticas a aquela janela.
//
struct zorder_d
{
	// tipo ... top ou bottom.
	//encontraremos com facilidade se ela é top ou bottom.
	
	//zorder_type_t zorderType; 
	//zorder_layer_t zorderLayer;
	
	int zIndex;
    
	//?? ...
	
    struct window_d *window;
	
	//toda janela está na lista de zorder de outra janela.
	struct window_d *parent; //janela mãe... 
	
	struct zorder_d *next;
};


/* 
struct zorderInfo
{
    struct window *top_window;	
} 
*/




/*
 * zorderList[] support.
 *     Sobreposição de janelas.    
 *     ?? Precisamos reorganizar a lista ??
 *     ?? seria melhor uma lista encadeada ??
 *     ??e quando fecharem uma janela no meio da lista ??
 *
 *  >> Quando criamos uma janela ela é incluída no primeiro lugar vago da lista.
 *  >> quando deletamos uma janela, apenas excluimos ela da lista, não precisamos reorganizar.
 *  >> uma janelas minimizada é excluida dessa lista, é zerada z_axis_order na sua estrutura.
 *  >> repintaremos começando do zero.
 */ 
//unsigned long zorderList[ZORDER_COUNT_MAX];





//
// Backbuffer support. (espelho da memória de video)
//

struct backbufferinfo_d
{
	//@todo: object support

    int used;
    int magic;
	
    unsigned long start;
    unsigned long end;
    unsigned long size;
    //...

    //@todo:
	// ?? O que nos podemos ter aqui ??	
	// terminal., window, line disciplice, cursor ...
	//input buffer? z-order ??
};
struct backbufferinfo_d *BackBufferInfo;




//
// Frontbuffer support. (memória de vídeo)
//

struct frontbufferinfo_d
{
	//@todo: object support
	
	int used;
	int magic;
	
    unsigned long start;
    unsigned long end;
    unsigned long size;
	
	unsigned long width;
    unsigned long height;
	unsigned long bpp;
	//
	
    //@todo:
	// ?? O que nos podemos ter aqui ??	
	// terminal., window, line disciplice, cursor ...	
};
struct frontbufferinfo_d *FrontBufferInfo;


/*
 **********************************************************
 * gui:
 *     Nível 0 
 *     ## gui  ##
 *
 * Obs: Foi incluído aqui os ponteiros para as janelas principais usadas nos 
 * principais recursos gráficos, como control menu do desktop por exemplo.
 *
 * Histórico: 
 * 2015 - Created.
 * 2016 - incluíndo novos elementos.
 * ...
 */


struct gui_d
{

	//Se a gui está ou não inicializada.
	int initialised;		  

	
	//Procedimento da janela ativa.
	unsigned long procedure;  

	
	/*
	 *    ****    BUFFERS    ****
	 *    Ponteiros para os principais buffers usados pelo sistema.
	 */
	
	
	/*
	 * LFB:
	 * O endereço do início da memória de vídeo do cartão de memória.
	 * Obs: Quantos desses ponteiros precisamos dentro da memória de
	 * vídeo? E se tivermos várias placas de memória de vídeo, seria
	 * um lfb para cada placa?
	 * Esse valor foi configurado pelo BIOS pelo metodo VESA.
	 */
	
	 unsigned long lfb;
	 
	/*
	 * Backbuffers.
	 *     O Backbuffer pe o buffer para colocar a imagem de pano de fundo.
	 * Ele será o buffer dedicado da janela principal gui->main. 
	 */
	
	// #importante.
	// Um backbuffer pode cobrir a área de vários monitores.
	// O conceito de backbuffer pode estar relacionado com o conceito de room,
	// (window station), com vários desktops e monitores.
	
	unsigned long backbuffer;
	
    void *backbuffer1; 
	void *backbuffer2; 
	void *backbuffer3;
	//...
	
	
	/*
	 * Default dedicated buffers.
	 *     Esses ponteiros podem ser usados para aloca
	 * memória para buffer dedicado antes mesmo de se criar a estrutura
	 * da janela.
	 * Obs: Toda janela tem que ter um buffer dedicado, onde ela será pintada.
	 * Depois de pintada ela pertencerá a uma lista de janelas que serão
	 * enviadas para o LFB seguindo a ordem da lista.
	 */
	
	//void* defaultWindowDedicatedBuffer1;
	//void* defaultWindowDedicatedBuffer2;
	//void* defaultWindowDedicatedBuffer3;
    //...	
	
	
	/*
	 * Flag para repintar todas as janelas.
	 * @todo: #bugbug, Isso parece estranho. Cada janela
	 * está pintada em seu buffer dedicado e fica por conta de
	 * cada janela decidir se repinta ou não apenas ela.
	 */
	int redraw;	

	
	/*
	 * Flag para enviar do backbuffer para a memória de video.
	 * Seguindo uma lista linkada, copiaremos o conteúdo do buffer
	 * dedicado de cada janela da lista no LFB. Primeiro é Backbuffer
	 * que é o buffer da janela principal, que funcionará como
	 * Head da lista.
	 */
	int refresh;			       
    //struct window_d * redrawWindowListHead;	
	
	
	//status das janelas usadas pelo sistema.
	int screenStatus;
	int backgroundStatus;
	int logoStatus;
	int mainStatus;
	int navigationbarStatus;	
	int menuStatus;
	int taskbarStatus;
	int statusbarStatus;	
	int infoboxStatus;
	int messageboxStatus;
	int debugStatus;
	int gridStatus;
	
	
	/*
	 *    ****    Windows    ****
	 *
	 * Obs: Ponteiros para as janelas principais usadas na interfáce
	 * gráfica. Essas janelas não dependem dos processos e sim os
	 * processos dependem delas. Os processos do sistema poderão recriar
	 * essas janelas e registrar seus ponteiros aqui. Por exemplo, o control
	 * menu pode sofrer alterações e depois registrar o ponteiro aqui.
	 * Outro exemplo é o control menu da janela ativa, toda vez que
	 * trocar a janela ativa, deve-se registrar o ponteiro do control menu
	 * da janela aqui, para fácil acesso.
	 *
	 * Os ponteiros aqui serão organizados em grupos:
	 * ==============================================
	 * Screen - root window
	 * Grupo 0: Background, Logo, Desktop, Taskbar.
	 * Grupo 1: Main (Full Screen), Status Bar. 
	 * Grupo 2: Grid. (grid de ícones flutuantes)
	 * Grupo 3: Control menu.(Control menu da janel atual).
	 * Grupo 4: Info Box, ToolTip.
	 * Grupo 5: ??
	 * Grupo 6: Outras.
	 */
	
	//Screen: 
	//      A tela. Tem as dimensões do monitor usado.
	// Root window.   
	
    struct window_d *screen; 	
	
	//
	// Grupo 0: Background, Logo, Desktop, Taskbar.
	//
	
	// A única janela em primeiro plano e com o foco de entrada. 
	// Será usada pelo desenvolvedor durante a construção dos 
	// elementos gráficos, até que o sistema gráfico fique mais robusto
	// e permita ficar trocando a janela com o foco de entrada.
	// Isso é para evitar confusão de output nesa fase.
	
    struct window_d *DEVELOPERSCREEN;    
	
    
	// Background: 
	//     Uma janela popup com as dimensões da tela.
	struct window_d *background; 

	//Logo: A imagem de pano de fundo.
    struct window_d *logo;
	
	
	
	/*
	 * Desktop:
	 *    A Área de trabalho.    
	 *    Uma área de tamanho variável,
	 *    dependendo da presensa ou não da barra de tarefas.
	 *    É a área onde ficam os ícones e as janelas dos
	 *    programas.
	 */
    struct window_d *desktop; 

	/*
	 * Task Bar: (top bar) 
	 *     A barra de tarefas.
	 */
	struct window_d *taskbar;


    //
    // Grupo 1: Main (Full Screen), Status Bar. 
    //

	/*
	 * Main:
	 * A área de trabalho.
	 */
    struct window_d *main;

	/*
	 * Status Bar:  
	 *     A barra de status.
	 *     Usada em qualquer condição.
	 *     Fica posicionada dentro de uma janela mãe.
	 */
	struct window_d *statusbar;
	
 
	//
	// Grupo 2: Grid. 
	//
	
	
	/*
	 *Grid:
	 *   (Área para colocar o grid de ícones).
	 *    Área dinâmica dentro da Área de trabalho.
	 *    Essa área de grid pode ser reposicionada
	 *    de acordo com o layout escolhido.
	 */
	struct window_d *grid;
	
	
	
	//
	// Grupo 3: Control menu.
	//
	
    /*
	 * Menu:  
	 *     Ponteiro para a estrutura do control menu atual.    
	 *     Isso depende da janela ativa e da janela com o foco de entrada.
	 *     Esse será o ponteiro para o control menu que deverá ser aberto.
	 *     Varia conforme muda a janela com o foco de entrada.
	 */	
	struct window_d *menu; 

	
	//
	// Grupo 4: Info Box, ToolTip.
	//
	
	/*
	 * Infobox:
	 *     Janela usada para o sistema enviar mensagens de informações.   
     * seria notification window ??	 
	 */
	struct window_d *infobox; 
    
	
	//
	// Pequena janela de notificações, que desaparece depois de um tempo..
	//
	//struct window_d *notification;   	

	
	/*
	 * ToolTip:
	 *     Janelinha que aparece quando repousa o mouse sobre elemento gráfico.
	 *      POPUP. A janela se adapta ao tamanho da string.
	 */
	struct window_d *tooltip;  
	
	
	// Grupo 5: 
	// MessageBox e DialogBox.
    // Isso e' um test.
	
	struct window_d *messagebox;
	struct window_d *dialogbox;
	
	
	//
	// Grupo 6: Outras.
	//
	
	
	//Debug: Janela usada pelo Kernel para mensagens de erro.
	struct window_d *debug;   

    //Menu bar.
	struct window_d *mbhWindow;       //Janela principal da menu bar.
	struct menu_d *mb;               //a menu bar é um menu
	struct menu_d *mbControlPanel;	 //Painel de controle
	struct menu_d *mbComputer;       //Meu computador(discos, diretorios ...)
	struct menu_d *mbFile;           //File manager. (abre e fecha arquivos)
	struct menu_d *mbWindow;         //Window manager (igual sistem menu) 
    //...	
	
	//
	//   **** BARs   ****
	//
	
	
	// Qualquer dessas barras serão gerenciadas pelo kernel ...
	// nãp fazem parate de um aplicativo, Porém o aplicativo gerenciador
	// de arquivos (explorer) será o responsável pela barra de tarefas que será 
	// usada pelo usuário.
	// Essas barras abaixo tem a finalidade de dar alguma navegabilidade
	// mesmo sem algum programa de gerenciamento de arquivos.
	// E também não há problemas em os dois conviverem.
	
	//TopBar.
	struct window_d *topbar;	
	struct menu_d *logonMenu;         //Logon
	struct menu_d *logoffMenu;	      //Logoff 

    //Navigation Bar.
    struct window_d *navigationbar;	
	struct menu_d *desktopMenu;       //Desktop 
	struct menu_d *setupMenu;         //Ambiente de configuração.
	
	//Current Menu.
	//Aponta para a estrutura do menu atual.
	//Seja ele de qual tipo for.
	struct menu_d *currentMenu;       //Current. Para outros ambiente.
	
	
	//
	// #taskman server.#
	//
	
	//janela usada pelo servidor taskman para 
	//se comunicar com o kernel.
	struct window_d *taskmanWindow;     //server 
	struct window_d *taskmanClientWindow; //client
	
	//
	// Shell.
	//
	
	//
	// Janelas para o shell.
    // Obs: A janela do Shell será a janela do navegador.
	// Pois cada página de Internet será considerada um processo
	// e será exibida dentro da janela de cliente do shell.
	// Assim como as aplicações e janelas de diálogo do sistema, 
	// poderão ser exibidas dentro e fora da janela de cliente do shell.
	//
	struct window_d *shellWindow;      //server 
	struct window_d *shellClientWindow; //client
	
	
	//Informações sobre a tela.
	struct screen_d *ScreenInfo;
	
	// Backbuffer support. (espelho da memória de video)
	struct backbufferinfo_d  *backbufferInfo;  
	
	// Frontbuffer support. (memória de vídeo)
	struct frontbufferinfo_d *frontbufferInfo; 
	
    
	//
	// ## globais ##
	//
	
	struct desktop_d *CurrentDesktop;
	struct wstation_d *CurrentWindowStation;
	struct usession_d *CurrentUserSession;
	
	//Lista de informações sobre usuários.
    //@todo: Isso não precisa ficar aqui.	
	struct user_info_d *User; 	
	
	//...
};

// #importante
// Estrutura global. 
// (Usada para passar estutura entre funções)
// Primeira e única. 

struct gui_d *gui; 




//
// == Prototypes ===============================================
//



/*
 * SetGuiParameters:
 *     Configura a inicialização das janelas gerenciadas pelo kernel.
 *     @todo: Limite de janelas (+- 10)
 */

void SetGuiParameters( int refresh,         
                       int screen,          
                       int background,       
                       int logo,            
                       int taskbar,         
                       int main,             
                       int menu,            
                       int infobox,         
                       int messagebox,       
                       int debug,           
                       int navigationbar,    
                       int grid );

  
//
// Bars support. (menubar)
//

int 
UpdateStatusBar ( struct window_d *window, 
                  unsigned char *string1, 
		          unsigned char *string2 );

struct window_d *
StatusBar ( struct window_d *window, 
            unsigned char *string1, 
            unsigned char *string2 );

struct window_d *ToolBar ( struct window_d *window );


//
// menubar
//

void *create_menubar (struct window_d *pwindow); 

int create_menubar_item (struct menu_d *menu, unsigned char *string, int status);

int draw_menubar_item ( struct window_d *window, unsigned char *string);

//int select_menubar_item(struct menuitem_d *menuitem);


//int menubarX (void);
int kgws_create_menubar ( struct window_d *window);


//Color.
void set_up_color(unsigned long color);

void 
set_up_text_color( unsigned char forecolor, 
                   unsigned char backcolor );

void 
update_button (  struct button_d *button,
               unsigned char *string,
               int style,
               int state,
               int type,
               unsigned long x, 
               unsigned long y, 
               unsigned long width, 
               unsigned long height, 
               unsigned long color );


void *draw_button ( unsigned char *string,
                    int style,
                    int state,
                    int type, 
                    unsigned long x, 
                    unsigned long y, 
                    unsigned long width, 
                    unsigned long height, 
                    unsigned long color );


int redraw_button ( struct button_d *button );


int button_down ( struct window_d *window );

int button_up ( struct window_d *window );



// Focus support.

void SetFocus ( struct window_d *window );
void *GetFocus (void);                             
void KillFocus ( struct window_d *window );

//foreground window support

void *windowGetForegroundWindow (void);

int windowSetForegroundWindow(struct window_d *window);

//parent.
void *GetParentWindow(struct window_d * hwnd);

//desktop
void *GetWindowDesktop(struct window_d * hwnd);


// pegando ponteiros para estrutura de janela na estrutura 'gui->'.
// kgws.c

void *guiGetScreenWindow (void);

void *guiGetDeveloperScreenWindow (void);

void *guiGetBackgroundWindow (void);

void *guiGetLogoWindow (void);

void *guiGetDesktopWindow (void);

void *guiGetTaskbarWindow (void);

void *guiGetMainWindow (void);

void *guiGetStatusbarWindow (void);

void *guiGetGridWindow (void);

void *guiGetMenuWindow (void);

void *guiGetInfoboxWindow (void);

void *guiGetTooltipWindow (void);

void *guiGetMessageboxWindow (void);

void *guiGetDialogboxWindow (void);

void *guiGetDebugWindow (void);

// ?
void *guiGetMbhWindowWindow (void);

void *guiGetTopbarWindow (void);

void *guiGetNavigationbarWindow (void);

void *guiGetShellWindowWindow (void);

void *guiGetShellClientWindowWindow (void);


//
// Client Area.
//

void *getClientAreaRect (void);

void 
setClientAreaRect ( unsigned long x, 
                    unsigned long y, 
                    unsigned long cx, 
                    unsigned long cy );



// Background support.
void bg_load_image (void);
void backgroundDraw(unsigned long color);
void backgroundSetColor(unsigned long color);
void backgroundRedraw(unsigned long color);
void backgroundBackground (void);    
int backgroundInit (void);




//
// Char and String support.
//

void 
draw_string ( unsigned long x, 
              unsigned long y, 
              unsigned long color, 
              unsigned char *string );


void 
draw_text ( struct window_d *window,
            unsigned long x,  
            unsigned long y,  
            unsigned long color, 
            unsigned char *string );


void 
my_buffer_char_blt ( unsigned long x, 
                     unsigned long y, 
                     unsigned long color, 
                     unsigned long c);


void set_char_width( int width );
void set_char_height( int height );


int get_char_width (void);
int get_char_height (void);





// desenha um caractere transparente.
void 
d_drawchar_transparent ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long color, 
    unsigned long c);


// desenha um caractere.
void 
d_draw_char ( 
    unsigned long x, 
    unsigned long y,  
    unsigned long c,
    unsigned long fgcolor,
    unsigned long bgcolor);
 
 

//
// Pixel, line rect support.
//

//pega um pixel no backbuffer
unsigned long get_pixel( unsigned long x,  unsigned long y );


//envia um pixel do backbuffer para o frontbuffer
void refresh_pixel( unsigned long x,  unsigned long y );


void 
refresh_horizontal_line ( 
    unsigned long x1,
    unsigned long y, 
    unsigned long x2 );
  


// envia um retângulo do backbuffer para o frontbuffer
void 
refresh_rectangle ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height );


//envia um retângulo de um buffer para outro.
void 
refresh_rectangle2 ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height,
    unsigned long buffer1,
    unsigned long buffer2 );


//
// ## salvando retângulos ##
//

//a ideia é salvar os bytes usados por um retângulo que está no backbuffer 
//em um buffer do tamanho do retângulo.
//um buffer cosntante, suficientemente grande para salvar um retângulo do tamanho da 
//tela será alocado e gerenciado por uma estrutura.
//essa estrutura deverá registrar as dimensões e posicionamento do retângulo,
//e tamabém controlar o fluxo do transmissão do retângulo do backbuffer para esse buffer 
//e de volta para o backbuffer.
//isso será usado nas operações de movimentação de janela.
//múltiplos buffers poderãos ser usados no futuro. Principalmente para gerar eleito.

struct saved_rect_d
{
    void *buffer_address;

    unsigned long x;
    unsigned long y;
    unsigned long width;
    unsigned long height;

    int pixels;  //quantidade de pixels.
    int bytes;   //quantidade de bytes.
    int bpp;     //bytes per pixel.
	
	// O buffer está cheio. 
	// 1 retângulo foi salvo nele.

    int full;    
};
struct saved_rect_d *SavedRect;



int initialize_saved_rect (void);

// #testando ...
// Salvar um retângulo no buffer será semelhante ao 
// método de salvar um bmp em um arquivo.

int 
save_rect ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height );


//pintar no backbuffer o retângulo salvo vai ser semelhante ao processo 
//de decodificar um bmp, copiando do arquivo para o backbuffer.
// esses argumentos devem representar o posicionamentod esejado do 
//retângulo no backbuffer.

int 
show_saved_rect ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height );


//#todo: deprecated.
void scroll_screen_rect (void);



//
// ...
//




// Pinta um pixel em um buffer de janela.
void 
pixelPutPixelWindowBuffer ( 
    void *buffer, 
    unsigned long x, 
    unsigned long y, 
    unsigned long color );


  
/*
 * pixelPutPixelDedicatedWindowBuffer:
 *     Coloca um pixel no buffer da janela.
 *     Serve para pintar janelas que irão direto do seu buffer para 
 * o LFB da memória de vídeo, sem passar pelo back buffer. (OVERLAPPED)
 */

void 
pixelPutPixelDedicatedWindowBuffer ( 
    struct window_d *window, 
    unsigned long x, 
    unsigned long y, 
    unsigned long color ); 



//
// pixel
//


void 
backbuffer_putpixel( 
    unsigned long ax, 
    unsigned long bx, 
    unsigned long cx, 
    unsigned long dx );


void 
lfb_putpixel ( 
unsigned long ax, 
    unsigned long bx, 
    unsigned long cx, 
    unsigned long dx );

//
// line
//
 
void 
my_buffer_horizontal_line ( 
    unsigned long x1,
    unsigned long y, 
    unsigned long x2,  
    unsigned long color );


// rectangle.

void 
drawDataRectangle ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height, 
    unsigned long color );



void *rectStrCopyMemory32 ( 
    unsigned long *dest, 
    unsigned long *src, 
    int count ); 



//
// Window support.
// 
 
int init_window_manager (void);

int init_windows (void);

int RegisterWindow (struct window_d *window);

void set_current_window (struct window_d *window);
void *get_current_window (void);

//salva o retãngulo de uma janela no buffer de salvamento.
//isso será usado para mover a janela.
int save_window (struct window_d *window);

//mostrar uma janela que tem seu retãngulo salvo no buffer de salvamento.
//#obs: antes de chamarmos essa função podemos chamar a função replace_window
//para mudar a janela de lugar.
int show_saved_window (struct window_d *window);


//mostra o retãngulo de uma janela que está no backbuffer.
//tem uma janela no backbuffer e desejamos enviar ela para o frontbuffer.
int show_window_rect (struct window_d *window);


int 
resize_window ( 
    struct window_d *window, 
    unsigned long cx, 
    unsigned long cy );


int 
replace_window ( 
    struct window_d *window, 
    unsigned long x, 
    unsigned long y ); 


// coloca a janela acima das outras.
int raise_window ( struct window_d *window );

int redraw_window (struct window_d *window, unsigned long flags );

//redraw all windows.
int redraw_screen (void);                          

int is_window_full(struct window_d *window);
int is_window_maximized(struct window_d *window);
int is_window_minimized(struct window_d *window);

void set_active_window (struct window_d *window);
int get_active_window (void);

void change_active_window (int id);

void CloseWindow(struct window_d *window);

void DestroyWindow(struct window_d *window);

void CloseActiveWindow (void);

void MinimizeWindow (struct window_d *window);
void MaximizeWindow (struct window_d *window);

//
// Show
//

void windowShowWindowList (void);

void show_window_with_focus (void);

void show_active_window (void);

//
// z-order support.
//

int z_order_get_free_slot (void);

int get_zorder ( struct window_d *window );
struct window_d *getTopWindow (struct window_d *window);



//configurando a top window.

void set_top_window ( int id );
int get_top_window (void);

void closeActiveWindow (void);

//bloqueando e desbloqueando o foco.
void windowBlockFocus (void);
void windowUnblockFocus (void);

int windowGetMainWindowDescriptor (void);

int windowGetWindowID ( struct window_d *window);


//@todo: Criar windowRefreshScreen();

void windowSwitchFocus (void);

void windowLock (struct window_d *window);
void windowUnlock (struct window_d *window);

int windowCreateDedicatedBuffer (struct window_d *window);


// Envia mensagem para a fila da janela com foco de entrada.

void 
windowSendMessage ( 
    unsigned long arg1, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 );


//
// pega uma mensagem na estrutura da janela com o foco de entrada.
//

void *windowGetHandleWindow (struct window_d *window); 
void *windowGetMessage (struct window_d *window);
void *windowGetLong1 (struct window_d *window);
void *windowGetLong2 (struct window_d *window);


// Mostra o buffer de mensagens da janela com foco de entrada.

void windowShowWWFMessageBuffers (void); 


//color support.
void windowSetUpColorScheme (int type);
int windowSelectColorScheme ( int type );


void 
guiSetUpMainWindow ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height );


//
// timer
//

int windowKillTimer ( struct window_d *window, int id );

 
//janela
//id do timer
//tempo(medida indefinida ainda)
int
windowSetTimer ( 
    struct window_d *window, 
    int id, 
    int time );



// Escaneia as janelas existentes procurando uma 
// que contenha o posicionamento do cursor.
int windowScan ( unsigned long x, unsigned long y );

int windowOverLappedScan ( unsigned long x, unsigned long y );

//Envia uma mensagem PAINT para o aplicativo atualizar a área de trabalho.
void windowUpdateWindow ( struct window_d *window );



//faz a janela atual entrar ou sair do modo fullscreen.
int windowSwitchFullScreen (void);


int DrawIcon ( struct window_d *window, int n );

int 
DrawTitleBar ( 
    struct window_d *window,
    unsigned long x,
    unsigned long y,
    unsigned long width,
    unsigned long height,
    int style,
    char *string );


int 
DrawFrame ( 
    struct window_d *window,
    unsigned long x,
    unsigned long y,
    unsigned long width,
    unsigned long height,
    int style );


/*
 **********************************************
 * CreateWindow:
 *     Cria uma janela com base em um tipo.
 */

void *CreateWindow ( 
    unsigned long type,         //1 - tipo de janela (popup ..normal ...)
    unsigned long status,       //2  - estado da janela (ativa ou nao)
    unsigned long view,         //3  - (min, max ...)
    char *windowname,           //4  - titulo                                
    unsigned long x,            //5  - deslocamento em relação às margens do desktop(sua instancia)        
    unsigned long y,            //6  - idem
    unsigned long width,        //7  - largura da janela  
    unsigned long height,       //8  - altura
    struct window_d *pWindow,   //9  - id da janela mae, se for zero, essa é a janela mae.
    int desktopid,              //10 - desktop ID.
    unsigned long clientcolor,  //11 - Client Area Color.
    unsigned long color         //12 - cor do bg (para janelas simples, tipo 1)
);



// #todo: 
// Talvez deletar essa função e usar apenas CreateWindow.
void *kgws_create_window ( 
    unsigned long type, 
    unsigned long status, 
    unsigned long view, 
    char *windowname, 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height, 
    struct window_d *pWindow, 
    int desktopid, 
    unsigned long clientcolor, 
    unsigned long color );
 

// #todo: deprecated.
int scroll_client_window ( struct window_d *window );


//
// End.
//

