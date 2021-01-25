// main.c 
// sysmon - System monitor using kgws.
// Environment: Setup.


// #bugbug
// Adicionar bibliotecas causou problemas. 

#include "sysmon.h"



#define GRID_HORIZONTAL    1000
#define GRID_VERTICAL      2000


//static int running = 1;
int running = 1;


// Windows.
struct window_d  *main_window;
struct window_d  *client_window;
struct window_d  *client_bar_Window;
struct window_d  *data_window;         // White.
// ...

// bar buttons
struct window_d *bar_button_1; 
struct window_d *bar_button_2; 
// ...


//
// == CPU usage ===============================================
//

struct window_d *cpu_window;   // Window.
unsigned long CPU_USAGE[32];
int __count;



 
/*
 ************************** 
 * sysmonProcedure:
 * 
 */

int 
sysmonProcedure ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );



// Interna.
// Usado para testar o timer.
void update_cpu_usage (void)
{
    unsigned long __idle_value=0;
    unsigned long __value=0;
    int i=0;



    __count++;
    //printf ("%d ",__count);

    __idle_value = (unsigned long) gramado_system_call ( 777, 0, 0, 0);

	//__value = (100 - __idle_value);
	//CPU_USAGE[__count] = __value;
    CPU_USAGE[__count] = __idle_value;


    if (__count >= 32)
    {
        __count = 0;

		//limpa
		gde_redraw_window ( cpu_window, 1 );
        //for (i=0; i<32; i++)
        for (i=1; i<32; i++)
        {
			//printf ("%d ", (unsigned long) CPU_USAGE[i]);
            gde_draw_text( 
                cpu_window, 
                (i*8), 
                CPU_USAGE[i], 
                COLOR_BLACK, "+");
        };
        gde_show_window (cpu_window);
    }

	//printf ("fim\n");
    //printf ("cpu usage: %d percent \n", __value);
}

void test_cpu (struct window_d *window)
{
    debug_print("test_cpu:");

    unsigned long deviceWidth  = gde_get_system_metrics(1); 
    unsigned long deviceHeight = gde_get_system_metrics(2);


    // validade da janela mae.
    if ( (void*) window == NULL )
    {
        debug_print("test_cpu: window\n");
             printf("test_cpu: window\n");
        return;
    }

    // a janela mae tem que ser a janela da barra.
    if( window != client_bar_Window)
    {
        debug_print("test_cpu: [FAIL] window\n");
             printf("test_cpu: [FAIL] window\n");
        return;
    }


//====================================
// # timer-test
//
// Essa rotina cria um objeto timer que gera um interrupção 
// de tempos em tempos e é tratado pelo procedimento de janelas.

    __count = 0;    //Tem que inicializar;

    //printf("Creating timer\n");
    //printf("%d Hz | sys time %d ms | ticks %d \n", 
    //apiGetSysTimeInfo(1), 
    //apiGetSysTimeInfo(2), 
    //apiGetSysTimeInfo(3) );

    //++
    gde_enter_critical_section ();
    // deixamos espaço para dois botoes. f1 e f2
    cpu_window = (void *) gde_create_window ( 1, 1, 1, 
                              "cpu-usage",  
                               40+4, 2, (32*8), 40-4, 
                               window, 0, COLOR_YELLOW, COLOR_YELLOW );
    gde_register_window (cpu_window);
    gde_show_window (cpu_window);
    gde_exit_critical_section ();
    //--


    // Atualizar à cada 2000 ms. 
    //janela, 100 ms, tipo 2= intermitente.
    //system_call ( 222, (unsigned long) window, 100, 2);

    gde_create_timer ( 
        getpid(), 
        (unsigned long) 50, 
        (int) 2 );
        
    //printf ("done\n");

//====================================
}




