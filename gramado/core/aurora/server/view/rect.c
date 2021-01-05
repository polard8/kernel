/*
 * rect.c 
 * 
 *     Rectangle support for gws.
 */



//#include <api.h>

#include <gws.h>


int
set_rect ( 
    struct gws_rect_d *rect, 
    unsigned long left, 
    unsigned long top,
    unsigned long width,
    unsigned long height )
{
    if ( (void*) rect == NULL )
        return FALSE;
    
    rect->left   = left;
    rect->top    = top;
    rect->width  = width;
    rect->height = height;

    return TRUE;
}


// See: window.h
void 
inflate_rect ( 
    struct gws_rect_d *rect, 
    unsigned long cx, 
    unsigned long cy )
{
    if ( (void*) rect == NULL )
        return;
    
    rect->left   -= cx;
    rect->top    -= cy;
    rect->right  += cx;
    rect->bottom += cy;

    rect->width  = (rect->right  - rect->left);
    rect->height = (rect->bottom - rect->top);
}


void 
copy_inflate_rect ( 
    struct gws_rect_d *rectDest, 
    struct gws_rect_d *rectSrc, 
    unsigned long cx, 
    unsigned long cy )
{
    if ( (void*) rectDest == NULL )
        return;

    if ( (void*) rectSrc == NULL )
        return;
    
    
    // inflate and copy.
    // todo: fazer isso em duas etapas.
    rectDest->left   = rectSrc->left   -= cx;
    rectDest->top    = rectSrc->top    -= cy;
    rectDest->right  = rectSrc->right  += cx;
    rectDest->bottom = rectSrc->bottom += cy;

    //update width and height
    rectSrc->width   = (rectSrc->right   - rectSrc->left);
    rectSrc->height  = (rectSrc->bottom  - rectSrc->top);
    rectDest->width  = (rectDest->right  - rectDest->left);
    rectDest->height = (rectDest->bottom - rectDest->top);
}


void 
offset_rect ( 
    struct gws_rect_d *rect, 
    unsigned long cx, 
    unsigned long cy )
{
    if ( (void*) rect == NULL )
        return;
    
    //offset rect
    rect->left   += cx;
    rect->top    += cy;
    rect->right  += cx;
    rect->bottom += cy;

    //update width and height
    rect->width  = (rect->right  - rect->left);
    rect->height = (rect->bottom - rect->top);
}


void 
copy_offset_rect ( 
    struct gws_rect_d *rectDest, 
    struct gws_rect_d *rectSrc, 
    unsigned long cx, 
    unsigned long cy )
{
    if ( (void*) rectDest == NULL )
        return;

    if ( (void*) rectSrc == NULL )
        return;
    
    // offset and copy the rect.
    rectDest->left   = rectSrc->left   += cx;
    rectDest->top    = rectSrc->top    += cy;
    rectDest->right  = rectSrc->right  += cx;
    rectDest->bottom = rectSrc->bottom += cy;

    //update width and height,
    rectSrc->width   = (rectSrc->right  - rectSrc->left);
    rectSrc->height  = (rectSrc->bottom - rectSrc->top);
    rectDest->width  = (rectDest->right  - rectDest->left);
    rectDest->height = (rectDest->bottom - rectDest->top);
}



int is_rect_empty( struct gws_rect_d *rect )
{
    if ( (void*) rect == NULL )
        return -1;


    if ((rect->left >= rect->right) || (rect->top >= rect->bottom))
    {
        return (int) TRUE;
    }
     
    return FALSE;
}



int is_rect_dirty( struct gws_rect_d *rect )
{
    if ( (void*) rect == NULL )
        return -1;

    if ( rect->dirty == 1  ){
        return (int) TRUE;
    }
     
    return FALSE;
}




void *rect_memcpy32 ( void *v_dst, const void *v_src, unsigned long c )
{

    long *src = (long *) v_src;
    long *dst = (long *) v_dst;

    register unsigned long Copy = c;

	//const char *src = v_src;
	//char *dst = v_dst;


    /* Simple, byte oriented memcpy. */
    while (Copy--)
    {
        *dst++ = *src++;
    };

    return v_dst;
}


int gwssrv_refresh_this_rect ( struct gws_rect_d *rect )
{

    if ( (void*) rect == NULL ){
        gwssrv_debug_print("gwssrv_refresh_this_rect: rect\n");
        return -1;
    }

    gws_refresh_rectangle ( 
        rect->left, rect->top, 
        rect->width, rect->height );

    return 0;
}


/*
 *************************************************** 
 * gws_refresh_rectangle:
 * 
 * 
 */

