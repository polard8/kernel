
// bg.c

#include <kernel.h>

// #bugbug
// Essa rotina é sensível, pois agora usamos 64bit.
// Called by kmain()
// Where? backbuffer?
// Draw a rectangle into the backbuffer.
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

    backbuffer_draw_rectangle( 
        0, 0, deviceWidth, deviceHeight, 
        color,
        0 );   //rop_flags

// Cursor.
// #bugbug: This routine is not working at this time.
    set_up_cursor(0,0);

//#debug
    //debug_print ("backgroundDraw: done\n");
}


// Called by kmain().
int Background_initialize(unsigned int color)
{
    backgroundDraw ( (unsigned int) color );
    //set_up_cursor(0,0);
    return 0;
}


