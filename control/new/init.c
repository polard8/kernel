
// init.c
// (Next Ten)

// This file contains the kernel_main function,
// called by START in 
// entrance/warden/unit0/x86_64/head_64.asm.
// This file and their folder will be the control panel
// for the initialization routine.
// Please put here data we need.
// fake main.c
// We need a fake KERNEL.BIN ELF file that will be used my the
// boot loader.
// The boot loader will load the fake kernel image before
// setting up the long mode and the paging.

// The main subsystem is the window system GWSSRV.BIN.
// The first usermode application is GWS.BIN.
// See:
// GWSSRV.BIN: prestier/gws/server
// GWS.BIN:    prestier/gws/client

// #bsod
// List of errors:
// Error: 0x00 - Unexpected error.
// Error: 0x01 - CURRENT_ARCH_X86_64 initialization fail.
// Error: 0x02 - generic.
// Error: 0x03 - Undefined 'current arch'.
// Error: 0x04 - The kernel image is too long.
// Error: 0x05 - Memory allocation for Display device structure.
// ...



#include <kernel.h>


//
// Initialization :)
//

// Global
//unsigned long gInitializationPhase=0;

// No pointer.
struct initialization_d  Initialization;


#define GCC_VERSION ( __GNUC__ * 10000 \
            + __GNUC_MINOR__ * 100 \
            + __GNUC_PATCHLEVEL__ )


//static char *s_hostname;
//#define PLATFORM_STRING                 "x64"


#define RELEASE_TYPE_NULL  0
#define RELEASE_TYPE_RC    1
#define RELEASE_TYPE_BETA  2

// ==========================

//
// Import from linker
//

// Não queremos um tamanho de imagem que
// exceda o tamanho da região de memória mapeada para ela.
// No futuro poderemos usar as informações que estão dentro
// do header ELF.
// See: link.ld
static int ImportDataFromLinker = TRUE;

extern unsigned long start_of_kernel_image(void);
extern unsigned long end_of_kernel_image(void);

extern unsigned long kernel_begin(void);
extern unsigned long kernel_end(void);

extern unsigned long code_begin(void);
extern unsigned long code_end(void);

extern unsigned long rodata_begin(void);
extern unsigned long rodata_end(void);

extern unsigned long data_begin(void);
extern unsigned long data_end(void);

extern unsigned long bss_begin(void);
extern unsigned long bss_end(void);

// ==========================

static unsigned long KernelImageSize=0;

static unsigned long KernelImage_Size=0;
static unsigned long KernelImage_CODE_Size=0;
static unsigned long KernelImage_RODATA_Size=0;
static unsigned long KernelImage_DATA_Size=0;
static unsigned long KernelImage_BSS_Size=0;

// ==========================



//char InitialUserProcessName[32] = "INIT.BIN"

// ??
// #bugbug
// Explain it better.
// Someone is setting this variable from another document.
// Change the name.
// See: head_64.asm.
unsigned long magic;

// virtual = physical.
#define BootBlockVA    0x0000000000090000
#define bbOffsetLFB_PA  0  // offset 0
#define bbOffsetX       1  // offset 8
#define bbOffsetY       2  // offset 16
#define bbOffsetBPP     3  // offset 24
#define bbLastValidPA   4  // offset 32  // Last valid physical address.
#define bbGramadoMode   5  // offset 40  // jail, p1, home ...
// ...


// See:
// xxxhead.asm
extern void x84_64_initialize_machine(void);

// Local boot structure.
struct x_boot_block_d
{
    int initialized;
    unsigned long lfb_pa;
    unsigned long deviceWidth;    // in pixels
    unsigned long deviceHeight;   // in pixels
    unsigned long bpp;            // bytes per pixel
    unsigned long last_valid_pa;  // Last valid physical address.
    unsigned long gramado_mode;   // system mode.
    // ...
};
struct x_boot_block_d  xBootBlock;


// ================================


//
// == Private functions: Prototypes ========
//

// Preinit routines.
static int preinit(void);
static int preinit_SetupBootblock(void);
static void preinit_Globals(int arch_type);
static void preinit_OutputSupport(void);
static void preinit_Serial(void);

// Booting routines.
static int booting_begin(int arch_type);
static int booting_end(int arch_type);

