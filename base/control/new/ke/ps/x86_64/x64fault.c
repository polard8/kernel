
// x64fault.c

#include <kernel.h>

static int __kill_process(void);


// #todo
// Criar uma rotina onde, 
// se o window server falhar, 
// tem que pedir para o init reinicializar o window server.

// #bugbug: #todo
// E se a excessão ocorrer durante a fase em ring 0 de um proceso
// em ring 3?

static int __kill_process(void)
{
    struct process_d *p;
    struct thread_d *t;
    pid_t pid=-1;
    tid_t tid=-1;
    
    pid = (pid_t) get_current_process();
    tid = (tid_t) current_thread;


//pid
    if(pid<0 || pid >= PROCESS_COUNT_MAX)
        return -1;

// We can't close the Kernel process or the Init process.
    if (pid==GRAMADO_PID_KERNEL){
        return -1;
    }
    if (pid==GRAMADO_PID_INIT){
        return -1;
    }

    p = (void*) processList[pid];
    if (p->magic != 1234)
        return -1; 

// We can't close the Kernel process or the Init process.
    if (p == KernelProcess)
        return -1;
    if (p == InitProcess)
        return -1; 

//tid
    if(tid<0 || tid >= THREAD_COUNT_MAX)
        return -1;

// We can't close the Iit thread.
// #bugbug: Change name. The init is NOT a client application.
// It is just the first ring 3 tid and the idle thread for now.
// See: create.c
    //if(tid == CLIENT0_TID)  //init thread
    if(tid == 0)  // The first thread    
        return -1;
    t = (void*) threadList[tid];
    if (t->magic != 1234)
        return -1;

// We can't close the Iit thread.
    if (t == InitThread)
        return -1;

//
// kill the process
//

    if (p->control == t){
        p->control = NULL;
    }
    p->magic = 0;
    p->used = FALSE;
    p=NULL;
    
// kill the thread
    t->magic = 0;
    t->used = FALSE;
    t = NULL;

    return 0; //ok
}


// Called by 'all_faults:' in unit1hw.asm.

void faults (unsigned long number)
{
    //struct process_d *CurrentProcess;
    //struct thread_d  *CurrentThread;

    //Get these values using assembly inline.
    //unsigned long fault_pa=0;       //from cr2
    //unsigned long fault_pml4_pa=0;  //from cr3

    debug_print ("~faults:\n");
    
    printf("\n");
    printf("\n");
    printf("\n");
    printf ("number: %d\n",number);

//see: clone.c    
    if(copy_process_in_progress==TRUE)
        printf("Fault while copying a process\n");

    //#debug: We dont need this in every pagefault.
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
    
    // GP, PF and reserved by intel
    //if (number == 13 || number == 14 || number == 15)
    if (number == 13 || number == 14)
    {
        printf("fault: %d\n",number);
        
        killstatus= (int) __kill_process();
        
        if(killstatus==0)
        {
            current_thread = (tid_t) target_tid; 
            IncrementDispatcherCount (SELECT_DISPATCHER_COUNT);
            // MOVEMENT 4 (Ready --> Running).
            // update cr3 and context.
            dispatcher(DISPATCHER_CURRENT);  
            //#todo: precisamos atualizar os contadores da proxima thread.
            //update the global variable
            set_current_process(target_pid);
            printf("kill process and resume init\n");
            refresh_screen();
            return; // retorna pra assembly para efetuar iretq.
        }
    }

    switch (number){

        // Divisão por zero, ou resultado muito longo?
        // Se a falta ocoreu em ring 0, então precisamos
        // encerrar o sistema, mas se a falta aconteceu em ring3,
        // podemos simplesmente fechar o aplicativo.
        // Se ocorrer em cpl 0, terminamos o sistema.
        // Se ocorrer em cpl 3, terminamos o processo.
        case 0: 
            x_panic("faults() 0"); 
            break;
        
        case 1: x_panic("faults() 1"); break;
        case 2: x_panic("faults() 2"); break;

        // #todo: Accept arguments.
        // service, arg1 and arg2.
        // So, we need to put some arguments in the faults() function.
        // #todo: faults(number,arg1,arg2,arg3).
        case 3: 
            printf("\n");
            printf ("== 3 ==\n");  
            save_current_context();
            //show_slots();
            show_reg(current_thread);
            refresh_screen();
            // Esse tipo funciona mesmo antes do console
            // ter sido inicializado.
            
            x_panic("faults() 3"); 
            
            break;

        case 4: x_panic("faults() 4"); break;
        case 5: x_panic("faults() 5"); break;
        case 6: x_panic("faults() 6"); break;
        
        // Math co-processor not available.
        case 7: 
            x_panic("fault 7: No 80387");
            break;
        
        // Double fault.
        case 8: 
            x_panic("fault 8: DOUBLE");
            break;
        
        case 9: x_panic("faults() 9"); break;
        
        case 10:
            x_panic("fault 10: Invalid tss");
            break;
        
        case 11: x_panic("faults() 11"); break;
        case 12: x_panic("faults() 12"); break;


        //General Protection Fault
        case 13: 
            printf ("== GP ==\n");  
            //show_slots();
            refresh_screen();
            // Esse tipo funciona mesmo antes do console
            // ter sido inicializado.
            x_panic("faults() 13"); 
            break;
        
        // Page Fault
        // #todo: Com assembly inline podemos pegar cr2 e cr3.
        case 14: 
            printf ("== PF ==\n");  
            //if(user_thread==TRUE){
            //    printf("It's an user thread!\n");
            //}
            show_slots();
            refresh_screen();
            x_panic("faults() 14"); 
            break;

        // Intel reserved.
        // Se ocorrer em ring3 podemos fechar o processo.
        case 15:
            x_panic("fault 15: Intel reserved");
            break;
        
        // Co-processor error on 486 and above.
        case 16: 
            x_panic("fault 16: Coprocessor error");
            break;

        case 17: x_panic("faults() 17"); break;
        case 18: x_panic("faults() 18"); break;
        
        // Intel reserved faults
        // 19~31
        case 19: x_panic("faults() 19"); break;
        case 20: x_panic("faults() 20"); break;
        case 21: x_panic("faults() 21"); break;
        case 22: x_panic("faults() 22"); break;
        case 23: x_panic("faults() 23"); break;
        case 24: x_panic("faults() 24"); break;
        case 25: x_panic("faults() 25"); break;
        case 26: x_panic("faults() 26"); break;
        case 27: x_panic("faults() 27"); break;
        case 28: x_panic("faults() 28"); break;
        case 29: x_panic("faults() 29"); break;
        case 30: x_panic("faults() 30"); break;
        case 31: x_panic("faults() 31"); break;

        default:
            x_panic("faults() default"); 
            break;
    };
    
    x_panic("faults() fail");
}



