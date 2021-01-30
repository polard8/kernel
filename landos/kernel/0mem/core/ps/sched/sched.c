/*
 * File: ps/sched/sched.c
 *
 * Descrição:
 *     O escalonador de processos do Kernel.
 *     Faz parte do Process Manager, parte fundamental do Kernel Base.
 *     The kernel schedules threads, not processes.
 *     Priority: +boosts for GUI foreground.
 *
 * Atribuições:
 *     + Salva o contexto da tarefa OLD.
 *     + Incrementa a tarefa atual. (RR).
 *     + Retorna o contexto da tarefa NEW.
 *
 * Obs:
 *     O Scheduler não salva nem restaura contexto de tarefa.
 * Apenas troca a tarefa atual e faz um agendamento das próximas
 * threads a rodarem.
 *     Será possível usar mais de um método de escalonamento. No momento,
 * o método usado é escalonamento Round Robin, preemptivo,
 * com múltiplas filas e prioridade.
 *
 * @todo:
 *     Não por interface nessa rotina. Perde velocidade.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     //...
 */


 /*
  * #importante:
  * Para implementarmos um scheduler como um processo, devemos separar 
  * as funções em funções de biblioteca e funções primitivas, que serão 
  * aquelas presentes no stub do scheduler. As funções primitivas 
  * serão as mesmas para todos os schedulers que criarmos.
  */
 

#include <kernel.h>


/*
 * pick_next_thread:
 *     Selecionamos a 'next_thread' olhando nas filas em QUEUE[].
 *     QUEUE[] contém ponteiros para listas encadeadas.
 *     Se não tiver nada nas filas então usaremos a InitThread.
 *
 *     #bugbug: Essa InitThread está configurada corretamente. ?
 *     #bugbug: E se não existir IfleThread? 
 */

struct thread_d *pick_next_thread (void){

    struct thread_d *t;
    struct thread_d *next;

    int i=0;      //id da fila selecionada
    int old=0;    //salva id da current thread


	//salva antiga thread
    old = next_thread;
	
	
	//se temos um ponteiro para fila de drivers.
    if ( QUEUES[0] != 0 ){
        i = 0;

	//se temos um ponteiro para a fila de servidores.

    } else if ( QUEUES[1] != 0 ){
        i = 1;

	//nos resta a fila de apps de usuário.
    }else{
        i = 2;
    };


	//
	// # Checando o conductor. #
	//


	//se o elemento tem um valor não nulo..
    if (QUEUES[i] != 0)
    {
	    //Ok temos uma fila.
		//vamos pegar a primeira thread da fila.
		
        t = (void *) QUEUES[i];

    }else{

		// nenhuma thread est'a no estado de READY ... entao nenhuma das
		// filas foi construida.
		// nos reata usarmos a thread idle. 
		
		//podemos fica nessa condiç~ao at'e que uma thread seja acordada ...
		//talvez ela esteja esperando alguma recurso,.
		//quando ela acordar ir'a pra alguma fila.
		
		
		
		// #todo
		// Mudar para ____IDLE;
		// Selecionamos a idle.
		// Isso está errado, estamos selecionando a thread de controle
		// do processo init.bin, mas queremos a idle do kernel.
        t = InitThread;
        //t = ____IDLE;
    };



	//
	// Checando a thread selecionada.
	//

    if ( ( void *) t == NULL ){
		next_thread = old;

    }else{

        // #bugbug
        // Se a estrutura falhou então não podemos usar essa thread.
        // Tem que abortar a tentativa.
        
        if ( t->used != 1 || t->magic != 1234 )
        {
            next_thread = old;
            goto prepare_next;
        }

		//Ok.
        next_thread = t->tid;
    };


prepare_next:

	//
	// # Checando a validade da next thread. #
	//

    next = (void *) threadList[next_thread];

    if ( ( void *) next == NULL )
    {
	    //fail
	    // #debug
	    //Não conseguimos selecionar nenhuma thread como próxima.
		//não temos nem mesmo uma thread idle para inicializarmos o round.
			
		//#debug
		//printf ("#DEBUG\n");
        printf ("pick_next_thread: No next_thread, we could't initialize the round\n");
        die ();

    }else{

        if ( next->used != 1 || next->magic != 1234 )
        {
	        //fail
	        // #debug
	        //Não conseguimos selecionar nenhuma thread como próxima.
		    //não temos nem mesmo uma thread idle para inicializarmos o round.
		    //#debug
			//printf ("#DEBUG\n");
            printf ("pick_next_thread: No next_thread, we could't initialize the round\n");
            die ();
        }

        if ( next->state == READY ){
            return (struct thread_d *) next;
        }
    };


