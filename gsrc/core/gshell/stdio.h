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

//_IOFBF	full buffering
//_IOLBF	line buffering
//_IONBF	no buffering 

 
#define BUFSIZ  1024

//#define PROMPT_MAX_DEFAULT 256  

// testando com buffer maior.
#define PROMPT_MAX_DEFAULT 1024



#define	STDIN_FILENO	0
#define	STDOUT_FILENO	1
#define	STDERR_FILENO	2


#ifndef FILENAME_MAX
#define	FILENAME_MAX	(260)
#endif

#define FOPEN_MAX	(32)
#define NUMBER_OF_FILES (32)


/*
 * FILE:
 *     Estrutura padrão para arquivos.    
 *     
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

#define	STDIN_FILENO	0
#define	STDOUT_FILENO	1
#define	STDERR_FILENO	2

/*  
"flags" bits definitions
*/

//valores provisórios

#define _IOREAD 	0x0001
#define _IOWRT		0x0002

#define _IOFBF		0x0010
#define _IOLBF		0x0020
#define _IONBF		0x0040

#define _IOMYBUF	0x0100
#define _IOEOF		0x0200
#define _IOERR		0x0400
#define _IOSTRG 	0x0800
#define _IORW		0x1000
#define	_IOAPPEND	0x2000

//#define _IOREAD   01  /* Read only file        */
//#define _IOWRT    02 /* Write only file       */
//#define _IONBF    04    /* Malloc'ed Buffer data */
//#define _IOMYBUF  010
//#define _IOEOF    020
//#define _IOERR    040 /* Error indicator       */
//#define _IOSTRG   0100
//#define _IOLBF    0200
//#define _IORW     0400


//#define	_IOFBF		0000	/* full buffered */
//#define	_IOLBF		0100	/* line buffered */
//#define	_IONBF		0004	/* not buffered */
//#define	_IOEOF		0020	/* EOF reached on read */
//#define	_IOERR		0040	/* I/O error from system */

//#define	_IOREAD		0001	/* currently reading */
//#define	_IOWRT		0002	/* currently writing */
//#define	_IORW		0200	/* opened for reading and writing */
//#define	_IOMYBUF	0010	/* stdio malloc()'d buffer */

 

//#define	_IOFBF	0		/* setvbuf should set fully buffered */
//#define	_IOLBF	1		/* setvbuf should set line buffered */
//#define	_IONBF	2		/* setvbuf should set unbuffered */


#ifndef SEEK_SET
#define SEEK_SET        0       /* It moves file pointer position to the beginning of the file. */
#endif
#ifndef SEEK_CUR
#define SEEK_CUR        1       /* It moves file pointer position to given location. */
#endif
#ifndef SEEK_END
#define SEEK_END        2       /*  It moves file pointer position to the end of file. */
#endif



#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef EOF
#define EOF (-1)
#endif


 
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




// Normalmente quem cria o fluxo padrão é a rotina 
// que cria o processo.

// Fluxo padrão.
char prompt[PROMPT_MAX_DEFAULT];      //stdin
char prompt_out[PROMPT_MAX_DEFAULT];  //stdout 
char prompt_err[PROMPT_MAX_DEFAULT];  //stderr 
   
int prompt_pos;
int prompt_max;
int prompt_status;

//char prompt_text[] = "$> ";

//...

//===========================================







//unsigned long __iob[NUMBER_OF_FILES]



//Fluxo padrão:
//FILE *stdin;
//FILE *stdout;
//FILE *stderr;

//FILE *_io_table[NUMBER_OF_FILES];

//#define stdin   (_io_table[0])	
//#define stdout 	(_io_table[1])
//#define stderr 	(_io_table[2])

/*
 * Protótipos do padrão C.
 */
 
int printf(const char *format, ...);
int sprintf(char *out, const char *format, ...);

int putchar(int ch);

FILE *fopen( const char *filename, const char *mode );

int fclose(FILE *stream);


//
// Outras.
//

void scroll(void);
int app_clear(int color);
int drawBar(int color);  //??

int app_print(char *message, unsigned int line, int color);
static int prints(char **out, const char *string, int width, int pad);
static int printi(char **out, int i, int b, int sg, int width, int pad, int letbase);
static int print(char **out, int *varg);
static void printchar(char **str, int c);
void outbyte(int c);
void _outbyte(int c);
int printf_main(void);    //@todo: Isso é para testes.
unsigned long input(unsigned long ch);


int getchar(void);

int fflush( FILE *stream );
int fprintf(FILE *stream, const char *format, ...);
char *gets(char *s);
int fgetc( FILE *stream );;
#define getc fgetc

int feof( FILE *stream );
int ferror( FILE *stream );
int fseek(FILE *stream, long offset, int whence);


int fputc(int ch, FILE *stream);

//sujo.
//#define feof(p)	  (((p)->_flags & _IOEOF) != 0)
//#define ferror(p)	  (((p)->_flags & _IOERR) != 0)
//#define clearerr(p) ((p)->_flags &= ~(_IOERR|_IOEOF))
//#define feof(p)     (((p)->flag & _EOF) != 0)
//#define ferror(p)   (((p)->flag & _ERR) != 0)
//#define fileno(p)   ((p)->fd)
//#define getc(p)     fgetc(p)
//#define putc(x, p)  fputc(x, p)
//#define getchar()   getc(stdin)
//#define putchar(x)  putc((x), stdout)
//


void stdioInitialize();

//
// End.
//
