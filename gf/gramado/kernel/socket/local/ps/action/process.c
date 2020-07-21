/*
 * File: ps/action/process.c 
 *
 * Descri��o:
 *     Gerenciamento de processos.
 *     PM - Process Manager (Parte fundamental do Kernel Base).
 *     Interfaces para o kernel chamar as rotinas de gerenciamento de
 * processos. 
 *     As rotinas aqui s�o independentes da arquitetura, quem se preocupa
 * com a arquitetura s�o as rotinas de inicializa��o comecadas por Ki.
 *     'Ki' para m�dulos internos do kernel.
 *
 * Atribui��es:
 *     Rotinas de gerenciamento das processos, cria��o, inicializa��o,
 * finaliza��o, task switch e outros.
 *
 *    Tipos de Processos:
 *
 *    PB - Processos inclu�dos no Kernel Base.
 *    P0 - Processos em ring0.
 *    P1 - Processos em ring1.
 *    P2 - Processos em ring2.
 *    P3 - Processos em ring3, User Mode.
 *
 * @todo: 
 * Essas interfaces devem ser padronizadas, obedecendo roteiros de abertura, 
 * fechamento, salvamento e restaura��o de pilha ou argumento.
 * +Criar a fun��o get_current_pid. (obs: Isso j� existe)
 *
 * In this file:
 * ============
 *     +processSendSignal
 *     +create_process 
 *     +CloseAllProcesses
 *     +show_process_information
 *     +muitas outras rotinas...
 *
 * History:
 *     2015 - Create by Fred Nora.
 */
 
 
/*
    Fluxo padr�o:
	
	The Standard Streams.
	
	Every process is initialized with three open file descriptors, 
	stdin, stdout, and stderr. 
	stdin is an abstraction for accepting input (from the keyboard or from pipes) and 
	stdout is an abstraction for giving output (to a file, to a pipe, to a terminal).

    That's a very simplified explanation but true nonetheless. 
	Those three file descriptors are collectively called 'The Standard Streams'.	
    
	Standard input - this is the file handle that your process reads to 
	get information from you.
    Standard output - your process writes normal information to this file handle.
    Standard error - your process writes error information here.
	
    Quando um programa inicia, 
	o sistema operacional automaticamente define quem � 
	a entrada padr�o (geralmente o teclado) e quem � 
	a sa�da padr�o (geralmente a tela).
*/ 
 
 
#include <kernel.h>



//
// Fun��es importadas.
//

extern unsigned long get_page_dir (void);


//
// Vari�veis internas.
//

//int processmanagerStatus;
//int processmanagerError;
//...

int caller_process_id;

int processNewPID;   






void process_enter_criticalsection(int pid)
{
    struct process_d *p;


    p = (void *) processList[pid];

    if ( (void *) p == NULL ){
        panic ("process_enter_criticalsection: p \n");


    } else {

        // todo: validation
        
        __spinlock_ipc = 1;
        criticalsection_pid = (pid_t) pid;
        p->_critical = 1;
    };

}


void process_exit_criticalsection(int pid)
{
    struct process_d *p;


    p = (void *) processList[pid];

    if ( (void *) p == NULL ){
        panic ("process_exit_criticalsection: p \n");


    } else {

        // todo: validation
        
        __spinlock_ipc = 0;
        criticalsection_pid = (pid_t) 0;
        p->_critical = 0;
    };
}



/*
// Chamada pelo timer.c
int process_profiler();
int process_profiler()
{
    return -1;
}
*/



unsigned long __GetProcessStats ( int pid, int index )
{
    struct process_d *p;

    //#todo:
    //checar validade dos argumentos.

	//Struct.
    p = (void *) processList[pid];

    if ( (void *) p == NULL ){
        printf ("__GetProcessStats: struct \n");
        return 0; 

    } else {
        //checar validade.
		//...
    };

	
	
	
	
    switch ( index )
    {

        case 1:
           return (unsigned long) p->pid;
           break;            
            
        case 2:
           return (unsigned long) p->ppid;
           break;            

        case 3:
           return (unsigned long) p->uid;
           break;            

        case 4:
           return (unsigned long) p->gid;
           break; 
           
        //state    
        case 5:
            return (unsigned long) p->state;
            break;                      
           
        case 6:
            return (unsigned long) p->plane;
            break;              
           
        case 7:
            return (unsigned long) p->input_type;
            break;              

        case 8:
            return (unsigned long) p->personality;
            break;              

        case 9:
            return (unsigned long) p->appMode;
            break;              

        
        case 10:
            return (unsigned long) p->private_memory_size;
            break;  
           
        case 11:
            return (unsigned long) p->shared_memory_size;
            break;          

        case 12:
            return (unsigned long) p->workingset_size;
            break;          

        case 13:
            return (unsigned long) p->workingset_peak_size;
            break;          

        case 14:
            return (unsigned long) p->pagefaultCount;
            break;          

        case 15:
            return (unsigned long) p->DirectoryPA;
            break;
           
        case 16:
            return (unsigned long) p->DirectoryVA;
            break;

        //image address.    
        case 17:
            return (unsigned long) p->Image;
            break;

        case 18:
            return (unsigned long) p->ImagePA;
            break;


        case 19:
            return (unsigned long) p->childImage;
            break;
           
        case 20:
           return (unsigned long) p->childImage_PA;
           break;
          
        case 21:
            return (unsigned long) p->Heap;
            break;

        case 22:
            return (unsigned long) p->HeapEnd;
            break;
           
        case 23:
            return (unsigned long) p->HeapSize;
            break;


        case 24:
            return (unsigned long) p->HeapPointer;
            break;

        case 25:
            return (unsigned long) p->HeapLastValid;
            break;

        case 26:
            return (unsigned long) p->HeapLastSize;
            break;

        case 27:
            return (unsigned long) p->Stack;
            break;
           
        case 28:
            return (unsigned long) p->StackEnd;
            break;


        case 29:
            return (unsigned long) p->StackSize;
            break;

        case 30:
           return (unsigned long) p->StackOffset;
           break;


        case 31:
            return (unsigned long) p->iopl;
            break;
           
        case 32:
            return (unsigned long) p->base_priority;
            break;
           
        case 33:
            return (unsigned long) p->priority;
            break;

        case 34:
            return (unsigned long) p->step;
            break;


        case 35:
            return (unsigned long) p->quantum;
            break;

        case 36:
            return (unsigned long) p->timeout;
            break;
           
           
        case 37:
            return (unsigned long) p->ticks_remaining;
            break;

        case 38:
            return (unsigned long) p->profiler_percentage_running;
            break;
           
           
        case 39:
            return (unsigned long) p->profiler_ticks_running;
            break;

        case 40:
            return (unsigned long) p->profiler_last_ticks;
            break;

        case 41:
            return (unsigned long) p->threadCount;
            break;

        case 42:
            return (unsigned long) p->bound_type;
            break;

        case 43:
            return (unsigned long) p->preempted;
            break;

        case 44:
            return (unsigned long) p->saved;
            break;

        case 45:
            return (unsigned long) p->PreviousMode;
            break;


        case 46:
            return (unsigned long) p->wait4pid;
            break;

        case 47:
            return (unsigned long) p->exit_code;
            break;

        case 48:
            return (unsigned long) p->signal;
            break;
           
        case 49:
            return (unsigned long) p->umask;   //signal_mask;
            break;

        case 50:
            return (unsigned long) p->dialog_address;
            break;
           
        // Image size.
        // Isso � importante.
        case 51:
            return (unsigned long) p->ImageSize;
            break;
           
        // #todo:
        // Precisamos da quantidade de p�ginas usadas.
    
        // ...
    };
    
    return 0;
}



//pega o nome do processo.
int getprocessname ( int pid, char *buffer ){

    struct process_d *p;

    char *name_buffer = (char *) buffer;

    //#todo
    //checar validade dos argumentos.
 
    p = (struct process_d *) processList[pid]; 

    if ( (void *) p == NULL ){
        //todo: message
        return -1;
    }else{
    
        if ( p->used != 1 || p->magic != 1234 )
        {
            //todo message
            return -1;
        }
        
        // 64 bytes
        strcpy ( name_buffer, (const char *) p->__processname );  
        
        return (int) p->processName_len;
    };

    return -1;
}



/*
 *******************************
 * processObject:
 * 
 *     Cria uma estrutura do tipo processo, mas não inicializada.
 *     #todo: Criar a mesma rotina para threads e janelas.
 */

struct process_d *processObject (void){

   struct process_d *tmp;

    tmp = (void *) kmalloc ( sizeof(struct process_d) );

    if ( (void *) tmp == NULL ){
        panic ("ps-processObject: tmp");
    }

    return (struct process_d *) tmp;
}


/*
 * getNewPID:
 *     Pegar um slot vazio na lista de processos.
 *     +Isso pode ser usado para clonar um processo.
 */

// Começaremos a busca onde começa o range de IDs 
// de processos de usuário.
// Se encontramos um slot vazio, retornaremos o índice.
 
pid_t getNewPID (void){

    struct process_d *p;

    int i = USER_BASE_PID;

    while ( i < PROCESS_COUNT_MAX ){

        p = (struct process_d *) processList[i];

        if ( (void *) p == NULL ){
            return (pid_t) i;
        }

        i++;
    };

    debug_print ("getNewPID: fail\n");

    return (pid_t) (-1);
}


/*
 * processTesting:
 *     Testando se o processo � v�lido. Se for v�lido retorna 1234.
 *     @todo: repensar os valores de retorno. 
 * system call (servi�o 88.)
 */

