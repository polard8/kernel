/*
 * File: stdlib.c
 *
 * Descrição:
 *     Stdlib. Parte da lib C do kernel.
 *
 * Versão 1.0, 2015.
 */

 
#include <kernel.h>


static int randseed = 1234;


//Alimenta a função rand.
//void srand(unsigned int seed)
//{};



/*
 * rand: Gera um número inteiro randômico.
 */
int rand(void){
	return (int) ( randseed = randseed * 1234 + 5 );
};


/*
 * malloc:
 *     Standard malloc function.
 */
void *malloc(size_t size)
{	
    void *h;		
	unsigned long s = ( unsigned long) size;
	
	//s = (s ? s : 1);	/* if s == 0, s = 1 */
	
	if( s < 0 ){
		return NULL;
	};
	
	if( s == 0 ){
	    s=1;
	};

    //Alocar memória no heap do kernel.
	//if(current_process == 0){
	    h = (void *) AllocateHeap(s);	
	//};
	
	//Alocar memória para um processo.
	//if(current_process != 0)
	//{
	    //Usar o heap do desktop atual.
		//h = (void *) ProcessAllocateHeap( _crtheap, s);
    //};
	
	
	
	
	if( (void*) h == NULL){
	    //printf("malloc: falha ao alocar memoria!\n");
		//refresh_screen();
		return NULL;
	};
	
	/*
	if((void*) h < KERNEL_HEAP_START){
	    printf("malloc: falha ao alocar memoria! Limits\n");
		refresh_screen();
		return NULL;		
	};
	*/
	
done:
    return (void*) h; 
};


/*
 * free:
 * The free() function frees the memory space pointed to by ptr, 
 * which must have been returned by a previous call 
 * to malloc(), calloc() or realloc(). 
 * Otherwise, or if free(ptr) has already been called before, 
 * undefined behavior occurs. 
 * If ptr is NULL, no operation is performed.
 *
 */
void free(void *ptr)
{	
    int Index;
    struct mmblock_d *Block;		
    struct mmblock_d *Anterior;
	
	//
	// @todo:
	// Se o argumento está correto, o argumento representa o início
	// da área de cliente, ou seja, se subtrairmos o tamanho do header
	// encontraremos o incício do bloco de memória.
	// Se o header for de tamanho padrão isso facilita encontrar
	// o início da estrutura. MMBLOCK_HEADER_SIZE
	//
	
	//test:
	//Calculando o início do header,dado o argumento, que é
	//o início da área de cliente.
	unsigned long HeaderBase;
	HeaderBase = (unsigned long) ( (void*) ptr - MMBLOCK_HEADER_SIZE);
	
	Block = (void*) HeaderBase;
	if( (void*) Block == NULL )
	{
		return;  //fail
	}
	else
	{
		//Confirma se é um bloco válido.
		if( Block->Magic != 1234 ){
			return;
		}

        //Limpa a lista.
		if( Block->Id > 0 && Block->Id < MMBLOCK_COUNT_MAX ){
		    mmblockList[Block->Id] = 0;	
		}
		
		//Conecta o bloco anterior ao próximo.
		if( (void*) Block->Prev != NULL )
		{
			Anterior = (void*) Block->Prev;
			Anterior->Next =(void*) Block->Next;
		}	
		
        //Apaga tudo.
		//Block->Header = 0;
		Block->headerSize = 0;
		Block->Id  = 0;
		Block->Used  = 0;		          
	    Block->Magic = 0;         
        Block->Free  = 0;
        Block->requestSize = 0;
        Block->unusedBytes = 0;
		Block->userareaSize = 0;
		Block->userArea = 0;
		Block->Footer = 0;
		Block->processId = 0;
		Block->process = NULL;
		Block->Next = NULL;
		Block->Prev = NULL;
		Block->Header = 0; //Volta apagar o Header.
		
		//Nothing.	
	}
	//Nothing.
done:	
	return;
};


/*
 * calloc: alloca e preenche com zero.
 * @todo:
 */
/*
void *calloc (size_t count, size_t size)
{
    size_t s = count * size;
    
	void *value = malloc (s);
    
	if (value != 0)
    {    
	    memset (value, 0, s);
	};
  return value;
};

*/

//
// End.
//
