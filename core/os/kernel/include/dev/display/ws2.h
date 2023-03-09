
// ws2.h
// Window system support.
// ring0, kernel base.
// #todo
// Tem muita coisa aqui nesse documento para ser deletado.
// Que era de quando existia gui dentro do kernel.
// Talvez alguma coisa sobre janela seja preservado,
// pois vamos dar suporte ao conceito de 'surfaces',
// que serao areas de memoria compartilhadas entre o painter-client side 
// e o compositor, server-side. 

#ifndef __DISPLAY_WS2_H
#define __DISPLAY_WS2_H    1

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
#define MSG_SYSCOMMAND  MSG_COMMAND

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

#define MSG_HOTKEY  8888


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

// Invalidate
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

//--------------------------------------

// Isso pode ser útil principalmente
// para passar um retângulo de um ambiente para outro.
// É muito mais didático que a figura do retângulo como objeto.
struct surface_d
{
    int used;
    int magic;
// Surface ID.
    int surface_id;
    struct rect_d rect;
// How many bytes?
    size_t size_in_bytes;
    int bpp;
    unsigned long width;
    unsigned long pitch;
    unsigned long height;

// Window ID.
// This window owns this surface.
// The wid provided by the window server.
    int owner_wid;

    int dirty;

    struct surface_d *next;
};

//--------------------------------------
// Ponteiros para ícones
// Ponteiros para o endereço onde os ícones 
// foram carregados.
// queremos saber se o endereço alocado eh compartilhado ...
// para o window server usar ... entao chamaremos de sharedbufferIcon.
// see: kgwm.c

// Icon cache structure.
// see: kgwm.c
struct icon_cache_d
{
    int initialized;
    size_t size_in_bytes;
// Pointers to shared memory.
    void *app;  //1
    void *file; 
    void *folder;
    void *terminal;
    void *cursor;  //5
};
extern struct icon_cache_d  icon_cache;


// gui:
// 2015 - Created by Fred Nora.
struct gui_d
{
    int initialized;

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


// see: bitblt.c
int 
bitblt(
    struct rect_d *src_rect,
    struct rect_d *dst_rect,
    unsigned long rop );

//
// == wm =====================
//

void exit_kernel_console(void);
void kgwm_early_kernel_console(void);

// ==========
int 
wmProcedure ( 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );

#endif    

