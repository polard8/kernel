
// main.c
// c-like interpreter.
// Ported from Gramado 32bit.
// 2022 - Fred Nora

#include "gramcnf.h"



//#define __VERSION__ "0.1"
//const char copyright[] = "Copyright (c) Fred Nora";

//default name.
char program_name[] = "[Default program name]";
char *compiler_name;
//static int running = 1;
int running = 1;
//Para o caso de não precisarmos produzir 
//nenhum arquivo de output. 
int no_output;

/* While POSIX defines isblank(), it's not ANSI C. */
//#define IS_BLANK(c) ((c) == ' ' || (c) == '\t')
// #important
// Specification for gramc.
//char *standard_spec = "%{%{CC} -c %{I} -o %{O}}";


// =====================================================
static int gramcnf_initialize(void);
static void usage(char **argv);
static void debugShowStat(void);
// =====================================================

/*
int is_letter(char c);
int is_letter(char c) 
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
*/


// gramcnf_initialize:
// Initialize global variables.
static int gramcnf_initialize(void)
{
    int Status = 0;
    register int i=0;

    //printf ("gramcnf_initialize:\n");

// Clear buffers

// Clear infile and outfile buffers.
    for ( i=0; i<INFILE_SIZE; i++ ){
        infile[i] = '\0';
    };
    sprintf (infile, "; ======================== \n");
    strcat (infile,  "; Initializing infile ...  \n\n");
    for ( i=0; i<OUTFILE_SIZE; i++ ){
        outfile[i] = '\0';
    };
    sprintf (outfile, "; ========================\n");
    strcat (outfile,  ";Initializing outfile ... \n\n");

// Clear text, data, bss buffers.
    sprintf (TEXT, "; ======================== \n");
    strcat  (TEXT, "; Initializing TEXT buffer \n");
    strcat  (TEXT, "segment .text              \n");
    sprintf (DATA, "; ======================== \n");
    strcat  (DATA, "; Initializing DATA buffer \n");
    strcat  (DATA, "segment .data              \n");
    sprintf (BSS,  "; ======================== \n");
    strcat  (BSS,  "; Initializing BSS buffer  \n");
    strcat  (BSS,  "segment .bss               \n");

// Table.

// Contador para não estourar a lista. 
    keyword_count = 0;  
    identifier_count = 0; 
    keyword_count = 0; 
    constant_count = 0; 
    string_count = 0; 
    separator_count = 0; 
    special_count = 0;
    // ...

// Usado pelo lexar pra saber 
// qual lugar na lista colocar o lexeme.

    current_keyword = 0; 
    current_identifier = 0; 
    current_keyword = 0; 
    current_constant = 0; 
    current_string = 0; 
    current_separator = 0; 
    current_special = 0;

// The 'program' structure.

    program.name = program_name;
    program.function_count;
    program.function_list = NULL;
    //...

    return (int) Status;
}

// Mostra as estatísticas para o desenvolvedor.
static void debugShowStat(void)
{
    printf("\n");
    printf("==========================================\n");

//#ifdef LEXER_VERBOSE
    printf("number of liner: {%d}\n",lexer_lineno);
    printf("first line:      {%d}\n",lexer_firstline);
    printf("last line:       {%d}\n",lexer_lastline);
    printf("token count:     {%d}\n",lexer_token_count);
//#endif

//#ifdef PARSER_VERBOSE
    printf("infile_size:     {%d bytes}\n",infile_size);
    printf("outfile_size:    {%d bytes}\n",outfile_size);
//#endif

    printf("\n");
    printf("==========================================\n");

    int i=0;
    for (i=0; i<32; i++)
    {
        if (metadata[i].initialized == TRUE)
        {
            printf("\n");
            printf("name{%s}\n",metadata[i].name); 
            printf("content{%s}\n",metadata[i].content);
        }
    };

    printf("\n");
    printf("==========================================\n");
}

//
// main:
//

int main ( int argc, char *argv[] )
{
// Input
    FILE *fp;
// Output file for compiler.
    FILE *____O;
    register int i=0;
    char *filename;
// Output string.
    char *o;
// Switches 
    int flagA = 0;
    int flagB = 0;
    int flagC = 0;
    int flagD = 0;
    int flagString1 = 0;
    int flagString2 = 0;
    int flagString3 = 0;
    int flagString4 = 0;
    int flagX = 0;
    int flagY = 0;
    int flagZ = 0;
    int flagR = 0;
    int flagS = 0;
    int flagT = 0;

    int fShowStats = FALSE;  //#bugbug
    int fDumpOutput = FALSE;  // Dump output file?

// Carregamos o arquivo num buffer em ring0.
// getc() precisa ler os dados em stdin
// #bugbug: 
// Se o buffer for maior que isso, read() falha.
    char __buf[1024];
    int nreads=0;

// Initializing
    //debug_print ("gramcnf: Initializing ...\n");  
    //printf ("\n");
    //printf ("main: Initializing ..\n");

// Inicializa variáveis globais.
    gramcnf_initialize();

    //printf ("*breakpoint");
    //while (1){}

//
// ## Args ##
//

// #todo
// O nome do programa é o primeiro comando da linha.
// compiler_name = argv[0];
 
// #debug 
// Mostrando os argumentos. 

    //printf ("argc=%d \n", argc );
    //for ( i=0; i < argc; i++ ){
    //    printf("arg %d = %s \n", i, argv[i] );
    //};

// flags.
// Comparando os argumentos para acionar as flags.

    for ( i=0; i < argc; i++ )
    {
        if ( strncmp( argv[i], "-a", 2) == 0 ){
        }
        if ( strncmp( argv[i], "-b", 2) == 0 ){
        }
        if ( strncmp( argv[i], "-s", 2) == 0 ){
            asm_flag = 1;
        }
        if ( strncmp( argv[i], "--stats", 7) == 0 ){
            fShowStats = TRUE;
        }
        if ( strncmp( argv[i], "--dumpo", 7) == 0 ){
            fDumpOutput = TRUE;
        }
        //...
    };

// # Arquivo de entrada #
// #bugbug
// lembrando que não podemos mais usar os elementos
// da estrutura em user mode.
// Então o buffer é gerenciado pelo kernel.
// podemos copiar o conteúdo do arquivo para um buffer aqui no programa
// através de fread, mas fread está disponível apenas na libc03.

// Open
    //printf ("\n");
    //printf("Calling fopen()    :)\n");
    //while(1){}

    fp = fopen((char *) argv[2], "rb");
    if ( fp == NULL ){
        printf("gramcnf: Couldn't open the input file\n");
        usage(argv);
        exit(1);
    }

// Input file.
// para que getc leia desse arquivo que carregamos.
    stdin = fp;
    finput = fp;
 
//#debug
// Esse while está aqui para visualizarmos o arquivo carregado.

    //int c;
    //while(1)
    //{
        //c=getc(stdin);
        //if(c == EOF)
            //break;
        //printf("%c",c);
    //}
    //fflush(stdout);
    //while(1){}
//=====================================

// Compiler
// Routine:
// + Initialize the lexer.
// + Parse the tokens.
// + Return a pointer to the output file.

    // IN: dump output file?
    ____O = (FILE *) compiler(fDumpOutput);   

    //if ( (void*) ____O == NULL ){
       //
    //}

    if (fShowStats){
        debugShowStat();
    }

    printf("Done :)\n");
    return 0;
}


static void usage(char **argv)
{
    printf ("\n");
    printf ("====================\n");
    printf ("%s version %s \n", 
        argv[0], 
        __VERSION__ );
}

//
// End.
//







