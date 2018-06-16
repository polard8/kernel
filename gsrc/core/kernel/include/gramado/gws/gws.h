/*
 * File gws.h
 *     GWS - Gramado Window Server
 *
 * Esse é o principal header do gws, preferenciamente
 * devem ficar aqui as globais usadas no servidor.
 *
 * #importante:
 *     Os dados serão emcapsulados nesse servidor  
 * e serão acessíveis através de métodos.
 *     Ficarão aqui as principais globais de controle
 * dos recursos gráficos.
 *
 * Obs: Um processo vai operar como grenciador de janelas
 * em ring e vai dialogar com o servidor para obter recursos.
 * Provavelmente esse gerenciador de janelas se chamará GWM
 * Gramado Window Manager. Porém podemos ter vários gerenciadores 
 * de janela em user mode.
 *
 *
 * History:
 *     2018 - Created by Fred Nora.
 *
 */
 
 
// ## Contagens ##
#define USER_SESSION_COUNT_MAX    32  //16 
#define WINDOW_STATION_COUNT_MAX  32  //16 
#define DESKTOP_COUNT_MAX         32  //16
#define WINDOW_COUNT_MAX          1024 //512 //256
#define MAX_WINDOWS WINDOW_COUNT_MAX 
 
 
 
//Definindo as dimensões padrão. 
//#define DEFAULT_SCREEN_WIDTH  800
//#define DEFAULT_SCREEN_HEIGHT 600 
 
//desktop
#define DESKTOP_X  0
#define DESKTOP_Y  0


// # video mode support #
#define VIDEO_MODE_TEXT     1
#define VIDEO_MODE_GRAPHIC  2 
 
 
// # char support # 
#define CHAR_WIDTH   8
#define CHAR_HEIGHT  8 
#define DEFAULT_CHAR_WIDTH   8
#define DEFAULT_CHAR_HEIGHT  8
//...



 
 
 
 
 
//
//  ## COLOR DEFINES ##
// 
 
// #importante:
// As definições de cores aqui se aplicam somente 
// ao servidor de recursos gráficos GWS.
// Nem tudo o que for definido aqui será público. 
 
 
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
 
//??#bugbug checar. 
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
#define GUICOLOR_SYSTEMFONT_COLOR  12
#define GUICOLOR_TERMINALFONT_COLOR  13
//...

//CORES BÁSICAS.
#define rgbBlack   0x000000
#define rgbBlue    0x0000FF
#define rgbCyan    0x00FFFF
#define rgbGreen   0x00FF00
#define rgbMagenta 0xFF00FF
#define rgbRed     0xFF0000
#define rgbYellow  0xFFFF00
#define rgbWhite   0xFFFFFF


// ## blue support ##
#define COLOR_BLUE1 0x067AB5
#define COLOR_BLUE2CYAN   0x1BA1E2
#define COLOR_BLUE3COBALT 0x0050EF
#define COLOR_BLUE4INDIGO 0x6A00FF
 
// ## gray support ## 
//cinza para pintar janela
//a janela tem camadas que vai do mais escuro para o mais claro.
#define xCOLOR_BLACK 0x000000  //preto
#define xCOLOR_GRAY1 0x202020  //cinza mais escuro
#define xCOLOR_GRAY2 0x404040  //cinza
#define xCOLOR_GRAY3 0x606060  //cinza
#define xCOLOR_GRAY4 0x808080  //cinza
#define xCOLOR_GRAY5 0xa0a0a0  //cinza
#define xCOLOR_GRAY6 0xc0c0c0  //cinza
#define xCOLOR_GRAY7 0xe0e0e0  //cinza mais clarinho
#define xCOLOR_WHITE 0xffffff  //branco  
 
//WIN23 - TRÊS TIPOS DE CINZA.
#define COLOR_LITBUTTON  0xE0E0E0
#define COLOR_LTGRAY     0xC0C0C0
#define COLOR_GRAY       0x808080 

// ## black support ##
// Preto. 
//50% 	#808080
//45% 	#737373
//40% 	#666666
//35% 	#595959
//30% 	#4d4d4d
//25% 	#404040
//20% 	#333333
//15% 	#262626
//10%   #1a1a1a
//5%    #0d0d0d
//0%    #000000
 
