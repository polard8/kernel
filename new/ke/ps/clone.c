
// clone.c

#include <kernel.h> 


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


// See: process.h for the flags.

// OUT:
// The pid of the clone or fail.

pid_t copy_process ( const char *filename, pid_t pid, unsigned long clone_flags )
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


    //#debug
    //printf (" :) \n");
    //refresh_screen();
    //return 0;


    // The new process will be in a different pid.
    // We are clonning the thread.
    //if ( clone_flags & CLONE_THREAD ){
        //THIS IS A TEST
    //}


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




    //#debug
    //printf (" :) \n");
    //refresh_screen();
    //return 0;


//
// Copy process structure.
//

    // Copiar a estrutura de processo. Do atual para o clone que estamos criando.
    // #important: It will also copy the control thread.
    // [2]
    debug_print ("clone_and_execute_process: [2] Copying process structure\n");
    printf      ("clone_and_execute_process: [2] Copying process structure\n");
    Status = copy_process_struct(p,Clone);
    if ( Status != 0 ){
        panic ("clone_and_execute_process: [FAIL] processCopyProcess\n");
    }

    //#debug
    //printf (" :) \n");
    //refresh_screen();
    //return 0;


    // #debug
    // ok
    //printf ("Clone->pml4_VA: %x\n",Clone->pml4_VA);
    //printf ("Clone->pml4_PA: %x\n",Clone->pml4_PA);
    //refresh_screen();
    //while(1){}


    // #debug
    //printf ("Stack : %x \n",__rsp);
    //refresh_screen();
    //while(1){}

    Clone->control = (struct thread_d *) copy_thread_struct( p->control );
    if ( (void *) Clone->control == NULL ){
        panic ("clone_and_execute_process: [FAIL] copy_thread_struct \n");
    }


    // #debug
    // ok
    //printf (" :) \n");
    //refresh_screen();
    //return 0;


    // rip and rsp

    Clone->control->rip = (unsigned long) 0x201000;
    // 32kb size
    //#todo precisa ser do mesmo tamanho que o pai 
    //no caso de fork()
    Clone->control->rsp = (unsigned long) (p->childStack + (30*1024));   // original   
    //Clone->control->rsp = (unsigned long) (p->childStack + (120*1024));  // test

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


    //#debug
    //ok
    //printf (" :) \n");
    //refresh_screen();
    //return 0;


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


    //#debug
    //printf (" :) \n");
    //refresh_screen();
    //return 0;


//
// BUG BUG BUG BUG
//

    // Algo está falhando nessa hora em que estamos criando a 
    // pagetable para a imagem do processo.


    /*
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
    */


//
// Page table
//

    // Alocando um endereço virtual onde criaremos nossa pagetable.

    unsigned long ptVA = (unsigned long) get_table_pointer();  //ok
    if ( ptVA == 0 ){
        panic ("copy_process: [FAIL] ptVA\n");
    }

    unsigned long ptPA = (unsigned long) virtual_to_physical ( 
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
    Clone->pd0_VA = (unsigned long) CloneKernelPD0();

    Clone->pd0_PA = (unsigned long) virtual_to_physical ( 
                                        Clone->pd0_VA, 
                                        gKernelPML4Address ); 

    mm_fill_page_table( 
        (unsigned long) Clone->pd0_VA,   // directory va. 
        (int) ENTRY_USERMODE_PAGES,      // directory entry for image base.
        (unsigned long) ptVA,            // page table va.
        (unsigned long) Clone->ImagePA,  // Region 2mb pa.
        (unsigned long) 7 );             // flags.



    // CLonando o pdpt0 do kernel.
    Clone->pdpt0_VA = (unsigned long) CloneKernelPDPT0();

    Clone->pdpt0_PA = (unsigned long) virtual_to_physical ( 
                                        Clone->pdpt0_VA, 
                                        gKernelPML4Address ); 

    //#debug
    //printf (" :) \n");
    //refresh_screen();
    //return 0;

//
// Installing (danger)
//

    
    unsigned long *PageTable                 = (unsigned long *) ptVA;
    unsigned long *PageDirectory             = (unsigned long *) Clone->pd0_VA;
    unsigned long *PageDirectoryPointerTable = (unsigned long *) Clone->pdpt0_VA;
    unsigned long *PML4                      = (unsigned long *) Clone->pml4_VA;


    
    //============================
    // Page Directory
    // Instalando o ponteiro para a pagetable entrada do diretório.
    // #?? Isso ja foi feito pela rotina mm_fill_page_table.
    // podemos criar uma rotina igual, mas que não instale o ponteiro no pd.
    PageDirectory[ENTRY_USERMODE_PAGES] = (unsigned long) ptPA;
    PageDirectory[ENTRY_USERMODE_PAGES] = (unsigned long) PageDirectory[ENTRY_USERMODE_PAGES] | 7; 

    
    //============================
    // Page Directory Pointer Table
    // Somente a ŕimeira entrada do pdpt0 é usada.
    PageDirectoryPointerTable[0] = (unsigned long) Clone->pd0_PA;
    PageDirectoryPointerTable[0] = (unsigned long) PageDirectoryPointerTable[0] | 7; 

    
    //============================
    // PML4
    // Somente a primeira entrada do pml4 é usada.
    PML4[0] = (unsigned long) Clone->pdpt0_PA;
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



    //#debug
    //ok
    //printf (" :) \n");
    //refresh_screen();
    //return 0;





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
    //printf ("Original thread::\n");
    // ok: Esses são iguais, como deveria ser.
    //printf ("pml4_VA:%x  | pml4_PA:%x  \n",p->control->pml4_VA,  p->control->pml4_PA);
    // ok: Esses são iguais, como deveria ser.
    //printf ("pdpt0_VA:%x | pdpt0_PA:%x \n",p->control->pdpt0_VA, p->control->pdpt0_PA);
    // ok: Esses são iguais, como deveria ser.
    //printf ("pd0_VA:%x   | pd0_PA:%x   \n",p->control->pd0_VA,   p->control->pd0_PA);

    //printf ("\n");
    //printf ("Clone thread::\n");
    // ok: Esses são iguais, como deveria ser.
    //printf ("pml4_VA:%x  | pml4_PA:%x  \n",Clone->control->pml4_VA,  Clone->control->pml4_PA);
    // ok: Esses são iguais, como deveria ser.
    //printf ("pdpt0_VA:%x | pdpt0_PA:%x \n",Clone->control->pdpt0_VA, Clone->control->pdpt0_PA);
    // ok: Esses são iguais, como deveria ser.
    //printf ("pd0_VA:%x   | pd0_PA:%x   \n",Clone->control->pd0_VA,   Clone->control->pd0_PA);

    //show_slot (p->control->tid);
    //show_reg  (p->control->tid);

    //show_slot (Clone->control->tid);
    //show_reg (Clone->control->tid);

    //printf ("\n");
    //current_process = Clone->pid;
    //show_currentprocess_info();

    //printf ("--------------------------------------------\n");
    //printf ("\n");

    // #debug
    refresh_screen();
    //while(1){}
    
    
    // Switch back
    //x64_load_pml4_table( old_pml4 );

//
// #todo
//

    // Ainda não selecionamos para execução.
    // Então a thread de controle esta em INITIALIZED e não em STANDBY.

    // Change the state to standby.
    // This thread is gonna run in the next taskswitch.

    SelectForExecution (Clone->control);

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






