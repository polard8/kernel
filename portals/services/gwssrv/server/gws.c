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



// #todo
// Sleep if there is no message in the queue.
void gwssrv_wait_message(void)
{
    // #todo
    // block()
    
    // #using this one for now.
    gwssrv_yield();
}


void gws_show_backbuffer(void)
{

    // #debug
    // [Deprecated] Using the kernel service.
    // gde_show_backbuffer();

    // #todo:
    // Create this flag. 
    // if (!paint_ready) return;


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



int gwssrv_init_globals(void)
{
    // buffers
    ____BACKBUFFER_VA  = (unsigned long) gde_get_system_metrics(12);
    ____FRONTBUFFER_VA = (unsigned long) gde_get_system_metrics(11);


    // Screen
    SavedX = gde_get_system_metrics(1);
    SavedY = gde_get_system_metrics(2);
    __device_width  = SavedX;
    __device_height = SavedY;


    // bpp
    SavedBPP = (unsigned long) gde_get_system_metrics(9);


    //background_color = xCOLOR_GRAY3;
   
   
   gwssrv_initialize_color_schemes(ColorSchemeHumility);
   gwssrv_select_color_scheme(ColorSchemeHumility);
   
   
    //...


    return 0;
}


/*
 ************************************
 * gwsInit:
 *     Initialize the server. 
 *
 */
//int gwsInit (void){
int gwsInit (){

    //paint_ready = FALSE;


    // Initializing globals.
    gwssrv_init_globals();

    
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
        CurrentScreen->id = 0; 
        CurrentScreen->used = 1; 
        CurrentScreen->magic = 1234; 

        // Serão configurados depois.
        // Por enquanto estamos apenas limpando.
        CurrentScreen->width = 0;
        CurrentScreen->height = 0;
        CurrentScreen->font_size = 0;
        CurrentScreen->char_width  = 0;
        CurrentScreen->char_height = 0;
        CurrentScreen->backbuffer  = NULL;
        CurrentScreen->frontbuffer = NULL;
        //...

    };


    // font support.
    gwssrv_init_font();

    // char support
    gwssrv_init_char();
    

    //windows
    gwssrv_init_windows();    
            

    //
    // gui structure.
    //
    
    // First level structure for the GUI.
    gui = (void *) malloc( sizeof( struct gui_d) );
    if ( (void *) gui == NULL )
    {
        debug_print("gwsInit: gui\n");
        return -1;
    }


    if ( (void *) gui != NULL )
    {
        // (root window)
        gui->screen = (struct gws_window_d *) createwCreateWindow ( WT_SIMPLE, 
                                              1, 1, "screen-window",  
                                              0, 0, 
                                              __device_width, __device_height,   
                                              NULL, 0, xCOLOR_GRAY3, xCOLOR_GRAY3 );

        if ( (void*) gui->screen == NULL){
            debug_print("gwsInit: screen window\n");
            return -1;    
        }

        //#test
        gwsDefineInitialRootWindow (gui->screen);
    
        // main window.
        // desktop area without the bars.
        // For maximized apps.
        gui->main = gui->screen;
    } 

    //
    // Refresh
    //
    
    // #todo
    // Configurar a estrutura de cliente.
    // Inicializar a lista de clientes.
    
    // #kgws.
    // Isso usa o kernel.
    // #todo: Acho que nessa hora ja temos uma rotina própria válida.

    //paint_ready = TRUE;
    
    gde_show_backbuffer();
    
    return 0;
}




// Função padrão para todos os servidores ???
// #todo: temos que criar isso.
int serverInit (){
	
	printf ("serverInit: Initializing gws server ...\n");
	
    return (int) gwsInit();
}

