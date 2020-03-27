/*
 
#importante:

>> o frame pertence à uma janela.
>> caption bar esta dentro de uma janela e chamado pela rotina de draw frame..

-----
primeiro cria-se uma janela...
depois cria-se um frame para ela,
quando for criar o frame então a rotina chama a função que cria a caption bar.

 
 */



/*
 * File: kgws/kgws/createw.c
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



int DrawIcon ( struct window_d *window, int n );
int DrawIcon ( struct window_d *window, int n )
{
    //todo: checar validades.
    
    // n = seleciona um icon de uma lista.
    // switch()
    
    bmpDisplayBMP ( appIconBuffer, 
         window->left +8, window->top +8 );
}


// #importante
// >>> Criaremos a barra de títulos depois que a janela estiver pronta.
              
int DrawTitleBar ( struct window_d *window,
                unsigned long x,
                unsigned long y,
                unsigned long width,
                unsigned long height,
                int style,
                char *string )         
{
	
	unsigned long __tmp_color;

    // podemos desenhar a string e os botões de controle.
    // Isso poderá ser chamado pelo wm.

    //todo: checar validades.

       // barra de títulos;   
       //todo: usar o esquema de cores.      
	
	 if (window->focus == 1)
	 { __tmp_color = xCOLOR_GRAY1; }        // mais escuro
	 if (window->focus == 0)
	 { __tmp_color = window->bg_color; }    // escolhida pelo aplicativo;
      
      //retângulo da barra de títulos.
     drawDataRectangle ( window->left +2, window->top +2, 
           window->width -4, 30, __tmp_color );        
        
	// String
    draw_string ( window->left +16 +8 +8, window->top +(32/3), 
        COLOR_TERMINALTEXT2, window->name );  

     return 0;
}





// #importante:
// essa rotina será chamada depois que criarmos uma janela básica
// mas só para alguns tipos de janelas
// pois nem todos os tipos precisam de um frame.
// ou ainda, cada tipo de janela tem um frame diferente ...
// por exemplo, podemos considerar que um checkbox tem um tipo de frame.
// toda janela criada pode ter um frame.
// >> durante a rotina de criação do frame para uma janela que ja existe
// podemos chamar a rotina de criação da caption bar, que vai criar os
// botões de controle ... mas nem toda janela que tem frame precisa
// de uma caption bar.

//estilo do frame.
//dependendo do estilo do frame, podemos ou nao criar a caption bar.
// por exemplo: uma editbox tem um frame mas não tem uma caption bar;


              
int DrawFrame ( struct window_d *window,
                unsigned long x,
                unsigned long y,
                unsigned long width,
                unsigned long height,
                int style )          //estilo do frame.
{

    unsigned long border_color;
    unsigned long border_size;
    unsigned long __tmp_color;  
    
    // #todo
    // desenhar o frame e depois desenhar a barra de títulos
    // caso esse estilo de frame precise de uma barra.

    //EDITBOX NÃO PRECISA DE BARRA DE TÍTULOS.
    //MAS PRECISA DE FRAME ... QUE SERÃO AS BORDAS.
		// Editbox
    if ( window->type == WT_EDITBOX )
    {
			// Se tiver o foco.
            if ( window->focus == 1 )
            {
                border_color = COLOR_BLUE;
                border_size = 2;
            }else{
                border_color = COLOR_PINK; //COLOR_INACTIVEBORDER;
                border_size = 1;
            };
            
        drawDataRectangle( window->left, 
            window->top, window->width, border_size, border_color );

        drawDataRectangle( window->left, 
            window->top, border_size, window->height, border_color );

		//board2, borda direita e baixo.
        drawDataRectangle( window->left +window->width -1, 
            window->top, border_size, window->height, border_color );

        drawDataRectangle ( window->left, window->top +window->height -1, 
            window->width, border_size, border_color );

        return 0;
    }



    if ( window->type == WT_OVERLAPPED)
    {
			// Se tiver o foco.
            if ( window->focus == 1 )
            {
                border_color = COLOR_BLUE;
                border_size = 3;
            }else{
                border_color = COLOR_INACTIVEBORDER;
                border_size = 2;
            };
            
        drawDataRectangle( window->left, 
            window->top, window->width, border_size, border_color );

        drawDataRectangle( window->left, 
            window->top, border_size, window->height, border_color );

		//board2, borda direita e baixo.
        drawDataRectangle( window->left +window->width -1, 
            window->top, border_size, window->height, border_color );

        drawDataRectangle ( window->left, window->top +window->height -1, 
            window->width, border_size, border_color );
            
       
       
       // title bar and string
       // #todo: Isso é trabalho do wm
       //DrawTitleBar ( (struct window_d *) window, 
       //     x, y,
       //     width, height, 
       //     1,
       //     (char *) window->name );  //style


        // Icon.
        // #todo: Isso é trabalho do wm
        //DrawIcon ( window, 1 );
            
        return 0;
    }


    /// QUADRADINHO PEQUENO COM BORDA GROSSA.
    if ( window->type == WT_CHECKBOX )
    {
			// Se tiver o foco.
            if ( window->focus == 1 )
            {
                border_color = xCOLOR_GRAY1;
                border_size = 8;
            }else{
                border_color = xCOLOR_GRAY2;
                border_size = 4;
            };
            
        drawDataRectangle( window->left, 
            window->top, window->width, border_size, border_color );

        drawDataRectangle( window->left, 
            window->top, border_size, window->height, border_color );

		//board2, borda direita e baixo.
        drawDataRectangle( window->left +window->width -1, 
            window->top, border_size, window->height, border_color );

        drawDataRectangle ( window->left, window->top +window->height -1, 
            window->width, border_size, border_color );

        return 0;
    }


    return 1;
}





/*
 ***************************************************************************
 * CreateWindow: 
 *     Função secundária. Cria uma janela simples. Apenas alguns tipos.
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


// # importante
// Essa rotina cria janelas simples, sem molduras, dos seguintes tipos:
// WT_SIMPLE, WT_POPUP, WT_BUTTON, WT_STATUSBAR e WT_ICON
 
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
	//int View;

	int Maximized; //??
	int Minimized; //

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
	
	
	unsigned long __tmp_color;
	
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
	
	if ( (void *) CurrentColorScheme == NULL ){
		
		panic ("CreateWindow: CurrentColorScheme");
		
	}else{
		
		if ( CurrentColorScheme->used != 1 || 
		     CurrentColorScheme->magic != 1234 )
		{
		    panic ("CreateWindow: CurrentColorScheme validation");
		}

		//Nothing.
	}


	//
	// ## New window ##
	//

//CreateStruct:

	//Alocando memória para a estrutura da janela.

	window = (void *) kmalloc ( sizeof(struct window_d) );

	if ( (void *) window == NULL )
	{
		// @todo: 
		// Onde o Kernel colocará essa mensagem de erro ?
		// Por enquanto no backbuffer.

		// Erro.
		printf ("CreateWindow: window struct \n");
		refresh_screen ();

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
		//if ( g_useGUI == 0 )
		//{ 
		 //   window->view = (int) VIEW_MINIMIZED;
            //#bugbug: Abortar.
		//};

        //Se não foi oferecido um modo de exibição, então temos um problema.
        //?? Talvez devamos retornar um erro. 
		//if( (int) view == VIEW_NULL ){ return NULL; };
		
		//??Qual é o status da janela, se ela é a janela ativa ou não.
		//?? Devemos definir quais são os status possíveis da janela.
		//
		
		//active 
		if ( status == WINDOW_STATUS_ACTIVE )
		{ 
		    active_window = (int) window->id;  
            //set_active_window(window); 
		    //window->active = WINDOW_STATUS_ACTIVE;
			//window->status = (unsigned long) WINDOW_STATUS_ACTIVE;
			window->relationship_status = (unsigned long) WINDOW_REALATIONSHIPSTATUS_FOREGROUND; 
            window->z = 0;  //z_order_get_free_slot()
			//...
		};

		//inactive
		if ( status == WINDOW_STATUS_INACTIVE )
		{ 
		    //window->active = WINDOW_STATUS_INACTIVE;
			//window->status = (unsigned long) WINDOW_STATUS_INACTIVE;
			window->relationship_status = (unsigned long) WINDOW_REALATIONSHIPSTATUS_BACKGROUND;
            window->z = 0; //z_order_get_free_slot()
			//...
		};

		// Focus = No!
		// Determinando que não temos o foco.
		window->focus = 0; 

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
		// Os deslocamentos servem para inserir elementos na janela, 
		// como barras, botões e textos.
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
		// #todo: 
		// Uma opção é inicializarmos a estrutura de ponteiro depois ...
		// pois tem janela que não tem ponteiro. 
		// JÁ QUE NO MOMENTO ESTAMOS ENFRENTANDO ALGUNS TRAVAMENTOS.
		//
		//window->cursor = (void*) kmalloc( sizeof(struct cursor_d) );

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

		//suspensa !!!

		//window->DedicatedBuffer = (void*) windowCreateDedicatedBuffer(window);
		window->DedicatedBuffer = NULL;

		// backbuffer and front buffer.
		window->BackBuffer = (void *) g_backbuffer_va;
		window->FrontBuffer = (void *) g_frontbuffer_pa;
		
		
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
		
		window->terminal_left = (unsigned long) 0;
		window->terminal_top = (unsigned long) 0;
		window->terminal_width = (unsigned long) 0;
		window->terminal_height = (unsigned long) 0;
		
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
		window->prev = (void *) Parent;
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

        case WT_NULL:
            return NULL; 
            break;


        // Simple window. (Sem barra de títulos).
        case WT_SIMPLE:
            Background = 1;
            window->backgroundUsed = 1;
            break;


		// Popup. (um tipo de overlapped mais simples).
		case WT_POPUP:
	        Shadow = 1;        
		    window->shadowUsed = 1;	        
	        Background = 1;
		    window->backgroundUsed = 1;
		    //if(titulo){} TitleBar = 1;    //titulo + borda
		    break;
 

		// Button.
        //Obs: existe uma rotina que desenha um botão.
        //quando create window for chamada para criarmos um botão 
        //podemos chamar essa rotina que desenha o botão ...
        //apenas isso.	
        //aqui nesse case podemos selecionar algumas caractrerísticas 
        //do botão que são acionadas através das características 
        //da janela.
        
        //Nothing for now ...
        //Deixaremos a rotina de desenhar o botão fazer tudo por enquanto.          
        case WT_BUTTON:
            break;


		//Status bar.
        case WT_STATUSBAR:
            Background = 1;
            window->backgroundUsed = 1;
            break;

        // Ícone da área de trabalho.
        case WT_ICON:
            Background = 1;
            window->backgroundUsed = 1;
            break;

        // Continua ...
		
		//Ainda não implementada.
        default:
            panic ("CreateWindow: default:");
		    break;
	};


	
	//
	// ==== Draw ====
	//
	
	// Hora de pintar. 
	// Os elementos serão incluídos se foram selecionados anteriormente.
	
//drawBegin:

	// Obs: 
	// Se for uma janela, pintaremos apenas a janela.
	// Se for um frame, pintaremos todos os elementos
	// presentes nesse frame de acordo com as flags.
	// Obs:
	// A janela precisa ser pintada em seu buffer dedicado.
	// Nesse momento o buffer dedicado da janela já está na estutura
	// da janela. Rotinas de pintura que tenham acesso à estrutura da
	// janela devem utilizar o buffer dedicado que for indicado na estrutura.
	// Para que seja possível pintar uma janela em seu buffer dedicado,
	// devemos passar um ponteiro para a estrutura da janela em todas
	// as rotinas de pintura chamadas daqui pra baixo.
	// #todo: 
	// Passar estrutura de janela via argumento, para a rotina
	// de pintura ter acesso ao buffer dedicado.


	//if(DedicatedBuffer == 1){};


	// Se o view for igual NULL talvez signifique não pintar.
    if ( window->view == VIEW_NULL )
    {
		//#bugbug: fail.
		//window->show = 0;
		//window->redraw = 0;
		//return (void*) window;
    }


	// Minimized ? (Hide ?)
	// Se tiver minimizada, não precisa mostrar a janela, porém
	// é necessário pintar a janela no buffer dedicado, se essa técnica 
	// estiver disponível.
	// Talvez antes de retornarmos nesse caso seja necessário configurar 
	// mais elementos da estrutura.
	
	//#bugbug
	//se estamos contruindo a janela, então ela não foi registrada 
	//não podemos checar as coisas na estrutura ainda,
	//mas a estrutura ja existe a algumas coisas foram inicializadas.
	
	// #importante
	// Pois retornaremos no caso de janelas minimizadas.
	// Provavelmente isso foi usado quando criamos janelas 
	// de referência na inicialização da GUI.(root)

    Minimized = 0;
    Minimized = (int) is_window_minimized (window);

    if ( Minimized == 1 )
    {
		//window->draw = 1; //Devemos pintála no buffer dedicado.
		window->show = 0;
		window->redraw = 0;
		//...
		
		//@todo: Não retornar. 
		//como teste estamos retornando.
		
		goto done;
	    //return (void *) window;
    }



	// #todo: 
	// Maximized ?
	// Para maximizar devemos considerar as dimensões da área de cliente
	// da janela mãe.
	// Se a jenela estiver maximizada, então deve ter o tamanho da área de 
	// cliente da janela main.
	// Essa área de cliente poderá ser a área de trabalho, caso a
	// janela mãe seja a janela principal.
	// Obs: se estiver maximizada, devemos usar as dimensão e coordenadas 
	// da janela gui->main.
	
	// #bugbug
	// Temos um problema com essa limitação.
	// Não conseguimos pintar janelas simples além do height da janela gui->main
	// para janelas overlapped funciona.
	
	
    Maximized = 0;
    Maximized = (int) is_window_maximized (window);

    if ( Maximized == 1 )
    {
		//#debug
		printf("file: createw.c: #debug\n");
		printf ("original: l=%d t=%d w=%d h=%d \n", 
		    window->left, gui->main->top, 
		    window->width, window->height );
		
		//Margens da janela gui->main
        window->left = gui->main->left;    
        window->top  = gui->main->top;

		//Dimensões da janela gui->main.
        window->width  = gui->main->width;
        window->height = gui->main->height; 
        
        window->right = (unsigned long) window->left + window->width;
        window->bottom = (unsigned long) window->top  + window->height;       

		// ??
		// Deslocamentos em relação às margens.
		// Os deslocamentos servem para inserir elementos na janela, 
		// como barras, botões e textos.
		window->x = 0;
        window->y = 0;
		
		//#debug
		printf ("corrigido: l=%d t=%d w=%d h=%d \n", 
		    window->left, gui->main->top, 
		    window->width, window->height );
		
		//#debug
		refresh_screen ();
		while (1){}
	}


	//
	// == ## draw ## ===========================
	//

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


	//  ## Shadow ##
	//
	// Sombra:
	//     A sombra pertence à janela e ao frame.
	//     A sombra é maior que a própria janela.
	//     ?? Se estivermos em full screen não tem sombra ??

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
		


	    if (window->focus == 1)
	    { __tmp_color = xCOLOR_GRAY1; }    //mais escuro
		if (window->focus == 0)
		{ __tmp_color = xCOLOR_GRAY2; }    //mais claro
			
		drawDataRectangle ( window->left +1, window->top +1, 
		    window->width +1 +1, window->height +1 +1, 
			__tmp_color );             


        // ??
		// E os outros tipos, não tem sombra ??
		// Os outros tipos devem ter escolha para sombra ou não ??
		// Flat design pode usar sombra para definir se o botão 
		// foi pressionado ou não.
		
		//...
    }



	// ## Background ##
	// Background para todo o espaço ocupado pela janela e pelo seu frame.
    // O posicionamento do background depende do tipo de janela.
    // Um controlador ou um editbox deve ter um posicionamento relativo
    // à sua janela mãe. Já uma overlapped pode ser relativo a janela 
    // gui->main ou relativo à janela mãe.

    if ( Background == 1 )
    {
		// Flag.
        window->backgroundUsed = 1;

        window->bg_color = CurrentColorScheme->elements[csiWindowBackground]; 

		// O argumento 'color' será a cor do bg para alguns tipos.
		// Talvez não deva ser assim. Talvez tenha que se respeitar o tema instalado.
        if ( (unsigned long) type == WT_SIMPLE ){ window->bg_color = color; }
        if ( (unsigned long) type == WT_POPUP ){ window->bg_color = color; }
        if ( (unsigned long) type == WT_EDITBOX){ window->bg_color = color; }
        if ( (unsigned long) type == WT_CHECKBOX){ window->bg_color = color; }
        //if ( (unsigned long) type == WT_SCROLLBAR){ window->bg_color = color; }
        if ( (unsigned long) type == WT_ICON ){ window->bg_color = color; }
        //...

		// Pintar o retângulo.
		// #todo: 
		// ?? width Adicionar a largura da bordas bordas verticais.
		// #todo: 
		// ?? height Adicionar as larguras das bordas horizontais e da barra de títulos.

        if ( (unsigned long) type == WT_STATUSBAR )
        {
            drawDataRectangle ( window->left, window->top, 
                window->width -1, window->height, window->bg_color ); 

            draw_string ( window->left +8, window->top +8, 
                COLOR_TEXT, window->name ); 
            goto done;
        }

        // 
        // * Draw!
        //
         
        drawDataRectangle ( window->left, window->top, 
            window->width, window->height, window->bg_color );

        //?? More ...
    }





    // # Client Area #
    // #importante
    // #todo: 
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

		clientRect = (void *) kmalloc ( sizeof(struct rect_d) ); 
		
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
			window->rcClient = (void *) clientRect;
			
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

            drawDataRectangle ( (unsigned long) window->rcClient->left, 
                (unsigned long) window->rcClient->top, 
                (unsigned long) window->rcClient->width, 
                (unsigned long) window->rcClient->height, 
                (unsigned long) window->rcClient->bg_color );

            // Done.
		};
		//Nothing.
	}




    // # Status bar #
    if ( (unsigned long) type == WT_STATUSBAR )
    {
        //#test
        window->parent = Parent;
    }



	//
	//  ## Create button ##
	//
	
	// #BUGBUG: 
	// JANELA DO TIPO BOTÃO.
    // NÃO TEMOS INFORMAÇÕES SOBRE O TIPO DE BOTÃO QUE DEVEMOS CRIAR. 
    // SÓ SABEMOS QUE A JANELA É DO TIPO BOTÃO.
	// As posições de left e right são da janela do botão.
    // #obs: 
    // Essa função retorna uma estrutura de botão.
    // Então, uma janela, quando acianoada sua flag que indica que ela é um botão,
    // podemos usar a estrutura de botão para acessar as características do botão.
	// #obs
	// As cores das bordas dependem do status.
	
	// #obs:
	// Aqui o botão sempre é desenhado no mesmo estado.
	
	// #bugbug
	// Se o tipo é um botao então o posicionamento é relativo.
	// tentaremos transformalo em absoludo, somando ao deslocamento da
	// janela mãe. Isso depois de pintarmos.
	// #bugbug: provavelmente isso dará problemas na hora de repintar,
	//tentaremos corrigir depois.

    if ( (unsigned long) type == WT_BUTTON )
    {
		// window->button aqui fica a estrutura de botão
		// caso a janela for um botão.
        window->button = (struct button_d *) draw_button ( windowname, 
                                                 0, BS_DEFAULT, 0,
                                                 window->left, window->top, 
                                                 window->width, window->height, 
                                                 window->bg_color );
        
        //para repintar precisamos olhar na estrutura de botão
        //e encontrarmos a janela.
        window->button->window = window;
        
        // #bugbug
        // E se retornar NULL ?
        //if ( (void *) window->button == NULL ){} 
        
        //#test
        window->parent = Parent;
        window->isButton = 1;
    }





    // #simple #
    if ( (unsigned long) type == WT_SIMPLE )
    {
       //#test
        window->parent = Parent;
    }


	//
	// Continua ... 
	// ( Pinta detalhes da janela, caso ouver )
	//
	
	//Barras de rolagem ...
	//efeitos ...
	//itens de menus...
	//itens de barras ...
	//carrega ícones ...
	//Continua ...
	
	
	// Message: 
	// #todo: 
	// Enviar uma mensagem de CREATE pra janela.
	// Assim o procedimento cria os elementos restantes.
	
	// #todo: 
	// Atualizar a linkedlist da parent window.
	
	

    // Icon.
    if (window->type == WT_ICON)
    {
        bmpDisplayBMP ( appIconBuffer, 
            window->left +8, window->top +8 );
            
        draw_string ( window->left +8, window->top +16 +8 +8, 
            COLOR_TERMINALTEXT2, window->name );  
    }


done:
    return (void *) window;
}



/*
 ***************************** 
 * kgws_create_window:
 *     
 *     Create a window.
 * 
 */
 
