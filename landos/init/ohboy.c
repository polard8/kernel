
//#define	NULL	((void *)0)


#include <types.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>


static char *ohboy_argv[] = { 
    "-flag1", 
    "-flag2", 
    "-flag3", 
    "-flag4", 
    NULL 
};

static char *ohboy_environ[] = { 

    "DISPLAY=kgws-or-gwssrv",  //#todo
    "EDITOR=gramcode",
    "HOME=/HOME",
    "HOSTNAME=gramado",
    "LANG=en-us",
    "LANG2=pt-br",
    "LANGX=en-br",
    "OSTYPE=gramado",   //#todo
    "PATH=/:/PROGRAMS:/GRAMADO",
    "PS1=~$",
    "PS2=:>",
    "PWD=/",             //#bugbug: This is the working directory.
    "SHELL=gdeshell",
    "TERM=noraterm",     //#bugbug
    "TMP=/TMP",
    "UID=no-id",         //#todo
    "USER=anon",  
    NULL 
};


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
    
    
    // Get pid
    int pid = (int) ohboy_system_call(85,0,0,0);

    //get Heap address given the pid.
    void *heap;
    //heap = (void*)ohboy_system_call(184,0,0,0);
    heap = (void*)gramado_system_call(184,pid,pid,pid);  //#test: Tentando usar a libc

    // Heap not valid.
    if ( (void*) heap == NULL )
        ohboy_system_call(65,'N',0,0);

    // Valid heap.
    if ( (void*) heap != NULL )
        ohboy_system_call(65,'Y',0,0);

    //ohboy_system_call(49,0,0,0);

    // console put char
    // ohboy_system_call(65,'x',0,0);

    //asm("int $3");
    //while(1){}

    // reboot
    //ohboy_system_call(110,0,0,0);

    // Debug on serial
    //char *s="fred";
    //ohboy_system_call(289,s,s,s);

    // Exit
    //ohboy_system_call(70,0,0,0);
    //while(1){
    //    ohboy_system_call(289,s,s,s);
    //}

    // List files.
    //ohboy_system_call(173,0,0,0);
  
  
  
// =================================================


//
// Initializing the ring3 libc.
//

    // Environment.
    environ = ohboy_environ;


//
// #todo
//


    // ok
    // See: stdlib/stdlib.c
    ohboy_system_call(65,'1',0,0);
    libcInitRT();

    // fail !
    // See: stdio/stdio.c
    ohboy_system_call(65,'2',0,0);
    stdioInitialize();

    //#fail
    //debug_print("Fred\n");

    //#fail
    //while(1)
        //printf("Fred\n");

    //#fail
    //putchar('z');
    //fflush(stdout);

    //gramado_system_call (82,0,0,0);
    
    ohboy_system_call(65,'z',0,0);
    
    // ok
    //rtl_reboot();

// tests:

    debug_print("-- init: tests ------------------\n");

    if ( (void*) stdin == NULL )
        debug_print("init.bin: stdin fail\n");

    if ( (void*) stdout == NULL )
        debug_print("init.bin: stdout fail\n");

    if ( (void*) stderr == NULL )
        debug_print("init.bin: stderr fail\n");



//
// printf()
//

    long value=1234;
    printf ("\n");
    printf ("init.bin: Testing printf()\n");
    
    // #bugbug
    // Wrong value !!
    printf ("init.bin: Value=%d\n",value);


//
// write
//

    printf ("\n");
    printf ("init.bin: Testing write()\n");

    char *s = "Fred";
    //putc('v',stdout);
    //write ( fileno(stdin), s, 4 );
    write ( fileno(stdout), s, 4 );
    //write ( fileno(stderr), s, 4 );
    //fflush(stdout);
    //while(1){}


//
// read
//
    printf ("\n");
    printf ("init.bin: Testing read()\n");

    char ReadBuffer[32];
    read( fileno(stdin), ReadBuffer, 4 );
    //read( fileno(stdout), ReadBuffer, 4 );
    //read( fileno(stderr), ReadBuffer, 4 );


// =================================================

    // refresh screen
    ohboy_system_call(11,0,0,0);

    //#debug
    //while(1){}
    
    // ok, a calling conventions funcionou,
    // os parametros estao em ordem.
    //ohboy_system_call(4321,0xa,0xb,0xc);

    printf ("init.bin: done\n");

// Return to marginal.asm
}














