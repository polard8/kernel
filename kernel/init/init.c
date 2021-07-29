
// main.c

// This file and theis folder will be the control panel
// for the initialization routine.
// Please put here data we need.


// fake main.c
// We need a fake KERNEL.BIN ELF file that will be used my the
// boot loader.
// The boot loader will load the fake kernel image before
// setting up the long mode and the paging.

#include <kernel.h>


unsigned long InitializationPhase;

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


// #todo
void preinit_Globals(int arch_type)
{
    asm ("cli");

    // This is the first time we do the in the C part.
    // See: head_64.asm

    system_state = SYSTEM_BOOTING;

    // ...
}

void preinit_Serial(void)
{
    serial_init();
    
    //debug_print("\n");
    debug_print("\n");
    debug_print("== X ========\n");
    debug_print("preinit_Serial: Serial debug initialized!\n");
}

void preinit_OutputSupport(void)
{
    // Virtual Console.
    // See: user/console.c
    
    debug_print ("[Kernel] kernel_main: Initializing virtual consoles ...\n");
    
    // O refresh ainda não funciona, 
    // precisamos calcular se a quantidade mapeada é suficiente.

    refresh_screen_flag = FALSE;
    
    // #
    // As estruturas de console sao estruturas de tty,
    // mas s~ao um array de estruturas, n~ao precisa de malloc,
    // por isso podem ser chamadas nesse momento.
    
    // #test
    // We need to test it better.

    VirtualConsole_initialize();
}


//
// main
//

