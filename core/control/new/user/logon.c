
// logon.c

#include <kernel.h>  

int init_logon_manager (void)
{
// #todo
// #bugbug

    debug_print("init_logon_manager: [TODO FIXME]\n");

// #bugbug
// Is it the first time? Or not?

    gui = (void *) kmalloc ( sizeof(struct gui_d) );

    if ( (void *) gui == NULL )
    {
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

// #test
// Mostrando as mensagens antes de pintarmos a primeira janela.

    //#debug
    //breakpoint
    //refresh_screen();
    //while(1){}

    // ...

    return 0;
}

