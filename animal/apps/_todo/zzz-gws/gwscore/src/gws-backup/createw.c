/*
 * File: gws/gws/createw.c
 *
 * Descrição: 
 *     Gerencia os métodos de criação de molduras de janelas e de janelas simples.
 *     Rotina principal de criação de janelas.
 *     Faz parte do módulo Window Manager do tipo MB.
 *
 * Obs: Os métodos de criação de moldura de janelas podem coexistirem e serão
 *      gerenciados por esse módulo.
 *
 * *Importante:
 * Um dos métodos inclui várias chamadas ao sistema, sendo que a promeira 
 * chamada será uma uma inicialização da rotina de construção da moldura. Essa
 * inicialização deve garantir exclusividade à um processo, para que outro processo
 * não interrompa a criação da moldura enquanto a rotina em user mode estiver
 * enviando parâmetros para o kernel.
 *
 *
 * @todo: 
 * Toda vez que criarmos uma estrutura de janela devemos alocar memória para 
 * o seu buffer dedicado de acordo com as dimensões da janela e registrar o 
 * ponteiro para o buffer na estrutura de janela.
 * Uma das primeiras coisa a fazer é criar o buffer dedicado, que será
 * passado para as rotinas de pintura, para a pintura ser feita no buffer
 * dedicado. 
 *
 * IMPORTANTE: De toda forma, se a rotina de pintura, não pintar a janela no 
 * seu buffer dedicado, ela pintará no buffer default, que é o backbuffer e
 * perceberemos o erro facilmente, para corrigi-lo. Então, na hora de passar o 
 * conteúdo dos buffers para o LFB deve-se seguir a ordem de uma lista linkada 
 * cujo primeiro ponteiro é o Backbuffer. Por observação poderemos ver se
 * ela é flutuante ou não. Se é flutuante, é porque foi pintada em buffer dedicado,
 * se não é flutuante é porque foi pintada no buffer default, que é o Backbuffer.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - 2018 New features.
 *     ...
 */

 
/*
 Importante:
    
    Sobre janelas e frames:
    =======================

    Uma janela na verdade é um container, na forma de retãngulo, que
abrigará elemntos gráficos como botões, textos, etiquetas  etc...
    Uma Janela pode ou não conter uma moldura, chamada de Frame,
que é formada pela barra de títulos, pela borda, pela sombra...
    Uma janela em modo full screen não contém frame.

   Sobre a função CreateWindow(.):
   ==============================
   O propósito dessa função é a criação de vários tipos de janelas
   que serão utilizadas pelas aplicações. A função pode criar uma janela
   que contenha frame ou não.
   No momento da criação da janela de um aplicativo, a função CreateWindow
   chamará o procedimento de janela do aplicativo para ver as solicitações
   de criação de elementos extras, que devem ser incluídos na janela.

 */

/*
    *Importante:
	 Poderá haver mais de um método de criação de uma frame window.   
 */
 

#include <kernel.h>


//Herdadas do Boot Loader.
// De onde vem isso ?? head.s
// @todo: Devemos chamar o módulo hal para obtermos esses valores.
//depois salvamos em variáveis internas usadas pela gui.

extern unsigned long SavedBootBlock;
extern unsigned long SavedLFB;
extern unsigned long SavedX;
extern unsigned long SavedY;
extern unsigned long SavedBPP; 

//
// Identificação do processo chamador e da janela a ser criada.
//

/*
struct process_d *xxxCallerProcess;
struct window_d *xxxNewWindow;

//
// Status: Qual é o status? se estiver aberto é porque algum processo está
//         utilizando a rotina de criação de frame.
//

int createw_in_use;  //@todo: Essa variável precisa ser inicializada.

int createwInitialize();
int createwInitialize()
{
	int pid;
	
	//Ocupado.
	if(createw_in_use == 1){
		goto fail;
	}
	
	//desocupado.
	if(createw_in_use == 0)
	{
		createw_in_use = 1;
	    pid = (int) current_process; //@todo: Criar rotina para pegar o id.
		xxxCallerProcess = (void*) processList[pid];
		return (int) 0;
	}
	//Nothing.
fail:
    return (int) 1;	
};


void *createwNewWindow();
void *createwNewWindow()
{
	xxxNewWindow = (void*) malloc(...);
	if( (void*) xxxNewWindow == NULL  ){
		return NULL;
	}
	
	return (void*) xxxNewWindow;
}

 ... @todo: criar mais rotinas primitivas.

*/


/*
 ***************************************************************************
 * CreateWindow: 
 *     Cria uma janela com base em uma struct. Retorna o endereço da estrutura 
 * da janela criada, para que possa ser registrada na lista windowList[].
 * Obs: A contagem é feita quando registra a janela.
 *
 * @todo: É necessário definir claramente os conceitos de window e window frame...
 *        A construção dos elementos gráficos precisam de organização e hierarquia.
 *
 * Obs: Essa rotian pode criar tanto uma janela, quanto um frame ou um botão.
 *
 * @todo: Corrigir as dimensões da janela: 
 * *Importante: OS ARGUMENTOS DE DIMENSÕES SÃO PARA O RETÂNGULO QUE FORMA UMA ÁREA
 * QUE INCLUI DA ÁREA DO CLIENTE + BARRA DE FERRAMENTAS + BARRA DE MENU.
 * a barra de títulos faz parte da moldura.
 * O AS DIMENSÕES DO FRAME PODEM SER VARIADOS, DEPENDENDO DO ESTILO DA JANELA.
 *
 * Cria a janela dependendo do tipo:                              
 * =================================
 * WT_NULL          0 
 * WT_SIMPLE        1
 * WT_EDITBOX       2  // igual simples, mais uma bordinha preta.
 * WT_OVERLAPPED    3  // sobreposta(completa)(barra de titulo + borda +client area)
 * WT_POPUP         4  // um tipo especial de sobreposta,  //usada em dialog ou 
 *                        message box. (com ou sem barra de titulo ou borda)					   
 * WT_CHECKBOX      5  // Caixa de seleção. Caixa de verificação. Quadradinho.
 * WT_SCROLLBAR     6  // Cria uma scroll bar. Para ser usada como janela filha.
 * CONTINUA ...
 */

//1  - Tipo de janela (popup,normal,...) 
//2  - Estado da janela. (poderia ter vários bits ??)
//3  - (min, max ...)
//4  - Título.
//5  - Deslocamento em relação às margens do Desktop.
//6  - Deslocamento em relação às margens do Desktop.
//7  - Largura da janela.
//8  - Altura da janela.
//9  - Endereço da estrutura da janela mãe.
//10 - desktop ID. (# Para levarmos em conta as características de cada desktop).
//11 - Client Area Color.
//12 - color (bg) (para janela simples)
 
