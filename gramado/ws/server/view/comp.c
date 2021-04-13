// comp.c


// window server routines.
#include <gws.h>


// Repintar os retângulos e as janelas marcadas como dirty.
// Respeitando a z-order.
// #todo.
// Check for dirty rectangles and refresh'em all.
// Show all the windows respecting the zorder.

void compositor (void)
{
    // + repinta as janelas.
    // + refresh nos retangulos ou tela toda.
    // + rasterization.
    // + raytracing.


    gwssrv_debug_print("compositor:\n");

    // Repinta as janelas e refresh nos retangulos ou tela toda.
    // See: window.c
    wm_process_windows();
    
    // rasterization();
    // raytracing();


    gwssrv_debug_print("compositor: done\n");
}

