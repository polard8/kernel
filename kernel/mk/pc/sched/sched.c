/*
 * File: sched/sched.c
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
 * Histórico:
 *     Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *     Versão 1.0, 2016 - Aprimoramento geral das rotinas básicas.
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


//
// Variáveis internas.
//

//int schedulerStatus;
//int schedulerError;
//int schedulerType;
//...



/*
 * pick_next_thread:
 *     Selecionamos a 'next_thread' olhando nas filas em QUEUE[].
 *     QUEUE[] contém ponteiros para listas encadeadas.
 *     Se não tiver nada nas filas então usaremos a IdleThread.
 *
 *     #bugbug: Essa IdleThread está configurada corretamente. ?
 *     #bugbug: E se não existir IfleThread? 
 */

struct thread_d *pick_next_thread (){
	
	int i;    //id da fila selecionada
	int old;  //salva id da current thread
	
	struct thread_d *t;
	struct thread_d *next;

	
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
		
		//selecionamos a idle.
		
		t = IdleThread;
	};
	
	//
	// Checando a thread selecionada.
	//
	
	if ( ( void *) t == NULL )
	{
	    //fail
		next_thread = old;
		
	}else{
	
	    if ( t->used != 1 || t->magic != 1234 )
		{
		    //fail
		    next_thread = old;			
		}
	
		//Ok.
		next_thread = t->tid;
	};
	
	
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
		printf ("#DEBUG\n");
		printf ("pick_next_thread: No next_thread, we could't initialize the round\n");
		die();
		
	}else{
	
	    
		if ( next->used != 1 || next->magic != 1234 )
		{
	        //fail
	        // #debug
	        //Não conseguimos selecionar nenhuma thread como próxima.
		    //não temos nem mesmo uma thread idle para inicializarmos o round.
		    //#debug
		    printf ("#DEBUG\n");
		    printf ("pick_next_thread: No next_thread, we could't initialize the round\n");
		    die();	
		}
		
		if ( next->state == READY )
		{
		    return (struct thread_d *) next;
		}
	}
	
	return NULL;
}




