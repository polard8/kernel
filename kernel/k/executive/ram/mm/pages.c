/*
 * File: pages.c
 *
 * Descrição:
 *     Faz a configuração da paginação de memória e oferece rotinas de
 * suporte ao mapeamento de memória física.
 *     Faz parte do modulo /mm da classe ram.
 *
 * @todo: 
 *    IMPORTANTE:
 *    FAZER GERENCIAMENTO DA MEMÓRIA FÍSICA. 
 *    DIVIDIR A MEMÓRIA FÍSICA EM PARTIÇÕES DE 4MB.
 *    E DIVIDIR CADA PARTIÇÃO EM FRAMES DE 4KB, O QUE DÁ 1024 FRAMES 
 *    POR PARTIÇÃO.
 *    Obs: Podemos chamar de 'framepool' o conjunto de 1024 frames.
 *         Poderemos mapear um framepool inteiro se preciso. 
 *
 * @todo:
 * Obs: Os processos Idle, Shell e Taskman estão usando o diretório de 
 * páginas do processo Kernel. É preciso criar um diretório para cada 
 * processo e criar uma rotina de automação na criação de diretórios
 * de páginas.
 *
 * @todo: 
 * Criar rotinas para ver o conteúdo da lista de diretórios de páginas.
 * ?? Cada diretório deve ter uma estrutura cujo ponteiro vai pra dentro da lista.
 * ?? A estrutura mostrará informações sobre o diretório de páginas.
 *
 * @todo: Criar rotinas que manipulem as estruturas de diretório de páginas e
 * de pagetables. 
 *
 * In this file:
 *     +CreatePageDirectory
 *     +CreatePageTable
 *     +SetCR3
 *     +SetUpPaging
 *     +
 *
 * Histórico:
 *     2015 - Created by Fred Nora.
 *     2016 - Revision.
 *     ...
 */


//
// + kernel area    = 1024 pageframes (4MB)
// + kernel image   = 1024 pageframes (4MB)
// + user mode area = 1024 pageframes (4MB)
// + vga = 1024 pageframes (4MB) (Isso transpassa o real tamanho da vga)
// + lfb = (frontbuffer) 1024 pageframes (4MB) (Isso é muito pouco, pois
//         uma placa de vídeo tem mais memória que isso)
//         @todo: LFB needs to be bigger. (Ex: Four 8GB graphic cards).
//                But the driver needs to do all the work.
// + backbuffer = 1024 pageframes (4MB) (Isso realmente é pouco, no backbuffer
//         deve caber uma imagem grande, que será dividade em vários monitores.)
//


/*
 O Boot Loader criou alguns diretórios nesses endereços físicos,
 parece conveniente usar esses endereços.

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
//     Endereço físico de algumas pagetales.
//
#define KM1_PAGETABLE     0x8F000    //Pagetable para o kernel mode stuffs.
#define KM2_PAGETABLE     0x8E000    //Pagetable para 'O Kernel'.(imagem).
#define UM_PAGETABLE      0x8D000    //Pagetable para o aplicativos em user mode.
#define VGA_PAGETABLE     0x8C000    //Pagetable para o vga em user mode.
#define LFB_PAGETABLE     0x8B000    //LFB.
#define BUFFER_PAGETABLE  0x8A000    //BackBuffer.
//...


/*
enum PAGE_PTE_FLAGS {
 
	I86_PTE_PRESENT			=	1,		//0000000000000000000000000000001
	I86_PTE_WRITABLE		=	2,		//0000000000000000000000000000010
	I86_PTE_USER			=	4,		//0000000000000000000000000000100
	I86_PTE_WRITETHOUGH		=	8,		//0000000000000000000000000001000
	I86_PTE_NOT_CACHEABLE		=	0x10,		//0000000000000000000000000010000
	I86_PTE_ACCESSED		=	0x20,		//0000000000000000000000000100000
	I86_PTE_DIRTY			=	0x40,		//0000000000000000000000001000000
	I86_PTE_PAT			=	0x80,		//0000000000000000000000010000000
	I86_PTE_CPU_GLOBAL		=	0x100,		//0000000000000000000000100000000
	I86_PTE_LV4_GLOBAL		=	0x200,		//0000000000000000000001000000000
   	I86_PTE_FRAME			=	0x7FFFF000 	//1111111111111111111000000000000
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


//Usar alguma rotina de hal_ pra isso;
//extern unsigned long _get_page_dir();


/*
 * CreatePageDirectory:
 *     Cria um page directory para um processo.
 *     Obs:
 *     + O endereço precisa ser alocado antes.
 *     + Precisa ser um endereço físico.
 *     +...
 *
 * @todo: Mudar para pagesCreatePageDirectory(.)
 */
