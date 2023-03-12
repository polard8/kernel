
// Init process. INIT.BIN.
// This is the first ring3 process.
// This is also has an embedded shell. 
// This way we can use it to launch the window server.
// After that the applications goes to a loop
// receving messages from the kernel.

/*
#include <types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <rtl/gramado.h>
*/

#include "init.h"

//Used by creat()
//#include <fcntl.h>

#define __COLOR_BLUE   0x000000FF
#define __COLOR_WHITE  0x00FFFFFF

#define __VK_RETURN    0x1C
#define __VK_TAB       0x0F


static isTimeToQuit = FALSE;


static const char *app1_name = "gramland.bin";
//static const char *app1_name = "gwssrv.bin";
static const char *app2_name = "gws.bin";
static const char *app3_name = "gnssrv.bin";
static const char *app4_name = "gns.bin";


// Flags:
// --dm - Launches the default Display Manager.
// -?   - ...
// -?   - ...
static const char *cmdline1 = "gramland -1 -2 -3";
//static const char *cmdline1 = "gwnsrv -1 -2 -3 --dm";
// ...

// private functions: prototypes;


// Loops
static int __coolmenu_loop(void);
static int __stdin_loop(void);

static void initPrompt(void);
static int __CompareString(void);

static void do_help(void);
static void do_launch_de(void);
static void do_launch_de2(void);
static void do_launch_list(void);


static void do_clear_console(void);

// ====================

static void do_help(void)
{
    printf ("\n");
    printf ("HELP:\n");
    printf ("Commands: help, wsq, nsq, reboot, shutdown ...\n");
// Launch the DE, Desktop Environment.
// See: gramland/
    printf ("'wsq': Launch the GUI\n");
    printf("[control + f9] to open the kernel console\n");
}

static void do_launch_list(void)
{
// Raw and ugly set of programs.
    rtl_clone_and_execute("gramland.bin");
    rtl_clone_and_execute("terminal.bin");
    rtl_clone_and_execute("editor.bin");
    rtl_clone_and_execute("browser.bin");
    rtl_clone_and_execute("fileman.bin");

// #
// Quit the command line.
// It's too much faster if we do not quit.
// But we need to quit and start listening for messages.
    isTimeToQuit = TRUE;
}

static void do_launch_de(void)
{
    int ret_val=-1;

    char filename[16];
    size_t string_size=0;
    memset(filename,0,16);


    do_clear_console();
    printf ("Launching GUI\n");

// Sending cmdline via stdin
    rewind(stdin);
    write( fileno(stdin), cmdline1, strlen(cmdline1) );

// Launch new process.
    sprintf(filename,app1_name);
    string_size = strlen(app1_name);
    filename[string_size] = 0;
    ret_val = (int) rtl_clone_and_execute(filename);
    //ret_val = (int) rtl_clone_and_execute(app1_name);
    if (ret_val<=0){
        printf("Couldn't clone\n");
        return;
    }

// Sleep (Good!)
    //sc82( 266, 8000, 8000, 8000 );

    //printf("pid=%d\n",ret_val);

// Quit the command line.
    isTimeToQuit = TRUE;
}

static void do_launch_de2(void)
{
    int ret_val=-1;

    do_clear_console();
    printf ("Launching GUI\n");
// Sending cmdline via stdin
    rewind(stdin);
    write( fileno(stdin), cmdline1, strlen(cmdline1) );
// Launch new process.
    ret_val = (int) rtl_clone_and_execute("gramland.bin");
    if (ret_val<=0){
        printf("Couldn't clone\n");
        return;
    }
// Launch new process.
    ret_val = (int) rtl_clone_and_execute("terminal.bin");
    if (ret_val<=0){
        printf("Couldn't clone\n");
        return;
    }

// Sleep (Good!)
    //sc82( 266, 8000, 8000, 8000 );
    //printf("pid=%d\n",ret_val);
// Quit the command line.
    isTimeToQuit = TRUE;
}



