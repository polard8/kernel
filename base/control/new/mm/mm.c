
// mm.c
// + Initialize the memory support.
//   The kernel heap and the kernel stack.
// + The implementation of the main kernel allocator.
// + Initialize the physical memory manager.
// + Initialize the paging support.


#include <kernel.h>

// --------------------------------
struct kernel_heap_d 
{
    int initialized;
// va
    unsigned long start;
    unsigned long end;
};

// Global.
struct kernel_heap_d KernelHeap;
// --------------------------------

// --------------------------------
struct kernel_stack_d 
{
    int initialized;
// va
    unsigned long start;
    unsigned long end;
};

// Global.
struct kernel_stack_d KernelStack;
// --------------------------------

// --------------------------------
/*
 * mmblockCount:
 *     mm block support.
 *     Conta os blocos de memória dentro de um heap.
 *     dentro do heap usado pelo kernel eu acho ?? 
 */
unsigned long mmblockCount=0;

unsigned long mmblockList[MMBLOCK_COUNT_MAX];  

//
// Memory size support.
//

//base     = base memory retornada pelo cmos
//other    = (1MB - base). (Shadow memory = 384 KB)
//extended = retornada pelo cmos.
//total    = base + other + extended.
// alias
unsigned long memorysizeBaseMemoryViaCMOS=0;

unsigned long memorysizeBaseMemory=0;
unsigned long memorysizeOtherMemory=0;
unsigned long memorysizeExtendedMemory=0;
unsigned long memorysizeTotal=0;

unsigned long memorysizeInstalledPhysicalMemory=0;
unsigned long memorysizeTotalPhysicalMemory=0;
unsigned long memorysizeAvailablePhysicalMemory=0;
// Used
unsigned long memorysizeUsed=0;
// Free
unsigned long memorysizeFree=0;

//========================================================
// Used memory:
// Estamos medindo o uso de memória física.
// Lembrando que a mesma região de memória física
// pode ser mapeada mais de uma vez.
// #todo #bugbug
// Precisamos checar corretamente qual é o endereço físico
// de cada uma dessas regiões e suas sobreposições.
// size=2MB
// see: mminit.c
unsigned long mm_used_ring0_area=0;
unsigned long mm_used_ring3_area=0;
unsigned long mm_used_kernelimage=0;
unsigned long mm_used_backbuffer=0;
unsigned long mm_used_pagedpool=0;
unsigned long mm_used_heappool=0;
unsigned long mm_used_extraheap1=0;
unsigned long mm_used_extraheap2=0;
unsigned long mm_used_extraheap3=0;
unsigned long mm_used_frame_table=0;
// start = ?? size = 2MB
unsigned long mm_used_lfb=0; 


// Heap support.
// #todo: 
// Precisamos melhorar esses nomes, 
// pois nada neles indica que estamos lidando com heap.

// Último heap pointer válido.
static unsigned long heap_pointer_last_valid=0;
// Último tamanho alocado.
static unsigned long last_size=0;
// Endereço da última estrutura alocada.
static unsigned long mm_prev_pointer=0;


// ----------------------------

static int __init_heap(void);
static int __init_stack(void);

// ----------------------------

/*
unsigned long slab_2mb_extraheap2(void)
{
    if(g_extraheap2_initialized != TRUE)
        panic("slab_2mb_extraheap2: not initialized\n");

    return (unsigned long) g_extraheap2_va;
}
*/

/*
unsigned long slab_2mb_extraheap3(void)
{
    if(g_extraheap3_initialized != TRUE)
        panic("slab_2mb_extraheap3: not initialized\n");

    return (unsigned long) g_extraheap3_va;
}
*/


/*
 * __init_heap:
 *     Iniciar a gerência de Heap do kernel. 
 * Essa rotina controi a mão o heap usado pelo processo kernel.
 *     +Ela é chamada apenas uma vez.
 *     +Ela deve ser chamada entes de qualquer outra operação 
 * envolvendo o heap do processo kernel.
 * @todo: Rotinas de automação da criação de heaps para processos.
 */

