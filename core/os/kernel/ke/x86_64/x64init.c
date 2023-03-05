
// x64init.c

#include <kernel.h>

// Task switching support.
extern void turn_task_switch_on (void);
extern void x64_clear_nt_flag (void);

// private
static int InitialProcessInitialized = FALSE;


//Onde ficam os códigos e arquivos de configuração usados na inicialização.
//A ideia é que se a inicialização precisar de algum arquivo, deve procurá-lo
//nos diretórios previamente combinados.
//melhor que sejam poucos e que sempre sejam os mesmos.

#define INIT_ROOT_PATH  "/"
#define INIT_BIN_PATH   "/BIN"
//...

// =========================================


//
// == Private functions: Prototypes ========
//

static int I_init(void);
static int I_x64CreateKernelProcess(void);
static int I_x64CreateInitialProcess(void);
static int I_x64CreateTID0(void);
static int __load_initbin_image(void);
// =========================================


/*
// #deprecated
// local
// Call a mm routine for that.
void x64init_load_pml4_table(unsigned long phy_addr)
{
    asm volatile ("movq %0,%%cr3"::"r"(phy_addr));
}
*/


//local
static int __load_initbin_image(void)
{
    int Status = -1;

    char *ImageName = "INIT    BIN";
    char *PathName = "/INIT.BIN";
    char *PathName2 = "/GRAMADO/INIT.BIN";

// The virtual address for the base of the image.
// ps: We are using the kernel page directories now,
// this way but we're gonna clone the kernel pages
// when creating the init process.
// #define CONTROLTHREAD_BASE        0x00200000
// See: x64gva.h
// #bugbug:
// Por que esse endereço está disponível para uso?
// Por que não precisamos alocar memoria para esse processo?
// Porque estamos usando 512 páginas?
// Talvez seja porque a gerência de memória
// reservou esse espaço de 2mb para o primeiro processo em ring3
// na hora de mapear as regiões principais da memória ram.

    unsigned long ImageAddress = 
        (unsigned long) CONTROLTHREAD_BASE;

//
// Load image GWS.BIN
//

// Session manager
// This is the first user mode process running
// after the kernel base.
// #importante
// Carregado do diretório raiz
// loading image.
// #bugbug
// Loading from root dir. 512 entries limit.
// #todo
// O propósito é termos a possibilidade de selecionar qual será
// a imagem desse processo incial
// e configurarmos isso no modulo init/ do kernel base.

    unsigned long BUGBUG_IMAGE_SIZE_LIMIT = (512 * 4096);

/*
 *    It loads a file into the memory.
 * IN:
 *     fat_address  = FAT address.
 *     dir_addresss = Directory address.
 *     dir_entries  = Number of entries in the given directory.
 *     file_name    = File name.
 *     buffer = Where to load the file. The pre-allocated buffer.
 *     buffer_size_in_bytes = Maximum buffer size.
 * OUT: 
 *    1=fail 
 *    0=ok.
 */

    Status = 
        (unsigned long) fsLoadFile( 
                            VOLUME1_FAT_ADDRESS, 
                            VOLUME1_ROOTDIR_ADDRESS, 
                            FAT16_ROOT_ENTRIES,    //#bugbug: number of entries.
                            ImageName, 
                            (unsigned long) ImageAddress,  // buffer
                            BUGBUG_IMAGE_SIZE_LIMIT );     // buffer limits

/*
    // #bugbug
    // Essa rotina ainda não leva direito emconsideração
    // o limite do tamanho do arquivo.
    // Estamos passando o tamanho do buffer definido,
    // mas a rotina ignora.
    
    Status = (int) fs_load_path ( 
                       (const char*) PathName, 
                       (unsigned long) ImageAddress,
                       (unsigned long) BUGBUG_IMAGE_SIZE_LIMIT ); 
*/

// OUT: 
//    1=fail 
//    0=ok.

    return (int) Status;
}


// Load INIT.BIN.
// Create a process for the first ring3 process.
// + Carrega a imagem do primeiro processo que vai rodar em user mode.
// + Configura sua estrutura de processo.
// + Configura sua estrutura de thraed.
// Não passa o comando para o processo.

