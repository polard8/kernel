
//pixel.c 



#include <api.h>
#include <gws.h>


//
// ## putpixel: 
// backbuffer e lfb ##
//
// IN: cor, x, y

int gws_backbuffer_putpixel ( unsigned long color, 
                              unsigned long x, 
                              unsigned long y )
{
	return (int) system_call ( 6, color, x, y );
}


