// gramk.c
// Wrappers for the gramk/ kernel components.
// This is a safer way to call this services.
// Created by Fred Nora.

#include <kernel.h>


void gramk_refresh_screen(void)
{
    refresh_screen();
}

void gramk_putchar_in_fgconsole(unsigned long _char)
{
    int c = (int) (_char & 0xFF);

// Draw and refresh.
    console_outbyte2 ( c, fg_console );
}
