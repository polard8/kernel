/*
 * File: gramado\gui\window.h 
 *
 * Descrição:
 *    Funções e parâmetros para o kernel controlar a interface gráfica 
 * e as operações com vídeo.
 *
 *     WINDOW -> DESKTOP -> WINDOW STATION -> USER SECTION.
 *
 * Histórico:
 *     Versão: 1.0, 2014 - Esse arquivo foi criado por Fred Nora.
 *     Versão: 1.0, 2015 - Revisão. 
 *     Versão: 1.0, 2016 - Revisão.
 */

 
//Endereços das fonts presentes no CMOS BIOS. 
#define BIOSFONT8X8 0x000FFA6E    //8x8
//#define BIOSFONT8X8 0x000FFA6E
//#define BIOSFONT8X8 0x000FFA6E
//#define BIOSFONT8X8 0x000FFA6E
//...
 
 
 
 
//Definindo as dimensões padrão. 
//#define DEFAULT_SCREEN_WIDTH  800
//#define DEFAULT_SCREEN_HEIGHT 600
 
// Número máximo de janelas.
#define WINDOW_COUNT_MAX 256
#define MAX_WINDOWS WINDOW_COUNT_MAX 


#define WINDOW_LOCKED 1
#define WINDOW_UNLOCKED 0


//#define PATH_MAX         128


/*
 * Messages.
 */
 
//window (0-19) 
#define MSG_NULL          0  
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
#define MSG_MOUSEKEYDOWN  30
#define MSG_MOUSEKEYUP    31
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
//...

 
 
/*
 * Window Type - Tipos de janela.
 */
#define WT_NULL          0 
#define WT_SIMPLE        1
#define WT_EDITBOX       2 // igual simples, mais uma bordinha preta.
#define WT_OVERLAPPED    3 //sobreposta(completa)(barra de titulo + borda +client area)
#define WT_POPUP         4 //um tipo especial de sobreposta,  //usada em dialog ou message box. (com ou sem barra de titulo ou borda)					   
//#define WT_BUTTON_DOWN   5 // cancelado
//#define WT_BUTTON_UP     6 // cancelado



// window style
#define WINDOW_STYLE_FLOATING 1000 
#define WINDOW_STYLE_DOCKING  2000  //(atracada em algum canto.)
//...


// window status
#define WINDOW_STATUS_ACTIVE       1
#define WINDOW_STATUS_INACTIVE     0
//...

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




//apresentação.
#define VIEW_NULL      0
#define VIEW_FULL      1000  // * Full screen.
#define VIEW_MAXIMIZED 1001  
#define VIEW_MINIMIZED 1002
#define VIEW_NORMAL    1003  //Normal (restaurada)
//...


//botoes
#define BN_CLICKED  200
#define BN_DOWN     1
#define BN_UP       2
#define BN_SELECTED 3

 
//@todo: what ??? 
//?? um handle para o desktop. 
#define HWND_DESKTOP 0


 
 
/*
 * Dimensões: 
 * 
 * Parametro principal para dimensões de janela.
 * todos os outros tomam esse como refêrencia.
 * depende do modo que estiver usando.
 *
 * vesa 112:
 *
 * 640x480x24bit - (3 bytes por pixel)
 * 
 * @todo, o kernel usará dimensões 640x480 no modo gráfico.
 */   
#define KERNEL_COL_MAX 640 
#define KERNEL_LIN_MAX 480 

//#define SCREEN_WIDTH 640 
//#define SCREEN_HEIGHT 480 

/*
 * video mode stuffs
 */
#define VIDEO_MODE_TEXT     1
#define VIDEO_MODE_GRAPHIC  2


/*
 * char 
 */
#define CHAR_WIDTH   8
#define CHAR_HEIGHT  8


#define	BAR_STEPS   46
#define LINE KERNEL_COL_MAX 


//dimensões - provisorio
#define COL_MAX   KERNEL_COL_MAX 
#define LINHA_MAX KERNEL_LIN_MAX  






/*
 EGA   VGA
0x0   0x00  Black
0x1   0x01  Blue
0x2   0x02  Green
0x3   0x03  Cyan
0x4   0x04  Red
0x5   0x05  Magenta
0x6   0x14  Brown
0x7   0x07  Light Gray
0x8   0x38  Gray
0x9   0x39  Light Blue
0xA   0x3A  Light Green
0xB   0x3B  Light Cyan
0xC   0x3C  Light Red
0xD   0x3D  Light Magenta
0xE   0x3E  Light Yellow
0xF   0x3F  White
*/


/*
 * Colors.
 */
 


 /*
                         COLOR_BACKGROUND,
                         COLOR_APPWORKSPACE,
                         COLOR_WINDOW,
                         COLOR_WINDOWTEXT,
                         COLOR_MENU,
                         COLOR_MENUTEXT,
                         COLOR_ACTIVECAPTION,
                         COLOR_INACTIVECAPTION,
                         COLOR_CAPTIONTEXT,
                         COLOR_ACTIVEBORDER,
                         COLOR_INACTIVEBORDER,
                         COLOR_WINDOWFRAME,
                         COLOR_SCROLLBAR,
                         COLOR_BTNFACE,
                         COLOR_BTNSHADOW,
                         COLOR_BTNTEXT,
                         COLOR_GRAYTEXT,
                         COLOR_HIGHLIGHT,
                         COLOR_HIGHLIGHTTEXT,
                         COLOR_INACTIVECAPTIONTEXT,
                         COLOR_BTNHIGHLIGHT
*/

/*
  BACKGROUND,
  MDIWINDOW,
  CLIENT,
  CLIENTTEXT,
  MENUBAR,
  MENUTEXT,
  MYCAPTION,
  CAPTION2,
  CAPTIONTEXT,
  CAPTION2TEXT,
  BORDER,
  BORDER2,
  WINDOWFRAME,
  SCROLLBARS,
  BUTTONFACE,
  BUTTONSHADOW,
  BUTTONTEXT,
  BUTTONHIGHLIGHT,
  GRAYTEXT,
  HIGHLIGHT,
  HIGHLIGHTTEXT,
 */


//enumerando os esquemas de cores. 
// temos 2 tipos de esquema de cores.
typedef enum {
	ColorSchemeNull,      // Null.
	ColorSchemeHumility,  // Gray stuff.
	ColorSchemePride,     // Colorful.
	//...
}ColorSchemeType;	


//definindo índices para elementos gráficos.
//esse índice retornará a cor... ou quem sabe,
//dependendo da estrutura, retorne outra característica.
#define GUICOLOR_NULL  0
#define GUICOLOR_DESKTOP  1
#define GUICOLOR_WINDOW  2
#define GUICOLOR_WINDOW_BACKGROUND  3
#define GUICOLOR_ACTIVE_WINDOW_BORDER  4
#define GUICOLOR_INACTIVE_WINDOW_BORDER  5
#define GUICOLOR_ACTIVE_WINDOW_TITLEBAR  6
#define GUICOLOR_INACTIVE_WINDOW_TITLEBAR  7
#define GUICOLOR_MENUBAR  8
#define GUICOLOR_SCROLLBAR  9 
#define GUICOLOR_STATUSBAR  10
#define GUICOLOR_MESSAGEBOX  11
//...


//enumerando os elementos gráficos
//color scheme index.
typedef enum {
	
	csiNull,                    //0
	csiDesktop,                 //1 área de trabalho.

	//window
	csiWindow,                  //2
	csiWindowBackground,        //3
	csiActiveWindowBorder,	    //4
	csiInactiveWindowBorder,    //5
	                    
	//bar
	csiActiveWindowTitleBar,    //6	
	csiInactiveWindowTitleBar,  //7
	csiMenuBar,                 //8
	csiScrollBar,               //9
	csiStatusBar,	            //10
	
	csiMessageBox,              //11
	//...
	
	//@todo: Window 'shadow' (black??)
}ColorSchemeIndex;  
 
 
 
//estrutura para esquema de cores. 
typedef struct color_scheme_d* color_scheme_t;
struct color_scheme_d
{
    //@todo: É preciso ainda definir esse tipo de objeto.
	//definir em gdef.h
	object_type_t objectType;
	object_class_t objectClass;	
	
	int used;
	int magic;
	
	char *name;  	
	
	//cada índice desse array representará um elemento gráfico,
	//os valores no array são cores correspondentes aos elementos gráficos 
	//representados por índices.
	unsigned long elements[32];
	
	//...
};
color_scheme_t CurrentColorScheme;
color_scheme_t HumilityColorScheme;
color_scheme_t PrideColorScheme;
//... 
 
 
 
//cinza para pintar janela
//a janela tem camadas que vai do mais escuro para o mais claro.
#define xCOLOR_BLACK 0x00000000  //preto
#define xCOLOR_GRAY1 0x20202000  //cinza mais escuro
#define xCOLOR_GRAY2 0x40404000  //cinza
#define xCOLOR_GRAY3 0x60606000  //cinza
#define xCOLOR_GRAY4 0x80808000  //cinza
#define xCOLOR_GRAY5 0xa0a0a000  //cinza
#define xCOLOR_GRAY6 0xc0c0c000  //cinza
#define xCOLOR_GRAY7 0xe0e0e000  //cinza mais clarinho
#define xCOLOR_WHITE 0xffffff00  //branco 


