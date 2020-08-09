// File: tasks.c
// Nothing. Delete it!


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

