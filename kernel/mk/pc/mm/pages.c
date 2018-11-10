/*
 * File: pc\mm\pages.c
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


//
// Algumas áreas de memória:
// =========================
//
// + kernel area    = 1024 pageframes (4MB).
// + kernel image   = 1024 pageframes (4MB).
// + user mode area = 1024 pageframes (4MB).
// + vga            = 1024 pageframes (4MB).
//     (Obs: Isso transpassa o real tamanho da vga).
// + lfb (frontbuffer) = 1024 pageframes (4MB).
//     (Obs: Isso é muito pouco, pois uma placa de vídeo tem mais memória
// que isso).
//      @todo: 
//      LFB needs to be bigger. (Ex: Four 8GB graphic cards). But the driver 
// needs to do all the work.
// + backbuffer     = 1024 pageframes (4MB). 
//     (Obs: Isso realmente é pouco, no backbuffer deve caber uma imagem 
// grande, que será dividida em vários monitores).
//


/*
 O Boot Loader criou alguns diretórios nesses endereços físicos, parece 
 conveniente usar esses endereços.
 @todo: Rever os endereços usados, tanto no kernel, quanto no Boot Loader.

	unsigned long *page_directory         = (unsigned long *) 0x01F00000;
	unsigned long *idle_page_directory    = (unsigned long *) 0x01E00000;
	unsigned long *shell_page_directory   = (unsigned long *) 0x01D00000;
	unsigned long *taskman_page_directory = (unsigned long *) 0x01C00000;
	unsigned long *x_page_directory       = (unsigned long *) 0x01B00000;
	unsigned long *xx_page_directory      = (unsigned long *) 0x01A00000;
	unsigned long *xxx_page_directory     = (unsigned long *) 0x01900000;

 */


#include <kernel.h>


//
// Variáveis passadas pelo Boot Loader.
//

//
// Obs: Teremos que rever os argumentos passados pelo Boot Loader ao Kernel 
// Pois desejamos tornar o Kernel compatível com GRUB.
//

extern unsigned long SavedBootBlock;    //Parâmtros passados pelo Boot Loader.
extern unsigned long SavedLFB;          //LFB address.
extern unsigned long SavedX;            //Screen width.
extern unsigned long SavedY;            //Screen height.
extern unsigned long SavedBPP;          //Bits per pixel.
//...


//
// Funções importadas.
//

extern void set_page_dir();
//...



//
// Obs: Deixar aqui os endereços das páginas.
//


//
// Pagetables:
// ==========
//     Endereços físicos de algumas pagetales.
//

#define KM1_PAGETABLE     0x8F000  // Pagetable para o kernel mode stuff.
#define KM2_PAGETABLE     0x8E000  // Pagetable para 'O Kernel'. A 'imagem'.
#define UM_PAGETABLE      0x8D000  // Pagetable para o aplicativos em user mode.
#define VGA_PAGETABLE     0x8C000  // Pagetable para o VGA em user mode.
#define LFB_PAGETABLE     0x8B000  // LFB.        FRONTBUFFER_PAGETABLE
#define BUFFER_PAGETABLE  0x8A000  // BackBuffer. BACKBUFFER_PAGETABLE
//...


//Usar alguma rotina de hal_ pra isso;
//extern unsigned long _get_page_dir();

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
void map_page(void * physaddr, void * virtualaddr, unsigned int flags)
{
    // Make sure that both addresses are page-aligned.
 
    unsigned long pdindex = (unsigned long)virtualaddr >> 22;
    unsigned long ptindex = (unsigned long)virtualaddr >> 12 & 0x03FF;
 
    unsigned long * pd = (unsigned long *)0xFFFFF000;
    // Here you need to check whether the PD entry is present.
    // When it is not present, you need to create a new empty PT and
    // adjust the PDE accordingly.
 
    unsigned long * pt = ((unsigned long *)0xFFC00000) + (0x400 * pdindex);
    // Here you need to check whether the PT entry is present.
    // When it is, then there is already a mapping present. What do you do now?
 
    pt[ptindex] = ((unsigned long)physaddr) | (flags & 0xFFF) | 0x01; // Present
 
    // Now you need to flush the entry in the TLB
    // or you might not notice the change.
}
*/