//WIN23
//TRÊS TIPOS DE CINZA.
#define COLOR_LITBUTTON  0xE0E0E000
#define COLOR_LTGRAY     0xC0C0C000
#define COLOR_GRAY       0x80808000

//CORES BÁSICAS.
#define rgbBlack   0x00000000
#define rgbBlue    0x0000FF00
#define rgbCyan    0x00FFFF00
#define rgbGreen   0x00FF0000
#define rgbMagenta 0xFF00FF00
#define rgbRed     0xFF000000
#define rgbYellow  0xFFFF0000
#define rgbWhite   0xFFFFFF00



//windows2k system colors
#define COLOR_TEST_0  0x8080FF00  // COLOR_BACKGROUND(verde claro) ??
#define COLOR_TEST_1  0x80FFFF00  // COLOR_APPWORKSPACE, MDIWINDOW 
#define COLOR_TEST_2  0x80FF8000  // COLOR_WINDOW, CLIENT
#define COLOR_TEST_3  0x80FF0000  // COLOR_WINDOWTEXT, CLIENTTEXT 
#define COLOR_TEST_4  0xFFFF8000  // COLOR_MENU, MENUBAR
#define COLOR_TEST_5  0xFF800000  // COLOR_MENUTEXT (laranjado+-)
#define COLOR_TEST_6  0xC080FF00  // COLOR_ACTIVECAPTION, MYCAPTION
#define COLOR_TEST_7  0xFF80FF00  // COLOR_INACTIVECAPTION, CAPTION2
#define COLOR_TEST_8  0x0000FF00  // COLOR_CAPTIONTEXT, CAPTIONTEXT(azul)highlight
#define COLOR_TEST_9  0x00FFFF00  // COLOR_ACTIVEBORDER, BORDER
#define COLOR_TEST_10 0x00FF8000  // COLOR_INACTIVEBORDER, BORDER2
#define COLOR_TEST_11 0x40FF0000  // COLOR_WINDOWFRAME
#define COLOR_TEST_12 0xFFFF0000  // COLOR_SCROLLBAR (amarelo)
#define COLOR_TEST_13 0xC0800000  // COLOR_BTNFACE
#define COLOR_TEST_14 0xC0808000  // COLOR_BTNSHADOW (vinho)
#define COLOR_TEST_15 0xFF00FF00  // COLOR_BTNTEXT (rosa)
#define COLOR_TEST_16 0x40408000  // COLOR_HIGHLIGHT ~ COLOR_GRAYTEXT (azul escuro)
#define COLOR_TEST_17 0x4080FF00  // COLOR_HIGHLIGHT
#define COLOR_TEST_18 0x00FF0000  // COLOR_HIGHLIGHTTEXT (verde)
#define COLOR_TEST_19 0x80800000  // COLOR_INACTIVECAPTIONTEXT
#define COLOR_TEST_20 0x80400000  // COLOR_BTNHIGHLIGHT
#define COLOR_TEST_21 0xFF808000 
#define COLOR_TEST_22 0x40008000 
#define COLOR_TEST_23 0x8000FF00
#define COLOR_TEST_24 0x00008000  //COLOR_HIGHLIGHT ~ hot track (azul)
#define COLOR_TEST_25 0x0080FF00 
#define COLOR_TEST_26 0x00800000 
#define COLOR_TEST_27 0x40800000 
#define COLOR_TEST_28 0xFF000000  //red
#define COLOR_TEST_29 0xA0000000 
#define COLOR_TEST_30 0x80008000 
#define COLOR_TEST_31 0xFF008000
#define COLOR_TEST_32 0x00004000
#define COLOR_TEST_33 0x00408000 
#define COLOR_TEST_34 0x00400000 
#define COLOR_TEST_35 0x40400000 
#define COLOR_TEST_36 0x80000000 
#define COLOR_TEST_37 0x40000000 
#define COLOR_TEST_38 0x40004000
#define COLOR_TEST_39 0x80004000
#define COLOR_TEST_40 0x00000000 //COLOR_BTNSHADOW ~ preto text
#define COLOR_TEST_41 0x00808000  //vrde escuro
#define COLOR_TEST_42 0x40808000  //vrde escuro
#define COLOR_TEST_43 0x80808000  //COLOR_APPWORKSPACE (cinza)
#define COLOR_TEST_44 0x80804000 
#define COLOR_TEST_45 0xC0C0C000  //silver
#define COLOR_TEST_46 0x40004000
 
 
//outros teste
#define COLOR_TEST_47 0x3366FF00  //azul claro
    

/*
 * Cores usadas nessa sistema.
 */

#define COLOR_BLACK               0x00000000
#define COLOR_WHITE               0xFFFFFF00 
#define COLOR_RED                 0xFF000000 
#define COLOR_GREEN               0x00FF0000
#define COLOR_BLUE                0x0000FF00
#define COLOR_DARKRED             0x8B000000
#define COLOR_DARKGREEN           0x00640000
#define COLOR_DARKBLUE            0x00008B00
//#define COLOR_GRAY                0x80808000
#define COLOR_GREY                0xAFAFAF00
#define COLOR_LIGHTGRAY           0xD3D3D300
#define COLOR_LIGHTGREEN          0x90EE9000
#define COLOR_LIGHTBLUE           0xADD8E600
#define COLOR_SILVER              0xC0C0C000

//window colors
#define COLOR_ACTIVEBORDER        0xB4B4B400
#define COLOR_ACTIVECAPTION       0x99B4D100
#define COLOR_ACTIVECAPTIONTEXT   0x00000000
#define COLOR_APPWORKSPACE        COLOR_SILVER 
// A cor padrão para o Bg é azul quase escuro,
// o azul escuro é usado em seleção de item.
#define COLOR_BACKGROUND          0x00808000  
#define COLOR_BORDER              COLOR_SILVER 
#define COLOR_BUTTONFACE          0xF0F0F000
#define COLOR_BUTTONHIGHLIGHT     0xFFFFFF00
#define COLOR_BUTTONSHADOW        0xA0A0A000  //COLOR_BLACK
#define COLOR_BUTTONTEXT          COLOR_WINDOWTEXT
#define COLOR_CONTROL             0xF0F0F000
#define COLOR_CONTROLDARK         0xA0A0A000
#define COLOR_CONTROLDARKDARK     0x69696900
#define COLOR_CONTROLLIGHT        0xE3E3E300
#define COLOR_CONTROLLIGHTLIGHT   0xFFFFFF00
#define COLOR_CONTROLTEXT         0x00000000
#define COLOR_DESKTOP             0x00000000
#define COLOR_FOCUS_TOPBAR        0x7FFF0000
#define COLOR_GRAYTEXT            0x80808000
#define COLOR_HIGHLIGHT           0x3399FF00
#define COLOR_HIGHLIGHTTEXT       0xFFFFFF00
#define COLOR_INACTIVEBORDER      0xF4F7FC00
#define COLOR_INACTIVECAPTION     0xBFCDDB00
#define COLOR_INACTIVECAPTIONTEXT 0x434E5400
#define COLOR_INFO                0xFFFFE100
#define COLOR_INFOTEXT            0x00000000

#define COLOR_MENU                  COLOR_GRAY
#define COLOR_MENUTEXT              COLOR_BLACK
#define COLOR_MENUITEM              COLOR_WHITE
#define COLOR_MENUITEMTEXT          COLOR_BLACK
#define COLOR_MENUITEM_SELECTED     COLOR_BLUE
#define COLOR_MENUITEMTEXT_SELECTED COLOR_WHITE
#define COLOR_MENUBAR               COLOR_GRAY
#define COLOR_MENUHIGHLIGHT         0x3399FF00

#define COLOR_NAVIGATIONBAR       COLOR_BLACK
#define COLOR_NAVIGATIONBAR_TEXT  COLOR_WHITE
#define COLOR_STATUSBAR           COLOR_WINDOW
#define COLOR_TASKBAR             COLOR_WINDOW
#define COLOR_TASKBAR_TEXT        COLOR_TEXT
#define COLOR_TEXT                0x00000000
#define COLOR_TITLEBAR            COLOR_BLUE
#define COLOR_TITLEBAR_TEXT       COLOR_WHITE
#define COLOR_TOPBAR              0x83F52C00
#define COLOR_TOPBAR_TEXT         0x397D0200
#define COLOR_WINDOW              0xFFFFFF00
#define COLOR_WINDOWFRAME         COLOR_GRAY
//(debug: Pink para contraste com quaquer cor de janela)
#define COLOR_WINDOWTEXT          COLOR_PINK //COLOR_BLACK 
#define COLOR_WORKSPACE           0x0000FF00 //area de trabalho

