
#include <kernel.h>

// kmain:
// Called by START in head_64.asm.
// See: kernel.h
int kmain(int arch_type)
{
// #
// Maybe get some arguments.

// #hack
    current_arch = CURRENT_ARCH_X86_64;

    asm ("cli");

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
    return (int) kmain2(current_arch);
}

