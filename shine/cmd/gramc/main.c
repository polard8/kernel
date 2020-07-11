/*
 * File: main.c
 *     Main file for 32bit app.
 *     gramc - c-like interpreter.
 */


#include "gramc.h"


#define __VERSION__ "0.1"



#ifndef __COPYRIGHT__
char copyright[] = "Copyright (c) Fred Nora.\n\
 All rights reserved.\n";
#endif 



/* While POSIX defines isblank(), it's not ANSI C. */
//#define IS_BLANK(c) ((c) == ' ' || (c) == '\t')

//default name.
char program_name[] = "[Default program name]";

// #important
// Specification for gramc.
char *standard_spec = "%{%{CC} -c %{I} -o %{O}}";


char *compiler_name;

//procurar os marcadores no arquivo intermediário 
//pegamos um arquivo intermediário e separamos cada um dos 
//elementos, colocando seus ponteiros em um vetor.
//A cada passo do offset comparamos uma palavra.
char **create_tokenlist( char *s );

// Imprime todas as strings de um vetor de ponteiros.
// Isso vai ser usado pelo echo.
void fncc_print_tokenList ( char *token_list[], char *separator );

//inicializando as variáveis e buffers.
int gramccInitialize();

void usage (char **argv);

//testando suporte à ctype.
//void mainTestingCTYPE();

//static int running = 1;
int running = 1;


//Para o caso de não precisarmos produzir 
//nenhum arquivo de output. 
int no_output;

//static char *dest_argv[] = { "-sujo0","-sujo1","-sujo2",NULL };
//static unsigned char *dest_envp[] = { "-sujo", NULL };
//static unsigned char dest_msg[512];

void editorClearScreen(); 

void debugShowStat();


/* Cancelada */
int gramc_main (){
    //cancelada, foi para crt0.	
}



/*
 ********************************************
 * mainTextEditor:
 *     O editor de textos.
 * In this fuction:
 *     Initializes crt.
 *     Initializes stdio.
 */
 
//#bugbug
//vamos cancelar isso já que temos um main() 
 
int mainTextEditor ( int argc, char *argv[] ){
	
	int ch;
	FILE *fp;
    int char_count = 0;	
	
	
#ifdef GRAMC_VERBOSE			
	printf("\n");
	printf("Initializing Text Editor:\n");
	printf("mainTextEditor:  ## argv={%s} ##  \n",
	    &argv[0] );
#endif	
	
	//
	// ## vamos repetir o que dá certo ...
	//
	
	//vamos passar mais coisas via registrador.
	
	//ok
	//foi passado ao crt0 via registrador
	//printf("argc={%d}\n", argc ); 
	
	//foi passado ao crt0 via memória compartilhada.
	//printf("argvAddress={%x}\n", &argv[0] ); //endereço.
	
	
	//unsigned char* buf = (unsigned char*) (0x401000 - 0x100) ;
	//printf("argvString={%s}\n" ,  &argv[0] );
	//printf("argvString={%s}\n" , &buf[0] );
	
	//printf("argv={%s}\n", &argv[2] );
	
	
    //stdlib
	//inicializando o suporte a alocação dinâmica de memória.
	libcInitRT();

	//stdio
	//inicializando o suporte ao fluxo padrão.
    stdioInitialize();	
	

	//
	// ## screen ##
	//

    // #bugbug
    // We don't need this thing.

    gde_begin_paint ();
    editorClearScreen (); 
    gde_end_paint ();


	//
	// Testing file support.
	//


file:

#ifdef GRAMC_VERBOSE
    printf("\n");
    printf("\n");
    printf("Loading file ...\n");
#endif


	//Page fault:
	//
    //fp = (FILE *) fopen( "init.txt", "r+");
    //fp = fopen("init.txt","rb");

    //fp = fopen("test1.txt","rb");	

    fp = fopen ( (char*) &argv[0],"rb");

    if (fp == NULL){
        printf("fopen fail\n");
        goto fail;

    }else{


#ifdef GRAMC_VERBOSE			
        printf(".\n");		
        printf("..\n");		
        printf("...\n");
#endif 

		// Exibe o arquivo.
        printf("%s",fp->_base);	


#ifdef GRAMC_VERBOSE	        
		printf("...\n");
        printf("..\n");		
        printf(".\n");		
#endif


#ifdef GRAMC_VERBOSE	
		printf("\n");
		printf("Typing a text ...\n");
#endif

Mainloop:

        while(running)
        {
            ch = (int) getchar ();
            
            if (ch == -1){
                // printf("EOF reached! ?? \n");
                asm ("pause");
            }

            if (ch != -1){

                printf ("%c",ch);
 
                //switch(ch)
                //{
			        //quit
			    //    case 'q':
			    //        goto hang;
				//        break;				 
		        //};		   
             }
        };

		//saiu.
        printf(".\n");		
        printf(".\n");		
        printf(".\n");
        goto done;
   };



fail:
    printf("fail.\n");

done:
    running = 0;
    printf("Exiting editor ...\n");
    printf("done.\n");

    while(1){
        asm ("pause");
        exit(0);
    };


    // Never reach this.	
    
    return 0;
}


