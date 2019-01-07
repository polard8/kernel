/*
 * File: action\threadi.c 
 *
 * Descrição:
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
 *     2018 - Revision.
 */

 
#include <kernel.h>



/*
 * KiShowPreemptedTask
 * @todo: Substituir a palavra task por thread. KiShowPreemptedThread
 *
 */
void KiShowPreemptedTask()
{
    //return;
};

 
/*
 * KiSetTaskStatus: #deletar
 *     @todo: Substituir a palavra task por thread. KiSetThreadStatus
 */ 
void KiSetTaskStatus(unsigned long status)
{
    //@todo: criar interface para mudanca de status.
	
	set_task_status(status);
};


/*
 * KiGetTaskStatus #deletar
 * @todo: Substituir a palavra task por thread. KiGetThreadStatus
 * #bugbgu task não é um termo usado.
 */
unsigned long KiGetTaskStatus ()
{ 
    return (unsigned long) get_task_status(); 
};



/*
 #deletar
 * KiSaveContextOfNewTask
 * @todo: Substituir a palavra task por thread. KiSaveContextOfNewThread
 *
 * ?? isso está muito estranho !!
 */
 
void KiSaveContextOfNewTask ( int id, unsigned long *task_address ){
	
    //return;
};


/*
 * KiReloadCurrentTask #deletar
 *  @todo: Substituir a palavra task por thread. KiReloadCurrentThread.
 *
 */
void KiReloadCurrentTask (){
	
    //return;
};


/* #todo: ?? de quem ?? processo ou thread */
void KiSetQuantum (unsigned long q){
    
    //return;
};


unsigned long KiGetQuantum (){
	
    return (unsigned long) 0; 
};


/* #todo: ?? de quem ?? processo ou thread */
void KiSetCurrentQuantum (unsigned long q){
	
    //return;
};


/* #todo: ?? de quem ?? processo ou thread */
unsigned long KiGetCurrentQuantum (){
	
    return (unsigned long) 0; 
};


/* #todo: ?? de quem ?? processo ou thread */
void KiSetNextQuantum ( unsigned long q ){
	
    //return;
};


/* #todo: ?? de quem ?? processo ou thread */
unsigned long KiGetNextQuantum (){
	
    return (unsigned long) 0; 
};


/* #todo: ?? de quem ?? processo ou thread */
void KiSetFocus (int pid){
	
	//return;
};


/* #todo: ?? de quem ?? processo ou thread */
int KiGetFocus (){
	
    return (int) 0; 
};


/* #todo: chamar função em debug.c */
void KiDebugBreakpoint (){
	
};


/* #deletar */
void KiShowTasksParameters (){
	
    //return;
};


/* #todo: mudar nomes */
void KiMostraSlots (){
	
	mostra_slots();
};


/* #todo: mudar nomes */
void KiMostraSlot (int id){
	
	mostra_slot(id);
};


/* #todo: mudar nomes */
void KiMostraReg (int id){
	
	//mostra_reg(id);
};


/*
 ***************************************
 * KiShowThreadList:
 *     Mostra os parametros de ALGUMAS das 
 * threads existentes em 
 * threadList[i]. (as primeiras da lista).
 */
void KiShowThreadList (){
	
    mostra_slots();
};


/*
 *****************************************
 * mostra_slots:
 *
 * @todo:
 * Obs: Estamos mostrando informações sobre todos 
 * os processos e todas threads.
 * Porém esse arquivo é para lidar com threads, 
 * então a torina de lidar com processos
 * deve ir pra outro arquivo.
 * @todo: Mudar nome.
 * #bugbug: Não encontro o protótipo dessa função.
 */
//void threadiShowSlots(){ 

void mostra_slots(){
	
    int i; 	
	struct process_d *p;    
    struct thread_d  *t;   


	//
	// Testando o for para process.
	//
	
	/*
	printf(" \n\n ** Process info ** \n\n");
	
	for( i=0; i<PROCESS_COUNT_MAX; i++)
    {
	    p = (void *) processList[i];
	    
		//Mostra as tarefas válidas, mesmo que estejam com problemas.
		if( (void*)p != NULL && 
		        p->used == 1 && 
				p->magic == 1234 )
	    {
			//@todo: Mostrar quem é o processo pai.
		    printf("PID={%d} Directory={%x} Name={%s} \n",p->pid ,p->Directory ,p->name_address);
	    };
    };
	*/
	
	//
	// Testando o for para threads.
	//
	printf("\n # Thread info #\n");
	
//Scan:	

	for( i=0; i<THREAD_COUNT_MAX; i++)
    {
	    t = (void *) threadList[i];
	    
		//Mostra as tarefas válidas, mesmo que estejam com problemas.
		if ( (void *)t != NULL && 
		          t->used == 1 && 
				 t->magic == 1234 )
	    {
			
			
			mostra_slot (t->tid);
		};
    };
};


