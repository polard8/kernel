
//
// pool
//

//tipo array de strings
typedef char ** poll;
typedef char ** POLL;

//array de unsigned longs contendo ponteiros 
//para pools de strings;
typedef unsigned long pool_list_t;
typedef unsigned long POOLLIST;
 

 



/* Values that can be returned by execute_command (). */
#define EXECUTION_FAILURE 1
#define EXECUTION_SUCCESS 0


/* The list of characters that are quoted in double-quotes with a
   backslash.  Other characters following a backslash cause nothing
   special to happen. */
#define slashify_in_quotes "\\`\"$"



//
// # env. support # 
//

/*POSIX*/

//colunas e linhas
#define ENV_COLUMNS "COLUMNS"
#define ENV_LINES "LINES"

#define ENV_LOGNAME "LOGNAME"

#define ENV_PATH "PATH"

#define ENV_SHELL "SHELL"

//the local time zone
#define ENV_TZ "TZ"

/*OUTROS*/

//home directory of the present user.
#define ENV_HOME "HOME"

//login name
#define ENV_USER "USER"


//the language she would like to see messages
#define ENV_LANG "LANG"

//the default printer to be used
#define ENV_PRINTER "PRINTER"
#define ENV_LPDEST "LPDEST"

//#define FILENAME_LENGTH (8+3) 

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
//#define LINES 25
//#define COLUMNS 80
//#define NPAR 16


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

#define SHELL_PATHNAME_SEPARATOR "/"
#define SHELL_PATHNAME_TERMINATOR "\0"

#define SHELL_STRING_TERMINATOR "\0" 


//@todo: 
//a versão do sistema operacional deve-se obter através de uma chamada ao sistema. 
#define OS_VERSION     "0.1"  
#define SHELL_VERSION  "0.1"

//prompt
#define SHELL_PROMPT   "$"
#define SHELL_PROMPT2  "#"
#define SHELL_PROMPT3  "%"
#define SHELL_PROMPT4  ">"
//... 



//
// Volume support
//

//Volume list
#define SHELL_ROOT_STRING        "root:"
#define SHELL_VOLUMELIST_STRING  "root:"

//volumes
#define SHELL_UNKNOWNVOLUME_STRING "unknown-volume"
#define SHELL_VOLUME0_STRING "volume0"   //vfs
#define SHELL_VOLUME1_STRING "volume1"   //boot volume
#define SHELL_VOLUME2_STRING "volume2"   //system volume.
//...

//
// pwd support
//

#define SHELL_UNKNOWNWORKINGDIRECTORY_ID (-1)
#define SHELL_VFSWORKINGDIRECTORY_ID     0
#define SHELL_BOOTWORKINGDIRECTORY_ID    1
#define SHELL_SYSTEMWORKINGDIRECTORY_ID  2


#define SHELL_VFSWORKINGDIRECTORY_STRING     "volume1"
#define SHELL_BOOTWORKINGDIRECTORY_STRING    "volume1"
#define SHELL_SYSTEMWORKINGDIRECTORY_STRING  "volume2"
#define SHELL_UNKNOWNWORKINGDIRECTORY_STRING "unknown-directory"

#define WORKINGDIRECTORY_STRING_MAX 32


//...

#define SHELL_STREAM_STATUS_INPUT  1 //input
#define SHELL_STREAM_STATUS_OUTPUT 2 //output
#define SHELL_STREAM_STATUS_ERROR  3 //error


/*
 * File: globals.h
 * 
 * Global variables.
 *
 * History:
 *     2018 - Created by Fred Nora.
 */
 
//"global command" stuff 
#define glob_percent_sign '%' 
#define glob_underscore '_'
#define glob_square_brackets_left '['
#define glob_square_brackets_right ']'
#define glob_caret '^'
#define glob_asterisk '*'
#define glob_number_sign '#'
#define glob_question_mark '?'
//... 
 
 
#define SHELL_TERMINAL_COLOR 0
#define SHELL_TERMINAL_COLOR2 0x303030
//...



