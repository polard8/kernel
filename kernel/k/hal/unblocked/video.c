/*
 * File: video.c
 *
 * Descrição: 
 *     Rotinas paga gerenciar os controladores de video.
 *     Faz parte do modulo HAL. (hardware)
 *     Crt, Vga ...
 *
 * Versão: 1.0, 2015.
 */


#include <kernel.h>


//
// Variáveis importadas.
//

extern unsigned long SavedBootMode;

//Variáveis. (head.s)
extern unsigned long SavedBootBlock;    //Parâmtros passados pelo Boot Loader.
extern unsigned long SavedLFB;          //LFB address.  
extern unsigned long SavedX;            //Screen width. 
extern unsigned long SavedY;            //Screen height.
extern unsigned long SavedBPP;          //Bits per pixel.
//...

//
// Variáveis internas.
//

int videoStatus;
int videoError;
//...


/*
 * videoVideo:
 *     Método construtor.
 *     Funçao interna. 
 *     Confgura algumas variáveis.
 */
int videoVideo();



/*
 * videoSetupCGAStartAddress:
 *     Configura o endereço inicial da memória de video em modo texto   
 *     fis=b8000  vir=0x800000 
 */
void videoSetupCGAStartAddress( unsigned long address)
{
    g_current_vm = (unsigned long) address;
	//g_current_cga_address
	return;
};

/*
 fis=a0000
void videoSetupVGAStartAddress( unsigned long address);
void videoSetupVGAStartAddress( unsigned long address)
{
    g_current_vga_address = (unsigned long) address;
	return;
};
*/



/*
 * videoInit:
 * Inicia variáveis de video de acordo com o modo gráfico utilizado.
 */ 
int videoInit()
{
	int Status = 0;
	
	//uintptr_t addr;
	
	
	//Construtor. Configura algumas variáveis internas do gerenciador de vídeo.
	videoVideo();
		
	
	//
	// Configuração inicial em modo gráfico.
	//
	
	if(g_useGUI == 1 || VideoBlock.useGui == 1)
	{
	    g_useGUI = 1;
		VideoBlock.useGui = 1;
	    
		//@todo: Configura Backbuffer e LFB.
		g_backbuffer_address = (unsigned long) BACKBUFFER_ADDRESS;
		g_frontbuffer_buffer_address = (unsigned long) SavedLFB;
		
		//Device screen sizes. (herdadas do boot loader.)
		g_device_screen_width = (unsigned long) SavedX;
		g_device_screen_height = (unsigned long) SavedY;
		
		//
		//@todo: #bugbug Para configurar a estrutura HostDeviceInfo tem que 
		//alocar memória antes, por isso só faremos isso depois de 
		//inicializarmos o módulo runtime. /rt.
		//
		
		//Background.
		backgroundDraw(COLOR_BLUE);
		
	    //@todo: Isso deve fazer parte do construtor.
		
		//Poderíamos copiar a font da ROM para a RAM.
		
		//Font. (BIOS font).
		gfontAddress = (unsigned long) 0x000FFA6E;  //Code page 437.  
	    gcharWidth = 8;
	    gcharHeight = 8;		
	    
		//Cursor. ??pra que isso?
		g_cursor_x = 0;
	    g_cursor_y = 8;
		
        g_cursor_left = 0;  //margem esquerda dada em linhas
        g_cursor_top = 0;   //margem superior dada em linhas
        
		//@todo:
		//#bugbug Um valor baixo aqui trava a máquina.
		g_cursor_right  = 256;  //margem direita dada em linhas
        g_cursor_bottom = 256;   //margem inferior dada em linhas
		
		//terminal. (cmd)
		//shell_create_terminal();
		
		//Continua ...
	};
	
	
	//
	// Configuração inicial em modo texto.
	//
	
	if(g_useGUI == 0 || VideoBlock.useGui == 0)
	{
	    g_useGUI = 0;
		VideoBlock.useGui = 0;
		
	    // Verifica se o monitor é de 16 cores ou monocromico
	    //if((inportb(0x3CC) & 0x01) != 0){
		//    addr      = 0xB8000L;
		//    video_io  = 0x3D4;
	    //}
	    //else{
		//    addr      = 0xB0000L;
		//    video_io  = 0x3B4;
	    //}		
		
		//video_mem = (uint16_t *)(addr);
		
	    //Screen.
        videoSetupCGAStartAddress(SCREEN_CGA_START);
	    
		//Background.
		kclear(0);
		
		//text color. (branco em preto).
	    set_up_text_color(0x0F, 0x00); 
		
		//set video mode
		//SetVideoMode(3);
		
		//Continua ...	
	};
	


	//
	// Outras configurações de vídeo independentes do modo de vídeo.
	//
	
config:	
	set_up_cursor(0,0);    //Cursor.
	
	//
    // @todo: Sizes, atribute, atribute color, row, column
	//
	
done:
    g_driver_video_initialized = 0;
    return (int) Status;    
};


/*
 * get_video_mode: 
 *     Obtem o modo de video atual.
 */
unsigned long videoGetMode(){
	return (unsigned long) g_current_video_mode;
};

/*
 * videoSetMode:
 * Configura o modo de video atual.
 */
void videoSetMode(unsigned long mode)
{
    unsigned long VideoMode;
    unsigned long Width;
	unsigned long Height;
	//continua...(outros parametros)

	
	VideoMode = (unsigned long) mode;
	
    //
	// todo: Check limits.
	//
	
	//if (){}
	

	//Se estiver nos limites.
	if( VideoMode > 0 && VideoMode < 9000)
	{
		//g_current_video_mode = (unsigned long) VideoMode;
        g_video_mode = (unsigned long) VideoMode;
		VideoBlock.vesaMode = (unsigned long) VideoMode; 
		//...
	};
	
	
    switch(VideoMode)
	{
	    case 0x110: 
		    Width = 800;
			Height = 600;
		break;

	    case 0x111:
		    Width = 800;
			Height = 600;
		break;

	    case 0x112:
		    Width = 800;
			Height = 600;
		break;

	    case 0x113:
		    Width = 800;
			Height = 600;
		break;

	    case 0x114:
		    Width = 800;
			Height = 600;
		break;
		
	    case 0x115:
		    Width = 800;
			Height = 600;
		    break;
	
	    default:
		    Width = 800;
			Height = 600;
		    break;
	};    
	
	
	screenSetSize(Width,Height);
	
	// Continua... (outros parametros)
	
done:
    g_current_video_mode = (unsigned long) VideoMode;
    return;
};


/*
 * videoVideo:
 *     Método construtor.
 *     Funçao interna. 
 *     Confgura algumas variáveis.
 */
int videoVideo()
{
    videoStatus = 0;
    videoError = 0;
    //...
	
	
Done:	
	return (int) 0;
};


//
// End.
//

