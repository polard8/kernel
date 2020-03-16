/*
 * File: kstdio.h
 *
 *    i/o functions for base kernel.
 *    ring 0.
 *  
 * History:
 *     2015 - Created by Fred Nora.
 */

 
 
/*
    The stdio.h header defines three variable types, 
	several macros, and various functions for performing 
	input and output.

    Library Variables
    Following are the variable types 
	defined in the header stdio.h -

    S.N.	Variable & Description
    1	size_t
    This is the unsigned integral type and 
	is the result of the sizeof keyword.

    2 FILE
    This is an object type suitable for storing 
	information for a file stream.

    3 fpos_t
    This is an object type suitable for 
	storing any position in a file.

    Library Macros
    Following are the macros 
	defined in the header stdio.h -

    S.N. Macro & Description
    1 NULL
    This macro is the value of a null pointer constant.

    2 _IOFBF, _IOLBF and _IONBF
    These are the macros which expand to integral constant 
	expressions with distinct values and 
	suitable for the use as third argument to the setvbuf function.

    3 BUFSIZ
    This macro is an integer, 
	which represents the size of the buffer used by the setbuf function.

    4 EOF
    This macro is a negative integer, 
	which indicates that the end-of-file has been reached.

   5 FOPEN_MAX
   This macro is an integer, 
   which represents the maximum number of files 
   that the system can guarantee to be opened simultaneously.

   6 FILENAME_MAX
   This macro is an integer, 
   which represents the longest length of a char array 
   suitable for holding the longest possible filename. 
   If the implementation imposes no limit, 
   then this value should be the recommended maximum value.

   7 L_tmpnam
   This macro is an integer, 
   which represents the longest length of a char array 
   suitable for holding the longest possible temporary filename 
   created by the tmpnam function.

  8 SEEK_CUR, SEEK_END, and SEEK_SET
  These macros are used in the fseek function to 
  locate different positions in a file.

  9	TMP_MAX
  This macro is the maximum number of unique filenames 
  that the function tmpnam can generate.

  10 stderr, stdin, and stdout
  These macros are pointers to FILE types 
  which correspond to the standard error, 
  standard input, and standard output streams.

  Library Functions
  Following are the functions defined in the header stdio.h -

  Follow the same sequence of functions for better understanding and 
  to make use of Try it(Online compiler) option, 
  because file created in the first function will be 
  used in subsequent functions.
  
  S.N.	Function & Description

  1	
  int fclose(FILE *stream)
  Closes the stream. All buffers are flushed.

  2	
  void clearerr(FILE *stream)
  Clears the end-of-file and error indicators for the given stream.

  3	
  int feof(FILE *stream)
  Tests the end-of-file indicator for the given stream.

  4	
  int ferror(FILE *stream)
  Tests the error indicator for the given stream.

  5	
  int fflush(FILE *stream)
  Flushes the output buffer of a stream.

  6	
  int fgetpos(FILE *stream, fpos_t *pos)
  Gets the current file position of the stream and writes it to pos.

  7	
  FILE *fopen(const char *filename, const char *mode)
  Opens the filename pointed to by filename using the given mode.

  8	
  size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
  Reads data from the given stream into the array pointed to by ptr.

  9	
  FILE *freopen(const char *filename, const char *mode, FILE *stream)
  Associates a new filename with the given open 
  stream and same time closing the old file in stream.

  10	
  int fseek(FILE *stream, long int offset, int whence)
  Sets the file position of the stream to the given offset. 
  The argument offset signifies the number of bytes to seek 
  from the given whence position.

  11	
  int fsetpos(FILE *stream, const fpos_t *pos)
  Sets the file position of the given stream to the given position. 
  The argument pos is a position given by the function fgetpos.

  12	
  long int ftell(FILE *stream)
  Returns the current file position of the given stream.

  13	
  size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
  Writes data from the array pointed to by ptr to the given stream.

  14	
  int remove(const char *filename)
  Deletes the given filename so that it is no longer accessible.

  15	
  int rename(const char *old_filename, const char *new_filename)
  Causes the filename referred to, by old_filename to be changed to new_filename.

  16	
  void rewind(FILE *stream)
  Sets the file position to the beginning of the file of the given stream.

  17	
  void setbuf(FILE *stream, char *buffer)
  Defines how a stream should be buffered.

  18	
  int setvbuf(FILE *stream, char *buffer, int mode, size_t size)
  Another function to define how a stream should be buffered.

  19	
  FILE *tmpfile(void)
  Creates a temporary file in binary update mode (wb+).

  20	
  char *tmpnam(char *str)
  Generates and returns a valid temporary filename which does not exist.

  21	
  int fprintf(FILE *stream, const char *format, ...)
  Sends formatted output to a stream.

  22	
  int printf(const char *format, ...)
  Sends formatted output to stdout.

  23	
  int sprintf(char *str, const char *format, ...)
  Sends formatted output to a string.

  24	
  int vfprintf(FILE *stream, const char *format, va_list arg)
  Sends formatted output to a stream using an argument list.

  25	
  int vprintf(const char *format, va_list arg)
  Sends formatted output to stdout using an argument list.

  26	
  int vsprintf(char *str, const char *format, va_list arg)
  Sends formatted output to a string using an argument list.

  27	
  int fscanf(FILE *stream, const char *format, ...)
  Reads formatted input from a stream.

  28	
  int scanf(const char *format, ...)
  Reads formatted input from stdin.

  29	
  int sscanf(const char *str, const char *format, ...)
  Reads formatted input from a string.

  30	
  int fgetc(FILE *stream)
  Gets the next character (an unsigned char) 
  from the specified stream and 
  advances the position indicator for the stream.

  31	
  char *fgets(char *str, int n, FILE *stream)
  Reads a line from the specified stream and 
  stores it into the string pointed to by str. 
  It stops when either (n-1) characters are read, 
  the newline character is read, 
  or the end-of-file is reached, 
  whichever comes first.

  32	
  int fputc(int char, FILE *stream)
  Writes a character (an unsigned char) 
  specified by the argument char to the specified stream and 
  advances the position indicator for the stream.

  33	
  int fputs(const char *str, FILE *stream)
  Writes a string to the specified stream up to 
  but not including the null character.

  34	
  int getc(FILE *stream)
  Gets the next character (an unsigned char) 
  from the specified stream and 
  advances the position indicator for the stream.

  35	
  int getchar(void)
  Gets a character (an unsigned char) from stdin.

  36	
  char *gets(char *str)
  Reads a line from stdin and 
  stores it into the string pointed to by, str. 
  It stops when either the newline character is 
  read or when the end-of-file is reached, 
  whichever comes first.

  37	
  int putc(int char, FILE *stream)
  Writes a character (an unsigned char) 
  specified by the argument char to the 
  specified stream and 
  advances the position indicator for the stream.

  38	
  int putchar(int char)
  Writes a character (an unsigned char) 
  specified by the argument char to stdout.

  39	
  int puts(const char *str)
  Writes a string to stdout up to 
  but not including the null character. 
  A newline character is appended to the output.

  40	
  int ungetc(int char, FILE *stream)
  Pushes the character char (an unsigned char) 
  onto the specified stream so 
  that the next character is read.

  41	
  void perror(const char *str)
  Prints a descriptive error message to stderr. 
  First the string str is printed followed by a colon and then a space.
*/ 




