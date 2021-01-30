/*
 * File: pages.c
 *
 *     Faz a configura��o da pagina��o de mem�ria e oferece rotinas de
 * suporte ao mapeamento de mem�ria f�sica.
 *     Faz parte do modulo /mm da classe ram.
 *
 * *Importante:
 *     Essa rotina pertence ao m�dulo de gerenciamento de mem�ria. N�o possui
 * informa��es sobre processos. Qualquer informa��o sobre processos deve ser 
 * conseguida atrav�s de invoca��o de m�todos pertencentes ao m�dulo 
 * /microkernel.
 *
 * @todo: 
 *    IMPORTANTE:
 *    +FAZER GERENCIAMENTO DA MEM�RIA F�SICA. 
 *    +DIVIDIR A MEM�RIA F�SICA EM PARTI��ES DE 4MB E 
 *    +DIVIDIR CADA PARTI��O EM FRAMES DE 4KB, O QUE D� 1024 FRAMES POR 
 * PARTI��O.
 *
 * Obs: 
 *     Chamaremos de 'framepool' o conjunto de 1024 frames.
 *     Poderemos mapear um framepool inteiro se preciso. 
 *
 * @todo:
 * *Importante:
 * Obs: 
 *     Os processos Idle, Shell e Taskman est�o usando o diret�rio de p�ginas 
 * do processo Kernel. � preciso criar um diret�rio para cada processo e 
 * criar uma rotina de automa��o na cria��o de diret�rios de p�ginas.
 *
 * @todo: 
 *     Criar rotinas para ver o conte�do da lista de diret�rios de p�ginas.
 *     ?? Cada diret�rio deve ter uma estrutura, cujo ponteiro vai pra dentro 
 * da lista.
 *     ?? A estrutura mostrar� informa��es sobre o diret�rio de p�ginas.
 *
 * @todo: 
 *     Criar rotinas que manipulem as estruturas de diret�rio de p�ginas e de 
 * pagetables. 
 *
 * Obs: Todas as pagetables podem ficar em sequ�ncia em uma mesma regi�o do endere�o
 * l�gico do processo kernel.
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
 */


// Algumas �reas de mem�ria:
// =========================
//
// + kernel area    = 1024 pageframes (4MB).
// + kernel image   = 1024 pageframes (4MB).
// + user mode area = 1024 pageframes (4MB).
// + vga            = 1024 pageframes (4MB).
//     (Obs: Isso transpassa o real tamanho da vga).
// + lfb (frontbuffer) = 1024 pageframes (4MB).
//     (Obs: Isso � muito pouco, placas de video possuem muita memo'ria)
// + backbuffer     = 1024 pageframes (4MB). 
//     (Obs: Isso realmente � pouco, no backbuffer deve caber uma imagem 
// grande, que ser� dividida em v�rios monitores).
// + ?? tem ainda um pool de pageframes usados para aloca�ao.


#include <kernel.h>


// These values came from BL.BIN.
// bootblock, lfb, device width, device height, bpp ...
//extern unsigned long SavedBootBlock; 
extern unsigned long SavedLFB;
//extern unsigned long SavedX;
//extern unsigned long SavedY;
//extern unsigned long SavedBPP;
// ...


//
// == imports =======================
//

extern void set_page_dir (void);
// ...



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
void *clone_kernel_page_directory (void);
void *clone_kernel_page_directory (void)
{
    return (void *) CreatePageDirectory ();
}
*/


// ===================================================================
//
// #important: DANGER !!!
//
// get_table_pointer:
//
// #bugbug
// Isso eh um improviso, precisamos de outro endereço.
// >>>> 0x1000
//
// O sistema esta usando esse endereço como inicio de um heap
// onde pegamos paginas (frames?) de memoria para criarmos diretorios de paginas.
// Isso porque precisamos de endereços que terminem com pelo menos 
// 12 bits zerados.
//
// #todo: 
// Precisamos encontrar outro lugar para esse heap, 
// tendo em vista que o numero de diretorios criados sera grande 
// e o heap invadir outras areas.
//
// #bugbug
// Vamos improvisar um limite por enquanto.
// See: globals/gpa.h
//

unsigned long table_pointer_heap_base = ____DANGER_TABLE_POINTER_HEAP_BASE;
//unsigned long table_pointer_heap_base = 0x1000;

// ====================================================================

unsigned long get_table_pointer (void)
{
    table_pointer_heap_base = (table_pointer_heap_base + 0x1000);

    // #todo
    // Precisamos de uma nova origem.
    // Os primeiros 12bits precisam ser '0'.
    // VM_BASE = 0x000B8000.
    
    // #bugbug
    // Todo o espaço entre 0x1000 e 0x000B8000 esta livre ?
    // Onde estao a fat e o root dir?
    // MBR_ADDRESS = 0x20000. 
    // Esse o o endereço mais baixo entre os endereços usados
    // pelo sistema de arquivos.
    
    //if ( table_pointer_heap_base >= VM_BASE )
    if ( table_pointer_heap_base >= MBR_ADDRESS )
    {
        panic ("pages-get_table_pointer: [FIXME] Limits\n");
    }


    return (unsigned long) table_pointer_heap_base;
}



/*
 ***********************************************************
 * initialize_frame_table:
 *     Frame table to handle a pool of page frames.
 */

int initialize_frame_table (void){

    int i=0;


    debug_print("initialize_frame_table:\n");

    FT.total_frames = (FT.frame_table_size_in_bytes/4096);

    // Número de páginas necessárias para termos uma tabela.
    // Cada página pode conter 4096 entradas de i byte
    FT.n_pages = (FT.total_frames/4096); 

    FT.frame_table = (unsigned char *) allocPages(FT.n_pages);

    if ((void *) FT.frame_table ==NULL){
        panic("initialize_frame_table: invalid FT.frame_table"); 
    }

    //#todo: limits
    if ( FT.frame_table_size_in_bytes == 0 ){
        panic("initialize_frame_table: frame_table_size_in_bytes");
    }

    // Clear frame table.
    for (i=0; i < FT.total_frames; i++){
        FT.frame_table[i] = 0;
    }

    //#debug
    printf ("Table size in pages %d\n",FT.n_pages);
    printf ("Total frames %d\n",FT.total_frames);
    refresh_screen();

    FT.frame_table_status = 1;

    //ok
    return 0;
}



unsigned long get_new_frame (void){

    int i=0;

    if (FT.frame_table_status != 1)
        return 0;

    //#todo: limits
    if (FT.frame_table_start == 0){
        panic("invalid FT.frame_table_start");
    }

    for (i=0; i< FT.total_frames; i++)
    {
        if ( FT.frame_table[i] == 0)
        {
            FT.frame_table[i] = 1; // não free.
            return (unsigned long) ( FT.frame_table_start + (i * 4096) ); 
        }
    };

    //fail;
    return 0;
}


/*
 *********************************** 
 * clone_directory:
 *     Clone a given page directory.
 * 
 */

// Clona um diretório dado seu endereço.
// Queremos clonar o diretório atual,
// para que o processo filho tenha o mesmo diretório do processo pai. 

// #??
// Esse endereço virtual eh valido?
// Pertence ao diretorio que estamos usando no momento?

// #todo
// mm_clone_directory

void *clone_directory ( unsigned long directory_va ){

    unsigned long destAddressVA=0; 
    int i=0;


    // #test
    // no directory in the address '0'

    if ( directory_va == 0 )
        panic("clone_directory: directory_va\n");


    // Get a target address for the directory.
    
    // #bugbug:
    // We are using that routine to get a poiter for a table.
    // Is that a virtual address ?
    // What about the size?

    destAddressVA = (unsigned long) get_table_pointer(); 
    
    if ( destAddressVA == 0 ){
        panic ("CreatePageDirectory: destAddressVA\n");
    }

    // Initialization

    unsigned long *src = (unsigned long *) directory_va;
    unsigned long *dst = (unsigned long *) destAddressVA;

    // Copy.

    for ( i=0; i < 1024; i++ ){
        dst[i] = (unsigned long) src[i]; 
    };

    // The address of the new page diretory.

    return (void *) destAddressVA;
}


/*
 **************************************************
 * CloneKernelPageDirectory:
 *
 *    Clone the kernel page diretory.
 *    OUT: The virtual address of the new directory.
 */

// #todo
// mmCloneKernelPageDirectory

void *CloneKernelPageDirectory (void){

    unsigned long destAddressVA=0; 
    int i=0;


    //destAddressVA = (unsigned long) newPage (); 
    destAddressVA = (unsigned long) get_table_pointer(); 

    if ( destAddressVA == 0 ){
        panic ("CreatePageDirectory: destAddressVA\n");
    }


    // The virtual address of the kernel page directory and
    // the virtual address of the new page directory.
    // #bugbug: What directory we are using right now? kernel?

    unsigned long *src = (unsigned long *) gKernelPageDirectoryAddress;  
    unsigned long *dst = (unsigned long *) destAddressVA;  

    // Copy.
    
    for ( i=0; i < 1024; i++ ){
        dst[i] = (unsigned long) src[i];
    };

    // Done.
    // The virtual address of the new pagedirectory. 

    return (void *) destAddressVA;
}


