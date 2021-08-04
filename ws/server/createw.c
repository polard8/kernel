/*
 * File: createw.c 
 * 
 *      Creates a window.
 *      It's part of the gws project.
 * 
 * History:
 *     2019 - Created by Fred Nora.
 */
 
    // #importante
    // O frame de uma janela deve ser parte do Window Manager.

// #bugbug
// #todo
// Para lidarmos com essas estruturas do kernel
// devemos usar a chamada sci2. int 0x82. ??


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



#include <gws.h>


// habilitando/desabilitando globalmente 
// alguns componentes da janela

int gUseShadow = TRUE;
int gUseFrame = TRUE;
//int gUseShadow = TRUE;
// ...

// #todo
// Essas rotina serão chamada pelo request assincrono sem resposta.

/*
void useShadow( int value );
void useShadow( int value )
{
    // Ativando.
    if ( value == TRUE ){
        gUseShadow = TRUE;
        return;
    }

    gUseShadow = FALSE;
}
*/

/*
void useFrame( int value );
void useFrame( int value )
{
    // Ativando.
    if ( value == TRUE ){
        gUseFrame = TRUE;
        return;
    }

    // No frames.
    // It means that the loadable window manager 
    // will create some kind of frames for all the windows, or not.
    
    gUseFrame = FALSE;
}
*/





/*
 *************************************************************
 * xxxCreateSurfaceWindow: 
 * 
 *     Cria uma janela com base em uma struct.
 *     Retorna o endereço da estrutura da janela criada. 
 *     Para que possa ser registrada na lista windowList[].
 *     Essa lista tambem fica em kgws no kernel.
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
 *
 */


void *xxxCreateSurfaceWindow( 
    unsigned long type,        // 1, Tipo de janela (popup,normal,...)
    unsigned long status,      // 2, Estado da janela (ativa ou nao)
    unsigned long view,        // 3, (min, max ...)
    char *windowname,          // 4, Título. 
    unsigned long x,           // 5, Deslocamento em relação às margens do Desktop. 
    unsigned long y,           // 6, Deslocamento em relação às margens do Desktop.
    unsigned long width,       // 7, Largura da janela.
    unsigned long height,      // 8, Altura da janela.
    void *pSurfaceWindow,      // 9, Endereço da estrutura da janela mãe.
    unsigned long desktop_id,  //10, Desktop id.
    unsigned long clientcolor, //11, Cor da área de cliente
    unsigned long color )      //12, Color (bg) (para janela simples).
{ 

    // opaque
    // A ring0 structure pointer.
    void *wObjectPointer;
    
	// Enviando tudo via argumento.
	// Esse método dá a possibilidade de enviarmos ainda 
	// mais argumentos. 
	// #importante: Isso está funcionado, Vamos fazer assim e 
	// não do jeito antigo.


	unsigned long message_buffer[12];



    gwssrv_debug_print ("xxxCreateSurfaceWindow: \n");

	message_buffer[0]  = (unsigned long) type;
	message_buffer[1]  = (unsigned long) status;
	message_buffer[2]  = (unsigned long) view;
	message_buffer[3]  = (unsigned long) windowname;
	message_buffer[4]  = (unsigned long) x;
	message_buffer[5]  = (unsigned long) y;
	message_buffer[6]  = (unsigned long) width;
	message_buffer[7]  = (unsigned long) height;
	message_buffer[8]  = (unsigned long) pSurfaceWindow;
	message_buffer[9]  = (unsigned long) desktop_id;
	message_buffer[10] = (unsigned long) clientcolor;
	message_buffer[11] = (unsigned long) color;

    // #bugbug
    // Maybe we need to use sc82()

    wObjectPointer = (void *) gramado_system_call ( 
                          118 , 
                          (unsigned long) &message_buffer[0], 
                          (unsigned long) &message_buffer[0], 
                          (unsigned long) &message_buffer[0] );

    if ( (void *) wObjectPointer == NULL ){
        gwssrv_debug_print ("xxxCreateSurfaceWindow: [FAIL] wObjectPointer\n");
        return NULL;  
    }

    // ??
    // #teste
    // Vamos enviar a mensagem MSG_CREATE para o procedimento de janela.
    // Assim ele pode terminar de pintar nessa mesma janela.

    return (void *) wObjectPointer;    
}


