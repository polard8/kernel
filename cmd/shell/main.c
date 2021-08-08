
// rtl
#include <types.h>
#include <stdio.h>

#include <rtl/gramado.h>


#include "shell.h"


#define MSG_KEYDOWN       20
#define MSG_KEYUP         21
#define MSG_SYSKEYDOWN    22
#define MSG_SYSKEYUP      23

#define VK_F1    0x3B  //59    // No DOS é 0x170.  
#define VK_F2    0x3C  //60 
#define VK_F3    0x3D  //61 
#define VK_F4    0x3E  //62 


#define VK_RETURN      0x1C
#define VK_TAB       0x0F


/*
 **************************************************
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
    printf("\n");
    putc('$',stdout);
    putc(' ',stdout);
    fflush(stdout);
}


// local
unsigned long shellCompare (void)
{
    unsigned long ret_value=0;
    char *c;


//
// The first char.
//

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


    if ( strncmp ( prompt, "about", 5 ) == 0 )
    {
        printf ("Gramado Operating System\n");
        goto exit_cmp;
    }

    printf ("Command not found\n");

exit_cmp:
    ret_value = 0;
done:
    shellPrompt();
    return (unsigned long) ret_value;
}


// local
int 
shellProcedure ( 
    void *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{

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



int main ( int argc, char *argv[] )
{

    debug_print ("------------------------------\n");
    debug_print ("shell.bin\n");


   printf ("Shell: $");
   fflush(stdout);

//
// Message loop
//

//=================================

    rtl_focus_on_this_thread();

    while (1){

        if ( rtl_get_event() == TRUE )
        {  
            // Podemos chamar mais de um diálogo
            // Retorna TRUE quando o diálogo chamado 
            // consumiu o evento passado à ele.
            // Nesse caso chamados 'continue;'
            // Caso contrário podemos chamar outros diálogos.

            shellProcedure ( 
                (void*) RTLEventBuffer[0], 
                RTLEventBuffer[1], 
                RTLEventBuffer[2], 
                RTLEventBuffer[3] );
        }
    };
//=================================



    asm ("int $3");
    return 0;
}


