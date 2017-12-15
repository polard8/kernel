/*
 * File: pc\mm\mm.h  
 *
 * Descrição:
 *     Header para o Memory Manager. Gerenciamento de memória.
 *
 * Ordem de importância do gerenciamento de memória:
 *     > Endereços dos page directories.
 *     > Endereços das pagetables. 
 *     > 
 *
 * Obs:
 *     Em executive, temos áreas de memórias reservadas para o sistema. 
 * Privilégios de executivo.
 *
 * @todo: 
 *     Criar blocos livres e alocados. 
 *     1 - Linked List of free blocks.
 *     2 - Procurar por blocos livres de tamanho suficiente para a alocação. 
 *     3 - Memory Pool, pre aloca blocos de tamanho fixo, ex: 4096.
 *     Estrutura e manipulação de 'page frames'.
 *     ...
 * @todo: + Mapping kernel mode memory into user address space.
 *          Dentro do espaço disponível para o usuário, ele poderá
 *          ler um conteúdo colocado pelo kernel para ele.
 *          Isso é uma área de transferência. 
 *
 * Histórico:
 *     Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *     Versão 1.0, 2016 - Revisão.
 *     ...
 */

/*
    Sobre 'pages' e 'page frames':
	============================
	pages: 
	    São blocos de memória virtual. 
		?? São blocos de disco equivalentes aos blocos de memória física.??
		
    pageframes: 
	    São blocos na memória física equivalentes aos blocos do disco.
 */ 
 
 
/*
    Memory map:
    (process page directory).	
	
	" Cada processo tem seu diretório e uma configuração de 4GB de memória 
virtual. Essa é a memória virtual para processos criados, uma padronização que
será respeitada na hora de criar o diretório de páginas de um processo ".	
	" Note que o início da memória virtual está disponível para drivers ou 
bibliotecas de link dinâmico ".   
	" Todo processo começará em 0x00400000vir e terá o entry point em 
0x00401000virt ". "Bibliotecas de ligação dinâmica, começarão em 0x0vir
e não sei se essas bibliotecas tem entry point"
		
	//...
	
 @todo: 	
     " O ideal é que um processo tenha disponível pra si toda a área baixa de 
memória virtual, até o início da área do kernel".
     "A divisão da memória virtual do processo entre a parte que pertence ao 
processo e a parte que pertence ao kernel tem seguido o seguinte padrão:
(1) meio à meio, onde o processo fica com os 2GB mais baixos e o kernel fica 
com os 2GB superiores, ou (2) O processo fica com os 3GB mais baixos e o
kernel fica com o 1GB superior."	 


    Mapeamento padrão de memória virtual para todos os processos do sistema:
    =======================================================================	


		     +------------------------------------+
	FFFFFFFF |             FIM                    |
		     +------------------------------------+
		     +------------------------------------+
		     +------------------------------------+ 
		     +------------------------------------+
	         |           Kernel land              | @todo:   
		     |                                    | Mudar de lugar.         
		     |                                    | Seder espaço para LFB, que precisa ser grande.
    C0800000 |           BackBuffer               |  			 
		     +------------------------------------+	
	         |           Kernel land              |	 Memória da placa de vídeo.
		     |             (4MB)                  |  @todo: 
			 |             ...                    |  Ampliar (TER O TAMANHO DA MEMÓRIA DA PLACA DE VÍDEO) 
	C0400000 |          FrontBuffer(LFB)          |  Obs: Tamanho da soma das áreas dos monitores, no mínimo.
		     +------------------------------------+
			 +====================================+
             |           Kernel land              |
	         |                                    | 
             |  Stack = 0xC0300000 ~ 0xC03FFFF0   | Pilha do Kernel. 
	         |  Heap  = 0xC0100000 ~ 0xC02FFFF0   |	Obs: O Heap do kernel precisa ser maior.
             |                                    | 			 
			 |  Kernel Entry point = 0xC0001000   |      Entry point do kernel.
	         |  Kernel Base = 0xC0000000          |	     Início da imágem do processo kernel. 
	C0000000 |         Kernel Mode access         |	 	   
	         +------------------------------------+
             |           User Land                |
		     +------------------------------------+
		     +------------------------------------+ 
		     +------------------------------------+
		     +------------------------------------+ 			 
	         |                                    |
             |  Stack = 0x00403000 ~ 0x0043FFF0   | @todo  Início da pilha em user mode do proesso.
	         |  Heap  = 0x00401000 ~ 0x0042FFF0   | @todo: Início do heap em user mode do processo.
             |                                    | ### Por enquando cada processo tem sua própria
             |                                    |     pilha e heap no fim da imagem do processo.   			 
             |                                    | 
			 |                                    |
			 | 00401000 = Process entry point     | Entrypoint da imagem.
			 | 00400000 = Process image base      | Onde se carrega uma imagem de processo.
             |                                    |  			 
             | 00000000 = Dinamic Library Base    |
			 | 00000000 = Dinamic Library image   |
			 |                                    |
             |              ...                   | @todo: ampliar heap.   			 
	00000000 |       User Mode access             |	 
			 +====================================+			 
			 

    ***
	
	

   mm - kernel process



*********************************   
 Memória linear para o processo kernel:

 Kernel Base        = 0xC0000000
 Kernel Entry point = 0xC0001000
 Heap               = 0xC0100000 ~ 0xC02FFFF0  
 Stack              = 0xC0300000 ~ 0xC03FFFF0


*********************************
 Memória física para o processo kernel: 

 Kernel Base        = 0x00100000
 Kernel Entry point = 0x00101000 
 Heap               = 0x00200000 ~ 0x003FFFF0    
 Stack              = 0x00400000 ~ 0x004FFFF0


 //#bugbug
 A configuração acima é a desejada, mas na prática o endereço 
 da pilha indicado na TSS é 0x200000
 
 
			 
	@todo: 
	    O layout da memória virtual está em fase de desenvolvimento.	   
	    Criar um layout dos endereços físicos principais usados pelo sistema.
*/ 
 
 
 
 //
 // **  ENDEREÇOS DOS PRINCIPAIS PAGE DIRECTORIES **
 //
 
 