// System initialization routines.

static int __setup_cmdline(void);
static void __enter_debug_mode(void);

// ================================

static int __setup_cmdline(void)
{
    char cmdline[64];

    memset(cmdline, 0, 64);  

    if ( (void*) stdin == NULL )
        return -1;

    if (stdin->magic!=1234)
        return -1;

// The string.
    mysprintf(cmdline,"Hello from kernel");
    cmdline[63]=0;
    
//rewind. 
// See: kstdio.c
    k_fseek( stdin, 0, SEEK_SET );

// Write
    file_write_buffer( stdin, cmdline, 64 );

    return 0;
}

static void __enter_debug_mode(void)
{
    if( Initialization.serial_log == TRUE ){
        PROGRESS("__enter_debug_mode:\n");
    }

    if( Initialization.console_log != TRUE )
    {
        if( Initialization.serial_log == TRUE ){
            PROGRESS("__enter_debug_mode: can't use the cirtual console\n");
        }
    }

    if( Initialization.console_log == TRUE )
    {
        printf("init.c: The kernel is in debug mode.\n");
        refresh_screen();
        
        kgwm_early_kernel_console();
        
        printf("init.c: End of debug mode.\n");
        refresh_screen();
        
        die();
    }

    die();
}

// Last step:
// This function stays in the top of this document.
static int booting_end(int arch_type)
{

// Open the kernel virtual console 
// instead of first process.
// We can receive this flag via command line.

    //int UseDebugMode=TRUE;
    int UseDebugMode=FALSE;

    PROGRESS("booting_end:\n");

// Final message before jumping to init process.
    printf("booting_end:\n");
    refresh_screen();
    //while(1){}

// Setup command line for the init process.
    __setup_cmdline();

// Clear the screen again.
    Background_initialize(COLOR_KERNEL_BACKGROUND); 

// ::: Initialization on debug mode.
// Initialize the default kernel virtual console.
// It depends on the run_level.
// See: kgwm.c

    if ( UseDebugMode == TRUE ){
        __enter_debug_mode();
    }

    switch (arch_type){
        
        case CURRENT_ARCH_X86_64:
            // Do not return!
            I_x64ExecuteInitialProcess();
            break;
        default:
            panic("booting_end: arch_type\n");
            break;
    };

    return FALSE;
}


static void preinit_Globals(int arch_type)
{
// Initializing the global spinlock.

    __spinlock_ipc = TRUE;

// IO Control

    IOControl.useTTY = FALSE;        // Model not implemented yet.
    IOControl.useEventQueue = TRUE;  // The current model.
    IOControl.initialized = TRUE;    // IO system initialized.

// Scheduler policies
// Early initialization.
// See: 
// sched.h, sched.c.

    SchedulerInfo.policy = SCHED_RR;
    SchedulerInfo.flags  = (unsigned long) 0;

    // ...
}


static void preinit_Serial(void)
{
// #todo: Check status.
    serial_init();
    debug_print("preinit_Serial: Initialized\n");
}


static void preinit_OutputSupport(void)
{
    PROGRESS("preinit_OutputSupport:\n");

// Virtual Console.
// See: user/console.c
    //debug_print ("preinit_OutputSupport:\n");

// O refresh ainda não funciona, 
// precisamos calcular se a quantidade mapeada é suficiente.

    refresh_screen_enabled = FALSE;

// As estruturas de console sao estruturas de tty,
// mas sao um array de estruturas, nao precisa de malloc,
// por isso podem ser chamadas nesse momento.
// #test
// We need to test it better.

    PROGRESS("preinit_OutputSupport: VirtualConsole_initialize\n");
    VirtualConsole_initialize();

// #IMPORTAT: 
// We do not have all the runtime support yet.
// We can't use printf yet.
}


// ------------------------------
// kmain:
// Called by START in arch/x86_64/entrance/head_64.asm.
// See: kernel.h

