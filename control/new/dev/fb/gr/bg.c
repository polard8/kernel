
// bg.c

#include <kernel.h>

// #bugbug
// Essa rotina é sensível, pois agora usamos 64bit.
// Called by kernel_main()
// Where? backbuffer?
void backgroundDraw (unsigned int color)
{
    unsigned long deviceWidth  = (unsigned long) screenGetWidth();
    unsigned long deviceHeight = (unsigned long) screenGetHeight();

    if ( deviceWidth == 0 || deviceHeight == 0 )
    {
        debug_print ("backgroundDraw: [PANIC] w h\n");
        //panic       ("drawDataRectangle: [PANIC] w h\n");
        return;
    }

// Draw a rectangle into the backbuffer.
    backbuffer_draw_rectangle( 
        0, 0, deviceWidth, deviceHeight, 
        color,
        0 );   //rop_flags

/*
    //loop
    register unsigned long i=0;

    if (VideoBlock.useGui != 1){
        debug_print ("backgroundDraw: No GUI\n");
        return;
    }

    for ( i=0; i<SavedY; i++ ){
        backbuffer_draw_horizontal_line ( 0, i, SavedX, color );
    };
    
    */

// Cursor.
// Nao funciona
    set_up_cursor(0,0);
}

// Called by kernel_main().
int Background_initialize(void)
{
    backgroundDraw ( (unsigned int) COLOR_BLACK );
    return 0;
}


