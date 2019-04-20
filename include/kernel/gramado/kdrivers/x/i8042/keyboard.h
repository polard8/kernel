/*
 * File: keyboard.h
 *     Header para driver de teclado.
 */
 

#define KEYBOARD_DRIVER_VERSION "0.1"

//
// OBS:
// ISSO PODE FICAR FORA DO KERNEL BASE ... NO DRIVER;
//


void abnt2_keyboard_handler (void);


//Kernel Base driver.
void KiKeyboard (void);    


unsigned long get_scancode (void);


//
// End.
//