static void initPrompt(void)
{
    register int i=0;

// Clean prompt buffer.
    for ( i=0; i<PROMPT_MAX_DEFAULT; i++ ){
        prompt[i] = (char) '\0';
    };

    prompt[0] = (char) '\0';
    prompt_pos    = 0;
    prompt_status = 0;
    prompt_max    = PROMPT_MAX_DEFAULT;  

// Prompt
    printf("\n");
    putc('$',stdout);
    putc(' ',stdout);
    fflush(stdout);
}


// Clear the background of the current virtual console.
// #todo: 
// Create a function in rtl for this.
static void do_clear_console(void)
{
// Change the console color.
    //ioctl(1,440, 0x0011DD11);
// White on blue.
// Clear the background of the fg console.
    //sc82( 8003,__COLOR_BLUE,0,0 );
// Change the fg color of the fg console.
    //sc82( 8004,__COLOR_WHITE,0,0 );

//#todo
// Use ioctl instead

// Respeitando as cores do fg console.
    ioctl(1,440,0);
}

static inline void do_int3(void)
{
    asm ("int $3");
}

static inline void do_cli(void)
{
    asm ("cli");
}

static inline void do_sti(void)
{
    asm ("sti");
}

static inline void do_hlt(void)
{
    asm ("hlt");
}

