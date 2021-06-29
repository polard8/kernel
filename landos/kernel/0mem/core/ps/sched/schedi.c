

#include <kernel.h>  


/*
 *************************************************
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
 *
 * @todo: 
 *     Essa rotina deve ter retorno do tipo 'int'.
 */

int KiScheduler (void){
    
	// ?? Quem está chamando ? Filtros ?
    // @todo: Talvez haja mais casos onde não se deva trocar a tarefa.

	//#bugbug 
	//Porque retornamos 0 ???
	//Scheduler Status. (LOCKED, UNLOCKED).


    if (g_scheduler_status == LOCKED){
        return 0;
    }

    
	//
	// Check idle
	//
	
    if ( (void *) ____IDLE == NULL ){
        panic ("KiScheduler: ____IDLE fail");

    }else{

        if ( ____IDLE->used != 1 || ____IDLE->magic != 1234 ){
            panic ("KiScheduler: ____IDLE validation");
        }

	    // ...
    };

	// Retornaremos se tivermos apenas um thread rodando.
	// Pois não há o que trocar.
	//Se só temos uma então devemos retornar a idle.

    //if ( ProcessorBlock.threads_counter == 1 )
    if ( UPProcessorBlock.threads_counter == 1 )
    { 
        current_thread = ____IDLE->tid;
        return (int) current_thread;
    }


    //Chama o Scheduler.

    return (int) scheduler();
}

/*
 ************************************************************
 * do_thread_sleeping:
 *     Muda o state de uma thread pra blocked.
 *     @todo: Mudar o nome da função para do_thread_blocked.
 */

// 7
void do_thread_blocked (int tid){

    struct thread_d *t; 

    // tid
    if (tid < 0 || tid >= THREAD_COUNT_MAX){
        return;
    }

    //
    // Thread.
    //

    t = (void *) threadList[tid];

    if ( (void *) t != NULL )
    {
        // #todo:
        // Validation
        t->state = BLOCKED;
    }
}

//3
void do_thread_dead (int tid){

    struct thread_d *t; 


    // tid
    if (tid < 0 || tid >= THREAD_COUNT_MAX){
        return;
    }

    //
    // Thread.
    //

    t = (void *) threadList[tid];

    if ( (void *) t != NULL )
    {
        // todo: validation
        t->state = DEAD;
    }
}

//0
void do_thread_initialized (int tid){

    struct thread_d *t; 


    if (tid < 0 || tid >= THREAD_COUNT_MAX){
        //todo message
        return;
    }

    //
    // Thread.
    //

    t = (void *) threadList[tid];

    if ( (void *) t != NULL )
    {
        // todo: validation
        //if ( t->used == 1 && t->magic == 1234 )
        t->state = INITIALIZED;
    }
}

//4  
void do_thread_ready (int tid)
{

    struct thread_d *t; 

    // tid
    if (tid < 0 || tid >= THREAD_COUNT_MAX){
        return;
    }

    //
    // Thread.
    //

    t = (void *) threadList[tid];

    if ( (void *) t != NULL )
    {
        // #todo: validation
        //if ( t->used == 1 && t->magic == 1234 )
        t->state = READY;
    }
}

//5
void do_thread_running (int tid){

    struct thread_d *t; 

    // tid
    if (tid < 0 || tid >= THREAD_COUNT_MAX){
        return;
    }

    //
    // Thread.
    //

    t = (void *) threadList[tid];

    if ( (void *) t != NULL )
    {
        if ( t->used == 1 && t->magic == 1234 ){
            t->state = RUNNING;
        }
    }
}

//1
void do_thread_standby (int tid)
{
    struct thread_d *t; 

    // tid
    if (tid < 0 || tid >= THREAD_COUNT_MAX){
        return;
    }

    //
    // Thread.
    //
    
    t = (void *) threadList[tid];

    if ( (void *) t != NULL )
    {
        // todo: validation
        t->state = STANDBY;
    }
}

//6
void do_thread_waiting (int tid)
{
    struct thread_d *t; 

    // tid
    if (tid < 0 || tid >= THREAD_COUNT_MAX){
        return;
    }

    //
    // Thread.
    //

    t = (void *) threadList[tid];

    if ( (void *) t != NULL)
    {
        //#todo: validation
        t->state = WAITING;
    }
}

// 2
void do_thread_zombie (int tid){

    struct thread_d *t; 

    // tid
    if (tid < 0 || tid >= THREAD_COUNT_MAX){
        return;
    }

    //
    // Thread.
    //

    t = (void *) threadList[tid]; 


    if ( (void *) t == NULL ){
        // todo: Message
        return;
        
    }else{

        if ( tid != IDLE )
        {
            // #todo: Validation
            t->state = ZOMBIE;
        }
    };
}

