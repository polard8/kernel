// gws.h 


// Current protocol version
#define GWS_PROTOCOL  1



// ============================
// Modes.
#define GRAMADO_JAIL        0x00
#define GRAMADO_P1          0x01
#define GRAMADO_HOME        0x02
#define GRAMADO_P2          0x03
#define GRAMADO_CASTLE      0x04
#define GRAMADO_CALIFORNIA  0x05
// ...
int current_mode;




// rtl
#include <types.h>
#include <sys/types.h>
#include <sys/cdefs.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <rtl/gramado.h>

 
#include "globals.h"

//
// view
//

#include "r_render.h"
#include "colors.h"
#include "bitblt.h"
#include "char.h"
#include "dtext.h"
#include "line.h"
#include "vk.h"       // # view input events
#include "wt.h"
#include "menu.h"
#include "xxxinput.h"   //#test
#include "window.h"
#include "bmp.h"
// h:0.0
#include "screen.h"   // X-like
#include "display.h"  // X-like
#include "host.h"     // X-like h:0.0
// Teremos isso aqui no window server,
// kgws é outro ws par ao ambiente de setup e tera 
// seu próprio gerenciamento.
#include "security.h"
#include "gui.h"
#include "comp.h"
#include "event.h"    // view inputs
#include "grprim.h"
#include "sprite.h"
#include "demos.h"


//
// model
//

// # data model
#include "packet.h"
// # model. business logic
// #todo:
// We can put this thing in the library. (libgws)
// or (libcon)
#include "connect.h"
#include "nc2.h"   //nelson cole 2 font. 8x8
#include "lt8x8.h"
#include "font.h"
// Client structure.
// O proprio servidor poderia ser o cliente 0??
#include "client.h"
// # model. business logic
#include "services.h"


struct gws_graphics_d
{
    int used;
    int magic;
    
    struct gui_d  *gui;

    // ...
};
struct gws_graphics_d *Currentgraphics;


struct engine_d
{
    // flag: When to quit the engine.
    // We can quit the engine and reinitialize it again.
    int quit;
    
    // engine status
    int status;


    // graphics support.
    struct gws_graphics_d *graphics;

    // ...

};
struct engine_d Engine;


//
// MAIN STRUCTURE
//

// This is the main data structure for the window server.

struct gws_d 
{

    // The name of the window server.
    char name[64];
    char edition_name[64];

    char version_string[16];

    unsigned long version_major;
    unsigned long version_minor;

    // fd
    int socket;

    // flag: When to quit the window server.
    int quit;

 
    // window server status
    int status;

    // sinaliza que registramos o servidor no sistema.
    int registration_status;
    int graphics_initialization_status;
    // ...
    
    // Se devemos ou não lançar o primeiro cliente.
    int launch_first_client;

    // graphics engine 

    struct engine_d *engine;
    
    // os info.
    
    // input support
    
    // ...
};

// GWS - Gramado Window Server
struct gws_d *gws;


//
// =============================================================
//


void invalidate(void);
void validate(void);
int isdirty(void);


void invalidate_background(void);
void validate_background(void);
int is_background_dirty(void);


// #test
// from x window system.
// #todo: move these to window.h
//struct gws_window_d *keyboard_window;
//struct gws_window_d *mouse_window;
//struct gws_window_d *cursor_window;  // Where cursor came from.
//struct gws_window_d *button_window;  // Where button was pressed.


void gwssrv_set_keyboard_focus(int window);


//
// == buffer ===============================================
//

// O buffer para  as mensagens recebidas via socket.
#define MSG_BUFFER_SIZE 512
char __buffer[MSG_BUFFER_SIZE];   

// Esses valores serão enviados como 
// resposta ao serviço atual.
// Eles são configurados pelo dialogo na hora da 
// prestação do serviço.
// No início desse array fica o header.
#define NEXTRESPONSE_BUFFER_SIZE  32
unsigned long next_response[32];




void xxxThread (void);
void ____test_threads (void);


void *gwssrv_create_thread ( 
    unsigned long init_eip, 
    unsigned long init_stack, 
    char *name );

void gwssrv_start_thread (void *thread);


// Drain input
int service_drain_input (void);


void gwssrv_debug_print (char *string);

int gwssrv_clone_and_execute ( char *name );
unsigned long gwssrv_get_system_metrics (int index);


void gwssrv_enter_critical_section (void);
void gwssrv_exit_critical_section (void);

void gwssrv_show_backbuffer (void);


char *gwssrv_get_version(void);


// init
int gwsInit(void);

unsigned long gws_get_device_width(void);
unsigned long gws_get_device_height(void);

// Função padrão para todos os servidores ???
// #todo: temos que criar isso.
int serverInit (void);


void gws_show_backbuffer(void);

int gwssrv_init_globals(void);

void gwssrv_wait_message(void);

void gwssrv_yield(void);

void serviceExitGWS(void);

//
// End.
//


