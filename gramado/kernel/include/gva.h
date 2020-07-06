
//gva.h 
//Endereços virtuais usados pelo kernel base.


#ifndef ____GVA_H
#define ____GVA_H 1



// #importante: PERIGO !!!
// O sistema está usando esse endereço como início de um heap
// onde pegamos páginas de memória para criarmos diretórios de páginas.
// Isso porque precisamos de endereços que terminem com pelo menos 
// 12bits zerados.
// #todo: Precisamos encontrar outro lugar para esse heap, tendo em vista que
// o nómero de diretórios criados será grande e o heap invadirá outras áreas.
// me parece que o pŕoximo endereço usado é o MBR em 0x00020000. 
// #todo: Possivelmente podemos mudar o MBR de lugar usando o alocador.
// #OBS: Os endereços físico e virtual são iguais.
// #define CREATE_DIRECTORY_HEAP_BASE 0x1000




//############################################################################
//
//  ## User Area ##
//


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

#define XXXPAGEDPOOL_VA 0xC0C00000

#define XXXHEAPPOOL_VA 0xC1000000


#define XXXEXTRAHEAP1_VA      0xC1400000
#define XXXEXTRAHEAP2_VA     0xC1800000
#define XXXEXTRAHEAP3_VA   0xC1C00000





//Cache do sistema.
#define SYSTEM_CACHE_START (0xCA000000)
#define SYSTEM_CACHE_END   (0xCAFFFFF0)


#define NIC1_VA 0xF0000000  //
#define AHCI1_VA 0xF0400000  //


#endif    


