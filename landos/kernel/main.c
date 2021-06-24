

 // fake main.c
 // We need a fake KERNEL.BIN ELF file that will be used my the
 // boot loader.
 // The boot loader will load the fake kernel image before
 // setting up the long mode and the paging.


#include <kernel.h>


unsigned long magic;

#define BootBlockVA    0x0000000000090000
#define bbOffsetLFB_PA    0
#define bbOffsetX         1
#define bbOffsetY         2
#define bbOffsetBPP       3
// ...


struct x_boot_block_d
{
    unsigned long lfb_pa;        // O endereço físico de lfb, usado pelo kernel para paginarmos o lfb.
    unsigned long deviceWidth;   // in pixels
    unsigned long deviceHeight;  // in pixels
    unsigned long bpp;           // bytes per pixel
    // ...
};
struct x_boot_block_d  xBootBlock;


// See:
// xxxhead.asm
extern void x84_64_initialize_machine(void);



void preinit_Globals(int arch_type)
{
    asm ("cli");
    
    // ...
}

void preinit_Serial(void)
{
    serial_init();
    debug_print("\n");
    debug_print("\n");
    debug_print("== X ========================\n");
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

    // Magic
    unsigned long bootMagic = (unsigned long) (magic & 0x00000000FFFFFFFF); 

    // The boot block address.
    // Each entry has 8 bytes.
    unsigned long *xxxxBootBlock = (unsigned long*) BootBlockVA; 


    // #test
    // isso não é possivel porque a paginação feita pelo bootloader
    // ainda não esta pronta.
    // #todo:
    // Talvez possamos refazer a paginação usada pelo kernel.
    unsigned long *fb = (unsigned long *) FRONTBUFFER_VA; 
    fb[0] = 0x00FFFFFF;
    
    int i=0;


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
    
    xBootBlock.lfb_pa       = (unsigned long) xxxxBootBlock[bbOffsetLFB_PA];
    xBootBlock.deviceWidth  = (unsigned long) xxxxBootBlock[bbOffsetX];
    xBootBlock.deviceHeight = (unsigned long) xxxxBootBlock[bbOffsetY];
    xBootBlock.bpp          = (unsigned long) xxxxBootBlock[bbOffsetBPP];
    // ...


    // See: kernel.h
    SavedLFB = (unsigned long) xBootBlock.lfb_pa;
    SavedX   = (unsigned long) xBootBlock.deviceWidth;
    SavedY   = (unsigned long) xBootBlock.deviceHeight;
    SavedBPP = (unsigned long) xBootBlock.bpp;

    screenSetSize (SavedX,SavedY);


    // teste para a máquina real.
    
    // preto
    if ( xBootBlock.deviceWidth == 320 )
    {
        for (i=0; i<40*40; i++){
            fb[i] = 0;
        };
    }



    // Globals
    // We do not have output yet

    //preinit_Globals(arch_type);
    preinit_Globals(0);
    
    // Serial
    // We do not have output yet

    preinit_Serial();

    // =================================================
    
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
    // Background
    //

    // Initializing background 
    // for the very first time.
    // Now we have a black screen.
    // But the cursor position is wrong yet.

    
    // #todo
    // See: user/draw/view/bg.c
    
    Background_initialize();


    // BANNER !
    // Welcome message. (Poderia ser um banner.) 

    //
    // This is the first message in the screen
    //

    set_up_cursor (0,1);

    debug_print ("kernel_main: First message\n");
    printf      ("kernel_main: First message \n");


    // ================================================


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

    //refresh_screen();
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

        // See: x64init.c
        case CURRENT_ARCH_X86_64:
            debug_print ("kernel_main: [CURRENT_ARCH_X86_64] calling x64main() ...\n");
            //printf("kernel_main: [FAIL] x86_64 is not supported!\n");
            Status = (int) x64main();
            if (Status < 0){
                x_panic("[Kernel] kernel_main: CURRENT_ARCH_X86 fail\n");
            }
            //goto fail2;
            break;

        // See:
        // armmain (); ??

        // ...

        default:
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

    printf ("LFB PA = %x \n",xBootBlock.lfb_pa );
    printf ("Width  = %d \n",xBootBlock.deviceWidth );
    printf ("Height = %d \n",xBootBlock.deviceHeight );
    printf ("BPP    = %d \n",xBootBlock.bpp );


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

    //#test
    x64_info();

    // #debug
    //console_putchar('F',fg_console);
    refresh_screen();
    //a_soft_place_to_fall();
    //die();
 

//=============================

//== Tests ===================================================
//++

//
// int 3
//

    // vai funcionar se as rotinas de inicializações de vetores
    // estiverem prontas e tivermos alguma forma de 
    // imprimir a string na tela.

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

    while(1){}

    // Breakpoint for tests!
    // x_panic("kernel_main: :)");

//--
//=====================================================



//=======================================
    // Something is wrong
    PROGRESS("Kernel:0:7\n"); 
    debug_print ("kernel_main: Something is wrong\n");

//
// Breakpoint!
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
    // Return to xxxhead.asm and hang.
    return (-1);
}



//#See: kernel.h and hw.asm
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







