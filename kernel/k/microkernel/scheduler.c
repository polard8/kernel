/*
 * File: scheduler.c
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
 * KeScheduler:
 *    Interface para chamar a rotina de scheduler.
 *    Troca as tarefas que estão em user mode, usando o método cooperativo.
 * Round Robing. 
 *    As tarefas tem a mesma prioridade.
 *    + Quando encontrada uma tarefa de maior prioridade, escolhe ela
 * imediatamente.
 *    + Quando encontrar uma tarefa de menor prioridade, apenas eleva
 * a prioridade dela em até dois valores acima da prioridade base,
 * pegando a próxima tarefa.
 *    + Quando uma tarefa está rodando à dois valores acima da sua
 * prioridade básica, volta a prioridade para a sua prioridade básica
 * e executa.
 *
 * @todo: 
 *     'Ke_' é a iniciação errada para o nome da função. Isso é destinado
 *      para chamadas à módulos externos, ou servers.
 *     O certo seria nem usar uma interface para essa rotina, para ganhar
 * desempenho, mas se for usar deve-se usar a intermafe com iniciação
 * 'Ki_' para o nome. KiScheduler();
 *
 */
int KeScheduler()
{
    //
	// ?? Quem está chamando ? Filtros ?
    // 
    // @todo: Talvez haja mais casos onde não se deva trocar a tarefa.
    //

	//Scheduler Status. (LOCKED, UNLOCKED).
	if(g_scheduler_status == LOCKED){
        return (int) 0;
    };

	//Only Idle? Return.
	//@todo: Essa estrutura é válida?!
	if(ProcessorBlock.running_tasks == 1)
	{
        if(current_thread == 0){
	        return (int) 0;
		};
	};
    //Chama o Scheduler.
done:
	return (int) scheduler();
}; 


/*
 * scheduler:
 *    Troca a thread atual, escolhe uma nova thread atual para rodar no
 * momento.
 *    O método é cooperativo, Round Robing.
 *
 * Ordem de escolha:
 * ================
 *  +fase 1 - Pega a próxima indicada na estrutura.
 *  +fase 2 - Pega nos slots a de maior prioridade.
 *  +fase 3 - pega a Idle.
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
int scheduler()
{
	int Index;
	struct thread_d *Thread;


	//
	// Constrói um caminho de vagões para o condutor andar.
	//

	//Usado para task switch.
	Conductor  = (void*) rootConductor;

	//Inicia a lista.
 	Conductor2 = (void*) rootConductor;
	Conductor2->Next = (void*) threadList[0];  //Thread idle.


	//
	// obs: *IMPORTANTE
	// Os primeiros tipos a se pegar são os de prioridade maior.
	// @todo: Elevar a prioridade da threads interativas,
	// como teclado e mouse, e não elevar das threads de i/o de disco.
	// Elevar a prioridade da thread associada a janela com o foco de entada.
	//


	//
	// Obs: A thread idle somente é usada quando o sistema estiver ocioso.
	//

	//
	// Agora, antes de tudo, devemos pegar as threads nas listas onde estão
	// as threads de maior prioridade.
	//

	//Encontra o id da thread de maior prioridade entre as threads que estão no estado READY.
	//KiFindHigherPriority();

	//
	// Daqui pra baixo pegaremos na lista threadList[] onde estão todas as trhreads.
	//

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
	for(Index=0; Index <= THREAD_COUNT_MAX; Index++)
	{
		Thread = (void*) threadList[Index];
		if( (void*) Thread != NULL )
		{
			if(Thread->used == 1 && Thread->magic == 1234 && Thread->state == READY )
			{
			    Conductor2 = (void*) Conductor2->Next; 
				Conductor2->Next = (void*) Thread;
			};
			
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
	Conductor2 = (void*) Conductor2->Next; 
	Conductor2->Next = NULL;

done:
    return (int) Conductor2->tid;
};


/*
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

void scheduler_start()
{  
    scheduler_lock();     //Lock Scheduler.
	set_current(IDLE);    //Set current.
	
	//...

done:
	return;
};


/*
 * scheduler_lock:
 *     Trava o scheduler.
 *     @todo: Mudar para schedulerLock().
 *
 */
//void schedulerLock()
 
void scheduler_lock(){
    g_scheduler_status = (unsigned long) LOCKED;
	return;
};


/*
 * scheduler_unlock:
 *     Destrava o scheduler.
 *     @todo: Mudar para schedulerUnlock().
 *
 */  
//void schedulerUnlock()
 
void scheduler_unlock(){
    g_scheduler_status = (unsigned long) UNLOCKED;
	return;
};


/*
 * scheduler_get_status:
 *     Pega o status do scheduler, se ele está travado ou não.
 *     @todo: Mudar para schedulerGetStatus().
 *
 */
//unsigned long schedulerGetStatus() 
 
unsigned long scheduler_get_status(){
    return (unsigned long) g_scheduler_status;
};


/*
 * new_task_scheduler: 
 *     ?? 
 */
void new_task_scheduler(){   
    return;    /* CANCELADA !*/  		
};	


/*
 * init_scheduler:
 *    Inicaliza o scheduler.
 *    @todo: Mudar para schedulerInit()
 *
 */

//void schedulerInit()
 
void init_scheduler()
{
	//
	// @todo: Implementar inicialização de variaveis do scheduler.
	//        O nome poderia ser schedulerInit().
	//        Formato de classes.Init é um método. 
	//

	return;    //Não implementada.
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