int processTesting (int pid){
	
	struct process_d *P;
	
	P = (void *) processList[pid];
	
	if ( (void *) P == NULL )
	{
		return 0;
		
	}else{		
		
		if ( P->used == 1 && P->magic == 1234 )
		{
			// magic.
	        return (int) 1234;
		}
	};
	
	// Fail.
	
	return 0;
}


/*
 * processSendSignal:
 *     Envia um sinal para um processo.
 *     Se o sinal e o processo forem v�lidos, um sinal � colocado
 * no PCB do processo.
 *     @todo: Rotinas envolvendo sinais devem ir para outro arquivo.
 */

int processSendSignal (struct process_d *p, unsigned long signal){
	
	//SIGNAL_COUNT_MAX
	
	//Limit
    //if(signal >= 32){
	//	return 1;
	//}
	
	if (signal == 0)
	{
		return 1;
	}
	
	//struct fail
	//if( (void*) p == NULL ){
	//	return 1;
	//}		
	
//ok:	
	//Ok
	if ( (void*) p != NULL )
	{	
		p->signal = (unsigned long) signal;
		return 0; //(int) signalSend(p,signal);
	}
	
	//...
	
//fail:
	
	return 1;
}


/*
 ****************************
 * processCopyMemory:
 * 
 *     Copia a imagem de um processo.
 *     Isso é usado na implementação de fork() e
 * na implementação da rotina de clonagem.
 *     Isso é usado por clone_and_execute_process()
 */

// O que copiar?
// >> code, data, bss, heap and stack.
// For now, all the processes has 4MB,
// and the stack begins at CONTROLTHREAD_STACK.
// We just use the control thread.

// #bugbug
// Imagem com limite de 200KB. (fail)
// heap ?? Depois              (fail)
// Stack de 32KB.              (ok)
// 

int processCopyMemory ( struct process_d *process ){

    unsigned long __new_base=0;    // base
    unsigned long __new_stack=0;   // stack


    if ( (void *) process == NULL ){
        printf ("processCopyMemory: process \n");
        refresh_screen();
        return (int) (-1);
    }


    //
    // Image base.
    //

    // #bugbug
    // Precisamos de memória física para a imagem e para a pilha.
    // 4mb de memória física nos permite criarmos um processo
    // com sua pilha no topo dos 4mb.
    // Por isso que precisamos de um alocador de frames,
    // que considere a memória ram inteira.
    // E precisamos de uma rotina que mapeie esses frames individualmente,
    // mesmos que eles sejam pegos esparçamente.

    // #bugbug
    // Esse alocador abaixo está limitado à uma região de 4MB,
    // previamente mapeado.

    // #obs:
    // A não ser que a pilha possa ficar em endereço
    // virtual aleatório.
    // Me parece que endereço virtual aleatório é
    // usado por questão de segurança.
    // Podemos tentar usar pilha com endereço virtual aleatório.

    // 200 KB.   200kb/4096 =  quantidade de páginas.
    // Allocating memory for the process's image.
    // #todo: We need this size.
    // 1024*200 = 200k
    // 50 páginas.
    
    // Retorna um endereço virtual.
    // Mas usaremos apenas o endereço físico extraído desse endereço.
    __new_base = (unsigned long) allocPages ( (1024*200)/4096 ); 

    if ( __new_base == 0 ){
        printf ("processCopyMemory: __new_base fail\n");
        refresh_screen();
        return (int) (-1);
    }


    //
    // Image stack
    //

    // 32 KB.
    // Allocating memory for the process's stack.
    // #todo: We need this size.

    // Retorna um endereço virtual.
    // Mas usaremos apenas o endereço físico extraído desse endereço.
    
    __new_stack = (unsigned long) allocPages ( (1024*32)/4096 ); 

    if ( __new_stack == 0 ){
        printf ("processCopyMemory: __new_stack fail\n");
        refresh_screen();
        return (int) (-1);
    }



    //
    // Copying memory.
    //

    // Copying base and stack.
    // Copiando do processo atual para o buffer que alocamos
    // logo acima.

    // Copia do início da imagem. 200KB.
    memcpy ( (void *) __new_base,  
        (const void *) CONTROLTHREAD_ENTRYPOINT, 
        ( 1024 * 200 ) );
    
    // Copia do fim da stack. 32KB.
    memcpy ( (void *) __new_stack, 
        (const void *) ( CONTROLTHREAD_STACK-( 1024*32 ) ), 
        ( 1024 * 32 ) );


    // Getting the physical addresses.
    // Obtendo o edereço físico da base da imagem e da pilha.
    unsigned long new_base_PA = (unsigned long) virtual_to_physical ( __new_base, gKernelPageDirectoryAddress ); 
    unsigned long new_stack_PA = (unsigned long) virtual_to_physical ( __new_base, gKernelPageDirectoryAddress ); 

    // #todo
    // Agora temos que fazer esses endereços físicos serem
    // mapeados em 0x400000 do diretório de páginas do processo filho.
    // Lembrando que o diretório de páginas do processo filho
    // será uma cópia do diretório do processo pai.
    // Como a cópia do diretórios anda não foi feita,
    // vamos salvar esses endereços para mapearmos depois.

    // virtual
    // Esse endereço virtual não nos server mais.
    // precisamos substituir pelo endereço virtual padrão 
    // para aplicativos. Faremos isso em clone.c quando retornarmos.
    process->childImage  = (unsigned long) __new_base;
    process->childStack  = (unsigned long) __new_stack;

    // físico.    
    process->childImage_PA = (unsigned long) new_base_PA;
    process->childStackPA  = (unsigned long) new_stack_PA;

    //#debug
    //printf ("new_base_PA=%x  \n", new_base_PA );
    //printf ("new_stack_PA=%x  \n", new_stack_PA );

// Done.
	
	//#debug
	//printf ("processCopyMemory: ok\n");
	//refresh_screen ();

    return 0;
}


/*
 ****************************************
 * processCopyProcess
 * 
 *     + Copia os elementos da estrutura de processo.
 *     + Cria um diret�rio de p�ginas e salva os endere�os 
 *       virtual e f�sico dele na estrutura de processo.
 *
 *     Isso � chamado por do_fork_process.
 */
 
// 1 = atual.
// 2 = clone. 
 