// 
// Directory:
// ========== 
//     Endereço físico de alguns diretórios.
//     Esses diretórios são dos utilitários principais.
//     Não tem problema se esses diretórios ficarem isolados.
//     Serão colocados em cr3.
//

//@todo: Precisamaos definir melhor esses endereços.
//Colocá-los em um lugar segura e concatenados.

#define KERNEL_PAGEDIRECTORY  (0x0009C000)                        
#define IDLE_PAGEDIRECTORY    (0x0009C000 + 4096)                
#define SHELL_PAGEDIRECTORY   (0x0009C000 + 4096 + 4096)         
#define TASKMAN_PAGEDIRECTORY (0x0009C000 + 4096 + 4096 + 4096)  
//...

 


/* 
 * As configurações de memória foram feitas pelo Boot Loader.
 * (aqui os endereços lógico e físicos são iguais.)
 */


//Quantidade de diretórios que podem ser criados.
//obs: cada processo cria seu próprio diretório. 
//@todo: Criar um array de estruturas alocado.
#define PAGEDIRECTORY_COUNT_MAX 1024  

//Quantidade de page tables criadas...
//cada diretório pode ter um monte de tabelas.
//@todo: Criar um array de estruturas alocado.
#define PAGETABLE_COUNT_MAX 1024 



//
// zones support
//

//memória total em duas partes.
// 


//Zones.
// ** ESSA ESTRUTURA É A RAIZ DE TODA GERÊNCIA DE MEMÓRIA **
typedef struct mm_zones_d mm_zones_t;
struct mm_zones_d
{
    struct system_zone_d *system_zone;  //Essa zona é para o sistema.
    struct window_zone_d *window_zone;  //Essa zona toda é uma user session.
};
mm_zones_t *zones;


//system zone. 
typedef struct system_zone_d system_zone_t;
struct system_zone_d
{
    unsigned long systemzone_start;  //0x00000000. são os 32MB iniciais  
};
system_zone_t *systemzone;


//window zone.  
typedef struct window_zone_d window_zone_t;
struct window_zone_d
{
	unsigned long windowzone_start;
	//Endereço onde começa a user session.
	unsigned long usersession_start;	//ficará dentro de uma área paginada.
    struct usession_d *usersession;    
};
window_zone_t *windowzone;




// variáveis blobais de endereços usados no gerenciamento de zonas de memória.

