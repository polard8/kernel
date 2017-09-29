/*
 * File: window.c 
 *
 * Descrição:
 *     Arquivo principal do Window Manager.
 *     Window Manager.
 *     MB - Módulos incluídos no Kernel Base.
 *     Rotinas envolvendo a feitura de janelas.     
 *     Parte da interface gráfica oferecida em Kernel Mode.
 *     A interface gráfica oferecida pelo Kernel Base deve ser leve e veloz.
 *
 * Obs: Muitas funcionalidades devem ser iplementadas em user mode e não aqui.
 *      aqui devem ficar as funções mais primitivas. e outras pra ganhar desempenho
 *      mas não tudo. 
 *
 * @todo: Criar uma função que copie o conteúdo de um buffer dedicado de janela para
 * o LFB,(FrontBuffer).
 *       
 * In this file:
 * ============
 * +
 * +
 * +
 *
 *
 *
 * Histórico:
 *     Versão: 1.0, 2013 - Esse arquivo foi criado por Fred Nora.
 *     Versão: 1.0, 2014 - Aprimoramento geral das rotinas básicas. 
 *     Versão: 1.0, 2015 - Revisão. 
 *     Versão: 1.0, 2016 - Revisão.
 *     ...
 */

 
#include <kernel.h>
 
 
 
// 
// Argumentos passados pelo Boot Loader em head.s. 
//

extern unsigned long kArg1;    //Video Mode.	
extern unsigned long kArg2;	   //LFB - Linear Frame Buffer.
extern unsigned long kArg3;	   //??.
extern unsigned long kArg4;	   //??.	



/*
int windowShowWindow(struct window_s *window);
int windowShowWindow(struct window_s *window)
{
	int Status;
	
	if( (void*) window == NULL ){
		return (int) 1;
	};
	
	//@todo: Copiar o conteudo do buffer dedicado para o frontbuffer.
	
	//na estrutura de janela:
	//a variável dedicatedbuffer precisa estar correta.
	//a variável frontbuffer precisa estar correta.
	
	return (int) Status;
}
*/



/*
 * windowSetParent:
 * Atribui uma nova janela mae à uma dada janela filha.
 */
/*
void *windowSetParent(struct window_t *clild, struct window_d *new_parent);
void *windowSetParent(struct window_t *clild, struct window_d *new_parent)
{
	//@implementar.
	//Obs: Se o parâmetro new_parent for NULL então a janela principal (main ou desktop) 
	//será a nova janela mae.
	return NULL;
}
*/

/*
 * windowIsWindow:
 *     Testa através do handle passado, se é uma janela ou não.
 *     0 = Yes; 1 = Not; 
 */
/* 
int windowIsWindow(struct window_d *window);
int windowIsWindow(struct window_d *window)
{
	//@todo:Implementar.
	return 0;
};
*/

/*
void* windowGetWindowWithFocus();
void* windowGetWindowWithFocus()
{
	return (void*) WindowWithFocus;
}
*/


//isso configura o esquema de cores a ser utilizado pelo sistema.
//o esquema de cores a ser utilizado deve estar salvo no perfil
//do usuário que fez o logon.

void windowSetUpColorScheme()
{
	//Por enquanto, estamos fazendo o básico.
	
	
    struct color_scheme_d *humility;
    struct color_scheme_d *pride;	
	
    //Criando o esquema de cores humility. (cinza)
    humility = (void*) malloc( sizeof(struct color_scheme_d) );
    if( (void*) humility == NULL ){
		printf("windowSetUpColorScheme: humility");
		refresh_screen();
		while(1){}
	}else{
		
		//Object.
		humility->objectType = ObjectTypeColorScheme;
		humility->objectClass = ObjectClassGuiObjects;
		

		humility->used = 1;
		humility->magic = 1234;
		
		humility->name = "Humility";
		
		humility->elements[csiNull] = 0;
        humility->elements[csiDesktop] = COLOR_BACKGROUND;		
		humility->elements[csiWindow] = COLOR_WINDOW;
        humility->elements[csiWindowBackground] = COLOR_WINDOW;		
		humility->elements[csiActiveWindowBorder] = 0x00FFFF00;
        humility->elements[csiInactiveWindowBorder] = 0x00FFFF00;		
		humility->elements[csiActiveWindowTitleBar] = COLOR_BLACK;
        humility->elements[csiInactiveWindowTitleBar] = COLOR_GRAY;		
		humility->elements[csiMenuBar] = COLOR_MENUBAR;
        humility->elements[csiScrollBar] = COLOR_GRAY;		
		humility->elements[csiStatusBar] = COLOR_STATUSBAR;
        humility->elements[csiMessageBox] = COLOR_GRAY;		
		//...
		
		HumilityColorScheme = (void*) humility;
	};	
	
	
    //Criando o esquema de cores PRIDE. (colorido)
    pride = (void*) malloc( sizeof(struct color_scheme_d) );
    if( (void*) pride == NULL ){
		printf("windowSetUpColorScheme: pride");
		refresh_screen();
		while(1){}
	}else{
		
		//Object.
		pride->objectType = ObjectTypeColorScheme;
		pride->objectClass = ObjectClassGuiObjects;
		

		pride->used = 1;
		pride->magic = 1234;
		
		pride->name = "Pride";
		
		pride->elements[csiNull] = 0;
        pride->elements[csiDesktop] = COLOR_TEST_0;		
		pride->elements[csiWindow] = COLOR_TEST_2;
        pride->elements[csiWindowBackground] = COLOR_WINDOW;		
		pride->elements[csiActiveWindowBorder] = 0x00FFFF00;
        pride->elements[csiInactiveWindowBorder] = 0x00FFFF00;		
		pride->elements[csiActiveWindowTitleBar] = COLOR_TEST_9;
        pride->elements[csiInactiveWindowTitleBar] = COLOR_TEST_10;		
		pride->elements[csiMenuBar] = COLOR_TEST_4;
        pride->elements[csiScrollBar] = COLOR_TEST_12;		
		pride->elements[csiStatusBar] = COLOR_STATUSBAR;
        pride->elements[csiMessageBox] = COLOR_GRAY;		
		//...
		
		PrideColorScheme = (void*) pride;
	};	
		
	
	// Set current.
	CurrentColorScheme = (void*) humility; 
	
done:	
	return;
}

