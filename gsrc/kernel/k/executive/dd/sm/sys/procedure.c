/*
 * File: sm\sys\procedure.c
 *
 *     ****   Central de diálogo.   ****
 *
 * A qui ficarão todos os diálogos para conversar com os módulos do kernel base.
 * Eles serão chamados de 'dialog' ou 'procedure'. 
 *
 * O PROCEDIMENTO NUNCA DEVE SER TROCADO, SEMPRE SERÁ O PROCEDIMENTO DO SISTEMA
 * QUANDO HOUVER UMA MENSAGEM ENVIADA PARA OUTRO PROCEDIMENTO, A MENSAGEM DEVE SER
 * COLOCADA NA ESTRUTURA DA JANELA ATIVA E AVISAR A THREAD E O PROCESSO SOBRE A MENSAGEM.
 * A THREAD PRINCIPAL DO PROGRAMA PEGARÁ AMENSAGEM E PASARA PARA O SEU PROCEDIMENTO.
 *
 * Obs: As teclas de F1 à F5 poderiam testar rotinas referentes às camadas
 *      respectivas. F1 testa rotinas de K1 e asem por diante.
 *      As rotinas de K0 seriam testadas de outra forma.
 *
 * Descrição:
 *     Procedimento de janela default, em kernel mode.
 *     Trata mensagens de sistema, como WIN KEY.
 *     Todas as tarefas são tratadas por esse procedimento padrão, 
 *     ao menos que inicializem seu próprio procedimento, ou um mix das 
 * duas coisas.
 *
 * OBS: 
 *     procedure.c está em hal, porque recebe intervenções de hardware
 * não importando a arquitetura.
 *
 * Histórico:
 *     Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *     Versão 1.0, 2016 - Aprimoramento geral das rotinas básicas.
 *     //...
 */ 
 
#include <kernel.h>


extern int alt_status;
extern int ctrl_status;
extern int shift_status;
extern int capslock_status;
extern int numlock_status;
extern int scrolllock_status;
//...

//
// Variáveis internas.
//

//unsigned long procedureCurrentProcedure;
//...

//
// Protótipos de funções internas.
//

//Realiza testes diferentes usando o procedimento do sistema.
void procedureMakeTests();
void procedureLinkDriverTest(); // testando linkar um driver ao sistema operacional
void procedureWindowWithFocusTest();
void procedureGrid();


 


/*
 * ldisc_dialog:
 *     Procedimento de dialogo usado para a manipulação de 
 * eventos de teclado.
 *     esse procedimento deve ser chamado quando o sistema 
 * ou algum processo deseja interagir com o driver de teclado 
 *  ?? planejando a funcionalidade desse diálogo ??
 */
unsigned long ldisc_dialog( struct window_d *window, 
                            int msg, 
							unsigned long long1, 
							unsigned long long2 ) 
{
	//cuidado
	//ponteiro para um buffer em user mode.
	unsigned long *buffer;
	
	if( (void*) window == NULL ){
		return (unsigned long) 0;
	}
	
	if( window->used != 1 || window->magic != 1234 ){
		return (unsigned long) 0;
	}
	
	switch(msg)
	{
	    case LDISC_NULL:
		    window->long1 = 0;
			window->long2 = 0;
	        break;
	
        case LDISC_GET_ALT_STATUS:
		    window->long1 = (unsigned long) keyboardGetKeyState(VK_LMENU);		
	        break;
		
	    case LDISC_GET_CTRL_STATUS:	
		    window->long1 = (unsigned long) keyboardGetKeyState(VK_LCONTROL);		
            break;
		
	    case LDISC_GET_SHIFT_STATUS:	
		    window->long1 = (unsigned long) keyboardGetKeyState(VK_LSHIFT);		
		    break;
		
	    case LDISC_GET_WINKEY_STATUS:	
		    window->long1 = (unsigned long) keyboardGetKeyState(VK_LWIN);		
		    break;

	    case LDISC_GET_CAPITAL_STATUS:	
		    window->long1 = (unsigned long) keyboardGetKeyState(VK_CAPITAL);		
		    break;

	    case LDISC_GET_NUMLOCK_STATUS:	
		    window->long1 = (unsigned long) keyboardGetKeyState(VK_NUMLOCK);		
		    break;	

	    //case LDISC_GET_SCROLLLOCK_STATUS:	
		//    window->long1 = (unsigned long) keyboardGetKeyState(VK_SCROLLOCK);		
		//    break;

        //use long1 como mensagem
        case LDISC_CHANGE_MESSAGE1:
		    window->msg = (int) window->long1;
		    break;

		//use long2 como mensagem	
        case LDISC_CHANGE_MESSAGE2:
		    window->msg = (int) window->long2;
		    break;
			
		//pega a próxima mensagem da fila fifo. circular.
		//case LDISC_GET_NEXT_MESSAGE:
            //window->msg = (int) ??;
			//window->long1 = (unsigned long) ??; 
			//window->long2 = (unsigned long) ??; 
		    //break;

		//pega o próximo scancode da fila fifo. circular.	
        //case LDISC_GET_NEXT_SCANCODE:
        //    window->long1 = (unsigned long) ??;
        //    break;  			
			
		//...
		
		//#importante:
		//#bugbug ?? Cuidado com a pagefault.
		//Um endereço em usermode espera pelos 4 argumentos da mesagem.
		//case LDISC_RECEIVE_MESSAGE:
        //    buffer = (unsigned long*) long1;
		//	buffer[0] = ??;  //hwnd 
		//	buffer[1] = ??;  //msg
		//	buffer[2] = ??;  //long1
		//	buffer[3] = ??;  //long2
		//    break;
			
			
		//a estrutura recebe os valores dos argumentos.	
		case LDISC_LOAD_ARGS:
		    window->msg = (int) msg;
            window->long1 = ( unsigned long ) long1;
            window->long2 = ( unsigned long ) long2;
            break;
 			
	    default:
            return (unsigned long) 0;
		    break;
    };	
	
done:	
    return (unsigned long) 0;	
};


