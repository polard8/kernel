/*
 * File: ps/action/dispatch.c
 *
 * Descrição:
 *     Arquivo principal do dispatcher do kernel.
 *     Faz parte do Process Control, parte fundamental do 
 * Kernel Base.    
 *     Coloca tarefas pra rodar que estejam em suas 
 * respectivas filas.
 *     Alterna entre as filas de acordo com o tipo de dispatcher.
 * As opções são:
 *     +System dispatcher. 
 *     +Idle dispatcher.
 *     +Periodic dispatcher.
 *     +round robin dispatcher.
 *     +realtime dispatcher.
 *
 * Observação:
 *    Somente um tipo de dispatcher está ativo no momento.
 *
 * History
 *     2015 - Created by Fred Nora.
 *     2018 - Revision.
 *     //...
 */


#include <kernel.h>


//
// Variáveis internas.
//

//int dispatchStatus;
//int dispatchError;
//...


//
// #todo:
// Protótipo de funções internas.
//

int syscoopDispatcher (void);
int usercoopDispatcher (void);
int sysconcDispatcher (void);
int userconcDispatcher (void);
int systemDispatcher (void);
int readyDispatcher (void);
int idleDispatcher (void);
int periodicDispatcher (void);
int rrDispatcher (void);
int realtimeDispatcher (void);
int dispatch_Default (void);



/*
 *********************************************************
 * dispatcher:
 *     Despacha a thread atual que foi escolhida pelo scheduler. 
 *     Despacha, colocando ela no estado RUNNING e restaurando os valores 
 * dos registradores.
 *     Essa função é chamada no final da rotina task_switch, antes dela 
 * retornar.
 *     Obs: 
 *     Despacha a tarefa de acordo dom o tipo de dispatcher.
 *     Porém os tipos diferentes de dispacher ainda não estão habilitados, 
 * só um funciona.
 */

// #todo
// Change the return type and return with error
// if something goes wrong. So this way we can try another thing.
// int dispatcher ( int type ){

