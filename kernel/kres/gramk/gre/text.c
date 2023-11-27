
// text.c

#include <kernel.h>

// draw_string:
// Draw a string on the screen. 
void 
draw_string ( 
    unsigned long x,
    unsigned long y,
    unsigned int color,
    char *string )
{
    register int Index=0;

   //int cWidth = 8;
    int cWidth = get_char_width ();
    //int cHeight = get_char_height ();

    //if ( cWidth == 0 || cHeight == 0 )
    if ( cWidth == 0 ){
        debug_print("dtext-draw_string: cWidth\n");
        //panic ("dtext-draw_string: cWidth\n");
        //panic ("dtext-draw_string: cWidth\n");
        return;
    }

    /*
    if ( (void *) string == NULL ){
        debug_print("dtext-draw_string: string\n");
        //panic ("dtext-draw_string: string\n");
        //panic ("dtext-draw_string: string\n");
        return;
    }
    if ( *string == 0  ){
        debug_print("dtext-draw_string: *string\n");
        //panic ("dtext-draw_string: *string\n");
        //panic ("dtext-draw_string: *string\n");
        return;
    }
    */

    // #bugbug
    // There is something not good with this routine.
    
    for ( Index=0; string[Index] != 0; Index++ )
    {
        d_drawchar_transparent ( x, y, color, string[Index] );

        x += cWidth;
    };
}


// x_panic:
// Draw a small red rectangle in the top/left
// and print a message into it.
void x_panic( char *string )
{

// #todo
// Check the string size?

    backbuffer_draw_rectangle( 0, 0, 200, 28, COLOR_RED, 0 );
    backbuffer_draw_horizontal_line( 0, 28, 200, COLOR_YELLOW, 0 );
// string 1
    draw_string(8,8,COLOR_WHITE,"x_panic: ");
// string2
    if ((void*) string != NULL){
        draw_string(80,8,COLOR_WHITE,string);
    }
// done:
    refresh_screen();
// A soft place to fall.
    while(1){ asm("cli"); asm("hlt"); };
}



