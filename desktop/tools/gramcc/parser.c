/*
 * File: parser.c
 *
 * 2018 - Created by Fred Nora.
 */
 
 
#include <types.h>

#include "heap.h"
#include "api.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "table.h"
#include "lexer.h"
#include "parser.h"
#include "gramcc.h"


int parse_function ( int token );
int parse_return ( int token );

//int parse_def (int token );    //não pertence a linguagem C.
//int parse_var ( int token );   //não pertence a linguagem C.
//...



//#test 
//não pertence a linguagem C.
//interna 

/*
int parse_def (int token )
{
	
	int c;
	
	//printf("parse_def:\n");
	
    c = yylex ();
	
	//se for um tipo, pois o modificador foi negligenciado.
	if ( c == TOKENTYPE )
	{
		printf("line %d TOKENTYPE={%s} \n", lineno, real_token_buffer );
		goto do_id;
	}else{
		
		//se não for um tipo precisa ser um modificador.
		//O modificador é uma palavra reservada.
		if ( c == TOKENKEYWORD ){
			printf("line %d (modifier) TOKENKEYWORD={%s} \n", lineno, 
			    real_token_buffer );
		}
		//goto do_type;	
	};
	
do_type:

    c = yylex ();
    
	//esperamso que seja um tipo, se não for algo deu errado,
	//ou ainda podemos usar o tipo padrão para fuções que será 'int'
	
	if( c == TOKENTYPE )
	{
		printf("line %d TOKENTYPE={%s} \n", lineno, real_token_buffer );
		
	}else{
	    //podemos usar o tipo padrão.
        printf("line %d TOKENTYPE={DEFAULT} \n", lineno );
         		
	}; 
	
do_id:	
    c = yylex ();
	if( c == TOKENIDENTIFIER)
	{
	    printf("line %d TOKENIDENTIFIER={%s} \n", lineno, real_token_buffer );	
	}else{
			//falhou.
			printf("parse_def: do_id fail");
			//exit(1);
			while(1){}		
	}
	
    //...
checkopen:
     c = yylex ();
    if( c == TOKENSEPARATOR )
    {
	    if( strncmp( (char *) real_token_buffer, "(", 1 ) == 0  )
        {
			//deu certo.
			// printf("line %d TOKENSEPARATOR={%s} \n", lineno, real_token_buffer );
		    goto done;
		}else{
			//falhou.
			printf("parse_def: checkopen fail");
			//exit(1);
			while(1){}
		};			
	}

done:	
    //printf("parse_def: done \n");
	return (int) c;
};
*/



//#test 
//não pertence a linguagem C.
//interna 
/*
int parse_var ( int token ){
	
	int c;
	
	//printf("parse_var:\n");
	
    c = yylex ();
	
	//se for um tipo, pois o modificador foi negligenciado.
	if( c == TOKENTYPE )
	{
		printf("line %d TOKENTYPE={%s} \n", lineno, real_token_buffer );
		goto do_id;
	}else{
		
		//se não for um tipo precisa ser um modificador.
		//O modificador é uma palavra reservada.
		if( c == TOKENKEYWORD )
	    {
			printf("line %d (modifier) TOKENKEYWORD={%s} \n", lineno, real_token_buffer );
             			
		}
		//goto do_type;	
	};	
	
do_type:
    c = yylex ();
    //esperamso que seja um tipo, se não for algo deu errado,
	//ou ainda podemos usar o tipo padrão para fuções que será 'int'
	if( c == TOKENTYPE )
	{
		printf("line %d TOKENTYPE={%s} \n", lineno, real_token_buffer );
		
	}else{
	    //podemos usar o tipo padrão.
        printf("line %d TOKENTYPE={DEFAULT} \n", lineno );
         		
	}; 
	
do_id:
	c = yylex ();
	//identifier para a variável.
	if( c == TOKENIDENTIFIER)
	{
	    printf("line %d TOKENIDENTIFIER={%s} \n", lineno, real_token_buffer );	
	}else{
			//falhou.
			printf("parse_var: do_id fail");
			//exit(1);
			while(1){}		
	};
	
	//## todo
	//aqui esperamos que a variável possa ter sido inicializada com uma expressão 
	// ou com uma constante.
	
//do_exp:
	//@todo
	
do_separator:
    c = yylex ();
    
	//separador ';'
	if( c == TOKENSEPARATOR )
    {
	    if( strncmp( (char *) real_token_buffer, ";", 1 ) == 0  )
        {
			//deu certo.
			//printf("line %d TOKENSEPARATOR={%s} \n", lineno, real_token_buffer );
		    goto done;
		}else{
			//falhou.
			printf("parse_var: do_separator separador fail");
			//exit(1);
			while(1){}
		};	
		
	}else{
			//falhou.
			printf("parse_var: do_separator expected separator ;");
			//exit(1);
			while(1){}		
	};	
	
done:	
    //printf("parse_var: done \n");
    return c;	
};
*/


