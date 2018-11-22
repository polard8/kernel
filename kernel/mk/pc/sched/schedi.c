/*
 * File: schedi.c
 *
 * Descrição:
 *     Scheduler (Internal).
 *     Chama rotinas de scheduler dentro do kernel base. (internal).
 *     Faz parte do Process Manager, parte fundamental do Kernel Base.
 *     Rotinas de apoio ao módulo scheduler.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - More basic functions.
 *     2018 - More basic functions.
 *     //...
 */


#include <kernel.h>


//bloqueia por um motivo
void block_for_a_reason (int tid, int reason)
{
	struct thread_d *t;
	
    if ( tid < 0 ||
         tid >= THREAD_COUNT_MAX )
	{
		return;
	    //goto fail;		
	} 
	
	if( reason < 0 ||
	    reason >= 8 )
	{
		return;
	    //goto fail;		
	} 	
	
	//thread
	t = (struct thread_d *) threadList[tid];
	
	if ( (void *) t == NULL )
	{	
        return;
		//goto fail;
		
	} else {
		
		if ( t->used == 1 && t->magic == 1234 )
		{
			t->wait_reason[reason] = 1;
	        do_thread_sleeping (tid);		
		}	
	
	};
	
    	
};

 

//acordar uma determinada thread se ela estiver 
//esperando por um evento desse tipo.
//uma outra função pode fazer um loop acordando 
//todas as threads que esperam pelo memso motivo.

int wakeup_thread_reason ( int tid, int reason ){
	
	struct thread_d *t;
	
    if ( tid < 0 ||
         tid >= THREAD_COUNT_MAX )
	{
	    goto fail;		
	} 
	
	if( reason < 0 ||
	    reason >= 8 )
	{
	    goto fail;		
	} 
	
	//thread
	t = (struct thread_d *) threadList[tid];
	
	if ( (void *) t == NULL )
	{	
		goto fail;
		
	} else {
		
		if ( t->used != 1 || t->magic != 1234 )
		{
			goto fail;
		}
		
		// OK.
		
		if ( t->wait_reason[reason] != 1 )
		{
		    
			goto fail;
		
		} else {
			
            //ok 
			
			switch (reason)
			{
				//Esperando um processo morrer. Mas qual ??
				case EVENT_WAIT4PID:
				    //se o processo que acabamos de fechar for o mesmo que 
					//a thread estava esperando.
					if ( current_dead_process > 0 && 
					     current_dead_process == t->wait4pid )
					{
					    t->wait_reason[reason] = 0;	
					    KiDoThreadRunning (tid);
					}
					break;
					
				//Esperando uma thread morrer. Mas qual ??
				case EVENT_WAIT4TID:
				    //se a thread que acabamos de fechar for a mesma que 
					//a thread estava esperando.				
					if ( current_dead_thread > 0 && 
					     current_dead_thread == t->wait4tid )
					{
					    t->wait_reason[reason] = 0;	
					    KiDoThreadRunning (tid);
					}
					break;
			    
                // ...				
			}
			
            goto done;
		}
		
		//nothing
	};
	
fail:
    return (int) 1;	
done:
    return (int) 0;	
};




// Acorda todas as threads da lista que estão esperando por 
// evento de determinado tipo.

int wakeup_scan_thread_reason ( int reason ){
	
    int i;
	
	if ( reason < 0 ||
	     reason >= 8 )
	{
	    goto fail;		
	} 
	
	for ( i=0; i<THREAD_COUNT_MAX; i++ )
	{
        wakeup_thread_reason ( i, reason );		    	
	}
	
	
	switch (reason)
	{
		//já acordamos todas as threads que esperavam por essa razão.
		//podemos sinalizar que não há mais nenhum processo morto recentemente.
		case EVENT_WAIT4PID:
			current_dead_process = 0;
			break;
					
		//já acordamos todas as threads que esperavam por essa razão.
		//podemos sinalizar que não há mais nenhuma thread morta recentemente.
		case EVENT_WAIT4TID:
    		current_dead_thread = 0;
			break;
			    
                // ...				
	};	
	
done:
    return (int) 0;		
fail:
    return (int) 1;	
};


