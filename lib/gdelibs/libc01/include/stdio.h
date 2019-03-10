/*
 * File: stdio.h
 *
 * Descrição:
 *     Parte da biblioteca C para API 32bit.
 *     c99 - ISO/IEC 9899:1999
 *
 * @todo: 
 *     Usar padrão C e colocar em outro arquivo o que não for daqui.
 *
 * Versão 1.0, 2016 - Created.
 */


#ifndef __STDIO_H__
#define __STDIO_H__
 
#include <stddef.h>
#include <stdarg.h> 

#ifdef	_BSD_SIZE_T_
typedef	_BSD_SIZE_T_	size_t;
#undef	_BSD_SIZE_T_
#endif
#ifdef	_BSD_SSIZE_T_
typedef	_BSD_SSIZE_T_	ssize_t;
#undef	_BSD_SSIZE_T_
#endif

#if defined(_POSIX_C_SOURCE)
#ifndef __VA_LIST_DECLARED
typedef __va_list va_list;
#define __VA_LIST_DECLARED
#endif
#endif



#define	__SLBF	0x0001		/* line buffered */
#define	__SNBF	0x0002		/* unbuffered */
#define	__SRD	0x0004		/* OK to read */
#define	__SWR	0x0008		/* OK to write */
	/* RD and WR are never simultaneously asserted */
#define	__SRW	0x0010		/* open for reading & writing */
#define	__SEOF	0x0020		/* found EOF */
#define	__SERR	0x0040		/* found error */
#define	__SMBF	0x0080		/* _buf is from malloc */
#define	__SAPP	0x0100		/* fdopen()ed in append mode */
#define	__SSTR	0x0200		/* this is an sprintf/snprintf string */
#define	__SOPT	0x0400		/* do fseek() optimization */
#define	__SNPT	0x0800		/* do not do fseek() optimization */
#define	__SOFF	0x1000		/* set iff _offset is in fact correct */
#define	__SMOD	0x2000		/* true => fgetln modified _p text */
#define	__SALC	0x4000		/* allocate string space dynamically */




typedef char *stdio_va_list; 

 
#ifndef NULL
#define NULL ((void *)0)
#endif

 

/*  
"flags" bits definitions
*/


/* Flags for the iobuf structure  */
#define _IOREAD  1
#define _IOWRT	 2
#define _IORW	 0x0080

#define	STDIN_FILENO  0
#define	STDOUT_FILENO 1
#define	STDERR_FILENO 2


/*
//bsd-like
//#todo: use this one.
#define	_IOFBF	0		// setvbuf should set fully buffered 
#define	_IOLBF	1		// setvbuf should set line buffered 
#define	_IONBF	2		// setvbuf should set unbuffered 
*/
#define _IOFBF    0x0000  /* full buffered */
#define _IOLBF    0x0040  /* line buffered */
#define _IONBF    0x0004  /* not buffered */

/*
 * The buffer size as used by setbuf such that it is equivalent to
 * (void) setvbuf(fileSetBuffer, caBuffer, _IOFBF, BUFSIZ).
 */
#define BUFSIZ  1024

/* Returned by various functions on end of file condition or error. */
#ifndef EOF
#define EOF (-1)
#endif


/*
 * #bsd-like
 * FOPEN_MAX is a minimum maximum, and is the number of streams that
 * stdio can provide without attempting to allocate further resources
 * (which could fail).  Do not use this for anything.
 */
				                 /* must be == _POSIX_STREAM_MAX <limits.h> */
//#define	FOPEN_MAX	20	        /* must be <= OPEN_MAX <sys/syslimits.h> */
//#define	FILENAME_MAX	1024	/* must be <= PATH_MAX <sys/syslimits.h> */


#define FOPEN_MAX	(32)

#ifndef FILENAME_MAX
#define	FILENAME_MAX	(260)
#endif

#define NUMBER_OF_FILES (32)

/* System V/ANSI C; this is the wrong way to do this, do *not* use these. */
#if defined(_XOPEN_SOURCE) || defined(_NETBSD_SOURCE)
#define	P_tmpdir	"/var/tmp/"
#endif
#define	L_tmpnam	1024	/* XXX must be == PATH_MAX */


//bsd-like
/* Always ensure that this is consistent with <limits.h> */
//#ifndef TMP_MAX
//#define TMP_MAX			308915776	/* Legacy */
//#endif

