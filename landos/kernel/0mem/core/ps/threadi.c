

#include <kernel.h>

/*
 *****************************************************
 * show_slot:
 *     Show info about a thread.
 */

void show_slot (int tid){

    struct thread_d *t;


    if ( tid < 0 || tid >= THREAD_COUNT_MAX )
    {
        printf ("show_slot: tid\n");
        goto fail;
    }

    t = (void *) threadList[tid];

    if ( (void *) t == NULL ){
        printf ("show_slot: t\n");
        goto fail;

    }else{

        // Show one slot.
        printf ("\n");
        printf ("TID   PID   pdPA  Prio  State Quan *Jiffies initial_eip eflags   tName \n");
        printf ("====  ====  ====  ====  ===== ==== ====    ==========  ======  ===== \n");
        printf ("%d    %d    %x   %d    %d    %d   %d      %x          %x      %s \n", 
            t->tid, 
            t->ownerPID,
            t->pml4_PA,
            t->priority, 
            t->state,
            t->quantum,    // Quantum
            t->step,       // >>> Jiffies
            t->initial_rip,
            t->rflags,
            t->name_address );
    };

    goto done;

fail:
    printf ("Fail\n");
done:
    return; 
}

/*
 *****************************************
 * show_slots:
 *     Show info about all threads.
 */

void show_slots(void){

    struct process_d *p;
    struct thread_d  *t;
    int i=0;

    printf ("\nThread info:\n");

    // Loop.
    // Mostra as tarefas válidas, mesmo que estejam com problemas.

    for ( i=0; i<THREAD_COUNT_MAX; i++ )
    {
        t = (void *) threadList[i];

        if ( (void *) t != NULL && 
             t->used  == 1 && 
             t->magic == 1234 )
        {
            show_slot (t->tid);
        }
    };
}

/*
 *************************************************
 * show_reg:
 *     Show the content of the registers.
 * 
 *    rflags
 *    cs:rip
 *    ss:rsp
 *    ds,es,fs,gs
 *    a,b,c,d
 */

void show_reg (int tid){

    struct thread_d *t; 


    if ( tid < 0 || tid >= THREAD_COUNT_MAX ){
        printf ("show_reg: fail\n");
        return;
    }

    // Structure.
    t = (void *) threadList[tid];

    if ( (void *) t == NULL ){
        printf ("show_reg: fail\n");
        return;

    } else {

        // Show registers.

        printf ("\n rflags=[%x]", t->rflags);
        printf ("\n cs:rip=[%x:%x] ss:rsp=[%x:%x]", 
            t->cs, t->rip, t->ss, t->rsp );
        printf ("\n ds=[%x] es=[%x] fs=[%x] gs=[%x]",
            t->ds, t->es, t->fs, t->gs );
        printf ("\n a=[%x] b=[%x] c=[%x] d=[%x]\n",
            t->rax, t->rbx, t->rcx, t->rdx );
        
        // r8~r12
        // ...
    };
}

/* 
 *********************************
 * set_thread_priority: 
 *
 */

// Muda a prioridade e o quantum de acordo com a prioridade.

void 
set_thread_priority ( 
    struct thread_d *t, 
    unsigned long priority )
{

    unsigned long OldPriority  = 0;
    unsigned long BasePriority = 0;


    // Limits
    if ( priority > PRIORITY_MAX )
        return;

    if ( (void *) t == NULL )
    {
        //
        return;

    }else{

        // Validation
        if ( t->used != 1 || t->magic != 1234 ){ return; }

        OldPriority  = t->priority;
        BasePriority = t->base_priority;

        // Se aprioridade solicitada for igual da prioridade atual.
        if ( priority == OldPriority ){ return; }
        
        // Se a prioridade solicitada for menor que a prioridade basica.
        if ( priority < BasePriority ){ return; }

        // Se a prioridade basica pertencer a classe de tempo real
        // nao podemos mudar a prioridade.
        if ( BasePriority > PRIORITY_NORMAL ){ return; }
        
        // limits again
        if ( priority > PRIORITY_MAX )
        {
            t->priority = PRIORITY_MAX;
        }

        // Change!
        // Se aprioridade solicitada for diferente da prioridade atual.
        // Tambem nao pode ser menor que a base.
        if ( priority != OldPriority )
        {
            // Muda a prioridade.
            t->priority = priority;
        
            t->quantum = ( priority * TIMESLICE_MULTIPLIER );
            
            if ( t->quantum > QUANTUM_LIMIT )
            {
                  t->quantum = QUANTUM_LIMIT;
            }
        };    
        // ...
    };
    // ??
}

// muda a prioridade para alem dos limites ... teste.
void threadi_power(
    struct thread_d *t, 
    unsigned long priority )
{

    if ( (void *) t == NULL ){ return; }
   
    if ( t->used != 1 || t->magic != 1234 ){ return; }
    
    t->priority = priority;
    t->quantum = ( priority * TIMESLICE_MULTIPLIER );
}

/*
 ****************************************
 * release:
 * #importante
 * Isso deve liberar uma thread que estava esperando 
 * ou bloqueada por algum motivo.
 * Obs: Aqui não devemos julgar se ela pode ou não ser
 * liberada, apenas alteramos se estado.
 */
 
void release ( int tid ){

    struct thread_d *Thread;


    if ( tid < 0 || tid >= THREAD_COUNT_MAX )
    {
        //  
		return; 
    }
	
    Thread = (void *) threadList[tid];

    if ( (void *) Thread == NULL ){
		//
		return; 

    }else{

        if ( Thread->magic != THREAD_MAGIC )
        {
            return; 
        }

		//#importante:
		//Não estamos selecionando ela para execução
		//Apenas estamos dizendo que ela está pronta para
		//executar.

        Thread->state = READY; 
    };
}


























