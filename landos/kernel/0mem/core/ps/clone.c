/*
 * File: ps/clone.c 
 * 
 */


#include <kernel.h>



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
    unsigned long old_dir_entry1 = 0; 
    //unsigned long old_image_pa; //usado para salvamento.

    int Ret = -1;
    int i=0;
    int w=0;


    // #debug: 
    debug_print ("clone-clone_process: [FIXME] Cloning the current process..\n");
    printf      ("clone-clone_process: [FIXME] Cloning the current process..\n");


    //
    // == Current ============================================
    //

    if ( current_process < 0 ){
        debug_print ("clone_process: [FAIL] current_process\n");
        printf      ("clone_process: [FAIL] current_process\n");
        goto fail;
    } 

    Current = (struct process_d *) processList[current_process];

    if ( (void *) Current == NULL ){
        debug_print ("clone_process: [FAIL] Current\n");
        printf      ("clone_process: [FAIL] Current\n");
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
        //old_dir_entry1 = dir[1];    // Saving it.
        
        if( (void*) Current->DirectoryVA == NULL )
            panic("clone_process: Current->DirectoryVA\n");

        // Saving the physical address.
        //old_image_pa = (unsigned long) virtual_to_physical ( Current->Image, gKernelPageDirectoryAddress ); 		

        // #debug
        // printf(">>> check current process: %d %d \n", current_process, Current->pid );
        goto do_clone;
        //...
    };

    // Fail
    // Something is wrong if we reach this point here!
    // goto fail;

    //
    // == Clone ===============================================
    //

	// Cria uma estrutura do tipo processo, mas nao inicializada.

