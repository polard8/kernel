
// x64init.c

#include <kernel.h>


extern unsigned long InitializationPhase;
int InitialProcessInitialized = FALSE;


// Task switching support.
extern void turn_task_switch_on (void);

extern void x64_clear_nt_flag (void);


/*
// #deprecated
// local
// Call a mm routine for that.
void x64init_load_pml4_table(unsigned long phy_addr)
{
    asm volatile ("movq %0,%%cr3"::"r"(phy_addr));
}
*/



// + Carrega a imagem do primeiro processo que vai rodar em user mode.
// + Configura sua estrutura de processo.
// + Configura sua estrutura de thraed.
// Não passa o comando para o processo.

void I_x64CreateInitialProcess (void)
{
    int fileret = -1;
    
    if ( system_state != SYSTEM_BOOTING )
        panic ("I_x64CreateInitialProcess: system_state\n");    

    //#todo
    debug_print ("I_x64CreateInitialProcess: [TODO]\n");
    printf      ("I_x64CreateInitialProcess: [TODO]\n");
    refresh_screen();



    //debug_print ("__x64CreateInitialProcess:\n");

//
// Load imag SM.BIN.
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

    fileret = (unsigned long) fsLoadFile ( 
                                  VOLUME1_FAT_ADDRESS, 
                                  VOLUME1_ROOTDIR_ADDRESS, 
                                  FAT16_ROOT_ENTRIES,    //#bugbug: number of entries.
                                  "SM      BIN", 
                                  (unsigned long) CONTROLTHREAD_BASE, //0x00200000
                                  BUGBUG_IMAGE_SIZE_LIMIT );

    // Coldn't load init.bin
    if ( fileret != 0 ){
        debug_print("I_x64CreateInitialProcess: Coldn't load init.bin \n");
        panic      ("I_x64CreateInitialProcess: Coldn't load init.bin \n");
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
        panic ("I_x64CreateInitialProcess: init_pml4_va\n");
    }

    init_mm_data.pml4_va = init_pml4_va;
    init_mm_data.pml4_pa = (unsigned long) virtual_to_physical ( 
                                               init_pml4_va, 
                                               gKernelPML4Address );

    if ( init_mm_data.pml4_pa == 0 ){
        panic ("I_x64CreateInitialProcess: init_mm_data.pml4_pa\n");
    }

    // ...

    init_mm_data.used  = TRUE;
    init_mm_data.magic = 1234;

// ===========================================

    InitProcess = (void *) create_process ( 
                               NULL, NULL, NULL, 
                               (unsigned long) CONTROLTHREAD_BASE, //0x00200000 
                               PRIORITY_HIGH, 
                               (int) KernelProcess->pid, 
                               "SM-PROCESS", 
                               RING3, 
                               (unsigned long ) init_pml4_va,
                               (unsigned long ) kernel_mm_data.pdpt0_va,
                               (unsigned long ) kernel_mm_data.pd0_va );

    if ( (void *) InitProcess == NULL ){
        panic ("I_x64CreateInitialProcess: InitProcess\n");
    }else{

        
        if ( init_mm_data.used != TRUE || init_mm_data.magic != 1234 )
        {
            panic ("I_x64CreateInitialProcess: init_mm_data validation\n");
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

        InitProcess->position = SPECIAL_GUEST;
        fs_initialize_process_cwd ( InitProcess->pid, "/" );
    };

//====================================================
// Create thread

    // #
    // Criamos um thread em ring3.
    // O valor de eflags é 0x3200.

    InitThread = (void *) create_CreateRing3InitThread();

    if ( (void *) InitThread == NULL ){
        panic ("I_x64CreateInitialProcess: InitThread\n");
    }else{

        // Herdando do processo configurado logo antes.
        InitThread->pml4_VA  = InitProcess->pml4_VA;
        InitThread->pml4_PA  = InitProcess->pml4_PA;
        InitThread->pdpt0_VA = InitProcess->pdpt0_VA;
        InitThread->pdpt0_PA = InitProcess->pdpt0_PA;
        InitThread->pd0_VA   = InitProcess->pd0_VA;
        InitThread->pd0_PA   = InitProcess->pd0_PA;


        InitThread->position = SPECIAL_GUEST;

        //IdleThread->ownerPID = (int) InitProcess->pid;

        // #todo #bugbug
        //InitThread->tss = current_tss;
        
        
        // [Processing time]
        current_process = InitProcess->pid;
        current_thread  = InitThread->tid;
        
        // [Focus]
        active_process = current_process;
        active_thread  = current_thread;
        
        // foreground thread ?
        
        // [Scheduler stuff]
        next_thread = InitThread->tid;
    };


    // This is a very good idea !
    // The init process has a bigger heap than 
    // the other ring3 processes.

    //if ( g_extraheap1_va != EXTRAHEAP1_VA )
    //{
    //    debug_print("__x86StartInit: [ERROR] g_extraheap1_va != EXTRAHEAP1_VA\n");
    //    while(1){}
    //}

    // #todo #bugbug
    InitProcess->Heap = (unsigned long) g_extraheap1_va;

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
}



// Passa o comando para o primeiro processo em user mode.
// Esse processo ja foi previamente configurado.

void I_x64ExecuteInitialProcess (void)
{
    struct thread_d  *Thread;
    int i=0;

    //#todo
    debug_print ("I_x64ExecuteInitialProcess: [TODO]\n");
    printf      ("I_x64ExecuteInitialProcess: [TODO]\n");
    refresh_screen();
   
    if ( system_state != SYSTEM_BOOTING )
        panic ("I_x64ExecuteInitialProcess: system_state\n");    


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

    Thread = InitThread; 


    if ( (void *) Thread == NULL ){
        debug_print ("I_x64ExecuteInitialProcess: Thread\n");
        panic       ("I_x64ExecuteInitialProcess: Thread\n");
    }

    if ( Thread->used != TRUE || Thread->magic != 1234 )
    {
        debug_print ("I_x64ExecuteInitialProcess: Thread validation\n");
        //printf ("I_x64ExecuteInitialProcess: tid={%d} magic \n", 
        //    Thread->tid);
        die();
    }

    // It its context is already saved, so this is not the fist time.
    
    if ( Thread->saved != FALSE ){
        panic("I_x64ExecuteInitialProcess: saved\n");
    }

    if ( Thread->tid < 0 ){
        panic("I_x64ExecuteInitialProcess: tid\n");
    }

    // Set the current thread.
    set_current( Thread->tid ); 
    
    // ...

    // State
    // The thread needs to be in Standby state.

    if ( Thread->state != STANDBY )
    {
        printf ("I_x64ExecuteInitialProcess: state tid={%d}\n", 
            Thread->tid);
        die();
    }

    // * MOVEMENT 2 ( Standby --> Running)
    if ( Thread->state == STANDBY )
    {
        Thread->state = RUNNING;
        
        //
        // #bugbug
        //
        
        debug_print("I_x64ExecuteInitialProcess: [FIXME] Overflow\n");
        
        //queue_insert_data( 
        //    queue, 
        //    (unsigned long) Thread, 
        //    QUEUE_RUNNING );
    }

    // Current process.

    current_process = Thread->process->pid;

//
// List
//
    for ( i=0; i < PRIORITY_MAX; i++ ){
        dispatcherReadyList[i] = (unsigned long) Thread;
    };
    IncrementDispatcherCount (SELECT_IDLE_COUNT);


//
// # check this
//

    // turn_task_switch_on:
    //  + Creates a vector for timer irq, IRQ0.
    //  + Enable taskswitch. 

    turn_task_switch_on();


    // #todo
    // Isso deve ser liberado pelo processo init
    // depois que ele habilitar as interrupções.
    
    taskswitch_lock();
    scheduler_lock();


    // timerInit8253 ( HZ );
    // timerInit8253 ( 800 );
    // timerInit8253 ( 900 );

    // See: hal/
    x64_load_pml4_table( Thread->pml4_PA );

    // #bugbug: rever isso.
    asm ("movq %cr3, %rax");
    asm ("movq %rax, %cr3");

//
// # check this
//
    // See: headlib.asm
    // Se nao limpar, um iret causa taskswitch

    x64_clear_nt_flag();   

    // #maybe
	//vamos iniciar antes para que
	//possamos usar a current_tss quando criarmos as threads
	//x64_init_gdt ();

    // ??
    asm ("clts \n");

	// #importante
	// Mudamos para a última fase da inicialização.
	// Com isso alguns recursos somente para as fases anteriores
	// deverão ficar indisponíveis.

// End of phase.
// Starting phase 4.

    InitializationPhase = 4;

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

    int elfStatus = -1;
    elfStatus = (int) fsCheckELFFile ( (unsigned long) CONTROLTHREAD_BASE );
    if ( elfStatus < 0 ){
        debug_print ("I_x64ExecuteInitialProcess: .ELF signature\n");
        panic       ("I_x64ExecuteInitialProcess: .ELF signature");
    }

// ==============
// #debug

    debug_print("I_x64ExecuteInitialProcess: [x64] Go to user mode! IRETQ\n");
    printf     ("I_x64ExecuteInitialProcess: [x64] Go to user mode! IRETQ\n");
    refresh_screen();

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

    if (Thread->iopl != RING3 ){
        panic ("I_x64ExecuteInitialProcess: iopl");
    }

    PROGRESS("-- Fly -----------------------------------\n");

    unsigned long entry = 0x201000;
    unsigned long rsp3  = 0x00000000002FFFF0;
    asm volatile ( 
        " movq $0, %%rax    \n" 
        " mov %%ax, %%ds    \n" 
        " mov %%ax, %%es    \n" 
        " mov %%ax, %%fs    \n" 
        " mov %%ax, %%gs    \n" 
        " movq %0, %%rax    \n" 
        " movq %1, %%rsp    \n" 
        " movq $0, %%rbp    \n" 
        " pushq $0x23       \n"  
        " pushq %%rsp       \n" 
        " pushq $0x3002     \n"  // Interrupts disabled for the first thread.
        " pushq $0x1B       \n" 
        " pushq %%rax       \n" 
        " iretq             \n" :: "D"(entry), "S"(rsp3) );

// ====
// Paranoia

    PROGRESS("-- iretq fail ------------\n");
    panic ("I_x64ExecuteInitialProcess: [FIXME] *breakpoint\n");
}


// Local
void __CreateKernelProcess(void)
{
    debug_print ("__CreateKernelProcess:\n");

    // IN: 
    // Room, Desktop, Window
    // base address, priority, ppid, name, iopl, page directory address.
    // See: ps/action/process.c
    
    KernelProcess = (void *) create_process ( 
                                 NULL, NULL, NULL, 
                                 (unsigned long) 0x30000000, 
                                 PRIORITY_HIGH, 
                                 (int) 0, 
                                 "KERNEL-PROCESS", 
                                 RING0,   
                                 (unsigned long ) gKernelPML4Address,
                                 (unsigned long ) kernel_mm_data.pdpt0_va,
                                 (unsigned long ) kernel_mm_data.pd0_va );

    if ( (void *) KernelProcess == NULL ){
        panic ("__CreateKernelProcess: KernelProcess\n");
    }

    if ( kernel_mm_data.used != TRUE || 
         kernel_mm_data.magic != 1234 )
    {
        panic ("__CreateKernelProcess: kernel_mm_data validation\n");
    }

    KernelProcess->pml4_VA = kernel_mm_data.pml4_va;
    KernelProcess->pml4_PA = kernel_mm_data.pml4_pa; 

    KernelProcess->pdpt0_VA = kernel_mm_data.pdpt0_va;
    KernelProcess->pdpt0_PA = kernel_mm_data.pdpt0_pa; 

    KernelProcess->pd0_VA = kernel_mm_data.pd0_va;
    KernelProcess->pd0_PA = kernel_mm_data.pd0_pa; 

    KernelProcess->position = KING;
    
    fs_initialize_process_cwd ( KernelProcess->pid, "/" ); 
    
    //...
}

// local
void __CreateEarlyRing0IdleThread(void)
{
    debug_print ("__CreateEarlyRing0IdleThread:\n");

//
// Thread
//

    EarlyRING0IDLEThread = (void *) create_CreateEarlyRing0IdleThread();

    if ( (void *) EarlyRING0IDLEThread == NULL ){
        panic ("__CreateEarlyRing0IdleThread: EarlyRING0IDLEThread\n");
    }

//
// Memory
//

    EarlyRING0IDLEThread->pml4_VA  = KernelProcess->pml4_VA;
    EarlyRING0IDLEThread->pml4_PA  = KernelProcess->pml4_PA;

    EarlyRING0IDLEThread->pdpt0_VA = KernelProcess->pdpt0_VA;
    EarlyRING0IDLEThread->pdpt0_PA = KernelProcess->pdpt0_PA;

    EarlyRING0IDLEThread->pd0_VA   = KernelProcess->pd0_VA;
    EarlyRING0IDLEThread->pd0_PA   = KernelProcess->pd0_PA;


//
// Idle thread
//

    // Idle thread
    // #todo
    // We can use a method in the scheduler for this.
    // Or in the dispatcher?

    ____IDLE = (struct thread_d *) EarlyRING0IDLEThread;


    // ?
    // Set position.

    EarlyRING0IDLEThread->position = KING;


//
// tss
//

    // #bugbug 
    // #todo
    
    // EarlyRING0IDLEThread->tss = current_tss;

    set_thread_priority ( 
        (struct thread_d *) EarlyRING0IDLEThread,
        PRIORITY_MIN );

    // #importante
    // Sinalizando que ainda não podemos usar as rotinas que dependam
    // de que o dead thread collector esteja funcionando.
    // Esse status só muda quando a thread rodar.

    dead_thread_collector_status = FALSE;
}


/*
 *************************************************
 * I_x64main: 
 *
 * Function history:
 *     2015 - Created by Fred Nora.
 */

// Initialization phases:
// 0 - I_x64main()
// 1 - See: I_init()
// 2 - See: I_init()
// 3 - See: I_x64main()
// 4 - See: I_x64main()

// Called by kernel_main in init.c

int I_x64main (void)
{
    int Status=0;


// ============================
// Phase counter

// Starting phase 0.

    InitializationPhase = 0;


// ============================
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
    debug_print ("I_x64main: [TODO]\n");
    printf      ("I_x64main: [TODO]\n");
    refresh_screen();


//
// System State
//

    if ( system_state != SYSTEM_BOOTING ){
        debug_print ("[x64] I_x64main: system_state\n");
        x_panic     ("[x64] I_x64main: system_state\n");
    }

//
// System Arch
//

    if (current_arch != CURRENT_ARCH_X86_64){
        debug_print ("[x64] I_x64main: current_arch fail\n");
        x_panic     ("[x64] I_x64main: current_arch fail\n");
    }

//
// Threads counter
//

    UPProcessorBlock.threads_counter = 0;


// ================================
// sse support.

    PROGRESS("Kernel:1:1\n"); 
    debug_print ("[x64] I_x64main: [TODO] SSE support\n");
    // x86_sse_init();


// ================================
// Status Flag

    gSystemStatus = 1;

// ================================
// Edition flag ?

    gSystemEdition = 0;

// =========================
// Hypervisor
// Initializing the variable.
// We will check the hv and change this flag.
// Not qemu for now.

    g_is_qemu = FALSE;


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

    PROGRESS("Kernel:1:2\n"); 
    debug_print ("I_x64main: Calling I_init()\n");

    if ( InitializationPhase != 0 ){
        x_panic ("I_x64main: InitializationPhase\n");
        //KiAbort();
    }

    // Phases 1 and 2.
    Status = (int) I_init(); 
    if ( Status != 0 ){
        debug_print ("I_x64main: I_init fail\n");
        x_panic     ("I_x64main: I_init fail\n");
    }

// End of phase.
// Starting phase 3.

    InitializationPhase = 3;

//================================
    PROGRESS("Kernel:1:3\n"); 
    // Initialize all the kernel graphics support.

    // Initialize all the kernel graphics support.
    // some extra things like virtual terminal and tty.
    // #todo: rever essa inicializaçao.
    
    // See: 
    // users/kgws.c

    KGWS_initialize();

    // debug
    //printf("~kgws\n");
    //refresh_screen();
    //while(1){}


// ================================
// user/ ?
// Initialize window server manager.
// ws.c
// #debug:  
// Esperamos alcaçarmos esse alvo.
// Isso funcionou gigabyte/intel
// Vamos avançar
// Quem chamou essa funçao foi o começo da inicializaçao do kernel.
// Retornamos para x86main.c para arch x86.

    PROGRESS("Kernel:1:4\n"); 
    ws_init();

// ================================
// GDT
// Setup GDT again.
// We already made this at kernel startup.
// # Caution.
// Lets create a TSS and setup a GDT.
// This way we can use 'current_tss' when we create threads.
// This function creates a TSS and sets up a GDT.
// See: hal/arch/x86/x86.c
// #todo
// Depois de renovarmos a GDT precisamos
// recarregar os registradores de segmento?

//
// DANGER !!!
//

    PROGRESS("Kernel:1:5\n"); 
    debug_print ("[x64] I_x64main: [DANGER] Initializing GDT\n");
    printf      ("[x86] I_x64main: Initializing GDT\n");      
    x64_init_gdt();


// ================================
// Creating kernel process.
// Local

    PROGRESS("Kernel:1:6\n"); 
    __CreateKernelProcess();

// ================================
// Creating a ring 0 thread for the kernel.
// Local

    PROGRESS("Kernel:1:7\n"); 
    __CreateEarlyRing0IdleThread();


// ================================
// Session Manager.
// Cria e inicializa apenas o SM.BIN
// Local routine.
// + Carrega a imagem do primeiro processo que vai rodar em user mode.
// + Configura sua estrutura de processo.
// + Configura sua estrutura de thraed.
// Não passa o comando para o processo.

    PROGRESS("Kernel:1:8\n"); 
    I_x64CreateInitialProcess();

//================================
// Check some initialization flags.
    PROGRESS("Kernel:1:9\n"); 


/*
#ifdef  ENTRY_DEBUG_CHECK_VALIDATIONS

    Status = (int) debug();

    if ( Status != 0 ){
        printf ("[x86] x86main: debug\n");
        system_state = KERNEL_ABORTED;
        goto fail;
    }

#endif
*/


	// ======== # TESTS # ========
	// begin - We can make some tests here.

    //Inicializando as variáveis do cursor piscante do terminal.
    //isso é um teste.
    
    //timer_cursor_used   = 0;   //desabilitado.
    //timer_cursor_status = 0;

// ================================
// Early ps/2 initialization.
// Initializing ps/2 controller.
// #todo: 
// Essa inicialização deve ser adiada.
// deixando para o processo init fazer isso.
// Chamaremos essa inicialização básica nesse momento.
// A inicialização completa será chamada pelo processo init.
// See: i8042.c

    PROGRESS("Kernel:1:10\n"); 
    debug_print ("[x64] I_x64main: ps2\n");      
    //PS2_initialize();           // This one will be called by the ring3 application.
    PS2_early_initialization();   // Use this one now.

// ================================
// Loading some system files.
// icons, bmps, etc ...
// Loading file tests.
// #test:
// Background support.
// Used to test load_path()
// See: ws/bg.c
// #Aviso:
// Isso funcionou, não mudar de lugar.
// Mas isso faz parte da interface gráfica,
// Só que somente nesse momento temos recursos 
// suficientes para essa rotina funcionar.

    PROGRESS("Kernel:1:11\n"); 
    //bg_load_image ();
    //windowLoadGramadoIcons();

// ================================
// Font support.
// #bugbug
// Font is independent from the x86 archtechture.
// We can do this in some other place. Maybe :)
// See: config/config.h

    PROGRESS("Kernel:1:12\n"); 
    //gfontSize = DEFAULT_FONT_SIZE;


// ================================
// Testing some rectangle support.

    PROGRESS("Kernel:1:13\n"); 

// ================================
// Done
// The routine is over.
// The caller will start the first thread create by us.
// The expected return value is 1234.

    PROGRESS("Kernel:1:14\n"); 
    debug_print ("[x64] I_x64main: done\n");
    debug_print ("==============\n");

    return (int) 1234;

// ================================
// The routine fails.

fail:
    // Nothing
    PROGRESS("Kernel:1:00\n"); 
fail0:
    debug_print ("[x64] I_x64main: fail\n");
    refresh_screen(); 
    return (int) (-1);
}



