
// mouse.c
// ps/2 mouse support.
// ring 0, kernel base.
// Created by Fred Nora.

#include <kernel.h>

// ps/2 mouse irq handler.
__VOID_IRQ 
irq12_MOUSE (void)
{
    // If ps2 mouse isn't initialized yet.
    if ( PS2.mouse_initialized != TRUE ){
        in8(0x60);
        return;
    }

// Disable keyboard port.
// Call the main routine.
// Reanable keyboard port.
// See: ps2mouse.c

    wait_then_write(0x64,0xAD);
    DeviceInterface_PS2Mouse();
    wait_then_write(0x64,0xAE);
}

