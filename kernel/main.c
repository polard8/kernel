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
 *     Main function.
 *     Vem pra cá do entrypoint em assembly, que é dependente da arquitetura.
 */

int kernel_main (void){

    int Status = 0;

    int zIndex;	

	//
	// Serial debug
	//

	init_serial (COM1_PORT);

	debug_print("[Kernel] kernel_main:\n");


    KernelStatus = KERNEL_NULL;

	//Initializing the global spinlock.

    __spinlock_ipc = 1;


	// #test.
	// Initializing zorder list.
	// Isso não deve ficar aqui.

    for ( zIndex = 0; zIndex < ZORDER_COUNT_MAX; zIndex++ )
    {
        zorderList[zIndex] = (unsigned long) 0;
    }

    zorderCounter = 0;

	//
	// Set system window procedure.
	//

	// #bugbug
	// Deletar.

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
	// #bugbug: Text mode is not supported.

    if ( SavedBootMode == 1 )
    {
        g_useGUI = GUI_ON;
        VideoBlock.useGui = GUI_ON;

		//...

    }else{

        g_useGUI = GUI_OFF;
        VideoBlock.useGui = GUI_OFF;

		//...

		//#todo
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

#ifdef ENTRY_VERBOSE	

    //If we are using graphics mode.

    if (VideoBlock.useGui == GUI_ON)
    {
        debug_print ("[Kernel] kernel_main: Using GUI\n");
    }

#endif	

	// #DEBUG
	// breakpoint

	// lfb_putpixel ( COLOR_YELLOW, 11, 11, 0 );
	// while(1){}


	//
	// Runtime
	//

	// #bugbug:
	// #todo:
	// Somente depois da inicialização da runtime é que temos suporte 
	// a mensagens, mas queremos mensagens antes, antão vamos tentar antecipar 
	// a inicialização da runtime.		


#ifdef EXECVE_VERBOSE
    debug_print ("[Kernel] kernel_main: Initializing runtime\n");
#endif

	// sm/rt/runtime.c

    Status = (int) KiInitRuntime ();

    if ( Status != 0 )
    {
		//#obs
		//Esse é o único tipo de mensagem que tempos por enquanto.

        debug_print ("[Kernel] kernel_main: Runtime fail\n");
		//die ();

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
	
	//#todo
	//Talvez um switch.

	// switch (){
	// ...
	//}

	// #provisório.
	
	x86main ();

	//armmain ();


	//
	// #todo
	//

	// #todo
	// Aqui poderemos inicializar outras partes independentes da arquitetura.

	//...

fail:

	// #hang
	// A inicialização falhou
	// Voltaremos para o assembly de head.s
	// Onde deverá ter um hang.

    debug_print ("[Kernel] kernel_main: fail: \n");

    return (-1);
}