/*
 *O procedimento de janela do (terminal.)
 */
unsigned long terminal_dialog( struct window_d *window, 
                               int msg, 
							   unsigned long long1, 
							   unsigned long long2 ) 
{
    //#suspenso esse diálogo.
	//repensando ele.
    return 0;	
};


/*
 * system_procedure:
 *     Procedimento de janela da janela com o foco de entrada ... (edit box.)
 *     Procedimento de janela default.
 *     
 * OBS: Existe uma relação grande entre control menus e o procedimento do
 * do sistema. Pois o procedimento do menu deve passar boa parte das mensagens
 * para serem tratadas pelo procedimento do sistema. 
 *
 * ?? QUAL JANELA É AFETADA POR ESSE PROCEDIMENTO ??
 *    É IMPORTANTE OBSERVAR O HANDLE DE JANELA PASSADO VIA ARGUMENTO.
 *
 * OBS: ESSE PROCEDIMENTO É INVOCADO POR 'ldisc.c' NA ROTINA LINEDISCIPLINE(..)
 *      POR ENQUANTO ESTÁ PASSANDO UM HANDLE DE JANELA NULO. 
 *
 */
unsigned long system_procedure( struct window_d *window, 
                                int msg, 
								unsigned long long1, 
								unsigned long long2) 
{ 	
	//
	// @todo: *importante:
	//        Não rpecisa dar refresh_screen para todos os casos.
	//        Cada caso é diferente ... 
	//        ?? Quem deve chamar esse refresh dos elentos gráficos ??
	//        O aplicativo ?? acionando a flag através de ShowWindow por exemplo??
	//
	
	
	//debug!
	//printf("system_procedure: msg={%d} long1={%d}\n", msg, long1);  
	
	void *buff;
	
	int AltStatus;
	int CtrlStatus;
	int ShiftStatus;
	//...
	
	//usado no refresh_rectangle
	//unsigned long saveX, saveY;
	

	//Get status.
	AltStatus = (int) get_alt_status(); 
	CtrlStatus = (int) get_ctrl_status();	
	//ShiftStatus = (int) get_shift_status();
	//...
	

	//
	// Lidando com a janela com o foco de entrada.
	//


	unsigned long left; 
	unsigned long top;   
	unsigned long width; 
	unsigned long height; 		

	
	//janela de teste.
	struct window_d *xxxx;
	
	//struct window_d *w;
	

	//
	// Checamos se a janela com o focod e entrada é válida.
	//
	
	//#bugbug isso está errado ... devemos pegar a janela passada por argumento 
	//poi o line discipline selecionou a janela com o foco de entrada.
	
	//w = (void *) windowList[window_with_focus];
	
	// Window With Focus !
	//window é a janela com o foco de entrada, obtita pelo ldisc.c 
	//e passada via argumento.
	if( (void*) window == NULL ){
	    printf("sm-sys-system_procedure: window");
        die();		
	}else{
	
	    //
	    // Configurando o cursor para ficar de acordo com a janela com o foco de entrda.
	    //
		
		//
		// @todo:
		// Aqui deveríamos apenas pegar o ponteiro para a estrutura 
		// de cursor que pertence a janela com o foco de entrada.
		//
	
	    //pegando as dimensões da janela com o foco de entrada.

		//left   = window->left;
	    //top    = window->top;
	    //width  = window->width;
	    //height = window->height;		
	
	    //
		// simular valores aqui para teste ... como 80 25
		//
		
		//g_cursor_left   = (window->left/8);
		//g_cursor_top    = (window->top/8) + 4;   //Queremos o início da área de clente.
		
		//g_cursor_right  = g_cursor_left + (width/8);
		//g_cursor_bottom = g_cursor_top  + (height/8);

		//100
		//a linha deve ser grande.
		//A linha pode ser maior que a janela.
		//g_cursor_right  = (800/8);
		//g_cursor_bottom = (600/8);

		
		//if( g_cursor_right == 0 ){
		//	g_cursor_right = 1;
		//}
		
        //if( g_cursor_bottom == 0 ){
		//	g_cursor_bottom = 1;
		//}		
		
		//cursor (0, mas com margem nova).
		//#bugbug ... isso reiniciaria o cursor a cada tecla pressionada.
		//g_cursor_x = g_cursor_left; 
		//g_cursor_y = g_cursor_top;  		
           
	
	    //...
	};

    //
    //*importante:
	// Desejamos que as teclas de controle sejam tratadas por esse 
	// procedimento mesmo que a janela seja do tipo terminal ...
	// pois as teclas de comtrole permite trocarmos a jenala com 
	// o foco de entrada sem fecharmos o terminal.
    //	
    
	switch(msg)
    { 
		//teclas de digitação.
		case MSG_KEYDOWN:
            switch(long1)
            {	
				// [ ENTER ]
				case VK_RETURN:
				    printf("\r");
					printf("\n");
					//input esta em stdio.c
					input( (unsigned long) long1);  
					goto done;
					break;
					
				//usando o scape para fechar a janela com o foco de entrada.
                case VK_ESCAPE:
				    alt_status = 0;
					ctrl_status = 0;
					shift_status = 0;
					//Mensagem para fechar a janela passada via argumento.
					//SendMessage(window,MSG_DEVELOPER,1,0);
					//CloseWindow(window);
                    KillFocus(window);
					goto done;				
				    break;
					
				//Obs: Não deve ser preocupação do desenvolvedor de aplicação 
				//incrementar o cursor quando pressiona a seta.
				//por isso vou tratálas aqui.
				
				//# bugbug problemas no 'i'.
				
				//case VK_RIGHT:	
				//    g_cursor_x++;
				//	break;
				
				//case VK_LEFT:
				//    g_cursor_x--;
				//    break;
					
				//case VK_DOWN:
				//    g_cursor_y++;
				//    break;
					
				//case VK_UP:
				//    g_cursor_y--;
				//	break;
				
				


                //o tab deve fazer parte das teclas de difitação. ??
                case VK_TAB:
					//if(AltStatus == 1){
                    //    //@todo: Chama uma rotina que muda a janela com o foco de entrada.						
					//	break;
					//};
					
					printf("\t");
					input( (unsigned long) long1);  
					goto done;
				    break;
                
				case VK_BACK:
				    g_cursor_x--;
					printf(" ");
					input( (unsigned long) long1);  
					goto done;
                    break;
					
				case VK_PAUSE:
                    if(CtrlStatus == 1){
					    KiInformation();	
					}
					goto done;
					break;				
				   					
					//Se for do tipo terminal as teclas de digitação se 
					//serão tratadas pelo procedimento de janelas do terminal.
					//para isso é só ir para o fim desse procedimento.
					//if( window->terminal == 1 ){
					//    goto do_terminal;	
					//}
						
					//
					// *importante:
					// Podemos imprimir nesse momento, pois a impressão está correta e 
					// deixarmos o input sem imprimir. O que parece ser normal, input
					// apenas por dentro do buffer.
					//
						
					//printf deve imprimir no caso de tab ou espaço...
					//input só vai mexer com o buffer
	
	                // Isso funciona, porque printf incrementa o cursor antes 
					// de imprimir o char no backbuffer. Tem caso que ele 
					// manipula o cursor e não imprime nada.
						
					// printf deveria imprimir na janela com o foco de entrada.
					// obs: printf usa o cursor do sistema. Para imprimir na janela temos 
					// que auterar o cursor do sistema para ficar com as dimensões da 
					// janela com o foco de entrada. shell.bin agradece.
					
					//#bugbug: Problemas com o cursor. Está saltando a cada 
					//caractere digitado. Mas o refresh funciona bem.
					
					//teste
					//#IMPORTANTE: ISSO FOI CANCELADO PORQUE A LIB EM USER MODE 
					//AGORA IMPRIME OS CARACTERES E FAZ O REFRESH DO CHAR.
					
					//printf("%c", (char) long1);
		            //refresh_rectangle( g_cursor_x*8, g_cursor_y*8, 8, 8 );
						
			        //
					// input:
					// Devemos nos certificar que input não imprima nada.
					//
								//teclas de digitação para o editbox.   
                
				default:	
					input( (unsigned long) long1);      //Coloca no stdin
					goto done;
                    break; 
            };		
			break;
          
		/* ## Teclas do sistema interceptadas pelo kernel ## */  
        case MSG_SYSKEYDOWN:                 
            switch(long1)	       
            {   
                //
				// As funções F1 à F12 são opções para o desenvolvedor.
				//
				
				//
				// Obs: Essa variáveis de estadus serão variáveis encapsuladas
				//      no driver de teclado. Para saber o valor delas
				//      tem que chamar uma função do driver. keyboard.c
				//
				
				//Obs: 
				// *Importante: Tem que chamar método pra pegar variável dentro de driver.
				 
				
				//Help. 
				case VK_F1:	
					procedureHelp();
				    //alt_status = 0;
					//ctrl_status = 0;
					//shift_status = 0;
                    //backgroundDraw(COLOR_BLACK);
					//printf("%s",stdin->_base);  //mostrar a entrada padrão.
					//refresh_screen();
                    
					//tentando indica qual janela está com o foco de entrada.
					//draw_text(window,0,0,COLOR_PINK,"*");
					//refresh_rectangle( window->left, window->top, 8, 8 );
					break;
					
				
				//Kernel info.	
                case VK_F2:
					KiInformation();
				    //alt_status = 0;
					//ctrl_status = 0;
					//shift_status = 0;
                    // backgroundDraw(COLOR_BLACK);
					//printf("%s",stdout->_base);  //mostrar a entrada padrão.
					//refresh_screen();
					break;
				
	
                //CPU info. 				
                case VK_F3: 
					show_cpu_intel_parameters();
				    //alt_status = 0;
					//ctrl_status = 0;
					//shift_status = 0;
                    // backgroundDraw(COLOR_BLACK);
					//printf("%s",stderr->_base);  //mostrar a entrada padrão.
					//refresh_screen();
					break;
					
				//Window tests.	
                case VK_F4:
					if(AltStatus == 1){ 
					    closeActiveWindow(); 
						alt_status = 0;
						goto done;
						break;
					};
					windowShowWindowList();  
					break;
				
				//Device Info.
				//Mostra informções sobre todos os dispositivos.
				//Igual ao gerenciador de dispositivos.
				case VK_F5:
					
					//if(AltStatus == 1){ window_with_focus = 5; break;};
					//if(CtrlStatus == 1){ active_window = 5; break;};
			        //if(ShiftStatus == 1){ printf("shift_F5\n"); break;};
				    //pci_info();     //PCI information.
				    
					//Obs: Não usa janelas, isso não mudará o foco.
					systemShowDevicesInfo();
					
					/*
					//testando chamar o bootloader na forma de módulo.
					asm (" pushl %eax ");
					asm (" pushl %ebx ");
					
					asm (" movl $0x12345678,  %eax "); //flag.
					
					asm (" movl $0x00021000,  %ebx "); //endereço do entrypoint do boot loader.
					asm (" call *%ebx "); 
					
					asm (" popl %ebx ");
					asm (" popl %eax ");
					*/
					
					//Test teclado scancode. (FUNCIONOU BEM)
					//Quando aciona esse status, o kernel mostra o scancode.
					//scStatus = 1;
					
					break;
				
                //Clock info./minishell				
				case VK_F6:
					//if(AltStatus == 1){ window_with_focus = 6; break;};
					//if(CtrlStatus == 1){ active_window = 6; break;};
			        //if(ShiftStatus == 1){ printf("shift_F6\n"); break;};
					
					//habilitando o cursor.
					//timer_cursor_used = 1;
					//timer_cursor_status = 0;
					
					
				    //testingFrameAlloc();
					
				    //init_clock(); //clock information
					//get_cmos_info();
					//printf( (const char*) stdout->_ptr );
				    
					//printf("F6: Testando carregar arquivo ...\n");
					//procedureMakeTests();
					
					//Obs: Não usa janelas, isso não mudará o foco.
					//windowShowWWFMessageBuffers();
					
					//printf("F6: Testando linkar um driver ...\n");
					//procedureLinkDriverTest();
					
					//Testando repintar o background.
					//resize_window(gui->background, gui->background->width, gui->background->height);
					//redraw_window(gui->background);	
                    //MaximizeWindow(struct window_d *window); //minimizar a janela ativa 					
					break;
				
                //Testing Message Box.				
				case VK_F7:
					MessageBox(gui->screen, 1, "F7:","Testing Message Box");
					goto done;
					break;
					
				//Cls. 
				//(reiniciar as configurações originais)	
				case VK_F8:
				    alt_status = 0;
					ctrl_status = 0;
					shift_status = 0;
                    //backgroundDraw(COLOR_BLACK);
					videoInit();
					//setar o foco ajuda a restaurar o input stdin para o procedimento de janela.
					SetFocus( gui->main );
					//kprintf está funcionando.
					//kprintf("F8: Testing kprintf ...\n");
					refresh_screen();
					goto done;	
					break;
				
                //Reboot.  				
				case VK_F9:
					systemReboot();
					break;				

				//Task Manager.	
				case VK_F10:
					//if(AltStatus == 1){ window_with_focus = 10; break;};
					//if(CtrlStatus == 1){ active_window = 10; break;};
			        //if(ShiftStatus == 1){ printf("shift_F10\n"); break;};
				    
					//KiShowThreadList(); //threadi.c
					//mostra_slots();  //threadi.c
					
					//@todo: abrir o gerenciador de tarefas.
					show_process_information();
					show_thread_information();					
				    
					//aumentando gradativamente uma janela de pouco em pouco.
					//xxxx = (void*) windowList[6];
					//xxxx->width  -= 20;
					//xxxx->height -= 20;
					//resize_window(xxxx, xxxx->width, xxxx->height);
					//redraw_window(xxxx);					
					//refresh_screen();
					break;
					
				//Program manager.
                //@todo: usar F11 para FULL SCREEN.				
				case VK_F11:				
					//if(AltStatus == 1){ window_with_focus = 11; break;};
					//if(CtrlStatus == 1){ active_window = 11; break;};
			        //if(ShiftStatus == 1){ printf("shift_F11\n"); break;};
					//printf("@todo Program manager.\n");
					//printf("F11\n");
					
					//aumentando gradativamente a janela de pouco em pouco.
					//xxxx = (void*) windowList[6];
					//xxxx->width  += 20;
					//xxxx->height += 20;
					//resize_window(xxxx, xxxx->width, xxxx->height);
					//redraw_window(xxxx);
					//refresh_screen();
					break;
					
					
				//case VK_F12:
					//if(AltStatus == 1){ window_with_focus = 12; break;};
					//if(CtrlStatus == 1){ active_window = 12; break;};
				    //procedureGrid();
					
					//testando informaçõe sobre os processos.
					//show_process_information();
					
					//testando informações sobre as threads.
					//show_thread_information();
					
					//Testando repintar todas as janelas seguindo a ordem list.
					//redraw_screen();
					
					//Teste de GC. 
					//Funcionando bem.
					//printf("F12: alocando ...\n");
					//buff = (void*) malloc(4*1024);
					//printf("F12: liberando ...\n");
					//free(buff);
					//printf("F12: testando GC ...\n");
					//gc();
					//printf("F12: OK\n");
					
 	
					//SystemMenu();
					//printf("@todo Control menu.\n");
					//@todo:control menu da area de trabalho.
					//MainMenu();
								
					//printf("time={%d}\n", get_time());
					//printf("date={%d}\n", get_date());
					
                    //Visualizando informações de memória obtidas através do rtc.
					//memoryShowMemoryInfo();
					
					//Testando limites na criação de componentes do /microkernel.
					//Ok, funcionou bem.
					//microkernelTestLimit();
					
					//Testando Limites na utilização de recursos do módulo pages.c.
					//??

					//Testando Limites na utilização de recursos do módulo memory.c.
					//??
					
					//Testando Limites na utilização de recursos do módulo window.c.
					//??
					
					//Testando imprimir mensagem na janela com o foco de entrada.
					//que no caso é a janela do desenvolvedor.
					//procedureWindowWithFocusTest();
					
					//drawScreenGrid();
					
					
					//repintar uma janela qualquer.
					
					
					//xxxx = (void*) windowList[4];
					//MaximizeWindow(xxxx);
					//redraw_window(xxxx);

					//xxxx = (void*) windowList[5];
					//replace_window(xxxx, 100, 100);
					//redraw_window(xxxx);

					//xxxx = (void*) windowList[6];
					//resize_window(xxxx, 100, 100);
					//redraw_window(xxxx);
				//	break;
				
				//caps lock keydown
				case VK_CAPITAL:
			        //Apenas percebe o status e efetua uma ação, 
					//mas não altera o status.
				    if(capslock_status == 1){ 
				        keyboard_set_leds(LED_CAPSLOCK);
					    break; 
				    };
				    break;
					
                // Nothing for now!  				
                case VK_LMENU:
                    if( alt_status == 1 ){ 
					    //todo 
					};				
				    break;
					
				// Nothing for now!	
                case VK_LCONTROL: 
				    if( ctrl_status == 1 ){ 
					    //todo
					};
					break;
                
				// Nothing for now!
				case VK_LSHIFT:   
				    if( shift_status == 1 ){ 
					    //todo.    
					}
				    break;
					
			    //Num Lock.	
		        case VK_NUMLOCK:
				    if(numlock_status == 1){
					    keyboard_set_leds(LED_NUMLOCK);  
					    break;
				    };
			        break;
					
			    //Scroll Lock.	
		        case VK_SCROLL:
				    if(scrolllock_status == 1){
		                keyboard_set_leds(LED_SCROLLLOCK);
					    break;
				    };
			        break;
					
                default: 
				    break;				
		    };              
        break;
		
		/* ## Teclas do sistema interceptadas pelo kernel ## */  
		
		case MSG_SYSKEYUP: 
            switch(long1)  
            {
				//0x5B.
                //Left WinKey system keyup. 
                //#super.
				//case VK_LGRAMADO:
                //    procedureGrid();  //Grid de botões usado pelo kernel.				
				//break;

                case VK_LWIN:
                case VK_RWIN:
				    //control menu.
					MessageBox(gui->screen, 1, "Win Key:","MSG_SYSKEYUP VK_LWIN or VK_RWIN");
                    break;
					
				//test.
				//control menu. (application)
                case VK_CONTROL_MENU:
				    //control menu.
					MessageBox(gui->screen, 1, "Control menu:","MSG_SYSKEYUP.VK_CONTROL_MENU");
                    break;
					
                default:
                    break;				
            };          
        break;
		

		// Essa categoria é para receber mensagens
        //enviadas para o console para gerenciamento do sistema.
        //como desligamentos, inicializações, reboot ...		
        //case MSG_CONSOLE:
		//case MSG_CONSOLE_COMMAND:
            //goto do_terminal;		
		//	break;
		 
        //Continua ... Create ... Close ...		
        //case MSG_CREATE:
		//    break;
		//case MSG_DESTROY:
	    //    break;
		//case MSG_CLOSE:
		    //#debug.
		    //Vamos tentar invalidar as janelas de diálogo.
			//Certamente não queremos fechar a janela gui->main.
	        //CloseWindow(window);
			//break;
		//case MSG_SETFOCUS:
	    //    break;
		//case MSG_KILLFOCUS:
	    //    break;
		//case MSG_PAINT:
	    //    break;
		
		//Dialogo especial:
		//Serve para funções provisórias usadas pelo desenvolvedor 
		//do sistema operacional.
		case MSG_DEVELOPER:
		    switch(long1)
			{
				//fechar message box em kernel mode.
				case 1:
				    CloseWindow(window);
				break;
				
				default:
				break;
			}
			break;

			
	    //
		// Aqui provavelmente estamos com teclas de digitação.
		// então não precisamos efetuar o refresh_screen() deixando isso 
		// para o procedimento de janela do aplicativo
		//
		
	    //Nothing.
	    default:    
		    //return (unsigned long) 0;
			break;
	};
	
	
    
do_terminal:
	//if(VideoBlock.useGui == 1){
	//    refresh_screen();
	//};
    //return (unsigned long) 0;	
	
	//
	// Chama o procedimento da janela terminal.
	// Se ajanela não for uma janela do tipo terminal isso irá retornar imediatamente.
	//
	//return (unsigned long) terminal_procedure( window, (int) msg, (unsigned long) long1, (unsigned long) long2 );
done:

   //
   // *importante:
   // Aqui devemos chamar o procedimento de janela da janela com o foco de entrada.
   // Pois bem, já mandamos a mensagem para fila de mensagens da janela com o foco
   // de entrada, então quando o aplicativo receber tempo de processamento ele irá  
   // processar a mensagem.
   //
   

    return (unsigned long) 0;
};  


