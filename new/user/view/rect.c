



#include <kernel.h>


/* 
 *************************************
 * drawDataRectangle:
 *     Draw a rectangle on backbuffer. 
 */

// #bugbug
// Agora precisamos considerar o limite de apenas 2mb
// de lfb mapeados e de apenas 2 mb de backbuffer mapeados.
// Pois nao queremos escrever em area nao mapeada.

void 
drawDataRectangle ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height, 
    unsigned int color )
{

    debug_print("drawDataRectangle: r0 :)\n");
    
    // #todo
    // Get the clipping window/rectangle.

    struct rect_d  Rect;
    struct rect_d  ClippingRect;


// flag
    int UseClipping = TRUE;

// dc: Clipping
    unsigned long deviceWidth  = (unsigned long) screenGetWidth();
    unsigned long deviceHeight = (unsigned long) screenGetHeight();


    //loop
    unsigned long internal_height = (unsigned long) height;

    // Clipping support.
    
    if ( deviceWidth == 0 || deviceHeight == 0 )
    {
        debug_print ("drawDataRectangle: [PANIC] w h\n");
        //panic       ("drawDataRectangle: [PANIC] w h\n");
        return;
    }

//
// Clipping rectangle
//

    // #todo
    // It need to be a blobal thing.
    // We need to handle the surfaces used by 
    // this embedded window server and the loadable one.

    ClippingRect.left   = 0;
    ClippingRect.top    = 0;
    ClippingRect.width  = deviceWidth;
    ClippingRect.height = deviceHeight;

    ClippingRect.right  = deviceWidth;
    ClippingRect.bottom = deviceHeight;

// #debug
// Provisório

    if ( ClippingRect.width > 800 )
       panic("drawDataRectangle: width");

    if ( ClippingRect.height > 600 )
       panic("drawDataRectangle: height");


    if ( ClippingRect.right > 800 )
       panic("drawDataRectangle: right");

    if ( ClippingRect.bottom > 600 )
       panic("drawDataRectangle: bottom");


//
// == Target rectangle ================
//

    Rect.bg_color = (unsigned int) color;

    // Dimensions
    Rect.x = 0;
    Rect.y = 0;
    Rect.width  = width;
    Rect.height = height;

    // Margins
    Rect.left   = x; 
    Rect.top    = y;
    Rect.right  = (unsigned long) (Rect.left + Rect.width);
    Rect.bottom = (unsigned long) (Rect.top  + Rect.height); 


//
// Clipping
//

	// Limits.
	
	// #todo: 
	// Repensar os limites para uma janela.
	// Uma janela poderá ser maior que as dimensões de um dispositivo.
	// mas não poderá ser maior que as dimensões do backbuffer.
	// Ou seja: O dedicated buffer de uma janela deve ser menor que
	// o backbuffer.

    //if ( Rect.right  > SavedX ){  Rect.right  = SavedX;  }
    //if ( Rect.bottom > SavedY ){  Rect.bottom = SavedY;  }


    if ( Rect.left   < ClippingRect.left   ){  Rect.left   = ClippingRect.left;   }
    if ( Rect.top    < ClippingRect.top    ){  Rect.top    = ClippingRect.top;    }
    if ( Rect.right  > ClippingRect.right  ){  Rect.right  = ClippingRect.right;  }
    if ( Rect.bottom > ClippingRect.bottom ){  Rect.bottom = ClippingRect.bottom; }


//
// Draw
//


    // Draw lines on backbuffer.

    if ( internal_height > 600 )
       panic("drawDataRectangle: internal_height");


    while (1)
    {
        // Pinta uma linha.
        my_buffer_horizontal_line ( 
            Rect.left, y, Rect.right, Rect.bg_color );
 
        // incrementa a linha a ser pintada.
        y++;
        
        // #??
        // Porque podemos desejar escrever no backbuffer
        // um retângulo que ultrapasse a área do frontbuffer.
        
        if ( UseClipping == TRUE )
        {
            if ( y > ClippingRect.bottom ){ break; };
        }
        
        // decrementa o contador.
        internal_height--;
        
        if (internal_height == 0)
            break;
    };

    debug_print("drawDataRectangle: Done\n");
}

