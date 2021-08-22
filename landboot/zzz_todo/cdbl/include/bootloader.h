/*
 * File: bootloader.h 
 *
 * Descrição:
 *     Header principal do Boot Loader de 32 bits, BL.BIN.
 *     Feito em 32bit C/Assembly.
 *
 * Propósito: 
 *    Declarações e protótipos para as funções principais do Boot Loader.
 *    Oferecer o suporte necessário nessa fase de inicialização.
 *    ...
 * 
 * Histórico:
 * =========
 * Versão 1.0, 2013 - Esse arquivo foi criado por Fred Nora.
 * Versão 1.0, 2014 - Construção de rotinas básicas de suporte.
 * Versão 1.0, 2015 - Construção de mais rotinas básicas de suporte.
 * Versão 1.0, 2016 - Aprimoramento e Debug do que foi feito até aqui.
 * ...
 *
 * Copyright (c) 2013 - 2016 Frederico Martins Nora (frednora).
 */

//
// Variáveis para habilitações de verbose pra debug.
// Em ordem alfabética.
//

//Debug flags.
//Testando desligado.
//#define BL_VERBOSE 1   


 
#include <gdef.h>  
 
 
/*
 * Variáveis importadas.
 * Stack pointers ??
 */
 
extern unsigned long task0_stack;
extern unsigned long task1_stack;
extern unsigned long task2_stack;
 
 
//
// Funções importadas.
//
 
extern void refresh_screen();
 
 
// Boot Loader version.
#define BL_VERSION "0.1"






/*
 * Status do carregamento de um arquivo.
 */
 
//#define LOAD_SUCCESS  0
//#define LOAD_FAILURE  1    //Erro genérico.
//#define LOAD_
//Continua...		 
 
 

/*
 * FDC support.
 *
 * PORTS: Constants for support ports.
 *        @todo: Não oferecer mais suporte ao FDC. 
 */
 
#define DOR1  0x3F2    //Digital Output Register. 
#define DOR2  0x372  
#define MSR1  0x3F4    //Main Status Register. 
#define MSR2  0x374  
#define DR1   0x3F5    //Data Register. 
#define DR2   0x375
#define DIR1  0x3F7    //Digital Input Register. 
#define DIR2  0x377
#define CCR1  0x3F7    //Configuration Control Register. 
#define CCR2  0x377
#define DOR   DOR1
#define DSR   MSR1


/*
 * Processor mode constants.
 */

#define SI_RM 0    //Real mode.
#define SI_PM 1    //Protected mode.
#define SI_LM 2    //Long mode.
#define SI_SM 3    //SMM, System Management Mode (Supervisor Mode).


/*
 * Boot Loader page directory constants.
 */
 

/*
 * Memory page tables:
 *     Mapeando memória para o Boot Loader e os arquivos que ele tem 
 * que carregar.
 * Obs: Cada processo terá seu próprio diretório de páginas. Isso significa 
 * que para cada processo, os endereços lógicos podem mudar, mas não deve-se 
 * mecher no endereço lógico do kernel. Todos os processos terão a parte
 * mais alta da sua memória lóca resercada para o Kernel. Tipicamente 
 * reserva-se o último gigabyte da memória virtual de cada processo
 * para uso do Kernel.
 * Obs: O arquivo head.s configura CR3 com 0x01F00000, que é o endereço
 * do primeiro page_directory. Os diretórios e páginas são configurados 
 * em pages.c. De toda forma o Kernel pode refazer essa configuração,
 * carregando os diretórios de página onde bem entender.
 * 
 */
#define BOOTLOADER_PAGEDIRECTORY  0x9C000    //Directory.
#define KM_PAGETABLE              0x8C000    //Kernel page table.
#define KM2_PAGETABLE             0x8D000    //Kernel page table 2.
#define UM_PAGETABLE              0x8E000    //User Mode page table.
#define VGA_PAGETABLE             0x8F000    //VGA page table..
//...