/*
 * windowShowWWFMessageBuffers:
 *     Mostra o buffer de mensagens da janela com foco de entrada.
 *     #Rotinas de teste. @todo: Enviar para a pasta /test.
 *     Esse rotina funcionou e se mostrou bem útil.
 */
void windowShowWWFMessageBuffers()
{
	struct window_d *wFocus;
    wFocus = (void *) WindowWithFocus;

	int i;
	//Obs: Tipo.
	for( i=0; i<32; i++){
	    printf("%d ", wFocus->msgList[i]);
    };
    return;	
}

/*
 * windowSendMessage:
 *    Uma mensagem deve ser enviada para a estrutura da janela com o foco de entrada.
 *    A classe system.devices.unblocked. pois essa rotina é um método dela.
 *
 * Sobre a fila de mensagem da janela com o foco de entrada:
 * ========================================================
 *  *IMPORTANTE: 
 *      O que importa é qual janela está com o foco de entrada.
 *      Quando sabemos qual janela está com o foco de entrada, então
 * sabemos qual é a janela que é a área de cliente, sabemos e provavelmente
 * a sua janela mãe é a janela ativa, se ela mesma não for a janela ativa.
 *      Uma mensagem pode ser enviada para a janela com o foco de entrada,
 * e a mensagem afetará apenas a janela com o foco de entrada.
 *      Se a janela que receber a mensagem for a janela ativa, ela não
 * terá janela mãe, nessa caso uma mensagem para fechar uma janela ativa
 * implica em fechar o processo ao qual ela está vinculada.
 *      (Não importa qual processo foi interrompido pela interrupção de 
 * teclado. A mensagem deve ir para a fila de mensagens da janela com o foco
 * de entrada.)
 * @todo: Criar uma rotina semelhante, mas exclusivamente para a janela com foco de entrada.
 * Ex: void windowSendMessageWWW(unsigned long arg1, unsigned long arg2, unsigned long arg3, unsigned long arg4)
 */	
void windowSendMessage(unsigned long arg1, unsigned long arg2, unsigned long arg3, unsigned long arg4)
{    
	struct window_d *wFocus;
		
	
    //
	// lembrando: O arg1 por enquanto será ignorado ;;; ele deveria 
	//conter a janela que devemos enviar a mensagem...
	// pegaremos por conta própria o penteiro pra janela com o foco de entrada.
	//
	
	//
    // Não estamos falando de fila de mensagens na estrutura da janela,
	// portando se uma mensagem for enviada para uma estrutura de janela
	// ela irá sobrepor a mensagem antiga caso a mensagem antiga ainda não 
	// tenha sido consumida.
    //	
		
	//
	// @todo: 
	// Na verdade, aqui tem que mandar a mensagem para a janela com o foco 
	// de entrada, mesmo que seja uma janela filha.
	//
		
	//lenbrando que esse é um endereço físico, o mínimo que uma rotina em user mode deve fazer 
    //com essa informação é converte-la em endereço lógico.
    //Ou devemos enviar um endereço lógico ??	
	wFocus = (void *) WindowWithFocus;
	
	// Aqui estamos apenas enviando para a janela com foco de entrada.
	// Não fazer nada caso não haja uma janela com o foco de entrada, 
	// pois quem decide que janela tem o foco de entrada é o usuário.
		
	if( (void*) wFocus == NULL )
	{
		printf("windowSendMessage: wFocus fail\n");
		refresh_screen();
	    return;
	}else{
		
		//Valida a estrutura da janela com o foco de entrada.
		if( wFocus->used == 1 && wFocus->magic == 1234 )
		{
            //nesse momento podemos mostrar o nome da janela com o foco de entrada.
			//printf("windowSendMessage: focus={%s}\n",wFocus->name);
              			
            
			wFocus->sendOffset = 0; 
			
			//Trata o deslocamento atual para as filas.
			//wFocus->sendOffset++;
			//if(wFocus->sendOffset >= 32){ 
			//    wFocus->sendOffset = 0; 
			//};
	        
			//Envia cada mensagem pra sua fila apropriada.
			wFocus->hwndList[wFocus->sendOffset]  = (unsigned long) 0;//WindowWithFocus; //arg1;
			wFocus->msgList[wFocus->sendOffset]   = (unsigned long) arg2;  //msg.
			wFocus->long1List[wFocus->sendOffset] = (unsigned long) arg3;  //long1
			wFocus->long2List[wFocus->sendOffset] = (unsigned long) arg4;  //long2
			
			
			//isso é um teste.
			//Para facilitar vamos colocar a mensagem num lugar mais acessivel.
			gNextKeyboardMessage = (int) 0;
			
		}else{
			//fail.
		};
          		
	};
	
	return;
}


/*
 * windowGetMessage:
 *     Pega uma mensagem na estrutura da janela com o foco de entrada.
 *
 * Obs: 
 *     Esse mecanismo deve ser reproduzido para os parametros hwnd, long1 e long2.
 *     As funções precisam ser criadas ainda. semelhantes a essa.
 *     Mas o que nos importa agora é somente o parâmetro 'msg'.
 * @todo: Quem chamou essa rotina, deseja pegar a mensagem de qualquer janela 
 *ou somente a da janela com o foco de entreada.???
 * @todo: Criar uma rotina semelhante, mas exclusivamente para a janela com foco de entrada.
 * Ex: void *windowGetMessageWWF()
 */
