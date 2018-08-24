/*
 * File: abort.c
 *
 * Descrição:
 *     Rotina para abortar o Boot Loader.
 *
 * Versão 1.0, 2015.
 */

#include <stdio.h>
 
 
extern void refresh_screen(); 
 
/*
 * abort:
 *     Função principal para abortar o Boot Loader.
 */ 
void abort()
{
	//clear screen
	//... 
	
done:
    printf("abort: Boot Loader abort!");
	refresh_screen();
	while(1){};
};

//
// End.
//