static int __init_heap (void)
{
    int i=0;

    // #bugbug
    // não usar printf
    // printf ainda não funciona nesse momento.


    KernelHeap.initialized = FALSE;

//
// Globals
//

// start and end.
    kernel_heap_start = (unsigned long) KERNEL_HEAP_START;
    kernel_heap_end   = (unsigned long) KERNEL_HEAP_END;

    KernelHeap.start = (unsigned long) kernel_heap_start;
    KernelHeap.end   = (unsigned long) kernel_heap_end;


// Heap Pointer, Available heap and Counter.
    g_heap_pointer   = (unsigned long) kernel_heap_start; 
    g_available_heap = (unsigned long) (kernel_heap_end - kernel_heap_start);  
    heapCount = 0; 

// #importante
// Último heap pointer válido. 
    heap_pointer_last_valid = (unsigned long) g_heap_pointer;
    last_size = 0;

// Check Heap Pointer.
    if ( g_heap_pointer == 0 ){
        debug_print ("__init_heap: [FAIL] g_heap_pointer\n");
        goto fail;
    }

// Check Heap Pointer overflow.
    if ( g_heap_pointer > kernel_heap_end ){
        debug_print ("__init_heap: [FAIL] Heap Pointer Overflow\n");
        goto fail;
    }

// Heap Start
    if ( kernel_heap_start == 0 ){
        debug_print("__init_heap: [FAIL] HeapStart\n");
        goto fail;
    }

// Heap End
    if ( kernel_heap_end == 0 ){
        debug_print("__init_heap: [FAIL] HeapEnd\n");
        goto fail;
    }

// Check available heap.
// #todo: Tentar crescer o heap.
    if ( g_available_heap == 0 ){
        debug_print ("__init_heap: [FAIL] g_available_heap\n");
        goto fail;
    }

// Heap list: 
// Inicializa a lista de heaps.

    while ( i < HEAP_COUNT_MAX ){
        heapList[i] = (unsigned long) 0;
        i++;
    };

    //KernelHeap = (void*) x??;

    //More?!

    KernelHeap.initialized = TRUE;

    return 0;


// Falha ao iniciar o heap do kernel.
// ====================================

fail:

    KernelHeap.initialized = FALSE;

    debug_print ("__init_heap: Fail\n");

    //refresh_screen();

    return (int) 1;
}


/*
 * __init_stack:
 *     Iniciar a gerência de Stack do kernel. 
 *     #todo: Usar stackInit(). 
 */

static int __init_stack (void)
{

    KernelStack.initialized = FALSE;

// Globals

    kernel_stack_end   = (unsigned long) KERNEL_STACK_END; 
    kernel_stack_start = (unsigned long) KERNEL_STACK_START; 

    KernelStack.end   = (unsigned long) kernel_stack_end;
    KernelStack.start = (unsigned long) kernel_stack_start;

// End
    if ( kernel_stack_end == 0 ){
        debug_print ("__init_stack: [FAIL] kernel_stack_end\n");
        goto fail;
    }

// Start
    if ( kernel_stack_start == 0 ){
        debug_print ("__init_stack: [FAIL] kernel_stack_start\n");
        goto fail;
    }

    KernelStack.initialized = TRUE;

    return 0;

fail:

    KernelStack.initialized = FALSE;

    //refresh_screen();
    
    return (int) 1;
    //return (int) -1;
}


int kernel_gc (void)
{
    return -1;
}


struct heap_d *memory_create_new_head ( 
    unsigned long start_va, 
    unsigned long size )
{
     return NULL;  //#todo
}


void memory_destroy_heap (struct heap_d *heap)
{
    // #todo
}


// mmInit:
// Inicializa o memory manager.
// Called by __init_runtime() in runtime.c
// Init Memory Manager for x64:
// Heap, Stack, Pages, mmblocks, memory sizes, memory zones ...

