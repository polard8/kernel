
// video.c
// Rotinas paga gerenciar os controladores de video.
// Crt, Vga ...


// See:
// https://wiki.osdev.org/Accelerated_Graphic_Cards

// # importante
// Essa deve ser a única maneira em que o sistema acessa
// o controlador de vídeo.
// Por aqui o sistema fará configurações no controlador
// e enviará dados para o lfb.

//
// == VGA =======================================================
//

/*
  
    This index lists the VGA's I/O ports in numerical order, 
    making looking up a specific I/O port access simpler.
 
    3B4h -- CRTC Controller Address Register
    3B5h -- CRTC Controller Data Register
    3BAh Read -- Input Status #1 Register
    3BAh Write -- Feature Control Register
    3C0h -- Attribute Address/Data Register
    3C1h -- Attribute Data Read Register
    3C2h Read -- Input Status #0 Register
    3C2h Write -- Miscellaneous Output Register
    3C4h -- Sequencer Address Register
    3C5h -- Sequencer Data Register
    3C7h Read -- DAC State Register
    3C7h Write -- DAC Address Read Mode Register
    3C8h -- DAC Address Write Mode Register
    3C9h -- DAC Data Register
    3CAh Read -- Feature Control Register
    3CCh Read -- Miscellaneous Output Register
    3CEh -- Graphics Controller Address Register
    3CFh -- Graphics Controller Data Register
    3D4h -- CRTC Controller Address Register
    3D5h -- CRTC Controller Data Register
    3DAh Read -- Input Status #1 Register
    3DAh Write -- Feature Control Register

See:
    https://web.stanford.edu/class/cs140/projects/pintos/specs/freevga/vga/portidx.htm
 */

// ================================

#include <kernel.h>

//@todo: Criar um arquivo para gerenciar fontes.
#define VIDEO_BIOS_FONT8X8_ADDRESS    0x000FFA6E
//#define VIDEO_BIOS_FONT8X16_ADDRESS (0x000FFA6E+??)
//...
#define VIDEO_BIOS_FONT8X8_WIDTH   8
#define VIDEO_BIOS_FONT8X8_HEIGHT  8
//...


//extern unsigned long SavedLFB;          //LFB address.  
//extern unsigned long SavedX;            //Screen width. 
//extern unsigned long SavedY;            //Screen height.
//extern unsigned long SavedBPP;          //Bits per pixel.

//
// Variáveis internas.
//

int videoStatus;
int videoError;
//...

// LFB - Esse é o endereço usado pelo driver de vídeo em /x
// para acessar o LFB, ou seja o frontbuffer.
// Lembrando que o driver de vídeo deve ser independente do 
// kernel então o kernel só poderá obter esse endereço se
// solicitar par asse driver.
// Mas o kernel não deve enviar dados para o frontbuffer,
// para isso ele deve usar esse driver.
// #importante: Esse driver poderá ser diferente para
// cada modelo de placa de vídeo.

unsigned long __frontbuffer_va;
unsigned long __frontbuffer_pa;  

//cga
unsigned long __cga_va;
unsigned long __cga_pa;  


int videoInit (void)
{
    int Status=0;

    // Se o modo de video nao esta habilitado
    if ( VideoBlock.useGui != TRUE )
    {
        // Can we use the function?
        panic("videoInit:\n");
    }

    g_useGUI          = TRUE;
    VideoBlock.useGui = TRUE;

//
// LFB
//

    // frontbuffer
    __frontbuffer_pa = (unsigned long) SavedLFB;
    __frontbuffer_va = (unsigned long) FRONTBUFFER_VA;
    g_frontbuffer_pa = (unsigned long) __frontbuffer_pa; 
    g_frontbuffer_va = (unsigned long) __frontbuffer_va;

//
// Backbuffer
//

    // backbuffer
    g_backbuffer_va  = (unsigned long) BACKBUFFER_VA;



    // Device screen sizes. 
    // (herdadas do boot loader.)
    // See: globals/gdevice.h

    g_device_screen_width  = (unsigned long) SavedX;
    g_device_screen_height = (unsigned long) SavedY;
    g_device_screen_bpp    = (unsigned long) SavedBPP;


    // gwsSetCurrentFontAddress ( VIDEO_BIOS_FONT8X8_ADDRESS );

    // #todo: 
    // Usar a função que configura essas variáveis.
    gcharWidth  = VIDEO_BIOS_FONT8X8_WIDTH;
    gcharHeight = VIDEO_BIOS_FONT8X8_HEIGHT;
    gfontSize   = FONT8X8;


    return 0;
    //return (int) Status;    
}


int videoVideo(void)
{
    videoStatus = 0;
    videoError = 0;
    //...
    return 0;
}


int Video_initialize(void)
{
    g_driver_video_initialized = FALSE;

    debug_print ("Video_initialize: [TODO]\n");

    videoVideo();
    videoInit();
    // ...

    // Done
    g_driver_video_initialized = TRUE;

    return 0;
}    

/*
 * videoGetMode: 
 *     Obtem o modo de video atual.
 */

//#todo
//isso pode ser incluido em 'get system parameters' system call.

unsigned long videoGetMode (void)
{
    return (unsigned long) g_current_video_mode;
}

/*
 * videoSetMode:
 *     Configura o modo de video atual.
 */

void videoSetMode (unsigned long mode)
{

    unsigned long VideoMode;
    unsigned long Width;
	unsigned long Height;
	//continua...(outros parametros)


    debug_print ("videoSetMode: [BUGBUG] This routine is wrong\n");


	
	VideoMode = (unsigned long) mode;
	
    //
	// todo: Check limits.
	//
	
	//if (){}
	

	//Se estiver nos limites.
	if ( VideoMode > 0 && VideoMode < 9000)
	{
		//g_current_video_mode = (unsigned long) VideoMode;
        g_video_mode = (unsigned long) VideoMode;
		VideoBlock.vesaMode = (unsigned long) VideoMode; 
		//...
	}

	//
	// @todo:
	// Organizar isso. Os valores atuais devem ser obtidos em real mode 
	// usando os recursos do VESA BIOS.
	//
	
    switch (VideoMode){
		
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

    screenSetSize (Width,Height);

	// Continua... (outros parametros)

    g_current_video_mode = (unsigned long) VideoMode;
}

/*
 * videoSetupCGAStartAddress:
 *     Configura o endereço inicial da memória de video em modo texto   
 *     fis=b8000  vir=??   #todo
 */

void videoSetupCGAStartAddress (unsigned long address)
{
    g_current_vm = (unsigned long) address;
	//g_current_cga_address
}



//
// End.
//
























