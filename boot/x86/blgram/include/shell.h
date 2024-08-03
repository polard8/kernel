/*
 * File: shell.h
 * Descrição:
 *     Header para o mini-shell dentro do Boot Loader 32 bit.
 * #todo: 
 *     Deixar o minishell enxuto, com poucos recursos.
 *     Deixar principalmente os recursos de configuração 
 *     da inicialização.
 * 2015 - Created by Fred Nora.
 */

#ifndef __SHELL_H
#define __SHELL_H    1


// 
// Command support.
//


// Prompt.
extern char prompt[250];
extern unsigned long prompt_pos;

//Quando o comando terminou. (string completa).
extern unsigned long g_cmd_status; 


//
// Shell
//


// Prototypes ========================

//Main.
int blShellMain ( int argc, char *argv[] );

// Initialization
void shellInit(void);
int shellInitializePrompt();
//...

void shellWaitCmd();
unsigned long shellCompare(void);
void shellHelp(void);
//...

int rescueShell(void);

#endif    

//
// End.
//