/*
 ***************************************************************
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
 
//#todo
//podemos contar os rounds;

int scheduler (){
	
	int Index;
	struct thread_d *Thread;
	
	
	debug_print(" [*SCHEDULER*]");
	
	//#debug
	//printf ("scheduler: Running Threads %d \n", ProcessorBlock.threads_counter );
	//refresh_screen();
	
	// spiritual quote:
	// "Constrói um caminho de vagões para o condutor andar".

	//Usado para task switch.
	//Conductor = (void *) rootConductor;
	//Inicia a lista.
 	//Conductor2 = (void *) rootConductor;
	//Next thread.
	//Conductor2->Next = (void *) threadList[next_thread];  
	
	
	//#importante 
	//rootConductor é um ponteiro válido,
	//mas a estrutura não foi inicializada.
	
	//Inicia a lista.
	//marca o início, mas não usa esse ponteiro.
  
  //#debug
  //printf ("scheduler: 1\n");
	
 	Conductor2 = (void *) rootConductor;
	
	
	
	//
	// ## preparando 'next_thread' ##
	//
	
	//Não sabemos quem está em next_thread.
	//Checaremos a possibilidade de não termos filas configuradas.
	//nesse caso a idle thread será a primeira trhead do round
	//não havendo outra, pelo menos ela vai rodar.
	
  //#debug
  //printf ("scheduler: 2\n");
	
  // #debug
  // supendendo essa rotina que falhou em gigabyte/intel
	// Vamos substituir a thread que a função retorna pela current_thread
  // que esperamos que seja válida. Talvez isso resolva o problema por enquanto.
  // Mas trabalharemos nessa função depois.
  
  //pick_next_thread ();
	
  // HACK HACK
  //next_thread = current_thread;
	
	//
	//  ## PRIMEIRO PONTEIRO VÁLIDO ##
	//
  
   //#debug
 // printf ("scheduler: 3\n"); 
	
	//Next thread.
	Conductor2->Next = (void *) threadList[next_thread];  
	
	//
	//  ## MARCADOR GLOBAL ##
	//
	
  //#debug
 // printf ("scheduler: 4\n");
  
	//TID=0
	//vamos começar a lista dessa aqui.
	Conductor = (void *) Conductor2->Next;	
	
	
	// Obs: 
	// ## IMPORTANTE  ##
	// Os primeiros tipos a se pegar são os de 
	// prioridade maior.
	// @todo: Elevar a prioridade da threads interativas,
	// como teclado e mouse, e não elevar das threads de 
	// i/o de disco.
	// Elevar a prioridade da thread associada a janela 
	// com o foco de entada.

	// Obs: 
	// ## IMPORTANTE  ##	
	// A thread idle somente é usada quando o sistema 
	// estiver ocioso ou quando ela for a única thread.
	// E é importante que a thread idle seja usada, pois 
	// ela tem as instruções sti/hlt que atenua a utilização 
	// da CPU, reduzindo o consumo de energia.

	// Agora, antes de tudo, devemos pegar as threads 
	// nas listas onde estão as threads de maior prioridade.

	//Encontra o id da thread de maior prioridade entre as 
	// threads que estão no estado READY.
	//KiFindHigherPriority();

	// ## Importante  ##
	// Daqui pra baixo pegaremos na lista threadList[] 
	// onde estão todas as threads.

    //@todo pegar primeiro por prioridade.	
	
  //#debug
 // printf ("scheduler: 5\n");
	
	//READY.
	for ( Index=0; Index < THREAD_COUNT_MAX; Index++ )
	{
		Thread = (void *) threadList[Index];
		
		if ( (void *) Thread != NULL )
		{
			if ( Thread->used == 1 && 
			     Thread->magic == 1234 && 
				 Thread->state == READY )
			{
			    Conductor2 = (void *) Conductor2->Next; 
				Conductor2->Next = (void *) Thread;
			};
		    //Nothing.
		};
		//Nothing.
	};	


	//
	// Continua pegando os tipos diferente.
	//

  //#debug
 // printf ("scheduler: 6\n");

	//finaliza a lista
	Conductor2 = (void *) Conductor2->Next; 
	Conductor2->Next = NULL;

    return (int) Conductor2->tid;
};


/*
 ***************************************************
 * scheduler_start:
 *     +Inicializa o sheduler.
 *     +Trava o scheduler.
 *     +Torna IDLE a tarefa atual.
 *     //...
 *
 *     @todo: nao seria init_scheduler
 *     @todo: Mudar para schedulerInit,ou schedulerStart. ??
 */

void scheduler_start (){
	
	//Lock Scheduler.
	//Set current.
	
    scheduler_lock ();  

    // #bugbug 
	// Esse negócio de selecionar pelo impondo um ID dá problemas.
	// Temos que saber qual é o ID da thread que queremos.
	
	set_current (IDLE);     
	
	//...
};


/* scheduler_lock: */
void scheduler_lock (){
	
    g_scheduler_status = (unsigned long) LOCKED;
};


/* scheduler_unlock: */  
void scheduler_unlock (){
	
    g_scheduler_status = (unsigned long) UNLOCKED;
};


/*
 * scheduler_get_status:
 *     Pega o status do scheduler, se ele está travado ou não.
 */
 
unsigned long scheduler_get_status()
{
    return (unsigned long) g_scheduler_status;
};


/*
 * new_task_scheduler: 
 *     ?? #deletar
 */
void new_task_scheduler()
{   
    return;    /* CANCELADA !*/  		
};	


/*
 * init_scheduler:
 *    Inicaliza o scheduler.
 *    @todo: Mudar para schedulerInit()
 *    #burbug: faz o mesmo que scheduler_start.
 */
//void schedulerInit()
void init_scheduler (){
	
	// @todo: Implementar inicialização de variaveis do scheduler.
	//        O nome poderia ser schedulerInit().
	//        Formato de classes.Init é um método. 

//	return;    //Não implementada.
};


/*
 * constructor.
int schedulerScheduler(){
	;
};
*/

/*
int schedulerInit(){
	;
};
*/


//
// End.
//

