
// mmpool.c

#include <kernel.h>   

static void *__pageObject(void);
static int __firstSlotForAList(int size);

/*
 * page:
 * Cria uma estrutura de página.
 * Procura um slot vazio para registrar ela.
 * Inicializa a estrutura.
 * Retorna o ponteiro da estrutura criada.
 */

// OUT:
// Retorna o ponteiro de estrutura.

static void *__pageObject(void)
{
    struct page_d *New;
    int __slot = 0;


    //debug_print ("page:\n");

// Vamos procurar um slot vazio.

    for ( __slot=0; 
          __slot < PAGE_COUNT_MAX; 
          __slot++ )
    {
        // #
        // Essa lista precisa ser inicializada com 0
        // antes de usarmos ela aqui nessa rotina.

        New = (void *) pageAllocList[__slot];

        if ( New == NULL )
        {
            New = (void *) kmalloc ( sizeof( struct page_d ) );

            // ?? panic ??
            if ( New == NULL )
            {
                debug_print ("__pageObject:\n");
                printf      ("__pageObject:\n");

                // #todo: free() ??
                goto fail;
            }

            New->id = __slot;  // Índice dentro da lista.
            
            New->used  = TRUE;
            New->magic = 1234;

            New->free = 0;        // Not free!
            New->next = NULL;

            // #bugbug ... isso tá errado.
            // endereço físico do inicio do frame.
            // New->address = (unsigned long) Address;
            // ...

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
 * newPage:
 * Aloca uma página em memoria compartilhada de ring3 
 * e retorna seu endereço virtual inicial. 
 * Isso é feito com base no id do pageframe e no endereço virtual 
 * inicial do pool de pageframes.
 * Obs: 
 * Alocaremos uma página de memória virtual e retornaremos o ponteiro 
 * para o início da página. Para isso usaremos o alocador de frames 
 * de memória física.
 */

// OUT:
// Retorna o endereço virtual da página alocada.
// #todo
// #fixme

void *newPage (void)
{
    struct page_d *New;

// Esse é o endereço virtual do início do pool de pageframes.
// Isso significa que num pool temos vários pageframes.

    unsigned long base = (unsigned long) g_pagedpool_va;

    unsigned long va=0;
    unsigned long pa=0;
    
    int PageSize = PAGE_SIZE;  //4096;

    //debug_print ("newPage:\n");

    if ( base == 0 )
    {
        debug_print ("newPage: base\n");
        panic       ("newPage: base\n");
        //return NULL;
    }

// Cria e registra uma estrutura de página.
// Objeto página.

    New = (void *) __pageObject();

    if ( New == NULL )
    {
        debug_print ("newPage: New\n");
        panic       ("newPage: New\n");
        //goto fail;
    }

    if ( New->used != TRUE )
    {
        debug_print ("newPage: New used\n");
        panic       ("newPage: New used \n");
    }

    if ( New->magic != 1234 )
    {
        debug_print ("newPage: New magic\n");
        panic       ("newPage: New magic \n");
    }


// Pega o id 
// Checa o limite de slots.


    if (New->id < 0)
        panic ("newPage: out of range\n");

    if (New->id >= PAGE_COUNT_MAX)
        panic ("newPage: out of range\n");

// trava ou não?
    New->locked = 0;

// contador de referências.
// Quantos processos estão usando essa página compartilhada.
    New->ref_count = 1;

// #importante
// precisamos pegar o endereço físico e dividir pelo tamanho da página.
// #debug  #bugbug: Wrong value for 'base'.
    //printf ("newPage: base=%x id=%d \n",base,New->id);
    //refresh_screen();
    //while(1){}

//
//  VA
//

// Pegando o endereço virtual.
// Temos uma base, que é um endereço virtual,
// um índice e um tamanho de página.
    va = (unsigned long) ( base + (New->id * PageSize) );

    if (va==0){
        panic ("newPage: va==0\n");
    }

//
//  PA
//

// Pegando o endereço físico.
// Convertendo de virtual para físico,
// usando o pml4 do kernel.

    pa = 
        (unsigned long) virtual_to_physical ( va, gKernelPML4Address );

// O pool não começa no endereço físico '0'.
// Então nenhum dos frames pode começar em '0'.
    if (pa==0){
        panic ("newPage: pa==0\n");
    }

// #test
// Calculando o número do frame com base
// no endereço físico.

    unsigned long alignedPA = (unsigned long) pa;
    unsigned long remainder = (unsigned long)( pa % PAGE_SIZE );

// Se temos um resto, ajustamos o endereço físico
// par apontar par ao início do frame.
    if (remainder != 0){
        alignedPA = (unsigned long) ( pa - remainder );
    }

// Com base no endereço do início do frame,
// calculamos o indic do frame.
// Os frames são contados à partir do início 
// da memória física.                 
    New->frame_number = (unsigned int) (alignedPA / PAGE_SIZE);

// Return the virtual address.
    //return (void *) va;
    return (void *) ( base + (New->id * PageSize) );

fail:
    debug_print ("newPage: fail\n");
    panic       ("newPage: fail\n");
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

    panic("mm_alloc_contig_pages: [TODO] its a work in progress\n");

    //if (size<=0)
       //panic("mm_alloc_contig_pages: [FIXME] invalid size");
      
    //#todo
    //return (void *) allocPages(size);
    return NULL; 
}


/*
 * __firstSlotForAList:
 * Retorna o primeiro índice de uma sequência de slots livres 
 * em pageAllocList[].
 */

// IN:
// A quantidade de slots livres consecutivos que precisamos.
// Nosso limite é 1024, que é o tamanho do pool.
// OUT:
// Retorna o índice do primeiro slot 
// de uma sequencia concatenada de slots livres.
// Ou retorn '-1' no caso de erro.
// #todo: Explain it better.

static int __firstSlotForAList(int size)
{
    register int i=0;

// Nosso limite é 512, que é o tamanho do pool.
// pois o pool tem 2mb,que dá 512 páginas de 4kb.
    int Max = PAGE_COUNT_MAX;//512;  

    int Base = 0;
    int Count = 0;
    void *slot;

tryAgain:

    for ( i=Base; i < Max; i++ )
    {
        slot = (void *) pageAllocList[i];

        // tenta novamente, começando numa base diferente.
        if ( (void *) slot != NULL )
        {
            Base = (Base + Count);
            Base++;
            Count = 0;
            
            //#bugbug: Podemos fica aqui pra sempre?
            goto tryAgain;
        }

        Count++; 

        if (Count >= size)
        {
            // OUT: 
            // Retorna o índice do primeiro slot 
            // de uma sequencia concatenada de slots livres.
            return (int) Base; 
        }
    };

// Fail: No empty slot.
    return (int) -1;
}



/*
 * allocPages:
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

// Essa rotina aloca uma quantidade de páginas
// de um pool de páginas.
// São compartilhadas.
// #todo: Explicar o ring e as permissões.

// #tomos que ter um marcador de páginas disponíveis para
// livres para alocação.
// Nosso limite é 512 páginas, pois so temos 2mb de pool.

void *allocPages (int size)
{

// Esse é o endereço virtual do início do pool de pageframes.
// #bugbug: O paged pool so tem 2mb, veja pages.c
// então só podemos mapear 2*1024*1024/4096 páginas.

    unsigned long base = (unsigned long) g_pagedpool_va;

    int __slot=0;

//página inicial da lista
    struct page_d *Ret;   

    struct page_d *pageConductor;
    struct page_d *p;

    unsigned long va=0;
    unsigned long pa=0;
    int Count=0;
    int __first_free_slot = -1;


    debug_print ("allocPages:\n");

//
// Checando limites.
//

//#ifdef PS_VERBOSE
    //printf ("allocPages: Initializing ...\n");
//#endif

//problemas com o size.
    if (size <= 0)
    {
        //size = 1;
        //if debug
        panic("allocPages: size 0\n");
        //return NULL;
    }

// Se é pra alocar apenas uma página.
    if (size == 1){
        return (void *) newPage();
    }

// Se o size for maior que o limite.
    if ( size >= PAGE_COUNT_MAX ){
        panic ("allocPages: [FAIL] size limits\n");
    }

// Isso encontra slots o suficiente para alocarmos 
// tudo o que queremos.
// PANIC !!
// A memória para a locação acabou.
// #todo:
// Liberar páginas mandando para o disco conforme
// critéria à definir ainda,

    __first_free_slot = (int) __firstSlotForAList(size);

    //if ( __first_free_slot < 0 )
    if ( __first_free_slot == -1 )
    {
        debug_print ("allocPages: No more free slots\n");
        panic       ("allocPages: No more free slots\n");
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

            if ( p == NULL )
            {
                //printf ("allocPages: fail 2\n");
                panic ("allocPages: fail 2\n");
                //goto fail;
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

            pageConductor->next = (void *) p;
            pageConductor = (void *) pageConductor->next;

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
    debug_print ("allocPages: fail\n");
    //printf      ("allocPages: fail\n");
    panic       ("allocPages: fail\n");
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

    debug_print("initializeFramesAlloc:\n");

// Inicializando a lista de pages.
// 512 pages

    for ( __slot=0; 
          __slot < PAGE_COUNT_MAX; 
          __slot++ )
    {
        pageAllocList[__slot] = (unsigned long) 0;
    };

//
// Criando o primeiro para testes.
//

// #bugbug
// Talvez seja desnecessário criar essa entrada.

    p = (void *) kmalloc ( sizeof( struct page_d ) );

    if (p == NULL)
    {
        debug_print ("initializeFramesAlloc:\n");
        panic       ("initializeFramesAlloc:\n");
    }

    p->id = 0;

    p->used = TRUE;
    p->magic = 1234;

    p->free = TRUE;  //free
    p->next = NULL; 
    // ...

    pageAllocList[0] = ( unsigned long ) p; 
}


