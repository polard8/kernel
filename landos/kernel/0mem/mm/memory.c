/*
 * File: mm/memory.c
 *
 *    mm support for x86.
 *
 * Atribuições:
 *     + Alocar Heap do Kernel.
 *     + Liberar Heap do Kernel.
 *     + Inicializar Heap e Stack do Kernel.
 *     + Gerenciar Page Directory, Page Table ...
 *     ...
 *
 * Obs:
 *     Uma região é uma área de 4MB alocada. São todas as páginas
 * que cabem em uma tabela, 2014 páginas de 4KB cada. Isso também pode
 * ser chamado de pool e ser alocado todo de uma vez. Até mesmo
 * compartilhado entre processos.
 *
 * Sobre o heap de processo:
 *    Uma variável global indica qual é o Heap do processo atual. 
 *    A estrutura de um processo contém informações sobre o seu Heap.
 *    ... 
 *
 * @todo: Criar: 
 * Criar uma função que aloca memória no heap de um processo. Deve-se usar 
 * o heap do desktop ao qual o processo pertence ou o heap do processo.
 * 
 * Obs: Possíveis organizações de Heap: 
 *     + Heap Size Modifier, (HSM).
 *     + Heap Size Checker, (HSC). 
 *     + Desktop Heap Size Manager, (DHSM). 
 *       Gerencia o Heap alocado para cada desktop. Os programas usam o Heap
 * do seu próprio desktop. Alguns desktops podem ter Heaps pequenos.
 * @todo: Criar o arquivo heap.c para as rotinas de gerência de heap.
 * Continua...
 *
 * Obs: Um processo pode criar um heap privado, que ele usará para alocação 
 * dinâmica.
 *      
 *
 * In this file:
 * =============
 *     +get_process_heap_pointer
 *     +SetKernelHeap
 *     +heapAllocateMemory
 *     +FreeHeap
 *     +init_heap
 *     +init_stack
 *     +init_mm
 *
 *
 * @todo: Criar: heapGetPointer, heapSePointer.
 *
 *
 * @todo: IMPORTANTE: Devemos ter um heap do kernebase, grande
 * o bastante para alocarmos os recursos gráficos grenciados
 * pelo módulo /gramado.
 *
 * @todo:
 * IMPORTANTE: Um alocador de memória física precisa ser criado,
 * que considere o tamanho da memória física disponível.
 * Esse alocador deve ser usado para alocarmos uma região bem grande
 * da memória física onde ficarão os frames de memória física. Os 
 * frames livres serão encontrados nessa região e o alocador de 
 * páginas, utilizará esses frames livres para associá-los às
 * páginas alocadas aos processos.
 *
 * @todo: Variáveis globais devem controlar o início e o fim da área
 * destinada aos frames de memória física. semelhando ao que foi 
 * feito com o heap do kernel base. Faremos isso no início do arquivo mm.h.
 *
 * 
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - basic routines.
 *     ...
 */




#include <kernel.h>
 
 
//Variáveis internas. 

// Heap support.
// #todo: Precisamos melhorar esses nomes. nada neles indica que
// estamos lidando com heap.
unsigned long heap_pointer_last_valid;  // Último heap pointer válido. 
unsigned long last_size;        // Último tamanho alocado.
unsigned long mm_prev_pointer;  // Endereço da úntima estrutura alocada.



/*
 Traduz um endereço virtual em um endereço físico.
unsigned long memoryGetPhysicalAddress( unsigned long virtual_address);
unsigned long memoryGetPhysicalAddress( unsigned long virtual_address){
	//return (unsigned long) ;
}
*/


/*
unsigned long heap_set_new_handler( unsigned long address );
unsigned long heap_set_new_handler( unsigned long address )
{
    unsigned long Old;

    Old = kernel_heap_start;
    
    kernel_heap_start = address;

    return (Old);
};
*/


/*
 ***********************************************************
 * get_process_heap_pointer:
 *     ?? Pega o 'heap pointer' do heap de um processo. ??
 */

