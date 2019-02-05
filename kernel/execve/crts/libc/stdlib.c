/*
 * File: execve/crts/libc/stdlib.c
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



/* rand: 
 * Gera um número inteiro randômico. */

int rand (void){
	
	return (int) ( randseed = randseed * 1234 + 5 );
}


/* 
 *****************************************
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

	h = (void *) heapAllocateMemory (s);
	
	if ( (void *) h == NULL ){
		return NULL;
	}
	
    return (void *) h; 
}


/*
 ************************************
 * free:
 *
 * >> #importante:
 * >> Tradicionalmente essa função só libera o que foi alocado pela última 
 * chamada de malloc. Mas estamos tentando algo diferente.
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
	
	if ( (void *) ptr == NULL )
	    return;

	//memory.c
    FreeHeap (ptr);	
	
	//return;
}


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
