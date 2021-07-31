


#include <kernel.h> 





// only the structure.
int copy_process_structure( pid_t p1, pid_t p2 )
{
    debug_print("copy_process: [todo]\n");
    return -1;
}

pid_t copy_process( const char *filename, unsigned long clone_flags )
{
    debug_print("copy_process: [todo]\n");
    return -1;
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


// ========
// pml4
    Process2->pml4_VA = (unsigned long) CloneKernelPML4();

    if ( (void *) Process2->pml4_VA == NULL ){
        panic ("processCopyProcess: [FAIL] pml4_VA\n");
    }

    Process2->pml4_PA = (unsigned long) virtual_to_physical ( 
                                              Process2->pml4_VA, 
                                              gKernelPML4Address ); 

// ========
//pdpt0
    Process2->pdpt0_VA = Process1->pdpt0_VA;
    Process2->pdpt0_PA = Process1->pdpt0_PA;

// ========
// pd0
    Process2->pd0_VA = Process1->pd0_VA;
    Process2->pd0_PA = Process1->pd0_PA;



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

        // Quantos descritores de arquivo apontam para essa mesma estrutura.
        if ( (void *)__f != NULL )
        {
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




// Clonning the current process and 
// executing the clone for the first time.
// #todo
// + We need a 'clone_flags' variable to known what we need to do.
// + Maybe create the names dup_process_struct and dup_thread_struct.
// + Create copy_files, copy_sighand, copy_signal, copy_thread
// total_forks ?
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

    // page table.
    void *__pt;

    // A place to save the pml4 of the current process.
    //unsigned long old_pml4=0;

    // #bugbug
    // Only for the rootdir.
    // Maybe we need to receive this values 
    // from parameters.


// Image support.
    unsigned long dir_address = VOLUME1_ROOTDIR_ADDRESS;
    unsigned long dir_entries = FAT16_ROOT_ENTRIES;
    char *path;
    char *name;


//
// Check parameters
//


    // file_name
    if ( (void*) filename == NULL ){
        panic ("clone_and_execute_process: [ERROR] filename\n");
    }
    if ( *filename == 0 ){
        panic ("clone_and_execute_process: [ERROR] *filename\n");
    }
    path = filename;
    name = filename;
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

    // Convert and search.

    fs_fntos ( (char *) name );
    Status = (int) search_in_dir ( name, dir_address );
    if (Status == 1){ 
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

    //printf (":)\n");
    //refresh_screen();
    //return -1;


	//unsigned long old_image_pa; //usado para salvamento.

	//#debug message.
    //printf ("do_clone_execute_processs: clona o pai e executa o filho..\n");

//
// == Current process ===========================================
//


    // Checando a validade do processo atual.

    Current = (struct process_d *) GetCurrentProcess();

    if ( (void *) Current == NULL ){
        printf ("clone_and_execute_process: [FAIL] Current \n");
        goto fail;
    }

    if ( Current->used != TRUE || Current->magic != 1234 ){ 
        printf ("clone_and_execute_process: [FAIL] Current validation \n");
        goto fail;
    }

    // Saving the pml4 of the current process. The caller.
    // We're gonna reload this one at the end of this routine.
    //old_pml4 = Current->pml4_PA;

    // Testing if the current process has a 
    // null pml4 virtual address.

    if( (void*) Current->pml4_VA == NULL ){
        printf ("clone_and_execute_process: [FAIL] Current->pml4_VA\n");
        goto fail;
    }

    if( (void*) Current->pdpt0_VA == NULL ){
        printf ("clone_and_execute_process: [FAIL] Current->pdpt0_VA\n");
        goto fail;
    }

    if( (void*) Current->pd0_VA == NULL ){
        printf ("clone_and_execute_process: [FAIL] Current->pd0_VA\n");
        goto fail;
    }

    // Salvando o endereço fisico da imagem 
    // que existe no processo.
    // old_image_pa = (unsigned long) virtual_to_physical ( Current->Image, gKernelPageDirectoryAddress ); 

    //#debug
    //printf(">>> check current process: %d %d \n", current_process, Current->pid );

    // ...

//
// == Clone =========================================
//

// Cria uma estrutura do tipo processo, mas não inicializada.

do_clone:


    // Switch
    //x64_load_pml4_table( kernel_mm_data.pml4_pa );


    //printf (":)\n");
    //refresh_screen();
    //return -1;

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
// Load image
//

    //printf (":)\n");
    //refresh_screen();
    //return -1;


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
    // See: fs.c

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


    // Isso foi obtido pela rotina de clonagem de processo,
    // juntamente com seu endereço físico.
    if( (void*) Clone->pml4_VA == NULL ){
        panic("clone_and_execute_process: [2nd time] Clone->pml4_VA\n");
    }

    if( (void*) Clone->pdpt0_VA == NULL ){
        panic("clone_and_execute_process: [2nd time] Clone->pdpt0_VA\n");
    }

    if( (void*) Clone->pd0_VA == NULL ){
        panic("clone_and_execute_process: [2nd time] Clone->pd0_VA\n");
    }

// ======

    if( (void*) Clone->ImagePA == NULL ){
        panic("clone_and_execute_process: Clone->ImagePA\n");
    }




//
// Breakpoint
//

    //printf (":)\n");
    //refresh_screen();
    //return -1;


    //debug_print ("clone_and_execute_process:  This is a work in progress\n");
    //     printf ("clone_and_execute_process:  This is a work in progress\n");
    debug_print ("clone_and_execute_process: Calling CreateAndIntallPageTable \n");
    printf      ("clone_and_execute_process: Calling CreateAndIntallPageTable :) \n");
    //panic       ("clone_and_execute_process: [Breakpoint] CreateAndIntallPageTable \n");

    // =====================================
    // Levels: PML4, PDPT, PD, PT
    //
    // PML4 - Page Map Level 4
    // PDPT - Page Directory Pointer Table
    // PD   - Page Directory
    // PT   - Page Table    


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

//
// Heap
//

    Clone->Heap     = (unsigned long) g_heappool_va + (g_heap_count * g_heap_size);
    Clone->HeapSize = (unsigned long) g_heap_size;
    Clone->HeapEnd  = (unsigned long) (Clone->Heap + Clone->HeapSize); 
    g_heap_count++;

//
// Stack
//

    // Stack for the clone. 
    Clone->control->rsp = CONTROLTHREAD_STACK;
    Clone->Stack        = CONTROLTHREAD_STACK;
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

    // Used by spawn.c
    Clone->control->new_clone = TRUE;

    //refresh_screen();

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

    

    // [5] done.
    debug_print ("clone_and_execute_process: [5] Done\n");
    debug_print ("---------------------------------------------\n");

    printf ("clone_and_execute_process: [5] Done\n");
    refresh_screen();

//
// Debug
//
    
    //printf ("\n");
    //printf ("--[ Debug ]---------------------------------\n");

    //printf ("\n");
    //current_process = Clone->pid;
    //show_currentprocess_info();

    //printf ("\n");
    //current_thread = Clone->control->tid;
    //show_reg(current_thread);

    // See: thread.c and spawn.c
    //Current->control->state = DEAD;
    //SelectForExecution(Clone->control);
    //KiSpawnThread(Clone->control->tid); 

    //printf ("--------------------------------------------\n");
    //printf ("\n");


    // #debug
    //refresh_screen();
    //while(1){}
    
    // Switch back
    //x64_load_pml4_table( old_pml4 );

    // Return child's PID.

    return (pid_t) Clone->pid;

fail:
//fail0:
    debug_print ("clone_and_execute_process: [X] Fail\n");
    debug_print ("---------------------------------------------\n");
    printf      ("clone_and_execute_process: [X] Fail\n");
    printf      ("---------------------------------------------\n");
    refresh_screen();

    // Nem chegamos a pegar o valor.
    // Nem mudar o pml4.
    //if (old_pml4 == 0){
    //    return (pid_t) (-1);
    //}

    // Switch back
    // Se falhamos logo após pegarmos o valor.
    //if (old_pml4 != 0){
    //    x64_load_pml4_table( old_pml4 );
    //}

    return (pid_t) (-1);
}