/*
 * registra_procedimento:
 * @todo: Essa função deve ser modificada.
 *        O propósito dos argumentos é 
 *        receber o endereço de algum procedimento
 *        que precisa ser selecionado como atual.
 *        o novo nome pode ser algo como:
 *        xxx_SetProcedure(,,,)   
 *
 * arg1 - next procedure.
 * arg2 - 0
 * arg3 - 0
 *
 */
unsigned long registra_procedimento( unsigned long arg1, 
                                     unsigned long arg2, 
									 unsigned long arg3, 
									 unsigned long arg4 )
{
	SetProcedure(arg1);
	return (unsigned long) 0;
};


/*
 * SetProcedure:
 *     Determina qual vai ser o procedimento atual.
 *     Esse deve ser o procedimento da janela com o foco de
 *     entrada. Não necessariamente precisa jer a janela ativa,
 *     pois pode ser uma janela filha que esteja com o foc de entrada.
 *     Ou um ícone. Pois ícone também tem procedimento e recebe mensagens.
 *     Mas as mensagens enviada para ícones são diferentes das mensagens
 *     enviadas para janelas.
 */
void SetProcedure(unsigned long proc)
{
	//@todo: Checar limites.
	if( (unsigned long) proc == 0 ){
		return; 
	};
	
	//
	// A estrutura da janela com o foco de entrada pode ser
	// atualizada nesse momento. Ou ao menos conferir
	// se o endereço enviado por argumento corresponde
	// com o endereço do procedimento da janela com o foco de entrada.
	//
	
	
    g_next_proc = (unsigned long) proc;	
	return;
};