unsigned long get_process_heap_pointer (int pid){

    struct process_d *P;

    unsigned long heapLimit=0;


    // #todo: 
    // Limite máximo.

    if (pid < 0){
        printf ("get_process_heap_pointer: pid fail\n");
        goto fail;
    }


    // Process.
    P = (void *) processList[pid];

    if ( (void *) P == NULL ){
        printf ("get_process_heap_pointer: struct fail\n");
        goto fail;
    }

    //#todo: Checar validade.


    // Limits:
    //     Cada processo tem uma área onde ele pode alocar memória, os 
    // processos usam seu próprio heap ou o heap do desktop ao qual 
    // pertencem.
    // Os limites devem ser respeitados.
    // if: Se for menor que o início ou maior que o limite.

    heapLimit = (unsigned long) (P->Heap + P->HeapSize);

    if ( P->HeapPointer < P->Heap || P->HeapPointer >= heapLimit ){
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




// #todo
/*
int 
memory_use_this_heap ( struct heap_d *heap );
int 
memory_use_this_heap ( struct heap_d *heap )
{
    if ( (void *) heap == NULL )
    {
        panic ("memory_use_this_heap: struct");
    }else{

        if ( heap->used != 1 || heap->magic != 1234 )
        {
            panic ("memory_use_this_heap: validation");
        }

        // #todo
    };
}
*/




/*
 ****************************************************
 * memory_create_new_head:
 * 
 *     Cria um novo heap dado um endereço virtual válido.
 *     #importante
 *     Só podemos usar isso depois que configurarmos manualmente
 *     o heap do kernel.
 */

struct heap_d *memory_create_new_head ( 
    unsigned long start_va, 
    unsigned long size )
{

    struct heap_d *h;  
    struct heap_d *tmp;

    unsigned long __start=0;
    unsigned long __end=0; 
    unsigned long __available=0;

    // Slot support.
    int __slot = -1;
    int i=0;


    // #todo
    // Tem outros limites que precisam ser respeitados.

    // No início da memória virtual.
    if ( start_va == 0 ){
        panic ("memory_create_new_head: Invalid address! (1)");
    }

    // Em cima da imagem do app.
    if ( start_va >= 0x00400000 && start_va <= 0x007F0000 ){
        panic ("memory_create_new_head: Invalid address! (2)");
    }
    
    // Em cima da imagem do kernel.
    if ( start_va >= 0xC0000000 && start_va <= 0xC0100000 ){
        panic ("memory_create_new_head: Invalid address! (3)");
    }
   
    
    // #bugbug
    // Ajuste para o mínimo.
    if ( size == 0 ){
        debug_print ("memory_create_new_head: ajust size\n");
        size = 32;
    }


    // Não pode ser maior que 4MB.
    // Por enquanto.
    //if ( size >= (1024*1024*4) )
    if ( size >= (1024*1024*2) ){
        panic ("memory_create_new_head: Invalid size");
    }
 

    __start     = (unsigned long) start_va;
    __end       = (unsigned long) (__start + size);  
    __available = (unsigned long) size;


    // Get slot

    for ( i=0; i<HEAP_COUNT_MAX; i++ )
    {
        tmp = ( struct heap_d * ) heapList[i];
        
        // Ok.
        if ( (void *) tmp == NULL ){ __slot=i; goto ok; }
    }

    panic ("memory_create_new_head: Overflow");

// Ok. 
// Temos um slot livre.
//=========================
ok:

    if ( __slot <= 0 || __slot >= HEAP_COUNT_MAX )
    {
        panic ("memory_create_new_head: __slot\n");
    }

    //
    // Struct
    //
    
    // Podemos alocar memória para a estrutura de heap
    // porque já temos p heap do kernel que foi
    // criado usando variáveis globais.
    // As variáveis globais servem para o heap atual.

    h = (void *) kmalloc(size);

    if ( (void *) h == NULL ){
        panic ("memory_create_new_head: struct\n");
    }else{

        h->used  = TRUE;
        h->magic = 1234;

        h->id = __slot;

        //#todo
        //h->objectType = 0;
        //h->objectClass = 0;

        h->HeapStart = (unsigned long) __start;
        h->HeapEnd   = (unsigned long) __end;

        h->HeapPointer   = (unsigned long) h->HeapStart;
        h->AvailableHeap = (unsigned long) __available;

        // Register

        heapList[__slot] = (unsigned long) h;

        return ( struct heap_d *) h;
    };

    // Fail.

    debug_print ("memory_create_new_head: Fail\n");
    //panic ("memory_create_new_head: Fail\n");

    return NULL;
}


// Destrói um heap se as flags permitirem.
// Isso deve ser chamado pelo gc. ?

void memory_destroy_heap (struct heap_d *heap)
{
    int __slot = -1;


    if ( (void *) heap == NULL ){
        debug_print ("memory_destroy_heap: [FAIL] heap\n");
        return;
    }else{

        // #gc
        // Condição que permite destruir.
        if ( heap->used != 216 || heap->magic != 4321 )
        {
            // Limpa a lista e destroi o ponteiro.
            // #bugbug: e os elementos da estrutura ??
            
            if ( heap->id >= 0 || heap->id < HEAP_COUNT_MAX )
            {
                __slot = heap->id;
                heapList[__slot] = (unsigned long) 0;
                heap = NULL;
            }
        }
    };
}



/*
 * HeapAlloc:
 * @todo: Criar essa rotina.
 * Aloca memória dentro de um heap determinado.
 * Esse rotina deve ser oferecida como serviço e chamada via system call.
void* HeapAlloc(struct heap_d * heap, unsigned long size);
void* HeapAlloc(struct heap_d * heap, unsigned long size)
{
	return (void*) ...;
}
*/


/*
 * GetProcessHeap:
 @todo:
 Retorna um ponteiro para a estrutura do heap de um processo.
 Obs: Oferecer como serviço do sistema.
void *GetProcessHeap(struct process_d *process);
void *GetProcessHeap(struct process_d *process)
{
	return NULL;
}
*/


/*
 * GetHeap:
 @todo:
 Retorna um ponteiro para o heap do processo atual.
 Obs: Oferecer como serviço do sistema.
void *GetHeap();
void *GetHeap()
{
	//@todo: Pegar o identificador do processo atual.
	//pegar na estrutura do processo o ponteiro para seu heap.
	return NULL;
}
*/


/*
 ****************************************************************
 * heapAllocateMemory:
 *     Aloca memória no heap do kernel.
 *
 * *IMPORTANTE: 
 *     Aloca BLOCOS de memória dentro do heap do processo Kernel.
 *
 * @todo: 
 *     ?? Ao fim dessa rotina, os valores da estrutura devem ser 
 * armazenas no header, lá onde foi alocado espaço para o header, 
 * assim tem-se informações sobre o header alocado. ??
 *
 *  A estrutura header do heap, é uma estrutura e deve ficar antes 
 * da área desejada. Partes={ header,client,footer }.
 *
 * Obs: 
 *     ?? A estrutura usada aqui é salva onde, ou não é salva ??
 *
 * IN:  size in bytes
 * OUT: address if success. 0 if fail.
 *
 * History:
 *     2015 - Created by Fred Nora.
 * ...
 */

unsigned long heapAllocateMemory ( unsigned long size )
{
    struct mmblock_d *Current;

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

        printf ("heapAllocateMemory: [FAIL] g_available_heap={0}\n");
        goto fail;
    }


    //
    // Size limits. (Min, max).
    //

    // Se o tamanho desejado for igual a zero.
    // @todo: Aqui podemos converter o size para o tamanho mínimo.
    // não há problema nisso.

    if ( size == 0 )
    {
        //size = 1;
        printf("heapAllocateMemory: [FAIL] size={0}\n");
        refresh_screen();
        
        //?? NULL seria o retorno para esse caso ??
        return (unsigned long) g_heap_pointer;
    }


    // Se o tamanho desejado é maior ou 
    // igual ao espaço disponível.
    if( size >= g_available_heap )
    {
        //
        // @todo: Tentar crescer o heap para atender o size requisitado.
        //

        //try_grow_heap() ...

        printf ("heapAllocateMemory error: size >= g_available_heap\n");
        goto fail;
    }

	
    //Salvando o tamanho desejado.
    last_size = (unsigned long) size;

    //
    // Contador de blocos.
    //

try_again:

    // #bugbug
    // Mesmo tendo espaço suficiente no heap, estamos chegando 
    // nesse limite de indices.
    // #obs: 
    // Temos um limite para a quantidade de índices na lista de blocos.

    mmblockCount++;

    if ( mmblockCount >= MMBLOCK_COUNT_MAX ){
        panic ("heapAllocateMemory: mmblockCount\n");
    }


    // #importante
    // A variável 'Header', no header do bloco, 
    // é o início da estrutura que o define. 'b->Header'. 
    // Ou seja, o endereço da variável marca o início da
    // estrutura.
    //
    // Pointer Limits:
    // ( Não vamos querer um heap pointer fora dos limites 
	//   do heap do kernel ).
    // Se o 'g_heap_pointer' atual esta fora dos limites do heap, 
	// então devemos usar o último válido, que provavelmente está 
	// nos limites. ?? #bugbug: Mas se o último válido está sendo 
	// usado por uma alocação anterior. ?? Temos flags que 
	// indiquem isso ??
    //
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
            panic ("heapAllocateMemory: heap_pointer_last_valid");
        }

        // #todo: 
		// Checar a disponibilidade desse último válido.
        // Ele é válido, mas não sabemos se está disponível.
		
		//Havendo um last heap pointer válido.
		//?? isso não faz sentido.

        g_heap_pointer = (unsigned long) (heap_pointer_last_valid + last_size);

        goto try_again;
    }

    // Agora temos um 'g_heap_pointer' válido, salvaremos ele.
    // 'heap_pointer_last_valid' NÃO é global. Fica nesse arquivo.
    
    heap_pointer_last_valid = (unsigned long) g_heap_pointer;
    

    // #importante:
    // Criando um bloco, que é uma estrutura mmblock_d.
    // Estrutura mmblock_d interna.
    // Configurando a estrutura para o bloco atual.
    //
    // Obs: A estutura deverá ficar lá no espaço reservado 
    // para o header. (Antes da area alocada).
    //
    // Current = (void*) g_heap_pointer;


	// #importante
	// O endereço do ponteiro da estrutura será o pointer do heap.

    Current = (void *) g_heap_pointer;    

    if ( (void *) Current != NULL )
    {
        // #importante:
        // obs: Perceba que 'Current' e 'Current->Header' 
        // devem ser iguais. 

        // Identificadores básicos:
		// Endereço onde começa o header.
		// Tamanho do header. (*TAMANHO DA STRUCT).
		// Id do mmblock. (Índice na lista)
		// used and magic flags.
		// 0=not free 1=FREE (*SUPER IMPORTANTE)

        Current->Header     = (unsigned long) g_heap_pointer; 
        Current->headerSize = (unsigned long) MMBLOCK_HEADER_SIZE; 

        Current->Id = (unsigned long) mmblockCount; 

        Current->Used  = 1;
        Current->Magic = 1234;

        Current->Free = 0;

        //Continua...

        //
        // Mensuradores. (tamanhos) (@todo:)
        //


        // @todo:
        // Tamanho da área reservada para o cliente.
        // userareaSize = (request size + unused bytes)
        // Zera unused bytes, já que não foi calculado.

        // User Area base:
        // *Onde começa a área solicitada. 
        // *Fácil. Isso fica logo depois do header.

        // Obseve que 'Current->headerSize' é igual 
        // a 'MMBLOCK_HEADER_SIZE'
        // E que 'Current->headerSize' é o início da estrutura.

        Current->userArea = (unsigned long) ( Current->Header + Current->headerSize );

        // Footer:
        // >> O footer começa no 
        // 'endereço do início da área de cliente' + 'o tamanho dela'.
        // >> O footer é o fim dessa alocação e início da próxima.
        //
        // #bugbug: Penso que aqui deveríamos considerar 
        // 'userareaSize' como tamanho da área de cliente, 
        // esse tamanho equivale ao tamanho solicitado mais o 
        // tanto de bytes não usados.
        // Obs: Por enquanto o tamanho da área de cliente tem 
        // apenas o tamanho do espaço solicitado.
 
        Current->Footer = (unsigned long) ( Current->userArea + size );


        // Heap pointer. 
        //     Atualiza o endereço onde vai ser a próxima alocação.

        //if ( Current->Footer < KERNEL_HEAP_START){
        //    Current->Used = 0;                //Flag, 'sendo Usado' ou 'livre'.
        //    Current->Magic = 0;            //Magic number. Ver se não está corrompido.
        //	goto try_again;
        //}


        // obs: 
        // O limite da contagem de blocos foi checado acima.

        //
        // Coloca o ponteiro na lista de blocos.
        //

        mmblockList[mmblockCount] = (unsigned long) Current;

        // Salva o ponteiro do bloco usado como 'prévio'.
        // Obs: 'mm_prev_pointer' não é global, fica nesse arquivo.

        mm_prev_pointer  = (unsigned long) g_heap_pointer; 


        // *****************************************************
        //                **** SUPER IMPORTANTE ****
        // *****************************************************
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
        // O que gastamos agora foi o tamanho do header mais o tamanho da área
        // de cliente.

        g_available_heap = (unsigned long) g_available_heap - (Current->Footer - Current->Header);

        
        // #Finalmente
        //
        // Retorna o ponteiro para o início da área alocada.
        // Essa área alocada chamado de user area.
        // Obs: Esse é o valor que será usado pela função kmalloc.
        //
        // #Importante:
        // O que acontece se um aplicativo utilizar além da área alocada ??
        // O aplicativo invadirá a área do footer, onde está a estrutura do 
        // próximo bloco. Inutilizando as informações sobre aquele bloco.
        // #Aviso: 
        // Cuidado com isso. @todo: Como corrigir.?? O que fazer??

        // ok.

        return (unsigned long) Current->userArea;

        // Nothing

    // Se o ponteiro da estrutura de mmblock for inválido.
    }else{
        printf ("heapAllocateMemory: [FAIL] struct\n");
        goto fail;
    };

    // #todo: 
    // Checar novamente aqui o heap disponível. Se esgotou, tentar crescer.
    // Colocar o conteúdo da estrutura no lugar destinado para o header.
    // O header conterá informações sobre o heap.
    // Se falhamos, retorna 0. Que equivalerá à NULL.