static int __CompareString(void)
{
    int ret_val=-1;
    char *c;
// Generic file support.
    int fd= -1;
    FILE *fp;

// Primeira letra do prompt.
    c = prompt;
    if ( *c == '\0' ){
        goto exit_cmp;
    }

// LF
    printf("\n");

// #test
// Enter the cool menu.
    if (strncmp(prompt,"coolmenu",8) == 0)
    {
        __coolmenu_loop();
        goto exit_cmp;
    }

    //#test
    if ( strncmp(prompt,"list",4) == 0 ){
        do_launch_list();
        goto exit_cmp;
    }

    if ( strncmp(prompt,"t1",2) == 0 )
    {
        //creat("saved1.txt",0);
        //fd = open("saved1.txt",0,0);
        //close(fd);
        //fp = fopen("SYSLOG  TXT","r+");
        //fprintf(fp,"Writing on syslog.txt from ring3.");
        //close(fp->_file);
        
        //ioctl(1,400, 0x00FFDD11); //change virtual console fg color.
        //ioctl(1,402, 0x0011DD11); //change virtual console bg color.
        //ioctl(1,440, 0x0011DD11);  // clear console.
        goto exit_cmp;
    }

    if ( strncmp(prompt,"cls",3) == 0 ){
        do_clear_console();
        goto exit_cmp;
    }

    if ( strncmp(prompt,"int3",4) == 0 ){
        do_int3();
        goto exit_cmp;
    }

    if ( strncmp(prompt,"cli",3) == 0 ){
        do_cli();
        goto exit_cmp;
    }

    if ( strncmp(prompt,"sti",3) == 0 ){
        do_sti();
        goto exit_cmp;
    }

// hlt:
// gp fault
    if ( strncmp(prompt,"hlt",3) == 0 ){
        do_hlt();
        goto exit_cmp;
    }

    if ( strncmp(prompt,"quit",4) == 0 ){
        isTimeToQuit=TRUE;
        goto exit_cmp;
    }

/*
// yes or no.
// see: stdio.c
    static int yn_result = -1;
    if ( strncmp(prompt,"yn",2) == 0 )
    {
        yn_result = (int) rtl_y_or_n();
        if ( yn_result == TRUE ){
            printf("Returned TRUE\n");
        }
        if ( yn_result == FALSE ){
            printf("Returned FALSE\n");
        }
        if ( yn_result != TRUE && yn_result != FALSE ){
            printf("Returned Invalid result\n");
        }
        goto exit_cmp;
    }
*/

    if ( strncmp(prompt,"about",5) == 0 ){
        printf ("INIT.BIN: This is the first user application\n");
        goto exit_cmp;
    }

    if ( strncmp(prompt,"help",4) == 0 ){
        do_help();
        goto exit_cmp;
    }

    if ( strncmp(prompt,"reboot",6) == 0 ){
        printf ("REBOOT\n");
        rtl_reboot();
        goto exit_cmp;
    }

    if ( strncmp(prompt,"shutdown",8) == 0 ){
        printf ("SHUTDOWN\n");
        rtl_clone_and_execute("shutdown.bin");
        goto exit_cmp;
    }

//==============================
// Window Server:

// Initialize the window server.
    if ( strncmp(prompt,"ws",2) == 0 ){
        //printf ("~WS\n");
        //rtl_clone_and_execute("gwssrv.bin");
        goto exit_cmp;
    }
// Initialize the window server and quit the command line.
    if ( strncmp(prompt,"wsq",3) == 0 ){
        printf ("~WSQ\n");
        do_launch_de();
        goto exit_cmp;
    }
// Initialize the window server, the terminal and 
// quit the command line.
    if ( strncmp(prompt,"wsq2",4) == 0 ){
        printf ("~WSQ2\n");
        do_launch_de2();
        goto exit_cmp;
    }

    if ( strncmp(prompt,"boot",4) == 0 ){
        printf ("~BOOT\n");
        do_launch_de();
        goto exit_cmp;
    }
    if ( strncmp(prompt,"gramado",7) == 0 ){
        printf ("~GRAMADO\n");
        do_launch_de();
        goto exit_cmp;
    }

//==============================
// Network Server:

// Initialize the network server.
    if ( strncmp(prompt,"ns",2) == 0 ){
        //printf ("~NS\n");
        //rtl_clone_and_execute("gnssrv.bin");
        goto exit_cmp;
    }
// Initialize the network server and quit the command line.
    if( strncmp(prompt,"nsq",3) == 0 ){
        printf ("~NSQ\n");
        do_clear_console();
        rtl_clone_and_execute(app3_name);
        isTimeToQuit = TRUE;
        goto exit_cmp;
    }

//
// 3D stuff
//

// #todo
// Something is not working fine
// when we put the name directly in the parameters field.
// We need a pointer instead.
// see: meta/

    // GMC - Gramado Meta Compositor.
    if ( strncmp(prompt,"comp",4) == 0 ){
        printf ("~ Comp:\n");
        do_clear_console();
        rtl_clone_and_execute("comp.bin");
        isTimeToQuit = TRUE;
        goto exit_cmp;
    }
    // eng.bin
    if ( strncmp(prompt,"eng",3) == 0 ){
        printf ("~ Game engine:\n");
        do_clear_console();
        rtl_clone_and_execute("eng.bin");
        isTimeToQuit = TRUE;
        goto exit_cmp;
    }
    // Game 1.
    if ( strncmp(prompt,"game1",5) == 0 ){
        printf ("~ Game 1:\n");
        do_clear_console();
        rtl_clone_and_execute("eng.bin");
        isTimeToQuit = TRUE;
        goto exit_cmp;
    }

// ----------------------------------------

    printf ("Command not found, type 'help' for more commands\n");

/*
 // This thing is very cool.
 // I'm not using it for safity.
    printf ("Command not found!\n");
    // DE - Desktop Environment?
    printf ("Do You want to launch the GUI\n");
    static int yn_result = -1;
    yn_result = (int) rtl_y_or_n();
    if ( yn_result == TRUE ){
        //printf("Returned TRUE\n");
        do_launch_de();
        goto exit_cmp;
    }
    if ( yn_result == FALSE ){
        //printf("Returned FALSE\n");
        printf ("Type 'help' for more commands\n");
    }
*/

exit_cmp:
    if (isTimeToQuit==TRUE){
        return 0;
    }
    initPrompt();
    return 0;
}

