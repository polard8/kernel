/*
 * main.c - TASCII.BIN
 *
 * Aplicativo de teste para o sistema operacional Gramado.
 * Exibe os acarteres da tabela ascii.
 * @todo: Pode haver alguma seleção, baseada em argumentos.
 * @todo: usar apenas a libC.
 *
 * 2018 - Fred Nora.
 */
 
 
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define STANDARD_ASCII_MAX 128

/*
 * # main #
 * C function to demonstrate the working of arithmetic operators 
 */

int main (int argc, char *argv[] ){
	
    unsigned char count;
	unsigned char standard_ascii_max = STANDARD_ASCII_MAX;
	
	//libc_set_output_mode (LIBC_DRAW_MODE);
	
	printf ("\n");
	printf ("ASCII.BIN:\n");
	printf ("Show ascii table ...\n");
	printf ("\n");
	
	
	//libc_set_output_mode (LIBC_NORMAL_MODE);
	
    for ( count=0; count<standard_ascii_max; count++ )
    {
		printf (" %d - %c", count, count);
        
		if ( count % 4 == 0 )
		{
            printf("\n");
		}
    };	
	
	printf ("\n");
	printf ("Done!\n");
	
	// #bugbug
	// Falha ao sair. Talvez falte o crt0.o
	//while (1){}
	
    return 0;
}