int kmain(int arch_type)
{
    int Status=FALSE;

    asm ("cli");

// Starting the counter.
    Initialization.current_phase = 0;


/*
    char hostname[64];
    sprintf(hostname,"gramado");
    s_hostname = (char *) &hostname[0];
*/

// Setup debug mode.
// Enable the usage of the serial debug.
// It is not initialized yet.

    //enable_serial_debug();
    disable_serial_debug();

//
// Presence level
//

// See:
// sched.h, sched.c

    // (timer ticks / fps) = level

    //presence_level = (1000/1000);  //level 1;    // 1000   fps
    //presence_level = (1000/500);   //level 2;    // 500    fps
    //presence_level = (1000/250);   //level 4;    // 250    fps
    //presence_level = (1000/125);   //level 8;    // 125    fps
    //presence_level = (1000/62);    //level 16;   // 62,20  fps
    //presence_level = (1000/25);    //level 32;   // 31,25  fps
    //presence_level = (1000/15);    //level 64;   // 15,625 fps 
    //presence_level = (1000/10);    //level 100;   // 10 fps
    //presence_level = (1000/5);     //level 200;   // 5  fps
    // presence_level = (1000/4);     //level 250;  // 4  fps
    //presence_level = (1000/2);     //level 500;   // 2  fps
    //presence_level = (1000/1);     //level 1000;  // 1  fps

    //set_update_screen_frequency(30);
    set_update_screen_frequency(60);
    //set_update_screen_frequency(120);

// ==================




// Preinit
    preinit();

// Booting ...

    current_arch = CURRENT_ARCH_X86_64;

    Status = (int) booting_begin(current_arch);

    if (Status==TRUE){
        Status = (int) booting_end(current_arch);
    }

    if (Status != TRUE)
    {
        // panic screen
        // Mostramos informações completas ou
        // permitimos a inicialização de outro modo,
        // talvez algum modo de recuperação ou simplificado.
 
        if( Initialization.serial_log == TRUE ){
            PROGRESS("kmain: booting_end fail\n");
        }
        if( Initialization.console_log == TRUE )
        {
            printf("kmain: booting_end fail\n");
            printf("kmain: Trying debug mode\n");
            __enter_debug_mode();
        }
        die();
    }

// Final messages
    if( Initialization.serial_log == TRUE ){
        PROGRESS("kmain: [final message] FAILURE\n");
    }
    if( Initialization.console_log == TRUE ){
        printf("kmain: [final message] FAILURE\n");
        refresh_screen();
    }

    system_state = SYSTEM_DEAD;

// Retorna para o assembly e para em hlt.
// see: _kernel_begin in head_64.asm.

    return FALSE;
}


// limitation: No serial debug yet.
// #todo: #bugbug
// We have another BootBlock structure in info.h
static int preinit_SetupBootblock(void)
{
// ---------------------------

// Magic
// #bugbug: Explain it better.
    unsigned long bootMagic = 
        (unsigned long) (magic & 0x00000000FFFFFFFF); 

// The boot block address. 0x0000000000090000.
// Each entry has 8 bytes.
// virtual = physical.
    unsigned long *xxxxBootBlock = (unsigned long*) BootBlockVA; 

// lfb
// Esse endereço virtual foi configurado pelo bootloader.
// Ainda não configuramos a paginação no kernel.

    unsigned long *fb = (unsigned long *) FRONTBUFFER_VA; 
    fb[0] = 0x00FFFFFF;

// Check magic
// Paint a white screen if magic is ok.
// Paint a colored screen if magic is not ok.
    int i=0;

// WHITE
    if ( bootMagic == 1234 )
    {
        //for (i=0; i<320; i++)
        for (i=0; i<320*50; i++)
        {
            fb[i] = 0xFFFFFFFFFFFFFFFF;
        };
    }

// COLORED
    if ( bootMagic != 1234 )
    {
        for (i=0; i<320*50; i++){
            fb[i] = 0xFF00FFFFFFF00FFF;
        };
    }

// Boot block (local structure)
// Saving the boot block
// Structure in this document.
// We will have a global one in gdef.h

    xBootBlock.lfb_pa        = (unsigned long) xxxxBootBlock[bbOffsetLFB_PA];
    xBootBlock.deviceWidth   = (unsigned long) xxxxBootBlock[bbOffsetX];
    xBootBlock.deviceHeight  = (unsigned long) xxxxBootBlock[bbOffsetY];
    xBootBlock.bpp           = (unsigned long) xxxxBootBlock[bbOffsetBPP];
    xBootBlock.last_valid_pa = (unsigned long) xxxxBootBlock[bbLastValidPA];
    xBootBlock.gramado_mode  = (unsigned long) xxxxBootBlock[bbGramadoMode];
    xBootBlock.initialized = TRUE;

// ------------------------------------------------------

// Gramado mode.
// Gramado mode. (jail, p1, home ...)
// Save global variable.

    current_mode = (unsigned long) xBootBlock.gramado_mode;

    // ...

// resolution
// global variables.
// See: kernel.h

    gSavedLFB = (unsigned long) xBootBlock.lfb_pa;
    gSavedX   = (unsigned long) xBootBlock.deviceWidth;
    gSavedY   = (unsigned long) xBootBlock.deviceHeight;
    gSavedBPP = (unsigned long) xBootBlock.bpp;

// Memory support.

// Last valid physical address.
// Used to get the available physical memory.
    blSavedLastValidAddress = (unsigned long) xBootBlock.last_valid_pa; 
// Memory size in KB.
    blSavedPhysicalMemoryInKB = (blSavedLastValidAddress / 1024);

// #todo
// Setup the real boot block structure at gdef.h
// BootBlock

    screenSetSize (gSavedX,gSavedY);


// teste para a máquina real.
// preto

/*
    //if ( xBootBlock.deviceWidth == 320 )
    //{
        for (i=0; i< 320*25; i++)
        {
            fb[i] = 0;
        };
    //}

*/
    // # ======== DEBUG =============
    // #todo
    // The initialization in the real machine
    // crashes here for the resolution 320x200
    // gramado mode: jail


//#debug
// Let's print some BLACK over the WHITE BAR.
    //while(1){}

// ========= funciona ate aqui na maq real ========================



// ----------------------------------------------
    return 0;
}