void *windowGetMessage(struct window_d *window)
{
	void *kMSG;
	
	struct window_d *wFocus;
	
	
	//
	// teste
	//
	//isso não ficará assim, é só para testar se um app em user mode 
	//consegue pegar alguma mensagem atravez dessa rotina.
	
	//int tmp;
	//if( gNextKeyboardMessage != 0)
	//{
	//	tmp = gNextKeyboardMessage;
    //    gNextKeyboardMessage = (int) 0;  		
	//	return (void *) tmp; 
	//};
	
	//Pega o ponteiro da janela com o foco de entrada.
	wFocus = (void *) WindowWithFocus;
	
	//Desejamos usar a janela com o foco de entrada.
	if(  (void*) window != (void*) wFocus  )
	{
		printf("windowGetMessage: window != wFocus \n");
		refresh_screen();		
		window = (void*) wFocus;
	};
	
	
	//Testando a validade.
	if((void*) window == NULL)
	{ 
		printf("windowGetMessage: window fail \n");
		refresh_screen();		
	    return NULL; 
	}else{	

			//isso exibiria muitas mensagens por causa do while.
			//printf("windowGetMessage: focus={%s}\n",wFocus->name);	
		
		//
		// @todo: Quando pegar a mensagem no buffer, tem que colocar 
		// zero no lugar, pra não pegar novamente.
		//
		
		window->receiveOffset = 0;
				
		// Não mudaremos o offset do receive ante de tentarmos pegar.
		//Circula.
		//if(window->receiveOffset >= 32){
		//	window->receiveOffset = 0;
		//};
				
		//Pega mensagem.
		kMSG = (void*) window->msgList[window->receiveOffset]; 
				
		//Apaga a mensagem que foi consumida.
		window->msgList[window->receiveOffset] = 0; 
		
        //Incrementamos o offset para a próxima vez.
		//window->receiveOffset++;  		
		
		//Retorna.
		return (void*) kMSG; 
	};
	//Nothing.
fail:	
	return NULL;
};


void *windowGetLong1(struct window_d *window)
{
	void *kLONG1;
	
	struct window_d *wFocus;
	
	
	//
	// teste
	//
	//isso não ficará assim, é só para testar se um app em user mode 
	//consegue pegar alguma mensagem atravez dessa rotina.
	
	//int tmp;
	//if( gNextKeyboardMessage != 0)
	//{
	//	tmp = gNextKeyboardMessage;
    //    gNextKeyboardMessage = (int) 0;  		
	//	return (void *) tmp; 
	//};
	
	//Pega o ponteiro da janela com o foco de entrada.
	wFocus = (void *) WindowWithFocus;
	
	//Desejamos usar a janela com o foco de entrada.
	if(  (void*) window != (void*) wFocus  )
	{
		printf("windowGetLong1: window != wFocus \n");
		refresh_screen();		
		window = (void*) wFocus;
	};
	
	
	//Testando a validade.
	if((void*) window == NULL)
	{ 
		printf("windowGetLong1: window fail \n");
		refresh_screen();		
	    return NULL; 
	}else{	

			//isso exibiria muitas mensagens por causa do while.
			//printf("windowGetMessage: focus={%s}\n",wFocus->name);	
		
		//
		// @todo: Quando pegar a mensagem no buffer, tem que colocar 
		// zero no lugar, pra não pegar novamente.
		//
		
		window->receiveOffset = 0;
				
		// Não mudaremos o offset do receive ante de tentarmos pegar.
		//Circula.
		//if(window->receiveOffset >= 32){
		//	window->receiveOffset = 0;
		//};
				
		//Pega mensagem.
		kLONG1 = (void*) window->long1List[window->receiveOffset]; 
				
		//Apaga a mensagem que foi consumida.
		window->long1List[window->receiveOffset] = 0; 
		
        //Incrementamos o offset para a próxima vez.
		//window->receiveOffset++;  		
		
		//Retorna.
		return (void*) kLONG1; 
	};
	//Nothing.
fail:	
	return NULL;
};



void *windowGetLong2(struct window_d *window)
{
	void *kLONG2;
	
	struct window_d *wFocus;
	
	
	//
	// teste
	//
	//isso não ficará assim, é só para testar se um app em user mode 
	//consegue pegar alguma mensagem atravez dessa rotina.
	
	//int tmp;
	//if( gNextKeyboardMessage != 0)
	//{
	//	tmp = gNextKeyboardMessage;
    //    gNextKeyboardMessage = (int) 0;  		
	//	return (void *) tmp; 
	//};
	
	//Pega o ponteiro da janela com o foco de entrada.
	wFocus = (void *) WindowWithFocus;
	
	//Desejamos usar a janela com o foco de entrada.
	if(  (void*) window != (void*) wFocus  )
	{
		printf("windowGetLong2: window != wFocus \n");
		refresh_screen();		
		window = (void*) wFocus;
	};
	
	
	//Testando a validade.
	if((void*) window == NULL)
	{ 
		printf("windowGetLong2: window fail \n");
		refresh_screen();		
	    return NULL; 
	}else{	

			//isso exibiria muitas mensagens por causa do while.
			//printf("windowGetMessage: focus={%s}\n",wFocus->name);	
		
		//
		// @todo: Quando pegar a mensagem no buffer, tem que colocar 
		// zero no lugar, pra não pegar novamente.
		//
		
		window->receiveOffset = 0;
				
		// Não mudaremos o offset do receive ante de tentarmos pegar.
		//Circula.
		//if(window->receiveOffset >= 32){
		//	window->receiveOffset = 0;
		//};
				
		//Pega mensagem.
		kLONG2 = (void*) window->long2List[window->receiveOffset]; 
				
		//Apaga a mensagem que foi consumida.
		window->long2List[window->receiveOffset] = 0; 
		
        //Incrementamos o offset para a próxima vez.
		//window->receiveOffset++;  		
		
		//Retorna.
		return (void*) kLONG2; 
	};
	//Nothing.
fail:	
	return NULL;
};



/*
 * windowCreateDedicatedBuffer: 
 * Cria um buffer dedicado de acordo com as dimensões da janela.
 */
