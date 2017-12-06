/*
 * Arquivo: tstack.c
 *
 * Descrição:
 *     Thread Stack routines.
 *     Faz parte do Process Manager, 
 *     parte fundamental do Kernel Base.
 *
 * Versão 1.0, 2015.
 */


#include <kernel.h>


/*
 * GetThreadStackStart:
 *     Obtem o valor início da Pilha.
 *
 */
unsigned long GetThreadStackStart(struct thread_d *thread)
{
    if( (void*) thread == NULL ){
        return (unsigned long) 0;        
	};
	
	// Nothing for now.
    
done:
	return (unsigned long) thread->Stack;
};


//
//fim.
//

