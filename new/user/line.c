

#include <kernel.h>


//Herdadas do Boot Loader.
// De onde vem isso ?? head.s
// @todo: Devemos chamar o módulo hal para obtermos esses valores.
//depois salvamos em variáveis internas usadas pela gui.
//extern unsigned long SavedBootBlock;
//extern unsigned long SavedLFB;
extern unsigned long SavedX;
extern unsigned long SavedY;
extern unsigned long SavedBPP; 

/*
 *****************************************
 * my_buffer_horizontal_line:
 *     Draw a horizontal line on backbuffer. 
 */


void 
my_buffer_horizontal_line ( 
    unsigned long x1,
    unsigned long y, 
    unsigned long x2, 
    unsigned int color )
{

    if (x1 > x2){
        return;
    }

    while (x1 < x2)
    {
        backbuffer_putpixel ( color, x1, y, 0 );
        x1++;
    };
}
