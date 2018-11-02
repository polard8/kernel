/*
 * File: dbox.c
 *     Dialog Box support.
 * 
 * Descrição: 
 *     Gerência de caixas de diálogo.
 *     Faz parte do módulo Window Manager do tipo MB.
 *     Obs: Dialogbox é basicamente um 'form'.
 *
 * History:
 *     2015 - Created by fred Nora.
 */

 
#include <kernel.h>


//Protótipo do procedimento.
unsigned long 
DialogBoxProcedure ( struct window_d *window, 
                     int msg, 
					 unsigned long long1, 
					 unsigned long long2 );
					 
					 
					 
					 
					 
					 

/*
//rotina interna de suporta ao mouseHandler 
#define _MOUSE_X_SIGN 0x10
#define _MOUSE_Y_SIGN 0x20

void
update_mouse1()
{

char x = (mouse_packet_data & _MOUSE_X_SIGN);
char y = ( mouse_packet_data & _MOUSE_Y_SIGN );


//do_x:
	    //x 
		//checando o sinal para x.
		//se for diferente de 0 então x é negativo
		if(x != 0)
		{
			//complemento de 2.
			mouse_packet_x = ~mouse_packet_x + 1;
			mouse_x = mouse_x - mouse_packet_x;
		}else{

			mouse_x = mouse_x + mouse_packet_x;
		}

		
//do_y:		
		//y
		//se for diferente de 0 então y é negativo
		if(y != 0)
		{
			//complemento de 2.
			mouse_packet_y = ~mouse_packet_y + 1;
			mouse_y = mouse_y + mouse_packet_y;
		}else{
			mouse_y = mouse_y - mouse_packet_y;
		};		
		
    return;		
};
*/





/*
 * mouse_write:
 *     Envia um byte para a porta 0x60.
 *     (Nelson Cole) 
 */
void mouse_write (unsigned char write){
	
	kbdc_wait(1);
	outportb (0x64,0xD4);
	
	kbdc_wait(1);
	outportb (0x60,write);
};


/*
 * mouse_read:
 *     Pega um byte na porta 0x60.
 *     (Nelson Cole) 
 */
unsigned char mouse_read (){
	
	kbdc_wait(0);
	
	return inportb(0x60);
};













					 
								  
								  
/*
 * DialogBox:
 *     Cria uma janela do tipo 3 (normal) e 
 * mostra uma mensagem.
 *
 */
void DialogBox ( struct window_d *parent_window, 
                 int type, 
				 char *title, 
				 char *string )
{

/*

    ### cancelada. Essa rotina agora está na API em user mode. deletar essa função ###	
	
	struct window_d *hWnd; 
	struct window_d *pWnd; 
	struct window_d *bWnd;
	
    //retângulo abaixo do grid.
	
	//x
	unsigned long x  = (unsigned long) (3*(800/20));	 //>
    unsigned long cx = (unsigned long) (14*(800/20));    //sobra 3 de cada lado.
	
	//y
	unsigned long y  = (unsigned long) (2*(600/20));     //V
    unsigned long cy = (unsigned long) (2*(600/20));		
	
	//
	// Parent window.
	//
	
	if ( (void *) parent_window == NULL )
	{
	    pWnd = (void *) gui->screen;
	
	} else {
	    pWnd = (void *) parent_window;
	};

	//
	// Type.
	//
	
	switch (type)
	{
	    case 1:
	        hWnd = (void *) CreateWindow ( 3, 0, 0, title, 
			                    x, y, cx, cy, 
							    pWnd, 0, 0, COLOR_WINDOW ); 
		    break;
			
	    case 2:
	        hWnd = (void *) CreateWindow ( 3, 0, 0, "DialogBox2", 
			                   x, y, cx, cy, 
							   pWnd, 0, 0, COLOR_WINDOW ); 
	        break;
			
	    case 3:
	        hWnd = (void *) CreateWindow ( 3, 0, 0, "DialogBox3", 
			                   x, y, cx, cy, 
							   pWnd, 0, 0, COLOR_WINDOW ); 
	        break;
			
	    case 4:
	        hWnd = (void *) CreateWindow ( 3, 0, 0, "DialogBox4", 
			                   x, y, cx, cy, 
							   pWnd, 0, 0, COLOR_WINDOW ); 
	        break;
			
		default:
	        //hWnd = (void*) CreateWindow( 3, 0, 0, "Error", 
			//                    x, y, cx, cy, pWnd, 0, 0, COLOR_WINDOW); 
		    break;
	};
	
	// Register.
	
	if( (void *) hWnd == NULL)
	{
	    printf("DialogBox: hWnd\n");
		die();
	
	} else {
		
		RegisterWindow(hWnd);
		set_active_window(hWnd);
	};
	
	//
    // String. 
	//
	
	//(@todo: Get client area rect).
//d_string:

	draw_text ( hWnd, 1*(cx/16), 4*(cy/16), COLOR_WINDOWTEXT, string );

	//
    // Button. 
	//
	
    // (@todo: Get client area rect).
//d_button:
	 
	bWnd = (void *) CreateWindow ( 11, 0, 0, "Close", 
	                    2*(cx/6), 3*(cy/6), cx/4, cy/6, 
						hWnd, 0, 0, COLOR_BUTTONFACE );
								 
	if ( (void *) bWnd == NULL)
	{
	    printf("DialogBox error: bWnd\n");
		die();
		
	} else {
		
	    RegisterWindow(bWnd);
        SetFocus(bWnd);		
	};		
	
	//
	// Continua ...
	//

	SetProcedure ( (unsigned long) &DialogBoxProcedure );	
	
//done:

    refresh_screen();	
    
	//return;
	
*/

};




/*
 * DialogBoxProcedure:
 *     O procedimento padrão de dialog box.
 *
 */																
unsigned long DialogBoxProcedure( struct window_d *window, 
                                  int msg, 
								  unsigned long long1, 
								  unsigned long long2 ) 
{
	
	
/*	
	    ### cancelada. Essa rotina agora está na API em user mode. deletar essa função ###
		
	//if (msg < 0)
	//    return 0;
	
    switch (msg)
	{	
        case MSG_KEYDOWN:
            switch(long1)
            {
                case VK_ESCAPE:
                   //KillFocus(window);				
				    SetProcedure( (unsigned long) &system_procedure);
                   	return (unsigned long) 0; 			   
				    break;
				   
                default:
                    break; 
            };
        break;
		
        case MSG_SYSKEYDOWN:                 
            switch(long1)	       
            {   
			
				//Start
				case VK_F1:
				    StatusBar(window,"Status Bar","F1");
                    break;
					
				//Reboot	
                case VK_F2:
                    break;
					
				case VK_F3:
                    break;					

				case VK_F4:
                    break;					

				//case VK_F5:
                //    break;	
					
                //
                // Testes: Install, format, create volume, delete volume, files operations...
                //
				
				default:
				    //SetProcedure( (unsigned long) &system_procedure);
				    break;
		    };              
        break;
		
		default:
		    //Nothing for now.
		    break;
	};
	
//done:

*/

	return (unsigned long) 0;
};


/*
int dialogboxInit()
{}
*/

//
// End.
//

