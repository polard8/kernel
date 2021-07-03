

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

// #test #bugbug
#define CONTROLTHREAD_BASE        0x00400000  // base
#define CONTROLTHREAD_ENTRYPOINT  0x00401000  // entry point
#define CONTROLTHREAD_STACK       0x005FFFF0  // stack

// Isso porque endereços físicos e virtuais são igual para
// baixo de 1 mb.
#define KERNEL_PML4_VA 0x000000000009C000


#define KERNEL_IMAGE_BASE  0x30000000  

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


//
// LFB
//

//Endereço virtual padrão para o Linear Frame Buffer. (LFB).
#define FRONTBUFFER_VA              0x0000000030200000
#define DEFAULT_LFB_VIRTUALADDRESS  FRONTBUFFER_VA 
#define FRONTBUFFER_ADDRESS         FRONTBUFFER_VA



//
// Backbuffer
//

//Endereço virtual padrão para o BackBuffer. (buffer1)
#define BACKBUFFER_VA                      0x0000000030400000
#define DEFAULT_BACKBUFFER_VIRTUALADDRESS  BACKBUFFER_VA
#define BACKBUFFER_ADDRESS                 BACKBUFFER_VA



#endif    





