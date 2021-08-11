

//pixel.h


#ifndef __PIXEL_H
#define __PIXEL_H  1

int 
pixelBackBufferPutpixel2 ( 
    unsigned int color, 
    int x, 
    int y );


//ACESSANDO O BACKBUFFER DIRETAMENTE
int 
pixelBackBufferPutpixel ( 
    unsigned int color, 
    int x, 
    int y );
    


unsigned long
pixelBackBufferGetColor ( 
    int x, 
    int y );
    

#endif    



