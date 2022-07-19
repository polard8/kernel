
// Init process. INIT.BIN.
// This is the first ring3 application.
// (old GWS.BIN)

#include <types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <rtl/gramado.h>


#define __VK_RETURN    0x1C
#define __VK_TAB       0x0F

#define __MSG_COMMAND       40


static isTimeToQuit = FALSE;

// private functions: prototypes;

// local
static int 
gwsProcedure ( 
    void *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );

static void initPrompt(void);
static int initCompareString(void);


// ====================

// local
static int 
gwsProcedure ( 
    void *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{
    if(msg<0){
        return -1;
    }

    switch (msg){

    // range: 4001~4009 
    case __MSG_COMMAND:
        printf("gws.bin: MSG_COMMAND %d \n",long1);
        switch(long1)
        {
            case 4001:  //app1
            printf("init.bin: 4001\n");
            rtl_clone_and_execute("terminal.bin");  break;
            case 4002:  //app2
            printf("init.bin: 4002\n");
            rtl_clone_and_execute("fileman.bin");  break;
            case 4003:  //app3
            printf("init.bin: 4003\n");
            rtl_clone_and_execute("editor.bin");  break;
            case 4004:  //app4
            printf("init.bin: 4004\n");
            rtl_clone_and_execute("reboot.bin");  break;
            
            case 4005:  //app5
            printf("init.bin: 4005\n");
            rtl_clone_and_execute("terminal.bin");  break;
            case 4006:  //app6
            printf("init.bin: 4006\n");
            rtl_clone_and_execute("fileman.bin");  break;
            case 4007:  //app7
            printf("init.bin: 4007\n");
            rtl_clone_and_execute("editor.bin");  break;
            case 4008:  //app8
            printf("init.bin: 4008\n");
            rtl_clone_and_execute("reboot.bin");  break;
            
            default:
                break;
        };
        break;
    default:
        break;
    };
    
    return 0;
}


static void initPrompt(void)
{
    int i=0;

    // Clean prompt buffer.
    
    for ( i=0; i<PROMPT_MAX_DEFAULT; i++ ){ prompt[i] = (char) '\0'; };
    
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

static inline void do_int3(void)
{
    asm ("int $3");
}

static int initCompareString(void)
{
    char *c;
    c = prompt;

    if ( *c == '\0' ){
        goto exit_cmp;
    }
    
    //LF
    printf("\n");


    if( strncmp(prompt,"int3",4) == 0 )
    {
        do_int3();
        goto exit_cmp;
    }

    if( strncmp(prompt,"about",5) == 0 )
    {
        printf ("INIT.BIN: This is the first user application.\n");
        goto exit_cmp;
    }

    
    if( strncmp(prompt,"help",4) == 0 )
    {
        printf ("HELP:\n");
        printf ("Commands: help, wsq, nsq, reboot, shutdown ...\n");
        printf("[control + f9] to open the kernel console\n");
        goto exit_cmp;
    }

    if( strncmp(prompt,"reboot",6) == 0 )
    {
        printf ("REBOOT\n");
        rtl_reboot();
        goto exit_cmp;
    }

    if( strncmp(prompt,"shutdown",8) == 0 )
    {
        printf ("SHUTDOWN\n");
        rtl_clone_and_execute("shutdown.bin");
        goto exit_cmp;
    }

// Window Server:

    if( strncmp(prompt,"ws",2) == 0 )
    {
        printf ("~WS\n");
        rtl_clone_and_execute("gwssrv2.bin");
        goto exit_cmp;
    }

    if( strncmp(prompt,"wsq",3) == 0 )
    {
        printf ("~WSQ\n");
        rtl_clone_and_execute("gwssrv2.bin");
        isTimeToQuit = TRUE;
        goto exit_cmp;
    }

// Network Server:

    if( strncmp(prompt,"ns",2) == 0 )
    {
        printf ("~NS\n");
        rtl_clone_and_execute("gnssrv.bin");
        goto exit_cmp;
    }

    if( strncmp(prompt,"nsq",3) == 0 )
    {
        printf ("~NSQ\n");
        rtl_clone_and_execute("gnssrv.bin");
        isTimeToQuit = TRUE;
        goto exit_cmp;
    }



    if( strncmp(prompt,"client",6) == 0 )
    {
        printf ("~Client\n");
        rtl_clone_and_execute("terminal.bin");
        isTimeToQuit = TRUE;
        goto exit_cmp;
    }

    if( strncmp(prompt,"editor",6) == 0 )
    {
        printf ("~Editor\n");
        rtl_clone_and_execute("editor.bin");
        isTimeToQuit = TRUE;
        goto exit_cmp;
    }


    // ...

    printf ("Command not found, type help for more commands\n");

exit_cmp:
    if(isTimeToQuit==TRUE){
        return 0;
    }
    initPrompt();
    return 0;
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

// The taskswithing will not work without this.

    asm ("int $199 \n");


// interrupts
// Unlock the taskswitching support.
// Unlock the scheduler embedded into the base kernel.
// Only the init process is able to do this.

    //gws_debug_print ("gws.bin: Unlock taskswitching and scheduler \n");
    //printf          ("gws.bin: Unlock taskswitching and scheduler \n");
    gramado_system_call (641,0,0,0);
    gramado_system_call (643,0,0,0);


// ====
// Small command line interpreter.
// We need to hang here because 
// maybe there is no window server installed.

    printf(":: Gramado OS ::\n");

    int C=0;
    initPrompt();
    while(1)
    {
        if( isTimeToQuit == TRUE ){
            break;
        }
        C = (int) fgetc(stdin);
        if( C == __VK_RETURN )
            initCompareString();
        if( C >= 0x20 && C <= 0x7F )
        {
            printf("%c",C);
            fflush(stdout);

            input(C);
        }
    };

    //#debug
    //printf("~Quit\n");
    //while(1){}

//================================
    
    //# no focus!
    //rtl_focus_on_this_thread();
    
    while (TRUE){
        //if( isTimeToQuit == TRUE )
            //break;
        if ( rtl_get_event() == TRUE )
        {
            //if( RTLEventBuffer[1] == MSG_QUIT ){ break; }
            gwsProcedure ( 
                (void*) RTLEventBuffer[0], 
                RTLEventBuffer[1], 
                RTLEventBuffer[2], 
                RTLEventBuffer[3] );
        }
    };

// hang
    while (TRUE){
        rtl_yield();
    };

    return 0;
}

