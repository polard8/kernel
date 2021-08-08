

#ifndef __X64MM_H
#define __X64MM_H    1



// The virtual address of the kernel pml4 table.
unsigned long gKernelPML4Address; 

// Some useful data for memory management.

struct mm_data_d
{
    int used;
    int magic;

    unsigned long pml4_va; 
    unsigned long pml4_pa; 

    // We just need one table to handle a basic initialization.

    // Saving the pointer for the first table.
    unsigned long pdpt0_va; 
    unsigned long pdpt0_pa; 

    // We just need one table to handle a basic initialization.

    // Saving the pointer for the first table.
    unsigned long pd0_va; 
    unsigned long pd0_pa; 
};

// Kernel process.
struct mm_data_d kernel_mm_data;
// Init process.
struct mm_data_d init_mm_data;
// A new process been created.
struct mm_data_d newprocess_mm_data;
// ...





//
// == zones ==================================================
//

// Memoria total em duas partes.


//system zone. 
struct system_zone_d
{
    unsigned long systemzone_start;  //0x00000000. s�o os 32MB iniciais  
};
struct system_zone_d *systemzone;

//window zone.  
//#bugbug: maybe it is not a good name.
struct window_zone_d
{
	unsigned long windowzone_start;
	//Endere�o onde come�a a user session.
	unsigned long usersession_start;	//ficar� dentro de uma �rea paginada.
    struct usession_d *usersession;    
};
struct window_zone_d *windowzone;


//Zones.
// ** ESSA ESTRUTURA � A RAIZ DE TODA GER�NCIA DE MEM�RIA **
struct mm_zones_d
{
    struct system_zone_d *system_zone;  //Essa zona � para o sistema.
    struct window_zone_d *window_zone;  //Essa zona toda � uma user session.
};
struct mm_zones_d *zones;



//===============================================================

// vari�veis blobais de endere�os usados no gerenciamento de zonas de mem�ria.

#define SYSTEMZONE_START 0
#define SYSTEMZONE_END   0x0FFFFFFF 
#define WINDOWZONE_START 0x10000000
//#define WINDOWZONE_END ??

unsigned long systemzoneStart;
unsigned long systemzoneEnd;
unsigned long systemzoneSize;
unsigned long windowzoneStart;
unsigned long windowzoneEnd;    //?? Devemos levar em considera��o o calculo do tamanho da mem�ria
unsigned long windowzoneSize;




/*
 * page_directory_d:
 *     Estrutura para o 'page directory' de um processo.
 *
 *     Todo processo tem seu pr�prio diret�rio de p�ginas.
 *     Assim v�rios processos podem usar o mesmo endere�o l�gico.
 *     Ex: 0x400000
 *     @todo: Um ponteiro para essa estrutura pode estar no PCB do processo.
 *            usar os processos criados por processos para testar a configura��o
 *           de page directory.
 *     Obs: Um diret�rio tem ponteiros para page tables. as page tables 
 * funcionam como pools de frames.
 */


//typedef struct page_directory_d page_directory_t;
struct page_directory_d
{
    object_type_t  objectType;
    object_class_t objectClass;

	//identificadores.
    int id;
    int used;
    int magic;
	
	//Qual processo � o dono do diret�rio de p�ginas.
	//talvez seja possivel reaproveitar o diret�rio.
    struct process_d *process;
	
	//Endere�o onde ficar� o diret�rio de p�ginas.
	//Obs: Para configurar um diret�rio de p�ginas talvez
	//tenha que colocar um endere�o f�sico em CR3. Lembre-se
	//que o malloc do kernel base aloca mem�ria no heap do 
	//processo kernel que fica no �ltimo giga da mem�ria virtual.
    unsigned long Address;
	
	
	// ?? struct page_directory_entry_d[1024] ??
	
	//@todo: Mais informa��es sobre o diret�rio de p�ginas.
	
	//Pr�ximo diret�rio, significa pr�ximo processo.
	//significa processos ligados em um job.
    struct page_directory_d *next;  
};

struct page_directory_d *pagedirectoryKernelProcess;    // KERNEL.
struct page_directory_d *pagedirectoryIdleProcess;      // IDLE.
struct page_directory_d *pagedirectoryCurrent;          // Current.
struct page_directory_d *pagedirectoryShared;           // Shared. 
//...


//
// Lista de diret�rios. (Pois cada processo tem um diret�rio).
//