static int I_x64CreateInitialProcess(void)
{
// This is a ring 3 process.
// It loads the first ring3 program, the INIT.BIN.

// #debug
    //debug_print ("I_x64CreateInitialProcess: \n");
    //printf      ("I_x64CreateInitialProcess:\n");
    //refresh_screen();

    InitialProcessInitialized = FALSE;

    if ( system_state != SYSTEM_BOOTING ){
        printf ("I_x64CreateInitialProcess: system_state\n");    
        return FALSE;
    }
    
    int ret0 = -1;
    ret0 = (int) __load_initbin_image();
    if (ret0 != 0)
    {
        printf ("I_x64CreateInitialProcess: Coldn't load INIT.BIN \n");
        return FALSE;
    }

// Creating init process.
// > Cria um diretório que é clone do diretório do kernel base 
// Retornaremos o endereço virtual, para que a função create_process possa usar 
// tanto o endereço virtual quanto o físico.
// > UPROCESS_IMAGE_BASE;
// #todo
// temos que checar a validade do endereço do dir criado
// antes de passarmos..

    void *init_pml4_va = (void *) CloneKernelPML4();

    if ( init_pml4_va == 0 ){
        printf ("I_x64CreateInitialProcess: init_pml4_va\n");
        return FALSE;
    }

    init_mm_data.pml4_va = init_pml4_va;  // #todo: type.
    init_mm_data.pml4_pa = (unsigned long) virtual_to_physical ( 
                                               init_pml4_va, 
                                               gKernelPML4Address );

    if ( init_mm_data.pml4_pa == 0 ){
        printf ("I_x64CreateInitialProcess: init_mm_data.pml4_pa\n");
        return FALSE;
    }

    // ...

    init_mm_data.used = TRUE;
    init_mm_data.magic = 1234;

// ===========================================

//
// Create init process
//

    unsigned long BasePriority = PRIORITY_SYSTEM_THRESHOLD;
    unsigned long Priority     = PRIORITY_SYSTEM_THRESHOLD;

    InitProcess = 
        (void *) create_process( 
                     NULL, 
                     NULL,  
                     (unsigned long) CONTROLTHREAD_BASE,  //0x00200000 
                     BasePriority, 
                     (int) KernelProcess->pid, 
                     "INIT-PROCESS", 
                     RING3, 
                     (unsigned long) init_pml4_va,
                     (unsigned long) kernel_mm_data.pdpt0_va,
                     (unsigned long) kernel_mm_data.pd0_va,
                     PERSONALITY_GRAMADO );

    if ( (void *) InitProcess == NULL )
    {
        printf ("I_x64CreateInitialProcess: InitProcess\n");
        return FALSE;
    }

    if ( InitProcess->used != TRUE || 
         InitProcess->magic != 1234 )
    {
        printf ("I_x64CreateInitialProcess: InitProcess validation\n");
        return FALSE;
    }



// struct
    if ( InitProcess->pid != GRAMADO_PID_INIT )
    {
        printf ("I_x64CreateInitialProcess: pid\n");
        return FALSE;
    }

// The init process is a system application.
// GWS.BIN

    InitProcess->type = PROCESS_TYPE_SYSTEM;

    InitProcess->base_priority = BasePriority;    
    InitProcess->priority = Priority;


    if ( init_mm_data.used != TRUE || 
         init_mm_data.magic != 1234 )
    {
        printf ("I_x64CreateInitialProcess: init_mm_data validation\n");
        return FALSE;
    }

// Esse foi configurado agora.
    InitProcess->pml4_VA = init_mm_data.pml4_va;
    InitProcess->pml4_PA = init_mm_data.pml4_pa; 

// Herdado do kernel
    InitProcess->pdpt0_VA = kernel_mm_data.pdpt0_va;
    InitProcess->pdpt0_PA = kernel_mm_data.pdpt0_pa; 

// Herdado do kernel
    InitProcess->pd0_VA = kernel_mm_data.pd0_va;
    InitProcess->pd0_PA = kernel_mm_data.pd0_pa; 

    fs_initialize_process_cwd ( InitProcess->pid, "/" );

//====================================================
// Create thread


// Criamos um thread em ring3.
// O valor de eflags é 0x3200. The app is gonna change that.
// The control thread of the first ring 3 process.
// See: create.c
// Struct, and struct validation.

    InitThread = (struct thread_d *) create_init_thread();

    if ( (void *) InitThread == NULL ){
        printf ("I_x64CreateInitialProcess: InitThread\n");
        return FALSE;
    }

    if ( InitThread->used != TRUE || 
         InitThread->magic != 1234 )
    {
        printf ("I_x64CreateInitialProcess: InitThread validation\n");
        return FALSE;
    }

// tid : tem que ser a primeira thread
    if ( InitThread->tid != 0 ){
        printf ("I_x64CreateInitialProcess: INIT_TID\n");
        return FALSE;
    }

// owner pid
    if ( InitThread->owner_pid != GRAMADO_PID_INIT ){
        printf ("I_x64CreateInitialProcess: GRAMADO_PID_INIT\n");
        return FALSE;
    }

//
// Paging
//

// Herdando do processo configurado logo antes.
    InitThread->pml4_VA  = InitProcess->pml4_VA;
    InitThread->pml4_PA  = InitProcess->pml4_PA;
    InitThread->pdpt0_VA = InitProcess->pdpt0_VA;
    InitThread->pdpt0_PA = InitProcess->pdpt0_PA;
    InitThread->pd0_VA   = InitProcess->pd0_VA;
    InitThread->pd0_PA   = InitProcess->pd0_PA;


    //IdleThread->ownerPID = (int) InitProcess->pid;

    // #todo #bugbug
    //InitThread->tss = current_tss;

    // [Processing time]
    //current_process = InitProcess->pid;
    set_current_process(InitProcess->pid);
    current_thread  = InitThread->tid;

    // [Focus]
    //active_process = current_process;
    active_process = InitProcess->pid;
    active_thread  = InitThread->tid; //current_thread;
        
    // foreground thread ?

    // [Scheduler stuff]
    next_thread = InitThread->tid;

// ===========================

// #importante
// A thread de controle do processo init2.bin.
    InitProcess->control = InitThread;

// #todo #bugbug
//registra um dos servidores do gramado core.
    //server_index, process, thread

    //ipccore_register ( 
        //(int) 0, 
        //(struct process_d *) InitProcess, 
        //(struct thread_d *) InitThread ); 

// Agora ja temos um processo em user mode devidamente 
// configurado. Então a rotina de inicialização em init/
// poderá pasasr o comando para ele quando quizer.

    InitialProcessInitialized = TRUE;
    return TRUE;
}

