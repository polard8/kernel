
// kgwm.c
// Events and wm inside the kernel.

#include <kernel.h> 


// 
// Imports
//

// from swlib.asm
// Used to handle callbacks used by the window server.
extern unsigned long wmData_RDI;
extern unsigned long wmData_RSI;
extern unsigned long wmData_RDX;
extern unsigned long wmData_RCX;
extern unsigned long wmWindowMananer_SendMessage(void);


// from swlib.asm
// Used to handle callbacks used by the window server.
extern unsigned long wmData_Callback0;
extern unsigned long wmData_Callback1;
extern unsigned long wmData_Callback2;


//keyboard support
//#define KEYBOARD_KEY_PRESSED  0x80
#define KEYBOARD_KEY_MASK  0x7F
//#define KEYBOARD_FULL      1
//#define KEYBOARD_EMPTY     0
//#define KEYBOARD_OBF       0x01    //Output buffer flag.


//--------------------------------------
// Ponteiros para ícones
// Ponteiros para o endereço onde os ícones 
// foram carregados.
// queremos saber se o endereço alocado eh compartilhado ...
// para o window server usar ... entao chamaremos de sharedbufferIcon.

void *shared_buffer_app_icon;  //1
void *shared_buffer_file_icon; 
void *shared_buffer_folder_icon;
void *shared_buffer_terminal_icon;
void *shared_buffer_cursor_icon;
// ... 

int zorder=0;
int zorderCounter=0;         //contador de janelas incluidas nessa lista.   
int zorderTopWindow=0;
//...


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

static int 
wmProcedure ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );

static int __feedSTDIN( unsigned long ch );
static void __launch_app_via_initprocess(int index);
static void __enter_embedded_shell(int kernel_in_debug_mode);
static void __exit_embedded_shell(void);

static int 
__wmProcessExtendedKeyboardKeyStroke(
    int prefix,
    int msg, 
    unsigned long vk,
    unsigned long rawbyte );

static unsigned long __last_tick(void);

// ============================

// Register callbacks sent by gwssrv.bin
void 
wmRegisterWSCallbacks(
    unsigned long callback0,
    unsigned long callback1,
    unsigned long callback2 )
{
    printf("wmRegisterWSCallbacks:\n");

    gUseWMCallbacks = TRUE;

// Save callbacks
// See: swlib.asm
    wmData_Callback0 = (unsigned long) callback0;
    wmData_Callback1 = (unsigned long) callback1;
    wmData_Callback2 = (unsigned long) callback2;

    if ( wmData_Callback0 == 0 ||
          wmData_Callback1 == 0 ||
          wmData_Callback2 == 0  )
    {
        panic("wmRegisterWSCallbacks: Invalid callbacks\n");
    }

//#debug

    //printf("wmData_Callback0 = %x \n", wmData_Callback0);
    //printf("wmData_Callback0 = %x \n", wmData_Callback1);
    //printf("wmData_Callback0 = %x \n", wmData_Callback2);

    // No while.
    // scroll will not work
    //while(1){
        //asm("call *%0" : : "r"(wsCallbacks[0]));
    //}
    

//done:
    //printf("done\n");

// #importante
// Nesse momento podemos criar
// interrupçoes para esses endereços.

    refresh_screen();
    //while(1){}
}

static unsigned long __last_tick(void)
{
    return (unsigned long) jiffies;
}

// #
// This callback is not used at the moment.
// We're gonna use this to call some routines
// inside the kernel modules.
// Send input to the window manager
// inside the window server ( gwssrv.bin )
unsigned long 
wmSendInputToWindowManager(
    unsigned long wid,
    unsigned long msg,
    unsigned long long1,
    unsigned long long2)
{

// We can't!
    if( gUseWMCallbacks != TRUE )
        return 0;

    //asm("call *%0" : : "r"(wsCallbacks[0]));

// Setup parameters
// See: swlib.asm

    wmData_RDI = (unsigned long) (wid & 0xFFFF); 
    wmData_RSI = (unsigned long) (msg & 0xFFFF);
    wmData_RDX = (unsigned long) long1;
    wmData_RCX = (unsigned long) long2;

// Trampoline
// See: swlib.asm
    return (unsigned long) wmWindowMananer_SendMessage();
}


//#todo: Talvez essa rotina possa ir pra outro lugar.
// talvez na lib.
static int __feedSTDIN( unsigned long ch )
{
    //char Data = (char) (ch & 0x7F);
    char Data = (char) (ch & 0xFF);
    char ch_buffer[2];

    if ( (void*) stdin == NULL ){
        goto fail;
    }
    if (stdin->used != TRUE) { return -1; }
    if (stdin->magic != 1234){ return -1; }

// Can write.
    stdin->sync.can_write = TRUE;
// Can write and read.
    stdin->_flags = __SWR;
// Data
    ch_buffer[0] = (char) (Data & 0xFF);

// Write
// Write 1 byte.

    file_write_buffer ( 
        (file *) stdin, 
        (char *) ch_buffer, 
        (int) 1 );

// Can read.
// O aplicativo precisa disso.
    stdin->sync.can_read = TRUE;
// Can read.
// O worker no kernel precisa disso.
    stdin->_flags = __SRD;
    return 0;
fail:
    return -1;
}


