/*
 * rect.c 
 * 
 *     Rectangle support for gws.
 */



#include <api.h>
#include <gws.h>


/* 
 * rectBackbufferDrawRectangle:
 *     Draw a rectangle on backbuffer. 
 */

void 
rectBackbufferDrawRectangle ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height, 
    unsigned long color )
{

    struct gws_rect_d rect;
    
    
    unsigned long w_max = gws_get_device_width();
    unsigned long h_max = gws_get_device_height();
   
    //Dimensions.
    rect.x = 0;  
    rect.y = 0;  

    //posicionamento
    rect.left = x;    
    rect.top  = y;
    
    rect.width  = width;  
    rect.height = height;  

    if ( rect.width > (w_max - rect.left) ){
        rect.width = (w_max - rect.left);
    }
    
    if (rect.height > (h_max - rect.top) ){
        rect.height > (h_max - rect.top);
    }

    //Margins.
    rect.right  = rect.left + rect.width;
    rect.bottom = rect.top  + rect.height; 

    rect.bg_color = color;


    // Draw lines on backbuffer.

    while (rect.height--)
    {
        lineBackbufferDrawHorizontalLine ( rect.left, 
            rect.top, 
            rect.right, 
            rect.bg_color );
       
       rect.top++;
    };    
}


