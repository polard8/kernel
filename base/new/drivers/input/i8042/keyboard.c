
// keyboard.c
// ps/2 keyboard support.
// See:
// https://www.gnu.org/software/libc/manual/html_node/Canonical-or-Not.html
// Created by Fred Nora.

#include <kernel.h>  

// ps/2 keyboard irq handler.
__VOID_IRQ 
irq1_KEYBOARD (void)
{
    // If ps2 keyboard isn't initialized yet.
    if ( PS2.keyboard_initialized != TRUE ){
        in8(0x60);
        return;
    }

// Disable mouse port.
// Call the main routine.
// Reenable the mouse port if ps2 mouse was initialized.
// See: ps2kbd.c

    wait_then_write(0x64,0xA7);
    DeviceInterface_PS2Keyboard();
    if ( PS2.mouse_initialized == TRUE ){
        wait_then_write(0x64,0xA8);
    }
}



