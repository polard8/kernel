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
 * rand: 
 *     Gera um número inteiro randômico.
 */
int rand (void){
	
	return (int) ( randseed = randseed * 1234 + 5 );
};


/*
 * malloc:
 *     Standard malloc function.
 */
void *malloc (size_t size){
	
    void *h;		
	unsigned long s = ( unsigned long) size;
	
	//s = (s ? s : 1);	/* if s == 0, s = 1 */
	
	if ( s < 0 ){
		return NULL;
	};
	
	if ( s == 0 ){
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
	
	
	
	
	if ( (void *) h == NULL )
	{
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
	
//done:

    return (void *) h; 
};


/*
 * free:
 *
 * >> #importante:
 * >> Tradicionalmente essa função só libera o que foi alocado pela 
 * última chamada de malloc. Mas estamos tentando algo diferente.
 *
 * The free() function frees the memory space pointed to by ptr, 
 * which must have been returned by a previous call 
 * to malloc(), calloc() or realloc(). 
 * Otherwise, or if free(ptr) has already been called before, 
 * undefined behavior occurs. 
 * >> If ptr is NULL, no operation is performed.
 *
 * Importante:
 *     uma estratégia seria apenas sinalizarmos na estrutura que 
 * desejamos que o GC libere os recurso. Em seguida devemos sinalizar 
 * no mmblock que libere o bloco para outras alocações. 
 *
 */
void free (void *ptr){
	
    int Index;
    struct mmblock_d *Block;		
    /*struct mmblock_d *Anterior;*/
	
	
	//>> If ptr is NULL, no operation is performed.
	if ( (void *) ptr == NULL )
	{
		//#debug
		//printf("free fail: null pointer\n");
		//goto fail;
		
		return;
	}
	
    
    // ptr:
	//     Não temos condição de saber que tipo de dado estava alocado
    // na área de cliente. O que nos resta é sinalizarmos na estrutura
    // mmblock_d que ela não está mais em uso, deixando para o GC a tarefa 
    // de desfazer a estrutura mmblock_d ou deixar a estrutura intacta e 
    // sinalizada que está livre para uso. O alocador de memória poderá 
    // reaproveitar essa estrutura liberada se o tamanho for o bastante para 
    // a próxima alocação desejada.	
	
	// @todo:
	// Se o argumento está correto, o argumento representa o início da 
	// área de cliente, ou seja, se subtraírmos o tamanho do header
	// encontraremos o incício do bloco de memória.
	// Se o header for de tamanho padrão isso facilita encontrar
	// o início da estrutura. MMBLOCK_HEADER_SIZE
	
	// #test:
	// Calculando o início do header, dado o argumento, que é o início da 
	// área de cliente.
    // Ou seja, estamos calculando o endereço do início da estrutura.
	// Se a esrtutura for válida então podemos liberar a memória.
	
	unsigned long UserAreaStart = (unsigned long) ptr; 
	
	Block = (void *) ( UserAreaStart - MMBLOCK_HEADER_SIZE );
	
	//Se o início da estrutura de mmblock_d for um valor inválido.
	
	if ( (void *) Block == NULL )
	{
		//#debug
		//printf("free fail: struct pointer\n");
		//goto fail;
		
		return;
				
	}else{
		
		if ( Block->Used != 1 || Block->Magic != 1234 )
		{
			//#debug
			//printf("free fail: Used\n");
		    //goto fail;
              
            return;			  
		};

		if ( Block->userArea != UserAreaStart )
		{
			//#debug
			//printf("free fail: userArea address\n");
			//goto fail;

            return;			
		};	
		
		//#importante:
		//Liberando o bloco para uso futuro.
		if ( Block->Free == 0 )
		{
			//#importante
			//sinalizando para o GC.
			//Fazendo a mesma coisa que nas outras estruturas;
			Block->Used = 216;
			Block->Magic = 4321;
		    Block->Free = 1;   
			return;
			
			//goto done;	
		} 
		
		//Se estamos aqui é porque algo deu errado.
        //goto fail;
	};
	//Nothing.
//fail:	
    die ();
//done:	
	//return;
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
