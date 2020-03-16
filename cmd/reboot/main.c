/*
 * reboot command for Gramado.
 */
 
 
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <time.h>



// ??
// Qual janela tem o foco de entrada ?
// A disciplina de linha precisa disso para encontrar
// a thread que receberá mensagem.
	
int main ( int argc, char *argv[] ){

    int code = 0;

    printf ("\n");
    printf ("####################################################\n");
      puts ("################### Reboot #########################\n");
    printf ("####################################################\n");
    printf ("\n");



    char *env_string;
       
    env_string = (char *) getenv ("USER");
    printf(">>> Bye %s! :) \n", env_string);



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



 
