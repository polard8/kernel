/*
 * File: fs/format.c
 *
 * 
 * Descrição:
 *     Serviços de formatação de disco e volumes.
 *     Formata a tabela de partições no mbr.
 *     Altera valores no mbr e metafile. 
 *
 * todo:
 *     Serviços de formatação podem ir para um aplicativo.
 * 
 * History:
 *    2015 - Created by Fred Nora.
 *    ...
 */
 

#include <kernel.h>


void fs_delete_entry ( unsigned long id, unsigned long eid )
{
    //return;
}



/*
 * fsClearFat:
 *      Zera o buffer e grava zeros no hd.
 */

// #todo
// Cool!

void fsClearFat (void)
{
    debug_print("fsClearFat: [TODO]\n");
}


//
// End.
//

