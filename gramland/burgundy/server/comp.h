
// comp.h

#ifndef __COMP_H
#define __COMP_H    1

extern int __compose_lock;

void gwssrv_show_backbuffer (void);

int flush_window (struct gws_window_d *window);
int flush_window_by_id(int wid);
void flush_frame(void);
void wmRefreshDirtyRectangles(void);

void 
wmCompose(
    unsigned long jiffies, 
    unsigned long clocks_per_second );

int gws_show_window_rect (struct gws_window_d *window);

void set_refresh_pointer_status(int value);

long comp_get_mouse_x_position(void);
long comp_get_mouse_y_position(void);
void compose(void);
void comp_set_mouse_position(long x, long y);
void comp_initialize_mouse(void);
void mouse_at(void);

#endif    