void *CreatePageDirectory(unsigned long directory_address)
{	
	int i;
	unsigned long *page_directory = (unsigned long *) directory_address;    //Diretório.


   /*
    * @todo: 
	*     Na verdade os diretórios de página e as page tables devem ser 
	* criados em sequência num local pre-definido ou deve-se alocar memória 
	* para criá-lo. 
	*/	
	
	//Limits.
	if(directory_address == 0){
		return NULL;
	};


	//
	//@todo:
	//    Save on a list of directories.
	//    Registra na lista de diretórios.
	//
	//pagedirectoryList[PAGEDIRECTORY_COUNT_MAX]; 
	
	
	//...
	
done:	
	return (void*) directory_address;
};



/*
 * CreatePageTable:
 *     Cria uma page table em um diretório.
 *     Obs:
 *     + O endereço precisa ser alocado antes.
 *     + Precisa ser um endereço físico.
 *     + O diretório precisa ser um diretório válido.
 *
 * Argumentos:
 *     directory_address - 
 *     offset -
 *     page_address -
 *
 * @todo: Mudar para pagesCreatePageTable(...)
 */
void *CreatePageTable( unsigned long directory_address, 
                      int offset, 
					  unsigned long page_address )
{
	int i;
	unsigned long *page_directory = (unsigned long *) directory_address;    //Diretório.
	unsigned long *page_table = (unsigned long *) page_address;
	
	//Limits.
	if(directory_address == 0){
		return NULL;
	};

	//Limits.
	if(offset < 0){
		return;
	};


	page_directory[offset] = (unsigned long) page_address;


	//
	// @todo: 
	//     Registrar na lista de páginas.  
	//     Salvar estruturas.
	//
	//unsigned long pagetableList[PAGETABLE_COUNT_MAX]; 

done:
    return (void*) page_address;
};


/*
 * SetCR3:
 *     Configurando cr3.
 *     Obs: Precisa ser endereço físico.
 *     Obs: Chamamos uma rotina em assembly.
 *     @todo: Mudar para pagesSetCR3(.)
 */
//void pagesSetCR3(unsigned long address) 
void SetCR3(unsigned long address)
{
	if(address == 0){
		return;
	};
	asm volatile("\n" :: "a"(address) );
	set_page_dir();
	return;
};


/*
 * SetUpPaging:
 *     Configura o diretório de páginas do processo Kernel e algumas tabelas 
 * de páginas.
 * Obs: 
 *     Na hora em que um processo é criado deve-se criar seu diretório de 
 * páginas e as tabelas de páginas usadas por ele, de acordo com o tamanho 
 * do processo.
 *
 * In this function:
 *     ...
 *
 * Diretório:
 *   page_directory = 0x0009C000. (endereço físico).
 *
 * Obs:
 *     Esse diretório criado será usado pelo processo Kernel e outros processos 
 * também durante essa fase de construção do sistema. Depois cada processo terá
 * seu próprio diretório de páginas. (@isso está em fase de implementação). O 
 * ideal é um diretório por processo.
 *     Toda vez que o processo Kernel iniciar a execução de um processo ele deve 
 * carregar o endereço do diretório do processo no registrador de controle CR3.
 *     @todo: Por enquanto só um diretório foi criado.
 *     @todo Mudar para pagesSetUpPaging
 *
 * Histórico:
 *     2015 - Essa função foi criada por Fred Nora.
 *     2016 - Revisão.
 *     ...
 */
