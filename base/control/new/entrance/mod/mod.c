
// mod.c

#include <kernel.h>

// Cross Pointer
#define XP_MOD0    0x30A01000

// Modulo 0.
// see: kernel.h
struct kernel_module_d  *kernel_mod0;


unsigned long kmList[KMODULE_MAX];


static void 
caller1(
    unsigned long function_address, 
    unsigned long data0 );

// ----------------------------------------


static void 
caller1(
    unsigned long function_address, 
    unsigned long data0 )
{
// #todo
// + Maybe return 'unsigned long'.
// + Maybe share data via shared memory
//   using a big buffer for that.
// + Maybe share the pointer of the buffer of a file.
// ...

// 32bit
    unsigned int x = (unsigned int) (data0 & 0xFFFFFFFF);
    unsigned int y = (unsigned int) (data0 & 0xFFFFFFFF);

// #todo: Simplify

    asm ("movl %1, %%eax;"
         "movl %%eax, %0;"
         "movl %%eax, %%edi;"
         :"=r"(y)        /* output */
         :"r"(x)         /* input */
         :"%eax"         /* clobbered register */
    );   

    //asm (" movq $65, %rdi ");
    
    asm ("call *%0" : : "r"(function_address));
}



// mod0: Call the entrypoint of the module.
// mod0.bin entry point.
// When this module was loaded?
// see: I_x64CreateKernelProcess in x64init.c
// see: control/newmod0/

void test_mod0(void)
{
    printf ("test_mod0:\n");

    if ( (void*) kernel_mod0 != NULL )
    {
        if (kernel_mod0->magic == 1234)
        {
            if (kernel_mod0->initialized == TRUE)
            {
                //while(1){
                // No return value.
                // 1 parameter.
                // reason=1000. (Initialize)
                caller1((unsigned long) XP_MOD0, 1000 );
                // reason=1001. (test)
                caller1((unsigned long) XP_MOD0, 1001 );
                // Invalid reason
                caller1((unsigned long) XP_MOD0,  999 );
                //};
            }
        }
    }
}



