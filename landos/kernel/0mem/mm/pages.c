





#include <kernel.h>

// These values came from BL.BIN.
// bootblock, lfb, device width, device height, bpp ...
//extern unsigned long SavedBootBlock; 
extern unsigned long SavedLFB;               // #todo: precisamos que o bl passe  endereço físico para mapearmos o lfb.
//extern unsigned long SavedX;
//extern unsigned long SavedY;
//extern unsigned long SavedBPP;
// ...



// #todo
// Describe this thing.
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



// Checar se a estrutura de p'agina � nula
// This is very ugly
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


// #todo
unsigned long 
virtual_to_physical ( 
    unsigned long virtual_address, 
    unsigned long pml4_va ) 
{
    panic ("virtual_to_physical: [TODO] \n");
    return (unsigned long) virtual_to_physical2 (virtual_address,pml4_va);
}


//#test
unsigned long 
virtual_to_physical2 ( 
    unsigned long virtual_address, 
    unsigned long pml4_va ) 
{

    debug_print ("virtual_to_physical2: [NOT TESTED] \n");

    unsigned int a = (unsigned int) virtual_address >> 39 & 0x1FF;   //  9 bits de pml4
    unsigned int b = (unsigned int) virtual_address >> 30 & 0x1FF;   //  9 bits de pdpt
    unsigned int d = (unsigned int) virtual_address >> 21 & 0x1FF;   //  9 bits de page directory
    unsigned int t = (unsigned int) virtual_address >> 12 & 0x1FF;   //  9 bits de page table. 
    unsigned int o = (unsigned int) (virtual_address      & 0xFFF ); // 12 bits de offset

    unsigned long tmp=0;
    unsigned long address=0;


    if (pml4_va == 0){
        panic ("virtual_to_physical: [FAIL] Invalid pml4_va\n");
    }

// ==============================
// pml4
    unsigned long *pml4VA = (unsigned long *) pml4_va;

    // Temos o pdpt junto com suas flags.
    tmp = (unsigned long) pml4VA[a];

// ==============================
// page directory pointer table.
    unsigned long *ptpt = (unsigned long *) (tmp & 0xFFFFFFFFF000);

    // Temos o pd junto com suas flags.
    tmp = (unsigned long) ptpt[b];

// ==============================
// page diretory
    unsigned long *dir = (unsigned long *) (tmp & 0xFFFFFFFFF000);

    // Temos o endereço da pt junto com as flags.
    tmp = (unsigned long) dir[d];

    // Page table.
    unsigned long *pt = (unsigned long *) (tmp & 0xFFFFFFFFF000);

    // Encontramos o endereço base do page frame.
    tmp = (unsigned long) pt[t];

    address = (tmp & 0xFFFFFFFFF000);

    // Physical address.
    return (unsigned long) (address + o);
}



// #todo
void pages_calc_mem (void)
{
	//#todo
}


// 64bit ?
void load_pml4_table(void *phy_addr)
{
    asm volatile ("movq %0,%%cr3"::"r"(phy_addr));
}


// PAE and PGE
void enable_pae(void)
{
    // PAE and PGE
    asm volatile ( " movq %%cr4, %%rax; "
                   " orl $0x20,  %%eax; "
                   " movq %%rax, %%cr4  " :: );
}


void page_enable(void)
{
    // Only paging.
    asm volatile (" movq %%cr0, %%rax;      "
                  " orl $0x80000000, %%eax; "
                  " movq %%rax, %%cr0       " :: );
}



// Called by:
// init_runtime in runtime.c

