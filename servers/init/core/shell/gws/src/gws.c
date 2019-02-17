

#include <api.h>
#include <gws.h>



#include "nc2.h"



int gws_init(){


	 // fonte atual.
	gws_currentfont_address = (unsigned long) &font_nelson_cole2[0]; 
	
    gfontSize = 8;

    // draw char support
    gcharWidth = 8;
    gcharHeight = 8;

	return 0;
}



