// This is a client-side library for the GNS. 



// System call.
void *
gns_system_call ( 
    unsigned long a, 
    unsigned long b, 
    unsigned long c, 
    unsigned long d )
{
    int __Ret = 0;

    //System interrupt.

    asm volatile ( " int %1 \n"
                 : "=a"(__Ret)
                 : "i"(0x80), "a"(a), "b"(b), "c"(c), "d"(d) );

    return (void *) __Ret; 
}


// Debug vai serial port. (COM1)
void gns_debug_print (char *string)
{
    gns_system_call ( 289, 
        (unsigned long) string,
        (unsigned long) string,
        (unsigned long) string );
}

void gns_yield(void)
{
    gns_system_call (265,0,0,0); //yield thread.
}




