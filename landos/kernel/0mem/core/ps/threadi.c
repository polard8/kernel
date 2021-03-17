/*
 * File: ps/threadi.c 
 *
 *      Thread internal.    
 *
 *     'Ki_' é para rotinas com threads oferecidas
 *     pelo modulo interno dentro do kernel base.
 *
 *     O kernel acessa as rotinas envolvendo threads
 *     atravéz dessas chamadas.
 *
 *     Faz parte do Process Manager, 
 *     parte fundamental do Kernel Base. 
 *
 * History:
 *     2015 - Created by Fred Nora.
 */

// #todo
// We can use the psXXXXX prefix to export the methods.


#include <kernel.h>


/*
 ************************************
 * kfork: 
 *
 * @todo:
 *     Semelhante ao unix, isso deve criar um processo filho fazendo uma cópia 
 * dos parâmetros presentes no PCB do processo pai. Um tipo de clonagem. 
 * Depois obviamente a imagem do processo filho será carregada em um endereço 
 * físico diferente da imagem do processo pai.
 * Essa não precisa ser a rotina, pode ser apenas uma interface, que chama a 
 * rotina dofork() e outras se necessário.
 */


int kfork (void){

    debug_print ("threadi-kfork: [TODO]\n");

    //struct process_t *p;
	
	//p = (void *) processList[current_process];
	
	//...
	
	//dofork();

	//return (int) p->pid;
	
	//Ainda não implementada.
	
    return -1;
}


/*
 **************************************
 * KiFork:
 *    Inicio do módulo interno que chama a função fork.
 *    Isso é uma interface para a chamada à rotina fork.
 *    #todo: 
 *    As funções relativas às rotinas de fork
 *    podem ir para um arquivo que será compilado junto com o kernel.
 *    ex: fork.c
 */

int KiFork (void)
{

    // #todo 
    // Criar interface

    return (int) kfork();
}


/*
 * KiShowPreemptedTask
 * @todo: Substituir a palavra task por thread. KiShowPreemptedThread
 */

void KiShowPreemptedTask (void)
{
    //return;
}

 
/*
 * KiSetTaskStatus: #deletar
 *     @todo: Substituir a palavra task por thread. KiSetThreadStatus
 */ 

void KiSetTaskStatus (unsigned long status)
{
    // #todo: 
    // Criar interface para mudanca de status.

    set_task_status (status);
}


/*
 * KiGetTaskStatus #deletar
 * @todo: Substituir a palavra task por thread. KiGetThreadStatus
 * #bugbgu task não é um termo usado.
 */

unsigned long KiGetTaskStatus (void)
{
    return (unsigned long) get_task_status(); 
}


/*
 #deletar
 * KiSaveContextOfNewTask
 * @todo: Substituir a palavra task por thread. KiSaveContextOfNewThread
 *
 * ?? isso está muito estranho !!
 */
 
void KiSaveContextOfNewTask ( 
    int id, 
    unsigned long *task_address )
{
    debug_print ("KiSaveContextOfNewTask: [DEPRECATED] \n");
}



/* #todo: ?? de quem ?? processo ou thread */
void KiSetQuantum (unsigned long q)
{
    debug_print ("KiSetQuantum: [DEPRECATED] \n");
}


unsigned long KiGetQuantum (void)
{
    debug_print ("KiGetQuantum: [DEPRECATED] \n");
    return (unsigned long) 0; 
}


/* #todo: ?? de quem ?? processo ou thread */
void KiSetCurrentQuantum (unsigned long q)
{
    debug_print ("KiSetCurrentQuantum: [DEPRECATED] \n");
}


/* #todo: ?? de quem ?? processo ou thread */

unsigned long KiGetCurrentQuantum (void)
{
    debug_print ("KiGetCurrentQuantum: [DEPRECATED] \n");
    return (unsigned long) 0; 
}


/* #todo: ?? de quem ?? processo ou thread */
void KiSetNextQuantum ( unsigned long q )
{
    debug_print ("KiSetNextQuantum: [DEPRECATED] \n");
}


/* 
 #todo: 
  ?? de quem 
  ?? processo ou thread 
  */

unsigned long KiGetNextQuantum (void)
{
    debug_print ("KiGetNextQuantum: [DEPRECATED] \n");
    return (unsigned long) 0; 
}


void KiSetFocus (int pid)
{
    debug_print ("KiSetFocus: [DEPRECATED] \n");
}



int KiGetFocus (void)
{
    debug_print ("KiGetFocus: [DEPRECATED] \n");
    return 0;   //#bugbug: Use -1;
}


/* 
 #todo: 
 chamar função em debug.c 
 */
void KiDebugBreakpoint (void)
{
    debug_print ("KiDebugBreakpoint: [DEPRECATED] \n");
}


/* #deletar */
void KiShowTasksParameters (void)
{
    debug_print ("KiShowTasksParameters: [DEPRECATED] \n");
}



