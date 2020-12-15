/*
 * File: init/x86/x86init.c 
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

    struct thread_d *Thread;
    int i=0;


    // Select the idle thread.

    Thread = InitThread; 
    

    if ( (void *) Thread == NULL ){
        panic ("x86mainStartFirstThread: Thread\n");

    } else {

        if ( Thread->saved != 0 ){
            panic ("x86mainStartFirstThread: saved\n");
        }


        if ( Thread->used != 1 || Thread->magic != 1234){
            printf ("x86mainStartFirstThread: tid={%d} magic \n", 
                Thread->tid);
            die();
        }

        set_current ( Thread->tid );       
        // ...
    };

    // State  
    if ( Thread->state != STANDBY ){
        printf ("x86mainStartFirstThread: state tid={%d}\n", 
            Thread->tid);
        die();
    }

    // * MOVEMENT 2 ( Standby --> Running)
    if ( Thread->state == STANDBY )
    {
        Thread->state = RUNNING;
        queue_insert_data ( queue, (unsigned long) Thread, QUEUE_RUNNING);
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

    turn_task_switch_on ();


    // timerInit8253 ( HZ );
    // timerInit8253 ( 800 );
    // timerInit8253 ( 900 );

	//nesse momento usaremos o mapeamento do processo alvo ..
	//no mapeamento do processo alvo tambem tem o kernel
	//entao nao há problemas.

    // Set cr3 and flush TLB.
    // isso não é necessário se chamarmos spawn ela faz isso.
    __local_x86_set_cr3 ( (unsigned long) Thread->DirectoryPA );
    
    // flush
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

    unsigned char *buff1 = (unsigned char *) 0x00400000;


    // init.bin (ELF)


    if ( buff1[0] != 0x7F ||
         buff1[1] != 'E' || buff1[2] != 'L' || buff1[3] != 'F' )
    {
        panic ("x86mainStartFirstThread: init .ELF signature");
    }


    // #debug
    printf ("[x86] Go to user mode!  IRET\n");
    refresh_screen ();


    // Fly!
    // We need to have the same stack in the TSS.
    // ss, esp, eflags, cs, eip;

    asm volatile ( " movl $0x003FFFF0, %esp \n"
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
    panic ("x86mainStartFirstThread: FAIL");
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
    
    
    unsigned long BUGBUG_IMAGE_SIZE_LIMIT = (512 * 4096);

	// loading image.
    
    fileret = (unsigned long) fsLoadFile ( VOLUME1_FAT_ADDRESS, 
                                  VOLUME1_ROOTDIR_ADDRESS, 
                                  32, //#bugbug: Number of entries.
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

    InitProcess = (void *) create_process ( NULL, NULL, NULL, 
                               (unsigned long) 0x00400000, 
                               PRIORITY_HIGH, 
                               (int) KernelProcess->pid, 
                               "INIT-PROCESS", 
                               RING3, 
                               (unsigned long ) CloneKernelPageDirectory() );

    if ( (void *) InitProcess == NULL ){
        panic ("__x86StartInit: InitProcess\n");

    }else{
        fs_initialize_process_pwd ( InitProcess->pid, "no-pwd" );
    };



	//====================================================
	//Create Idle Thread. tid=0. ppid=0.
	
    InitThread = (void *) createCreateInitThread ();

    if ( (void *) InitThread == NULL ){
        panic ("__x86StartInit: IdleThread\n");

    }else{

        //IdleThread->ownerPID = (int) InitProcess->pid;

        InitThread->tss = current_tss;
        
        
        // [Processing time]
        current_process = InitProcess->pid;
        current_thread = InitThread->tid;
        
        // [Focus]
        active_process = current_process;
        active_thread = current_thread;
        
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


    if (current_arch != CURRENT_ARCH_X86){
        debug_print ("[x86] x86main: Arch fail\n");
        panic       ("[x86] x86main: Arch fail\n"); 
    }

    debug_print ("==============\n");
    debug_print ("[x86] x86main:\n");


    // SSE
    x86_sse_init ();

    // Threads counter.
    UPProcessorBlock.threads_counter = 0;







//
//=======================================================================================================
//

    // # system
    // #bugbug
    // Daqui pra frente tem coisa que é dependente da arquitetura x86 e 
    // coisa que não é ... 
    // precisamos que aqui tudo seja dependente da arquitetura x86.
    // As outras coisas podem ser chamadas em main.
    // Talvez possamos mandar coisas que não são dependentes 
    // para main.c


    // System initialization.
    // See: core/system.c

    printf ("[x86] x86main: Calling systemInit\n");

    //Status = (int) systemInit();

    //if ( Status != 0 )
    //{
    //    KernelStatus = KERNEL_ABORTED;
        
    //    debug_print ("[x86] x86main: systemInit fail\n");
    //    printf      ("[x86] x86main: systemInit fail\n");
    //    goto fail;
    //}





    //
    // == phase 0 ========================================
    //

    // Essa eh uma boa rotina pra inicializar o contador de fases.
    // Set Kernel phase.  
    // Status Flag.
    // edition flag.
    
    KeInitPhase = 0;
    gSystemStatus = 1;
    gSystemEdition = 0;

    debug_print ("====\n");
    debug_print ("systemInit:\n");
    printf      ("systemInit:\n");

//
//=======================================================================================================
//

    debug_print ("====\n");
    debug_print ("==== systemStartUp:\n");
    printf("systemStartUp:\n");

	// Antes de tudo: 
	// CLI, Video, runtime.

	// ## BUGBUG ##
	// As mensagens do abort podem não funcionarem nesse caso.
	// AINDA NÃO INICIALIZAMOS O RECURSO DE MENSAGENS.
	
    if ( KeInitPhase != 0 )
    {
        KiAbort();
    
    }else{
        
        // Disable interrupts, lock taskswitch and scheduler.
        //Set scheduler type. (Round Robin).
        // #todo: call a hal routine for cli.

        asm ("cli");  
        taskswitch_lock();
        scheduler_lock();
        
       
         Scheduler.policy = SCHEDULER_RR;
         Dispatcher.policy = DISPATCHER_CURRENT;

		// Obs: 
		// O video já foi inicializado em main.c.
		// Isso atualiza a estrutura de console do console atual.
        // #test: mudamos isso para o momento em que inicializamos os consoles.
        
		// BANNER !
        //Welcome message. (Poderia ser um banner.) 
        
        //set_up_cursor (0,1);


        //
        // == INIT ! ===========================================
        //  

        // See: 
        // core/init.c

        Status = (int) init(); 
        
        if ( Status != 0 )
        {
            debug_print ("systemStartUp: init fail\n");
            panic       ("systemStartUp: init fail\n");
        }
        //...

    }; //--else

    //printf("*breakpoint\n");
    //refresh_screen();
    //while(1){}


// Done: 
//     Completas as 3 fases de inicialização do sistema.
//     @todo: Na verdade serão mais fases..
//           as fases estão em init().

    printf ("systemStartUp: done\n");

//
//=======================================================================================================
//

	//#debug 
	//a primeira mensagem só aparece após a inicialização da runtime.
	//por isso não deu pra limpar a tela antes.


#ifdef BREAKPOINT_TARGET_AFTER_SYSTEM
    printf ("systemInit: *breakpoint\n");
    refresh_screen(); 
    while (1){ asm ("hlt"); }
#endif


    printf("=========================\n");
    printf("core-init: end of phase 2\n");

    // 3 - fim da fase 2.
    IncrementProgressBar();
    
    //refresh_screen();
    //while(1){}

//
// == phase 3 ? ================================================
//
    
    KeInitPhase = 3; 
    
    // Initialize all the kernel graphics support.
    // some extra things like virtual terminal and tty.
    // #todo: rever essa inicializaçao.
    // See; windows/model/kgws.c
    KGWS_initialize();
    
    //ws.c
    ws_init();

    // #debug:  
    // Esperamos alcaçarmos esse alvo.
    // Isso funcionou gigabyte/intel
    // Vamos avançar
    // Quem chamou essa funçao foi o começo da inicializaçao do kernel.
    // Retornamos para x86main.c para arch x86.

    debug_print ("systemInit: done\n");
    debug_print ("====\n");
    
    //printf("*breakpoint\n");
    //refresh_screen();
    //while(1){}

//
//=======================================================================================================
//

    //
    //=======================================================
    //

	//
	// # GDT
	//

    // # Caution.
    // Lets create a TSS and setup a GDT.
    // This way we can use 'current_tss' when we create threads.
    // This function creates a TSS and sets up a GDT.
    // See: hal/arch/x86/x86.c

    debug_print ("[x86] x86main: Initializing GDT\n");
    printf      ("[x86] x86main: Initializing GDT\n");
        
    x86_init_gdt();

    //printf("*breakpoint\n");
    //refresh_screen();
    //while(1){}

    //
    // == Processes and threads ===================================
    //


    debug_print ("[x86] x86main: processes and threads\n");
    printf      ("[x86] x86main: processes and threads\n");

	//
	// # Processes
	//

    //=================================================
    // processes and threads initialization.
    // Creating processes and threads.
    // The processes are: Kernel, Idle, Shell, Taskman.
    // ps: The images are loaded in the memory.


//createProcesses:

	// #debug
    // printf ("creating kernel process ...\n");

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
        fs_initialize_process_pwd ( KernelProcess->pid, "no-directory" ); 
        //...
    };
    
    
    // Criando thread em ring 0 (idle)
    // pertence ao processo kernel.
    
    
//#ifdef ENTRY_CREATE_KERNELTHREAD_RING0
    //===================================
    // Cria uma thread em ring 0.
    // Ok. isso funcionou bem.

	// >>>>> Como essa thread pertence ao processo kernel, então mudaremos ela 
	// um pouco pra cima, onde criamos o processo kernel.
	// obs: Mesmo não sendo ela o primeiro TID.
	// See: threadi.c

    RING0IDLEThread = (void *) KiCreateRing0Idle ();

    if ( (void *) RING0IDLEThread == NULL ){
        panic ("x86main: RING0IDLEThread\n");

    }else{

        // #todo
        //processor->IdleThread  = (void *) RING0IDLEThread;    
        //____IDLE = (void *) RING0IDLEThread;  

        //RING0IDLEThread->ownerPID =  (int) KernelProcess->pid; 

        RING0IDLEThread->tss = current_tss;
		
		// priority and quantum.
	    //set_thread_priority ( (struct thread_d *) RING0IDLEThread,
	        //PRIORITY_HIGH4 );

	    //set_thread_priority ( (struct thread_d *) RING0IDLEThread,
	        //PRIORITY_LOW1 );


	    //set_thread_priority ( (struct thread_d *) RING0IDLEThread,
	        //PRIORITY_LOW3 );

        // funcionou no mínimo.
        // com multiplicador 3. quantum = (1*3=3)
        set_thread_priority ( (struct thread_d *) RING0IDLEThread,
            PRIORITY_MIN );

        //set_thread_priority ( (struct thread_d *) RING0IDLEThread,
            //PRIORITY_NORMAL );

		// #importante
		// Sinalizando que ainda não podemos usar as rotinas que dependam
		// de que o dead thread collector esteja funcionando.
		// Esse status só muda quando a thread rodar.

		dead_thread_collector_status = 0;
		//...
    };
//#endif



	// Cria e inicializa apenas o INIT.BIN
    __x86StartInit ();


    //printf("*breakpoint\n");
    //refresh_screen();
    //while(1){}


	//
	//===============================================
	//


	//...


//Kernel base Debugger.
//doDebug:

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
    timer_cursor_used = 0;   //desabilitado.
    timer_cursor_status = 0;




	//
	// ========= ## ps2 ## =============
	//

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




	//
	// Loading file tests.
	//

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



	//
	// ## testando suporte a salvamento de retângulo ##
	//
	
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
    debug_print ("[x86] x86main: done\n");
    debug_print ("==============\n");

    // Return to assembly file, (head.s).
    if ( KernelStatus == KERNEL_INITIALIZED )
    {
        //
        // Starting idle thread.
        //

        printf("[x86] x86main: Initializing INIT ..\n");
        
#ifdef KERNEL_VERBOSE
    refresh_screen();
#endif

        x86mainStartFirstThread(); 

        printf ("[x86] x86main: No idle thread selected\n");
        goto fail;
    }

    // ok
    return 0;

    // fail
	// #todo
	// Uma opção aqui é usarmos a tipagem void para essa função
	// e ao invés de retornarmos, apenas entrarmos na thread idle
	// em ring 0, isso depois de criadas as threads em user mode.

fail:
    debug_print ("[x86] x86main: fail\n");
    refresh_screen (); 
    return -1;
}


//
// End.
//


