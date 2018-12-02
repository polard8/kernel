/*
 * File: parser.c
 *
 * 2018 - Created by Fred Nora.
 */
 

#include  "c.h"  
 
 
 /*
//#include "config.h"
//#include "debug.h"

//#include <types.h>

//#include "heap.h"
//#include "api.h"

//#include <stddef.h>
//#include <stdlib.h>
//#include <string.h>
//#include <stdio.h>

//#include "table.h"
//#include "lexer.h"
//#include "parser.h"
//#include "gramcc.h"

//#include "tree.h"
*/ 



//expression
int parse_expression ( int token );

int parse_function ( int token );
int parse_return ( int token );


int parse_if ( int token );
int parse_do ( int token );
int parse_while ( int token );
int parse_for ( int token );

int parse_asm ( int token );

//...




//#test
/*
int parse_number (int olen){
	
    //pointer #todo	
    //register char *p = lexptr;
    register char *p = token_buffer;
  
  register long n = 0;
  register int c;
  register int base = 10;
  register len = olen;
  char *err_copy;

    //#todo função importada.
	extern double atof ();

    for (c = 0; c < len; c++)
	{
        //se encontrarmos um ponto no meio dos números.
		//pois não tem ponto no meio de uma expressões no  
		//#if (ainda não sei se gcc está falando de diretivas ou statement)
		if ( p[c] == '.' )
		{
            // It's a float since it contains a point.  
            //yyerror ("floating point numbers not allowed in #if expressions");
			printf ("floating point numbers not allowed in #if expressions");
            return ERROR;
      
            // ****************
	        //yylval.dval = atof (p);
	       // lexptr += len;
	       // return FLOAT;
		   // ****************  
        }		
	}
  
    //se o comprimeiro for mior que 3.
	//se começar com '0x', ou '0X', indicando se um número heaxadecimal.
	//então a base será 16.
	if ( len >= 3 && 
	     ( !strncmp (p, "0x", 2) || !strncmp (p, "0X", 2)) ) 
	{
		//baes hexa.
		base = 16;
        
		//pegaremos depois do x.
		p += 2;
		
		//atualiza o comprimeito.
		len -= 2;
    
	
	//Se o número começar com '0', então temos octal.
	
	}else if ( *p == '0' )
	      {
			base = 8;  
		  };
            
  
   
	while (len-- > 0) 
	{
        c = *p++;
        n *= base;
        
		//se o caractere for um dígito decimal.
		if (c >= '0' && c <= '9')
		{
            n += c - '0';
        
		}else{
			
            if (c >= 'A' && c <= 'Z') 
				c += 'a' - 'A';
            
			if (base == 16 && c >= 'a' && c <= 'f'){
				
	            n += c - 'a' + 10;
				
            }else if (len == 0 && c == 'l'){
				
	            ; //nothing
				
            }else{
	            //yyerror ("Invalid number in #if expression");
				printf ("Invalid number in #if expression");
	            return ERROR;
            }
        };
    };

    lexptr = p;
    yylval.lval = n;
    return INT;
};
*/



//analizando uma expressão.
//temos a questão de predecessores para os operadores.

int parse_expression ( int token )
{
	int c;
	
	c = token;
    
	//primeiro analizamos o que veio via argumento 
	//assim checaremos a validade da expressão e
	//abortaremos logo cedo.
	
	//uma expressão pode começar com (, operador, número ...
	//então vamos ver qual é o primeiro token da expressão.
	
	
	int running = 1;
	int State = 1;
	
	//agora pegaremos os outros elementos da expressão.
	
	while (running == 1)
	{
	    c = yylex ();
	    
		switch (State)   
	    {
			
			//State 1
			//não vamos começar com operadores e sim com operandos,
			//que pdoem ser números ou identificadores.
			case 1:
			    switch(c)
				{
					//se for operando falhou 
	                case TOKENOPERATOR:
					    printf("parse_expression: invalid operator in the beggining of expression");
						exit(1); //die();
                        break;					
					
					//...
					
					default:
					    printf("parse_expression: default case in State 1");
						exit(1); //die();
					    break;
				}
			   break;
			   
			//State 2
            //operadores			
			case 2:
			    switch (c)
			    {
					//#importante
					//o lexer lida com alguns tokens usados por expressões 
					//usar esse tokens. 
					//lexer_code = o operador encontrado, que pode ser simples ou duplo. 
					
                    case '+':
                    case '-':
                    case '*':
					case '/':
					case '&':
                    case '|':
                    case '<':
                    case '>':
                    case '%':
                    case '^':
                    case '!':
                    case '=':
					    printf("parse_expression: State 2 simple operator lexer_code=%d", lexer_code );
        			    //die();
						break;		
					
					case ARITHCOMPARE:
					    printf("parse_expression: State 2 ARITHCOMPARE lexer_code=%d", lexer_code );
						switch (lexer_code)
						{
							case LE_EXPR:
							    printf("LE_EXPR lexer_code=%d", lexer_code );
							    break;
								
							case GE_EXPR:
							    printf("GE_EXPR lexer_code=%d", lexer_code );
							    break;
	
								
							///...	
								
							default:
							    printf("parse_expression: State 2 error ARITHCOMPARE default lexer_code=%d in line %d", 
								    lexer_code, lineno );
							    exit(1); //die();
								break;
						}
						break;
					   
				    
					case EQCOMPARE:
					    printf("parse_expression: State 2 EQCOMPARE lexer_code=%d", lexer_code );
						switch (lexer_code)
						{
							
							case NE_EXPR:
							    printf("NE_EXPR lexer_code=%d", lexer_code );
							    break;
								
							case EQ_EXPR:
							    printf("EQ_EXPR lexer_code=%d", lexer_code );
							    break;							
							
							default:
							    printf("parse_expression: State 2 error EQCOMPARE default lexer_code=%d in line %d", 
								    lexer_code, lineno );
							    exit(1); //die();
								break;
                        };						
					    break;
					   
					case ASSIGN:
                        printf("parse_expression: State 2 ASSIGN lexer_code=%d", lexer_code );
						break;					
					   
					case PLUSPLUS:
					   printf("parse_expression: State 2 PLUSPLUS lexer_code=%d", lexer_code );
					   break;
					   
					case MINUSMINUS:
					   printf("parse_expression: State 2 MINUSMINUS lexer_code=%d", lexer_code );
					   break;
					   
					case ANDAND:
					   printf("parse_expression: State 2 ANDAND lexer_code=%d", lexer_code );
					   break;
					   
					case OROR:
					   printf("parse_expression: State 2 OROR lexer_code=%d", lexer_code );
					   break;
					   
					   
					case POINTSAT:
					   printf("parse_expression: State 2 POINTSAT lexer_code=%d", lexer_code );
					   break;
					   
					case LSHIFT:
					   printf("parse_expression: State 2 LSHIFT lexer_code=%d", lexer_code );
					   break;
					   
					   
					case RSHIFT:
					   printf("parse_expression: State 2 RSHIFT lexer_code=%d", lexer_code );
					   break;
					   
					//...
					
					default:
					    printf("parse_expression: default case in State 2");
						break;
					    break;
				};
           	    break;		 
            
            //...
			
			//State default
            default:	
                printf("parse_expression: default State");
                exit(1); //die();				
		        break;
	    };
	};
	
	return 0;
};