int windowCreateDedicatedBuffer(struct window_d *window) 
{
	size_t bufferSize;
	
	//Check;
	if((void*) window == NULL ){ 
	    return (int) 1;  //Fail. 
	};
	
    //
    // Buffer size.
    //
	
	//@todo: Usar variável para quantidade de bytes por pixel.
	bufferSize = (size_t) (window->width * 3) + (window->height * 3);
	
	//
	// Alocando memória no Heap do kernel.
	//
	
	if(bufferSize == 0){
	    return (int) 1;    //Fail.	
	}
	else
	{
	    window->DedicatedBuffer = (void*) malloc(bufferSize);	
	    if( (void*) window->DedicatedBuffer == NULL ){
		    return (int) 1;    //Fail.	
		}
		goto done;
	};
	//Nothing
done:
	return (int) 0;  //Success.
};

/*
 * windowLock:
 *     Bloqueia uma janela.
 *     @todo: Quem pode realizar essa operação??
 */
void windowLock(struct window_d *window)
{
    //Check.
	if( (void*) window == NULL ){
	    return;
    };  
    window->locked = (int) WINDOW_LOCKED;  //1.
    return;
};

/*
 * windowUnlock:
 *     Desbloqueia uma janela.
 *     @todo: Quem pode realizar essa operação??
 */
void windowUnlock(struct window_d *window)
{
    //Check.
	if( (void*) window == NULL ){
	    return;
    };  
    window->locked = (int) WINDOW_UNLOCKED;  //0.
    return;
};


/*
 * set_current_window:
 *     @todo: Mudar para windowSetCurrentWindow
 */
void set_current_window(struct window_d *window)
{
    //Check.
	if( (void*) window == NULL ){ return; };  
    
	CurrentWindow = (void*) window;
	current_window = (int) window->id;
    return;
};


/*
 * get_current_window: Get current window pointer.
 */
void *get_current_window(){
	return (void *) CurrentWindow;
};


/*
 * RegisterWindow: 
 *     Registrando uma janela numa lista de janelas.
 */
int RegisterWindow(struct window_d *window)
{
	int Offset = 0; 
    struct window_d *Empty; 
	
    if( (void*) window == NULL ){
        return (int) 1;    //Erro, estrutura inválida.
    };
   
	//
	// Contagem de janelas e limites.
	// (é diferente de id, pois id representa a posição
	// da janela na lista de janelas).
	//
	
	windows_count++;
	
	if(windows_count >= WINDOW_COUNT_MAX){
	    printf("RegisterWindow: Limits.");
		refresh_screen();
		while(1){}
	};
    
	// Create empty.	
	
//Loop.	
get_next:

	Offset++;
	
	//Limite da lista, volta ao início da lista.
	if(Offset >= WINDOW_COUNT_MAX){
	   Offset = 0;
	};	
    
	//Get empty.
 	Empty = (void*) windowList[Offset]; 	
    if( (void*) Empty != NULL ){
        goto get_next;
    }else{
	    
		//coloca na lista.
		//Onde está vazio, registra o ponteiro.
	    windowList[Offset] = (unsigned long) window; 	
		
		//configura o id.
		window->id = (int) Offset;
		
		//...
	};  		
	
done:
    return (int) 0;
};


/*
 * windowShowWindowList:
 *     Show Window List
 *     Mostra a lista de janelas registradas. 
 */
void windowShowWindowList()
{
	int i = 0;
	struct window_d *hWnd;
	struct window_d *hWindow;
	
	
	//Se não estivermos em modo gráfico, não há o que mostrar.	
    if(VideoBlock.useGui != 1){
	    return;	
	};
		
	//@todo: Chamar método.	
	//Cursor.
	g_cursor_x = 0;
	g_cursor_y = 10; 
	//set_up_cursor(0,10);
	
	//
	// Se estamos no modo gráfico.
	//
	
	if(VideoBlock.useGui == 1)
	{
		//Parent window.
	    if( (void*) gui->main == NULL){
	        return;
	    };
			
	    //Create.
	    hWindow = (void*) CreateWindow( 3, 0, VIEW_MAXIMIZED, "Window List:", 
	                                    (800 -320 -2), (600 -240 -2), 320, 240, 
			     				         gui->main, 0, COLOR_BLACK, COLOR_TEST_1 ); 

	    if( (void*) hWindow == NULL){
	        printf("show_window_list:\n");
		    return;
        }else{
		    RegisterWindow(hWindow);
			set_active_window(hWindow);
			SetFocus(hWindow);
	    };										
		
		
		// Auterando as margens.
		// Essas margens são usadas pela função printf.
		// Obs: As medidas são feitas em números de caracteres.
		// Obs: @todo: Devemos usar aqui o retângulo da área de cliente,
		// e não as margens da janela.
		// A estrutura de janela deve nos oferecer os valores para a métrica do 
		// retângulo da área de cliente.
		
		g_cursor_left   = (hWindow->left/8);
		g_cursor_top    = (hWindow->top/8) + 4;   //Queremos o início da área de clente.
		g_cursor_right  = g_cursor_left + (320/8);
		g_cursor_bottom = g_cursor_top  + (240/8);
		
		//cursor (0, mas com margem nova).
		g_cursor_x = g_cursor_left; 
		g_cursor_y = g_cursor_top; 
		
        //Mostrando as informações de todas as janelas registradas.		
        while(i < WINDOW_COUNT_MAX)
        {	
	        hWnd = (void*) windowList[i];
		
		    //
		    // @todo: BUGBUG.
		    // O valor de hWnd tem que estar num limite válido, não adianta apenas ser
		    // diferente de NULL.
		    //
		
		    if( (void*) hWnd != NULL )
			{
	            printf("i={%d} h={%x} dBuf={%x} Name={%s}\n", i, hWnd, hWnd->DedicatedBuffer, hWnd->name);
				//draw_text( hWindow, 8,  1*(400/16), COLOR_WINDOWTEXT, "F1 Help.");
	        };
		    ++i;
	    };
		
		show_active_window();
        show_window_with_focus();
        SetFocus(hWindow);
	
		
		//voltando a margem normal a margem
		g_cursor_left = 0;
		g_cursor_top =  0;
		g_cursor_right = 256;
		g_cursor_bottom = 256;
		
		//cursor (0, mas com margem nova)
		g_cursor_x = g_cursor_left; 
		g_cursor_y = g_cursor_top;
        //set_up_cursor(g_cursor_left,g_cursor_top); 		


		StatusBar(hWindow,"Esc=EXIT","Enter=?");		
	    //refresh_screen();    	
	    
		//Nothing.
		
		//return;
	};	
	    

    // Continua ...
	
done:
    //SetFocus(hWindow);
    return;
};



