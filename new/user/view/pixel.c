


#include <kernel.h>

/*
 *********************************
 * backbuffer_putpixel:
 *     Ok. 
 *     O servidor kgws pode acessar um backbuffer. Mas não tem acesso
 * ao frontbuffer. Para isso ele precisa usasr o diálogo do driver 
 * de vídeo.
 * IN: 
 *     color, x, y, 0
 */

void 
backbuffer_putpixel ( 
    unsigned int ax,    // color, 32bit 
    unsigned long bx, 
    unsigned long cx, 
    unsigned long dx )
{

	// #importante
	// Esse é o original. Isso funciona.
	// Não usar.
	// hal_backbuffer_putpixel ( ax, bx, cx, dx );


	// #test
	// tentando um novo método.
	// usando o endereço virtual do backbuffer.
	// precisamos de uma variável global para isso.

    // # todo
    // Estamos determinando um valor.
    // Precisamos de uma variável de devinição do sistema.
    
    // BACKBUFFER_VA = 0xC0800000
    // See: gramado/kernel/include/gva.h
    
    unsigned char *where = (unsigned char *) BACKBUFFER_VA;

    unsigned int color = (unsigned int) ax;

    char b, g, r, a;

    // bgra
    b = (color & 0xFF);
    g = (color & 0xFF00) >> 8;
    r = (color & 0xFF0000) >> 16;
    a = (color >> 24) + 1;


    // Position.
    int x = (int) bx;
    int y = (int) cx;


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

		//#testando
		//case 16:
		//	bytes_count = 2;
		//	break;
		
		//case 8:
		//	bytes_count = 1;
		//	break;

        default:
            //#todo
            //panic ("backbuffer_putpixel: SavedBPP\n");
            debug_print_string("backbuffer_putpixel: SavedBPP\n");
            while(1){}
            break;
    };

	// #importante
	// Pegamos a largura do dispositivo.

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

