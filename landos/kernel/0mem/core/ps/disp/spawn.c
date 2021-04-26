/*
 * File: ps/disp/spawn.c
 *
 * It executes a thread fot the first time, calling the method spawn.
 * Part of the dispatcher module.
 *
 * O Spawn coloca uma nova thread pra executar efetuando
 * um iret. A pilha foi configurada para user  mode antes de efetuar
 * o iret.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - Small changes.
 *     //...
 */


#include <kernel.h>


static inline void spawnSetCr3 ( unsigned long physical_address )
{
    asm ( "mov %0, %%cr3" : : "r" (physical_address) );
}



// KiSpawnTask:
// Interface to spawn a thread.

void KiSpawnThread (int tid){

    if ( tid < 0 || tid >= THREAD_COUNT_MAX )
    {
        printk ("KiSpawnThread: TID=%d\n", tid );
        die ();
    }

    spawn_thread (tid);

    panic ("KiSpawnThread\n");
}


/*
 *********************************************************
 * spawn_thread: 
 *     Execute a thread for the first time.
 *     The thread needs to be in the state 'STANDBY'.
 */ 

// #bugbug
// Archtecture dependent stuff.
// x86.
 
void spawn_thread (int tid)
{
    struct thread_d  *Target;
    struct thread_d  *Next;


    // The next will be the current thread.
    Next = (void *) threadList[current_thread];


    //
    //  spawn_Pointer 
    //

    if ( tid < 0 || tid >= THREAD_COUNT_MAX )
    {
        printf ("spawn_thread: TID=%d", tid );
        die();
    }

    Target = (void *) threadList[tid]; 

    if ( (void *) Target == NULL ){
        printf ("spawn_thread: Target TID={%d}", tid );
        die();
    }

    if ( Target->used != TRUE || Target->magic != 1234 )
    {
        panic("spawn_thread: Target validation");
    }


    // Check tid validation
    if (Target->tid != tid){
        panic("spawn_thread: tid validation");
    }

    // State: Needs to be in Standby,
    if ( Target->state != STANDBY ){
        printf ("spawn_thread: TID={%d} not in Standby\n", tid );
        die();
    }

    // Saved:
    // If the context is saved, so it is not the first time.
    if ( Target->saved == TRUE ){
        printf ("spawn_thread: Saved TID={%d}\n", tid );
        die();
    }

    // Initializing
    Target->saved = FALSE;

    // ??
    // More checks ?
    // Prepare some elements.


    // The current thread will be the next.

    Target->next = (void *) Next; 

//
// MOVEMENT 2 (Standby --> Running).
//

    if ( Target->state == STANDBY )
    {
        Target->state = RUNNING;
        queue_insert_data ( 
            queue, 
            (unsigned long) Target, 
            QUEUE_RUNNING );
    }

    // Destrava o mecanismo de taskswitch.
    // Destrava o Scheduler.

    set_task_status(UNLOCKED);
    scheduler_unlock(); 


    // Paranoia: Check state.

    if ( Target->state != RUNNING ){
        printf ("spawn_thread: State TID={%d}\n", tid );
        die ();
    }

    // Set current process

    if ( (void*) Target->process == NULL ){
        panic("spawn_thread: Target->process\n");
    }

    current_process = Target->process->pid;
    if ( current_process < 0 ){
        panic("spawn_thread: current_process\n");
    }

    // Set current thread

    current_thread = (int) Target->tid;
    if ( current_thread < 0 ){
        panic("spawn_thread: current_thread\n");
    }

    IncrementDispatcherCount (SELECT_INITIALIZED_COUNT);


    // Set cr3 and flush TLB.

    spawnSetCr3 ( (unsigned long) Target->DirectoryPA );

    asm ("movl %cr3, %eax");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("movl %eax, %cr3");

    // #debug
    // show_reg(spawn_Pointer->tid);
    // refresh_screen();
    // while(1){}


    //#bugbug
    //Eax sujou. Isso é um problema para a thread clonada de fork()
    //Por isso que ela não deve usar o spawn ... e sim ficar ready.

    asm volatile ( 
        " cli \n"
        " mov $0x23, %ax \n"
        " mov %ax, %ds   \n"
        " mov %ax, %es   \n"
        " mov %ax, %fs   \n"
        " mov %ax, %gs   \n" );


	//unsigned long argc = 1234;
	//#test
	//Tentando enviar linha de comando para crt0 ou main() do aplicativo.
	//#importante: O aplicativo n�o pode ler uma string que esteja escrito 
	//em kernel mode, ent�o n�o adianta passar o ponteiro.

	//asm("pushl %0" :: "r" ((unsigned long) ? ) : "%esp");
	//asm("pushl %0" :: "r" ((unsigned long) argc ) : "%esp");  //argc 

	//argc 
	//Ok. isso funcionou ... 
    // main no aplicativo recebeu argc do crt0.
	//até mesmo na thread clonada no fork();
    // o que não é bom ... pois a thread clonada tem que ter os valores
    //da thread do processo pai. >> vamos suprimir isso.
    
    //asm (" mov $0x1234, %ebx \n");


    // #test
    // Mudando eflags para iopl 3 antes de usarmos a pilha.

    asm (" pushl $0x3000 \n");
    asm (" popfl \n");


	// #bugbug
	// Os carinhas do gcc 9.1.0 resolveram sacanear.
	// N�o posso usar mais isso porque eles tiveram um ataque de pelanca.
	// Warning:
	// "Listening the stack pointer register in a clobber list is deprecated."  


    // Stack frame.
    // Pilha para iret.
    // ss, esp, eip, cs, eip;

    //Pilha para iret.
    asm ("pushl %0" :: "r" ((unsigned long) Target->ss     & 0xffff ) );  //ss.
    asm ("pushl %0" :: "r" ((unsigned long) Target->esp             ) );  //esp.
    asm ("pushl %0" :: "r" ((unsigned long) Target->eflags          ) );  //eflags.
    asm ("pushl %0" :: "r" ((unsigned long) Target->cs     & 0xffff ) );  //cs.
    asm ("pushl %0" :: "r" ((unsigned long) Target->eip             ) );  //eip.
    

    // #bugbug
    // As interrupções estão habilitadas ?
    // Qual é o valor de eflags no stack frame ?

    // Lembrando que no caso do processo init
    // saltamos com as interrupções desabilitadas,
    // mas no caso das outras threads precisamos saltar com as
    // interrupções habilitadas.


    // #bugbug
    // Why the EOI ?
    
    // #importante
    // Precismos disso pois foi o irq0 quem nos trouxe aqui.
    // Atravez de um request ?
    
    // #todo
    //if ( eoi_needed == TRUE )
    //{
        asm ("movb $0x20, %al \n");
        asm ("outb %al, $0x20 \n");
    //}
    
    // #bugbug
    // Estamos com 'eax' sujo.

	//
	// Fly!
	//

    asm ("iret \n"); 

    /*
	// # teste sujo
	//tss
	//isso ser� um test para taskswitch via hardware,
	//precisa habilitar flag nt antes,
	//asm  ("ljmp $0x2B, $0x401000 \n\t");
	//asm ("sti  \n"); 
    */

// fail:
    panic ("spawn_thread: iret fail");
}


//
// End.
//

