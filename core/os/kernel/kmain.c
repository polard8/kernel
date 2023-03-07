
#include <kernel.h>

// kmain:
// Called by x64InitializeKernel() in x64init.c for x64 systems.
// Maybe get some arguments.
// See: kernel.h
int kmain(int arch_type)
{
    //current_arch = arch_type;
    // #hack
    current_arch = CURRENT_ARCH_X86_64;

// Setup debug mode.
// Enable the usage of the serial debug.
// It is not initialized yet.
// #see: debug.c
    disable_serial_debug();
    if (USE_SERIALDEBUG == 1){
        enable_serial_debug();
    }

// Retorna para o assembly e para em hlt.
// see: _kernel_begin in head_64.asm.
    return (int) init_system(current_arch);
}