void 
gws_refresh_rectangle ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height )
{

    void       *dest = (void *)      ____FRONTBUFFER_VA;
    const void *src  = (const void*) ____BACKBUFFER_VA;

    //loop?
    register unsigned int i=0;
    register int count=0; 
    register unsigned int lines=0;      // quantas linhas.
    unsigned int line_size=0;  // rectangle line size in pixels.

    // screen line size in pixels * bytes per pixel.
    unsigned int pitch=0;  
    // rectangle line size in pixels * bytes per pixel.
    register unsigned int rectangle_pitch=0;  //loop



    unsigned int offset=0;
    
    // = 3; 24bpp
    int bytes_count=0;


    // Device info.
    unsigned long ScreenWidth  = (unsigned long) gws_get_device_width();
    //unsigned long ScreenHeight = (unsigned long) gws_get_device_height();

    if ( ScreenWidth == 0 ){
        printf ("gws_refresh_rectangle: ScreenWidth\n");  exit(1);
    }

    line_size = (unsigned int) width; 
    lines     = (unsigned int) height;

    switch (SavedBPP){
        case 32:  bytes_count = 4;  break;
        case 24:  bytes_count = 3;  break;
        // ... #todo
        default:
            printf ("gws_refresh_rectangle: SavedBPP\n");  exit(1);
            break;
    };


    // screen line size in pixels * bytes per pixel.
    pitch = (unsigned int) (bytes_count * ScreenWidth);

    // rectangle line size in pixels * bytes per pixel.
    rectangle_pitch = (unsigned int) (bytes_count * line_size);


	// #atenção.
	//offset = (unsigned int) BUFFER_PIXEL_OFFSET( x, y );

    offset = (unsigned int) ( (y*pitch) + (bytes_count*x) );

    dest = (void *)       (dest + offset);    
    src  = (const void *) (src  + offset);    


	// #bugbug
	// Isso pode nos dar problemas.
	// ?? Isso ainda é necessário nos dias de hoje ??
	
	//vsync ();	
		
	//(line_size * bytes_count) é o número de bytes por linha. 

	//#importante
	//É bem mais rápido com múltiplos de 4.	


    // Se for divisível por 4.
    // Copia uma linha ou um pouco mais caso não seja divisível por 4.
    if ( (rectangle_pitch % 4) == 0 )
    {
        count = (rectangle_pitch / 4); 

        for ( i=0; i < lines; i++ ){
            rect_memcpy32 ( (void *) dest, (const void *) src, count );
            dest += pitch;
            src  += pitch;
        };
        
        /* doom style.
        i=0;
        do{
            rect_memcpy32 ( (void *) dest, (const void *) src, count );
            dest += pitch;
            src  += pitch;
            i++;
        }while(i<lines);
        */
    }

    // Se não for divisível por 4.
    if ( (rectangle_pitch % 4) != 0 )
    {
        for ( i=0; i < lines; i++ ){
             memcpy ( (void *) dest, (const void *) src, rectangle_pitch );
             dest += pitch;
             src  += pitch;
        };
        
        /* doom style
        i=0;
        do{
            memcpy ( (void *) dest, (const void *) src, rectangle_pitch );
            dest += pitch;
            src  += pitch;
            i++;
        }while(i<lines);
        */
    }
}



/*
 *******************************************************
 * rectBackbufferDrawRectangle:
 *     Draw a rectangle on backbuffer. 
 */

void 
rectBackbufferDrawRectangle ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height, 
    unsigned long color,
    int fill )
{

    struct gws_rect_d rect;
    
    unsigned long w_max = gws_get_device_width();
    unsigned long h_max = gws_get_device_height();


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


    // empty rectangle




    /*
    if (fill==0)
    {
            //  ____
            // |
            //
            
            //board1, borda de cima e esquerda.
            rectBackbufferDrawRectangle ( 
                window->left, window->top,
                window->width, 1, 
                color, 1 );
            rectBackbufferDrawRectangle ( 
                window->left, window->top, 
                1, window->height,
                color, 1 );

            //  
            //  ____|
            //

            //board2, borda direita e baixo.
            rectBackbufferDrawRectangle ( 
                 ((window->left) + (window->width) -1), window->top, 
                 1, window->height, 
                 color, 1 );
            rectBackbufferDrawRectangle ( 
                 window->left, ( (window->top) + (window->height) -1 ),  
                 window->width, 1, 
                 color, 1 );
          
        return;
    }
    */


    //
    // fill
    //

    // Draw lines on backbuffer.

    while (rect.height--){
        lineBackbufferDrawHorizontalLine ( rect.left, rect.top, 
            rect.right, rect.bg_color );
       
       rect.top++;
    };
}



