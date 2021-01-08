

#ifndef __GWSSRV_GLOBALS_H
#define __GWSSRV_GLOBALS_H  1


// =======================================
// Protocol request constants
// Os primeiros sao os mesmos encontrados na api.
 
//window (1-19)  
#define GWS_Create   1
#define GWS_Destroy  2
#define GWS_Move     3
#define GWS_Size     4
#define GWS_Resize   5
//#define GWS_Open     6
#define GWS_Close      7
#define GWS_Paint      8
#define GWS_SetFocus   9
#define GWS_KillFocus    10
#define GWS_Activate     11 
#define GWS_ShowWindow   12
#define GWS_SetCursor    13 
#define GWS_Hide         14
#define GWS_Maximize     15
#define GWS_Restore      16
#define GWS_ShowDefault  17

// keyboard (20-29)
#define GWS_KeyDown    20
#define GWS_KeyUp      21
#define GWS_SysKeyDown 22
#define GWS_SysKeyUp   23

// mouse (30 - 39)
// tem uma lista de eventos de mouse em events.h
#define GWS_MouseKeyDown     30 
#define GWS_MouseKeyUp       31
#define GWS_MouseButtonDown  30
#define GWS_MouseButtonUp    31
#define GWS_MouseMove        32
#define GWS_MouseOver        33
#define GWS_MouseWheel       34
#define GWS_MousePressed     35
#define GWS_MouseReleased    36
#define GWS_MouseClicked     37
#define GWS_MouseEntered     38
#define GWS_MouseExited      39
//#define GWS_MouseMoveByOffset
//#define GWS_MouseMoveToElement

//outros (40 - ...)
#define GWS_Command  40
#define GWS_Cut      41
#define GWS_Copy     42
#define GWS_Paste    43
#define GWS_Clear    44
#define GWS_Undo     45
#define GWS_Insert   46
#define GWS_Process  47
#define GWS_Thread   48
//Quando um comando é enviado para o console. ele será atendido pelo
//módulo /sm no procedimento de janela do sistema.
//Todas as mensagens de console serão atencidas pelo procedimento de janela 
//nessa mensagem.
#define GWS_ConsoleCommand  49
#define GWS_ConsoleShutDown 50
#define GWS_ConsoleReboot   51
#define GWS_Developer       52

//UM TIMER SE ESGOTOU,
#define GWS_Timer  53 
//...


// =======================================
// Protocol request constants
//
// #todo:
// Create a consistent interface.
// See: xxxHandleNextClientRequest() and gwsProcedure on aurora/server/main.c 
// See: 
// All the standar messages, just like MSG_SYSKEYUP ...
// There are some old messages below 369.
#define GWS_GetInputMessage        369
#define GWS_Hello                 1000
#define GWS_CreateWindow          1001
#define GWS_BackbufferPutPixel    1002
#define GWS_DrawHorizontalLine    1003
#define GWS_DrawChar              1004
#define GWS_DrawText              1005
#define GWS_RefreshWindow         1006
#define GWS_RedrawWindow          1007
#define GWS_ResizeWindow          1008
#define GWS_ChangeWindowPosition  1009
#define GWS_BackbufferPutPixel2   2000
#define GWS_Disconnect            2010
#define GWS_RefreshScreen         2020
#define GWS_RefreshRectangle      2021
//#define GWS_GetSendEvent          2030  // send event #
#define GWS_GetNextEvent          2031
#define GWS_GrPlot0               2040
#define GWS_GrCubeZ               2041
#define GWS_GrRectangle           2042
#define GWS_AsyncCommand          2222
#define GWS_DrainInput            8080
// ...



// =====================================================




// ## button support ##
#define GWS_COLOR_BUTTONFACE            0x00F0F0F0
#define GWS_COLOR_BUTTONFACE2           0x00E0E0E0
#define GWS_COLOR_BUTTONFACE3           0x00D0D0D0
#define GWS_COLOR_BUTTONHIGHLIGHT       0x00FFFFFF
#define GWS_COLOR_BUTTONHIGHLIGHT2      0x00404040
#define GWS_COLOR_BUTTONHIGHLIGHT3      0x00008080
#define GWS_COLOR_BUTTONHIGHLIGHTTEXT   COLOR_WHITE
#define GWS_COLOR_BUTTONHIGHLIGHTTEXT2  COLOR_WHITE 
#define GWS_COLOR_BUTTONSHADOW          0x00A0A0A0
#define GWS_COLOR_BUTTONSHADOW2         0x00303030 
#define GWS_COLOR_BUTTONSHADOW3         0x00202020 
#define GWS_COLOR_BUTTONTEXT            COLOR_TEXT


// #importante
// usaremos essas definições para configurarmos
// os dois esquemas básicos, humility e pride.
// Apenas poucas cores devem ser definidas aqui. Elas
// servirão de base para outros conjuntos. Devem ser definidas
// com números.

#define HUMILITY_COLOR_BACKGROUND                 0x00008080 
#define HUMILITY_COLOR_WINDOW                     0x00FFFFFF 
#define HUMILITY_COLOR_WINDOW_BACKGROUND          0x00202020 
#define HUMILITY_COLOR_ACTIVE_WINDOW_BORDER       0x00404040 
#define HUMILITY_COLOR_INACTIVE_WINDOW_BORDER     0x00606060 
#define HUMILITY_COLOR_ACTIVE_WINDOW_TITLEBAR     0x00404040 
#define HUMILITY_COLOR_INACTIVE_WINDOW_TITLEBAR   0x00606060 
#define HUMILITY_COLOR_MENUBAR                    0x00808080 
#define HUMILITY_COLOR_SCROLLBAR                  0x00FFF5EE 
#define HUMILITY_COLOR_STATUSBAR                  0x0083FCFF 
#define HUMILITY_COLOR_MESSAGEBOX                 0x00404040 
#define HUMILITY_COLOR_SYSTEMFONT                 0x00000000 
#define HUMILITY_COLOR_TERMINALFONT               0x00FFFFFF 
//...

