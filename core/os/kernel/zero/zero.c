
// zero.c
// Wrappers for kernel initialization routines.

#include <kernel.h>

// As estruturas de console sao estruturas de tty,
// mas sao um array de estruturas, nao precisa de malloc,
// por isso podem ser chamadas nesse momento.
// #test
// We need to test it better.
// see:
// dev/chardev/tty/console.c
// crt/kstdio.c
void zero_initialize_virtual_consoles(void)
{
    VirtualConsole_initialize();
}

// See: 
// dev/chardev/display/bldisp/bldisp.c
void zero_initialize_video(void)
{
    //#breakpoint: BLACK ON WHITE.
    //ok, funcionou na maq real no modo jail, provavelmente 320x200.
    //for (i=0; i< 320*25; i++){ fb[i] = 0; };
    //while(1){asm("hlt");};

    Video_initialize();
    PROGRESS("zero_initialize_video: Initialized\n");
}

// Runtime
// #bugbug:
// We need the runtime initialization for the messages.
// What about to initialize it early?! now!!!!
// #bugbug
// Here the background is not initialized yet,
// so, we have a lot of dirty things.
// See: runtime.c
// Runtime:
// System memory support.
// Heap, stack, memory usage and frames.
// see:
// mm/mmrt.c
void zero_initialize_runtime(int arch_id)
{
    Runtime_initialize(arch_id);
    PROGRESS("zero_initialize_runtime: Initialized\n");
}

// see:
// dev/chardev/display/bg.c
void zero_initialize_background(void)
{
    Background_initialize(COLOR_KERNEL_BACKGROUND);
    PROGRESS("zero_initialize_background: ok\n");
}

// See:
// ke/x86_64/x64init.c
int zero_initialize_x64(void)
{
    return (int) (int) I_x64main();
}

// Setup Default kernel font.
// ROM BIOS 8x8 font.
// see: font.c
void zero_initialize_default_kernel_font(void)
{
    gwsInitializeDefaultKernelFont();
    PROGRESS("zero_initialize_default_kernel_font: ok\n");
}


// =================================
// Console:
// We have a virtual console and we can use the printf.
// This is the first message in the screen.
// see: tty/console.c
void zero_show_banner(void)
{
    char product_string[256];
    char build_string[256];
    size_t size=0;

// product string
    sprintf(product_string,PRODUCT_NAME);
    size = sizeof(PRODUCT_NAME);
    product_string[size+1]=0;

// build string
    sprintf(build_string,BUILD_STRING);
    size = sizeof(BUILD_STRING);
    build_string[size+1]=0;
    
// Crear screen and print version string.
    console_banner( product_string, build_string, 0 );
}


int zero_initialize_arch(int arch_type)
{
//=============================
// Initialize archtecture dependent stuff.

    int Status = FALSE;

    switch (arch_type){

    case CURRENT_ARCH_X86_64:
        //debug_print ("kernel_main: [CURRENT_ARCH_X86_64] calling x64main() ...\n");
        //zero_initialize_background();
        Status = (int) zero_initialize_x64();
        if (Status == TRUE)
        {
            // Do not return!
            //booting_end(CURRENT_ARCH_X86_64);
            
            //ok
            return TRUE;
        }
        debug_print ("kernel_main: CURRENT_ARCH_X86_64 fail\n");
        x_panic("Panic: Error 0x01");
        //#todo: return -1;
        break;

    // See:
    // armmain (); ??

    // ...

    default:
        debug_print ("kernel_main: Current arch not defined!\n");
        //system_state = SYSTEM_ABORTED;
        x_panic("Error 0x03");
        //#todo: return FALSE;
        break;
    };

// Fail
fail:
    return FALSE;
}










