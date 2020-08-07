/*
 * File: ps/action/clone.c 
 * 
 */


#include <kernel.h>




pid_t sys_fork_process (void)
{
    debug_print ("sys_fork_process: [TODO]\n");
    
    //return (pid_t) clone_process();
    return -1;
}


/*
 ***************************************
 * clone_process 
 *     used for fork();
 */
 

pid_t clone_process (void){

    int PID = -1;

    struct process_d *Current;
    struct process_d *Clone;

    unsigned long *dir;
    unsigned long old_dir_entry1; 
    //unsigned long old_image_pa; //usado para salvamento.

    int Ret = -1;
    int i;
    int w;



    // #debug: 
    debug_print ("clone-clone_process: FIXME. It's a work in progress!\n");
    printf ("clone-clone_process: Cloning the current process..\n");


	//
	// # Current.
	//

    // Validation.
	
    if ( current_process < 0 ){
        printf("clone_process: current_process\n");
        goto fail;
    } 

    Current = (struct process_d *) processList[current_process];
	
    if ( (void *) Current == NULL ){
        printf ("clone_process: Current struct \n");
        goto fail;
	
    }else{
		
        if ( Current->used != 1 || Current->magic != 1234 ){    
            printf ("clone_process: Current validation \n");
            goto fail;
        }


        // ?? why???
        // #test
        // Virtual Address of the current process.
        dir = (unsigned long *) Current->DirectoryVA;
        //old_dir_entry0 = dir[0];    // Saving it.
        old_dir_entry1 = dir[1];    // Saving it.

        // Saving the physical address.
		//old_image_pa = (unsigned long) virtual_to_physical ( Current->Image, gKernelPageDirectoryAddress ); 		
		
	    // #debug
	    // printf(">>> check current process: %d %d \n", current_process, Current->pid );		
		goto do_clone;
		//...
	};


	//
	// # Clone.
	//

	// Cria uma estrutura do tipo processo, mas n�o inicializada.
	
do_clone:

    // Creating a struct of type process.
    // It's not initialized yet.

    Clone = (struct process_d *) processObject ();

    if ( (void *) Clone == NULL ){
        printf ("clone_process: Clone struct fail \n");
        goto fail;

    } else {

        // Get a empty slot in the list of processes.

        PID = (int) getNewPID ();

        if ( PID <= 0 ){
            printf ("clone_process: getNewPID fail %d \n", PID );
            goto fail;
        }

        Clone->pid = PID;
        Clone->used = 1;
        Clone->magic = 1234;

        // Saving into the list.
        processList[PID] = (unsigned long) Clone;

        //
        // # Copy memory.
        //

        // Copy memory.
        // Copy all the process's image.
        // Save the address in: 
        // Current->childImage and Current->childImage_PA.

        processCopyMemory ( Current );



        //
        // #debug 
        //

        // Breakpoint to see some critical info.

        //unsigned long *xxx = (unsigned long *) Current->DirectoryVA;	
        //printf ("DirectoryVA = %x \n",Current->DirectoryVA);
        //printf ("Directory Entry 1 = %x \n", xxx[1] );
        //printf ("childImage_PA = %x \n",Current->childImage_PA);	

        //mmShowPDEForAllProcesses (1);

        //printf ("DirectoryVA = %x \n",Current->DirectoryVA);
        //printf ("Directory Entry 1 = %x \n", xxx[1] );

        //kprintf ("debug *breakpoint");
        //refresh_screen();
        //while (1){}


        //
        // Copy structure.
        //

        // Creating a page directory for the child, and
        // Copying the father's structure.

        Ret = processCopyProcess ( Current->pid, Clone->pid );

        if ( Ret != 0 ){
            panic ("clone_process: processCopyProcess fail\n");
        }

        // Creating a new pagetable for the child process's image.
        // We are using the child process's directory to this.
        // This is the physical address for the child's image,
        // we got this when allocating memory. It's ok.
        // #important: It's pointing to 0x400000. (ENTRY_USERMODE_PAGES)
        // 4MB ??

        CreatePageTable ( (unsigned long) Clone->DirectoryVA, 
            ENTRY_USERMODE_PAGES, Clone->ImagePA );
            //ENTRY_USERMODE_PAGES, Current->childImage_PA );
          
        // Com base no endereço físico, usamos a função acima
        // para atribuírmos um novo endereço virtual para a imagem.
        Clone->Image = 0x400000; // com base na entrada escolhida (ENTRY_USERMODE_PAGES)

        // #bugbug
        // A rotina acima resolve o mapeamento da imagem do processo clone.
        // Porém não resolve a pilha, que foi alocada em um endereço diferente.
        // Salvamos esse endereço precisamos mapear;

       // Talvez mapear a pilha em outra pagetable
       // possa ser uma solução.

        //
        // # debug.
        //

        // #important:
        // Checking if it's all right with the saved info.
        // #todo: Show the structure and the registers.

        // ??
        // mmShowPDEForAllProcesses (1);
        // show_thread_information (); 


		// printf ("\n");
		
		// [current]
		// mostra_reg (Current->control->tid);
		// printf ("Current.DirectoryVA = %x \n",Current->DirectoryVA);
		// printf ("Current.DirectoryPA = %x \n",Current->DirectoryPA);
		// printf ("Current.Image = %x \n",Current->Image);
		// printf ("Current.ImagePA = %x \n",Current->ImagePA);
		// Current->control->eipPA = (unsigned long) virtual_to_physical ( Current->control->eip, Current->DirectoryVA ); 
		// printf ("Current.control.eipVA = %x \n",Current->control->eip);
		// printf ("Current.control.ring0_eipVA = %x \n",Current->control->ring0_eip);
		// printf ("Current.control.eipPA = %x \n",Current->control->eipPA);

		
		// [clone]
		// mostra_reg (Clone->control->tid);
		// printf ("Clone.DirectoryVA = %x \n",Clone->DirectoryVA);
		// printf ("Clone.DirectoryPA = %x \n",Clone->DirectoryPA);
		// printf ("Clone.Image = %x \n",Clone->Image);
		// printf ("Clone.ImagePA = %x \n",Clone->ImagePA);
		// #bugbug: Esse � o endere�o l[ogico em que deve estar a imagem do clone
		// na vis�o do diret�rio do clone.
		// Clone->Image = 0x400000;
		// Clone->ImagePA = (unsigned long) virtual_to_physical ( Clone->Image  , Clone->DirectoryVA ); 
		// agora visto com o diret�rio do processo clone.
		// printf ("Clone.Image = %x \n",Clone->Image);
		// printf ("***Clone.ImagePA = %x \n",Clone->ImagePA);
		// Clone->control->eipPA = (unsigned long) virtual_to_physical ( Clone->control->eip  , Clone->DirectoryVA ); 		
		// printf ("Clone.control.eipVA = %x \n",Clone->control->eip);
		// printf ("Clone.control.ring0_eipVA = %x \n",Clone->control->ring0_eip);
		// printf ("Clone.control.eipPA = %x \n",Clone->control->eipPA);
		
		
		// printf ("\ndo fork process: *breakpoint");
		// refresh_screen();
		// while(1){}
		
		//
		// Load child image.
		//
		
		// #importante: 
	    // Carregando a image do processo filho.
		
		
        //fsLoadFile ( VOLUME1_FAT_ADDRESS, VOLUME1_ROOTDIR_ADDRESS, 
	     //   "GDESHELL BIN", (unsigned long) Clone->Image );
		

		
		
		// Clonando manualmente a thread de controle.
		// S� a imagem ... falta a pilha.

        // #bugbug: size ???
        // Ja n�o fizemos isso quando chamamos processCopyMemory ???
        // l� copiamos 200kb
	//	memcpy ( (void *) Clone->Image, (const void *) Current->Image, ( 0x50000 ) ); 
		//memcpy ( (void *) Clone->Image, (const void *) Current->Image, (1024*200) );  //bugbug

        //====
		Clone->control->ownerPID      = Clone->pid;
		Clone->control->type          = Current->control->type; 
		Clone->control->plane         = Current->control->plane;
		Clone->control->base_priority = Current->control->base_priority;
		Clone->control->priority      = Current->control->priority;
		Clone->control->iopl          = Current->control->iopl;
		Clone->control->preempted     = Current->control->preempted;
		Clone->control->step          = 0;//Current->control->step;
		Clone->control->quantum       = Current->control->quantum;
		Clone->control->quantum_limit = Current->control->quantum_limit;
		
		// A thread do processo clone ainda n�o rodou.
		Clone->control->standbyCount = 0;
		Clone->control->runningCount = 0;
		Clone->control->initial_time_ms = get_systime_ms();
		Clone->control->total_time_ms = 0;
		Clone->control->runningCount_ms = 0;
		Clone->control->readyCount = 0;
		Clone->control->ready_limit = READY_LIMIT;
		Clone->control->waitingCount = 0;
		Clone->control->waiting_limit = WAITING_LIMIT;
		Clone->control->blockedCount = 0;
		Clone->control->blocked_limit = BLOCKED_LIMIT;

        for ( w=0; w<8; w++ ){
            Clone->control->wait_reason[w] = (int) 0;
        }

        Clone->control->ticks_remaining = Current->control->ticks_remaining;
        
        Clone->control->signal = Current->control->signal;
        Clone->control->umask  = Current->control->umask;


		// CPU context


        //
        // Stack frame.
        //

        // # Caution
        // In the fork() routine we need the same esp from father,
        // and not the start of the stack.

        Clone->control->ss = Current->control->ss;
        
        //
        // Clild stack
        //

        //printf("child stack\n");
        //refresh_screen();
                
        // O conteúdo da pilha foi copiado, porém elas possuem endereço virtual diferentes.
        //Clone->control->esp         = Current->control->esp;  // #Atention!
        Clone->control->esp = Current->childStack;  // #Atention!

        //podemos copiar a stack do pai numa área de memória compartilhada
        //e pasasrmos o ponteiro
        //Clone->control->esp = (unsigned long) allocPages(2); //8KB


        //#todo: checar validade
       
        //copiar.
        //nesse momento o kernel está usando o diretório de páginas
        //do processo pai, então tem acesso à sua pilha.
        //char *src = (char *) Current->control->esp;
        //char *dst = (char *) Clone->control->esp;
        
        //copiando para a área compartilhada 
        //para o filho ler . 8KB
        //int __c;
        //for (__c=0; __c<(1024*8); __c++)
           // dst[__c] = src[__c];
        
        //printf("child stack ok\n");
        //refresh_screen();


        Clone->control->eflags = Current->control->eflags;
        Clone->control->cs     = Current->control->cs;
        
        Clone->control->eip    = Current->control->eip;  // mesmo do pai.
        //Clone->control->eip = 0x401000; //teste: para o clone começar do início.


        Clone->control->initial_eip = Current->control->initial_eip;

        printf (">> %x\n",Current->control->eip);
        printf (">> %x\n",Clone->control->eip);


		// more registers.
		Clone->control->ds = Current->control->ds;
		Clone->control->es = Current->control->es;
		Clone->control->fs = Current->control->fs;
		Clone->control->gs = Current->control->gs;
		Clone->control->eax = 0;                       // Retornamos 0 para o filho.
		Clone->control->ebx = Current->control->ebx;
		Clone->control->ecx = Current->control->ecx;
		Clone->control->edx = Current->control->edx;
		Clone->control->esi = Current->control->esi;
		Clone->control->edi = Current->control->edi;
		Clone->control->ebp = Current->control->ebp;

        // tss
        // mesma tss
        Clone->control->tss = Current->control->tss;

        Clone->control->Next = NULL;
        Clone->control->exit_code = 0;
        //====

       //todo: tem outros elementos ...
       Clone->ppid = Current->pid; 
       Clone->uid  = Current->uid;
       Clone->gid  = Current->gid;
       Clone->tty  = Current->tty;
       //strncpy(proc->name, curr_proc->name, NAME_MAX);
       Clone->plane = Current->plane;
       Clone->personality = Clone->personality;
       Clone->base_priority = Current->base_priority;       
       Clone->priority = Current->priority;
       Clone->step = 0;
       Clone->quantum = Current->quantum;
       Clone->bound_type = Current->bound_type;
       Clone->preempted = Current->preempted;
       Clone->usession = Current->usession;
       Clone->room     = Current->room;
       Clone->desktop  = Current->desktop;
       Clone->wait4pid = 0;
       Clone->exit_code = 0;
       Clone->nchildren = 0;
       
       Current->nchildren++;
       
       //Clone->signal = 0;  //todo
       Clone->umask = Current->umask;
       
       Clone->iopl = Current->iopl;
       //Clone->prev = NULL;
       Clone->next = NULL;

        // Objects.
        for (i=0; i<32; i++){  
            Clone->Objects[i] = Current->Objects[i]; 
        }


        //
        // # debug
        //

        // Showing registers.

        // #obs
        // regs ok ?!

        // Current.
        //printf("\n\n");
        //printf ("==== Current: control thread ====\n");
        //show_reg (Current->control->tid);

        // Clone.
        //printf("\n\n");
        //printf ("==== Clone: control thread ====\n");
        //show_reg (Clone->control->tid);

        // #hang
        //refresh_screen();
        //while(1){}

		
		// #importante
		// O dispatcher precisa disso na hora que restaura
		// o contexto.
		// Mas isso ja foi feito antes quando copiamos o processo.
		
        //#debug
        //printf("Directory PA %x \n",Clone->DirectoryPA);
        //refresh_screen();
        //while(1){}

        Clone->control->DirectoryPA = Clone->DirectoryPA;


        // [pai]
        Current->control->quantum = 30;
        Current->control->saved = 1;
        Current->control->state = READY;

        // [filho]
        // Esse é o melhor jeito.
        // Não podemos usar o spawn.
        Clone->control->quantum = 30;
        Clone->control->saved = 1;        // Está salvo
        Clone->control->state = READY;    // Está pronta para ser escalonada. 


        //
        // return
        //


		// #importante:
		// Retornamos para o processo pai o PID do filho.
		
		//pai
		current_thread = Current->control->tid;
		current_process = Current->pid;
		
		// Isso retornou corretamente para o processo pai
		// o pid do filho.
        Current->control->eax = (unsigned long) Clone->pid;
        return (pid_t) Clone->pid;
    };


    // Fail.

fail:

    return (pid_t) -1;
}



