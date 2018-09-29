/*
 * File: stdlib.h 
 *
 * Descrição:
 *     Parte da libC do kernel.
 *
 */
 
 
 /*
 atof 	string para float
 atoi 	string para integer
 atol 	string para long integer
 strtod 	string para double
 strtol 	string para long int
 strtoul 	string para unsigned long int

 Geração de seqüência pseudo-aleatória
rand 	gera um número inteiro pseudo aleatório
srand 	seleciona a semente do gerador pseudo aleatório

Alocação e liberação de memória
malloc
calloc
realloc 	aloca memória do "heap"
free 	libera memória de volta para o "heap"

Controle de processos
abort 	força o término da execução
atexit 	registra uma função "callback" para saída do programa
exit 	termina a execução do programa
getenv 	obtém uma variável de ambiente
system 	executa um comando externo

Ordenamento e procura
bsearch 	procura binária em "array"
qsort 	ordena "array" segundo algoritmo Quick Sort

Matemática

valor absoluto
abs
labs 	

divisão inteira
div
ldiv 	
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
// tipos de retorno das funções div e ldiv.

typedef struct div_d div_t;
struct div_d 
{
	int quot;
	int rem;
};

typedef struct ldiv_d ldiv_t;
struct ldiv_d 
{
	long quot;
	long rem;
};
*/


#define kmalloc malloc
#define kfree free


/*
 * malloc:
 *    Allocates the requested memory and returns a pointer to it.
 */
void *malloc (size_t size);


/*
 * free:
 *     Libera a memória alocada por malloc.
 */
void free (void *ptr);
//void free2(void *ptr);


//Returns a pseudo-random number in the range of 0 to RAND_MAX.
int rand (void);


//Alimenta a função rand.
//void srand(unsigned int seed);


//@todo: talvez essa função esteja declara erradamente em systemcall.
//int system(const char *string);

//
//fim.
//