//w2k - system colors
//#bugbug delete;
#define COLOR_TEST_0  0x8080FF  // COLOR_BACKGROUND(verde claro) ??
#define COLOR_TEST_1  0x80FFFF  // COLOR_APPWORKSPACE, MDIWINDOW 
#define COLOR_TEST_2  0x80FF80  // COLOR_WINDOW, CLIENT
#define COLOR_TEST_3  0x80FF00  // COLOR_WINDOWTEXT, CLIENTTEXT 
#define COLOR_TEST_4  0xFFFF80  // COLOR_MENU, MENUBAR
#define COLOR_TEST_5  0xFF8000  // COLOR_MENUTEXT (laranjado+-)
#define COLOR_TEST_6  0xC080FF  // COLOR_ACTIVECAPTION, MYCAPTION
#define COLOR_TEST_7  0xFF80FF  // COLOR_INACTIVECAPTION, CAPTION2
#define COLOR_TEST_8  0x0000FF  // COLOR_CAPTIONTEXT, CAPTIONTEXT(azul)highlight
#define COLOR_TEST_9  0x00FFFF  // COLOR_ACTIVEBORDER, BORDER
#define COLOR_TEST_10 0x00FF80  // COLOR_INACTIVEBORDER, BORDER2
#define COLOR_TEST_11 0x40FF00  // COLOR_WINDOWFRAME
#define COLOR_TEST_12 0xFFFF00  // COLOR_SCROLLBAR (amarelo)
#define COLOR_TEST_13 0xC08000  // COLOR_BTNFACE
#define COLOR_TEST_14 0xC08080  // COLOR_BTNSHADOW (vinho)
#define COLOR_TEST_15 0xFF00FF  // COLOR_BTNTEXT (rosa)
#define COLOR_TEST_16 0x404080  // COLOR_HIGHLIGHT ~ COLOR_GRAYTEXT (azul escuro)
#define COLOR_TEST_17 0x4080FF  // COLOR_HIGHLIGHT
#define COLOR_TEST_18 0x00FF00  // COLOR_HIGHLIGHTTEXT (verde)
#define COLOR_TEST_19 0x808000  // COLOR_INACTIVECAPTIONTEXT
#define COLOR_TEST_20 0x804000  // COLOR_BTNHIGHLIGHT
#define COLOR_TEST_21 0xFF8080 
#define COLOR_TEST_22 0x400080 
#define COLOR_TEST_23 0x8000FF
#define COLOR_TEST_24 0x000080  //COLOR_HIGHLIGHT ~ hot track (azul)
#define COLOR_TEST_25 0x0080FF 
#define COLOR_TEST_26 0x008000 
#define COLOR_TEST_27 0x408000 
#define COLOR_TEST_28 0xFF0000  //red
#define COLOR_TEST_29 0xA00000 
#define COLOR_TEST_30 0x800080 
#define COLOR_TEST_31 0xFF0080
#define COLOR_TEST_32 0x000040
#define COLOR_TEST_33 0x004080 
#define COLOR_TEST_34 0x004000 
#define COLOR_TEST_35 0x404000 
#define COLOR_TEST_36 0x800000 
#define COLOR_TEST_37 0x400000 
#define COLOR_TEST_38 0x400040
#define COLOR_TEST_39 0x800040
#define COLOR_TEST_40 0x000000  //COLOR_BTNSHADOW ~ preto text
#define COLOR_TEST_41 0x008080  //vrde escuro
#define COLOR_TEST_42 0x408080  //vrde escuro
#define COLOR_TEST_43 0x808080  //COLOR_APPWORKSPACE (cinza)
#define COLOR_TEST_44 0x808040 
#define COLOR_TEST_45 0xC0C0C0  //silver
#define COLOR_TEST_46 0x400040 
 