// Passa o comando para o primeiro processo em user mode.
// Esse processo ja foi previamente configurado.
// Called by booting_end() in init.c
void I_x64ExecuteInitialProcess (void)
{
    struct thread_d  *t;
    register int i=0;

    //#todo
    debug_print ("I_x64ExecuteInitialProcess:\n");

    // #debug
    // For real machine.
    //printf      ("I_x64ExecuteInitialProcess: [TODO]\n");
    //refresh_screen();

    if ( system_state != SYSTEM_BOOTING ){
        panic ("I_x64ExecuteInitialProcess: system_state\n");    
    }

    if ( InitialProcessInitialized != TRUE ){
        debug_print ("I_x64ExecuteInitialProcess: InitialProcessInitialized\n");
        panic       ("I_x64ExecuteInitialProcess: InitialProcessInitialized\n");
    }

// Se essa rotina foi chamada antes mesmo
// do processo ter sido devidamente configurado.
    if ( InitialProcessInitialized != TRUE ){
        debug_print ("I_x64ExecuteInitialProcess: InitialProcessInitialized\n");
        panic       ("I_x64ExecuteInitialProcess: InitialProcessInitialized\n");
    }

// The first thread to run will the control thread 
// of the init process. It is called InitThread.

    t = (struct thread_d *) InitThread; 

    if ( (void *) t == NULL ){
        panic ("I_x64ExecuteInitialProcess: t\n");
    }
    if ( t->used != TRUE || t->magic != 1234 ){
        panic ("I_x64ExecuteInitialProcess: t validation\n");
    }
    if ( t->tid < 0 || t->tid > THREAD_COUNT_MAX ){
        panic("I_x64ExecuteInitialProcess: tid\n");
    }

// It its context is already saved, 
// so this is not the fist time.
    if ( t->saved != FALSE ){
        panic("I_x64ExecuteInitialProcess: saved\n");
    }

// Set the current thread.
    set_current_thread(t->tid);

// Set the first foreground thread.
// #todo: We need a function for this job.
    foreground_thread = (tid_t) t->tid;

// State
// The thread needs to be in Standby state.
    if (t->state != STANDBY){
        printf ("I_x64ExecuteInitialProcess: state tid={%d}\n", t->tid );
        die();
    }

// :: MOVEMENT 2 ( Standby --> Running )

    if (t->state == STANDBY){
        debug_print("I_x64ExecuteInitialProcess: Now RUNNING!\n");
        t->state = RUNNING;
    }

//
// Current process.
//

    if (t->owner_process->pid != GRAMADO_PID_INIT){
        panic("I_x64ExecuteInitialProcess: t->owner_process->pid\n");
    }
    set_current_process(GRAMADO_PID_INIT);

// List
// Dispatcher ready list.
// Maybe it is not used.
    for ( i=0; i < PRIORITY_MAX; i++ ){
        dispatcherReadyList[i] = (unsigned long) t;
    };

// Counting the type of the dispatching criteria.
    IncrementDispatcherCount(SELECT_IDLE_COUNT);

// #todo 
// check this
// turn_task_switch_on:
//  + Creates a vector for timer irq, IRQ0.
//  + Enable taskswitch. 

    turn_task_switch_on();

// #todo
// Isso deve ser liberado pelo processo init
// depois que ele habilitar as interrupções.
    
    //taskswitch_lock();
    //scheduler_lock();


// Setup cr3.
// This is a Physical address.
// See: hal/
// Reload tlb.
// See: https://en.wikipedia.org/wiki/Translation_lookaside_buffer
// #bugbug: rever isso.

    x64_load_pml4_table( t->pml4_PA );

    asm ("movq %cr3, %rax");
    asm ("movq %rax, %cr3");

// #todo 
// check this
// See: headlib.asm
// Se nao limpar, um iret causa taskswitch
// em sistemas x86 de 32bit. Mas estamos em 64bit.

    x64_clear_nt_flag();   

// #maybe
// Vamos iniciar antes para que
// possamos usar a current_tss quando criarmos as threads

    //x64_init_gdt();

// ??
    asm ("clts \n");

// #importante
// Mudamos para a última fase da inicialização.
// Com isso alguns recursos somente para as fases anteriores
// deverão ficar indisponíveis.

// -------------------------------
// Starting phase 4.
    Initialization.current_phase = 4;

// =============
// # go!
// Nos configuramos a idle thread em user mode e agora vamos saltar 
// para ela via iret.
// #todo:
// #importante:
// Podemos usr os endereços que estão salvos na estrutura.
// #bugbug:
// temos a questão da tss:
// será que a tss está configurada apenas para a thread idle do INIT ??
// temos que conferir isso.
// base dos arquivos.
// #todo
// Rever se estamos usando a base certa.
// sm.bin (ELF)
// See: fs.c

// #bugbug
// O processo init deve ter suas proprias tabelas de paginas.
// checar um endereço usando a tabela de paginas do kernel
// esta errado.
// >>> Mas logo acima, acabamos de mudar as tabelas.

    int elfStatus = -1;
    elfStatus = (int) fsCheckELFFile ( (unsigned long) CONTROLTHREAD_BASE );
    if ( elfStatus < 0 )
    {
        debug_print ("I_x64ExecuteInitialProcess: .ELF signature\n");
        panic       ("I_x64ExecuteInitialProcess: .ELF signature");
    }


/*
// ==============
// #test
// ok. It's working fine.
// Testing the structure in exec_elf.h

// #todo
// Create a helper for this routine.

    struct elf_header_64bit_d *elf_header;

    // The base of the image.
    // The header is in the top.
    elf_header = (struct elf_header_64bit_d *) CONTROLTHREAD_BASE;


// signature
    printf ("Signature: %c %c %c \n",
        elf_header->e_ident[1],     // 'E'
        elf_header->e_ident[2],     // 'L'
        elf_header->e_ident[3] );   // 'F'


// file class
// 1 = 32 bit, 2 = 64 bit
    if( elf_header->e_ident[EI_CLASS] != ELFCLASS64 )
    {
        //
    } 
    printf ("Class: %x\n", elf_header->e_ident[EI_CLASS]);

// type
// 1 = relocatable, 2 = executable, 3 = shared, 4 = core
    if( elf_header->e_type != ET_EXEC )
    {
        //
    }
    printf ("Type: %x\n", elf_header->e_type);

// machine
// x86  3 | IA-64  0x32 | x86-64  0x3E(62)
    if( elf_header->e_machine != EM_X86_64 )
    {
        //
    }
    printf ("Machine: %x\n", elf_header->e_machine);

// entry
    if( elf_header->e_entry != CONTROLTHREAD_ENTRYPOINT )
    {
        //
    }
    printf ("Entry: %x\n", elf_header->e_entry);


    //#breakpoint
    refresh_screen();
    while(1){}
// ==============
*/



// ==============
// #debug

    //debug_print("I_x64ExecuteInitialProcess: [x64] Go to user mode! IRETQ\n");
    //printf     ("I_x64ExecuteInitialProcess: [x64] Go to user mode! IRETQ\n");
    //refresh_screen();

// Here is where the boot routine ends.
    system_state = SYSTEM_RUNNING;

// =============
// Fly!
// #important:
// This is an special scenario,
// Where we're gonna fly with the eflags = 0x3000,
// it means that the interrupts are disabled,
// and the init process will make a software interrupt
// to reenable the interrupts. 
// Softwre interrupts are not affecte by this flag, I guess.
// #bugbug
// This routine is very ugly and very gcc dependent.
// We deserve a better thing.
// We need to have the same stack in the TSS.
// ss, rsp, rflags, cs, rip;
// See:
// gva.h


// cpl
    if (t->cpl != RING3 ){
        panic ("I_x64ExecuteInitialProcess: cpl\n");
    }

// iopl
// weak protection
    if (t->rflags_initial_iopl != 3 ){
        panic ("I_x64ExecuteInitialProcess: rflags_initial_iopl\n");
    }

    PROGRESS("Go to ring3! \n");
    
    //printf("go!\n");
    //refresh_screen();
    //while(1){}

// Entry point and ring3 stack.
// CONTROLTHREAD_ENTRYPOINT

    unsigned long entry = (unsigned long) 0x0000000000201000;
    unsigned long rsp3  = (unsigned long) 0x00000000002FFFF0;

// rflags:
// 0x3002
// iopl 3. weak protection.
// Interrupts disabled for the first thread.

    asm volatile ( 
        " movq $0, %%rax  \n" 
        " mov %%ax, %%ds  \n" 
        " mov %%ax, %%es  \n" 
        " mov %%ax, %%fs  \n" 
        " mov %%ax, %%gs  \n" 
        " movq %0, %%rax  \n" 
        " movq %1, %%rsp  \n" 
        " movq $0, %%rbp  \n" 
        " pushq $0x23     \n"  
        " pushq %%rsp     \n" 
        " pushq $0x3002   \n" 
        " pushq $0x1B     \n" 
        " pushq %%rax     \n" 
        " iretq           \n" :: "D"(entry), "S"(rsp3) );

// Paranoia
    PROGRESS("I_x64ExecuteInitialProcess: Unexpeted error\n");
    panic   ("I_x64ExecuteInitialProcess: Unexpeted error\n");
}

