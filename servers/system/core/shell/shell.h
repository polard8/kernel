/*
 * File: shell.h
 *
 * Descrição:
 *     Header principal do Shell.
 *     SHELL.BIN (32bit User Mode) 
 *
 * Obs: 
 * Para atender os comandos do usuário o Shell chamará vários programas, assim 
 * como terá rotinas internas que atendem os comandos. Para isso, esse 
 * diretório deve ter várias pastas, uma para cada um dos comandos principais, 
 * como shutdown. Cda pasta é um programa que o Shell vai chamar.
 *
 * O kernel que gerencia a estrutura de processo deve criar o fluxo padrão ?
 * 
 *
 * History:
 *     2016 - Created by Fred Nora.
 *     2017 - procedure and command stuff.
 *     2018 - Add some bash 1.05 stuff. 
 */
 

// main window.
//# usado para teste 
//divisível por 4 é mais lento.

#define WINDOW_LEFT      0      
#define WINDOW_TOP       0      

#define WINDOW_WIDTH     800    
#define WINDOW_HEIGHT    600-24   




//Setup current compiler 
#include "compiler.h"


//lib C
#include <types.h>
#include <stddef.h>
#include <stdarg.h>   
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>


//#tedt: open()
#include <fcntl.h>
  

#include "globals.h"

 

#include "builtins.h"

#include <api.h>
#include <gws.h>


#include "desktop.h"

//# bash 1.05 stuff #
#include "variables.h"
#include "general.h"
#include "flags.h"
#include "alias.h"
#include "ndir.h"
#include "version.h"
//...


#include "login.h"

#include <stubs/gramado.h>


#include "tests.h"


//#define SHELL_VERBOSE 1


//
// botões
// 




//janela da taskbar
struct window_d *taskbar_window;
struct window_d *taskbar_button1;

//struct window_d *taskbarWindow;  //task bar.
//struct window_d *menu_button;

 
//...

//grid de aplicativos.
struct window_d *app1_button;
struct window_d *app2_button;
struct window_d *app3_button;
struct window_d *app4_button;

struct window_d *editboxWindow;  //edit box.

 //outros.
struct window_d *reboot_button;
struct window_d *close_button;
 
 

//
// Structures.
// 




//??
typedef struct shell_hook_d shell_hook_t; 
struct shell_hook_d
{
	int dummy;
	//struct window_d *window;
	//struct rect_d *rect;
}; 
shell_hook_t *ShellHook; 




//metrics
typedef struct shell_metrics_d shell_metrics_t;
struct shell_metrics_d
{
    int fontWidth;
    int fontHeight;
	int lineMax;
	int colMax; //rowMax
	//... 
};
shell_metrics_t *ShellMetrics;
//...
 






//
// Estrutura principal.
// Informações sobre o shell.
//

typedef struct shell_info_d shell_info_t;
struct shell_info_d
{
	struct window_d *main_window;
	struct window_d *terminal_window;
	
	//stream support.
    int stream_status;  //inpout ou output.
	
	//#BUGBUG duplicando estrutura. ??
	//struct _iobuf *stdin;
	//struct _iobuf *stdout;
	//struct _iobuf *stderr;
	
	//O retângulo da área de cliente.
	struct rect_d *rect;   
	//struct terminal_rect_info_d *r;
	
	struct shell_hook_d *hook;
	struct shell_metrics_d *metrics;
	//...
	
}; 
//sem ponteiro.
struct shell_info_d shell_info;


 
/*
 #bugbug isso dá problema. falta de página.
 
typedef struct shell_message_d shell_message_t;  
struct shell_message_d
{
	struct window_d *window;
	int msg;
	unsigned long long1;
	unsigned long long2;
};
*/


//
// @todo:
// Cada atitude do terminal merece uma estrutura.
// faremos as estruturas daqui para baixo.
//
 
 
//screen info 
typedef struct terminal_screen_info_d terminal_screen_info_t; 
struct terminal_screen_info_d
{
	unsigned long width;
	unsigned long height;
}; 
 

 
//#importante. 
//rect info
//retângulo da área de cliente onde aparecerão os caracteres.
typedef struct terminal_rect_info_d terminal_rect_info_t; 
struct terminal_rect_info_d
{
	unsigned long top;
	unsigned long left;
	unsigned long width;
	unsigned long height;
	//...
};
struct terminal_rect_info_d terminal_rect; 