int mmInit(void)
{
// + Initialize the memory support.
//   The kernel heap and the kernel stack.
// + The implementation of the main kernel allocator.
// + Initialize the physical memory manager.
// + Initialize the paging support.

    int Status=0;
    register int i=0;

    debug_print("mmInit: [TODO] [FIXME]\n");

// #todo: 
// Inicializar algumas variáveis globais.
// Chamar os construtores para inicializar o básico.
// #todo: 
// Clear BSS.
// Criar mmClearBSS()

// heap and stack
    Status = (int) __init_heap();
    if (Status != 0){
        debug_print("mmInit: [FAIL] Heap\n");
        goto fail;
    }
    Status = (int) __init_stack();
    if (Status != 0){
        debug_print ("mmInit: [FAIL] Stack\n");
        goto fail;
    }

// Initialize the list of pointer.
    while (i<MMBLOCK_COUNT_MAX){
        mmblockList[i] = (unsigned long) 0;
        i++;
    };

// Primeiro Bloco.
    // current_mmblock = (void *) NULL;

// #importante:
// Inicializando o índice la lista de ponteiros 
// para estruturas de alocação.

    mmblockCount = 0;

    // ...

//
// MEMORY SIZES
//

// Get memory sizes via RTC. (KB)
// base, other, extended.
// RTC só consegue perceber 64MB de memória.
    memorysizeBaseMemoryViaCMOS = (unsigned long) rtcGetBaseMemory();
    memorysizeBaseMemory = 
        (unsigned long) memorysizeBaseMemoryViaCMOS;
    memorysizeOtherMemory = 
        (unsigned long) (1024 - memorysizeBaseMemory);

// #todo
// New we have a new value from boot.
// We're gonna use this new value instead the one from cmos.

    unsigned long __total_memory_in_kb = (blSavedLastValidAddress/0x400);

// extended memory from cmos.
    //memorysizeExtendedMemory = (unsigned long) rtcGetExtendedMemory(); 
    memorysizeExtendedMemory =  
        (unsigned long) ( 
        __total_memory_in_kb - 
        memorysizeBaseMemory - 
        memorysizeOtherMemory 
        );

// Size in KB.
    memorysizeTotal = 
        (unsigned long) ( 
        memorysizeBaseMemory + 
        memorysizeOtherMemory + 
        memorysizeExtendedMemory 
        );

// #IMPORTANTE 
// Determinar o tipo de sistema de memória.
// small   pelo menos 32mb
// medium  pelo menos 64mb
// large   pelo menos 128mb


// 0MB
// #atenção 
// Nesse caso devemos prosseguir e testar as outras opções.
    if (memorysizeTotal >= 0){
        g_mm_system_type = stNull;
        debug_print ("mmInit: stNull\n");
    }

// Small. (32MB).
    if (memorysizeTotal >= SMALLSYSTEM_SIZE_KB){
        g_mm_system_type = stSmallSystem;
        debug_print ("mmInit: stSmallSystem\n");
    }
// Medium. (64MB).
    if (memorysizeTotal >= MEDIUMSYSTEM_SIZE_KB){
        g_mm_system_type = stMediumSystem;
        debug_print ("mmInit: stMediumSystem\n");
    }
// Large. (128MB).
    if (memorysizeTotal >= LARGESYSTEM_SIZE_KB){
        g_mm_system_type = stLargeSystem;
        debug_print ("mmInit: stLargeSystem\n");
    }

    // #debug
    //while(1){}

// Inicializando o framepool (paged pool).
    initializeFramesAlloc();

    // Continua...

// Mapping all the static system areas.
// See: pages.c
    int PagingStatus=-1;
    PagingStatus = (int) mmSetUpPaging();
    if (PagingStatus<0){
        x_panic("mmInit: Paging");
    }

done:

    //#debug
    //debug_print("mmInit: done\n");
    //refresh_screen();
    //while(1){}

    return 0;

fail:
    debug_print("mmInit: fail\n");
    //refresh_screen();
    //while(1){}
    return (int) (-1);
}


/*
 * heapAllocateMemory:
 *     Aloca memória no heap do kernel.
 * IMPORTANTE: 
 *     Aloca BLOCOS de memória dentro do heap do processo Kernel.
 * @todo: 
 *     ?? Ao fim dessa rotina, os valores da estrutura devem ser 
 * armazenas no header, lá onde foi alocado espaço para o header, 
 * assim tem-se informações sobre o header alocado. ??
 *  A estrutura header do heap, é uma estrutura e deve ficar antes 
 * da área desejada. Partes={ header,client,footer }.
 * Obs: 
 *     ?? A estrutura usada aqui é salva onde, ou não é salva ??
 * IN:  size in bytes
 * OUT: address if success. 0 if fail.
 * History:
 *     2015 - Created by Fred Nora.
 * ...
 */

