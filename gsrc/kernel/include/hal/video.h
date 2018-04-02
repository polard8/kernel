/*
 * File: video.h
 *
 * Descrição:
 *     Header para rotinas de gerenciamento dos controladores de video.
 *     As configurações de video podem ser usadas pelo shell.
 * 
 * // 0xBEEF	VirtualBox Graphics Adapter	0x80EE	Oracle Corporation - InnoTek Systemberatung GmbH
 * @todo: Criar um utilitário que mostre e configure informações de video.
 *  Versão 1.0, 2015, 2016. 
 */

 
/*

    3C0-3CF  EGA/VGA
	3C0 VGA attribute and sequencer register
	3C1 Other video attributes
	3C2 EGA, VGA, CGA input status 0
	3C3 Video subsystem enable
	3C4 CGA, EGA, VGA sequencer index
	3C5 CGA, EGA, VGA sequencer
	3C6 VGA video DAC PEL mask
	3C7 VGA video DAC state
	3C8 VGA video DAC PEL address
	3C9 VGA video DAC
	3CA VGA graphics 2 position
	3CC VGA graphics 1 position
	3CD VGA feature control
	3CE VGA graphics index
	3CF Other VGA graphics

	3D0-3DF Color Graphics Monitor Adapter (ports 3D0-3DB are
		write only, see 6845)
	3D0 port address decodes to 3D4
	3D1 port address decodes to 3D5
	3D2 port address decodes to 3D4
	3D3 port address decodes to 3D5
	3D4 6845 index register, selects which register [0-11h]
	    is to be accessed through port 3D5
	3D5 6845 data register [0-11h] selected by port 3D4,
	    registers 0C-0F may be read.  If a read occurs without
	    the adapter installed, FFh is returned.  (see 6845)
	3D6 port address decodes to 3D4
	3D7 port address decodes to 3D5
	3D8 6845 Mode control register (CGA, EGA, VGA, except PCjr)
	3D9 color select palette register (CGA, EGA, VGA, see 6845)
	3DA status register (read only, see 6845, PCjr VGA access)
	3DB Clear light pen latch (any write)
	3DC Preset Light pen latch
	3DF CRT/CPU page register (PCjr only)
	
*/ 
 
/*

MDA	B0000 to B0FFF	3B0 to 3BB
CGA	B8000 to BBFFF	3D0 to 3DF

Mono text	B0000 to B7FFF	3B0 to 3BB, 3C0 to 3CF
Mono graphics	A0000 to AFFFF	3B0 to 3BB, 3C0 to 3CF
Colour text	B8000 to BFFFF	3C0 to 3CF, 3D0 to 3DF
Colour graphics	A0000 to AFFFF or B8000 to BFFFF	3C0 to 3CF, 3D0 to 3DF
 */ 
 
 
/*
  bytes.
  A whole screeen is either 2000 bytes (40*25*2) or 4000 bytes (80*25*2).
*/ 
 
/*
 * LFB e BACKBUFFER
 *     
 *     Constantes para endereços lógicos.
 *     O bootloader configura as páginas e 
 *     atribui esse endereço para o LFB.
 * 
 */ 
#define LFB_BASE        0xC0400000 
#define BACKBUFFER_BASE 0xC0800000


//Memória de video vga em text mode. b8000
//the address 0xC00B8000 must be used, since the virtual address 0xC0000000 maps to the physical address 0x00000000.


/*
 * Video mode:
 *     Modo de vídeo usado.
 *     //@todo: se estamos encapsulando no módulo, retirar o G de global.
 */
unsigned long g_video_mode;    

/*
 * Suporte às dimenções da tela no modo de vídeo escolhido.
 * @todo: existe uma redefinição em window.h
 */
//unsigned long gScreenWidth;
//unsigned long gScreenHeight;




//
// Graphic mode support.
//
 
typedef struct tagGraphics Graphics_t;
struct tagGraphics
{
    unsigned long LFB;
	//...
};
Graphics_t *Graphics;



//
// Video support.
//

/*
 * video_d:
 *     Estrutura para informações sobre parâmetros de vídeo.
 *
 */
typedef struct video_d VideoBlock_t;

typedef struct video_d video_t;
struct video_d
{

	object_type_t objectType;
	object_class_t objectClass;
	
	
	//call back ;d
	
	int useGui;   //c, se estamos ou não usando gui. text mode, video mode.
	int vgaMode;  //b, número do modo de vídeo se estiver usando vga.
	int vesaMode; //a, número do modo vesa.
	//int 
	//...
	
	//unsigned long flag;  //f
	//unsigned long error; //e
	
	//currente video memory. Ponteiro para a base atual da memoria de video
	// em text mode.
	unsigned long currentVM; 
	char ch;           //caractere.
	char chAtrib;      //atributo do caractere. 
	//...    

    //unsigned long Display[32];    //Ponteiros para as telas.
	
};
video_t VideoBlock;
//...


/*
 * Prototypes.
 */
 
/*
 * Sincroniza o retraço vertical. para directdraw usando lfb.
 * @todo: 
 *     Essa função pode ser arte do hal, 
 * ficando aqui apenas uma interface.
 *Obs: Isso é coisa de hardware. vídeo. (HAL)
 */
void vsync();  
 
 
//video.c 
void videoSetupCGAStartAddress(unsigned long address);
unsigned long videoGetMode();
void videoSetMode(unsigned long mode);
int videoInit(); 
int videoVideo();  //Método construtor.


//
// End.
//
