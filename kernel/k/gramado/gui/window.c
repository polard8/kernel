/*
 * File: gui\window.c 
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
 * windowInitializeBrowserSupport:
 *      (KSOC - Kernel Standard Output Container)
 *       gerenciador de ambientes de janelas ... como no caso de window station/desktop/window...
 * só que com abas.
 *
 *     Inicialização do sistema de suporte ao navegador shell.
 * *Importante: Essa rotina será bem longa..
 * devemos inicializar todos os recursos que serão usados pelo navagador ...
 * O kernel deve criar uma janela uma janela maximizada que será o navegador ...
 * deve criar 12 abas que serão atendidas através do procedimento de janelas do sistema.
 * 
 * *Importante: essa rotina deve ser chamada antes de rodar qualquer processo em user mode.
 * portanteo um bom lugar pra essa rotina ser chamada é no final de main.c, antes de dar iretd
 * para a thread idle.
 *
 */
int windowInitializeBrowserSupport()
{
	int i;
	
	printf("Initializing browser support\n");
	
	
	for(i=0; i< TABWINDOW_COUNT_MAX; i++){
		browsertabList[i] = (unsigned long) 0;
	}
	
	BROWSERWINDOW = NULL;
	TABWINDOW = NULL;
	current_tab = 0;
	
	
	//
	// @todo: Inicializar todos os recursos que o navegador vai precisar.
	//
	
	/*Criando a janela do navegador ... isso requer uma ponteiro exclusivo*/
	/*Esse é a janela com moldura onde as abas serão criadas.
	Essas abas serão janelas filhas da janela do navegador KSOC.*/
	struct window_d *w;
	

    w = (void*) CreateWindow( 3, 0, 0,"KSOC - Kernel Standard Output Container", 
			                             0, 0, 800, 600, 
										 gui->screen, 0, COLOR_WINDOW, 0xC0C0C0 );

    if( (void*) w == NULL ){
	    printf("windowInitializeBrowserSupport:");
		die();
		//refresh_screen();
	    //while(1){};
	}else{
		
		if( w->used != 1 || w->magic != 1234 ){
	        printf("windowInitializeBrowserSupport: fail");
		    die();
			//refresh_screen();
	        //while(1){};			
		}
		
		RegisterWindow(w);
        set_active_window(w);
		SetFocus(w);

        //Ponteiro exclusivo.
        BROWSERWINDOW = (void*) w;		
	};


	/*Criando as estruturas para as 12 abas do navegador.*/	
	/* Criaremos apenas 4 abas ... rotinas de erro perceberão a as faltantes*/
	/* cada aba tem uma estrutura de aba, um ponteiro par a asua janela dentro da estrutura.*/
	
	struct browser_tab_d *bt; //browser tabs.
	
	
	/*Importante: Começaremos de 1 pois a aba 0 é a janela gui->screen*/
	for(i=1; i<4; i++)
	{
		bt = (void*) malloc( sizeof(struct browser_tab_d) );
	    if((void*) bt == NULL){
	        printf("erro tab struct");
		    die();
			//refresh_screen();
	        //while(1){};
	    }		
		
		bt->used = 1;
		bt->magic = 1234;
		bt->type = 1;  //do mesmo tipo por enquanto.
		
		bt->name = "TAB NAME";
		bt->view = 1;
		
		//As abas são janelas do tipo 1, pop up simples.
		//os tamanhos serão revistos.
		//brancas á princípio.
		//
		// *Importante: Pintar todas essas janelas sobrepostas demanda tempo 
        // podemos criar janelas minimizadas, que não precisam pintar. 		
		//
        w = (void*) CreateWindow( 1, 0, 0,"TAB", 
			                             0, 24, 800, 600-24, 
										 gui->screen, 0, COLOR_WINDOW, COLOR_WINDOW );		
		
	    if((void*) w == NULL){
	        printf(".");
		    die();
			//refresh_screen();
	        //while(1){};
	    }else{   
		    RegisterWindow(w);
		    //...
	    };
	
	    //Ponteiro da janela da aba.
	    bt->window = (void*) w;
		
		bt->next =  NULL;
		
		//salvando o ponteiro para a tab na lista de ponteiros de tab.
		browsertabList[i] = (unsigned long) bt;
	
	}
	

   //
   // Testando uma aba.
   //   
   
    //testando a aba 1.
    bt = (void*) browsertabList[1];
    
	if((void*) bt == NULL){
	    printf("~erro tab struct");
		die();
		//refresh_screen();
	    //while(1){};
	}	   
   
    if( bt->used != 1 || bt->magic != 1234 ){
	    printf("windowInitializeBrowserSupport: bt fail");
		die();
		//refresh_screen();
	    //while(1){};			
	}


	//Determinado que a tab 1 é a tab atual.
	//Obs; Isso não é a janela com o foco de entrada.
    current_tab = 1;
	
	//janela da aba. (a aba propriamente dita.
    w = (void*) bt->window;	

    if( (void*) w == NULL ){
	    printf("windowInitializeBrowserSupport:~fail");
		die();
		//refresh_screen();
	    //while(1){};
	}else{
		
	    if( w->used != 1 || w->magic != 1234 ){
	        printf("windowInitializeBrowserSupport: ~fail");
	        die();
			//refresh_screen();
	        //while(1){};			
	    }
		
		//Aqui temos uma janela válida. Essa janela é uma aba.
		//vamos escrever nela pra testar.
		
		//Ponteiro para a janela da aba atual.
		//Obs: Rotinas que desejam pintar na aba atual usam esse ponteiro.
        TABWINDOW = (void*) w;

        
		//Test: Criando alguns elementos gráficos dentro da aba no navegador.
		draw_text( TABWINDOW, 0, 0, COLOR_PINK, "bt: This is a text on the browser tab number 1");	
        draw_button( TABWINDOW, "bt: Button label 11 11", 1, 11, 11, 56, 24, COLOR_BUTTONFACE); 
		StatusBar( TABWINDOW, "bt: Status bar, string 1", "bt: Status bar, string 2");
	};

	
   //
   // Deve haver muito o que fazer ainda  ...
   //
   
    printf("done.\n");	
	return (int) 0;
}


