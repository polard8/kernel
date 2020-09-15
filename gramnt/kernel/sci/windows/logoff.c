/*
 * File: gramado\logoff\logoff.c
 *
 *  Kernel Mode Logoff Support Routines.
 *
 * isso prepara um ambiente para rodar o processo logoff
 *
 * Descrição:
 *     Módulo do kernel responsável por rotinas de logoff.
 *     Esse módulo faz parte do kernel base.
 *     Encerra uma seção de usuário.
 *     Um usuário sai.
 *     Fecha todos os programas e enserra a sessão do usuário.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - Revision.
 */


#include <kernel.h>





// See: include/gpid.h
int register_logoff_process ( pid_t pid ){

    if (pid<0 || pid >= PROCESS_COUNT_MAX ){
        debug_print("register_logoff_process: pid fail\n");
        return -1;
    }

    if ( __gpidLogoff != 0 ){
        debug_print("register_logoff_process:\n");
        return -1;
    }

    __gpidLogoff = (pid_t) pid;
    
    return 0;
}


//deprecated
int StartLogoff(int argc, char *argv[]) 
{
    panic ("StartLogoff: DEPRECATED");
    return -1;
}


// deprecated
int init_logoff (int argc, char *argv[]) 
{
    panic ("init_logoff: DEPRECATED");
    return -1;
}


//
// End.
//