//cursor info
typedef struct terminal_cursor_info_d terminal_cursor_info_t; 
struct terminal_cursor_info_d
{
	unsigned long width;
	unsigned long height;
	//...
}; 


//char info
typedef struct terminal_char_info_d terminal_char_info_t; 
struct terminal_char_info_d
{
	unsigned long width;
	unsigned long height;
}; 


typedef struct COMMANDHISTORY_D COMMANDHISTORY_T;
struct COMMANDHISTORY_D
{
    int NumberOfCommands;
	int MaximumNumberOfCommands;
	
};
COMMANDHISTORY_T *CommandHistory;  




// alias support
typedef struct alias_d alias_t;
struct alias_d 
{
	int used;
	int magic;
	
	int name_lenght;
    char *name;
	
	int command_lenght;
    char *command;
}; 
 

typedef struct COMMAND_D COMMAND_T;
struct COMMAND_D
{
	int used;
	int magic;
	
	int command_lenght;
	char *command;
	
	struct alias_d *alias; 
};
COMMAND_T *CurrentCommand;  
//...



typedef struct line_d line_t;
struct line_d
{
	int id;     //identificação da linha.
	
	int used;
	int magic;  //Validade e característica da estrutura.
	
	int Start;
	int End;
	
	//Deslocamentos em relação ao Start.
	int LeftOffset;    //Onde começa o texto dentro da linha.   
	int RightOffset;   //Onde termina o texto dentro da linha.
	
	// Continua
	// ...
	
	int SizeInChars;  // Quantos chars tem na linha.
	int SizeInBytes;  // Quantos bytes tem na linha. (char + atrr)	
	
    struct line_d *next;	
};




//Conterá ponteiros para estruturas de linha.
unsigned long lineList[LINE_COUNT_MAX];




//
// Estrutura de suporte ao screen buffer.
//

typedef struct screen_buffer_d screen_buffer_t;
struct screen_buffer_d
{
	int id;
	
	int used;
	int magic;
	
	char *name;
	char *description;
	
		
    //
    // Current line support.
    //
	
	int current_line_id;              //id.
	struct line_d *current_line;   //struct 
	//...
	
    //
    // lines.
    //	
	
	struct line_d *first_line;
	struct line_d *last_line;
	//...
	
	
	//Continua ...
	
	//Número total de linhas no buffer.
	int total_lines;
	
	struct screen_buffer_d *next;
};

//Conterá ponteiros para estruturas de linha.
unsigned long screenbufferList[8];

 

/* 
//command type 
typedef enum {
	ctNull,
	//...
}command_type_t;
 

//command struct
typedef struct command_d command_t;
struct command_d
{
	// Typo de comando.
    command_type_t type;
	
	//@todo: Criar essas estruturas.
    //struct start_com_d     *Start;
    //struct finish_com_d    *Finish;
    //struct super_com_d     *Super;
    //struct rules_com_d     *Rules;
    //struct condition_d     *Condition;
    //struct open_com_d      *Open;
    //struct close_com_d     *Close;
    //struct run_com_d       *Run;
    //struct stop_com_d      *Stop;
    //struct guarantee_com_d *Guarantee;	
    //struct mix_com_d       *Mix;
    //struct here_com_d      *Here;
    //struct there_com_d     *There;	
	
	//...
};
command_t *current_command;
*/
/*
//command struct
typedef struct connection_d connection_t;
struct connection_d
{
    struct command_d *first;
    struct command_d *second;
    
	//qual é o tipo de conector entre os comandos
	// | ??? 
	int connectorType;  	
};
connection_t *current_connection;
*/






//
// ## Text support #@#
//

struct shell_line
{
    char CHARS[80];
    char ATTRIBUTES[80];	
	
	//início e fim da string dentro da linha.
	//o resto é espaço.
	int left;
	int right;
	
	//posição do cursor dentro da linha.
	int pos;
};

//PROVISÓRIO
//O TEXTO TEM 32 LINHAS NO MÁXIMO.
//ESSA É A PARTE DO TEXTO QUE PODERÁ SER MANIPULADA,
//O RESTO DO TEXTO DEVERÁ FICAR ESPERANDO NO BUFFER.
//#IMPORTANTE: 25 DESSAS 32 LINHAS SERÃO VISÍVEIS.
struct shell_line LINES[32]; 