//
// * Kernel streams.
//

// Essas são as primeiras streams na estrutura Streams[]
// São padronizadas e pertencem ao kernel.

// Configuradas em stdio.c
#define __KERNEL_STREAM_STDIN   0
#define __KERNEL_STREAM_STDOUT  1
#define __KERNEL_STREAM_STDERR  2

// Configuradas em vfs.c.c
#define __KERNEL_STREAM_VFS     3

// Configuradas em fs.c
#define __KERNEL_STREAM_VOL1_ROOTDIR   4
#define __KERNEL_STREAM_VOL2_ROOTDIR   5

// ...
 
 
 
 
//#ifdef  _POSIX_
//...
//#endif
 
//
// input() support
// 

#define INPUT_MODE_LINE                0
#define INPUT_MODE_MULTIPLE_LINES      1
int g_inputmode;
 
 
 

#define REVERSE_ATTRIB 0x70
#define PAD_RIGHT 1
#define PAD_ZERO 2

/* the following should be enough for 32 bit int */
#define PRINT_BUF_LEN 12


//
// bsd style.
//

// #importante
// Esses serão os valores de referência
// para todos os projetos.

#define  __SLBF 0x0001    /* line buffered */
#define  __SNBF 0x0002    /* unbuffered */
#define  __SRD  0x0004    /* OK to read */
#define  __SWR  0x0008    /* OK to write */

