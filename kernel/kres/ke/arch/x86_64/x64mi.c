
// mi.c
// Maskable interrups
// see: sw1.asm

#include <kernel.h>

// Globals
// We got these values at the interrupt time.
// See: sw.asm.
unsigned long sci0_cpl=0;
unsigned long sci1_cpl=0;
unsigned long sci2_cpl=0;
unsigned long sci3_cpl=0;

// ----------------------------------------

// This is the handler for the interrupt 0x80.
// Called by the assembly code.
void *mi80h ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{
    pid_t current_process = (pid_t) get_current_pid();
    int cpl = -1;

// -----------
//cpl
    unsigned long *cpl_buffer = (unsigned long *) &sci0_cpl;

    unsigned long tmp_cpl = (unsigned long) cpl_buffer[0];
    cpl = (int) (tmp_cpl & 3);

    if ( cpl != 0 && cpl != 1 && cpl != 2 && cpl != 3 )
    {
        panic("mi80h: cpl");
    }

    if (cpl == 0){
        printk("number=%d\n",number);
        printk("pid=%d\n",current_process);
        //if(current_process != 0){
            panic("mi80h: cpl 0\n");
        //}
    }
    if (cpl == 1){
        panic("mi80h: cpl 1\n");
    }
    if (cpl == 2){
        panic("mi80h: cpl 2\n");
    }
    if (cpl == 3){
        // ok
    }
// -----------

    return (void*) sci0(number,arg2,arg3,arg4);
}

// This is the handler for the interrupt 0x81.
// Called by the assembly code.
void *mi81h ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{
    pid_t current_process = (pid_t) get_current_pid();
    int cpl = -1;

//--------------
//cpl
    unsigned long *cpl_buffer = (unsigned long *) &sci1_cpl;
    unsigned long tmp_cpl = (unsigned long) cpl_buffer[0];
    cpl = (int) (tmp_cpl & 3);

    if( cpl != 0 && cpl != 1 && cpl != 2 && cpl != 3 )
    {
        panic("mi81h: cpl");
    }

    if(cpl == 0){
        panic("mi81h: cpl 0\n");
    }
    if(cpl == 1){
        panic("mi81h: cpl 1\n");
    }
    if(cpl == 2){
        panic("mi81h: cpl 2\n");
    }
    if(cpl == 3){
        // ok
    }
//-----------------

    return (void*) sci1(number,arg2,arg3,arg4);
}

// This is the handler for the interrupt 0x82.
// Called by the assembly code.
void *mi82h ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{
    pid_t current_process = (pid_t) get_current_pid();
    int cpl = -1;

// --------------
//cpl
    unsigned long *cpl_buffer = (unsigned long *) &sci2_cpl;
    unsigned long tmp_cpl = (unsigned long) cpl_buffer[0];
    cpl = (int) (tmp_cpl & 3);

    if ( cpl != 0 && cpl != 1 && cpl != 2 && cpl != 3 )
    {
        panic("mi82h: cpl");
    }

    if (cpl == 0){
        panic("mi82h: cpl 0\n");
    }
    if (cpl == 1){
        panic("mi82h: cpl 1\n");
    }
    if (cpl == 2){
        panic("mi82h: cpl 2\n");
    }
    if (cpl == 3){
        // ok
    }
// --------------

    return (void*) sci2(number,arg2,arg3,arg4);
}

// This is the handler for the interrupt 0x83.
// Called by the assembly code.
void *mi83h ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{
    pid_t current_process = (pid_t) get_current_pid();
    int cpl = -1;

//-------
//cpl
    unsigned long *cpl_buffer = (unsigned long *) &sci3_cpl;
    unsigned long tmp_cpl = (unsigned long) cpl_buffer[0];
    cpl = (int) (tmp_cpl & 3);

    if( cpl != 0 && cpl != 1 && cpl != 2 && cpl != 3 )
    {
        panic("mi83h: cpl");
    }

    if(cpl == 0){
        panic("mi83h: cpl 0\n");
    }
    if(cpl == 1){
        panic("mi83h: cpl 1\n");
    }
    if(cpl == 2){
        panic("mi83h: cpl 2\n");
    }
    if(cpl == 3){
        // ok
    }
//-------

    return (void*) sci3(number,arg2,arg3,arg4);
}