void dispatcher ( int type ){

    struct thread_d *dispatch_Pointer;


	// Obs: 
	// @todo:
	// (Fase de teste). 
	// Usando apenas um tipo de dispatcher. 
	// Deteminando o tipo de dispacher por enquanto

    if ( type != DISPATCHER_CURRENT )
    {
        type = DISPATCHER_CURRENT;
    }


	//
	// Seleciona o tipo.
	//

    // #todo:
    // All the different types of dispatch need to be implemented.

//SelectDispatcherType:


    switch (type)
    {

        // It's not implemented.
        case DISPATCHER_NULL:
            goto dispatchCurrent;     
            break;

        // It's not implemented.
        case DISPATCHER_SYSCOOP:
            goto dispatchSyscoop;
            break;

        // It's not implemented.
        case DISPATCHER_USERCOOP:
            goto dispatchUsercoop; 
            break;

        // It's not implemented.
        case DISPATCHER_SYSCONC: 
            goto dispatchSysconc;
            break;

        // It's not implemented.
        case DISPATCHER_USERCONC: 
            goto dispatchUserconc;
            break;

        // It's not implemented.
        //System.
        case DISPATCHER_SYSTEM:
            goto dispatchCurrent;
            break;

        // It's not implemented.
        //Idle.
        case DISPATCHER_IDLE:
            goto dispatchCurrent;
            break;

        // It's not implemented.
        //Periodic. 
        case DISPATCHER_PERIODIC:
            goto dispatchCurrent;
            break;

        // It's not implemented.
        //Round Robin. (RR).
        case DISPATCHER_RR:
            goto dispatchCurrent;
            break;

        // It's not implemented.
        //Realtime.
        case DISPATCHER_REALTIME:
            goto dispatchRealtime;
            break;


        // This is working ...
        case DISPATCHER_CURRENT:
            goto dispatchCurrent;
            break;
 
        // It's not implemented.
        //Despacha da fila do dispatcher(ready queue)
        case DISPATCHER_READY:
            goto dispatchReady;
            break; 

        //default.
        default:
            goto dispatchCurrent;
            break;
     };


	// Obs: 
	// E se escapar do laço acima ?!


//Dispatch sys coop.
dispatchSyscoop: 
    current_thread = syscoopDispatcher();
    goto do_dispatch;
  
//Dispatch user coop.
dispatchUsercoop:
    current_thread = usercoopDispatcher();
    goto do_dispatch;
   
//Dispatch system conc.
dispatchSysconc:
    current_thread = sysconcDispatcher();
    goto do_dispatch;
   
//Dispatch user conc.
dispatchUserconc:
    current_thread = userconcDispatcher();
    goto do_dispatch; 

//Dispatch realtime.
dispatchRealtime:
    current_thread = realtimeDispatcher();
    goto do_dispatch;

//Dispatch ready.
dispatchReady:
    current_thread = readyDispatcher();
    goto do_dispatch;


//Dispatch current.
dispatchCurrent:
    //current_thread = current_thread;
    goto do_dispatch;


    //
    //    ####  DO DISPATCH ####
    //

//----------------------------------------
// Do Dispatch: Dispatch 'current_thread'.
//----------------------------------------

do_dispatch:


	// Checa estrutura.

    dispatch_Pointer = (void *) threadList[current_thread];

    if ( (void *) dispatch_Pointer == NULL ){
        panic ("dispatch-dispatcher: struct\n");
    }

	// Checa o 'state'.

    if ( dispatch_Pointer->state != READY ){
        panic ("dispatch-dispatcher: State ERROR\n");
    }


	// #importante
	// * MOVEMENT 4 (Ready --> Running).
	// A thread passa para o estado RUNNING.
	// Reinicia a contagem.


    if ( dispatch_Pointer->state == READY )
    {
        dispatch_Pointer->state = RUNNING;
        dispatch_Pointer->runningCount = 0;

        queue_insert_data ( queue, 
            (unsigned long) dispatch_Pointer, QUEUE_RUNNING );
    }


	//
	// ## RESTORE CONTEXT ##
	//

	// #importante
	// Flag sinalizando que o contexto não está mais salvo.
	// Esse flag é acionada quando o contexto é salvo no início 
	// da task switch.

    dispatch_Pointer->saved = 0;

	// #importante
	// Chama a rotina que colocará as informações da estrutura de thread 
	// nas variáveis usadas pelo assembly para configurar os registradores 
	// antes do iretd.

    restore_current_context();

// #todo
// Change the return type and return with error
// if something goes wrong. So this way we can try another thing.
    //return 0;

    return;
}


//
//  ## IMPORTANTE  ##
//  Todos os outros modelos de dispacher abaixo ainda 
//  não foram habilitados.
//

/*
 * readyDispatcher:
 *     Dispatcher principal. 
 *     Pega da fila do dispatcher. Que é a fila de READY tasks.
 *     Pega a head da fila de ready quando vencer o tempo dela de espera.
 *     Obs: Esse tipo de dispacher ainda não foi habilitado.
 */

// #todo
// It's not implemented.

int readyDispatcher (void)
{
	struct thread_d *dispatch_Pointer;
	
    dispatch_Pointer = (void*) queue_get_data( queue, QUEUE_READY);
	
	if( (void*) dispatch_Pointer != NULL && 
	            dispatch_Pointer->used == 1 && 
				dispatch_Pointer->magic == 1234)
	{
        dispatch_Pointer->quantum = 0;
        goto done;
	}
	else
	{
	    dispatch_Pointer = (void*) threadList[0];
		dispatch_Pointer->quantum = 0;
        goto done; 
	};
	
	//
	// @todo: Check.
	//
	
	/*
	if( (void*) dispatch_Pointer == NULL )
	{
	    //todo
	};
    */
	
//Done.
done:
	current_thread = (int) dispatch_Pointer->tid;
	return (int) current_thread;
}



/*
 * syscoopDispatcher:
 *  Obs: Esse tipo de dispacher ainda não foi habilitado.
 */
 
// #todo
// It's not implemented.

