/*
 * Gramado Boot Loader - The main file for the Boot Loader.
 * (c) Copyright 2015-2016 Fred Nora.
 *
 * File: main.c 
 *
 * Descri��o:
 *    Arquivo principal do Boot Loader do sistema de 32bit para desktops.
 *    M0 - M�dulos em ring0.
 *
 * Atribui��es:
 *    + Carregar o Kernel.
 *    + Carregar os m�dulos do kernel. (idle, shell, task manager).
 *    + Carregar os metafiles de inicializa��o.
 *    + Carregar os aplicativos.
 *    + Fazer a configura��o inicial da pagina��o.
 *    + Passar o comando para o Kernel.
 *
 * Obs:
 * O Kernel ser� carregado em 0x00100000, entry point em 0x00101000.
 * Esses s�o endere�os f�sicos. Os endere�os l�gicos do Kernel s�o 0xC0000000 
 * para base e 0xC0001000 para entry point.
 *
 * Sobre o Boot Loader:
 * O BL foi carregado em 0x00020000 com entry point em 0x00021000.
 * As fun��es normais do Boot Loader come�am com 'Bl'.
 * As fun��es que utilizem recursos importados do Boot Manager come�am 
 * com 'Ble', que significa algo como Boot Loader Extention.
 *
 * In this file:
 *     + BlMain        - Entrada da parte em C do boot loader. 
 *     + BlLoadKernel  - Carrega o kernel.
 *     + BlLoadFiles   - Carrega os m�dulos do Kernel, aplicativos e 
                         metafiles de iniciliza��o.
 *     + BlSetupPaging - Configura a pagina��o.
 *     ...
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - Revision.
 *    ... 
 */
 
 
#include <bootloader.h>


// Prot�tipos de fun��es internas.
void BlLoadKernel();
void BlLoadFiles();
void BlSetupPaging();


//static char *codename = "Gramado Boot";


//char kernel_file_name[] = "kernel.bin";

//static char **argv = { NULL, NULL, NULL };
//static char **envp = { NULL, NULL, NULL };


/*
 ************************************************
 * BlMain:
 *     Entrada da parte em C do Boot Loader. 
 *
 * In this function:
 *     + Inicializa��es.
 *     + Carrega kernel.
 *     + Carrega m�dulos do kernel e 
 *       metafiles de inicializa��o.
 *     + Configura a pagina��o.
 *     + Retorna para head.s, o c�digo em 
 *       assembly que chamou essa rotina.
 */
 
//void BlMain( int argc, char *argv[], char *envp[] ) 

void BlMain (){
	
    //Set GUI.
	//Isso foi meio imperativo.
	//VideoBlock.useGui = 1;			
	//VideoBlock.useGui = 0;				
	
	//INIT ~ Faz inicializa��es b�sicas.
	init (); 
	
	
	//
	//@todo: Limpar a tela.
	//
	
	//Welcome Message.
	//banner
#ifdef BL_VERBOSE		
	printf("BlMain: Starting Boot Loader..\n");	
#endif    
	
	//Debug:
	//kprintf( "BlMain: Boot Loader 32 bits em C (TEXT Mode) #test. #hang", 9, 9 );
	//while(1){}

    if (g_initialized != 1)
	{
		printf ("BlMain:");
		die();
	}


	//Debug...
	//printf("#################################################\n");
	//printf("#DEBUG: *HANG\n");		
	//refresh_screen();
	//while(1){}
	

	//*Importante:
    // ===========
    //     Daqui pra frente vamos carregar os arquivos. Lembrando que
    // o Boot Loader ainda n�o sabe carregar de outro dispositivo se n�o IDE. 
    
    //
	// Inicia os carregamentos.
	//
	
	//Carrega arquivos.	
#ifdef BL_VERBOSE	
    printf("BlMain: Loading files..\n");
    refresh_screen();
#endif

    
	// #importante:
	// Carregando o diret�rio raiz e a fat na mem�ria.
	// Evitando repeti��o de carregamento.
	
	
	// Ok isso deu certo.
	fs_load_rootdirEx();
	fs_load_fatEx();
	
    g_fat16_root_status = 1;
    g_fat16_fat_status = 1;	

	
	//
	//  ## Loading files ... ##
	//
	
	//loading kernel base.
	
    BlLoadKernel ();
	
	
	// @Todo: (Pensando na possibilidade)
	// Aqui podemos ter acondi��o de carregarmos apenas o krnel base.
	// Essa op��o dever� ser habilitada atrav�s de um arquivo de configura��o.
	// Ou no header do kernel base poder� ter a indica��o de quais m�dulos 
	// deve-se carregar.
	
	
	//Loading files.
	
	BlLoadFiles ();

    
    // Paging:
    //     Depois carregar o kernel e os m�dulos 
	//     nos seus endere�os f�sicos, 
    //     configura a pagina��o e 
	//     volta para o assembly para 
	//     configurar os registradores e 
	//     passar o comando para o kernel.
	//
	// Obs:
	//     Essa configura��o b�sica n�o impede
	//     que o kernel fa�a uma reconfigura��o completa.
    
#ifdef BL_VERBOSE	
	printf("BlMain: Initializing pages..\n");
	//refresh_screen();
#endif	
	BlSetupPaging();
    
    
	//@todo: Atualizar status.
 	
	
  // Done:
  //     Ao retornar, head.s configura CR0 e CR3.	

//done:
	
    //Debug message.
	
//#ifdef BL_VERBOSE	
//	printf("BlMain: LFB={%x} \n",g_lbf_pa);	
//#endif

#ifdef BL_VERBOSE	
    printf("BlMain: Done\n");
    //printf("#DEBUG: *HANG\n");		
	refresh_screen();
    //while(1){};	
#endif	

	//return;
};