unsigned long heapAllocateMemory (unsigned long size)
{
    struct mmblock_d *Current;

    //pid_t current_process = (pid_t) get_current_process();
    //#todo: process pointer.

// #todo: 
// Aplicar filtro.
// Aqui podemos checar se o quantidade de heap disponível
// está coerente com o tamanho do heap. Se essa quantidade
// for muito grande, maior que o heap total, então temos um problema.
// Se não há espaço disponível no heap, não há muito o que fazer.
// Uma opção seria tentar almentar o heap, se isso for possível.

// Available heap.

    if (g_available_heap == 0)
    {
        // #todo: 
        // Tentar crescer o heap para atender o size requisitado.
        //try_grow_heap() ...
        // #todo: 
        // Aqui poderia parar o sistema e mostrar essa mensagem.
        debug_print ("heapAllocateMemory: [FAIL] g_available_heap={0}\n");
        printf ("heapAllocateMemory: [FAIL] g_available_heap={0}\n");
        goto fail;
    }

// Size limits. (Min, max).
// Se o tamanho desejado for igual a zero.
// @todo: Aqui podemos converter o size para o tamanho mínimo.
// não há problema nisso.

    if (size == 0)
    {
        //size = 1;
        debug_print("heapAllocateMemory: [FAIL] size={0}\n");
        printf("heapAllocateMemory: [FAIL] size={0}\n");
        refresh_screen();
        //?? NULL seria o retorno para esse caso ??
        return (unsigned long) g_heap_pointer;
    }

// Se o tamanho desejado é maior ou 
// igual ao espaço disponível.

    if (size >= g_available_heap)
    {
        // #todo: 
        // Tentar crescer o heap para atender o size requisitado.
        //try_grow_heap() ...
        debug_print ("heapAllocateMemory error: size >= g_available_heap\n");
        printf ("heapAllocateMemory error: size >= g_available_heap\n");
        goto fail;
    }

// Salvando o tamanho desejado.
    last_size = (unsigned long) size;

// Contador de blocos.

try_again:

// #bugbug
// Mesmo tendo espaço suficiente no heap, estamos chegando 
// nesse limite de indices.
// #obs: 
// Temos um limite para a quantidade de índices na lista de blocos.

    mmblockCount++;
    if (mmblockCount >= MMBLOCK_COUNT_MAX){
        x_panic ("heapAllocateMemory: mmblockCount\n");
    }

// #importante
// A variável 'Header', no header do bloco, 
// é o início da estrutura que o define. 'b->Header'. 
// Ou seja, o endereço da variável marca o início da estrutura.
// Pointer Limits:
// ( Não vamos querer um heap pointer fora dos limites 
//   do heap do kernel ).
// Se o 'g_heap_pointer' atual esta fora dos limites do heap, 
// então devemos usar o último válido, que provavelmente está 
// nos limites. ?? #bugbug: Mas se o último válido está sendo 
// usado por uma alocação anterior. ?? Temos flags que 
// indiquem isso ??
// #importante: 
// O HEAP POINTER TAMBÉM É O INÍCIO DE UMA ESTRUTURA. 
// NESSA ESTRUTURA PODEMOS SABER SE O HEAP ESTA EM USO OU NÃO.
// ISSO SE APLICA À TENTATIVA DE REUTILIZAR O ÚLTIMO HEAP 
// POINTER VÁLIDO.

// Se estiver fora dos limites.

    if ( g_heap_pointer < KERNEL_HEAP_START || 
         g_heap_pointer >= KERNEL_HEAP_END )
    {
        // #bugbug: ?? Como saberemos, se o último válido,
        // não está em uso por uma alocação anterior. ??

        //Checa os limites o último last heap pointer válido.
        if ( heap_pointer_last_valid < KERNEL_HEAP_START || 
             heap_pointer_last_valid >= KERNEL_HEAP_END )
        {
            x_panic ("heapAllocateMemory: heap_pointer_last_valid");
        }

        // #todo: 
        // Checar a disponibilidade desse último válido.
        // Ele é válido, mas não sabemos se está disponível.

        // Havendo um last heap pointer válido.
        // ?? isso não faz sentido.

        g_heap_pointer = 
            (unsigned long) (heap_pointer_last_valid + last_size);

        goto try_again;
    }

// Agora temos um 'g_heap_pointer' válido, salvaremos ele.
// 'heap_pointer_last_valid' NÃO é global. Fica nesse arquivo.
    
    heap_pointer_last_valid = (unsigned long) g_heap_pointer;

// #importante:
// Criando um bloco, que é uma estrutura mmblock_d.
// Estrutura mmblock_d interna.
// Configurando a estrutura para o bloco atual.
// Obs: A estutura deverá ficar lá no espaço reservado 
// para o header. (Antes da area alocada).
// #importante
// O endereço do ponteiro da estrutura será o pointer do heap.

    Current = (void *) g_heap_pointer;

    // Se o ponteiro da estrutura de mmblock for inválido.
    if ( (void *) Current == NULL ){
        debug_print ("heapAllocateMemory: [FAIL] struct\n");
        printf      ("heapAllocateMemory: [FAIL] struct\n");
        goto fail;
    }

// #importante:
// obs: 
// Perceba que 'Current' e 'Current->Header' devem ser iguais. 

// Identificadores básicos:
// Endereço onde começa o header.
// Tamanho do header. (TAMANHO DA STRUCT).
// Id do mmblock. (Índice na lista)
// used and magic flags.
// 0=not free 1=FREE (*SUPER IMPORTANTE)

    Current->Header = (unsigned long) g_heap_pointer; 
    Current->headerSize = (unsigned long) MMBLOCK_HEADER_SIZE; 
    Current->Id = (unsigned long) mmblockCount; 
    Current->Free = 0;  // not free
    // ...
    Current->Used = TRUE;
    Current->Magic = 1234;

//
// Mensuradores. (tamanhos) #todo
//

// #todo:
// Tamanho da área reservada para o cliente.
// userareaSize = (request size + unused bytes)
// Zera unused bytes, já que não foi calculado.

// User Area base:
// Onde começa a área solicitada. 
// Fácil. Isso fica logo depois do header.
// Obseve que 'Current->headerSize' é igual a 'MMBLOCK_HEADER_SIZE'
// e que 'Current->headerSize' é o início da estrutura.

    Current->userArea = 
        (unsigned long) (Current->Header + Current->headerSize);

// Footer:
// >> O footer começa no 
// 'endereço do início da área de cliente' + 'o tamanho dela'.
// >> O footer é o fim dessa alocação e início da próxima.
// #bugbug: 
// Penso que aqui deveríamos considerar 
// 'userareaSize' como tamanho da área de cliente, 
// esse tamanho equivale ao tamanho solicitado mais o 
// tanto de bytes não usados.
// #obs: 
// Por enquanto o tamanho da área de cliente tem 
// apenas o tamanho do espaço solicitado.
 
    Current->Footer = 
        (unsigned long) (Current->userArea + size);

// #todo:
    //Current->pid = (pid_t) current_process;
    //Current->process = p;

// #obs: 
// O limite da contagem de blocos foi checado acima.

// Coloca o ponteiro na lista de blocos.

    mmblockList[mmblockCount] = (unsigned long) Current;

// Salva o ponteiro do bloco usado como 'prévio'.
// #obs: 'mm_prev_pointer' não é global, fica nesse arquivo.

    mm_prev_pointer = (unsigned long) g_heap_pointer; 

// ===============================================
//                SUPER IMPORTANTE 
// ===============================================
// Atualiza o ponteiro. 
// Deve ser onde termina o último bloco configurado.
// Isso significa que o próximo ponteiro onde começaremos 
// a próxima estrutura fica exatamente onde começa o footer 
// dessa estrutura.
// Obs: O footer está aqui somente para isso. Para ajudar
// a localizamarmos o início da próxima estrutura.

    g_heap_pointer = (unsigned long) Current->Footer;

// Available heap:
// Calcula o valor de heap disponível para as próximas alocações.
// O heap disponível será o que tínhamos disponível menos o que 
// gastamos agora.
// O que gastamos agora foi o tamanho do header mais o 
// tamanho da área de cliente.

    g_available_heap = 
        (unsigned long) g_available_heap - (Current->Footer - Current->Header);

// Finalmente
// Retorna o ponteiro para o início da área alocada.
// Essa área alocada chamado de user area.
// Obs: Esse é o valor que será usado pela função kmalloc.
// #importante:
// O que acontece se um aplicativo utilizar além da área alocada ??
// O aplicativo invadirá a área do footer, onde está a estrutura do 
// próximo bloco. Inutilizando as informações sobre aquele bloco.
// #aviso: 
// Cuidado com isso. 
// #todo: Como corrigir.?? O que fazer??

    // ok
    return (unsigned long) Current->userArea;

// #todo: 
// Checar novamente aqui o heap disponível. Se esgotou, tentar crescer.
// Colocar o conteúdo da estrutura no lugar destinado para o header.
// O header conterá informações sobre o heap.
// Se falhamos, retorna 0. Que equivalerá à NULL.
fail:
    refresh_screen();
    return (unsigned long) 0;
}

