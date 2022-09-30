
// Init process. INIT.BIN.
// This is the first ring3 process.
// This is also a server.

#include <types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <rtl/gramado.h>

//Used by creat()
//#include <fcntl.h>


#define __VK_RETURN    0x1C
#define __VK_TAB       0x0F

#define __MSG_COMMAND       40


static isTimeToQuit = FALSE;

// The tid of the caller.
// Sent us a system message.
static int __Caller=-1;

static const char *app1_name = "gwssrv.bin";
static const char *app2_name = "gws.bin";
static const char *app3_name = "gnssrv.bin";
static const char *app4_name = "gns.bin";

// private functions: prototypes;

// local
static int 
__Procedure ( 
    void *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );

static int __server_loop(void);

static void initPrompt(void);
static int __CompareString(void);


// ====================

// local
// #todo: change this name.
static int 
__Procedure ( 
    void *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{
    if(msg<0){
        return -1;
    }

    switch (msg){


// Start a client.
// It's gonna wor only if the is already running.
// range: 4001~4009 

    case __MSG_COMMAND:
        printf("init.bin: MSG_COMMAND %d \n",long1);
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
            //rtl_clone_and_execute("cmdline.bin");  break;
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

    // #test Hello.
    // Responding the hello.
    // Hey init, are you up?
    case 44888:
        //printf("init.bin: 44888 received | sender=%d receiver=%d\n",
        //    RTLEventBuffer[8],   //sender (the caller)
        //    RTLEventBuffer[9] ); //receiver
        printf("init.bin: 44888 received from %d\n", __Caller);
        // Reply: Sending response
        // Sending back the same message found into the buffer.
        rtl_post_system_message( 
            (int) __Caller,  //message back to caller.
            (unsigned long) &RTLEventBuffer[0] );

        //rtl_clone_and_execute("gnssrv.bin");
        //rtl_clone_and_execute("gns.bin");
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


//#todo: Create a function in rtl for this.
static void do_clear_console(void)
{

#define __COLOR_BLUE     0x000000FF
#define __COLOR_WHITE    0x00FFFFFF

    // Change the console color.
    //ioctl(1,440, 0x0011DD11);

// White on blue.
// Clear the background of the fg console.
     sc82( 8003,__COLOR_BLUE,0,0 );
// Change the fg color of the fg console.
     sc82( 8004,__COLOR_WHITE,0,0 );
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

static inline void do_restorer(void);
static inline void do_restorer(void)
{
    asm ("int $198");
}
void callback1(void)
{
    printf("INIT: Callback\n");
    do_restorer();

    while(1){
        printf("."); fflush(stdout);
    }
}


static int __CompareString(void)
{
    int ret_val=-1;
    char *c;
    c = prompt;
// Generic file support.
    int fd= -1;
    FILE *fp;
 
 
    if ( *c == '\0' ){
        goto exit_cmp;
    }
    
    //LF
    printf("\n");


//testando callback
//o kernel tem que retornar para a funçao indicada.
//#suspended: The ws is using this callback support.
    //if( strncmp(prompt,"callback",8) == 0 )
    //{
    //    printf("~callback\n");
    //    sc82(44000,&callback1,&callback1,&callback1);
    //    printf("~done\n");
    //    goto exit_cmp;
    //}


    if( strncmp(prompt,"t1",2) == 0 )
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

    if( strncmp(prompt,"cls",3) == 0 )
    {
        do_clear_console();
        goto exit_cmp;
    }

    if( strncmp(prompt,"int3",4) == 0 )
    {
        do_int3();
        goto exit_cmp;
    }

    if( strncmp(prompt,"cli",3) == 0 )
    {
        do_cli();
        goto exit_cmp;
    }

    if( strncmp(prompt,"sti",3) == 0 )
    {
        do_sti();
        goto exit_cmp;
    }

    // gp fault
    if( strncmp(prompt,"hlt",3) == 0 )
    {
        do_hlt();
        goto exit_cmp;
    }

    if( strncmp(prompt,"quit",4) == 0 )
    {
        isTimeToQuit=TRUE;
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

//==============================
// Window Server:
    if( strncmp(prompt,"ws",2) == 0 )
    {
        //printf ("~WS\n");
        //rtl_clone_and_execute("gwssrv.bin");
        goto exit_cmp;
    }
    if( strncmp(prompt,"wsq",3) == 0 )
    {
        printf ("~WSQ\n");
        ret_val = (int) rtl_clone_and_execute(app1_name);
        if (ret_val<=0){
            printf("Couldn't clone\n");
        }
        //printf("pid=%d\n",ret_val);
        isTimeToQuit = TRUE;
        goto exit_cmp;
    }

//==============================
// Network Server:
    if( strncmp(prompt,"ns",2) == 0 )
    {
        //printf ("~NS\n");
        //rtl_clone_and_execute("gnssrv.bin");
        goto exit_cmp;
    }
    if( strncmp(prompt,"nsq",3) == 0 )
    {
        printf ("~NSQ\n");
        rtl_clone_and_execute(app3_name);
        isTimeToQuit = TRUE;
        goto exit_cmp;
    }


// #todo
// Something is not working fine
// when we put the name directly in the parameters field.
// We need a pointer instead.
    if( strncmp(prompt,"demo1",5) == 0 )
    {
        printf ("~ Demo 1:\n");
        rtl_clone_and_execute("demo1.bin");
        isTimeToQuit = TRUE;
        goto exit_cmp;
    }

// #todo
// Something is not working fine
// when we put the name directly in the parameters field.
// We need a pointer instead.
    if( strncmp(prompt,"demo2",5) == 0 )
    {
        printf ("~ Demo 2:\n");
        rtl_clone_and_execute("demo2.bin");
        isTimeToQuit = TRUE;
        goto exit_cmp;
    }

//-------

// #todo
// Something is not working fine
// when we put the name directly in the parameters field.
// We need a pointer instead.
    if( strncmp(prompt,"demo3",5) == 0 )
    {
        printf ("~ Demo 3:\n");
        rtl_clone_and_execute("demo3.bin");
        isTimeToQuit = TRUE;
        goto exit_cmp;
    }

// #todo
// Something is not working fine
// when we put the name directly in the parameters field.
// We need a pointer instead.
    if( strncmp(prompt,"demo4",5) == 0 )
    {
        printf ("~ Demo 4:\n");
        rtl_clone_and_execute("demo4.bin");
        isTimeToQuit = TRUE;
        goto exit_cmp;
    }

// Gramado game engine
    if( strncmp(prompt,"demo5",5) == 0 )
    {
        printf ("~ Demo 5:\n");
        rtl_clone_and_execute("demo5.bin");
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



static int __server_loop(void)
{

// #todo
// Get the id of the caller.
// Get the message code.
// Who can call us?

    while (TRUE)
    {

        //if( isTimeToQuit == TRUE )
            //break;
        
        if ( rtl_get_event() == TRUE )
        {
            // save
            __Caller = (int) ( RTLEventBuffer[8] & 0xFFFF );

            __Procedure ( 
                (void*) RTLEventBuffer[0], 
                RTLEventBuffer[1], 
                RTLEventBuffer[2], 
                RTLEventBuffer[3] );
        }
    };

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


// Clear the console and set cursor position to 0,0.
    do_clear_console();

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
        if( C == __VK_RETURN ){
            __CompareString();
        }
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

//
// Server loop.
// 
    int ServerLoopStatus = -1;

    ServerLoopStatus = (int) __server_loop();


/*
    while (TRUE){
        //if( isTimeToQuit == TRUE )
            //break;
        if ( rtl_get_event() == TRUE )
        {
            //if( RTLEventBuffer[1] == MSG_QUIT ){ break; }
            __Procedure ( 
                (void*) RTLEventBuffer[0], 
                RTLEventBuffer[1], 
                RTLEventBuffer[2], 
                RTLEventBuffer[3] );
        }
    };
*/

// hang
    while (TRUE){
        rtl_yield();
    };

    return 0;
}