/*
void * get_physaddr(void * virtualaddr);
void * get_physaddr(void * virtualaddr)
{
    unsigned long pdindex = (unsigned long)virtualaddr >> 22;
    unsigned long ptindex = (unsigned long)virtualaddr >> 12 & 0x03FF;
 
    unsigned long * pd = (unsigned long *)0xFFFFF000;
    // Here you need to check whether the PD entry is present.
 
    unsigned long * pt = ((unsigned long *)0xFFC00000) + (0x400 * pdindex);
    // Here you need to check whether the PT entry is present.
 
    return (void *)((pt[ptindex] & ~0xFFF) + ((unsigned long)virtualaddr & 0xFFF));
}
*/


/*
static inline void __native_flush_tlb_single(unsigned long addr)
{
   asm volatile("invlpg (%0)" ::"r" (addr) : "memory");
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
 *
 *   **  Aviso importante!  **
 *
 *    O endereço precisa ser um endereço físico.
 * 
 *    O endereço passado via argumento pode ser alocado dinamicamente antes 
 * ou então essa rotina pode corromper alguma área importante.
 *
 *    Antes de chamar essa rotina devemos alocar memória do tamanho de 
 * um diretório, que é de 1024 entradas de 4 bytes. (1024*4).
 *
 * #obs: 
 * #bugbug: Quando criamos um novo diretório de páginas ele não tem nada,
 * nem mesmo o kernel base foi mapeado a parte superior da memória virtual.
 * para todo novo diretório criado, precisamos mapear as páginas que o 
 * kernel base vai usar.
 * >> Por isso que clonar o diretório de páginas do kernel parece se uma boa opção.
 */
 
//deve retornar o endereço do diretório de páginas criado,
//que é um clone do diretório de páginas do kernel.


//#importante:
//retornaremos o endereço virtual, para que a função create_process possa usar 
//tanto o endereço virtual quanto o físico.

void *CreatePageDirectory (){
	
	int i;
	
	unsigned long destAddressVA;  //virtual.
	//unsigned long destAddressPA;  //físico.
	
	//alocaremos uma página apenas, pois tem 4KB.
	
	destAddressVA = (unsigned long) newPage (); //malloc(4096);
	if ( destAddressVA == 0 )
	{
		return NULL;
	}
	
	//o endereço do diretório de páginas clone.
    //precisamos uar o endereço virtual para manipularmos os dados,
	//pois estamos no esquema de memória do kernel base.
	unsigned long *dest = (unsigned long *) destAddressVA;  
	
	//o endereço do diretório de páginas do kernel.
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
	
	//
	// Retornaremos o endereço físico do diretório clone.
	//
	
	//destAddressPA = (unsigned long) virtual_to_physical ( destAddressVA, gKernelPageDirectoryAddress );
	//if ( destAddressPA == 0 ){
	//	return NULL;
	//}
	
	
	//return (void *) destAddressPA;
	
	return (void *) destAddressVA;
};



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
 *
 */
 
//retorna o endereço virtual. 
 
 
 
void *CreatePageTable( unsigned long directory_address, 
                       int offset, 
					   unsigned long region_address )
{
	
	
	//
    // ### pd  ###
    //	
	
	
	//Diretório.
	//precisamos do endereço virtual do diretório para editá-lo
	unsigned long *PD = (unsigned long *) directory_address;       
	
	
	//Limits.
	if ( directory_address == 0 ){
		
		return NULL;
	}	


	//
    // ### pt  ###
    //	
	
	
	
	
	//Tabela de páginas.
	//Precisamos de um endereço virtual para manipularmos a tabela.
	//pois o kernel trabalha com os endereços virtuais ...
	//só depois converteremos e salvaremos na entrada do diretório 
	//o ponteiro que é um endereço físico.
	
	//unsigned long ptVA = (unsigned long) newPage(); 
    unsigned long ptVA = (unsigned long) malloc (4096);
	//Limits.
	if ( ptVA == 0 ){
		
		return NULL;
	}	

	//unsigned long ptPA = (unsigned long) virtual_to_physical ( ptVA, gKernelPageDirectoryAddress ); 
	

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
	int i;
	for ( i=0; i < 1024; i++ )
    {
		//7 decimal é igual a 111 binário.
	    newPT[i] = (unsigned long) region_address | 3;             
	    region_address = (unsigned long) region_address + 4096;  //+4KB.
    };
	
	
	//
    // ### pd  ###
    //		

	//Aqui devemos incluir as flags também.
	//Configurando os atributos.
	
	//#importante
    //vamos usar o endereço virtual, assim como fizemos na 
	//rotina de configuração das páginas.
	
	PD[offset] = (unsigned long) &newPT[0]; 
    PD[offset] = (unsigned long) PD[offset] | 3;      

	
 
    //
	// Retornaremos o endereço virtual para que a tabela possa ser manipulada pelo kernel.
	//

    return (void *) ptVA;
};
 


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
};


