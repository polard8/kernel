
// spawn.c

#include <kernel.h>  

static int __spawn_eoi_is_necessary = FALSE;

//
// == Private functions: Prototypes =======
//

static int __spawn_is_eoi_needed(void);

//=====================


// global
// used by the taskswitching
void spawn_set_eoi_state(void)
{
    __spawn_eoi_is_necessary = TRUE;
}

// global
// used by the taskswitching

void spawn_reset_eoi_state(void)
{
    __spawn_eoi_is_necessary = FALSE;
}

// local
static int __spawn_is_eoi_needed(void)
{
    return (int) __spawn_eoi_is_necessary;
}


// local
void __spawn_load_pml4_table(unsigned long phy_addr)
{
    asm volatile ("movq %0,%%cr3"::"r"(phy_addr));
}


// spawn_thread:
// main worker.
// Spawn a new thread.
// The flag 'new_clone' indicates this is the control thread
// of a clone process that is running for the first time.

void spawn_thread(int tid)
{
    struct thread_d *target_thread;

    int next_tid = (int) (tid & 0xFFFF);

    debug_print ("spawn_thread:\n");

    // #debug
    //printf ("spawn_thread: SPAWN !\n");
    //refresh_screen();

//
// Target 
//

    debug_print ("spawn_thread: target_thread\n");

    if ( next_tid < 0 || next_tid >= THREAD_COUNT_MAX )
    {
        printf ("spawn_thread: next_tid=%d", next_tid );  
        die();
    }

// target thread.

    target_thread = (void *) threadList[next_tid]; 

    if ( (void *) target_thread == NULL )
    {
        printf ("spawn_thread: target_thread, next_tid={%d}", 
            next_tid );  
        die();
    }

    if ( target_thread->used != TRUE || target_thread->magic != 1234 )
    {
        panic("spawn_thread: target_thread validation");
    }

// Is it a new clone?
// new clone
    if ( target_thread->new_clone == TRUE )
    {
        debug_print ("spawn_thread: Spawning the control thread of a new clone\n");
        //refresh_screen();
    }


// Check tid validation
    if (target_thread->tid != next_tid){
        panic("spawn_thread: target_thread->tid validation");
    }

    // State: Needs to be in Standby,
    if ( target_thread->state != STANDBY )
    {
        printf ("spawn_thread: TID={%d} not in Standby\n", next_tid );
        die();
    }

    // Saved:
    // If the context is saved, so it is not the first time.
    if ( target_thread->saved == TRUE ){
        printf ("spawn_thread: Saved TID={%d}\n", next_tid );
        die();
    }

// Initializing
// Not saved
    target_thread->saved = FALSE;

// ??
// More checks ?
// Prepare some elements.

// #todo
// Talvez ja exista um worker para essa rotina.

    target_thread->standbyCount = 0;
    target_thread->standbyCount_ms = 0;
    target_thread->runningCount = 0;
    target_thread->runningCount_ms = 0;
    target_thread->readyCount = 0;
    target_thread->readyCount_ms = 0;
    target_thread->waitingCount = 0;
    target_thread->waitingCount_ms = 0;
    target_thread->blockedCount = 0;
    target_thread->blockedCount_ms = 0;
    // ...

// Initial jiffie
// Spawn time.
    target_thread->initial_jiffie = (unsigned long) jiffies;

// how much tick untill now.
    target_thread->step = 0;

    target_thread->initial_time_ms = 0;
    target_thread->total_time_ms = 0;

// Linked list
// The next thread will be the window server.

    target_thread->next = (void *) tid0_thread; 

//
// MOVEMENT 2 (Standby --> Running).
//

    if ( target_thread->state == STANDBY )
    {
        target_thread->state = RUNNING;
        
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

    if ( target_thread->state != RUNNING ){
        printf ("spawn_thread: State TID={%d}\n", next_tid );
        die();
    }


// ??
// Set current process

    if ( (void*) target_thread->process == NULL )
    {
        panic("spawn_thread: target_thread->process\n");
    }


// Pegamos o pid.
// #bugbug: 
// Talvez o ponteiro t->process nao foi devidamente inicializado.

    //pid_t cur_pid = (pid_t) target_thread->process->pid;
    
    pid_t cur_pid = (pid_t) target_thread->ownerPID;
    
    if ( cur_pid < 0 || 
         cur_pid >= PROCESS_COUNT_MAX )
    {
        panic("spawn_thread: cur_pid\n");
    }

// The current process will be the owner pid.

    set_current_process(cur_pid);
    

// Set current thread
// (global) (tid)

    //(tid)
    current_thread = (int) target_thread->tid;

// paranoia
    if ( current_thread < 0 || 
         current_thread >= THREAD_COUNT_MAX )
    {
        panic("spawn_thread: current_thread\n");
    }

    IncrementDispatcherCount (SELECT_INITIALIZED_COUNT);



// local
// Set cr3 and flush TLB.

    debug_print ("spawn_thread: Load pml4\n");
    __spawn_load_pml4_table ( target_thread->pml4_PA );


//#bugbug
//Maybe we need to call a method for that.

    // #bugbug: rever isso.
    asm ("movq %cr3, %rax");
    // #todo: wait here, (remember: we're using registers.)
    asm ("movq %rax, %cr3");


//
// iretq
//

    debug_print ("spawn_thread: iretq\n");

// #todo
// Configurar a stackframe para saltar para
// qualquer ring.

// #todo
// Precisamos de uma flag que nos diga que estamos
// lançando uma thread durante uma interrupçao de timer (pit)
// para efetuarmos o 'EOI' propriamente.

    int eoi_is_needed = __spawn_is_eoi_needed();

    // #test #debug
    if ( eoi_is_needed != TRUE ){
        panic("spawn_thread: eoi_is_needed != TRUE\n");
    }

// #bugbug
// We're having problems when receiving syscalls from ring0.
// Our system interrupt is only for ring3 processes.

    if ( target_thread->initial_iopl == RING0 )
    {
        //#debug
        
        debug_print ("spawn_thread: RING0\n");
        
        //printf      ("spawn_thread: RING0\n");
        //debug_print ("spawn_thread: RING0 not supported yet\n");
        //panic       ("spawn_thread: RING0 not supported yet\n");
        //refresh_screen();
        
        spawn_enter_kernelmode( 
            TRUE,  // EOI
            (unsigned long) target_thread->rip,
            (unsigned long) target_thread->rsp );
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
    
    if ( target_thread->initial_iopl == RING3 )
    {
        spawn_enter_usermode( 
            TRUE,  // EOI
            (unsigned long) target_thread->rip,
            (unsigned long) target_thread->rsp );
    }

    /*
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

    */

    PROGRESS("-- iretq fail -----------------\n");

    // Paranoia
    panic ("spawn_thread: [ERROR] iretq fail\n");
}


// do not check parameters.
void 
spawn_enter_usermode( 
    int eoi,                 // do we need eoi ? TRUE or FALSE. 
    unsigned long entry_va,  // Entry point
    unsigned long rsp3_va )  // Stack pointer.
{

// This is the entry point of the new thread
// Probably created by a ring 3 process.
    unsigned long entry = (unsigned long) entry_va;

// This is the stack pointer for the ring 3 thread.
// Probably given by a ring 3 process.
    unsigned long rsp3  = (unsigned long) rsp3_va;

    if ( eoi == TRUE ){
        asm ("movb $0x20, %al \n");
        asm ("outb %al, $0x20 \n");
    }

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
  
    PROGRESS("spawn_enter_usermode: -- iretq fail ---\n");

    // Paranoia
    panic ("spawn_enter_usermode: [ERROR] iretq fail\n");
}


// do not check parameters.
void 
spawn_enter_kernelmode( 
    int eoi,                 // do we need eoi ? TRUE or FALSE. 
    unsigned long entry_va,  // Entry point
    unsigned long rsp0_va )  // Stack pointer.
{

    // This is the entry point of the new thread
    unsigned long entry = (unsigned long) entry_va;

    unsigned long rsp0  = (unsigned long) rsp0_va;


    // #debug
    //printf("rsp0: %x \n",rsp0);
    //refresh_screen();
    //while(1){}


    if ( eoi == TRUE ){
        asm ("movb $0x20, %al \n");
        asm ("outb %al, $0x20 \n");
    }

// #todo
// We need to review the stack frame fpor ring0

    asm volatile ( 
        " movq $0, %%rax    \n" 
        " mov %%ax, %%ds    \n" 
        " mov %%ax, %%es    \n" 
        " mov %%ax, %%fs    \n" 
        " mov %%ax, %%gs    \n"
        " movq %0, %%rax    \n" 
        " movq %1, %%rsp    \n" 
        " movq $0, %%rbp    \n" 
        " pushq $0x10       \n"  
        " pushq %%rsp       \n" 
        " pushq $0x0202     \n"  // Interrupts enabled for the thread that is not the first.
        " pushq $0x8       \n" 
        " pushq %%rax       \n" 
        " iretq             \n" :: "D"(entry), "S"(rsp0) );
  
    PROGRESS("spawn_enter_kernelmode: -- iretq fail ---\n");

    // Paranoia
    panic ("spawn_enter_kernelmode: [ERROR] iretq fail\n");
}


// KiSpawnTask:
// Interface to spawn a thread.

void KiSpawnThread(int tid)
{
    debug_print ("KiSpawnThread:\n");

    if ( tid < 0 || tid >= THREAD_COUNT_MAX )
    {
        printf("KiSpawnThread: TID=%d\n", tid );
        die();
    }
    spawn_thread(tid);
    panic("KiSpawnThread:\n");
}


// spawn_pid:
// Spawn the control thread of a process.
// Remember we need to call this after 
// the irq0 interrupt. Cause the spawn routine
// has the eoi.
// #bugbug
// Not tested yet.
void spawn_pid(pid_t pid)
{
    struct process_d *p;
    tid_t __tid=-1;

// pid
    if (pid < 0 || pid >= PROCESS_COUNT_MAX ){
        panic("spawn_pid: pid\n");
    }

// process structure.

    p = (struct process_d *) processList[pid];
    
    if ( (void*) p == NULL ){
        panic("spawn_pid: p\n");
    }

    if ( p->used != TRUE || p->magic != 1234 )
    {
        panic("spawn_pid: p validation\n");
    }

// spawn
    __tid = (tid_t) p->control->tid;
    KiSpawnThread(__tid);
// not reached
    panic("spawn_pid: fail");
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

// spawn
    KiSpawnThread(tid);
// not reached
    panic("spawn_tid: fail");
}