fail:
    refresh_screen();
    return (unsigned long) 0;
}


/*
 ********************
 * FreeHeap:
 */

void FreeHeap (void *ptr){

    struct mmblock_d *Header;


    if ( (void *) ptr == NULL ){
        debug_print ("FreeHeap: [FAIL] ptr\n");
        return;
    }

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
    }else{
        if ( Header->Used != 1 || Header->Magic != 1234 ){
            debug_print ("FreeHeap: [FAIL] Header validation\n");
            return;
        }

        // Check
        if ( mmblockList[mmblockCount] == (unsigned long) Header && 
             Header->Id == mmblockCount )
        {
            mmblockList[mmblockCount] = 0;
            mmblockCount--;
        }

        // Isso invalida a estrutura, para evitar mal uso.

        Header->Used  = 0;
        Header->Magic = 0;
        
        g_heap_pointer = (unsigned long) Header;
    };
}


/*
 *********************************************
 * init_heap:
 * 
 *     Iniciar a gerência de Heap do kernel. 
 *     @todo: Usar heapInit() ou heapHeap(). memoryInitializeHeapManager().
 *
 * Essa rotina controi a mão o heap usado pelo processo kernel.
 *     +Ela é chamada apenas uma vez.
 *     +Ela deve ser chamada entes de quelquer outra operação 
 * envolvendo o heap do processo kernel.
 * 
 * @todo: Rotinas de automação da criação de heaps para processos.
 */

