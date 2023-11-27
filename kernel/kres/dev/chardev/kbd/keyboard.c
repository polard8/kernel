
// keyboard.c
// ps/2 keyboard support.
// See:
// https://www.gnu.org/software/libc/manual/html_node/Canonical-or-Not.html
// Created by Fred Nora.

#include <kernel.h>


// Status
// @todo: Status pode ser (int).
// variáveis usadas pelo line discipline para controlar o 
// estado das teclas de controle.
// #todo: talvez isso possa ir pra dentro da estrutura 
// de teclado ps2.
unsigned long key_status=0;
unsigned long escape_status=0;
unsigned long tab_status=0;
unsigned long winkey_status=0;
unsigned long ctrl_status=0;
unsigned long alt_status=0;
unsigned long shift_status=0;
unsigned long capslock_status=0;
unsigned long numlock_status=0;
unsigned long scrolllock_status=0;
//...

// ==================================

// ps/2 keyboard irq handler.
__VOID_IRQ 
irq1_KEYBOARD (void)
{
// If ps2 keyboard isn't initialized yet.
    if (PS2.keyboard_initialized != TRUE){
        in8(0x60);
        return;
    }
    PS2Keyboard.irq_is_working = TRUE;
    PS2Keyboard.last_jiffy = 
        (unsigned long) get_systime_totalticks();

// Disable mouse port.
// Call the main routine.
// Reenable the mouse port if ps2 mouse was initialized.
// See: ps2kbd.c
    wait_then_write(0x64,0xA7);
    DeviceInterface_PS2Keyboard();
    if (PS2.mouse_initialized == TRUE){
        wait_then_write(0x64,0xA8);
    }
}



