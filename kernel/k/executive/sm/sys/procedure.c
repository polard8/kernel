/*
 * File: procedure.c
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


/*
 * system_procedure:
 *     Procedimento do sistema.
 *     Procedimento de janela default.
 *     
 * OBS: Existe uma relação grande entre control menus e o procedimento do
 * do sistema. Pois o procedimento do menu deve passar boa parte das mensagens
 * para serem tratadas pelo procedimento do sistema. 
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
	//...
	

	//Get status.
	AltStatus = (int) get_alt_status(); 
	CtrlStatus = (int) get_ctrl_status();	
	//...
	
	
    switch(msg)
    { 
        /*	
        case MSG_KEYDOWN:
            switch(long1)
            {
				//@todo: incluir o [enter].
				
                //@todo: fazendo o driver de teclado.
	            //putchar( (int) long1 );
				
				//@todo: O escape poderia reiniciar algumas variáveis
				//       zerar algum buffer ... etc.
				case VK_ESCAPE:
                    SetProcedure( (unsigned long) &system_procedure);				
					//...
					break;
				   
				   
				//
                // Quando qualquer tecla que não é do sistema é pressionada
				// colocamos em um buffer para depois comparar com um comando.
				// Obs: input(.) em stdio.c.
                //
				
                default:
					//my_buffer_char_blt( 0, 0, COLOR_TEXT, long1); //funciona.
				    //putchar( (int) long1);
					
					//Salva num buffer pra comparar depois.
					//@todo: Salvando em prompt[], porém o buffer da linha
					// na disciplina de linha deve apontar para esse buffer.
					input( (unsigned long) long1 );   
					goto done;
					//refresh_screen();
					//return (unsigned long) 0;   //retorna pois a tela atualizando 2 vezes
					break; 
            };
        break;
		*/
          
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
				 
				//Help. 
				case VK_F1:
					//AltStatus = (int) get_alt_status(); 
					//CtrlStatus = (int) get_ctrl_status();
					//if(AltStatus == 1){ break;};
					//if(ctrl_status  == 1){ break;};
			        //if(shift_status == 1){ break;}; 
                    if(VideoBlock.useGui == 1){ procedureHelp(); break; };
					//ShowUserInfo(0);    //Mostra o usuário 0, default.
                    break;
					
				//Kernel info.	
                case VK_F2:
				    //AltStatus = (int) get_alt_status(); 
					//if(alt_status   == 1){ break;};
					//if(ctrl_status  == 1){ MainMenu(); break;};
			        //if(shift_status == 1){ printf("shift_F2\n"); break;}; 				
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
                    //AltStatus = (int) get_alt_status();  				
					//if(alt_status   == 1){ printf("alt_F3\n"); break;};
					//if(ctrl_status  == 1){ printf("ctrl_F3\n"); break;};
			        //if(shift_status == 1){ printf("shift_F3\n"); break;};
				    //maximizar a janela ativa
				    show_cpu_intel_parameters();					
                    break;
					
				//Window tests.	
                case VK_F4:
				    //AltStatus = (int) get_alt_status(); 
				    //if(alt_status   == 1){ printf("alt_F4\n"); break;};
					//if(ctrl_status  == 1){ printf("ctrl_F4\n"); break;};
			        //if(shift_status == 1){ printf("shift_F4\n"); break;};
				    show_window_list();     //#ocupa muito espaço na tela.
					//MaximizeWindow(struct window_d *window); //minimizar a janela ativa 
                    break;
				
				//Device Info.
				//Mostra informções sobre todos os dispositivos.
				//Igual ao gerenciador de dispositivos.
				case VK_F5:
					//if(alt_status   == 1){ printf("alt_F5\n"); break;};
					//if(ctrl_status  == 1){ printf("ctrl_F5\n"); break;};
			        //if(shift_status == 1){ printf("shift_F5\n"); break;};
				    //pci_info();     //PCI information.
				    
					systemShowDevicesInfo();
					
					//Test teclado scancode. (FUNCIONOU BEM)
					//Quando aciona esse status, o kernel mostra o scancode.
					//scStatus = 1;
					break;
				
                //Clock info./minishell				
				case VK_F6:
					//if(alt_status  == 1){ procedureMakeTests(); break;};
					//if(ctrl_status == 1){ procedureLinkDriverTest(); break;};
			        //if(shift_status == 1){ printf("shift_F6\n"); break;};
				    //init_clock(); //clock information
					//get_cmos_info();
					//shell_main(0,0,0,0); //bugbug.
					//printf( (const char*) stdout->_ptr );
				    
					//printf("F6: Testando carregar arquivo ...\n");
					//procedureMakeTests();
					
					windowShowWWFMessageBuffers();
					
					//printf("F6: Testando linkar um driver ...\n");
					//procedureLinkDriverTest();
					break;
				
                //Testing Message Box.				
				case VK_F7:
					//if(alt_status   == 1){ printf("alt_F7\n"); break;};
					//if(ctrl_status  == 1){ printf("ctrl_F7\n"); break;};
			        //if(shift_status == 1){ printf("shift_F7\n"); break;};
				    //pertence ao desktop,tipo 1, string.
				    if(VideoBlock.useGui == 1){
					    MessageBox(gui->screen, 1, "F7:","Testing Message Box");
					};
					break;
					
				//Cls.	
				case VK_F8:
					//if(alt_status   == 1){ printf("alt_F8\n"); break;};
					//if(ctrl_status  == 1){ printf("ctrl_F8\n"); break;};
			        //if(shift_status == 1){ printf("shift_F8\n"); break;};
					
					backgroundDraw(COLOR_BLACK);
					
					//Testando repintar o background.
					//resize_window(gui->background, gui->background->width, gui->background->height);
					//redraw_window(gui->background);
					break;
				
                //Reboot.  				
				case VK_F9:
					//if(alt_status   == 1){ printf("alt_F9\n"); break;};
					//if(ctrl_status  == 1){ printf("ctrl_F9\n"); break;};
			        //if(shift_status == 1){ printf("shift_F9\n"); break;};
                    systemReboot();
					break;				

				//Task Manager.	
				case VK_F10:
					//if(alt_status   == 1){ printf("alt_F10\n"); break;};
					//if(ctrl_status  == 1){ printf("ctrl_F10\n"); break;};
			        //if(shift_status == 1){ printf("shift_F10\n"); break;};
				    
					//KiShowThreadList(); //threadi.c
					mostra_slots();  //threadi.c
					
					//@todo: abrir o gerenciador de tarefas.
					//show_process_information();
					//show_thread_information();					
				    break;
					
				//Program manager.
                //@todo: usar F11 para FULL SCREEN.				
				case VK_F11:
					//if(alt_status   == 1){ printf("alt_F11\n"); break;};
					//if(ctrl_status  == 1){ printf("ctrl_F11\n"); break;};
			        //if(shift_status == 1){ printf("shift_F11\n"); break;};
					//printf("@todo Program manager.\n");
					printf("F11\n");
					break;
					
				//Control menu.	
				case VK_F12:
					//if(alt_status   == 1){ printf("alt_F12\n"); break;};
					//if(ctrl_status  == 1){ printf("ctrl_F12\n"); break;};
			        //if(shift_status == 1){ printf("shift_F12\n"); break;};	
					//SystemMenu();
					//printf("@todo Control menu.\n");
					//@todo:control menu da area de trabalho.
					//MainMenu();
					printf("F12\n");
					break;
				
                //Mudar o foco de entrada pra próxima janela de uma lista.				
                case VK_TAB:
				    windowSwitchFocus();
				    break;
					
                // Nothing for now!  				
                case VK_LMENU:    break;
                case VK_LCONTROL: break;
                case VK_LSHIFT:   break;
                //default: break;				
		    };              
        break;
		
		/*
		case MSG_SYSKEYUP: 
            switch(long1)  
            {
				//Obs: Em ordem, da esquer pra direita.
				
				//@todo: Me parece que esse botão não funciona.
                case VK_LSHIFT:
				    //windowSwitchFocus();
					//SetFocus(gui->desktop);
					//SystemMenu();
					//StatusBar(gui->screen, "Status bar", "string 2");
					//DialogBox(gui->screen,1,"DialogBox","String2"); 
					//MessageBox(gui->screen, 1, "F7:","Testing Message Box");
				    break;    	
					
                case VK_LCONTROL:
				    SetFocus(window);
				    ControlMenu();    //teste.
				    break; 	
					
				case VK_RWIN: 	
				case VK_LWIN:    break; 
                case VK_LMENU:	 break;
					
                //case KEY_ALTGR:				    
				//    break;
				
                //case KEY_WINKEY2:				    
				//    break;

                //case KEY_CONTROLMENU: //@todo criar constante.				    
				//    break;

                //case KEY_CONTROL2:
				//    break; 					
            };          
        break;
        */
        /*		
        case MSG_DESTROY:		
            //destroy 
        break;
         */ 
        //Continua ... Create ... Close ...		
    
	    //Nothing.
	    default:    break;
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
 *
 */