/*
 *****************************
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

int do_waitpid (pid_t pid, int *status, int options){

    struct process_d *p;  


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

// #todo: get current thread
int get_current (void)
{
    return (int) current_thread;
}

/* 
 * set_current:
 *     #todo: 
 *     Mudar para set_current_thread ( int tid ). 
 */
 
void set_current (int id){

    if ( id == current_thread )
    {
        return;
    }


	// Limits.
    if (id < 0 || id >= THREAD_COUNT_MAX)
    {
        return;
    }

	// Nothing ?!
	// Done.


    current_thread = (int) id;
}

/*
 * wait_for_a_reason:
 *     Faz a thread esperar  por um motivo.
 */

void wait_for_a_reason ( int tid, int reason ){

    struct thread_d *t;


    printf ("wait_for_a_reason: %d\n", reason);

    // tid
    if ( tid < 0 || tid >= THREAD_COUNT_MAX ){
        debug_print ("wait_for_a_reason: validation\n");
        return;
    } 

    //reason
    if ( reason < 0 || reason >= 10 ){
        debug_print ("wait_for_a_reason: limits\n");
        return;
    }


    //thread
    t = (struct thread_d *) threadList[tid];

    if ( (void *) t == NULL ){
        debug_print ("wait_for_a_reason: t\n");
        return;

    } else {

        if ( t->used != 1 || t->magic != 1234 ){
            debug_print ("wait_for_a_reason: t validation\n");
        }
        
        if ( t->used == 1 && t->magic == 1234 )
        {
			t->wait_reason[reason] = 1;
	        
			//
			// ## Wait ##
			//

			t->state =  WAITING;
        }
    };
    
   //KiScheduler ();
    
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

int wakeup_thread_reason ( int tid, int reason ){

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

    //thread
    t = (struct thread_d *) threadList[tid];

    if ( (void *) t == NULL ){
        debug_print ("wakeup_thread_reason: t\n");
        goto fail;

    } else {

        if ( t->used != 1 || t->magic != 1234 ){
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
done:
    return 0;
}

/*
 ******************************************
 * wakeup_scan_thread_reason:
 * 
 */

// Acorda todas as threads da lista que estão esperando por 
// evento de determinado tipo.

int wakeup_scan_thread_reason ( int reason ){

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

    printf ("wakeup_scan_thread_reason: done\n");
    refresh_screen();
    return 0;

// Fail

fail:
    printf ("wakeup_scan_thread_reason: fail\n");
    refresh_screen();
    return (int) 1;
}


/*
 **************************************************
 * wakeup_thread: 
 *    Para acordar uma thread, basta colocar ela no 
 * estado RUNNING se ela estiver com seu contexto 
 * salvo e seu estado WAITING. 
 *
 * @todo:
 *     Criar scheduleriWakeupYhread(int tid);
 */

void wakeup_thread (int tid){

    struct thread_d *t;
    int Status;
	//...


	// Limits.

    if ( tid < 0 || tid >= THREAD_COUNT_MAX )
    {
        return;
    }

    //Struct.

    t = (void *) threadList[tid]; 

    if ( (void *) t == NULL ){
        return;    
   
    }else{
    
		//Se o contexto não foi salvo. 
		//Não tem como acorda-la.
		//Pois acordar significa apenas retornar 
		//ao estado RUNNING.
		if ( t->saved == 0 ){ 
	        return; 
		}
		
		// Se estiver bloqueada, 
		// não tem como acordar ainda. 
		// precisa desbloquear.
		if (t->state == BLOCKED){ 
	        return; 
		}
			
	    //Isso acorda a thread,
		//mas não coloca ela imediatamente para rodar,
		//nem precisa.

        do_thread_running (tid);
	};

    // Nothing ?!
}

// Desiste do tempo de processamento.
// cooperativo.
// Muda o seu tempo executando para: Próximo de acabar.

void yield (int tid){

    struct thread_d *t; 


    //tid
    if (tid < 0 || tid >= THREAD_COUNT_MAX){
        //debug_print ("yield: tid\n");
        return;
    }


    t = (void *) threadList[tid];

    if ( (void *) t != NULL )
    {
        if ( t->used == 1 && t->magic == 1234 )
        {
	        // flag. 
	        // 1 = Sinaliza que a thread está dando a preferência
	        // e que deve sair quando for seguro fazer isso.
            // Agenda o yield.
            // >>> O ts.c vai fazer isso na hora certa.

            t->_yield = 1;    
        }
    }
}

//
// End.
//
























































