/*
 * File: kernel/main.c 
 * 
 *     This is the main file for the kernel.
 *     It's architecture independent.
 *     The Assembly code passed the control for us, so now
 * we're gonna do some architechture intependent initialization 
 * and call the next part of the architechture dependent stuff.
 *
 * History:
 *     2019 - Created by Fred Nora.
 *     2020 -
 */



#include <kernel.h>


// Boot mode.
extern unsigned long SavedBootMode;


// char copyright[] =
// "Copyright (c) 2005-2020 \n\tFred Nora. All rights reserved.\n\n";



/*
 *************************************************
 * kernel_main:
 *
 *     Main function.
 *     The Assembly part calls this function.
 */

int kernel_main (int arch_type){

    int Status = -1;


    // Current arch support.
    // We received this arg from Assembly.

    current_arch = arch_type;


    // Kernel status.
    KernelStatus = KERNEL_NULL;



    // #order
    // serial debug.
    // video.
    // ...
    
    // Serial debug
    // Initialize all the ports.
    // ps: We can't use debug in this first initialization.
    // See: bottom/dd/serial/serial.c
    Status = serial_init();
    if (Status != 0)
    {
        // #bugbug
        // Não temos uma mensagem pra alertar que alguma coisa
        // falhou na inicialização das portas seriais.
        // Vamos continuar por enquanto.
    }
    
    debug_print ("============================================\n");
    debug_print ("== main.c: Architechture independent part ==\n");
    debug_print ("============================================\n");
    debug_print ("[Kernel] kernel_main: \n");
    debug_print ("[Kernel] kernel_main: Initializing the part in C ...\n");


    // Virtual Console
    // The kernel only have four virtual consoles.
    debug_print ("[Kernel] kernel_main: Initializing virtual console...\n");
    
    console_set_current_virtual_console (0);
    console_init_virtual_console (0);
    console_init_virtual_console (1);
    console_init_virtual_console (2);
    console_init_virtual_console (3);


    switch (current_arch){

        case CURRENT_ARCH_X86:
            debug_print ("[Kernel] kernel_main: x86? \n");
            break;

        case CURRENT_ARCH_X86_64:
            debug_print ("[Kernel] kernel_main: x86_64? \n");
            debug_print ("[Kernel] kernel_main: x86_64 not supported!\n *hang");
            goto fail;
            break;

        // ...

        default:
            debug_print ("[Kernel] kernel_main: Current arch not defined!\n");
            debug_print ("*Hang\n");
            goto fail;
            break; 
    };



    // Initializing the global spinlock.
    // todo: Isso pode ir para init_globals

    __spinlock_ipc = 1;


	//
	// Video support 
	//

	// First of all.
	// #ps: 
	// Boot loader is mapping the LFB.

	// #todo: 
	// Device screen sizes.

	// Set graphics mode or text mode using a flag.
	// #bugbug: 
	// Text mode is not supported.

    if ( SavedBootMode == 1 ){
        g_useGUI = GUI_ON;
        VideoBlock.useGui = GUI_ON;
        debug_print ("[Kernel] kernel_main: GUI_ON\n");
		//...

    }else{
        g_useGUI = GUI_OFF;
        VideoBlock.useGui = GUI_OFF;
        debug_print ("[Kernel] kernel_main: GUI_OFF\n");
        debug_print ("[Kernel] kernel_main: Text mode not supported! *hang");

        while (1){
            asm ("cli \n");
            asm ("hlt \n");
        };

		//...

		// #todo
		// No message support at the moment ?!
		// panic ("kernel_main: Text mode not supported");
	};


    debug_print ("[Kernel] kernel_main: Initializing video support ...\n");
    
	//
	// Verbose mode.
	//

	// #obs:
	// Verbose mode do kernel.
	// Initializes a new line when '\n' is found.

    stdio_verbosemode_flag = 1;


    // In video.c 

    videoVideo();
    videoInit();

    // Init screen


// If we are using graphics mode.
#ifdef ENTRY_VERBOSE	
    if (VideoBlock.useGui == GUI_ON){
        debug_print ("[Kernel] kernel_main: Using GUI\n");
    }
#endif	


	// #debug
	// breakpoint
	// lfb_putpixel ( COLOR_YELLOW, 11, 11, 0 );
	// while(1){}


	//
	// Runtime
	//

    // #bugbug:
    // We need the runtime initialization for the messages.
    // What about to initialize it early?! now!!!!
    // See: core/runtime.c

    debug_print ("[Kernel] kernel_main: Initializing runtime\n");

    Status = (int) init_runtime();

    if ( Status < 0 ){
        debug_print ("[Kernel] kernel_main: Runtime fail. *hang\n");
        while (1){
            asm ("cli \n");
            asm ("hlt \n");
        };
    }


	// #DEBUG
	// breakpoint
	// lfb_putpixel ( COLOR_YELLOW, 11, 11, 0 );
	// while(1){}

    // obs:
    // Nesse momento o bl deixou a tela suja.
    // Entao as mensagens nessa fase da inicializaçao
    // sao apresentadas em cima da sujeira deixada pelo boot loader.
    // #test: 
    // Se possivel vamos limpara a tela agora. Pois ja inicializamos
    // a runtime.
    
    backgroundDraw ( (unsigned long) COLOR_BLACK); 
        
    //#debug.
    //refresh_screen();
    //while(1){}


	//
	// ======== Select arch ========
	//

	// #todo
	// A partir daqui faremos inicializações de partes
	// dependentes da arquitetura.

    switch (current_arch){

        // See: hwi/init/x86/x86init.c
        case CURRENT_ARCH_X86:
            debug_print ("[Kernel] kernel_main: Initializing x86 arch ...\n");
            Status = (int) x86main();
            if (Status < 0)
                panic("[Kernel] kernel_main: CURRENT_ARCH_X86 fail\n");
            break;

        // See:
        case CURRENT_ARCH_X86_64:
            debug_print ("[Kernel] kernel_main: Initializing x86_64 arch ...\n");
            debug_print ("[Kernel] kernel_main: Current arch not supported !\n *hang");
            //Status = (int) x86_64main();
            goto fail;
            break;

        // See:
        // armmain (); ??

        // ...


        default:
            debug_print ("[Kernel] kernel_main: Current arch not defined!\n ");
            debug_print ("*Hang\n");
            goto fail;
            break; 
    };

    //
    // Fail!
    //

fail:

    debug_print ("[Kernel] kernel_main-fail:  *hang \n");
    return (-1);
}


//
// End.
//


