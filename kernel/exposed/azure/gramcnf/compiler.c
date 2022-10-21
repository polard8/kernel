
// compiler.h 
// Aqui ficará o compilador, 
// que transformará a linguagem intermediária em assembly.
// Bom, como ainda não temos linguagem intermediária,
// vamos transformar C em Assembly
// lexer >> parser >> compiler
// 2022 - Fred Nora

#include "gramcnf.h"


// OUT: The output pointer.
FILE *compiler (void)
{
    int lexer_return = -1;
    int parser_return = -1;

    printf ("compiler: Initializing ...\n");

// Just initializing the lexer.
    printf ("compiler: calling lexer ...\n");
    lexer_return = (int) lexer();
    //analizar retorno

// The parser will call the yylex() a lot of times.
    printf ("compiler: calling parser ...\n");
    parser_return = (int) parser();
    //analizar retorno

// Nesse momento ja temos um arquivo de output.
// more ...

    printf ("compiler: $$$$$$$$ Done\n");

// Returning the output.
    return (FILE *) stdout;
}

