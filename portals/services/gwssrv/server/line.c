/*
 * File: line.c 
 * 
 * 
 * 
 * 
 */



//#include <api.h>

#include <gws.h>




int servicelineBackbufferDrawHorizontalLine (void)
{

	//o buffer é uma global nesse documento.
    unsigned long *message_address = (unsigned long *) &__buffer[0];

    //x1,y,x2, color
    unsigned long x1,y,x2,color;
      
    x1 = message_address[4];  // 
    y  = message_address[5];   // 
    x2 = message_address[6];  // 
    color = message_address[7];



    lineBackbufferDrawHorizontalLine ( x1, y, x2, color );
    
    gws_show_backbuffer(); // for debug   
    return 0;
}



/* 
 * lineBackbufferDrawHorizontalLine:
 *     Draw a horizontal line on backbuffer. 
 */

void 
lineBackbufferDrawHorizontalLine ( 
    unsigned long x1,
    unsigned long y, 
    unsigned long x2,  
    unsigned long color )
{

    while (x1 < x2)
    {
        pixelBackBufferPutpixel ( color, x1, y );
        x1++;  
    };
}


