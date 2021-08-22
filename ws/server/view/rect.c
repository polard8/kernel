/*
 * rect.c 
 * 
 *     Rectangle support for gws.
 */


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
    {
        return FALSE;
    }
    
    rect->left   = left;
    rect->top    = top;
    rect->width  = width;
    rect->height = height;

    // #text
    // rect->is_empty = TRUE;

    return TRUE;
}


// See: window.h
void 
inflate_rect ( 
    struct gws_rect_d *rect, 
    unsigned long cx, 
    unsigned long cy )
{
    if ( (void*) rect == NULL ){
        return;
    }
    
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
    if ( (void*) rectDest == NULL ){
        return;
    }

    if ( (void*) rectSrc == NULL ){
        return;
    }


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


// ??
// #todo: Comment what is happening here.
// Move
void 
offset_rect ( 
    struct gws_rect_d *rect, 
    unsigned long cx, 
    unsigned long cy )
{
    if ( (void*) rect == NULL ){
        return;
    }
    
    //offset rect
    rect->left   += cx;
    rect->top    += cy;
    rect->right  += cx;
    rect->bottom += cy;

    //update width and height
    rect->width  = (rect->right  - rect->left);
    rect->height = (rect->bottom - rect->top);
}

// ??
// #todo: Comment what is happening here.
void 
copy_offset_rect ( 
    struct gws_rect_d *rectDest, 
    struct gws_rect_d *rectSrc, 
    unsigned long cx, 
    unsigned long cy )
{
    if ( (void*) rectDest == NULL ){
        return;
    }

    if ( (void*) rectSrc == NULL ){
        return;
    }

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


// ??
// #todo: Comment what is happening here.
// Checando alguma falha nos valores.
// Devemos ajustar quando falhar?
// Talvez o termo empty nao seja o apropriado aqui,
// pois empty pode significar apenas nao pintado. not fill.
int rect_validate_size( struct gws_rect_d *rect )
{
    if ( (void*) rect == NULL ){
        return -1;
    }

    if ((rect->left >= rect->right) || 
        (rect->top  >= rect->bottom))
    {
        return FALSE;
    }

    return TRUE;
}

int rect_validate_size2( struct gws_rect_d *rect )
{
    if ( (void*) rect == NULL ){
        return -1;
    }

    if ( (rect->width  <= 0 ) || 
         (rect->height <= 0 ) )
    {
        return FALSE;
    }
     
    return TRUE;
}

int is_rect_null( struct gws_rect_d *rect )
{
    if ( (void*) rect == NULL ){
        return -1;
    }
    
    if (rect->width == 0 && rect->height == 0 )
    {
        return TRUE;
    }
    
    return FALSE;
}



int is_rect_empty( struct gws_rect_d *rect )
{
    if ( (void*) rect == NULL ){
        return -1;
    }

    if (rect->is_empty == TRUE)
    {
        return (int) TRUE;
    }
 
    rect->is_empty = FALSE;
    return FALSE;
}


// ??
// #todo: Comment what is happening here.
int is_rect_dirty( struct gws_rect_d *rect )
{
    // Error!
    if ( (void*) rect == NULL ){
        return -1;
    }

    // true
    if ( rect->dirty == TRUE  ){
        return (int) TRUE;
    }
    
    //false
    return FALSE;
}


int 
rect_contains_vertically ( 
    struct gws_rect_d *rect,  
    unsigned long y ) 
{
    if ( (void*) rect == NULL ){
        return -1;
    }

    // ta dentro
    if ( y >= rect->top &&
         y <= rect->bottom )
    {
        return TRUE;
    }

    // ta fora
    return FALSE;
}


int 
rect_contains_horizontally ( 
    struct gws_rect_d *rect,
    unsigned long x )
{
    if ( (void*) rect == NULL ){
        return -1;
    }
    
    // ta dentro
    if ( x >= rect->left &&
         x <= rect->right )
    {
        return TRUE;
    }

    // ta fora
    return FALSE;
}


void 
rect_set_left ( 
    struct gws_rect_d *rect, 
    unsigned long value )
{
    if ( (void*) rect == NULL ){
        return;
    }
    
    rect->left = value;
}

void 
rect_set_top ( 
    struct gws_rect_d *rect, 
    unsigned long value )
{
    if ( (void*) rect == NULL ){
        return;
    }
    
    rect->top = value;
}

void 
rect_set_right ( 
    struct gws_rect_d *rect, 
    unsigned long value )
{
    if ( (void*) rect == NULL ){
        return;
    }
    
    rect->right = value;
}

void 
rect_set_bottom ( 
    struct gws_rect_d *rect, 
    unsigned long value )
{
    if ( (void*) rect == NULL ){
        return;
    }
    
    rect->bottom = value;
}

// #todo
// Do not check the validation.
// We need a prefix that tellus that we will no chack the validation
// os the addresses

void *rect_memcpy32 ( 
    void *v_dst, 
    const void *v_src, 
    unsigned long c )
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

    return (void *) v_dst;
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


//======================================
// Calling kgws in ring0.
// Using the kgws to draw the rectangle.
void 
xxx_gws_draw_rectangle ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height,
    unsigned long color )
{
    unsigned long Buffer[6];
    
    Buffer[0] = (unsigned long) x;
    Buffer[1] = (unsigned long) y;
    Buffer[2] = (unsigned long) width;
    Buffer[3] = (unsigned long) height;
    Buffer[4] = (unsigned long) color;
    
    gramado_system_call ( 
        9, 
        (unsigned long) &Buffer[0], 
        0, 
        0 );
}


//======================================
// Calling kgws in ring0.
// Using the kgws to refresh the rectangle.
void 
xxx_gws_refresh_rectangle ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height )
{
    unsigned long Buffer[5];
    
    Buffer[0] = (unsigned long) x;
    Buffer[1] = (unsigned long) y;
    Buffer[2] = (unsigned long) width;
    Buffer[3] = (unsigned long) height;

    gramado_system_call ( 
        10, 
        (unsigned long) &Buffer[0], 
        0, 
        0 );
}






