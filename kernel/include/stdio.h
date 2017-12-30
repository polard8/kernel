/*
 * Arquivo: stdio.h
 *
 * Descrição:
 *     Rotinas padrão de I/O.
 *   
 * @todo: Trabalhar nas funções de abrir e fechar arquivos.
 * 
 * Versão 1.0, 2015, 2016.
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
// input() support
// 

#define INPUT_MODE_LINE                0
#define INPUT_MODE_MULTIPLE_LINES      1
int g_inputmode;
 
// 
//printf support 
//

//#define kprintf printf    //kernel support
//#define dprintf printf    //debug support
//...
 

#define REVERSE_ATTRIB 0x70
#define PAD_RIGHT 1
#define PAD_ZERO 2

/* the following should be enough for 32 bit int */
#define PRINT_BUF_LEN 12


#define EOF (-1)    //Ok.





//#define SEEK_SET   0
//#define SEEK_CUR   1
//#define SEEK_END   2


//enum FileFlags {_F_READ = 0x0001, _F_WRIT = 0x0002, _F_RDWR = 0x0003, _F_ERR = 0x0010, _F_EOF = 0x0020, _F_BIN = 0x0040};


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
#define FOPEN_MAX	(20)
#define NUMBER_OF_FILES (20)


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

#define  _IOFBF  4096    //Full buffer (uma página)
#define  _IOLBF  256     //Uma linha.       
#define  _IONBF  0       
#define  BUFSIZ  512 
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

/*
 * FILE:
 *     Estrutura padrão para arquivos.
 *     >>> i/o buffer 
 */
typedef struct _iobuf FILE; 
struct _iobuf 
{
	object_type_t objectType;
	object_class_t objectClass;	
	
	char *_ptr;    //Current position of file pointer (absolute address).
	int   _cnt;
	char *_base;    //Pointer to the base of the file.
	int   _flag;    //Flags (see FileFlags).
	int   _file;
	int   _charbuf;
	int   _bufsiz;
	char *_tmpfname;
};

//principais
FILE *file_BootManager;
FILE *file_BootLoader;
FILE *file_Kernel;
FILE *file_Idle;
FILE *file_Shell;
FILE *file_TaskMan;

//
FILE *file_root;
FILE *file_pwd;
FILE *file_Current;
//...


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

//Fluxo padrão:
FILE *stdin;
FILE *stdout;
FILE *stderr;

//Fluxo padrão para o kernel:
//FILE *kstdin;
//FILE *kstdout;
//FILE *kstderr;


FILE *_io_table[NUMBER_OF_FILES];

#define stdin  (_io_table[0])	
#define stdout 	(_io_table[1])
#define stderr 	(_io_table[2])

//Lista de arquivos abertos
//unsigned long openfileList[128];
//...Outras listas de arquivos.

/*
 * Protótipos do padão C.
 */

#define kprintf printf
 
int fclose(FILE *stream);    //@todo:  
FILE *fopen( const char *filename, const char *mode );    //@todo: 
int printf(const char *format, ...);
int sprintf(char *str, const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);
int putchar( int ch );
int panic(const char *format, ...);
//...

//BUFFER:
//void setbuf(FILE *stream, char *buffer)
//int setvbuf(FILE *stream, char *buffer, int mode, size_t size);


//testes...(ainda não  implementadas.)
//int fgetpos(FILE *stream, fpos_t *pos);
//int remove(const char *filename);
//int rename(const char *old_filename, const char *new_filename);
//  void setbuf(FILE *stream, char *buffer);
//  FILE *tmpfile(void);
//  int scanf(const char *format, ...)
//int fgetc(FILE *stream)
//  int fputc(int char, FILE *stream)
//  int getc(FILE *stream)
//  int getchar(void)
//  int putc(int char, FILE *stream)


/*
 * Funções internas para o padrão C.
 */
static void printchar(char **str, int c);
static int prints(char **out, const char *string, int width, int pad);
static int printi(char **out, int i, int b, int sg, int width, int pad, int letbase);
static int print(char **out, int *varg);
int printf_main(void);    //#Teste.


//Suporte às rotinas do padrão C.
void outbyte(int c);
void _outbyte(int c);


/*
 * Outros protótipos. 
 *     Para rotinas do kernel que estão fora do padrão C.
 */
void scroll( void );
int kclear(int color);
int kclearClientArea(int color);
int kprint(char *message, unsigned int line, int color);


//inicializa os buffers do fluxo padrão em stdio.c
void stdioInitialize();
//
// Fim.
//