//
// Buffer support.
// 






//===
 

/* 
 # generic list #

 All structs which contain a `next' field should have that field
as the first field in the struct.  This means that functions
can be written to handle the general case for linked lists. 
*/
   

typedef struct g_list_d g_list;
typedef struct g_list_d GENERIC_LIST; 
typedef struct g_list_d g_list_t;
struct g_list_d 
{
    struct g_list_d *next;
};


/* Instructions describing what kind of thing to do for a redirection. */
typedef enum r_instruction_t r_instruction;
typedef enum {
    r_output_direction, 
	r_input_direction, 
	r_inputa_direction,
	r_appending_to, 
	r_reading_until, 
	r_duplicating,
	r_deblank_reading_until, 
	r_close_this, 
	r_err_and_out 
}r_instruction_t;


/* Command Types: */
typedef enum command_type_t command_type;
typedef enum { 
    cm_for, 
	cm_case, 
	cm_while, 
	cm_if, 
	cm_simple,
	cm_connection, 
	cm_function_def, 
	cm_until, 
	cm_group 
}command_type_t;



/* A structure which represents a word. */


typedef struct word_desc_d word_desc; 
typedef struct word_desc_d WORD_DESC;
typedef struct word_desc_d word_desc_t;
struct word_desc_d
{
  char *word;			/* Zero terminated string. */
  int dollar_present;		/* Non-zero means dollar sign present. */
  int quoted;			/* Non-zero means single, double, or back quote
				   or backslash is present. */
  int assignment;		/* Non-zero means that this word contains an assignment. */
};

/* A linked list of words. */
typedef struct word_list_d word_list; 
typedef struct word_list_d WORD_LIST;
typedef struct word_list_d word_list_t;
struct word_list_d
{
    struct word_list_d *next;
    struct word_desc_d *word;
}; 






/* ******************************** */
/*								    */
/*       Shell Command Structs      */
/*								    */
/* ******************************** */


/* 
 What a redirection descriptor looks like.  If FLAGS is IS_DESCRIPTOR,
 then we use REDIRECTEE.DEST, else we use the file specified. 
 */
 
typedef struct redirect_d redirect;
typedef struct redirect_d REDIRECT;
typedef struct redirect_d redirect_t; 
struct redirect_d
{
    struct redirect_d *next;	/* Next element, or NULL. */
    int redirector;		/* Descriptor to be redirected. */
    int flags;			/* Flag value for `open'. */
    r_instruction_t  instruction; /* What to do with the information. */
    
	union {
        int dest;			/* Place to redirect REDIRECTOR to, or ... */
        WORD_DESC *filename;	/* filename to redirect to. */
    }redirectee;
    
	char *here_doc_eof;		/* The word that appeared in <<foo. */
};


/* 
 An element used in parsing.  
 A single word or a single redirection.
 This is an ephemeral construct. 
 */
typedef struct element_d element;
typedef struct element_d ELEMENT;
typedef struct element_d element_t;
struct element_d 
{
    WORD_DESC *word;
    REDIRECT *redirect;
};


/* 
 What a command looks like. 
 */
typedef struct command_d command; 
typedef struct command_d COMMAND;
typedef struct command_d command_t; 
struct command_d
{
    command_type_t type;	/* FOR CASE WHILE IF CONNECTION or SIMPLE. */
    int subshell;			/* Non-zero means execute in a subshell. */
    REDIRECT *redirects;		/* Special redirects for FOR CASE, etc. */
    
	union {
        struct for_com *For;
        struct case_com *Case;
        struct while_com *While;
        struct if_com *If;
        struct connection *Connection;
        struct simple_com *Simple;
        struct function_def *Function_def;
        struct group_com *Group;
    }value;
};


/* 
 Structure used to represent the CONNECTION type. 
 */
 
typedef struct connection_d connection;
typedef struct connection_d CONNECTION;
typedef struct connection_d connection_t;
struct connection_d
{
    COMMAND *first;		/* Pointer to the first command. */
    COMMAND *second;		/* Pointer to the second command. */
    int connector;		/* What separates this command from others. */
};


/* Structures used to represent the CASE command. */

/* Pattern/action structure for CASE_COM. */

