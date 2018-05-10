/*
 * Gramado Boot Loader - The main file for the Boot Loader.
 * (c) Copyright 2015-2016 Fred Nora.
 *
 * File: main.c 
 *
 * Descrição:
 *    Arquivo principal do Boot Loader do sistema de 32bit para desktops.
 *    M0 - Módulos em ring0.
 *
 * Atribuições:
 *    + Carregar o Kernel.
 *    + Carregar os módulos do kernel. (idle, shell, task manager).
 *    + Carregar os metafiles de inicialização.
 *    + Carregar os aplicativos.
 *    + Fazer a configuração inicial da paginação.
 *    + Passar o comando para o Kernel.
 *
 * Obs:
 * O Kernel será carregado em 0x00100000, entry point em 0x00101000.
 * Esses são endereços físicos. Os endereços lógicos do Kernel são 0xC0000000 
 * para base e 0xC0001000 para entry point.
 *
 * Sobre o Boot Loader:
 * O BL foi carregado em 0x00020000 com entry point em 0x00021000.
 * As funções normais do Boot Loader começam com 'Bl'.
 * As funções que utilizem recursos importados do Boot Manager começam 
 * com 'Ble', que significa algo como Boot Loader Extention.
 *
 * In this file:
 *     + BlMain        - Entrada da parte em C do boot loader. 
 *     + BlLoadKernel  - Carrega o kernel.
 *     + BlLoadFiles   - Carrega os módulos do Kernel, aplicativos e 
                         metafiles de inicilização.
 *     + BlSetupPaging - Configura a paginação.
 *     ...
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - Revision.
 *    ... 
 */
 
 
#include <bootloader.h>


//
// Protótipos de funções internas.
//

void BlLoadKernel();
void BlLoadFiles();
void BlSetupPaging();


//static char *codename = "Gramado Boot";


/*
 ******************************************************************
 * BlMain:
 *     Entrada da parte em C do Boot Loader. 
 *
 * In this function:
 *     + Inicializações.
 *     + Carrega kernel.
 *     + Carrega módulos do kernel e metafiles de inicialização.
 *     + Configura a paginação.
 *     + Retorna para head.s, o código em assembly que chamou essa rotina.
 */
void BlMain()
{	
    //Set GUI.
	//Isso foi meio imperativo.
	//VideoBlock.useGui = 1;			
	//VideoBlock.useGui = 0;				
	
	//INIT ~ Faz inicializações básicas.
	init(); 
	
	
	libcInitRT();
	
	//
	//@todo: Limpar a tela.
	//
	
	//Welcome Message.
#ifdef BL_VERBOSE		
	printf("BL.BIN: Starting Boot Loader..\n");	
#endif  

    printf("BL.BIN: initializin ata ..\n");
    ata_initialize();   
	
	//Debug:
	//kprintf( "BlMain: Boot Loader 32 bits em C (TEXT Mode) #test. #hang", 9, 9 );
	//while(1){}

    if(g_initialized != 1){
		printf("BlMain:");
		die();
	}


	//Debug...
	//printf("#################################################\n");
	//printf("#DEBUG: *HANG\n");		
	//refresh_screen();
	//while(1){}
	
	//
	//*Importante:
    // ===========
    //     Daqui pra frente vamos carregar os arquivos. Lembrando que
    // o Boot Loader ainda não sabe carregar de outro dispositivo se não IDE. 
	//
    
    //
	// Inicia os carregamentos.
	//
	
	//Carrega arquivos.	
#ifdef BL_VERBOSE	
    printf("BlMain: LOADING FILES ...\n");
    refresh_screen();
#endif

    //
	// #importante:
	// Carregando o diretório raiz e a fat na memória.
	// Evitando repetição de carregamento.
	//
	
	// Ok isso deu certo.
	fs_load_rootdirEx();
	fs_load_fatEx();
	
    g_fat16_root_status = 1;
    g_fat16_fat_status = 1;	

	
	//printf("Loading kernel base ...\n");
    BlLoadKernel();
	
	//
	// @Todo: (Pensando na possibilidade)
	// Aqui podemos ter acondição de carregarmos apenas o krnel base.
	// Essa opção deverá ser habilitada através de um arquivo de configuração.
	// Ou no header do kernel base poderá ter a indicação de quais módulos 
	// deve-se carregar.
	//
	
	//printf("Loading files ...\n");
	BlLoadFiles();

    //
    // Paging:
    //     Depois carregar o kernel e os módulos 
	//     nos seus endereços físicos, 
    //     configura a paginação e 
	//     volta para o assembly para 
	//     configurar os registradores e 
	//     passar o comando para o kernel.
	//
	// Obs:
	//     Essa configuração básica não impede
	//     que o kernel faça uma reconfiguração completa.
    //
#ifdef BL_VERBOSE	
	printf("BlMain: Initializing pages..\n");
	//refresh_screen();
#endif	
	BlSetupPaging();
    
    
	//@todo: Atualizar status.
 	

//	
// Done:
//     Ao retornar, head.s configura CR0 e CR3.	
//
done:
	
    //Debug message.
//#ifdef BL_VERBOSE	
//	printf("BlMain: LFB={%x} \n",g_lbf_pa);	
//#endif

#ifdef BL_VERBOSE	
    printf("BlMain: Done.\n");
    //printf("#DEBUG: *HANG\n");		
	refresh_screen();
    //while(1){};	
#endif	
	return;
};


