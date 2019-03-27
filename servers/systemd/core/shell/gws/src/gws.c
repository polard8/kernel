
#include <stddef.h>
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


int serverInit (){
	
	printf ("serverInit: Initializing gws server ...\n");
	
    return (int) gws_init();
}



/*
 ************************************
 * serverDialog:
 *     Dia'logo padrao para servidores em user mode.
 */

void *serverDialog ( unsigned long buffer_address ){
	
	unsigned long *message_buffer = (unsigned long *) buffer_address;

	
	if (buffer_address == 0)
		return NULL;

	//0 = window
	//1 = msg
	//2 = long1
	//3 = long2
	//4 = long3
	//  ...
	
	//msg
	int msg = (int) message_buffer[1];
	
	unsigned long long1 = (unsigned long) message_buffer[2];
	unsigned long long2 = (unsigned long) message_buffer[3];
	unsigned long long3 = (unsigned long) message_buffer[4];
	unsigned long long4 = (unsigned long) message_buffer[5];
	unsigned long long5 = (unsigned long) message_buffer[6];
	unsigned long long6 = (unsigned long) message_buffer[7];
	unsigned long long7 = (unsigned long) message_buffer[8];
	unsigned long long8 = (unsigned long) message_buffer[9];
	unsigned long long9 = (unsigned long) message_buffer[10];	
	//...
	
	switch (msg)
	{
	    case 0:
			return NULL;
			break;
			
			//Initialize gws server	
		case 9000:
			printf ("9000: \n");
			return (void *) serverInit ();
			break;
			
		//
		case 9001:	
			//color, x, y
			return (void *) gws_backbuffer_putpixel ( long1, long2, long3 );
			break;			
		
		//
		case 9002:	
			//x, y, color, char
			gws_drawchar_transparent ( long1, long2, long3, (unsigned long) long4);
			return NULL;
			break;			

		case 9003:
			//x, y, char, fg, bg
			gws_draw_char ( long1, long2, (unsigned long) long3, long4, long5 );
			return NULL;
			break;
			
		case 9004:
			printf ("9004: \n");
			// x1, y, x2, color
			my_buffer_horizontal_line ( long1, long2, long3, long4 );
			
			//#debug
			refresh_screen();  
			
			return NULL;
			break;


		case 9005:
			//x, y, width, height, color
			drawDataRectangle ( long1, long2, long3, long4, long5 );
			return NULL;
			break;
	
	    //...
			
			
		default:
			break;
	};
	
    return NULL;
}