//outros teste
#define COLOR_TEST_47 0x3366FF  //azul claro

  
// # testes #
#define COLOR_ALICEBLUE           0xF0F8FF
#define COLOR_ANTIQUEWHITE        0xFAEBD7
#define COLOR_AQUA                0x00FFFF
#define COLOR_AQUAMARINE          0x7FFFD4 //verde claro.
#define COLOR_AZURE               0xF0FFFF //azul, quase branco. 
#define COLOR_BEIGE               0xF5F5DC
#define COLOR_BISQUE              0xFFE4C4
#define COLOR_BLANCHEDALMOND      0xFFEBCD
#define COLOR_BLUEVIOLET          0x8A2BE2
#define COLOR_BROWN               0xA52A2A
#define COLOR_BURLYWOOD           0xDEB887
#define COLOR_CADETBLUE           0x5F9EA0
#define COLOR_CHARTREUSE          0x7FFF00
#define COLOR_CHOCOLATE           0xD2691E
#define COLOR_CORAL               0xFF7F50
#define COLOR_CORNFLOWERBLUE      0x6495ED
#define COLOR_CORNSILK            0xFFF8DC
#define COLOR_CRIMSON             0xDC143C
#define COLOR_CYAN                0x00FFFF
#define COLOR_DARKCYAN            0x008B8B
#define COLOR_DARKGOLDENROD       0xB8860B
#define COLOR_DARKGRAY            0xA9A9A9
#define COLOR_DARKKHAKI           0xBDB76B
#define COLOR_DARKMAGENTA         0x8B008B
#define COLOR_DARKOLIVEGREEN      0x556B2F
#define COLOR_DARKORANGE          0xFF8C00
#define COLOR_DARKORCHID          0x9932CC
#define COLOR_DARKSALMON          0xE9967A
#define COLOR_DARKSEAGREEN        0x8FBC8B
#define COLOR_DARKSLATEBLUE       0x483D8B
#define COLOR_DARKSLATEGRAY       0x2F4F4F
#define COLOR_DARKTURQUOISE       0x00CED1
#define COLOR_DARKVIOLET          0x9400D3
#define COLOR_DEEPPINK            0xFF1493
#define COLOR_DEEPSKYBLUE         0x00BFFF
#define COLOR_DIMGRAY             0x696969
#define COLOR_DODGERBLUE          0x1E90FF
#define COLOR_FIREBRICK           0xB22222
#define COLOR_FLORALWHITE         0xFFFAF0
#define COLOR_FORESTGREEN         0x228B22
#define COLOR_FUCHSIA             0xFF00FF
#define COLOR_GAINSBORO           0xDCDCDC
#define COLOR_GHOSTWHITE          0xF8F8FF
#define COLOR_GOLD                0xFFD700
#define COLOR_GOLDENROD           0xDAA520
#define COLOR_GRADIENTACTIVECAPTION   0xB9D1EA
#define COLOR_GRADIENTINACTIVECAPTION 0xD7E4F2
#define COLOR_GREENYELLOW         0xADFF2F
#define COLOR_HONEYDEW            0xF0FFF0
#define COLOR_HOTPINK             0xFF69B4 //rosa chiclete.
#define COLOR_HOTTRACK            0x0066CC //azul legal.
#define COLOR_INDIANRED           0xCD5C5C
#define COLOR_INDIGO              0x4B0082 //violeta
#define COLOR_IVORY               0xFFFFF0
#define COLOR_KHAKI               0xF0E68C
#define COLOR_LAVENDER            0xE6E6FA
#define COLOR_LAVENDERBLUSH       0xFFF0F5
#define COLOR_LAWNGREEN           0x7CFC00
#define COLOR_LEMONCHIFFON        0xFFFACD
#define COLOR_LIGHTCORAL          0xF08080
#define COLOR_LIGHTCYAN           0xE0FFFF
#define COLOR_LIGHTGOLDENRODYELLOW 0xFAFAD2
#define COLOR_LIGHTPINK           0xFFB6C1
#define COLOR_LIGHTSALMON         0xFFA07A
#define COLOR_LIGHTSEAGREEN       0x20B2AA
#define COLOR_LIGHTSKYBLUE        0x87CEFA  //azul clarinho
#define COLOR_LIGHTSLATEGRAY      0x778899
#define COLOR_LIGHTSTEELBLUE      0xB0C4DE
#define COLOR_LIGHTYELLOW         0xFFFFE0
#define COLOR_LIME                0x00FF00
#define COLOR_LIMEGREEN           0x32CD32
#define COLOR_LINEN               0xFAF0E6
#define COLOR_MAGENTA             0xFF00FF
#define COLOR_MAROON              0x800000
#define COLOR_MEDIUMAQUAMARINE    0x66CDAA
#define COLOR_MEDIUMBLUE          0x0000CD
#define COLOR_MEDIUMORCHID        0xBA55D3
#define COLOR_MEDIUMPURPLE        0x9370DB
#define COLOR_MEDIUMSEAGREEN      0x3CB371
#define COLOR_MEDIUMSLATEBLUE     0x7B68EE
#define COLOR_MEDIUMSPRINGGREEN   0x00FA9A
#define COLOR_MEDIUMTURQUOISE     0x48D1CC
#define COLOR_MEDIUMVIOLETRED     0xC71585
#define COLOR_MIDNIGHTBLUE        0x191970
#define COLOR_MINTCREAM           0xF5FFFA
#define COLOR_MISTYROSE           0xFFE4E1
#define COLOR_MOCCASIN            0xFFE4B5
#define COLOR_NAVAJOWHITE         0xFFDEAD //branco areioso.
#define COLOR_NAVY                0x000080
#define COLOR_OLDLACE             0xFDF5E6
#define COLOR_OLIVE               0x808000
#define COLOR_OLIVEDRAB           0x6B8E23
#define COLOR_ORANGE              0xFFA500
#define COLOR_ORANGERED           0xFF4500
#define COLOR_ORCHID              0xDA70D6
#define COLOR_PALEGOLDENROD       0xEEE8AA
#define COLOR_PALEGREEN           0x98FB98
#define COLOR_PALETURQUOISE       0xAFEEEE
#define COLOR_PALEVIOLETRED       0xDB7093
#define COLOR_PAPAYAWHIP          0xFFEFD5
#define COLOR_PEACHPUFF           0xFFDAB9
#define COLOR_PERU                0xCD853F
#define COLOR_PINK                0xFFC0CB
#define COLOR_PLUM                0xDDA0DD
#define COLOR_POWDERBLUE          0xB0E0E6
#define COLOR_PURPLE              0x800080
#define COLOR_ROSYBROWN           0xBC8F8F
#define COLOR_ROYALBLUE           0x4169E1
#define COLOR_SADDLEBROWN         0x8B4513
#define COLOR_SALMON              0xFA8072
#define COLOR_SANDYBROWN          0xF4A460
#define COLOR_SCROLLBAR           0xC8C8C8
#define COLOR_SEAGREEN            0x2E8B57
#define COLOR_SEASHELL            0xFFF5EE  //branco sujinho
#define COLOR_SIENNA              0xA0522D
#define COLOR_SKYBLUE             0x87CEEB  //azul claro
#define COLOR_SLATEBLUE           0x6A5ACD  //azul/violeta
#define COLOR_SLATEGRAY           0x708090
#define COLOR_SNOW                0xFFFAFA //branco
#define COLOR_SPRINGGREEN         0x00FF7F
#define COLOR_STEELBLUE           0x4682B4 //azul legal.
#define COLOR_TAN                 0xD2B48C
#define COLOR_TEAL                0x008080
#define COLOR_THISTLE             0xD8BFD8
#define COLOR_TOMATO              0xFF6347
#define COLOR_TRANSPARENT         0xFFFFFF
#define COLOR_TURQUOISE           0x40E0D0
#define COLOR_VIOLET              0xEE82EE
#define COLOR_WHEAT               0xF5DEB3
#define COLOR_WHITESMOKE          0xF5F5F5 //branco enfumaçado.
#define COLOR_YELLOW              0xFFFF00
#define COLOR_YELLOWGREEN         0x9ACD32
#define STEALTH_ORANGE            0xFF8800
#define STEALTH_OLIVE             0x666600
#define STEALTH_GREEN             0x33DD11
#define STEALTH_PINK              0xFF22EE
#define STEALTH_BLUE              0x0077BB
 

 
 
