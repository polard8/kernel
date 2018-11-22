/*
 * File: pc\mm\memory.c
 *
 * Descrição:
 *     Arquivo principal do módulo /mm do /pc, Memory Manager. 
 *     MB - Módulos incluídos no Kernel Base.
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
 *     +AllocateHeap
 *     +FreeHeap
 *     +AllocateHeapEx
 *     +show_memory_structs
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
 * Histórico:
 *     Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *     Versão 1.0, 2016 - Aprimoramento geral das rotinas básicas.
 *     ...
 */

 
/*
 @todo:
 +Criar o arquivo heap.c 
 +Criar a função CreateHeap: Se o argumento 'endereço' for nulo, alocamos memória.
 ...
*/ 
 
 
#include <kernel.h>
 
 
//Variáveis internas. 

//int mmStatus;
unsigned long last_valid;         //Último heap pointer válido. 
unsigned long last_size;          //Último tamanho alocado.
unsigned long mm_prev_pointer;    //Endereço da úntima estrutura alocada.



/*
 * memsize: 
 *     Testando manualmente o tamanho da memória.
 *     ## Adaptado de SANOS - Michael Ringgaard.
 *     @todo: Corrigir o asm inline. usar padrão gcc.
 *
 */

/* 
unsigned long memsize();  
unsigned long memsize() 
{
    volatile unsigned long *mem;
  unsigned long addr;
  unsigned long value;
  unsigned long cr0save;
  unsigned long cr0new;

  // Start at 1MB
  addr = 1024 * 1024;

  // Save a copy of CR0
  __asm { mov eax, cr0 };
  __asm { mov [cr0save], eax };

  // Invalidate the cache (write-back and invalidate the cache)
  __asm { wbinvd };

  // Plug cr0 with just PE/CD/NW (cache disable(486+), no-writeback(486+), 32bit mode(386+))
  cr0new = cr0save | 0x00000001 | 0x40000000 | 0x20000000;
  __asm { mov eax, [cr0new] };
  __asm { mov cr0, eax };

  //Probe for each megabyte
  
    while(addr < 0xFFF00000){
		
        addr += 1024 * 1024;
        mem = (unsigned long *) addr;

        value = *mem;
        *mem = 0x55AA55AA;

        if(*mem != 0x55AA55AA) break;

        *mem = 0xAA55AA55;
        if(*mem != 0xAA55AA55) break;

        *mem = value;  //corrige.
    };

  //Restore 
  
  __asm { mov eax, [cr0save] };
  __asm { mov cr0, eax };

  return addr;
}
*/

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
 *
 */
unsigned long get_process_heap_pointer ( int pid ){
	
	struct process_d *P;
	
	unsigned long heapLimit;
	
	//@todo: Limite máximo.
	if (pid < 0){
		
		printf("get_process_heap_pointer: pid fail\n");
		goto fail;
	};
	
	P = (void *) processList[pid];
	
	if ( (void *) P == NULL ){
		
		printf("get_process_heap_pointer: struct fail\n");
		goto fail;
	};
	
	//Obs podemos checr 'used' e 'magic'.
	
	//
	// Limits:
	//     Cada processo tem uma área onde ele pode alocar memória, os 
    // processos usam seu próprio heap ou o heap do desktop ao qual pertencem.
    // Os limites devem ser respeitados.	
	//
	
	heapLimit = (unsigned long) (P->Heap + P->HeapSize);
	
	//Se for menor que o início ou maior que o limite.
	if ( P->HeapPointer < P->Heap || P->HeapPointer >= heapLimit ){
		
		printf("get_process_heap_pointer: heapLimit\n");
		goto fail;
	};
	
//done:

    //Retorna o heap pointer do processo. 
	return (unsigned long) P->HeapPointer;
fail:
    return (unsigned long) 0;    
};


/*
 ****************************************************
 * SetKernelHeap:
 *    Configura o heap do kernel.
 *    Reconfiguração total do heap do kernel.
 *    @todo: Salvar em estrutura de processo. 
 * O kernel tem seu processo.
 */