/*
 * KiIncreasePriority:
 *     Aumenta a prioridade de uma processo
 *     
 */
int KiIncreasePriority (int pid){
	
	return (int) 0;    //Nothing for now. 
};


/*
 *************************************************
 * KiScheduler:
 *    Interface para chamar a rotina de scheduler.
 *    Troca as threads que estão em user mode, 
 * usando o método cooperativo. 
 * Round Robing. 
 *    As tarefas tem a mesma prioridade.
 *    + Quando encontrada uma tarefa de maior prioridade, 
 * escolhe ela imediatamente.
 *    + Quando encontrar uma tarefa de menor prioridade, 
 * apenas eleva a prioridade dela em até dois valores 
 * acima da prioridade base, pegando a próxima tarefa. 
 *    + Quando uma tarefa está rodando à dois valores 
 * acima da sua prioridade, volta a prioridade para a 
 * sua prioridade básica e executa.
 *
 * @todo: 
 *     Essa rotina deve ter retorno do tipo 'int'.
 */
int KiScheduler (){
    
	// ?? Quem está chamando ? Filtros ?
    // @todo: Talvez haja mais casos onde não se deva trocar a tarefa.

	//#bugbug 
	//Porque retornamos 0 ???
	//Scheduler Status. (LOCKED, UNLOCKED).
	
	if (g_scheduler_status == LOCKED)
	{
        return (int) 0;
    };

	// Retornaremos se tivermos apenas um thread rodando.
	// Pois não há o que trocar.
	if ( ProcessorBlock.threads_counter == 1 )
	{ 
		//Se só temos uma então devemos retornar a idle.
		current_thread = idle;
		return (int) idle;
	};
	
    //Chama o Scheduler.
//done:

	return (int) scheduler ();
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
 

 
/* KiSelectNextThread: */ 
/* #todo: rever isso */
int KiSelectNextThread (int current ){
	
	//
    // @todo: Fazer filtros.
	//
	
	//@todo: Max.
	
	if (current < 0)
	{
		current = next_thread;
	}
	
//done:

    return (int) SelectNextThread (current);
};


void KiDoThreadReady (int id){
	
    do_thread_ready(id);
};


void KiDoThreadRunning (int id){
	
    do_thread_running(id);
};


void KiDoThreadSleeping (int id){
	
    do_thread_sleeping(id);
};


void KiDoThreadZombie (int id){
	
	do_thread_zombie(id);
};


void KiDoThreadDead (int id){
	
    do_thread_dead(id);
};

 
/*
 * KiNewTaskScheduler:
 *     ??
 *    @todo: Mudar para KiSchedulerNewThread().
 */
void KiNewTaskScheduler()
{
    //return;    //Cancelada.
};


/*
 * KiDispatchTask:
 *     Executa uma thread pronta pra rodar.
 *     @todo: Mudar para KiDispatchThread(int tid);
 *
 */
void KiDispatchTask()
{
	//...
//done:
    //return;
};


/*
 * KiSetPriority:
 *     Interface. 
 *     Faz alterações na prioridade de acordo com o status.
 */
 
int KiSetPriority (){
	
	//#todo: Fazer alguma coisa aqui.
	
	return (int) set_priority ();
};


/*
 *****************************************************
 * KiSetCurrent:
 *     Seleciona a thread atual.
 *     @todo: Mudar o argumento para (int tid).
 */
void KiSetCurrent (int id){
	
	//@todo: Filtro.
	
    set_current (id);
};


/*
 * KiGetCurrent:
 *     Pega o tid da thread atual.
 */
 
int KiGetCurrent (){
	
    return (int) get_current ();
};


/*
 * KiGetCurrentTask:
 *     @todo: Modar para KiGetCurrentProcess.
 *     #bugbug: Esse nome é inapropriado.
 */
 
int KiGetCurrentTask (){
	
    return (int) get_current_task(); 
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
	
	if ( i >= (2*THREAD_COUNT_MAX) ){
        return (int) next_thread;			
	};
	
	// Nothing ?!
	
	// Done! 
	// Encontramos uma tarefa de prioridade maior.

    return (int) Current;
};


/*
 ********************************************************************
 * preempt:
 *     Preempt current.
 *     Uma thread que está rodando será interrompida para dar lugar pra 
 * outra thread com prioridade maior.
 *
 * #todo: Se estiver running, torna ready. (preempt).
 * Preempt current task if we can. 
 * Find Higher priority thread if we can.
 */
 
void preempt (){

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
	
	//
	// Next 
	// Procura uma de maior prioridade. 
	// Não havendo usa a Idle.
	//
	
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
    
    //#bugbug:
	//E se Next for inválida.
	//Poderíamos checar aqui mesmo.
	
};



/* Obtendo o TID da thread atual. */
int get_current (){
	
	return (int) current_thread;
};


/* #deletar
 * get_current_task:
 *     Pega o id da thread atual.
 *    @todo: Criar scheduleriGetCurrentTID();
 */
int get_current_task (){
	
    return (int) get_current();
};


/* #todo: mudar para set_current_thread ( int tid ). */
void set_current (int id){
	
	if ( id == current_thread ){
		return;
	}
	
	// Limits.
	if (id < 0 || id >= THREAD_COUNT_MAX){
	    return;
	}
	
	// Nothing ?!
	
	// Done.	

	current_thread = (int) id; 	
};



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
};


