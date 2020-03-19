

// testar a implementação de funções com classes em C.
// Ambiente: Gramado 0.1, user mode.


#include <types.h>
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "api.h"


// ?? O que é isso ??
// Me parece que são protótipos para funções que não serão realmente criadas
// os ponteiros chamarão outras funções.
typedef int (*Operation)( int a , int b );
typedef struct _str *(*PrintString)(const char *string);
//...

typedef struct _str STR;
typedef struct _str *PSTR;  
struct _str {

    int result;       // to sotre the resut
    Operation opt;    // funtion pointer 
    PrintString printString;
       //... 
       
    int a;
    void (*fun) (int *a);        // <-- function pointers
       
    //struct _str *(*newPrint)( const char *);
};
 
//struct _str *(*newPrint)( const char *);
 
 
void get_a (int *a) {
	
    printf (" input : ");
    scanf ("%d",a);
};
 
 
struct _str *do_print_string (const char *string){
	
    return (struct _str *) printf (string);
}; 
 
 
/*
 * Add two numbers a and b 
 */
int Add ( int a , int b ){
	
    return (int) (a+b);
};


/*
 * Multiple two numbers a and b 
 */
int Multi ( int a , int b ){
	
    return (int) (a*b);
};


/*
 ******************************* 
 * app_main
 *     Função principal.
 */
 
int app_main ( int argc, char *argv[] ){ 
    
    //
    // test1 ===============================================
    //
    
	printf("test1:\n");   
    printf("======\n");
	
    STR str_obj;
    STR screen;
    
    printf("\nTest 1 ...\n");
    
    // Add.
    //the function pointer variable point to Add function
    str_obj.opt = Add;     
    str_obj.result = str_obj.opt(5,3);
    printf ("The result is %d\n", str_obj.result );

    // Mul.
    //the function pointer variable point to Multi function
    str_obj.opt= Multi;  
    str_obj.result = str_obj.opt(5,3);
    printf ("The result is %d\n", str_obj.result );

    // print ...
    str_obj.printString = do_print_string;  
    str_obj.printString("String 1 ...\n");
    
    //print ...
    screen.printString = do_print_string;
    screen.printString("String 2 ...\n");
    screen.printString("String 3 ...\n");
    
    
    //
    // test2 ===============================================
    //
	
    printf("test2:\n");   
    printf("======\n");

    //scanf 
	
    struct _str test;
    
    test.a = 0;
    test.fun = get_a;
    
    printf("\nTest 2 ...\n");
    printf ("(before): %d\n", test.a);
    
	test.fun(&test.a);
    
	printf ("(after ): %d\n", test.a);
    
    //
    // test3 ===============================================
    //
	
    printf("test3:\n");   
    printf("======\n");
	
    
	printf("malloc\n");
	
	struct _str *s;   
	
    s = (struct _str *) malloc ( sizeof(struct _str) );
    
	//#todo: Precisamos testar se não é null.
	
    s->printString = do_print_string;
    
	printf ("print test.\n");
	
	s->printString("\n");   	
	s->printString("Test 3 ... \n");   

    //
    // test4 ===============================================
    //
	
    printf("test4:\n");   
    printf("======\n");
	
    PSTR x;
    
	x = (PSTR) malloc ( sizeof(struct _str) );   
    
	//#todo: Precisamos testar se não é null.
	
	x->printString = do_print_string;
    
	x->printString("\n"); 
	x->printString("Test 4 ... \n");      
     
    //
    // test ... ?? ===============================================
    //

    
//done:  

    //system ("pause");	
	//return 0;
	
	puts("done");
	
	while (1){
		asm ("pause");
	}
	
};

