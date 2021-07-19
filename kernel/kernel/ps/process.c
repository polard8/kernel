

#include <kernel.h>


int caller_process_id;
int processNewPID;


// Clonning the current process and 
// executing the clone for the first time.
pid_t clone_and_execute_process ( const char *filename )
{

    //
    // ===== This is a work in progress !  ========================
    //

    // #todo
    // Estamos portando essa rotina do gramado de 32bit.
    // Tem muitas dependências para resolver.
    
    //debug_print ("clone_and_execute_process: [TODO] Porting from 32bit to 64bit\n");
    //return -1;

    // #bugbug (fs)
    // We need to get the fs directory size to allocate a buffer
    // to this fs directory.

    debug_print ("-----------------------------------------------\n");
    debug_print ("clone_and_execute_process: This is a work in progress \n");
    printf      ("-----------------------------------------------\n");
    printf      ("clone_and_execute_process: This is a work in progress\n");

    struct process_d *Current;  // The current process.
    struct process_d *Clone;    // The process we will create.

    // loop
    // Socket support.
    // indice usado na inicializaçao da lista de 
    // conexoes pendentes do processo servidor.
    register int sIndex=0;

    int Status = -1;
    int PID = -1;

    // # What is this?
    // The directory virtual address of the current process. ??
    unsigned long *pml4;



    // #bugbug
    // Only for the rootdir.
    // Maybe we need to receive this values 
    // from parameters.
    
    // File support.
    unsigned long dir_address = VOLUME1_ROOTDIR_ADDRESS;
    unsigned long dir_entries = FAT16_ROOT_ENTRIES;


    char *path;
    char *name;

    // page table.
    void *__pt;


    // #debug
    //debug_print ("clone_and_execute_process: [TODO] \n");
    //printf      ("clone_and_execute_process:\n");

//
// argument
//

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



//
// Loop
//

    // Search
    // Convertendo o formato do nome do arquivo.
    // >>> "12345678XYZ"
    // Procura o nome no diretório. 
    // Que em nosso caso ainda é o diretório raiz.

__search:

    // Convert
    fs_fntos ( (char *) name );

    // Search.
    Status = (int) search_in_dir ( name, dir_address );
    
    // Found.
    if (Status == 1)
    { 
        goto __found; 
    }
// Fail.
// Falhou a busca em todos os diretorios procurados.
    debug_print ("clone_and_execute_process: [FAIL] File not found!\n");
    printf      ("clone_and_execute_process: [FAIL] File not found!\n");
    goto fail;

//
// == go ====================================
//

// The file was found into the directory.

__found:

	//unsigned long old_image_pa; //usado para salvamento.

	//#debug message.
    //printf ("do_clone_execute_processs: clona o pai e executa o filho..\n");

//
// == Current process ===========================================
//

    // ## Current ##
    // Checando a validade do processo atual.

    if ( current_process < 0 ){
        printf ("clone_and_execute_process: [FAIL] current_process \n");
        goto fail;
    }

    Current = (struct process_d *) processList[current_process];

    if ( (void *) Current == NULL ){
        printf ("clone_and_execute_process: [FAIL] Current \n");
        goto fail;
    }else{
        if ( Current->used != TRUE || Current->magic != 1234 ){ 
            printf ("clone_and_execute_process: [FAIL] Current validation \n");
            goto fail;
        }

        // #test
        //pml4 = (unsigned long *) Current->pml4_VA;

        // Testing if the current process has a 
        // null pml4 virtual address.

        if( (void*) Current->pml4_VA == NULL ){
            printf ("clone_and_execute_process: [FAIL] Current->pml4_VA\n");
            goto fail;
        }

        // Salvando o endereço fisico da imagem 
        // que existe no processo.
        // old_image_pa = (unsigned long) virtual_to_physical ( Current->Image, gKernelPageDirectoryAddress ); 

        //#debug
        //printf(">>> check current process: %d %d \n", current_process, Current->pid );
        
        // Lets clone the current process.
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

// Get PID.
// Obtêm um índice para um slot vazio na lista de processos.
// Precisa estar dentro do range válido para processos
// em ring3.

    // Invalidate.
    Clone->pid = -1;

    // Get new pid.
    PID = (int) getNewPID();
    if ( PID <= 0 || PID < USER_BASE_PID )
    {
        debug_print ("clone_and_execute_process: [FAIL] getNewPID\n");
        printf      ("clone_and_execute_process: [FAIL] getNewPID %d \n", 
            PID );
        goto fail;
    }

    // Initializing the process structure.
    Clone->pid = (pid_t) PID;
    Clone->uid = (uid_t) current_user;
    Clone->gid = (gid_t) current_group;
    Clone->used  = TRUE;
    Clone->magic = 1234;

    // Saving the process pointer in the list.
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

    // #bugbug
    // Estamos usando o ponteiro Current, 
    // sem antes ao menos checarmos a validade.

    // Explicando:
    // Copia a imagem do processo atual e salva o endereço
    // da copia num elemento da estrutura passada como argumento.
    // #changeme: Essa rotina é um absurdo.

//
// Copy process image and stack.
//

    // [1]
    debug_print ("clone_and_execute_process: [1] Copying process image and stack.\n");
    printf      ("clone_and_execute_process: [1] Copying process image and stack.\n");
    Status = processCopyMemory(Current);
    if ( Status != 0 ){
        panic ("clone_and_execute_process: [FAIL] processCopyMemory\n");
    }

//
// Copy process structure.
//

    // Copiar a estrutura de processo. Do atual para o clone que estamos criando.
    // #important: It will also copy the control thread.
    // [2]
    debug_print ("clone_and_execute_process: [2] Copying process structure\n");
    printf      ("clone_and_execute_process: [2] Copying process structure\n");
    Status = processCopyProcess( Current->pid, Clone->pid );
    if ( Status != 0 ){
        panic ("clone_and_execute_process: [FAIL] processCopyProcess\n");
    }

//
// Load image.
//

    // [3]
    debug_print ("clone_and_execute_process: [3] Loading the image.\n");
         printf ("clone_and_execute_process: [3] Loading the image.\n");

    // Loading from rootdir?

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


    if ( dir_address == 0 ){
        panic("clone_and_execute_process: dir_address\n");
    }

    if ( (void *) Clone->Image == NULL ){
        panic("clone_and_execute_process: Clone->Image\n");
    }

    Status = (int) fsLoadFile ( 
                       VOLUME1_FAT_ADDRESS, 
                       (unsigned long) dir_address,  //#bugbug: This is only for the root dir.
                       (unsigned long) dir_entries,  //#bugbug: Number of entries. 
                       name, 
                       (unsigned long) Clone->Image,
                       BUGBUG_IMAGE_SIZE_LIMIT );

    if ( Status != 0 )
    {
        // #todo
        // We need a helper function for that.
        
        
        // #??
        // Is this a valid thread at this moment?

        // Kill control thread
        Clone->control->used  = FALSE;
        Clone->control->magic = 0;
        Clone->control->state = DEAD;
        Clone->control == NULL;
        Clone->used  = FALSE;
        Clone->magic = 0;
        Clone = NULL;

        //#todo
        //check number of entries in the routine above 

        debug_print ("clone_and_execute_process: [FAIL] Couldn't load the file\n");
        printf      ("clone_and_execute_process: [FAIL] Couldn't load the file %s\n", 
            filename );
            
        goto fail;
   }

    // [4]
    debug_print ("clone_and_execute_process: [4] Check signature.\n");
    printf      ("clone_and_execute_process: [4] Check signature.\n");

    // Check ELF signature.
    // OK. O comando existe e o arquivo foi carregado, mas 
    // precisamos saber se a assinatura de ELF é válida.
    // Assinatura ELF inválida. 
    // Vamos matar a thread e o processo.

    Status = (int) fsCheckELFFile ( (unsigned long) Clone->Image );
    
    if ( Status < 0 )
    {
        Clone->control->used  = FALSE;
        Clone->control->magic = 0;
        Clone->control == NULL;
        Clone->used  = FALSE;
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
    // endereço virtual padrão para aplicativos em ring3, 0x200000.

    // #todo
    // Retornaremos o endereço virtual da pagetable.
    // See: core/ps/x86/pages.c

    if( (void*) Clone->pml4_VA == NULL ){
        panic("clone_and_execute_process: Clone->pml4VA\n");
    }

    if( (void*) Clone->ImagePA == NULL ){
        panic("clone_and_execute_process: Clone->ImagePA\n");
    }




//
// Breakpoint.
//


    debug_print ("clone_and_execute_process: [Breakpoint] This is a work in progress\n");
         printf ("clone_and_execute_process: [Breakpoint] This is a work in progress\n");
    debug_print ("clone_and_execute_process: [Breakpoint] CreateAndIntallPageTable \n");
    panic       ("clone_and_execute_process: [Breakpoint] CreateAndIntallPageTable \n");

    // =====================================
    // Levels: PML4, PDPT, PD, PT
    //
    // PML4 - Page Map Level 4
    // PDPT - Page Directory Pointer Table
    // PD   - Page Directory
    // PT   - Page Table    

    /*
    // See: pages.c
    __pt = CreateAndIntallPageTable (
               (unsigned long) Clone->pml4_VA,   // page map level 4
               (unsigned long) 0,                // index  
               (unsigned long) Clone->pdpt0_VA,  // page directory pointer table
               (unsigned long) 0, 
               (unsigned long) Clone->pd0_VA,         // page directory 
               (int)           ENTRY_USERMODE_PAGES,  // Install the pagetable into this entry of the page directory. See: gentry.h
               (unsigned long) Clone->ImagePA );      // region pa

    if ( (void*) __pt == NULL ){
        panic ("clone_and_execute_process: __pt\n");
    }
    */
    

    // Configurando o endereço virtual padrão para aplicativos.
    // Novo endereço virtual da imagem. 
    // Conseguimos isso por causa da criação da pagetable, logo acima.
    // # Caution
    // Entry point and stack.
    // We are clonning only the control thread.
    // The entry point in the start of the image. 0x201000.
    // And the stack ??

    Clone->Image        = (unsigned long) CONTROLTHREAD_BASE;        // 0x200000 
    Clone->control->rip = (unsigned long) CONTROLTHREAD_ENTRYPOINT;  // 0x201000

        // #bugbug
        // #todo
        // Ok mesma coisa precisa ser feito para o endereço
        // virtual da pilha.

        // #Cuidado
        // Heap for Clone.
        // Essa é a rotina usada na criação de processo 
        // pra gerar um heap para ele.
        // Vamos tentar usar isso na rotina de clonagem.


    if (g_heappool_va == 0){
        panic("clone_and_execute_process: g_heappool_va\n");
    }

    if (g_heap_count == 0){
        panic("clone_and_execute_process: g_heap_count\n");
    }

    if (g_heap_size == 0){
        panic("clone_and_execute_process: g_heap_size\n");
    }

    // #bugbug
    // There is a limit here. End we will have a huge problem 
    // when reach it.

    // Heap.

    Clone->Heap     = (unsigned long) g_heappool_va + (g_heap_count * g_heap_size);
    Clone->HeapSize = (unsigned long) g_heap_size;
    Clone->HeapEnd  = (unsigned long) (Clone->Heap + Clone->HeapSize); 
    g_heap_count++;

    // Stack

    // Stack for the clone. 
    Clone->control->rsp = CONTROLTHREAD_STACK;  //0x007FFFF0 
    Clone->Stack        = CONTROLTHREAD_STACK;  //0x007FFFF0
    Clone->StackSize = (32*1024);    //isso foi usado na rotina de alocação.
    Clone->StackEnd = ( Clone->Stack - Clone->StackSize );


//
// Process name.
//

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


    //
    // syscall counter
    // 

    Clone->syscalls_counter = 0;


    //
    // # HACK HACK
    //


    // [pai]
    Current->control->state = READY;

    // [filho]
    Clone->control->saved = 0;
    
    // Change the state to standby.
    // This thread is gonna run in the next taskswitch.
    // Or maybe in this moment.
    
    SelectForExecution (Clone->control);


    refresh_screen();

	//pai
    current_process = Current->pid;
    current_thread  = Current->control->tid;

    // paranoia.    
    if ( current_process < 0 || current_thread < 0 )
    {
        panic("clone_and_execute_process: current_process or current_thread\n");
    }


// #todo
// Antes de retornarmos, vamos exibir todas as informações
// sobre esse processo e essa thread.
// Isso ajudará a reorganizarmos essa rotina.

    

    // [4] done.
    debug_print ("clone_and_execute_process: [5] Done\n");
    debug_print ("---------------------------------------------\n");

    // Return child's PID.

    return (pid_t) Clone->pid;

fail:
    debug_print ("clone_and_execute_process: [X] Fail\n");
    debug_print ("---------------------------------------------\n");
    printf      ("clone_and_execute_process: [X] Fail\n");
    printf      ("---------------------------------------------\n");
    refresh_screen();
    return (pid_t) (-1);
}


unsigned long __GetProcessStats ( int pid, int index ){

    struct process_d *p;


    if (pid<0){
        panic ("__GetProcessStats: pid \n");
    }

    // Process

    p = (void *) processList[pid];

    if ( (void *) p == NULL ){
        printf ("__GetProcessStats: struct \n");
        return 0; 

    } else {
        //checar validade.
		//...
    };


    switch (index){

        case 1:  return (unsigned long) p->pid;  break; 
        case 2:  return (unsigned long) p->ppid;  break; 
        case 3:  return (unsigned long) p->uid;  break; 
        case 4:  return (unsigned long) p->gid;  break; 
        case 5:  return (unsigned long) p->state;  break; 
        case 6:  return (unsigned long) p->plane;  break; 
        case 7:  return (unsigned long) p->input_type;  break; 
        case 8:  return (unsigned long) p->personality;  break; 
        case 9:  return (unsigned long) p->appMode;  break; 

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

        //case 15:  return (unsigned long) p->DirectoryPA;  break;
        //case 16:  return (unsigned long) p->DirectoryVA;  break;
        
        case 17:  return (unsigned long) p->Image;  break;
        case 18:  return (unsigned long) p->ImagePA;  break;
        case 19:  return (unsigned long) p->childImage;  break;
        case 20:  return (unsigned long) p->childImage_PA;  break;
        case 21:  return (unsigned long) p->Heap;  break;
        case 22:  return (unsigned long) p->HeapEnd;  break;
        case 23:  return (unsigned long) p->HeapSize;  break;
        case 24:  return (unsigned long) p->HeapPointer;  break;
        case 25:  return (unsigned long) p->HeapLastValid;  break;
        case 26:  return (unsigned long) p->HeapLastSize;  break;
        case 27:  return (unsigned long) p->Stack;  break;
        case 28:  return (unsigned long) p->StackEnd;  break;
        case 29:  return (unsigned long) p->StackSize;  break;
        case 30:  return (unsigned long) p->StackOffset;  break;
        case 31:  return (unsigned long) p->iopl;  break;
        case 32:  return (unsigned long) p->base_priority;  break;
        case 33:  return (unsigned long) p->priority;  break;
        case 34:  return (unsigned long) p->step;  break;
        case 35:  return (unsigned long) p->quantum;  break;
        case 36:  return (unsigned long) p->timeout;  break;
        case 37:  return (unsigned long) p->ticks_remaining;  break;
        
        case 38:  
            return (unsigned long) p->profiler_percentage_running;
            break;

        case 39:
            return (unsigned long) p->profiler_ticks_running;
            break;

        case 40:
            return (unsigned long) p->profiler_last_ticks;
            break;

        case 41:  return (unsigned long) p->thread_count;  break;
        case 42:  return (unsigned long) p->bound_type;  break;
        case 43:  return (unsigned long) p->preempted;  break;
        case 44:  return (unsigned long) p->saved;  break;
        case 45:  return (unsigned long) p->PreviousMode;  break;
        case 46:  return (unsigned long) p->wait4pid;  break;
        case 47:  return (unsigned long) p->exit_code;  break;
        case 48:  return (unsigned long) p->signal;  break;
        case 49:  return (unsigned long) p->umask;  break;
        case 50:  return (unsigned long) p->dialog_address; break;
        case 51:  return (unsigned long) p->ImageSize;  break;
           
        // #todo:
        // Precisamos da quantidade de p�ginas usadas.
    
        // ...
    };

    return 0;
}

// Systemcall 882.
// Pega o nome do processo.
int getprocessname ( int pid, char *buffer ){

    struct process_d *p;

    char *name_buffer = (char *) buffer;

    //#todo
    //checar validade dos argumentos.

    if (pid<0){
        debug_print ("getprocessname: [FAIL] pid\n");
        return -1;
    }

    //#todo
    //buffer validation
 
    p = (struct process_d *) processList[pid]; 

    if ( (void *) p == NULL ){
        debug_print ("getprocessname: [FAIL] p\n");
        return -1;
    }else{
        if ( p->used != TRUE || p->magic != 1234 ){
            debug_print ("getprocessname: [FAIL] VALIDATION\n");
            return -1;
        }
        
        // 64 bytes
        strcpy ( name_buffer, (const char *) p->__processname );  
        
        //#bugbug: Provavelmente isso ainda nem foi calculado.
        return (int) p->processName_len;
    };

    return -1;
}

/*
 * processObject:
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

    int i = USER_BASE_PID;
    struct process_d  *p;

    while ( i < PROCESS_COUNT_MAX ){

        p = (struct process_d *) processList[i];

        if ( (void *) p == NULL ){ return (pid_t) i; }
        
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

    struct process_d  *P;

    P = (void *) processList[pid];

    if ( (void *) P == NULL ){
        return 0;
    }else{
        if ( P->used == 1 && P->magic == 1234 ){ return (int) 1234; }
    };

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
 ***********************************************************
 * init_processes:
 *    Inicaliza o process manager.
 *   #todo: rever esse nome, pois na verdade estamos inicializando variaveis 
 * usadas no gerenciamento de processo.
 */

// Called by init_microkernel in mk.c

void init_processes (void){

    register int i=0;

    debug_print("init_processes:\n");

    // Globals

	kernel_request = 0;    // O que fazer com a tarefa atual.
	
	
	// ?? Contagem de tempo de execu��o da tarefa atual.
	//n�o precisa, isso � atualizado pelo request()
	//kernel_tick = 0;                                 

    kernel_switch = 0;     // ?? Ativa o kernel switch do scheduler.

    current_process = 0;

    // Clear process list.
    i=0;
    while (i < PROCESS_COUNT_MAX){
        processList[i] = (unsigned long) 0;
        i++;
    };

    // More ?
}


/*
 * CloseAllProcesses:
 *     Bloqueia todos os processos da lista de processos.
 *     Menos o processo '0'.
 *     processCloseAllProcesses();    
 */

void CloseAllProcesses (void)
{
    int i=0;
    struct process_d  *P;

	// #importante:
	// Menos o 0, pois � o kernel. 

    //Pega, bloqueia e tira da lista.
    for ( i=1; i < PROCESS_COUNT_MAX; i++ )
    {
        P = (void *) processList[i];
        P->state = PROCESS_BLOCKED;
        
        // Not kernel.
        if (i != 100){
            processList[i] = (unsigned long) 0;
        }
    };

    //Check process 0.
    P = (void *) processList[0];

    if ( (void *) P == NULL ){
        panic ("CloseAllProcesses: P\n");
    }

    // #bugbug
    // The kernel is process 100.

    P = (void *) processList[100];

    if ( (void *) P == NULL ){
        panic ("CloseAllProcesses: kernel\n");
    }
}

// usado pelo comando "current-process" no shell
void show_currentprocess_info (void){

    struct process_d  *Current;


    if ( current_process < 0 || current_process >= PROCESS_COUNT_MAX )
    {
        //printf("show_process_information: current_process fail\n");
        return;
    }


	//Struct.
    Current = (void *) processList[current_process];

    if ( (void *) Current == NULL ){
        printf ("show_currentprocess_info: [FAIL] Current \n");
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
        //printf (">>DirectoryPA={%x} \n", Current->DirectoryPA );
        //printf (">>DirectoryVA={%x} \n", Current->DirectoryVA );

		//Heap and stack.
        printf("Heap={%x}  HeapSize={%d KB}  \n", Current->Heap, 
            Current->HeapSize );

        printf("Stack={%x} StackSize={%d KB} \n", Current->Stack, 
            Current->StackSize );

		//...
    };

    refresh_screen();
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

void show_process_information (void)
{
    // loop
    int i=0;
    struct process_d *p;

    printf ("show_process_information: \n");


    for ( i=0; i<PROCESS_COUNT_MAX; i++ )
    {

        p = (void *) processList[i];

        if ( (void *) p != NULL && 
                      p->used  == TRUE && 
                      p->magic == 1234 )
        { 

            //printf("\n");
            printf("\n=====================================\n");
            printf(">>[%s]\n", p->__processname);
            printf("PID=%d PPID=%d \n", p->pid,  p->ppid );
            
            printf("image-base =%x image-size =%d \n", 
                p->Image, p->ImageSize );
            printf("heap-base  =%x heap-size  =%d \n", 
                p->Heap,  p->HeapSize );
            printf("stack-base =%x stack-size =%d \n", 
                p->Stack, p->StackSize );

            //printf("dir-pa=%x dir-va=%x \n", 
            //    p->DirectoryPA, p->DirectoryVA );

            printf("iopl=%d prio=%d state=%d \n", 
                p->iopl, p->priority, p->state );

            printf("syscalls = { %d }\n", p->syscalls_counter );
        }
    // Nothing.
    };

    refresh_screen();
}



// Create process
struct process_d *create_process ( 
    struct room_d    *room,
    struct desktop_d *desktop,
    struct window_d  *window,
    unsigned long base_address, 
    unsigned long priority, 
    int ppid, 
    char *name, 
    unsigned long iopl,
    unsigned long pml4_va )
{

    struct process_d  *Process;
    pid_t PID = -1;

    // Para a entrada vazia no array de processos.
    struct process_d *EmptyEntry; 
    
    // loop
    register int i=0;

    // loop
    // indice usado na inicializaçao da lista de 
    // conexoes pendentes do processo servidor.
    register int sIndex=0;

    unsigned long BasePriority=0;
    unsigned long Priority=0;



    debug_print ("create_process: #todo\n");
    printf      ("create_process: #todo\n");


    //=================================
    // check parameters

    if( (void*) room == NULL ){
        debug_print ("create_process: [FIXME] room parameter is NULL\n");
    }
    
    if( (void*) desktop == NULL ){
        debug_print ("create_process: [FIXME] desktop parameter is NULL\n");
    }
    
    if( (void*) window == NULL ){
        debug_print ("create_process: [FIXME] window parameter is NULL\n");
    }

    // #todo
    // Maybe the virtual 0 is n option in the future. Maybe.
    if( base_address == 0 ){
        panic ("create_process: [ERROR] base_address\n");
    }

    if( ppid < 0 ){
        panic ("create_process: [ERROR] ppid\n");
    }
  
    if( (void*) name == NULL ){
        panic ("create_process: [ERROR] name\n");
    }
  
    if( *name == 0 ){
        panic ("create_process: [ERROR] *name\n");
    }

    if( pml4_va == 0 ){
        panic ("create_process: [ERROR] pml4_va\n");
    }

    // ...
    //=================================

	// @todo:
	// Melhorar esse esquema de numera��o e 
	// contagem de processos criados.
	// processNewPID � global ?

    if ( processNewPID < USER_BASE_PID || 
         processNewPID >= PROCESS_COUNT_MAX )
    {
        processNewPID = (int) USER_BASE_PID;
    }

    // Base priority.
    // Please, don't inherit base priority!

    BasePriority = (unsigned long) PRIORITY_NORMAL; 
    Priority     = (unsigned long) priority;

//
// Process
//
    Process = (void *) kmalloc ( sizeof(struct process_d) );

    // #todo: 
    // Aqui pode retornar NULL.
    if ( (void *) Process == NULL ){
        panic ("create_process: Process\n");
    }

//get_next:

	// Get empty.
	// Obt�m um �ndice para um slot vazio na lista de processos.
	// Se o slot estiver ocupado tentaremos o pr�ximo.
	// Na verdade podemos usar aquela fun��o que procura por um vazio. 

    while (1){

        PID = (int) getNewPID();

        if ( PID <= 0 || PID >= PROCESS_COUNT_MAX )
        {
            debug_print ("create_process: [FAIL] getNewPID \n");
            printf      ("create_process: [FAIL] getNewPID %d \n", PID);
            goto fail;
        }

        EmptyEntry = (void *) processList[PID];
 
        if ( (void *) EmptyEntry == NULL ){ break; }
    };
 
// ====================

    Process->objectType  = ObjectTypeProcess;
    Process->objectClass = ObjectClassKernelObjects;
    Process->used  = TRUE;
    Process->magic = PROCESS_MAGIC;

    // Undefined
    Process->position = 0;

    Process->iopl = iopl; 

    // Not a protected process!
    Process->_protected = 0;

    processNewPID = (int) PID;
        
    // Identificadores.
    // PID. PPID. UID. GID.
    Process->pid  = (int) PID; 
    Process->ppid = (int) ppid; 
    Process->uid  = (int) GetCurrentUserId(); 
    Process->gid  = (int) GetCurrentGroupId(); 
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

    Process->processName_len = sizeof(Process->__processname);


    // Standard stream.
    // See: kstdio.c for the streams initialization.
    // #todo: We need a flag.
    
    if (kstdio_standard_streams_initialized != TRUE )
    {
        panic ("create_process: [ERROR] Standard stream is not initialized\n");
    }
    
    for ( i=0; i<32; ++i ){ Process->Objects[i] = 0; }

    if ( (void *) stdin == NULL ){
        panic ("create_process: [TEST] stdin");
    }

    if ( (void *) stdout == NULL ){
        panic ("create_process: [TEST] stdout");
    }

    if ( (void *) stderr == NULL ){
        panic ("create_process: [TEST] stderr");
    }

    Process->Objects[0] = (unsigned long) stdin;
    Process->Objects[1] = (unsigned long) stdout;
    Process->Objects[2] = (unsigned long) stderr;


    //Process->terminal =

//
// Banco de dados
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


//
// pml4_va
//

    if (pml4_va == 0)
    {
        debug_print("create_process: [FAIL] pml4_va\n");
        printf     ("create_process: [FAIL] pml4_va\n");
        goto fail;
        //return NULL;
    }

    Process->pml4_VA = (unsigned long) pml4_va;
    Process->pml4_PA = (unsigned long) virtual_to_physical ( 
                                               pml4_va, 
                                               gKernelPML4Address );

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

//
// Image
//

    // Endere�o virtual e endere�o f�sico.
    Process->Image   = (unsigned long) base_address;  
    Process->ImagePA = (unsigned long) virtual_to_physical ( 
                                           Process->Image, 
                                           gKernelPML4Address ); 
                                               


//
// Child image
//

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

    // #todo: 
    // Estrutura com informa��es sobre a imagem do processo.
    
    Process->image_info = NULL;


//
// == Heap and Stack ===========
//

    // #obs: 
    // O 'endereço virtual' do heap e da stack dos processos serão 
    // os mesmos para todos os processos, assim como o 'endereço virtual' 
    // de carregamento da imagem.

    // #todo:
    // #bugbug: 
    // O Heap e a Stack devem estar dentro da 
    // área de memória do processo.
    // #wrong: Uma pagetable do diretório é para o heap e outra para a stack.
    // #wrong: Cada pagetable no diretório do processo é pra uma coisa.

    // ## HEAP ##

    // directory va, index, region pa
    //CreatePageTable ( Process->DirectoryVA, 512, 0 );

    //Process->Heap = (unsigned long) 0x00400000; //funciona
    //Process->Heap = (unsigned long) 0xC0C00000; //funciona

    // g_heappool_va
    // endere�o virtual do pool de heaps.
    // os heaps nessa �rea ser�o dados para os processos.
    // base + (n*size)

    if ( g_heap_count < 0 || 
         g_heap_count >= g_heap_count_max )
    {
        debug_print ("create_process: [FIXME] g_heap_count limits\n");
        //panic ("create_process: [FAIL] g_heap_count limits\n");
    }

    // #atenção
    // Estamos usando o heappool pra pegarmos esses endereços.
    // me parece que isso é memória compartilhada em ring3
    // e que o malloc da libc está usando isso sem problemas.

    // #todo: 
    // #test: A stack de um process recem criado
    // poderia ficar no fim de seu heap ???

    if (g_heappool_va == 0){
        debug_print ("clone_and_execute_process: g_heappool_va\n");
        //panic ("clone_and_execute_process: g_heappool_va\n");
    }

    // Ignoraremos esse pois vai falhar na criacao do primeiro heap.
    //if (g_heap_count == 0)
        //panic("clone_and_execute_process: g_heap_count");

    if (g_heap_size == 0){
        debug_print ("clone_and_execute_process: g_heap_size\n");
        //panic ("clone_and_execute_process: g_heap_size\n");
    }

    // #bugbug
    // There is a limit here. End we will have a huge problem 
    // when reach it.

    Process->Heap     = (unsigned long) g_heappool_va + (g_heap_count * g_heap_size);
    Process->HeapSize = (unsigned long) g_heap_size;
    Process->HeapEnd  = (unsigned long) (Process->Heap + Process->HeapSize); 
    g_heap_count++;


    // Endere�o do in�cio da Stack do processo.
    // Endere�o do fim da stack do processo.
    // Tamanho da pilha, dada em KB.
    // #importante: 
    // Deslocamento do endere�o do in�cio da pilha em rela��o 
    // ao in�cio do processo. 

    // #bugbug
    // Isso indica que a stack será no endereço virtual tradicional,
    // porém qual é o endereço físico da stack do processo criado
    // com essa rotina.
    // #bugbug: Com esse erro todos os processo criados
    // estão usando a mesma stack, pois todas apontam para o mesmo
    // endereço físico.


//
// #bugbug #bugbug #bugbug #bugbug
//

    // Wrong !!!!!!!!!!!!!!!!!!!!

    Process->Stack       = (unsigned long) UPROCESS_DEFAULT_STACK_BASE; 
    Process->StackSize   = (unsigned long) UPROCESS_DEFAULT_STACK_SIZE; //?? usamos isso na hora de criar a stack?? 
    Process->StackEnd    = (unsigned long) (Process->Stack - Process->StackSize);  
    Process->StackOffset = (unsigned long) UPROCESS_DEFAULT_STACK_OFFSET;  //??


//
// PPL - (Process Permition Level).(gdef.h)
//

    // Determina as camadas de software que um processo ter� acesso irrestrito.
    // Process->ppl = pplK0;

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

//
// Priority
//
    Process->base_priority = (unsigned long) BasePriority;
    Process->priority      = (unsigned long) Priority;

    //Que tipo de scheduler o processo utiliza. (rr, realtime ...).
    //Process->scheduler_type = ; 
    
    // Syscalls counter.
    Process->syscalls_counter = 0;

    // #todo
    // Counters

    //Process->step
    //Process->quantum
    //Process->timeout
    //Process->ticks_remaining

    //As threads do processo iniciam com esse quantum.
    //Process->ThreadQuantum   

//
// == Thread =====================
//

    //Process->threadCount = 0;    //N�mero de threads do processo.
    //Process->tList[32] 

    Process->threadListHead = NULL;
    Process->control = NULL;

    //Process->event

    // #importante
    // user session, room and desktop.

    // #bugbug: 
    // N�o temos informa��o sobre a user session, 
    // devemos pegar a estrutura de current user session. 
    // Para isso ela deve ser configurada na inicializa��o do gws,
    // antes da cria��o dos processo.

//
// Security
//

    Process->usession = CurrentUserSession;  // Current.
    Process->room     = room;                // Passado via argumento.
    Process->desktop  = desktop;             // Passado via argumento.


    // absolute pathname and relative pathname. 

    Process->file_root = (file *) 0;
    Process->file_cwd  = (file *) 0;
    Process->inode_root = (struct inode_d *) 0;
    Process->inode_cwd  = (struct inode_d *) 0;

    // wait4pid: 
    // O processo esta esperando um processo filho fechar.
    // Esse � o PID do processo que ele est� esperando fechar.

    Process->wait4pid = (pid_t) 0;
        
    // Número de processos filhos.
    Process->nchildren = 0;

    Process->zombieChildListHead = NULL;
    Process->exit_code = 0;

    // ?? 
    // Procedimento eem ring 0 por enquanto.
    //Process->dialog_address = (unsigned long) &system_procedure;

    // Signal
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

//
// == Socket ===================================
//

    // loop
    // pending connections;
    
    for ( 
        sIndex = 0; 
        sIndex < SOCKET_MAX_PENDING_CONNECTIONS; 
        ++sIndex )
    {
        Process->socket_pending_list[sIndex] = 0; 
    };

    Process->socket_pending_list_head = 0;
    Process->socket_pending_list_tail = 0;
    Process->socket_pending_list_max  = 0;  // atualizado pelo listen();

//
// tty support
//

    //printf ("create_process: calling tty_create[DEBUG]\n");

    Process->tty = ( struct tty_d *) tty_create(); 

    if ( (void *) Process->tty == NULL ){
        panic ("create_process: Couldn't create tty\n");
    }
    tty_start(Process->tty);

//
// Navigation
//
    Process->prev = NULL; 
    Process->next = NULL; 

    // Register
    // List
    // Coloca o processo criado na lista de processos.

    processList[PID] = (unsigned long) Process;

    // #todo
    // last_created = PID;
    
    // #debug
    debug_print ("create_process: done\n");
    printf ("create_process: done\n");

    // ok
    return (void *) Process;

// Fail

fail:
    //Process = NULL;
    refresh_screen();
    return NULL;
}


unsigned long GetProcessPML4_PA ( struct process_d *process )
{
    if( (void *) process != NULL )
    {
        //@todo: checar used e magic.
        return (unsigned long) process->pml4_PA;
    }

    // fail
    return (unsigned long) 0;
}

unsigned long GetProcessPML4_VA ( struct process_d *process )
{
    if( (void *) process != NULL )
    {
        //@todo: checar used e magic.
        return (unsigned long) process->pml4_VA;
    }

    // fail
    return (unsigned long) 0;
}


// VA, I guess.
unsigned long GetProcessHeapStart ( pid_t pid )
{
    struct process_d  *process;


    debug_print ("GetProcessHeapStart:\n");

    // #debug
    printf ("GetProcessHeapStart: [DEBUG] pid %d\n", pid);
    refresh_screen();

    // Limits

    if ( pid < 0 || pid >= PROCESS_COUNT_MAX )
    {
        debug_print ("pid\n");
        goto fail; 
    }

    process = (struct process_d *) processList[pid];
    
    if ( (void *) process == NULL )
    {
        debug_print ("process\n");
        goto fail;
    }else{

        if ( process->used != 1 || process->magic != 1234 )
        {
            debug_print ("process validation\n");
            goto fail;
        }

        // Ok.
        return (unsigned long) process->Heap;
    };

fail:
    debug_print ("GetProcessHeapStart: fail\n");
    panic       ("GetProcessHeapStart: fail\n");
    return (unsigned long) 0;
}


void 
SetProcessPML4_VA ( 
    struct process_d *process, 
    unsigned long va )
{
    if ( (void *) process != NULL ){
        process->pml4_VA = (unsigned long) va;  
    }
}

void 
SetProcessPML4_PA ( 
    struct process_d *process, 
    unsigned long pa )
{
    if ( (void *) process != NULL ){
        process->pml4_PA = (unsigned long) pa;  
    }
}

int get_caller_process_id (void)
{
    return (int) caller_process_id;
}

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

int init_process_manager (void)
{
    caller_process_id = (int) 0;
    processNewPID = (int) USER_BASE_PID;

	//...

    return 0;
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

// Explicando:
// Copia a imagem do processo atual e salva o endereço
// da copia num elemento da estrutura passada como argumento.

// OUT:
// 

int processCopyMemory ( struct process_d *process )
{
    unsigned long __new_base=0;    // base
    unsigned long __new_stack=0;   // stack

    if ( (void *) process == NULL )
    {
        printf ("processCopyMemory: [FAIL] process \n");
        refresh_screen();
        return (int) (-1);
    }

//
// Image base
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

    int number_of_pages = 0;

    // Quantas páginas temos em 200KB?
    number_of_pages = (int) (200*1024)/4096;

    __new_base = (unsigned long) allocPages(number_of_pages); 
    if ( __new_base == 0 )
    {
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

    // Quantas páginas temos em 32KB?
    number_of_pages = (int) (32*1024)/4096;

    __new_stack = (unsigned long) allocPages(number_of_pages); 

    if ( __new_stack == 0 )
    {
        printf ("processCopyMemory: __new_stack fail\n");
        refresh_screen();
        return (int) (-1);
    }


//
// == Copying memory ======================================
//

    // Copying base and stack.
    // Copiando do processo atual para o buffer que alocamos
    // logo acima.

    // Copia a imagem do processo.
    // Copia do início da imagem. 200KB.
    memcpy ( 
        (void *) __new_base,  
        (const void *) CONTROLTHREAD_ENTRYPOINT, 
        (200*1024) );

    // Copia a pilha do process.
    // Copia do fim da stack. 32KB.
    memcpy ( 
        (void *) __new_stack, 
        (const void *) ( CONTROLTHREAD_STACK-(32*1024) ), 
        (32*1024) );

//
// Getting the physical addresses.
//

// Obtendo o edereço físico da base da imagem e da pilha.

    unsigned long new_base_PA  = (unsigned long) virtual_to_physical ( __new_base, gKernelPML4Address ); 
    unsigned long new_stack_PA = (unsigned long) virtual_to_physical ( __new_stack, gKernelPML4Address ); 

    if ( new_base_PA == 0 ){
        printf("processCopyMemory: new_base_PA\n");
        refresh_screen();
        return -1;
    }
    
    if ( new_stack_PA == 0 ){
        printf("processCopyMemory: new_stack_PA\n");
        refresh_screen();
        return -1;
    }

    // #debug
    //refresh_screen();
    //while(1){}
    
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

    // Salvando os endereços virtuais onde carregamos a imagem e a pilha.
    process->childImage  = (unsigned long) __new_base;
    process->childStack  = (unsigned long) __new_stack;

    // Salvando endereços físicos obtidos anteriormente.  
    // Esses endereços representam a base da imagem e o inicio da pilha.
    process->childImage_PA = (unsigned long) new_base_PA;
    process->childStackPA  = (unsigned long) new_stack_PA;

    // #debug
    // Showing the addresses of base and stack pointers.

    printf("processCopyMemory: new base PA %x | new stack PA %x \n",
        new_base_PA, new_stack_PA );

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

// Called by clone_and_execute_process at clone.c

// #
// It will also copy the control thread.

// IN:
// p1 = atual.
// p2 = clone. 

// OUT:
// 0 = ok
// 1 = fail

int processCopyProcess ( pid_t p1, pid_t p2 ){

    struct process_d  *Process1;
    struct process_d  *Process2;
    int Status=0;
    int i=0;
    unsigned long BasePriority=0;
    unsigned long Priority=0;


    // Balancing the priority.
    // Please, don't inherit base priority!

    BasePriority = (unsigned long) PRIORITY_NORMAL; 
    Priority     = (unsigned long) PRIORITY_NORMAL;


    if ( p1 == p2 ){
        printf ("processCopyProcess: [FAIL] same PID\n");  goto fail;
    }

    if ( p1 < 0 ){
        printf ("processCopyProcess: [FAIL] p1 limits\n"); goto fail;
    }

    if ( p2 < 0 ){
        printf ("processCopyProcess: [FAIL] p2 limits\n"); goto fail;
    }



    // ===========================
    // Check process 1.
    Process1 = (struct process_d *) processList[p1];

    // Check Process1
    if ( (void *) Process1 == NULL ){
        printf ("processCopyProcess: Process1\n"); goto fail;
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
        printf ("processCopyProcess: Process1\n"); goto fail; 
    }else{
        if ( Process2->used != 1 || Process2->magic != 1234 )
        {
           printf ("processCopyProcess: Process2 validation \n");
           goto fail;
        }
    };


//
// Copy
//

    // Object.
    Process2->objectType  = Process1->objectType;
    Process2->objectClass = Process1->objectClass;

    // O clone não inicializa na seção crítica, pois senão teríamos
    // dois processos na sessão crítica.
    Process2->_critical = 0;

    // Identificadores.
    Process2->pid  = (pid_t) p2;               // PID.  O pid do clone.
    Process2->ppid = (pid_t) Process1->pid;    // PPID. O parent do clone é o pid do pai. 
    Process2->uid  = (uid_t) Process1->uid;   // UID. 
    Process2->euid = (uid_t) Process1->euid;  // EUID. 
    Process2->ruid = (uid_t) Process1->ruid;  // RUID. 
    Process2->suid = (uid_t) Process1->suid;  // SUID. 
    Process2->gid  = (gid_t) Process1->gid;   // GID. 
    Process2->egid = (gid_t) Process1->egid;  // EGID. 
    Process2->rgid = (gid_t) Process1->rgid;  // RGID. 
    Process2->sgid = (gid_t) Process1->sgid;  // SGID. 
    Process2->pgrp = Process1->pgrp;

    // validation.
    Process2->used  = Process1->used;
    Process2->magic = Process1->magic;

    // State of process
    Process2->state = Process1->state;  

    // Plano de execução.
    Process2->plane = Process1->plane;

	//Process->name_address = NULL;

    Process2->framepoolListHead = Process1->framepoolListHead;

//
// pml4
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

    Process2->pml4_VA = (unsigned long) CloneKernelPML4();

    if ( (void *) Process2->pml4_VA == NULL ){
        panic ("processCopyProcess: [FAIL] pml4_VA\n");
    }

    Process2->pml4_PA = (unsigned long) virtual_to_physical ( 
                                              Process2->pml4_VA, 
                                              gKernelPML4Address ); 

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


    Process2->Image   = (unsigned long) Process1->childImage; // #bugbug: Esse endereço não é 0x400000
    Process2->ImagePA = (unsigned long) Process1->childImage_PA;
    Process2->childImage    = 0;
    Process2->childImage_PA = 0;


    // #bugbug
    // We simply can't do this!
    // Every process need your own heap!
    // The function that called up is gonna fix this later. :)
    // Simply initialize for now!

    //heap
    Process2->Heap     = (unsigned long) 0; //Process1->Heap;    
    Process2->HeapEnd  = (unsigned long) 0; // Process1->HeapEnd; 
    Process2->HeapSize = (unsigned long) 0; // Process1->HeapSize;

    //stack
    Process2->Stack       = (unsigned long) 0; // Process1->Stack;   
    Process2->StackEnd    = (unsigned long) 0; // Process1->StackEnd; 
    Process2->StackSize   = (unsigned long) 0; // Process1->StackSize;
    Process2->StackOffset = (unsigned long) 0; // Process1->StackOffset;


    Process2->iopl = Process1->iopl;


    // Priority.

    Process2->base_priority = (unsigned long) BasePriority;
    Process2->priority      = (unsigned long) Process1->priority;

    // == Security ====================================

    Process2->usession = Process1->usession;
    Process2->room     = Process1->room;
    Process2->desktop  = Process1->desktop;

    // absolute pathname and relative pathname. 

    Process2->file_root  = Process1->file_root;
    Process2->file_cwd   = Process1->file_cwd;

    Process2->inode_root = Process1->inode_root;
    Process2->inode_cwd  = Process1->inode_cwd;

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

    for (i=0; i<32; i++)
    {
        // Copy
        Process2->Objects[i] = Process1->Objects[i];
        
        // Updating the referency counter.
        // ??limits
        __f = (void*) Process2->Objects[i];
        if ((void*)__f!= NULL)
        {
            // Quantos descritores de arquivo apontam para essa mesma estrutura.
            __f->fd_counter++;
        }
    };


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


//
// == Clone the control thread =================================
//

    // Clonando a thread de controle.
    // obs: Isso precisa funcionar direito. Não podemos ficar sem isso.
    // See: thread.c
    
    Process2->control = (struct thread_d *) threadCopyThread( Process1->control );

    if ( (void *) Process2->control == NULL ){
        panic ("processCopyProcess: [FAIL] threadCopyThread \n");
    }

//
// Page Directory
//

	// #importante
	// Um diret�rio de p�ginas para a thread de controle.
	// O diret�rio de p�ginas da thread de controle ser� o mesmo
	// do processo.
	// � importante deixarmos esse endere�o na estrutura da thread, pois
	// � a� que o taskswitch espera encontra-lo.

    Process2->control->pml4_PA = Process2->pml4_PA;

//
// Owner PID
//

    Process2->control->ownerPID = Process2->pid;


    //#todo: review
    
    //?? herda a lista de threads ??
    Process2->threadListHead = Process1->threadListHead;
    Process2->zombieChildListHead = Process1->zombieChildListHead;
    Process2->dialog_address = Process1->dialog_address;


//
// == TTY ======================
//

    // Vamos criar uma tty para o processo clone.
    // Ela será uma tty privada, mas precisa ter um
    // uma estrutura de arquivo que aponte para ela
    // e um fd na lista de objetos abertos pelo processo.
  
    //++
    Process2->tty = ( struct tty_d *) tty_create();

    if ( (void *) Process2->tty == NULL ){
         panic ("processCopyProcess: Couldn't create TTY\n");
    }
    tty_start (Process2->tty);
    //--

    // panic()
    debug_print ("processCopyProcess: [FIXME] No slot for tty\n");
 
__OK:
    Process2->exit_code = Process1->exit_code;
    Process2->prev = Process1->prev; 
    Process2->next = Process1->next; 
    //Status = 0;
    return (int) 0;

// Fail

fail:
    Status = 1;  //-1 ??
    printf ("processCopyProcess: Fail\n");
    return (int) Status;
}




// Service 227
// Entering critical section.
// Close gate. Turn it FALSE.
void process_close_gate(int pid)
{
    struct process_d  *p;

    if (pid<0){
        panic ("process_close_gate: pid \n");
    }

// Process

    p = (void *) processList[pid];

    if ( (void *) p == NULL ){
        panic ("process_close_gate: p \n");
    } else {

        // todo: validation
        
        __spinlock_ipc = __GATE_CLOSED;  //0;
        criticalsection_pid = (pid_t) 0;
        p->_critical = FALSE;  //0;
    };
}


// Service 228
// Exiting critical section
// Open gate. Turn it TRUE.
void process_open_gate (int pid)
{
    struct process_d  *p;

    if (pid<0)
        panic ("process_open_gate: pid \n");

    // Process.

    p = (void *) processList[pid];

    if ( (void *) p == NULL ){
        panic ("process_open_gate: p \n");
    } else {

        // todo: validation
        
        __spinlock_ipc = __GATE_OPEN; //1;
        criticalsection_pid = (pid_t) pid;
        p->_critical = TRUE; //1;
    };
}

//=============

// Pega uma stream na lista de arquivos dado o fd.

file *process_get_file_from_pid ( pid_t pid, int fd )
{
    struct process_d *p;
    file *fp;

    if ( pid < 0){
        return NULL;
    }

    // Get process pointer.
    p = (struct process_d *) processList[ pid ];

    if (fd<0){
        return NULL;
    }

    // Get fp from list of open files.
    // #bugbug: Overflow.
    
    return ( file * ) p->Objects[fd];  
}

// Return the file pointer from a given fd.
// the fd represents a index in the object list of the
// current process.

file *process_get_file ( int fd )
{
    if( fd<0){
        return NULL;
    }

    return (file *) process_get_file_from_pid (current_process, fd );
}

// Get tty id.
// Pega o número da tty de um processo, dado o pid.
// Serviço: 266.

int process_get_tty (int pid)
{
    // Usada para debug.
  
    struct process_d *p;
    struct tty_d *tty;

    //#debug
    //printf ("process_get_tty: pid %d \n", pid);
    //refresh_screen();


    // #todo
    // Overflow ?
    
    if ( pid < 0 )
    {
        debug_print ("process_get_tty: pid \n");
        //printf ("pid fail\n");
        //refresh_screen();
        return -1;
    }


    p = (struct process_d *) processList[pid];

    if ( (void *) p == NULL )
    {
        debug_print ("process_get_tty: p \n");
        //printf ("p fail\n");
        //refresh_screen();
        return -1;
    }

    // Get the private tty.
    
    tty = p->tty;    

    if ( (void *) tty == NULL )
    {
        debug_print ("process_get_tty: tty fail\n");
        //printf ("tty fail\n");
        //refresh_screen();
        return -1;
    }


    //printf ("tty %d belongs to %d\n", tty->index, p->pid );
    //refresh_screen ();

    // #bugbug
    // Isso precisa ser o fd na lista de arquivos abertos 
    // pelo processo.
    //file *f;
    
    //f = ()

    return (int) tty->index;
} 































































