//82540 test
//e, 88000h ficará a pagetable para mapear o endereço físico f0000000
//mapeando o nic principal.
//considerando que tenhamos mais de uma placa de rede, 
//esse mapeamento só será válido para o primeiro.
unsigned long mapping_nic0_device_address ( unsigned long address ){
	
    unsigned long *page_directory = (unsigned long *) gKernelPageDirectoryAddress;      

	
	//##bugbug: 
	//Esse endereço é improvisado. Parece que não tem nada nesse endereço.
	//#todo: temos que alocar memória e converter o endereço lógico em físico.
	
	unsigned long *nic0_page_table = (unsigned long *) PAGETABLE_NIC1; //0x88000;
	
	
	int i;
	for ( i=0; i < 1024; i++ ){
		
		nic0_page_table[i] = (unsigned long) address | 3;     
	    address = (unsigned long) address + 4096;  
    };
	

	//0xC1000000    772  ##test
	//f0000000      960
	
    page_directory[960] = (unsigned long) &nic0_page_table[0];      
    page_directory[960] = (unsigned long) page_directory[960] | 3;   	
	
	//endereço equivalente à entrada 772
	return (unsigned long) 0xF0000000;
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

int SetUpPaging (){
	
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


	//
	// *FIM
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
	gKernelPageDirectoryAddress = 0x0009C000;  
	
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
	
	//#test
	//precisamos de um endereço físico para a pagetable que mapeará os buffers.
	//#bugbug: o malloc não funciona ainda. Estamos inicializando o mapeamento.
	//então isso deveria retornar 0 se o malloc não funcionar.???
	//então mesmo que o malloc funcione a rotina de transformar v em f não funciona 
	//porque o diretorio de páginas do kernel ainda está incompleto.
	//unsigned long xxxhptVA = (unsigned long) malloc (4096); 
	//if(xxxhptVA == 0)
	//{
	//    printf("pages.c xxxhptVA *fail");
    //    refresh_screen();
	//    while(1){}
	//}	
	//unsigned long *heappool_page_table = (unsigned long *) virtual_to_physical ( xxxhptVA, gKernelPageDirectoryAddress );  
	unsigned long *heappool_page_table = (unsigned long *) PAGETABLE_HEAPPOOL; 
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
	
	for ( i=0; i < 1024; i++ ){
		
		km_page_table[i] = (unsigned long) SMALL_kernel_address | 3;     
	    SMALL_kernel_address = (unsigned long) SMALL_kernel_address + 4096;  
    };
	
    page_directory[0] = (unsigned long) &km_page_table[0];      
    page_directory[0] = (unsigned long) page_directory[0] | 3;  
	
	
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

	    km2_page_table[i] = (unsigned long) SMALL_kernel_base | 3;     
	    SMALL_kernel_base = (unsigned long) SMALL_kernel_base + 4096;  
    };
	
    page_directory[768] = (unsigned long) &km2_page_table[0];       
    page_directory[768] = (unsigned long) page_directory[768] | 3;  


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
	
	for ( i=0; i < 1024; i++ ){
		
		um_page_table[i] = (unsigned long) SMALL_user_address | 7;     
	    SMALL_user_address = (unsigned long) SMALL_user_address + 4096; 
    };
	
    page_directory[1] = (unsigned long) &um_page_table[0];      
    page_directory[1] = (unsigned long) page_directory[1] | 7; 
	
	
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
		
	    vga_page_table[i] = (unsigned long) SMALL_vga_address | 7;     
	    SMALL_vga_address = (unsigned long) SMALL_vga_address + 4096;  
    };

    page_directory[2] = (unsigned long) &vga_page_table[0];     
    page_directory[2] = (unsigned long) page_directory[2] | 7;  

	
	// Obs: 4MB começando do endereço físico 0x000B8000, são acessíveis
	// em user mode à partir do endereço virtual 0x00800000virt.
	
	//
	// ** PAGETABLE, FRONT BUFFER  **
	//
	
	g_frontbuffer_va = (unsigned long) 0xC0400000;        
	
	
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
		
	
    for ( i=0; i < 1024; i++ ){

		frontbuffer_page_table[i] = (unsigned long) SMALL_frontbuffer_address | 7;     
	    SMALL_frontbuffer_address = (unsigned long) SMALL_frontbuffer_address + 4096;  
    };
	
    page_directory[769] = (unsigned long) &frontbuffer_page_table[0];       
    page_directory[769] = (unsigned long) page_directory[769] | 7;  	
	
	
	//
	// ** PAGETABLE, BACKBUFFER **
	//
	
	g_backbuffer_va = (unsigned long) 0xC0800000; 
	
    //===============================================================
	// user mode BUFFER1 pages - (0x01000000 - 0x800000 fis) = 0xC0800000virt).
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
	
	for ( i=0; i < 1024; i++ ){
		
	    backbuff_page_table[i] = (unsigned long) SMALL_backbuffer_address | 7;     
	    SMALL_backbuffer_address = (unsigned long) SMALL_backbuffer_address + 4096;  
    };
	
    page_directory[770] = (unsigned long) &backbuff_page_table[0];      
    page_directory[770] = (unsigned long) page_directory[770] | 7;  	


	// Obs: 4MB da memória física à partir do endereço físico 0x01000000 (16MB)
    // são destinados ao back buffer. Obs: Isso é bem pouco, uma tela com alta 
	// resolução usa mais que isso.	
	
	
	//
	// ** PAGETABLE, PAGEDPOOL **
	//	
	
	g_pagedpool_va = (unsigned long) 0xC0C00000;
	
	// (user mode)
	// 7 decimal é igual a 111 binário.	
	// kernel
    // Criando a entrada do diretório de páginas do processo kernel.
	// o bit 7 da entrada permanece em 0, indicando que temos páginas de 4KB.
	// Salva no diretório o endereço físico.
	// Configurando os atributos.
	
	for ( i=0; i < 1024; i++ ){
		
	    pagedpool_page_table[i] = (unsigned long) SMALL_pagedpool_address | 7;     
	    SMALL_pagedpool_address = (unsigned long) SMALL_pagedpool_address + 4096;  
    };

    page_directory[771] = (unsigned long) &pagedpool_page_table[0];      
    page_directory[771] = (unsigned long) page_directory[771] | 7;  	

	
	//heaps suppport
	//preparando uma área de memória grando o bastante 
	//para conter o heap de todos os processos.
	//ex: podemos dar 128kb para cada processo inicialmente.

	for ( i=0; i < 1024; i++ ){
		
	    heappool_page_table[i] = (unsigned long) SMALL_heappool_address | 7;     
	    SMALL_heappool_address = (unsigned long) SMALL_heappool_address + 4096;  
    };

    page_directory[772] = (unsigned long) &heappool_page_table[0];      
    page_directory[772] = (unsigned long) page_directory[772] | 7;  	
	
	
	
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

	
	//
	// Obs: Podemos reaproveitas pagetables em diferentes processos.
	//

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
	// Inicializando a lista de pageframes.
	//
	
	for ( Index=0; Index < PAGEFRAME_COUNT_MAX; Index++ ){
		
	    pageframeList[Index] = (unsigned long) 0;
	};

	//Configurando manualmente a lista de pageframes.
	pageframeList[0] = (unsigned long) 0;
	pageframeList[1] = (unsigned long) 0;
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
		
		kfp->address = (unsigned long) (0 * MB);   //?? Começa em 0 MB. ??
		
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
		
		small_fp->address = (unsigned long) (4 * MB);   //Começa em 4 MB.

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
		
		pageable_fp->address = (unsigned long) (20 * MB);   //Começa em 20 MB.

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
done:
#ifdef MK_VERBOSE
	printf("Done\n");
