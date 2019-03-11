
#include <api.h>
#include <gws.h>




/* my_buffer_horizontal_line:
 *     Draw a horizontal line on backbuffer. */

void 
my_buffer_horizontal_line ( unsigned long x1,
                            unsigned long y, 
						    unsigned long x2,  
						    unsigned long color )
{
	
	//printf (">>> ");
	
	while (x1 < x2){
		
		gws_backbuffer_putpixel ( color, x1, y );
        x1++;  
    }
	
	//printf ("<<< ");
}