/*
 * Kernel memory constants.
 */

#define KERNEL_BASE     0x00100000    //1MB físico.
#define KERNEL_ADDRESS  0x00100000    //Físico.
#define KERNEL_VA       0xC0000000    //Lógico. 


/*
 * User mode memory constants.
 */
 
#define  USER_BASE       0x00400000    //4MB físico.
//#define  USER_BASE32MB_PA   0x02000000    //32MB físico.


/*
 * Video Memory constans.
 */
#define VM_BASE   0x000B8000    //Físico.
#define MEM_BASE  0x000A0000    //Físico.


/*
 * Tasks constans.
 */
 
/*
 * APP and DLL:
 *     Endereços virtuais do início dos programas.
 * @todo: Os programas do sistema em User Mode poderiam ser carregados 
 * na parte mais alta da memória virtual disponivel para aplicativos 
 * em user mode. Isso fica antes da área destinada ao Kernel. É um
 * forma de proteção.
 *
 */
#define DLL_VA 0             //Vínculo dinâmico, .DLL, .SO.  
#define APP_VA 0x00400000    //Padrão para aplicativos. 4MB. 
//...


//
// File support: 
// Usado pelo loader pra carregar arquivos do sistema.
// Obs: Esses são endereços físicos para carregamento das aplicaçções
// do sistema. Porém o endereço lógico para o carregamento das
// aplicações será 0x400000 e das bibliotecas compartilhadas será 0x0.
//





#define INIT_ADDRESS         0x00400000    //Físico.
#define SHELL_ADDRESS        0x00450000    //Físico. 
#define TASKMANAGER_ADDRESS  0x004A0000    //Físico.
//... 

//Endereços físicos.
//#define SERVER_ADDRESS       0x00400000    //Genérico.
//#define APP_ADDRESS          0x00400000    //Genérico.
 
 
/*
 * Disk constants.
 */ 

#define MBR_SIGNATURE (0xAA55) 
#define SECTOR_SIZE 512  
#define INIT_SECTOR 20
//...


/*
 * Constants for text support.
 *     @todo: Definir tamanho padrão.
 */

//Char.
#define CHAR_WIDTH   8
#define CHAR_HEIGHT  8
 
//Line 
#define LINE         1024    //800.??
#define LINE_MAX     768     //600. ?? 

//Column
//#define COL          1024    //800. ??
#define COL_MAX      1024    //800. ??


//...


/*
 * Constants for window support.
 *     @todo: Boot Loader não deve ter suporte à janelas.
 *            Apenas suporte ao tamanho ta tela.
 */

#define HWND_DESKTOP 0   //errado.
#define MAX_WINDOWS 256
#define DESKTOP_X        0
#define DESKTOP_Y        0
#define DESKTOP_LARGURA 1024    //640.
#define DESKTOP_ALTURA   768    //480.
//...


/*
 * Constants for menu support.
 */
 
#define menu_size  (MENU_ALTURA * 8)
#define MENU_X         0
#define MENU_Y         748    
#define MENU_LARGURA   200
#define MENU_ALTURA    200
#define MENU_INICIAR_X   0
#define MENU_INICIAR_Y  748    
#define MENU_INICIAR_LARGURA   60
#define MENU_INICIAR_ALTURA    20
//...


/*
 *  Colors:
 *      Constants for support colors. 
 *      @todo: O Boot Loader deve usar poucas cores, 
 *      como: Branco, Preto, Cinza, Vermelho.
 */

//White.
#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_WHITESMOKE 0xF5F5F5FF
#define COLOR_SNOW 0xFFFAFAFF
#define COLOR_GHOSTWHITE 0xF8F8FFFF

