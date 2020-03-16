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
  bytes.
  A whole screeen is either 2000 bytes (40*25*2) or 4000 bytes (80*25*2).
*/ 
 
/*
 * LFB e BACKBUFFER
 *     
 *     Constantes para endereços lógicos.
 *     O bootloader configura as páginas e 
 *     atribui esse endereço para o LFB.
 */ 

#define LFB_BASE        0xC0400000 
#define BACKBUFFER_BASE 0xC0800000


//Memória de video vga em text mode. b8000
//the address 0xC00B8000 must be used, since the virtual address 0xC0000000 maps 
//to the physical address 0x00000000.


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

void vsync (void);  
 
 
//video.c 
void videoSetupCGAStartAddress(unsigned long address);

unsigned long videoGetMode (void);

void videoSetMode (unsigned long mode);

int videoInit (void); 

int videoVideo (void);  


//
// End.
//
