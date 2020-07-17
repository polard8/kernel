/*
 * File: rt/runtime.c
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


//Variáveis internas.
//int runtimeStatus;
//...


/*
 *********************************
 * init_runtime:
 *     Initializing run time. 
 *     Kernel heap and stack stuffs.
 *     @todo: Mudar para runtimeInit().
 */

int init_runtime (void){


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
            init_mm ();
            
            debug_print ("[x86] init_runtime: Initializing paging ...\n");
            SetUpPaging ();
            
            //...
            break;


        case CURRENT_ARCH_X86_64:
            debug_print ("[x86_64] init_runtime: Initializing mm ...\n");
            debug_print ("[x86_64] init_runtime: Current arch not supported !\n *hang");
            return -1;
            break;

        // armmain (); ??

        // ...

        default:
            debug_print ("[Kernel] kernel_main: Current arch not defined!\n *hang");
            return -1;
            break; 
    };

 
    // obs:
    // Now we have malloc, free and messages support.
    // The video support is using the boot loader configuration yet.


    //
    // Done!
    //

    return 0; 
}


/*
 ********************************
 * KiInitRuntime: 
 *     Init runtime.
 *     +Clear bss segment.
 *     +Init heap, malloc.
 *     +...
 *     @todo: 
 *         Criar aqui, apenas a interface que chama a rotina 
 *         de inicialização da runtime.
 */

int KiInitRuntime (void){

    int Status = 0;

    debug_print ("KiInitRuntime:\n");


	//#todo 
	//preparar a tela para as mensagens;
	//mas somente se a flag de debug estiver acionada.

    Status = (int) init_runtime ();

    if (Status<0)
        debug_print ("KiInitRuntime: init_runtime fail.\n");


	// #### importante ####
	// provavelmente aqui é o primeiro lugar onde as mensagens funcionam.
	
	//#bugbug
	//mas temos um problema no Y.

	//#bugbug
#ifdef EXECVE_VERBOSE
	backgroundDraw ( (unsigned long) COLOR_BLUE ); 
#endif


	//#todo:
	//podemos analisar o status aqui.
	
#ifdef BREAKPOINT_TARGET_AFTER_RUNTIME
    //#debug 
	//a primeira mensagem só aparece após a inicialização da runtime.
	//por isso não deu pra limpar a tela antes.
	printf (">>>debug hang: after runtime initialization");
	refresh_screen(); 
	while (1){ asm ("hlt"); };
#endif

    //
    // Done!
    //

    g_module_runtime_initialized = 1;

    return (int) Status;
}


/*
int runtimeInit(){
	;
};
*/


//
// End.
//