/*
#define BLACK       0
#define RED         1
#define GREEN       2
#define BROWN       3
#define BLUE        4
#define MAGENTA     5
#define CYAN        6
#define LIGHTGRAY   7
#define DARKGRAY    8
#define LIGHTRED    9
#define LIGHTGREEN  10
#define YELLOW      11
#define LIGHTBLUE   12
#define PINK        13
#define LIGHTCYAN   14
#define WHITE       15 
*/ 
 
 
 
//#ifndef whitespace
//#define whitespace(c) (((c) == ' ') || ((c) == '\t'))
//#endif 


//#ifndef digit
//#define digit(c)  ((c) >= '0' && (c) <= '9')
//#endif

//#ifndef isletter
//#define isletter(c) (((c) >= 'A' && (c) <= 'Z') || ((c) >= 'a' && (c) <= 'z'))
//#endif

//#ifndef digit_value
//#define digit_value(c) ((c) - '0')
//#endif
 
 
//#define NEWLINE '\n' 
//#define TAB '\t'
//#define SPACE 0x020
 



//
// Estrutura para mainpular linhas dentro do screen_buffer[]
//


#define MAGIC_NORMALLINE 1234
//...

#define LINE_SIZE_MAX 80

#define LINE_COUNT_MAX 2048


#define SCREENBUFFER_COUNT_MAX 8





//
// ## System Metrics ##
//

int smScreenWidth;                   //1 
int smScreenHeight;                  //2
unsigned long smCursorWidth;         //3
unsigned long smCursorHeight;        //4
unsigned long smMousePointerWidth;   //5
unsigned long smMousePointerHeight;  //6
unsigned long smCharWidth;           //7
unsigned long smCharHeight;          //8
//...

//
// ## Window limits ##
//

//full screen support
unsigned long wlFullScreenLeft;
unsigned long wlFullScreenTop;
unsigned long wlFullScreenWidth;
unsigned long wlFullScreenHeight;

//limite de tamanho da janela.
unsigned long wlMinWindowWidth;
unsigned long wlMinWindowHeight;
unsigned long wlMaxWindowWidth;
unsigned long wlMaxWindowHeight;

//quantidade de linhas e colunas na área de cliente.
int wlMinColumns;
int wlMinRows;
int wlMaxColumns;
int wlMaxRows;


//
//  ## Window size ##
//

unsigned long wsWindowWidth;
unsigned long wsWindowHeight;
//...


//
//  ## Window position ##
//

unsigned long wpWindowLeft;
unsigned long wpWindowTop;
//..





//@todo:
//devemos criar uma rotina que inicialisa
//esses buffers.



//#importante:
//Linhas visíveis.
//número da linha
//isso será atualizado na hora do scroll.
int textTopRow;  //Top nem sempre será '0'.
int textBottomRow;

//linha e coluna atuais
int textCurrentRow;
int textCurrentCol;

int textSavedRow;
int textSavedCol;


int textWheelDelta; //delta para rolagem do texto.
int textMinWheelDelta;  //mínimo que se pode rolar o texto
int textMaxWheelDelta;  //máximo que se pode rolar o texto
//...




//
// ## pathname suppport ##
//

#define PATH_SEPARATOR '/'
#define PATH_TERMINATOR '\0'

#define PATHNAME_LENGHT (64)
char pathname_buffer[PATHNAME_LENGHT];
int pathname_lenght; //tamanho do atual pathname.
int pathname_initilized;


// Colors
 
 
//cores do texto. 
unsigned long backgroung_color;  //pano de fundo.
unsigned long foregroung_color;  //texto.






//
// ## filename suppport ##
//

#define FILENAME_LENGHT (8+3)
char filename_buffer[FILENAME_LENGHT];
int filename_lenght; //tamanho do nome de arquivo atual.
int filename_initilized;


//...



//marcador do cursor.
unsigned long screen_buffer_pos;    //(offset) 

