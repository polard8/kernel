
//kgwm.h

// Registrar um window manager.
int kgwmRegisterWindowManager( int pid );



// Mouse dialog.
unsigned long
kgwm_mouse_dialog ( struct window_d *window,
                    int msg,
                    unsigned long long1,
                    unsigned long long2 );

// controles de janela.
unsigned long
kgwm_window_control_dialog ( struct window_d *window,
                             int msg,
                             unsigned long long1,
                             unsigned long long2 );





