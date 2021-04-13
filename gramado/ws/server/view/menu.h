


// Menu item types
#define MI_TYPE_SEPARATOR  1000
#define MI_TYPE_TEXT       2000



struct gwsssrv_menu_item_d
{
    int id;

    struct gws_window_d *window;
    
    unsigned long x;
    unsigned long y;
    unsigned long width;
    unsigned long height;
    
    unsigned long color;
    
    int selected;

    struct gwsssrv_menu_item_d *next;
};


// menu
struct gwsssrv_menu_d
{
    struct gws_window_d  *window;
    struct gws_window_d  *parent;

    unsigned long x;
    unsigned long y;
    unsigned long width;
    unsigned long height;

    unsigned long color;
    
    int highlight; //item em destaque
    
    //list
    int itens_count;
    struct gwsssrv_menu_item_d *list;
};



//
// == Prototypes ==============================================
//

int gwssrv_get_number_of_itens (struct gwsssrv_menu_d *menu);

struct gwsssrv_menu_d *gwssrv_create_menu (
    struct gws_window_d *parent,
    int highlight,
    int count,
    unsigned long x,
    unsigned long y,
    unsigned long width,
    unsigned long height,
    unsigned long color );

struct gwsssrv_menu_item_d *gwssrv_create_menu_item (
    char *label,
    int id,
    struct gwsssrv_menu_d *menu);
    
    
//test
int create_main_menu(void);























