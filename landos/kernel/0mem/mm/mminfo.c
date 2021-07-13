/*
 * File: mminfo.c
 *
 * Informações sobre a gerência de memória.
 * Valores em variáveis e estruturas.
 * Testes para mostrar informações.
 */

#include <kernel.h>  

void mmShow_PML4Entry (int index, unsigned long pml4_va)
{

    // #fixme:
    // 9 9 9 9 12
    // Agora as tabelas possuem 512 entradas,
    // pois é isso o que dá pra ter com apenas 9 bits.


    // pd address.
    unsigned long pd_va=0;


	//#todo: filtros.


    // #todo
    debug_print("mmShow_PML4Entry: [TODO]\n");
    return;

	if (pml4_va == 0)
		return;


//
// pd
//


	if (pd_va == 0)
		return;


	unsigned long *dir = (unsigned long *) pd_va;
	
	//#todo: filtros.
	
    if (index < 0)
        return;


    unsigned long value = dir[index];

	printf (" DirVA = %x ", (unsigned long) pd_va );
	printf (" DirEntry %d = %x ", index, (unsigned long) value );
	

//
// pt
//

	//12 bit de flags     1000 0000 0000
	unsigned long pt_address = (unsigned long) (value & 0xFFFFF800);
	unsigned long *pt = (unsigned long *) pt_address;
	
	printf (" PT_Address = %x ", (unsigned long) pt_address );
	
	//primeira entrada da pt.
	printf (" PT_Entry_0 = %x \n", (unsigned long) pt[0] );	
}

/*
 ************************************
 * memoryShowMemoryInfo:
 *     Show memory info. 
 */

