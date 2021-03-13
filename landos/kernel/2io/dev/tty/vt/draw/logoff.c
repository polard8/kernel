/*
 * File: logoff.c
 *
 *  Kernel Mode Logoff Support Routines.
 *
 * isso prepara um ambiente para rodar o processo logoff
 *
 * Descri��o:
 *     M�dulo do kernel respons�vel por rotinas de logoff.
 *     Esse m�dulo faz parte do kernel base.
 *     Encerra uma se��o de usu�rio.
 *     Um usu�rio sai.
 *     Fecha todos os programas e enserra a sess�o do usu�rio.
 *
 * History:
 *     2015 - Created by Fred Nora.
 */


#include <kernel.h>



// See: include/gpid.h
int register_logoff_process ( pid_t pid ){

    if (pid<0 || pid >= PROCESS_COUNT_MAX ){
        debug_print("register_logoff_process: pid fail\n");
        return -1;
    }

    // Global variable.

    if ( __gpidLogoff != 0 ){
        debug_print("register_logoff_process:\n");
        return -1;
    }

    __gpidLogoff = (pid_t) pid;
    
    return 0;
}


// #todo
int init_logoff (int mode) 
{
    panic ("init_logoff: [TODO]");
    return -1;
}


//
// End.
//

