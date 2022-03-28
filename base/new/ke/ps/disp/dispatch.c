
// dispatch.c


#include <kernel.h>  

/*
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
// dispatch.h

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
    struct thread_d *TargetThread;

    //debug_print (" DISPATCHER: ");

//
// type
//

// See:
// dispatch.h

//#define DISPATCHER_UNDEFINED  0  // Type undefined.
//#define DISPATCHER_CURRENT    1  // Dispatch the current thread.
//#define DISPATCHER_IDLE       2  // Dispatch the current idle thread and select it as the current.
// ...

    if ( type != DISPATCHER_CURRENT ){
        type = DISPATCHER_CURRENT;
    }

dispatch_current:

// tid
    if ( current_thread < 0 || 
         current_thread >= THREAD_COUNT_MAX )
    {
        panic("dispatcher: current_thread\n");
    }

// pointer
    TargetThread = (void *) threadList[current_thread];

    if ( (void *) TargetThread == NULL ){
        panic ("dispatcher: TargetThread\n");
    }

// state
    if ( TargetThread->state != READY ){
        panic ("dispatcher: state\n");
    }

// #importante
// >> MOVEMENT 4 (Ready --> Running).
// A thread passa para o estado RUNNING.
// Reinicia a contagem.
// Os outros elementos são reiniciados pelo caller

    if ( TargetThread->state == READY )
    {
        TargetThread->state = RUNNING;
        TargetThread->runningCount = 0;
        TargetThread->runningCount_ms = 0;
    }

//
// ## RESTORE CONTEXT ##
//

// Flag sinalizando que o contexto não está mais salvo.
// Esse flag é acionada quando o contexto é salvo no início 
// da task switch.
// Chama a rotina que colocará as informações da estrutura de thread 
// nas variáveis usadas pelo assembly para configurar 
// os registradores antes do iretd.
// #todo
// Change the return type and return with error
// if something goes wrong. So this way we can try another thing.

    TargetThread->saved = FALSE;
    restore_current_context();
    return;
    //return 0;
}

