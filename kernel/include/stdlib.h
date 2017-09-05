/*
 * Arquivo: stdlib.h 
 *
 * Descrição:
 *     Parte da libC do kernel.
 *
 */

 
/* 
 * A rotina terminou normalmente. 
 */                                                                                
#define	EXIT_SUCCESS  0    

 
/* 
 * A rotina terminou de maneira anormal. 
 */                                                                        
#define	EXIT_FAILURE  1                                    
            
			
// Números pseudoaleatórios   
#define RAND_MAX  32767    //0x7FFF


/*
 * malloc:
 *    Allocates the requested memory and returns a pointer to it.
 *
 *
 */
void *malloc(size_t size);


/*
 * free:
 *     Libera a memória alocada por malloc.
 *
 */
void free(void *ptr);
//void free2(void *ptr);

//Returns a pseudo-random number in the range of 0 to RAND_MAX.
int rand(void);

//Alimenta a função rand.
//void srand(unsigned int seed);


//@todo: talvez essa função esteja declara erradamente em systemcall.
//int system(const char *string);

//
//fim.
//
