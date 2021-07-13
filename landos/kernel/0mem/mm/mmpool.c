

#include <kernel.h>   


/*
 ***********************************************
 * page:
 *     Cria uma estrutura de página.
 *     Procura um slot vazio para registrar ela.
 *     Inicializa a estrutura.
 *     Retorna o ponteiro da estrutura criada.
 */

// OUT:
// Retorna o ponteiro de estrutura.

void *page (void){

    struct page_d *New;

    int __slot = 0;


    //debug_print ("page:\n");

//
// Vamos procurar um slot vazio.
// 

    for ( __slot=0; __slot < PAGE_COUNT_MAX; __slot++ )
    {
        New = (void *) pageAllocList[__slot];

        if ( New == NULL )
        {
            New = (void *) kmalloc ( sizeof( struct page_d ) );

            // ?? panic ??
            if ( New == NULL )
            {
                debug_print ("mmpool-page:\n");
                printf      ("mmpool-page:\n");

                // #todo: free() ??
                goto fail;
            }

            New->id = __slot;
            New->used  = TRUE;
            New->magic = 1234;

            New->free = 0;        // Not free!
            New->next = NULL;


			//#bugbug ... isso tá errado.
			//endereço físico do inicio do frame.
			//New->address = (unsigned long) Address;
			//...

            pageAllocList[__slot] = ( unsigned long ) New; 

            //debug_print ("page: ok\n");

            return (void *) New;
        };
    };

    // Overflow.
    //#debug ??
fail:
    // Message?

    //debug_print ("page: fail\n");

    return NULL; 
}


/*
 ***************************************************
 * newPage:
 * 
 *     Aloca uma página e retorna seu endereço virtual inicial. 
 * 
 *     Isso é feito com base no id do pageframe e no endereço virtual 
 * inicial do pool de pageframes.
 * 
 * Obs: 
 * Alocaremos uma página de memória virtual e retornaremos o ponteiro 
 * para o início da página. Para isso usaremos o alocador de frames 
 * de memória física.
 */

// OUT:
// Retorna o endereço virtual da página alocada.

// #todo
// #fixme

void *newPage (void){

    struct page_d *New;

	// Esse é o endereço virtual do início do pool de pageframes.
	// Isso significa que num pool temos vários pageframes.

    unsigned long base = (unsigned long) g_pagedpool_va;

    unsigned long va=0;
    unsigned long pa=0;


    debug_print ("newPage:\n");


    if ( base == 0 ){
        debug_print ("newPage: [FAIL] base\n");
        return NULL;
    }


	// Cria e registra uma estrutura de página.

    New = (void *) page();

    if ( New == NULL ){
        debug_print ("mmpool-newPage: New\n");
        //printf ("mmpool-newPage: New\n");
        goto fail;
    }else{
        if ( New->used == TRUE && New->magic == 1234 )
        {
            // Pega o id 
            // Checa o limite de slots.

            //if ( New->id <= 0 ){
            //    debug_print ("newPage: New->id <= 0\n");
            //}
            
            //if ( New->id > 0 && New->id < PAGE_COUNT_MAX )
            if ( New->id >= 0 && New->id < PAGE_COUNT_MAX )
            {
                // trava ou não??
                New->locked = 0;

                // contador de referências.
                New->ref_count = 1;

                //#importante
                //precisamos pegar o endereço físico e dividir pelo tamanho da página.

                // #debug  #bugbug: Wrong value for 'base'.
                //printf ("newPage: base=%x id=%d \n",base,New->id);
                //refresh_screen();
                //while(1){}
                
                // #debug
                //if ( New->id > 10 ){
                //    printf ("newPage: New->id > 10\n");
                //    refresh_screen();
                //    while(1){}
                //}

                // Pegando o endereço virtual.

                va = (unsigned long) ( base + (New->id * 4096) );

                // #todo
                // #fixme
                // Use pml4 address

                // Pegando o endereço físico.
                pa = (unsigned long) virtual_to_physical ( va, gKernelPML4Address ); 

                //
                // Calculando o número do pageframe.
                //

                // #todo
                // Salvar o endereço físico ??
                
                // #bugbug 
                // ?? Isso tá certo ??
                
                // Se o resto da divisão do endereço físico, pelo 
                // tamanho de uma página for diferente de zero, então 
                // o endereço físico vai sero endereço físico menos 
                // esse resto.
                
                if ( ( pa % PAGE_SIZE ) != 0 )
                {
                    pa = pa - ( pa % PAGE_SIZE);
                }

                // Temos um id de frame com base no endereço
                // modificado.
                
                New->frame_number = (pa / PAGE_SIZE);

                // #bugbug
                // FIXME.
                // Isso está errado. 
                // Pois a heap onde pegamos os frames não começa
                // em 0.
                
                // Se o endereço físico for 0, o id do frame é 0.
                if ( pa == 0 )
                {
                    //New->frame_number = 0;
                    New->frame_number = -1;

                    debug_print ("newPage: [ERROR] pa == 0\n");
                          panic ("newPage: FIXME, frame number\n");
                }

                // #importante:
                // Retorna o endereço virtual.
                // A base, mas o deslocamento dado em páginas.

                //debug_print ("newPage: ok\n");

                return (void *) ( base + (New->id * 4096) );
             }
        };
    };

fail:
    debug_print ("newPage: fail\n");
    return NULL;
}



// Allocate single page.
void *mm_alloc_single_page (void)
{
    //return (void *) allocPages (1);
    return (void *) newPage();
}

// Allocate n contiguous pages.
void *mm_alloc_contig_pages (size_t size)
{

    debug_print("mm_alloc_contig_pages: [TODO] [FIXME]\n");

    if (size<=0)
       panic("mm_alloc_contig_pages: [FIXME] invalid size");
      
    //#todo
    //return (void *) allocPages(size);
    return NULL; 
}


