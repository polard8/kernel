/*
 * File: pc/mm/x86/pages.c
 *
 * Descrição:
 *     Faz a configuração da paginação de memória e oferece rotinas de
 * suporte ao mapeamento de memória física.
 *     Faz parte do modulo /mm da classe ram.
 *
 * *Importante:
 *     Essa rotina pertence ao módulo de gerenciamento de memória. Não possui
 * informações sobre processos. Qualquer informação sobre processos deve ser 
 * conseguida através de invocação de métodos pertencentes ao módulo 
 * /microkernel.
 *
 * @todo: 
 *    IMPORTANTE:
 *    +FAZER GERENCIAMENTO DA MEMÓRIA FÍSICA. 
 *    +DIVIDIR A MEMÓRIA FÍSICA EM PARTIÇÕES DE 4MB E 
 *    +DIVIDIR CADA PARTIÇÃO EM FRAMES DE 4KB, O QUE DÁ 1024 FRAMES POR 
 * PARTIÇÃO.
 *
 * Obs: 
 *     Chamaremos de 'framepool' o conjunto de 1024 frames.
 *     Poderemos mapear um framepool inteiro se preciso. 
 *
 * @todo:
 * *Importante:
 * Obs: 
 *     Os processos Idle, Shell e Taskman estão usando o diretório de páginas 
 * do processo Kernel. É preciso criar um diretório para cada processo e 
 * criar uma rotina de automação na criação de diretórios de páginas.
 *
 * @todo: 
 *     Criar rotinas para ver o conteúdo da lista de diretórios de páginas.
 *     ?? Cada diretório deve ter uma estrutura, cujo ponteiro vai pra dentro 
 * da lista.
 *     ?? A estrutura mostrará informações sobre o diretório de páginas.
 *
 * @todo: 
 *     Criar rotinas que manipulem as estruturas de diretório de páginas e de 
 * pagetables. 
 *
 * Obs: Todas as pagetables podem ficar em sequência em uma mesma região do endereço
 * lógico do processo kernel.
 *
 * In this file:
 * =============
 *     +CreatePageDirectory
 *     +CreatePageTable
 *     +SetCR3
 *     +SetUpPaging
 *     +
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - Revision.
 *     ...
 */


// Algumas áreas de memória:
// =========================
//
// + kernel area    = 1024 pageframes (4MB).
// + kernel image   = 1024 pageframes (4MB).
// + user mode area = 1024 pageframes (4MB).
// + vga            = 1024 pageframes (4MB).
//     (Obs: Isso transpassa o real tamanho da vga).
// + lfb (frontbuffer) = 1024 pageframes (4MB).
//     (Obs: Isso é muito pouco, placas de video possuem muita memo'ria)
// + backbuffer     = 1024 pageframes (4MB). 
//     (Obs: Isso realmente é pouco, no backbuffer deve caber uma imagem 
// grande, que será dividida em vários monitores).
// + ?? tem ainda um pool de pageframes usados para alocaçao.


#include <kernel.h>


//
// Variáveis passadas pelo Boot Loader.
//


// Obs: 
// Teremos que rever os argumentos passados pelo Boot Loader ao Kernel 
// Pois podemos tornar o Kernel compatível com GRUB.

extern unsigned long SavedBootBlock;    //Parâmtros passados pelo Boot Loader.
extern unsigned long SavedLFB;          //LFB address.
extern unsigned long SavedX;            //Screen width.
extern unsigned long SavedY;            //Screen height.
extern unsigned long SavedBPP;          //Bits per pixel.
//...


//
// Funções importadas.
//

extern void set_page_dir (void);
//...



//Usar alguma rotina de hal_ pra isso;
//extern unsigned long _get_page_dir();

/*
// Page table/directory entry flags.
#define PTE_P		0x001	// Present
#define PTE_W		0x002	// Writeable
#define PTE_U		0x004	// User
#define PTE_PWT		0x008	// Write-Through
#define PTE_PCD		0x010	// Cache-Disable
#define PTE_A		0x020	// Accessed
#define PTE_D		0x040	// Dirty
#define PTE_PS		0x080	// Page Size
#define PTE_MBZ		0x180	// Bits must be zero
*/

/*
 ?? Para qual tipo ??
enum PAGE_PTE_FLAGS {
 
	I86_PTE_PRESENT			=	1,		    // 0000000000000000000000000000001
	I86_PTE_WRITABLE		=	2,		    // 0000000000000000000000000000010
	I86_PTE_USER			=	4,		    // 0000000000000000000000000000100
	I86_PTE_WRITETHOUGH		=	8,		    // 0000000000000000000000000001000
	I86_PTE_NOT_CACHEABLE	=	0x10,		// 0000000000000000000000000010000
	I86_PTE_ACCESSED		=	0x20,		// 0000000000000000000000000100000
	I86_PTE_DIRTY			=	0x40,		// 0000000000000000000000001000000
	I86_PTE_PAT			   =	0x80,		// 0000000000000000000000010000000
	I86_PTE_CPU_GLOBAL		=	0x100,		// 0000000000000000000000100000000
	I86_PTE_LV4_GLOBAL		=	0x200,		// 0000000000000000000001000000000
   	I86_PTE_FRAME			=	0x7FFFF000 	// 1111111111111111111000000000000
};
*/



/*
static inline void __native_flush_tlb_single (unsigned long addr)
{
   asm volatile ("invlpg (%0)" ::"r" (addr) : "memory");
}
*/


/*
 ************************
 * CreatePageDirectory:
 *
 *     Cria um page directory para um processo.
 *
 *     Obs:
 *     + O endereço precisa ser alocado antes.
 *     + Precisa ser um endereço ( ## físico  ## ).
 *     +...
 *
 * Obs:
 *    **  Aviso importante!  **
 *    O endereço precisa ser um endereço físico.
 *    O endereço passado via argumento pode ser alocado dinamicamente antes 
 * ou então essa rotina pode corromper alguma área importante.
 *    Antes de chamar essa rotina devemos alocar memória do tamanho de 
 * um diretório, que é de 1024 entradas de 4 bytes. (1024*4).
 *
 * #obs: 
 * #bugbug: 
 * Quando criamos um novo diretório de páginas ele esta' vazio, nem mesmo o
 * kernel base foi mapeado na parte superior da memória virtual.
 * Para todo novo diretório criado, precisamos mapear as páginas que o 
 * kernel base vai usar. Por isso que clonar o diretório de páginas do 
 * kernel parece se uma boa opção.
 */
 
//deve retornar o endereço do diretório de páginas criado,
//que é um clone do diretório de páginas do kernel.


//#importante:
//retornaremos o endereço virtual, para que a função create_process possa usar 
//tanto o endereço virtual quanto o físico.

void *CreatePageDirectory (void){
	
	int i;
	
	//virtual.
	unsigned long destAddressVA;  
	
	//alocaremos uma página apenas, pois tem 4KB.
	destAddressVA = (unsigned long) newPage (); 
	if ( destAddressVA == 0 )
	{
		return NULL;
	}
	
	//o endereço do diretório de páginas clone.
    //precisamos uar o endereço virtual para manipularmos os dados,
	//pois estamos no esquema de memória do kernel base.
	unsigned long *dest = (unsigned long *) destAddressVA;  
	
	//o endereço do diretório de páginas do kernel.
	// #importante: O endereço dessa físico e virtual dessa tabela são iguais.
	unsigned long *src = (unsigned long *) gKernelPageDirectoryAddress;  
	
	
    //Nesse momento já temos o endereço da origem e do destino.
    //O endereço lógico e físico do diretório de páginas do kernel 
    //são iguais, porém os endereços físico e virtual do diretório 
    //de páginas clone são diferentes.
    //#importante: A rotina de cópia do conteúdo entre os buffers precisa usar 
    //endereços lógicos, pois estamos usando o kernel base e sua 
    //configuração de memória.	
	
	//
	// ## Copiar ##
	//

	// Agora vamos apenas copiar o diretório de páginas do kernel 
	// para o diretório de páginas clone.
	// São 1024 dwords.
	
	// Criamos um diretório vazio com páginas não presentes.
	// 0010 em binário.	
	
	for ( i=0; i < 1024; i++ )
	{
		dest[i] = (unsigned long) src[i];    
	};	
	
	// #importante
	// Retornamos um endereço lógico, que será transformado em físico
	// para colocarmos no cr3.
	
	return (void *) destAddressVA;
}


