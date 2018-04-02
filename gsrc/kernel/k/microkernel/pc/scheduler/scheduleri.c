/*
 * File: scheduleri.c
 *
 * Descrição:
 *     Scheduler (Internal).
 *     Chama rotinas de scheduler dentro do kernel base. (internal).
 *     Faz parte do Process Manager, parte fundamental do Kernel Base.
 *     Rotinas de apoio ao módulo scheduler.
 *
 * Histórico:
 *     Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *     Versão 1.0, 2016 - Aprimoramento geral das rotinas básicas.
 *     //...
 */


#include <kernel.h>


/*
 * KiIncreasePriority:
 *     Aumenta a prioridade de uma processo
 *     @todo:
 */
int KiIncreasePriority(int pid)
{  
	return (int) 0;    //Nothing for now. 
};


/*
 * KiScheduler:
 *    Interface para chamar a rotina de scheduler.
 *    Troca as threads que estão em user mode, usando o método cooperativo. 
 * Round Robing. 
 *    As tarefas tem a mesma prioridade.
 *    + Quando encontrada uma tarefa de maior prioridade, escolhe ela 
 * imediatamente.
 *    + Quando encontrar uma tarefa de menor prioridade, apenas eleva a 
 * prioridade dela em até dois valores acima da prioridade base, pegando a 
 * próxima tarefa. 
 *    + Quando uma tarefa está rodando à dois valores acima da sua prioridade, 
 * volta a prioridade para a sua prioridade básica e executa.
 *
 * @todo: 
 *     Essa rotina deve ter retorno do tipo 'int'.
 */
int KiScheduler()
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

	// Retornaremos se a única thread rodando for a idle.
	if(ProcessorBlock.running_threads == 1)
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
 * KiFindHigherPriority:
 *     Interface para chamar a rotina de encontrar tarefa com maior prioridade.
 *     Encontra uma tarefa de maior prioridade entre as tarefas de estado
 * READY para que possa assumir o estado RUNNING.
 *     Essa rotina é usada após a preempçao, onde uma thread de baixa
 * prioridade para de executar para que rode uma de maior prioridade.
 * 
 */ 
int KiFindHigherPriority(){ 
    return (int) find_higher_priority(); 
}; 
 

 
/*
 * KiSelectNextThread:
 *
 */ 
int KiSelectNextThread(int current)
{
	//
    // @todo: Fazer filtros.
	//
	
	//@todo: Max.
	if(current < 0)
	{
	    current = 0;
	};
	
done:
    return (int) SelectNextThread(current);
};


void KiDoThreadReady(int id){
    do_thread_ready(id);
	return;
};


void KiDoThreadRunning(int id){
    do_thread_running(id);
	return;
};


void KiDoThreadSleeping(int id){
    do_thread_sleeping(id);
	return;
};


void KiDoThreadZombie(int id){
	do_thread_zombie(id);
    return;
};


void KiDoThreadDead(int id){
    do_thread_dead(id);
	return;
};


void KiStartTask(unsigned long id, unsigned long *task_address){
    return;
};


void KiAcordarTarefa(int id){
    wakeup_thread(id);
	return;
}; 


/*
 * KiTaskExit:
 *     Sai da tarefa atual.
 *     Ela entra no estado zombie para ser morta depois.
 *     @todo: Mudar para KiThreadExit();.
 */

void KiTaskExit()
{
	//
    //@todo: Criar rotina de interface.
	//
	
	
	
done:	
	taskexit();
	return;
};


/*
 * KiKillTask:
 *     Mata uma thread.
 *     @todo: Mudar para KiKillThread(int tid). 
 */
void KiKillTask(int id)
{
	//
    //@todo: alguma rotina de checagem, algum filtro.
	//
	
done:
    kill_task(id);
	return;
};


/*
 * KiNewTaskScheduler:
 *     ??
 *    @todo: Mudar para KiSchedulerNewThread().
 */
void KiNewTaskScheduler(){
    return;    //Cancelada.
};


/*
 * KiDispatchTask:
 *     Executa uma thread pronta pra rodar.
 *     @todo: Mudar para KiDispatchThread(int tid);
 *
 */
void KiDispatchTask()
{
	//...
done:
    return;
};