int processCopyProcess ( pid_t p1, pid_t p2 ){

    struct process_d *Process1;
    struct process_d *Process2;
    
    int Status=0;
    int i=0;



    if ( p1 < 0 ){
        printf ("processCopyProcess: p1 limits\n"); 
        goto fail;
    }

    if ( p2 < 0 ){
        printf ("processCopyProcess: p2 limits\n"); 
        goto fail;
    }

    if ( p1 == p2 ){
        printf ("processCopyProcess: same PID\n"); 
        goto fail;
    }

    // ===========================
    // Check process 1.
    Process1 = (struct process_d *) processList[p1];

    // Check Process1
    if ( (void *) Process1 == NULL ){
        printf ("processCopyProcess: Process1\n");
        goto fail;

    }else{

        if ( Process1->used != 1 || Process1->magic != 1234 )
        {
           printf ("processCopyProcess: Process1 validation \n");
           goto fail;
        }
    };

    // ===========================
    // Check process 2.
    Process2 = (struct process_d *) processList[p2];

    if ( (void *) Process2 == NULL ){
        printf ("processCopyProcess: Process1\n");
        goto fail;
    
    }else{

        if ( Process2->used != 1 || Process2->magic != 1234 )
        {
           printf ("processCopyProcess: Process2 validation \n");
           goto fail;
        }
    };


    //
    // Copy.
    //

    // Object.
    Process2->objectType  = Process1->objectType;
    Process2->objectClass = Process1->objectClass;

    // O clone não inicializa na seção crítica, pois senão teríamos
    // dois processos na sessão crítica.
    Process2->_critical = 0;

    // Identificadores.
    Process2->pid  = (pid_t) p2;             // PID.  O pid do clone.
    Process2->ppid = (pid_t) Process1->pid;  // PPID. O parent do clone é o pid do pai. 
    
    Process2->uid   = (uid_t) Process1->uid;   // UID. 
    Process2->euid  = (uid_t) Process1->euid;  // EUID. 
    Process2->ruid  = (uid_t) Process1->ruid;  // RUID. 
    Process2->suid  = (uid_t) Process1->suid;  // SUID. 
    
    
    Process2->gid   = (gid_t) Process1->gid;   // GID. 
    Process2->egid  = (gid_t) Process1->egid;  // EGID. 
    Process2->rgid  = (gid_t) Process1->rgid;  // RGID. 
    Process2->sgid  = (gid_t) Process1->sgid;  // SGID. 
    
    Process2->pgrp = Process1->pgrp;



    // validation.
    Process2->used = Process1->used;
    Process2->magic = Process1->magic;

    // State of process
    Process2->state = Process1->state;  

    // Plano de execução.
    Process2->plane = Process1->plane;

	//Process->name_address = NULL;

    Process2->framepoolListHead = Process1->framepoolListHead;


	//
	// Directory
	//

	// #bugbug
	// Precisamos clonar o diret�rio de p�ginas
	// sen�o alguma altera��o feita na pagetable da imagem pode
	// corromper o processo que est� sendo clonado.

    // #importante:
    // Deve retornar o endere�o do diret�rio de p�ginas criado,
    // que � um clone do diret�rio de p�ginas do kernel.
    // Retornaremos o endere�o virtual, para que a fun��o create_process 
    // possa usar tanto o endere�o virtual quanto o f�sico.

	// #bugbug
	// Na verdade precisamos clonar o diret�rio do processo e n�o o 
	// diret�rio do kernel.

	// #importante
	// Isso clona o diret�rio de p�ginas do kernel. Isso facilita as coisas.
	// Retorna o endere�o virtual do novo diret�rio de p�ginas.

	// #importante:
	// Vamos converter porque precisamos de endere�o f�sico para colocarmos no cr3.
	// Mas o taskswitch faz isso pegando o endere�o que estiver na thread, ent�o
	// esse endere�o precisa ir pra thread.

    Process2->DirectoryVA = (unsigned long) CloneKernelPageDirectory();

    if ( (void *) Process2->DirectoryVA == NULL ){
        panic ("processCopyProcess: CloneKernelPageDirectory fail");
    }

    Process2->DirectoryPA = (unsigned long) virtual_to_physical ( Process2->DirectoryVA, 
                                                gKernelPageDirectoryAddress ); 


    // #bugbug
    // Lembrando que na rotina de fork() nos obtemos
    // os endereços físicos da imagem do clone e de sua pilha.
    // precisamos mapear esses endereços em 0x400000, caso contrário
    // o processo filho apontará para a imagem do processo pai,
    // como estava antes de copiarmos o diretório de páginas do kernel.


	// ??
	// #bugbug
	// Se o endere�o for virtual, ok fazer isso. 
	// Usaremos o mesmo endere�o virtual da imagem.
	// #importante: se bem que esse endere�o virtual de imagem
	// pode ser diferente para o kernel. Pois no momento
	// que ele alocar mem�ria para a imagem ele ter� o
	// endere�o l�gico retornado pelo alocador.

    // #bugbug
    // Conseguimos o endere�o da imagem copiada,
    // mas teremos que refazer isso mais a frente quando
    // carregarmos, (isso no caso da rotina de clonagem)
    // Isso � v�lido s� para o fork.

    // Atenção
    // O processo pai armazenava o  novo endereço da imagem do processo
    // filho. Isso foi criado durante a alocação de memória
    // para o processo filho.
    // porém esse endereço virtual não aponta para o 
    // entry point da imagem do processo filho, e sim para
    // o endereço virtual obtido na alocação.



    Process2->Image    = Process1->childImage; // #bugbug: Esse endereço não é 0x400000
    Process2->ImagePA  = Process1->childImage_PA;
    Process2->childImage    = 0;
    Process2->childImage_PA = 0;



    //heap
    Process2->Heap = Process1->Heap;    
    Process2->HeapEnd = Process1->HeapEnd; 
    Process2->HeapSize = Process1->HeapSize;

    //stack
    Process2->Stack = Process1->Stack;   
    Process2->StackEnd = Process1->StackEnd; 
    Process2->StackSize = Process1->StackSize;
    Process2->StackOffset = Process1->StackOffset;


    Process2->iopl = Process1->iopl;

    Process2->base_priority = Process1->base_priority;
    Process2->priority      = Process1->priority;


    // =============
    // #IMPORTANTE
    // Herdar todos arquivos.
    // #bugbug: 
    // Lembrando que o fd 1 tem sido usado como dispositivo 
    // console virtual.
    
    // #bugbug
    // Imagine um processo que fechou um dos três arquivos e agora
    // vamos clonar sem o fluxo padrão em ordem.
    file *__f;

    for (i=0;i<32;i++)
    {
        // Copy
        Process2->Objects[i] = Process1->Objects[i];
        
        // Updating the referency counter.
        // ??limits
        __f = (void*) Process2->Objects[i];
        if((void*)__f!= NULL)
            __f->counter++;
    }

    // O fluxo padrão foi criando antes em klib/kstdio.c
    // #todo: Checar as características desses arquivos.
    Process2->Objects[0] = (unsigned long) stdin;
    Process2->Objects[1] = (unsigned long) stdout;
    Process2->Objects[2] = (unsigned long) stderr;


	//
	// ========================
	// Thread de controle
	//


	// Vamos clonar a thread de controle do processo pai.
	
	// obs:
	// Me parece que a fun��o que clona apenas a thread de controle 
	// chama-se fork1. #todo
	
	// #todo: Precisamos copiar todas as threads
	// vamos come�ar pela thread de controle.
	// teoriacamente elas precisam ter o mesmo endere�o virtual ...
	// mas est�o em endere�os f�sicos diferentes.
	// #bugbug precisamos clonar a thread.
	
	// ############### #IMPORTANTE #################
	// #bugbug
	// Ainda n�o temos um salvamento de contexto apropriado para essa system call.
	// S� o timer tem esse tipo de salvamento.
	// Precisamos salvar o contexto antes de chamarmos o servi�o fork()
	// Pois se n�o iremos retomar a thread clone em um ponto antes de 
	// chamarmos o fork, que � onde est� o �ltimo ponto de salvamento.


    // Clonando a thread de controle.
    // obs: Isso precisa funcionar direito. Não podemos ficar sem isso.
    // See: thread.c
    
    Process2->control = (struct thread_d *) threadCopyThread( Process1->control );

    if ( (void *) Process2->control == NULL ){
        panic ("processCopyProcess: threadCopyThread fail");
    }



    //
    // Directory.
    //

	// #importante
	// Um diret�rio de p�ginas para a thread de controle.
	// O diret�rio de p�ginas da thread de controle ser� o mesmo
	// do processo.
	// � importante deixarmos esse endere�o na estrutura da thread, pois
	// � a� que o taskswitch espera encontra-lo.


    Process2->control->DirectoryPA = Process2->DirectoryPA;


    Process2->control->ownerPID = Process2->pid;


	//?? herda a lista de threads ??
    Process2->threadListHead = Process1->threadListHead;

    Process2->zombieChildListHead = Process1->zombieChildListHead;

    Process2->dialog_address = Process1->dialog_address;

    //#bugbug
    //deleta isso.
	//message support.
    //Process2->window = Process1->window;    //arg1. 
    //Process2->msg    = Process1->msg;       //arg2.
    //Process2->long1  = Process1->long1;     //arg3.
    //Process2->long2  = Process1->long2;     //arg4.


    /*
    //++
    // tty support
    Process2->tty = ( struct tty_d *) tty_create ();  
       
    if ( (void *) Process2->tty == NULL ){
         panic ("processCopyProcess: Couldn't create tty\n");
    }
    tty_start (Process2->tty);
    //--
    */
    
    // #test
    // No caso da clonagem, vamos herdar a tty,
    // talvezz isso facilite a comunicação.
    
    Process2->tty = Process1->tty;


    Process2->exit_code = Process1->exit_code;

    Process2->prev = Process1->prev; 
    Process2->next = Process1->next; 

    Status = 0;
    goto done;



fail:
    Status = 1;
    printf ("processCopyProcess: fail\n");


done:
    return (int) Status;
}


/*
 ******************************************************
 * create_process:
 *     Cria process para ring 3.
 *     Preenche o PCB (Process Control Block).
 *
 * @todo: 
 *     Um processo na verdade inclui tudo sobre a tarefa,
 *     Desde o nome do arquivo at� o carregamento, registro e execu��o.
 *
 * Obs:
 *     Um job � um conjunto de processos.
 *     Tudo depende do tipo (funcionalidade): 
 *     SYSTEM, PERIODIC, ROUND_ROBIN, IDLE.
 *
 *    Classes de processos (tipo de n�vel):
 *
 *    PB - Processos inclu�dos no Kernel Base.
 *    P0 - Processos em ring0.
 *    P1 - Processos em ring1.
 *    P2 - Processos em ring2.
 *    P3 - Processos em ring3, User Mode.
 *
 * @todo: 
 * Esse fun��o deve chamar uma rotina de cria��o de diret�rio. 
 * Quando um processo � criado deve-se criar o seu diret�rio e criar 
 * as pagetables que o processo vai usar de acordo com o tamanho do 
 * processo. 
 *
 * @todo: processCreateProcess(...)
 *
 * @todo: 
 * Aumetar o n�mero de argumentos para dar o suporte necess�rio para 
 * criar um processo do jeito que for necess�rio
 */

// Cria uma estrutura de processo.
// Cria uma tty pra esse processo.

