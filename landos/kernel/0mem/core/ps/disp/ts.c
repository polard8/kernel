/*
 * File: ps/disp/ts.c
 *
 *     Task Switching.
 *     Part of the dispatcher module.
 *
 *     +Save the context of a thread.
 *     +Call scheduler to switch the thread.
 *     +Call dispatcher to dispatch a thread.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - 2021 Revision and small changes.
 */


#include <kernel.h>


//
// Variáveis internas.
//

int lock_taskswitch;  


//
// ...
//

/*
void taskswitchFlushTLB();
void taskswitchFlushTLB(){
	//@todo: Implementar.
	return;
}
*/


/*
 ****************************************************
 * psTaskSwitch:
 * 
 *     Interface para chamar a rotina de Task Switch.
 *     Essa rotina somente é chamada por hw.inc.
 *     KiTaskSwitch em ts.c gerencia a rotina de 
 * troca de thread, realizando operações de salvamento e 
 * restauração de contexto utilizado variáveis globais e 
 * extrutura de dados, seleciona a próxima thread através 
 * do scheduler, despacha a thread selecionada através do 
 * dispatcher e retorna para a função _irq0 em hw.inc, 
 * que configurará os registradores e executará a 
 * thread através do método iret.
 *
 * #importante:
 * Na verdade, é uma interface pra uma rotina que 
 * faz tudo isso.
 * 
 */
 
/*
	// @todo: Fazer alguma rotina antes aqui ?!
	
	// Obs: A qui poderemos criar rotinas que não lidem com a troca de 
	// threads propriamente, mas com atualizações de variáveis e gerenciamento 
	// de contagem.
	// >> Na entrada da rotina podemos atualizar a contagem da tarefa que acabou de rodar.
	// >> A rotina task_switch fica responsável apenas troca de contexto, não fazendo 
	// atualização de variáveis de contagem.
	// >> ?? Na saída ??
	
	// ?? quem atualizou as variáveis de critério de escolha ??? o dispacher ??
*/


// Called by:
// _irq0 in hw.asm

void psTaskSwitch (void){

    // Check current process limits.
    if ( current_process < 0 || current_process >= PROCESS_COUNT_MAX )
    {
        printf ("psTaskSwitch: current_thread %d", current_process );
        die();
    }

    // Check current thread limits.
    if ( current_thread < 0 || current_thread >= THREAD_COUNT_MAX )
    {
        printf ("psTaskSwitch: current_thread %d", current_thread ); 
        die();
    }

#ifdef SERIAL_DEBUG_VERBOSE
    debug_print (".");
    // debug_print ("ts ");
#endif

    //
    // real task switch
    //

    task_switch();

    // obs: 
    // Nessa hora já temos um thread atual e um processo atual 
    // selecionados. Podemos checar as variáveis para conferir se 
    // não está fora dos limites. Se estiverem fora dos limites, 
    // podemos usar algum método para selecionarmos outro processo 
    // ou outra thread com limites válidos.
 
    // #importante:   
    // Retornando para _irq0 em x86/hw.inc.
}


// Internal
// Call extra routines scheduled to this moment.
// called by task_switch.
// #importante:
// Checaremos por atividades extras que foram agendadas pelo 
// mecanismo de request. Isso depois do contexto ter sido 
// salvo e antes de selecionarmos a próxima thread.

void tsCallExtraRoutines(void)
{
    // Kernel requests.
    KiRequest();

    // Unix signals.
    KiSignal();

    // ...

    // #todo: 
    // Talvez possamos incluir mais atividades extras.
}


/*
 **********************************************************
 * task_switch:
 *
 * Switch the thread.
 * Save and restore context.
 * Select the next thread and dispatch.
 * return to _irq0.
 * Called by KiTaskSwitch.
 */
 
