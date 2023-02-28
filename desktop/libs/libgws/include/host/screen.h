/*
 * File: screen.h
 * 
 * 
 *     This header should be included by including "gws.h".
 */


#ifndef __LIBGWS_SCREEN_H
#define __LIBGWS_SCREEN_H  1


struct gws_screen_d
{
    int id;
    int used;
    int magic;
    
    unsigned long width;
    unsigned long height;
    //bpp?

    unsigned long font_size;

    unsigned long char_width; 
    unsigned long char_height;
    
    void *backbuffer;
    void *frontbuffer;

    // Belongs to this display.
    struct gws_display_d *display;

    struct gws_screen_d *next;
};


#endif    


