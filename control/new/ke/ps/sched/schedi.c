
// schedi.c

#include <kernel.h>  


/*
 * KiScheduler:
 *    Interface para chamar a rotina de scheduler.
 *    Troca as threads que estão em user mode, 
 * usando o método cooperativo. 
 * Round Robing. 
 *    As tarefas tem a mesma prioridade.
 *    + Quando encontrada uma tarefa de maior prioridade, 
 * escolhe ela imediatamente.
 *    + Quando encontrar uma tarefa de menor prioridade, 
 * apenas eleva a prioridade dela em até dois valores 
 * acima da prioridade base, pegando a próxima tarefa. 
 *    + Quando uma tarefa está rodando à dois valores 
 * acima da sua prioridade, volta a prioridade para a 
 * sua prioridade básica e executa.
 */

// OUT: next tid.
tid_t KiScheduler(void)
{

// #bugbug
// Quem está chamando? 
// Filtros?
// #todo: 
// Talvez haja mais casos onde não se deva trocar a tarefa.

//#bugbug 
//Porque retornamos 0 ???
//Scheduler Status. (LOCKED, UNLOCKED).

    if (g_scheduler_status == LOCKED)
    {
        debug_print ("KiScheduler: Locked $\n");
        
        // #bugbug
        // Why are we returning tid 0?
        
        //return 0;
        return -1;  //error
    }

// Não existem threads nesse processador.

    if ( UPProcessorBlock.threads_counter == 0 ){
        panic("KiScheduler: UPProcessorBlock.threads_counter == 0\n");
    }

// So existe uma thread nesse processador.
// Então ela precisa ser a idle.
// Ela será a current_thread.

    if ( UPProcessorBlock.threads_counter == 1 )
    {         
        Conductor = 
            (struct thread_d *) UPProcessorBlock.IdleThread;
        
        current_thread = (tid_t) Conductor->tid;
        
        debug_print("schedi: Idle $\n");
        
        // Return tid.
        return (tid_t) current_thread;
    }

// Scheduler
// Return tid.

    return (tid_t) scheduler();
}

// 0, 11
void do_thread_initialized(tid_t tid)
{
    struct thread_d  *t;

    if (tid < 0 || tid >= THREAD_COUNT_MAX)
    {
        return;
    }

    t = (void *) threadList[tid];

    if ( (void*) t == NULL ){
        return;
    }

    if (t->used != TRUE){
        return;
    }

    if (t->magic != 1234){
        return;
    }

    t->state = INITIALIZED;
}

// 1
void do_thread_standby(tid_t tid)
{
    struct thread_d *t; 

    if (tid < 0 || tid >= THREAD_COUNT_MAX)
    {
        return;
    }

    t = (void *) threadList[tid];

    if ( (void*) t == NULL ){
        return;
    }

    if (t->used != TRUE){
        return;
    }

    if (t->magic != 1234){
        return;
    }

    t->state = STANDBY;
}

// 2,4
void do_thread_running(tid_t tid)
{
    struct thread_d *t; 

    if (tid < 0 || tid >= THREAD_COUNT_MAX)
    {
        return;
    }

    t = (void *) threadList[tid];

    if ( (void *) t != NULL ){
        if ( t->used == TRUE && t->magic == 1234 )
        {
            t->state = RUNNING;
        }
    }
}

// 3,6
void do_thread_ready(tid_t tid)
{
    struct thread_d  *t;


    if ( tid < 0 || 
         tid >= THREAD_COUNT_MAX )
    {
        return;
    }

    t = (void *) threadList[tid];

    if ( (void*) t == NULL ){
        return;
    }

    if (t->used != TRUE){
        return;
    }

    if (t->magic != 1234){
        return;
    }

// #todo
// Se a thread estiver rodando no momento
// e ela mesmo ou uma thread de outro núcleo
// chamou essa rotina, então precisamos reescalonar ?

/*
    if (t->state == RUNNING)
    {
        // Set the 'Need to reeschedule' flag.
    }
*/

    t->state = READY;
    t->ready_jiffie = (unsigned long) jiffies;
}

