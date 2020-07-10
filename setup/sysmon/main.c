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
    struct window_d *data_window;     //white.

    // launcher buttons
    struct window_d *launcher_button_1;
    struct window_d *launcher_button_2;

    // bar buttons
    struct window_d *bar_button_1; 
    struct window_d *bar_button_2;
    struct window_d *bar_button_3;

    struct window_d *cpu_window;  //cpu usage test;



//static char *dest_argv[] = { "-sujo0","-sujo1","-sujo2",NULL };
//static unsigned char *dest_envp[] = { "-sujo", NULL };
//static unsigned char dest_msg[512];

 

int 
sysmonProcedure ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );
 


int __count;
unsigned long CPU_USAGE[32];

// Interna.
// Usado para testar o timer.
void update_cpu_usage ()
{
    unsigned long __idle_value;
    unsigned long __value;
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
		for (i=0; i<32; i++)
		{
			//printf ("%d ", (unsigned long) CPU_USAGE[i]);
		
		    gde_draw_text ( cpu_window, i*8, CPU_USAGE[i], COLOR_BLACK, "+");
		}
		gde_show_window (cpu_window);
    }
	
	//printf ("fim\n");
    //printf ("cpu usage: %d percent \n", __value);
}


// internal
// #todo: ordenar por pid
void showinfo_button1()
{

    //salvaremos o nome do processo aqui.
    char __processname_buffer[64];
    char __tmp_buffer[64];

    unsigned long __process_priority;
                            
    int i;
  
    //#todo
    //Criar um for para mostrar vários processos.
  
    //unsigned long x = 0;
    unsigned long y = 4;
        
    for ( i=100; i<104; i++)
    {
        // get process name.
        gde_getprocessname  ( i,  
             __processname_buffer, 
             sizeof(__processname_buffer) );
        
        // get process priority
        __process_priority = gde_get_process_stats ( i,33);      
        itoa(__process_priority, __tmp_buffer);
        
        gde_draw_text ( data_window,   4, y, COLOR_BLACK, "n" );
        gde_draw_text ( data_window,  40, y, COLOR_BLACK, (char *) __processname_buffer );
        gde_draw_text ( data_window, 200, y, COLOR_BLACK, (char *) __tmp_buffer ); 
    
        //update y
        y = y + 10;
    };

    // refresh screen
    gde_show_backbuffer ();
}

// internal
// #todo: ordenar por state
void showinfo_button2()
{

    //salvaremos o nome do processo aqui.
    char __processname_buffer[64];
    char __tmp_buffer[64];

    unsigned long __process_priority;
                            
    int i;
  
    //#todo
    //Criar um for para mostrar vários processos.
  
    //unsigned long x = 0;
    unsigned long y = 4;
        
    for ( i=100; i<104; i++)
    {
        // get process name.
        gde_getprocessname  ( i,  
             __processname_buffer, 
             sizeof(__processname_buffer) );
        
        // get process priority
        __process_priority = gde_get_process_stats ( i,33);      
        itoa(__process_priority, __tmp_buffer);
        
        gde_draw_text ( data_window,   4, y, COLOR_BLACK, "n" );
        gde_draw_text ( data_window,  40, y, COLOR_BLACK, (char *) __processname_buffer );
        gde_draw_text ( data_window, 200, y, COLOR_BLACK, (char *) __tmp_buffer ); 
    
        //update y
        y = y + 10;
    };

    // refresh screen
    gde_show_backbuffer ();
}


// internal
// #todo: ordenar por priority
void showinfo_button3()
{

    //salvaremos o nome do processo aqui.
    char __processname_buffer[64];
    char __tmp_buffer[64];

    unsigned long __process_priority;
                            
    int i;
  
    //#todo
    //Criar um for para mostrar vários processos.
  
    //unsigned long x = 0;
    unsigned long y = 4;
        
    for ( i=100; i<104; i++)
    {
        // get process name.
        gde_getprocessname  ( i,  
             __processname_buffer, 
             sizeof(__processname_buffer) );
        
        // get process priority
        __process_priority = gde_get_process_stats ( i,33);      
        itoa(__process_priority, __tmp_buffer);
        
        gde_draw_text ( data_window,   4, y, COLOR_BLACK, "n" );
        gde_draw_text ( data_window,  40, y, COLOR_BLACK, (char *) __processname_buffer );
        gde_draw_text ( data_window, 200, y, COLOR_BLACK, (char *) __tmp_buffer ); 
    
        //update y
        y = y + 10;
    };

    // refresh screen
    gde_show_backbuffer ();
}



/*
 * *********************************
 * sysmonProcedure:
 *     Procedimento de janela.
 */

