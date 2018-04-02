/*
 * Arquivo: screen.h
 *
 * Descrição:
 *     Informações sobre o monitor de video.
 *     informações de características de hardware.
 * 
 *     Ex: HD44780 - Display LCD para sistema embarcado. 
 *
 *   LCD:
 *   Active-matrix technologies:
 *   ==========================
 *   Twisted nematic (TN).
 *   In-plane switching (IPS).  IPS LCD vs AMOLED. 
 *   Super In-plane switching (S-IPS).
 *   Advanced fringe field switching (AFFS).
 *   Vertical alignment (VA).
 *   Blue phase mode.
 *
 *  Versão 1.0, 2015, 2016.    
 */


#define SCREEN_DEFAULT_LEFT  0
#define SCREEN_DEFAULT_TOP   0

//#define SCREEN_START 0x000B8000   //Físico.
#define SCREEN_START 0x800000       //Virtual.(remapeado pelo Boot Loader.)    
#define ScreenStart SCREEN_START
#define COLUMNS 80
#define SCREEN_WIDTH COLUMNS
#define ROWS 25
#define SCREEN_HEIGHT ROWS


#define SCREEN_CGA_START 0x800000  //FISICO= B8000.
//#define SCREEN_VGA_START (0x800000 + ??)  //FISICO= A0000.

//int screenCount;    //Numero de monitores.
//unsigned long screenList[8];

typedef struct screen_buffers_d screen_buffers_t;
struct screen_buffers_d
{

	//Object.
	//object_type_t objectType;
	//object_class_t objectClass;
	
    //
	// Endereços físicos.
    //
	
	unsigned long BackBuffer;     //off-screen buffer.
	unsigned long FrontBuffer;    //on-screen buffer. (LFB).	
	
	//Back buffer. (independente do dispositivo).
    unsigned long BackBufferWidth;
	unsigned long BackBufferHeight; 

	//Screen. LFB. (dependente do dispositivo).
    unsigned long FrontBufferWidth;
	unsigned long FrontBufferHeight; 	
	
};
screen_buffers_t *screenBuffers;
//...

/*
 * struct screen_d:
 *     Estrutura para informações sobre o monitor.
 *     Screen Object.
 */
typedef struct screen_d screen_t;
struct screen_d 
{
	object_type_t objectType;
	object_class_t objectClass;
	
    //unsigned long callback; //d
	
	
	unsigned long left; //c
    unsigned long top;  //b
    unsigned long width; //a
    unsigned long height;  //g
	
	
	unsigned long flag; //f
	unsigned long error;  //e

	//ext...
	
    //int Id;    //
	
	//Lista de estruturas de buffers ???
	screen_buffers_t *buffers;
	
	
	//Navigation.
    struct screen_d *next; 
};
screen_t *Screen;
screen_t *ScreenInfo;
screen_t *CurrentScreen;
//...
  

  
//@criar função: screenSetRenderTargets(...).

/*
 termos:
 
 ClientBounds - Limites da área de cliente desejada pelo usuário.??
 The screen dimensions of the game window's client rectangle.
 
 DisplayMode - dimensões da tela. dependentes do dispositivo.
 Retrieves the display mode's spatial resolution, color resolution, and refresh frequency.
 
 letterboxing: black bars
  If the aspect ratio of the back buffer is different from the aspect ratio of the 
  television display mode, the Xbox 360 will automatically add black bars 
  (also called letterboxing) if the user's display is not widescreen.
  
  pillar boxing: black box vertical.
  
  
  Outros:  back-buffer resolution, output device,
  
  the back-buffer is resized.
  
  dedicated buffers. (um elemento gráfico tem seu próprio buffer que será copiado para 
  o front buffer, ninguém mais pode usar esse buffer senão o elemento que o possui)
  
  talvez os seguintes termos sejam apropriados:
   screen buffer, window buffer, char buffer, button buffer, rect buffer ...
  
 Obs:
 A screen buffer can be any size, limited only by available memory. 
screen buffer's window = uma janela dentro do screen buffer.

The console(terminal emulator) window displays a portion of the active screen buffer.  

terminal screen buffer: (um buffer grande onde se coloca o conteudo)
  uma janela, a janela do emulador de terminal pode mostrar apenas uma parte
  do terminal screen buffer se quiser.
  
 The effects of ScrollConsoleScreenBuffer can be limited by specifying an optional 
 clipping rectangle so that the contents of the console screen buffer 
 outside the clipping rectangle are unchanged. 
 
 scroll: podemos apenas movimentar a janela dentro do terminal screen buffer para
 fazer o scroll, deixando o conteúdo do terminal screen buffer inalterado.
 
 Each console has an input buffer that contains a queue of input event records.
 
 terminal's input buffer.
 
*/
  

//screen.c 
unsigned long screenGetWidth();
unsigned long screenGetHeight();
void refresh_screen();
void screenRefresh();
void screenSetSize(unsigned long width, unsigned long height);
int screenInit(); 


//Outros.
void vsync();  //vsync.c



//
// End.
//