/*
 * @todo: Talvez aque devamos apenas atualizar a flag de view da janela.
int windowShowWindow(struct window_d *window, int msg);
int windowShowWindow(struct window_d *window, int msg)
{
	int Status;
	
	if( (void*) window == NULL ){
		return (int) 1;
	};
	
	
	switch(cmd)
	{
		case MSG_HIDE:
		case MSG_MAXIMIZE:
		case MSG_RESTORE:
		case MSG_SHOWDEFAULT:
		default:
	}
	
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

//configuramos qual janela ficará por cima de todas as outras.
/*
void windowSetForegroundWindow(struct window_d *window);
void windowSetForegroundWindow(struct window_d *window)
{
	//set focus 
	//coloca no topo da lista
	return;
}
*/


//get parent window
void *GetParentWindow(struct window_d * hwnd)
{
	if( (void*) hwnd == NULL ){
		return NULL;
	}
	return (void*) hwnd->parent;
}

//get the desktop of a window.
void *GetWindowDesktop(struct window_d * hwnd)
{
	if( (void*) hwnd == NULL ){
		return NULL;
	}
	return (void*) hwnd->desktop;
}

/*
 * ===============================================================
 * windowSetUpColorScheme:
 *     Isso configura os esquemas de cores utilizados pelo sistema.
 *     O esquema de cores a ser utilizado deve estar salvo no perfil
 * do usuário que fez o logon.
 * Os dois esquemas padrão chamam-se: 'humility' e 'pride'.
 * + O esquema 'humility' são cores com tema cinza, lembrando interfaces antigas.
 * + O esquema 'pride' são cores modernas 
 *   ( Aquele verde e preto e cinza, das primeiras versões, com imagens publicadas. )
 *
 */
void windowSetUpColorScheme(int type)
{	
    struct color_scheme_d *humility;
    struct color_scheme_d *pride;	
	
	//
	// * HUMILITY
	//
	
    //Criando o esquema de cores humility. (cinza)
    humility = (void*) malloc( sizeof(struct color_scheme_d) );
    if( (void*) humility == NULL ){
		printf("windowSetUpColorScheme: humility");
		die();
		//refresh_screen();
		//while(1){}
	}else{
		
		//Object.
		humility->objectType = ObjectTypeColorScheme;
		humility->objectClass = ObjectClassGuiObjects;
		

		humility->used = 1;
		humility->magic = 1234;
		
		humility->name = "Humility";
		
		humility->elements[csiNull] = 0;                               //0
        humility->elements[csiDesktop] = COLOR_BACKGROUND;             //1		
		humility->elements[csiWindow]  = COLOR_WINDOW;                 //2
        humility->elements[csiWindowBackground] = xCOLOR_GRAY1;	       //3	
		humility->elements[csiActiveWindowBorder] = xCOLOR_GRAY2;      //4
        humility->elements[csiInactiveWindowBorder] = xCOLOR_GRAY3;    //5		
		humility->elements[csiActiveWindowTitleBar] = xCOLOR_GRAY2;    //6
        humility->elements[csiInactiveWindowTitleBar] = xCOLOR_GRAY3;  //7	 	
		humility->elements[csiMenuBar] = COLOR_MENUBAR;                //8
        humility->elements[csiScrollBar] = xCOLOR_GRAY3;		       //9  
		humility->elements[csiStatusBar] = COLOR_STATUSBAR;            //10
        humility->elements[csiMessageBox] = xCOLOR_GRAY2;		       //11
		humility->elements[csiSystemFontColor] =   COLOR_BLACK;		   //12
		humility->elements[csiTerminalFontColor] = COLOR_WHITE;	       //13
		//...
		
		//Sanvando na estrutura padrão para o esquema humility.
		HumilityColorScheme = (void*) humility;
	};	
	
	//
	// * PRIDE 
	//
	
    //Criando o esquema de cores PRIDE. (colorido)
    pride = (void*) malloc( sizeof(struct color_scheme_d) );
    if( (void*) pride == NULL ){
		printf("windowSetUpColorScheme: pride");
		die();
		//refresh_screen();
		//while(1){}
	}else{
		
		//Object.
		pride->objectType = ObjectTypeColorScheme;
		pride->objectClass = ObjectClassGuiObjects;
		

		pride->used = 1;
		pride->magic = 1234;
		
		pride->name = "Pride";
		
		//@todo:
		pride->elements[csiNull] = 0;
        pride->elements[csiDesktop] = COLOR_BACKGROUND; //0x00808000 verde escuro.
		pride->elements[csiWindow] = COLOR_WINDOW;
        pride->elements[csiWindowBackground] = xCOLOR_GRAY1;
		pride->elements[csiActiveWindowBorder] =  0x80FFFF00;
        pride->elements[csiInactiveWindowBorder] = 0x80FFFF00;    //  (LIGHT GREEN) 
		pride->elements[csiActiveWindowTitleBar] = 0x80FFFF00;    //  (LIGHT GREEN)
        pride->elements[csiInactiveWindowTitleBar] =  0x80FFFF00;		
		pride->elements[csiMenuBar] = COLOR_GRAY;
        pride->elements[csiScrollBar] = COLOR_GRAY;		
		pride->elements[csiStatusBar] = 0x40404000;  //COLOR_STATUSBAR;  //#404040 cinza #FFFFFF branco
        pride->elements[csiMessageBox] = COLOR_GRAY;
		pride->elements[csiSystemFontColor] =   COLOR_BLACK;		   //12
		pride->elements[csiTerminalFontColor] = COLOR_WHITE;	       //13		
		//...
		
		//Sanvando na estrutura padrão para o esquema pride.
		PrideColorScheme = (void*) pride;
	};	
		
	
	//
	// Configurando qual será o esquema padrão.
	//
	
	//
	// @todo; Criar uma função que selecione qual dois esquemas serão usados
	//        apenas selecionando o ponteiro da estrutura.  
	//
	
	
    switch(type)
	{
		case ColorSchemeNull:
		    CurrentColorScheme = (void*) humility;
		    break;
		
		case ColorSchemeHumility:
		    CurrentColorScheme = (void*) humility;
		    break;
		
		case ColorSchemePride:
	        CurrentColorScheme = (void*) pride; 
		    break;
		
		default:
		    CurrentColorScheme = (void*) humility;
			break;
	}	
	

done:	
	return;
};


