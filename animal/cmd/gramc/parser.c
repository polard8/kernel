/*
 * File: parser.c
 *
 * 2018 - Created by Fred Nora.
 */
 
#include "gramc.h"


// symbol table (simple list of identifiers)
int *x_sym;     

// currently parsed identifier
int *id;        


char *x_p;        // current position in source code
char *x_lp;       // current position in source code
char *x_data;     // data/bss pointer

int *x_e;       // current position in emitted code
int *x_le;      // current position in emitted code

int x_tk;       // current token
int x_ival;     // current token value
int x_ty;       // current expression type
int x_loc;      // local variable offset
int x_line;     // current line number
int x_src;      // print source and assembly flag
int x_debug;    // print executed instructions


// opcodes #todo
enum { 
       
       OPCODE_NOP, 
       
       OPCODE_LEA, 
       OPCODE_IMM, 
       OPCODE_JMP, 
       OPCODE_JSR, 
       OPCODE_BZ, 
       OPCODE_BNZ, 
       OPCODE_ENT, 
       OPCODE_ADJ, 
       OPCODE_LEV, 
       OPCODE_LI, 
       OPCODE_LC, 
       OPCODE_SI, 
       OPCODE_SC, 
       OPCODE_PSH,
       OPCODE_OR, 
       OPCODE_XOR, 
       OPCODE_AND, 
       OPCODE_EQ, 
       OPCODE_NE, 
       OPCODE_LT, 
       OPCODE_GT, 
       OPCODE_LE, 
       OPCODE_GE, 
       OPCODE_SHL, 
       OPCODE_SHR, 
       OPCODE_ADD, 
       OPCODE_SUB, 
       OPCODE_MUL, 
       OPCODE_DIV, 
       OPCODE_MOD,
       
       OPCODE_OPEN, 
       OPCODE_RUN, 
       OPCODE_READ, 
       OPCODE_CLOS, 
       OPCODE_PRTF, 
       OPCODE_MALC, 
       OPCODE_FREE, 
       OPCODE_MSET, 
       OPCODE_MCMP, 
       OPCODE_EXIT 
};


char save_symbol[32];



//
// Function
//

int parse_function ( int token );




//
// Statements
//

int parse_asm ( int token );
int parse_do ( int token );
int parse_for ( int token );
int parse_if ( int token );
//int parse_number (int olen);
int parse_return ( int token );
unsigned long parse_sizeof ( int token );
int parse_while ( int token );
//...



//
// Expression
//

unsigned long parse_expression ( int token );




//
// Emit
//

void emit_label(void);
void emit_function(void);




void emit_label(void)
{
    strcat (TEXT,";[LABEL]\n");
    strcat (TEXT,"segment .text\n");
    strcat (TEXT,"_");
    strcat (TEXT,save_symbol);
    strcat (TEXT,":\n");
}

void emit_function(void)
{
    strcat (TEXT,";[FUNCTION] (\n");
    strcat (TEXT,"segment .text \n");
    strcat (TEXT,"_");
    strcat (TEXT,save_symbol);
    strcat (TEXT,":\n");
}


// Parse function.
int parse_function (int token){
	
	int c;
	int running = 1;
	int State = 1;
	
	
//#ifdef PARSER_FUNCTION_VERBOSE	
	//debug
	//printf("parse_function: Initializing ...\n");	
//#endif	
	
	
	//se entramos errado.
	if ( token != TOKENIDENTIFIER )
	{
		printf ("parse_function: Can't initialize function statement\n");
		exit (1);
	}
	
	
    if ( token == TOKENIDENTIFIER )	
	{
	
		id[ID_TOKEN] = TOKENIDENTIFIER;
		id[ID_STACK_OFFSET] = stack_index;
		
//#ifdef PARSER_FUNCTION_VERBOSE			
	//	printf ("parse_function: TOKENIDENTIFIER={%s} in line %d\n", 
	//	    real_token_buffer, lineno );    			
//#endif	

	};

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
							
//#ifdef PARSER_FUNCTION_VERBOSE							
	//					    printf ("parse_function: TOKENSEPARATOR={%s} in line %d\n", 
	//						    real_token_buffer, lineno ); 
//#endif
							
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
							
//#ifdef PARSER_FUNCTION_VERBOSE							
	//					    printf ("parse_function: TOKENSEPARATOR={%s} in line %d\n", 
	//						    real_token_buffer, lineno ); 
//#endif
							
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
							
//#ifdef PARSER_FUNCTION_VERBOSE							
	//					    printf ("parse_function: TOKENSEPARATOR={%s} in line %d\n", 
	//						    real_token_buffer, lineno ); 
//#endif						
	
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
				printf ("parse_function: default statement\n");
				exit (1);				    
			    break;
		};
	};	
}