//Tipos de azul
#define COLOR_BLUE1 0x067AB500
#define COLOR_BLUE2CYAN   0x1BA1E200
#define COLOR_BLUE3COBALT 0x0050EF00
#define COLOR_BLUE4INDIGO 0x6A00FF00

/*
 *  Lista de cores de 32 bit usando Alpha.
 */

#define COLOR_ALICEBLUE           0xF0F8FFFF
#define COLOR_ANTIQUEWHITE        0xFAEBD7FF
#define COLOR_AQUA                0x00FFFFFF
#define COLOR_AQUAMARINE          0x7FFFD4FF
#define COLOR_AZURE               0xF0FFFFFF
#define COLOR_BEIGE               0xF5F5DCFF
#define COLOR_BISQUE              0xFFE4C4FF
#define COLOR_BLANCHEDALMOND      0xFFEBCDFF
#define COLOR_BLUEVIOLET          0x8A2BE2FF
#define COLOR_BROWN               0xA52A2AFF
#define COLOR_BURLYWOOD           0xDEB887FF
#define COLOR_CADETBLUE           0x5F9EA0FF
#define COLOR_CHARTREUSE          0x7FFF00FF
#define COLOR_CHOCOLATE           0xD2691EFF
#define COLOR_CORAL               0xFF7F50FF
#define COLOR_CORNFLOWERBLUE      0x6495EDFF
#define COLOR_CORNSILK            0xFFF8DCFF
#define COLOR_CRIMSON             0xDC143CFF
#define COLOR_CYAN                0x00FFFFFF
#define COLOR_DARKCYAN            0x008B8BFF
#define COLOR_DARKGOLDENROD       0xB8860BFF
#define COLOR_DARKGRAY            0xA9A9A9FF
#define COLOR_DARKKHAKI           0xBDB76BFF
#define COLOR_DARKMAGENTA         0x8B008BFF
#define COLOR_DARKOLIVEGREEN      0x556B2FFF
#define COLOR_DARKORANGE          0xFF8C00FF
#define COLOR_DARKORCHID          0x9932CCFF
#define COLOR_DARKSALMON          0xE9967AFF
#define COLOR_DARKSEAGREEN        0x8FBC8BFF
#define COLOR_DARKSLATEBLUE       0x483D8BFF
#define COLOR_DARKSLATEGRAY       0x2F4F4FFF
#define COLOR_DARKTURQUOISE       0x00CED1FF
#define COLOR_DARKVIOLET          0x9400D3FF
#define COLOR_DEEPPINK            0xFF1493FF
#define COLOR_DEEPSKYBLUE         0x00BFFFFF
#define COLOR_DIMGRAY             0x696969FF
#define COLOR_DODGERBLUE          0x1E90FFFF
#define COLOR_FIREBRICK           0xB22222FF
#define COLOR_FLORALWHITE         0xFFFAF0FF
#define COLOR_FORESTGREEN         0x228B22FF
#define COLOR_FUCHSIA             0xFF00FFFF
#define COLOR_GAINSBORO           0xDCDCDCFF
#define COLOR_GHOSTWHITE          0xF8F8FFFF
#define COLOR_GOLD                0xFFD700FF
#define COLOR_GOLDENROD           0xDAA520FF
#define COLOR_GRADIENTACTIVECAPTION   0xB9D1EAFF
#define COLOR_GRADIENTINACTIVECAPTION 0xD7E4F2FF
#define COLOR_GREENYELLOW         0xADFF2FFF
#define COLOR_HONEYDEW            0xF0FFF0FF
#define COLOR_HOTPINK             0xFF69B4FF
#define COLOR_HOTTRACK            0x0066CCFF
#define COLOR_INDIANRED           0xCD5C5CFF
#define COLOR_INDIGO              0x4B0082FF
#define COLOR_IVORY               0xFFFFF0FF
#define COLOR_KHAKI               0xF0E68CFF
#define COLOR_LAVENDER            0xE6E6FAFF
#define COLOR_LAVENDERBLUSH       0xFFF0F5FF
#define COLOR_LAWNGREEN           0x7CFC00FF
#define COLOR_LEMONCHIFFON        0xFFFACDFF
#define COLOR_LIGHTCORAL          0xF08080FF
#define COLOR_LIGHTCYAN           0xE0FFFFFF
#define COLOR_LIGHTGOLDENRODYELLOW 0xFAFAD2FF
#define COLOR_LIGHTPINK           0xFFB6C1FF
#define COLOR_LIGHTSALMON         0xFFA07AFF
#define COLOR_LIGHTSEAGREEN       0x20B2AAFF
#define COLOR_LIGHTSKYBLUE        0x87CEFAFF
#define COLOR_LIGHTSLATEGRAY      0x778899FF
#define COLOR_LIGHTSTEELBLUE      0xB0C4DEFF
#define COLOR_LIGHTYELLOW         0xFFFFE0FF
#define COLOR_LIME                0x00FF00FF
#define COLOR_LIMEGREEN           0x32CD32FF
#define COLOR_LINEN               0xFAF0E6FF
#define COLOR_MAGENTA             0xFF00FFFF
#define COLOR_MAROON              0x800000FF
#define COLOR_MEDIUMAQUAMARINE    0x66CDAAFF
#define COLOR_MEDIUMBLUE          0x0000CDFF
#define COLOR_MEDIUMORCHID        0xBA55D3FF
#define COLOR_MEDIUMPURPLE        0x9370DBFF
#define COLOR_MEDIUMSEAGREEN      0x3CB371FF
#define COLOR_MEDIUMSLATEBLUE     0x7B68EEFF
#define COLOR_MEDIUMSPRINGGREEN   0x00FA9AFF
#define COLOR_MEDIUMTURQUOISE     0x48D1CCFF
#define COLOR_MEDIUMVIOLETRED     0xC71585FF
#define COLOR_MIDNIGHTBLUE        0x191970FF
#define COLOR_MINTCREAM           0xF5FFFAFF
#define COLOR_MISTYROSE           0xFFE4E1FF
#define COLOR_MOCCASIN            0xFFE4B5FF
#define COLOR_NAVAJOWHITE         0xFFDEADFF
#define COLOR_NAVY                0x000080FF
#define COLOR_OLDLACE             0xFDF5E6FF
#define COLOR_OLIVE               0x808000FF
#define COLOR_OLIVEDRAB           0x6B8E23FF
#define COLOR_ORANGE              0xFFA500FF
#define COLOR_ORANGERED           0xFF4500FF
#define COLOR_ORCHID              0xDA70D6FF
#define COLOR_PALEGOLDENROD       0xEEE8AAFF
#define COLOR_PALEGREEN           0x98FB98FF
#define COLOR_PALETURQUOISE       0xAFEEEEFF
#define COLOR_PALEVIOLETRED       0xDB7093FF
#define COLOR_PAPAYAWHIP          0xFFEFD5FF
#define COLOR_PEACHPUFF           0xFFDAB9FF
#define COLOR_PERU                0xCD853FFF
#define COLOR_PINK                0xFFC0CBFF
#define COLOR_PLUM                0xDDA0DDFF
#define COLOR_POWDERBLUE          0xB0E0E6FF
#define COLOR_PURPLE              0x800080FF
#define COLOR_ROSYBROWN           0xBC8F8FFF
#define COLOR_ROYALBLUE           0x4169E1FF
#define COLOR_SADDLEBROWN         0x8B4513FF
#define COLOR_SALMON              0xFA8072FF
#define COLOR_SANDYBROWN          0xF4A460FF
#define COLOR_SCROLLBAR           0xC8C8C8FF
#define COLOR_SEAGREEN            0x2E8B57FF
#define COLOR_SEASHELL            0xFFF5EEFF
#define COLOR_SIENNA              0xA0522DFF
#define COLOR_SKYBLUE             0x87CEEBFF
#define COLOR_SLATEBLUE           0x6A5ACDFF
#define COLOR_SLATEGRAY           0x708090FF
#define COLOR_SNOW                0xFFFAFAFF
#define COLOR_SPRINGGREEN         0x00FF7FFF
#define COLOR_STEELBLUE           0x4682B4FF
#define COLOR_TAN                 0xD2B48CFF
#define COLOR_TEAL                0x008080FF
#define COLOR_THISTLE             0xD8BFD8FF
#define COLOR_TOMATO              0xFF6347FF
#define COLOR_TRANSPARENT         0xFFFFFF00
#define COLOR_TURQUOISE           0x40E0D0FF
#define COLOR_VIOLET              0xEE82EEFF
#define COLOR_WHEAT               0xF5DEB3FF
#define COLOR_WHITESMOKE          0xF5F5F5FF
#define COLOR_YELLOW              0xFFFF00FF
#define COLOR_YELLOWGREEN         0x9ACD32FF
#define STEALTH_ORANGE            0xFF880000
#define STEALTH_OLIVE             0x66660000
#define STEALTH_GREEN             0x33DD1100
#define STEALTH_PINK              0xFF22EE00
#define STEALTH_BLUE              0x0077BB00
 
 
/*
 * (w) Colors, futuristic GUI. (Dark blu and Black)
 */ 
