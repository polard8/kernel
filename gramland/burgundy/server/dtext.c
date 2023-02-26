/*
 * File: dtext.c 
 *     Draw text routines.
 */

#include "gwsint.h"

/* 
 * grDrawString:
 *     Draw a string on the screen. 
 */
// No clipping
void 
grDrawString ( 
    unsigned long x,
    unsigned long y,
    unsigned int color,
    unsigned char *string )
{
    int Index=0;
    //#bugbug:  Determinando
    int cWidth = 8;   
    //int cWidth = get_char_width ();
    //int cHeight = get_char_height ();

    //int is_transparent = transparent;  // from parameters.
    int is_transparent = TRUE;

    //#todo
    //unsigned int __fg_color = fg_color;
    //unsigned int __bg_color = bg_color;
    unsigned int __fg_color = color;
    //unsigned int __bg_color = color;

    if ( (void*) string == NULL )
        return;
    if ( *string==0 )
        return;

// #fail
// Char width
    //if ( cWidth == 0 || cHeight == 0 )
    if (cWidth == 0){
        //panic ("grDrawString: cWidth");
        //#debug
        //gde_message_box (3, "xxx","dtext-draw_string: cWidth");
        printf ("grDrawString: cWidth\n");
        while(1){
        };
    }

    //int size = sizeof(string);  
    //for ( Index=0; Index<size; Index++ )

// Draw
// see: char.c

    for ( Index=0; string[Index] != 0; Index++ )
    {
        // not transparent.
        /*
        if (is_transparent != TRUE)
        {
            grBackbufferDrawChar( 
                x, 
                y,
                string[Index],
                (unsigned int) __fg_color,     // fg color
                (unsigned int) __bg_color );   // bg color
        }
        */
        
        // transparent
        //if (is_transparent == TRUE)
        //{
            //grBackbufferDrawCharTransparent ( 
            //    x, y, 
            //    (unsigned int) __fg_color, 
            //    string[Index] );
            grBackbufferDrawCharTransparent2 ( 
                x, y, 
                (unsigned int) __fg_color, 
                string[Index],
                font_lt8x8); //gws_currentfont_address );
         //}

        // gradient
        //if( string_flags & ? ){
        //grBackbufferDrawCharTransparent ( 
            //x, y, 
            //(unsigned int) interpolate_color(COLOR_BLACK, __fg_color, x), 
            //string[Index] );
        //}

        x += cWidth;
    };
}

/* 
 * dtextDrawText:
 *     Draw text on a window.
 * #test: 
 *     Como opção, se nenhuma janela for especificada, 
 *     então pintaremos na janela principal.
 */
void 
dtextDrawText ( 
    struct gws_window_d *window,
    unsigned long x,
    unsigned long y,
    unsigned int color,
    unsigned char *string )
{ 
    struct gws_window_d * __w;

// #bugbug
// Is gui a valid pointer?

    //if ( (void*) gui == NULL )
        //return;

    __w = (struct gws_window_d *) gui->screen_window;


    if( (void*) string == NULL )
        return;
    if( *string==0 )
        return;

    if ( (void *) window == NULL ){

        if ( (void*)__w != NULL )
        {
            // #todo: We need a parameter for transparent or not.
            grDrawString ( 
                (__w->left +x), 
                (__w->top  +y), 
                (unsigned int) color, 
                string );
            return;
        }
        
        // #fail
        gwssrv_debug_print("dtextDrawText: __w\n");
        return;

    }else{

        // #todo: We need a parameter for transparent or not.
        grDrawString ( 
            (window->left +x), 
            (window->top  +y), 
            (unsigned int) color, 
            string );
    };
}


