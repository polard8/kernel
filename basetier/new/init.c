
// init.c

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


//static char *s_hostname;

#define GCC_VERSION ( __GNUC__ * 10000 \
            + __GNUC_MINOR__ * 100 \
            + __GNUC_PATCHLEVEL__ )


unsigned long InitializationPhase=0;

//#test
//static const unsigned int something=1234;

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
int ImportDataFromLinker = TRUE;
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



//char InitialUserProcessName[32] = "INIT.BIN"

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
    unsigned long lfb_pa;
    unsigned long deviceWidth;    // in pixels
    unsigned long deviceHeight;   // in pixels
    unsigned long bpp;            // bytes per pixel
    unsigned long last_valid_pa;  // Last valid physical address.
    // ...
};
struct x_boot_block_d  xBootBlock;


// ================================


//
// == Prototypes ========
//

static void preinit_Globals(int arch_type);
static void preinit_OutputSupport(void);
static void preinit_Serial(void);


// ================================




// #todo
static void preinit_Globals(int arch_type)
{
    asm ("cli");

// This is the first time we do the in the C part.
// See: head_64.asm

    system_state = SYSTEM_BOOTING;

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
    serial_init();
    debug_print("preinit_Serial: Initialized\n");
}


static void preinit_OutputSupport(void)
{

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

    VirtualConsole_initialize();

// #IMPORTAT: 
// We do not have all the runtime support yet.
// We can't use printf yet.
}


// main
// Called by START in 
// entrance/warden/unit0/x86_64/head_64.asm.
// See:
// init.h