// Create the kernel process.
// It will create a process for two images:

static int I_x64CreateKernelProcess(void)
{
    // This is a ring0 process.
    // This process has two images,
    // KERNEL.BIN loaded by the boot loader and
    // MOD0.BIN loaded by the kernel base.

    char *ImageName = "MOD0    BIN";

    // This is the virtual address for the base of the image.
    // We are using the kernel pagetables for that.
    // #define EXTRAHEAP1_VA   0x0000000030A00000
    // MOD0_IMAGE_VA
    // See: x64gva.h

    unsigned long ImageAddress =
        (unsigned long) 0x30A00000;

    unsigned long fileret=1;
    int Status=FALSE;
    unsigned long BUGBUG_IMAGE_SIZE_LIMIT = (512 * 4096);

    //debug_print ("I_x64CreateKernelProcess:\n");

    unsigned long BasePriority = PRIORITY_MAX;
    unsigned long Priority     = PRIORITY_MAX;

//
// Module 0 image.
//

// WS_IMAGE_VA

    fileret = 
        (unsigned long) fsLoadFile( 
                            VOLUME1_FAT_ADDRESS, 
                            VOLUME1_ROOTDIR_ADDRESS, 
                            FAT16_ROOT_ENTRIES,    //#bugbug: number of entries.
                            ImageName, 
                            (unsigned long) ImageAddress,
                            BUGBUG_IMAGE_SIZE_LIMIT ); 

    if (fileret != 0){
        printf ("I_x64CreateInitialProcess: MOD0.BIN\n");
        return FALSE;
    }

//
// Kernel process
//

// IN: 
// Room, Desktop, Window
// base address, priority, ppid, name, iopl, page directory address.
// See: ps/action/process.c
// KERNELIMAGE_VA
 
    KernelProcess = 
        (void *) create_process( 
                     NULL, 
                     NULL,  
                     (unsigned long) 0x30000000, 
                     BasePriority, 
                     (int) 0,        //ppid
                     "KERNEL-PROCESS", 
                     RING0,   
                     (unsigned long ) gKernelPML4Address,
                     (unsigned long ) kernel_mm_data.pdpt0_va,
                     (unsigned long ) kernel_mm_data.pd0_va,
                     PERSONALITY_GRAMADO );

// Struct and struct validation.
    if ( (void *) KernelProcess == NULL ){
        printf ("I_x64CreateKernelProcess: KernelProcess\n");
        return FALSE;
    }
    if (KernelProcess->used != TRUE || KernelProcess->magic != 1234){
        printf ("I_x64CreateKernelProcess: KernelProcess validation\n");
        return FALSE;
    }

// pid
    if ( KernelProcess->pid != GRAMADO_PID_KERNEL ){
        printf ("I_x64CreateKernelProcess: pid\n");
        return FALSE;
    }

// The kernel process is a system program.
// KERNEL.BIN and GWSSRV.BIN

    KernelProcess->type = PROCESS_TYPE_SYSTEM;

    KernelProcess->base_priority = BasePriority;
    KernelProcess->priority = Priority;

//
// mm
//

// kernel_mm_data validation.

    if (kernel_mm_data.used != TRUE || kernel_mm_data.magic != 1234){
        printf ("I_x64CreateKernelProcess: kernel_mm_data validation\n");
        return FALSE;
    }

    KernelProcess->pml4_VA = kernel_mm_data.pml4_va;
    KernelProcess->pml4_PA = kernel_mm_data.pml4_pa; 

    KernelProcess->pdpt0_VA = kernel_mm_data.pdpt0_va;
    KernelProcess->pdpt0_PA = kernel_mm_data.pdpt0_pa; 

    KernelProcess->pd0_VA = kernel_mm_data.pd0_va;
    KernelProcess->pd0_PA = kernel_mm_data.pd0_pa; 


// cwd
    fs_initialize_process_cwd ( KernelProcess->pid, "/" ); 

// ==================
// The control thread.
// This is the control thread for the 
// window server image.

    /*
    Status = I_x64CreateTID0();
    if ( Status != TRUE ){
        printf("Couldn't Create the WS thread\n");
        return FALSE;
    }
    */

// ====================
// Initialize the kernel module list.

    int i=0;
    for (i=0; i<KMODULE_MAX; i++){
        kmList[i] = 0;
    };

// ====================
// Setup the first kernel module.
// It is not a dynlinked module.
// This is just a loadable ring0 thread with shared symbols.

    struct kernel_module_d *m;
    
    m = (struct kernel_module_d *) kmalloc( sizeof(struct kernel_module_d) );
    if( (void*) m == NULL ){
        printf ("I_x64CreateKernelProcess: m\n");
        return FALSE;
    }

// name

    char *name = "km::first";
    size_t s=0;

    memset(m->name,0,64);
    mysprintf(m->name,name);
    s = strlen(name);
    m->name_size = s;
    m->name[s] = 0;   // finalize

//#debug
    //printf ("String: {%s}\n",m->name);
    //refresh_screen();
    //while(1){}

// See:
// I_x64CreateWSControlThread()

    //m->thread = (struct thread_d *) tid0_thread;

// info
    //m->info.entry_point = (unsigned long) tid0_thread->initial_rip;
    m->info.dialog_address = 0;
    m->info.function_table_address = 0;

// Put it into the list.
// #todo: Change this name
    m->id = KMODULE_MOD0;
    kmList[KMODULE_MOD0] = (unsigned long) m;

// Finalize the module structure.
    m->initialized = TRUE;
    m->used  = TRUE;
    m->magic = 1234;

// See: kernel.h
    kernel_mod0 = (struct kernel_module_d *) m; 

    return TRUE;
}