// local
// Launch an app via init process.
// Just a small range of messages are accepted.
// See: gramado/core/client
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
        NULL,                   // window
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
// update desktop
    if ( gUseWMCallbacks == TRUE ){
         //wmSendInputToWindowManager(0,9092,0,0);
    }
// done
    ShellFlag = FALSE;
}


void exit_kernel_console(void)
{
// Se estavamos no ambiente de desktop completo
// e nao no modo debug.
// se temos callbacks e' porque o window server inicializou isso.
    if ( gUseWMCallbacks == TRUE ){
        __exit_embedded_shell();
    }
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
// Local function.
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

static int 
wmProcedure ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{
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
                    post_message_to_ws( NULL, MSG_COPY, long1, long2 );
                    return 0;
                }

                if (ctrl_status == TRUE && long1 == 'v'){
                    post_message_to_ws( NULL, MSG_PASTE, long1, long2 );
                    return 0;
                }

                if (ctrl_status == TRUE && long1 == 'x'){
                    post_message_to_ws( NULL, MSG_CUT, long1, long2 );
                    return 0;
                }

                if (ctrl_status == TRUE && long1 == 'z'){
                    post_message_to_ws( NULL, MSG_UNDO, long1, long2 );
                    return 0;
                }

                if (ctrl_status == TRUE && long1 == 'a'){
                    post_message_to_ws( NULL, MSG_SELECT_ALL, long1, long2 );
                    return 0;
                }

                if (ctrl_status == TRUE && long1 == 'f'){
                    post_message_to_ws( NULL, MSG_FIND, long1, long2 );
                    return 0;
                }

                if (ctrl_status == TRUE && long1 == 's'){
                    post_message_to_ws( NULL, MSG_SAVE, long1, long2 );
                    return 0;
                }

                // ...

                // No caso da combinação não ter sido tratada na rotina acima.
                // Enviamos combinação de [shift + tecla] de digitaçao.
                post_message_to_ws( NULL, msg, long1, long2 );
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
                    //post_message_to_ws( NULL, (int) 77101,0, 0 );
                }
                if (shift_status == TRUE){
                    jobcontrol_switch_console(0);
                    //post_message_to_ws( NULL, (int) 88101,0, 0 );
                }
                return 0;
                break;

            case VK_F2:
                if (ctrl_status == TRUE){
                     __launch_app_via_initprocess(4002);  //fileman
                     return 0;
                }
                if (alt_status == TRUE){
                    //post_message_to_ws( NULL, (int) 77102,0, 0 );
                }
                if (shift_status == TRUE){
                    jobcontrol_switch_console(1);
                    //post_message_to_ws( NULL, (int) 88102,0, 0 );
                }
                return 0;
                break;

            case VK_F3:
                if (ctrl_status == TRUE){
                    __launch_app_via_initprocess(4003);  //editor
                    return 0;
                }
                if (alt_status == TRUE){
                    //post_message_to_ws( NULL, (int) 77103,0, 0 );
                }
                if (shift_status == TRUE){
                    jobcontrol_switch_console(2);
                    //post_message_to_ws( NULL, (int) 88103,0, 0 );
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
                    //post_message_to_ws( 
                    //    NULL, 33888, 0, 0 ); //#TEST
                    return 0;
                }
                // alt+f4: The vm handle this combination.
                // We can't use it on vms.
                if (alt_status == TRUE){
                    //post_message_to_ws( NULL, (int) 77104,0, 0 );
                    return 0;
                }
                if (shift_status == TRUE){
                    jobcontrol_switch_console(3);
                    //post_message_to_ws( NULL, (int) 88104,0, 0 );
                }
                return 0;
                break;

            // Reboot
            case VK_F5:
                if (ctrl_status == TRUE){
                    //__launch_app_via_initprocess(4005);
                    //post_message_to_ws( 
                        //NULL, 33888, 0, 0 ); //#TEST
                    return 0;
                }
                if (alt_status == TRUE){
                    //post_message_to_ws( NULL, (int) 77105,0, 0 );
                }
                if (shift_status == TRUE){
                    //post_message_to_ws( NULL, (int) 88105,0, 0 );
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
                    //post_message_to_ws( NULL, (int) 77106,0, 0 );
                }
                if (shift_status == TRUE){
                    //post_message_to_ws( NULL, (int) 88106,0, 0 );
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
                    //post_message_to_ws( NULL, (int) 77107,0, 0 );
                }
                if (shift_status == TRUE){
                    //post_message_to_ws( NULL, (int) 88107,0, 0 );
                }
                return 0;
                break;

            // Test 2.
            case VK_F8:
                if (ctrl_status == TRUE){
                    return 0;
                }
                if (alt_status == TRUE){
                    //post_message_to_ws( NULL, (int) 77108,0, 0 );
                }
                if (shift_status == TRUE){
                    //post_message_to_ws( NULL, (int) 88108,0, 0 );
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
                    //post_message_to_ws( NULL, (int) 77109,0, 0 );
                }
                if (shift_status == TRUE){
                    // #goal
                    // This is a emergency keycombination.
                    // We can't call another process and 
                    // we want to reboot the machine.
                    sys_reboot();
                    //post_message_to_ws( NULL, (int) 88109,0, 0 );
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
                    //post_message_to_ws( NULL, (int) 77110,0, 0 );
                }
                if (shift_status == TRUE){
                    Background_initialize(COLOR_KERNEL_BACKGROUND);
                    show_slots();   //See: tlib.c
                    //pages_calc_mem();
                    //post_message_to_ws( NULL, (int) 88110,0, 0 );
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
                    //post_message_to_ws( NULL, (int) 77111,0, 0 );
                }
                if (shift_status == TRUE){
                   hal_reboot();
                   //post_message_to_ws( NULL, (int) 88111,0, 0 );
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
                    //post_message_to_ws( NULL, (int) 77112,0, 0 );
                }

                // [SHIFT + F12]
                // Update desktop and show the mouse pointer.
                // IN: window, msg code, data1, data2.
                if (shift_status == TRUE){
                    post_message_to_ws( NULL, (int) 88112,0, 0 );
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
    refresh_screen();
    return -1;
}

