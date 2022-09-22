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

    int used;
    int magic;

    int wid;   // The window id.
    int pwid;  // The wid of the parent.

    int type;

// Relative to the parent.
    unsigned long left;
    unsigned long top;
    unsigned long width;
    unsigned long height;

// Relative to the parent.
    unsigned long right;
    unsigned long bottom;

// Client rectangle.
// Se a janela tem um client rect, 
// so we can save the values here.
// This when querying the window's info
// we also get all the client area info.
    unsigned long cr_left;
    unsigned long cr_top;
    unsigned long cr_width;
    unsigned long cr_height;

    unsigned long border_width;

    // ...
};


//struct gws_window_info_d  RootWindowInfo;
// ...



#endif    


//
// End.
//



