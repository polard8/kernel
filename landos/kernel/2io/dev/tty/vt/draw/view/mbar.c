/*
 * File: menubar.c
 *    Deprecated.
 *    No more menubar support for ring 0.
 * History:
 *     2015 - Created by Fred Nora.
 *     2020 - Deprecated.
 */


#include <kernel.h>


// Deprecated.
void *create_menubar ( struct window_d *pwindow )
{
    debug_print ("create_menubar: Deprecated\n");
    return NULL;
}

// Deprecated. 
int 
create_menubar_item ( 
    struct menu_d *menu, 
    unsigned char *string, 
    int status )
{
    debug_print ("create_menubar_item: Deprecated\n");
    return -1;
}

int select_menubar_item (int n)
{
    debug_print ("select_menubar_item: Deprecated\n");
    return -1;
}

int unselect_menubar_item (int n)
{
    debug_print ("unselect_menubar_item: Deprecated\n");
    return -1;
}

int redraw_menubar_item (int n)
{
    debug_print ("redraw_menubar_item: Deprecated\n");
    return -1;
}

int get_menubar_selected_item (void)
{
    debug_print ("get_menubar_selected_item: Deprecated\n");
    return -1;
}

// Deprecated.
int kgws_create_menubar ( struct window_d *window )
{
    debug_print ("kgws_create_menubar: Deprecated\n");
    return -1;
}

// Deprecated.
unsigned long 
MenuBarProcedure ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 ) 
{
    debug_print ("MenuBarProcedure: Deprecated\n");
    return (unsigned long) 0;
}


//
// End.
//