//private
static int 
__wmProcessExtendedKeyboardKeyStroke(
    int prefix,
    int msg, 
    unsigned long vk,
    unsigned long rawbyte )
{

/*
 Scancodes:
 Notebook acer, abnt2. ubuntu.
 see: vk.h and kbdabnt2.h.

             down | up
 pause     = 0x1D | 0x9D
 ins       = 0x52 | 0xD2
 del       = 0x53 | 0xD3
 home      = 0x47 | 0xC7
 pgup      = 0x49 | 0xC9
 pgdn      = 0x51 | 0xD1
 end       = 0x4F | 0xCF
 right     = 0x4D | 0xCD
 up        = 0x48 | 0xC8
 down      = 0x50 | 0xD0
 left      = 0x4B | 0xCB
 r-control = 0x1D | 0x9D
 sys menu  = 0x5D | 0xDD
 altgr     = 0x38 | 0xB8
 */

    //printf("kgwm.c: #todo Extended keyboard\n");
    //printf("sc={%x}\n",scancode);
    //refresh_screen();

    if (rawbyte >= 0xFF){
        return -1;
    }

    unsigned long scancode = (unsigned long) (rawbyte & 0x7F);

    switch (scancode)
    {
        case 0x1D: //pause, r-control
            break;
        case 0x52: //ins
            post_message_to_ws( NULL, MSG_INSERT, 0, scancode );
            break;
        case 0x53:  //del
            post_message_to_ws( NULL, MSG_CLEAR, 0, scancode );
            break;
        case 0x47:  //home
            break;
        case 0x49:  //pgup
            break;
        case 0x51:  //pgdn
            break;
        case 0x4F:  //end
            break;
            
        //#bugbug
        //Suspenso o keydown e arrow
        //pois atrapalha as teclas de digitação.

        case 0x4D:  //right
            if(ctrl_status==TRUE){
                post_message_to_ws( NULL, MSG_CONTROL_ARROW_RIGHT, VK_RIGHT, scancode );
                return 0;
            }
            //post_message_to_ws( NULL, MSG_KEYDOWN, VK_RIGHT, scancode );
            break;
        case 0x48:  //up
            if(ctrl_status==TRUE){
                post_message_to_ws( NULL, MSG_CONTROL_ARROW_UP, VK_UP, scancode );
                return 0;
            }
            //post_message_to_ws( NULL, MSG_KEYDOWN, VK_UP, scancode );
            break;
        case 0x50:  //down
            if(ctrl_status==TRUE){
                post_message_to_ws( NULL, MSG_CONTROL_ARROW_DOWN, VK_DOWN, scancode );
                return 0;
            }
            //post_message_to_ws( NULL, MSG_KEYDOWN, VK_DOWN, scancode );
            break;
        case 0x4B:  //left
            if(ctrl_status==TRUE){
                post_message_to_ws( NULL, MSG_CONTROL_ARROW_LEFT, VK_LEFT, scancode );
                return 0;
            }
            //post_message_to_ws( NULL, MSG_KEYDOWN, VK_LEFT, scancode );
            break;

        case 0x5D:  //sysmenu (app)
            break;
        case 0x38:  //altgr
            break;

        // ...
        default:
            break;
    };

    return 0;
}


// ----------------------------------------------
// wmKeyEvent:
// This is basically the low level support for the
// ps2 keyboard on Gramado OS.
// We are called from the embedded ps2 keyboard device driver.
// :: We are called, we do not read data from a file provided
// by the device driver.
// We post the message into the stdin file and into the
// control thread of the widnow server and sometimes
// we process the input before sending a message.
// ----------------------------------------------
// Envia uma mensagem de teclado para a janela com o 
// foco de entrada.
// Called by DeviceInterface_PS2Keyboard in ps2kbd.c
// Pega um scancode, transforma em caractere e envia 
// na forma de mensagem para a thread de controle associada 
// com a janela que tem o foco de entrada.
// #todo
// #importante
// Precisa conferir ke0 antes de construir a mensagem,
// para assim usar o array certo. ke0 indica o teclado estendido.
// #todo
// Na verdade é 'translate' and 'dispatch'.
// Cria o evento usando o rawbyte, traduz o raw byte para ascii,
// e por fim envia para o buffer da tty de teclado e para
// a thread do processo em foreground. Tudo depende
// do input mode.
// Called by console_interrupt() in console.c
// and by the kdb device driver in ps2kbd.c.
// Is this the forground thread?
// #bugbug: Não estamos usando o parâmetro tid.
// Lembrando que numa interrupção de teclado,
// não temos o contexto salvo. Então não podemos chamar o
// scheduler. Mas podemos acionar uma flag
// que de alguma direção para o escalonador.
// Pega um scancode, transforma em caractere e envia na forma de mensagem
// para a thread de controle associada com a janela que tem o foco de entrada.
// + Build the message and send it to the thread's queue.
// This routine will select the target thread.
// + Or send the message to the input TTY.
// This way the foreground process is able to get this data.
// See: ps2kbd.c
// See: console.c
// IN: 
// device type, data.
// 1 = keyboard
// Call the event handler.
// Console interrupt
// Valid foreground thread.
// Handler for keyboard input.
// See: kgwm.c
// ##
// Nesse caso o driver esta chamando a rotina
// que lida com o evento. Mas o plano é apenas
// colocar os eventos de teclado em um arquivo
// que poderá ser aberto e lido pelo window server.
// IN:
// target thread, raw byte 

