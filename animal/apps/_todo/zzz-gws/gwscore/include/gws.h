

//gws.h 


unsigned long SavedBootBlock;
unsigned long SavedLFB;   // ??? pa va ???
unsigned long SavedX;
unsigned long SavedY;
unsigned long SavedBPP; 


unsigned long  ____BACKBUFFER_VA;


//...



#include "gws/pixel.h"
#include "gws/char.h"
#include "gws/line.h"
#include "gws/window.h"
#include "gws/ws.h"

int gwsInit ();




// Função padrão para todos os servidores ???
// #todo: temos que criar isso.
int serverInit ();


