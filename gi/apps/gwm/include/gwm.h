
/*
 * File: gwm.h 
 * 
 *     Main header file for the gwm.
 *     It uses the libgws library.
 * 
 */

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


    struct wm_client_d *next;
};

struct wm_client_d *c_topbar;
struct wm_client_d *c_taskbar;
struct wm_client_d *c_tester;   // Usado para fazer testes de pintura e posicionamento.

unsigned long wmclientList[1024];



unsigned long gScreenWidth;
unsigned long gScreenHeight;



#define WINDOW_COUNT_MAX 1024

unsigned long windowList[WINDOW_COUNT_MAX];


int gwm_init_globals(void);

int gwm_init_windows(void);