/*
 *******************
 * CreatePageTable:
 *     Cria uma page table em um diret�rio.
 *     Obs:
 *     + O endere�o precisa ser alocado antes.
 *     + Precisa ser um endere�o f�sico.
 *     + O diret�rio precisa ser um diret�rio v�lido.
 *
 * =====================================
 * IN:
 *
 *     [directory_address]
 *         O endere�o do diret�rio onde colocaremos o endere�o 
 * do in�cio da tabela de p�gina que criaremos.
 *
 *     [offset]
 *         O deslocamento dentro do diret�rio para sabermos o 
 * lugar para salvarmos o endere�o da tabela de p�ginas 
 * que estamos criando.
 * @todo: Na hora de salvarmos esse endere�o tamb�m 
 * temos que incluir as flags.
 * #importante:
 * O offset � um �ndice dentro do diret�rio de p�ginas.
 *
 *     [region_address]
 * O endere�o da regi�o que estamos mapeando na pagetable.
 * Obs: Precisamos alocar mem�ria para a pagetable 
 * que estamos criando, isso antes de chamarmos essa rotina. 
 * Obs: Uma pagetable tem 4096 bytes de tamanho.
 * Obs: Criamos uma tabela de p�ginas, com p�ginas em user mode.
 *
 */ 

// #importante:
// Cria uma pagetable em um dado diret�rio de p�ginas.
// Uma regi�o de 4MB da mem�ria f�sica � mapeanda nessa pt.

// #bugbug:
// Isso aparentemente est� com problema. #testando ...

// #todo
// mmCreatePageTable

void *CreatePageTable ( 
    unsigned long directory_address_va, 
    int dir_index, 
    unsigned long region_address )
{

    unsigned long *PD = (unsigned long *) directory_address_va;
    int i=0;


	//
	// =======================
	// ### pd  ###
	//


	// #importante:
	// Endere�o virtual do diret�rio de p�ginas.
	// Precisamos do endere�o virtual do diret�rio para edit�-lo.

    if ( directory_address_va == 0 ){
        panic ("CreatePageTable: directory_address_va\n");
    }


	//
	// ===========================
	// ### pt  ###
	//
	
	// #importante:
	// Endere�o virtual da tabela de p�ginas que vamos criar.
	// Precisamos de um endere�o virtual para manipularmos a tabela,
	// pois o kernel trabalha com os endere�os virtuais,
	// s� depois converteremos para f�sico e salvaremos na 
	// entrada do diret�rio o ponteiro que � um endere�o f�sico.

    //unsigned long ptVA = (unsigned long) kmalloc (4096);
    //unsigned long ptVA = (unsigned long) allocPages (1);
	
	//#bugbug
	//Temos que criar um alocador de mem�ria para os ponteiros
	//das tabelas, esses ponteiros precisam de 12 bits zerados.
	//ent�o tem que alocar de 4kb em 4kb.
	//precisamos encontrar alguma �rea dentro do kernel para isso.
	
	//unsigned long ptVA = (unsigned long) newPage ();    //bug (pf)
	//unsigned long ptVA = (unsigned long) kmalloc(4096);  //bug (precisa 12bits zerados)
	//unsigned long ptVA = (unsigned long) 0x1000;               //ok
	unsigned long ptVA = (unsigned long) get_table_pointer();  //ok

    if ( ptVA == 0 ){
        panic ("CreatePageTable: ptVA\n");
    }

    // O endereço virtual permite manipularmos a 
    // pagetable daqui do kernel.
    unsigned long *newPT = (unsigned long *) ptVA;

	
	//
	// ===================================
	// ### dir_index  ###
	//

    // Limits.
    if ( dir_index < 0 || dir_index >= 1024 )
    {
        panic ("CreatePageTable: offset\n");
    }



	//
	// ===============================
	// ### region  ###
	//

    // Limits.
    if ( region_address == 0 ){
        panic ("CreatePageTable: region_address\n");
    }

	
	//
	// ===================================
	// ### pt  ###
	//
	
	// #importante:
	// Agora vamos mapear a regi�o de mem�ria f�sica na nova pagetable.

	// #obs:
	// + J� criamos uma pagetable e temos seu endere�o l�gico.
	// + Vamos mapear 4MB de mem�ria f�sica.
	// + Ser�o p�ginas em user mode.
	// + A pagetable ser� usado por um processo em user mode. 
	// + Note as flags.(7). 7 decimal � igual a 111 bin�rio.
	// ...
	
	//#debug
	//printf (">> region_address = %x \n",region_address);
	

    for ( i=0; i < 1024; i++ )
    {
        newPT[i] = (unsigned long) region_address | 7; 
        region_address = (unsigned long) region_address + 4096; 
    };


	//#debug
	//printf (">> newPT[0] = %x \n", newPT[0]);


    //
    // ==================================
    // ## pd ##
    //

	// #importante:
	// Agora vamos colocar o endere�o f�sico da nova pagetable em 
	// uma das entradas do diret�rio de p�ginas. 
	// O n�mero da entrada � o �ndice passado via argumento. dir_index.
    // Antes precisamos converter o endere�o l�gico da tabela de p�ginas
	// em um endere�o f�sico.
	
	// obs:
    // + Precisamos colocar o endere�o f�sico da tabela em uma entrada 
	// do diret�rio.	
	// + Aqui devemos incluir as flags tamb�m.
    // ...

	// #importante:
	// Para chamarmos essa rotina, temos que ter o diret�rio do kernel 
	// corretamente configurado.
	
	// #obs: 
	// Poder�amos passar as flags via argumento.
	// O endere�o do diret�rio de paginas do kernel precisa ser um endere�o virtual.
	
    unsigned long ptPA = (unsigned long) virtual_to_physical ( ptVA, 
                                             gKernelPageDirectoryAddress ); 
	
	//printf (">> ptVA = %x \n",ptVA);
	//printf (">> ptPA = %x \n",ptPA);	

    if ( ptPA == 0 ){
        panic ("CreatePageTable: ptPA\n");
    }

    PD[dir_index] = (unsigned long) ptPA;
    PD[dir_index] = (unsigned long) PD[dir_index] | 7; 

	// Done.
	// Retornaremos o endereço virtual da pagetable,
	// para que a tabela possa ser manipulada pelo kernel.

    return (void *) ptVA;
}
 

/*
 ************************************ 
 * x86_SetCR3:
 * 
 */

// Coloca o endere�o do diret�rio de p�ginas de um processo
// no registrador cr3 da arquitetura Intel.
// #bugbug: Esse método não está bom.
// Usar o outro presente nesse documento.
// mm_switch_directory.
// N�o podemos usar um diret�rio de p�ginas que esteja
// no in�cio da mem�ria RAM.
// See: x86/headlib.asm

void x86_SetCR3 (unsigned long pa)
{
    if (pa == 0){
        panic ("x86_SetCR3: 0 is not a valid address!");
    }

    asm volatile ("\n" :: "a"(pa) );
    
    set_page_dir();
}



// Get the physical address from cr3.

unsigned long mm_get_current_directory_pa (void)
{
    unsigned long __ret = 0;

    asm volatile ("mov %%cr3, %0" : "=r"(__ret));
    
    return (unsigned long) __ret;
}


// #todo
// It can be used to change different directories.
// And then switch back to the current directory.
void mm_switch_directory (unsigned long dir)
{
    if (dir == 0){
        debug_print("mm_switch_directory: [FAIL] dir\n");
        return;
    }

    asm volatile ("mov %0, %%cr3" :: "r"(dir)); 
}


/*
// pegar o endereço físico do diretório de páginas de uma processo
// dado seu pid.
unsigned long mm_get_directory_pa ( pid_t pid );
unsigned long mm_get_directory_pa ( pid_t pid ){

    // #todo
    // Validations.

    if (pid<0)
        return 0;
        
    p = (struct process_d *) processList[pid];
    
    if ( (void *) p == NULL )
        return 0;
        
    return (unsigned long) p->DirectoryPA; 
}
*/


/*
void mm_free_directory ( unsigned long dir );
void mm_free_directory ( unsigned long dir ){
    unsigned long current_directory_pa = 0;
    
    if ( dir == 0 )
        return;
    
    current_directory_pa = mm_get_directory_pa (current_process);
    
    if (current_directory_pa==0)
        return;
    
    if ( dir == current_directory_pa )
        return;


    // #todo
    // Clear the directory properly.
}
*/


/*
 ************************************************************
 * mapping_ahci0_device_address:
 *     Mapeando um endere�i f�cico usado pelo driver AHCI.    
 */

// #bugbug
// Isso realmente eh um improviso.
// Temos muito o que fazer ainda.

