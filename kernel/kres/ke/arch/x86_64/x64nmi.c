
// x64nmi.c

#include <kernel.h>

static int __kill_process(void);

// --------------------------

// #todo
// Criar uma rotina onde, 
// se o window server falhar, 
// tem que pedir para o init reinicializar o window server.
// #bugbug: #todo
// E se a excessão ocorrer durante a fase em ring 0 
// de um proceso em ring 3?
static int __kill_process(void)
{
// #todo: Explain it better.

    struct process_d *p;
    struct thread_d *t;
    pid_t pid=-1;
    tid_t tid=-1;

// The current process
    pid = (pid_t) get_current_process();
// The current thread.
    tid = (tid_t) current_thread;

//
// PID
//

//pid
    if (pid<0 || pid >= PROCESS_COUNT_MAX)
        goto fail;

// We can't close the Kernel process or the Init process.
    if (pid == GRAMADO_PID_KERNEL){
        goto fail;
    }
    if (pid == GRAMADO_PID_INIT){
        goto fail;
    }

//
// Process structure
//

    p = (void*) processList[pid];
    if (p->used != TRUE)
        goto fail;
    if (p->magic != 1234)
        goto fail;

// We can't close the Kernel process or the Init process.
    if (p == KernelProcess)
        goto fail;
    if (p == InitProcess)
        goto fail;

//
// TID
//

//tid
    if (tid<0 || tid >= THREAD_COUNT_MAX)
        goto fail;
// We can't close the Init thread.
// #bugbug: Change name. The init is NOT a client application.
// It is just the first ring 3 tid and the idle thread for now.
// See: create.c
// The first thread
// The control thread of the init process.
    if (tid == INIT_TID)
        goto fail;

//
// Thread structure
//

    t = (void*) threadList[tid];
    if (t->used != TRUE)
        goto fail;
    if (t->magic != 1234)
        goto fail;

// We can't close the Iit thread.
    if (t == InitThread)
        goto fail;

//
// Kill the process
//

// --------------
// Destroy the process structure.
    p->magic = 0;
    p->used = FALSE;
    p=NULL;
// --------------
// Destroy the thread structure.
    t->magic = 0;
    t->used = FALSE;
    t = NULL;

// OK
    return 0;
fail:
    return (int) -1;
}

