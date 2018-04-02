/*
 * Gramado Executive - The main file for the Executive module in the 
 * kernel base. 
 * (c) Copyright 2015-2016 Fred Nora.
 *
 * File: k\executive.c 
 * 
 * Classes:
 *     system.ram (K5)
 *
 * Obs: O executive lida com gerentes que manipulam rotinas independentes
 *      de dispositivos. Seu ambiente natural é a RAM. É o ambiente de maior
 *      liberdade, sem as restrições impostas pelos dispositivos externos.
 *      O ambiente do executive é ideal para oferecer variáveis e funções globais.
 * e públicas. O ideal é que os processos em user mode somente tenham acesso
 * ao que é oferecido por essa camada.
 *      Não é pertinente a inclusão de código assembly nessa camada.
 *
 * Descrição:
 *     Arquivo principal do módulo Executive do Kernel Base.
 *     MB - Módulos incluídos no Kernel Base.
 *     Contém drivers básicos em Kernel Mode, 
 *     compilados dentro do Kernel Base.
 *     Contém Managers e Servers e o SubSystem que recebe as 
 *     chamadas do usuário.
 *
 *   OBS: 
 *   *IMPORTANTE  
 *   Os módulos do executive são incluidos ao 'Kernel Base'
 *   na hora da compilação, pois são excenciais para o 
 *   funcionamento do Kernel.
 *
 *   Módulos em Kernel Mode também poderão ser ligados dinamicamente, 
 *   mas não podem ser sistemicamente importantes. Pois não é certo deixar
 *   o usuário incluir um módulo que possa travar o sistema.
 *
 * @todo:
 * Os serviços oferecidos por esse módulo aparecerão aqui 
 * começando por 'sys_'. Corrigindo, na verdade os serviços
 * devem começar por 'systemXXXXX'.
 *
 * executiveExecutive(); é o construtor
 *
 * Versão 1.0, 2015, 2016.
 */
 
 
#include <kernel.h>
//#include "eidata.h"  //Executive Internal Data.

//unsigned char  EcecutiveName[] = "EXECUTIVE LAYER";


/*
void executiveMain();
void executiveMain(){
	return;
};
*/

/*
 * executive_config_exported_functions:
 *
 *     Configura a tabela do Kernel de funções exportadas
 *	   e a tabela de ponteiros para tabelas dos outros programas em Kernel Mode.
 *
 */
/*
int executive_config_exported_functions(); 
int executive_config_exported_functions()
{
	
    ring0_exported = (void*) malloc(sizeof(struct ring0_exported_d));
	
	if( (void*) ring0_exported == NULL )
	{
	    return (int) 1;
	}
	else
	{
	    //ring0_exported->bm_exported  = ( ponteiro para a tabela de funções exportadas pelo boot manager)
		//ring0_exported->bl_exported  = ( ponteiro para a tabela de funções exportadas pelo boot loader)
		//ring0_exported->bk_exported  = ( ponteiro para a tabela de funções exportadas pelo kernel)
		
		
		//@todo: Criar a tabela do kernel e salvar o ponteiro nessa estrutura ai.
		//       Pegar os ponteiros de bootmanager e bootloader e colocar ai.
		
	};
	
	
	// @todo: Nothing more?
	
done:
    return (int) 0;
};

*/

/*
 * sys_showkernelinfo:
 *     Show kernel info.
 */
void sys_showkernelinfo()
{
	KiInformation();
	return;
};


/*
 * init_executive:
 *     Initialize the kernel executive.
 *     Archtecture (independent) inicialization. 
 */
int init_executive()
{
    int Status = 0;
	
	printf("EXECUTIVE:\n");
	
	//  PCI - Pega informações da PCI.
	init_pci();
	
	// CLOCK - Pega informações de Hora e Data.
    init_clock();
	
	//configura a tabela do kernel de funções exportadas
	//e tabela de ponteiros para tabelas dos outros programas em kernel mode.
    //Status = (int) executive_config_exported_functions();

	//Continua ...
	
Done:
    
	//@todo: Checar a validade de 'Initialization' ??

    Initialization.executive = 1;	
	printf("Done!\n");	
	return (int) Status;
};


/*
int executiveInit()
{};
*/

//
// End.
//

