
// tty.h

#ifndef ____TTY_H
#define ____TTY_H  1

#define TTYCHARS_COUNT_MAX  25    //80 
#define TTYLINES_COUNT_MAX  25    //25 

//#define DEVELOPER_TTYCHARS_MAX 25    //80
//#define DEVELOPER_TTYLINES_MAX 25    //25 
//... 

/* tty magic number */
//#define TTY_MAGIC		0x5401
#define TTY_MAGIC    1234

//TTY_DRIVER_TYPE_SYSTEM
//TTY_DRIVER_TYPE_CONSOLE
//TTY_DRIVER_TYPE_SERIAL
//TTY_DRIVER_TYPE_PTY

// type
#define TTY_TYPE_CONSOLE    1000
#define TTY_TYPE_SERIAL     2000
#define TTY_TYPE_USBSERIAL  3000
#define TTY_TYPE_PTY        4000
// ...


// subtype
#define TTY_SUBTYPE_PTY_MASTER   100
#define TTY_SUBTYPE_PTY_SLAVE    200
// ...


//These bits are used in the flags field of the tty structure.
#define TTY_THROTTLED         0	/* Call unthrottle() at threshold min */
#define TTY_IO_ERROR          1	/* Cause an I/O error (may be no ldisc too) */
#define TTY_OTHER_CLOSED      2	/* Other side (if any) has closed */
#define TTY_EXCLUSIVE         3	/* Exclusive open mode */
#define TTY_DEBUG             4	/* Debugging */
#define TTY_DO_WRITE_WAKEUP   5	/* Call write_wakeup after queuing new */
#define TTY_PUSH              6	/* n_tty private */
#define TTY_CLOSING           7	/* ->close() in progress */
#define TTY_LDISC             9	/* Line discipline attached */
#define TTY_LDISC_CHANGING   10	/* Line discipline changing */
#define TTY_LDISC_OPEN       11	/* Line discipline is open */
#define TTY_HW_COOK_OUT      14	/* Hardware can do output cooking */
#define TTY_HW_COOK_IN       15	/* Hardware can do input cooking */
#define TTY_PTY_LOCK         16	/* pty private */
#define TTY_NO_WRITE_SPLIT   17	/* Preserve write boundaries to driver */
#define TTY_HUPPED           18	/* Post driver->hangup() */
#define TTY_FLUSHING         19	/* Flushing to ldisc in progress */
#define TTY_FLUSHPENDING     20	/* Queued buffer flush pending */

//
// Chars
// 

// Some special chars from termios
// used in the tty.

#define START_CHAR(tty)  ((tty)->termios.c_cc[VSTART])
#define STOP_CHAR(tty)   ((tty)->termios.c_cc[VSTOP])
#define EOF_CHAR(tty)    ((tty)->termios.c_cc[VEOF])
#define INTR_CHAR(tty)   ((tty)->termios.c_cc[VINTR])
#define ERASE_CHAR(tty)  ((tty)->termios.c_cc[VERASE])

//
// Flags
//

// Some flags from termios
// used in the tty.

#define _L_FLAG(tty,f)  ((tty)->termios.c_lflag & f)
#define _I_FLAG(tty,f)  ((tty)->termios.c_iflag & f)
#define _O_FLAG(tty,f)  ((tty)->termios.c_oflag & f)

#define L_CANON(tty)    _L_FLAG((tty),ICANON)
#define L_ISIG(tty)     _L_FLAG((tty),ISIG)
#define L_ECHO(tty)     _L_FLAG((tty),ECHO)
#define L_ECHOE(tty)    _L_FLAG((tty),ECHOE)
#define L_ECHOK(tty)    _L_FLAG((tty),ECHOK)
#define L_ECHOCTL(tty)  _L_FLAG((tty),ECHOCTL)
#define L_ECHOKE(tty)   _L_FLAG((tty),ECHOKE)

#define I_UCLC(tty)  _I_FLAG((tty),IUCLC)
#define I_NLCR(tty)  _I_FLAG((tty),INLCR)
#define I_CRNL(tty)  _I_FLAG((tty),ICRNL)
#define I_NOCR(tty)  _I_FLAG((tty),IGNCR)

#define O_POST(tty)   _O_FLAG((tty),OPOST)
#define O_NLCR(tty)   _O_FLAG((tty),ONLCR)
#define O_CRNL(tty)   _O_FLAG((tty),OCRNL)
#define O_NLRET(tty)  _O_FLAG((tty),ONLRET)
#define O_LCUC(tty)   _O_FLAG((tty),OLCUC)


#define TTY_BUF_SIZE 1024

// Contador de linhas usados na hora da criação de linhas.
int ttyLineCounter;

// Cursor.
int ttyCurrentX;
int ttyCurrentY;

/*
struct ttybuffer_d
{
    int used;
    int magic;

    // #importante:
    // Usaremos um stream sem  nome para gerenciar a 
    // área de memória que a tty precisa como buffer.
 
    file *stream;

    struct ttybuffer_d *next;
};
struct ttybuffer_d *CurrentTTYBUFFER;
*/

struct tty_line_d
{
    //int index;

    char CHARS[80];
    char ATTRIBUTES[80];  //Isso poderia ser unsigned long.	

    // Início e fim da string dentro da linha. O resto é espaço.
    int left;
    int right;

    //Posição do cursor dentro da linha.
    int pos;
};


struct tty_queue 
{
    // Quantidade de bytes dentro do buffer.
    // Se colocar mais isso aumenta, se retirarmos, isso diminui.
    int cnt;

    unsigned long head;
    unsigned long tail;

    // Vamos acordar as threads que estão nessa lista.
    // é uma lista encadeada de processo esperando nesse tipo de fila.
    struct thread_d *thread_list;