int 
wmKeyEvent( 
    unsigned char raw_byte,
    int prefix )
{
// Post keyboard event to the current foreground thread.

    int Prefix = (int) (prefix & 0xFF);

// Step 0 
// Declarações de variáveis.

    //struct process_d  *__p;
    //struct thread_d   *t;

    unsigned long status = 0;
    int msg_status = -1;
    int save_pos = 0;

// Pegando o argumento e convertendo para ascii
    unsigned char Keyboard_RawByte  =0;
    unsigned char Keyboard_ScanCode =0;    // The scancode.

    //==============
    // [event block]
    struct window_d  *Event_Window;            //arg1 - window pointer
    int               Event_Message       =0;  //arg2 - message number
    unsigned long     Event_LongASCIICode =0;  //arg3 - ascii code (vk)
    unsigned long     Event_LongRawByte   =0;  //arg4 - raw byte
    //===================

// #test
// Not working yet.
    //struct thread_d *input_thread;
    //input_thread = (struct thread_d *) threadList[tid];
    //input_thread->quantum = 20;

    // Inicializando a janela, 
    // pois os outros elementos já foram incializados logo acima.
    Event_Window = NULL;

    // true for keyup and false for keydown.
    // int Break = TRUE;

//#todo
    //debug_print("xxxKeyEvent:\n");

    //if (tid<0 || tid >= THREAD_COUNT_MAX)
    //{
    //    debug_print("wmKeyEvent: tid\n");
    //    return (int) (-1);
    //}


// =============
// Step1
// Pegar o RawByte.
// O driver pegou o scancode e passou para a disciplina de linha 
// através de parâmetro.

    Keyboard_RawByte = raw_byte;

/*
// #test
// prefix
    if (KEY_E0 true)
        wordKeyboard_RawByte |= 0xE000;
    if (KEY_E1 true)
        wordKeyboard_RawByte |= 0xE100;
*/


    //if ( Keyboard_RawByte == 0 )
        //return -1;

    if (Keyboard_RawByte == 0xFF){
        return -1;
    }

// #todo
// The last byte was a prefix
    //if( __has_e0_prefix == 1 )
        //goto GotE0;

// #todo
// The last byte was a prefix
    //if(__has_e1_prefix == 1 )
        //goto GotE1;

//
// Debug
//

// ++
// ===================

    // #debug.
    // Show the scancode if the flag is enabled.
    // Talvez isso nem seja necess'ario.
    
    // #hackhack
    // Variable not initialized yet.

    /*
    scStatus = FALSE;
    if (scStatus == TRUE){
        printf ("raw byte {%d,%x} \n", 
            Keyboard_RawByte, Keyboard_RawByte );
        // Refresh screen?
        refresh_screen();
    }
    */

// ===================
// --

// #todo
// Enable these shortcuts
// Se temos a flag ou não
    //if ( Keyboard_RawByte > 0x7F )
         //goto key_released;
    //if ( Keyboard_RawByte < 0x7F )
         //goto key_pressed;


// ==========
// Step 2
// Tratar as mensagens.
// Traduzir rawbyte em evento.

// #test
    //int isDown=0;
    //isDown = !(Keyboard_RawByte & 0x80);

// ================================================
//key_released:

    // Não está pressioanda
    if ( (Keyboard_RawByte & 0x80) != 0 )
    {
        // Break = TRUE;
        // Desativando o bit de paridade caso esteja ligado.
        Keyboard_ScanCode = Keyboard_RawByte;
        Keyboard_ScanCode &= KEYBOARD_KEY_MASK;

        // Configurando se é do sistema ou não.
        // #todo: 
        // Aqui podemos chamar uma rotina interna que faça essa checagem.
        // Os primeiros 'case' é quando libera tecla do sistema.
        // O case 'default' é pra quando libera tecla que não é do sistema.

        switch (Keyboard_ScanCode)
        {
            // left shift liberado.
            case VK_LSHIFT: 
                shift_status = FALSE;  Event_Message = MSG_SYSKEYUP;
                //printf ("VK_LSHIFT: Liberada\n"); refresh_screen();
                break;

            // left control liberado.
            case VK_LCONTROL:
                ctrl_status = FALSE;  Event_Message = MSG_SYSKEYUP;
                //printf ("VK_LCONTROL: Liberada\n"); refresh_screen();
                break;

            // left winkey liberada.
            case VK_LWIN:
                winkey_status = FALSE;  Event_Message = MSG_SYSKEYUP;
                //printf ("VK_LWIN: Liberada\n"); refresh_screen();
                break;

            // left alt liberado.
            case VK_LMENU:
                alt_status = FALSE;  Event_Message = MSG_SYSKEYUP;
                //printf ("VK_LMENU: Liberada\n"); refresh_screen();
                break;

            // right winkey liberada.
            case VK_RWIN:
                winkey_status = FALSE;  Event_Message = MSG_SYSKEYUP;
                //printf ("VK_RWIN: Liberada\n"); refresh_screen();
                break;

            // control menu.
            case VK_CONTROL_MENU:
                //controlmenu_status = 0; //@todo
                Event_Message = MSG_SYSKEYUP;
                //printf ("VK_CONTROL_MENU: Liberada\n"); refresh_screen();
                break;

            //right control liberada.
            case VK_RCONTROL:
                ctrl_status = FALSE;  Event_Message = MSG_SYSKEYUP;
                //printf ("VK_RCONTROL: Liberada\n"); refresh_screen();
                break;

            // right Shift liberado.
            case VK_RSHIFT:
                shift_status = FALSE;  Event_Message = MSG_SYSKEYUP;
                //printf ("VK_RSHIFT: Liberada\n"); refresh_screen();
                break;

            // Funções liberadas.
            case VK_F1: case VK_F2: case VK_F3: case VK_F4:
            case VK_F5: case VK_F6: case VK_F7: case VK_F8:
            case VK_F9: case VK_F10: case VK_F11: case VK_F12:
                Event_Message = MSG_SYSKEYUP;
                break;

            // ...

            // A tecla liberada NÃO é do sistema.
            default:
                Event_Message = MSG_KEYUP;
                break;
        };

        // Selecionando o char para os casos de tecla liberada.
        
        // Analiza: 
        // Se for tecla normal, pega o mapa de caracteres apropriado.
        // minúscula
        // Nenhuma tecla de modificação ligada.

        // #bugbug: some chars are not working
        // for shift_abnt2[]
        // See: include/user/kbdabnt2.h
        if (Event_Message == MSG_KEYUP)
        {
            // Minúsculas.
            if (capslock_status == FALSE)
            { Event_LongASCIICode = map_abnt2[Keyboard_ScanCode];   goto done; }
            // Maiúsculas.
            if (capslock_status == TRUE)
            { Event_LongASCIICode = shift_abnt2[Keyboard_ScanCode]; goto done; }
            // ...
        }

        // Analiza: Se for do sistema usa o mapa de caracteres apropriado. 
        // Normal.
        
        if (Event_Message == MSG_SYSKEYUP)
        {   
            // se liberada teclas de sistema como capslock ligado
            if (capslock_status == FALSE)
            { Event_LongASCIICode = map_abnt2[Keyboard_ScanCode];   goto done; }
            // se liberada teclas de sistema como capslock desligado
            if (capslock_status == TRUE)
            { Event_LongASCIICode = shift_abnt2[Keyboard_ScanCode]; goto done; }
            // ...
        }

        // Nothing.
        goto done;
    }

// ================================================
// key_pressed:

    // Está pressionada.
    if ( (Keyboard_RawByte & 0x80) == 0 ) 
    {
        // Break = FALSE;

        Keyboard_ScanCode = Keyboard_RawByte;
        Keyboard_ScanCode &= KEYBOARD_KEY_MASK; //Desativando o bit de paridade caso esteja ligado.

        // O Último bit é zero para key press.
        // Checando se é a tecla pressionada é o sistema ou não.
        // #todo: 
        // Aqui podemos chamar uma rotina interna que faça essa checagem.

        switch (Keyboard_ScanCode)
        {
            // back space será tratado como tecla normal

            // #todo: tab,
            // tab será tratado como tecla normal por enquanto.

            // caps lock keydown
            // muda o status do capslock não importa o anterior.
            case VK_CAPITAL:
                if (capslock_status == FALSE){ 
                    capslock_status = TRUE; 
                    Event_Message = MSG_SYSKEYDOWN; 
                    break; 
                }
                if (capslock_status == TRUE){ 
                    capslock_status = FALSE; 
                    Event_Message = MSG_SYSKEYDOWN; 
                    break; 
                }
                break; 

            // left shift pressionada.
            // case KEY_SHIFT:
            case VK_LSHIFT:
                shift_status = TRUE;
                Event_Message = MSG_SYSKEYDOWN;
                break;

            // left control pressionada.
            // case KEY_CTRL:
            case VK_LCONTROL:
                ctrl_status = TRUE;
                Event_Message = MSG_SYSKEYDOWN;
                break;

            // left winkey pressionada.
            case VK_LWIN:
                winkey_status = TRUE; 
                Event_Message = MSG_SYSKEYDOWN;
                break;

            // left alt pressionada.
            case VK_LMENU:
                alt_status = TRUE;
                Event_Message = MSG_SYSKEYDOWN;
                break;

            // #todo 
            // alt gr.

            // right winkey pressionada.
            case VK_RWIN:
                winkey_status = TRUE;
                Event_Message = MSG_SYSKEYDOWN;
                break;

            // #todo: 
            // Control menu.

            // right control pressionada.
            case VK_RCONTROL:
                ctrl_status = TRUE;
                Event_Message = MSG_SYSKEYDOWN;
                break;

            // right shift pressionada.
            case VK_RSHIFT:
                shift_status = TRUE;
                Event_Message = MSG_SYSKEYDOWN;
                break;

            // Funções pressionadas.
            case VK_F1: case VK_F2: case VK_F3: case VK_F4:
            case VK_F5: case VK_F6: case VK_F7: case VK_F8:
            case VK_F9: case VK_F10: case VK_F11: case VK_F12:
                Event_Message = MSG_SYSKEYDOWN;
                break;

            // num Lock.
            // Muda o status do numlock não importa o anterior.
            case VK_NUMLOCK:
                if (numlock_status == FALSE){
                    numlock_status = TRUE;
                    Event_Message = MSG_SYSKEYDOWN;
                    break;
                }
                if (numlock_status == TRUE){ 
                    numlock_status = FALSE;
                    Event_Message = MSG_SYSKEYDOWN; 
                    break; 
                }
                break;

            // Scroll Lock.
            // Muda o status do numlock não importa o anterior.
            case VK_SCROLL:
                if (scrolllock_status == FALSE){  
                    scrolllock_status = TRUE;
                    Event_Message = MSG_SYSKEYDOWN;
                    break;
                }
                if (scrolllock_status == TRUE){ 
                    scrolllock_status = FALSE;
                    Event_Message = MSG_SYSKEYDOWN; 
                    break; 
                }
                break;

            //...

            // A tecla pressionada não é do sistema.
            default:
                // printf("keyboard debug: default: MSG_KEYDOWN\n");
                Event_Message = MSG_KEYDOWN;
                break;
        };

        // ==============================
        // Teclas de digitaçao
        // Uma tecla normal foi pressionada ou liberada
        // mensagem de digitação.
        if (Event_Message == MSG_KEYDOWN || Event_Message == MSG_KEYUP)
        {
            // Minúsculas.
            if (capslock_status == FALSE && shift_status == FALSE)
            { 
                Event_LongASCIICode = map_abnt2[Keyboard_ScanCode];
                //if (Prefix == 0xE0)
                //    panic("0xE0\n");
                //if (Prefix == 0xE1)
                // #todo: precisamos de uma map para teclado extendido abnt2.
                goto done; 
            }
            // Maiúsculas.
            if (capslock_status == TRUE || shift_status == TRUE)
            {
                Event_LongASCIICode = shift_abnt2[Keyboard_ScanCode];
                //if (Prefix == 0xE0)
                //if (Prefix == 0xE1)
                // #todo: precisamos de uma map para teclado extendido abnt2.
                goto done;
            }
            
            // ...
        }

        // ==============================
        // Teclas de sistema
        // Uma tecla do sistema foi pressionada ou liberada.
        if (Event_Message == MSG_SYSKEYDOWN || Event_Message == MSG_SYSKEYUP)
        {   
            // se pressionamos teclas de sistema como capslock ligado
            if (capslock_status == FALSE)
            { Event_LongASCIICode = map_abnt2[Keyboard_ScanCode];   goto done; }
            // se pressionamos teclas de sistema como capslock desligado
            if (capslock_status == TRUE || shift_status == TRUE)
            { Event_LongASCIICode = shift_abnt2[Keyboard_ScanCode]; goto done; }
            // ...
        }
        // Nothing
        goto done;
    }

//
// == Dispatch ====
//

// Done
// Para finalizar, vamos enviar a mensagem para fila certa.
// Fixing the rawbyte to fit in the message arg.
// See: kgwm.c

done:

    Event_LongRawByte = 
        (unsigned long) (Keyboard_RawByte & 0x000000FF);

// Não tem virtual key '0'.
    if (Event_LongASCIICode == 0){
        return -1;
    }

// ------------------------------------
// It is a extended keyboard key.
    if (Prefix == 0xE0 || Prefix== 0xE1)
    {
        __wmProcessExtendedKeyboardKeyStroke(
                (int) Prefix,
                (int) Event_Message, 
                (unsigned long) Event_LongASCIICode,
                (unsigned long) Event_LongRawByte );

        return 0;
    }

// #todo
// A sistema precisa ter uma flag
// para cada tipo de processamento aqui.
// ioctl() poderá mudar as configurações
// do dispositivo de teclado, determinando
// que tipo de recurso de processamento
// de input estará disponível.

// #todo
// Check 'control + alt + del'.
// Teclas de digitação.
// Manda para o window server.
// Ele vai imprimir na janela com foco de entrada
// e enviar mensagem para a thread com foco.

/*
    if ( Event_Message == MSG_KEYDOWN )
    {
        if ( ShellFlag!=TRUE ){
            wmSendInputToWindowManager(0, MSG_KEYDOWN, Event_LongASCIICode, Event_LongRawByte);
            return 0;
        }
    }
*/

// #test
// Colocando no arquivo.
// Não colocamos quando estivermos no modo 'console',
// pois nesse caso o aplicativo em ring3 receberia input de teclado
// e reagiria a esse input.
// Write:
// Estamos dentro do kernel.
// Vamos escrever diretamente no buffer do arquivo,
// dado seu ponteiro de estrutura.
// O fd do processo atual não serveria nesse momento.
// See: sys.c

    //char ch_buffer[2];

// ==================================
// Coloca no arquivo stdin.
// Envia para a thread de controle do window server.
// Colocamos no arquivo somente se não estivermos
// no modo console.

    if (ShellFlag != TRUE)
    {
        // Coloca no arquivo stdin.
        // Somente ascii.
        // #todo: Nesse caso da pra enviar os primeiros ascii
        // que representam comandos.
        if (Event_Message == MSG_KEYDOWN)
        {
            // Se uma tecla de controle estiver acionada,
            // então não mandamos o evento para o arquivo,
            // pois vamos chamar o procedimento local e
            // considerarmos a combinação de teclas, 
            // antes de enviarmos o evento.
            if ( alt_status != TRUE && 
                 ctrl_status != TRUE && 
                 shift_status != TRUE )
            {
                __feedSTDIN( (unsigned long) Event_LongASCIICode );
            }
        }

        // Envia para a thread de controle do window server.
        // Todo tipo de tecla.
        // Se uma tecla de controle estiver acionada,
        // então não mandamos o evento para a thread,
        // pois vamos chamar o procedimento local e
        // considerarmos a combinação de teclas, 
        // antes de enviarmos o evento.
        // O estado de capslock não importa aqui.
        if ( alt_status != TRUE && 
             ctrl_status != TRUE && 
             shift_status != TRUE )
        {
            post_message_to_ws(
                NULL, 
                Event_Message, 
                Event_LongASCIICode,
                Event_LongRawByte );
            
            // Não há tecla de controle pressionada.
            // então podemos retornar depois de termos
            // enviado uma mensagem para a thread.
            // Dessa forma, evitamos chamar o procedimento local.
            return 0;  //ok 
        }
    }

// Process the event using the system's window procedures.
// It can use the kernel's virtual console or
// send the event to the loadable window server.
// See: kgwm.c
// ##
// Acho que esses são os aceleradores de teclado.
// Então essa rotina somente será chamada se 
// os aceleradores de teclado estiverem habilitados.
// #todo
// precisamos de uma flag que indique que isso deve ser feito.

    int __Status=-1;

// Quando devemos processar internamente?
// + Somente quando uma tecla de controle estiver acionada.

// Uma flag global poderia nos dizer se devemos ou não
// processar algumas combinações. Mas o sistema deve
// sim processar algumas combinações, independente dos aplicativos.
// Como a chamada aos consoles do kernel ou control+alt+del.

    // ShellFlag == TRUE
    __Status = 
        (int) wmProcedure(
        (struct window_d *) Event_Window,    // opaque pointer
        (int)               Event_Message,
        (unsigned long)     Event_LongASCIICode,
        (unsigned long)     Event_LongRawByte );

    return (int) __Status;
}

