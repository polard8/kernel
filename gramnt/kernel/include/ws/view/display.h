
// File: x/display.h


#ifndef ____DISPLAY_H
#define ____DISPLAY_H


// Syntax: The environment variable
// hostname:Displaynumber.Screennumber
// A display consists (simplified) of: a keyboard, a mouse and a screen.
// Ok ... o window server vai solicitar as informaçoes daqui 
// e somente ele.

//
// == Display ==============================
//


// What desktop own the display. (monitor)
// #bugbug: estamos presumindo apenas um monitor.
// We are talking about the memory in the graphics card.
// Access to that memory.
// What display ? We only have one?
// Precisamos de estrutura de display que tera um elemento desktop.
// O window server em ring3 podera solicitar informaçoes daqui.




struct display_d
{
    int used;
    int magic;
    
    int id;
    
    // What desktop owns this display
    struct desktop_d *desktop;
    
    struct display_d *next;
};

//struct display_d *CurrentDisplay;



#endif    