do_clone:

    // Creating a struct of type process.
    // It's not initialized yet.

    Clone = (struct process_d *) processObject();

    if ( (void *) Clone == NULL )
    {
        debug_print ("clone_process: [FAIL] Clone\n");
        printf      ("clone_process: [FAIL] Clone\n");
        goto fail;
    }


    // Get a empty slot in the list of processes.
    // Register. Saving into the list.
    
    PID = (int) getNewPID();

    if ( PID <= 0 )
    {
        debug_print ("clone_process: [FAIL] getNewPID \n");
        printf      ("clone_process: [FAIL] getNewPID \n");
        goto fail;
    }

    Clone->pid = PID;
    Clone->used = 1;
    Clone->magic = 1234;

    processList[PID] = (unsigned long) Clone;

    //
    // == Copy image memory ===============================
    //

    // Copy memory.
    // Copy all the process's image.
    // Save the address in: 
    // Current->childImage and Current->childImage_PA.

    Ret = processCopyMemory(Current);
    if ( Ret != 0 ){
        panic ("clone_process: processCopyMemory\n");
    }

    //
    // == Copy process structure ===========================
    //

    // Creating a page directory for the child, and
    // Copying the father's structure.

    Ret = processCopyProcess ( Current->pid, Clone->pid );
    if ( Ret != 0 ){
        panic ("clone_process: processCopyProcess\n");
    }

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


        // Creating a new pagetable for the child process's image.
        // We are using the child process's directory to this.
        // This is the physical address for the child's image,
        // we got this when allocating memory. It's ok.
        // #important: It's pointing to 0x400000. (ENTRY_USERMODE_PAGES)
        // 4MB ??


    // #bugbug
    // Checando a validade dos valores obtidos pelas rotinas
    // chamadas logo acima.

    if( (void*) Clone->DirectoryVA == NULL )
        panic("clone_process: Clone->DirectoryVA\n");

    if( (void*) Clone->ImagePA == NULL )
        panic("clone_process: Clone->ImagePA\n");


    void *__pt;

    __pt = (void *) CreatePageTable( 
                        (unsigned long) Clone->DirectoryVA, 
                        ENTRY_USERMODE_PAGES, 
                        (unsigned long) Clone->ImagePA );

    if ( (void*) __pt == NULL )
        panic ("clone_process: __pt\n");


    // Com base no endereço físico, usamos a função acima
    // para atribuírmos um novo endereço virtual para a imagem.
    // com base na entrada escolhida (ENTRY_USERMODE_PAGES)

    Clone->Image = (unsigned long) 0x400000; 


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
        // memcpy ( (void *) Clone->Image, (const void *) Current->Image, ( 0x50000 ) ); 
        // memcpy ( (void *) Clone->Image, (const void *) Current->Image, (1024*200) );  //bugbug


    //
    //  Control thread.
    //
    

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


    // A thread do processo clone ainda nao rodou.
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

    // Signals.
            
    Clone->control->signal = Current->control->signal;
    Clone->control->umask  = Current->control->umask;


    //
    // == Stack frame =========================================
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
    Clone->control->esp = (unsigned long) Current->childStack;  // #Atention!


    if ( (void*) Clone->control->esp == NULL )
        panic ("clone_process: Clone->control->esp\n");


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


    Clone->control->eflags = (unsigned long) Current->control->eflags;
    Clone->control->cs     = Current->control->cs;
        
    //
    // == EIP ==================================
    //

    // mesmo do pai.
    Clone->control->eip = (unsigned long) Current->control->eip;  

    // O filho vai começar de onde parou o pai.
    // Essa variavel eh so um salvamento.
    Clone->control->initial_eip = (unsigned long) Clone->control->eip;

    printf (">> father eip = %x\n",Current->control->eip);
    printf (">> child eip  = %x\n",Clone->control->eip);


    if ( (void*) Clone->control->eip == NULL )
        panic ("clone_process: Clone->control->eip\n");

    if ( (void*) Clone->control->initial_eip == NULL )
        panic ("clone_process: Clone->control->initial_eip\n");


    // More registers.
    Clone->control->ds = Current->control->ds;
    Clone->control->es = Current->control->es;
    Clone->control->fs = Current->control->fs;
    Clone->control->gs = Current->control->gs;
    Clone->control->eax = 0;                       // Retornamos 0 para o filho.
    Clone->control->ebx = Current->control->ebx;
    Clone->control->ecx = Current->control->ecx;
    Clone->control->edx = Current->control->edx;
    Clone->control->esi = (unsigned long) Current->control->esi;
    Clone->control->edi = (unsigned long) Current->control->edi;
    Clone->control->ebp = (unsigned long) Current->control->ebp;

    // tss
    // mesma tss
    Clone->control->tss = Current->control->tss;

    Clone->control->next = NULL;

    Clone->control->exit_code = 0;
    //====

    //todo: tem outros elementos ...
    Clone->ppid = Current->pid; 
    Clone->uid  = Current->uid;
    Clone->gid  = Current->gid;
    Clone->tty  = Current->tty;
    //strncpy(proc->name, curr_proc->name, NAME_MAX);
    Clone->plane         = Current->plane;
    Clone->personality   = Current->personality;
    Clone->base_priority = Current->base_priority;       
    Clone->priority      = Current->priority;
    Clone->step = 0;
    Clone->quantum       = Current->quantum;
    Clone->bound_type    = Current->bound_type;
    Clone->preempted     = Current->preempted;
    Clone->usession      = Current->usession;
    Clone->room          = Current->room;
    Clone->desktop       = Current->desktop;
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

    if ( (void*) Clone->control->DirectoryPA == NULL )
        panic ("clone_process: Clone->control->DirectoryPA\n");

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

        // pai
    current_process = Current->pid;
    current_thread  = Current->control->tid;

        // #test
        // Isso retornou corretamente para o processo pai
        // o pid do filho.

    Current->control->eax = (unsigned long) Clone->pid;

    debug_print ("clone_process: done\n");
    return (pid_t) Clone->pid;


    // Fail.

fail:
    debug_print ("clone_process: Fail\n");
    printf      ("clone_process: Fail\n");
    refresh_screen();
    
    return (pid_t) -1;
}