#define PRIDE_COLOR_BACKGROUND                    0x00008080 
#define PRIDE_COLOR_WINDOW                        0x00FFFFFF 
#define PRIDE_COLOR_WINDOW_BACKGROUND             0x00202020 
#define PRIDE_COLOR_ACTIVE_WINDOW_BORDER          0x0080FFFF
#define PRIDE_COLOR_INACTIVE_WINDOW_BORDER        0x0080FFFF
#define PRIDE_COLOR_ACTIVE_WINDOW_TITLEBAR        0x0080FFFF
#define PRIDE_COLOR_INACTIVE_WINDOW_TITLEBAR      0x0080FFFF
#define PRIDE_COLOR_MENUBAR                       0x00808080 
#define PRIDE_COLOR_SCROLLBAR                     0x00FFF5EE 
#define PRIDE_COLOR_STATUSBAR                     0x002EB982
#define PRIDE_COLOR_MESSAGEBOX                    0x00808080  
#define PRIDE_COLOR_SYSTEMFONT                    0x00000000  
#define PRIDE_COLOR_TERMINALFONT                  0x00FFFFFF  
//...



/*
 *****************************************************
 * ColorSchemeType:
 *     Enumerando os esquemas de cores. 
 *     Esses são esquemas default.
 *     Poderemos carregar outros e cada esquema terá 
 * seu índice.
 *     Esses serão sempre os primeiros.    
 */

typedef enum {

    ColorSchemeNull,      // 0 - Null.
    ColorSchemeHumility,  // 1 - Gray stuff.
    ColorSchemePride,     // 2 - Colorful.
    ColorSchemeUser,      // 3 - Personalizado. Criado ou carregado.
    // ...

}ColorSchemeType;



/*
 ******************************************************
 * ColorSchemeIndex:
 *     csi - color scheme index. 
 *     Enumerando os elementos gráficos
 *     O esquema de cores se aplica ao servidor 
 * de recursos gráficos. GWS.
 */
typedef enum {

    csiNull,                    //0
    csiDesktop,                 //1 área de trabalho.

    //window
    csiWindow,                  //2
    csiWindowBackground,        //3
    csiActiveWindowBorder,      //4
    csiInactiveWindowBorder,    //5

    //bar
    csiActiveWindowTitleBar,    //6
    csiInactiveWindowTitleBar,  //7
    csiMenuBar,                 //8
    csiScrollBar,               //9
    csiStatusBar,               //10

    csiMessageBox,              //11
    csiSystemFontColor,         //12 BLACK
    csiTerminalFontColor,       //13 WHITE
	//...

	//@todo: focus,
	
    //@todo: Window 'shadow' (black??)

}ColorSchemeIndex;  




/*
 ***************************************************
 * color_scheme_d:
 *     Estrutura para esquema de cores. 
 *     O esquema de cores se aplica ao servidor 
 * de recursos gráficos. GWS.
 */ 

struct gws_color_scheme_d
{
    //@todo: É preciso ainda definir esse tipo de objeto.
	//definir em gdef.h
	//object_type_t objectType;
	//object_class_t objectClass;	

    int id;

    int used;
    int magic;

	//marcador de estilo de design para 
	//o padrão de cores.
	//cada estilo pode invocar por si um padrão de cores.
	//ou o padrão de cores por si pode representar um estilo.
    int style;

    char *name; 

	//cada índice desse array representará um elemento gráfico,
	//os valores no array são cores correspondentes aos elementos gráficos 
	//representados por índices.
    unsigned long elements[32];

	//...
};

struct gws_color_scheme_d* GWSCurrentColorScheme;
struct gws_color_scheme_d* GWSHumilityColorScheme; // Simples.
struct gws_color_scheme_d* GWSPrideColorScheme;    // Colorido.


//
// == variables ==============================================
//


// #ordem
// hadware, software

unsigned long  ____BACKBUFFER_VA;
unsigned long  ____FRONTBUFFER_VA;

// Saving
unsigned long SavedBootBlock;
unsigned long SavedLFB;   // #bugbug? VA ?
unsigned long SavedX;
unsigned long SavedY;
unsigned long SavedBPP; 

// helper.
unsigned long __device_width;
unsigned long __device_height;
unsigned long __device_bpp;

// refresh rate of the whole screen.
static unsigned long fps;

// refresh rate for all dirty objects.
static unsigned long frames_count;

// Vamos usar ou nao.
int use_vsync;
#define VSYNC_YES  1
#define VSYNC_NO   0



// Pointers to screens.
#define MAX_SCREENS    4
#define SCREEN_FRONTBUFFER     0
#define SCREEN_BACKBUFFER      1
//#define SCREEN_BACKBUFFER2   2
//#define SCREEN_BACKBUFFER3   3
static unsigned long screens[MAX_SCREENS];




/*
struct vid_d
{
    unsigned long width;
    unsigned long height;
    unsigned long bpp;
    
    unsigned long frontbuffer;  // lfb
    unsigned long backbuffer;   // screen[0]
};
struct vid_d vidConfig;
*/



//
// == Prototypes ===================================================
//

void 
gwssrv_initialize_color_schemes (int selected_type);

int gwssrv_select_color_scheme (int type);


#endif   



