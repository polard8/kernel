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
 * Versão 1.0, 2016.
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
// Usage banner.
//
 
static const char usage[] =
    "Usage: shell [arguments...]\n"
    "       shell -help             Display this help message and exit.\n"
    "       shell -version          Output version information and exit.";
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


//int app_main(int argc, char *argv[]); 

 
//
// End.
//

