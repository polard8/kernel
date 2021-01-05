
//kgwm.h

#ifndef __KGWM_H
#define __KGWM_H    1


#define KGWM_SINGLE    1000
#define KGWM_DOUBLE    2000
#define KGWM_TRIPLE    3000 
#define KGWM_QUAD      4000

int kgwm_mode;


// Registrar um window manager.
int kgwmRegisterWindowManager( int pid );



// Mouse dialog.
unsigned long
kgwm_mouse_dialog ( 
    struct window_d *window,
    int msg,
    unsigned long long1,
    unsigned long long2 );

// controles de janela.
unsigned long
kgwm_window_control_dialog ( 
    struct window_d *window,
    int msg,
    unsigned long long1,
    unsigned long long2 );


#endif    