/*
 * SendMessage:
 *     Envia mensagem para o procedimento da janela
 *     indicada no argumento.
 *     É bem provável que a janela enviada por argumento
 *     seja a janela com o foco de entrada.
 *     
 *     @todo: Esse pode ser o formato padrão e envio de mensagens.
 *            Os processos podem trocar mensagens desse tipo
 *            atravéz de uma estrutura que contenha esses quatro 
 *            argumentos na forma de parâmetros. 
 */
unsigned long SendMessage( struct window_d *window, 
                  int msg, 
				  unsigned long long1, 
				  unsigned long long2 )
{
	return (unsigned long) system_procedure(window,msg,long1,long2);
};


/*
 * procedureHelp:
 *     Mensagem de ajuda ao usuário.
 */
void procedureHelp()
{ 
	struct window_d *hWindow; 		
	
	//Parent window.
	if( (void*) gui->main == NULL){
	    return;
	};
	
	unsigned long left   = gui->main->left;
	unsigned long top    = gui->main->top;
	unsigned long width  = gui->main->width;
	unsigned long height = gui->main->height;
	
	g_cursor_x = (left/8);
	g_cursor_y = (top/8); 
	
	//backgroundDraw(COLOR_BACKGROUND);
	
	//Create.
	hWindow = (void*) CreateWindow( 3, 0, VIEW_MAXIMIZED, "//KERNEL Help", 
	                                left, top, width, height, 
							        gui->main, 0, KERNEL_WINDOW_DEFAULT_CLIENTCOLOR, KERNEL_WINDOW_DEFAULT_BGCOLOR );     
	if( (void*) hWindow == NULL){
	    printf("procedureHelp:\n");
		return;
    }else{
		RegisterWindow(hWindow);
	};
	
//Coloca as mensagens na janela.
messages: 
	draw_text( hWindow, 8,  2*(height/20), 
	           COLOR_WINDOWTEXT, "F1 Help.");
    draw_text( hWindow, 8,  3*(height/20), 
	           COLOR_WINDOWTEXT, "F2 Kernel info.");
	draw_text( hWindow, 8,  4*(height/20), 
	           COLOR_WINDOWTEXT, "F3 CPU info.");
	draw_text( hWindow, 8,  5*(height/20), 
	           COLOR_WINDOWTEXT, "F4 Window tests.");
	draw_text( hWindow, 8,  6*(height/20), 
	           COLOR_WINDOWTEXT, "F5 Device info.");
	draw_text( hWindow, 8,  7*(height/20), 
	           COLOR_WINDOWTEXT, "F6 Clock info.");
	draw_text( hWindow, 8,  8*(height/20), 
	           COLOR_WINDOWTEXT, "F7 MessageBox.");
	draw_text( hWindow, 8,  9*(height/20), 
	           COLOR_WINDOWTEXT, "F8 Cls.");
	draw_text( hWindow, 8, 10*(height/20), 
	           COLOR_WINDOWTEXT, "F9 Reboot.");
	draw_text( hWindow, 8, 11*(height/20), 
	           COLOR_WINDOWTEXT, "F10 Task Manager.");
	draw_text( hWindow, 8, 12*(height/20), 
	           COLOR_WINDOWTEXT, "F11 Program manager.");
    draw_text( hWindow, 8, 13*(height/20), 
	           COLOR_WINDOWTEXT, "F12 Tests");
			   
			   

		
    //
    // Testing Status Bar
    //
    
	StatusBar( hWindow, "Esc=EXIT", "Enter=?" );
	
	
	//
	// @todo: Habilitar o procedimento de janela.
	//
		
//Done.
done:
	if(VideoBlock.useGui == 1)
	{    
		//@todo: 
		//Devemos dar o refresh somente da janela.
		refresh_screen();
	};
    SetFocus(hWindow);
    return;
};