/*
 *     Limpar a tela deletar isso
 */

void editorClearScreen (){
	
    int lin, col;    

	// @todo:
	//system( "cls" ); // calls the cls command.
	
	//cursor.
    gde_set_cursor ( 0, 0 );

	//
	// Tamanho da tela. 80x25
	//

	//linhas.
    for ( lin=0; lin < ((600/8)-1); lin++)
    {
		col = 0;
		
		gde_set_cursor (col,lin);
		
		//colunas.
		for( col=0; col < ((800/8)-1); col++)
		{
			printf("%c",' ');
	    }
	};
	
    gde_set_cursor (0,2);
}



//procurar os marcadores no arquivo intermediário 
//pegamos um arquivo intermediário e separamos cada um dos 
//elementos, colocando seus ponteiros em um vetor.
//A cada passo do offset comparamos uma palavra.
//#define create_tokenlist_DELIM " \t\r\n\a" 
#define create_tokenlist_DELIM " " 
char **create_tokenlist ( char *s ) {
	
//criando o ambiente.
	//transferindo os ponteiros do vetor para o ambiente.
	
	char **Ret;
	char *tokenList[TOKENLIST_MAX_DEFAULT];
	char *token;
	int z;
	register int token_count;
	
	Ret = (char **) tokenList;
	
	tokenList[0] = strtok( s, create_tokenlist_DELIM);
	
 	//salva a primeira palavra digitada.
	token = (char *) tokenList[0];
 

	int index=0;                                  
    while( token != NULL )
	{
        // Coloca na lista.
        //salva a primeira palavra digitada.
		tokenList[index] = token;

		//#debug
		//Mostra
        //printf("shellCompare: %s \n", tokenList[i] );
        //refresh_screen();
		
		token = strtok( NULL, create_tokenlist_DELIM );
		
		// Incrementa o índice da lista
        index++;
		
		//salvando a contagem.
		token_count = index;
    }; 

	//Finalizando a lista.
    tokenList[index] = NULL;		
	
	
	//goto done;
		
done:	
	//fncc_print_tokenList(tokenList, "/");
	
	number_of_tokens = (int) token_count;
	lexer_token_count = (int) token_count;  
	
    return (char **) Ret;	
}


// Imprime todas as strings de um vetor de ponteiros.
// Isso vai ser usado pelo echo.
void fncc_print_tokenList ( char *token_list[], char *separator ){
	
	char *token;
	
	token = (char *) token_list[0];
	
	if( token == NULL )
	    goto fail;
	
	
	//token = (char *) tokenList[i];
		
	//	if( token == NULL ){
			
    int i;
	for( i=0; i,128; i++ )
    {
		token = (char *) token_list[i];

	    if( token == NULL )
	        goto done;
		
		//if( strncmp( (char*) token_list[i], "echo", 4 ) == 0 )
		//    continue;	
		
		printf("%s", token_list[i]);
		printf("%s", separator);
    }
	
fail:
done:
    return;	
}


/*
int is_letter(char c) ;
int is_letter(char c) 
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');

}
*/


/*
 **************************************
 * gramcInitialize:
 *     Inicializa variáveis globais.
 */

int gramcInitialize (){

    int Status = 0;
    int i=0;


    printf ("gramcInitialize: Initializing ...\n");


	// Clear buffers

    for ( i=0; i<INFILE_SIZE; i++ ){
        infile[i] = '\0';
    }
    sprintf (infile, "; ======================== \n");
    strcat (infile,  "; Initializing infile ...\n\n");


    for ( i=0; i<OUTFILE_SIZE; i++ ){
        outfile[i] = '\0';
    }
    sprintf (outfile, "; ======================== \n" );
    strcat (outfile,  ";Initializing outfile ...\n\n");



    // text, data, bss


    sprintf (TEXT, "; ======================== \n" );
    strcat (TEXT,  "; Initializing TEXT buffer \n");
    strcat (TEXT,  "segment .text \n");
    
    sprintf (DATA, "; ======================== \n" );
    strcat (DATA,  "; Initializing DATA buffer \n");
    strcat (DATA,  "segment .data \n");
    
    sprintf (BSS, "; ======================== \n" );
    strcat (BSS,  "; Initializing BSS buffer \n");
    strcat (BSS,  "segment .bss \n");


	//table.

//contador para não estourar a lista. 
    keyword_count = 0;  
    identifier_count = 0; 
    keyword_count = 0; 
    constant_count = 0; 
    string_count = 0; 
    separator_count = 0; 
    special_count = 0;	
	//...
	
	
//usado pelo lexar pra saber qual lugar na lista 
//colocar o lexeme.
    current_keyword = 0; 
    current_identifier = 0; 
    current_keyword = 0; 
    current_constant = 0; 
    current_string = 0; 
    current_separator = 0; 
    current_special = 0;

	
	//
	// ## program ##
	//
	
	program.name = program_name;
	program.function_count;
	program.function_list = NULL;


	//...

    printf ("gramcInitialize: done\n");

    return (int) Status;
}


