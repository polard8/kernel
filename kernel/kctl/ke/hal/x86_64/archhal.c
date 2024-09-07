// archhal.c
// HAL interface for x86_64 architecture.
// Created by Fred Nora.

#include <kernel.h>


//
// Imports
//

extern void asm_reboot(void);


//  VECTORS 
//  (isr and irq address)

// #todo: Oh boy, oh boy!
// Endereços das rotinas básicas chamadas pelos vetores de interrupções.
// Essas rotinas devem chamar seus handlers específicos.
// 256 interrupções
//unsigned long VECTORS[256];

// HANDLERS 
// (callbacks??) 

// #todo: Oh boy, oh boy!
// Endereços para as rotinas em C que tratam as interrupções.
// Essas rotinas rodam depois da rotina básica em assembly.
// 256 interrupções
// 8 extras para handlers default.
//unsigned long HANDLERS[256+8];


// ===============================

/*
 * Beep support
 * #bugbug: 
 * Não quero comprometer a programação do PIT. 
 */

/*
void ____Beep_tone (int freq){

    if (freq == 0) {
        int i = io_in8(0x61);
        io_out8(0x61, i & 0x0d);
    
    } else {
        int i = 1193180000 / freq;
        io_out8(0x43, 0xb6);
        io_out8(0x42, i & 0xff);
        io_out8(0x42, i >> 8);
        i = io_in8(0x61);
        io_out8(0x61, (i | 0x03) & 0x0f);
    }
}
*/ 



/*
// Called by the idle handler for up.
void hal_up_idle(void);
void hal_up_idle(void)
{
    asm ("sti");
    asm ("hlt");
    return;
}
*/


/*
// Called by the idle handler for mp.
void hal_mp_idle(void);
void hal_mp_idle(void)
{
    asm ("sti");
    return;
}
*/



// Speaker ON. 
// OUT 
// Play sound using built in speaker
void archhal_speaker_on (void)
{
// Play the sound using the PC speaker.

    uint8_t tmp=0;
    tmp = in8(0x61);
    if (tmp != (tmp | 3))
    {
        out8(0x61, tmp | 3);
    }
}

// Speaker OFF
// IN
void archhal_speaker_off (void)
{
// make it shutup.

    uint8_t tmp=0; 
    tmp = in8(0x61) & 0xFC;
    out8 (0x61, tmp);
}

void archhal_reboot(void)
{
    asm_reboot();
}
