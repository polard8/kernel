

#include <kernel.h>  

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
	// Isse é chamado várias vezes, é melhor não ter mensagem de debug.

void IncrementDispatcherCount ( int type )
{

    if (type < 0){
        debug_print("IncrementDispatcherCount: [FAIL] type\n");
        return;
    }


    // See:
    // landos/kernel/include/land/ps/dispatch.h

    if ( (void *) DispatchCountBlock == NULL ){
        panic ("IncrementDispatcherCount:\n");
    }

	// Activating the selected type.

    switch (type){
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
           debug_print("IncrementDispatcherCount: [FIXME] default\n");
           break;
    };

    // ??
}

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

void dispatcher ( int type )
{
    struct thread_d *dispatch_Pointer;


    debug_print ("dispatcher: [not tested] \n");

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
    //current_thread = syscoopDispatcher();
    goto do_dispatch;
  
//Dispatch user coop.
dispatchUsercoop:
    //current_thread = usercoopDispatcher();
    goto do_dispatch;
   
//Dispatch system conc.
dispatchSysconc:
    //current_thread = sysconcDispatcher();
    goto do_dispatch;
   
//Dispatch user conc.
dispatchUserconc:
    //current_thread = userconcDispatcher();
    goto do_dispatch; 

//Dispatch realtime.
dispatchRealtime:
    //current_thread = realtimeDispatcher();
    goto do_dispatch;

//Dispatch ready.
dispatchReady:
    //current_thread = readyDispatcher();
    goto do_dispatch;


//Dispatch current.
dispatchCurrent:
    debug_print ("dispatcher: [TODO] dispatchCurrent\n"); 
    //current_thread = current_thread;
    goto do_dispatch;


//
//  ##  DO DISPATCH ##
//

//----------------------------------------
// Do Dispatch: Dispatch 'current_thread'.
//----------------------------------------

do_dispatch:

    // slot

    if ( current_thread < 0 || current_thread >= THREAD_COUNT_MAX )
    {
        panic("dispatcher-do_dispatch: [FAIL] current_thread\n");
    }

    // Struct

    dispatch_Pointer = (void *) threadList[current_thread];

    if ( (void *) dispatch_Pointer == NULL ){
        panic ("dispatch-dispatcher: struct\n");
    }

    // State

    if ( dispatch_Pointer->state != READY ){
        panic ("dispatch-dispatcher: [ERROR] State\n");
    }


    // #importante
    // >> MOVEMENT 4 (Ready --> Running).
    // A thread passa para o estado RUNNING.
    // Reinicia a contagem.


    if ( dispatch_Pointer->state == READY )
    {
        dispatch_Pointer->state = RUNNING;
        dispatch_Pointer->runningCount = 0;

        //queue_insert_data ( queue, 
            //(unsigned long) dispatch_Pointer, QUEUE_RUNNING );
    }


//
// ## RESTORE CONTEXT ##
//

    // Flag sinalizando que o contexto não está mais salvo.
    // Esse flag é acionada quando o contexto é salvo no início 
    // da task switch.

    dispatch_Pointer->saved = FALSE;

    // Chama a rotina que colocará as informações da estrutura de thread 
    // nas variáveis usadas pelo assembly para configurar 
    // os registradores antes do iretd.

    restore_current_context();

// #todo
// Change the return type and return with error
// if something goes wrong. So this way we can try another thing.
    //return 0;

    return;
}





























