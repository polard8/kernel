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
int init_runtime (){
	
	
	
	
	// Init Memory Manager:	
	// Heap, Stack, Pages, mmblocks, memory sizes, memory zones ...
	// ?? onde fica ??
	
	init_mm ();
	
	
    //printf ("init_runtime: debug breakpoint, real machine, gigabyte/intel ..\n");
    //refresh_screen (); 
    //while(1){}	
	
	
	// Nessa hora a memória já funciona e o malloc tambem. e mensagens.
	//
	// o video esta usando ainda as configurações de buffer e lfb faitas pelo boot loader.
	
	//
	//@todo: Suspensa a configurações de páginas
	//       por enquanto fica tudo como foi configurado pelo bootloader.
	//
	
	
	//Cria o diretório de páginas do processo kernel, page tables e 
	//area para pageframes de memória paginada.
	//pages.c
	
	SetUpPaging ();	
	
	
    //printf ("init_runtime: 2 debug breakpoint, real machine, gigabyte/intel ..\n");
    //refresh_screen (); 
    //while(1){}		

	
    // Continua ...
	
 

    g_module_runtime_initialized = 1;
	
    return (int) 0;    
};


/*
 * KiInitRuntime: 
 *     Init runtime.
 *     +Clear bss segment.
 *     +Init heap, malloc.
 *     +...
 *     @todo: 
 *         Criar aqui, apenas a interface que chama a rotina 
 *         de inicialização da runtime.
 */

int KiInitRuntime (){
	
	int Status = 0;
	
	debug_print("KiInitRuntime\n");
	
	
	//#todo 
	//preparar a tela para as mesagens;
	//mas somente se a flag de debug estiver acionada.


//#bugbug: Isso aqui não seviu pra coisa alguma,
//pois é preciso inicializar a memória antes de usar 
//a rotina que pinta o bg.	
//#ifdef EXECVE_VERBOSE
//	backgroundDraw ( (unsigned long) COLOR_BLUE ); 
//#endif	
	
    Status = (int) init_runtime ();
	
	// #### importante ####
	// provavelmente aqui é o primeiro lugar onde as mensagens funcional.
	
	//#bugbug
	//mas temos um problema no Y.
	
#ifdef EXECVE_VERBOSE
	backgroundDraw ( (unsigned long) COLOR_BLUE ); 
#endif		
	
	//#todo:
	//podemos analisar o status aqui.
	
#ifdef BREAKPOINT_TARGET_AFTER_RUNTIME
    //#debug 
	//a primeira mensagem só aparece após a inicialização da runtime.
	//por isso não deu pra limpar a tela antes.
	printf(">>>debug hang: after runtime initialization");
	refresh_screen(); 
	while (1){
		asm ("hlt");
	}
#endif	
	
    return (int) Status;	
};


/*
int runtimeInit(){
	;
};
*/


//
// End.
//