int parse_function ( int token )
{
	int c;
	
	int running = 1;
	int State = 1;
	
	
	//debug
	printf("parse_function: Initializing ...\n");	
	
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
	
	
	//debug
	printf("parse_return: Initializing ...\n");	
	
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
						//ok;
						printf("parse_return: State1 TOKENCONSTANT={%s} line %d\n", real_token_buffer, lineno );

						strcat( outfile,"  mov eax, 0x");
						strcat( outfile,real_token_buffer);
						strcat( outfile,"\n  ret \n\n");
                        //strcat( outfile,"");							
						
						//Se não temos um parêntese aberto então vamos para o proximo
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
			                //deu certo.
			                printf("parse_return: State2 do_separator TOKENSEPARATOR={%s} line %d \n", real_token_buffer, lineno );
		                    
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
	

	if( c == TOKENCONSTANT)
	{
	    printf("parse_return: do_constant TOKENCONSTANT={%s} line %d\n", real_token_buffer, lineno );	
	
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
			//deu certo.
			printf("parse_return: do_separator TOKENSEPARATOR={%s} line %d \n", real_token_buffer, lineno );
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
		
	    //statement classes
		
		switch (State)
		{
            //
			//  ## MODIFIER,  TYPE and SEPARATOR ##
			//
						
			//################################
			// #State 1
			// Esperamos um TOKENTYPE.
			case 1:
			    printf("<1> ");
				switch (c)
				{
	                case TOKENMODIFIER:
						//continua pois precisamos pegar um tipo.
						//#bugbug ??mas e se o modificar vir seguido de um simbolo ???
						printf("State1: TOKENMODIFIER={%s} line %d\n", real_token_buffer, lineno );
						State = 1;
						//goto again;
						break;
					
					//TYPE
					// >>> peekChar=) significa marcação de tipagem.
					// >>> peekSymbol=symbol  significa declaração de variável ou função.
			        case TOKENTYPE:
			            printf("State1: TOKENTYPE={%s} line %d\n", real_token_buffer, lineno );
						id[ID_TYPE] = type_found;
				        
						//depois de um type vem um identificador.
						State = 2;
			            break;
						
					case TOKENSEPARATOR:
					     printf("State1: TOKENSEPARATOR={%s} line %d\n", real_token_buffer, lineno );
						 
					    //fechando UM parênteses, provavelmente sem nada dentro.
					    if ( strncmp( (char *) real_token_buffer, ")", 1 ) == 0  )
						{
						    if ( parentheses_inside > 0 )
							{
								printf("\n[/PAR]\n");
                                parentheses_inside--;
                                State = 1;
								break;
								//State++;
                                //goto again; 								
							};
						}
                        //fechando UM corpo de função. 					
				        if ( strncmp( (char *) real_token_buffer, "}", 1 ) == 0  )
                        {
						    if ( braces_inside > 0 )
							{
								printf("\n[/BRACE]\n");
                                braces_inside--;
                                State = 1;
								break;
								//State++;
                                //goto again; 								
							};							
						}
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
                         
						//EOF 
						if( c = TOKENEOF )
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
			            
						id[ID_TOKEN] = TOKENIDENTIFIER;
				        id[ID_STACK_OFFSET] = stack_index;
				        printf("State2: TOKENIDENTIFIER={%s} line %d\n", real_token_buffer, lineno );    
						
						
                        //salva o símbolo. #isso funciona.						
						sprintf ( save_symbol, real_token_buffer );
						
						//?? não sabemos se real_token_buffer é código ou dados ?? 
						
						
                        c = yylex ();
						
						//printf("test={%s} line %d\n", real_token_buffer, lineno ); 
						
						//: para label 
                        //( para função 
                        //; para declaração de variável.
                        //, para sequencia de variável.
                        //... 						
						if ( c == TOKENSEPARATOR )
						{
							//printf("sep \n");
							
						    //: label
							if( strncmp ( (char *) real_token_buffer, ":", 1 ) == 0  )
                            {
						        //tentando mandar alguma coisa para o arquivo de output 
						        //pra ter o que salvar, pra construir o assembly file;	
						        strcat( outfile,"\n segment .text \n");
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
								//incrementamos
								//pois podemos estar no primeiro, no segundo etc ...
								parentheses_inside++;
								printf ("\n[PAR]\n");  //debug par open
								
								//#test
								//peekChar = c;
								
						        //tentando mandar alguma coisa para o arquivo de output 
						        //pra ter o que salvar, pra construir o assembly file;	
						        strcat( outfile,"\n segment .text \n");
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
								//se não tem parênteses aberto.
								if ( parentheses_inside < 1 )
								{
									printf("state2: Error closing parentheses in line %d ", lineno);
									exit(1);
								}
								
								//fechamos um dos parênteses.
								parentheses_inside--;
								printf ("\n[/PAR]\n");  //debug par close
								
							    //é bss porque não foi inicializada.
								strcat( outfile,"\n segment .bss \n");
						        strcat( outfile,"_");
						        strcat( outfile,save_symbol);
						        strcat( outfile,":\n");								
						        
								//?? depois de ) podemos ter o corpo da função.
								//ou outra coisa caso estivermos parentese aberto.
								
								//peek next
								c = yylex ();
								
								//entramos no corpo da função.
								if ( strncmp( (char *) real_token_buffer, "{", 1 ) == 0  )
								{
									printf("State2: separator={%s} line %d\n", real_token_buffer, lineno );  
									 
									braces_inside++;
								    printf ("\n[BRACE]\n");  //debug par close
									//isso vai para o 1 onde procura-se por modificadores e tipos,
									//mas se estivermos com o corpo da função aberto ele avançará para o próximo state.
									State = 1;
								}	
									
							    break;
						    }									

						    //; var
							if ( strncmp( (char *) real_token_buffer, ";", 1 ) == 0  )
                            {
						        //tentando mandar alguma coisa para o arquivo de output 
						        //pra ter o que salvar, pra construir o assembly file;	
						        
								//é bss porque não foi inicializada.
								strcat( outfile,"\n segment .bss \n");
						        strcat( outfile,"_");
						        strcat( outfile,save_symbol);
						        strcat( outfile,":\n");
								
								//recomeçar, vai que tem mais variável...
								State = 1;
								break;
							}
							
							
						    //, var (listando) tirando da pilha
							if ( strncmp( (char *) real_token_buffer, ",", 1 ) == 0  )
                            {
						        //tentando mandar alguma coisa para o arquivo de output 
						        //pra ter o que salvar, pra construir o assembly file;	
						        
								//é bss porque não foi inicializada.
								strcat( outfile,"\n segment .bss \n");
						        strcat( outfile,"_");
						        strcat( outfile,save_symbol);
						        strcat( outfile,":\n");
								
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
					    printf("line %d TOKENKEYWORD={%s} \n", lineno, real_token_buffer );
						
						// # return #
						//return. Chamaremos o tratador do stmt parse_return() 
				        if( keyword_found == KWRETURN )
				        {
					        printf("State3: TOKENKEYWORD={%s} KWRETURN line %d  \n", real_token_buffer, lineno );
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

						
				        //se a kw for 'def' chamamo parse_def() que retorna só quando 
				        //encontrar um '(', onde começará os argumentos.
                        /*						
				        if ( keyword_found == KWDEF )
				        {
					         printf("State1: TOKENKEYWORD={%s} KWDEF line %d  \n", real_token_buffer, lineno );
					
					        // parse deve retornar o '(' quando encontrá-lo.
					        c = parse_def (TOKENKEYWORD);
					        if ( c == TOKENSEPARATOR )
					        {
						        //goto next;
					        }
					        printf("State1: TOKENKEYWORD KWDEF fail;");
					        exit(1); //while(1){}
					        break;
				        }
						*/
						
				        //e a kw var foi encontrada, chamaremos parse_var(),
				        //que retornará quando encontrar ';'.
				        /* 
				        if( keyword_found == KWVAR )
				        {
					        printf("State1: TOKENKEYWORD={%s} KWVAR line %d \n", real_token_buffer, lineno );
					        // parse deve retornar o ';' quando encontrá-lo.
					        c = parse_var (TOKENKEYWORD);
				       	    if ( c == TOKENSEPARATOR )
					        {
						        //goto next;
					        }
					        printf("State1: TOKENKEYWORD KWVAR fail");
					        exit(1);//while(1){}
					        break;
				        }
                        */						
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
					    printf("State3: keyword default");
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
			    printf("<default>State default: Error.\n");
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
 
	




	    };//State	
		
      		
		size--;
		
		//sai do while
        if (size <= 0)
            running = 0;		
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

	printf("\n OUTPUT: \n");
	printf("%s\n",outfile);
	printf("number of lines: %d \n",lineno);
	
hang:	

	printf("parse: *hang");
	    
		while (1){
			
			asm ("pause");
		}
		
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
	
	//id support
	
	
	for ( i=0; i<512; i++ )
		stack[i] = 0;
	
    
	for ( i=0; i<8; i++ )
		id[i] = 0;

	
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