// Quantidade de diretórios que podem ser criados na lista.
#define PAGEDIRECTORY_COUNT_MAX 1024  

//Lista de estruturas para diret�rios de p�ginas.
unsigned long pagedirectoryList[PAGEDIRECTORY_COUNT_MAX]; 


// ------------


/*
 * page_table_d.
 *     Page table structure.
 *     Obs: Uma page table funciona como um pool de frames.
 *          Tamb�m pode ser compartilhada entre processo.(cuidado).
 */

//typedef struct page_table_d page_table_t;
struct page_table_d
{
    object_type_t  objectType;
    object_class_t objectClass;

    int id;
    int used;
    int magic;
	
	//A qual diret�rio de p�ginas a page table perrtence.
	//se bem que talvez possamos usar a mesma pagetable
	//em mais de um diret�rio. ser�??
    struct page_directory_d *directory;
	
	//Cada pagetable pertence � um processo.
    struct process_d *process;
	
	//Travando uma pagetable inteira,
	//nenhuma de suas p�ginas poder�o se descarregadas
	//para o disco de swap.
    int locked;
	
	// ?? struct page_table_entry_d[1024] ??
	
    //@todo: Mais informa��es sobre a pagetable.
    struct page_table_d *next;
};

struct page_table_d *pagetableCurrent;
//...

//
// Lista de pagetables.
//

// Quantidade de page tables criadas na lista.
#define PAGETABLE_COUNT_MAX  1024 


unsigned long pagetableList[PAGETABLE_COUNT_MAX]; 

//Linked List talvez seja uma op��o.
//page_table_t *pagetableLinkedListHead;



// ------------

/**
 **  **  SUPER IMPORTANTE  **
 **
 ** Super block.
 ** ESSAS VARI�VEIS GLOBAIS MARCAR�O O IN�CIO E O FIM 
 ** DA �REA DE MEM�RIA F�SICA DESTINADA AOS FRAMES DE MEM�RIA 
 ** F�SICA QUE SER�O USADOS PELO GERENCIADOR DE P�GINAS.
 **
 ** Pertencer�o ao banco FDB. (Free Data Base).
 ** 0x10000000 � um bom lugar pra come�ar os frames ,
 ** na verdade os blocos 4MB, pois cada bloco de 4MB pode ser mapeado 
 ** usando apenas uma pagetable.
 ** 
 ** mmFramesSuperBlockStart = 0x10000000
 ** mmFramesSuperBlockEnd   = 0x1FFFFFFF
 ** 
 ** Esses s�o endere�os f�sicos.
 ** Obs: Ficar�o nesse lugar caso se tenha mem�ria dispon�vel para isso.
 **
 **/

// Frames Super Block.
// Vari�veis globais parecem ser uma op��o melhor de estrutura
// para esse caso. 
// Obs: Temos listas de frames em algum lugar. 
// Criaremos listas aqui para o FSB, que ser� o nome do gerenciado, 
// para melhorar o controle dessa �rea.
unsigned long mmFramesSuperBlockStart;      //Endere�o onde come�a o FSB.
unsigned long mmFramesSuperBlockEnd;        //Endere�o onde termina o FSB.
unsigned long mmFramesSuperBlockSize;       //Tamanho do FSB dado em bytes.
unsigned long mmFramesSuperBlockTotal;      //Total de frames.
unsigned long mmFramesSuperBlockTotalFree;  //Total de frames livres. 
unsigned long mmFramesSuperBlockTotalUsed;  //Total de frames e uso. 
//Continua...

// ((0x1FFFFFFF - 0x10000000) / 512)  = QUANTIDADE DE FRAMES NESSA �REA.
#define FSB_FRAMES_MAX      (1*1024) //?? @todo: Determinar melhor isso
#define FSB_FREEFRAMES_MAX  (1*1024) //?? @todo: Determinar melhor isso

//## BUGBUG isso tornaria esse array bem grande.


//
// Lista com todos.
//


//Lista de ponteiros para as estruturas de todos os frames do FSB.
unsigned long fsbFrames[FSB_FRAMES_MAX]; 

//
// Lista de livres.
//

//Lista de ponteiros para as estruturas de todos os frames 'LIVRES' do FSB.
unsigned long fsbFreeFrames[FSB_FREEFRAMES_MAX];  
 
 



//
// memory:
//

 
 
//
// MM BLOCK.
// 

