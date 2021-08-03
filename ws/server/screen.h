
#ifndef ____SCREEN_H
#define ____SCREEN_H    1



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


// The device screen.
// The refresh is called by refresh_device_screen();
// It is called explicit by the app.
struct gws_screen_d *DeviceScreen;



//
// == prototypes ================================
//


// Refresh the device screen
void refresh_screen(void);

// Refresh the device screen
void refresh_device_screen(void);

// Refresh the valid screen
void refresh_valid_screen(void);


#endif    