// ----------------------------------------------
// wmMouseEvent:
// This is basically the low level support for the
// ps2 mouse on Gramado OS.
// We are called from the embedded ps2 mouse device driver.
// :: We are called, we do not read data from a file provided
// by the device driver.
// We post the message into the stdin file and into the
// control thread of the widnow server and sometimes
// we process the input before sending a message.
// ----------------------------------------------
// For mouse events, see: window.h
// #todo: change parameters.
// we need more information about the mouse event.
// called by __ps2mouse_parse_data_packet in ps2mouse.c
//  Post mouse events only to the window server's control thread.
// #todo
// Se uma tecla de controle estiver precionada,
// então podemos enviar o status das teclads de controle
// atraves do segundo long.

int 
wmMouseEvent(
    int event_id,
    long long1, 
    long long2 )
{
    int Status=-1;
    //static long old_x=0;
    //static long old_y=0;

// data:
    unsigned long button_number = 
        (unsigned long) (long1 & 0xFFFF);
    //unsigned long ? = long2;

    unsigned long deviceWidth = (unsigned long) screenGetWidth();
    unsigned long deviceHeight = (unsigned long) screenGetHeight();
    deviceWidth  = (unsigned long) (deviceWidth & 0xFFFF);
    deviceHeight = (unsigned long) (deviceHeight & 0xFFFF);
    if (deviceWidth==0 || deviceHeight==0){
        panic("wmMouseEvent: w h\n");
    }

// Event id:
    if (event_id<0){
        goto fail;
    }

// ====================================
// Button events:
// Buttons:
// Pressionado ou liberado.
// Post message.
// #todo
// Se uma tecla de controle estiver precionada,
// então podemos enviar o status das teclads de controle
// atraves do segundo long.
// IN: window pointer, event id, button number. button number.

    if ( event_id == MSG_MOUSEPRESSED || event_id == MSG_MOUSERELEASED )
    {
        // #todo: Send control keys status.
        post_message_to_ws( NULL, event_id, button_number, button_number );
        return 0;
    }

// ====================================
// mouse move events:

    //#debug
    //printf ("w:%d h:%d\n",deviceWidth, deviceHeight);
    //printf ("x:%d y:%d\n",long1, long2);
    //refresh_screen();
    //while(1){}

// #test
// Draw rectangle.
// #todo #bugbug
// Isso está falhando ...
// Existe algum problema na rotina de retângulo
// que gera PF. Provavelmente é alguma coisa na
// tipagem de algumas variáveis ... pois esse
// é um código portado da arquitetura de 32bit 
// para a arquitetura de 64bit.
// IN: window pointer, event id, x, y.

    if (event_id == MSG_MOUSEMOVE)
    {
        if (long1 < 1){ long1=1; }
        if (long2 < 1){ long2=1; }
        if ( long1 >= deviceWidth ) { long1 = (deviceWidth-1);  }
        if ( long2 >= deviceHeight ){ long2 = (deviceHeight-1); }

        post_message_to_ws(
            NULL, 
            event_id, 
            (unsigned long) long1, 
            (unsigned long) long2 );
        return 0;
    }

done:
    return 0;
fail:
    return -1;
}

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