// Mark the structure as 'reusable'. STOCK
// #todo: Precisamos de rotinas que nos mostre
// essas estruturas.
// IN: ptr.
// Esse ponteiro indica o início da área alocada para uso.
// Essa área fica logo após o header.
// O tamanho do header é MMBLOCK_HEADER_SIZE.
void FreeHeap (void *ptr)
{
    struct mmblock_d  *Header;
    

// validation
    if ( (void *) ptr == NULL ){
        debug_print ("FreeHeap: [FAIL] ptr\n");
        return;
    }

// validation
    if ( ptr < (void *) KERNEL_HEAP_START || 
         ptr >= (void *) KERNEL_HEAP_END )
    {
        debug_print ("FreeHeap: [FAIL] ptr limits\n");
        return;
    }

// Header
// Encontrando o endereço do header.
// O ponteiro passado é o endereço da área de cliente.

    unsigned long UserAreaStart = (unsigned long) ptr; 

    Header = (void *) ( UserAreaStart - MMBLOCK_HEADER_SIZE );

    if ( (void *) Header == NULL ){
        debug_print ("FreeHeap: [FAIL] Header\n");
        return;
    }

    if ( Header->Used != TRUE || 
         Header->Magic != 1234 )
    {
        debug_print ("FreeHeap: [FAIL] Header validation\n");
        return;
    }

// Apenas marcamos a estrutura como reusável,
// pois agora ela esta no STOCK.

    Header->Used = TRUE;   // still alive.
    Header->Magic = 4321;  // reusable, stock
    
    // A alocação continua do ponteiro onde parou.
}


