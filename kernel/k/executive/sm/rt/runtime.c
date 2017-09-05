/*
 * File: rt\runtime.c
 *
 * Descrição:
 *     Arquivo principal do módulo '/rt' do kernel base.
 *     Interfaces para rotinas de runtime do kernel.
 *
 * Objetivo:
 *    Fazer a inicialização do mecanismo de alocação dinâmica, incluindo 
 * configurações de heaps, stacks, mmblocks ... 
 *
 * Histórico:
 *    Versão 1.0, 2015 - Created.
 *    Versão 1.0, 2016 - Aprimoramento geral das rotinas básicas.
 *    ...
 */


#include <kernel.h>


//Variáveis internas.
//int runtimeStatus;
//...


/*
 * init_runtime:
 *     Initializing run time. 
 *     Kernel heap and stack stuffs.
 *     @todo: Mudar para runtimeInit().
 */
int init_runtime()
{
    //	
	// Init Memory Manager:	
	// Heap, Stack, Pages, mmblocks ...
	//
	init_mm();
	
	
	//
	// Nessa hora a memória já funciona e o malloc tambem. e mensagens.
	//
	// o video esta usando ainda as configurações de buffer e lfb faitas pelo boot loader.
	//
	
	//
	//@todo: Suspensa a configurações de páginas
	//       por enquanto fica tudo como foi configurado pelo bootloader.
	//
	
	
	//@todo: Gerenciamento de memória é primordial.
	SetUpPaging();		
	
    // Continua ...
	
done:
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
 *
 */
int KiInitRuntime()
{
    //@todo: ... interface.
	
    return (int) init_runtime();
};


/*
int runtimeInit(){
	;
};
*/


//
// End.
//