/*
 * procedureLinkDriverTest:
 *     Testando linkar um driver ao sistema operacional.
 *     Obs: Essa rotina é um tipo de callout. Foi implementada usando um
 * iret, mas poderia bem ser um jmp.
 * Obs: Isse test  funcionou bem, implementar essa rotina definitivamente.
 */
void procedureLinkDriverTest()
{
	//
	// Saltando para a thread idle:
	//
	
	//
	// Obs: Estamos forçando. estamos atropelando o escalonamento
	// e thread e saltando para a thread idle para testar a nossa tentativa
	// de inicializar o processo idle tambem com driver, alem de ser um processo cliente.
	//
	
	//
	// estamos usando o mesmo método que saltamos para a thread idle pela primeira vez.
	//
	
	
	//
	// @todo: Poderiamos ter aqui opções de filtro, que faria a rotina falhar e retornar 
	// no caso de reprovar alguma coisa.
	//
	//goto: failReturn;
	
	printf("iret\n");
	
    asm volatile(" cli \n"   
                 " mov $0x23, %ax  \n" 
                 " mov %ax, %ds  \n"
                 " mov %ax, %es  \n"
                 " mov %ax, %fs  \n"
                 " mov %ax, %gs  \n"
                 " pushl $0x23            \n"    //ss.
                 " movl $0x0044FFF0, %eax \n"
                 " pushl %eax             \n"    //esp.
                 " pushl $0x3200          \n"    //eflags.
                 " pushl $0x1B            \n"    //cs.
                 " pushl $0x00401000      \n"    //eip. 
				 
				 " mov $1234, %edx  \n"          //Obs: Acrescentamos essa flag.
												 
                 " iret \n" );
				 
				 
//failReturn:
    return;	
};


