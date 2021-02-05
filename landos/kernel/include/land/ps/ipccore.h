/*
 * File: ipccore.h 
 *
 *    ?? What 
 *  
 *    2019 - Created by Fred Nora. 
 */


#ifndef  ____IPCCORE_H
#define ____IPCCORE_H    1



// #todo
// Repensar a finalidade disso.
// Me parece um gerenciamento de um grupo de componentes do sistema.

// ??
// para se conetar com os servidores do módulo gramado core.


// Registra um dos servidores do gramado core.
int 
ipccore_register ( 
    int server_index, 
    struct process_d *process, 
    struct thread_d *thread );


unsigned long 
ipccore_services ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 );


int ipccore_open ( int pid, int server_index );
int ipccore_close ( int pid, int server_index );



#endif    



//
// End.
//








