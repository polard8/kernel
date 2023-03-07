
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


//
// Initialization :)
//

// Global
//unsigned long gInitializationPhase=0;

// No pointer.
struct initialization_d  Initialization;


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
unsigned long magic=0;
unsigned long saved_bootblock_base=0;

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
static void kernel_booting(int arch_type);
static int booting_begin(int arch_type);
static int booting_end(int arch_type);

static void kernel_final_messages(void);

// System initialization routines.

static int __setup_cmdline(void);
static void __enter_debug_mode(void);


static void __print_resolution_info(void);
static void __check_gramado_mode(void);
static void __import_data_from_linker(void);

static void __check_refresh_support(void);
// ================================

// Worker
static void __check_refresh_support(void)
{
// Check if we can use refresh_screen or not.

// -------------------------------------------

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

// #bugbug
// Para os outros casos o pitch será '0'.

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

// Quantos KB vamos precisar para uma tela nessa resoluçao?
    sz_in_kb = 
        (unsigned long) (( pitch * xBootBlock.deviceHeight )/ 1024 );

// Saving:
// Screen size in kb.
// Remember: For now we only have 2048KB mapped for LFB.
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
        Initialization.is_console_log_initialized = FALSE;
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

// -------------------------------------------

}

// Worker
static void __print_resolution_info(void)
{
// Print device info.
    printf ("Width:%d Height:%d BPP:%d\n",
        xBootBlock.deviceWidth,
        xBootBlock.deviceHeight,
        xBootBlock.bpp );
// ---------------
// Is it supported?
// #temp
// Supported widths. 800, 640, 320.
    if ( xBootBlock.deviceWidth != 800 &&
         xBootBlock.deviceWidth != 640 &&
         xBootBlock.deviceWidth != 320 )
    {
        panic("__print_resolution_info: Unsupported resolution\n");
    }
}

// Worker
static void __check_gramado_mode(void)
{
//-----------
// gramado mode.

// Show gramado mode.
    printf ("gramado mode: %d\n",current_mode);

    switch (current_mode){
// #temp
// Supported gramado mode.
    case GRAMADO_JAIL:
    case GRAMADO_P1:
    case GRAMADO_HOME:
        // OK
        break;
// #temp
// Unsupported gramado mode. (yet)
    case GRAMADO_P2:
    case GRAMADO_CASTLE:
    case GRAMADO_CALIFORNIA:
        // #bugbug: panic and x_panic are not working at this point.
        debug_print("__check_gramado_mode: Unsupported gramado mode\n");
        panic("__check_gramado_mode: Unsupported gramado mode\n");
        //x_panic("x");
        //die();
        break;
// Undefined gramado mode.
    default:
        // #bugbug: panic and x_panic are not working at this point.
        debug_print("__check_gramado_mode: Undefined gramado mode\n");
        panic("__check_gramado_mode: Undefined gramado mode\n");
        break;
    };

    // Breakpoint
    //refresh_screen();
    //while(1){}
}

static void __import_data_from_linker(void)
{
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
}

// Setup stdin file.
// Clean the buffer.
// Set the offset position.
// See: kstdio.c
static int __setup_cmdline(void)
{
    char cmdline[64];

    memset(cmdline, 0, 64);  
    cmdline[63]=0;

    if ( (void*) stdin == NULL ){
        return -1;
    }
    if (stdin->magic!=1234){
        return -1;
    }
// Rewind.
    k_fseek( stdin, 0, SEEK_SET );
// Clean
    file_write_buffer( stdin, cmdline, 64 );
    k_fseek( stdin, 0, SEEK_SET );
    return 0;
}

static void __enter_debug_mode(void)
{
    if (Initialization.is_serial_log_initialized == TRUE){
        PROGRESS("__enter_debug_mode:\n");
    }

    if (Initialization.is_console_log_initialized != TRUE)
    {
        if (Initialization.is_serial_log_initialized == TRUE){
            PROGRESS("__enter_debug_mode: can't use the cirtual console\n");
        }
    }

    if (Initialization.is_console_log_initialized == TRUE)
    {
        printf("init.c: The kernel is in debug mode.\n");
        //refresh_screen();
        kgwm_early_kernel_console();
        printf("init.c: End of debug mode.\n");
        refresh_screen();
        die();
    }

    die();
}