/*
 * KiSetPriority:
 *     Interface. Faz alterações na prioridade de acordo com o status.
 */
int KiSetPriority(){
	return (int) set_priority();
};


/*
 * KiSetCurrent:
 *     Seleciona a thread atual.
 *     @todo: Mudar o argumento para (int tid).
 */
void KiSetCurrent(int id)
{
	//@todo: Filtro.
	
done:
    set_current(id);
    return;
};


/*
 * KiGetCurrent:
 *     Pega o tid da thread atual.
 */
int KiGetCurrent(){
    return (int) get_current();
};


/*
 * KiGetCurrentTask:
 *     @todo: Modar para KiGetCurrentProcess.
 */
int KiGetCurrentTask(){ 
    return (int) get_current_task(); 
};


/*
 * find_higher_priority:
 *     Encontra uma thread de maior prioridade entre as threads de 
 * estado READY.
 *     Essa rotina é usado após a preempção, onde uma thread de 
 * baixa prioridade para de executar, para que rode uma de maior 
 * prioridade.
 *
 * @todo: Mudar para scheduleriFindHigherPriorityThread();.
 *
 */
int find_higher_priority()
{
	int i;              //Contador.
	unsigned long p;    //Prioridade.	
    int Current;     
    struct thread_d *t;  	
	
	//Only Idle? return.
	if(ProcessorBlock.running_threads == 1)
	{
		//#bugbug, Nã devemos determinar o valor da thread idle dessa forma.
		//tempos um ponteiro para a estrutura da thread idle.
	    if(current_thread == 0){
		    return (int) 0;
		};
		//@todo: E caso a única thread que está rodando não seja a thread idle??
	};	
	
	//
	// Find: Procura uma thread de maior prioridade, que o estado seja READY e 
	// que o contexto esteja salvo.
	//
	
	for( i = 0; i < THREAD_COUNT_MAX; i++ )
	{		 
       	t = (void *) threadList[i];    //Pega na lista. 		
        if( (void*) t != NULL )
		{ 
		    if(t->used  != 1    ){ continue; };
		    if(t->magic != 1234 ){ continue; };
		    if(t->state != READY){ continue; };		
		    
			//Pega a de maior prioridade.
			if(t->priority > p){ 
			    p = t->priority; 
			};
            //Nothing.			
		};
		//Nothing.
	};

	//
	// Encontra a próxima thread a ser executada. Ela deve ter prioridade 
	// maior ou igual a "p". Dá duas voltas nos slots procurando.
	//
	
	for( i=0; i < (2*THREAD_COUNT_MAX); i++ )
	{
    	Current++;
		
		//Circula.
		if(Current >= THREAD_COUNT_MAX){
			Current = (int) 0;
		};
	
		t = (void *) threadList[Current];
        if( (void*) t != NULL )
        {
		    //A tarefa rodando de maior prioridade.  
            if( (t->state == READY) && (t->priority >= p ) ){
			    break;
			};
			//Nothing.
        };	  
        //Nothing.		
	};

	//
	// Limites, overflow. Não encontrando nenhuma tarefa retorna o id da Idle. 
	//
	
	if( i >= (2*THREAD_COUNT_MAX) ){		
		return (int) 0;		
	};
	
	
	//
	// Nothing ?!
	//
	
//Done! Encontramos uma tarefa de prioridade maior.
done:
    return (int) Current;
};


/*
 * preempt:
 * Preempt current task if we can. Find Higher priority thread if we can.
 */
void preempt()
{	
    int Current;
	int Next = 0;
    struct thread_d *t;  
	//...
	
	//
	// Current.
	//
	
	Current = (int) current_thread;
	
	//
	// Preempt current.
	//
	
	//Struct.
	t = (void *) threadList[Current]; 	
	if( (void*) t == NULL )
	{
	    current_thread = (int) 0;    //We can't.
	    return;
	}else{
	    
		//Checa se a tarefa atual pode entrar em preempção, flag=1.	    
		if(t->preempted == 1)
		{
		    //Colocando ela numa fila de espera.
            //Se não for a idle e a prioridade for baixa.			
		    if( t->tid != 0 && t->priority == PRIORITY_LOW ){
		        t->state = WAITING;    //Wait.
            };
            //Nothing.			
	    };
		//Nothing.
	};	
	
	//
	// Next - Procura uma de maior prioridade. Não havendo usa a Idle.
	//
	
	Next = (int) find_higher_priority();
	
	//Use idle.
	if(Next <= 0){
	    current_thread = (int) 0;
        goto done;		
	};
	
	//Dentro do limite.
	if(Next > 0 && Next < THREAD_COUNT_MAX ){
	    current_thread = (int) Next;
	};
    
	//
	// Nothing ?!	
	//
	
// Done.
done:	
    return;
};



