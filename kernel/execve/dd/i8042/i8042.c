/*
 * File: i8042.c
 *

 *

 */

 
#include <kernel.h>

//deletar
unsigned long 
MessageBoxProcedure( struct window_d *window, 
                     int msg, 
				     unsigned long long1, 
					 unsigned long long2 );
					 
					 
					 
	

/*
 ***************
 * ps2:
 *     Essa rotina de inicialização do controladro 
 * poderá ter seu próprio módulo.
 *     Inicializa o controlador ps2.
 *     Inicializa a porta do teclado no controlador.
 *     Inicializa a porta do mouse no controlador.
 *     Obs: *importante: A ordem precisa ser respeitada.
 *     As vezes os dois não funcionam ao mesmo tempo se a 
 *     inicialização não for feita desse jeito. 
 */
void ps2 (){
	
   // printf("");	
	
	//printf("ps2: Desabilitando as duas portas...\n");
	//refresh_screen();

    
	
	//
	// ## DESATIVANDO AS DUAS PORTAS ##
	//
	
	
	// Desativar dispositivos PS/2 , isto evita que os dispositivos PS/2 
	// envie dados no momento da configuração.

//desablePorts:

    //##bugbug
	//não sabemos o efeito colateral disso.
	//isso pode dar problema.
	
	// Desativar a primeira porta PS/2.
	//kbdc_wait(1);
	//outportb(0x64,0x60);  	
  	kbdc_wait(1);
	outportb(0x64,0xAD);  
	
	// Desativar a segunda porta PS/2, 
	// hahaha por default ela já vem desativada, só para constar
	//kbdc_wait(1);
	//outportb(0x64,0x60);  	
	kbdc_wait(1);
	outportb(0x64,0xA7); 


    //
	//======================================
	//
	

    //
	// ## step 1 ##
    // mouse	 
    //
	

	
//mouse_initialization:	
	

	//inicializa o controlador para habilitar abort
	//segunda porta. O mouse.
    
	//2
	//printf("ps2: inicializando mouse ...\n");
	//refresh_screen();	
	
	ps2_mouse_initialize();  
	
	
	
	

	//printf("ps2: inicializando globais do mouse ...\n");
	//refresh_screen();	
	
	//Não afeta o controlador. 
	//Apenas inicializa variáveis.
	ps2_mouse_globals_initialize();	 	
	 

	
	
    //
	// ## step 2 ##
    // keyboard	 
	//
//keybaord_initialization:


	
    //2
	//printf("ps2: inicializando teclado ...\n");
	//refresh_screen();	
	ps2_keyboard_initialize();
	
	
	//
	//mouse install ...
	//
	
	mouse_install();
	
	
 
    //
	// ## REABILITANDO ##
	//
 
 	//3
	//printf("ps2: reabilitando  porta do mouse; ...\n");
	//refresh_screen();	
	
	// Ativar a segunda porta PS/2.
	//kbdc_wait(1);
	//outportb(0x64,0x60);    
	//kbdc_wait(1);
	//outportb(0x64,0xA8); 
 
	//3
	//printf("ps2: reabilitando  porta do teclado ...\n");
	//refresh_screen();		
	
	
	//AE    Enable Keyboard Interface: clears Bit 4 of command register
	//      enabling keyboard interface.
	//kbdc_wait(1);
	//outportb(0x64,0x60);    	
	//kbdc_wait(1);
	//outportb(0x64,0xAE);   // Activar a primeira porta PS/2		
	

	//
	// ## RESETANDO ##
	//
	
	
	//1
	//printf("ps2: resetando mouse. ...\n");
	//refresh_screen();		
	
	//+devemos configurar o modo escrita
	//+enviar o comando reset;
	//+ler as respostas.(#todo) fa, ff, 00
	
	// defina, a escrita  de byte de configuração do controlador PS/2.
    // Reseta mouse (reset ? lento!)...
    // Espero pelo byte 0xaa que encerra a sequ?ncia
    // de reset!	
	//kbdc_wait(1);
	//outportb(0x64,0x60);  
    //kbdc_wait(1);
    //mouse_write(0xff);
    
	//#bubug: loop infinito.
	//while ( mouse_read() != 0xaa )
	//{
		//
	//};			
	
    //1
	//printf("ps2: resetando teclado. ...\n");
	//refresh_screen();		

	//+devemos configurar o modo escrita
	//+enviar o comando reset;
	//+ler as respostas.(#todo) fa, ff, 00	

	//reset KEYBOARD.
	//kbdc_wait(1);
	//outportb(0x60,0x60);  
	//kbdc_wait(1);
	//outportb(0x60,0xFF);
	//#bubug: loop infinito.
	//while ( kbd_read() != 0xaa )
	//{
		//
	//};			

	//printf("ps2: done\n");
	//refresh_screen();		
};
		
	
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
 ***************************************************************
 * MessageBox:
 *     Cria uma Window Frame e apresenta uma mensagem nela.
 * 
 * #Importante:
 *     Temos que considerar o propósito do message box e 
 * o design do message box.
 * Opções: tradicional, com elementos 3d ou mais flat e clean.
 *
 * IN: 
 * Window frame handle.
 * Message Box type. 
 * Title for the window frame.
 * Message string.
 *
 */