// Função interna para realiza testes usando o procedimento do sistema.
void procedureMakeTests()
{
	
     //
	 // Outro teste.
	 //
	 
	/*
    printf("Testando desalocar..\n");	
	void *buff;
	buff = (void*) malloc( sizeof(32) );
    //~~~~
	//show_memory_structs();//mostra apos alocar
	//~~~~
	free(buff); //zera o penultimo indice da lista.
	//~~~~
	buff = (void*) malloc( sizeof(32) );
	//...
	show_memory_structs();//mostra apos desalocar
	//~~~~	
	return;
	*/
	
	
	//
	// @todo: #bugbug: A interruoção de timer bagunça tudo.
	//
	
	
	//unsigned long buff;
	// Desabilita taskswitch
	
	taskswitch_lock();
	scheduler_lock();	
	
	printf("sm-sys-procedureMakeTests:\n");
	
	//Fluxo padrão. (file structure)
	stdout = (void*) malloc( sizeof(FILE) );
	if( (void*) stdout != NULL )
	{
		//File size.
		//buff = (unsigned long) malloc( sizeof(4096) );
		stdout->_ptr = (char*) malloc( sizeof(4096) );
		
		if(stdout->_ptr == 0)
		{
			printf("erro 1\n");
			goto done;
		}
		fsLoadFile("INIT    TXT", (unsigned long) stdout->_ptr);
		printf("%s\n", (const char*) stdout->_ptr);
		//printf("~~%s \n",stdout->_ptr);
		//free(stdout->_ptr);
		goto done;
		//refresh_screen();
		//return;
		//while(1){}
	}
	else
	{
		//printf("fail.\n");
		printf("erro2\n");
		goto done;
		//refresh_screen();
		//return;
		//while(1){}
	};
	
	

	
done:

    //
	// Testando listar os arquivos.
	//
    fsListFiles(0);

	printf("sm-sys-procedureMakeTests: done\n");
    //Reabilita task switch.
	scheduler_unlock();
	taskswitch_unlock();



	
	//refresh_screen();
	//while(1){}
	return;
}

