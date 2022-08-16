
// clone.c

#include <kernel.h> 


int copy_process_in_progress=FALSE;


// #bugbug
// Na maquina real, o processo clone esta recebendo
// o mesmo pid do processo pai. Mas no qemu esta funcionando bem.


// Clonning the current process and 
// executing the clone for the first time.
// #todo
// + We need a 'clone_flags' variable to known what we need to do.
// + Maybe create the names dup_process_struct and dup_thread_struct.
// + Create copy_files, copy_sighand, copy_signal, copy_thread
// total_forks ?
// See: process.h for the flags.

// IN:
// filename = The name of the image file to load.
// pid      = The pid of the process we will clone.
// flags    = flags for clone types.

// #todo
// The stack for the process.
// Maybe it needs to reflect only the control thread.

// OUT:
// The pid of the clone or fail.

pid_t copy_process( 
    const char *filename, 
    pid_t pid, 
    unsigned long clone_flags )
{
    pid_t parent_pid = (pid_t) pid;    //parameter
    pid_t child_pid  = (pid_t) (-1);   //fail

    struct process_d *parent_process;  // The process we will clone.
    struct process_d *child_process;   // The process we will create.

    struct thread_d *parent_thread;
    struct thread_d *child_thread;

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
    _pd = 0;
    _pt = 0;


    copy_process_in_progress=TRUE;

// Copiar a tabela pml4 do kernel.
    _pml4 = (void *) CloneKernelPML4();
    if ( (void*) _pml4 == NULL ){
        panic("copy_process: _pml4\n");
    }

    //printf ("_pml4: %x\n",_pml4);
    //refresh_screen();
    //while(1){}

    //#debug
    //printf (" :) \n");
    //refresh_screen();
    //return 0;

// The new process will be in a different pid.
// We are clonning the thread.
    //if ( clone_flags & CLONE_THREAD ){
        //THIS IS A TEST
    //}

// #bugbug (fs)
// We need to get the fs directory size to allocate a buffer
// to this fs directory.


// loop
// Socket support.
// indice usado na inicializaçao da lista de 
// conexoes pendentes do processo servidor.
    register int sIndex=0;

    int Status = -1;

// A place to save the pml4 of the current process.
    //unsigned long old_pml4=0;

// #bugbug
// Only for the rootdir.
// Maybe we need to receive this values 
// from parameters.

    // #debug
    debug_print ("copy_process: This is a work in progress \n");
         //printf ("copy_process: This is a work in progress \n");

// pega
    pid_t current_process = (pid_t) get_current_process();

    //printf (":)\n");
    //refresh_screen();
    //return -1;

    //usado para salvamento.
    //unsigned long old_image_pa; 

//
// == Current process ===========================================
//

// parent_pid came from function parameters.

// parent pid.
    if ( parent_pid < 0 || 
         parent_pid >= PROCESS_COUNT_MAX )
    {
        printf("copy_process: parent_pid\n");
        goto fail;
    }

// parent process pointer.
    parent_process = (struct process_d *) processList[ parent_pid ];
    if ( (void *) parent_process == NULL )
    {
        printf("copy_process: parent_process\n");
        goto fail;
    }
    if ( parent_process->used != TRUE || 
         parent_process->magic != 1234 )
    {
        printf("copy_process: parent_process validation\n");
        goto fail;
    }

// cpl:
// Apenas processos em ring3 podem clonar por enquanto.
    if (parent_process->cpl != RING3){
        panic("copy_process: cpl != RING3\n");
    }

// iopl:
// #todo: Para o futuro, precisamos aceitar
// iopl 0, para termos mais proteção.
// #bugbug: Actually the caller is running with the iopl=0,
// but maybe the dispatcher is saving 
// this context in another variable.

    //if (parent_process->rflags_iopl != 3){
    //    panic("copy_process: iopl\n");
    //}

// Saving the pml4 of the current process. The caller.
// We're gonna reload this one at the end of this routine.

    //old_pml4 = parent_process->pml4_PA;

// Testing if the current process has a 
// null pml4 virtual address.

// pml4
    if( (void*) parent_process->pml4_VA == NULL )
    {
        printf ("copy_process: [FAIL] parent_process->pml4_VA\n");
        goto fail;
    }
// pdpt
    if( (void*) parent_process->pdpt0_VA == NULL )
    {
        printf ("copy_process: [FAIL] parent_process->pdpt0_VA\n");
        goto fail;
    }
// pd
    if( (void*) parent_process->pd0_VA == NULL )
    {
        printf ("copy_process: [FAIL] parent_process->pd0_VA\n");
        goto fail;
    }

// Salvando o endereço fisico da imagem 
// que existe no processo.

    // old_image_pa = (unsigned long) virtual_to_physical ( parent_process->Image, gKernelPageDirectoryAddress ); 

    //#debug
    //printf(">>> check current process: %d %d \n", current_process, parent_process->pid );

    // ...

//
// Parent's control thread
//
    parent_thread = (struct thread_d *) parent_process->control;
    
    if( (void*) parent_thread == NULL ){
        panic("copy_process: parent_thread\n");
    }

    if(parent_thread->magic!=1234){
        panic("copy_process: parent_thread validation\n");
    }

// cpl
// For now we can only clone ring 3 threads.
    if(parent_thread->cpl!=RING3)
        panic("copy_process: parent_thread->cpl\n");

// iopl
// #bugbug:
// For now, we can only clone threads in ring 3,
// with weak protection;
// #bugbug: Actually the initial iopl is 3, 
// but the app is changing its on iopl at the end
// of the rtl initialization.

    //if (parent_thread->rflags_initial_iopl != 3){
    //    panic("copy_process: parent rflags_initial_iopl\n");
    //}

//
// == PREEMPT ========
//

// [pai]
// Change the state of the parent's control thread.
// #bugbug: Por que?
// A rotina copy_process foi chamada por um processo em ring3
// via systemcall e não tem o seu contexto salvo na estrutura da thread,
// Uma systemcall vai retornar para o processo usando a rotina 
// em assembly e não as rotinas do taskswitch,
// Portanto, não mude o state da thread do processo pai.
// Apenas retorne para o processo depois da syscall.
// O processo filho ficara pronto e o scheduler 
// colocara ele pra rodar depois,

    parent_thread->state = RUNNING;
    
// O dono da parent thread tem que ser o processo pai.
    if( parent_thread->owner_pid != parent_process->pid )
    {
        panic("copy_process: parent_thread->owner_pid\n");
    }

// A thread que fez a chamada precisa ser
// a thread de controle do processo pai.
    if ( current_thread != parent_thread->tid ){
        panic("copy_process: current_thread mismatched\n");
    }

// O pid do processo pai.
    if ( parent_pid != parent_process->pid ){
        panic("copy_process: parent_pid mismatched\n");
    }

// Select the 
// new current process and the 
// new current thread.

// #todo: Isso pode ir para o fim da rotina?

//====

// Limits for the callers pid.
    if( parent_process->pid < 0 || 
        parent_process->pid >= PROCESS_COUNT_MAX )
    {
        panic("copy_process: parent_process->pid limits\n");
    }

// pid again.
// Tem que ser igual ao current_process que pegamos logo acima
// pois o pai tem que ser quem esta chamando.
    if( parent_process->pid != current_process ){
        panic("copy_process: parent_process->pid != current_process\n");
    }


//
// == child_process =========================================
//

do_clone:

    // Switch
    //x64_load_pml4_table( kernel_mm_data.pml4_pa );

    //printf (":)\n");
    //refresh_screen();
    //return -1;

// Worker
// See: 
// process.c

    child_process = 
        (struct process_d *) create_and_initialize_process_object();
    
    if ( (void *) child_process == NULL )
    {
        debug_print ("copy_process: child_process\n");
        printf      ("copy_process: child_process\n");
        goto fail;
    }
    
    if (child_process->magic!=1234)
    {
        debug_print ("copy_process: child_process validation\n");
        printf      ("copy_process: child_process validation\n");
        goto fail;
    }

// Personality first of all. 
// Because some features depends on that.

    child_process->personality = (int) parent_process->personality;

// pid

    child_pid = (pid_t) child_process->pid;

    if ( child_pid < 0 || 
         child_pid >= PROCESS_COUNT_MAX )
    {
        panic("copy_process: child_pid limits\n");
    }

// The child pid can't be the same of his father.
    if ( child_pid == parent_pid ){
        panic("copy_process: child_pid == parent_pid\n");
    }

// The child pid can't be the same of the kernel.
    if ( child_pid == GRAMADO_PID_KERNEL ){
        panic("copy_process: child_pid == GRAMADO_PID_KERNEL\n");
    }

// Breakpoint

    //#debug
    //printf (" :) \n");
    //refresh_screen();
    //return 0;

//
// Heap
//

// ==============================
// pml4
// A tabela pml4 usada pelo clone.
// Ela é uma cópia da tabela do kernel.
// Fizemos essa clonagem no início da rotina.


// Endereço virtual do pml4 do processo filho.
    child_process->pml4_VA = (unsigned long) _pml4;

    if ( (void *) child_process->pml4_VA == NULL ){
        panic ("copy_process: [FAIL] child_process->pml4_VA\n");
    }

// Endereço físico do pml4 do processo filho.
    child_process->pml4_PA = 
        (unsigned long) virtual_to_physical ( 
                            child_process->pml4_VA, 
                            gKernelPML4Address ); 


// Breakpoint

    // #debug
    //printf ("child_process->pml4_VA: %x\n",child_process->pml4_VA);
    //printf ("child_process->pml4_PA: %x\n",child_process->pml4_PA);
    //refresh_screen();
    //while(1){}


// ==============================
// pdpt0
// A tabela pdpt usada pelo clone.
// Ela é uma cópia da tabela usada pelo processo pai.

    child_process->pdpt0_VA = (unsigned long) parent_process->pdpt0_VA;
    child_process->pdpt0_PA = (unsigned long) parent_process->pdpt0_PA;

// ========
// pd0
// A tabela do pd do clone.
// Ela é uma cópia da tabela usada pelo processo pai.

    child_process->pd0_VA = (unsigned long) parent_process->pd0_VA;
    child_process->pd0_PA = (unsigned long) parent_process->pd0_PA;

// ==================================

// #todo:
// Rever esse comentário todo, colocar uma síntese aqui
// e umcomentário completo la na função chamada.

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
// #explicando:
// Copia a imagem do processo atual e salva o endereço
// da copia num elemento da estrutura passada como argumento.
// #bugbug
// Estamos usando o ponteiro Current, 
// sem antes ao menos checarmos a validade.
// #explicando:
// Copia a imagem do processo atual e salva o endereço
// da copia num elemento da estrutura passada como argumento.
// #changeme: Essa rotina é um absurdo.
// Copy process image and stack.
// Explicando:
// Copia a imagem do processo atual e salva o endereço
// da copia num elemento da estrutura passada como argumento.
// See: process.c
// Salvaremos as informações assim:
// parent_process->childImage    : Endereço virtual do buffer para a imagem do clone.
// parent_process->childStack    : Endereço virtual para a pilha em ring3 usada pelo clone.
// parent_process->childImage_PA : Endereço físico do buffer para a imagem do clone.
// parent_process->childStackPA  : Endereço físico para a pilha em ring3 usada pelo clone.
// [1]
// #bugbug: 
// Na verdade não estamos mais copiando e 
// sim criando um endereçamento novo.
//see: process.c

    // #debug
    debug_print ("copy_process: [1] Copying process image and stack.\n");
    //printf      ("copy_process: [1] Copying process image and stack.\n");


// Allocating memory for the image and for the stack.

    Status = (int) alloc_memory_for_image_and_stack( parent_process );

    if (Status != 0){
        panic ("copy_process: __alloc_memory_for_image_and_stack\n");
    }

// Breakpoint

    //#debug
    //printf (" :) \n");
    //refresh_screen();
    //return 0;

// Copy process structure.
// [2]
// Copiar a estrutura de processo. 
// Do atual para o clone que estamos criando.
// #important: It will also copy the control thread.
// see: process.c

    //#debug
    debug_print ("copy_process: [2] Copying process structure\n");
    //printf ("copy_process: [2] Copying process structure\n");

// Cloning the process structure.
// #todo: It depends on the childs personality.

    Status = 
        (int) copy_process_struct( parent_process, child_process );

    if ( Status != 0 ){
        panic ("copy_process: [FAIL] copy_process_struct\n");
    }

// Breakpoint

    //#debug
    //printf (" :) \n");
    //refresh_screen();
    //return 0;

    // #debug
    // ok
    //printf ("child_process->pml4_VA: %x\n",child_process->pml4_VA);
    //printf ("child_process->pml4_PA: %x\n",child_process->pml4_PA);
    //refresh_screen();
    //while(1){}

    // #debug
    //printf ("Stack : %x \n",__rsp);
    //refresh_screen();
    //while(1){}


//
// child thread.
//

//
// Copy parent thread structure.
//

    debug_print ("copy_process: [3] Copying thread structure\n");
// see: thread.c

    child_thread = 
        (struct thread_d *) copy_thread_struct( parent_thread );

    if ( (void *) child_thread == NULL ){
        panic ("copy_process: [FAIL] copy_thread_struct \n");
    }

// #bugbug: We already get the childs personality.
// it needs to be a parameter given by the caller.

    //child_thread->personality = (int) parent_thread->personality;

// Save the pointer for the control thread.
    child_process->control = (struct thread_d *) child_thread;

// The child process is the owner of the child thread.
    child_thread->owner_process = (struct process_d *) child_process;

// Salvando o pid do owner.
    child_thread->owner_pid = (pid_t) child_pid;

// Breakpoint

    // #debug
    //printf (" :) \n");
    //refresh_screen();
    //return 0;

// rip and rsp

// Standard va entry point.
// 0x201000

    child_thread->rip = (unsigned long) CONTROLTHREAD_ENTRYPOINT;
    
// 32KB size
// #todo 
// Precisa ser do mesmo tamanho que o pai 
// no caso de fork()
// #todo: Precismos levar emconsideração o tamanho da stack
// que foi alocada anteriormente. Precisamos de uma variavel
// na estrutura que registre seu tamanho.

    child_thread->rsp = 
        (unsigned long) (parent_process->childStack + (30*1024));

    // #debug
    // ok
    //printf ("child_process->pml4_VA: %x\n",child_process->pml4_VA);
    //printf ("child_process->pml4_PA: %x\n",child_process->pml4_PA);
    //refresh_screen();
    //while(1){}

// #hackhack
// Vamos herdar porque configuramos esses valores para o process clone.
// Agora eles serão usados na thread de controle do clone.

    child_thread->pml4_VA = (unsigned long) child_process->pml4_VA;
    child_thread->pml4_PA = (unsigned long) child_process->pml4_PA;

    // #debug
    //printf ("child_thread->pml4_VA: %x\n",child_thread->pml4_VA);
    //printf ("child_thread->pml4_PA: %x\n",child_thread->pml4_PA);
    //refresh_screen();
    //while(1){}

// A control thread do processo clone
// está herdando as tabelas usadas por ele.
    child_thread->pml4_PA = (unsigned long) child_process->pml4_PA;

// Salvando o pid do owner.
    //child_thread->ownerPID = (pid_t) child_pid;


//
// Load image
//

// Configurando os buffers.
// Os endereços virtual e físico da imagem do processo filho.

// O endereço virtual da imagem do processo filho.
// No processo pai estava salvo o endereço virtual do buffer
// reservado para a imagem do clone.
// O endereço físico da imagem do processo filho.
// Agora o endereço físico do buffer.

    child_process->Image   = (unsigned long) parent_process->childImage;     //va
    child_process->ImagePA = (unsigned long) parent_process->childImage_PA;  //pa

// Check both addresses.

    // va
    if ( (void *) child_process->Image == NULL ){
        panic ("copy_process: [FAIL] child_process->Image\n");
    }

    // pa
    if ( (void *) child_process->ImagePA == NULL ){
        panic ("copy_process: [FAIL] child_process->ImagePA\n");
    }


//
// Load image
//

    debug_print ("copy_process: [3] load image\n");

// Carregando a imagem do clone no buffer criado para ela.
// IN: 
// name, image va.

    Status = (int) fs_load_image(
                       filename, 
                       (unsigned long) child_process->Image );
 
    if ( Status != 0 ){
        debug_print ("copy_process: [FAIL] Couldn't load the file\n");
        printf      ("copy_process: [FAIL] Couldn't load the file %s\n", filename );
        goto fail;
    }

    //#debug
    //ok
    //printf (" :) \n");
    //refresh_screen();
    //return 0;


// [5]
// Check ELF signature.
// OK. O comando existe e o arquivo foi carregado, mas 
// precisamos saber se a assinatura de ELF é válida.
// Assinatura ELF inválida. 
// Vamos matar a thread e o processo.
// See: fs.c

// #debug
    debug_print ("copy_process: [5] Check signature.\n");
    //printf ("copy_process: [5] Check signature.\n");

// #bugbug
// O processo init deve ter suas proprias tabelas de paginas.
// checar um endereço usando a tabela de paginas do kernel
// esta errado.


    Status = (int) fsCheckELFFile ( (unsigned long) child_process->Image );

    if ( Status < 0 )
    {
        debug_print ("copy_process: [FAIL] ELF fail \n");
        printf      ("copy_process: [FAIL] ELF fail \n");
        goto fail;
    }

    //#debug
    //ok
    //printf (" :) \n");
    //refresh_screen();
    //return 0;

// >> Page table:
// Remapeando a imagem, mas agora no diretório de páginas
// do processo filho.
// Lembrando que já criamos o diretório de páginas para o clone.
// ENTRY_USERMODE_PAGES, esse número de entrada é para o 
// endereço virtual padrão para aplicativos em ring3, 0x200000.

    // #todo
    // Retornaremos o endereço virtual da pagetable.
    // See: core/ps/x86/pages.c

// Check again
// Checando as tabelas principais novamente.
// Isso foi obtido pela rotina de clonagem de processo,
// juntamente com seu endereço físico.

    if( (void*) child_process->pml4_VA == NULL ){
        panic("copy_process: [2nd time] child_process->pml4_VA\n");
    }
    if( (void*) child_process->pdpt0_VA == NULL ){
        panic("copy_process: [2nd time] child_process->pdpt0_VA\n");
    }
    if( (void*) child_process->pd0_VA == NULL ){
        panic("copy_process: [2nd time] child_process->pd0_VA\n");
    }


//
// Breakpoint
//

    //printf (":)\n");
    //refresh_screen();
    //return -1;

    //debug_print ("copy_process:  This is a work in progress\n");
    //     printf ("copy_process:  This is a work in progress\n");
    debug_print ("copy_process: Calling CreateAndIntallPageTable \n");
    //printf      ("copy_process: Calling CreateAndIntallPageTable :) \n");
    //panic       ("copy_process: [Breakpoint] CreateAndIntallPageTable \n");

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

    //#debug
    //printf (" :) \n");
    //refresh_screen();
    //return 0;


//
// BUG BUG BUG BUG
//

// #bugbug
// Algo está falhando nessa hora em que estamos criando a 
// pagetable para a imagem do processo.


    /*
    // See: pages.c
    // OUT: Retorna o endereço virtual da pagetable criada.
    _pt = (void*) CreateAndIntallPageTable (
               (unsigned long) child_process->pml4_VA,   // page map level 4
               (unsigned long) 0,                // index  
               (unsigned long) child_process->pdpt0_VA,  // page directory pointer table
               (unsigned long) 0, 
               (unsigned long) child_process->pd0_VA,         // page directory 
               (int)           ENTRY_USERMODE_PAGES,  // Install the pagetable into this entry of the page directory. See: gentry.h
               (unsigned long) child_process->ImagePA );      // region pa

    if ( (void*) _pt == NULL ){
        panic ("clone_and_execute_process: _pt\n");
    }
    */


//
// Page table
//

// Alocando um endereço virtual onde 
// criaremos nossa pagetable.

    unsigned long ptVA = (unsigned long) get_table_pointer();

    if ( ptVA == 0 ){
        panic ("copy_process: [FAIL] ptVA\n");
    }

    unsigned long ptPA = 
        (unsigned long) virtual_to_physical ( 
                            ptVA, 
                            gKernelPML4Address ); 


// Vamos mapear uma região de memória 
// preenchendo a nossa page table recem criada.
// Essa rotina preenche uma pagetable, mapeando
// a região indicada.
// Cria uma page table com 512 entradas
// para uma região de 2mb e configura uma
// determinada entrada no diretório de páginas.
// Antes vamos clonar o diretório de páginas do kernel.

    child_process->pd0_VA = (unsigned long) CloneKernelPD0();
    child_process->pd0_PA = (unsigned long) virtual_to_physical ( 
                                child_process->pd0_VA, 
                                gKernelPML4Address ); 

    if(child_process->pd0_VA==0)
        panic("copy_process: child_process->pd0_VA==0\n");
    if(child_process->pd0_PA==0)
        panic("copy_process: child_process->pd0_PA==0\n");

//See: gentry.h
    mm_fill_page_table( 
        (unsigned long) child_process->pd0_VA,   // directory va. 
        (int) PD_ENTRY_RING3AREA,      // directory entry for image base.
        (unsigned long) ptVA,            // page table va.
        (unsigned long) child_process->ImagePA,  // Region 2mb pa.
        (unsigned long) 7 );             // flags.

// Clonando o pdpt0 do kernel.
    child_process->pdpt0_VA = (unsigned long) CloneKernelPDPT0();
    child_process->pdpt0_PA = (unsigned long) virtual_to_physical ( 
                                  child_process->pdpt0_VA, 
                                  gKernelPML4Address ); 

    if(child_process->pdpt0_VA==0)
        panic("copy_process: child_process->pdpt0_VA==0\n");
    if(child_process->pdpt0_PA==0)
        panic("copy_process: child_process->pdpt0_PA==0\n");


    //#debug
    //printf (" :) \n");
    //refresh_screen();
    //return 0;

//
// Installing (danger)
//

    unsigned long *PageTable                 = (unsigned long *) ptVA;
    unsigned long *PageDirectory             = (unsigned long *) child_process->pd0_VA;
    unsigned long *PageDirectoryPointerTable = (unsigned long *) child_process->pdpt0_VA;
    unsigned long *PML4                      = (unsigned long *) child_process->pml4_VA;

//============================
// Page Directory
// Instalando o ponteiro para a pagetable entrada do diretório.
// #?? Isso ja foi feito pela rotina mm_fill_page_table.
// podemos criar uma rotina igual, mas que não instale o ponteiro no pd.
    PageDirectory[PD_ENTRY_RING3AREA] = 
        (unsigned long) ptPA;
    PageDirectory[PD_ENTRY_RING3AREA] = 
        (unsigned long) (PageDirectory[PD_ENTRY_RING3AREA] | 7); 

//============================
// Page Directory Pointer Table
// Somente a primeira entrada do pdpt0 é usada.
    PageDirectoryPointerTable[0] = (unsigned long) child_process->pd0_PA;
    PageDirectoryPointerTable[0] = (unsigned long) PageDirectoryPointerTable[0] | 7; 

//============================
// PML4
// Somente a primeira entrada do pml4 é usada.
    PML4[0] = (unsigned long) child_process->pdpt0_PA;
    PML4[0] = (unsigned long) PML4[0] | 7; 

// ======================================

    //#debug
    // ok
    //printf (" :) \n");
    //refresh_screen();
    //return 0;

    // #debug
    //printf ("New page table : %x \n", _pt);
    //refresh_screen();
    //while(1){}

// Configurando o endereço virtual padrão para aplicativos.
// Novo endereço virtual da imagem. 
// Conseguimos isso por causa da criação da pagetable, logo acima.
// #caution
// Entry point and stack.
// We are clonning only the control thread.
// The entry point in the start of the image. 0x201000.
// And the stack ??

    child_process->Image = (unsigned long) CONTROLTHREAD_BASE;        // 0x200000 
    child_thread->rip    = (unsigned long) CONTROLTHREAD_ENTRYPOINT;  // 0x201000

// Process name.

    strcpy ( child_process->__processname, (const char *) filename );   
    //child_process->processName_len = (size_t) strlen ( (const char *) filename );
    child_process->processName_len = (size_t) sizeof(child_process->__processname);

    //#debug
    //ok
    //printf (" :) \n");
    //refresh_screen();
    //return 0;

//
// Clone thread
//

    // [filho]
    child_thread->saved = 0;  //#todo: FALSE

    // Used by spawn.c
    child_thread->new_clone = TRUE;

// [5] done.
// #todo
// Antes de retornarmos, vamos exibir todas as informações
// sobre esse processo e essa thread.
// Isso ajudará a reorganizarmos essa rotina.

// #debug
    debug_print ("copy_process: [5] Done\n");
    //debug_print ("----------------------\n");
    //printf ("copy_process: [5] Done\n");

    invalidate_screen();
    //refresh_screen();

//
// Debug
//

    //printf ("\n");
    //printf ("--[ Debug ]---------------------------------\n");

    //printf ("\n");
    //printf ("Original thread::\n");
    // ok: Esses são iguais, como deveria ser.
    //printf ("pml4_VA:%x  | pml4_PA:%x  \n", parent_thread->pml4_VA,  parent_thread->pml4_PA);
    // ok: Esses são iguais, como deveria ser.
    //printf ("pdpt0_VA:%x | pdpt0_PA:%x \n", parent_thread->pdpt0_VA, parent_thread->pdpt0_PA);
    // ok: Esses são iguais, como deveria ser.
    //printf ("pd0_VA:%x   | pd0_PA:%x   \n", parent_thread->pd0_VA,   parent_thread->pd0_PA);

    //printf ("\n");
    //printf ("Clone thread::\n");
    // ok: Esses são iguais, como deveria ser.
    //printf ("pml4_VA:%x  | pml4_PA:%x  \n",child_thread->pml4_VA,  child_thread->pml4_PA);
    // ok: Esses são iguais, como deveria ser.
    //printf ("pdpt0_VA:%x | pdpt0_PA:%x \n",child_thread->pdpt0_VA, child_thread->pdpt0_PA);
    // ok: Esses são iguais, como deveria ser.
    //printf ("pd0_VA:%x   | pd0_PA:%x   \n",child_thread->pd0_VA,   child_thread->pd0_PA);

    //show_slot (parent_thread->tid);
    //show_reg  (parent_thread->tid);

    //show_slot (child_thread->tid);
    //show_reg  (child_thread->tid);

    //printf ("\n");
    //current_process = (pid_t) child_pid;
    //show_currentprocess_info();

    //printf ("--------------------------\n");
    //printf ("\n");

    // #debug
    //refresh_screen();
    //while(1){}

    // Switch back
    //x64_load_pml4_table( old_pml4 );

//
// Balance 
//

// priority and quantum.


// Threshold
    parent_thread->priority = PRIORITY_THRESHOLD;
    child_thread->priority  = PRIORITY_THRESHOLD;
    parent_thread->quantum  = QUANTUM_THRESHOLD;
    child_thread->quantum   = QUANTUM_THRESHOLD;

// Time critical
    if ( parent_thread->type == THREAD_TYPE_SYSTEM ||
         child_thread->type == THREAD_TYPE_SYSTEM )
    {
        parent_thread->priority = PRIORITY_TIME_CRITICAL;
        child_thread->priority  = PRIORITY_TIME_CRITICAL;
        parent_thread->quantum  = QUANTUM_TIME_CRITICAL;
        child_thread->quantum   = QUANTUM_TIME_CRITICAL;
    }

// Select for execution
// Então a thread de controle esta em INITIALIZED e não em STANDBY.
// Change the state to standby.
// This thread is gonna run in the next taskswitch.

    SelectForExecution (child_thread);  // :)


// Current thread
// the parent thread.

    current_thread = (tid_t) parent_thread->tid;
    if ( current_thread < 0 || 
         current_thread >= THREAD_COUNT_MAX )
    {
        panic("copy_process: current_thread limits\n");
    }

    copy_process_in_progress = FALSE;

// Return child's PID.
// Retornaremos para o pai.

    return (pid_t) child_pid;

fail:
//fail0:

// #debug
    debug_print ("copy_process: [X] Fail\n");
    //debug_print ("----------------------\n");
    printf      ("copy_process: [X] Fail\n");
    //printf      ("----------------------\n");
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

    copy_process_in_progress=FALSE;

    return (pid_t) (-1);
}



