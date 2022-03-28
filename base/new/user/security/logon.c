

#include <kernel.h>  


int init_logon_manager (void)
{
    //#todo

    struct window_d  *hWindow; 
    int z=0;


    debug_print("init_logon_manager: [TODO FIXME]\n");

    //printf ("init_logon_manager: Initialize version support \n");
    //systemSetupVersion();

    gui = (void *) kmalloc ( sizeof(struct gui_d) );

    if ( (void *) gui == NULL ){
        panic ("init_logon_manager: [FAIL] gui\n");
    }

    //
    // TTY
    //


    // tty support.
    // As mensagens do kernel precisam usar esses parametros.
    // o kernel usa a tty0.


     // Limpa a lista
     printf ("init_logon_manager: Initializing tty module\n");
     //tty_init_module();

     // Limpa a lista de terminais virtuais tamb�m.
     printf ("init_logon_manager: Initializing vt module\n");
     //vt_init_module();


    // See: userenv.c
    User_initialize();


    // See: ws.h
    // hostname:Displaynumber.Screennumber
    // gramado:0.0

    // display and screen
    current_display = 0;
    current_screen  = 0;

    // window and menu.
    current_window  = 0;
    current_menu    = 0;    


    // Initializing zorder list.

    for ( z=0; z < KGWS_ZORDER_MAX; z++ )
    {
        Windows[z] = (unsigned long) 0;
    };
    zorderCounter = 0;



        // #test
        // Mostrando as mensagens antes de pintarmos a primeira janela.
        
        //#debug
        //breakpoint

        //refresh_screen();
        //while(1){}



        // Inicia estrutura.
        // window.c

//#ifdef KERNEL_VERBOSE
		//printf ("init_logon_manager: initializing windows\n");   
//#endif
        //init_windows();


		//menus.
//#ifdef KERNEL_VERBOSE
		//printf("create_logon: initializing menus\n");
//#endif
        //init_menus();

	    // ...


    return 0;
}

