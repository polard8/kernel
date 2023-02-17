

// painter.h

#ifndef __PAINTER_H
#define __PAINTER_H    1

void 
__draw_button_borders(
    struct gws_window_d *w,
    unsigned int color1,
    unsigned int color2,
    unsigned int color2_light,
    unsigned int outer_color );

//worker: no checks
void 
__draw_window_border( 
    struct gws_window_d *parent, 
    struct gws_window_d *window );

void begin_paint(struct gws_window_d *window);
void end_paint(struct gws_window_d *window);

int clear_window_by_id(int wid, unsigned long flags);

void invalidate_root_window(void);
void invalidate_taskbar_window(void);
void invalidate_window (struct gws_window_d *window);
void invalidate_window_by_id( int wid );

int 
redraw_window (
    struct gws_window_d *window, 
    unsigned long flags ); 
int redraw_window_by_id(int wid, unsigned long flags);

int 
update_window ( 
    struct gws_window_d *window, 
    unsigned long flags );

void validate_window (struct gws_window_d *window);

void wm_flush_rectangle(struct gws_rect_d *rect);
void wm_flush_screen(void);
void wm_flush_window(struct gws_window_d *window);


#endif    