//int pagesSetUpPaging() 
int SetUpPaging()
{
    unsigned int i;
	int Index;

    //
	// (phase 1) Endereços da memória físicas acessíveis em Kernel Mode.
    //	

	// Kernel process.
	unsigned long kernel_address = 0;        //para os 4 primeiros mega da memoria fisica     
	unsigned long kernel_base = KERNEL_BASE; //0x00100000 //para o kernnel que começa no primeiro mega

    //
	// (phase 2) Endereços da memória físicas acessíveis em User Mode.
    //


	// User, VGA, VESA LFB, BUFFER ...
	unsigned long user_address = USER_BASE; //0x00400000; 	
	unsigned long vga_address  = VM_BASE;   //0x000B8000; 
    unsigned long lfb_address  = (unsigned long) SavedLFB;    //g_lbf_pa, Foi passado pelo boot manager.
	unsigned long buff_address = (unsigned long) 0x01000000;  //16MB, #Provisório.
	// ...


	//
	// DIRECTORY:
	//     Diretório do processo Kernel. Esse diretório já foi criado nesse 
	// endereço físico pelo Boot Loader. Aqui o kernel apenas reconfigura, 
	// utilizando a mesma localizaçao. KERNEL_PAGEDIRECTORY.
	//
	unsigned long *page_directory = (unsigned long *) 0x0009C000;    //KERNEL_PAGEDIRECTORY. 


	//
	// O que temos logo abaixo são pequenas partições de memória física.
	// cada partição tem 1024 unsigned longs. o que dá 4kb cada. 
	//
	//
	
	//
	// TABLES: 
	//     Tabelas de páginas para o diretório do processo Kernel. Essas 
	// tabelas já foram criadas nesses endereços físicos pelo Boot Loader. 
	// Aqui o Kernel apenas reconfigura utilizando as mesmas localizações.
	//

	//kernel mode. (Endereços).
	unsigned long *km_page_table   = (unsigned long *) 0x0008F000;  //KM1_PAGETABLE.

	//kernel mode. (O kernel).
    unsigned long *km2_page_table  = (unsigned long *) 0x0008E000;  //KM2_PAGETABLE.

	//user mode.
	unsigned long *um_page_table   = (unsigned long *) 0x0008D000;  //UM_PAGETABLE.

	//user mode. (vga).
	unsigned long *vga_page_table  = (unsigned long *) 0x0008C000;  //VGA_PAGETABLE.

	//user mode. (LFB).
	unsigned long *lfb_page_table  = (unsigned long *) 0x0008B000;  //LFB_PAGETABLE.

	//user mode. (buffer).
    unsigned long *buff_page_table = (unsigned long *) 0x0008A000;  //BUFFER_PAGETABLE.

	//...


    //
	// Message. (verbose).
	printf("SetUpPaging: Initializing Pages..\n");


	//
	// Preenchendo todo o diretório com páginas não presentes. Usando um 
	// endereço inválido de página.
	//

	for(i = 0; i < 1024; i++){
		page_directory[i] = (unsigned long) 0 | 2;    //010 em binário.
	};

	//
	// kernel mode pages (0fis = 0virt)
	// kernel_address = 0.
	// Mapear os primeiros 4MB da memória. (kernel mode). Preenchendo a tabela 
	// km_page_table. A entrada 0 do diretório refere-se aos primeiros 4 megas 
	// de endereço virtual.
	//
    // Aqui estamos pegando uma partição de memória física de 4MB que começa no 
	// início da memória RAM.
    //
    
	for(i = 0; i < 1024; i++)
    {
	    km_page_table[i] = (unsigned long) kernel_address | 3;     //011 binário.
	    kernel_address   = (unsigned long) kernel_address + 4096;  //+ 4KB.
    };
    //Criando a entrada número '0' do diretório de páginas do processo Kernel.
    page_directory[0] = (unsigned long) &km_page_table[0];      //Salva no diretório o endereço físico da tabela.
    page_directory[0] = (unsigned long) page_directory[0] | 3;  //Configurando os atributos.
    

	//
	// kernel mode pages (0x00100000fis = 0xC0000000virt)
	// kernel_base = 0x00100000 = KERNEL_BASE.
	// Mapear 4MB começando do primeiro mega. (kernel mode).
	// Preenchendo a tabela km2_page_table.
	//
    // Aqui estamos pegando uma partição de memória física de 4MB que começa no
	// endereço físico que carregamos a imágem do kernel. 
    //	

	 
    for(i = 0; i < 1024; i++)
    {
	    km2_page_table[i] = (unsigned long) kernel_base | 3;     //011 binário.
	    kernel_base       = (unsigned long) kernel_base + 4096;  //+4KB.
    };
    // Criando a  entrada do diretório.
    page_directory[768] = (unsigned long) &km2_page_table[0];       //Salva no diretório o endereço físico.
    page_directory[768] = (unsigned long) page_directory[768] | 3;  //Configurando os atributos.


	//
    // Obs: Percebe-se que houve uma sobreposição. Os megas 0,1,2,3 para
	// kernel mode e os megas 1,2,3,4 para o kernel base.
	// Isso significa que o Kernel Base pode acessar o primeiro mega
	// da memória física, usando endereço virtual igual ao endereço físico.
	//
	
	//
	// user mode pages - (0x00400000fis = 0x00400000virt)
	// user_address = 0x00400000 = USER_BASE.
	// Mapear 4MB da memória começando em 0x00400000fis. (user mode).
	//
	//
    // Aqui estamos pegando uma partição de memória física de 4MB que começa no
	// endereço físico 0x00400000, no quarto mega da memória física. 
    //

	for(i = 0; i < 1024; i++)
    {
	    um_page_table[i] = (unsigned long) user_address | 7;     //7 decimal é igual a 111 binário.
	    user_address     = (unsigned long) user_address + 4096;  //+4KB.
    };
    // Criando a entrada do diretório.
    page_directory[1] = (unsigned long) &um_page_table[0];      //Salva no diretório o endereço físico.
    page_directory[1] = (unsigned long) page_directory[1] | 7;  //Configurando os atributos.

	//
    // Obs: Novamente aqui há uma sobreposição. O primeiro mega
	// dessa área destinada à user mode, é o mesmo último mega da
    // área destinada ao Kernel Base. Isso significa uma área de memória
    // compartilhada. O que está no primeiro mega dessa área em user mode
	// também está no último mega da área do kernel base.
    //	
	  
	  
    //
	// user mode VGA pages - ( 0x000B8000fis = 0x00800000virt)
	// vga_address  = VM_BASE;   //0x000B8000;
	// Mapear 4MB da memória começando em 0x000B8000fis. (user mode).
	// @todo: Aqui na verdade não precisa configurar 4 megas, 
	//        apenas o tamanho da memória de vídeo presente em 0xb8000.
	//
    // Aqui estamos pegando uma partição de memória física de 4MB que começa no
	// endereço físico 0x000B8000.
    // @todo: bugbug: ESSA É CGA E NÃO A VGA.
    //Mudar o nome para cga.	
    //	
    	
    for(i = 0; i < 1024; i++)
    {
	    vga_page_table[i] = (unsigned long) vga_address | 7;     //7 decimal é igual a 111 binário.
	    vga_address       = (unsigned long) vga_address + 4096;  //+4KB.
    };
    // Criando a entrada do diretório.
    page_directory[2] = (unsigned long) &vga_page_table[0];     //Salva no diretório o endereço físico.
    page_directory[2] = (unsigned long) page_directory[2] | 7;  //Configurando os atributos.

	//
	// Obs: 4MB começando do endereço físico 0x000B8000, são acessíveis
	// em user mode à partir do endereço virtual 0x00800000virt.
	//
	
	
    //
	// user mode LFB pages - (0x????????fis = 0xC0400000virt).
	// lfb_address  = SavedLFB = g_lbf_pa, Foi passado pelo boot manager.
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
	
    for(i = 0; i < 1024; i++)
    {
	    lfb_page_table[i] = (unsigned long) lfb_address | 7;     //7 decimal é igual a 111 binário.
	    lfb_address       = (unsigned long) lfb_address + 4096;  //+4KB.
    };
    // Criando a entrada do diretório.
    page_directory[769] = (unsigned long) &lfb_page_table[0];       //Salva no diretório o endereço físico.
    page_directory[769] = (unsigned long) page_directory[769] | 7;  //Configurando os atributos.	

    //
	// user mode BUFFER1 pages - (0x01000000fis = 0xC0800000virt).
	// ***BackBuffer: 
	//     É o buffer onde se pinta o que aparecerá na tela. O conteúdo 
	// desse buffer é copiado no LFB da memória de vídeo, (refresh_screen).
    // buff_address = 0x01000000 = 16MB, #Provisório.	
	// O endereço de memória lógica utilizada é 4MB à partir de 0xC0800000.
	//
    // Aqui estamos pegando uma partição de memória física de 4MB que começa no
	// endereço físico 0x01000000, no decimo sexto mega da memória física. 
    //	

    for(i = 0; i < 1024; i++)
    {
	    buff_page_table[i] = (unsigned long) buff_address | 7;     //7 decimal é igual a 111 binário.
	    buff_address       = (unsigned long) buff_address + 4096;  //+4KB.
    };
    // Criando a entrada do diretório.
    page_directory[770] = (unsigned long) &buff_page_table[0];      //Salva no diretório o endereço físico.
    page_directory[770] = (unsigned long) page_directory[770] | 7;  //Configurando os atributos.	


	//
	// Obs: 4MB da memória física à partir do endereço físico 0x01000000 (16MB)
    // são destinados ao back buffer. Obs: Isso é bem pouco, uma tela com alta 
	// resolução usa mais que isso.	
	//


	//
	// @todo:  O que precisa ser feito no momento:
	//         + Os processos em user mode precisam alocação
	// dinâmica de memória, para isso será usado o heap do processo
	// ou o heap do desktop ao qual o processo pertence.
	// *IMPORTANTE: Os buffers de janela serão alocados no heap
	// do processo em user mode que gerencia a criação de janelas,
	// portanto esse processo tem que ter bastante heap disponível.
	//


	//
	// @todo: Continua: Mais páginas podem ser criadas.
	//


	//
	// @todo: Até agora tem uma sobreposição danada no mapeamento
	// um mesmo endereço físico de memória é mapeado para vários
	// endereços virtuais. Ete aí não há problema nisso. Na prática
	// podemos acessar a mesma região de memória de várias maneira diferentes.
	//


	//
	// @todo: *IMPORTANTE.
	// O que queremos é utilizar uma lista de frames livres na hora
	// configurarmos o mapeamento. Queremos pegar um frame livre e
	// associarmos ele com uma PTE, (entrada na tabela de páginas).
	// O que está faltando é o gerenciamento de memória física.
	// O gerenciamento de memória física é feito dividindo
	// a memória física em partições, pedaços grandes de memória.
	//
	//

	//
	// Debug:
	//     Mostrando os endereços do diretório e das páginas.
	//     #verbose.
	//

	printf("Debug:\n");
	printf("Configurando CR3={%x} !\n", (unsigned long) &page_directory[0]);
	printf("Page={%x} !\n", (unsigned long) &km_page_table[0]);
	printf("Page={%x} !\n", (unsigned long) &km2_page_table[0]);
	printf("Page={%x} !\n", (unsigned long) &um_page_table[0]);
	printf("Page={%x} !\n", (unsigned long) &vga_page_table[0]);
	printf("Page={%x} !\n", (unsigned long) &lfb_page_table[0]);
	printf("Page={%x} !\n", (unsigned long) &buff_page_table[0]);
	//refresh_screen();
	//while(1){};

	//
	// CR3:
	// Salvando o endereço do diretório do processo Kernel no CR3. O diretório 
	// do processo Kernel está agora dentro de uma área protegida. Está em 
	// kernel mode.  
	// Obs: Será rotineiro configurar isso cada vez que um processo for 
	// executar ou for criado.
	// Obs: Quando se troca o valor do cr3, a TLB é atualizada pra todas 
	// as entradas. (?? automático)
    //

	SetCR3( (unsigned long) &page_directory[0] );

	//Debug:
	//refresh_screen();
	//while(1){}


	//
    // LISTAS:
	//    Configurando a lista de diretórios e 
	//    a lista de tabelas de páginas.
	//    Salvando na lista o endereço físico dos
	// diretórios e das tabelas de páginas.
	//


	//Inicializar a lista de diretórios de páginas.
	for(Index = 0; Index < PAGEDIRECTORY_COUNT_MAX; Index++){
	    pagedirectoryList[Index] = (unsigned long) 0;
	};

	//O primeiro diretório da lista é o diretório do kernel.
	pagedirectoryList[0] = (unsigned long) &page_directory[0];  //Único por enquanto.
    pagedirectoryList[1] = (unsigned long) 0;
    pagedirectoryList[2] = (unsigned long) 0;
    //...


	//
	// Inicializando a lista de pagetables..
	//
	for(Index = 0; Index < PAGETABLE_COUNT_MAX; Index++){
	    pagetableList[Index] = (unsigned long) 0;
	};


    //Configurando manualmente as primeiras entradas da lista.
	pagetableList[0] = (unsigned long) &km_page_table[0];
	pagetableList[1] = (unsigned long) &km2_page_table[0];
	pagetableList[2] = (unsigned long) &um_page_table[0];
	pagetableList[3] = (unsigned long) &vga_page_table[0];
	pagetableList[4] = (unsigned long) &lfb_page_table[0];
	pagetableList[5] = (unsigned long) &buff_page_table[0];
	pagetableList[6] = (unsigned long) 0;
    //...


	//
	// Inicializando a lista de pageframes.
	//
	for(Index = 0; Index < PAGEFRAME_COUNT_MAX; Index++){
	    pageframesList[Index] = (unsigned long) 0;
	};


	//Configurando manualmente a lista de pageframes.
	pageframesList[0] = (unsigned long) 0;
	pageframesList[1] = (unsigned long) 0;
	//...


	//
	// Inicializando a lista de framepools. (partições)
	//
	for(Index = 0; Index < FRAMEPOOL_COUNT_MAX; Index++){
	    framepoolList[Index] = (unsigned long) 0;
	};


	//Configurando manualmente a lista de pageframes.
	framepoolList[0] = (unsigned long) 0;
	framepoolList[1] = (unsigned long) 0;
	//...


	//
	// Creating kernel space framepool.
	//

	struct frame_pool_d *kfp;

	//kernel framepool.
	kfp = (void*) malloc( sizeof(struct frame_pool_d) );
	if( (void*) kfp != NULL  )
	{
		kfp->id = 0;
		kfp->used = 1;
		kfp->magic = 1234;
		kfp->address = (unsigned long) (0 * MB);   //Comça em 20 MB.
		
		//pertence ao processo kernel.
		kfp->process = (void*) KernelProcess;
		
		kfp->next =  NULL;
		//...

		//salva e ponteiro global.
		framepoolKernelSpace = (void*) kfp;

		//Salva na lista.
		framepoolList[0] = (unsigned long) kfp;
	};


    //
	// Creating user space framepool for small systems..
	//

	struct frame_pool_d *small_fp;

	//kernel framepool.
	small_fp = (void*) malloc( sizeof(struct frame_pool_d) );
	if( (void*) small_fp != NULL  )
	{
		small_fp->id = 1;
		small_fp->used = 1;
		small_fp->magic = 1234;
		small_fp->address = (unsigned long) (4 * MB);   //Comça em 4 MB.

		//pertence ao processo kernel.
		small_fp->process = (void*) NULL; //??;

		small_fp->next =  NULL;
		//...

		//salva e ponteiro global.
		framepoolSmallSystemUserSpace = (void*) small_fp;

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
	pageable_fp = (void*) malloc( sizeof(struct frame_pool_d) );
	if( (void*) pageable_fp != NULL  )
	{
		pageable_fp->id = 5;   //quinto índice.
		pageable_fp->used = 1;
		pageable_fp->magic = 1234;
		pageable_fp->address = (unsigned long) (20 * MB);   //Comça em 20 MB.

		//pertence ao processo kernel.
		pageable_fp->process = (void*) NULL; //??
		
		pageable_fp->next =  NULL;
		//...

		//salva em ponteiro global.
		framepoolPageableSpace = (void*) pageable_fp;

		//Salva na lista.
		framepoolList[5] = (unsigned long) pageable_fp;
	};

	//???	
	//Máximo de indices de quantidades de framepools na área de pagináveis. 	
	//g_pageable_framepool_index_max = PAGEABLE_FRAMEPOOL_MAX;	

	//Usaremos o ultimo maga pra que??? o 32mb.

	//Obs: Tem LFB em 0xE0000000 //Excepcional.(é a memória da placa de vídeo)

	//struct frame_pool_d *frontbuffer_fp; //lfb

	//kernel framepool.
	//frontbuffer_fp = (void*) malloc( sizeof(struct frame_pool_d) );
	//if( (void*) frontbuffer_fp != NULL  )
	//{
		//frontbuffer_fp->id = 5;   //quinto índice.
	//	frontbuffer_fp->used = 1;
	//	frontbuffer_fp->magic = 1234;

		//Obs: Não sei se o endereço do LFB é múltiplo de 4MB.
		//frontbuffer_fp->address = (unsigned long) SavedLFB; //Talvez 0xe0000000;   

		//pertence ao processo kernel.
	//	frontbuffer_fp->process = (void*) NULL; //??

	 //   frontbuffer_fp->next =  NULL;
		//...

		//salva em ponteiro global.
	//	framepoolFrontBuffer1 = (void*) frontbuffer_fp;

		//Salva na lista.
		//framepoolList[??] = (unsigned long) frontbuffer_fp;
	//};	


	// **** Estamos atuando em uma memória de 32MB por enquanto.

	//
	// More?!
	//

// Done.
done:
	printf("Done!\n");
    return (int) 0;
};


//
// End.
//

