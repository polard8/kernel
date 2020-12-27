/*
 * File: builtins.c
 *     Buittin commands for Gramado Core Shell.
 *
 * History:
 *     2018 - Created by Fred Nora.
 */

 
#include "gdeshell.h"


void cd_buitins (void)
{
    printf ("cd_buitins:\n");
}

//cls
void cls_builtins (void)
{
    shellClearScreen ();
}

void copy_builtins(void)
{
}

void date_builtins(void)
{
}

void del_builtins(void)
{
    printf ("~del: Delete ... \n");
}

void dir_builtins (void)
{

	// #todo: 
	// Get set disk id e directory id.

    printf ("~dir \n");

    // #test 
    // 173 - Lista arquivos de um diretório, 
    // dado o número do disco,
    // o número do volume e o número do diretório,

    system_call (173,0,0,0);

    printf ("~done\n");
}


// echo command.
// Imprimir a lista de comandos de uma linha de comandos.
void echo_builtins (char *list[])
{	
    shell_print_tokenList( list, " ");
	//shell_print_tokenList( list, "/");
}

void exec_builtins (void)
{
    printf("@todo: ~exec\n");
}

void exit_builtins ()
{
    printf ("gdeshell.bin: Exiting ...\n");
    exit(0);
}

int getpid_builtins (void)
{
    shellShowPID();  return 0; 
}

int getppid_builtins (void)
{
    shellShowPPID();  return 0;
}

int getuid_builtins (void)
{
    shellShowUID ();  return 0;
}


int getgid_builtins (void)
{
    shellShowGID ();  return 0;
}


// Help.
void help_builtins (void)
{
    printf ("gdeshell: cls, ls, reboot, newfile, newdir, creat, mkdir \n");
}

    unsigned long __profiler_ints_irq0; 
    unsigned long __profiler_ints_irq1; 
    unsigned long __profiler_ints_irq2; 
    unsigned long __profiler_ints_irq3; 
    unsigned long __profiler_ints_irq4; 
    unsigned long __profiler_ints_irq5; 
    unsigned long __profiler_ints_irq6; 
    unsigned long __profiler_ints_irq7; 
    unsigned long __profiler_ints_irq8; 
    unsigned long __profiler_ints_irq9; 
    unsigned long __profiler_ints_irq10;
    unsigned long __profiler_ints_irq11;
    unsigned long __profiler_ints_irq12;
    unsigned long __profiler_ints_irq13;
    unsigned long __profiler_ints_irq14;
    unsigned long __profiler_ints_irq15;
    unsigned long __profiler_ints_gde_services;
    
void ints_builtins(void)
{
        __profiler_ints_irq0 = gde_get_system_metrics (100);
        __profiler_ints_irq1 = gde_get_system_metrics (101);
        __profiler_ints_irq2 = gde_get_system_metrics (102);
        __profiler_ints_irq3 = gde_get_system_metrics (103);
        __profiler_ints_irq4 = gde_get_system_metrics (104);
        __profiler_ints_irq5 = gde_get_system_metrics (105);
        __profiler_ints_irq6 = gde_get_system_metrics (106);
        __profiler_ints_irq7 = gde_get_system_metrics (107);
        __profiler_ints_irq8 = gde_get_system_metrics (108);
        __profiler_ints_irq9 = gde_get_system_metrics (109);
        __profiler_ints_irq10 = gde_get_system_metrics (110);
        __profiler_ints_irq11 = gde_get_system_metrics (111);
        __profiler_ints_irq12 = gde_get_system_metrics (112);
        __profiler_ints_irq13 = gde_get_system_metrics (113);
        __profiler_ints_irq14 = gde_get_system_metrics (114);
        __profiler_ints_irq15 = gde_get_system_metrics (115);
        
        __profiler_ints_gde_services = gde_get_system_metrics (117);
        
        printf ("profiler ints:\n");
        printf ("irq0: %d (timer)\n",__profiler_ints_irq0);
        printf ("irq1: %d (ps/2 keyboard)\n",__profiler_ints_irq1);
        printf ("irq2: %d \n",__profiler_ints_irq2);
        printf ("irq3: %d \n",__profiler_ints_irq3);
        printf ("irq4: %d (serial com1)\n",__profiler_ints_irq4);
        printf ("irq5: %d \n",__profiler_ints_irq5);
        printf ("irq6: %d \n",__profiler_ints_irq6);
        printf ("irq7: %d \n",__profiler_ints_irq7);
        printf ("irq8: %d (rtc)\n",__profiler_ints_irq8);
        printf ("irq9: %d (nic controller)\n",__profiler_ints_irq9);
        printf ("irq10: %d \n",__profiler_ints_irq10);
        printf ("irq11: %d \n",__profiler_ints_irq11);
        printf ("irq12: %d (ps/2 mouse)\n",__profiler_ints_irq12);
        printf ("irq13: %d \n",__profiler_ints_irq13);
        printf ("irq14: %d (ata1)\n",__profiler_ints_irq14);
        printf ("irq15: %d (ata2)\n",__profiler_ints_irq15);
        printf ("int 0x80: %d (System interrupt)\n",
            __profiler_ints_gde_services );
}




void pwd_builtins (void)
{
    printf ("~pwd - print working directory: \n");
    system_call ( 170, 0, 0, 0 );
}


//
// End.
//