int parse_asm ( int token )
{
	
	int c;
	
	int running = 1;

	int State = 1;	
	
#ifdef PARSER_VERBOSE	
	//debug
	printf("parse_asm: Initializing ...\n");	
#endif	

	//se entramos errado.
	if ( token != TOKENKEYWORD)
	{
		printf("parse_asm: token error\n");
		exit(1);
	}
	
    if ( token == TOKENKEYWORD )	
	{		
		printf("parse_asm: TOKENKEYWORD={%s} in line %d\n", real_token_buffer, lineno );    			
	}

	
	int inside = 0;
	
	//
	// (
	//
	
	c = yylex ();
	
	if ( c == TOKENSEPARATOR )
	{
	    if ( strncmp( (char *) real_token_buffer, "(", 1 ) == 0  )
        {
			printf("parse_asm: TOKENKEYWORD={%s} in line %d\n", real_token_buffer, lineno ); 
			//ok
			inside = 1;
			
		} 
		
	}else{
		//fail
		printf("parse_asm: expected (");
		exit(1);
	}
	
	//
	// " .... "
	//
	
	c = yylex ();
	
	if ( c == TOKENSTRING )
	{
	    //if ( strncmp( (char *) real_token_buffer, "\"", 1 ) == 0  )
        //{
			//ok
			//inside = 1;
		//} 
		
		//coloca a string no arquivo de saída.
		strcat( outfile, real_token_buffer );
		
			//ao fim da string vamos para a próxima linha do output file
		strcat( outfile,"\n");		
		
		c = yylex ();
		
		
			//)
		    if ( strncmp( (char *) real_token_buffer, ")", 1 ) == 0  )
			{
				inside = 0;
				
				c = yylex ();
				
				//;
				if ( strncmp( (char *) real_token_buffer, ";", 1 ) == 0  )
				{
					//ok
					return c;
				}
			    printf("parse_asm: expected ; in asm string");
			    exit(1);	
			}
			
			printf("parse_asm: expected ) in asm string");
			exit(1);	
			
		
		
	}else{
		//fail
		printf("parse_asm: expected string in asm("") ");
		exit(1);
	}
	
	
	/*

	int size = 32;  //max
	
    while (size == 0 )	
    {
	    c = yylex ();

	    //se encontramos um " no meio da string, significa que acabou a string de asm.
		if ( strncmp( (char *) real_token_buffer, "\"", 1 ) == 0  )
        {
			//ao fim da string vamos para a próxima linha do output file
			strcat( outfile,"\n");
			
		    c = yylex ();	
			
			//)
		    if ( strncmp( (char *) real_token_buffer, ")", 1 ) == 0  )
			{
				c = yylex ();
				
				//;
				if ( strncmp( (char *) real_token_buffer, ";", 1 ) == 0  )
				{
					//ok
					return c;
				}
			    printf("parse_asm: expected ; in asm string");
			    exit(1);	
			}
			
			printf("parse_asm: expected ) in asm string");
			exit(1);	
		
		// se ainda não encontramos o finalizador, então tudo é assembly.
		//apenas copiaremos a string assembly para o output.
		
		}else{
			
			//copiamos a palavra encontrada.
			strcat( outfile, real_token_buffer );
			
			//colocamos um espaço entra as palavras.
			strcat( outfile," ");			
		};		
		
        size--;		
	}
	
	if ( size == 0 )
	{
		//fail
		if( inside == 1 )
		{
		   printf("parse_asm: expected \" inside string");
		   exit(1);					
		}
		   printf("parse_asm: todo error in asm string");
		   exit(1);							
	}
	*/
	
    printf("parse_asm: todo unexpected error in asm string");
	exit(1);		
		   
	return -1;
};