// # importante 
// Essa será a função que atenderá a interrupção.
// Esse é o serviço de criação da janela.
// Talvez ampliaremos o número de argumentos.
    
//1. Começamos criando uma janela simples
//2. depois criamos o frame, que decide se vai ter barra 
//   de títulos ou nao.
                  
void *kgws_create_window ( unsigned long type, 
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

    struct window_d *__w;

    
    // No caso dos tipos com moldura então criaremos em duas etapas.
    // no futuro todas serão criadas em duas etapas e 
    // CreateWindow será mais imples.
    
    if ( type == WT_OVERLAPPED )
    {

       // # importante
       // Essa rotina cria janelas simples, sem molduras, dos seguintes tipos:
       // WT_SIMPLE, WT_POPUP, WT_BUTTON, WT_STATUSBAR e WT_ICON

        __w = (void *) CreateWindow ( WT_SIMPLE, status, view, 
                           (char *) windowname, 
                           x, y, width, height, 
                           (struct window_d *) pWindow, 
                           desktopid, 
                           clientcolor, color );      
    
    
        //pintamos simples, mas a tipagem será  overlapped
        __w->type = WT_OVERLAPPED;   
       goto draw_frame;
    }


    if ( type == WT_EDITBOX )
    {

       // # importante
       // Essa rotina cria janelas simples, sem molduras, dos seguintes tipos:
       // WT_SIMPLE, WT_POPUP, WT_BUTTON, WT_STATUSBAR e WT_ICON

		// Podemos usar o esquema padrão de cores ...
        __w = (void *) CreateWindow ( WT_SIMPLE, status, view, 
                           (char *) windowname, 
                           x, y, width, height, 
                           (struct window_d *) pWindow, 
                           desktopid, 
                           clientcolor, color );      
    
        //pintamos simples, mas a tipagem será  overlapped
        __w->type = WT_EDITBOX;   
        goto draw_frame;
    }

    if ( type == WT_CHECKBOX )
    {
       // # importante
       // Essa rotina cria janelas simples, sem molduras, dos seguintes tipos:
       // WT_SIMPLE, WT_POPUP, WT_BUTTON, WT_STATUSBAR e WT_ICON

		// Podemos usar o esquema padrão de cores ...
        __w = (void *) CreateWindow ( WT_SIMPLE, status, view, 
                           (char *) windowname, 
                           x, y, width, height, 
                           (struct window_d *) pWindow, 
                           desktopid, 
                           clientcolor, color );      
    
        //pintamos simples, mas a tipagem será  overlapped
        __w->type = WT_CHECKBOX;   
        goto draw_frame;
    }


    //================
    
    
    // OS TIPOS ABAIXO NÃO PRECISAM DE FRAME.
    // PODERIAMOS DEIXAR ESSA ROTINA LÁ EM CIMA COM UM IF PARA SEUS TIPOS.
       // # importante
       // Essa rotina cria janelas simples, sem molduras, dos seguintes tipos:
       // WT_SIMPLE, WT_POPUP, WT_BUTTON, WT_STATUSBAR e WT_ICON
   
    __w = (void *) CreateWindow ( type, status, view, 
                       (char *) windowname, 
                        x, y, width, height, 
                        (struct window_d *) pWindow, 
                        desktopid, 
                        clientcolor, color );      
    
    
    goto done;





draw_frame:

    //#IMPORTANTE
    //DESENHA O FRAME DOS TIPOS QUE PRECISAM DE FRAME.
    //OVERLAPED, EDITBOX, CHECKBOX ...

    if ( type == WT_OVERLAPPED || type == WT_EDITBOX || type == WT_CHECKBOX )
    {
        if (type == WT_EDITBOX)
        { __w->isEditBox = 1; }

        if (type == WT_CHECKBOX)
        { __w->isCheckBox = 1; }

        // draw frame.
        // Nessa hora essa rotina podera criar a barra de títulos.
        // o wm poderá chamar a rotina de criar frame.
        
        DrawFrame ( (struct window_d *) __w, 
            x, y,
            width, height, 
            1 );  //style
            
        goto done;
   }
    
  
    
    // =====
    
done:

    //
    // Thread.
    //

	// Associando a janela criada a trhead atual, 
	// que chamou essa rotina. O problema é na hora da inicialização.
    // #importante: Quando criarmos uma janela do tipo controle
    // uma thread será associada à ela. Então o window manager
    // poderá mandar mensagem para o procedimento de janela
    // do aplicativo avisando dos efeitos dobre o controle.

    __w->control = (struct thread_d *) threadList[current_thread];

        if ( (void *) __w->control != NULL )
        {
            if ( __w->used != 1 || __w->magic != 1234 ){
                __w->control = NULL;
            }
        }


    //
    // MSG_CREATE
    //
        
    // #test
    // O procedimento de janelas do aplicativo receberá essa mensagem
    // quando criar uma overlapped, pedindo pra ele terminar de criar
    // as janelas filhas da overlapped.
 
    if (__w->type == WT_OVERLAPPED)
    {
		if ( (void *) __w->control != NULL )
        {
			if ( __w->used == 1 || __w->magic == 1234 )
			{

                // New way. Use this one!
                __w->control->window_list[ __w->control->tail_pos ] = __w;
                   __w->control->msg_list[ __w->control->tail_pos ] = MSG_CREATE;
                 __w->control->long1_list[ __w->control->tail_pos ] = 0;
                 __w->control->long2_list[ __w->control->tail_pos ] = 0;
                __w->control->tail_pos++;
                if ( __w->control->tail_pos >= 31 )
                    __w->control->tail_pos = 0;


				//Old way. Delete it!
			    // mandamos a mensagem
			    // o aplicativo decide o que fazer com ela.
			    //__w->control->window = __w;
			    //__w->control->msg = MSG_CREATE;
			    //__w->control->long1 = 0;
			    //__w->control->long2 = 0;
			    //__w->control->newmessageFlag = 1;
			}
		}        
    };
    
    //
    // z order support.
    //
    
    int z;
    z = (int) z_order_get_free_slot();
    
    if ( z >= 0 && z < KGWS_ZORDER_MAX )
    {
        __w->z = z;
        Windows[z] = (unsigned long) __w;
    }else{
        panic ("kgws_create_window: No free slot on zorder.\n");
    };


    return (void *) __w;
}



//
// End.
//