/*
 *******************
 * CreatePageTable:
 *     Cria uma page table em um diretório.
 *     Obs:
 *     + O endereço precisa ser alocado antes.
 *     + Precisa ser um endereço físico.
 *     + O diretório precisa ser um diretório válido.
 *
 * Argumentos:
 *
 *     directory_address
 *         O endereço do diretório onde colocaremos o endereço 
 * do início da tabela de página que criaremos.
 *
 *     offset
 *         O deslocamento dentro do diretório para sabermos o 
 * lugar para salvarmos o endereço da tabela de páginas 
 * que estamos criando.
 * @todo: Na hora de salvarmos esse endereço também 
 * temos que incluir as flags.
 *
 *     page_address
 * O endereço da página que estamos criando.
 * Obs: Precisamos alocar memória para a pagetable 
 * que estamos criando, isso antes de chamarmos essa rotina. 
 * Obs: Uma pagetable tem 4096 bytes de tamanho.
 * Obs: Criamos uma tabela de páginas, com páginas em user mode.
 *
 * #importante:
 * O offset é um índice dentro do diretório de páginas.
 */ 

void *CreatePageTable ( unsigned long directory_address, 
                       int offset, 
					   unsigned long region_address )
{
	
	int i;
	
	//
    // ### pd  ###
    //	
	
	// #importante:
	// Endereço virtual do diretório de páginas.
	// Precisamos do endereço virtual do diretório para editá-lo.
	
	unsigned long *PD = (unsigned long *) directory_address;       
	
	if ( directory_address == 0 ){
		
		return NULL;
	}	


	//
    // ### pt  ###
    //	
	
	//#importante:
	//Endereço virtual da tabela de páginas.
	//Precisamos de um endereço virtual para manipularmos a tabela.
	//pois o kernel trabalha com os endereços virtuais ...
	//só depois converteremos e salvaremos na entrada do diretório 
	//o ponteiro que é um endereço físico.
	

    unsigned long ptVA = (unsigned long) malloc (4096);
	//unsigned long ptVA = (unsigned long) newPage(); 
	
	if ( ptVA == 0 ){
		
		return NULL;
	}	
	

	//o endereço virtual permite manipularmos a pagetable daqui do kernel.
	unsigned long *newPT = (unsigned long *) ptVA;     
	
	
	//
    // ### Offset  ###
    //	

	
	//Limits.
	if( offset < 0 )
	{
		return NULL;
	}
	
	
	//
    // ### region  ###
    //		

	//Limits.
	if( region_address == 0 )
	{
		return NULL;
	}	
	
	
	
	//
    // ### pt  ###
    //		
	

	// Criando uma pagetable.
	// 4MB de memória física.
	// user mode pages
	// Será usado pelo processo em user mode. 
	// Note as flags.(7).
	
	for ( i=0; i < 1024; i++ )
    {
		//7 decimal é igual a 111 binário.
	    newPT[i] = (unsigned long) region_address | 7;             
	    region_address = (unsigned long) region_address + 4096;  //+4KB.
    };
	
	
	//
    // ### pd  ###
    //		

	//Aqui devemos incluir as flags também.
	//Configurando os atributos.
	
	//#importante
    //precisamos colocar um endereço físico na entrada do diretório.
	
	//#importante:
	//Para chamarmos essa rotina temos que ter o diretório do kernel configurado.
	
	unsigned long ptPA = (unsigned long) virtual_to_physical ( ptVA, gKernelPageDirectoryAddress ); 	
	
	PD[offset] = (unsigned long) ptPA;
    PD[offset] = (unsigned long) PD[offset] | 7;      

 
	// Retornaremos o endereço virtual para que a tabela possa ser manipulada 
	// pelo kernel.

    return (void *) ptVA;
}
 

/*
 * SetCR3:
 *     Configurando cr3.
 *     Obs: Precisa ser endereço físico.
 *     Obs: Chamamos uma rotina em assembly.
 *     @todo: Mudar para pagesSetCR3(.)
 */

//void pagesSetCR3(unsigned long address) 

void SetCR3 (unsigned long address){
	
	if (address == 0){
		return;
	}
	
	asm volatile ("\n" :: "a"(address) );
	
	set_page_dir();
}


/*
 * mapping_ahci0_device_address:
 *     Mapeando um endereçi fícico usado pelo driver AHCI.    
 */

//e, ???h ficará a pagetable para mapear o endereço físico em ????va


unsigned long mapping_ahci1_device_address ( unsigned long address ){
	
    unsigned long *page_directory = (unsigned long *) gKernelPageDirectoryAddress;      

	
	//##bugbug: 
	//Esse endereço é improvisado. Parece que não tem nada nesse endereço.
	//#todo: temos que alocar memória e converter o endereço lógico em físico.
	
	unsigned long *ahci1_page_table = (unsigned long *) PAGETABLE_AHCI1; //0x00083000 
	
	
    // If you do use a pointer to the device register mapping, 
	// be sure to declare it volatile; otherwise, 
	// the compiler is allowed to cache values and reorder accesses to this memory.	
	
    // Since this is device memory and not regular DRAM, you'll have to tell 
	// the CPU that it isn't safe to cache access to this memory. 	
	//(cache-disable and write-through).
	
	
	// #imporatante
	// #todo:
	// Ainda não calculamos o uso de memória física.
	// Precisamos saber quanta memória física esse dispositivo está usando.
	
	int i;
	for ( i=0; i < 1024; i++ ){
		
		
		// 10=cache desable 8= Write-Through 0x002 = Writeable 0x001 = Present
		// 0001 1011
		ahci1_page_table[i] = (unsigned long) address | 0x1B; // 0001 1011
		//nic0_page_table[i] = (unsigned long) address | 3;     
	    
		address = (unsigned long) address + 4096;  
    };
	

	//f0400000      961
	
    page_directory[ENTRY_AHCI1_PAGES] = (unsigned long) &ahci1_page_table[0];
    page_directory[ENTRY_AHCI1_PAGES] = (unsigned long) page_directory[ENTRY_AHCI1_PAGES] | 0x1B; // 0001 1011   		
	
	//(virtual)
	return (unsigned long) AHCI1_VA;
}


/*
 * mapping_nic0_device_address:
 *     Mapeando um endereçi fícico usado pelo NIC1.    
 */

//82540 test
//e, 88000h ficará a pagetable para mapear o endereço físico em f0000000va
//mapeando o nic principal.
//considerando que tenhamos mais de uma placa de rede, 
//esse mapeamento só será válido para o primeiro.

unsigned long mapping_nic1_device_address ( unsigned long address ){
	
    unsigned long *page_directory = (unsigned long *) gKernelPageDirectoryAddress;      

	
	//##bugbug: 
	//Esse endereço é improvisado. Parece que não tem nada nesse endereço.
	//#todo: temos que alocar memória e converter o endereço lógico em físico.
	
	//unsigned long volatile *nic0_page_table = (unsigned long volatile *) PAGETABLE_NIC1; //0x88000;
	unsigned long *nic0_page_table = (unsigned long *) PAGETABLE_NIC1; //0x88000;
	
	
    // If you do use a pointer to the device register mapping, 
	// be sure to declare it volatile; otherwise, 
	// the compiler is allowed to cache values and reorder accesses to this memory.	
	
    // Since this is device memory and not regular DRAM, you'll have to tell 
	// the CPU that it isn't safe to cache access to this memory. 	
	//(cache-disable and write-through).
	
	
	// #imporatante
	// #todo:
	// Ainda não calculamos o uso de memória física.
	// Precisamos saber quanta memória física esse dispositivo está usando.
	
	
	int i;
	for ( i=0; i < 1024; i++ ){
		
		
		// 10=cache desable 8= Write-Through 0x002 = Writeable 0x001 = Present
		// 0001 1011
		nic0_page_table[i] = (unsigned long) address | 0x1B; // 0001 1011
		//nic0_page_table[i] = (unsigned long) address | 3;     
	    
		address = (unsigned long) address + 4096;  
    };
	

	//f0000000      960
	
    page_directory[ENTRY_NIC1_PAGES] = (unsigned long) &nic0_page_table[0];
    page_directory[ENTRY_NIC1_PAGES] = (unsigned long) page_directory[ENTRY_NIC1_PAGES] | 0x1B; // 0001 1011   		
    //page_directory[ENTRY_NIC1_PAGES] = (unsigned long) page_directory[ENTRY_NIC1_PAGES] | 3;   	
	
	
	//(virtual)
	return (unsigned long) NIC1_VA;
};


