

   // window.c
   
#include <api.h>
#include <gws.h>


   
/*
 *******************************************************
 * gwsRegisterWindow: 
 *     Register a window.
 */
 
// OUT:
// < 0 = fail.
// > 0 = Ok. (index)
 
int gwsRegisterWindow (struct gws_window_d *window){

    struct gws_window_d *tmp; 

    int __slot=0;



    if ( (void *) window == NULL ){
        //gws_debug_print ("gwsRegisterWindow: window struct\n");
        return (int) -1;    
    }


	// Contagem de janelas e limites.
	// (é diferente de id, pois id representa a posição
	// da janela na lista de janelas).

    windows_count++;

    if ( windows_count >= WINDOW_COUNT_MAX ){
        //gws_debug_print ("gwsRegisterWindow: Limits\n");
        printf ("gwsRegisterWindow: Limits\n");
        return -1;
    }


    // Search for empot slot
    
    
    for (__slot=0; __slot<1024; __slot++)
    {
        tmp = (struct gws_window_d *) windowList[__slot];

        // Found!
        if ( (void *) tmp == NULL ){
            windowList[__slot] = (unsigned long) window; 
            window->id = (int) __slot;
            return (int) __slot;
        }
    };

// fail
    //gde_debug_print("No more slots\n");
    return (int) (-1);
}

/*
 * get_active_window:
 *     Obtem o id da janela ativa.
 *     @todo: Mudar para windowGetActiveWindowId().
 */


int get_active_window ()
{
    return (int) active_window;  
}


/*
 * set_active_window:
 */

void set_active_window (int id){

	// @todo: Limits. Max.
    if (id < 0)
        return;
    

    active_window = (int) id;
}


// Pegando a z-order de uma janela.
int get_zorder ( struct window_d *window ){

    if ( (void *) window != NULL ){
        return (int) window->zIndex;
    }

    return (int) -1;
}

int get_top_window (){
	
	return (int) top_window;
}


//Setando a top window.
void set_top_window (int id){
	
	top_window = (int) id;
}



/*
 *********************************************
 * gws_resize_window:
 *     Muda as dimensões da janela.
 */
 
int 
gws_resize_window ( 
    struct gws_window_d *window, 
    unsigned long cx, 
    unsigned long cy )
{

    if ( (void *) window == NULL ){
        //gde_debug_print("gws_resize_window:\n"); 
        return (int) (-1); 

    } else {
    
		//@todo: Checar limites.

        window->width  = (unsigned long) cx;
        window->height = (unsigned long) cy;
    };


    return 0;
}


/*
 ****************************************************
 * gws_replace_window:
 *     Muda os valores do posicionamento da janela.
 */	
 
int 
gws_replace_window ( 
    struct gws_window_d *window, 
    unsigned long x, 
    unsigned long y )
{

    if ( (void *) window == NULL ){
        return (int) (-1);

    } else {

        //@todo: Checar limites.
	
        window->left = (unsigned long) x;
        window->top = (unsigned long) y;
	};

    return 0;
}



/*
 * gwsWindowLock:
 *     Bloqueia uma janela.
 *     @todo: Quem pode realizar essa operação??
 */
 
void gwsWindowLock (struct gws_window_d *window){

    if ( (void *) window == NULL )
        return;


    window->locked = (int) WINDOW_LOCKED;  //1.
}


/*
 * gwsWindowUnlock:
 *     Desbloqueia uma janela.
 *     @todo: Quem pode realizar essa operação??
 */
 
void gwsWindowUnlock (struct gws_window_d *window){

    if ( (void *) window == NULL )
        return;


    window->locked = (int) WINDOW_UNLOCKED;  //0.
}











