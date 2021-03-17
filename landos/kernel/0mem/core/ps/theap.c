/*
 * File: ps/theap.c
 *
 *     THM - Thread Heap Manager.
 *
 *    Cada desktop tem seu próprio heap de memória. Uma thread usa o heap de 
 * memória herdado do seu processo. Um processo usa o heap de memória herdado 
 * pelo seu desktop. Então antes de tudo deve-se alocar memória par ao desktop.
 *
 *    Cada thread tem seu heap de memória. ??
 *
 * Obs: No gerenciamento de memória tem rotinas de tratamento de heap. 
 *
 * Observação sobre o tamanho do heap:
 *     O tamanho do heap do processo kernel atualmente é bem pequeno,
 * 1MB, porém o heap de um processo pode ser bem maior e com possibilidade 
 * de aumentar. Isso facilita a alocação em tempo de execução. Pois cada 
 * processo poderá aloca memória dentro do seu próprio heap e no heap do 
 * desktop que ele pertence. Ou ainda o desktop poderia doar heap para o 
 * processo que precise de mais heap. 
 *     O tanto de heap que os processos podem receber à mais, está limitado 
 * ao tamanho do heap do desktop ao qual ele pertence.
 *
 * History:
 *     2015 - Created by Fred Nora.
 */


#include <kernel.h>


//
// Variáveis internas.
//

//int thmStatus;
//int thmError;
//...


/*
    @todo:
        +Set thread heap start.
	    +Set thread heap end.
		+Get thread heap start.
	    +Get thread heap end.
		//...		
		
*/


/*
void *theapGetHeapPointer(struct thread_d *thread);
void *theapGetHeapPointer(struct thread_d *thread)
{
    if((void*) thread == NULL)
	{
        return NULL;        
	};

	return (void *) thread->heap;
};
*/

/*
void *theapSetHeapPointer(struct thread_d *thread, struct heap_d heap);
void *theapSetHeapPointer(struct thread_d *thread, struct heap_d heap)
{
    if((void*) thread == NULL){
        return;        
	};

	thread->heap = (void*) heap;
	return;
};
*/


//@todo:
//unsigned long GetThreadHeapSize(struct thread_d *thread)
//{};


//@todo:
//unsigned long GetThreadHeapEnd(struct thread_d *thread)
//{};


/*
 * GetThreadHeapStart:
 *     Obtem o início do heap de uma thread.
 *     Return 0 if error.
 *     @todo: Mudar para theapGetStart(.).
 */
//unsigned long theapGetStart(struct thread_d *thread) 

unsigned long GetThreadHeapStart ( struct thread_d *thread )
{

    if ((void*) thread == NULL)
    {
        // message?
        return (unsigned long) 0;
    }

	//@todo:
    //return (unsigned long) thread->heap->HeapStart;

    return (unsigned long) thread->Heap;
}


//
// End.
//