/*
 *************************************************************
 * SetUpPaging:
 *     Configura o diretório de páginas do processo Kernel e 
 * algumas tabelas de páginas.
 *
 * Obs: 
 *     Na hora em que um processo é criado deve-se criar seu diretório de 
 * páginas e as tabelas de páginas usadas por ele, de acordo com o tamanho 
 * do processo.
 *
 * Diretório:
 *     page_directory = 0x0009C000. (Endereço físico).#kernel
 *
 * Obs:
 *     Esse diretório criado será usado pelo processo Kernel e também por 
 * outros processos também durante essa fase de construção do sistema. 
 * Depois cada processo terá seu próprio diretório de páginas. Isso está em 
 * fase de implementação. O ideal é um diretório por processo.
 *     Toda vez que o Kernel iniciar a execução de um processo ele deve 
 * carregar o endereço do diretório do processo no registrador de controle CR3.
 * 
 * @todo: 
 *     Por enquanto só um diretório foi criado.
 *     
 * @tod:
 *     o Mudar para pagesSetUpPaging.
 *
 * @TODO: AS COISAS ESTÃO MEIO BAGUNÇADAS AQUI. A INTENÇÃO É QUE 
 * A PARTE BAIXA DA MEMÓRIA VIRTURAL DO PROCESSO PERTENÇA AO PROCESSO 
 * E A PARTE ALTA DA MEMÓRIA VIRTUAL DO PROCESSO PERTENÇA AO KERNEL.
 * QUANTO A MEMÓRIA FÍSICA, DESEJAMOS QUE APENAS O KERNEL ACESSE A 
 * PARTE BAIXA DA MEMÓRIA FÍSICA, OS PROGRAMAS EM USER MODE MANIPULARÃO
 * APENAS A MEMÓRIA QUE LHES FOR CONCEDIDA.
 *
 * Histórico:
 *     2015 - Essa função foi criada por Fred Nora.
 *     2016 - Revisão.
 *     ...
 */
//int pagesSetUpPaging() 

