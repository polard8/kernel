
//gva.h 
//Endereços virtuais usados pelo kernel base.


#ifndef ____GVA_H
#define ____GVA_H 1



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



// #importante 
// Essas pagetable possuem endereço físico e lógico iguais.


// Page tables.
// ?? estao sendo usadas no momento ou nao?
//#define PAGETABLE_RES7  0x00080000
#define PAGETABLE_RES6_VA    0x00081000
#define PAGETABLE_RES5_VA    0x00082000


// Tentando mapear alguma coisa para ahci.
// AHCI 1
#define PAGETABLE_AHCI1_VA  0x00083000   


// Extra heaps.
#define PAGETABLE_EXTRAHEAP3_VA  0x00084000
#define PAGETABLE_EXTRAHEAP2_VA  0x00085000
#define PAGETABLE_EXTRAHEAP1_VA  0x00086000


// pagetable para mapear um pool de heaps.
#define PAGETABLE_HEAPPOOL_VA     0x00087000 

// Page table para mapear um NIC.
#define PAGETABLE_NIC1_VA  0x00088000


// Pagetable para mapear um pool.
// Possivelmente usado por um alocador de memoria compartilhada.
#define PAGETABLE_PAGEDPOOL_VA  0x00089000

// Pagetable para o backbuffer.
// Esse eh o backbuffer que copiamos para o lfb.
#define PAGETABLE_BACKBUFFER_VA  0x0008A000

// pagetable para o lfb.
#define PAGETABLE_FRONTBUFFER_VA  0x0008B000

// Pagetable para o CGA em user mode.
// Aquele memoria de modo texto colorido.
#define PAGETABLE_CGA_VA  0x0008C000

// Pagetable para mapear uma area de memoria 
// que sera usada pelos aplicativos em user mode.
#define PAGETABLE_USERBASE_VA  0x0008D000

// Pagetable para mapear o endereço onde a imagem do kernel
// sera carregada na memoria fisica.
#define PAGETABLE_KERNELBASE_VA  0x0008E000

// Pagetable para mapear os primeiros 4MB de memoria fisica.
// ring0. 1:1
#define PAGETABLE_KERNELAREA_VA 0x0008F000



// ==========================================

//Endereço virtual do diretório de páginas do processo kernel.
//Como aqui ficam as coisas de usuário,
//termos que mapear o diretório de páginas do kernel em outro lugar.
#define PD_BASE 0x0009C000

//Aqui é onde fica a primeira entrada.
#define PTE_BASE 0x0009C000



//
// process support.
//


#define CONTROLTHREAD_BASE        0x00400000  // base
#define CONTROLTHREAD_ENTRYPOINT  0x00401000  // entry point
#define CONTROLTHREAD_STACK       0x007FFFF0  // stack



//...

//0x80000000 ??

//############################################################################
//
//  ## System Area ##
//

// O útimo giga da memória virtual.
//Os endereços virtuais aqui serão usados por componentes do sistema.

//Base da imagem do kernel.
#define KERNEL_IMAGE_BASE  0xC0000000  

//Essa é a área onde a imagem do kernel está,
//Ela pode ter no máximo 1 MB.
//O código do kernel tem 1MB de tamanho,
//logo em seguida começa o heap;
#define CODE_START  0xC0000000   //0x100000pys  
#define CODE_END    0xC00FFFFF   //0x1FFFFFpys  
#define CODE_SIZE (CODE_END-CODE_START)


//
// #importante
// Vamos testar outro tamanho de stack para o kernel.
// Mudaremos de 8KB para 128KB.
// 0x8000 0x20000
//



//
// ## KERNEL HEAP ##
//

//kernel heap.(Endereço virtual do heap do processo Kernel).
//O heap deve começa depois do kernel e antes da pilha..
// heapstart = kernelstart + kernel size 
//considerando o kernel de 1 mega

#define KERNEL_HEAP_START  (0xC0000000 + 0x100000)   //kernel start + kernel size.
#define KERNEL_HEAP_END    (0xC02FFFF0 - 0x20000)    //(0xC02FFFF0 - 0x8000)     //stack start - stack size
#define KERNEL_HEAP_SIZE   (KERNEL_HEAP_END - KERNEL_HEAP_START)


//
// ## KERNEL STACK ##
//

//@todo: Crir estrutura de pilha.
//kernel stack. (Endereço virtual da pilha do processo Kernel).
//Obs: O Heap e a Stack estão dentro dos limites de 4MB de
//tamanho da imagem do kernel base.
//32kb
#define KERNEL_STACK_SIZE   0x20000  //0x8000                                      
#define KERNEL_STACK_START  0xC02FFFF0                                        
#define KERNEL_STACK_END    (KERNEL_STACK_START - KERNEL_STACK_SIZE)  


//Endereço virtual padrão para o Linear Frame Buffer. (LFB).
#define DEFAULT_LFB_VIRTUALADDRESS  0xC0400000 
#define FRONTBUFFER_ADDRESS         0xC0400000
#define FRONTBUFFER_VA              0xC0400000



//Endereço virtual padrão para o BackBuffer. (buffer1)
#define DEFAULT_BACKBUFFER_VIRTUALADDRESS  0xC0800000
#define BACKBUFFER_ADDRESS                 0xC0800000
#define BACKBUFFER_VA                      0xC0800000


//#IMPORTANTE
//Essa área de memória compartilhada tem sido usada pelos processos
//para troca de mensagens. O shell está passando a linha de comandos.
//#bugbug: Isso tá dentro da memória de vídeo, que são 4MB e começa em 0xC0400000. 
//#define SHARED_MEMORY (0xC0800000 -0x100)

#define XXXPAGEDPOOL_VA  0xC0C00000

#define XXXHEAPPOOL_VA  0xC1000000

#define XXXEXTRAHEAP1_VA    0xC1400000
#define XXXEXTRAHEAP2_VA    0xC1800000
#define XXXEXTRAHEAP3_VA    0xC1C00000


//Cache do sistema.
#define SYSTEM_CACHE_START  (0xCA000000)
#define SYSTEM_CACHE_END    (0xCAFFFFF0)


#define NIC1_VA   0xF0000000  //
#define AHCI1_VA  0xF0400000  //


#endif    