/*
 * windowShowWWFMessageBuffers:
 *     Mostra o buffer de mensagens da janela com foco de entrada.
 *     #Rotinas de teste. @todo: Enviar para a pasta /test.
 *     Esse rotina funcionou e se mostrou bem útil.
 */
void windowShowWWFMessageBuffers()
{
	struct window_d *wFocus;
    wFocus = (void *) windowList[window_with_focus];

	int i;
	//Obs: Tipo.
	for( i=0; i<32; i++){
	    printf("%d ", wFocus->msgList[i]);
    };
    return;	
};


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
	wFocus = (void *) windowList[window_with_focus];
	
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
			wFocus->hwndList[wFocus->sendOffset]  = (unsigned long) 0; //arg1;
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
};


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
	wFocus = (void *) windowList[window_with_focus];
	
	//Desejamos usar a janela com o foco de entrada.
	//if(  (void*) window != (void*) wFocus  )
	//{
	//	printf("windowGetMessage: window != wFocus \n");
	//	refresh_screen();		
	//	window = (void*) wFocus;
	//};
	
	
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
	wFocus = (void *) windowList[window_with_focus];
	
	//Desejamos usar a janela com o foco de entrada.
	//if(  (void*) window != (void*) wFocus  )
	//{
	//	printf("windowGetLong1: window != wFocus \n");
	//	refresh_screen();		
	//	window = (void*) wFocus;
	//};
	
	
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
	wFocus = (void *) windowList[window_with_focus];
	
	//Desejamos usar a janela com o foco de entrada.
	//if(  (void*) window != (void*) wFocus  )
	//{
	//	printf("windowGetLong2: window != wFocus \n");
	//	refresh_screen();		
	//	window = (void*) wFocus;
	//};
	
	
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
 *     Cria um buffer dedicado de acordo com as dimensões da janela.
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
	if( (void*) window == NULL ){ 
	    return; 
	};  
    
	CurrentWindow = (void*) window;
	current_window = (int) window->id;
    return;
};


/*
 * get_current_window: 
 *     Get current window pointer.
 */
void *get_current_window(){
	return (void *) CurrentWindow;
};


/*
int get_current_window_id();
int get_current_window_id()
{
    return (int) current_window;	
};
*/


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
		die();
		//refresh_screen();
		//while(1){}
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
	
	
	//Parent window.
	if( (void*) gui->main == NULL){
	    return;
	};
	
	unsigned long left   = gui->main->left;
	unsigned long top    = gui->main->top;
	unsigned long width  = gui->main->width;
	unsigned long height = gui->main->height;	
	
		
	//@todo: Chamar método.	
	//Cursor.
	g_cursor_x = (left/8);
	g_cursor_y = (top/8);  
	//set_up_cursor(0,10);
	
	//
	// Se estamos no modo gráfico.
	//
	
	
	//
	// @todo: Usar esquema de cores padrão.
	//
	
	if(VideoBlock.useGui == 1)
	{
		//Parent window.
	    if( (void*) gui->main == NULL){
	        return;
	    };
			
	    //Create.
	    hWindow = (void*) CreateWindow( 3, 0, VIEW_MAXIMIZED, "//KERNEL Window List", 
	                                    left, top, width, height, 
			     				        gui->main, 0, KERNEL_WINDOW_DEFAULT_CLIENTCOLOR, KERNEL_WINDOW_DEFAULT_BGCOLOR ); 

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
		// Obs: @todo:Acho que essa não é a forma correta de configurar isso. Uma 
		//rotina deveria perceber as dimensões da janela de do caractere e determinar
		//as margens.
		
		g_cursor_left   = (hWindow->left/8);
		g_cursor_top    = (hWindow->top/8) + 4;   //Queremos o início da área de clente.
		g_cursor_right  = g_cursor_left + (width/8);
		g_cursor_bottom = g_cursor_top  + (height/8);
		
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
		g_cursor_left   = (left/8);    //0;
		g_cursor_top    = (top/8);        //0;
		g_cursor_right  = (width/8);   
		g_cursor_bottom = (height/8);  
		
		//cursor (0, mas com margem nova)
		g_cursor_x = g_cursor_left; 
		g_cursor_y = g_cursor_top;
        //set_up_cursor(g_cursor_left,g_cursor_top); 		


		StatusBar(hWindow,"Esc=EXIT","Enter=?");		
		//Nothing.
	};	   

    // Continua ...
	