static int preinit(void)
{
    system_state = SYSTEM_PREINIT;


// Checkpoints
    Initialization.phase1_checkpoint = FALSE;
    Initialization.phase2_checkpoint = FALSE;
    Initialization.phase3_checkpoint = FALSE;
    Initialization.hal_checkpoint = FALSE;
    Initialization.microkernel_checkpoint = FALSE;
    Initialization.executive_checkpoint = FALSE;
    Initialization.gramado_checkpoint = FALSE;

// Flags
    Initialization.serial_log = FALSE;
    Initialization.console_log = FALSE;

// Hack Hack
    VideoBlock.useGui = TRUE;

// first of all
// Getting critical boot information.
    preinit_SetupBootblock();

// We do not have serial debug yet.
    preinit_Globals(0);  // IN: arch_type

// Serial debug support.
    preinit_Serial();
    PROGRESS("preinit: Serial debug initialized\n");

// Initialize the virtual console structures.
// We do not have all the runtime support yet.
// We can't use printf yet.
    PROGRESS("preinit: preinit_OutputSupport\n");
    preinit_OutputSupport();

    return 0;
}


static int booting_begin(int arch_type)
{
    int Status = (-1);

    system_state = SYSTEM_BOOTING;

    PROGRESS("booting_begin:\n");

    printf("booting_begin:\n");

// boot info
    if (xBootBlock.initialized != TRUE){
        panic ("booting_begin: xBootBlock.initialized\n");
    }

// #IMPORTAT: 
// We do not have all the runtime support yet.
// We can't use printf yet.

// =================================================
// Show some basic info.

// #todo
// The mode.
    //debug_print ("mode: ");
    //debug_print ("\n");

// #todo
// The architecture.
    //debug_print ("arch: ");
    //debug_print ("\n");

//
// Pixel
//

    //ok
    //backbuffer_putpixel(COLOR_WHITE,100,100,0);
    //backbuffer_putpixel(COLOR_WHITE,150,150,0);
    //backbuffer_putpixel(COLOR_WHITE,160,160,0);

//
// Refresh sceen
//
    //refresh_screen();

// Video support
// See: drivers/video/video.c


    //#breakpoint: BLACK ON WHITE.
    //ok, funcionou na maq real no modo jail, provavelmente 320x200.
    //for (i=0; i< 320*25; i++){ fb[i] = 0; };
    //while(1){asm("hlt");};

    PROGRESS("booting_begin: Video_initialize\n");
    Video_initialize();

// Runtime
// #bugbug:
// We need the runtime initialization for the messages.
// What about to initialize it early?! now!!!!
// #bugbug
// Here the background is not initialized yet,
// so, we have a lot of dirty things.
// See: ke/runtime.c

    //#breakpoint: BLACK ON WHITE.
    //ok, funcionou na maq real no modo jail, provavelmente 320x200.
    //Ainda nao podemos usar o refresh screen porque a
    //flag refresh_screen_enabled ainda nao foi acionada.
    //for (i=0; i< 320*25; i++){ fb[i] = 0; };
    //while(1){asm("hlt");};

// Runtime:
// System memory support.
// Heap, stack, memory usage and frames.

// #hackhack
    current_arch = CURRENT_ARCH_X86_64;

    PROGRESS("booting_begin: Runtime_initialize\n");
    Runtime_initialize(current_arch);

// =========================
// Clear the screen.
// print some basic info.
// Setup printing resources.


// Setup Default kernel font.
// ROM BIOS 8x8 font.
// see: font.c

    PROGRESS("booting_begin: gwsInitializeDefaultKernelFont\n");
    gwsInitializeDefaultKernelFont();

// Initializing background for the very first time.
// See: bg.c

    PROGRESS("booting_begin: Background_initialize\n");
    Background_initialize(COLOR_KERNEL_BACKGROUND);

// No refresh screen yet!
// Ainda nao podemos usar o refresh screen porque a
// flag refresh_screen_enabled ainda nao foi acionada.
// Eh o que vamos fazer agora,
// de acordo com o tamanho da memoria disponivel pra isso.

// ++
// ======================================
// Screen size
// #importante
// Essa rotina calcula a memória que precisamos
// e nos diz se podemos usar o refresh screen.
// Isso habilita o uso do console como verbose para log.

    unsigned long bytes_per_pixel = 0;
    unsigned long pitch = 0;
    unsigned long sz_in_kb = 0;

    refresh_screen_enabled = FALSE;
    screen_size_in_kb = 0;

    if ( xBootBlock.bpp == 24 || 
         xBootBlock.bpp == 32 )
    {
        bytes_per_pixel = (xBootBlock.bpp / 8); 
        pitch = (xBootBlock.deviceWidth * bytes_per_pixel);
    }  

// pitch fail,
// don't stop, the real machine needs some kind of
// message support.

    if (pitch == 0){
        refresh_screen_enabled = FALSE;
        debug_print("Screen size fail. pitch\n");
    }

// Quantos kb vamos precisar para uma tela nessa resoluçao?
    sz_in_kb = 
        (unsigned long) (( pitch * xBootBlock.deviceHeight )/ 1024 );

// Screen size in kb.
// Remember: For now we only have 2048 kb mapped for lfb.
    screen_size_in_kb = sz_in_kb;

    // #debug
    //printf ("Screen size: %d KB\n", sz_in_kb);
 
// Se a quantidade usada por uma tela nessa resoluçao
// for maior que o que temos disponivel.
// Entao nao podemos habilitar o refresh screen.

    if ( sz_in_kb >= 2048 ){
        refresh_screen_enabled = FALSE;
        debug_print ("Screen size fail sz_in_k\n");
    }

// ok
// Ok We can use the refresh routine.
// Because we have memory enough for that.

    if ( sz_in_kb < 2048 ){
        refresh_screen_enabled = TRUE;  
    }
    
// ======================================
// --

//
// Full console initialization.
//

// We can't live without this.
// But the real machine needs the message support,
// so, we can't stop here. Let's hack for a now.

/*
    if ( refresh_screen_enabled != TRUE )
    {
        debug_print("kernel_main: refresh_screen_enabled != TRUE\n");
        Initialization.console_log = FALSE;
        while(1){asm("hlt");};
        //die(); //we dont have refresh screen support,
    }
*/

// #hackhack
// Nesse caso a rotina de refreshscreen vai usar
// um tamanho falso de tela, bem pequeno, que
// cabe na memoria mapeada disponivel.
// Isso sera usado para debug em ambiente
// que tivermos problemas.
// tudo isso se resolvera quando mapearmos memoria
// o suficiente para resoluçoes grandes.
    if ( refresh_screen_enabled != TRUE )
    {
        // enough for 320x200x32bpp
        fake_screen_size_in_kb = (( 320*4*200 )/1024);
        g_use_fake_screen_size = TRUE;
        refresh_screen_enabled = TRUE;
    }

// =================================
// Console:
// We have a virtual console and we can use the printf.
// This is the first message in the screen.
// see: tty/console.c

    Initialization.console_log = TRUE;
    console_banner(0);
    printf("gcc: %d\n",GCC_VERSION);
    printf ("Width:%d Height:%d BPP:%d\n",
        xBootBlock.deviceWidth,
        xBootBlock.deviceHeight,
        xBootBlock.bpp );

// Breakpoint
    //refresh_screen();
    //while(1){}

// #temp
// Supported widths. 800, 640, 320.

    if ( xBootBlock.deviceWidth != 800 &&
         xBootBlock.deviceWidth != 640 &&
         xBootBlock.deviceWidth != 320 )
    {
        panic("booting_begin: Unsupported resolution\n");
    }

// Show gramado mode.

    printf ("gramadomode:%d\n",current_mode);

    switch (current_mode){
// #temp
// Supported gramado mode.
    case GRAMADO_JAIL:
    case GRAMADO_P1:
    case GRAMADO_HOME:
        break;
// #temp
// Unsupported gramado mode. (yet)
    case GRAMADO_P2:
    case GRAMADO_CASTLE:
    case GRAMADO_CALIFORNIA:
        panic("booting_begin: Unsupported gramado mode\n");
        break;
// Undefined gramado mode.
    default:
        panic("booting_begin: Undefined gramado mode\n");
        break;
    }

// Breakpoint
    //refresh_screen();
    //while(1){}
    
// ================================================

// #todo
// Isso deve ter uma flag no aquivo de configuração.
// config.h i guess.

    if ( ImportDataFromLinker == TRUE )
    {
        //printf("\n");
 

        //KernelImageSize = (start_of_kernel_image - end_of_kernel_image);
        //printf ("Image Size %d KB \n",KernelImageSize/1024);

        //-------------

        // Não queremos um tamanho de imagem que
        // exceda o tamanho da região de memória mapeada para ela.

        KernelImage_Size = (kernel_end - kernel_begin);
        //printf ("Image Size %d KB \n",KernelImage_Size/1024);

        // .text
        KernelImage_CODE_Size = (code_end - code_begin);
        //printf ("CODE Size %d KB \n",KernelImage_CODE_Size/1024);

        // .rodata
        KernelImage_RODATA_Size = (rodata_end - rodata_begin);
        //printf ("RODATA Size %d KB \n",KernelImage_RODATA_Size/1024);

        // .data
        KernelImage_DATA_Size = (data_end - data_begin);
        //printf ("DATA Size %d KB \n",KernelImage_DATA_Size/1024);

        // .bss
        KernelImage_BSS_Size = (bss_end - bss_begin);
        //printf ("BSS Size %d KB \n",KernelImage_BSS_Size/1024);

        // Limit 1 MB
        // The kernel image is too long.
        if ( KernelImage_Size/1024 > 1024 )
        {
            panic ("Error 0x04: Image size");
        }
        
        // Address limit for the kernel image.
        // See: x64gva.h
        if( kernel_end > KERNEL_HEAP_START )
        {
            panic ("Error 0x04: kernel_end");
        }

        // #debug: breakpoint
        //refresh_screen();
        //while(1){}
    }


// =====================================

// Display device
// See:
// halvid.h
// gva.h
// Todas essas informações devem ser passadas pelo Gramado Boot Loader.

    PROGRESS("booting_begin: Background_initialize\n");

    printf("booting_begin: Setup display device\n");

    GramadoDisplayDevice = 
        (struct display_device_d *) kmalloc ( sizeof(struct display_device_d) ); 

    // Memory allocation for Display device structure.
    if ( (void*) GramadoDisplayDevice == NULL ){
        x_panic ("Error: 0x05");
    }

// framebuffer address.
    GramadoDisplayDevice->framebuffer_pa = (unsigned long) xBootBlock.lfb_pa;
    GramadoDisplayDevice->framebuffer_va = (unsigned long) FRONTBUFFER_VA;
 
// w, h, bpp.
    GramadoDisplayDevice->framebuffer_width  = (unsigned long) xBootBlock.deviceWidth;
    GramadoDisplayDevice->framebuffer_height = (unsigned long) xBootBlock.deviceHeight;
    GramadoDisplayDevice->framebuffer_bpp    = (unsigned long) xBootBlock.bpp;

// pitch
    GramadoDisplayDevice->framebuffer_pitch = 
        (unsigned long) ( xBootBlock.deviceWidth * xBootBlock.bpp );

// size in bytes.
    GramadoDisplayDevice->framebuffer_size_in_bytes =
        (unsigned long) ( GramadoDisplayDevice->framebuffer_pitch * GramadoDisplayDevice->framebuffer_height );


// Is it a valid screen pointer?
    GramadoDisplayDevice->screen = (struct screen_d *) CurrentScreen;

// validation
    GramadoDisplayDevice->used = TRUE;
    GramadoDisplayDevice->magic = 1234;


//=============================
// Initialize current archtecture.

    //printf("Plataform: %s\n", PLATFORM_STRING );

// #todo
// A partir daqui faremos inicializações de partes
// dependentes da arquitetura.

    // Hack hack
    // Também sado por outras rotinas dainicialização.
    //current_arch = CURRENT_ARCH_X86_64;

    switch (arch_type){

    // See: x64init.c in ke/arch/x86_64/
    case CURRENT_ARCH_X86_64:
        //debug_print ("kernel_main: [CURRENT_ARCH_X86_64] calling x64main() ...\n");
        Background_initialize(COLOR_KERNEL_BACKGROUND);  // again
        Status = (int) I_x64main();
        if (Status == TRUE){
            // Do not return!
            //booting_end(CURRENT_ARCH_X86_64);
            
            //ok
            return TRUE;
        }
        debug_print ("kernel_main: CURRENT_ARCH_X86_64 fail\n");
        x_panic("Panic: Error 0x01");
        //#todo: return -1;
        break;

    // See:
    // armmain (); ??

    // ...

    default:
        debug_print ("kernel_main: Current arch not defined!\n");
        //system_state = SYSTEM_ABORTED;
        x_panic("Error 0x03");
        //#todo: return FALSE;
        break;
    };

//=============================

    //ok
    //debug_print ("kernel_main: Testing reboot\n");
    //hal_reboot();

    //void *buff;
    //buff = (void*) kmalloc(1024*512);
    //if ( (void*) buff != NULL ){ debug_print ("kmalloc OK\n"); }
    //if ( (void*) buff == NULL ){ debug_print ("kmalloc FAIL\n"); }


    //console_outbyte('z',fg_console);




    //int x= 0x2345;
    //char *s ="String";
    //char b[512];
    
    //printf("kernel_main: info ::\n");
    
    //kinguio_printf("kernel_main: *breakpoint %x %s\n",x,s);
    //mysprintf(b,"Testing string \n");
    //kinguio_printf("kernel_main:  %s\n",b);

    //printf("kernel_main: *breakpoint %x %s\n",x,s);
    //sprintf(b,"Testing string \n");
    //sprintf(b,"Testing string2: %x\n",x);
    //printf("kernel_main:  %s\n",b);

    //printf ("LFB PA = %x \n",xBootBlock.lfb_pa );
    //printf ("Width  = %d \n",xBootBlock.deviceWidth );
    //printf ("Height = %d \n",xBootBlock.deviceHeight );
    //printf ("BPP    = %d \n",xBootBlock.bpp );
    //printf ("last valid pa = %d \n",xBootBlock.last_valid_pa);

    //refresh_screen();
    //while(1){}


    /*
    // Antecipado
    // ++
    // ======================================
    // Screen size
    
    unsigned long bytes_per_pixel = 0;
    unsigned long pitch = 0;
    unsigned long sz_in_kb = 0;

    refresh_screen_enabled = FALSE;
    screen_size_in_kb = 0;

    if ( xBootBlock.bpp == 24 || xBootBlock.bpp == 32 )
    {
        bytes_per_pixel = (xBootBlock.bpp / 8); 
        pitch = (xBootBlock.deviceWidth * bytes_per_pixel);
    }  

    if ( pitch == 0){
        refresh_screen_enabled = FALSE;
        printf ("Screen size fail. pitch\n");
    }

    if ( pitch != 0){
        
        sz_in_kb = (unsigned long) (( pitch * xBootBlock.deviceHeight )/ 1024 );
        screen_size_in_kb = sz_in_kb;
        
        printf ("Screen size: %d KB\n", sz_in_kb);
        
        // fail.
        if ( sz_in_kb >= 2048 ){
            refresh_screen_enabled = FALSE;
            printf ("Screen size fail sz_in_k\n");
        }
    
        // ok
        if ( sz_in_kb < 2048 ){
            refresh_screen_enabled = TRUE;  
        }
    }
    // ======================================
    // --
    */



// =====================================

// Final message.

    printf("\n");
    printf("init.c: Kernel initialization fail\n\n");
    refresh_screen();

// Show process info if it's valid.

    if( (void*) KernelProcess != NULL )
    {
        if(KernelProcess->magic==1234)
        {
            set_current_process(KernelProcess->pid);
            show_currentprocess_info();
            refresh_screen();
        }
    }

// hang.

    //while (1){
    //    asm ("cli");
    //    asm ("hlt");
    //};

// ===========================================

//
// Fail
//

// Rule 22:
// " When in doubt, know your way out. "

// Full console support.
fail2:
    //printf ("kernel_main: Fail. *HANG\n");
    //refresh_screen();

// Only serial debug support.
fail1:
    PROGRESS("Kernel:0:0\n"); 
    debug_print ("[Kernel] kernel_main-fail:  *hang \n");

// No output support.
fail0:
    system_state = SYSTEM_ABORTED;
    // Return to xxxhead.asm and hang.

    x_panic("Error: 0x02");
    return FALSE;
}


