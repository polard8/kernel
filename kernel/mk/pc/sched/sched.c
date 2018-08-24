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

//unsigned long schedulerQueue[4];



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
 *
 */
int scheduler (){
	
	int Index;
	struct thread_d *Thread;

	// spiritual quote:
	// Constrói um caminho de vagões para o condutor andar.

	//Usado para task switch.
	Conductor = (void *) rootConductor;

	//Inicia a lista.
 	Conductor2 = (void *) rootConductor;

	//#bugbug
	//Conductor2->Next = (void *) threadList[idle];  	
    
	// ?? por que ??
	//Thread idle em ring 0.
	Conductor2->Next = (void *) threadList[next_thread];  
	
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

	/*	
    //BLOCKED
	for(Index=0; Index <= THREAD_COUNT_MAX; Index++)
	{
		Thread = (void*) threadList[Index];
		if( (void*) Thread != NULL)
		{
			if(Thread->used == 1 && Thread->magic == 1234 && Thread->state == BLOCKED )
			{
				//ACORDA
				Thread->state = READY;
			    Conductor2->Next = (void*) Thread;
                Conductor2 = (void*) Conductor2->Next;
			};
			
		};
	};

	//WAITING
	for(Index=0; Index <= THREAD_COUNT_MAX; Index++)
	{
		Thread = (void*) threadList[Index];
		if( (void*) Thread != NULL)
		{
			if(Thread->used == 1 && Thread->magic == 1234 && Thread->state == WAITING )
			{
				//ACORDA
				Thread->state = READY;
			    Conductor2->Next = (void*) Thread;
                Conductor2 = (void*) Conductor2->Next;
			};
			
		};
	};

	*/

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

	/*
	//READY. again (de traz pra frente.
	for(Index=THREAD_COUNT_MAX; Index >= 0; Index--)
	{
		Thread = (void*) threadList[Index];
		if( (void*) Thread != NULL)
		{
			if(Thread->used == 1 && Thread->magic == 1234 && Thread->state == READY )
			{
			    Conductor2->Next = (void*) Thread;
                Conductor2 = (void*) Conductor2->Next;
			};
			
		};
	};	

	*/

	/*
    //RUNNING
	for(Index=0; Index <= THREAD_COUNT_MAX; Index++)
	{
		Thread = (void*) threadList[Index];
		if( (void*) Thread != NULL)
		{
			if(Thread->used == 1 && Thread->magic == 1234 && Thread->state == RUNNING )
			{
				//ACORDA
				Thread->state = READY;
			    Conductor->Next = (void*) Thread;
                Conductor = (void*) Conductor->Next;
			};
			
		};
	};
    */

	//Conductor2->Next = NULL;

	//
	// Continua pegando os tipos diferente.
	//


	//finaliza a lista
	Conductor2 = (void *) Conductor2->Next; 
	Conductor2->Next = NULL;

//done:
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
 *
 */
//void schedulerStart()
void scheduler_start (){
	
    scheduler_lock();     //Lock Scheduler.
	set_current(IDLE);    //Set current.
	
	//...

//done:
//	return;
};


/*
 ****************************************
 * scheduler_lock:
 *     Trava o scheduler.
 */
void scheduler_lock (){
	
    g_scheduler_status = (unsigned long) LOCKED;
};


/*
 ********************************************
 * scheduler_unlock:
 *     Destrava o scheduler.
 */  
//void schedulerUnlock() 
void scheduler_unlock (){
	
    g_scheduler_status = (unsigned long) UNLOCKED;
};


/*
 * scheduler_get_status:
 *     Pega o status do scheduler, se ele está travado ou não.
 *     @todo: Mudar para schedulerGetStatus().
 *
 */
//unsigned long schedulerGetStatus() 
 
unsigned long scheduler_get_status()
{
    return (unsigned long) g_scheduler_status;
};


/*
 * new_task_scheduler: 
 *     ?? 
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
// Fim.
//