//#define COLOR_DARKBLUE   0x00008B00 
//#define COLOR_BLACK      0x00000000 
 
 
 
#define COLOR_KERNEL_BACKGROUND COLOR_BLUE     
 
/*
 * Padrão para janela de Aplicativo.  
 */

#define APP_X 100
#define APP_Y 100
#define APP_LARGURA  640
#define APP_ALTURA   480
#define APP_COLOR_BG            0x00000000 //@todo        
#define APP_COLOR_BARRA_TITULO  0x00000000 //@todo
#define APP_COLOR_BORDA         0x00000000 //@todo       
#define APP_COLOR_TEXT          0x0001fe00 //@todo   


//barra de status
#define BARRA_DE_STATUS_X        0
#define BARRA_DE_STATUS_Y        KERNEL_LIN_MAX
#define BARRA_DE_STATUS_LARGURA  KERNEL_COL_MAX
#define BARRA_DE_STATUS_ALTURA   40


//client area
#define CLIENT_X_START  0
#define CLIENT_X_END    KERNEL_COL_MAX
#define CLIENT_Y_START  17
#define CLIENT_Y_END    ( KERNEL_LIN_MAX-16 )


//MESSAGE BOX - UTIL
#define MB_X              100
#define MB_Y              100
#define MB_LARGURA        320
#define MB_ALTURA         200
#define MB_TITULO_ALTURA  24
#define MB_STRING_X       (100 + (320/3))  
#define MB_STRING_Y       (100 + (200/3))


//barra de titulos BOX - UTIL
#define TB_X           0
#define TB_Y           0
#define TB_LARGURA     KERNEL_COL_MAX
#define TB_ALTURA      16
#define TB_STRING_X    16+4  
#define TB_STRING_Y    5




//@todo: Inglês
// barra de tarefas
#define BARRA_DE_TAREFAS_X         0
#define BARRA_DE_TAREFAS_Y         KERNEL_LIN_MAX
#define BARRA_DE_TAREFAS_LARGURA   KERNEL_COL_MAX
#define BARRA_DE_TAREFAS_ALTURA    20

//area das tarefas na barra de tarefas
#define AREA_DE_TAREFAS_X      MENU_INICIAR_LARGURA
#define AREA_DE_TAREFAS_Y      KERNEL_LIN_MAX
  
#define AREA_DE_TAREFAS_LARGURA  (BARRA_DE_TAREFAS_LARGURA - MENU_INICIAR_LARGURA)
#define AREA_DE_TAREFAS_ALTURA    20

//desktop
#define DESKTOP_X        0
#define DESKTOP_Y        0
#define DESKTOP_LARGURA  KERNEL_COL_MAX
#define DESKTOP_ALTURA   KERNEL_LIN_MAX

//menu
#define MENU_X         0
#define MENU_Y         KERNEL_LIN_MAX
#define MENU_LARGURA   200
#define MENU_ALTURA    200
#define MENU_INICIAR_X 0
#define MENU_INICIAR_Y (600 - MENU_ALTURA - 50 ) //50=altura da taskbar
#define MENU_INICIAR_LARGURA  MENU_LARGURA
#define MENU_INICIAR_ALTURA   MENU_ALTURA
#define menu_size  (MENU_ALTURA * 8)


/*
 * Constants para a task bar.
 */
 
#define TASKBUTTONS_BASE 40
#define CLOCK_BASE  (KERNEL_COL_MAX-40)


//=========================================
//    ****    KERNEL WINDOW    ****
//Definições padronizadas para janelas do kernel usadas para 
//fornecer informações sobre o sistema.
// (Retângulo grande no topo da tela.)
#define KERNEL_WINDOW_DEFAULT_LEFT 0
#define KERNEL_WINDOW_DEFAULT_TOP  0
#define KERNEL_WINDOW_DEFAULT_WIDTH  800
#define KERNEL_WINDOW_DEFAULT_HEIGHT (600/4) 
#define KERNEL_WINDOW_DEFAULT_CLIENTCOLOR  xCOLOR_GRAY2
#define KERNEL_WINDOW_DEFAULT_BGCOLOR      xCOLOR_GRAY1
//...



//
// ******** ESSA VARIÁVEL BLOQUEIA O FOCO NA JANELA DO DESENVOLVEDOR   *****
//
int _lockfocus;


// ESSA SERÁ USADA DEPOIS QUANDO A INTERFACE GRÁFICA ESTIVER MAIS ROBUSTA;
int gFocusBlocked;   


/*
 * Window.
 */
 
unsigned long g_mainwindow_width;
unsigned long g_mainwindow_height;
unsigned long g_navigationbar_width;
unsigned long g_navigationbar_height;


/*
 * Status de ambientes gráficos.
 *
 */
int logonStatus;              //Logon status.
int logoffStatus;             //Logoff status.
int userenvironmentStatus;    //User environment status.

int guiStatus;        //Status da Interface gráfica do usuário.
//outros...

int g_guiMinimal; //Light or Full gui.


/*
 * Contagem de janelas.
 */
int windows_count;  

/*
 * A janela com o foco de entrada.
 *
 */     
int window_with_focus;   

//Id da janela ativa.
int active_window;


// LFB - address for kernel graphic mode
unsigned long g_kernel_lfb; 


//video mode
unsigned long g_current_vm; //video memory
unsigned long g_current_video_mode; //video mode
 

//font
unsigned long gfontAddress;      //fonte atual.
unsigned long g8x8fontAddress;   //8×8, 80×25,CGA, EGA
unsigned long g8x14fontAddress;  //8x14,80×25,EGA
unsigned long g8x16fontAddress;  //??
unsigned long g9x14fontAddress;  //9x14,80×25,MDA, Hercules
unsigned long g9x16fontAddress;  //9x16,80×25,VGA
//...

//char
int gcharWidth;
int gcharHeight;

//color  
unsigned long g_system_color;
unsigned long g_char_attrib;
 
 
unsigned long  STATUS_X;
unsigned long  STATUS_Y;

unsigned long  EDITBOX_X;
unsigned long  EDITBOX_Y;
unsigned long  EDITBOX_LARGURA;  //todo: EDITBOX_WIDTH 
unsigned long  EDITBOX_ALTURA;   //todo: EDITBOX_HEIGHT. 
unsigned long  EDITBOX_BG_COLOR;
unsigned long  EDITBOX_TEXT_COLOR;


//estrutura para botões.
typedef struct button_d button_t;
struct button_d
{
	object_type_t objectType;
	object_class_t objectClass;	
	
    int used;
    int magic;

    int selected;	
    unsigned long border1; //color
    unsigned long border2; //color	
	
    struct window_d *window; //A qual janela o botão pertence.
    unsigned char *string; //label
    unsigned long type; //tipo de botão.
    unsigned long x;    //deslocamento em relação à margem da janela
    unsigned long y;  //deslocamento em relação à margem da janela
    unsigned long width; 
    unsigned long height; 
    unsigned long color;
	
	//More ??
				  
    struct button_d *Next;  //proximo botão dentro da mesma janela.??
};
//Botões na janela principal.				  
button_t *mainButton1;  
button_t *mainButton2;  
button_t *mainButton3;  
//...

/*
 * taskbar_d: 
 * Estrutura para a task bar.
 * Essa estrutura é marcador oficial das dimensões da barra de tarefas.    
 * Essa é a barra de tarefas tradicional, aquela que normalmente fica 
 * em baixo e contêm ícones dos programas abertos.
 * Porém essa barra na verdade é uma janela e pode ser redimensionada 
 * ou movida.
 * O kernel terá umagom registro disso para salvar as dimensões da
 * área de trabalho, que é o tamanho da tela menos o tamanho da barra.
 */
typedef struct taskbar_d taskbar_t;
struct taskbar_d
{
	//object stuff??
	
    unsigned long Left;	
    unsigned long Top;
    unsigned long Width;
    unsigned long Height;
}; 
taskbar_t TaskBar;    //*Importante: Sem Ponteiro.


/*
 * menubar_d: 
 *     Estrutura para a menu bar.
 *
 *     Essa estrutura é marcador oficial das dimensões
 *     da barra de menu.    
 *
 *     Essa é a barra de menu tradicional,
 *     que aparece no topo da tela e oferece
 *     um conjunto de menus para manipular
 *     o porcesso com a janela ativa.
 */
typedef struct menubar_d menubar_t;
struct menubar_d
{
	//object stuff??
	
    unsigned long Left;	
    unsigned long Top;
    unsigned long Width;
    unsigned long Height;
}; 
menubar_t MenuBar;    //*Importante: Sem Ponteiro.

 

/*
 * window_procedure_d:
 *     Estrutura para procedimento de janela.
 *
 */ 
typedef struct window_procedure_d window_procedure_t;
struct window_procedure_d
{

	object_type_t objectType;
	object_class_t objectClass;	
	
    //4 argumentos do procedimento
	struct window_d *window;  //à qual janela pertence o procedimento.
    int msg;	
	unsigned long long1;
	unsigned long long2;
	
