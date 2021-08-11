

#include <kernel.h>


int desktopdummmy;    

/*
 * init_desktop_list:
 *     Inicializa o array de ponteiros de desktop.
 */


void init_desktop_list (void)
{
    int i=0;

    while ( i < DESKTOP_COUNT_MAX )
    {
        desktopList[i] = 0;
        i++; 
    };
}



/*
 ***********************************************
 * init_desktop:
 *     Inicializa o desktop 0.
 *     int ?
 */


void init_desktop (void)
{
    int i=0;

    debug_print ("init_desktop:\n");
    //printf("init_desktop: Initializing..\n");


    desktops_count = 0;

// List

    init_desktop_list();

//
// Struct
//

    // Creatin the desktop0. 

    desktop0 = (void *) kmalloc ( sizeof(struct desktop_d) );

    if ( (void *) desktop0 == NULL ){
        panic ("init_desktop: desktop0\n");
    }else{

        desktop0->id = 0;
        
        desktop0->used  = TRUE;
        desktop0->magic = 1234;

        //todo: object
        
        desktops_count = 1;

        desktop0->lTail = 0;
        desktop0->lHead = 0;
        for (i=0; i<8; i++){
            desktop0->list[i] = (unsigned long) 0;
        };


	    // #todo
	    // Depois precisamos colocar aqui
	    // o pid do processo kernel.
	    // Cada desktop terá sem ws e sua wm.

        desktop0->ws = -1;
        desktop0->wm = -1;
        // ...
   
 
        // Registrando na lista

        desktopList[0] = (unsigned long) desktop0;
        //RegisterDesktop (desktop0); 
 
        set_current_desktop (desktop0);  

        //set_current_menuwindow (desktop0, NULL); 
        //set_current_foreground (desktop0, NULL); 
        //set_current_messagewindow (desktop0, NULL); 
        //set_current_traywindow (desktop0, NULL); 
        //set_current_tooltipwindow (desktop0, NULL); 
        //set_current_sysMenu (desktop0, NULL);
        //set_current_dialogsysMenu (desktop0, NULL);
        //set_current_menuHScroll (desktop0, NULL);
        //set_current_menuVScroll (desktop0, NULL);

        //desktop0->room = NULL;
    };
}

void set_current_desktop ( struct desktop_d *desktop )
{
    if ( (void *) desktop == NULL )
    { 
        return; 
    }

    current_desktop = (int) desktop->id;

    CurrentDesktop = desktop;
}

void *get_current_desktop (void)
{
    //Check limits.

    if ( current_desktop < 0 || 
         current_desktop >= DESKTOP_COUNT_MAX )
    {
        return NULL;
    }
    
    return (void *) desktopList[current_desktop];
}


int get_current_desktop_id (void)
{
    return (int) current_desktop;
}

/*
 * RegisterDesktop:
 *     Registrando um desktop numa lista de desktops.
 *     @todo: Mudar para desktopRegisterDesktop(.). 
 */

int RegisterDesktop (struct desktop_d *d)
{
    int Offset = 0;


    if ( (void *) d == NULL ){
        debug_print ("RegisterDesktop: [FAIL] d\n");
        return (int) 1;  
    }


	// #bugbug: 
	// Pode aparacer um loop infinito aqui.
	// #todo: usar for.

    while ( Offset < DESKTOP_COUNT_MAX )
    {
        if ( (void *) desktopList[Offset] == NULL )
        {
            desktopList[Offset] = (unsigned long) d; 
            
            d->id = Offset;
            
            return 0;
        }

       Offset++;
    };

	// Fail.
	
    return (int) 1;
}

/*
 * CreateDesktop:
 *     Cria um desktop em uma window station.
 */

void *CreateDesktop ( struct room_d *room )
{
    struct desktop_d *Current;
    struct desktop_d *Empty;

    int i=0;
    //... 


    if ( (void *) room == NULL ){
        debug_print ("CreateDesktop: [FAIL] room\n");
        return NULL; 
    }

	//
	// #todo: 
	// O usuário precisa de permissão pra criar desktops.
	//


    Current = (void *) kmalloc ( sizeof(struct desktop_d) );

    if ( (void *) Current == NULL ){
        panic ("CreateDesktop: Current\n");
    } else {
        Current->room = (void *) room;

		//continua...
    };


    while ( i < DESKTOP_COUNT_MAX )
    {
        Empty = (void *) desktopList[i];

        if ( (void *) Empty == NULL )
        {
            desktopList[i] = (unsigned long) Current;

            Current->id = i;

            return (void *) Current;
        }

        i++;
    };

    return NULL;
}


int desktop_setup_ws ( struct desktop_d *desktop, int ws_pid )
{
    debug_print ("desktop_setup_ws: \n");

    if ( (void *) desktop != NULL )
    {
        desktop->ws = ws_pid;
        return 0;    
    }

    return -1;
}


int desktop_setup_wm ( struct desktop_d *desktop, int wm_pid )
{
    debug_print ("desktop_setup_wm: \n");

    if ( (void *) desktop != NULL )
    {
        desktop->wm = wm_pid;
        return 0;
    }

    return -1;
}


