/* do_thread_ready: #todo: mudar o argumento para tid */ 
void do_thread_ready (int id){
	
    struct thread_d *t; 
	
	if (id < 0 || id >= THREAD_COUNT_MAX){
	    return;
	}
	
	t = (void *) threadList[id]; 	
	
	if ( (void *) t != NULL )
	{
		//if ( t->used == 1 && t->magic == 1234 )
			
	    t->state = READY;
	}
};


/* do_thread_running: #todo: mudar o argumento para tid */
void do_thread_running (int id){
	
    struct thread_d *t; 
	
	if (id < 0 || id >= THREAD_COUNT_MAX){
	    return;
	}
	
	t = (void *) threadList[id]; 	
	
	if ( (void *) t != NULL )
	{
		if ( t->used == 1 && t->magic == 1234 )
		{
		    t->state = RUNNING;	
		}
	};
};


/*
 ************************************************************
 * do_thread_sleeping:
 *     Muda o state de uma thread pra blocked.
 *     @todo: Mudar o nome da função para do_thread_blocked.
 */
void do_thread_sleeping (int id){
	
    struct thread_d *t; 

	if (id < 0 || id >= THREAD_COUNT_MAX){
	    return;
	}

    // Struct.
	t = (void *) threadList[id];	
	
	if ( (void *) t != NULL){
	    t->state = BLOCKED;
    }	
};


/* do_thread_zombie: #todo: mudar o argumento para tid */
void do_thread_zombie (int id){
	
    struct thread_d *t; 
	 
	if (id < 0 || id >= THREAD_COUNT_MAX){
	    return;
	}
	
	t = (void *) threadList[id]; 
	
	if( (void *) t == NULL )
	{
	    return;
	}else{
        
		if ( id != IDLE )
		{
            t->state = ZOMBIE;
        }
    };
};


/* do_thread_dead: #todo: mudar o argumento para tid */
void do_thread_dead (int id){
	
    struct thread_d *t; 
	
	if (id < 0 || id >= THREAD_COUNT_MAX){
	    return;
	}

	t = (void *) threadList[id]; 	
	
	if ( (void *) t != NULL )
	{
	    t->state = DEAD;
	}
};


/*
 **************************************************
 * wakeup_thread: 
 *    Para acordar uma thread, basta colocar ela no 
 * estado RUNNING se ela estiver com seu contexto 
 * salvo e seu estado WAITING. 
 *
 * @todo:
 *     Criar scheduleriWakeupYhread(int tid);
 * 
 */
void wakeup_thread (int tid){
	
    int Status;
    struct thread_d *t; 	
	//...
	
	//Limits.
	if ( tid < 0 || tid >= THREAD_COUNT_MAX ){
	    return;
	}

    //Struct.
	t = (void *) threadList[tid]; 
	
	if ( (void *) t == NULL )
	{ 	
	    return;    
	
	}else{
	    
		//Se o contexto não foi salvo. 
		//Não tem como acorda-la.
		//Pois acordar significa apenas retornar 
		//ao estado RUNNING.
		if ( t->saved == 0 ){ 
	        return; 
		}
		
		// Se estiver bloqueada, 
		// não tem como acordar ainda. 
		// precisa desbloquear.
		if (t->state == BLOCKED){ 
	        return; 
		}
			
	    //Isso acorda a thread,
		//mas não coloca ela imediatamente para rodar,
		//nem precisa.
	    do_thread_running(tid);
	
	};

    // Nothing ?!
};
 