/* RD and WR are never simultaneously asserted */
#define  __SRW  0x0010    /* open for reading & writing */
#define  __SEOF 0x0020    /* found EOF */
#define  __SERR 0x0040    /* found error */
#define  __SMBF 0x0080    /* _buf is from malloc */
#define  __SAPP 0x0100    /* fdopen()ed in append mode */
#define  __SSTR 0x0200    /* this is an sprintf/snprintf string */
#define  __SOPT 0x0400    /* do fseek() optimization */
#define  __SNPT 0x0800    /* do not do fseek() optimization */
#define  __SOFF 0x1000    /* set iff _offset is in fact correct */
#define  __SMOD 0x2000    /* true => fgetln modified _p text */
#define  __SALC 0x4000    /* allocate string space dynamically */



/*
 (BSD style)
#define	_IOFBF	0		// setvbuf should set fully buffered 
#define	_IOLBF	1		// setvbuf should set line buffered 
#define	_IONBF	2		// setvbuf should set unbuffered 

#define	BUFSIZ	1024	// size of buffer used by setbuf
#define	EOF	(-1)
*/
#define EOF (-1)    //Ok.


//#define SEEK_SET   0
//#define SEEK_CUR   1
//#define SEEK_END   2


//enum FileFlags {_F_READ = 0x0001, _F_WRIT = 0x0002, _F_RDWR = 0x0003, _F_ERR = 0x0010, _F_EOF = 0x0020, _F_BIN = 0x0040};

#define _IOMYBUF  0x0008  /* stdio malloc()'d buffer */
#define _IOEOF    0x0010  /* EOF reached on read */
#define _IOERR    0x0020  /* I/O error from system */
#define _IOSTRG   0x0040 /* Strange or no file descriptor */


#define	STDIN_FILENO	0
#define	STDOUT_FILENO	1
#define	STDERR_FILENO	2

//The macro yields the maximum size array of characters that 
//you must provide to hold a filename.
//#define FILENAME_MAX (8+3)

#ifndef FILENAME_MAX
#define	FILENAME_MAX	(260)
#endif

//The macro yields the maximum number of files that the target 
//environment permits to be simultaneously open (including stderr, stdin, and stdout).
#define FOPEN_MAX	    (32)
#define NUMBER_OF_FILES (32)


/*
 * Prompt:
 *    O prompt do shell. 
 *    Se os caracteres do prompt do shell
 * serão pintados no terminal, então precisamos de mais espaço.
 * o terminal pode ser a janela que é a tela toda (gui->screen) ou
 * outra janela qualquer.
 *
 */
 
//BUFFER
//_IOFBF, _IOLBF and _IONBF
//_IONBF: The macro yields the value of the mode argument to 
// setvbuf to indicate no buffering. (Flush the stream buffer at the end of each write operation.)

/*
#define  _IONBF  0       //unbuffered 
#define  _IOLBF  256     //Uma linha.       
#define  _IOFBF  4096    //Full buffer (uma página)
*/

/*bsd-like*/
#define	_IOFBF	0		// setvbuf should set fully buffered 
#define	_IOLBF	1		// setvbuf should set line buffered 
#define	_IONBF	2		// setvbuf should set unbuffered 
    
//#define  BUFSIZ  512 
#define  BUFSIZ  1024 

/* It moves file pointer position to the beginning of the file. */
#ifndef SEEK_SET
#define SEEK_SET        0       
#endif

/* It moves file pointer position to given location. */
#ifndef SEEK_CUR
#define SEEK_CUR        1       
#endif

/*  It moves file pointer position to the end of file. */
#ifndef SEEK_END
#define SEEK_END        2       
#endif


#define PROMPT_SIZE 256 
#define PROMPT_MAX_DEFAULT 256

 
char prompt[PROMPT_SIZE];      //buffer para stdin
char prompt_out[PROMPT_SIZE];  //buffer para stdout
char prompt_err[PROMPT_SIZE];  //buffer para strerr

