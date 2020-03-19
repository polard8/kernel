
//pixel.c 



#include <api.h>
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




// usando serviço do kernel
int 
pixelBackBufferPutpixel2 ( unsigned long color, 
                          unsigned long x, 
                          unsigned long y )
{
    return (int) gramado_system_call ( 6, color, x, y );
}




// usando o endereço virtual do backbuffer
// ?? será que está mapeado ???
// está em ring 3 ??? ou ring 0???
int 
pixelBackBufferPutpixel ( unsigned long color, 
                          unsigned long x, 
                          unsigned long y )
{
    //return (int) gramado_system_call ( 6, color, x, y );
    
    

    //unsigned char *where = (unsigned char *) 0xC0800000;
    unsigned char *where = (unsigned char *) ____BACKBUFFER_VA;

    //unsigned long color = (unsigned long) ax;

    char b, g, r, a;


    // bgra

    b = (color & 0xFF);	
    g = (color & 0xFF00) >> 8;
    r = (color & 0xFF0000) >> 16;
    a = (color >> 24) + 1;


    // Position.

    //int x = (int) bx;
    //int y = (int) cx;




	// 3 = 24 bpp

    int bytes_count;

    //
    // bpp
    //
    
    // #danger
    // Esse valor foi herdado do bootloader.

    switch (SavedBPP)
    {
		case 32:
		    bytes_count = 4;
		    break;
		
		case 24:
		    bytes_count = 3;
			break;
			
		//#testando
		//case 16:
		//	bytes_count = 2;
		//	break;
		
		//case 8:
		//	bytes_count = 1;
		//	break;
		
		default:
		    //panic ("backbuffer_putpixel: SavedBPP");
		    gde_message_box (3,"xxx","backbuffer_putpixel: SavedBPP");
		    break;
	}
	
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


