/*
 ****************************************************
 * clone_and_execute_process:  
 * 
 *     Service 900.
 * 
 *     Clona o processo atual e executa o processo filho.
 *     O processo pai continua rodando.
 *     #obs: Isso funciona.
 */


// Clona e executa o filho dado o nome do filho.
// O filho inicia sua execução do início da imagem.

// Se o processo filho herdar o floxo padr�o, ent�o o processo filho
// pode escrever no seu stdout e o processo pai pode ler no seu
// pr�prio stdout.


// #importante
// >>>> Isso funciona. 
// ( * N�o * ) mexa pois ainda estamos
// trabalahndo os outros m�todos.

// IN: ??
// OUT: ??

pid_t clone_and_execute_process (char *filename){

    struct process_d *Current;
    struct process_d *Clone;

    unsigned long *dir;
    unsigned long old_dir_entry1;

    int PID = -1;
    int Ret = -1;

    int Status = -1;
    int __Status = -1;


    // # sobre debug:
    // Essa rotina está falhando na máquina real às vezes.
    // Precisamos usar printf para verbose, pois não podemos
    // usar porta serial ainda.

    // #debug
    debug_print ("clone_and_execute_process: [FIXME] It's a work in progress\n");
    printf      ("clone_and_execute_process:\n");


    // Convertendo o formato do nome do arquivo.
    // >>> "12345678XYZ"

    read_fntos ( (char *) filename );


    // Searching for the file only on the root dir.

    __Status = (int) KiSearchFile ( filename, VOLUME1_ROOTDIR_ADDRESS );

    if (__Status != 1){
         debug_print ("clone_and_execute_process: File not found!\n");
         printf      ("clone_and_execute_process: File not found!\n");
         goto fail;
    }


	//unsigned long old_image_pa; //usado para salvamento.

	//#debug message.
    //printf ("do_clone_execute_processs: clona o pai e executa o filho..\n");


	// ## Current ##
	// Checando a validade do processo atual.

	//if ( current_process < 0 )
	//    return 0;

    Current = (struct process_d *) processList[current_process];

    if ( (void *) Current == NULL ){
        printf ("clone_and_execute_process: Current struct \n");
        goto fail;

    }else{

        if ( Current->used != 1 || Current->magic != 1234 ){    
            printf ("clone_and_execute_process: Current validation \n");
            goto fail;
        }


        // #test
        dir = (unsigned long *) Current->DirectoryVA;
        //old_dir_entry0 = dir[0];    // Saving it.
        old_dir_entry1 = dir[1]; //salvando


		//salvando o endere�o f�sico da imagem que existe no processo.
		//old_image_pa = (unsigned long) virtual_to_physical ( Current->Image, gKernelPageDirectoryAddress ); 

        //#debug
        //printf(">>> check current process: %d %d \n", current_process, Current->pid );
        goto do_clone;
        // ...
    };


	//
	// Clone.
	//

do_clone:

	// Cria uma estrutura do tipo processo, mas não inicializada.

    Clone = (struct process_d *) processObject();

    if ( (void *) Clone == NULL ){
        printf ("clone_and_execute_process: Clone struct fail \n");
        goto fail;

    } else {

        // Obtêm um índice para um slot vazio na lista de processos.
        // Precisa estar dentro do range válido para processos
        // em ring3.
        
        PID = (int) getNewPID();

        if ( PID < 0 || PID < USER_BASE_PID )
        {
            printf ("clone_and_execute_process: getNewPID fail %d \n", 
                PID );
            goto fail;
        }

        Clone->pid = (pid_t) PID;
        Clone->uid = (uid_t) current_user;
        Clone->gid = (gid_t) current_group;
        Clone->used = 1;
        Clone->magic = 1234;
        
        // Salvando na lista.
        processList[PID] = (unsigned long) Clone;

        // Copiando a memória e o processo.
        // Copy memory:
        // >> Copia a memória usada pela imagem do processo.
        // #bugbug: Esse é um momento crítico.
        // #todo: Precisamos do suporte a imagens ELF.
        // >> Clone the process: 
        // Lets create the page directory for the Clone.
        // Now we need to map the physical addresses we got 
        // in the allocation routine.
        // #obs: 
        // Na hora de copiar o processo, a estrutura do clone 
        // receberá os valores da estrutura do processo atual,
        // até mesmo o endereço do diretório de páginas.
        // See: process.c

        processCopyMemory(Current);

        Ret = processCopyProcess ( Current->pid, Clone->pid );

        if ( Ret != 0 ){
            panic ("clone_and_execute_process: processCopyProcess fail\n");
        }


        // >> Load file:
        // #importante: 
        // Carregando a imagem do processo filho.
        // Se o carregamento falhar, temos que abortar a clonagem,
        // caso contrário, executa a cópia da imagem do pai. ??
        // #bugbug: Essa rotina começou a falhar aqui. Convertendo 
        // num formato errado.
        // Movemos essa conversão para o início dessa função,
        // onde checaremos se o arquivo está no diretório.
        // #bugbug
        // Se isso não está funcionando direito e uma thread 
        // defeituosa fica remanescente quando digitamos um 
        // comando errado então vamos matar a thread e o processo.

        // #todo
        // Num ambiente 'mp' precisaremos de um lock aqui.
        
        //#debug
        //printf ("do_clone_execute_process: %s\n",filename);
        
        Status = (int) fsLoadFile ( VOLUME1_FAT_ADDRESS, 
                           VOLUME1_ROOTDIR_ADDRESS, 
                           filename, 
                           (unsigned long) Clone->Image );

       // Se falhou o carregamento. Vamos matar a thread e o processo.
       if ( Status != 0 )
       {
            // kill thread.
            Clone->control->used = 0;
            Clone->control->magic = 0;
            Clone->control->state = DEAD;
            Clone->control == NULL;
            
            // kill process.
            Clone->used = 0;
            Clone->magic = 0;  
            Clone = NULL;
            
            printf ("clone_and_execute_process: [FAIL] Couldn't load the file %s\n", 
                filename );
            goto fail;
       }
       
       // Check ELF signature.
       // OK. O comando existe e o arquivo foi carregado, mas 
       // precisamos saber se a assinatura de ELF é válida.
       Status = (int) fsCheckELFFile ( (unsigned long) Clone->Image );

       // Assinatura ELF inválida. Vamos matar a thread e o processo.
       if ( Status != 0 )
       {
            // kill thread.
            Clone->control->used = 0;
            Clone->control->magic = 0;
            Clone->control == NULL;
            
            // kill process.
            Clone->used = 0;
            Clone->magic = 0;            
            Clone = NULL;
            
            printf ("clone_and_execute_process: [FAIL] ELF fail \n");
            goto fail;
        }

        // >> Page table:
        // Remapeando a imagem, mas agora no diretório de páginas
        // do processo filho.
        // Lembrando que já criamos o diretório de páginas para o clone.
        // ENTRY_USERMODE_PAGES, esse número de entrada é para o 
        // endereço virtual padrão para aplicativos em ring3, 0x400000.
  
        CreatePageTable ( (unsigned long) Clone->DirectoryVA, 
            ENTRY_USERMODE_PAGES, Clone->ImagePA );

        // Configurando o endereço virtual padrão para aplicativos.
        // Novo endereço virtual da imagem. Conseguimos isso 
        // por causa da criação da pagetable, logo acima.
        // # Caution
        // Entry point and stack.
        // We are clonning only the control thread.
        // The entry point in the start of the image. 0x401000.
        // And the stack ??

        Clone->Image = CONTROLTHREAD_BASE;               //0x400000 
        Clone->control->eip = CONTROLTHREAD_ENTRYPOINT;  //0x401000
 
        // #bugbug
        // #todo
        // Ok mesma coisa precisa ser feito para o endereço
        // virtual da pilha.

        // #Cuidado
        // Heap for Clone.
        // Essa é a rotina usada na criação de processo 
        // pra gerar um heap para ele.
        // Vamos tentar usar isso na rotina de clonagem.

        Clone->Heap     = (unsigned long) g_heappool_va + (g_heap_count * g_heap_size);
        Clone->HeapSize = (unsigned long) g_heap_size;
        Clone->HeapEnd  = (unsigned long) (Clone->Heap + Clone->HeapSize); 
        g_heap_count++;


        // Stack for the clone. 
        Clone->control->esp = CONTROLTHREAD_STACK;  //0x007FFFF0 
        Clone->Stack        = CONTROLTHREAD_STACK;  //0x007FFFF0
        Clone->StackSize = (32*1024);    //isso foi usado na rotina de alocação.
        Clone->StackEnd = ( Clone->Stack - Clone->StackSize );


        // name.
        Clone->processName_len = (size_t) strlen ( (const char *) filename );
        strcpy ( Clone->__processname, (const char *) filename );   


        //
        // Debug
        //

		
		// mmShowPDEForAllProcesses (1);
		// show_thread_information (); 

		// [current]
		// printf ("\n");
		// mostra_reg (Current->control->tid);
		// printf ("Current.DirectoryVA = %x \n",Current->DirectoryVA);
		// printf ("Current.DirectoryPA = %x \n",Current->DirectoryPA);
		// printf ("Current.Image = %x \n",Current->Image);
		// printf ("Current.ImagePA = %x \n",Current->ImagePA);
		// printf ("Current.control.eipVA = %x \n",Current->control->eip);


		// [clone]
		//printf ("\n");
		//mostra_reg (Clone->control->tid);
		//printf ("Clone.DirectoryVA = %x \n",Clone->DirectoryVA);
		//printf ("Clone.DirectoryPA = %x \n",Clone->DirectoryPA);
		//printf ("Clone.Image = %x \n",Clone->Image);
		//printf ("Clone.ImagePA = %x \n",Clone->ImagePA);
		//printf ("Clone.control.eip = %x \n",Clone->control->eip);
		//printf ("Clone.control.esp = %x \n",Clone->control->esp);
		// printf ("\n : *breakpoint");
		//refresh_screen();
		//while(1){}



		//#hackhack

		// [pai]
		Current->control->state = READY;


		// [filho]
		Clone->control->saved = 0;
		SelectForExecution (Clone->control);


        // Se o processo filho herdar o floxo padr�o, ent�o o 
        // processo filho pode escrever no seu stdout e o processo 
        // pai pode ler no seu pr�prio stdout.


		//#test
		//Clone->control->stdin  = stdin; //Current->control->stdin;
		//Clone->control->stdout = stdout; //Current->control->stdout;
		//Clone->control->stderr = stderr; //Current->control->stderr;
		//Clone->Streams[0] = (unsigned long) stdin; //Current->control->stdin;
		//Clone->Streams[1] = (unsigned long) stdout; //Current->control->stdout;
		//Clone->Streams[2] = (unsigned long) stderr; //Current->control->stderr;



        // #debug: Para a máquina real.
        printf ("clone_and_execute_process: [DEBUG] Returning to father.\n");
        refresh_screen ();

		//
		// Return.
		//

		// #obs:
		// Retornamos para o pai o PID do filho.
		// Igual acontece no fork().
		
		//pai
        current_process = Current->pid;
        current_thread  = Current->control->tid;

        return (pid_t) Clone->pid;
    };

	// Fail.

fail:
    refresh_screen();
    return (pid_t) (-1);
}


//
// End.
//

