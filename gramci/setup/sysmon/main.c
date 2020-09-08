// main.c 
// sysmon - System monitor using kgws.


#include "sysmon.h"


//#define TEDITOR_VERBOSE 1


#define GRID_HORIZONTAL    1000
#define GRID_VERTICAL      2000


//static int running = 1;
int running = 1;


// Janelas
struct window_d *main_window;
struct window_d *client_window;
struct window_d *client_bar_Window;
struct window_d *data_window;         //White.


// bar buttons
struct window_d *bar_button_1; 

struct window_d *cpu_window;    //cpu usage test;

int __count;
unsigned long CPU_USAGE[32];


//static char *dest_argv[] = { "-sujo0","-sujo1","-sujo2",NULL };
//static unsigned char *dest_envp[] = { "-sujo", NULL };
//static unsigned char dest_msg[512];

 
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

void test_cpu(struct window_d *window)
{
    debug_print("test_cpu:");

    unsigned long deviceWidth  = gde_get_system_metrics(1); 
    unsigned long deviceHeight = gde_get_system_metrics(2);


    if ( (void*) window == NULL ){
        debug_print("test_cpu: window\n");
        return;
    }


    //gramado_system_call ( 9901,   
      //  (unsigned long) window, 
      //  (unsigned long) window, 
      //  (unsigned long) window );

     //execve ( (const char *) "noraterm.bin", 
        //(const char *) 0, (const char *) 0); 

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
    cpu_window = (void *) gde_create_window ( 1, 1, 1, 
                              "cpu-usage",  
                               (deviceWidth - (32*8) -4 ), 2, 
                               32*8, 100,    
                               window, 0, 
                               COLOR_YELLOW, COLOR_YELLOW );
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
    gde_draw_text ( data_window,   50, 8, COLOR_BLACK, "Name" );
    gde_draw_text ( data_window,  200, 8, COLOR_BLACK, "Priority" );     
    gde_draw_text ( data_window,  300, 8, COLOR_BLACK, "State" );     
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
            gde_draw_text ( data_window,  50, y, 
                COLOR_BLACK, (char *) __processname_buffer );
            gde_draw_text ( data_window, 200, y, 
                COLOR_BLACK, (char *) __priority_buffer ); 
            gde_draw_text ( data_window, 300, y, 
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

    //Salvaremos o nome do processo aqui.
    //char __processname_buffer[64];
    //char __tmp_buffer[64];


    switch (msg)
    {

        case MSG_SYSKEYDOWN:
            switch (long1)
            {  
                case VK_F1: 
                    debug_print("sysmon: [F1]"); 
                    showinfo_button1();
                    goto done;
                    break;

                case VK_F2: 
                    debug_print("sysmon: [F2]"); 
                    goto done;
                    break;

                case VK_F3: 
                    debug_print("sysmon: [F3]"); 
                    goto done;
                    break;

                case VK_F4: 
                    debug_print("sysmon: [F4]"); 
                    // IN: parent window.
                    test_cpu(main_window);
                    goto done;
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
				case 1:
					if (window == main_window)
					{
						gde_set_focus (window);
					    gde_redraw_window (window,1);
					    // #todo: we need to redraw all other windows.
					}

                    //pid button.
                    if ( window == bar_button_1 )
                    {
                        gde_redraw_window (data_window,1);
                        gramado_system_call ( 9901,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window ); 
                        showinfo_button1();
                        break;
                    }
				    break;
			};
			goto done;
			break;


        default:
            debug_print ("sysmon: default message");
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
    
    unsigned long left=0;
    unsigned long top=0;
    unsigned long width=0;
    unsigned long height=0;
    
    left = 4;  //deviceWidth/2;
    top = 4;  //deviceHeight/3;
    width  = (deviceWidth -20);
    height = (deviceHeight-20);


//#ifdef TEDITOR_VERBOSE
	//printf("\n");
	//printf("Initializing File explorer:\n");
	//printf("mainTextEditor: # argv={%s} # \n", &argv[0] );
//#endif

	//
	// ## vamos repetir o que dá certo ...
	//

	//vamos passar mais coisas via registrador.

	//ok
	//foi passado ao crt0 via registrador
	//printf("argc={%d}\n", argc ); 
	
	//foi passado ao crt0 via memória compartilhada.
	//printf("argvAddress={%x}\n", &argv[0] ); //endereço.
	
	
	//unsigned char* buf = (unsigned char*) (0x401000 - 0x100) ;
	//printf("argvString={%s}\n" ,  &argv[0] );
	//printf("argvString={%s}\n" , &buf[0] );
	
	//printf("argv={%s}\n", &argv[2] );

	//
	// ## app window ##
	//

	//green crocodile = 0x44541C 
	//orange royal = 0xF9812A
	//window = 0xF5DEB3
	//client window = 0x2d89ef 
	//...


    //++
    // The main window.
    gde_begin_paint (); 
    hWindow = (void *) gde_create_window (  WT_OVERLAPPED, 1, 1, 
                           "Setup: sysmon",
                           left, top, width, height,    
                           0, 0, 
                           COLOR_BLUE, COLOR_BLUE );  

    if ( (void *) hWindow == NULL ){
        printf ("sysmon: hWindow fail\n");
        gde_end_paint ();
        goto fail;

    }else{
        //Registrar e mostrar.
        gde_register_window (hWindow);
        gde_show_window (hWindow);
        main_window = ( struct window_d *) hWindow;
    };
    gde_end_paint ();
    //--

     //Text
     gde_draw_text ( main_window, 4, 4, 
         COLOR_WHITE, "sysmon.bin: System information." );
     gde_show_window (main_window);
     //while(1){}


    //
    // == Client background =====================
    //

    //++
    // Client background.
    gde_enter_critical_section ();  
    client_window = (void *) gde_create_window ( WT_SIMPLE, 1, 1, 
                                "client-bg",     
                                16, 16, 
                                width -16 -16, height -16 -16, 
                                main_window, 0, 
                                0xF5DEB3, 0xF5DEB3 );

    if ( (void *) client_window == NULL){
        printf ("client_window fail");
        gde_show_backbuffer();
        gde_exit_critical_section ();
        while(1){}
    }
    gde_register_window (client_window);
    gde_show_window (client_window);
    gde_exit_critical_section ();  
    //--


    //
    // ========= Client bar =====================
    //

    //++
    // Client bar.
    gde_enter_critical_section ();  
    client_bar_Window = (void *) gde_create_window ( WT_SIMPLE, 1, 1, 
                                    "client-bar",     
                                    2, 2, 
                                    ((width -16 -16) -2 -2), 40, 
                                    client_window, 0, 
                                    0x404040, 0x404040 );
    
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
                                " F1 ",  
                                4, 4, 100, 32,    
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




    //
    // == Data window ===================
    //

    // White window to show the data.

    //++
    // White window.
    gde_enter_critical_section ();  
    data_window = (void *) gde_create_window ( WT_SIMPLE, 1, 1, 
                               "DataWindow",     
                                4, 48, 
                                ((width -16 -16) -4 -4), ((height*2)/3), 
                                client_window, 0, 
                                COLOR_WHITE, COLOR_WHITE );

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

    while (running)
    {
        gde_enter_critical_section (); 
        system_call ( 111,
            (unsigned long) &message_buffer[0],
            (unsigned long) &message_buffer[0],
            (unsigned long) &message_buffer[0] );
        gde_exit_critical_section (); 


        if ( message_buffer[1] != 0 )
        {
            sysmonProcedure ( (struct window_d *) message_buffer[0], 
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
    printf ("sysmon: Exit with error\n");
    return -1;

done:
    printf ("sysmon: Exit\n");
    return 0;
}