// internal
// #todo: ordenar por pid
void showinfo_button1(void)
{

    char __pid_buffer[8];
    char __processname_buffer[64];
    char __priority_buffer[8];
    char __state_buffer[8];
    //...

    int i=0;
    int name_len = 0;
    unsigned long __process_priority=0;
    unsigned long __state=0;

 
  
    //#todo
    //Criar um for para mostrar vários processos.
  
    //unsigned long x = 0;
    unsigned long y = 32;
  
    // Labels
    gde_draw_text ( data_window,    4, 8, COLOR_BLACK, "PID" );
    gde_draw_text ( data_window,   40, 8, COLOR_BLACK, "Name" );
    gde_draw_text ( data_window,  180, 8, COLOR_BLACK, "Prio" );     
    gde_draw_text ( data_window,  220, 8, COLOR_BLACK, "State" );     
    //...
        
    //for ( i=100; i<104; i++ )
    for ( i=100; i<110; i++ )
    {
        // get process name.
        name_len = gde_getprocessname  ( i,  
                       __processname_buffer, 
                       sizeof(__processname_buffer) );
        
        if (name_len>0)
        {
            //Get PID string
            itoa(i, __pid_buffer); 
            
            // get process priority
            __process_priority = gde_get_process_stats (i,33);  
            itoa(__process_priority, __priority_buffer);

            // get process state
            __state = gde_get_process_stats (i,5);  
            itoa(__state, __state_buffer);

            //...
        
            gde_draw_text ( data_window,   4, y, 
                COLOR_BLACK, (char *) __pid_buffer );
            gde_draw_text ( data_window,  40, y, 
                COLOR_BLACK, (char *) __processname_buffer );
            gde_draw_text ( data_window, 180, y, 
                COLOR_BLACK, (char *) __priority_buffer ); 
            gde_draw_text ( data_window, 220, y, 
                COLOR_BLACK, (char *) __state_buffer );      
            //...
    
            //update y
            y = (y+10);
         }
    };


    // refresh screen
    gde_show_backbuffer ();
}



/*
 * *********************************
 * sysmonProcedure:
 *     Window procedure.
 */

int 
sysmonProcedure ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{


    if ( msg<0 )
        return -1;

    switch (msg)
    {

        case MSG_SYSKEYDOWN:
            switch (long1)
            {  
                case VK_F1: 
                    debug_print("sysmon: [F1]"); 
                    showinfo_button1();
                    return 0;
                    break;

                case VK_F2: 
                    debug_print("sysmon: [F2]"); 
                    // IN: parent window.
                    test_cpu (client_bar_Window);
                    return 0;
                    break;

                case VK_F3: 
                    debug_print("sysmon: [F3]"); 
                    return 0;
                    break;

                case VK_F4: 
                    debug_print("sysmon: [F4]"); 
                    // IN: parent window.
                    test_cpu (client_bar_Window);
                    return 0;
                    break;

            };
            goto done;
            break;


        case MSG_SYSKEYUP:  
            goto done;
            break;


        //case MSG_CREATE:  break;


        case MSG_TIMER:
            debug_print("sysmonProcedure: MSG_TIMER\n");
            update_cpu_usage ();
            return 0;
            break;


        case MSG_SETFOCUS:
            gde_redraw_window (main_window, 1);
            gde_redraw_window (main_window, 1);
            gde_redraw_window (main_window, 1);
            gde_redraw_window (main_window, 1);
            gde_redraw_window (main_window, 1);
            gde_redraw_window (main_window, 1);
            break;
        
        
        case MSG_KILLFOCUS:  
            break;


        // MSG_MOUSEKEYDOWN
        // case 30:  break;


        // Mouse button up
        case 31:
            switch (long1)
            {
                // button 1
                case 1:
                    if (window == main_window)
                    {
                        gde_set_focus (window);
                        gde_redraw_window (window,1);
                        // #todo: we need to redraw all other windows.
                        return 0;
                    }

                    if ( window == bar_button_1 )
                    {
                        gde_redraw_window (data_window,1);
                        gramado_system_call ( 9901,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window ); 
                        showinfo_button1();
                        return 0;
                        break;
                    }

                    if ( window == bar_button_2 )
                    {
                        gde_redraw_window (data_window,1);
                        gramado_system_call ( 9901,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window ); 
                        test_cpu (client_bar_Window);
                        return 0;
                        break;
                    }

                    break;
                    
            };
            goto done;
            break;

        default:
            //debug_print ("sysmon: default message");
            break;
    };

done:
    return (int) gde_system_procedure (window, msg, long1, long2);
}


