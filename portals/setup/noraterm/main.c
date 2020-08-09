/*
 * File: main.c 
 *
 * Client side terminal app for gde project.
 *
 * History:
 *     2016 - Created by Fred Nora.
 *     2019 - .
 */
 
 
// #importante
// O terminal pega as teclas digitadas e envia elas para
// um arquivo que o shell poderá ler.
// Então o stdout do terminal será lido pelo child.


// See:
// https://www.mkssoftware.com/docs/man5/struct_termios.5.asp
// https://invisible-island.net/xterm/ctlseqs/ctlseqs.html#h2-PC-Style-Function-Keys
// https://en.wikipedia.org/wiki/ANSI_escape_code 
// https://en.wikipedia.org/wiki/C0_and_C1_control_codes
// https://vt100.net/docs/vt220-rm/table2-4.html
// http://notes.burke.libbey.me/ansi-escape-codes/
// http://jafrog.com/2013/11/23/colors-in-terminal.html
// https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
// https://tforgione.fr/posts/ansi-escape-codes/



//ja deve ter sido definodo em outro lugar.
//#define RESPONSE "\033[?1;2c"     
     
     

/*
Style	Code
Bold	        \x1B[1m
Faint	        \x1B[2m
Italic	        \x1B[3m
Underlined	    \x1B[4m
Inverse	        \x1B[7m
Strikethrough	\x1B[9m
 */
 
 
/*
Effect	Code
Goes back one character	\b
Moves one line up	\x1B[A
Moves n lines up (replace N by the number of lines)	\x1B[NA
Goes back to the begining of the line	\r
Goes back to the begining of the previous line	\x1B[F
Goes back to the begining of the n-th previous line (replace N by the number of lines)	\x1B[NF
Erases the whole line	\x1B[2K  
 */ 
 

// Iniciando sequências.
//Shell 	    \e
//ASCII Hex 	\0x1B
//ASCII Oct 	\033

#define __ESC "\x1b"
#define __CSI "\x1b["


/*
 Numpad & Function Keys
Key 	Sequence
Backspace 	0x7f (DEL)
Pause 	0x1a (SUB)
Escape 	0x1b (ESC)
Insert 	ESC [ 2 ~
Delete 	ESC [ 3 ~
Page Up 	ESC [ 5 ~
Page Down 	ESC [ 6 ~
F1 	ESC O P
F2 	ESC O Q
F3 	ESC O R
F4 	ESC O S
F5 	ESC [ 1 5 ~
F6 	ESC [ 1 7 ~
F7 	ESC [ 1 8 ~
F8 	ESC [ 1 9 ~
F9 	ESC [ 2 0 ~
F10 	ESC [ 2 1 ~
F11 	ESC [ 2 3 ~
F12 	ESC [ 2 4 ~
 */

 
/* 
Single-character functions
BEL       Bell (Ctrl-G).
BS        Backspace (Ctrl-H).
CR        Carriage Return (Ctrl-M).
ENQ       Return Terminal Status (Ctrl-E).  Default response is an empty
          string, but may be overridden by a resource answerbackString.
FF        Form Feed or New Page (NP).  (FF  is Ctrl-L).  FF  is treated
          the same as LF .
LF        Line Feed or New Line (NL).  (LF  is Ctrl-J).
SI        Switch to Standard Character Set (Ctrl-O is Shift In or LS0).
          This invokes the G0 character set (the default) as GL.
          VT200 and up implement LS0.
SO        Switch to Alternate Character Set (Ctrl-N is Shift Out or
          LS1).  This invokes the G1 character set as GL.
          VT200 and up implement LS1.
SP        Space.
TAB       Horizontal Tab (HT) (Ctrl-I).
VT        Vertical Tab (Ctrl-K).  This is treated the same as LF.
*/
 
 
 
 /*
Erase and kill:
Erase and kill processing occurs when either of two special characters, 
the ERASE and KILL characters is received. This processing affects data 
in the canonical input queue that has not yet been delimited by
a '\n' or EOF character. This un-delimited data makes up the current line.
The ERASE character deletes the last character in the current line if any. 
The KILL character deletes all data in the current line.
The ERASE and KILL characters have no effect if there is no data in the line
and are themselves never placed in the input queue.  
 */


/*
 Como o kernel envia mensagens para o terminal em user mode?
 
 The mechanism for delivering messages to the console is implemented by the 
 printk function, defined in kernel/printk.c. 
 The function uses vsprintf (defined in lib/vsprintf.c) to create a message 
 string, places the string in the circular buffer of kernel messages and 
 passes it to all active console devices if the priority of the message is 
 less than console_loglevel. 
*/ 


// #importante:
// O terminal não pinta, ele deve chamar o X para isso.
// > O xterm chama o X-server e o windows terminal chama o direct X.
	


// #importante:
// #todo
// SetTerminalPID()
// SetTerminalTID()
 

//#todo:
//ScrollScreen() e ScrollEntireScreen()
//ScrollRegion
//Abort() // se o terminal receber uma mensagem enquanto está criando
//as coisas do terminal, então ele pode abortar a criação de liberar os recursos.



// #bugbug
// O header principal não deve ser esse. deve ser noraterm.h.

#include "noraterm.h" 



//Credits: xterm.
/*
#ifdef USE_ANY_SYSV_TERMIO
#define TERMIO_STRUCT struct termio
#define ttySetAttr(fd, datap) ioctl(fd, TCSETA, datap)
#define ttyGetAttr(fd, datap) ioctl(fd, TCGETA, datap)
#define ttyFlush(fd)          ioctl(fd, TCFLSH, 1)
#elif defined(USE_POSIX_TERMIOS)
#define TERMIO_STRUCT struct termios
#define ttySetAttr(fd, datap) tcsetattr(fd, TCSANOW, datap)
#define ttyGetAttr(fd, datap) tcgetattr(fd, datap)
#define ttyFlush(fd)          tcflush(fd, TCOFLUSH)
#endif 
*/


//
// Modes.
//

//int __terminal_mode = 0;
//int __cursor_mode = 0;
//int __keypad_mode = 0;
//...

//#todo: fazer estrutura para gerenciar a sequencia.
int __sequence_status = 0;


#define TAB_SIZE 8



//
// CSI support
// 

//#test
//Control Sequence Introducer

#define CSI_BUFFER_SIZE 128
char CSI_BUFFER[ CSI_BUFFER_SIZE ];

int __csi_buffer_tail = 0;
int __csi_buffer_head = 0;


//
// Structures
//

//#importante
//vamos tentar copiar as estruturas usadas pelo terminal gramado/st

enum term_mode {
	MODE_WRAP	     = 1,
	MODE_INSERT      = 2,
	MODE_APPKEYPAD   = 4,
	MODE_ALTSCREEN   = 8,
	MODE_CRLF	     = 16,
	MODE_MOUSEBTN    = 32,
	MODE_MOUSEMOTION = 64,
	MODE_MOUSE       = 32|64,
	MODE_REVERSE     = 128,
	MODE_KBDLOCK     = 256,
	MODE_HIDE	     = 512,
	MODE_ECHO	     = 1024,
	MODE_APPCURSOR	 = 2048,
	MODE_MOUSESGR    = 4096,
};

enum escape_state {
	
	ESC_START = 1,
	ESC_CSI	= 2,
	ESC_STR	= 4,         /* DSC, OSC, PM, APC */
	ESC_ALTCHARSET = 8,
	ESC_STR_END = 16,    /* a final string was encountered */
	ESC_TEST = 32,       /* Enter in test mode */
	
};



// #importante
// Colocaremos aqui dentro elementos que apontem para
//variáveis que já usavamos antes de criarmos essa estrutura.
/* Internal representation of the screen */
typedef struct {
	
	//int row;	/* nb row */
	//int col;	/* nb col */
	//Line *line;	/* screen */
	//Line *alt;	/* alternate screen */
	//bool *dirty;	/* dirtyness of lines */
	//TCursor c;	/* cursor */
	//int top;	/* top    scroll limit */
	//int bot;	/* bottom scroll limit */
	int mode;	/* terminal mode flags */
	int esc;	/* escape state flags */
	//bool numlock;	/* lock numbers in keyboard */
	//bool *tabs;
} Term;

//Sem ponteiro.
static Term term;


#define ESC_BUF_SIZ 32 //(128*UTF_SIZ)
#define ESC_ARG_SIZ 16
#define STR_BUF_SIZ   ESC_BUF_SIZ
#define STR_ARG_SIZ ESC_ARG_SIZ


// 
// Escape sequence
//

/* CSI Escape sequence structs */
/* ESC '[' [[ [<priv>] <arg> [;]] <mode>] */
typedef struct {

    char buf[ESC_BUF_SIZ];    /* raw string */
    int len;                  /* raw string length */
    char priv;
    int arg[ESC_ARG_SIZ];
    int narg;                 /* nb of args */
    char mode;

} CSIEscape;

static CSIEscape csiescseq;



/* STR Escape sequence structs */
/* ESC type [[ [<priv>] <arg> [;]] <mode>] ESC '\' */
typedef struct {
	char type;	     /* ESC type ... */
	char buf[STR_BUF_SIZ]; /* raw string */
	int len;	       /* raw string length */
	char *args[STR_ARG_SIZ]; // ponteiro duplo.
	int narg;	      /* nb of args */
} STREscape;
static STREscape strescseq;



/*
 * credits: linux 0.1.
 * this is what the terminal answers to a ESC-Z or csi0c
 * query (= vt100 response).
 */
#define RESPONSE "\033[?1;2c"

#define VT102_ID "\033[?6c"


//
// Windows.
//

//main window
struct window_d *main_window;

//client area.
struct window_d *client_background_window;
struct window_d *client_window;

// bar 
struct window_d *client_bar_Window;
struct window_d *bar_button_1; 
struct window_d *bar_button_2;
struct window_d *bar_button_3;
    
//...



// Input flags.
#define SHELLFLAG_NULL 0
#define SHELLFLAG_COMMANDLINE 1
#define SHELLFLAG_SCRIPT 2
#define SHELLFLAG_HELP 3
#define SHELLFLAG_VERSION 4
#define SHELLFLAG_USAGE 5
#define SHELLFLAG_TOPBAR 6
#define SHELLFLAG_FEEDTERMINAL 7
#define SHELLFLAG_EXIT 8
//...



#define LINE_BUFFER_SIZE 1024
char LINE_BUFFER[LINE_BUFFER_SIZE];
int line_buffer_tail;  //entrada.
int line_buffer_head;  //saída.
int line_buffer_buffersize;
//...
 


// _init_app 
// 1 = tente inicializar o programa que vai rodar no terminal
// 0 = Inicialine o shell interno para gerenciamento do terminal.

//int _init_app = 1;
int _init_app = 0;   // >>> usado para debug.

//
// ======== ## Shell Flag ## ========
//

int ShellFlag = 0;

//usar o shell embutido.
int __embedded_shell = 1;

//
// ======== ## Status support ## ========
//


int shellStatus = 0;
int shellError = 0;

//O shell está rodando.
int running = 1;

/* Non-zero when we are executing a top-level command. */
//o shell está executando um comando que está emprimeiro plando.
int executing = 0;




//
// ======== ## Arguments support  ## ========
//

/* The name of this shell, as taken from argv[0]. */
char *shell_name;

//Se o shell vai rodar um script e não é interativo.
//é acionado com a flag em argv[1]  '-f'
int script_shell = 0;

/* The name of this shell, as taken from argv[2]. */
char *script_name;


/* Non-zero means this shell is running interactively. */
//Se for diferente de zero então esse shell é interativo.
//Se for zero ele pode apenas estar executando um script.
int interactive = 0;

/* Non-zero means that this shell is a login shell.
   Specifically:
   0 = not login shell.
   1 = login shell from getty (or equivalent fake out)
  -1 = login shell from "-login" flag.
  -2 = both from getty, and from flag.
 */
//Se o shell vai ser usado para login.
//Obs: Uma variável no kernel guardo o id do processo 
//que fez login. 
int login_shell = 0;


// #todo: 
// Nesse modo o servidor shell.bin não abrirá janelas,
// apanas inicializará os recursos do gws.

int headless;

// Show the task bar.
int taskbar = 0;

// GWS mode;
// O shell funcionará apenas como um servidor de recursos gráficos em ring3.
int gws = 0;

// modo desktop
int desktop = 0;


//
// ======== ## Login support ## ========
//

int login_status = 0;

char username[11];
char password[11];
//char *username;
//char *password; 



//
// ======== ## Prompt support ## ========
//

//coisa de shell
#ifndef PPROMPT
#define PPROMPT "shell\\$ "
#endif
char *primary_prompt = PPROMPT;


//coisa de shell
#ifndef SPROMPT
#define SPROMPT "shell> "
#endif
char *secondary_prompt = SPROMPT;


//
// ======== ## Version support ## ========
//

char *dist_version;
char *build_version; /*revision*/


//
// ======== ## ## ========
//


//
// ======== ## ## ========
//


//
// ======== ## Commands support ## ========
//

COMMAND *global_command = (COMMAND *) NULL;


//
// ======== ## Outros ## ========
//

// #importante
// As variáveis aqui pertencem ao bash,
// estamos tentando aproveitá-las.

int mainwindow_used = 1;

/* Non-zero after SIGINT. */
int interrupt_state = 0;

/* The current user's name. */
char *current_user_name = (char *) NULL;

/* The current host's name. */
char *current_host_name = (char *) NULL;


/* Non-zero means to remember lines typed to the shell on the history
   list.  This is different than the user-controlled behaviour; this
   becomes zero when we read lines from a file, for example. */
int remember_on_history = 1;


/* Non-zero means this shell is restricted. */
int restricted = 0;

/* Special debugging helper. */
int debugging_login_shell = 0;


/* The environment that the shell passes to other commands. */
//O ambiente que o shell passa para 
//o comando que ele executou.
char **shell_environment;


/* The number of commands executed so far. */
int current_command_number = 1;


/* Non-zero is the recursion depth for commands. */
int indirection_level = 0;


/* The number of times BASH has been executed.  This is set
   by initialize_variables () in variables.c. */
int shell_level = 0;


/* The name of the .(shell)rc file. */
char *bashrc_file = "~/.bashrc";

/*nome do arquivo de configuração*/
char *shell_config_file = "./shellcnf.txt";


/* Non-zero means to act more like the Bourne shell on startup. */
int act_like_sh = 0;



/* Values for the long-winded argument names. */
int debugging = 0;		/* Do debugging things. */
int no_rc = 0;			/* Don't execute ~/.bashrc */
int no_profile = 0;		/* Don't execute .profile */
int do_version = 0;		/* Display interesting version info. */
/* Be quiet when starting up. */
//inicialização silenciosa. Suprime alguns verboses.
int quiet = 0;	
int make_login_shell = 0;	/* Make this shell be a `-bash' shell. */
int no_line_editing = 0;	/* Don't do fancy line editing. */
int no_brace_expansion = 0;	/* Non-zero means no foo{a,b} -> fooa fooa. */




//
// ======== ## bash Arguments support ## ========
//

// #obs
// Não sei se estamos usando isso.

// ??
//é semelhante à estrutura acima.
/* Some long-winded argument names.  These are obviously new. */
// Argumentos.
#define Int 1
#define Charp 2
struct 
{
    char *name;
    int *value;
    int type;
	
} long_args[] = {
	
    { 
        "debug", 
        &debugging, 
		Int 
	},
    
	{ 
	    "norc", 
		&no_rc, 
		Int 
	},
	
    { 
	    "noprofile", 
		&no_profile, 
		Int 
	},
	
    { 
	    "rcfile", 
		(int *) &bashrc_file, 
		Charp
	},
	
    { 
	    "version", 
		&do_version, 
		Int
	},
	
    { 
	    "quiet", 
		&quiet, 
		Int
	},
	
    { 
	    "login", 
		&make_login_shell, 
		Int
	},
    
	{ 
	    "nolineediting", 
		&no_line_editing, 
		Int
	},
	
    { 
	    "nobraceexpansion", 
		&no_brace_expansion, 
		Int
	},
	
    { 
	    (char *) NULL, 
		(int *) 0x0, 
		0 
	}
  
};


//... 


/*
//argument buffer
char **argbuf;
int argbuf_length;
int argbuf_index;
*/


//
// ======== ## Prototypes ## ======== 
//




// escreve um char no backbuffer e exibe na tela
// usando o cursor gerenciado pelo sistema,
void terminal_write_char ( int c);

void terminalInitSystemMetrics ();

void terminalInitWindowLimits ();

void terminalInitWindowSizes ();

void terminalInitWindowPosition ();

void csidump (void);
void csireset (void);
void strdump(void);
void strreset (void);

void techo(char *buf, int len);
void tputc (char *c, int len);
int print_buffer (void);
void initialize_buffer (void);

// #todo:
// Se possível, colocar essas rotinas em tests;c




void die (char * str);
void error ( char *msg, char *arg1, char *arg2 );
void fatal ( char *msg, char *arg1, char *arg2 );
char *concat ( char *s1, char *s2, char *s3 );
char *save_string ( char *s, int len );
int shell_save_file ();
int save_string2 ( char string[], char file_name[] );




int
__PostMessageToProcess ( int pid, 
                          struct window_d *window, 
                          int message,
                          unsigned long long1,
                          unsigned long long2 );



//diálogo para alimentar o terminal usado pelos aplicativos.
int feedterminalDialog( struct window_d *window, 
                      int msg, 
				      unsigned long long1, 
				      unsigned long long2 );



int process_input ();




// Procedimento de janela principal do aplicativo.
void *noratermProcedure ( struct window_d *window, 
                          int msg, 
                          unsigned long long1, 
                          unsigned long long2 );


void terminal_test_write ();
// ...


//
// ======== ## Internal functions ## ========
//




				// Write a char in the current line buffer.
				// >> Isso é chamado quando um printf na libc03 
				// encontra um \n.
				// Isso indica que o terminal tem chars na 
				// stream da tty (CurrentTTY), então ele deve 
				// pegar e exibir.
				// Pega um char, mas não é o último que foi colocado, 
				// é o que ainda não foi pego.
				// #todo: 
				// O terminal deve configurar qual stream ele quer 
				// pegar bytes.

// int xxx_ch;
// serviço 2008;
void handle_notification(void)
{
    int xxx_ch;
				//case 2008:

					// Inicializa o 'line buffer' e não o buffer de texto.
					initialize_buffer();
					
					// Pegando chars no arquivo. CurrentTTY->stdout;
					// See: gde_serv.c in the base kernel.
					// Isso lê no buffer da tty CurrentTTY.
					// >> Mas poderia ser alguma stream passada 
					// para o processo filho na hora de clonar.
                    while (1)
                    {
                        xxx_ch = (int) gramado_system_call ( 1002, 0, 0, 0 );

                        // Chegamos no fim do arquivo antes de 
                        // acabar a sring?
                        // Mostre o buffer e sinalize o erro.
                        if (xxx_ch == EOF )
                        {
                            print_buffer ();
                            gde_message_box ( 3, 
                                "noraterm", 
                                "#bugbug: case 2008 - EOF");
                            exit (1);
                        }

                        // Chegamos no fim da string.
                        // Mostre a string e continue.
                        if (xxx_ch == '\0')
                        {
                            print_buffer ();
                            break;
                        }


                        // Encontramos um \n em uma string.
                        // Mostre o buffer e continue.
                        if (xxx_ch == '\n')
                        {
                            //printf ("noraterm: EOL, flush me\n");
                            print_buffer ();

                        // Ainda não encontramos  \n nem \0, 
                        // continue colocando no buffer.
                        }else{

                            // #importante:
                            // Colocar o char no buffer
                            LINE_BUFFER[line_buffer_tail++] = (char) xxx_ch;

                            if ( line_buffer_tail >= line_buffer_buffersize )
                            {

							    //LINE_BUFFER[line_buffer_tail--] = 0; //FINALIZA;
							    //line_buffer_tail = 0;

                                //isso vai inicializar o buffer,
								print_buffer ();
								
							    //printf ("noraterm: buffer limits, flush me\n"); 
								//MessageBox (3, "noraterm","buffer limit");
							    //break;
						    }
                       };
                    };
                    //break;
}




/*
void __respond (void)
{
}
*/

void terminal_test_write ()
{
}


int
__PostMessageToProcess ( int pid, 
                         struct window_d *window, 
                         int message,
                         unsigned long long1,
                         unsigned long long2 )
{
    unsigned long message_buffer[5];

    if (pid<0)
        return -1;

    message_buffer[0] = (unsigned long) window;
    message_buffer[1] = (unsigned long) message;
    message_buffer[2] = (unsigned long) long1;
    message_buffer[3] = (unsigned long) long2;

	//...

    return (int) system_call ( 112 , (unsigned long) &message_buffer[0], 
                    (unsigned long) pid, (unsigned long) pid );
}


void quit ( int status ){
	
	running = 0;
}


/*
 *  pause:
 */

static inline void pause (void){
	
    asm volatile ("pause" ::: "memory"); 
}; 


/* 
 * rep_nop:
 *     REP NOP (PAUSE) is a good thing to insert into busy-wait loops. 
 */

static inline void rep_nop (void){
	
    asm volatile ("rep;nop" :::"memory");
};
#define cpu_relax()  rep_nop()

 
 
/*
 ***********************  
 * process_input:
 * 
 */
 
//main loop
//pegamos a mensagem e enviamos para o procedimento de janela.
//essa rotina poderia fazer parte da api ?? o problema é o 'running'

int process_input (){

	unsigned long message_buffer[16];
		
	int msg_status = 0;	

	// #obs: 
	// O retorno será 1 se tiver mensagem e 0 se não tiver.
	// message_buffer[1] será 0 se não tiver mensagem
	// Chamaremos o procedimento de janelas do aplicativo.

    while (running)
    {
		msg_status = host_get_message ( (unsigned long) &message_buffer[0] );
					
		// Se temos mensagem.
		if (msg_status != 0)
		{
            noratermProcedure ( (struct window_d *) message_buffer[0], 
                (int) message_buffer[1], 
                (unsigned long) message_buffer[2], 
                (unsigned long) message_buffer[3] );

            message_buffer[0] = 0;  //window
            message_buffer[1] = 0;  //msg
            message_buffer[3] = 0;  //long1
            message_buffer[4] = 0;	//long2
        };
    };


    return 0;
}



void csidump (void) {

    int i;
    unsigned int c;    //uint c; //?

    printf ("ESC[");

    for (i = 0; i < csiescseq.len; i++)
    {
        c = csiescseq.buf[i] & 0xff;

		if(isprint(c)) {
			putchar(c);
		} else if(c == '\n') {
			printf("(\\n)");
		} else if(c == '\r') {
			printf("(\\r)");
		} else if(c == 0x1b) {
			printf("(\\e)");
		} else {
			printf ("(%02x)", c);
		};
    };

    putchar ('\n');
}


void csireset (void){
    
    memset ( &csiescseq, 0, sizeof(csiescseq) );
}

void
strdump(void) {

	int i;
	unsigned int c;    //uint c;

	printf ("ESC%c", strescseq.type);

	for(i = 0; i < strescseq.len; i++)
	{
		c = strescseq.buf[i] & 0xff;
		
		if(c == '\0') {
			return;
		} else if(isprint(c)) {
			putchar(c);
		} else if(c == '\n') {
			printf("(\\n)");
		} else if(c == '\r') {
			printf("(\\r)");
		} else if(c == 0x1b) {
			printf("(\\e)");
		} else {
			printf("(%02x)", c);
		}
	}
	printf("ESC\\\n");
}


void strreset (void){
    
    memset ( &strescseq, 0, sizeof(strescseq) );
}


