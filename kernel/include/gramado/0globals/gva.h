

#ifndef ____GVA_H
#define ____GVA_H    1


    // #todo
    // Tem um monte de endereços usados no início da 
    // memoria virtual do kernel. Mas acontece que esses
    // endereços são os mesmos para físico e virtual.
    // então precisamos estar concordância com os endereços
    // encontrados em gpa.h 


// mbr
#define MBR_ADDRESS_VA    0x00020000  

// vbr
//Podemos alocar memória para isso, liberando esse espaço?
#define VOLUME1_VBR_ADDRESS_VA   (0x00020000 + 0x200) 
#define VOLUME2_VBR_ADDRESS_VA   (0x00020000 + 0x200) 

// fat
//Podemos alocar memória para isso, liberando esse espaço?
#define VOLUME1_FAT_ADDRESS_VA   0x00030000 
#define VOLUME2_FAT_ADDRESS_VA   0x00030000

// rootdir
//Podemos alocar memória para isso, liberando esse espaço?
#define VOLUME1_ROOTDIR_ADDRESS_VA  0x00070000 
#define VOLUME2_ROOTDIR_ADDRESS_VA  0x00070000 




//
// process support.
//



// #test 
// Isso será usado por todos os processos em ring3
// no ambiente do sistema principal.
#define CONTROLTHREAD_BASE        0x00200000  // base
#define CONTROLTHREAD_ENTRYPOINT  0x00201000  // entry point
// Stack do processo em ring3.
// Lembre-se que o processo vai precisa de um heap.
#define CONTROLTHREAD_STACK       0x003FFFF0  // stack 


// Isso porque endereços físicos e virtuais são igual para
// baixo de 1 mb.
#define KERNEL_PML4_VA 0x000000000009C000


// ==============================================================


//
// Main regions
//

// See: pages.c
#define RING0AREA_VA    0
#define RING3AREA_VA    0x0000000000200000
#define KERNELIMAGE_VA  0x0000000030000000  
#define FRONTBUFFER_VA  0x0000000030200000
#define BACKBUFFER_VA   0x0000000030400000
#define PAGEDPOOL_VA    0x0000000030600000
#define HEAPPOOL_VA     0x0000000030800000
#define EXTRAHEAP1_VA   0x0000000030A00000
#define EXTRAHEAP2_VA   0x0000000030C00000
#define EXTRAHEAP3_VA   0x0000000030E00000



// The start of the kernel image virtual address.
#define KERNEL_IMAGE_BASE  KERNELIMAGE_VA  
#define KERNBASE           KERNELIMAGE_VA

// Entry point
// Start of kernel text.
#define KERNTEXTOFF  (KERNBASE + 0x1000)


//
// heap and stack  (va)
//

// heap
#define KERNEL_HEAP_START  0x30100000 
#define KERNEL_HEAP_END    0x301D0000
#define KERNEL_HEAP_SIZE   (KERNEL_HEAP_END - KERNEL_HEAP_START)

// Tem um espaço perdido para
// evitar colisão.

// stack
#define KERNEL_STACK_END    0x301E0000
#define KERNEL_STACK_START  0x301FFFF0 
#define KERNEL_STACK_SIZE   (KERNEL_STACK_START-KERNEL_STACK_END)


// Frontbuffer
// Endereço virtual padrão para o Linear Frame Buffer. (LFB).
#define DEFAULT_LFB_VIRTUALADDRESS  FRONTBUFFER_VA 
#define FRONTBUFFER_ADDRESS         FRONTBUFFER_VA

// Backbuffer
//Endereço virtual padrão para o BackBuffer. (buffer1)
#define DEFAULT_BACKBUFFER_VIRTUALADDRESS  BACKBUFFER_VA
#define BACKBUFFER_ADDRESS                 BACKBUFFER_VA


// ==============================================================


#endif    





