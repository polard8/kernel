

#include <sys/types.h>   //for pid_t
//#include <unistd.h>      //for pid_t


/*
#ifndef __pid_t_defined
#define __pid_t_defined
typedef __pid_t pid_t;
#endif
*/


pid_t wait ( int *status );
pid_t waitpid (pid_t pid, int *status, int options); 


/*
 //BSD System Calls Manual        
 // wait, wait3, wait4, waitpid -- wait for process termination 
#include <sys/wait.h>

     pid_t wait(int *stat_loc);
     pid_t wait3(int *stat_loc, int options, struct rusage *rusage);
     pid_t wait4(pid_t pid, int *stat_loc, int options, struct rusage *rusage);
     pid_t waitpid(pid_t pid, int *stat_loc, int options);
*/


/*

https://www.dca.ufrn.br/~adelardo/cursos/DCA409/node36.html
    
	  int *status               // status descrevendo a morte do filho 

       pid_t wait(int *status)    // espera a morte de um filho 
       pid_t waitpid(pid_t pid, int *status, int options)	 

Valor de retorno: identificador do processo morto ou -1 em caso de erro. 
A função wait suspende a execução do processo até a morte de seu filho. 
Se o filho já estiver morto no instante da chamada da primitiva 
(caso de um processo zumbi, abordado mais a frente), a função retorna imediatamente.

??? refletindo
então wait faz uma chamada ao kernel e se encontrar o filho morto, ja retorna.
caso não encontre o filho morto então o kernel muda o status da thread e retorna da interrupção
isso fará com que a thread não rode mais apos uma interruoção do timer;
??

A função waitpid suspende a execução do processo até que o filho especificado pelo argumento 
pid tenha morrido. Se ele já estiver morto no momento da chamada, o comportamento é idêntico ao descrito anteriormente.

O valor do argumento pid pode ser:

< -1 : significando que o pai espera a morte de qualquer filho cujo o ID do grupo é igual so valor de pid;
-1 : significando que o pai espera a morte de qualquer filho;
0 : significando que o pai espera a morte de qualquer processo filho cujo ID do grupo é igual ao do processo chamado;
> 0 : significando que o pai espera a morte de um processo filho com um valor de ID exatamente igual a pid.


Se status é não nulo (NULL), wait e waitpid armazena a informação relativa a razão da morte do processo filho, sendo apontada pelo ponteiro status. Este valor pode ser avaliado com diversas macros que são listadas com o comando shell man 2 wait.

O código de retorno via status indica a morte do processo que pode ser devido uma:

uma chamada exit(), e neste caso, o byte à direita de status vale 0, e o byte à esquerda é o parâmetro passado a exit pelo filho;
uma recepção de um sinal fatal, e neste caso, o byte à direita de status é não nulo. Os sete primeiros bits deste byte contém o número do sinal que matou o filho.
*/