void procedureHelp()
{ 
	struct window_d *hWindow; 		
	
	//Parent window.
	if( (void*) gui->main == NULL){
	    return;
	};
	
	//Create.
	hWindow = (void*) CreateWindow( 3, 0, VIEW_MAXIMIZED, "Help:", 
	                                (6*(800/20)), (4*(600/20)), 320, 480, 
							        gui->main, 0, 0, 0 );     
	if( (void*) hWindow == NULL){
	    printf("procedureHelp:\n");
		return;
    }else{
		RegisterWindow(hWindow);
	};
//Coloca as mensagens na janela.
messages: 
	draw_text( hWindow, 8,  2*(480/20), 
	           COLOR_WINDOWTEXT, "F1 Help.");
    draw_text( hWindow, 8,  3*(480/20), 
	           COLOR_WINDOWTEXT, "F2 Kernel info.");
	draw_text( hWindow, 8,  4*(480/20), 
	           COLOR_WINDOWTEXT, "F3 CPU info.");
	draw_text( hWindow, 8,  5*(480/20), 
	           COLOR_WINDOWTEXT, "F4 Window tests.");
	draw_text( hWindow, 8,  6*(480/20), 
	           COLOR_WINDOWTEXT, "F5 Device info.");
	draw_text( hWindow, 8,  7*(480/20), 
	           COLOR_WINDOWTEXT, "F6 Clock info.");
	draw_text( hWindow, 8,  8*(480/20), 
	           COLOR_WINDOWTEXT, "F7 MessageBox.");
	draw_text( hWindow, 8,  9*(480/20), 
	           COLOR_WINDOWTEXT, "F8 Cls.");
	draw_text( hWindow, 8, 10*(480/20), 
	           COLOR_WINDOWTEXT, "F9 Reboot.");
	draw_text( hWindow, 8, 11*(480/20), 
	           COLOR_WINDOWTEXT, "F10 Task Manager.");
	draw_text( hWindow, 8, 12*(480/20), 
	           COLOR_WINDOWTEXT, "F11 Program manager.");
    draw_text( hWindow, 8, 13*(480/20), 
	           COLOR_WINDOWTEXT, "F12 Control menu.");
			   
			   

		
    //
    // Testing Status Bar
    //
    
	StatusBar(hWindow,"Esc=EXIT","Enter=?");
	
	
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

//
// End.
//