//Isso � usdo pelo heap.
//#define MMBLOCK_HEADER_SIZE  64 
#define MMBLOCK_HEADER_SIZE  128


// #bugbug
// @todo: Aumentar ...
// Contagem de mmblock. 
#define MMBLOCK_COUNT_MAX  (2*4096)



// Quantidade m�xima de framepools.
// Um framepool � uma parti��o da mem�ria f�sica.
// Cada framepool � composto de 1024 pageframes.
//
// @todo: 
// #bugbug: 
// A quantidade de framepools deve ser equivalente � quantidade 
// de mem�ria f�sica dispon�vel.
// Por isso devemos criar �reas de mem�ria f�sica aloc�veis. O que 
// facilita a manuten��o de listas de framepools.
//
// Em outras palavra. Temos que concatenar parti��es de mem�ria f�sica
// pra facilitar. Ent�o chamaremos essa �rea onde est�o as parti��es de
// �rea pagin�vel. Pois existem �res de mem�ria que n�o s�o pafin�veis,
// elas simplesmente foram mapeadas para que alguma parte do sistema use.
//
// @todo: 
// Criar um ponteiro que indique o �n�cio da �rea p�gin�vel, assim como 
// acontece com o in�cio de um heap.
//
// � principio todo processo poderia ter acesso � apenas uma parti��o.
// Um framepool � garantido para um processo quando esse processo � criado
// mesmo antes de haver algum mapeamento. Na verdade um processo ter� uma lista
// de framepools.
//


//List.(1024 framepools de 4MB d� 4GB).
#define FRAMEPOOL_COUNT_MAX 1024




//
// ## MEMORY PARTITION ##
//

//Um framepool tem 4MB de tamanho.
#define MEMORY_PARTITION_SIZE (4 * MB)



// Obs: Criamos apenas algumas entradas no diret�rio de p�ginas
// do kernel, mas algumas dessas entradas ser�o iguais para todos 
// os processos. Ent�o os diret�rios de da p�ginas dos processos
// ser�o configurados de forma semelhante.

//
// Page frames da imagem do kernel:
// ================================
// Foram alocadas 1024 pageframes para a imagem do kernel.
// Isso equivale a um pageframe pool. Que � igual a 4MB. Pois
// s�o 1024 page frames de pag�nas de 4KB cada.
//

//
// + kernel area = 1024 page frames (4MB)
// + kernel image = 1024 pageframes (4MB)
// + user mode area = 1024 pageframes (4MB)
// + vga = 1024 pageframes (4MB) (Isso transpassa o real tamanho da vga)
// + lfb = (frontbuffer) 1024 pageframes (4MB) (Isso � muito pouco, pois 
//         uma placa de v�deo tem mais mem�ria que isso)
// + backbuffer = 1024 pageframes (4MB) (Isso realmente � pouco, o backbuffer 
//         deve caner uma imagem grande, que ser� dividade em v�rios monitores.)
//
//


/*
INVLPG

INVLPG is an instruction available since the i486 that invalidates a single page in the TLB. 
Intel notes that this instruction may be implemented differently on future processes,
 but that this alternate behavior must be explicitly enabled. INVLPG modifies no flags.

NASM example:

     invlpg [0]
Inline assembly for GCC (from Linux kernel source):

static inline void __native_flush_tlb_single(unsigned long addr)
{
   asm volatile("invlpg (%0)" ::"r" (addr) : "memory");
}

*/

/*
typedef enum {
    MM_SYSTEM_SMALL,
    MM_SYSTEM_MEDIUM,
	MM_SYSTEM_BIG,
}SYSTEM_SIZE_T;
*/


/*
 * mmblockCount:
 *     mm block support.
 *     Conta os blocos de mem�ria dentro de um heap.
 *     *dentro do heap usado pelo kernel eu acho ?? 
 */

unsigned long mmblockCount;



/*
 * Kernel Stack suppport.
 */ 

unsigned long kernel_stack_end;        //va
unsigned long kernel_stack_start;      //va
unsigned long kernel_stack_start_pa;   //pa (endere�o indicado na TSS).






/*
 * process_memory_info_d:
 *
 *     Estrutura para informa��es sobre a mem�ria utilizada por um processo.
 * Obs: 
 * O gerenciamento de mem�ria � tarefa do m�dulo /sm portanto isso n�o deve 
 * ir para o /microkernel.
 */

struct process_memory_info_d
{
    object_type_t  objectType;
    object_class_t objectClass;


