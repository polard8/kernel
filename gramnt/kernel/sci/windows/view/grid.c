/*
 * File: grid.c
 *
 *     Deprecated
 *     No more grid support in ring0.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2020 - Deprecated.
 */

#include <kernel.h>

/*
 * InitializeGridObject:
 *     Deprecated.
 */
int 
InitializeGridObject ( 
    struct window_d *window, 
    struct grid_d *g, 
    int n, 
    int view )
{
    debug_print ("InitializeGridObject: Deprecated\n");
    return (int) -1;
}

/*
 * CreateGrid:
 *     Deprecated.
 */

void *CreateGrid (void)
{
    debug_print ("CreateGrid: Deprecated\n");
    return NULL;
}

/*
 * grid:  
 */

int 
grid ( 
    struct window_d *window, 
    int n, 
    int view )
{
    debug_print ("grid.c-grid: Deprecated\n");
    return (int) -1;
}


//
// End.
//
