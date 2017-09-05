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
 *      Não importa qual processo foi interrompida pela interrupção de 
 * teclado. A mensagem deve ir para a fila de mensagens da janela com o foco
 * de entrada.
 */	
void windowSendMessage(unsigned long arg1, unsigned long arg2, unsigned long arg3, unsigned long arg4)
{    
	struct window_d *wFocus;
		
		
	//
    // Não estamos falando de fila de mesagens na estrutura da janela,
	// portando se uma mensagem for enviada para uma estrutura de janela
	// ela irá sobrepor a mensagem antiga cao a mensagem aintiga ainda não tenha sido
	//consumida.
    //	
		
	//
	// @todo: 
	// Na verdade, aqui tem que mandar a mensage para a janela com o foco 
	// de entrada, mesmo que seja uma janela filha.
	//
		
	wFocus = (void *) WindowWithFocus;
		
	//
	// A janela atual, seria a janela ativa ?
	//
		
	//
	// Estamos apenas enviando para a janela com foco de entrada.
	//
		
    if( (void*) wFocus == NULL )
	{
        //@todo: não ha uma janela com o foco de entrada, retornar.		
        //system_dispatch_to_procedure( NULL, (int) mensagem, (unsigned long) ch, 0);
	    return;
	}
	else
	{	
		//Valida a estrutura da janela com o foco de entrada.
		if( wFocus->used == 1 && wFocus->magic == 1234 )
		{		
            wFocus->sendOffset++;
			if(wFocus->sendOffset >= 32){ wFocus->sendOffset = 0; };
	        
			//wFocus->hwndList[wFocus->sendOffset] = (unsigned long) arg1;
			wFocus->msgList[wFocus->sendOffset] = (unsigned long) arg2;
			//wFocus->long1List[wFocus->sendOffset] = (unsigned long) arg3;
			//wFocus->long2List[wFocus->sendOffset] = (unsigned long) arg4;
		}; 		
		
		//system_dispatch_to_procedure( wFocus, (int) mensagem, (unsigned long) ch, 0);
	};
	
	return;
}


/*
 * windowGetMessage:
 * Pega uma mensagem na estrutura da janela com o foco de entrada.
 * Obs: esse mecanismo deve ser reproduzido para os parametros
 * hwnd, long1 e long2.
 * as funções precisam ser criadas ainda. semelhantes a essa.
 */
void *windowGetMessage(struct window_d *window)
{
	void *kMSG;
	
	if((void*) window == NULL){ 
	    return NULL; 
	}else{			
		
		//
		// @todo: Quando pegar a mensagem no buffer, tem que colocar 
		// zero no lugar, pra não pegar novamente.
		//
				
		//Circula.
		window->receiveOffset++;
		if(window->receiveOffset >= 32){
			window->receiveOffset = 0;
		};
				
		//Pega mensagem.
		kMSG = (void*) window->msgList[window->receiveOffset]; 
				
		//Apaga a mensagem que foi consumida.
		window->msgList[window->receiveOffset] = 0; 
				
		//Retorna.
		return (void*) kMSG; 
	};
	
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
 * show_window_list:
 *     Mostra a lista de janelas registradas.
 *     windowShowWindowList().  
 */
void show_window_list()
{
	int i = 0;
	struct window_d *hWnd;
	struct window_d *hWindow;
	
	
	//Se não estivermos em modo gráfico.
    //Não há o que mostrar.	
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
	                                    (6*(800/20)), (4*(600/20)), 320, 480, 
			     				        gui->main, 0, 0, 0 );

	    if( (void*) hWindow == NULL){
	        printf("show_window_list:\n");
		    return;
        }else{
		    RegisterWindow(hWindow);
			set_active_window(hWindow);
			SetFocus(hWindow);
	    };										
		
		
		//Auterando a margem
		g_cursor_left = (hWindow->left/8);
		g_cursor_top =  (hWindow->top/8)+2;
		g_cursor_right = g_cursor_left+(320/8);
		g_cursor_bottom = g_cursor_top+(480/8);
		
		//cursor (0, mas com margem nova)
		g_cursor_x = g_cursor_left; 
		g_cursor_y = g_cursor_top; 
		

		//printf("test\n");
		
        while(i < WINDOW_COUNT_MAX)
        {	
	        hWnd = (void*) windowList[i];
		
		    //
		    // @todo: BUGBUG.
		    // O valor de hWnd tem que estar num limite válido, não adianta apenas ser
		    // diferente de NULL.
		    //
		
		    if( (void*) hWnd != NULL ){
				//draw_text( hWindow, 8,  1*(400/16), COLOR_WINDOWTEXT, "F1 Help.");
	            printf("Index={%d} Handle={%x} DedicatedBuffer={%x} Name={%s}\n", i, hWnd, hWnd->DedicatedBuffer, hWnd->name);
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
    return;
};


/*
 * redraw_window:
 *     Repinta uma janela de acordo com os parâmetros na estrutura.
 *     Repinta uma janela válida. Tem que estar registrada. 
 *     @todo: Mudar para windowRedraw(.)
 */
int redraw_window(struct window_d *window)
{
	int Status;
	unsigned long Type;
	
	//Checar se a estrutura é válida.
	if((void*) window == NULL){
		return (int) 1;
	};
	
	// Minimized ? Se tiver minimizada, não precisa repintar.
	Status = (int) is_window_minimized(window);
    if(Status == 1){
	    return (int) 1;
	};	
	
	
	//
	// Checar o tipo.
	//
	
	Type = (unsigned long) window->type;
	
	switch(Type)
	{
		case WT_NULL:
		    return (int) 1;
			break;
		
		case WT_SIMPLE:
		    //Nao tem borda.
		    break;

		case WT_EDITBOX:
		    DrawEditBoxWindow( window, window->x, window->y, window->width, window->height, window->color_bg);
		    break;

		case WT_OVERLAPPED:
		    DrawNormalWindow( window, window->name,window->x, window->y, window->width, window->height, window->color_bg);
			break;

		case WT_POPUP:
            DrawPopUpWindow( window, window->x, window->y, window->width, window->height, window->color_bg);
		    break;

		case WT_BUTTON_DOWN:
		    break;

		case WT_BUTTON_UP:
		    break;

		default:
		    return (int) 1;
		    break;
	};
	
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


/*
 * SetFocus:
 *     Atribui o foco à uma janela.
 */
void SetFocus(struct window_d *window)
{
    if( (void *) window == NULL ){
		
		//Isso pe recursivo, pode dar problema.
		//SetFocus(gui->screen);    
		return;
	}else{
		
		//Focus.
	    window->focus = (int) 1;
	    window_with_focus = (int) window->id;		
		WindowWithFocus = (void *) window;
		
		//Procedure.
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