/*
 *****************************************************
 * mostra_slot:
 *     Mostra as variaveis mais importantes de um slot.
 *     obs: Não precisa mostrar o contexto, tem rotina pra isso.
 *     @todo: Mudar nome.
 *     #bugbug: Não encontro o protótipo dessa função. 
 */
//void threadiShowSlot(int id){  

void mostra_slot (int id){
	
    struct thread_d *t;

    if ( id < 0 || id >= THREAD_COUNT_MAX ){
		
	    printf("pc-threadi-mostra_slot: id\n");
		goto fail;
	};
	
	
	// Structure.
	t = (void *) threadList[id];
	
	if( (void*) t == NULL )
	{
	    printf("pc-threadi-mostra_slot: t\n");
		goto fail;	
	}else{
	
	    // Show one slot.
	    printf("\n");
	    printf("TID   PID   pdPA  Prio  State Quan ms    initial_eip   tName \n");
	    printf("====  ====  ====  ====  ===== ==== ====  ==========    ===== \n");
		
        printf("%d    %d    %x    %d    %d    %d    %d    %x           %s \n", 
			t->tid, 
			t->ownerPID,
			t->DirectoryPA,
			t->priority, 
			t->state,
			t->quantum,
			t->total_time_ms,
			t->initial_eip,
			t->name_address );
			
	};
	
    goto done;

	
fail:	
    printf("fail\n");	
done:
    return; 
};


/*
 *************************************************
 * mostra_reg:
 *    Mostra conteúdo dos registradores de uma thread..
 *
 *    eflags
 *    cs:eip	
 *    ss:esp	
 *    ds,es,fs,gs
 *    a,b,c,d
 *
 *    @todo Mudar nome
 */
//void threadiShowRegisters (int id){   

void mostra_reg (int id){
	
    struct thread_d *t; 

	// Limits.
    if ( id < 0 || id >= THREAD_COUNT_MAX ){
		
	    printf ("fail\n");	
		return;
	}
	
	// Structure.
    t = (void *) threadList[id];
	
	if ( (void *) t == NULL )
	{	
	    
		printf ("fail\n");	
		return;
		
	} else {
		
		
	    // Show registers.	
        
	    printf("\n eflags=[%x]", t->eflags);
	    printf("\n cs:eip=[%x:%x] ss:esp=[%x:%x]", 
		    t->cs, t->eip, t->ss, t->esp );
			
	    printf("\n ds=[%x] es=[%x] fs=[%x] gs=[%x]",
	        t->ds, t->es, t->fs, t->gs );
	
	    printf("\n a=[%x] b=[%x] c=[%x] d=[%x]\n",
	        t->eax, t->ebx, t->ecx, t->edx );
			
			
		//...	
	};
	
};


/* set_thread_priority: */
void set_thread_priority ( struct thread_d *t, unsigned long priority ){
	
    unsigned long ThreadPriority;
	
	if ( (void *) t == NULL )
	{
	    return;
		
	}else{
		
        if ( t->used != 1 || t->magic != 1234 ){
		    return;
	    }	
		//...
	};
	
	ThreadPriority = t->priority;

	// se aprioridade solicitada for igual da prioridade atual.	
	if ( priority == ThreadPriority ){
		return;
	}
	
//do_change:
	
	// se aprioridade solicitada for diferente da prioridade atual.
	if ( priority != ThreadPriority )
	{
		//Muda a prioridade.
        t->priority = priority;
		
		/*
		switch(t->state) 
		{
		    case READY:
		        //@todo if(priority < ThreadPriority){};
				break; 

		    case RUNNING:
			    //@todo
				//if( (void*) t->Next == NULL )
				//{
				//	if(priority < ThreadPriority){
					    //@todo: encontra e prepara uma outra tarefa.
				//	};
				//};
		        break; 
			    //Nada para os outros estados.
		    default:
			    //Nothing for now.
			    break;
		};
		*/
		
    };
};


/*
 ************************************************************
 * SetThreadDirectory:
 *     Altera o endereço do diretório de páginas de uma thread.
 *     Apenas a variável. Não altera o CR3.
 */
 
void SetThreadDirectory ( struct thread_d *thread, unsigned long Address ){
	
    if ( (void *) thread == NULL )
	{
        return;
        
	}else{
		
		//@todo:
		//Aqui podemos checar a validade da estrutura,
		//antes de operarmos nela.
		
		thread->DirectoryPA = (unsigned long) Address;	
	};
};


/*
 ***********************************************************
 * GetThreadDirectory:
 *     Pega o endereço do diretório de páginas de uma thread.
 */
 
unsigned long GetThreadDirectory ( struct thread_d *thread ){
	
    if ( (void *) thread == NULL )
	{
		return (unsigned long) 0;    
		
	}else{
		
		//@todo:
		//Aqui podemos checar a validade da estrutura,
		//antes de operarmos nela.
		
	    return (unsigned long) thread->DirectoryPA;		
	};
	
	return (unsigned long) 0;
};