int syscoopDispatcher (void)
{
	struct thread_d *dispatch_Pointer;
	
    dispatch_Pointer = (void*) queue_get_data( queue, QUEUE_SYSCOOP);
	
	if( (void*) dispatch_Pointer != NULL && 
	            dispatch_Pointer->used == 1 && 
				dispatch_Pointer->magic == 1234)
	{
        dispatch_Pointer->waitingCount++;	
		if(dispatch_Pointer->waitingCount > dispatch_Pointer->waiting_limit)
		{
		    dispatch_Pointer->waitingCount = 0;
			current_thread = (int) dispatch_Pointer->tid;
		    return (int) dispatch_Pointer->tid;
        }	
		
	}
	else
	{
	    current_thread = 0;
	    return (int) current_thread;
	};
	
fail:
    //todo: hang
    return (int) current_thread;
}


/*
 * usercoopDispatcher:
 *  Obs: Esse tipo de dispacher ainda não foi habilitado.
 */
 
// #todo
// It's not implemented.

int usercoopDispatcher (void)
{
	struct thread_d *dispatch_Pointer;
	
    dispatch_Pointer = (void*) queue_get_data( queue, QUEUE_USERCOOP);
	
	if( (void*) dispatch_Pointer != NULL && 
	            dispatch_Pointer->used == 1 && 
				dispatch_Pointer->magic == 1234)
	{
        dispatch_Pointer->waitingCount++;	
		if(dispatch_Pointer->waitingCount > dispatch_Pointer->waiting_limit)
		{
		    dispatch_Pointer->waitingCount = 0;
			current_thread = dispatch_Pointer->tid;
		    return (int) dispatch_Pointer->tid;
        }	
		
	}
	else
	{
	    current_thread = 0;
	    return (int) current_thread;
	};

fail:
    //todo: hang
    return (int) current_thread;
}


/*
 * sysconcDispatcher:
 *  Obs: Esse tipo de dispacher ainda não foi habilitado.
 */
 
// #todo
// It's not implemented.

int sysconcDispatcher (void)
{
	struct thread_d *dispatch_Pointer;
	
    dispatch_Pointer = (void*) queue_get_data( queue, QUEUE_SYSCONC);
	
	if( (void*) dispatch_Pointer != NULL && 
	            dispatch_Pointer->used == 1 && 
				dispatch_Pointer->magic == 1234)
	{
        dispatch_Pointer->waitingCount++;	
		if(dispatch_Pointer->waitingCount > dispatch_Pointer->waiting_limit)
		{
		    dispatch_Pointer->waitingCount = 0;
			current_thread = dispatch_Pointer->tid;
		    return (int) dispatch_Pointer->tid;
        }	
		
	}
	else
	{
	    current_thread = 0;
	    return (int) current_thread;
	};

fail:
    //todo: hang
    return (int) current_thread;
}


/*
 * userconcDispatcher:
 *  Obs: Esse tipo de dispacher ainda não foi habilitado.
 */

// #todo
// It's not implemented.

int userconcDispatcher (void)
{
	struct thread_d *dispatch_Pointer;
	
    dispatch_Pointer = (void*) queue_get_data( queue, QUEUE_USERCONC);
	
	if( (void*) dispatch_Pointer != NULL && 
	            dispatch_Pointer->used == 1 && 
				dispatch_Pointer->magic == 1234)
	{
        dispatch_Pointer->waitingCount++;	
		if(dispatch_Pointer->waitingCount > dispatch_Pointer->waiting_limit)
		{
		    dispatch_Pointer->waitingCount = 0;
			current_thread = dispatch_Pointer->tid;
		    return (int) dispatch_Pointer->tid;
        }	
		
	}
	else
	{
	    current_thread = 0;
	    return (int) current_thread;
	};
	
fail:
    //todo: hang
    return (int) current_thread;
}


/*
 ******************************************************
 * systemDispatcher:
 *     System dispatcher.
 *     ?? Penso que isso seja uma interface para 
 * chamar o dispacher. 
 */

// #todo
// It's not implemented.

// # suspensa #
int systemDispatcher (void)
{ 
    return 0; 
}