#define SYSTEMZONE_START 0
#define SYSTEMZONE_END   0x0FFFFFFF 
#define WINDOWZONE_START 0x10000000
//#define WINDOWZONE_END ??

unsigned long systemzoneStart;
unsigned long systemzoneEnd;
unsigned long systemzoneSize;
unsigned long windowzoneStart;
unsigned long windowzoneEnd;    //?? Devemos levar em consideração o calculo do tamanho da memória
unsigned long windowzoneSize;
//
// tables support
//

//PDE - Page Directory Entry
typedef struct page_directory_entry_d page_directory_entry_t;
struct page_directory_entry_d
{
    unsigned long Present              :1;
    unsigned long ReadWrite            :1;
    unsigned long UserSupervisor       :1;
    unsigned long WriteThrough         :1;
    unsigned long CacheDisabled        :1;
    unsigned long Accessed             :1;
    unsigned long Reserved             :1;
    unsigned long PageSize             :1;
    unsigned long GlobalPage           :1;
    unsigned long Available1           :1;
    unsigned long Available2           :1;
    unsigned long Available3           :1;
    unsigned long PageTableBaseAddress :20;
};

//PTE - Page Table Entry
typedef struct page_table_entry_d page_table_entry_t;
struct page_table_entry_d
{
    unsigned long Present         :1;
    unsigned long ReadWrite       :1;
    unsigned long UserSupervisor  :1;
    unsigned long WriteThrough    :1;
    unsigned long CacheDisabled   :1;
    unsigned long Accessed        :1;
    unsigned long Reserved        :1;
    unsigned long PAT             :1;  // Page Table Attribute Index.
    unsigned long GlobalPage      :1;
    unsigned long Available1      :1;
    unsigned long Available2      :1;
    unsigned long Available3      :1;
    unsigned long PageBaseAddress :20;
};


/*
 * page_directory_d:
 *     Estrutura para o 'page directory' de um processo.
 *
 *     Todo processo tem seu próprio diretório de páginas.
 *     Assim vários processos podem usar o mesmo endereço lógico.
 *     Ex: 0x400000
 *     @todo: Um ponteiro para essa estrutura pode estar no PCB do processo.
 *            usar os processos criados por processos para testar a configuração
 *           de page directory.
 *     Obs: Um diretório tem ponteiros para page tables. as page tables 
 * funcionam como pools de frames.
 */
typedef struct page_directory_d page_directory_t;
struct page_directory_d
{
	
	object_type_t objectType;
	object_class_t objectClass;
	
	//identificadores.
	int id;
	int used;
	int magic;
	
	//Qual processo é o dono do diretório de páginas.
	//talvez seja possivel reaproveitar o diretório.
	struct process_d *process;
	
	//Endereço onde ficará o diretório de páginas.
	//Obs: Para configurar um diretório de páginas talvez
	//tenha que colocar um endereço físico em CR3. Lembre-se
	//que o malloc do kernel base aloca memória no heap do 
	//processo kernel que fica no último giga da memória virtual.
	unsigned long Address;
	
	
	// ?? struct page_directory_entry_d[1024] ??
	
	//@todo: Mais informações sobre o diretório de páginas.
	
	//Próximo diretório, significa próximo processo.
	//significa processos ligados em um job.
    struct page_directory_d *next;  
};
page_directory_t *pagedirectoryKernelProcess;    // KERNEL.
page_directory_t *pagedirectoryIdleProcess;      // IDLE.
page_directory_t *pagedirectoryTaskmanProcess;   // TASKMAN.
page_directory_t *pagedirectoryCurrent;          // Current.
page_directory_t *pagedirectoryShared;           // Shared. 
//...

//
// Lista de diretórios. (Pois cada processo tem um diretório).
//

//Lista de estruturas para diretórios de páginas.
unsigned long pagedirectoryList[PAGEDIRECTORY_COUNT_MAX]; 

//Linked list pode ser uma opção.
//Deve estar em sintonia com o scheduler de threads.
//page_directory_t *pagedirectoryLinkedListHead;



/*
 * page_table_d.
 *     Page table structure.
 *     Obs: Uma page table funciona como um pool de frames.
 *          Também pode ser compartilhada entre processo.(cuidado).
 */
