
// gwsint.h 
// Internal definitions for Gramado Window Server.

// ...
extern int current_mode;

// rtl
#include <types.h>
#include <sys/types.h>
#include <sys/cdefs.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <rtl/gramado.h>


// Gramado Window Server
#include "gws.h"
#include "callback.h"

// Configuration and debug support.
#include "config/config.h"
#include "protocol.h"
#include "globals.h"
#include "colors.h"
//#include "nc2.h"   //nelson cole 2 font. 8x8

// #imported
// Display device library.
#include <libdisp.h>

#include "char.h"
#include "dtext.h"
#include "line.h"

#include "wt.h"
#include "menu.h"
#include "grinput.h"   //#test
#include "window.h"
#include "painter.h"
#include "bmp.h"

// h:0.0
#include "os/screen.h"   // X-like
#include "os/display.h"  // X-like
#include "os/host.h"     // X-like h:0.0

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


#include "packet.h"


// # model. business logic
// #todo:
// We can put this thing in the library. (libgws)
// or (libcon)
#include "connect.h"

#include "font.h"

// Client structure.
// O proprio servidor poderia ser o cliente 0??
#include "client.h"

// Device Context.
// This is the structure that is gonna be used by the
// drawing routines.
// 'dc->something'
// It needs to be the last one.
#include "dc.h"


#include "dispatch.h"


struct gws_graphics_d
{
    int used;
    int magic;
    struct gui_d  *gui;
    // ...
};
extern struct gws_graphics_d *Currentgraphics;


struct engine_d
{

// flag: When to quit the engine.
// We can quit the engine and reinitialize it again.
    int quit;
// Engine status
    int status;
// graphics support.
    struct gws_graphics_d *graphics;
    // ...
};
extern struct engine_d  Engine;


// MAIN STRUCTURE
// This is the main data structure for the window server.

struct gws_d 
{
    int initialized;

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

//see: main.c
extern struct gws_d  *window_server;

#define STATUS_RUNNING    1   

//
// == Prototypes =============================
//

void invalidate(void);
void validate(void);
int isdirty(void);

void invalidate_background(void);
void validate_background(void);
int is_background_dirty(void);

void gwssrv_set_keyboard_focus(int window);

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

unsigned long gwssrv_get_system_metrics (int index);

void gwssrv_enter_critical_section (void);
void gwssrv_exit_critical_section (void);



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
void gwssrv_quit(void);

int is_accepting_input(void);
void set_input_status(int is_accepting);


//
// End
//


