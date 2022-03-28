
// kgws.h

#ifndef __KGWS_H
#define __KGWS_H    1




#define grMIN2(a, b)  (((a) < (b)) ? (a) : (b))
#define grMAX2(a, b)  (((a) > (b)) ? (a) : (b))

#define grMIN3(x,y,z)     (x < y  ? (x < z ? x : z) : (y < z ? y : z))
#define grMAX3(x,y,z)     ( (x>y) ? ((x>z)?x:z)     : ((y>z)?y:z) )

int refresh_device_screen_flag;
int refresh_valid_screen_flag;

struct gws_screen_d
{

    int id;
    int used;
    int magic;
    
    unsigned long flags;
    
    unsigned long width;
    unsigned long height;
    unsigned long bpp;    // bits per pixel

    unsigned long pitch;
    
    unsigned long hotspot_x;
    unsigned long hotspot_y;

    //origin
    unsigned long min_x;   // 0 = hot spot
    unsigned long min_y;   // 0 = hot spot
    
    unsigned long max_x;
    unsigned long max_y;

    unsigned long font_size;

    unsigned long char_width; 
    unsigned long char_height;
    
    void *backbuffer;
    void *frontbuffer;

    // Belongs to this display.
    struct gws_display_d *display;
    
    struct gws_screen_d *next;

    struct gws_window_d *root;
};

struct gws_screen_d *DeviceScreen;


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
 
 
    // #todo
    // The IP of the host where we're gonna display.
    //char IP[4];
 
 
    //#todo:
    //See: r_render.h
    //int render_mode;
    //rendermode_t render_mode;
     
 
    //#test
    //char *buffer;		//Output buffer starting address. 
    //char *bufptr;		//Output buffer index pointer. 
    //char *bufmax;		//Output buffer maximum+1 address. 

    // The device screen.
    // The refresh is called by refresh_device_screen();
    // It is called explicit by the app.
    struct gws_screen_d *device_screen;

    // The device screen.
    // The refresh is called by refresh_valid_screen();
    // It is called frequently by the window server.
    struct gws_screen_d *valid_screen;


    //#test
    //root window for the screen ??
    //struct gws_window_d *root;
    //struct gws_window_d *current;
    
    // ??
    //#test
    //struct gws_gui_d *gui;
    
    
    //...

    struct gws_display_d *next;
};
struct gws_display_d *CurrentDisplay;






//
// == prototypes =====================================
//




int init_gramado (void);


int windowLoadGramadoIcons (void);
void *ui_get_system_icon ( int n );


// ========


//
//  Compositor
//

int DemoFlag;
int UpdateScreenFlag;

// (1000/fps)=presence_level
unsigned long get_update_screen_frequency(void);
void set_update_screen_frequency(unsigned long fps);
unsigned long get_presence_level(void);
void set_presence_level(unsigned long value);
void schedulerUpdateScreen(void);

// =======================================================



int 
write_in_tty ( 
    struct tty_d *target_tty,
    struct window_d *window, 
    int message,
    unsigned long ascii_code,
    unsigned long raw_byte );

int 
postto_eventqueue( 
    int tid,
    struct window_d *window, 
    int message,
    unsigned long ascii_code,
    unsigned long raw_byte );




// ===============================

int fib (int n);

int 
grPlot0 ( 
    struct window_d *clipping_window,   
    int z, 
    int x, 
    int y, 
    unsigned int color );


void 
plotLine3d (
    int x0, int y0, int z0, 
    int x1, int y1, int z1, 
    unsigned int color );

void
rectangleZ (
    int left, int top, 
    int right, int bottom,
    unsigned int color,
    int z );

void 
plotCircleZ ( 
    int xm, 
    int ym, 
    int r, 
    unsigned int color, 
    int z );

void noraDrawingStuff3 (int x, int y, int z);
void demoFred0(void);
void demoFred1(void);

void demo0(void);

int grInit (void);

int KGWS_initialize(void);

void kgws_enable(void);
void kgws_disable(void);

int kgwsRegisterWindowServer (pid_t pid);

#endif   