unsigned long prompt_pos; 
unsigned long prompt_status;

//@todo: Testando strings.
static char prompt_cursor[] = "$";
static char prompt_string[] = "Prompt:";


//
// Print char flags. (_outbyte)
// usada para rotinas de pintura da libC.
// ou seja, dentro do terminal. 
//

//
//#importante: 
//
//  +++ Não se escreve fora do terminal com printf. +++
//
// Como não se escreve fora no terminal com printf.
// essa flag só faz sentido dentro de stdio.c
//
// Para rotinas de pintura fora do terminal poderemos 
// usar os dois tipos de draw char.
//
// flag usada por _outbyte para decidir
// se desenha um char transparente ou não.
int stdio_terminalmode_flag;


//verbose mode do kernel.
//permite que a tela do kernel funcione igual a um 
//terminal, imprimindo os printfs um abaixo do outro.
//sempre reiniciando x.
int stdio_verbosemode_flag;




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
    int _size;
};





/*
 **********************************************
 * FILE:
 *     Estrutura padrão para arquivos.
 *     >>> i/o buffer 
 *
 *     Ambiente: RING 0.
 */
 
struct file_d
{

    // Indica qual tipo de objeto esse arquivo representa.
    // See: globals/gobject.h
    object_type_t ____object;


	// #importante
	// Vamos tornar a estrutura em kernel mode igual a estrutura de ring3;

    int used;
    int magic;

    
    int iopl;

	//Current position of file pointer (absolute address).
    unsigned char *_p;    

	// read space left for getc()
    int _r;

	// write space left for putc()
    int _w;

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

	//operations 
	//#todo: olhar __P em sys/cdefs.h
    void *_cookie;                 // cookie passed to io functions 
    int (*_close) __P((void *));
    int (*_read)  __P((void *, char *, int));
    fpos_t (*_seek)  __P((void *, fpos_t, int));
    int (*_write) __P((void *, const char *, int));

	//file extension 
    struct __sbuf _ext;

	// separate buffer for long sequences of ungetc() 
	// saved _p when _p is doing ungetc data 
    unsigned char *_up;
	// saved _r when _r is counting ungetc data
    int _ur;

	
	// tricks to meet minimum requirements even when malloc() fails 
    unsigned char _ubuf[3];   // guarantee an ungetc() buffer 
    unsigned char _nbuf[1];   // guarantee a getc() buffer 	
	
	
	//separate buffer for fgetln() when line crosses buffer boundary 
    struct __sbuf _lb;	// buffer for fgetln() 

	//Unix stdio files get aligned to block boundaries on fseek() 
    int _blksize;       // stat.st_blksize (may be != _bf._size) 
    fpos_t _offset;     // current lseek offset 		


    // 1= is a device; 0= is a file.
    // Se é um dispositivo ou não.
    // Se for um dispositivo então o dispositivo terá
    // na lista deviceList[] o mesmo offset da stream 
    // na list Streams[].

    int isDevice;
    int deviceId;  //índice na lista deviceList[]

	// old stuff
	// isso pertence a estrutura no formato antigo
	// e os elementos ainda estão presentes em várias rotinas.
	//No futuro vamos deletar isso. (Talvez não.)
    int   _cnt;
    unsigned char *_base;    
    int   _charbuf;
    char *_tmpfname;
    
    
    // Private ?
    // Vamos colocar aqui a estrutura de socket.
    void *priv;
};

typedef struct file_d FILE;   //#todo: deletar isso. 
typedef struct file_d file; 


/*
    Fluxo padrão. Também conhecidos como descritores padrão.

 +----------------+---------+-----------------------------------+
 |ID padronizado  |  Nome   |             Descricao             |
 +----------------+---------+-----------------------------------+
 |       0        |  stdin  |   associado a leitura do teclado  |
 +----------------+---------+-----------------------------------+
 |       1        | stdout  |  associado a saída normal na tela |
 +----------------+---------+-----------------------------------+
 |       2        | stderr  | associado a saída de erro         |
 +----------------+---------+-----------------------------------+
*/

//
//  ## ARQUIVOS DO PROCESSO KERNEL  ##
//

