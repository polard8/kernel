/*
 * File: createw.c 
 * 
 *      Creates a window.
 *      It's part of the gws project.
 * 
 * History:
 *     2019 - Created fy Fred Nora.
 */


// todo
// Quando estivermos contrindo as molduras das janelas,
// as rotinas devem retornar suas alturas, para assim
// o posicionamento do 'top' da área de cliente possa ser
// atualizado. (rect)
// Lembrando que possivelmente o window manager fará esse trabalho
// sobrando para o qindo server apenas rotinas de baixo nível.
// ~> mas o sistema tem que funcionar somente com o window server.

// wm: ~> o ws oferecerá rotinas de redimencionamento e 
// reposicionamento de janelas. Essas rotinas serão a base 
// do window manager.


#include <api.h>
#include <gws.h>


/*
 *****************************
 * createwDrawTitleBar:
 * 
 * 
 */

// #importante
// Criaremos a barra de títulos depois que a janela estiver pronta.
// Desenhar a barra de titulos faz parte da criação do frame.
  
int 
createwDrawTitleBar ( 
    struct gws_window_d *window,
    unsigned long x,
    unsigned long y,
    unsigned long width,
    unsigned long height,
    int style,
    char *string )         
{

    unsigned long __tmp_color;

    // Podemos desenhar a string e os botões de controle.
    // Isso poderá ser chamado pelo wm.

    //todo: checar validades.

    // barra de títulos;   
    //todo: usar o esquema de cores.      

    // mais escuro
    if (window->focus == 1)
    { __tmp_color = xCOLOR_GRAY1; }  


    // escolhida pelo aplicativo;
    if (window->focus == 0)
    { __tmp_color = xCOLOR_GRAY5; }    
    //{ __tmp_color = window->bg_color; }     
 
    // Retângulo da barra de títulos.
    // #todo: Posicionar direito. 
    // Queremos que as bordas fiquem evidentes.
    rectBackbufferDrawRectangle ( window->left +3, window->top +3, 
        window->width -5, 30, __tmp_color );        
 
	// String
    dtextDrawString ( 
        window->left +16 +8 +8, 
        window->top +(32/3), 
        COLOR_TERMINALTEXT2, 
        window->name );  


    // #test:
    // Draw button.
    // #todo: registra isso na estrutura da janela.
    // #bugbug: Tem que pintar usando posicionamento relativo. 
    // #todo: mudar a função gws_draw_button e incluir o argumento
    // ponteiro de estrutura de janela.
    
    //gws_draw_button ("X", 1,1,1, 
    //    window->left + window->width -32, window->top +4, 
    //    28, 28, 
    //    xCOLOR_GRAY3 );//GWS_COLOR_BUTTONFACE3 );
    
    /*
    struct gws_window_d *__mybutton;

    __mybutton = (struct gws_window_d *) createwCreateWindow ( WT_BUTTON, 
                                              1, 1, "x",  
                                              window->width -32, +4, 
                                              28, 28,   
                                              window, 0, 
                                              COLOR_PINK, xCOLOR_GRAY3 ); 

    if ( (void *) __mybutton == NULL ){
       gde_debug_print ("createwDrawTitleBar: __mybutton fail\n");
       //return -1;
    }
    */
 

    return 0;
}




/*
 ********************************
 * createwDrawFrame:
 * 
 */

// #importante:
// Essa rotina será chamada depois que criarmos uma janela básica,
// mas só para alguns tipos de janelas, pois nem todos os tipos 
// precisam de um frame. Ou ainda, cada tipo de janela tem um 
// frame diferente. Por exemplo: Podemos considerar que um checkbox 
// tem um tipo de frame.
// Toda janela criada pode ter um frame.
// Durante a rotina de criação do frame para uma janela que ja existe
// podemos chamar a rotina de criação da caption bar, que vai criar os
// botões de controle ... mas nem toda janela que tem frame precisa
// de uma caption bar (Title bar).
// Estilo do frame:
// Dependendo do estilo do frame, podemos ou nao criar a caption bar.
// Por exemplo: Uma editbox tem um frame mas não tem uma caption bar.

// IN:
// style = Estilo do frame.