/*
//#todo:
void csiparse (void);
void csiparse (void) {
	
	char *p = csiescseq.buf, *np;
	long int v;

	csiescseq.narg = 0;
	if(*p == '?') {
		csiescseq.priv = 1;
		p++;
	}

	csiescseq.buf[csiescseq.len] = '\0';
	while(p < csiescseq.buf+csiescseq.len) {
		np = NULL;
		v = strtol(p, &np, 10);
		if(np == p)
			v = 0;
		if(v == LONG_MAX || v == LONG_MIN)
			v = -1;
		csiescseq.arg[csiescseq.narg++] = v;
		p = np;
		if(*p != ';' || csiescseq.narg == ESC_ARG_SIZ)
			break;
		p++;
	}
	csiescseq.mode = *p;
}
*/



void techo(char *buf, int len) {

    for(; len > 0; buf++, len--)
    {
		char c = *buf;

		if(c == '\033') {		/* escape */
			tputc("^", 1);
			tputc("[", 1);
		} else if(c < '\x20') {	/* control code */
			if(c != '\n' && c != '\r' && c != '\t') {
				c |= '\x40';
				tputc("^", 1);
			}
			tputc(&c, 1);
		} else {
			break;
		}
	};
	
	if(len)
		tputc (buf, len);
}


/*
 ***************** 
 * tputc:
 * 
 */

// #todo
// See: https://github.com/gramado/st/blob/tlvince/st.c

		// #Atenção: A libc do app foi configurada dinamicamente
		// para que printf coloque chars no arquivo. Mas 
		// a libc desse terminal ainda não foi. Então a printf
		// desse terminal escreve no backbuffer e exibe na tela.
        // #bugbug: O problema é que dessa forma nada foi colocado no buffer de arquivo.
        
//#todo
// fazer essa função colocar os chars no buffer de arquivo. Usaremos no scroll.

void tputc (char *c, int len){
	
	 //int c = (int) *c;
	 unsigned char ascii = *c;
	 
	 //control codes
	 //bool control = ascii < '\x20' || ascii == 0177;
     int control = ascii < '\x20' || ascii == 0177;
	 
	 
	 //
	 // #importante
	 // Se não é controle é string ou escape sequence.
	 //
	 
	 //??
	 //if(iofd != -1) {}
	 
	 //string normal
	 //if(term.esc & ESC_STR) 
	 if (__sequence_status == 0)
	 {
		 switch (ascii)
		 {
			 //deixou de ser string normal e
			 //entramos em uma sequência
			 //logo abaixo esse char será tratado novamente.
		     case '\033':
		         term.esc = ESC_START;
                 __sequence_status = 1;
                 break;
             
             
             //
             // #importante
             // 
             
             // Imprimindo caracteres normais.
             // #todo: talvez possamos usar a API para isso.
             // como acontece nos caracteres digitados no shell interno.
             default:
             
                 // #importante
                 // Isso vai exibir o caractere mas também
                 // na colocar ele no buffer ba posição atual.
                 
                 //printf ("%c",ascii);
                 terminal_write_char ( (int) ascii); 
                 return;
         }
	 }


	 //control codes. (dentro de um range)
	 if(control){
		 
		 switch(ascii)
		 {

		    //case '\v': /* VT */
		    //case '\a': /* BEL */    
		    		    		    
		    case '\t': /* HT */
		    case '\b': /* BS */
		    case '\r': /* CR */
		    case '\f': /* LF */
            case '\n': /* LF */
                //#deixa o kernel lidar com isso por enquanto.
                //printf ("%c",ascii);
                terminal_write_char ( (int) ascii);
                return;	
                break;
		    
		    //^[
		    //case '\e':
			//case '\033':
		    case '\x1b':
		        term.esc = ESC_START;
		        __sequence_status = 1;
		        //printf (" {ESCAPE} ");
		        terminal_write_char ( (int) '$');
		        return;
		        break;
		        
		    case '\016':	/* SO */
            case '\017': /* SI */
		        return;
		        break;
		        
		    case '\032':	/* SUB */
		    case '\030':	/* CAN */
			    //csireset ();
			    //printf (" {reset?} ");
                terminal_write_char ( (int) '$');
                return;
		        break;
		            
		    case '\005':	/* ENQ (IGNORED) */
		    case '\000':	/* NUL (IGNORED) */
		    case '\021':	/* XON (IGNORED) */
		    case '\023':	/* XOFF (IGNORED) */
		    //case 0177:	/* DEL (IGNORED) */
                //Nothing;
                return;
                
            //...    
		 }
		        
		 //...	 
		 
	 // Um 1b já foi encontrado.
	 } else if(term.esc & ESC_START) {
	 
	     // Um [ já foi encontrado.
	     //#todo parse csi
	     if(term.esc & ESC_CSI){
		      
		      switch(ascii)
		      {
		     	//quando acaba a sequencia.
		     	case 'm':
		     	    term.esc = 0;
			        __sequence_status = 0;
			        //printf (" {m} ");
			        terminal_write_char ( (int) '$');
			        return;
			        break;  
			     
			     //Nothing??
			     //case ';':
			         //return;
			         //break;
			         
			     //Vamos apenas colocar no buffer
			     //para analizarmos depois.
			     //Colocamos no tail e retiramos no head.
		         default:
		              //printf (" {.} ");
		              terminal_write_char ( (int) '$');
		              CSI_BUFFER[__csi_buffer_tail] = ascii;
		              __csi_buffer_tail++;
		              if ( __csi_buffer_tail >= CSI_BUFFER_SIZE )
		              {
						  __csi_buffer_tail = 0;
					  }
		              return;
		              break;
		      }
		 
		 } else if(term.esc & ESC_STR_END){ 
			 
			 
			 //...
	 
	     } else if(term.esc & ESC_ALTCHARSET){
			 
			 switch(ascii)
			 {
			      case 'A': /* UK (IGNORED) */
			      case '<': /* multinational charset (IGNORED) */
			      case '5': /* Finnish (IGNORED) */
			      case 'C': /* Finnish (IGNORED) */
			      case 'K': /* German (IGNORED) */
                      break;
			 }
			 
	     } else if(term.esc & ESC_TEST) {
			 
		    //...
		    	 
		 }else{
			
		   switch(ascii)
		   {
			 case '[':
			     term.esc |= ESC_CSI;
			     //printf (" {CSI} ");
			     terminal_write_char ( (int) '$');
			     return;
			     break; 
			       
			 case '#':
			     term.esc |= ESC_TEST;
			     break;
			
			case 'P': /* DCS -- Device Control String */
			case '_': /* APC -- Application Program Command */
			case '^': /* PM -- Privacy Message */
			case ']': /* OSC -- Operating System Command */
            case 'k': /* old title set compatibility */
			     term.esc |= ESC_STR;
			     break; 
			     
			case '(': /* set primary charset G0 */  
			    term.esc |= ESC_ALTCHARSET;
			    break;    
			    
			case ')': /* set secondary charset G1 (IGNORED) */
			case '*': /* set tertiary charset G2 (IGNORED) */
			case '+': /* set quaternary charset G3 (IGNORED) */
				term.esc = 0;
                __sequence_status = 0;
                break;  
                
                
             case 'D': /* IND -- Linefeed */
                 term.esc = 0;
                 //printf (" {IND} ");
                 terminal_write_char ( (int) '$');
                 break;
                 
             case 'E': /* NEL -- Next line */
                 term.esc = 0;
                 //printf (" {NEL} ");
                 terminal_write_char ( (int) '$');
                 break;
                        			
			   
			 case 'H': /* HTS -- Horizontal tab stop */  
                 term.esc = 0;
                 //printf (" {HTS} ");
                 terminal_write_char ( (int) '$');
                 break;
                 
 			 case 'M': /* RI -- Reverse index */    
                 term.esc = 0;
                 //printf (" {RI} ");
                 terminal_write_char ( (int) '$');
                 break;
                 
                 			     
			  case 'Z': /* DECID -- Identify Terminal */   
                 term.esc = 0;
                 //printf (" {DECID} ");
                 terminal_write_char ( (int) '$');
                 break;
                 
                 			 
			 case 'c': /* RIS -- Reset to inital state */
                 term.esc = 0;
                 //printf (" {reset?} ");
                 terminal_write_char ( (int) '$');
                 break; 
                 
			 case '=': /* DECPAM -- Application keypad */
                 term.esc = 0;
                 //printf (" {=} ");
                 terminal_write_char ( (int) '$');
                 break;
                 			 
			 case '>': /* DECPNM -- Normal keypad */
                 term.esc = 0;
                 //printf (" {>} ");
                 terminal_write_char ( (int) '$');
                 break;
                 			 
			 //case '7': /* DECSC -- Save Cursor */    
               //  term.esc = 0;
               //  break;
                 			   
			 //case '8': /* DECRC -- Restore Cursor */
               //  term.esc = 0;
                // break;
                 
			 //0x9C 	ST 	String Terminator ???
			 //case '\\': /* ST -- Stop */  
                 //term.esc = 0;
                 //break;	           
  
  			 //erro    
			 //default:
			     //break;          
		   }
		};	 
	    
	     //...
	     
	     return;
	 };
	 
	 //...
}



/*
 ********************************** 
 * print_buffer
 * 
 *     Print line buffer.
 * 
 */

//O buffer de linha está cheio.
//vamos mostrar na tela.

int print_buffer (void){

    int c;
    int i;

    int charsize = 1;    /* size of utf8 char in bytes */

	//int sequence_status = 0;
	

	
	//provisorio
    //printf (LINE_BUFFER); 
    
    // #bugbug: da pra medir um array? 

    size_t len = strlen (LINE_BUFFER);
    
   
    //#todo limits
    
    if ( len >= LINE_BUFFER_SIZE )
    {
        gde_message_box (3,"noraterm","print_buffer: buffer limit");
        return -1;
    }


    for (i=0; i<len; i++)
    {
		// See: Função interna. Logo acima.
		// uma rotian especial, pois vai tratar as escape sequencies. 
        // Desejamos que o caractere seja exibido na tela e
        // que entre no buffer de arquivo.        
        //IN: char, len
         tputc ( (char *) &LINE_BUFFER[i], (int) 1 );
    };

 
	terminal_write_char ( (int) '\n'); 
	 
	// Depois de lido o buffer podemos reinicali-lo.
	// Limpando só o buffer de linha. Não é o buffer de arquivo. 
    initialize_buffer();
	    
    return 0;	
}





/*
 ********************************** 
 * initialize_buffer 
 * 
 * 
 */

//
// Inicializando o buffer.
//

// #bugbug
// E o arquivo ??
// Em que momento o arquivo chega ao EOF ?

// #importante:
// Limpando só o buffer de linha. Não é o buffer de arquivo. 

void initialize_buffer (void){
	
	int i;
	
	for (i=0; i<LINE_BUFFER_SIZE; i++)
	{
		LINE_BUFFER[i] = 0;
	}
	
    line_buffer_tail = 0;  //entrada.
    line_buffer_head = 0;  //saída.
    
    line_buffer_buffersize = LINE_BUFFER_SIZE;	
}






//int bufferInsertChar();
//int bufferInsertChar(){}

/*
 ***********************************************
 * noratermProcedure:
 *     Procedimento de janela.
 *     LOCAL
 */