	//Parametros extras.
	
	struct d_process *process; //à qual processo pertence o procedimento.
	struct d_thread  *thread;  //à qual thread pertence o procedimento.
	
	int msgStatus;
	int active_window;      //Id da janela ativa.
	int window_with_focus;  //Id da janela com o foco de entrada.

	//...
};
window_procedure_t *CurrentProcedure;
window_procedure_t *WindowProcedure;
//... 
 


/* Message structure */
/*
typedef struct msg_d msg_t;
struct msg_d
{
	struct window_d *window;
	int 	        message;
	unsigned long	long1;
	unsigned long	lomg2;
	unsigned long	time;
};
msg_t *Msg;
msg_t *ProcedureMsg;
*/



/*
 * rect_d:
 *     Estrutura para gerenciamento de retângulos.
 *     Um retângulo pertence à uma janela.
 *
 */
typedef struct rect_d rect_t;
struct rect_d 
{
	object_type_t objectType;
	object_class_t objectClass;

    int used;	
	int magic;
	int flag;
	
	//int validated;
	//int focus;
	
    unsigned long x;
    unsigned long y;
    unsigned long cx;
    unsigned long cy;

	
    unsigned long width;
    unsigned long height;

	unsigned long left;
	unsigned long top;	
	unsigned long right;
	unsigned long bottom;
	
	unsigned long color_bg;
	
	//Essa é  ajanela à qual o retângulo pertence.
	struct window_d *window;
};
//rect_t *ShellRect;    //retangulo da área de cliente do shell atual.
rect_t *rect;
rect_t *rectClientArea;   //Retângulo da área de cliente da janela ativa.
//rect_t *RC;
//rect_t *Rect;
//...


typedef struct tagRGBA RGBA_t;
struct tagRGBA
{
	object_type_t objectType;
	object_class_t objectClass;	
	
   char red;
   char green;
   char blue;
   char alpha;
};
RGBA_t *RGBA;


/*
 * Windows structures.
 */ 

 
/*
 * window_d:
 *     Window - nível 1. 
 *     Estrutura para janelas.
 */
typedef struct window_d window_t;
struct window_d
{	
    //
    // Identificadores.
    //
    
	object_type_t objectType;
	object_class_t objectClass;		
	
    unsigned long id;              //Window Id. 
	char *name;                    //Window name.
	
	
	//Segurança.
	int used;
	int magic;
	
	
	//
	// Window Class support.
	//
	
	//@todo: Criar essa estrutura.
	//struct window_class_d *windowClass;
	
	unsigned long type;                    //tipo ... (editbox, normal, ...)  style???
	
	/*
     Número da aba do navegador que a janela está.
     Se for 0, então a janela está no desktop.
    */
	int tab;
    
	//window style:
	//WINDOW_STYLE_FLOATING (flutuante) 
	//WINDOW_STYLE_DOCKING   (atracada em algum canto)
	int style;   
	
	
	//procedure support. (poderia ser um argumento ou elemento da classe.)
	unsigned long procedure;               //procedimento da janela
    struct window_procedure_d *wProcedure; //procedure struct
	//unsigned long Icon;
	//unsigned long Cursor;    //@todo: Criar cursorx e cursory.
	//unsigned long CursorX;
	//unsigned long CursorY;
	//unsigned long Background;
	//int instance; //???	
	
	
    //
	// Características dessa janela..
	//

	//*full screen mode = modo tela cheia. 
	//( utiliza a resolução atual do dispositivo )
	// deve ser a janela em primeiro plano. acima de todas as outras.
	//mas podemos configurar para que uma jenela esteja em full screen 
	//enquanto outra janela é a janela ativa e ainda outra tenha o foco de entrada.
	//uma janela em modo full screen pode conter barras de rolagem.
	//*embedded mode = dentro de uma janela ou de um navegador. 

    //int active;    //FAST FLAG. Essa será a flag de ativa ou não. (decidido isso)
    //int focus;     //Se tem o foco de entrada ou não.
    int view;      //Estado: (Full,Maximized,Minimized...)	
    //unsigned long status;                //ATIVA OU NÃO.
    unsigned long relationship_status;   //seu estatus de relacionamento com outras janelas.
	
	//ordem na pilha de janelas do eixo z.
	//A janela mais ao topo é a janela foreground.
	int z_axis_order; 

	//dimensões e margens.
    unsigned long x;           //deslocamento x
    unsigned long y;           //deslocamento y 
    unsigned long width;       //largura
    unsigned long height;      //altura    
    unsigned long left;        //margem esquerda 
    unsigned long top;         //margem superior
    unsigned long right;       //margem direita  
    unsigned long bottom;      //margem inferior       
    
    unsigned long color_bg;    //cor  
    unsigned long clientrect_color_bg;    //cor do retãngulo da área do cliente.
    //...definir mais cores.


	//?? Se mudar para Rect pode deletar alguns elementos acima
	//como x, y, width ...
	struct rect_d *rcWindow;
	
	//Lista encadeada dos retângulos que pertencem a essa janela.
	//Quando uma janela for deletada, devemos desalocar toda a memória 
	//uada por esses recursos.
	struct rect_d *rectList;

	// Bars support.
	// Cada tipo de janela tem seus itens específicos.
	// Esses são os status dos ítens. Se eles estão presentes ou não.
	
	int backgroundUsed;
	int shadowUsed;
	int titlebarUsed;
    int menubarUsed; 
	int toolbarUsed;
	int clientAreaUsed;
	int statusbarUsed;
	int scrollbarUsed;
	int minimizebuttonUsed;
	int maxmizebuttonUsed;
	int closebuttonUsed;
	//Continua.
	
	//Msg support.
	//Argumentos para o procedimento de janela.
	struct window_d *msg_window;    //arg1.
	int msg;                    //arg2.
	unsigned long long1;        //arg3.
	unsigned long long2;        //arg4.	
	
	int msgAlert;  //um alerta de que exite uma mensagem para essa janela.
	
	//struct msg_d *msg;
	
	int sendOffset;
	int receiveOffset;
	
	//Filas para uma janela receber mensagens.
	//São os quatro argumentos de um procedimento de janela padrão.
	
	unsigned long hwndList[32];
	unsigned long msgList[32];
	unsigned long long1List[32];
	unsigned long long2List[32];
	
	//unsigned long scancodeList[32];
	
	
	//
	// Buffers support.
	//

	// Um ponteiro para um array de ponteiros de estruturas de linhas
	// Explicando: Nesse endereço teremos um array. Cada ponteiro armazenado
	// nesse array é um ponteiro para uma estrutura de linha.
	//Obs: @todo: Todos esses elementos podem formar uma estrutura e ficaria aqui 
	//apenas um ponteiro para ela.
	void *LineArray;
	int LineArrayIndexTotal;    //Total de índices presentes nesse array.
    int LineArrayIndexMax;      //Número máximo de índices permitidos no array de linhas.
    int LineArrayTopLineIndex;  //Indice para a linha que ficará no topo da página.
    int LineArrayPointerX;      //Em qual linha o ponteiro está. 	
	int LineArrayPointerY;      //em qual coluna o ponteiro está.
	//...
	
	
	// Buffer.
	// DedicatedBuffer
	// DedicatedBuffer --> LFB.
	// Endereço de memória onde a janela foi pintada.
	// Obs: Toda janela deve ter seu próprio buffer de pintura para poder 
	// passar a janela direto de seu próprio buffer para o LFB, sem passar 
	// pelo Backbuffer.
	//void *buffer;        //Qual buffer dedicado a janela usa.
	void *DedicatedBuffer;        //Qual buffer dedicado a janela usa.
	void *BackBuffer;    //Qual backbuffer a janela usa.
	void *FrontBuffer;   //Qual frontbuffer a janela usa. (LFB).
    //... 	

	
	//
	// Parent support
	//
	
	struct window_d *parent;	  //Parent window.	
    unsigned long parentid;       //(Número da janela mãe).
	
	//
	// Child support.
	//
	
	//Lista encadeada de janelas filhas.
	struct window_d *childListHead;
    int childCount;    //Tamanho da lista.
	
	//
	// Client window support.
	//
    
	//Client window.
    //é a janela propriamente dita, excluindo a moldura e a barra de rolagem.
	struct window_d *client_window;   	
	struct rect_d *rcClient;     	
	
	
	//
	// Desktop support.
	// A que desktop a janela pertence??
	//
	

	struct desktop_d *desktop;
	int desktop_id;  


    //
    //  Process support.
    //  A que processo a janela pertence??
    //
    struct process_d *process;	
	
	//
	// Menus support.
	//
	
	//?? Qual janela o menu usará.
	struct window_d *menu_window;   //Menu Window.
	
	struct menu_d *sysMenu;         //menu de sistema.(control menu)
	struct menu_d *barMenu;         //menu da barra de menu.
	struct menu_d *defaultMenu;     //menu da janela (*importante)
	//...
	
    // Flag par indicar se a janela é um item de menu.	
	//ou um botão.
	int isMenu;   //deletar??
	int isButton; //deletar??
	//int isIcon; //deletar??
	//...
	
