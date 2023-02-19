
// grinput.c

#include <kernel.h>


//keyboard support
//#define KEYBOARD_KEY_PRESSED  0x80
#define KEYBOARD_KEY_MASK  0x7F
//#define KEYBOARD_FULL      1
//#define KEYBOARD_EMPTY     0
//#define KEYBOARD_OBF       0x01    //Output buffer flag.


static int 
__ProcessExtendedKeyboardKeyStroke(
    int prefix,
    int msg, 
    unsigned long vk,
    unsigned long rawbyte );
    
// ------------------------------
    
//private
static int 
__ProcessExtendedKeyboardKeyStroke(
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
// Called by the mouse handler.

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

// ----------------------------------------------
// wmKeyEvent:
// This is basically the low level support for the
// ps2 keyboard on Gramado OS.
// We are called from the embedded ps2 keyboard device driver.
// :: We are called, we do not read data from a file provided
// by the device driver.
// We post the message into the stdin file and into the
// control thread of the Window Server and sometimes
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
// Called by the keyboard handler.

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

    // #todo
    //if ( raw_byte & 0x80 )
    //    Break = TRUE;

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
        __ProcessExtendedKeyboardKeyStroke(
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
            // Nenhuma tecla de controle esta acionada,
            // então vamos colocar a tecla no arquivo de input.
            // Somente keydown. (make).
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

int wmTimerEvent(int signature)
{
// Called by the timer handler.

    if (signature!=1234)
        return -1;

//--------------------
// It is time to flush the dirty rectangles
// in the window server.
// 1000/16*4 = 15,625 fps.
// #test 60fps com o pit a 1000.
// 1000/16*1 = 62.5
// 1000/16*2 = 31,25
// 1000/16*3 = 20,83
// 1000/16*4 = 15,625
// ::: Reset callback stuff.
// Reconfigura os dados sobre o callback.
// #todo: Podemos ter uma estrutura para eles.
// Acho que o assembly importa esses valores,
// e é mais difícil importar de estruturas.

    if ( ws_callback_info.initialized == TRUE )
    {
        if ( ws_callback_info.each_n_ms < 1 ||
              ws_callback_info.each_n_ms > JIFFY_FREQ )
        {
            panic ("PIT: Invalid ws_callback_info.each_n_ms\n");
        }
 
        if ( (jiffies % (ws_callback_info.each_n_ms) ) == 0 )
        {
            // reinitialize callback based on the saved value.
                if ( ws_callback_info.callback_address_saved != 0 )
                {
                    setup_callback(
                        ws_callback_info.callback_address_saved,
                        ws_callback_info.each_n_ms );
               }
        }
    }
//--------------------

    return 0;
}




