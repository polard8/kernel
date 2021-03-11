/*
 * File: display.h 
 * 
 *     Display structure support.
 *     This header should be included by including "gws.h".
 */

#ifndef __LIBGWS_DISPLAY_H
#define __LIBGWS_DISPLAY_H    1


struct gws_display_d
{
    int id;
    
    int used;
    int magic;

    // #test
    //"host:display" string used on this connect
    char *display_name;
    
    int fd;    // Network socket. 
    int lock;  // is someone in critical section?  
 
    int connected;
 
    //#test
    //char *buffer;		//Output buffer starting address. 
    //char *bufptr;		//Output buffer index pointer. 
    //char *bufmax;		//Output buffer maximum+1 address. 
    
    //#test
    //only one screen for now.
    //struct gws_screen_d *screen;

    //...

    struct gws_display_d *next;
};

#endif    



