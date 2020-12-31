/*
 * File: fs/cf.c 
 *
 * Descrição: 
 *     Create File routines.
 * 
 * History:
 *    2015 - Created by Fred Nora.
 *    ...
 */


#include <kernel.h>



/*
 *****************************************************
 * fs_create_file:
 *     Cria um arquivo.
 */
// #todo
// This function could be used to support libc function creat()
// See: we have this on fs.c
int fs_create_file ( char *name )
{
    debug_print("fs_create_file: [FIXME]\n");
    return -1;
}


/*
 * fs_create_dir:
 *     Cria um diretório.
 */
// See: we have this on fs.c
unsigned long fs_create_dir ( char *name, unsigned long id )
{
    debug_print("fs_create_dir: [FIXME]\n");
    return -1;
}


// Create entry.
void 
fs_create_entry ( 
    char *name,             //nome do arquivo
    unsigned long id,       //id do diretorio
    unsigned long eid,      //id da entrada de diretorio
    unsigned long cluster,  //numero do cluster inicial na fat
    unsigned long size )    //tamanho do arquivo.
{
    debug_print("fs_create_entry: [TODO]\n");
}   


void 
fs_create_name ( 
    char *name, 
    unsigned long id, 
    unsigned long eid )
{
    debug_print("fs_create_name: [TODO]\n");
}  


//
// End.
//