    struct process_d *process;
	
	//valor em KB. (quantidade de p�ginas + tamanho da p�gina.)
	
    unsigned long WorkingSet;  //Working Set.
    unsigned long Private;     //Mem�ria n�o compartilhada. 
    unsigned long Shared;	   //Mem�ria compartilhada.
	//...
	
	
	//unsigned long pageFaults; //Contagem de faltas.
	//Pico de Working Set.
	//??delta de conjunto de trabalho.
	//...
};
struct process_memory_info_d *pmiCurrent;
//...



/*
 * physical_memory_info_d:
 *
 *     Informa��es sobre a mem�ria f�sica.
 *     O arquivo system.h deve usar isso. 
 */

struct physical_memory_info_d
{
	object_type_t objectType;
	object_class_t objectClass;
	
	//?? d�vidas.
	unsigned long Total;     //Total de mem�ria f�sica.(RAM).
	unsigned long InCache;   //Parte do total que est� em cache.(foi paginada e est� em cache).
	unsigned long Free;      //Livre.(Existe na RAM mas n�o foi paginada??).
    //...	
};
struct physical_memory_info_d *pmiMemoryInfo;
//...



/*
 * memory_info_d:
 *     Informa��es sobre a mem�ria.
 *     Isso pode ser usado pela configura��o do sistema. 
 */

struct memory_info_d
{
	object_type_t objectType;
	object_class_t objectClass;
	
    //Physical.
	unsigned long TotalP;
    unsigned long AvailableP;
    
	//Virtual
	unsigned long TotalV;
    unsigned long AvailableV;
};
struct memory_info_d *miMemoryInfo;
//...



/*
 *****************************************************************
 * mmblock_d:
 *     Estrutura para memory blocks.
 *     Temos v�rios blocos de mem�ria espalhados em lugares diferentes 
 * dentro de um heap.
 *     Essa estrutura � usada pelo kernel para controlar as �reas de mem�ria
 * alocadas din�micamente dentro do heap do kernel. Por�m poderemos
 * usar essa mesma estrutura para alocar mem�ria em outros heaps. Como o heap 
 * de um processo ou o heap de um desktop. @todo: Para isso essa estrutura 
 * poderia conter informa��es sobre qual heap estamos usando. Mas me parece 
 * que o tamanho do header deve ser fixo.
 *
 * @todo: 
 * Os blocos precisam de alguma organiza��o. 
 * Por enquanto, o total � 256 heaps de tamanhos diferentes.
 *
 * Os blocos formar�o uma lista encadeada que ser� percorrida para se 
 * encontrar um bloco vazio. (walk).
 *
 * *Importante: A mem�ria ser� organizada em bancos, que conter�o mem�ria 
 * privada e mem�ria compartilhada. Os blocos de mem�ria e os heaps 
 * precisam estar associadoas aos bancos, que conter�o informa��es sobre 
 * processos e usu�rios. @todo:
 * Obs: Os bancos est�o definidos em bank.h
 * 
 * Obs: Um heap de processo tem v�rios blocos dentro.
 *
 * *IMPORTANTE: 
 *     Talvez tenhamos algum limite para o tamanho dessa estrutura 
 * em especial. (N�o incluir nenhuma vari�vel por enquanto!).
 *****************************************************************
 */ 


struct mmblock_d 
{
	
	// Essa estrutura � para gerenciar �reas de mem�ria alocadas dinamicamente 
	// dentro do heap do processo kernel. Alocadas em tempo de eecu��o.
	
	// @todo: 
	// Talvez n�o seja poss�vel mudar essa estrutura. �la � diferente.
	// Portanto n�o definiremos inada o tipo de objeto que ela � e nem a classe.
	
	//object_type_t objectType;
	//object_class_t objectClass;
	
    //Identificadores.	
	unsigned long Header;      //Endere�o onde come�a o header do heap. *Importante.
	unsigned long headerSize;  //Tamanho do header em bytes.
	unsigned long Id;          //Id do header.
	unsigned long Used;        //Flag 'usado' ou 'livre'.
	unsigned long Magic;       //Magic number. Ver se n�o est� corrompido.
	
	//Status.
	unsigned long Free;           //Se o bloco esta livre ou n�o.
	
	//Mensuradores. (sizes).	
	unsigned long requestSize;    //Tamanho, em bytes, da �rea solicitada.
	unsigned long unusedBytes;    //Quantidade de bytes n�o usados na �rea do cliente.	
	unsigned long userareaSize;   //Tamanho da �rea reservada para o cliente. 
	                              //(request size + unused bytes). 
								  
