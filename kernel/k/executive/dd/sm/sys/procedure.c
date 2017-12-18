/*
 * File: executive\dd\sm\sys\procedure.c
 *
 *                   
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
 * system_procedure:
 *     Procedimento do sistema.
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
    //debug!
	//printf("system_procedure: msg={%d} long1={%d}\n", msg, long1);  
	
	int AltStatus;
	int CtrlStatus;
	int ShiftStatus;
	//...
	

	//Get status.
	AltStatus = (int) get_alt_status(); 
	CtrlStatus = (int) get_ctrl_status();	
	//ShiftStatus = (int) get_shift_status();
	//...
	
	// ??
	// E SE O HANDLE DE JANELA FOR NULL ??
	// ENTÃO O PROCEDIMENTO DE JANELA NÃO PODERÁ ATUAR SOBRE JANELA NENHUMA.
	// OBS:
	//
	
	//janela de teste.
	struct window_d *xxxx;
	
	
	void *buff;
	
    switch(msg)
    { 
        /*
         ## Não tratar digitações normais ## 		
        case MSG_KEYDOWN:
            //#cancelado.
		break;
		*/
          
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
				     					
					//teste
					//devemos enviar para o shell a mensagem command .. avisando que o botão foi clicado ..
					// que estamos selecionado a opção de mostrar o menu de aplicativos.
					/*
			        if(AltStatus == 1)
					{ 
					    xxxx = (void*) windowList[window_with_focus];
						if( (void*) xxxx != NULL ){
						    //@todo xxxx->
					        xxxx->msg = MSG_COMMAND; 
					        xxxx->long1 = BN_CLICKED; 
					        //xxxx->long2 =  
						}
						break;
					};*/
					
					//if(AltStatus == 1){ window_with_focus = 1; break;};
					//if(CtrlStatus == 1){ active_window = 1; break;};
			        //if(ShiftStatus == 1){ break;}; 
					if(VideoBlock.useGui == 1){ 
					    procedureHelp();
                        break;						
					};
					//ShowUserInfo(0);    //Mostra o usuário 0, default.
                    break;
					
				
				//Kernel info.	
                case VK_F2:
				
					//teste
					//devemos enviar para o shell a mensagem command .. avisando que o botão foi clicado ..
					// que estamos selecionado a opção de mostrar o interpretador de comandos.

				
					//if(AltStatus == 1){ window_with_focus = 2; break;};
					//if(CtrlStatus == 1){ active_window = 2; break;};
			        //if(ShiftStatus == 1){ printf("shift_F2\n"); break;}; 				
				    
					//Obs: Não usa janelas, isso não mudará o foco.
					backgroundDraw(COLOR_BACKGROUND);
					KiInformation();
                    //show_process_information();    //Test.
                    //ShowUserInfo(0);  //#bugbug
                    //ShowUserInfo(1); 	 //#bugbug
                    //fs_check_disk();					
                    //... @todo: Testar mais coisa aqui.					
                    break;
				
	
                //CPU info. 				
                case VK_F3: 
					//if(AltStatus == 1){ window_with_focus = 3; break;};
					//if(CtrlStatus == 1){ active_window = 3; break;};
			        //if(ShiftStatus == 1){ printf("shift_F3\n"); break;};
				    //maximizar a janela ativa
				    //Obs: Não usa janelas, isso não mudará o foco.
					show_cpu_intel_parameters();					
                    break;
					
				//Window tests.	
                case VK_F4:
					if(AltStatus == 1){ 
					    closeActiveWindow(); 
						AltStatus = 0;
						break;
					};
					//if(CtrlStatus == 1){ active_window = 4; break;};
			        //if(ShiftStatus == 1){ printf("shift_F4\n"); break;};
				    
					//Mostra informações sobre as jnaelas.
					//gramado/gui/window.c
					windowShowWindowList();  
					//MaximizeWindow(struct window_d *window); //minimizar a janela ativa 
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
					
					
				    testingFrameAlloc();
					
				    //init_clock(); //clock information
					//get_cmos_info();
					//printf( (const char*) stdout->_ptr );
				    
					//printf("F6: Testando carregar arquivo ...\n");
					//procedureMakeTests();
					
					//Obs: Não usa janelas, isso não mudará o foco.
					//windowShowWWFMessageBuffers();
					
					//printf("F6: Testando linkar um driver ...\n");
					//procedureLinkDriverTest();
					break;
				
                //Testing Message Box.				
				case VK_F7:
					//if(AltStatus == 1){ window_with_focus = 7; break;};
					//if(CtrlStatus == 1){ active_window = 7; break;};
			        //if(ShiftStatus == 1){ printf("shift_F7\n"); break;};
				    //pertence ao desktop,tipo 1, string.
				    if(VideoBlock.useGui == 1){
						//isso cria uma janela, mudando o foco atual.
					    MessageBox(gui->screen, 1, "F7:","Testing Message Box");
					};
					break;
					
				//Cls.	
				case VK_F8:
					//if(AltStatus == 1){ window_with_focus = 8; break;};
					//if(CtrlStatus == 1){ active_window = 8; break;};
			        //if(ShiftStatus == 1){ printf("shift_F8\n"); break;};
					
					//Obs: Não usa janelas, isso não mudará o foco.
					backgroundDraw(COLOR_BLACK);
					
					//Testando repintar o background.
					//resize_window(gui->background, gui->background->width, gui->background->height);
					//redraw_window(gui->background);
					break;
				
                //Reboot.  				
				case VK_F9:
					//if(AltStatus == 1){ window_with_focus = 9; break;};
					//if(CtrlStatus == 1){ active_window = 9; break;};
			        //if(ShiftStatus == 1){ printf("shift_F9\n"); break;};
                    backgroundDraw(COLOR_BACKGROUND);
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
					//show_process_information();
					//show_thread_information();					
				    
					//aumentando gradativamente uma janela de pouco em pouco.
					xxxx = (void*) windowList[6];
					xxxx->width  -= 20;
					xxxx->height -= 20;
					resize_window(xxxx, xxxx->width, xxxx->height);
					redraw_window(xxxx);					
					
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
					xxxx = (void*) windowList[6];
					xxxx->width  += 20;
					xxxx->height += 20;
					resize_window(xxxx, xxxx->width, xxxx->height);
					redraw_window(xxxx);
					
					break;
					
				//Control menu.	
				case VK_F12:
					//if(AltStatus == 1){ window_with_focus = 12; break;};
					//if(CtrlStatus == 1){ active_window = 12; break;};
				    //procedureGrid();
					
					//testando informaçõe sobre os processos.
					show_process_information();
					
					//testando informações sobre as threads.
					show_thread_information();
					
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
					
					break;
				
                //Mudar o foco de entrada pra próxima janela de uma lista.				
                case VK_TAB:
				
				    //circula até errar.
				    window_with_focus++;
					if( (void*) windowList[window_with_focus] == NULL ){
						window_with_focus = 1;
					}
				    //windowSwitchFocus();
					
					//if(AltStatus   == 1)
					//{ 
					    //window_with_focus++;
                        //if(	window_with_focus > 9 ){
						//	window_with_focus = 1;
						//}					
						//break;
					//};
					
				    break;
					
                // Nothing for now!  				
                case VK_LMENU:    break;
                case VK_LCONTROL: break;
                case VK_LSHIFT:   break;
                //default: break;				
		    };              
        break;
		
		/* ## Teclas do sistema interceptadas pelo kernel ## */  
		/*
		case MSG_SYSKEYUP: 
            switch(long1)  
            {
				//0x5B.
                //Left WinKey system keyup. 
                //#super.
				case VK_LGRAMADO:
                    procedureGrid();  //Grid de botões usado pelo kernel.				
				break; 		
            };          
        break;
		*/
		
        /*		
        case MSG_DESTROY:		
            //destroy 
        break;
         */

		// Essa categoria é para receber mensagens
        //enviadas para o console para gerenciamento do sistema.
        //como desligamentos, inicializações, reboot ...		
        case MSG_CONSOLE_COMMAND:
		    switch(long1)
			{
				case MSG_CONSOLE_SHUTDOWN:
				    systemShutdown();
				    break;
				case MSG_CONSOLE_REBOOT:
				    systemReboot();
                    break;				
			    default:
				    break;
			};
			break;
		 
        //Continua ... Create ... Close ...		
    
	
	    //
		// Aqui provavelmente estamos com teclas de digita~çao.
		// então não precisamos efetuar o refresh_screen() deixando isso 
		// para o procedimento de janela do aplicativo
		//
		
	    //Nothing.
	    default:    
		    return (unsigned long) 0;
			break;
	};
	
	
    //Done.
done:
	if(VideoBlock.useGui == 1){
	    refresh_screen();
	};
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
void SendMessage( struct window_d *window, 
                  int msg, 
				  unsigned long long1, 
				  unsigned long long2 )
{
    unsigned long Old;

    if( (void *) window == NULL){
	    return;
	};
	
	//Salva o procedimento antigo.
	Old = (unsigned long) g_next_proc;
	
	//Usa o procedimento da janela.
	g_next_proc = (unsigned long) window->procedure;
	
	//@todo Check limits.
	if( (unsigned long) g_next_proc == 0 ){
		g_next_proc = (unsigned long) Old;
		return; 
	}else{
	    //Send.
        system_dispatch_to_procedure(window, msg, long1, long2);
		return;
	};
	
	//Se tudo deu errado, não envia nada e volta a usar o antigo.
	g_next_proc = (unsigned long) Old;
	return;
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
	if(VideoBlock.useGui == 1){
	    //refresh_screen();
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
	
	printf("procedureMakeTests:\n");
	
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

	printf("procedureMakeTests: done.\n");
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
		printf("procedureGrid: FAIL\n");
	}
	return;
};


//
// End.
//

