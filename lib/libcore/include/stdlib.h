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


#include <stddef.h>



#ifdef	_BSD_SIZE_T_
typedef	_BSD_SIZE_T_	size_t;
#undef	_BSD_SIZE_T_
#endif

#if defined(_BSD_WCHAR_T_) && !defined(__cplusplus)
typedef	_BSD_WCHAR_T_	wchar_t;
#undef	_BSD_WCHAR_T_
#endif

typedef struct {
	int quot;		/* quotient */
	int rem;		/* remainder */
} div_t;

typedef struct {
	long quot;		/* quotient */
	long rem;		/* remainder */
} ldiv_t;


#if !defined(_ANSI_SOURCE) && \
    (defined(_ISOC99_SOURCE) || (__STDC_VERSION__ - 0) >= 199901L || \
     (__cplusplus - 0) >= 201103L || defined(_NETBSD_SOURCE))
typedef struct {
	/* LONGLONG */
	long long int quot;	/* quotient */
	/* LONGLONG */
	long long int rem;	/* remainder */
} lldiv_t;
#endif

#if defined(_NETBSD_SOURCE)
typedef struct {
	quad_t quot;		/* quotient */
	quad_t rem;		    /* remainder */
} qdiv_t;
#endif


#define	EXIT_FAILURE	1
#define	EXIT_SUCCESS	0


//bsd-like
//#define	RAND_MAX	0x7fffffff

#define RAND_MAX  32767 


//bsd stuff
//extern size_t __mb_cur_max;
//#define	MB_CUR_MAX	__mb_cur_max


void *stdlib_system_call ( unsigned long ax, 
                           unsigned long bx, 
                           unsigned long cx, 
                           unsigned long dx );




const char	*getprogname(void);
void setprogname(const char *progname);

int unlockpt(int fd);

int getpt(void);

int grantpt(int fd);

int posix_openpt (int flags);




//The ptsname() function returns the name of the slave pseudoterminal
//       device corresponding to the master referred to by fd.
char *ptsname (int fd);


// The ptsname_r() function is the reentrant equivalent of ptsname().
// It returns the name of the slave pseudoterminal device as a null-
// terminated string in the buffer pointed to by buf.  The buflen
// argument specifies the number of bytes available in buf.
int ptsname_r (int fd, char *buf, size_t buflen);



int mkostemps(char *template, int suffixlen, int flags);

int mkstemps(char *template, int suffixlen);

int mkostemp(char *template, int flags);

int mkstemp(char *template);

long labs (long j);



void stdlib_die (char *str);

int atoi (const char *str);

void itoa (int n, char s[]);





char *getenv (const char *name);


//setenv - change or add an environment variable
//POSIX.1-2001, POSIX.1-2008, 4.3BSD.
// RETURN VALUE:
// The setenv() function returns zero on success, or -1 on error, with
// errno set to indicate the cause of the error.
int setenv (const char *name, const char *value, int overwrite);


//POSIX.1-2001, POSIX.1-2008, 4.3BSD.
// RETURN VALUE:
// The unsetenv() function returns zero on success, or -1 on error, with
// errno set to indicate the cause of the error.
int unsetenv (const char *name);


// mktemp - make a unique temporary filename
//4.3BSD, POSIX.1-2001.  POSIX.1-2008 removes the specification of mktemp().
char *mktemp (char *template);


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


long
strtol(const char *nptr, char **endptr, int base);
	
unsigned long
strtoul( const char *nptr, char **endptr, int base);

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