// Create a ring0 thread for the window server image.
// It belongs to the kernel process.
static int I_x64CreateTID0(void)
{
/*
    //debug_print ("I_x64CreateTID0:\n");

// Thread
// This is the control thread of the window server module.
// See: create.c, thread.h.

    tid0_thread = (void *) create_tid0();

    if ( (void *) tid0_thread == NULL ){
        printf ("I_x64CreateTID0: tid0_thread\n");
        return FALSE;
    }

    if ( tid0_thread->used != TRUE || 
         tid0_thread->magic != 1234 )
    {
        printf ("I_x64CreateTID0: tid0_thread validation\n");
        return FALSE;
    }

// tid
    if ( tid0_thread->tid != TID0_TID ){
        printf ("I_x64CreateTID0: TID0_TID");
        return FALSE;
    }

// owner pid
    if ( tid0_thread->ownerPID != GRAMADO_PID_KERNEL ){
        printf ("I_x64CreateTID0: GRAMADO_PID_KERNEL");
        return FALSE;
    }

// Memory

    tid0_thread->pml4_VA  = KernelProcess->pml4_VA;
    tid0_thread->pml4_PA  = KernelProcess->pml4_PA;

    tid0_thread->pdpt0_VA = KernelProcess->pdpt0_VA;
    tid0_thread->pdpt0_PA = KernelProcess->pdpt0_PA;

    tid0_thread->pd0_VA   = KernelProcess->pd0_VA;
    tid0_thread->pd0_PA   = KernelProcess->pd0_PA;

//
// tss
//

// #bugbug 
// #todo
    
    // tid0_thread->tss = current_tss;

// Priority

    set_thread_priority( 
        (struct thread_d *) tid0_thread, 
        PRIORITY_MAX );

// #importante
// Sinalizando que ainda não podemos usar as rotinas que dependam
// de que o dead thread collector esteja funcionando.
// Esse status só muda quando a thread rodar.

    dead_thread_collector_status = FALSE;

// Idle thread
// For now,
// the control thread of the window server will be our idle thread.
// But it is not actually a idle routine, 
// it is a standard server code.

    ____IDLE = (struct thread_d *) tid0_thread;
    UPProcessorBlock.IdleThread = (struct thread_d *) ____IDLE;

    //if ( UPProcessorBlock.IdleThread != ____IDLE)
    //   x_panic("here");


// ??
// This is the control thread of the kernel process.
// OK, the loadable tharead that belongs to the ws is
// the kernel process's control thread. :)

    if ((void*)KernelProcess != NULL)
    {
        KernelProcess->control = (struct thread_d *) ____IDLE;
    }

*/
    return TRUE;
}

