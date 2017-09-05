/*
 * File: messagebox.c
 *
 * Descrição:
 *     Mostra um message box na tela.
 *     Faz parte do módulo Window Manager do tipo MB.
 *
 * Fase de desenvolvimento: Retângulo abaixo do grid.
 *
 * Versão 1.0, 2015.
 */

 
#include <kernel.h>


unsigned long MessageBoxProcedure( struct window_d *window, 
                                   int msg, 
								   unsigned long long1, 
								   unsigned long long2 );

								   
	
/*
void messageboxIn(int type, char *title, char *string);
void messageboxIn(int type, char *title, char *string)
{
	//@todo: melhorar esse filtro.
    if( (void*) gui->shellWindow == NULL ){
		return;
	};
	
	MessageBox( (struct window_d *) gui->shellWindow, (int) type, (char *) title, (char *) string );
    return;				 
};
*/	

/*
void messageboxOut(struct window_d *parent_window, int type, char *title, char *string);
void messageboxOut(struct window_d *parent_window, int type, char *title, char *string)
{	
	MessageBox( (struct window_d *) parent_window, (int) type, (char *) title, (char *) string );
    return;				 
};
*/	

								   
/*
 * MessageBox:
 *     Cria uma Window Frame e apresenta uma mensagem nela.
 *     
 */
void MessageBox( struct window_d *parent_window,  //Window frame handle.      
                 int type,                        //Message Box type.
				 char *title,                     //Title for the window frame.
				 char *string )                   //Message string.
{	
	//
	// Set up.
	//
	
	//Elementos.
	int Button = 0;
	int Icon = 0;
	//continua...
	
	//unsigned long x  = (unsigned long) (1*(800/3));	
	//unsigned long y  = (unsigned long) (1*(600/3));
    //unsigned long cx = (unsigned long) (1*(800/3));
    //unsigned long cy = (unsigned long) (1*(600/3));	

    //retângulo abaixo do grid.
	
	//x
	unsigned long x  = (unsigned long) (3*(800/20));	 //>
    unsigned long cx = (unsigned long) (14*(800/20));    //sobra 3 de cada lado.
	
	//y
	unsigned long y  = (unsigned long) (2*(600/20)); //V
    unsigned long cy = (unsigned long) (2*(600/20));	

	
	struct window_d *hWnd;    //Window.
	struct window_d *pWnd;    //Parent.
	struct window_d *bWnd;    //Button.

	
	//No GUI.
	if(VideoBlock.useGui != 1){
		printf("MessageBox error: Using text mode.\n");
	    return;	
	};
	
	if( (void*) gui->screen == NULL ){
	    return;
	};
	
	// Parent.
	if( (void*) parent_window == NULL ){
	    pWnd = gui->screen;
	}else{
	    pWnd = (void*) parent_window;
	};
	
	
    //
    // @todo: 
	//     O switch deve ser usado somente para a seleção da mensagem.
	//     Deve haver apenas uma função de criação, depois do switch.
    // 	
	
	
	//
	// Aqui cria uma janela em com base a parent window 'pWnd'.
	//
	
	//
	// Creating a Window Frame for the Message Box. 
	//

	switch(type)
	{
		//
		// 765432(D=1) ??
		//
				
	    //Considera o título.
	    case 1:
		    Button = 1;
	        hWnd = (void*) CreateWindow( 3, 0, 0, title, x, y, cx, cy, pWnd, 0, 0, 0); 
		    break;
			
		//Sem botão	
	    case 2:
		    Button = 0;
	        hWnd = (void*) CreateWindow( 3, 0, 0, title, x, y, cx, cy, pWnd, 0, 0, 0); 
	        break;
			
	    case 3:
	        Button = 1;
			hWnd = (void*) CreateWindow( 3, 0, 0, "Alert", x, y, cx, cy, pWnd, 0, 0, 0); 
	        break;
			
	    case 4:
		    Button = 1;
	        hWnd = (void*) CreateWindow( 3, 0, 0, "System Message", x, y, cx, cy, pWnd, 0, 0, 0); 
	        break;
			
		default:
		    Button = 1;
	        hWnd = (void*) CreateWindow( 3, 0, 0, "Error", x, y, cx, cy, pWnd, 0, 0, 0); 
		    break;
	};
	
	//
    // Register.
	//
	
	if((void*) hWnd == NULL){
	    printf("MessageBox error: Window Struct.\n");
		refresh_screen();
	    while(1){};
	}else{   
		
		RegisterWindow(hWnd);
        set_active_window(hWnd);
		
		//@todo: O foco deve estar no botão e não na janela ativa..
		SetFocus(hWnd);  	 
		//...
	};
	
	//
	// Icon
	//
	//if ( Icon == 1){};
	
	//
    // String. (Uma string dentro da client area.)
    //
	
	//@todo: Calcular o tamanho da string.
	//size_t S;
	//S = (size_t) strlen( (const char*) string);
	
d_string:
	draw_text( hWnd, 1*(cx/16), (cy-16), COLOR_WINDOWTEXT, string);

	//
    // Button: 
	//    (Um botão dentro da client area.)
    //    @todo: É preciso criar um botão do tipo janela.
	//           para colocar foco na janela.
	//
	//
	//
d_button:	
    if(Button == 1)
	{
		//@todo: Criar uma janela do tipo botão para setar o foco.
        //       Pegar o tamanho da string para definir o tamanho do botão.
        draw_button( hWnd, "Close", 1, (cx-56-8), (cy-24-8), 56, 24, COLOR_BUTTONFACE); 
		//draw_button( hWnd, "Close", 1, 12*(cx/16), 8*(cy/16), 48, 24, COLOR_BLACK);		
    
	    //   
	    // @todo: FOCO NO BOTÃO !!!
	    //
		
	};
	
/*
    ** Outra maneira de cria um botão ***
    ** Obs: Retorna o haldle da janela **
    ** Obs: Precisamos de um handle para setar o foco. ***
	
        bWnd = CreateWindow( 11, 0, 0, "Close", 
		                     cx-102, y+2, 100, 24, 
							 hWnd, 0, 0, 0);
							 
	    if( (void*) bWnd == NULL )
	    {
	        printf("MessageBox error: Button Struct.\n");
		    refresh_screen();
	        while(1){};
	    }
	    else
	    {
		    SetFocus(bWnd);   //o botão tem o foco de entrada.
			RegisterWindow(bWnd); 
	    };	
*/		
	
	
	//
	// Continua ...
	//
	
	CurrentWindow = (void*) hWnd;
	SetProcedure( (unsigned long) &MessageBoxProcedure );	
	
done:
    //SetFocus(bWnd);    //@todo: Setar foco no botão.		
    refresh_screen();		   
    return;
};


