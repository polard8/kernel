
// globals.h


#ifndef __GWSSRV_GLOBALS_H
#define __GWSSRV_GLOBALS_H   1


extern int gUseCallback;
extern int gUseMouse;


//
// == buffer ===============================================
//

// This is the buffer used when we receive 
// requests via socket.
// see: globals.c
#define MSG_BUFFER_SIZE  512
extern char __buffer[MSG_BUFFER_SIZE];

// Esses valores serão enviados como 
// resposta ao serviço atual.
// Eles são configurados pelo dialogo na hora da 
// prestação do serviço.
// No início desse array fica o header.
// see: globals.c
#define NEXTRESPONSE_BUFFER_SIZE  32
extern unsigned long next_response[32];

//----------------------------------------


struct initialization_d
{

// Initialization phase.
// 0: Nothing
// 1: Initialize global variables and structures.
// 2: Initialize graphics infrastructure.
// 3: Entering the main loop. 

    int current_phase;
    
    int ws_struct_checkpoint;
    int wm_struct_checkpoint;
    int register_ws_checkpoint;
    int setup_callback_checkpoint;
    int setup_connection_checkpoint;
    int setup_graphics_interface_checkpoint;
    int inloop_checkpoint;
};
extern struct initialization_d  Initialization;


// Host Operating System
#define OS_OTHER    0
#define OS_NATIVE   1
#define OS_LINUX    2
#define OS_WINDOWS  3

// Virtual Machine
#define VM_OTHER       0
#define VM_NATIVE      1
#define VM_VMWARE      2
#define VM_QEMU        3
#define VM_VIRTUALBOX  4

// =========================
// h:d.s
extern char *host_name;
extern char *display_number;
extern char *screen_number;


// ============================
// Modes.
#define GRAMADO_JAIL        0x00
#define GRAMADO_P1          0x01
#define GRAMADO_HOME        0x02
#define GRAMADO_P2          0x03
#define GRAMADO_CASTLE      0x04
#define GRAMADO_CALIFORNIA  0x05
extern int current_mode;


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



/*
// --------------------
// #importante
// Usaremos essas definições para configurarmos
// o esquema de cores 'default'.
#define HUMILITY_COLOR_BACKGROUND                 0x00008080 
#define HUMILITY_COLOR_WINDOW                     0x00FFFFFF 
#define HUMILITY_COLOR_WINDOW_BACKGROUND          0x00202020 
#define HUMILITY_COLOR_ACTIVE_WINDOW_BORDER       0x00404040 
#define HUMILITY_COLOR_INACTIVE_WINDOW_BORDER     0x00606060
// Titlebar for active window.
// Light blue (Um pouco fosco) 
#define HUMILITY_COLOR_ACTIVE_WINDOW_TITLEBAR  COLOR_BLUE1
#define HUMILITY_COLOR_INACTIVE_WINDOW_TITLEBAR   0x00606060 
#define HUMILITY_COLOR_MENUBAR                    0x00808080 
#define HUMILITY_COLOR_SCROLLBAR                  0x00FFF5EE 
#define HUMILITY_COLOR_STATUSBAR                  0x0083FCFF
// Taskbar for the window manager.
#define HUMILITY_COLOR_TASKBAR  0x00C3C3C3 
#define HUMILITY_COLOR_MESSAGEBOX      0x00404040 
#define HUMILITY_COLOR_SYSTEMFONT      0x00000000 
#define HUMILITY_COLOR_TERMINALFONT    0x00FFFFFF 
#define HUMILITY_COLOR_BUTTON  0x00C3C3C3 
// Window border
#define HUMILITY_COLOR_WINDOW_BORDER  COLOR_INACTIVEBORDER
// Window with focus border
#define HUMILITY_COLOR_WWF_BORDER  COLOR_BLUE
#define HUMILITY_COLOR_TITLEBAR_TEXT  COLOR_WHITE
#define HUMILITY_COLOR_BG_ONMOUSEHOVER  xCOLOR_GRAY3
//...
// --------------------
*/