typedef struct pattern_list_d pattern_list; 
typedef struct pattern_list_d PATTERN_LIST;
typedef struct pattern_list_d pattern_list_t; 
struct pattern_list_d
{
    struct pattern_list_d *next;	/* The next clause to try in case this one failed. */
    WORD_LIST *patterns;		/* Linked list of patterns to test, one after each other. */
    COMMAND *action;		/* Thing to execute if one of the patterns match. */
};


/* The CASE command. */
typedef struct case_com_d case_com;
typedef struct case_com_d CASE_COM; 
typedef struct case_com_d case_com_t;
struct case_com_d
{
    WORD_DESC *word;		/* the thing to test. */
    PATTERN_LIST *clauses;	/* the clauses to test against, or NULL. */
};


/* FOR command. */
typedef struct for_com_d for_com;
typedef struct for_com_d FOR_COM; 
typedef struct for_com_d for_com_t; 
struct for_com_d
{
    WORD_DESC *name;		/* The variable name to get mapped over. */
    WORD_LIST *map_list;		/* The things to map over.  This is never NULL. */
    COMMAND *action;		/* The action to execute.
				   During execution, NAME is bound to successive
				   members of MAP_LIST. */
};


/* IF command. */
typedef struct if_com_d if_com; 
typedef struct if_com_d IF_COM; 
typedef struct if_com_d if_com_t;
struct if_com_d 
{
    COMMAND *test;		/* Thing to test. */
    COMMAND *true_case;		/* What to do if the test returned non-zero. */
    COMMAND *false_case;		/* What to do if the test returned zero. */
};


/* WHILE command. */
typedef struct while_com_d while_com;
typedef struct while_com_d WHILE_COM;
typedef struct while_com_d while_com_t;
struct while_com_d 
{
    COMMAND *test;		/* Thing to test. */
    COMMAND *action;		/* Thing to do while test is non-zero. */
};


/* The "simple" command.  Just a collection of words and redirects. */
typedef struct simple_com_d simple_com; 
typedef struct simple_com_d SIMPLE_COM;
typedef struct simple_com_d simple_com_t;  
struct simple_com_d
{
    WORD_LIST *words;		/* The program name, the arguments, variable assignments, etc. */
    REDIRECT *redirects;		/* Redirections to perform. */
};


/* The "function_def" command.  This isn't really a command, but it is
   represented as such for now.  If the function def appears within 
   `(' `)' the parser tries to set the SUBSHELL bit of the command.  That
   means that FUNCTION_DEF has to be run through the executor.  Maybe this
   command should be defined in a subshell.  Who knows or cares. */
typedef struct function_def_d function_def; 
typedef struct function_def_d FUNCTION_DEF; 
typedef struct function_def_d function_def_t; 
struct function_def_d 
{
    WORD_DESC *name;
    COMMAND *command;
};


/* A command that is `grouped' allows pipes to take effect over
   the entire command structure. */
typedef struct group_com_d group_com; 
typedef struct group_com_d GROUP_COM;
typedef struct group_com_d group_com_t; 
struct group_com_d
{
    COMMAND *command;
};



//...




//===










//
//  ** SCREEN BUFFER ***
//

//#bugbug: ALGUMAS AQUI NÃO SÃO MAIS USDAS. DELETAR !!!

//O buffer
char screen_buffer[SCREEN_BUFFER_SIZE]; 

//
// Macros.
// 
 
//#define DeclareStructHandle(name) struct nameJABUTICABA__ { int unused; }; typedef struct nameJABUTICABA__ *name 
//#define DeclareHandle(name) typedef void* name 
  



//
// ===============================================
//


int main ( int argc, char *argv[] );
 
 
//
// Screen support.
//

void shellClearScreen();
void shellRefreshScreen(); //copia o conteúdo do buffer para a tela. (dentro da janela)
void shellRefreshLine ( int line_number );
void shellRefreshChar ( int line_number, int col_number );
void shellRefreshCurrentChar(); //refresh do char que está na posição usada pelo input.



//scroll dentro da screen_buffer. (VGA emulada)
void shellScroll();
//...


//
// Buffer support.
//

void shellClearBuffer();
void shellShowScreenBuffer();
//...


//
// Typing support.
//

void shellInsertCR();
void shellInsertLF();
void shellInsertNullTerminator();
void shellInsertNextChar(char c);

