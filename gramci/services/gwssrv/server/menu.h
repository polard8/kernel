


struct gwsssrv_menu_item_d
{
    int id;

    //int window;
    struct gws_window_d *window;
    
    unsigned long x;
    unsigned long y;
    unsigned long width;
    unsigned long height;
    
    unsigned long color;
    
    int selected;

    struct gwsssrv_menu_item_d *next;
};


struct gwsssrv_menu_d
{

    //int window;
    //int parent;
    
    struct gws_window_d *window;
    struct gws_window_d *parent;


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























