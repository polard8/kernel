/*
 * rect.c 
 * 
 *     Rectangle support for gws.
 */



//#include <api.h>

#include <gws.h>




int is_rect_empty( struct gws_rect_d *rect )
{
    if ( (void*) rect == NULL )
        return -1;
        
    return (int) ((rect->left >= rect->right) || (rect->top >= rect->bottom));
}


void *rect_memcpy32 ( void *v_dst, const void *v_src, unsigned long c )
{
	
	//const char *src = v_src;
	//char *dst = v_dst;

	long *src = (long *) v_src;
	long *dst = (long *) v_dst;
	
	/* Simple, byte oriented memcpy. */
	while (c--)
		*dst++ = *src++;

	return v_dst;
}




void 
gws_refresh_rectangle ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height )
{

    void       *p = (void *)      ____FRONTBUFFER_VA;
    const void *q = (const void*) ____BACKBUFFER_VA;


	//#TEST
	register unsigned int i;
	//unsigned int i;


	unsigned int line_size=0; 
	unsigned int lines=0;
	unsigned int offset=0;


    // Device info.
    unsigned long ScreenWidth  = (unsigned long) gws_get_device_width();
    //unsigned long ScreenHeight = (unsigned long) gws_get_device_height();

	int count; 

	// = 3; 24bpp
	int bytes_count;



    line_size = (unsigned int) width; 
    lines     = (unsigned int) height;

    switch (SavedBPP)
    {
        case 32:  bytes_count = 4;  break;
        case 24:  bytes_count = 3;  break;

		// ...

		//??
		//default:
		    //break;
    };

	// #atenção.
	
	//offset = (unsigned int) BUFFER_PIXEL_OFFSET( x, y );

    offset = (unsigned int) ( (bytes_count*SavedX*(y)) + (bytes_count*(x)) );

    p = (void *)       (p + offset);    
    q = (const void *) (q + offset);    


	// #bugbug
	// Isso pode nos dar problemas.
	// ?? Isso ainda é necessário nos dias de hoje ??
	
	//vsync ();	
		
	//(line_size * bytes_count) é o número de bytes por linha. 

	//#importante
	//É bem mais rápido com múltiplos de 4.	
	
	//se for divisível por 4.
	if ( ((line_size * bytes_count) % 4) == 0 )
	{
        count = ((line_size * bytes_count) / 4); 

	    for ( i=0; i < lines; i++ )
	    {
		    //copia uma linha ou um pouco mais caso não seja divisível por 
		    rect_memcpy32 ( p, q, count );
		    
			q += (ScreenWidth * bytes_count);
	 		p += (ScreenWidth * bytes_count);
	    };
	}

	//se não for divisível por 4.
	if ( ((line_size * bytes_count) % 4) != 0 )
	{
	    for ( i=0; i < lines; i++ )
	    {
		    memcpy ( (void *) p, (const void *) q, (line_size * bytes_count) );
		    
			q += (ScreenWidth * bytes_count);
		    p += (ScreenWidth * bytes_count);
	    };
	}
}



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

    if ( rect.width > (w_max - rect.left) )
    {
        rect.width = (w_max - rect.left);
    }
    
    if (rect.height > (h_max - rect.top) )
    {
        rect.height > (h_max - rect.top);
    }

    //Margins.
    rect.right  = (rect.left + rect.width);
    rect.bottom = (rect.top  + rect.height); 

    rect.bg_color = color;


    // Draw lines on backbuffer.

    while (rect.height--)
    {
        lineBackbufferDrawHorizontalLine ( 
            rect.left, 
            rect.top, 
            rect.right, 
            rect.bg_color );
       
       rect.top++;
    };    
}



