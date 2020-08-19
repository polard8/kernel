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

//h:d.s
#include "screen.h"
#include "display.h"
#include "host.h"



#include "menu.h"


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



int 
gws_redraw_window(int fd, int window, unsigned long flags);


int gws_refresh_window (int fd, int window );

int gws_change_window_position (int fd, int window, unsigned long x, unsigned long y );
int 
gws_resize_window( 
    int fd, 
    int window, 
    unsigned long w, 
    unsigned long h );

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

void gws_enter_critical_section(void);
void gws_exit_critical_section(void);


//menu
struct gws_menu_d *gws_create_menu (
    int fd,
    int parent,
    int highlight,
    int count,
    unsigned long x,
    unsigned long y,
    unsigned long width,
    unsigned long height,
    unsigned long color );

//menu item
struct gws_menu_item_d *gws_create_menu_item (
    int fd,
    char *label,
    int id,
    struct gws_menu_d *menu);


// get next event.
// the window server return the next event
// from the queue of a client.
struct gws_event_d *gws_next_event(int fd);




// Send event.
// It is gonna be used by the window manager to send 
// events to the window server.
// Remember: The window manager gets the system messages
// end sends window events to the window server.
void 
gws_send_event ( 
    int fd, 
    int window, 
    struct gws_event_d *event );


//
// End.
//






