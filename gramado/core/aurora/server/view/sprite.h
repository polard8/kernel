

#ifndef  ____SPRITE_H
#define  ____SPRITE_H    1


// Types
// #todo: maybe create a 'enum'

#define SPRITE_NULL   0
#define SPRITE_POINT  1
#define SPRITE_LINE   2
#define SPRITE_CIRCLE 3
// ...


struct gws_sprite_d
{
    int used;
    int magic;
    
    int type;
    
    // basics
    int x1;
    int y1;
    int z1;
    unsigned long color1;
    int x2;
    int y2;
    int z2;
    unsigned long color2;

    int r;
    
    // ...
};

#define SPRITE_MAX_NUMBER 32
// Sprite list.
unsigned long spriteList[SPRITE_MAX_NUMBER];




//
// == prototypes ==============
//


int 
PlotSprite3D ( 
    struct gws_display_d *display,
    int x, int y, int z,
    unsigned long sprite_list_address,
    int sprite_list_size,
    int just_one );




#endif    