void 
SetKernelHeap( unsigned long HeapStart, 
               unsigned long HeapSize )
{
	struct heap_d *h;    //Kernel Heap struct.    
	
	
	// Check limits.
	
	//if(HeapStart == 0){}
	//if(HeapSize == 0){}

    //
    // Salvando em variáveis globais.
    //
	
	//start, end, pointer, available.    
	
	kernel_heap_start = (unsigned long) HeapStart;                 
	kernel_heap_end   = (unsigned long) (HeapStart + HeapSize);
	
	g_heap_pointer    = (unsigned long) kernel_heap_start;            
	g_available_heap  = (unsigned long) (kernel_heap_end - kernel_heap_start); 
	
	
	//
	// ?? Devemos checar a validade dessa estrutura ??
	//
	
	//A estrutura fica no início do heap.??!!
	h = (void *) kernel_heap_start;
	
	//Configurando a estrutura.
	h->HeapStart = (unsigned long) kernel_heap_start;             
	h->HeapEnd   = (unsigned long) kernel_heap_end;
	
	h->HeapPointer   = (unsigned long) g_heap_pointer;            
	h->AvailableHeap = (unsigned long) g_available_heap; 	
	
	
	//
	// Configura a estrutura global que guarda informações sobre o heap do 
	// kernel. 'KernelHeap'
	//
	
	KernelHeap = (void *) h;
	
	//
	// Lista de heaps.
	//
	
	//@todo: Um 'for' pode inicializar essa lista com '0' nesse momento.
	//for(...)
	
	
	//Configuração inicial da lista de heaps. Só temos 'um' ainda.
	heapList[0] = (unsigned long) KernelHeap;  //Configura o heap do kernel.
	heapList[1] = (unsigned long) 0;
	heapList[2] = (unsigned long) 0;
	//...
	
	//Contagem? ainda em zero.?!
};



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
 * AllocateHeap:
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
 * @todo: 
 *     Essa rotina poderia se chamar: 
 *     memoryKernelProcessHeapAlloc(unsigned long size).
 * Obs: 
 *     ?? A estrutura usada aqui é salva onde, ou não é salva ??
 *
 * IN:  size in bytes
 * OUT: address if success. 0 if fail.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - Revision.
 * ...
 */