// ## text support ##
#define COLOR_TEXT2  0x00404040   //25%
#define COLOR_TEXT1  0x00333333   //20% 
#define COLOR_TEXT   COLOR_TEXT1 
//#define COLOR_TEXT  0x00000000  

#define COLOR_WINDOW              0x00FFFFFF
#define COLOR_BLACK               0x000000
#define COLOR_WHITE               0xFFFFFF 
#define COLOR_RED                 0xFF0000 
#define COLOR_GREEN               0x00FF00
#define COLOR_BLUE                0x0000FF
#define COLOR_DARKRED             0x8B0000
#define COLOR_DARKGREEN           0x006400
#define COLOR_DARKBLUE            0x00008B
//#define COLOR_GRAY                0x808080
#define COLOR_GREY                0xAFAFAF
#define COLOR_LIGHTGRAY           0xD3D3D3
#define COLOR_LIGHTGREEN          0x90EE90
#define COLOR_LIGHTBLUE           0xADD8E6
#define COLOR_SILVER              0xC0C0C0
 
 

//
// ## WINDOW COLORS ##
//  


#define COLOR_ACTIVEBORDER        0xB4B4B4

#define COLOR_ACTIVECAPTION       0x99B4D1
#define COLOR_ACTIVECAPTION_TEXT   0x000000