/*
 * get_current:
 *    Obtendo o TID da thread atual.
 *    @todo: Criar scheduleriGetCurrentTID();
 */
int get_current(){ 
	return (int) current_thread;
};



/*
 * get_current_task:
 *     Pega o id da thrad atual.
 *    @todo: Criar scheduleriGetCurrentTID();
 */
int get_current_task(){
    return (int) get_current();
};



/*
 * set_current:  
 *    Indicando qual será a thread atual.
 * @todo: 
 *     Criar scheduleriSetCurrentTID(int tid);
 *  
 */
void set_current(int id)
{
	if( id == current_thread ){
		return;
	};
	
	// Limits.
	if(id < 0 || id >= THREAD_COUNT_MAX){
	    return;
	};
	
	//
	// Nothing ?!
	//
	
	
//Done.	
done:
	current_thread = (int) id;    	
	return;
};



/*
 * set_priority:
 *     Equilibra a prioridade da thread atual.
 *     @todo: Não é esse o nome apropriado para essa rotina.
 *            Criar scheduleriBalanceCurrentThreadPriority()
 */
int set_priority()
{
    struct thread_d *Current; 
	
	Current = (void *) threadList[current_thread];
    
	if( (void *) Current == NULL ){
	    return (int) 1;    //?? fail.
    };
	
	//
	// Nothing ?!
	//
	
done:
    set_thread_priority( Current, PRIORITY_NORMAL);
    return (int) 0; 
};


/*
 * do_thread_ready:
 *     Muda o state de uma thread.
 *     @todo: mudar o nome da função pra do_thread_ready
 */ 
void do_thread_ready(int id)
{
    struct thread_d *t; 
	
	if (id < 0 || id >= THREAD_COUNT_MAX){
	    return;
	};
	
    //Struct.
	t = (void *) threadList[id]; 	
	
	if( (void*) t != NULL){
	    t->state = READY;
	};
	
//Done.
done:	
	return;
};



/*
 * do_thread_running:
 *     Muda o state de uma thread pra running.
 *     @todo: mudar o nome da função para do_thread_running
 */
void do_thread_running(int id)
{
    struct thread_d *t; 
	
	if (id < 0 || id >= THREAD_COUNT_MAX){
	    return;
	};
	   
    // Struct.
	t = (void *) threadList[id]; 	
	
	if( (void*) t != NULL){
	    t->state = RUNNING;
	};
	
// Done.
done:
	return;
};



/*
 * do_thread_sleeping:
 *     Muda o state de uma thread pra blocked.
 *     @todo: Mudar o nome da função para do_thread_blocked.
 */
void do_thread_sleeping(int id)
{
    struct thread_d *t; 

	if (id < 0 || id >= THREAD_COUNT_MAX){
	    return;
	};

    // Struct.
	t = (void *) threadList[id];	
	
	if( (void*) t != NULL){
	    t->state = BLOCKED;
    };

// Done.
done:	
    return;	
};



/*
 * do_thread_zombie:
 * Muda o state da thread para zombie.
 * @todo: Mudar o nome da função para do_thread_zombie.
 */
void do_thread_zombie(int id)
{
    struct thread_d *t; 
	 
	if (id < 0 || id >= THREAD_COUNT_MAX){
	    return;
	};
	
    //Struct.
	t = (void *) threadList[id]; 
	
	if( (void*) t == NULL){
	    return;
	}else{
        
		if( id != IDLE ){
            t->state = ZOMBIE;
        };
    };

// Done.	
done:	
	return;	
};



/*
 * do_thread_dead:
 * Muda o state da thread para dead.
 * @todo: Mudar o nome da função para do_thread_dead.
 */