int SetUpPaging (void){
	
    unsigned int i;
	int Index;
	
	
	//==============================================================
	//                  ****    SMALL SYSTEMS    ****
	//==============================================================
	
	unsigned long SMALL_kernel_address = SMALLSYSTEM_KERNELADDRESS;
	unsigned long SMALL_kernel_base = SMALLSYSTEM_KERNELBASE;
	unsigned long SMALL_user_address = SMALLSYSTEM_USERBASE;
	unsigned long SMALL_vga_address = SMALLSYSTEM_VGA;
	unsigned long SMALL_frontbuffer_address = (unsigned long) SavedLFB;                    //frontbuffer
	unsigned long SMALL_backbuffer_address = (unsigned long) SMALLSYSTEM_BACKBUFFER;       //backbuffer
	unsigned long SMALL_pagedpool_address = (unsigned long) SMALLSYSTEM_PAGEDPOLL_START;   //PAGED POOL
    unsigned long SMALL_heappool_address = (unsigned long) SMALLSYSTEM_HEAPPOLL_START;		
	
	unsigned long SMALL_gramadocore_init_heap_address = (unsigned long) SMALLSYSTEM_GRAMADOCORE_INIT_HEAP_START;
    unsigned long SMALL_gramadocore_shell_heap_address = (unsigned long) SMALLSYSTEM_GRAMADOCORE_SHELL_HEAP_START;
    unsigned long SMALL_gramadocore_taskman_heap_address = (unsigned long) SMALLSYSTEM_GRAMADOCORE_TASKMAN_HEAP_START;	
	//...
	
	
	//==============================================================
	//                  ****    MEDIUM SYSTEMS    ****
	//==============================================================	
	
	unsigned long MEDIUM_kernel_address = MEDIUMSYSTEM_KERNELADDRESS;
	unsigned long MEDIUM_kernel_base = MEDIUMSYSTEM_KERNELBASE;
	unsigned long MEDIUM_user_address = MEDIUMSYSTEM_USERBASE;
	unsigned long MEDIUM_vga_address = MEDIUMSYSTEM_VGA ;
	unsigned long MEDIUM_frontbuffer_address = (unsigned long) SavedLFB;
	unsigned long MEDIUM_backbuffer_address = (unsigned long) MEDIUMSYSTEM_BACKBUFFER;
	unsigned long MEDIUM_pagedpool_address = (unsigned long) MEDIUMSYSTEM_PAGEDPOLL_START; 	
    unsigned long MEDIUM_heappool_address = (unsigned long) MEDIUMSYSTEM_HEAPPOLL_START;
	
	unsigned long MEDIUM_gramadocore_init_heap_address = (unsigned long) MEDIUMSYSTEM_GRAMADOCORE_INIT_HEAP_START;	
    unsigned long MEDIUM_gramadocore_shell_heap_address = (unsigned long) MEDIUMSYSTEM_GRAMADOCORE_SHELL_HEAP_START;
    unsigned long MEDIUM_gramadocore_taskman_heap_address = (unsigned long) MEDIUMSYSTEM_GRAMADOCORE_TASKMAN_HEAP_START;	
	
	//==============================================================
	//                  ****    LARGE SYSTEMS    ****
	//==============================================================	
	
	unsigned long LARGE_kernel_address = LARGESYSTEM_KERNELADDRESS;
	unsigned long LARGE_kernel_base = LARGESYSTEM_KERNELBASE;
	unsigned long LARGE_user_address = LARGESYSTEM_USERBASE;
	unsigned long LARGE_vga_address = LARGESYSTEM_VGA;
	unsigned long LARGE_frontbuffer_address = (unsigned long) SavedLFB;
	unsigned long LARGE_backbuffer_address = (unsigned long) LARGESYSTEM_BACKBUFFER;
	unsigned long LARGE_pagedpool_address = (unsigned long) LARGESYSTEM_PAGEDPOLL_START; 	
    unsigned long LARGE_heappool_address = (unsigned long) LARGESYSTEM_HEAPPOLL_START;
	
	unsigned long LARGE_gramadocore_init_heap_address = (unsigned long) LARGESYSTEM_GRAMADOCORE_INIT_HEAP_START;	
    unsigned long LARGE_gramadocore_shell_heap_address = (unsigned long) LARGESYSTEM_GRAMADOCORE_SHELL_HEAP_START;
    unsigned long LARGE_gramadocore_taskman_heap_address = (unsigned long) LARGESYSTEM_GRAMADOCORE_TASKMAN_HEAP_START;	
	
	// ** bank 1 ** //
	// O primeiro banco representa o mínimo de memória RAM que o sistema 
	// operacional suporta, 32MB. 
	// Dentro deve conter tudo. Até cache e frames para memória paginada.
	// Endereços da memória físicas acessíveis em Kernel Mode.
	// Kernel process.
	// >> Os 4 primeiros mega da memória fisica.     
	// >> A imagem do kernel que começa no primeiro mega.
	// >> Endereços da memória físicas acessíveis em User Mode.
	// >> VGA, VESA LFB, BACKBUFFER e PAGEDPOOL
	// *Importante.
    // Esse endereço servirá para sistema de 32Mb e para sistemas com mais que 32Mb de RAM.
	// Para um sistema de 32MB a área de pagedpool deve acabar em 0x01FFFFFF.
	
	
	//=====================================================
	// A memória física é dividida em duas partes principais: 
	// + System Zone. (oito bancos de 32MB começando em 0)
	// + Window Zone. (Uma user session começando em 0x10000000)
	//
	//=====================================================	


	// O número máximo de bancos no sistema será 8.
	// Se o sistema for pequeno, teremos menos bancos.
	// Se o sistema for grande o bastante, teremos 8 bancos e uma user session.
	// Mas o sistema sempre será composto de bancos e uma user session.
	// A quantidade de bancos será contada em variáveis globais.
	
	
	//=========================================================================
	
	//
	// **** Endereços iniciais áreas de memória 'não paginada'.
	//
	
	
	// *importante:
    // ?? e se o sistema tiver 	
	
	
	//=========================================================================
	// ### importante ###
	// Essa rotina vai configurar só o deiretório de páginas do processo kernel.
	
	
	// DIRECTORY:
	//     Diretório do processo Kernel. Esse diretório já foi criado nesse 
	// endereço físico pelo Boot Loader. Aqui o kernel apenas reconfigura, 
	// utilizando a mesma localizaçao. KERNEL_PAGEDIRECTORY.
	// ??
	
	//
	// Esse valor precisa ser determinado, pois ainda não temos 
	// como usar algum alocador, pois sem a memória inicializada,
	// não temos alocador.
	//
	
	//inicializando o endereço.
	//0x0009C000;
	gKernelPageDirectoryAddress = XXXKERNEL_PAGEDIRECTORY;    
	
	// 0x0009C000
	//unsigned long *page_directory = (unsigned long *) KERNEL_PAGEDIRECTORY;         
    unsigned long *page_directory = (unsigned long *) gKernelPageDirectoryAddress; 
	
	// O que temos logo abaixo são pequenas partições de memória física.
	// cada partição tem 1024 unsigned longs. o que dá 4KB cada. 
	
	
	// TABLES: 
	//     Tabelas de páginas para o diretório do processo Kernel. Essas 
	// tabelas já foram criadas nesses endereços físicos pelo Boot Loader. 
	// Aqui o Kernel apenas reconfigura utilizando as mesmas localizações.
	
	
	// Poderíamos alocar memória para as page tables ??
	// Sim, mas precisa ser um mecanismo que devolva o endereço físico 
	// de onde foi alocado memória para a page table.
	// Na verdade deve haver uma área de memória reservada para a alocação 
	// de page tables. Todas as que serão criadas ocuparão muito espaço.

	//
	// SYSTEM MEMORY * NONPAGED POOLS 
	//
	
	//*Importante:
	// @todo: Não mudar o endereço onde essas tabelas foram construidas.
	// Esses endereços estão bem organizados, essa será o início da memória 
	// não paginada do processo kernel.
	// Todas as páginas mapeadas aqui nunca serão enviadas para a memória secundária 
	// ou seja nunca mudarão de endereço físico.
	//
	// 0x0008F000 Tabela para mapear a parte mais baixa da memória física. Começa em 0.
	// 0x0008E000 Tabela para mapear a memória usada pela imagem do kernel. Começa em 0x100000.
	// 0x0008D000 Tabela para mapear uma área em user mode onde rodam códigos. Começa em 0x400000.
	// 0x0008C000 Tabela para mapear a vga. Começa em 0xb8000.
	// 0x0008B000 Tabela para mapear o frontbuffer, O começo é passado pelo Boot.
	// 0x0008A000 Tabela para mapear o backbuffer, o começo é em (0x01000000 - 0x400000) no small system.
	// 0x00089000 Tabela de páginas para o pagedpool.
	
	//kernel mode. (Endereços). 
	unsigned long *km_page_table = (unsigned long *) PAGETABLE_KERNELAREA; //0x0008F000;  
 
	//kernel mode. (O kernel).
    unsigned long *km2_page_table = (unsigned long *) PAGETABLE_KERNELBASE; //0x0008E000;   

	//user mode.
	unsigned long *um_page_table = (unsigned long *) PAGETABLE_USERBASE; //0x0008D000;   

	//user mode. (vga).
	unsigned long *vga_page_table = (unsigned long *) PAGETABLE_VGA; //0x0008C000;   

	//user mode. (LFB).
	unsigned long *frontbuffer_page_table = (unsigned long *) PAGETABLE_FRONTBUFFER; //0x0008B000;   

	//user mode. (buffer). backbuffer ??
    unsigned long *backbuff_page_table = (unsigned long *) PAGETABLE_BACKBUFFER; //0x0008A000; 
	
    //pagetable para o pagedpool
	unsigned long *pagedpool_page_table = (unsigned long *) PAGETABLE_PAGEDPOOL; //0x00089000;  
	
	//um endereço físico para a pagetable que mapeará os buffers.
	unsigned long *heappool_page_table = (unsigned long *) PAGETABLE_HEAPPOOL; 
	
	//#importante.
	//Especiais esclusivo para o ambiente gramado core.
	unsigned long *gramadocore_init_page_table = (unsigned long *) PAGETABLE_GRAMADOCORE_INIT_HEAP; 
	unsigned long *gramadocore_shell_page_table = (unsigned long *) PAGETABLE_GRAMADOCORE_SHELL_HEAP; 
	unsigned long *gramadocore_taskman_page_table = (unsigned long *) PAGETABLE_GRAMADOCORE_TASKMAN_HEAP; 
	
	//...

	//
	// SYSTEM MEMORY * PAGED POOLS 
	//

	//@criaremos por enquanto apenas uma pagetable com memória paginada.
    //unsigned long *paged_page_table = (unsigned long *) ??;  //BUFFER_PAGETABLE.	
	
	
    //
	// Message. (verbose).
#ifdef MK_VERBOSE	
	printf("SetUpPaging: Initializing Pages..\n");
#endif
	
	//
	//  **  DIRECTORIES **
	//

	// Preenchendo todo o diretório de páginas do kernel com páginas não 
	// presentes. Usando um endereço nulo de página.

	// Inicializando quatro diretórios.
	// o bit 7 da entrada permanece em 0, indicando que temos páginas de 4KB.
	// kernel
	// Diretório de páginas do processo kernel.
	// 0 no bit 2 indica qual level ??
	// 010 em binário.
	
	for ( i=0; i < 1024; i++ ){

	    // #importante:	
		// O endereço físico e virtual são iguais para essa tabela.
		page_directory[i] = (unsigned long) 0 | 2;    
		
	};
	
	
	//
	//  ** PAGE TABLE, KERNEL AREA **
	//

	//===========================================================
	// kernel mode pages (0fis = 0virt)
	// SMALL_kernel_address = 0.
	// Mapear os primeiros 4MB da memória. (kernel mode). Preenchendo a tabela 
	// km_page_table. A entrada 0 do diretório refere-se aos primeiros 4 megas 
	// de endereço virtual.
	//
    // Aqui estamos pegando uma partição de memória física de 4MB que começa no 
	// início da memória RAM.
    // Obs: Essa page table dá acesso aos primeiros 4MB da memória física,
	// Isso inclu a área do kernel base que começa no primeiro MB. Manipular
	// esse espaço pode corromper o kernel base.
	//
	// A intenção aqui é que o kernel base possa manipular as áreas baixas da 
	// memória física com facilidade. Porém, para os outros processos, os endereços 
	// lógicos mais baixos não devem corresponder aos endereços físicos mais baixos,
	// por segurança, apenas o kernel base deve ter acesso à essa área.
	// Para alguns processos especiais, algum tipo de permissão poderá ser concedida.
	//
    
	
	// Configurando uma pagetable.
	// a pagetable para os primeiros 4MB de memória física. 
	// kernel mode pages (0fis = 0virt)
	//011 binário.
	//kernel
	//Criando a entrada número '0' do diretório de páginas do processo Kernel.
	//que apontará para a pagetable que criamos.
	//o bit 7 da entrada permanece em 0, indicando que temos páginas de 4KB.
	//Salva no diretório o endereço físico da tabela.
	//Configurando os atributos.	
	
	mm_used_kernel_area = (1024 * 4);  // 4096 KB = (4 MB).
		
	for ( i=0; i < 1024; i++ ){
		
		// #importante:	
		// O endereço físico e virtual são iguais para essa tabela.
		km_page_table[i] = (unsigned long) SMALL_kernel_address | 3;     
	    SMALL_kernel_address = (unsigned long) SMALL_kernel_address + 4096;  
    };
	
    page_directory[ENTRY_KERNELMODE_PAGES] = (unsigned long) &km_page_table[0];      
    page_directory[ENTRY_KERNELMODE_PAGES] = (unsigned long) page_directory[ENTRY_KERNELMODE_PAGES] | 3;  
	
	
	//
	//  ** PAGE TABLE, KERNEL BASE **
	//
	
	//===============================================
	// kernel mode pages (0x00100000fis = 0xC0000000virt)
	// SMALL_kernel_base = 0x00100000 = KERNEL_BASE.
	// Mapear 4MB começando do primeiro mega. (kernel mode).
	// Preenchendo a tabela km2_page_table.
	//
    // Aqui estamos pegando uma partição de memória física de 4MB que começa no
	// endereço físico que carregamos a imagem do kernel.
    // são 4MB de memória física, começando do primeiro MB, onde o KERNEL.BIN 
    // foi carregado.	
    //	

	// Criando uma pagetable.
    // 4MB de memória física, começando em 1MB.
    // kernel mode pages (0x00100000fis = 0xC0000000virt)	
	// 011 binário.
	//kernel
	// Criando a  entrada do diretório de páginas do processo kernel.
	//o bit 7 da entrada permanece em 0, indicando que temos páginas de 4KB.
	//Salva no diretório o endereço físico.
	//Configurando os atributos.
	
    for ( i=0; i < 1024; i++ ){

	    // #importante:	
		// O endereço físico e virtual são iguais para essa tabela.
		km2_page_table[i] = (unsigned long) SMALL_kernel_base | 3;     
	    SMALL_kernel_base = (unsigned long) SMALL_kernel_base + 4096;  
    };
	
    page_directory[ENTRY_KERNELBASE_PAGES] = (unsigned long) &km2_page_table[0];       
    page_directory[ENTRY_KERNELBASE_PAGES] = (unsigned long) page_directory[ENTRY_KERNELBASE_PAGES] | 3;  


    // Obs: Percebe-se que houve uma sobreposição. Os megas 0,1,2,3 para
	// kernel mode e os megas 1,2,3,4 para o kernel base.
	// Isso significa que o Kernel Base pode acessar o primeiro mega
	// da memória física, usando endereço virtual igual ao endereço físico.
	
	//
	//    ** PAGETABLE, USER BASE **
	//
	
	//===================================================================
	// user mode pages - (0x00400000fis = 0x00400000virt)
	// SMALL_user_address = 0x00400000 = USER_BASE.
	// Mapear 4MB da memória começando em 0x00400000fis. (user mode).
	//
	//
    // Aqui estamos pegando uma partição de memória física de 4MB que começa no
	// endereço físico 0x00400000, no quarto mega da memória física. 
    //
    // É nesse endereço lógico que ficarão os processos em user mode.
	// Cada processo terá um diretório de páginas, e nesse diretório de 
	// páginas terá uma page table que atribuirá o endereço lógico de 0x400000
	// à algum endereço físico alocado dinâmicamente para receber a imagem do processo.
	// Obs: Se o processo tiver mais que 4MB de tamanho, então será preciso 
    // de mais de uma pagetable.
    //
    // Obs: 
	// HACK HACK. No momento, nessa pagetable do diretório do processo kernel, existem 
    // três imagens carregadas nessa mesma área de memória, compilados em endereços 
    // absolutos diferentes. (Idle, Taskman e Shell). Mas queremos que todos os 
    // processos de usuário utilizem o mesmo endereço lógico. 0x400000.	
	//
	
	//Criando uma pagetable.
	//4MB de memória física, começando do querto mega.
	// user mode pages - (0x00400000fis = 0x00400000virt)
	//será usado pelo processo em user mode. Note as flags.(7).
	//7 decimal é igual a 111 binário.
    //kernel 	
    // Criando a entrada do diretório de páginas do processo kernel.
	//o bit 7 da entrada permanece em 0, indicando que temos páginas de 4KB.
	//Salva no diretório o endereço físico.
	//Configurando os atributos.
	
	mm_used_user_area = (1024 * 4);  // 4096 KB = (4 MB).
	
	for ( i=0; i < 1024; i++ ){
		
		// #importante:	
		// O endereço físico e virtual são iguais para essa tabela.
		um_page_table[i] = (unsigned long) SMALL_user_address | 7;     
	    SMALL_user_address = (unsigned long) SMALL_user_address + 4096; 
    };
	
    page_directory[ENTRY_USERMODE_PAGES] = (unsigned long) &um_page_table[0];      
    page_directory[ENTRY_USERMODE_PAGES] = (unsigned long) page_directory[ENTRY_USERMODE_PAGES] | 7; 
	
	
    // Obs: Novamente aqui há uma sobreposição. O primeiro mega
	// dessa área destinada à user mode, é o mesmo último mega da
    // área destinada ao Kernel Base. Isso significa uma área de memória
    // compartilhada. O que está no primeiro mega dessa área em user mode
	// também está no último mega da área do kernel base.
	  
	  
	//
    // ** PAGE TABLE, VGA **
    //	
	  
    //==============================================================
	// user mode VGA pages - ( 0x000B8000fis = 0x00800000virt)
	// SMALL_vga_address  = VM_BASE;   //0x000B8000;
	// Mapear 4MB da memória começando em 0x000B8000fis. (user mode).
	// @todo: Aqui na verdade não precisa configurar 4 megas, 
	//        apenas o tamanho da memória de vídeo presente em 0xb8000.
	//
    // Aqui estamos pegando uma partição de memória física de 4MB que começa no
	// endereço físico 0x000B8000.
    // @todo: bugbug: ESSA É CGA E NÃO A VGA.
    //Mudar o nome para cga.	
    //	
    
    // Criando uma pagetable.
    // 4MB de memória física, começando 0x000B8000fis.
    // user mode VGA pages - ( 0x000B8000fis = 0x00800000virt)
    // Podemos permitir que alguns processos em user mode acessem
    // essa área diretamente.
    // 7 decimal é igual a 111 binário.
    // kernel
	// Criando a entrada do diretório de páginas do processo kernel.
	// o bit 7 da entrada permanece em 0, indicando que temos páginas de 4KB.
	// Salva no diretório o endereço físico.
	// Configurando os atributos.
	
    for ( i=0; i < 1024; i++ ){
		
	    // #importante:	
		// O endereço físico e virtual são iguais para essa tabela.
		vga_page_table[i] = (unsigned long) SMALL_vga_address | 7;     
	    SMALL_vga_address = (unsigned long) SMALL_vga_address + 4096;  
    };

    page_directory[ENTRY_VGA_PAGES] = (unsigned long) &vga_page_table[0];     
    page_directory[ENTRY_VGA_PAGES] = (unsigned long) page_directory[ENTRY_VGA_PAGES] | 7;  

	
	// Obs: 4MB começando do endereço físico 0x000B8000, são acessíveis
	// em user mode à partir do endereço virtual 0x00800000virt.
	
	//
	// ** PAGETABLE, FRONT BUFFER  **
	//
	
	g_frontbuffer_va = (unsigned long) FRONTBUFFER_ADDRESS; //0xC0400000;        
	
	
    //==================================================================
	// user mode LFB pages - (0x????????fis = 0xC0400000virt).
	// SMALL_frontbuffer_address  = SavedLFB = g_lbf_pa, Foi passado pelo boot manager.
	// Mapear 4MB da memória física começando no valor do endereço físico 
	// do LFB que foi passado pelo Boot Manager.
	// O endereço de memória lógica utilizada é 4MB à partir de 0xC0400000.
	//
    // Aqui estamos pegando uma partição de memória física de 4MB que começa no
	// endereço físico do LFB, de valor desconhecido. Foi configurado em modo real. 
    // pelo método VESA.
    //	
	// @todo: LFB needs to be bigger. (Ex: Four 8GB graphic cards).
    //        But the driver needs to do all the work.
    //
	
	
	
	// Criando uma pagetable. (user mode)
	// Os quatro primeiros MB da memória de vídeo.
	// user mode LFB pages - (0x????????fis = 0xC0400000virt).
	// provavelmente o endereço físico é 0xE0000000
	// 7 decimal é igual a 111 binário.
	// kernel
	// Criando a entrada do diretório de páginas do processo kernel.
	// o bit 7 da entrada permanece em 0, indicando que temos páginas de 4KB.
	// Salva no diretório o endereço físico.
	// Configurando os atributos.
		
	 mm_used_lfb = (1024 * 4);  // 4096 KB = (4 MB).
	
    for ( i=0; i < 1024; i++ ){

		// #importante:	
		// O endereço físico e virtual são iguais para essa tabela.
		frontbuffer_page_table[i] = (unsigned long) SMALL_frontbuffer_address | 7;     
	    SMALL_frontbuffer_address = (unsigned long) SMALL_frontbuffer_address + 4096;  
    };
	
    page_directory[ENTRY_FRONTBUFFER_PAGES] = (unsigned long) &frontbuffer_page_table[0];       
    page_directory[ENTRY_FRONTBUFFER_PAGES] = (unsigned long) page_directory[ENTRY_FRONTBUFFER_PAGES] | 7;  	
	
	
	//
	// ** PAGETABLE, BACKBUFFER **
	//
	
	g_backbuffer_va = (unsigned long) BACKBUFFER_ADDRESS; //0xC0800000; 
	
    //===============================================================
	// user mode BUFFER1 pages - 0x800000fis = (0x01000000 - 0x800000 fis) = 0xC0800000virt).
	// ***BackBuffer: 
	//     É o buffer onde se pinta o que aparecerá na tela. O conteúdo 
	// desse buffer é copiado no LFB da memória de vídeo, (refresh_screen).
    // SMALL_backbuffer_address = , #Provisório.	
	// O endereço de memória lógica utilizada é 4MB à partir de 0xC0800000.
	//
    // Aqui estamos pegando uma partição de memória física de 4MB que começa no
	// endereço físico , no decimo sexto mega da memória física. 
    //	

    // criando uma page table.
	// 4MB de meória física, começando em 16MB, que serão usados 
	// para backbuffer. Obs essa área deve ter o mesmo tamanho do frontbuffer.
	// user mode BUFFER1 pages - ((0x01000000 - 0x800000 fis) = 0xC0800000virt).
	// 7 decimal é igual a 111 binário.	
	// kernel
    // Criando a entrada do diretório de páginas do processo kernel.
	// o bit 7 da entrada permanece em 0, indicando que temos páginas de 4KB.
	// Salva no diretório o endereço físico.
	// Configurando os atributos.
	
    mm_used_backbuffer = (1024 * 4);  // 4096 KB = (4 MB).
	
    for ( i=0; i < 1024; i++ ){
		
	    // #importante:	
		// O endereço físico e virtual são iguais para essa tabela.
		backbuff_page_table[i] = (unsigned long) SMALL_backbuffer_address | 7;     
	    SMALL_backbuffer_address = (unsigned long) SMALL_backbuffer_address + 4096;  
    };
	
    page_directory[ENTRY_BACKBUFFER_PAGES] = (unsigned long) &backbuff_page_table[0];      
    page_directory[ENTRY_BACKBUFFER_PAGES] = (unsigned long) page_directory[ENTRY_BACKBUFFER_PAGES] | 7;  	


	// Obs: 4MB da memória física à partir do endereço físico 0x01000000 (16MB)
    // são destinados ao back buffer. Obs: Isso é bem pouco, uma tela com alta 
	// resolução usa mais que isso.	
	
	
	//
	// ** PAGETABLE, PAGEDPOOL **
	//	
	
	g_pagedpool_va = (unsigned long) XXXPAGEDPOOL_VA;  //0xC0C00000;
	
	// (user mode)
	// 7 decimal é igual a 111 binário.	
	// kernel
    // Criando a entrada do diretório de páginas do processo kernel.
	// o bit 7 da entrada permanece em 0, indicando que temos páginas de 4KB.
	// Salva no diretório o endereço físico.
	// Configurando os atributos.
	
	mm_used_pagedpool = (1024 * 4);  // 4096 KB = (4 MB).
	
	for ( i=0; i < 1024; i++ ){
		
	    
		// #importante:	
		// O endereço físico e virtual são iguais para essa tabela.
		pagedpool_page_table[i] = (unsigned long) SMALL_pagedpool_address | 7;     
	    SMALL_pagedpool_address = (unsigned long) SMALL_pagedpool_address + 4096;  
    };

    page_directory[ENTRY_PAGEDPOOL_PAGES] = (unsigned long) &pagedpool_page_table[0];      
    page_directory[ENTRY_PAGEDPOOL_PAGES] = (unsigned long) page_directory[ENTRY_PAGEDPOOL_PAGES] | 7;  	

	
    // endereço virtual do pool de heaps.
    // os heaps nessa área serão dados para os processos.	
	g_heappool_va = (unsigned long) XXXHEAPPOOL_VA; //0xC1000000;
	g_heap_count = 0;
	g_heap_count_max = G_DEFAULT_PROCESSHEAP_COUNTMAX;
	g_heap_size = G_DEFAULT_PROCESSHEAP_SIZE;
	
	//heaps suppport
	//preparando uma área de memória grande o bastante 
	//para conter o heap de todos os processos.
	//ex: podemos dar 128kb para cada processo inicialmente.

    mm_used_heappool = (1024 * 4);  // 4096 KB = (4 MB).
	
	for ( i=0; i < 1024; i++ ){
		
	    // #importante:	
		// O endereço físico e virtual são iguais para essa tabela.
		heappool_page_table[i] = (unsigned long) SMALL_heappool_address | 7;     
	    SMALL_heappool_address = (unsigned long) SMALL_heappool_address + 4096;  
    };

    page_directory[ENTRY_HEAPPOOL_PAGES] = (unsigned long) &heappool_page_table[0];      
    page_directory[ENTRY_HEAPPOOL_PAGES] = (unsigned long) page_directory[ENTRY_HEAPPOOL_PAGES] | 7;  	
	
	
	
	//+++++++
	//gramado core init heap 
	g_gramadocore_init_heap_va = (unsigned long) XXXGRAMADOCORE_INIT_HEAP_VA; //0xC1400000;
	g_gramadocore_init_heap_size = G_DEFAULT_GRAMADOCORE_INIT_HEAP_SIZE;  //4MB

	mm_used_gramadocore_init_heap = (1024 * 4);  // 4096 KB = (4 MB).
	
	for ( i=0; i < 1024; i++ ){
		
	    // #importante:	
		// O endereço físico e virtual são iguais para essa tabela.
		gramadocore_init_page_table[i] = (unsigned long) SMALL_gramadocore_init_heap_address | 7;     
	    SMALL_gramadocore_init_heap_address = (unsigned long) SMALL_gramadocore_init_heap_address + 4096;  
    };

    page_directory[ENTRY_GRAMADOCORE_INIT_PAGES] = (unsigned long) &gramadocore_init_page_table[0];      
    page_directory[ENTRY_GRAMADOCORE_INIT_PAGES] = (unsigned long) page_directory[ENTRY_GRAMADOCORE_INIT_PAGES] | 7;  		
	
	
	
	//+++++++
	//gramado core shell heap 
	g_gramadocore_shell_heap_va = (unsigned long) XXXGRAMADOCORE_SHELL_HEAP_VA; //0xC1800000;
	g_gramadocore_shell_heap_size = G_DEFAULT_GRAMADOCORE_SHELL_HEAP_SIZE;  //4MB

	mm_used_gramadocore_shell_heap = (1024 * 4);  // 4096 KB = (4 MB).
	
	for ( i=0; i < 1024; i++ ){
		
	    // #importante:	
		// O endereço físico e virtual são iguais para essa tabela.
		gramadocore_shell_page_table[i] = (unsigned long) SMALL_gramadocore_shell_heap_address | 7;     
	    SMALL_gramadocore_shell_heap_address = (unsigned long) SMALL_gramadocore_shell_heap_address + 4096;  
    };

    page_directory[ENTRY_GRAMADOCORE_SHELL_PAGES] = (unsigned long) &gramadocore_shell_page_table[0];      
    page_directory[ENTRY_GRAMADOCORE_SHELL_PAGES] = (unsigned long) page_directory[ENTRY_GRAMADOCORE_SHELL_PAGES] | 7;  		
	


	//+++++++
	//gramado core taskman heap 
	g_gramadocore_taskman_heap_va = (unsigned long) XXXGRAMADOCORE_TASKMAN_HEAP_VA; //0xC1C00000;
	g_gramadocore_taskman_heap_size = G_DEFAULT_GRAMADOCORE_TASKMAN_HEAP_SIZE;  //4MB

	mm_used_gramadocore_taskman_heap = (1024 * 4);  // 4096 KB = (4 MB).
	
	for ( i=0; i < 1024; i++ ){
		
	    // #importante:	
		// O endereço físico e virtual são iguais para essa tabela.
		gramadocore_taskman_page_table[i] = (unsigned long) SMALL_gramadocore_taskman_heap_address | 7;     
	    SMALL_gramadocore_taskman_heap_address = (unsigned long) SMALL_gramadocore_taskman_heap_address + 4096;  
    };

    page_directory[ENTRY_GRAMADOCORE_TASKMAN_PAGES] = (unsigned long) &gramadocore_taskman_page_table[0];      
    page_directory[ENTRY_GRAMADOCORE_TASKMAN_PAGES] = (unsigned long) page_directory[ENTRY_GRAMADOCORE_TASKMAN_PAGES] | 7;  		

	
	
    //...
	
	
	//
	//   #### Importante ####
	//
	
	// Agora vamos calcular a quantidade de memória física usada até agora.
	// Levando em conta a inicialização que fizemos nessa rotina.
	
	// Estamos deixando de fora a memória dos dispositivos, pois a memória
	// usada pelos dispositivos possuem endereço físico, mas está na parte alta 
	// do endereçamento físico, muito alem da memória RAM instalada.
	// Com a exceção da vga, que fica antes de 1MB.
	// Os dispositivos por enquanto são memória de vídeo e placa de rede.
	
    memorysizeUsed = (unsigned long) ( mm_used_kernel_area + 
		mm_used_user_area + 
		mm_used_backbuffer + 
		mm_used_pagedpool + 
		mm_used_heappool + 
		mm_used_gramadocore_init_heap +
		mm_used_gramadocore_shell_heap +
		mm_used_gramadocore_taskman_heap );
			
    memorysizeFree = memorysizeTotal - memorysizeUsed;

	
	
	// @todo:  
	// (sobre heaps para processos em user mode).
	// O que precisa ser feito no momento:
	// + Os processos em user mode precisam alocação dinâmica de memória, 
	// para isso será usado o heap do processo ou o heap do desktop ao qual o 
	// processo pertence.
	//
	//@todo:
	// *IMPORTANTE: 
	// (sobre heaps para gerenciamento de recursos gráficos).
	// + Os buffers de janela serão alocados no heap do processo em user mode 
	// que gerencia a criação de janelas, portanto esse processo tem que ter 
	// bastante heap disponível. Talvez quem faça esse papel seja o próprio 
	// kernel base, aí quem precisa de bastante heap é o kernel base.
	// Talvez seja um módulo em kernel mode que gerencie as janelas.
	// Por enquanto é a camada superior do kernel base. Mas interfaces poderão
	// chamar essa camada no kernel base e oferecerem serviços de gerenciamento
	// de recursos gráficos, utilizando apenas as primitivas oferecidas pelo 
	// kernel base. Essas bibliotecas que oferecem recursos gráficos podem 
	// ser processos em kernel mode ou em user mode. Elas oferecerão recursos 
	// bem elaborados e completos, chamando o kernel base apenas para 
	// as rotinas primitivas. Isso facilita a criação de recursos gráficos,
	// porém prejudica o desempenho, por isso o kernel base também oferece 
	// seu conjunto de recursos gráficos mais elaborados, além das primitivas,
	// é claro.


	// @todo: 
	// Continuar: Mais páginas podem ser criadas manualmente agora.
	// Porem a intenção é utilizar rotinas de automação da criação 
	// de paginas, pagetable e diretórios.


	// @todo: 
	// Até agora tem uma sobreposição danada no mapeamento um mesmo 
	// endereço físico de memória é mapeado para vários endereços virtuais. 
	// Isso não é proibido, é assim que se comaprtilha memória. Na prática
	// podemos acessar a mesma região de memória de várias maneira diferentes.
	// Mas devemos tomar cuidado, principalmente para não corrompermos o 
	// kernel base.
	// O acesso a memória compartilhada será gerenciado pelos mecanismos
	// padrão de comunicação e compartilhamento. Semáforos e mutexes ...


	// @todo: 
	// *IMPORTANTE.
	// O que queremos é utilizar uma lista de frames livres na hora
	// configurarmos o mapeamento. Queremos pegar um frame livre e
	// associarmos ele com uma PTE, (entrada na tabela de páginas).
	// O que está faltando é o gerenciamento de memória física.
	// O gerenciamento de memória física é feito dividindo a memória física 
	// em partições, pedaços grandes de memória. Tem um módulo que trata
	// de bancos, aspaces no kernel base.
	
	
	// @todo:
	// *SUPER IMPORTANTE.
	// para gerenciarmos a meória física, precisamos saber o tamanho 
	// da memória física disponpivel. tem um módulo no kernel base 
	// que trata disso.
	// * Depois de alocarmos uma região grande da memória física,
	// destinada para frames, então criaremos a lista de frames livres.
	// que significará uma quantidade de frames livres dentro da área 
	// destinadas à frames. Não significa área toda a área livre
	// na memória física, mas apenas os frames livres dentro da região 
	// destinada aos frames.

	// Debug:
	//     Mostrando os endereços do diretório e das páginas.
	//     #verbose.

	
#ifdef MK_VERBOSE	
	printf("Debug:\n");
	printf("Configurando CR3={%x}\n", (unsigned long) &page_directory[0]);
	printf("Page={%x} \n", (unsigned long) &km_page_table[0]);
	printf("Page={%x} \n", (unsigned long) &km2_page_table[0]);
	printf("Page={%x} \n", (unsigned long) &um_page_table[0]);
	printf("Page={%x} \n", (unsigned long) &vga_page_table[0]);
	printf("Page={%x} \n", (unsigned long) &frontbuffer_page_table[0]);
	printf("Page={%x} \n", (unsigned long) &backbuff_page_table[0]);
	printf("Page={%x} \n", (unsigned long) &pagedpool_page_table[0]);
	//refresh_screen();
	//while(1){};
#endif

	// Obs: 
	// Podemos reaproveitas pagetables em diferentes processos.

	// CR3:
	// Salvando o endereço do diretório do processo Kernel no CR3. O diretório 
	// do processo Kernel está agora dentro de uma área protegida. Está em 
	// kernel mode.  
	// Obs: Será rotineiro configurar isso cada vez que um processo for 
	// executar ou for criado.
	// Obs: Quando se troca o valor do cr3, a TLB é atualizada pra todas 
	// as entradas. (?? automático)

	SetCR3 ( (unsigned long) &page_directory[0] );

	//Debug:
	//refresh_screen();
	//while(1){}


    // LISTAS:
	//    Configurando a lista de diretórios e 
	//    a lista de tabelas de páginas.
	//    Salvando na lista o endereço físico dos
	// diretórios e das tabelas de páginas.

    //
	// Inicializar a lista de diretórios de páginas.
	// 
	
	for ( Index=0; Index < PAGEDIRECTORY_COUNT_MAX; Index++ ){
		
	    pagedirectoryList[Index] = (unsigned long) 0;
	};

	//O primeiro diretório da lista é o diretório do kernel.
	pagedirectoryList[0] = (unsigned long) &page_directory[0];          //kernel.
	//pagedirectoryList[1] = (unsigned long) &idle_page_directory[0];     //idle.
	//pagedirectoryList[2] = (unsigned long) &shell_page_directory[0];    //shell.
	//pagedirectoryList[3] = (unsigned long) &taskman_page_directory[0];  //taskman.	
    //pagedirectoryList[4] = (unsigned long) 0;
    //pagedirectoryList[5] = (unsigned long) 0;	
    //...


	//
	// Inicializando a lista de pagetables..
	//
	
	for ( Index=0; Index < PAGETABLE_COUNT_MAX; Index++ ){
		
	    pagetableList[Index] = (unsigned long) 0;
	};

    //Configurando manualmente as primeiras entradas da lista.
	pagetableList[0] = (unsigned long) &km_page_table[0];
	pagetableList[1] = (unsigned long) &km2_page_table[0];
	pagetableList[2] = (unsigned long) &um_page_table[0];
	pagetableList[3] = (unsigned long) &vga_page_table[0];
	pagetableList[4] = (unsigned long) &frontbuffer_page_table[0];
	pagetableList[5] = (unsigned long) &backbuff_page_table[0];
	//pagetableList[6] = (unsigned long) 0;
    //...


	//
	// Inicializando a lista de framepools. (partições)
	//
	
	for ( Index=0; Index < FRAMEPOOL_COUNT_MAX; Index++ ){
		
	    framepoolList[Index] = (unsigned long) 0;
	};

	//Configurando manualmente a lista de pageframes.
	framepoolList[0] = (unsigned long) 0;
	framepoolList[1] = (unsigned long) 0;
	//...


	//
	// Creating "Kernel Space Framepool". 
	//

	struct frame_pool_d *kfp;

	//kernel framepool.
	kfp = (void *) malloc ( sizeof(struct frame_pool_d) );
	
	if ( (void *) kfp != NULL  )
	{
		kfp->id = 0;
		
		kfp->used = 1;
		kfp->magic = 1234;
		
		//?? Começa em 0 MB. ??
		kfp->address = (unsigned long) (0 * MB);   
		
		//pertence ao processo kernel.
		kfp->process = (void *) KernelProcess;
		
		kfp->next =  NULL;
		//...

		//salva e ponteiro global.
		framepoolKernelSpace = (void *) kfp;

		//Salva na lista.
		framepoolList[0] = (unsigned long) kfp;
	};


    //
	// Creating user space framepool for small systems.
	//

	struct frame_pool_d *small_fp;

	//kernel framepool.
	small_fp = (void *) malloc ( sizeof(struct frame_pool_d) );
	
	if( (void *) small_fp != NULL  )
	{
		small_fp->id = 1;
		
		small_fp->used = 1;
		small_fp->magic = 1234;
		
		//Começa em 4 MB.
		small_fp->address = (unsigned long) (4 * MB);   

		//pertence ao processo kernel.
		small_fp->process = (void*) NULL; //??;

		small_fp->next =  NULL;
		//...

		//salva e ponteiro global.
		framepoolSmallSystemUserSpace = (void *) small_fp;

		//Salva na lista.
		framepoolList[1] = (unsigned long) small_fp;
	};


   //@todo: Outros indices, (2,3,4.)
   
	//Obs: Tem um buffer em  0x01000000 (16MB).
	//...

	//
	// Creating pageble space framepool.
	//

	struct frame_pool_d *pageable_fp;
	
	//kernel framepool.
	pageable_fp = (void *) malloc ( sizeof(struct frame_pool_d) );
	
	if( (void *) pageable_fp != NULL  )
	{
		pageable_fp->id = 5;   //quinto índice.
		
		pageable_fp->used = 1;
		pageable_fp->magic = 1234;
		
		//Começa em 20 MB.
		pageable_fp->address = (unsigned long) (20 * MB);   

		//pertence ao processo kernel.
		pageable_fp->process = (void*) NULL; //??
		
		pageable_fp->next =  NULL;
		//...

		//salva em ponteiro global.
		framepoolPageableSpace = (void*) pageable_fp;

		//Salva na lista.
		framepoolList[5] = (unsigned long) pageable_fp;
	};
	
	//
	// More?!
	//

// Done.
//done:
	
#ifdef MK_VERBOSE
	printf("Done\n");
#endif	
	
    return 0;
}


