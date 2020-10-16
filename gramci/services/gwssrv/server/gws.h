// gws.h 

// Modes.
#define GRAMADO_JAIL        0x00
#define GRAMADO_P1          0x01
#define GRAMADO_HOME        0x02
#define GRAMADO_P2          0x03
#define GRAMADO_CASTLE      0x04
#define GRAMADO_CALIFORNIA  0x05
// ...

// Fail mode.
static char current_mode = 0xFF;



// rtl
#include <types.h>
#include <sys/types.h>
#include <sys/cdefs.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
// ...


// 
#include "globals.h"


// #view
#include "view/colors.h"
#include "view/pixel.h"
#include "view/char.h"
#include "view/dtext.h"
#include "view/line.h"
#include "view/vk.h"       // # view input events
#include "view/wt.h"
#include "view/menu.h"
#include "view/window.h"
#include "view/bmp.h"
#include "view/screen.h"   // X-like
#include "view/display.h"  // X-like
#include "view/host.h"     // X-like h:0.0
#include "view/gui.h"
#include "view/comp.h"
#include "view/event.h"    // view inputs
// ...


#include "view/grprim.h"




// # data model
#include "model/packet.h"


// # model. business logic
// #todo:
// We can put this thing in the library. (libgws)
// or (libcon)
#include "model/connect.h"

// data model

#include "model/nc2.h"   //nelson cole 2 font. 8x8
#include "model/lt8x8.h"
// ...
#include "model/font.h"




// Client structure.
// O proprio servidor poderia ser o cliente 0??

#include "model/client.h"


// # model. business logic
#include "model/services.h"


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
struct gws_window_d *keyboard_window;
struct gws_window_d *mouse_window;
struct gws_window_d *cursor_window;  // Where cursor came from.
struct gws_window_d *button_window;  // Where button was pressed.



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







// MAIN STRUCTURE

struct gws_d 
{
    struct gui_d *gui;
};
struct gws_d GWS;



void xxxThread (void);
void ____test_threads (void);


void *
gwssrv_create_thread ( 
    unsigned long init_eip, 
    unsigned long init_stack, 
    char *name );

void gwssrv_start_thread (void *thread);



int service_drain_input (void);


void gwssrv_debug_print (char *string);

int gwssrv_clone_and_execute ( char *name );
unsigned long gwssrv_get_system_metrics (int index);


void gwssrv_enter_critical_section (void);
void gwssrv_exit_critical_section (void);

void gwssrv_show_backbuffer (void);




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