// 5, 13
void do_thread_waiting(tid_t tid)
{
    struct thread_d *t; 

    if (tid < 0 || tid >= THREAD_COUNT_MAX)
    {
        return;
    }

    t = (void *) threadList[tid];

    if ( (void*) t == NULL ){
        return;
    }

    if (t->used != TRUE){
        return;
    }

    if (t->magic != 1234){
        return;
    }

    t->state = WAITING;
    t->waiting_jiffie = (unsigned long) jiffies;
}

// 12, 7
// do_thread_sleeping:
// Muda o state de uma thread pra blocked.
// #todo: Mudar o nome da função para do_thread_blocked.

void do_thread_blocked(tid_t tid)
{
    struct thread_d  *t; 

    if (tid < 0 || tid >= THREAD_COUNT_MAX)
    {
        return;
    }

    t = (void *) threadList[tid];

    if ( (void*) t == NULL ){
        return;
    }

    if (t->used != TRUE){
        return;
    }

    if (t->magic != 1234){
        return;
    }

// #todo
// Se a thread estiver rodando no momento
// e ela mesmo ou uma thread de outro núcleo
// chamou essa rotina, então precisamos reescalonar ?

/*
    if (t->state == RUNNING)
    {
        // Set the 'Need to reeschedule' flag.
    }
*/

    t->state = BLOCKED;
    t->blocked_jiffie = (unsigned long) jiffies;
}

// 9
void do_thread_zombie(tid_t tid)
{
    struct thread_d  *t; 


    if (tid < 0 || tid >= THREAD_COUNT_MAX)
    {
        return;
    }

    t = (void *) threadList[tid]; 

    if ( (void*) t == NULL ){
        return;
    }

    if (t->used != TRUE){
        return;
    }

    if (t->magic != 1234){
        return;
    }

// #test
// Can't close the init thread for now.

    if ( tid == INIT_TID ){
        return;
    }

    t->state = ZOMBIE;
    t->zombie_jiffie = (unsigned long) jiffies;
}

// 10
void do_thread_dead(tid_t tid)
{
    struct thread_d  *t;

    if (tid < 0 || tid >= THREAD_COUNT_MAX)
    {
        return;
    }

    t = (void *) threadList[tid];

    if ( (void*) t == NULL ){
        return;
    }

    if (t->used != TRUE){
        return;
    }

    if(t->magic != 1234){
        return;
    }

    t->state = DEAD;
}

// ----------------------

void drop_quantum(struct thread_d *thread)
{
    if ( (void*) thread == NULL )
        return;
    if (thread->magic!=1234)
        return;

    thread->quantum = QUANTUM_MIN;
}


/*
 * do_waitpid:
 *     espera por qualquer um do processo filho.
 */

//#todo 
//vamos apenas lidar com a estrutura de processo.
//#importante: o kernel terá a obrigação de 
//finalizar o processo quando sua thread primária ficar em zombie. 
//poi um processo tem várias threads, e se uma fechar não significa que o 
//processo terminou. Por isso vamos apenas checar o estado dos processos e 
//não das threads.
//rever essa função, há muito o que fazer nela 
//ela precisa retornar valores padronizados e configurar 
//o status recebido

int do_waitpid (pid_t pid, int *status, int options)
{
    struct process_d *p;  

    pid_t current_process = (pid_t) get_current_process();

    //#debug
    //printf ( "do_waitpid: current_process=%d pid=%d \n", 
        //current_process, pid );

    // #todo
    // tem que bloquear o processo atual até que um dos seus 
    // processos filhos seja fechado.

    p = (struct process_d *) processList[current_process];

    if ( (void *) p == NULL ){
        printf ("do_waitpid: Current process struct fail\n");
        return -1;
   
    }else{

        if ( p->used != 1 || p->magic != 1234 ){
            debug_print ("do_waitpid: validation\n");
        }
        
        // #todo: Esse if não é necessário.
        if ( p->used == 1 && p->magic == 1234 )
        {

            //#debug
            //printf ("blocking process\n");
            
            p->state = PROCESS_BLOCKED;


			//significa que está esperando por qualquer
			//um dos filhos.
            p->wait4pid = (pid_t) pid; 

            //checando se a thread atual é a thread de controle. 
            if (current_thread == p->control->tid )
            {
                //#debug
                //printf ("the current thread is also the control thread\n");
            }
           
            //printf ("blocking thread\n");
            //tem que bloquear todas as threads do pai.
            //Isso pode estar falhando;
            //block_for_a_reason ( (int) p->control, (int) WAIT_REASON_WAIT4PID );
            p->control->state = BLOCKED; 
       }
   };


	//aqui precisamos dar informações sobre o status 
	//do processo

    // #bugbug: Isso pode ter falhado.
    //fake value. 
    //*status = 1; 


    //#debug
    //printf ("do_waitpid: done. \n");
    //refresh_screen();

    return (int) (-1);
}

