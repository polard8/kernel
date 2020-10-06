/*
 * File: noraterm.h
 *
 * Descrição:
 * 
 *
 * History:
 *     2016 - Created by Fred Nora.
 *     2017 - procedure and command stuff.
 *     2018 - Add some bash 1.05 stuff. 
 */
 
 
 
 

// main window.
// # usado para teste 
// divisível por 4 é mais lento.

#define WINDOW_LEFT      0      
#define WINDOW_TOP       0      
#define WINDOW_WIDTH     800    
#define WINDOW_HEIGHT    600-24   




// rtl
#include <rtl/gramado.h>
#include <ctype.h>
#include <types.h>
#include <stddef.h>
#include <stdarg.h>   
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>
#include <fcntl.h>

// libcore
#include <api.h>


//pty includes.
//#include "pty/pty.h"

//base includes.
#include "base/compiler.h"
#include "base/globals.h"
#include "base/variables.h"
#include "base/general.h"
#include "base/flags.h"
#include "base/alias.h"
#include "base/ndir.h"

#include "base/version.h"

#include "base/renderer.h"
#include "base/builtins.h"
#include "base/login.h"
#include "base/tests.h"
#include "base/desktop.h"
#include "base/terminal.h"
#include "base/input.h"
//#include "base/output.h"







//#define SHELL_VERBOSE 1


//#define MIN(x,y) ((x < y) ? x : y)


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
 
 









//scroll dentro da screen_buffer. (VGA emulada)
void shellScroll(void);
//...


//
// Buffer support.
//



//...


//
// Reset prompt.
//

void shellPrompt(void);


//cmd
//Funções chamadas pelos comandos.

void shellShowExperienceMenu(void);
void shellShowTestsMenu(void);
void shellShowInfo(void);
void shellShowMetrics(void);
void shellShowSystemInfo(void);


void shellTree(void);
void shellThread(void);

void shellTestLoadFile(void);
void shellTestThreads(void);
void shellTestMBR(void);


//int test_operators();

void terminalShowWindowInfo (void);



unsigned long 
shellSendMessage ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );
//...


// Wait for commands.
// Isso não é usado, temos um while.
void shellWaitCmd (void);             
 
 // Compare comands.
unsigned long shellCompare (struct window_d *window);   
 


//
// Initialization. 
//

 //Init.
int terminalInit ( struct window_d *window );               


//Constructor.
void terminalTerminal (void);                


// Finalizing ... 
// ??exit, die... 
 
 
//show ascii table
//void shellASCII(); 


// copia bytes	
void 
shell_memcpy_bytes ( 
    unsigned char *Dest, 
    unsigned char *Source,
    unsigned long Length );
 
 
void shellUpdateCurrentDirectoryID( int id ); 
void shellUpdateWorkingDiretoryString( char *string );

void shellInitializeWorkingDiretoryString (void);

//lista informações sobre os processos.
void shellTaskList(void);


//
// shell.c
//

void ShowPID (void);
void ShowPPID (void);
void ShowUID (void);
void ShowGID (void);
void ShowUserSessionID(void);
void ShowWindowStationID(void);  //room
void ShowDesktopID(void);

void shellShowProcessHeapPointer(void);
void shellShowKernelHeapPointer(void);
void shellShowDiskInfo(void);
void shellShowVolumeInfo(void);
void shellShowMemoryInfo(void);
void shellShowPCIInfo(void);
void shellShowKernelInfo(void);



/*
 * gramado core specials execve SUPPORT.
 * Executa um programa exclusivamente dentro 
 * do ambiente Gramado Core no lugar do processo init.bin.
 */

int 
shell_gramado_core_init_execve( 
    const char *arg1, 
    const char *arg2, 
    const char *arg3 );



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
int shellInitPathname (void);
//inicializaremos o supporte a filename
int shellInitFilename (void);


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

int shellCheckPassword (void);

void shellPipeTest (void);

//não é o soquete da libc.
void shellSocketTest (void);