/*
 * initializeFramesAlloc:
 *     Inicializa o framepool. */

void initializeFramesAlloc (void){
	
	int Index;
	struct page_d *p;
	
	//
	// Inicializando a lista de pages.
	//
	
	for ( Index=0; Index < PAGE_COUNT_MAX; Index++ )
	{	
	    pageAllocList[Index] = (unsigned long) 0;
	};
	
	
	//
	// Criando o primeiro para testes.
	//
	
	p = (void *) malloc ( sizeof( struct page_d ) );
	
	if ( p == NULL )
	{
		printf("initializeFramesAlloc:\n");
		return;
		//goto done;
	}else{
		
	    p->id = 0;
	
	    p->used = 1;
	    p->magic = 1234;
	
	    p->free = 0;  //not free
	    p->next = NULL; 
	    //...	
	
	    pageAllocList[0] = ( unsigned long ) p; 		
	};	
}



/*
 ***********************************************
 * allocPages:
 *
 * @param número de páginas contíguas.
 * Obs: Pode ser que os pageframes não sejam 
 * contíguos mas as páginas serão.
 * estamos usando uma page table toda já mapeada. 4MB.
 * @TODO: ESSA ROTINA ESTÁ INCOMPLETA ... REVISAR. #bugbug
 *
 * #bugbug: se estamos lidando com o endereço base vitual, então estamos 
 * lidando com páginas pre alocadas e não pageframes.
 */