/* 
 * get_current:
 *     Obtendo o TID da thread atual. 
 */

int get_current_thread (void)
{
    return (int) current_thread;
}



/* 
 * set_current:
 */
 
void set_current_thread (int tid)
{
    struct thread_d  *t; 


    if (tid < 0 || tid >= THREAD_COUNT_MAX)
    {
        return;
    }

    if ( tid == current_thread )
    {  
        return;
    }

// struct

    t = (void *) threadList[tid]; 

    if( (void*) t == NULL )
        return;

    if(t->used != TRUE)
        return;

    if(t->magic != 1234)
        return;


// Change global variable.
    current_thread = (int) tid;
}


/*
 * wait_for_a_reason:
 *     Faz a thread esperar  por um motivo.
 */

void wait_for_a_reason ( int tid, int reason ){

    struct thread_d  *t;

    // #debug
    printf ("wait_for_a_reason: %d\n", reason);

    // tid
    if ( tid < 0 || tid >= THREAD_COUNT_MAX )
    {
        debug_print ("wait_for_a_reason: validation\n");
        return;
    } 

    // reason
    if ( reason < 0 || reason >= 10 ){
        debug_print ("wait_for_a_reason: limits\n");
        return;
    }

//
// Thread
//

    t = (struct thread_d *) threadList[tid];

    if ( (void *) t == NULL ){
        debug_print ("wait_for_a_reason: t\n");
        return;

    } else {

        if ( t->used != 1 || t->magic != 1234 ){
            debug_print ("wait_for_a_reason: t validation\n");
        }

        if ( t->used == TRUE && t->magic == 1234 )
        {
            // t->wait_reason[reason] = 1;

            // ## Wait ##
            t->state =  WAITING;
        }
    };

   //KiScheduler ();
   
   // #debug
   printf ("wait_for_a_reason: done\n");
   refresh_screen();
}


/*
 * wakeup_thread_reason:
 * 
 */

//acordar uma determinada thread se ela estiver 
//esperando por um evento desse tipo.
//uma outra função pode fazer um loop acordando 
//todas as threads que esperam pelo memso motivo.

int wakeup_thread_reason ( int tid, int reason )
{
    panic("wakeup_thread_reason: #todo\n");

/*
    struct thread_d *t;


    // tid
    if ( tid < 0 || tid >= THREAD_COUNT_MAX ){
        debug_print ("wakeup_thread_reason: tid\n");
        goto fail;
    } 

    // reason
    if ( reason < 0 || reason >= 10 ){
        debug_print ("wakeup_thread_reason: reason\n");
        goto fail;
    }

//
// Thread
//

    t = (struct thread_d *) threadList[tid];

    if ( (void *) t == NULL ){
        debug_print ("wakeup_thread_reason: t\n");
        goto fail;

    } else {

        if ( t->used != TRUE || t->magic != 1234 ){
            debug_print ("wakeup_thread_reason: t validation\n");
            goto fail;
        }

		// OK.
        if ( t->wait_reason[reason] != 1 ){
            debug_print ("wakeup_thread_reason: status\n");
            goto fail;

        } else {

            //ok 

            switch (reason)
            {
				//Esperando um processo morrer. Mas qual ??
				case WAIT_REASON_WAIT4PID: 
				    //se o processo que acabamos de fechar for o mesmo que 
					//a thread estava esperando.
					if ( current_dead_process > 0 && 
					     current_dead_process == t->wait4pid )
					{
					    t->wait_reason[reason] = 0;
					    do_thread_ready (tid);
					}
					break;
					
				//Esperando uma thread morrer. Mas qual ??
				case WAIT_REASON_WAIT4TID:
				    //se a thread que acabamos de fechar for a mesma que 
					//a thread estava esperando.
					if ( current_dead_thread > 0 && 
					     current_dead_thread == t->wait4tid )
					{
					    t->wait_reason[reason] = 0;
					    do_thread_ready (tid);
					}
					break;
					
				case WAIT_REASON_TEST:
					t->wait_reason[reason] = 0;
					do_thread_ready (tid);
				    break;
			    
                // ...
			}
			
            goto done;
		}
		
		//nothing
    };

fail:
    return (int) 1;
*/

done:
    return 0;
}

