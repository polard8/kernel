// File: ps/tasks.c
// #todo
// Devemos reaproveitar esse arquivo,
// mas com outro nome e outro proposito.


#include <kernel.h>


void task0 (void)
{
    //printf ("Thread started\n"); 
    while(1){ asm("hlt"); }
}

void task1 (void)
{
    //printf("Thread started\n"); 
    while(1){ asm("hlt"); }
}


//
// End.
//