typedef struct page_table_d page_table_t;
struct page_table_d
{
	object_type_t objectType;
	object_class_t objectClass;
	
	int id;
	int used;
	int magic;
	
	//A qual diretório de páginas a page table perrtence.
	//se bem que talvez possamos usar a mesma pagetable
	//em mais de um diretório. será??
	struct page_directory_d *directory;
	
	//Cada pagetable pertence à um processo.
	struct process_d *process;
	
	//Travando uma pagetable inteira,
	//nenhuma de suas páginas poderão se descarregadas
	//para o disco de swap.
	int locked;
	
	// ?? struct page_table_entry_d[1024] ??
	
    //@todo: Mais informações sobre a pagetable.
	struct page_table_d *next;
};
//page_table_t *pagetableCurrent;

page_table_t *pagetableCurrent;
//...

//
// Lista de pagetables.
//

unsigned long pagetableList[PAGETABLE_COUNT_MAX]; 

//Linked List talvez seja uma opção.
//page_table_t *pagetableLinkedListHead;








 
 
/**
 **  **  SUPER IMPORTANTE  **
 **
 ** ESSAS VARIÁVEIS GLOBAIS MARCARÃO O INÍCIO E O FIM 
 ** DA ÁREA DE MEMÓRIA FÍSICA DESTINADA AOS FRAMES DE MEMÓRIA 
 ** FÍSICA QUE SERÃO USADOS PELO GERENCIADOR DE PÁGINAS.
 ** pertencerão ao banco FDB. Free Data Base.
 ** 0x10000000 é um bom lugar pra começar os frames 
 ** na verdade os blocos 4MB, pois cada bloco de 4MB pode ser mapeado 
 ** usando apenas uma pagetable.
 ** 
 ** mmFramesSuperBlockStart = 0x10000000
 ** mmFramesSuperBlockEnd   = 0x1FFFFFFF
 ** 
 **
 **
 **/
 
// Frames Super Block.
// Variáveis globais parecem ser uma opção melhor de estrutura
// para esse caso. 
// Obs: temos listas de frames em algum lugar. criaremos listas aqui
//para o FSB, que será o nome do gerenciado, para melhorar o controle dessa área.
unsigned long mmFramesSuperBlockStart;      //Endereço onde começa o FSB.
unsigned long mmFramesSuperBlockEnd;        //Endereço onde termina o FSB.
unsigned long mmFramesSuperBlockSize;       //Tamanho do FSB dado em bytes.
unsigned long mmFramesSuperBlockTotal;      //Total de frames.
unsigned long mmFramesSuperBlockTotalFree;  //Total de frames livres. 
unsigned long mmFramesSuperBlockTotalUsed;  //Total de frames e uso. 
//Continua...

// ((0x1FFFFFFF - 0x10000000) / 512)  = QUANTIDADE DE FRAMES NESSA ÁREA.
#define FSB_FRAMES_MAX      (1*1024) //?? @todo: Determinar melhor isso
#define FSB_FREEFRAMES_MAX  (1*1024) //?? @todo: Determinar melhor isso

//## BUGBUG isso tornaria esse array bem grande.

//Lista de ponteiros para as estruturas de todos os frames do FSB.
unsigned long fsbFrames[FSB_FRAMES_MAX]; 
//Lista de ponteiros para as estruturas de todos os frames 'LIVRES' do FSB.
unsigned long fsbFreeFrames[FSB_FREEFRAMES_MAX];  
 
 


 
//
// memory:
//

//
// Stack.
//

//@todo: Crir estrutura de pilha.
//kernel stack. (Endereço virtual da pilha do processo Kernel).
//Obs: O Heap e a Stack estão dentro dos limites de 4MB de
//tamanho da imagem do kernel base.
#define KERNEL_STACK_SIZE   0x8000                                      //32kb
#define KERNEL_STACK_START  0xC02FFFF0                                  //(1 mega + 3 megas)Início da pilha. No fim dos 4MB.      
#define KERNEL_STACK_END    (KERNEL_STACK_START - KERNEL_STACK_SIZE)    //Fim da pilha.  




//Default stack que será usado em outra configuração de pilha.
//#define DEFAULT_STACK_SIZE           (1 * 1024 * 1024)
//#define DEFAULT_INITIAL_STACK_COMMIT (8 * 1024)


