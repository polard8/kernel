/*
 * File: ps/execve.c
 * 
 */

// #todo
// Rotinas de execve podem ir para sysmk.


#include <kernel.h>

//#include "eidata.h"  //Executive Internal Data.


/*
 *******************************************
 * sys_execve:
 * 
 */

// service 248
// execve support.
// executa um programa usando o processo atual.
// #bugbug: A intenção é carregar a imagem num novo endereço físico
// e continuar usando o processo clone criado pode fork.


// IN: name, argv, envp.
int 
sys_execve ( 
    const char *pathname, 
    char *argv[], 
    char *envp[] ) 
{

    debug_print("sys_execve: [TODO] Not implemented yet\n");

    if ( (void*) pathname == NULL )
    {
        debug_print("sys_execve: [ERROR] pathname \n");
    }
    
    // ...
    
    return -1;
}



//
// End.
//

