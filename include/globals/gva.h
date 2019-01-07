
//gva.h 
//Endereços virtuais usados pelo kernel base.


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


// Os três primeiros gigas da memória virtual.
//Os endereços virtuais aqui serão usados pelas aplicações.


//idle thread. (init process) ( SIZE = 0x4FFF0 ) 319KB
#define GRAMADOCORE_IDLETHREAD_STACK       0x0044FFF0  //pilha
#define GRAMADOCORE_IDLETHREAD_ENTRYPOINT  0x00401000  //entrypoint

//shell thread (shell process) ( SIZE = 0x4FFF0 ) 319KB
#define GRAMADOCORE_SHELLTHREAD_STACK       0x0049FFF0   //pilha
#define GRAMADOCORE_SHELLTHREAD_ENTRYPOINT  0x00451000   //entry point


//taskman thread (taskman process) ( SIZE = 0x5FFF0 ) 383KB
#define GRAMADOCORE_TASKMANTHREAD_STACK       0x004FFFF0   //pilha
#define GRAMADOCORE_TASKMANTHREAD_ENTRYPOINT  0x004A1000   //entry point


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
// ## KERNEL HEAP ##
//

//kernel heap.(Endereço virtual do heap do processo Kernel).
//O heap deve começa depois do kernel e antes da pilha..
// heapstart = kernelstart + kernel size 
//considerando o kernel de 1 mega

#define KERNEL_HEAP_START  (0xC0000000 + 0x100000)   //kernel start + kernel size.
#define KERNEL_HEAP_END    (0xC02FFFF0 - 0x8000)     //stack start - stack size
#define KERNEL_HEAP_SIZE   (KERNEL_HEAP_END - KERNEL_HEAP_START)


//
// ## KERNEL STACK ##
//

//@todo: Crir estrutura de pilha.
//kernel stack. (Endereço virtual da pilha do processo Kernel).
//Obs: O Heap e a Stack estão dentro dos limites de 4MB de
//tamanho da imagem do kernel base.
//32kb
#define KERNEL_STACK_SIZE   0x8000                                      
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



#define XXXPAGEDPOOL_VA 0xC0C00000

#define XXXHEAPPOOL_VA 0xC1000000

#define XXXGRAMADOCORE_INIT_HEAP_VA      0xC1400000
#define XXXGRAMADOCORE_SHELL_HEAP_VA     0xC1800000
#define XXXGRAMADOCORE_TASKMAN_HEAP_VA   0xC1C00000


//Cache do sistema.
#define SYSTEM_CACHE_START (0xCA000000)
#define SYSTEM_CACHE_END   (0xCAFFFFF0)


#define NIC1_VA 0xF0000000  //