int parse_function ( int token )
{
	int c;
	
	int running = 1;
	int State = 1;
	
#ifdef PARSER_VERBOSE	
	//debug
	printf("parse_function: Initializing ...\n");	
#endif	
	
	//se entramos errado.
	if ( token != TOKENIDENTIFIER )
	{
		printf("parse_function: Can't initialize function statement\n");
		exit(1);
	}
	
    if ( token == TOKENIDENTIFIER )	
	{
	
		id[ID_TOKEN] = TOKENIDENTIFIER;
		id[ID_STACK_OFFSET] = stack_index;
		
		printf("parse_function: TOKENIDENTIFIER={%s} in line %d\n", real_token_buffer, lineno );    			
	}

	while (running)
	{
		c = yylex ();
		
		switch ( State )
		{
			//state1 
			//esperamos um separador '('
			//pois isso é uma função e não uma definação de variável.
			case 1:
			    switch (c)
				{
					case TOKENSEPARATOR:
	                    if ( strncmp( (char *) real_token_buffer, "(", 1 ) == 0  )
						{
						    printf("parse_function: TOKENSEPARATOR={%s} in line %d\n", real_token_buffer, lineno ); 
							State = 2;	
						}
					    break;
						
                    default:
                        printf("parse_function: State1 Missed '(' separator in line %d ", lineno );
						exit(1);
						break;					
				}
			    break;
				
			//esperamos aqui tipos, simbolos , separador ',' ou o separador ')'	
			case 2:
			    switch (c)
				{
					//')'
					case TOKENSEPARATOR:
	                    if ( strncmp( (char *) real_token_buffer, ")", 1 ) == 0  )
						{
						    printf("parse_function: TOKENSEPARATOR={%s} in line %d\n", real_token_buffer, lineno ); 
							State = 3;	
						}
					    break;
						
					//case type 
					//case symbol 
					//case ','
					//...
					
                    default:
                        printf("parse_function: State2 something wrong in line %d ", lineno );
						exit(1);
						break;					
				}
			    break;
				
			//esperamos aqui o separador final ';'
            //isso finaliza o statement 'function'			
			case 3:
			    switch (c)
				{
					//';'
					//terminamos o statement function.
					case TOKENSEPARATOR:
	                    if ( strncmp( (char *) real_token_buffer, ";", 1 ) == 0  )
						{
						    printf("parse_function: TOKENSEPARATOR={%s} in line %d\n", real_token_buffer, lineno ); 
							return (int) TOKENSEPARATOR;	
						}
					    break;
						
                    default:
                        printf("parse_function: State3 Expected separator ';' in line %d ", lineno );
						exit(1);
						break;										
				}
			    break;
			
			default:
				printf("parse_function: default statement\n");
				exit(1);				    
			    break;
		};
	};	
};

// #return statement
// >> termina com  ';'
// return 0;
// return (int) 1;
// return 1+2;
// return (1+2);
// return (int) (1+2);
// return function();
// return (int) function();
//interna 
int parse_return ( int token ){
	
	
	int c;
	
	int running = 1;
	int State = 1;
	
	int open = 0;
	

#ifdef PARSER_VERBOSE	
	//debug
	printf("parse_return: Initializing ...\n");	
#endif	
	
	//se entramos errado.
	if ( token != TOKENKEYWORD || keyword_found != KWRETURN )
	{
		printf("parse_return: Can't initialize return statement\n");
		exit(1);
	}
	

	
	while (running)
	{
		c = yylex ();
		
		switch ( State )
		{
			
			//#state1
		    //esperamos constante, expressão, tipo ou função.
			case 1:
			    switch(c)
				{
					//se encontramos a constante, o que segue é o separador ';' ou o separador ')'
					case TOKENCONSTANT:					
#ifdef PARSER_VERBOSE							
						//ok;
						printf ("parse_return: State1 TOKENCONSTANT={%s} line %d\n", 
						    real_token_buffer, lineno );
#endif

					    constant[CONSTANT_TOKEN] = TOKENCONSTANT;
						constant[CONSTANT_TYPE] = constant_type_found;
						constant[CONSTANT_BASE] = constant_base_found;

						//#todo: fazer um switch para tipos válidos.
						strcat( outfile,"  mov eax, ");
						strcat( outfile, real_token_buffer );
						strcat( outfile,"\n  ret \n\n");
                        //strcat( outfile,"");							
						
						// se parênteses aberto.
						//if ( open == 1 )
						//{
						//    struct tree_node *n = (struct tree_node *) create_tree_node ( ?, NULL, NULL );	
						//}
						
						//Se não temos um parêntese aberto então vamos para o próximo
						//que deverá ser um ';'
						
						if ( open == 0 )
						{
						    State = 2;	
						}
						
						//mas se ainda temos um parentese aberto então
						//encontramos uma constante dentro do parêntese,
						//indicando que estamos um uma expressão.
						break;
					
					
                     
					case TOKENSEPARATOR:
	                    
						//iniciamos uma expressão ou condicional.
						//uma árvore.
						if ( strncmp( (char *) real_token_buffer, "(", 1 ) == 0  )
                        {
						    open = 1;
						}
						
						//se fecharmos, o que segue pode ser um separador ';',
						//uma função, uma constante ou uma expressão.
	                    if ( strncmp( (char *) real_token_buffer, ")", 1 ) == 0  )
						{
						    open = 0;							
						}
						
						//se o separador for ';' é porque estamos num retorno do tipo void.
						//se o retorno não for do tipo void então foi erro de sintaxe..
						if ( strncmp( (char *) real_token_buffer, ";", 1 ) == 0  )
						{
							printf("parse_return: separator ';' in line %d\n", lineno);
							
						    if (open == 1)
                            {
								printf("parse_return: State1 wrong separator ';' in line %d\n", lineno);
								exit(1);
							}
							
                            //retorno do tipo void.
							if (open == 0)
                            {
								strcat( outfile,"\n  ret \n\n");
								return (int) TOKENSEPARATOR;
                            }								
						}
						break;
					
				    //case identificador. (símbolo)
					//significa que o return foi seguido de uma função.
					case TOKENIDENTIFIER:
					    //#todo Nesse momento podemos chamar a rotian qu trata uma função 
						//function statement. function_parser
						
						// ';' foi encontrado.
						//finalizado o statement de função então vamos sair do statemente de return.
						//pois o ';' da função é o mesmo do return.
						//se estivermos após a keyword 'return' ou após o tipo '(int)'.
						if ( open == 0 )
						{
                            //vamos analizar uma chamada de função dentro de um statement de return.							
						    return (int) parse_function ( TOKENIDENTIFIER );
						}
						
						//#importante
						//temos um identificador dentro do parênteses.
						//Se uma função foi chamada dentro do parênteses não devemos esperar 
						//por um separador ';'
						if ( open == 1 )
						{
						    //todo	
						}
						break;		
						
					default:
				        printf("parse_return: State1 default\n");
				        exit(1);
					    break;
				}
                break;

			
			//#state2
			// separador ';'
			case 2:
			    switch(c)
				{
					case TOKENSEPARATOR:
	                    if ( strncmp( (char *) real_token_buffer, ";", 1 ) == 0  )
                        {
#ifdef PARSER_VERBOSE								
			                //deu certo.
			                printf ("parse_return: State2 do_separator TOKENSEPARATOR={%s} line %d \n", 
							    real_token_buffer, lineno );
#endif		                    
							//Se encontramos o separador que finaliza o statement
							//então podemos retornar.
							return (int) TOKENSEPARATOR;
		                }	
					    break;
						
					default:
				        printf("parse_return: State2 default\n");
				        exit(1);
					    break;
				}
			    break;
				
			//Statemente não enumerado.
			default:
				printf("parse_return: default statement\n");
				exit(1);			
			    break;
		};
	};
	
	//printf("parse_var:\n");
	
	//pegaremos o tipo e a exp.
	
do_constant:

	c = yylex ();
	

	if ( c == TOKENCONSTANT)
	{
		
#ifdef PARSER_VERBOSE			
	    printf ("parse_return: do_constant TOKENCONSTANT={%s} line %d\n", 
		    real_token_buffer, lineno );	
#endif
		constant[CONSTANT_TOKEN] = TOKENCONSTANT;
		constant[CONSTANT_TYPE] = constant_type_found;
		constant[CONSTANT_BASE] = constant_base_found;	
	
	} else {
			//falhou.
			printf("parse_return: do_constant Expacted constant on line %d", lineno);
			exit(1);
			//while(1){}		
	};
	
	
	
do_separator:

    c = yylex ();
    
	//separador ';'
	//isso finaliza o statement.
	if( c == TOKENSEPARATOR )
    {
	    if( strncmp( (char *) real_token_buffer, ";", 1 ) == 0  )
        {

#ifdef PARSER_VERBOSE	
			//deu certo.
			printf("parse_return: do_separator TOKENSEPARATOR={%s} line %d \n", 
			    real_token_buffer, lineno );
#endif		  
		  
			goto done;
		}else{
			//falhou.
			printf("parse_return: do_separator: fail");
			exit(1);
			//while(1){}
		};	
		
	}else{
			//falhou.
			printf("parse_return: do_separator Expected ';' on line %d",lineno);
			exit(1);
			//while(1){}		
	};	
	
done:		
   return c;
};

