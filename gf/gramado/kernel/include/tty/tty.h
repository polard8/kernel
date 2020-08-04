/*
 * File: tty.h 
 * Header para o gerenciado de fluxo de caractere.
 */

#ifndef ____TTY_H
#define ____TTY_H

 

#define TTYCHARS_COUNT_MAX 25    //80 
#define TTYLINES_COUNT_MAX 25    //25 


//#define DEVELOPER_TTYCHARS_MAX 25    //80
//#define DEVELOPER_TTYLINES_MAX 25    //25 
//... 



/* tty magic number */
//#define TTY_MAGIC		0x5401
#define TTY_MAGIC		1234



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


 
//Contador de linhas usados na hora da criação de linhas.
int ttyLineCounter;

//Cursor.
int ttyCurrentX;
int ttyCurrentY;



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



//estrutura para tty
//uma estrutura de tty deve estar associado a
//uma janela de terminal virtual.

struct tty_d
{
    object_type_t  objectType;
    object_class_t objectClass;

    int index;

    int used;
    int magic;

    // device driver, line discipline and termios.

    //#todo: Indice do dispositivo.
    //int device;
    
    struct ttydrv_d *driver;
    
    struct ttyldisc_d *ldisc;
    
    struct termios termios;

    
    // #importante
    // Esse é o arquivo que aponta para essa estrutura.
    file *_fp;

    char __ttyname[64];    // 
    size_t ttyName_len;    // len 
    

    // process group.
    // Usando quanto tiver uma interrupção de tty.
    // Quais processos estão no mesmo grupo quanto tiver a interrupção.
    // Vamos sinalizá-los.
    int pgrp;
    
    // linux-like
    short type;       // type of tty
    short subtype;    // subtype of tty 
    int flags;        // tty flags.   
    
    
    //talvez;
    //int device_number;
    
    
    //status
    int stopped;


	//
	// User
	//

    struct user_info_d *user_info;


    // Security
    // user session, room, desktop;
    struct usession_d  *user_session;
    struct room_d      *room;
    struct desktop_d   *desktop;

    // Window.
    // When we are using the kgws.
    struct window_d *window;

    // ??
    // Quantos objetos associados a essa tty?
    int count;

    // id do terminal associado a essa tty.
    int terminal_id;  //tdo deletar.
    int terminal_pid;  //todo: usar esse



    // Owner process.
    struct process_d *process;

    // Thread de input.
    struct thread_d *thread;

    //
    // Buffers.
    //

    // Standard stream
    file *stdin;
    file *stdout;
    file *stderr;


    // Canonical. (cooked mode)
    // Applications programs reading from the terminal 
    // receive entire lines, after line editing has been 
    // completed by the user pressing return.

    // Raw input buffer.
    // Canonical buffer.

    file *_rbuffer;
    file *_cbuffer;


	//
	// Print support
	//
	
	// De onde começar a pintar
	// depois da libc ter colocado caracteres no arquivo. 

    //unsigned char *stdin_last_ptr;
    //unsigned char *stdin_limit;
    unsigned char *stdout_last_ptr;
    unsigned char *stdout_limit;
    unsigned char *stderr_last_ptr;
    unsigned char *stderr_limit;


	// status
	// 0 = não repinte stdout no tty atual
	// 1 = repinte stdout no tty atual
    int stdout_status;
    int stdout_update_what; //char, linha, coluna.

    int print_pending;

    int LinMax;
    int ColMax;
    int FullScreen;    //flag.


	//informações básicas sobre o retângulo
    unsigned long left; 
    unsigned long top;
    unsigned long width;
    unsigned long height;
 
    //cursor support.
    unsigned long cursor_x;
    unsigned long cursor_y;
    unsigned long cursor_width;    //??
    unsigned long cursor_height;   //??

    unsigned long cursor_left;     // margem esquerda dada em linhas
    unsigned long cursor_top;      // margem superior dada em linhas
    unsigned long cursor_right;    // margem direita dada em linhas
    unsigned long cursor_bottom;   // margem inferior dada em linhas