void memoryShowMemoryInfo (void){

    unsigned long HeapTotal  = ((kernel_heap_end - kernel_heap_start)/1024);
    unsigned long StackTotal = ((kernel_stack_start - kernel_stack_end)/1024);


    printf ("RAM Memory info:\n");
    printf ("\n");
    printf ("BaseMemory     (%d KB)\n", memorysizeBaseMemory );
    printf ("OtherMemory    (%d KB)\n", memorysizeOtherMemory );
    printf ("ExtendedMemory (%d KB)\n", memorysizeExtendedMemory );
    printf ("TotalMemory    (%d KB)\n", memorysizeTotal );
    printf ("\n");
    printf ("TotalUsed      (%d KB)\n", memorysizeUsed );
    printf ("TotalFree      (%d KB)\n", memorysizeFree );
    printf ("\n");
    
    printf ("ring0 area     (%d KB)\n", mm_used_ring0_area );
    printf ("ring3 area     (%d KB)\n", mm_used_ring3_area );
    printf ("kernel image area      (%d KB)\n", mm_used_kernelimage );
    
    printf ("backbuffer     (%d KB)\n", mm_used_backbuffer );
    printf ("paged pool     (%d KB)\n", mm_used_pagedpool );
    printf ("heap pool      (%d KB)\n", mm_used_heappool );
    printf ("extraheap1     (%d KB)\n", mm_used_extraheap1 );
    printf ("extraheap2     (%d KB)\n", mm_used_extraheap2 );
    printf ("extraheap3     (%d KB)\n", mm_used_extraheap3 );
    printf ("frame table    (%d KB)\n", mm_used_frame_table );


    // System type
    printf ("\n");
    printf ("====================================\n");
    printf ("This is a ");

    switch (g_mm_system_type){

        case stSmallSystem:
            printf ("Small System with %d KB \n\n", memorysizeTotal );
            printf("Origin:            %xH \n", SMALL_origin_pa );
            printf("Base kernel start: %xH \n", SMALL_kernel_base_pa );
            printf("User area start:   %xH \n", SMALL_user_pa );
            printf("cga memory:        %xH \n", SMALL_cga_pa );
            printf("frontbuffer:       %xH \n", SMALL_frontbuffer_pa );
            printf("backbuffer:        %xH \n", SMALL_backbuffer_pa );
            printf("paged memory pool: %xH \n", SMALL_pagedpool_pa );
            printf("heap pool:         %xH \n", SMALL_heappool_pa );
            printf("extraheap1:        %xH \n", SMALL_extraheap1_pa );
            printf("extraheap2:        %xH \n", SMALL_extraheap2_pa );
            printf("extraheap3:        %xH \n", SMALL_extraheap3_pa );
            break;

        case stMediumSystem:
            printf("Medium System with %d KB \n\n", memorysizeTotal );
            printf("Origin:            %xH \n", MEDIUM_origin_pa );
            printf("Base kernel start: %xH \n", MEDIUM_kernel_base_pa );
            printf("User area start:   %xH \n", MEDIUM_user_pa );
            printf("cga memory:        %xH \n", MEDIUM_cga_pa );
            printf("frontbuffer:       %xH \n", MEDIUM_frontbuffer_pa );
            printf("backbuffer:        %xH \n", MEDIUM_backbuffer_pa );
            printf("paged memory pool: %xH \n", MEDIUM_pagedpool_pa );
            printf("heap pool:         %xH \n", MEDIUM_heappool_pa );
            printf("extraheap1:        %xH \n", MEDIUM_extraheap1_pa );
            printf("extraheap2:        %xH \n", MEDIUM_extraheap2_pa );
            printf("extraheap3:        %xH \n", MEDIUM_extraheap3_pa );
            break;

        case stLargeSystem:
            printf("Large System with %d KB \n\n", memorysizeTotal );
            printf("Origin:            %xH \n", LARGE_origin_pa );
            printf("Base kernel start: %xH \n", LARGE_kernel_base_pa );
            printf("User area start:   %xH \n", LARGE_user_pa );
            printf("cga memory:        %xH \n", LARGE_cga_pa );
            printf("frontbuffer:       %xH \n", LARGE_frontbuffer_pa );
            printf("backbuffer:        %xH \n", LARGE_backbuffer_pa );
            printf("paged memory pool: %xH \n", LARGE_pagedpool_pa );
            printf("heap pool:         %xH \n", LARGE_heappool_pa );
            printf("extraheap1:        %xH \n", LARGE_extraheap1_pa );
            printf("extraheap2:        %xH \n", LARGE_extraheap2_pa );
            printf("extraheap3:        %xH \n", LARGE_extraheap3_pa );
            break;

        //case stNull:
        default:
            //printf("(Null) %d KB\n", memorysizeTotal );
            printf("memoryShowMemoryInfo: [FIXME] Not defined system size!\n");
            break;
    };


    // Frame table
    printf("Frame table start: %xH \n", FT.frame_table_start );

    // ...


    //#todo
    //See: gramnt/kernel/include/mm/x86mm.h


	//system zone
	//printf("systemzoneStart  = 0x%x\n", systemzoneStart);
	//printf("systemzoneEnd    = 0x%x\n", systemzoneEnd);
	//printf("systemzoneSize   = 0x%x\n", systemzoneSize);

	//window zone.
	//printf("windowzoneStart  = 0x%x\n", windowzoneStart);
	//printf("windowzoneEnd    = 0x%x\n", windowzoneEnd);
	//printf("windowzoneSize   = 0x%x\n", windowzoneSize);
	
	
    
	// #Suspenso
	// Suspendemos o uso de variáveis importadas do makefile.
	
/*	
#ifdef IMPORTED_VARIABLES	
	//=======================================
	// #Warning                            //
	// Variables imported from link.ld     //
	//=======================================
	
	// ## code rodata data bss ##
	
	extern unsigned long code_begin;
	extern unsigned long code_end;

	extern unsigned long rodata_begin;
	extern unsigned long rodata_end;
	
	extern unsigned long data_begin;
	extern unsigned long data_end;
	
	extern unsigned long bss_begin;
	extern unsigned long bss_end;
	
	printf("\n");
	printf("code_begin={%x} code_end={%x} \n", &code_begin, &code_end );
	printf("rodata_begin={%x} rodata_end={%x} \n", &rodata_begin, &rodata_end );
	printf("data_begin={%x} data_end={%x} \n", &data_begin, &data_end );
	printf("bss_begin={%x}  bss_end={%x}\n", &bss_begin, &bss_end );
	
#endif
*/



    //
    // kernel image 
    //


    //#todo
    //unsigned long imageStart = KERNEL_IMAGE_BASE;
    //unsigned long imageEnd;
    //unsigned long imageSize = 

    unsigned long imageAvailableAreaStart = KERNEL_IMAGE_BASE;
    unsigned long imageAvailableAreaEnd   = (kernel_heap_start - 8);
    unsigned long imageAvailableAreaSize_in_Bytes = (imageAvailableAreaEnd - imageAvailableAreaStart);
    unsigned long imageAvailableAreaSize_in_KB    = (imageAvailableAreaSize_in_Bytes/1024);

    printf("\n\n");
    printf("IMAGE SIZE: #todo \n");

    printf("\n\n");
    printf("IMAGE AVAILABLE AREA:  [%x...%x] Total={%d KB} \n",
        imageAvailableAreaStart, 
        imageAvailableAreaEnd, 
        imageAvailableAreaSize_in_KB );

    //
    //  heap e stack 
    //
    
    //printf("\n[Kernel Heap and Stack info:]\n");

    printf("\n\n");
    printf("HEAP:  [%x...%x] Total={%d KB} \n",
        kernel_heap_start, kernel_heap_end, HeapTotal );
    printf("AvailableHeap={%d KB}\n", (g_available_heap/1024) );

		// @todo:
		// Mostrar o tamanho da pilha..
		// #bugbug: A informações sobre a stack estão incorretas, 
		// pois essas variáveis mostram o endereço da stack na hora 
		// da inicialização. Quando o processador retorna de ring3 
		// para ring0 ele usa o endereço de pilha indicado na TSS.
		// Pois bem, é mais digno mostrar aqui o endereço da pilha, 
		// indicado no TSS.

    printf("\n\n");
    printf("STACK: [%x...%x] Total={%d KB} \n", 
        kernel_stack_start, kernel_stack_end, StackTotal );
    printf("STACK: StartPhysicalAddress={%x} \n", kernel_stack_start_pa );


	// Video info
    printf("\n\n");
    printf ("FrontbufferPA={%x} FrontbufferVA={%x} \n", 
        g_frontbuffer_pa, g_frontbuffer_va );  
    printf ("BackbufferVA={%x} \n", g_backbuffer_va );

	//...
}

