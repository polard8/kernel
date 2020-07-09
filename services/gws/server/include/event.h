

struct gws_keyboard_event_d
{
    int dummy;
};

struct gws_mouse_event_d
{
    int dummy;
};


struct gws_window_event_d
{
    int dummy;
};


struct gws_event_d
{
    struct gws_keyboard_event_d  *kEvent;
    struct gws_mouse_event_d     *mEvent;
    struct gws_window_event_d    *wEvent;
    // ...
    
    struct gws_event_d *next;
};

//#test
// Main structure for event.
struct gws_event_d gwsEvent;

//#test
struct gws_event_d *gwsCurrentEvent;
