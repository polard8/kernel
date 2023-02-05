
// window.h
// ring0, kernel base.
// #todo
// Tem muita coisa aqui nesse documento para ser deletado.
// Que era de quando existia gui dentro do kernel.
// Talvez alguma coisa sobre janela seja preservado,
// pois vamos dar suporte ao conceito de 'surfaces',
// que serao areas de memoria compartilhadas entre o painter-client side 
// e o compositor, server-side. 

#ifndef  __WINDOW_H
#define  __WINDOW_H    1


#define KGWS_ZORDER_BOTTOM   0 
#define KGWS_ZORDER_TOP     1023   //top window
#define KGWS_ZORDER_MAX     1024   //max


// #importante:
// Tipos de mensagem de comunicação nos diálogos 
// e procesimento de janelas:
// 
// SIGNAL_       Sinal. Não contém argumentos.
// MSG_          Message. Contém os argumentos padrão.
// STREAMMSG_    Streams. O argumento é um ponteiro para uma stream.
// BUFFER_MSG_   Buffer. O argumento é um ponteiro para um buffer.
// CAT_MSG_      Concatenate. Os argumentos long1 e long devem ser concatenados.
 

// Window handle status
// Se uma janela está aberta ou não. 
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


//
// Message code.
//

#define MSG_NULL  0 
 
// Window (1-19)  
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

// mouse (30 - 39)
#define MSG_MOUSEKEYDOWN     30
#define MSG_MOUSEKEYUP       31
#define MSG_MOUSEBUTTONDOWN  30
#define MSG_MOUSEBUTTONUP    31 
#define MSG_MOUSEMOVE        32
#define MSG_MOUSEOVER        33
#define MSG_MOUSEWHEEL       34
#define MSG_MOUSEPRESSED     35
#define MSG_MOUSERELEASED    36
#define MSG_MOUSECLICKED     37
#define MSG_MOUSEENTERED     38    //?? capturou ??
#define MSG_MOUSEEXITED      39   //?? descapturou ??
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

#define MSG_TERMINAL_COMMAND  49
#define MSG_TERMINAL_SHUTDOWN  50
#define MSG_TERMINAL_REBOOT   51

#define MSG_DEVELOPER  52

// UM TIMER SE ESGOTOU,
#define MSG_TIMER  53
//...

// O servidor de rede se comunica com o processo.
#define MSG_AF_INET  54
#define MSG_NET_DATA_IN  55

// O driver de network está notificando um processo em ring3.
#define MSG_NETWORK_NOTIFY_PROCESS  56

// mouse support: continuação ...
#define MSG_MOUSE_DOUBLECLICKED   60
#define MSG_MOUSE_DRAG            61
#define MSG_MOUSE_DROP            62
//...

// #test
// seleciona todos os elementos.
// control+a
#define MSG_SELECT_ALL    70
// control+f
#define MSG_SEARCH    71
#define MSG_FIND      71 

// control+s
#define MSG_SAVE    72

#define MSG_CONTROL_ARROW_UP     80
#define MSG_CONTROL_ARROW_DOWN   81
#define MSG_CONTROL_ARROW_LEFT   82
#define MSG_CONTROL_ARROW_RIGHT  83

//  terminal commands
#define MSG_TERMINALCOMMAND      100
#define TERMINALCOMMAND_PRINTCHAR 1000
//#define TERMINALCOMMAND_PRINT??? 1001
//...

// o evento de rolagem aconteceu ...
// O número do evento será entregue em long1.
#define MSG_HSCROLL  2000
#define MSG_VSCROLL  2001

// 
// Window type
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
#define WINDOW_STYLE_FLOATING  1000
#define WINDOW_STYLE_DOCKING   2000
//...

// Window status
#define WINDOW_STATUS_ACTIVE       1
#define WINDOW_STATUS_INACTIVE     0
//...

/*
 * rect_d:
 *     Estrutura para gerenciamento de retângulos.
 *     Um retângulo pertence à uma janela.
 */
// #todo
// Usar isso para lidar com dirty rectangles.

struct rect_d 
{
    object_type_t  objectType;
    object_class_t objectClass;

    int used;
    int magic;

//
// Invalidate
//

// Sujo de tinta.
// If the rectangle is dirty, so it needs to be flushed into 
// the framebuffer.
// When we draw a window it needs to be invalidated.
    int dirty;
    int flag;
// Estilo de design
    int style;

//dimensoes
    unsigned long x;
    unsigned long y;
    unsigned long cx;
    unsigned long cy;

//margins
    unsigned long left;
    unsigned long top;
    unsigned long width;
    unsigned long height;

    unsigned long right;
    unsigned long bottom;

    // 32 bit
    unsigned int bg_color; 

    struct rect_d *next;
};

// Isso pode ser útil principalmente
// para passar um retângulo de um ambiente para outro.
// É muito mais didático que a figura do retângulo como objeto.
struct surface_d
{
    int used;
    int magic;
    int dirty;
    struct rect_d *rect;
    
    struct surface_d *next;
};

/* rgba */
struct tagRGBA
{
    object_type_t  objectType;
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

// estrutura para window class
struct window_class_d
{

//Que tipo de window class.
// do sistema, dos processos ...
//tipo de classe.