done:
    //@todo; Aqui podemos dar refresh apenas na janela
	refresh_screen();
    //SetFocus(hWindow);
    return;
};


/*
 * redraw_window:
 *     O OBJETICO DESSA ROTINA DEVE SER APENAS REPINTAR UM RETÂNGULO
 * QUE FOI PINTADO DENTRO DA ÁREA DE CLIENTE DA JANELA QUE FOI PASSADA 
 * VIA ARGUMENTO.  @TODO 
 * Obs: Esse retângulo deve pertencer a janela que foi passada por argumento.
 * na estrutura de retângulo deve haver um ponteiro para  ajanela à qual ele pertence.
 * também deve-se repintar os elementos incluidos na área de cliente pelo programa aplicativo.
 * a estrutura de janela deve registrar totos os elementos que foram incluidos na hora da sua criação.
 * *****************
 *     Repinta uma janela de acordo com os parâmetros na estrutura.
 *     Repinta uma janela válida. Tem que estar registrada. 
 *     @todo: Mudar para windowRedrawWindow(.)
 * Obs: Esse é o tipo de rotina que exige o recurso de buffer dedicado.??
 * Pois podemos redezenhar a janela em seu buffer dedicado e depois copiar
 * o conteúdo do buffer dedicado para o backbuffer... na hora de atualizar a tela
 * é so copiar o backbuffer no frontbuffer(LFB).

 * pois bem, essa janela vai ter muitos elementos para incluir isso leva muito tempo.
 * Devemos registrar na estrutura da janela todos os botões que ela tem.
 * todos os textos gravados nela... todas as cores etc..
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
	
	//used magic
	if( window->used != 1 || window->magic != 1234 ){
		return (int) 1;
	};
	
	
	//@todo: Pra que serva a flag redraw ??
	// É para indicar que repecisamos repintar. ??
	//if( window->redraw != 1 ){ return (int) 0;}
	
	//
	// Ok, pelo jeito já temos uma estrutura válida.
	//
	
	// Minimized? Se tiver minimizada, não precisa repintar.
	//então está tudo certo?? retorna 0??
	Status = (int) is_window_minimized(window);
    if(Status == 1){
	    return (int) 0;  //??
	};	
	
	//E se ela estiver travada ??
	//O que significa travada?? não pode se mover??
	// ?? travada pra quem ??
	//if(window->locked == 1){}
	
	//@todo:
	//docked ?? num canto da tela.

	
	//Pintar ?? Onde ?? backbuffer ?? dedicated buffer ??
//drawWindow:	
	
	// *********************************
	// Devo lembrar que as características da janela estão salvas na estrutura
	// e são muitas características. Não exige cálculos, toda a métrica já está pronta.
	// *********************************
	
	
	//Buffers ??
	//window->DedicatedBuffer
	//window->BackBuffer
	//window->FrontBuffer
	
	
	//
	// *Importante: Checando se o esquema de cores está funcionando.
	//
	
	if( (void*) CurrentColorScheme == NULL ){
		printf("redraw_window: CurrentColorScheme");
		die();
		//refresh_screen();
		//while(1){}
	}else{
		
		if( CurrentColorScheme->used != 1 || CurrentColorScheme->magic != 1234 ){
		    printf("redraw_window: CurrentColorScheme validation");
		    die();
			//refresh_screen();
		    //while(1){}			
		};
		//Nothing.
	};	
	
	// ****************************
	// Importante:
	// Agora na hora de efetivamente redezenhar podemos ver na estrutura
	// quais são os elementos presentes nela. Lembrando que esses elementos 
	// podem ter sido modificados, então o melhor lugar para pegar essas
	// informações é na estrutura mesmo, pois lá serão salvos as preferências
	// atuais do usuário em relação a janela que deve ser repintada.
	// Ex: O usuário pode ter redimencionado ou arrastado elementos da janela,
	// ou ocultado apenas. Afinal, feito escolhas ... usuarísses.
	//*************************************
	
    //
	// Redraw !
	//	
	
redrawBegin:


	if( window->view == VIEW_NULL ){
		//@todo: temos um problema, dvemos retornar??
	    //return NULL;
	};		

    //Sombra.	
	if(window->shadowUsed == 1)
	{
        drawDataRectangle( window->left +1, 
		                   window->top  +1, 
						   window->width  +1 +1,   // @todo: Adicionar a largura da bordas bordas verticais e barra de rolagem se tiver.
						   window->height +1 +24 +1,   // @todo: Adicionar as larguras das bordas horizontais e da barra de títulos.
						   xCOLOR_GRAY1 );         //Cinza escuro.       
	};

    //Background.
	if(window->backgroundUsed == 1)
	{		
	    //if( (unsigned long) type == WT_SIMPLE){
		//    window->color_bg = color;
		//};
		
		//Validando o argumento para todos os tipos de janelas.
		window->color_bg = xCOLOR_GRAY2;  //CINZA UM POUQUINHO MAIS CLARO.
		
		//@todo: Se tiver barra de rolagem a largura do backgrond deve ser maior.
		//if()
		
		//@todo: Passar a estrutura de janela.
		drawDataRectangle( window->left, 
		                   window->top, 
						   window->width,  // @todo: Adicionar a largura da bordas bordas verticais.
						   window->height, // @todo: Adicionar as larguras das bordas horizontais e da barra de títulos.
						   window->color_bg );      	
	};
	
	
	
    //Título + borda.	
	if(window->titlebarUsed == 1)
	{ 
		//Focus.
		//Cores diferentes se tiver foco e se não tiver.
		if(window->id == window_with_focus){
		    window->color_bg = CurrentColorScheme->elements[csiActiveWindowTitleBar]; 
		}else{
			window->color_bg = CurrentColorScheme->elements[csiInactiveWindowTitleBar]; 
		};
		
		//@todo: String color.
		
		//@todo: String size.
		
		//@todo: Se tiver barra de rolagem, a largura deve ser maior.
		//if()
		
		//Rectangle and string.
		
        drawDataRectangle( window->left, 
		                   window->top, 
						   window->width  +1 +1,  // @todo: Adicionar a largura da bordas bordas verticais.
						   window->height +1 +24 +1, // @todo: Adicionar as larguras das bordas horizontais e da barra de títulos.
						   window->color_bg );
						   
		//ressaltando a barra de títulos da janala com o foco de entrada.
        //quem deve ser pintada diferente é a janela com o foco de entrada e não a janela ativa.						   
        if(window->id == window_with_focus)
		{
            drawDataRectangle( window->left, 
		                       window->top, 
				    		   window->width  +1 +1,  // largura do retângulo que marca que a janela está ativa.
						       4,                     // altura do retângulo que marca que a janela está ativa.
						       COLOR_SALMON );			
		}
						   
		//@todo: Se estivermos em full screen, não teremos string.				   
		draw_string( window->left +8 +16 +8, 
		             window->top +8 +4, 
					 COLOR_PINK,  //*test
					 window->name );  
					 
					 
	    //Isso é um teste.
	    //A janela nem foi registrada ainda e já estamos passando o handle
	    //via argumento.
		
	    //So criamos o botão na barra de títulos se tivermos uma barra de títulos.
		//então esse é o lugar certo para essa rotina.
		
		//@todo: Se estivermos em full screen, não teremos botão.	
		if(window->minimizebuttonUsed == 1)
		{
			//Quando passamos o handle da janela, a função draw_button
			//obtem as margens que precisa. nos resta passarmos os 
			//deslocamentos em relação às margens. (x=window->width-?) (y=2).
			//A função draw_button vai somar a margem obtida pelo handle 'window'
			//ao deslocamento obtido em (x=window->width-?).
	        draw_button( window, "V", 1, 
			             (window->width -42 -1), 4, 
						 21, 21, 
						 COLOR_BUTTONFACE);	
	    };
		
		//@todo: Se estivermos em full screen, não teremos botão.
	    if(window->closebuttonUsed == 1)
		{
	        draw_button( window, "X", 1, 
			            (window->width -21), 4, 
						21, 21, 
						COLOR_BUTTONFACE);				
	    };					 
					
		//More??...			 		 
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
			printf("redraw_window: a estrututura de client falhou");
			die();
			//refresh_screen();
            //while(1){}			
		     
		}else{
			
			//conferir validade.
			if( window->rcClient->used != 1 || window->rcClient->magic != 1234 ){
			    printf("redraw_window: validade falhou");
			    die();
				//refresh_screen();
                //while(1){}							
			}
		    
            //dimensões e posicionamento da área de cliente.
			//Esse é o posicionamento e as dimensões da janela propriamente dita.
			//Nesse espaço serão incluídos elementos adicionais.
			//Essa é a parte que deve parecer em full screen.
			window->rcClient->x  = (unsigned long)(window->left +1);     //+ borda
            window->rcClient->y  = (unsigned long)(window->top  +1 +24); //+borda +barra de títulos.     
            window->rcClient->cx = (unsigned long)(window->width);    
            window->rcClient->cy = (unsigned long)(window->height);	
            
            window->rcClient->width  = (unsigned long) window->rcClient->cx;
            window->rcClient->height = (unsigned long) window->rcClient->cy;
			
            window->rcClient->left   = (unsigned long) window->rcClient->x;
            window->rcClient->top    = (unsigned long) window->rcClient->y;
  			window->rcClient->right  = (unsigned long) (window->rcClient->left + window->rcClient->width);
			window->rcClient->bottom = (unsigned long) (window->rcClient->top + window->rcClient->height);
		
		    //zerando o deslocamento.
		    window->rcClient->x = 0;
			window->rcClient->y = 0;			
			
			//draw
            drawDataRectangle( (unsigned long) window->rcClient->left, 
		                       (unsigned long) window->rcClient->top, 
						       (unsigned long) window->rcClient->width, 
						       (unsigned long) window->rcClient->height, 
						       (unsigned long) window->rcClient->color_bg );         
							    
		};
		//Nothing.
	};




	//
	// Outros elementos ainda não implementados ...
	//
	
	//checar na estrutura se essa janela tinha:
	//botões ?? botões de radio ?? textos ?? barras ??
	//etc ...


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
 * redraw_screen:
 *     Repinta todas as janelas com base na zorder.
 *     @todo: Obs: Ao repintar cada janela a rotina redraw_window deverá 
 * incluir todos os elementos da janela. Do mesmo jeito que o usuário 
 * modificou de acordo com suas prefeências.
 *
 */