void do_thread_dead(int id)
{
    struct thread_d *t; 
	
	if (id < 0 || id >= THREAD_COUNT_MAX){
	    return;
	};

    // Struct.	
	t = (void *) threadList[id]; 	
	
	if( (void*) t != NULL){
	    t->state = DEAD;
	};	
	
done:	
	return;
};



/*
 * wakeup_thread: 
 *    Para acordar uma thread, basta colocar ela no estado RUNNING se ela
 * estiver com seu contexto salvo e seu estado WAITING. 
 *
 * @todo:
 *     Criar scheduleriWakeupYhread(int tid);
 * 
 */
void wakeup_thread(int tid)
{
    int Status;
    struct thread_d *t; 	
	//...
	
	//Limits.
	if(tid < 0 || tid >= THREAD_COUNT_MAX){
	    return;
	};	

    //Struct.
	t = (void *) threadList[tid]; 
	if( (void*) t == NULL )
	{ 	
	    return;    //Retorna sem despachar.
	}else{
	    
		//Se o contexto nao foi salvo. Não tem como acorda-la.
		if(t->saved == 0){ return; };
		
		//Se estiver bloqueada, não tem como acordar ainda. precisa desbloquear.
		if(t->state == BLOCKED){ return; }; 
		
		//Check context.
	    Status = contextCheckThreadRing3Context(tid);
		if(Status == 1 ){ return; };
		
	    //Set current.
	    current_thread = (int) tid;	
		
		//Dispach current.
		//Obs: O que acontece aqui? Tem iret pra thread ou não ?
		//
		dispatch_task();
	};

    //
    // Nothing ?!
    //
			
//Done.
done: 
    return;	
};



/*
 * kill_task:
 *    Deleta uma thread, liberando o slot.
 *
 * @todo: 
 *     +Quando uma thread finaliza, deve-se mudar o número de tarefas 
 * rodando. (Feito)
 *     +Mudar o nome da função para scheduleriKillThread(int tid);.
 *
 */
void kill_task(int id)
{
    struct thread_d *t; 	   

	// @todo: 
	//     Checar se algo impede que a tarefa seja fechada. 
	//
	
	// Limits.
	if (id <= 0 || id >= THREAD_COUNT_MAX){
	    return;
	};	

    // Struct.		
	t = (void *) threadList[id]; 		
	if( (void*) t == NULL){
	    return;
	}else{
	    
		//Zerar as variáveis da estrutura.
	    t->tid = 0;
	    t->ownerPID = 0;    
	    t->used = 0;
	    t->magic = 0;
	    t->state = DEAD;
		//...
		
		//@todo: Zerar as variáveis de contexto.
		
		//lista
		threadList[id] = 0;
		//t = NULL;
	};
	
	//
	// Contador de tarefas que estão rodando.
	//
	
	//@todo: Check struct.
	
	if(ProcessorBlock.running_threads > 1)
	{
        ProcessorBlock.running_threads--;	 
	    //...
	};	 
 	
	
	//
	// More ?!
	//
	
// Done.	
done:
    current_thread = (int) 0;    //Idle.
	return;
};


/* 
 * taskexit:
 *    Finaliza a execução de uma ?. 
 *
 *    Passa o comando para a tarefa Pai.
 *    ex: Quando fechamos uma janela filha.
 *
 *    @todo: 
 *        Essa função deve ser um recurso oferecido 
 *        nos serviços do sistema, assim os aplicativos 
 *        em user mode podem chama-la.
 *
 *  @todo: Analizar o que essa rotina faz, se finaliza
 *         uma thread ou sai de processo. 
 */
void taskexit()
{
    int i;
	int Parent;     //Parent process.
	int Current;    //Current thread.
	struct thread_d *t; 
    struct process_d *p; 
	
	//
	// Current.
	//
	
	Current = (int) current_thread;

	
	if(Current <= 0 || Current >= THREAD_COUNT_MAX ){
	    return;
	};
	
    //Struct.
    t = (void *) threadList[Current]; 	
	if( (void*) t == NULL)
	{
		//
	    //@todo: Enviar mensagem de erro.
	    //
		return;
	}
	else
	{
        t->state = ZOMBIE;    //Zombie current.	
	
	    //
	    // Parent. //Parent process
	    //

    	Parent = t->ownerPID;    //Parent process.
 	
	    if(Parent < 0){
		    return;
		}else{
			
			
		    //Process.
	        p = (void *) processList[Parent];	
	        if( (void *) p == NULL ){
			    return;
			}else{
				
			  /*
			    //se a parent estava esperando a filha fechar.
	            if( p->wait4pid == 0) 
				{ 
				    current_thread = (int) 0; 
					return; 
				};	
                
				//se não estava esperando.
				if( p->wait4pid == 1)
	            { 
	                p->wait4pid = 0;
		            current_thread = (int) Parent;
	            };
				*/
			};
		
		};
	
	};
	
	
//
// Done.    
//	
done:

    //
    //@todo: Usar outra função...(wakeup()).
    //
	
	wakeup_thread(current_thread);
	return; 
};



