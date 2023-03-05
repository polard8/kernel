
// kstdio.h

#ifndef __KSTDIO_H
#define __KSTDIO_H    1

// input() function support?
#define INPUT_MODE_LINE              0
#define INPUT_MODE_MULTIPLE_LINES    1
int g_inputmode;

#define REVERSE_ATTRIB  0x70
#define PAD_RIGHT  1
#define PAD_ZERO   2

// The following should be enough for 32 bit int.
#define PRINT_BUF_LEN  12

//
// bsd style.
//

// #importante
// Esses serão os valores de referência
// para todos os projetos.

#define __SLBF  0x0001    /* line buffered */
#define __SNBF  0x0002    /* unbuffered */
#define __SRD   0x0004    /* OK to read */
#define __SWR   0x0008    /* OK to write */

/* RD and WR are never simultaneously asserted */
#define __SRW   0x0010    /* open for reading & writing */
#define __SEOF  0x0020    /* found EOF */
#define __SERR  0x0040    /* found error */
#define __SMBF  0x0080    /* _buf is from malloc */
#define __SAPP  0x0100    /* fdopen()ed in append mode */
#define __SSTR  0x0200    /* this is an sprintf/snprintf string */
#define __SOPT  0x0400    /* do fseek() optimization */
#define __SNPT  0x0800    /* do not do fseek() optimization */
#define __SOFF  0x1000    /* set iff _offset is in fact correct */
#define __SMOD  0x2000    /* true => fgetln modified _p text */
#define __SALC  0x4000    /* allocate string space dynamically */


/*
 (BSD style)
#define	_IOFBF	0		// setvbuf should set fully buffered 
#define	_IOLBF	1		// setvbuf should set line buffered 
#define	_IONBF	2		// setvbuf should set unbuffered 

// See: limits.h
#define	BUFSIZ	1024	// size of buffer used by setbuf
*/

// See: limits.h
#define EOF    GRAMADO_EOF

//enum FileFlags {_F_READ = 0x0001, _F_WRIT = 0x0002, _F_RDWR = 0x0003, _F_ERR = 0x0010, _F_EOF = 0x0020, _F_BIN = 0x0040};

#define _IOMYBUF  0x0008  /* stdio malloc()'d buffer */
#define _IOEOF    0x0010  /* EOF reached on read */
#define _IOERR    0x0020  /* I/O error from system */
#define _IOSTRG   0x0040 /* Strange or no file descriptor */

#define STDIN_FILENO   0
#define STDOUT_FILENO  1
#define STDERR_FILENO  2

//The macro yields the maximum size array of characters that 
//you must provide to hold a filename.
//#define FILENAME_MAX (8+3)

// See:
// gramado/limits.h
#ifndef FILENAME_MAX
#define FILENAME_MAX    GRAMADO_FILENAME_MAX
#endif



// The size of the file table.
// The macro yields the maximum number of files that the target 
// environment permits to be simultaneously open 
// (including stderr, stdin, and stdout).
// See:
// gramado/limits.h

#define FOPEN_MAX          GRAMADO_FOPEN_MAX
#define NUMBER_OF_FILES    GRAMADO_FOPEN_MAX
#define _NFILE             GRAMADO_FOPEN_MAX
#define NR_OPEN            GRAMADO_FOPEN_MAX


//BUFFER
//_IOFBF, _IOLBF and _IONBF
//_IONBF: The macro yields the value of the mode argument to 
// setvbuf to indicate no buffering. (Flush the stream buffer at the end of each write operation.)


/*
#define  _IONBF  0       //unbuffered 
#define  _IOLBF  256     //Uma linha.       
#define  _IOFBF  4096    //Full buffer (uma p�gina)
*/

// bsd-like
#define _IOFBF  0  // setvbuf should set fully buffered 
#define _IOLBF  1  // setvbuf should set line buffered 
#define _IONBF  2  // setvbuf should set unbuffered 

// See:  limits.h
#define BUFSIZ  GRAMADO_BUFSIZ 


#ifndef SEEK_SET
#define SEEK_SET  0
#endif

#ifndef SEEK_CUR
#define SEEK_CUR  1
#endif

#ifndef SEEK_END
#define SEEK_END  2
#endif

// Clear the file buffer
// and set the postition at the start of the file.
#ifndef GRAMADO_SEEK_CLEAR
#define GRAMADO_SEEK_CLEAR  1000
#endif


// #define  TMP_MAX    32767
// #define  L_tmpnam    1024    /* XXX must be == PATH_MAX */
// #define  P_tmpdir    "/tmp/"
// #define  L_ctermid   1024    /* size for ctermid(); PATH_MAX */

//
// == prompt =============================
//

//#define PROMPT_SIZE         256 
//#define PROMPT_MAX_DEFAULT  256