// See: window.h
    shared_buffer_app_icon          = (void *) allocPages(4);
    shared_buffer_file_icon           = (void *) allocPages(4);
    shared_buffer_folder_icon      = (void *) allocPages(4);
    shared_buffer_terminal_icon  = (void *) allocPages(4);
    shared_buffer_cursor_icon      = (void *) allocPages(4);
    // ...

    if ( (void *) shared_buffer_app_icon == NULL ){
        panic ("windowLoadGramadoIcons: shared_buffer_app_icon\n");
    }
    if ( (void *) shared_buffer_file_icon == NULL ){
        panic ("windowLoadGramadoIcons: shared_buffer_file_icon\n");
    }
    if ( (void *) shared_buffer_folder_icon == NULL ){
        panic ("windowLoadGramadoIcons: shared_buffer_folder_icon\n");
    }
    if ( (void *) shared_buffer_terminal_icon == NULL ){
        panic ("windowLoadGramadoIcons: shared_buffer_terminal_icon\n");
    }
    if ( (void *) shared_buffer_cursor_icon == NULL ){
        panic ("windowLoadGramadoIcons: shared_buffer_cursor_icon\n");
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
                            (unsigned long) shared_buffer_app_icon,
                            tmp_size );
    if (fRet != 0){
        panic("windowLoadGramadoIcons: APP.BMP\n");
    }