//Blue.
#define COLOR_BLUE 0x0000FFFF
#define COLOR_DARKBLUE 0x00008BFF
#define COLOR_LIGHTBLUE 0xADD8E6FF
#define COLOR_BLUEVIOLET 0x8A2BE2FF
#define COLOR_DEEPSKYBLUE 0x00BFFFFF
#define COLOR_DODGERBLUE 0x1E90FFFF
#define COLOR_MEDIUMBLUE 0x0000CDFF
#define COLOR_LIGHTSKYBLUE 0x87CEFAFF
#define COLOR_LIGHTSTEELBLUE 0xB0C4DEFF
#define COLOR_MIDNIGHTBLUE 0x191970FF
#define COLOR_POWDERBLUE 0xB0E0E6FF
#define COLOR_ROYALBLUE 0x4169E1FF
#define COLOR_SKYBLUE 0x87CEEBFF
#define COLOR_SLATEBLUE 0x6A5ACDFF
#define COLOR_STEELBLUE 0x4682B4FF
#define STEALTH_BLUE 0x0077BB00

//Gray.
#define COLOR_GRAY 0x808080FF
#define COLOR_GREY     0xAFAFAFAA
#define COLOR_DARKGRAY 0xA9A9A9FF
#define COLOR_LIGHTGRAY 0xD3D3D3FF
#define COLOR_DARKSLATEBLUE 0x483D8BFF
#define COLOR_DARKSLATEGRAY 0x2F4F4FFF
#define COLOR_DIMGRAY 0x696969FF
#define COLOR_GRAYTEXT 0x808080FF
#define COLOR_LIGHTSLATEGRAY 0x778899FF
#define COLOR_SILVER 0xC0C0C0FF


//Outros. 
#define COLOR_BLACK 0x000000FF
#define COLOR_RED 0x00FF0000
#define COLOR_TEXT 0x00000000
#define COLOR_WINDOW 0xFFFFFFFF
#define COLOR_MENU 0xF0F0F0FF
#define COLOR_DESKTOP 0x000000FF
#define COLOR_APPWORKSPACE 0xABABABFF
//#define COLOR_BUTTONFACE 0xF0F0F0FF
//#define COLOR_BUTTONHIGHLIGHT 0xFFFFFFFF
//#define COLOR_BUTTONSHADOW 0xA0A0A0FF
//#define COLOR_CONTROL 0xF0F0F0FF
//#define COLOR_CONTROLDARK 0xA0A0A0FF
//#define COLOR_CONTROLDARKDARK 0x696969FF
//#define COLOR_CONTROLLIGHT 0xE3E3E3FF
//#define COLOR_CONTROLLIGHTLIGHT 0xFFFFFFFF
//#define COLOR_CONTROLTEXT 0x000000FF
//#define COLOR_GRADIENTACTIVECAPTION 0xB9D1EAFF
//#define COLOR_GRADIENTINACTIVECAPTION 0xD7E4F2FF
#define COLOR_HIGHLIGHT 0x3399FFFF
#define COLOR_HIGHLIGHTTEXT 0xFFFFFFFF
//#define COLOR_INACTIVEBORDER 0xF4F7FCFF
//#define COLOR_INACTIVECAPTION 0xBFCDDBFF
//#define COLOR_INACTIVECAPTIONTEXT 0x434E54FF
#define COLOR_INFO 0xFFFFE1FF
#define COLOR_INFOTEXT 0x000000FF
#define COLOR_MENUBAR 0xF0F0F0FF
#define COLOR_MENUHIGHLIGHT 0x3399FFFF
#define COLOR_MENUTEXT 0x000000FF
//#define COLOR_SCROLLBAR 0xC8C8C8FF
//#define COLOR_TOMATO 0xFF6347FF 
#define COLOR_WINDOWFRAME 0x646464FF
#define COLOR_WINDOWTEXT 0x000000FF
//...


/*
 * Includes.
 */
 
#include "en/strings.h"

#include <memmap.h>     //Memory Map - address.
#include <diskmap.h>    //Disk Map   - sectors.


/*
 * Lib C support.
 */
#include <types.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
//...