/*
 * wakeup_scan_thread_reason:
 * 
 */
// Acorda todas as threads da lista que estão esperando por 
// evento de determinado tipo.

int wakeup_scan_thread_reason ( int reason )
{
    panic("wakeup_scan_thread_reason: #todo\n");

/*
    //loop
    register int i=0;

    // #debug ??
    // printf ("wakeup_scan_thread_reason: %d", reason);
    // refresh_screen();

    // reason
    if ( reason < 0 || reason >= 10 ){
        debug_print ("wakeup_scan_thread_reason: reason\n");
        goto fail;
    } 

    // loop
    for ( i=0; i<THREAD_COUNT_MAX; ++i )
    {
        wakeup_thread_reason ( i, reason );
    };


//done:

    // #debug
    printf ("wakeup_scan_thread_reason: done\n");
    refresh_screen();
    
    return 0;

// Fail

fail:

    // #debug
    printf ("wakeup_scan_thread_reason: fail\n");
    refresh_screen();

*/
    return (int) 1;
}


/*
 * wakeup_thread: 
 *    Para acordar uma thread, basta colocar ela no 
 * estado READY se ela estiver com seu contexto 
 * salvo e seu estado WAITING.
 *    Estando em READY o scheduler vai escalonar ela quando
 * for possível.
 */

void wakeup_thread(int tid)
{
    struct thread_d  *t;
    int Status=0;


    if ( tid < 0 || 
         tid >= THREAD_COUNT_MAX )
    {
        return;
    }

    t = (void *) threadList[tid]; 

    if ( (void *) t == NULL )
    {
        return;
    }

    if ( t->used != TRUE ){
        return;
    }

    if ( t->magic != 1234 ){
        return;
    }

// Se o contexto não foi salvo. 
// Não tem como acorda-la.
// Pois acordar significa apenas retornar ao estado RUNNING.

    if ( t->saved == FALSE )
    {
        return; 
    }

// Se a thread ja está acordada, então não há mais o que fazer.
    if (t->state == READY)
    {
        return;
    }


// Não podemos acordar uma thread que ja está rodando.
// Ela precisa estar esperando.

    if (t->state == RUNNING)
    {
        return;
    }


// Se estiver bloqueada, 
// não tem como acordar ainda. 
// precisa desbloquear.

    if (t->state == BLOCKED)
    { 
        return; 
    }

// Isso acorda a thread.

    do_thread_ready(tid);
}


// Yield
// Set a flag that this thread will be preempted.
// Desiste do tempo de processamento.
// cooperativo.
// Muda o seu tempo executando para: Próximo de acabar.

void yield (tid_t tid)
{
    struct thread_d  *t;

// tid
    if (tid < 0 || tid >= THREAD_COUNT_MAX)
    {
        return;
    }

// Thread
    t = (void *) threadList[tid];
    if ( (void *) t == NULL ){  return;  }
    if ( t->used != TRUE || t->magic != 1234 )
    {
        return;
    }

// Flag 
// 1 = Sinaliza que a thread está dando a preferência
// e que deve sair quando for seguro fazer isso.
// Agenda o yield.
// >>> O ts.c vai fazer isso na hora certa.
// O ts.c vai esgotar o quantum dessa thread
// no momento do task switching.
// Isso não deve afetar a prioridde da thread.

    t->yield_in_progress = TRUE;
}


