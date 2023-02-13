
// comp.c

#include "gwsint.h"

// The call back can't use the compose()
// if the window server is using it at the moment.
int __compose_lock = FALSE;

extern struct gws_window_d *mouse_hover;


// #todo
// Create some configuration globals here
// int gUseSomething = TRUE;
// ...

//old
static long __old_mouse_x=0;
static long __old_mouse_y=0;
//current
static long __new_mouse_x=0;
static long __new_mouse_y=0;
static int __mouse_initialized = FALSE;

static int refresh_pointer_status= FALSE;

static void draw_mouse_pointer(void);


// --------------------------

void set_refresh_pointer_status(int value)
{
    if (value != FALSE && value != TRUE)
        return;
    refresh_pointer_status = value;
}


// Onde esta o mouse? em que janela?
// simple implementation.
// get the old one in the 32bit version of gramado.

void mouse_at(void)
{
    register int i=0;
    struct gws_window_d *w;
    for (i=0; i<WINDOW_COUNT_MAX; i++)
    {
        w = (void*) windowList[i];
        if ( (void*) w != NULL )
        {
            if (w->magic == 1234)
            {
                if ( __new_mouse_x > w->left &&
                     __new_mouse_x < w->right &&
                     __new_mouse_y > w->top &&
                     __new_mouse_y > w->bottom )
                {
                    if (w != __root_window)
                    {
                        mouse_hover = (void *) w;
                        //redraw_window(w,TRUE);
                    }
                }
            }
        }
    };
}

long comp_get_mouse_x_position(void)
{
    return (long) __new_mouse_x;
}

long comp_get_mouse_y_position(void)
{
    return (long) __new_mouse_y;
}

static void draw_mouse_pointer(void)
{

// #todo: 
// print directly into the lfb.
// DRAW
    frontbuffer_draw_rectangle( 
        (unsigned long) __new_mouse_x, 
        (unsigned long) __new_mouse_y, 
        (unsigned long) 8, 
        (unsigned long) 8, 
        COLOR_RED, 
        0 );
}

// + Apaga o cursor antigo, copiando o conteudo do backbuffer
// + Pinta o novo cursor diretamente no lfb.
void __display_mouse_cursor(void)
{
    if ( (void*) window_server == NULL )
        return;
    if (window_server->initialized != TRUE )
        return;

// #todo Limits
// Precisa inicializar os valores sobre o mouse.
// Precisa criar uma estrura pra eles.

    if ( __old_mouse_x<0 ){ __old_mouse_x=0; }
    if ( __old_mouse_y<0 ){ __old_mouse_y=0; }

    if ( __new_mouse_x<0 ){ __new_mouse_x=0; }
    if ( __new_mouse_y<0 ){ __new_mouse_y=0; }

//------
//#dangerdanger
//#todo: show the backbuffer

// Apaga se houve algum evento, como movimento.
    if (refresh_pointer_status == TRUE)
    {
        gws_refresh_rectangle( __old_mouse_x, __old_mouse_y, 16, 16 );
        set_refresh_pointer_status(FALSE);
    }

// save
    __old_mouse_x = __new_mouse_x;
    __old_mouse_y = __new_mouse_y;

// Draw direcly into the lfb.
    draw_mouse_pointer();
//------ 
}


// Flush
// The compositor.
// Called by wmCompose
void compose(void)
{
// Called by wmCompose() and callback_compose().

    static int Dirty = FALSE;

// fps++
    if (WindowManager.initialized == TRUE){
        WindowManager.frame_counter++;
    }

// Backgroud
// If the background is marked as dirty, 
// we flush it, validate it, show the cursor and return.
    Dirty = (int) is_background_dirty();
    if (Dirty == TRUE)
    {
        gws_show_backbuffer();
        validate_background();  
        return;
    }

// Rectangles
// Refresh the rectangles of the windows.
    wmRefreshDirtyRectangles();

//
// #suspended
//

// mouse
// Show the cursor in the screen.
// remember: we're using 15 fps refresh,
// we can change this in the kernel.

    if (gUseMouse == TRUE){
        __display_mouse_cursor();
    }

// Validate the frame.
    validate_background();
    validate();
// fps
    //__update_fps();

    // return;
}


// global
void comp_initialize_mouse(void)
{
    unsigned long w = gws_get_device_width();
    unsigned long h = gws_get_device_height();

    int hotspotx=0;
    int hotspoty=0;
    if(w>=0 && w<=800)
        hotspotx = (w >> 1);
    if(h>=0 && h<=800)
        hotspoty = (h >> 1);

    __old_mouse_x = hotspotx;
    __old_mouse_y = hotspoty;
    __new_mouse_x = hotspotx;
    __new_mouse_y = hotspoty;

    __mouse_initialized = TRUE; 

// CONFIG:
    //gUseMouse = TRUE;
    gUseMouse = FALSE;
}

// global
// Set new mouse position.
void comp_set_mouse_position(long x, long y)
{
    unsigned long w = gws_get_device_width();
    unsigned long h = gws_get_device_height();
    if( x<0 ){ x=0; }
    if( y<0 ){ y=0; }
    if( x>w ){
         x=w;
    }
    if( y>h){
        y=h;
    }
    __new_mouse_x = (long) x;
    __new_mouse_y = (long) y;
}

