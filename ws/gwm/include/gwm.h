
/*
 * File: gwm.h 
 * 
 *     Main header file for the gwm.
 *     It uses the libgws library.
 * 
 */
 
 

// Hot spot for the mouse pointer or system menu.
struct wm_hot_spot
{
    unsigned long x;
    unsigned long y;
};
struct wm_hot_spot hot_spot;


struct wm_client_d
{
    int used;
    int magic;
    
    int window;
    int title_window;
    
    // window
    int x;
    int y;
    int w;
    int h;
    
    // title window
    int tx;
    int ty;
    int tw;
    int th;

    char name[256];

    //test
    int dirty;
    
    int focus;

    // control menu.
    struct gws_menu_d *menu;

    struct wm_client_d *next;
};


struct wm_client_d  *c_bg;
struct wm_client_d  *c_topbar;
struct wm_client_d  *c_taskbar;
struct wm_client_d  *c_tester;   // Usado para fazer testes de pintura e posicionamento.
// ...

unsigned long wmClientList[32];



unsigned long gScreenWidth;
unsigned long gScreenHeight;


//
// == Window ==========================
//

// #todo
// We need to sync these with the window server.
// This way, the window server will paint the chars in the right window.


// The active window.
int active_window;


// The window with the input focus.
// Sometimes it is a child window, and it's parent needs to be the
// active window.
int window_with_focus;

//...

#define WINDOW_COUNT_MAX 1024

unsigned long windowList[WINDOW_COUNT_MAX];


// ===============================
// register window manager
int register_wm (void);
// ===============================


//
// == Prototypes ==========================
//


int gwm_init_globals(void);

int gwm_init_windows(void);


