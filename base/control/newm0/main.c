
// main file for the ring 0 kernel module.
// called by ./crt0.c
// #todo: Do not use 'interrupts'.

#include "newm0.h"

struct module_initialization_d  ModuleInitialization;


// kernel sysboltable address.
// unsigned long imported_functions[32];
unsigned long *kfunctions;
int DIE=0;      //it works
int PUTCHARK=1; //it works
int REBOOT=2;   //it works
int REFESHSCREEN=3;
int PUTCHAR_FGCONSOLE=4;  //(1arg)
// #todo: Call dead thread collector, scheduler ...
// read flags
// read messages
// ...

static void caller0(unsigned long function_address);
static void 
caller1(
    unsigned long function_address, 
    unsigned long data0 );

static int module_print(char *string);
static inline void do_int3(void);
static inline void do_hlt(void);

// -----------------------------

static inline void do_int3(void)
{
    asm ("int $3");
}

static inline void do_hlt(void)
{
    asm ("hlt");
}

static void caller0(unsigned long function_address)
{
    asm ("call *%0" : : "r"(function_address));
}

static void 
caller1(
    unsigned long function_address, 
    unsigned long data0 )
{

    int x = (int) (data0 & 0xFF);
    int y = (int) (data0 & 0xFF);

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


static int module_print(char *string)
{
    //#todo: We nned to send an argument to the kernel function.
    caller0( (unsigned long) kfunctions[PUTCHARK] );
    return 0;
}


//strlen
// strlen:
//    Give the string lenght in bytes.
int module_strlen(const char *s);
int module_strlen(const char *s)
{
    register int i=0;

//#todo
    //if ( (void *) s == NULL ){ return -1; }

    for ( i=0; s[i] != '\0'; ++i )
    {
    };

    return (int) i;
}


void module_print_string (char *s);
void module_print_string (char *s)
{
    register int i=0;
    int size=0;
    size = module_strlen(s);
    if (size <= 0)
        return;
    for (i=0; i<size; i++)
    {
        caller1( 
            kfunctions[PUTCHAR_FGCONSOLE], 
            s[i] 
        );
    };
}


//
// main:
//

int main( int arc, char *argv[], int reason )
{

// Invalid reason.
    if ( reason != 1000 &&
         reason != 1001 )
    {
        return -1;
    }

// The kernel static entry point.
// #bugbug: It's not safe.
// We need a random address.

    unsigned char *k = (unsigned char *) 0x30001000;

// #test
// Lookup for "__GRAMADO__"
// see: head_64.asm
    int i=0;
    int Found=0;
    unsigned long __function_table=0;
    for (i=0; i<100; i++)
    {
        if (k[i+0]  == '_' &&
            k[i+1]  == '_' &&
            k[i+2]  == 'G' &&
            k[i+3]  == 'R' &&
            k[i+4]  == 'A' &&
            k[i+5]  == 'M' &&
            k[i+6]  == 'A' &&
            k[i+7]  == 'D' &&
            k[i+8]  == 'O' &&
            k[i+9]  == '_' &&
            k[i+10] == '_')
        {
            Found = 1;
            // The function table starts here.
            __function_table = (unsigned long) &k[i+11];
        }
    };

// Symbol table 'exported' hehe by the kernel.
    //unsigned long *kfunctions = (unsigned long *) __function_table;
    kfunctions = (unsigned long *) __function_table;

    if (Found==1)
    {
        if (reason == 1000){
            module_print_string("newm0: reason 1000\n");
        }

        if (reason == 1001){
            module_print_string("newm0: reason 1001\n");
        }


        //for (i=0; i<100; i++)
        //    caller0( (unsigned long) kfunctions[PUTCHARK] );
        //caller0( (unsigned long) kfunctions[DIE] );
        //caller0( (unsigned long) kfunctions[PUTCHARK] );
        //caller0( (unsigned long) kfunctions[REBOOT] );
        //do_int3();
        //caller1( kfunctions[PUTCHAR_FGCONSOLE], 'x');
        
        return 0;
    }

fail:
    return -1;
}