/*
 * redraw_window:
 *     #bugbug: Essa rotina está errada !!!
 *     O OBJETICO DESSA ROTINA DEVE SER APENAS REPINTAR UM RETÂNGULO
 * QUE FOI PINTADO DENTRO DA ÁREA DE CLIENTE DA JANELA QUE FOI PASSADA 
 * VIA ARGUMENTO. PORTANTO UM ARGUMENTO DE RETÂNGULO TAMBEM DEVE SER OFERECIDO @TODO 
 * Obs: Esse retângulo deve pertencer a janela que foi passada por argumento.
 * na estrutura de retângulo deve haver um ponteiro para  ajanela à qual ele pertence.
 *
 *
 *
 *     Repinta uma janela de acordo com os parâmetros na estrutura.
 *     Repinta uma janela válida. Tem que estar registrada. 
 *     @todo: Mudar para windowRedrawWindow(.)
 * Obs: Esse é o tipo de rotina que exige o recurso de buffer dedicado.
 * Pois podemos redezenhar a janela em seu buffer dedicado e depois copiar
 * o conteúdo do buffer dedicado para o backbuffer... na hora de atualizar a tela
 * é so copiar o backbuffer no frontbuffer(LFB).
 * *** Na verdade eu não faço a menor ideia de como redezenhar uma janela...
 * Talvez essa função deva ser igual a função create, mas as características da 
 * janela são pegadas da estrutura de janela passada via argumento.
 * pois bem, essa janela vai ter muitos elementos para incluir isso leva muito tempo.
 * Devemos registrar na estrutura da janela todos os botões que ela tem.?? 
 * todos os textos gravados nela?? ... todas as cores??
 */
//int windowRedrawWindow(struct window_d *window) 
//int redraw_window(struct window_d *window, struct rect_d *rect)
int redraw_window(struct window_d *window)
{
	int Status;
 
 
	//Checar se a estrutura é válida.
	
	//handle
	if((void*) window == NULL){
		return (int) 1;
	};
	
	//used
	if( window->used != 1 ){
		return (int) 1;
	}
	
	//magic
	if( window->magic != 1234 ){
		return (int) 1;
	}
	
	//@todo: Pra que serva a flag redraw ??
	// É para indicar que repecisamos repintar. ??
	//if( window->redraw != 1 ){ return (int) 0;}
	
	//
	// Ok, pelo jeito temos uma estrutura válida.
	//
	
	// Minimized? Se tiver minimizada, não precisa repintar.
	Status = (int) is_window_minimized(window);
    if(Status == 1){
	    return (int) 1;
	};	
	
	//E se ela estiver travada ??
	// ?? travada pra quem ??
	//if(window->locked == 1){}

	
	//Pintar ?? Onde ?? backbuffer ?? dedicated buffer ??
//drawWindow:	
	
	//
	// Devo lembrar que as características da janela estão salvas na estrutura
	// e são muitas características. Não exige cálculos, toda a métrica já está pronta.
	//
	
	
	//Buffers ??
	//window->DedicatedBuffer
	//window->BackBuffer
	//window->FrontBuffer
	
	
 
	
	//
	// Agora na hora de efetivamente redezenhar. podemos ver na estrutura
	// Qual os elementos preseentes nela, lembrando que esses elementos 
	// podem ter sido modificados, então o melhor lugar para pegar essas
	//informações é na estrutura mesmo, pois lá serão salvos as preferências
	//atuais do usuário em relação a janela que deve ser repintada.
	// por ex: o usuário pode ter redimencionado ou arrastado elementos da janela,
	//ou ocultado apenas. afinal feito escolhas ... usuarisses.
	//
	
	
RedrawBegin:		



    //Sombra.	
	if(window->shadowUsed == 1)
	{
        drawDataRectangle( window->left +1, 
		                   window->top  +1, 
						   window->width, 
						   window->height, 
						   COLOR_BLACK );  //@criar padrão de cor para sombra.      
	};


    //Background.
	if(window->backgroundUsed == 1)
	{		
	    drawDataRectangle( window->left, 
		                   window->top, 
						   window->width, 
						   window->height, 
						   window->color_bg );   	
	};
	
	
	
	
    //Título + borda.	
	if(window->titlebarUsed == 1)
	{ 
        //
		// #bugbug: Aqui temos um problema, nahora de repintar, não temos 
		// definido a cor que precisamos....esse if focus não deveria existir na rotina de redraw.
		//
		
		//Focus.
		if(window->focus == 1){
		    window->color_bg = COLOR_BLACK;  // Com foco de entrada.
		}else{
			window->color_bg = COLOR_GRAY;   // Sem foco de entrada.
		};
		
		//@todo: String color.
		
		//@todo: String size.
		
		//Rectangle and string.
		
        drawDataRectangle( window->left, 
		                   window->top, 
						   window->width, 
						   window->height, 
						   window->color_bg );
						   
						   
		//#bugbug não temos salvo o posicionamento da string.
        //deveria estar na estrutura da janela.		
		draw_string( window->left +8 +16 +8, 
		             window->top +8, 
					 COLOR_WHITE, 
					 window->name );   //?? name 
					 
		//...			 
	};		
	
	

   // Client Area. 	
	if(window->clientAreaUsed == 1)
	{
		//
		// Obs: A Client Area é apenas um retângulo.
		//

		//@todo: Passar a estrutura de janela.
		
		
		//
		// #BUGBUG :: NÃO PODEMOS REALOCAR NOVAMENTE ... TEMOS QUE CHECAR 
		// SE A ESTRUTURA É VÁLIDA...
		// SE TRATA APENAS DE UMA ESTRUTTURA DE RETÃNGULO, NÃO ESPERAMOS MUITOS PROBLEMAS.
		//
		
		 
		if( (void*) window->rcClient == NULL )
		{
			printf("redraw window: a estrtutura de client falhou");
			refresh_screen();
            while(1){}			
		     
		}else{
		
		    //@todo: a cor deveria vir de outra estrutura: window->rcClient->color_bg.
            drawDataRectangle( (unsigned long) window->rcClient->x, 
		                       (unsigned long) window->rcClient->y, 
						       (unsigned long) window->rcClient->cx, 
						       (unsigned long) window->rcClient->cy, 
						       (unsigned long) window->clientrect_color_bg );         
							    
		};
		//Nothing.
	};




	//
	// Outros elementos inda nõ implementados ...
	//


	//
	// A rotina de repintura deve estar em sintonia com a rotina de pintura, elas 
	// devem ser semelhantes, porem a rotina de repintura deve levar em consideração 
	// os elementos incluídos depois da criação da janela e que ficam gravados na 
	// estrutura. como por exemplo: arquivos abertos.
	//

	//Continua ...
	
done:
    return (int) 0; 
};


