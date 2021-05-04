/*
 * File: x86/x86init.c 
 *
 * Description:
 *     It's is the initialization for x86 architechture.
 *     x86main was called by kernel/main.c
 *
 * The Kernel area is the first 4MB of real memory.
 * The image was loaded in the address 0x00100000 and the entry point 
 * is in the address 0x00101000. 
 * The logic address for the Kernel image is 0xC0001000 and the 
 * entry point is 0xC0001000.
 * 
 * #todo: 
 * Create a log file.
 *
 *  In this file:
 *  ============
 *      + __x86StartInit
 *      + clean_nt_flag
 *      + mainSetCr3
 *      + turn_task_switch_on
 *      + x86main - The entry point for a C part of the Kernel.
 *      + x86mainStartFirstThread
 * 
 * Revision History:
 *     2015      - Created by Fred Nora.
 *     2020      - Last revision.
 *     //... 
 */ 


#include <kernel.h>


// # external dependencies #

// Variables from Boot Loader.
extern unsigned long SavedBootBlock;    // Boot Loader Block.
extern unsigned long SavedLFB;          // LFB address.
extern unsigned long SavedX;            // Screen width.
extern unsigned long SavedY;            // Screen height.
extern unsigned long SavedBPP;          // Bits per pixel.
// ...


// Args.
extern unsigned long kArg1;
extern unsigned long kArg2;
extern unsigned long kArg3;
extern unsigned long kArg4;
//...

// Boot mode.
extern unsigned long SavedBootMode;

// Task switching support.
extern void turn_task_switch_on (void);

extern void x86_clear_nt_flag (void);



// local
// set cr3.
//static inline void __local_x86_set_cr3 (unsigned long value);
static inline void __local_x86_set_cr3 (unsigned long value)
{
    asm ( "mov %0, %%cr3" : : "r" (value) );
}



/*
 *********************************
 * x86mainStartFirstThread:
 *      # internal.
 *
 * It selects the first thread to run and jumps to ring3. 
 */

void x86mainStartFirstThread (void){

    struct thread_d  *Thread;
    int i=0;


    debug_print("x86mainStartFirstThread:\n");


    // The first thread to run will the control thread 
    // of the init process. It is called InitThread.

    Thread = InitThread; 


    if ( (void *) Thread == NULL ){
        panic("x86mainStartFirstThread: Thread\n");
    }

    if ( Thread->used != TRUE || Thread->magic != 1234 )
    {
        printf ("x86mainStartFirstThread: tid={%d} magic \n", 
            Thread->tid);
         die();
    }

    // It its context is already saved, so this is not the fist time.
    
    if ( Thread->saved != FALSE ){
        panic("x86mainStartFirstThread: saved\n");
    }

    if ( Thread->tid < 0 ){
        panic("x86mainStartFirstThread: tid\n");
    }

    // Set the current thread.
    set_current( Thread->tid ); 

    // ...

    // State
    // The thread needs to be in Standby state.

    if ( Thread->state != STANDBY )
    {
        printf ("x86mainStartFirstThread: state tid={%d}\n", 
            Thread->tid);
        die();
    }

    // * MOVEMENT 2 ( Standby --> Running)
    if ( Thread->state == STANDBY )
    {
        Thread->state = RUNNING;
        
        queue_insert_data( 
            queue, 
            (unsigned long) Thread, 
            QUEUE_RUNNING );
    }

    // Current process.

    current_process = Thread->process->pid;

    // list.
    
    for ( i=0; i < PRIORITY_MAX; i++ )
    {
        dispatcherReadyList[i] = (unsigned long) Thread;
    };

    IncrementDispatcherCount (SELECT_IDLE_COUNT);


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

	//nesse momento usaremos o mapeamento do processo alvo ..
	//no mapeamento do processo alvo tambem tem o kernel
	//entao nao há problemas.

    // Set cr3 and flush TLB.
    // isso não é necessário se chamarmos spawn ela faz isso.
    __local_x86_set_cr3 ( (unsigned long) Thread->DirectoryPA );
    
    // flush tlb
    asm ("movl %cr3, %eax");
    //#todo: delay.
    asm ("movl %eax, %cr3");  


    // See: x86/headlib.asm
    x86_clear_nt_flag ();   

	//vamos iniciar antes para que
	//possamos usar a current_tss quando criarmos as threads
	//x86_init_gdt ();


    // ??
    asm ("clts \n");


    //#debug.
	//if ( (void *) Thread != NULL )
	//{
	//    mostra_slot ( (int) Thread->tid );
	//    mostra_reg  ( (int) Thread->tid );
	//    refresh_screen ();
	//}    


	// #importante
	// Mudamos para a última fase da inicialização.
	// Com isso alguns recursos somente para as fases anteriores
	// deverão ficar indisponíveis.

    KeInitPhase = 4;

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

    // Image buffer
    unsigned char *buff1 = (unsigned char *) 0x00400000;


    // init.bin (ELF)


    if ( buff1[0] != 0x7F ||
         buff1[1] != 'E' || buff1[2] != 'L' || buff1[3] != 'F' )
    {
        panic ("x86mainStartFirstThread: init .ELF signature");
    }


    // #debug
    debug_print("[x86] Go to user mode!  IRET\n");
    printf     ("[x86] Go to user mode!  IRET\n");
    refresh_screen ();


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
    // ss, esp, eflags, cs, eip;

    asm volatile ( 
        " movl $0x003FFFF0, %esp \n"
        " movl $0x23,       %ds:0x10(%esp)  \n"
        " movl $0x0044FFF0, %ds:0x0C(%esp)  \n"
        " movl $0x3000,     %ds:0x08(%esp)  \n"
        " movl $0x1B,       %ds:0x04(%esp)  \n"
        " movl $0x00401000, %ds:0x00(%esp)  \n"
        " movl $0x23, %eax  \n"
        " mov %ax, %ds      \n"
        " mov %ax, %es      \n"
        " mov %ax, %fs      \n"
        " mov %ax, %gs      \n"
        " iret              \n" );

    // Paranoia
    panic ("x86mainStartFirstThread: FAIL\n");
}