// Gramado Boot
file *stdin;            //0
file *stdout;           //1
file *stderr;           //2
file *vfs;              //3 - Diretório raiz do vfs. 
file *volume1_rootdir;  //4 - Diretório raiz do volume de boot.
file *volume2_rootdir;  //5 - Diretório raiz do volume do sistema. 
file *file_InitTXT;     //6 - Arquivo de configuração de inicialização. INIT.TXT.
file *file_users;       //7 - Pasta para perfis de usuários. /users
file *file_BootManager; //8 - Boot Manager. BM.BIN.
file *file_BootLoader;  //9 - Boot Loader. BL.BIN.

// Gramado Core
file *file_Kernel;      //10 - Kernel base. KERNEL.BIN
file *file_Init;        //11 - Init subsystem. INIT.BIN
file *file_Shell;       //12 - Shell subsystem. SHELL.BIN
file *file_TaskMan;     //13 - Task manager subsystem. TAKSMAN.BIN

// Gramado Cali
file *file_CS;          //14 California Shell. CS.BIN
file *file_CFE;         //15 California File explorer. CFE.BIN
file *file_CWE;         //16 California Web Explorer. CWE.BIN

// Gramado LA
file *file_LA;          //17 - Los Angeles Package Manager. LA.BIN  

// System directories
file *file_dd;          //18 - device drivers folder
file *file_bin;         //19 - applications folder
file *file_tmp;         //20 - tmp files folder
file *file_download;    //21 - download files folder
file *file_libs;        //22 - system libs folder

// User directories
file *file_pwd;         //23 - Diretório de trabalho. Diretório usado no comando 'pwd'. 

//...

//Array de estruturas.
//FILE *_io_table[NUMBER_OF_FILES];

// Nã usaremos o array de estrutura.
//#define stdin     (_io_table[0])	
//#define stdout 	(_io_table[1])
//#define stderr 	(_io_table[2])
//#define stdin     (&_io_table[0])	
//#define stdout 	(&_io_table[1])
//#define stderr 	(&_io_table[2])


/*
 * ## Aprendendo sobre streams ##
 * #importante 
 * Lista de endereços de estruturas de streams.
 * Essas são as streas que pertencem ao processo kernel.
 * Array de ponteiros de estrutura.
 *
 *
 * Isso poderia ser um array de acesso global,
 * contendo streams de todos os processos,
 * As primeiras sreasm seriam do processo kernel.
 * Obs: Quando um processo solicitar um descritor 
 * para a biblioteca C ele estará usando um índice que 
 * seleciona o descritor real do arquivo, que será usado 
 * nessa lista.
 * Vários processos selecionarão o descritor '0',
 * mas esse descritor deve ser traduzido para 
 * um verdadeiro descritor usado nessa lista global.
 *
 * ## IMPORTANTE ##
 * O kernel precisa gerenciar os recursos 
 * usados pelos processos e liberar esses recursos 
 * quando o processo não estiver mais usando ..
 * >>> Não é trabalho da libc se preocupar
 * com o gerenciamento de recursos do processo.
 *
 * ## facilita as coisas ##
 * Pois o kernel pode alocar memória 
 * para alguns arquivos usando o alocador de páginas, 
 * mas o processo não tem acesso a essa memória,
 * então o processo em user mode teria que fazer 
 * muitas chamadas para acessar o conteúdo do arquivo, 
 * a não ser que o kernel compartilhe a memória 
 * com o processo.
 */
 
unsigned long fileList[NUMBER_OF_FILES]; 



/*
 * #importante 
 * ## suspenso ##
 */
//unsigned long GlobalStreams[??]; 

//
// Pipes support
//

// 0
//Pipe para a rotina execve particular 
//usada no no init do ambiente Gramado Core.
file *pipe_gramadocore_init_execve;

// 1
//Pipe usado pela rotina execve.
file *pipe_execve;

//Continua ...

#define NUMBER_OF_PIPES 8
unsigned long Pipes[NUMBER_OF_PIPES];



/* bsd */
/*
 * The __sfoo macros are here so that we can 
 * define function versions in the C library.
 */
