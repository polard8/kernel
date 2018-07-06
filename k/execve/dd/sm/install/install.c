/*
 * Arquivo: install.c
 *
 * MB - Módulos incluídos no Kernel Base.
 *
 * Descrição:
 *     Rotinas de instalação do sistema.
 *     Mbr, Vbr, Bootmanager, Bootloader, Metafiles, fonfigurações.
 *     
 * @todo:
 *     Isso pode estar em um aplicativo de instalação.
 *     Poderia ser um módulo do tipo M0.
 *
 *    Versão 1.0, 2015, 2016.
 */


#include <kernel.h>

//Variáveis internas
//int installStatus;
//...


/*
 * install_os:
 *     Instala os arquivos do sistema operacional.
 *     BM.BIN, BL.BIN, (kernel Não), IDLE.BIN, SHELL.BIN, TASKMAN.BIN.
 */
void install_os()
{
    //
	// BM.BIN
	//
	
    //
	// BL.BIN
	//
	
    //
	// IDLE.BIN
	//
	
    //
	// SHELL.BIN
	//
	
    //
	// TASKMAN.BIN
	//
	    
done: 
    return;
};


/*
 * install_boot_manager:
 *     Reinstala o bootmanager.
 *
 *     O Boot Manager é um arquivo de 32kb que fica no inicio do disco.
 *     O propósito dessa rotina é carregar na memória uma versão atual 
 *     do arquivo BM.BIN e depois gravála no início do disco.
 */
void install_boot_manager()
{
   /* 
	//debug message.
	printf("* install_boot_manager: Reinstalando o Boot Manager ...\n");
	refresh_screen();
	
	//@todo: usar alocação dinâmica.
	//ESSE BUFFER É MUITO GRANDE.
	unsigned long buf[1];//[32*1024]; //32kb
	
	printf("Loading ...\n");
	carregar_arquivo("BM      BIN",(unsigned long) buf);
	
	//@todo: Check file header on memory.
	
	//@todo: Gravar o arquivo ni disco.
	
	printf("done.");
	
	
done:
	refresh_screen();
	//while(1){}
	
	*/
done:
    return;
};


/*
 * install_bootmanager_stage1:
 *    Reinstala o stage 1 do bootmanager. (MBR)
 *
 */ 
void install_bootmanager_stage1()
{
  /*
	 * Teste: Funcionou, leu um arquivo.
	printf("*teste ...\n");
	refresh_screen();
	unsigned long buf[32];
	printf("Loading ...\n");
	carregar_arquivo("STAGE1  BIN",(unsigned long) buf);
	printf("Showing ...\n");
    printf("%s\n",buf);  			
	printf("*done.");
	refresh_screen();
	while(1){}
	*/
done:
	return;
};


/*
 * install_bootmanager_stage2:
 *     Reinstala o stage 2 do bootmanager.
 */ 
void install_bootmanager_stage2()
{
  /*
	 * Teste: Funcionou, leu um arquivo.
	printf("*teste ...\n");
	refresh_screen();
	unsigned long buf[32];
	printf("Loading ...\n");
	carregar_arquivo("STAGE1  BIN",(unsigned long) buf);
	printf("Showing ...\n");
    printf("%s\n",buf);  			
	printf("*done.");
	refresh_screen();
	while(1){}
	*/
done:
	return;
};

/*
 * install_bootmanager_metafile:
 *     Reinstala o metafile do bootmanager.
 *     O metafile poderá ser editado pelo usuário administrador.
 *
 */
void install_bootmanager_metafile()
{
  /*
	 * Teste: Funcionou, leu um arquivo.
	printf("*teste ...\n");
	refresh_screen();
	unsigned long buf[32];
	printf("Loading ...\n");
	carregar_arquivo("METAFILEBIN",(unsigned long) buf);
	printf("Showing ...\n");
    printf("%s\n",buf);  			
	printf("*done.");
	refresh_screen();
	while(1){}
	*/
done:
	return;
};

/*
int installInit()
{}
*/

//
//fim.
//