// Called by 'all_faults:' in hw1.asm.
void x64_nmi(unsigned long number)
{
// Quote: 'You've never failed and You won't start now'.

// Get the pagefault address.
// #todo: Not tested.
    //unsigned long address=0;
    //if(number==14){
    //    asm volatile ("movq %%cr2, %0":"=r"(address):);
    //}

    //struct process_d *CurrentProcess;
    //struct thread_d  *CurrentThread;

    //Get these values using assembly inline.
    //unsigned long fault_pa=0;       //from cr2
    //unsigned long fault_pml4_pa=0;  //from cr3

    debug_print("x64_nmi:\n");

    //printk("\n");
    printk("\n");
    printk("\n");
    printk ("number: %d\n",number);

// see: clone.c    
    if (copy_process_in_progress == TRUE){
        printk("Fault while copying a process\n");
    }

//#debug: 
// We dont need this in every pagefault.
    refresh_screen();

/*
// #todo
// Salvaremos o contexto se a fault aconteceu
// em ring3. Pois nesse caso poderemos tentar retomar a
// execução.

    if ( current_thread < 0 || 
         current_thread >= THREAD_COUNT_MAX )
    {
        panic("faults: current_thread\n");
    }

    CurrentThread = (void *) threadList[current_thread]; 

// validation
    if ( CurrentThread->used != TRUE ||  
         CurrentThread->magic != 1234 )
    {
        panic ("faults: CurrentThread validation\n");
    }

// Save the context:
// The new context is stored into blobal variables.
// We're gonna put it all into the thread structure.

    save_current_context();
    CurrentThread->saved = TRUE;

// Is it an user thread?
// We can easily kill an user process.

    int user_thread=FALSE;
    
    if (CurrentThread->initial_iopl == 3)
        user_thread=TRUE;


// =============


    unsigned long saved_cr2=0;
    unsigned long saved_cr3=0;
    unsigned long saved_cr4=0;

    unsigned long cr2_va=0;
    unsigned long cr2_pa=0;

    unsigned long cr3_pa=0;

// PF
    if(number=14)
    {
        asm volatile ("movq %%cr2, %0":"=a"(saved_cr2):); // va?
        asm volatile ("movq %%cr3, %0":"=a"(saved_cr3):);
        asm volatile ("movq %%cr4, %0":"=a"(saved_cr4):);

        cr2_va = (unsigned long) saved_cr2;
        
        // ?
        // Devemos usar o pml4 do kernel ou o da current thread?
        // Possivelmente o da current thread, se a fault ocorreu
        // em ring3.
        
        //if(user_thread==FALSE){
        //cr2_pa = 
          //(unsigned long) virtual_to_physical ( cr2_va, gKernelPML4Address ); 
        //}

        //if(user_thread==TRUE){
        //cr2_pa = 
          //(unsigned long) virtual_to_physical ( cr2_va, CurrentThread->pml4_VA ); 
        //}

        cr3_pa = (unsigned long) saved_cr3;

        // #todo
        // dump this info.
    }
*/

    int killstatus = (int)-1;
    
    // next process.
    tid_t target_tid = INIT_TID;
    pid_t target_pid = GRAMADO_PID_INIT;

//
// Kill the process.
//

// #todo
// See ... we're killing the process
// when we reach a PF. But its not our goal.
// Maybe we're gonna implement some kind os
// allocation of falting pages. (Demand paging)
// See:
// https://en.wikipedia.org/wiki/Demand_paging
// https://wiki.osdev.org/Exceptions

//      - Division Error,            0
// (GP) - General Protection Fault, 13 (0xD) 
// (PF) - Page Fault,               14 (0xE) 

    if ( number == 0  ||
         number == 13 || 
         number == 14 )
    {
        printk("x64_nmi: {%d}\n",number);

        // Kill process
        // #bugbug: Precisamos checar o ring que o processo
        // estava no momento da falta. Se foi em ring0
        // entao temos problema.
        // 0=OK | -1 = FAIL.
        killstatus= (int) __kill_process();
        if (killstatus != 0){
            x_panic("x64_nmi: Coudn't kill process");
        }
        if (killstatus == 0)
        {
            printk("The process was killed\n");
            
            //
            // Resume init thread
            //

            // Set the INIT_TID as the next current thread.
            //current_thread = (tid_t) target_tid;
            set_current_thread((tid_t) target_tid);
            
            // Count the dispatcher method.
            IncrementDispatcherCount(SELECT_DISPATCHER_COUNT);
            
            // Change the thread state.
            // MOVEMENT 4 (Ready --> Running).
            // Update cr3 and context.
            dispatcher(DISPATCHER_CURRENT);  
            
            // Se the next current process.
            // #todo: 
            // Precisamos atualizar os contadores da proxima thread.
            // update the global variable
            set_current_process((pid_t)target_pid);
            
            // Final message.
            printk("Resuming the init thread\n");
            refresh_screen();
            
            // Retorna pra assembly para efetuar iretq.
            return;
        }
    }

//
// More numbers.
//

    switch (number){

        // Division Error
        // Divisão por zero, ou resultado muito longo?
        // Se a falta ocoreu em ring 0, então precisamos
        // encerrar o sistema, mas se a falta aconteceu em ring3,
        // podemos simplesmente fechar o aplicativo.
        // Se ocorrer em cpl 0, terminamos o sistema.
        // Se ocorrer em cpl 3, terminamos o processo.
        case 0: 
            x_panic("x64_nmi: 0"); 
            break;

        // Debug
        case 1:
            x_panic("x64_nmi: 1");
            break;

        // Non-maskable Interrupt
        case 2:
            x_panic("x64_nmi: 2");
            break;

        // Debug breakpoint - 3 (0x3) 
        // #todo: Accept arguments.
        // service, arg1 and arg2.
        // So, we need to put some arguments in the faults() function.
        // #todo: faults(number,arg1,arg2,arg3).
        case 3: 
            printk("\n");
            printk ("== 3 ==\n");  
            save_current_context();
            //show_slots();
            show_reg(current_thread);
            refresh_screen();
            // Esse tipo funciona mesmo antes do console
            // ter sido inicializado.
            x_panic("x64_nmi: 3"); 
            break;

        // Overflow
        case 4:
            x_panic("x64_nmi: 4");
            break;

        // Bound Range Exceeded
        case 5:
            x_panic("x64_nmi: 5");
            break;

        // Invalid Opcode - 6 (0x6) 
        case 6:
            x_panic("x64_nmi: 6");
            break;

        // Device Not Available
        // Math co-processor not available.
        case 7: 
            x_panic("x64_nmi: 7 - No 80387");
            break;

        // Double fault.
        case 8:
            x_panic("x64_nmi: 8 - DOUBLE");
            break;
        
        // Coprocessor Segment Overrun?
        case 9:
            x_panic("x64_nmi: 9");
            break;

        // Invalid TSS
        case 10:
            x_panic("x64_nmi: 10 - Invalid tss");
            break;

        // Segment Not Present
        case 11:
            x_panic("x64_nmi: 11");
            break;

        // Stack-Segment Fault
        case 12:
            x_panic("x64_nmi: 12");
            break;

        // (GP) - General Protection Fault
        case 13: 
            printk ("== GP ==\n");  
            //show_slots();
            refresh_screen();
            // Esse tipo funciona mesmo antes do console
            // ter sido inicializado.
            x_panic("x64_nmi: 13"); 
            break;

        // (PF) - Page Fault
        // #todo: Com assembly inline podemos pegar cr2 e cr3.
        case 14: 
            printk ("== PF ==\n");  
            //if(user_thread==TRUE){
            //    printk("It's an user thread!\n");
            //}
            show_slots();
            refresh_screen();
            x_panic("x64_nmi: 14"); 
            break;

        // Intel reserved.
        case 15:
            x_panic("x64_nmi: 15 - Intel reserved");
            break;

        // x87 Floating-Point Exception
        // Co-processor error on 486 and above.
        case 16:
            x_panic("x64_nmi: 16 - Coprocessor error");
            break;

        // Alignment Check
        case 17:
            x_panic("x64_nmi: 17");
            break;

        // Machine Check
        case 18:
            x_panic("x64_nmi: 18");
            break;

        // Intel reserved faults
        // 19~31

        // 19 - SIMD Floating-Point Exception
        case 19: x_panic("x64_nmi: 19"); break;
        // 20 - Virtualization Exception
        case 20: x_panic("x64_nmi: 20"); break;
        // 21 - Control Protection Exception
        case 21: x_panic("x64_nmi: 21"); break;
        case 22: x_panic("x64_nmi: 22"); break;
        case 23: x_panic("x64_nmi: 23"); break;
        case 24: x_panic("x64_nmi: 24"); break;
        case 25: x_panic("x64_nmi: 25"); break;
        case 26: x_panic("x64_nmi: 26"); break;
        case 27: x_panic("x64_nmi: 27"); break;
        // 28 - Hypervisor Injection Exception
        case 28: x_panic("x64_nmi: 28"); break;
        // 29 - VMM Communication Exception
        case 29: x_panic("x64_nmi: 29"); break;
        // 30 - Security Exception
        case 30: x_panic("x64_nmi: 30"); break;
        case 31: x_panic("x64_nmi: 31"); break;

        default:
            x_panic("x64_nmi: Unknown"); 
            break;
    };
    
    x_panic("x64_nmi: Fail");
}