void gramado_shutdown (int how)
{
    //hal_shutdown();
}


// #deprecated
// #see: 
// kernel.h and hw.asm
void xxxxIRQ0_DEBUG_MESSAGE(void)
{
    debug_print ("xxxxIRQ0_DEBUG_MESSAGE:\n");
    //xxxDrawString("TICK\n");
    //console_outbyte('x',fg_console);
    
    //printf ("k\n");
    //refresh_screen();
}


// #deprecated
//#See: kernel.h and hw.asm
void xxxxIRQ1_DEBUG_MESSAGE(void)
{
    debug_print ("xxxxIRQ1_DEBUG_MESSAGE:\n");
    
    printf ("k");
    refresh_screen();
}


// #deprecated
//#See: kernel.h and sw.asm
void xxxxINT128_DEBUG_MESSAGE(void)
{
    debug_print ("xxxxINT128_DEBUG_MESSAGE:\n");
    //x_panic("xxxxINT128_DEBUG_MESSAGE: hang");
}

// == Idle thread in ring 0  ===============
// #test

// #bugbug
// This thread will start to run at the moment when
// the init process enable the interrupts.

// #suspended
void early_ring0_IdleThread (void)
{

// #danger: Do NOT change this function.
// #bugbug: This thread can't execute complex routine for now.

    //printf("");  //fail

    unsigned long deviceWidth  = (unsigned long) screenGetWidth();
    unsigned long deviceHeight = (unsigned long) screenGetHeight();

    if ( deviceWidth == 0 || deviceHeight == 0 )
    {
        debug_print ("early_ring0_IdleThread: w h\n");
        panic       ("early_ring0_IdleThread: w h\n");
    }

Loop:

// acende
    //drawDataRectangle( 0, 0, deviceWidth, 28, COLOR_KERNEL_BACKGROUND );
    //draw_string(8,8,COLOR_YELLOW," Gramado Operating System ");
    //refresh_screen();

// relax
    asm ("sti");
    asm ("hlt");

// apaga
    //drawDataRectangle( 0, 0, deviceWidth, 28, COLOR_KERNEL_BACKGROUND );
    //drawDataRectangle( 0, 0, deviceWidth, deviceHeight, COLOR_KERNEL_BACKGROUND );  //#bug
    //refresh_screen();

    goto Loop;
}


//
// End.
//










