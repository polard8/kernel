/*
 * File: gws.h 
 *     Client-side library for Gramado Window Server. 
 * History:
 *     2020 -  Created by Fred Nora.
 */

typedef int  __wid_t;
typedef int wid_t;


// internal
// used only by the lib
#define __PORTS_WS  4040
#define __PORTS_NS  4041
#define __PORTS_FS  4042
// ...

#define __IP(a, b, c, d) (a << 24 | b << 16 | c << 8 | d)

#include "protocol.h"

//
// window
//

// Virtual keys.
#include "window/vk.h"
// Window Messages.
#include "window/wm.h"
// Window types.
#include "window/wt.h"
// Colors.
#include "window/colors.h"
// Windows.
#include "window/window.h"

//
// host
//

//h:d.s
#include "host/screen.h"
#include "host/display.h"
#include "host/host.h"


#include "ports.h"

// menu
#include "window/menu.h"

// Events
#include "io/events.h"


// Connecting with the ws.
//#include "connect.h"

#include "gws_pack.h"

// Read and write from socket.
#include "io/rw.h"

// Client-side 3D graphics support.
#include "gr/gr.h"

// ...

//
// == Version ====
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
//struct libgws_version_d libgwsVersion;

// See: gws.c
extern struct libgws_version_d libgwsVersion;

//
// == TOP ========================
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

void *gws_malloc(size_t size);
void gws_free(void *ptr);

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
// == 2d ==============================================
//

// Draw a char.
int 
gws_draw_char (
    int fd, 
    int window,
    unsigned long x,
    unsigned long y,
    unsigned int color,
    unsigned int ch );

// Draw a text.
int 
gws_draw_text (
    int fd, 
    int window,
    unsigned long x,
    unsigned long y,
    unsigned int color,
    char *string );

int 
gws_set_text (
    int fd, 
    int window,
    unsigned long x,
    unsigned long y,
    unsigned int color,
    char *string );

int 
gws_get_text (
    int fd, 
    int window,
    unsigned long x,
    unsigned long y,
    unsigned int color,
    char *string );


// Redraw a window.
int 
gws_redraw_window (
    int fd, 
    int window, 
    unsigned long flags );

// The server will return the info about one given window.
struct gws_window_info_d *gws_query_window(
    int fd,
    int wid,
    struct gws_window_info_d *window_info );

// The server will return the info about one given window.
struct gws_window_info_d *gws_get_window_info(
    int fd,
    int wid,
    struct gws_window_info_d *window_info );

// The server will return an event from the its client's event queue.
struct gws_event_d *
gws_get_next_event(
    int fd, 
    int wid,
    struct gws_event_d *event );

// Refresh a window.
int gws_refresh_window (int fd, wid_t wid );

int
gws_refresh_retangle ( 
    int fd,
    unsigned long left, 
    unsigned long top, 
    unsigned long width, 
    unsigned long height );

// Change window position.
int 
gws_change_window_position (
    int fd, 
    int window, 
    unsigned long x, 
    unsigned long y );

// Resize a window.
int 
gws_resize_window ( 
    int fd, 
    int window, 
    unsigned long w, 
    unsigned long h );

// Atualiza o retângulo da surface da thread.
void 
setup_surface_retangle ( 
    unsigned long left, 
    unsigned long top, 
    unsigned long width, 
    unsigned long height );

// #todo: 
// change to gws_invalidate_surface_rectangle,
// or gws_invalidate-surface.
void invalidate_surface_retangle (void);

void gws_invalidate_window(int fd,int wid);

// Create a window.
wid_t
gws_create_window ( 
    int fd,
    unsigned long type,        //1, Tipo de janela (popup,normal,...)
    unsigned long status,      //2, Estado da janela (ativa ou nao)
    unsigned long view,        //3, (min, max ...)
    char *windowname,          //4, Título. #todo maybe const char.
    unsigned long x,           //5, Deslocamento em relação às margens do Desktop. 
    unsigned long y,           //6, Deslocamento em relação às margens do Desktop.
    unsigned long width,       //7, Largura da janela.
    unsigned long height,      //8, Altura da janela.
    int parentwindow,          //9, Endereço da estrutura da janela mãe.
    unsigned long style,       //10, Ambiente.( Está no desktop, barra, cliente ...)
    unsigned int clientcolor,  //11, Cor da área de cliente
    unsigned int color );      //12, Color (bg) (para janela simples).

void gws_reboot(int fd);
void gws_shutdown(int fd);
void gws_update_desktop(int fd);
// #test 
// Load a file given a path.
// We are testing the path support.
int 
gws_load_path ( 
    char *path, 
    unsigned long buffer, 
    unsigned long buffer_len );

// Yield the current thread.
void gws_yield(void);
// Refresh the background and yield the current thread.
void gws_refresh_yield (int fd);
// Refresh a given window and yield the current thread.
void gws_refresh_yield2 (int fd, int window);
// Yield the current thread n times.
void gws_yield_n_times (unsigned long n);

void *gws_create_thread ( 
    unsigned long init_eip, 
    unsigned long init_stack, 
    char *name );

void gws_start_thread (void *thread);

int gws_clone_and_execute ( char *name );

//#todo: change arguments.
int 
gws_clone_and_execute2 (
    int fd, 
    unsigned long arg1,
    unsigned long arg2,
    unsigned long arg3,
    unsigned long arg4,
    char *string );

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
    unsigned int color );

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

unsigned int gws_explode_byte_32 (unsigned char data);

void
gws_async_command ( 
    int fd, 
    unsigned long request,
    unsigned long sub_request,
    unsigned long data );

void
gws_async_command2 ( 
    int fd, 
    unsigned long request,
    unsigned long sub_request,
    unsigned long data1,
    unsigned long data2,
    unsigned long data3,
    unsigned long data4 );


void gws_destroy_window(int fd, wid_t wid);
void gws_set_active(int fd, wid_t wid);
void gws_set_focus(int fd, wid_t wid);
void gws_clear_window(int fd, wid_t wid);

void gws_send_wm_magic( int fd, int pid );

// ==========================

// Application
int application_start(void);
void application_end(void);
// ==========================

int gws_enable_input_method(int method);

int 
gws_default_procedure ( 
    int fd,
    int window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );

//
// End
//