// file icon
    fRet = 
        (unsigned long) fsLoadFile ( 
                            VOLUME1_FAT_ADDRESS,
                            VOLUME1_ROOTDIR_ADDRESS, 
                            FAT16_ROOT_ENTRIES, 
                            "FILE    BMP", 
                            (unsigned long) shared_buffer_file_icon,
                            tmp_size );
    if (fRet != 0){
        panic("windowLoadGramadoIcons: FILE.BMP\n");
    }

// folder icon
    fRet = 
        (unsigned long) fsLoadFile ( 
                            VOLUME1_FAT_ADDRESS, 
                            VOLUME1_ROOTDIR_ADDRESS, 
                            FAT16_ROOT_ENTRIES,
                            "FOLDER  BMP", 
                            (unsigned long) shared_buffer_folder_icon,
                            tmp_size );
    if (fRet != 0){
        panic("windowLoadGramadoIcons: FOLDER.BMP\n");
    }

// terminal icon
    fRet = 
        (unsigned long) fsLoadFile ( 
                            VOLUME1_FAT_ADDRESS, 
                            VOLUME1_ROOTDIR_ADDRESS, 
                            FAT16_ROOT_ENTRIES, 
                            "TERMINALBMP", 
                            (unsigned long) shared_buffer_terminal_icon,
                            tmp_size );
    if (fRet != 0){
        panic("windowLoadGramadoIcons: TERMINAL.BMP\n");
    }