void init_globals(void)
{
    int Status=FALSE;

// Inicializa as estruturas do fluxo padrão.
// Isso vai usar a file table.
    Status = (int) kstdio_initialize();
    if (Status != TRUE){
        panic("init_globals: kstdio_initialize fail\n");
    }

// Screen
// Now we can print strings in the screen.
// Reinitializing ... we already printed the banner.
    screenInit();

    //debug_print("init_globals: [printf] WE HAVE MESSAGES NOW!\n");
    //printf     ("init_globals: [printf] WE HAVE MESSAGES NOW!\n");

//
// SMP
//
    g_smp_initialized = FALSE;
    g_processor_count = 0;

// ===================

// Profiler
// See: 
// pints.h

// Legacy hardware interrupts (irqs) (legacy pic)
    g_profiler_ints_irq0  = 0;
    g_profiler_ints_irq1  = 0;
    g_profiler_ints_irq2  = 0;
    g_profiler_ints_irq3  = 0;
    g_profiler_ints_irq4  = 0;
    g_profiler_ints_irq5  = 0;
    g_profiler_ints_irq6  = 0;
    g_profiler_ints_irq7  = 0;
    g_profiler_ints_irq8  = 0;
    g_profiler_ints_irq9  = 0;
    g_profiler_ints_irq10 = 0;
    g_profiler_ints_irq11 = 0;
    g_profiler_ints_irq12 = 0;
    g_profiler_ints_irq13 = 0;
    g_profiler_ints_irq14 = 0;
    g_profiler_ints_irq15 = 0;
    // ...

// Interrupção para serviços do sistema.
    g_profiler_ints_gde_services = 0;
// User and group.
    current_user  = 0;
    current_group = 0;
// Security layers.
// user session, room(window station), desktop.
    current_usersession = (int) 0;
    current_room = (int) 0;
    current_desktop = (int) 0;

// Process, Thread.
// See: kernel.h   
    foreground_process = (pid_t) 0;
    foreground_thread = (tid_t) 0;
    //current_process = (pid_t) 0;
    set_current_process(0);  //?
    current_thread = (int) 0;

// The kernel request
// See: request.c
    clear_request();

// Messages
    g_new_message = 0;

//
// FS
//

// fs support
// FS type.
// type 1, fat16.
// #todo

    g_currentvolume_filesystem_type = FS_TYPE_FAT16;
    g_currentvolume_fatbits = (int) 16;
}

// ==============================
// I_init:
// Phases 1.
// Called in the initialization phase 0.
// Called by x64main in x64init.c
// OUT: TRUE if it is ok.

