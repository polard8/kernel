
// keyboard.c


// See:
// https://www.gnu.org/software/libc/manual/html_node/Canonical-or-Not.html
//

#include <kernel.h>  


__VOID_IRQ 
irq1_KEYBOARD (void)
{
    //#debug

    debug_print ("\n");
    debug_print ("irq1_KEYBOARD: [TODO]\n");
    
    //printf ("k");
    //refresh_screen();

    // Disable mouse port.
    wait_then_write (0x64,0xA7);

    // #test
    // See: ps2kbd.c
    
    DeviceInterface_PS2Keyboard();

    // #bugbug
    // Se estivermos usando uma inicialização reduzida,
    // onde habilitamos somente a porta do teclado,
    // não podemos habilitar a porta do mouse, sem a 
    // devida inicialização.

    // Só reabilitaremos se a configuração de ps2 
    // nos disser que o segundo dispositivo esta em uso.
    
    // Reabilitando a porta de um dispositivo que
    // ja foi devidamente inicializado.

    // Reenable the mouse port.

done:

    if ( PS2.used == TRUE )
    {
        if ( PS2.mouse_initialized == TRUE ){
            wait_then_write (0x64,0xA8);
        }
    }
}



