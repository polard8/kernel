/*
 * File: line.c 
 * 
 * 
 * 
 * 
 */



//#include <api.h>

#include <gws.h>

// ...
//dx = x2 − x1
//dy = y2 − y1
//for x from x1 to x2 do
//    y = y1 + dy × (x − x1) / dx
//    plot(x, y)
// See: https://en.wikipedia.org/wiki/Line_drawing_algorithm

void
A_naive_line_drawing_algorithm(
    unsigned long x1,
    unsigned long x2, 
    unsigned long y1, 
    unsigned long y2, 
    unsigned long color)
{
    unsigned long dx =  x2 - x1;
    unsigned long dy =  y2 - y1;
    unsigned long x=0;
    unsigned long y=0;
    
    for ( x = x1; x < x2; x++ )
    {
         y = (y1 + dy * (x - x1) / dx);
         
         pixelBackBufferPutpixel ( color, x, y );
    }; 
    
    //gwssrv_show_backbuffer();
}


void test_draw_line(void)
{
    int g=0;

    for( g=0; g<400; g++ )
    {
            A_naive_line_drawing_algorithm ( 
                8, 750, 
                8, (50 + (g*4)) , 
                COLOR_YELLOW );
     };

    gwssrv_show_backbuffer();
    //while(1){}
}





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