	wc_t windowClass; 

//1
    client_window_classes_t	clientClass;
//2
	kernel_window_classes_t kernelClass;
//3
	server_window_classes_t serverClass;
//Endereço do procedimento de janela.
//(eip da thread primcipal do app)
	unsigned long procedure;
    //...
};

// Message structure.
struct msg_d 
{

// validation
    int used;
    int magic;
// standard header
    struct window_d *window;  //#opaque
    int msg;
    unsigned long long1;
    unsigned long long2;
// extra payload
    unsigned long long3;
    unsigned long long4;

// extention

    pid_t sender_pid;
    pid_t receiver_pid;

    tid_t sender_tid;
    tid_t receiver_tid;
    // ...
    
    //unsigned long jiffie1;
    //unsigned long jiffie2;

// #todo
// We need some synchronization flags.
// Maybe its better putting this flag into the thread struct.
// t->msg_flags;
    //unsigned long flags;

// navigation?
    struct msg_d *next;
};


// #deprecated
struct window_d
{
    int dummy_deprecated;
    //int used;
    //int magic;
};

// #maybe
//struct window_d *kernel_surface_window;

// Window list.
unsigned long windowList[WINDOW_COUNT_MAX];

// ??
unsigned long Windows[KGWS_ZORDER_MAX];

// id da janela que o mouse está em cima.
int window_mouse_over; 

//--------------------------------------
// Ponteiros para ícones
// Ponteiros para o endereço onde os ícones 
// foram carregados.
// queremos saber se o endereço alocado eh compartilhado ...
// para o window server usar ... entao chamaremos de sharedbufferIcon.
// see: kgwm.c

extern void *shared_buffer_app_icon;  //1
extern void *shared_buffer_file_icon; 
extern void *shared_buffer_folder_icon;
extern void *shared_buffer_terminal_icon;
extern void *shared_buffer_cursor_icon;
// ... 

//
// == z order support =========================
//

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

// Estrutura para controlar um índice de janela 
// ponteiros de instãncias dessa estrutura ficarão na lista zorderList[].
// Obs: uma estrutura de janela pode ter um poteiro para essa 
// estrutura que controlará todas as propriedades de zorder relaticas a aquela janela.
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


//see:  kgwm.c
extern int zorder;
extern int zorderCounter;         //contador de janelas incluidas nessa lista.   
extern int zorderTopWindow;
//...


// gui:
// 2015 - Created by Fred Nora.

struct gui_d
{
    int initialised;

// redraw
// Flag para repintar todas as janelas.
// #todo: #bugbug, Isso parece estranho. Cada janela
// está pintada em seu buffer dedicado e fica por conta de
// cada janela decidir se repinta ou não apenas ela.

    int redraw;

// refresh
// Flag para enviar do backbuffer para a memória de video.
// Seguindo uma lista linkada, copiaremos o conteúdo do buffer
// dedicado de cada janela da lista no LFB. Primeiro é Backbuffer
// que é o buffer da janela principal, que funcionará como
// Head da lista.

    int refresh;

// Security
    struct usession_d  *CurrentUserSession;
    struct room_d        *CurrentRoom;  // (Window station)
    struct desktop_d   *CurrentDesktop;
};

extern struct gui_d  *gui; 


//
// == prototypes ================
//

//
// pixel
//

void 
putpixel0 ( 
    unsigned int  _color,
    unsigned long _x, 
    unsigned long _y, 
    unsigned long _rop_flags,
    unsigned long buffer_va );

void 
backbuffer_putpixel ( 
    unsigned int  _color,
    unsigned long _x, 
    unsigned long _y, 
    unsigned long _rop_flags );

void 
frontbuffer_putpixel ( 
    unsigned int  _color,
    unsigned long _x, 
    unsigned long _y, 
    unsigned long _rop_flags );

//
// char
//

void set_char_width ( int width );
void set_char_height (int height);
int get_char_width (void);
int get_char_height (void);

void 
d_draw_char ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long c,
    unsigned int fgcolor,
    unsigned int bgcolor );

void 
d_drawchar_transparent ( 
    unsigned long x, 
    unsigned long y, 
    unsigned int color, 
    unsigned long c );

//
// string
//    

void 
draw_string ( 
    unsigned long x,
    unsigned long y,
    unsigned int color,
    char *string ); 

// Early panic function.
// Print a panic message in the early stages.
void x_panic(char *string);

//
// line
//

void 
backbuffer_draw_horizontal_line ( 
    unsigned long x1,
    unsigned long y, 
    unsigned long x2, 
    unsigned int color,
    unsigned long rop_flags );

void 
frontbuffer_draw_horizontal_line ( 
    unsigned long x1,
    unsigned long y, 
    unsigned long x2, 
    unsigned int color,
    unsigned long rop_flags );

//
// Draw rectangle into the backbuffer.
//

void 
backbuffer_draw_rectangle( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height, 
    unsigned int color,
    unsigned long rop_flags );

void 
frontbuffer_draw_rectangle( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height, 
    unsigned int color,
    unsigned long rop_flags );

void 
refresh_rectangle ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height );

void scroll_screen_rect (void);

//
// == wm =====================
//

// See: kgwm.c
void 
wmRegisterWSCallbacks(
    unsigned long callback0,
    unsigned long callback1,
    unsigned long callback2 );

// Send input to the window manager
// inside the window server
// gwssrv.bin
unsigned long wmSendInputToWindowManager(
    unsigned long wid,
    unsigned long msg,
    unsigned long long1,
    unsigned long long2);

void exit_kernel_console(void);
void kgwm_early_kernel_console(void);

// ==========

// Input events:

int 
wmKeyEvent(
    unsigned char raw_byte,
    int prefix );

int wmMouseEvent(int event_id,long long1, long long2);

#endif    

