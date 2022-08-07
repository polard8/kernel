
// main file for the ring 0 kernel module.
// called by ./crt0.c

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

int module_main( int reason )
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

    unsigned long *functions = (unsigned long *) __function_table;
    int DIE=0;      //it works
    int PUTCHARK=1; //it works
    int REBOOT=2;   //it works
    // #todo: Call dead thread collector, scheduler ...
    // read flags
    // read messages
    // ...
    if (Found==1)
    {
        //caller( (unsigned long) functions[DIE] );
        //caller( (unsigned long) functions[PUTCHARK] );
        //caller( (unsigned long) functions[REBOOT] );
        //do_int3();
    }


    if (reason==1){
        return 0;
    }

    while(1){
        // Relax
        //do_hlt();
    };

    return 0;
}



