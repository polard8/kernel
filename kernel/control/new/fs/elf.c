
// fs/elf.c
// See:
// fs/exec_elf.h


#include <kernel.h>


int elfCheckSignature( unsigned long address )
{
    unsigned char *buf = (unsigned char *) address;

    if ( (void *) buf == NULL ){
        printf ("elfCheckSignature: buf \n");
        return (int) (-1);
    }

    // ELFMAG0
    if ( buf[0] != 0x7F ||
         buf[1] != 0x45 || buf[2] != 0x4C || buf[3] != 0x46 )
    {
        printf ("elfCheckSignature: Sig \n");
        return (int) (-1);
    }

    return 0;  //ok
}



