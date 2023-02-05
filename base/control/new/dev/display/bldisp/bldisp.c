
// bldisp.c
// bl display device

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
// == VGA =============================
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


int refresh_device_screen_flag=0;
int refresh_valid_screen_flag=0;


unsigned long screen_size_in_kb=0;
// hack: for debuging purpose
int g_use_fake_screen_size=0;
unsigned long fake_screen_size_in_kb=0;

// The refresh is enabled we mapped
// memory enough for that.
int refresh_screen_enabled=0;
// We need to flush the whole screen into the frontbuffer.
int screen_is_dirty=0;

unsigned long gSavedLFB=0;
unsigned long gSavedX=0;
unsigned long gSavedY=0;
unsigned long gSavedBPP=0;


// Private variables.
// Display device support.
static unsigned long screen_width=0;
static unsigned long screen_height=0;
static unsigned long screen_bpp=0;
static unsigned long screen_pitch=0;
//...

// The info comes from the gramado boot loader.
struct display_device_d *bl_display_device;


//@todo: Criar um arquivo para gerenciar fontes.
#define VIDEO_BIOS_FONT8X8_ADDRESS    0x000FFA6E
//#define VIDEO_BIOS_FONT8X16_ADDRESS (0x000FFA6E+??)
//...
#define VIDEO_BIOS_FONT8X8_WIDTH   8
#define VIDEO_BIOS_FONT8X8_HEIGHT  8
//...

// frontbuffer and backbuffer.
// see: gdef.h
unsigned long g_frontbuffer_pa=0;
unsigned long g_backbuffer_pa=0;



// LFB - Esse é o endereço usado pelo driver de vídeo em /x
// para acessar o LFB, ou seja o frontbuffer.
// Lembrando que o driver de vídeo deve ser independente do 
// kernel então o kernel só poderá obter esse endereço se
// solicitar par asse driver.
// Mas o kernel não deve enviar dados para o frontbuffer,
// para isso ele deve usar esse driver.
// #importante: Esse driver poderá ser diferente para
// cada modelo de placa de vídeo.


// private:
// We gotta build methods to get these values
// from outside.

static unsigned long __frontbuffer_va=0;
static unsigned long __frontbuffer_pa=0;
static unsigned long __cga_va=0;
static unsigned long __cga_pa=0;

#define VSYNC_INPORT  0x3DA

//
// == Private functions: Prototypes ========
//

static int __videoInit(void);
static char vsync_inb(int port);


// ============================

// vsync_inb: 
// Pega um byte na porta. 
static char vsync_inb(int port)
{
    char Value = 0;

    Value = (char) in8 (port); 

    asm (" nop \n");
    asm (" nop \n");
    asm (" nop \n");
    asm (" nop \n");

	//#todo: io_delay();

    return (char) Value;    
}

// ===============================


// Called by hal_vsync
void vsync (void)
{

	// Método 1
	//================================
	
	// while ( ( vsync_inb (0x3DA) & 8 ) != 8 );
	// while ( ( vsync_inb (0x3DA) & 8 ) == 8 );
	// return;
	
	// Método 2
	//================================
	
	// Checar se vsync foi gerado.

    unsigned long MaxDelay=0;

    out8 ( 0x3c4, 0 );

    if (  vsync_inb( 0x3c5 ) & 0x2 ) 
    {
        MaxDelay = 100000;
        while ( ( ( vsync_inb (0x3DA) & 8 ) == 8 ) && MaxDelay-- );

        MaxDelay = 100000;
        while ( ( ( vsync_inb (0x3DA) & 8 ) == 0  ) && MaxDelay-- );
    }
}





// Qual é o endereço virtual do início de uma dada linha da tela?
unsigned long screen_scanline_va(int scanline)
{
    unsigned long scanline_va=0;
    unsigned long start = FRONTBUFFER_VA;

// pitch
    unsigned long pitch = (unsigned long) screenGetHeight();
    if ( pitch == 0 ){
        panic ("screen_scanline_va: pitch limits");
    }

// height
    unsigned long height = (unsigned long) screenGetHeight();
    if ( height == 0 ){
        panic ("screen_scanline_va: height limits");
    }

    if (scanline >= height){
        panic ("screen_scanline_va: scanline limits");
    }

    scanline_va = (unsigned long) ( start + (pitch * scanline) );

// É o endereço virtual do início de uma dada linha da tela.
    return (unsigned long) scanline_va;
}

