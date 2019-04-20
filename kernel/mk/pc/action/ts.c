/*
 * File: mk/pc/action/ts.c
 *
 *     Task Switching.
 *
 *     +Save the context of a thread.
 *     +Call scheduler to switch the thread.
 *     +Call dispatcher to dispatch a thread.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - 2019 Revision.
 *     //...
 */


#include <kernel.h>
 
 
//
// Variáveis internas.
//
  
int lock_taskswitch;  
//int __taskswitch_lock;
//...


  
//  
// Internal.  
//

void taskswitchRR (void);
//...



//
// ...
//

/*
void taskswitchFlushTLB();
void taskswitchFlushTLB(){
	//@todo: Implementar.
	return;
}
*/


/*
 * KiTaskSwitch:
 *     Interface para chamar a rotina de Task Switch.
 *     Essa rotina somente é chamada por hw.inc.
 *     KiTaskSwitch em ts.c gerencia a rotina de 
 * troca de thread, realizando operações de salvamento e 
 * restauração de contexto utilizado variáveis globais e 
 * extrutura de dados, seleciona a próxima thread através 
 * do scheduler, despacha a thread selecionada através do 
 * dispatcher e retorna para a função _irq0 em hw.inc, 
 * que configurará os registradores e executará a 
 * thread através do método iret.
 *
 * #importante:
 * Na verdade, é uma interface pra uma rotina que 
 * faz tudo isso.
 * 
 */
 
/*
	// @todo: Fazer alguma rotina antes aqui ?!
	
	// Obs: A qui poderemos criar rotinas que não lidem com a troca de 
	// threads propriamente, mas com atualizações de variáveis e gerenciamento 
	// de contagem.
	// >> Na entrada da rotina podemos atualizar a contagem da tarefa que acabou de rodar.
	// >> A rotina task_switch fica responsável apenas troca de contexto, não fazendo 
	// atualização de variáveis de contagem.
	// >> ?? Na saída ??
	
	// ?? quem atualizou as variáveis de critério de escolha ??? o dispacher ??
*/ 
 
void KiTaskSwitch (void){
	
	//Limits.
	
	if ( current_thread < 0 || current_thread >= THREAD_COUNT_MAX )
	{	
	    printf ("KiTaskSwitch: current_thread %d", current_thread );										   
        die ();
	}
	
	if ( current_process < 0 || current_process >= PROCESS_COUNT_MAX )
	{
		
	    printf ("KiTaskSwitch: current_thread %d",current_process );										   
        die ();
	}
	
#ifdef SERIAL_DEBUG_VERBOSE
	debug_print ("ts ");
#endif	
	

	// ## Task switch ##
	
	task_switch ();
	
    // obs: 
	// Nessa hora ja temos um thread atual e um processo atual selecionados.
    // podemos checar as variáveis para conferir se não está fora dos limites.
    // Se estiverem fora dos limites, podemos usar algum etodo para selecioanrmos 
    // outro processo ou outra thread com limites válidos.
	
	//Retornando para _irq0 em head\x86\hw.inc.
};


/*
 **********************************************************
 * task_switch:
 *
 * Switch the thread.
 * Save and restore context.
 * Select the next thread and dispatch.
 * return to _irq0.
 * Called by KiTaskSwitch.
 */
 
