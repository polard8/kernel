/*
 * File: dispatch.h
 *
 *     Dispatcher support.
 * 
 * History:
 *     2015 - Created by Fred Nora.
 */


#ifndef __DISPATCH_H  
#define __DISPATCH_H    1


//
// Dispatcher types
//

// Used in disptcher();

#define DISPATCHER_UNDEFINED  0  // Type undefined.
#define DISPATCHER_CURRENT    1  // Dispatch the current thread.
#define DISPATCHER_IDLE       2  // Dispatch the current idle thread and select it as the current.
// ...



//Enumerador de criterio de seleção de thread.
#define SELECT_IDLE_COUNT         1
#define SELECT_INITIALIZED_COUNT  2
#define SELECT_NEXT_COUNT         3 
#define SELECT_CURRENT_COUNT      4  
#define SELECT_ANY_COUNT          5
#define SELECT_IDEAL_COUNT        6
#define SELECT_DISPATCHER_COUNT   7

/*
 * Seleciona o tipo de dispatcher sendo usado no momento.
 */
int dispatcherType;
int dispatcherQueueIndex;


//
// Contador de dispatch por categoria de dispatch.
//

struct dispatch_count_d
{
    // Quando selecionamos a idle.
    unsigned long SelectIdleCount;

    // Quando selecionamos uma thread no momento de sua inicialização.
    unsigned long SelectInitializedCount;

    // Quando selecionamos a próxima indicada na estrutura da thead.
    unsigned long SelectNextCount;

    unsigned long SelectCurrentCount;

    // Quando selecionamos uma procurando por ela.	
    unsigned long SelectAnyCount;

    // Selecionamos a melhor possivel.
    unsigned long SelectIdealCount;	

    // Quando selecionamos a proxima na fila do dispatcher.
    unsigned long SelectDispatcherQueueCount;

    // ...
};

struct dispatch_count_d  *DispatchCountBlock;


// exemplo:
// KiDispatcherReadyListHead - This is an array of type list entry. The
//      elements of the array are indexed by priority. Each element is a list
//      head for a set of threads that are in a ready state for the respective
//      priority. This array is used by the find next thread code to speed up
//      search for a ready thread when a thread becomes unrunnable. See also
//      KiReadySummary.
//

/*
 * dispatcherReadyList:
 *
 *    **** SHORT-TERM SCHEDULER FOR THREADS****
 *
 *     Esta é a lista do dispatcher.
 *     Lista ponteiros para as heads de listas.
 *     as listas são para threads, uma lista para cada prioridade.
 *
 *     *IMPORTANTE. 
 *     As threads aqui estão no estado READY e
 *     ordenadas por prioridade.
 *     
 *     A última thread da lista é a thread de maior prioridade.
 *
 *     Cada elemento dessa lita é o olemento que está na HEAD de uma lista
 *     Cada uma dessas lista é uma lista para uma prioridade específica.
 * 
 *     Apenas a head de cada uma das listas é colocada aqui nessa lista do dispacher.
 *
 *     OBS: Nesse momento essa lista do dispacher não está sendo usada.  
 *          o kernel esta usando a lista de threads criadas. threadList[]
 *          não considerando a prioridade. ;)
 */ 

unsigned long dispatcherReadyList[PRIORITY_MAX +1];


//
// == prototypes ===============================
//

void IncrementDispatcherCount ( int type );
void dispatcher ( int type );

#endif    


//
// End.
//

