void task_switch (void){

    struct process_d  *P;
    struct thread_d   *Current;

    pid_t pid = -1;


    // Current thread. 


    // Check current thread limits.
    if ( current_thread < 0 || current_thread >= THREAD_COUNT_MAX )
    {
        panic ("ts-task_switch: current_thread\n");
    }

    Current = (void *) threadList[current_thread]; 

    if ( (void *) Current == NULL ){
        panic ("ts-task_switch: Current\n");
    }
    
    // #todo
    // Check the thread's validation. 
    // used and magic.


    // Current process. 
    
    pid = (pid_t) Current->ownerPID;

    // #todo: Check overflow too.
    if (pid<0){
        panic ("ts-task_switch: pid\n");
    }

    P = (void *) processList[pid];

    if ( (void *) P == NULL ){
        panic ("ts-task_switch: P\n");
    }

    // validation
    if ( P->used != TRUE && P->magic != 1234 )
    {
        panic ("ts-task_switch: P validation\n");
    }

   // Update the global variable.

   current_process = (int) P->pid;

//
//  == Conting =================================
//

    // 1 second = 1000 milliseconds
    // sys_time_hz = 600 ticks per second.
    //1/600 de segundo a cada tick
    //1000/100 = 10 ms quando em 100HZ.
    //1000/600 = 1.x ms quando em 600HZ.
    //x = 0 + (x ms); 


    // step: 
    // Quantas vezes ela já rodou no total.
    Current->step++; 

    // runningCount: 
    // Quanto tempo ela está rodando antes de parar.
    Current->runningCount++;

    //
    // == #bugbug ==============================================
    //

	// #bugbug
	// Rever essa contagem
/*
The variables i have are:
Current->step = How many timer the thread already ran.
sys_time_hz = The timer frequency. (600Hz).
No double type, no float type.
----------
600Hz means that we have 600 ticks per second.
With 100 Hz we have 10 milliseconds per tick. ((1000/100)=10)
With 600Hz we have 1.66666666667 milliseconds per tick.   ((1000/600)=1)
------
Maybe i will try 500Hz.
With 600Hz we have 2 milliseconds per tick.   ((1000/500)=2)
----
This is a very poor incrementation method:
Current->total_time_ms = Current->total_time_ms + (1000/sys_time_hz);
The remainder ??
----
*/

	//quanto tempo em ms ele rodou no total.
    Current->total_time_ms = (unsigned long) Current->total_time_ms + (1000/sys_time_hz);

	//incrementa a quantidade de ms que ela está rodando antes de parar.
	//isso precisa ser zerado quando ela reiniciar no próximo round.
    Current->runningCount_ms = (unsigned long) Current->runningCount_ms + (1000/sys_time_hz);



//
// == Locked ? ===============================
//

    // Taskswitch locked? 
    // Return without saving.

    if ( task_switch_status == LOCKED ){
        IncrementDispatcherCount (SELECT_CURRENT_COUNT);
        return; 
    }


//
// == Unlocked ? ==============================
//

    // Nesse momento a thread atual sofre preempção por tempo
    // Em seguida tentamos selecionar outra thread.

    if ( task_switch_status == UNLOCKED )
    {
        //
        // ## SAVE CONTEXT ##
        //

        save_current_context();
        Current->saved = TRUE;

		// #obs:
		// A preempção acontecerá por dois possíveis motivos.
		// + Se o timeslice acabar.
		// + Se a flag de yield foi acionada.

		// #importante:
		// Se a thread ainda não esgotou seu quantum, 
		// então ela continua usando o processador.

        if ( Current->runningCount < Current->quantum )
        {
            // Yield support.
            // Coloca no estado de pronto e limpa a flag.
            if ( Current->state == RUNNING && Current->_yield == 1 )
            {
                Current->state  = READY;
                Current->_yield = 0;
                goto try_next;
            }

            IncrementDispatcherCount (SELECT_CURRENT_COUNT);
            return; 

		// #importante
		// Nesse momento a thread [esgotou] seu quantum, 
		// então sofrerá preempção e outra thread será colocada 
		// para rodar de acordo com a ordem estabelecida 
		// pelo escalonador.

        }else{

            //
            // ==== ## PREEMPT ## ====
            //

            // >> MOVEMENT 3 (Running --> Ready).

            if ( Current->state == RUNNING )
            {
				// Preempt.
				// MOVEMENT 3 (running >> ready)  
				
				// sofrendo preempção por tempo.
				// #todo: Mas isso só poderia acontecer se a flag
				// ->preempted permitisse. 
				// talvez o certo seja ->preenptable.

                Current->state = READY;    

                // Se pode sofrer preenpção vai para fila de prontos.
                if ( Current->preempted == PREEMPTABLE )
                {
                    //debug_print (" preempt_q1 ");
                    queue_insert_head ( 
                        queue, (unsigned long) Current, QUEUE_READY );
                }

                if ( Current->preempted == UNPREEMPTABLE )
                {
                    //debug_print (" preempt_q2 ");
                    queue_insert_data ( 
                        queue, (unsigned long) Current, QUEUE_READY );
                }
            }

            //debug_print (" ok ");


            //
            // == EXTRA ===============================================
            //

            // Call extra routines scheduled to this moment.

            if (extra == TRUE){
                tsCallExtraRoutines();
                extra = FALSE;
            }

			// Dead thread collector
			// Avalia se é necessário acordar a thread do dead thread collector.
			// É uma thread em ring 0.
			// Só chamamos se ele ja estiver inicializado e rodando.
			
			// #bugbug
			// precismos rever essa questão pois isso pode estar
			// fazendo a idle thread dormir. Isso pode prejudicar
			// a contagem.

			// See: core/ps/threadi.c

            if (dead_thread_collector_status == TRUE)
            {
                // #bugbug
                // #todo: This is a work in progress!
                check_for_dead_thread_collector();
            }

            //
            // === Spawn nre thread ==================================
            //

            // Check for a thread in standby.
            // In this case, this routine will not return.
            // See: ts/sched/schedi.c

            check_for_standby(); 
            goto try_next;
        };
    }  //FI UNLOCKED


    //
    // == Crazy Fail ============================================
    //

	// #bugbug
	// Não deveríamos estar aqui.
	// Podemos abortar ou selecionar a próxima provisóriamente.

	//panic ("ts.c: crazy fail");

    goto dispatch_current; 


//
// == TRY NEXT THREAD ========================================
//

try_next: 

#ifdef SERIAL_DEBUG_VERBOSE
    debug_print(" N ");
#endif

    // We have only ONE thread.
    // Is that thread the idle thread?
    // Can we use the mwait instruction ?

    if (UPProcessorBlock.threads_counter == 1)
    {
        //debug_print(" JUSTONE ");
        
        // Is this a pointer?
        Conductor = ____IDLE;
        
        // If we will run only the idle thread, 
        // so we can use the mwait instruction. 
        // asm ("mwait"); 
        
        goto go_ahead;
    }


    //
    // ==== Reescalonar se chegamos ao fim do round. ====
    //

	// #bugbug
	// Ao fim do round estamos tendo problemas ao reescalonar 
	// Podemos tentar repedir o round só para teste...
	// depois melhoramos o reescalonamento.
		
	// #importante:
	// #todo: #test: 
	// De pempos em tempos uma interrupção pode chamar o escalonador,
	// ao invés de chamarmos o escalonador ao fim de todo round.
	
	// #critério:
	// Se alcançamos o fim da lista encadeada cujo ponteiro é 'Conductor'.
	// Então chamamos o scheduler para reescalonar as threads.


    if ( (void *) Conductor->next == NULL )
    {

#ifdef SERIAL_DEBUG_VERBOSE
        debug_print(" LAST ");
#endif

        //printf ("ts: scheduler 1\n");
        KiScheduler();
        goto go_ahead;
    }



	// #critério
	// Se ainda temos threads na lista encadeada, então selecionaremos
	// a próxima da lista.
	// #BUGBUG: ISSO PODE SER UM >>> ELSE <<< DO IF ACIMA.

    if ( (void *) Conductor->next != NULL )
    {
        Conductor = (void *) Conductor->next;
        goto go_ahead;
    }

    // #bugbug
    panic ("ts-task_switch: Unspected");


	//
	// == Go ahead ========================================
	//

	// #importante:
	// Nesse momento já temos uma thread selecionada,
	// vamos checar a validade e executar ela.
	// #importante:
	// Caso a thread selecionada não seja válida, temos duas opções,
	// ou chamamos o escalonador, ou saltamos para o início dessa rotina
	// para tentarmos outros critérios.

go_ahead:


//################################//
//                                //
//    # We have a thread now #    //
//                                //
//################################//


    Current = (void *) Conductor;

    if( (void *) Current == NULL )
    { 
        debug_print ("task_switch: Struct \n");
        KiScheduler();
        goto try_next;

    }else{

        if ( Current->used != TRUE || Current->magic != 1234 )
        {
            debug_print ("task_switch: val \n");
            KiScheduler ();
            goto try_next;
        }

        if ( Current->state != READY )
        {
            debug_print ("task_switch: state \n");
            KiScheduler ();
            goto try_next;
        }

        //
        // == Dispatcher =================================
        //

        // Current selected.
        current_thread = (int) Current->tid;
        goto dispatch_current;
    }


	//
	// fail
	//

//superCrazyFail:
    goto dispatch_current; 



// ===========================
//    # Dispatch current #
// ============================

dispatch_current:

#ifdef SERIAL_DEBUG_VERBOSE	
    debug_print (" DISPATCH_CURRENT \n");
#endif

    // Validation

    // Check current thread limits.
    if ( current_thread < 0 || current_thread >= THREAD_COUNT_MAX )
    {
        panic ("ts-task_switch: [Dispatch current] current_thread\n");
    }

    Current = (void *) threadList[current_thread];

    if ( (void *) Current == NULL ){
        panic ("ts-task_switch.dispatch_current: Struct\n");
    }

    // Validation
    if ( Current->used  != TRUE || 
         Current->magic != 1234 || 
         Current->state != READY )
    {
        panic ("task_switch.dispatch_current: validation\n");
    }

    Current->runningCount = 0;


	//
	// Call dispatcher. 
	//

    // #bugbug
    // Talvez aqui devemos indicar que a current foi selecionada. 
        
    IncrementDispatcherCount (SELECT_DISPATCHER_COUNT);

    //
    // MOVEMENT 4 (Ready --> Running).
    //

    dispatcher(DISPATCHER_CURRENT); 

//
// == DONE ======================================================
//

   // Wi will return in the end of this function

//done:

    // Owner validation.

    if ( Current->ownerPID < 0 || 
         Current->ownerPID >= THREAD_COUNT_MAX )
    {
       printf ("ts-task_switch: ownerPID ERROR \n", 
            Current->ownerPID );
       die();
    }


	//
	// ## PROCESS ## 
	//

    P = (void *) processList[Current->ownerPID];

    if ( (void *) P == NULL ){
        printf ("ts-task_switch: Process %s struct fail \n", P->name );
        die();
    }

    if ( (void *) P != NULL )
    {
        if ( P->used != 1 || P->magic != 1234 ){
            printf ("ts-task_switch: Process %s corrompido \n", 
                P->name );
            die ();
        }


        if ( P->used == 1 && P->magic == 1234 )
        {
            current_process = (int) P->pid;


            if ( (unsigned long) P->DirectoryPA == 0 ){
                printf ("ts-task_switch: Process %s directory fail\n", 
                    P->name );
                die();
            }

            //
            // Done
            //

            current_process_pagedirectory_address = (unsigned long) P->DirectoryPA;
            return;
        }
        panic ("ts-task_switch: * Struct * \n");
    }
 
    panic ("ts-task_switch: Unspected error\n");
}