struct process_d *create_process ( 
    struct room_d *room,
    struct desktop_d *desktop,
    struct window_d *window,
    unsigned long base_address, 
    unsigned long priority, 
    int ppid, 
    char *name, 
    unsigned long iopl,
    unsigned long directory_address )
{

    pid_t PID;
    struct process_d *Process;
    

    // Para a entrada vazia no array de processos.
    struct process_d *Empty; 
    
    int i=0;
    
    debug_print ("process-create_process: It's a work in progress!\n");

	// @todo:
	// Melhorar esse esquema de numera��o e 
	// contagem de processos criados.
	// processNewPID � global ?

    if ( processNewPID < USER_BASE_PID || processNewPID >= PROCESS_COUNT_MAX )
    {
        processNewPID = (int) USER_BASE_PID;
    }



    //
    // Process.
    //

    Process = (void *) kmalloc ( sizeof(struct process_d) );

	// #todo: 
	// Aqui pode retornar NULL.
    if ( (void *) Process == NULL ){
        panic ("process-create_process: Process");
    }



	// Loop.
	// #BugBug: 
	// Isso pode virar um loop infinito.

get_next:


/*
	i++;
	
	if ( i >= PROCESS_COUNT_MAX )
	{
		// #bugbug: 
		// Isso deixa o sistema devagar caso n�o apare�a 
		// a mensagem.
		
		printf("pc-process-create_process: End of list");
        refresh_screen();
		
		return NULL;
		//while(1){}
	};
	
*/



	// Get empty.
	// Obt�m um �ndice para um slot vazio na lista de processos.

    PID = (int) processNewPID;  // deletar!!
    
    PID = (int) getNewPID ();

    // #todo: Limits. Max ?
    
    if ( PID == -1 || PID == 0 ){
        printf ("create_process: getNewPID fail %d \n", PID);
        refresh_screen ();
        return NULL;
    }



	//Se o slot estiver ocupado tentaremos o pr�ximo.
	//Na verdade podemos usar aquela fun��o que procura por um vazio. 


    Empty = (void *) processList[PID];

    if ( (void *) Empty != NULL )
    {
        goto get_next;

    }else{

        // Object.
        Process->objectType = ObjectTypeProcess;
        Process->objectClass = ObjectClassKernelObjects;

        //Validation.
        Process->used = 1;
        Process->magic = 1234;


        processNewPID = (int) PID;
        
		// Identificadores.
		// PID. PPID. UID. GID.

        Process->pid  = (int) PID; 
        Process->ppid = (int) ppid; 
        Process->uid  = (int) GetCurrentUserId (); 
        Process->gid  = (int) GetCurrentGroupId (); 
        // ...
        

        // sessão crítica.
        Process->_critical = 0;

		//State of process

        Process->state = INITIALIZED;  

		//@TODO: ISSO DEVERIA VIR POR ARGUMENTO
        Process->plane = FOREGROUND;

		//Error.
		//Process->error = 0;

		//Name.
		Process->name = (char *) name; //@todo: usar esse.
		//Process->cmd = NULL;  //nome curto que serve de comando.
        //Process->pathname = NULL;
        
        
        //#test
        //64 bytes m�x.
        strcpy ( Process->__processname, (const char *) name); 
        

		// Lista de streams ...
		// Zerando essa lista e criando 3 streams para o processo.
		// Mas vamos improvisar e usar os ponteiros do kernel.
		
        //for ( i=0; i< NUMBER_OF_FILES; i++ ){
            //Process->Streams[i] = 0;
        //}

        //Process->Streams[0] = (unsigned long) stdin;
        //Process->Streams[1] = (unsigned long) stdout;
        //Process->Streams[2] = (unsigned long) stderr;

        // #todo
        // Podemos colocar 3 arquivos em Objects[]
        // Ou seriam tty ? 

        // Limpando todos slots.
        for ( i=0; i<32; i++ ){ Process->Objects[i] = 0; }

        if ( (void *) stdin == NULL ){
            panic ("create_process: [TEST] stdin");
        }

        if ( (void *) stdout == NULL ){
            panic ("create_process: [TEST] stdout");
        }
        
        if ( (void *) stderr == NULL ){
            panic ("create_process: [TEST] stderr");
        }
        
        // #bugbug
        // precisamos colocar os arquivos também na lista
        // global de arquivos abertos. openfileList[]
        // See: fs.c
     
        // O fluxo padrão foi criando antes em klib/kstdio.c
        // #todo: Checar as características desses arquivos.
        Process->Objects[0] = (unsigned long) stdin;
        Process->Objects[1] = (unsigned long) stdout;
        Process->Objects[2] = (unsigned long) stderr;


		//Process->terminal =

		//
		//    ****  Banco de dados ****
		//

		//bancos de dados e contas do processo.
		//Process->kdb =
		//Process->gdbListHead =
		//Process->ldbListHead =
		//Process->aspaceSharedListHead =
		//Process->aspacePersonalListHead =
		//Process->dspaceSharedListHead =
		//Process->dspacePersonalListHead =
		
		// Inicializando a lista de framepools do processo.
		// @todo: Todo processo deve ser criado com pelo menos um 
		// frame pool, o que � equivalente a 4MB. (uma parti��o)
		// Obs: Um framepool indica onde � a �rea de mem�ria fisica
		// que ser� usada para mapeamento das p�ginas usadas pelo processo.

        Process->framepoolListHead = NULL;

		//Thread inicial.
		//Process->thread =
		
		//Process->processImageMemory =
		//Process->processHeapMemory =
		//Process->processStackMemory =
		
	    // ORDEM: 
		// O que segue � referenciado durante o processo de task switch.

		// Page Directory: 
		//     Alocar um endere�o f�sico para o diret�rio de p�ginas do 
		// processo a ser criado, depois chamar a fun��o que cria o diret�rio.
		//
		// @todo:
		// *IMPORTANTE: Por enquanto os processos s�o criadas usando o 
		// diret�rio de p�ginas do processo Kernel. Mas temos que criar 
		// um diret�rio novo pra cada processo criado.
		// O diret�rio de todos os processos de usu�rio ser�o iguais. 
		// Ter�o uma �rea de us�rio particular e uma �rea compartilhada 
		// em kernel mode.
		//
		//@todo: Alocar um endere�o f�sico antes, depois chamar a fun��o que 
		// cria o pagedirectory.
		//@todo: 
        //op��o: KERNEL_PAGEDIRECTORY; //@todo: Usar um pra cada processo.

		// #obs:
		// Vari�vel recebida via argumento.

        if (directory_address == 0)
        {
            printf ("create_process: page directory address fail\n");
            return NULL;
        }

        Process->DirectoryVA = (unsigned long ) directory_address;
        Process->DirectoryPA = (unsigned long) virtual_to_physical ( directory_address, 
                                                   gKernelPageDirectoryAddress );

		// cancelados. 
		// Process->mmBlocks[32]
		// Process->mmblockList[32]
		
		
		// Process->processMemoryInfo
		
		
		// #todo: 
		// Precisa alocar espa�o na mem�ria f�sica.
		// Precisa criar page tables para essas areas de cada processo.
		// Os endere�os virtuais dessas areas dos processos s�o sempre os mesmos.
		// mas os endere�os f�sicos dessas areas variam de processo pra processo.

		// Imagem do processo.
		// ?? Provavelmente esse endere�o � virtual.
		// Queremos que esse endere�o seja padronizado e que todos 
		// os processos usem o mesmo endere�o.
		
		// #bugbug
		// Todos os processos de usu�rio come�am no mesmo endere�o virtual.
		// Por�m temos os processos em kernel mode e os processos do gramado core
		// que usam endere�os virtuais diferentes.
		// #todo: Rever isso.
		// #todo: estamos suspendendo essa informa��o.
		
		//
		// # IMPORTANTE 
		//
		
		// Base da imagem do processo.
		// Na verdade precisamos aceitar o endere�o passado via 
		// argumento, pois nem todos processos come�am no endere�o 
		// default.

        // Endere�o virtual e endere�o f�sico.
        Process->Image = base_address;  
        Process->ImagePA = (unsigned long) virtual_to_physical ( Process->Image, 
                                               gKernelPageDirectoryAddress ); 
                                               
        
        // Endere�o virtual e endere�o f�sico de um processo filho.
        // Isso � usado durante a clonagem.
        Process->childImage = 0;
        Process->childImage_PA = 0;


        // #todo
        // Precisamos saber o tamanho da imagem do processo para
        // calcularmos quantas p�ginas ele vai usar.
        // Precisamos dividir a imagem em code, data, heap e stack
        // Pois a �rea de dados poder� sofrer swap.

		// Tamanho da imagem do processo.
		// Temos que chamar a fun��o que pega o tamanho de um arquivo,
		// #bugbug: Porem, no momento o kernel n�o consegue ler arquivos
		// que est�o em subdiret�rios corretamente e os programas est�o 
		// em subdiret�rios.
		// #obs: O tamanho tamb�m poderia ser passado por arguemento.
		// #ou um argumento com ponteiro pra estrutura de informa��o 
		// sobre uma imagem.
        Process->ImageSize = 0;

		//#todo: estrutura com informa��es sobre a imagem do processo.
        Process->image_info = NULL;

		// Heap e Stack:
		//
		// @todo: #BugBug 
		// O Heap e a Stack devem estar dentro da �rea de mem�ria do processo.
		// Uma pagetable do diret�rio � para o heap e outra para a stack.
        // Cada pagetable no diret�rio do processo � pra uma coisa.
        //
		// Obs: O endere�o virtual do heap e da stack dos processos ser�o 
		// os mesmos para todos os processos, assim como o endere�o virtual 
		// de carregamento da imagem.
		
		// Heap and Stack. 
		// #importante: (Endere�os virtuais).
		// Por isso pode ser o mesmo para todos os processos.
		
		
		// #### HEAP ####
		
		// directory va, index, region pa
		//CreatePageTable ( Process->DirectoryVA, 512, 0 );
		
		//Process->Heap = (unsigned long) 0x00400000; //funciona
		//Process->Heap = (unsigned long) 0xC0C00000; //funciona
		
		// g_heappool_va
		// endere�o virtual do pool de heaps.
		// os heaps nessa �rea ser�o dados para os processos.
		// base + (n*size)

        if ( g_heap_count < 0 || g_heap_count >= g_heap_count_max )
        {
            panic ("create_process: g_heap_count limits");
        }

        // #atenção
        // Estamos usando o heappool pra pegarmos esses
        // endereços.
        // me parece que isso é memória compartilhada em ring3
        // e que o malloc da libc está usando isso sem problemas.

        // #todo: 
        // #test: A stack de um process recem criado
        // poderia ficar no fim de seu heap ???

        Process->Heap = (unsigned long) g_heappool_va + (g_heap_count * g_heap_size);
        Process->HeapSize = (unsigned long) g_heap_size;
        Process->HeapEnd = (unsigned long) (Process->Heap + Process->HeapSize); 
        
        g_heap_count++;



		// Endere�o do in�cio da Stack do processo.
		// Endere�o do fim da stack do processo.
		// Tamanho da pilha, dada em KB.
		// #importante: Deslocamento do endere�o do in�cio da pilha em rela��o 
		// ao in�cio do processo. 

        // #bugbug
        // Isso indica que a stack será no endereço virtual tradicional,
        // porém qual é o endereço físico da stack do processo criado
        // com essa rotina.
        // #bugbug: Com esse erro todos os processo criados
        // estão usando a mesma stack, pois todas apontam para o mesmo
        // endereço físico.

        Process->Stack = UPROCESS_DEFAULT_STACK_BASE; 
        Process->StackSize = UPROCESS_DEFAULT_STACK_SIZE; //?? usamos isso na hora de criar a stack?? 
        Process->StackEnd = Process->Stack - Process->StackSize;  
        Process->StackOffset = UPROCESS_DEFAULT_STACK_OFFSET;  //??




		//ring.
        Process->iopl = iopl; 

		//PPL - (Process Permition Level).(gdef.h)
		//Determina as camadas de software que um processo ter� acesso irrestrito.
		//Process->ppl = pplK0;


        //Process->callerq          //head of list of procs wishing to send.
        //Process->sendlink;        //link to next proc wishing to send.
        //Process->message_bufffer  //pointer to message buffer.
        //Process->getfrom_pid      //from whom does process want to receive.
        //Process->sendto_pid       //pra quem.

        //Signal
        //Process->signal = 0;
        //Process->signalMask = 0;

		//cancelada.
		//Process->process_message_queue[8]

		//Outras coisas.
		
		//Prioridade.
        Process->base_priority = (unsigned long) priority;
        Process->priority = (unsigned long)  Process->base_priority;

        //Que tipo de scheduler o processo utiliza. (rr, realtime ...).
        //Process->scheduler_type = ; 

		//Process->step
		//Process->quantum
		//Process->timeout
		//Process->ticks_remaining

		//As threads do processo iniciam com esse quantum.
		//Process->ThreadQuantum   


		//Process->threadCount = 0;    //N�mero de threads do processo.
		
		//Process->tList[32] 
		
		//Lista de threads.
        Process->threadListHead = NULL;

        Process->control = NULL;

        //Process->window_id 


		//Process->event
		

		// #importante
		// user session, room and desktop.

		// #bugbug: 
		// N�o temos informa��o sobre a user session, 
		// devemos pegar a estrutura de current user session. 
		// Para isso ela deve ser configurada na inicializa��o do gws,
		// antes da cria��o dos processo.
		
        Process->usession = CurrentUserSession;  // Current.
        Process->room = room;                    // Passado via argumento.
        Process->desktop = desktop;              // Passado via argumento.

		//Process->base_priority

	
        // wait4pid: 
        // O processo esta esperando um processo filho fechar.
        // Esse � o PID do processo que ele est� esperando fechar.

        Process->wait4pid = (pid_t) 0;
        
        // N�mero de processos filhos.
        Process->nchildren = 0;

        Process->zombieChildListHead = NULL;

        Process->exit_code = 0;

		// ?? 
		// Procedimento eem ring 0 por enquanto.
        Process->dialog_address = (unsigned long) &system_procedure;

        Process->signal = 0;
        Process->umask = 0;

		//
		// Msg
		//

    //#bugbug
    //deleta isso.
		//Msg support.
		//Argumentos do procedimento de janela.
		//@todo: Isso pode ser um ponteiro de estrutura,
		//a fila de mensgens pode ser uma fila de ponteiros.
        //Process->window = NULL;    //arg1. 
        //Process->msg = 0;          //arg2.
        //Process->long1 = 0;        //arg3.
        //Process->long2 = 0;        //arg4.




        // tty support
        
        printf ("create_process: calling tty_create[DEBUG]\n");

        Process->tty = ( struct tty_d *) tty_create ();         
        
        if ( (void *) Process->tty == NULL ){
            panic ("create_process: Couldn't create tty\n");
        }
        tty_start (Process->tty);



        Process->prev = NULL; 
        Process->next = NULL; 

		// List.
		// Coloca o processo criado na lista de processos.

        processList[PID] = (unsigned long) Process;
    };


	// More ?

    return (void *) Process;
}

 
/*
 ************************************************
 * CloseAllProcesses:
 *     Bloqueia todos os processos da lista de processos.
 *     Menos o processo '0'.
 *     processCloseAllProcesses();    
 */

