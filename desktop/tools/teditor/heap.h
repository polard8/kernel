/*
 * File: heap.h
 *
 * Descrição:
 *     Suporte ao gerenciamento de heap na api de 32bit.
 *     O propósito desse header é dar suporte ao gerenciamento de
 * do heap que será usado para a alocação de memória para um programa
 * em user mode. Suporte oferecido pela API.
 *     Obs: O kernel poderá usar tanto o heap do processo quanto o heap 
 * do desktop ao qual o processo pertence.
 * 
 * Histórico:
 *     Versão 1.0, 2016 - Esse arquivo foi criado por Fred Nora.
 */
 
/*
 * Sobre Heap em user mode:
 * =======================
 *     @todo: Quando um processo é inicializado, deve-se criar um Heap de
 * 1MB para ele.
 *     @todo: Funções de gerência: heapCreate, heapAlloc, heapFree, heapSize ...    
 *    
 */ 
 
static unsigned long Heap;
static unsigned long ProcessHeap;
static unsigned long DesktopHeap;
//...


//@todo: Criar a estrutura. (copiar do kernel)

//
// Fim.
//

