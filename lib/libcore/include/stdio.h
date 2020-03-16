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

#include <sys/types.h>
#include <sys/cdefs.h>
#include <stddef.h>
#include <stdarg.h> 




// tty id desse processo.
// Usado na inicialização da biblioteca.
// See: stdio.c:
int __libc_tty_id;


//
// # Modes #
//


// #test
//Os caracteres são colocados em stdout.
#define LIBC_NORMAL_MODE 1
//Os caracteres são pintados na tela.
#define LIBC_DRAW_MODE 2
// ...

//printf using draw mode.
int printf_draw ( const char *fmt, ... );

//setup libc mode
void libc_set_output_mode ( int mode );

	
	
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

//#define _IOFBF    0x0000  /* full buffered */
//#define _IOLBF    0x0040  /* line buffered */
//#define _IONBF    0x0004  /* not buffered */

/*bsd-like*/
#define	_IOFBF	0		// setvbuf should set fully buffered 
#define	_IOLBF	1		// setvbuf should set line buffered 
#define	_IONBF	2		// setvbuf should set unbuffered 

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
 * This is fairly grotesque, but pure ANSI code must not inspect the
 * innards of an fpos_t anyway.  The library internally uses off_t,
 * which we assume is exactly as big as eight chars.
 */

/*
#if (!defined(_ANSI_SOURCE) && !defined(__STRICT_ANSI__)) || defined(_LIBC)
typedef __off_t fpos_t;
#else
typedef struct __sfpos {
	__off_t _pos;
} fpos_t;
#endif
*/

// Vamos usar esse por enquanto.
typedef __off_t fpos_t;

//#define	_FSTDIO			/* Define for new stdio with functions. */

/*
 * NB: to fit things in six character monocase externals, the stdio
 * code uses the prefix `__s' for stdio objects, typically followed
 * by a three-character attempt at a mnemonic.
 */

/* stdio buffers */
struct __sbuf {
	unsigned char *_base;
	int	_size;
};

/*
 **********************************************************************
 * FILE:
 *     Estrutura padrão para arquivos.    
 *     #bugbug: os arquivos com esse tipo de estrutura serao
 *              gerenciados pelo kernel, para ser compativel com unix-like
 *              e para facilitar a comunicaçao entre processos.
 */


// #importante
// Essa é a versão antiga usada no gde,
// Para libc03 vou modificar essa estrutura para ficar igual a do BSD.

/*
 old version
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
*/


/*
typedef	struct __sFILE {
	unsigned char *_p;	          // current position in (some) buffer 
	int	_r;		                  // read space left for getc() 
	int	_w;		                  // write space left for putc() 
	short	_flags;		          // flags, below; this FILE is free if 0 
	short	_file;		          // fileno, if Unix descriptor, else -1 
	struct	__sbuf _bf;	          // the buffer (at least 1 byte, if !NULL) 
	int	_lbfsize;	              // 0 or -_bf._size, for inline putc 

	//operations 
	void	*_cookie;	                 // cookie passed to io functions 
	int	(*_close) __P((void *));
	int	(*_read)  __P((void *, char *, int));
	fpos_t	(*_seek)  __P((void *, fpos_t, int));
	int	(*_write) __P((void *, const char *, int));

	//file extension 
	struct	__sbuf _ext;

	// separate buffer for long sequences of ungetc() 
	unsigned char *_up;   	// saved _p when _p is doing ungetc data 
	int	_ur;		        // saved _r when _r is counting ungetc data 

	// tricks to meet minimum requirements even when malloc() fails 
	unsigned char _ubuf[3];	// guarantee an ungetc() buffer 
	unsigned char _nbuf[1];	// guarantee a getc() buffer 

	//separate buffer for fgetln() when line crosses buffer boundary 
	struct	__sbuf _lb;	// buffer for fgetln() 

	//Unix stdio files get aligned to block boundaries on fseek() 
	int	_blksize;	// stat.st_blksize (may be != _bf._size) 
	fpos_t	_offset;	// current lseek offset 
} FILE;
*/



