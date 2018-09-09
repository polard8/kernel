/*
 * main.c - OPER1.BIN
 *
 */
 
 
#include "stddef.h"
#include "stdio.h"


// C function to demonstrate the working of arithmetic operators
int app_test()
{
    int a = 9,b = 4, c;
    
	printf("Testing operators ...\n");
	printf("a=9 b=4\n\n");
	
    c = a+b;
    printf("a+b = %d \n",c);

    c = a-b;
    printf("a-b = %d \n",c);
    
    c = a*b;
    printf("a*b = %d \n",c);
    
    c=a/b;
    printf("a/b = %d \n",c);
    
    c=a%b;
    printf("Remainder when a divided by b = %d \n",c);
	
	
	printf("done.\n");
	
	printf("Testing getchar(). Press a key\n");
    printf("press q to quit .\n\n");
	
	int ch;
	
		
	while(1)
	{
        //
		// Testando getch() #137
		//
		
	    //ch = (int) stdio_system_call(137,0 ,0 ,0);
	
	    ch = (int) getchar();
	    if(ch != -1)
	    {
	        printf("%c",ch);
	    
	        switch(ch)
            {
			   //quit
			   case 'q':
			       goto hang;
				   break;				 
		    }		   
		};
		asm("pause");
	};
    
hang:	
    printf("exit.\n");
	while(1){
		asm("pause");
	}
    //return 0;
};