#endif	
    return (int) 0;
};


/*
 * initializeFramesAlloc:
 *     Inicializa o framepool.
 */
void initializeFramesAlloc (){
	
	int Index;
	struct page_frame_d *pf;
	
	//
	// Inicializando a lista de pageframes.
	//
	
	for ( Index=0; Index < PAGEFRAME_COUNT_MAX; Index++ ){
		
	    pageframeAllocList[Index] = (unsigned long) 0;
	};
	
	
	//
	// Criando o primeiro para testes.
	//
	
	pf = (void *) malloc ( sizeof( struct page_frame_d ) );
	
	if ( pf == NULL )
	{
		printf("initializeFramesAlloc:\n");
		return;
		//goto done;
	}else{
		
	    pf->id = 0;
	
	    pf->used = 1;
	    pf->magic = 1234;
	
	    pf->free = 0;  //not free
	    pf->next = NULL; 
	    //...	
	
	    pageframeAllocList[0] = ( unsigned long ) pf; 		
	};	
};



/*
 ***********************************************
 * allocPageFrames:
 *
 * @param número de páginas contíguas.
 * Obs: Pode ser que os pageframes não sejam 
 * contíguos mas as páginas serão.
 * estamos usando uma page table toda já mapeada. 4MB.
 * @TODO: ESSA ROTINA ESTÁ INCOMPLETA ... REVISAR. #bugbug
 *
 */
