

//gws.h 



//...

#include "globals.h"


#include "char.h"
#include "line.h"
#include "pixel.h"


// X-like
#include "window.h"
#include "screen.h"
#include "display.h"
#include "gui.h"


#include "packet.h"
#include "bmp.h"

// #todo:
// We can put this thing in the library. (libgws)
// or (libcon)
#include "connect.h"

// Client structure.
// O proprio servidor poderia ser o cliente 0??
#include "client.h"

#include "font.h"

// nc2 font.
#include "nc2.h"

#include "event.h"




// MAIN STRUCTURE

struct gws_d 
{
    struct gui_d *gui;
};
struct gws_d GWS;


int gwsInit ();

unsigned long gws_get_device_width(void);
unsigned long gws_get_device_height(void);

// Função padrão para todos os servidores ???
// #todo: temos que criar isso.
int serverInit ();


void gws_show_backbuffer(void);

int gwssrv_init_globals(void);

void gwssrv_wait_message(void);

void gwssrv_yield(void);