unsigned long AllocateHeap ( unsigned long size ){
	
    struct mmblock_d *Current;
    //struct mmblock_d *Prev;

    //
    // @todo: Aplicar filtro.
    // Aqui podemos checar se o quantidade de heap disponível
    // está coerente com o tamanho do heap. Se essa quantidade
    // for muito grande, maior que o heap total, então temos um
    // problema.
    //

    //
    // Se não há espaço disponível no heap, não há muito o que fazer.
    // Uma opção seria tentar almentar o heap, se isso for possível.
    //

    // Available heap.
    if(g_available_heap == 0)
    {
        //
        // @todo: Tentar crescer o heap para atender o size requisitado.
        //

        //try_grow_heap() ...

        //
        // @todo: Aqui poderia parar o sistema e mostrar essa mensagem.
        //

        printf("AllocateHeap fail: g_available_heap={0}\n");
        goto fail;
    };


    //
    // Size limits. (Min, max).
    //

    // Se o tamanho desejado for igual a zero.
    // @todo: Aqui podemos converter o size para o tamanho mínimo.
    // não há problema nisso.
    if( size == 0 )
	{
        //size = 1;
        printf("AllocateHeap error: size={0}\n");
        refresh_screen();
        
		//?? NULL seria o retorno para esse caso ??
		return (unsigned long) g_heap_pointer;
    };

    // Se o tamanho desejado é maior ou 
	// igual ao espaço disponível.
    if( size >= g_available_heap )
    {
        //
        // @todo: Tentar crescer o heap para atender o size requisitado.
        //

        //try_grow_heap() ...

        printf("AllocateHeap error: size >= g_available_heap\n");
        goto fail;
    };
    
    //Salvando o tamanho desejado.
    last_size = (unsigned long) size;
    
    //
    // Contador de blocos.
    //

try_again:

    mmblockCount++;  
    
    // #bugbug
    // Mesmo tendo espaço suficiente no heap, estamos chegando 
	// nesse limite de indices.
    // Obs: Temos um limite para a quantidade de índices 
	// na lista de blocos.
    
	if( mmblockCount >= MMBLOCK_COUNT_MAX )
	{
        printf("pc-mm-memory-AllocateHeap: MMBLOCK_COUNT_MAX");
        die();
    };

    //
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
    //

    //Se estiver fora dos limites.
    if( g_heap_pointer < KERNEL_HEAP_START || 
        g_heap_pointer >= KERNEL_HEAP_END )
    {
        // #bugbug: ?? Como saberemos, se o último válido,
        // não está em uso por uma alocação anterior. ??

        //Checa os limites o último last heap pointer válido.
        if( last_valid < KERNEL_HEAP_START || 
           last_valid >= KERNEL_HEAP_END )
        {
            printf("pc-mm-memory-AllocateHeap: last_valid");
            die();
        };

        //
        // @todo: Checar a disponibilidade desse último válido.
        // Ele é válido, mas não sabemos se está disponível.
		
		//Havendo um last heap pointer válido.
		//?? isso não faz sentido.
		g_heap_pointer = (unsigned long) last_valid + last_size;
		goto try_again;
	};
	

    //
    // Agora temos um 'g_heap_pointer' válido, salvaremos ele.
    // 'last_valid' NÃO é global. Fica nesse arquivo.
    //
    
    last_valid = (unsigned long) g_heap_pointer;
    
    //
	// #importante:
    // Criando um bloco, que é uma estrutura mmblock_d.
    // Estrutura mmblock_d interna.
    // Configurando a estrutura para o bloco atual.
    //
    // Obs: A estutura deverá ficar lá no espaço reservado 
	// para o header. (Antes da area alocada).
	//
    // Current = (void*) g_heap_pointer;
    //

    
	// ## importante ##
	// O endereço do ponteiro da estrutura será o pointer do heap.
	
    Current = (void *) g_heap_pointer;    

    if( (void *) Current != NULL )
    {
        // #importante:
		// Obs: Perceba que 'Current' e 'Current->Header' 
		// devem ser iguais. 

        // Identificadores básicos:
		// Endereço onde começa o header.
		// Tamanho do header. (*TAMANHO DA STRUCT).
		// Id do mmblock. (Índice na lista)
		// used and magic flags.
		// 0=not free 1=FREE (*SUPER IMPORTANTE)
		Current->Header = (unsigned long) g_heap_pointer;  
        Current->headerSize = MMBLOCK_HEADER_SIZE;         
        Current->Id = mmblockCount;                        
        Current->Used = 1;                
        Current->Magic = 1234;            
        Current->Free = 0;                
        //Continua...

        //
        // Mensuradores. (tamanhos) (@todo:)
        //

        //
        // @todo:
        // Tamanho da área reservada para o cliente.
        // userareaSize = (request size + unused bytes)
        // Zera unused bytes, já que não foi calculado.
        //

        //
        // User Area base:
        // *Onde começa a área solicitada. 
        // *Fácil. Isso fica logo depois do header.
        //

        // Obseve que 'Current->headerSize' é igual 
		// a 'MMBLOCK_HEADER_SIZE'
        // E que 'Current->headerSize' é o início da estrutura.

        Current->userArea = (unsigned long) Current->Header + Current->headerSize;

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
        
		Current->Footer = (unsigned long) Current->userArea + size;

        //
        // Heap pointer. 
        //     Atualiza o endereço onde vai ser a próxima alocação.
        //

        //if ( Current->Footer < KERNEL_HEAP_START){
        //    Current->Used = 0;                //Flag, 'sendo Usado' ou 'livre'.
        //    Current->Magic = 0;            //Magic number. Ver se não está corrompido.
        //	goto try_again;
        //}


        //
        // Obs: O limite da contagem de blocos foi checado acima.
        //

        //
        // Coloca o ponteiro na lista de blocos.
        //

        mmblockList[mmblockCount] = (unsigned long) Current;

        //
        // Salva o ponteiro do bloco usado como 'prévio'.
        // Obs: 'mm_prev_pointer' não é global, fica nesse arquivo.
        //

        mm_prev_pointer  = (unsigned long) g_heap_pointer; 

        //
        // *****************************************************
        //                **** SUPER IMPORTANTE ****
        // *****************************************************
        //
        // Atualiza o ponteiro. 
		// Deve ser onde termina o último bloco configurado.
        // Isso significa que o próximo ponteiro onde começaremos 
		// a próxima estrutura fica exatamente onde começa o footer 
		// dessa estrutura.
        // Obs: O footer está aqui somente para isso. Para ajudar
        // a localizamarmos o início da próxima estrutura.
        //

        g_heap_pointer = (unsigned long) Current->Footer;


        //
        // Available heap:
        // Calcula o valor de heap disponível para as próximas alocações.
        // O heap disponível será o que tínhamos disponível menos o que 
        // gastamos agora.
        // O que gastamos agora foi o tamanho do header mais o tamanho da área
        // de cliente.
        //

        g_available_heap = (unsigned long) g_available_heap - (Current->Footer - Current->Header);

        //
		// ## Finalmente ##
		//
        // Retorna o ponteiro para o início da área alocada.
		// Essa área alocada chamado de user area.
        // Obs: Esse é o valor que será usado pela função malloc.
        //
        // *Importante:
        // O que acontece se um aplicativo utilizar além da área alocada ??
        // O aplicativo invadirá a área do footer, onde está a estrutura do 
        // próximo bloco. Inutilizando as informações sobre aquele bloco.
        // *Aviso: Cuidado com isso. @todo: Como corrigir.?? O que fazer??
        //

        return (unsigned long) Current->userArea;
        //Nothing.

    }else{

        //Se o ponteiro da estrutura de mmblock for inválido.
        printf("AllocateHeap fail: struct.\n");
        goto fail;
    };


    //
    // @todo: 
    // Checar novamente aqui o heap disponível. Se esgotou, tentar crescer.
    //


    /*
     * *IMPORTANTE
     *
     * @todo:
     * Colocar o conteúdo da estrutura no lugar destinado para o header.
     * O header conterá informações sobre o heap.
     *
     */


    /* errado #bugbug.
    Prev = (void*) mm_prev_pointer;

    if( (void*) Prev != NULL)
    {
        if( Prev->Used == 1 && 
            Prev->Magic == 1234 && 
            Prev->Free == 0)
        {
            Current->Prev = (void*) Prev;
            Prev->Next = (void*) Current;
        };
    };
    */


//
// Fail.
//

fail:
    refresh_screen();
    //Se falhamos, retorna 0. Que equivalerá à NULL.
    return (unsigned long) 0;
};


