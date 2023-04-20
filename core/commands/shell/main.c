
// shell.bin

// rtl
#include <types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <rtl/gramado.h>

#include "shell.h"


//================

//
// VGA TEST
//

// libio
//#include <libio.h>
#include "vga_test.h"
//================



#define MSG_KEYDOWN       20
#define MSG_KEYUP         21
#define MSG_SYSKEYDOWN    22
#define MSG_SYSKEYUP      23

#define VK_F1    0x3B  //59    // No DOS é 0x170.  
#define VK_F2    0x3C  //60 
#define VK_F3    0x3D  //61 
#define VK_F4    0x3E  //62 


#define VK_RETURN    0x1C
#define VK_TAB       0x0F

#define COLOR_BLACK    0x000000
#define COLOR_GRAY     0x808080 

unsigned long device_width;
unsigned long device_height;


//======================================
// Calling kgws in ring0.
// Using the kgws to refresh the rectangle.
void 
__shell_refresh_rectangle ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height )
{
    unsigned long Buffer[5];
    
    Buffer[0] = (unsigned long) x;
    Buffer[1] = (unsigned long) y;
    Buffer[2] = (unsigned long) width;
    Buffer[3] = (unsigned long) height;

    gramado_system_call ( 
        10, 
        (unsigned long) &Buffer[0], 
        0, 
        0 );
}


void 
__shell_draw_rectangle ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height,
    int color )
{
    unsigned long Buffer[5];
    
    Buffer[0] = (unsigned long) x;
    Buffer[1] = (unsigned long) y;
    Buffer[2] = (unsigned long) width;
    Buffer[3] = (unsigned long) height;
    Buffer[4] = (unsigned long) (color & 0xFFFFFF);

    gramado_system_call ( 
        391, 
        (unsigned long) &Buffer[0], 
        (unsigned long) &Buffer[0], 
        0 );
}



/*
 * shellPrompt:
 *     Inicializa o prompt.
 *     Na inicializa��o de stdio, 
 *    prompt foi definido como stdin->_base.
 */

void shellPrompt (void)
{
    int i=0;

    // Clean prompt buffer.
    
    for ( i=0; i<PROMPT_MAX_DEFAULT; i++ ){ prompt[i] = (char) '\0'; };
    
    prompt[0] = (char) '\0';
    prompt_pos    = 0;
    prompt_status = 0;
    prompt_max    = PROMPT_MAX_DEFAULT;  

    // Prompt
    //printf("\n");
    putc('$',stdout);
    putc(' ',stdout);
    fflush(stdout);
}