void mmShowPML4EntryForAllProcesses (int entry_number){

    struct process_d  *p;
    int i=0;

    printf ("mmShowPML4EntryForAllProcesses:\n");

    if (entry_number < 0 || entry_number >= 512 )
        return;

    for ( i=0; i<111; i++)
    {
        p = (struct process_d *) processList[i];

        if ( (void *) p != NULL )
        {

            // #fixme

            // Mostra a entrada 1, que se refere ao endereço lógico 0x400000
            //if ( p->DirectoryVA != 0 )
            //{
            //    printf ("Process %d: ", i);
            //    mmShowPDE ( entry_number, (unsigned long) p->DirectoryVA );
            //}
        }
    };

    refresh_screen();
}  

// Mostra as estruturas de pagina 
// usadas para paginação no pagedpool.

void showFreepagedMemory ( int max ){

    struct page_d  *p;
    int i=0;


    if (max < 0 || max >= 512 )
        return;


    for ( i=0; i < max; i++ )
    {  
        p = (void *) pageAllocList[i]; 

		//if ( (void *) p == NULL )
		//{
		//    printf("null\n");	 
		//}

        if ( (void *) p != NULL ){
            printf ("id=%d free=%d frameno=%d ref=%d \n", 
                p->id, p->free, p->frame_number, p->ref_count );
        }
    };

    refresh_screen();
}  


/*
 ********************************************************
 * show_memory_structs:
 * 
 *     IMPORTANTE.
 *     Mostra as informações das estruturas de memória. 
 *     Essas são as estruturas usadas pelo kmalloc.
 * @todo: 
 *     Mostrar a memória usada pelos processos.
 *     Mostrar o quanto de memória o processo usa.
 *     *Importante: Esse tipo de rotina mereçe muita atenção
 * principalmente na fase inicial de construção do sistema.
 * Apresentar as informações em uma janela bem grande e 
 * chamar através do procedimento de janela do sistema é uma opção bem 
 * interessante.
 * Por enquanto apenas escrevemos provavelmente na janela como 
 * foco de entrada e o procedimento de janela do sistema efetua um 
  *refresh screen
 */

void show_memory_structs (void)
{
    struct mmblock_d  *B;
    int i = 0;


	// Title.
	printf("Memory Block Information:\n\n");
	//printf("=========================\n");

    // Mostra os heap da lista.
    while (i < MMBLOCK_COUNT_MAX) 
    {
        B = (void *) mmblockList[i];

        i++;
        if ( (void *) B != NULL )
        {
            if ( B->Used == 1 && B->Magic == 1234 )
            {
                printf ("Id={%d} Header={%x} userA={%x} Footer{%x}\n",
                    B->Id, B->Header, B->userArea, B->Footer );
            }
            //Nothing.
        }
        //Nothing.
    };


	// Aqui podemos aprentar informações sobre o heap.
	// como tamanho, espaço disponível, ponteiro, à que processo ele 
	// pertence.
	// mas estamos lidando a estrtutura de mmblock_d, que é especial e meio 
	// engessada.
	
	//More?!
}  


void testingPageAlloc (void)
{
    // #todo
}     



//
// End.
//










