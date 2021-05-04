/*
 * File: kernel/0mem/main.c
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


// It starts with the kernel data and
// it has the main routine for the kernel.


#include <kernel.h>


// This variables came from BL.BIN.

// The boot mode. CLI or GUI.
extern unsigned long SavedBootMode;

// Boot Block address.
extern unsigned long SavedBootBlock;



//
// == kernel data ==============================
//

// char copyright[] =
// "Copyright (c) 2005-2020 \n\tFred Nora. All rights reserved.\n\n";


// Salvaremos aqui o endereço da idle thread.
// Isso podera ser importado pelo assembly.
// unsigned long Ring0IdleThreadAddress;


// Algum componente em ring0 pode configurar esse callout
// o assmebly pode importar e chamar isso.
// Entao com isso rodariamos uma rotina em ring0 mas fora do kernel.
// unsigned long Ring0CallOut;


// ...


/*
//#test
// The problem here is the variables are imported from 'ld'.
// Thats not what we want.
// We wanna build gramado with our own compiler.
extern unsigned long bss_begin;
extern unsigned long bss_end;
static void clear_bss(void)
{
    memset ( 
        bss_begin,              // start 
        0,                      // data
        bss_end - bss_begin );  // size
}
*/


/*
struct kernel_d
{
    int hasBooted;
    void *scheduler;
};
struct kernel_d Kernel;
*/


// internal
// #todo: Talvez isso precise retornar int.

void preinit_Globals(int arch_type)
{

//
// == Boot block ======================================
//

    //See:
    //landos/kernel/include/land/0globals/gdef.h
    
    BootBlock.initialized = FALSE;

    unsigned long *base = (unsigned long *) SavedBootBlock;

    // #todo
    // Check address validation
    
    //if ( (void *) == NULL ){
        //FAIL
    //}

    BootBlock.bootblock_address  = (unsigned long) SavedBootBlock;
    BootBlock.lfb                = (unsigned long) base[0];  //  0
    BootBlock.x                  = (unsigned long) base[1];  //  4
    BootBlock.y                  = (unsigned long) base[2];  //  8
    BootBlock.bpp                = (unsigned long) base[3];  // 12
    BootBlock.last_valid_address = (unsigned long) base[4];  // 16
    BootBlock.metafile_address   = (unsigned long) base[5];  // 20
    BootBlock.disk_number        = (unsigned long) base[6];  // 24
    BootBlock.heads              = (unsigned long) base[7];  // 28
    BootBlock.spt                = (unsigned long) base[8];  // 32
    BootBlock.cylinders          = (unsigned long) base[9];  // 36
    BootBlock.boot_mode          = (unsigned long) base[10]; // 40
    BootBlock.gramado_mode       = (unsigned long) base[11]; // 44
    BootBlock.initialized = TRUE;

    // ==============================================

    // Kernel status.
    KernelStatus = KERNEL_NULL;

    // Current arch support.
    // We received this arg from Assembly.

    current_arch = arch_type;


    // runlevel
    
    current_runlevel = DEFAULT_RUNLEVEL;
    //current_runlevel = 5;

    // Kernel symbol table.
    // #todo: maybe we will load a kernel.map file.
    g_kernel_symbols_available = FALSE;


    //
    // == gramado mode =============================================
    //

    // The 'gramado mode' or 'gamemode'.
    // jail,p1,home,p2,castle
    // We can't check right here ...
    // there is no messages yet.

    // Saving
    // It is used by the kernel info.
    current_mode = (char) BootBlock.gramado_mode;


//
// == No preemptions ==============================
//

    // Para evitar que exista qualquer tipo de preempção
    // devemos usar essas flags, que serão destravadas
    // no fim da rotina do processo init.bin.

    // #bugbug
    // Talvez alguma rotina de carregamento de arquivo esteja
    // usando essas flags e travando e destravando isso.
    // Uma delas pode destravas antes mesmo o processo init
    // fazer seu trabalho.

    // Disable interrupts, lock taskswitch and scheduler.
    //Set scheduler type. (Round Robin).
    // #todo: call a hal routine for cli.

    asm ("cli");  // #todo: isso é dependente da arquitetura.
    taskswitch_lock();
    scheduler_lock();
    schedulerType = SCHEDULER_RR; 

    // Initializing the global spinlock.
    // #todo: Isso pode ir para init_globals

    //## pre initialization globals.

    __spinlock_ipc = TRUE;



//
// == input mode =============================================
//

    // This is the default initial input mode.
    // This mode is gonna change only when we load
    // a ring3 window server.
    
    current_input_mode = INPUT_MODE_SETUP;


//
// == Verbose mode ================================
//

	// #obs:
	// Verbose mode do kernel.
	// Initializes a new line when '\n' is found.

    stdio_verbosemode_flag = TRUE;

    // ...
}