void CloseAllProcesses (void){

    int Index = 0;
    struct process_d *P;

	// #importante:
	// Menos o 0, pois � o kernel. 

    for ( Index = 1; Index < PROCESS_COUNT_MAX; Index++ )
    {
		//Pega, bloqueia e tira da lista.
        P = (void *) processList[Index];
        P->state = PROCESS_BLOCKED;

        processList[Index] = (unsigned long) 0;
    };


	//Check process 0.
    P = (void *) processList[0];

    if ( (void *) P == NULL ){
        panic ("CloseAllProcesses: P\n");
    }
}

// usado pelo comando "current-process" no shell
void show_currentprocess_info (void){

    struct process_d *Current;


    if ( current_process < 0 || current_process >= PROCESS_COUNT_MAX )
    {
        //printf("show_process_information: current_process fail\n");
        return;
    }


	//Struct.
    Current = (void *) processList[current_process];

    if ( (void *) Current == NULL )
    {
        printf ("show_currentprocess_info: struct \n");
        return; 

    } else {

		//Index.
        printf ("PID={%d} PPID={%d} UID={%d} GID={%d} \n",
            Current->pid, Current->ppid, Current->uid, Current->gid );
		//Name
        //printf ("Name={%s} \n", Current->name_address );
        printf ("Name={%s} \n", Current->name );
        
		//Image Address.
        printf ("ImageAddress={%x} \n", Current->Image );

		//Directory Address. *IMPORTANTE.
        printf (">>DirectoryPA={%x} \n", Current->DirectoryPA );
        printf (">>DirectoryVA={%x} \n", Current->DirectoryVA );

		//Heap and stack.
        printf("Heap={%x}  HeapSize={%d KB}  \n", Current->Heap, 
            Current->HeapSize );

        printf("Stack={%x} StackSize={%d KB} \n", Current->Stack, 
            Current->StackSize );

		//...
    };


    refresh_screen ();
}


/*
 * show_process_information:
 *     Mostra informa��es sobre os processos. 
 *     #todo: na verdade um aplicativo em user mode deve fazer esse trabalho
 * solicitando informa��es sobre cada processo atrav�s de chamadas.
 */

// Mostrar informa��es sobre os processos da lista.
// obs: as imagens s�o carregadas em endere�os virtuais diferentes
// e o endere�o mostrado � em rela��o ao diret�rio de p�ginas do kernel
// pois o kernel � que controla o posicionamento das imagens.

void show_process_information (void){

    int i=0;
    struct process_d *p;


    printf ("\n\n show_process_information: \n\n");


    for ( i=0; i<PROCESS_COUNT_MAX; i++ )
    {
        p = (void *) processList[i];

        if ( (void *) p != NULL && 
                      p->used == 1 && 
                      p->magic == 1234 )
        { 

            //printf("\n");
            printf("\n=====================================\n");
            printf(">>[%s]\n",p->__processname);
            printf("PID=%d PPID=%d \n", p->pid,  p->ppid );
            
            printf("image-base =%x image-size =%d \n", p->Image, p->ImageSize );
            printf("heap-base  =%x heap-size  =%d \n", p->Heap, p->HeapSize );
            printf("stack-base =%x stack-size =%d \n", p->Stack, p->StackSize );

            printf("dir-pa=%x dir-va=%x \n", p->DirectoryPA, p->DirectoryVA );

            printf("iopl=%d prio=%d state=%d \n", p->iopl, p->priority, p->state );
        }

		//Nothing.
    };


    //printf ("done\n");
    refresh_screen ();
}


/*
 **************************************************************
 * SetProcessDirectory:
 *     Configura o endere�o do diret�rio de p�ginas do processo.
 *     @todo: Isso pode ser um servi�o oferecido pelo kernel,
 * para um gerenciador de processos em user mode usar.
 * @todo: processSetDirectory(...)
 */

void 
SetProcessDirectory ( struct process_d *process, unsigned long Address )
{
    if ( (void *) process != NULL )
    {
        process->DirectoryPA = (unsigned long) Address;  
    }
}


/*
 ************************************************************
 * GetProcessDirectory:
 *     Pega o endere�o do diret�rio de p�ginas do processo.
 *     @todo: Isso pode ser um servi�o oferecido pelo kernel,
 * para um gerenciador de processos em user mode usar.
 * @todo: processGetDirectory(...)
 */

unsigned long GetProcessDirectory ( struct process_d *process ){

    if( (void *) process != NULL )
    {
		//@todo: checar used e magic.
        return (unsigned long) process->DirectoryPA;
    }


    return (unsigned long) 0;
}


/*
 ****************************************************
 * GetPageDirValue:
 *     Pega o endere�o do diret�rio de p�ginas do processo.
 *     processGetPageDirValue()
 */

unsigned long GetPageDirValue (void)
{
    return (unsigned long ) get_page_dir ();
}



/*
 ***************************************************************
 * init_task:
 *     Inicia um processo.
 *     @todo: Mudar o nome para init_process().
 *            Inicializa a estrutura de um processo criado.
 *            Quando cria o processo, cria apenas sua estrutura,
 *            ficando a cargo dessa rotina inicializar a estrutura criada. 
 */ 

int init_task (int id)
{ 
	//@todo: inicializar uma estrutura para um processo criado.
	//obs: ja tem essa rotina feita em aalgum lugar..
	
    return 0;   
}



/*
 *************************************************************
 * init_tasks: 
 *     Inicia as vari�veis.
 *
 * @todo: 
 *     Bug bug, problemas na inicializa��o das estruturas.
 *     Implementar a aloca��o din�mica na cria��o das tarefas.
 */

//#bugbug
//rever e deletar, se poss'ivel.

//#bugbug
//os conceitos de tasks ainda est�o misturados, hora � thread e hora � processo

