

#ifndef ____GVA_H
#define ____GVA_H    1


//
// process support.
//

// #test #bugbug
#define CONTROLTHREAD_BASE        0x00400000  // base
#define CONTROLTHREAD_ENTRYPOINT  0x00401000  // entry point
#define CONTROLTHREAD_STACK       0x005FFFF0  // stack


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





