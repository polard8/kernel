

#include <kernel.h>


extern unsigned long SavedX;
extern unsigned long SavedY;


// Please, help me to be faster!

void r_refresh_screen (void){

    unsigned long *backbuffer  = (unsigned long *) BACKBUFFER_VA;
    unsigned long *frontbuffer = (unsigned long *) FRONTBUFFER_VA;

    int i=0;
    int Max = (int) (SavedX*SavedY);

    // ?? hummmm
    
    vsync();

    // 32bpp.
    
    for ( i=0; i<Max; i++ )
    {
        frontbuffer[i] = backbuffer[i];
    };
}






