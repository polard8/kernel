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
 */
 
//
// File suppport.
//
 
//#define FILENAME_LENGTH (8+3) 
//...




//
// SCREEN SUPPORT
//

#define DEFAULT_WINDOW_X 0
#define DEFAULT_WINDOW_Y 0

//Obs: aumentar essas constantes aumenta o tamanho da janela.
#define DEFAULT_MAX_COLUMNS 80
#define DEFAULT_MAX_ROWS    50 //25 
  

//linux 
//#define SCREEN_START 0xb8000
//#define SCREEN_END   0xc0000
#define LINES 25
#define COLUMNS 80
#define NPAR 16
   

//
// BUFFER SUPPORT
//

//
// Screen Buffer: 
// Igual a tela do vga, com caracteres e atributos.
// @todo: O buffer deve ser maior, com várias vistas para rolagem.
// mas apenas uma parte do buffer será mostrada na tela por vez.
//

#define DEFAULT_BUFFER_MAX_COLUMNS 80
#define DEFAULT_BUFFER_MAX_ROWS    25
#define SCREEN_BUFFER_SIZE ( ((DEFAULT_BUFFER_MAX_COLUMNS*DEFAULT_BUFFER_MAX_ROWS)*2)+1)


 

 
//
// Messages support.
//


#define CMD_ABOUT 1000
//#define CMD_ABOUT 1001
//#define CMD_ABOUT 1002
//#define CMD_ABOUT 1003
//...


#define TAB_SIZE 8

//
// Strings
//

#define SHELL_PATHNAME_SEPARATOR "\\"
#define SHELL_PATHNAME_TERMINATOR "\0"

#define SHELL_STRING_TERMINATOR "\0" 


//@todo: 
//a versão do sistema operacional deve-se obter através de uma chamada ao sistema. 
#define OS_VERSION     "0.1"  
#define SHELL_VERSION  "0.1"

//prompt
#define SHELL_PROMPT   ">"
#define SHELL_PROMPT2  "$"
#define SHELL_PROMPT3  "%"
//#define SHELL_PROMPT4  "shell: " 
//... 




#define CalculateRowScanLine(WindowY,CharHeight) \
    ( WindowY * CharHeight )


#define CalculateColumnScanLine(WindowX,CharWidth) \
    ( WindowX * CharWidth )
	
	
	
 
//usado para salvar um comando atual  
//char tmp_command[32];      
 
//
// Banners.
//
 
 
// help 
static const char help_banner[] =
    "\n Commands: \n \n"
	" ?         - This help\n"
	" cd        - Change current directory\n"
	" cls       - Clear screen\n"
	" copy      - Copy file or directory\n"
	" date      - Date\n"
	" del       - Delete file or directory\n"
	" dir       - List\n"
	" echo      - This ---\n"
	" exit      - Exit shell\n"
	" help      - This help\n"
    " mov       - Move file or diretory\n"
    " new       - New file or directory\n"
    " reboot    - Reboot system\n"
    " rename    - Rename file or directory\n"
	" shutdown  - Shutdown your computer locally or remotely\n"
	" time      - Time\n"
	" version   - Shell version\n"
	"\n";

	
// tree
static const char tree_banner[] =
"\n"
"\n"	
"     \\o/    \n"
"      d      \n"
"     ccc     \n"
"    bbbbb    \n"
"   aaaaaaa   \n"
"  ggggggggg  \n" 
" fffffffffff \n"
"eeeeeeeeeeeee\n" 
"     ||      \n"  
"     ||      \n"
"     ||      \n"
"    ~~~~     \n"
"\n";	
//... 

// usage	
static const char usage[] =
    "Usage: shell [arguments...]\n"
    "       shell -help             Display this help message and exit.\n"
    "       shell -version          Output version information and exit.\n";
	//...
	
	
//
// Files (strings).
//	
	
static const char bmp1_file_name[] = "BMP1    BMP";
static const char bmp2_file_name[] = "BMP2    BMP";
static const char bmp3_file_name[] = "BMP3    BMP";
static const char bmp4_file_name[] = "BMP4    BMP";	
static const char init_file_name[] = "INIT    TXT";	
//... 
 	
