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


//interna 
int parse_def (){
	
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



//interna 
int parse_var (){
	
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


//interna 
int parse_return (){
	
	int c;
	
	//printf("parse_var:\n");
	
	//pegaremos o tipo e a exp.
	
do_constant:

	c = yylex ();
	
	//identifier para a variável.
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
	
	
	
	int running = 1;
	size_t size = (size_t) strlen ( (const char *) stdin->_base );
	
	//steps;
	int State = 1;
	
	printf("\n");
	
	//#obs
	//Aqui podemos usar um while(running) até que se encontre o fim do arquivo.
	
	//for ( i=0; i<size; i++ )
	while (running == 1)
	{
	    //pega o char.
		//#todo: trocar c por TOKEN.
	    c = yylex ();
		
		//#debug
	    //printf("%c", c );
		
	    
		switch (State)
		{
			next:
			
			//################################
			// #State 1
			// Esperamos uma TOKENKEYWORD. (KWDEF KWVAR KWRETURN )
			// Esperamos um TOKENTYPE.
			//return não.
			// (var def ou int void ...)
			case 1:
				switch (c)
				{
					//TYPE
			        case TOKENTYPE:
			            id[ID_TYPE] = type_found;
				        printf("State1: TOKENTYPE={%s} line %d\n", real_token_buffer, lineno );
						//depois de um type vem um identificador.
						State = 2;
			            break;
						
					//KEYWORD.	
				    case TOKENKEYWORD:
					    //printf("line %d TOKENKEYWORD={%s} \n", lineno, real_token_buffer );
			    
				        //se a kw for 'def' chamamo parse_def() que retorna só quando 
				        //encontrar um '(', onde começará os argumentos.
				
				        if ( keyword_found == KWDEF )
				        {
					         printf("State1: TOKENKEYWORD={%s} KWDEF line %d  \n", real_token_buffer, lineno );
					
					        // parse deve retornar o '(' quando encontrá-lo.
					        c = parse_def();
					        if ( c == TOKENSEPARATOR )
					        {
						        //goto next;
					        }
					        printf("State1: TOKENKEYWORD KWDEF fail;");
					        exit(1); //while(1){}
					        break;
				        }
						
						
				        //e a kw var foi encontrada, chamaremos parse_var(),
				        //que retornará quando encontrar ';'.
				
				        if( keyword_found == KWVAR )
				        {
					        printf("State1: TOKENKEYWORD={%s} KWVAR line %d \n", real_token_buffer, lineno );
					        // parse deve retornar o ';' quando encontrá-lo.
					        c = parse_var();
				       	    if ( c == TOKENSEPARATOR )
					        {
						        //goto next;
					        }
					        printf("State1: TOKENKEYWORD KWVAR fail");
					        exit(1);//while(1){}
					        break;
				        }							
						break;

                    default:
					    printf("State1: default error\n");
						printf("State1: keyword expected on line %\n", lineno);
						exit(1);
                        break;					
				}
		        break;
				
			//################################
			// #State 2	
			// Esperamos um identificador, pos estamos logo após um tipo.
			//
			case 2:
			    switch (c)
				{
				    //identificador. (símbolo)
					case TOKENIDENTIFIER:
			            id[ID_TOKEN] = TOKENIDENTIFIER;
				        id[ID_STACK_OFFSET] = stack_index;
				        printf("State2: TOKENIDENTIFIER={%s} line %d\n", real_token_buffer, lineno );    
						//depois do identificador deve vir um '(' ou um '=';
						State = 3;
						break;		
                
				    default:
					    printf("State2: default Error.\n");
						printf("State2: expected identifier on line %.\n", lineno);
						exit(1);
					    break;
				};
                break;			
			
			//################################
			// #State 3	
            //	esperamos '(' ou '='
            //pois estamos após o identificador.			
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
        		
			//################################
			// #State 4	
			// esperamos um separador ')' para fechar ... ou algum conteúdo 
            // como um tipo e um simbolo e uma virgula.			
            case 4:
			    switch (c)
			    {
	
					// separadores (){}[],.;:? ...
			        case TOKENSEPARATOR:
			            printf("State4: TOKENSEPARATOR={%s} line %d \n", real_token_buffer, lineno );   
						//Se encontramos um separador ')' 
						//ent]ao esperaremos um separador '{'.
						State = 5;
						break;
						
					default:
					    printf("State4: default. Error \n");
						printf("State4: Expected ')' on line %d \n",lineno);
						exit(1);
					    break;					
				}
			    break;
				
			//################################
			// #State 5	
			// esperamos um '{'
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
				
			//################################
			// #State 6	
			// esperamos um '}' ou return 0; ou coisa assim.		
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
					        c = parse_return ();
					        printf ("\n");
							
							//esperávamos o separador ';', se não veio então falhou o parser.
							if ( c != TOKENSEPARATOR )
					        {
							    printf("State6: TOKENKEYWORD TOKENSEPARATOR fail");
                                exit(1);								
					        }
				        }		
					    break;

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
				
			//################################
			// #State 7
			//esperamos um ';' para terminar a função.
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
				
 
		    default:
			    printf("State default: Error.");
				exit(1); 
 
	




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
	printf("\n");
	printf("stdin_base: %s\n",stdin->_base);
	printf("number of lines: %d \n",lineno);
	//...
	
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

