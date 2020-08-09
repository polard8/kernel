/*
 * File: fs/cf.c 
 *
 * Descrição: 
 *     Create File.
 *     Rotinas criação de arquivos.
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

int fs_create_file ( char *name )
{
    debug_print("fs_create_file: [TODO]\n");

    /*
    return (int) fsSaveFile ( 
                     (char *) name, 
                     (unsigned long) 2,     // sectors
                     (unsigned long) 1024,  // bytes
                     (char *) file_address, // address
                     (char) 0x20 );         // flags  
    */                 
                     
    return -1;
}


/*
 * fs_create_dir:
 *     Cria um diretório.
 */

unsigned long fs_create_dir ( char *name, unsigned long id )
{
    debug_print("fs_create_dir: [TODO]\n");
    //return fs_create_file( name, id ); 
    return 1;
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
   // return;
}   


void 
fs_create_name ( 
    char *name, 
    unsigned long id, 
    unsigned long eid )
{
    //return;
}  


//
// End.
//

