/*
 * File: screen.h
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


#ifndef ____SCREEN_H
#define ____SCREEN_H    1


#define COLUMNS  80
#define ROWS     25
#define SCREEN_WIDTH   COLUMNS
#define SCREEN_HEIGHT  ROWS
#define SCREEN_DEFAULT_LEFT  0
#define SCREEN_DEFAULT_TOP   0


//#define SCREEN_START 0x000B8000   //Físico.
#define SCREEN_START 0x800000       //Virtual.(remapeado pelo Boot Loader.)    
#define ScreenStart SCREEN_START

#define SCREEN_CGA_START 0x800000  //FISICO= B8000.
//#define SCREEN_VGA_START (0x800000 + ??)  //FISICO= A0000.



//
// PAINT
//

// #sobre:
// A estrutura PAINT vai descrever os planos
// que serão usados pelo compositor para desenhar
// a tela.
// Cada plano tem seu backbuffer e seu frontbuffer.
// A placa de vídeo fará todos os frontbuffers serem pintados
// na mesma tela, gerando efeito de sombra e transparência.


struct plane_d
{
    int used;
    
    unsigned char *frontbuffer;
    unsigned char *backbuffer;
    
    unsigned long size_x;
    unsigned long size_y;
    unsigned long size_bpp;
};

struct paint_d
{
    struct plane_d plane[4];
    int number_of_planes;
};

struct paint_d PAINT;



/*
 * struct screen_d:
 *     Estrutura para informações sobre o monitor.
 *     Screen Object.
 */

struct screen_d 
{
    object_type_t  objectType;
    object_class_t objectClass;

    int used;
    int magic;
    
    int id;

    struct display_d *display;

    unsigned long left;
    unsigned long top;  
    unsigned long width; 
    unsigned long height; 

    unsigned long flag; 
    unsigned long error;  


    //Navigation.
    struct screen_d *next; 
};
struct screen_d  *Screen;
struct screen_d  *ScreenInfo;
struct screen_d  *CurrentScreen;
//...
  
//int screenCount;    //Numero de monitores.
//unsigned long screenList[8];

  
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

The terminal emulator window displays a portion of the active screen buffer.  

terminal screen buffer: (um buffer grande onde se coloca o conteudo)
  uma janela, a janela do emulador de terminal pode mostrar apenas uma parte
  do terminal screen buffer se quiser.
  
 The effects of ScrollTerminalScreenBuffer can be limited by specifying an optional 
 clipping rectangle so that the contents of the terminal screen buffer 
 outside the clipping rectangle are unchanged. 
 
 scroll: podemos apenas movimentar a janela dentro do terminal screen buffer para
 fazer o scroll, deixando o conteúdo do terminal screen buffer inalterado.
 
 Each terminal has an input buffer that contains a queue of input event records.

 terminal's input buffer.
 
*/



//
// == prototypes =========================
//


//screen.c 

unsigned long screenGetWidth (void);

unsigned long screenGetHeight (void);

void refresh_screen (void);

void screenRefresh (void);

void screenSetSize (unsigned long width, unsigned long height);

int screenInit (void); 


//Outros.
//#bugbug:?? redefinido ??
//void vsync ();  //vsync.c

#endif 


//
// End.
//

