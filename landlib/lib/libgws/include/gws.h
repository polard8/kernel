/*
 * File: gws.h 
 * 
 *     Client-side library for Gramado Window Server. 
 * 
 * History:
 *     2020 -  Created by Fred Nora.
 */



// =======================================
// Protocol request constants
//
// #todo:
// Create a consistent interface.
// See: xxxHandleNextClientRequest() and gwsProcedure on aurora/server/main.c 
// See: 
// All the standar messages, just like MSG_SYSKEYUP ...
// There are some old messages below 369.
#define GWS_GetInputMessage        369
#define GWS_Hello                 1000
#define GWS_CreateWindow          1001
#define GWS_BackbufferPutPixel    1002
#define GWS_DrawHorizontalLine    1003
#define GWS_DrawChar              1004
#define GWS_DrawText              1005
#define GWS_RefreshWindow         1006
#define GWS_RedrawWindow          1007
#define GWS_ResizeWindow          1008
#define GWS_ChangeWindowPosition  1009
#define GWS_BackbufferPutPixel2   2000
#define GWS_Disconnect            2010
#define GWS_RefreshScreen         2020
#define GWS_RefreshRectangle      2021
//#define GWS_GetSendEvent          2030  // send event #
#define GWS_GetNextEvent          2031
#define GWS_GrPlot0               2040
#define GWS_GrCubeZ               2041
#define GWS_GrRectangle           2042
#define GWS_AsyncCommand          2222
#define GWS_DrainInput            8080
// ...


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


#include "ports.h"


#include "menu.h"


// Events.
#include "events.h"


// Connecting with the ws.
//#include "connect.h"


#include "gws_pack.h"


// Read and write from socket.
#include "rw.h"


// 3d graphics support.
#include "gr.h"

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

void *gws_system_call ( 
    unsigned long a, 
    unsigned long b, 
    unsigned long c, 
    unsigned long d );


void gws_debug_print (char *string);


// Initialize the library.
int gws_initialize_library (void);


// Services.
// Dialog with the library
// IN: service number, ...

void *gws_services ( 
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



//
// == 3d ==============================================
//

//test
//plot a point
int 
gws_plot0 (
    int fd,
    unsigned long x,
    unsigned long y,
    unsigned long z,
    unsigned long color );



int 
gws_plotcube (
    int fd,
    struct gr_cube_d *cube );




//plot rectangle
int 
gws_plotrectangle (
    int fd,
    struct gr_rectangle_d *rect );
    
    
    
// ...


//
// == 2d ==============================================
//

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
gws_redraw_window (
    int fd, 
    int window, 
    unsigned long flags );


int gws_refresh_window (int fd, int window );

int 
gws_change_window_position (
    int fd, 
    int window, 
    unsigned long x, 
    unsigned long y );

int 
gws_resize_window ( 
    int fd, 
    int window, 
    unsigned long w, 
    unsigned long h );



/*
 *********************************** 
 * gws_create_window:
 * 
 */

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


void gws_reboot (void);


int 
gws_load_path ( 
    char *path, 
    unsigned long buffer, 
    unsigned long buffer_len );


void gws_yield(void);

// refresh the background and yield the current thread
void gws_refresh_yield (int fd);


// refresh a given window and yield the current thread
void gws_refresh_yield2 (int fd, int window);


void gws_yield_n_times (unsigned long n);


//
// payment
//

void gws_payment(void);




void *gws_create_thread ( 
    unsigned long init_eip, 
    unsigned long init_stack, 
    char *name );

void gws_start_thread (void *thread);

int gws_clone_and_execute ( char *name );

unsigned long gws_get_system_metrics (int index);


void gws_enter_critical_section(void);
void gws_exit_critical_section(void);

int gws_create_empty_file ( char *file_name );
int gws_create_empty_directory ( char *dir_name );


// menu
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
struct gws_event_d *gws_next_event (int fd);


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


unsigned long gws_explode_byte (unsigned char data);


void
gws_async_command ( 
    int fd, 
    unsigned long request);

//
// End.
//





