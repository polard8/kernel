/*
 * File: i8042/i8042.c
 *     i8042 controller initialization.
 *     initialize ps2 controller.
 * env:
 *     Ring 0. Kernel base persistent code.
 * 2018 - Created by Fred Nora.
 */

 
#include <kernel.h>



/*
 ***************
 * ps2:
 *     Essa rotina de inicialização do controladro 
 * poderá ter seu próprio módulo.
 *     Inicializa o controlador ps2.
 *     Inicializa a porta do teclado no controlador.
 *     Inicializa a porta do mouse no controlador.
 *     Obs: *importante: A ordem precisa ser respeitada.
 *     As vezes os dois não funcionam ao mesmo tempo se a 
 *     inicialização não for feita desse jeito. 
 */
 
void ps2 (){
	
	
	printf ("ps2: initializing ...\n");
	refresh_screen();
	
    //printf("");	
	//printf("ps2: Desabilitando as duas portas...\n");
	//refresh_screen();

    
	//
	// ## DESATIVANDO AS DUAS PORTAS ##
	//
	
	
	// Desativar dispositivos PS/2 , isto evita que os dispositivos PS/2 
	// envie dados no momento da configuração.

	
//desablePorts:


    //##bugbug
	//não sabemos o efeito colateral disso.
	//isso pode dar problema.

	
	// Desativar a primeira porta PS/2.
	//kbdc_wait(1);
	//outportb(0x64,0x60);  
	
	//printf ("ps2: 1\n");
	//refresh_screen();
  	
	kbdc_wait(1);
	outportb(0x64,0xAD);  
	
	// Desativar a segunda porta PS/2, 
	// hahaha por default ela já vem desativada, só para constar
	//kbdc_wait(1);
	//outportb(0x64,0x60);  	
	
	//printf ("ps2: 2\n");
	//refresh_screen();
	
	kbdc_wait(1);
	outportb(0x64,0xA7); 


    //
	//======================================
	//

    //
	// ## step 1 ##
    // mouse	 
    //

	
//mouse_initialization:	
	

	//inicializa o controlador para habilitar abort
	//segunda porta. O mouse.
    
	//2
	//printf("ps2: inicializando mouse ...\n");
	//refresh_screen();	
	
	//printf ("ps2: 3\n");
	////refresh_screen();
	
	ps2_mouse_initialize();  
	
	
	
	//printf("ps2: inicializando globais do mouse ...\n");
	//refresh_screen();	
	//Não afeta o controlador. 
	//Apenas inicializa variáveis.
	
	//printf ("ps2: 4\n");
	//refresh_screen();
	
	ps2_mouse_globals_initialize();	

	
	
    //
	// ## step 2 ##
    // keyboard	 
	//
//keybaord_initialization:


    //2
	//printf("ps2: inicializando teclado ...\n");
	//refresh_screen();
	
	//printf ("ps2: 5\n");
	//refresh_screen();
	
	ps2_keyboard_initialize();
	
	
	//
	//mouse install ...
	//
	
	//printf ("ps2: 6\n");
	//refresh_screen();
	
	mouse_install ();
	
	
 
    //
	// ## REABILITANDO ##
	//
 
 	//3
	//printf("ps2: reabilitando  porta do mouse; ...\n");
	//refresh_screen();	
	
	// Ativar a segunda porta PS/2.
	//kbdc_wait(1);
	//outportb(0x64,0x60);    
	//kbdc_wait(1);
	//outportb(0x64,0xA8); 
 
	//3
	//printf("ps2: reabilitando  porta do teclado ...\n");
	//refresh_screen();		
	
	
	//AE    Enable Keyboard Interface: clears Bit 4 of command register
	//      enabling keyboard interface.
	//kbdc_wait(1);
	//outportb(0x64,0x60);    	
	//kbdc_wait(1);
	//outportb(0x64,0xAE);   // Activar a primeira porta PS/2		
	

	//
	// ## RESETANDO ##
	//
	
	
	//1
	//printf("ps2: resetando mouse. ...\n");
	//refresh_screen();		
	
	//+devemos configurar o modo escrita
	//+enviar o comando reset;
	//+ler as respostas.(#todo) fa, ff, 00
	
	// defina, a escrita  de byte de configuração do controlador PS/2.
    // Reseta mouse (reset ? lento!)...
    // Espero pelo byte 0xaa que encerra a sequ?ncia
    // de reset!	
	//kbdc_wait(1);
	//outportb(0x64,0x60);  
    //kbdc_wait(1);
    //mouse_write(0xff);
    
	//#bubug: loop infinito.
	//while ( mouse_read() != 0xaa )
	//{
		//
	//};			
	
    //1
	//printf("ps2: resetando teclado. ...\n");
	//refresh_screen();		

	//+devemos configurar o modo escrita
	//+enviar o comando reset;
	//+ler as respostas.(#todo) fa, ff, 00	

	//reset KEYBOARD.
	//kbdc_wait(1);
	//outportb(0x60,0x60);  
	//kbdc_wait(1);
	//outportb(0x60,0xFF);
	//#bubug: loop infinito.
	//while ( kbd_read() != 0xaa )
	//{
		//
	//};			

	printf("ps2: done\n");
	refresh_screen();		
}


//
// End.
//

