// comp.c


// window server routines.
#include <gws.h>

// #todo
// Create some configuration globals here
// int gUseSomething = TRUE;
// ...

/*
 * compositor:
 * 
 * 
 */

// Respeitando a z-order.
// #todo.
// Check for dirty rectangles and refresh'em all.
// Show all the windows respecting the zorder.

// #goal
// Repintar os retângulos e as janelas marcadas como dirty.
// O efeitos serão aplicados dentro das janelas.
// Teremos o depth-buffer para janelas e não par aa tela toda.
// Poderemos usar janelas em full screen.
// Clipping window.

void compositor (void)
{
    // + repinta as janelas.
    // + refresh nos retangulos ou tela toda.
    // + rasterization.
    // + raytracing.

    gwssrv_debug_print("compositor:\n");

    // Repinta as janelas e refresh nos retangulos ou tela toda.
    // See: wm.c

    wm_process_windows();
    
    // rasterization();

    // raytracing();

    gwssrv_debug_print("compositor: done\n");
}

