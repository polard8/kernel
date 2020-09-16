/*
 * File: spawn.c
 *
 * Descri��o:
 *     Executa uma thread pela primeira vez usando o m�todo Spawn. 
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


static inline void spawnSetCr3 ( unsigned long value )
{
	//#todo:
	//Podemos fazer alguma filtragem aqui ??
	
    __asm__ ( "mov %0, %%cr3" : : "r" (value) );
}


/*
 ******************************************************************
 * KiSpawnTask:
 *     Interface para chamada de m�dulo interno para rotina de 
 * spawn de thread.
 */
 
// #todo
// change to (int tid). 
 
void KiSpawnTask (int id){


    if ( id < 0 || id >= THREAD_COUNT_MAX )
    {
        printf ("spawn-KiSpawnTask: TID=%d", id );
        die ();
    }

    //
    // do spawn.
    //

    spawn_thread (id);

    
    // Not reached.
    panic ("spawn-KiSpawnTask");
}


/*
 *********************************************************
 * spawn_thread: 
 *     Execute a thread for the first time.
 *     The thread needs to be in the state 'STANDBY'.
 *     @todo: Mudar para spawnThread(int tid).
 */ 
 
	// #bugbug
	// Archtecture dependent stuff.
	// x86.
 
void spawn_thread (int id){

    int Status;

    struct thread_d *Current;
    struct thread_d *spawn_Pointer;

	// #todo: 
	// Filtrar tid.

    if ( id < 0 || id >= THREAD_COUNT_MAX){
        printf ("spawn-spawn_thread: TID=%d", id );
        die ();
    }


	//
	// Pega na lista.
	//

	// Pega e salva a atual.
	// Ser� usada no caso de falha.

    Current = (void *) threadList[current_thread];

	// #importante:
	// Struct para a thread que ser� executada.
	// O id foi passado via argumento.

    spawn_Pointer = (void *) threadList[id]; 

    if ( (void *) spawn_Pointer == NULL ){
        printf ("spawn_thread: Pointer TID={%d}", id );
        die ();

    } else {


        // ?? spawn_Pointer->tid == id ???
        if (spawn_Pointer->tid != id)
        {
            panic("spawn_thread: #debug spawn_Pointer->tid != id");
        }

        // State ~ Checa o estado da thread.
        if ( spawn_Pointer->state != STANDBY ){
            printf ("spawn_thread: State TID={%d}\n", id );
            die ();
        }


        // Saved ~ Se o contexto est� salvo, � porque n�o � a primeira vez.
        if ( spawn_Pointer->saved == 1 ){
            printf ("spawn_thread: Saved TID={%d}\n", id );
            die ();
        }


        // ??
        // More checks ?
    };


    //
    // Preparar a thread para executar.
    //


	// Context:
	// Se a thread N�O est� com contexto salvo, ent�o pode ser que ela nunca 
	// tenha sido executada.

    if ( spawn_Pointer->saved == 0 )
    {

		// Configura a vari�vel global.

        current_thread = (int) spawn_Pointer->tid;   

        //fazemos isso logo abaixo.
        //    current_process = spawn_Pointer->process->pid;

        // ?? e o current_process ?? 

		// Configura a pr�xima.
		// A next ser� a antiga current salva anteriormente.

        spawn_Pointer->next = (void *) Current;        


		// * MOVEMENT 2 (Standby --> Running).


        if ( spawn_Pointer->state == STANDBY )
        {
            spawn_Pointer->state = RUNNING;    

            queue_insert_data ( queue, 
                (unsigned long) spawn_Pointer, QUEUE_RUNNING );
        }

		// Destrava o mecanismo de taskswitch.
		// Destrava o Scheduler.

        set_task_status(UNLOCKED);
        scheduler_unlock(); 

	    //@todo: Continua ...
    };


	// #importante
	// Se o status estiver diferente de RUNNING, ent�o algo 
	// deu errado na prepara��o.

    if ( spawn_Pointer->state != RUNNING ){
        printf ("spawn_thread: State TID={%d}\n", id );
        die ();
    }


    // #debug
    //printf ("spawn_thread: iret\n");
    //refresh_screen();

	// Configura a vari�vel global.

    current_process = spawn_Pointer->process->pid;


    IncrementDispatcherCount (SELECT_INITIALIZED_COUNT);


	//Set cr3 and flush TLB.

    spawnSetCr3 ( (unsigned long) spawn_Pointer->DirectoryPA );

    asm ("movl %cr3, %eax");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("nop");
    asm ("movl %eax, %cr3");


 
	//Isso mostra que o contexto da thread clonada em fork está certo nesse momento.
	//show_reg(spawn_Pointer->tid);
	//refresh_screen();
    //while(1){}
	
	
	
	// #bugbug
	// Isso est� falando na m�quina real.
	// Talvez seja porque estamos colocando os calores da pilha do kernel
	// e n�o na pilha do aplicaitvo como faz a irq0.
	// #test vamos tentar usar a pilha do aplicativo pra ver se o iret funciona na m�quina real.
	
    // #problema
	// Como faremos para que o aplicativo pegue esses valores.
	// pois o ponteiro de pilha aponta para um valor em ring 0,
	// ent�o o aplicativo estaria proibido de usar essa pilha ??!!
	// Porvavelmente sim ,,,, mas um aplicativo em ring0 n�o.
	// talvez se a mem�ria do kernel para ring3 e fazermos um iret para
	// dentro do kernel seja poss�vel fazer um segundo iret para fora.
	
	//lembrando que o handler do irq0 recebe uma pilha em ring3 por isso consegue voltar.
	//como n�o temos uma pilha em ring3 , en�o n�o consegumos voltar.
	
    // Spiritual quote:
	// "Body and Things"

    //Segmentos.

    //#bugbug
    //Eax sujou. Isso é um problema para a thread clonada de fork()
    //Por isso que ela não deve usar o spawn ... e sim ficar ready.

    asm volatile (" cli\n"
                  " mov $0x23, %ax \n"
                  " mov %ax, %ds \n"
                  " mov %ax, %es \n"
                  " mov %ax, %fs \n"
                  " mov %ax, %gs \n");  


	//unsigned long argc = 1234;
	//#test
	//Tentando enviar linha de comando para crt0 ou main() do aplicativo.
	//#importante: O aplicativo n�o pode ler uma string que esteja escrito 
	//em kernel mode, ent�o n�o adianta passar o ponteiro.

	//asm("pushl %0" :: "r" ((unsigned long) ? ) : "%esp");
	//asm("pushl %0" :: "r" ((unsigned long) argc ) : "%esp");  //argc 

	//argc 
	//Ok. isso funcionou ... 
    // main no aplicativo recebeu argc do crt0.
	//até mesmo na thread clonada no fork();
    // o que não é bom ... pois a thread clonada tem que ter os valores
    //da thread do processo pai. >> vamos suprimir isso.
    
    //asm (" mov $0x1234, %ebx \n");
	
	//#test
	//Mudando eflags para iopl 3 antes de usarmos a pilha.
	
	asm (" pushl $0x3000 \n");
	asm (" popfl \n");
	
	// #bugbug
	// Os carinhas do gcc 9.1.0 resolveram sacanear.
	// N�o posso usar mais isso porque eles tiveram um ataque de pelanca.
	// Warning:
	// "Listening the stack pointer register in a clobber list is deprecated."  
	
	
	// Pilha para iret.
    // ss, esp, eip, cs, eip;

    //Pilha para iret.
    asm ("pushl %0" :: "r" ((unsigned long) spawn_Pointer->ss     & 0xffff )  );    //ss.
    asm ("pushl %0" :: "r" ((unsigned long) spawn_Pointer->esp             )  );    //esp.
    asm ("pushl %0" :: "r" ((unsigned long) spawn_Pointer->eflags          )  );    //eflags.
    asm ("pushl %0" :: "r" ((unsigned long) spawn_Pointer->cs     & 0xffff )  );    //cs.
    asm ("pushl %0" :: "r" ((unsigned long) spawn_Pointer->eip             )  );    //eip.
    

	// #importante
	// Precismos disso pois foi o irq0 quem nos trouxe aqui.

    asm ("movb $0x20, %al \n");
    asm ("outb %al, $0x20 \n");

	//
	// Fly!
	//

    asm ("iret \n");    

    /*
	// # teste sujo
	//tss
	//isso ser� um test para taskswitch via hardware,
	//precisa habilitar flag nt antes,
	//asm  ("ljmp $0x2B, $0x401000 \n\t");
	//asm ("sti  \n"); 
    */

    panic ("spawn_thread: iret fail");
}


//
// End.
//

