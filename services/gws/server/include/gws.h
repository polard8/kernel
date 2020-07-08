

//gws.h 


unsigned long SavedBootBlock;
unsigned long SavedLFB;   // ??? pa va ???
unsigned long SavedX;
unsigned long SavedY;
unsigned long SavedBPP; 


unsigned long  ____BACKBUFFER_VA;


//...


#include "char.h"
#include "line.h"
#include "pixel.h"
#include "window.h"
#include "packet.h"
#include "bmp.h"

// #todo:
// We can put this thing in the library. (libgws)
// or (libcon)
#include "connect.h"


// Client structure.
// O proprio servidor poderia ser o cliente 0??
#include "client.h"



// ## button support ##
#define GWS_COLOR_BUTTONFACE            0x00F0F0F0
#define GWS_COLOR_BUTTONFACE2           0x00E0E0E0
#define GWS_COLOR_BUTTONFACE3           0x00D0D0D0
#define GWS_COLOR_BUTTONHIGHLIGHT       0x00FFFFFF
#define GWS_COLOR_BUTTONHIGHLIGHT2      0x00404040
#define GWS_COLOR_BUTTONHIGHLIGHT3      0x00008080
#define GWS_COLOR_BUTTONHIGHLIGHTTEXT   COLOR_WHITE
#define GWS_COLOR_BUTTONHIGHLIGHTTEXT2  COLOR_WHITE 
#define GWS_COLOR_BUTTONSHADOW          0x00A0A0A0
#define GWS_COLOR_BUTTONSHADOW2         0x00303030 
#define GWS_COLOR_BUTTONSHADOW3         0x00202020 
#define GWS_COLOR_BUTTONTEXT            COLOR_TEXT



// draw char support
int gcharWidth;
int gcharHeight;


int gfontSize;

//As fontes usadas pelo servidor gws
unsigned long gws_currentfont_address;  // fonte atual.
unsigned long g8x8fontAddress;          // 8×8, 80×25,CGA, EGA
unsigned long g8x14fontAddress;         // 8x14,80×25,EGA
unsigned long g8x16fontAddress;         // ??
unsigned long g9x14fontAddress;         // 9x14,80×25,MDA, Hercules
unsigned long g9x16fontAddress;         // 9x16,80×25,VGA




unsigned long gws_get_device_width(void);
unsigned long gws_get_device_height(void);


int gwsInit ();




// Função padrão para todos os servidores ???
// #todo: temos que criar isso.
int serverInit ();


void gws_show_backbuffer(void);