/*
 ***************************************************************
 * BlLoadKernel: 
 *     Carrega o Kernel.
 *     Kernel carregado em 0x00100000, entry point em 0x00101000.
 */ 
void BlLoadKernel (){
	
    int Status;
	
	Status = (int) elfLoadKernelImage ();	
	
	if ( Status != 0 )
	{
		printf ("BlLoadKernel:\n");
	    die();		
	};
};
 
 
/*
 ****************************************************
 * BlLoadFiles:
 *     Carrega outros arquivos.
 * In this function:
 *     + Carrega tarefas do sistema, (idle, shell ...)
 *     + ...
 */ 
void BlLoadFiles (){
	
	int Status;
	
	// Est� em loader.c
	Status = (int) load_files ();
	
	if ( Status != 0 )
	{
	    //Erro fatal.
		printf ("BlLoadFiles:\n");
	    die();	
	};
};


/*
 ********************************************************************
 * BlSetupPaging:
 *     Configura as p�ginas.
 *
 * In this function:
 *
 * @diretorio:
 *   page_directory = 0x9C000
 *   OBS: Esse diret�rio criado ser� usado pelas primeiros processos durante
 * essa fase de constru��o do sistema.
 *        O ideal � um diret�rio por processo.
 *        Toda vez que o kernel iniciar a execu��o de um processo ele deve 
 * carregar o endere�o do diretorio do processo em CR3.
 *       Por enquanto s� tem um diret�rio criado.
 *
 * @p�ginas:
 *   km_page_table  = 0x8C000 (RING 0).
 *   um_page_table  = 0x8E000 (RING 3).
 *   vga_page_table = 0x8F000 (RING 3).
 *   lfb_page_table = ?? (RING 3).
 *
 *  @todo: 
 *      Esses endere�os precisam ser registrados em vari�veis globais ou
 * dentro de uma estrutura para se passado para o Kernel.
* 
 *      Essa deve ser uma interface que chama as rotinas de configura��o
 * da pagina��o. 
 * 
 */ 
void BlSetupPaging (){
	
    SetUpPaging ();
};


/*
 ********************************************
 * BlAbort:
 *     Rotina para abortar o bootloader em caso de erro grave.
 */
void BlAbort (){
	
	
	//@todo: 
	//    Talvez poderia ter uma interface antes de chamar a rotina abort().
	//
	//ex:
	//checks()
	
    abort (); 
    //die ();	
};


/*
 *****************************************************************
 * BlKernelModuleMain:
 *     Se � o kernel que est� chamando o Boot Loader na forma de 
 * m�dulo do kernel em kernel mode.
 *
 */
 
void BlKernelModuleMain (){
	
    printf("BlKernelModuleMain: Boot Loader\n");
    refresh_screen();
};



/*
 **************************************************
 * die:
 *     A inten��o dessa rotina deixar o processador no 
 * estado hlt durante um erro fatal. Para que ele n�o fique 
 * funcionando a 100% num loop infinito.
 */

// Final message !
// Bullet, Message.
// Wait forever. 
// Halt system.	
//
//  No return.
//	     	


void die (){
	
	printf ("[BL]: * System Halted");    
	refresh_screen ();
	   
	while (1){
		
	    asm("cli"); 	
	    asm("hlt");    		
	};                        
};
 

//
// End.
//  
