/*
 * reboot command for Gramado.
 */



// rtl
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <time.h>
#include <stdbool.h>



// ??
// Qual janela tem o foco de entrada ?
// A disciplina de linha precisa disso para encontrar
// a thread que receberá mensagem.
	
int main ( int argc, char *argv[] ){

    int code = 0;
    char *env_string;

    printf ("\n");
    printf ("####################################################\n");
      puts ("################### Reboot #########################\n");
    printf ("####################################################\n");
    printf ("\n");

    /*
     // OK. Isso funcionou.
    bool pode;
    pode = true;
    if ( pode == 1 )
       printf("YES\n");
    
    pode = false;
    if ( pode == 0 )
       printf("NO\n");
   
    while(1){}
    */   


    env_string = (char *) getenv ("USER");
    printf(">>> Bye %s! :) \n", env_string);
    //while(1);


	// #todo
	// salvamentos.
	// fechar os processos e efetuar as rotinas
	// de reboot do kernel.

    printf ("#todo: reboot the system ...\n");


    // #todo
    // Usar uma função da libc.

    while (1){
        gramado_system_call ( 110, 0, 0, 0 );
    };


    return -1;
}



 
