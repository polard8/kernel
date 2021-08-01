


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


/*
// ========
// pml4
    Process2->pml4_VA = (unsigned long) CloneKernelPML4();

    if ( (void *) Process2->pml4_VA == NULL ){
        panic ("processCopyProcess: [FAIL] pml4_VA\n");
    }

    Process2->pml4_PA = (unsigned long) virtual_to_physical ( 
                                              Process2->pml4_VA, 
                                              gKernelPML4Address ); 
*/

/*
// ========
//pdpt0
    Process2->pdpt0_VA = Process1->pdpt0_VA;
    Process2->pdpt0_PA = Process1->pdpt0_PA;
*/

/*
// ========
// pd0
    Process2->pd0_VA = Process1->pd0_VA;
    Process2->pd0_PA = Process1->pd0_PA;
*/


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

// IN:
// filename = The name of the image file to load.
// pid      = The pid of the process we will clone.

// OUT:
// The pid of the clone or fail.

pid_t clone_and_execute_process ( const char *filename, pid_t pid )
{

    // Usado como armazenamento temporário de endereço físico de tabela.
    unsigned long phy=0;


//
// Tables
//

    // =====================================
    // Levels: PML4, PDPT, PD, PT
    //
    // PML4 - Page Map Level 4
    // PDPT - Page Directory Pointer Table
    // PD   - Page Directory
    // PT   - Page Table    


    void *_pml4;
    void *_pdpt;
    void *_pd;
    void *_pt;

    _pml4 = 0;
    _pdpt = 0;
    _pd   = 0; 
    _pt   = 0;


    // Copiar a tabela pml4 do kernel.
    _pml4 = (void *) CloneKernelPML4();

    if ( (void*) _pml4 == NULL ){
        panic("clone_and_execute_process: _pml4");
    }

    //printf ("_pml4: %x\n",_pml4);
    //refresh_screen();
    //while(1){}


    // #todo
    // Estamos portando essa rotina do gramado de 32bit.
    // Tem muitas dependências para resolver.
    
    //debug_print ("clone_and_execute_process: [TODO] Porting from 32bit to 64bit\n");
    //return -1;

    // #bugbug (fs)
    // We need to get the fs directory size to allocate a buffer
    // to this fs directory.

    struct process_d *p;      // The process we will clone.
    struct process_d *Clone;  // The process we will create.
    // loop
    // Socket support.
    // indice usado na inicializaçao da lista de 
    // conexoes pendentes do processo servidor.
    register int sIndex=0;
    int Status = -1;
    int PID = -1;



    // A place to save the pml4 of the current process.
    //unsigned long old_pml4=0;

    // #bugbug
    // Only for the rootdir.
    // Maybe we need to receive this values 
    // from parameters.


    debug_print ("-----------------------------------------------\n");
    debug_print ("clone_and_execute_process: This is a work in progress \n");
    printf      ("-----------------------------------------------\n");
    printf      ("clone_and_execute_process: This is a work in progress\n");


    //printf (":)\n");
    //refresh_screen();
    //return -1;

    //unsigned long old_image_pa; //usado para salvamento.

//
// == Current process ===========================================
//

    // Checando a validade do processo atual.

    if (pid<0 || pid >= PROCESS_COUNT_MAX){
        printf ("clone_and_execute_process: [FAIL] pid \n");
        goto fail;
    }

    p = (struct process_d *) processList[pid];

    if ( (void *) p == NULL ){
        printf ("clone_and_execute_process: [FAIL] p \n");
        goto fail;
    }

    if ( p->used != TRUE || p->magic != 1234 ){ 
        printf ("clone_and_execute_process: [FAIL] p validation \n");
        goto fail;
    }

    // Saving the pml4 of the current process. The caller.
    // We're gonna reload this one at the end of this routine.
    //old_pml4 = p->pml4_PA;

    // Testing if the current process has a 
    // null pml4 virtual address.

    if( (void*) p->pml4_VA == NULL ){
        printf ("clone_and_execute_process: [FAIL] p->pml4_VA\n");
        goto fail;
    }

    if( (void*) p->pdpt0_VA == NULL ){
        printf ("clone_and_execute_process: [FAIL] p->pdpt0_VA\n");
        goto fail;
    }

    if( (void*) p->pd0_VA == NULL ){
        printf ("clone_and_execute_process: [FAIL] p->pd0_VA\n");
        goto fail;
    }

    // Salvando o endereço fisico da imagem 
    // que existe no processo.
    // old_image_pa = (unsigned long) virtual_to_physical ( p->Image, gKernelPageDirectoryAddress ); 

    //#debug
    //printf(">>> check current process: %d %d \n", current_process, p->pid );

    // ...


    // [pai]
    p->control->state = READY;

     // pai
    current_process = p->pid;
    current_thread  = p->control->tid;

    if ( current_process < 0 || current_thread < 0 ){
        panic("clone_and_execute_process: current_process or current_thread\n");
    }


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

    // See: process.c

    Clone = (struct process_d *) __create_and_initialize_process_object();

    if ( (void *) Clone == NULL )
    {
        debug_print ("clone_and_execute_process: [FAIL] Clone\n");
        printf      ("clone_and_execute_process: [FAIL] Clone\n");
        goto fail;
    }
    


// ==============================
// pml4
// A tabela pml4 usada pelo clone.
// Ela é uma cópia da tabela do kernel.

    Clone->pml4_VA = (unsigned long) _pml4;
    
    if ( (void *) Clone->pml4_VA == NULL ){
        panic ("processCopyProcess: [FAIL] Clone->pml4_VA\n");
    }

    Clone->pml4_PA = (unsigned long) virtual_to_physical ( 
                                              Clone->pml4_VA, 
                                              gKernelPML4Address ); 

    // #debug
    // ok
    //printf ("Clone->pml4_VA: %x\n",Clone->pml4_VA);
    //printf ("Clone->pml4_PA: %x\n",Clone->pml4_PA);
    //refresh_screen();
    //while(1){}


// ==============================
// pdpt0
// A tabela pdpt usada pelo clone.
// Ela é uma cópia da tabela usada pelo processo pai

    Clone->pdpt0_VA = p->pdpt0_VA;
    Clone->pdpt0_PA = p->pdpt0_PA;

// ========
// pd0
// A tabela do pd do clone.
// Ela é uma cópia da tabela usada pelo processo pai.

    Clone->pd0_VA = p->pd0_VA;
    Clone->pd0_PA = p->pd0_PA;



// ==================================

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

    // Explicando:
    // Copia a imagem do processo atual e salva o endereço
    // da copia num elemento da estrutura passada como argumento.
    // See: process.c

    // Salvaremos as informações assim:
    // p->childImage    : Endereço virtual do buffer para a imagem do clone.
    // p->childStack    : Endereço virtual para a pilha em ring3 usada pelo clone.
    // p->childImage_PA : Endereço físico do buffer para a imagem do clone.
    // p->childStackPA  : Endereço físico para a pilha em ring3 usada pelo clone.

    // [1]
    // #bugbug: na verdade não estamos mais copiando e sim criando um endereçamento novo.
    debug_print ("clone_and_execute_process: [1] Copying process image and stack.\n");
    printf      ("clone_and_execute_process: [1] Copying process image and stack.\n");
    Status = __alloc_memory_for_image_and_stack(p);
    if ( Status != 0 ){
        panic ("clone_and_execute_process: [FAIL] __alloc_memory_for_image_and_stack\n");
    }

//
// Copy process structure.
//

    // Copiar a estrutura de processo. Do atual para o clone que estamos criando.
    // #important: It will also copy the control thread.
    // [2]
    debug_print ("clone_and_execute_process: [2] Copying process structure\n");
    printf      ("clone_and_execute_process: [2] Copying process structure\n");
    Status = processCopyProcess( p->pid, Clone->pid );
    if ( Status != 0 ){
        panic ("clone_and_execute_process: [FAIL] processCopyProcess\n");
    }


    // #debug
    // ok
    //printf ("Clone->pml4_VA: %x\n",Clone->pml4_VA);
    //printf ("Clone->pml4_PA: %x\n",Clone->pml4_PA);
    //refresh_screen();
    //while(1){}



    unsigned long __rip = (unsigned long) 0x201000;
    unsigned long __rsp = (unsigned long) (p->childStack + (30*1024));   // 32kb size

    // #debug
    //printf ("Stack : %x \n",__rsp);
    //refresh_screen();
    //while(1){}

    Clone->control = (struct thread_d *) threadCopyThread( p->control, __rip, __rsp );
    if ( (void *) Clone->control == NULL ){
        panic ("clone_and_execute_process: [FAIL] threadCopyThread \n");
    }


    // #debug
    // ok
    //printf ("Clone->pml4_VA: %x\n",Clone->pml4_VA);
    //printf ("Clone->pml4_PA: %x\n",Clone->pml4_PA);
    //refresh_screen();
    //while(1){}


    // # hack hack
    // Vamos herdar porque configuramos esses valores para o process clone.
    // Agora eles serão usados na thread de controle do clone.

    Clone->control->pml4_VA = Clone->pml4_VA;
    Clone->control->pml4_PA = Clone->pml4_PA;

    // #debug
    //printf ("Clone->control->pml4_VA: %x\n",Clone->control->pml4_VA);
    //printf ("Clone->control->pml4_PA: %x\n",Clone->control->pml4_PA);
    //refresh_screen();
    //while(1){}


    // A control thread do processo clone
    // está herdando as tabelas usadas por ele.
    
    Clone->control->pml4_PA  = Clone->pml4_PA;
    
    // Salvando o pid do owner.
    Clone->control->ownerPID = Clone->pid;


//
// Load image
//

    // Configurando os buffers.

    // No processo pai estava salvo o endereço virtual do buffer
    // reservado para a imagem do clone.
    Clone->Image   = (unsigned long) p->childImage;
    // Agora o endereço físico do buffer.
    Clone->ImagePA = (unsigned long) p->childImage_PA;

    if ( (void *) Clone->Image == NULL ){
        panic ("processCopyProcess: [FAIL] Clone->Image\n");
    }

    if ( (void *) Clone->ImagePA == NULL ){
        panic ("processCopyProcess: [FAIL] Clone->ImagePA\n");
    }

    // Carregando a imagem do clone no buffer criado para ela.

    // IN: name, image va.
    Status = (int) __load_image(filename,(unsigned long) Clone->Image);
    if ( Status != 0 ){
        debug_print ("clone_and_execute_process: [FAIL] Couldn't load the file\n");
        printf      ("clone_and_execute_process: [FAIL] Couldn't load the file %s\n", filename );
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
    if ( Status < 0 ){
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

//
// Check again
// 

    // Checando as tabelas principais novamente.

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



//
// pt
//

    // Page table para a imagem.
    // Vamos criar a pagetable e instalar o ponteiro da pegatable.

    // Mapeando a região usada pela imagem
    // com base no endereço físico que obtivemos anteriormente.

    // =====================================
    // Levels: PML4, PDPT, PD, PT
    //
    // PML4 - Page Map Level 4
    // PDPT - Page Directory Pointer Table
    // PD   - Page Directory
    // PT   - Page Table    

    // See: pages.c
    // OUT: Retorna o endereço virtual da pagetable criada.
    _pt = (void*) CreateAndIntallPageTable (
               (unsigned long) Clone->pml4_VA,   // page map level 4
               (unsigned long) 0,                // index  
               (unsigned long) Clone->pdpt0_VA,  // page directory pointer table
               (unsigned long) 0, 
               (unsigned long) Clone->pd0_VA,         // page directory 
               (int)           ENTRY_USERMODE_PAGES,  // Install the pagetable into this entry of the page directory. See: gentry.h
               (unsigned long) Clone->ImagePA );      // region pa

    if ( (void*) _pt == NULL ){
        panic ("clone_and_execute_process: _pt\n");
    }

    // #debug
    //printf ("New page table : %x \n", _pt);
    //refresh_screen();
    //while(1){}


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





//
// Process name.
//
    // name.
    strcpy ( Clone->__processname, (const char *) filename );   
    //Clone->processName_len = (size_t) strlen ( (const char *) filename );
    Clone->processName_len = (size_t) sizeof(Clone->__processname);



//
// Parent
//

    /*
    // [pai]
    p->control->state = READY;

     // pai
    current_process = p->pid;
    current_thread  = p->control->tid;

    if ( current_process < 0 || current_thread < 0 ){
        panic("clone_and_execute_process: current_process or current_thread\n");
    }
    */

//
// Clone
//

    // [filho]
    Clone->control->saved = 0;

    // Used by spawn.c
    Clone->control->new_clone = TRUE;

    // Change the state to standby.
    // This thread is gonna run in the next taskswitch.
    // Or maybe in this moment.

    SelectForExecution (Clone->control);

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


    printf ("\n");
    printf ("--[ Debug ]---------------------------------\n");

    //printf ("\n");
    //printf ("Original thread::\n");
    // ok: Esses são iguais, como deveria ser.
    //printf ("pml4_VA:%x  | pml4_PA:%x  \n",p->control->pml4_VA,  p->control->pml4_PA);
    // ok: Esses são iguais, como deveria ser.
    //printf ("pdpt0_VA:%x | pdpt0_PA:%x \n",p->control->pdpt0_VA, p->control->pdpt0_PA);
    // ok: Esses são iguais, como deveria ser.
    //printf ("pd0_VA:%x   | pd0_PA:%x   \n",p->control->pd0_VA,   p->control->pd0_PA);

    printf ("\n");
    printf ("Clone thread::\n");
    // ok: Esses são iguais, como deveria ser.
    printf ("pml4_VA:%x  | pml4_PA:%x  \n",Clone->control->pml4_VA,  Clone->control->pml4_PA);
    // ok: Esses são iguais, como deveria ser.
    printf ("pdpt0_VA:%x | pdpt0_PA:%x \n",Clone->control->pdpt0_VA, Clone->control->pdpt0_PA);
    // ok: Esses são iguais, como deveria ser.
    printf ("pd0_VA:%x   | pd0_PA:%x   \n",Clone->control->pd0_VA,   Clone->control->pd0_PA);

    //show_slot (p->control->tid);
    //show_reg  (p->control->tid);

    show_slot (Clone->control->tid);
    show_reg (Clone->control->tid);

    //printf ("\n");
    //current_process = Clone->pid;
    //show_currentprocess_info();

    printf ("--------------------------------------------\n");
    printf ("\n");

    // #debug
    refresh_screen();
    while(1){}
    
    
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