/*
 *****************************************************
 * idleDispatcher:
 *     Despachar a thread idle atual.
 *     current_idle_thread.
 *         
 * Obs:
 *     A tarefa idle pode ter qualquer id.
 *     Devemos despachar a idle quando o sistema estiver 
 * ocioso ou quanto a thread idle é a única thread.
 *     Se o kernel detectar quen não há mas nenhuma thread 
 * no sistema então o kernel deve selecionar uma nova 
 * idle atual e despacha-la. 
 */
 
// #todo
// It's not implemented.

// ## suspensa ##

int idleDispatcher (void)
{ 
    //current_idle_thread

    return 0; 
}


/*
 * periodicDispatcher:
 *     Periodic dispatcher.
 *     Obs: Esse tipo de dispacher ainda não foi habilitado.
 */

// #todo
// It's not implemented.

int periodicDispatcher (void)
{ 
    // struct thread_d *New;
   
    return 0; 
}


/*
 * rrDispatcher:
 *     Round robin dispatcher.
 *     Obs: Esse tipo de dispacher ainda não foi habilitado.
 */
 
// #todo
// It's not implemented.

int rrDispatcher (void)
{ 
    return 0; 
}


/*
 * realtimeDispatcher:
 *     ## bugbug, na verdade ainda estou aprendendo sobre isso. :) sorry.
 *     Real time dispatcher.
 *     Pega uma tarefa na fila de tarefas com prioridade e tipo realtime.
 *
 * * IMPORTANTE:
 *   Normalmente essas tarefas ficam confinadas em um processador, destinado 
 * pra tarefas de tempo real.
 * Obs:
 *     Na verdade não é tão real time assim.
 *     Obs: Esse tipo de dispacher ainda não foi habilitado.
 */

// #todo
// It's not implemented.

int realtimeDispatcher (void)
{
	
/*
 	
    struct thread_d *New;
	  
    //Real time status ~ Round robin.     
    if(realtimeStatus == 1)
    { 
        New = (void*) queue_get_data( queue, QUEUE_REALTIME);
	    if( (void*) New != NULL && 
	                New->used == 1 && 
				    New->magic == 1234 && 
				    New->type == TYPE_REALTIME &&
				    New->priority == PRIORITY_MAX )
	    {   
	        return (int) New->tid;
	    };  
    }; 
	
//
// Fail, use tID 0.
//

*/

fail:
    return 0; //idle.
}


/*
 * dispatch_Default:
 *  Obs: Esse tipo de dispacher ainda não foi habilitado.
 */
 
// #todo
// It's not implemented.

