/*
 * File: display.h 
 * 
 *     Display structure support.
 *     This header should be included by including "gws.h".
 */

#ifndef __LIBGWS_DISPLAY_H
#define __LIBGWS_DISPLAY_H    1


// #??
// Podemos ter um buffer de request dentro da estrutura de display.
// Isso é melhor que um buffer global solto,
// Dessa forma cada display pode ter seus próprios buffers.

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

    // ...

    //char *request_buffer;
    //char *reply_buffer;

    struct gws_display_d *next;
};


//
// The current display
//

struct gws_display_d *libgwsCurrentDisplay;

int gws_set_current_display ( struct gws_display_d *display );


#endif    




