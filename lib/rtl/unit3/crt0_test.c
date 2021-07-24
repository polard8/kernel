#include <types.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>




void crt0_main(void)
{
    //ok
    gramado_system_call(4321,0xa,0xb,0xc);

    // ok
    // See: stdlib/stdlib.c
    gramado_system_call(65,'1',0,0);
    libcInitRT();

    // fail !
    // See: stdio/stdio.c
    gramado_system_call(65,'2',0,0);
    stdioInitialize();



    asm ("int $3");
    while(1){}
    return;
}



