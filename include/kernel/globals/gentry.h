
//gentry.h
// números de entradas em diretórios de páginas e tabelas de páginas.

 

//...


//
//  ## User Area ##
//

//Os dois primeiros gigas.
//


#define ENTRY_KERNELMODE_PAGES  0
#define KERNEL_PAGE_DIRECTORY_ENTRY        0    // 4 primeiros megas em kernel mode.


#define ENTRY_USERMODE_PAGES    1
#define USERMODE_PAGE_DIRECTORY_ENTRY      1    // 4 megas em user mode.


#define ENTRY_VGA_PAGES         2
#define VGA_PAGE_DIRECTORY_ENTRY           2    // VGA

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

#define ENTRY_KERNELBASE_PAGES 768
#define KERNEL_IMAGE_PAGE_DIRECTORY_ENTRY  768  // A imagem do kernel.

#define ENTRY_FRONTBUFFER_PAGES 769 
#define LFB_PAGE_DIRECTORY_ENTRY           769  // Frontbuffer.

#define ENTRY_BACKBUFFER_PAGES  770
#define BACKBUFFER_PAGE_DIRECTORY_ENTRY    770  // Backbuffer.

#define ENTRY_PAGEDPOOL_PAGES 771

#define ENTRY_HEAPPOOL_PAGES  772


#define ENTRY_GRAMADOCORE_INIT_PAGES     773
#define ENTRY_GRAMADOCORE_SHELL_PAGES    774
#define ENTRY_GRAMADOCORE_TASKMAN_PAGES  775

#define ENTRY_NIC1_PAGES 960 
#define ENTRY_AHCI1_PAGES 961 