// not tested yet
struct gws_surface_d *xxxCreateSurface( 
    unsigned long left,
    unsigned long top,
    unsigned long width,
    unsigned long height,
    unsigned long color )
{

    struct gws_surface_d *surface;

    void *surfaceWindowObject;

//
// surface
//
    surface = (struct gws_surface_d *) malloc ( sizeof( struct gws_surface_d ) );

    if ( (void*) surface == NULL )
    {
        //todo: message
        return NULL;
    }

    surface->initialized = FALSE;

//
// window
//

    surfaceWindowObject = (void *) xxxCreateSurfaceWindow ( 
                                       WT_SIMPLE, 
                                       1, 
                                       1, 
                                       "Surface",
                                       left, top, width, height, 
                                       0, 0, COLOR_BLACK, COLOR_BLACK );  

    if ( (void*) surfaceWindowObject == NULL )
    {
        //todo: message
        return NULL;
    }
    
    
//
// structure
//

    surface->used  = TRUE;
    surface->magic = 1234;
    surface->window_object = (void *) surfaceWindowObject;
    surface->left   = left;
    surface->top    = top;
    surface->width  = width;
    surface->height = height;

    surface->dirty = FALSE;
    surface->locked = FALSE;
    
    surface->next = NULL;
    surface->initialized = TRUE;

    return (struct gws_surface_d *) surface;
}



// Strings
//char *title_when_no_title = "Window";


void demoTerry(void)
{
     createwCreateWindow ( 
         WT_SIMPLE, 
         1, 
         1, 
         "terry0",  
         0, 0, 240 +8+8, 320 +8+8,   
         gui->screen_window, 0, 
         COLOR_WHITE, COLOR_WHITE );
  
     struct gws_window_d *terry;
     terry = (struct gws_window_d *) createwCreateWindow ( 
         WT_SIMPLE, 
         1, 
         1, 
         "terry",  
         8, 8, 240, 320,   
         gui->screen_window, 0, 
         COLOR_WHITE, COLOR_WHITE );

    // IN: l,r,t,b, solid
    DrawBorder ( 
        8, 240, 
        8, 320, 1 );

    // IN: l,r,t,b, solid
    //DrawBorder ( 
    //    8, 240, 
    //    8, 320, 0 );

    if ( (void*) terry != NULL){
        dtextDrawText ( (struct gws_window_d *) terry,
            20, 20, COLOR_BLUE, "Demo: Terry's window" );
        dtextDrawText ( (struct gws_window_d *) terry,
            20, 32, COLOR_RED,  "by Fred Nora" );
    }
}