/*
 * resize_window:
 *     Muda as dimensões da janela.
 */				  
int resize_window(struct window_d *window, unsigned long cx, unsigned long cy)
{
    if( (void*) window == NULL ){
	    return (int) 1;    //Erro, estrutura inválida.
	}else{	
	    
		//@todo: Checar limites.
	
        window->width  = (unsigned long) cx;
        window->height = (unsigned long) cy;	
	};

done:
    return (int) 0;
};


/*
 * replace_window:
 *     Muda os valores do posicionamento da janela.
 */				  
int replace_window(struct window_d *window, unsigned long x, unsigned long y)
{
    if( (void*) window == NULL ){
	    return (int) 1;
	}else{
		
        //@todo: Checar limites.
	
        window->left = (unsigned long) x;
        window->top  = (unsigned long) y;
	};

done:
    return (int) 0;
};


/*
 * is_window_full:
 *     Checar se está no modo tela cheia.
 *
 *     retorno 1, modo tela cheia.
 * @todo: Rever o retorno.
 */
int is_window_full(struct window_d *window)
{
    //Checa estrutura.
    if( (void*) window == NULL ){
	    return (int) 0;    //FALSE.
	};

	//Checa modo tela cheia.
    if(window->view == VIEW_FULL){
	    return (int) 1;    //TRUE.
	};
	
fail:
	return (int) 0;
};


/*
 * is_window_maximized:
 *     Checar se está no modo maximizado.
 *
 *     retorno 1, modo maximizada.
 * @todo: Rever o retorno.
 */
int is_window_maximized(struct window_d *window)
{
    //Checa estrutura.
    if( (void*) window == NULL){
	    return (int) 0;    //FALSE.
	};

	//Checa se está maximizada.
    if( window->view == VIEW_MAXIMIZED){
	    return (int) 1;    //TRUE.
	};
	
fail:
	return (int) 0;    //FALSE.
};

//todo: rever o retorno
int is_window_minimized(struct window_d *window)
{
    //Checa estrutura.
	if( (void*) window == NULL){
	    return (int) 0;    //FALSE.
	};

	//Checa se está minimizada.
    if( window->view == VIEW_MINIMIZED){
	    return (int) 1;    //TRUE.
	};
	
fail:
	return (int) 0;    //FALSE.
};


/*
 * CloseWindow:
 *     Fecha uma janela. (Destrói).
 *
 *     OBS: O ato de fechar uma janela está associado
 *          ao ato de encerrar um processo. Mas nem sempre.
 *
 */
void CloseWindow(struct window_d *window)
{
	int Offset;
	
	//Check.
	if( (void*) window == NULL ){ return; };

	// Focus.
	KillFocus(window);
	
	// Parent.
	if( (void*) window->parent == NULL)
	{
		//@todo: Usar a linked list de janelas ativas.
	    set_current_window(gui->screen);
	    set_active_window(gui->screen);    
		SetFocus(gui->screen);
	}else{
        set_current_window(window->parent); 
	    set_active_window(window->parent);
        SetFocus(window->parent);  		
    };
	
	//Tira da lista.
    Offset = (int) window->id;		
	windowList[Offset] = (unsigned long) 0;  
	
	//Destrói a estrutura..
	window = NULL;
	
	
	//
	// @todo: 
	//     Liberar memória. 
	//     (bug bug) problemas para novo ponteiro de heap.
	//
	
	// Counter.
	if( windows_count > 0){
	    windows_count--;
	};
	
	
	//
	// Next window procedure. (@todo: usar lista linkada.)
	//
	//g_next_proc = (unsigned long) &system_procedure;
	SetProcedure( (unsigned long) &system_procedure );
	
// Done
done:
    return;
};


/*
 * DestroyWindow:
 *     Destrói uma janela.
 *
 *     Obs: Quando a janela é do tipo Overlapped,
 *          destruir janela significa também fechar 
 *          o processo e as threads associados à ela.
 *
 *          Pois Overlapped é o tipo de janela usado
 *          como janela principal de um processo.
 *
 */