static int booting_end(int arch_type)
{
// + Pass the command to the first process or,
// + Pass thecommand to the embedded debug shell.

// Open the kernel virtual console 
// instead of first process.
// We can receive this flag via command line.

    //int UseDebugMode=TRUE;
    int UseDebugMode=FALSE;

    PROGRESS("booting_end:\n");

// Final message before jumping to init process.
    printf("booting_end:\n");

    //#debug
    //refresh_screen();
    //while(1){}

// Setup command line for the init process.
    __setup_cmdline();

// Clear the screen again.
    zero_initialize_background();

// ::: Initialization on debug mode.
// Initialize the default kernel virtual console.
// It depends on the run_level.
// See: kgwm.c
    if (UseDebugMode == TRUE){
        __enter_debug_mode();
    }

    switch (arch_type){
        
        case CURRENT_ARCH_X86_64:
            // Do not return!
            // see: x64init.c
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

// Scheduler policies
// Early initialization.
// See: 
// sched.h, sched.c.
    SchedulerInfo.policy = SCHED_RR;
    SchedulerInfo.flags  = (unsigned long) 0;

// Initializing the global spinlock.
    __spinlock_ipc = TRUE;

// IO Control
    IOControl.useTTY = FALSE;        // Model not implemented yet.
    IOControl.useEventQueue = TRUE;  // The current model.
    IOControl.initialized = TRUE;    // IO system initialized.

    // ...
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
}

// see: serial.c
static void preinit_Serial(void)
{
    int Status=FALSE;
    Status = serial_init();
    if(Status!=TRUE){
        //#bugbug
        //Oh boy!, We can't use the serial debug.
    }
    PROGRESS("preinit_Serial: Serial debug initialized\n");
}

static void preinit_OutputSupport(void)
{
    PROGRESS("preinit_OutputSupport:\n");

// O refresh ainda não funciona, 
// precisamos calcular se a quantidade mapeada é suficiente.
    refresh_screen_enabled = FALSE;

    PROGRESS("preinit_OutputSupport: zero_initialize_virtual_consoles\n");
    zero_initialize_virtual_consoles();

    PROGRESS("preinit_OutputSupport: preinit_OutputSupport\n");

// #IMPORTAT: 
// We do not have all the runtime support yet.
// We can't use printf yet.
}

static void kernel_final_messages(void)
{
// Final messages
    if ( Initialization.is_serial_log_initialized == TRUE ){
        PROGRESS("init: [final message] FAILURE\n");
    }
    if ( Initialization.is_console_log_initialized == TRUE ){
        printf("init: [final message] FAILURE\n");
        refresh_screen();
    }
}

// ------------------------------
// init_system:
// Called by kmain.c
int init_system(int arch_type)
{
// Preinit
    preinit();
// Booting ...
    kernel_booting(arch_type);
// Fail
    kernel_final_messages();
    system_state = SYSTEM_DEAD;
// Return to kmain().
    return FALSE;
}

// limitation: No serial debug yet.
// #todo: #bugbug
// We have another BootBlock structure in info.h
static int preinit_SetupBootblock(void)
{

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
// Paint a 'colored' screen if magic is not ok.
    register int i=0;
// WHITE
    if (bootMagic == 1234){
        for (i=0; i<320*32; i++){ fb[i] = 0xFFFFFFFFFFFFFFFF; };
    }
// COLORED
    if (bootMagic != 1234){
        for (i=0; i<320*32; i++){ fb[i] = 0xFF00FFFFFFF00FFF; };
        //#debug
        //while(1){}
    }

    //#debug
    //while(1){}

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

// #todo
// Setup the real boot block structure at gdef.h

// Set up private variables in screen.c
    screenSetSize (gSavedX,gSavedY);

// Memory support.

// Last valid physical address.
// Used to get the available physical memory.
    blSavedLastValidAddress = (unsigned long) xBootBlock.last_valid_pa; 
// Memory size in KB.
    blSavedPhysicalMemoryInKB = (blSavedLastValidAddress / 1024);

    return 0;
}


static int preinit(void)
{
    system_state = SYSTEM_PREINIT;

// Starting the counter.
    Initialization.current_phase = 0;

// ==================

// Checkpoints
    Initialization.phase1_checkpoint = FALSE;
    Initialization.phase2_checkpoint = FALSE;
    Initialization.phase3_checkpoint = FALSE;
    Initialization.hal_checkpoint = FALSE;
    Initialization.microkernel_checkpoint = FALSE;
    Initialization.executive_checkpoint = FALSE;
    Initialization.gramado_checkpoint = FALSE;

// Flags
// We still dont have any log/verbose support.
    Initialization.is_serial_log_initialized = FALSE;
    Initialization.is_console_log_initialized = FALSE;
// The display dirver is not initialized yet,
// but the kernel owns it.
    Initialization.kernel_owns_display_device = TRUE;

// Hack Hack
    VideoBlock.useGui = TRUE;

// first of all
// Getting critical boot information.
    preinit_SetupBootblock();
// We do not have serial debug yet.
    preinit_Globals(0);  // IN: arch_type
// Serial debug support.
    preinit_Serial();
// Initialize the virtual console structures.
// We do not have all the runtime support yet.
// We can't use printf yet.
    preinit_OutputSupport();

    return 0;
}

static void kernel_booting(int arch_type)
{
    int Status=FALSE;

// Begin
// Kernel initialization.
    Status = (int) booting_begin(arch_type);

// End
// + Pass the command to the first process or,
// + Pass the command to the embedded debug shell.
    if (Status==TRUE){
        Status = (int) booting_end(arch_type);
    }

// + Pass the command to the embedded debug shell if possible.
    if (Status != TRUE)
    {
        // panic screen
        // Mostramos informações completas ou
        // permitimos a inicialização de outro modo,
        // talvez algum modo de recuperação ou simplificado.
 
        if (Initialization.is_serial_log_initialized == TRUE){
            PROGRESS("init: booting_end fail\n");
        }
        if (Initialization.is_console_log_initialized == TRUE)
        {
            printf("init: booting_end fail\n");
            printf("init: Trying debug mode\n");
            __enter_debug_mode();
        }
        die();
    }
}

// OUT: TRUE or FALSE.
static int booting_begin(int arch_type)
{
// + Initialize video.
// + Initialize runtime. 
//   Memory initialization.
// + Initialize default kernel font.
// + Initialize background
// + Initialize display device.
// + Initialize x86_64 architecture.

    int Status = (-1);

// #IMPORTAT: 
// We do not have all the runtime support yet.
// We can't use printf yet.

    system_state = SYSTEM_BOOTING;

    PROGRESS("booting_begin:\n");
    printf("booting_begin:\n");

// boot info
    if (xBootBlock.initialized != TRUE){
        panic ("booting_begin: xBootBlock.initialized\n");
    }

// Video support
    zero_initialize_video();
// Runtime
// Memory initialization
    zero_initialize_runtime(arch_type);
// kernel font.
   zero_initialize_default_kernel_font();
// Initializing background for the very first time.
    zero_initialize_background();
// Setup refresh/flush support.
// Flush data into the lfb.
    __check_refresh_support();
// Now we have console debug
    Initialization.is_console_log_initialized = TRUE;
// Show banner!
    zero_show_banner();
// Print resolution info
    __print_resolution_info();
// Check gramado mode
    __check_gramado_mode();
// Import data from linker.
    __import_data_from_linker();
// Initialize bootloader display device.
    bldisp_initialize();
// Initialize the current architecture.
    Status = (int) zero_initialize_arch(arch_type);
    if (Status == TRUE){
        // Done!
        return TRUE;
    }
// Fail
    system_state = SYSTEM_ABORTED;
    x_panic("Error: 0x02");
    return FALSE;
}

void gramado_shutdown(int how)
{
    //hal_shutdown();
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
    //backbuffer_draw_rectangle( 0, 0, deviceWidth, 28, COLOR_KERNEL_BACKGROUND );
    //draw_string(8,8,COLOR_YELLOW," Gramado Operating System ");
    //refresh_screen();

// relax
    asm ("sti");
    asm ("hlt");

// apaga
    //backbuffer_draw_rectangle( 0, 0, deviceWidth, 28, COLOR_KERNEL_BACKGROUND );
    //backbuffer_draw_rectangle( 0, 0, deviceWidth, deviceHeight, COLOR_KERNEL_BACKGROUND );  //#bug
    //refresh_screen();

    goto Loop;
}


//
// End.
//