/*
 ********************
 * xxxCreateWindow: 
 * 
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

void *xxxCreateWindow ( 
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

	// #todo: 
	// O argumento style está faltando.
	// Cada tipo de tanela poderá ter vários estilos.
	// Obs: 
	// Podemos ir usando apenas um estilo padrão por enquanto.


    // #todo:
    // Receberemos isso via parametro de função.
    // Default is FALSE.
    // We need to know the parent's bg color.
    int Transparent = FALSE;

    //unsigned long parent_bg_color;


	// (min, max ...).
	//int View;

    int Maximized;  //??
    int Minimized;  //

	// Bars.
    int TitleBar  = FALSE;
    int MenuBar   = FALSE;
    int ToolBar   = FALSE;
    int StatusBar = FALSE;
    int ScrollBar = FALSE;
    // ...

	// Title bar buttons. [v] [X] 
    int MinimizeButton = FALSE;
    int MaximizeButton = FALSE;
    int CloseButton    = FALSE;
    // ...

	// Items.
    int Background    = FALSE;
    int ClientArea    = FALSE;
    int Shadow        = FALSE;
    int ButtonDown    = FALSE; 
    int ButtonUp      = FALSE;  // ??
    int ButtonSysMenu = FALSE;  // system menu na barra de títulos.
    int Border        = FALSE;  // New !!! usado no edit box.
	// ...
	
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


//
// The client rectangle.
//

    struct gws_rect_d *clientRect;

//
// Border
//

    // #
    // Improvisando uma largura de borda.
    // Talvez devamos receber isso via parâmetros.

    unsigned long border_size = 0;
    unsigned long border_color = COLOR_BORDER;

    // ??
    unsigned long __tmp_color=0;

//
// Position and dimension.
//

    unsigned long WindowX      = x;
    unsigned long WindowY      = y;
    unsigned long WindowWidth  = width;
    unsigned long WindowHeight = height;
    // #todo: right and bottom.

//
// Position and dimension for fullscreen mode.
//

    // Initial configuration.
    // It will change.

    // #bugbug
    // left and top needs to be '0'?

    unsigned long fullWindowX      = WindowX + border_size;
    unsigned long fullWindowY      = WindowY + border_size;
    unsigned long fullWindowWidth  = WindowWidth;
    unsigned long fullWindowHeight = WindowHeight;
    // #todo: right and bottom.


//
// Button suport
//

    int buttonFocus=0;
    int buttonSelected=0;
    unsigned long buttonBorderColor1=0;
    unsigned long buttonBorderColor2=0;
    unsigned long buttonBorderColor2_light=0;

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
   // #todo: 
   // Onde o Kernel colocará essa mensagem de erro ?
   // Por enquanto no backbuffer.

    window = (void *) malloc( sizeof(struct gws_window_d) );

    if ( (void *) window == NULL )
    {

        // #fixme

        debug_print ("xxxCreateWindow: [ERROR] window\n");
        printf      ("xxxCreateWindow: [ERROR] window\n");

        // #debug
        gwssrv_show_backbuffer ();
        while(1){}
        
        // #todo
        // We need to return.
        //return NULL; 
    }


    // We have a valid pointer.
    // Let's set up the elements using the parameters.

    // #todo
    // Object support.
    //window->objectType  = ObjectTypeWindow;
    //window->objectClass = ObjectClassGuiObjects;

    // #todo
    // #importante
    // Id. 
    // A janela recebe um id somente na hora de registrar.
    // window->id = ?.


    // Validating the structure.
    // #todo: Mover isso par ao fim da função.

    window->used  = TRUE;
    window->magic = 1234;

//
// The window name
//

    // #test
    if ( (void*) windowname == NULL ){
        debug_print ("xxxCreateWindow: [ERROR] Invalid windowname\n");
    }

    // #test
    if ( *windowname == 0 ){
        debug_print ("xxxCreateWindow: [ERROR] Invalid *windowname\n");
    }

    window->name  = (char *) windowname;

//
// Window type
//

    // Tipo é unsigned long pois poderá ser um conjunto de flags.

    window->type = (unsigned long) type;


//
// Parent window
//

    // #test
    if ( (void*) pWindow == NULL ){
        debug_print ("xxxCreateWindow: [CHECK THIS] Invalid parent window\n");
    }

    Parent = (void *) pWindow;
    
    window->parent = Parent;


    //#todo: 
    // é importante definir o procedimento de janela desde já.
    //senão dá problemas quando chamá-lo e ele naõ estiver pronto.
    //Procedure support.
    //#todo: Devemos receber esses parâmetros e configurar aqui.
    //#bugbug: Talvez isso será configurado na estrutura
    // de window class. Se é que termos uma.
    //window->procedure = (unsigned long) &system_procedure;
    //window->wProcedure = NULL;  //Estrutura.

//
// View
//

    // Modo de exibição:
    window->view = (int) view;

    //Se não foi oferecido um modo de exibição, então temos um problema.
    //?? Talvez devamos retornar um erro. 
    //if( (int) view == VIEW_NULL ){ return NULL; };


//
// == Status ============================
//

    // Qual é o status da janela, se ela é a janela ativa ou não.
    //?? Devemos definir quais são os status possíveis da janela.

    window->status = status;

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


//
// Focus
//

    // Initialize focus flag.
    window->focus = FALSE; 


//
// == Margins and dimensions ======================
//

	// @todo:
	// Se for uma janela filha o posicionamento deve ser somado às margens 
	// da área de cliente da janela que será a janela mãe.

	// #bugbug @todo 
	// Esses valores de dimensões recebidos via argumento na verdade 
	// devem ser os valores para a janela, sem contar o frame, que 
	// inclui as bordas e a barra de títulos.

    // Dimensões.
    window->width  = WindowWidth;
    window->height = WindowHeight;

    // Deslocamento em relação a janela mãe.
    window->x = WindowX;
    window->y = WindowY;

    //++
    // Margens.
    // Deslocamento em relação a tela. (Screen)
    if ( window->parent != NULL ){
        window->left = (window->parent->left + window->x); //x; 
        window->top  = (window->parent->top  + window->y); //y;
        
    // No caso da primeira janela de todas.
    }else{
        window->left = window->x;
        window->top  = window->y; 
    };
    window->right  = (unsigned long) ( window->left + window->width );
    window->bottom = (unsigned long) ( window->top  + window->height ); 
    //--


//
// == Margins and dimensions for fullscreen mode ==================
//

    // #bugbug
    // This is valid only for some types of window.

    // #bugbug
    // left and top needs to be '0'?

    window->full_left   = fullWindowX;
    window->full_top    = fullWindowY;
    window->full_right  = fullWindowX + fullWindowWidth;
    window->full_bottom = fullWindowY + fullWindowHeight;
    window->full_width  = fullWindowWidth;
    window->full_height = fullWindowHeight;


//
// Background
//

    window->bg_color            = (unsigned long) color;
    window->clientrect_bg_color = (unsigned long) clientcolor;

//
// Input pointer
//

    window->ip_on = FALSE;  // desligado
    window->ip_device = IP_DEVICE_NULL;
    window->ip_x = 0;       // in chars
    window->ip_y = 0;       // in chars
    window->ip_color = COLOR_BLACK;
    window->ip_type = 0;    // #bugbug #todo

    // In pixel, for mouse pointer ip device.
    window->ip_pixel_x = 0;
    window->ip_pixel_y = 0;


		
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


		//Barras.
		//As flags que representam a presença de cada uma das barras
		//serão acionadas mais tarde, na hora da pintuda, de acordo com
		//o tipo de janela à ser pintada.


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


//
// Client window 
//

    // (#importante)
    // Client window support.
    // Obs: A área de cliente será um retângulo e não uma janela.
    // Mas nda impede da estrutra gerenciar uma janela que fique 
    // em cima da área de cliente.

    window->client_window = NULL;  // window. 
    window->rcClient      = NULL;  // rect. (#importante)


//
// Terminal window
//

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


//
// Desktop support
//

    //window->desktop = (void*) Desktop; //configurado anteriormente.
    //window->desktop_id = Desktop->id;  //@todo: verificar elemento.

//
// Menu support
//

    window->menu_window  = NULL;
    window->sysMenu      = NULL;
    window->barMenu      = NULL;
    window->defaultMenu  = NULL;

    // What is that?
    window->isMenu    = 0;
    window->isButton  = 0;
    window->isEditBox = 0;


//
// Selected menu item.
//

    //Caso a janela seja um ítem de menu.
    window->selected = FALSE; 

    // Texto, caso a janela seja um ítem de menu
    // window->text = NULL; 

    // Draw support.
    window->draw   = 0;      //@todo: Cuidado com isso.
    window->redraw = 0;
    window->show   = 1; //Inicialmente presumimos que precisamos mostrar essa janela.
    // Continua ...

        //Abaixo, elementos referenciados com menor frequência.
	    
		//window->desktop = NULL; //@todo: Definir à qual desktop a janela perence.
		//window->process = NULL; //@todo: Definir à qual processo a janela perence.

//
// Locked
//

    window->locked = FALSE;


    // Linked list.
    //window->linkedlist = NULL;


//
// Navigation
//

    // Prev e next.
    window->prev = (void *) Parent;
    window->next = NULL;


    //==========


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


//
// Flags
//

    // Initializing the flag for all the elements.
    // not used by default.

    window->shadowUsed     = FALSE;  //  1
    window->backgroundUsed = FALSE;  //  2
    window->titlebarUsed   = FALSE;  //  3
    window->controlsUsed   = FALSE;  //  4
    window->borderUsed     = FALSE;  //  5  
    window->menubarUsed    = FALSE;  //  6 
    window->toolbarUsed    = FALSE;  //  7
    window->clientAreaUsed = FALSE;  //  8
    window->scrollbarUsed  = FALSE;  //  9
    window->statusbarUsed  = FALSE;  // 10

//
// Element style
//

    // Initialize style indicators.

    window->shadow_style     = 0;
    window->background_style = 0;
    window->titlebar_style   = 0;
    window->controls_style   = 0;
    window->border_style     = 0;
    window->menubar_style    = 0;
    window->toolbar_style    = 0;
    window->clientarea_style = 0;
    window->scrollbar_style  = 0;
    window->statusbar_style  = 0;

//
// Elements
//

    // Selecting the elements given the type.
    // Each type has it's own elements.

    switch (type){

        // Simple window. (Sem barra de títulos).
        case WT_SIMPLE:
            Background = TRUE;
            window->backgroundUsed = TRUE;
            window->background_style = 0;
            break;

        // Edit box. (Simples + borda preta).
        // Editbox não tem sombra, tem bordas. 
        case WT_EDITBOX:
            Background = TRUE;
            Border     = TRUE;
            window->backgroundUsed = TRUE;
            window->background_style = 0;
            break;

        // Overlapped. (completa, para aplicativos).
        // Sombra, bg, título + borda, cliente area ...
        // #obs: Teremos recursividade para desenhar outras partes.
        case WT_OVERLAPPED:
            Shadow         = TRUE;
            Background     = TRUE;
            TitleBar       = TRUE;
            ClientArea     = TRUE;
            MinimizeButton = TRUE;
            MaximizeButton = TRUE;
            CloseButton    = TRUE; 
            window->shadowUsed     = TRUE;
            window->backgroundUsed = TRUE;
            window->titlebarUsed   = TRUE;
            window->controlsUsed   = TRUE;
            window->clientAreaUsed = TRUE;
            window->background_style = 0;
            break;

        // Popup. (um tipo de overlapped mais simples).
        case WT_POPUP:
            Shadow     = TRUE;
            Background = TRUE;
            window->shadowUsed     = TRUE;
            window->backgroundUsed = TRUE;
            window->background_style = 0;
            break;
  
        // Check box. (Simples + borda preta).
        // Caixa de seleção. Caixa de verificação. Quadradinho.
        // #todo: checkbox has borders.
        case WT_CHECKBOX:
            Background = TRUE;
            Border     = TRUE;
            window->backgroundUsed = TRUE;
            // #todo: structure element for 'border'
            window->background_style = 0;
            break;

        //case WT_SCROLLBAR:
            // Nothing for now.
            //break;

        // Only the bg for now.
        // #todo: Button has borders.
        case WT_BUTTON:
            Background = TRUE;
            window->backgroundUsed = TRUE;
            window->background_style = 0;
            break;

        // Status bar.
        // #todo: checkbox has borders sometimes.
        case WT_STATUSBAR:
            Background = TRUE;
            window->backgroundUsed = TRUE;
            window->background_style = 0;
            break;

        // Ícone da área de trabalho.
        // #todo: icons has borders sometimes.
        case WT_ICON:
            Background = TRUE;
            window->backgroundUsed = TRUE;
            window->background_style = 0;
            break;

        // barra de rolagem
        // botões de radio 
        // ...


        // #todo
        // #bugbug
        // We need to work on this case.
 
        default:
            debug_print("xxxCreateWindow: [DEBUG] default\n");
                 printf("xxxCreateWindow: [DEBUG] default\n");
            while(1){}
            //return NULL;
            break;
    };

    // #debug
    // while(1){}


//
// == Draw ========
//


	// Hora de pintar. 
	// Os elementos serão incluídos se foram 
	// selecionados anteriormente.


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

    // 1
    if ( Shadow == TRUE )
    {
        window->shadowUsed = TRUE;

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
            if (window->focus == 1){ __tmp_color = xCOLOR_GRAY1; }
            if (window->focus == 0){ __tmp_color = xCOLOR_GRAY2; }

            //ok funciona
            //rectBackbufferDrawRectangle ( window->left +1, window->top +1, 
            //    window->width +1 +1, window->height +1 +1, 
            //    __tmp_color, 1 ); 
         
            //test
            //remeber: the first window do not have a parent.
            if ( (void*) Parent == NULL )
            { 
                gwssrv_debug_print ("xxxCreateWindow: [Shadow] Parent\n"); 
                //exit(1); 
                rectBackbufferDrawRectangle ( 
                    (window->left +1),     (window->top +1), 
                    (window->width +1 +1), (window->height +1 +1), 
                    __tmp_color, TRUE ); 
            }

            if ( (void*) Parent != NULL ){

                rectBackbufferDrawRectangle ( 
                    (window->left +1),     (window->top +1), 
                    (window->width +1 +1), (window->height +1 +1), 
                    __tmp_color, TRUE ); 
            }
            
            window->shadow_color = __tmp_color;
        }

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

    // 2
    if ( Background == TRUE )
    {
        window->backgroundUsed = TRUE;

        // Select background color.
        switch (type){
            case WT_SIMPLE:
            case WT_POPUP:
            case WT_EDITBOX:
            case WT_CHECKBOX:
            case WT_ICON:
            case WT_BUTTON:
                window->bg_color = color;
                break;
            default:
                //#fixme
                window->bg_color = COLOR_PINK;  //BLACK?
                //window->bg_color = CurrentColorScheme->elements[csiWindowBackground]; 
                break;
        };

        // Draw 

        //#bugbug
        //Remember: The first window do not have a parent.

        if ( (void*) Parent == NULL )
        { 
            gwssrv_debug_print ("xxxCreateWindow: [Background] Parent\n"); 
            rectBackbufferDrawRectangle ( 
                    window->left, window->top, 
                    window->width, window->height, 
                    window->bg_color, TRUE );
        }  

        if ( (void*) Parent != NULL )
        {
            gwssrv_debug_print ("xxxCreateWindow: [Background] No Parent\n"); 
            rectBackbufferDrawRectangle ( 
                window->left, window->top, 
                window->width, window->height, 
                window->bg_color, TRUE );
        }
    }

    //#debug
    //asm ("int $3");

//
// == Button ====================
//

    // Termina de desenhar o botão, mas não é frame
    // é só o botão...
    // caso o botão tenha algum frame, será alguma borda extra.

    if ( (unsigned long) type == WT_BUTTON )
    {

        //border color
        //o conceito de status e state
        //está meio misturado. ja que estamos usando
        //a função de criar janela para criar botão.
        //#bugbug
    
        switch ( status )
        {
            case BS_FOCUS:
                buttonBorderColor1 = COLOR_BLUE;
                buttonBorderColor2 = COLOR_BLUE;
                break;

            case BS_PRESS:
                buttonSelected = TRUE;
                buttonBorderColor1 = COLOR_WHITE; 
                buttonBorderColor2 = xCOLOR_GRAY3;
                buttonBorderColor2_light = xCOLOR_GRAY5; 
                break;

            case BS_HOVER:
                break;
                    
            case BS_DISABLED:
                buttonBorderColor1 = COLOR_GRAY;
                buttonBorderColor2 = COLOR_GRAY;
                break;

            case BS_PROGRESS:
                break;

            case BS_DEFAULT:
            default: 
                buttonSelected = FALSE;
                buttonBorderColor1 = COLOR_WHITE;
                buttonBorderColor2 = xCOLOR_GRAY3; 
                buttonBorderColor2_light = xCOLOR_GRAY5;
                break;
        };

        // center?
        size_t tmp_size = (size_t) strlen ( (const char *) windowname );
        unsigned long offset = 
            ( ( (unsigned long) window->width - ( (unsigned long) tmp_size * (unsigned long) gcharWidth) ) / 2 );


        //#debug
        if ( (void*) Parent == NULL ){
            gwssrv_debug_print ("xxxCreateWindow: [WT_BUTTON] Parent NULL\n"); 
        }


        if ( (void*) Parent != NULL )
        {

            //
            // Drawing a button
            //
            
            // Maybe we can use a helper function to do this job.
            // See: button.c

            //  ____
            // |
            //
            
            //board1, borda de cima e esquerda.
            
            //cima
            rectBackbufferDrawRectangle ( 
                window->left+1, window->top,
                window->width-2, 1, 
                COLOR_BLACK, TRUE );
            rectBackbufferDrawRectangle ( 
                window->left+1, window->top+1,
                window->width-2, 1, 
                buttonBorderColor1, TRUE );
            rectBackbufferDrawRectangle ( 
                window->left+1+1, window->top+1+1,
                window->width-4, 1, 
                buttonBorderColor1, TRUE );
               
            //esq
            rectBackbufferDrawRectangle ( 
                window->left, window->top+1, 
                1, window->height-2,
                COLOR_BLACK, TRUE );
            rectBackbufferDrawRectangle ( 
                window->left+1, window->top+1, 
                1, window->height-2,
                buttonBorderColor1, TRUE );
            rectBackbufferDrawRectangle ( 
                window->left+1+1, window->top+1+1, 
                1, window->height-4,
                buttonBorderColor1, TRUE );

            //  
            //  ____|
            //

            //board2, borda direita e baixo.
            
            //dir
            rectBackbufferDrawRectangle ( 
                 ((window->left) + (window->width) -1 -1 -1), window->top+1+1, 
                 1, window->height-4, 
                 buttonBorderColor2_light, TRUE );
            rectBackbufferDrawRectangle ( 
                 ((window->left) + (window->width) -1 -1), window->top+1, 
                 1, window->height-2, 
                 buttonBorderColor2, TRUE );
            rectBackbufferDrawRectangle ( 
                 ((window->left) + (window->width) -1), window->top+1, 
                 1, window->height-2, 
                 COLOR_BLACK, TRUE );

            //baixo
            rectBackbufferDrawRectangle ( 
                 window->left+1+1, ( (window->top) + (window->height) -1 -1 -1),  
                 window->width-4, 1, 
                 buttonBorderColor2_light, TRUE );
            rectBackbufferDrawRectangle ( 
                 window->left+1, ( (window->top) + (window->height) -1 -1),  
                 window->width-2, 1, 
                 buttonBorderColor2, TRUE );
            rectBackbufferDrawRectangle ( 
                 window->left+1, ( (window->top) + (window->height) -1 ),  
                 window->width-2, 1, 
                 COLOR_BLACK, TRUE );


            // Button label

            if (buttonSelected == TRUE){
                dtextDrawString ( 
                    (window->left) +offset, 
                    (window->top)  +8, 
                    COLOR_WHITE, window->name );
            }

            if (buttonSelected == FALSE){
                dtextDrawString ( 
                    (window->left) +offset,  
                    (window->top)  +8,  
                    COLOR_BLACK, window->name );
            }
        }

      //todo
      // configurar a estrutura de botão 
      // e apontar ela como elemento da estrutura de janela.
      //window->button->?
    
    } //button


//done:

    // #todo
    //window->used  = TRUE;
    //window->magic = 1234;

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

// #todo: change name to 'const char *'

void *createwCreateWindow ( 
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

   struct gws_window_d  *__w;


    // This function is able to create some few 
    // kinds of windows for now:
    // overlapped, editbox, button and simple.

    int ValidType=FALSE;

    switch (type){
    case WT_OVERLAPPED:  ValidType=TRUE; break;
    case WT_EDITBOX:     ValidType=TRUE; break;
    case WT_BUTTON:      ValidType=TRUE; break;
    case WT_SIMPLE:      ValidType=TRUE; break;
    };

    if ( ValidType == FALSE ){
        gwssrv_debug_print ("createwCreateWindow: Invalid type\n");
        return NULL;
    }



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
    
    
    // #todo
    // Check parent window validation.
    // APPLICATION window uses the screen margins for relative positions.
    //if ( (void*) pWindow == NULL ){}
    

    // #todo
    // check window name validation.
    //if ( (void*) windowname == NULL ){}
    //if ( *windowname == 0 ){}


// ============================
// Types with frame.

    // Overlapped
    if ( type == WT_OVERLAPPED )
    {
        __w = (void *) xxxCreateWindow ( 
                           WT_SIMPLE, status, view, 
                           (char *) windowname, 
                           x, y, width, height, 
                           (struct gws_window_d *) pWindow, 
                           desktopid, clientcolor, color ); 

         if ( (void *) __w == NULL ){
             gwssrv_debug_print ("createwCreateWindow: xxxCreateWindow fail \n");
             return NULL;
         }

        // Pintamos simples, mas a tipagem será overlapped.
        __w->type = WT_OVERLAPPED;   
        goto draw_frame;
    }


    // #todo
    // It does not exist by itself. It needs a parent window.
    
    //edit box
    if ( type == WT_EDITBOX )
    {
        //if ( (void*) pWindow == NULL ){ return NULL; }
        
        // Podemos usar o esquema padrão de cores ...
        __w = (void *) xxxCreateWindow ( 
                           WT_SIMPLE, status, view, 
                           (char *) windowname, 
                           x, y, width, height, 
                           (struct gws_window_d *) pWindow, 
                           desktopid, clientcolor, color ); 

         if ( (void *) __w == NULL ){
             gwssrv_debug_print ("createwCreateWindow: xxxCreateWindow fail \n");
             return NULL;
         }

        //pintamos simples, mas a tipagem será  overlapped
        __w->type = WT_EDITBOX;   
        goto draw_frame;
    }


    // #todo
    // It does not exist by itself. It needs a parent window.

    //button
    if ( type == WT_BUTTON )
    {
        gwssrv_debug_print ("[DEBUG]: createwCreateWindow WT_BUTTON\n");
      
        //if ( (void*) pWindow == NULL ){ return NULL; }
        
        // Podemos usar o esquema padrão de cores ...
        __w = (void *) xxxCreateWindow ( 
                           WT_BUTTON, status, view, 
                           (char *) windowname, 
                           x, y, width, height, 
                           (struct gws_window_d *) pWindow, 
                           desktopid, clientcolor, color ); 

         if ( (void *) __w == NULL ){
             gwssrv_debug_print ("createwCreateWindow: xxxCreateWindow fail \n");
             return NULL;
         }

        //pintamos simples, mas a tipagem será  overlapped
        __w->type = WT_BUTTON;   
        goto draw_frame;
    }


// ============================
// Types with no frame!

    if ( type == WT_SIMPLE )
    {
        __w = (void *) xxxCreateWindow ( 
                           WT_SIMPLE, status, view, 
                           (char *) windowname, 
                           x, y, width, height, 
                           (struct gws_window_d *) pWindow, 
                           desktopid, clientcolor, color );  

         if ( (void *) __w == NULL ){
             gwssrv_debug_print ("createwCreateWindow: xxxCreateWindow fail \n");
             return NULL;
         }

        __w->type = WT_SIMPLE;
        return (void *) __w;
    }

//type_fail:

    gwssrv_debug_print ("createwCreateWindow: [FAIL] type \n");
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
    // See: window.c

    if ( type == WT_OVERLAPPED || 
         type == WT_EDITBOX || 
         type == WT_BUTTON )
    {
        
        // #todo
        // if __w is valid.
        
        // #todo
        // __w->useStandardFrame

        // See: wm.c

        if ( (void*) __w != NULL )
        {
            wmDrawFrame ( 
                (struct gws_window_d *) pWindow,  //parent.
                (struct gws_window_d *) __w,      //bg do botão em relação à sua parent. 
                0, 0, width, height, 
                1 );  //style
        }
    }


//draw_menubar:
// ...

//draw_toolbar:
// ...

//draw_h_scrollbar:
// ...

//draw_v_scrollbar:
// ...



//
// z order for overlapped.
//


    // Quando criamos uma overlapped, ela deve vicar no topo da pilha.
    if ( type == WT_OVERLAPPED )
    {
        // #bugbug
        // refaz a lista de zorder...
        // somente com overlalled
        //reset_zorder();
        
        // #bugbug isso nao eh bom.
        //invalidate parent, if present
        //invalidate_window(__w->parent);

        // coloca a nova janela no topo.
        __w->zIndex = ZORDER_TOP;
        zList[ZORDER_TOP] = (unsigned long) __w;
    }


// ===============

//
// level
//
    
    // #test
    
    if ( (void*) pWindow != NULL )
    {
        __w->level = (pWindow->level + 1);
    }

    if ( (void*) pWindow == NULL )
    {
        __w->level = 0;
    }

    // ===============


//done:
    return (void *) __w;
}


// Create root window
// Called by gwsInit in gws.c.

struct gws_window_d *createwCreateRootWindow(void)
{
    struct gws_window_d *w;


    unsigned long left   = 0;
    unsigned long top    = 0;
    unsigned long width  = __device_width;
    unsigned long height = __device_height;


    debug_print("createwCreateRootWindow:\n");

    // (root window)
    // #bugbug: EStamos usado device info sem checar.
    
    w = (struct gws_window_d *) createwCreateWindow ( 
                                    WT_SIMPLE,  1, 1, "RootWindow",  
                                    left, top, width, height,
                                    NULL, 0, COLOR_PINK, COLOR_PINK );
    if ( (void*) w == NULL)
    {
        debug_print("createwCreateRootWindow: [FAIL] w\n");
        printf     ("createwCreateRootWindow: [FAIL] w\n");
        exit(1);
    }

    w->used  = TRUE;
    w->magic = 1234;

        // Register.
        // WindowId = gwsRegisterWindow (__root_window);

        // if (WindowId<0){
        // gwssrv_debug_print ("create_background: Couldn't register window\n");
        //return;
        //}


    // Root window
    gwsDefineInitialRootWindow (w);


    debug_print("createwCreateRootWindow: done\n");

    return (struct gws_window_d *) w;
}



//
// End.
//