// Get screen width
unsigned long screenGetWidth (void)
{
    return (unsigned long) screen_width;
}

// Get screen height
unsigned long screenGetHeight (void)
{
    return (unsigned long) screen_height;
}

// Get screen bpp
unsigned long screenGetBPP (void)
{
    return (unsigned long) screen_bpp;
}

// Get screen pitch
unsigned long screenGetPitch (void)
{
    return (unsigned long) screen_pitch;
}


// screenSetSize:
//     Configura as dimensões da tela.
//     Tamanho do monitor.

void screenSetSize( unsigned long width, unsigned long height )
{
    screen_width  = (unsigned long) width;
    screen_height = (unsigned long) height;
}


/*
 * fb_refresh_screen:
 *     Coloca o conteúdo do BackBuffer no LFB da memória de vídeo.
 *     Ok, isso está no lugar certo. Pois somente
 *  O driver de vídeo pode acessar o LFB
 *  /x/video/screen.c 
 */
// backup.
// This is working very well.
// Copying long by long.
// ?? 
// Total size is wrong.
// Esse é mais rápido.
// #bugbug
// #danger
// Dependendo do tamanho da tela, 
// essa rotina pode acabar copiando conteúdo 
// para alguma parte não mapeada no lfb.
// Precisamos de limites. Obedecendo a quantidade mapeada.
// #bugbug
// Como temos apenas 2MB de lfb mapeados, 
// então vamos copiar menos dados pra evitar ultrapassar o limite
// e causar PF.
// #todo
// We can also use 16 bytes ... SSE?

void fb_refresh_screen (unsigned long flags)
{
    int i=0;
// Char. The slow way.
    unsigned char *backbuffer  = (unsigned char *) BACKBUFFER_VA;
    unsigned char *frontbuffer = (unsigned char *) FRONTBUFFER_VA;
// Long. The fast way.
    unsigned long *backbuffer_long  = (unsigned long *) BACKBUFFER_VA;
    unsigned long *frontbuffer_long = (unsigned long *) FRONTBUFFER_VA;

// We can't refresh.
// The buffer wasn't validated.
    if ( refresh_screen_enabled != TRUE ){
        debug_print_string("fb_refresh_screen: [FAIL-FIXME] refresh_screen_flag\n");
        return;
    }

    if ( gSavedX == 0 || gSavedY == 0 || gSavedBPP == 0 )
    {
        panic("fb_refresh_screen: display info\n");
    }

// #todo
// Isso significa que só poderemos 
// usar o modo 320x200 por enquanto.
// clipping:
// Podemos recortar, e mesmo que a resoluçao seja alta,
// somente escreveremos nos primeiros 2mb ...
// Isso seria divertido, a velocidade seria alta,
// mas teriamos uma tela recortada. kkk
// Essa tecnica pode ser uma opçao configuravel

    //int Total = (int)(gSavedX*gSavedBPP*gSavedY);
    int Total = 
        (int) (screen_size_in_kb * 1024);


/*
// nao pode ser mais que 2mb
    //if ( Total >= (2*1024*1024) )
    if (Total >= 2097152 ){
        debug_print_string("fb_refresh_screen: [FAIL-FIXME] Total\n");
        return;
    }
*/
// Se algo deu errado 
// e realmente precisamos de alguma tela
// para debug na inicializaçao.
// entao vamos limitar o tamanho do refresh screen
// isso ajuda no refresh screen, mas nao em outras rotinas graficas.
    if ( g_use_fake_screen_size == TRUE)
    {
        //fake_screen_size_in_kb = (( 320*4*200 )/1024);
        Total = (int) (fake_screen_size_in_kb * 1024);
    }

// nao pode ser mais que 2mb
    if (Total >= 2097152 ){
        debug_print_string("fb_refresh_screen: [FAIL-FIXME] Total\n");
        return;
    }

//
// Refresh
//

// Vertical synchonization?
//  if(flags & 1)
    vsync();

// Fast way ?
// Divisible by 8. So use the fast way.

    int FastTotal=0;
    if ( (Total % 8) == 0 )
    {
        FastTotal = (int) (Total >> 3);
        for ( i=0; i<FastTotal; i++ ){
            frontbuffer_long[i] = backbuffer_long[i];
        };
        return;
    }

// Slow way.
// One byte per time.
    for ( i=0; i<Total; i++ ){
        frontbuffer[i] = backbuffer[i];
    };

    return;
}   


void refresh_screen (void)
{
    fb_refresh_screen(0);
}

