

#include <kernel.h>    


//Variáveis internas. 

// Heap support.
// #todo: Precisamos melhorar esses nomes. nada neles indica que
// estamos lidando com heap.
unsigned long heap_pointer_last_valid;  // Último heap pointer válido. 
unsigned long last_size;        // Último tamanho alocado.
unsigned long mm_prev_pointer;  // Endereço da úntima estrutura alocada.



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
        //printf ("init_heap: [FAIL] g_heap_pointer\n");
        debug_print ("init_heap: [FAIL] g_heap_pointer\n");
        goto fail;
    }

    // Check Heap Pointer overflow.
    if ( g_heap_pointer > kernel_heap_end ){
        //printf ("init_heap: [FAIL] Heap Pointer Overflow\n");
        debug_print ("init_heap: [FAIL] Heap Pointer Overflow\n");
        goto fail;
    }

    // Heap Start
    if ( kernel_heap_start == 0 ){
        debug_print("init_heap: [FAIL] HeapStart\n");
        //printf ("init_heap: [FAIL] HeapStart={%x}\n", 
            //kernel_heap_start );
            
        goto fail;
    }

    // Heap End
    if ( kernel_heap_end == 0 ){
        debug_print("init_heap: [FAIL] HeapEnd\n");
        //printf ("init_heap: [FAIL] HeapEnd={%x}\n", 
        //    kernel_heap_end );
        goto fail;
    }

    // Check available heap.
    // #todo: Tentar crescer o heap.
    if ( g_available_heap == 0 ){
        debug_print ("init_heap: [FAIL] g_available_heap\n");
        //printf      ("init_heap: [FAIL] g_available_heap\n");
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
    //printf ("Done\n");
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
    //printf ("init_heap: Fail\n");
    debug_print ("init_heap: Fail\n");
    
    refresh_screen ();

    return (int) 1;
}



/*
 **************************************************
 * init_stack:
 *     Iniciar a gerência de Stack do kernel. 
 *     #todo: Usar stackInit(). 
 */
 
int init_stack (void)
{

    // Globals

    kernel_stack_end   = (unsigned long) KERNEL_STACK_END; 
    kernel_stack_start = (unsigned long) KERNEL_STACK_START; 

    // End
    if ( kernel_stack_end == 0 ){
        debug_print ("init_stack: [FAIL] kernel_stack_end\n");
        //printf ("init_stack: [FAIL] kernel_stack_end %x \n", 
            //kernel_stack_end );
        goto fail;
    }

    // Start
    if ( kernel_stack_start == 0 ){
        debug_print ("init_stack: [FAIL] kernel_stack_start\n");
        //printf ("init_stack: [FAIL] kernel_stack_start %x \n", 
            //kernel_stack_start );
        goto fail;
    }

    // Done.
    return 0;

fail:
    refresh_screen();
    return (int) 1;
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


/*
 ******************************************
 * mmInit:
 *   Inicializa o memory manager.
 */

// Called by:
// init_runtime in runtime.c

int mmInit(void)
{

    int Status=0;
    int i=0;


    debug_print("mmInit: [TODO] [FIXME]\n");

	// @todo: 
	// Inicializar algumas variáveis globais.
	// Chamar os construtores para inicializar o básico.

	// @todo: 
	// Clear BSS.
	// Criar mmClearBSS()

    // heap and stack

    Status = (int) init_heap();

    if (Status != 0){
        debug_print("mmInit: [FAIL] Heap\n");
        //printf ("mmInit: [FAIL] Heap\n");
        goto fail;
    }


    Status = (int) init_stack();

    if (Status != 0){
        debug_print ("mmInit: [FAIL] Stack\n");
        //printf ("mmInit: [FAIL] Stack\n");
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


   // ...

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

    // Size in KB.
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
        debug_print ("mmInit: stNull\n");
    }

//
// Small
//

    // 32 MB
    if ( memorysizeTotal >= SMALLSYSTEM_SIZE_KB ){
        g_mm_system_type = stSmallSystem;
        debug_print ("mmInit: stSmallSystem\n");
    }

//
// Medium
//

    // 64 MB
    if ( memorysizeTotal >= MEDIUMSYSTEM_SIZE_KB ){
        g_mm_system_type = stMediumSystem;
        debug_print ("mmInit: stMediumSystem\n");
    }

//
// Large
//

    // 128 MB
    if ( memorysizeTotal >= LARGESYSTEM_SIZE_KB ){
        g_mm_system_type = stLargeSystem;
        debug_print ("mmInit: stLargeSystem\n");
    }

    // #debug
    //while(1){}
    
    
    // Inicializando o framepool (paged pool).

    initializeFramesAlloc();

	// Continua...

    debug_print("mmInit: done\n");

    //refresh_screen();
    //while(1){}

    return 0;
    //return (int) Status;

fail:
    debug_print("mmInit: fail\n");
    //refresh_screen();
    //while(1){}
    return 1;
}    


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

        debug_print ("heapAllocateMemory: [FAIL] g_available_heap={0}\n");
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
        debug_print("heapAllocateMemory: [FAIL] size={0}\n");
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

        debug_print ("heapAllocateMemory error: size >= g_available_heap\n");
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
        x_panic ("heapAllocateMemory: mmblockCount\n");
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
            x_panic ("heapAllocateMemory: heap_pointer_last_valid");
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
        debug_print ("heapAllocateMemory: [FAIL] struct\n");
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






