/*
 ***************************************************************
 * firstSlotForAList:
 *     Retorna o primeiro índice de uma sequência de slots livres 
 * em pageAllocList[].
 */

int firstSlotForAList ( int size ){

    int Index = 0;
    int Base = 0;
    int Count = 0;
    void *slot;

tryAgain:

    for ( Index=Base; Index < 1024; Index++ )
    {
        slot = (void *) pageAllocList[Index];

        if ( (void *) slot != NULL )
        {
            Base = (Base + Count);
            Base++;
            Count = 0;
            goto tryAgain;
        }

        Count++; 

        if (Count >= size){ return (int) Base; }
    };

    // Fail: NO empty slot.
    return (int) -1;
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
 * #bugbug: 
 * Se estamos lidando com o endereço base vitual, então estamos 
 * lidando com páginas pre alocadas e não pageframes.
 */
 
// #bugbug
// Estamos alocando memória compartilhada?
// então seria sh_allocPages() 

void *allocPages (int size){

    // Esse é o endereço virtual do início do pool de pageframes.
    unsigned long base = (unsigned long) g_pagedpool_va;

    int __slot=0;

	//página inicial da lista
    struct page_d *Ret;   

    struct page_d *Conductor;
    struct page_d *p;

    unsigned long va=0;
    unsigned long pa=0;
    int Count=0;
    int __first_free_slot = -1;


    debug_print ("allocPages: [TESTING]\n");

	//
	// Checando limites.
	//

//#ifdef PS_VERBOSE
    //printf ("allocPages: Initializing ...\n");
//#endif


	//problemas com o size.
    if (size <= 0)
    {
		//if debug
        printf ("allocPages: size 0\n");
        return NULL;
    }

    // Se é pra alocar apenas uma página.
    if (size == 1){
        return (void *) newPage();
    }

    // Se o size for maior que o limite.
    if ( size > PAGE_COUNT_MAX )
    {
		//if debug
        printf ("allocPages: [FAIL] size limits\n");
        goto fail;
    }


    // Isso encontra slots o suficiente para alocarmos 
    // tudo o que queremos.
    // PANIC !!
    // A memória para a locação acabou.
    // #todo:
    // Liberar páginas mandando para o disco conforme
    // critéria à definir ainda,


    __first_free_slot = (int) firstSlotForAList(size);

    //if ( __first_free_slot < 0 )
    if ( __first_free_slot == -1 )
    {
        debug_print ("allocPages: [FAIL] No more free slots\n");
        panic       ("allocPages: [FAIL] No more free slots\n");
    }


    // Procurar slot vazio.
    // Começamos a contar do frame logo após o condutor.

    for ( 
        __slot = __first_free_slot; 
        __slot < (__first_free_slot+size+1);
        __slot++ )
    {

        p = (void *) pageAllocList[__slot];

        // Slot livre
        if ( p == NULL )
        {
            // #bugbug
            // Isso pode esgotar o heap do kernel

            p = (void *) kmalloc ( sizeof( struct page_d ) );

            if ( p == NULL ){
                printf ("allocPages: fail 2\n");
                goto fail;
            }

			//printf("#");
            
            p->id = __slot;
            p->used  = TRUE;
            p->magic = 1234;
            p->free = FALSE;
            p->locked = FALSE;

            // Contador de referências
            p->ref_count = 1;

			// #fixme
			// Precisamos usar pml4

            // Pegando o endereço virtual.
            va = (unsigned long) ( base + (p->id * 4096) ); 
            pa = (unsigned long) virtual_to_physical ( va, gKernelPML4Address ); 

            if ( ( pa % PAGE_SIZE ) != 0 ) 
            {
                pa = pa - ( pa % PAGE_SIZE);
            }

            p->frame_number = (pa / PAGE_SIZE);

            if ( pa == 0 ){
                p->frame_number = 0;
            }

			//---

			pageAllocList[__slot] = ( unsigned long ) p; 

			Conductor->next = (void *) p;
			Conductor = (void *) Conductor->next;


			// #obs:
			// Vamos precisr da estrutura da primeira página alocada.
			// #Importante:
			// Retornaremos o endereço virtual inicial do primeiro 
			// pageframe da lista. Ou seja, da primeira página.

            Count++;
            if ( Count >= size )
            {
                Ret = (void *) pageAllocList[__first_free_slot];
                
                return (void *) ( base + (Ret->id * 4096) );
            }
            //fail
        };
    };

fail:
    debug_print ("mmpool-allocPages: fail \n");
    printf      ("mmpool-allocPages: fail \n");
    return NULL;
}

/*
 * initializeFramesAlloc:
 *     Inicializa o framepool. 
 */

void initializeFramesAlloc (void)
{
    struct page_d  *p;
    int __slot = 0;


    debug_print("initializeFramesAlloc: \n");

	// Inicializando a lista de pages.

    for ( __slot=0; __slot < PAGE_COUNT_MAX; __slot++ )
    {
        pageAllocList[__slot] = (unsigned long) 0;
    };


	//
	// Criando o primeiro para testes.
	//

    // #bugbug
    // Talvez seja desnecessário criar essa entrada.

    p = (void *) kmalloc ( sizeof( struct page_d ) );

    if ( p == NULL ){
        debug_print ("initializeFramesAlloc:\n");
        panic ("initializeFramesAlloc:\n");
    }else{
        p->id = 0;
        p->used = 1;
        p->magic = 1234;
        p->free = 1;  //free
        p->next = NULL; 
        // ...

        pageAllocList[0] = ( unsigned long ) p; 
    };
}













