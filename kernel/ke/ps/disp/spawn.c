

#include <kernel.h>  


// local
void __spawn_load_pml4_table(unsigned long phy_addr)
{
    asm volatile ("movq %0,%%cr3"::"r"(phy_addr));
}


void spawn_thread (int tid)
{
    struct thread_d  *Target;
    struct thread_d  *Next;


    debug_print ("spawn_thread:\n");

    // #debug
    printf ("spawn_thread: SPAWN !\n");
    refresh_screen();


    // The next will be the current thread.
    Next = (void *) threadList[current_thread];

//
// Target 
//

    debug_print ("spawn_thread: Target\n");

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
        
        // #bugbug
        // #todo
        // We have some overflow issues to resolve.
        
        //queue_insert_data ( 
        //    queue, 
        //    (unsigned long) Target, 
        //    QUEUE_RUNNING );
    }

    // Destrava o mecanismo de taskswitch.
    // Destrava o Scheduler.

    set_task_status(UNLOCKED);
    scheduler_unlock(); 

    // Paranoia: Check state.

    if ( Target->state != RUNNING ){
        printf ("spawn_thread: State TID={%d}\n", tid );
        die();
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


    debug_print ("spawn_thread: Load pml4\n");


    // Set cr3 and flush TLB.
    // local
    __spawn_load_pml4_table ( Target->pml4_PA );
    // #bugbug: rever isso.
    asm ("movq %cr3, %rax");
    asm ("movq %rax, %cr3");

//
// iretq
//

    debug_print ("spawn_thread: iretq\n");

    // #todo
    // Configurar a stackframe para saltar para
    // qualquer ring.

    if ( Target->iopl != RING3 ){
        debug_print ("spawn_thread: Not a ring3 thread\n");
        panic       ("spawn_thread: Not a ring3 thread\n");
    }


    // #debug
    // show_reg(Target->tid);
    // refresh_screen();
    // while(1){}
    
    // Target->ss     & 0xffff
    // Target->rsp
    // Target->rflags
    // Target->cs     & 0xffff
    // Target->rip

    // This is the entry point of the new thread
    // Probably created by a ring 3 process.
    unsigned long entry = (unsigned long) Target->rip;

    // This is the stack pointer for the ring 3 thread.
    // Probably given by a ring 3 process.
    unsigned long rsp3  = (unsigned long) Target->rsp;

    // #test
    // Isso porque o spawn só é chamado durante uma interrupção
    // de timer.
    // #todo
    // Deveria ter uma flag indicando que estamos devendo um EOI.
    
    asm ("movb $0x20, %al \n");
    asm ("outb %al, $0x20 \n");


    asm volatile ( 
        " movq $0, %%rax    \n" 
        " mov %%ax, %%ds    \n" 
        " mov %%ax, %%es    \n" 
        " mov %%ax, %%fs    \n" 
        " mov %%ax, %%gs    \n" 
        " movq %0, %%rax    \n" 
        " movq %1, %%rsp    \n" 
        " movq $0, %%rbp    \n" 
        " pushq $0x23       \n"  
        " pushq %%rsp       \n" 
        " pushq $0x3202     \n"  // Interrupts enabled for the thread that is not the first.
        " pushq $0x1B       \n" 
        " pushq %%rax       \n" 
        " iretq             \n" :: "D"(entry), "S"(rsp3) );
  
    PROGRESS("-- iretq fail -----------------\n");

    // Paranoia
    panic ("spawn_thread: [ERROR] iretq fail\n");
}


// KiSpawnTask:
// Interface to spawn a thread.

void KiSpawnThread (int tid)
{
    debug_print ("KiSpawnThread:\n");


    if ( tid < 0 || tid >= THREAD_COUNT_MAX )
    {
        printf ("KiSpawnThread: TID=%d\n", tid );
        die();
    }
    spawn_thread (tid);
    panic ("KiSpawnThread\n");
}


// Spawn the control thread of a process.
// Remember we need to call this after 
// the irq0 interrupt. Cause the spawn routine
// has the eoi.
void spawn_pid(pid_t pid)
{
    struct process_d *p;
    
    if (pid < 0 || pid >= PROCESS_COUNT_MAX )
        panic("spawn_pid: pid\n");
    
    p = (struct process_d *) processList[pid];
    
    if ( (void*) p == NULL )
        panic("spawn_pid: pid\n");

    if ( p->used != TRUE || p->magic != 1234 )
        panic("spawn_pid: validation\n");

    KiSpawnThread(p->control);

    return;
}


void spawn_tid(int tid)
{
    struct thread_d *t;
    
    if (tid < 0 || tid >= THREAD_COUNT_MAX )
        panic("spawn_tid: tid\n");
    
    t = (struct thread_d *) threadList[tid];
    
    if ( (void*) t == NULL )
        panic("spawn_tid: tid\n");

    if ( t->used != TRUE || t->magic != 1234 )
        panic("spawn_tid: validation\n");

    KiSpawnThread(t);

    return;
}