#define TMP_MAX	32767


#define _IOMYBUF  0x0008  /* stdio malloc()'d buffer */
#define _IOEOF    0x0010  /* EOF reached on read */
#define _IOERR    0x0020  /* I/O error from system */
#define _IOSTRG   0x0040  /* Strange or no file descriptor */

#ifdef __POSIX__
#define	_IOAPPEND 0x0200
#endif


/* Always ensure that these are consistent with <fcntl.h> and <unistd.h>! */

/* It moves file pointer position to the beginning of the file. */
#ifndef SEEK_SET
#define	SEEK_SET	0	/* set file offset to offset */
#endif

/* It moves file pointer position to given location. */
#ifndef SEEK_CUR
#define	SEEK_CUR	1	/* set file offset to current plus offset */
#endif

/*  It moves file pointer position to the end of file. */
#ifndef SEEK_END
#define	SEEK_END	2	/* set file offset to EOF plus offset */
#endif




/*
 **********************************************************************
 * FILE:
 *     Estrutura padrão para arquivos.    
 *     #bugbug: os arquivos com esse tipo de estrutura serao
 *              gerenciados pelo kernel, para ser compativel com unix-like
 *              e para facilitar a comunicaçao entre processos.
 */
typedef struct _iobuf FILE; 
struct _iobuf 
{
	char *_ptr;      // Current position of file pointer (absolute address).
	int   _cnt;      // number of available characters in buffer 
	char *_base;     // Pointer to the base of the file. the buffer
	int   _flag;     // Flags (see FileFlags). the state of the stream
	int   _file;     // UNIX System file descriptor
	int   _charbuf;   
	int   _bufsiz;
	char *_tmpfname;
};

FILE *stdin;
FILE *stdout;
FILE *stderr;

//listando os arquivos da biblioteca.
unsigned long Streams[NUMBER_OF_FILES];

//#define	fileno(stream)		((stream)->_fd)
//#define L_ctermid 255	/* required by POSIX */
//#define L_cuserid 255	/* required by POSIX */


/*
 // outra lista.
 // lista tradicional

  // _ptr, _cnt, _base,  _flag, _file, _charbuf, _bufsiz  
  // stdin (_iob[0]) 
  // stdout (_iob[1])  
  // stderr (_iob[3]) 
 
char buf_stdin[BUFSIZ];
FILE _iob[NUMBER_OF_FILES] = {
	{ buf_stdin, 0, buf_stdin, _IOREAD | _IOYOURBUF, 0, 0, _INTERNAL_BUFSIZ },
	{ NULL, 0, NULL, _IOWRT, 1, 0, 0 },
	{ NULL, 0, NULL, _IOWRT, 2, 0, 0 },
};

#define stdin  (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

*/


 
 
//
// Posição virtual da memória de vídeo.
//  VA=0x800000 = PA=0x000B8000.
//
#define SCREEN_START 0x800000 
#define ScreenStart SCREEN_START

#define COLUMNS 80
#define SCREEN_WIDTH COLUMNS

#define ROWS 25
#define SCREEN_HEIGHT ROWS

#define SCREEN_WIDTH COLUMNS
#define HEIGHT ROWS

//limite máximo. provisório.
#define SCREEN_MAX_HEIGHT 256  //linhas.
#define SCREEN_MAX_WIDTH  256  //colunas.

#define REVERSE_ATTRIB 0x70

#define PAD_RIGHT 1
#define PAD_ZERO 2

#define PRINT_BUF_LEN 12

#define KEY_RETURN   13    //@todo: Pertence ao teclado.



//
// Obs: O tipo da variável aqui é provisório. (UL).
//

//cursor
unsigned long g_cursor_x;
unsigned long g_cursor_y;

//char.
unsigned long g_char_attrib;

//columns and rows
//@todo: Esse precisa ser inicializado
//Obs: Se essas variáveis forem 0, 
// as rotinas de stdio usarão os valores default.
//COLUMNS e ROWS.
unsigned long g_columns;
unsigned long g_rows;

int g_using_gui; //modo gráfico?







//===========================================

//
// Prompt support.
//

// Obs: Esses buffers são usados pela libe como arquivo.
// #importante: 
// Qual o tamanho máximo que eu posso usar nesse buffer.
// Qual é o padrão de tamanho usado para o fluxo padrão.
//