/*
 ***********************************************************
 * refresh_rectangle:
 *     Copiar um retângulo do backbuffer para o frontbuffer. 
 * 
 *     @todo: Rotina parecida com essa pode ser criada e usada para manipular 
 * regiões da tela, como área de cliente efetuar scroll de buffer em páginas 
 * de navegador ou menus .. mas para isso, a cópia seria dentro do próprio 
 * backbuffer ou de um terceiro buffer para o backbuffer. 
 *
 * Histórico:
 *     2017 - Criado por Frederico Lamberti Pissarra.
 *     2018 - Fred Nora.
 */

// #todo 
//kgws não pode acessar o lfb, devemos chamar o diálogo em x/video.c


//#importante
//É bem mais rápido com múltiplos de 4.

// #bugbug
// Agora precisamos considerar o limite de apenas 2mb
// de lfb mapeados e de apenas 2 mb de backbuffer mapeados.
// Pois nao queremos escrever em area nao mapeada.

void 
refresh_rectangle ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height )
{

    debug_print("refresh_rectangle: r0 :)\n");

    void *dest       = (void *)      FRONTBUFFER_ADDRESS;
    const void *src  = (const void*) BACKBUFFER_ADDRESS;

    // loop
    register unsigned int i=0;
    register unsigned int lines=0;
    unsigned int line_size=0; 
    register int count=0; 



    // Screen pitch.
    // screen line size in pixels * bytes per pixel.
    unsigned int screen_pitch=0;  
    // Rectangle pitch
    // rectangle line size in pixels * bytes per pixel.
    unsigned int rectangle_pitch=0;  




    unsigned int offset=0;

    // = 3; 24bpp
    int bytes_count=0;


    int FirstLine = (int) y;

    //int UseVSync = FALSE;
    int UseClipping = TRUE;


    // dc
    unsigned long deviceWidth  = (unsigned long) screenGetWidth();
    unsigned long deviceHeight = (unsigned long) screenGetHeight();

    if ( deviceWidth == 0 || deviceHeight == 0 )
    {
        debug_print ("refresh_rectangle: w h\n");
        panic       ("refresh_rectangle: w h\n");
    }

    line_size = (unsigned int) width; 
    lines     = (unsigned int) height;

    switch (SavedBPP){

        case 32:  bytes_count = 4;  break;
        case 24:  bytes_count = 3;  break;
        // ... #todo
        
        default:
            panic ("refresh_rectangle: SavedBPP\n");
            break;
    };

//
// Pitch
//

    // Screen pitch.
    // Screen line size in pixels plus bytes per pixel.
    screen_pitch    = (unsigned int) (bytes_count * deviceWidth);
    // Rectangle pitch.
    // rectangle line size in pixels * bytes per pixel.
	//(line_size * bytes_count) é o número de bytes por linha. 
    rectangle_pitch = (unsigned int) (bytes_count * line_size);


	// #atenção.
	//offset = (unsigned int) BUFFER_PIXEL_OFFSET( x, y );

    offset = (unsigned int) ( (y*screen_pitch) + (bytes_count*x) );


    dest = (void *)       (dest + offset); 
    src  = (const void *) (src  + offset); 


	// #bugbug
	// Isso pode nos dar problemas.
	// ?? Isso ainda é necessário nos dias de hoje ??

    //if ( UseVSync == TRUE){
        //vsync();
    //}


    // #test
    // Se for divisível por 8.
    if ( (rectangle_pitch % 8) == 0 )
    {
        // 'strength reduction'
        // count = ( internal_pitch / 8 ); 
        count = ( rectangle_pitch >> 3 );   // dividido por 8.
        
        // Copy lines
        for ( i=0; i < lines; i++ )
        {
            // Não copiamos a parte que está fora da janela do dispositivo.
            if ( UseClipping == TRUE ){
                if ( (FirstLine + i) > deviceHeight ){ break; }
            }

            // 8 bytes
            memcpy64 ( (void *) dest, (const void *) src, count );
            dest += screen_pitch;
            src  += screen_pitch;
        };
        return;
    }


    // Se for divisível por 4.

    if ( (rectangle_pitch % 4) == 0 )
    {
        // 'strength reduction'
        // count = ( internal_pitch / 4 ); 
        count = ( rectangle_pitch >> 2 );  //#todo: Use this one.

        // Copy lines
        for ( i=0; i < lines; i++ )
        {
            // Não copiamos a parte que está fora da janela do dispositivo.
            if ( UseClipping == TRUE ){
                if ( (FirstLine + i) > deviceHeight ){ break; }
            }

            // 4 bytes
            memcpy32 ( (void *) dest, (const void *) src, count );
            dest += screen_pitch;
            src  += screen_pitch;
        };
        return;
    }

    // Se não for divisível por 4.
    if ( (rectangle_pitch % 4) != 0 )
    {
        // Copy lines
        for ( i=0; i < lines; i++ )
        {
            // Não copiamos a parte que está fora da janela do dispositivo.
            if ( UseClipping == TRUE ){
                if ( (FirstLine + i) > deviceHeight ){ break; }
            }
            
            // 1 byte
            memcpy ( (void *) dest, (const void *) src, rectangle_pitch );
            dest += screen_pitch; 
            src  += screen_pitch; 
        };
        return;
    }
}

