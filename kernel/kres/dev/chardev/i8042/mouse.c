// mouse.c
// This is the ps2/mouse driver, embedded into the kernel base.
// ps/2 mouse support.
// ring 0, kernel base.
// Created by Fred Nora.

#include <kernel.h>

unsigned long g_mousepointer_width=0;
unsigned long g_mousepointer_height=0;
// Estado dos botões do mouse
int mouse_button_1=FALSE;
int mouse_button_2=FALSE;
int mouse_button_3=FALSE;
// Estado anterior dos botões do mouse.
int old_mouse_button_1=FALSE;
int old_mouse_button_2=FALSE;
int old_mouse_button_3=FALSE;
// Se ouve alguma modificação no estado dos botões.
int mouse_button_action=FALSE;

// ==============

// ps/2 mouse irq handler.
__VOID_IRQ 
irq12_MOUSE (void)
{
// If ps2 mouse isn't initialized yet.
    if (PS2.mouse_initialized != TRUE){
        in8(0x60);
        return;
    }
    PS2Mouse.irq_is_working = TRUE;
    PS2Mouse.last_jiffy = (unsigned long) get_systime_totalticks();

// Disable keyboard port.
// Call the main routine.
// Reanable keyboard port.
// See: ps2mouse.c
    wait_then_write(0x64,0xAD);
    DeviceInterface_PS2Mouse();
    wait_then_write(0x64,0xAE);
}