// Parse asm statement.
int parse_asm (int token){
	
	int c;
	int running = 1;
	int State = 1;	
	
	
//#ifdef PARSER_ASM_VERBOSE	
	//debug
	//printf("parse_asm: Initializing ...\n");	
//#endif	


	//se entramos errado.
	if ( token != TOKENKEYWORD)
	{
		printf ("parse_asm: token error\n");
		exit (1);
	}
	
    if ( token == TOKENKEYWORD )	
	{	
		
//#ifdef PARSER_ASM_VERBOSE	
//		printf("parse_asm: TOKENKEYWORD={%s} in line %d\n", 
//		    real_token_buffer, lineno );  
//#endif	
	
	};

	
	int inside = 0;
	
	//
	// (
	//
	
	c = yylex ();
	
	if ( c == TOKENSEPARATOR )
	{
	    if ( strncmp( (char *) real_token_buffer, "(", 1 ) == 0  )
        {
			
//#ifdef PARSER_ASM_VERBOSE				
//			printf("parse_asm: TOKENKEYWORD={%s} in line %d\n", 
//			    real_token_buffer, lineno ); 
//#endif	
		
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
	

    printf ("parse_asm: todo unexpected error in asm string\n");
	exit (1);		
		   
	return 0;
}



// Parse do statement.
int parse_do (int token){
	
	printf("todo: parse_do in line %d\n ", lineno );
	exit (1);
	
    return -1;	
}




// Parse for statement.
int parse_for ( int token ){
	
	printf ("todo: parse_for in line %d \n", lineno );
	exit (1);
	
    return -1;	
}





// Parse if statement.
int parse_if (int token){
	
	int If_Result = -1;
	
	unsigned long Exp_Result = 0;
	
	printf("todo: parse_if in line %d \n", lineno );
	
	//#todo
	//conferir se o token do argumento é um if 
	
	//#todo 
	//temos que criar State para if.
	
	//pega o próximo que deve ser um (
	int c = yylex();
	
	if ( c != TOKENSEPARATOR )
	{
		printf ("parse_if separator missed\n");
		exit (1);
	}
	
	//
	// Expression.
	//
	
	//testando chamar uma análise de expressão dentro do statement de if.
	Exp_Result = parse_expression ( c );
	
	//#importante 
	//retornamos 1 ou 0 da análise da expressão,
	//quem chamou o if vai armazenar esse valor para 
	//chamar o else.
	If_Result = (int) Exp_Result;
	
	printf ("EXP={%d}\n",Exp_Result);
	
	c = yylex();
	if ( c != TOKENSEPARATOR )
	{
		printf ("parse_if separator { missed\n");
		exit(1);
	}
	
	c = yylex();
	if ( c != TOKENSEPARATOR )
	{
	printf ("parse_if separator } missed\n");
		exit(1);
	}
	
	c = yylex();
	if ( c != TOKENSEPARATOR )
	{
		printf ("parse_if separator ; missed\n");
		exit(1);
	}
	
	//exit(1);
    return (int) If_Result;	
}






// Parse number statement.
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






// Parse return statement.
// >> termina com  ';'
// return 0;
// return (int) 1;
// return 1+2;
// return (1+2);
// return (int) (1+2);
// return function();
// return (int) function();
int parse_return (int token){

    int c;

	int running = 1;
	int State = 1;
	int open = 0;
	unsigned long eval_ret;
	char buffer[32];
	//char *buffer;


	//debug
	printf ("parse_return: Initializing ...\n");	
	
	// Se entramos errado.
    if ( token != TOKENKEYWORD || keyword_found != KWRETURN ){
        printf ("parse_return: Can't initialize return statement\n");
        exit (1);
    }


	// #obs:
	// Isso significa que o token atual é uma keyword 'return'.
 	// Se a próxima keyword for um ';' então não temos uma expressão.	
 		
 		
    //
    // Eval.
    //

    eval_ret = (unsigned long) tree_eval ();


    // itoa
     itoa ( (int) eval_ret, buffer );
 
    
    // ??
	//buffer = (char *) itoa ( (int) eval_ret);

    //
    // Output
    //

    // emit_return();
    strcat ( TEXT,";[RETURN]\n");
    strcat ( TEXT,"  mov eax, ");
    strcat ( TEXT, buffer );
    strcat ( TEXT,"\n  ret \n\n");

	//strcat ( outfile,"  mov eax, ");
	//strcat ( outfile, buffer );
	//strcat ( outfile,"\n  ret \n\n");


	//o ultimo token em um return statement foi ';'
	//vamos conferir
    if ( strncmp( (char *) real_token_buffer, ";", 1 ) == 0  )
    {
		//printf("; OK ");
		c = TOKENSEPARATOR;
		return c;
	}	

    //
    // ** Debug hang
    //
    
	//#debug
	printf ("parse_return: debug *hang");
	while(1){}
	
	//#obs 
	//supendemos todo o resto abaixo por enquanto.
	
    /*	
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
							
#ifdef PARSER_RETURN_VERBOSE							
							printf("parse_return: separator ';' in line %d\n", 
							    lineno );
#endif							
							
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
#ifdef PARSER_RETURN_VERBOSE							
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
		
#ifdef PARSER_RETURN_VERBOSE		
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

#ifdef PARSER_RETURN_VERBOSE
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

    */	
	
done:		

   return c;
}








unsigned long parse_sizeof ( int token ){
	
	unsigned long Result = 0;
	
    int c = token;	
	
	if ( c != TOKENKEYWORD )
	{
		printf("parse_sizeof: fail");
		exit(1);
	}
 
    int State = 1;
	int running = 1;
	
	while (running)
	{
		c = yylex (); 
		
		again:
		
	    switch (State)
        {
		    //#todo
			//(	
		    case 1:
			    printf("parse_sizeof: State 1\n");
			    if ( c == TOKENSEPARATOR )
				{
					State = 2;
				    break;	
				}
				printf("parse_sizeof: State 1 fail");
		        exit(1);
				break;
			   
			//#todo   
		    //tipo, símbolo, etc ...	
		    case 2:
				printf("parse_sizeof: State 2\n");
				//#todo modifier 
				//if ...
			    if ( c == TOKENTYPE )
				{
					switch (type_found)
					{
						case TNULL:
						    Result = sizeof(0);
						    break;
							
						case TINT:
						    Result = sizeof(int);
							break;

						case TVOID:
						    Result = sizeof(void);
						    break;

						case TCHAR:
						    Result = sizeof(char);
						    break;

						case TSHORT:
						    Result = sizeof(short);
						    break;
							
						case TLONG:
						    Result = sizeof(long);
                            break;						

							
						default:
				        printf("parse_sizeof: State 2 unexpected type found in line %d", 
				           lineno);						
						   break;
					}
					State = 3;
					break;
				};
				    
				printf("parse_sizeof: #TODO State 2 unexpected element on sizeof in line %d", 
				    lineno);
		        exit(1);				              					
		        break;

		    //#todo
			//)	
		    case 3:
			    printf("parse_sizeof: State 3\n");
			    if ( c == TOKENSEPARATOR )
				{
					goto done;
					//State = 2;
				    break;	
				}
				printf("parse_sizeof: State 3 fail");
		        exit(1);		        
				goto done;
				break;

			default:
		        printf("parse_sizeof: default State");
		        exit(1);                
				break;			
		};		
	};
		
done:	

    return (unsigned long) Result;	
}






// Parse while statement.
int parse_while (int token){
	
	int While_Result = -1;
	unsigned long Exp_Result = 0;
	
	printf("todo: parse_while in line %d\n ", lineno );
	
	//#todo
	//conferir se o token do argumento é um while

	//pega o próximo que deve ser um (
	int c = yylex();

	if ( c != TOKENSEPARATOR )
	{
		printf ("parse_while separator missed\n");
		exit(1);
	}
	
	//testando chamar uma análise de expressão dentro do statement de while.
	Exp_Result = parse_expression ( c );
	While_Result = (int) Exp_Result;
	
	c = yylex();
	if ( c != TOKENSEPARATOR )
	{
		printf ("parse_while separator { missed\n");
		exit(1);
	}
	
	c = yylex();
	if ( c != TOKENSEPARATOR )
	{
	printf ("parse_while separator } missed\n");
		exit(1);
	}
	
	c = yylex();
	if ( c != TOKENSEPARATOR )
	{
		printf ("parse_while separator ; missed\n");
		exit(1);
	}
	
	printf ("EXP={%d}\n",Exp_Result);
	
	//exit(1);
    return (int) While_Result;	
}









// Parse expression.
// Analizando uma expressão.
// Temos a questão de predecessores para os operadores.

unsigned long parse_expression ( int token ){

    //#todo tree
    
	int c;
	
	int eCount = 0;
	
	//operator
	int Op;
	unsigned long sizeof_constant;
	int sizeof_flag = 0;
	
	// e1=x  e2=y
	unsigned long e[2];	
	unsigned long Result = 0;

	
	c = token;
	
	
    
	//primeiro analizamos o que veio via argumento 
	//assim checaremos a validade da expressão e
	//abortaremos logo cedo.
	
	//uma expressão pode começar com (, operador, número ...
	//então vamos ver qual é o primeiro token da expressão.
	
	
    switch (c)
	{
		case TOKENSEPARATOR:
	        if ( strncmp( (char *) real_token_buffer, "(", 1 ) == 0  )
			{
				
				
//#ifdef PARSER_EXPRESSION_VERBOSE				
//			    printf("parse_expression: TOKENSEPARATOR={%s} in line %d\n", 
//				    real_token_buffer, lineno ); 
//#endif 


				//State = 2;	
			}
		    break;
	    default:

//#ifdef PARSER_EXPRESSION_VERBOSE		
//           printf ("parse_expression: State 1 Missed '(' separator in line %d \n", 
//			    lineno );
//#endif	
		
			exit(1);
			break;					
	}	
	
	
	// #todo:
	// #importante:
	// estamos suspendendo a parte de baixo e chamado uma rotina 
	// em tree para calcular a expressão.
	return (unsigned long) tree_eval ();
	
	//===========================================================
	
	/*
	int running = 1;
	int State = 1;
	
	//agora pegaremos os outros elementos da expressão.
	
	while (running == 1)
	{
	    c = yylex ();
		
		//voltando sem pegar.
		again:
		
		
		if( c == TOKENEOF )
		{
            printf("parse_expression: #error EOF \n");
            exit(1);			
		}		
	    
		switch (State)   
	    {
			
			//===================
			//State 1
			//Aceitamos constantes ou identificadores.
			//não vamos começar com operadores e sim com operandos,
			//que pdoem ser números ou identificadores.
			case 1:
			    switch(c)
				{
					
					case TOKENSEPARATOR:
	                    if ( strncmp( (char *) real_token_buffer, "(", 1 ) == 0  )
						{
#ifdef PARSER_EXPRESSION_VERBOSE								
						    printf("parse_expression: TOKENSEPARATOR={%s} in line %d\n", 
							    real_token_buffer, lineno ); 
#endif							
							//State = 1;	
						    break;
						}
	                    if ( strncmp( (char *) real_token_buffer, ")", 1 ) == 0  )
						{
							
#ifdef PARSER_EXPRESSION_VERBOSE								
						    printf("parse_expression: TOKENSEPARATOR={%s} in line %d\n", 
							    real_token_buffer, lineno );
#endif								
							//State = 1;
                            //provisório
							//retornaremos, mas falta o corpo {...};
							goto expression_exit;
							break;							
						}						
					    break;
					
					
					
					case TOKENCONSTANT:					
						//ok;
#ifdef PARSER_EXPRESSION_VERBOSE							
						printf ("parse_expression: State1 TOKENCONSTANT={%s} line %d\n", 
						    real_token_buffer, lineno );
#endif
						
						switch(eCount)
						{
							//primeiro elemento
							//esperamos uma constante
							case 0:
							
#ifdef PARSER_EXPRESSION_VERBOSE								
							    printf("eCount-case-0:\n");
#endif								
								//se estamos lidando com a contante gerada pelo sizeof.
								if( sizeof_flag == 1 )
								{
									e[0] = sizeof_constant;
									sizeof_flag = 0;
									
								}else{
									e[0] = (unsigned long) atoi (real_token_buffer);
								};								
								
								eCount++;
								//vamos para o tratador de operadores.
								State = 2;
								break;
								
							//segundo elemento	
							//error: o operador é tratado em outro case.
							case 1:
#ifdef PARSER_EXPRESSION_VERBOSE								
						        printf("eCount-case-1:\n");
								printf ("parse_expression: State1 error unexpected operator element TOKENCONSTANT={%s} line %d\n", 
						            real_token_buffer, lineno );
#endif                                
								exit(1); 									
							    break;
								
							//terceito elemento	
							//esperamos uma constante
							case 2:
#ifdef PARSER_EXPRESSION_VERBOSE								
							    printf("eCount-case-2:\n");
#endif							    
								//se estamos lidando com a contante gerada pelo sizeof.
								if( sizeof_flag == 1 )
								{
									e[1] = sizeof_constant;
									sizeof_flag = 0;
									
								}else{
									e[1] = (unsigned long) atoi (real_token_buffer);
								};
								eCount = 0;
								switch (Op)
								{
								    case PLUS_EXPR:
                                        Result = (unsigned long) ( (unsigned long) e[0] + (unsigned long) e[1] ); 									
								        break;
										
								    case MINUS_EXPR:
                                        Result = (unsigned long) ( (unsigned long) e[0] - (unsigned long) e[1] ); 									
								        break;

								    case BIT_AND_EXPR:
                                        Result = (unsigned long) ( (unsigned long) e[0] & (unsigned long) e[1] ); 									
								        break;

								    case BIT_IOR_EXPR:
                                        Result = (unsigned long) ( (unsigned long) e[0] | (unsigned long) e[1] ); 									
								        break;	

								    case MULT_EXPR:
                                        Result = (unsigned long) ( (unsigned long) e[0] * (unsigned long) e[1] ); 									
								        break;
										
								    case TRUNC_DIV_EXPR:
                                        Result = (unsigned long) ( (unsigned long) e[0] / (unsigned long) e[1] ); 									
								        break;
										
								    case TRUNC_MOD_EXPR:
                                        Result = (unsigned long) ( (unsigned long) e[0] % (unsigned long) e[1] ); 									
								        break;
										
								    case BIT_XOR_EXPR:
                                        Result = (unsigned long) ( (unsigned long) e[0] ^ (unsigned long) e[1] ); 									
								        break;
										
								    case LSHIFT_EXPR:
                                        Result = (unsigned long) ( (unsigned long) e[0] << (unsigned long) e[1] ); 									
								        break;
										
										
								    case RSHIFT_EXPR:
                                        Result = (unsigned long) ( (unsigned long) e[0] >> (unsigned long) e[1] ); 									
								        break;
										
								    case LE_EXPR:
                                        Result = (unsigned long) ( (unsigned long) e[0] <= (unsigned long) e[1] ); 									
								        break;
										
								    case GE_EXPR:
                                        Result = (unsigned long) ( (unsigned long) e[0] >= (unsigned long) e[1] ); 									
								        break;
										
									//...	
									
									default:
                                        printf("parse_expression: State1 default Op={%d}",Op);
										exit(1);             
										break;									
								};
								
								// ( 1 + 2 ')'
								//vamos ver se o que vem depois da segunda constante é um esperado separador 
								//ou outracoisa.
								c = yylex ();
								
								//Ok temos um sepador
								//vamos tratá-lo
								if ( c == TOKENSEPARATOR )
								{
									State = 1;
								    goto again;	
								}else{
									printf("expected separator in line %d", lineno);
									exit(1);
								}
								
								
								//vamos ver se tem um separador ou não
								//que finalize a expressão.
								//então continuaremos no State 1.
								//State = 1;							
							    break;
								
							default:
						        printf ("parse_expression: State1 error #default TOKENCONSTANT={%s} line %d\n", 
						            real_token_buffer, lineno );
								exit(1);
							    break;
						};
						break;
						
					case TOKENIDENTIFIER:
						printf ("parse_expression: State1 #todo TOKENIDENTIFIER={%s} line %d\n", 
						    real_token_buffer, lineno );					
					    //State = 2;
						exit(1);
						break;
						
					//sizeof	
					case TOKENKEYWORD:
					    if (keyword_found == KWSIZEOF)
						{
							
#ifdef PARSER_EXPRESSION_VERBOSE								
						   printf("parse_expression: State1 sizeof found in line %d\n", lineno); 	
#endif						   
						    //#bugbug
							//não sabemos se é a primeira ou a segunda constante.
							sizeof_constant = (unsigned long) parse_sizeof (TOKENKEYWORD);
							sizeof_flag = 1;
							
#ifdef PARSER_EXPRESSION_VERBOSE								
							printf("SIZEOF={%d}\n", sizeof_constant );
#endif 
							
							c = TOKENCONSTANT; //transformamos a keyword em constant.
							State = 1;
							goto again;
							//eCount++;
							
							//c = yylex();
							//if ( c == TOKENSEPARATOR )
							//{
							//	State = 1;
							//    goto again;
							//}
							
							//se o próximo não for um separador então temos mais operadores e 
							//constantes.
							//depois de um sizeof tem operadores ou separador.
							//vamos para o 2 porque esperamos por operador.
							State = 2;						   
						    break;
						    //exit(1);	
						};
					    break;	
					//...
					
					default:
					    //printf("parse_expression: default case in State 1");
						//exit(1); //die();
					    //vamos permitir operadores, indo para o state2, 
						//ele voltará par o state 1 se for um número ou identificador.
						State = 2;
						goto again;
						break;
				}
			   break;
			   
			//=================
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
					
#ifdef PARSER_EXPRESSION_VERBOSE						
					    printf("parse_expression: State 2 simple operator{%s} lexer_code=%d \n", 
						    real_token_buffer, lexer_code );
#endif					    
						
						if ( eCount != 1 )
						{
							printf ("parse_expression: State 2 eCount error %d", eCount);
							exit(1);
						}
						//avançamos para pegarmos constantes.
						eCount++; 
						
						switch (lexer_code)
						{
                            case PLUS_EXPR:
							    Op = PLUS_EXPR;
                                break;
								
							case MINUS_EXPR:
							    Op = MINUS_EXPR;
								break;
								
                            case BIT_AND_EXPR:
							    Op = BIT_AND_EXPR;
								break;
								
                            case BIT_IOR_EXPR:
							    Op = BIT_IOR_EXPR;
								break;
								
                            case MULT_EXPR:
							    Op = MULT_EXPR;
								break;
								
                            case TRUNC_DIV_EXPR:
                                Op = TRUNC_DIV_EXPR;
								break;
								
							case TRUNC_MOD_EXPR:
                                Op = TRUNC_MOD_EXPR;
								break;
								
							case BIT_XOR_EXPR:
                                Op = BIT_XOR_EXPR;
								break;
								
							case LSHIFT_EXPR:
                                Op = LSHIFT_EXPR;
								break;
								
							case RSHIFT_EXPR:							
							    Op = RSHIFT_EXPR;
								break;
								
							//...	
								
							default:
                                printf ("parse_expression: State 2 default lexer code %d", lexer_code );
								exit (1); 
								break;							
							//...
						}
						//voltamos para pegarmos constantes.
						State = 1;
						break;		
					
					case ARITHCOMPARE:
					
#ifdef PARSER_EXPRESSION_VERBOSE	
					    printf("parse_expression: State 2 ARITHCOMPARE{%s} lexer_code=%d \n", 
						    real_token_buffer, lexer_code );
#endif					    
						if ( eCount != 1 )
						{
							printf ("parse_expression: State 2 eCount error %d", eCount);
							exit(1);
						}
						//avançamos para pegarmos constantes.
						eCount++; 						
						
						switch (lexer_code)
						{
							case LE_EXPR:
							    Op = LE_EXPR;

#ifdef PARSER_EXPRESSION_VERBOSE									
								printf("parse_expression: LE_EXPR lexer_code=%d \n", lexer_code );
#endif							    
								//State = 1;
								break;
								
							case GE_EXPR:
							    Op = GE_EXPR;
#ifdef PARSER_EXPRESSION_VERBOSE									
								printf("parse_expression: GE_EXPR lexer_code=%d \n", lexer_code );
#endif							    
								//State = 1;
								break;
	
								
							///...	
								
							default:
							    printf("parse_expression: State 2 error ARITHCOMPARE default lexer_code=%d in line %d \n", 
								    lexer_code, lineno );
							    exit(1); //die();
								//State = 1;
								break;
						};
						State = 1;
						break;
					   
				    
					case EQCOMPARE:
#ifdef PARSER_EXPRESSION_VERBOSE						
					    printf("parse_expression: State 2 EQCOMPARE{%s} lexer_code=%d \n", 
						    real_token_buffer, lexer_code );
#endif						
						switch (lexer_code)
						{
							
							case NE_EXPR:
#ifdef PARSER_EXPRESSION_VERBOSE								
							    printf("parse_expression: NE_EXPR lexer_code=%d \n", lexer_code );
#endif							    
								State = 1;
								break;
								
							case EQ_EXPR:
#ifdef PARSER_EXPRESSION_VERBOSE								
							    printf("parse_expression: EQ_EXPR lexer_code=%d \n", lexer_code );
#endif							    
								State = 1;
								break;							
							
							default:
							    printf("parse_expression: State 2 error EQCOMPARE default lexer_code=%d in line %d \n", 
								    lexer_code, lineno );
							    //exit(1); //die();
								State = 1;
								exit(1);
								break;
                        };						
					    break;
					   
					case ASSIGN:
#ifdef PARSER_EXPRESSION_VERBOSE						
                        printf("parse_expression: State 2 ASSIGN{%s} lexer_code=%d \n",  
						    real_token_buffer, lexer_code );
#endif						
						State = 1;
						break;					
					   
					case PLUSPLUS:
#ifdef PARSER_EXPRESSION_VERBOSE						
					   printf("parse_expression: State 2 PLUSPLUS{%s} lexer_code=%d \n",  
					       real_token_buffer, lexer_code );
#endif					   
					   State = 1;
					   break;
					   
					case MINUSMINUS:
#ifdef PARSER_EXPRESSION_VERBOSE						
					   printf("parse_expression: State 2 MINUSMINUS{%s} lexer_code=%d \n", 
					       real_token_buffer, lexer_code );
#endif					   
					   State = 1;
					   break;
					   
					case ANDAND:
#ifdef PARSER_EXPRESSION_VERBOSE						
					   printf("parse_expression: State 2 ANDAND{%s} lexer_code=%d \n",  
					       real_token_buffer, lexer_code );
#endif					   
					   State = 1;
					   break;
					   
					case OROR:
#ifdef PARSER_EXPRESSION_VERBOSE						
					   printf("parse_expression: State 2 OROR{%s} lexer_code=%d \n",  
					       real_token_buffer, lexer_code );
#endif					   
					   State = 1;
					   break;
					   
					   
					case POINTSAT:
#ifdef PARSER_EXPRESSION_VERBOSE						
					   printf("parse_expression: State 2 POINTSAT{%s} lexer_code=%d \n", 
					       real_token_buffer, lexer_code );
#endif
					   State = 1;
					   break;
					   
					case LSHIFT:
#ifdef PARSER_EXPRESSION_VERBOSE						
					   printf("parse_expression: State 2 LSHIFT{%s} lexer_code=%d \n", 
					       real_token_buffer, lexer_code );
#endif
					   State = 1;
					   break;
					   
					   
					case RSHIFT:
#ifdef PARSER_EXPRESSION_VERBOSE						
					   printf ("parse_expression: State 2 RSHIFT{%s} lexer_code=%d \n", 
					       real_token_buffer, lexer_code );
#endif					   
					   State = 1;
					   break;
					   
					//...
					
					default:
					    printf("parse_expression: default case in State 2 {%s} lexer_code=%d \n",real_token_buffer, lexer_code );
						State = 1;
						goto again;
					    break;
				};
           	    break;		 
            
            //...
			
			//State default
            default:	
                printf("parse_expression: default State {%s} lexer_code=%d \n",real_token_buffer, lexer_code );
                exit(1); //die();				
		        break;
	    };
	};
	
	*/
	
expression_exit:
    
	return (unsigned long) Result;
}


void stmt(void);
void stmt(void)
{
    // #todo:
    // o que segue é uma keyword.
    // temos que ver qual statemente é a keyword e
    // chamar a rotina de tratamento apropriada para cada stmt.
    
    switch ( keyword_found )
    {
        case KWRETURN:
            printf ("stmt: [TODO] KWRETURN found\n");
            break;
            
        case KWGOTO:
            printf ("stmt: [TODO] KWGOTO found\n");
            break;
                  
        case KWIF:
            printf ("stmt: [TODO] KWIF found\n");
            break;
            
        case KWWHILE:
            printf ("stmt: [TODO] KWWHILE found\n");
            break;

        case KWASM:
            printf ("stmt: [TODO] KWASM found\n");
            break;
            
            
        default:
            printf ("stmt: [TODO] DEFAULT keyword_found found\n");
            break;
    };                      
}


/*
 *********************************************************
 * parse:
 *     Função principal.
 *     Pegando tokens com o lexer e fazendo coisas ...
 */
 
int parse (){

    int running = 1;

    register int token;
    
    
    //++
    int fd, bt, ty, poolsz, *idmain;
    
    // vm registers
    int *reg_pc; 
    int *reg_sp; 
    int *reg_bp; 
    int reg_a;
    int reg_cycle; 
    // ...   
    //--

    int i;


    //Se entramos em um desses corpos.
    int braces_inside = 0;
    int parentheses_inside = 0;
    int square_brackets_inside = 0;

    int If_Result = -1;
    int While_Result = -1;
    //...

    // steps;
    int State = 1;


    size_t size;
 
    // arbitrary size
    poolsz = 256*1024;


    // Buffer.
    // sym, le, data, sp
    
    // symbol table (simple list of identifiers)
    if (!(x_sym = malloc(poolsz))) 
    { printf("could not malloc(%d) symbol area\n", poolsz); return -1; }
    
    // #importante:
    // id é um ponteiro. Temos que inicializar para usar.
    id = x_sym;
 
    // limpa o primeiro id[]
    for ( i=0; i<8; i++ )
        id[i] = 0;
   
    // x_le current position in emitted code
    // x_e current position in emitted code
    if (!(x_le = x_e = malloc(poolsz))) 
    { printf("could not malloc(%d) text area\n", poolsz); return -1; }
    
    // data/bss pointer
    if (!(x_data = malloc(poolsz))) 
    { printf("could not malloc(%d) data area\n", poolsz); return -1; }
    
    // register.
    if (!(reg_sp = malloc(poolsz))) 
    { printf("could not malloc(%d) stack area\n", poolsz); return -1; }


    memset(x_sym,  0, poolsz);
    memset(x_e,    0, poolsz);
    memset(x_data, 0, poolsz);
   
    
     
    // #bugbug
    // Tentando encontrar o tamanho do arquivo via fseek/ftell.

     // #bugbug
     // Esse tratamento de size está suspenso,
     // pois não conseguimos calcular o tamanho do
     // arquivo.

    //++
    //===============================
    // seek to end of file
    //fseek ( stdin, 0, SEEK_END);
    
    // get current file pointer 
    //size = ftell (stdin); 
    
    // seek back to beginning of file
    //fseek (stdin, 0, SEEK_SET); 
    
    // #debug
    //printf ("Size=%d\n", size);
    //====================
    //--


    //
    // Initial message.
    //
    
    printf ("parse: Initializing ...\n");
    printf ("parse: [TODO] Now we have a new parser.\n"); 
    // It needs to use if else instead of switch.   



    //
    // [TODO]
    //
    
    // #todo:
    // Vamos fazer o parser ficar igual ao parser do gramc4.
    // usando os mesmos if else e while.
    // E no fim vamos rodar as funções.
    // Igualzinho.
    // Mas temos que aceitar o jeito em que nosso parser
    // nos oferece os tokens.


    // This llop needs to look like gramc4.
    // It will use if else instead of switch.
    
    token = yylex();  //next
    
    while (running == 1)
    {
        // EOF: O lexer nos disse que acabou.
        if ( token == TOKENEOF ){ printf ("parse: ~EOF\n"); running = 0; break; }
 
        // tipos: INT CHAR 
        if ( token == TOKENTYPE ){ id[ID_TYPE] = type_found; token = yylex(); }
        
        // symbol depois do tipo.
        // #bugbug: E se o anterior não foi um tipo ??
        
        // Apocalipse: Enquanto for diferente do fim.';' '}'.
        //while (tk != ';' && tk != '}')
        while (1)
        {
            // O fim!
            // volta par ao while principal. 
            // Pois terminamos uma declaração de variável ou um corpo de função.
            if ( token == TOKENSEPARATOR )
            {
                if ( strncmp( (char *) real_token_buffer, ";", 1 ) == 0  ){ break; } 
                if ( strncmp( (char *) real_token_buffer, "}", 1 ) == 0  ){ break; }  
            }
            
            // *Alerta: Precisamos de um symbol depois do tipo.
            // Se não é um symbol. Fail!
            if (token != TOKENIDENTIFIER) 
            { 
                printf ("%d: symbol expected \n", lineno);  
                printf ("%d: {%s} \n", lineno, real_token_buffer);
                exit (1);
            }
            
            // #debug - symbol found!
            printf ("%d: $$$ symbol found! {%s} \n", lineno, real_token_buffer);


            id[ID_TOKEN] = TOKENIDENTIFIER;
            id[ID_OPCODE] = OPCODE_NOP;
            id[ID_STACK_OFFSET] = stack_index;
            // Não sei a que classe pertence o symboll
            // se é função ou variável.
            id[ID_CLASS] = IDCLASS_NOTHING;  

            // Salva o símbolo. #isso funciona.
            sprintf ( save_symbol, real_token_buffer );
       
            //main:
            if ( strncmp( (char *) real_token_buffer, "main", 4 ) == 0  )
            { 
                idmain = id; 
                id[ID_CLASS] = IDCLASS_FUNCTION;
            }
            
            // Avança para depois de um identifier.
                              
            token = yylex();  //next
            
            // Depois do symbol
            //printf("%s\n",real_token_buffer );
            
            // FUNCTION: Pilha de parâmetros.
            // () 
            if ( token == TOKENSEPARATOR )
            {
            	//printf("::::%s\n",real_token_buffer );

                // '(': abertura de pilha de parâmetros. 
                if ( strncmp( (char *) real_token_buffer, "(", 1 ) == 0  )
                {
                	//printf ("::(\n");
                    // Mudando a classe. Agora temos uma função.
                    id[ID_CLASS] = IDCLASS_FUNCTION;
                                
                    // break;
                    // dentro da ílha de parâmetros.
                    // Apocalipse: Enquanto for diferente do fim.')'.
                    while(1)
                    {
                        token = yylex();  
                        
                        // Termina a pilha de parâmetros.
                        if ( token == TOKENSEPARATOR )
                        {
                            if ( strncmp( (char *) real_token_buffer, ")", 1 ) == 0  ){ break; }
                            //if ( strncmp( (char *) real_token_buffer, ",", 1 ) == 0  ){ printf("::,\n"); }
                        }        
                        // #bugbug: loop infinito se não encontrar ).
                    };
                    
                    token = yylex();  //next

                    // Acabou a pilha de parâmetros.

                    // vamos entrar no corpo.
                    // '{'
                    if ( token != TOKENSEPARATOR )
                    { printf ("%d: Expected { separator!\n", lineno); exit(-1); }
                    
                    // É um separador, mas não é o que queremos.
                    if ( strncmp( (char *) real_token_buffer, "{", 1 ) != 0  )
                    { printf ("%d: Expected { separator!\n", lineno);exit(-1); }
                    
                    // encontramos o { ...
                    // Entraremos no corpo da função.
                    
                    while (1)
                    {
                        token = yylex(); 

                        // Apocalipse:  Enquanto for diferente do fim.'}'.
                        if ( token == TOKENSEPARATOR )
                        {
                            // FIM !!!
                            // Se chegou ao fim, temos que atualizar a tabela de symbolos.
                            if ( strncmp( (char *) real_token_buffer, "}", 1 ) == 0  )
                            { 
                                id = id + ID_SIZE;
                                break;
                            }
                        }
                        
                        // #todo
                        // Enquanto não chega ao fim analizaremos os statements.
                        // Todo statement é uma keyword.
                        if ( token == TOKENKEYWORD )
                        {
                            id[ID_CLASS] = IDCLASS_STATEMENT; 
                            
                            // #todo
                            // comparar e chamar a rotina de tratamento do statemente específico.
                            // ou chamar uma rotina genérica que seja um hub de statement.
                            // stmt();
                            stmt();
                        }
                        
                        
                        // EOF: O lexer nos disse que acabou o arquivo, mas não encontramos o apocalipse.
                        if ( token == TOKENEOF )
                        { printf ("%d: [ERROR] Missing }\n", lineno); running = 0; break; }
                    };
                }
                
                // Era um separador, mas não era abertura de pilha de parâmetros.
                
                // Separador de symbols.
                if ( strncmp( (char *) real_token_buffer, ",", 1 ) == 0  )
                { 
                    //printf ("%d:  ',' found\n", lineno); 
                    break; 
                }
                
                // ??
                // O que temos aqui ???
                // Cuidado.
                
              // Não era um separador depois do symbol.
            } else { 
                printf ("%d: Separator expected!\n", lineno);  exit(-1);
            };
            

            //#debug
            //printf ("%d: Unexpected error!\n", lineno);
            break;
            
        }; //while. Finalização de declaração ou corpo.
        
        
        // poderia pegar o pŕoximo e recomeçar o while.
        // a última função precis ser um main() ?
        
        token = yylex();  //next
         
        
        // #importante:
        // Só sai do while principal no fim do arquivo.
        
        //#debug
        //break;
        
    }; //while principal.




    //#todo
    //Para rodar as funções precisamos da pilha.


    // Step 4.

    //
    // Run...
    //
    
   // int Wait_status;
    
    // ??
    // Vamos rodar o interpretador ?
    // Realizando algumas instruções.

    int inst =0; // instruction.

    reg_cycle = 0;
    
    printf ("\n");
    printf ("Running ...\n");
    printf ("\n");
    
    // Começamos com main.
    reg_pc = (int *) &idmain[ID_OPCODE];

    while (1)
    {
        ++reg_cycle;
    
        // Pega o program counter e 
        // incrementa para pegar o próximo.
         
        //i = *pc++;
         
        //inst = id[ID_OPCODE];
         inst = *reg_pc;
         
         // Proxima instrução é proxima função ??
         id = id + ID_SIZE;
         reg_pc = (int *) &id[ID_OPCODE];
         
         // NOP 
         if ( inst == OPCODE_NOP ){
             printf ("OPCODE_NOP on cycle %d \n", reg_cycle); 
             break;
         
         
         // LEA
         }
         else if ( inst == OPCODE_LEA ){
             printf ("LEA: on cycle %d \n", reg_cycle); 
             //break;
         
         //...
         
         // ERROR
         }
         else {
            printf ("unknown instruction: opcode=%d! cycle = %d\n", inst, reg_cycle); 
            exit(-1); 
         };
     };



    // reaproveitas as intruções abaixo.
    /*
    //--
    while (1)
    {

        //i = *pc++; 
        //++cycle;
    
        if (debug){

            printf ("parser: [TODO]  debug stuff\n");
            
            //printf ("%d> %.4s", cycle,
                //&"LEA ,IMM ,JMP ,JSR ,BZ  ,BNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PSH ,"
                //"OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,"
                //"OPEN,RUN,READ,CLOS,PRTF,MALC,FREE,MSET,MCMP,EXIT,"[i * 5]);
            
            //if (i <= ADJ) printf (" %d\n", *pc); else printf("\n");
        }
        
        // O interpretador realiza algumas instruções.

        // load local address
        if      (i == LEA) { 
            //a = (int)(bp + *pc++); 
        
        // load global address or immediate
        } 
        else if (i == IMM) { 
            //a = *pc++; 
        
        // jump
        } 
        else if (i == JMP) { 
            //pc = (int *)*pc; 
        
        // jump to subroutine
        }  
        else if (i == JSR) { 
            //*--sp = (int)(pc + 1); 
            //pc = (int *)*pc; 
        
        
        // branch if zero
        }        
        else if (i == BZ)  { 
            //pc = a ? pc + 1 : (int *)*pc; 
        
        
        // branch if not zero
        } 
        else if (i == BNZ) { 
            //pc = a ? (int *)*pc : pc + 1; 
        
        // enter subroutine
        } 
        else if (i == ENT) { 
            //*--sp = (int) bp; 
            //bp = sp; 
            //sp = sp - *pc++; 
        
        // stack adjust
        }     
        else if (i == ADJ) { 
            //sp = sp + *pc++; 
        
        // leave subroutine
        }    
        else if (i == LEV) { 
            //sp = bp; 
            //bp = (int *)*sp++; 
            //pc = (int *)*sp++; 
        
        // load int
        } 
        else if (i == LI) { 
            //a = *(int *)a; 
        
        
        // load char
        } 
        else if (i == LC) { 
            //a = *(char *)a; 
        
        
        // store int
        } 
        else if (i == SI) { 
            //*(int *)*sp++ = a; 
        
        // store char
        }   
        else if (i == SC) { 
            //a = *(char *)*sp++ = a; 
        
        
        // push
        } 
        else if (i == PSH) { 
            //*--sp = a; 
        
        } 
        else if (i == OR) { 
            //a = *sp++ |  a; 
        
        }
        else if (i == XOR) { 
            //a = *sp++ ^  a; 
        
        }
        else if (i == AND) { 
            //a = *sp++ &  a; 
        
        }
        else if (i == EQ)  { 
            //a = *sp++ == a; 
        
        }
        else if (i == NE) { 
            //a = *sp++ != a; 
        
        }
        else if (i == LT) { 
            //a = *sp++ <  a; 
        
        }
        else if (i == GT) { 
            //a = *sp++ >  a; 
        
        }
        else if (i == LE) { 
            //a = *sp++ <= a; 
        
        }
        else if (i == GE) { 
            //a = *sp++ >= a; 
        
        }
        else if (i == SHL) { 
            //a = *sp++ << a; 
        
        }
        else if (i == SHR) { 
           // a = *sp++ >> a; 
        
        }
        else if (i == ADD) { 
            //a = *sp++ +  a; 
        
        }
        else if (i == SUB) { 
            //a = *sp++ -  a; 
        
        }
        else if (i == MUL) { 
            //a = *sp++ *  a; 

        }
        else if (i == DIV) { 
            //a = *sp++ /  a; 
        
        }
        else if (i == MOD) { 
            //a = *sp++ %  a; 

        }
        else if (i == OPEN) { 
            //a = open ((char *)sp[1], *sp,0); 

        }
        else if (i == RUN) { 
            //a = open ((char *)sp[1], *sp,0);
            //a = gramado_system_call (900,(unsigned long)sp[1],0,0); 
            //waitpid (-1,&Wait_status,0); 
        
        }
        else if (i == READ) { 
            //a = read (sp[2], (char *)sp[1], *sp); 
        
        }
        else if (i == CLOS) { 
           //a = close (*sp); 
        
        }
        else if (i == PRTF) { 
            //t = sp + pc[1]; 
            //a = printf ((char *)t[-1], t[-2], t[-3], t[-4], t[-5], t[-6]); 
        
        }
        else if (i == MALC) { 
            //a = (int) malloc (*sp); 
        
        }
        else if (i == FREE) { 
            //free ((void *)*sp); 
        
        }
        else if (i == MSET) { 
            //a = (int) memset ((char *)sp[2], sp[1], *sp); 

        }
        else if (i == MCMP) { 
            //a = memcmp ((char *)sp[2], (char *)sp[1], *sp); 
        
        }
        else if (i == EXIT) { 
            //printf("exit(%d) cycle = %d\n", *sp, cycle); 
            //return *sp; 
        
        }
        else { 
            //printf ("unknown instruction = %d! cycle = %d\n", i, cycle); 
            return -1; 
        };
    
    }; // while
    //--
    */


    printf ("parse: done\n");
    return 0;
}




/*
 ***********************************
 * parserInit:
 *     Initializing parser.
 */

int parserInit (){
	
	register int i=0;
	
	
//#ifdef GRAMC_VERBOSE	
    printf ("parserInit:\n");
//#endif		
	
	//infile_size = 0;
	//outfile_size = 0;
	
    //stack support
	stack_flag = 0;
	stack_count = 0;
	stack_index = 0;


	
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
    
    program_header_address = 0;
    program_text_address = 1*100;
    program_data_address = 2*100;
    program_bss_address  = 3*100;	
	
	//...
	
	return 0;
}


int parser(){

    int Status = -1;
    
    
    gde_debug_print ("parser:\n");
    
    //initialize	
    Status = (int) parserInit();
    
    //parse it
    Status = (int) parse ();
    printf ("parser: parse() returned %d\n", Status); 
    
    return 0;
}

//
// End.
//


