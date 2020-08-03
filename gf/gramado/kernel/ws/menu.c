/*
 * File: menu.c 
 *
 *    Deprecated.
 *    No more menubar support for ring 0.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2020 - Deprecated.
 */

#include <kernel.h>

/*
 * create_menu:
 *     Deprecated.
 */
void *create_menu ( 
    struct window_d *pwindow,    // Parent window. 
    unsigned long iCount,        // Contagem de ítems. 
    unsigned long sCount,        // Contagem de espaçadores.
    int type,                    // Horizontal ou vertical
    int style )                  // Estilo.
{
    debug_print ("create_menu: Deprecated\n");
    return NULL;
}

/*
 * create_menu_item:
 *     Deprecated.
 */
int 
create_menu_item ( 
    struct menu_d *menu, 
    unsigned char *string, 
    int status )
{
    debug_print ("create_menu_item: Deprecated\n");
    return (int) -1;
}

/*
 * set_current_menu:
 */
void set_current_menu ( struct menu_d *menu )
{
    debug_print ("set_current_menu: Deprecated\n");
}

/*
 * get_current_menu:
 */
void *get_current_menu (void)
{
    debug_print ("get_current_menu: Deprecated\n");
    return NULL;
}

/*
 * RegisterMenu:
 *     Deprecated.
 */
int RegisterMenu ( struct menu_d *menu )
{
    debug_print ("RegisterMenu: Deprecated\n");
    return (int) -1;
}

/*
 * initmenuArray:
 *      Deprecated.
 */
void initmenuArray ( struct menu_d *a, int initialSize )
{
    debug_print ("initmenuArray: Deprecated\n");
}

/*
 * ControlMenu:
 *     Deprecated.
 */
int ControlMenu (struct window_d *window)
{
    debug_print ("ControlMenu: Deprecated\n");
    return (int) -1;
}

/*
 * MainMenu:
 *     Deprecated.
 */
int MainMenu (struct window_d *window)
{
    debug_print ("MainMenu: Deprecated\n");
    return (int) -1;
}

/*
 * MainMenuProcedure:
 *     Deprecated.
 */
unsigned long 
MainMenuProcedure( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 ) 
{
    debug_print ("MainMenuProcedure: Deprecated\n");
    return (unsigned long) 0;
}

/*
 * init_menus:
 *     Deprecated.
 */

// #bugbug
// We will keep the list initialization to avoid problems.

int init_menus (void)
{
    debug_print ("init_menus: [Deprecated] \n");
    
    //++
    int i=0;
    for ( i=0; i < MENU_COUNT_MAX; i++ )
    {
        menuList[i] = (unsigned long) 0;
    };
    set_current_menu (NULL);
    menus_count = 0;
    return 0;
    //--
}


//
// End.
//