    unsigned long cursor_color;
    

	//linha atual da lista abaixo.
    int current_line;

	// Organizando as linhas dentro do TTY.	
	//Lista de ponteiros de estrutura de linha (tty_line_d)
    unsigned long lines[32];
    
    
    //#todo
    //struct ttybuffer_d *buffer;



    //in support
    //unsigned long IN[320];
    //int head; //coloca.
    //int tail; //pega.
	
	//out support	
	//unsigned long OUT[320];
	
	//continua ...
	
	//#obs: olhar o do minix
	
	//Id da janela do terminal virtual associado
	//ao tty
    //int windowID;
    
    //#test
    //canal de conexão; (network channel)
    struct channel_d *channel;
     
    // pty associa a tty 'to' com a tty 'from'
    // master/slave.
    struct tty_d *link;

};


// Consoles virtuais
// Consoles virtuais em full screen.
// Criados a unha pelo kernel.

//#define MAX_KERNEL_VIRTUAL_CONSOLES 4
int current_vc;
struct tty_d TTY[4];



//
// Pseudo terminais.
//

struct tty_d *CurrentTTY;


// Usado pelos aplicativos para criarem terminais virtuais.
// Criadas com ponteiros e alocadas com kmalloc.
//int current_pts;


//#define TTY_COUNT_MAX 256
//unsigned long ttyList[256]; 


// Get the tty pointer.
//OUT: tty pointer.
struct tty_d *file_tty (file *f);


struct ttyldisc_d *ttyldisc_create (void);  
int ttyldisc_delete ( struct ttyldisc_d *tty_ldisc );

struct ttydrv_d *ttydrv_create (void); 
int ttydrv_delete ( struct ttydrv_d *tty_driver );


struct tty_d *tty_create (void); 
int tty_delete ( struct tty_d *tty );





/*
int pty_write(struct tty_d *tty, const char *buf, int c);
int pty_write(struct tty_d *tty, const char *buf, int c)
{}
*/



void tty_stop (struct tty_d *tty);
void tty_start (struct tty_d *tty);


int 
tty_gets ( 
    struct tty_d *tty, 
    struct termios *termiosp );

int 
tty_sets ( 
    struct tty_d *tty, 
    int options, 
    struct termios *termiosp );


// Channel is a fd in the open file list of a process.
int 
tty_read ( 
   int fd, 
   char *buffer, 
   int n );


// Channel is a fd in the open file list of a process.
int 
tty_write ( 
    int fd, 
    char *buffer, 
    int n );



int 
__tty_read ( 
    struct tty_d *tty, 
    char *buffer, 
    int nr );

int 
__tty_write ( struct tty_d *tty, 
              char *buffer, 
              int nr );



int tty_ioctl ( int fd, unsigned long request,  unsigned long arg );

void tty_reset_termios ( struct tty_d *tty );



// Escreve na tty de um processo alvo e envia uma mensagem pra
// ele saber o que fazer com o que ele ler no buffer.
// Talvez seja possível fazer o mesmo
// em outros modulos, esses mesmos argumentos mais outros.
// Essa rotina dentro do kernel copia os dados que estão num buffer 
// para dentro do buffer da tty e em seguida envia um alerta para um 
// processo alvo, dizendo que ele tem dados no buffer de sua tty. 
// Os últimos argumentos são enviados para o processo na hora do alerta 
// pra dizer pra ele que tipo de dados tem no buffer e o que deve 
// fazer com eles.
// ---
// Da pra enviar todo tipo de coisa, pois o buffer é do tamanho que 
// você quizer. Inclusive da pra enviar protocolos de rede.

int 
tty_send_message ( 
    int target_pid, 
    char *buffer, 
    int nr,
    int msg,
    unsigned long long1,
    unsigned long long2 ); 


int tty_init_module (void);


#endif


//
// End.
//




