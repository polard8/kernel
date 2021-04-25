// main.c 
// app launcher
// Environment: setup.


#include "launcher.h"


#define GRID_HORIZONTAL  1000
#define GRID_VERTICAL    2000


//static int running = 1;
int running = 1;


// Windows and buttons.

struct window_d *main_window;

struct window_d *gWindow;          // grid 
struct window_d *mWindow;          // menu
struct window_d *reboot_button;    // reboot button;

struct window_d *launcher_button_1;
struct window_d *launcher_button_2;
struct window_d *launcher_button_3;   //para testes



//static char *dest_argv[] = { "-sujo0","-sujo1","-sujo2",NULL };
//static unsigned char *dest_envp[] = { "-sujo", NULL };
//static unsigned char dest_msg[512];

 

int 
launcherProcedure ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );



// Window procedure.
int 
launcherProcedure ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{

    if(msg<0)
        return -1;

    switch (msg){

		// A janela principal é uma overlapped,
		// então colocou uma mensagem na fila,
		// e o app vai pegar quando entrar no loop.
        //case MSG_CREATE: 
            //printf ("MSG_CREATE:\n");
            //debug_print ("MSG_CREATE:\n"); 
            //break;

        case MSG_SYSKEYDOWN:
            //...
            switch (long1)
            {  
                case VK_F1:
                    debug_print("F1\n");
                    gde_clone_and_execute("gdeshell.bin");
                    exit(0);
                    break;

                case VK_F2: 
                    debug_print("F2\n");
                    gde_clone_and_execute("gramcode.bin");
                    exit(0);
                    break;
                    
                case VK_F3: 
                    debug_print("F3\n");
                    gde_clone_and_execute("sysmon.bin");
                    exit(0);
                    break;
                
                case VK_F4:
                    // switch the foreground thread.
                    gramado_system_call (301,0,0,0);
                    break;
            };
            goto done;
            break;


        // MSG_MOUSEKEYDOWN
        case 30:
            switch (long1)
            {
                //botão 1.
                case 1:
                    if ( window == launcher_button_1 || 
                         window == launcher_button_2 || 
                         window == launcher_button_3 )
                    {
                        gramado_system_call ( 9900,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
                            break;
                    }

                    if ( window == reboot_button )
                    {
                        gde_reboot ();
                        break;
                    }

                    if ( window == gWindow ){ 
                        printf("grid window\n");
                    }

                    if ( window == mWindow ){
                        printf("menu window\n");
                    }

                    if ( window == main_window )
                    {
                         //raise window.
	                     //system_call ( 9700, 
	                        // (unsigned long) window, 
		                     //(unsigned long) window, 
		                     //(unsigned long) window );
		                 break;
                    }

                    break;
            };
            goto done;
            break;

        //mouse key up
        case 31:
            switch (long1)
            {
                case 1:
                    if (window == main_window)
                    {
                        gde_set_focus (window);
                        gde_redraw_window (window,1);
                        break;
                    }

                    if ( window == launcher_button_1 )
                    {
                        gramado_system_call ( 9901, 
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
                       
                        gde_clone_and_execute("gdeshell.bin");
                        exit(0);
                        break;
                    }
                    if ( window == launcher_button_2 )
                    {
                        gramado_system_call ( 9901,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );

                        gde_clone_and_execute("gramcode.bin");
                        exit(0);
                        break;
                    }
                    if ( window == launcher_button_3 )
                    {
                        gramado_system_call ( 9901,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
                        
                        gde_clone_and_execute("sysmon.bin");
                        exit(0);
                        break;
                    }
                    break;
            };
            goto done;
            break;

        case MSG_SETFOCUS:
            gde_redraw_window (main_window, 1);
            gde_redraw_window (launcher_button_1, 1);
            gde_redraw_window (launcher_button_2, 1);
            gde_redraw_window (launcher_button_3, 1);
            break;

        //case MSG_KILLFOCUS:
            //gde_message_box (3,"launcher","MSG_KILLFOCUS");
            //break;

        //PARA MOSTRAR A ÁREA DE CLIENTE.
        case MSG_PAINT:
            gde_redraw_window (launcher_button_1, 1);
            gde_redraw_window (launcher_button_2, 1);
            gde_redraw_window (launcher_button_3, 1);
            break;

        case MSG_CLOSE:
            gde_message_box (3,"launcher","MSG_CLOSE");
            gde_close_window (main_window );
            gde_exit(0);
            break;

        // #test
        // update
        // Enviado pelo kernel quando a thread volta a ter o input.
        case 11216:
            gde_redraw_window (main_window,TRUE);
            gde_redraw_window (launcher_button_1, 1);
            gde_redraw_window (launcher_button_2, 1);
            gde_redraw_window (launcher_button_3, 1);
            break;

        default:
            debug_print("launcher: default message\n");
            break;
    };

done:
    return (int) gde_system_procedure (window,msg,long1,long2);
}


/*
 ********************************************
 * main:
 */

int main ( int argc, char *argv[] )
{
    struct window_d *hWindow;

    FILE *fp;

    int char_count = 0;

    unsigned long left=0;
    unsigned long top=0;
    unsigned long width=0;
    unsigned long height=0;

    unsigned long deviceWidth  = gde_get_system_metrics(1);
    unsigned long deviceHeight = gde_get_system_metrics(2);


    if ( deviceWidth == 0 || deviceHeight == 0 )
    {
        printf("launcher: [FAIL] device info\n");
        exit(1);
    }

    left   = 2;
    top    = 2;
    width  = (deviceWidth  >> 2);
    height = (deviceHeight >> 1);

    // #hackhack

    if ( deviceWidth == 320 && deviceHeight == 200 )
    {
        width  = (deviceWidth  -4);
        height = (deviceHeight -4);
    }

	// #remember: Colors
	// green crocodile = 0x44541C 
	// orange royal    = 0xF9812A
	// window          = 0xF5DEB3
	// client window   = 0x2d89ef 


    //
    // main window
    //

    //++
    gde_begin_paint();
    hWindow = (void *) gde_create_window ( 
                           WT_OVERLAPPED, 1, 1, "Launcher",
                           left, top, width, height,  
                           0, 0, COLOR_BLUE2CYAN, COLOR_BLUE2CYAN ); 

    if ( (void *) hWindow == NULL )
    {
        printf ("launcher: hWindow fail\n");
        gde_end_paint();
        goto fail;
    }else{
        //Registrar e mostrar.
        gde_register_window  (hWindow);
        gde_show_window (hWindow);
        
        //global, pra acessar via procedimento de janela.
        main_window = ( struct window_d *) hWindow;
    };
    gde_end_paint();
    //--


    gde_draw_text ( main_window, 8, 8, COLOR_WHITE, "Gramado OS 1.0" );


    // =========
    // button 1
    //++
    gde_enter_critical_section ();
    launcher_button_1 = (void *) gde_create_window ( 
                                     WT_BUTTON, 1, 1, "[F1] gdeshell",  
                                     2, (height/8)*4, (width -4), (height/8), 
                                     hWindow, 0, xCOLOR_GRAY3, xCOLOR_GRAY3 );

    if ( (void *) launcher_button_1 == NULL )
    {
        printf ("Couldn't create button 1\n");
        gde_exit_critical_section (); 
        goto fail;
    }else{
        gde_register_window (launcher_button_1);
        gde_show_window (launcher_button_1);
        gde_show_backbuffer ();
    };
    gde_exit_critical_section ();
    //--

    // =========
    // button 2
    //++
    gde_enter_critical_section (); 
    launcher_button_2 = (void *) gde_create_window ( 
                                     WT_BUTTON, 1, 1, "[F2] gramcode", 
                                     2, (height/8)*5, (width -4), (height/8),
                                     hWindow, 0, 
                                     xCOLOR_GRAY3, xCOLOR_GRAY3 );

    if ( (void *) launcher_button_2 == NULL )
    {
        printf ("Couldn't create button 2\n");
        gde_exit_critical_section (); 
        goto fail;
    }else{
        gde_register_window (launcher_button_2);
        gde_show_window (launcher_button_2);
        gde_show_backbuffer ();
    };
    gde_exit_critical_section (); 
    //--

    // =========
    // button 3
    //++
    gde_enter_critical_section (); 
    launcher_button_3 = (void *) gde_create_window ( 
                                     WT_BUTTON, 1, 1, "[F3] sysmon", 
                                     2, (height/8)*6, (width -4), (height/8),
                                     hWindow, 0, 
                                     xCOLOR_GRAY3, xCOLOR_GRAY3 );

    if ( (void *) launcher_button_3 == NULL )
    {
        printf ("Couldn't create button 3\n");
        gde_exit_critical_section (); 
        goto fail;
    }else{

        gde_register_window (launcher_button_3);
        gde_show_window (launcher_button_3);
        gde_show_backbuffer ();
    };
    gde_exit_critical_section (); 
    //--


    //

    gde_set_focus(hWindow);

    gde_set_active_window(hWindow);
        
    gde_show_window (hWindow);

    // #bugbug
    // Is it working ?
    gde_show_backbuffer();


	//
	// == Loop ============================
	//

    // #todo
    // #bugbug
    // Maybe we need to setup this thread as
    // a foreground thread.


    unsigned long message_buffer[5];

Mainloop:

    while (running){

        gde_enter_critical_section ();
        system_call ( 111,
            (unsigned long) &message_buffer[0],
            (unsigned long) &message_buffer[0],
            (unsigned long) &message_buffer[0] );
        gde_exit_critical_section (); 

        // msg
        if ( message_buffer[1] != 0 )
        {
            launcherProcedure ( (struct window_d *) message_buffer[0], 
                (int) message_buffer[1], 
                (unsigned long) message_buffer[2], 
                (unsigned long) message_buffer[3] );

            message_buffer[0] = 0;
            message_buffer[1] = 0;
            message_buffer[2] = 0;
            message_buffer[3] = 0;
        };
    };


fail:
    printf ("fail.\n");
    // exit(1);

done:
    //running = 0;
    return 0;
}



