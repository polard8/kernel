

//gws.h 

#include <types.h>
#include <sys/types.h>
#include <stddef.h>
#include <stdio.h>

//...

#include "globals.h"

#include "colors.h"


#include "pixel.h"
#include "char.h"
#include "dtext.h"
#include "line.h"



#include "vk.h"
#include "wt.h"


// X-like
#include "window.h"
#include "screen.h"
#include "display.h"
#include "host.h"
#include "gui.h"




#include "comp.h"

#include "packet.h"
#include "bmp.h"

// #todo:
// We can put this thing in the library. (libgws)
// or (libcon)
#include "connect.h"


#include "font.h"

// nc2 font.
#include "nc2.h"

#include "event.h"



// Client structure.
// O proprio servidor poderia ser o cliente 0??
#include "client.h"


#include "services.h"



// #test
// from x window system.
struct gws_window_d *keyboard_window;
struct gws_window_d *mouse_window;
struct gws_window_d *cursor_window;  // Where cursor came from.
struct gws_window_d *button_window;  // Where button was pressed.
unsigned long mouse_x;
unsigned long mouse_y;



// O buffer para  as mensagens recebidas via socket.
#define MSG_BUFFER_SIZE 512
char __buffer[MSG_BUFFER_SIZE];   

// Esses valores serão enviados como 
// resposta ao serviço atual.
// Eles são configurados pelo dialogo na hora da 
// prestação do serviço.
// No início desse array fica o header.
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