/*
int 
sched_thread (
    struct thread_d *t, 
    unsigned long quantum,
    unsigned long priority );
int 
sched_thread (
    struct thread_d *t, 
    unsigned long quantum,
    unsigned long priority )
{
    if ( (void*) t == NULL )
        return -1;
    if (t->magic != 1234)
        return -1;

// quantum
    if (quantum>QUANTUM_MAX){
        return -1;
    }
    t->quantum = (unsigned long) quantum;

// priority
    if (priority>PRIORITY_MAX){
        return -1;
    }
    t->priority = (unsigned long) priority;

    return 0;
}
*/

//#bugbug: Suspended.
void set_input_responder_tid(int tid)
{
    if( tid < 0 )
        return;

    if( tid >= THREAD_COUNT_MAX )
        return;

    // #todo
    // We can check the struct validation

// Set tid
    input_responder_tid = (int) tid;

// Set flag
    flagUseThisInputResponder = TRUE;
}


// #deprecated
// Let's check if one thread was selected to run imediatly
// because we had an input event.
// This way the reponder doesn't deed to wait the end 
// of the round to run.
// OUT:
//  -1: No thread was selected
// tid: The tid of the selected thread.

int check_for_input_responder(void)
{

//
// #deprecated
//


    struct thread_d *t;


// No responder
    if (flagUseThisInputResponder != TRUE )
        return -1;

    if( input_responder_tid < 0 )
        return -1;

    if( input_responder_tid >= THREAD_COUNT_MAX )
        return -1;

    t = (struct thread_d *) threadList[input_responder_tid];

    if( (void*) t == NULL )
        return -1;

    if (t->used!=TRUE)
        return -1;

    if (t->magic!=1234)
        return -1;

// Cut the round
// This way the scheduler will be called.

    t->next = NULL;

done:
    flagUseThisInputResponder = FALSE;
    // Return a valid tid
    return (int) input_responder_tid;
}


/*
 * check_for_standby:
 * Check for a thread in standby.
 * In this case, this routine will not return.
 * Procura na lista de threads no estado StandyBy.
 * Se tiver uma thread nessa lista, ela se torna 
 * a current. Para rodar pela primeira vez, atravéz de Spawn.
 * Não retorna se encontrar uma threa na lista.
 */
// Called by __on_finished_executing() in ts.c.

void check_for_standby(void)
{
    register int i = 0;
    register int Max = THREAD_COUNT_MAX;
    int newId=0;
    struct thread_d  *New;

//#ifdef SERIAL_DEBUG_VERBOSE
    //debug_print (" check_for_standby ");
    //debug_print (" Check ");
//#endif

    do {

        // #todo: 
        // As filas ainda não funcionam.
        // Vamos usar a lista global.
        //New = (void *) queue->standbyList[i];
        
        New = (void *) threadList[i];
        
        if ( (void *) New != NULL )
        {
            if ( New->used  == TRUE && 
                 New->magic == 1234 && 
                 New->state == STANDBY ) 
            {
                current_thread = (int) New->tid;
                goto do_spawn;
            }
        }

        i++;

    // Todas as threads da lista global.
    } while (i < Max); 

// Done: 
// Nenhuma tarefa precisa ser inicializada.
// Podemos apenas retornar para o taskswitch.

//#ifdef SERIAL_DEBUG_VERBOSE
    //debug_print (" Nothing ");
//#endif

    return;

//
// Spawn
//

// See: spawn.c
do_spawn:

    if( current_thread < 0 ||
        current_thread >= THREAD_COUNT_MAX )
    {
        goto fail;
    }

// A init thread foi a primeira thread a rodar.
// Não podemos fazer spawn dela, pois ela tem uma rotina
// especial para isso.
    if ( current_thread == INIT_TID ){
        panic("check_for_standby: Can't spawn INIT_TID\n");
    }

    KiSpawnThread(current_thread);

// Not reached.
fail:
    panic("check_for_standby: ERROR\n");
}


//
// End.
//
























































