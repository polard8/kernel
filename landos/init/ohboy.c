
// system call.
void *ohboy_system_call ( 
    unsigned long a, 
    unsigned long b, 
    unsigned long c, 
    unsigned long d )
{
    long __Ret = 0;

    // System interrupt.

    asm volatile ( " int %1 \n"
                 : "=a"(__Ret)
                 : "i"(0x80), "a"(a), "b"(b), "c"(c), "d"(d) );

    return (void *) __Ret; 
}


void main(void)
{
    
    // #todo
    // This is a place for 

    ohboy_system_call(0,0,0,0);
    //ohboy_system_call(0,0,0,0);
    //ohboy_system_call(0,0,0,0);
    //ohboy_system_call(0,0,0,0);

    //asm("int $3");
    //while(1){}

    //ohboy_system_call(0,0,0,0);
}