static int I_init(void)
{
    int Status = FALSE;
    unsigned char ProcessorType=0;

// #debug
    //debug_print ("I_init:\n");
    //printf      ("I_init:\n");

// ==================
// Check kernel phase.

    if (Initialization.current_phase != 1){
        printf ("I_init: Initialization phase is Not 1.\n");
        return FALSE;
    }

// ===============================
// Globals
    PROGRESS("Kernel:2:1: globals\n"); 
    init_globals();

// Nothing for now.
    //PROGRESS("Kernel:2:2\n"); 
    //PROGRESS("Kernel:2:3\n"); 

// ===============================
// Initialize device manager.
// see: dev/devmgr.c
    PROGRESS("Kernel:2:4 device manager\n"); 
    init_device_manager();

// ===============================
// Storage manager
// Ordem: storage, disk, volume, file system.
// #importante 
// A estrutura 'storage' vai ser o nível mais baixo.
// É nela que as outras partes devem se basear.

    PROGRESS("Kernel:2:5 storage, disk, volume, fs\n"); 

// Storage
    int st_status=FALSE;
    st_status = init_storage_support();
    if ( st_status != TRUE ){
       printf ("I_init: init_storage_support fail\n");
       return FALSE;
    }

// Disks and volumes.
// see: storage.c
    disk_init();
    volume_init();

// File systems support.
// see: fs.c
    //vfsInit();
    fsInit();
    // ...

// ==========================
// Network support.
// See: network.c
    PROGRESS("Kernel:2:6 network\n"); 
    networkInit();

// Nothing for now.
    //PROGRESS("Kernel:2:7\n"); 

// ===============================
// #important
// We need to be in the phase 1.

    //if (Initialization.current_phase != 1){
    //    printf ("I_init: Initialization phase is NOT 1.\n");
    //    return FALSE;
    //}

// ==========================
// hal
    PROGRESS("Kernel:2:8 hal\n"); 
    Status = init_hal();
    if (Status != TRUE){
        printf ("I_init: init_hal fail\n");
        return FALSE;
    }

// ==========================
// microkernel components:
// mm, ipc, ps ...
    PROGRESS("Kernel:2:9 microkernel\n"); 
    Status = init_microkernel();
    if (Status != TRUE){
        printf ("I_init: init_microkernel fail\n");
        return FALSE;
    }

// =========================================
// Executive components
    PROGRESS("Kernel:2:10 executive\n"); 
    Status = init_executive();
    if (Status != TRUE){
        printf ("I_init: init_executive fail\n"); 
        return FALSE;
    }

// =========================================
// Some gui components.
// #todo: rever 
    PROGRESS("Kernel:2:11 gramado, fat directories\n"); 
    Status = init_gramado();
    if (Status != TRUE){
        printf ("I_init: init_gramado fail\n"); 
        return FALSE;
    }

// FAT support.
    initialize_FAT_and_main_directories();

// =========================================
// Nothing for now.
    //PROGRESS("Kernel:2:12\n"); 

// =========================================
// 2:13: 
// Initialize processor information.
// + 'processor' structuture initialization.
// + Probing processor type.
// + Initialize fpu and smp support.
// + Detect the hypervisor.

    PROGRESS("Kernel:2:13 processor, fpu, smp, hv\n"); 

// --------
// 'processor' structuture initialization.
    processor = (void *) kmalloc( sizeof( struct processor_d ) ); 
    if ( (void *) processor == NULL ){
        printf("I_init: processor\n");
        return FALSE;
    }

// --------
// Probing processor type.
// #todo
// Check if cpuid instruction is available.
// See: _x86_test_cpuid_support on bootmx/headlib.asm
// #todo: extern int x86_test_cpuid_support(void);
// Sonda pra ver qual é a marca do processador.
// #todo: 
// É a segunda vez que fazemos a sondagem ?!
// See: hal/detect.c
// This routine is valid for intel and amd processors.
// Ok.
// Let's make some initialization and 
// get more information about the processor
// using the cpuid instruction.
// See: 
// detect.c
// x86.c
// cpuamd.c

    ProcessorType = (int) hal_probe_processor_type();
    processor->Type = (int) ProcessorType;

// --------
// Initialize fpu and smp support.

    int fpu_status = -1;     // fail
    int smp_status = FALSE;  // fail

    switch (ProcessorType){
    case Processor_INTEL:  
    case Processor_AMD:
        x64_init_intel();   
        //init_amd(); 
        fpu_status = (int) x64_init_fpu_support();
        if (fpu_status<0){
            printf("I_init: [FAIL] FPU Initialization fail\n");
            return FALSE;
        }

        // #debug
        // Testando a inicializaçao do lapic.
        // Tentando ler o id e a versao.
        // See: x64.c
        smp_status = (int) smp_probe();
        if (smp_status!=TRUE){
            printf("I_init: [FAIL] SMP probe fail\n");
            //return FALSE;
        
            //#debug
            //refresh_screen();
            //while(1){}
        }

        //#breakpoint
        //printf("#breakpoint in I_init()\n");
        //refresh_screen();
        //while(1){  asm ("cli");  }

        break;
    // ...
    default:
        printf ("I_init: [ERROR] default ProcessorType\n");
        return FALSE;
        break;
    };

// --------
// Detect the hypervisor.
// Saved into the processor data structure.
// Save the option found into a global variable.
// #todo: We need a structure for that thing.
// see: detect.c
    detect_hv();

// ======================
// Nothing for now.
    //PROGRESS("Kernel:2:14\n"); 
    //PROGRESS("Kernel:2:15\n"); 
    //PROGRESS("Kernel:2:16\n"); 

// ok
// Return to the main initialization routine
// in x64init.c
    return TRUE;

// ====================
// fail
// Return to the main initialization routine
// in x64init.c

//fail1:
    // If we already have printf verbose.
fail0:
    debug_print ("I_init: fail\n");
    return FALSE;
}