/*
 *****************************************
 * show_slots:
 *     Show info about all threads.
 */

void show_slots(){

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
             t->used == 1 && 
             t->magic == 1234 )
        {
            show_slot (t->tid);
        }
    };
}


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
        printf ("TID   PID   pdPA  Prio  State *Quan *Jiffies initial_eip eflags   tName \n");
        printf ("====  ====  ====  ====  ===== ==== ====    ==========  ======  ===== \n");
        printf ("%d    %d    %x   %d    %d    %d   %d      %x          %x      %s \n", 
            t->tid, 
            t->ownerPID,
            t->DirectoryPA,
            t->priority, 
            t->state,
            t->quantum,    // Quantum
            t->step,       // Jiffies
            t->initial_eip,
            t->eflags,
            t->name_address );
    };

    goto done;


fail:
    printf ("Fail\n");

done:
    return; 
}


/*
 *************************************************
 * show_reg:
 *     Show the content of the registers.
 * 
 *    eflags
 *    cs:eip
 *    ss:esp
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

        printf ("\n eflags=[%x]", t->eflags);
        printf ("\n cs:eip=[%x:%x] ss:esp=[%x:%x]", 
            t->cs, t->eip, t->ss, t->esp );
        printf ("\n ds=[%x] es=[%x] fs=[%x] gs=[%x]",
            t->ds, t->es, t->fs, t->gs );
        printf ("\n a=[%x] b=[%x] c=[%x] d=[%x]\n",
            t->eax, t->ebx, t->ecx, t->edx );
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
 ************************************************************
 * SetThreadDirectory:
 *     Altera o endereço do diretório de páginas de uma thread.
 *     Apenas a variável. Não altera o CR3.
 */
 
void 
SetThreadDirectory ( 
    struct thread_d *thread, 
    unsigned long Address )
{

    if ( (void *) thread == NULL ){
        //
        return;

    }else{
		
		//@todo:
		//Aqui podemos checar a validade da estrutura,
		//antes de operarmos nela.
		
		thread->DirectoryPA = (unsigned long) Address;	
    };
}


/*
 ***********************************************************
 * GetThreadDirectory:
 *     Pega o endereço do diretório de páginas de uma thread.
 */
 
unsigned long GetThreadDirectory ( struct thread_d *thread ){
	
    if ( (void *) thread == NULL ){
		//
        return (unsigned long) 0;    

    }else{
		
		//@todo:
		//Aqui podemos checar a validade da estrutura,
		//antes de operarmos nela.
		
	    return (unsigned long) thread->DirectoryPA;		
    };


    return (unsigned long) 0;
}


/*
 * show_preempted_task: #deletar
 *
 *    Mostrar informações sobre a tarefa de baixa prioridade
 *    que teve seu contexto salvo e deu a vez pra outra de
 *    maior prioridade.
 *
 *    @todo: Criar uma variavel global que identifique
 *           a tarefa com contexto salvo.
 */

void show_preempted_task (void)
{
    debug_print("show_preempted_task: [DEPRECATED]\n");
}

/*  #deletar  */
void show_tasks_parameters (void)
{
    debug_print("show_tasks_parameters: [DEPRECATED]\n");
}



/*
 ****************************************
 * release:
 * #importante
 * Isso deve liberar uma thread que estava esperando 
 * ou bloqueada por algum motivo.
 * Obs: Aqui não devemos julgar se ela pode ou não ser
 * liberada, apenas alteramos se estado.
 *
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
		
        if ( Thread->magic != THREAD_MAGIC ){
			
			return; 
		}
		
		//#importante:
		//Não estamos selecionando ela para execução
		//Apenas estamos dizendo que ela está pronta para
		//executar.
		
		Thread->state = READY; 
    };
}




/*
 *****************************************************
 * kill_thread:
 *     Destrói uma thread.
 *     Destroi a estrutura e libera o espaço na lista.
 */