// cursor icon
    fRet = 
        (unsigned long) fsLoadFile ( 
                            VOLUME1_FAT_ADDRESS, 
                            VOLUME1_ROOTDIR_ADDRESS, 
                            FAT16_ROOT_ENTRIES,
                            "CURSOR  BMP", 
                            (unsigned long) shared_buffer_cursor_icon,
                            tmp_size );
    if (fRet != 0){
        panic("windowLoadGramadoIcons: CURSOR.BMP\n");
    }

// More?
// Podemos checar se eles foram carregados corretamente,
// conferindo apenas a assinatura em cada um deles.

    return 0;
}

// Get a shared buffer to a system icon.
// it is gonna be used by the window server.
// It is a pre allocated buffer containg an bmp icon loaded at it.
// Service 9100
// See: window.h

void *ui_get_system_icon(int n)
{
    if (n <= 0){
        return NULL;
    }

// #bugbug
// This is very unsafe.
// The app can mess up our memory.
// #todo
// Only the window server can access this routine.

    switch (n){
    case 1: return (void *) shared_buffer_app_icon;       break;
    case 2: return (void *) shared_buffer_file_icon;      break;
    case 3: return (void *) shared_buffer_folder_icon;    break;
    case 4: return (void *) shared_buffer_terminal_icon;  break;
    case 5: return (void *) shared_buffer_cursor_icon;    break;
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
// Redraw and flush stuff.

// Calling the window manager inside the window server
// at gwssrv.bin
// 9091 = message code for calling the compositor.

    if (gUseWMCallbacks == TRUE){
        //wmSendInputToWindowManager(0,9091,0,0);
    }

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

