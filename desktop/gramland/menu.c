
// menu.c

#include "gwsint.h"


int mainmenu_buttons_count=0;
int mainmenu_buttons[MAINMENU_BUTTONS_MAX];

struct gws_menu_d *main_menu;

static const char *mn_app0 = "terminal.bin";
static const char *mn_app1 = "editor.bin";
static const char *mn_app2 = "reboot.bin";
static const char *mn_app3 = "shutdown.bin";

// ----------------

// TRUE = OK
int redraw_main_menu(void)
{
// Invalid menu. Cant redraw.
    if ( (void*) main_menu == NULL )
        return FALSE;
    if (main_menu->in_use != TRUE)
        return FALSE;

    if ( (void*) main_menu->bg_window == NULL )
        return -1;
    if (main_menu->bg_window->magic != 1234)
        return -1;

// Redraw bg window.
   //redraw_window(main_menu->bg_window,TRUE);
   redraw_window(main_menu->bg_window,FALSE);

// Redraw items.
    struct gws_menu_item_d *tmp;
    tmp = (struct gws_menu_item_d *) main_menu->list;  //First
    while (1){
        if ( (void*) tmp == NULL )
            break;
        // Redraw menu item.
        if ( (void*) tmp != NULL )
        {
            //redraw_window(tmp->bg_window,1);
            redraw_window(tmp->bg_window,FALSE);
        }
        tmp = (struct gws_menu_item_d *) tmp->next;
    };

    flush_window(main_menu->bg_window);

// ok
    StartMenu.is_visible = TRUE;
    return TRUE;
}

// #test
// Window server's widget.
// ::: The context menu for the root window.
int create_main_menu(void)
{
//

    struct gws_menu_d *menu;

    unsigned long m_left = 0;
    unsigned long m_top = 0;
    unsigned long m_width  = (WindowManager.wa_width  >> 1);
    unsigned long m_height = (WindowManager.wa_height >> 1);
    unsigned int m_color = COLOR_WHITE;

// Special width.
    if (current_mode == GRAMADO_JAIL)
    {
        m_top    = ((WindowManager.wa_height >> 1)*1);
        m_width  = (WindowManager.wa_width  >> 1);
        m_height = (WindowManager.wa_height >> 1);
    }
// Special height.
    if ( current_mode == GRAMADO_P1 || current_mode == GRAMADO_HOME)
    {
        m_top    = ((WindowManager.wa_height >> 2)*3);
        m_width  = (WindowManager.wa_width  >> 2);
        m_height = (WindowManager.wa_height >> 2);
    }

    StartMenu.is_created = FALSE;

// No window manager.
    if (WindowManager.initialized != TRUE)
        return -1;
    if (WindowManager.initialized != TRUE)
        return -1;

// No root window.
    if ( (void*) __root_window == NULL )
        return -1;
    if (__root_window->magic != 1234)
        return -1;


    register int b=0;
    for (b=0; b<MAINMENU_BUTTONS_MAX; b++){
        mainmenu_buttons[b]=0;
    };
    mainmenu_buttons_count = 0;

//
// Create the menu.
//

    menu = 
        (struct gws_menu_d *) gwssrv_create_menu (
            (struct gws_window_d *) __root_window,  // Parent window.
            (int) 0,   // Highlight
            (int) 4,   // Count. Number of items.
            (unsigned long) m_left,
            (unsigned long) m_top,
            (unsigned long) m_width,
            (unsigned long) m_height,
            (unsigned int) m_color );

    if ( (void*) menu == NULL ){
        printf("create_main_menu: menu\n");
        return -1;
    }

//
// Create menu items.
//

    struct gws_menu_item_d *tmp;

// Item 0
    tmp = 
    (struct gws_menu_item_d *) gwssrv_create_menu_item (
        "Terminal",
        (int) 0,
        (struct gws_menu_d *) menu );
// Register wid.
    if ( (void*) tmp != NULL ){
        if ( (void*) tmp->bg_window != NULL )
            mainmenu_buttons[0] = tmp->bg_window->id;
    }

// Item 1
    tmp = 
    (struct gws_menu_item_d *) gwssrv_create_menu_item (
        "Editor",
        (int) 1,
        (struct gws_menu_d *) menu );
// Register wid.
    if ( (void*) tmp != NULL ){
        if ( (void*) tmp->bg_window != NULL )
            mainmenu_buttons[1] = tmp->bg_window->id;
    }

// Item 2
    tmp = 
    (struct gws_menu_item_d *) gwssrv_create_menu_item (
        "Reboot",
        (int) 2,
        (struct gws_menu_d *) menu );
// Register wid.
    if ( (void*) tmp != NULL ){
        if ( (void*) tmp->bg_window != NULL )
            mainmenu_buttons[2] = tmp->bg_window->id;
    }

// Item 3
    tmp = 
    (struct gws_menu_item_d *) gwssrv_create_menu_item (
        "Shutdown",
        (int) 3,
        (struct gws_menu_d *) menu );  
// Register wid.
    if ( (void*) tmp != NULL ){
        if ( (void*) tmp->bg_window != NULL )
            mainmenu_buttons[3] = tmp->bg_window->id;
    }

//
// Show
// 

    if ( (void*) menu->bg_window == NULL ){
        printf("create_main_menu: menu->bg_window\n");
        return -1;
    }
    flush_window(menu->bg_window);

// The mai menu.
    main_menu = (struct gws_menu_d *) menu;
    main_menu->in_use = TRUE;

// Done
    StartMenu.is_selected = FALSE;
    StartMenu.is_visible = TRUE;
    StartMenu.is_created = TRUE;
    return 0;
}

