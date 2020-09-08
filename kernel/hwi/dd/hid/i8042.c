/*
 * File: i8042/i8042.c
 *     i8042 controller initialization.
 *     initialize ps2 controller.
 * env:
 *     Ring 0. Kernel base persistent code.
 * 2018 - Created by Fred Nora.
 */

 
// When the keyboard and mouse are USB devices, the BIOS uses SMM code 
// to emulate PS/2 devices. 
// I see mentioned that the USB devices should halt ps/2 emulation 
// once they've been initialized (or at least their host hub?)


#include <kernel.h>



void 
prepare_for_input (void){
    kbdc_wait(0);
}
void 
prepare_for_output (void){
    kbdc_wait (1);
}


unsigned char 
wait_then_read (int port){
    prepare_for_input();
    return (unsigned char) in8 (port);
}
void 
wait_then_write ( int port, int data ){
    prepare_for_output();
    out8 ( port, data );
}



/*
 ***************
 * ps2:
 *     Essa rotina de inicialização do controlador 
 * poderá ter seu próprio módulo.
 *     Inicializa o controlador ps2.
 *     Inicializa a porta do teclado no controlador.
 *     Inicializa a porta do mouse no controlador.
 *     Obs: *importante: A ordem precisa ser respeitada.
 *     As vezes os dois não funcionam ao mesmo tempo se a 
 *     inicialização não for feita desse jeito. 
 */
 
void ps2 (void){


	// #debug
	printf ("ps2: Initializing..\n");
	refresh_screen();



    // ======================================
    // Deactivate ports!
    wait_then_write (0x64,0xAD);
    wait_then_write (0x64,0xA7); 


    // Keyboard.
    printf ("ps2: Initializing keyboard ..\n");
    refresh_screen();
    ps2kbd_initialize_device ();


    // Mouse.
    printf ("ps2: Initializing mouse ..\n");
    refresh_screen();
    ps2mouse_initialize_device ();


    // ======================================
    // Reactivate ports!
    wait_then_write (0x64,0xAE);
    wait_then_write (0x64,0xA8);


    // Wait for nothing!
    kbdc_wait (1);
    kbdc_wait (1);
    kbdc_wait (1);
    kbdc_wait (1);


// Done.

    //#debug
    printf ("ps2: done\n");
    refresh_screen();
}


// Inicialização preliminar. Sem mouse.
// Ela existe porque a emulação de ps2 na máquina real 
// apresenta falhas.
// No gdeshell.bin incluiremos os comando "ps2-init"
// para obtermos a inicialização completa.
void early_ps2_init (void)
{
    // mas simples...
    // apenas teclado.

	// #debug
	printf ("early_ps2_init: Initializing..\n");
	refresh_screen();



    // ======================================
    // Deactivate ports!
    wait_then_write (0x64,0xAD);
    wait_then_write (0x64,0xA7); 


    // Keyboard.
    printf ("early_ps2_init: Initializing keyboard ..\n");
    refresh_screen();
    ps2kbd_initialize_device ();


    // Mouse.
    //printf ("ps2: Initializing mouse ..\n");
    //refresh_screen();
    //ps2mouse_initialize_device ();


    // ======================================
    // Reactivate ports!
    wait_then_write (0x64,0xAE);
    //wait_then_write (0x64,0xA8);


    // Wait for nothing!
    kbdc_wait (1);
    kbdc_wait (1);
    kbdc_wait (1);
    kbdc_wait (1);


// Done.

    //#debug
    printf ("early_ps2_init: done\n");
    refresh_screen();


}









//
// End.
//

