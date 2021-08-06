/*
 * File: mm/mmglobal.h
 *
 * Aqui terão globais para gerenciamento de memória.
 * listas páginas e frames.
 * é o acesso global a informações gerais sobre o gerenciamento de páginas.
 *
 */

#ifndef __MMGLOBAL_H
#define __MMGLOBAL_H    1


// #test
// It needs to be a global thing.

typedef unsigned long  pml4_entry_t;
typedef unsigned long  pdpt_entry_t;
typedef unsigned long  pd_entry_t;
typedef unsigned long  pt_entry_t;

/*
#define L4_MASK		0x0000ff8000000000
#define L3_MASK		0x0000007fc0000000
#define L2_MASK		0x000000003fe00000
#define L1_MASK		0x00000000001ff000
*/



#define PAGE_SHIFT  12
#define PAGE_SIZE   (1 << PAGE_SHIFT)  // 4096
//#define PAGE_MASK   (PAGE_SIZE - 1)



// #rever
// Macros para conversão de endereços.
#define PAGE_GET_DIR(addr)   ((unsigned)(addr) >> 22)
#define PAGE_GET_TAB(addr)  (((unsigned)(addr) >> 12) & 0x3FF)

/*
// Definições dos campos das páginas.
#define PAGE_PRESENT            0x001
#define PAGE_WRITE              0x002
#define PAGE_USER               0x004
#define PAGE_NOCACHE            0x010
#define PAGE_ACCESSED           0x020
#define PAGE_DIRTY              0x040
#define PAGE_GLOBAL             0x100
#define PAGE_AVAIL              0xE00
#define PAGE_PRESENT_WRITE      (PAGE_PRESENT | PAGE_WRITE)
#define PAGE_PRESENT_WRITE_USER (PAGE_PRESENT | PAGE_WRITE | PAGE_USER)
#define PAGE_KERNEL_PGPROT	(PAGE_PRESENT_WRITE)
*/


/*
 Obs: lfb é um objeto.
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