void *allocPages ( int size ){
	
	int Index;
	
	//página inicial da lista
	struct page_d *Ret;   
	
	struct page_d *Conductor;
	struct page_d *p;
	
	//Esse é o endereço virtual do início do pool de pageframes.
	unsigned long base = (unsigned long) g_pagedpool_va;
	
	unsigned long va;
    unsigned long pa;
	
	int Count = 0;
	
	//
	// Checando limites.
	//
	
#ifdef MK_VERBOSE
    printf("allocPageFrames: Initializing ...\n");	
#endif

	//problemas com o size.
	if(size <= 0)
	{
		//if debug
		printf("allocPageFrames: size 0\n");
		return NULL;
	};
			
    //Se é pra alocar apenas uma página.
	if (size == 1)
	{		
		return (void *) newPage ();	
	}	
	
	//se o size for maior que o limite.
    if ( size > PAGE_COUNT_MAX )
	{
		//if debug
		printf("allocPageFrames: size limits\n");
		goto fail;
	}
	
	
	//
	// Isso encontra slots o suficiente para alocarmos tudo o que queremos.
	//
	
	int Base;
	
	Base = firstSlotForAList (size);
	
	if ( Base == -1 )
	{
		printf("Base = -1 \n");
		goto fail;
	}
	
#ifdef MK_VERBOSE	
    printf("allocPageFrames: for ...\n");		
#endif 
 
	//começamos a contar do frame logo após o condutor.
	
	for (Index = Base; Index < (Base+size+1); Index++ )
	{
	    p = (void *) pageAllocList[Index];
				
		//Slot livre
		if ( p == NULL )
		{
			//#bugbug
			//Isso pode esgotar o heap do kernel
			
			p = (void *) malloc ( sizeof( struct page_d ) );
			
			if ( p == NULL )
			{
				printf("allocPageFrames: 2\n");
				goto fail;
			};
			
			//printf("#");
			p->id = Index;
			
			p->used = 1;
			p->magic = 1234;
			
			//not free
			p->free = 0;  

			//----
			
			p->locked = 0;
			
			//contador de referências
			p->ref_count = 1;	
			
			//pegando o endereço virtual.
			va = (unsigned long) ( base + (p->id * 4096) );    
			pa = (unsigned long) virtual_to_physical ( va, gKernelPageDirectoryAddress ); 
			
	
			if ( ( pa % PAGE_SIZE) != 0 ) 
			{		
			    pa = pa - ( pa % PAGE_SIZE);			
			}	 	
			
			p->frame_number = (pa / PAGE_SIZE);
			
			if ( pa == 0 )
			{
			    p->frame_number = 0;
			}
			
			//---
			
			pageAllocList[Index] = ( unsigned long ) p; 
			
			Conductor->next = (void *) p;
			Conductor = (void *) Conductor->next;
			
			Count++;
			if( Count >= size )
			{
				Ret = (void *) pageAllocList[Base];
			    goto done;	
			}	
		};
	};
	
fail:
    printf("allocPageFrames: fail \n");		
    return NULL;	
done:
    //printf("allocPageFrames: done ...\n");	
    
	//*Importante:
	//retornaremos o endereço virtual inicial do primeiro pageframe da lista.
	return (void *) ( base + (Ret->id * 4096) );
}