void DestroyWindow(struct window_d *window)
{
	//Check.
	if( (void*) window == NULL ){ return; };
	
	// Kill Threads and Process.
	if(window->type == WT_OVERLAPPED)
    {
	    //kill threads ...
	    //kill process ...
		
		//destroy as threads e o processo associado à janela.
	};
		
	//
	// Close child. (todas do array de estrutura cujo ponteiro esta na estrutura da janela)
	//
	
done:
    //Do Close.
    CloseWindow(window);
    return;
};


/*
 * get_active_window:
 *     Obtem o id da janela ativa.
 *     @todo: Mudar para windowGetActiveWindowId().
 */
int get_active_window(){
    return (int) active_window;  
};


/*
 * set_active_window:
 *     Seleciona qual será a janela ativa.
 *     Ativa uma janela.
 */
void set_active_window(struct window_d *window)
{
    //Checa procedimento de janela.	
	if( (void*) WindowProcedure == NULL){
	    return;
	};
	
	//Check window.
	if((void*) window == NULL ){ 
	    return; 
	}else{

	    window->active = (int) 1;	
        WindowProcedure->active_window = (int) window->id;			

	    //Variável global
        active_window = (int) window->id;	
	
	    //Estrutura global
	    ActiveWindow = (void *) window;	
	
	    //Essa função deveria fazer o que manualmente foi feito acima.
	    SetFocus(window);		
	};
	//Nothing.
done:
    return;
};


/*
 * change_active_window:
 *     @todo: Trocar a janela ativa usando uma linked list.
 */
void change_active_window(int Id)
{
	// @todo: Limits. Max.
    if(Id < 0){
	    return;
	};
	
    // Procedure Struct.	
    if( (void*) WindowProcedure == NULL){
	    return;
	};
    
	//
	// @todo: Usar a linked list pra trocar o id.
	//
	
	// Id.
	WindowProcedure->active_window = (int) Id;
	
done:
    return;
};


/*
 * show_active_window:
 *     Mostra o id da janela ativa.
 *     @todo: Mudar o nome para windowShowActiveWindowId() 
 */
void show_active_window(){
	printf("ActiveWindowId={%d}\n", (int) active_window);
    return;
};

/*
 * show_window_with_focus:
 *     Mostra o id da janela com o foco de entrada..
 */
void show_window_with_focus(){
	printf("WindowWithFocusId={%d}\n", (int) window_with_focus);
    return;
};

/*
 * CloseActiveWindow:
 *     Fecha a janela ativa.
 */
void CloseActiveWindow()
{
	int Offset;
    struct window_d *Window;
	
    Offset = (int) get_active_window();	
	if(Offset < 0){
       return;	
	};
	
	//struct.
	Window = (void*) windowList[Offset];
	
	//Nothing to do.
	if( (void*) Window == NULL ){
        return;
    }else{
	    
		//Torna ativa a próxima janela.
	    if( (void*) Window->next != NULL ){
	        set_active_window(Window->next);
	    }else{
	        //Torna ativa a janela mãe.
	        if( (void*) Window->parent != NULL ){
	            set_active_window(Window->parent);
	        };
		};
	};	
	
// Done.
done:
    DestroyWindow(Window);
    return;
};


//
// @todo: windowSetFocus(.) e windowGetFocus() windowSwitchFocus()
//



void windowBlockfocus(){
	gFocusBlocked = (int) 1;
	return;
};

void windowUnblockFocus(){
	gFocusBlocked = (int) 0;
	return;
};

/*
 * SetFocus:
 *     Atribui o foco à uma janela e possível.
 *     //Por enquanto estamos implementando a possibilidade
 * de travar a obtenção de foco, somente para teste... porem 
 * isso pode ser útil depois.
 */
void SetFocus(struct window_d *window)
{
	//Impossível mudar o focus.
	//Isso manterá o foco na janela do desenvolvedor
	//durante a fase de criação da interface gráfica.
	if( _lockfocus == 1){
		return;
	};
	
	
	
    if( (void *) window == NULL )
	{
		
		//Isso pe recursivo, pode dar problema.
		//SetFocus(gui->screen);    
		return;
	}else{
		
		//Focus.
	    window->focus = (int) 1;
	    window_with_focus = (int) window->id;		
		WindowWithFocus = (void *) window;
		
		//cursor
		//WindowWithFocus->cursor_x = 0;
		//WindowWithFocus->cursor_y = 0;
		
		//Procedure.
		//?? Não sei se é o ideal.
		SetProcedure((unsigned long) window->procedure);	
	};
	//Nothing.
	return;
};


/*
 * GetFocus: Pega o id da janela com o foco de entrada.
 */
int GetFocus(){
    return (int) window_with_focus;	
};

/*
 muda qual sra a janela ativa.
 Obs: Quando mudamos qual será a janela ativa
 temos que atualizar qum será a janela com o foco de entrada.
 ... e as janes com o foco de entrada devem ficar numa lista.
 .. que provavelmente é a lista de janelas filhas.
void windowSwitchActiveWindow();
void windowSwitchActiveWindow()
{}
*/

/*
 * windowSwitchFocus:
 *     Muda a janela que está com foco de entrada.
 *     @todo: Selecionar a janela indicada como next na estrutura.
 *     Em cada momento o foco está em uma lista de janelas
 * e quando trocamos o foco, percorremos a lista atual.
 * mas a lista muda dependendo do ambeinte gráfico que estamos.
 * muda quando trocamos a janela ativa, muda quando trocamos o desktop.
 * 
 */
