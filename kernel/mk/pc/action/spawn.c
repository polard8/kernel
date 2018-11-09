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
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - Small changes.
 *     //...
 */


#include <kernel.h>


static inline void spawnSetCr3 ( unsigned long value ){
	
	
	//#todo:
	//Podemos fazer alguma filtragem aqui ??
	
    __asm__ ( "mov %0, %%cr3" : : "r" (value) );
};


/*
 **********************************************************************
 * KiSpawnTask:
 *     Interface para chamada de módulo interno para rotina de spawn de 
 * thread.
 */
void KiSpawnTask (int id){
	
    
	// @todo: 
	// Some checks.

	if ( id < 0 )
	{
		printf("spawn-KiSpawnTask: ERROR TID={%d}", id );
		die();
	};

	//
	// More ?!
	//

    //Done.	

	spawn_thread (id);

	printf("spawn-KiSpawnTask: ERROR");
	
	//
	// No return.
	//
};



/*
 *********************************************************
 * spawn_thread: 
 *     Execute a  thread for the first time.
 *     The thread needs to be in the state 'INITIALIZED'.
 *     @todo: Mudar para spawnThread(int tid).
 */ 
 
void spawn_thread (int id){
	
	int Status;
	struct thread_d *Current;
    struct thread_d *spawn_Pointer;


	//
	// @todo: Filtrar tid.
	//

	if ( id < 0 )
	{
		//#todo
	    return;	
	}


	//
	// Pega na lista.
	//

	// Pega e salva a atual.
	// Será usada no caso de falha.
	
	Current = (void *) threadList[current_thread];

	// #importante:
	// Struct para a thread que será executada.
	// O id foi passado via argumento.

	spawn_Pointer = (void *) threadList[id]; 
	
	if ( (void *) spawn_Pointer == NULL )
	{
	    printf ("spawn_thread: Pointer TID={%d}", id );
		die();
		
	} else {
	    
		// State ~ Checa o estado da thread.	 
        
		if ( spawn_Pointer->state != STANDBY )
		{
            printf ("spawn_thread: State TID={%d}\n", id );
		    die();
        };

		
	    // Saved ~ Se o contexto está salvo, é porque não é a primeira vez.
		
        if ( spawn_Pointer->saved == 1 )
		{
            printf ("spawn_thread: Saved TID={%d}\n", id );
		    die();
        };  
		
		
	    // ??
		// More checks ?
	};	
	
	
    //
    // Preparar a thread para executar.
    //

	
	// Context:
	// Se a thread NÃO está com contexto salvo, então pode ser que ela nunca 
	// tenha sido executada.

	if ( spawn_Pointer->saved == 0 )
	{
		
		// Configura a variável global.
		
	    current_thread = (int) spawn_Pointer->tid;    
		
		// Configura a próxima.
		// A next será a antiga current salva anteriormente.
		
		spawn_Pointer->Next = (void *) Current;        

		
		// * MOVEMENT 2 (Standby --> Running).
		
        if ( spawn_Pointer->state == STANDBY )
		{
			spawn_Pointer->state = RUNNING;    
			
			queue_insert_data ( queue, (unsigned long) spawn_Pointer, 
			    QUEUE_RUNNING );
		};	
		
		
		// Destrava o mecanismo de taskswitch.
		// Destrava o Scheduler.
		
		set_task_status(UNLOCKED);    
	    scheduler_unlock();	           
		
	    //@todo: Continua ...
	};


	// #importante
	// Se o status estiver diferente de RUNNING, então algo 
	// deu errado na preparação.
	
	if ( spawn_Pointer->state != RUNNING )
	{
        printf("* spawn_thread: State TID={%d}\n", id );
		die();
	};
	
	
	// Configura a variável global.
	
	current_process = spawn_Pointer->process->pid;
	

	IncrementDispatcherCount(SELECT_INITIALIZED_COUNT);
	
	
	// #todo
	// setup cr3.
	// flush pipeline
	
	// setup cr3.
	spawnSetCr3 ( (unsigned long) spawn_Pointer->DirectoryPA );
	
	// flush pipeline
	asm ("movl %cr3, %eax");
	asm ("nop");
	asm ("nop");
	asm ("nop");
	asm ("nop");
    asm ("movl %eax, %cr3");			
	
	
    // Spiritual quote:
	// "Body and Things"

    //Segmentos.
	
    asm volatile (" cli \n"
                  " mov $0x23, %ax \n"
                  " mov %ax, %ds \n"
                  " mov %ax, %es \n"
                  " mov %ax, %fs \n"
                  " mov %ax, %gs \n");
				 
				 
	
    //unsigned long argc = 1234;	
	//#test
    //Tentando enviar linha de comando para crt0 ou main() do aplicativo.	
	//#importante: O aplicativo não pode ler uma string que esteja escrito 
	//em kernel mode, então não adianta passar o ponteiro.
	
	//asm("pushl %0" :: "r" ((unsigned long) ? ) : "%esp");			 
	//asm("pushl %0" :: "r" ((unsigned long) argc ) : "%esp");  //argc 	

	//argc 
	//Ok. isso funcionou ... main no aplicativo recebeu argc do crt0.
	asm (" mov $0x1234, %ebx \n");
	  
	//Pilha para iret.
    asm ("pushl %0" :: "r" ((unsigned long) spawn_Pointer->ss)     : "%esp");    //ss.
    asm ("pushl %0" :: "r" ((unsigned long) spawn_Pointer->esp)    : "%esp");    //esp.
    asm ("pushl %0" :: "r" ((unsigned long) spawn_Pointer->eflags) : "%esp");    //eflags.
    asm ("pushl %0" :: "r" ((unsigned long) spawn_Pointer->cs)     : "%esp");    //cs.
    asm ("pushl %0" :: "r" ((unsigned long) spawn_Pointer->eip)    : "%esp");    //eip.
	// EOI and iret.
	//Obs: Isso suja o registrador eax.
	//parece que isso é realmente preciso, libera o teclado.
	asm ("movb $0x20, %al \n");
	asm ("outb %al, $0x20 \n");
	//asm(" movl $0, %eax \n");
	asm ("sti  \n"); 
	
	asm ("iret \n");    //Fly!
    
	//Nothing.
	
//fail:

	panic ("*spawn_task: Return");
	
};


//
// End.
//

