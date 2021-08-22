/*
 * File: abort.c
 *
 * Descrição:
 *     Rotina para abortar o Boot Loader.
 *
 * 2015 - Created by Fred Nora.
 */

 
#include <stdio.h>
 
 
extern void refresh_screen(); 

 
/* abort: 
   Função principal para abortar o Boot Loader. */ 

void abort (void){

    printf ("BL.BIN: [ABORT] * System halted\n");
    refresh_screen ();

    while (1){
        asm ("cli");
        asm ("hlt");
    };
}


//
// End.
//
