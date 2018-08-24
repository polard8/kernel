/*
 * File: tstack.c
 *
 * Descrição:
 *     Thread Stack routines.
 *     Faz parte do Process Manager, 
 *     parte fundamental do Kernel Base.
 *
 * History:
 *     2015 - Created by Fred Nora.
 */


#include <kernel.h>


/*
 ************************************************
 * GetThreadStackStart:
 *     Obtem o valor início da Pilha.
 *     OUT: 0 = error.
 */
unsigned long 
GetThreadStackStart( struct thread_d *thread )
{
    if( (void *) thread == NULL )
	{
        return (unsigned long) 0;        
	};
	
	// Nothing for now.
    
done:
	return (unsigned long) thread->Stack;
};


//
// End.
//