//image.
#define KERNEL_IMAGE_BASE  0xC0000000    //Base da imagem do kernel.
 
 
 
 
//
// MM BLOCK.
// 

#define MMBLOCK_HEADER_SIZE 64 
 



//Quantidade máxima de pageframes.
//@todo: #bugbug. isso tá errado. Essa é a quantidade de pageframes
//de apenas uma page table. Isso equiva à apenas um pagepool.
#define PAGEFRAME_COUNT_MAX 1024 //provisório


//Quantidade máxima de framepools.
//Um framepool é uma partição da memória física.
//cada framepool é composto de 1024 pageframes.
//@todo: #bugbug: A quantidade de framepools deve ser
//equivalente à quantidade de memória física disponível.
//Por isso devemos criar áreas de memória física alocáveis.
// o que facilita a manutenção de listas de framepools.
// Em outras palavra, temos que concatenar partições de memória física
//pra facilitar. Chamaremos essa área onde estão as partições de
//área paginável.
//@todo: Criar um ponteiro que indique o ínício da área páginável,
//assim como acontece com o início de um heap.
// À principio todo processo poderia ter acesso à apenas uma partição
// Um framepool é garantido para um processo quando esse processo é criado
// mesmo antes de haver algum mapeamento. Na verdade um processo terá uma lista
// de framepools.
//

//List.(1024 framepools de 4MB dá 4GB).
#define FRAMEPOOL_COUNT_MAX 1024

//Contagem de mmblock. 
#define MMBLOCK_COUNT_MAX  256 
 
 
#define PAGE_SIZE 0x1000    //4096.

//
// Size support.
//

#define KB  (1024)
#define MB	(1024 * 1024)
#define GB	(1024 * 1024 * 1024)

//Um framepool tem 4MB de tamanho.
#define MEMORY_PARTITION_SIZE (4 * MB)

//
// Obs: Criamos apenas algumas entradas no diretório de páginas
// do kernel, mas algumas dessas entradas serão iguais para todos 
// os processos. Então os diretórios de da páginas dos processos
// serão configurados de forma semelhante.
//

//
// Page frames da imagem do kernel:
// ================================
// Foram alocadas 1024 pageframes para a imagem do kernel.
// Isso equivale a um pageframe pool. Que é igual a 4MB. Pois
// são 1024 page frames de pagínas de 4KB cada.
//

//
// + kernel area = 1024 page frames (4MB)
// + kernel image = 1024 pageframes (4MB)
// + user mode area = 1024 pageframes (4MB)
// + vga = 1024 pageframes (4MB) (Isso transpassa o real tamanho da vga)
// + lfb = (frontbuffer) 1024 pageframes (4MB) (Isso é muito pouco, pois 
//         uma placa de vídeo tem mais memória que isso)
// + backbuffer = 1024 pageframes (4MB) (Isso realmente é pouco, o backbuffer 
//         deve caner uma imagem grande, que será dividade em vários monitores.)
//
//

//
// Page directory entries.
//

#define KERNEL_PAGE_DIRECTORY_ENTRY 0
#define KERNEL_IMAGE_PAGE_DIRECTORY_ENTRY 768
#define USERMODE_PAGE_DIRECTORY_ENTRY 1
#define VGA_PAGE_DIRECTORY_ENTRY 2
#define LFB_PAGE_DIRECTORY_ENTRY 769           //Frontbuffer.
#define BACKBUFFER_PAGE_DIRECTORY_ENTRY 770    //Backbuffer.
//...


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
 *     Conta os blocos de memória dentro de um heap.
 *     *dentro do heap usado pelo kernel eu acho ?? 
 */
unsigned long mmblockCount;         
 


/*
 * Kernel Stack suppport.
 */ 
unsigned long kernel_stack_end;        //va
unsigned long kernel_stack_start;      //va
unsigned long kernel_stack_start_pa;   //pa (endereço indicado na TSS).

/*
 * process_memory_info_d:
 *
 *     Estrutura para informações sobre a memória utilizada por um processo.
 * Obs: 
 * O gerenciamento de memória é tarefa do módulo /sm portanto isso não deve 
 * ir para o /microkernel.
 *
 */
typedef struct process_memory_info_d process_memory_info_t;
struct process_memory_info_d
{
	object_type_t objectType;
	object_class_t objectClass;	
	