/*
 ***************************************************************
 * BlLoadKernel: 
 *     Carrega o Kernel.
 *     Kernel carregado em 0x00100000, entry point em 0x00101000.
 */ 
void BlLoadKernel()
{   
    int Status;
	
	Status = (int) load_kernel();	
	if(Status != 0){
	    //Erro fatal.
		printf("BlLoadKernel:\n");
	    die();
		//refresh_screen();		
	    //while(1){};			
	};
	return;
};
 
 
/*
 ****************************************************
 * BlLoadFiles:
 *     Carrega outros arquivos.
 * In this function:
 *     + Carrega tarefas do sistema, (idle, shell ...)
 *     + ...
 */ 
void BlLoadFiles()
{ 
	int Status;
	
	// Está em loader.c
	Status = (int) load_files();
	if(Status != 0){
	    //Erro fatal.
		printf("BlLoadFiles:\n");
	    die();	
	};
	return;
};


/*
 ********************************************************************
 * BlSetupPaging:
 *     Configura as páginas.
 *
 * In this function:
 *
 * @diretorio:
 *   page_directory = 0x9C000
 *   OBS: Esse diretório criado será usado pelas primeiros processos durante
 * essa fase de construção do sistema.
 *        O ideal é um diretório por processo.
 *        Toda vez que o kernel iniciar a execução de um processo ele deve 
 * carregar o endereço do diretorio do processo em CR3.
 *       Por enquanto só tem um diretório criado.
 *
 * @páginas:
 *   km_page_table  = 0x8C000 (RING 0).
 *   um_page_table  = 0x8E000 (RING 3).
 *   vga_page_table = 0x8F000 (RING 3).
 *   lfb_page_table = ?? (RING 3).
 *
 *  @todo: 
 *      Esses endereços precisam ser registrados em variáveis globais ou
 * dentro de uma estrutura para se passado para o Kernel.
* 
 *      Essa deve ser uma interface que chama as rotinas de configuração
 * da paginação. 
 * 
 */ 
void BlSetupPaging(){
    SetUpPaging();
	return;
};


/*
 * BlAbort:
 *     Rotina para abortar o bootloader em caso de erro grave.
 */
void BlAbort()
{
	//
	//@todo: 
	//    Talvez poderia ter uma interface antes de chamar a rotina abort().
	//
	//ex:
	//checks()
	//
	
//Done:	
    abort(); 
    while(1){};	
};


/*
 * BlKernelModuleMain:
 *     Se é o kernel que está chamando o Boot Loader na forma de 
 * módulo do kernel em kernel mode.
 *
 */
void BlKernelModuleMain()
{
    printf("BlKernelModuleMain: Boot Loader \\o/ !");
    refresh_screen();
	
	while(1){}
	return;	
}



/*
 **************************************************
 * die:
 *     A intenção dessa rotina deixar o processador no 
 * estado hlt durante um erro fatal. Para que ele não fique 
 * funcionando a 100% num loop infinito.
 */
void die()
{
    // Final message !
    printf("* System Halted!\n");    // Bullet, Message.
	refresh_screen();
	   
	// Wait forever.   
	while(1)
	{
	    asm("cli"); 	
	    asm("hlt");    // Halt system.		
	};                        
    
	//
    //  No return.
    //	     	
};
 

//
// End.
//  
