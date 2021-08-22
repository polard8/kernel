/*
 * File: priority.c
 * 
 *    Priority support. 
 */


#include <kernel.h>


/*
 ******************************************
 * set_priority:
 *     Equilibra a prioridade da thread atual.
 *     @todo: Não é esse o nome apropriado para essa rotina.
 *            Criar scheduleriBalanceCurrentThreadPriority()
 */

// Equilibra a prioridade.
// #bugbug: Uma função com esse nome deveria ter um valor de entrada.

//#todo: int set_priority (int priority){

int set_priority (void){

    struct thread_d *Current; 


    Current = (void *) threadList[current_thread];

    if ( (void *) Current == NULL ){
        debug_print ("set_priority: Current\n");
        return (int) 1; 
    }

	// Nothing ?!

    set_thread_priority ( Current, PRIORITY_NORMAL);

    return 0; 
}


/*
 * KiSetPriority:
 *     Interface. 
 *     Faz alterações na prioridade de acordo com o status.
 */
 
int KiSetPriority (void)
{
	//#todo: Fazer alguma coisa aqui.

    return (int) set_priority();
}


/*
 * KiIncreasePriority:
 *     Aumenta a prioridade de uma processo
 *     
 */
int KiIncreasePriority (int pid)
{
    debug_print ("KiIncreasePriority: [TODO]\n");
    return 0;    //Nothing for now. 
}


/*
 **************************************
 * find_higher_priority:
 *     Encontra uma thread de maior prioridade entre as threads de 
 * estado READY.
 *     Essa rotina é usado após a preempção, onde uma thread de 
 * baixa prioridade para de executar, para que rode uma de 
 * maior prioridade.
 */
 
int find_higher_priority (void){

    //loop
    register int i=0;  // Counter

    unsigned long p=0;  // Priority
    
    int Current=0; 

    struct thread_d *t;
    


    // Only Idle? return.
    if ( UPProcessorBlock.threads_counter == 1 )
    {
		
		//#bugbug, 
		// Nã0 devemos determinar o valor da thread idle dessa forma.
		//tempos um ponteiro para a estrutura da thread idle.
		
	    //if (current_thread == 0)
		//{
			//return (int) next_thread;
		//}

		// #todo: 
		// E caso a única thread que está rodando não seja a thread idle??
		
		return (int) ____IDLE->tid;
    }


	// Find: Procura uma thread de maior prioridade, que o estado seja READY e 
	// que o contexto esteja salvo.

    for ( i=0; i < THREAD_COUNT_MAX; ++i )
    {
        //Pega na lista.
        t = (void *) threadList[i]; 
        
        if ( (void *) t != NULL )
        { 
		    if (t->used  != 1)    { continue; };
		    if (t->magic != 1234) { continue; };
		    if (t->state != READY){ continue; };

			// Pega a de maior prioridade.
            if (t->priority > p)
            { 
                p = t->priority; 
            }
            //Nothing.
        }
		//Nothing.
    };


	// Encontra a próxima thread a ser executada. Ela deve ter prioridade 
	// maior ou igual a "p". Dá duas voltas nos slots procurando.

    for ( i=0; i < (2*THREAD_COUNT_MAX); i++ )
    {
        Current++;

		//Circula.
        if (Current >= THREAD_COUNT_MAX)
        {
            Current = (int) 0;
        }

        t = (void *) threadList[Current];
        
        if ( (void *) t != NULL )
        {
	        // Done! 
	        // Encontramos uma thread de prioridade maior.
		    // A tarefa rodando de maior prioridade.  
            if ( (t->state == READY) && (t->priority >= p ) )
            {
                return (int) Current;
                //break;
            }
			//Nothing.
        }  
        // Nothing.
    };


	// Limites, overflow. 
	// Não encontrando nenhuma tarefa retorna o id da Idle. 

    if ( i >= (2*THREAD_COUNT_MAX) )
    {
        return (int) ____IDLE->tid;
    }

    return (int) ____IDLE->tid;
}


/*

 * KiFindHigherPriority:
 *     Interface para chamar a rotina de encontrar tarefa com maior 
 * prioridade.
 * Encontra uma tarefa de maior prioridade entre as 
 * threads de estado READY para que possa assumir o estado RUNNING.
 * Essa rotina é usada após a preempçao, onde uma thread 
 * de baixa prioridade para de executar para que rode 
 * uma de maior prioridade.
 */ 
 
int KiFindHigherPriority (void)
{
	// #todo:
	// Algo pode ser feito aqui.

    return (int) find_higher_priority(); 
}


//
//  End.
//