int 
createwDrawFrame ( 
    struct gws_window_d *parent,
    struct gws_window_d *window,
    unsigned long x,
    unsigned long y,
    unsigned long width,
    unsigned long height,
    int style ) 
{

    unsigned long border_color=0;
    unsigned long border_size=0;
    
    
    struct gws_window_d *__mybutton;
    
    // #todo
    // Desenhar o frame e depois desenhar a barra de títulos
    // caso esse estilo de frame precise de uma barra.

    // Editbox
    // EDITBOX NÃO PRECISA DE BARRA DE TÍTULOS.
    // MAS PRECISA DE FRAME ... QUE SERÃO AS BORDAS.
    
    if ( window->type == WT_EDITBOX )
    {
            // Se tiver o foco.
            if ( window->focus == 1 )
            {
                border_color = COLOR_BLUE;
                border_size = 2;
            }else{
                border_color = COLOR_PINK;  // COLOR_INACTIVEBORDER;
                border_size = 1;
            };
        
        // board1, borda de cima e esquerda.
        rectBackbufferDrawRectangle( 
            (parent->left  + window->left), 
            (parent->top   + window->top), 
            window->width, 
            border_size, border_color );

        rectBackbufferDrawRectangle( 
            (parent->left +window->left), 
            (parent->top  +window->top), 
            border_size, window->height, border_color );

        // board2, borda direita e baixo.
        rectBackbufferDrawRectangle( 
            (parent->left + window->left + window->width -1), 
            (parent->top + window->top), 
            border_size, window->height, border_color );

        rectBackbufferDrawRectangle ( 
            (parent->left + window->left), 
            parent->top + window->top + window->height -1, 
            window->width, border_size, border_color );

        return 0;
    }

    // Overlapped.
    // Janela de aplicativos.

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
            
        // Quatro bordas.
         
        // board1, borda de cima e esquerda.
        rectBackbufferDrawRectangle( 
            parent->left + window->left, 
            parent->top + window->top, 
            window->width, 
            border_size, border_color );

        rectBackbufferDrawRectangle( 
            parent->left + window->left, 
            parent->top + window->top, 
            border_size, window->height, border_color );

        //board2, borda direita e baixo.
        rectBackbufferDrawRectangle( 
            parent->left + window->left + window->width -1, 
            parent->top + window->top, 
            border_size, window->height, border_color );

        rectBackbufferDrawRectangle ( 
            parent->left + window->left, 
            parent->top + window->top + window->height -1, 
            window->width, border_size, border_color );

        // Atenção:
        // No more Title bar!
        // No more button in the title bar.

        return 0;
    }


    //button
    if ( window->type == WT_BUTTON )
    {
        gde_debug_print ("[DEBUG]: desenha o frame do botao\n");
        
        //todo frame or not
        //just like the edit box.        
        return 0;
    }

    return 1;
}




/*
 ***************************************************************************
 * createwCreateWindow2: 
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


void *createwCreateWindow2 ( 
    unsigned long type, 
    unsigned long status, 
    unsigned long view, 
    char *windowname, 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height, 
    struct gws_window_d *pWindow, 
    int desktopid, 
    unsigned long clientcolor, 
    unsigned long color ) 
{

	// @todo: O argumento style está faltando.
	//        cada tipo de tanela poderá ter vários estilos.
	// Obs: Podemos ir usando apenas um estilo padrão por enquanto.
	
	// (min, max ...).
	//int View;

    int Maximized;  //??
    int Minimized;  //

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
    struct gws_window_d *windowButton1;  // minimize
    struct gws_window_d *windowButton2;  // maximize
    struct gws_window_d *windowButton3;  // close

    // botões na barra de rolagem.
    struct gws_window_d *windowButton4;
    struct gws_window_d *windowButton5;
    struct gws_window_d *windowButton6;

    // Structs.
    struct gws_window_d *window;
    struct gws_window_d *Parent;

	//struct desktop_d *Desktop;  //suspenso.
	
    struct gws_rect_d *clientRect;  //rect

	
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
	
	/*
	if ( (void *) pWindow == NULL ){
		
		Parent = (void *) gui->screen;

	} else {

		Parent = (void *) pWindow;
	};
    */
    
    //provisório
    Parent = (void *) pWindow;
	
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

	/*
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
    */


	//
	// ## New window ##
	//