struct _iobuf 
{

    int used;
    int magic;


    // Pointer to the base of the file. the buffer
    unsigned char *_base;      


	// Current position in (some) buffer
	// Current position of file pointer (absolute address).
    unsigned char *_p;


	// read space left for getc()
    int _r;

	// write space left for putc()
    int _w;

    int _cnt;      // number of available characters in buffer 


	// flags, below; this FILE is free if 0 
	// Flags (see FileFlags). the state of the stream
    short _flags;


	// fileno, if Unix descriptor, else -1
	// UNIX System file descriptor
    short _file;


	// the buffer (at least 1 byte, if !NULL)
    struct __sbuf _bf;

	// 0 or -_bf._size, for inline putc 
    int _lbfsize;



	// operations - (bsd-like)
	//#todo: olhar __P em sys/cdefs.h
    void *_cookie;                  // cookie passed to io functions 
    int     (*_close) __P((void *));
    int     (*_read)  __P((void *, char *, int));
    fpos_t  (*_seek)  __P((void *, fpos_t, int));
    int     (*_write) __P((void *, const char *, int));



	//file extension 
    struct __sbuf _ext;


	// separate buffer for long sequences of ungetc() 
	// saved _p when _p is doing ungetc data 
    unsigned char *_up;
	// saved _r when _r is counting ungetc data
    int _ur;

	// tricks to meet minimum requirements even when malloc() fails 
    unsigned char _ubuf[3];    // guarantee an ungetc() buffer 
    unsigned char _nbuf[1];    // guarantee a getc() buffer 



	//separate buffer for fgetln() when line crosses buffer boundary 
    struct __sbuf _lb;    // buffer for fgetln() 


	// Unix stdio files get aligned to block boundaries on fseek() 
    int _blksize;       // stat.st_blksize (may be != _bf._size) 
    fpos_t _offset;     // current lseek offset 


    int   _charbuf;   
    char *_tmpfname;


    int eof;
    int error;
    int have_ungotten;
    char ungotten;
        
    char default_buffer[BUFSIZ];


    // 1= is a device; 0= is a file.
    // Se é um dispositivo ou não.
    // Se for um dispositivo então o dispositivo terá
    // na lista deviceList o mesmo offset da stream na list Streams.
    int isDevice;
    int deviceId;  //índice na lista deviceList[] no kernel.
    
    int iopl;
};

typedef struct _iobuf FILE; 

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

// #bubgug
// Isso não é um prompt, isso pe uma linha de comando.
// O ideal seria mudar isso para cmdline[], desse modo
// poderíamos criar a função prompt();
//


char prompt[PROMPT_MAX_DEFAULT];      //stdin
char prompt_out[PROMPT_MAX_DEFAULT];  //stdout 
char prompt_err[PROMPT_MAX_DEFAULT];  //stderr 
   
int prompt_pos;
int prompt_max;
int prompt_status;

//char prompt_text[] = "$> ";

//...


/*
 * The __sfoo macros are here so that we can 
 * define function versions in the C library.
 */

//#todo Precisamos de __srget.
//#define	__sgetc(p) (--(p)->_r < 0 ? __srget(p) : (int)(*(p)->_p++))

//#todo Precisamos de __swbuf.
/*
#if defined(__GNUC__) && defined(__STDC__)
static __inline int __sputc(int _c, FILE *_p) {
	if (--_p->_w >= 0 || (_p->_w >= _p->_lbfsize && (char)_c != '\n'))
		return (*_p->_p++ = _c);
	else
		return (__swbuf(_c, _p));
}
#else
//This has been tuned to generate reasonable code on the vax using pcc.
#define	__sputc(c, p) \
	(--(p)->_w < 0 ? \
		(p)->_w >= (p)->_lbfsize ? \
			(*(p)->_p = (c)), *(p)->_p != '\n' ? \
				(int)*(p)->_p++ : \
				__swbuf('\n', p) : \
			__swbuf((int)(c), p) : \
		(*(p)->_p = (c), (int)*(p)->_p++))
#endif
*/