// #test
#define PROMPT_SIZE         BUFSIZ
#define PROMPT_MAX_DEFAULT  BUFSIZ

char prompt[PROMPT_SIZE];      //buffer para stdin
char prompt_out[PROMPT_SIZE];  //buffer para stdout
char prompt_err[PROMPT_SIZE];  //buffer para strerr

unsigned long prompt_pos; 
unsigned long prompt_max; 
unsigned long prompt_status;


// =======================================

// Print char flags. (_outbyte)
// usada para rotinas de pintura da libC.
// ou seja, dentro do terminal. 

//
//#importante: 
//
//  +++ Nao se escreve fora do terminal com printf. +++
//
// Como n�o se escreve fora no terminal com printf.
// essa flag s� faz sentido dentro de stdio.c
//
// Para rotinas de pintura fora do terminal poderemos 
// usar os dois tipos de draw char.
//
// flag usada por _outbyte para decidir
// se desenha um char transparente ou n�o.
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
typedef __off_t  fpos_t;

//#define _FSTDIO    /* Define for new stdio with functions. */

/*
 * NB: 
 * to fit things in six character monocase externals, the stdio
 * code uses the prefix `__s' for stdio objects, typically followed
 * by a three-character attempt at a mnemonic.
 */

// stdio buffers
struct __sbuf 
{
    unsigned char *_base;
    int _size;
};


// =======================================================
// Sync

#define ACTION_NULL       0
#define ACTION_REQUEST    1000
#define ACTION_REPLY      2000
#define ACTION_EVENT      3000
#define ACTION_ERROR      4000
// ...
#define SYNC_REQUEST_SET_ACTION  1
#define SYNC_REQUEST_GET_ACTION  2
// ...

struct kstdio_sync_d
{
    int used;
    int magic;

    pid_t sender;
    pid_t receiver;

    // REQUEST, REPLY, EVENT, ERROR
    // See: defines above.
    int action;

    // for files, ttys, sockets ...
    int can_read;
    int can_write;
    
    // for images.
    int can_execute;
    
    // for sockets.
    int can_accept;
    int can_connect;
    
    int block_on_write;
    int block_on_write_full;
    
    int block_on_read;
    int block_on_read_empty;
    
    int lock;
    
    // save into the disk.
    // TRUE = Save the content of the _base into the physical media.
    // FALSE = Nothing to be saved.
    
    // #todo: See: O_SYNC O_DSYNC O_RSYNC and O_DIRECT. 
    
    // O_SYNC: The file is opened for synchronous I/O. 
    // Any write () s on the resulting file descriptor 
    // will block the calling process until the data has been 
    // physically written to the underlying hardware.   
    
    int _sync;
    
    // ...
};


#define SYNC_COUNT_MAX  1024
// Lista global de objetos do tipo sync.
// os processos utilizarao um id para
// a lista global.
unsigned long syncList[SYNC_COUNT_MAX];


//
// =============================
//

/*
 * file_d:
 *     File structure.
 *     ring 0.
 */

struct file_d
{

    object_type_t ____object;
    int used;
    int magic;
    char *_tmpfname;  

// Index for the list of open files that belongs to a process.
// p->Objects[_file]
// #todo: Maybe 'int'.
    short _file;

// Global index.
// A estrutura de arquivos aponta para tabela global de 
// arquivos abertos.
    int filetable_index;

    pid_t pid;  // Process
    uid_t uid;  // User 
    gid_t gid;  // Group

//
// inode
//

// A estrutura de arquivos aponta para a tabela de inodes.
    int inodetable_index;
    struct inode_d   *inode;

//
// Device
//

// The minor represents an index in deviceList[i].
    int isDevice;
    short dev_major;  // Driver ID.
    short dev_minor;  // Device ID.
    struct device_d  *device;

    struct tty_d  *tty;

//
// Socket
//

    int socket_buffer_full;
    struct socket_d  *socket;


//
// Buffer
//

// Endereço base do buffer.
    unsigned char *_base;
// Ponteiro de trabalho.
// Current position of file pointer (absolute address).
// Next character position from/to here in buffer
    unsigned char *_p;
// Read space left for getc()
    int _r;
// Write space left for putc()
    int _w;
// The buffer size,
// 0 or -_bf._size, for inline putc 
    int _lbfsize;
// #todo: file size.
// #test
    int _fsize;
// Number of available characters in buffer.
    int   _cnt;
// The buffer (at least 1 byte, if !NULL)
    struct __sbuf _bf;

// cookie passed to io functions
    void *_cookie; 

    short _flags;

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

// Separate buffer for fgetln() when line crosses buffer boundary 
    struct __sbuf _lb;  // buffer for fgetln() 

// Unix stdio files get aligned to block boundaries on fseek() 
    int _blksize;    // stat.st_blksize (may be != _bf._size) 
    fpos_t _offset;  // current lseek offset

