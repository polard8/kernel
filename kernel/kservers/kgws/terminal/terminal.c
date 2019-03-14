
// terminal.c

//   This is the kserver part for the virtual terminal support.
//   Initialization routines needs to call this file to setup 
//   the virtual terminal functionalities.

#include <kernel.h>


//todo
//set_terminal_pid
//set_terminal_tid


//todo
//criar um diálogo consistente com o servidor de terminal.
//assim ele pode ser chamado e oferecer vários serviços.

unsigned long 
terminal_dialog ( struct window_d *window, 
                  int msg, 
                  unsigned long long1, 
                  unsigned long long2 ) 
{
    //# todo
    return 0;	
}

