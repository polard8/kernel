
//priority support.

#include <kernel.h>


/*
 *********************************************************
 * set_priority:
 *     Equilibra a prioridade da thread atual.
 *     @todo: Não é esse o nome apropriado para essa rotina.
 *            Criar scheduleriBalanceCurrentThreadPriority()
 */

int set_priority (){
	
    struct thread_d *Current; 
	
	Current = (void *) threadList[current_thread];
    
	if ( (void *) Current == NULL ){
	    return (int) 1;    //?? fail.
    }
	
	// Nothing ?!
	
    set_thread_priority ( Current, PRIORITY_NORMAL);
    
	return (int) 0; 
}

/*
 * KiSetPriority:
 *     Interface. 
 *     Faz alterações na prioridade de acordo com o status.
 */
 
int KiSetPriority (){
	
	//#todo: Fazer alguma coisa aqui.
	
	return (int) set_priority ();
}


/*
 * KiIncreasePriority:
 *     Aumenta a prioridade de uma processo
 *     
 */
int KiIncreasePriority (int pid){
	
	return (int) 0;    //Nothing for now. 
};


/*
 *********************************************************************
 * find_higher_priority:
 *     Encontra uma thread de maior prioridade entre as threads de 
 * estado READY.
 *     Essa rotina é usado após a preempção, onde uma thread de 
 * baixa prioridade para de executar, para que rode uma de maior 
 * prioridade.
 *
 */
 
int find_higher_priority (){
	
	int i;              //Contador.
	unsigned long p;    //Prioridade.	
    int Current;     
    struct thread_d *t;  	
	
	//Only Idle? return.
	
	if ( ProcessorBlock.threads_counter == 1 )
	{
		//#bugbug, Nã devemos determinar o valor da thread idle dessa forma.
		//tempos um ponteiro para a estrutura da thread idle.
		
	    if (current_thread == 0)
		{
			return (int) next_thread;
		}
		
		//@todo: E caso a única thread que está rodando não seja a thread idle??
	};	
	
	
	
	// Find: Procura uma thread de maior prioridade, que o estado seja READY e 
	// que o contexto esteja salvo.
	
	for ( i=0; i < THREAD_COUNT_MAX; i++ )
	{
        //Pega na lista.		
       	t = (void *) threadList[i];     		
        
		if ( (void *) t != NULL )
		{ 
		    if (t->used  != 1){ continue; };
		    if (t->magic != 1234){ continue; };
		    if (t->state != READY){ continue; };		
		    
			//Pega a de maior prioridade.
			if (t->priority > p)
			{ 
			    p = t->priority; 
			};
			
            //Nothing.			
		};
		//Nothing.
	};

	// Encontra a próxima thread a ser executada. Ela deve ter prioridade 
	// maior ou igual a "p". Dá duas voltas nos slots procurando.
	
	for ( i=0; i < (2*THREAD_COUNT_MAX); i++ )
	{
    	Current++;
		
		//Circula.
		if (Current >= THREAD_COUNT_MAX){
			Current = (int) 0;
		}
	
		t = (void *) threadList[Current];
        
		if ( (void *) t != NULL )
        {
		    //A tarefa rodando de maior prioridade.  
            if ( (t->state == READY) && (t->priority >= p ) ){
			    break;
			}
			//Nothing.
        }	  
        //Nothing.		
	};

	
	// Limites, overflow. 
	// Não encontrando nenhuma tarefa retorna o id da Idle. 
	
	if ( i >= (2*THREAD_COUNT_MAX) )
	{
        return (int) next_thread;			
	};
	
	// Nothing ?!
	
	// Done! 
	// Encontramos uma tarefa de prioridade maior.

    return (int) Current;
};

/*
 *************************************************
 * KiFindHigherPriority:
 *     Interface para chamar a rotina de encontrar 
 * tarefa com maior prioridade.
 * Encontra uma tarefa de maior prioridade entre as 
 * threads de estado READY para que possa assumir o 
 * estado RUNNING.
 * Essa rotina é usada após a preempçao, onde uma thread 
 * de baixa prioridade para de executar para que rode 
 * uma de maior prioridade.
 */ 
 
int KiFindHigherPriority (){
	
	// #todo:
	// Algo pode ser feito aqui.
	
    return (int) find_higher_priority (); 
}; 
 





