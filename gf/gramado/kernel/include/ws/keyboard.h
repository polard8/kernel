/*
 * File: keyboard.h
 *     Header para driver de teclado.
 */
 
 
 
#ifndef ____KEYBOARD_H
#define ____KEYBOARD_H


#define KEYBOARD_DRIVER_VERSION "0.1"

//
// OBS:
// ISSO PODE FICAR FORA DO KERNEL BASE ... NO DRIVER;
//


static int __has_e0_prefix = 0;
static int __has_e1_prefix = 0;
//...


void abnt2_keyboard_handler (void);

//Kernel Base driver.
void KiKeyboard (void);    

unsigned long get_scancode (void);


unsigned long 
__local_ps2kbd_procedure ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 ); 


#endif   


//
// End.
//