/*
 * FreeHeap: #bugbug
 * @todo: Implementar essa função.
 * Objetivo: Liberar o bloco de memória, configurando a sua estrutura.
 * Libera memória.
 * O argumento é a diferença entra o ponteiro antigo e o novo ponteiro 
 * desejado. 
 * Ponteiros do início da área do cliente.
 * ??
 */
unsigned long FreeHeap (unsigned long size){
	
    // #cancelada !
	// Usaremos flags e o GC. 
	return (unsigned long) g_heap_pointer;    
};


/*
 **********************************************
 * AllocateHeapEx:
 *     Aloca heap.
 *     @todo: Deletar: Rotina inútil.
 */
void *AllocateHeapEx (unsigned long size){
	
	return (void *) AllocateHeap(size);  
};


/*
 ********************************************************
 * show_memory_structs:
 *     *IMPORTANTE.
 *     Mostra as informações das estruturas de memória. 
 * @todo: 
 *     Mostrar a memória usada pelos processos.
 *     Mostrar o quanto de memória o processo usa.
 *     *Importante: Esse tipo de rotina mereçe muita atenção
 * principalmente na fase inicial de construção do sistema.
 * Apresentar as informações em uma janela bem grande e 
 * chamar através do procedimento de janela do sistema é 
 * uma opção bem interessante.
 * Por enquanto apenas escrevemos provavelmente na janela como 
 * foco de entrada e o procedimento de janela do sistema efetua
 * um refresh screen
 * 
 */
void show_memory_structs (){
	
	int i = 0;
    struct mmblock_d *B;	
	
	// Title.
	printf("Memory Block Information:\n\n");
	//printf("=========================\n");
	
	//Mostra os heap da lista.		
	while (i < MMBLOCK_COUNT_MAX) 
	{
        B = (void *) mmblockList[i];
		
		i++;
		
		if ( (void *) B != NULL )
		{
			//Validade.
		    if ( B->Used == 1 && B->Magic == 1234 ){
				
		        printf("Id={%d} Header={%x} userA={%x} Footer{%x}\n",
				    B->Id, B->Header, B->userArea, B->Footer );
			};
			//Nothing.
		};
		//Nothing.
    };
	
	
	// Aqui podemos aprentar informações sobre o heap.
	// como tamanho, espaço disponível, ponteiro, à que processo ele 
	// pertence.
	// mas estamos lidando a estrtutura de mmblock_d, que é especial e meio 
	// engessada.
	
	//More?!
	
// Done.
};


