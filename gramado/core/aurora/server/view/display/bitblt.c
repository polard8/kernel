
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

    if (x<0){ return -1; }
    if (y<0){ return -1; }

    pixelBackBufferPutpixel ( color, x, y );

    // for debug
    // nem precisa ser o composer estiver fazendo refresh,
    // gws_show_backbuffer(); 

    return 0;
}






// usando serviço do kernel
int 
pixelBackBufferPutpixel2 ( 
    unsigned long color, 
    int x, 
    int y )
{

    if (x<0){ return -1; }
    if (y<0){ return -1; }

    return (int) gramado_system_call ( 6, color, x, y );
}


/*
 *******************************************
 * pixelBackBufferPutpixel:
 *     Put pixel in the device screen.
 */

// #??
// Usando o endereço virtual do backbuffer
// Será que está mapeado ???
// Está em ring 3 ??? ou ring 0???

// Pinta um pixel no backbuffer.
// O buffer tem o tamanho da janela do dispositivo.
// A origem está em top/left.

// #bugbug
// #todo
// Precismos considerar o limite do backbuffer.
// Então teremos um Offset máximo.

// #todo
// Check some flags, just like rasterizations.
// We will need a lot of parameters in this kind of function
// Including the address of the backbuffer.

int 
pixelBackBufferPutpixel ( 
    unsigned long color, 
    int x, 
    int y )
{

    // #todo: It needs to be a parameter.
    // 0xC0800000 ??
    unsigned char *where = (unsigned char *) ____BACKBUFFER_VA;

    // #todo
    // Precismos considerar o limite do backbuffer.
    // Então teremos um Offset máximo.

    unsigned long tmpOffset=0;
    unsigned long MaxOffset=0;

    int Offset=0;
    
    // #todo
    // raster operation. rasterization.
    // unsigned long rop;


    // 4MB limit
    // #bubug: Não fazer multilicações
    //MaxOffset = (int) (1024*10124*4);
    MaxOffset = (int) 0x00400000;

    int width=0;

    char b, g, r, a;
    b = (color & 0xFF);
    g = (color & 0xFF00)   >> 8;
    r = (color & 0xFF0000) >> 16;
    a = (color >> 24) + 1;

    // 3 = 24 bpp
    int bytes_count=0;


    if (x<0){ goto fail; }
    if (y<0){ goto fail; }


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
            printf("pixelBackBufferPutpixel: [ERROR] SavedBPP\n");
            goto fail;
            break;
    };


    

	// #importante
	// Pegamos a largura do dispositivo.

    //int width = (int) SavedX; 
    
    width = (int) SavedX; 


    // unsigned long
    // Nao pode ser maior que 4 MB.
    
    tmpOffset = (unsigned long) ( (bytes_count*width*y) + (bytes_count*x) );

    if( tmpOffset >= MaxOffset ){
        gwssrv_debug_print ("pixelBackBufferPutpixel: [ERROR] backbuffer limits > Max\n"); 
        printf ("pixelBackBufferPutpixel: [ERROR] backbuffer limits > Max\n");
        printf ("tmpOffset=%x\n",tmpOffset);
        printf ("x=%d\n",x);
        printf ("y=%d\n",y);
        printf ("width=%d\n",width);
        exit(1);
        //goto fail;
    }

    // int. menor que 4MB
    Offset = (int) tmpOffset;

    // #bugbug
    // #todo
    // Para não termos problemas com o offset, temos que checar
    // os limites de x e y.

    //
    // Backbuffer limit
    //
    
    // #bugbug
    // Escrever fora do backbuffer pode gerar PF.


    //
    // BGR and A
    //

    where[Offset]    = b;
    where[Offset +1] = g;
    where[Offset +2] = r;
    if ( SavedBPP == 32 ){ where[Offset +3] = a; };
    
    return 0;

fail:
    return -1;
}


// pega uma cor dado sua posição
unsigned long
pixelBackBufferGetColor ( 
    int x, 
    int y )
{

    // 0xC0800000
    unsigned char *where = (unsigned char *) ____BACKBUFFER_VA;


	// 3 = 24 bpp

    int bytes_count=0;


    // #bugbug
    // Essa funçao eta errada,
    // precisamos passar o ponteiro para o retorno via parametro
    // e o retorno da funçao deve ser int, pra indicar sucesso ou nao.

    if (x<0){ return 0; }
    if (y<0){ return 0; }



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

    // bgra
    char b, g, r, a;

    // Get bytes.

    b = where[offset];
    g = where[offset +1];
    r = where[offset +2];
    if ( SavedBPP == 32 ){ a = where[offset +3]; };
    
    unsigned long ColorBuffer=0;
    unsigned char *c = (unsigned char *) &ColorBuffer;

    // Set bytes of ColorBuffer.

    c[0] = b; 
    c[1] = g;
    c[2] = r;
    c[3] = a;

    // return the color value.
    return (unsigned long) ColorBuffer;
}



//
// End.
//



