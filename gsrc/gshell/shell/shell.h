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

#define DEFAULT_BUFFER_MAX_COLUMNS 80
#define DEFAULT_BUFFER_MAX_ROWS    25


//#define SHELL_BUFFER_SIZE 512
//#define SHELL_BUFFER_SIZE 1024 
//#define SHELL_BUFFER_SIZE (80*25)      
//#define SHELL_BUFFER_SIZE (80*25*4)
#define SHELL_BUFFER_SIZE ((DEFAULT_BUFFER_MAX_COLUMNS*DEFAULT_BUFFER_MAX_ROWS)+1) 


 
//
// Messages support.
//


#define CMD_ABOUT 1000
//#define CMD_ABOUT 1001
//#define CMD_ABOUT 1002
//#define CMD_ABOUT 1003
//...




//
// Strings
//
 
//@todo: 
//a versão do sistema operacional deve-se obter através de uma chamada ao sistema. 
#define OS_VERSION     "0.1"  
#define SHELL_VERSION  "0.1"
#define SHELL_PROMPT   ">"
#define SHELL_PROMPT2  "$"
//#define SHELL_PROMPT3  "shell: " 
//... 
 
 
//
// Banners.
//
 
 
// help 
static const char help_banner[] =
    "\n Commands: \n \n"
	"help, version, reboot, exit\n";
	
// tree
static const char tree_banner[] =
"\n"
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
	int colMax;
	//... 
};
shell_metrics_t *ShellMetrics;
//...
 
 
 
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

void shellShowInfo();
void shellShowMetrics();
void shellShowSystemInfo();
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
 
 
//
// shelui.c
//

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