	//@todo: 
    //    Incluir quando poss�vel.
    // Lembrando que talvez o tamanho dessa estrutura seja fixo.
    // Talvez n�o mudaremos nada no tamanho dela.	
    //struct heap_d *heap;

//
// User area
//

    // (Onde come�a a �rea solicitada).

    unsigned long userArea;    //In�cio da �rea alocada.


//
// Footer
//
    unsigned long Footer;    //Endere�o do in�cio do footer.

//
// Process
//

    //pid_t pid;  //#todo
    int processId;  // pid
    struct process_d  *process;


	// Continua ?? ... 
	// Talvez n�o pode.
	
	// IMPORTANTE: 
	// Talvez temos algum limite para o tamanho dessa estrutura em especial. 
	// N�o inluir nada por enquanto.

    // Navigation
    struct mmblock_d *Prev;
    struct mmblock_d *Next;
};
struct mmblock_d *current_mmblock;

 
//Lista de blocos. 
//lista de blocos de mem�ria dentro de um heap.
//@todo: na verdade temos que usar lista encadeada. 
unsigned long mmblockList[MMBLOCK_COUNT_MAX];  



/*
 ****************************************************************
 * page_d:
 *     Guarda informa��es sobre um 'page frame' na mem�ria f�sica.
 *     @todo: Incluir todas as informa��es necess�rias.
 */

struct page_d
{
	
	//identificador da estrutura.
	//� um �ndice na lista de p�ginas do pagedpool.

    int id;
    int used;
    int magic;
	
	// Identificador de frame.
	// (pa/4096)

    int frame_number;

    // Locked:
    // Não pode ser descarregado para o disco.
    // Não pode ser alterado.
    int locked;

    // A página está livrea para uso pelos processos.
    int free;

    // Contador de referências.
    int ref_count;

    // Navigation
    struct page_d *next;
};

// #importante
// Pool de memória paginável usado para alocação.
// Aqui ficam os ponteiros para estrutura do tipo page.

#define PAGE_COUNT_MAX   1024    //??

unsigned long pageAllocList[PAGE_COUNT_MAX];




/*
 * frame_pool_d:
 *     Estrutura para uma parti��o da mem�ria f�sica.
 *     Uma parti��o da mem�ria f�sica � chamada de framepool.
 *     Cada framepool tem 1024 frames.
 *     @todo: Poderia ser framepool_d ??
 */

struct frame_pool_d
{
	//object_type_t objectType;
	//object_class_t objectClass;
	
	//�ndice na lista de frame pools;

    int id;
    int used;
    int magic;

	//N�o pode ser modificada.
    int locked;
	
	//Endere�o do in�cio do framepool.
	// va ou pa ??
	unsigned long address; 
	
	//Qual processo � o dono desse framepool.
    struct process_d *process;

    // Navigation
    struct frame_pool_d *next;
};

//
// Cada framepool abaixo � o framepool inicial de uma regi�o.
// Uma regis�o pode ter v�rios framepools.
//

//kernel space.
struct frame_pool_d *framepoolKernelSpace;            //0x00000000  Kernel Space. In�cio do kernel space.

//user space
struct frame_pool_d *framepoolSmallSystemUserSpace;   //0x00400000  Para um sistema pequeno o kernel space tem 4MB.
struct frame_pool_d *framepoolMediumSystemUserSpace;  // 
struct frame_pool_d *framepoolLargeSystemUserSpace;   //0x40000000  Para um sistema grande o kernel space tem um giga. 
//...

//Cada front buffer � uma placa de v�deo.
struct frame_pool_d *framepoolFrontBuffer1;   //In�cio do linear frame buffer 1.
struct frame_pool_d *framepoolFrontBuffer2;   //In�cio do linear frame buffer 2.
struct frame_pool_d *framepoolFrontBuffer3;   //In�cio do linear frame buffer 3.
struct frame_pool_d *framepoolFrontBuffer4;   //In�cio do linear frame buffer 4.
//...

//Backbuffer
struct frame_pool_d *framepoolBackBuffer1;   //In�cio do backbuffer.
struct frame_pool_d *framepoolBackBuffer2;   //In�cio do backbuffer.
struct frame_pool_d *framepoolBackBuffer3;   //In�cio do backbuffer.
struct frame_pool_d *framepoolBackBuffer4;   //In�cio do backbuffer.
//...


