

//pixel.h


#ifndef __PIXEL_H
#define __PIXEL_H  1

int 
pixelBackBufferPutpixel2 ( 
    unsigned long color, 
    unsigned long x, 
    unsigned long y );


//ACESSANDO O BACKBUFFER DIRETAMENTE
int 
pixelBackBufferPutpixel ( 
    unsigned long color, 
    unsigned long x, 
    unsigned long y );
    


unsigned long
pixelBackBufferGetColor ( 
    unsigned long x, 
    unsigned long y );
    

#endif    