    char buf[TTY_BUF_SIZE];
};


/*
 * tty_d:
 *     The tty structure need to have a pointer to
 * a buffer and a pointer to a thread. These is the where
 * we're gonna send the data.
 */
// estrutura para tty
// uma estrutura de tty deve estar associado a
// uma janela de terminal virtual.

struct tty_d
{

//
// == Identification =============
//
    object_type_t  objectType;
    object_class_t objectClass;
    
// In the TTYs table?
    int index;
    int used;
    int magic;

// tty name
    char name[64];      // 
    size_t Name_len;    // len 

    int initialized;

//
// == (1) storage ========
//

// The buffer. The box.

//
// Buffers.
//

// If the buffer are used or not.
// options: TRUE, FALSE.
    int nobuffers;

// Canonical. (cooked mode)
// Applications programs reading from the terminal 
// receive entire lines, after line editing has been 
// completed by the user pressing return.

    struct tty_queue raw_queue;        // Raw input buffer.
    struct tty_queue canonical_queue;  // Canonical buffer.

    struct tty_queue output_queue;     // Output buffer.

//
// == (2) synchronization ========
//

// Flag para sincronizaçao de leitura e escrita de eventos.
    int new_event;

// Synch and job control.
// This way the TTY driver can send the input to the forground process.

// If a process try to write in a stopped TTY it will be blocked.
    int stopped;
    
    //int lock;

// Owner process.
    struct process_d *process;

// #todo: Process group?
    //int pgrp;

// #todo: merge?
// Thread de input.
    struct thread_d *thread;
// Control thread;
    struct thread_d *control;

//
// == (3) transmition ========
//

// The pipe fd, the socket fd, the read write operation.

    file *_fp;    

//linked socket?
    struct tty_d *link;

//
// == Device info ==================
//

// Device.
    //struct device_d *device;
    struct ttydrv_d *driver;

// i don't like this
// line discipline
    struct ttyldisc_d *ldisc;

// termios
    struct termios termios;

//
// == Security ============================================
//

// What is the user logged in this terminal?
    struct user_info_d *user_info;

// Security?
// user session, room, desktop;
    struct usession_d  *user_session;
    struct room_d      *room;
    struct desktop_d   *desktop;
// ===================================================

// process group.
// Usando quanto tiver uma interrupção de tty.
// Quais processos estão no mesmo grupo quanto tiver a interrupção.
// Vamos sinalizá-los.
    gid_t gid;

// ??
// Quantos processos estao usando essa tty.
    int pid_count;
//=========================


//
// ==  properties ========================
//

// Qual eh o modo de operacao do terminal virtual.
// graphics, text ...
    //int vt_mode;

// Qual eh o modo de operacao do console virtual.
// graphics, text ...
    int vc_mode;

    short type;       // type of tty
    short subtype;    // subtype of tty 
    
    unsigned long flags;        // tty flags.   

//
// == Actions ==============
//

// Qual terminal virtual esta usando essa tty.
    int virtual_terminal_pid;

// Window.
// When we are using the kgws.
    //struct window_d  *window;

//
// system metrics.
//
    
// cursor dimentions in pixel.
    unsigned long cursor_width_in_pixels;
    unsigned long cursor_height_in_pixels; 

// Char support.
// bg and fg colors.
    unsigned int bg_color;
    unsigned int fg_color;

//
// Print support
//

    // print position in chars.
    unsigned long cursor_x;
    unsigned long cursor_y;

    int fullscreen_flag;

    // margin in chars.
    unsigned long cursor_left;     // margem esquerda dada em linhas
    unsigned long cursor_top;      // margem superior dada em linhas
    unsigned long cursor_right;    // margem direita dada em linhas
    unsigned long cursor_bottom;   // margem inferior dada em linhas

    //
    // == Connection ===========================
    //
    
    // pty associa a tty 'to' com a tty 'from'
    // master/slave.

    // navigation
    // ?? estamos pensando nisso.
    // struct tty_d *next;
};

//
// == consoles ==================
//

// Index
extern int fg_console;

// Consoles virtuais
// Consoles virtuais em full screen.
// Criados a unha pelo kernel.

#define CONSOLETTYS_COUNT_MAX    4
//#define CONSOLETTYS_COUNT_MAX    8


// #importante:
// #todo
// #bugbug
// Aqui no Gramado X, funcionou sem 'static' e não funcionou com 'static'.
// Talvez devamos usar sem o 'static', assim como fazemos em outros
// modulos do kernel base.

//static struct tty_d CONSOLE_TTYS[8];
struct tty_d CONSOLE_TTYS[8];


// == prototypes ===============================================


int 
__tty_read ( 
    struct tty_d *tty, 
    char *buffer, 
    int nr );

int 
__tty_write ( 
    struct tty_d *tty, 
    char *buffer, 
    int nr );

int 
tty_read ( 
    int fd, 
    char *buffer, 
    int n );

int 
tty_write ( 
    int fd, 
    char *buffer, 
    int n );


void tty_reset_termios ( struct tty_d *tty );
struct tty_d *tty_create(void);


struct tty_d *file_tty (file *f);
int tty_delete ( struct tty_d *tty );
void tty_flush( struct tty_d *tty );
void tty_start (struct tty_d *tty);
void tty_stop (struct tty_d *tty);

int 
tty_gets ( 
    struct tty_d *tty, 
    struct termios *termiosp );

int 
tty_sets ( 
    struct tty_d *tty, 
    int options, 
    struct termios *termiosp );

int tty_init_module (void);


int 
tty_ioctl ( 
    int fd, 
    unsigned long request, 
    unsigned long arg );



#endif    
























