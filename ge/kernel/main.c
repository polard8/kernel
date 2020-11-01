/*
 * File: kernel/main.c
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

// This variables came from BL.BIN.

// The boot mode. CLI or GUI.
extern unsigned long SavedBootMode;

// Boot Block address.
extern unsigned long SavedBootBlock;


// char copyright[] =
// "Copyright (c) 2005-2020 \n\tFred Nora. All rights reserved.\n\n";


/*
 ********************************************
 * kernel_main:
 *
 *     Main function.
 *     The Assembly part calls this function.
 */


int kernel_main (int arch_type){

    int Status = (-1);


    // Current arch support.
    // We received this arg from Assembly.

    current_arch = arch_type;


    // Kernel status.
    KernelStatus = KERNEL_NULL;


    // #bugbug
    // Talvez esse endereço nao esteja acessivel ao kernel.

     //See gdef.h
    unsigned long *base = (unsigned long *) SavedBootBlock;
    
    BootBlock.lfb                = (unsigned long) base[0]; // 0
    BootBlock.x                  = (unsigned long) base[1];  // 4
    BootBlock.y                  = (unsigned long) base[2];  // 8
    BootBlock.bpp                = (unsigned long) base[3];  // 12
    BootBlock.last_valid_address = (unsigned long) base[4];  // 16
    BootBlock.metafile_address   = (unsigned long) base[5];  // 20
    BootBlock.disk_number        = (unsigned long) base[6];  // 24
    BootBlock.heads              = (unsigned long) base[7];  // 28
    BootBlock.spt                = (unsigned long) base[8];  // 32
    BootBlock.cylinders          = (unsigned long) base[9];  // 36
    BootBlock.boot_mode          = (unsigned long) base[10]; // 40
    BootBlock.gramado_mode       = (unsigned long) base[11]; // 44


    // The 'gramado mode' or 'gamemode'.
    // jail,p1,home,p2,castle
    // We can't check right here ...
    // there is no messages yet.

    // Saving
    // It is used by the kernel info.
    current_mode = (char) BootBlock.gramado_mode;


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


    //gramado mode
    //game mode
    switch (current_mode){

        case GRAMADO_JAIL:
            debug_print ("kernel_main: GRAMADO_JAIL: \n");
            break;

        case GRAMADO_P1:
            debug_print ("kernel_main: GRAMADO_P1: \n");
            break;

        case GRAMADO_HOME:
            debug_print ("kernel_main: GRAMADO_HOME: \n");
            break;

        case GRAMADO_P2:
            debug_print ("kernel_main: GRAMADO_P2: \n");
            break;

        case GRAMADO_CASTLE:
            debug_print ("kernel_main: GRAMADO_CASTLE: \n");
            break;

        //case GRAMADO_CALIFORNIA:
        // ...
        default:
            debug_print ("kernel_main: current_mode not defined!\n");
            break;
    };


    // Virtual Console:
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
    // #todo: Isso pode ir para init_globals

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

    backgroundDraw ( (unsigned long) COLOR_BLACK );

    //#debug.
    //refresh_screen();
    //while(1){}

    // #debug
    // breakpoint
    // Consegumos pegar varios valores do boot block
    // menos o ultimo, que o que mais nos interessa.

    printf ("kernel_main: breakpoint. pegando valores do boot block\n");
    printf ("Boot block pa %x\n",SavedBootBlock); //isso esta certo.
    printf ("lfb %x\n",BootBlock.lfb);
    printf ("x   %d\n",BootBlock.x);
    printf ("y   %d\n",BootBlock.y);
    printf ("bpp %d\n",BootBlock.bpp);
    //...
    printf (">>>  Gramado mode %d\n", BootBlock.gramado_mode);

    refresh_screen();
    //while(1){}


    //
    // == Select arch ==============================
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