void *allocPageFrames( int size ){
	
	int Index;
	
	//página inicial da lista
	struct page_frame_d *Ret;   
	
	struct page_frame_d *Conductor;
	struct page_frame_d *pf;
	
	//Esse é o endereço virtual do início do pool de pageframes.
	unsigned long base = (unsigned long) g_pagedpool_va;
	
	int Count = 0;
	
	//
	// Checando limites.
	//
	
#ifdef MK_VERBOSE
    printf("allocPageFrames: Initializing ...\n");	
#endif

	//problemas com o size.
	if(size <= 0){
		//if debug
		printf("allocPageFrames: size 0\n");
		return NULL;
	};
			
    //Se é pra alocar apenas uma página.
	if(size == 1)
	{
		//
		//   ## bugbug ##
		//
		
		//printf("allocPageFrames: alguem esta tentando alocar somente uma página ...\n");
		//refresh_screen();
		//while(1){ asm ("hlt");}		
		
		//#importante
		//Para corrigir podemos usar essa rotina de alocação de uma página 
		//ela faz tudo certinho. 
		
		return (void *) newPage();
		
	}	
	
	//se o size for maior que o limite.
    if( size > PAGEFRAME_COUNT_MAX ){
		//if debug
		printf("allocPageFrames: size limits\n");
		goto fail;
	}
	
	
	//
	// Isso encontra slots o suficiente para alocarmos tudo o que queremos.
	//
	int Base;
	Base = firstSlotForAList(size);
	if( Base == -1 ){
		printf("Base = -1 \n");
		goto fail;
	}
	
#ifdef MK_VERBOSE	
    printf("allocPageFrames: for ...\n");		
#endif 
 
	//começamos a contar do frame logo após o condutor.
	for(Index = Base; Index < (Base+size+1); Index++)
	{
	    pf = (void*) pageframeAllocList[Index];
				
		//Slot livre
		if( pf == NULL )
		{
			//#bugbug
			//Isso pode esgotar o heap do kernel
			pf = (void*) malloc( sizeof( struct page_frame_d ) );
			if( pf == NULL ){
				printf("allocPageFrames: 2\n");
				goto fail;
			};
			
			//printf("#");
			pf->id = Index;
			pf->used = 1;
			pf->magic = 1234;
			pf->free = 0;  //not free
			//...
			
			pageframeAllocList[Index] = ( unsigned long ) pf; 
			
			Conductor->next = (void*) pf;
			Conductor = (void*) Conductor->next;
			
			Count++;
			if( Count >= size )
			{
				Ret = (void*) pageframeAllocList[Base];
			    goto done;	
			}	
		};
	};
	
fail:
    printf("allocPageFrames: fail ...\n");		
    return NULL;	
done:
    //printf("allocPageFrames: done ...\n");	
    
	//*Importante:
	//retornaremos o endereço virtual inicial do primeiro pageframe da lista.
	return (void*) ( base + (Ret->id * 4096) );
};


