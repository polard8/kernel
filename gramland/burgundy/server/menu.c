
// menu.c

#include "gwsint.h"

int is_menu_active=FALSE;

// Chamado na hora de inicializar ou finaliza o menu.
int on_menu(void)
{

    if ( (void*)__root_window == NULL )
        return -1;

    if (__root_window->magic != 1234){
        return -1;
    }

// cria o menu
// Se não tem o context menu. Então cria.

    if ( (void*) __root_window->contextmenu == NULL ){
        create_main_menu(0,0);
        return 0;
    }

// para de usar o menu
// Se temos o menu e temos a janela do menu.
// repinta ela e mostra.

    struct gws_window_d *mw;

    mw = (struct gws_window_d *) __root_window->contextmenu->window;
    
    if( (void*) mw != NULL )
    {
        if (mw->magic == 1234)
        {
            is_menu_active = FALSE;
            wm_update_desktop(TRUE);
            //redraw_window(
            //    __root_window->contextmenu->window, 
            //    TRUE ); 
            return 0;
        }
        return -1;
    }

    return -1;
}


// #test
// Window server's widget.
// ::: The context menu for the root window.
int create_main_menu(int position_x, int position_y)
{
    struct gwssrv_menu_d *menu;

// --------------------------------------

    //unsigned long menux = (unsigned long) (position_x & 0xFFF);
    //unsigned long menuy = (unsigned long) (position_y & 0xFFF);
    unsigned long menux = 4;
    unsigned long menuy = 4;
// menuy
    if (WindowManager.initialized == TRUE)
    {
        menuy = 
            (unsigned long)( WindowManager.wa_top + 
                             WindowManager.wa_height -
                             200 );
    }

    // #test
    // On corner of active window
    if ( (void*) active_window != NULL )
    {
        if(active_window->magic == 1234)
        {
            if (active_window->type == WT_OVERLAPPED)
            {
                menux = (active_window->left +3);
                menuy = (active_window->top  +25);
            }  
        }
    }


// --------------------------------------

    if ( (void*) gui == NULL )
        return -1;
    if ( (void*) gui->screen_window == NULL )
        return -1;

    // #testing (NEW)
    menu = 
        (struct gwssrv_menu_d *) gwssrv_create_menu (
            (int) gui->screen_window,  //parent
            (int) 0,   //highlight
            (int) 4,   //count
            (unsigned long) menux,
            (unsigned long) menuy,
            (unsigned long) 200,
            (unsigned long) 200,
            (unsigned long) COLOR_WHITE );

    if ( (void*) menu == NULL ){
        return -1;
    }

//menu item 0
    gwssrv_create_menu_item (
        "F1 - Minimize",
        (int) 0,
        (struct gwssrv_menu_d *) menu );

//menu item 1
    gwssrv_create_menu_item (
        "F2 - Maximize",
        (int) 1,
        (struct gwssrv_menu_d *) menu );

//menu item 2
    gwssrv_create_menu_item (
        "F3 - Close",
        (int) 2,
        (struct gwssrv_menu_d *) menu );

//menu item 3
    gwssrv_create_menu_item (
        "F4 - Close menu",
        (int) 3,
        (struct gwssrv_menu_d *) menu );  

//show
    if ( (void*) menu->window != NULL )
        gws_show_window_rect(menu->window);

// global
    if ( (void*) __root_window != NULL )
    {
        if(__root_window->magic == 1234)
        {
            __root_window->contextmenu = (struct gwssrv_menu_d *) menu;
            __root_window->contextmenu->in_use = TRUE;
        
            is_menu_active=TRUE;
        }
    }

    return 0;
}


// Create menu item
struct gwssrv_menu_item_d *gwssrv_create_menu_item (
    char *label,
    int id,
    struct gwssrv_menu_d *menu)
{
    struct gwssrv_menu_item_d *item;
    struct gws_window_d       *window;  //menu item window

    //gwssrv_debug_print("gwssrv_create_menu_item:\n");    
    
    if ( (void *) menu == NULL ){
        return (struct gwssrv_menu_item_d *) 0;
    }
    
    //create menu item.
    item = (struct gwssrv_menu_item_d *) malloc( sizeof(struct gwssrv_menu_item_d) );

    if ( (void *) item == NULL ){
        return (struct gwssrv_menu_item_d *) 0;
    }

    //provisório
    if(id>5 || id>menu->itens_count)
        return (struct gwssrv_menu_item_d *) 0;