/*
 ***********************************************************************
 * init_heap:
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

int init_heap (){
	
	int i = 0;

    //Globals.	
	kernel_heap_start = (unsigned long) KERNEL_HEAP_START;  
    kernel_heap_end = (unsigned long) KERNEL_HEAP_END;  
	
	//Heap Pointer, Available heap and Counter.
	g_heap_pointer = (unsigned long) kernel_heap_start;    	
    g_available_heap = (unsigned long) (kernel_heap_end - kernel_heap_start);    	 
	heapCount = 0;      
	
	// #importante
	// Último heap pointer válido. 
	last_valid = (unsigned long) g_heap_pointer;
	last_size = 0;
	
	//Check Heap Pointer.
	if ( g_heap_pointer == 0 )
	{	
	    printf("init_heap fail: Heap pointer\n");
		goto fail;
	}
	
	//Check Heap Pointer overflow.
	if( g_heap_pointer > kernel_heap_end )
	{
        printf("init_heap fail: Heap Pointer Overflow\n");
		goto fail;
    }	
	
    //Heap Start.
	if( kernel_heap_start == 0 )
	{
	    printf("init_heap fail: HeapStart={%x}\n", kernel_heap_start );
	    goto fail;
	}
	
	//Heap End.
	if( kernel_heap_end == 0 )
	{
	    printf("init_heap fail: HeapEnd={%x}\n", kernel_heap_end );
	    goto fail;
	}
	
	//Check available heap.
	if( g_available_heap == 0 )
	{
	    //@todo: Tentar crescer o heap.
		
		printf("init_heap fail: Available heap\n");
		goto fail;
	}
	
	// Heap list:
	// Inicializa a lista de heaps.
	
	while ( i < HEAP_COUNT_MAX )
	{
        heapList[i] = (unsigned long) 0;
		i++;
    };
	
	//KernelHeap = (void*) x??;
	
	//More?!
	
// Done.
//done:

#ifdef MK_VERBOSE
    printf("Done\n");
#endif	
	
	return (int) 0;
	
    
	// Fail. 
	// Falha ao iniciar o heap do kernel.

fail:
    printf("init_heap: Fail\n");
	refresh_screen();
	
	/*
	// #debug
	printf("* Debug: %x %x %x %x \n", kernel_heap_start, 
	                                  kernel_heap_end,
									  kernel_stack_start,
									  kernel_stack_end);	
	refresh_screen();	 
    while(1){}		
	*/
    
	return (int) 1;
};


/*
 **************************************************
 * init_stack:
 *     Iniciar a gerência de Stack do kernel. 
 *     @todo Usar stackInit(). 
 */
 
int init_stack (){
	
    //Globals.
	//#bugbug
	
	kernel_stack_end = (unsigned long) KERNEL_STACK_END; 
	kernel_stack_start = (unsigned long) KERNEL_STACK_START; 
	
    //End.
	if ( kernel_stack_end == 0 )
	{
	    printf("init_stack fail: StackEnd={%x}\n", kernel_stack_end );
	    goto fail;
	};
	
	//Start.
	if ( kernel_stack_start == 0 )
	{
	    printf("init_stack fail: StackStart={%x}\n", kernel_stack_start );
	    goto fail;
	};
	
	//Nothing.
//done:

    return (int) 0;
fail:
    return (int) 1;
};


/*
 ************************************
 * memoryShowMemoryInfo:
 *     Show memory info.
 */