void init_tasks (void)
{
    init_processes ();
}


/*
 ***********************************************************
 * init_processes:
 *    Inicaliza o process manager.
 *   #todo: rever esse nome, pois na verdade estamos inicializando variaveis 
 * usadas no gerenciamento de processo.
 */
 
void init_processes (void){
	
    int i;
	
	//
	// Iniciando vari�veis globais.
	//
	
	kernel_request = 0;    // O que fazer com a tarefa atual.
	
	
	// ?? Contagem de tempo de execu��o da tarefa atual.
	//n�o precisa, isso � atualizado pelo request()
	//kernel_tick = 0;                                 

    kernel_switch = 0;     // ?? Ativa o kernel switch do scheduler.

    current_process = 0;


	//
	// Inicializando a lista de processos.
	//

    i=0;

    while (i < PROCESS_COUNT_MAX)
    {
        processList[i] = (unsigned long) 0;
        i++;
    };

    // More ?
}



/*
 ***************************************************
 * exit_process:
 *
 *     Exit process.
 *     Coloca o processo no estado PROCESS_TERMINATED, mas n�o destr�i a 
 * estrutura do processo. Outra rotina destruir� as informa��es.
 *
 * @todo: 
 * Liberar a mem�ria e os recursos usado pelo processo. Ou ainda apenas 
 * sinalizar a flag magic para que o GC a reutilize.
 *
 * @todo: 
 * Fechar as threads seguindo a lista encadeada.
 */

void exit_process ( pid_t pid, int code ){

    struct process_d *Process;
    struct thread_d *__Thread;    
    
    //list;
    struct thread_d *Threads;
    
    struct thread_d *Next;
	//...


    //debug_print ("exit_process:\n");

//#ifdef MK_VERBOSE
	// Debug:
    printf ("exit_process: Terminating process %d\n", pid );
    refresh_screen ();
//#endif


	//Limits. 

    if ( pid < 0 || pid >= PROCESS_COUNT_MAX ){
        debug_print ("exit_process: pid limits\n");
        return;
    }

    //
    // Struct
    // 
	
	// Pega o ponteiro para a estrutura, 
	// muda o c�digo de sa�da e o status.


    Process = (struct process_d *) processList[pid];

    // We can't kill the kernel process.
    if ( Process == KernelProcess ){
        debug_print ("exit_process: We can't kill the kernel process.\n");
        return;
    }

    if ( (void *) Process == NULL ){
        debug_print ("exit_process: Process\n");
        return;
 
    }else{

        if ( Process->used != 1 || Process->magic != PROCESS_MAGIC ){
            debug_print ("exit_process: Validation\n");
            return;
        }


        Process->exit_code = (int) code; 
        Process->state = PROCESS_TERMINATED; 
        
        // #important
        // Isso é para evitar deadlock.
        // Não queremos que um processo feche estando na sua
        // seção crítica.
        process_exit_criticalsection(pid);
        
        // ...
    };


    // #todo
    // Tem que liberar todos os recursos usados pelo processo.
    // >>Streams[]
    // memory ??
    // ...
 

//#ifdef MK_VERBOSE
	//Debug:
	printf ("exit_process: Terminating threads..\n");
	refresh_screen ();
//#endif


    // #obs
    // Acho que ainda n�o estamos usando a lista.
    // Mas podemos ao fim disso deletarmos a thread de controle
    // caso ela ainda exista.

	// Agora temos que terminar as threads que est�o na lista 
	// de threads do processo.
	// Pegaremos a primeira da lista.
	// Se o head da list n�o foi inicializado corretamente 
	// d� page fault.

    __Thread = (void *) Process->threadListHead;

    // Se n�o h� nada na head.
    if ( __Thread == NULL )
    {
		// #todo: 
		// Talvez haja mais o que fazer.
		// Podemos checar se existe uma thread de controle.
  
        goto done;

    }else{
		
		// Ok, se o primeiro da lista � v�lido, podemos 
		// tentar fechar todas.
        // ... 
    };


	// Se a primeira thread da lista � v�lida, 
	// ent�o tentaremos fechar toda a lista.

    while (1)
    {
		// ?? Qual deve fechar depois. ??
		
		printf (".\n");
		refresh_screen ();
		
		// Salva o ponteiro para o pr�ximo thread.
		Next = (void *) __Thread->Next;
		
		// Confere se chegamos ao fim da lista.
		// 'Thread' fecha agora.
		
        if( __Thread == NULL ){
            goto done;

        }else{
    
#ifdef MK_VERBOSE    
		    //fecha a thread.
		    printf ("exit_process: Killing thread %d\n", __Thread->tid );
#endif

            // Kill!
            kill_thread ( __Thread->tid ); 

		    // Prepara qual deve fechar agora.
		    // Hav�amos salvo e agora � vez dela.
		    // Obs: Estamos reusando o ponteiro.

            __Thread = (void *) Next;
        };
        // Nothing.
    };

	//nothing

done:
	
	//@todo:
	//    Escalonar o processo atual. Se o processo fechado foi o processo 
	// atual, precisamos de um novo processo atual. Usaremos o processo zero 
	// por enquanto. Obs: Devemos fazer aqui apenas escalonameto de processo
	// e n�o de thread.	

	//Zerando por enquanto.

	//?? Analizar essa parte.
	//@todo: Select next process (idle)



	// #todo: 
	// chamar o scheduler.
	
	//scheduler ();


    // Current process.
    KernelProcess->state = READY;
    current_process = KernelProcess->pid;

    // Current thread.
    ____IDLE->state = READY;
    current_thread  = ____IDLE->tid;

    return;
}



// ??
int get_caller_process_id (void)
{
    return (int) caller_process_id;
}


// ??
void set_caller_process_id (int pid)
{
    caller_process_id = (int) pid;
}


/*
 *************************************************
 * init_process_manager:
 *     Initialize process manager.
 *     processInitializeProcessManager();
 */

int init_process_manager (void){

    caller_process_id = (int) 0;

    processNewPID = (int) USER_BASE_PID;

	//...

    return 0;
}


/*
 Constructor.
int processmanagerProcessmanager ()
{
}
*/


/*
int processmanagerInit ()
{
};
*/


/*
 * GetProcessHeapStart:
 *     Pega o endere�o do heap do processo.
 */

unsigned long GetProcessHeapStart ( pid_t pid ){

    struct process_d *process;

	//Limits.

    if ( pid < 0 || pid >= PROCESS_COUNT_MAX )
    {
        goto fail; 
    }


    process = (struct process_d *) processList[pid];
    
    if ( (void *) process == NULL )
    {
		goto fail;
		 
    }else{
		
		if ( process->used != 1 || process->magic != 1234 )
		{
			goto fail;
		}
		
		//Ok.
		return (unsigned long) process->Heap;
    };


fail:
	
    return (unsigned long) 0;
}


/*
 * GetProcessPageDirectoryAddress:
 *
 */

unsigned long GetProcessPageDirectoryAddress ( pid_t pid ){

    struct process_d *process;

	//Limits.

    if( pid < 0 || pid >= PROCESS_COUNT_MAX )
    {
        goto fail; 
    }


    process = (struct process_d *) processList[pid];

    if ( (void *) process == NULL )
    {
		goto fail;
		 
    }else{
		
		if ( process->used != 1 || process->magic != 1234 ){
			goto fail;
		}

        return (unsigned long) process->DirectoryPA;
    };


fail:

    return (unsigned long) 0;
}


// Isso vai alterar uma das entradas do diret�rio de p�ginas do processo.
// Criando uma pagetable e mapeando nela 4MB da mem�ria f�sica.
// Usaremos isso para carregar a imagem do programa em 0x400000.
// #bugbug: Na verdade precisamos saber quantas p�ginas o programa precisa.
// e Carregarmos s� as p�ginas que ele precisa, ou menos caso a pagina��o
// por demanda esteja funcionando..

/*
int xxxloadHere4MB ( struct process_d *process, unsigned long region4MB_PA );
int xxxloadHere4MB ( struct process_d *process, unsigned long region4MB_PA )
{
    
    //#todo melhorar esses filtros.
    
    if ( (void *) process == NULL )
        return -1;
    
    if ( region4MB_PA == 0 )
        return -1;
    
    
    // Cria uma pagetable em um dado diret�rio de p�ginas.
    // Uma regi�o de 4MB da mem�ria f�sica � mapeanda nessa pt.
    
    CreatePageTable ( process->DirectoryVA, ENTRY_USERMODE_PAGES, region4MB_PA );
    
    return 0;
}
*/




//#todo
//encontrar um slot vazio em Process->Streams[]
//retornar o indice.
/*
int process_find_empty_stream_slot ( struct process_d *process );
int process_find_empty_stream_slot ( struct process_d *process ){

 	int i = 0;
	
	if ( (void *) process == NULL )
	{
		return -1;
		 
	}else{
		
		if ( process->used != 1 || process->magic != 1234 ){
			
			return -1;
		}
		
	    for ( i=0; i< NUMBER_OF_FILES; i++ )
	    {
	        if ( Process->Streams[i] == 0 )
		    {
		        return i;
		    }
	    }
	};  
	
	return -1;
} 
*/


    
//=============

// Pega uma stream na lista de arquivos dado o fd.


//mudar para: get_file_from_fd
file *get_stream_from_fd ( int pid, int fd )
{
    struct process_d *p;
    file *fp;
    
   

    if ( pid < 0)
        return NULL;


    // Get process pointer.
    p = (struct process_d *) processList[ pid ];

    if (fd<0)
        return NULL;


    // Get fp from list of open files.
    return ( file * ) p->Objects[fd];  
}

//===============
  
  

