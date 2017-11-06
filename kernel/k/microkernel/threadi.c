/*
 * File: threadi.c 
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
 */

 
#include <kernel.h>


/*
 * KiShowPreemptedTask
 * @todo: Substituir a palavra task por thread. KiShowPreemptedThread
 *
 */
void KiShowPreemptedTask(){
    return;
};

 
/*
 * KiSetTaskStatus:
 *     @todo: Substituir a palavra task por thread. KiSetThreadStatus
 */ 
void KiSetTaskStatus(unsigned long status)
{
    //@todo: criar interface para mudanca de status.
	
	set_task_status(status);
	return;
};


/*
 * KiGetTaskStatus
 * @todo: Substituir a palavra task por thread. KiGetThreadStatus
 *
 */
unsigned long KiGetTaskStatus(){ 
    return (unsigned long) get_task_status(); 
};



/*
 * KiSaveContextOfNewTask
 * @todo: Substituir a palavra task por thread. KiSaveContextOfNewThread
 *
 *
 */
void KiSaveContextOfNewTask(int id, unsigned long *task_address){
    return;
};


/*
 * KiReloadCurrentTask
 *  @todo: Substituir a palavra task por thread. KiReloadCurrentThread.
 *
 */
void KiReloadCurrentTask(){
    return;
};


void KiSetQuantum(unsigned long q){    
    return;
};


unsigned long KiGetQuantum(){ 
    return (unsigned long) 0; 
};


void KiSetCurrentQuantum( unsigned long q){
    return;
};


unsigned long KiGetCurrentQuantum(){ 
    return (unsigned long) 0; 
};


void KiSetNextQuantum( unsigned long q){
    return;
};


unsigned long KiGetNextQuantum(){ 
    return (unsigned long) 0; 
};


void KiSetFocus(int pid){
	return;
};


//Pegar o foco do que? thread?!
int KiGetFocus(){ 
    return (int) 0; 
};


void KiDebugBreakpoint(){
    return;
};


void KiShowTasksParameters(){
    return;
};


void KiMostraSlots(){
	//mostra_slots();
    return;
};


void KiMostraSlot(int id){ 
	//mostra_slot(id);
    return;
};


void KiMostraReg(int id){
	//mostra_reg(id);
    return;
};


/*
 * KiShowThreadList:
 *     Mostra os parametros de ALGUMAS das threads existentes em 
 * threadList[i]. (as primeiras da lista).
 *
 */
void KiShowThreadList(){
    mostra_slots();
    return;	
};


/*
 * mostra_slots:
 *
 * @todo:
 * Obs: Estamos mostrando informações sobre todos os processos e todas threads.
 * Porém esse arquivo é para lidar com threads, então a torina de lidar com processos
 * deve ir pra outro arquivo.
 */
void mostra_slots()
{
    int i; 	
	struct process_d *p;    //Process.
    struct thread_d  *t;    //Threads.


	//
	// Testando o for para process.
	//
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
	
	
	//
	// Testando o for para threads.
	//
	printf(" \n\n ** Thread info ** \n\n");
	
	for( i=0; i<THREAD_COUNT_MAX; i++)
    {
	    t = (void *) threadList[i];
	    
		//Mostra as tarefas válidas, mesmo que estejam com problemas.
		if( (void*)t != NULL && 
		        t->used == 1 && 
				t->magic == 1234 )
	    {
		  printf("TID={%d} Step={%d} PPID={%d} pHandle={%x} State={%d} Handle={%x} Name={%s}\n\n",t->tid 
		      ,t->step ,t->ppid, t->process ,t->state ,(void*) t ,t->name_address);
	    };
    };
    
	
	
done:	
    printf("Done!\n");
	//refresh_screen();
	//while(1){}
    return;
};

/*
 * mostra_slot:
 *     Mostra as variaveis mais importantes de um slot.
 *     obs: Não precisa mostrar o contexto, tem rotina pra isso.
 *     @todo: Mudar nome.
 */
void mostra_slot(int id)
{
    struct thread_d *t;

	// Limits.
    if(id < 0 || id >= THREAD_COUNT_MAX){
	    printf("mostra_slot: invalid ID\n");
		return;
	};
	
	
	// Structure.
	t = (void *) threadList[id];
	
	if( (void*) t == NULL){
	    printf("mostra_slot: Empty slot\n");
		return;	
	}else{
	
	    // Show one slot.
	    printf("\n");
	    printf("TID  PPID pHandle  Prio  State   tName   \n");
	    printf("===  ==== ======== ====  =====   ======= \n");
        printf("%d   %d   %x       %d    %d      %s      \n" ,t->tid 
	                                                         ,t->ppid
                                                             ,t->process															
														     ,t->priority 
														     ,t->state
														     ,t->name_address);
	};
															 
done:
    printf("Done\n");
    return; 
};


/*
 * mostra_reg:
 *    Mostra conteúdo dos registradores de uma thread..
 *
 *    eflags
 *    cs:eip	
 *    ss:esp	
 *    ds,es,fs,gs
 *    a,b,c,d
 *
 *    @todo Mudar nome: KiShowRegs(int tid)
 */
