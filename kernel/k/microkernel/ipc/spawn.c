/*
 * File: spawn.c
 *
 * Descrição:
 *     Executa uma thread pela primeira vez usando o método Spawn. 
 *     Faz parte do Process Manager, parte fundamental do Kernel Base.
 * Obs: Spawn significa 'desovar'.
 *
 * O Spawn coloca uma nova thread pra executar efetuando
 * um iret. A pilha foi configurada para user  mode antes de efetuar
 * o iret.
 *
 * Histórico:
 *     Versão 1.0, 2015 -  Esse arquivo foi criado por Fred Nora.
 *     Versão 1.0, 2016 - Aprimoramento geral das rotinas básicas.
 *     //...
 */


#include <kernel.h>

/*
 * KiSpawnTask:
 *     Interface para chamada de módulo interno para rotina de spawn de 
 * thread.
 */
void KiSpawnTask(int id)
{
    //
	// @todo: Some checks.
	//

	if(id<0)
	{
		printf("KiSpawnTask Error: Id={%d}.",id);
	    //@todo: Talvez aqui devesse parar.
		return;	
	};

	//
	// More ?!
	//

//Done.	
done:
	spawn_task(id);

	//
	// No return.
	//
};



/*
 * spawn_task: 
 *     Executa uma thread pela primeira vez.
 *     A thread deve estar no estado INITIALIZED.
 *     @todo: Mudar para spawnThread(int tid).
 */
//void spawnThread(int tid) 
 
void spawn_task(int id)
{
	int Status;
	struct thread_d *Current;
    struct thread_d *spawn_Pointer;


	//
	// @todo: Filtrar tid.
	//

	//if(tid < 0){}


	//
	// Pega na lista.
	//

	//Pega e salva a atual.
	//Será usada no caso de falha.
	Current = (void *) threadList[current_thread];


	//
	// Struct para a thread que será executada.
	// O id foi passado via argumento.
	//

	spawn_Pointer = (void *) threadList[id]; 
	if((void*) spawn_Pointer == NULL)
	{
	    printf("spawn_task error: Pointer. TID={%d}",id);
		refresh_screen();
		while(1){};
	}
    else
    {
	    // State ~ Checa o estado da tarefa.	 
        if(spawn_Pointer->state != STANDBY){
            printf("spawn_task error: State. TID={%d}\n",id);
		    refresh_screen();
		    while(1){}
        };

	    // Saved ~ Se o contexto está salvo, é porque não é a primeira vez.
        if(spawn_Pointer->saved == 1){
            printf("spawn_task error: Saved. TID={%d}\n",id);
		    refresh_screen();
		    while(1){}
        };    
	    //More checks ?!!...
	};	

    //
	// Check context.
	//

	Status = contextCheckThreadRing3Context(id);
	if(Status != 0){
	    printf("spawn_task error: Context. TID={%d}",id);
		refresh_screen();
		while(1){}
	};

    //
    // Preparar a thread para executar.
    //

threadSetUp:

/*
 * Context:
 *     Se a thread NÃO está com contexto salvo, então pode ser que ela nunca 
 * tenha sido executada.
 */
	
	//
	// @todo: if(spawn_Pointer->saved == 1){...}
	// E se o contexto ja estivesse salvo ? Teríamos um problema ?
	//

	if(spawn_Pointer->saved == 0)
	{
	    current_thread = (int) spawn_Pointer->tid;    //Set current.
		
		spawn_Pointer->Next = (void*) Current;        //Next thread. A next será a antiga current.

		// * MOVEMENT 2 (Standby --> Running).
        if(spawn_Pointer->state == STANDBY){
			spawn_Pointer->state = RUNNING;    
			queue_insert_data(queue, (unsigned long) spawn_Pointer, QUEUE_RUNNING);
		};	
		
		set_task_status(UNLOCKED);    //Destrava o mecanismo de taskswitch.
	    scheduler_unlock();	          //Destrava o Scheduler. 
		
	    //@todo: Continua ...
	};


	//Se o status estiver diferente de RUNNING, algo deu errado na preparação.
	if(spawn_Pointer->state != RUNNING)
	{
		//...
        printf("* spawn_task error: State. TID={%d}\n",id);
		refresh_screen();
		while(1){}
	};

	//Debug:
	//printf("spawn_task: Spawn thread %d ... \n",id);
	//refresh_screen();

	IncrementDispatcherCount(SELECT_INITIALIZED_COUNT);

 /*
  Gn 15: 9-17:
  " E as aves de rapina desciam sobre os cadáveres, Abrão, porém,
  as enxotava. ".

  " Ele tomou o pão, deu graças, e o partiu e deu a seus discípulos, dizendo:
	TOMAI, TODOS, E COMEI: ISTO É O MEU CORPO, QUE SERÁ ENTREGUE POR VÓS. ".
  */

    //Segmentos.
    asm volatile(" cli \n"
                 " mov $0x23, %ax \n"
                 " mov %ax, %ds \n"
                 " mov %ax, %es \n"
                 " mov %ax, %fs \n"
                 " mov %ax, %gs \n");

	//Pilha para iret.
    asm("pushl %0" :: "r" ((unsigned long) spawn_Pointer->ss)     : "%esp");    //ss.
    asm("pushl %0" :: "r" ((unsigned long) spawn_Pointer->esp)    : "%esp");    //esp.
    asm("pushl %0" :: "r" ((unsigned long) spawn_Pointer->eflags) : "%esp");    //eflags.
    asm("pushl %0" :: "r" ((unsigned long) spawn_Pointer->cs)     : "%esp");    //cs.
    asm("pushl %0" :: "r" ((unsigned long) spawn_Pointer->eip)    : "%esp");    //eip.
	// EOI and iret.
	asm("movb $0x20, %al \n");
	asm("outb %al, $0x20 \n");
	asm("sti  \n"); 
	asm("iret \n");    //Fly!
    //Nothing.
fail:
	panic("spawn_task error: *Return!");
	while(1){};
};


//
// Fim.
//

