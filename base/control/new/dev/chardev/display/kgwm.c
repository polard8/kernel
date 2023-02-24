
// kgwm.c
// Events and wm inside the kernel.

#include <kernel.h> 

// 
// Imports
//


//--------------------------------------
// Ponteiros para ícones
// Ponteiros para o endereço onde os ícones 
// foram carregados.
// queremos saber se o endereço alocado eh compartilhado ...
// para o window server usar ... entao chamaremos de sharedbufferIcon.

// Icon cache structure.
// see: window.h
struct icon_cache_d  icon_cache;


// ============================
static unsigned long presence_level=32;
static unsigned long flush_fps=30;

// ============================

// Endereços dos charmaps usados:
// Obs: Incluídos na estrutura.
//unsigned long normal_charmap_address;
//unsigned long shift_charmap_address;
//unsigned long control_charmap_address;

//
// Prototypes ===========================================
//


static void __launch_app_via_initprocess(int index);
static void __enter_embedded_shell(int kernel_in_debug_mode);
static void __exit_embedded_shell(void);


static unsigned long __last_tick(void);

// ============================

static unsigned long __last_tick(void)
{
    return (unsigned long) jiffies;
}



// local
// Launch an app via init process.
// Just a small range of messages are accepted.
// range: 4001~4009

static void __launch_app_via_initprocess(int index)
{
    tid_t src_tid = 0;  //#todo
    tid_t dst_tid = (tid_t) INIT_TID;

    if ( index < 4001 || index > 4009 )
    {
        return;
    }
// Post
// #todo: sender.
    post_message_to_tid(
        (tid_t) src_tid,        // sender tid
        (tid_t) dst_tid,        // receiver tid
        (int) MSG_COMMAND,      // msg code
        (unsigned long) index,  // range: 4001~4009
        0 );
}

static void __enter_embedded_shell(int kernel_in_debug_mode)
{
    int console_index = fg_console;

    // ShellFlag = FALSE;

//
// Set up console
//

    jobcontrol_switch_console(0);

// Message

    if (kernel_in_debug_mode){
        printf("[[ KERNEL IN DEBUG MODE ]]\n");
    }
    printf("kernel console number %d\n",console_index);
    printf("Prompt ON: Type something\n");
    consolePrompt();  // it will refresh the screen.
    //refresh_screen();  

// Flag
    ShellFlag = TRUE;
}

static void __exit_embedded_shell(void)
{
// log
    printf("\n");
    printf ("Prompt OFF: Bye\n");
    printf("\n");
    refresh_screen();
// done
    ShellFlag = FALSE;
}


void exit_kernel_console(void)
{
    __exit_embedded_shell();
// suficiente para o modo debug.
    ShellFlag = FALSE;
}


// #deprecated
// called by init.c
void kgwm_early_kernel_console(void)
{
// #deprecated
    x_panic ("kgwm_early_kernel_console:");
}


/*
 * wmProcedure:
 *       Some combinations with control + F1~F12
 */
// Called by kgws_event_dialog in kgws.c
// Called by si_send_longmessage_to_ws and si_send_message_to_ws
// in siws.c 
// #bugbug: We don't wanna call the window server. Not now.
// #important:
// Isso garante que o usuário sempre podera alterar o foco
// entre as janelas do kgws usando o teclado, pois essa rotina
// é independente da thread que está em foreground.
// #todo
// Talvez a gente possa usar algo semelhando quando o window
// server estiver ativo. Mas possivelmente precisaremos 
// usar outra rotina e não essa. Pois lidaremos com uma estrutura
// de janela diferente, que esta localizada em ring3.
// From Windows:
// Because the mouse, like the keyboard, 
// must be shared among all the different threads, the OS 
// must not allow a single thread to monopolize the mouse cursor 
// by altering its shape or confining it to a small area of the screen.
// #todo
// This functions is the moment to check the current input model,
// and take a decision. It will help us to compose the event message.
// It is because each environment uses its own event format.

