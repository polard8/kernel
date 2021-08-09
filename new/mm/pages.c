





#include <kernel.h>

// These values came from BL.BIN.
// bootblock, lfb, device width, device height, bpp ...
//extern unsigned long SavedBootBlock; 
extern unsigned long SavedLFB;               // #todo: precisamos que o bl passe  endereço físico para mapearmos o lfb.
//extern unsigned long SavedX;
//extern unsigned long SavedY;
//extern unsigned long SavedBPP;
// ...




// Vamos criar uma pagetable com 512 entradas
// para mapearmos uma região da memória física.
// Em seguida instalar nas tabelas passadas via argumento.
// Os endereços virtuas das tabelas passados via parâmetro
// pertencem ao pml4 do kernel e nos permite acessar essas tabelas
// para configurarmos elas.

// #todo: This is a work in progress.
// #bugbug: è uma rotina muito ruim, se possível substituir por algo melhor.

void *CreateAndIntallPageTable (
    unsigned long pml4_va,   // page map level 4
    unsigned long pml4_index,
    unsigned long pdpt_va,   // page directory pointer table
    unsigned long pdpt_index,
    unsigned long pd_va,     // page directory 
    int pd_index,            // Install the pagetable into this entry of the page directory. 
    unsigned long region_pa )
{




    panic("CreateAndIntallPageTable: suspended");



    return NULL;

/*

    int i=0;

    // #todo
    // Vamos criar uma pagetable com 512 entradas
    // para mapearmos uma região da memória física.

    debug_print("CreateAndIntallPageTable: [TODO] NOT TESTED YET\n");


// =========================
    if ( pml4_va == 0 ){
        debug_print("CreateAndIntallPageTable: [FAIL] Invalid pml4_va\n");
        return NULL;
    }
    if ( pml4_index <0 || pml4_index >= 512 )
    {
        debug_print("CreateAndIntallPageTable: [FAIL] Invalid pml4_index\n");
        return NULL;
    }

// ============================
    if ( pdpt_va == 0 ){
        debug_print("CreateAndIntallPageTable: [FAIL] Invalid pdpt_va\n");
        return NULL;
    }
    if ( pdpt_index <0 || pdpt_index >= 512 )
    {
        debug_print("CreateAndIntallPageTable: [FAIL] Invalid pdpt_index\n");
        return NULL;
    }

// ============================
    if ( pd_va == 0 ){
        debug_print("CreateAndIntallPageTable: [FAIL] Invalid pd_va\n");
        return NULL;
    }
    if ( pd_index <0 || pd_index >= 512 )
    {
        debug_print("CreateAndIntallPageTable: [FAIL] Invalid pd_index\n");
        return NULL;
    }


// ============================

    // Não queremos mapear o início da memória física.
    if ( region_pa == 0 ){
        panic ("CreateAndIntallPageTable: [FAIL] region_pa\n");
    }


//
// Page table
//

    unsigned long ptVA = (unsigned long) get_table_pointer();  //ok
    if ( ptVA == 0 ){
        panic ("CreateAndIntallPageTable: [FAIL] ptVA\n");
    }

    // Vamos mapear uma região de memória 
    // preenchendo a nossa page table recem criada.

    // Essa rotina preenche uma pagetable, mapeando
    // a região indicada.

    mm_fill_page_table( 
        (unsigned long) pd_va,      // directory va. 
        (int) pd_index,             // directory entry.
        (unsigned long) ptVA,       // page table va.
        (unsigned long) region_pa,  // Region 2mb pa.
        (unsigned long) 7 );        // flags.


//
// Install
//

// Vamos instalar a pagetable no diretorio de páginas.
// Antes vamos pegar o endereço físico da page table.
// Pois precisamos desse endereço pra colocar no diretório de páginas.

    // Nessa conversão precisamos usar o pml4 do kernel.
//
// Installing
//


    unsigned long *PageTable                 = (unsigned long *) ptVA;
    unsigned long *PageDirectory             = (unsigned long *) pd_va;
    unsigned long *PageDirectoryPointerTable = (unsigned long *) pdpt_va;
    unsigned long *PML4                      = (unsigned long *) pml4_va;



//
// #debug
//
    //printf("\n");
    //printf (" pt va   : %x\n",PageTable);
    //printf (" pd va   : %x\n",PageDirectory);
    //printf (" pdpt va : %x\n",PageDirectoryPointerTable);
    //printf (" pml4 va : %x\n",PML4);
    //refresh_screen();
    //while(1){}


    unsigned long __ptPA = (unsigned long) virtual_to_physical ( 
                                             PageTable, 
                                             gKernelPML4Address ); 


    unsigned long __pdPA = (unsigned long) virtual_to_physical ( 
                                             PageDirectory, 
                                             gKernelPML4Address ); 
                                             

    unsigned long __pdptPA = (unsigned long) virtual_to_physical ( 
                                             PageDirectoryPointerTable, 
                                             gKernelPML4Address ); 

 

//
// #debug
//
    //printf("\n");
    //printf (" pt pa   : %x\n",__ptPA);
    //printf (" pd pa   : %x\n",__pdPA);
    //printf (" pdpt pa : %x\n",__pdptPA);
    //refresh_screen();
    //while(1){}

 
 
    if ( __ptPA == 0 ){
        panic ("CreateAndIntallPageTable: __ptPA\n");
    }

    if ( __pdPA == 0 ){
        panic ("CreateAndIntallPageTable: __pdPA\n");
    }

    if ( __pdptPA == 0 ){
        panic ("CreateAndIntallPageTable: __pdptPA\n");
    }

    //============================
    // Page Directory
    // Instalando o ponteiro para a pagetable entrada do diretório.
    PageDirectory[pd_index] = (unsigned long) __ptPA;
    PageDirectory[pd_index] = (unsigned long) PageDirectory[pd_index] | 7; 


    //============================
    // Page Directory Pointer Table
    PageDirectoryPointerTable[pdpt_index] = (unsigned long) __pdPA;
    PageDirectoryPointerTable[pdpt_index] = (unsigned long) PageDirectoryPointerTable[pdpt_index] | 7; 


    //============================
    // PML4
    PML4[pml4_index] = (unsigned long) __pdptPA;
    PML4[pml4_index] = (unsigned long) PML4[pml4_index] | 7; 

    
    // Retornando o endereço virtual da pt criada.
    return (void*) ptVA;

    //panic ("CreateAndIntallPageTable: [TODO] This is a work in progress.\n");
    // #todo retorno.
    //return NULL;
    
    */
}



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


