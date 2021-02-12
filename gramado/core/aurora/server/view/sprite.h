

#ifndef  ____SPRITE_H
#define  ____SPRITE_H    1


// Types
// #todo: maybe create a 'enum'

#define SPRITE_NULL   0
#define SPRITE_LINE   1
#define SPRITE_CIRCLE 2
// ...


struct gws_sprite_d
{
    int used;
    int magic;
    
    int type;
    
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