void windowSwitchFocus()
{
	int Max;
	int Current;

    struct window_d *window;
	struct window_d *next;
	struct window_d *Saved;    //Caso tudo ter errado, use essa.	
	//...
	
	//Max e Current.
	Max     = (int) windows_count;
	Current = (int) window_with_focus;	
	
	//
	// @todo: 
	// Essa rotina precisa ser refeita. Seguindo uma lista linkada de janelas.
	//
	
	window = (void*) windowList[window_with_focus];	
	
	if( (void*) window == NULL ){
	    return;    
	}else{
		
	    //Se não há uma próxima, não tem como mudar.
	    if( (void*) window->next == NULL ){
		    return;
		};		
		
	    KillFocus(window);  //Kill.
		
	    next = (void*) window->next;  //Get next.

		//Focus.	    
		Current = (int) next->id;     //Current id.
	    
		//Se estiver fora dos limites, use o antigo.
		if(Current < 0 || Current >= Max){
		    Current = (int) window->id;
	    };	

		//@todo: Usar o método.
		window_with_focus = (int) Current;
		window = (void*) windowList[Current];
        SetFocus(window);		
	};
	//Nothing.
done:

    //Debug message:  
	//@todo: Criar mecanismo melhor pra mostrar a janela com o foco.
    printf("Focus={%d}\n", (int) window_with_focus);
	refresh_screen();
	
	return;
};


/*
 * KillFocus:
 *     Uma janela perde o foco.
 */
void KillFocus(struct window_d *window)
{
    //Check.
	if( (void *) window == NULL ){ return; };
	
	//Focus.
	window->focus = (int) 0;

	//
	// Pra onde vai o foco ??
	//
	
	//set next window
	if( (void*) window->parent == NULL){
	    SetFocus(gui->screen); //@todo: Usar a linked list de janelas ativas.
	}else{
	    SetFocus(window->parent); 
    };	
	
	//Set procedure.
    //g_next_proc =  (unsigned long) &system_procedure;
	
done:
	//window_with_focus = ??
	return;
};


/*
 * MinimizeWindow:
 *     Minimiza uma janela.
 *     @todo windowMinimize()
 */
void MinimizeWindow(struct window_d *window)
{
	int Status;
	
    if( (void *) window == NULL){
		return;
	};
	
	Status = (int) is_window_minimized(window);
    if(Status == 1){
	    return;
	};	
	
	//
	//@todo: Redraw ?!
	//
	
done:
	window->view = (int) VIEW_MINIMIZED;
    return;	
};


/*
 * MaximizeWindow:
 *     Maximiza uma janela.
 *     @todo: windowMazimize()
 */
void MaximizeWindow(struct window_d *window)
{
	int Status;
	
    if( (void *) window == NULL){
	    return;
	};
	
	Status = (int) is_window_maximized(window);
    if(Status == 1){
	    return;
	};


    //redimensionar.
	if(gui->main != NULL){
        window->left   = gui->main->left;             
        window->top    = gui->main->top;                   
	    window->width  = gui->main->width;             
        window->height = gui->main->height;
	}; 	

	//
	//@todo: Redraw ?!
	//
	
done:
	window->view = (int) VIEW_MAXIMIZED;
    return;	
};


/*
 * init_window_manager:
 *     Inicializa o gerenciamento de janelas.
 *     @todo windowmanagerInit()
 */
int init_window_manager()
{
	//
    // Aloca memória para a estrutura do procedimento 
	// de janela da thread atual.
	//
	
	WindowProcedure = (void*) malloc( sizeof( struct window_procedure_d ) );
	if( (void*) WindowProcedure == NULL ){
	    printf("init_window_manager fail: Structure.");
		refresh_screen();
		while(1){}
	};  

	//
	// Configura a janela ativa. 
	// Configura a janela com o foco de entrada. 
	// Se a janela com o foco de entrada for uma janela filha,
	// então a janela mãe será a janela ativa.
	//
	
	WindowProcedure->active_window = (int) 0;
	WindowProcedure->window_with_focus = (int) 0;

	//
	// @todo:  
	//     Continua fazendo inicializações de procedimento de janela.
	//
	
done:
    printf("done!\n");
    return (int) 0;
};


/*
 * init_windows:
 *     Inicializa a lista de janelas.
 *     Inicializa globais relativas à janelas.
 */
int init_windows()
{
	int Offset = 0;
	
	windows_count = 0;
	
	// Inicializa a lista de janelas.
	//printf("init_windows:\n");  	
	
	while(Offset < WINDOW_COUNT_MAX){
	    windowList[Offset] = (unsigned long) 0;
        ++Offset;
	};
	
	// Set current.
	set_current_window(NULL);
	
	//
	// Inicializando a estrutura do retângulo da área de cliente.
	//
	
	rectClientArea = (void*) malloc( sizeof(struct rect_d) );
    if((void*) rectClientArea == NULL){	
	    printf("init_windows:");
		refresh_screen();
		while(1){}
	}else{
	    setClientAreaRect( 0, 0, 0, 0);	
	};
	
	
	//
    // Set fonts. @todo: Criar uma estrutura para características do char.
	//
		
	// 8x8 
	g8x8fontAddress  = (unsigned long) 0x000FFA6E;    //ROM. @todo usar definição de constante.
	//g8x16fontAddress = (unsigned long) 0x000FFA6E;  //@todo.
	//...
	
	//@todo: create SetFontAddress(.)
	gfontAddress = (unsigned long) g8x8fontAddress;
	
	//
	// Char parameters.
	//
	
	//@todo: Create SetCharParam(.,.)
	gcharWidth = (int) 8;
	gcharHeight = (int) 8;	
	
	//...	
	
	//
	// @todo:
	// Pega o video mode passado pelo Boot Loader e 
	// registra na global e na estrutura.
	//
	
	/*
	
	//video mode
	if( kArg1 > 0)
	{
	    printf("init_windows: Configurando modo de video.");
	    SetVideoMode(kArg1);
	};
	
	//LFB
	if( kArg2 != LFB_BASE)
    {
        printf("init_windows: LFB error");
		//@todo hang
    };	
	
	*/
	
	//Inicializando variáveis.
	current_windowstation = 0;
	current_desktop = 0;
	current_window = 0;
	windows_count = 0;
	window_with_focus = 0;
	current_menu = 0;
    //Continua...		

	
	//inicializando os esquemas de cores.
	windowSetUpColorScheme();	
	
	//
	// Continua ...
	//
	
done:	
    //printf("Done.\n");
	return (int) 0;
};


//
// End.
//