//CreateStruct:

	//Alocando memória para a estrutura da janela.

    window = (void *) malloc( sizeof(struct window_d) );

    if ( (void *) window == NULL )
    {
        // #todo: 
        // Onde o Kernel colocará essa mensagem de erro ?
        // Por enquanto no backbuffer.

        // Erro.
        debug_print ("createwCreateWindow2: window struct \n");
        printf ("createwCreateWindow2: window struct \n");
        gde_show_backbuffer ();
    
       // Using the kgws. The window server inside the kernel.
       gde_message_box ( 3,
           "createwCreateWindow2:",
           "window struct fail!" );
       while(1){}
 
       //return NULL; 

    }else{

		// Obs: 
		// Conseguimos alocar memória para a estrutura da janela. 
		// Agora vamos inicializar os elementos da estrutura de acordo 
		// com os parâmetros passados via argumento.

		// Object support.
		//window->objectType = ObjectTypeWindow;
		//window->objectClass = ObjectClassGuiObjects;

		// #importante
		// Id. A janela recebe um id somente na hora de registrar.
		// window->id = ??.

        window->name = windowname;
        window->used = 1;
        window->magic = 1234;

		// Window type.
		// Tipo é unsigned long pois poderá ser um conjunto de flags.
        window->type = (unsigned long) type;
        
        
        //#test
        window->parent = Parent;

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

        // Active 
        if ( status == WINDOW_STATUS_ACTIVE )
        { 
            active_window = (int) window->id;  
            //set_active_window(window); 
            //window->active = WINDOW_STATUS_ACTIVE;
            //window->status = (unsigned long) WINDOW_STATUS_ACTIVE;
            window->relationship_status = (unsigned long) WINDOW_REALATIONSHIPSTATUS_FOREGROUND; 
            
            //#todo
            //window->z = 0;  //z_order_get_free_slot()
            //...
        }

        // Inactive
        if ( status == WINDOW_STATUS_INACTIVE )
        { 
            //window->active = WINDOW_STATUS_INACTIVE;
            //window->status = (unsigned long) WINDOW_STATUS_INACTIVE;
            window->relationship_status = (unsigned long) WINDOW_REALATIONSHIPSTATUS_BACKGROUND;
            
            //todo
            //window->z = 0; //z_order_get_free_slot()
            //...
        }

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
        window->width  = width;
        window->height = height;  

        // Margens.
        window->left = x;    
        window->top  = y;
        window->right  = (unsigned long) ( window->left + window->width );
        window->bottom = (unsigned long) ( window->top  + window->height ); 

		// Deslocamentos em relação às margens.
		// Os deslocamentos servem para inserir elementos na janela, 
		// como barras, botões e textos.

        window->x = 0;
        window->y = 0;

		// ?? saving.
		//saveLeft = window->left;
		//saveTop  = window->top;

		// Color
		// Background support.
		window->bg_color = (unsigned long) color; 
		window->clientrect_bg_color = (unsigned long) clientcolor;
		
		// ??
		// O retângulo da janela.
		//window->rcWindow = NULL;
		

		// Cursor support
        window->CursorX = 0;
        window->CursorY = 0;
        window->CursorColor = COLOR_WINDOWTEXT; 
		//@todo: As outras características do cursor.
		//Características.
		
		//Estrutura para cursor.
		//todo
		//window->cursor = NULL;
		
		// #todo: 
		// Uma opção é inicializarmos a estrutura de ponteiro depois ...
		// pois tem janela que não tem ponteiro. 
		// JÁ QUE NO MOMENTO ESTAMOS ENFRENTANDO ALGUNS TRAVAMENTOS.
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
		window->hwndList[0]  = 0;
		window->msgList[0]   = 0;
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
		//window->BackBuffer = (void *) g_backbuffer_va;
		//window->FrontBuffer = (void *) g_frontbuffer_pa;
		
		
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
		window->terminal_used  = (int) 0;
		window->terminal_magic = (int) 0;
		window->terminal_tab   = (int) 0;
		
		//window->terminal_left = (unsigned long) 0;
		//window->terminal_top = (unsigned long) 0;
		//window->terminal_width = (unsigned long) 0;
		//window->terminal_height = (unsigned long) 0;
		
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
	    
		//window->desktop = NULL; //@todo: Definir à qual desktop a janela perence.
		//window->process = NULL; //@todo: Definir à qual processo a janela perence.
		
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
        //case WT_NULL:
            //return NULL; 
            //break;

        // Simple window. (Sem barra de títulos).
        case WT_SIMPLE:
            Background = 1;
            window->backgroundUsed = 1;
            break;


        // Edit box. (Simples + borda preta).
        // Editbox não tem sombra, tem bordas. 
        case WT_EDITBOX:
            Background = 1;
            window->backgroundUsed = 1;
            Border = 1;
            //window->borderUsed = 1;
            break;


		// Overlapped. (completa, para aplicativos).
		// Sombra, bg, título + borda, cliente area ...
		// #obs: Teremos recursividade para desenhar outras partes.
        case WT_OVERLAPPED:
            Shadow = 1;
            window->shadowUsed = 1;
            Background = 1;
            window->backgroundUsed = 1;
            TitleBar = 1;
            window->titlebarUsed = 1;
            ClientArea = 1;
            window->clientAreaUsed = 1;

            MinimizeButton = 1;   
            MaximizeButton = 1;   
            CloseButton = 1;       

            //MenuBar       = 1;    // Barra de menu. 
            //ButtonSysMenu = 1;    // System menu button. ??

		    //set_active_window(window);
		    break;


		// Popup. (um tipo de overlapped mais simples).
        case WT_POPUP:
            Shadow = 1; 
            window->shadowUsed = 1;
            Background = 1;
            window->backgroundUsed = 1;
            //if(titulo){} TitleBar = 1;    //titulo + borda
            break;
 
 
        // Check box. (Simples + borda preta).
        // Caixa de seleção. Caixa de verificação. Quadradinho.
        case WT_CHECKBOX:
            Background = 1;    
            window->backgroundUsed = 1;
            Border = 1;
 			//window->borderUsed = 1;@todo: isso ainda não existe na extrutura ??
            break;
			
		// Scroll bar. Para ser usada como janela filha.
		case WT_SCROLLBAR:
			//Background = 1;    //bg.
		    //window->backgroundUsed = 1;
            //bordas.
            //Border = 1;
 			//window->borderUsed = 1;@todo: isso ainda não existe na extrutura ??
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
            Background = 1;
            window->backgroundUsed = 1;
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

		//barra de rolagem
		//botões de radio .. 
		//...

        // Continua ...

        //Ainda não implementada.
        default:
            //return NULL; 
            gde_message_box (3,"createwCreateWindow2","default");
            debug_print("createwCreateWindow2: default\n");
            while(1){}
            break;
    };



    //gde_message_box (3,"xxx","xxxx");
    //while(1){}



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

    /*
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
     */


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
	
	/*
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
    */

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
			if (window->focus == 1)
			{ __tmp_color = xCOLOR_GRAY1; }    //mais escuro
			if (window->focus == 0)
			{ __tmp_color = xCOLOR_GRAY2; }    //mais claro

            
            //ok funciona
            //rectBackbufferDrawRectangle ( window->left +1, window->top +1, 
            //    window->width +1 +1, window->height +1 +1, 
            //    __tmp_color ); 
            
            //test
            //remeber: the first window do not have a parent.
            if ( (void*) Parent == NULL )
            { 
                gde_debug_print ("createwCreateWindow2: [Shadow] Parent"); 
                //exit(1); 
                rectBackbufferDrawRectangle ( 
                    (window->left +1), 
                    (window->top +1), 
                    (window->width +1 +1), 
                    (window->height +1 +1), 
                    __tmp_color ); 
            }
            
            if ( (void*) Parent != NULL ){
                rectBackbufferDrawRectangle ( 
                    (Parent->left   + window->left +1), 
                    (Parent->top    + window->top +1), 
                    (window->width +1 +1), 
                    (window->height +1 +1), 
                    __tmp_color ); 
            }

        }

        // ??
        // E os outros tipos, não tem sombra ??
        // Os outros tipos devem ter escolha para sombra ou não ??
        // Flat design pode usar sombra para definir se o botão 
        // foi pressionado ou não.

       // ...
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

        window->bg_color = COLOR_PINK;
        //window->bg_color = CurrentColorScheme->elements[csiWindowBackground]; 

        // O argumento 'color' será a cor do bg para alguns tipos.
        // Talvez não deva ser assim. Talvez tenha que se respeitar o tema instalado.
        if ( (unsigned long) type == WT_SIMPLE ) { window->bg_color = color; }
        if ( (unsigned long) type == WT_POPUP )  { window->bg_color = color; }
        if ( (unsigned long) type == WT_EDITBOX) { window->bg_color = color; }
        if ( (unsigned long) type == WT_CHECKBOX){ window->bg_color = color; }
        //if ( (unsigned long) type == WT_SCROLLBAR){ window->bg_color = color; }
        if ( (unsigned long) type == WT_ICON )   { window->bg_color = color; }
        if ( (unsigned long) type == WT_BUTTON ) { window->bg_color = color; }
        // ...

		// Pintar o retângulo.
		// #todo: 
		// ?? width Adicionar a largura da bordas bordas verticais.
		// #todo: 
		// ?? height Adicionar as larguras das bordas horizontais e da barra de títulos.

        /*
        if ( (unsigned long) type == WT_STATUSBAR )
        {
            drawDataRectangle ( window->left, window->top, 
                window->width -1, window->height, window->bg_color ); 

            dtextDrawString ( window->left +8, window->top +8, 
                COLOR_TEXT, window->name ); 
            goto done;
        }
        */

        // 
        // Draw background!
        //

        //#bugbug
        //Remember: The first window do not have a parent.
        if ( (void*) Parent == NULL ){ 
            gde_debug_print ("createwCreateWindow2: [Background] Parent\n"); 
            //exit(1); 
            rectBackbufferDrawRectangle ( 
                window->left, 
                window->top, 
                window->width, 
                window->height, 
                window->bg_color );
        }  
        
        if ( (void*) Parent != NULL ){
            rectBackbufferDrawRectangle ( 
                (Parent->left   + window->left), 
                (Parent->top    + window->top), 
                (window->width), 
                (window->height), 
                window->bg_color );
        }
        //?? More ...
    }

    //Termina de desenhar o botão, mas não é frame
    //é só o botão...
    //caso o botão tenha algum frame, será alguma borda extra.
    int Focus;    //(precisa de borda)
    int Selected;
    unsigned long border1;
    unsigned long border2;

    if ( (unsigned long) type == WT_BUTTON )
    {

        //border color
        //o conceito de status e state
        //está meio misturado. ja que estamos usando
        //a função de criar janela para criar botão.
        //#bugbug
        switch( status )
        {
            case BS_FOCUS:
                border1 = COLOR_BLUE;
                border2 = COLOR_BLUE;
                break;

            case BS_PRESS:
                Selected = 1;
                border1 = GWS_COLOR_BUTTONHIGHLIGHT3;
                border2 = GWS_COLOR_BUTTONSHADOW3;
                break;

            case BS_HOVER:
                break;
                    
            case BS_DISABLED:
                border1 = COLOR_GRAY;
                border2 = COLOR_GRAY;
                break;

            case BS_PROGRESS:
                break;

            case BS_DEFAULT:
            default: 
                Selected = 0;
                border1 = GWS_COLOR_BUTTONHIGHLIGHT3;
                border2 = GWS_COLOR_BUTTONSHADOW3;
                break;
        };


        size_t tmp_size = (size_t) strlen ( (const char *) windowname );
        unsigned long offset = 
        ( ( (unsigned long) window->width - ( (unsigned long) tmp_size * (unsigned long) gcharWidth) ) / 2 );
       

        if ( (void*) Parent == NULL )
        {
            gde_debug_print ("createwCreateWindow2: [WT_BUTTON] Parent NULL\n"); 
        }
        
        if ( (void*) Parent != NULL )
        {

            //board1, borda de cima e esquerda.
            rectBackbufferDrawRectangle ( 
                (Parent->left   + window->left), 
                (Parent->top    + window->top), 
                (window->width), 
                1, 
                border1 );
                
            rectBackbufferDrawRectangle ( 
                (Parent->left   + window->left), 
                (Parent->top    + window->top), 
                1, 
                (window->height),
                 border1 );

             //board2, borda direita e baixo.
             rectBackbufferDrawRectangle ( 
                 (Parent->left   + window->left) + (window->width) -1, 
                 (Parent->top    + window->top), 
                 1, 
                 (window->height), 
                 border2 );
                 
             rectBackbufferDrawRectangle ( 
                 (Parent->left   + window->left), 
                 (Parent->top    + window->top) + (window->height) -1, 
                 (window->width), 
                 1, 
                 border2 );
                 
                 
            // Button label
            if (Selected == 1){
                dtextDrawString ( 
                    (Parent->left   + window->left) + offset,
                    (Parent->top    + window->top)  +8, 
                    COLOR_WHITE, windowname );
            }else{
                // (largura do botão, menos a largura da string)/2
                // #debug: Rotina provisória
                //dtextDrawString ( x +20, y +20, COLOR_TERMINALTEXT, string );
                dtextDrawString ( 
                    (Parent->left   + window->left) +offset, 
                    (Parent->top    + window->top)  +8, 
                    COLOR_TERMINALTEXT, windowname );
            };
        }

      //todo
      // configurar a estrutura de botão 
      // e apontar ela como elemento da estrutura de janela.
      //window->button->?
    }
    return window;








    //
    //  ======   cut here =========
    //


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
        
        // Passado via argumento.
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

        rectBackbufferDrawRectangle ( window->left, window->top, 
            window->width +1 +1, window->height +1 +1, window->bg_color );
        
       
       // barra de títulos;   
       //todo: usar o esquema de cores.      
			if (window->focus == 1)
			{ __tmp_color = xCOLOR_GRAY1; }        // mais escuro
			if (window->focus == 0)
			{ __tmp_color = window->bg_color; }    // escolhida pelo aplicativo;
        
        rectBackbufferDrawRectangle ( window->left +2, window->top +2, 
            window->width -4, 30, __tmp_color );        
        
		// String
        //dtextDrawString ( window->left +16 +8 +8, window->top +(32/3), 
          //  COLOR_TERMINALTEXT2, window->name );  

		// ??
		// Só criamos o botão na barra de títulos se tivermos uma barra de títulos.
		// Então esse é o lugar certo para essa rotina.
		// @todo: Se estivermos em full screen, não teremos botão.	

		if (MinimizeButton == 1)
		{
			window->minimizebuttonUsed = 1;
			
            // Create button.
			// #importante: os argumentos possuem deslocamentos em relação a janela que o botão está.
			//obs: talvez não precise ser assim. talvez possamos simplesmente criarmos o botão
			//na posição determinada agora.
			
			windowButton1 = createwCreateWindow2 ( WT_BUTTON, 1, 1, "V", 
                               (window->left + window->width -32 -32 -1 -32 -1), window->top +2, 
                                32, 32,
                                window, 0, 
                               (unsigned long) COLOR_TERMINAL2, (unsigned long) COLOR_TERMINAL2);

			//#test OK ISSO FUNCIONOU
			//registrar o posicionamento do botão na tela.
			//deve ser o o posicionamento da janela mais o deslocamento.

			windowButton1->left   = ( window->left + (window->width -32 -32 -1 -32 -1) );
			windowButton1->right  = windowButton1->left +32;
			windowButton1->top    = window->top +2;
			windowButton1->bottom = windowButton1->top +32; 
			windowButton1->isControl = 1; // Esse botão é um controle.
			windowButton1->isMinimize = 1;

			//RegisterWindow (windowButton1);
			window->minimize = windowButton1;
	    }
		
		if (MaximizeButton == 1)
		{
			window->maximizebuttonUsed = 1;

            // Create button.
            windowButton2 = createwCreateWindow2 ( WT_BUTTON, 1, 1, "^", 
                               (window->left + window->width -32 -32 -1), window->top +2, 
                               32, 32,
                               window, 0, 
                               (unsigned long) COLOR_TERMINAL2, (unsigned long) COLOR_TERMINAL2);

			windowButton2->left   = ( window->left + (window->width -32 -32 -1) );
			windowButton2->right  = windowButton2->left +32;
			windowButton2->top    = window->top +2;
			windowButton2->bottom = windowButton2->top +32; 
			windowButton2->isControl = 1; // Esse botão é um controle.
            windowButton2->isMaximize = 1;
            
			//RegisterWindow (windowButton2);
			window->minimize = windowButton2;
        }

        if (CloseButton == 1)
        {
			window->closebuttonUsed = 1;
			
			// Create button.
			windowButton3 = createwCreateWindow2 ( WT_BUTTON, 1, 1, "X", 
                                (window->left + window->width -32), window->top +2, 
                                 32, 32,
                                 window, 0, 
                                 (unsigned long) COLOR_TERMINAL2, (unsigned long) COLOR_TERMINAL2 );

			windowButton3->left   = ( window->left + (window->width -32) );
			windowButton3->right  = windowButton3->left +32;
			windowButton3->top    = window->top +2;
			windowButton3->bottom = windowButton3->top +32; 
            windowButton3->isControl = 1; // Esse botão é um controle.
            windowButton3->isClose = 1;
            
			//RegisterWindow (windowButton3);
			window->close = windowButton3;
         }

		//...
    }


	
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
			};
		}


		// Editbox
        if ( window->type == WT_EDITBOX )
        {
			// Se tiver o foco.
            if ( window->focus == 1 )
            {
                border_color = COLOR_BLUE;
                border_size = 2;
            }else{
                border_color = COLOR_INACTIVEBORDER;
                border_size = 1;
            };
         }


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
        rectBackbufferDrawRectangle( window->left, 
            window->top, window->width, border_size, border_color );

        rectBackbufferDrawRectangle( window->left, 
            window->top, border_size, window->height, border_color );

		//board2, borda direita e baixo.
        rectBackbufferDrawRectangle( window->left +window->width -1, 
            window->top, border_size, window->height, border_color );

        rectBackbufferDrawRectangle ( window->left, window->top +window->height -1, 
            window->width, border_size, border_color );

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
			window->rcClient = (void *) clientRect;
			
			// Object stuff.
			//window->rcClient->objectType = ObjectTypeRectangle;
			//window->rcClient->objectClass = ObjectClassGuiObjects;
			
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

            // Estamos posicionando e dimensionando a área de cliente do
            // editbox.
            if ( window->type == WT_EDITBOX || 
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
            }


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

            rectBackbufferDrawRectangle ( (unsigned long) window->rcClient->left, 
                (unsigned long) window->rcClient->top, 
                (unsigned long) window->rcClient->width, 
                (unsigned long) window->rcClient->height, 
                (unsigned long) window->rcClient->bg_color );

            // Done.
		};
		//Nothing.
	}



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
	// SCROLL BAR
	//

	// #todo: 
	// janela com scroll bar padrão.
	//if( ScrollBar == 1 ){}


	// Se create window foi usada para criar uma janela filha 
	// do tipo scroll bar. Completaremos.
	 
    if ( (unsigned long) type == WT_SCROLLBAR )
    {
        //#test
        window->parent = Parent;

        //bg
		rectBackbufferDrawRectangle ( window->left, window->top, 
			window->width, window->height, window->bg_color );  
		//#importante 
		//#todo
		if ( (void *) Parent != NULL )
		{
			//#todo: Check validation
            Parent->scrollbarUsed = 1;
		    Parent->scrollbar = window;
	    } 
		
		//Botão de cima da scrollbar vertival
		
		// Criar.
		windowButton4 = createwCreateWindow2 ( WT_BUTTON, 1, 1, "^", 
	                        window->left +1, window->top +1, 
	                        32, 32, 
		                    window, 0, 
		                    (unsigned long) COLOR_TERMINAL2, 
		                    (unsigned long) COLOR_TERMINAL2);
        
		// Registrar.
		//RegisterWindow (windowButton4); 
		windowButton4->isControl = 1;  // Esse botão é um controle.
		windowButton4->isScrollBarButton1 = 1;
        window->scrollbar_button1 = windowButton4; 
		
		//#test	
	    //limits
	    //if ( window->height == 0 || window->height > SavedX )
	    if ( window->height == 0 || window->height > 800 )  //#bugbug largura da tela
	    { 
		    window->height = 2; 
		}

	    //Botão do meio da scrollbar vertival
		// Criar.
		windowButton5 = createwCreateWindow2 ( WT_BUTTON, 1, 1, "=", 
	                        window->left + 1, window->top +(window->height/2), 
	                        32, 32,
		                    window, 0, 
		                    (unsigned long) COLOR_TERMINAL2, 
		                    (unsigned long) COLOR_TERMINAL2);
		
		// Registrar.
		//RegisterWindow (windowButton5);
		windowButton5->isControl = 1;  // Esse botão é um controle.
		windowButton5->isScrollBarButton2 = 1;
		window->scrollbar_button2 = windowButton5;
	
        //Botão de baixo da scrollbar vertival
		// Criar.
		windowButton6 = createwCreateWindow2 ( WT_BUTTON, 1, 1, "v", 
	                        window->left +1, window->top +(window->height -32 -1), 
	                        32, 32, 
		                    window, 0, 
		                    (unsigned long) COLOR_TERMINAL2, 
		                    (unsigned long) COLOR_TERMINAL2 );

		// Registrar.
		//RegisterWindow (windowButton6);
		windowButton6->isControl = 1;  // Esse botão é um controle.
		windowButton6->isScrollBarButton3 = 1;
		window->scrollbar_button3 = windowButton6;
		
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
		/*
		// window->button aqui fica a estrutura de botão
		// caso a janela for um botão.
        window->button = (struct button_d *) draw_button ( windowname, 
                                                 0, BS_DEFAULT, 0,
                                                 window->left, window->top, 
                                                 window->width, window->height, 
                                                 window->bg_color );
        */
        
        //para repintar precisamos olhar na estrutura de botão
        //e encontrarmos a janela.
        //window->button->window = window;
        
        // #bugbug
        // E se retornar NULL ?
        //if ( (void *) window->button == NULL ){} 
        
        //#test
        window->parent = Parent;
        window->isButton = 1;
    }
    


    // # editbox #
    if ( (unsigned long) type == WT_EDITBOX )
    {
        window->parent = Parent;
        window->isEditBox = 1;
        //...
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
	
	

	// ## Overlapped. ##
    if (window->type == WT_OVERLAPPED)
    {
        //#test
        window->parent = Parent;

		active_window = window->id;
		window->active = 1;
		
		// Não começar com o foco.
		//window_with_focus = window->id;
		//window->focus = 1;
		
		// ## scrollbar ##
		//Esses valores precisam ser melhor declarados.
        
		// #BUGBUG
		// SÓ CRIAREMOS SCROLL BAR NUMA OVERLAPPED SE A FLAG INDICAR ISSO;
		// ISSO VALE PRA OUTROS TIPOS DE JANELA NÃO SOMENTE ESSE TIPO.
		
		// #test
		// No momento vamos criar a scrool bar apenas para testar e implementar.

        window->scrollbar = createwCreateWindow2 ( WT_SCROLLBAR, 1, 1, "scrollbar-test", 
                                window->right -37, window->top +2 +32 +2, 
                                35, (window->height -2 -35 -2 -24 -2),
                                window, 0, 
                                COLOR_GREEN,
                                COLOR_YELLOWGREEN );
                                //(unsigned long) CurrentColorScheme->elements[csiScrollBar], 
                                //(unsigned long) CurrentColorScheme->elements[csiScrollBar] );

        //RegisterWindow (window->scrollbar);

        // status bar
        //Esses valores precisam ser melhor declarados.
		
		//#BUGBUG
		//SÓ CRIAREMOS STATUS BAR NUMA OVERLAPPED SE A FLAG INDICAR ISSO;
		//ISSO VALE PRA OUTROS TIPOS DE JANELA NÃO SOMENTE ESSE TIPO.		

        window->statusbar = createwCreateWindow2 ( WT_STATUSBAR, 1, 1, "Status: ...", 
                                window->left+1, window->bottom-25-1, 
                                window->width, 25, window, 0, 
                                COLOR_BLUE, COLOR_GRAY );

        //RegisterWindow (window->statusbar);

		window->statusbarUsed = 1;
		window->statusbar = window->statusbar;

        // # icon #
        // Os ícones já estão carregados, 
        // vamos apenas decodificá-lo no backbuffer 
        //bmpDisplayBMP ( appIconBuffer, window->left +8, window->top +8 );
    }



    // ## Icon. ##
    // #todo
    // Planejar o posicionamento centralizado do bmp dentro da 
    // janela ícone.
    if (window->type == WT_ICON)
    {
        //bmpDisplayBMP ( appIconBuffer, window->left +8, window->top +8 );
        //bmpDisplayBMP ( appIconBuffer, window->left +8, window->top +8 );

		// String
       // dtextDrawString ( window->left +8, window->top +16 +8 +8, 
         //   COLOR_TERMINALTEXT2, window->name );  
    }



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

    /*
    int z;

    z = (int) z_order_get_free_slot();
    
    if ( z >= 0 && z < KGWS_ZORDER_MAX )
    {
        window->z = z;
        Windows[z] = (unsigned long) window;
    }else{
        panic ("CreateWindow: no free slot on zorder");
    };
    */


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
	

    //
    // Thread.
    //

	// Associando a janela criada a trhead atual, 
	// que chamou essa rotina. O problema é na hora da inicialização.
    // #importante: Quando criarmos uma janela do tipo controle
    // uma thread será associada à ela. Então o window manager
    // poderá mandar mensagem para o procedimento de janela
    // do aplicativo avisando dos efeitos dobre o controle.

    /*
    window->control = (struct thread_d *) threadList[current_thread];

        if ( (void *) window->control != NULL )
        {
			if ( window->used != 1 || window->magic != 1234 )
			{
			    window->control = NULL;
			}
        }
      */  
        
        //
        // MSG_CREATE
        //
        
        // #test
        // O procedimento de janelas do aplicativo receberá essa mensagem
        // quando criar uma overlapped, pedindo pra ele terminar de criar
        // as janelas filhas da overlapped.
 
    /*
    if (window->type == WT_OVERLAPPED)
    {
		if ( (void *) window->control != NULL )
        {
			if ( window->used == 1 || window->magic == 1234 )
			{
			   // mandamos a mensagem
			   // o aplicativo decide o que fazer com ela.
			    window->control->window = window;
			    window->control->msg = MSG_CREATE;
			    window->control->long1 = 0;
			    window->control->long2 = 0;
			    window->control->newmessageFlag = 1;
			}
		}        
    };
    */
 
    return (void *) window;
}