/*
 * get_process_heap_pointer:
 *     ?? Pega o 'heap pointer' do heap de um processo. ??
 */

unsigned long get_process_heap_pointer (int pid)
{
    struct process_d *P;
    unsigned long heapLimit=0;

// #todo: 
// Limite máximo.

    if (pid < 0 || pid >= PROCESS_COUNT_MAX){
        printf ("get_process_heap_pointer: pid fail\n");
        goto fail;
    }

// Process.

    P = (void *) processList[pid];
    if ( (void *) P == NULL ){
        printf ("get_process_heap_pointer: struct fail\n");
        goto fail;
    }

// validation
    if (P->used != TRUE || P->magic != 1234){
        printf ("get_process_heap_pointer: struct validation\n");
        goto fail;
    }

// #
// Cada processo tem seu heap.
// É memória em ring3 compartilhada.
// Mas tem processo em ring0. Onde fica o heap nesse caso?

    heapLimit = (unsigned long) (P->HeapStart + P->HeapSize);

    if ( P->HeapPointer < P->HeapStart || 
         P->HeapPointer >= heapLimit )
    {
        printf ("get_process_heap_pointer: heapLimit\n");
        goto fail;
    }

    //Retorna o heap pointer do processo. 
    return (unsigned long) P->HeapPointer;

fail:
    //??
    //refresh_screen();
    return (unsigned long) 0; 
}




