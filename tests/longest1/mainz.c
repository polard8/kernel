/*
 * main.c - OPER1.BIN
 *
 */
 
 
#include "stddef.h"
#include "stdio.h"


// C function to demonstrate the working of arithmetic operators
int app_test()
{
    unsigned char count;
	unsigned char standard_ascii_max = 128;
	
	
	printf("ASCII.BIN:\n");
	printf("Show ascii table ...\n\n");
	
    for( count=0; count<standard_ascii_max; count++ )
    {
		printf(" %d - %c",count,count);
        if( count % 4 == 0 ){
            printf("\n");
		}
    };	
	
	printf("done.\n");
	
	while(1){
		asm("pause");
	}
    
    //return 0;
};

