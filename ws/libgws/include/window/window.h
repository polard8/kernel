/*
 * File: window.h
 * 
 * 
 *     This header should be included by including "gws.h".
 */

#ifndef  __LIBGWS_WINDOW_H
#define  __LIBGWS_WINDOW_H    1


//button state
#define BS_NULL     0 
#define BS_DEFAULT  1
#define BS_FOCUS    2
#define BS_PRESS    3
#define BS_HOVER    4
#define BS_DISABLED 5
#define BS_PROGRESS 6
//...


// The window manager needs to get some information
// about the window.

struct gws_window_info_d
{
    //int window;
    int type;
    unsigned long width;
    unsigned long height;
    unsigned long border_width;
    // ...
};



#endif    


//
// End.
//