int 
wmProcedure ( 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{
// Called by wmKeyEvent() in grinput.c

    int Status = -1;
    int UseSTDIN=TRUE;  // Input model
    char ch_buffer[2];  // char string.
    char buffer[128];   // string buffer
    unsigned long tmp_value=0;

    //debug_print("wmProcedure:\n");
    sprintf (buffer,"My \x1b[8C string!\n"); 

// ===================================
// Control:
//     'Control + ?' belongs to the kernel.

// ===================================
// Shift:
//     'Shift + ?' belongs to the window server.


//
// Dispatcher
//

    if (msg<0){
        debug_print("wmProcedure: Invalid msg\n");
        return -1;
    }

    switch (msg){

// ==============
// msg:
// Mouse stuff.
    case MSG_MOUSEMOVE:
    case MSG_MOUSEPRESSED:
    case MSG_MOUSERELEASED:
        return -1;
        break;

// ==============
// msg:
// Keydown.
    case MSG_KEYDOWN:

        // Para todas as teclas quando o console não está ativo.
        // Serão exibidas pelo window server 
        // na janela com foco de entrada,
        // Se ela for do tipo editbox.
        // O ws mandará mensagens para a thread associa
        // à janela com foco de entrada.
            
        if (ShellFlag!=TRUE){
            //wmSendInputToWindowManager(0,MSG_KEYDOWN,long1,long2);
        }

        switch (long1){

        case VK_RETURN:
            //if(ShellFlag!=TRUE){
                //wmSendInputToWindowManager(0,MSG_KEYDOWN,long1,long2);
                //return 0;
            //}
            if(ShellFlag==TRUE)
            {
                kinput('\0');               // finalize
                consoleCompareStrings();   // compare
                //invalidate_screen();
                refresh_screen();
                return 0;
            }
            break;

         //case 'd':
         //case 'D':
         //    if(ctrl_status==TRUE && alt_status==TRUE)
         //    {
         //        __enter_embedded_shell(FALSE);
         //        return 0;
         //    }
         //    break;

        //case VK_TAB: 
            //printf("TAB\n"); 
            //invalidate_screen();
            //refresh_screen(); 
            //break;

        default:

            // Console!
            // YES, we're using the embedded kernel console.
            // O teclado vai colocar o char no prompt[]
            // e exibir o char na tela somente se o prompt
            // estiver acionado.
            if (ShellFlag==TRUE)
            {
                consoleInputChar(long1);
                console_putchar ( (int) long1, fg_console );
                return 0;
            }


            // Not console.
            // NO, we're not using the kernel console.
            // Pois não queremos que algum aplicativo imprima na tela
            // enquanto o console virtual está imprimindo.
            if (ShellFlag != TRUE)
            {
                if (ctrl_status == TRUE && long1 == 'c'){
                    post_message_to_ws( MSG_COPY, long1, long2 );
                    return 0;
                }

                if (ctrl_status == TRUE && long1 == 'v'){
                    post_message_to_ws( MSG_PASTE, long1, long2 );
                    return 0;
                }

                if (ctrl_status == TRUE && long1 == 'x'){
                    post_message_to_ws( MSG_CUT, long1, long2 );
                    return 0;
                }

                if (ctrl_status == TRUE && long1 == 'z'){
                    post_message_to_ws( MSG_UNDO, long1, long2 );
                    return 0;
                }

                if (ctrl_status == TRUE && long1 == 'a'){
                    post_message_to_ws( MSG_SELECT_ALL, long1, long2 );
                    return 0;
                }

                if (ctrl_status == TRUE && long1 == 'f'){
                    post_message_to_ws( MSG_FIND, long1, long2 );
                    return 0;
                }

                if (ctrl_status == TRUE && long1 == 's'){
                    post_message_to_ws( MSG_SAVE, long1, long2 );
                    return 0;
                }

                // ...

                // No caso da combinação não ter sido tratada na rotina acima.
                // Enviamos combinação de [shift + tecla] de digitaçao.
                post_message_to_ws( msg, long1, long2 );
                // return 0;

                // Send it to the window server.
                //wmSendInputToWindowManager(0,MSG_KEYDOWN,long1,long2);
                // #test
                // Write into stdin
                if (UseSTDIN == TRUE)
                {
                    //debug_print ("wmProcedure: Writing into stdin ...\n");
                    //stdin->sync.can_write = TRUE;
                    //ch_buffer[0] = (char) (long1 & 0xFF);
                    //sys_write(0,ch_buffer,1);
                    return 0;
                }
            }

            //debug_print ("wmProcedure: done\n");
            return 0;
            break;
        };
        break;

// ==============
// msg:
// Syskeyup.
// liberadas: teclas de funçao
// syskeyup foi enviado antes pela função que chamou essa função.
// não existe combinação de tecla de controle e syskeyup.
    case MSG_SYSKEYUP:
        // Se nenhum modificador esta acionado,
        // entao apenas enviamos a tecla de funçao 
        // para o window server.
        // Send it to the window server.
        if( shift_status != TRUE &&
            ctrl_status != TRUE &&
            alt_status != TRUE )
        {
            return 0;
        }
        break;

// ==============
// msg:
// Syskeydown.
// Pressionadas: teclas de funçao
// Se nenhum modificador esta acionado,
// entao apenas enviamos a tecla de funçao 
// para o window server.
// Send it to the window server.
// #bugbug:
// Esse tratamento é feito pela rotina que chamou
// essa rotina. Mas isso também pode ficar aqui.
        
    case MSG_SYSKEYDOWN:

        // #??
        // Não enviamos mensagem caso não seja combinação?
        if ( shift_status != TRUE && ctrl_status != TRUE && alt_status != TRUE )
        {
            return 0;
        }

        // Process a set of combinations.
        switch (long1){

            // Exibir a surface do console.
            case VK_F1:
                if (ctrl_status == TRUE){
                    // control + shift + F1
                    // Full ps2 initialization and launch the app.
                    // #danger: Mouse is not well implemented yet.
                    if( shift_status == TRUE){
                        PS2_initialization();
                        __launch_app_via_initprocess(4001);
                        return 0;
                    }
                    __launch_app_via_initprocess(4001);  //terminal
                    return 0;
                }
                if (alt_status == TRUE){
                    //post_message_to_ws( (int) 77101, 0, 0 );
                }
                if (shift_status == TRUE){
                    jobcontrol_switch_console(0);
                    //post_message_to_ws( (int) 88101, 0, 0 );
                }
                return 0;
                break;

            case VK_F2:
                if (ctrl_status == TRUE){
                     __launch_app_via_initprocess(4002);  //fileman
                     return 0;
                }
                if (alt_status == TRUE){
                    //post_message_to_ws( (int) 77102, 0, 0 );
                }
                if (shift_status == TRUE){
                    jobcontrol_switch_console(1);
                    //post_message_to_ws( (int) 88102, 0, 0 );
                }
                return 0;
                break;

            case VK_F3:
                if (ctrl_status == TRUE){
                    __launch_app_via_initprocess(4003);  //editor
                    return 0;
                }
                if (alt_status == TRUE){
                    //post_message_to_ws( (int) 77103, 0, 0 );
                }
                if (shift_status == TRUE){
                    jobcontrol_switch_console(2);
                    //post_message_to_ws( (int) 88103, 0, 0 );
                }
                return 0;
                break;

            case VK_F4:
                if (ctrl_status == TRUE){
                    
                    // kill fg thread if it is possible.
                    if ( shift_status == TRUE){
                        // #todo: see: tlib.c 
                        // kill_thread(foreground_thread)
                        return 0;
                    }
                    //__launch_app_via_initprocess(4004);
                    //post_message_to_ws( 33888, 0, 0 ); //#TEST
                    return 0;
                }
                // alt+f4: The vm handle this combination.
                // We can't use it on vms.
                if (alt_status == TRUE){
                    //post_message_to_ws( (int) 77104, 0, 0 );
                    return 0;
                }
                if (shift_status == TRUE){
                    jobcontrol_switch_console(3);
                    //post_message_to_ws( (int) 88104, 0, 0 );
                }
                return 0;
                break;

            // Reboot
            case VK_F5:
                if (ctrl_status == TRUE){
                    //__launch_app_via_initprocess(4005);
                    //post_message_to_ws( 33888, 0, 0 ); //#TEST
                    return 0;
                }
                if (alt_status == TRUE){
                    //post_message_to_ws( (int) 77105, 0, 0 );
                }
                if (shift_status == TRUE){
                    //post_message_to_ws( (int) 88105, 0, 0 );
                    //post_message_to_foreground_thread(
                    //   ??, 1234, 1234 );
                }
                return 0;
                break;

            // Send a message to the Init process.
            // 9216 - Launch the redpill application
            case VK_F6:
                if (ctrl_status == TRUE){
                    // __launch_app_via_initprocess(4006);
                    return 0; 
                }
                if (alt_status == TRUE){
                    //post_message_to_ws( (int) 77106, 0, 0 );
                }
                if (shift_status == TRUE){
                    //post_message_to_ws( (int) 88106, 0, 0 );
                }
                return 0;
                break;

            // Test 1.
            case VK_F7:
                if (ctrl_status == TRUE){
                    //__launch_app_via_initprocess(4007);
                    return 0;
                }
                if (alt_status == TRUE){
                    //post_message_to_ws( (int) 77107, 0, 0 );
                }
                if (shift_status == TRUE){
                    //post_message_to_ws( (int) 88107, 0, 0 );
                }
                return 0;
                break;

            // Test 2.
            case VK_F8:
                if (ctrl_status == TRUE){
                    return 0;
                }
                if (alt_status == TRUE){
                    //post_message_to_ws( (int) 77108, 0, 0 );
                }
                if (shift_status == TRUE){
                    //post_message_to_ws( (int) 88108, 0, 0 );
                    // MSG_HOTKEY=8888 | 1 = Hotkey id 1.
                    post_message_to_ws( (int) MSG_HOTKEY, 1, 0 );
                }
                return 0;
                break;

            case VK_F9:
                // Enter ring0 embedded shell.
                if (ctrl_status == TRUE){
                    __enter_embedded_shell(FALSE);
                    return 0;
                }
                if (alt_status == TRUE){
                    //post_message_to_ws( (int) 77109, 0, 0 );
                }
                if (shift_status == TRUE){
                    // #goal
                    // This is a emergency keycombination.
                    // We can't call another process and 
                    // we want to reboot the machine.
                    sys_reboot();
                    //post_message_to_ws( (int) 88109, 0, 0 );
                }
                return 0;
                break;

            case VK_F10:
                // Exit ring0 embedded shell.
                if (ctrl_status == TRUE){
                    __exit_embedded_shell();
                    return 0;
                }
                if (alt_status == TRUE){
                    //post_message_to_ws( (int) 77110, 0, 0 );
                }
                if (shift_status == TRUE){
                    Background_initialize(COLOR_KERNEL_BACKGROUND);
                    show_slots();   //See: tlib.c
                    //pages_calc_mem();
                    //post_message_to_ws( (int) 88110, 0, 0 );
                    refresh_screen();
                }
                return 0;
                break;

            case VK_F11:
                // Mostra informaçoes sobre as threads.
                if (ctrl_status == TRUE){
                    show_slots();
                    return 0;
                }
                if (alt_status == TRUE){
                    //post_message_to_ws( (int) 77111, 0, 0 );
                }
                if (shift_status == TRUE){
                   hal_reboot();
                   //post_message_to_ws( (int) 88111, 0, 0 );
                }
                return 0;
                break;

            case VK_F12:
                // Mostra informaçoes sobre os processos.
                if (ctrl_status == TRUE){
                    show_process_information();
                    return 0;
                }
                if (alt_status == TRUE){
                    //post_message_to_ws( (int) 77112, 0, 0 );
                }

                // [SHIFT + F12]
                // Update desktop and show the mouse pointer.
                // IN: window, msg code, data1, data2.
                if (shift_status == TRUE){
                    post_message_to_ws( (int) 88112, 0, 0 );
                }
                return 0;
                break;

            default:
                // nothing
                return 0;
            }

// ==============
    default:
        return -1;
        break;
    };

//unexpected_fail:
    return -1;

fail:
    debug_print("wmProcedure: fail\n");
    //refresh_screen();
    return -1;
}


//----------------------------------------------

// called by I_init()
// OUT: return TRUE if its ok.
int init_gramado (void)
{
    debug_print ("init_gramado: [fixme]\n");
    return TRUE;
}

// windowLoadGramadoIcons:
// Carrega alguns ícones do sistema.
// It's a part of the window system's initialization.
int windowLoadGramadoIcons(void)
{
    unsigned long fRet=0;

    icon_cache.initialized = FALSE;

    //#debug
    //printf("windowLoadGramadoIcons:\n");

// ## Icon support ##
// iconSupport:
// Carregando alguns ícones básicos usados pelo sistema.
// ## size ##
// Vamos carregar ícones pequenos.
// @todo checar a validade dos ponteiros.
// #bugbug
// Size determinado, mas não sabemos o tamanho dos ícones.
// 4 pages.
// 16 KB ? Is it enough ?
// Sim, os ícones que estamos usam possuem no máximo 2KB.
// See: base/

    unsigned long tmp_size = (4*4096);
    icon_cache.size_in_bytes = (size_t) tmp_size;

// See: window.h
    icon_cache.app          = (void *) allocPages(4);
    icon_cache.file           = (void *) allocPages(4);
    icon_cache.folder      = (void *) allocPages(4);
    icon_cache.terminal  = (void *) allocPages(4);
    icon_cache.cursor      = (void *) allocPages(4);
    // ...

    if ( (void *) icon_cache.app == NULL ){
        printf ("windowLoadGramadoIcons: app\n");
        goto fail;
    }
    if ( (void *) icon_cache.file == NULL ){
        printf ("windowLoadGramadoIcons: file\n");
        goto fail;
    }
    if ( (void *) icon_cache.folder == NULL ){
        printf ("windowLoadGramadoIcons: folder\n");
        goto fail;
    }
    if ( (void *) icon_cache.terminal == NULL ){
        printf ("windowLoadGramadoIcons: terminal\n");
        goto fail;
    }
    if ( (void *) icon_cache.cursor == NULL ){
        printf ("windowLoadGramadoIcons: cursor\n");
        goto fail;
    }

//
// Load .BMP images.
//

// app icon
    fRet = 
        (unsigned long) fsLoadFile ( 
                            VOLUME1_FAT_ADDRESS,
                            VOLUME1_ROOTDIR_ADDRESS, 
                            FAT16_ROOT_ENTRIES,
                            "APP     BMP", 
                            (unsigned long) icon_cache.app,
                            tmp_size );
    if (fRet != 0){
        printf("windowLoadGramadoIcons: APP.BMP\n");
        goto fail;
    }

// file icon
    fRet = 
        (unsigned long) fsLoadFile ( 
                            VOLUME1_FAT_ADDRESS,
                            VOLUME1_ROOTDIR_ADDRESS, 
                            FAT16_ROOT_ENTRIES, 
                            "FILE    BMP", 
                            (unsigned long) icon_cache.file,
                            tmp_size );
    if (fRet != 0){
        printf("windowLoadGramadoIcons: FILE.BMP\n");
        goto fail;
    }

// folder icon
    fRet = 
        (unsigned long) fsLoadFile ( 
                            VOLUME1_FAT_ADDRESS, 
                            VOLUME1_ROOTDIR_ADDRESS, 
                            FAT16_ROOT_ENTRIES,
                            "FOLDER  BMP", 
                            (unsigned long) icon_cache.folder,
                            tmp_size );
    if (fRet != 0){
        printf("windowLoadGramadoIcons: FOLDER.BMP\n");
        goto fail;
    }

// terminal icon
    fRet = 
        (unsigned long) fsLoadFile ( 
                            VOLUME1_FAT_ADDRESS, 
                            VOLUME1_ROOTDIR_ADDRESS, 
                            FAT16_ROOT_ENTRIES, 
                            "TERMINALBMP", 
                            (unsigned long) icon_cache.terminal,
                            tmp_size );
    if (fRet != 0){
        printf("windowLoadGramadoIcons: TERMINAL.BMP\n");
        goto fail;
    }

// cursor icon
    fRet = 
        (unsigned long) fsLoadFile ( 
                            VOLUME1_FAT_ADDRESS, 
                            VOLUME1_ROOTDIR_ADDRESS, 
                            FAT16_ROOT_ENTRIES,
                            "CURSOR  BMP", 
                            (unsigned long) icon_cache.cursor,
                            tmp_size );
    if (fRet != 0){
        printf("windowLoadGramadoIcons: CURSOR.BMP\n");
        goto fail;
    }

// More?
// Podemos checar se eles foram carregados corretamente,
// conferindo apenas a assinatura em cada um deles.
    icon_cache.initialized = TRUE;
    return 0;
fail:
    icon_cache.initialized = FALSE;
    panic ("windowLoadGramadoIcons: Fail\n");
    return -1;
}

// Get a shared buffer to a system icon.
// it is gonna be used by the window server.
// It is a pre allocated buffer containg an bmp icon loaded at it.
// Service 9100
// See: window.h

void *ui_get_system_icon(int n)
{
    if (icon_cache.initialized != TRUE){
        return NULL;
    }

    if (n < 1 || n > 5){
        return NULL;
    }

// #bugbug
// This is very unsafe.
// The app can mess up our memory.
// #todo
// Only the window server can access this routine.

    switch (n){
    case 1: return (void *) icon_cache.app;       break;
    case 2: return (void *) icon_cache.file;      break;
    case 3: return (void *) icon_cache.folder;    break;
    case 4: return (void *) icon_cache.terminal;  break;
    case 5: return (void *) icon_cache.cursor;    break;
    // ...
    };

    return NULL;
}

unsigned long get_update_screen_frequency(void)
{
    return (unsigned long) flush_fps;
}

void set_update_screen_frequency(unsigned long fps)
{
    if (fps==0)   { fps=1; };
    if (fps>=1000){ fps=1000; };

// See: sched.h
    flush_fps = (unsigned long) (fps&0xFFFF);
    presence_level = (unsigned long) (1000/flush_fps);
    presence_level = (unsigned long) (presence_level & 0xFFFF);
}

unsigned long get_presence_level(void)
{
    return (unsigned long) presence_level;
}

void set_presence_level(unsigned long value)
{
    if (value==0)  { value=1; }
    if (value>1000){ value=1000; }
    presence_level = value;
}

// Called by task_switch
void schedulerUpdateScreen(void)
{
    register int i=0;
    struct thread_d *TmpThread;

    unsigned long deviceWidth  = (unsigned long) screenGetWidth();
    unsigned long deviceHeight = (unsigned long) screenGetHeight();
    if ( deviceWidth == 0 || deviceHeight == 0 ){
        debug_print ("schedulerUpdateScreen: w h\n");
        panic       ("schedulerUpdateScreen: w h\n");
    }

// Atualizado pelo timer.
    if (UpdateScreenFlag != TRUE){
        return;
    }

    deviceWidth  = (deviceWidth & 0xFFFF);
    deviceHeight = (deviceHeight & 0xFFFF);

// ============================
// Precisamos apenas validar todos retangulos
// porque fizemos refresh da tela toda.
    
    int validate_all= FALSE;

// Flush the whole screen and exit.
// The whole screen is invalidated.
    if (screen_is_dirty == TRUE)
    {
        refresh_screen();
        validate_all = TRUE;
        // Validate the screen
        screen_is_dirty = FALSE;
    }

/*
//=========================
// Blue bar:
    unsigned long fps = get_update_screen_frequency();
    char data[32];
    backbuffer_draw_rectangle( 
        0, 0, deviceWidth, 24, COLOR_KERNEL_BACKGROUND, 0 );
    sprintf(data,"  FPS %d       ",fps);
    data[12]=0;
    draw_string(0,8,COLOR_YELLOW,data);
    refresh_rectangle ( 0, 0, deviceWidth, 24 );
//=========================
*/


// Flush a list of dirty surfaces.

    for ( i=0; i < THREAD_COUNT_MAX; ++i )
    {
        TmpThread = (void *) threadList[i];

        if ( (void *) TmpThread != NULL )
        {
            if ( TmpThread->used == TRUE && 
                 TmpThread->magic == 1234 && 
                 TmpThread->state == READY )
            {
                // #test 
                debug_print("  ---- Compositor ----  \n");
                
                if ( (void *) TmpThread->surface_rect != NULL )
                {
                    if ( TmpThread->surface_rect->used == TRUE && 
                         TmpThread->surface_rect->magic == 1234 )
                    {
                        // Como fizemos refresh da tela toda,
                        // então precisamos validar todos os retângulos.
                        
                        if ( validate_all == TRUE )
                            TmpThread->surface_rect->dirty = FALSE;

                        // dirty rectangle
                        // Se uma surface está suja de tinta.
                        // Precisamos copiar para o framebuffer.

                        if ( TmpThread->surface_rect->dirty == TRUE )
                        {
                            refresh_rectangle ( 
                                TmpThread->surface_rect->left, 
                                TmpThread->surface_rect->top, 
                                TmpThread->surface_rect->width, 
                                TmpThread->surface_rect->height );

                            // Validate the surface. (Rectangle)
                            TmpThread->surface_rect->dirty = FALSE;
                        }

                    }
                }
            }
        }
    };

// Chamamos o 3d demo do kernel.
// See: kgws.c

    if (DemoFlag==TRUE)
    {
        //demo0();
        DemoFlag=FALSE;
    }

// Atualizado pelo timer.
    UpdateScreenFlag = FALSE;
}

