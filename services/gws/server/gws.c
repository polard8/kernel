/*
 * File: gws.c
 * 
 *     Part of the Gramado Window Server.
 *
 * History:
 *     2019 - Created by Fred Nora.
 *     2020    
 */




//
#include <stddef.h>

//Using some system resources.
#include <api.h>

// window server routines.
#include <gws.h>


//fonts
#include "nc2.h"




unsigned long __device_width;
unsigned long __device_height;


void gws_show_backbuffer(void)
{
    // #debug
    // Using the kernel service.
    // gde_show_backbuffer();

    if( (void *) gui->screen == NULL ){
        debug_print("gws_show_backbuffer: [PANIC] screen window fail\n");
        return;
    }
    gws_show_window_rect(gui->screen);
}


unsigned long gws_get_device_width(void)
{
    return (unsigned long) __device_width;
}



unsigned long gws_get_device_height(void)
{
    return (unsigned long) __device_height;
}






/*
 ************************************
 * gwsInit:
 *     Initialize the server. 
 *
 */

int gwsInit (){

    int i=0;
    
    
    // #todo
    // Configurar as estruturas em ordem:
    // Current display, current screen, current root window.


    CurrentDisplay = (void *) malloc (sizeof(struct gws_display_d));
    if( (void*) CurrentDisplay == NULL){
        debug_print("gwsInit: CurrentDisplay\n");
        return -1;
        //while(1);
    }else{
        CurrentDisplay->id = 0; //
        CurrentDisplay->used = 1; //
        CurrentDisplay->magic = 1234; //
        
        CurrentDisplay->fd = 0;
        
        //...
    };
    
    
    CurrentScreen  = (void *) malloc (sizeof(struct gws_screen_d));
    if( (void*) CurrentScreen == NULL){
        debug_print("gwsInit: CurrentScreen\n");
        //while(1);
    }else{
        CurrentScreen->id = 0; //
        CurrentScreen->used = 1; //
        CurrentScreen->magic = 1234; //
        //...
    };


    
    // Initializing the counter.
    windows_count = 0;

   
    for (i=0; i<1024; i++)
        windowList[0] = 0;


    // Fonte atual.
    gws_currentfont_address = (unsigned long) &font_nelson_cole2[0]; 
    gfontSize = 8;

    //CurrentScreen->font_size = gfontSize;

    // draw char support
    // #todo: Essa configuração ficará aqui, dependendo da fonte.
    gcharWidth = 8;   //gde_get_system_metrics (7);
    gcharHeight = 8;   //gde_get_system_metrics (8);
    
    
    //CurrentScreen->char_width = gcharWidth;
    //CurrentScreen->char_height = gcharHeight;
    
    //
    // Screen
    //
    
    __device_width =  gde_get_system_metrics (1);
    __device_height = gde_get_system_metrics (2);
    
    SavedX = __device_width;
    SavedY = __device_height;
    
    
    //CurrentScreen->width = __device_width;
    //CurrentScreen-height = __device_height;
    
    //
    // bpp
    //
    
    //#test
    SavedBPP = (unsigned long) gde_get_system_metrics (9);
    
    
    //#obs:
    //Se for possível vamos copiar do backbuffer para o front buffer
    //daqui do gws e não chamaremos o kernel para isso.
    
    //ok
    ____BACKBUFFER_VA = (unsigned long) gde_get_system_metrics (12);
    
    //#test
    ____FRONTBUFFER_VA = (unsigned long) gde_get_system_metrics (11);
    
    
    
    
    
    //
    // gui structure.
    //
    
    // First level structure for the GUI.
    gui = (void *) malloc ( sizeof( struct gui_d) );
    
    if ( (void *) gui == NULL ){
        debug_print("gwsInit: gui\n");
        return -1;
    }
    
    // (root window)
    gui->screen = (struct gws_window_d *) createwCreateWindow ( WT_SIMPLE, 
                                          1, 1, "screen-window",  
                                          0, 0, 
                                          __device_width, __device_height,   
                                           NULL, 0, xCOLOR_GRAY3, xCOLOR_GRAY3 );

    if( (void*) gui->screen == NULL){
        debug_print("gwsInit: screen window\n");
        return -1;    
    }

    //#test
    gwsDefineInitialRootWindow (gui->screen);
    
    
    // main window.
    // desktop area without the bars.
    // For maximized apps.
    gui->main = gui->screen;

    
    
    // #todo
    // Configurar a estrutura de cliente.
    // Inicializar a lista de clientes.
    
    // #kgws.
    // Isso usa o kernel.
    gde_show_backbuffer ();

    return 0;
}




// Função padrão para todos os servidores ???
// #todo: temos que criar isso.
int serverInit (){
	
	printf ("serverInit: Initializing gws server ...\n");
	
    return (int) gwsInit();
}

