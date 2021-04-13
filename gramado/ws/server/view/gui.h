

#ifndef ____GUI_H
#define ____GUI_H    1

struct gui_d 
{

    // Janela do dispositivo.
    // Podemos ter um ponteiro para isso em display.
    struct gws_window_d  *screen_window;

    // Área de trabalho.
    struct gws_window_d  *main_window;

    //  screen
    struct gws_screen_d  *_screen;

    // The current display.
    struct gws_display_d *_display;
};

struct gui_d *gui;


#endif   