// Create menu item
struct gws_menu_item_d *gwssrv_create_menu_item (
    char *label,
    int id,
    struct gws_menu_d *menu)
{
    struct gws_menu_item_d *item;
    struct gws_window_d    *window;  //menu item window

    //gwssrv_debug_print("gwssrv_create_menu_item:\n");    
    
    if ( (void *) menu == NULL ){
        return NULL;
    }

// Create menu item.
    item = (struct gws_menu_item_d *) malloc( sizeof(struct gws_menu_item_d) );
    if ( (void *) item == NULL ){
        return (struct gws_menu_item_d *) 0;
    }

    //provisório
    if(id>5 || id>menu->itens_count)
        return (struct gws_menu_item_d *) 0;


    item->id = id;

    item->width  = (menu->width -8);
    item->height = (menu->height / menu->itens_count);
    item->x      = 4;
    item->y      = (item->height*id);

// A janela do menu.
    if(menu->bg_window == NULL){
        return NULL;
    }

// A janela do item.
    window = 
        (struct gws_window_d *) CreateWindow ( 
        WT_BUTTON,
        0, //style
        1, //status 
        1, //view 
        (char *) label,  
        item->x, item->y, item->width, item->height,   
        menu->bg_window, 
        0, 
        COLOR_GRAY, 
        COLOR_GRAY );    

    if ( (void*) window == NULL ){
        item->bg_window = NULL;
        goto fail;
    }

//register.
    int mi_wid=-1;
    mi_wid = RegisterWindow(window);
    if(mi_wid<0){
        return NULL;
    }

// This window is a menuitem.
    window->isMenuItem = TRUE;

    item->bg_window = window;

    struct gws_menu_item_d *tmp;

    // First.
    tmp = (struct gws_menu_item_d *) menu->list;
    if ( (void*) tmp == NULL ){
        menu->list = (struct gws_menu_item_d *) item;
        // OK. Return first.
        return (struct gws_menu_item_d *) item;
    }

    register int C=0;
    while (1)
    {
        if (C>5){
            return NULL;
        }
            
        if ( (void*) tmp->next == NULL ){
            tmp->next = (struct gws_menu_item_d *) item;
            // OK. Return first.
            return (struct gws_menu_item_d *) item;
        }
        tmp = (struct gws_menu_item_d *) tmp->next;
        C++;
    };

fail:
    printf ("gwssrv_create_menu_item: Fail\n");
    return NULL;
done:
    return (struct gws_menu_item_d *) item;
}

struct gws_menu_d *gwssrv_create_menu (
    struct gws_window_d *parent,
    int highlight,
    int count,
    unsigned long x,
    unsigned long y,
    unsigned long width,
    unsigned long height,
    unsigned int color )
{
    struct gws_menu_d *menu;
    struct gws_window_d *bg_window;
    int m_wid = -1;

// Create menu object.
    menu = (struct gws_menu_d *) malloc( sizeof(struct gws_menu_d) );
    if ( (void *) menu == NULL ){
        printf("gwssrv_create_menu: menu\n");
        return NULL;
    }

    menu->in_use = FALSE;  // Not yet.

// Deslocamento em relação a janela mãe.
    menu->x = x;
    menu->y = y;
    menu->width  = width;
    menu->height = height;
    
    menu->color=color;
    menu->highlight = highlight;
    menu->itens_count = count;

//
// Background window.
//

    bg_window = 
        (struct gws_window_d *) CreateWindow ( 
            WT_SIMPLE, 
            0,  //style
            1,  //status
            1,  //view
            "menu-bg-w",  
            menu->x, menu->y, menu->width, menu->height,   
            (struct gws_window_d *) parent, 
            0, 
            color, color ); 

    if ( (void *) bg_window == NULL ){
        printf ("gwssrv_create_menu: bg_window\n");  
        return NULL;
    }

//#todo register
    m_wid = RegisterWindow(bg_window);
    if (m_wid<0){
        printf ("gwssrv_create_menu: Coudn't register bg_window\n");  
        return NULL;
    }

// This window is a menu.
    bg_window->isMenu = TRUE;

// Save window pointer.
    menu->bg_window = bg_window; 
    menu->owner_window = parent;

    menu->in_use =  TRUE;

    return (struct gws_menu_d *) menu;
}