int dispatch_Default (void){

	struct thread_d *New;
	struct thread_d *Current;

	Current = NULL;
	
	
	/*
	 * Fase1 - Tenta tarefa de quantum vencido.
	 */
	int qNext=0;
    qNext = (int) check_quantum();
    if(qNext != 0)
	{
	    New = (void *) threadList[qNext];
	    
		// todo: check structure.
		
		New->next = (void *) Current;
		New->quantum = 0;
	    
		return (int) qNext;
    }


	
	/*
	 * Fase 2: 
	 *     Preempt, gethigher priority, no return.
	 *     + Coloca em preempção a tarefa atual se ela for de baixa prioridade.
	 *     + Pega uma tarefa de prioridade alta nos slots e torna ela READY,
	 *       colocando ela no fim da fila de tarefas READY. 
	 *     + Não retorna.
	 */
	
	
	/*
	 * Checar se a tarefa atual pode entrar em preempção. 
	 * Se ela não pode entrar em premmpção não faz nada. 
	 * então continua no estado READY, mas vai para o fim da fila das 
	 * tarefas ready. 
	 * obs: a tarefa tem que estar no estado ready.
	 */
	
	Current = (void *) threadList[current_thread]; 
	
	if ( Current->preempted == PREEMPTABLE && 
	     Current->priority == PRIORITY_LOW )
	{
	    //preempt ..fifo
	    //Só pode entrar se o estado é ready.
        if( Current->state == READY)
		{
		    
			//manda para o fim da fila de ready.
		    //Current->event = EVENT_PREMMPTED; //Motivo.   
			
			Current->waitingCount = 0;             //Zera o tempo de espera.
			queue_insert_data(queue, (unsigned long) Current, QUEUE_SYSCOOP);
		};
	};
	

	/*
	 * Pega nos slots uma tarefa de prioridade mais alta.
	 * Executa imediatamente se ela for ready. 
	 * mas antes coloca no fim da fila uma de menor prioridade.
	 * e coloca no fim da fila de ready.
	 */
	int nextId=0; 
	nextId = find_higher_priority();
	if( nextId > 0 )
	{
	    New = (void *) threadList[nextId]; 
		if( (void*) New == NULL ){
		    panic ("dispatch_Default: findhigerpriority return null");
		}
		//inicio da fila, lifo
		if( New->state == READY)
		{
		    New->waitingCount = New->waiting_limit;    //Tempo limite de espera.
			if( New->tid != 0)
			{
			    New->quantum = 0;
				New->next = (void *) Current;
			    return (int) New->tid;
			}
		}
	}

	
	
	/*
	 * Fase 3: Pega a próxima se houver.
	 */
	
	//se existe uma proxima tarefa. pega ela.
	//se ela estiver no estado ready o scheduler retorna.
	//se estiver no estado initialized, da spawn.
	if( (void*) Current->next != NULL )
    {
        New = (void*) Current->next;
        Current->next = NULL; //zera o indicador.
		
		if(New->state == READY)
		{
		    New->waitingCount = 0;
			if(New->tid != 0)
			{
			    New->quantum = 0;
			    New->next = (void *) Current;
				return (int) New->tid;
            }
		}
    }

	 
	/*
	 * Fase 4: Pega a idle.
	 */ 
	 
	New = (void *) threadList[0];
	
	if ( (void *) New != NULL )
	{
	    New->quantum = 0;
		New->next = (void *) Current;
		
		return (int) New->tid;
    }
    
fail:
     //#todo: test this return.
     panic ("dispatch_Default: return not tested");
     return -1;
}



/*
 * dispatch_thread2:
 *     Restaura o contexto e retorna.
 *     #bugbug. Nem sei se essa rotina está em uso.
 */
 
void dispatch_thread2 (void){
	
    struct thread_d *t;  
	
	//
	// *RESTORE CONTEXT. (current_thread)
	//
	
	restore_current_context();
	
	//
	// Struct.
	//
	
	t = (void *) threadList[current_thread]; 
	
	if ( (void *) t == NULL )
	{
		//deveria ser a current_idle_thread
	    current_thread = (int) 0;  //current_idle_thread
	    return;
		
	}else{
	    t->saved = 0;         //Náo está mais salvo o contexto.
	    t->state = RUNNING;   //Movimento 2 ou 4. ??
	};
}



/*
 *****************************************************
 * dispatch_thread:
 *     #bugbug. Nem sei se essa rotina está em uso.
 */
 
void dispatch_thread (struct thread_d *thread){

    int Status = 0;

	//
	// Structure.
	//

    if ( (void *) thread == NULL )
    {
        printf ("dispatch-dispatch_thread: thread tid={%d}", current_thread ); 
        die ();

    }else{

	    // Context.
		// #bugbug: Não estamos mais usando esse filtro
        // que seleciona apenas threads em ring 3.		
	    //Status = contextCheckThreadRing3Context(thread->tid);
	    //if(Status == 1){
	    //    printf("pc-dispatch-dispatch_task: contextCheckThreadRing3Context\n");
		//    die();
	    //};
	    //...
	};

	
	/*
	 * State:
	 *     Dispacha de acordo com o status.
	 *     +Spawn no caso de INITIALIZED.
	 */
 
    switch (thread->state)
    {
	    //Se vai rodar pela primeira vez
		case INITIALIZED:
		    thread->saved = 0;
			KiSpawnTask(current_thread);
			//spawn_task(current_thread);
	        break;
		//Continua ?? ...	
		
        //Nothing for now.
		default:
            printf("dispatch_thread fail: State!\n");
		    break;
    };


fail:
    panic ("dispatch-dispatch_thread: fail");
}