// internal
// #todo: Talvez isso precise retornar int.
void preinit_Serial(void)
{
    // Serial
    // See: bottom/dd/serial/serial.c

    serial_init();
}

// internal
// #todo: Talvez isso precise retornar int.
void preinit_OutputSupport(void)
{

    // Virtual Console.
    // See: user/console.c
    debug_print ("[Kernel] kernel_main: Initializing virtual consoles ...\n");
    VirtualConsole_initialize();
}


/*
 ********************************************
 * kernel_main:
 *
 *  Gramado OS kernel C entry point. :)
 * 
 *  This is where C execution begins, after head.asm 
 *  transfers control here.
 * 
 *  The purpose is to initialize the virtual console support,
 *  the video support, the runtime support and starts the
 *  architecture initialization routine.
 * 
 */

// #progress
// name:level:sublevel

int kernel_main (int arch_type)
{
    int Status = (-1);


    // Globals
    // We do not have output yet

    preinit_Globals(arch_type);

    // Serial
    // We do not have output yet

    preinit_Serial();

    // =================================================
    
    //
    // #progress
    // name:level:sublevel
    //

    PROGRESS("----------------\n");
    PROGRESS("  GRAMADO LAND  \n");
    // Now we have serial port output.

    // =================================================


    PROGRESS("Kernel:0:1\n");
    // Initialize the virtual console structures.
    // #IMPORTAT: We do not have all the runtime support yet.
    // We can't use printf yet.

    preinit_OutputSupport();


    PROGRESS("Kernel:0:2\n");
    // Show some basic info.

    debug_print ("Initializing landos kernel ...\n");



    /*
    // #test
    // precisamos importar essa vari'avel?
    if ( kernel_end >= (0xC0000000 + 0x300000) )
    {
        debug_print ("kernel_main: The kernel image is too large\n");
        asm volatile("cli;hlt");
    }
    */


    // The mode.
    debug_print ("mode: ");

    switch (current_mode){
        // Standard modes.
        case GRAMADO_JAIL:   debug_print ("GRAMADO_JAIL\n");   break;
        case GRAMADO_P1:     debug_print ("GRAMADO_P1\n");     break;
        case GRAMADO_HOME:   debug_print ("GRAMADO_HOME\n");   break;
        case GRAMADO_P2:     debug_print ("GRAMADO_P2\n");     break;
        case GRAMADO_CASTLE: debug_print ("GRAMADO_CASTLE\n"); break;
        // Super modes.
        case GRAMADO_CALIFORNIA:  
            debug_print ("GRAMADO_CALIFORNIA\n"); 
            break;
        //case GRAMADO_CALIFORNIA2:  
        //    debug_print ("GRAMADO_CALIFORNIA2\n"); 
        //    break;
        // ...

        // We can't use printf yet.
        default:  
            debug_print ("[FAIL] Not defined\n");  
            goto fail1;
            break;
    };


    // The architecture.
    debug_print ("arch: ");
    
    switch (current_arch){

        case CURRENT_ARCH_X86:  
            debug_print ("x86\n");  
            break;

        // We can't use printf yet.
        case CURRENT_ARCH_X86_64:
            debug_print ("x86_64 [FAIL] Not supported\n");
            goto fail1;
            break;
        // ...

        // We can't use printf yet.
        default:
            debug_print ("? [FAIL] Not defined\n");
            goto fail1;
            break; 
    };


    PROGRESS("Kernel:0:3\n");
    // Video support


    debug_print ("[Kernel] kernel_main: Initializing video support ...\n");

    // First of all.
    // #ps:
    // Boot loader is mapping the LFB.

    // #todo:
    // Device screen sizes.

    // Set graphics mode or text mode using a flag.
    // #bugbug:
    // Text mode is not supported.

    if ( SavedBootMode == 1 ){
        g_useGUI          = GUI_ON;
        VideoBlock.useGui = GUI_ON;
        debug_print ("[Kernel] kernel_main: GUI_ON\n");
        // ...

    // We can't use printf yet.
    }else{
        g_useGUI          = GUI_OFF;
        VideoBlock.useGui = GUI_OFF;
        debug_print ("[Kernel] kernel_main: GUI_OFF\n");
        debug_print ("[Kernel] kernel_main: Text mode not supported! *hang");
        goto fail1;
    };


    if (VideoBlock.useGui == GUI_ON){
        debug_print ("[Kernel] kernel_main: Using GUI\n");
    }

    // ================================================

    // Now we will initialize the video support,
    // the runtime support and clean the background.
    // This way we're gonna be able to use 'printf'.

    //
    // Video
    //

    // In hid/video.c
    Video_initialize();

    PROGRESS("Kernel:0:4\n");
    // Runtime


    //
    // Runtime
    //

    // #bugbug:
    // We need the runtime initialization for the messages.
    // What about to initialize it early?! now!!!!
    // See: core/runtime.c

    // #bugbug
    // Here the background is not initialized yet,
    // so, we have a lot of dirty things.

    debug_print ("[Kernel] kernel_main: Initializing runtime\n");
    Runtime_initialize();
    //printf("2\n");
    
    PROGRESS("Kernel:0:5\n");
    // Clear the screen.
    // print some basic info.

    //
    // Background
    //

    // Initializing background 
    // for the very first time.
    // Now we have a black screen.
    // But the cursor position is wrong yet.

    // See: user/draw/view/bg.c
    Background_initialize();


    // ================================================

    //
    // The first char!
    //
   
    // This is the first char ever for 
    // the new background.

    //See:
    //landos/kernel/include/land/0globals/gdef.h

    printf ("$\n");
    printf ("GRAMADO LAND\n");

    if ( BootBlock.initialized != TRUE ){
        panic ("kernel_main: [FAIL] BootBlock not initialized!\n");
    }

    printf ("Boot block address %x\n",BootBlock.bootblock_address);  
    printf ("lfb %x\n",BootBlock.lfb);
    printf ("x   %d\n",BootBlock.x);
    printf ("y   %d\n",BootBlock.y);
    printf ("bpp %d\n",BootBlock.bpp);
    printf (">>>  Gramado mode %d\n", BootBlock.gramado_mode);
    refresh_screen();

    // #debug
    // while(1){}


    PROGRESS("Kernel:0:6\n"); 
    // Initialize current archtecture.


	// #todo
	// A partir daqui faremos inicializações de partes
	// dependentes da arquitetura.

    switch (current_arch){

        // See: x86/x86init.c
        case CURRENT_ARCH_X86:
            debug_print ("kernel_main: Initializing x86 arch ...\n");
            printf("kernel_main: Initializing x86 arch ...\n");
            Status = (int) x86main();
            if (Status < 0)
                panic("[Kernel] kernel_main: CURRENT_ARCH_X86 fail\n");
            break;

        // See:
        case CURRENT_ARCH_X86_64:
            printf("kernel_main: [FAIL] x86_64 is not supported!\n");
            debug_print ("[Kernel] kernel_main: [FAIL] x86_64 is not supported!\n");
            //Status = (int) x86_64main();
            goto fail2;
            break;

        // See:
        // armmain (); ??

        // ...

        default:
            debug_print ("kernel_main: [FAIL] Current arch not defined!\n");
            printf("kernel_main: [FAIL] Current arch not defined!");
            goto fail2;
            break;
    };

    // Something is wrong
    PROGRESS("Kernel:0:7\n"); 
    debug_print ("kernel_main: Something is wrong\n");


//
// Fail
//

// Rule 22:
// " When in doubt, know your way out. "

// Console support.
fail2:
    printf ("kernel_main: Fail. *HANG\n");
    refresh_screen();

// Only serial debug support.
fail1:    
    PROGRESS("Kernel:0:0\n"); 
    debug_print ("[Kernel] kernel_main-fail:  *hang \n");

// No output support.
fail0:
    return (int) (-1);
}



// == Idle thread in ring 0  ===============
// #test

// #bugbug
// This thread will start to run at the moment when
// the init process enable the interrupts.

void early_ring0_IdleThread (void)
{
// #danger: Do NOT change this function.
Loop:
    asm ("sti");
    asm ("hlt");
    goto Loop;
}


//
// End.
//