	struct process_d *process;
	
	//valor em KB. (quantidade de páginas + tamanho da página.)
	
	unsigned long WorkingSet;  //Working Set.
    unsigned long Private;     //Memória não compartilhada. 
    unsigned long Shared;	   //Memória compartilhada.
	//...
	
	
	//unsigned long pageFaults; //Contagem de faltas.
	//Pico de Working Set.
	//??delta de conjunto de trabalho.
	//...
};
//Informações de memória do processo atual.
process_memory_info_t *pmiCurrent;
//...


/*
 * physical_memory_info_d:
 *
 *     Informações sobre a memória física.
 *     O arquivo system.h deve usar isso. 
 */
typedef struct physical_memory_info_d physical_memory_info_t;
struct physical_memory_info_d
{
	object_type_t objectType;
	object_class_t objectClass;
	
	//?? dúvidas.
	unsigned long Total;     //Total de memória física.(RAM).
	unsigned long InCache;   //Parte do total que está em cache.(foi paginada e está em cache).
	unsigned long Free;      //Livre.(Existe na RAM mas não foi paginada??).
    //...	
};
physical_memory_info_t *pmiMemoryInfo;
//...


/*
 * memory_info_d:
 *     Informações sobre a memória.
 *     Isso pode ser usado pela configuração do sistema. 
 */
typedef struct memory_info_d memory_info_t;
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
memory_info_t *miMemoryInfo;
//...


/*
 *****************************************************************
 * mmblock_d:
 *     Estrutura para memory blocks.
 *     Temos vários blocos de memória espalhados em lugares diferentes 
 * dentro de um heap.
 *     Essa estrutura é usada pelo kernel para controlar as áreas de memória
 * alocadas dinâmicamente dentro do heap do kernel. Porém poderemos
 * usar essa mesma estrutura para alocar memória em outros heaps. Como o heap 
 * de um processo ou o heap de um desktop. @todo: Para isso essa estrutura 
 * poderia conter informações sobre qual heap estamos usando. Mas me parece 
 * que o tamanho do header deve ser fixo.
 *
 * @todo: 
 * Os blocos precisam de alguma organização. 
 * Por enquanto, o total é 256 heaps de tamanhos diferentes.
 *
 * Os blocos formarão uma lista encadeada que será percorrida para se 
 * encontrar um bloco vazio. (walk).
 *
 * *Importante: A memória será organizada em bancos, que conterão memória 
 * privada e memória compartilhada. Os blocos de memória e os heaps 
 * precisam estar associadoas aos bancos, que conterão informações sobre 
 * processos e usuários. @todo:
 * Obs: Os bancos estão definidos em bank.h
 * 
 * Obs: Um heap de processo tem vários blocos dentro.
 *
 * *IMPORTANTE: 
 *     Talvez tenhamos algum limite para o tamanho dessa estrutura 
 * em especial. (Não incluir nenhuma variável por enquanto!).
 *****************************************************************
 */ 
//typedef struct mmblock_d mmblock_t;  //@todo: usar esse. 
typedef struct mmblock_d mmblock_descriptor_t;
struct mmblock_d 
{
	//
	// Essa estrutura é para gerenciar áreas de memória alocadas dinamicamente 
	// dentro do heap do processo kernel. Alocadas em tempo de eecução.
	//
	
	//
	// @todo: 
	// Talvez não seja possível mudar essa estrutura. Éla é diferente.
	// Portanto não definiremos inada o tipo de objeto que ela é e nem a classe.
	
	//object_type_t objectType;
	//object_class_t objectClass;
	
    //Identificadores.	
	unsigned long Header;      //Endereço onde começa o header do heap. *Importante.
	unsigned long headerSize;  //Tamanho do header em bytes.
	unsigned long Id;          //Id do header.
	unsigned long Used;        //Flag 'usado' ou 'livre'.
	unsigned long Magic;       //Magic number. Ver se não está corrompido.
	
	//Status.
	unsigned long Free;           //Se o bloco esta livre ou não.
	
	//Mensuradores. (sizes).	
	unsigned long requestSize;    //Tamanho, em bytes, da área solicitada.
	unsigned long unusedBytes;    //Quantidade de bytes não usados na área do cliente.	
	unsigned long userareaSize;   //Tamanho da área reservada para o cliente. 
	                              //(request size + unused bytes). 
								  