void 
MessageBox( struct window_d *parent_window,        
            int type,                        
		    char *title,                     
			char *string )                   
{	

/*

    ### cancelada. Essa rotina agora está na API em user mode. deletar essa função ###
	
	//Desktop support.
	int desktopID = (int) get_current_desktop_id();	 

	//Window support.
	
	struct window_d *hWnd;    //Window.
	struct window_d *pWnd;    //Parent.
	struct window_d *bWnd;    //Button.
	
	unsigned long WindowClientAreaColor;
	unsigned long WindowColor;
		
	// x and y
	// @todo centralizado: metade | um terço.
	// @todo: Pegar a métrica do dispositivo.
	unsigned long x  = (unsigned long) 20;       //deslocamento x
	unsigned long y  = (unsigned long) 20;       //deslocamento y
    unsigned long cx = (unsigned long) (800/2);  //largura   
    unsigned long cy = (unsigned long) (600/3);  //altura	
	
	//Button support.
	struct button_d *b1; 
	struct button_d *b2;
	int Button = 0;
	
	//icon.
	int Icon = 0;
	//...

	
	//No GUI.
	//?? deletar
	if( VideoBlock.useGui != 1 )
	{
		printf("MessageBox: No GUI\n");
	    return;	
	};
	
	if( (void *) gui->screen == NULL ){
	    return;
	};
	
	// Parent.
	if( (void *) parent_window == NULL )
	{
	    pWnd = gui->screen;
	}else{
	    pWnd = (void*) parent_window;
	};
	
	// *Importante: 
	// Checando se o esquema de cores está funcionando.
	
	if( (void *) CurrentColorScheme == NULL )
	{
		printf("MessageBox: CurrentColorScheme");
		die();
	}else{
		
		if( CurrentColorScheme->used != 1 || 
		    CurrentColorScheme->magic != 1234 )
		{
		    printf("MessageBox: CurrentColorScheme validation");
		    die();			
		};
		//Nothing.
	};
	
	// Colors: background and client area.
	WindowColor = CurrentColorScheme->elements[csiWindowBackground];  
	WindowClientAreaColor = CurrentColorScheme->elements[csiWindow];  	
	
	// # Create Window #
	
frame:
    
	//  ## type ##

    //@todo: Criar definições de tipos de message boxs.(enum)
	//@todo: Criar um tipo light.
	
	//Obs: Por enquanto para todos os tipos de messagebox 
	// estamos usando o mesmo tipo de janela.
	switch(type)
	{	
	    // Com botão, considera o título.
	    case 1:
		    Button = 1;
			//janela tipo simples.
	        hWnd = (void*) CreateWindow( WT_SIMPLE, 0, 0, title, 
			                x, y, 
							cx, cy, 
							pWnd, desktopID, 
							WindowClientAreaColor, WindowColor); 
		    break;
			
		// Sem botão, considera o título.	
	    case 2:
		    Button = 0;
	        hWnd = (void*) CreateWindow( WT_POPUP, 0, 0, title, 
			                x, y, 
							cx, cy, 
							pWnd, desktopID, 
							WindowClientAreaColor, WindowColor); 
	        break;
			
		// Com botão, Título de alerta.	
	    case 3:
		    //janela de aplicativo.
	        Button = 1;
			hWnd = (void*) CreateWindow( WT_OVERLAPPED, 0, 0, "Alert", 
			                x, y, 
							cx, cy, 
							pWnd, desktopID, 
							WindowClientAreaColor, WindowColor); 
	        break;
			
		//Com botão, título de mensagem do sistema.	
	    case 4:
		    Button = 1;
	        hWnd = (void*) CreateWindow( WT_OVERLAPPED, 0, 0, "System Message", 
			                x, y, 
							cx, cy, 
							pWnd, desktopID, 
							WindowClientAreaColor, WindowColor); 
	        break;
			
		//Tipo negligenciado. Usamos o formato padrão.	
		default:
		    Button = 1;
	        hWnd = (void*) CreateWindow( WT_OVERLAPPED, 0, 0, "Error", 
			                x, y, 
							cx, cy, 
							pWnd, desktopID, 
							WindowClientAreaColor, WindowColor); 
		    break;
	};
	
	
	// ## Window ##
	
	if( (void *) hWnd == NULL )
	{
	    printf("MessageBox: hWnd \n");
		die();
	}else{   
	
	    //Registrar e ativar.
		RegisterWindow(hWnd);
        set_active_window(hWnd);
		
	    //Configurando qual vai ser a janela atual.
	    CurrentWindow = (void *) hWnd;
	    //current_window ?? id ?? hWnd->id
	
	    //Habilitando o procedimento de janela do message box.
	    SetProcedure( (unsigned long) &MessageBoxProcedure );			
		
		//Setar foco.
		//Quando um controle recebe o foco 
		//Os eventos de input deverão ser 
		//tratados pelo procedimento de janela do controle.
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
	
drawString:
	draw_text( hWnd, 
	    1*(cx/16), 
		1*(cy/3), 
		COLOR_WINDOWTEXT, 
		string );

	//
    // Button: 
	//    (Um botão dentro da client area.)
    //    @todo: É preciso criar um botão do tipo janela.
	//           para colocar foco na janela.
	//
	// Obs: A quantidade de botão vai depender do tipo. 
	//
drawButton:	

    //#bugbug:
	//Aqui estamos apenas desenhando o botão, mas precisamos 
	//criar uma janela filha do tipo botão.
    if(Button == 1)
	{
		//@todo: Criar uma janela do tipo botão para setar o foco.
        //       Pegar o tamanho da string para definir o tamanho do botão.
		
        
		bWnd = CreateWindow( WT_BUTTON, 1, 1, " Close ", 
	               3*(cx/4), 2*(cy/3), 
			       64, 36,									  
		           hWnd, 0, (unsigned long) COLOR_TERMINAL2, (unsigned long) COLOR_TERMINAL2);	
		RegisterWindow(bWnd);		
		
		//b1 = (void*) draw_button( hWnd, 
		//                 "Close", 
		//				 1, 
		//				 3*(cx/4), 
		//				 2*(cy/3), 
		//				 64, 
		//				 36, 
		//				 COLOR_TERMINAL2 );
		//				 
		//if((void*) b1 == NULL )
		//{
		//	printf("button 1 fail\n");
		//}
		
		//b2 = (void*) draw_button( hWnd, "Close", 1, 12*(cx/16), 8*(cy/16), 48, 24, COLOR_BLACK);		
		//if((void*) b2 == NULL ){
		//	printf("button 2 fail\n");
		//}
		
	    //   
	    // @todo: FOCO NO BOTÃO !!!
	    //
		
		//SetFocus(??);
	};
	
 	
	//
	// ?? Continua ...
	//	
	
done:
    refresh_rectangle( x, y, cx, cy );
	return;
	
*/
};


/*
 **************************************************
 * MessageBoxProcedure:
 *     O procedimento padrão de message box.
 */																
unsigned long 
MessageBoxProcedure( struct window_d *window, 
                     int msg, 
   				     unsigned long long1, 
					 unsigned long long2 )
{
	
/*
    ### cancelada. Essa rotina agora está na API em user mode. deletar essa função ###
	
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
				//Test.
				case VK_F1:
				    //DestroyWindow(window);
                    break;
					
                //case VK_F2:
				    //Nothing.
				//	break;
									
				default:
				    return (unsigned long) 0;
				    break;
		    };              
        break;
		
	    case MSG_SYSKEYUP:
		   return (unsigned long) 0; 
           break;
		
        //@todo case command .. button ??
		
		default:
		    return (unsigned long) 0;
            break;		
	};
	
	
done:
	//Refresh screen. 
	//?? deletar.
	if(VideoBlock.useGui == 1){
	    refresh_screen();
	};	
	
	*/
	
	return (unsigned long) 0;
};

/*
?? Pra quê ??
int messageboxInit()
{}
*/

//
// End.
//