/*
 ******************************************************
 * createwCreateWindow:
 * 
 *     It creates a window
 */


// Essa será a função que atenderá a interrupção
// esse é o serviço de criação da janela.
// talvez ampliaremos o número de argumentos

// #todo
// Precisamos de uma estrutura de janela que fique aqui
// no servidor.
// Não podemos usar a estrutura de janela
// da api.

                      
void *
createwCreateWindow ( 
    unsigned long type, 
    unsigned long status, 
    unsigned long view, 
    char *windowname, 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height, 
    struct gws_window_d *pWindow, 
    int desktopid, 
    unsigned long clientcolor, 
    unsigned long color ) 
{

   struct gws_window_d *__w;
   
    //1. Começamos criando uma janela simples
    //2. depois criamos o frame. que decide se vai ter barra de títulos ou nao.
    
    /*
    __w = (void *) CreateWindow ( type, status, view, (char *) windowname, 
                           x, y, width, height, 
                           (struct window_d *) pWindow, desktopid, clientcolor, color );  
    */
    
    // No caso dos tipos com moldura então criaremos em duas etapas.
    // no futuro todas serão criadas em duas etapas e 
    // CreateWindow será mais imples.
    
    
    // Overlapped
    if ( type == WT_OVERLAPPED )
    {
        __w = (void *) createwCreateWindow2 ( WT_SIMPLE, 
                           status, 
                           view, 
                           (char *) windowname, 
                           x, y, width, height, 
                           (struct gws_window_d *) pWindow, 
                           desktopid, clientcolor, color );      
    
        // Pintamos simples, mas a tipagem será overlapped.
        __w->type = WT_OVERLAPPED;   
       goto draw_frame;
    }


    //edit box
    if ( type == WT_EDITBOX )
    {
        // Podemos usar o esquema padrão de cores ...
        __w = (void *) createwCreateWindow2 ( WT_SIMPLE, 
                           status, 
                           view, 
                           (char *) windowname, 
                           x, y, width, height, 
                           (struct gws_window_d *) pWindow, 
                           desktopid, clientcolor, color );      

        //pintamos simples, mas a tipagem será  overlapped
        __w->type = WT_EDITBOX;   
        goto draw_frame;
    }


    //button
    if ( type == WT_BUTTON )
    {
        gde_debug_print ("[DEBUG]: createwCreateWindow WT_BUTTON\n");
        // Podemos usar o esquema padrão de cores ...
        __w = (void *) createwCreateWindow2 ( WT_BUTTON, 
                           status, 
                           view, 
                           (char *) windowname, 
                           x, y, width, height, 
                           (struct gws_window_d *) pWindow, 
                           desktopid, clientcolor, color ); 

        //pintamos simples, mas a tipagem será  overlapped
        __w->type = WT_BUTTON;   
        goto draw_frame;
    }


    // Types with no frame!
    if ( type == WT_SIMPLE )
    {
        __w = (void *) createwCreateWindow2 ( type, 
                       status, 
                       view, 
                       (char *) windowname, 
                       x, y, width, height, 
                       (struct gws_window_d *) pWindow, 
                       desktopid, clientcolor, color );  

         if ( (void *) __w == NULL )
            gde_debug_print ("createwCreateWindow: createwCreateWindow2 fail \n");
    

        __w->type = WT_SIMPLE;
        return (void *) __w;
    }

    gde_debug_print ("createwCreateWindow: [FAIL] type \n");
    return NULL;
    
    
    //
    // == Draw frame ===============================
    //
    
    // #todo:
    // Lembrando que frame é coisa do wm.
    // Porém tem algumas coisas que o window server faz,
    // como as bordas de um editbox.

draw_frame:

    // #IMPORTANTE
    // DESENHA O FRAME DOS TIPOS QUE PRECISAM DE FRAME.
    // OVERLAPED, EDITBOX, CHECKBOX ...

    // draw frame.
    // #todo:
    // Nessa hora essa rotina podera criar a barra de títulos.
    // o wm poderá chamar a rotina de criar frame.
    
    if ( type == WT_OVERLAPPED || 
         type == WT_EDITBOX || 
         type == WT_BUTTON )
    {
        createwDrawFrame ( 
            (struct gws_window_d *) pWindow,  //parent.
            (struct gws_window_d *) __w,      //bg do botão em relação à sua parent. 
            0, 0, width, height, 
            1 );  //style
        
        return (void *) __w;   
    }

}



//
// End.
//