#define COLOR_APPWORKSPACE  COLOR_SILVER 

// A cor padrão para o Bg é azul quase escuro,
// o azul escuro é usado em seleção de item.

#define COLOR_BACKGROUND  0x008080  
#define COLOR_BACKGROUNDTEXT  COLOR_TEXT  

#define COLOR_BORDER  COLOR_SILVER 

// ## button support ##
#define COLOR_BUTTONFACE 0xF0F0F0
#define COLOR_BUTTONFACE2 0xE0E0E0
#define COLOR_BUTTONFACE3 0xD0D0D0
#define COLOR_BUTTONHIGHLIGHT 0xFFFFFF
#define COLOR_BUTTONHIGHLIGHT2 0x404040
#define COLOR_BUTTONHIGHLIGHTTEXT COLOR_WHITE
#define COLOR_BUTTONHIGHLIGHTTEXT2 COLOR_WHITE //@todo: branco menos intenso.
#define COLOR_BUTTONSHADOW 0xA0A0A0
#define COLOR_BUTTONSHADOW2 0x303030  
#define COLOR_BUTTONTEXT COLOR_TEXT

// # control support #
#define COLOR_CONTROL             0xF0F0F0
#define COLOR_CONTROLTEXT COLOR_TEXT
#define COLOR_CONTROLDARK         0xA0A0A0
#define COLOR_CONTROLDARKDARK     0x696969
#define COLOR_CONTROLLIGHT        0xE3E3E3
#define COLOR_CONTROLLIGHTLIGHT   0xFFFFFF
#define COLOR_CONTROLLIGHTLIGHTTEXT COLOR_WHITE

#define COLOR_DESKTOP  0x000000

#define COLOR_FOCUS_TOPBAR  0x7FFF00

//TEXT SUPPORT
#define COLOR_GRAYTEXT  0x808080
#define COLOR_HIGHLIGHT           0x3399FF
#define COLOR_HIGHLIGHTTEXT       0xFFFFFF


#define COLOR_INACTIVEBORDER      0xF4F7FC
#define COLOR_INACTIVECAPTION     0xBFCDDB
#define COLOR_INACTIVECAPTIONTEXT 0x434E54

#define COLOR_INFO  0xFFFFE1
#define COLOR_INFOTEXT  TEXT_COLOR

#define COLOR_MENU  COLOR_GRAY
#define COLOR_MENUTEXT  COLOR_TEXT

#define COLOR_MENUITEM  COLOR_WHITE
#define COLOR_MENUITEMTEXT  COLOR_TEXT

#define COLOR_MENUITEMSELECTED  COLOR_BLUE
#define COLOR_MENUITEMSELECTEDTEXT  COLOR_WHITE

#define COLOR_MENUBAR  COLOR_GRAY
#define COLOR_MENUBARTEXT  COLOR_TEXT

#define COLOR_MENUHIGHLIGHT  0x003399FF
#define COLOR_MENUHIGHLIGHTTEXT  COLOR_WHITE

#define COLOR_NAVIGATIONBAR       COLOR_BLACK
#define COLOR_NAVIGATIONBARTEXT  COLOR_WHITE

//status bar
#define COLOR_STATUSBAR  COLOR_WINDOW   //branca
#define COLOR_STATUSBAR2 xCOLOR_GRAY6   //cinza
#define COLOR_STATUSBAR3 0x83FCFF       //verde
//...
#define COLOR_STATUSBARTEXT      COLOR_TEXT

#define COLOR_TASKBAR             COLOR_WINDOW
#define COLOR_TASKBARTEXT        COLOR_TEXT

#define COLOR_TITLEBAR            COLOR_BLUE
#define COLOR_TITLEBARTEXT       COLOR_TEXT

#define COLOR_TOPBAR  0x83F52C
#define COLOR_TOPBARTEXT  COLOR_TEXT

#define COLOR_WINDOWFRAME  COLOR_GRAY

// NÃO FAREMOS JANELAS PRETAS
// PRETO É O BACKGROUND
#define COLOR_WINDOWTEXT COLOR_TEXT  

//area de trabalho
#define COLOR_WORKSPACE 0x0000FF00 
#define COLOR_WORKSPACETEXT COLOR_TEXT


