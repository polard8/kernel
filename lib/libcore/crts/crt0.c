/*
 * File: crts/crt0.c
 *
 * Usado para inicializar a rt na libcore do garden.
 * tentando criar um crt0 padrão
 */


#include <types.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <unistd.h>



static char *argv[] = { 
    "-flag1", 
    "-flag2", 
    "-flag3", 
    "-flag4", 
    NULL 
};



// Esperamos um extern em stdlib para pegar as informações
// que estão aqui.

static char *my_environ[] = { 
    "PS0=$",           
    "PS1=>",    
    "WS=KGWS",   // Window server in the kernel.  
	NULL 
};


extern int main ( int argc, char *argv[] );



#define LSH_TOK_DELIM " \t\r\n\a" 
#define SPACE " "
#define TOKENLIST_MAX_DEFAULT 80


//#todo
//int crt0 ( int argc, char **argv, char **envp ){
//    environ = envp;

int crt0 (){

    environ = my_environ;

    //
    // Token support.
    //

    char *tokenList[TOKENLIST_MAX_DEFAULT];
    char *token;
    int ____token_count;
    int index;


    int retval;

    // #importante
    // Linha de comandos passada pelo shell.

    char *shared_memory = (char *) (0xC0800000 -0x100);

/*
#ifdef TEDITOR_VERBOSE	
	
	printf ("\n");
	printf ("crt0: Initializing ...\n");
	//printf("\n");
	//printf(".\n");
	printf ("..\n");
	printf ("# MESSAGE={%s} #\n", shared_memory );
	printf ("..\n");
	//printf(".\n");
	//printf("\n");
	
	//#debug
	//while(1){ asm ("pause"); }
#endif
*/


    //
    // The token list.
    //


//token_support:

    // ==========================================
    // ++
    // Criando o ambiente.
    // Transferindo os ponteiros do vetor para o ambiente.
    // Get the first call returns pointer to first part of user_input 
    // separated by delim.
    // Isso pega a primeira palavra digitada.
    // Isso inicializa a função strtok. que continuaá pegando
    // desse mesmo prompt.

    tokenList[0] = strtok ( &shared_memory[0], LSH_TOK_DELIM );

	// Salva a primeira palavra digitada, que pegamos imediatamente
	// antes.
	// #todo: 
	// Isso precisa ser limpado sempre.

    token = (char *) tokenList[0];

    index = 0; 
    while ( token != NULL )
    {
        // Coloca na lista.
        tokenList[index] = token;
        index++;
        ____token_count = index;        
        
        // Pega mais um da linha de comandos.
        token = strtok ( NULL, LSH_TOK_DELIM );
    }; 

    //Finalizando a lista.
    tokenList[index] = NULL;
    //--
    // ==========================================



/*
	// #debug 	
	// Mostra a quantidade de argumentos. 

#ifdef TEDITOR_VERBOSE
	printf("\n");
	printf("____token_count={%d}\n", ____token_count );

    //Mostra os primeiros argumentos.
    for ( index=0; index < ____token_count; index++ )
    {
        token = (char *) tokenList[index];
        if ( token == NULL )
        {
            printf ("crt0: for fail!\n")
            goto hang;
        }

        printf ("# argv{%d}={%s} #\n", index, tokenList[index] );
    };
#endif
*/



    // #importante
    // Inicializa a biblioteca libcore.

    libcInitRT ();
    stdioInitialize ();


/*
#ifdef TEDITOR_VERBOSE
    //Inicializando o editor propriamente dito.
    printf("Calling main ... \n"); 
#endif
*/


    // Calling main().

    retval = (int) main ( ____token_count, tokenList );


    switch (retval)
    {

       case 0:
            //printf ("crt0: main returned 0\n");
            exit (0);
            break;


        case 1:
            //printf ("crt0: main returned 1\n");
            exit (1);
            break;


        //...


        default:
            //printf ("crt0: main returned default\n");
            exit (-1);
            break; 
    };



    //
    // No return!
    //

    //printf ("libcore-crts-crt0: * fail! \n");
    exit (-1);

    // Not reached.
    //printf ("libcore-crts-crt0: *HANG \n");
    while (1) { asm ("pause"); };
}


