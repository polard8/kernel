

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