//int memoryInitializeHeapManager() 

int init_heap (void){

    int i=0;

    // #bugbug
    // não usar printf
    // printf ainda não funciona nesse momento.

    //
    // Globals
    //

    // start and end.

    kernel_heap_start = (unsigned long) KERNEL_HEAP_START;
    kernel_heap_end   = (unsigned long) KERNEL_HEAP_END;


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
        printf ("init_heap: [FAIL] g_heap_pointer\n");
        goto fail;
    }

    // Check Heap Pointer overflow.
    if ( g_heap_pointer > kernel_heap_end ){
        printf ("init_heap: [FAIL] Heap Pointer Overflow\n");
        goto fail;
    }

    // Heap Start
    if ( kernel_heap_start == 0 ){
        printf ("init_heap: [FAIL] HeapStart={%x}\n", 
            kernel_heap_start );
        goto fail;
    }

    // Heap End
    if ( kernel_heap_end == 0 ){
        printf ("init_heap: [FAIL] HeapEnd={%x}\n", 
            kernel_heap_end );
        goto fail;
    }

    // Check available heap.
    // #todo: Tentar crescer o heap.
    if ( g_available_heap == 0 ){
        debug_print ("init_heap: [FAIL] g_available_heap\n");
        printf      ("init_heap: [FAIL] g_available_heap\n");
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

// Done.

#ifdef PS_VERBOSE
    // #bugbug
    // printf ainda não funciona nesse momento.
    printf ("Done\n");
#endif

    return 0;


// Falha ao iniciar o heap do kernel.
// ====================================

fail:

    // #debug
    /*
    printf("* Debug: %x %x %x %x \n", 
        kernel_heap_start, kernel_heap_end,
        kernel_stack_start, kernel_stack_end);
    refresh_screen();
    while(1){}
    */

    // #bugbug
    // printf ainda não funciona nesse momento.
    printf ("init_heap: Fail\n");
    
    refresh_screen ();

    return (int) 1;
}