void mostra_reg(int id)
{
    struct thread_d *t; 

	// Limits.
    if(id < 0 || id >= THREAD_COUNT_MAX){
	    return;
	};
	
	// Structure.
    t = (void *) threadList[id];
	
	if( (void*) t == NULL){
	    return;
	};
    	
	// Show registers.	
    printf("\n");
	printf("eflags=[%x]\n",t->eflags);
	printf("cs:eip=[%x:%x]\n",t->cs ,t->eip );
	printf("ss:esp=[%x:%x]\n",t->ss ,t->esp); 
    printf("ds=[%x] es=[%x] fs=[%x] gs=[%x]\n",t->ds ,t->es ,t->fs ,t->gs);
	printf("a=[%x] b=[%x] c=[%x] d=[%x]\n",t->eax ,t->ebx ,t->ecx ,t->edx); 
	
done:    
	return; 
};


/*
 * set_thread_priority:
 *     Muda a prioridade de uma tarefa específica.
 */
void set_thread_priority(struct thread_d *t, unsigned long priority)
{
    unsigned long ThreadPriority;
	
	if( (void*) t == NULL ){
	    return;
	};
	
    if( t->used != 1 || t->magic != 1234 ){
		return;
	}	
	
	ThreadPriority = t->priority;

	// se aprioridade solicitada for igual da prioridade atual.	
	if( priority == ThreadPriority ){
		return;
	};
	
	// se aprioridade solicitada for diferente da prioridade atual.
	if( priority != ThreadPriority )
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
//Done.
done:
    return;	
};


/*
 * SetThreadDirectory:
 *     Configura o diretório de páginas para uma thread.
 *     Apenas a variável. Não altera o CR3.
 */
void SetThreadDirectory(struct thread_d *thread, unsigned long Address)
{
    if( (void*) thread == NULL ){
        return;        
	};
//Nothing.		
done:
	thread->Directory = (unsigned long) Address;
	return;
};


/*
 * GetThreadDirectory:
 *     Pega o endereço do diretorio de páginas de uma thread.
 *
 */
unsigned long GetThreadDirectory(struct thread_d *thread)
{
    if( (void*) thread == NULL ){
        return (unsigned long) 0;        
	};
//Nothing.	
done:
	return (unsigned long) thread->Directory;
};


/*
 * show_preempted_task: 
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
    return;
};


void show_tasks_parameters(){  
	return; 
};


/*
 * exit_thread:
 *     Exit a thread.
 *     Torna o estado ZOMBIE mas não destrói a estrutura.
 *     Outra rotina destruirá as informações de uma estrutura de 
 * thread zombie.
 */
void exit_thread(int tid)
{
	int i;
    struct thread_d *Thread;

	
	//Limits. 
	if(tid < 0 || tid >= THREAD_COUNT_MAX){
	    return;	
	};    
	
	Thread = (void*) threadList[tid];
	
	if( (void*) Thread == NULL )
	{
		return;
	}
	else
	{	
        //Se estiver corrompida.
        if(Thread->magic != THREAD_MAGIC){
			return;
		};
		//Thread->exit_code = 0;    //@todo: Isso é necessário. Onde está.
		Thread->state = ZOMBIE; 
	};
		
	//Se a thread fechada é a atual, necessitamos de algum escalonamento.	
    if(tid = current_thread){
	    scheduler();
    };
	
//Nothing.		
done:
	return;
};


/*
 * kill_thread:
 *     Destrói uma thread.
 *     Destroi a estrutura e libera o espaço na lista. 
 */
void kill_thread(int tid)
{
    struct thread_d *Thread;
	
	//Limits.
	if(tid < 0 || tid >= THREAD_COUNT_MAX){
	    return;	
	};    
	
	//
	// @todo: 
	//     Antes, deve acordar o pai que está esperando o filho fechar.
	//	
	
	
	//@todo: Checar used e magic.
	
	Thread = (void*) threadList[tid];
	
	if( (void*) Thread == NULL){
		return;
	}
	else
	{
	    //@todo pegar o id do pai e enviar um sinal e acorda-lo
        //se ele estiver esperando por filho.		
        Thread->used = 0;
        Thread->magic = 0; 		
		Thread->state = DEAD; 
		//...
	};
	
//Done.
done:
    //threadList[tid] = NULL;   //@todo: Liberar o espaço na lista.
    Thread = NULL;		
	return;
};


/*
 * dead_thread_collector:
 *     Procura por uma thread no estado zombie mata ela.
 *
 * @todo
 *     Alerta o processo que a thread morreu.
 *
 */
void dead_thread_collector()
{
	int i;
    struct thread_d  *Thread;    //Thread.	  
    struct process_d *p;         //Process.
	
	for( i = 0; i < THREAD_COUNT_MAX; i++ )
	{
	    Thread = (void *) threadList[i];
		
		if( (void *) Thread != NULL )
		{
		    if( Thread->state == ZOMBIE && 
			    Thread->used == 1 && 
				Thread->magic == 1234 )
			{
				//kill_thread(Thread->tid);
				Thread->used = 0;
				Thread->magic = 0;
				Thread->state = DEAD; // Por enquanto apenas fecha.
				//...
			};
			//Nothing.
		};
		//Nothing.
	};
	
	//@todo:
	// * MOVEMENT 10 (zombie --> Dead)
	// * MOVEMENT 11 (zombie --> Initialized) .. reinicializar.
	
done: 
    //threadList[i] = NULL;   //@todo: Liberar o espaço na lista.	
    Thread = NULL;
	return;
};


//
//fim.
//

