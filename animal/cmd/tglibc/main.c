
#include <types.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>


#include <stdio.h>

#include <unistd.h>

//#include <api.h>


#include <stubs/gramado.h>


//função interna.
//int main ( int argc, char *argv[] );

int test1(void);

#define LSH_TOK_DELIM " \t\r\n\a" 
#define SPACE " "
#define TOKENLIST_MAX_DEFAULT 80

//entry point

void crt0()
{

    int value = 1234;

    unsigned long ch = '.';
    unsigned long ch2 = '.';
    unsigned long ch3 = '.';

    // Imprimeindo usando a systemcall do gramado.

    gramado_system_call ( 65, (unsigned long) ch, (unsigned long) ch, 
        (unsigned long) ch );

    gramado_system_call ( 65, (unsigned long) ch2, (unsigned long) ch2, 
        (unsigned long) ch2 );


    // Imprimindo usando a biblioteca glibc

    putch ( (char) ch3 );
    puts ("  \n\n  Aplicativo com glibc 0.1.1 \n\n");


	//#bugbug
	/* STATE 3: AWAITING MODIFIER CHARS (FNlh) */
	//aparece a mensagem nesse estagio da funçao >>> 'hee4'

    printf ("Testing printf ... value=%d  hex=%x \n", value, value );

    //
    // Test 1.
    //

    test1 ();

    printf ("done. *hang");
    while (1){}
    //return 0;
}


int test1 (void){

    char buf[64];

    sprintf (buf, "%u score and %i years ago ... \n", 4, -7);
    puts (buf);
    printf ("\n");

    sprintf (buf, "-1L == 0x%lX == octal %lo \n", -1L, -1L);
    puts (buf);
    printf ("\n");
    
    printf ("<%-08s> and <%08s> justified strings \n", "left", "right");
    printf ("\n");

    return 0;
}

/*
int crt02 (){
	
	printf("crt0: GLIBCT1.BIN: ");
	printf("Testing glibc 0.1.1 ... *hang\n");
	while(1){}
	
	
	
	char *tokenList[TOKENLIST_MAX_DEFAULT];
	char *token;
	int token_count;
	int index;	
	
	int retval;
	
	// #importante
	// Linha de comandos passada pelo shell.
	char *shared_memory = (char *) (0xC0800000 -0x100);	
	
	
//#ifdef TEDITOR_VERBOSE	
	
	//printf("\n");
	//printf("crt0:\n");
	//printf("Initializing teditor.bin ...\n\n");	
	//printf("\n");
	//printf(".\n");
	//printf("..\n");
	//printf("# MESSAGE={%s} #\n", shared_memory );
	//printf("..\n");
	//printf(".\n");
	//printf("\n");
	
	//#debug
	//while(1){
	//	asm ("pause");
	//}
	
//#endif
	

    // Criando o ambiente.
	// Transferindo os ponteiros do vetor para o ambiente.

	tokenList[0] = strtok ( &shared_memory[0], LSH_TOK_DELIM );
	
 	// Salva a primeira palavra digitada.
	token = (char *) tokenList[0];
 
	index = 0;                                  
    while ( token != NULL )
	{
        // Coloca na lista.
        // Salva a primeira palavra digitada.
		tokenList[index] = token;

		//#debug
        //printf("shellCompare: %s \n", tokenList[i] );
		
		token = strtok ( NULL, LSH_TOK_DELIM );
		
		// Incrementa o índice da lista
        index++;
		
		// Salvando a contagem.
		token_count = index;
    }; 

	//Finalizando a lista.
    tokenList[index] = NULL;	
	
	
 
	

 
	
	//#todo: suspenso.
    //retval = (int) main ( token_count, tokenList );
	
	switch (retval)
	{
		case 0:
		    printf("crt0: main returned 0.\n");
			exit (0);
			break;
			
		case 1:
		    printf("crt0: main returned 1.\n");
		    exit (1);
			break;
			
		//...
		
	    default:
		    printf("crt0: main returned default\n");
            exit (-1);
			break; 		
	};
	
    //printf("*HANG\n");
	exit (-1);
};
*/

/*
int main ( int argc, char *argv[] )
{	
	register int c;

	FILE *fp;

    fp = fopen ( (char *) argv[1], "rb" );	

	while ((c = fgetc(fp)) >= 0)
		printf("%c", c);	
	//exit(0);

	//#debug
	//hang
	while(1){}
	
    return -1;
}
*/



