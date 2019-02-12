/*
 * File: stdlib.h 
 *
 * Descrição:
 *     Parte da libC C99 para usermode 32bit.
 * Versão: 1.0, 2016 - Created.
 */

 
/*
   O que deve conter:
   
    atof string para float
    atoi	string para integer
    atol	string para long integer
    strtod	string para double
    strtol	string para long int
    strtoul	string para unsigned long int

	Geração de seqüência pseudo-aleatória
    rand	gera um número inteiro pseudo aleatório
    srand	seleciona a semente do gerador pseudo aleatório
    
	Alocação e liberação de memória
    malloc
    calloc
    realloc	aloca memória do "heap"
    free	libera memória de volta para o "heap"

	Controle de processos
    abort	força o término da execução
    atexit	registra uma função "callback" para saída do programa
    exit	termina a execução do programa
    getenv	obtém uma variável de ambiente
    system	executa um comando externo

	Ordenamento e procura
    bsearch	procura binária em "array"
    qsort	ordena "array" segundo algoritmo Quick Sort

	Matemática
    abs
    labs	valor absoluto
    div
    ldiv	divisão inteira
   
*/   


#ifndef _STDLIB_H
#define _STDLIB_H 1
  
//A rotina terminou normalmente.
#define EXIT_SUCCESS  0    

//A rotina terminou de maneira anormal.
#define EXIT_FAILURE  1

#define RAND_MAX  32767 

void *stdlib_system_call ( unsigned long ax, 
                           unsigned long bx, 
                           unsigned long cx, 
                           unsigned long dx );

void stdlib_die (char *str);

int atoi (const char *str);	


void itoa (int n, char s[]);
		   

char *getenv (const char *name);


/*
 * malloc:
 *    Allocates the requested memory and returns a pointer to it. */

void *malloc (size_t size);

void *calloc (size_t count, size_t size);

void *zmalloc ( size_t size);

void *realloc ( void *start, size_t newsize );


/*
 * xmalloc:
 *     exit se malloc não der certo. */

void *xmalloc ( int size);



/*
 * free:
 *     Libera a memória alocada por malloc. */

void free (void *ptr);

//Returns a pseudo-random number in the range of 0 to RAND_MAX.
int rand (void);

//Alimenta a função rand.
void srand (unsigned int seed);


//@todo: talvez essa função esteja declara erradamente em systemcall.
//Obs: Essa rotina existe na API e funciona. Se ela faz parte da lib C
// então ela deve sair de lá vir pra cá.
int system (const char *command);





//=================================




double strtod (const char *str, char **endptr);
float strtof(const char *str, char **endptr);
long double strtold(const char *str, char **endptr);
double atof(const char *str);


//=================================


int abs( int j);


//rt support
//pegando informações sobre o heap usado pela biblioteca C99 em user mode.
unsigned long rtGetHeapStart();
unsigned long rtGetHeapEnd();
unsigned long rtGetHeapPointer();
unsigned long rtGetAvailableHeap();
//...


/*
 * libcInitRT:
 *     Inicializa o gerenciamento em user mode de memória virtual
 * para a biblioteca libC99.
 * Obs: *IMPORTANTE: Essa rotina deve ser chamada entes que a biblioteca C 
 * seja usada.
 * Obs: Pode haver uma chamada à ela em crt0.s por exemplo.
 */
int libcInitRT();


#endif  /*stdlib.h*/

//
// End.
//