void memoryShowMemoryInfo (){
	
	unsigned long HeapTotal = ((kernel_heap_end - kernel_heap_start)/1024);
	unsigned long StackTotal = ((kernel_stack_start - kernel_stack_end)/1024);
	
	printf(" Memory info:\n");
	printf(" ============\n");
	
	//sizes
	printf(" BaseMemory     = (%d KB)\n", memorysizeBaseMemory );
	printf(" OtherMemory    = (%d KB)\n", memorysizeOtherMemory );
	printf(" ExtendedMemory = (%d KB)\n", memorysizeExtendedMemory );
	printf(" TotalMemory    = (%d KB)\n", memorysizeTotal );
	
	//system zone
	//printf("systemzoneStart  = 0x%x\n", systemzoneStart);
	//printf("systemzoneEnd    = 0x%x\n", systemzoneEnd);
	//printf("systemzoneSize   = 0x%x\n", systemzoneSize);

	//window zone.
	//printf("windowzoneStart  = 0x%x\n", windowzoneStart);
	//printf("windowzoneEnd    = 0x%x\n", windowzoneEnd);
	//printf("windowzoneSize   = 0x%x\n", windowzoneSize);
	
	
	// System type
	
	switch (g_mm_system_type){
		
		case stSmallSystem:
		    printf(" stSmallSystem={%d KB}\n", memorysizeTotal );
		    break;
			
		case stMediumSystem:
		    printf(" stMediumSystem={%d KB}\n", memorysizeTotal );
			break;
			
		case stLargeSystem:
		    printf(" stLargeSystem={%d KB}\n", memorysizeTotal );
			break;
			
		case stNull:
		default:
		    printf(" stNull={%d KB}\n", memorysizeTotal );
			break;
	};
	
	// ## code data bss ##
	
	extern unsigned long code_begin;
	extern unsigned long code_end;
	
	extern unsigned long data_begin;
	extern unsigned long data_end;
	
	extern unsigned long bss_begin;
	extern unsigned long bss_end;
	
	printf("\n");
	printf("code_begin={%x} code_end={%x} \n", &code_begin, &code_end );
	printf("data_begin={%x} data_end={%x} \n", &data_begin, &data_end );
	printf("bss_begin={%x}  bss_end={%x}\n", &bss_begin, &bss_end );
	
	
	//  ## heap e stack ##
	
	
    printf("\n[Kernel Heap and Stack info:]\n");
	
	printf("HEAP: [%x...%x] Total={%d KB} \n",
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
		
    printf("STACK: [%x...%x] Total={%d KB} \n", 
        kernel_stack_start, kernel_stack_end, StackTotal );
			
    printf("STACK: StartPhysicalAddress={%x} \n", kernel_stack_start_pa );
	
	
	    // Video info
	
	//printf("\nVideo: ");
	
	    //Video mode.
	    //printf("The video option is %x \n",g_video_mode);
	printf ("\n FrontbufferPA={%x} FrontbufferVA={%x} \n", 
	    g_frontbuffer_pa, g_frontbuffer_va );  
	
	printf ("\n BackbufferVA={%x} \n", g_backbuffer_va );
	
	//...
};


/*
 ******************************************
 * init_mm:
 *   Inicializa o memory manager.
 *    @todo: Usar mmInit().
 */
 
int init_mm (){
	
    int Status = 0;
	int i = 0;	
	
	
	// @todo: 
	// Inicializar algumas variáveis globais.
	// Chamar os construtores para inicializar o básico.
	

	// @todo: 
	// Clear BSS.
	// Criar mmClearBSS()
	
	//
	// Chamando uma rotina que cria e inicializa o heap do kernel manualmente.
	//
	
	//Heap.
	Status = (int) init_heap();
	if(Status != 0)
	{
	    printf("init_mm fail: Heap\n");
	    return (int) 1;
	};	
	
	//Stack.
	Status = (int) init_stack();
	if(Status != 0)
	{
	    printf("init_mm fail: Stack\n");
	    return (int) 1;
	};		
	
	
	// Zerar a lista.
	// Lista de blocos de memória dentro do heap do kernel.
	
	while ( i < MMBLOCK_COUNT_MAX )
	{
        mmblockList[i] = (unsigned long) 0;
		++i;
    };
	
	//Primeiro Bloco.
    //current_mmblock = (void *) NULL;
	
	
	//
	// MEMORY SIZES
	//
	
	// Get memory sizes via RTC. (KB)
	// base, other, extended.
	// RTC só consegue perceber 64MB de memória.
	
	memorysizeBaseMemory = (unsigned long) rtcGetBaseMemory();  
	memorysizeOtherMemory = (unsigned long) (1024 - memorysizeBaseMemory);
	memorysizeExtendedMemory = (unsigned long) rtcGetExtendedMemory(); 
    
	memorysizeTotal = (unsigned long) ( memorysizeBaseMemory + memorysizeOtherMemory + memorysizeExtendedMemory );
	
	
	// #IMPORTANTE 
	// Determinar o tipo de sistema de memória.
	//
	// small   pelo menos 32mb
	// medium  pelo menos 64mb
	// large   pelo menos 128mb
	
	
	//0MB
	if ( memorysizeTotal >= (0) )
	{
		g_mm_system_type = stNull;
	    
		// #atenção 
		// Nesse caso devemos prosseguir e testar as outras opções.		
	}	
	
	
	//32MB
	//(32*1024)
	if ( memorysizeTotal >= SMALLSYSTEM_SIZE_KB )   
	{
		g_mm_system_type = stSmallSystem;
	}
	
	
	//64MB
	//(64*1024)
	if ( memorysizeTotal >= MEDIUMSYSTEM_SIZE_KB )  
	{
		g_mm_system_type = stMediumSystem;
	}	
	
	
	//128MB
	//(128*1024)
	if ( memorysizeTotal >= LARGESYSTEM_SIZE_KB )  
	{
		g_mm_system_type = stLargeSystem;
	}		
	

	
	//inicializando o framepool (paged pool)
	
	initializeFramesAlloc();
	
	
	// Continua...

    return (int) Status;	
}; 




//
// Segue rotinas de GC.
// =====================================================
//

//limpa a camada /gramado
int gcGRAMADO (){
	
	//Ainda não implementado.
	return (int) 0;
};


/*
 gcEXECUTIVE:
 
    Limpa a camada /execve.
    
	Esse é o Garbage Collector, o trabalho dele é checar nas listas 
 de ponteiros de estrutura e encontrar estruturas sinalizadas para 
 serem liberadas. 
 
    Quando encontra uma estrutura sinalizada, libera os recurso da 
estrutura.
   
   --------

    Obs:
        #importante: 
        As estruturas poderão ser deletadas ou não.
  
    Obs: 
	    A área do cliente na estrutura mmblock deverá se preenchida com zero
        quando a estrutura estiver sinalizada como reutilizável.
        
	Obs:	
		O garbage collector é um serviço do kernel, e poderá ser 
	    chamado por interrupção. Pois utilitários de gerência de memória 
	    usarão recursos de gerência de memória oferecidos pelo kernel.
		
    Obs: 
	    A função gc() poderá ser chamada de tempos em tempos, do mesmo modo 
        que o dead thread collector.
		#todo: Resta encontrarmos quais são os momentos em que essas rotinas 
		são chamadas.
	   
    Obs: 
        #Importante:
		O GC deve efetuar apenas uma operação de liberação, mesmo que 
        haja muita coisa pra fazer, pois não queremos que ele use 
		muito tempo de processamento prejudicando os outros processos.
		Pois bem, ele efetua apenas uma operação de limpeza e sai sem erro.
		Se não encontrar nada pra fazer, também sai sem erro.
		
		@todo: Cria os 'for's para as outras listas.
		@todo: Criar as rotinas de limpeza para as outras listas.
		 
	
	#### #todo: #### 
	
	#importante:
	+Checar as etruturas de mmblock e liberar as estruturas marcadas como Free=1.
	 ?? Para isso deve haver um array mmblockList[].
	
	+Checar as estruturas de janela e liberar as estiverem marcadas 
	 como used=216 e magic=4321.

	*Importante:
	Essa rotina deve limpar alocações de memória e não estruturas de 
	objetos de outros tipos.
	+O módulo de gerência de recursos gráficos que limpe suas listas.
	+O módulo de gerência de processos que limpe suas listas.
    +O módulo de gerência de threads que limpe suas listas.
 */
int gcEXECUTIVE (){
	
	int i;
	struct mmblock_d *b;  //memory block.
	struct heap_d *h;     //heap.
	//...
	
	//Obs: 
	// Importante: Cada lista contêm um tipo de estrutura.
	// Importante: Limparemos somente as listas que pertencem ao módulo /ram
	
	
	//#importante:
	//mmblock_d é a estrutura usada pelo malloc para organizar as alocações 
	//dentro de um heap. 
	//Essa estrutura será sinalizada com Free=1 e precisa liberar a área do cliente.
	
	//mmblockList[]
	//#importante: Nessa lista tem ponteiros para uma estrutura especial,
	//usada pela malloc para organizar os blocos de memória que serão utilizados 
	//para alocação dinâmica.
	for ( i=0; i<MMBLOCK_COUNT_MAX; i++ )
	{
	    b = (void *) mmblockList[i];
		
		//ponteiro válido.
	    if( (void *) b != NULL )
		{
			//sinalizado para o GC.
			if( b->Used == 216 && b->Magic == 4321 && b->Free == 1 )
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
		
		//ponteiro válido.
	    if( (void *) h != NULL )
		{
			//sinalizado para o GC.
			if( h->Used == 216 && h->Magic == 4321 )
			{
				goto clear_heap;
			}
		}
	};
	
	//
	// #### #importante ####
	// @todo: Cria os 'for's para as outras listas.
	// ex: session, window station, desktop, window etc ...

	
    goto done;
	
	//
	// Segue operações de limpeza em estruturas de tipos diferentes.
	// Devemos limpar e sairmos em seguida.
	//
	
	//Nothing
	
clear_mmblock:	
    
	if ( (void *) b != NULL )
    {
		//Checar se a área alocada está dentro dos limites.
	    //O inicio da área mais o tamanho dela tem que coincidir 
		//com o footer.
		if ( (b->userArea + b->userareaSize) != b->Footer )
		{
			//#debug
			//printf("gc fail: User Area Size");
			//goto fail;
			
			return (int) 1;
		
		}else{
			
	        //preenche com zeros a área do cliente.
			bzero ( (char *) b->userArea, (int) b->userareaSize );
		
		};
		
        //Nothing.		
	};
	goto done;
	//Nothing.
	
clear_heap:

    if ( (void *) h != NULL )
	{
		// ?? O que fazer aqui ??
		
		//Limparemos mas não deletaremos.
		//h->Used  = 1;
		//h->Magic = 1234;
		
		//#todo: 
		//Por enquanto vamos desabilitar a estrutura cancelada 
		//pelo sistema.
		if ( h->Used == 216 && h->Magic == 4321 )
		{
			h->Used = 0;
			h->Magic = 0;
			h = NULL;
		}
		
		//lista encadeada de blocos que formavam o heap.
		//podemos apenas sinalizar todos os mmblocks dessa lista e depois o GC acaba com eles.
		//para isso precisamos de um 'for'.
		//h->mmblockListHead = NULL;		
	};
	goto done;
	//Nothing.

	//
	// @todo: Criar as rotinas de limpeza para as outras listas.
	//

fail:
    refresh_screen();
	return (int) 1;
done:	
	return (int) 0;	
};


//limpa a camada /microkernel
int gcMICROKERNEL (){
	
	return (int) 0;
};


//limpa a camada /hal
int gcHAL (){
	
	return (int) 0;
};


/*
 ******************************
 * gc:
 *     Garbage Collector.     
 *	   
 * Call all Garbage Collections rotines.
 * Clear all main layers.
 *	
 * +GRAMADO 
 * +EXECUTIVE 
 * +MICROKERNEL 
 * +HAL
 *
 * #importante:
 * Em duas condições as estruturas poderão ser destruidas ou reaproveitadas: 
 * +Quando a estrutura usada pelo malloc estiver sinalizada com Free=1 e 
 * +quando as outras estruturas estiverem com a flag igual a used=216 e 
 * magic=4321.
 * obs: Outros tratamentos de flags serão introduzidos com o tempo,
 * #todo: criaremos um enum de flags para serem utilizadas.
 *
 * #importante:
 * Para não perdermos muito tempo com a rotina de limpeza devemos limpar
 * apenas uma estrutura e saírmos.
 * #importante: ?? Quando essa rotina é chamada, pois ela só deve ser 
 * chamada de tempos em tempos, provavelmente usando a flag 'extra' que 
 * está em ts.c.
 * #por enquanto ainda não chamamos isso, apenas temos o serviço para 
 * utilitários usarem.
 */
 
int gc (){
	
    int Status;
	
//clearGramadoLayer:

    Status = (int) gcGRAMADO ();
    if ( Status == 1 )
	{
		//#debug
		//printf("gc: clearGramadoLayer:\n");
		//goto fail;
		
		return (int) 1;
	}
	
//clearExecutiveLayer:

    Status = (int) gcEXECUTIVE ();
    if ( Status == 1 )
	{
		//#debug
		//printf("gc: clearExecutiveLayer:\n");
		//goto fail;
		
		return (int) 1;
	}
	
//clearMicrokernelLayer:

    Status = (int) gcMICROKERNEL ();
    if ( Status == 1 )
	{
		//#debug
		//printf("gc: clearMicrokernelLayer:\n");
		//goto fail;
		
		return (int) 1;
	}
	
//clearHalLayer:

    Status = (int) gcHAL ();
    if ( Status == 1 )
	{
		//#debug
		//printf("gc: clearHalLayer:\n");
		//goto fail;
	    
		return (int) 1;
	}

//done:
    return (int) 0;	
};


/*
int mmInit()
{
    //...	
}
*/


//
// End.
//
