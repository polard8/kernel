
// kmain.c

#include <kernel.h>


// ::(3)
// kmain:
// Called by x64InitializeKernel() in x64init.c for x64 systems.
// Maybe get some arguments.
// See: kernel.h
int I_kmain(int arch_type)
{
// We don't have any print support yet.

    // #hack
    current_arch = CURRENT_ARCH_X86_64;
    //current_arch = (int) arch_type;

// Setup debug mode.
// Enable the usage of the serial debug.
// It is not initialized yet.
// #see: debug.c
    disable_serial_debug();
    if (USE_SERIALDEBUG == 1){
        enable_serial_debug();
    }

// see: init.c
    return (int) I_init_main(current_arch);
}