/*bsd*/
#define	__sfeof(p)	(((p)->_flags & __SEOF) != 0)
#define	__sferror(p)	(((p)->_flags & __SERR) != 0)
#define	__sclearerr(p)	((void)((p)->_flags &= ~(__SERR|__SEOF)))
#define	__sfileno(p)	((p)->_file)
//define	feof(p)		__sfeof(p)
//#define	ferror(p)	__sferror(p)
//#define	clearerr(p)	__sclearerr(p)

//#ifndef _ANSI_SOURCE
//#define	fileno(p)	__sfileno(p)
//#endif

//#ifndef lint
//#define	getc(fp)	__sgetc(fp)
//#define putc(x, fp)	__sputc(x, fp)
//#endif /* lint */

//#define	getchar()	getc(stdin)
//#define	putchar(x)	putc(x, stdout)


/*minix3/bsd style*/
/*
#define	__sfeof(p)	(((p)->_flags & __SEOF) != 0)
#define	__sferror(p)	(((p)->_flags & __SERR) != 0)
#define	__sclearerr(p)	((void)((p)->_flags &= ~(__SERR|__SEOF)))
#define	__sfileno(p)	\
    ((p)->_file == -1 ? -1 : (int)(unsigned short)(p)->_file)

#if !defined(__lint__) && !defined(__cplusplus)
#if !defined(_REENTRANT) && !defined(_PTHREADS)
#define	feof(p)		__sfeof(p)
#define	ferror(p)	__sferror(p)
#define	clearerr(p)	__sclearerr(p)

#define	getc(fp)	__sgetc(fp)
#define putc(x, fp)	__sputc(x, fp)

#define	getchar()	getc(stdin)
#define	putchar(x)	putc(x, stdout)
*/

/*
//#define getchar()         getc(stdin)
//#define putchar(_c)       putc((_c),stdout)
*/


/*linux klibc style.*/
//#define getc(f) fgetc(f)


/*glib style; isso pode ser usado no kernel*/
/* Optimizing.  */
/*
#ifdef	__OPTIMIZE__
#define	feof(stream)	((stream)->__eof != 0)
#define	ferror(stream)	((stream)->__error != 0)
#endif 
*/
	

/*glibc style*/
/* The C standard explicitly says this can
   re-evaluate its arguments, so it does.  */
/*
#define	__putc(c, stream)						      \
  ((stream)->__bufp < (stream)->__put_limit ?				      \
   (int) (unsigned char) (*(stream)->__bufp++ = (unsigned char) (c)) :	      \
   __flshfp ((stream), (unsigned char) (c)))
*/


// versão para humanos entenderem.
//enquanto for menor que o limite coloca o char, caso contrário
//__flshfp ???
/*
zzz __putc (c, stream)
{
  ( (stream)->__bufp < (stream)->__put_limit 
  ? (int) (unsigned char) (*(stream)->__bufp++ = (unsigned char) (c) ) 
  :	__flshfp ((stream), (unsigned char) (c)))
  
}
*/


/*glibc style*/
/* The C standard explicitly says this can be a macro,
   so we always do the optimization for it.  */
//#define	putc(c, stream)	__putc ((c), (stream))



void debug_print (char *string);

//===========================================
// ## Protótipos do padrão C. ##
//===========================================

char *ctermid(char *s);

int fpurge(FILE *stream);

int fsetpos(FILE *stream, const fpos_t *pos);

int fgetpos(FILE *stream, fpos_t *pos);

FILE *fmemopen(void *buf, size_t size, const char *mode);

FILE *open_wmemstream(wchar_t **ptr, size_t *sizeloc);

FILE *open_memstream(char **ptr, size_t *sizeloc);

FILE *freopen(const char *pathname, const char *mode, FILE *stream);

FILE *fdopen(int fd, const char *mode);

FILE *tmpfile(void);