//Buffer para o buffer usado para input de comandos.
//prompt[] 

#define PROMPT_MAX_DEFAULT BUFSIZ //1024




// Normalmente quem cria o fluxo padrão é a rotina 
// que cria o processo.

// Fluxo padrão.
//O alocador pode ignorar isso e criar outros buffers.
char prompt[PROMPT_MAX_DEFAULT];      //stdin
char prompt_out[PROMPT_MAX_DEFAULT];  //stdout 
char prompt_err[PROMPT_MAX_DEFAULT];  //stderr 
   
int prompt_pos;
int prompt_max;
int prompt_status;

//char prompt_text[] = "$> ";

//...

//===========================================
// ## Protótipos do padrão C. ##
//===========================================


int fileno ( FILE *stream );
 
/*
 * File Operations
 */ 
 
FILE *fopen( const char *filename, const char *mode ); 
int fflush( FILE *stream ); 
int fclose(FILE *stream); 
//#define fileno(p)   ((p)->fd)
 
 
/*
 * Normal output.
 */ 
 
int puts(const char *str); 

static int prints(char **out, const char *string, int width, int pad);
static int printi(char **out, int i, int b, int sg, int width, int pad, int letbase);
static int print(char **out, int *varg);
static void printchar(char **str, int c);
void outbyte(int c);
void _outbyte(int c);
 
 
/*
 * Formatted Output
 */ 
 
int fprintf(FILE *stream, const char *format, ...); 







//#testes
//ok isso funcionou.
int vfprintf ( FILE *stream, const char *format, stdio_va_list argptr );
int stdout_printf (const char *format, ...);
int stderr_printf (const char *format, ...);

void perror(const char *str);


int printf(const char *format, ...); 

//tradicional, incompleta; não funciona,
//estamos implementando uma printf padrão tradicional.
int printf2(const char *format, ...); 

int printf3(const char *fmt, ...);

int sprintf(char *out, const char *format, ...);


//#test 
//?? coisa do c++ 
void rewind ( FILE * stream );

/*
 * Normal input.
 */
 
//Usado por interpretadores de comando.
//Recebem input e colocam em prompt[] 
unsigned long input(unsigned long ch);


/*
 * Formatted Input
 */
int scanf ( const char *fmt, ... );


//(since C99)	
//int fscanf( FILE *restrict stream, const char *restrict format, ... );
	
// #bugbug
// Essa funções está implementada em fscanf/fscanf.c
int fscanf(FILE *stream, const char *format, ... ); 

int sscanf(const char *str, const char *format, ...);
 
/*
 * Character Input and Output Functions
 */
 
int fgetc( FILE *stream );;
#define getc fgetc
int ungetc( int c, FILE *stream );

long ftell (FILE *stream);

int fputc(int ch, FILE *stream);
char *gets(char *s);
int getchar(void);
int putchar(int ch);


//#define getc(p)     fgetc(p)
#define putc(x, p)  fputc(x, p)
//#define getchar()   getc(stdin)
//#define putchar(x)  putc((x), stdout)


size_t fread(void *ptr, size_t size, size_t n, FILE *fp);
size_t fwrite(const void *ptr, size_t size, size_t n, FILE *fp);

/*
 * Direct Input and Output Functions
 */
 
 
 
/*
 * File Positioning Functions
 */
int fseek(FILE *stream, long offset, int whence);



/*
 * Error Functions
 */
 
int feof( FILE *stream );
int ferror( FILE *stream ); 
//#define feof(p)	  (((p)->_flags & _IOEOF) != 0)
//#define ferror(p)	  (((p)->_flags & _IOERR) != 0)
//#define clearerr(p) ((p)->_flags &= ~(_IOERR|_IOEOF))
//#define feof(p)     (((p)->flag & _EOF) != 0)
//#define ferror(p)   (((p)->flag & _ERR) != 0) 
 
//
// More stuff.
//

void scroll(void);

//#bugbug: deletando isso...
//int app_clear(int color);

int drawBar(int color);  //??


//#todo
int snprintf(char *str,size_t count,const char *fmt,...);

int vprintf (const char *fmt, va_list ap);

//#test
//ainda não foi testada
int fscanf (FILE *stream, const char *format, ... );


/*Inicialização da biblioteca*/
void stdioInitialize();


#endif //__STDIO_H__

//
// End.
//