// local
unsigned long shellCompare (void)
{
    unsigned long ret_value=0;
    char *c;

// The first char.
// $(NULL)
// [ENTER] finalizou a atring antes de ter digitado alguma coisa.
// Se alguem pressiona [ENTER] com prompt vazio d� page fault ?
// Isso cancela caso o buffer esteja vazio.

    c = prompt;

    if ( *c == '\0' )
    {
        //shellInsertLF();
        goto exit_cmp;
    }

//
// Compare
//


// Compare strings.
// Let's start at the next line.

do_compare:

    //shellInsertLF();
    printf("\n");


    // cls
    if ( strncmp(prompt,"cls",3) == 0 )
    {
        // suspenso
        //shell_clear_screen();
        
         /*
        //shell_clear_screen();
        //while(1){}
        

        // Draw surface
        debug_print("1\n");
        __shell_draw_rectangle( 0, 0,
            device_width >> 1,  device_height >> 1,  COLOR_GRAY );

        // refresh surface
        debug_print("2\n");
        __shell_refresh_rectangle( 0, 0,
            device_width >> 1,  device_height >> 1 );

        // Reset cursor
        debug_print("3\n");
        gramado_system_call( 34, 0, 4, 0 );

        debug_print("4\n");
        shellPrompt();
        */
        
        goto exit_cmp;
    }
 

    // about
    if ( strncmp ( prompt, "about", 5 ) == 0 )
    {
        printf ("Gramado Operating System");
        fflush(stdout);
        goto exit_cmp;
    }

    // getpid
    int my_pid=0;
    if ( strncmp( prompt, "getpid", 6 ) == 0 )
    {
        my_pid=getpid();
        printf ("pid: %d\n",my_pid);
        goto exit_cmp;
    }

    // getppid
    int my_ppid=0;
    if ( strncmp( prompt, "getppid", 7 ) == 0 )
    {
        my_ppid=getppid();
        printf ("ppid: %d\n",my_ppid);
        goto exit_cmp;
    }

    // mm-size (MB)
    unsigned long __mm_size_mb = 0;    
    if ( strncmp( prompt, "mm-size", 7 ) == 0 )
    {
        __mm_size_mb = (unsigned long) gramado_system_call (292,0,0,0);
        printf ("Memory size = %d MB \n",__mm_size_mb);
        goto exit_cmp;
    }

    // current-process
    if ( strncmp ( prompt, "current-process", 15 ) == 0 )
    {
        printf("\n");
        //gramado_system_call ( SYSTEMCALL_CURRENTPROCESSINFO, 0, 0, 0 );
        gramado_system_call ( 80, 0, 0, 0 );
        goto exit_cmp; 
    }


    // process-info
    if ( strncmp ( prompt, "process-info", 12 ) == 0 )
    {
        printf("\n");
        gramado_system_call ( 82, 0, 0, 0 );
        goto exit_cmp; 
    }


    if ( strncmp( prompt, "exit", 4 ) == 0 )
    {
        exit(0);
        goto exit_cmp;
    }


    // malloc
    void *hBuffer;
    if ( strncmp( prompt, "malloc", 6 ) == 0 )
    {
        printf ("Testing heap: 32kb\n");
        hBuffer = (void *) malloc ( 1024*32 );        // 32 kb
        //...
        if ( (void *) hBuffer == NULL ){
            printf("Fail\n");
        }else{
            printf("OK\n");
        };
        printf("done\n");
        goto exit_cmp;
    }

    // sync - salva os buffers em ring0 no disco fisico.
    // Isso pode ser um programa.
    // See: unistd.c
    if ( strncmp( prompt, "sync", 4 ) == 0 )
    {
        //printf ("sync: \n");
        sync();
        goto exit_cmp;
    }


    
    // tty3
    if ( strncmp ( prompt, "tty3", 4 ) == 0 )
    {
        //if ( isatty(fileno(stdin)) == 0 ){
        //    printf ("stdin is not a tty\n");
        //}
        //if ( isatty(fileno(stdout)) == 0 ){
        //    printf ("stdout is not a tty\n");
        //}
        //if ( isatty(fileno(stderr)) == 0 ){
        //    printf ("stderr is not a tty\n");
        //}
        goto exit_cmp;
    }
    



launch_app:

    //rtl_clone_and_execute(prompt);

    printf ("Command not found\n");

exit_cmp:
    ret_value = 0;
done:
    shellPrompt();
    return (unsigned long) ret_value;
}