	//@todo: 
	//    Incluir quando possível.
    // Lembrando que talvez o tamanho dessa estrutura seja fixo.
    // Talvez não mudaremos nada no tamanho dela.	
	//struct heap_d *heap;							  
	
    // User area. 
	// (Onde começa a área solicitada).
	unsigned long userArea;    //Início da área alocada.
	
	// Footer.
	unsigned long Footer;    //Endereço do início do footer.
	
	// Process info.
    // (Pertence à qual processo?).	
	int processId;
	struct process_d *process;
	
	//
	// Continua ?? ... 
	// Talvez não pode.
	//
	
	//
	// *IMPORTANTE: 
	// Talvez temos algum limite para o tamanho dessa estrutura em especial. 
	// Não inluir nada por enquanto.
	//
	
	//Encadeando.
	struct mmblock_d *Prev;
	struct mmblock_d *Next;
};
mmblock_descriptor_t *current_mmblock;
//mmblock_descriptor_t *SystemCache_mmblock;
//mmblock_descriptor_t *ProcessCache_mmblock;
//...

 
//Lista de blocos. 
//lista de blocos de memória dentro de um heap.
//@todo: na verdade temos que usar lista encadeada. 
unsigned long mmblockList[MMBLOCK_COUNT_MAX];  
                                 
								 
								 							 
/*
typedef struct free_mmblock_d free_mmblock_t;
struct free_mmblock_d 
{
   struct mmblock_d *next;
   char garbage[4092];
}
*/



//
// ********  GERENCIAMENTO DE MEMÓRIA FÍSICA **************
//



//
// A memória física é dividida em partições.
// cada partição é composta de 1024 frames.
// Uma partição será chamada de framepool.
// Cada pegepool tem 1024 page frames.
//

/*
 * page_frames_d:
 *     Guarda informações sobre um 'page frame' na memória física.
 *     @todo: Incluir todas as informações necessárias.
 */
typedef struct page_frames_d page_frames_t;
struct page_frames_d
{
	object_type_t objectType;
	object_class_t objectClass;
	
	int id;
	int used;
	int magic;
	int locked;             //Não pode ser descarregado para o disco.
	//...
	
    unsigned long address;  //Endereço físico da page frame.	
	
	//...
	
	//@todo
	//'owner' A quem pertence a page frame.???user, group, process.
	struct process_d *process;
	//...
	
	//à qual pagetable pertence esse page frame.
	struct page_table_d *pagetable;
	
	//aspace associado à esse pageframe.
	struct aspace_d *aspace;
	
	//area de disco associada à esse pageframe.
	struct dspace_d *dspace;
	
	
	//navegação
    struct page_frames_d *next;	
};
page_frames_t *pageframeCurrent;
//...

//Lista de page frames.
unsigned long pageframesList[PAGEFRAME_COUNT_MAX];
//page_frames_t *pageframeListHead;




/*
 * frame_pool_d:
 *     Estrutura para uma partição da memória física.
 *     Uma partição da memória física é chamada de framepool.
 *     Cada framepool tem 1024 frames.
 *     @todo: Poderia ser framepool_d ??
 */
typedef struct frame_pool_d frame_pool_t;
struct frame_pool_d
{
	object_type_t objectType;
	object_class_t objectClass;
	
	int id;
	int used;
	int magic;
	int locked;
	
	//Endereço do início do framepool.
	unsigned long address; 
	
	//Qual processo é o dono desse framepool.
	struct process_d *process;
	
	struct frame_pool_d *next;
};

//
// Cada framepool abaixo é o framepool inicial de uma região.
// Uma regisão pode ter vários framepools.
//

//kernel space.
frame_pool_t *framepoolKernelSpace;            //0x00000000  Kernel Space. Início do kernel space.

//user space
frame_pool_t *framepoolSmallSystemUserSpace;   //0x00400000  Para um sistema pequeno o kernel space tem 4MB.
frame_pool_t *framepoolMediumSystemUserSpace;  // 
frame_pool_t *framepoolLargeSystemUserSpace;   //0x40000000  Para um sistema grande o kernel space tem um giga. 
//...

