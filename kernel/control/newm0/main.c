
// main file for the ring 0 kernel module.
// called by ./crt0.c
// #todo: Do not use 'interrupts'.

struct module_initialization_d
{
    int initialized;
    //unsigned long ksysmboltable_address;
};
struct module_initialization_d  ModuleInitialization;


// kernel sysboltable address.
// unsigned long imported_functions[32];
unsigned long *kfunctions;
int DIE=0;      //it works
int PUTCHARK=1; //it works
int REBOOT=2;   //it works
int REFESHSCREEN=3;
    // #todo: Call dead thread collector, scheduler ...
    // read flags
    // read messages
    // ...

inline void do_int3(void)
{
    asm ("int $3");
}

inline void do_hlt(void)
{
    asm ("hlt");
}

void caller(unsigned long function_address)
{
    asm("call *%0" : : "r"(function_address));
}


int module_print( char *string );
int module_print( char *string )
{
    //#todo: We nned to send an argument to the kernel function.
    caller( (unsigned long) kfunctions[PUTCHARK] );
    return 0;
}


//
// main:
//

int module_main(int reason)
{

// The kernel entry point.
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
        for (i=0; i<100; i++)
            caller( (unsigned long) kfunctions[PUTCHARK] );
        
        //caller( (unsigned long) kfunctions[DIE] );
        //caller( (unsigned long) kfunctions[PUTCHARK] );
        //caller( (unsigned long) kfunctions[REBOOT] );
        //do_int3();
    }


// #todo:
// Call a function sending a pointer to a vector
// where the kernel will put all the exported functions.

    //unsigned long imported_functions[32];


    if (reason==1){
        return 0;
    }

    //while(1){
        // Relax
        //do_hlt();
    //};

    return 0;
}



