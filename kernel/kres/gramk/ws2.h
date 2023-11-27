
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
    struct usession_d  *user_session;
    struct zing_hook_d   *zing_hook;
};
extern struct gui_d  *gui; 


//
// == prototypes ================
//

//
// pixel
//


int 
backbuffer_putpixel ( 
    unsigned int  _color,
    unsigned long _x, 
    unsigned long _y, 
    unsigned long _rop_flags );

int 
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

int 
backbuffer_draw_horizontal_line ( 
    unsigned long x1,
    unsigned long y, 
    unsigned long x2, 
    unsigned int color,
    unsigned long rop_flags );

int 
frontbuffer_draw_horizontal_line ( 
    unsigned long x1,
    unsigned long y, 
    unsigned long x2, 
    unsigned int color,
    unsigned long rop_flags );

// Draw rectangle into the backbuffer.
int 
backbuffer_draw_rectangle( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height, 
    unsigned int color,
    unsigned long rop_flags );

int 
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

// See: input.c
void enter_kernel_console(void);
void exit_kernel_console(void);

// ==========

#endif    