/*
 * Boot Loader i386 specific support.
 */
#include <bli386.h>

/*
 * File System support.
 */
#include <fs.h>

/*
 * IRQs support.
 */

//#include <timer.h>     //irq 0.
#include <keyboard.h>    //irq 1.
//#include <ide.h>
//...


/*
 * Shell.
 * Boot Loader mini-shell support. 
 * Obs: This must be the last one.
 */
#include <shell.h>


//
// (Boot Loader Internal). Para rotinas globais começadas com BlXXXX().
// Acessiveis à todos os módulos do boot loader.
//
#include <bli.h>


//
// Variáveis globais.
//

//Se o boot loader está inicializado.
int g_initialized;

/*
 * Variables for text support.
 *     @todo: Usar o padrão 'g_' para todas variáveis globais
 * aqui no suporte à texto.
 */

unsigned long g_cursor_x;        //Cursor.
unsigned long g_cursor_y;        //Cursor. 
unsigned long g_system_color;    //Color. 
unsigned long g_char_attrib;     //Color.  
unsigned long CURSOR_X;
unsigned long CURSOR_Y; 
unsigned long STATUS_X;
unsigned long STATUS_Y;
unsigned long EDITBOX_X;
unsigned long EDITBOX_Y;
unsigned long EDITBOX_LARGURA;
unsigned long EDITBOX_ALTURA;
unsigned long EDITBOX_BG_COLOR;
unsigned long EDITBOX_TEXT_COLOR;



//
// CR3 support.
//

//unsigned long registerCR3;
unsigned long LegacyCR3;        //Valor existente.
unsigned long BootLoaderCR3;    //Valor configurado pelo Boot Loader.

//CR0
//unsigned long registerCR0;


/*
 *  Variables for GUI support. Usar ou não o modo gráfico.
 */
int useGUI;         


/*
 * Variables for window procedure support.
 */
 
unsigned long g_proc_status; 
unsigned long g_next_app;
unsigned long g_next_proc;
unsigned long g_nova_mensagem;
unsigned long next_address;  //??


/*
 * Variables for task support.
 * @todo: Não usar o termo task.
 */ 
unsigned long current_task;
unsigned long proximo;  //??	


/*
 * Variables for LFB Address support. 
 */
unsigned long g_lbf_pa;    //Endereço Físico do LFB.
unsigned long g_lbf_va;    //Endereço Lógico do LFB.


/*
 * Structures for Boot Loader.
 */
 


/*
 * system_d:
 *     Structure for global system informations.
 */
 
typedef struct system_d system_t;
struct system_d
{
    unsigned long processor_mode;        
    unsigned long video_mode;   
    //Continua...        
};
system_t system_info;
//system_t systemInfo; 
//...
 
 
/*
 * Structure for global video parameters.
 */ 
 
/*
 * VideoBlock:
 *     Estrutura para informações sobre parâmetros de vídeo.
 *     @todo: criar um header para video. video.h.
 *
 */
typedef struct video_d VideoBlock_t;
struct video_d
{
	int useGui;      //Se estamos ou não usando gui. text mode, video mode.
	int vgaMode;     //Número do modo de vídeo se estiver usando vga.
	int vesaMode;    //Número do modo vesa.
	
	unsigned long LFB_PA;    //Endereço Físico do LFB.
	unsigned long LFB_VA;    //Endereço Lógico do LFB.
	
	//...
	
	//currente video memory. Ponteiro para a base atual da memoria de video
	// em text mode.
	
	unsigned long currentVM; 
	char ch;                   //Caractere.
	char chAtrib;              //Atributo do caractere. 
	//...           
};
VideoBlock_t VideoBlock;    //@todo: Usar um ponteiro.

 
 

/*
 * VESA support.
 */ 
 