/*
 ***************************************
 * SelectNextThread:
 *     Configurando a próxima thread da thread
 * indicada via argumento.
 *
 * @todo: Mudar para schediSelectNextThread(int current);.
 *
 */
int SelectNextThread (int current){
	
	int Next;
	
    struct thread_d *t; 
    struct thread_d *n; 
    
	//Limits.
	
	if ( current < 0 || current >= THREAD_COUNT_MAX ){
		
	    return (int) 0;
	}
	
    // Struct.
	
    t = (void *) threadList[current];		
	
	if( (void *) t == NULL )
	{
	    return (int) 0;
	
	}else{
		
        //Se não existe indicação de próxima.
	    if( (void *) t->Next == NULL )
	    {
		    //Procura a próxima tarefa, de acordo com a prioridade.
		    Next = (int) find_higher_priority();
			
		    n = (void *) threadList[Next];
		    
			if ( (void *) n == NULL )
			{
				Next = next_thread;
			    return (int) Next; 
		    
			}else{
				
			    Next = (int) n->tid;    //Pega id.
			    return (int) Next;
			};
	    
		//Aceita a indicação de próxima.
		}else{
			
			n = (void *) t->Next;
			
			if ( (void *) n == NULL )
			{
				Next = next_thread;
			    return (int) Next;
			
			}else{
			    Next = (int) n->tid;    //Pega o tid.
				t->Next = NULL;
                return (int) Next;
			};
			//Nothing.
		};
        //Nothing.		
	};
	
	// More ?!
	
// Done.
done:	
    return (int) Next;
};



/*
 *****************************************
 * check_for_standby:
 *     Procura na lista de threads no 
 * estado StandyBy.
 * Se tiver uma thread nessa lista, ela se torna 
 * a current. Para rodar pela primeira vez, 
 * atravéz de Spawn.
 * Não retorna se encontrar uma threa na lista.
 *
 */
 
void check_for_standby (){
	
    int newId;
	
	struct thread_d *New;
	
	
	// #todo: 
	// Max variable.
	
	int i = 0;
	int Max = 32;
	
	do 
	{
		New = (void *) queue->standbyList[i];
		
		if ( (void *) New != NULL )
		{
		    if ( New->used == 1 && 
			     New->magic == 1234 && 
				 New->state == STANDBY )   
			{
			    	
				current_thread = (int) New->tid;
			    goto do_spawn;
			
			};
		};
		
		++i;
		
	} while (i < Max);  

    // Done. 
    // Nenhuma tarefa precisa ser inicializada.
    // Podemos apenas retornar para o taskswitch.
	
    //done:
    
	return;
	
	
	//
	//  ## SPAWN ##
	//
	
    // Do Spawn.
    // spawn.c
	
do_spawn:

    KiSpawnTask ( current_thread );
	
    //  ## No return ##	
	
    panic ("schedi-check_for_standby: ERROR");	
};


/*
 *****************************************************
 * check_quantum:
 *     Checa o quantum atribuido às threads da lista.
 *     Seleciona a primeira thread encontrada com o 
 * quantum no limite. #todo: rever isso.
 *
 * @todo: Mudar para schediCheckThreadQuantum();
 *
 */
int check_quantum (){
	
    //int newId;	
	
	struct thread_d *New;
	
	int i=0;
	
	while ( i < THREAD_COUNT_MAX )
	{
        New = (void *) threadList[i];    	
	    
		if ( (void *) New != NULL )
		{ 
		    if ( New->used == 1 && 
				 New->magic == 1234 &&
				 New->state == READY &&
				 New->quantum == QUANTUM_LIMIT )
			{
		        return (int) New->tid;
			};
			//Nothing.
		};	
		
		i++;
	};
	
	// Nothing ?!
	
    return (int) 0;
};


//
// End.
//