/*
 ********************************************
 * main:
 */

int main ( int argc, char *argv[] ){

    struct window_d *hWindow;
    FILE *fp;
    int ch=0;
    int char_count = 0;


    unsigned long deviceWidth  = gde_get_system_metrics(1);
    unsigned long deviceHeight = gde_get_system_metrics(2);

    //main window
    unsigned long left=0;
    unsigned long top=0;
    unsigned long width=0;
    unsigned long height=0;
    unsigned long color;

    //client window
    unsigned long cw_left=0;
    unsigned long cw_top=0;
    unsigned long cw_width=0;
    unsigned long cw_height=0;
    unsigned long cw_color;

    //client bar window
    unsigned long cbw_left=0;
    unsigned long cbw_top=0;
    unsigned long cbw_width=0;
    unsigned long cbw_height=0;
    unsigned long cbw_color;

    //data window
    unsigned long dw_left=0;
    unsigned long dw_top=0;
    unsigned long dw_width=0;
    unsigned long dw_height=0;
    unsigned long dw_color;
    
    
    if ( deviceWidth == 0 || deviceHeight == 0 ){
        printf ("SYSMON.BIN: [FAIL] device metrics\n");
        exit(1);
    }
    

    // main window
    left = 0;
    top  = 0;  
    width  = deviceWidth;
    height = deviceHeight;
    color = COLOR_GRAY;

    // client window
    cw_left = 1;
    cw_top  = 1;  
    cw_width  = width -2;
    cw_height = height -2;
    cw_color = 0xF5DEB3;  //0xF5DEB3

    // client bar window
    // inside the client window
    cbw_left = 1;
    cbw_top  = 1;  
    cbw_width  = cw_width -2;
    cbw_height = 40;
    cbw_color = 0x404040;  //0x404040

    // data window
    // inside the client window
    dw_left = 1;
    dw_top  = cbw_height + 8;  
    dw_width  = cw_width -2;
    dw_height = cw_height - cbw_height - 8;
    dw_color = COLOR_WHITE;


//
// == Main window =================================================
//

    //++
    // The main window.
    gde_begin_paint (); 
    hWindow = (void *) gde_create_window (  
                           WT_OVERLAPPED, 1, 1, "SYSMON", 
                           left, top, width, height, 
                           0, 0, color, color );  

    if ( (void *) hWindow == NULL ){
        printf ("sysmon: hWindow fail\n");
        gde_end_paint ();
        goto fail;

    // Register and show.
    }else{
        gde_register_window (hWindow);
        gde_show_window (hWindow);
        main_window = ( struct window_d *) hWindow;
    };
    gde_end_paint ();
    //--

     // #debug
     // Text,
     //gde_draw_text ( main_window, 4, 4, 
     //    COLOR_WHITE, "sysmon.bin: System information." );
     //gde_show_window (main_window);
     //while(1){}


    //
    // == Client background =====================
    //

    //++
    // Client background.
    // Almost the same size of the main window.
    gde_enter_critical_section ();  
    client_window = (void *) gde_create_window ( 
                                 WT_SIMPLE, 1, 1, "client-bg",     
                                 cw_left, cw_top, cw_width, cw_height, 
                                 main_window, 0, 
                                 cw_color, cw_color); //0xF5DEB3, 0xF5DEB3 );

    if ( (void *) client_window == NULL)
    {
        printf ("client_window fail");
        gde_show_backbuffer();
        gde_exit_critical_section ();
        exit(1);
    }
    gde_register_window (client_window);
    gde_show_window (client_window);
    gde_exit_critical_section ();
    //--


    //
    // == Client bar ============================================
    //

    //++
    // Client bar.
    gde_enter_critical_section ();  
    client_bar_Window = (void *) gde_create_window ( WT_SIMPLE, 1, 1, 
                                    "client-bar",     
                                    cbw_left, cbw_top, cbw_width, cbw_height, 
                                    client_window, 0, 
                                    cbw_color, cbw_color );  //0x404040, 0x404040 );
    
    if ( (void *) client_bar_Window == NULL){
        printf ("client_bar_Window fail");
        gde_show_backbuffer();
        gde_exit_critical_section (); 
        while(1){}
    }
    gde_register_window (client_bar_Window);
    gde_show_window (client_bar_Window);
    gde_exit_critical_section ();  
    //--


    //
    // ============ Bar buttons =========
    //

    //++
    //bar button [ F1 ]
    gde_enter_critical_section (); 
    bar_button_1 = (void *) gde_create_window ( WT_BUTTON, 1, 1, 
                                "F1",  
                                1, 1, 20, 40-4,    
                                client_bar_Window, 0, 
                                xCOLOR_GRAY3, xCOLOR_GRAY3 );

    if ( (void *) bar_button_1 == NULL ){
        printf ("Couldn't create PID button\n");
        gde_exit_critical_section ();
        return 1;

    }else{
        gde_register_window (bar_button_1);
        gde_show_window (bar_button_1);
        gde_show_backbuffer ();
    };
    gde_exit_critical_section (); 
    //--


    //++
    //bar button [ F2 ]
    gde_enter_critical_section (); 
    bar_button_2 = (void *) gde_create_window ( WT_BUTTON, 1, 1, 
                                "F2",
                                20+2, 1, 20, 40-4,    
                                client_bar_Window, 0, 
                                xCOLOR_GRAY3, xCOLOR_GRAY3 );

    if ( (void *) bar_button_2 == NULL ){
        printf ("Couldn't create PID button\n");
        gde_exit_critical_section ();
        return 1;

    }else{
        gde_register_window (bar_button_2);
        gde_show_window (bar_button_2);
        gde_show_backbuffer ();
    };
    gde_exit_critical_section (); 
    //--



    //
    // == Data window ===================
    //

    // White window to show the data.

    //++
    // White window.
    gde_enter_critical_section ();  
    data_window = (void *) gde_create_window ( WT_SIMPLE, 1, 1, 
                               "DataWindow",     
                                dw_left, dw_top, dw_width, dw_height,  
                                client_window, 0, 
                                dw_color, dw_color );

    if ( (void *) data_window == NULL){
        printf ("DataWindow fail");
        gde_show_backbuffer();
        gde_exit_critical_section ();
        while(1){}
 
    }
    gde_register_window (data_window);
    gde_show_window (data_window);
    gde_exit_critical_section ();  
    //--



    gde_set_focus(hWindow);

	//
	// == Loop ===================
	//

    unsigned long message_buffer[5];

Mainloop:

    while (running){

        gde_enter_critical_section (); 
        system_call ( 111,
            (unsigned long) &message_buffer[0],
            (unsigned long) &message_buffer[0],
            (unsigned long) &message_buffer[0] );
        gde_exit_critical_section (); 


        if ( message_buffer[1] != 0 )
        {
            sysmonProcedure ( 
                (struct window_d *) message_buffer[0], 
                (int)               message_buffer[1], 
                (unsigned long)     message_buffer[2], 
                (unsigned long)     message_buffer[3] );

            message_buffer[0] = 0;
            message_buffer[1] = 0;
            message_buffer[2] = 0;
            message_buffer[3] = 0;
        }
    };

fail:
    printf ("sysmon: Exit with error\n");
    return -1;
done:
    printf ("sysmon: Exit\n");
    return 0;
}


