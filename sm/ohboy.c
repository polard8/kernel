
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


void testThread(void)
{
	debug_print("THREAD\n");
	while(1){}
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
        debug_print("sm.bin: stdout fail\n");

    if ( (void*) stderr == NULL )
        debug_print("sm.bin: stderr fail\n");



//
// printf()
//

    //long value=1234;
    //printf ("\n");
    //printf ("init.bin: Testing printf()\n");
    
    // #bugbug
    // Wrong value !!
    //printf ("init.bin: Value=%d\n",value);


//
// write
//

    printf ("\n");
    printf ("sm.bin: Testing write()\n");

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
    printf ("sm.bin: Testing read()\n");

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

    //printf ("Testing fflush()");
    //fflush(stdout);
    //while(1){}
    
    //close(0); close(1); close(2);

    // #todo: 
    // Trabalhando na implementação dessa rotina em ring0.
    // See: x64init.c, pages.c, process.c ...
    //rtl_clone_and_execute("gdeshell.bin");
    //rtl_clone_and_execute("sm.bin"); 


//
//
//

    // It is working ... but the crt0 in rtl just have an 'int 3'
    rtl_clone_and_execute("reboot.bin"); 
    
    
    
    //rtl_clone_and_execute("gdeshell.bin");   //fail
    //rtl_clone_and_execute(".bin"); 


    //char thread_stack[1024];
   
    //void *t1;
    //#todo: IN: address, stack, name.
    //t1 = (void *) rtl_create_thread(
    //    &testThread,
    //    &thread_stack[1023], 
    //    "Ring3Thread" );

    //#todo: Ainda não é possível, pois não temos timer.
    //rtl_start_thread(t1);

    printf ("sm.bin: done\n");
    
    


// interna
// Uma interrupção para habilitar as interrupções mascaráveis.
// So depois disso a interrupção de timer vai funcionar.
// This is Intel processors.
// [32~255]

    // ok, funciona. Podemos usar o teclado.
    //asm ("int $199 \n");

    // #test
    while(1){}

// Return to marginal.asm
}