/*
 **************************************************
 * init_stack:
 *     Iniciar a gerência de Stack do kernel. 
 *     #todo: Usar stackInit(). 
 */
 
int init_stack (void){

    // Globals

    kernel_stack_end   = (unsigned long) KERNEL_STACK_END; 
    kernel_stack_start = (unsigned long) KERNEL_STACK_START; 

    // End
    if ( kernel_stack_end == 0 ){
        printf ("init_stack: [FAIL] kernel_stack_end %x \n", 
            kernel_stack_end );
        goto fail;
    }

    // Start
    if ( kernel_stack_start == 0 ){
        printf ("init_stack: [FAIL] kernel_stack_start %x \n", 
            kernel_stack_start );
        goto fail;
    }

    // Done.
    return 0;

fail:
    refresh_screen();
    return (int) 1;
}


/*
 ******************************************
 * mmInit:
 *   Inicializa o memory manager.
 */

// Called by:
// init_runtime in runtime.c

int mmInit (void){

    int Status=0;
    int i=0;


    debug_print("mmInit:\n");


	// @todo: 
	// Inicializar algumas variáveis globais.
	// Chamar os construtores para inicializar o básico.

	// @todo: 
	// Clear BSS.
	// Criar mmClearBSS()

    // heap and stack

    Status = (int) init_heap();

    if (Status != 0){
        printf ("mmInit: [FAIL] Heap\n");
        goto fail;
    }


    Status = (int) init_stack();

    if (Status != 0){
        printf ("mmInit: [FAIL] Stack\n");
        goto fail;
    }


	// Zerar a lista.
	// Lista de blocos de memória dentro do heap do kernel.

    while ( i < MMBLOCK_COUNT_MAX )
    {
        mmblockList[i] = (unsigned long) 0;
        i++;
    };


	//Primeiro Bloco.
    //current_mmblock = (void *) NULL;
	
	//#importante:
	//#inicializando o índice la lista de ponteiros 
	//par estruturas de alocação.

    mmblockCount = 0;


	//
	// MEMORY SIZES
	//
	
	// Get memory sizes via RTC. (KB)
	// base, other, extended.
	// RTC só consegue perceber 64MB de memória.

    memorysizeBaseMemory  = (unsigned long) rtcGetBaseMemory();  
    memorysizeOtherMemory = (unsigned long) (1024 - memorysizeBaseMemory);


    // #todo
    // New we have a new value from boot.
    // We're gonna use this new value instead the one from cmos.

    unsigned long __total_memory_in_kb = (blSavedLastValidAddress/0x400);

    // extended memory from cmos.
    //memorysizeExtendedMemory = (unsigned long) rtcGetExtendedMemory(); 
    memorysizeExtendedMemory =  (__total_memory_in_kb - memorysizeBaseMemory - memorysizeOtherMemory);

    memorysizeTotal = (unsigned long) ( memorysizeBaseMemory + memorysizeOtherMemory + memorysizeExtendedMemory );



    // #IMPORTANTE 
    // Determinar o tipo de sistema de memória.
    // small   pelo menos 32mb
    // medium  pelo menos 64mb
    // large   pelo menos 128mb

    // 0MB
    // #atenção 
    // Nesse caso devemos prosseguir e testar as outras opções.
    if ( memorysizeTotal >= (0) ){
        g_mm_system_type = stNull;
    }

    // 32MB
    if ( memorysizeTotal >= SMALLSYSTEM_SIZE_KB ){
        g_mm_system_type = stSmallSystem;
    }

    // 64MB
    if ( memorysizeTotal >= MEDIUMSYSTEM_SIZE_KB ){
        g_mm_system_type = stMediumSystem;
    }

    // 128MB
    if ( memorysizeTotal >= LARGESYSTEM_SIZE_KB ){
        g_mm_system_type = stLargeSystem;
    }

    // Inicializando o framepool (paged pool).

    initializeFramesAlloc();

	// Continua...

    debug_print("mmInit: done\n");

    return (int) Status;

fail:
    refresh_screen();
    return 1;
}



