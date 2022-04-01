
#include <kernel.h>


// Called by 'all_faults:' in unit1hw.asm.

void faults ( unsigned long number )
{

    struct thread_d   *CurrentThread;

    //Get these values using assembly inline.
    //unsigned long fault_pa=0;       //from cr2
    //unsigned long fault_pml4_pa=0;  //from cr3

    debug_print ("~faults:\n");


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
    
    if (CurrentThread->iopl == 3)
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



// ============

    switch ( number ){

        // Divisão por zero, ou resultado muito longo?
        // Se a falta ocoreu em ring 0, então precisamos
        // encerrar o sistema, mas se a falta aconteceu em ring3,
        // podemos simplesmente fechar o aplicativo.
        case 0: 
            x_panic("faults() 0"); 
            break;
        
        case 1: x_panic("faults() 1"); break;
        case 2: x_panic("faults() 2"); break;


        case 3: 
            //printf ("== 3 ==\n");  
            //show_slots();
            //refresh_screen();
            // Esse tipo funciona mesmo antes do console
            // ter sido inicializado.
            
            x_panic("faults() 3"); 
            
            break;


        
        case 4: x_panic("faults() 4"); break;
        case 5: x_panic("faults() 5"); break;
        case 6: x_panic("faults() 6"); break;
        case 7: x_panic("faults() 7"); break;
        case 8: x_panic("faults() 8"); break;
        case 9: x_panic("faults() 9"); break;
        case 10: x_panic("faults() 10"); break;
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
            if(user_thread==TRUE){
                printf("It's an user thread!\n");
            }
            show_slots();
            refresh_screen();
            x_panic("faults() 14"); 
            break;

        case 15: x_panic("faults() 15"); break;
        case 16: x_panic("faults() 16"); break;
        case 17: x_panic("faults() 17"); break;
        case 18: x_panic("faults() 18"); break;
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



