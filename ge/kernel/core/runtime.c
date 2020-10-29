/*
 * File: runtime.c
 *
 * Descrição:
 *     Arquivo principal do módulo '/rt' do kernel base.
 *     Interfaces para rotinas de runtime do kernel.
 *
 * Objetivo:
 *    Fazer a inicialização do mecanismo de alocação dinâmica, incluindo 
 * configurações de heaps, stacks, mmblocks ... 
 *
 * History:
 *    2015 - Created by Fred Nora.
 *    2016 - Some basic functions.
 *    ...
 */


#include <kernel.h>



/*
 *********************************
 * init_runtime:
 *     Initializing run time. 
 *     Kernel heap and stack stuffs.
 *     @todo: Mudar para runtimeInit().
 */

int init_runtime (void){

    int Status = 0;


    debug_print ("init_runtime:\n");
    debug_print ("[Kernel] init_runtime: Initializing runtime ...\n");


    //
    // Current arch.
    //

    switch (current_arch)
    {

        // Init Memory Manager for x86:
        // Heap, Stack, Pages, mmblocks, memory sizes, memory zones ...
        // See: mm/86/memory.c
 
        case CURRENT_ARCH_X86:
        
            debug_print ("[x86] init_runtime: Initializing mm ...\n");
            mmInit();
            
            debug_print ("[x86] init_runtime: Initializing paging ...\n");
            mmSetUpPaging();
            
            //...
            break;


        case CURRENT_ARCH_X86_64:
            debug_print ("[x86_64] init_runtime: [NOT SUPPORTED] CURRENT_ARCH_X86_64\n");
            printf      ("[x86_64] init_runtime: [NOT SUPPORTED] CURRENT_ARCH_X86_64\n");
            goto fail;
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
	
#ifdef BREAKPOINT_TARGET_AFTER_RUNTIME
    //#debug 
	//a primeira mensagem só aparece após a inicialização da runtime.
	//por isso não deu pra limpar a tela antes.
	printf (">>>debug hang init_runtime: after runtime initialization");
	refresh_screen(); 
	while (1){ asm ("hlt"); };
#endif


    //
    // == Done ===========================================
    //

    g_module_runtime_initialized = 1;

    return 0; 

fail:
    debug_print ("[Kernel] init_runtime: Runtime fail\n");
    refresh_screen();
    return -1;
}



// DEPRECATED!
int KiInitRuntime (void)
{
    debug_print ("KiInitRuntime: [DEPRECATED] \n");
    return (int) -1;
}



//
// End.
//