	int selected;     //seleção  de item de menu.
    const char *text; //@todo usar unsigned char.

    //
    // Ações.
    //

    int draw;     	
    int redraw;
    int show;   //se precisa ou não mostrar a janela.	
    // Continua ...
	
	
	//Continua...
	
 	
	//
	// Text Cursor support.
	//

	//Estrutura de cursor para a janela.
    struct cursor_d	*cursor;
	
	//Posição do cursor para texto dentro da janela.
	//Obs: Deve ser multiplo da altura e largura do caractere.
	//Obs: Para cada janela o cursor pode estar em uma posição diferente.
	//@todo: Deletar isso e começar usar a estrutura.
	unsigned long cursor_x;
	unsigned long cursor_y;
	//unsigned long bgcolor;		// Background color.
	//unsigned long fgcolor;		// Foreground color. 
	
	struct button_d *current_button;  //Botão atual.      
    struct button_d *buttonList;      //Lista encadeada de botões em uma janela.
	
	//
	// Mouse cursor support ???
	//
	
	//
	// Abaixo ficam os elementos referenciados com menor frequência.
	//
	
	// Trava. Se travada, não pode mudar nada.
	// Enables or disables mouse and keyboard input to the specified window 
	// or control.
	int locked;    
	
	//linked list. ( a linked list da janela)
	struct linkedlist_d *linkedlist;	
	
	// Navegation.
	struct window_d *prev;     
	struct window_d *next;     //Next window.	
};
window_t *CurrentWindow;    //Janela atual
window_t *ActiveWindow;     //Janela atual.
window_t *WindowWithFocus;  //Janela com o foco de entrada.   
//window_t *ShellWindow;    //Shell Window
//window_t *ControlMenuWindow;    //O control menu usado para fechar janelas.
//window_t *Window;
//window_t *ConsoleWindow;
//...

// Lista encadeada de janelas.
window_t *window_Conductor2;
window_t *window_Conductor;
window_t *window_rootConductor;


 /*
 * Lista de janelas.
 * @todo: Na verdade poderia ser alocação dinâmica
 * pois o numero de janelas é muito grande. isso deixaria o kernel grande demais.
 */ 
unsigned long windowList[WINDOW_COUNT_MAX];

//
// Browser support. (SHELL.BIN)
//

#define TABWINDOW_COUNT_MAX 12  //F1 à F12.

/* Essa é a aba onde os lementos devem ser criados ...
quando um aplicativo chamar serviços do kernel para criar elementos na aba.*/
int current_tab;

window_t *BROWSERWINDOW;    //Ponteiro para a janela do navegador.
window_t *TABWINDOW;        //ponteiro para a janela da tab atual..

//janela full screen que será usada pelo navegador...
//essa janela deve ter as dimensões da tela...
//Obs: já existe uma janela com essas características ... que é a janela 
//gui->screen ... lenbrando que não queremos que a janela gui->screen tenha 
//os valores de sua estrutura alterados ... pois refletem as características do dispositivo.
//Importante: Estragar essa estrutura pode causar muitos problemas.
window_t *FULLSCREEN_TABWINDOW;   

/*
 estrutura para tabs do navegador do kernel.

 */
typedef struct browser_tab_d browser_tab_t;
struct browser_tab_d
{
	object_type_t objectType;
	object_class_t objectClass;	
	
    int used;
    int magic;
	
	int id;   //Identificação da aba.
	
	char *name;
	
	/* 
	  *Importante:
	       Tipo de aba. Temos três tipos basicamente:
		   + 1 = Aba de console. para aplicativos de console.
		   + 2 = Aba de janela. para aplicativos de janela.
		   + 3 = Aba de navegador. para páginas da internet.
		   
	 */
	int type;
	
	/* talvez teremos 2 modos, maximizado e full screen*/
	int view; 
	
	/*
	 Qual é a janela que constitui a aba. 
	 Isso nos dá muitas informações sobre a aba.
	 Toda a sua métrica ...
	 */
	struct window_d* window;
	
	/*
      Importante:	
	      Dedicated buffer:
		  ??
	 */
	/*void *buffer;*/

    	

    struct browser_tab_d *next;    	
};
//browser_tab_t *CurrentTab;
//browser_tab_t *BrowserTab;
//...

unsigned long browsertabList[TABWINDOW_COUNT_MAX]; //lista de ponteiros para estruturas de tabs.
/*
 * zorderList[] support.
 *     Sobreposição de janelas.    
 *     ?? Precisamos reorganizar a lista ??
 *     ?? seria melhor uma lista encadeada ??
 *     ??e quando fecharem uma janela no meio da lista ??
 *
 *  >> Quando criamos uma janela ela é incluída no primeiro lugar vago da lista.
 *  >> quando deletamos uma janela, apenas excluimos ela da lista, não precisamos reorganizar.
 *  >> uma janelas minimizada é excluida dessa lista, é zerada z_axis_order na sua estrutura.
 *  >> repintaremos começando do zero.
 */

 #define ZORDER_COUNT_MAX  128  //??PROVISÓRIO   
unsigned long zorderList[ZORDER_COUNT_MAX];

int zorderCounter;         //contador de janelas incluidas nessa lista.



//
// Backbuffer support. (espelho da memória de video)
//

typedef struct backbufferinfo_d backbufferinfo_t;
struct backbufferinfo_d
{
	//@todo: object support
	
	int used;
	int magic;
	
    unsigned long start;
    unsigned long end;
    unsigned long size;
    //...

    //@todo:
	// ?? O que nos podemos ter aqui ??	
	// terminal., window, line disciplice, cursor ...
	//input buffer? z-order ??
};
backbufferinfo_t *BackBufferInfo;




//
// Frontbuffer support. (memória de vídeo)
//

typedef struct frontbufferinfo_d frontbufferinfo_t;
struct frontbufferinfo_d
{
	//@todo: object support
	
	int used;
	int magic;
	
    unsigned long start;
    unsigned long end;
    unsigned long size;
	
	unsigned long width;
    unsigned long height;
	unsigned long bpp;
	//
	
    //@todo:
	// ?? O que nos podemos ter aqui ??	
	// terminal., window, line disciplice, cursor ...	
};
frontbufferinfo_t *FrontBufferInfo;


/*
 * gui:
 *     Nível 0 - gui.
 *
 * Obs: Foi incluído aqui os ponteiros para as janelas principais usadas nos 
 * principais recursos gráficos, como control menu do desktop por exemplo.
 *
 * Histórico: 
 * 2015 - Created.
 * 2016 - incluíndo novos elementos.
 * ...
 */
typedef struct gui_d gui_t;
struct gui_d
{
    /*
	 * Header. ??
	 */   

	//Se a gui está ou não inicializada.
	int initialised;		  
	
	//Procedimento da janela ativa.
	unsigned long procedure;  
	
	/*
	 *    ****    BUFFERS    ****
	 *
	 * Ponteiros para os principais buffers usados pelo sistema.
	 * 
	 */
	
	/*
	 * LFB:
	 * O endereço do início da memória de vídeo do cartão de memória.
	 * Obs: Quantos desses ponteiros precisamos dentro da memória de
	 * vídeo? E se tivermos várias placas de memória de vídeo, seria
	 * um lfb para cada placa?
	 * Esse valor foi configurado pelo BIOS pelo metodo VESA.
	 */
	 unsigned long lfb;
	 
	/*
	 * Backbuffers.
	 *     O Backbuffer pe o buffer para colocar a imagem de pano de fundo.
	 * Ele será o buffer dedicado da janela principal gui->main.
	 * 
	 */
	unsigned long backbuffer; //Paranóia.
	
    void* backbuffer1; 
	void* backbuffer2; 
	void* backbuffer3;
	//...
	
	/*
	 * Default dedicated buffers.
	 *     Esses ponteiros podem ser usados para aloca
	 * memória para buffer dedicado antes mesmo de se criar a estrutura
	 * da janela.
	 * Obs: Toda janela tem que ter um buffer dedicado, onde ela será pintada.
	 * Depois de pintada ela pertencerá a uma lista de janelas que serão
	 * enviadas para o LFB seguindo a ordem da lista.
	 *
	 */
	void* defaultWindowDedicatedBuffer1;
	void* defaultWindowDedicatedBuffer2;
	void* defaultWindowDedicatedBuffer3;
    //...	
	
