/*
 * File: line.c 
 * 
 * 
 * 
 * 
 */



#include <api.h>
#include <gws.h>




/* 
 * lineBackbufferDrawHorizontalLine:
 *     Draw a horizontal line on backbuffer. 
 */

void 
lineBackbufferDrawHorizontalLine ( unsigned long x1,
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