unsigned long screen_buffer_x;      //current col 
unsigned long screen_buffer_y;      //current row

static unsigned long screen_buffer_saved_x = 0;
static unsigned long screen_buffer_saved_y = 0;





int EOF_Reached;


char *current_volume_string;
int current_volume_id;


//...

int g_current_disk_id;
int g_current_volume_id;
int g_current_workingdirectory_id;  //??




// a string do diretório de trabalho.
char current_workingdiretory_string[WORKINGDIRECTORY_STRING_MAX];
int pwd_initialized;

#define CalculateRowScanLine(WindowY,CharHeight) \
    ( WindowY * CharHeight )


#define CalculateColumnScanLine(WindowX,CharWidth) \
    ( WindowX * CharWidth )
	
	
	



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
	" pwd       - Print working directory\n"
    " reboot    - Reboot system\n"
    " rename    - Rename file or directory\n"
	" shutdown  - Shutdown your computer locally or remotely\n"
	" time      - Time\n"
	" version   - Shell version\n"
	"\n";

// experience banner
static const char experience_banner[] =
    "\n Try these commands: \n \n"
	" ?            - This help\n"
	" cls          - Clear screen\n"
	" dir          - List\n"
	" exit         - Exit shell\n"
	" gramcode     - Text editor\n"
	" help         - This help\n"
	" help --tests - Extra commands\n"
	" jackpot      - Game\n"	
	" kernel-info  - kernel Info\n"
	" mm-info      - Memory Info\n"
	" disk-info    - Disk Info\n"
	" volume-info  - Volume Info\n"
	" pwd          - Print working directory\n"
    " reboot       - Reboot system\n"	
	"\n";

	
// tests banner 
// mostra os comandos para testes do sistema 
// e aplicativos em deseenvolvimento.
static const char tests_banner[] =
    "\n Try these commands: \n \n"
	" about       - Testing message\n"
	" bmp         - bmp <filename>\n"
	" cd          - cd <dirname>\n"
	" color       - color --humility | color --pride\n"
	" disk-info   - Disk Info\n"
	" exit        - Exit shell\n"
	" fork        - fork\n"	
    " heap        - User mode Heap test\n"	
	" help        - This help\n"
	" kernel-info - kernel Info\n"	
    " mbr         - MBR\n"
	" pci-info    - PCI Info\n"
    " socket-test - Socket test\n"    
    " system-info - System info\n"
	" timer-test  - Timer test\n"
	" ~>          - getpid getppid getuid getgid\n"	
	" ~>          - get-usersession get-room get-desktop\n"		
	" ~>          - dialog-box edit-box message-box\n"
	" ~>          - mm-info mm-kernelheap mm-processheap\n"
	" ~>          - test-taskman-server\n"
	" ~>          - t1 t2 t3 ... t6 t17\n"	
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


//...

//Lista de palavras reservadas.
//São as mesmas da gramado language, pois 
//a gramado language é uma linguagem de script.
//*.gra  usar esse >>> (*.gl1)
static char *RESERVED[] = {
	"start",   //início do script
	"finish",  //fim do script
	"super",   //tipo genérico.
	"rules",   //fecha declaração (;)
	"condition",   //
	"open",        //( 
	"close",       //)
	"run",         //{
	"stop",        //} 
	"guarantee",   //while
	"mix",         //done: ?? 
	"here",        //system() command 
	"there",       // fecha (;)
};


static unsigned char SPECIAL[] = {
	'(',
	')',
	'{',
	'}',
	'/',
	'*',
	'-',
	'+',
	'|',
	'\'',
	'@',
	'$',
	'%',
	'&',
	'+',	
	//...
}; 


static unsigned char SPECIALOPEN[] = {
	'(',
	'{',
	'[',
	//...
}; 

static unsigned char SPECIALCLOSE[] = {
	')',
	'{',
	']',
	//...
}; 


static unsigned char SPECIALMATH[] = {
	'/',
	'*',
	'-',
	'+',
	'.',
	',',
	//...
}; 




	
	
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