char *tempnam(const char *dir, const char *pfx);
char *tmpnam_r(char *s);
char *tmpnam(char *s);

int vfscanf(FILE *stream, const char *format, va_list ap);
int vsscanf(const char *str, const char *format, va_list ap);
int vscanf(const char *format, va_list ap);

int vsnprintf(char *str, size_t size, const char *format, va_list ap);
int vsprintf(char *str, const char *format, va_list ap);
int vdprintf(int fd, const char *format, va_list ap); 
int dprintf(int fd, const char *format, ...);

unsigned int filesize (FILE * fp);
char * fileread (FILE * fp);




// remove - remove a file or directory 
// On success, zero is returned. On error, -1 is returned, and 
// errno is set appropriately. 
// C89, C99, 4.3BSD, POSIX.1-2001. 
int remove (const char *pathname); 


int fileno ( FILE *stream );
 
/*
 * File Operations
 */ 
 
FILE *fopen( const char *filename, const char *mode ); 

int fclose(FILE *stream); 
//#define fileno(p)   ((p)->fd)
 
 
/*
 * Normal output.
 */ 
 


//#todo: testar.
//Credits: Sombra OS.
void nputs (char *cp, int len);

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


int printf (const char *format, ...); 

//tradicional, incompleta; não funciona,
//estamos implementando uma printf padrão tradicional.
int printf2(const char *format, ...); 

int printf3(const char *fmt, ...);


//find next line
char *stdio_nextline ( char *string );

//next line sprintf
int nlsprintf ( char *out, const char *format, ... );

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
 



//
// low level
//


int fflush (FILE *stream); 
int __fflush (FILE *stream);
int __getc ( FILE *stream );
int __putc (int ch, FILE *stream);


//
// Root.
//

int getc (FILE *stream);
int putc (int ch, FILE *stream);
int fgetc (FILE *stream);
int fputc (int ch, FILE *stream);

//
// Root 2
//

int getchar (void);
int putchar (int ch);



//
// Root 3
//

char *gets (char *s);
int puts (const char *s);


//
// Root 4
//

char *fgets (char *s, int size, FILE *stream);
int fputs ( const char *s, FILE *stream );


//
// Root 5
//

int getw (FILE *stream);
int putw (int w, FILE *stream);



//saved
int __gramado__getc ( FILE *stream );
int __serenity_fflush ( FILE *stream);
int __serenity_fputc (int ch, FILE *stream);
int __serenity_putc (int ch, FILE *stream);



int ungetc ( int c, FILE *stream );
long ftell (FILE *stream);













//#define getc(p)     fgetc(p)

//#define getchar()   getc(stdin)
//#define putchar(x)  putc((x), stdout)

//#importante:
//Podemos usar isso para compatibilidade com as
//rotinas de baixo nível do bsd.
//#todo: podemos fazer o mesmo para compatibilidade com outras libs.
//>>> sempre usando as rotinas de baixo nível do gde.
//#define __sgetc(p) fgetc(p)
//#define __sputc(x, p) fputc(x, p)



size_t fread (void *ptr, size_t size, size_t n, FILE *fp);
size_t fwrite (const void *ptr, size_t size, size_t n, FILE *fp);



// prompt support.
// coloca no prompt[] em ring3 e exibe com uma rotina em ring0.
int prompt_putchar ( int c, int con_id );
int prompt_put_string ( char *string );
int prompt_strcat (char *string);
int prompt_flush ( int con_id );
void prompt_clean ();





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

// inicializa o fluxo padrão para o processo.
int stdio_initialize_standard_streams (void);


// see: https://linux.die.net/man/3/setvbuf
void setbuf(FILE *stream, char *buf);
void setbuffer(FILE *stream, char *buf, size_t size);
void setlinebuf(FILE *stream);
int setvbuf(FILE *stream, char *buf, int mode, size_t size);


int libcStartTerminal (void);

/*Inicialização da biblioteca*/
void stdioInitialize ();


#endif    //__STDIO_H__

//
// End.
//