// --------------------
// #importante
// Usaremos essas definições para configurarmos
// o esquema de cores 'default'.
#define HUMILITY_COLOR_BACKGROUND                 0x00909497 //0x00008080 
#define HUMILITY_COLOR_WINDOW                     0x00FFFFFF 
#define HUMILITY_COLOR_WINDOW_BACKGROUND          0x00202020 
#define HUMILITY_COLOR_ACTIVE_WINDOW_BORDER       0x00404040 
#define HUMILITY_COLOR_INACTIVE_WINDOW_BORDER     0x00606060
// Titlebar for active window.
// Light blue (Um pouco fosco) 
#define HUMILITY_COLOR_ACTIVE_WINDOW_TITLEBAR  0x00A9CCE3  //COLOR_BLUE1
#define HUMILITY_COLOR_INACTIVE_WINDOW_TITLEBAR   0x00606060 
#define HUMILITY_COLOR_MENUBAR                    0x00808080 
#define HUMILITY_COLOR_SCROLLBAR                  0x00FFF5EE 
#define HUMILITY_COLOR_STATUSBAR                  0x0083FCFF
// Taskbar for the window manager.
#define HUMILITY_COLOR_TASKBAR  0x00C3C3C3 
#define HUMILITY_COLOR_MESSAGEBOX      0x00404040 
#define HUMILITY_COLOR_SYSTEMFONT      0x00000000 
#define HUMILITY_COLOR_TERMINALFONT    0x00FFFFFF 
#define HUMILITY_COLOR_BUTTON  0x00C3C3C3 
// Window border
#define HUMILITY_COLOR_WINDOW_BORDER  COLOR_INACTIVEBORDER
// Window with focus border
#define HUMILITY_COLOR_WWF_BORDER  COLOR_BLUE
#define HUMILITY_COLOR_TITLEBAR_TEXT  COLOR_WHITE
#define HUMILITY_COLOR_BG_ONMOUSEHOVER  xCOLOR_GRAY3
//...
// --------------------




/*
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
    csiTaskBar,                 //11

    csiMessageBox,              //12
    csiSystemFontColor,         //13 BLACK
    csiTerminalFontColor,       //14 WHITE
    
    csiButton,   // 15

    csiWindowBorder,  // 16 window border
    csiWWFBorder,     // 17 window with focus border.

    csiTitleBarTextColor,  // 18
    csiWhenMouseHover,     // 19 bg when mouse hover
    
    csiTaskBarTextColor   // 20: Color for text in the taskbar.

    //...
    //@todo: focus,
    //@todo: Window 'shadow' (black??)

}ColorSchemeIndex;  


/*
 * color_scheme_d:
 *     Estrutura para esquema de cores. 
 *     O esquema de cores se aplica ao servidor 
 * de recursos gráficos. GWS.
 */ 

struct gws_color_scheme_d
{
    int used;
    int magic;

    int id;
    int initialized;

    char *name; 

// Marcador de estilo de design para o padrão de cores.
// Cada estilo pode invocar por si um padrão de cores 
// ou o padrão de cores por si pode representar um estilo.
    int style;

// Cada índice desse array representará um elemento gráfico,
// Os valores no array são cores 
// correspondentes aos elementos gráficos indicados pelos índices.

    unsigned int elements[32];
    //color_t elements[32];

    //...

// Navigation
    struct gws_color_scheme_d *next;
};

// See: wm.c
extern struct gws_color_scheme_d* GWSCurrentColorScheme;


//
// == variables ==============================================
//

// #ordem
// hardware, software
extern unsigned long  ____BACKBUFFER_VA;
extern unsigned long  ____FRONTBUFFER_VA;
// Saving
extern unsigned long SavedBootBlock;
extern unsigned long SavedLFB;   // #bugbug? VA ?
extern unsigned long SavedX;
extern unsigned long SavedY;
extern unsigned long SavedBPP; 
// helper.
extern unsigned long __device_width;
extern unsigned long __device_height;
extern unsigned long __device_bpp;

// refresh rate of the whole screen.
//static unsigned long fps;

// refresh rate for all dirty objects. In one round.
//static unsigned long frames_count;
// static unsigned long frames_count_in_this_round;

// Vamos usar ou nao.
extern int use_vsync;
#define VSYNC_YES  1
#define VSYNC_NO   0


// Pointers to screens.
#define MAX_SCREENS    4
#define SCREEN_FRONTBUFFER     0
#define SCREEN_BACKBUFFER      1
//#define SCREEN_BACKBUFFER2   2
//#define SCREEN_BACKBUFFER3   3

extern unsigned long screens[MAX_SCREENS];



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

// wm.c
int gwssrv_initialize_default_color_scheme(void);
unsigned int get_color(int index);

#endif   



