/*
 * File: main.c
 * 
 *     Main file for the kernel.
 *     Architecture independent.
 *
 * History:
 *     2019 - Created by Fred Nora.
 */



#include <kernel.h>


// Boot mode.
extern unsigned long SavedBootMode;



/*
 ****************************
 * kernel_main:
 *
 *     Main function.
 *     The Assembly part calls this function.
 */

int kernel_main (int arch_type){

    int Status = 0;
    int z;

    //
    // Current arch support.
    //

    // We received this arg from Assembly.

    current_arch = arch_type;

    //#todo
    //if(current_arch<=0)


    // #order
    // serial debug.
    // video.
    // ...


    //
    //  Virtual Console
    //

    // Só tem 4.
    console_set_current_virtual_console (0);
    
    console_init_virtual_console (0);
    console_init_virtual_console (1);
    console_init_virtual_console (2);
    console_init_virtual_console (3);   // window server.


    
	//
	// Serial debug
	//

    // Initialize all the ports.
    serial_init ();

    debug_print("============================================\n");
    debug_print("== main.c: Architechture independent part ==\n");
    debug_print("============================================\n");
	
    debug_print("[Kernel] kernel_main: \n");
    debug_print("[Kernel] kernel_main: Initializing the part in C ...\n");

    switch (current_arch)
    {
        case CURRENT_ARCH_X86:
            debug_print ("[Kernel] kernel_main: x86? \n");
            break;

		case CURRENT_ARCH_X86_64:
            debug_print ("[Kernel] kernel_main: x86_64? \n");
            debug_print ("[Kernel] kernel_main: Current arch not supported!\n *hang");
			goto fail;
            break;

        // ...

        default:
            debug_print ("[Kernel] kernel_main: Current arch not defined!\n *hang");
			goto fail;
            break; 
    };


    //
    // Kernel status.
    //

    KernelStatus = KERNEL_NULL;

    //Initializing the global spinlock.

    __spinlock_ipc = 1;


	// #test.
	// Initializing zorder list.
	
    // #todo
    // Move this to another place.

    for ( z=0; z < KGWS_ZORDER_MAX; z++ ){
        Windows[z] = (unsigned long) 0;
    }
    zorderCounter = 0;


	//
	// Set system window procedure.
	//

	// #bugbug
	// Delete this thing!

    SetProcedure ( (unsigned long) &system_procedure );



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
		//panic ("kernel_main: Text mode not supported");
	};


	//
	// Verbose mode.
	//

	// #obs:
	// Verbose mode do kernel.
	// Initializes a new line when '\n' is found.

    stdio_verbosemode_flag = 1;


	// In video.c 

    videoVideo ();
    videoInit ();

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
	// What about to initialize it early?!
	// See: sm/rt/runtime.c

    debug_print ("[Kernel] kernel_main: Initializing runtime\n");

    Status = (int) KiInitRuntime ();

    if ( Status != 0 ){
        debug_print ("[Kernel] kernel_main: Runtime fail. *hang\n");
        while (1){
            asm ("cli \n");
            asm ("hlt \n");
        };
    };


	// #DEBUG
	// breakpoint
	// lfb_putpixel ( COLOR_YELLOW, 11, 11, 0 );
	// while(1){}


	//
	// ======== Select arch ========
	//

	// #todo
	// A partir daqui faremos inicializações de partes
	// dependentes da arquitetura.
	
	switch (current_arch)
	{
	    case CURRENT_ARCH_X86:
            debug_print ("[Kernel] kernel_main: Initializing x86 arch ...\n");
            x86main ();
            break;

		case CURRENT_ARCH_X86_64:
            debug_print ("[Kernel] kernel_main: Initializing x86_64 arch ...\n");
            debug_print ("[Kernel] kernel_main: Current arch not supported !\n *hang");
			goto fail;
            break;

        // armmain (); ??

        // ...

        default:
            debug_print ("[Kernel] kernel_main: Current arch not defined!\n *hang");
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