void task_switch (void){

	int New;
	int Max;

	struct process_d *P;	
	struct thread_d *Current;

	Max = PRIORITY_MAX;


	// Current thread. 
	
	Current = (void *) threadList[current_thread]; 
	
	if ( (void *) Current == NULL )
	{
		panic ("ts-task_switch: struct Current");
		//printf ("ts-task_switch: struct Current %x", (void *) Current );
		//die ();
	}

	// Current process. 

	P = (void *) Current->process;

	if ( (void *) P == NULL )
	{
        panic ("ts-task_switch: struct C");
		//printf ("ts-task_switch: struct C %x", (void *) P );
		//die ();
	}
	
	if ( (void *) P != NULL )
	{
		if ( P->used == 1 && P->magic == 1234 )
		{	
			current_process = (int) P->pid;
		}else{
		
		    //??
			//? fail ??
		}
		
		//...
	};

	
	//...

    //
	//  ======== ## Conting ## ========
    //
	
	
	// step: Quantas vezes ela já rodou no total.
	// runningCount: Quanto tempo ela está rodando antes de parar.

	Current->step++; 
	Current->runningCount++;
	
	//quanto tempo em ms ele rodou no total.
	Current->total_time_ms = (unsigned long) Current->total_time_ms + (1000/sys_time_hz);	
	
	//incrementa a quantidade de ms que ela está rodando antes de parar.
	//isso precisa ser zerado quando ela reiniciar no próximo round.
	Current->runningCount_ms = (unsigned long) Current->runningCount_ms + (1000/sys_time_hz);	


	//
	// ======== ## locked ## ========
	//
	
	// Taskswitch locked ?, Return without saving.
	
	if ( task_switch_status == LOCKED )
	{    		
		IncrementDispatcherCount (SELECT_CURRENT_COUNT);
		return; 
		
	}; //FI LOCKED

	
    //
	// ======== ## unlocked ## ========
	//
	
	if ( task_switch_status == UNLOCKED )
	{
		//
		// ## SAVE CONTEXT ##
		//
		
		save_current_context ();
		Current->saved = 1;	
		
		// #importante:
		// Se a thread ainda não esgotou seu quantum, 
		// então ela continua usando o processador.
		
		if ( Current->runningCount < Current->quantum )
		{
			IncrementDispatcherCount (SELECT_CURRENT_COUNT);
			return; 
		
		// #importante
		// Nesse momento a thread esgotou seu quantum, então sofrerá preempção
		// e outra thread será colocada para rodar de acordo com a ordem 
		// estabelecida pelo escalonador.
			
		}else{
			
			//
			// ======== ## PREEMPT ## ========
			//
		
			// * MOVEMENT 3 (Running --> Ready).
			
			if ( Current->state == RUNNING )
			{
				// Preempt.
				// MOVEMENT 3 (running >> ready)  
				
				Current->state = READY;    

				if ( Current->preempted == PREEMPTABLE )
				{
					//debug_print (" preempt_q1 ");
					queue_insert_head ( queue, (unsigned long) Current, 
						QUEUE_READY );	
				};

				if ( Current->preempted == UNPREEMPTABLE )
				{
					//debug_print (" preempt_q2 ");
					queue_insert_data ( queue, (unsigned long) Current, 
						QUEUE_READY );	
				};
			};

			//debug_print (" ok ");
			
			//
			// ======== ## EXTRA ## ========
			//
			
			// #importante:
			// Checaremos por atividades extras que foram agendadas pelo 
			// mecanismo de request. Isso depois do contexto ter sido salvo e 
			// antes de selecionarmos a próxima thread.

			if (extra == 1)
			{
				KiRequest ();
				
				// #todo: Talvez possamos incluir mais atividades extras.
				// Continua ...
				
				extra = 0;
			}
			
			//
			// ======== ## Spawn ? ## =========
			//
			
			// #importante:
			// Checar se uma thread está em standby, esperando pra rodar pela 
			// primeira vez. Nesse caso essa função não retornará.
			
			// schedi.c
			
			check_for_standby (); 

			goto try_next;

		};
		
	}; //FI UNLOCKED

    //	
    // ==== Crazy Fail ====
    //
	
	// #bugbug
	// Não deveríamos estar aqui.
	// Podemos abortar ou selecionar a próxima provisóriamente.
	
	//panic ("ts.c: crazy fail");
	
	goto dispatch_current;      	
	
	
	
	
	//
	// ======== ####  NEXT #### ========
	//
	
try_next: 
	
	
#ifdef SERIAL_DEBUG_VERBOSE	
	debug_print(" N ");
#endif	
	
	// #critério:
	// Se tivermos apenas uma thread rodando.
	
	if (ProcessorBlock.threads_counter == 1)
	{		
		//debug_print(" JUSTONE ");
		Conductor = IdleThread;

		goto go_ahead;
	}
	
	

	
	// #bugbug
	// Ao fim do round estamos tendo problemas ao reescalonar 
	// Podemos tentar repedir o round só para teste...
	// depois melhoramos o reescalonamento.
		
	// #importante:
	// #todo: #test: 
	// De pempos em tempos uma interrupção pode chamar o escalonador,
	// ao invés de chamarmos o escalonador ao fim de todo round.
	
	// #critério:
	// Se alcançamos o fim da lista encadeada cujo ponteiro é 'Conductor'.
	// Então chamamos o scheduler para reescalonar as threads.

	
	if ( (void *) Conductor->Next == NULL )
	{
		
#ifdef SERIAL_DEBUG_VERBOSE		
		debug_print(" LAST ");
#endif		
		
		//printf ("ts: scheduler 1\n");
		KiScheduler ();
		
		goto go_ahead;
	
	
	}
	
	// #critério
	// Se ainda temos threads na lisca encadeada, então selecionaremos
	// a próxima da lista.
	// #BUGBUG: ISSO PODE SER UM >>> ELSE <<< DO IF ACIMA.
	
	if ( (void *) Conductor->Next != NULL )
	{		
		Conductor = (void *) Conductor->Next;	
		
		goto go_ahead;
		
	}
	
	
	//
	//    ======== # Go ahead ## ========
	//
	
	// #importante:
	// Nesse momento já temos uma thread selecionada,
	// vamos checar a validade e executar ela.
	
	// #importante:
	// Caso a thread selecionada não seja válida, temos duas opções,
	// ou chamamos o escalonador, ou saltamos para o início dessa rotina
	// para tentarmos outros critérios.
	
	
go_ahead:

	//##############################################//
	//                                              //
	//    #### We have a thread now ####            //
	//                                              //
	//##############################################//

	Current = (void *) Conductor;
		
	if( (void *) Current == NULL )
	{ 		
		debug_print(" Struct ");
		
		//printf ("ts: scheduler 2\n");
		KiScheduler ();
		
		goto try_next;
		
	}else{
		
		if ( Current->used != 1 || Current->magic != 1234 )
		{
			debug_print(" val ");
			
			//printf ("ts: scheduler 3\n");
			KiScheduler ();
			goto try_next;	
		}	
		
		if ( Current->state != READY )
		{
			debug_print(" state ");	
			
			//printf ("ts: scheduler 4\n");
			KiScheduler ();
			goto try_next;	
		}

		//
		//    ####  Dispatcher ####
		//

		IncrementDispatcherCount (SELECT_DISPATCHER_COUNT);
		
		current_thread = (int) Current->tid;
		
		goto dispatch_current;
	}
	
	//
	// # fail #
	//
	
 	
//superCrazyFail:
	
	goto dispatch_current; 
	
	//
	//    ####  Dispatch current ####
	//	

dispatch_current:
	
	
#ifdef SERIAL_DEBUG_VERBOSE	
	debug_print(" DISPATCH_CURRENT \n");
#endif
	
	//
	//    ####  Validation ####
	//	

	Current = (void *) threadList[current_thread];
	
	if ( (void *) Current == NULL )
	{	
		panic ("pc-action-ts-task_switch.dispatch_current: Struct ERROR");
	
	}else{
				
		if ( Current->used != 1 || 
			 Current->magic != 1234 || 
			 Current->state != READY )
		{
			panic ("pc-action-ts-task_switch.dispatch_current: validation ERROR");
		}

		Current->runningCount = 0;	
	}
	
	//
	// #### Call dispatcher #### 
	//
	
	//
	// * MOVEMENT 4 (Ready --> Running).
	//
	
	dispatcher (DISPATCHER_CURRENT);    	

	//
	//  #### DONE ####
	//

done:

	if ( Current->ownerPID < 0 || Current->ownerPID >= THREAD_COUNT_MAX )
	{
		printf ("action-ts-task_switch: ownerPID ERROR \n", Current->ownerPID );
		die();
	}
	
	//
	//    ## PROCESS ## 
	//
	
	
	P = (void *) processList[Current->ownerPID];
	
	if ( (void *) P == NULL )
	{
		printf("action-ts-task_switch: Process %s struct fail \n", P->name_address );
		die();
	}
	
	if ( (void *) P != NULL )
	{
		if ( P->used != 1 || P->magic != 1234 )
		{
			printf("action-ts-task_switch: Process %s corrompido \n", 
				P->name_address );
			die();
		}

		if ( P->used == 1 && P->magic == 1234 )
		{
			current_process = (int) P->pid;

			if ( (unsigned long) P->DirectoryPA == 0 )
			{	
				printf ("action-ts-task_switch: Process %s directory fail\n", 
					P->name_address );
				die();
			}
			
			current_process_pagedirectory_address = (unsigned long) P->DirectoryPA;
			goto doneRET;
		}
		
		panic ("action-ts-task_switch: * Struct * \n");
	}

	panic ("action-ts-task_switch: bug sinistro kkk \n");

doneRET:
	return; 
}