    item->id = id;

    item->width  = (menu->width -8);
    item->height = (menu->height / menu->itens_count);
    item->x      = 4;
    item->y      = (item->height*id);

// A janela do menu.
    if(menu->window == NULL){
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
        menu->window, 
        0, 
        COLOR_GRAY, 
        COLOR_GRAY );    

    if ( (void*) window == NULL ){
        item->window = NULL;
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

// The window this window belongs to.
    item->window = window;

//ok
    return (struct gwssrv_menu_item_d *) item;
fail:
    return (struct gwssrv_menu_item_d *) 0;
}


struct gwssrv_menu_d *gwssrv_create_menu (
    struct gws_window_d *parent,
    int highlight,
    int count,
    unsigned long x,
    unsigned long y,
    unsigned long width,
    unsigned long height,
    unsigned int color )
{
    struct gwssrv_menu_d  *menu;
    struct gws_window_d    *window;

    //gwssrv_debug_print("gwssrv_create_menu:\n");

    menu = (struct gwssrv_menu_d *) malloc( sizeof(struct gwssrv_menu_d) );
    if ( (void *) menu == NULL ){
        gwssrv_debug_print("gwssrv_create_menu: [FAIL] menu\n");
        return (struct gwssrv_menu_d *) 0;
    }

// Deslocamento em relação a janela mãe.
    menu->x = x;
    menu->y = y;
    menu->width  = width;
    menu->height = height;
    
    menu->color=color;
    menu->highlight = highlight;
    menu->itens_count = count;

    window = 
        (struct gws_window_d *) CreateWindow ( 
            WT_SIMPLE, 
            0,  //style
            1,  //status
            1,  //view
            "menu-bg",  
            menu->x, menu->y, menu->width, menu->height,   
            (struct gws_window_d *) parent, 
            0, 
            color, 
            color ); 

    if ( (void *) window == NULL ){
        gwssrv_debug_print ("gwssrv_create_menu: window fail\n");  
        return NULL;
    }

//#todo register
    int m_wid=-1;
    m_wid = RegisterWindow(window);
    if(m_wid<0){
        return NULL;
    }

// This window is a menu.
    window->isMenu = TRUE;

// Save window pointer.
    menu->window = window; 
    menu->parent = parent;

    //menu->used = TRUE;
    //menu->magic = 1234;

    return (struct gwssrv_menu_d *) menu;
}




// checa se o mouse esta passando sobre o main menu.
int __is_inside_menu(struct gwssrv_menu_d *menu, int x, int y)
{

// #todo
// Para as janelas do menu precisamos considerar
// a parent window para encontrarmos o 
// deslocamento correto.

    struct gwssrv_menu_d *m;

    struct gws_window_d *pw;
    struct gws_window_d *mw;

    m = (struct gwssrv_menu_d *) menu;

    if( (void*)m==NULL )
        return -1;

// parent window
    pw = m->parent;
    if( (void*)pw == NULL )
        return -1;

// menu window
    mw = m->window;
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



int gwssrv_get_number_of_itens (struct gwssrv_menu_d *menu)
{
    if ( (void*) menu == NULL ){
        return -1;
    }

    return (int) menu->itens_count;
}


/*
struct gwssrv_menu_item_d *gwssrv_get_menu_item(struct gwssrv_menu_d *menu, int i);
struct gwssrv_menu_item_d *gwssrv_get_menu_item(struct gwssrv_menu_d *menu, int i)
{
     //return (struct gwssrv_menu_item_d *) ?;
}
*/


/*
int gwssrv_redraw_menuitem(struct gwssrv_menu_item_d *);
int gwssrv_redraw_menuitem(struct gwssrv_menu_item_d *)
{
}
*/


/*
int gwssrv_redraw_menu ( struct gwssrv_menu_d *menu );
int gwssrv_redraw_menu ( struct gwssrv_menu_d *menu )
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

    //printf("menuProcedure:\n");

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

    switch (msg){
    case GWS_SysKeyUp:
        if (long1==VK_F1){
            printf("F1\n");
            return 1;
        }
        if (long1==VK_F2){
            printf("F2\n");
            return 2;
        }
        if (long1==VK_F3){
            printf("F3\n");
            return 3;
        }
        if (long1==VK_F4){
            printf("F4\n");
            return 4;
        }
        break;
    default:
        break;
    };

    return -1;
}