int 
shellProcedure ( 
    void *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{

    if(msg<0)
        return -1;

    switch (msg)
    {
        // 20 = MSG_KEYDOWN
        case MSG_KEYDOWN:
            switch (long1)
            {

                // [Enter] - Finalize the command line and compare.
                case VK_RETURN:
                    input('\0');
                    shellCompare();
                    //asm("int $3");
                    goto done;
                    break; 

                case VK_TAB: 
                    printf("\t");
                    goto done; 
                    break;

                // keyboard arrows
                case 0x48: printf ("UP   \n"); goto done; break;
                case 0x4B: printf ("LEFT \n"); goto done; break;
                case 0x4D: printf ("RIGHT\n"); goto done; break;
                case 0x50: printf ("DOWN \n"); goto done; break;


                case 0x47: 
                    printf ("HOME\n");
                    goto done; 
                    break;
                    
                case 0x4F: 
                    printf ("END \n"); 
                    goto done; 
                    break;

                //pageup pagedown
                case 0x49: printf ("PAGEUP   \n"); goto done; break;
                case 0x51: printf ("PAGEDOWN \n"); goto done; break;

                // insert delete
                case 0x52: printf ("INSERT\n"); goto done; break;
                case 0x53: printf ("DELETE\n"); goto done; break;

                default:
                    input ( (unsigned long) long1 );  
                    printf("%c",long1); fflush(stdout);
                    break;
            };
            break;

  // 22 = MSG_SYSKEYDOWN
        case MSG_SYSKEYDOWN:
            switch (long1)
            {
                case VK_F1: printf ("F1\n");  break;
                case VK_F2: printf ("F2\n");  break;
            };
            break;
    };


done:
    return 0;
}


void shell_clear_screen(void)
{

//loop:

// Draw surface
    debug_print("1\n");
    __shell_draw_rectangle(
        0,
        0,
        (unsigned long) (device_width >> 1),
        (unsigned long) (device_height >> 1),
        COLOR_GRAY);

// refresh surface
    debug_print("2\n");
    __shell_refresh_rectangle(
        0,
        0,
        (unsigned long) (device_width >> 1),
        (unsigned long) (device_height >> 1) );

// Reset cursor
    debug_print("3\n");
    gramado_system_call(
        34,
        0,   // x
        4,   // y
        0);

    debug_print("4\n");
    
    //goto loop;
    
    return;
}


//backup
int main_backup ( int argc, char *argv[] )
{

    //argc=0;
    //argv=NULL;
    
    debug_print ("SHELL.BIN\n");

    device_width  = rtl_get_system_metrics(1);
    device_height = rtl_get_system_metrics(2);


    //shell_clear_screen();

    /*
    // draw surface.
    __shell_draw_rectangle(
        0,
        0,
        device_width,
        device_height,
        COLOR_GREEN );
    */

    /*
    // cursor
    gramado_system_call( 
        34,
        0,
        4,
        0);
    */

    printf ("SHELL.BIN: Gramado OS\n");
    shellPrompt();


// #test
// changing vga resolution.
// IN: only 320x200x256
    //printf ("Calling VGA_init\n");
    //VGA_init(320,200,256);

// #bugbug
// Clear the screen.
    //gramado_system_call(390,0,0,0);

//
// Message loop
//

// =================================
// Getting input event with the control thread.
// #todo: First we need to set the focus on this thread.

// Podemos chamar mais de um diálogo
// Retorna TRUE quando o diálogo chamado 
// consumiu o evento passado à ele.
// Nesse caso chamados 'continue;'
// Caso contrário podemos chamar outros diálogos.


    rtl_focus_on_this_thread();
    while (1){
        if ( rtl_get_event() == TRUE ){
            shellProcedure ( 
                (void*) RTLEventBuffer[0], 
                RTLEventBuffer[1], 
                RTLEventBuffer[2], 
                RTLEventBuffer[3] );
        }
    };

//=================================

    //#debug
    //asm ("int $3");

    while(1){};
    
    return 0;
}


//
// Main
//

int main ( int argc, char *argv[] )
{
    register int i=0;
    int C=0;

// -----------------------------------
// (>>> stdout)
// Still using the kernel console.

    printf("shell.bin: argc={%d} ",argc);
    fflush(stdout);
    if (argc>0)
    {
        for (i=0; i<argc; i++){
            printf("argv[%d]: %s\n", i, argv[i] );
        };
    }

// -----------------------------------
// (>>> stderr)
// Now we have a new stdout.
// Now we're gonna send the data to the terminal.bin
// that is reading stderr.

    stdout = stderr;

// Send a simple string.
    printf("SHELL.BIN: Shell is alive!$ ");
    fflush(stdout);

// ------------------------------------------------
// Loop: (Input events).
// Reading from stdin and sending to our new stdout.
// stderr.

    while (1){

        // #bugbug
        // We got a PF when we type a lot of keys.
        // And sometimes when we type Enter.

        C = fgetc(stdin);
        // Como estamos usando um arquivo regular,
        // entao o kernel concatena ate chegar no fim do arquivo.
        if (C == EOF){
            //rewind(stdin);
            //exit(0);
        }

        // Valid char.
        if (C>0)
        {
            // [ Enter ]
            if (C == VK_RETURN)
            {
                //printf("%c",'$');
                //fflush(stdout);
 
                // #bugbug #todo: Compare the string.
                //shellCompare();
            }

            // Printable chars.
            if (C >= 0x20 && C <= 0x7F)
            {

                // Feed the command line in 'prompt', i guess.
                input(C);

                // #debug
                // O terminal vai imprimir errado.
                // ok funcionou.
                //printf("%c", (C+1) ); 
      
                printf("%c",C);
                fflush(stdout);
                 
                // + precisamos nos certificar que eh o shell
                // que esta enviando chars para o terminal
                // e nao o kernel
                // + precisamos nos certivicar que o shell esta lendo de um arquivo.
                // isso eh uma tentativa
                if (C == 'q')
                {
                    //printf("%c",'9');
                    //fflush(stdout);
                    exit(0);   //#test
                }
             }
        }
    };

    while (1){
    };

    return 0;
}


