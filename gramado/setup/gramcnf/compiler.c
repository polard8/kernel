
// compiler.h 

// Aqui ficará o compilador, 
// que transformará a linguagem intermediária em assembly.
// Bom, como ainda não temos linguagem intermediária,
// vamos transformar C em Assembly


// lexer >> parser >> compiler


#include "gramcnf.h"



FILE *compiler (void){

    int lexer_return = -1;
    int parser_return = -1;



    gde_debug_print ("compiler:\n");

    printf ("compiler: Initializing ...\n");


    printf ("compiler: calling lexer ...\n");
    // Just initializing the lexer.
    lexer_return = (int) lexer ();
    //analizar retorno


    printf ("compiler: calling parser ...\n");
    // The parser will call the yylex() a lot of times.
    parser_return = (int) parser ();
	//analizar retorno	


     //
     // Nesse momento ja temos um arquivo de output.
     //

      //more ...
	
//done:	
	printf ("compiler: $$$$$$$$$$ Done \n\n");
	
    // Returning the output.
    return (FILE *) stdout;
}