//�rea onde poderemos alocar frames para os processos usarem...
//Esse � o framepool inicial de usa �re grande de mem�ria.
struct frame_pool_d *framepoolPageableSpace;   


//Current.
struct frame_pool_d *framepoolCurrent;
//...

//struct frame_pool_d *framepoolKernelPagedPool;
//struct frame_pool_d *framepoolKernelNonPagedPool;
//struct frame_pool_d *framepoolUserPagedPool;
//struct frame_pool_d *framepoolUserNonPagedPool;

//
//   **** PAGEABLE AREA ****
//



unsigned long gPagedPollStart;
unsigned long gPagedPollEnd;


//Obs: ISSO � UM TESTE.
//N�mero m�ximo de framepools na �rea de aloca�ao de frames.
//Obs: Isso � uma esp�cie de cache. Por�m cache � coisa de disco.
//
// ( 1 * 4MB) =   4 MB.
// ( 2 * 4MB) =   8 MB. (Usando esse num sistema de 32mb de ram).
// ( 4 * 4MB) =  16 MB.
// ( 8 * 4MB) =  32 MB.
// (16 * 4MB) =  64 MB.
// (32 * 4MB) = 128 MB.
//



//#define PAGEABLE_FRAMEPOOL_MAX 1
#define PAGEABLE_FRAMEPOOL_MAX 2          //usando 8 MB para frames sob demanda.
//#define PAGEABLE_FRAMEPOOL_MAX 4
//#define PAGEABLE_FRAMEPOOL_MAX 8
//#define PAGEABLE_FRAMEPOOL_MAX 16
//#define PAGEABLE_FRAMEPOOL_MAX 32


//
// N�mero m�ximo de �ndices de framepool que ser�o usados nessa �rea de 
// aloca��o de frames.
// *** Uma certa quantidade de framepools ser�o usados
// para aloca��o de frames para os processos. Durante
// a aloca��o sobre demanda os frames usados vir�o dessa �rea de mem�ria.
//
//
//

int g_pageable_framepool_index_max;


//List.(1024 framepools de 4MB d� 4GB).
unsigned long framepoolList[FRAMEPOOL_COUNT_MAX];



//Lista de framepools livres.
//int framepoolFreeList[FRAMEPOOL_COUNT_MAX]
//frame_pool_t *framepoolFreeListHead;



//frame pool atual.
int g_current_framepool;


//o indice do framepool da user space para qualquer tamanho de mem�ria.
int g_user_space_framepool_index;


//O m�ximo de framepools poss�veis dado o tamanho da mem�ria f�sica.
unsigned long g_framepool_max;


//Tamanho m�ximo da mem�ria f�sica.
unsigned long g_total_physical_memory;



//Contabilidade. kernel(talvez deva fazer uma estrututra) MS.
//Mem�ria usada pelo kernel.
//+Paginada. paged
//+n�o paginada. nonpaged
//+fisica paginada
//+virtual paginada 
//+paginada limite
//+na� pagianda limite.
//
unsigned long g_kernel_paged_memory;
unsigned long g_kernel_nonpaged_memory;




// **** GERENCIA DE MEM�RIA F�SICA. ****
//MS - Windows 
// +Resevada para hardware.
// +Em uso.
// +Modificada. 
// +Em espera.
// +Livre.
// ?? Aqui n�o conta a mem�ria de v�deo, somente o tamanho da mem�ria ram f�sica.
// A mem�ria de v�deo est� normalmente no topo da mem�ria f�sica real. Endere�o 
// al�m do tamanho da mem�ria ram.
//


// **** GERENCIA DE MEM�RIA F�SICA. ****
//MS - Windows 
// + Total.
// + Em cache.
// + Dispon�vel.
// + Livre.
//





// Tipo de sistema baseado no tamanho da memoria.
typedef enum {

    stNull,
    stSmallSystem,
    stMediumSystem,
    stLargeSystem,

}mm_system_type_t;


//salva o tipo de sistema baseado no tamanho da mem�ria.
int g_mm_system_type;


//
// ## Physical memory ##
//