// #todo
// mm_mapping_ahci1_device_address

unsigned long 
mapping_ahci1_device_address ( unsigned long pa )
{

    unsigned long *page_directory = (unsigned long *) gKernelPageDirectoryAddress;      

    // Endereço improvisado.
    // See: gpa.h
    unsigned long *ahci1_page_table = (unsigned long *) PAGETABLE_AHCI1; 

    int i=0;

    // If you do use a pointer to the device register mapping, 
	// be sure to declare it volatile; otherwise, 
	// the compiler is allowed to cache values and reorder accesses to this memory.	
	
    // Since this is device memory and not regular DRAM, you'll have to tell 
	// the CPU that it isn't safe to cache access to this memory. 	
	//(cache-disable and write-through).
	
	
	// #imporatante
	// #todo:
	// Ainda n�o calculamos o uso de mem�ria f�sica.
	// Precisamos saber quanta mem�ria f�sica esse dispositivo est� usando.
	// 10=cache desable 8= Write-Through 0x002 = Writeable 0x001 = Present
	// 0001 1011

    for ( i=0; i < 1024; i++ )
    {
        ahci1_page_table[i] = (unsigned long) pa | 0x1B; 
        pa = (unsigned long) (pa + 4096);
    };


	//f0400000      961
    page_directory[ENTRY_AHCI1_PAGES] = (unsigned long) &ahci1_page_table[0];
    page_directory[ENTRY_AHCI1_PAGES] = (unsigned long) page_directory[ENTRY_AHCI1_PAGES] | 0x1B;


    // (virtual)
    return (unsigned long) AHCI1_VA;
}


/*
 ***********************************
 * mapping_nic0_device_address:
 *     Mapeando um endere�o f�cico usado pelo NIC1.    
 */

//82540 test
//e, 88000h ficar� a pagetable para mapear o endere�o f�sico em f0000000va
//mapeando o nic principal.
//considerando que tenhamos mais de uma placa de rede, 
//esse mapeamento s� ser� v�lido para o primeiro.

// #bugbug
// Isso realmente eh um improviso.
// Temos muito o que fazer ainda.

// #todo
// mm_mapping_nic1_device_address

unsigned long 
mapping_nic1_device_address ( unsigned long pa )
{

    unsigned long *page_directory = (unsigned long *) gKernelPageDirectoryAddress; 

    // Endereço improvisado.
    // See: gpa.h
    unsigned long *nic0_page_table = (unsigned long *) PAGETABLE_NIC1;

    int i=0; 

    // If you do use a pointer to the device register mapping, 
	// be sure to declare it volatile; otherwise, 
	// the compiler is allowed to cache values and reorder accesses to this memory.	
	
    // Since this is device memory and not regular DRAM, you'll have to tell 
	// the CPU that it isn't safe to cache access to this memory. 	
	//(cache-disable and write-through).
	
	
	// #imporatante
	// #todo:
	// Ainda n�o calculamos o uso de mem�ria f�sica.
	// Precisamos saber quanta mem�ria f�sica esse dispositivo est� usando.
	// 10=cache desable 8= Write-Through 0x002 = Writeable 0x001 = Present
	// 0001 1011

    for ( i=0; i < 1024; i++ )
    {
        nic0_page_table[i] = (unsigned long) pa | 0x1B;
        pa = (unsigned long) (pa + 4096); 
    };


	// f0000000   960
    page_directory[ENTRY_NIC1_PAGES] = (unsigned long) &nic0_page_table[0];
    page_directory[ENTRY_NIC1_PAGES] = (unsigned long) page_directory[ENTRY_NIC1_PAGES] | 0x1B; // 0001 1011 


	// (virtual)
    return (unsigned long) NIC1_VA;
}


/*
 *************************************************************
 * mmSetUpPaging:
 *     Configura o diret�rio de p�ginas do processo Kernel e 
 * algumas tabelas de p�ginas.
 *
 * Obs: 
 *     Na hora em que um processo � criado deve-se criar seu diret�rio de 
 * p�ginas e as tabelas de p�ginas usadas por ele, de acordo com o tamanho 
 * do processo.
 *
 * Diret�rio:
 *     page_directory = 0x0009C000. (Endere�o f�sico).#kernel
 *
 * Obs:
 *     Esse diret�rio criado ser� usado pelo processo Kernel e tamb�m por 
 * outros processos tamb�m durante essa fase de constru��o do sistema. 
 * Depois cada processo ter� seu pr�prio diret�rio de p�ginas. Isso est� em 
 * fase de implementa��o. O ideal � um diret�rio por processo.
 *     Toda vez que o Kernel iniciar a execu��o de um processo ele deve 
 * carregar o endere�o do diret�rio do processo no registrador de controle CR3.
 * 
 * @todo: 
 *     Por enquanto s� um diret�rio foi criado.
 *     
 * @tod:
 *     o Mudar para pagesSetUpPaging.
 *
 * @TODO: AS COISAS EST�O MEIO BAGUN�ADAS AQUI. A INTEN��O � QUE 
 * A PARTE BAIXA DA MEM�RIA VIRTURAL DO PROCESSO PERTEN�A AO PROCESSO 
 * E A PARTE ALTA DA MEM�RIA VIRTUAL DO PROCESSO PERTEN�A AO KERNEL.
 * QUANTO A MEM�RIA F�SICA, DESEJAMOS QUE APENAS O KERNEL ACESSE A 
 * PARTE BAIXA DA MEM�RIA F�SICA, OS PROGRAMAS EM USER MODE MANIPULAR�O
 * APENAS A MEM�RIA QUE LHES FOR CONCEDIDA.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     ...
 */

// Called by:
// init_runtime in runtime.c