/*
#define	__sgetc(p) (--(p)->_r < 0 ? __srget(p) : (int)(*(p)->_p++))
#if defined(__GNUC__) && defined(__STDC__)
static __inline int __sputc(int _c, FILE *_p) {
	if (--_p->_w >= 0 || (_p->_w >= _p->_lbfsize && (char)_c != '\n'))
		return *_p->_p++ = (unsigned char)_c;
	else
		return __swbuf(_c, _p);
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

#define	__sfeof(p)	(((p)->_flags & __SEOF) != 0)
#define	__sferror(p)	(((p)->_flags & __SERR) != 0)
#define	__sclearerr(p)	((void)((p)->_flags &= ~(__SERR|__SEOF)))
#define	__sfileno(p)	\
    ((p)->_file == -1 ? -1 : (int)(unsigned short)(p)->_file)
*/


/*adaptado do bsd*/
// rotina em ring0 para colocar conteúdo numa stream.
/*
static __inline int bsd__sputc (int _c, FILE *_p)
{
	if ( --_p->_w >= 0 || 
		 ( _p->_w >= _p->_lbfsize && (char) _c != '\n' ) )
	{	
		return *_p->_p++ = (unsigned char) _c;
	
	}else{
		//return __swbuf(_c, _p);
	};
};
*/


//#importante:
//Podemos usar isso para compatibilidade com as
//rotinas de baixo nível do bsd.
//#define __sgetc(p) fgetc(p)
//#define __sputc(x, p) fputc(x, p)



/*
 * Diretórios onde a pesquisa deve ser feita.
 * Isso é configurável.
 * 
 */
//unsigned long Search[9]; 



//Lista de arquivos abertos
//unsigned long openfileList[128];
//...Outras listas de arquivos.

/*
 * Protótipos do padrão C.
 */

// #todo
// Deletar printf
#define kprintf printf


//Isso pertence à fcntl
int __openat (int dirfd, const char *pathname, int flags);

int fclose(file *stream);    //@todo:  
file *fopen( const char *filename, const char *mode );    //@todo: 
int printf(const char *format, ...);
int sprintf(char *str, const char *format, ...);
int fprintf(file *stream, const char *format, ...);
int putchar( int ch );
//...

int __do_fflush (file *stream);






size_t fread (void *ptr, size_t size, size_t n, file *fp);
size_t fwrite (const void *ptr, size_t size, size_t n, file *fp);

int fflush ( file *stream );

//atualiza o fluxo padrão para determinado processo
int update_standard_stream ( int PID, file *stream1, file *stream2, file *stream3 );



int fputs ( const char *str, file *stream );
int ungetc ( int c, file *stream );
long ftell (file *stream);
int fileno ( file *stream );
int fgetc ( file *stream );
int feof ( file *stream );
int ferror ( file *stream );
int fseek ( file *stream, long offset, int whence );
int fputc ( int ch, file *stream );
int fscanf (file *stream, const char *format, ... );
void rewind ( file *stream );



//BUFFER:
//void setbuf(file *stream, char *buffer)
//int setvbuf(file *stream, char *buffer, int mode, size_t size);


//testes...(ainda não  implementadas.)
//int fgetpos(file *stream, fpos_t *pos);
//int remove(const char *filename);
//int rename(const char *old_filename, const char *new_filename);
//  void setbuf(file *stream, char *buffer);
//  FILE *tmpfile(void);
//  int scanf(const char *format, ...)
//int fgetc(file *stream)
//  int fputc(int char, file *stream)
//  int getc(file *stream)
//  int getchar(void)
//  int putc(int char, file *stream)


int puts ( const char *str );




/*
 * Funções internas para o padrão C.
 */

void printchar (char **str, int c);

int 
prints ( char **out, 
         const char *string, 
         int width, 
         int pad );

int 
printi ( char **out, 
         int i, 
         int b, 
         int sg, 
         int width, 
         int pad, 
         int letbase );

int print (char **out, int *varg);




/*
 * Outros protótipos. 
 *     Para rotinas do kernel que estão fora do padrão C.
 */





//int getchar();


//
// stream buffer support
//

// see: https://linux.die.net/man/3/setvbuf
void setbuf(file *stream, char *buf);
void setbuffer(file *stream, char *buf, size_t size);
void setlinebuf(file *stream);
int setvbuf(file *stream, char *buf, int mode, size_t size);

//inicializa os buffers do fluxo padrão em stdio.c
int stdioInitialize (void);


//
// End.
//

