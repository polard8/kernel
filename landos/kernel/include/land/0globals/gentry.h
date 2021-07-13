
//gentry.h
// números de entradas em diretórios de páginas e tabelas de páginas.

// #bugbug
// Isso pertence à arquitetura Intel.
// Deveria estar em outro lugar.

//...


// #bugbug
// #todo
// Atenção: 
// Para x86_64 teremos outros números para esses mesmos nomes.


#ifndef ____GENTRY_H
#define ____GENTRY_H  1


// Número das entradas no diretório principal.
// Usado para mapear as regiões principais de memória virtual.
// See: pages.c
#define PD_ENTRY_RING0AREA    0
#define PD_ENTRY_RING3AREA    1
#define PD_ENTRY_KERNELIMAGE  384
#define PD_ENTRY_FRONTBUFFER  385
#define PD_ENTRY_BACKBUFFER   386
#define PD_ENTRY_PAGEDPOOL    387
#define PD_ENTRY_HEAPPOOL     388
#define PD_ENTRY_EXTRAHEAP1   389
#define PD_ENTRY_EXTRAHEAP2   390
#define PD_ENTRY_EXTRAHEAP3   391



//
//  ## User Area ##
//

//Os dois primeiros gigas.
//


#define ENTRY_KERNELMODE_PAGES       0
#define KERNEL_PAGE_DIRECTORY_ENTRY  0    // 4 primeiros megas em kernel mode.

#define ENTRY_USERMODE_PAGES           1
#define USERMODE_PAGE_DIRECTORY_ENTRY  1    // 4 megas em user mode.

#define ENTRY_CGA_PAGES           2
#define CGA_PAGE_DIRECTORY_ENTRY  2    // CGA

//256
//Se o programa do processo for carregado aqui, então ele pode 
//ter até 2GB de tamanho.


//512
//Se o programa do processo for carregado aqui, então ele pode 
//ter até 1GB de tamanho.


//
//  ## System Area ##
//



// À partir do terceiro giga.
// O sistema deve gerenciar tudas as suas coisas 
// nesse giga superior da memoria virtual.

//0xC0000000
#define ENTRY_KERNELBASE_PAGES 768
#define KERNEL_IMAGE_PAGE_DIRECTORY_ENTRY  768  // A imagem do kernel.


//0xC0400000
#define ENTRY_FRONTBUFFER_PAGES 769 
#define LFB_PAGE_DIRECTORY_ENTRY           769  // Frontbuffer.

//0xC0800000
#define ENTRY_BACKBUFFER_PAGES  770
#define BACKBUFFER_PAGE_DIRECTORY_ENTRY    770  // Backbuffer.


// pool
// 0xC0C00000
#define ENTRY_PAGEDPOOL_PAGES 771   


// 0xC1000000
#define ENTRY_HEAPPOOL_PAGES  772    


//0xC1400000
#define ENTRY_EXTRAHEAP1_PAGES     773

//0xC1800000
#define ENTRY_EXTRAHEAP2_PAGES     774

//0xC1C00000
#define ENTRY_EXTRAHEAP3_PAGES     775




#define ENTRY_NIC1_PAGES 960 
#define ENTRY_AHCI1_PAGES 961 


#endif   




