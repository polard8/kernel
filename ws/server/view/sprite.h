

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
    
    //  shape
    int type;

    unsigned long flags;
    

    // ??
    // what is this?
    
    // basics
    int x1;
    int y1;
    int z1;
    unsigned long color1;

    int x2;
    int y2;
    int z2;
    unsigned long color2;

    // ??
    int r;
    
    // z-order
    int z;
    
    
    unsigned long transparent_color;
    
    // next
    // struct gws_sprite_d *next;
    
    // associated window.
    struct gws_window_d *window;
    
    // #todo
    // Rectangles
    
    // rcSprite =  the rectangle that represents the sprint in the screen
    // rcBackbuffer
    // rcSrc
    // rcDst
    // ...

    // ...
};

#define SPRITE_MAX_NUMBER 32
// Sprite list.
unsigned long spriteList[SPRITE_MAX_NUMBER];


/*
struct gws_spritedata_d
{
    int id;
    
    // window
    struct gws_window_d *window;
    int x;  // inside the client widnow.
    int y;

    struct gws_sprite_d *sprite;
    struct gws_sprite_d *next;
};
*/


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