// Small systems.
unsigned long SMALL_origin_pa;
unsigned long SMALL_kernel_base_pa;
unsigned long SMALL_user_pa;
unsigned long SMALL_cga_pa;
unsigned long SMALL_frontbuffer_pa;
unsigned long SMALL_backbuffer_pa; 
unsigned long SMALL_pagedpool_pa; 
unsigned long SMALL_heappool_pa; 
unsigned long SMALL_extraheap1_pa;
unsigned long SMALL_extraheap2_pa; 
unsigned long SMALL_extraheap3_pa; 
//...

// Medium systems.
unsigned long MEDIUM_origin_pa;
unsigned long MEDIUM_kernel_base_pa; 
unsigned long MEDIUM_user_pa; 
unsigned long MEDIUM_cga_pa; 
unsigned long MEDIUM_frontbuffer_pa; 
unsigned long MEDIUM_backbuffer_pa; 
unsigned long MEDIUM_pagedpool_pa;  
unsigned long MEDIUM_heappool_pa; 
unsigned long MEDIUM_extraheap1_pa;
unsigned long MEDIUM_extraheap2_pa; 
unsigned long MEDIUM_extraheap3_pa; 

// Large systems.
unsigned long LARGE_origin_pa;
unsigned long LARGE_kernel_base_pa;
unsigned long LARGE_user_pa;
unsigned long LARGE_cga_pa;
unsigned long LARGE_frontbuffer_pa;
unsigned long LARGE_backbuffer_pa;
unsigned long LARGE_pagedpool_pa; 
unsigned long LARGE_heappool_pa;
unsigned long LARGE_extraheap1_pa;
unsigned long LARGE_extraheap2_pa; 
unsigned long LARGE_extraheap3_pa; 






//base     = base memory retornada pelo cmos
//other    = (1MB - base). (Shadow memory = 384 KB)
//extended = retornada pelo cmos.
//total    = base + other + extended.

unsigned long memorysizeBaseMemory;
unsigned long memorysizeOtherMemory;
unsigned long memorysizeExtendedMemory;
unsigned long memorysizeTotal;

unsigned long memorysizeInstalledPhysicalMemory;

unsigned long memorysizeTotalPhysicalMemory;
unsigned long memorysizeAvailablePhysicalMemory;

//??
// Quantidade de mem�ria em uso.
unsigned long memorysizeUsed;

//??
//Quantidade de mem�ria livre.
// ? = total - used.
unsigned long memorysizeFree;


//========================================================

// Used memory:
// Estamos medindo o uso de memória física.
// Lembrando que a mesma região de memória física
// pode ser mapeada mais de uma vez.

// #todo #bugbug
// Precisamos checar corretamente qual é o endereço físico
// de cada uma dessas regiões e suas sobreposições.
unsigned long mm_used_ring0_area;  // start = 0 size = 4MB
unsigned long mm_used_ring3_area;  // start = 0x400000 size = 4MB
unsigned long mm_used_kernelimage;
unsigned long mm_used_backbuffer;  // start = 0x800000 size = 4MB
unsigned long mm_used_pagedpool;   // start = 0xC00000 size = 4MB  
unsigned long mm_used_heappool;    // start = 0x01000000 size = 4MB   
unsigned long mm_used_extraheap1;  // start = (0x01000000 + 0x400000) size = 4MB
unsigned long mm_used_extraheap2;  // start = (0x01000000 + 0x800000) size = 4MB
unsigned long mm_used_extraheap3;  // start = (0x01000000 + 0xC00000) size = 4MB
unsigned long mm_used_frame_table;


// #bugbug
// Só pra lembrar que temos estruturas de bancos de memória.
// eles deverão ser usados no futuro.

// #importante
// Como é uma tabela de bytes,
// 0 pode indicar livre e um valor acima de zero
// pode indicar o número de processos que
// estão compartilhando a mesma página.

struct frame_table_d 
{
    unsigned char *frame_table;
    int frame_table_status;

    unsigned long frame_table_start; // 0x02000000 - 32mb mark. 
    unsigned long frame_table_end;
    unsigned long frame_table_size_in_bytes;

    int total_frames;
    int n_pages;

    int total_free;
    int total_used;
};

// frame table struct.
struct frame_table_d FT;




// #test

//
// Frame structure.
//

// This structure is gonna handle a free frame.
struct frame_d
{
    pid_t owner;

    int count; //reference count.

    int age; //reference time.

    unsigned long virtual_address;

    // O número da entrada na tabela FT.frame_table[entry_number].
    // Também é o índice que representa o offset de lba
    // no armazenamento secundário.
    int entry_number;
    