/*
 *************************************************** 
 * gws_refresh_rectangle:
 * 
 */

void 
gws_refresh_rectangle ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height )
{

    int RefreshRectangleUsingKGWS = TRUE;

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


//
// Refresh in ring0 using the kgws.
//

    if ( RefreshRectangleUsingKGWS == TRUE )
    {
        xxx_gws_refresh_rectangle(x,y,width,height);
        return;
    }


    if ( ScreenWidth == 0 ){
        printf ("gws_refresh_rectangle: [ERROR] ScreenWidth\n");  
        exit(1);
    }

    line_size = (unsigned int) width; 
    lines     = (unsigned int) height;

    switch (SavedBPP){
        case 32:  bytes_count = 4;  break;
        case 24:  bytes_count = 3;  break;
        // ... #todo
        default:
            printf ("gws_refresh_rectangle: [ERROR] SavedBPP\n");  
            exit(1);
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

    int DrawRectangleUsingKGWS = TRUE;
    
    struct gws_rect_d rect;
    
    unsigned long w_max = gws_get_device_width();
    unsigned long h_max = gws_get_device_height();


    rect.left = x;
    rect.top  = y;
    rect.width  = width;  
    rect.height = height;  

    rect.bg_color = color;


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



    //
    // empty
    //
    
    if ( fill == FALSE ){
        rect.is_empty = TRUE;
    }


    /*

    // #todo
    // Desenhar as bordas com linhas
    // ou com retangulos
   
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
    
    if ( fill == TRUE ){
        rect.is_empty = FALSE;
    }


//
// Draw
//


    
//
// Drawing in ring0 using kgws.
//

    // Draw lines on backbuffer.
    if ( DrawRectangleUsingKGWS == TRUE )
    {
         xxx_gws_draw_rectangle (
             rect.left,
             rect.top,
             rect.width,
             rect.height,
             rect.bg_color );
 
         return;
    }


//
// Drawing in ring3.
//

    // Draw lines on backbuffer.
    while (rect.height--){
        lineBackbufferDrawHorizontalLine ( 
            rect.left, rect.top, 
            rect.right, rect.bg_color );
       
       rect.top++;
    };
}