/*
 *********************************
 * __x86StartInit: 
 * 
 */
 
// Função local.
// Inicializa só o init.bin

void __x86StartInit (void){

    int fileret = -1;
 

    debug_print ("__x86StartInit:\n");


    //
    // INIT.BIN
    //

    // #importante
    // Carregado do diretório raiz
 
    unsigned long BUGBUG_IMAGE_SIZE_LIMIT = (512 * 4096);

	// loading image.
    
    // #bugbug
    // Loading from root dir. 512 entries limit.

    fileret = (unsigned long) fsLoadFile ( 
                                  VOLUME1_FAT_ADDRESS, 
                                  VOLUME1_ROOTDIR_ADDRESS, 
                                  FAT16_ROOT_ENTRIES,    //#bugbug: number of entries.
                                  "INIT    BIN", 
                                  (unsigned long) 0x00400000,
                                  BUGBUG_IMAGE_SIZE_LIMIT );

    // Coldn't load init.bin
    if ( fileret != 0 ){
        panic ("__x86StartInit: Coldn't load init.bin \n");
    }


	// Creating init process.
	
	// > Cria um diretório que é clone do diretório do kernel base 
	// Retornaremos o endereço virtual, para que a função create_process possa usar 
	// tanto o endereço virtual quanto o físico.
	
	// > UPROCESS_IMAGE_BASE;
	
	// #todo
	// temos que checar a validade do endereço do dir criado
	//antes de passarmos..

    InitProcess = (void *) create_process ( 
                               NULL, NULL, NULL, 
                               (unsigned long) 0x00400000, 
                               PRIORITY_HIGH, 
                               (int) KernelProcess->pid, 
                               "INIT-PROCESS", 
                               RING3, 
                               (unsigned long ) CloneKernelPageDirectory() );

    if ( (void *) InitProcess == NULL ){
        panic ("__x86StartInit: InitProcess\n");
    }else{

        InitProcess->position = SPECIAL_GUEST;
 
        fs_initialize_process_cwd ( InitProcess->pid, "/" );
    };


	//====================================================
	// Create

    // #
    // Criamos um thread em ring3.
    // O valor de eflags é 0x3200.

    InitThread = (void *) create_CreateRing3InitThread();

    if ( (void *) InitThread == NULL ){
        panic ("__x86StartInit: InitThread\n");
    }else{

        InitThread->position = SPECIAL_GUEST;

        //IdleThread->ownerPID = (int) InitProcess->pid;

        InitThread->tss = current_tss;
        
        
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


    InitProcess->Heap = (unsigned long) g_extraheap1_va;


    // #importante
    // A thread de controle do processo init2.bin.
    InitProcess->control = InitThread;

	//registra um dos servidores do gramado core.
	//server_index, process, thread

    ipccore_register ( (int) 0, 
        (struct process_d *) InitProcess, 
        (struct thread_d *) InitThread );   
}



//
// MAIN
//


/*
 *************************************************
 * x86main: 
 *
 * Function history:
 *     2015 - Created by Fred Nora.
 */

// Called by main.c

int x86main (void)
{
    int Status=0;


    if (current_arch != CURRENT_ARCH_X86)
    {
        debug_print ("[x86] x86main: current_arch fail\n");
        panic       ("[x86] x86main: current_arch fail\n"); 
    }


    debug_print ("==============\n");
    debug_print ("[x86] x86main:\n");

    // x86 global thing.
    // Threads counter.
    UPProcessorBlock.threads_counter = 0;


    PROGRESS("Kernel:1:1\n"); 
    // sse support.

    x86_sse_init();



//
// =================================================================
//

    //
    // == phase 0 ========================================
    //

    // Essa eh uma boa rotina pra inicializar o contador de fases.
    // Set Kernel phase.  
    // Status Flag.
    // edition flag.
    
    KeInitPhase = 0;

    gSystemStatus = 1;
    
    // ?? #todo: this is not a x86 thing.
    gSystemEdition = 0;

    //
    // hypervisor
    //

    // ?? #todo: this is not a x86 thing.

    g_is_qemu = FALSE;


    debug_print ("====\n");
    debug_print ("x86main:\n");
    printf      ("x86main:\n");

//
// ====================================================================
//

    debug_print ("====\n");
    debug_print ("==== x86main:\n");
    printf("x86main:\n");

	// Antes de tudo: 
	// CLI, Video, runtime.

	// ## BUGBUG ##
	// As mensagens do abort podem não funcionarem nesse caso.
	// AINDA NÃO INICIALIZAMOS O RECURSO DE MENSAGENS.


    if ( KeInitPhase != 0 )
    {
        KiAbort();
    }


	// Obs: 
	// O video já foi inicializado em main.c.
	// Isso atualiza a estrutura de console do console atual.
    // #test: mudamos isso para o momento em que inicializamos os consoles.
        
	// BANNER !
    //Welcome message. (Poderia ser um banner.) 
        
    //set_up_cursor (0,1);


    PROGRESS("Kernel:1:2\n"); 
    // Calling 'init' kernel module. 

    // See: 
    // core/init.c

    Status = (int) init(); 
 
    if ( Status != 0 )
    {
        debug_print ("x86main: init fail\n");
        panic       ("x86main: init fail\n");
    }

    // ...

    //printf("*breakpoint\n");
    //refresh_screen();
    //while(1){}


// Done: 
//     Completas as 3 fases de inicialização do sistema.
//     @todo: Na verdade serão mais fases..
//           as fases estão em init().

    printf ("x86main: done\n");

//
//=======================================================================================================
//

	//#debug 
	//a primeira mensagem só aparece após a inicialização da runtime.
	//por isso não deu pra limpar a tela antes.


#ifdef BREAKPOINT_TARGET_AFTER_SYSTEM
    printf ("x86main: *breakpoint\n");
    refresh_screen(); 
    while (1){ asm ("hlt"); }
#endif


    printf("======================\n");
    printf("x86main: end of phase 2\n");


//
// == phase 3 ? ================================================
//
    
    KeInitPhase = 3; 


    PROGRESS("Kernel:1:3\n"); 
    // Initialize all the kernel graphics support.



    // Initialize all the kernel graphics support.
    // some extra things like virtual terminal and tty.
    // #todo: rever essa inicializaçao.
    // See: users/kgws.c

    KGWS_initialize();


    // debug
    //printf("~kgws\n");
    //refresh_screen();
    //while(1){}



    PROGRESS("Kernel:1:4\n"); 
    // Initialize window server manager.

    //ws.c
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

    debug_print ("x86main: done\n");
    debug_print ("====\n");
    
    //printf("*breakpoint\n");
    //refresh_screen();
    //while(1){}

//
//=======================================================================================================
//


    PROGRESS("Kernel:1:5\n"); 
    // Setup GDT again.
    // We already made this at kernel startup.


    // # Caution.
    // Lets create a TSS and setup a GDT.
    // This way we can use 'current_tss' when we create threads.
    // This function creates a TSS and sets up a GDT.
    // See: hal/arch/x86/x86.c

    debug_print ("[x86] x86main: Initializing GDT\n");
    printf      ("[x86] x86main: Initializing GDT\n");
        
    x86_init_gdt();
    
    // #todo
    // Depois de renovarmos a GDT precisamos
    // recarregar os registradores de segmento.

    //printf("*breakpoint\n");
    //refresh_screen();
    //while(1){}

    //
    // == Processes and threads ===================================
    //


    debug_print ("[x86] x86main: processes and threads\n");
    printf      ("[x86] x86main: processes and threads\n");


    PROGRESS("Kernel:1:6\n"); 
    // Creating kernel process.

    //=================================================
    // processes and threads initialization.
    // Creating processes and threads.
    // The processes are: Kernel, Idle, Shell, Taskman.
    // ps: The images are loaded in the memory.

    // Creating Kernel process. PID=0.

    // IN: 
    // Room, Desktop, Window
    // base address, priority, ppid, name, iopl, page directory address.
    // See: ps/action/process.c
    
    KernelProcess = (void *) create_process ( NULL, NULL, NULL, 
                                 (unsigned long) 0xC0000000, 
                                 PRIORITY_HIGH, 
                                 (int) 0, 
                                 "KERNEL-PROCESS", 
                                 RING0,   
                                 (unsigned long ) gKernelPageDirectoryAddress );

    if ( (void *) KernelProcess == NULL ){
        panic ("[x86] x86main: KernelProcess\n");
    }else{

        KernelProcess->position = KING;

        fs_initialize_process_cwd ( KernelProcess->pid, "/" ); 
        //...
    };


    PROGRESS("Kernel:1:7\n"); 
    // Creating a ring 0 thread for the kernel.

    // Criando thread em ring 0 (idle)
    // pertence ao processo kernel.
    
    
    // Cria uma thread em ring 0.
    // Ok. isso funcionou bem.

	// >>>>> Como essa thread pertence ao processo kernel, então mudaremos ela 
	// um pouco pra cima, onde criamos o processo kernel.
	// obs: Mesmo não sendo ela o primeiro TID.
	// See: core/ps/create.c

    // #bugbug
    // O problema é que se essa thread começa afuncionar
    // antes mesmo do processo init habilitar as interrupções,
    // então o sistema vai falhar.
    // #todo
    // Como essa thread funciona sendo apenas uma rotina sti/hlt,
    // podemos deixar ela como idle thread somente nos estágios 
    // iniciais, sendo substituida por outra quando fot possível.

    EarlyRING0IDLEThread = (void *) create_CreateEarlyRing0IdleThread();

    if ( (void *) EarlyRING0IDLEThread == NULL ){
        panic ("x86main: EarlyRING0IDLEThread\n");
    }else{

        // Idle thread
        // #todo
        // We can use a method in the scheduler for this.
        // Or in the dispatcher?

        ____IDLE = (struct thread_d *) EarlyRING0IDLEThread;


        EarlyRING0IDLEThread->position = KING;
        
        // #todo
        //processor->IdleThread  = (void *) EarlyRING0IDLEThread;    
        //____IDLE = (void *) EarlyRING0IDLEThread;  

        //EarlyRING0IDLEThread->ownerPID =  (int) KernelProcess->pid; 

        EarlyRING0IDLEThread->tss = current_tss;

        set_thread_priority ( 
            (struct thread_d *) EarlyRING0IDLEThread,
            PRIORITY_MIN );

		// #importante
		// Sinalizando que ainda não podemos usar as rotinas que dependam
		// de que o dead thread collector esteja funcionando.
		// Esse status só muda quando a thread rodar.

        dead_thread_collector_status = FALSE;

        // ...
    };

    // debug
    //printf("I\n");
    //refresh_screen();
    //while(1){}


    //============================================================

    PROGRESS("Kernel:1:8\n"); 
    // Cria e inicializa apenas o INIT.BIN

    __x86StartInit();

    // debug
    //printf("~I\n");
    //refresh_screen();
    //while(1){}


    //printf("*breakpoint\n");
    //refresh_screen();
    //while(1){}


    PROGRESS("Kernel:1:9\n"); 
    // Check some initialization flags.

#ifdef  ENTRY_DEBUG_CHECK_VALIDATIONS

    Status = (int) debug();

    if ( Status != 0 ){
        printf ("[x86] x86main: debug\n");
        KernelStatus = KERNEL_ABORTED;
        goto fail;
    }else{
        KernelStatus = KERNEL_INITIALIZED;
    };

#endif



	// ======== # TESTS # ========
	// begin - We can make some tests here.


    //Inicializando as variáveis do cursor piscante do terminal.
    //isso é um teste.
    timer_cursor_used   = 0;   //desabilitado.
    timer_cursor_status = 0;


    PROGRESS("Kernel:1:10\n"); 
    // Early ps/2 initialization.


	// Initializing ps/2 controller.

	//#DEBUG
	//printf ("testing ps2\n");
	//refresh_screen(); 

    debug_print ("[x86] x86main: ps2\n");    
    
    
    
    // #todo: 
    // Essa inicialização deve ser adiada.
    // deixando para o processo init fazer isso.
    // Chamaremos essa inicialização básica nesse momento.
    // A inicialização completa será chamada pelo processo init.
    // See: i8042.c

    //PS2_initialize();
    PS2_early_initialization();



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

    windowLoadGramadoIcons();


    //printf("*breakpoint\n");
    //refresh_screen();
    //while(1){}


    PROGRESS("Kernel:1:12\n"); 
    // font support.

    //
    // Fonts.
    //
    
    // #bugbug
    // Font is independent from the x86 archtechture.
    // We can do this in some other place. Maybe :)
 
    // See: config/config.h
    gfontSize = DEFAULT_FONT_SIZE;

    switch (gfontSize){

        //case FONT8X8:
            //gfontSize = FONT8X8;
            //gwsInstallFont ("NC2     FON");
            //gwsSetCurrentFontCharWidth(8);
            //gwsSetCurrentFontCharHeight(8);
            //break;


        case FONT8X8:
            //gfontSize = FONT8X8;
            gwsInstallFont ("LIN8X8  FON");
            gwsSetCurrentFontCharWidth(8);
            gwsSetCurrentFontCharHeight(8);
            break;


        // #bugbug: fullscreen scroll.
        case FONT8X16:
            //gfontSize = FONT8X16;
            gwsInstallFont ("LIN8X16 FON");      
            gwsSetCurrentFontCharWidth(8);
            gwsSetCurrentFontCharHeight(16);
            break;

        //...
        
        // 8x8
        default:
            gfontSize = FONT8X8;
            gwsInstallFont ("LIN8X8  FON");
            gwsSetCurrentFontCharWidth(8);
            gwsSetCurrentFontCharHeight(8);
            debug_print ("[x86] x86main: FIXME: Using default font.\n");            
            break;
    };



    PROGRESS("Kernel:1:13\n"); 
    // Testing some rectangle support.


    // Testando suporte a salvamento de retângulo ##

	//#debug
	//printf ("testando salvamento de retangulo\n");
	//refresh_screen();
	
	//isso funcionou ...
	initialize_saved_rect ();
	
	
    //#test
    //testando salvar um retângulo ...
	//save_rect ( 0, 0, 100, 100 );
	//copiando aqui no backbuffer
	//show_saved_rect ( 20, 20, 100, 100 );
	

	// #debug
	// printf("\n");
	// refresh_screen();
	// die();

//    ====================== ## TESTS ## =============================
// #end.




#ifdef BREAKPOINT_TARGET_AFTER_ENTRY
	//#debug 
	//a primeira mensagem só aparece após a inicialização da runtime.
	//por isso não deu pra limpar a tela antes.

    printf ("[x86] x86main: after entry");
    refresh_screen(); 
    while (1){ asm ("hlt"); }

#endif


	// done !
done:

    PROGRESS("Kernel:1:14\n"); 
    // Start first thread ever.

    debug_print ("[x86] x86main: done\n");
    debug_print ("==============\n");



    // debug
    //printf("T\n");
    //refresh_screen();
    //while(1){}


    //
    // Starting idle thread.
    //


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

        x86mainStartFirstThread(); 

        panic("x86mainStartFirstThread: Couldn't spawn the first thread!\n");
    }


    // ===============================

    // fail
	// #todo
	// Uma opção aqui é usarmos a tipagem void para essa função
	// e ao invés de retornarmos, apenas entrarmos na thread idle
	// em ring 0, isso depois de criadas as threads em user mode.

fail:
    
    PROGRESS("Kernel:1:00\n"); 
    
    debug_print ("[x86] x86main: fail\n");
    refresh_screen (); 
    return -1;
}


//
// End.
//


