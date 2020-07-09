


struct gws_display_d
{
    int id;
    
    int used;
    int magic;

    // #test
    //"host:display" string used on this connect
    char *display_name;	
    
    int fd;    // Network socket. 
    int lock;  // is someone in critical section?  
 
    //#test
    //char *buffer;		//Output buffer starting address. 
    //char *bufptr;		//Output buffer index pointer. 
    //char *bufmax;		//Output buffer maximum+1 address. 
    
    //#test
    //only one screen for now.
    //struct gws_screen_d *screen;
    
    //#test
    //root window for the screen ??
    //struct gws_window_d *root;
    struct gws_window_d *current;
    
    // ??
    //#test
    //struct gws_gui_d *gui;
    
    
    //...

    struct gws_display_d *next;
};

//#todo
//#define GWS_DISPLAY_MAX 128;
//unsigned long displayList[GWS_DISPLAY_MAX];