int kernel_main(int arch_type)
{

// Command line sent to stdin.
// GWS.BIN will read this data.
    char cmdline[64];

// Setup debug mode.
// Enable the usage of the serial debug.
// It is not initialized yet.

    //enable_serial_debug();
    disable_serial_debug();


// Open the kernel virtual console 
// instead of first process.
// We can receive thiflag via command line.

    static int debug_mode=FALSE;
    //static int debug_mode=TRUE;


    Initialization.phase1 = FALSE;
    Initialization.phase2 = FALSE;
    Initialization.phase3 = FALSE;

    Initialization.hal = FALSE;
    Initialization.microkernel = FALSE;
    Initialization.executive = FALSE;
    Initialization.gramado = FALSE;

    Initialization.serial_log = FALSE;
    Initialization.console_log = FALSE;

/*
    char hostname[64];
    sprintf(hostname,"gramado");
    s_hostname = (char *) &hostname[0];
*/

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

    int Status = (-1);
    //int Options=0;
    //int SafeMode = FALSE;
    //unsigned long MemorySyze=0;
    int i=0;

// Magic
    unsigned long bootMagic = 
        (unsigned long) (magic & 0x00000000FFFFFFFF); 

// The boot block address. 0x0000000000090000.
// Each entry has 8 bytes.
// virtual = physical.
    unsigned long *xxxxBootBlock = (unsigned long*) BootBlockVA; 

//
// lfb
//

// #test
// isso não é possivel porque a paginação feita pelo bootloader
// ainda não esta pronta.
// #todo:
// Talvez possamos refazer a paginação usada pelo kernel.

    unsigned long *fb = (unsigned long *) FRONTBUFFER_VA; 
    fb[0] = 0x00FFFFFF;

// Check magic
// Paint a white screen if magic is ok.
// Paint a colored screen if magic is not ok.


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


//
// #breakpoint
//

    //while(1){}


// Hack Hack
    VideoBlock.useGui = TRUE;

// Boot block
// Saving the boot block
// Structure in this document.
// We will have a global one in gdef.h

    xBootBlock.lfb_pa        = (unsigned long) xxxxBootBlock[bbOffsetLFB_PA];
    xBootBlock.deviceWidth   = (unsigned long) xxxxBootBlock[bbOffsetX];
    xBootBlock.deviceHeight  = (unsigned long) xxxxBootBlock[bbOffsetY];
    xBootBlock.bpp           = (unsigned long) xxxxBootBlock[bbOffsetBPP];
    xBootBlock.last_valid_pa = (unsigned long) xxxxBootBlock[bbLastValidPA];

// Gramado mode.
// Gramado mode. (jail, p1, home ...)

    current_mode = (unsigned long) xxxxBootBlock[bbGramadoMode];

    // ...

// See: 
// kernel.h

    SavedLFB = (unsigned long) xBootBlock.lfb_pa;
    SavedX   = (unsigned long) xBootBlock.deviceWidth;
    SavedY   = (unsigned long) xBootBlock.deviceHeight;
    SavedBPP = (unsigned long) xBootBlock.bpp;

// Last valid physical address.
// Used to get the available physical memory.

    blSavedLastValidAddress = (unsigned long) xBootBlock.last_valid_pa; 

// Memory size in KB.
    blSavedPhysicalMemoryInKB = (blSavedLastValidAddress / 1024);

// #todo
// Setup the real boot block structure at gdef.h
// BootBlock

    screenSetSize (SavedX,SavedY);

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

// We do not have output yet

    preinit_Globals(0);  // IN: arch_type
    preinit_Serial();

    //if ( system_state != SYSTEM_BOOTING ){
    //    debug_print ("FAIL");
    //    while(1){}
    //}

// ============================
// #progress
// name:level:sublevel
// ============================

// Now we have serial port output.
    PROGRESS("kernel_main: Initializing ...\n");

// =================================================
// Initialize the virtual console structures.
// We do not have all the runtime support yet.
// We can't use printf yet.

    PROGRESS("Kernel:0:1\n");
    preinit_OutputSupport();

// #IMPORTAT: 
// We do not have all the runtime support yet.
// We can't use printf yet.

// =================================================
// Show some basic info.

    PROGRESS("Kernel:0:2\n");

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
    
    PROGRESS("Kernel:0:3\n");
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

    PROGRESS("Kernel:0:4\n");
    Runtime_initialize();

// =========================
// Clear the screen.
// print some basic info.
// Setup printing resources.
// ROM BIOS 8x8 font
// #todo: Isso ja foi feito em outro lugar?

    PROGRESS("Kernel:0:5\n");

    gws_currentfont_address = (unsigned long) BIOSFONT8X8;
    set_char_width(8);
    set_char_height(8);
    gfontSize = FONT8X8;

// Background
// Initializing background 
// for the very first time.
// Now we have a black screen.
// But the cursor position is wrong yet.
// #todo
// See: drivers/video/fbdev/bg.c

    //#breakpoint: BLACK ON WHITE.
    //ok, funcionou na maq real no modo jail, provavelmente 320x200.
    //Ainda nao podemos usar o refresh screen porque a
    //flag refresh_screen_enabled ainda nao foi acionada.
    //for (i=0; i< 320*25; i++){ fb[i] = 0; };
    //while(1){asm("hlt");};

    Background_initialize();


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

// OK. 
// We have a virtual console and we can use the printf.
    Initialization.console_log = TRUE;

// BANNER!
// Welcome message.
// This is the first message in the screen
// See: user/console.c

    console_banner(0);

    //printf("gcc: %d\n",GCC_VERSION);

// Na maquina real, com a placa de video nvidea
// a resoluçao do modo jail eh 320x200
// Na maquina real, com a placa de video onboard
// a resoluçao do modo jail eh muito grande.

    printf ("Width  = %d \n",xBootBlock.deviceWidth );
    printf ("Height = %d \n",xBootBlock.deviceHeight );
    printf ("BPP    = %d \n",xBootBlock.bpp );

//
// Stop: 
//

// We will support only 2 resolutions for now
// when we're not on qemu.
// width=800 or width=640
// In qemu we can support 3 resolutions
// width=800 or width=640 or width=320
// But at this moment we can't call the funtion
// for detecting if we are using qemuor not.
// #todo: 
// We need another function for detecting it
// in this phase of the initialization.

    if ( xBootBlock.deviceWidth != 800 &&
         xBootBlock.deviceWidth != 640 &&
         xBootBlock.deviceWidth != 320 )
    {
        printf("Bad resolution\n");
        printf("We're working to support more resolutions\n");
        refresh_screen();
        while(1){asm("hlt");}
    }

// #breakpoint
    //refresh_screen();
    //while(1){asm("hlt");}


// Show gramado mode.

    switch (current_mode){

    case GRAMADO_JAIL:
    case GRAMADO_P1:
    case GRAMADO_HOME:
        // ok
        break;

    case GRAMADO_P2:
    case GRAMADO_CASTLE:
    case GRAMADO_CALIFORNIA:
        //printf (">> [TODO] current_mode\n");
        break;

    // #panic
    default:
        printf (">> Undefined mode!\n");
        break;
    }

    //#debug
    //refresh_screen();
    //while(1){}

// ================================================

// #test
// Não queremos um tamanho de imagem que
// exceda o tamanho da região de memória mapeada para ela.

    unsigned long KernelImage_BSS_Size=0;
    unsigned long KernelImage_DATA_Size=0;
    unsigned long KernelImage_RODATA_Size=0;
    unsigned long KernelImage_CODE_Size=0;
    unsigned long KernelImage_Size=0;

// #todo
// Isso deve ter uma flag no aquivo de configuração.
// config.h i guess.

    if ( ImportDataFromLinker == TRUE )
    {
        //printf("\n");
 
        // #bugbug
        // Something is wrong here.
        KernelImage_Size = (kernel_end - kernel_begin);
        //printf ("Image Size %d KB \n",KernelImage_Size/1024);

        KernelImage_CODE_Size = (code_end - code_begin);
        //printf ("CODE Size %d KB \n",KernelImage_CODE_Size/1024);

        KernelImage_RODATA_Size = (rodata_end - rodata_begin);
        //printf ("RODATA Size %d KB \n",KernelImage_RODATA_Size/1024);

        KernelImage_DATA_Size = (data_end - data_begin);
        //printf ("DATA Size %d KB \n",KernelImage_DATA_Size/1024);

        KernelImage_BSS_Size = (bss_end - bss_begin);
        //printf ("BSS Size %d KB \n",KernelImage_BSS_Size/1024);

        // Limit 1 MB
        // The kernel image is too long.
        if ( KernelImage_Size/1024 > 1024 )
        {
            panic ("Error 0x04");
        }

        // #debug
        // refresh_screen();
        // while(1){}
    }

//
// char
//

    // ok
    //d_drawchar_transparent(120,120,COLOR_YELLOW,'G');
    //d_drawchar_transparent(130,120,COLOR_YELLOW,'X');

    // ok
    //d_drawchar_transparent(100,100,COLOR_YELLOW,'A');
    //refresh_rectangle(100,100,8,8);
    //while(1){}


//
// string
//

    //ok
    //draw_string(80,80,COLOR_YELLOW,"Gramado X");
    
    //ok
    //backbuffer_draw_horizontal_line( 100, 100, 200, COLOR_GREEN );

    //ok
    //backbuffer_draw_horizontal_line( 100, 100, 200, COLOR_GREEN );
    //refresh_rectangle(100,100,200,4);
    //while(1){}

    //ok
    //drawDataRectangle( 20, 20, 40, 40, COLOR_RED );
    //drawDataRectangle( 30, 30, 40, 40, COLOR_GREEN );
    //drawDataRectangle( 40, 40, 40, 40, COLOR_BLUE );
    
    //ok
    //set_up_cursor(0,1);
    //console_outbyte('\n',fg_console);
    //console_outbyte('X',fg_console);
    //console_outbyte('\n',fg_console);
    //console_outbyte('a',fg_console);

/*
    printf ("#test\n");
    printf ("LFB PA = %x \n",xBootBlock.lfb_pa );
    printf ("Width  = %d \n",xBootBlock.deviceWidth );
    printf ("Height = %d \n",xBootBlock.deviceHeight );
    printf ("BPP    = %d \n",xBootBlock.bpp );
    printf ("last valid pa = %x \n", xBootBlock.last_valid_pa);
*/

/*
// See: mmInit() in memory.c
    printf ("memorysizeBaseMemory %d\n",memorysizeBaseMemory);
    printf ("memorysizeOtherMemory %d\n",memorysizeOtherMemory);
    printf ("memorysizeExtendedMemory %d\n",memorysizeExtendedMemory);
    printf ("memorysizeTotal %d\n",memorysizeTotal);

// See: pages.c
    printf ("memorysizeUsed %d\n",memorysizeUsed);
    printf ("memorysizeFree %d\n",memorysizeFree);
*/

// #debug
    //refresh_screen();
    //while(1){}

// =====================================

// Display device
// See:
// halvid.h
// gva.h
// Todas essas informações devem ser passadas pelo Gramado Boot Loader.

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

    PROGRESS("Kernel:0:6\n"); 

// #todo
// A partir daqui faremos inicializações de partes
// dependentes da arquitetura.

    // Hack hack
    // Também usado por outras rotinas dainicialização.
    current_arch = CURRENT_ARCH_X86_64;

    switch (current_arch){

    // Not supported on Gramado X.
    //case CURRENT_ARCH_X86:
    //    break;
    // See: x64init.c in ke/arch/x86_64/

    case CURRENT_ARCH_X86_64:
        //debug_print ("kernel_main: [CURRENT_ARCH_X86_64] calling x64main() ...\n");
        Background_initialize();
        Status = (int) I_x64main();
        
        if (Status != TRUE){
            x_panic("Panic: Error 0x01");
        }
        
        if (Status == TRUE)
        {
            // Clear the screen.
            Background_initialize();

            // ::: Initialization on debug mode.
            // Initialize the default kernel virtual console.
            // It depends on the run_level.
            // See: kgwm.c
            if( debug_mode == TRUE )
            {
                printf("init.c: The kernel is in debug mode.\n");
                refresh_screen();
                kgwm_early_kernel_console();
                printf("init.c: End of debug mode.\n");
                refresh_screen();
                asm("hlt");
            }
            
            // Initialize the first process.
            // This is the default first client of the window server.
            // GWS.BIN.

            // Setup command line.
            if( (void*) stdin != NULL )
            {
                memset(cmdline, 0, 64);
                mysprintf(cmdline,"GWS.BIN hello");
                cmdline[63]=0;
                //rewind. See: kstdio.c
                k_fseek(stdin, 0, SEEK_SET);
                file_write_buffer( stdin, cmdline, 64 );
            }
            
            I_x64ExecuteInitialProcess();
        }
        break;

    // See:
    // armmain (); ??

    // ...

    default:
        debug_print ("kernel_main: [FAIL] Current arch not defined!\n");
        //system_state = SYSTEM_ABORTED;
        x_panic("Error 0x03");
        break;
    };

//=============================

    //ok
    //debug_print ("kernel_main: Testing reboot\n");
    //hal_reboot();
    
    // See: detect.c
    //if ( detect_IsQEMU() == TRUE ){
    //    debug_print ("kernel_main: Running on QEMU\n");
    //}

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




    //#test
    // x64_info();

    /*
    // #testing scroll
    printf("1 Testing scroll\n");
    printf("2 \n");
    printf("3 \n");
    printf("4 \n");
    printf("5 \n");
    printf("6 \n");
    printf("7 \n");
    printf("8 done\n");
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

    while (1){
        asm ("cli");
        asm ("hlt");
    };

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
    return -1;
}


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


//#See: kernel.h and hw.asm
void xxxxIRQ1_DEBUG_MESSAGE(void)
{
    debug_print ("xxxxIRQ1_DEBUG_MESSAGE:\n");
    
    printf ("k");
    refresh_screen();
}


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
    //drawDataRectangle( 0, 0, deviceWidth, 28, COLOR_BLUE );
    //draw_string(8,8,COLOR_YELLOW," Gramado Operating System ");
    //refresh_screen();

// relax
    asm ("sti");
    asm ("hlt");

// apaga
    //drawDataRectangle( 0, 0, deviceWidth, 28, COLOR_BLUE );
    //drawDataRectangle( 0, 0, deviceWidth, deviceHeight, COLOR_BLUE );  //#bug
    //refresh_screen();

    goto Loop;
}


//
// End.
//










