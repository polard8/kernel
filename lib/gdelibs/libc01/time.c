/*
 * File: time.c 
 *
 * 2018 - Created by Fred Nora.
 */
 

#include <time.h>
#include <types.h> 

//system calls.
#include <stubs/gramado.h> 

/*
 * time_system_call:
 *     Protótipo de função interna. #encapsulada
 *     As funções padrão de stdio chamarão os recursos do
 * kernel atravéz dessa rotina.
 *     System call usada pelo módulo . 
 *     Interrupção de sistema, número 200, chama vários serviços do Kernel 
 * com a mesma interrupção.
 *     Essa é a chamada mais simples.
 *
 * Argumentos:
 *    eax = arg1, o Número do serviço.
 *    ebx = arg2. 
 *    ecx = arg3.
 *    edx = arg4.
 */

/*
void *time_system_call ( unsigned long ax, 
                         unsigned long bx, 
				         unsigned long cx, 
				         unsigned long dx );
*/

						 
						 
// time 
// #obs: O que representa esse retorno ?
// Isso funciona.						 
time_t time (time_t *timer){
	
	time_t Ret;
	
	//system call. (224) get time
	
	//Ret = (time_t) time_system_call ( 224, 0, 0, 0 );
	
	Ret = (time_t) gramado_system_call ( 224, 0, 0, 0 );
	
    *timer = Ret;

    return (time_t) Ret;	
};


/*
 *****************************************************************************
 * time_system_call:
 *     System call usada pelo módulo stdio.  
 *     Função interna. 
 *     As funções padrão de stdio chamarão recursos do kernel atravéz dessa 
 * rotina.
 *     Interrupção de sistema, número 200, personalizada para stdio.
 *     Chama vários serviços do Kernel com a mesma interrupção.
 *     Essa é a chamada mais simples.
 *
 * Argumentos:
 *    eax = arg1, o Número do serviço.
 *    ebx = arg2. 
 *    ecx = arg3.
 *    edx = arg4.
 */
/*
void *time_system_call ( unsigned long ax, 
                         unsigned long bx, 
				         unsigned long cx, 
				         unsigned long dx )
{
    int Ret = 0;	
	
    //System interrupt. 	
	
	asm volatile (" int %1 \n"
		           : "=a"(Ret)	
		           : "i"(0x80), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );
				   
	return (void *) Ret; 
};
*/