/*
 * MessageBoxProcedure:
 *     O procedimento padrão de message box.
 */																
unsigned long 
MessageBoxProcedure( struct window_d *window, 
                     int msg, 
   				     unsigned long long1, 
					 unsigned long long2 )
{
    switch(msg)
	{
        case MSG_KEYDOWN:
            switch(long1)
            {
                case VK_ESCAPE:	
				    SetProcedure( (unsigned long) &system_procedure);
                    return (unsigned long) 0;				   
				    break;
				   
                default:
				    return (unsigned long) 0;
                    break; 
            };
        break;
	
        case MSG_SYSKEYDOWN:                 
            switch(long1)	       
            {
                //Testando alguns comandos.
				
				case VK_F1:
				    StatusBar(window,"Status Bar","F1");
                    break;
					
                case VK_F2:
                    StatusBar(window,"Status Bar","F2");
					break;
					
				case VK_F3:
				    //DestroyWindow(window);
                    break;					

				case VK_F4:
				    //DestroyWindow(window);
                    break;					
					
                //
                // Testes: Install, format, create volume, delete volume, files operations...
                //
				
				default:
				    return (unsigned long) 0;
				    break;
		    };              
        break;
		
	    case MSG_SYSKEYUP:
		   return (unsigned long) 0; 
           //Nothing.		
           break;
		
        default:
		    return (unsigned long) 0;
			//Nothing.
            break;		
	};
	
	
done:
	//Refresh screen. 
	if(VideoBlock.useGui == 1){
	    refresh_screen();
	};	
	return (unsigned long) 0;
};

/*
int messageboxInit()
{}
*/

//
// End.
//

