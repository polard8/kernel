/*
 * File gws.h
 *     GWS - Gramado Window Server
 *
 * Esse é o prncipal header do gws, preferenciamente
 * devem ficar aqui as globais usadas no servidor.
 *
 * #importante:
 *     Os dados serão emcapsulados nesse servidor  
 * e serão acessíveis através de métodos.
 *     Ficarão aqui as principais globais de controle
 * dos recursos gráficos.
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