/*
 * taskswitchRR:
 *     Task switch usando Round Robin.
 *     Obs: Esse método ainda não foi habilitado.
 */

void taskswitchRR (void)
{
	int i;
	int Max = (int) ProcessorBlock.threads_counter;
	struct thread_d *Current; //Thread atual.
	
	//Filtro.
	//if(current_thread ...){}
	
	Current = (void *) threadList[current_thread]; 
	if((void *) Current == NULL)
	{
	    panic("taskswitchRR error: Struct");
		//die();
	};
	
	//
	//todo: Checar se a estrutura é válida. 
	//
	
	/*
	 *    Incrementa.
	 *     Continua na mesma tarefa enquanto a contagem de quantum for
	 *     menor que o quantum limite da tarefa atual.
	 *     Assim temos uma contagem de vezes que uma tarefa deve ficar
     *     no processador sem sair.	 
	 */	


	//se o runningCount ainda é menor que a cota, dispacha.
	//Obs: Cuidado !! A média é (PRIORITY_NORMAL*2)
	if(Current->runningCount < Current->quantum){ 
		goto dispatch_current;
	}else{
		
        //?? @todo: Talvez aqui seja o movimento 3, running >> ready. Conferir.  		
		Current->state = READY;
		
		//
		// @todo: Nesse momento, colocar no fim da fila ready. tail
		//
		//queue_insert_data( queue, (unsigned long) Current, QUEUE_READY);
		
		//se ouver outra válida nos slots despacha.
		i = (int) current_thread;
				
		do
		{
		    i++;
			
			//Contando++
			if(i < Max)
			{
		        Current = (void *) threadList[i];
		        if( (void *) Current != NULL )
			    {
			        if( Current->used == 1 && 
					    Current->magic == 1234 && 
						Current->state == READY)
				    {
				        Current->runningCount = 0;
				        current_thread = (int) i;
				        goto dispatch_current;
				    };
			    };
			};
			
			// Overflow
			if(i >= Max)
			{ 
			    i = 0; 
				Current = (void *) threadList[i];
			    if( (void *) Current != NULL )
				{
				    if( Current->used == 1 && 
					    Current->magic == 1234 && 
						Current->state == READY )
					{
					    Current->runningCount = 0;
					    current_thread = (int) i;
						goto dispatch_current;
					};
				};
			};

		}while(i < Max);
			
        panic("taskswitchRR error: *HANG");
  			
		//Use idle. Não havendo outra alem da idle usa ela.
		//current_idle_thread.
		//current_thread = (int) 0;
		//goto dispatch_current;
	}; 
	
//	
// Done.
//
dispatch_current:	
	dispatcher(DISPATCHER_CURRENT);	
	return;	
};




