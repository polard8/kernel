/*
 * File: tasks.c
 *
 * Descrição:
 *     Algumas Threads em ring 0. Chamadas de task.
 *     Saão usadas na configuração da TSS em headlib.s.
 *     PB - Processos incluídos no Kernel Base.
 *     Faz parte do Process Manager, parte fundamental do Kernel Base.
 *    OBS: @todo: Todas as rotinas abaixo podem ser threads de um mesmo processo
 *                do tipo PB, ring 0.
 *
 * Obs: O conceito de tasks está meio bagunçado aqui. Nesse momento, task sigifica
 * uma pequena thread em ring 0 escrita dentro do kernel base.
 *
 * Versão: 1.0, 2015.
 */


#include <kernel.h>


/*
 * Threads em kernel mode incluída no kernel base. Essa threads deverão pertencer ao 
 * ao processo Kernel.
 */
 
 
 
void task0(){ 	
    while(1){}
};

void task1(){ 	
    while(1){}
};

void task2(){ 	
    while(1){}
};

void task3(){
    while(1){}
};

//
// End.
//