    int _charbuf;
   // =============================

//
// == (2) synchronization ========
//


// Sincronizando a leitura e a escrita
// para arquivos como socket, tty, buffer ... etc.
    struct kstdio_sync_d  sync;

//----------------------------------------------

// Contador de descritores de arquivo que usam essa mesma estrutura.
// we need to synchronize the readers.
    int fd_counter;

    //pipe ??

    int iopl;

// The list of threads that are waiting for this object.
    //struct thread_d *waiting;
    int tid_waiting;

// Navigation?
    struct file_d  *next;
};

// The file structure type.
typedef struct file_d  file; 
typedef struct file_d  object; 

//-----------------------------------------------

// File pointers.
// see: kstdio.c

// Standard stream.
// Initialized by kstdio_initialize() in kstdio.c
extern file *stdin;
extern file *stdout;
extern file *stderr;
// VFS
// Not initialized yet.
extern file *vfs_fp;
// Rootdir for bootvolume and systemvolume.
// Initialized by fsInit() in fs.c
extern file *volume1_rootdir_fp;
extern file *volume2_rootdir_fp;
//...

//
// file table.
//
 
unsigned long file_table[NUMBER_OF_FILES]; 

//-----------------------------------------------


int kstdio_standard_streams_initialized;


// N� usaremos o array de estrutura.
//#define stdin     (_io_table[0])
//#define stdout    (_io_table[1])
//#define stderr    (_io_table[2])
//#define stdin     (&_io_table[0])
//#define stdout    (&_io_table[1])
//#define stderr    (&_io_table[2])

//
// == Pipes ======================================
//

// 0
//Pipe para a rotina execve particular 
//usada no no init do ambiente Gramado Core.
extern file *pipe_gramadocore_init_execve;
// 1
//Pipe usado pela rotina execve.
extern file *pipe_execve;

//Continua ...

#define NUMBER_OF_PIPES  8
unsigned long Pipes[NUMBER_OF_PIPES];

// ========================================================


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
// rotina em ring0 para colocar conte�do numa stream.
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
//rotinas de baixo n�vel do bsd.
//#define __sgetc(p) fgetc(p)
//#define __sputc(x, p) fputc(x, p)


//
// == prototypes ============================
//

int __feedSTDIN( unsigned long ch );

int is_socket (file *f);
int is_virtual_console (file *f);

unsigned long kinput ( unsigned long ch );

void printchar (char **str, int c);
int putchar (int ch);

//#test
void putchar_K(void);

//
// == printf support ===================
//

int 
prints ( 
    char **out, 
    const char *string, 
    int width, 
    int pad );

int 
printi (
    char **out, 
    int i, 
    int b, 
    int sg, 
    int width, 
    int pad, 
    int letbase );

int print ( char **out, int *varg );

//=============================================


// service 8002
int sys_setup_stdin( int stdin_fd );

// #suspensa
// Essa implementação foi feita para 32bit e não funciona
// por inteiro em long mode.
// Usaremos kinguio_printf por enquanto.
int printk_old ( const char *format, ... );

// ===================================

int kputs ( const char *str );

// #suspensa
// Essa implementação foi feita para 32bit e não funciona
// por inteiro em long mode.
int sprintf_old ( char *str, const char *format, ... );
int mysprintf(char *buf, const char *fmt, ...);


// ===================================
void kinguio_i2hex(unsigned int val, char* dest, int len);
char *kinguio_itoa (int val, char *str);



int kinguio_vsprintf(char * str,const char * fmt, va_list ap);
void kinguio_puts(const char* str);
int kinguio_printf(const char *fmt, ...);

// ===================================

int k_ungetc ( int c, file *f );
long k_ftell (file *f);
int k_fileno ( file *f );
int k_fgetc (file *f);
int k_feof ( file *f );
int k_ferror ( file *f );
int k_fseek ( file *f, long offset, int whence );
int k_fputc ( int ch, file *f );
int k_fscanf (file *f, const char *format, ... );
void k_rewind ( file *f );
int k_fclose (file *f);
int k_fputs ( const char *str, file *f );
void k_setbuf (file *f, char *buf);
void k_setbuffer (file *f, char *buf, size_t size);
void k_setlinebuf (file *f);
int k_setvbuf (file *f, char *buf, int mode, size_t size);

int 
regularfile_ioctl ( 
    int fd, 
    unsigned long request, 
    unsigned long arg );

int kstdio_initialize (void);


//
// == printk ===============================================
//

//https://en.wikipedia.org/wiki/Printk
//#define  printf printk
//#define kprintf printk
#define printf   kinguio_printf
#define printk   kinguio_printf
#define sprintf  mysprintf


#endif    