int parse_if ( int token )
{
	printf("todo: parse_if in line %d ", lineno );
	
	//testando chamar uma análise de expressão dentro do statement de if.
	parse_expression ( token );
	
	exit(1);
    return -1;	
};

int parse_do ( int token )
{
	printf("todo: parse_do in line %d ", lineno );
	exit(1);
    return -1;	
};

int parse_while ( int token )
{
	printf("todo: parse_while in line %d ", lineno );
	
	//testando chamar uma análise de expressão dentro do statement de while.
	parse_expression ( token );
	
	exit(1);
    return -1;	
};

int parse_for ( int token )
{
	printf("todo: parse_while in line %d ", lineno );
	exit(1);
    return -1;	
};


/*
 ************************************************************************
 * parse:
 *     Função principal.
 *     Pegando tokens com o lexer e fazendo coisas ...
 */
 
int parse (){
	
	register int c;
	int i;
	
	char save_symbol[32];
	
	int running = 1;
	size_t size = (size_t) strlen ( (const char *) stdin->_base );
	
	
	//{([
	//se entramos em um desses corpos.
	int braces_inside = 0;
	int parentheses_inside = 0;
	int square_brackets_inside = 0;
	
	//steps;
	int State = 1;
	
	printf("\n");
	
	//#obs
	//Aqui podemos usar um while(running) até que se encontre o fim do arquivo.

	while (running == 1)
	{
	    //pega o char.
		//#todo: trocar c por TOKEN.
		
	    c = yylex ();
		
		again:
		
		//#debug
	    //printf("%c", c );
		
		
        //#importante		
        //Estamos começando um arquivo. No começo do arquivo 
		//apenas alguns tokens são válidos, são eles:
        // >>'#' do preprocessador
        // >>modificadores 
        // >>qualificadores 
        // >>tipos   		
		
		switch (State)
		{
            //
			//  ## MODIFIER,  TYPE and SEPARATOR ##
			//
						
			//################################
			// #State 1
			// Esperamos um MODIFIER,  TYPE and SEPARATOR
			//
			case 1:
			    printf("<1> ");
				switch (c)
				{
	                case TOKENMODIFIER:
					
#ifdef PARSER_VERBOSE							
						//continua pois precisamos pegar um tipo.
						//#bugbug ??mas e se o modificar vir seguido de um simbolo ???
						printf("State1: TOKENMODIFIER={%s} line %d\n", real_token_buffer, lineno );
#endif
						
						State = 1;
						//goto again;
						break;
					
					//TYPE
					// >>> peekChar=) significa marcação de tipagem.
					// >>> peekSymbol=symbol  significa declaração de variável ou função.
			        case TOKENTYPE:
					
#ifdef PARSER_VERBOSE						
			            printf("State1: TOKENTYPE={%s} line %d\n", real_token_buffer, lineno );
#endif						
						
						id[ID_TYPE] = type_found;
				        
						//depois de um type vem um identificador.
						State = 2;
			            break;
						
						
					// #bugbug	
					// e se o arquivo começar com um separador, então teremos problema.	
					
					case TOKENSEPARATOR:
					
#ifdef PARSER_VERBOSE						
					     printf("State1: TOKENSEPARATOR={%s} line %d\n", real_token_buffer, lineno );
#endif						 

					
						//; função
						if ( strncmp( (char *) real_token_buffer, "(", 1 ) == 0  )
                        {
						    printf("State2: SEP={%s} line %d\n", real_token_buffer, lineno );
								//incrementamos
								//pois podemos estar no primeiro, no segundo etc ...
							parentheses_inside++;
							printf ("[PAR] line %d\n", lineno );  //debug par open
								
								//#test
								//peekChar = c;
								
						        //tentando mandar alguma coisa para o arquivo de output 
						        //pra ter o que salvar, pra construir o assembly file;	
						       // strcat( outfile,"\n segment .text \n");
						    strcat( outfile,"_");
						    strcat( outfile,save_symbol);
						    strcat( outfile,":\n");
								
								//recomeçar a lista. 
								//#bugbug desconsiderando o modificador.
							State = 1;	
							break;
						};							
						
						//entramos no corpo da função.
						if ( strncmp( (char *) real_token_buffer, "{", 1 ) == 0  )
						{
							printf("State1: separator={%s} line %d\n", real_token_buffer, lineno );  
									 
							braces_inside++;
						    printf ("[BRACE] line %d\n", lineno);  //debug par close
									//isso vai para o 1 onde procura-se por modificadores e tipos,
									//mas se estivermos com o corpo da função aberto ele avançará para o próximo state.
							State = 1;
							break;
						};

					    //fechando UM parênteses, provavelmente sem nada dentro.
					    if ( strncmp( (char *) real_token_buffer, ")", 1 ) == 0  )
						{
						    if ( parentheses_inside > 0 )
							{
								printf("[/PAR] line %d\n", lineno);
                                parentheses_inside--;
                                State = 1;
								break;
								//State++;
                                //goto again; 								
							};
						};
						
                        //fechando UM corpo de função. 					
				        if ( strncmp( (char *) real_token_buffer, "}", 1 ) == 0  )
                        {
						    if ( braces_inside > 0 )
							{
								printf("[/BRACE] line %d\n", lineno);
                                braces_inside--;
                                State = 1;
								break;
								//State++;
                                //goto again; 								
							};							
						};
						
					    break;




                    //#bugbug						
					//Não devemos aceitar diretivas do preprocessador nesse momento,
					//pois antes de tudo devemos rodar um preprocessador para expandir as 
					//diretivas.
					
                    //Se o corpo da função estiver aberto podemos ter identificadores sem tipo,
					//que são label: ou chamada de função (call). ou ainda keywords.
					
					//significa que dentro do um corpo de função não encontramos um tipo,
					//então vamos ver do que se trata o token e configurar a variável c.
					//loga após vamos reiniciar o running mas sem pegarmos o próximo token.
					//poderíamos realizar um ungetchar, mas não testamos isso direito.
					
					//Pode ser que não encontramos um token válido no início do documento.
	
					default:
					    //se estamos dentro do parênteses e não encontramos nenhum case acima.
					    if ( parentheses_inside > 0 )
					    {
						    State++;
						    goto again;
					    }	
					    //se estamos dentro de uma chave e não encontramos nenhum case acima.
				        if ( braces_inside > 0 )
					    {
						    State++;
						    goto again;
					    }
						//EOF 
						if( c == TOKENEOF )
						{
						    printf("State1: eof\n");
                            goto debug_output; 							
						}
					    printf("State1: default error\n");
						printf("State1: modifier or type expected on line %d \n", lineno);
						exit(1);
                        break;
						
				}
		        break;
				
				
            //
			//  ## IDENTIFIER ##
			//				
				
			//################################
			// #State 2	
			// Esperamos um identificador, pos estamos logo após um tipo.
			// Pode ser uma função ou uma declaração de variável, isso depende do peekChar.
			case 2:
			    printf("<2> ");
			    switch (c)
				{
				    //identificador. (símbolo)
					//peekChar=: significa que o identificador é uma label. acontece no case.
					//peekChar=( estamos chamando uma função
					//peekChar=; estamos finalizando um goto ou um return.
					//peekChar=, estamos listando variáveis.
					//
					case TOKENIDENTIFIER:
			            
#ifdef PARSER_VERBOSE							
				        printf("State2: TOKENIDENTIFIER={%s} line %d\n", real_token_buffer, lineno );    
#endif 
						
						id[ID_TOKEN] = TOKENIDENTIFIER;
				        id[ID_STACK_OFFSET] = stack_index;
						
                        //salva o símbolo. #isso funciona.						
						sprintf ( save_symbol, real_token_buffer );
						
						//?? não sabemos se real_token_buffer é código ou dados ?? 
						
						
                        c = yylex ();
						
						//printf("test={%s} line %d\n", real_token_buffer, lineno ); 
						
						//: para label 
                        //( para função 
                        //; para declaração de variável.
                        //, para sequência de variável.
                        // = para atribuição de valor à uma variável.
						// vários operadores se estivermos em uma expressão == <= ...
						//... 						
						if ( c == TOKENSEPARATOR )
						{
							//printf("sep \n");
							
						    //: label
							if( strncmp ( (char *) real_token_buffer, ":", 1 ) == 0  )
                            {
						        printf("State2: SEP={%s} line %d\n", real_token_buffer, lineno );
								//tentando mandar alguma coisa para o arquivo de output 
						        //pra ter o que salvar, pra construir o assembly file;	
						       // strcat( outfile,"\n segment .text \n");
						        strcat( outfile,"_");
						        strcat( outfile,save_symbol);
						        strcat( outfile,":\n");
								
								//recomeçar.
								State = 1;
								break;
							}
							
						    //; função
							if ( strncmp( (char *) real_token_buffer, "(", 1 ) == 0  )
                            {
								printf("State2: SEP={%s} line %d\n", real_token_buffer, lineno );
								//incrementamos
								//pois podemos estar no primeiro, no segundo etc ...
								parentheses_inside++;
								printf ("[PAR] line %d\n", lineno );  //debug par open
								
								//#test
								//peekChar = c;
								
						        //tentando mandar alguma coisa para o arquivo de output 
						        //pra ter o que salvar, pra construir o assembly file;	
						       // strcat( outfile,"\n segment .text \n");
						        strcat( outfile,"_");
						        strcat( outfile,save_symbol);
						        strcat( outfile,":\n");
								
								//recomeçar a lista. 
								//#bugbug desconsiderando o modificador.
								State = 1;
								
								break;
							}	

						    //Se encontramos um separador ')' 
						    //entao esperaremos um separador '{'.
						    if ( strncmp( (char *) real_token_buffer, ")", 1 ) == 0  )
					 	    {
								printf("State2: SEP={%s} line %d\n", real_token_buffer, lineno );
								//se não tem parênteses aberto.
								if ( parentheses_inside < 1 )
								{
									printf("state2: Error closing parentheses in line %d ", lineno);
									exit(1);
								}
								
								//fechamos um dos parênteses.
								parentheses_inside--;
								printf ("[/PAR] line %d\n", lineno);  //debug par close
								
							    //é bss porque não foi inicializada.
								//strcat( BSS,"\n segment .bss \n");
						        strcat( BSS,"_");
						        strcat( BSS,save_symbol);
						        strcat( BSS,": dd 0 \n");								
						        
								//?? depois de ) podemos ter o corpo da função.
								//ou outra coisa caso estivermos parentese aberto.
								
								//peek next
								c = yylex ();
								
								//entramos no corpo da função.
								if ( strncmp( (char *) real_token_buffer, "{", 1 ) == 0  )
								{
									printf("State2: separator={%s} line %d\n", real_token_buffer, lineno );  
									 
									braces_inside++;
								    printf ("\n[BRACE] line %d\n", lineno);  //debug par close
									//isso vai para o 1 onde procura-se por modificadores e tipos,
									//mas se estivermos com o corpo da função aberto ele avançará para o próximo state.
									State = 1;
									break;
								}	
									
							    break;
						    }									

						    //; var
							if ( strncmp( (char *) real_token_buffer, ";", 1 ) == 0  )
                            {
						        printf("State2: SEP={%s} line %d\n", real_token_buffer, lineno );
								//tentando mandar alguma coisa para o arquivo de output 
						        //pra ter o que salvar, pra construir o assembly file;	
						        
								//é bss porque não foi inicializada.
								//strcat( BSS,"\n segment .bss \n");
						        strcat( BSS,"_");
						        strcat( BSS,save_symbol);
						        strcat( BSS,": dd 0 \n");
								
								//recomeçar, vai que tem mais variável...
								State = 1;
								break;
							}
							
							
						    //, var (listando) tirando da pilha
							if ( strncmp( (char *) real_token_buffer, ",", 1 ) == 0  )
                            {
						        printf("State2: SEP={%s} line %d\n", real_token_buffer, lineno );
								//tentando mandar alguma coisa para o arquivo de output 
						        //pra ter o que salvar, pra construir o assembly file;	
						        
								//é bss porque não foi inicializada.
								//strcat( BSS,"\n segment .bss \n");
						        strcat( BSS,"_");
						        strcat( BSS,save_symbol);
						        strcat( BSS,": dd 0 \n");
								
								//recomeçar, vai que tem mais variável...
								State = 1;
								break;
							}							
							
							//printf("...");
							//goto debug_output;
							
						}//else{
							//printf("sep fail");
						//}
						
						printf("state2: TOKENIDENTIFIER fail");
						exit(1);
						//tentando mandar alguma coisa para o arquivo de output 
						//pra ter o que salvar, pra construir o assembly file;	
						//strcat( outfile,"\n");
						//strcat( outfile,"_");
						//strcat( outfile,real_token_buffer);
						//strcat( outfile,":\n");
						
						//depois do identificador deve vir um '(' ou um '=';
						//State = 3;
						break;	

                    //Se o corpo da função estiver aberto podemos ter identificadores sem tipo,
					//que são label: ou chamada de função (call). ou ainda keywords.
					
					//significa que dentro do um corpo de função não encontramos um tipo,
					//então vamos ver do que se trata o token e configurar a variável c.
					//loga após vamos reiniciar o running mas sem pegarmos o próximo token.
					//poderíamos realizar um ungetchar, mas não testamos isso direito.
					

 				
                
				    default:
					    //se estamos dentro do parênteses e não encontramos nenhum case acima.
					    if ( parentheses_inside > 0 )
					    {
						    State++;
						    goto again;
					    }	
					    //se estamos dentro de uma chave e não encontramos nenhum case acima.
				        if ( braces_inside > 0 )
					    {
						    State++;
						    goto again;
					    }						
					    printf("State2: default Error.\n");
						printf("State2: expected identifier on line %.\n", lineno);
						exit(1);
					    break;
				};
                break;	


            //
			//  ## KEYWORD ##
			//			
            
            case 3:
			    printf("<3> ");
			    switch(c)
				{
					//KEYWORD.
                    //peekChar=; depois do break, ou continue.(obrigatório)
                    //peekChar=: depois do default.(obrigatório)
                    //peekChar=( depois do switch, if, while ...					
				    case TOKENKEYWORD:
					
#ifdef PARSER_VERBOSE						
					    printf("line %d TOKENKEYWORD={%s} \n", lineno, real_token_buffer );
#endif 
						
						// # return #
						//return. Chamaremos o tratador do stmt parse_return() 
				        if( keyword_found == KWRETURN )
				        {
							
#ifdef PARSER_VERBOSE								
					        printf("State3: TOKENKEYWORD={%s} KWRETURN line %d  \n", real_token_buffer, lineno );
#endif					        
							// parse deve retornar o '(', quando encontrá-lo faz o tratamento até chegar  no ';'
						    // a função deve retornar o separador ';'
				            //indicando que tudo deu certo no parser.
						    //continuaremos nesse state até pegarmos o separador '}'.
							printf ("\n");
					        c = parse_return ( TOKENKEYWORD );
					        printf ("\n");
							
							//esperávamos o separador ';', se não veio então falhou o parser.
							if ( c != TOKENSEPARATOR )
					        {
							    printf("State3: TOKENKEYWORD TOKENSEPARATOR fail");
                                exit(1);								
					        }
							
							//reinicia
							//porque depois de um return podemos ter várias outras coisas.
							//inclusive apenas terminarmos um corpo.
							State = 1;
							break;
				        }

                        if( keyword_found == KWGOTO )
						{
#ifdef PARSER_VERBOSE								
					        printf("State3: TOKENKEYWORD={%s} KWGOTO in line %d \n", real_token_buffer, lineno );
#endif								
						    //parse_goto??
							//Esperamos um identificador logo após o goto.
							State = 2;
							break;
						}
						
                        if( keyword_found == KWIF )
						{
#ifdef PARSER_VERBOSE								
					        printf("State3: TOKENKEYWORD={%s} KWIF in line %d \n", real_token_buffer, lineno );
#endif								
						    //parse_if??
							parse_if (TOKENSEPARATOR);
							//recomeçamos
							State = 1;
							break;
						}
						
						// asm (" ... ");
                        if( keyword_found == KWASM )
						{
#ifdef PARSER_VERBOSE								
					        printf("State3: TOKENKEYWORD={%s} KWASM in line %d \n", real_token_buffer, lineno );
#endif								
						     
							parse_asm (TOKENKEYWORD);
							//recomeçamos
							State = 1;
							break;
						}						

                        //...							
						
						break;
						
					
					//estamos dentro do corpo da função e não encontramos uma keyword.	
					default:
					    if ( parentheses_inside > 0 )
					    {
						    printf("State3: bugbug searching for keyword inside parentheses");
						    exit(1);
					    }
					    if ( braces_inside > 0 )
					    {
						    printf("State3: bugbug searching for keyword inside braces");
						    exit(1);
					    }
						//??em que momento espera-se por uma keyword e não encontra ??
					    printf("State3: default. keyword expected in line %d",lineno);
						exit(1);
						break;
				};
                break;	

            //###################################
            //state4 ';'			
			case 4:
			    printf("<4> ");
				switch (c)
				{
		            case TOKENSEPARATOR:
				        // ';'
                        if ( strncmp( (char *) real_token_buffer, ";", 1 ) == 0  )			 
      	                {
				            //ok #todo
			            }else{
					        printf(" State4: expected ; in line %d", lineno);
					        exit(1);
				        };	
					    break;
					
				        default:
					        printf(" State4: default. expected ; in line %d", lineno);
					        exit(1);				
				            break;
				};	
			    break;
				
			//################################
			// #State 3	
            //	esperamos '(' ou '='
            //pois estamos após o identificador.			
			/*
			case 3:
			    switch (c)
				{
					// separadores (){}[],.;:? ...
			        case TOKENSEPARATOR:
			            printf("State3: TOKENSEPARATOR={%s} line %d \n", real_token_buffer, lineno );
						//Se encontramos um separador '(' vamos ver o que tem dentro.
						State = 4;
						break;

                    //math. + - * / % | & ^ =
					case TOKENOPERATOR:
					    printf("State3: TOKENOPERATOR={%s} line %d  \n", real_token_buffer, lineno );
                        break;					
					
					default:
					    printf("State3: default. Error \n");
						printf("State3: expected separator or operator on line %.\n", lineno);
						exit(1);
					    break;
				}
			    break;
			*/
        		
			//################################
			// #State 4	
			// esperamos um separador ')' para fechar ... ou algum conteúdo 
            // como um tipo e um simbolo e uma virgula.	
            //#importante: estamos dentro do parênteses, e aqui dentro pode ter uma sequencia de 
            //variáveis separadas por vírgula. Vamos voltar se encontrarmos um tipo. 		
            /*
			case 4:
			    switch (c)
			    {
	                // #importante.  
	                // se encontrarmos o separador ')' então completamos os argumentos.
                    // se encontrarmos um tipo, então temos mais argumentos. 
					
					// separadores (){}[],.;:? ...
			        case TOKENSEPARATOR:
			            printf("State4: TOKENSEPARATOR={%s} line %d \n", real_token_buffer, lineno );   
						//Se encontramos um separador ')' 
						//entao esperaremos um separador '{'.
						if ( strncmp( (char *) real_token_buffer, ")", 1 ) == 0  )
						{
						    State = 5;	
							break;
						}						
						
						printf("state4: fail");
						break;
						
					//encontramos um tipo então temos que voltar.
					
			        case TOKENTYPE:
			            id[ID_TYPE] = type_found;
				        printf("State1: TOKENTYPE={%s} line %d\n", real_token_buffer, lineno );
						//depois de um type vem um identificador.
						State = 2;
			            break;						
						
						
					default:
					    printf("State4: default. Error \n");
						printf("State4: Expected ')' on line %d \n",lineno);
						exit(1);
					    break;					
				}
			    break;
			*/
				
			//################################
			// #State 5	
			// esperamos um '{'
			
			/*
            case 5:
			    switch (c)
			    {
					// separadores (){}[],.;:? ...
			        case TOKENSEPARATOR:
			            printf("State5: TOKENSEPARATOR={%s} line %d \n", real_token_buffer, lineno );
						//Se encontramos um separador '{' 
						//ent]ao esperaremos um separador '}'.
						//ou return 0;...
						State = 6;
						break;
					
					default:
					    printf("State5: default. Error \n");
						printf("State5: Separator '{' expected on line %d \n", lineno);
						exit(1);
					    break;					
				}
			    break;
			*/
				
			//################################
			// #State 6	
			// esperamos um '}' ou return 0; ou coisa assim.
            /*			
            case 6:
			    switch (c)
			    {
					//esperamos uma keyword return.
					case TOKENKEYWORD:         
						//return. Chamaremos o tratador do stmt parse_return() 
				        if( keyword_found == KWRETURN )
				        {
					        printf("State6: TOKENKEYWORD={%s} KWRETURN line %d  \n", real_token_buffer, lineno );
					        // parse deve retornar o '(', quando encontrá-lo faz o tratamento até chegar  no ';'
						    // a função deve retornar o separador ';'
				            //indicando que tudo deu certo no parser.
						    //continuaremos nesse state até pegarmos o separador '}'.
							printf ("\n");
					        c = parse_return ( TOKENKEYWORD );
					        printf ("\n");
							
							//esperávamos o separador ';', se não veio então falhou o parser.
							if ( c != TOKENSEPARATOR )
					        {
							    printf("State6: TOKENKEYWORD TOKENSEPARATOR fail");
                                exit(1);								
					        }
							//State = 7;
				        }		
					    break;

			        // Aqui esperamos o separador '}' para fechar a função.
					// separadores (){}[],.;:? ...
			        case TOKENSEPARATOR:
			            printf("State6: TOKENSEPARATOR={%s} line %d \n", real_token_buffer, lineno );                        
				        //encontramos o separador final da função }
						//no próximo state esperaremos o separador final ';' ou não precisa,
						State = 7;
					    break;
					
					default:
					    printf("State6: default. Error \n");
						printf("State6: Expected '}' on line %d \n",lineno);
						exit(1);
					    break;					
				}
			    break;
			*/
				
			//################################
			// #State 7
			//esperamos um ';' para terminar a função.
			/*
            case 7:
			    switch (c)				
				{
					
					// separadores (){}[],.;:? ...
			        case TOKENSEPARATOR:
			            printf("State7: TOKENSEPARATOR={%s} line %d \n", real_token_buffer, lineno );                        
                        //encontramos ';' fim da função
						//vamos sair do while.
						//State = 8;
					    running = 0;
						break;
						
			        case ENDFILE:
                        printf("State7: line %d EOF reached.\n", lineno); 
                        running = 0;						
				        break;		

					default:
					    printf("State7: default. Error \n");
						printf("State2: warning expected ';' on line %.\n", lineno);
						exit(1);
					    break;										
				}
			    break;
            */ 				
				
 
		    default:
#ifdef PARSER_VERBOSE				
			    printf("<default>State default: Error.\n");
#endif				
				if ( parentheses_inside > 0 )
				{
				    printf("default: expected ) in line %d \n", lineno);
                }
				if ( braces_inside > 0 )
				{
				    printf("default: expected } in line %d \n", lineno);
			    }				
				goto debug_output;
				//exit(1);
                break;				
 
	




	    };//switch State	
		
				
		size--;
		
		//sai do while
        if (size <= 0)
		{
			printf("parser: End of size cont\n");
            running = 0;
        }			
	};
	
	//
	// Saimos do while running.
	//
	
	//#debug
	//printf("\n INPUT: \n");
	//printf("%s\n",stdin->_base);
	//printf("number of lines: %d \n",lineno);
	//...
debug_output:

    //incluimos no arquivo de output os segmentos de dados,
	strcat( outfile,DATA);
    strcat( outfile,BSS);
	
#ifdef PARSER_OUTPUT_VERBOSE	
	//exibimos o arquivo de output.
	printf("\n OUTPUT: \n");
	printf("%s\n",outfile);
	printf("number of lines: %d \n",lineno);
#endif	
	
hang:	

	printf("parse: *hang");
	//goto done;    
		while (1){
			
			asm ("pause");
		}
		
		
syntax:	
    printf("parser: systax error in line %d \n",lineno);	
	exit(1);
	
//done:	
	return 0;
}; 


/*
 ***********************************
 * parserInit:
 *     Initializing parser.
 */
int parserInit (){
	
	register int i;
	
	//infile_size = 0;
	//outfile_size = 0;
	
    //stack support
	stack_flag = 0;
	stack_count = 0;
	stack_index = 0;
	

	    
	for ( i=0; i<8; i++ )
		id[i] = 0;
	
	for ( i=0; i<8; i++ )
		constant[i] = 0;
	
	for ( i=0; i<8; i++ )
		return_info[i] = 0;

	for ( i=0; i<512; i++ )
		stack[i] = 0;
	
	//...
	
	//esses endereços vão depender do arquivo de configuração do 
	//linker ...
	//#test: default em 0.
    program_header_address =     0;
    program_text_address   =   100;
    program_data_address   = 2*100;
    program_bss_address    = 3*100;	
	
	//...
	
	return (int) 0;
};