/*
 * Configura o procedimento atual.
void procedureSetProcedure(unsigned long address)
{};
*/

/*
 * Obtem o procedimento atual.
void procedureGetProcedure()
{
    return (unsigned long) x;	
};
*/

/*
 * Invocar um procedimento que está em user mode
 e pertence à um processo cliente.
 Invocar da mesma forma que o kernel inicializa um driver,
 através de iret diretamente na rotina.
 o procedimento de janel retornará utilizando uma system call.
 
void *procedureInvokeUserModeProcedure()
void *procedureInvokeUserModeProcedure()
{
	
}
*/


void procedureWindowWithFocusTest()
{
	//
	// ****  TESTANDO A JANELA DO desenvolvedor ****
	// ****  SERÁ A ÚNICA JANELA EM PRIMEIRO PLANO POR ENQUANTO ****
	// **** A ÚNICA COM O FOCO DE ENTRADA  ****
	//
					
	//
	// #bugbug ... essa rotina está travando ...
	//
					
	//escrevendo fora da janela
	printf("F12:Fora.\n");
	//refresh_screen();
					
	if( (void*) WindowWithFocus == NULL ){
	    printf("F12: WindowWithFocus");
	    refresh_screen();
		while(1){}
	}

	if( (void*) WindowWithFocus != gui->DEVELOPERSCREEN ){
		printf("F12: WindowWithFocus != gui->DEVELOPERSCREEN");
		refresh_screen();
		while(1){}
	}
					
	//Esperamos que a ultima janela a receber o foco tenha sido
	//a janela do desenvolvedor...
	//
	WindowWithFocus->cursor_x = 0;
	WindowWithFocus->cursor_y = 0;
	//WindowWithFocus->left  = 0;
	//WindowWithFocus->top = 0;
					
	g_cursor_x = (unsigned long) (WindowWithFocus->left);
	g_cursor_y = (unsigned long) (WindowWithFocus->top);
	printf("F12: [left/top]\n");

	//g_cursor_x = (unsigned long) (WindowWithFocus->right);
	//g_cursor_y = (unsigned long) (WindowWithFocus->top);
	//printf("F12: [right/top]\n");

	//g_cursor_x = (unsigned long) (WindowWithFocus->left);
	//g_cursor_y = (unsigned long) (WindowWithFocus->bottom);
	//printf("F12: [left/bottom]\n");

	//g_cursor_x = (unsigned long) (WindowWithFocus->right);
	//g_cursor_y = (unsigned long) (WindowWithFocus->bottom);
	//printf("F12: [right/bottom]\n");
	
	//...
	
	return;				
};


/* @todo; Criar um grid parecido com o outro, mas que será gerenciado pelo
 procedimento de janelas do sistema.
*/ 
void procedureGrid()
{
	int Status;
	
	Status = grid(GRID_VERTICAL);
	if(Status == 1){
		printf("sm-sys-procedureGrid: grid\n");
	}
	return;
};


//
// End.
//