//Cada front buffer é uma placa de vídeo.
frame_pool_t *framepoolFrontBuffer1;   //Início do linear frame buffer 1.
frame_pool_t *framepoolFrontBuffer2;   //Início do linear frame buffer 2.
frame_pool_t *framepoolFrontBuffer3;   //Início do linear frame buffer 3.
frame_pool_t *framepoolFrontBuffer4;   //Início do linear frame buffer 4.
//...

//Backbuffer
frame_pool_t *framepoolBackBuffer1;   //Início do backbuffer.
frame_pool_t *framepoolBackBuffer2;   //Início do backbuffer.
frame_pool_t *framepoolBackBuffer3;   //Início do backbuffer.
frame_pool_t *framepoolBackBuffer4;   //Início do backbuffer.
//...


//Área onde poderemos alocar frames para os processos usarem...
//Esse é o framepool inicial de usa áre grande de memória.
frame_pool_t *framepoolPageableSpace;   


//Current.
frame_pool_t *framepoolCurrent;
//...

//frame_pool_t *framepoolKernelPagedPool;
//frame_pool_t *framepoolKernelNonPagedPool;
//frame_pool_t *framepoolUserPagedPool;
//frame_pool_t *framepoolUserNonPagedPool;

//
//   **** PAGEABLE AREA ****
//



unsigned long gPagedPollStart;
unsigned long gPagedPollEnd;


//Obs: ISSO É UM TESTE.
//Número máximo de framepools na área de alocaçao de frames.
//Obs: Isso é uma espécie de cache. Porém cache é coisa de disco.
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
// Número máximo de índices de framepool que serão usados nessa área de 
// alocação de frames.
// *** Uma certa quantidade de framepools serão usados
// para alocação de frames para os processos. Durante
// a alocação sobre demanda os frames usados virão dessa área de memória.
//
//
//

int g_pageable_framepool_index_max;


//List.(1024 framepools de 4MB dá 4GB).
unsigned long framepoolList[FRAMEPOOL_COUNT_MAX];


//Lista de framepools livres.
//int framepoolFreeList[FRAMEPOOL_COUNT_MAX]
//frame_pool_t *framepoolFreeListHead;



//frame pool atual.
int g_current_framepool;


//o indice do framepool da user space para qualquer tamanho de memória.
int g_user_space_framepool_index;


//O máximo de framepools possíveis dado o tamanho da memória física.
unsigned long g_framepool_max;


//Tamanho máximo da memória física.
unsigned long g_total_physical_memory;


//Contabilidade. kernel(talvez deva fazer uma estrututra) MS.
//Memória usada pelo kernel.
//+Paginada. paged
//+não paginada. nonpaged
//+fisica paginada
//+virtual paginada 
//+paginada limite
//+naõ pagianda limite.
//
unsigned long g_kernel_paged_memory;
unsigned long g_kernel_nonpaged_memory;

// **** GERENCIA DE MEMÓRIA FÍSICA. ****
//MS - Windows 
// +Resevada para hardware.
// +Em uso.
// +Modificada. 
// +Em espera.
// +Livre.
// ?? Aqui não conta a memória de vídeo, somente o tamanho da memória ram física.
// A memória de vídeo está normalmente no topo da memória física real. Endereço 
// além do tamanho da memória ram.
//


// **** GERENCIA DE MEMÓRIA FÍSICA. ****
//MS - Windows 
// + Total.
// + Em cache.
// + Disponível.
// + Livre.
//



unsigned long memorysizeBaseMemory;
unsigned long memorysizeOtherMemory;
unsigned long memorysizeExtendedMemory;
unsigned long memorysizeTotal;

//
// Protótipos.
//
void memoryShowMemoryInfo();

//
// Init support.
//

int init_mm(); 
int init_stack();
int SetUpPaging();    //Configura paginação.
void SetCR3(unsigned long address);



//
// Directory and Page Tables.
//

void *CreatePageDirectory(unsigned long directory_address);
void *CreatePageTable( unsigned long directory_address, 
                       int offset, 
					   unsigned long page_address );



//
// Debug support.
//

void show_memory_structs();


//
// garbage collection support
//

int gc();
int gcGRAMADO();
int gcEXECUTIVE();
int gcMICROKERNEL();
int gcHAL();




//
// End.
//


