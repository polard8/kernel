
// ws.h
// Window system support.
// Colors and color scheme.

#ifndef __DISPLAY_WS_H
#define __DISPLAY_WS_H    1


// Counters.
#define USER_SESSION_COUNT_MAX  16
#define ROOM_COUNT_MAX          16
#define DESKTOP_COUNT_MAX       16

//
// Colors
//

/*
 * ColorSchemeType:
 *     Enumerando os esquemas de cores. 
 *     Esses são esquemas default.
 *     Poderemos carregar outros e cada esquema terá seu índice.
 *     Esses serão sempre os primeiros.    
 */
typedef enum {
    ColorSchemeNull,      // 0 - Null.
    ColorSchemeHumility,  // 1 - Gray stuff.
    ColorSchemePride,     // 2 - Colorful.
    // ...
}ColorSchemeType;

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

    csiMessageBox,              //11
    csiSystemFontColor,         //12 BLACK
    csiTerminalFontColor,       //13 WHITE
    //...
//@todo: focus,
//@todo: Window 'shadow' (black??)

}ColorSchemeIndex;  


/*
 * color_scheme_d:
 *     Estrutura para esquema de cores. 
 *     O esquema de cores se aplica ao servidor de recursos gráficos. 
 */ 
struct color_scheme_d
{

// #todo: 
// É preciso ainda definir esse tipo de objeto.
// definir em gdef.h

    //object_type_t  objectType;
    //object_class_t objectClass;

    //#todo Not initilized yet.
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
// #ps:
// The kernel only have two color schemes:
// Humility and Pride.
// see: graphics.c
extern struct color_scheme_d *HumilityColorScheme; // Simples.
extern struct color_scheme_d *PrideColorScheme;    // Colorido.
extern struct color_scheme_d *CurrentColorScheme;
// ===============================================================

struct ws_info_d
{
    int initialized;
    pid_t pid;
    int pid_personality;
    tid_t tid;
    int tid_personality
};
// see: graphics.c
extern struct ws_info_d  WindowServerInfo;

// ===============================================================

// # Principais variáveis globais #
// This is not the right place for them.

// see: graphics.c
extern int current_display; 
extern int current_screen;
extern int guiStatus;
// Status de ambientes gráficos.
extern int logonStatus;              //Logon status.
extern int logoffStatus;             //Logoff status.
extern int userenvironmentStatus;    //User environment status.
// Contagens de ambientes;
extern int rooms_count;  
extern int desktops_count;

// draw char support
extern int gcharWidth;
extern int gcharHeight;
extern unsigned long g_system_color;
extern unsigned long g_char_attrib;
// LFB - address for kernel graphic mode
extern unsigned long g_kernel_lfb; 
//video mode
extern unsigned long g_current_vm;          //video memory
extern unsigned long g_current_video_mode;  //video mode
//status do cursor.
//se ele deve aparecer e piscar ou não.
extern int g_show_text_cursor;
//status: aceso ou apagado.
//0=apaga 1=acende.
extern int textcursorStatus;      
extern unsigned long g_mousepointer_x;
extern unsigned long g_mousepointer_y;

//
// == window server ==================================================
//

// types of window server.
typedef enum {
    WindowServerTypeNull,
    WindowServerTypeEmbedded,       // Embedded inside the base kernel.
    WindowServerTypeRing0Process,
    WindowServerTypeRing3Process
    // ...
} window_server_t;

// The window server struct.
// Here we will find all the info we need about the window server
// that the system is using in the moment. Things like, name, pid ... 
// The system is able to run only one window server.
// We can select one window server per desktop.
// The window server is a ring3 process.
// The system also have an embedded window server inside the base kernel.
// Maybe we will create different kinds of window server in the future,
// but this is gonna be the struct for then all. Only one structure.


// #todo:
// maybe the window server can be an kind of device
// and we can use the file dev/ws to setup the properties.
// and use ioctl.


// #bugbug
// Estamos com problemas na hora dos aplicativos pegarem 
// informaçoes que estao dentro de estruturas do kernel.
// Por isso suspendemos essa estrutura por enquanto.
// Leia as notas de design.

//struct window_server_d
//{
    // #bugbug
    // It works fine on qemu.
    // But we lost all these values when testing on my real machine. 
    // Why?
    // ps: We are using the embedded command, 'metrics' on gdeshell.
    // Maybe the problem is in the gdeshell application.

    int WindowServer_initialized;
    
    window_server_t WindowServer_type;  // tipo de window server.
    
    // the pid for loadable window servers.
    // When the window server is the embedded so this pid needs to be
    // the pid of the kernel process.
    
    pid_t WindowServer_pid; 
    //struct desktop_d *desktop;  // The desktop associated with the ws. 

    // Limiting the nale to 64.
    char WindowServer_name[64];

    //file *ws_file;
    
    // the virtual console used by this window server.
    int WindowServer_virtual_console;
    
    //no navigation.
//};
//static struct window_server_d WindowServer;


//
// == prototypes ==============================================
//

int ws_init (void);

int 
ws_ioctl ( 
    int fd, 
    unsigned long request, 
    unsigned long arg );

void ws_show_info(void);

#endif    
















