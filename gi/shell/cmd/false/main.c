/*
 * Fle: main.c
 * 
 * return false
 */


#include <types.h>
#include <stdio.h> 
#include <stdlib.h>
//#include <unistd.h> 
 

void cleanPrompt (){

    int i;

	// Linpando o buffer de entrada.
	
    for ( i=0; i<PROMPT_MAX_DEFAULT; i++ ){
        prompt[i] = (char) '\0';
    }


    prompt[0] = (char) '\0';
    prompt_pos = 0;
    prompt_status = 0;
    prompt_max = PROMPT_MAX_DEFAULT;  
}


char String[] = "This is a string in ring3\n";

char __buffer[1024]; 
 
int main ( int argc, char *argv[] )
{

    /*
    struct sigaction act;
    
    memset(&act, 0, sizeof(act));
    act.sa_flags = SA_NOCLDWAIT;
    act.sa_handler = SIG_IGN;
    
    int rc = sigaction(SIGCHLD, &act, nullptr);
    if (rc < 0) {
        
        //#bugbug: perror está usando estrutura em ring3.
        //perror("sigaction");
        
        return 1;
    }
    */


	// #bugbug
	// The client process has the same PID of the father.
	// printf ("false.bin: PID %d \n", getpid() );
    
    //printf ("Hello, this is false.bin \n");
    
    size_t len;
    
    
    // ok.
    /*
    len = strlen( (const char *) String );
    
    //imprime uma string usando a rotina em ring0, mas a string está em ring3.
    //IN: string, console id, len
    gramado_system_call ( 66, (unsigned long) String, 0, len );
    */
    
    
    // ok.
    /*    
    sprintf (__buffer, "My new string in ring3\n" );
    len = strlen( (const char *) __buffer );    
    gramado_system_call ( 66, (unsigned long) __buffer, 0, len );    
    */
    
    /*
    char *p;
    int i;
    int c = 'X';
    
    p = &__buffer[0];
    
    // no limite do buffer,
    for(i=0; i<8; i++)
    {
        sprintf (p, "%c", (int) c );
        p++;
    }    
    len = strlen( (const char *) __buffer );    
    gramado_system_call ( 66, (unsigned long) __buffer, 0, len );    
    */
    
    
    //ok
    /*
    //testing prompt[]
    cleanPrompt ();
    int i;
    for(i=0; i<8; i++)
    {
        input ('x');
    }
    input ('\0'); 
    len = strlen( (const char *) prompt );  
    gramado_system_call ( 66, (unsigned long) prompt, 0, len );        
    */
    
    
    // testando rotinas de prompt print
    
    /*
    //prompt_clean();
    prompt_putchar ('c',0);
    prompt_putchar ('o',0);
    prompt_putchar ('n',0);
    prompt_putchar ('0',0);    
    prompt_flush(0);
    */
    
    //isso funcionou, imprimiu em lugar diferente do con0;
    /*
    prompt_putchar ('c',1);
    prompt_putchar ('o',1);
    prompt_putchar ('n',1);
    prompt_putchar ('1',1);    
    prompt_flush(1);
    */
    
    
    //printf ("Testando printf em false.bin usando prompt\n again\n");
    
    
    
    // #test
    // testando a inicialização da biblioteca.
    // escrevendo em stdout
    
    //printf ("false.bin: hi!\n");
    //fprintf ( stdout, "Hello from false.bin \n");
    //printf ("false.bin: bye!\n");



    //IN: console number, buf, count
    //write_VC ( 0, __buffer, 64 );

   
    //printf ("This is false.bin. Returning 0.\n");
    return 0;  //false
}




//
// End.
//


