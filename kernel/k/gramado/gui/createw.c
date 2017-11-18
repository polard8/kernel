/*
 * File: createw.c
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
 *
 * Histórico:
 *     Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *     Versão 1.0, 2016 - Aprimoramento geral das rotinas básicas.
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
 * 1 - POP-UP.
 * 2 - EDIT-BOX.
 * 3 - NORMAL ( bg + client area ).
 * 4 - NORMAL_EDIT ( bg + editbox).
 * 5 - MENUBAR.
 * 6 - TOOLBAR.
 * 7 - STATUSBAR.
 * 8 - TASKBAR.
 * 9 - ? 
 * CONTINUA ...
 */
void *CreateWindow( unsigned long type, //1  - Tipo de janela (popup,normal,...)
unsigned long status,     //2  - Estado da janela (ativa ou nao)
unsigned long view,       //3  - (min, max ...)
char *windowname,         //4  - Título.                          
unsigned long x,          //5  - Deslocamento em relação às margens do Desktop.                           
unsigned long y,          //6  - Deslocamento em relação às margens do Desktop.
unsigned long width,      //7  - Largura da janela.
unsigned long height,     //8  - Altura da janela.
struct window_d *pWindow, //9  - Endereço da estrutura da janela mãe.
int desktopid,              //10 - desktop ID. (# Para levarmos em conta as características de cada desktop).
unsigned long clientcolor,  //11 - Client Area Color.
unsigned long color         //12 - color (bg) (para janela simples)
)
{
	int View;	//(min, max ...).

	//Bars.
	int TitleBar = 0;
	int MenuBar = 0;
	int ToolBar = 0;
	int StatusBar = 0;
	int ScrollBar = 0;
	//...
	
	//tile bar buttons
	int MinimizeButton = 0; // V (flecha para baixo)
	int CloseButton = 0;    // X.
    //..
	
	//Items.
	int Background = 0;
	int ClientArea = 0;
	int Shadow = 0;
	int ButtonDown = 0; //??
	int ButtonUp = 0;   //??
	int ButtonSysMenu = 0;  //system menu na barra de títulos.	

	//Desktop support.
    int ParentWindowDesktopId;    //Id do desktop da parent window.
	int WindowDesktopId;          //Id do desktop da janela a ser criada.
	

    //Structs.	
	struct window_d *window;
	struct window_d *Parent;
	struct desktop_d *Desktop;
    struct rect_d *clientRect;  //rect
	
	
	//salvar para depois restaurar os valores originais no fim da rotina.
	//unsigned long saveLeft;
    //unsigned long saveTop;
	
	//
	// Desktop:
	// @todo: Configurar desktop antes de tudo. 
	// @todo: Quando criamos uma janela temos de definir que ela
	// pertence ao desktop atual se não for enviado por argumento 
	// o desktop que desejamos que a janela pertença.
	//

	
	//
	// O argumento onde:
	// Indica onde devemos pintar a janela. Serve para indicar as janelas 
	// principais. Ex: Se o valor do argumento for 0, indica que devemos 
	// pintar na tela screen(background) etc...
	//


	//
	// full screen mode ??
	// Se a janela a ser criada estiver no modo full screen, ela não deve ter
	// um frame, então as dimensões da janela serão as dimensões do retângulo
	// que forma a janela. Talvez chamado de Client Area.
	//
	
	//
	// Parent window.
	//
	
	// Se a parent window enviada por argumento for inválida, então usaremos
	// a janela gui->screen. ?? Talvez o certo fosse retornar com erro.
	//@todo: devemos checar used e magic da janela mãe.
	if( (void*) pWindow == NULL ){
		Parent = (void*) gui->screen;	
	}else{
		Parent = (void*) pWindow;
	};
	
	//
	// @todo: Checar se é uma janela filha, se for uma janela filha e não tiver 
	// uma janela mãe associada a ela, não permita e encerre a função.
	//
	
	//
	// @todo: A atualização da contagem de janela deve ficar aqui,
	// mas me parece que está em outro lugar, ou não tem. ainda.
	// 
	
	//
	// @todo: Se essa não for uma janela filha, então temos que resetar 
	// as informações sobre a janela mãe. porque não procedem.
	//
	
	
	//
	//ms. e se essa é uma janela filha de uma janela mãe que pertence à
	//outra thread e não está no desktop ??
	//
	
	
	//
	// *Importante: Checando se o esquema de cores está funcionando.
	//
	
	if( (void*) CurrentColorScheme == NULL ){
		printf("CreateWindow: CurrentColorScheme");
		refresh_screen();
		while(1){}
	}else{
		
		if( CurrentColorScheme->used != 1 || CurrentColorScheme->magic != 1234 ){
		    printf("CreateWindow: CurrentColorScheme validation");
		    refresh_screen();
		    while(1){}			
		};
		//Nothing.
	};
	
	
	
	
	//
    // New window.
    //	
	
//CreateStruct:
	
	//Alocando memória para a estrutura da janela.
	window = (void*) malloc( sizeof(struct window_d) );	           
	if( (void*) window == NULL )
	{
        //
        // @todo: 
		// Onde o Kernel colocará essa mensagem de erro ?
		// Por enquanto no backbuffer.
        //
		
		printf("CreateWindow:\n");
		refresh_screen();	
		return NULL; //erro.
		
    }else{
        
		//
		// Obs: 
		// Conseguimos alocar memória para a estrutura da janela. Agora 
		// vamos inicializar os elementos da estrutura de acordo com os 
		// parâmetros passados via argumento.
		//
		
		//Object.
		window->objectType = ObjectTypeWindow;
		window->objectClass = ObjectClassGuiObjects;

		//Id. A janela recebe um id somente na hora de registrar.
		//window->id = ??.

	    //Name.
		window->name = windowname;
		
		//Segurança.
		window->used = 1;
		window->magic = 1234;
		
	    //Window type.	
	    window->type = (unsigned long) type;
		
		//@todo: Criar instância.
		
		//@todo: é importante definir o procedimento de janela desde já.
		//senão dá problemas quando chamá-lo e ele naõ estiver pronto.

		//Procedure support.
		//@todo: Devemos receber esses parâmetros e configurar aqui.
		//window->procedure = (unsigned long) &system_procedure;
		//window->wProcedure = NULL;  //Estrutura.
		
		//icon, cursor, cursor x, cursor y, bg etc...
		
		//Características.
		
		//Modo de exibição:
		
		//Se não estivermos no modo gráfico, não há o que pintar.
		window->view = (int) view;
		if(g_useGUI == 0){ window->view = (int) VIEW_MINIMIZED; };

        //Se não foi oferecido um modo de exibição, então temos um problema.
        //?? Talvez devamos retornar um erro. 
		//if( (int) view == VIEW_NULL ){ return NULL; };		
		
		//??Qual é o status da janela, se ela é a janela ativa ou não.
		//?? Devemos definir quais são os status possíveis da janela.
		//
		
		//active 
		if( status == WINDOW_STATUS_ACTIVE){ 
		    active_window = (int) window->id;  
            //set_active_window(window); 		
		    //window->active = WINDOW_STATUS_ACTIVE;
			//window->status = (unsigned long) WINDOW_STATUS_ACTIVE;
			window->relationship_status = (unsigned long) WINDOW_REALATIONSHIPSTATUS_FOREGROUND; 
            window->z_axis_order = 0; // ?? inicializando apenas. @todo:getNextZAxisOrder()
			//...			
		};
		
		//inactive
		if( status == WINDOW_STATUS_INACTIVE){ 
		    //window->active = WINDOW_STATUS_INACTIVE;
			//window->status = (unsigned long) WINDOW_STATUS_INACTIVE;
			window->relationship_status = (unsigned long) WINDOW_REALATIONSHIPSTATUS_BACKGROUND;
            window->z_axis_order = 0; //inicializando apenas. @todo:getNextZAxisOrder()
			//...			
		};	
		
		
		//focus	
		//window->focus = 0; //determinando que não temos o foco.

		//
		// @todo:
		// Se for uma janela filha o posicionamento deve ser somado às margens 
		// da área de cliente da janela que será a janela mãe.
		//

		//
		// #bugbug @todo 
		// Esses valores de dimensões recebidos via argumento na verdade 
		// devem ser os valores para a janela, sem contar o frame, que 
		// inclui as bordas e a barra de títulos.
		//

		//Dimensões.	
        window->width  = width;
        window->height = height;  
		
		//Margens.
		window->left   = x;    
        window->top    = y;
        window->right  = (unsigned long) window->left + window->width;
        window->bottom = (unsigned long) window->top  + window->height;       

		//Deslocamentos em relação às margens.
		// Os deslocamentos servem para inserir elementos na janela, como barras, botões e textos.
		window->x = 0;
        window->y = 0;		
		
		//saving.
		//saveLeft = window->left;
		//saveTop  = window->top;
		
		window->color_bg = (unsigned long) color; 
		
		//O retângulo da janela.
		//window->rcWindow = NULL;
		
		
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
		
		//Msg support.
		window->msg_window = (void *) window;
		window->msg = 0;
		window->long1 = 0;
		window->long2 = 0;
		
		//Offsets
		window->sendOffset = 0;
		window->receiveOffset = 0;
		
		//Filas de mensagens.
		//São dessas filas que os programas em user mode
		//são pegar as mensagens, solicitando através de system call.
		window->hwndList[0] = 0;
		window->msgList[0] = 0;
		window->long1List[0] = 0;
		window->long2List[0] = 0;
		
		//Buffers support.
		
		//Dedicated buffer: 
		//Cria um buffer dedicado de acordo com as dimensões da janela.		
		window->DedicatedBuffer = (void*) windowCreateDedicatedBuffer(window);
		
		//O backbuffer é a janela do desktop ao qual a janela pertence.
		//window->BackBuffer = (void*) windowGetBackbufferAddress(); //@todo: Criar função.
		window->BackBuffer = (void*) g_backbuffer_address;
		
		//o frontbuffer é o endereço da memória de vídeo para o monitor
		//que se deseja mostrar a janela. (LFB, cr3)
		//window->FrontBuffer = (void*) windowGetFrontbufferAddress(); //@todo: Criar função.
		window->FrontBuffer = (void*) g_frontbuffer_buffer_address;
		
	    //@todo:
	    //Se não for uma Child, deve-se resetar todas as informações relativas
	    //à parent window.
		
		//Parent support
		window->parent = (void*) Parent;
		window->parentid = (unsigned long) Parent->id;
		
		//Child window linked list.
		window->childListHead = NULL;
		
		//Client window support.
		window->client_window = NULL;  //window.
		window->rcClient = NULL;       //rect.
		
		//Desktop support.
		//window->desktop = (void*) Desktop; //configurado anteriormente.
		//window->desktop_id = Desktop->id;  //@todo: verificar elemento.
		
	    //Menu window. Qual janela o menu usará.
	    window->menu_window = NULL;    //gui->menu_window ???
		
		//Menus.
		window->sysMenu = NULL;  //gui->menu ???
		window->barMenu = NULL;  //gui->menu ???
		window->defaultMenu = NULL; //gui->menu ???
		
		//menu and button support.
		window->isMenu = 0;
		window->isButton = 0;
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
			
		//Debug:
		//printf("config1 %s %d %d %d %d \n",window->name,window->left, window->top, window->width, window->height);
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

	
	
	
	//
	// Configurando os elementos de acordo com o tipo.
	// @todo: Salvar as flags para os elementos presentes
	// na estrutura da janela.
	//
	
    switch(type)
    {
		//0) Null.
		case WT_NULL:
		    return NULL;  //Ainda não implementada.
		break;
		
		//    **** WINDOW ****
		// A window is an undecorated Frame.
		//1) Simple rect, (Sem barra de títulos).
		case WT_SIMPLE:
	        Background = 1;    //bg.
	        window->backgroundUsed = 1;
		break;

		//
		//2) Edit box, (Simples + borda preta).
		case WT_EDITBOX:
	    Shadow = 1;        //sombra.
	    Background = 1;    //bg.
		window->shadowUsed = 1;
		window->backgroundUsed = 1;	
		break;

		//   **** FRAME ****
		//3) Overlapped, (completa, para aplicativos).
		case WT_OVERLAPPED:
	    Shadow = 1;        //Sombra.
	    Background = 1;    //bg.
	    TitleBar = 1;      //Título + Borda.
		MinimizeButton = 1;  //Botão para minimizar
		CloseButton = 1;     //Botão para fechar. 
		//MenuBar       = 1;  //Barra de menu. 
	    ButtonSysMenu = 1;    //System menu button. ??
		ClientArea = 1;
		
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


        //Continua ...
		
        default:
            return NULL;  //Ainda não implementada.		
		    break;
	};	
	
	// Continua...
	
	
    //
	// Draw !
	//
	
	//
	// Hora de pintar. Os elementos serão incluídos se foram 
	// selecionados anteriormente.
	//
	
drawBegin:	

    //
	// Obs: Se for uma janela, pintaremos apenas a janela.
	//      Se for um frame, pintaremos todos os elementos
	//      presentes nesse frame de acordo com as flags.
	//

    //
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
	//
	
	//if(DedicatedBuffer == 1){};
	
	if( window->view == VIEW_NULL ){
		//@todo: temos um problema, dvemos retornar??
	    //return NULL;
	};
	
    //
	//
	//
	
	//
	// Minimized ? 
	// Se tiver minimizada, não precisa mostrar a janela, porém
	// é necessário pintar a janela no buffer dedicado.
	//
	View = 0;
	View = (int) is_window_minimized(window);
    if(View == 1)
	{
		//window->draw = 1; //Devemos pintála no buffer dedicado.
		window->show = 0;
		window->redraw = 0;
		//...
		
		//@todo: Não retornar. 
		//como teste estamos retornando.
		//goto done;
	    return (void*) window;
	};
	
	//
	// @todo: Maximized ?
	// Para maximizar devemos considerar as dimensões da área de cliente
	// da janela mãe.
	// Se a jenela estiver maximizada, então deve ter 
	// o tamanho da área do cliente, caso ela seja uma janela filha.
	// Essa área de cliente poderá ser a área de trabalho, caso a
	// janela mãe seja a janela principal.
	// 
	
	//View = 0;
	//View = (int) is_window_maximized(window);
    //if(View == 1){
	//	//...
	//}	

    //
    //  * FULL SCREEN
    //

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
	

    //
	// Color:
	// Obs: @todo: Isso foi definido acima, foi passado por argumento e
	// colocado na estrutura. Fiacrá assim somente por teste,
	// depois deletaremos essa definição aqui.
	//
	
	//*Importante: Devemos utilizar a cor que foi passada via argumento?!
	// senão todas as janelas terão a mesma cor.
	//

	
	//
	// Sombra:
	//     A sombra pertence à janela e ao frame.
	//     A sombra é maior que a própria janela.
	//     ?? Se estivermos em full screen não tem sombra ??
	//
	//
	
    //Sombra.	
	if(Shadow == 1)
	{
		//CurrentColorScheme->elements[??]
		
		//@todo: Se tiver barra de rolagem a largura da sombra deve ser maior.
		//if()
		
		//@todo: Passar a estrutura de janela.
        drawDataRectangle( window->left +1, 
		                   window->top  +1, 
						   window->width  +1 +1,   // @todo: Adicionar a largura da bordas bordas verticais e barra de rolagem se tiver.
						   window->height +1 +24 +1,   // @todo: Adicionar as larguras das bordas horizontais e da barra de títulos.
						   xCOLOR_GRAY1 );         //Cinza escuro.        
	};	
	
    
	//
	// Background:
	//    Background para todo o espaço ocupado pela janela e pelo seu frame.
	//
	
	//Background.
	if(Background == 1)
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
	if(TitleBar == 1)
	{ 
		//Focus.
		//Cores diferenste se tiver foco e se não tiver.
		if(window->id == window_with_focus)
		{
			//esquema de cor. No caso de inativa.
		    window->color_bg = CurrentColorScheme->elements[csiActiveWindowTitleBar]; 
		}else{
			//*Cor enviada por argumento.
		    window->color_bg = color;
			//window->color_bg = CurrentColorScheme->elements[csiInactiveWindowTitleBar]; 
		};
		
		//@todo: String color.
		
		//@todo: String size.
		
		//@todo: Se tiver barra de rolagem, a largura deve ser maior.
		//if()
		
		//Rectangle and string.
		
		//retângulao
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
		if(MinimizeButton == 1)
		{
			window->minimizebuttonUsed = 1;
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
	    if(CloseButton == 1)
		{
			window->closebuttonUsed = 1;
	        draw_button( window, "X", 1, 
			            (window->width -21), 4, 
						21, 21, 
						COLOR_BUTTONFACE);				
	    };					 
			
		//#bugbug O kernel não pode ficar tanto tempo assim carregando uma imagem.
		//essa coisa de pitar o ícone nesse momento até que deu certo, mas 
		//demora muito carregálo na memória, ele ja deveria estar lá
		// e nesse momento somente seria transferido par ao backbuffer.
		/*
		//icon.	
        //load bmp file.
		void *bmp_buffer = (void*)malloc(32*1024);
        fsLoadFile("BMP1    BMP", (unsigned long) bmp_buffer); 		
		//display bmp.	
		load_bitmap_16x16( (unsigned long) bmp_buffer, window->left, window->top, 0);	
		*/
		
		//...			 
	};	
	
	
    // Client Area. 
    //@todo: RESPEITAR A IMPORTÂNCIA DESSE ELEMENTO.	
	if(ClientArea == 1)
	{
		//
		// Obs: A Client Area é apenas um retângulo.
		//

		//@todo: Passar a estrutura de janela.
		
		clientRect = (void*) malloc( sizeof(struct rect_d) ); 
		if( (void*) clientRect == NULL )
		{
			//free(clientRect);
		    window->rcClient = NULL;	
		}else{
			
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
			
			window->rcClient->objectType = ObjectTypeRectangle;
			window->rcClient->objectClass = ObjectClassGuiObjects;
			
			window->rcClient->used = 1;
			window->rcClient->magic = 1234;
			
			window->rcClient->window = (void*) window; //pertence à que janela.
			
			
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
			
		    //
			// * ESSA COR FOI PASSADA VIA ARGUMENTO.
			//
			window->rcClient->color_bg = clientcolor;
			
			//@todo: isso deveria ir para a estrutura de retãngulo usada pela área de cliente.
			//Obs: não precisamos mais disso. deletar.
	        window->clientrect_color_bg = clientcolor;
			
			//window->rcClient->color_bg;  //esse é o certo
            drawDataRectangle( (unsigned long) window->rcClient->left, 
		                       (unsigned long) window->rcClient->top, 
						       (unsigned long) window->rcClient->width, 
						       (unsigned long) window->rcClient->height, 
							   (unsigned long) window->rcClient->color_bg );
						      
		
		};
		//Nothing.
	};

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
	

	
	//
	// Continua ... ( Pinta detalhes da janela, caso ouver )
	//
	
	//Barras de rolagem ...
	//efeitos ...
	//itens de menus...
	//itens de barras ...
	//carrega ícones ...
	//Continua ...
	
	
	//
	// Message: 
	// @todo: Enviar uma mensagem de CREATE pra janela.
	//        Assim o procedimento cria os elementos
	//        restantes.
	//
		
	
	
	//
	// @todo: Atualizar a linkedlist da parent window.
	//
	
	

	
	
	//
	// **** TEMOS QUE MANDAR UMA MENSAGEM DE 'MSG_CREATE' PRA JANELA,
	//      SE ELA NÃO RESPONDER CORRETAMENTE, ENTÃO TEMOS QUE APAGAR TUDO O QUE
	// INICIALIZAMOS E NOTIFICAR O ERRO E RETORNAR NULL.
	//
	
	//Ex: if( sendMessage(.,.,.,.) == 0 )
	//{
	//	//apaga tudo, notifica o erro e retorna null.
	//	return NULL;
	//}
	
	
	//
	// Nesse momento a janela já está criada, podemos configurar 
	//algumas globais importantes, como thread, desktop ...
	//
	
	//atualizar parent and child links.
	
	//@TODO: ENVIAR UMA MENSAGEM PARA A JANELA QUE RETORNARÁ 
	//O TAMANHO OFICIAL DA JANELA DO CLIENTE.(STRUCT DE RECT)
	
	
	//ENVIAMOS A MENSAGEM CREATE PRA JANELA. SEI LA, AVISANDO QUE CRIAMOS 
	//A A JANELA DO CLIENTE , ?? A JANELA DO CLIENTE É UMA JANELA NORMAL??
	//OU SÓ UM RETÂNGULO??
	
	//NOTIFICAR TODO MUNDO SOBRE O EVENTO DA CRIAÇÃO DA JANELA.
	//ALGUEM PODERIA ESTAR ESPERANDO POR ISSO...
	//DEVEMOS NOTIFICAR SOMENTE DEPOIS DE ENVIARMOS A MENSAGEM MSG_CREATE ...
	//E ANTES DE QUALQUER OPERAÇÃO DE MOVIMENTAÇÃO OU REDIMENSIONAMENTO DE JANELA ..
	//EXISTEM OBSERVADORES FAZENDO CONTAGEM DESSAS COISAS.


   //É HORA DE MINIMIZAR OU MAXIMIZAR, CONFORME FOI INDICADO POR QUEM
  // CHAMOU A FUNÇÃO PARA CRIAR A JANELA.

   //SE É UMA JANELA FILHA, DEVEMOS ENVIAR UMA MENSAGEM PRA JANELA PAI,
   //AVISANDO QUE A JANELA FILHA FOI CRIADA ... POIS ELE PODE ESTAR ESPERANDO 
   //POR ISSO. ... devemos travar a threadmae dessa janela antes de enviar a mensagem e 
   //depois destravar.

   //  
	//
	// @todo: ShowWindow.
	//

    //destravar a thread dessa janela e a thread mae antes de sair.
	
	
	//
	// zorder stuff.
	//
	
	int zIndex; 
	struct window_d *zWindow;
	
	for( zIndex = 0; zIndex < ZORDER_COUNT_MAX; zIndex++ )
	{
	    zWindow = (void*) zorderList[zIndex];
        
		//Obtendo um espaço vazio.
		//Se for NULL, então não tinha um ponteiro no slot.
		if( (void*) zWindow == NULL )
		{
			//Coloca o ponteiro da janela criada no slot vazio.
			zorderList[zIndex] = (unsigned long) window;

            //Salva o índice da ordem na estrutura da janela criada. 			
            window->z_axis_order = (int) zIndex;
			
			zorderCounter++;
			if(zorderCounter >= ZORDER_COUNT_MAX){
				printf("CreateWindow: zorderCounter\n");
				goto fail;
			}
            
			goto done; 				
		};		
		//Nothing
	};
	
//Se o for acabou sem termos conseguido um lugar vazio.	
fail:
    printf("CreateWindow: zorderList\n");
    refresh_screen();
    while(1){}	
	
// done.		
done:

    //Testando se a rotina modificou algum desses.
    //window->left =  saveLeft;
	//window->top  =  saveTop;
	
    //SetFocus(window);
	return (void*) window;
};

//
// End.
//