void *noratermProcedure ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{

    unsigned long input_ret=0;
    unsigned long compare_return=0;
    int q=0;
    int c=0;
     
    //usado no read()
    int ____this_tty_id = -1;
    char __rbuf2[128]; //line ? read 
    
    
	//#importante
	//Temos um ponteiro para o nosso buffer de argumentos
	//para as mensagens atendidas pelo servidor. 
	

	
	//if( msg == COMMAND_INITIALIZE_SHELL ){
		//...
	//}

    switch (msg)
    {

        case MSG_SYSKEYDOWN:
            //...
            switch (long1)
            {

                case VK_F1:
                    printf ("VK_F1:\n");

                    //pegando a tty desse processo pra poder ler.
                    ____this_tty_id = (int) gramado_system_call ( 266, getpid(), 0, 0 );
                    printf ("NORATERM: The tty for THIS process is %d \n", 
                          ____this_tty_id );

                
                    // lançando um processo filho.  
                    gramado_system_call ( 900, 
                        (unsigned long) "hello3.bin", 0, 0 );


				    //textCurrentCol++;
				    //terminalSetCursor ( textCurrentCol, textCurrentRow );
				    //MessageBox ( 3, "Noraterm", "F1" ); 
				    //shellSendMessage ( NULL, MSG_TERMINALCOMMAND, 2008, 0);
		            //printf ("*SCROLL\n");
		            //terminal_scroll_display ();
		            //shellPrompt ();
                    break;


				//posiciona na proxima linha
				case VK_F2:

                    printf ("VK_F2:\n");
  
                    //pegando a tty desse processo pra poder ler.
                    ____this_tty_id = (int) gramado_system_call ( 266, getpid(), 0, 0 );
                    printf ("NORATERM: The tty for THIS process is %d \n", 
                          ____this_tty_id );


                    //read_ttyList ( ____this_tty_id, __rbuf2, 32 );  
                    printf (__rbuf2);
                    printf("VK_F2: =)\n");
                    fflush(stdout);

				    //textCurrentRow++;
				    //terminalSetCursor ( textCurrentCol, textCurrentRow );
					//MessageBox ( 3, "Noraterm", "F2" );
					//shellSendMessage ( NULL, MSG_TERMINALCOMMAND, 2020, 0);
					break;

                //posiciona no início da linha atual 
				case VK_F3:
				    textCurrentCol = 0;
				    terminalSetCursor ( 0, textCurrentRow );
				    //testChangeVisibleArea();
				    //terminalRefreshVisibleArea();
					//textSetCurrentRow ( (int) 0 );
					//textSetCurrentCol ( (int) 0 );
					//shellTestLoadFile ();
					//inicializa a área visível.
					//textTopRow = 0;
	                //textBottomRow = 0 + 24;
					break;

				//posiciona no inpicio da área de cliente.	
				case VK_F4:
				    terminalSetCursor ( 0, 0 );
				    break;

                // #Caution
                // f5,f6,f7,f8 belongs to the kernel.
                // Do not touch'em!


                case VK_F9:
                    debug_print("F9");
                    //MessageBox ( 3, "Noraterm", "F9" );
                    shellSendMessage ( NULL, MSG_TERMINALCOMMAND, 2009, 0);
                    break;
                    
                case VK_F10:
                    //MessageBox ( 3, "Noraterm", "F10" );
                    //shellSendMessage ( NULL, MSG_TERMINALCOMMAND, 2020, 0);
                    //updateVisibleArea (0);
                    //terminal_scroll_display ();
                    terminal_scroll_down (); //funcionou.
                    break;
                
                //full screen
                //colocar em full screen somente a área de cliente. 
		        case VK_F11:
		            //MessageBox ( 3, "Noraterm", "F11" );
					//shellSendMessage ( NULL, MSG_TERMINALCOMMAND, 2020, 0);
					//updateVisibleArea (1);
					//terminal_scroll_display ();
					terminal_scroll_up ();
					break;
					
				case VK_F12:
				    //MessageBox ( 3, "Noraterm", "F12" );
				    //shellSendMessage ( NULL, MSG_TERMINALCOMMAND, 2020, 0);
				    terminal_write_char ('A');
				    //terminalNewVisibleArea (0, 15); //fazer isso uma  vez.
				    terminalNewVisibleArea (0, 20); //fazer isso uma  vez.
				    break;
				
				//...

            };
            goto done;
            break;

		//Obs:
		//essas teclas são tratadas pelo procedimento do sistema.
		//mas alguma tecla personalizada pode ser  tratada pelo aplicativo,
		//como o context menu [Application Key]
		case MSG_SYSKEYUP:
            switch (long1)
			{		
				//O MENU APPLICATION É O CONTEXT MENU.
				case VK_APPS:
				    gde_message_box ( 3, 
				        "noraterm:", "VK_APPS Context Menu" );
					break;
            };
            goto done;
            break;

 
        case MSG_KEYDOWN:
            switch (long1)
            {
				//EOF
				//case -1:
				//    #todo
				//    break;
				
				// Null key.
				case 0:
					pause ();
					cpu_relax ();
				    return NULL;
				    break;
				
				// Enter.
				// Finaliza a string e compara.
				case VK_RETURN:
				    //se temos um shell embutido
				    //if ( __embedded_shell == 1)
					//{
					    terminal_write_char ((int) '\r');
					    terminal_write_char ((int) '\n');
				        input ('\0'); 
				        
				        
				        printf ("Sending ...\n");
				        // #nesse momento devemos enviar o conteúdo do
				        // prompt[] para um lugar onde outro aplicativo possa pegar.
					    // vamos enviar para CurrentTTY->stdout->_base por enquanto.
					    
					    // #bugbug: precisamos de um ponteiro válido para o buffer.
					    //IN: service, fd, buffer, buflen
					    gramado_system_call (810, 0, (unsigned long) &prompt[0], 64);
					    
					    //#obs: 
					    //#importante 
					    //Se essa janela for a janela do shell, 
					    //então a rotina de comparação poderá fazer um refresh dessa janela. 
					    //#obs: talvez esse refresh nem seja necessário.
					    //cada rotina chamada que faça seu próprio refresh se conseguir.
					    
					    //shellCompare (window);
				    //}
					goto done;
                    break; 

				//#test	
                case VK_TAB:
                    //if ( __embedded_shell == 1)
                    //{
					    terminal_write_char ( (int) '\t');
					//}
					goto done;
				    break;

				//#todo
				case VK_BACK:
				   // fprintf (stdout, "Hello child, are you up?\n");
					//#test
					//textCurrentCol--;
					//apiSetCursor (textCurrentCol,textCurrentRow);
					//terminalSetCursor (textCurrentCol,textCurrentRow);
					//terminalInsertNextChar ( (char) ' ' ); 
					goto done;
                    break;
                              
                // Mensagens de digitação.
				// Texto. Envia o caractere.
                // Imprime os caracteres normais na janela com o foco de 
				// entrada.
				// Enfilera os caracteres na string 'prompt[]' para depois 
				// ser comparada com outras strings.
				// prompt[] é o stdin.
					
                default:
                
                    // #test
                    // esperamos que o child leia stdout
                    //que foi passado durante a clonagem.

				    
				    //se temos um shell embutido
					// Coloca no stdin, prompt[].
                    // coloca no buffer de linhas e colunas e
					// imprime na tela usando api
					//if ( __embedded_shell == 1)
					//{
					    input ( (unsigned long) long1 );   
					    terminal_write_char ( (int) long1 );
                    //};
                    
					goto done;
                    break; 
            };
            goto done;
            break;


       case MSG_KEYUP: 
           return NULL;
           break;




        // alerta que tem que ler na ttyList[] do pid indicado em long1
        case 444:
            printf("444: =)\n");
            fflush(stdout);

            //pegando a tty desse processo pra poder ler.
            //long1 é o pid de quem vamos ler a tty.
            //____this_tty_id = (int) gramado_system_call ( 266, long1, 0, 0 );
            ____this_tty_id = (int) gramado_system_call ( 266, getpid(), 0, 0 );
            printf ("NORATERM: The tty for the this process is %d \n", 
                ____this_tty_id );


            //read_ttyList ( ____this_tty_id, __rbuf2, 32 );  
            printf (__rbuf2);
            printf("444: =)\n");
            fflush(stdout);
            goto done;
            break;


		//Faz algumas inicializações de posicionamento e dimensões.
		//case MSG_INITDIALOG:
		//    break;


		//Torna a janela visível.
        //case MSG_SHOWWINDOW:
		//    break; 




		//100 - Terminal communication
		case MSG_TERMINALCOMMAND:
			switch (long1)
			{
				// Isso indica que o terminal tem chars na stream da tty,
				// então ele deve pegar e exibir.
				// Pegar um char, mas não é o último que foi colocado, 
				// é o que ainda não foi pego.

                int __x_ch;
                case 2000:
                    while (1)
                    {
						// Estudar isso.
						// Isso pega o char.
                        __x_ch = (int) system_call ( 1002, 0, 0, 0 );
 
                        if (__x_ch == '\n')
                        {
                            //terminal_write_char ( (int) '\n' ); 
                            //terminalInsertLF ();
                            //terminalInsertCR ();
                            //lf ();
                            //cr ();
                            //textCurrentRow++;
                            //textCurrentCol = 0;
                            //terminalSetCursor ( textCurrentRow, textCurrentCol );
                            break;
                        }

                        terminal_write_char ( (int) __x_ch );
                    };
                    //textCurrentRow++;
                    //textCurrentCol = 0;
                    //terminalSetCursor ( textCurrentRow, textCurrentCol );
                    break;


					
					
				// Hello	
				case 2001:
					gde_draw_text  ( NULL, 
					    0, 0, COLOR_RED, 
					    "noraterm: Hello friend, I'm alive! \n");
					gde_show_backbuffer ();
					break;
					
					
				// #importante
                // Vamos escrever na tela do terminal usando recursos da api
                // e não da libc. 
                // #obs: Aqui talvez possamos indicar o handle da janela.
				case 2002:
					gde_draw_text ( (struct window_d *) shell_info.terminal_window, 
					    0, 0, COLOR_RED, "==(top)==========" );
					gde_draw_text ( (struct window_d *) shell_info.terminal_window, 
					    0, 25*8, COLOR_RED, "==(bottom)====" );	
					gde_show_window  (shell_info.terminal_window);
					break;
					
					
				// Select current row
				//#bugbug: isso gerencia somente internamente.
				case 2005:
					terminalSetCursor ( long2, textCurrentCol );
					break;
				
					
				// Select current col	
				//#bugbug: isso gerencia somente internamente.
				case 2006:
					terminalSetCursor ( textCurrentRow, long2 );
					break;
					
						
				// Write a char in the current line buffer.
				// >> Isso é chamado quando um printf na libc03 
				// encontra um \n.
				// Isso indica que o terminal tem chars na 
				// stream da tty (CurrentTTY), então ele deve 
				// pegar e exibir.
				// Pega um char, mas não é o último que foi colocado, 
				// é o que ainda não foi pego.
				// #todo: 
				// O terminal deve configurar qual stream ele quer 
				// pegar bytes.
				case 2008:
				    //Interna.
				    handle_notification();
				    break;
				
				/*
				int xxx_ch;
				case 2008:

					// Inicializa o 'line buffer' e não o buffer de texto.
					initialize_buffer();
					
					// Pegando chars no arquivo. CurrentTTY->stdout;
					// See: gde_serv.c in the base kernel.
					// Isso lê no buffer da tty CurrentTTY.
					// >> Mas poderia ser alguma stream passada 
					// para o processo filho na hora de clonar.
                    while (1)
                    {
                        xxx_ch = (int) gramado_system_call ( 1002, 0, 0, 0 );

                        // Chegamos no fim do arquivo antes de 
                        // acabar a sring?
                        // Mostre o buffer e sinalize o erro.
                        if (xxx_ch == EOF )
                        {
                            print_buffer ();
                            MessageBox ( 3, 
                                "noraterm", 
                                "#bugbug: case 2008 - EOF");
                            exit (1);
                        }

                        // Chegamos no fim da string.
                        // Mostre a string e continue.
                        if (xxx_ch == '\0')
                        {
                            print_buffer ();
                            break;
                        }


                        // Encontramos um \n em uma string.
                        // Mostre o buffer e continue.
                        if (xxx_ch == '\n')
                        {
                            //printf ("noraterm: EOL, flush me\n");
                            print_buffer ();

                        // Ainda não encontramos  \n nem \0, 
                        // continue colocando no buffer.
                        }else{

                            // #importante:
                            // Colocar o char no buffer
                            LINE_BUFFER[line_buffer_tail++] = (char) xxx_ch;

                            if ( line_buffer_tail >= line_buffer_buffersize )
                            {

							    //LINE_BUFFER[line_buffer_tail--] = 0; //FINALIZA;
							    //line_buffer_tail = 0;

                                //isso vai inicializar o buffer,
								print_buffer ();
								
							    //printf ("noraterm: buffer limits, flush me\n"); 
								//MessageBox (3, "noraterm","buffer limit");
							    //break;
						    }
                       };
                    };
                    break;
                    */
				
				//flush buffer	
				case 2009:
					print_buffer ();
					break;
					
				// #importante	
                // Pegando mensagens no arquivo stdout do desse terminal. 
                // Talvez deva ser stdin.
				// Isso imprime na posição x y. 
				// 2005 e 2006 gerenciam o posicionamento atual                
                // ver: https://github.com/skiftOS/skift/
                //blob/6d7876bb95c160596c74f0ba4b011ede31429b1a/userspace/terminal.c
                
                #define READ_BUFFER_SIZE 512
                char ___buffer[READ_BUFFER_SIZE];
				int _i;
				case 2020:
				    fread ( (void *) ___buffer, 1, READ_BUFFER_SIZE, stdout );
					for (_i=0; _i<50; _i++)
					{
					    terminal_write_char ( (int) ___buffer[_i] );
					}
					//rewind(stdout);
					break;

					
				//#importante
				// Write char on terminal x y.	
				case 2021:
				    terminal_write_char ( (int) long2 );
				    break;
				    
				//#todo:    
				//case TERMINALCOMMAND_CLS:   
				    //printf (" {CLS} \n");
				    //break;
				      
					//...
			};
			goto done;
			break;

        // Commands.		
		case MSG_COMMAND:
            switch (long1)
			{
				// Null.
				case 0:
				    gde_message_box ( 3, 
				        "Noraterm", 
				        "Testing MSG_COMMAND NULL" );
				    break;
				
				// About.
				// Abre uma janela e oferece informações sobre o aplicativo.
				case CMD_ABOUT:
				    // Test.
					printf ("noraterm: CMD_ABOUT\n");
				    gde_message_box ( 3, 
				        "Noraterm", 
				        "Testing MSG_COMMAND CMD_ABOUT" );
				    break;
				
				//clicaram no botão
				case BN_CLICKED:
				    //if(window == i1Window){
					     //@todo: abre o menu de aplicativos
					//}
				    //if(window == i2Window){
					   //@todo: abre o interpretador de comandos.
					//}
					//#debug
					printf (" * BN_CLICKED * \n");
				    break;
				//...
					
				case CMD_EXIT:
					exit_builtins ();
					exit ();
					break;
				
				//default:
				//break;
			};
			goto done;
		    break; 


		//Essa mensagem pode ser acionada clidando um botão.
        case MSG_CLOSE:
            printf ("noraterm: MSG_CLOSE\n");
            gde_close_window (main_window);
            gde_exit(0);
            break;


		//Essa mensagem pode ser acionada clidando um botão.
        case MSG_DESTROY:
            printf ("noraterm: MSG_DESTROY\n");
            gde_exit(0);
            break;


		// MSG_MOUSEKEYDOWN	
		case 30:
			//qual botão?
		    switch (long1)
			{
				case 1:
				    //#obs: No keydown a gente só abaixa o botão.
					
					
                    if ( window == bar_button_1 )
                    {
                        gramado_system_call ( 9900,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
                            break;
                    }

                    if ( window == bar_button_2 )
                    {
                        gramado_system_call ( 9900,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
                            break;
                    }


                    if ( window == bar_button_3 )
                    {
                        gramado_system_call ( 9900,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
                            break;
                    }

					
				    //#debug
					//printf("button 1\n");     
					
                    //botão 1
					if ( window == app1_button )
                    {
						//updateVisibleArea( 0 );
						//terminalRefreshVisibleArea(); 
                        //shellScroll();
						printf (" ** BUTTON 1 ** \n");
						break;
					}

					//botão 2
					if ( window == app2_button )
                    {
                        //updateVisibleArea( 1 );
						//terminalRefreshVisibleArea();
					    printf (" ** BUTTON 2 ** \n");
						break;
					}
					
					//botão 3
					if ( window == app3_button )
                    {
                        //updateVisibleArea( 1 );
						//terminalRefreshVisibleArea();
					    printf (" ** BUTTON 3 ** \n");
						break;
					}
					
					//botão 4
					if ( window == app4_button )
                    {
                        //updateVisibleArea( 1 );
						//terminalRefreshVisibleArea();
					    printf (" ** BUTTON 4 ** \n");
						break;
					}
					
					if ( window == editboxWindow )
					{
					    gde_set_focus (editboxWindow);
					    //APIredraw_window (editboxWindow,1);
						break;
					}
					
					if ( window == main_window )
					{
						//raise window.
	                     //system_call ( 9700, 
	                         //(unsigned long) window, 
		                     //(unsigned long) window, 
		                     //(unsigned long) window );
		                 gde_set_focus (window);  
		                 break;
					}
					
					// ??
					gde_set_active_window (window);
					//APIredraw_window ( window, 1 );
					
					//pode ser que recebemos um ponteiro que não nos é acessível.
					//o 'long2' poderia nos dizer se ele é um dos controles de janela.
					//isso tornaria tudo mais fácil.
					//se ele for um controle de janela é só mandar a mensagem de minimizar
					//maximizar, fechar ...
					//porém não deveria ser trabalho do aplicativo fazer isso ...
					//>>> então o servidor deve tomar alguma atitude caso
					//a janela seja um controle ... ou o procedimento defered receberá 
					//essa mesma mensagem que contem o argumento long2 indicando qual é o controle de
					//janela que foi acionado
					//se o servidor conseguir identificar que esse botão é um controle, então
					//ele mandara a mensagem de fechar janela ao inves de mandar essa mesagem, por ex.
					
                    // #test
					// se não podemos atender esse evento enão vamos permitir que o kernel
					// trate ele. 
					// O procedimento do sistema pode fazer isso, ou o defered ou
					// mandando uma mensagem para o servidor.
					// eventSendMessage (...) todo
					
					//podemos salvar o ponteiro dos botões da barra de títulos,
					//solicitando eles para o kernel.
					
					//podemos ainda usar algum controle de janelas
					//windowcontrolSendMessage
					
					break;

				case 2: printf("button 2\n"); break;
				case 3: printf("button 3\n"); break;
            };
            goto done;
            break;


		// MSG_MOUSEKEYUP	
		case 31:
		    switch (long1)
			{
				case 1:

                    if ( window == bar_button_1 )
                    {
                        gramado_system_call ( 9901,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
                        //apiDrawText ( client_window, 4, 40 +32, COLOR_BLACK, "test 1 ...");
                        //refresh_screen ();
                        //terminal_clear_from_startofline ();
                        //terminalCopyToScroll ();
                        
                        gramado_system_call (900, (unsigned long) "hello3.bin", 0, 0);
                        //gramado_system_call (900, (unsigned long) "reboot2.bin", 0, 0);
                        
                        //pegando a tty desse processo pra poder ler.
                        //____this_tty_id = (int) gramado_system_call ( 266, getpid(), 0, 0 );
                                           
                       //while(1)
                       //{
                           //read ( ____this_tty_id, __rbuf2, 32 );     
                           //printf (__rbuf2);
                       //}
                        
                        //gramado_system_call (900, (unsigned long) "hello3.bin", 0, 0);
                        //gramado_system_call (900, (unsigned long) "gwm.bin", 0, 0);
                          
                        //if ( fork () == 0 )
                        //{ execve ("launcher.bin", NULL, NULL );  } 
                        
                        
                        // #todo
                        // Tentar ler o que o processo filho colocou na stream stdout.
                        
                        //printf ("noraterm: entrando num loop para ler do fluxo padrao\n");
                        
                        
                        //fprintf(stdout, "Noraterm wrote this shit!\n");
                        
                        //while ( (c = fgetc(stdin)) >= 0 )
                            //printf ("%c", c);                  
                        
                        //while ( (c = fgetc(stdout)) >= 0 )
                            //printf ("%c", c);                  
                            
                            
                        //while ( (c = fgetc(stderr)) >= 0 )
                            //printf ("%c", c);                  
                            
                        break;
                    }

                    if ( window == bar_button_2 )
                    {
                        gramado_system_call ( 9901,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
                        //apiDrawText ( client_window, 4, 40 +32, COLOR_BLACK, "test 2 ...");
                        //refresh_screen ();
                        //terminal_clear_to_endofline ();
                        //terminal_scroll_display ();
                        
                        //gramado_system_call (900, (unsigned long) "false.bin", 0, 0);
                        gramado_system_call (900, (unsigned long) "hello.bin", 0, 0);
                        
                        ____this_tty_id = (int) gramado_system_call ( 266, getpid(), 0, 0 );
                                           
                       while(1)
                       {
                           if ( read ( ____this_tty_id, __rbuf2, 32 ) > 0 )
                           {     
                               printf (__rbuf2);
                               fflush (stdout);
                           }
                       }
                        
                        
                        break;
                    }

                    if ( window == bar_button_3 )
                    {
                        gramado_system_call ( 9901,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
                        //apiDrawText ( client_window, 4, 40 +32, COLOR_BLACK, "test 3 ...");
                        //refresh_screen ();
                        //terminal_clear_to_endofdisplay ();
                        //terminalShowScreenBuffer ();
                        
                        //gramado_system_call (900, (unsigned long) "false.bin", 0, 0);
                        gramado_system_call (900, (unsigned long) "hello3.bin", 0, 0);
                        
                        ____this_tty_id = (int) gramado_system_call ( 266, getpid(), 0, 0 );
                         
                       // #debug
                       // Debug na máquina real ...
                       // como o write deu sinal de vida ...
                       // então vamos suspender o read  
                       
                        //yield. test
                        gramado_system_call ( 265,0,0,0);          
                        gramado_system_call ( 265,0,0,0);          
                        gramado_system_call ( 265,0,0,0);                                  
                                          
                       while(1)
                       {
                           read ( ____this_tty_id, __rbuf2, 32 );     
                           printf (__rbuf2);
                           fflush(stdout);
                           // se isso não aparecer .. 
                           //o printf acima tambem nao funcionou, 
                           //mesmo que o read tenha funcionado
                       }
                       break;
                    }


				
				    //printf("up button 1\n");
					if (window == taskbar_button1)
					{
	                    //terminalTestButtons ();	
		                //refresh_screen ();
						printf ("Start menu \n");
					}
					
					
					//botão de reboot;
					if ( window == reboot_button )
                    {
					    printf("Rebooting...\n");
		                system("reboot"); 	
					}
					
					//botão de close
					if ( window == close_button )
				    {
					    //APIresize_window ( window, 200, 200 );
					    //APIredraw_window ( window, 1 );
					    //refresh_screen (); //não precisa isso	

						running = 0;
                        ShellFlag = SHELLFLAG_EXIT;						
					}  
					
					break;

				case 2: debug_print("up button 2\n"); break;
				case 3: debug_print("up button 3\n"); break;
            };
            goto done;
            break;

		// MSG_MOUSEMOVE	
        //case 32:
            //break;

		// MSG_MOUSEOVER	
		case 33: 
			//se tiver passando em cima do botão de close.
			if ( window == close_button )
			{
				//printf(".");
			    //APIresize_window ( window, 200, 200 );
				//APIredraw_window ( window, 1 );	
			}
            
		    break;

		//entered	
        case 38:
		    if ( window == close_button )
			{
			    //printf("entered\n");	
			}
            break;		

		//exited	
        case 39:
		    if ( window == close_button )
		    {
			    //printf("exited\n");
		    }
            break;
			
		// Quando a aplicativo em user mode chama o kernel para 
		// que o kernel crie uma janela, depois que o kernel criar a janela,
		// ele faz uma chamada ao procedimento de janela do aplicativo com a mensagem 
        // MSG_CREATE, se o aplicativo retornar -1, então a rotina em kernel mode que 
        // esta criando a janela, cancela a janela que está criando e retorn NULL.		
		case MSG_CREATE:
		    printf ("noraterm: MSG_CREATE *debug\n");
		    //exit(0); //debug
		    break;
			
		//isso pinta os elementos da área de cliente.
        //essa mensagem é enviada para o aplicativo quando 
        //a função 'update window'	é chamada.
        case MSG_PAINT:
            //printf ("noraterm: MSG_PAINT\n");
		    if ( window == main_window )
		    {
				//MessageBox (3,"noraterm","set focus");
				//repinta janelas filhas.
				gde_redraw_window ( main_window, 1);
				gde_redraw_window ( client_background_window, 1);
				gde_redraw_window ( client_window, 1);
				gde_redraw_window ( client_bar_Window, 1);
				gde_redraw_window ( bar_button_1, 1); //botões
				gde_redraw_window ( bar_button_2, 1); //botões
				gde_redraw_window ( bar_button_3, 1); //botões 
			}
			break;
			
		// MSG_TIMER 
		// #TODO INCLUIR ISS0 NA API.
		// Em algum momento o shell foi inicializado ... então
		// ele chamará essa mensagens de acordo com o tempo programado.
		case 53:
			//See tests.c
			testsTimerUpdateObject ();
            //printf("shell timer tick\n");
			break; 		

        // Uma janela recebe esse mensagem logo após ganhar 
        // o foco de entrada.
		case MSG_SETFOCUS:
		    if ( window == main_window )
		    {
				//MessageBox (3,"noraterm","set focus");
				//repinta janelas filhas.
				gde_redraw_window ( main_window, 1);
				gde_redraw_window ( client_background_window, 1);
				gde_redraw_window ( client_window, 1);
				gde_redraw_window ( client_bar_Window, 1);
				gde_redraw_window ( bar_button_1, 1); //botões
				gde_redraw_window ( bar_button_2, 1); //botões
				gde_redraw_window ( bar_button_3, 1); //botões 
			}
			break;

        // Uma janela recebe esse mensagem logo após perder 
        // o foco de entrada.
        case MSG_KILLFOCUS:
            gde_message_box (3,"noraterm","kill focus");
            break;
            
            
         //#test
         case MSG_HSCROLL:
             //#todo
             break;   

         //#test
         case MSG_VSCROLL:
             if ( long1 == 0 )
             { terminal_scroll_down (); };
             if ( long1 == 1 )
             { terminal_scroll_up (); };
             break;   


		//@todo: isso ainda não existe na biblioteca. criar.	
        //case MSG_CLS:
            //limparemos o retãngulo da área de cliente,
			//mesmo que estejamos em full screen. 
		//	break;		
		
		//mudaremos o curso usando long1 e long2.
		//case MSG_SETCURSOR:
		//    break;
		
		//case MSG_HSCROLL:
		//    break;
		//case MSG_VSCROLL:
		//    break;
		
		
		//case MSG_FULLSCREEN:
		//    break;
		
		
		//case COMMAND_SET_WINDOW_SIZE:
		//    break;
		
		//case COMMAND_HIDE_WINDOW:
        //    break; 

		
		//#importante
		// os caracteres de controle encontrados na tabela ascii.
		//@todo: Essa mensagem precis ser criada, tanto no kernel 
		//quanto na API.
		//case MSG_ASCII_CONTROL_KEYS:
		//   switch(long1)
		//	{
	
		        //^A STX
                //case 1:
		        //    printf("^A");
                //    break;  		
	
		        //^B SOT
                //case 2:
		        //    printf("^B");
                //   break;  		
			
		        //^C ETX
                //case 3:
		        //    printf("^C");
		        //	shellPrompt();
                //    break;

		        //^D EOT
                //case 4:
		        //   printf("^D");
                //   break;

		        //^E ENQ
                //case 5:
		        //    printf("^E");
                //    break;  								
			
		        //^F ACK
                //case 6:
		        //    printf("^F");
                //    break;  					


		        //^G BEL
                //case 7:
		        //   printf("^G");
                //    break;  					
			
			
		        //^H BS
                //case 8:
                //    break;  								
			
		        //^I HT horizontal tab
                //case 9:
                //    break;  	

		        //^J LF
                //case 10:
                //    break;  			
			
						
		        //^K VT vertical tab
                //case 11:
                //    break;  	

		        //^L FF form feed
                //case 12:
                //    break;  	
			
			
		        //^M CR
                //case 13:
                //    break;  	
			

		        //^N SO
                //case 14:
                //    break;  				
		

		        //^O SI
                //case 15:
                //    break;


		        //^P DLE DATA LINK ESCAPE
                //case 16:
                //    break;  			
		
		
		        //^Q DC1 DEVICE CONTROL 1
                //case 17:
                //    break;  	
  			
			
		        //^R DC2 DEVICE CONTROL 2
                //case 18:
                //    break;

		        //^S DC3 DEVICE CONTROL 3
                //case 19:
                //    break;  			

		        //^T DC3 DEVICE CONTROL 4
                //case 20:
                //    break;  			
		
		
		        //^U NAK NEGATIVE ACKNOLEDGE
                //case 21:
                //    break;  			

		        //^V SYN SYNCHRONOUS IDLE
                //case 22:
                //    break;  			
		
		        //^W ETB END OF TRANSMISSION BLOCK
                //case 23:
                //    break;  			
		
		        //^X CAN CANCEL
                //case 24:
                //    break;  			

		
		        //^Y EM END OF MEDIUM
                //case 25:
                //    break;  			
		
		        //^Z SUB SUBSTITUTE
                //case 26:
                //    break;  			
		
		
		        //^[ ESC ESCAPE
                //case 27:
                //    break;  			
		
		        //^\ FS FILE SEPARATOR
                //case 28:
                //    break;  			
		
		        //^] GS GROUP SEPARATOR
                //case 29:
                //    break;  			
		
		        //^ RS RECORD SEPARATOR
                //case 30:
                //    break;  			
		
		
		        //_ US UNIT SEPARATOR
                //case 31:
                //    break;  			
		
		
		        //DELETE
                //case 127:
                //    break; 

        //    };		
		//    break;
			
		
		//...

       default:
            debug_print("noraterm: default message");
            goto done;
            break;
    };

    // Nothing for now !

done:

    if ( (void *) window == NULL ){ return NULL; }

    return (void *) gde_system_procedure (window,msg,long1,long2);
}



/*
 ******************************
 * shellWaitCmd:
 *     Espera completar o comando com um [ENTER]. ##suspensa
 */

void shellWaitCmd (){
		
	// @todo: Cuidado com loop infinito.

	
	// Obs: Quem muda o status é o procedimento,
	//      quando recebe o retorno da função input:
	

	// Uma interrupção de teclado aciona o procedimento
	// do shell que atualiza o status.
	
	
	// BUG BUG :
    //
    //    Pra esse shell funcionar teria que habilita
    //    agora a interrupção de teclado e somente ela
    //    para que a interrupção de timer não bagunçe as
    //    coisas fazendo troca de contexto.

	
	//asm("sti");    //@todo; Não habilitar!
	
    //Loop.  
	
    do{	 
		if ( prompt_status == 1 )
		{
			prompt_status = 0;     
			return;
	    };
	
	} while (1);

    prompt_status = 0;	
}


/*
 ****************
 * shellCompare:
 *     Compara comandos digitados com palavras chave.
 *     Compara a palavra em 'prompt[]' com outras e chama o serviço.
 * o enter foi o caractere digitado, vamos comparar palavras.
 *
 * Credits:
 * + Stephen Brennan - https://brennan.io/2015/01/16/write-a-shell-in-c/
 * + Frederico Martins Nora (frednora)
 */
 
//#TEST 
//#define LSH_TOK_DELIM " \t\r\n\a+!:=/.<>;|&" 
 
#define LSH_TOK_DELIM " \t\r\n\a" 
#define SPACE " "
#define TOKENLIST_MAX_DEFAULT 80
 
unsigned long shellCompare (struct window_d *window){
	
    //char **stringarray1;
	char *tokenList[TOKENLIST_MAX_DEFAULT];
	char *token;
	int token_count;	
	int i = 0;

    unsigned long ret_value;
	int q;    //diálogo
	char *c;
	
    //?? é um pathname absoluto ou não. ??
	//Ok. isso funcionou.
    int absolute; 
	
	//buffer de test;
	unsigned long message_buffer[11];
	int PID;
	
	//#importante:
	//Transferir toda alinha de comando para a memória 
	//compartilhada.
	//obs: Possivelmente isso não continuaá assim, pas por enquanto tá bom.

	unsigned char *shared_memory = (unsigned char *) (0xC0800000 -0x100);
	
	//linha de 80 chars no máx.
	for ( i=0; i<80; i++ ){
		shared_memory[i] = prompt[i];
	}
	
	
    // Temos uma linha de comando em prompt[]
    // que é o stdin.  
NewCmdLine:	

    //#debug
	//printf("prompt:{%s}\n",prompt);
	
	c = prompt;
	
	//Se alguem pressiona [ENTER] com prompt vazio
	//dá page fault.
	//Isso cancela caso o buffer esteja vazio.
	
	//>(NULL)
	//[ENTER] finalizou a atring antes de ter digitado alguma coisa.
	if ( *c == '\0' ){
	    goto exit_cmp;	
	}
	
	//>' '
	//Só faz o tratamento com while se for igual a ' '.
    if ( *c == ' ' || *c == '\t' )
	{
        int j;		
        //#importante:
		//Aqui estamos tratando uma linha de comando inteira.
		
	    //enquanto c[] for diverente de ' ' c avança.
	    //isso elimina os espaços para c[]
	    j=0;
		while ( *c == ' ' || *c == '\t' )
		{ 
	        
			//Limits
		    j++;
			if ( j > __wlMaxColumns )
			{
			   //#debug
               //Isso significa que uma string 
			   //construida em prompt[] não foi 
			   //corretamente finalizada.
			   //ou algum problema no while anterior.
			   //printf("#debug \n");				
			   printf("shellCompare: *hang while1\n");	
			   while (1){
				   asm ("pause");
			   }
			}
			
			//desrepeitamos o limite imposto pelo fim da string.
			//por isso temos que fazer a marcação exata do início 
			//da linha de comando e do fim da linha de comando.
			// |            |.......|        |
			// start       left   right     end
			
			c++; 
		};
		
		//se depois de eliminarmos os espaços encontrarmos
		//um '\0' de fim de string.
		//significa que o usuário digitou um monte de espaços
		//depois apertou enter.
		//não há mais o que fazer.
	    if ( *c == '\0' ){
	        goto exit_cmp;	
	    }		
	    
		int line_rest = ( __wlMaxColumns-j);
		
		//copia todo o resto da linha para o inpicio da linha.
        for ( j=0; j<line_rest; j++ )
		{
			prompt[j] = c[j];
			
			//se enquanto estamos copiando,
			//ja copiamos o finalizador de string,
			//não precisamos copiar mais nada.
			if ( *c == '\0' ){
				goto commandlineok;
			}				
		}
        
		//#bugbug
        //se estamos aqui é porque copiamos quase 80 chars.		
    };


commandlineok:	

    //#debug
	//printf("prompt:{%s}\n",prompt);	
	
    //>/
    //>.
    //>./
    //>..
    //>../
	
	// #importante:
	// Vamos checar se o pathname é absoluto ou relativo.
	// +Se tiver barra, significa que o pathname é absoluto e 
	// começa no diretório raiz do volume do sistema. root:/volume1/
	// +Se começar por root:/ também é absoluto.
	// +Pathname relativo é somente aquele que é apenas um nome 
	// de arquivo dentro do diretório atual. Como: 'name' ou name1/name2,
	// sem barra ou ponto.
	// $/ é o diretório raiz do volume do sistema.
	// $v/ é o diretório raiz do vfs.	
 

    absolute = absolute_pathname ( (char *) prompt );
	
    switch (absolute)
	{
		//Não é absoluto ou falhar
		case 0:
		    goto this_directory;
		    break;
			
		//é absoluto	
		case 1:
		    goto check_directory; 
			break;
		//falha	
		case 2:
		default:
		    goto this_directory;
			break;
	};

//precisamos checar em que diretório 
//o programa está.
//o comando tem um pathname absoluto ...
//Precisamos invocar esse programa 
//que está em um diretório apontado no pathname.
//ex: ../cmd 	

check_directory:
	
	
//O primeiro elemento da linha de comandos 
// é um comando simples	
// cd ..
this_directory:	
	
	//if( *prompt == (char) '\0' ){
	//    goto exit_cmp;	
	//}
	
	// O input pode ser copiado aqui, então manipularemos essa variável.
	//char *FileName;
	
	//
	// ?? E se tivermos várias palavras na linha de comando ??
	//
		
    // Returns first token 
    //char *token = strtok(prompt, " -");
	
	//#debug
    //printf("shellCompare: Testing ...\n");
    //refresh_screen();	
   

	
	
	// ?? what ?
    // first call returns pointer
	// to first part of user_input
	// separated by delim
	
    //isso pega a primeira palavra digitada
	tokenList[0] = strtok( prompt, LSH_TOK_DELIM);
	
	
	//para o argumento atual
	//@todo: isso precisa ser limpado sempre.
	
	//salva a primeira palavra digitada.
	token = (char *) tokenList[0];
	
	i=0;                                  
    while ( token != NULL )
	{
        // Coloca na lista.
        //salva a primeira palavra digitada.
		tokenList[i] = token;

		//#debug
		//Mostra
        //printf("shellCompare: %s \n", tokenList[i] );
        //refresh_screen();
		
		token = strtok( NULL, LSH_TOK_DELIM );
		
		// Incrementa o índice da lista
        i++;
		
		//salvando a contagem.
		token_count = i;
    }; 

	//Finalizando a lista.
    tokenList[i] = NULL;
	
	
	//
	//#importante:
	//nesse momento todos os argumentos estão certinhos no vetor.
	//já conferimos.
	//

	//#debug
    //printf("shellCompare: %s \n", tokenList[i] );
    //refresh_screen();	

	//#debug
    //printf("shellCompare: Test done!\n");
    //refresh_screen();	


	// Zerando o índice do tokenList
    i=0;	
   
    //printf("shellCompare: Testing ...\n");
    //refresh_screen();
   
    // Keep printing tokens while one of the
    // delimiters present in str[].
    //while(token != NULL)
    //{
    //    printf("%s\n", token);
	//	refresh_screen();
	//	token = strtok(NULL, " -");
    //}
	
	
		
	//do_command(argc, argv);
	goto do_command;	
	
do_command:	
    //nothing.	
do_compare:

    //
	// ## identificadores de iniciação de linha ##
	//
	
	//Esses identificadores determinam o que 
	//se vai encontrar na linha. E não existe volta, 
	//o que o identificador determinou será obedecido.
	
	//
	// ## Lista de identificadores ligado a execussão ##
	//
	// (do)
	//
	// dobin - Execute programa .bin
	// dotry - Tenta executar qualquer extensão
	// Obs: Esses comandos efetuam goto 
	// dentro desse código, saltando diretamente 
	// para as rotinas executadoras de programas ou scripts.
	// Obs: O nome do progama está em tokenList[1] e os 
    // argumentos nos próximos tokenList.	
	//
	//

    if ( strncmp( (char *) tokenList[0], "dobin", 5 ) == 0 ){
	    goto dobin;	
	}

    if ( strncmp( (char *) tokenList[0], "dotry", 5 ) == 0 ){
		goto dotry;
	} 
	
	//um comando no shell pede para executar um script
    if ( strncmp( (char *) tokenList[0], "dosh", 4 ) == 0 ){
		goto dosh;
	} 	

    //...

    //
	// #Importante:
	// Devemos pegar os argumentos salvos na lista.
	// O primeiro argumento é o nome do aplicativo que deve ser executado
	// e os outros argumentos são argumentos que devem ser passados para 
	// o aplicativo a ser executado.
	//
	
	//
	// Talvez aqui devamos usar tokenList[0] e não prompt.
	//
	
    //@todo Criar sof links no vfs.
	//o vfs ficará no kernel base.
	//@todo: Criar chamadas ao vfs.
		
    // L1 RAM /objetcs   
	// (diretório raiz para os arquivos que são diretórios de objetos)
	// os objetos serão listador em um arquivo que nunca será salvo no disco.
	//if( strncmp( prompt, "/objects", 6 ) == 0 )
	//{
	//    printf("info: Open object manager root dir ...\n");
    //    goto exit_cmp;
    //};

	// L2 disk  /diretório raiz do sistema de arquivos.
	//if( strncmp( prompt, "/", 5 ) == 0 )
	//{
	//    printf("info: Open file system root dir ...\n");
    //    goto exit_cmp;
    //};

	// L3 LAN  // acesso a arquivos da lan
	//os arquivos lan serão listador em um arquivo que nunca será salvo no disco.
	//if( strncmp( prompt, "/lan", 6 ) == 0 )
	//{
	//    printf("info: Open lan root dir ...\n");
    //    goto exit_cmp;
    //};
 
	// L4 WAN   //acesso a arquivos da wan
	// os arquivos lan serão listador em um arquivo que nunca será salvo no disco.
	//if( strncmp( prompt, "/wan", 6 ) == 0 )
	//{
	//    printf("info: Open wan root dir ...\n");
    //    goto exit_cmp;
    //};
	
	
	//comentário
	// a linha é um comentário, podemos ignorar.
    //if( strncmp( prompt, "//", 2 ) == 0 ){
	//	goto exit_cmp;
	//};		
	
    //
	// Ordem alfabética.
	//
	

	//token
	//testando tokenList
	//comando usado para testes de comando.
	if ( strncmp( prompt, "token", 5 ) == 0 )
    {
		printf("\nTesting tokenList ...\n");
		printf("\nTotal={%d}\n",token_count);
		printf("\n Comand = %s \n",tokenList[i]);
		gde_show_backbuffer ();
		
		i++;
		token = (char *) tokenList[i];
		
		if ( token == NULL ){
			goto exit_cmp;
		}else{
			
		    printf("\n argument_number={%d} argument={%s}\n", i, tokenList[i] );	
            
			if ( strncmp( (char*) tokenList[i], "-a", 2 ) == 0 ){
			    printf("[OK] argumento %s selecionado.\n", tokenList[i]);
		    }
			//...
		};
		
		
		i++;
		token = (char *) tokenList[i];
		
		if ( token == NULL ){
			goto exit_cmp;
		}else{
			
		    printf("\n argument_number={%d} argument={%s}\n", i, tokenList[i] );	
            
			if ( strncmp( (char*) tokenList[i], "-b", 2 ) == 0 ){
			    printf("[OK] argumento %s selecionado.\n", tokenList[i] );
		    }
			//...
		};		
		
		
		i++;
		token = (char *) tokenList[i];
		
		if ( token == NULL ){
			goto exit_cmp;
		}else{
			
		    printf("\n argument_number={%d} argument={%s}\n", i, tokenList[i] );	
            
			if ( strncmp( (char *) tokenList[i], "-c", 2 ) == 0 ){
			    printf("[OK] argumento %s selecionado.\n", tokenList[i] );
		    }
			//...
		};
		
		printf("\n");
		goto exit_cmp;
	};
    

    //
    // Início dos comandos.
    //
	
	//about 
	//isso é um teste.
	//mostra informações sobre o aplicativo usando 
	//um message box ou uma janela.
	if ( strncmp( prompt, "about", 5 ) == 0 )
	{
		shellSendMessage ( NULL, MSG_COMMAND, CMD_ABOUT, 0);
		
        //chama message box com mensagem about.
        //apiSendMessage ( (struct window_d *) 0, 
		//                 (int) MSG_COMMAND, 
		//				 (unsigned long) CMD_ABOUT, 
		//				 (unsigned long) 0 );
						 
	    goto exit_cmp;
	};

	// Imprime a tabela ascii usando a fonte atual.
    // 128 chars.	
    //if( strncmp( prompt, "ascii", 5 ) == 0 )
    //{
		//shellASCII();
	//	goto exit_cmp;
	//}


	//bmp exemplo.bmp
    if ( strncmp( prompt, "bmp", 3 ) == 0 )
	{
		i++;
		token = (char *) tokenList[i];
		
		if( token == NULL )
		{
			printf("Error: No name!\n");
		}else{
			
		   //test 200kb
		   printf ("test 200kb\n");
			
		   terminalDisplayBMPEx ( (char *) tokenList[i], (int) (200) );
		};
		goto exit_cmp;
    };	
	
	


	// cd - Change dir.
	if ( strncmp( prompt, "cd", 2 ) == 0 )
	{
		
		i++;
		token = (char *) tokenList[i];
		
		if( token == NULL )
		{
			printf("cd error: no arg\n");
		}else{
			
			//#bugbug: não é possivel fazer isso por enquanto,
			//pois não estamos fazendo parse de char por char.
			//if( strncmp( (char*) tokenList[i], ".", 2 ) == 0 )
			//{}
				
			if( strncmp( (char*) tokenList[i], "..", 2 ) == 0 )
			{
				//Apaga o nome do último diretório.
			    shell_pathname_backup ( current_workingdiretory_string, 1 ); 
                goto exit_cmp;				
		    }			
			
	        // updating the current working directory string.
	        shellUpdateWorkingDiretoryString ( (char *) tokenList[i] );
			
			//@todo: podemos checar se o pathname é absoluto,
			//e onde se encontra o arquivo que queremos.
			
			//terminalDisplayBMP ( (char*) tokenList[i] );
		};		
		
		
		// o que segue o comando cd é um pathname.
		//@todo: podemos checar se o pathname é absoluto,
		//e onde se encontra o arquivo que queremos.
		//cd_buitins();
	    goto exit_cmp;
	};	

	// clear-screen-buffer
	if ( strncmp( prompt, "clear-screen-buffer", 19 ) == 0 )
	{
		terminalClearBuffer ();
		goto exit_cmp;
	}	
	
	//close
	if ( strncmp( prompt, "close", 5 ) == 0 )
	{
		shellSendMessage ( NULL, MSG_CLOSE, 0, 0);
	    goto exit_cmp;
	}		


    // cls - Clear the screen.
	if ( strncmp( prompt, "CLS", 3 ) == 0 || 
	     strncmp( prompt, "cls", 3 ) == 0 )
	{
        cls_builtins ();
        goto exit_cmp;
	}
	
	
	// color
	// color-scheme
	// Seleciona um dos 2 modos de cores padrão do sistema.
    if ( strncmp( prompt, "color", 5 ) == 0 || 
	     strncmp( prompt, "color-scheme", 12 ) == 0 )
	{

		i++;
		token = (char *) tokenList[i];
		
		if( token == NULL )
		{
			printf("No args\n");
			goto exit_cmp;
		}else{
            
			//humility
			if( strncmp( (char*) tokenList[i], "--humility", 10 ) == 0 )
			{ 
		        printf("Selecting Humility color scheme\n"); 
                system_call ( 119, 
                  (unsigned long)1, (unsigned long)1, (unsigned long)1);
				printf("done\n");
                goto exit_cmp;				
			}
			
			//pride
			if( strncmp( (char*) tokenList[i], "--pride", 7 ) == 0 )
			{
				printf("Selecting Pride color scheme\n");
                system_call ( 119, 
                  (unsigned long)2, (unsigned long)2, (unsigned long)2);
                printf("done\n");
				goto exit_cmp;				
			}
			
			// Talvez haverão mais esquemas ...
			//...
		};
		goto exit_cmp;
    };		
	
	
	
			


	// del
	// o que segue o comando del é um pathname.
	//@todo: podemos checar se o pathname é absoluto,
	//e onde se encontra o arquivo que queremos.		
	if ( strncmp( prompt, "del", 3 ) == 0 )
	{
		del_builtins();
	    goto exit_cmp;
	};	

    // desktop.
	if ( strncmp( prompt, "desktop", 7 ) == 0 )
	{
        desktopInitialize();
        goto exit_cmp;
	};	
	


	// dir - Lista os arquivos no estilo DOS.
	if ( strncmp ( prompt, "dir", 3 ) == 0 )
	{
		//char dir_name[] = "volume1";
		
		i++;
		token = (char *) tokenList[i];
		
		if ( token == NULL )
		{
			
		    //listar os arquivos em um diretório dado o nome do diretório.
			gde_enter_critical_section ();
		    system_call( 177,
		             (unsigned long) 0,   //nome do diretório.
                     (unsigned long) 0,   
                     (unsigned long) 0 ); 			
		    gde_exit_critical_section ();		
			
			
		}else{

		    //listar os arquivos em um diretório dado o nome do diretório.
			gde_enter_critical_section();
		    system_call ( 177,
		        (unsigned long) tokenList[i],   //nome do diretório.
                (unsigned long) tokenList[i],   
                (unsigned long) tokenList[i] ); 
		    gde_exit_critical_section();		
			
			//...
		};		
				
		// o que segue o comando dir é um pathname.
		//@todo: podemos checar se o pathname é absoluto,
		//e onde se encontra o arquivo que queremos.
        //se o pathname for null então o comando atua sobre o pwd		
		//dir_builtins();
        goto exit_cmp;
    };
	
    // disk-info
	if ( strncmp( prompt, "disk-info", 9 ) == 0 )
	{
	    shellShowDiskInfo();
        goto exit_cmp;
    };	
	
	
	// echo - Echo de terminal.
    if ( strncmp( prompt, "echo", 4 ) == 0 )
	{
		echo_builtins(tokenList);
		goto exit_cmp;
    };

	
	// editbox
	// Cria uma edibox.
    // #teste: deletar.
	if ( strncmp( prompt, "edit-box", 8 ) == 0 )
	{
	    gde_enter_critical_section();    
	    terminalCreateEditBox ();
	    gde_exit_critical_section();    
		
		goto exit_cmp;
    };		
	
	// exec - Executa um programa fechando o shell.
    if ( strncmp( prompt, "exec", 4 ) == 0 )
	{
		// o que segue o comando exec é um pathname.
		//@todo: podemos checar se o pathname é absoluto,
		//e onde se encontra o arquivo que queremos.		
		exec_builtins();
		ShellFlag = SHELLFLAG_EXIT;
		goto exit_cmp;
    };	
	
	// exit - Exit the application.
    if ( strncmp( prompt, "exit", 4 ) == 0 )
	{
		exit_builtins ();
		ShellFlag = SHELLFLAG_EXIT;
		goto exit_cmp;
    };
	
    // fork - Testando a função fork.
	// Apenas obtendo o retorno na rotina de clonagem.
	// #bugbug: Não usar fork no garden
	if ( strncmp ( prompt, "fork", 4 ) == 0 )
	{
		/*
		printf("fork: Tentando clonar o processo atual ...\n");
		
		int pidFORK = (int) fork ();

 		//Mostra o ID do processo clone.
		printf("Clone PID={%d}\n", pidFORK );
		
		//mostra o id do processo atual.
		shellShowPID ();
		
		printf("fork: done\n");
        */
        
		goto exit_cmp;
	};		
	
	
    // getpid
	if ( strncmp( prompt, "getpid", 6 ) == 0 )
	{
	    getpid_builtins();
        goto exit_cmp;
    };
	
    // getppid
	if ( strncmp( prompt, "getppid", 7 ) == 0 )
	{
	    getppid_builtins();
        goto exit_cmp;
    };
	
	
    // getuid - get user id
	if ( strncmp( prompt, "getuid", 6 ) == 0 )
	{
	    getuid_builtins();
        goto exit_cmp;
    };
	
	
    // getgid - get group id
	if ( strncmp( prompt, "getgid", 6 ) == 0 )
	{
	    getgid_builtins();
        goto exit_cmp;
    };
	
    //get-usersession
	if ( strncmp( prompt, "get-usersession", 15 ) == 0 )
	{
	    ShowUserSessionID();
        goto exit_cmp;
    };
	
	
    //get-room (windowstation)
	if ( strncmp( prompt, "get-room", 8 ) == 0 )
	{
		//#todo change name.
	    ShowWindowStationID();
        goto exit_cmp;
    };
	
    //get-desktop
	if ( strncmp( prompt, "get-desktop", 11 ) == 0 )
	{
	    ShowDesktopID();
        goto exit_cmp;
    };
	
	// #gws
	// Testando funcionalidades do gws.
	// gws é um recurso importante de terminal, pois
	// pode trazer recursos de interface gráfica personalizados
	// para dentro do terminal. É um diferencial.
	if ( strncmp ( prompt, "gws", 3 ) == 0 )
	{
		goto exit_cmp;
	}

	
	//unsigned char *hBuffer = (unsigned char *) 0xC1000000;
	void *hBuffer;
	
	//int thisprocess_id = (int) system_call ( 85, 0, 0, 0); 
	//unsigned char *heaptest = (unsigned char *) system_call ( 184, thisprocess_id, 0, 0 );		
	
    // heap
	if ( strncmp( prompt, "heap", 4 ) == 0 )
	{
		
		printf("testando heap\n");
		
		//printf("%x\n", &heaptest[0]);
		
		//heaptest[0] = 'x';
		
		//printf("%c\n", heaptest[0]);
		//hBuffer[0] = 88;
	    //hBuffer[1] = 99;
		//printf("%d %d \n",hBuffer[0],hBuffer[1]);
		
		hBuffer = (void *) malloc ( 1024*100 ); //100kb
        //hBuffer = (void *) malloc ( 1024*1024*3 ); //3mb		
		if ( (void *) hBuffer == NULL )
		{
			printf("malloc fail 100kb\n");
		}else{
			printf("malloc ok 100kb\n");
		}
		
		printf("done\n");
        goto exit_cmp;
    };		
	

	
	
	// help
	// ?
	// Mostra ajuda.
	// Menu. for gramado virtual machine experience.
    if ( strncmp( prompt, "HELP", 4 ) == 0 ||  
	     strncmp( prompt, "help", 4 ) == 0 || 
	     strncmp( prompt, "?", 1 ) == 0 )
	{

		i++;
		token = (char *) tokenList[i];
		
		if( token == NULL )
		{
			help_builtins (1);
			
		}else{
            
			//if ( strncmp( (char*) tokenList[i], "--experience", 12 ) == 0 )
			//{ 
            //    help_builtins (1); 		
			//}
			
			if ( strncmp( (char*) tokenList[i], "--tests", 7 ) == 0 )
			{
                help_builtins (2);				
			}
			
			//...
		};
		goto exit_cmp;
    };	
		
	
	
	
    // kernel-info
	if ( strncmp( prompt, "kernel-info", 11 ) == 0 )
	{
	    shellShowKernelInfo();
        goto exit_cmp;
    };

    // mm-info
	if ( strncmp( prompt, "mm-info", 7 ) == 0 )
	{
	    shellShowMemoryInfo();
        goto exit_cmp;
    };	
	
	
    // mm-kernelheap
	if ( strncmp( prompt, "mm-kernelheap", 13 ) == 0 )
	{
	    shellShowKernelHeapPointer();
        goto exit_cmp;
    };

    // mm-processheap
	if ( strncmp( prompt, "mm-processheap", 14 ) == 0 )
	{
	    shellShowProcessHeapPointer();
        goto exit_cmp;
    };

	// mov
	//if ( strncmp( prompt, "mov", 3 ) == 0 )
	//{
	//    goto exit_cmp;
	//}		

    // metrics
	// Mostra algumas informações de métrica do sistema.
	if ( strncmp( prompt, "metrics", 7 ) == 0 )
	{
		shellShowMetrics ();
        goto exit_cmp;
	};	


	if ( strncmp( prompt, "pipe-test", 9 ) == 0 )
	{       
		shellPipeTest ();
		goto exit_cmp;
    }			
	
    // puts - testing puts, from libc.
	if ( strncmp( prompt, "puts", 4 ) == 0 )
	{
        //@todo: Ainda não existe na libc.
		//puts(" # puts Ok# \n");
        goto exit_cmp;
	};	
	
	if ( strncmp ( prompt, "current-process", 15 ) == 0 )
	{
		system_call ( SYSTEMCALL_CURRENTPROCESSINFO, 0, 0, 0 );
		goto exit_cmp; 
	}



	//scroll
	//usado para teste de scroll
	if ( strncmp( prompt, "scroll", 6 ) == 0 )
	{
		printf ("*SCROLL\n");
		terminal_scroll_display ();
		shellPrompt ();
        goto exit_cmp;
	}
	
	//scroll1
	//usado para teste de scroll
	if ( strncmp( prompt, "scroll1", 7 ) == 0 )
	{
	    testScrollChar ((int) '1');
        goto exit_cmp;		
	}
	
	
	//scroll2
	//usado para teste de scroll
	if ( strncmp( prompt, "scroll2", 7 ) == 0 )
	{
	     testScrollChar ((int) '2');
        goto exit_cmp;		
	}

	

	
	// show-screen-buffer
	// Mostra a área visível dentro do buffer de linhas.
	if ( strncmp( prompt, "show-screen-buffer", 18 ) == 0 )
	{
		terminalShowScreenBuffer ();
		goto exit_cmp;
	}

	

	// socket-test
	// Rotina de teste de soquetes.
	// Esses soquetes não seguem o padrão da libc.
	// Mas no futuro serão absorvidos pela libc.
	
	if ( strncmp( prompt, "socket-test", 11 ) == 0 )
	{       
		shellSocketTest ();
		goto exit_cmp;
    }		



	// slots
	if ( strncmp( prompt, "slots", 5 ) == 0 )
	{
	    printf("~slots - mostra slots \n");
		//mostra_slots();
        goto exit_cmp;
    };
	
	
	// start
	// Inicia uma nova janela(instancia ??) para executar 
	// um programa ou comando desejado.
	//??#bugbug: O que isso deveria fazer ?? 
	//??reiniciar o shell ou iniciar um programa ??
    if ( strncmp( prompt, "start", 5 ) == 0 )
	{
		// Isso deve setar o foco na janela do shell.
		// ao mesmo tempo que reinicia o input para digitação 
		// e ajusta as margens do cursor. :)
		// Qualquer editbox precisa desse tipo de ajuste.
	    
		gde_set_focus (window);
		//shellPrompt();
		printf("~start\n");
		
		goto exit_cmp;
    };

    // systeminfo
	// informações sobre o sistema.
	if ( strncmp( prompt, "system-info", 11 ) == 0 )
	{
	    printf("~@todo: system info.\n");
		shellShowSystemInfo();
        goto exit_cmp;
    };	
	

	
	// tty-info
	// Pegar informações sobre a tty atual.
    int TTY_ID;	
	if ( strncmp( prompt, "tty-info", 8 ) == 0 )
	{	
		TTY_ID = (int) system_call ( 236, 0, 0, 0 );		
        
		printf ("tty %d \n", TTY_ID);
		goto exit_cmp;
    };
	
	
    // t1 - Test file
	// Carrega um arquivo no buffer de words 
	// depois exibe todo o buffer mantendo o posicionamento 
	//no cursor. Isso força um scroll.
	if ( strncmp( prompt, "t1", 2 ) == 0 )
	{	
		shellTestLoadFile();		
        goto exit_cmp;
    };
	
	
	// t2 - Test bmp
	if ( strncmp( prompt, "t2", 2 ) == 0 )
	{
		terminalTestDisplayBMP ();
        goto exit_cmp;
    };	
	
	
	// t3 - Test thread
	if ( strncmp( prompt, "t3", 2 ) == 0 ||
        strncmp( prompt, "test-thread", 11 ) == 0	)
	{
	    shellTestThreads();
        goto exit_cmp;
    };
	
	//@todo: Colocar no início dessa função.
	FILE *f1;
	int ch_test;
	
	// t4 - testando fopen
	if ( strncmp( prompt, "t4", 2 ) == 0 )
	{
		printf("\n t4: Open init.txt \n");
        
		f1 = (FILE *) fopen ("init.txt","rb");
        if( f1 == NULL )
		{
			printf("fopen fail\n");
		}else{
			printf("fopen ok\n");
		}
		
		//Isso mostra que o arquivo foi carregado corretamente 
		//na base esperada.
		//printf("Show f1->_base: %s\n",f1->_base);
		
		//printf("stream info:\n");
		//printf("f1->_base: %x\n",f1->_base);
		//printf("f1->_ptr: %x\n",f1->_ptr);
		//printf("f1->_cnt: %d\n",f1->_cnt);
		
		//
		// #bugbug ... o fgetc não lê na estrutura esperada.
		//
		printf("Testing fgetc ... \n\n");
		while(1)
		{
			//#bugbug: page fault quando chamamos fgetc.
			//printf("1");
			ch_test = (int) fgetc (f1);
			//ch_test = (int) getc (f1); 
			
			if( ch_test == EOF )
			{
				printf("\n\n");
				printf("EOF reached :)\n\n");
				goto exit_cmp;
				
			}else{
				//printf("2");
			    printf("%c", ch_test);
			};
		};
		
		//fail.
		goto exit_cmp;
    };

	// t5 - ( save file )
	// Ok isso funcionou.
	if ( strncmp( prompt, "t5", 2 ) == 0 )
	{
		printf("t5: save file\n");
		save_string2 ( "t5: Salvando texto em test1234.txt \n", "TEST1234TXT" );
		//shell_save_file ();
		printf("t5: done\n");
        goto exit_cmp;
    };	


	// t7
	// Testando estado das teclas.
	if ( strncmp( prompt, "KEYS", 4 ) == 0 ||
         strncmp( prompt, "keys", 4 ) == 0 || 
         strncmp( prompt, "T7", 2 ) == 0 || 		 
	     strncmp( prompt, "t7", 2 ) == 0 )	
	{
		printf ("VK_CAPITAL %d \n", system_call ( 138, 
		    VK_CAPITAL, VK_CAPITAL, VK_CAPITAL ) );				
	    printf ("VK_LSHIFT %d \n", system_call ( 138, 
			VK_LSHIFT, VK_LSHIFT, VK_LSHIFT ) );
		printf ("VK_RSHIFT %d \n", system_call ( 138, 
			VK_RSHIFT, VK_RSHIFT, VK_RSHIFT ) );
		printf ("VK_CONTROL %d \n", system_call ( 138, 
			VK_CONTROL, VK_CONTROL, VK_CONTROL ) );
		printf ("VK_WINKEY %d \n", system_call ( 138, 
			VK_WINKEY, VK_WINKEY, VK_WINKEY ) );
		printf ("VK_LMENU %d \n", system_call ( 138, 
			VK_LMENU, VK_LMENU, VK_LMENU ) );
		//...
		goto exit_cmp;
	};
	
	//Testando a criação de botão e a interação com ele através do mouse.
	if ( strncmp( prompt, "t8", 2 ) == 0 )
    {
	    terminalTestButtons ();	
		gde_show_backbuffer ();
		
		goto exit_cmp;
	};	

	
	// t9 - Show lines.
	if ( strncmp( prompt, "t9", 2 ) == 0 )
    {    
        testShowLines ();	
		goto exit_cmp;
	};
	
	
    // t10 - Show visible area.
	if ( strncmp( prompt, "t10", 3 ) == 0 )
    {    
	    testChangeVisibleArea ();
		goto exit_cmp;
	};
	
	
	// t11 - 
    // Envia uma mensagem para a thread atual.
    // Nesse caso a thread atual é essa mesma, que é a thread de controle
	// do processo shell.
	// Isso funcionou bem.
	// ex: Chama message box com mensagem about.
	
	if ( strncmp( prompt, "t11", 3 ) == 0 )
    {    
        gde_send_message ( (struct window_d *) 0, 
			(int) MSG_COMMAND, 
		    (unsigned long) CMD_ABOUT, 
			(unsigned long) 0 );
		
		goto exit_cmp;
	};
	
	
	// t12
	// testando mudar um retângulo de lugar.
	// + salva o retângulo num buffer 
	// + copia do buffer para o backbuffer 
	if ( strncmp( prompt, "t12", 3 ) == 0 )	
	{
        printf("t12: test rect \n");
		
		gde_enter_critical_section (); 
		message_buffer[0] = 100;
		message_buffer[1] = 100;
		message_buffer[2] = 100;
		message_buffer[3] = 100;
		system_call ( 132,
		    (unsigned long) &message_buffer[0],
			(unsigned long) &message_buffer[0],
			(unsigned long) &message_buffer[0] );
		message_buffer[0] = 50;
		message_buffer[1] = 50;
		message_buffer[2] = 100;
		message_buffer[3] = 100;			
		system_call ( 133,
		    (unsigned long) &message_buffer[0],
			(unsigned long) &message_buffer[0],
			(unsigned long) &message_buffer[0] );
		gde_exit_critical_section(); 
		
        goto exit_cmp;					 
	};	
	
	// escrevendo em stdout e mostrando.
	if ( strncmp( prompt, "t13", 3 ) == 0 )
    {    
        //#obs 
        //#lembrando: podemos ter problemas com o buffer do arquivo.		

	    //coloca no stdout.
		stdout_printf("Escrevendo no stdout com stdout_printf \n");
		
		//mostra o arquivo desde o começo.
		//printf(stdout->_base);

		goto exit_cmp;
	};	
	
	if ( strncmp( prompt, "t14", 3 ) == 0 )
	{
		
		printf ("t14:\n");
	    terminalCreateWindow ();
		
		//#bubug
		//Vamos abortar por causa de uma page fault.
		printf ("t14: debug *hang\n");
		while(1){}
		
		goto exit_cmp;
	}
	
	
	//testando open()
	//precisa incluir fcntl.h
	int ooofd;
	if ( strncmp( prompt, "t15", 3 ) == 0 )
	{
		printf ("t15: open() Opening file init.txt\n");
		ooofd = open ( "init.txt", 0, 0 );
		
		printf ("descriptor=%d \n", ooofd );
		goto exit_cmp;
	}
	
	
	//testando close()
	//precisa incluir fcntl.h
	int cccRet;
	if ( strncmp( prompt, "t16", 3 ) == 0 )
	{
		printf ("t16: close() Closing file '0' \n");
		cccRet = close (0);
		
		printf ("ret=%d \n", cccRet );
		goto exit_cmp;
	}
	
	
	//chamado rotinas para abrir e fechar um servidor do modulo gramado core.
	if ( strncmp( prompt, "t17", 3 ) == 0 )
    {   
		//abrir
	    //serviço, sender pid, receiver index
		system_call ( 8000, 100, 1, 0 );
		
		//fechar
		//serviço, sender pid, receiver index
        system_call ( 8001, 100, 1, 0 );
		
		goto exit_cmp;
	};


	// t18
	// Send message to a process.
	// Envia uma mensagem para a thread de controle de um processo.
	// Nesse teste vamos mandar uma mensagem para esse processo mesmo.

	if ( strncmp( prompt, "t18", 3 ) == 0 )
	{
        gde_enter_critical_section ();
        printf ("t18:\n");

        //fprintf (stdout, "This is a string in stdout \n" );
         
		//get pid
        PID = (int) system_call ( SYSTEMCALL_GETPID, 0, 0, 0 );

		//Enviando uma mensagem para um processo.		
		//__PostMessageToProcess ( PID, NULL, MSG_TERMINALCOMMAND, 
		    //TERMINALCOMMAND_PRINTCHAR, TERMINALCOMMAND_PRINTCHAR );	 
		       
		// #Bugbug: A mensagem é postada na verdade e demora para ser lida,
		//então teremos uma sobreposição, pois não temos fila ainda.
		//__PostMessageToProcess ( PID, NULL, MSG_TERMINALCOMMAND, 2005, 4 );	
		//__PostMessageToProcess ( PID, NULL, MSG_TERMINALCOMMAND, 2006, 4 );	
		
		__PostMessageToProcess ( PID, NULL, MSG_TERMINALCOMMAND, 2020, 2020 );		
        
		//obs: essa rotina existe nas libs do projeto gramado.
		//apiSendMessageToProcess ( PID, NULL, MSG_COMMAND, CMD_ABOUT, CMD_ABOUT );

		//__PostMessageToProcess ( PID, NULL, MSG_COMMAND, CMD_ABOUT, CMD_ABOUT );
		
       	printf ("t18: done\n");
        gde_exit_critical_section ();

        goto exit_cmp;
	}
	
	if ( strncmp( prompt, "t19", 3 ) == 0 )
	{		
        fprintf ( stdout, "noraterm: testing stdout \n");
        fprintf ( stderr, "noraterm: testing stderr \n");	
		fflush (stdout);
		fflush (stderr);
        goto exit_cmp;		
	}
   
	//t20 OpenTTY.
	FILE *opentty_fp;
	FILE *terminal_opentty_fp;
	int x_ch;
	if ( strncmp ( prompt, "t20", 3 ) == 0 )	
	{
		printf("t20: \n");
		//get tty stream
		//pega um stream para escrever.
		opentty_fp = (FILE *) system_call ( 1000, getpid(), 0, 0 );
		
		stdout = opentty_fp;
		
		fprintf (stdout, "test1 ...");   //sem \n
		fprintf (stdout, "test2 ...\n");   
		
		//Vamos avisar o terminal que ele pode pegar os chars na stream do tty
		//apiSendMessageToProcess ??
		//__PostMessageToProcess ( getpid(), NULL, MSG_TERMINALCOMMAND, 2000, 2000 );
	    __PostMessageToProcess ( getpid(), NULL, MSG_TERMINALCOMMAND, 2020, 2020 );
		
		//get tty stream
		//o terminal pegar um stream para ler.
		//terminal_opentty_fp = (FILE *) system_call ( 1001, 0, 0, 0 );
		 
	    //x_ch = (int) fgetc (terminal_opentty_fp);	
		
		//while (1)
		//{
		    //pega um char, mas não é o último que foi colocado, é o que ainda não foi pego.
		    //x_ch = (int) system_call ( 1002, 0, 0, 0 );
		   // if (x_ch == '\n'){ break;};
			
			//printf (" CHAR:{%c} \n",x_ch);
	    //}
		goto exit_cmp;
	}
	
	
	// t21 - Chama um programa.
	if ( strncmp ( prompt, "t21", 3 ) == 0 )
	{
		// Isso já foi feito na inicialização do terminal.
		//printf ("t21: registrando terminal e criando shell como processo filho\n");
		//printf ("t21: Executing child process ...\n");
		
		// registrando teminal.
		system_call ( 1003, getpid(), 0, 0 );
		
		// Isso funciona.
		//>>> clona e executa o filho dado o nome do filho.
		system_call ( 900, (unsigned long) "hello3.bin", 0, 0 );
		
		//system_call ( 900, (unsigned long) "hello.bin", 0, 0 );
		//system_call ( 900, (unsigned long) "gdeshell.bin", 0, 0 );
         
        //printf ("t21: done\n"); 
		goto exit_cmp;
	}
	
	//write char on x y.
	//ok isso funcionou.
	if ( strncmp ( prompt, "t22", 3 ) == 0 )
	{	
	    __PostMessageToProcess ( getpid(), NULL, MSG_TERMINALCOMMAND, 2021, 'X' );
        goto exit_cmp;
    }

    //t23
    // Tentando atualizar a barra de status da janela.
    if ( strncmp ( prompt, "t23", 3 ) == 0 )
    {
		//#funciona.
		//system call
		//system_call ( 300, (unsigned long) main_window, 
		//(unsigned long) "| 1 Updating status bar", 
		//(unsigned long) "| 2 Updating status bar" );
		
		//#test
		//api function
		//apiUpdateStatusBar ( (struct window_d *) main_window,
		  //   "|new String 1", "|new String 2");	
        goto exit_cmp;		
	}
	
	
	
	// t24 - test api, drawtext.
	if ( strncmp ( prompt, "t24", 3 ) == 0 )
	{
	    __PostMessageToProcess ( getpid(), NULL, MSG_TERMINALCOMMAND, 
	        2002, 2002 );		
	    goto exit_cmp; 	
	}    
	
	
	
	// setup-x
	// setup x server PID
	if ( strncmp( prompt, "setup-x", 7 ) == 0 )
	{
	    gde_enter_critical_section ();
		
		//get current pid
        PID = (int) system_call ( SYSTEMCALL_GETPID, 0, 0, 0 );
		
		// set x server PID
		system_call ( 513, PID, PID, PID );
		
		gde_exit_critical_section ();
		goto exit_cmp;
	}

    // test-x
	if ( strncmp( prompt, "test-x", 6 ) == 0 )
	{
	    gde_enter_critical_section ();
		
		//get x server pid
        PID = (int) system_call ( 512, 0, 0, 0 );
		
		//Enviando uma mensagem para a thread de controle do processo x server.
        //obs: essa rotina existe nas libs do projeto gramado.
		//apiSendMessageToProcess ( PID, NULL, MSG_COMMAND, CMD_ABOUT, CMD_ABOUT );
		
		gde_exit_critical_section ();		
		goto exit_cmp;
	}
	

    // show x server info
	if ( strncmp( prompt, "xserver-info", 12 ) == 0 )
	{
	    gde_enter_critical_section ();
		
        system_call ( 516, 0, 0, 0 );
				
		gde_exit_critical_section ();	
		goto exit_cmp;
	}

    // show wm info
	if ( strncmp( prompt, "wm-info", 7 ) == 0 )
	{
	    gde_enter_critical_section ();
		
        system_call ( 517, 0, 0, 0 );
				
		gde_exit_critical_section ();	
		goto exit_cmp;
	}

	//flush stdout
	if ( strncmp( prompt, "flush-stdout", 12 ) == 0 )
	{
		fflush (stdout);
		goto exit_cmp;
	}

	

	
	
    //test-taskman-server - testando servidor taskman
	if ( strncmp( prompt, "test-taskman-server", 19 ) == 0 )
	{
		//só podemos enviar a próxima mensagem depois que a primeira for atendida.
		//pois ainda não temos fila de mensagens e o servidor demora para receber 
		//tempo de processamento.
        system_call ( 116, 123, 0, 0 );
		//system_call ( 116, 1000, 0, 0 );
		//system_call ( 116, 2000, 0, 0 );
		//system_call ( 116, 3000, 0, 0 );
		//system_call ( 116, 4000, 0, 0 );
        goto exit_cmp;
	};	
	
	
	// timer-test
	// Essa rotina cria um objeto timer que gera um interrupção 
	// de tempos em tempos e é tratado pelo procedimento de janelas.
	if ( strncmp( prompt, "timer-test", 10 ) == 0 )
	{  
		printf("timer-test: \n");
		
	    testsInitTimer ( (struct window_d *) window );
        
		printf("timer-test: done\n");		  
		
        goto exit_cmp;
    };
	

	// taskbar
    if ( strncmp( prompt, "taskbar", 7 ) == 0 )
	{
		terminalCreateTaskBar ();
		goto exit_cmp;
    };			
	
	
	// test-terminal
    // o terminal executa um processo filho que
    // lhe enviará mensagens.
    // Para isso tem que passar para o processo filho o PID
    // do terminal;
    if ( strncmp( prompt, "test-terminal", 13 ) == 0 )
	{
		//#todo
		goto exit_cmp;
    };		
	
	

    // volume-info
	if ( strncmp( prompt, "volume-info", 11 ) == 0 )
	{
	    shellShowVolumeInfo();
        goto exit_cmp;
    };	
	

	// window
    if ( strncmp( prompt, "window", 6 ) == 0 )
	{
		terminalShowWindowInfo ();
        goto exit_cmp;
    };

	
	
	// ==============================
	//     Fim das comparações     //
	// ==============================
	
	
	
    // #obs
	// Se apertamos o enter e não encontramos um comando válido
    // então damos um aviso de comando inválido e reiniciamos o prompt 
    // na próxima linha.
	
	// Inicializando o retorno.
	// fail.
	
	int Execve_Ret = 1;
	
	// ??
    //unsigned long a1 = (unsigned long) tokenList[0];
	//char *a1 = tokenList[1];
	//char *a1 = tokenList[2];
	
	
doexec_first_command:

    //
	// ## TEST ##
	//

	// #bugbug
	// #todo:
	// Rever essa rotina.
	// Um pathname absoluto começa no início do diretório raiz,
	// declarandoem que volume está. ex: root:/volume1/... ou /volume1/...
	
    absolute = absolute_pathname ( (char *) tokenList[0] );
	
    switch (absolute)
	{
		//Não é absoluto ou falhar
		case 0:
		    //printf("doexec_first_command: not absolute pathname\n");
		    break;
			
		//é absoluto	
		case 1:
		    printf("doexec_first_command: absolute pathname\n");		
			break;
			
		//falha	
		case 2:
		default:
		    printf("doexec_first_command: pathname fail\n");
			break;
	};   

    // ./
	// + Eliminar ./ pois se trata de arquivo no diretório atual.
	
	if (absolute == 1)
	{
		//#bugbug: Essa definição não deve ficar aqui.
		char *t = (char *) tokenList[0];
		
		if ( *t == '.' )
		{
			t++;
			
		    if ( *t == '/' )
			{	
				t++;
				tokenList[0] = (char *) t;
			}
	    };	
	};
		
	
	// #todo: 
	// Colocar isso no início dessa função.

    unsigned long buffer[5];
    int z;

	// Colocamos todos os ponteiros no array.

    for ( z=0; z<token_count; z++ )
    {
        buffer[z] = (unsigned long) tokenList[z];
    }

    //
    //  #test
    //  Testando novo jeito.
    //

    /*
    printf ("=======================\n"); 
	printf ("Executing child process ...\n");
	// registrando teminal.
	system_call ( 1003, getpid(), 0, 0 );
	//>>> clona e executa o filho dado o nome do filho.
	system_call ( 900, (unsigned long) &tokenList[0], 0, 0 );		         
    printf ("done\n"); 
    goto exit_cmp;	
    //goto fail;    
    printf ("=======================\n"); 
    */



    // #bugbug
    // Não usar mais execve no garden. usar service 900;
 

	// ## ISSO DEU CERTO ## 	
	// Passamos anteriormente a linha de comandos via memória compartilhada,
	// agora então precisamos passar somente o nome do arquivo.	

	// Ok, funcionou e o arquivo foi carregado,
	// mas demora para receber tempo de processamento.
	
    //Execve_Ret = (int) shell_gramado_core_init_execve ( 
    //                       (const char *) tokenList[0], 
    //                       (const char *) 0,
    //                       (const char *) 0);
	
    Execve_Ret = (int) execve ( (const char *) tokenList[0], 
                           (const char *) 0,
                           (const char *) 0);

	if ( Execve_Ret == 0 )
	{
		//
		// ## WAIT ??
		//
		
		// Aqui temos uma decisão a tomar.
		// Se o aplicativo executou corretamente e esta em primeiro 
		// plano então devemos entrar em wait.
		// Se o aplicativo funcionou corretamente mas está em segundo 
		// plano então decemos continuar. 
		// Por enquanto estamos continuando e rodando concomitantemente.
		
		//
		// # Stop running #
		//
		
		// Isso sai do loop de mensagens e sai do shell elegantemente.
		
		running = 0;
		
	    goto exit_cmp;	
		
	}else{
		
		// falhou. 
		// Significa que o serviço não conseguir encontrar o arquivo ou 
		// falhou o carregamento.
		
		printf ("shell: execve: fail\n");
		
		goto fail;
	};
	
	
	//
	// # dobin #
	//
	
	// Vamos executar um programa .bin.
	// .bin é a extensão padrão.
	// Executaremos o segundo comando, pois o primeiro é ~$dobin.
	
dobin:

    if( is_bin( (char *) tokenList[1] ) != 1 )
    {
        printf ("dobin: it's not a .bin filename.\n");
        printf ("dobin: fail\n");

		//@todo: back ...
    };

	//Precisamos passar somente o nome pois a linah de comando 
	//já foi enviada através de memória compartilhada.

    Execve_Ret = (int) shell_gramado_core_init_execve( 
                           (const char*) tokenList[1],
                           (const char*) 0, 
                           (const char*) 0 ); 

	// Ok, funcionou e o arquivo foi carregado,
	// mas demora para receber tempo de processamento.

    if ( Execve_Ret == 0 )
    {
		//
		// ## WAIT ??
		//
		
		// Aqui temos uma decisão a tomar.
		// Se o aplicativo executou corretamente e esta em primeiro 
		// plano então devemos entrar em wait.
		// Se o aplicativo funcionou corretamente mas está em segundo 
		// plano então decemos continuar. 
		// Por enquanto estamos continuando e rodando concomitantemente.
		
		//
		// # Stop running #
		//
		
		//Isso sai do loop de mensagens e 
		//sai do shell elegantemente.
		running = 0;
		
	    goto exit_cmp;	
	}else{
		// falhou. Significa que o serviço naõ conseguir encontrar 
		// o arquivo ou falhou o carregamento.
		printf("shell: execve fail\n");
		goto fail;
	};	
	
	
	
// Tente executar um aplicativo com outra extensão.
// Checaremos se é uma extensão das suportadas.	
	
dotry:
    	
    //Precisamos passar somente o nome pois já passamos 
	//a linha de comandos através de memória compartilhada.
    Execve_Ret = (int) shell_gramado_core_init_execve( 
	                       (const char*) tokenList[1], //Name
	                       (const char*) 0,            //Null
						   (const char*) 0 );          //Null
						 
	// Ok, funcionou e o arquivo foi carregado,
	// mas demora para receber tempo de processamento.
	if( Execve_Ret == 0 )
	{
		//
		// ## WAIT ??
		//
		
		// Aqui temos uma decisão a tomar.
		// Se o aplicativo executou corretamente e esta em primeiro 
		// plano então devemos entrar em wait.
		// Se o aplicativo funcionou corretamente mas está em segundo 
		// plano então decemos continuar. 
		// Por enquanto estamos continuando e rodando concomitantemente.
		
		//
		// # Stop running #
		//
		
		//Isso sai do loop de mensagens e 
		//sai do shell elegantemente.
		running = 0;		
		
	    goto exit_cmp;	
	}else{
		// falhou. Significa que o serviço naõ conseguir encontrar 
		// o arquivo ou falhou o carregamento.
		printf("shell: execve fail\n");
		goto fail;
	};		
	
	
	//
	// # Script #
	//
	
	// Um comando no shell invoca a execussão de um script 
	// dado o nome via tokenList.
	
dosh:

	// Vamos tentar colocar o arquivo de script no stdin 
	// que é onde fica o prompt. Então retornaremos no 
	// início dessa rotina mas agora com uma nova linha de comando.
	//
    //nothing for now.
	//o comando [0] é o 'dosh' o [1] é o nome do script.

    if ( is_sh1( (char *) tokenList[1] ) != 1 )
	{
		printf ("dosh: it's not a .sh1 filename.\n");
		printf ("dosh: fail\n");
	};

    // #ok
	// Estamos passando o nome do arquivo.
	
	//#todo:
	//Essa função deve chamar o interpretador de script
	shellExecuteThisScript ( tokenList[1] );	
	
	//#todo 
	//Podemos apenas sair já a função acima executou o script
	//goto exit_cmp;
	
	goto NewCmdLine;
	
	
//
//  ## Fail ##
//	
	
fail:	
	
    printf (" Unknown command!\n");
    
	ret_value = 1;
	
	goto done;
	
	
   //====================
   //    ## EXIT CMP ##
   //====================	

	
exit_cmp:

    ret_value = 0;	
	
done:

	// Limpando a lista de argumentos.
	// Um array de ponteiros.

	for ( i=0; i<TOKENLIST_MAX_DEFAULT; i++ )
	{
		tokenList[i] = NULL;
	};

	shellPrompt ();
	
	// #bugbug:
	// Queremos dar refresh apenas da janela.
	// Mostrando as strings da rotina de comparação.	
	
	// refresh_screen ();
	
    return (unsigned long) ret_value;
}





/*
 *******************************************
 * terminalInitSystemMetrics:
 *     mudar para noratermInitSystemMetrics
 */

// #importante
// Já na inicialização solicita as infomações que os sistema pode nos dar.
// ?? Pegaremos todas as metricas de uma vez só,
// se uma falhar, então pegaremos tudo novamente.

// #importante
// #todo: Criar uma função que mostre todas as informações obtidas
// #todo: Criar uma função que mostre todas as informações configuradas
// Mostre as informações depois de criar uma tela.

void terminalInitSystemMetrics (){
	
	
	//Tamanho da tela. (full screen)
	smScreenWidth = gde_get_system_metrics (1);
	smScreenHeight = gde_get_system_metrics (2); 
	
	//cursor
	smCursorWidth = gde_get_system_metrics(3);
	smCursorHeight = gde_get_system_metrics(4);
	
	//mouse
	smMousePointerWidth = gde_get_system_metrics(5);
	smMousePointerHeight = gde_get_system_metrics(6);
	
	//char
	smCharWidth = gde_get_system_metrics(7);
	smCharHeight = gde_get_system_metrics(8);
	
	
	//#todo:
	//vertical scroll size
	//horizontal scroll size.
	
	//#importante
	//#todo: pegar mais.
	
	//...
	
	//#todo: Temos que criar essa variável.
	//InitSystemMetricsStatus = 1;
} 


/*
 * terminalInitWindowLimits:
 *     #todo: mudar para noratermInitWindowLimits
 *    #importante
 */

//#todo:
//ordem: fullscreeen sizes, font sizes, mínimos e máximos.

void terminalInitWindowLimits (){
	
	// #todo
	// Tem variáveis aqui que não podem ser '0'.
	
	//#todo: temos que criar essa variável.
	/*
	if (InitSystemMetricsStatus == 0)
	{
	    terminalInitSystemMetrics ();
	}
	*/
	
    //
    // ## Window limits ##
    //
	
	// problemas; 
	//if ( smScreenWidth == 0 || smScreenHeight )
	//{
	//	 printf ...
	//}

    //full screen support
    wlFullScreenLeft = 0;
    wlFullScreenTop = 0;
    wlFullScreenWidth = smScreenWidth;
    wlFullScreenHeight = smScreenHeight;
	
    //limite de tamanho da janela.
    wlMinWindowWidth = smCharWidth * 80;
    wlMinWindowHeight = smCharWidth * 25;
    wlMaxWindowWidth = wlFullScreenWidth;
    wlMaxWindowHeight = wlFullScreenHeight;	
	
    //quantidade de linhas e colunas na área de cliente.
    wlMinColumns = 80;
    wlMinRows = 1;


	
	//dado em quantidade de linhas.
    textMinWheelDelta = 1;  //mínimo que se pode rolar o texto
    textMaxWheelDelta = 4;  //máximo que se pode rolar o texto	
	textWheelDelta = textMinWheelDelta;
	//...
}


void terminalInitWindowSizes()
{
	
//
//  ## Window size ##
//

    //wsWindowWidth = wlMinWindowWidth;
    //wsWindowHeight = wlMinWindowHeight;	
	
	//Tamanho da janela do shell com base nos limites 
    //que ja foram configurados.	
	
	wsWindowWidth =  WINDOW_WIDTH;
	wsWindowHeight = WINDOW_HEIGHT;
	
	
	if ( wsWindowWidth < wlMinWindowWidth )
	{
		wsWindowWidth = wlMinWindowWidth;
	}
	
	if ( wsWindowHeight < wlMinWindowHeight )
	{
	    wsWindowHeight = wlMinWindowHeight;	
	}
}


void terminalInitWindowPosition()
{
	
	//window position
	wpWindowLeft = WINDOW_LEFT;
	wpWindowTop = WINDOW_TOP;
	
	//wpWindowLeft = (unsigned long) ( (smScreenWidth - wsWindowWidth)/2 );
	//wpWindowTop = (unsigned long) ( (smScreenHeight - wsWindowHeight)/2 );  	
}




/*
 ******************************************
 * terminalTerminal:
 *     Constructor.
 *     Não emite mensagens.
 */

// #bugbug
// essas configurações são configurações de janela,
// então estão mais para terminal do que para shell.


void terminalTerminal (){
	
	int i=0;
	int j=0;
	
	// Internas.
	
    shellStatus = 0;
    shellError = 0;
	
	
	//
	// ## Inicializando as estruturas de linha ##
	//
	
	//inicializamos com espaços.
	for ( i=0; i<32; i++ )
	{
		for ( j=0; j<80; j++ )
		{
		    LINES[i].CHARS[j] = (char) ' ';
		    LINES[i].ATTRIBUTES[j] = (char) 7;
	    }
		
		LINES[i].left = 0;
		LINES[i].right = 0;
		LINES[i].pos = 0;
	};
	
	
	
	// Deve ser pequena, clara e centralizada.
	// Para ficar mais rápido.
	
	// #importante:
	// O aplicativo tem que confiar nas informações 
	// retornadas pelo sistema.
		
	// Usar o get system metrics para pegar o 
	// tamanho da tela.
	
	//inicializa as metricas do sistema.
	terminalInitSystemMetrics ();
	
    //inicializa os limites da janela.
	terminalInitWindowLimits ();
	
	//inicia o tamanho da janela.
	terminalInitWindowSizes ();
	
	//inicializar a posição da janela.
	//terminalInitWindowPosition ();
 
 
    //
	// initialize visible area.
	// #todo: criar função para isso
	// É melhor que seja pequena por enquanto pra não ativar
	// o scroll do kernel e só usar o scroll desse terminal.
	
	//textTopRow = 0;
	//textBottomRow = 24;
    terminalNewVisibleArea ( 0, 19);


	//...	

	
	// Obs:
	// prompt[] - Aqui ficam as digitações. 

	terminalClearBuffer ();

	
	//shellBufferMaxColumns = DEFAULT_BUFFER_MAX_COLUMNS;
	//shellBufferMaxRows    = DEFAULT_BUFFER_MAX_ROWS;
	
	//buffersize = (shellBufferMaxColumns * shellBufferMaxRows);
	

	
	//
	// @todo: E o fluxo padrão. Quem configurou os arquivos ???
	//        o kernel configuroru???
	//
	
    //...
	
	
	for ( i=0; i<WORKINGDIRECTORY_STRING_MAX; i++ ){
		current_workingdiretory_string[i] = (char) '\0';
	};
	
    sprintf ( current_workingdiretory_string, 
	    SHELL_UNKNOWNWORKINGDIRECTORY_STRING );    
	
	//...
	
//done:

    ShellFlag = SHELLFLAG_COMMANDLINE;
	
    //#bugbug
	//Nossa referência é a moldura e não a área de cliente.
	//@todo:usar a área de cliente como referência
	//terminalSetCursor(0,0);
    //terminalSetCursor(0,4);
    
	//@todo
	//tentando posicionar o cursor dentro da janela
	//terminalSetCursor( (shell_info.main_window->left/8) , (shell_info.main_window->top/8));	
	
	//shellPrompt();
}


/*
 ******************************************
 * terminalInit:
 *     Inicializa o Shell.  
 *
 * @todo: Inicializar globais e estruturas.
 */
 
// #bugbug
// Essa rotina contém coisas de terminal e de shell
// precisa organizar isso.

	// #bugbug ??
	// O ponteiro do argumento pode ser inválido, pois 
	// é uma variável local.
	// Agora é global.

int terminalInit ( struct window_d *window ){

    int PID;
    int PPID;

    int ActiveWindowId = 0;
    int WindowWithFocusId = 0;

    // ?
    void *P;


    char buffer[512];



	// Registrar o terminal na estrutura de tty.
    
    PID = getpid ();
    system_call ( 1003, PID, PID, PID );



	// #bugbug:
    //     Esse ponteiro de estrutura está em kernel mode. 
	//     Não podemos usá-lo.
	
	//??
	//stream status
	shell_info.stream_status = 0;
	


	//
	// Window support.
	//

	// Testando a validade do ponteiro da janela.
	// #importante: A estrutura está em kernel mode 
	// e não podemos acessa-la.
	
	if ( (void *) window == NULL )
	{
	    printf ("shellInit: window fail.\n"); 
	    
	    //# hang??
		
	} else {
		
		// Nesse momento temos um ponteiro válido,
		// mas infelismente não podemos testar outros elementos 
		// da estrutura.
		
		gde_set_focus ( window );
		
		// mensagens !!
		
#ifdef SHELL_VERBOSE		
		printf("shellInit: Starting shell.bin ...\n");
		printf("shellInit: Running tests ...\n");
#endif
		
	};
	
	
	//
	// Obtendo informações sobre a janela ativa.
	//
	
	//Active window
	ActiveWindowId = (int) gde_get_active_window ();
	
	//valor de erro
	if ( ActiveWindowId == (-1) ){
		
	    printf("shellInit: ERROR getting Active window ID\n");	
	}	
	
#ifdef SHELL_VERBOSE			
	printf("ActiveWindowId={%d}\n", ActiveWindowId );
#endif
	
	// Obtendo informações sobre a janela com o foco de entrada.

	// Focus.
	WindowWithFocusId = (int) gde_get_focus();
	
	//valor de erro
	if ( WindowWithFocusId == (-1) ){
	    printf("shellInit: ERROR getting Window With Focus ID\n");	
	}	
	
#ifdef SHELL_VERBOSE			
	printf("WindowWithFocusId={%d}\n", WindowWithFocusId );	
#endif
	
	//
	// Obetendo informações sobre linhas e colunas do shell.
	//
	
	
//#ifdef SHELL_VERBOSE		
	//columns and rows
	//printf("__wlMaxColumns={%d} \n", __wlMaxColumns );
	//printf("__wlMaxRows={%d} \n", __wlMaxRows );	
//#endif
	
	//
	//printf ("debug *breakpoint");
	//while(1){}
	
	//
	// Process support.
	//
	
	// @todo: 
	// Essa mensagem está aparecendo fora da área de trabalho do shell
	// pois ainda não temos um ponteiro para a memória que representa essa área.
	// Talvez as mensagens devessem ir para um buffer de linha antes de irem 
	// para a memória de vídeo.
	// #Impotante:
	// Devemos utilizar as configurações de terminal virtual, respeitar a estrutura 
	// de terminal, que indicará qual é a janela de terminal onde os caracteres 
	// devem ser escritos. Na verdade é um ponteiro para um retãngulo e não para 
	// uma janela. Obs: Esse retângulo do terminal deve esr configurável e uma rotina 
	// deve dar suporte a essa configuração.
	

	// @todo: 
	// O que tevemos fazer aqui é pegar informações sobre o processo Shell
	// e coloca-las na tela.
	

	// @todo: Criar na API uma rotina de inteface que use essa chamada.
	// ex: APIGetPID().

	
	//PID = (int) APIGetPID();
	
	//#todo usar libc
	
    PID = (int) system_call( SYSTEMCALL_GETPID, 0, 0, 0 );
	if ( PID == (-1) ){
	    printf("ERROR getting PID\n");	
	}
  
    PPID = (int) system_call( SYSTEMCALL_GETPPID, 0, 0, 0 );
	if ( PPID == (-1) ){
	    printf("ERROR getting PPID\n");	
	}
  
    //Mensagem ...
	//printf("Starting SHELL.BIN ... PID={%d} PPID={%d} \n", PID, PPID );
	
	
	// @todo: Criar processos processos:
	//     E.BIN, F.BIN, G.BIN, A.BIN, B.BIN, C.BIN, D.BIN
 	//     (Mermaids) Usados para testes.

//#ifdef SHELL_VERBOSE			
//	printf("Creating processes ...\n");
//#endif

/*
    printf("Creating process ...\n");	
	//D.:)
	P = (void *) apiCreateProcess ( 0x400000, PRIORITY_HIGH, "NEW-PROCESS");
	if ( (void *) P==NULL )
	{
		printf ("Fail creating process D :)\n");
	};
*/	
	
	/*
#ifdef SHELL_VERBOSE
    
    printf("Creating processes ...\n");	
	//D.:)
	P=(void*)apiCreateProcess(0x400000,PRIORITY_HIGH,"D");
	if((void*)P==NULL){printf("Fail creating process D :)\n");};
	//C.
	P=(void*)apiCreateProcess(0x400000,PRIORITY_HIGH,"C");
	if((void*)P==NULL){printf("Fail creating process C.\n");};
	//B.
	P=(void*)apiCreateProcess(0x400000,PRIORITY_HIGH,"B");
	if((void*)P==NULL){printf("Fail creating process B.\n");};
	//A.(Balance).
	P=(void*)apiCreateProcess(0x400000,PRIORITY_NORMAL,"A");	
	if((void*)P==NULL){printf("Fail creating process A.\n");};
	//G.
	P=(void*)apiCreateProcess(0x400000,PRIORITY_LOW,"G");	
	if((void*)P==NULL){printf("Fail creating process G.\n");};
	//F.
	P=(void*)apiCreateProcess(0x400000,PRIORITY_LOW,"F");
	if((void*)P==NULL){printf("Fail creating process F.\n");};
	//E.
	P=(void*)apiCreateProcess(0x400000,PRIORITY_LOW,"E");	
	if((void*)P==NULL){printf("Fail creating process E :( \n");};
	
	printf("Created!\n");
	//...
#endif	
	*/
	
	//
	//@todo: 
	// Devemos implementar uma rotina de inicialização dessas threads 
	// criadas através de chamadas ao sistema.
	//
	
	//printf("Initializing a thread...\n");
	//...
	
	//Testando bibliotecas.
	//printf("Testing libraries:\n");	
	
	//stdio.h
	//printf("Testing stdio:\n");
	//app_clear(0);  //Não fez nada.
    //...

	/*
	//stdlib.h
#ifdef SHELL_VERBOSE			
	printf("Testing stdlib:\n");
#endif
*/	
	
	
	
	/*
#ifdef SHELL_VERBOSE			
	//Obs: Sempre inicia com o mesmo número.
	int rand_value;
	rand_value = (int) rand();
	printf("RandValue1={%d}\n", rand_value);
	//rand_value = (int) rand();
	//printf("RandValue2={%d}\n", rand_value);
    //rand_value = (int) rand();
	//printf("RandValue3={%d}\n", rand_value);
	//...
#endif	
*/
	
	
	//stddef.h
	//printf("Testing stddef:\n");	
	
	//Testing COLUMNS
	
	//Testing ROWS
	
	
	//testando api.h
	//...
	
	
	//Funcionou...
	//sprintf( buffer,"Testando String dentro do buffer\n");
	//printf("%s",buffer);
	

	//
	// Get process info.
	//
	
	
	//
	// Get thread info.
	//
	
	
	//
	// Testing commands.
	//
	/*
#ifdef SHELL_VERBOSE		
	//Lib C.
	//libC. (stdlib.c)
	system("test");       
	system("ls");
	system("start");
	//system("xxfailxx");
	//...
#endif
	*/
	
	/*
#ifdef SHELL_VERBOSE			
	//API.
	apiSystem("test");    
    apiSystem("ls");
	apiSystem("start");
	//apiSystem("xxfailxx");
	//...
#endif
	*/
	
	//Ok funcionando ...
	//@todo: Testar outros comandos.
	//...
	
	
	//Testing message box.
	//MessageBox(3, "Shell message box","Testing message box...");
	
	//
	// @todo: Clear client area.
	//        System call redraw client area.
	
	
// Done.
	
done:

    return 0;
}





/*
 * shellTestLoadFile:
 *     Carrega um arquivo de texto no buffer e mostra na tela.
 */
void shellTestLoadFile (){
	
	FILE *f;
	
	int Ret;
	int i=0;
	int ch_test;
	
	int pos;
	
	//#importante:
	//precisa ser arquivo pequeno.
	
	
	f = fopen ("gramado.txt","rb");  	
	
	//pequeno
	//f = fopen ("init.txt","rb");  
	
	//grande
	//f = fopen ("init.txt","rb");  	
	
    if( f == NULL )
	{
		printf("fopen fail\n");
		return;
	}else{
		//printf("fopen ok\n");
	};	
	
	
	//#test 
	//testando com um arquivo com texto pequeno.
	//enviando para o buffer de words, 
	//obs: agora tem rotinas de refresh.
	
	while (1)
	{
		ch_test = (int) getc (f); 
		
		if( ch_test == EOF )
		{
			//printf("\n");
			//printf("EOF reached :)\n");
			goto done;
		
		} else {   			
		    
			terminalInsertNextChar ( (char) ch_test ); 
        };
    };


done:
    //
fail:
    return;
}


/*
 *************************************************************
 * shellTestThreads:
 *     Cria um thread e executa.
 *     #bugbug ...já funcionou uma vez, mas agora está com problemas.
 *     @todo: na hora de criar a thread precisamos passar o PID desse processo.
 */
 
void shellTestThreads (){
	
    //void *T;	
	
	// Obs: 
	// As threads criadas aqui são atribuídas ao processo PID=0.
	// @todo: 
	// No kernel, quando criar uma thread ela deve ser atribuída
    // ao processo que chamou a rotina de criação.	
	
	printf("shellTestThreads: Creating threads..\n");
	//apiCreateThread((unsigned long)&shellThread, 0x004FFFF0,"TestShellThread1");
	//apiCreateThread((unsigned long)&shellThread, 0x004FFFF0,"TestShellThread2");
	//apiCreateThread((unsigned long)&shellThread, 0x004FFFF0,"TestShellThread3");
	//apiCreateThread((unsigned long)&shellThread, 0x004FFFF0,"TestShellThread4");
	//...
	
	//
	// # Criar e executar #
	//
	
	// Tentando executar um thread.
	// *******************************
    // OBS: 
	// ISSO JÁ FUNCIONOU. 
	// ESTAMOS SUSPENDENDO PORQUE PRECISAMOS AUMENTAR O 
	// TAMANHO DO HEAP USADO PELO PROCESSO PARA 
	// ALOCAÇÃO DINÂMICA, ELE NÃO TÁ DANDO CONTA 
    // DE TODA A DEMANDA POR MEMÓRIA.		  
	//
	
	//>>Dessa vez pegaremos o retorno, 
	// que deve ser o ponteiro para a estrutura da thread.
	// Obs: Não podemos usar a estrutura porque ela está 
	// em ring0.
	//>>Chamaremos a system_call que executa essa thread 
	// que temos o ponteiro da estrutura.
    
	void *ThreadTest1;	
	
	//#bugbug: 
	// Não temos mais espaço no heap do preocesso 
	// para alocar memória pois gastamos o heap com 
	// a imagem bmp. (isso aconteceu kkk).

	unsigned long *threadstack1;
	
	
	
	
	// ++
	gde_enter_critical_section ();
	// #importante:
	// Como a torina de thread é bem pequena e o 
	// alocador tem pouquíssimo heap, vamos alocar o mínimo.
	// Isso é apenas um teste, vamos var se a thread funciona 
	// com um a pilha bem pequena. 2KB.
	threadstack1 = (unsigned long *) malloc(2*1024);
	
	//Ajuste para o início da pilha.
	//threadstack1 = ( threadstack1 + (2*1024) - 4 ); 
	
	//
	// # Criando a thread #
	//
//creating:

    printf("shellTestThreads: Tentando executar uma thread..\n");	

    ThreadTest1  = (void *) gde_create_thread ( (unsigned long) &shellThread, 
                                (unsigned long) (&threadstack1[0] + (2*1024) - 4), 
                                "ThreadTest1" );

    if ( (void *) ThreadTest1 == NULL )
    {	
	    printf("shellTestThreads: apiCreateThread fail \n");	
	    die("ThreadTest1\n");
    }


	// # executando #
	
	// #importante:
	// Lá no kernel, isso deve selecionar a thread para 
	// execussão colocando ela no estado standby.
	// Logo em seguida a rotinad e taskswitch efetua o spawn.
	
	gde_start_thread (ThreadTest1);
	
	gde_exit_critical_section();
	//--
	
	
	printf("shell: Tentando executar um thread [ok]..\n");
	
	//permitir que o shell continue.
}




/*
 ********************************************
 * shellScroll:
 *     @todo: Efetuar um scroll somente dentro 
 * da VGA virtual.
 * #importante: isso não deveria estar aqui,
 * deve ser uma rotina de automação, presente 
 * em alguma biblioteca, servidor ou kernel.
 */

void shellScroll (){
	
	//reajustando a área visível do buffer 
 

	//desliga o cursor
	//system_call ( 245, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);	

    testChangeVisibleArea ();	//desloca a área visível usando delta.
	terminalRefreshVisibleArea ();
	
	//#todo:posicionar cursor
	
	//reabilita o cursor
	//system_call ( 244, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);	
}








/*
 ***************************************************
 * shellTestMBR:
 *     Testar a leitura de um setor do disco.
 *     Testaremos o setor do mbr.
 */

void shellTestMBR (){

// suspenso.
/*
	unsigned char buffer[512];




	enterCriticalSection(); 
	
	//message 
	printf("shellTestMBR: Initializing MBR test ...\n");
	
	//read sector
	system_call ( SYSTEMCALL_READ_LBA, 
	              (unsigned long) &buffer[0],  //address 
				  (unsigned long) 0,           //lba
				  (unsigned long) 0);
				 
	
	exitCriticalSection();   
	
	//
	// exibe o conteúdo carregado.
	//
	
	//?? address #bugbug
	printf ("Signature: [ %x %x ] \n" , buffer[0x1FE], buffer[0x1FF] );
	
	
	//
	// @todo: Sondar cada elemento do MBR para 
	// confirmar a presença.
	//
	
//done:
	//printf("done");
	//refresh_screen(); //??deletar.
	//return;

*/
}



//show shell info
void shellShowInfo (){
	
	int PID, PPID;
	
    printf (" # shellShowInfo: #\n");
	
	
    PID = (int) system_call( SYSTEMCALL_GETPID, 0, 0, 0);
	if( PID == (-1)){
	    printf("ERROR getting PID\n");	
	}
  
    PPID = (int) system_call( SYSTEMCALL_GETPPID, 0, 0, 0);
	if( PPID == (-1)){
	    printf("ERROR getting PPID\n");	
	}
  
	printf ("Process info: PID={%d} PPID={%d} \n", PID, PPID );
	
	printf ("__wlMaxColumns={%d} \n", __wlMaxColumns );
	printf ("__wlMaxRows={%d} \n", __wlMaxRows );	
	//...
}


//metrics
void shellShowMetrics (){
	
    //reinicializa as metricas do sistema.
	//isso pega os valores e coloca nas variáveis globais.
	
	terminalInitSystemMetrics ();
	
	printf ("\n");  
	printf (" # shellShowMetrics: # \n");
	
	printf ("screenWidth={%d} screenHeight={%d}\n",smScreenWidth, smScreenHeight );
	printf ("cursorWidth={%d} cursorHeight={%d}\n", smCursorWidth, smCursorHeight );
	printf ("mousepointerWidth={%d} mousepointerHeight={%d}\n", 
	    smMousePointerWidth, smMousePointerHeight );
	printf ("charWidth={%d} charHeight={%d}\n", smCharWidth, smCharHeight );	
	//...
	
    printf ("Done\n");	
}


//show system info
void shellShowSystemInfo (){
	
	int ActiveWindowId;
	int WindowWithFocusId;
	
	printf (" # shellShowSystemInfo: #\n");
	
	//
	//Active
	ActiveWindowId = (int) gde_get_active_window ();
	
	//valor de erro
	if( ActiveWindowId == (-1)){
	    printf("ERROR getting Active window ID\n");	
	}	
	printf("ActiveWindowId={%d}\n", ActiveWindowId );


	//
	// Focus.
	WindowWithFocusId = (int) gde_get_focus();
	
	//valor de erro
	if( WindowWithFocusId == (-1)){
	    printf("ERROR getting Window With Focus ID\n");	
	}	
	
	printf ("WindowWithFocusId={%d}\n", WindowWithFocusId );	
}


//mostrar informações sobre janelas.
void terminalShowWindowInfo (){
	
    int wID;	
	//
	// #bugbug.
	// Testando a estrutura de janela.
	// A janela foi criada pelo kernel e copiamos o ponteiro 
	// da estrutura para um ponteiro em user mode.
	// Podemos ter erros de memória com essas operações.
		
	printf ("\n");	
	printf ("terminalShowWindowInfo:\n");
	
	//printf ("mainWindow={%x}", shell_info.main_window );
		
	//#bugbug 
	//temos um problema aqui.
	// provavelmente o erro é por acessar um endereço que está 
	// em kernel mode.
	//if( shell_info.main_window->left > 0 && shell_info.main_window->top > 0  )
	//{
	//    terminalSetCursor( (shell_info.main_window->left/8), (shell_info.main_window->top/8) );
	//}
		
		
	//obs: Isso é uma estrutura interna, não reflete 
    //a informação usada pelo kernel.	
	
	printf ("\n");		
	printf ("Window info: \n");	
    printf ("l={%d} t={%d} w={%d} h={%d}\n", 
	    wpWindowLeft, wpWindowTop, wsWindowWidth, wsWindowHeight );

													  
	//Obs: isso funcionou. setando o cursor.
	//if( terminal_rect.left > 0 && terminal_rect.top > 0 )
	//{
    //    terminalSetCursor( (terminal_rect.left/8), (terminal_rect.top/8) ); 
	//};
		
		
	wID = (int) system_call ( SYSTEMCALL_GETTERMINALWINDOW, 0, 0, 0 ); 
	
	printf ("\n current terminal: \n");
	printf ("Windows ID for current terminal = {%d} \n", wID );
	
	//...
}


//??
//void shellSetScreenColors( ... ){}

//??
//void *shellGetTerminalWindow(){}

//void shellSetTerminalRectangle(....){}

//void *shellOpenTerminal(.){}



				  
unsigned long 
shellSendMessage ( struct window_d *window, 
                   int msg, 
				   unsigned long long1, 
				   unsigned long long2 )
{
	return (unsigned long) noratermProcedure ( window, 
	                           msg, long1, long2 );
}


// Copia bytes.	
void 
shell_memcpy_bytes ( unsigned char *Dest, 
                     unsigned char *Source,
                     unsigned long Length )
{
    while (Length--)
        *Dest++ = *Source++;
}


/*
 * shell_write_to_screen:
 *     refresh de um retângulo ??    
 */
/* 
void shell_write_to_screen( struct shell_screen_d *screen, 
                            struct shell_rect_d *region )
{
    //@todo	
};
*/

 
//@todo: Criar rotina de saída do shell.
void shellExit (int code){
	
	//@todo ...
	exit (code);
}
 

/*
 *****************************************
 * shellUpdateWorkingDiretoryString:
 *     Atualiza a string do diretório de trabalho.
 * Essa é a string que será mostrada antes do prompt.
 * 'pwd'> 
 * ?? isso deve sser todo o pathname do pwd ?? 
 * ex: root:/volume0>
 */

void shellUpdateWorkingDiretoryString ( char *string ){
	
	if ( pwd_initialized == 0 )
	{
		goto fail;
	}else{
		
        if( (void *) string == NULL )
	    {
		    goto fail;
	    }else{
	    
	        // ## separador ##
		    //strcat( current_workingdiretory_string, 
			//    SHELL_PATHNAME_SEPARATOR );		
		
	        // ## separador ##		
		    strcat ( current_workingdiretory_string, string );	

		    strcat( current_workingdiretory_string, 
			    SHELL_PATHNAME_SEPARATOR );				
		
            //Atualizar no gerenciamento feito pelo kernel.
	        system_call( 175, (unsigned long) string,
		        (unsigned long) string, (unsigned long) string );		
		};
	};
	//...
fail:	
done:
    return;
}


/*
 *****************************************
 * shellInitializeWorkingDiretoryString:
 *     Atualiza a string do diretório de trabalho.
 * Essa é a string que será mostrada antes do prompt.
 * 'pwd'> 
 * ?? isso deve sser todo o pathname do pwd ?? 
 * ex: root:/volume0>
 */

void shellInitializeWorkingDiretoryString (){
	
	//get info
	
	//test: get current volume id.
	current_volume_id = (int) system_call ( 171, 0, 0, 0 );
	
	//global usada para string do nome do volume.
	current_volume_string = (char *) SHELL_VOLUME1_STRING;
	
	
    //  ## volume list ##
	
	//root:
    //primeiro colocamos a string que indica 
	//a lista de volumes.
    sprintf( current_workingdiretory_string, SHELL_VOLUMELIST_STRING ); 
	
	
	// ## separador ##

	//root:/
	strcat( current_workingdiretory_string, SHELL_PATHNAME_SEPARATOR );
	
	
	//  ## volume root dir ##
	
	//root:/volumex
	strcat( current_workingdiretory_string, current_volume_string );

	
	// ## separador ##

	//root:/volumex/
	strcat( current_workingdiretory_string, SHELL_PATHNAME_SEPARATOR );
	
    pwd_initialized = 1;
}



// atualiza a variável global para id de diretório atual de trabalho.
void shellUpdateCurrentDirectoryID ( int id ){
	
	g_current_workingdirectory_id = (id);
}


//lista informações sobre os processos.
void shellTaskList (){
	
	// opções:
	// +podemos pedir para o kernel listar as informações.
	// +podemos solicitar as informações uma a uma.
	// Obs: A segunda opção é a mais trabalhosa, mas 
	// da oportunidade para testarmos as chamadas ao kernel e 
	// explorarmos as possibilidades que cada informação traz 
	// individualmente.
	
	
	// testando posicionamento de strings
	
	unsigned long X, Y;
	int PID;

	//Pega o PID do processo atual.
    PID = (int) system_call ( SYSTEMCALL_GETPID, 0, 0, 0 );
	
    //X = apiGetCursorX();
	Y = gde_get_cursor_y ();
	
	Y++;
	X=0;
	terminalSetCursor (X,Y);	
    printf("PID ");
	X=8;
	terminalSetCursor (X,Y);
	printf("XXXXXXXX");
	
	Y++;
	X=0;
	terminalSetCursor (X,Y);
    printf("====");
	X=8;
	terminalSetCursor (X,Y);
	printf("========");

	Y++;
	X=0;
	terminalSetCursor (X,Y);	
    printf("%d",PID);
	X=8;
	terminalSetCursor (X,Y);
	printf("...\n");
	
    //...		
}



/*
 ***************************************************
 * shell_fntos:
 *     Rotina interna de support.
 * isso deve ir para bibliotecas depois.
 * não tem protótipo ainda.
 * Credits: Luiz Felipe
 */

void shell_fntos (char *name){
	
    int  i, ns = 0;
    char ext[4];
    //const char ext[4];
	
    //transforma em maiúscula
	while ( *name && *name != '.' )
	{
        if(*name >= 'a' && *name <= 'z')
            *name -= 0x20;

        name++;
        ns++;
    }

    // aqui name[0] é o ponto.
	// então constroi a extensão.
	for ( i=0; i < 3 && name[i+1]; i++ )
	{
        if(name[i+1] >= 'a' && name[i+1] <= 'z')
            name[i+1] -= 0x20;

        ext[i] = name[i+1];
    };

    while (ns < 8)
	{
        *name++ = ' ';
        ns++;
    };

    for ( i=0; i < 3; i++ )
        *name++ = ext[i];

    *name = '\0';
}


/*
 *******************************************************
 * shell_gramado_core_init_execve:   ## terminal
 *
 *     #importante:
 *         Essa é uma maneira alternativa de executar um processo. Pois ainda
 *     não implementamos as formas tradicionais.
 *
 *     >> Executa arquivos do tipo "$test.bin"
 *
 *     #obs: 
 *     E caso o arquivo não tenha extensão ?
 *     Devemos presumir que ele seja .bin ? 
 *     Ou não tenha ponto nem extensão. ? 
 *     Certamente o carregamento irá falhar.
 * 
 *     #todo: 
 *     Caso seja .bin, mas começe com "/", devemos suprimir a barra. 
 *
 */	

int 
shell_gramado_core_init_execve ( const char *arg1,     // nome
                                 const char *arg2,     // arg (endereço da linha de comando)
                                 const char *arg3 )    // env
{
	//erro.

	int Status = 1;

	//unsigned long arg_address = (unsigned long) &argv[0];

// suprimindo dot-slash
	// The dot is the current directory and the 
	// slash is a path delimiter.
	//if( filename[0] == '.' && filename[1] == '/' )
	//{ 
	//    filename++;
	//    filename++; 
	//    goto translate;	
	//};


	//suprimindo a barra.
	//if( *arg1 == '/' || 
	//    *arg1 == '\\' )
	//{ 
	//    arg1++; 
	//};


translate:

	//
	// ## BUG BUG
	//
	// Talvez nesse momento, ao transformar a string ele 
	// corrompa o espaço reservado para o argumento seguinte.
	// vamos fazer um teste no quan a rotina não precise 
	// acrescentar zeros.
	//
	
	//
	// correto é isso mesmo,
	// para não corromper o espaço dos argumentos no vetor,
	// teremos que transformar somente lá no kernel, pouco antes 
	// de carregarmos o arquivo.
	//
	
	//Isso faz uma conversão de 'test.bin' em 'TEST    BIN'.
	//Ok funcionou.
	//shell_fntos( (char *) arg1);
	
	//const char* isso não foi testado.
	//shell_fntos(filename);


	// #importante:
	// Isso deve chamar gramado_core_init_execve() na api.


//isso chamará uma rotina especial de execve, somente 
//usada no ambiente gramado core. 

execve:


// #importante
// #todo: esse comentário será revisto.
// Nesse momento o shell pode atuar com outro procedimento de janela 
// que ficaria responsável por conduzir essas mensagens até o processo 
// filho, que até mesmo ser um aplicativo que não use  recursos gráficos.
// Esse processo filho a janela do shell como output e o shell como input.
// Ex: um aplicativo chamado pelo shell pode chamar a função getch() para 
// obter input ... como o shell tem a janela com o foco de entrada, então 
// o shell precisa enviar a mensagem para esse aplicativo. Como ?
// Uma opção seria fazer uma chamada ao kernel enviando essa mensagem 
// para o lugar padrão onde os aplicativos pegam mensagens do tipo caractere.
// Ou seja, getch() solicita um caractere ao kernel, e quem enviou esse caractere 
// ao kernel foi o shell no qual o aplicativo está rodando.
// Se esse aplicativo pertence a um terminal específico, então o caractere 
// pode ser enviado para a estrutura desse terminal específico. Pode uasr 
// descritores de terminal.
// teminalFeed(teminal_id,ch) poderia enviar o caratere para um terminal específico,
// de onde o aplicativo pegará o caractere.


    // O retorno significa que o aplicativo foi colocado
	// para rodar e em breve receberá tempo de processamento.
	// '0' significa que funcionou e '1' que falhou.	
	
	// Obs: 
	// Se retornar o número do processo então podemos esperar por ele 
	// chamando wait (ret);
	
	// #importante
	// Chama a rotina de execve alternativa, que executa um processo
	// com os recursos do processo init.

    Status = (int) system_call ( 167, 
                       (unsigned long) arg1,      // Nome
                       (unsigned long) arg2,      // arg (endereço da linha de comando)
                       (unsigned long) arg3 );    // env

    if ( Status == 0 )
	{
		// Não houve erro. O aplicativo irá executar.
		// Nesse momento devemos usar um novo procedimento de janela.
		// Que vai enviar as mensagens de caractere para um terminal 
		// específico, para que aplicativos que user aquele terminal 
		// possam pegar essas mensgens de caractere.


#ifdef SHELL_VERBOSE
        printf ("shell: Process initialized.\n");
#endif

		//
		// ## teste ##
		//
		// saindo do shell.
		//

		// getpid...
		// waitforpid(?);

		//die("Exiting shell.bin\n");
		
		//Saindo sem erro.
		//exit(0);

		// Saída elegante, retornando para o crt0.
		
        ShellFlag = SHELLFLAG_EXIT;

		//ShellFlag = SHELLFLAG_FEEDTERMINAL;		

        goto done;

    }else{

		// Se estamos aqui é porque ouve erro 
		// ainda não sabemos o tipo de erro. 
		// Status indica o tipo de erro.
		// Se falhou significa que o aplicativo não vai executar,
		// então não mais o que fazer.

		//#importante: Error message.
		
        printf ("shell: Process was NOT initialized.\n");

		ShellFlag = SHELLFLAG_COMMANDLINE;
		
        goto fail;
    };


	// fail.
	// Retornaremos. 
	// Quem chamou essa rotina que tome a decisão 
	// se entra em wait ou não.

	
fail:

    //#importante: Error message.
    //status = 1.
	
    printf ("shell_gramado_core_init_execve: \n fail retornando ao interpretador\n");
	
done:

    return (int) Status;
}


/*
 * feedterminalDialog:
 *     Para alimentar um terminal com caracteres.
 */		

int 
feedterminalDialog ( struct window_d *window, 
                     int msg, 
				     unsigned long long1, 
				     unsigned long long2 )
{
	//int q;
	
	switch (msg)
	{
	
	    //para alimentar o terminal
		case MSG_KEYDOWN:
			//para todas as teclas.
			//feed terminal system call.
			system_call( 135,  // número do serviço 
			             0,    // número do terminal
						 long1,    // o caractere
						 long1 );  // o caractere

			break;
			
		//para sair do diálogo.	
		case MSG_SYSKEYDOWN:
		    switch (long1)
			{

                //
                // ?? #importante:
				// ?? Quando parar de alimentar o terminal ??
                // ## [CONTROL + C]  ou [ESC]  ## 
				// >>> F12 POR ENQUANTO PARA TESTES.
				//
				//help
				case VK_F1:
				    //APISetFocus(i1Window);
					//APIredraw_window(i1Window);
					//MessageBox ( 1, "feedterminalDialog","F1: HELP");
					printf ("VK_F1\n");
					break;
				
                //full screen
                //colocar em full screen somente a área de cliente. 				
		        case VK_F2:
				    //APISetFocus(i2Window);
					//APIredraw_window(i2Window);				
				    //MessageBox ( 1, "feedterminalDialog","F2: ");
					//ShellFlag = SHELLFLAG_COMMANDLINE;
					printf ("VK_F2\n");
					break;
					
				case VK_F3:
				    printf ("F3: Saindo do aplicativo e voltando ao shell...\n");
				    ShellFlag = SHELLFLAG_COMMANDLINE;
				    break;
					
					
			};
		    break;
			
		default:  
		    break;
	
    };
	
    return 0;
}


void die (char *str){
	
	printf ("die: %s \n", str);
	fflush(stdout);
	
	//@todo
	fprintf (stderr,"%s\n",str);
	//fflush(stderr);
	
	exit (1);
}


/*
//isso foi para stdlib.c
void *xmalloc( int size){
	
    register int value = (int) malloc(size);
    if(value == 0)
        die ("xmalloc fail.\n");
//done:  
    return (void *) value;
};
*/


char *concat ( char *s1, char *s2, char *s3 ){
	
    int len1 = (int) strlen(s1);
    int len2 = (int) strlen(s2);
    int len3 = (int) strlen(s3);
  
    char *result = (char *) xmalloc ( len1 +len2 +len3 +1 );

    strcpy( result, s1);
    strcpy( result +len1, s2 );
    strcpy( result +len1 +len2, s3 );
  
    *( result +len1 +len2 +len3 ) = 0;

//done:  
	
  return (void *) result;
}


/* error */
void error ( char *msg, char *arg1, char *arg2 ){
	
    fprintf (stderr, "shell: ");
    fprintf (stderr,"%s %s %s", msg, arg1, arg2);
    fprintf (stderr, "\n");
}


void fatal ( char *msg, char *arg1, char *arg2 ){
	
    error (msg, arg1, arg2);
    
	//delete_temp_files ();
    exit (1);
}


char *save_string ( char *s, int len ){
	
    register char *result = (char *) xmalloc (len + 1);

    bcopy (s, result, len);
  
    result[len] = 0;
  
    return result;
}


/*
void 
reader_loop()
{
	while( !EOF_Reached )
	{
		//...
		
	};
	
};
*/

 

/*
char **
array_of_strings()
{
	char **a;
	
	a[0] = "test0";
	a[1] = "test1";
	a[2] = NULL;
	
	return (a);
};
*/


/*
//retorna o pool de strings contendo os nomes dos arquivos
//em um diretório que está no buffer.
char **
get_dir_files( char *buffer )
{
    char **poll;	
	
	// ...
	
	
    return (poll);	
}
*/

/*
//coloca no pool de strings passado por argumento 
//as strings que correspondem  aos nomes 
// dos arquivos encontrados no diretório 
//indicado pelo buffer.
int set_dir_files( char **poll, char *buffer )
{
	
	//...
	
    return (0);
};
*/




//testando a rotina de salvar um arquivo.
//estamos usando a API.
int shell_save_file (){
	
	//
	// #importante:
	// Não podemos chamar a API sem que todos os argumentos estejam corretos.
	//
	
	// #obs:
	// Vamos impor o limite de 4 setores por enquanto. 
	// 512*4 = 2048  (4 setores) 2KB
	// Se a quantidade de bytes for '0'. ???
	
	int Ret;
	
	char file_1[] = "t5: Arquivo \n escrito \n em \n user mode. \n";
	
	char file_1_name[] = "FILE1UM TXT";
	//char file_1_name[] = "TESTSAVETXT";
	
	printf("shell_save_file: Salvando um arquivo ...\n");
	
	unsigned long number_of_sectors = 0;
    size_t len = 0;
	
	
	//
	// Lenght in bytes.
	//
	
	len = (size_t) strlen (file_1);

	if (len <= 0)
	{
	    printf ("shell_save_file:  Fail. Empty file.\n");
        return (int) 1;		
	}
	
	if (len > 2048)
	{
	    printf ("shell_save_file:  Limit Fail. The  file is too long.\n");
        return (int) 1;		
	}
	
    //
    // Number os sectors.
    //
	
	number_of_sectors = (unsigned long) ( len / 512 );
	
	if ( len > 0 && len < 512 ){
	    number_of_sectors = 1; 
    }		
	
	if ( number_of_sectors == 0 )
	{
	    printf ("shell_save_file:  Limit Fail. (0) sectors so save.\n");
        return (int) 1;				
	}
	
	//limite de teste.
	//Se tivermos que salvar mais que 4 setores.
	if ( number_of_sectors > 4 )
	{
	    printf ("shell_save_file:  Limit Fail. (%d) sectors so save.\n",
		    number_of_sectors );
        return (int) 1;				
	}
	
	/*
	 ## test
    Ret = (int) apiSaveFile ( file_1_name,        //name 
                              number_of_sectors,  //number of sectors.
                              len,                //size in bytes			
                              stdin->_base,      //address
                              0x20 );             //flag
	*/
	
	
    Ret = (int) gde_save_file ( file_1_name,  //name 
                              number_of_sectors,            //number of sectors.
                              len,            //size in bytes			
                              file_1,       //address
                              0x20 );       //flag		

	//if (Ret == 0)
	
	printf("shell_save_file: done\n");	
	

    return (int) Ret;
}


//salvando uma string.
int save_string2 ( char string[], char file_name[] ){
	
	// #importante:
	// Não podemos chamar a API sem que todos os argumentos estejam corretos.
	
	// #obs:
	// Vamos impor o limite de 4 setores por enquanto. 
	// 512*4 = 2048  (4 setores) 2KB
	// Se a quantidade de bytes for '0'. ???
	
	int Ret;
	
	//char file_1[] = "t5: Arquivo \n escrito \n em \n user mode. \n";
	
	//char file_1_name[] = "FILE1UM TXT";
	//char file_1_name[] = "TESTSAVETXT";
	
	printf ("save_string2: Salvando um arquivo ...\n");
	
	unsigned long number_of_sectors = 0;
    size_t len = 0;
	
	
	//
	// Lenght in bytes.
	//
	
	len = (size_t) strlen (string);

	if (len <= 0)
	{
	    printf ("save_string2:  Fail. Empty file.\n");
        return (int) 1;		
	}
	
	if (len > 2048)
	{
	    printf ("save_string2:  Limit Fail. The  file is too long.\n");
        return (int) 1;		
	}
	
    //
    // Number os sectors.
    //
	
	number_of_sectors = (unsigned long) ( len / 512 );
	
	if ( len > 0 && len < 512 ){
	    number_of_sectors = 1; 
    }		
	
	if ( number_of_sectors == 0 )
	{
	    printf ("save_string2:  Limit Fail. (0) sectors so save.\n");
        return (int) 1;				
	}
	
	//limite de teste.
	//Se tivermos que salvar mais que 4 setores.
	if ( number_of_sectors > 4 )
	{
	    printf ("save_string2:  Limit Fail. (%d) sectors so save.\n",
		    number_of_sectors );
        return (int) 1;				
	}
	
	/*
	 ## test
    Ret = (int) apiSaveFile ( file_1_name,        //name 
                              number_of_sectors,  //number of sectors.
                              len,                //size in bytes			
                              stdin->_base,      //address
                              0x20 );             //flag
	*/
	
	
    Ret = (int) gde_save_file ( file_name,  //name 
                              number_of_sectors,            //number of sectors.
                              len,            //size in bytes			
                              string,       //address
                              0x20 );       //flag		
				
	//if (Ret == 0)
	
	printf("save_string2: done\n");	
	
	return (int) Ret;
}



/* 
 * Give version information about this shell.  
 */

void show_shell_version (){

    printf ("%s, version %s.%s \n", 
        shell_name, dist_version, build_version );
}



// #todo
// Isso é um teste.
/*
void response ();
void response (){

    char *p = RESPONSE;

    while (*p){
        terminal_write_char ( (int) *p );
        p++;
    }
}
*/



/*
 *********************************************************
 *********************************************************
 * terminal_write_char: 
 * 
 * # Importante:
 * 
 * Escreve um char no backbuffer e exibe na tela usando o cursor 
 * gerenciado pelo sistema.
 * 
 * #todo: Essa rotina pode ir para ./terminal ?
 */

void terminal_write_char (int c){

	//
	//  Escape sequence.
	//
	
	// #todo
	// Talvez esse seja o momento de tratarmos
	// as sequencias.
	// >>> Talvez seja melhor depois de preenchermos o buffer.
	
	
	/*
	switch (c)
	{
		// #bugbug: \033 e \x1b são a mesma coisa; 
		//case '\033':
		case '\x1b':	
		    //#debug
		    printf ("[ESCAPE FOUND]");
		    break;
		
		//case ..
		    //break;
		
		//...
	};
	*/

    // #test scroll.
    // tentando fazer scroll da área de cliente.
    // #bugbug: esse if não funcionou,
    // o scroll do kernel foi acionado.
    
    //atualizar a área visível
    //rodando up ou down.
    // updateVisibleArea (0); //down
    //updateVisibleArea (1); //up    
    
	if ( textCurrentRow >= __wlMaxRows )
	{
		updateVisibleArea (0); //down
		     
        //MessageBox ( 3, "terminal_write_char:","*Scroll" )
		terminal_scroll_display ();
	}


    //coloca no buffer de linhas e colunas.
	terminalInsertNextChar ( (char) c );  

	// #bugbug
	// imprime na tela usando api.  
	//(implementando ainda). 
	//isso funcionou.
	//terminalRefreshCurrentChar2 ();
	
	//#obs: Não usar mais esse.
	// imprime na tela usando libc. (funcionou)
	terminalRefreshCurrentChar ();
}





/*
 ********************************************************
 * main: 
 *     Main function.
 *
 * @todo:
 *    +Checar argumentos.
 *    +Criar a janela do TERMINAL. (Ok).
 *    +Enviar mensagem de texto para ele. (Ok).
 *    +Configurar procedimento de janela.
 *    +Definir a janela que é área do cliente.
 *    +Carregar um arquivo na área de cliente.
 *    +Testar outros recursos do Kernel.
 *    +Testar as chamadas para pegar informções sobre o processo.
 *    +...
 *
 *  
 *  ## O SHELL É UM APLICATIVO DO TIPO JANELA, DEVE TER UM MAIN 
 *     DO TIPO JANELA ##
 *
 * Obs: Esses argumentos podem ser um padrão.
 */
 
int main ( int argc, char *argv[] ){
	
	//#importante: Isso será definido somente uma vez.
	__wlMaxColumns = DEFAULT_MAX_COLUMNS;
	__wlMaxRows    = DEFAULT_MAX_ROWS;
	
	// Número máximo de colunas e linhas.
    g_columns = __wlMaxColumns;    // 80;
    g_rows    = __wlMaxRows;       // 25;

    FILE *default_input = stdin;
    char *local_pending_command = (char *) NULL;	

	//char **internal;
	char *filename;
	register int i;

	
	int _quit = 0;
	
	
	// Obs: Esse não é um programa que roda em modo terminal,
	// ele na verdade cria um terminal dentro de uma janela filha.
	// isso pode servir para esse programa interpretar linguagem 
	// basic por exemplo.
	// os programas em modo terminal não criarão janelas e rodarão nas 
	// janelas de terminal cridas para eles pelo kernel.
	
	
	//#debug
	//deixe o kernel usar essa janela para teste.
	//Obs: Não criaremos a janela principal desse programa 
	//para evitarmos erros com printf.
 
	
	
	/*
	 * Uma boa ordem para os passos dessa rotina nos aplicativos  
	 * é: Step1=WindowClass, Step2=Window e Step3=Message.
	 */
	
	//@todo: Criar esse tipo de classe.
	//       Provavelmente deve coincidir com a estrutura presente
    //nas rotinas de gerenciamento de janela que estão em kernel mode.	
	//struct window_class_d *wc; 
	
	
	// A janela principal do aplicativo.
	struct window_d *hWindow;    

	
	int Status = 0;
	//char *s;    //String	
	
	
	//
	// Debug
	//
	
	// Serial debug.
	gde_debug_print ("noraterm: Initializing ...\n");
	
	
	//printf ("SHELL.BIN is alive");
	//while (1){ asm ("pause"); }
	
	
	
	
    /* Wait forever if we are debugging a login shell. */
    //while(debugging_login_shell);	

	
    //if(shell_initialized)
    //{
        //reinitialize();
    //};
	
	
    //shell_environment = env;
    //shell_name = argv[0];
	
	//
	// ## ARGS ##
	//
	
	//
	// ## Command Switch ##
	//
	
	//Ok isso funcionou.
	//Argumentos passados com sucesso do crt0 para o main.
	
	//printf("argc={%d}\n",argc);	
	//if ( argc >= 2 )
	//{
	//    printf("arg[0]={%s}\n",argv[0]);
	//    printf("arg[1]={%s}\n",argv[1]);
	//}
	
	//
	// Filtra a quantidade de argumentos.
	//
	
	//goto noArgs; 
	
	//Não usar verbose nessa fase de tratar os argumentos
	//pois a janela ainda não foi inicializada.
	//argv[0] = Tipo de shell: interativo ou não
	//argv[1] = Tipo de uso: login ... outros ?? 
	
	
	// Se não há argumentos.
	if (argc < 1)
	{
		//printf("No args !\n");
		//#Test.
        //fprintf( stderr,"Starting Shell with no arguments...\n");	 	
		
		die ("SHELL.BIN: No args \n");
		
		goto noArgs; 
		
	}else{
		
		
		// #importante
		// Precisamos de 9 argumentos.
		// Ver os argumentos no crt0.c
		
		// #importante
		// Não podemos comparar com um ponteiro nulo, se não é PF.
		
		if (argc < 2)
		{
		    printf ("main: argc=%d we need 2 or more \n", argc );
			return 1;
		}
		
		// 0
		// Nome passado viar argumento.
		shell_name = (char *) argv[0];
        printf ("Shell Name = { %s }\n", shell_name );		
		
		// 1
		// -f
        // Se o shell foi iniciado com um arquivo de script para ser executado.
		// Então o arg[1] cpontém o nome do arquivo.
        if ( strncmp ( (char *) argv[1], "-f", 2 ) == 0 )
        {
			script_shell = 1;
			//interactive = 0;
		    //goto dosh2;
		};			
		
		
		// 2
		// Script name.
		//script_name = (char *) argv[2];
        //printf ("Script Name = { %s }\n", script_name );			
		
		
		// 3
		// --interactive
	    if ( strncmp ( (char *) argv[3], "--interactive", 13 ) == 0 )
		{	
			interactive = 1;
			
            printf ("Initializing an interactive shell ...\n");
            //printf ("arg[0]={%s}\n",argv[0]);			
        };
		
		// 4
		// --login
	    if ( strncmp ( (char *) argv[4], "--login", 7 ) == 0 )
		{	
			login_shell = 1;
			
			//printf("Initializing login ...\n");
            //printf("arg[1]={%s}\n",argv[1]);    
        };			

		
        // 5
		// --headless
		// Aqui o shell não criará janelas, apenas inicializará o gws.
		
		if ( strncmp ( (char *) argv[5], "--headless", 10 ) == 0 )
		{	
			headless = 1;	
		};
		
        // 6
		// --taskbar
		
		if ( strncmp ( (char *) argv[6], "--taskbar", 9 ) == 0 )
		{	
			taskbar = 1;	
		};
		
		if ( strncmp ( (char *) argv[6], "--notaskbar", 11 ) == 0 )
		{	
			taskbar = 0;	
		};		

		// 7
		// Shell funcionando no modo servidor.
		if ( strncmp ( (char *) argv[7], "--gws", 5 ) == 0 )
		{	
			//gws_shell = 1;	
		};

		// 8
		// Shell funcionando no modo desktop.
		
		if ( strncmp ( (char *) argv[8], "--desktop", 9 ) == 0 )
		{	
			desktop = 1;	
		};
		
		if ( strncmp ( (char *) argv[8], "--nodesktop", 11 ) == 0 )
		{	
			desktop = 0;	
		};		
		
		
		//se version _quit = 1;
		

        //...		
	};
	
	//Nothing.
	
	
	if (_quit)
		exit (0);
	
	
	
	// #todo
	// Nesse momento usa-se as funções de termio.h para configurar o terminal.
	// Ou outra lib/api apropriada.
	
	
	// #debug
	//printf ("#debug: Breakpoint");
	//while (1){}
	
	
noArgs:		
	
	
	//...
	
	//@todo:
	//Podemos começar pegando o id do processo atual e 
	//melhorando a prioridade.
	
	
	// get current dir
	//pegamos o diretório atual.
	
	//get user dir
	//pegamos o diretório do usuário /root/user/(name)
	
	//set current dir
	//setamos para que o diretório do usuário seja o diretório atual.
	
	
	// Isso configura alguns padrões do aplicativo.
	// Os argumentos tratados abaixo podem modificar esses padrões
	// Ex: Um argumento de entrada pode solicitar a troca de cor de fonte.
	
	terminalTerminal (); 	
	
	
    //
    // Main window.
    //
	
	
    mainwindow_used = 1;



    // ++
    // See: termui.c
    gde_enter_critical_section ();    
    hWindow = (struct window_d *) terminalCreateMainWindow (1);
    // Setup a global pointer for main window.
    main_window = hWindow;
    shell_info.main_window = ( struct window_d * ) hWindow;	
    gde_exit_critical_section ();
    //--



	// #test 
	// Criando um timer.
	// janela, 100 ms, tipo 2= intermitente.
	//system_call ( 222, (unsigned long) hWindow, 100, 2);
	
	
	
	// #importante:
	// +pegamos o retângulo referente à area de cliente da janela registrada. 
	// +atualizamos as variáveis que precisam dessa informação. 
	// reposicionamos o cursor.
	// reabilitamos a piscagem de cursor.
	
 
	
	//===============================
	
    //
	// ## Janela para texto ##
	//
	

	// #obs
	// terminalTerminal() inicializou todas as globais.



     // background.
     __bgleft = 1 +20;
     __bgtop  = 1 +36;    
     __bgwidth  = (__wlMaxColumns*8) +60;  
     __bgheight = (__wlMaxRows*8)    +200; 
 
     // bar.
     __barleft = 2;
     __bartop = 2;
     __barwidth = wsWindowWidth -40 -4;
     __barheight = 34; 


    //
    // Client window.
    //

    //#todo
    // Essa estrutura não deve guardar um posicionamento relativo
    // Pois ela será usada para redraw.

    // relativo: 
    // Usado para desenhar agora em relação
    // a sua janela mãe.

    unsigned long __terminal_left  = 2;
    unsigned long __terminal_top   = __barheight +2; 
    unsigned long __terminal_width  = __bgwidth  -4; 
    unsigned long __terminal_height = __bgheight -__barheight -4;  


    //aboluto: usado para redraw
    terminal_rect.left  = wpWindowLeft + __terminal_left;
    terminal_rect.top   = wpWindowTop + __terminal_top; 
    terminal_rect.width  = __terminal_width; 
    terminal_rect.height = __terminal_height;  
    
    // #importante
    // Reajustando o limite de caracteres por linha.
    // Pois isso depende do tamanho da área de cliente.
    
    


    //
    // Bg Window.
    //

    struct window_d *client_bg;
    
    //++
    client_bg = (void *) gde_create_window ( WT_SIMPLE, 1, 1, 
                            "NORATERM-CLIENT-bg",
                            __bgleft, __bgtop, __bgwidth, __bgheight,
                            hWindow, 0, 0xF5DEB3, 0xF5DEB3 ); 

    if ( (void *) client_bg == NULL )
    {
		printf ("client_bg window fail \n");
		die( ":( \n");
    }else{
		
        gde_register_window  (client_bg);
        gde_show_window (client_bg );
        client_background_window = client_bg;
    };
    //--


	//
	// Client window.
	//
	
	// #Atenção
	// Estamos criando um área de cliente. 
	// É uma janela filha que se sobrepoe ao bg da janela mãe.
	

	//JANELA CRIADA NA ÁREA DE CLIENTE DA JANELA PRINCIPAL.
    struct window_d *hWindow2;  
	//++
    //apiBeginPaint ();
    hWindow2 = (void *) gde_create_window ( WT_SIMPLE, 1, 1, 
                            "NORATERM-CLIENT-window",
                            __terminal_left, 
                            __terminal_top, 
                            __terminal_width, 
                            __terminal_height,
                            client_bg, 0, 
                            COLOR_TERMINAL2, COLOR_TERMINAL2 );
 
    if ( (void *) hWindow2 == NULL )
    {
        die ("NORATERM: hWindow2 \n");
    }else{

        gde_register_window (hWindow2);
        gde_set_focus (hWindow2);
        gde_show_window (hWindow2);
        
        //
        // Saving ...
        //
        
        // Salvamos para uso nesse documento.
        client_window = hWindow2;


        //
        // Terminal window.
        //

        // Salva ponteiro da janela do terminal.
        // Essa é a janela da área de cliente.
        // Ela que será repintada para apagar o texto.
        // Poderemos usar em outros documentos. 
        
        shell_info.terminal_window = ( struct window_d * ) hWindow2;



	    //Terminal window.
	    // #importante
	    // Definindo a janela como sendo uma janela de terminal.
	    // Isso faz com que as digitações tenham acesso ao 
	    // procedimento de janela de terminal 
	    // para essa janela e não apenas ao procedimento de janela do sistema.
	    // # provavelmente isso marca os limites para a 
	    // impressão de caractere em modo terminal 
        
        system_call ( SYSTEMCALL_SETTERMINALWINDOW, 
            (unsigned long) hWindow2, 
            (unsigned long) hWindow2, 
            (unsigned long) hWindow2 );
    };
	//apiEndPaint ();
	//--


    //
    // Create the wt_d struct as an element of window struct
    //
    
    int vt_ret = -1;
    int father_pid = getpid();
    
    //IN: window, father's pid
    vt_ret = (int) gramado_system_call ( 270, 
                       (unsigned long) hWindow2, 
                       (unsigned long) father_pid, 
                       0 );

    if (vt_ret < 0)
    {
        printf ("noraterm: We couldn't create the terminal\n");
        exit(1);  
    }





    //
    // Vamos fazer botões na barra de ferramentas.. 
    // que será o início do bg da área de cliente.
    //


	//++
	gde_enter_critical_section ();  
	client_bar_Window = (void *) gde_create_window ( WT_SIMPLE, 1, 1, 
	                                 "client-bar",     
                                    __barleft, __bartop, 
                                    __barwidth, __barheight, 
                                    client_bg, 0, 0x404040, 0x404040 );
	if ( (void *) client_bar_Window == NULL)
	{	
		printf(".. fail \n");
		gde_show_backbuffer();
		gde_exit_critical_section ();  
		while(1){}
	}
	gde_register_window (client_bar_Window);
	gde_show_window (client_bar_Window);
	gde_exit_critical_section ();  
	//--


    //
    // ============ Bar buttons =========
    //
    
	//++
    gde_enter_critical_section (); 
	bar_button_1 = (void *) gde_create_window ( WT_BUTTON, 1, 1, " 1 ",  
                                     1, 1, 
                                     50, 32,    
                                     client_bar_Window, 0, 
                                     xCOLOR_GRAY3, xCOLOR_GRAY3 );

    if ( (void *) bar_button_1 == NULL )
    {
		printf ("Couldn't create PID button\n");
		return 1;
    }else{
        gde_register_window (bar_button_1);
        gde_show_window (bar_button_1);
        gde_show_backbuffer ();
    };
    gde_exit_critical_section (); 
	//--


    
	//++
    gde_enter_critical_section (); 
	bar_button_2 = (void *) gde_create_window ( WT_BUTTON, 1, 1, " 2 ", 
                                     50 +1, 1,
                                     100, 32,   
                                     client_bar_Window, 0, 
                                     xCOLOR_GRAY3, xCOLOR_GRAY3 );
	
	if ( (void *) bar_button_2 == NULL )
	{
		printf ("Couldn't create State button\n");
		return 1;
	}else{

        gde_register_window (bar_button_2);
        gde_show_window (bar_button_2);
        gde_show_backbuffer ();
	};
    gde_exit_critical_section (); 
	//--


	//++
    gde_enter_critical_section (); 
	bar_button_3 = (void *) gde_create_window ( WT_BUTTON, 1, 1, " 3 ", 
                                     50 +1 +100 +1, 1,
                                     200, 32,   
                                     client_bar_Window, 0, 
                                     xCOLOR_GRAY3, xCOLOR_GRAY3 );
	
	if ( (void *) bar_button_3 == NULL )
	{
		printf ("Couldn't create Priority button\n");
		return 1;
	}else{

        gde_register_window (bar_button_3);
        gde_show_window (bar_button_3);
        gde_show_backbuffer ();
	};
    gde_exit_critical_section (); 
	//--




	//
	// ===========================================================
	//
	
	// #obs
	// Aqui, tentaremos inicializar o aplicativo indicado pelo argumento
	// ele deve ser um aplicativo que rode em terminal.
	// Caso não tenha um aplicativo indicado no argumento então
	// chamaremos o shell padrão.
	// Caso o shell padrão falhe então entraremos no shell interno 
	// que pertence ao terminal noraterm.
	// O procedimento de janela é o 'noratermProcedure' e serve para
	// o shell interno e para o terminal. Esse shell interno pode
	// ser usado para gerenciar o terminal;
	
	// _init_app 
	// 1 = tente inicializar o programa que vai rodar no terminal
	// 0 = Inicialine o shell interno para gerenciamento do terminal.
	
	/*
	if ( _init_app == 1 )
	{
		printf ("noraterm: Tentando executar um aplicativo usando fork\n");
		
		int pidFORK = (int) fork ();

		// Erro.
		if ( pidFORK < 0 )
		{
		    printf ("noraterm: fork falhou\n");
            //goto do_run_internal_shell;
            interactive = 0; //não temos mais um shell interativo
		    __embedded_shell = 0; //sem shell embutido.
		    goto no_internal_shell;
		}
		
		// Pai.
		if ( pidFORK > 0 )
		{
			printf ("noraterm: Noraterm is alive!\n");
		    printf ("noraterm: estamos no PAI. O filho eh pid=%d \n", pidFORK);
			interactive = 0; //não temos mais um shell interativo
			__embedded_shell = 0; //sem shell embutido.
			//goto do_run_internal_shell;
		    goto no_internal_shell;
		}
		
		// Filho.
		if ( pidFORK == 0 )
		{
			// #todo
			// Aqui tentaremos rodar um aplicativo passado por argumento em main,
			// caso não for possível, então chamaremos gdeshell
			
			//#importante
			//A intenção pe que gdeshell rode na área de cliente do noraterm
			
		    printf ("noraterm: estamos no FILHO\n");
			printf ("PID=%d", getpid());
			
			//#bugbug: 
			//O gdeshell é fullscreen e não cabe dentro da 
			//área de cliente da janela do terminal.
			execve ("gdeshell.bin", NULL, NULL );
			
			printf ("execve falhou. *hang\n");
			while(1){}
			//goto do_run_internal_shell;
		}	
	};
	*/
	
	
	
	
	//
	// Internal shell
	//
	
do_run_internal_shell:
 	


	// ===========================================================
	
	// Set cursor.
	// Enable cursor.	
	
	terminalSetCursor ( ( terminal_rect.left / 8 ), 
	    ( terminal_rect.top / 8 ) );
	
	system_call ( 244, 
	    (unsigned long) 0, 
	    (unsigned long) 0, 
	    (unsigned long) 0 );

	//===========================
	

no_internal_shell:
	
	//
	// ======== ## terminal init ## ========
	//	
	
	// #importante
	// Para inicializarmos o shell precisamos de uma janela válida
	// onde as mensagens irão aparecer.
	
	
	// Init Shell:
	//     Inicializa variáveis, buffers e estruturas. Atualiza a tela.
    //#BUGBUG
    //Estamos passando um ponteiro que é uma variável local.	
	
	
	//#todo
	//devemos chamar as rotina de configuração do terminal ainda antes
	//de chegarmos na parte do shell interno ou de chamarmos o aplicativo
	//que vai rodar no terminal
	
	
	//++
	gde_enter_critical_section();
	Status = (int) terminalInit (hWindow2); 
	
	if ( Status != 0 )
	{
		die ("noraterm: terminalInit fail");
	}else{
			
	    //#isso é coisa de shell.
	    // ## prompt string support ##
	    shellInitializeWorkingDiretoryString ();	
	
	    //#suspenso
	    //supendemos isso porque fopen está falhando na máquina real.
	
	    //if (interactive == 1)
	        //loginCheckPassword ();

	    //#isso é coisa de shell.
	    if ( interactive == 1 )
	        shellPrompt ();
	};
	gde_exit_critical_section();     		
	//--
	
	
	
	// #importante:
	// Agora é a hora de pegar mensagens de input de teclado.
	// Mas se o shell não for interativo, então não pegaremos 
	// mensagens de input de teclado.
	
	// #obs
	// Noraterm é um terminal, mas estamos lidando com
	// rotinas de seu shell interno.

	
	//#debug
	if ( interactive != 1 )
	{
        printf ("noraterm: Internal shell is not interactive\n");	
		goto skip_input;
	};

	
	//
	// Podemos tentar criar um processo.
	//


    //
    // ==== Child process ====
    //
    
    // #importante
    // >>> clona e executa o filho dado o nome do filho.
    //printf ("noraterm: Executing default child process launcher ...\n");
    
    printf ("noraterm: no child for now!\n");
    
    //isso funciona
    //system_call ( 900, (unsigned long) "hello3.bin", 0, 0 );

    //#testar isso: funcionou
    //gde_clone_and_execute ("hello3.bin");



	//printf ("noraterm: Executing default child process hello3 ...\n");
    //system_call ( 900, (unsigned long) "hello3.bin", 0, 0 );
    //system_call ( 900, (unsigned long) "launcher.bin", 0, 0 );
    
    //printf ("noraterm: noraterm is still alive!\n");
    //printf ("noraterm: No internal shell\n"); 
    //__embedded_shell = 0; //sem shell embutido.

    //
	// Get message.
	//

	/*
	 * @todo: 
	 *     Entrar num loop, solicitando ao kernel possiveis mensagens
	 * deixadas no buffer de mensagens do PCB do processo shell.
	 * Obs: O kernel coloca na fila de mensagens do processo, mensagens
	 * provenientes não apenas do teclado, mas também de outras fontes.
	 * Então dessa forma, pode-se enviar mensagens de um processo para outro.
	 * *IMPORTANTE:Cabe a cada processo pegar as mensagens deixadas no buffer de mensagens 
	 * em seu PCB, atravez de uma chamada ao kernel.
	 */
    
   
	//
	// Por fim: Testar cursor e terminar.
	//

	//@todo: 0,0 não está na área de cliente.
	
 
	
	//
	// **** Mensagens  ****
	//
	
	//printf("Tentando pegar mensagem enviada para o procedimento de janela.");
	//refresh_screen();
	
	//isso é um teste pegar um valor por vez não é a melhor opção.
	
	//struct window_d *msg_Window;
	int msg_Message;
	void *msg_Long1;
	void *msg_Long2;
	
	//struct shell_message_d *msg;
	

	// Get Message: 
	// Systemcall get message
	// Enviamos um ponteiro de estrutura de janela para que o Kernel possa 
	// pegar a mensagem que esta dentro da estrutura. Essa estrtura fica 
	// protegida no Kernel.
		
	// #bugbug: ??
	// Na verdade essa rotina está pegando a mensagem na janela 
	// com o foco de entrada. Esse argumento foi passado mas não foi usado.
		
	//unsigned long message_buffer[32];	
	
	//vamos testar se a mensagem esta no range padrao de servidores
	//9000 ~  9999
	//int msgtest;
	
	
	//
	// ======== ## main loop ## ========
	//
		
Mainloop:
	
	process_input ();
	
	//
	// Entramos aqui se running for igual a 0.
	//
	
	switch (ShellFlag)
	{
	    // Sai do shell.
		case SHELLFLAG_EXIT:
		    goto end;
			break;

		//@todo:
        //opções ...
		
		// Sai do shell.	
        default:
            goto end;
			break;		
	};

	
	// Pulamos a parte que pega mensgens de input de teclado 
	// porque esse shell não está configurado como interativo.
	
//	
// # RunScript #	
//

skip_input:	

    shellExecuteThisScript ( argv[3] );

	// Exit process.
	
end:

    // Desabilitando o cursor de texto.
    // Quando outro aplicativo precisar ele clica em uma janela, 
	// ela ganha o foco e habilita o cursor piscante.	
	
    system_call ( 245, 
        (unsigned long) 0, (unsigned long) 0, (unsigned long) 0 );

#ifdef SHELL_VERBOSE		
    printf ("noraterm: exiting code '0' ...\n");
#endif 
	
	return 0;
}


//
// End.
//