int 
sysmonProcedure ( struct window_d *window, 
                  int msg, 
                  unsigned long long1, 
                  unsigned long long2 )
{
	
	//salvaremos o nome do processo aqui.
   //char __processname_buffer[64];
   //char __tmp_buffer[64];

    switch (msg)
    {
		
		case MSG_CREATE:
		    break;
		    
		        
		case MSG_TIMER:
		    update_cpu_usage ();
		    break;

		case MSG_SYSKEYDOWN:
		    switch (long1)
			{  
				case VK_F1:
					break;
					
				case VK_F2:
					break;
					
				//case VK_F3:
					//break;

				//...
	
                //full screen
                //colocar em full screen somente a área de cliente. 
		        case VK_F11:    
					break;

				//...

			};
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
        case 30:
            switch (long1)
            {
				//botão 1.
				case 1:
				    if ( window == launcher_button_1 )
				    {
                        gramado_system_call ( 9900,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
						 break;
					}

				    if ( window == launcher_button_2 )
				    {
                        gramado_system_call ( 9900,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
						 break;
					}
					
					if ( window == bar_button_1 )
					{
                        gramado_system_call ( 9900,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
						break;
					}
					
					if ( window == bar_button_2 )
					{
                        gramado_system_call ( 9900,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
					    break;
					}

					if ( window == bar_button_3 )
					{
                        gramado_system_call ( 9900,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
					    break;
					}



					//se
					if ( window == main_window )
					{
						gde_set_focus (window);
						//raise window.
	                     //system_call ( 9700, 
	                         //(unsigned long) main_window, 
		                     //(unsigned long) main_window, 
		                     //(unsigned long) main_window );
					}

					break;
			};
			break;


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
				
				    if ( window == launcher_button_1 )
				    {
                        gramado_system_call ( 9901,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
						//execve ( (const char *) "noraterm.bin", 
                           //(const char *) 0, (const char *) 0); 
						 //====================================
	                     // timer-test
	                     // Essa rotina cria um objeto timer que gera um interrupção 
	                     // de tempos em tempos e é tratado pelo procedimento de janelas.
		                 __count = 0; //tem que inicializar;
		                 //printf("Creating timer\n");
	                     //printf("%d Hz | sys time %d ms | ticks %d \n", 
		                 //apiGetSysTimeInfo(1), 
			             //apiGetSysTimeInfo(2), 
			             //apiGetSysTimeInfo(3) );
		                 gde_enter_critical_section ();
		                 cpu_window = (void *) gde_create_window ( 1, 1, 1, 
		                                         "cpu-usage",  
                                                 20 +4, (32 +2), 
                                                 32*8, 100,    
                                                 main_window, 0, 
                                                 COLOR_YELLOW, COLOR_YELLOW );
                         gde_register_window (cpu_window);
	                     gde_show_window (cpu_window);
	                     gde_exit_critical_section ();
	                     // Atualizar à cada 2000 ms. 
		                 //janela, 100 ms, tipo 2= intermitente.
		                 //system_call ( 222, (unsigned long) window, 100, 2);
                         gde_create_timer ( (struct window_d *) window, 
                            (unsigned long) 80, (int) 2 );
                         //printf ("done\n");
						 //====================================
						 break;
					}
				    if ( window == launcher_button_2 )
				    {
                        gramado_system_call ( 9901,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
						 execve ( (const char *) "reboot2.bin",
                            (const char *) 0, (const char *) 0);
						 break;
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

                    //state button.
                    if ( window == bar_button_2 )
                    {
                        gde_redraw_window (data_window,1);
                        gramado_system_call ( 9901,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
                        showinfo_button2();
                        break;
                    }
             
                    //priority button
                    if ( window == bar_button_3 )
                    {
                        gde_redraw_window (data_window,1);
                        gramado_system_call ( 9901,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
                        showinfo_button3();
                        break;
                   }

				    break;
			};
			break;


        default:
            break;
    };


    //return 0;
    return (int) gde_system_procedure (window, msg, long1, long2);
}


/*
 ********************************************
 * main:
 */

int main ( int argc, char *argv[] ){

    struct window_d *hWindow;

    FILE *fp;

    int ch;
    int char_count = 0;

    //#bugbug
    //Ele falha se a largura for pouco.

    //unsigned long left = 600;
    //unsigned long top = 100;
    //unsigned long width = 320;
    //unsigned long height = 480;
    
    unsigned long left;
    unsigned long top;
    unsigned long width;
    unsigned long height;
    

    unsigned long deviceWidth = gde_get_system_metrics (1); 
    unsigned long deviceHeight = gde_get_system_metrics (2);

    //left = deviceWidth/2;
    left = 4;
    //top = deviceHeight/3;
    top = 4;
    
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



	//++
    gde_enter_critical_section (); 
    launcher_button_1 = (void *) gde_create_window ( WT_BUTTON, 1, 1, 
                                     "1",  
                                     20 + (32*8)  +10, 36 +10, 
                                     40, 40,    
                                     hWindow, 0, 
                                     xCOLOR_GRAY3, xCOLOR_GRAY3 );

    if ( (void *) launcher_button_1 == NULL )
    {
		printf ("Couldn't create button\n");
		gde_exit_critical_section (); 
		return 1;
    }else{
        gde_register_window (launcher_button_1);
        gde_show_window (launcher_button_1);
        gde_show_backbuffer ();
    };
    gde_exit_critical_section (); 
	//--



	//++
    gde_enter_critical_section (); 
    launcher_button_2 = (void *) gde_create_window ( WT_BUTTON, 1, 1, 
                                     "2", 
                                     20 + (32*8) +10 +40, 36 +10,
                                     40, 40,   
                                     hWindow, 0, 
                                     xCOLOR_GRAY3, xCOLOR_GRAY3 );
	
	if ( (void *) launcher_button_2 == NULL )
	{
		printf ("Couldn't create button\n");
		gde_exit_critical_section (); 
		return 1;
	}else{

        gde_register_window (launcher_button_2);
        gde_show_window (launcher_button_2);
        gde_show_backbuffer ();
	};
    gde_exit_critical_section (); 
	//--




    //
    // ========= Client background =====================
    //

	//++
	gde_enter_critical_section ();  
	client_window = (void *) gde_create_window ( WT_SIMPLE, 1, 1, 
	                            "client-bg",     
                                20, 100 +36, 
                                width -4 -42, height -36 -100 -40, 
                                hWindow, 0, 
                                0xF5DEB3, 0xF5DEB3 );

    if ( (void *) client_window == NULL)
    {
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
    gde_enter_critical_section ();  
    client_bar_Window = (void *) gde_create_window ( WT_SIMPLE, 1, 1, 
                                    "client-bar",     
                                    2, 2, 
                                    (width -10 -40), 40, 
                                    client_window, 0, 
                                    0x404040, 0x404040 );
    if ( (void *) client_bar_Window == NULL)
    {
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
    gde_enter_critical_section (); 
    bar_button_1 = (void *) gde_create_window ( WT_BUTTON, 1, 1, 
                                "PID",  
                                1, 1, 
                                50, 32,    
                                client_bar_Window, 0, 
                                xCOLOR_GRAY3, xCOLOR_GRAY3 );

    if ( (void *) bar_button_1 == NULL )
    {
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
    gde_enter_critical_section (); 
    bar_button_2 = (void *) gde_create_window ( WT_BUTTON, 1, 1, 
                                "State", 
                                50 +1, 1,
                                100, 32,   
                                client_bar_Window, 0, 
                                xCOLOR_GRAY3, xCOLOR_GRAY3 );

    if ( (void *) bar_button_2 == NULL )
    {
		printf ("Couldn't create State button\n");
		gde_exit_critical_section (); 
        return 1;
    }else{

        gde_register_window (bar_button_2);
        gde_show_window (bar_button_2);
        gde_show_backbuffer ();
    };
    gde_exit_critical_section (); 
	//--


	//++
    gde_enter_critical_section (); 
    bar_button_3 = (void *) gde_create_window ( WT_BUTTON, 1, 1, 
                                "Priority", 
                                50 +1 +100 +1, 1,
                                200, 32,   
                                client_bar_Window, 0, 
                                xCOLOR_GRAY3, xCOLOR_GRAY3 );
	
    if ( (void *) bar_button_3 == NULL )
    {
		printf ("Couldn't create Priority button\n");
		gde_exit_critical_section ();
		return 1;
    }else{

        gde_register_window (bar_button_3);
        gde_show_window (bar_button_3);
        gde_show_backbuffer ();
    };
    gde_exit_critical_section (); 
	//--



    //
    // ========= Data window ===================
    //

    // White window to show the data.

	//++
	gde_enter_critical_section ();  
	data_window = (void *) gde_create_window ( WT_SIMPLE, 1, 1, 
	                            "data_window",     
                                4, 48, 
                                width -4 -50, height -36 -100 -40 -50, 
                                client_window, 0, 
                                COLOR_WHITE, COLOR_WHITE );

    if ( (void *) data_window == NULL)
    {
        printf ("data_window fail");
        gde_show_backbuffer();
        gde_exit_critical_section ();
        while(1){}
    }
	gde_register_window (data_window);
	gde_show_window (data_window);
	gde_exit_critical_section ();  
	//--



	//
	//  Loop
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
            message_buffer[3] = 0;
            message_buffer[4] = 0;
        };
    };



fail:
    printf ("Fail!\n");
    return -1;

done:
    return 0;
}




