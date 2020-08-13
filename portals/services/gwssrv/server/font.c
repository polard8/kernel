

    //todo: the font support.

//#include <api.h>

#include <gws.h>



int gwssrv_init_font(void)
{
    // Font
    gfontSize   = 8;
    // Fonte atual.
    gws_currentfont_address = (unsigned long) &font_nelson_cole2[0]; 

    // ...
    
    return 0;
}



