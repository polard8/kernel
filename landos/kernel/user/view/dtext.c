
#include <kernel.h>



/* 
 * draw_string:
 *     Draw a string on the screen. 
 */

void 
draw_string ( 
    unsigned long x,
    unsigned long y,
    unsigned int color,
    unsigned char *string )
{

    // loop
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

void x_panic( char *string )
{
    drawDataRectangle( 0, 0, 200, 28, COLOR_RED );
    my_buffer_horizontal_line( 0, 28, 200, COLOR_YELLOW );

    // string 1
    draw_string(8,8,COLOR_WHITE,"x_panic: ");

    // string2
    if( (void*) string != NULL ){
        draw_string(80,8,COLOR_WHITE,string);
    }

//done:
    refresh_screen();
    while(1){ asm("cli"); asm("hlt"); };
}


void xxxDrawString( char *string )
{
/*
    drawDataRectangle( 0, 0, 200, 28, COLOR_RED );
    my_buffer_horizontal_line( 0, 28, 200, COLOR_YELLOW );

    // string 1
    draw_string(8,8,COLOR_WHITE,"string: ");

    // string2
    if( (void*) string != NULL ){
        draw_string(80,8,COLOR_WHITE,string);
    }

//done:
    refresh_screen();
    //while(1){ asm("cli"); asm("hlt"); };
*/
}



