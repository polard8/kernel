/*
 * File: mm/mmglobal.h
 * Aqui terão globais para gerenciamento de memória.
 * listas páginas e frames.
 * é o acesso global a informações gerais sobre o 
 * gerenciamento de páginas.
 */

#ifndef __MMGLOBAL_H
#define __MMGLOBAL_H    1


// #test
// It needs to be a global thing.

typedef unsigned long  pml4_entry_t;
typedef unsigned long  pdpt_entry_t;
typedef unsigned long  pd_entry_t;
typedef unsigned long  pt_entry_t;


// Selecting the bits for the given level.
// #todo: Not tested yet.
#define X64_L1_MASK  0x00000000001ff000
#define X64_L2_MASK  0x000000003fe00000
#define X64_L3_MASK  0x0000007fc0000000
#define X64_L4_MASK  0x0000ff8000000000


// We need the values for x86_64
#define PAGE_SHIFT  12
#define PAGE_SIZE   (1 << PAGE_SHIFT)  // 4096
//#define PAGE_MASK   (PAGE_SIZE - 1)

//
// Get indexes
//

// We need the values for x86_64
// #todo: 9 9 9 9 12

// OFFSET - Level 0
#define X64_GET_OFFSET(addr) \
    (((unsigned)(addr)) & 0xFFF)
// PTE - Level 1
// Desloca o offset e pegar os 9 bits do índice de pte.
#define X64_GET_PTE_INDEX(addr) \
    (((unsigned)(addr) >> (12)) & 0x1FF)
// PDE - Level 2
#define X64_GET_PDE_INDEX(addr) \
    (((unsigned)(addr) >> (12+9)) & 0x1FF)
// PDPE - Level 3
#define X64_GET_PDPE_INDEX(addr) \
    (((unsigned)(addr) >> (12+9+9)) & 0x1FF)
// PML4E - Level 4
#define X64_GET_PML4E_INDEX(addr) \
    (((unsigned)(addr) >> (12+9+9+9)) & 0x1FF)

/*
 Obs: 
 lfb é um objeto.
 Teremos um lfb por cartão de memória.

typedef struct lfb_d lfb_t;
struct lfb_d
{
	//object ...
	
	int used;
	int magic;
	
	int status;
	unsigned long address; 
};
*/

#endif   

//
// End.
//

