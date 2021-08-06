
// init.c

#include <kernel.h>


extern unsigned long InitializationPhase;

//Onde ficam os códigos e arquivos de configuração usados na inicialização.
//A ideia é que se a inicialização precisar de algum arquivo, deve procurá-lo
//nos diretórios previamente combinados.
//melhor que sejam poucos e que sempre sejam os mesmos.

#define INIT_ROOT_PATH  "/"
#define INIT_BIN_PATH   "/BIN"
//...



void init_globals (void)
{
    int i=0;


//#ifdef EXECVE_VERBOSE
    debug_print("init_globals:\n");
    printf     ("init_globals:\n");
//#endif


    // stdio
    // Inicializa as estruturas do fluxo padrão.
    // Isso vai usar a file table.
    // #todo: Mudar para kstdioInitialize.

    stdioInitialize();

    // Screen
    // Now we can print strings in the screen.

    screenInit();

//
// == First message ====================================
//

    // #todo
    // Maybe we can print the banner.


    debug_print("init_globals: [printf] WE HAVE MESSAGES NOW!\n");
    //printf     ("init_globals: [printf] WE HAVE MESSAGES NOW!\n");


    // ===================
    // Vamos atrasar configuração de janela 
    // em favor de configuração de mensagem

    // ??
    // What is this?
    // Atalho para a próxima mensagem de teclado..(test) debug
    gNextKeyboardMessage = (int) 0;

    // Essa flag bloqueia e impede que uma janela obtenha o foco.
    gFocusBlocked = (int) 0;

//
// == Profiler =============================
//

// See: 
// include/kernel/profiler/pints.h

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

//
// == User ===========================================
//

	// As globais relativas à usuário são independentes do 
	// ambiente gráfico.

    // =========================================
    //User and group.
    current_user  = 0;
    current_group = 0;

    // =========================================
    // Security layers.
    // user session, room(window station), desktop.
    current_usersession = (int) 0;
    current_room        = (int) 0;
    current_desktop     = (int) 0;

//
// == ps ==============================================
//
    // =========================================
    // Process, Thread.
    // See: kernel.h
    
    foreground_process = (int) 0;
    foreground_thread  = (int) 0;
    current_process    = (int) 0;
    current_thread     = (int) 0;

//
// == Network ===================================
//
    // =========================================
    // Initialize the ports table used by the socket infrastruture.
    // todo: Create socket_init_gramado_ports();
    for (i=0; i<GRAMADO_PORT_MAX; i++)
    {
        gramado_ports[i] = 0;
    };


//
// == Kernel requests ===================================
//

    // The kernel request
    // See: request.c

    clear_request();

//
// == kgws ===========================================
//

    // =========================================
    //if ( g_useGUI != TRUE ){
    //    panic("init_globals: No GUI\n");
    //}

    // ===============================================
    // Window support.
 
    current_window    = (int) 0;  // Current Window.
    windows_count     = (int) 0;  // Window count.
    window_with_focus = (int) 0;  // Window with focus.
    current_menu      = (int) 0;  // Current Menu.
    // Continua ...

    // #todo

    // windows
    //init_windows();
        
    // #todo: Delete?
    //init_menus();

    // Continua...

    // ??
    // Messages.
    g_new_message = 0;

//
// == fs ==============================
//

    // ==============================
    // fs support

    // FS type.
    // type 1, fat16.
    
    // #todo
    g_currentvolume_filesystem_type = FS_TYPE_FAT16;    
    g_currentvolume_fatbits = (int) 16;


	//===================
	
	// #importante:
	// provavelmente isso altere o comportamento do cursor,
	// levando o cursor par ao início da tela. Então precisamos
	// repintar o background para recomeçarmos.
	
	//printf("#breakpoint glob");
    //refresh_screen(); 
    //while(1){}	
	
	//#bugbug isso esta dando problemas.
//#ifdef EXECVE_VERBOSE
    // backgroundDraw ( (unsigned long) COLOR_BLUE ); 
//#endif

    //printf("#breakpoint glob");
    //refresh_screen(); 
    //while(1){}

//
// Keyboard support
//
    ldisc_init_modifier_keys();
    ldisc_init_lock_keys();

    // Continua ...
}



// Phases 1 and 2.
// Called in the initialization phase 0.
// Called by x64main in x64init.c