// Wrapper
unsigned long alloc_frame(void)
{
    return (unsigned long) get_new_frame();
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

    debug_print ("get_table_pointer:\n");

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


void *CloneKernelPDPT0(void)
{
    register int i=0;
    unsigned long destAddressVA=0; 


    //destAddressVA = (unsigned long) newPage (); 
    destAddressVA = (unsigned long) get_table_pointer(); 

    if ( destAddressVA == 0 ){
        panic ("CloneKernelPML4: destAddressVA\n");
    }


    // The virtual address of the kernel page directory and
    // the virtual address of the new page directory.
    // #bugbug: What directory we are using right now? kernel?

    unsigned long *src = (unsigned long *) kernel_mm_data.pdpt0_va; //gKernelPML4Address;
    unsigned long *dst = (unsigned long *) destAddressVA;  

    // Copy

    for ( i=0; i < 512; ++i ){
        dst[i] = (unsigned long) src[i];
    };

    // Done.
    // The virtual address of the new pml4. 

    return (void *) destAddressVA;
}



void *CloneKernelPD0(void)
{
    register int i=0;
    unsigned long destAddressVA=0; 


    //destAddressVA = (unsigned long) newPage (); 
    destAddressVA = (unsigned long) get_table_pointer(); 

    if ( destAddressVA == 0 ){
        panic ("CloneKernelPML4: destAddressVA\n");
    }


    // The virtual address of the kernel page directory and
    // the virtual address of the new page directory.
    // #bugbug: What directory we are using right now? kernel?

    unsigned long *src = (unsigned long *) kernel_mm_data.pd0_va; //gKernelPML4Address;
    unsigned long *dst = (unsigned long *) destAddressVA;  

    // Copy

    for ( i=0; i < 512; ++i ){
        dst[i] = (unsigned long) src[i];
    };

    // Done.
    // The virtual address of the new pml4. 

    return (void *) destAddressVA;
}


/*
 * CloneKernelPML4:
 *
 *    Clone the kernel pml4.
 *    OUT: The virtual address of the new directory.
 */

// OUT: va
void *CloneKernelPML4(void)
{
    register int i=0;
    unsigned long destAddressVA=0; 


    //destAddressVA = (unsigned long) newPage (); 
    destAddressVA = (unsigned long) get_table_pointer(); 

    if ( destAddressVA == 0 ){
        panic ("CloneKernelPML4: destAddressVA\n");
    }


    // The virtual address of the kernel page directory and
    // the virtual address of the new page directory.
    // #bugbug: What directory we are using right now? kernel?

    unsigned long *src = (unsigned long *) gKernelPML4Address;
    unsigned long *dst = (unsigned long *) destAddressVA;  

    // Copy

    for ( i=0; i < 512; ++i ){
        dst[i] = (unsigned long) src[i];
    };

    // Done.
    // The virtual address of the new pml4. 

    return (void *) destAddressVA;
}

/*
 * clone_pml4:
 *     Clone a given page directory.
 * 
 */

// Clona um pml4 dado seu endereço.
// Queremos clonar o diretório atual,
// para que o processo filho tenha o mesmo diretório do processo pai. 

// #??
// Esse endereço virtual eh valido?
// Pertence ao diretorio que estamos usando no momento?

// #todo
// clone_pml4

void *clone_pml4 ( unsigned long pml4_va )
{
    register int i=0;
    unsigned long destAddressVA=0; 


    // #test
    // no directory in the address '0'

    if ( pml4_va == 0 )
        panic("clone_pml4: pml4_va\n");


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

    unsigned long *src = (unsigned long *) pml4_va;
    unsigned long *dst = (unsigned long *) destAddressVA;

    // Copy

    for ( i=0; i < 512; ++i ){
        dst[i] = (unsigned long) src[i]; 
    };

    // The address of the new pml4.

    return (void *) destAddressVA;
}


/*
 ***********************************************************
 * initialize_frame_table:
 *     Frame table to handle a pool of page frames.
 */

int initialize_frame_table (void)
{
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


unsigned long 
virtual_to_physical ( 
    unsigned long virtual_address, 
    unsigned long pml4_va ) 
{

    //debug_print("virtual_to_physical: [TESTING] \n");

    //panic ("virtual_to_physical: [TODO] \n");
    return (unsigned long) __virtual_to_physical (virtual_address,pml4_va);
}


// Worker
unsigned long 
__virtual_to_physical ( 
    unsigned long virtual_address, 
    unsigned long pml4_va ) 
{

    //debug_print ("__virtual_to_physical: [TESTING] \n");

    //#debug
    //printf("virtual_address = %x \n",virtual_address);
    //printf("pml4_va = %x \n",pml4_va);
    //refresh_screen();
    //while(1){}


    if ( virtual_address == 0 ){
        debug_print ("__virtual_to_physical: [?] virtual_address == 0 \n");
    }

    unsigned int a = (unsigned int) ((virtual_address >> 39) & 0x1FF);   //  9 bits de pml4
    unsigned int b = (unsigned int) ((virtual_address >> 30) & 0x1FF);   //  9 bits de pdpt
    unsigned int d = (unsigned int) ((virtual_address >> 21) & 0x1FF);   //  9 bits de page directory
    unsigned int t = (unsigned int) ((virtual_address >> 12) & 0x1FF);   //  9 bits de page table. 
    unsigned int o = (unsigned int) (virtual_address      & 0xFFF );     // 12 bits de offset

    unsigned long tmp=0;
    unsigned long address=0;


    //printf ("a=%d b=%d d=%d t=%d o=%d \n",a,b,d,t,o);
    //refresh_screen();
    //while(1){}

    //#debug
    if ( a >= 512 || b >= 512 || d >= 512 || t >= 512 || o >= 512  )
    {
        printf ("__virtual_to_physical: entry limits \n");
        refresh_screen();
        while(1){}
    }
    
    // #todo
    // Por enquanto estamos usando apenas as entradas '0'
    // de pml4 e pdpt ... mas depois vamos usar todas.
    
    // #hackhack
    if ( a != 0 ){
        printf ("__virtual_to_physical: [TODO] a != 0 \n");
        refresh_screen();
        while(1){}
        //return;
    }

    // #hackhack
    if ( b != 0 ){
        printf ("__virtual_to_physical: [TODO] b != 0 \n");
        refresh_screen();
        while(1){}
        //return;
    }

    if (pml4_va == 0){
        debug_print ("__virtual_to_physical: [?] pml4_va == 0 \n");
        panic       ("__virtual_to_physical: [FAIL] Invalid pml4_va\n");
    }

// ==============================
// pml4
    //debug_print ("virtual_to_physical2: [pml4]\n");
    unsigned long *pml4VA = (unsigned long *) pml4_va;

    //printf (">> pml4VA[a] %x\n", pml4VA[a]);
    //refresh_screen();

    // Temos o pdpt junto com suas flags.
    tmp = (unsigned long) pml4VA[a];


// ==============================
// page directory pointer table.
    //debug_print ("virtual_to_physical2: [ptpt]\n");
    unsigned long *ptpt = (unsigned long *) (tmp & 0xFFFFFFFFF000);

    //printf (">> ptpt[d] %x\n", ptpt[b]);
    //refresh_screen();

    // Temos o pd junto com suas flags.
    tmp = (unsigned long) ptpt[b];

// ==============================
// page diretory
    //debug_print ("virtual_to_physical2: [dir]\n");
    unsigned long *dir = (unsigned long *) (tmp & 0xFFFFFFFFF000);

    //printf ("dir[d] %x\n", dir[d]);
    //refresh_screen();
    
    // Temos o endereço da pt junto com as flags.
    tmp = (unsigned long) dir[d];

    // Page table.
    //debug_print ("virtual_to_physical2: [pt]\n");
    unsigned long *pt = (unsigned long *) (tmp & 0xFFFFFFFFF000);

    // Encontramos o endereço base do page frame.
    tmp = (unsigned long) pt[t];

    address = (tmp & 0xFFFFFFFFF000);

    //debug_print ("virtual_to_physical2: done\n");
    // Physical address.
    return (unsigned long) (address + o);
}



// #todo
void pages_calc_mem (void)
{
    int a=0;
    int b=0;
    int i=0;
    int j=0;
    int k=0;
    int free=0;

    unsigned long *pml4 = (unsigned long *) gKernelPML4Address;
    unsigned long *pdpt;
    unsigned long *pg_dir;
    unsigned long *pg_tbl;

    printf ("\n\n");

    //for(i=0 ; i<PAGING_PAGES ; i++)
    //    if (!mem_map[i]) free++;
    //printf("%d pages free (of %d)\n\r",free,PAGING_PAGES);


    for (a=0; a<512; a++)
    {
        if ( pml4[a] & 1 )
        {
            pdpt = (unsigned long *) (0xFFFFFFFFF000 & pml4[a]);
            for (b=0; b<512; b++)
            {
                if ( pdpt[b] & 1 )
                {
                    pg_dir = (unsigned long *) (0xFFFFFFFFF000 & pdpt[b]);
                    for (i=0; i<512; i++)
                    {
                        if ( pg_dir[i] & 1 )    //if (1 & pg_dir[i])
                        {
                            pg_tbl = (unsigned long *) (0xFFFFFFFFF000 & pg_dir[i]);

                            // ugly
                            for ( j=k=0; j<512; j++ )
                            {
                                if (pg_tbl[j] & 1){ k++; }
                            };
                            printf ("%d|%d:  dir[%d]  uses  %d  pages\n",a,b,i,k);
                        }
                    };
                }
            };
        }
    };

    refresh_screen();
}



// 64bit ?
// local
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



// #test
// Cria uma page table com 512 entradas
// para uma região de 2mb e configura uma
// determinada entrada no diretório de páginas.
int mm_fill_page_table( 
    unsigned long directory_va, 
    int           directory_entry,
    unsigned long pt_va,
    unsigned long region_2mb_pa,
    unsigned long flags )
{

    register int i=0;
    unsigned long *dir = (unsigned long *) directory_va;
    unsigned long *pt  = (unsigned long *) pt_va;
    unsigned long pa   = (unsigned long) region_2mb_pa;

    if ( directory_entry < 0 || directory_entry >= 512 ){ return -1; }

    // Fill the pagetable with 512 entries.
    for ( i=0; i<512; ++i )
    {
        pt[i] = (unsigned long) (pa | flags);
        pa    = (unsigned long) (pa + 4096);
    };
    
    // Create a directory entry in the given index.
    dir[directory_entry] = (unsigned long) &pt[0];
    dir[directory_entry] = (unsigned long) (dir[directory_entry] | flags);

// done
    return 0;
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
    memorysizeFree = 0;
    memorysizeUsed= 0;

    mm_used_ring0_area = 0;
    mm_used_ring3_area = 0; 
    mm_used_kernelimage = 0;
    mm_used_backbuffer = 0; 
    mm_used_pagedpool = 0; 
    mm_used_heappool = 0;
    mm_used_extraheap1 = 0;
    mm_used_extraheap2 = 0; 
    mm_used_extraheap3 = 0; 
    mm_used_frame_table = 0;
    
    // ============


// =========================================================

//
// pml4
//
    // 0x0009C000 = Kernel pml4


    // 9 9 9 9 12
    // Agora as tabelas possuem 512 entradas,
    // pois é isso o que dá pra ter com apenas 9 bits.

    // #todo
    // Precisamos encontra espaço na memória para kernel_pml4 e kernel_pdpt0.
    // Precisamos criar 'worker functions' para essas rotinas repetitivas.

    // See:
    // gpa.h for some physical addresses.


// =====================================
// Levels: PML4, PDPT, PD, PT
//
// PML4 - Page Map Level 4
// PDPT - Page Directory Pointer Table
// PD   - Page Directory
// PT   - Page Table

    // Isso porque endereço físico e virtual são igual abaixo de 1 mb.
    // 0x0009C000va = 0x0009C000pa

    gKernelPML4Address = KERNEL_PML4_VA;

    // level 4
    unsigned long *kernel_pml4  = (unsigned long *) KERNEL_PML4_PA;
    // level 3
    unsigned long *kernel_pdpt0 = (unsigned long *) KERNEL_PDPT_PA;
    // level 2
    unsigned long *kernel_pd0   = (unsigned long *) KERNEL_PD_PA;
    // level 1
    // a lot of page tables in the level 1.


//
// Saving the data
//

// Saving some info used by the kernel to handle 
// the memory he needs.

// See:
// x64mmm.h

    // pml4
    kernel_mm_data.pml4_va = (unsigned long) kernel_pml4;
    kernel_mm_data.pml4_pa = (unsigned long) KERNEL_PML4_PA;

    // pdpt0
    kernel_mm_data.pdpt0_va = (unsigned long) kernel_pdpt0;
    kernel_mm_data.pdpt0_pa = (unsigned long) KERNEL_PDPT_PA;

    // pd0
    kernel_mm_data.pd0_va = (unsigned long) kernel_pd0;
    kernel_mm_data.pd0_pa = (unsigned long) KERNEL_PD_PA;

    kernel_mm_data.used   = TRUE;
    kernel_mm_data.magic  = 1234; 


// Check

    if ( kernel_mm_data.pml4_va  == 0 || 
         kernel_mm_data.pml4_pa  == 0 ||
         kernel_mm_data.pdpt0_va == 0 || 
         kernel_mm_data.pdpt0_pa == 0 ||
         kernel_mm_data.pd0_va   == 0 || 
         kernel_mm_data.pd0_pa   == 0 )
    {
        debug_print ("mmSetUpPaging: [FAIL] Invalid kernel_mm_data \n");
        panic       ("mmSetUpPaging: [FAIL] Invalid kernel_mm_data \n");
    }


// =============================================================
// Regions
// =============================================================
// See:
// gpa.h

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


// =============================================================
// Page tables
// =============================================================
// See:
// gpa.h


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
    // kernel mode. (O kernel). 0x0008E000
    // user mode. 0x0008D000
    // user mode. (vga). 0x0008C000
    // user mode. (LFB). 0x0008B000
    // user mode. (buffer). backbuffer 0x0008A000
    // pagetable para o pagedpool 0x00089000
    // um endere�o f�sico para a pagetable que mapear� os buffers.



    unsigned long *pt_ring0area    = (unsigned long *) PAGETABLE_RING0AREA; 
    unsigned long *pt_ring3area    = (unsigned long *) PAGETABLE_RING3AREA;
    unsigned long *pt_kernelimage  = (unsigned long *) PAGETABLE_KERNELIMAGE; 
    unsigned long *pt_frontbuffer  = (unsigned long *) PAGETABLE_FRONTBUFFER;
    unsigned long *pt_backbuffer   = (unsigned long *) PAGETABLE_BACKBUFFER;
    unsigned long *pt_pagedpool    = (unsigned long *) PAGETABLE_PAGEDPOOL;
    unsigned long *pt_heappool     = (unsigned long *) PAGETABLE_HEAPPOOL; 
    unsigned long *pt_extraheap1   = (unsigned long *) PAGETABLE_EXTRAHEAP1;
    unsigned long *pt_extraheap2   = (unsigned long *) PAGETABLE_EXTRAHEAP2;
    unsigned long *pt_extraheap3   = (unsigned long *) PAGETABLE_EXTRAHEAP3;
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
    
    // #todo
    // Como esses são endereços físicos,
    // podemos usar nomes que indiquem que esses são endereços físicos.
    // Como por exemplo, nomes terminados em _PA.
 
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
       kernel_pdpt0[i] = (unsigned long) 0 | 2;
    };

    // Clear level 2
    for ( i=0; i < 512; i++ ){
        kernel_pd0[i] = (unsigned long) 0 | 2;
    };


//
// ============================
//

    // #bugbug
    // Estaríamos dizendo que todas as entradas do primeiro diretorio
    // esntão em ring0, e que todas as entradas do primeiro pdpt
    // também estão?
 
    // pd >> pdpt
    // Pointing the 'page directory' address 
    // at the first entry in the 'page directory pointer table'.

    kernel_pdpt0[0] = (unsigned long) &kernel_pd0[0];
    kernel_pdpt0[0] = (unsigned long) kernel_pdpt0[0] | 7; //3;

    // pdpt >> pml4
    // Pointing the 'page directory pointer table' address 
    // at the first entry in the kernel_pml4.
    kernel_pml4[0] = (unsigned long) &kernel_pdpt0[0];
    kernel_pml4[0] = (unsigned long) kernel_pml4[0] | 7; //3;

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
// Primeiros 2MB.  0 ~ 0x1FFFFF
// 0virt
// RING0AREA_VA
Entry_0:
    mm_used_ring0_area = (1024 * 1);  //1mb, pois seremos sobrepostos pela imagem do kernel.  
    // mm_used_ring0_area = (1024 * 2);  

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

    // Criamos a pagetable.
    // Criando a primeira entrada do diretório.
    // Isso mapeia os primeiros 2MB da memória RAM.
    // SMALL_origin_pa = kernel_address;

    // #test
    // Tentando usar o worker para esse trabalho repetitivo.
    mm_fill_page_table( 
        (unsigned long) &kernel_pd0[0], (int) PD_ENTRY_RING0AREA, 
        (unsigned long) &pt_ring0area[0], (unsigned long) kernel_address, 
        (unsigned long) 3 ); 


// =======================================
// Uma área em user mode. 0x00200000 ~ 0x003FFFFF
// 0x00200000vir - Começa na marca de 32mb fis.
// RING3AREA_VA
Entry_1:
    mm_used_ring3_area = (1024 * 2);  //2mb

    // user_address = 0x02000000
    // 32MB mark
    // 0x02000000pys = 0x00200000vir  ?? 
    // Essa é uma área em user mode

    // (2 MB).


    // Criamos a pagetable.
    // Criando a entrada número 1 do diretório.
    // Isso mapeia 2 MB de memória em user mode.
    // SMALL_user_pa = user_address


    // #test
    // Tentando usar o worker para esse trabalho repetitivo.
    mm_fill_page_table( 
        (unsigned long) &kernel_pd0[0], (int) PD_ENTRY_RING3AREA, 
        (unsigned long) &pt_ring3area[0], (unsigned long) user_address, 
        (unsigned long) 7 ); 


// =====================================
// A imagem do kernel.  0x30000000 ~ 0x301FFFFF
// 0x30000000virt
// KERNELIMAGE_VA
Entry_384:
    mm_used_kernelimage = (1024 * 2);  //2mb


    // kernel_base = 0x100000pys
    // (0x100000pys = 0x30000000virt).
    // Configurando a área de memória onde ficará a imagem do kernel.
    // Isso mapeia 2MB começando do primeiro mega. 
    // (kernel mode).
    // Preenchendo a tabela pt_ring0area.
    // 'kernel_base' é o endereço físico da imagem do kernel.

    // Criamos a pagetable.
    // Criamos a entrada 384 apontando para a pagetable.
    // SMALL_kernel_base_pa = kernel_base;


    // #test
    // Tentando usar o worker para esse trabalho repetitivo.
    mm_fill_page_table( 
        (unsigned long) &kernel_pd0[0], (int) PD_ENTRY_KERNELIMAGE, 
        (unsigned long) &pt_kernelimage[0], (unsigned long) kernel_base, 
        (unsigned long) 3 ); 

//===========================================
// frontbuffer - LFB  0x30200000 ~ 0x303FFFFF 
// 0x30200000virt
// FRONTBUFFER_VA
Entry_385:
    mm_used_lfb = (1024 * 2);  

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

    // Criamos uma pagetable.
    // Apontamos a pagetable para a entrada 385 do diretório.
    // lfb_address = Endereço físico do lfb.

    // #test
    // Tentando usar o worker para esse trabalho repetitivo.
    mm_fill_page_table( 
        (unsigned long) &kernel_pd0[0], (int) PD_ENTRY_FRONTBUFFER,
        (unsigned long) &pt_frontbuffer[0], (unsigned long) lfb_address, 
        (unsigned long) 7 ); 

// ===================================================
// backbuffer    0x30400000 ~ 0x305FFFFF
// 0x30400000virt
// BACKBUFFER_VA
Entry_386:
    mm_used_backbuffer = (1024 * 2);  

    // buff_address = 0x01000000pys
    // 16mb mark.
    // 0x01000000pys = 0x30400000virt

    
    // Criamos a pagetable.
    // Apontamos a pagetable para a entrada 386 do diretório.

    // #test
    // Tentando usar o worker para esse trabalho repetitivo.
    mm_fill_page_table( 
        (unsigned long) &kernel_pd0[0], (int) PD_ENTRY_BACKBUFFER, 
        (unsigned long) &pt_backbuffer[0], (unsigned long) buff_address, 
        (unsigned long) 7 ); 


//++
// ====================================================================
// #test #todo : Paged pool area. 0x30600000 ~ 0x307FFFFF
// 0x30600000
// PAGEDPOOL_VA
Entry_387:
    mm_used_pagedpool = (1024 * 2);  //2mb 

    //g_pagedpool_va = (unsigned long) XXXPAGEDPOOL_VA;  
    g_pagedpool_va = (unsigned long) PAGEDPOOL_VA; //0x30600000;  // 2mb `a mais que o backbuffer


    // #test
    // Tentando usar o worker para esse trabalho repetitivo.
    mm_fill_page_table( 
        (unsigned long) &kernel_pd0[0], (int) PD_ENTRY_PAGEDPOOL, 
        (unsigned long) &pt_pagedpool[0], (unsigned long) SMALL_pagedpool_pa, 
        (unsigned long) 7 ); 

// ====================================================================
//--


//++
// ====================================================================
// pool of heaps.
// HEAPPOOL_VA
Entry_388:
    mm_used_heappool = (1024 * 2);  

    g_heappool_va    = (unsigned long) HEAPPOOL_VA; //0x30800000;
    g_heap_count     = 0;
    g_heap_count_max = G_DEFAULT_PROCESSHEAP_COUNTMAX;
    g_heap_size      = G_DEFAULT_PROCESSHEAP_SIZE;  //#bugbug

    // >> (user mode).
    // Heaps support.
    // Preparando uma �rea de mem�ria grande o bastante para conter 
    // o heap de todos os processos.
    // ex: 
    // Podemos dar 128 KB para cada processo inicialmente.

    // 2048 KB = (2 MB).

    // #importante:
    // Os endereços físico e virtual são iguais para essa tabela.

    // #test
    // Tentando usar o worker para esse trabalho repetitivo.
    mm_fill_page_table( 
        (unsigned long) &kernel_pd0[0], (int) PD_ENTRY_HEAPPOOL, 
        (unsigned long) &pt_heappool[0], (unsigned long) SMALL_heappool_pa, 
        (unsigned long) 7 ); 

// ====================================================================
//--

//
// #important
//

    // The INitProcess uses one of these extra heaps,
    // and just a small heap from the heap pool
    // as the other ring3 process do.
    // See: x64init.c When we setup the Heap pointer.
    // InitProcess->Heap = (unsigned long) g_extraheap1_va; :)



//++
// ====================================================================
// Extra heap used by the ring 3 init process.
// See: x64init.c When we setup the Heap pointer.
// InitProcess->Heap = (unsigned long) g_extraheap1_va; :)

// 2048 KB = (2 MB).

// heap
// EXTRAHEAP1_VA
Entry_389:
    mm_used_extraheap1 = (1024 * 2); 
    g_extraheap1_va = (unsigned long) EXTRAHEAP1_VA; //0x30A00000;
    g_extraheap1_size = (1024 * 2); 
    mm_fill_page_table( 
        (unsigned long) &kernel_pd0[0], (int) PD_ENTRY_EXTRAHEAP1, 
        (unsigned long) &pt_extraheap1[0], (unsigned long) SMALL_extraheap1_pa, 
        (unsigned long) 7 ); 

// compositor heap.
// EXTRAHEAP2_VA
Entry_390:
    mm_used_extraheap2 = (1024 * 2); 
    g_extraheap2_va = (unsigned long) EXTRAHEAP2_VA; //0x30C00000;
    g_extraheap2_size = (1024 * 2);  
    mm_fill_page_table( 
      (unsigned long) &kernel_pd0[0], (int) PD_ENTRY_EXTRAHEAP2,
      (unsigned long) &pt_extraheap2[0], (unsigned long) SMALL_extraheap2_pa,
      (unsigned long) 3 );

// comsositor.
// EXTRAHEAP3_VA
Entry_391:
    mm_used_extraheap3 = (1024 * 2); 
    g_extraheap3_va = (unsigned long) EXTRAHEAP3_VA; //0x30E00000;
    g_extraheap3_size = (1024 * 2);  
    mm_fill_page_table( 
        (unsigned long) &kernel_pd0[0], (int) PD_ENTRY_EXTRAHEAP3,
        (unsigned long) &pt_extraheap3[0], (unsigned long) SMALL_extraheap3_pa,
        (unsigned long) 3 );

// ====================================================================
//--



//
// ================================================
//


    //breakpoint
    debug_print ("mmSetUpPaging: tables done\n");
    //printf ("SetUpPaging: tables done\n");


    if ( memorysizeTotal == 0 ){
        debug_print ("mmSetUpPaging: [FIXME] We need the memorysizeTotal\n");
        //while(1){}
    }
    debug_print ("mmSetUpPaging: [DEBUG] memorysizeTotal is not zero\n");
    //while(1){}


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
        debug_print ("mmSetUpPaging: [PANIC] We need at least 256 MB of RAM\n");
        while(1){}
    };



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
    memorysizeUsed = 
        (unsigned long) ( 
        mm_used_ring0_area +  
        mm_used_ring3_area +  
        mm_used_kernelimage +
        mm_used_backbuffer + 
        mm_used_pagedpool + 
        mm_used_heappool + 
        mm_used_extraheap1 + 
        mm_used_extraheap2 + 
        mm_used_extraheap3 +
        mm_used_frame_table 
        );

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





