void kill_thread (int tid){

    struct thread_d *__Thread;


	//Limits.
    if ( tid < 0 || tid >= THREAD_COUNT_MAX ){
        debug_print ("kill_thread: tid");
        return;
    }


    // #bugbug
    // The IDLE thread.
    
    if ( (void *) ____IDLE == NULL ){
        panic ("kill_thread: ____IDLE fail");
    
    }else{

        if ( ____IDLE->used != 1 || ____IDLE->magic != 1234 )
        {
            panic ("kill_thread: ____IDLE validation");
        }

	    // Se queremos deletar a idle.
        if ( tid == ____IDLE->tid ){
            panic ("kill_thread: Sorry, we can't kill the idle thread!");
	    }
	    // ...
    };

	
	//
	// @todo: 
	//    Deve acordar o pai que está esperando o filho fechar.
	//    Mas no caso estamos apenas fechando uma thread.
    //    Caso essa não seja a thread primária, isso não deve 
    // causar o fechamento do processo.	
    //

    __Thread = (void *) threadList[tid];

	// A thread alvo nem existe,
	// vamos apenas continuar.

    if ( (void *) __Thread == NULL ){
        printf ("kill_thread: This thread doesn't exist!\n");
        refresh_screen();
        return;

    }else{


        /*
        // This process can't be killed by another process.
        if ( __Thread->_protected == 1 )
        {
            debug_print("exit_process: [FAIL] This thread can't be killed\n");
            debug_print("This is a protected thread!\n");
            return;  
        }
        */


        // #todo 
        // Pegar o id do pai e enviar um sinal e acorda-lo
        //se ele estiver esperando por filho.		
        __Thread->used = 0;
        __Thread->magic = 0; 
        __Thread->state = DEAD; 
        // ...


		//ProcessorBlock.threads_counter--;
		//if ( ProcessorBlock.threads_counter < 1 ){
			//#bugbug
			//panic("kill_thread: threads_counter");
		//}

        UPProcessorBlock.threads_counter--;
        if ( UPProcessorBlock.threads_counter < 1 ){
            panic ("kill_thread: threads_counter");
        }


        threadList[tid] = (unsigned long) 0;
        __Thread = NULL;		
        
         
        // se matamos a thread atual.         
        if ( tid == current_thread )
            scheduler ();

        
        // Se falhou o escalonamento.
        if ( current_thread < 0 || 
             current_thread >= THREAD_COUNT_MAX )
        {
            current_thread = ____IDLE->tid;
        }
    };


done:
    debug_print ("kill_thread: done\n");
    return;
}


/*
 * dead_thread_collector:
 *     Procura por uma thread no estado zombie mata ela.
 *     #todo: Alertar o processo que a thread morreu.
 */
 
void dead_thread_collector (void){

    register int i=0;  //loop
    
    struct process_d  *p; 
    struct thread_d   *Thread; 


	//
	// Check idle
	//

    if ( (void *) ____IDLE == NULL ){
        panic ("dead_thread_collector: ____IDLE fail");

    }else{

        if ( ____IDLE->used != 1 || ____IDLE->magic != 1234 )
        {
            panic ("dead_thread_collector: ____IDLE validation");
        }
        // ...
    };

    // loop
    // Scan
    for ( i=0; i < THREAD_COUNT_MAX; i++ )
    {
	    Thread = (void *) threadList[i];
		
		if ( (void *) Thread != NULL )
		{
		    if ( Thread->state == ZOMBIE && 
			     Thread->used == 1 && 
				 Thread->magic == 1234 )
			{

                // Se queremos deletar a idle.
                if ( Thread->tid == ____IDLE->tid ){
                    panic ("dead_thread_collector: Sorry, we can't kill the idle thread!");
                }

				//kill_thread(Thread->tid);
				Thread->used = 0;
				Thread->magic = 0;
				Thread->state = DEAD; // Por enquanto apenas fecha.
				//...
			    
				// #importante:
				// Nessa hora precisamos notificar o 
				// a thread que estava esperando essa thread  
				// terminar.
				// Se essa for a thread primária então o processo 
				// irá terminar também, então o processo que esperava 
				// também deverá ser notificado.
				
                //Thread = NULL;
	            //threadList[i] = NULL;   //@todo: Liberar o espaço na lista.


				//ProcessorBlock.threads_counter--;
				//if ( ProcessorBlock.threads_counter < 1 ){
					//panic("dead_thread_collector: threads_counter");
				//}

				UPProcessorBlock.threads_counter--;
				if ( UPProcessorBlock.threads_counter < 1 ){
					panic ("dead_thread_collector: threads_counter");
				}

			};
			//Nothing.
		};
		//Nothing.
	};
	
	//@todo:
	// * MOVEMENT 10 (zombie --> Dead)
	// * MOVEMENT 11 (zombie --> Initialized) .. reinicializar.	
}


void kill_all_threads (void)
{
    register int i=0;
    for ( i=0; i < THREAD_COUNT_MAX; ++i ){ kill_thread(i); };
}


// se a flag estiver habilitada, então devemos acorar a
// thread do dead thread collector.
void check_for_dead_thread_collector (void){
	
	// #importante
	// Essa flag é acionada quando uma thread entra em estado zombie.
	
	switch (dead_thread_collector_flag)
	{
		// waik up
		case 1:
			
			// Liberamos a thread.
			// O próprio dead thread collector vai sinalizar que 
			// quer dormir, dai o case default faz isso.
			
            release ( RING0IDLEThread->tid );
            break;
			
		// sleep
		default:
			block_for_a_reason ( RING0IDLEThread->tid, 
			    WAIT_REASON_BLOCKED );
			dead_thread_collector_flag = 0;
			break;
	};
}

//
// End.
//

