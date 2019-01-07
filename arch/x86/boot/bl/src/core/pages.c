/*
 * File: pages.c
 *
 * Ambiente: 
 *     Boot Loader, Ring0.
 *
 * Descrição: 
 *     Configuração da paginação de memória.
 *     O Boot Loader faz uma prévia configuração de páginas. Podendo 
 * ser alteradas futuramente pelo Kernel.
 * Obs: Essa configuração básica não impede que o Kernel faça uma 
 * reconfiguração completa.
 *
 * Histórico:
 *     Versão: 1.0, 2015 - Created by Fred Nora.
 *     Versão: 1.0, 2016 - Revision.
 *     ...
 */


#include <bootloader.h>


/*
 * SetUpPaging:
 *     Configura as páginas. Mapeamento.
 *
 * In this function:
 *     (Phase 1) Endereços da memória físicas acessíveis em Kernel Mode. 
 *     (Phase 2) Inicializando o diretório.
 *     (Phase 3) Cria tabelas de páginas e coloca o ponteiro de cada uma 
 * delas na sua respectiva entrada de diretório.
 *     (Phase 4) **** CRIANDO OUTROS DIRETÓRIOS ****
 *
 * @diretorio:
 *   page_directory = 0x9C000.
 *    
 *   Page directory do kernel.
 *
 * Obs: Esse diretório criado será usado pelas primeiros processos durante
 * essa fase de construção do sistema. O ideal é um diretório por processo.
 *      Toda vez que o Kernel inicia a execução de um processo, ele deve 
 * carregar o endereço do diretório do processo em CR3. Por enquanto só tem 
 * um diretório criado e todos os processos estão definindo o diretório do
 * Kernel como sendo seu próprio. Ou seja, eles podem usar as mesmas tabelas
 * de páginas que o processo kernel usa. O problema é que com isso os 
 * processos precisam ter endereço virtual diferentes. Quando cada processo
 * tiver seu próprio diretório então eles poderão ter o mesmo endereço virtual.
 *
 * @todo: Esses endereços precisam ser registrados em variáveis globais ou
 * dentro de uma estrutura para serem passados para o Kernel.
 * 
 * Obs: Essa deve ser uma interface que chama as rotinas de configuração de 
 * paginação. (Mapeamento). 
 *
 * Obs: Essa configuração inicial feita no Boot Loader, não impede o Kernel de 
 * refazer as configurações básicas de paginação. O fato é que o kernel será o 
 * gerenciador de páginas de memória. O que não impede de haver gerenciamento
 * um user mode.
 * 
 * 2015 - Created.
 * Oct 2016, Revision.
 * ...
 */
//int pagesSetUpPages()
 