/*
 ******************************
 * kernel_gc:
 * 
 * Kernel Garbage Collector.
 * It's used to clean some unused memory.
 * It will be called by the idle thread.
 */

// #todo
// review and improve this function. 

int kernel_gc (void){


    struct mmblock_d  *b;  // memory block.
    struct heap_d     *h;  // heap.
    int i=0;
    // ...


    //#todo: Test this thing!
    //debug_print("kernel_gc: \n");
    
    
	//#importante:
	//mmblock_d é a estrutura usada pelo kmalloc para organizar as alocações 
	//dentro de um heap. 
	//Essa estrutura será sinalizada com Free=1 e precisa liberar a área do cliente.
	
	//mmblockList[]
	//#importante: Nessa lista tem ponteiros para uma estrutura especial,
	//usada pela kmalloc para organizar os blocos de memória que serão utilizados 
	//para alocação dinâmica.

    for ( i=0; i<MMBLOCK_COUNT_MAX; i++ )
    {
        b = (void *) mmblockList[i];

		// Valid pointer.
        if ( (void *) b != NULL )
        {
			// Sinalizado para o GC.
			// #bugbug: rever a sinalização de 'free'.
            if ( b->Used  == 216 && 
                 b->Magic == 4321 && 
                 b->Free  == TRUE )
            {
                goto clear_mmblock;
            }
        }
    };

	
	//heapList[]
	//Limpar a lista de heaps.
	//Existirão vários heaps que poderão ser usados pelos alocadores.
	//Essa lista tem o pnteiros para heaps.

    for ( i=0; i<HEAP_COUNT_MAX; i++ )
    {
	    h = (void *) heapList[i];
		
		// Valid pointer.
	    if ( (void *) h != NULL )
		{
			//sinalizado para o GC.
			if( h->used == 216 && h->magic == 4321 )
			{
				goto clear_heap;
			}
		}
    };


	// #importante:
	// #todo: Cria os 'for's para as outras listas.
	// ex: session, window station, desktop, window etc ...

	
    goto done;
	
	// Segue operações de limpeza em estruturas de tipos diferentes.
	// Devemos limpar e sairmos em seguida.
	
	//Nothing
	
clear_mmblock:	
    
    if ( (void *) b != NULL )
    {
		//Checar se a área alocada está dentro dos limites.
	    //O inicio da área mais o tamanho dela tem que coincidir 
		//com o footer.

        if ( (b->userArea + b->userareaSize) != b->Footer ){

			//#debug
			//printf("gc fail: User Area Size");
			//goto fail;

            return (int) 1;

        // Preenche com zeros a área do cliente.
        }else{
            bzero ( (char *) b->userArea, (int) b->userareaSize );
        };

        // Nothing.
    };
    goto done;
	//Nothing.
	
clear_heap:

    if ( (void *) h != NULL )
    {
		// ?? O que fazer aqui ??
		
		//Limparemos mas não deletaremos.
		//h->used  = 1;
		//h->magic = 1234;
		
		//#todo: 
		//Por enquanto vamos desabilitar a estrutura cancelada 
		//pelo sistema.
        if ( h->used == 216 && h->magic == 4321 )
        {
            h->used  = 0;
            h->magic = 0;
            h = NULL;
        }

		//lista encadeada de blocos que formavam o heap.
		//podemos apenas sinalizar todos os mmblocks dessa lista e depois o GC acaba com eles.
		//para isso precisamos de um 'for'.
		//h->mmblockListHead = NULL;
    };
    goto done;
	//Nothing.

	// #todo: 
	// Criar as rotinas de limpeza para as outras listas.

fail:
    refresh_screen();
    return (int) 1;
done:
    return 0;
}



// #todo
/*
unsigned long mm_query_system_size(void);
unsigned long mm_query_system_size(void)
{
    return (unsigned long) memorysizeTotal;
}
*/


//
// End.
//


