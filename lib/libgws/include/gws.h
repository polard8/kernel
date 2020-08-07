/*
 * File: gws.h 
 * 
 *     Client-side library for Gramado Window Server. 
 * 
 * History:
 *     2020 -  Created by Fred Nora.
 */



// Virtual keys.
#include "vk.h"

// Window Messages.
#include "wm.h"

// Window types.
#include "wt.h"

// Colors.
#include "colours.h"

// Windows.
#include "window.h"

// Events.
#include "events.h"


// Connecting with the ws.
//#include "connect.h"


#include "gws_pack.h"


// Read and write from socket.
#include "rw.h"

// ...


//
// ==== Version ====
//


#define GWS_LIB_PROTOCOL           0
#define GWS_LIB_PROTOCOL_REVISION  1


struct libgws_version_d
{
    unsigned long majorVersion;
    unsigned long minorVersion;
    // ...
};
// Version struct.
struct libgws_version_d libgwsVersion;


struct gws_keyboard_event_d
{
    int dummy;
};

struct gws_mouse_event_d
{
    int dummy;
};


struct gws_window_event_d
{
    int dummy;
};


struct gws_event_d
{

    //standard msg block
    int wid;    // window id.
    int msg;   // msg. (event type).
    unsigned long long1;
    unsigned long long2;

    // extra
    //unsigned long long3;
    //unsigned long long4;
    //unsigned long long5;
    //unsigned long long6;
    
    
    
    struct gws_keyboard_event_d kEvent;
    struct gws_mouse_event_d    mEvent;
    struct gws_window_event_d   wEvent;
    // ...
    
    struct gws_event_d *next;
};
struct gws_event_d *CurrentEvent;



struct gws_screen_d
{
    int id;
    int used;
    int magic;
    
    unsigned long width;
    unsigned long height;
    //bpp?

    unsigned long font_size;

    unsigned long char_width; 
    unsigned long char_height;
    
    void *backbuffer;
    void *frontbuffer;

    // Belongs to this display.
    struct gws_display_d *display;

    struct gws_screen_d *next;
};



struct gws_display_d
{
    int id;
    
    int used;
    int magic;

    // #test
    //"host:display" string used on this connect
    char *display_name;
    
    int fd;    // Network socket. 
    int lock;  // is someone in critical section?  
 
    //#test
    //char *buffer;		//Output buffer starting address. 
    //char *bufptr;		//Output buffer index pointer. 
    //char *bufmax;		//Output buffer maximum+1 address. 
    
    //#test
    //only one screen for now.
    //struct gws_screen_d *screen;
    

    
    
    //...

    struct gws_display_d *next;
};







//
// =============== TOP ========================
//


// #todo
// Na parte mais baixa desse documento devem ficar as abstraçẽos.
// Elas serão as rotinas de mais alto nível e devem começar com gws_


// System call.

void *
gws_system_call ( 
    unsigned long a, 
    unsigned long b, 
    unsigned long c, 
    unsigned long d );


void gws_debug_print (char *string);


// Initialize the library.
int gws_initialize_library (void);


// Services.
// IN: service number, ...

void *
gws_services ( 
    int service,
    unsigned long arg2,
    unsigned long arg3,
    unsigned long arg4 );



// Send message to a process.                     
int
gws_send_message_to_process ( 
    int pid, 
    int window, 
    int message,
    unsigned long long1,
    unsigned long long2 );


// Send message to a thread.
int 
gws_send_message_to_thread ( 
    int tid, 
    int window, 
    int message,
    unsigned long long1,
    unsigned long long2 ); 



//draw a char
int 
gws_draw_char (
    int fd, 
    int window,
    unsigned long x,
    unsigned long y,
    unsigned long color,
    unsigned long c );
    
int 
gws_draw_text (
    int fd, 
    int window,
    unsigned long x,
    unsigned long y,
    unsigned long color,
    char *string );


int gws_refresh_window (int fd, int window );

// Talvez vamos retonar o descritor
// dado pelo servidor.

int
gws_create_window ( 
    int fd,
    unsigned long type,        //1, Tipo de janela (popup,normal,...)
    unsigned long status,      //2, Estado da janela (ativa ou nao)
    unsigned long view,        //3, (min, max ...)
    char *windowname,          //4, Título.                          
    unsigned long x,           //5, Deslocamento em relação às margens do Desktop.                           
    unsigned long y,           //6, Deslocamento em relação às margens do Desktop.
    unsigned long width,       //7, Largura da janela.
    unsigned long height,      //8, Altura da janela.
    int parentwindow,          //9, Endereço da estrutura da janela mãe.
    unsigned long onde,        //10, Ambiente.( Está no desktop, barra, cliente ...)
    unsigned long clientcolor, //11, Cor da área de cliente
    unsigned long color );     //12, Color (bg) (para janela simples).


int
gws_create_window_using_socket (
    int fd, 
    unsigned long type,        //1, Tipo de janela (popup,normal,...)
    unsigned long status,      //2, Estado da janela (ativa ou nao)
    unsigned long view,        //3, (min, max ...)
    char *windowname,          //4, Título.                          
    unsigned long x,           //5, Deslocamento em relação às margens do Desktop.                           
    unsigned long y,           //6, Deslocamento em relação às margens do Desktop.
    unsigned long width,       //7, Largura da janela.
    unsigned long height,      //8, Altura da janela.
    int parentwindow,  //9, Endereço da estrutura da janela mãe.
    unsigned long onde,        //10, Ambiente.( Est� no desktop, barra, cliente ...)
    unsigned long clientcolor, //11, Cor da área de cliente
    unsigned long color );     //12, Color (bg) (para janela simples).


// #bugbug:
// Nessa biblioteca devem ficar apenas as rotinas
// Que lidam com o window server.
void gws_reboot (void);

void gws_yield(void);

int gws_clone_and_execute ( char *name );

unsigned long gws_get_system_metrics (int index);

// Get next event
struct gws_event_d *gws_next_system_message(void);

void gws_enter_critical_section();
void gws_exit_critical_section();




//
// End.
//