//checar se a estrutura é nula
int pfEmpty (struct page_frame_d *pf){
	
    return pf == NULL ? 1 : 0;
};


//selecionar o pageframe como livre.
void freePageframe (struct page_frame_d *pf){
	
	if (pf == NULL){
		return;  //fail	
	}
	    
	//check
    if( pf->used == 1 && pf->magic == 1234 ){
	    pf->free = 1;
	}		
};


//selecionar o pageframe como não livre.
void notfreePageframe (struct page_frame_d *pf){
	
	if(pf == NULL){
		return;  //fail	
	}
	    
	//check
    if( pf->used == 1 && pf->magic == 1234 ){
	    pf->free = 0;
	}		
};


/*
 ******************************************************
 * newPageFrame:
 *    Aloca apenas um frame de memória física e retorna 
 * o ponteiro.
 *    ? kernel mode ? user mode ?
 *    obs: isso funciona bem.
 * Obs: Isso é usado pelo alocador de páginas, logo abaixo.
 * 
 */
void *newPageFrame (){
	
	//#importante: 
	//Essa estrutura é para frame na memória física.
	struct page_frame_d *New;
	
	int Index;	
	unsigned long Address = (unsigned long) (g_pagedpool_va);

	//procura slot vazio.
    for(Index = 0; Index < PAGEFRAME_COUNT_MAX; Index++)
	{
	    New = (void*) pageframeAllocList[Index];		
		if( New == NULL )
		{
			New = (void*) malloc( sizeof( struct page_frame_d ) );
			if( New == NULL ){
				printf("pc-mm-newPageFrame:\n");
				goto fail;
			};
			
			//printf("$");
			New->id = Index;
			New->used = 1;
			New->magic = 1234;
			New->free = 0;  //not free
			New->next = NULL;
			
			
			//#bugbug ... isso tá errado.
			//endereço físico do inicio do frame.
			//New->address = (unsigned long) Address;
			//...
			
			pageframeAllocList[Index] = ( unsigned long ) New; 
		    return (void*) New;
		};
	};	

fail:
    return NULL;    
};


/*
 *********************************************************************
 * newPage:
 *     Aloca uma página e retorna seu endereço virtual inicial
 * com base no id do pageframe e no endereço virtual inicial do pool 
 * de pageframes.
 *     ? kernel Mode ? ou user mode ?
 *     Obs: Isso funciona bem.
 * Obs: Alocaremos uma página de memória virtual e retornaremos 
 * o ponteiro para o início da página.
 * Para isso usaremos o alocador de frames de memória física.
 */
void *newPage (){
	
	//#importante: 
	//Essa estrutura é para frame na memória física.	
	struct page_frame_d *New;
	
	// Esse é o endereço virtual do início do pool de pageframes.
	// Isso significa que num pool temos vários pageframes.
	
	unsigned long base = (unsigned long) g_pagedpool_va;	
    
	
    //
	// Pega o id do pageframe e 
	// multiplica pelo tamanho do frame e 
	// adiciona à base.	
	//
	
    // Novo frame.
	New	= (void *) newPageFrame ();
	
	if( New == NULL )
	{
		printf("pc-mm-newPage: New\n");
		goto fail;
		
	}else{
	    
		//check
        if( New->used == 1 && New->magic == 1234 )
		{
			//pega o id 
			//checa o limite de slots.
			if( New->id > 0 && New->id < PAGEFRAME_COUNT_MAX )
            {
				return (void *) ( base + (New->id * 4096) );
			}				
		};		
	};
	
 //
 // Fail !
 //
	
fail:
    return NULL;	
};


/*
 ***************************************************************
 * firstSlotForAList:
 *     Retorna o primeiro índice de uma sequência de 
 * slots livres no pageframeAllocList[].
 *
 */
int firstSlotForAList ( int size ){
	
	int Index;
	int Base = 0;
	int Count = 0;
    void *slot;
	
tryAgain:
	
	for( Index=Base; Index < 1024; Index++ )
	{
	    slot = (void*) pageframeAllocList[Index];
		if( (void*) slot != NULL )
		{
			Base = Base+Count;
			Base++;
			Count = 0;
			goto tryAgain;			
		};
		
		Count++;       
		if(Count >= size){
			return (int) Base;
		}
	};
     	
fail:		
    return (int) -1;		
};


