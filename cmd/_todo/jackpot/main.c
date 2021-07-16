/*
 * # Jackpot Game #
 *
 * Portando para o sistema operacional Gramado 0.4
 * Portando para a linguagem C.
 * Original: Dev C++.
 * This version: Fred Nora.
 * 2018.
 */
 
 
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int  i, j, life, maxrand;
int c;


// String do número digitado.
char number[16]; 


void Start ();
void GetResults ();
int jackpot_main ();


//int jackpot_atoi (char * s);


void Start (){
	
    i = 0;
    j = 0;
    life = 0;
    maxrand = 6;
	
	time_t *time1;

	// The user has to select a difficutly level.
	
    printf ("Start: \n");
    printf ("Select difficulty mode:\n"); 
    printf ("1 : Easy (0-15)\n");
    printf ("2 : Medium (0-30)\n");
    printf ("3 : Difficult (0-50)\n");
    printf ("or type q to quit.\n\n");
    
	c = 30;
	
	
	// #importante
	// O input funcionou chamando com execve através do gdeshell.
    // pois execve prepara o input para o novo programa que vai rodar.	

	// read the user's choice.
	
	while (1)
	{
        c = (int) getchar ();
        
		if (c == -1){
			
			//printf("EOF reached! ?? \n");
		    //asm ("pause");				
		};
			
	    if ( c != -1 )
		{	
	        printf ("%c", c);	        
			goto selected;
		};
	};	
	
	
//Um grau de dificuldade foi selecionado.	
	
selected:

	// The random number will be between 0 and maxrand.
		
    switch (c){
		
        case '1' : 
		    maxrand = 15;  
            break;
        
		case '2' : 
		    maxrand = 30;
            break;
        
		case '3' : 
		    maxrand = 50;
            break;
            
        case 'Q':    
        case 'q':
            exit (0);
            break;
            
		default : 
		    maxrand = 15;
		    //exit(0);
            break;
    };

	// Number of lifes of the player.
    life = 5;         
    
	
	// init Rand() function.
	srand ( (unsigned int) time (time1) );
	
	// j get a random value between 0 and maxrand.
	j = rand() % maxrand;  
	
    GetResults ();
}


void GetResults (){
	
	// if player has no more life then he lose
    if ( life <= 0 )
    {	
        printf ("You lose !\n\n");
        Start ();
    }

	// #  Pedimos para digitar um número ... #
	printf ("\n\n");
	printf ("Type a number: \n");
	
	//isso coloca a string digitada em 'number'
	gets (number);
	
	//i = jackpot_atoi ( number );
	i = atoi ( number );
	
	
checkNumber:

    //printf("checkNumber={%d}\n",i);
	
	// if the user number isn't correct, restart
    if ( (i>maxrand) || (i<0) ) 
    {
		//?? check
        printf("Error : Number not between 0 and %d \n", maxrand );
        GetResults();
    };

    if (i == j)
    {
		// The user found the secret number
		
	    printf("\n");	
	    printf("################################################\n");
	      puts("################ YOU WIN ! #####################\n");
	    printf("################################################\n");
		printf("\n");
		
        Start ();
		
		//#todo:
        //Podemos criar uma solução mais elegante para finalizar.
    
	}else if (i>j){
        
		printf("Too BIG\n");
        
		// -1 to the user's "life"
		life = life - 1;    
        
		//#check.
		printf("Number of remaining life:  %d \n\n", life);
		
        GetResults ();
		
     }else if (i<j){
		 
        printf("Too SMALL\n");;
		
        life = life - 1;
        
		//#check.
		printf("Number of remaining life:  %d \n\n", life);
        
		GetResults ();
      };
	
	//Nothing.  
}


/*
int jackpot_atoi (char * s){
	
    int rv=0; 
    char sign = 0;

    // skip till we find either a digit or '+' or '-' 
	
    while (*s) 
	{
	    if (*s <= '9' && *s >= '0')
		    break;
	    if (*s == '-' || *s == '+') 
		    break;
	    s++;
    }; 	  

    if (*s == '-')
	    sign=1;

    //     sign = (*s == '-');
    if (*s == '-' || *s == '+') 
	    s++;

    while (*s && *s >= '0' && *s <= '9') 
	{
	    rv = (rv * 10) + (*s - '0');
        s++;
    };

    if (sign) return (-rv);
        else return (rv);
     
    //     return (sign ? -rv : rv);
}
*/



/*
 *******************************************
 * jackpot_main:
 *     Initialize the game.
 */

int jackpot_main (){
	
    // stdlib
	// inicializando o suporte a alocação dinâmica de memória.
	//stdio
	//inicializando o suporte ao fluxo padrão.
	
	//#cancelado. Porque o crt0.o faz isso.
	//libcInitRT ();
	//stdioInitialize ();		
	
    printf ("** Jackpot game **\n");
    printf ("The goal of this game is to guess a number. You will be ask to type\n");
    printf ("a number (you have 5 guess)\n");
    printf ("Jackpot will then tell you if this number is too big of too small compared to the secret number to find\n\n");
    
	Start ();
	
	return 0;
}

/*
 * main:
 *     Entry point. 
 */

// ??
// Qual janela tem o foco de entrada ?
// A disciplina de linha precisa disso para encontrar
// a thread que receberá mensagem.
	
int main ( int argc, char *argv[] ){

	int code = 0;
	
	printf ("\n");
	printf ("####################################################\n");
	  puts ("################## JackPot #########################\n");
	printf ("####################################################\n");
	printf ("\n");	
	
	
	code = (int) jackpot_main ();
	
	switch (code) 
	{
	    
        case 0:
            exit (0);
            break;	

		default:	
		    exit (code);
			break;	
	};
	
	return -1;
}



