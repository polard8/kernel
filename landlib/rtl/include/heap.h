/*
 * File: heap.h
 *
 * Descrição:
 *     O propósito desse header é dar suporte ao gerenciamento de
 * do heap que será usado para a alocação de memória para um programa
 * em user mode. 
 *     Um suporte oferecido pela biblioteca libC99.
 *     Obs: O kernel poderá usar tanto o heap do processo quanto o heap 
 * do desktop ao qual o processo pertence.
 * 
 * History:
 *     2016 - Created by Fred Nora.
 */

#ifndef __HEAP_H
#define __HEAP_H  1



//Contagem de heap.
#define HEAP_COUNT_MAX  256 


unsigned long HEAP_START; 
unsigned long HEAP_END;
unsigned long HEAP_SIZE;
 
//@todo: padronizar 
unsigned long heapCount;            //Conta os heaps da stdlib.

unsigned long heap_start;    //Start.
unsigned long heap_end;      //End.

unsigned long g_heap_pointer;       //Pointer.
unsigned long g_available_heap;     //Available. 
 
 
// 
// Heap pointer:
//     Isso deve apontar para o heap buffer atual. Quando acabar o heap atual
// deve-se chamar o kernel para criar mais heap dentro da working set do processo. 
//
 
void *Heap;    


//
// *** HEAP ***
//

#define HEAP_BUFFER_SIZE (32*1024)  // 32KB, provisório.

static unsigned char HeapBuffer[HEAP_BUFFER_SIZE]; 



/*
 * heap_d:
 *     Estrutura para heap.
 *     Cada processo tem seu heap.
 *     Cada heap tem uma lista encadeada de blocos.  
 */

struct heap_d 
{
    int Id;
    
    int Used;
    int Magic;

    unsigned long HeapStart;
    unsigned long HeapEnd;

    unsigned long HeapPointer;
    unsigned long AvailableHeap; 

    //lista linkada de blocos. 
    //struct mmblock_d *nextblock; 
};
struct heap_d *libcHeap;
//...


//Heap list.
//obs:. heapList[0] = The Kernel Heap !
unsigned long heapList[HEAP_COUNT_MAX];


//
// == prototypes ===============================================
//

int heapInit(void);
void heapSetLibcHeap( unsigned long HeapStart, unsigned long HeapSize);


//
// Alloc and Free.
//

unsigned long heapAllocateMemory ( unsigned long size );

unsigned long FreeHeap( unsigned long size );


#endif    


//
// End.
//