/*
 ***************************************************
 * set_task_status:
 *    Configura o status do mecanismo de task switch.
 *    Se o mecanismo de taskswitch estiver desligado 
 * não ocorrerá a mudança.
 *
 * @todo: Mudar o nome dessa função para taskswitchSetStatus(.);
 *
 */ 
void set_task_status( unsigned long status )
{
    //#bugbug: Mudar para int.
    task_switch_status = (unsigned long) status;
}


/*
 * get_task_status:
 *     Obtem o status do mecanismo de taskswitch.
 * @todo: Mudar o nome dessa função para taskswitchGetStatus();.
 */

    //#bugbug: Mudar para int.
    
unsigned long get_task_status (void)
{
    return (unsigned long) task_switch_status;
}


/*
 * taskswitch_lock:
 *     Trava o mecanismo de taskswitch.
 *     @todo: Mudar para taskswitchLock().
 */ 

void taskswitch_lock (void)
{
    task_switch_status = (unsigned long) LOCKED;
}


/*
 * taskswitch_unlock:
 *     Destrava o mecanismo de taskswitch.
 *     @todo: Mudar para taskswitchUnlock().
 */ 

void taskswitch_unlock (void)
{
    task_switch_status = (unsigned long) UNLOCKED;
}


//
// End.
//