// ??
// A ideia aqui é efetuar o refresh de um retângulo 
// que esteja em um dado buffer.
// ?? Not tested yet

void 
refresh_rectangle2 ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height,
    unsigned long buffer1,
    unsigned long buffer2 )
{

	// #todo
	// Fazer a mesma otimizaçao que fizemos na outra rotina de refresh rectangle.


    void *p       = (void *)       buffer1;  // destino.
    const void *q = (const void *) buffer2;  // origem.


    register unsigned int i=0;
    register unsigned int lines=0;
    unsigned int line_size=0; 
    register int count=0; 

    unsigned int offset=0;

	// = 3; //24bpp
    int bytes_count;

	unsigned long Width = (unsigned long) screenGetWidth();
	unsigned long Height = (unsigned long) screenGetHeight();


	line_size = (unsigned int) width; 
	lines     = (unsigned int) height;


    switch (SavedBPP)
    {
		case 32:  bytes_count = 4;  break;
		case 24:  bytes_count = 3;  break;
		//#todo: default
    };


	//offset = (unsigned int) BUFFER_PIXEL_OFFSET( x, y );
	offset = (unsigned int) ( (bytes_count*SavedX*(y)) + (bytes_count*(x)) );	

	
	p = (void *)       (p + offset);    
	q = (const void *) (q + offset);    

    //if( use_vsync)
    //vsync ();

	
	//(line_size * 3) é o número de bytes por linha. 
	
	//se for divisível por 4.
    if ( ((line_size * 3) % 4) == 0 )
    {
        count = ((line_size * 3) / 4);  	

	    for ( i=0; i < lines; i++ )
	    {
		    //copia uma linha ou um pouco mais caso não seja divisível por 
		    memcpy32 ( p, q, count );
		    
			q += (Width * 3);
	 	    p += (Width * 3);
	    };
    }

	//se não for divisível por 4.
    if ( ((line_size * 3) % 4) != 0 )
    {

        //count = (line_size * 3); 
	
	    for ( i=0; i < lines; i++ )
	    {
		    memcpy ( (void *) p, (const void *) q, (line_size * 3) );
		    q += (Width * 3);
		    p += (Width * 3);
	    };
    }

	/*
	
	for ( i=0; i < lines; i++ )
	{
		memcpy( p, q, (line_size * 3) );
		q += (Width * 3);
		p += (Width * 3);
	};	
	*/
}