/*
 *************************************
 * init_dispatcher:
 *     inicializa o dispacher.
 *
 * dispatcherReadyList
 *     Esta é a lista do dispatcher.
 *
 * *IMPORTANTE:
 *  As threads aqui estão no estado READY e ordenadas 
 * por prioridade.
 *     
 *  +A última thread da lista é a thread de maior prioridade.
 *  +Cada elemento dessa lista é o elemento que está na HEAD 
 * de uma lista
 *  +Cada uma dessas lista é uma lista para uma prioridade 
 * específica.
 *  +Apenas a head de cada uma das listas é colocada aqui 
 * nessa lista do dispacher.
 *
 * OBS: 
 * #bugbug
 * Nesse momento, essa lista do dispacher não está em uso.  
 * O kernel está usando a lista de threads criadas, 
 * threadList[], não considerando a prioridade. :) sorry.
 *
 * @todo: Mudar o nome para dispachInit();.
 */ 
 
int init_dispatcher (void){

    int i=0;

	//
	// Para um dispatcher na forma de array.
	//


//dispatcher_array:
	
	//Index
    dispatcherQueueIndex = (int) 0;

	//Seleciona o tipo de dispatcher.
    dispatcherType = DISPATCHER_SYSTEM;

	//inicializa a fila do dispacher.

    for ( i=0; i <= PRIORITY_MAX; i++ ){
        dispatcherReadyList[i] = (unsigned long) 0;
    };

	//Init
	dispatcherReadyList[0] = (unsigned long) InitThread;


	//
	// (Desliga realtime dispatcher.) ??
	//
	
	
	//
	// Para um dispatcher na forma de Linked List.
	//

//dispatcher_linked_list:

    //
    // == Conductor =============================
    //
    
    // Inicializa o indice de condutores.
    conductorIndex = 0;

    rootConductor = (void *) kmalloc( sizeof(struct thread_d) );

    if ( (void *) rootConductor == NULL ){
        panic ("init_dispatcher: rootConductor");
    }

	// #bugbug 
	// Deveríamos iniciar com a idle thread e não com a thread 0.
	// Inicia a lista.
	// Usado para task switch.

    //#test
    rootConductor = (void *) InitThread;

    Conductor = (void *) rootConductor;
    
    tmpConductor       = (void *) rootConductor;
    tmpConductor->next = (void *) threadList[0]; 

    // #bugbug
    // Check the threads validation.

    return 0;
}



/*
 ************************************************
 * IncrementDispatcherCount:
 *     Mensura os critérios de escolha.
 *     Contagem por critério de seleção.
 *     Faz uma contagem de quantas vezes o dispatcher 
 * fez uso de cada critério.
 * Obs: Esse modelo apresentou bons resultados por muito 
 * tempo. Vamos preserva-lo. 
 */

	// #todo
	// Create error messages.

void IncrementDispatcherCount ( int type ){

	// Testing struct.

    if ( (void *) DispatchCountBlock == NULL )
    {
        return;
    }

	// Limits.

    if (type < 0 || type > 10)
    {
        return;
    }


	// Activating the selected type.

    switch (type)
    {
        case SELECT_IDLE_COUNT:
            DispatchCountBlock->SelectIdleCount++;
            break;

        case SELECT_INITIALIZED_COUNT:
            DispatchCountBlock->SelectInitializedCount++;
            break;

        case SELECT_NEXT_COUNT:
            DispatchCountBlock->SelectNextCount++;
            break;

        case SELECT_CURRENT_COUNT:
            DispatchCountBlock->SelectCurrentCount++;
            break;

       case SELECT_ANY_COUNT:
            DispatchCountBlock->SelectAnyCount++;
            break;

       case SELECT_IDEAL_COUNT:
            DispatchCountBlock->SelectIdealCount++;
            break;

       case SELECT_DISPATCHER_COUNT:
            DispatchCountBlock->SelectDispatcherQueueCount++;
            break;

		//...

       // Nothing.
       // Aqui poderia ter um contador de indefinições.
       default:
           break;
    };

	// Nothing.
	//     #bugbug
	//     Obs: @todo: O laço acima pode não selecionar nada.

}


/*
   Constructor.
int dispatchDispatch()
{};
*/


/*
int dispatchInit()
{};
*/


//
// End.
//

