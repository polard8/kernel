
//gva.h 


//Base da imagem do kernel.
#define KERNEL_IMAGE_BASE  0xC0000000  



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

//0x80000000 ??

#define NIC1_VA 0xF0000000  //





