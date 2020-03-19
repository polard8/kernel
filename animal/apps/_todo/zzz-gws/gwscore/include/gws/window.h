
// window status
#define WINDOW_STATUS_ACTIVE       1
#define WINDOW_STATUS_INACTIVE     0

//window relationship status. (seu status em relação as outras janelas.)
//Obs: tem uma estreita ligação com o status da thread que está trabalahndo com ela 
//e com a prioridade dessa thread e do processo que a possui.
// *** RELAÇÃO IMPLICA PRIORIDADE ***
#define WINDOW_REALATIONSHIPSTATUS_FOREGROUND     1000
#define WINDOW_REALATIONSHIPSTATUS_BACKGROUND     2000
#define WINDOW_REALATIONSHIPSTATUS_OWNED          3000  //Possuida por outra janela.
#define WINDOW_REALATIONSHIPSTATUS_ZAXIS_TOP      4000
#define WINDOW_REALATIONSHIPSTATUS_ZAXIS_BOTTOM   6000
//...


/*
 ***********************************************
 * Messages.
 * mensagens para procedimentos de janelas e 
 * para diálogos dentro do gws.
 * Obs: Isso refere-se principalmente à janelas.
 */

 
 //??tipos de mensagens ??
#define MSG_NULL          0 
#define SIGNAL_NULL       0 
#define STREAM_MSG_NULL   0 
#define BUFFER_MSG_NULL   0 
#define CAT_MSG_NULL      0  

 
//window (1-19)  
#define MSG_CREATE        1
#define MSG_DESTROY       2
#define MSG_MOVE          3 
#define MSG_SIZE          4
#define MSG_RESIZE        5
//#define MSG_OPEN        6
#define MSG_CLOSE         7
#define MSG_PAINT         8
#define MSG_SETFOCUS      9
#define MSG_KILLFOCUS     10
#define MSG_ACTIVATE      11
#define MSG_SHOWWINDOW    12 
#define MSG_SETCURSOR     13
#define MSG_HIDE          14
#define MSG_MAXIMIZE      15
#define MSG_RESTORE       16
#define MSG_SHOWDEFAULT   17

//keyboard (20-29)
#define MSG_KEYDOWN       20
#define MSG_KEYUP         21
#define MSG_SYSKEYDOWN    22
#define MSG_SYSKEYUP      23

//mouse (30 - 39)
//tem uma lista de eventos de mouse em events.h
#define MSG_MOUSEKEYDOWN  30
#define MSG_MOUSEKEYUP    31
#define MSG_MOUSEBUTTONDOWN	30
#define MSG_MOUSEBUTTONUP	31 
#define MSG_MOUSEMOVE	    32
#define MSG_MOUSEOVER	    33
#define MSG_MOUSEWHEEL	    34
#define MSG_MOUSEPRESSED	  35
#define MSG_MOUSERELEASED	  36
#define MSG_MOUSECLICKED	  37
#define MSG_MOUSEENTERED	  38    //?? capturou ??
#define MSG_MOUSEEXITED	       39   //?? descapturou ??
//#define MSG_MOUSEMOVEBYOFFSET
//#define MSG_MOUSEMOVETOELEMENT

//outros (40 - ...)
#define MSG_COMMAND       40
#define MSG_CUT           41
#define MSG_COPY          42
#define MSG_PASTE         43
#define MSG_CLEAR         44 
#define MSG_UNDO          45
#define MSG_INSERT        46
#define MSG_RUN_PROCESS   47
#define MSG_RUN_THREAD    48
//Quando um comando é enviado para o console. ele será atendido pelo
//módulo /sm no procedimento de janela do sistema.
//Todas as mensagens de console serão atencidas pelo procedimento de janela 
//nessa mensagem.
#define MSG_CONSOLE_COMMAND 49
#define MSG_CONSOLE_SHUTDOWN 50
#define MSG_CONSOLE_REBOOT   51
#define MSG_DEVELOPER 52


//UM TIMER SE ESGOTOU,
//#todo>: incluir isso na api.
#define MSG_TIMER 53   
//...







/*
struct gws_rect_d
{
    unsigned long x;
	unsigned long y;
	unsigned long width;
	unsigned long height; 
		
	unsigned long left;
	unsigned long top;
	unsigned long right;
	unsigned long bottom;
		
	unsigned long bg_color;
	
	//?? ...
};
*/

//#todo
// A estrtutura deve ficar em user mode.
// Criaremos janelas gerenciadas por esse servidor.

/*
struct gws_window_d 
{
    //#todo
	//...
    int dummy;
	
	//...
	
	
	struct gws_window_d *next;
};
*/

//
// ================================================================
//



struct gui_d 
{
	//...
	
    struct window_d *screen;
    struct window_d *main;
};
struct gui_d *gui;



//
// variáveis 
//

int active_window;



void 
rectBackbufferDrawRectangle ( unsigned long x, 
                              unsigned long y, 
                              unsigned long width, 
                              unsigned long height, 
                              unsigned long color );
                   




// #importante
// >>> Criaremos a barra de títulos depois que a janela estiver pronta.
            
int createwDrawTitleBar ( struct window_d *window,
                unsigned long x,
                unsigned long y,
                unsigned long width,
                unsigned long height,
                int style,
                char *string );




int createwDrawFrame ( struct window_d *window,
                unsigned long x,
                unsigned long y,
                unsigned long width,
                unsigned long height,
                int style );          //estilo do frame.


void *createwCreateWindow2 ( unsigned long type, 
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
                     unsigned long color ) ;





// Essa será a função que atenderá a interrupção
//esse é o serviço de criação da janela.
// talvez ampliaremos o número de argumentos
                      
void *createwCreateWindow ( unsigned long type, 
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
                     unsigned long color ); 



void 
dtextDrawString ( unsigned long x,
              unsigned long y,
              unsigned long color,
              unsigned char *string );
              
void 
dtextDrawText ( struct window_d *window,
            unsigned long x,
            unsigned long y,
            unsigned long color,
            unsigned char *string );

            
              
              