// #todo: It's a work in progress!  
// cria um novo process, uma thread e carrega a imagem.
// #bugbug: 
// O aplicativo não pode chamar essa rotina e carregar
// em 0x400000, pois ainda estamos usado o diretório de
// de páginas desse aplicativo e ele está nesse endereço.
// #todo: Talvez usar outro alocador e outro endereço
// pra só depois mapear no endereço certo e no diretório certo.

int 
__execute_new_process ( const char *filename, 
                        char *argv[], 
                        char *envp[] )
{
    struct process_d *p;
    struct thread_d *t;
    
    
    debug_print ("process-__execute_new_process: FIXME, it's a work in progress!\n");
    return -1;
    
    
    int __pid = (int) getNewPID ();
    if (__pid < 0){
        panic ("__execute_new_process: pid");
        return -1;
    }
    
    p = (struct process_d *) create_process ( NULL, NULL, NULL, 
                                   (unsigned long) 0x00400000, 
                                   PRIORITY_HIGH, 
                                   __pid,
                                   (char *) filename, 
                                   RING3, 
                                   (unsigned long ) CloneKernelPageDirectory() ); 

    if ( (void *) p == NULL )
    {
		panic ("__execute_new_process: p");
        return -1;
    }
    
    t = (struct thread_d *) sys_create_thread ( 
                                NULL,             // room ? 
                                NULL,             // desktop
                                NULL,             // w.
                                (unsigned long) 0x00401000,                 // init eip
                                (unsigned long) (0x00401000 + (1024*200)),   // init stack
                                __pid,  // pid
                                "new-thread" );    // name

    if ( (void *) t == NULL )
    {
		panic ("__execute_new_process: t");
        return -1;
    }
    
    t->DirectoryPA = p->DirectoryPA;
    
    //load image.

	// loading image.
	
    int fileret = -1;
    
    fileret = (unsigned long) fsLoadFile ( VOLUME1_FAT_ADDRESS, 
                                  VOLUME1_ROOTDIR_ADDRESS, 
                                  (unsigned char *) filename, 
                                  (unsigned long) 0x00400000 );


    if ( fileret != 0 )
    {
        panic ("__execute_new_process: fileret \n");
    }
    
    //t->tss = current_tss;
    SelectForExecution (t);    // >>standby
    
    
    
    printf ("__execute_new_process: done\n");

    //debug
    show_slot (t->tid);
    show_reg  (t->tid);

    printf ("__execute_new_process: *breakpoint { Work in progress } \n");    
    refresh_screen();
    while(1){}
    
    return 0;
    //return __pid;
    //...
}
      
 

// Pega o n�mero da tty de um processo, dado o pid.
int process_get_tty ( int pid )
{
    // Usada para debug.

    
    struct process_d *p;
    struct tty_d *tty;


    //3debug
	//printf ("process_get_tty: pid %d \n", pid);
	//refresh_screen();


    // #todo
    // Overflow ?
    
    if ( pid < 0 )
    {
		//printf ("pid fail\n");
		//refresh_screen();
        return -1;
    }

    p = (struct process_d *) processList[pid];

    if ( (void *) p == NULL )
    {
		//printf ("p fail\n");
		//refresh_screen();
        return -1;
    }

    tty = p->tty;    


    if ( (void *) tty == NULL )
    {
		//printf ("tty fail\n");
		//refresh_screen();
        return -1;
    }


    //printf ("tty %d belongs to %d\n", tty->index, p->pid );
    //refresh_screen ();

    return (int) tty->index;
}                   
                      
 

/*
 *******************************************
 *
 */
 
// IN: name, argv, envp.

