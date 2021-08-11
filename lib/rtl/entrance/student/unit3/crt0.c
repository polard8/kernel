/*
 * File: unit3/crt0.c
 *
 * Usado para inicializar a rt na libc for 64bit.
 */

#include <types.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>


#include <rtl/gramado.h>

static char *argv[] = { 
    "-flag1", 
    "-flag2", 
    "-flag3", 
    "-flag4", 
    NULL 
};

/*
	$USER:      Gives current user's name.
	$PATH:      Gives search path for commands.
	$PWD:       Gives the path of present working directory.
	$HOME:      Gives path of home directory.
	$HOSTNAME:  Gives name of the host.
	$LANG:      Gives the default system language.
	$EDITOR:    Gives default file editor.
	$UID:       Gives user ID of current user.
	$SHELL:     Gives location of current user's shell program.
*/

static char *my_environ[] = { 

    "DISPLAY=kgws-or-gwssrv",  //#todo
    "EDITOR=gramcode",
    "HOME=/HOME",
    "HOSTNAME=gramado",
    "LANG=en-us",
    "LANG2=pt-br",
    "LANGX=en-br",
    "OSTYPE=gramado",   //#todo
    "PATH=/:/PROGRAMS:/GRAMADO",
    "PS1=~$",
    "PS2=:>",
    "PWD=/",             //#bugbug: This is the working directory.
    "SHELL=gdeshell",
    "TERM=noraterm",     //#bugbug
    "TMP=/TMP",
    "UID=no-id",         //#todo
    "USER=anon",  
    NULL 
};


// ??
// See: sysdeps/x86/x86start.c
// int x86start ( int argc, char *argv[], char *envp[] );


extern int main ( int argc, char *argv[] );


#define LSH_TOK_DELIM " \t\r\n\a" 
#define SPACE " "
#define TOKENLIST_MAX_DEFAULT 80


// # importante
// Esses aplicativos rodam no terminal.
// Esses aplicativos escrevem em stdout.
// O terminal precisa conhecer esse stdout para ler.


//#todo
//int crt0 ( int argc, char **argv, char **envp ){
//    environ = envp;



//int crt0 (void){

int crt0( unsigned long rdi){

    // Retorno de main().
    int retval=0;

    // Token support.
    char *tokenList[TOKENLIST_MAX_DEFAULT];
    char *token;
    int token_count=0;
    int index=0;



    unsigned long *surface_config = (unsigned long *) rdi;



	// #importante
	// Linha de comandos passada pelo shell.
	// See:
	// globals/gva.h
    // #define FRONTBUFFER_VA    0xC0400000
    // #define BACKBUFFER_VA     0xC0800000
    // So. We are using the top of the front buffer
    // as a shared memory. No problem for now.

    // #todo
    // Change this address. We need a valid one.


    // #todo
    //char *shared_info = (char *) (0xC0800000 -0x100);

    char *shared_info = "nothing nothing";
    
    // Environment.
    environ = my_environ;

/*
 // #debug

#ifdef TEDITOR_VERBOSE
	printf ("\n");
	printf ("crt0: Initializing ...\n");
	//printf("\n");
	//printf(".\n");
	printf ("..\n");
	printf ("# MESSAGE={%s} #\n", shared_info );
	printf ("..\n");
	//printf(".\n");
	//printf("\n");
	//#debug
	//while(1){ asm ("pause"); }
#endif
*/

    //
    // Tokenizing.
    //

    // Criando o ambiente.
    // Transferindo os ponteiros do vetor para o ambiente.

    tokenList[0] = strtok ( &shared_info[0], LSH_TOK_DELIM );

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


/*
 #debug
#ifdef TEDITOR_VERBOSE
	// #debug 	
	// Mostra a quantidade de argumentos. 

	printf("\n");
	printf("token_count={%d}\n", token_count );

    //Mostra os primeiros argumentos.
    for ( index=0; index < token_count; index++ )
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


//
// Initialize the library.
//

    int rt_status = -1;
    
    // See: stdlib/stdlib.c
    gramado_system_call(65,'1',0,0);
    rt_status = libcInitRT();

    if (rt_status != 0)
        gramado_system_call(65,'e',0,0);


    // return void
    // See: stdio/stdio.c
    gramado_system_call(65,'2',0,0);
    stdioInitialize();



    // #todo
    // Chamar esse ao invés de chamar os dois acima.
    //See: sysdeps/x86/x86start.c
    //x86start ( ( token_count, tokenList, default_env );


/*
#ifdef TEDITOR_VERBOSE
    //Inicializando o editor propriamente dito.
	printf("Calling main ... \n"); 
#endif
*/

  
  
    // Calling main().

    retval = (int) main ( token_count, tokenList );

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

    //printf ("libc03-crts-crt0: *fail\n");
    exit (-1);

    //printf ("libc03-crts-crt0: *hang\n");
    while (1) { asm ("pause"); };
}