void shellInsertCharXY(unsigned long x, unsigned long y, char c);
char 
shellGetCharXY ( unsigned long x, 
                 unsigned long y );
 
static void lf(void);
static void ri(void);
static void cr(void);
static void del(void);
void move_to( unsigned long x, unsigned long y);
//...


//
// Cursor support.
//

void shellSetCursor(unsigned long x, unsigned long y);
static void save_cur(void);
static void restore_cur(void);


//
// Reset prompt.
//

void shellPrompt();


//cmd
//Funções chamadas pelos comandos.

void shellShowExperienceMenu();
void shellShowTestsMenu();

void shellTree();
void shellThread();
void shellTestLoadFile();
void shellTestThreads();
void shellTestMBR();


//int test_operators();

void shellShowWindowInfo();
void shellShowInfo();
void shellShowMetrics();
void shellShowSystemInfo();

unsigned long 
shellSendMessage( struct window_d *window, 
                  int msg, 
				  unsigned long long1, 
				  unsigned long long2 );
//...

// Wait for commands.
//Isso não é usado, temos um while.
void shellWaitCmd();             
 
 // Compare comands.
unsigned long shellCompare (struct window_d *window);   
 
// Initialization. 
int shellInit( struct window_d *window );                //Init.
void shellShell();               //Constructor. 
 
// Finalizing ... 
// ??exit, die... 
 
 
//show ascii table
//void shellASCII(); 


// copia bytes	
void shell_memcpy_bytes ( unsigned char *Dest, 
                          unsigned char *Source,
                          unsigned long Length );

 
 
void shellUpdateCurrentDirectoryID( int id ); 
void shellUpdateWorkingDiretoryString( char *string );

void shellInitializeWorkingDiretoryString ();

//lista informações sobre os processos.
void shellTaskList();

void shellShowPID();
void shellShowPPID();



void shellShowUID();
void shellShowGID();


void shellShowUserSessionID();
void shellShowWindowStationID();
void shellShowDesktopID();

void shellShowProcessHeapPointer();
void shellShowKernelHeapPointer();

void shellShowDiskInfo();
void shellShowVolumeInfo();

void shellShowMemoryInfo();
void shellShowPCIInfo();
void shellShowKernelInfo();


/*
 * gramado core specials execve SUPPORT.
 * Executa um programa exclusivamente dentro 
 * do ambiente Gramado Core no lugar do processo init.bin.
 */
int shell_gramado_core_init_execve( const char *arg1, 
                                    const char *arg2, 
                                    const char *arg3 );

//
// shelui.c
//

void shellCreateEditBox();


struct window_d *shellCreateMainWindow( int status );
//struct window_d *shellCreatemainWindow ();




int shellDisplayBMP( char *file_name );



int shellDisplayBMPEx (char *file_name, int size );
void shellTestDisplayBMP();


void bmpDisplayBMP ( void* address, 
                     unsigned long x, 
					 unsigned long y, 
					 int width, 
					 int height );
					
				

//um comando no shell aponta o script para executar.
int shellExecuteThisScript ( char* script_name );
					
/*
 **************************************
 * absolute_pathname:
 * Retorna 1 nos seguintes casos:
 *
 * >/
 * >.
 * >./
 * >..
 * >../
 *
 * Credits: bash 1.05
 */
int absolute_pathname ( char *string );


//inicializaremos o supporte a pathname
int shellInitPathname ();


//inicializaremos o supporte a filename
int shellInitFilename ();

void shellExit (int code);	

/* 
 Remove the last N directories from PATH.  
 Do not leave a blank path.
 PATH must contain enough space for MAXPATHLEN characters. 
 Credits: bash 1.05
 */
void shell_pathname_backup ( char *path, int n ); 

//isso vai ser usado pelo echo.
void shell_print_tokenList ( char *token_list[], char *separator );	


/* Check if it's a .bin file */
int is_bin ( char *cmd );

/* Check if it's a .sh1 file */
int is_sh1 ( char *cmd );

int shellCheckPassword();


//testando botão.
int shellTestButtons ();


//tests
void testCreateWindow ();


int shellCreateTaskBar();


// Procedimento de janela da topbar.							  
void *shellTopbarProcedure ( struct window_d *window, 
                             int msg, 
			                 unsigned long long1, 
					         unsigned long long2 );



