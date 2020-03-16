/*
 * File: preempt.c 
 * 
 *    Preemption support. 
 */


#include <kernel.h>


/*
 *************************************
 * preempt:
 *     Preempt current.
 *     Uma thread que está rodando será interrompida para dar lugar pra 
 * outra thread com prioridade maior.
 *
 * #todo: 
 * Se estiver running, torna ready. (preempt).
 * Preempt current task if we can. 
 * Find Higher priority thread if we can.
 */
 
// #todo
// Talvez o retorno 'int' seja bom aqui.
 
void preempt (void){

    int Current;
    int Next = 0;

    struct thread_d *t; 
	//...

	// Preempt current.

    Current = (int) current_thread;


    t = (void *) threadList[Current];

    if ( (void *) t == NULL )
    {
		// #bugbug: 
		// Rever isso.
		
		current_thread = (int) next_thread;
        return;

    } else {

        if ( t->used != 1 || t->magic != 1234 )
        {
			// #bugbug: 
			// Rever isso.
		    
			current_thread = (int) next_thread;
            return;
        }
	    
		//Checa se a tarefa atual pode entrar sofrer preempção, flag=1.
		
		if (t->preempted == 1)
		{
		    
			// Colocando ela numa fila de espera.
			// Se não for a idle e a prioridade for baixa.

			//#bugbug: rever isso.
			//Pois estamos determinando que a idle é a thread 0.

            if ( t->tid != 0 && t->priority == PRIORITY_LOW )
            {
                t->state = READY;  
            }
            //Nothing.
        };
		//Nothing.
    };


	// Next 
	// Procura uma de maior prioridade. 
	// Não havendo usa a Idle.

    Next = (int) find_higher_priority ();

    if (Next <= 0)
    {
        current_thread = (int) next_thread;
        return;
    }


	//Dentro do limite.
	
	if (Next > 0 && Next < THREAD_COUNT_MAX )
	{
	    current_thread = (int) Next;
	}


	// #bugbug:
	// E se Next for inválida. Poderíamos checar aqui mesmo.
}


//
// End.
//