void *CreateWindow ( unsigned long type, 
                     unsigned long status, 
                     unsigned long view, 
                     char *windowname, 
                     unsigned long x, 
                     unsigned long y, 
                     unsigned long width, 
                     unsigned long height, 
                     struct window_d *pWindow, 
                     int desktopid, 
                     unsigned long clientcolor, 
                     unsigned long color ) 
{	
	// @todo: O argumento style está faltando.
	//        cada tipo de tanela poderá ter vários estilos.
	// Obs: Podemos ir usando apenas um estilo padrão por enquanto.
	
	// (min, max ...).
	int View;	

	// Bars.
	int TitleBar = 0;
	int MenuBar = 0;
	int ToolBar = 0;
	int StatusBar = 0;
	int ScrollBar = 0;
	//...
	
	// Title bar buttons. [v] [X] 
	int MinimizeButton = 0; 
	int MaximizeButton = 0; 
	int CloseButton = 0;    
    //..
	
	// Items.
	int Background = 0;
	int ClientArea = 0;
	int Shadow = 0;
	int ButtonDown = 0; //??
	int ButtonUp = 0;   //??
	int ButtonSysMenu = 0;  //system menu na barra de títulos.	
	int Border = 0;         //New !!! usado no edit box.
	//int ScrollBar;
	//...
	
	// Desktop support.
	int ParentWindowDesktopId;    //Id do desktop da parent window.
	int WindowDesktopId;          //Id do desktop da janela a ser criada.

	
	//controle de janela
	struct window_d *windowButton1;  //minimize	
    struct window_d *windowButton2;	 //maximize
	struct window_d *windowButton3;  //close
	
	//botões na barra de rolagem.
	struct window_d *windowButton4;
	struct window_d *windowButton5;
	struct window_d *windowButton6;
	
    // Structs.	
	struct window_d *window;
	struct window_d *Parent;
	struct desktop_d *Desktop;
    struct rect_d *clientRect;  //rect
	
	
	// #improvisando uma largura de borda.
	// @todo: isso deve ir para outro lugar.
	unsigned long border_size = 0;
	unsigned long border_color = COLOR_BORDER;
    	
	
	//salvar para depois restaurar os valores originais no fim da rotina.
	//unsigned long saveLeft;
	//unsigned long saveTop;
	
	
	// Desktop:
	// @todo: Configurar desktop antes de tudo. 
	// @todo: Quando criamos uma janela temos de definir que ela
	// pertence ao desktop atual se não for enviado por argumento 
	// o desktop que desejamos que a janela pertença.

	
	// O argumento onde:
	// Indica onde devemos pintar a janela. Serve para indicar as janelas 
	// principais. Ex: Se o valor do argumento for 0, indica que devemos 
	// pintar na tela screen(background) etc...


	// full screen mode ??
	// Se a janela a ser criada estiver no modo full screen, ela não deve ter
	// um frame, então as dimensões da janela serão as dimensões do retângulo
	// que forma a janela. Talvez chamado de Client Area.
	
	//
	// Parent window.
	//
	
	// Se a parent window enviada por argumento for inválida, 
	// então usaremos a janela gui->screen. ?? 
	// Talvez o certo fosse retornar com erro.
	// ?? Qual deve ser a janela mãe ? Limites ?
	// @todo: devemos checar used e magic da janela mãe.
	// #bugbug: E quando formos criar a gui->screen, quem será a janela mãe ?
	
	if ( (void *) pWindow == NULL ){
		
		Parent = (void *) gui->screen;	
	
	} else {
		Parent = (void *) pWindow;
	};
	
	
	// Devemos checar se a janela está no mesmo desktop 
	// que a ajnela mãe.
	// No caso aqui, criarmos uma janela no mesmo desktop que a 
	// janela mãe.
	
	// Devemos setar uma flag que indique que essa 
	// é uma janela filha, caso seja uma. Essa flag 
	// deve ser passada via argumento @todo.

	// @todo: Checar se é uma janela filha, 
	// se for uma janela filha e não tiver uma janela mãe associada a ela, 
	// não permita e encerre a função.

	
	//if(FlagChild == 1)
	//{
		//if(pWindow = NULL) return NULL;
	//}
	

	// @todo: A atualização da contagem de janela deve ficar aqui,
	// mas me parece que está em outro lugar, ou não tem. ainda.
	
	// @todo: Se essa não for uma janela filha, então temos que resetar 
	// as informações sobre a janela mãe. porque não procedem.	
	
	//ms. e se essa é uma janela filha de uma janela mãe que pertence à
	//outra thread e não está no desktop ??
	
	
	// *Importante: 
	// Checando se o esquema de cores está funcionando.
	
	if ( (void *) CurrentColorScheme == NULL )
	{
		panic ("CreateWindow: CurrentColorScheme");
		//die();
		
	}else{
		
		if ( CurrentColorScheme->used != 1 || 
		     CurrentColorScheme->magic != 1234 )
		{
		    panic ("CreateWindow: CurrentColorScheme validation");
		    //die();			
		}
		
		//Nothing.
	}
	
	
	//
    // ## New window ##
    //	
	
//CreateStruct:
	
	//Alocando memória para a estrutura da janela.
	
	window = (void *) malloc ( sizeof(struct window_d) );	
	
	if ( (void *) window == NULL )
	{
        // @todo: 
		// Onde o Kernel colocará essa mensagem de erro ?
		// Por enquanto no backbuffer.
		
		// Erro.
		printf("CreateWindow: window struct \n");
		refresh_screen();	
		
		return NULL; 
		
    }else{
        
		// Obs: 
		// Conseguimos alocar memória para a estrutura da janela. 
		// Agora vamos inicializar os elementos da estrutura de acordo 
		// com os parâmetros passados via argumento.
		
		// Object support.
		window->objectType = ObjectTypeWindow;
		window->objectClass = ObjectClassGuiObjects;

		// #importante
		// Id. A janela recebe um id somente na hora de registrar.
		// window->id = ??.

	    //Name.
		window->name = windowname;
		
		// Segurança.
		window->used = 1;
		window->magic = 1234;
		
	    // Window type.
        // Tipo é unsigned long pois poderá ser um conjunto de flags.		
	    window->type = (unsigned long) type;
		
		//@todo: Criar instância.
		
		//@todo: é importante definir o procedimento de janela desde já.
		//senão dá problemas quando chamá-lo e ele naõ estiver pronto.

		//Procedure support.
		//@todo: Devemos receber esses parâmetros e configurar aqui.
		//window->procedure = (unsigned long) &system_procedure;
		//window->wProcedure = NULL;  //Estrutura.
		
		
		//Modo de exibição:
		window->view = (int) view;
		
		// Se não estivermos no modo gráfico, não há o que pintar.
		if ( g_useGUI == 0 )
		{ 
		    window->view = (int) VIEW_MINIMIZED;
            //#bugbug: Abortar.			
		};

        //Se não foi oferecido um modo de exibição, então temos um problema.
        //?? Talvez devamos retornar um erro. 
		//if( (int) view == VIEW_NULL ){ return NULL; };		
		
		//??Qual é o status da janela, se ela é a janela ativa ou não.
		//?? Devemos definir quais são os status possíveis da janela.
		//
		
		//active 
		if( status == WINDOW_STATUS_ACTIVE )
		{ 
		    active_window = (int) window->id;  
            //set_active_window(window); 		
		    //window->active = WINDOW_STATUS_ACTIVE;
			//window->status = (unsigned long) WINDOW_STATUS_ACTIVE;
			window->relationship_status = (unsigned long) WINDOW_REALATIONSHIPSTATUS_FOREGROUND; 
            window->zIndex = 0; // ?? inicializando apenas. @todo:getNextZAxisOrder()
			//...			
		};
		
		//inactive
		if( status == WINDOW_STATUS_INACTIVE )
		{ 
		    //window->active = WINDOW_STATUS_INACTIVE;
			//window->status = (unsigned long) WINDOW_STATUS_INACTIVE;
			window->relationship_status = (unsigned long) WINDOW_REALATIONSHIPSTATUS_BACKGROUND;
            window->zIndex = 0; //inicializando apenas. @todo:getNextZAxisOrder()
			//...			
		};	
		
		
		//focus	
		//window->focus = 0; //determinando que não temos o foco.

		// @todo:
		// Se for uma janela filha o posicionamento deve ser somado às margens 
		// da área de cliente da janela que será a janela mãe.

		// #bugbug @todo 
		// Esses valores de dimensões recebidos via argumento na verdade 
		// devem ser os valores para a janela, sem contar o frame, que 
		// inclui as bordas e a barra de títulos.

		// Dimensões.	
        window->width = width;
        window->height = height;  
		
		// Margens.
		window->left = x;    
        window->top = y;
        window->right = (unsigned long) ( window->left + window->width );
        window->bottom = (unsigned long) ( window->top + window->height );       

		// Deslocamentos em relação às margens.
		// Os deslocamentos servem para inserir elementos na janela, como barras, botões e textos.
		window->x = 0;
        window->y = 0;		
		
		// ?? saving.
		//saveLeft = window->left;
		//saveTop  = window->top;
		
		//
		//  ## color ##
		//
		
		// Background support.
		window->bg_color = (unsigned long) color; 
		window->clientrect_bg_color = (unsigned long) clientcolor;
		
		// ??
		// O retângulo da janela.
		//window->rcWindow = NULL;
		
		//
		// # Cursor support #
		//
		
		window->CursorX = 0;
		window->CursorY = 0;
		window->CursorColor = COLOR_WINDOWTEXT; 
		//@todo: As outras características do cursor.
		//Características.		
		
		//Estrutura para cursor.
		window->cursor = NULL;
		//@todo: Uma opção é inicializarmos a estrutura de ponteiro depois ...
		//pois tem janela que não tem ponteiro. JA QUE NO MOMENTO ESTAMOS ENFRENTANDO ALGUNS TRAVAMENTOS.
		//
		//window->cursor = (void*) malloc( sizeof(struct cursor_d) );
		
		//@@todo: Criar uma função: Inicializarcursor(struct cursor_d *cursor).
		//if(window->cursor != NULL)
		//{
		//    window->cursor->objectType = ObjectTypeCursor;
		//    window->cursor->objectClass = ObjectClassGuiObjects;
		//	window->cursor->x = 0;
		//	window->cursor->y = 0;
		//	window->cursor->imageBuffer = NULL;
		//	window->cursor->imagePathName = NULL;
			//window->cursor->cursorFile = ??; //@todo: Difícil definir o tipo.
		//	window->cursor->cursorType = cursorTypeDefault;
		//};
		
		//cursores (parar de usar e começar usar apenas a estrutura.)
		window->cursor_x = 0;
		window->cursor_y = 0;
		
		//Barras.
		//As flags que representam a presença de cada uma das barras
		//serão acionadas mais tarde, na hora da pintuda, de acordo com
		//o tipo de janela à ser pintada.
		
		//Current message.
		//Msg support.
		window->msg_window = (void *) window;
		window->msg = 0;
		window->long1 = 0;
		window->long2 = 0;
		
		//Se tem ou não uma nova mensagem.
		window->newmessageFlag = 0;
		
		//Filas de mensagens.
		//São dessas filas que os programas em user mode
		//são pegar as mensagens, solicitando através de system call.
		window->hwndList[0] = 0;
		window->msgList[0] = 0;
		window->long1List[0] = 0;
		window->long2List[0] = 0;
		
		//Offsets
		window->sendOffset = 0;
		window->receiveOffset = 0;
		
		//Buffers support.
		
		//Dedicated buffer: 
		//Cria um buffer dedicado de acordo com as dimensões da janela.		
		window->DedicatedBuffer = (void*) windowCreateDedicatedBuffer(window);
		
		//O backbuffer é a janela do desktop ao qual a janela pertence.
		//window->BackBuffer = (void*) windowGetBackbufferAddress(); //@todo: Criar função.
		//window->BackBuffer = (void*) g_backbuffer_address;
		window->BackBuffer = (void*) g_backbuffer_va;
		
		//o frontbuffer é o endereço da memória de vídeo para o monitor
		//que se deseja mostrar a janela. (LFB, cr3)
		window->FrontBuffer = (void*) g_frontbuffer_pa;
		
	    //@todo:
	    //Se não for uma Child, deve-se resetar todas as informações relativas
	    //à parent window.
		
		//Parent support
		window->parent = (void*) Parent;
		window->parentid = (unsigned long) Parent->id;
		
		//Child window linked list.
		window->childListHead = NULL;
		
		// (#importante)
		// Client window support.
		// Obs: A área de cliente será um retângulo e não uma janela.
		// Mas nda impede da estrutra gerenciar uma janela que fique 
		// em cima da área de cliente.
		window->client_window = NULL;  //window. 
		window->rcClient = NULL;       //rect. (#importante)
		
		// #importante
		// Terminal support.
		// Suporte não tradicional à terminais.
		// manipulando variáveis ao invés de uma estrutura.
		window->terminal_used = (int) 0;
		window->terminal_magic = (int) 0;
		window->terminal_tab = (int) 0;
		window->teminal_left = (unsigned long) 0;
		window->teminal_top = (unsigned long) 0;
		window->teminal_width = (unsigned long) 0;
		window->teminal_height = (unsigned long) 0;
		
		//Desktop support.
		//window->desktop = (void*) Desktop; //configurado anteriormente.
		//window->desktop_id = Desktop->id;  //@todo: verificar elemento.
		
		// # Menu support #
	    window->menu_window = NULL;    
		window->sysMenu = NULL;  
		window->barMenu = NULL;  
		window->defaultMenu = NULL; 
		window->isMenu = 0;
		window->isButton = 0;
		window->isEditBox = 0;
		window->selected = 0;  //Caso a janela seja um ítem de menu.
		//window->text = NULL; //Texto, caso a janela seja um ítem de menu

		//Draw support.
		window->draw = 0;      //@todo: Cuidado com isso.
		window->redraw = 0;
	    window->show = 1; //Inicialmente presumimos que precisamos mostrar essa janela.
	    //Continua ...
	
        //Abaixo, elementos referenciados com menor frequência.
	    
		window->desktop = NULL; //@todo: Definir à qual desktop a janela perence.
		window->process = NULL; //@todo: Definir à qual processo a janela perence.
		
		//Trava.
		window->locked = 0;
		
		//Linked list.
		//window->linkedlist = NULL;
		
		//Prev e next.
		window->prev = (void*) Parent;
		window->next = NULL;
			
		//#debug
		//printf("config1 %s %d %d %d %d \n",
		//    window->name, window->left, window->top, window->width, window->height );
	};
	
    //Exemplos de tipos de janelas, segundo MS.	
    //Overlapped Windows
    //Pop-up Windows
    //Child Windows
    //Layered Windows
    //Message-Only Windows	
	
	//
	// Preparando os parametros da pintura de acordo com o tipo.
	//	

	// De acordo com o tipo de janela, preparamos a configuração
	// e a própria rotina create window está pintando.
	// Porém nesse momento o 'case' pode chamar rotinas de pintura em 
	// draw.c e retornar. 
	// CreateWindow é para criar a moldura principal ...
	// para so outros tipos de janelas podemos usar draw.c
	// pois quando chamarmos draw.c a estrutura de janela ja deve estar 
	// inicializada.
	// Rotinas grandes como pintar um barra de rolagem podem ficar em draw.c
	
	// #importante
	// Deveria ter uma variável global indicando o tipo de 
	// design atual, se é 3D ou flat.
	
	
	// Configurando os elementos de acordo com o tipo.
	// @todo: Salvar as flags para os elementos presentes
	// na estrutura da janela.
	
    switch (type)
    {
		//0) Null.
		//Ainda não implementada.
		case WT_NULL:
		    return NULL; 
		    break;
		
		//    **** WINDOW ****
		// A window is an undecorated Frame.
		//1) Simple rect, (Sem barra de títulos).
		//Obs: para o tipo 1 é fundamental considerar a cor passada por argumento.
		case WT_SIMPLE:
	        Background = 1;    //bg.
			window->backgroundUsed = 1;
		    break;

		// 
		//2) Edit box, (Simples + borda preta).
        //editbox não tem sombra, tem bordas. 
		case WT_EDITBOX:
            Background = 1;    //bg.
	        window->backgroundUsed = 1;
            Border = 1;
		    //window->borderUsed = 1;@todo: isso ainda não existe na extrutura ??	
		    break;

		//   **** FRAME ****
		// 3) Overlapped, (completa, para aplicativos).
		// Obs: Nessa caso, como se trata de uma janela de aplicativo,
		// poderíamos configurar a área de cliente.
		case WT_OVERLAPPED:
	        Shadow = 1;           // Sombra.
	        Background = 1;       // bg.
	        TitleBar = 1;         // Título + Borda.
		    ClientArea = 1;
			
			//essas flags farão a chamar createwindow 
			//recursivamente para desenhar os botões.
			
			//Controle de janela.
			//Botões da barra de tírulos.
			MinimizeButton = 1;   
		    MaximizeButton = 1;   
			CloseButton = 1;       
			
		    //MenuBar       = 1;  // Barra de menu. 
	        //ButtonSysMenu = 1;    // System menu button. ??
		    window->shadowUsed = 1;
		    window->backgroundUsed = 1;
		    window->titlebarUsed = 1;
		    window->clientAreaUsed = 1;
		    //@todo:
		    //Se for do tipo overlapped pode ser ou não a janela ativa.
		    //set_active_window(window);
		    break;

		//4) Popup (um tipo de overlapped mais simples).
		case WT_POPUP:
	        Shadow = 1;        //sombra.
	        Background = 1;    //bg.
		    window->shadowUsed = 1;
		    window->backgroundUsed = 1;		
		    //if(titulo){} TitleBar = 1;    //titulo + borda	
		    break;
 
		//5) Check box, (Simples + borda preta).
        //   Caixa de seleção. Caixa de verificação. Quadradinho.
		case WT_CHECKBOX:
	        Background = 1;    //bg.
		    window->backgroundUsed = 1;
            //bordas.
            Border = 1;
 			//window->borderUsed = 1;@todo: isso ainda não existe na extrutura ??
		    break;
			
		//6) scroll bar.
        // Cria uma scroll bar. Para ser usada como janela filha.
		case WT_SCROLLBAR:
			//Background = 1;    //bg.
		    //window->backgroundUsed = 1;
            //bordas.
            //Border = 1;
 			//window->borderUsed = 1;@todo: isso ainda não existe na extrutura ??
		    break;
			
		// 8) button
        //Obs: existe uma rotina que desenha um botão.
        //quando create window for chamada para criarmos um botão 
        //podemos chamar essa rotina que desenha o botão ...
        //apenas isso.	
        //aqui nesse case podemos selecionar algumas caractrerísticas 
        //do botão que são acionadas através das características 
        //da janela.  		
		case WT_BUTTON:	
            //Nothing for now ...
            //Deixaremos a rotina de desenhar o botão fazer tudo por enquanto.			
			break;	
			
		//9) Status bar.	
		case WT_STATUSBAR:
	        Background = 1;    //bg.
			window->backgroundUsed = 1;
		    break;
			
		//barra de rolagem
		//botões de radio .. 
		//...

        // Continua ...
		
		//Ainda não implementada.
        default:
            return NULL;  		
		    break;
	};	
	
	// Continua...
	
	// * Draw !
	// Hora de pintar. Os elementos serão incluídos se foram 
	// selecionados anteriormente.
	
//drawBegin:	

	// Obs: Se for uma janela, pintaremos apenas a janela.
	//      Se for um frame, pintaremos todos os elementos
	//      presentes nesse frame de acordo com as flags.
	// Obs:
	// A janela precisa ser pintada em seu buffer dedicado.
	// Nesse momento o buffer dedicado da janela já está na estutura
	// da janela. Rotinas de pintura que tenham acesso à estrutura da
	// janela devem utilizar o buffer dedicado que for indicado na estrutura.
	// Para que seja possível pintar uma janela em seu buffer dedicado,
	// devemos passar um ponteiro para a estrutura da janela em todas
	// as rotinas de pintura chamadas daqui pra baixo.
	//
	// @todo: Passar estrutura de janela via argumento, para a rotina
	// de pintura ter acesso ao buffer dedicado.
	
	//if(DedicatedBuffer == 1){};
	
	
	// se o view for igual NULL talvez signifique 
	if ( window->view == VIEW_NULL )
	{
		//#bugbug: fail.
		//window->show = 0;
		//window->redraw = 0;
		//return (void*) window;
	}
	
	// Minimized ? 
	// Se tiver minimizada, não precisa mostrar a janela, porém
	// é necessário pintar a janela no buffer dedicado, se essa técnica 
	// estiver disponível.
	// Talvez antes de retornarmos nesse caso seja necessário configurar 
	// mais elementos da estrutura.
	
	//#bugbug
	//se estamos contruindo a janela, então ela não foi registrada 
	//não podemos checar as coisas na estrutura ainda,
	//mas a estrutura ja existe a algumas coisas foram inicializadas.
	
	View = 0;
	View = (int) is_window_minimized(window);
	
    if ( View == 1 )
	{
		//window->draw = 1; //Devemos pintála no buffer dedicado.
		window->show = 0;
		window->redraw = 0;
		//...
		
		//@todo: Não retornar. 
		//como teste estamos retornando.
		//goto done;
	    return (void *) window;
	}
	
	// @todo: Maximized ?
	// Para maximizar devemos considerar as dimensões da área de cliente
	// da janela mãe.
	// Se a jenela estiver maximizada, então deve ter 
	// o tamanho da área do cliente, caso ela seja uma janela filha.
	// Essa área de cliente poderá ser a área de trabalho, caso a
	// janela mãe seja a janela principal.
	// Obs: se estiver mazimizada devemos usar as dimensão e coordenadas 
	// da janela gui->main.
	
	View = 0;
	View = (int) is_window_maximized(window);
	
    if ( View == 1 )
	{
		//Dimensões.	
        window->width  = gui->main->width;
        window->height = gui->main->height;  
		
		//Margens.
		window->left = gui->main->x;    
        window->top = gui->main->y;
        window->right = (unsigned long) window->left + window->width;
        window->bottom = (unsigned long) window->top  + window->height;       

		//Deslocamentos em relação às margens.
		// Os deslocamentos servem para inserir elementos na janela, como barras, botões e textos.
		window->x = 0;
        window->y = 0;		
	}	

    //  # FULL SCREEN #

	//??
	//entrar no modo full screen deve ser sempre uma iniciativa do usuário.
	//apenas um comando do usuário pode colocar uma janela no modo full screen.
	
    //View = 0;
	//View = (int) is_window_full(window);
    //if(View == 1){
	//	//...
	//}		
	
	//Se estivermos em full screen, mudaremos algumas caracteríticas.
	// Não usaremos frame: nem borda nem barra de títulos.
	//if( window->view == VIEW_FULL )
	//{
    //    Shadow = 0;
	//	TitleBar = 0;
		
        //Dimensões:
		//??@todo: deveríamos chamar métodos que peguem
		//a métrica do dispositivo. ex getmetricsDeviceWidth();
	//	window->left = 0; 
	//	window->top = 0; 
	//	window->width = 800;  //@todo: getmetricsDeviceWidth();
	//	window->height = 600;
						           
	//	window->titlebarUsed = 0;
	//}
	

	// Color:
	// Obs: @todo: Isso foi definido acima, foi passado por argumento e
	// colocado na estrutura. Fiacrá assim somente por teste,
	// depois deletaremos essa definição aqui.
	//*Importante: Devemos utilizar a cor que foi passada via argumento?!
	// senão todas as janelas terão a mesma cor.
	
	// Sombra:
	//     A sombra pertence à janela e ao frame.
	//     A sombra é maior que a própria janela.
	//     ?? Se estivermos em full screen não tem sombra ??
	
	//  ## Shadow ##
	
	if ( Shadow == 1 )
	{
		//flag.
		window->shadowUsed = 1;
		
		//CurrentColorScheme->elements[??]
		
		//@todo: 
		// ?? Se tiver barra de rolagem a largura da 
		// sombra deve ser maior. ?? Não ...
		//if()
		
        // @todo: Adicionar a largura das bordas verticais 
		// e barra de rolagem se tiver.
		// @todo: Adicionar as larguras das 
		// bordas horizontais e da barra de títulos.
		// Cinza escuro.  CurrentColorScheme->elements[??] 
		// @TODO: criar elemento sombra no esquema. 
		
		if ( (unsigned long) type == WT_OVERLAPPED )
		{	
			drawDataRectangle ( window->left +1, window->top +1, 
				window->width +1 +1, window->height +1 +1, xCOLOR_GRAY1 );             
        }

        // ??
		// E os outros tipos, não tem sombra ??
		// Os outros tipos devem ter escolha para sombra ou não ??
		// Flat design pode usar sombra para definir se o botão 
		// foi pressionado ou não.
		
		//...
	}
	
	// ## Background ##
	//    Background para todo o espaço ocupado pela janela e pelo seu frame.
			
	// Background.
	if ( Background == 1 )
	{
		// Flag.
        window->backgroundUsed = 1;
		
		window->bg_color = CurrentColorScheme->elements[csiWindowBackground]; 
	    
		// O argumento 'color' será a cor do bg para alguns tipos.
		// Talvez não deva ser assim. Talvez tenha que se respeitar o tema instalado.
		if( (unsigned long) type == WT_SIMPLE ){ window->bg_color = color; };
		if( (unsigned long) type == WT_POPUP ){ window->bg_color = color; };
		if( (unsigned long) type == WT_EDITBOX){ window->bg_color = color; }
		if( (unsigned long) type == WT_CHECKBOX){ window->bg_color = color; }
		//if( (unsigned long) type == WT_SCROLLBAR){ window->bg_color = color; }
		//...
		
		//Pintar o retângulo.
		// @todo: ?? width Adicionar a largura da bordas bordas verticais.
		// @todo: ?? height Adicionar as larguras das bordas horizontais e da barra de títulos.
		
		if ( (unsigned long) type == WT_STATUSBAR )
		{
		    drawDataRectangle ( window->left, window->top, 
			    window->width -1, window->height, window->bg_color ); 	
						   
		    draw_string ( window->left +8, window->top +8, COLOR_TEXT,  
		  	  window->name ); 	
			goto done;
		}
		
		drawDataRectangle ( window->left, window->top, 
			window->width, window->height, window->bg_color ); 
		

        //?? More ...	
	}

	
	// ## Title bar ##
    // Título + borda(frame).
    
    // #importante: 
    // Sobre bordas. 
    // Isso pinta a barra de títulos e as bordas para janelas de 
    // aplicativos. Ou seja, as bordas não são pintadas individualmente nesse 
    // momento, mas logo abaixo, pintaremos as bordas para as janelas onde 
    // esse for o caso. Só falta criar elemento na estrutura para gerenciar 
    // as bordas.	
    
    //parametros 16=icone 8=paddings
	
	if ( TitleBar == 1 )
	{ 
        //flag.
        window->titlebarUsed = 1;
        
		window->bg_color = color;  
		
		//@todo: String color.
		
		//@todo: String size.
		
		//@todo: Se tiver barra de rolagem, a largura deve ser maior.
		//if()
		
		//Rectangle and string.
		
		//#importante
		//retângulao
		//??width  @todo: Adicionando a largura da bordas bordas verticais.
		//??height @todo: Adicionando as larguras das bordas horizontais e da barra de títulos.
						   
		drawDataRectangle ( window->left, window->top, 
			window->width +1 +1, window->height +1 +1, window->bg_color );
        
		// String		
		draw_string ( window->left +16 +8 +8, window->top +(32/3), 
			COLOR_TERMINALTEXT2, window->name );  
		
								 		
	    // ??
		// Só criamos o botão na barra de títulos se tivermos uma barra de títulos.
		// Então esse é o lugar certo para essa rotina.
		// @todo: Se estivermos em full screen, não teremos botão.	
		
		if (MinimizeButton == 1)
		{
			window->minimizebuttonUsed = 1;
			
            // Create button.			
			windowButton1 = CreateWindow ( WT_BUTTON, 1, 1, "V", 
	                           (window->width -32 -32 -1 -32 -1), 2, 32, 32,									  
			                   window, 0, 
							   (unsigned long) COLOR_TERMINAL2, (unsigned long) COLOR_TERMINAL2);	
			
			RegisterWindow (windowButton1);
			window->minimize = windowButton1;
	    }
		
		if (MaximizeButton == 1)
		{
			window->maximizebuttonUsed = 1;
			
            // Create button.			
			windowButton2 = CreateWindow ( WT_BUTTON, 1, 1, "^", 
	                           (window->width -32 -32 -1), 2, 32, 32,									  
			                   window, 0, 
							   (unsigned long) COLOR_TERMINAL2, (unsigned long) COLOR_TERMINAL2);	
			
			RegisterWindow (windowButton2);
			window->minimize = windowButton2;
	    }
	
	    if (CloseButton == 1)
		{
			window->closebuttonUsed = 1;
			
			// Create button.
			windowButton3 = CreateWindow ( WT_BUTTON, 1, 1, "X", 
	                            (window->width -32), 2, 32, 32,									  
			                    window, 0, 
								(unsigned long) COLOR_TERMINAL2, (unsigned long) COLOR_TERMINAL2 );	
            
			RegisterWindow (windowButton3);
			window->close = windowButton3;
	    }					 
		
		//...			 
	};	
	
	
	//#debug
    //if ( (unsigned long) type == WT_OVERLAPPED )
	//{
	//    printf("CreateWindow: #debug");
	//	refresh_screen();
	//	while(1){}
	//}
	
	// ## Border ##
	// BORDA COLOR_INACTIVEBORDER 
	// Borda para as janelas.
	// Obs: As bordas dependem do tipo de janela e do 
	// estilo de janela.
	
	//vamos pintar a borda de acordo com o status da janela.
	//se a janela for um botão, e pintarmos essa borda, 
	//na hora de desenhar o botão essa borda vai desaparecer.
	//para isso podemos simplesmente, desenha um botão menor que 
	//a janela dele.
	
	if ( Border == 1 )
	{
		//flag.
		window->borderUsed = 1;
		
		//#importante:
		//devemos tratar a borda para cada tipo de janela individualmente.

		//botão
		if ( window->type == WT_BUTTON )
		{
			//se o botão tiver o foco.
			if ( window->focus == 1 )
			{
				border_color = COLOR_BLUE;
			    border_size = 2;
			}else{
			    border_color = COLOR_INACTIVEBORDER;	
			    border_size = 1;
			}
		};
		
		//editbox
		if ( window->type == WT_EDITBOX )
		{
			//se tiver o foco.
			if ( window->focus == 1 )
			{
				border_color = COLOR_BLUE;
			    border_size = 2;
			}else{
			    border_color = COLOR_INACTIVEBORDER;	
			    border_size = 1;
			}
		};		
		
		//overlapped (app)
		if ( window->type == WT_OVERLAPPED )
		{
			//se tiver o foco.
			if ( window->focus == 1 )
			{
				border_color = COLOR_BLUE;
			    border_size = 2;
				
				if (window->active == 1){
				    border_size = 3;	
				}
				
			}else{
			    border_color = COLOR_INACTIVEBORDER;	
			    border_size = 1;
			}
		};	

		//simple.
		if ( window->type == WT_SIMPLE )
		{
			//se tiver o foco.
			if ( window->focus == 1 )
			{
				border_color = COLOR_GRAY;
			    border_size = 2;
			}else{
			    border_color = COLOR_INACTIVEBORDER;	
			    border_size = 1;
			}
		};		
		



		
		
		// A largura da borda pode sinalizar o status (ativo ou inativo) 
		// de uma caixa de edição.
		
		//#todo: a largura da borda deve ficr registrado na estrutura.
		
		//if ( status == 0 ){ 
		//    border_size = 1;
        //    border_color = COLOR_INACTIVEBORDER; 			
		//}
		
		//if ( status == 1 ){ 
		//    border_size = 2; 
		//    border_color = COLOR_BLUE;
		//}
		//if( status == 2 ){ border_size = 3; } //just for fun
		
	    //board1, borda de cima e esquerda.    
		drawDataRectangle( window->left, 
		    window->top, window->width, border_size, border_color );
						   
	    drawDataRectangle( window->left, 
		    window->top, border_size, window->height, border_color );

	    //board2, borda direita e baixo.
	    drawDataRectangle( window->left +window->width -1, 
	        window->top, border_size, window->height, border_color );
					   
	    drawDataRectangle ( window->left, window->top +window->height -1, 
			window->width, border_size, border_color );
		
	};	
	
	
	//#debug
    //if ( (unsigned long) type == WT_OVERLAPPED )
	//{
	//    printf("CreateWindow: #debug");
	//	refresh_screen();
	//	while(1){}
	//}
	
	// # Client Area #
	// #importante
    // @todo: 
    //     RESPEITAR A IMPORTÂNCIA DESSE ELEMENTO.	
    //     PERMITIR QUE MAIS TIPOS DE JANELA TENHAM CLIENT AREA.
    // Nesse caso deveremos considerar o tipo de janela na hora de  
    // criarmos a client area, pois tem janela que tem barra de títulos 
    // e tem janela que não tem, tem janela que bordas e tem janela que 
    // não tem.
    // #Testando para diferentes tipos de janela.
	
    if ( ClientArea == 1 )
	{
		//flag.
		window->clientAreaUsed = 1;
		
		// Obs: A Client Area é apenas um retângulo.
		//@todo: Passar a estrutura de janela.
		
		clientRect = (void *) malloc ( sizeof(struct rect_d) ); 
		
		if ( (void *) clientRect == NULL )
		{
			//free(clientRect);
		    window->rcClient = NULL;
			
            // O que acontece nesse caso?? 
			// Ficaremos sem área de cliente ??
			// #bugbug
			// Nenhum alerta será emitido aqui por enquanto.
			
		} else {
			
			//@todo: Criar função rectSetup(....)
			// Testando, isso pode falhar.
		    
			//
			// ?? DIMENSÕES DA JANELA: ??
			// A janela é um retângulo que pode conter elementos como:
			// barra de menu, barra de ferramentas.
			// O frame não pertence a jenela. O frame é composto
			//pela barra de títulos e a borda.
			//
			// Obs: A área de cliente deve ter as dimensões passadas
			//  via argumento.
			//

			//Salva o ponteiro.
			window->rcClient = (void*) clientRect;
			
			// Object stuff.
			window->rcClient->objectType = ObjectTypeRectangle;
			window->rcClient->objectClass = ObjectClassGuiObjects;
			
			// Validation.
			window->rcClient->used = 1;
			window->rcClient->magic = 1234;
			
			// janela.
			// O retângulo pertence à essa janela.
			window->rcClient->window = (void *) window; 
			
			// #importante
			// ( Posicionamento e dimencionamento. )
            // + Ajustando o posicionamento da área de cliente com base
            // no posicionamento e dimensões da janela.
			// + Nesse espaço serão incluídos elementos adicionais,
			// desenhados e repintados pelo próprio aplicativo.
			// + Essa é a única parte que deve aparecer quando o aplicativo
			// entrar em modo full screen.
			//
			
			// ## SIMPLE ##
			
			//#bugbug
			//Janela simples não deve ter área de cliente.

			if ( window->type == WT_SIMPLE )
			{	
				
					//#debug
                 //printf("createw: l={%d} t={%d} w={%d} h={%d}\n", 
	             //    window->left, window->top, window->width, window->height ); 	
				 //refresh_screen();
				 //while(1){}
				
                //left top
                window->rcClient->left = (unsigned long) (window->left);
                window->rcClient->top = (unsigned long) (window->top);
            
                // width e height.
                // width = window widdth - as bordas verticais.
                // height = windows height - as bordas horizontais - a barra de títulos.
                window->rcClient->width = (unsigned long) (window->width);
                window->rcClient->height = (unsigned long) (window->height);
				
				//window->rcClient->right = window->rcClient->left + window->rcClient->width;
				//window->rcClient->bottom = window->rcClient->top + window->rcClient->height;
			};			
			
			
			// ## OVERLAPPED WINDOW ##
			
            if ( window->type == WT_OVERLAPPED )
            {
			    //left top
                window->rcClient->left = (unsigned long) (window->left +1);
                window->rcClient->top = (unsigned long) (window->top  +2 +32 +2);
            
                // width e height.
                // width = window widdth - as bordas verticais.
                // height = windows height - as bordas horizontais - a barra de títulos.
                window->rcClient->width = (unsigned long) (window->width -1 -1);
                window->rcClient->height = (unsigned long) (window->height -2 -32 -2 -24 -2);
				
				//window->rcClient->right = window->rcClient->left + window->rcClient->width;
				//window->rcClient->bottom = window->rcClient->top + window->rcClient->height;
                
			};
			
			// ## EDITBOX ##

			if( window->type == WT_EDITBOX || 
			    window->type == WT_EDITBOX_MULTIPLE_LINES )
			{	
                //left top
                window->rcClient->left = (unsigned long) (window->left +1);
                window->rcClient->top = (unsigned long) (window->top  +1);
            
                // width e height.
                // width = window widdth - as bordas verticais.
                // height = windows height - as bordas horizontais - a barra de títulos.
                window->rcClient->width = (unsigned long) (window->width -1 -1);
                window->rcClient->height = (unsigned long) (window->height -1 -1);
				
				//window->rcClient->right = window->rcClient->left + window->rcClient->width;
				//window->rcClient->bottom = window->rcClient->top + window->rcClient->height;
			};
			
			//right bottom.
			//válido para todos os tipos de janela.
  			window->rcClient->right = (unsigned long) (window->rcClient->left + window->rcClient->width);
			window->rcClient->bottom = (unsigned long) (window->rcClient->top + window->rcClient->height);
			
			
            // #bugbug Isso pode dar problemas.		
		    // Deslocamento dentro da área de cliente.
            // Zerando o deslocamento.
		    window->rcClient->x = 0;
			window->rcClient->y = 0;
			
		    //
			// * ESSA COR FOI PASSADA VIA ARGUMENTO.
			//
			
			//#debug
			//window->rcClient->bg_color = (unsigned long) COLOR_YELLOW; 
            
			window->rcClient->bg_color = (unsigned long) window->clientrect_bg_color;	      	      
			
			//
			// Draw!
			//
			
			
            drawDataRectangle( (unsigned long) window->rcClient->left, 
		                       (unsigned long) window->rcClient->top, 
						       (unsigned long) window->rcClient->width, 
						       (unsigned long) window->rcClient->height, 
							   (unsigned long) window->rcClient->bg_color );
							   
            // Done.
		};
		//Nothing.
	};
	
	
	//#debug
    //if ( (unsigned long) type == WT_OVERLAPPED )
	//{
	//    printf("CreateWindow: #debug clientarea ok");
	//	refresh_screen();
	//	while(1){}
	//}
	
	
	//@todo: janela com scroll bar padrão.
	//if( ScrollBar == 1 ){}

	//MenuBar (teste)
    /*   
    if(MenuBar == 1)
	{
	    create_menubar(window);
        initmenuArray( window->barMenu, 2);    //Quantidade.
        create_menubar_item(window->barMenu,"Item1",1);    /Selected
        create_menubar_item(window->barMenu,"Item2",0); 		
	};
	*/
	
	// SCROLL BAR
	//se create window foi usada para criar uma janela filha do tipo scroll bar. 		
	//completaremos 
	if ( (unsigned long) type == WT_SCROLLBAR )
	{

		
        //bg
		drawDataRectangle ( window->left, window->top, 
			window->width, window->height, window->bg_color ); 
						   
	    
		//#importante 
		//#todo
        Parent->scrollbarUsed = 1;
		Parent->scrollbar = window;

		
		//Botão de cima da scrollbar vertival
		
		// Criar.
		windowButton4 = CreateWindow ( WT_BUTTON, 1, 1, "^", 
	        1, 1, (window->width -2), 32,									  
		    window, 0, (unsigned long) COLOR_TERMINAL2, (unsigned long) COLOR_TERMINAL2);
        
		// Registrar.
		RegisterWindow (windowButton4);  		
        window->scrollbar_button1 = windowButton4; 
		
		//#test	
	    //limits
	    if ( window->height == 0 || window->height > SavedX ){ 
		    window->height = 2; 
		}

	    //Botão do meio da scrollbar vertival
		
		// Criar.
		windowButton5 = CreateWindow( WT_BUTTON, 1, 1, "=", 
	        1, (window->height/2), (window->width -2), 32,									  
		    window, 0, (unsigned long) COLOR_TERMINAL2, (unsigned long) COLOR_TERMINAL2);	
		
		// Registrar.
		RegisterWindow (windowButton5);
		window->scrollbar_button3 = windowButton5;
		
	    //botão 2 da barra horizontal.
        //Botão de baixo da scrollbar vertival
	    
		// Criar.
		windowButton6 = CreateWindow( WT_BUTTON, 1, 1, "v", 
	        1, (window->height -32 -1), (window->width -2), 32,									  
		    window, 0, (unsigned long) COLOR_TERMINAL2, (unsigned long) COLOR_TERMINAL2);			
	    
		// Registrar.
		RegisterWindow (windowButton6);
		window->scrollbar_button2 = windowButton6;
	};	

	
	//if ( (unsigned long) type == WT_STATUSBAR )
	//{
		//#debug 
		//printf("CreateWindow.WT_STATUSBAR\n");
		
	//	drawDataRectangle ( window->left, window->top, 
	//		window->width -1, window->height, window->bg_color ); 	
						   
		//draw_string ( window->left +8, window->top +8, COLOR_TEXT,  
		//	window->name );  
			
			
		//#importante 
		//#todo
        //Parent->statusbarUsed = 1;
		//Parent->statusbar = window;
	//};
	
	//JANELA DO TIPO BOTÃO.
	//#BUGBUG: NÃO TEMOS INFORMAÇÕES SOBRE O TIPO DE BOTÃO 
	//QUE DEVEMOS CRIAR. SÓ SABEMOS QUE A JANELA É DO TIPO BOTÃO.
	if ( (unsigned long) type == WT_BUTTON )
	{
	    //as posições de left e right são da janela do botão.	
        //#obs: Essa função retorna uma estrutura de botão.	
        //Então uma janela, quando acianoada sua flag que indica que ela é um botão,
        //podemos usar a estrutura de botão para acessar as características do botão.		
		

        window->button = (struct button_d *) draw_button ( Parent, windowname, BS_DEFAULT, 0, 0,		
                                                 window->left, window->top, window->width, window->height, 
                                                 window->bg_color );
		
		window->isButton = 1;	
	}	

    if ( (unsigned long) type == WT_EDITBOX )	
	{
		window->isEditBox = 1;
	}


	//
	// Continua ... ( Pinta detalhes da janela, caso ouver )
	//
	
	//Barras de rolagem ...
	//efeitos ...
	//itens de menus...
	//itens de barras ...
	//carrega ícones ...
	//Continua ...
	
	
	// Message: 
	// @todo: Enviar uma mensagem de CREATE pra janela.
	//        Assim o procedimento cria os elementos
	//        restantes.
		
	
	// @todo: Atualizar a linkedlist da parent window.
	
	
	// Overlapped.
	if (window->type == WT_OVERLAPPED)
	{
		active_window = window->id;
		window->active = 1;
		
		window_with_focus = window->id;
		window->focus = 1;
		
		// ## scrollbar ##
		//Esses valores precisam ser melhor declarados.
        
		//#BUGBUG
		//SÓ CRIAREMOS SCROLL BAR NUMA OVERLAPPED SE A FLAG INDICAR ISSO;
		//ISSO VALE PRA OUTROS TIPOS DE JANELA NÃO SOMENTE ESSE TIPO.
		
		// Criar.
		//window->scrollbar = CreateWindow ( WT_SCROLLBAR, 1, 1, "scrollbar-test", 
	    //                        window->right -40, window->top +2 +40 +2, 
		//						40, (window->height -2 -40 -2 -24 -2),									  
		//			            window, 0, 
		//						(unsigned long) CurrentColorScheme->elements[csiScrollBar], 
		//						(unsigned long) CurrentColorScheme->elements[csiScrollBar]);
		
		// Registrar.
		//RegisterWindow (window->scrollbar);


		
        // ## status bar ##
		//Esses valores precisam ser melhor declarados.
		
		//#BUGBUG
		//SÓ CRIAREMOS STATUS BAR NUMA OVERLAPPED SE A FLAG INDICAR ISSO;
		//ISSO VALE PRA OUTROS TIPOS DE JANELA NÃO SOMENTE ESSE TIPO.		
		
		window->statusbar = CreateWindow ( WT_STATUSBAR, 1, 1, "Status: ...", 
	                              window->left+1, window->bottom-25-1, 
								  window->width, 25,							  
					              window, 0, 
								  COLOR_BLUE, 
								  COLOR_GRAY );
        
		// Registrar.
		RegisterWindow (window->statusbar);
		
		window->statusbarUsed = 1;
		window->statusbar = window->statusbar;
        
        // # icon #
		// Os ícones já estão carregados, 
		// vamos apenas decodificá-lo no backbuffer 
		
	    bmpDisplayBMP ( appIconBuffer, window->left +8, window->top +8 );
	};
	
	
	//#debug
    //if ( (unsigned long) type == WT_OVERLAPPED )
	//{
	//    printf("CreateWindow: #debug scroll status and *icon ok");
	//	refresh_screen();
	//	while(1){}
	//}

	
	//Ex: if( sendMessage(.,.,.,.) == 0 )
	//{
	//	//apaga tudo, notifica o erro e retorna null.
	//	return NULL;
	//}
	
	
	// Nesse momento a janela já está criada, podemos configurar 
	// algumas globais importantes, como thread, desktop ...
	
	//atualizar parent and child links.
	
	//@TODO: ENVIAR UMA MENSAGEM PARA A JANELA QUE RETORNARÁ 
	//O TAMANHO OFICIAL DA JANELA DO CLIENTE.(STRUCT DE RECT)
	
	// #test
	// TEMOS QUE MANDAR UMA MENSAGEM DE 'MSG_CREATE' PRA JANELA,
	// SE ELA NÃO RESPONDER CORRETAMENTE, ENTÃO TEMOS QUE APAGAR TUDO O QUE
	// INICIALIZAMOS E NOTIFICAR O ERRO E RETORNAR NULL.

	//ENVIAMOS A MENSAGEM CREATE PRA JANELA. SEI LA, AVISANDO QUE CRIAMOS 
	//A A JANELA DO CLIENTE , ?? A JANELA DO CLIENTE É UMA JANELA NORMAL??
	//OU SÓ UM RETÂNGULO??
	
	//NOTIFICAR TODO MUNDO SOBRE O EVENTO DA CRIAÇÃO DA JANELA.
	//ALGUEM PODERIA ESTAR ESPERANDO POR ISSO...
	//DEVEMOS NOTIFICAR SOMENTE DEPOIS DE ENVIARMOS A MENSAGEM MSG_CREATE ...
	//E ANTES DE QUALQUER OPERAÇÃO DE MOVIMENTAÇÃO OU REDIMENSIONAMENTO DE JANELA ..
	//EXISTEM OBSERVADORES FAZENDO CONTAGEM DESSAS COISAS.

    //É HORA DE MINIMIZAR OU MAXIMIZAR, CONFORME FOI INDICADO POR QUEM
    //CHAMOU A FUNÇÃO PARA CRIAR A JANELA.

    //SE É UMA JANELA FILHA, DEVEMOS ENVIAR UMA MENSAGEM PRA JANELA PAI,
    //AVISANDO QUE A JANELA FILHA FOI CRIADA ... POIS ELE PODE ESTAR ESPERANDO 
    //POR ISSO. ... devemos travar a threadmae dessa janela antes de enviar a mensagem e 
    //depois destravar.

	// @todo: ShowWindow.

    //destravar a thread dessa janela e a thread mae antes de sair.
	
	
	
	// # zorder support #
	
	// Deve ter uma função que faça isso,
	// daí chamamos só a função.
	
	// Opções:
	// + z-order dos elementos gráficos dentro da janela mãe.
	// + z-order global da overlapped windows.
	
    //z-order global de overlapped windows.
	//@todo: Colocar essa definição no início da função.
    int z;
	z = (int) z_order_get_free_slot();	
    
	if( z >= 0 && z < ZORDER_COUNT_MAX )
	{
	    zorderList[z] = (unsigned long) window;
	};
	
	//@todo: z-order de elementos gráficos dentro da janela mãe.
 
// done.		
done:

    //Testando se a rotina modificou algum desses.
    //window->left =  saveLeft;
	//window->top  =  saveTop;
	
    //SetFocus(window);
	
	//if ( window->type == WT_BUTTON || 
    //     window->type == WT_STATUSBAR )
	//{
	//    RegisterWindow (window);	
	//}
	
	//#teste
	//Associando a janela criada a trhead atual, que chamou essa rotina.
	//o problema é na hora da inicialização.
	
		window->InputThread = (struct thread_d *) threadList[current_thread];
		
		if( (void *) window->InputThread != NULL )
        {
			if ( window->used != 1 || window->magic != 1234 )
			{
			    window->InputThread = NULL;	
			}
		}	
	    
	
	return (void *) window;
};

//
// End.
//
