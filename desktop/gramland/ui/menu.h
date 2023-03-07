
// menu.h

#ifndef GWS_MENU_H
#define GWS_MENU_H    1

// Menu item types
#define MI_TYPE_SEPARATOR  1000
#define MI_TYPE_TEXT       2000


#define MAINMENU_BUTTONS_MAX  5
extern int mainmenu_buttons_count;  
extern int mainmenu_buttons[MAINMENU_BUTTONS_MAX];


// menu item
struct gws_menu_item_d
{
    int id;
    int selected;

    unsigned int color;

    // Relative
    unsigned long x;
    unsigned long y;
    unsigned long width;
    unsigned long height;
    struct gws_window_d *bg_window;
    struct gws_menu_item_d *next;
};

// menu
struct gws_menu_d
{
// TRUE = the menu procedure is running at the moment.
    int in_use;

    unsigned int color;

// Número do item em destaque.
    int highlight;  
    // Relative
    unsigned long x;
    unsigned long y;
    unsigned long width;
    unsigned long height;
// Background window.
    struct gws_window_d *bg_window;
// The window that this menu belongs to.
    struct gws_window_d *owner_window;
// List of items.
    int itens_count;
    struct gws_menu_item_d *list;
};
extern struct gws_menu_d *main_menu;

//
// == Prototypes ==============================================
//


// checa se o mouse esta passando sobre o menu.
int __is_inside_menu(struct gws_menu_d *menu, int x, int y);

int gwssrv_get_number_of_itens (struct gws_menu_d *menu);

struct gws_menu_item_d *gwssrv_create_menu_item (
    char *label,
    int id,
    struct gws_menu_d *menu);

struct gws_menu_d *gwssrv_create_menu (
    struct gws_window_d *parent,
    int highlight,
    int count,
    unsigned long x,
    unsigned long y,
    unsigned long width,
    unsigned long height,
    unsigned int color );

int redraw_main_menu(void);
int create_main_menu(void);

int
menuProcedure(
    struct gws_window_d *window,
    int msg,
    unsigned long long1,
    unsigned long long2 );

#endif    


