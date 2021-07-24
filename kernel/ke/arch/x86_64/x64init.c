
// x64init.c

#include <kernel.h>


extern unsigned long InitializationPhase;
int InitialProcessInitialized = FALSE;


// Task switching support.
extern void turn_task_switch_on (void);

extern void x64_clear_nt_flag (void);


// local
void x64init_load_pml4_table(unsigned long phy_addr)
{
    asm volatile ("movq %0,%%cr3"::"r"(phy_addr));
}


// Local routine.
// + Carrega a imagem do primeiro processo que vai rodar em user mode.
// + Configura sua estrutura de processo.
// + Configura sua estrutura de thraed.
// Não passa o comando para o processo.

void __x64CreateInitialProcess (void)
{
    //#todo
    debug_print ("__x64CreateInitialProcess: [TODO]\n");
    printf      ("__x64CreateInitialProcess: [TODO]\n");
    refresh_screen();


    int fileret = -1;

    debug_print ("__x64CreateInitialProcess:\n");

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
        debug_print("__x64CreateInitialProcess: Coldn't load init.bin \n");
        panic      ("__x64CreateInitialProcess: Coldn't load init.bin \n");
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
        panic ("__x64CreateInitialProcess: init_pml4_va\n");
    }

    init_mm_data.pml4_va = init_pml4_va;
    init_mm_data.pml4_pa = (unsigned long) virtual_to_physical ( 
                                               init_pml4_va, 
                                               gKernelPML4Address );

    if ( init_mm_data.pml4_pa == 0 ){
        panic ("__x64CreateInitialProcess: init_mm_data.pml4_pa\n");
    }

    // ...

    init_mm_data.used  = TRUE;
    init_mm_data.magic = 1234;

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
        panic ("__x64CreateInitialProcess: InitProcess\n");
    }else{

        
        if ( init_mm_data.used != TRUE || init_mm_data.magic != 1234 )
        {
            panic ("__x64CreateInitialProcess: init_mm_data validation\n");
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
        panic ("__x64CreateInitialProcess: InitThread\n");
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

void x64ExecuteInitialProcess (void)
{
    //#todo
    debug_print ("x64ExecuteInitialProcess: [TODO]\n");
    printf      ("x64ExecuteInitialProcess: [TODO]\n");
    refresh_screen();
   
    
    struct thread_d  *Thread;
    int i=0;


    // Se essa rotina foi chamada antes mesmo
    // do processo ter sido devidamente configurado.

    if ( InitialProcessInitialized != TRUE ){
        debug_print ("x64ExecuteInitialProcess: InitialProcessInitialized\n");
        panic       ("x64ExecuteInitialProcess: InitialProcessInitialized\n");
    }

    // The first thread to run will the control thread 
    // of the init process. It is called InitThread.

    Thread = InitThread; 


    if ( (void *) Thread == NULL ){
        debug_print ("x64ExecuteInitialProcess: Thread\n");
        panic       ("x64ExecuteInitialProcess: Thread\n");
    }

    if ( Thread->used != TRUE || Thread->magic != 1234 )
    {
        debug_print ("x64ExecuteInitialProcess: Thread validation\n");
        //printf ("x64ExecuteInitialProcess: tid={%d} magic \n", 
        //    Thread->tid);
        die();
    }

    // It its context is already saved, so this is not the fist time.
    
    if ( Thread->saved != FALSE ){
        panic("x64ExecuteInitialProcess: saved\n");
    }

    if ( Thread->tid < 0 ){
        panic("x64ExecuteInitialProcess: tid\n");
    }

    // Set the current thread.
    set_current( Thread->tid ); 
    
    // ...

    // State
    // The thread needs to be in Standby state.

    if ( Thread->state != STANDBY )
    {
        printf ("x64ExecuteInitialProcess: state tid={%d}\n", 
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
        
        debug_print("x64ExecuteInitialProcess: [FIXME] Overflow\n");
        
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

    // local
    x64init_load_pml4_table( Thread->pml4_PA );

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

    InitializationPhase = 4;

	// # go!
	// Nos configuramos a idle thread em user mode e agora vamos saltar 
	// para ela via iret.

	// #todo:
	// #importante:
	// Podemos usr os endereços que estão salvos na estrutura.

	//#bugbug:
	//temos a questão da tss:
	//será que a tss está configurada apenas para a thread idle do INIT ??
	//temos que conferir isso.

	//base dos arquivos.

    // #todo
    // Rever se estamos usando a base certa.

    // init.bin (ELF)
 
    // Image base.
    // 0x00200000
    unsigned char *buff1 = (unsigned char *) CONTROLTHREAD_BASE;

    if ( buff1[0] != 0x7F ||
         buff1[1] != 'E' || buff1[2] != 'L' || buff1[3] != 'F' )
    {
        debug_print ("x64ExecuteInitialProcess: init .ELF signature\n");
        panic       ("x64ExecuteInitialProcess: init .ELF signature");
    }

    // #debug
    debug_print("x64ExecuteInitialProcess: [x64] Go to user mode! IRETQ\n");
    printf     ("x64ExecuteInitialProcess: [x64] Go to user mode! IRETQ\n");
    refresh_screen();


    PROGRESS("-- Fly -----------------------------------\n");

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

    // Fly!
    // We need to have the same stack in the TSS.
    // ss, rsp, rflags, cs, rip;

//
// #todo
//

    // See:
    // gva.h

    // ok, funciona
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
        " pushq $0x3002     \n" 
        " pushq $0x1B       \n" 
        " pushq %%rax       \n" 
        " iretq             \n" :: "D"(entry), "S"(rsp3) );
  
    PROGRESS("-- iretq fail -----------------\n");

    // Paranoia
    panic ("x64ExecuteInitialProcess: [FIXME] *breakpoint\n");
}


/*
 *************************************************
 * x86main: 
 *
 * Function history:
 *     2015 - Created by Fred Nora.
 */

// Called by kernel_main.

int x64main (void)
{
    int Status=0;
    
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
 
    debug_print ("x64main: [TODO]\n");
    printf      ("x86main: [TODO]\n");
    refresh_screen();

    if (current_arch != CURRENT_ARCH_X86_64)
    {
        debug_print ("[x64] x64main: current_arch fail\n");
        x_panic     ("[x64] x64main: current_arch fail\n");
    }

    // Threads counter.

    UPProcessorBlock.threads_counter = 0;


//================================
    PROGRESS("Kernel:1:1\n"); 
    // sse support.

    debug_print ("[x64] x64main: [TODO] SSE support\n");
    // x86_sse_init();

//
// ======================================================
//
    //
    // == phase 0 ========================================
    //

    // Essa eh uma boa rotina pra inicializar o contador de fases.
    // Set Kernel phase.  
    // Status Flag.
    // edition flag.
    
    InitializationPhase = 0;

    gSystemStatus = 1;
    
    // ?? #todo: this is not a x86 thing.
    gSystemEdition = 0;

//
// Hypervisor
//
    // Initializing the variable.
    // #todo: this is not a x86 thing.

    g_is_qemu = FALSE;

//
// ===============================================================
//

	// Antes de tudo: 
	// CLI, Video, runtime.

	// ## BUGBUG ##
	// As mensagens do abort podem não funcionarem nesse caso.
	// AINDA NÃO INICIALIZAMOS O RECURSO DE MENSAGENS.

    // Essa rotina só pode ser chamada 
    // durante essa fase da inicialização.

    if ( InitializationPhase != 0 ){
        x_panic ("x64main: InitializationPhase\n");
    }

//================================
    PROGRESS("Kernel:1:2\n"); 
    // Calling 'init' kernel module. 

    // See: 
    // core/init.c

    debug_print ("x64main: Calling init()\n");

    Status = (int) init(); 
 
    if ( Status != 0 )
    {
        debug_print ("x64main: init fail\n");
        x_panic     ("x64main: init fail\n");
    }

    // ...

    // Testando o funcionamento das estruturas de console. tty.
    //set_up_cursor(0,1);
    //console_outbyte('f',fg_console);

    //printf("*breakpoint\n");
    //refresh_screen();
    //while(1){}


// Done: 
//     Completas as 3 fases de inicialização do sistema.
//     @todo: Na verdade serão mais fases..
//           as fases estão em init().

    //printf ("x86main: done\n");

//
// ====================================================================
//

	//#debug 
	//a primeira mensagem só aparece após a inicialização da runtime.
	//por isso não deu pra limpar a tela antes.


//#ifdef BREAKPOINT_TARGET_AFTER_SYSTEM
    //printf ("x86main: *breakpoint\n");
    //refresh_screen(); 
    //while (1){ asm ("hlt"); }
//#endif


    //printf("======================\n");
    //printf("x86main: end of phase 2\n");

//
// == phase 3 ? ================================================
//
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


//================================
    PROGRESS("Kernel:1:4\n"); 
    // Initialize window server manager.

    // 2io/ws.c
    ws_init();

    // debug
    //printf("~ws\n");
    //refresh_screen();
    //while(1){}

    // #debug:  
    // Esperamos alcaçarmos esse alvo.
    // Isso funcionou gigabyte/intel
    // Vamos avançar
    // Quem chamou essa funçao foi o começo da inicializaçao do kernel.
    // Retornamos para x86main.c para arch x86.

    debug_print ("x64main: done\n");
    debug_print ("====\n");
    
    //printf("*breakpoint\n");
    //refresh_screen();
    //while(1){}


//================================
    PROGRESS("Kernel:1:5\n"); 
    // Setup GDT again.
    // We already made this at kernel startup.

    // # Caution.
    // Lets create a TSS and setup a GDT.
    // This way we can use 'current_tss' when we create threads.
    // This function creates a TSS and sets up a GDT.
    // See: hal/arch/x86/x86.c

    debug_print ("[x64] x64main: [DANGER] Initializing GDT\n");
    //printf      ("[x86] x86main: Initializing GDT\n");


//
// DANGER !!!
//
        
    x64_init_gdt();


    // #todo
    // Depois de renovarmos a GDT precisamos
    // recarregar os registradores de segmento.

    //printf("*breakpoint\n");
    //refresh_screen();
    //while(1){}

    //
    // == Processes and threads ===================================
    //


    debug_print ("[x64] x64main: processes and threads\n");
    //printf      ("[x86] x86main: processes and threads\n");


//================================
    PROGRESS("Kernel:1:6\n"); 
    // Creating kernel process.

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
        panic ("x64main: KernelProcess\n");
    }else{

        if ( kernel_mm_data.used != TRUE || kernel_mm_data.magic != 1234 )
        {
            panic ("x64main: kernel_mm_data validation\n");
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
    };



//================================
    PROGRESS("Kernel:1:7\n"); 
    // Creating a ring 0 thread for the kernel.

    EarlyRING0IDLEThread = (void *) create_CreateEarlyRing0IdleThread();

    if ( (void *) EarlyRING0IDLEThread == NULL ){
        panic ("x64main: EarlyRING0IDLEThread\n");
    }else{

        EarlyRING0IDLEThread->pml4_VA  = KernelProcess->pml4_VA;
        EarlyRING0IDLEThread->pml4_PA  = KernelProcess->pml4_PA;
        EarlyRING0IDLEThread->pdpt0_VA = KernelProcess->pdpt0_VA;
        EarlyRING0IDLEThread->pdpt0_PA = KernelProcess->pdpt0_PA;
        EarlyRING0IDLEThread->pd0_VA   = KernelProcess->pd0_VA;
        EarlyRING0IDLEThread->pd0_PA   = KernelProcess->pd0_PA;

        // Idle thread
        // #todo
        // We can use a method in the scheduler for this.
        // Or in the dispatcher?

        ____IDLE = (struct thread_d *) EarlyRING0IDLEThread;

        EarlyRING0IDLEThread->position = KING;

        // #bugbug #todo
        // EarlyRING0IDLEThread->tss = current_tss;

        set_thread_priority ( 
            (struct thread_d *) EarlyRING0IDLEThread,
            PRIORITY_MIN );

		// #importante
		// Sinalizando que ainda não podemos usar as rotinas que dependam
		// de que o dead thread collector esteja funcionando.
		// Esse status só muda quando a thread rodar.

        dead_thread_collector_status = FALSE;
    };


//================================
    PROGRESS("Kernel:1:8\n"); 
    // Session Manager.
    // Cria e inicializa apenas o SM.BIN

// Local routine.
// + Carrega a imagem do primeiro processo que vai rodar em user mode.
// + Configura sua estrutura de processo.
// + Configura sua estrutura de thraed.
// Não passa o comando para o processo.

    __x64CreateInitialProcess();

    //printf("*breakpoint\n");
    //refresh_screen();
    //while(1){}


//================================
    PROGRESS("Kernel:1:9\n"); 
    // Check some initialization flags.
    


	// ======== # TESTS # ========
	// begin - We can make some tests here.

    //Inicializando as variáveis do cursor piscante do terminal.
    //isso é um teste.
    
    //timer_cursor_used   = 0;   //desabilitado.
    //timer_cursor_status = 0;

//================================
    PROGRESS("Kernel:1:10\n"); 
    // Early ps/2 initialization.

	// Initializing ps/2 controller.
	//#DEBUG
	//printf ("testing ps2\n");
	//refresh_screen(); 

    debug_print ("[x64] x64main: ps2\n");      
    
    // #todo: 
    // Essa inicialização deve ser adiada.
    // deixando para o processo init fazer isso.
    // Chamaremos essa inicialização básica nesse momento.
    // A inicialização completa será chamada pelo processo init.
    // See: i8042.c

    //PS2_initialize();           // This one will be called by the ring3 application.
    PS2_early_initialization();   // Use this one now.



//================================
    PROGRESS("Kernel:1:11\n"); 
    // Loading some system files.
    // icons, bmps, etc ...
    
    // Loading file tests.
    // #test:
    // Background support.
    // Used to test load_path()
    // See: ws/bg.c
    
    //bg_load_image ();
    //refresh_screen();
    //while(1){}

	// #Aviso:
	// Isso funcionou, não mudar de lugar.
	// Mas isso faz parte da interface gráfica,
	// Só que somente nesse momento temos recursos 
	// suficientes para essa rotina funcionar.

    //windowLoadGramadoIcons();

    //printf("*breakpoint\n");
    //refresh_screen();
    //while(1){}


//================================
    PROGRESS("Kernel:1:12\n"); 
    // font support.

    //
    // Fonts.
    //
    
    // #bugbug
    // Font is independent from the x86 archtechture.
    // We can do this in some other place. Maybe :)
 
    // See: config/config.h
    //gfontSize = DEFAULT_FONT_SIZE;



//================================
    PROGRESS("Kernel:1:13\n"); 
    // Testing some rectangle support.

//done:
//================================
    PROGRESS("Kernel:1:14\n"); 
    // Start first thread ever.

    debug_print ("[x64] x64main: done\n");
    debug_print ("==============\n");

    // debug
    //printf("T\n");
    //refresh_screen();
    //while(1){}

//
// Starting idle thread.
//

    /*
    if ( KernelStatus == KERNEL_INITIALIZED )
    {
        debug_print ("[x86] x86main: Initializing INIT ..\n");
        printf      ("[x86] x86main: Initializing INIT ..\n");
        
#ifdef KERNEL_VERBOSE
    refresh_screen();
#endif

        //
        // No return!
        //

        x64mainStartFirstThread(); 

        panic("x86mainStartFirstThread: Couldn't spawn the first thread!\n");
    }
    */





//
// #todo
//

    // Estamos trabalhando nessa rotina, pois é ela que faz o salto
    // para ring3. O salto esta falhando.
    
    // #todo
    // pegar o retorno dessa funçao e retornar para quem nos chamou.
    
    // This will be called by the init.c in init/
    //debug_print ("x64main: Calling x64ExecuteInitialProcess()\n");
    //x64ExecuteInitialProcess();

    // Expected return value.

    return (int) 1234;

    // #test
    // Estamos usando esse retorno ate fazermos achamada logo acima.

    //return 0;

   

// ===============================

// ===============================

// fail
// #todo
// Uma opção aqui é usarmos a tipagem void para essa função
// e ao invés de retornarmos, apenas entrarmos na thread idle
// em ring 0, isso depois de criadas as threads em user mode.

fail:
//================================
    PROGRESS("Kernel:1:00\n"); 
    debug_print ("[x64] x64main: fail\n");
    refresh_screen (); 
    return -1;
}




