// ## virtual terminal support ##
#define COLOR_TERMINAL  COLOR_BLACK
#define COLOR_TERMINAL2 0x303030
//...

#define COLOR_TERMINALTEXT COLOR_WHITE
#define COLOR_TERMINALTEXT2 xCOLOR_GRAY7
//...
  
//
// ========
//  
 
 
/*
 * (w) Colors, futuristic GUI. (Dark blu and Black)
 */ 
 
//#define COLOR_DARKBLUE   0x00008B00 
//#define COLOR_BLACK      0x00000000 
 
 
#define COLOR_KERNEL_BACKGROUND COLOR_BLUE   
 
 
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
	//...
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
	csiActiveWindowBorder,	    //4
	csiInactiveWindowBorder,    //5
	                    
	//bar
	csiActiveWindowTitleBar,    //6	
	csiInactiveWindowTitleBar,  //7
	csiMenuBar,                 //8
	csiScrollBar,               //9
	csiStatusBar,	            //10
	
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
 *
 */ 
typedef struct color_scheme_d* color_scheme_t;
struct color_scheme_d
{
    //@todo: É preciso ainda definir esse tipo de objeto.
	//definir em gdef.h
	object_type_t objectType;
	object_class_t objectClass;	
	
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
color_scheme_t CurrentColorScheme;
color_scheme_t HumilityColorScheme; // Simples.
color_scheme_t PrideColorScheme;    // Colorido.
//... 

//
// # Principais variáveis globais #
//

int guiStatus;        //Status da Interface gráfica do usuário.
int g_guiMinimal; //Light or Full gui.

//Status de ambientes gráficos.
int logonStatus;              //Logon status.
int logoffStatus;             //Logoff status.
int userenvironmentStatus;    //User environment status.


// ## Contagens ##
int windowstations_count;  
int desktops_count;
int windows_count;  

 
int current_usersession;    //gws
int current_windowstation;  //gws
int current_desktop;        //gws 
int current_window;         //gws
int current_menu; //gws

//
// # Outras variáveis globais #
//

//janela ativa
int active_window;
//janela com foco de entrada. 
int window_with_focus;
//Indice 0 na zorder atual.  
int top_window;
//edit box atual
int editbox_window;
//combobox atual
int combobox_window;
//janela atual do terminal atual.
int terminal_window;

// ## tests ##
//int mouseover_window;
//int current_button_window;
////cada janela tem seu controle first responder.
//int current_first responder.
//...

//
// gws fonts
//


//As fontes usadas pelo servidor gws
unsigned long gws_currentfont_address;      //fonte atual.
unsigned long g8x8fontAddress;   //8×8, 80×25,CGA, EGA
unsigned long g8x14fontAddress;  //8x14,80×25,EGA
unsigned long g8x16fontAddress;  //??
unsigned long g9x14fontAddress;  //9x14,80×25,MDA, Hercules
unsigned long g9x16fontAddress;  //9x16,80×25,VGA
//...

int gfontSize;

// draw char support
int gcharWidth;
int gcharHeight;

unsigned long g_system_color;
unsigned long g_char_attrib;



// LFB - address for kernel graphic mode
unsigned long g_kernel_lfb; 

//video mode
unsigned long g_current_vm; //video memory
unsigned long g_current_video_mode; //video mode


//#test# todo
//#importante: Em gws.h é o lugar ideal para 
//gerenciar recursos de gerente servidor de recursos gráficos.
//unsigned long gwsSavedLFB;          //LFB address.  
//unsigned long gwsSavedX;            //Screen width. 
//unsigned long gwsSavedY;            //Screen height.
//unsigned long gwsSavedBPP;          //Bits per pixel.


//cursor support.
unsigned long g_cursor_x;
unsigned long g_cursor_y;
unsigned long g_cursor_width;   //??
unsigned long g_cursor_height;  //??
unsigned long g_cursor_color;
unsigned long g_cursor_left;     // margem esquerda dada em linhas
unsigned long g_cursor_top;      // margem superior dada em linhas
unsigned long g_cursor_right;    // margem direita dada em linhas
unsigned long g_cursor_bottom;   // margem inferior dada em linhas


unsigned long g_mousepointer_x;
unsigned long g_mousepointer_y;


void 
gwsSetCurrentFontAddress( unsigned long address );

unsigned long
gwsGetCurrentFontAddress();

//
// End
//