// The whole screen is dirty.
// It can be flushed into the framebuffer.
void invalidate_screen(void)
{
    screen_is_dirty = TRUE;
}

/*
 * screenInit:
 *     Inicializando o gerenciamento de tela.
 */ 
// #bugbug
// Screen is a reagion in the display, or in many displays.
// Display is a monitor, or a set o hid in a given host.

int screenInit(void)
{
    debug_print ("screenInit:\n");

// Validate the whole screen
// We don't need to flush the screen yet.
    screen_is_dirty = FALSE;

// Configura globais com base nos valores passados pelo Boot Loader.
    screenSetSize( 
        (unsigned long) gSavedX, 
        (unsigned long) gSavedY );

    screen_bpp = gSavedBPP;
    screen_pitch = ( gSavedBPP * gSavedX );
    //...
    return 0;
}

//==============================

// Called by init.c
int bldisp_initialize(void)
{
// Initialize bl display device.

    bl_display_device = 
        (struct display_device_d *) kmalloc ( sizeof(struct display_device_d) ); 

    // Memory allocation for Display device structure.
    if ( (void*) bl_display_device == NULL ){
        x_panic ("Error: 0x05");
    }

// xBootBlock was initialized by init.c
    if (xBootBlock.initialized != TRUE){
        x_panic ("bldisp_initialize: xBootBlock");
    }

// framebuffer address.
    bl_display_device->framebuffer_pa = (unsigned long) xBootBlock.lfb_pa;
    bl_display_device->framebuffer_va = (unsigned long) FRONTBUFFER_VA;
// w, h, bpp.
    bl_display_device->framebuffer_width  = (unsigned long) xBootBlock.deviceWidth;
    bl_display_device->framebuffer_height = (unsigned long) xBootBlock.deviceHeight;
    bl_display_device->framebuffer_bpp   = (unsigned long) xBootBlock.bpp;
// pitch
    bl_display_device->framebuffer_pitch = 
        (unsigned long) ( xBootBlock.deviceWidth * xBootBlock.bpp );
// size in bytes.
    bl_display_device->framebuffer_size_in_bytes =
        (unsigned long) ( bl_display_device->framebuffer_pitch * bl_display_device->framebuffer_height );

// validation
    bl_display_device->used = TRUE;
    bl_display_device->magic = 1234;
    return 0;
}


static int __videoInit(void)
{
    int Status=0;

// Se o modo de video nao esta habilitado
    if (VideoBlock.useGui != TRUE)
    {
        // Can we use the function?
        // No we can't
        //panic("videoInit:\n");
        debug_print("__videoInit:\n");
        asm ("cli \n");
        while(1){ asm("hlt"); }
    }

    g_useGUI          = TRUE;
    VideoBlock.useGui = TRUE;

//
// LFB
//

// frontbuffer
    __frontbuffer_pa = (unsigned long) gSavedLFB;
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

    g_device_screen_width  = (unsigned long) gSavedX;
    g_device_screen_height = (unsigned long) gSavedY;
    g_device_screen_bpp    = (unsigned long) gSavedBPP;

    // gwsSetCurrentFontAddress ( VIDEO_BIOS_FONT8X8_ADDRESS );

// #todo: 
// Usar a função que configura essas variáveis.
    gcharWidth  = VIDEO_BIOS_FONT8X8_WIDTH;
    gcharHeight = VIDEO_BIOS_FONT8X8_HEIGHT;
    gfontSize   = FONT8X8;

    return 0;
    //return (int) Status;    
}

int Video_initialize(void)
{
    g_driver_video_initialized = FALSE;
    __videoInit();
    // ...
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
    unsigned long VideoMode=0;
    unsigned long Width=0;
    unsigned long Height=0;
    //continua...(outros parametros)

    debug_print ("videoSetMode: [FIXME] This routine is wrong\n");

    VideoMode = (unsigned long) mode;

//
// todo: Check limits.
//

    //if (){}

// Se estiver nos limites.
    if ( VideoMode > 0 && VideoMode < 9000)
    {
        //g_current_video_mode = (unsigned long) VideoMode;
        g_video_mode = (unsigned long) VideoMode;
        VideoBlock.vesaMode = (unsigned long) VideoMode; 
        //...
    }

// #todo:
// Organizar isso. Os valores atuais devem ser obtidos em real mode 
// usando os recursos do VESA BIOS.

// #bugbug
// This is is very wrong.
// We need to get these values in the controller.

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