	/*
	 * Flag para repintar todas as janelas.
	 * @todo: #bugbug, Isso parece estranho. Cada janela
	 * está pintada em seu buffer dedicado e fica por conta de
	 * cada janela decidir se repinta ou não apenas ela.
	 */
	int redraw;	

	
	/*
	 * Flag para enviar do backbuffer para a memória de video.
	 * Seguindo uma lista linkada, copiaremos o conteúdo do buffer
	 * dedicado de cada janela da lista no LFB. Primeiro é Backbuffer
	 * que é o buffer da janela principal, que funcionará como
	 * Head da lista.
	 */
	int refresh;			       
    //struct window_d * redrawWindowListHead;	
	
	
	//status das janelas usadas pelo sistema.
	int screenStatus;
	int backgroundStatus;
	int logoStatus;
	int mainStatus;
	int navigationbarStatus;	
	int menuStatus;
	int taskbarStatus;
	int statusbarStatus;	
	int infoboxStatus;
	int messageboxStatus;
	int debugStatus;
	int gridStatus;
	
	
	/*
	 *    ****    Windows    ****
	 *
	 * Obs: Ponteiros para as janelas principais usadas na interfáce
	 * gráfica. Essas janelas não dependem dos processos e sim os
	 * processos dependem delas. Os processos do sistema poderão recriar
	 * essas janelas e registrar seus ponteiros aqui. Por exemplo, o control
	 * menu pode sofrer alterações e depois registrar o ponteiro aqui.
	 * Outro exemplo é o control menu da janela ativa, toda vez que
	 * trocar a janela ativa, deve-se registrar o ponteiro do control menu
	 * da janela aqui, para fácil acesso.
	 *
	 * Os ponteiros aqui serão organizados em grupos:
	 * ==============================================
	 * Grupo 0: Screen, Background, Logo, Desktop, Taskbar.
	 * Grupo 1: Main (Full Screen), Status Bar. 
	 * Grupo 2: Grid. (grid de ícones flutuantes)
	 * Grupo 3: Control menu.(Control menu da janel atual).
	 * Grupo 4: Info Box, ToolTip.
	 * Grupo 5: MessageBox e DialogBox.
	 * Grupo 6: Outras.
	 */
	
	
	
	//
	// Grupo 0: Screen, Background, Logo, Desktop, Taskbar.
	//
	
	
    /*
	 * Screen: 
	 *     A tela. Tem as dimensões do monitor usado.
	 */   
    struct window_d *screen; 


	//
	// A única janela em primeiro plano e com o foco de entrada. 
	// Será usada pelo desenvolvedor durante a construção dos 
	// elementos gráficos, até que o sistema gráfico fique mais robusto
	// e permita ficar trocando a janela com o foco de entrada.
	// Isso é para evitar confusão de output nesa fase.
	//
    struct window_d *DEVELOPERSCREEN;    
	
    /*
	 * Background: 
	 *     Uma janela popup com as dimensões da tela.
	 */   
	struct window_d *background; 

	/*
	 * Logo:
	 *     A imagem de pano de fundo.
	 */
    struct window_d *logo;
	
	
	
	/*
	 * Desktop:
	 *    A Área de trabalho.    
	 *    Uma área de tamanho variável,
	 *    dependendo da presensa ou não da barra de tarefas.
	 *    É a área onde ficam os ícones e as janelas dos
	 *    programas.
	 */
    struct window_d *desktop; 

	/*
	 * Task Bar: (top bar) 
	 *     A barra de tarefas.
	 */
	struct window_d *taskbar;


    //
    // Grupo 1: Main (Full Screen), Status Bar. 
    //

	/*
	 * Main:
	 * A área de trabalho.
	 */
    struct window_d *main;

	/*
	 * Status Bar:  
	 *     A barra de status.
	 *     Usada em qualquer condição.
	 *     Fica posicionada dentro de uma janela mãe.
	 */
	struct window_d *statusbar;
	
 
	//
	// Grupo 2: Grid. 
	//
	
	
	/*
	 *Grid:
	 *   (Área para colocar o grid de ícones).
	 *    Área dinâmica dentro da Área de trabalho.
	 *    Essa área de grid pode ser reposicionada
	 *    de acordo com o layout escolhido.
	 */
	struct window_d *grid;
	
	
	
	//
	// Grupo 3: Control menu.
	//
	
    /*
	 * Menu:  
	 *     Ponteiro para a estrutura do control menu atual.    
	 *     Isso depende da janela ativa e da janela com o foco de entrada.
	 *     Esse será o ponteiro para o control menu que deverá ser aberto.
	 *     Varia conforme muda a janela com o foco de entrada.
	 */	
	struct window_d *menu; 

	
	//
	// Grupo 4: Info Box, ToolTip.
	//
	
	/*
	 * Infobox:
	 *     Janela usada para o sistema enviar mensagens de informações.   
     * seria notification window ??	 
	 */
	struct window_d *infobox; 
    
	
	//
	// Pequena janela de notificações, que desaparece depois de um tempo..
	//
	//struct window_d *notification;   	

	
	/*
	 * ToolTip:
	 *     Janelinha que aparece quando repousa o mouse sobre elemento gráfico.
	 *      POPUP. A janela se adapta ao tamanho da string.
	 */
	struct window_d *tooltip;  
	
	//
	// Grupo 5: MessageBox e DialogBox.
	//

	/*
	 * Messagebox:
	 *     Janela usada para o sistema enviar mensagens de informações.
	 *     Esse é um ponteiro para um messagebox especial, utilizado 
	 * apenas pelo sistema, para mensagens sistemicamente importante.
	 */
	struct window_d *messagebox;

	/*
	 * DialogBox:
	 *     Janela usada para o sistema se comunicar com o usuário
	 *     solicitando alguma escolha de opção.
	 * Essa dialogbox é exclusiva para o sistema se comunicar com o 
	 * usuário sobre informações sistemicamente importantes. 
	 */
	struct window_d *dialogbox;
	
	//
	// Grupo 6: Outras.
	//
	
	
	//Debug: Janela usada pelo Kernel para mensagens de erro.
	struct window_d *debug;   

    //Menu bar.
	struct window_d *mbhWindow;       //Janela principal da menu bar.
	struct menu_d *mb;               //a menu bar é um menu
	struct menu_d *mbControlPanel;	 //Painel de controle
	struct menu_d *mbComputer;       //Meu computador(discos, diretorios ...)
	struct menu_d *mbFile;           //File manager. (abre e fecha arquivos)
	struct menu_d *mbWindow;         //Window manager (igual sistem menu) 
    //...	
	
	//
	//   **** BARs   ****
	//
	
	
	// Qualquer dessas barras serão gerenciadas pelo kernel ...
	// nãp fazem parate de um aplicativo, Porém o aplicativo gerenciador
	// de arquivos (explorer) será o responsável pela barra de tarefas que será 
	// usada pelo usuário.
	// Essas barras abaixo tem a finalidade de dar alguma navegabilidade
	// mesmo sem algum programa de gerenciamento de arquivos.
	// E também não há problemas em os dois conviverem.
	
	//TopBar.
	struct window_d *topbar;	
	struct menu_d *logonMenu;         //Logon
	struct menu_d *logoffMenu;	      //Logoff 

    //Navigation Bar.
    struct window_d *navigationbar;	
	struct menu_d *desktopMenu;       //Desktop 
	struct menu_d *setupMenu;         //Ambiente de configuração.
	
	//Current Menu.
	//Aponta para a estrutura do menu atual.
	//Seja ele de qual tipo for.
	struct menu_d *currentMenu;       //Current. Para outros ambiente.
	
	//
	// Shell.
	//
	
	//
	// Janelas para o shell.
    // Obs: A janela do Shell será a janela do navegador.
	// Pois cada página de Internet será considerada um processo
	// e será exibida dentro da janela de cliente do shell.
	// Assim como as aplicações e janelas de diálogo do sistema, 
	// poderão ser exibidas dentro e fora da janela de cliente do shell.
	//
	struct window_d *shellWindow;
	struct window_d *shellClientWindow;
	
	
	//Informações sobre a tela.
	struct screen_d *ScreenInfo;
	
	
	struct backbufferinfo_d  *backbufferInfo;  // Backbuffer support. (espelho da memória de video)
	
	struct frontbufferinfo_d *frontbufferInfo; // Frontbuffer support. (memória de vídeo)
	
    //Lista de informações sobre usuários.
    //@todo: Isso não precisa ficar aqui.	
	struct user_info_d *User; 	
	
	//...
};
gui_t *gui;   //Estrutura global. (Usada para passar estutura entre funções) 



/*
 * GUI:
 *     Interface gráfica para o usuário.
 *     Tudo o que compõe a área de trabalho. 
 *     Deve conter as janelas do sistema, como barra de ferramentas,
 * control menu.
 *
 */


 

/*
 *  Protótipos.
 */
 
 
 
/*
 * StartGui:
 *     Inicializa a gui.
 */						   
int StartGui();


/*
 * Create GUI.
 *    Cria a GUI na hora da inicialização.
 *
 */						   
void create_gui();


/*
 * SetGuiParameters:
 *     Configura a inicialização das janelas gerenciadas pelo kernel.
 *     @todo: Limite de janelas (+- 10)
 *
 */
void SetGuiParameters( int refresh,         
                       int screen,          
                       int background,       
                       int logo,            
                       int taskbar,         
                       int main,             
                       int menu,            
                       int infobox,         
                       int messagebox,       
                       int debug,           
                       int navigationbar,    
                       int grid );

					   
//
// Bars support. (menubar)
//

