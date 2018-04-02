/*
 * File: dialogbox.c
 *
 * Descrição: 
 *     Gerência de caixas de diálogo.
 *     Faz parte do módulo Window Manager do tipo MB.
 *     Obs: Dialogbox é basicamente um 'form'.
 * History:
 *     2015 - Created by fred Nora.
 */

 
#include <kernel.h>


//Protótipo do procedimento.
unsigned long DialogBoxProcedure( struct window_d *window, 
                                  int msg, 
								  unsigned long long1, 
								  unsigned long long2 );
								  
								  
/*
 * DialogBox:
 *     Cria uma janela do tipo 3 (normal) e mostra uma mensagem.
 *
 */
void DialogBox( struct window_d *parent_window, 
                int type, 
				char *title, 
				char *string )
{
	struct window_d *hWnd; 
	struct window_d *pWnd; 
	struct window_d *bWnd;
	
	//Set up.
	//unsigned long x = (unsigned long) 800/3;	
	//unsigned long y = (unsigned long) 600/3;
    //unsigned long cx = (unsigned long) 800/3;
    //unsigned long cy = (unsigned long) 600/3;
	
	
    //retângulo abaixo do grid.
	
	//x
	unsigned long x  = (unsigned long) (3*(800/20));	 //>
    unsigned long cx = (unsigned long) (14*(800/20));    //sobra 3 de cada lado.
	
	//y
	unsigned long y  = (unsigned long) (2*(600/20)); //V
    unsigned long cy = (unsigned long) (2*(600/20));		
	
	// Parent window.
	if( (void*) parent_window == NULL ){
	    pWnd = (void*) gui->screen;
	}else{
	    pWnd = (void*) parent_window;
	};

	// Type.
	switch(type)
	{
	    case 1:
	        hWnd = (void*) CreateWindow( 3, 0, 0, title, x, y, cx, cy, pWnd, 0, 0, COLOR_WINDOW); 
		    break;
	    case 2:
	        hWnd = (void*) CreateWindow( 3, 0, 0, "DialogBox2", x, y, cx, cy, pWnd, 0, 0, COLOR_WINDOW); 
	        break;
	    case 3:
	        hWnd = (void*) CreateWindow( 3, 0, 0, "DialogBox3", x, y, cx, cy, pWnd, 0, 0, COLOR_WINDOW); 
	        break;
	    case 4:
	        hWnd = (void*) CreateWindow( 3, 0, 0, "DialogBox4", x, y, cx, cy, pWnd, 0, 0, COLOR_WINDOW); 
	        break;
		default:
	        //hWnd = (void*) CreateWindow( 3, 0, 0, "Error", x, y, cx, cy, pWnd, 0, 0, COLOR_WINDOW); 
		    break;
	};
	
	// Register.
	if( (void*) hWnd == NULL){
	    printf("DialogBox: hWnd\n");
		refresh_screen();
	    while(1){};    //Hang.
	}else{
		RegisterWindow(hWnd);
		set_active_window(hWnd);
	};
	
    // String. 
	//(@todo: Get client area rect).
d_string:
	draw_text( hWnd, 1*(cx/16), 4*(cy/16), COLOR_WINDOWTEXT, string);

    // Button. 
    // (@todo: Get client area rect).
d_button:	 
	bWnd = (void*) CreateWindow( 11, 0, 0, "Close", 
	                             2*(cx/6), 3*(cy/6), cx/4, cy/6, 
						         hWnd, 0, 0, COLOR_BUTTONFACE); 
	if( (void*) bWnd == NULL){
	    printf("DialogBox error: bWnd\n");
		refresh_screen();
	    while(1){};
	}else{
	    RegisterWindow(bWnd);
        SetFocus(bWnd);		
	};		
	
	//
	// Continua ...
	//

	SetProcedure( (unsigned long) &DialogBoxProcedure);	
	
done:
    refresh_screen();	
    return;
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
    //Msg. 
    switch(msg)
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

				case VK_F5:
                    break;	
					
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
	
done:
	return (unsigned long) 0;
};


/*
int dialogboxInit()
{}
*/

//
//fim
//