    // Se esse frame está no disco.
    // Isso significa que o frame pode ser considerado livre.
    // The pointer is in the SWAPPED_FRAMES[] list.
    int swapped;
};


// O armazenamento secundário pode ser um arquivo
// ou uma partição de swap.

// 1024 frames de fácil acesso.
// pode ser usado pra alocar rapidamente memória para um novo processo.
// NULL = entrada vazia
// !NULL = ponteiro para a estrutura do tipo free_frame_d.

// Lista de processos livres.
// Isso facilita, possivelmente evitando a busca 
// na tabela global FT.frame_table[]
struct frame_d FREE_FRAMES[1024];

//This entries are in the disk.
struct frame_d SWAPPED_FRAMES[1024];

// Maybe we can have more lists here.
// ...




// ...


unsigned long mm_used_lfb;          // start = ?? size = 4MB

//#todo
//unsigned long mm_used_
//more ...


//
//  ## virtual memory ##
//

unsigned long memorysizeTotalVirtualMemory;
unsigned long memorysizeAvailableVirtualMemory;


// Tamanho dado em bytes.
#define SMALLSYSTEM_SIZE  ( 32*1024*1024)
#define MEDIUMSYSTEM_SIZE ( 64*1024*1024)
#define LARGESYSTEM_SIZE  (128*1024*1024)

// Tamanho do sistema, dado em KB.
#define SMALLSYSTEM_SIZE_KB  ( 32*1024)
#define MEDIUMSYSTEM_SIZE_KB ( 64*1024)
#define LARGESYSTEM_SIZE_KB  (128*1024)

// #todo
// Tamanho do sistema, dado em MB.
//#define SMALLSYSTEM_SIZE_MB  ( 32)
//#define MEDIUMSYSTEM_SIZE_MB ( 64)
//#define LARGESYSTEM_SIZE_MB  (128)


// Tamanho so sitema, dado em quantidade de p�ginas de 4KB.
#define SMALLSYSTEM_SIZE_PAGES  ( ( 32*1024*1024) / 4096 )
#define MEDIUMSYSTEM_SIZE_PAGES ( ( 64*1024*1024) / 4096 )
#define LARGESYSTEM_SIZE_PAGES  ( (128*1024*1024) / 4096 )



//
// == prototypes =================================================
//



void *CreateAndIntallPageTable (
    unsigned long pml4_va,   // page map level 4
    unsigned long pml4_index,
    unsigned long pdpt_va,   // page directory pointer table
    unsigned long pdpt_index,
    unsigned long pd_va,     // page directory 
    int pd_index,            // Install the pagetable into this entry of the page directory. 
    unsigned long region_pa );


int 
mm_fill_page_table( 
    unsigned long directory_va, 
    int           directory_entry,
    unsigned long pt_va,
    unsigned long region_2mb_pa,
    unsigned long flags );

int mmSetUpPaging (void);

int init_heap (void);
int init_stack (void);

int mmInit(void);

unsigned long heapAllocateMemory ( unsigned long size );
void FreeHeap (void *ptr);

// ============

void memoryShowMemoryInfo (void);
void mmShow_PML4Entry (int index, unsigned long pml4_va);
void mmShowPML4EntryForAllProcesses (int entry_number);
void showFreepagedMemory ( int max );
void show_memory_structs (void);
void testingPageAlloc (void);


// ==

int kernel_gc (void);



unsigned long get_new_frame (void);
unsigned long alloc_frame(void);

// #danger
unsigned long get_table_pointer (void);


void load_pml4_table(void *phy_addr);


void *CloneKernelPDPT0(void);
void *CloneKernelPD0(void);
void *CloneKernelPML4 (void);
void *clone_pml4 ( unsigned long pml4_va );

int initialize_frame_table (void);

int pEmpty (struct page_d *p);
void freePage (struct page_d *p);
void notfreePage (struct page_d *p);



// Wrapper
unsigned long 
virtual_to_physical ( 
    unsigned long virtual_address, 
    unsigned long pml4_va );

// Worker
unsigned long 
__virtual_to_physical ( 
    unsigned long virtual_address, 
    unsigned long pml4_va );



// #todo
void pages_calc_mem (void);


void *page (void);

// #todo
// #fixme
void *newPage (void);

void *mm_alloc_single_page (void);
void *mm_alloc_contig_pages (size_t size);


int firstSlotForAList ( int size );

void *allocPages (int size);

void initializeFramesAlloc (void);

#endif    













