



#include <kernel.h>

/*
 *********************************
 * init_runtime:
 *     Initializing run time. 
 *     Kernel heap and stack stuffs.
 *     @todo: Mudar para runtimeInit().
 */

int init_runtime (void)
{
    int Status = 0;


    debug_print ("init_runtime:\n");
    debug_print ("[Kernel] init_runtime: Initializing runtime ...\n");


    //
    // Current arch.
    //
    
    // #hack hack
    
    current_arch = CURRENT_ARCH_X86_64;

    switch (current_arch){

        // Init Memory Manager for x86:
        // Heap, Stack, Pages, mmblocks, memory sizes, memory zones ...
        // See: 
        // mm/memory.c
        // mm/pages.c
 

        case CURRENT_ARCH_X86_64:
            debug_print ("[x86_64] init_runtime: [TODO] CURRENT_ARCH_X86_64\n");
            //printf      ("[x86_64] init_runtime: [NOT SUPPORTED] CURRENT_ARCH_X86_64\n");
            //goto fail;
            
            //#todo
            //See: memory.c
            debug_print ("[x86_64] init_runtime: [TODO] Initializing mm ...\n");
            mmInit();
            
            //See: pages.c
            debug_print ("[x86_64] init_runtime: [DANGER] Initializing paging ...\n");
            mmSetUpPaging();
            
            return TRUE;
            break;

        // armmain (); ??

        // ...

        default:
            debug_print ("[Kernel] init_runtime: Current arch not defined!\n *hang");
            goto fail;
            break; 
    };

 
    // obs:
    // Now we have malloc, free and messages support.
    // The video support is using the boot loader configuration yet.



	// #### importante ####
	// provavelmente aqui é o primeiro lugar onde as mensagens funcionam.
	
	//#bugbug
	//mas temos um problema no Y.

	//#bugbug
//#ifdef EXECVE_VERBOSE
	//backgroundDraw ( (unsigned long) COLOR_BLUE ); 
//#endif


	//#todo:
	//podemos analisar o status aqui.

//#ifdef BREAKPOINT_TARGET_AFTER_RUNTIME
    //#debug 
	//a primeira mensagem só aparece após a inicialização da runtime.
	//por isso não deu pra limpar a tela antes.
	//printf (">>>debug hang init_runtime: after runtime initialization");
	//refresh_screen(); 
	//while (1){ asm ("hlt"); };
//#endif


    debug_print ("init_runtime: done\n");
    //refresh_screen();
    return 0; 

fail:
    debug_print ("[Kernel] init_runtime: Runtime fail\n");
    refresh_screen();
    return (-1);
}



// called by main.c
int Runtime_initialize(void)
{
    int Status=0;


    g_module_runtime_initialized = FALSE;
    
    debug_print ("Runtime_initialize:\n");
    
    Status = (int) init_runtime();

    if ( Status < 0 )
    {
        debug_print ("Runtime_initialize: Runtime fail. *hang\n");
        // No message support at the moment ?!
        asm ("cli \n");
        while (1){  asm ("hlt \n");  };
    }

    // ...

    debug_print ("Runtime_initialize: done\n");
    
    g_module_runtime_initialized = TRUE;
    
    return 0;
}