/*
 * show_preempted_task: #deletar
 *
 *    Mostrar informações sobre a tarefa de baixa prioridade
 *    que teve seu contexto salvo e deu a vez pra outra de
 *    maior prioridade.
 *
 *    @todo: Criar uma variavel global que identifique
 *           a tarefa com contexto salvo.
 *
 */
void show_preempted_task(){
    
	//return;
};


/* #deletar */
void show_tasks_parameters(){  
	
	//return; 
};



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
	
	
	if ( tid < 0 || tid >= THREAD_COUNT_MAX ){
	    
		return; 
	}
	
	Thread = (void *) threadList[tid];
	
	if ( (void *) Thread == NULL )
	{
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
};



/*
 *******************************************************
 * exit_thread:
 *     Exit a thread.
 *     Torna o estado ZOMBIE mas não destrói a estrutura.
 *     Outra rotina destruirá as informações de uma 
 * estrutura de thread zombie.
 */
 
void exit_thread (int tid){
	
    struct thread_d *Thread;
	
	if ( tid < 0 || tid >= THREAD_COUNT_MAX ){
		
	    goto fail;
	}
	
	if ( tid == idle ){
		
		goto fail;
	}
	
	Thread = (void *) threadList[tid];
	
	if ( (void *) Thread == NULL )
	{
		goto fail;
		
	}else{
		
        if ( Thread->magic != THREAD_MAGIC ){
			
			goto fail;
		}
		
		//#bugbug 
		//lembrando que se deixarmos no estado ZOMBIE o 
		//deadthread collector vai destruir a estrutura.
		
		Thread->state = ZOMBIE; 
	};
		
	
	// # reavaliar isso.
	// Se a thread fechada é a atual, 
	// necessitamos de algum escalonamento.	
    // #obs: Essa rotina de reescalonamento não trás problemas.
	
	if ( tid = current_thread )
	{	
	    scheduler ();
    }
	
	
fail:
//Nothing.		
done:
	return;
};


/*
 *****************************************************
 * kill_thread:
 *     Destrói uma thread.
 *     Destroi a estrutura e libera o espaço na lista. 
 */
void kill_thread (int tid){
	
    struct thread_d *Thread;
	
	//Limits.
	if ( tid < 0 || tid >= THREAD_COUNT_MAX ){
		
	    goto fail;	
	}
	
	if ( tid == idle ){
		
		goto fail;
	}
	
	
	//
	// @todo: 
	//    Deve acordar o pai que está esperando o filho fechar.
	//    Mas no caso estamos apenas fechando uma thread.
    //    Caso essa não seja a thread primária, isso não deve 
	// causar o fechamento do processo.	
    //
	
	Thread = (void *) threadList[tid];
	
	if ( (void *) Thread == NULL )
	{
		goto fail;
		
	}else{
		
		
	    //@todo pegar o id do pai e enviar um sinal e acorda-lo
        //se ele estiver esperando por filho.		
        Thread->used = 0;
        Thread->magic = 0; 		
		Thread->state = DEAD; 
		//...
		
		ProcessorBlock.threads_counter--;
		if ( ProcessorBlock.threads_counter < 1 ){
			//#bugbug
			panic("kill_thread: threads_counter");
		}		
		
        threadList[tid] = (unsigned long) 0;
        Thread = NULL;		
	};
	
	// # reavaliar isso.
	// Se a thread fechada é a atual, 
	// necessitamos de algum escalonamento.	
    if ( tid == current_thread )
	    scheduler();
	
fail:	
	
//Done.
done:
    current_thread = idle;
	return;
};


/*
 **********************************************************
 * dead_thread_collector:
 *     Procura por uma thread no estado zombie mata ela.
 *
 * @todo
 *     Alerta o processo que a thread morreu.
 */
 
void dead_thread_collector (){
	
	int i;
    struct thread_d *Thread;   	  
    struct process_d *p;         
	
//Scan:
	
	for ( i=0; i < THREAD_COUNT_MAX; i++ )
	{
	    Thread = (void *) threadList[i];
		
		if ( (void *) Thread != NULL )
		{
		    if ( Thread->state == ZOMBIE && 
			     Thread->used == 1 && 
				 Thread->magic == 1234 )
			{
				
				if( Thread->tid == idle )
				{
					printf("dead_thread_collector: we can't close idle\n");
					die();
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
				
				ProcessorBlock.threads_counter--;
				
				//#bugbug
				if ( ProcessorBlock.threads_counter < 1 ){
					panic("dead_thread_collector: threads_counter");
				}
	
			};
			//Nothing.
		};
		//Nothing.
	};
	
	//@todo:
	// * MOVEMENT 10 (zombie --> Dead)
	// * MOVEMENT 11 (zombie --> Initialized) .. reinicializar.	
};


void kill_all_threads (){
	
	int i;
    
	for ( i=0; i < THREAD_COUNT_MAX; i++ ){
		
	    kill_thread (i);	
	}
};


//
// End.
//