//static const char file_bmp1[] = "BMP1.BMP";
//static const char file_bmp2[] = "BMP2.BMP";
//static const char file_bmp3[] = "BMP3.BMP";
//static const char file_bmp4[] = "BMP4.BMP";	
//static const char file_init[] = "INIT.TXT";	
//... 
 

/*
    Fluxo padrão: definido em <stdio.h>
	
    FILE *stdin; 
    FILE *stdout; 
    FILE *stderr; 
 
*/

//
// font support.
//

//FILE *font_file;

 
//Diretórios para o shell comparar os comandos com os nomes dos arquivos lá. 
struct _iobuf *pwd; 
struct _iobuf *root;
//...

//Janelas usadas pelo aplicativo.

struct window_d *topbar_scrollbarWindow;
struct window_d *topbar_checkboxWindow;
struct window_d *topbar_editboxWindow;  //edit box.
struct window_d *editboxWindow;  //edit box.
struct window_d *topbarWindow;  //task bar.
struct window_d *i1Window;      //icone 1.
struct window_d *i2Window;      //icone 2.
//...


	

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
// Comunicação Cliente/Servidor:
// Número da mensagem enviada pelo terminal virtual.
// São apenas mensagens usadas pelo terminal virtual 
// em modo texto, relativas a input e output de textos.
// 
//


typedef enum terminal_api_message_number_d {
	
	terminalNull,          // 0
	terminalOpenTerminal,  // Inicia a estrutura de terminal virtual.
    terminalCloseTerminal, // Fecha a estrutura de terminal.
	terminalGetWindow,     //
    terminalGetMessage,    //
    terminalGetLong1,      //
    terminalGetLong2, 	   //
    terminalScreenWidth,
    terminalScreenHeight,
    terminalCursorWidth,
    terminalCursorHeight,
    terminalCharWidth,
    terminalCharHeight	
	
}terminal_api_message_number_t;


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

//...

#define SHELL_STREAM_STATUS_INPUT  1 //input
#define SHELL_STREAM_STATUS_OUTPUT 2 //output
#define SHELL_STREAM_STATUS_ERROR  3 //error


//
// Estrutura principal.
// Informações sobre o shell.
//

typedef struct shell_info_d shell_info_t;
struct shell_info_d
{
	struct window_d *main_window;
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

typedef struct COMMANDHISTORY_D COMMANDHISTORY_T;
struct COMMANDHISTORY_D
{
    int NumberOfCommands;
	int MaximumNumberOfCommands;
	
};
COMMANDHISTORY_T *CommandHistory;  

 
//
// Macros.
// 
 
//#define DeclareStructHandle(name) struct nameJABUTICABA__ { int unused; }; typedef struct nameJABUTICABA__ *name 
//#define DeclareHandle(name) typedef void* name 
  
 
//void *GramadoMain( int argc, char *argv[], unsigned long address, int view );
 
 
//
// Screen support.
//

void shellClearScreen();
void shellRefreshScreen(); //copia o conteúdo do buffer para a tela. (dentro da janela)
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
void shellInsertCharPos(unsigned long offset, char c);
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
void shellHelp();
void shellTree();
void shellThread();
void shellTestLoadFile();
void shellTestThreads();
void shellTestMBR();


int test_operators();

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
unsigned long shellCompare(struct window_d *window);    //Compare command. 
 
// Initialization. 
int shellInit( struct window_d *window );                //Init.
void shellShell();               //Constructor. 
 
// Finalizing ... 
// ??exit, die... 
 
 
//show ascii table
void shellASCII(); 


// copia bytes	
void shell_memcpy_bytes( unsigned char *Dest, 
                         unsigned char *Source,
                         unsigned long Length );

 
//
// shelui.c
//

void shellCreateEditBox();
void shellCreateTopBar(); 
void shellTestDisplayBMP();
void bmpDisplayBMP( void* address, 
                    unsigned long x, 
					unsigned long y, 
					int width, 
					int height );
					
					
//
// End.
//