//testing ctype support
/*
void mainTestingCTYPE()
{
    int var1 = 'h';
    int var2 = '2';
    
    printf("Testing ctype.h\n");
   
    if( isdigit(var1) ) 
    {
        printf("var1 = |%c| is a digit\n", var1 );
    }else{
        printf("var1 = |%c| is not a digit\n", var1 );
    };
   
    if( isdigit(var2) ) 
	{
        printf("var2 = |%c| is a digit\n", var2 );
    }else{
        printf("var2 = |%c| is not a digit\n", var2 );
    };

    // More ...
};
*/



//mostra as estatísticas para o desenvolvedor.
void debugShowStat (){
	
	printf("debugShowStat:\n\n");
	
	printf("name: %s\n", program.name );
	printf("function count : %d\n", program.function_count );
	printf("list handle : %x\n", program.function_list );
	
	
	if( (void *) function_main == NULL )
	{
		printf("debugShowStat: function_main struct \n");
		return;
	
	} else {
		
        if ( function_main->used != 1 || function_main->magic != 1234 )
        {
		    printf("function_main: validation \n");
		    return;
			
		} else {
			
			printf("main id: %d \n", function_main->id );
		    
			//...
			
			if( (void *) function_main->h0 ==  NULL )
			{
				printf("function_main: h0 \n");
			}else{
				
				printf("h0 type %d \n",function_main->h0->type_token_index);
				printf("h0 identifier %d \n",function_main->h0->identifier_token_index);
			};
			//nothing
		};			
        //nothing		
	};

	
#ifdef LEXER_VERBOSE	
	printf("number of liner: %d \n",lexer_lineno);
	printf("first line: %d \n",lexer_firstline);
	printf("last line: %d \n",lexer_lastline);
	printf("token count: %d \n",lexer_token_count);	
#endif	
	
#ifdef PARSER_VERBOSE	
	printf("infile_size: %d bytes \n",infile_size);
    printf("outfile_size: %d bytes \n",outfile_size);	
#endif	
	
}


/*
 ********************************
 * main:
 *     Main function. 
 *     The entry point is is crt0.o.
 */

int main ( int argc, char *argv[] ){

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


	// Initializing.
    gde_debug_print ("gramc: Initializing ...\n");  
    
    printf ("\n");
    printf ("main: Initializing ..\n");

   
    // Globals.
    gramcInitialize();


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
	
#ifdef GRAMC_VERBOSE		
    printf ("argc=%d \n", argc );

    for ( i=0; i < argc; i++ )
        printf ("arg %d = %s \n", i, argv[i] );
#endif 


    // flags.
	// Comparando os argumentos para acionar as flags.
	
    for ( i=0; i < argc; i++ )
    {
        if ( strcmp( argv[i], "-a") == 0 ){
            printf ("## %d flag a ##\n",i);
        }

        if ( strcmp( argv[i], "-b") == 0 ){
            printf("## %d flag b ##\n",i);
        }

        if ( strcmp( argv[i], "-s") == 0 ){
            printf("## %d flag -s ##\n",i);
            asm_flag = 1;
        }
        
        //...
    };


    //
	// # Arquivo de entrada #
	//
	
	// #bugbug
	// lembrando que não podemos mais usar os elementos
	// da estrutura em user mode.
	// Então o buffer é gerenciado pelo kernel.
	// podemos copiar o conteúdo do arquivo para um buffer aqui no programa
	// através de fread, mas fread está disponível apenas na libc03.

    // Carregamos o arquivo num buffer em ring0.
    // getc() precisa ler os dados em stdin
    // #bugbug: Se o buffer for maior que isso, read() falha!
    char __buf[1024];
    int nreads = 0;

    // gramc -c [filename]
    fp = fopen ( (char *) argv[2], "rb" );

    if ( fp == NULL ){
        printf ("gramc: Couldn't open the input file \n");
        usage (argv);
        exit(1);

    }else{

         // Input file.
         // para que getc leia desse arquivo que carregamos.
         stdin = fp; finput = fp;
         
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
    };




    //
    // Compiler.
    //
    
    // It returns a pointer to the output file.
        
    printf ("gramc: Calling compiler\n");
    ____O = (FILE *) compiler();

    printf ("gramc: compiler returned \n");
    debug_print ("gramc: compiler returned \n");

    //#debug
    //printf ("*breakpoint");
    //while (1){} 
    

//exit_default:

	//#importante
	//mostra o asm
	//isso dependerá da flag -s
	
    // More ...   
	
//out:
    
	//if ( asm_flag == 1 )
	//{
        //printf ("===============================\n");
        //printf ("OUTPUT: \n %s \n", outfile );   //array usado por strcat
        //printf ("===============================\n");
	//}


	//#debug suspensa por enquanto.
	//debugShowStat();

    gde_debug_print ("gramc: Done. :^) \n");    
    
    printf("\n");
    printf ("gramc: done. \n");


    return 0;
}



void usage (char **argv){

    printf ("\n\n");
    printf ("====================\n");
    printf ("%s version %s \n", 
        argv[0], __VERSION__);
}

//
// End.
//