static int __coolmenu_loop(void)
{
// Get input from sdtin.

// Clear the console and set cursor position to 0,0.
    do_clear_console();

// ====
// Small command line interpreter.
// We need to hang here because 
// maybe there is no window server installed.

    printf("\n");
    printf(":: Cool menu ::\n");

    printf("\n");
    printf("+ (q) - Quit the cool menu\n");  
    printf("\n");
    printf("+ (r) - Reboot the system\n");  
    printf("\n");
    printf("+ (s) - Shutdown the system\n");  

    initPrompt();

    register int C=0;
    static int yn_result = FALSE;

    while(1)
    {
        if( isTimeToQuit == TRUE ){
            break;
        }
        C = (int) fgetc(stdin);
        
        // Quit the cool menu.
        if (C == 'q'){
            break;
        }

        // Reboot the system.
        if (C =='r')
        {
            printf ("Reboot the system? (yn)\n");
            yn_result = (int) rtl_y_or_n();
            if (yn_result == TRUE){
                rtl_clone_and_execute("reboot.bin");
            }
        }

        // Poweroff the system.
        if (C =='s')
        {
            printf ("Shutdown the system? (yn)\n");
            yn_result = (int) rtl_y_or_n();
            if (yn_result == TRUE){
                rtl_clone_and_execute("shutdown.bin");
            }
        }
    };
}

static int __stdin_loop(void)
{
// Get input from sdtin.

//================================

// Clear the console and set cursor position to 0,0.
    do_clear_console();

// ====
// Small command line interpreter.
// We need to hang here because 
// maybe there is no window server installed.

    printf(":: Gramado OS ::\n");
    initPrompt();

    register int C=0;

    while(1)
    {
        if( isTimeToQuit == TRUE ){
            break;
        }
        C = (int) fgetc(stdin);
        if( C == __VK_RETURN )
        {
            __CompareString();
        }
        if( C >= 0x20 && C <= 0x7F )
        {
            printf("%c",C);
            fflush(stdout);

            input(C);  // coloca no prompt.
        }
    };

    //#debug
    //printf("~Quit\n");
    //while(1){}

//================================
}


int main( int argc, char **argv)
{
    //#todo
    //printf()

//testando se esse codigo esta mesmo em ring3. 
//#bugbug: this proces is running in ring0.
    //asm ("cli");

//
// Interrupts
//

// Changing  the interrupt flag and the iopl.
// The taskswithing will not work without this.
// #test: We're doint that at the libc initialization.
// see: crt0.c
 
    // asm volatile ("int $199 \n");


// interrupts
// Unlock the taskswitching support.
// Unlock the scheduler embedded into the base kernel.
// Only the init process is able to do this.

    //gws_debug_print ("gws.bin: Unlock taskswitching and scheduler \n");
    //printf          ("gws.bin: Unlock taskswitching and scheduler \n");
    gramado_system_call (641,0,0,0);
    gramado_system_call (643,0,0,0);



/*
//================================

// Clear the console and set cursor position to 0,0.
    do_clear_console();

// ====
// Small command line interpreter.
// We need to hang here because 
// maybe there is no window server installed.

    printf(":: Gramado OS ::\n");
    initPrompt();

    register int C=0;

    while(1)
    {
        if( isTimeToQuit == TRUE ){
            break;
        }
        C = (int) fgetc(stdin);
        if( C == __VK_RETURN )
        {
            __CompareString();
        }
        if( C >= 0x20 && C <= 0x7F )
        {
            printf("%c",C);
            fflush(stdout);

            input(C);  // coloca no prompt.
        }
    };

    //#debug
    //printf("~Quit\n");
    //while(1){}

//================================
*/

//================================
// Get input from stdin.
    __stdin_loop();

//================================
// Get input from idle thread.
// Idle thread loop.
    return (int) run_server();
}