/*
 *******************************************************
 * sys_fork_process:
 *     Service 71.
 *     Iimplementation of the fork() system call.
 */

// #todo
// It's not working.

pid_t sys_fork_process (void)
{
    pid_t _pid = -1;
    
    debug_print ("sys_fork_process: [FIXME]\n");
    
    _pid = (pid_t) clone_process();

    debug_print ("sys_fork_process: done\n");
    return _pid;
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
// (  Nao  ) mexa pois ainda estamos
// trabalahndo os outros m�todos.

// It loads a file of a given directory address.
// #todo: We need some info about this directory,
// We need to use the dir entry structure as the argument.

// IN: ??
// OUT: ??

pid_t clone_and_execute_process ( char *filename )
{

    // #bugbug (fs)
    // We need to get the fs directory size to allocate a buffer
    // to this fs directory.
    

    struct process_d *Current;
    struct process_d *Clone;

    // loop
    // Socket support.
    // indice usado na inicializaçao da lista de 
    // conexoes pendentes do processo servidor.
    register int sIndex=0;


    int Status = -1;
    int PID = -1;

    // # What is this?
    // The directory virtual address of the current process. ??
    unsigned long *dir;
    
    unsigned long old_dir_entry1=0;


    // File support.
    unsigned long dir_address = 0;

    char *path;
    char *name;

    // page table.
    void *__pt;


    // #debug
    debug_print ("clone_and_execute_process: [FIXME] It's a work in progress\n");
    //printf      ("clone_and_execute_process:\n");


    if ( (void*) filename == NULL ){
        panic ("clone_and_execute_process: [ERROR] filename\n");
    }

    if ( *filename == 0 ){
        panic ("clone_and_execute_process: [ERROR] *filename\n");
    }

    path = filename;
    name = filename;


    
    // #todo
    // Essas rotinas de procura e garregamento podem ir para outro lugar.
    // #bugbug
    // O maior problema aqui eh o tamanho do diretorio, pois estamos pre-alocando
    // memoria para conter o diretorio.

    // from cwd?
    if (path[0] == '.' && path[1] == '/')
    {
        debug_print ("clone_and_execute_process: [FIXME] Can't execute from cwd \n");
        printf      ("clone_and_execute_process: [FIXME] Can't execute from cwd \n");
        goto fail;
    }


    // Shotcuts to execute programs.
    
    // Principais diretórios para execução de programas.
    // no disco do sistema.
    // Os dois pontos significa que o pathname é simplificado.
    // e contém quatro caracteres que selecionam um 
    // dos subdiretórios do diretório raiz, que podem muito bem
    // terem seus endereços na memória pre-definidos para facilitar.
    // gramado-like
    // ::p/ = "/PORTALS/"   (system apps)


    // para 32 entradas.
    unsigned long BUGBUG_OVERFLOW = ( 32*128 );
    
    
    /* 
    // execute from root.
    if (path[0] == ':' &&
        path[1] == ':' &&
        path[2] == 'p' &&
        path[3] == '/' )
    {

        path++;
        path++; 
        path++; 
        path++;
        name=path;

        // #bugbug
        // We need to get the directory size to allocate a buffer
        // to this directory.
        
        //dir_address = VOLUME1_ROOTDIR_ADDRESS;
        dir_address = (unsigned long) kmalloc(     BUGBUG_OVERFLOW     );
        
        if (dir_address == 0){ 
            debug_print("clone_and_execute_process: [FAIL] dir_address allocation fail\n");
            kfree(dir_address); 
            goto fail;
        }

        //load portals/ dir.
        debug_print ("clone_and_execute_process: [FIXME] Loading /PORTALS/ diretory \n");
        // IN: 
        // fat address, dir address, filename, file address.
        // OUT: 0=OK
        Status = fsLoadFile ( (unsigned long) VOLUME1_FAT_ADDRESS,  // fat address
                     (unsigned long) VOLUME1_ROOTDIR_ADDRESS,       // dir address. onde procurar. 
                     32, //#bugbug: Number of entries.  
                     (unsigned char *) "PORTALS    ",               // dir name 
                     (unsigned long) dir_address,                   // addr. Onde carregar.
                      BUGBUG_OVERFLOW );                  
        if(Status!=0){ 
            debug_print("clone_and_execute_process: [FAIL] Couldn't load file\n");
            kfree(dir_address); 
            goto fail;
        }
        // Procure dentro do diretorio carregado.
        goto __search;
    }
    */

    // No caso de nenhum dos atalhos acima.
    // Search in root dir. ("/")
    dir_address = VOLUME1_ROOTDIR_ADDRESS;


//
// Loop.
//

    // Search
    // Convertendo o formato do nome do arquivo.
    // >>> "12345678XYZ"
    // Procura o nome no diretorio carregado anteriormente.
    // Que eh o diretorio raiz

__search:

    read_fntos ( (char *) name );

    Status = (int) search_in_dir ( name, dir_address );
    if (Status == 1)
    { 
        goto __found; 
    }



    /*
    //
    // == Search in BIN/ ====================================================
    //

        // #bugbug
        // We need to get the directory size to allocate a buffer
        // to this directory.

    //load bin/ dir.
    debug_print ("clone_and_execute_process: [FIXME] Loading BIN diretory \n");
        // IN: 
        // fat address, dir address, filename, file address.
        // OUT: 0=OK
    Status = fsLoadFile ( (unsigned long) VOLUME1_FAT_ADDRESS,  // fat address
                     (unsigned long) VOLUME1_ROOTDIR_ADDRESS,       // dir address. onde procurar.  
                     32, //#bugbug: Number of entries. 
                     (unsigned char *) "BIN        ",               // dir name 
                     (unsigned long) dir_address,                  // addr. Onde carregar.
                     BUGBUG_OVERFLOW );                  
    if(Status!=0){ 
        debug_print("clone_and_execute_process: [FAIL] Couldn't load BIN folder\n");
        kfree(dir_address); 
        goto fail;
    }

    // Procura o nome no diretorio carregado
    __Status = (int) search_in_dir ( name, dir_address );
    if (__Status == 1){ goto __found; }
    */
 


    /*
    //
    // == Search in SBIN/ =======================================================
    //

        // #bugbug
        // We need to get the directory size to allocate a buffer
        // to this directory.


    //load bin/ dir.
    debug_print ("clone_and_execute_process: [FIXME] Loading SBIN directory \n");
        // IN: 
        // fat address, dir address, filename, file address.
        // OUT: 0=OK
    Status = fsLoadFile ( (unsigned long) VOLUME1_FAT_ADDRESS,  // fat address
                     (unsigned long) VOLUME1_ROOTDIR_ADDRESS,       // dir address. onde procurar.  
                     (unsigned char *) "SBIN       ",               // dir name 
                     (unsigned long) dir_address );                 // addr. Onde carregar. 
    if(Status!=0){ 
        debug_print("clone_and_execute_process: [FAIL] Couldn't load SBIN folder\n");
        kfree(dir_address); 
        goto fail;
    }

    // Procura o nome no diretorio carregado
    __Status = (int) search_in_dir ( name, dir_address );
    if (__Status == 1){ goto __found; }
    */


    //
    // == Fail =====================================
    //
    
    // Falhou a busca em todos os diretorios procurados.
    
    debug_print ("clone_and_execute_process: [FAIL] File not found!\n");
    printf      ("clone_and_execute_process: [FAIL] File not found!\n");
    goto fail;

    //
    // == go ====================================
    //

__found:

	//unsigned long old_image_pa; //usado para salvamento.

	//#debug message.
    //printf ("do_clone_execute_processs: clona o pai e executa o filho..\n");


    //
    // == Current ===========================================
    //

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
        //old_dir_entry1 = dir[1]; //salvando
        
       if( (void*) Current->DirectoryVA == NULL )
            panic("clone_and_execute_process: Current->DirectoryVA\n");

        

        // Salvando o endereço fisico da imagem 
        // que existe no processo.
        // old_image_pa = (unsigned long) virtual_to_physical ( Current->Image, gKernelPageDirectoryAddress ); 

        //#debug
        //printf(">>> check current process: %d %d \n", current_process, Current->pid );
        
        goto do_clone;
        // ...
    };


    //
    // == Clone =========================================
    //

    // Cria uma estrutura do tipo processo, mas não inicializada.

do_clone:

    Clone = (struct process_d *) processObject();

    if ( (void *) Clone == NULL )
    {
        debug_print ("clone_and_execute_process: [FAIL] Clone\n");
        printf      ("clone_and_execute_process: [FAIL] Clone\n");
        goto fail;
    }

    // Obtêm um índice para um slot vazio na lista de processos.
    // Precisa estar dentro do range válido para processos
    // em ring3.

    PID = (int) getNewPID();

    if ( PID <= 0 || PID < USER_BASE_PID )
    {
        debug_print ("clone_and_execute_process: [FAIL] getNewPID\n");
        printf      ("clone_and_execute_process: [FAIL] getNewPID %d \n", 
            PID );
        goto fail;
    }

    Clone->used  = 1;
    Clone->magic = 1234;
    Clone->pid   = (pid_t) PID;
    
    // #todo: 
    // Deletar. Isso iremos herdar?
    Clone->uid = (uid_t) current_user;
    Clone->gid = (gid_t) current_group;


    // Register.

    // Saving the new process in the list.
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

        // Explicando:
        // Copia a imagem do processo atual e salva o endereço
        // da copia num elemento da estrutura passada como argumento.


    Status = processCopyMemory(Current);
    if ( Status != 0 ){
        panic ("clone_and_execute_process: [FAIL] processCopyMemory\n");
    }

    Status = processCopyProcess( Current->pid, Clone->pid );
    if ( Status != 0 ){
        panic ("clone_and_execute_process: [FAIL] processCopyProcess\n");
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

    unsigned long BUGBUG_IMAGE_SIZE_LIMIT = (unsigned long) (512 * 4096);


        //Status = (int) fsLoadFile ( 
        //                   VOLUME1_FAT_ADDRESS, 
        //                   VOLUME1_ROOTDIR_ADDRESS, 
        //                   filename, 
        //                   (unsigned long) Clone->Image );

        //Status = (int) fsLoadFile ( 
        //                   VOLUME1_FAT_ADDRESS, 
        //                   dir_address, 
        //                   filename, 
        //                   (unsigned long) Clone->Image );


    if( dir_address == 0 )
        panic("clone_and_execute_process: dir_address\n");

    if( (void*) Clone->Image == NULL )
        panic("clone_and_execute_process: Clone->Image\n");


    // Se falhar o carregamento. 
    // Vamos destruir a thread e o processo.


    Status = (int) fsLoadFile ( 
                       VOLUME1_FAT_ADDRESS, 
                       (unsigned long) dir_address,
                       32, //#bugbug: Number of entries. 
                       name, 
                       (unsigned long) Clone->Image,
                       BUGBUG_IMAGE_SIZE_LIMIT );
    
    if ( Status != 0 )
    {
        Clone->control->used = 0;
        Clone->control->magic = 0;
        Clone->control->state = DEAD;
        Clone->control == NULL;

        Clone->used = 0;
        Clone->magic = 0;  
        Clone = NULL;

        //#todo
        //check number of entries in the routine above 

        debug_print ("clone_and_execute_process: [FAIL] Couldn't load the file\n");
        printf      ("clone_and_execute_process: [FAIL] Couldn't load the file %s\n", 
            filename );
        goto fail;
   }


    // Check ELF signature.
    // OK. O comando existe e o arquivo foi carregado, mas 
    // precisamos saber se a assinatura de ELF é válida.
    // Assinatura ELF inválida. 
    // Vamos matar a thread e o processo.

    Status = (int) fsCheckELFFile ( (unsigned long) Clone->Image );
    
    if ( Status < 0 )
    {
        // Kill thread.
        Clone->control->used = 0;
        Clone->control->magic = 0;
        Clone->control == NULL;

        // Kill process.
        Clone->used = 0;
        Clone->magic = 0; 
        Clone = NULL;

        debug_print ("clone_and_execute_process: [FAIL] ELF fail \n");
        printf      ("clone_and_execute_process: [FAIL] ELF fail \n");
        goto fail;
    }


        // >> Page table:
        // Remapeando a imagem, mas agora no diretório de páginas
        // do processo filho.
        // Lembrando que já criamos o diretório de páginas para o clone.
        // ENTRY_USERMODE_PAGES, esse número de entrada é para o 
        // endereço virtual padrão para aplicativos em ring3, 0x400000.

       // #todo
       // Retornaremos o endereço virtual da pagetable.
       // See: core/ps/x86/pages.c

    if( (void*) Clone->DirectoryVA == NULL )
        panic("clone_and_execute_process: Clone->DirectoryVA\n");

    if( (void*) Clone->ImagePA == NULL )
        panic("clone_and_execute_process: Clone->ImagePA\n");

    // page table.

    __pt = (void *) CreatePageTable ( 
                        (unsigned long) Clone->DirectoryVA, 
                        ENTRY_USERMODE_PAGES, 
                        (unsigned long) Clone->ImagePA );

    if ( (void*) __pt == NULL )
        panic ("clone_and_execute_process: __pt");


        // Configurando o endereço virtual padrão para aplicativos.
        // Novo endereço virtual da imagem. Conseguimos isso 
        // por causa da criação da pagetable, logo acima.
        // # Caution
        // Entry point and stack.
        // We are clonning only the control thread.
        // The entry point in the start of the image. 0x401000.
        // And the stack ??

    Clone->Image        = (unsigned long) CONTROLTHREAD_BASE;        // 0x400000 
    Clone->control->eip = (unsigned long) CONTROLTHREAD_ENTRYPOINT;  // 0x401000

 
        // #bugbug
        // #todo
        // Ok mesma coisa precisa ser feito para o endereço
        // virtual da pilha.

        // #Cuidado
        // Heap for Clone.
        // Essa é a rotina usada na criação de processo 
        // pra gerar um heap para ele.
        // Vamos tentar usar isso na rotina de clonagem.


    if (g_heappool_va == 0)
        panic("clone_and_execute_process: g_heappool_va");

    if (g_heap_count == 0)
        panic("clone_and_execute_process: g_heap_count");

    if (g_heap_size == 0)
        panic("clone_and_execute_process: g_heap_size");


        // #bugbug
        // There is a limit here. End we will have a huge problem 
        // when reach it.


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
    strcpy ( Clone->__processname, (const char *) filename );   
    //Clone->processName_len = (size_t) strlen ( (const char *) filename );
    Clone->processName_len = (size_t) sizeof(Clone->__processname);

    //
    // Socket ============
    //

    for (sIndex=0; sIndex<32; ++sIndex){
        Clone->socket_pending_list[sIndex] = 0; 
    };

    Clone->socket_pending_list_head = 0;
    Clone->socket_pending_list_tail = 0;
    Clone->socket_pending_list_max  = 0; //atualizado pelo listen();


  //#bugbug: The priv socket ??

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
    
    SelectForExecution(Clone->control);


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



    // #debug: 
    // Para a máquina real.

    //printf ("clone_and_execute_process: [DEBUG] Returning to father\n");
    refresh_screen();

	// Return.
	// #obs:
	// Retornamos para o pai o PID do filho.
	// Igual acontece no fork().


	//pai
    current_process = Current->pid;
    current_thread  = Current->control->tid;
    
    //if ( current_process < 0 || current_thread < 0 )
    //    return -1;

    return (pid_t) Clone->pid;

fail:
    refresh_screen();
    return (pid_t) (-1);
}


//
// End.
//

