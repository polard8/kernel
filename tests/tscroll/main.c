/*
 * main.c - 
 *
 */
 
 
#include "stddef.h"
#include "stdio.h"




//
// Imprimir uma quantidade de caracteres o suficiente para 
// preencher uma tela com eles.
// Se não preencher a tela é porque falhou.
// A rotina de scroll não está aqui. Apenas estamos 
// preenchendo a tela.
//

void _tMain( int argc, char *argv[], char *envp[] )
{
    int i;
	
	int CharsPerLine = 100; //(800/8);
	int NumberOfLines = 75; //(600/8);
	
	
	printf("TSCROLL:\n");
	printf("Testing scroll ...\n");
	
	
    for( i=0; i< (CharsPerLine*NumberOfLines); i++ )
	{
		printf("T");
    };	
		
	
	
hang:	
    printf("TSCROLL: Done!");
	while(1)
	{
		asm("pause");
	}
};

