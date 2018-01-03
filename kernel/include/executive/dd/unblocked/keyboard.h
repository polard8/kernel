// keyboard.h

//isso ainda está no kernelbase, mas será um driver em user mode.


//
// 
//
//

#define KEYBOARD_DRIVER_VERSION "1.0"


//ISSO PODE FICAR FORA DO KERNEL BASE ... NO DRIVER;
void abnt2_keyboard_handler();
void KiKeyboard();    //Kernel Base driver.