// checa se o mouse esta passando sobre o main menu.
int __is_inside_menu(struct gws_menu_d *menu, int x, int y)
{

// #todo
// Para as janelas do menu precisamos considerar
// a parent window para encontrarmos o 
// deslocamento correto.

    struct gws_menu_d *m;

    struct gws_window_d *pw;
    struct gws_window_d *mw;

    m = (struct gws_menu_d *) menu;
    if( (void*)m==NULL )
        return -1;

// Owner.
    pw = m->owner_window;
    if( (void*)pw == NULL )
        return -1;

// menu window
    mw = m->bg_window;
    if( (void*)mw == NULL )
        return -1;

//parent
    int x1= pw->left + mw->left; 
    int x2= x1 + mw->width;
    int y1= pw->top    + mw->top;
    int y2= y1 + mw->height;

    if( x > x1 && 
        x < x2 &&
        y > y1 && 
        y < y2 )
    {
        return TRUE;
    }

    return FALSE;
}



int gwssrv_get_number_of_itens (struct gws_menu_d *menu)
{
    if ( (void*) menu == NULL ){
        return -1;
    }

    return (int) menu->itens_count;
}


/*
struct gws_menu_item_d *gwssrv_get_menu_item(struct gws_menu_d *menu, int i);
struct gws_menu_item_d *gwssrv_get_menu_item(struct gws_menu_d *menu, int i)
{
     //return (struct gws_menu_item_d *) ?;
}
*/


/*
int gwssrv_redraw_menuitem(struct gws_menu_item_d *);
int gwssrv_redraw_menuitem(struct gws_menu_item_d *)
{
}
*/


/*
int gwssrv_redraw_menu ( struct gws_menu_d *menu );
int gwssrv_redraw_menu ( struct gws_menu_d *menu )
{
    int i=0;
    int n=0;

    if ( (void*) menu == NULL )
        return -1;
    
    n = (int) gwssrv_get_number_of_itens(menu);

    if ( n<=0 )
        return -1;
    
    for (i=0; i<n; i++)
    {
        mi = gwssrv_get_menu_item(i,menu);
        gwssrv_redraw_menuitem(mi);
    };
}
*/



int
menuProcedure(
    struct gws_window_d *window,
    int msg,
    unsigned long long1,
    unsigned long long2 )
{
    int Status=FALSE;

    char filename[16];
    size_t string_size=0;

    //printf("menuProcedure:\n");

    memset(filename,0,16);

    /*
    // ok, it is working
    Status = __is_inside_menu(main_menu,long1,long2);
    if(Status==FALSE)
        yellow_status("Out ");
    if(Status==TRUE)
        yellow_status("In ");
    */

    if(msg<0)
        return -1;

    int item = (int) (long1 & 0xFFFF);
    int _i0 = (int) (mainmenu_buttons[0] & 0xFFFF);
    int _i1 = (int) (mainmenu_buttons[1] & 0xFFFF);
    int _i2 = (int) (mainmenu_buttons[2] & 0xFFFF);
    int _i3 = (int) (mainmenu_buttons[3] & 0xFFFF);

    if (item == _i0){
        sprintf(filename,mn_app0);
        string_size = strlen(mn_app0);
        filename[string_size] = 0;
        rtl_clone_and_execute(filename);
        return 0;
    }
    if (item == _i1){
        sprintf(filename,mn_app1);
        string_size = strlen(mn_app1);
        filename[string_size] = 0;
        rtl_clone_and_execute(filename);
        return 0;
    }
    if (item == _i2){
        sprintf(filename,mn_app2);
        string_size = strlen(mn_app2);
        filename[string_size] = 0;
        rtl_clone_and_execute(filename);
        return 0;
    }
    if (item == _i3){
        //sprintf(filename,mn_app3);
        //string_size = strlen(mn_app3);
        //filename[string_size] = 0;
        //rtl_clone_and_execute(filename);
        gwssrv_quit();
        return 0;
    }

    return 0;
}


