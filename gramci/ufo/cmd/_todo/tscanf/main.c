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


#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STANDARD_ASCII_MAX 128





/*
 * # main #
 * C function to demonstrate the working of arithmetic operators 
 */

void _main()
{
	
	printf("\n");
	printf("\n");
	printf("TSCANF.BIN:\n");
	printf("Testing scanf ... \n\n");
	
    //#testing 
	//=============================
    
	//string
	char str[80];
	printf("\n==============\n");
    printf("Enter a string:\n");
    //scanf(" %s",str);	//isso funciona e está no padrão.
	//scanf(" %s",&str);   //isso funciona e está no padrão.
	scanf(" %s",&str[0]);   //isso funciona e está no padrão.
	printf("You entered { %s }.\n\n",str);  

	//char
    // OK. Isso está no padrão..
	char ch;
    printf("\n==============\n");
	printf("Enter a char:\n");
    scanf("%c",&ch);	
	printf("You entered { %c }.\n\n",ch);  
	
	
	int i;
	printf("\n==============\n");
    printf("Enter a number:\n");
    scanf("%d", &i);	
	printf("You entered { %d }.\n\n",i);  	
    
	
 //================	
	
	printf("done.\n");
	
	while(1){
		asm("pause");
	}
    
    //return 0;
    exit(0);
};

