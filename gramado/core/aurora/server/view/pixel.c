
//pixel.c 



#include <gws.h>


//
// ## putpixel: 
// backbuffer e lfb ##
//
// IN: cor, x, y


//
// #todo
// Talvez possamos escrever diretamente no lfb.
// Precisamos de memória compartilhada.
//



int servicepixelBackBufferPutpixel(void)
{
	//o buffer é uma global nesse documento.
    unsigned long *message_address = (unsigned long *) &__buffer[0];

    unsigned long x,y,color;
      
    x     = message_address[4];  // x
    y     = message_address[5];  // y
    color = message_address[6];  // color

    pixelBackBufferPutpixel ( color, x, y );

    gws_show_backbuffer (); // for debug
    return 0;
}





// usando serviço do kernel
int 
pixelBackBufferPutpixel2 ( 
    unsigned long color, 
    unsigned long x, 
    unsigned long y )
{
    return (int) gramado_system_call ( 6, color, x, y );
}


/*
 * pixelBackBufferPutpixel:
 * 
 * 
 */

// usando o endereço virtual do backbuffer
// ?? será que está mapeado ???
// está em ring 3 ??? ou ring 0???

int 
pixelBackBufferPutpixel ( 
    unsigned long color, 
    unsigned long x, 
    unsigned long y )
{
    unsigned char *where = (unsigned char *) ____BACKBUFFER_VA;
    //unsigned char *where = (unsigned char *) 0xC0800000;


    // bgra
    char b, g, r, a;

    b = (color & 0xFF);
    g = (color & 0xFF00)   >> 8;
    r = (color & 0xFF0000) >> 16;
    a = (color >> 24) + 1;


	// 3 = 24 bpp

    int bytes_count=0;

    //
    // bpp
    //
    
    // #danger
    // Esse valor foi herdado do bootloader.

    switch (SavedBPP){

        case 32:  bytes_count = 4;  break;
        case 24:  bytes_count = 3;  break;
        //case 16:  bytes_count = 2;  break;
        //case 8:   bytes_count = 1;  break;
        
        default:
            printf("backbuffer_putpixel: [ERROR] SavedBPP\n");
            //panic ("backbuffer_putpixel: SavedBPP");
            break;
    };

	// #importante
	// Pegamos a largura do dispositivo.
	
    //int width = (int) SavedX; 
    
    int width = (int) SavedX; 
    
    int offset = (int) ( (bytes_count*width*y) + (bytes_count*x) );

    //
    // BGR and A
    //

    where[offset]    = b;
    where[offset +1] = g;
    where[offset +2] = r;
    if ( SavedBPP == 32 ){ where[offset +3] = a; };
}



//
// End.
//