int StatusBar(struct window_d *window, unsigned char *string1, unsigned char *string2);
void *create_menubar(struct window_d *pwindow); 
int create_menubar_item(struct menu_d *menu, unsigned char *string, int status);
int draw_menubar_item( struct window_d *window, unsigned char *string);
//int select_menubar_item(struct menuitem_d *menuitem);
int menubarX();



//Color.
void set_up_color(unsigned long color);
void set_up_text_color(unsigned char forecolor, unsigned char backcolor);
							

//Button.
void *draw_button( struct window_d *window,
                  unsigned char *string, 
                  unsigned long type, 
                  unsigned long x, 
                  unsigned long y, 
                  unsigned long width, 
                  unsigned long height, 
                  unsigned long color);
				  
void MessageBox( struct window_d *parent_window, int type,char *title, char *string);
void DialogBox(struct window_d *parent_window, int type, char *title, char *string);


// Focus support.
void SetFocus( struct window_d *window );
void *GetFocus();                             
void KillFocus( struct window_d *window );

//foreground window support
void *windowGetForegroundWindow();
int windowSetForegroundWindow(struct window_d *window);

//parent.
void *GetParentWindow(struct window_d * hwnd);

//desktop
void *GetWindowDesktop(struct window_d * hwnd);


// pegando ponteiros para estrutura de janela na estrutura 'gui->'.
void *guiGetScreenWindow();
void *guiGetDeveloperScreenWindow();
void *guiGetBackgroundWindow();
void *guiGetLogoWindow();
void *guiGetDesktopWindow();
void *guiGetTaskbarWindow();
void *guiGetMainWindow();
void *guiGetStatusbarWindow();
void *guiGetGridWindow();
void *guiGetMenuWindow();
void *guiGetInfoboxWindow();
void *guiGetTooltipWindow();
void *guiGetMessageboxWindow();
void *guiGetDialogboxWindow();
void *guiGetDebugWindow();
void *guiGetMbhWindowWindow();
void *guiGetTopbarWindow();
void *guiGetNavigationbarWindow();
void *guiGetShellWindowWindow();
void *guiGetShellClientWindowWindow();


//
// Client Area.
//
void *getClientAreaRect();
void setClientAreaRect( unsigned long x, 
                        unsigned long y, 
						unsigned long cx, 
						unsigned long cy );

//
// Background support.
//

void backgroundDraw(unsigned long color);
void backgroundSetColor(unsigned long color);
void backgroundRedraw(unsigned long color);
void backgroundBackground();    //Construtor.
int backgroundInit();

//
// Char and String support.
//

void draw_string( unsigned long x, unsigned long y, unsigned long color, unsigned char *string);
void draw_text( struct window_d *window,
                unsigned long x,  
                unsigned long y,  
				unsigned long color, 
				unsigned char *string );
void my_buffer_char_blt( unsigned long x, 
                         unsigned long y, 
						 unsigned long color, 
						 unsigned long c);
						 
						 
						 
//
// Pixel, line rect support.
//						 
	
//Pinta um pixel em um buffer de janela.
void pixelPutPixelWindowBuffer( void* buffer, 
                          unsigned long x, 
						  unsigned long y, 
						  unsigned long color );
						  
/*
 * pixelPutPixelDedicatedWindowBuffer:
 *     Coloca um pixel no buffer da janela.
 *     Serve para pintar janelas que irão direto do seu buffer para o LFB da 
 * memória de vídeo, sem passar pelo back buffer. (OVERLAPPED)
 *
 */

void pixelPutPixelDedicatedWindowBuffer( struct window_d *window, 
                                         unsigned long x, 
										 unsigned long y, 
										 unsigned long color ); 	
						 
void my_buffer_put_pixel( unsigned long ax, 
                          unsigned long bx, 
						  unsigned long cx, 
						  unsigned long dx );
void my_buffer_horizontal_line( unsigned long x1,
                                unsigned long y, 
								unsigned long x2,  
								unsigned long color );
void drawDataRectangle( unsigned long x, 
                        unsigned long y, 
						unsigned long width, 
						unsigned long height, 
						unsigned long color );
 
//
// Window support.
// 
 
int init_window_manager();
int init_windows();
int RegisterWindow(struct window_d *window);
void set_current_window(struct window_d *window);
void *get_current_window();
int resize_window(struct window_d *window, unsigned long cx, unsigned long cy);		  
int replace_window(struct window_d *window, unsigned long x, unsigned long y);			  
int redraw_window(struct window_d *window);   //redraw window. 
int redraw_screen();                          //redraw all windows.
int is_window_full(struct window_d *window);
int is_window_maximized(struct window_d *window);
int is_window_minimized(struct window_d *window);

int get_active_window();
void set_active_window(struct window_d *window);
void change_active_window(int Id);
void CloseWindow(struct window_d *window);
void DestroyWindow(struct window_d *window);
void CloseActiveWindow();
void MinimizeWindow(struct window_d *window);
void MaximizeWindow(struct window_d *window);
void windowShowWindowList();
void show_window_with_focus();
void show_active_window();

//bloqueando e desbloqueando o foco.
void windowBlockfocus();
void windowUnblockFocus();


//@todo: Criar windowRefreshScreen();

void windowSwitchFocus();
void windowLock(struct window_d *window);
void windowUnlock(struct window_d *window);
int windowCreateDedicatedBuffer(struct window_d *window);

//envia mensagem para a fila da janela com foco de entrada.
void windowSendMessage(unsigned long arg1, unsigned long arg2, unsigned long arg3, unsigned long arg4);
//pega uma mensagem na estrutura da janela com o foco de entrada.
void *windowGetMessage(struct window_d *window);
void *windowGetLong1(struct window_d *window);
void *windowGetLong2(struct window_d *window);

void windowShowWWFMessageBuffers(); //mostra o buffer de mensagens da janela com foco de entrada.


//color support.
void windowSetUpColorScheme(int type);

/*Inicialização do sistema de suporte ao navegador shell*/
int windowInitializeBrowserSupport();

/*
 * CreateWindow:
 *     Cria uma janela com base em um tipo.
 */
void *CreateWindow( unsigned long type,  //1 - tipo de janela (popup ..normal ...)
unsigned long status,           //2  - estado da janela (ativa ou nao)
unsigned long view,             //3  - (min, max ...)
char* windowname,               //4  - titulo                                
unsigned long x,                //5  - deslocamento em relação às margens do desktop(sua instancia)        
unsigned long y,                //6  - idem
unsigned long width,            //7  - largura da janela  
unsigned long height,           //8  - altura
struct window_d *pWindow,       //9  - id da janela mae, se for zero, essa é a janela mae.
int desktopid,                  //10 - desktop ID.
unsigned long clientcolor,            //11 - Client Area Color.
unsigned long color             //12 - cor do bg (para janelas simples, tipo 1)
);


/*
 * do_draw:
 *     Pinta vários tipos de janelas.
 */
void do_draw(struct window_d *window, int type);


//
// Rotinas de pintura:
// Funções  de suporte à CreateWindow.
//

//1
void DrawPopUpWindow( struct window_d *w,
                        unsigned long x,  
                      unsigned long y,  
					  unsigned long width,  
					  unsigned long height,  
					  unsigned long color);
//2
void DrawEditBoxWindow( struct window_d *w,
                        unsigned long x, 
                        unsigned long y, 
						unsigned long width, 
						unsigned long height, 
						unsigned long color);
//3
void DrawNormalWindow( struct window_d *w,
                       char* titulo, 
                       unsigned long x, 
					   unsigned long y, 
					   unsigned long width, 
					   unsigned long height, 
					   unsigned long color);
//4
void DrawNormalEditWindow( struct window_d *w,
                           unsigned long x, 
                           unsigned long y, 
						   unsigned long width, 
						   unsigned long height, 
						   unsigned long color);
//5
void DrawMenuBarWindow( struct window_d *w,
                        unsigned long x, 
                        unsigned long y, 
						unsigned long width, 
						unsigned long height, 
						unsigned long color);
//6
void DrawToolBarWindow( struct window_d *w,
                        unsigned long x, 
                        unsigned long y, 
						unsigned long width, 
						unsigned long height, 
						unsigned long color);
//7
void DrawStatusBarWindow( struct window_d *w,
                          unsigned char *string1, 
                          unsigned char *string2, 
						  unsigned long x, 
						  unsigned long y, 
						  unsigned long width, 
						  unsigned long height, 
						  unsigned long color);
//8
void DrawTaskBarWindow( struct window_d *w,
                        unsigned long x, 
                        unsigned long y, 
						unsigned long width, 
						unsigned long height, 
						unsigned long color);
//9
void DrawControlMenuWindow(struct window_d *w,
                            unsigned long x, 
                            unsigned long y, 
							unsigned long width, 
							unsigned long height, 
							unsigned long color);
//10
void DrawAppWindow( struct window_d *w,
                    char* titulo, 
                    unsigned long x, 
					unsigned long y, 
					unsigned long width, 
					unsigned long height, 
					unsigned long color);
					
//
//fim.
//
