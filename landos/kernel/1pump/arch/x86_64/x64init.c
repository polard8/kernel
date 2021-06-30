

#include <kernel.h>



// Função local.
// Inicializa só o init.bin

void __x64StartInit (void)
{
    //#todo
    debug_print ("__x64StartInit: [TODO]\n");
    panic ("__x64StartInit: [TODO]\n");
}

// local
void x64mainStartFirstThread (void)
{
    //#todo
    debug_print ("x64mainStartFirstThread: [TODO]\n");
    panic ("x64mainStartFirstThread: [TODO]\n");
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
    
    KeInitPhase = 0;

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

    if ( KeInitPhase != 0 ){
        x_panic ("x64main: KeInitPhase");
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
    KeInitPhase = 3;

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

    debug_print ("[x64] x64main: Initializing GDT\n");
    //printf      ("[x86] x86main: Initializing GDT\n");
        
    //x86_init_gdt();

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


//================================
    PROGRESS("Kernel:1:7\n"); 
    // Creating a ring 0 thread for the kernel.


//================================
    PROGRESS("Kernel:1:8\n"); 
    // Cria e inicializa apenas o INIT.BIN

    //__x86StartInit();

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

        x86mainStartFirstThread(); 

        panic("x86mainStartFirstThread: Couldn't spawn the first thread!\n");
    }
    */

    // #test
    // Estamos usando esse retorno at'e fazermos achamada logo acima.
    return 0;

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




