int mmSetUpPaging (void)
{
    // loops
    register unsigned int i=0;


	// #importante
	// Inicializando as vari�veis que vamos usr aqui.
	// S�o endere�os de mem�ria f�sica.
	// As vari�veis s�o globais para podermos gerenciar o uso de
	// mem�ria f�sica.
	// See:  mm/mm.h
	// See:  gpa.h

	//==============================================================
	//                  ****    SMALL SYSTEMS    ****
	//==============================================================
    SMALL_origin_pa      = (unsigned long) SMALLSYSTEM_ORIGIN_ADDRESS;
    SMALL_kernel_base_pa = (unsigned long) SMALLSYSTEM_KERNELBASE;
    SMALL_user_pa        = (unsigned long) SMALLSYSTEM_USERBASE;
    SMALL_cga_pa         = (unsigned long) SMALLSYSTEM_CGA;
    SMALL_frontbuffer_pa = (unsigned long) SavedLFB;                     //frontbuffer
    SMALL_backbuffer_pa  = (unsigned long) SMALLSYSTEM_BACKBUFFER;       //backbuffer
    SMALL_pagedpool_pa   = (unsigned long) SMALLSYSTEM_PAGEDPOLL_START;  //PAGED POOL
    SMALL_heappool_pa    = (unsigned long) SMALLSYSTEM_HEAPPOLL_START;
    SMALL_extraheap1_pa  = (unsigned long) SMALLSYSTEM_EXTRAHEAP1_START;
    SMALL_extraheap2_pa  = (unsigned long) SMALLSYSTEM_EXTRAHEAP2_START;
    SMALL_extraheap3_pa  = (unsigned long) SMALLSYSTEM_EXTRAHEAP3_START;
	//==============================================================
	//                  ****    MEDIUM SYSTEMS    ****
	//==============================================================
    MEDIUM_origin_pa      = (unsigned long) MEDIUMSYSTEM_ORIGIN_ADDRESS;
    MEDIUM_kernel_base_pa = (unsigned long) MEDIUMSYSTEM_KERNELBASE;
    MEDIUM_user_pa        = (unsigned long) MEDIUMSYSTEM_USERBASE;
    MEDIUM_cga_pa         = (unsigned long) MEDIUMSYSTEM_CGA;
    MEDIUM_frontbuffer_pa = (unsigned long) SavedLFB;
    MEDIUM_backbuffer_pa  = (unsigned long) MEDIUMSYSTEM_BACKBUFFER;
    MEDIUM_pagedpool_pa   = (unsigned long) MEDIUMSYSTEM_PAGEDPOLL_START;
    MEDIUM_heappool_pa    = (unsigned long) MEDIUMSYSTEM_HEAPPOLL_START;
    MEDIUM_extraheap1_pa  = (unsigned long) MEDIUMSYSTEM_EXTRAHEAP1_START;
    MEDIUM_extraheap2_pa  = (unsigned long) MEDIUMSYSTEM_EXTRAHEAP2_START;
    MEDIUM_extraheap3_pa  = (unsigned long) MEDIUMSYSTEM_EXTRAHEAP3_START;
	//==============================================================
	//                  ****    LARGE SYSTEMS    ****
	//==============================================================
    LARGE_origin_pa      = (unsigned long) LARGESYSTEM_ORIGIN_ADDRESS;
    LARGE_kernel_base_pa = (unsigned long) LARGESYSTEM_KERNELBASE;
    LARGE_user_pa        = (unsigned long) LARGESYSTEM_USERBASE;
    LARGE_cga_pa         = (unsigned long) LARGESYSTEM_CGA;
    LARGE_frontbuffer_pa = (unsigned long) SavedLFB;
    LARGE_backbuffer_pa  = (unsigned long) LARGESYSTEM_BACKBUFFER;
    LARGE_pagedpool_pa   = (unsigned long) LARGESYSTEM_PAGEDPOLL_START;
    LARGE_heappool_pa    = (unsigned long) LARGESYSTEM_HEAPPOLL_START;
    LARGE_extraheap1_pa  = (unsigned long) LARGESYSTEM_EXTRAHEAP1_START;
    LARGE_extraheap2_pa  = (unsigned long) LARGESYSTEM_EXTRAHEAP2_START;
    LARGE_extraheap3_pa  = (unsigned long) LARGESYSTEM_EXTRAHEAP3_START;


	// ** bank 1 ** //
	// O primeiro banco representa o m�nimo de mem�ria RAM que o sistema 
	// operacional suporta, 32MB. 
	// Dentro deve conter tudo. At� cache e frames para mem�ria paginada.
	// Endere�os da mem�ria f�sicas acess�veis em Kernel Mode.
	// Kernel process.
	// >> Os 4 primeiros mega da mem�ria fisica.     
	// >> A imagem do kernel que come�a no primeiro mega.
	// >> Endere�os da mem�ria f�sicas acess�veis em User Mode.
	// >> VGA, VESA LFB, BACKBUFFER e PAGEDPOOL
    // #Importante.
    // Esse endere�o servir� para sistema de 32Mb e para sistemas 
    // com mais que 32Mb de RAM.
    // Para um sistema de 32MB a �rea de pagedpool deve acabar 
    // em 0x01FFFFFF.

	
	//=====================================================
	// A mem�ria f�sica � dividida em duas partes principais: 
	// + System Zone. (oito bancos de 32MB come�ando em 0)
	// + Window Zone. (Uma user session come�ando em 0x10000000)
	//
	//=====================================================	


	// O n�mero m�ximo de bancos no sistema ser� 8.
	// Se o sistema for pequeno, teremos menos bancos.
	// Se o sistema for grande o bastante, teremos 8 bancos e uma user session.
	// Mas o sistema sempre ser� composto de bancos e uma user session.
	// A quantidade de bancos ser� contada em vari�veis globais.
	
	
	//==================================================================
	
	//
	// **** Endere�os iniciais �reas de mem�ria 'n�o paginada'.
	//
	
	
	// *importante:
    // ?? e se o sistema tiver 	
	
	
	//==================================================================
	// ### importante ###
	// Essa rotina vai configurar s� o deiret�rio de p�ginas do processo kernel.
	
	
	// DIRECTORY:
	//     Diret�rio do processo Kernel. Esse diret�rio j� foi criado nesse 
	// endere�o f�sico pelo Boot Loader. Aqui o kernel apenas reconfigura, 
	// utilizando a mesma localiza�ao. KERNEL_PAGEDIRECTORY.
	// ??

	// Esse valor precisa ser determinado, pois ainda n�o temos 
	// como usar algum alocador, pois sem a mem�ria inicializada,
	// n�o temos alocador.

    //
    // Directory.
    //

    // 0x0009C000 = Kernel page directory
    gKernelPageDirectoryAddress = XXXKERNEL_PAGEDIRECTORY;    

    unsigned long *page_directory = (unsigned long *) gKernelPageDirectoryAddress; 



	// O que temos logo abaixo s�o pequenas parti��es de mem�ria f�sica.
	// cada parti��o tem 1024 unsigned longs. o que d� 4KB cada. 
	
	
	// TABLES: 
	//     Tabelas de p�ginas para o diret�rio do processo Kernel. Essas 
	// tabelas j� foram criadas nesses endere�os f�sicos pelo Boot Loader. 
	// Aqui o Kernel apenas reconfigura utilizando as mesmas localiza��es.
	
	
	// Poder�amos alocar mem�ria para as page tables ??
	// Sim, mas precisa ser um mecanismo que devolva o endere�o f�sico 
	// de onde foi alocado mem�ria para a page table.
	// Na verdade deve haver uma �rea de mem�ria reservada para a aloca��o 
	// de page tables. Todas as que ser�o criadas ocupar�o muito espa�o.

	//
	// SYSTEM MEMORY * NONPAGED POOLS 
	//
	
	//*Importante:
	// @todo: N�o mudar o endere�o onde essas tabelas foram construidas.
	// Esses endere�os est�o bem organizados, essa ser� o in�cio da mem�ria 
	// n�o paginada do processo kernel.
	// Todas as p�ginas mapeadas aqui nunca ser�o enviadas para a mem�ria secund�ria 
	// ou seja nunca mudar�o de endere�o f�sico.
	//
	// 0x0008F000 Tabela para mapear a parte mais baixa da mem�ria f�sica. Come�a em 0.
	// 0x0008E000 Tabela para mapear a mem�ria usada pela imagem do kernel. Come�a em 0x100000.
	// 0x0008D000 Tabela para mapear uma �rea em user mode onde rodam c�digos. Come�a em 0x400000.
	// 0x0008C000 Tabela para mapear a vga. Come�a em 0xb8000.
	// 0x0008B000 Tabela para mapear o frontbuffer, O come�o � passado pelo Boot.
	// 0x0008A000 Tabela para mapear o backbuffer, o come�o � em (0x01000000 - 0x400000) no small system.
	// 0x00089000 Tabela de p�ginas para o pagedpool.


    // kernel mode. (Endere�os). 0x0008F000
    unsigned long *km_page_table = (unsigned long *) PAGETABLE_KERNELAREA; 

    // kernel mode. (O kernel). 0x0008E000
    unsigned long *km2_page_table = (unsigned long *) PAGETABLE_KERNELBASE; 

    // user mode. 0x0008D000
    unsigned long *um_page_table = (unsigned long *) PAGETABLE_USERBASE;

    // user mode. (vga). 0x0008C000
    unsigned long *cga_page_table = (unsigned long *) PAGETABLE_CGA;

    // user mode. (LFB). 0x0008B000
    unsigned long *frontbuffer_page_table = (unsigned long *) PAGETABLE_FRONTBUFFER;

    // user mode. (buffer). backbuffer 0x0008A000
    unsigned long *backbuffer_page_table = (unsigned long *) PAGETABLE_BACKBUFFER;

    // pagetable para o pagedpool 0x00089000
    unsigned long *pagedpool_page_table = (unsigned long *) PAGETABLE_PAGEDPOOL;

    // um endere�o f�sico para a pagetable que mapear� os buffers.
    unsigned long *heappool_page_table = (unsigned long *) PAGETABLE_HEAPPOOL; 


    // #todo
    // Extra heaps. Rever!

    unsigned long *extraheap1_page_table = (unsigned long *) PAGETABLE_EXTRAHEAP1;
    unsigned long *extraheap2_page_table = (unsigned long *) PAGETABLE_EXTRAHEAP2;
    unsigned long *extraheap3_page_table = (unsigned long *) PAGETABLE_EXTRAHEAP3;

    //...

	//
	// SYSTEM MEMORY * PAGED POOLS 
	//


    //Criaremos por enquanto apenas uma pagetable com mem�ria paginada.
    //unsigned long *paged_page_table = (unsigned long *) ??;  //BUFFER_PAGETABLE.	


    // Message. (verbose).

#ifdef PS_VERBOSE
    printf ("mmSetUpPaging: Initializing Pages..\n");
#endif


	//
	// # DIRECTORIES
	//

	// Preenchendo todo o diret�rio de p�ginas do kernel com p�ginas 
	// n�o presentes. Usando um endere�o nulo de p�gina.

	// Inicializando quatro diret�rios.
	// o bit 7 da entrada permanece em 0, 
	// indicando que temos p�ginas de 4KB.
	// kernel
	// Diret�rio de p�ginas do processo kernel.
	// 0 no bit 2 indica qual level ??
	// 010 em bin�rio.

    // #importante:
    // O endere�o f�sico e virtual s�o iguais para essa tabela.
    
    for ( i=0; i < 1024; ++i ){
        page_directory[i] = (unsigned long) 0 | 2; 
    };



	//
	// # PAGE TABLE. (Kernel area)
	//

	//===========================================================
	// kernel mode pages (0fis = 0virt)
	// SMALL_kernel_address = 0.
	// Mapear os primeiros 4MB da mem�ria. (kernel mode). Preenchendo a tabela 
	// km_page_table. A entrada 0 do diret�rio refere-se aos primeiros 4 megas 
	// de endere�o virtual.
	//
    // Aqui estamos pegando uma parti��o de mem�ria f�sica de 4MB que come�a no 
	// in�cio da mem�ria RAM.
    // Obs: Essa page table d� acesso aos primeiros 4MB da mem�ria f�sica,
	// Isso inclu a �rea do kernel base que come�a no primeiro MB. Manipular
	// esse espa�o pode corromper o kernel base.
	//
	// A inten��o aqui � que o kernel base possa manipular as �reas baixas da 
	// mem�ria f�sica com facilidade. Por�m, para os outros processos, os endere�os 
	// l�gicos mais baixos n�o devem corresponder aos endere�os f�sicos mais baixos,
	// por seguran�a, apenas o kernel base deve ter acesso � essa �rea.
	// Para alguns processos especiais, algum tipo de permiss�o poder� ser concedida.
	//
    
	
	// Configurando uma pagetable.
	// a pagetable para os primeiros 4MB de mem�ria f�sica. 
	// kernel mode pages (0fis = 0virt)
	// 011 bin�rio.
	// >>> kernel mode.
	// Criando a entrada n�mero '0' do diret�rio de p�ginas do processo Kernel.
	// que apontar� para a pagetable que criamos.
	// o bit 7 da entrada permanece em 0, indicando que temos p�ginas de 4KB.
	// Salva no diret�rio o endere�o f�sico da tabela.
	// Configurando os atributos.	
	
    // 4096 KB = (4 MB).
    mm_used_kernel_area = (1024 * 4);  


    // #importante:
    // O endere�o f�sico e virtual s�o iguais para essa tabela.

    for ( i=0; i < 1024; ++i )
    {
        km_page_table[i] = (unsigned long) SMALL_origin_pa | 3;     
        SMALL_origin_pa  = (unsigned long) SMALL_origin_pa + 4096;  
    };
    page_directory[ENTRY_KERNELMODE_PAGES] = (unsigned long) &km_page_table[0];      
    page_directory[ENTRY_KERNELMODE_PAGES] = (unsigned long) page_directory[ENTRY_KERNELMODE_PAGES] | 3;  



	//
	// # PAGE TABLE, (Kernel image)
	//

    //===============================================
    // kernel mode pages (0x00100000fis = 0xC0000000virt)
    // SMALL_kernel_base_address = 0x00100000 = KERNEL_BASE.
    // Mapear 4MB come�ando do primeiro mega. (kernel mode).
    // Preenchendo a tabela km2_page_table.
    //
    // Aqui estamos pegando uma parti��o de mem�ria f�sica de 4MB 
    // que come�a no endere�o f�sico que carregamos a imagem do kernel.
    // S�o 4MB de mem�ria f�sica, come�ando do primeiro MB, 
    // onde o KERNEL.BIN foi carregado.

    // Criando uma pagetable.
    // 4MB de mem�ria f�sica, come�ando em 1MB.
    // kernel mode pages (0x00100000fis = 0xC0000000virt)
    // 011 bin�rio.
    // >>> (kernel mode).
    // Criando a  entrada do diret�rio de p�ginas do processo kernel.
    // O bit 7 da entrada permanece em 0, indicando que 
    // temos p�ginas de 4 KB.
    // Salva no diret�rio o endere�o f�sico.
    // Configurando os atributos.

    // #importante:
    // O endere�o f�sico e virtual s�o iguais para essa tabela.

    for ( i=0; i < 1024; ++i )
    {
        km2_page_table[i]    = (unsigned long) SMALL_kernel_base_pa | 3; 
        SMALL_kernel_base_pa = (unsigned long) SMALL_kernel_base_pa + 4096; 
    };
    page_directory[ENTRY_KERNELBASE_PAGES] = (unsigned long) &km2_page_table[0]; 
    page_directory[ENTRY_KERNELBASE_PAGES] = (unsigned long) page_directory[ENTRY_KERNELBASE_PAGES] | 3;  


    // Obs: 
    // Percebe-se que houve uma sobreposi��o. Os megas 0,1,2,3 para
    // kernel mode e os megas 1,2,3,4 para o kernel base.
    // Isso significa que o Kernel Base pode acessar o primeiro mega
    // da mem�ria f�sica, usando endere�o virtual igual ao endere�o f�sico.


	//
	// #PAGETABLE. (User base)
	//

    //==============================================================
    // user mode pages - (0x00400000fis = 0x00400000virt)
    // SMALL_user_address = 0x00400000 = USER_BASE.
    // Mapear 4MB da mem�ria come�ando em 0x00400000fis. (user mode).
    //
    // Aqui estamos pegando uma parti��o de mem�ria f�sica de 4MB 
    // que come�a no endere�o f�sico 0x00400000, no quarto mega da 
    // mem�ria f�sica. 
    // � nesse endere�o l�gico que ficar�o os processos em user mode.
    // Cada processo ter� um diret�rio de p�ginas, e nesse diret�rio de 
    // p�ginas ter� uma page table que atribuir� o endere�o l�gico 
    // de 0x400000 � algum endere�o f�sico alocado din�micamente 
    // para receber a imagem do processo.
    // Obs: 
    // Se o processo tiver mais que 4MB de tamanho, ent�o ser� preciso 
    // de mais de uma pagetable.


    // Criando uma pagetable.
    // 4MB de mem�ria f�sica, come�ando do querto mega.
    // user mode pages - (0x00400000fis = 0x00400000virt)
    // ser� usado pelo processo em user mode. Note as flags.(7).
    // 7 decimal � igual a 111 bin�rio.
    // >>> (user mode).
    // Criando a entrada do diret�rio de p�ginas do processo kernel.
    // o bit 7 da entrada permanece em 0, indicando que temos 
    // p�ginas de 4KB.
    // Salva no diret�rio o endere�o f�sico.
    // Configurando os atributos.

    // 4096 KB = (4 MB).
    mm_used_user_area = (1024 * 4);  

    // #importante:
    // O endere�o f�sico e virtual s�o iguais para essa tabela.

    for ( i=0; i < 1024; ++i )
    {
        um_page_table[i]  = (unsigned long) SMALL_user_pa | 7; 
        SMALL_user_pa     = (unsigned long) SMALL_user_pa + 4096; 
    };
    page_directory[ENTRY_USERMODE_PAGES] = (unsigned long) &um_page_table[0]; 
    page_directory[ENTRY_USERMODE_PAGES] = (unsigned long) page_directory[ENTRY_USERMODE_PAGES] | 7; 


    // Obs: 
    // Novamente aqui h� uma sobreposi��o. 
    // O primeiro mega dessa �rea destinada � user mode, � o mesmo 
    // �ltimo mega da �rea destinada ao Kernel Base. 
    // Isso significa uma �rea de mem�ria compartilhada. 
    // O que est� no primeiro mega dessa �rea em user mode tamb�m est� 
    // no �ltimo mega da �rea do kernel base.

  
    //
    // #PAGE TABLE. (VGA).
    //

    // ==============================================================
    // user mode VGA pages - ( 0x000B8000fis = 0x00800000virt)
    // SMALL_vga_address  = VM_BASE;   //0x000B8000;
    // Mapear 4MB da mem�ria come�ando em 0x000B8000fis. (user mode).
    // todo: 
    // Aqui na verdade n�o precisa configurar 4 megas, 
    // apenas o tamanho da mem�ria de v�deo presente em 0xb8000.
    // Aqui estamos pegando uma parti��o de mem�ria f�sica de 4MB 
    // que come�a no endere�o f�sico 0x000B8000.
    // todo: 
    // bugbug: ESSA � CGA E N�O A VGA.
    // Mudar o nome para cga.
 
 
    // Criando uma pagetable.
    // 4MB de mem�ria f�sica, come�ando 0x000B8000fis.
    // user mode VGA pages - ( 0x000B8000fis = 0x00800000virt)
    // Podemos permitir que alguns processos em user mode acessem
    // essa �rea diretamente.
    // 7 decimal � igual a 111 bin�rio.
    // >>> (user mode).
    // Criando a entrada do diret�rio de p�ginas do processo kernel.
    // o bit 7 da entrada permanece em 0, indicando que temos 
    // p�ginas de 4KB.
    // Salva no diret�rio o endere�o f�sico.
    // Configurando os atributos.

    // #importante:	
    // O endere�o f�sico e virtual s�o iguais para essa tabela.

    for ( i=0; i < 1024; ++i )
    {
        cga_page_table[i] = (unsigned long) SMALL_cga_pa | 7; 
        SMALL_cga_pa      = (unsigned long) SMALL_cga_pa + 4096; 
    };
    page_directory[ENTRY_CGA_PAGES] = (unsigned long) &cga_page_table[0]; 
    page_directory[ENTRY_CGA_PAGES] = (unsigned long) page_directory[ENTRY_CGA_PAGES] | 7;  


    // Obs: 
    // 4MB, come�ando do endere�o f�sico 0x000B8000, 
    // s�o acess�veis em user mode � partir do endere�o virtual 
    // 0x00800000virt.



	//
	// # PAGETABLE. (Front buffer).
	//

    // 0xC0400000; 
    g_frontbuffer_va = (unsigned long) FRONTBUFFER_ADDRESS; 


    // ================================================================
    // user mode LFB pages - (0x????????fis = 0xC0400000virt).
    // SMALL_frontbuffer_address  = SavedLFB = g_lbf_pa, 
    // Foi passado pelo boot manager.
    // Mapear 4MB da mem�ria f�sica come�ando no valor do 
    // endere�o f�sico do LFB que foi passado pelo Boot Manager.
    // O endere�o de mem�ria l�gica utilizada � 4MB � partir de 
    // 0xC0400000.
    //
    // Aqui estamos pegando uma parti��o de mem�ria f�sica de 4MB 
    // que come�a no endere�o f�sico do LFB, de valor desconhecido. 
    // Foi configurado em modo real, pelo m�todo VESA.
    //
    // todo: 
    // LFB needs to be bigger. 
    // (Ex: Four 8GB graphic cards).
    // But the driver needs to do all the work.
    //

    // Criando uma pagetable. (user mode)
    // Os quatro primeiros MB da mem�ria de v�deo.
    // user mode LFB pages - (0x????????fis = 0xC0400000virt).
    // provavelmente o endere�o f�sico � 0xE0000000
    // >>> (user mode).
    // 7 decimal � igual a 111 bin�rio.
    // Criando a entrada do diret�rio de p�ginas do processo kernel.
    // o bit 7 da entrada permanece em 0, indicando que temos 
    // p�ginas de 4KB.
    // Salva no diret�rio o endere�o f�sico.
    // Configurando os atributos.

    // 4096 KB = (4 MB).
    mm_used_lfb = (1024 * 4);  

    // #importante:	
    // O endere�o f�sico e virtual s�o iguais para essa tabela.

    for ( i=0; i < 1024; ++i )
    {
        frontbuffer_page_table[i] = (unsigned long) SMALL_frontbuffer_pa | 7; 
        SMALL_frontbuffer_pa      = (unsigned long) SMALL_frontbuffer_pa + 4096; 
    };
    page_directory[ENTRY_FRONTBUFFER_PAGES] = (unsigned long) &frontbuffer_page_table[0]; 
    page_directory[ENTRY_FRONTBUFFER_PAGES] = (unsigned long) page_directory[ENTRY_FRONTBUFFER_PAGES] | 7; 


	//
	// # PAGETABLE. (Back buffer).
	//


    // 0xC0800000;
    g_backbuffer_va = (unsigned long) BACKBUFFER_ADDRESS;  


    //===============================================================
    // user mode BUFFER1 pages - 0x800000fis = 
    // (0x01000000 - 0x800000 fis) = 0xC0800000virt).
    //
    // BackBuffer: 
    // � o buffer onde se pinta o que aparecer� na tela. O conte�do 
    // desse buffer � copiado no LFB da mem�ria de v�deo, 
    // (refresh_screen).
    // SMALL_backbuffer_address = , #Provis�rio.
    // O endere�o de mem�ria l�gica utilizada � 4MB � partir de 
    // 0xC0800000.
    //
    // Aqui estamos pegando uma parti��o de mem�ria f�sica de 4MB, 
    // que come�a no endere�o f�sico, no decimo sexto mega da 
    // mem�ria f�sica. 
 
 
    // criando uma page table.
    // 4MB de me�ria f�sica, come�ando em 16MB, que ser�o usados 
    // para backbuffer. 
    // Obs 
    // Essa �rea deve ter no m�nimo o mesmo tamanho do frontbuffer.
    // user mode BUFFER1 pages - ((0x01000000 - 0x800000 fis) = 
    // 0xC0800000virt).
    // >>> (user mode).
    // 7 decimal � igual a 111 bin�rio.
    // Criando a entrada do diret�rio de p�ginas do processo kernel.
    // o bit 7 da entrada permanece em 0, indicando que temos p�ginas 
    // de 4KB.
    // Salva no diret�rio o endere�o f�sico.
    // Configurando os atributos.

    // 4096 KB = (4 MB).
    mm_used_backbuffer = (1024 * 4);  

    // #importante:
    // O endere�o f�sico e virtual s�o iguais para essa tabela.

    for ( i=0; i < 1024; ++i )
    {
        backbuffer_page_table[i] = (unsigned long) SMALL_backbuffer_pa | 7; 
        SMALL_backbuffer_pa      = (unsigned long) SMALL_backbuffer_pa + 4096; 
    };
    page_directory[ENTRY_BACKBUFFER_PAGES] = (unsigned long) &backbuffer_page_table[0]; 
    page_directory[ENTRY_BACKBUFFER_PAGES] = (unsigned long) page_directory[ENTRY_BACKBUFFER_PAGES] | 7; 


    // Obs: 
    // 4MB da mem�ria f�sica, � partir do endere�o f�sico 0x01000000 
    // (marca de 16MB), s�o destinados ao back buffer. 
    // Obs: 
    // Isso � bem pouco, uma tela com alta resolu��o usa mais que isso.


	//
	// # PAGETABLE. (Paged pool).
	//


    // 0xC0C00000;
    g_pagedpool_va = (unsigned long) XXXPAGEDPOOL_VA;  


    // >>> (user mode)
    // 7 decimal � igual a 111 bin�rio.
    // Criando a entrada do diret�rio de p�ginas do processo kernel.
    // O bit 7 da entrada permanece em 0, indicando que temos p�ginas 
    // de 4KB.
    // Salva no diret�rio o endere�o f�sico.
    // Configurando os atributos.


    // 4096 KB = (4 MB).
    mm_used_pagedpool = (1024 * 4); 

    // #importante:
    // O endere�o f�sico e virtual s�o iguais para essa tabela.

    for ( i=0; i < 1024; ++i )
    {
        pagedpool_page_table[i] = (unsigned long) SMALL_pagedpool_pa | 7; 
        SMALL_pagedpool_pa      = (unsigned long) SMALL_pagedpool_pa + 4096; 
    };
    page_directory[ENTRY_PAGEDPOOL_PAGES] = (unsigned long) &pagedpool_page_table[0]; 
    page_directory[ENTRY_PAGEDPOOL_PAGES] = (unsigned long) page_directory[ENTRY_PAGEDPOOL_PAGES] | 7; 


    // Endere�o virtual do pool de heaps.
    // Os heaps nessa �rea ser�o dados para os processos.

    g_heappool_va = (unsigned long) XXXHEAPPOOL_VA; //0xC1000000;
    g_heap_count = 0;
    g_heap_count_max = G_DEFAULT_PROCESSHEAP_COUNTMAX;
    g_heap_size = G_DEFAULT_PROCESSHEAP_SIZE;


    // >> (user mode).
    // Heaps support.
    // Preparando uma �rea de mem�ria grande o bastante para conter 
    // o heap de todos os processos.
    // ex: 
    // Podemos dar 128 KB para cada processo inicialmente.

    // 4096 KB = (4 MB).
    mm_used_heappool = (1024 * 4);  

    // #importante:
    // O endere�o f�sico e virtual s�o iguais para essa tabela.

    for ( i=0; i < 1024; ++i )
    {
        heappool_page_table[i] = (unsigned long) SMALL_heappool_pa | 7; 
        SMALL_heappool_pa      = (unsigned long) SMALL_heappool_pa + 4096; 
    };
    page_directory[ENTRY_HEAPPOOL_PAGES] = (unsigned long) &heappool_page_table[0]; 
    page_directory[ENTRY_HEAPPOOL_PAGES] = (unsigned long) page_directory[ENTRY_HEAPPOOL_PAGES] | 7;  


    //
    // Extra heaps.
    //


    // +++++++
    // Extra heap 1.
    // >>> (user mode).
    g_extraheap1_va = (unsigned long) XXXEXTRAHEAP1_VA;  //0xC1400000;
    g_extraheap1_size = G_DEFAULT_EXTRAHEAP_SIZE;        //4MB


    // 4096 KB = (4 MB).
    mm_used_extraheap1 = (1024 * 4);  

    // #importante:
    // O endere�o f�sico e virtual s�o iguais para essa tabela.
    
    for ( i=0; i < 1024; ++i )
    {
        extraheap1_page_table[i] = (unsigned long) SMALL_extraheap1_pa | 7; 
        SMALL_extraheap1_pa      = (unsigned long) SMALL_extraheap1_pa + 4096; 
    };
    page_directory[ENTRY_EXTRAHEAP1_PAGES] = (unsigned long) &extraheap1_page_table[0]; 
    page_directory[ENTRY_EXTRAHEAP1_PAGES] = (unsigned long) page_directory[ENTRY_EXTRAHEAP1_PAGES] | 7;  



    // +++++++
    // Extra heap 2.
    // >>> (user mode).
    g_extraheap2_va = (unsigned long) XXXEXTRAHEAP2_VA;  //0xC1800000;
    g_extraheap2_size = G_DEFAULT_EXTRAHEAP_SIZE;        //4MB


    // 4096 KB = (4 MB).
    mm_used_extraheap2 = (1024 * 4);  

    // #importante:	
    // O endere�o f�sico e virtual s�o iguais para essa tabela.

    for ( i=0; i < 1024; ++i )
    {
        extraheap2_page_table[i] = (unsigned long) SMALL_extraheap2_pa | 7; 
        SMALL_extraheap2_pa      = (unsigned long) SMALL_extraheap2_pa + 4096; 
    };
    page_directory[ENTRY_EXTRAHEAP2_PAGES] = (unsigned long) &extraheap2_page_table[0]; 
    page_directory[ENTRY_EXTRAHEAP2_PAGES] = (unsigned long) page_directory[ENTRY_EXTRAHEAP2_PAGES] | 7;  


    // +++++++
    // Extra heap 3.
    // >>> (user mode). 
    g_extraheap3_va = (unsigned long) XXXEXTRAHEAP3_VA;  //0xC1C00000;
    g_extraheap3_size = G_DEFAULT_EXTRAHEAP_SIZE;        //4MB

    // 4096 KB = (4 MB).
    mm_used_extraheap3 = (1024 * 4);  

    // #importante:
    // O endere�o f�sico e virtual s�o iguais para essa tabela.

    for ( i=0; i < 1024; ++i )
    {
        extraheap3_page_table[i] = (unsigned long) SMALL_extraheap3_pa | 7; 
        SMALL_extraheap3_pa      = (unsigned long) SMALL_extraheap3_pa + 4096; 
    };
    page_directory[ENTRY_EXTRAHEAP3_PAGES] = (unsigned long) &extraheap3_page_table[0]; 
    page_directory[ENTRY_EXTRAHEAP3_PAGES] = (unsigned long) page_directory[ENTRY_EXTRAHEAP3_PAGES] | 7; 

    // ...


    //
    // == Frame table =============================================
    //

    // Vamos configurar a frame table de acordo com o
    // total de memória ram.


    // Size in KB.
    // Se for maior que 1 GB.
    // Se for maior que 1024 MB. 
    // (1024*1024) KB
    if ( memorysizeTotal > (1024*1024)  )
    {
        FT.frame_table_start = FRAME_TABLE_START_PA;  // 64 MB mark. 
        FT.frame_table_end   = (0x40000000 - 1);      // 1GB -1 mark.
        FT.frame_table_size_in_bytes  = (FT.frame_table_end - FT.frame_table_start);
        //memória utilizada para isso.dado em kb.
        mm_used_frame_table = (FT.frame_table_size_in_bytes/1024); 


    // Size in KB.
    // Se for maior que 512 MB.
    // (512*1024)KB
    } else if ( memorysizeTotal > (512*1024) ){

        FT.frame_table_start = FRAME_TABLE_START_PA;  // 64 MB mark. 
        FT.frame_table_end   = (0x20000000 - 1);      // 512 MB -1 mark.
        FT.frame_table_size_in_bytes  = (FT.frame_table_end - FT.frame_table_start);
        //memória utilizada para isso.dado em kb.
        mm_used_frame_table = (FT.frame_table_size_in_bytes/1024); 

    // Size in KB.
    // Se for maior que 256 MB.
    // (256*1024)KB
    } else if ( memorysizeTotal > (256*1024) ){

        FT.frame_table_start = FRAME_TABLE_START_PA;  // 64 MB mark. 
        FT.frame_table_end   = (0x10000000 - 1);      // 256 MB -1 mark.
        FT.frame_table_size_in_bytes  = (FT.frame_table_end - FT.frame_table_start);
        //memória utilizada para isso.dado em kb.
        mm_used_frame_table = (FT.frame_table_size_in_bytes/1024); 

    // Size in KB.
    // Se for maior que 128 MB.
    // (128*1024) KB
    } else if ( memorysizeTotal > (128*1024) ){

        FT.frame_table_start = FRAME_TABLE_START_PA;  // 64 MB mark. 
        FT.frame_table_end   = (0x08000000 - 1);      // 128 MB -1 mark.
        FT.frame_table_size_in_bytes  = (FT.frame_table_end - FT.frame_table_start);
        //memória utilizada para isso.dado em kb.
        mm_used_frame_table = (FT.frame_table_size_in_bytes/1024); 


    // #ERROR
    // A memória tem menos de 128 MB ou igual,
    // Então não conseguiremos criar uma frame_table 
    // que começe na marca de 64 MB.

    }else{

        debug_print ("mmSetUpPaging: [PANIC] We need 256 MB of RAM\n");
        kprintf     ("mmSetUpPaging: [PANIC] We need 256 MB of RAM\n");
        refresh_screen();
        //die();
        
        panic2       ("mmSetUpPaging: [PANIC] We need 256 MB of RAM\n");
    };


    //
    // Memory size.
    //


    // #Importante
    // Agora vamos calcular a quantidade de mem�ria f�sica usada 
    // at� agora.
    // Levando em conta a inicializa��o que fizemos nessa rotina.
    // Estamos deixando de fora a mem�ria dos dispositivos, pois a 
    // mem�ria usada pelos dispositivos possuem endere�o f�sico, 
    // mas est� na parte alta do endere�amento f�sico, muito al�m da 
    // mem�ria RAM instalada.
    // Com a exce��o da vga, que fica antes de 1MB.
    // Os dispositivos por enquanto s�o mem�ria de v�deo e placa 
    // de rede.
    // Tem a quest�o do dma a se considerar tamb�m.
    // Tem dma abaixo da marca de 16mb.
    // Tem dma que usa mem�ria virtual.



    // Used.
    memorysizeUsed = (unsigned long) ( mm_used_kernel_area + 
        mm_used_user_area + 
        mm_used_backbuffer + 
        mm_used_pagedpool + 
        mm_used_heappool + 
        mm_used_extraheap1 + mm_used_extraheap2 + mm_used_extraheap3 +
        mm_used_frame_table );

    // Free.
    memorysizeFree = memorysizeTotal - memorysizeUsed;


    // #todo:  
	// (sobre heaps para processos em user mode).
	// O que precisa ser feito no momento:
	// + Os processos em user mode precisam aloca��o din�mica de mem�ria, 
	// para isso ser� usado o heap do processo ou o heap do desktop ao qual o 
	// processo pertence.

	// #todo:
	// *IMPORTANTE: 
	// (sobre heaps para gerenciamento de recursos gr�ficos).
	// + Os buffers de janela ser�o alocados no heap do processo em user mode 
	// que gerencia a cria��o de janelas, portanto esse processo tem que ter 
	// bastante heap dispon�vel. Talvez quem fa�a esse papel seja o pr�prio 
	// kernel base, a� quem precisa de bastante heap � o kernel base.
	// Talvez seja um m�dulo em kernel mode que gerencie as janelas.
	// Por enquanto � a camada superior do kernel base. Mas interfaces poder�o
	// chamar essa camada no kernel base e oferecerem servi�os de gerenciamento
	// de recursos gr�ficos, utilizando apenas as primitivas oferecidas pelo 
	// kernel base. Essas bibliotecas que oferecem recursos gr�ficos podem 
	// ser processos em kernel mode ou em user mode. Elas oferecer�o recursos 
	// bem elaborados e completos, chamando o kernel base apenas para 
	// as rotinas primitivas. Isso facilita a cria��o de recursos gr�ficos,
	// por�m prejudica o desempenho, por isso o kernel base tamb�m oferece 
	// seu conjunto de recursos gr�ficos mais elaborados, al�m das primitivas,
	// � claro.


	// @todo: 
	// Continuar: Mais p�ginas podem ser criadas manualmente agora.
	// Porem a inten��o � utilizar rotinas de automa��o da cria��o 
	// de paginas, pagetable e diret�rios.


	// @todo: 
	// At� agora tem uma sobreposi��o danada no mapeamento um mesmo 
	// endere�o f�sico de mem�ria � mapeado para v�rios endere�os virtuais. 
	// Isso n�o � proibido, � assim que se comaprtilha mem�ria. Na pr�tica
	// podemos acessar a mesma regi�o de mem�ria de v�rias maneira diferentes.
	// Mas devemos tomar cuidado, principalmente para n�o corrompermos o 
	// kernel base.
	// O acesso a mem�ria compartilhada ser� gerenciado pelos mecanismos
	// padr�o de comunica��o e compartilhamento. Sem�foros e mutexes ...


	// @todo: 
	// *IMPORTANTE.
	// O que queremos � utilizar uma lista de frames livres na hora
	// configurarmos o mapeamento. Queremos pegar um frame livre e
	// associarmos ele com uma PTE, (entrada na tabela de p�ginas).
	// O que est� faltando � o gerenciamento de mem�ria f�sica.
	// O gerenciamento de mem�ria f�sica � feito dividindo a mem�ria f�sica 
	// em parti��es, peda�os grandes de mem�ria. Tem um m�dulo que trata
	// de bancos, aspaces no kernel base.
	
	
	// @todo:
	// *SUPER IMPORTANTE.
	// para gerenciarmos a me�ria f�sica, precisamos saber o tamanho 
	// da mem�ria f�sica disponpivel. tem um m�dulo no kernel base 
	// que trata disso.
	// * Depois de alocarmos uma regi�o grande da mem�ria f�sica,
	// destinada para frames, ent�o criaremos a lista de frames livres.
	// que significar� uma quantidade de frames livres dentro da �rea 
	// destinadas � frames. N�o significa �rea toda a �rea livre
	// na mem�ria f�sica, mas apenas os frames livres dentro da regi�o 
	// destinada aos frames.

	// Debug:
	//     Mostrando os endere�os do diret�rio e das p�ginas.
	//     #verbose.


#ifdef PS_VERBOSE
    printf ("Debug:\n");
    printf ("Setup CR3={%x}\n", (unsigned long) &page_directory[0]);
    printf ("Page={%x} \n",     (unsigned long) &km_page_table[0]);
    printf ("Page={%x} \n",     (unsigned long) &km2_page_table[0]);
    printf ("Page={%x} \n",     (unsigned long) &um_page_table[0]);
    printf ("Page={%x} \n",     (unsigned long) &cga_page_table[0]);
    printf ("Page={%x} \n",     (unsigned long) &frontbuffer_page_table[0]);
    printf ("Page={%x} \n",     (unsigned long) &backbuffer_page_table[0]);
    printf ("Page={%x} \n",     (unsigned long) &pagedpool_page_table[0]);
    // ...
	//refresh_screen();
	//while(1){};
#endif

	// Obs: 
	// Podemos reaproveitas pagetables em diferentes processos.

    // Salvando o endere�o do diret�rio do processo Kernel no CR3. 

    x86_SetCR3 ( (unsigned long) &page_directory[0] );


    // LISTAS:
    // Configurando a lista de diret�rios e a lista de 
    // tabelas de p�ginas.
    // Salvando na lista o endere�o f�sico dos diret�rios e 
    // das tabelas de p�ginas.


    //
    // Inicializar a lista de diret�rios de p�ginas.
    // 


    for ( i=0; i < PAGEDIRECTORY_COUNT_MAX; ++i )
    {
        pagedirectoryList[i] = (unsigned long) 0;
    };

    //O primeiro diret�rio da lista � o diret�rio do kernel.
    pagedirectoryList[0] = (unsigned long) &page_directory[0]; //kernel.
    //pagedirectoryList[1] = (unsigned long) 0;
    //...


	//
	// Inicializando a lista de pagetables..
	//

    for ( i=0; i < PAGETABLE_COUNT_MAX; ++i )
    {
        pagetableList[i] = (unsigned long) 0;
    };

    //Configurando manualmente as primeiras entradas da lista.
	pagetableList[0] = (unsigned long) &km_page_table[0];
	pagetableList[1] = (unsigned long) &km2_page_table[0];
	pagetableList[2] = (unsigned long) &um_page_table[0];
	pagetableList[3] = (unsigned long) &cga_page_table[0];
	pagetableList[4] = (unsigned long) &frontbuffer_page_table[0];
	pagetableList[5] = (unsigned long) &backbuffer_page_table[0];
	//pagetableList[6] = (unsigned long) 0;
    //...


	//
	// Inicializando a lista de framepools. (parti��es)
	//

    for ( i=0; i < FRAMEPOOL_COUNT_MAX; ++i )
    {
        framepoolList[i] = (unsigned long) 0;
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
    kfp = (void *) kmalloc ( sizeof(struct frame_pool_d) );
	
	// #todo: e se falhar?
	
    if ( (void *) kfp != NULL  )
    {
		kfp->id = 0;
		kfp->used = 1;
		kfp->magic = 1234;
		
		//?? Come�a em 0 MB. ??
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
    small_fp = (void *) kmalloc ( sizeof(struct frame_pool_d) );
	
	// #todo: e se falhar.
	
    if ( (void *) small_fp != NULL  )
    {
		small_fp->id = 1;
		small_fp->used = 1;
		small_fp->magic = 1234;
		
		//Come�a em 4 MB.
		small_fp->address = (unsigned long) (4 * MB);   

		//pertence ao processo kernel.
		small_fp->process = (void*) NULL; //??;

		small_fp->next =  NULL;
		//...

		//salva e ponteiro global.
		framepoolSmallSystemUserSpace = (void *) small_fp;

		// Salva na lista.
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
    pageable_fp = (void *) kmalloc ( sizeof(struct frame_pool_d) );
 
    //#todo e se falhar?

    if( (void *) pageable_fp != NULL  )
    {
		pageable_fp->id = 5;   //quinto �ndice.
		pageable_fp->used = 1;
		pageable_fp->magic = 1234;
		
		//Come�a em 20 MB.
		pageable_fp->address = (unsigned long) (20 * MB);   

		//pertence ao processo kernel.
		pageable_fp->process = (void*) NULL; //??
		
		pageable_fp->next =  NULL;
		//...

		//salva em ponteiro global.
		framepoolPageableSpace = (void*) pageable_fp;

		// Salva na lista.
        framepoolList[5] = (unsigned long) pageable_fp;
    };


	// More ?

// Done.
	
#ifdef MK_VERBOSE
    printf ("Done\n");
#endif

    return 0;
}




// Checar se a estrutura de p'agina � nula
int pEmpty (struct page_d *p)
{
    return p == NULL ? 1 : 0;
}


// Selecionar a página como livre.
void freePage (struct page_d *p)
{
    if ( (void*) p == NULL )
    {
        // #debug ?
        return;  
    }

    // Free it!
    if ( p->used == 1 && p->magic == 1234 ){ p->free = 1; }
}


// Selecionar a p�gina como n�o livre.
void notfreePage (struct page_d *p)
{
    if ( (void*) p == NULL )
    {
        // #debug ?
        return; 
    }
 
    // Not free!
    if ( p->used == 1 && p->magic == 1234 ){ p->free = 0; }
}



/*
 ***************************************** 
 * virtual_to_physical:
 * 
 */
 
unsigned long 
virtual_to_physical ( 
    unsigned long virtual_address, 
    unsigned long dir_va ) 
{

    if (dir_va == 0){
        panic ("virtual_to_physical: invalid dir va");
    }

    // Directory.
    unsigned long *dir = (unsigned long *) dir_va;

    unsigned long tmp=0;
    unsigned long address=0;
    
    unsigned int d = (unsigned int) virtual_address >> 22 & 0x3FF;
    unsigned int t = (unsigned int) virtual_address >> 12 & 0x3FF;
    unsigned int o = (unsigned int) (virtual_address & 0xFFF);



	// Temos o endere�o da pt junto com as flags.
    tmp = (unsigned long) dir[d];


    // Page table.
    unsigned long *pt = (unsigned long *) (tmp & 0xFFFFF000);


	// Encontramos o endereço base do page frame.
    tmp = (unsigned long) pt[t];

    address = (tmp & 0xFFFFF000);


    return (unsigned long) (address + o);
}


// show info.
// Mostra entradas no diretório.
// move to mminfo.c? pois eh um teste que imprime.
// credits: old linux
// This is a small routine that shows the info inside 
// the kernel's page directory.
// First of all it gets a used entry in the directory. 
// This Entry will point to another table called Page Table. 
// After that the routine checks how many used entries 
// we have in this page table. Each entry in the page table 
// is able to handle a single Page. 
// This page can be in the ram, in the rom, 
// in the video card memory or even in the disk.

// #todo
// We can create the same routine to check any page directory, 
// given its address.
//void pages_calc_mem_for_this_directory (unsigned long address)
//{}

void pages_calc_mem (void){
 
    int i=0;
    int j=0;
    int k=0;
    int free=0;

    // The kernel page directory.
    long *pg_dir = (long *) gKernelPageDirectoryAddress;
    long *pg_tbl;


    printf ("\n\n");

    //for(i=0 ; i<PAGING_PAGES ; i++)
    //    if (!mem_map[i]) free++;
    //printf("%d pages free (of %d)\n\r",free,PAGING_PAGES);


    // todas as entradas do diretorio.
    for (i=0; i<1024; i++)
    {
        // O primeiro bit da entrada.
        // O que ele significa mesmo? kkk
        if ( pg_dir[i] & 1 )    //if (1 & pg_dir[i])
        {
            pg_tbl = (long *) (0xfffff000 & pg_dir[i]);

            // ugly
            for ( j=k=0; j<1024; j++ )
            {
                if (pg_tbl[j] & 1){ k++; }
            };
            printf ("Pg-dir[%d] uses %d pages\n",i,k);
        }
    };

    refresh_screen();
}



//
// End.
//

