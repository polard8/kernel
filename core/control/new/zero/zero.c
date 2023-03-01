
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
}

// see:
// mm/mmrt.c
void zero_initialize_runtime(int arch_id)
{
    Runtime_initialize(arch_id);
}

// see:
// dev/chardev/display/bg.c
void zero_initialize_background(void)
{
    Background_initialize(COLOR_KERNEL_BACKGROUND);
}

// See:
// ke/x86_64/x64init.c
int zero_initialize_x64(void)
{
    return (int) (int) I_x64main();
}










