

/* Gramado Core shell - builtins commands */


#include "api.h"
#include "types.h"
#include "stddef.h"   
#include "stdio.h"   
#include "stdlib.h"  
#include "string.h"
#include "shell.h"
#include "globals.h"
#include "builtins.h"



void cd_buitins()
{
	printf("cd_buitins:\n");
	return;
};


void cls_builtins()
{
	//@todo
    shellClearScreen();
    shellSetCursor(0,0);
	//shellPrompt();	
};


void copy_builtins()
{
	
};

void date_builtins()
{
	
};

void del_builtins()
{
	
};


void dir_builtins()
{
	//
	// @todo: get set disk id e directory id.
	//

    printf("~dir \n");		
        
	//#test 
	//173 Lista arquivos de um diretório, dado o número do disco,
    //o número do volume e o número do diretório,	
    system_call(173,0,0,0);		
		
	printf("~done\n");	
};


void echo_builtins()
{
	//output the args.
	
	//@todo
	
	printf("\n %s \n",prompt[4]);
	//printf("%s\n",prompt);	
};


void exec_builtins()
{
    printf("~exec\n");	
};

void exit_builtins()
{
    printf("~exit\n");
	printf("Exiting shell process ...\n");
	//refresh_screen();
	//exit(0);	
};

int getpid_builtins()
{
    shellShowPID();	
	return (int) 0; 
};

int getppid_builtins()
{
	shellShowPPID();
	return (int) 0;
};

int getuid_builtins()
{
	shellShowUID();
	return (int) 0;
};

int getgid_builtins()
{
	shellShowGID();
	return (int) 0;
};



void help_builtins( int arg )
{
	switch( arg )
	{
		//all
		case 1:
		    printf("Show all help topics.\n");
			shellHelp();
		    break;
		//min
		case 2:
		    printf("cls, help, exit ...\n");
			break;
		
		default:
			shellHelp();
			break;
			
	}
}


void pwd_builtins()
{
    printf("~pwd - print working directory\n");
    system_call(170,0,0,0);		
};