/*
 * testingFrameAlloc:
 *
 * //#importante:
 * //teste de memória é sempre importante.
 * //@todo: Rotina de teste. 
 */ 
void testingFrameAlloc (){
	
	int Index;
    struct page_frame_d *pf;
	void *RetAddress;
	unsigned long fileret;
	
	//#bugbug .;;;: mais que 100 dá erro ...
	//@todo: melhorar o código de alocação de páginas.
	//printf("testingFrameAlloc: #100\n");
	printf("testingFrameAlloc:\n");
	
	//
	// =============================================
	//
	
	// #test:
	// Funcionou com 500.
    //Ret = (void*) allocPageFrames(500);  
	
	//8KB. Para imagem pequena.
	RetAddress = (void *) allocPageFrames(2);      
	if( (void*) RetAddress == NULL )
	{
	    printf("RetAddress fail\n");
        goto fail;		
	}
	
	printf("\n");
	printf("BaseOfList={%x} Showing #32 \n",RetAddress);
    
	for ( Index=0; Index < 32; Index++ )   	
	{  
        pf = (void *) pageframeAllocList[Index]; 
		
		if( (void *) pf == NULL ){
		    printf("null\n");	 
		}
	    
		if ( (void *) pf != NULL )
		{
		    printf("id={%d} used={%d} magic={%d} free={%d} handle={%x} next={%x}\n", pf->id,
			    pf->used, pf->magic, pf->free, pf, pf->next ); 	
		}
		//Nothing.
	};
	
	
    //===================================
	// @todo: Carregar a estrelinha e usar como ponteiro de mouse.
	//
	//janela de test
    //CreateWindow( 1, 0, 0, "Fred-BMP-Window", 
	//              (10-5), (10-5), (376+10), (156+10), 
	//			  gui->main, 0, COLOR_WINDOW, COLOR_WINDOW); 	
	
	
	
	//fileret = fsLoadFile( "DENNIS  BMP", (unsigned long) Ret);
	//fileret = fsLoadFile( "FERRIS  BMP", (unsigned long) Ret);
	//fileret = fsLoadFile( "GOONIES BMP", (unsigned long) Ret);
	//fileret = fsLoadFile( "GRAMADO BMP", (unsigned long) Ret);
	fileret = fsLoadFile( "BMP1    BMP", (unsigned long) RetAddress);  
	if(fileret != 0)
	{
		printf("BMP1    BMP FAIL\n");
		//escrevendo string na janela
	    //draw_text( gui->main, 10, 500, COLOR_WINDOWTEXT, "DENNIS  BMP FAIL");
        //draw_text( gui->main, 10, 500, COLOR_WINDOWTEXT, "FERRIS  BMP FAIL");
		//draw_text( gui->main, 10, 500, COLOR_WINDOWTEXT, "GOONIES BMP FAIL");	
        //draw_text( gui->main, 10, 500, COLOR_WINDOWTEXT, "GRAMADO BMP FAIL");
		//draw_text( gui->main, 10, 500, COLOR_WINDOWTEXT, "BMP1    BMP FAIL");
	};
	
	
	bmpDisplayBMP( (char*) RetAddress, 20, 20);

    //===================================							
    
	
	//
	// *importante:
	//  O REFRESH RECT SÓ FUNCIONA DAS DIMENSÕES NÃO O POSICIONAMENTO.
	//
	
	//Isso funcionou ...
	refresh_rectangle( 20, 20, 16, 16 );
	
	//struct myrect *rc;
	
	//rc = (void *) malloc( sizeof( struct myrect ) );
	//if(
	
	//rc->left   = 40 ;
	//rc->right  = 80;
	//rc->top    = 40 ;
	//rc->bottom = 80;
	
	//move_back_to_front(rc);
	
	printf("pc-mm-testingFrameAlloc: debug hang\n");
    die();
	
done:
  // Nothing for now.	
fail:
	refresh_screen();
    return;	
};


unsigned long 
virtual_to_physical ( unsigned long virtual_address, 
                      unsigned long dir_address ) 
{
	
	unsigned long address;
	
	unsigned long *dir = (unsigned long *) dir_address;

	unsigned long tmp;
	
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
};

//
// End.
//