/*
 * SelectNextThread:
 *     Seleciona a próxima thread indicanda na estrutura da thread 
 * passada via argumento.
 *
 * @todo: Mudar para scheduleriSelectNextThread(int current);.
 *
 */
int SelectNextThread(int current)
{
	int Next;
    struct thread_d *t; 
    struct thread_d *n; 

    
	//Limits.
	if( current < 0 || current >= THREAD_COUNT_MAX ){
	    return (int) 0;
	};
	
    // Struct.
    t = (void *) threadList[current];		
	if( (void*) t == NULL)
	{
	    return (int) 0;
	}
	else
	{
        //Se não existe indicação de próxima.
	    if( (void *) t->Next == NULL )
	    {
		    //Procura a próxima tarefa, de acordo com a prioridade.
		    Next = (int) find_higher_priority();
			
		    n = (void*) threadList[Next];
		    if( (void*) n == NULL ){
		        Next = 0;    //Pega Idle.
			    return (int) Next; 
		    }else{
			    Next = (int) n->tid;    //Pega id.
			    return (int) Next;
			};
	    }
	    else //Aceita a indicação de próxima.
	    {
			n = (void *) t->Next;
			
			if( (void*) n == NULL ){
			    Next = (int) 0;    //Pega idle.
			    return (int) Next;
			}else{
			    Next = (int) n->tid;    //Pega o tid.
				t->Next = NULL;
                return (int) Next;
			};
			//Nothing.
		};
        //Nothing.		
	};
	
	
	//
	// More ?!
	//
	
// Done.
done:	
    return (int) Next;
};



/*
 * check_for_standby:
 *     Procura na lista de threads no estado StandyBy.
 *     Se tiver uma thread nessa lista, ela se torna a current.
 *     Para rodar pela primeira vez, atravéz de Spawn.
 *     @todo: na verdade essa função deveria se chamar check for standby
 */
void check_for_standby()
{
	int i = 0;
    int newId;
	struct thread_d *New;
	
	//@todo: Max variable.
	
	do
	{
        //New = (void*) threadList[i];    	
		
		New = (void*) queue->standbyList[i];
		
		if( (void *) New != NULL )
		{
		    if( New->used == 1 && 
			    New->magic == 1234 && 
				New->state == STANDBY )   
			{
			    current_thread = (int) New->tid;
			    goto do_spawn;
			};
		};
		++i;
	}while(i < 32);    //@todo: Constante do tamanho da queue.  
	
//Done. Nenhuma tarefa precisa ser inicializada.
done:
    return;
//Do Spawn.
do_spawn:
    KiSpawnTask(current_thread);  //spawn.c
	//spawn_task(current_thread);
    panic("check_for_initialized:");
	while(1){};	
};


/*
 * check_quantum:
 *     Checa o quantum atribuido às threads da lista.
 *
 * @todo: Mudar para scheduleriCheckThreadQuantum();
 *
 */
int check_quantum()
{
	int i=0;
    int newId;	
	struct thread_d *New;
	
	while(i<THREAD_COUNT_MAX)
	{
        New = (void*) threadList[i];    	
	    
		if( (void*) New != NULL )
		{ 
		    if( New->used == 1 && 
				New->magic == 1234 &&
				New->state == READY &&
				New->quantum == QUANTUM_LIMIT )
			{
		        goto token;
			};
			//Nothing.
		};	
		++i;
	};
	
	//
	// Nothing ?!
	//
	
//Done.	
done:
    return (int) 0;
token:
	return (int) New->tid;	
};


//
// Fim.
//