typedef struct vesa_d vesa_t;
struct vesa_d
{
    unsigned long mode_number;    //Número do modo.
    unsigned long x_res;          //Pixels por linha.
	unsigned long y_res;          //Pixels por coluna.
	unsigned long bpp;            //Bits per pixel.		
	//Continua...
};
vesa_t vesa_mode;




/*
 * Structure for support window procedure parameters.
 *
 */

typedef struct procedure_d procedure_t;
struct procedure_d
{
    unsigned long next;      //Endereço do procimo procedimento.     
    unsigned long status;    //Status do procedimento do sistema. 
	unsigned long res1;      //Reservado.
	unsigned long res2;      //Reservado.
    // ...        	
};
procedure_t procedure_info;



/*
  // gdtr support.
typedef struct gdtr_d gdtr_t;
struct gdtr_d 
{
    unsigned short  Limit;
    unsigned long   Base;
};
gdtr_t bl_gdtr;    //Sem ponteiro. 
*/


/*
 *  Boot Loader prototypes.
 */
 


/*
 * Ports support.
 */

inline void bloutportb(unsigned int port,unsigned int value);
inline unsigned char inportb(int port);
//int inport8(int port,int data);
char inb(int port);
int outb(int port, int data);
int outport8(int port,int data);
int inport16(int port,int data);
int outport16(int port,int data);
int inport32(int port,int data); 
int outport32(int port,int data);
int outportb(int port, int data);
int BlProcessorInPort8(int port,int data);      
int BlProcessorOutPort8(int port,int data);     
int BlProcessorInPort16(int port,int data);     
int BlProcessorOutPort16(int port,int data);    
int BlProcessorInPort32(int port,int data);     
int BlProcessorOutPort32(int port,int data);    
inline unsigned long inportl(unsigned long port);
inline void outportl(unsigned long port, unsigned long value);

/*
 * CPU instructions support.
 */
 
void enable();
void disable();
void stopCpu();      
void intReturn();
void farReturn();
int getFlags(int variable);
int setFlags(int variable);
int Push(int value);
int Pop(int variable);
void pushRegs();
void popRegs();
void pushFlags();
void popFlags();
int getStackPointer(int addr);
int setStackPointer(int addr);


//
// Initialization support.
//

int init();
void init_globals();
void boot(); 


							
//
// Text support.
//

void set_up_color(unsigned long color);
void set_up_text_color(unsigned char forecolor, unsigned char backcolor); 
unsigned long get_cursor_x();
unsigned long get_cursor_y();
unsigned long input(unsigned long ch);
void panic(const char *msg); 



//
// Timer support.
//
void timer();
int BltimerInit();

//
// Paging support.
//
int SetUpPaging();


								   
//
// Disk support.
//  @todo: usar inglês.
//
void limpa_root(); //@todo: usar inglês.
void limpa_fat();  //@todo: usar inglês.
void my_read_hd_sector( unsigned long ax, 
                        unsigned long bx, 
						unsigned long cx, 
						unsigned long dx);
void my_write_hd_sector( unsigned long ax, 
                         unsigned long bx, 
						 unsigned long cx, 
						 unsigned long dx);
void write_lba( unsigned long address, unsigned long lba);
void read_lba( unsigned long address, unsigned long lba);



//
// PCI support.
//

int pciInit(); 
int pciInfo();
unsigned char pciGetClassCode(unsigned char bus, unsigned char slot);
unsigned short pciCheckVendor(unsigned char bus, unsigned char slot);
unsigned short pciCheckDevice(unsigned char bus, unsigned char slot);
unsigned short pciConfigReadWord( unsigned char bus, 
                                  unsigned char slot, 
								  unsigned char func, 
								  unsigned char offset );

//
// Boot Loader services.
//
		
void system_services();
 
//
// Debug support.
//@todo: usar inglês.
//
                        
void mostra_reg(unsigned long id);  


//
// Finalizations support.
//


void reboot();

//erros
void abort();  //abort.c  //apresenta o tipo de erro.
void die();    //main.c   //erro fatal.

//
//fim.
//