int SetUpPaging (){
	
    unsigned int i;
	
    //
	//(Phase 1) Endereços da memória físicas acessíveis em Kernel Mode.
    //	
	
	//
	// Kernel.
	//
	
	//Address. para os 4 primeiros mega da memória fisica.
	//Base, 0x100000, para o kernel que começa no primeiro mega.
	unsigned long kernel_address = 0;           //Início da memória RAM.                
	unsigned long kernel_base = KERNEL_BASE;    //Início da imagem do kernel.    
	
    //
	// (Phase 2) Endereços da memória físicas acessíveis em User Mode.
    //
	
	// User, 0x00400000.
	unsigned long user_address =  USER_BASE; // USER_BASE32MB_PA;	
	
	// VGA, Físico=0x000B8000.
	unsigned long vga_address  = VM_BASE;   
	
	// VESA LFB, foi passado pelo Boot Manager.
	unsigned long lfb_address  = (unsigned long) g_lbf_pa;
    
	// BUFFER, provisório. @todo: Mudar. (para sistemas com pouca memória.)
	//16mb. (16*1024*1024) = 0x01000000.
	unsigned long buff_address  = (unsigned long) 0x01000000; 

	
	//
	// DIRECTORY:
	// Diretórios de páginas.
    // Esse valor é salvo em cr3. Cada diretório tem seu endereço.
    // Esse diretório, configurado aqui no Boot Loader é o mesmo usado 
	// pelo Kernel.
	//
	// Obs: 
	// A idéia é que os diretório sejam criados em ordem decrescente.
	// Os espaços entre os diretório serão preenchidos com páginas 
	// avulsas. Depois, no kernel, haverá área de alocação para 
	// diretórios e páginas.
	//
	// Teste:
	// Criando diretórios para os primeiros processos do sistema. 
	// (antes de 32MB).
    //
	// Obs: Essa área onde estão os diretórios é uma área desprotegiada ainda.
	// Obs: O kernel está reconfigurando e usando outro endereço para o 
	// diretório de páginas.
	//
	// @todo: Alertar o kernel sobre esses endereços de diretórios.
	//
	
	
	unsigned long *page_directory         = (unsigned long *) (0x01000000 - 0x900000);   	
	unsigned long *idle_page_directory    = (unsigned long *) (0x01000000 - 0x901000); 
	unsigned long *shell_page_directory   = (unsigned long *) (0x01000000 - 0x902000); 
	unsigned long *taskman_page_directory = (unsigned long *) (0x01000000 - 0x903000); 
	unsigned long *x_page_directory       = (unsigned long *) (0x01000000 - 0x904000); 
	unsigned long *xx_page_directory      = (unsigned long *) (0x01000000 - 0x905000); 
	unsigned long *xxx_page_directory     = (unsigned long *) (0x01000000 - 0x906000); 	
	//Continua descendo.
	
	
	//
	// TABLES: 
	// Tabelas de páginas.
	// Uma tabela para cada área de memória que se deseja usar.
	// Usando endereços decrescentes.     
	//
	
	//kernel mode. (Endereços).
	unsigned long *km_page_table   = (unsigned long *) 0x8F000;    
    
	//kernel mode. (O kernel).
    unsigned long *km2_page_table  = (unsigned long *) 0x8E000;    
    
	//user mode.
	unsigned long *um_page_table   = (unsigned long *) 0x8D000;    

	//user mode. (vga).
	unsigned long *vga_page_table  = (unsigned long *) 0x8C000;     
    
	//user mode. (LFB).
	unsigned long *lfb_page_table  = (unsigned long *) 0x8B000;        
	
	//user mode. (buffer).
    unsigned long *buff_page_table = (unsigned long *) 0x8A000;        
    
	//
	// Continua... ??
    // 
 
 
	// Message. (verbose)
	//printf("SetUpPaging: Initializing Pages..\n");
	
	//
	// (Phase 2) Inicializando o diretório.
	//
	
	/*
	 * Inicializando o diretório de páginas usado pelo processo kernel.
	 * Isso preenche todo o diretório com páginas não presentes.
	 * 'kernel_address' é o início da memória RAM.
	 */	
	
ClearDirectory:	
		 
	for ( i=0; i < 1024; i++ ){
	    page_directory[i] = kernel_address | 2;    //0010 em binário.
	};

	
	//
	// (Phase 3) Cria tabelas de páginas e coloca o ponteiro de cada uma delas 
	// na sua respectiva entrada de diretório.
	//

Entry_0:	
	/*
	 * kernel mode pages 
	 * =================
	 * (kernel mode)(0fis = 0virt).
	 *
	 * Configurando o início da memória RAM
	 * como área em kernel mode.
	 *
	 * + Mapeando os primeiros 4MB da memória.  
	 * + Preenchendo a tabela km_page_table.
	 * + A entrada '0' do diretório aponta para
	 *   uma tabela que mapeia os primeiros 4 mega 
	 *   de endereço virtual.
	 *
	 * 'kernel_address' é o início da memória RAM.
	 *  Cada pagina tem 4KB.
	 */	
    for(i = 0; i < 1024; i++){
	    km_page_table[i] = kernel_address | 3;     //0011 binário.
	    kernel_address = kernel_address + 4096;    //4KB page.
    };
    //Criando a primeira entrada do diretório.
	//Isso mapeia os primeiros 4MB da memória RAM.
    page_directory[0] = (unsigned long) &km_page_table[0];
    page_directory[0] = page_directory[0] | 3;    //Configurando atributos.
    
Entry_1:
	/*
	 * user mode pages 
	 * ===============
	 * (400000fis = 400000virt).
	 *
	 * Configurando uma área de memória em user mode,
	 * usada por processos em user mode.
	 * Mapear 4MB da memória começando em 400000fis. 
	 * (user mode).
	 * user_address = (400000fis = 400000virt).
	 *
	 */
    for(i = 0; i < 1024; i++){
	    um_page_table[i] = user_address | 7;    //0111 em binário.
	    user_address = user_address + 4096;     //4096 = 4KB.
    };
    //Criando a entrada número 1 do diretório.
    page_directory[1] = (unsigned long) &um_page_table[0];
    page_directory[1] = page_directory[1] | 7;    //Configurando atributos.
	 
	 
Entry_2:	 
    /*
	 * User Mode VGA pages: 
	 * ===================
	 * (0xB8000fis = 800000virt).
	 * 
	 * Mapeando a área de memória usada pela memória
	 * de vídeo em modo texto, 0xB8000.
	 *
	 * Mapear 4MB da memória começando em B8000fis.
	 *
	 * Obs:
	 *     Aqui, na verdade não precisaria configurar 4 megas, 
	 *     apenas o tamanho da memória de vídeo presente em 0xb8000.
	 * vga_address = 0xB8000.
	 */
    for(i = 0; i < 1024; i++){
	    vga_page_table[i] = vga_address | 7;    //0111 em binário.
	    vga_address = vga_address + 4096;       //4KB.
    };
    //Criando a entrada número 2 no diretório.
    page_directory[2] = (unsigned long) &vga_page_table[0];
    page_directory[2] = page_directory[2] | 7;    //Configurando atributos.

Entry_768:
	/*
	 * kernel mode pages 
	 * =================
	 * (0x100000fis = 0xc0000000virt).
	 *  
	 * Configurando a área de memória onde ficará a imagem do kernel.
	 * Isso mapeia 4MB começando do primeiro mega. 
	 * (kernel mode).
	 *
	 * Preenchendo a tabela km_page_table.
	 * 'kernel_base' é o endereço físico da imagem do kernel.
	 */	
    for(i = 0; i < 1024; i++){
	    km2_page_table[i] = kernel_base | 3;    //0011 binário.
	    kernel_base = kernel_base + 4096;       //4KB.
    };
    //Criando a entrada de número 768 do diretório.
    page_directory[768] = (unsigned long) &km2_page_table[0];
    page_directory[768] = page_directory[768] | 3;    //Configurando atributos.	
	
	
Entry_769:	
    /*
	 * user mode LFB pages 
	 * ===================
	 * (0X??fis = 0xC0400000virt).
	 *
	 * Mapear 4MB à partir do endereço configurado
	 * como início do LFB.
	 * 
	 * O Boot Manager configurou VESA e obteve o endereço do LFB.
	 * O Boot Manager passou para o Boot Loader esse endereço.
	 * Mapeando 4MB da memória fisica começando no 
	 * endereço passado pelo Boot Manager.
	 * O endereço de memória virtual utilizada é 0xC0400000.
	 * lfb_address = Endereço do LFB, passado pelo Boot Manager.
	 *
	 */
    for(i = 0; i < 1024; i++){
	    lfb_page_table[i] = lfb_address | 7;    //0111 em binário.
	    lfb_address = lfb_address + 4096;       //4KB.
    };
    //Criando a entrada número 769 do diretório.
    page_directory[769] = (unsigned long) &lfb_page_table[0];
    page_directory[769] = page_directory[769] | 7;    //Configurando atributos.	
	

Entry_770:	
    /*
	 * user mode BUFFER1 pages 
	 * =======================
	 * (0X??fis = 0xC0800000virt) (BackBuffer).
	 * 
	 * Esse é o backbuffer para a memória de vídeo.
	 * O conteúdo desse buffer é transferido para o LFB. 
	 * O endereço de memória virtual utilizada é 0xC0800000.
	 * buff_address = 0x01000000. (16MB), provisório.
	 * //16mb. (16*1024*1024) = 0x01000000.
	 */
    for(i = 0; i < 1024; i++){
	    buff_page_table[i] = buff_address | 7;    //0111 em binário.
	    buff_address = buff_address + 4096;       //4KB.
    };
    //Criando a entrada número 770 do diretório.
    page_directory[770] = (unsigned long) &buff_page_table[0];
    page_directory[770] = page_directory[770] | 7;    //Configurando atributos.	
	
	
	//
	// Continua ?!
	//     Mais páginas podem ser criadas agora.
	//     Mas ficará à cargo do Kernel fazer o
	//     gerenciamento do conjunto completo de
	//     páginas usadas pelo sistema.
	//
	
	
	//
	// (Phase 4) **** CRIANDO OUTROS DIRETÓRIOS ****
	//
	
	
	//
	// **** IDLE ****
	//
	
	//Iniciando o diretório idle.
	for(i = 0; i < 1024; i++){
	    idle_page_directory[i] = kernel_address | 2;    //0010 em binário.
	};	

    //Entrada 0.
	//aproveitando a tabela criada antes.
    //Criando a primeira entrada do diretório da idle.
	//Isso mapeia os primeiros 4MB da meória RAM.
    idle_page_directory[0] = (unsigned long) &km_page_table[0];
    idle_page_directory[0] = idle_page_directory[0] | 3;    //Configurando atributos.
	
	//Entrada 1.
	//aproveitando outra tabela.
    //Criando a entrada número 1 do diretório.
    idle_page_directory[1] = (unsigned long) &um_page_table[0];
    idle_page_directory[1] = idle_page_directory[1] | 7;    //Configurando atributos.
	
	//Entrada 2.
	//vga.
    //Criando a entrada número 2 no diretório.
    idle_page_directory[2] = (unsigned long) &vga_page_table[0];
    idle_page_directory[2] = idle_page_directory[2] | 7;    //Configurando atributos.	
	
    //Entrada 768.
	//Criando a entrada de número 768 do diretório.
    idle_page_directory[768] = (unsigned long) &km2_page_table[0];
    idle_page_directory[768] = idle_page_directory[768] | 3;    //Configurando atributos.		
	
	//Entrada 769.
	//LFB
    //Criando a entrada número 769 do diretório.
    idle_page_directory[769] = (unsigned long) &lfb_page_table[0];
    idle_page_directory[769] = idle_page_directory[769] | 7;    //Configurando atributos.		
	
	//Entrada 770.
	//backbuffer.
    //Criando a entrada número 770 do diretório.
    idle_page_directory[770] = (unsigned long) &buff_page_table[0];
    idle_page_directory[770] = idle_page_directory[770] | 7;    //Configurando atributos.		
	
	
	
	//
	// **** SHELL ****
	//

    //Iniciando o diretório shell.
	for(i = 0; i < 1024; i++){
	    shell_page_directory[i] = kernel_address | 2;    //0010 em binário.
	};	

    //Entrada 0.
	//aproveitando a tabela criada antes.
    //Criando a primeira entrada do diretório da shell.
	//Isso mapeia os primeiros 4MB da meória RAM.
    shell_page_directory[0] = (unsigned long) &km_page_table[0];
    shell_page_directory[0] = shell_page_directory[0] | 3;    //Configurando atributos.
	
	//Entrada 1.
	//aproveitando outra tabela.
    //Criando a entrada número 1 do diretório.
    shell_page_directory[1] = (unsigned long) &um_page_table[0];
    shell_page_directory[1] = shell_page_directory[1] | 7;    //Configurando atributos.
	
	//Entrada 2.
	//vga.
    //Criando a entrada número 2 no diretório.
    shell_page_directory[2] = (unsigned long) &vga_page_table[0];
    shell_page_directory[2] = shell_page_directory[2] | 7;    //Configurando atributos.	
	
    //Entrada 768.
	//Criando a entrada de número 768 do diretório.
    shell_page_directory[768] = (unsigned long) &km2_page_table[0];
    shell_page_directory[768] = shell_page_directory[768] | 3;    //Configurando atributos.		
	
	//Entrada 769.
	//LFB
    //Criando a entrada número 769 do diretório.
    shell_page_directory[769] = (unsigned long) &lfb_page_table[0];
    shell_page_directory[769] = shell_page_directory[769] | 7;    //Configurando atributos.		
	
	//Entrada 770.
	//backbuffer.
    //Criando a entrada número 770 do diretório.
    shell_page_directory[770] = (unsigned long) &buff_page_table[0];
    shell_page_directory[770] = shell_page_directory[770] | 7;    //Configurando atributos.		

	//
	// **** TASKMAN ****
	//
	
    //Iniciando o diretório taskman.
	for(i = 0; i < 1024; i++){
	    taskman_page_directory[i] = kernel_address | 2;    //0010 em binário.
	};	

    //Entrada 0.
	//aproveitando a tabela criada antes.
    //Criando a primeira entrada do diretório da taskman.
	//Isso mapeia os primeiros 4MB da meória RAM.
    taskman_page_directory[0] = (unsigned long) &km_page_table[0];
    taskman_page_directory[0] = taskman_page_directory[0] | 3;    //Configurando atributos.
	
	//Entrada 1.
	//aproveitando outra tabela.
    //Criando a entrada número 1 do diretório.
    taskman_page_directory[1] = (unsigned long) &um_page_table[0];
    taskman_page_directory[1] = taskman_page_directory[1] | 7;    //Configurando atributos.
	
	//Entrada 2.
	//vga.
    //Criando a entrada número 2 no diretório.
    taskman_page_directory[2] = (unsigned long) &vga_page_table[0];
    taskman_page_directory[2] = taskman_page_directory[2] | 7;    //Configurando atributos.	
	
    //Entrada 768.
	//Criando a entrada de número 768 do diretório.
    taskman_page_directory[768] = (unsigned long) &km2_page_table[0];
    taskman_page_directory[768] = taskman_page_directory[768] | 3;    //Configurando atributos.		
	
	//Entrada 769.
	//LFB
    //Criando a entrada número 769 do diretório.
    taskman_page_directory[769] = (unsigned long) &lfb_page_table[0];
    taskman_page_directory[769] = taskman_page_directory[769] | 7;    //Configurando atributos.		
	
	//Entrada 770.
	//backbuffer.
    //Criando a entrada número 770 do diretório.
    taskman_page_directory[770] = (unsigned long) &buff_page_table[0];
    taskman_page_directory[770] = taskman_page_directory[770] | 7;    //Configurando atributos.		
	
	//
	// O que foi feito:
	// ================
	//    Foram criados 4 diretórios.
    //    kernel, idle, shell e taskman. 
    //    As tabelas configuradas para 
    //    o diretório kernel foram
    //    reaproveitadas nos demais diretórios.
    //
	

	
// Done.
done:
	//printf("Done.\n");	 
    return (int) 0;
};

//
// End.
//