int kernel_main(int arch_type)
{
    int Status = (-1);
    //int Options=0;
    //int SafeMode = FALSE;
    //unsigned long MemorySyze=0;
    int i=0;


    // Magic
    unsigned long bootMagic = (unsigned long) (magic & 0x00000000FFFFFFFF); 

    // The boot block address.
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


//
// magic
//

    // Paint a white screen if magic is ok.
    if ( bootMagic == 1234 )
    {
        for (i=0; i<320*50; i++){
            fb[i] = 0xFFFFFFFFFFFFFFFF;
        };
    }

    // Paint a colored screen if magic is not ok.
    if ( bootMagic != 1234 )
    {
        for (i=0; i<320*50; i++){
            fb[i] = 0xFF00FFFFFFF00FFF;
        };
    }

    // Hack Hack
    VideoBlock.useGui = TRUE;


//
// Boot block
//

    // Saving the boot block
    // Structure in this document.
    // We will have a global one in gdef.h
    
    xBootBlock.lfb_pa         = (unsigned long) xxxxBootBlock[bbOffsetLFB_PA];
    xBootBlock.deviceWidth    = (unsigned long) xxxxBootBlock[bbOffsetX];
    xBootBlock.deviceHeight   = (unsigned long) xxxxBootBlock[bbOffsetY];
    xBootBlock.bpp            = (unsigned long) xxxxBootBlock[bbOffsetBPP];
    xBootBlock.last_valid_pa  = (unsigned long) xxxxBootBlock[bbLastValidPA];
    // ...

    // See: kernel.h
    SavedLFB = (unsigned long) xBootBlock.lfb_pa;
    SavedX   = (unsigned long) xBootBlock.deviceWidth;
    SavedY   = (unsigned long) xBootBlock.deviceHeight;
    SavedBPP = (unsigned long) xBootBlock.bpp;

    // Last valid physical address
    // Used to get the available physical memory.
    blSavedLastValidAddress = (unsigned long) xBootBlock.last_valid_pa; 

    // Memory size in KB.
    blSavedPhysicalMemoryInKB = (blSavedLastValidAddress / 1024);


//
// #todo
//

    // Setup the real boot block structure at gdef.h
    // BootBlock

    screenSetSize (SavedX,SavedY);


    // teste para a máquina real.
    
    // preto
    if ( xBootBlock.deviceWidth == 320 )
    {
        for (i=0; i<40*40; i++){
            fb[i] = 0;
        };
    }


// =================================================
    // Globals
    // We do not have output yet
    //preinit_Globals(arch_type);
    preinit_Globals(0);

// =================================================
    // Serial
    // We do not have output yet
    preinit_Serial();


    //if ( system_state != SYSTEM_BOOTING ){
    //    debug_print ("FAIL");
    //    while(1){}
    //}

    //
    // #progress
    // name:level:sublevel
    //

    PROGRESS("---------------------\n");
    PROGRESS(" Initializing landos \n");
    // Now we have serial port output.
    // =================================================

    PROGRESS("Kernel:0:1\n");
    // Initialize the virtual console structures.
    // #IMPORTAT: We do not have all the runtime support yet.
    // We can't use printf yet.

    preinit_OutputSupport();

    // =================================================


    PROGRESS("Kernel:0:2\n");
    // Show some basic info.

    debug_print ("Initializing landos kernel ...\n");


    // #todo
    // The mode.
    debug_print ("mode: ");
    debug_print ("\n");

    // #todo
    // The architecture.
    debug_print ("arch: ");
    debug_print ("\n");


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


// ====================================

//
// video
//

    PROGRESS("Kernel:0:3\n");
    // Video support

    debug_print ("[Kernel] kernel_main: Initializing video support ...\n");
    Video_initialize();



// ====================================

//
// Runtime
//

    PROGRESS("Kernel:0:4\n");
    // Runtime

    // #bugbug:
    // We need the runtime initialization for the messages.
    // What about to initialize it early?! now!!!!
    // See: core/runtime.c

    // #bugbug
    // Here the background is not initialized yet,
    // so, we have a lot of dirty things.

    debug_print ("[Kernel] kernel_main: Initializing runtime\n");
    Runtime_initialize();


// =========================
    PROGRESS("Kernel:0:5\n");
    // Clear the screen.
    // print some basic info.

//
// Setup printing resources.
//

    // ROM BIOS 8x8 font
    // #todo: Isso ja foi feito em outro lugar?
    gws_currentfont_address = (unsigned long) BIOSFONT8X8;
    set_char_width(8);
    set_char_height(8);
    gfontSize = FONT8X8;



//
// == Background ===================================================
//

    // Initializing background 
    // for the very first time.
    // Now we have a black screen.
    // But the cursor position is wrong yet.

    
    // #todo
    // See: user/draw/view/bg.c
    
    Background_initialize();


    // ++
    // ======================================
    // Screen size
    
    unsigned long bytes_per_pixel = 0;
    unsigned long pitch = 0;
    unsigned long sz_in_kb = 0;

    refresh_screen_flag = FALSE;
    screen_size_in_kb = 0;

    if ( xBootBlock.bpp == 24 || xBootBlock.bpp == 32 )
    {
        bytes_per_pixel = (xBootBlock.bpp / 8); 
        pitch = (xBootBlock.deviceWidth * bytes_per_pixel);
    }  

    if ( pitch == 0){
        refresh_screen_flag = FALSE;
        printf ("Screen size fail. pitch\n");
    }

    if ( pitch != 0){
        
        sz_in_kb = (unsigned long) (( pitch * xBootBlock.deviceHeight )/ 1024 );
        screen_size_in_kb = sz_in_kb;
        
        printf ("Screen size: %d KB\n", sz_in_kb);
        
        // fail.
        if ( sz_in_kb >= 2048 ){
            refresh_screen_flag = FALSE;
            printf ("Screen size fail sz_in_k\n");
        }
    
        // ok
        if ( sz_in_kb < 2048 ){
            refresh_screen_flag = TRUE;  
        }
    }
    // ======================================
    // --


//
// BANNER!
//

    // Welcome message. (Poderia ser um banner.) 

    //
    // This is the first message in the screen
    //

    set_up_cursor (0,1);

    debug_print ("kernel_main: First message\n");
    printf      ("kernel_main: First message \n");

    // ================================================

    // #test
    // Não queremos um tamanho de imagem que
    // exceda o tamanho da região de memória mapeada para ela.
    unsigned long KernelImage_BSS_Size=0;
    unsigned long KernelImage_DATA_Size=0;
    unsigned long KernelImage_RODATA_Size=0;
    unsigned long KernelImage_CODE_Size=0;
    unsigned long KernelImage_Size=0;

    if ( ImportDataFromLinker == TRUE )
    {
        printf("\n");
 
        // #bugbug
        // Something is wrong here.
        KernelImage_Size = (kernel_end - kernel_begin);
        printf ("Image Size %d KB \n",KernelImage_Size/1024);

        KernelImage_CODE_Size = (code_end - code_begin);
        printf ("CODE Size %d KB \n",KernelImage_CODE_Size/1024);

        KernelImage_RODATA_Size = (rodata_end - rodata_begin);
        printf ("RODATA Size %d KB \n",KernelImage_RODATA_Size/1024);

        KernelImage_DATA_Size = (data_end - data_begin);
        printf ("DATA Size %d KB \n",KernelImage_DATA_Size/1024);

        KernelImage_BSS_Size = (bss_end - bss_begin);
        printf ("BSS Size %d KB \n",KernelImage_BSS_Size/1024);

        // Limit 1 MB
        if ( KernelImage_Size/1024 > 1024 ){
            panic ("kernel_main: The kernel image is too long\n");
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
    //my_buffer_horizontal_line( 100, 100, 200, COLOR_GREEN );

    //ok
    //my_buffer_horizontal_line( 100, 100, 200, COLOR_GREEN );
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


    printf ("#test\n");
    printf ("LFB PA = %x \n",xBootBlock.lfb_pa );
    printf ("Width  = %d \n",xBootBlock.deviceWidth );
    printf ("Height = %d \n",xBootBlock.deviceHeight );
    printf ("BPP    = %d \n",xBootBlock.bpp );
    printf ("last valid pa = %x \n", xBootBlock.last_valid_pa);

    // See: mmInit() in memory.c
    printf ("memorysizeBaseMemory %d\n",memorysizeBaseMemory);
    printf ("memorysizeOtherMemory %d\n",memorysizeOtherMemory);
    printf ("memorysizeExtendedMemory %d\n",memorysizeExtendedMemory);
    printf ("memorysizeTotal %d\n",memorysizeTotal);

    // See: pages.c
    printf ("memorysizeUsed %d\n",memorysizeUsed);
    printf ("memorysizeFree %d\n",memorysizeFree);
    
    
    // #debug
    refresh_screen();
    //while(1){}


//=============================

    PROGRESS("Kernel:0:6\n"); 
    // Initialize current archtecture.

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

        // See: x64init.c in kernel/arch/x86_64/
        case CURRENT_ARCH_X86_64:
            
            debug_print ("kernel_main: [CURRENT_ARCH_X86_64] calling x64main() ...\n");
            //printf      ("kernel_main: [CURRENT_ARCH_X86_64] calling x64main() ...\n");
            Status = (int) I_x64main();
            
            if (Status < 0)
            {
                x_panic("[Kernel] kernel_main: CURRENT_ARCH_X86 fail\n");
            }
            
            // #test
            if (Status == 1234)
            {
                // No return.
                debug_print ("kernel_main: Calling x64ExecuteInitialProcess()\n");
                I_x64ExecuteInitialProcess();
            }
            
            //goto fail2;
            break;

        // See:
        // armmain (); ??

        // ...

        default:
            //system_state = SYSTEM_ABORTED;
            
            debug_print ("kernel_main: [FAIL] Current arch not defined!\n");
            //printf("kernel_main: [FAIL] Current arch not defined!");
            goto fail2;
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

    refresh_screen_flag = FALSE;
    screen_size_in_kb = 0;

    if ( xBootBlock.bpp == 24 || xBootBlock.bpp == 32 )
    {
        bytes_per_pixel = (xBootBlock.bpp / 8); 
        pitch = (xBootBlock.deviceWidth * bytes_per_pixel);
    }  

    if ( pitch == 0){
        refresh_screen_flag = FALSE;
        printf ("Screen size fail. pitch\n");
    }

    if ( pitch != 0){
        
        sz_in_kb = (unsigned long) (( pitch * xBootBlock.deviceHeight )/ 1024 );
        screen_size_in_kb = sz_in_kb;
        
        printf ("Screen size: %d KB\n", sz_in_kb);
        
        // fail.
        if ( sz_in_kb >= 2048 ){
            refresh_screen_flag = FALSE;
            printf ("Screen size fail sz_in_k\n");
        }
    
        // ok
        if ( sz_in_kb < 2048 ){
            refresh_screen_flag = TRUE;  
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


    // #debug
    // Show current process info.
    printf("\n");
    printf("\n");
    current_process = KernelProcess->pid;
    show_currentprocess_info();

    // #fail
    //printf("\n");
    //printf("\n");
    //current_process = InitProcess->pid;
    //show_currentprocess_info();

    // #debug
    // Show current thread info.
    printf("\n");
    printf("\n");
    current_thread = EarlyRING0IDLEThread->tid;
    show_thread_information();
    
    // #fail
    //printf("\n");
    //printf("\n");
    //current_thread = InitThread->tid;
    //show_thread_information();


    // #debug
    //console_putchar('F',fg_console);
    //refresh_screen();
    //a_soft_place_to_fall();
    //die();

    printf("\n");
    printf("kernel_main: *breakpoint :)\n");
    refresh_screen();

//=============================

//== Tests ===================================================
//++

//
// int 3
//

    // vai funcionar se as rotinas de inicializações de vetores
    // estiverem prontas e tivermos alguma forma de 
    // imprimir a string na tela.

    // #test
    // Actually, the init process will use a syscall to
    // enable the interrupts and start the taskswitching stuff.

    //debug_print ("TEST: sti\n");
    asm ("sti");

    //debug_print ("TEST: int $3\n");
    //asm ("int $3");

    //debug_print ("TEST: 8/0\n");
    //int zzz=8/0;

    //debug_print ("TEST: int $128\n");
    //asm ("int $128");

//
// panic
//

    //a_soft_place_to_fall();
    //die();

    while (1){
        asm ("sti");
        asm ("hlt");
    };

    // Breakpoint for tests!
    // x_panic("kernel_main: :)");

//--
//=====================================================

//=======================================
    // Something is wrong
    PROGRESS("Kernel:0:7\n"); 
    debug_print ("kernel_main: Something is wrong\n");

//
// Breakpoint
//
  // x_panic("kernel_main: :)");


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
    return (-1);
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
Loop:
    asm ("sti");
    asm ("hlt");
    goto Loop;
}

//
// End.
//