int I_x64main (void)
{
// Called by zero_initialize_x64().

    int Status = FALSE;

// -------------------------------
// Phase counter: 
// Starting phase 0.
// We already did that before in kmain().
    Initialization.current_phase = 0;

// The first ring3 process.
// Ainda não configuramos qual será o primeiro processo
// a rodar em user mode.
    InitialProcessInitialized = FALSE;

// Obs: 
// O video já foi inicializado em main.c.
// Isso atualiza a estrutura de console do console atual.
// #bugbug: 
// A inicialização não funciona, pois os elementos das estruturas
// não guardam os valores corretamente.
// Talvez está escrevendo em lugar inapropriado.
// #test: 
// Mudamos isso para o momento em que inicializamos os consoles.
 
    // #debug
    debug_print ("I_x64main:\n");

// #debug
// For real machine.
    //printf      ("I_x64main: [TODO]\n");
    //refresh_screen();

// System State
    if (system_state != SYSTEM_BOOTING){
        debug_print ("[x64] I_x64main: system_state\n");
        //x_panic     ("[x64] I_x64main: system_state\n");
        return FALSE;
    }

// System Arch
    if (current_arch != CURRENT_ARCH_X86_64){
        debug_print ("[x64] I_x64main: current_arch fail\n");
        //x_panic     ("[x64] I_x64main: current_arch fail\n");
        return FALSE;
    }

// Threads counter
    UPProcessorBlock.threads_counter = 0;

// ================================
// sse support.
    PROGRESS("Kernel:1:1\n"); 
    //debug_print ("[x64] I_x64main: [TODO] SSE support\n");
    // x86_sse_init();

// Status Flag and Edition flag.
    gSystemStatus = 1;
    gSystemEdition = 0;

// ===================================
// I_init
// Calling the main initialization routine.
// Antes de tudo: 
// CLI, Video, runtime.
// ## BUGBUG ##
// As mensagens do abort podem não funcionarem nesse caso.
// AINDA NÃO INICIALIZAMOS O RECURSO DE MENSAGENS.
// Essa rotina só pode ser chamada 
// durante essa fase da inicialização.
// See: sysinit.c

    PROGRESS("Kernel:1:2 \n"); 
    if (Initialization.current_phase != 0){
        debug_print ("I_x64main: Initialization phase is NOT 0.\n");
        return FALSE;
    }

// -------------------------------
// Starting phase 1.
    Initialization.current_phase = 1;

    Status = (int) I_init(); 
    if ( Status != TRUE ){
        printf ("I_x64main: I_init fail\n");
        return FALSE;
    }

// -------------------------------
// Starting phase 2.
    Initialization.current_phase = 2;
    // :)

// -------------------------------
// Starting phase 3.
    Initialization.current_phase = 3;

//================================
// Initialize all the kernel graphics support.
// Initialize all the kernel graphics support.
// some extra things like virtual terminal and tty.
// #todo: rever essa inicializaçao.
// See: graphics.c
// ================================
// Initialize window server manager.
// ws.c
// #debug:  
// Esperamos alcaçarmos esse alvo.
// Isso funcionou gigabyte/intel
// Vamos avançar
// Quem chamou essa funçao foi o começo da inicializaçao do kernel.
// Retornamos para x86main.c para arch x86.
// See: drivers/ws.c
// Initialize ws callback support.
// see: callback.c

    PROGRESS("Kernel:1:3 kgws, ws, ws callback\n"); 
    // Graphics infrastruture.
    KGWS_initialize();
    // ws registration support.
    ws_init();
    // ws callback support.
    initialize_ws_callback_info();

// ================================
// Nothing for now.
    //PROGRESS("Kernel:1:4\n"); 

// ================================
// DANGER !!!
// :::: GDT ::::
// Setup GDT again.
// We already made this at kernel startup.
// # Caution.
// Lets create a TSS and setup a GDT.
// This way we can use 'current_tss' when we create threads.
// This function creates a TSS and sets up a GDT.
// #todo
// Depois de renovarmos a GDT precisamos
// recarregar os registradores de segmento?
// See: hal/arch/x86/x86.c
// #bugbug
// see: x64.c

    PROGRESS("Kernel:1:5 gdt\n"); 
    x64_init_gdt();

// ================================
// Creating kernel process.
// Local
// It loads the window server's image and create
// a process structure to handle the kernel base and the
// window server's control thread.

    PROGRESS("Kernel:1:6 kernel process\n"); 
    Status = I_x64CreateKernelProcess();
    if (Status != TRUE){
        debug_print ("Couldn't create the Kernel process\n");
        return FALSE;
    }

// ================================
// Nothing for now
    //PROGRESS("Kernel:1:7\n"); 

// ================================
// Create the first ring3 process.
// INIT.BIN.

    PROGRESS("Kernel:1:8 init process\n"); 
    Status = I_x64CreateInitialProcess();
    if(Status != TRUE){
        debug_print ("Couldn't create the Initial process\n");
        return FALSE;
    }

//================================
// Nothing for now.
    // PROGRESS("Kernel:1:9\n"); 

// ================================
// Early ps/2 initialization.
// Initializing ps/2 controller.
// #todo: 
// Essa inicialização deve ser adiada.
// deixando para o processo init fazer isso.
// Chamaremos essa inicialização básica nesse momento.
// A inicialização completa será chamada pelo processo init.
// See: i8042.c
// ================
// Early initialization
// Only the keyboard.
// It is working
// ================
// This is the full initialization.
// #bugbug This is a test yet.
// It fails in the real machine.

    PROGRESS("Kernel:1:10 ps2\n"); 
    PS2_early_initialization();
    //PS2_initialization();

// Loading .BMP icon images.
    PROGRESS("Kernel:1:11 icons\n"); 
    windowLoadGramadoIcons();

// Nothing for now.
    //PROGRESS("Kernel:1:12\n"); 
    //PROGRESS("Kernel:1:13\n"); 
    //PROGRESS("Kernel:1:14\n"); 

    return TRUE;

// ================================
// The routine fails.

fail:
    // Nothing
    PROGRESS("Kernel:1:00 fail\n"); 
fail0:
    debug_print ("[x64] I_x64main: fail\n");
    refresh_screen(); 
    return FALSE;
}