int mmSetUpPaging (void)
{
    // loops
    register unsigned int i=0;

    // ============
    
    // Inicializando as variáveis de contagem de uso de memória ram.
    // Talvez ja tenhamos feito isso antes, mas não tem problema.
    
    memorysizeUsed = 0;
    mm_used_kernel_area = 0;
    mm_used_user_area = 0; 
    mm_used_backbuffer = 0; 
    mm_used_pagedpool = 0; 
    mm_used_heappool = 0;
    mm_used_extraheap1 = 0;
    mm_used_extraheap2 = 0; 
    mm_used_extraheap3 = 0; 
    mm_used_frame_table = 0;
    memorysizeFree = 0;
    memorysizeTotal= 0; 
    memorysizeUsed= 0;

    // ============


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
    SMALL_frontbuffer_pa = (unsigned long) SavedLFB;                     //frontbuffer // #todo: precisamos que o bl passe  endereço físico para mapearmos o lfb.
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
    MEDIUM_frontbuffer_pa = (unsigned long) SavedLFB; // #todo: precisamos que o bl passe  endereço físico para mapearmos o lfb.
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
    LARGE_frontbuffer_pa = (unsigned long) SavedLFB; // #todo: precisamos que o bl passe  endereço físico para mapearmos o lfb.
    LARGE_backbuffer_pa  = (unsigned long) LARGESYSTEM_BACKBUFFER;
    LARGE_pagedpool_pa   = (unsigned long) LARGESYSTEM_PAGEDPOLL_START;
    LARGE_heappool_pa    = (unsigned long) LARGESYSTEM_HEAPPOLL_START;
    LARGE_extraheap1_pa  = (unsigned long) LARGESYSTEM_EXTRAHEAP1_START;
    LARGE_extraheap2_pa  = (unsigned long) LARGESYSTEM_EXTRAHEAP2_START;
    LARGE_extraheap3_pa  = (unsigned long) LARGESYSTEM_EXTRAHEAP3_START;



    //
    // Directory.
    //

    // 0x0009C000 = Kernel page directory


    // 9 9 9 9 12
    // Agora as tabelas possuem 512 entradas,
    // pois é isso o que dá pra ter com apenas 9 bits.

    // #todo
    // Precisamos encontra espaço na memória para kernel_pml4 e kernel_pdpt.
    // Precisamos criar 'worker functions' para essas rotinas repetitivas.

    // See:
    // gpa.h for some physical addresses.


// =====================================
// PML4, PDPT, PD, PT
// PML4 - Page Map Level 4
// PDPT - Page Directory Pointer Table
// PD   - Page Directory
// PT   - Page Table

    // isso porque endereço físico e virtual são igual abaixo de 1 mb.
    gKernelPML4Address = KERNEL_PML4_VA;

    // level 4
    unsigned long *kernel_pml4 = (unsigned long *) KERNEL_PML4_PA;
    // level 3
    unsigned long *kernel_pdpt = (unsigned long *) KERNEL_PDPT_PA;
    // level 2
    unsigned long *kernel_pd0  = (unsigned long *) KERNEL_PD_PA;
    // level 1
    // a lot of page tables in the level 1.




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
	// SYSTEM MEMORY - NONPAGED POOLS 
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

    // ...
    
    
    debug_print("mmSetUpPaging:\n");
    


	//
	// SYSTEM MEMORY - PAGED POOLS 
	//


    //Criaremos por enquanto apenas uma pagetable com mem�ria paginada.
    //unsigned long *paged_page_table = (unsigned long *) ??;  //BUFFER_PAGETABLE.	


    // Message. (verbose).



    // See:
    // gpa.h

    // Início da memória RAM.
    unsigned long kernel_address = SYSTEM_ORIGIN;

    // Início da imagem do kernel. (1 MB mark)
    unsigned long kernel_base = KERNEL_BASE; 

    // User area, 0x02000000 (32 MB mark)
    // 32mb. (32*1024*1024) = 0x02000000.
    unsigned long user_address = USER_BASE;

    // frontbuffer
    // VESA LFB, foi passado pelo Boot Manager.
    unsigned long lfb_address  = (unsigned long) SavedLFB;

    // backbuffer 
    // Endereço físico provisório para o backbuffer
    // (para sistemas com pouca memória.)
    // 16mb. (16*1024*1024) = 0x01000000.
    unsigned long buff_address  = (unsigned long) 0x01000000; 


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
    
//
// ==================================================
//

    // Clear levels 4, 3 and 2.

    // Clear level 4
    for ( i=0; i < 512; i++ ){
        kernel_pml4[i] = (unsigned long) 0 | 2;
    };

    // Clear level 3
    for ( i=0; i < 512; i++ ){
       kernel_pdpt[i] = (unsigned long) 0 | 2;
    };

    // Clear level 2
    for ( i=0; i < 512; i++ ){
        kernel_pd0[i] = (unsigned long) 0 | 2;
    };


//
// ============================
//

    // pd >> pdpt
    // Pointing the 'page directory' address 
    // at the first entry in the 'page directory pointer table'.

    kernel_pdpt[0] = (unsigned long) &kernel_pd0[0];
    kernel_pdpt[0] = (unsigned long) kernel_pdpt[0] | 3;

    // pdpt >> pml4
    // Pointing the 'page directory pointer table' address 
    // at the first entry in the kernel_pml4.
    kernel_pml4[0] = (unsigned long) &kernel_pdpt[0];
    kernel_pml4[0] = (unsigned long) kernel_pml4[0] | 3;


//
// ============================
//

//
// PAGE TABLES.
//

    // Vamos criar algumas pagetables e apontá-las
    // como entradas no diretório 'kernel_pd0'.

    // Entries:
    // 0 = Primeiros 2MB da memória RAM.
    // 1 = Area em user mode que começa em 32MB da memória física.
    // 384 = Imagem do kernel que começa em 1MB da memória física.
    // 385 = frontbuffer. LFB
    // 386 = backbuffer, começa na área de 16MB da memória física.

// =======================================
// Primeiros 2MB.
// 0virt
Entry_0:

    // kernel_address = 0h;
    // (0fis = 0virt)
    // Essa é a área do kernel. Começa no início da memória RAM
    // e possui 2MB de tamanho.

    // #importante
    // Essa primeira entrada esta funcionando.
    // Conseguimos usar essa identidade 1:1,
    // tanto aqui no bl, quanto no kernel.


    // #todo: Essa variável salva a quantidade de memória
    // usada por essa área.
    // (2 MB).
    mm_used_kernel_area = (1024 * 2);  


    // Criamos a pagetable.
    // Criando a primeira entrada do diretório.
    // Isso mapeia os primeiros 2MB da memória RAM.
    // SMALL_origin_pa = kernel_address;
    for ( i=0; i < 512; i++ )
    {
        km_page_table[i] = (unsigned long) kernel_address | 3;
        kernel_address   = (unsigned long) kernel_address + 4096;
    };
    kernel_pd0[0] = (unsigned long) &km_page_table[0];
    kernel_pd0[0] = (unsigned long) kernel_pd0[0] | 3;


// =======================================
// Uma área em user mode.
// 0x00200000vir - Começa na marca de 32mb fis.
Entry_1:

    // user_address = 0x02000000
    // 32MB mark
    // 0x02000000pys = 0x00200000vir  ?? 
    // Essa é uma área em user mode

    // (2 MB).
    mm_used_user_area = (1024 * 2);

    // Criamos a pagetable.
    // Criando a entrada número 1 do diretório.
    // Isso mapeia 2 MB de memória em user mode.
    // SMALL_user_pa = user_address
    for (i=0; i < 512; i++)
    {
        um_page_table[i] = (unsigned long) user_address | 7;
        user_address     = (unsigned long) user_address + 4096;
    };
    kernel_pd0[1] = (unsigned long) &um_page_table[0];
    kernel_pd0[1] = (unsigned long) kernel_pd0[1] | 7;


// =====================================
// A imagem do kernel.
// 0x30000000virt
Entry_384:

    // kernel_base = 0x100000pys
    // (0x100000pys = 0x30000000virt).
    // Configurando a área de memória onde ficará a imagem do kernel.
    // Isso mapeia 2MB começando do primeiro mega. 
    // (kernel mode).
    // Preenchendo a tabela km_page_table.
    // 'kernel_base' é o endereço físico da imagem do kernel.

    // Criamos a pagetable.
    // Criamos a entrada 384 apontando para a pagetable.
    // SMALL_kernel_base_pa = kernel_base;

    for ( i=0; i < 512; i++ )
    {
        km2_page_table[i] = (unsigned long) kernel_base | 3;
        kernel_base       = (unsigned long) kernel_base + 4096;
    };
    kernel_pd0[384] = (unsigned long) &km2_page_table[0];
    kernel_pd0[384] = (unsigned long) kernel_pd0[384] | 3;



//===========================================
// frontbuffer - LFB
// 0x30200000virt
Entry_385:

    // lfb_address = Endereço físico do lfb.
    // 0x????pys = 0x30200000virt
    // Uma área em user mode.
    // O endereço físico foi passado pelo bootblock.
    // Mapear 2MB à partir do endereço configurado
    // como início do LFB.
    // O Boot Manager configurou VESA e obteve o endereço do LFB.
    // O Boot Manager passou para o Boot Loader esse endereço.
    // Mapeando 2MB da memória fisica começando no 
    // endereço passado pelo Boot Manager.
    // O endereço de memória virtual utilizada é 0x30200000virt.
    // lfb_address = Endereço do LFB, passado pelo Boot Manager.

    // (2 MB).
    mm_used_lfb = (1024 * 2);  

    // Criamos uma pagetable.
    // Apontamos a pagetable para a entrada 385 do diretório.
    // lfb_address = Endereço físico do lfb.
    for ( i=0; i < 512; i++ )
    {
        frontbuffer_page_table[i] = (unsigned long) lfb_address | 7;
        lfb_address               = (unsigned long) lfb_address + 4096; 
    };
    kernel_pd0[385] = (unsigned long) &frontbuffer_page_table[0];
    kernel_pd0[385] = (unsigned long) kernel_pd0[385] | 7;


// ===================================================
// backbuffer
// 0x30400000virt
Entry_386:

    // buff_address = 0x01000000pys
    // 16mb mark.
    // 0x01000000pys = 0x30400000virt

    mm_used_backbuffer = (1024 * 2);  
    
    // Criamos a pagetable.
    // Apontamos a pagetable para a entrada 386 do diretório.

    for ( i=0; i < 512; i++ )
    {
        backbuffer_page_table[i] = (unsigned long) buff_address | 7;
        buff_address             = (unsigned long) buff_address + 4096;
    };
    kernel_pd0[386] = (unsigned long) &backbuffer_page_table[0];
    kernel_pd0[386] = (unsigned long) kernel_pd0[386] | 7;



//
// ================================================
//


    //breakpoint
    debug_print ("SetUpPaging: tables done\n");
    //printf ("SetUpPaging: tables done\n");
    //refresh_screen();
    //while(1){}


// ================================================================
//
// Memory size
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
    // #todo: mm_used_lfb ??
    memorysizeUsed = (unsigned long) ( mm_used_kernel_area + 
        mm_used_user_area + 
        mm_used_backbuffer + 
        mm_used_pagedpool + 
        mm_used_heappool + 
        mm_used_extraheap1 + mm_used_extraheap2 + mm_used_extraheap3 +
        mm_used_frame_table );

    // Free.
    memorysizeFree = memorysizeTotal - memorysizeUsed;

// ==============================================


    debug_print ("SetUpPaging: [DANGER] Load cr3\n");


    // __asm__ __volatile__("cli");

// pae
    //printf ("SetUpPaging: enable_pae\n");
    //refresh_screen();

    //isso ja foi feito no bl.
    //enable_pae();

    //refresh_screen();
    //while(1){}


// Load it in cr3.
    //printf ("SetUpPaging: load_pml4_table\n");
    //refresh_screen();
    
    
    // #importante
    // O kernel já está em long mode,
    // a única coisa que precisamos fazer é
    // carregar o cr3, mas acho que agora usaremos
    // endereços de 64bit?
    
    load_pml4_table( &kernel_pml4[0] );



    // ==============================================
    //printf ("SetUpPaging: cpuSetMSR\n");
    //refresh_screen();
    
    // #todo
    // long mode exige uma configuração usando msr.
    //int msrStatus = FALSE;
    //msrStatus = cpuHasMSR();
    //in: MSR, LO, HI
    //cpuSetMSR( 0xC0000080, 0x100, 0 );

    //refresh_screen();
    //while(1){}



//done:
    // x86_SetCR3 ( (unsigned long) &kernel_pml4[0] );
    debug_print("mmSetUpPaging: done\n");
    return 0;
}





