/*
 ***************************************************
 * set_task_status:
 *    Configura o status do mecanismo de task switch.
 *    Se o mecanismo de taskswitch estiver desligado 
 * não ocorrerá a mudança.
 *
 * @todo: Mudar o nome dessa função para taskswitchSetStatus(.);
 *
 */ 
void set_task_status( unsigned long status )
{
    //#bugbug: Mudar para int.	
	task_switch_status = (unsigned long) status;
};


/*
 * get_task_status:
 *     Obtem o status do mecanismo de taskswitch.
 * @todo: Mudar o nome dessa função para taskswitchGetStatus();.
 */

unsigned long get_task_status (void)
{
    //#bugbug: Mudar para int.		
    
	return (unsigned long) task_switch_status;
}


/*
 * taskswitch_lock:
 *     Trava o mecanismo de taskswitch.
 *     @todo: Mudar para taskswitchLock().
 */ 

void taskswitch_lock (void){
	
    task_switch_status = (unsigned long) LOCKED;
}


/*
 * taskswitch_unlock:
 *     Destrava o mecanismo de taskswitch.
 *     @todo: Mudar para taskswitchUnlock().
 */ 

void taskswitch_unlock (void){
	
    task_switch_status = (unsigned long) UNLOCKED;
}


//
// End.
//