//checar se a estrutura de p'agina é nula
int pEmpty (struct page_d *p){
	
    return p == NULL ? 1 : 0;
};


//selecionar a página como livre.
void freePage (struct page_d *p){
	
	if (p == NULL){
		return;  //fail	
	}
	    
    if( p->used == 1 && p->magic == 1234 )
	{
	    p->free = 1;
	}		
}


//selecionar a página como não livre.
void notfreePage (struct page_d *p){
	
	if(p == NULL){
		return;  //fail	
	}
	    
	//check
    if( p->used == 1 && p->magic == 1234 )
	{
	    p->free = 0;
	}		
}


/*
 ***************************************************************
 * firstSlotForAList:
 *     Retorna o primeiro índice de uma sequência de slots livres 
 * em pageAllocList[].
 */

int firstSlotForAList ( int size ){
	
	int Index;
	int Base = 0;
	int Count = 0;
    void *slot;
	
tryAgain:
	
	for ( Index=Base; Index < 1024; Index++ )
	{
	    slot = (void *) pageAllocList[Index];
		
		if ( (void *) slot != NULL )
		{
			Base = Base+Count;
			Base++;
			Count = 0;
			goto tryAgain;			
		}
		
		Count++; 
		
		if (Count >= size){
			return (int) Base;
		}
	};
	
    return (int) -1;		
}


unsigned long 
virtual_to_physical ( unsigned long virtual_address, 
                      unsigned long dir_address ) 
{
	unsigned long tmp;
	unsigned long address;
	
	unsigned long *dir = (unsigned long *) dir_address;

	
	int d = (int) virtual_address >> 22 & 0x3FF;
    int t = (int) virtual_address >> 12 & 0x3FF;
    int o = (int) (virtual_address & 0xFFF);

	//temos o endereço da pt junto com as flags.
	tmp = (unsigned long) dir[d];
	
	unsigned long *pt = (unsigned long *) (tmp & 0xFFFFF000);
	
	//encontramos o endereço base do page frame.
	tmp = (unsigned long) pt[t];	
	
	address = (tmp & 0xFFFFF000);
	
	return (unsigned long) (address + o);	
}


//
// End.
//

