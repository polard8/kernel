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
// Definições.
//
 
#define SHELL_VERSION  "1.0"
#define SHELL_PROMPT   ">"
//#define SHELL_PROMPT   "$"
//#define SHELL_PROMPT   "shell: " 
//... 
 
 
//
// Macros.
// 
 
//#define DeclareStructHandle(name) struct nameJABUTICABA__ { int unused; }; typedef struct nameJABUTICABA__ *name 
//#define DeclareHandle(name) typedef void* name 
 

//cores do texto. 
unsigned long backgroung_color;  //pano de fundo.
unsigned long foregroung_color;  //texto.
 
 
//
// banners.
//
 
static const char usage[] =
    "Usage: shell [arguments...]\n"
    "       shell -help             Display this help message and exit.\n"
    "       shell -version          Output version information and exit.\n";
	//...
 
static const char help_banner[] =
    "\n Commands: \n \n"
	"boot, cls, dir, exit\n"
    "hd, help, install, ls\n"
    "newfile, newdir, mbr, reboot\n"
	"root, save, service, slots\n"
	"start, t1, t2, t3\n"
	"version\n";
	
	//... 
	
	
//
// files.
//	
	
static const char init_file_name[] = "INIT    TXT";	
static const char  bmp1_file_name[] = "BMP1    BMP";
static const char  bmp2_file_name[] = "BMP2    BMP";
static const char  bmp3_file_name[] = "BMP3    BMP";
static const char  bmp4_file_name[] = "BMP4    BMP";	
//... 
 
//
// Structures.
// 
 

typedef struct shell_hook_d shell_hook_t; 
struct shell_hook_d
{
	int dummy;
	//struct window_d *window;
	//struct rect_d *rect;
}; 
shell_hook_t *ShellHook; 


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
 
 
//void *GramadoMain( int argc, char *argv[], unsigned long address, int view );
 
//
// End.
//