int I_init (void)
{
    int Status = 0;
    unsigned char ProcessorType=0;


    debug_print ("I_init:\n");
    printf      ("I_init:\n");

// ==================
// Check kernel phase.

    if ( InitializationPhase != 0 ){
        debug_print ("I_init: InitializationPhase fail\n");
        x_panic     ("I_init: InitializationPhase fail\n");
    }

// ===============================
// Globals

    PROGRESS("Kernel:2:1\n"); 
    debug_print ("I_init: Globals\n");
    init_globals();


// ===============================
// Create the progress bar.
// No bar for now.
// #importante
// À partir daqui podemos exibir strings na tela.

    PROGRESS("Kernel:2:2\n"); 

// ===============================
// io manager
// #bugbug:
// Depois de iniciar as globais, provavelmente o cursor mude 
// para o início da tela.
// então após iniciarmos as globais temos que repintar o background e 
// fazer um refresh da tela se a flag de verbose estiver ligada.

    PROGRESS("Kernel:2:3\n"); 
    debug_print ("I_init: Object manager\n");
    //init_object_manager ();
    debug_print ("I_init: io manager\n");
    //ioInit ();

// ===============================
// device manager.
// Inicializa o gerenciamento de dispositivos.
// Inicializa a lista de dispositivos.

    PROGRESS("Kernel:2:4\n"); 
    debug_print ("I_init: device manager\n");
    init_device_manager();

// ===============================
// Storage manager
// Ordem: storage, disk, volume, file system.
// #importante 
// A estrutura 'storage' vai ser o nível mais baixo.
// É nela que as outras partes devem se basear.

    PROGRESS("Kernel:2:5\n"); 
    debug_print ("I_init: storage structure\n");
    storage = (void *) kmalloc ( sizeof(struct storage_d) );
    if ( (void *) storage == NULL ){
       panic ("I_init: storage\n");
    }
    debug_print ("I_init: disk [TODO]\n");
    disk_init();
    debug_print ("I_init: volume [TODO]\n");
    volume_init();
    debug_print ("I_init: vfs [TODO]\n");
    //vfsInit();
    debug_print ("I_init: fs [TODO]\n");
    fsInit();
    // ...
 
// ==========================
// network
// Maybe we have a new plain for that in the 64bit version of Gramado.
// See: network.c

    PROGRESS("Kernel:2:6\n"); 
    debug_print ("I_init: network [FIXME]\n");
    //networkInit();

// ==========================
// Initialize Platform structure.
// #todo

    PROGRESS("Kernel:2:7\n"); 
    debug_print ("I_init: Platform struct\n");

//++
// ====================================================================
    /*
    Platform = (void *) kmalloc ( sizeof(struct platform_d) );

    if ( (void *) Platform ==  NULL ){
        panic ("core-init: Platform\n");
    }else{

        // UP or MP.
        Platform->system_type = SYSTEM_TYPE_NULL;

        // Hardware
        Hardware = (void *) kmalloc ( sizeof(struct hardware_d) );

        if ( (void *) Hardware ==  NULL ){
            panic ("core-init: Hardware\n");
        }else{
            Platform->Hardware = (void *) Hardware;
            //printf(".");
        };

		//Firmware
        Firmware = (void *) kmalloc ( sizeof(struct firmware_d) );

        if ((void *) Firmware ==  NULL ){
            panic ("core-init: Firmware\n");
        }else{
            Platform->Firmware = (void *) Firmware;
            //printf("."); 
        };


		//System (software)

		// #IMPORTATE: 
		// Aqui estamos inicializando a estrutura do systema.

        System = (void *) kmalloc ( sizeof(struct system_d) );

        if ( (void *) System ==  NULL ){
            panic ("core-init: System\n");
        }else{
            System->used  = TRUE;  // Sinaliza que a estrutura esta em uso.
            System->magic = 1234;  // Sinaliza que a estrutura não esta corrompida.
            
            Platform->System = (void *) System;
            //printf(".");
        };

		//printf(" Done!\n");	
		//...
    };
    */
// ====================================================================
//--


    // ...


//
// ====================================================================
//


// ===============================
// #important
// We need to be in the phase 0.

    if (InitializationPhase != 0){
        x_panic ("I_init: InitializationPhase\n");
    }


// ==========================
// hal

    PROGRESS("Kernel:2:8\n"); 
    debug_print ("I_init: hal\n");
    Status = init_hal();
    if (Status != 0){
        x_panic ("I_init: init_hal fail\n");
    }

// ==========================
// microkernel components:
// mm, ipc, ps ...

    PROGRESS("Kernel:2:9\n"); 
    Status = init_microkernel();
    if (Status != 0){
        panic ("core-init: init_microkernel fail\n");
    }

// =========================================
// Executive components

    PROGRESS("Kernel:2:10\n"); 
    Status = init_executive();
    if (Status != 0){
        panic ("I_init: init_executive fail\n"); 
    }

// =========================================
// Some gui components.
// #todo: rever 

    PROGRESS("Kernel:2:11\n"); 
    Status = init_gramado();
    if (Status != 0){
        panic ("I_init: init_gramado fail\n"); 
    }

// =========================================
// In-kernel window manager.
// #todo: maybe

    PROGRESS("Kernel:2:12\n"); 
    //init_window_manager();


// End of phase.
// Starting phase 1.

    InitializationPhase = 1;



// ========================
// We need to be in the phase 1.

    if ( InitializationPhase != 1 ){
        x_panic ("I_init: InitializationPhase\n");
    }

// =========================================
// 'processor' structure.
// The 'processor' structure.
// ?? Is it 'up' or 'smp' ?

    PROGRESS("Kernel:2:13\n"); 
    processor = (void *) kmalloc ( sizeof( struct processor_d ) ); 
    if ( (void *) processor == NULL ){
        x_panic("I_init: processor\n");
    }


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
    // 1pump/arch/x86/x86.c
    // 1pump/arch/amd/cpuamd.c

    ProcessorType = (int) hal_probe_processor_type();

    // Error
    // Vamos suspender isso por enquanto ...
    // precisamos apurar essa rotina de identificação da cpu.

    //if (ProcessorType <= 0){
    //    x_panic("init: [ERROR] ProcessorType\n");
    //}

    processor->Type = (int) ProcessorType;
    
    switch (ProcessorType){
    case Processor_INTEL:  
    case Processor_AMD:
        x64_init_intel();   
        //init_amd(); 
        break;
    // ...
    default:
        x_panic ("I_init: [ERROR] default Type");
        break;
    };


//
// qemu
//
    // Check if we are running on qemu.
    // and set flag.

    int isQEMU=FALSE;
    isQEMU = detect_IsQEMU();
    if( isQEMU == TRUE ){
        debug_print("I_init: Running on QEMU\n");
        //printf ("Running on QEMU\n");
    }


// =========================================
// process manager.
// #obs: O contexto é depedente.
// Inicializando o Process manager.

    PROGRESS("Kernel:2:14\n"); 
    // init_process_manager();

// =========================================
// Load rootdir.

    PROGRESS("Kernel:2:15\n"); 

    // #todo: 
    // We can move this above to the 'storage' section.

    // #importante
    // Só podemos carregar o diretório raiz depois que 
    // inicializamos o controlador de IDE e as estruturas de 
    // sistema de arquivos.
    // #todo: Precisamos inicializar a estrutura de diretorio
    // usada pelo diretorio raiz, para colocarmos o ponteiro
    // na estrutura de processos, juntamente com o ponteiro
    // para o cwd. 
    // Talvez essa seja a hora de criarmos a estrutura para
    // o diretorio raiz, mas ainda nao temos estrutura de processo.

    debug_print ("I_init: load rootdir.\n");
	// Carregando o diretório raiz.
    //fs_load_rootdir( VOLUME1_ROOTDIR_ADDRESS, VOLUME1_ROOTDIR_LBA, 32 );


    // Disable interrupts, lock task switch and scheduler.

    // # isso ja foi feito no começo da rotina de inicialização do kernel.
    // Tem que pensar nisso antes de tudo.

    //asm ("cli");
    //set_task_status(LOCKED); 
    //scheduler_lock();


// End of phase.
// Starting phase 2.

    InitializationPhase = 2;

// =========================================
// keyboard stuff.
// Nothing for now.

    PROGRESS("Kernel:2:16\n"); 
    debug_print ("I_init: done\n");
    //printf      ("I_init: done\n");

    // ok
    // Return to the main initialization routine
    // in x64init.c

    return 0;

// ====================
// fail
// Return to the main initialization routine
// in x64init.c

//fail1:
    // If we already have printf verbose.
fail0:
    debug_print ("I_init: fail\n");
    return (-1);
}



