    return NULL;
}




/*
 *********************************************************
 * scheduler:
 *    Troca a thread atual, escolhe uma nova thread atual 
 * para rodar no momento.
 *    O método é cooperativo, Round Robing.
 *
 * Ordem de escolha:
 * ================
 *  +fase 1 - Pega a próxima indicada na estrutura.
 *  +fase 2 - Pega nos slots a de maior prioridade.
 *  +fase 3 - Pega a Idle. 
 *            @todo: Nessa fase devemos usar a idle atual, 
 *            indicada em current_idle_thread.  
 *  //...
 *
 * Obs:
 *     O que estamos fazendo aqui é incrementar a tarefa atual e olhando se a
 * próxima tarefa da lista threadList[] está pronta pra rodar.
 *
 * Obs:
 *     Pega na fila ReadyQueue.
 *     O scheduler deve sempre pegar da fila do dispatcher.
 */
 
// #todo
// Podemos contar os rounds.
// Obs: 
// ## IMPORTANTE  ##
// A thread idle somente é usada quando o sistema 
// estiver ocioso ou quando ela for a única thread.
// E é importante que a thread idle seja usada, pois 
// ela tem as instruções sti/hlt que atenua a utilização 
// da CPU, reduzindo o consumo de energia.


int scheduler (void){

    // loop
    register int i=0;

    struct thread_d *TmpThread;


#ifdef SERIAL_DEBUG_VERBOSE
    debug_print(" [*SCHEDULER*] ");
#endif


    // tmpConductor and it's next. 
    tmpConductor       = (void *) rootConductor;
    tmpConductor->next = (void *) ____IDLE;

    // The global conductor.
    Conductor = (void *) tmpConductor->next;

    // READY threads in the threadList[].
    for ( i=0; i < THREAD_COUNT_MAX; ++i )
    {
        TmpThread = (void *) threadList[i];

        if ( (void *) TmpThread != NULL )
        {
            if ( TmpThread->used  == TRUE && 
                 TmpThread->magic == 1234 && 
                 TmpThread->state == READY )
            {
                // The tmpConductor and it's next.
                tmpConductor       = (void *) tmpConductor->next; 
                tmpConductor->next = (void *) TmpThread;
            }
        }
    };

    // #todo
    // Let's try some other lists.

    // Finalizing the list.
    // The tmpConductor and it's next.
    tmpConductor       = (void *) tmpConductor->next; 
    tmpConductor->next = NULL;


    return (int) rootConductor->tid;
    //return (int) tmpConductor->tid;
    //return (int) Conductor->tid;
}


// #deprecated
void scheduler_start (void)
{
    // #maybe
    // scheduler_unlock();

    panic("scheduler_start: deprecated\n");
}


// Lock scheduler
void scheduler_lock (void){
    g_scheduler_status = (unsigned long) LOCKED;
}

// Unlock scheduler
void scheduler_unlock (void)
{
    g_scheduler_status = (unsigned long) UNLOCKED;
}


/*
 * scheduler_get_status:
 *     Pega o status do scheduler, se ele está travado ou não.
 */
 
unsigned long scheduler_get_status (void)
{
    return (unsigned long) g_scheduler_status;
}


/*
 ********************************
 * init_scheduler:
 *    Inicaliza o scheduler.
 *    @todo: Mudar para schedulerInit()
 *    #burbug: faz o mesmo que scheduler_start.
 */

	// #todo: 
	// Implementar inicialização de variaveis do scheduler.
	// O nome poderia ser schedulerInit().
	// Formato de classes.Init é um método. 

// Called by init_microkernel in mk.c

void init_scheduler (void)
{
    debug_print ("init_scheduler: [TODO]\n");
    // ...
    
    scheduler_lock();
    
    // #bugbug
    // Maybe there is no IDLE defined 
    // at this point of the initialization.
    
    //set_current (IDLE);
}


//
// End.
//