/*
 ************************* 
 * scroll_screen_rect:
 * 
 *     Scroll a rectangle. ?
 */

// Helper function to scroll routine.
// Called by console_scroll() in tty/console.c

void scroll_screen_rect (void){

    register unsigned int i=0;

    unsigned int line_size=0;  // w 
    unsigned int lines=0;      // h

    unsigned int offset=0;

    // Device info.
    unsigned long deviceWidth  = (unsigned long) screenGetWidth();
    unsigned long deviceHeight = (unsigned long) screenGetHeight();


    //int cWidth = get_char_width ();
    int cHeight = get_char_height ();

	// = 3; 
	//24bpp
    int bytes_count = 0;
    
    int count = 0; 


    // #debug
    //debug_print ("scroll_screen_rect:\n");

    if ( deviceWidth == 0 || deviceHeight == 0 )
    {
        debug_print ("scroll_screen_rect: [PANIC] w h\n");
        panic       ("scroll_screen_rect: [PANIC] w h\n");
    }

    // #debug
    //if(cHeight == 8)
        //debug_print("8\n");

    // #debug
    //if(cHeight == 16)
        //debug_print("16\n");


    line_size = (unsigned int) deviceWidth; 
    lines     = (unsigned int) deviceHeight;

    switch (SavedBPP){
        case 32:  bytes_count = 4;  break;
        case 24:  bytes_count = 3;  break;
        // ...
        default:
            panic("scroll_screen_rect: SavedBPP");
            break;
    };


//
// Pointers
//

    // Destination and Source.
    // Destination is the first line.
    // Source is the second line. It has the height of a char.

    void *Dest = (void *) BACKBUFFER_ADDRESS;
    const void *Src  = (const void *) BACKBUFFER_ADDRESS + ( bytes_count * SavedX * cHeight ) ;


    //
    // Copy.
    //

	//#importante
	//É bem mais rápido com múltiplos de 4.	


    // Se for divisível por 4.
    // Copia uma linha, quatro bytes de cada vez.  
        
    if ( ((line_size * bytes_count) % 4) == 0 )
    {
        // #todo: Create a variable for 'pitch' and use streigh reduction
        count = ((line_size * bytes_count) / 4); 
        // count = (internal_pitch>>2);  // #todo: Use this one.

        for ( i=0; i < lines; i++ )
        {
            memcpy32 (Dest,Src,count);

            Src  += (deviceWidth * bytes_count);
            Dest += (deviceWidth * bytes_count);
        };
        return;
    }

    // Se não for divisível por 4.
    // Copia a linha, um bytes por vez.
    // #todo: Podemos suprimir esse if e deixarmos ssomente o for.
    
    if ( ((line_size * bytes_count) % 4) != 0 )
    {
        for ( i=0; i < lines; i++ )
        {
            memcpy ( 
                (void *) Dest, 
                (const void *) Src, 
                (line_size * bytes_count) );

            Src  += (deviceWidth * bytes_count);
            Dest += (deviceWidth * bytes_count);
        };
    }
}

// ??
// Copiando ...
// Destination is an Null pointer? 
// Source is an Null pointer? 
// Zero-sized copy? 
// Destination is Source?

void *rectStrCopyMemory32 ( 
    unsigned long *dest, 
    unsigned long *src, 
    int count ) 
{

    register int i=0;

    // Yes
    if ( (dest == NULL)  || 
         (src == NULL)   || 
         (count == 0)    || 
         (src == dest) ) 
    {
        return dest;
    }

    // GCC should optimize this for us :)
    // I'm lying.
    for ( i=0; i < count; i++ ) 
    {
        dest[i] = src[i];
    };

    return dest;
}    