int 
process_execve ( const char *arg1, 
                 const char *arg2, 
                 const char *arg3 ) 
{
    int Status = 1;    // fail.

    struct process_d *process;
    struct thread_d *Thread;

	//??
	//Esse � o primeiro argumento.
    int Plane = 0;

    char *s;

	// Usados gerenciamento de arquivo.

    size_t l;                        //lenght.
    char bin_string[] = ".bin";
    //char bin2_string[] = ".BIN";


	//#debug
	//printf("0=%s ",&argv[0]);
	//printf("1=%s ",&argv[1]);


	// #importante
	// Testando carregar um programa para rodar no processo INIT, 
	// usando a thread prim�ria do processo !
	// � o mesmo que consierar que o processo INIT j� seja o clone 
	// de outro v�lido.

	//??
	//array de ponteiros.
    unsigned long *p = (unsigned long *) arg2;

	// #importante:
	// Mem�ria compartilhada entre o kernel e o aplicativo.
	// O aplicativo vai ler esse trem 
    unsigned char *shared_memory = (unsigned char *) (0xC0800000 - 0x100);

	// #IMPORTANTE:
	// PRECISAMOS ENVIAR A MENSAGEM SOMENTE DEPOIS QUE O NOVO PROGRAMA FOR 
	// COLOCADO NA MEM�RIA, SEN�O AO COLOCAR O PROGRAMA NA MEM�RIA A MENSAGEM 
	// SER� SOBRESCRITA.
	// #TODO: CRIAR UM MECANISMO DE TROCA DE MENSAGENS MAIS EFICIENTE,
	// BASEADO NESSE.

	//=================================================
	//  ## CMD ##

	//#importante.
	//antes de tudo vamos testar o comando.
	//se ele n�o existir ent�o nem vamos mexer na estrutura da trhead.
	//se n�o mexermos na estrutura da thread ele continuar� presa no while 
	//do exit da libc.
	
	
	//
	// ## Load file ##
	//
	
	// #bugbug
	// # arg1=name ##
	
	// Devemos ver se a string n�o passa dos limites.

	// Como essa rotina � para executar um arquivo .bin,
	// caso n�o exista uma extens�o .bin e o nome seja menor que 8, 
	// podemos adicionar a extens�o .bin.



    l = (size_t) strlen ( (char *) arg1 ); //ok
    //l = (size_t) strlen ( (char *) &arg1[0] );
    
	printf ("filename %s   \n", &arg1[0] );
	printf ("name size %d  \n", l );

    // O tamanho m�ximo � 12.
    // '8' '.' '3'

    if ( l > 12 )
    {
		printf ("name size %d  \n", l );
        panic ("do_execve: l. The filename is too long ! \n");
        
		// #obs: 
		// N�o sairemos da fun��o pois isso � um teste ainda.
		// goto fail;

    }
    
    // 
    if (l < 9)
    {
		// Se n�o existe um ponto entre os oito primeiros chars,
		// ent�o colocamos a extens�o .bin logo ap�s o nome passado.
		// Ele � pelo menos menor que 11, mas deveria ser menor que oito.

            if ( arg1[0] != '.' && 
                 arg1[1] != '.' && 
                 arg1[2] != '.' && 
                 arg1[3] != '.' && 
                 arg1[4] != '.' && 
                 arg1[5] != '.' && 
                 arg1[6] != '.' && 
                 arg1[7] != '.' )
            {       
                if ( l > 8 )
                {
                    panic ("do_execve: File without ext is too long\n");
                    
					// Obs: 
					// N�o sairemos da fun��o pois isso � um teste ainda.
					// goto fail;
                }

                strcat ( (char *) arg1, (const char *) bin_string );
            };

			// #obs:
			// Se estamos aqui, isso significa existe um ponto 
			// nos primeiros oito bytes.
			// Ainda n�o sabemos se todo o nome do arquivo est� certo,
			// mas ja sabemos que n�o precisamos incluir uma exten��o.
    };


	// #importante
	// Transformando o nome do arquivo em mai�scula, pois estamos 
	// usando FAT16, que exige isso.

    read_fntos ( (char *) arg1 );


    //
    // Searching for the file only on the root dir.
    //
    
    //#todo
    //Testar isso, � mais segura checar se o arquivo existe.
    
    /*
    int __Status = -1;
    __Status = (int) KiSearchFile ( filename, VOLUME1_ROOTDIR_ADDRESS );
    if (__Status == 1){

         //#debug
         //printf("found\n");
    
    }else{
         printf("not found\n");
         goto fail;
    };
     */


	//
	// Load file.
	//

	// #importante:
	// Carregaremos o programa no endere�o l�gico 0x400000, usando o
	// diret�rio de p�ginas do processo kernel.

	// #todo:
	// Nas rotinas de execu��o, temos que usar o diretorio de p�ginas
	// do processo que est� solicitando o carregamento e execu��o.
	// Ou carregarmos em um endere�o f�sico e mapearmos no
	// diret�rio de p�ginas do processo na posi��o 0x400000.

	// #bugbug
	// Esse carregamento � feito usando o diret�rio de p�ginas do kernel,
	// mas o certo � usarmos o diret�rio de p�ginas do processo atual.
	// A quest�o � que sempre carregaremos em endere�os f�sicos diferentes,
	// mas todo diret�rio de p�ginas ter� o mesmo endere�o l�gico.
	// Essa rotina de carregamento tem que usar o endere�o l�gico
	// referente ao endere�o f�sico desejado e esse endere�o l�gico
	// deve pertencer ao diret�rio de p�ginas do kernel.

    process = (struct process_d *) processList[current_process];

    // #todo
    // Precisamos checar a validade da estrutura.

    // #todo
    // Vamos tentar atualizar o nome do processo na estrutura
    // de processo.

    //memcpy (process->name_address, arg1, 11);
    //memcpy (process->name, arg1, 11);
    //process->name = (char *) arg1; 

    Status = (int) fsLoadFile ( VOLUME1_FAT_ADDRESS, 
                       VOLUME1_ROOTDIR_ADDRESS, 
                       (unsigned char *) arg1, 
                       (unsigned long) process->Image );

    if ( Status == 1 )
    {
        printf ("do_execve: Couldn't load file\n");
        goto fail;
    }

	// Check ELF signature.
	// OK. O comando existe e o arquivo foi carregado, mas 
	// precisamos saber se a assinatura de ELF � v�lida.

    Status = (int) fsCheckELFFile ( (unsigned long) process->Image );

    if ( Status == 0 )
    {
        goto format_ok;
    }else{

		// #debug
		panic ("do_execve: It's not a valid ELF file\n");
		//goto fail;
    };


	//
	// ELF Signature OK
	//

format_ok:

	//#debug
	//tentando receber uma linha de ocmando inteira.
	//printf("\nexecutive_gramado_core_init_execve: testing..\n\n");

	// # ISSO DEU CERTO #
	// testando se o shell transferiu toda alinha de comandos para a 
	// mem�ria compartilhada.
	//printf(">>>cmdline2={%s}\n", shared_memory);
	
	//#IMPORTANTE:
	//se a linha de comandos est� na mem�ria compartilhada 
	//e o nome do arquivo programa foi passado via endere�o 
	//ent�o temos tudo o que � preciso 
	//para enviarmos a linha de comandos para o aplicativo.

	//...
	
	
	//## teste
	//
	//if( ! strcmp( (char*)argv[0], "-f" ) ) 
	//if( strncmp( (char*) &argv[1], "-f", 2 ) == 0 )
	//{
	//	printf("executive_gramado_core_init_execve: FOREGROUND\n");
    //    Plane = FOREGROUND;
    //}else{
	//	printf("executive_gramado_core_init_execve: BACKGROUND\n");
	//	Plane = BACKGROUND;
	//};
	
	//fail.
	//if( (const char *) filename == NULL ){
	//	return 1;
	//}
	
	//
	// ENVIANDO A MENSAGEM
	//
	
	//unsigned longs.
	//for( i=0; i<512; i++ )
	//{
        
		//N�o queremos transferir o primeiro ponteiro 
		//pois ele � o nome do programa e n�o um argumento.
	//	shared_p[i] = p[i+1];
		
		//pipe[i] = src[i];
		//shared_memory[i] = src[i];
	//};
	
	//os ponteiros est�o na mem�ria compartilhada, 
	//mas as strings est�o onde ??
	//provavelmente as strings ainda esteja na mem�ria 
	//do shell, e o aplicativo n�o pode ler as strings que est�o 
	//na mem�ria do shell.
	//obs: o shell poderia copiar toda a linha de comando para 
	//a mem�ria compartilhada.
	//printf(">>>shared_p0={%s}\n"     ,shared_p[0]);
	//printf(">>>shared_p1={%s}\n"     ,shared_p[1]);
	//printf(">>>shared_p2={%s}\n\n"   ,shared_p[2]);
	//printf(">>>shared_p3={%s}\n\n"   ,shared_p[3]);
	
 
	//#debug
	//ok. isso funcionou.
	//printf("Showpipe={%s}\n",pipe);
	//printf("Showsharedmemory={%s}\n",shared_memory);
	
	
	// Pegar o ponteiro da thread prim�ria do processo INIT.
    // o ponteiro vai continuar existindo mesmo que o deadthread collector 
	// tenha destruido a estrutura depois de um app mudar o estado para zombie 
	// por causa de um exit.
	//Ent�o � melhor criarmos uma thread nova. Mas se fizermos isso
	//sem antes o deadthread collector ter destruido a estrutua e 
	// liberado a mem�ria 
	//ent�o a antiga estrutura de thread ficar� sem porteiro e poderemos 
	//desalocar a mem�ria 
	//usanda, ou pior, se n�o mudarmos o status ele pode querer destruir a 
	//que estamos criando
	//ent�o s� criaremos se o ponteiro for NULL, significando que o 
	// deadthread collector 
	//ja destruiu a estrutura e aproveitou a mem�ria se conseguiu.

	//#importante:
	//Podemos eswperar que essa thread esteja no estado ZOMBIE.
	//Pois um aplicativo pode ter efetuado um exit.
	//se ela estiver no estado ZOMBIE
	
	// #importante
	// Esperamos que tenha limpado InitThread antes de usarmos o ponteiro.
	// Isso � trabalho do exit e do deadthread collector.
	
	// #bugbug
	// Esse ponteiro ode dar problemas.
	
	/*
	if ( i == 216 )
	{
		printf ("do_execve: ClonedThread \n");
	    Thread = (struct thread_d *) ClonedThread; 
	}else{
		printf ("do_execve: InitThread \n");
	    Thread = (struct thread_d *) InitThread;
	}
    */




	//
	// Current Thread.
	//

	// #obs
	// A thread que chamou essa rotina deve ser a current_thread. 
	// Certo ?
	// +N�o podemos retornar para ela ap�s essa chamada. 
	// +Devemos reinicializar a thread ou fazermos um spawn.
	// #bugbug: Perderemos a pilha salva na chamada.
	// #bugbug: Se retornarmos teremos problema pois a thread foi 
	// alterada.
	// S� nos resta reinicializarmos a thread atual e rodarmos ela.

    Thread = (struct thread_d *) threadList[current_thread];

    if ( (void *) Thread == NULL )
    {
        panic ("do_execve: Thread fail\n");
		//goto fail;
    }else{

		// #importante:
		// N�o podemos voltar para essa trhead.

		// #importante:
		// Checar a flag de reaproveitamento.
		// Se a flag do reaproveitamento falhar ent�o o exit no kernel
		// n�o acionou ela para a threa InitThread, que � nossa �nica reaproveit�vel.
		// por enquanto.
		
		//if ( Thread->used != 1 || Thread->magic != 1234 )
		//{
		//	printf("executive_gramado_core_init_execve: Validation fail \n");
		//	die();
			//goto fail;
		//}


		//
		// ## state ##
		//

		// Vamos seguir a sequ�ncia de nacimento de um thread e 
		// cancelaremos, caso n�o for poss�vel carregar o arquivo do programa.
		// INITIALIZED >> STANDBY >> READY >> RUNNING ...

        Thread->state = INITIALIZED;

		// '0'. Significa que o contexto nunca foi salvo, pois o spawn 
		// n�o funciona em thread com o contexto salvo.

        Thread->saved = 0; 

		// ??
		// Plano. bg/fg.

        Thread->plane = Plane;

		//#test
		// Vamos associar ao primeiro tty, mesmo que seja um aplicatibo GUI.
		// Se ele for um aplicativo GUI ele ir� atualizar o foco.
		// Se for um aplicativo de terminal ent�o ter� uma janela 
		// para rodar. Pois o ldisc manda mensagens para a thread de controle 
		// da janela com foco de entrada. Vamos fazer isso manualmente.

        if ( (void *) CurrentTTY != NULL )
        {
            if ( CurrentTTY->used == 1 && CurrentTTY->magic == 1234 )
            {
                current_tty = CurrentTTY->index;

                Thread->tty_id = current_tty;

				// #terminal window.
                window_with_focus = CurrentTTY->window->id;
                terminal_window = CurrentTTY->window->id;

				//#importante
				//a thread de controle da janela, para qual
				//ser�o enviadas as mensagens pelo ldisc
                CurrentTTY->window->control = Thread;
            }

        }else{
            //Thread->tty_id = 0; //-1
        };

		// Context.
		// #todo: 
		// Isso deve ser uma estrutura de contexto.

		// Stack frame.

        Thread->ss = 0x23; 
        //Thread->esp = (unsigned long) 0x0044FFF0; 
        Thread->esp = (unsigned long) process->Image + 0x4FFF0; 
        Thread->eflags = 0x3200; 
        Thread->cs = 0x1B; 
        //Thread->eip = (unsigned long) 0x00401000; 
        Thread->eip = (unsigned long) process->Image + 0x1000;


		// Segment registers.
        Thread->ds = 0x23; 
        Thread->es = 0x23; 
        Thread->fs = 0x23; 
        Thread->gs = 0x23; 

		// Outros.
        Thread->eax = 0;
        Thread->ebx = 0;
        Thread->ecx = 0;
        Thread->edx = 0;
        Thread->esi = 0;
        Thread->edi = 0;
        Thread->ebp = 0;


		// Next thread.
        Thread->Next = NULL;

		// Thread queue.
        queue_insert_data ( queue, 
            (unsigned long) Thread, 
            QUEUE_INITIALIZED );


		// #importante:
		// * MOVEMENT 1 ( Initialized ---> Standby ).
		// Isso permitira que o taskswitch selecione ela pra rodar.

        SelectForExecution (Thread); 
        

        
        // #debug
        //printf ("do_execve: Spawn thread \n");
        //refresh_screen();
        //while(1){}

        KiSpawnTask ( Thread->tid );

        // No return!
                
        panic ("do_execve: KiSpawnTask returned ");
        //goto done;
    };

	// fail

fail:

    printf ("do_execve: #fail\n");
	// refresh_screen ();

done:

	//#debug
	//printf(">>>shared_p0={%s}\n"     ,shared_p[0]);
	//printf(">>>shared_p1={%s}\n"     ,shared_p[1]);
	//printf(">>>shared_p2={%s}\n\n"   ,shared_p[2]);
	//printf(">>>shared_p3={%s}\n\n"   ,shared_p[3]);
	//refresh_screen();
	//while(1){ asm("hlt"); }

	//#debug
	//printf("done\n");	

	// #Obs: 
	// +N�o devemos emitir mensagens no caso de acerto.
	// +refresh_screen s� no caso de erro.

	// #bugbug
	// #obs: 
	// Estamos usando isso s� por enquanto para debug.

    refresh_screen ();

    return (int) Status;
}

                 
               
    

//
// End.
//