int redraw_screen()
{
	int z;
    int RedrawStatus;	
	struct window_d *zWindow;
	
	//
	// Vamos procurar na lista por ponteiros válidos.
	// Repintaremos todas as janelas com ponteiros válidos.
	//
	
	for( z = 0; z < ZORDER_COUNT_MAX; z++ )
	{
	    zWindow = (void*) zorderList[z];
	
		//Pegando um ponteiro de janela válido na zorderList.
		if( (void*) zWindow != NULL )
		{
			if( zWindow->used == 1 && zWindow->magic == 1234 )
            {
				//compara os índices.
				if( zWindow->zIndex != z ){
					printf("redraw_screen: z index error\n");
					goto fail;
				};
				
				//retira o foco.
				//KillFocus(zWindow);
				
				//Repinta uma janela.
				RedrawStatus = (int) redraw_window(zWindow);
				if(RedrawStatus == 1){
					printf("redraw_screen: redraw error\n");
					goto fail;
				};
				//Nothing.
			};
        //Nothing.			
		};
       //nothing.
	};	

	//#bugbug ?? Repintaremos duas vezes a última janela.
    // Repintaremos novamente a última janela.
    //Agora com foco de entrada.	

    if( (void*) zWindow != NULL )
	{
		if( zWindow->used == 1 && zWindow->magic == 1234 )
		{
            set_active_window(zWindow);	
            SetFocus(zWindow);

	        //Repinta uma janela.
	        RedrawStatus = (int) redraw_window(zWindow);
	        if(RedrawStatus == 1){
		        printf("redraw_screen: redraw error\n");
		        goto fail;
	        };
		};
	};
	
	
//Seo for terminar corretamente é porque repintamos tudo o que foi possível.	
//Nothing.
done:	
    return (int) 0;	
fail:
    printf("redraw_screen: FAIL.\n");
    die();
	//while(1){}
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
 *     Obs: O ato de fechar uma janela está associado
 *          ao ato de encerrar um processo. Mas nem sempre.
 *     *Importante: @todo: Fechar  ajanela qui deve signifcicar apenas 
 * sinalizar para o GC que ele pode atuar sobre a estrutura.
 */
void CloseWindow(struct window_d *window)
{
	int Offset;
	
	//Check.
	if( (void*) window == NULL ){ 
	    return; 
	};
	
	//Obs:
	// Não fechamos a janela principal.
	//Se for a janela principal.
	//if( (void*) window == (void*) gui->main ){
	//	return;
	//}
	
	//
	// ?? E as threads e processos associados à essa janela ??
	//

	// Focus.
	KillFocus(window);

	
    //Se temos uma janela mãe válida. Ela herda o foco.
	if( (void*) window->parent != NULL )
	{
        if( window->parent->used == 1 && window->parent->magic == 1234)
        {			
            set_current_window(window->parent); 
	        set_active_window(window->parent);
            SetFocus(window->parent);
        }; 		
    };
	
	
	//
	// devemos retirar a janela da zorder list 
	//
	
	int z = (int) window->zIndex;
	
	if( z >= 0 && z < ZORDER_COUNT_MAX )
	{
		//retira da lista
	    zorderList[z] = (unsigned long) 0;	
	    
		//atualiza o contador.
        zorderCounter--;
	   
	    if(zorderCounter < 0 ){
		    zorderCounter = 0;
        }
	};
	
	
    //Sinaliza para o GC.
	window->used = WINDOW_GC;       //216;
	window->magic = WINDOW_CLOSED;  //4321;
	
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
 *   Obs: Apenas sinalizaremos para o GC.
 */
void DestroyWindow(struct window_d *window){	
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
 ****************************************************
 * set_active_window:
 *     Seleciona qual será a janela ativa.
 *     Ativa uma janela.
 */
void set_active_window(struct window_d *window)
{
	//Check window.
	if((void*) window == NULL ){ 
	    return; 
	}else{

	    if( window->used == 1 && window->magic == 1234 )
		{
		    window->relationship_status = (unsigned long) WINDOW_REALATIONSHIPSTATUS_FOREGROUND;

			//Estrutura global
	        ActiveWindow = (void *) window;

		    //Variável global
            active_window = (int) window->id;				
		}
	};
	//Nothing.
done:
    return;
};


/*
 * change_active_window:
 *     @todo: Trocar a janela ativa
 */
void change_active_window(int id)
{
	// @todo: Limits. Max.
    if(id < 0){
	    return;
	};
	active_window = (int) id;
};


/*
 * show_active_window:
 *     Mostra o id da janela ativa.
 *     @todo: Mudar o nome para windowShowActiveWindowId() 
 */
void show_active_window(){
	printf("ActiveWindowId={%d}\n", (int) active_window);
};

/*
 * show_window_with_focus:
 *     Mostra o id da janela com o foco de entrada..
 */
void show_window_with_focus(){
	printf("wwfId={%d}\n", (int) window_with_focus);
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
};

void windowUnblockFocus(){
	gFocusBlocked = (int) 0;
};


/*
 *****************************************************
 * SetFocus:
 *     Atribui o foco à uma janela e possível.
 *     //Por enquanto estamos implementando a possibilidade
 * de travar a obtenção de foco, somente para teste... porem 
 * isso pode ser útil depois.
 */
void SetFocus(struct window_d *window)
{
	
	int i;
	
	//Impossível mudar o focus.
	//Isso manterá o foco na janela do desenvolvedor
	//durante a fase de criação da interface gráfica.
	//if( _lockfocus == 1){
	//	return;
	//};
	
	// Quando uma janela recebe o foco de entrada, ela vira a janela ativa, 
	// porém se ela tiver uma janela mãe, então a janela mãe será a 
	// janela ativa.
	
    if( (void *) window == NULL )
	{
		//Isso e recursivo, pode dar problema.
		//SetFocus(gui->screen);    
		return;
	}else{
		
		if( window->used == 1 && window->magic == 1234 )
		{
			//Se a janela é a janela ativa.
			if( window->id == active_window )
			{
		        //Procedure.
		        //?? Não sei se é o ideal.
		        SetProcedure((unsigned long) window->procedure);
		    
			    //set wwf pointer.
			    WindowWithFocus = (void *) window;

	            //set wwf id.
			    window_with_focus = (int) window->id;
				goto done;
				
			};
			
			//Se ela não é a janela ativa, tentamos ativar sua janela mãe.			
			if( window->id != active_window )
			{
				
			    //Se a janela mãe tem um ponteiro inválido. Ativamos a janela filha. 
		        if( (void*) window->parent == NULL ){
			        set_active_window(window);				
		        }

		        //Ativar a janela mãe se ela tem um ponteiro válido.
		        if( (void*) window->parent != NULL )
		        {
			        if( window->parent->used == 1 && window->parent->magic == 1234 ){
			            set_active_window(window->parent);	
			        };
		        };
				
		        //Procedure.
		        //?? Não sei se é o ideal.
		        SetProcedure((unsigned long) window->procedure);
		    
			    //set wwf pointer.
			    WindowWithFocus = (void *) window;

	            //set wwf id.
			    window_with_focus = (int) window->id;
                goto done;				
			};
			
			//
			// Se a janela for um editbox, ela precisa ter seu input resetado..
			// para que o procedimento de janela do kernel possa usá-lo.
			// por enquanto, faremos isso para todos os tipos de janelas.
			//
			
			//Resetando o input do procedimento de janela.
			
	        g_cursor_left   = (window->left/8);
	        g_cursor_top    = (window->top/8);   
	        g_cursor_right  = g_cursor_left + (window->right/8);
	        g_cursor_bottom = g_cursor_top + (window->height/8);
	
            g_cursor_x = g_cursor_left; 
	        g_cursor_y = g_cursor_top;  		
	
	        for(i=0; i<PROMPT_MAX_DEFAULT;i++)
	        {
		        prompt[i] = (char) '\0';
		        prompt_out[i] = (char) '\0';
		        prompt_err[i] = (char) '\0';
	        };
            prompt_pos = 0;				
		    
			//... 				
		};
		
	};
	
done:	
	//Nothing.
	return;
};


/*
 * GetFocus: 
 *     Pega o ponteiro para a estrutura da janela com o foco de entrada.
 */
void *GetFocus(){
    return (void *) windowList[window_with_focus];	
};



/*
 * windowGetForegroundWindow:
 * recupera o handle da janela que o usuário está trabalhando.
   ou seja, a janela em primeiro plano.
 */
void *windowGetForegroundWindow(){
    return (void *) windowList[window_with_focus];		
};

/*
 * windowSetForegroundWindow:
 *     coloca uma janela em primeiro plano para o usuário trabalhar nela.
 *     @todo: aumentar aprioridade da thread que configurou a janela de primeiro plano.
 *     +o input do teclado deve vi pra essa janela.
 *     +modificações visuais deve ocorrer na janela que está em primeiro plano, para 
 * que ela se destaque.
 * retorno: 0=OK  , 1=error.
 */
int windowSetForegroundWindow(struct window_d *window)
{
	if( (void *) window == NULL ){
		return;
	};
	SetFocus(window);
	set_active_window(window); 
	
	//@todo: aumentar a prioridade da thread.
	return (int) 0;
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
	int CurrentID;
	int NextID;

    struct window_d *window;
	struct window_d *next;	
	//...
	
	//Max e Current.
	Max     = (int) windows_count;
	CurrentID = (int) window_with_focus;	//salva
	
	//
	// @todo: 
	// Essa rotina precisa ser refeita. Seguindo uma lista linkada de janelas.
	//
	
	window = (void*) windowList[window_with_focus];	
	
	if( (void*) window == NULL ){
	    return;    
	}else{
		
	    KillFocus(window);  //Kill.
		
		//Se a próxima janela é válida.
		if( (void*) window->next != NULL )
		{
		    next = (void*) window->next;  //Get next.
		   	    
		    NextID = (int) next->id;     //Current id.
		   
		    //Se estiver dentro dos limites usaremos a próxima.
		    if(NextID > 0 && NextID < Max){
		        window_with_focus = (int) NextID;
	        }else{
			    window_with_focus = (int) CurrentID;	
			}			

		    window = (void*) windowList[window_with_focus];			
            SetFocus(window);
			goto done;			
		}else{
		    window_with_focus = (int) CurrentID;	
		    window = (void*) windowList[window_with_focus];			
            SetFocus(window);
            goto done;  			
		};
		//Fail.
	};
	//Nothing.
done:
    redraw_window(window);
	
    //Debug message:  
	//@todo: Criar mecanismo melhor pra mostrar a janela com o foco.
    //printf("Focus={%d}\n", (int) window_with_focus);
	//refresh_screen();
	
	return;
};


/*
 *************************************
 * KillFocus:
 *     Uma janela perde o foco.
 */
void KillFocus(struct window_d *window)
{
    //Check.
	if( (void *) window == NULL ){ 
	    return; 
	};
	
	//Focus.
	//window->focus = (int) 0;
    
	// ?? @todo: Quem deve receber o foco nesse caso ??
	// ?? um índice antes no zorder ??
	
	if( (void*) gui->main != NULL )
	{
		if( gui->main->used == 1 && gui->main->magic == 1234 ){
	        window_with_focus = (int) gui->main->id;
		};
	}
	//
	// Pra onde vai o foco ??
	//
	
	//set next window
	if( (void*) window->parent != NULL )
	{
		if( window->parent->used == 1 && window->parent->magic == 1234 ){
		    SetFocus(window->parent); 	
		} 	    
    };	
	
done:
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
    KillFocus(window);
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
    set_active_window(window);
	SetFocus(window);
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
		die();
		//refresh_screen();
		//while(1){}
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
#ifdef KERNEL_VERBOSE
    printf("done!\n");
#endif
    return (int) 0;
};


/*
 *******************************************************
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
		die();
		//refresh_screen();
		//while(1){}
	}else{
	    setClientAreaRect( 0, 0, 0, 0);	
	};
	
	
	//
    // Set fonts. @todo: Criar uma estrutura para características do char.
	//
		
	// 8x8 
	g8x8fontAddress  = (unsigned long) BIOSFONT8X8; //0x000FFA6E;    //ROM.
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
	//@todo: Isso poderia ter um argumento, selecionado entre o 
	//tipo 1 e 2, humility e pride.
	//ColorSchemeHumility ou ColorSchemePride
	windowSetUpColorScheme(ColorSchemePride);	
	
	//input buffer support ??
	//output buffer support ??
	
	
	//inicializar as estruturas de backbuffer e frontbuffer.
	
//
// Backbuffer support. (espelho da memória de video)
//
	
	BackBufferInfo = (void*) malloc( sizeof(struct backbufferinfo_d) );
    if((void*) BackBufferInfo == NULL){
	    //fail	
	}else{
	    BackBufferInfo->used = 1;
        BackBufferInfo->magic = 1234;
        //BackBufferInfo->start = ?
        //BackBufferInfo->end = ?
        //BackBufferInfo->size = ?
        //...		
	};		
	

//
// Frontbuffer support. (memória de vídeo)
//
	
	FrontBufferInfo = (void*) malloc( sizeof(struct frontbufferinfo_d) );
    if((void*) FrontBufferInfo == NULL){	
	    //fail	
	}else{
		
		//Algumas informações foram enviadas pelo boot loader.
	    FrontBufferInfo->used = 1;
        FrontBufferInfo->magic = 1234;
        //FrontBufferInfo->start = ?
        //FrontBufferInfo->end = ?
        //FrontBufferInfo->size = ?	

        //FrontBufferInfo->width = ?	
        //FrontBufferInfo->height = ?	
        //FrontBufferInfo->bpp = ?			
		
        //... 

        //?? console ??		
	};		

	
	//
	// Continua ...
	//
	
done:	
    //printf("Done.\n");
	return (int) 0;
};


//pegando a z-order de uma janela.
int get_zorder( struct window_d *window )
{
    if( (void*) window != NULL ){
		return (int) window->zIndex;
	}		
fail:
	return (int) -1;
};


//pegando a o id da janela que está no topo da lista de uma janela.
struct window_d *getTopWindow(struct window_d *window)
{
	//refletindo ??
    //se um argumento for passado teremos que examinar a ordem das janelas filhas.	
	//sendo assim cada estrutura de janela precisa de uma lista de janelas filhas 
	// e a zorder delas ... 
	//
	//se nenhuma janela for passada como argumento 
	// teremos que olhar as janelas filhas da janela principal que é a gui->main ...
	//a janela gui->main pode ser a janela mae de todas as outras ...
	// sendo a janela gui->main a janela principal do processo kernel.
	//o processo explorador de arquivos poderá ser o processo que 
	//seja a mãe de todos os aplicativos de usuário ... então a 
	//z order na estrutura da janela desse aplicativo indica a ordem 
	//das janelas principais dos seus processos filhos ...
	//??
	// Uma estrutura de janela pode ter uma variável top_window indicando o id 
	// da janela que está no topo da z-order da janela.
	//
	
	
	if( (void*) window == NULL )
	{
		return ( struct window_d * ) windowList[top_window];
	};
	
	return NULL;
}; 


int get_top_window(){
	return (int) top_window;
};

//configurando a top window.
void set_top_window( int id )
{
	top_window = (int) id;
	return;
};

//fecha a janela ativa.
void closeActiveWindow()
{
    int ID;
	struct window_d *w;
	
	ID = get_active_window();
	
	w = (void*) windowList[ID];
	
	CloseWindow(w);
};


//encontrando um slot livre na z-order global de 
//overlapped windows.
int z_order_get_free_slot()
{
	int response;
	int z; 
	struct window_d *zWindow;

	for( z = 0; z < ZORDER_COUNT_MAX; z++ )
	{
	    zWindow = (void*) zorderList[z];
        
		//Obtendo um espaço vazio.
		//Se for NULL, então não tinha um ponteiro no slot.
		if( (void*) zWindow == NULL )
		{
			response = (int) z; 
			
			zorderCounter++;
			if(zorderCounter >= ZORDER_COUNT_MAX){
				printf("CreateWindow: zorderCounter\n");
				goto fail;
			}
            
			goto done; 				
		};		
		//Nothing
	};
	
fail:
    return (int) -1;
done:
    return (int) response;	
};

//
// End.
//

