/*
 * File: builtins.h
 *     Buittin commands for Gramado Core Shell.
 *
 * History:
 *     2018 - Created by Fred Nora.
 */

 
#define fgdfgd 44 
 
 
void cd_buitins();

void cls_builtins();


void copy_builtins();
void date_builtins();
void del_builtins();
void dir_builtins();

void echo_builtins(char *list[]);

void exec_builtins();
void exit_builtins();
int getpid_builtins();
int getppid_builtins();
int getuid_builtins();
int getgid_builtins();
void help_builtins( int arg );
void pwd_builtins();

