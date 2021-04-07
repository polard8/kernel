/*
 * File: kgws.c
 * 
 *     kgws - kernel gramado window server.
 * 
 * History:
 *     2019 -  Created by fred Nora.
 */
 
// Window Server into the kernel base.

#include <kernel.h>


static int EnableKGWS = TRUE;


int kgws_status;
int kgws_ws_PID;
int kgws_ws_status;


int kgws_mouse_event_mouse_buttom_1;
int kgws_mouse_event_mouse_buttom_2;
int kgws_mouse_event_mouse_buttom_3;

int kgws_mouse_event_old_mouse_buttom_1;
int kgws_mouse_event_old_mouse_buttom_2;
int kgws_mouse_event_old_mouse_buttom_3;


unsigned long kgws_mouse_event_saved_mouse_x;
unsigned long kgws_mouse_event_saved_mouse_y;
unsigned long kgws_mouse_event_mouse_x;
unsigned long kgws_mouse_event_mouse_y;

int kgws_mouse_event_moving;
int kgws_mouse_event_drag_status;

int kgws_mouse_event_button_pressed;

//se houve ou não alguma ação envolvendo botões.
int kgws_mouse_event_button_action;


int flagRefreshMouseOver;


//salvaremos aqui o último total ticks pra
//pegarmos um delta, se o delta for menor que o limite
//então temos um duploclick.
unsigned long kgws_current_totalticks;
unsigned long kgws_last_totalticks;
unsigned long kgws_delta_totalticks;

//==========================================================


void kgws_enable(void)
{
    debug_print("kgws_enable: Enable KGWS\n");
         printf("kgws_enable: Enable KGWS\n");
    refresh_screen();
    
    // Sending event messages to the thread associated with the wwf.
    current_input_mode = INPUT_MODE_SETUP;
    
    EnableKGWS = TRUE;
}


void kgws_disable(void)
{
    debug_print("kgws_disable: Disable KGWS\n");
         printf("kgws_disable: Disable KGWS\n");
    backgroundDraw(COLOR_RED);
    refresh_screen();
        
    // Using unix-like TTY mode for input.
    // using the stdin.
    current_input_mode = INPUT_MODE_TTY;
    
    EnableKGWS = FALSE;
}



//=================================

/*
 ******************* 
 * kgws_put_console:
 * 
 *     Colocamos na tty PS2KeyboardDeviceTTY ou imprimimos na tela.
 * 
 */

// Somente para SETUP INPUT MODE.

int 
kgws_put_console ( 
    struct window_d *window, 
    int message,
    unsigned long ascii_code,
    unsigned long raw_byte )
{

    //==============
    // [event block]
    struct window_d  *Event_Window;            //arg1 - window pointer
    int               Event_Message       =0;  //arg2 - message number
    unsigned long     Event_LongASCIICode =0;  //arg3 - ascii code
    unsigned long     Event_LongRawByte   =0;  //arg4 - raw byte
    //===================


    // setup event block
    // get parameters.
    
    Event_Window        = (struct window_d  *) window;
    Event_Message       = message;
    Event_LongASCIICode = ascii_code;
    Event_LongRawByte   = raw_byte;


    // ===========================

    // #todo
    // Send the message to the TYY,
    // this way the foreground process is able to read it
    // using stdin.
    // See:
    // devmgr.h ps2kbd.c
    // ...
    
    // only one standard event
    unsigned long event_buffer[5];


    int i=0;    //iterator.
    char bugBuffer[4];


    //
    // SETUP INPUT MODE
    //

    if ( current_input_mode == INPUT_MODE_SETUP )
    {
        printf("kgws_put_console: This routine is only for SETUP INPUT MODE\n");
        goto fail;
        //refresh_screen();
        //return -1;
    }


    //
    // TTY INPUT MODE
    //

    if ( current_input_mode == INPUT_MODE_TTY )
    {

        if ( (void *) PS2KeyboardDeviceTTY != NULL )
        {
            // ok. This is a valid tty pointer.
       
        // #test
        // Let's write something ...
            event_buffer[0] = (unsigned long) Event_Window;                      // window pointer 
            event_buffer[1] = (unsigned long) Event_Message;                     // message number.
            event_buffer[2] = (unsigned long) Event_LongASCIICode & 0x000000ff;  // ascii code
            event_buffer[3] = (unsigned long) Event_LongRawByte   & 0x000000ff;  // raw byte
       
        // #todo
        // >> PS2KeyboardDeviceTTY->_rbuffer
        // No buffer 'bruto' colocamos os raw bytes.
        // >> PS2KeyboardDeviceTTY->_cbuffer
        // No buffer 'canonico' colocamos os ascii codes.
        // ps: nao usaremos o buffer de output no caso do teclado. 
        
        //devemos cheacar se o tty esta configurado para
        //escrever na fila bruta ou canonica e escrevermos no lugar certo
        //Do mesmo modo deve ser a leitura.
        //a configuraçao pode ser feita em ring3// see:ioctl
        // esse tipo de decisao deve ficar dentro das rotinas de leitura e escrita e nao aqui.
        
        //quanto a fila eh canonica, escrevemos somente os keydown.
                
            //xxxbug[0] = 'x';  //fake bytes
            bugBuffer[0] = Event_LongASCIICode & 0x000000ff;

        // ?? #bugbug
        // Explique melhor isso. ... estamos escrevendo um byte 
        // no arquivo '0' ???
        //if ( Event_Message == MSG_KEYDOWN)
            sys_write(0,bugBuffer,1);
        
        // coloca o raw byte no buffer de raw byte.
        //file_write_buffer ( PS2KeyboardDeviceTTY->_rbuffer, "dirty", 5);
        
            //canonica
            //if ( Event_Message == MSG_KEYDOWN)
            file_write_buffer ( PS2KeyboardDeviceTTY->_cbuffer, bugBuffer , 1);
        
        // #bugbug
        // Estamos colocando um evento no buffer 'bruto'.
       
        // it is gonna write in the base of the buffer.
        // >> Essa rotina escreve na fila bruta. (raw buffer).
        // See: tty.c
        
        //__tty_write ( 
        //    (struct tty_d *) PS2KeyboardDeviceTTY, 
        //    (char *) event_buffer, 
        //    (int) (4*4) );  //16 bytes = apenas um evento.
         
         // Sinalizamos que temos um novo evento.
         
         // #todo
         // Precisamos de uma flag que diga que é para imprimirmos na tela.
         
         // o teclado esta escrevendo na tty
         // ela decide se faz echo no console ou nao,
         // dependendo da configuraçao da tty.
         // #test: fazendo echo
            if ( (Event_Message == MSG_KEYDOWN) && ((char)bugBuffer[0] != '\n') )
            {
                // ainda nao pode ler.
                PS2KeyboardDeviceTTY->new_event = FALSE;
         
                console_write ( 
                    (int) fg_console, 
                    (const void *) bugBuffer, 
                    (size_t) 1 );

                
                // #bugbug:
                // Usado somente para teste.
                refresh_screen(); 
            }
            //pode ler
            if ( (Event_Message == MSG_KEYDOWN) && ((char)bugBuffer[0] == 'q') )
            {
                PS2KeyboardDeviceTTY->new_event = TRUE;

             // da proxima vez escreveremos no inicio do buffer.
             //PS2KeyboardDeviceTTY->_rbuffer->_w = 0;
             // PS2KeyboardDeviceTTY->_rbuffer->_r = 0;
             //PS2KeyboardDeviceTTY->_rbuffer->_p = PS2KeyboardDeviceTTY->_rbuffer->_base; 
             //PS2KeyboardDeviceTTY->_rbuffer->_cnt = PS2KeyboardDeviceTTY->_rbuffer->_lbfsize;
             //for( xxxi=0; xxxi<BUFSIZ; xxxi++){ PS2KeyboardDeviceTTY->_rbuffer->_p[xxxi] = 0; };
            }
  
        }
        
        // ok
        return 0;
    } //fim do current input mode. (TTY MODE)


fail:
    refresh_screen();
    // fail
    return -1;
}


// keyboard events.
// Envia eventos para a fila na thread em foreground.
// Chama um diálogo local para algumas combinações de teclas.

int 
kgws_event_dialog ( 
    int tid,
    struct window_d *window, 
    int message,
    unsigned long ascii_code,
    unsigned long raw_byte )
{

    //==============
    // [event block]
    struct window_d  *Event_Window;            //arg1 - window pointer
    int               Event_Message       =0;  //arg2 - message number
    unsigned long     Event_LongASCIICode =0;  //arg3 - ascii code
    unsigned long     Event_LongRawByte   =0;  //arg4 - raw byte
    //===================


    // setup event block
    // get parameters.
    
    Event_Window        = (struct window_d  *) window;
    Event_Message       = message;
    Event_LongASCIICode = ascii_code;
    Event_LongRawByte   = raw_byte;



    if ( tid<0 ){
        debug_print("kgws_event_dialog: tid\n");
        return -1;
    }

    // -----

    // Esse tratador é para todos os modos de input
    // mas dentro dele tem rotinas para modos especificos.

    // #todo
    // Como essa rotina usa os quatro parametros começados com 'Event_'
    // então talvez possamos chamar um diálogo.
    // Mas precisa da tid também.
    
    switch (Event_Message){
       
        // Para os dois casos.
        // quando o control ou a tecla de funçao forem pressionadas ou liberadas.
        case MSG_SYSKEYDOWN: 
        case MSG_SYSKEYUP:
            switch (Event_LongASCIICode){

                // function key
                // Quando pressionarmos uma tecla de funçao.
                // no metodo olharemos control ou alt.
                case VK_F1:  case VK_F2:  case VK_F3:  case VK_F4:
                case VK_F5:  case VK_F6:  case VK_F7:  case VK_F8:
                case VK_F9:  case VK_F10:  case VK_F11:  case VK_F12:
                    // For all the input modes.
                    if (Event_Message == MSG_SYSKEYDOWN)
                    {
                       // se alguma tecla de controle esta pressionada, chamaremos o procedimento local.
                       if ( shift_status == 1 || ctrl_status == 1 || alt_status == 1 )
                       {
                           debug_print ("kgws_event_dialog: >>>> [MSG_SYSKEYUP] to system procedure\n"); 
                            __kgwm_ps2kbd_procedure ( 
                                            Event_Window, 
                            (int)           Event_Message, 
                            (unsigned long) Event_LongASCIICode, 
                            (unsigned long) Event_LongRawByte );
                        debug_print("out of sysm procedure\n");
                        return 0;
                        }
                        // caso nenhuma tecla de controle esteja pressionada,
                        //enviaremos a tecla de funçao para a alicaçao.
                        if (current_input_mode == INPUT_MODE_SETUP)
                        {
                            //if ( EnableKGWS == FALSE ){ return 0; }
                            //kgws_send_to_controlthread_of_currentwindow ( 
                            //                    Event_Window,
                            //    (int)           Event_Message, 
                            //    (unsigned long) Event_LongASCIICode, 
                            //    (unsigned long) Event_LongRawByte );

                            kgws_send_to_tid (  tid,
                                                Event_Window,
                                (int)           Event_Message, 
                                (unsigned long) Event_LongASCIICode, 
                                (unsigned long) Event_LongRawByte );
                                
                            debug_print ("kgws_event_dialog: >>>> [MSG_SYSKEYUP.function] to wwf\n");        
                            return 0;
                        }
                    }
                    return 0;
                    break;

                // todas as outras teclas de controle.
                // Default syskeyups dent to control thread.
                // This is a window of the embedded window server.
                // Not the loadable window server.
                // Only for the setup input mode.
                default:
                    // Only for the setup input mode.
                    if (current_input_mode == INPUT_MODE_SETUP)
                    {
                        //if ( EnableKGWS == FALSE ){ return 0; }
                        //kgws_send_to_controlthread_of_currentwindow ( 
                        //                    Event_Window,
                        //    (int)           Event_Message, 
                        //    (unsigned long) Event_LongASCIICode, 
                        //    (unsigned long) Event_LongRawByte );

                        kgws_send_to_tid (  tid,
                                            Event_Window,
                            (int)           Event_Message, 
                            (unsigned long) Event_LongASCIICode, 
                            (unsigned long) Event_LongRawByte );

                            
                        debug_print ("kgws_event_dialog: >>>> [MSG_SYSKEYUP.function] to wwf\n");        
                    }
                    
                    // #todo
                    // We are building a set of info about the ps2 devices.
                    // We're gonna use the TTY here.
                    // See: devmgr.h
                    
                    // PS2KeyboardTTY ??
                    
                    return 0; 
                    break;
            };
            return 0;
            break;

        //===============
        // Para todas as outras mensagens alem de syskeyup e syskeydown.
        // kgws:
        // Send a message to the thread associated with the
        // window with focus.
        // See: ws/kgws.c
        default:
           // Only for the setup input mode.
           if (current_input_mode == INPUT_MODE_SETUP)
           {
               //if ( EnableKGWS == FALSE ){ return 0; }
               //kgws_send_to_controlthread_of_currentwindow ( 
               //                    Event_Window,
               //    (int)           Event_Message, 
               //    (unsigned long) Event_LongASCIICode, 
               //    (unsigned long) Event_LongRawByte );

               kgws_send_to_tid (  tid,
                                   Event_Window,
                   (int)           Event_Message, 
                   (unsigned long) Event_LongASCIICode, 
                   (unsigned long) Event_LongRawByte );
                   
               debug_print ("kgws_event_dialog: >>>> [default] to wwf\n");
            
               // #test
               // Vamos escrever em stdin.
               // Que tipo de objeto? file? tty?
               // #bugbug: kernel panic!
            
               //sys_write ( 
               //    (int) 0, (const void *) &ch, (size_t) 1 );
            }
            return 0;
            break;
    };

    return 0;
}

//==========================================================


/*
 ***************
 * KGWS_SEND_KEYBOARD_MESSAGE:
 *     Envia uma mensagem de teclado para a janela com o 
 * foco de entrada.
 */

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

int 
KGWS_SEND_KEYBOARD_MESSAGE (
    int tid, 
    unsigned char raw_byte )
{


// ==== #importante ====
// Na verdade isso aqui eh trabalho do window server.
// Eh ele que le na fila de RAW bytes de constroi uma fila de eventos.
// Esses eventos serao lidos pelos cliente.

    // Step 0 
    // Declarações de variáveis.


    struct process_d  *__p;
    struct thread_d   *t;


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
    unsigned long     Event_LongASCIICode =0;  //arg3 - ascii code
    unsigned long     Event_LongRawByte   =0;  //arg4 - raw byte
    //===================

    // Inicializando a janela, 
    // pois os outros elementos já foram incializados logo acima.
    Event_Window = NULL;



    if (tid<0){
        debug_print("KGWS_SEND_KEYBOARD_MESSAGE: tid\n");
        return -1;
    }

    // =============
    // Step1
    // Pegar o RawByte.
    // O driver pegou o scancode e passou para a disciplina de linha 
    // através de parâmetro.

    Keyboard_RawByte = raw_byte;

	// Obs: 
	// Observe que daqui pra frente todas as rotinas poderiam 
	// estar em user mode.

    // #debug.
    // Show the scancode if the flag is enabled.
    // Talvez isso nem seja necess'ario.
    
    // rawbyteStatus
    if (scStatus == TRUE){
        printk ("raw byte {%d,%x} ", 
            Keyboard_RawByte, Keyboard_RawByte );
        // Refresh screen?
    }

    // ==========
    // Step 2
    // Tratar as mensagens.
    // Traduzir rawbyte em evento.


    // ================================================
    // Se a tecla for (liberada).
    // ligado. tecla liberada.
    if ( (Keyboard_RawByte & LDISC_KEY_RELEASED) != 0 ) // liberada.
    {
        // Desativando o bit de paridade caso esteja ligado.

        Keyboard_ScanCode = Keyboard_RawByte;
        Keyboard_ScanCode &= LDISC_KEY_MASK;

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
    };

    // ================================================
    // * Tecla (pressionada) ...........
    // bit desligado. tecla pressionada.
    if ( (Keyboard_RawByte & LDISC_KEY_RELEASED) == 0 )  // pressionada.
    { 
        Keyboard_ScanCode = Keyboard_RawByte;
        Keyboard_ScanCode &= LDISC_KEY_MASK; //Desativando o bit de paridade caso esteja ligado.

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
                shift_status = TRUE; Event_Message = MSG_SYSKEYDOWN;
                //printf ("VK_LSHIFT: Pressionada\n"); refresh_screen();
                break;

            // left control pressionada.
            // case KEY_CTRL:
            case VK_LCONTROL:
                ctrl_status = TRUE; Event_Message = MSG_SYSKEYDOWN;
                //printf ("VK_LCONTROL: Pressionada\n"); refresh_screen();
                break;

            // left winkey pressionada.
            case VK_LWIN:
                winkey_status = TRUE; Event_Message = MSG_SYSKEYDOWN;
                //printf ("VK_LWIN: Pressionada\n"); refresh_screen();
                break;

            // left alt pressionada.
            case VK_LMENU:
                alt_status = TRUE;  Event_Message = MSG_SYSKEYDOWN;
                //printf ("VK_LMENU: Pressionada\n"); refresh_screen();
                break;

            // #todo 
            // alt gr.

            // right winkey pressionada.
            case VK_RWIN:
                winkey_status = TRUE;  Event_Message = MSG_SYSKEYDOWN;
                //printf ("VK_RWIN: Pressionada\n"); refresh_screen();
                break;

            // #todo: 
            // Control menu.

            // right control pressionada.
            case VK_RCONTROL:
                ctrl_status = TRUE; Event_Message = MSG_SYSKEYDOWN;
                //printf ("VK_RCONTROL: Pressionada\n"); refresh_screen();
                break;

            // right shift pressionada.
            case VK_RSHIFT:
                shift_status = TRUE; Event_Message = MSG_SYSKEYDOWN;
                //printf ("VK_RSHIFT: Pressionada\n"); refresh_screen();
                break;

            case VK_F1: case VK_F2: case VK_F3: case VK_F4:
            case VK_F5: case VK_F6: case VK_F7: case VK_F8:
            case VK_F9: case VK_F10: case VK_F11: case VK_F12:
                Event_Message = MSG_SYSKEYDOWN;
                break;

            // num Lock.
            // Muda o status do numlock não importa o anterior.
            case VK_NUMLOCK:
                if (numlock_status == FALSE){
                    numlock_status = TRUE; Event_Message = MSG_SYSKEYDOWN;
                    break;
                }
                if (numlock_status == TRUE){ 
                    numlock_status = FALSE; Event_Message = MSG_SYSKEYDOWN; 
                    break; 
                }
                break;

            // Scroll Lock.
            // Muda o status do numlock não importa o anterior.
            case VK_SCROLL:
                if (scrolllock_status == FALSE){  
                    scrolllock_status = TRUE; Event_Message = MSG_SYSKEYDOWN;
                    break;
                }
                if (scrolllock_status == TRUE){ 
                    scrolllock_status = FALSE; Event_Message = MSG_SYSKEYDOWN; 
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
        // Uma tecla normal foi pressionada.
        // mensagem de digitação.
        if (Event_Message == MSG_KEYDOWN)
        {
            // Minúsculas.
            if (capslock_status == FALSE)
            { Event_LongASCIICode = map_abnt2[Keyboard_ScanCode];   goto done; }
            // Maiúsculas.
            if (capslock_status == TRUE)
            { Event_LongASCIICode = shift_abnt2[Keyboard_ScanCode]; goto done; }
            // ...
        }

        // ==============================
        // Teclas de sistema
        // Uma tecla do sistema foi pressionada.
        if (Event_Message == MSG_SYSKEYDOWN)
        {   
            // se pressionamos teclas de sistema como capslock ligado
            if (capslock_status == FALSE)
            { Event_LongASCIICode = map_abnt2[Keyboard_ScanCode];   goto done; }
            // se pressionamos teclas de sistema como capslock desligado
            if (capslock_status == TRUE)
            { Event_LongASCIICode = shift_abnt2[Keyboard_ScanCode]; goto done; }
            // ...
        }

        // Nothing.
        goto done;
        
    };  // Fim do else

    // Done.
    // Para finalizar, vamos enviar a mensagem para fila certa.

done:

    // Fixing the rawbyte to fit in the message arg.
    Event_LongRawByte = (unsigned long) Keyboard_RawByte;
    Event_LongRawByte = (unsigned long) ( Event_LongRawByte & 0x000000FF );


	// Nesse momento temos duas opções:
	// Devemos saber se a janela com o foco de entrada é um terminal ou não ...
	// se ela for um terminal chamaremos o porcedimento de janelas de terminal 
	// se ela não for um terminal chamaremos o procedimento de janela de edit box. 
	// que é o procedimento de janela do sistema.
	// *IMPORTANTE: ENQUANTO O PROCEDIMENTO DE JANELA DO SISTEMA TIVER ATIVO,
	// MUITOS COMANDOS NÃO VÃO FUNCIONAR ATE QUE SAIAMOS DO MODO TERMINAL.

	// *importante:
	// Passamos a mensagem de teclado para o procedimento de janela do sistema.
	// que deverá passar chamar o procedimento de janela da janela com o focod eentrada.

	// *importante:
	// Quem é o 'first responder' para evento de teclado.
	// A janela com o foco de entrada é o first responder para 
	// eventos de teclado, mas não para todo tipo de envento.

	
	// ## window ##
	
	// #importante
	// +Pegamos a janela com o foco de entrada, pois ela será um elemento 
	// da mensagem.	
	// Mas enviaremos a mensagem para a fila da thread de input associada
	// a essa janela.
	
	// ### super importante ###
    // Estamos enviando esse input para a thread de input de uma janela.
	// Mas poderíamos por padrão mandar para uma thread específica do
	// servidor de recursos gráficos, x server, ele por sua vez
	// envia a mensagem para o servidor de janelas que mandará para
	// thread de input associada à janela com o foco de entrada.
	
	// >> kbd driver >> ldisc >> x server >> wm >> thread.

	
	// #importante
	// Caso tenhamos um servidor x-server carregável e funcionando
	// então podemos mandar a mensagem para a thread de controle dele.
	// Essa mensagem será armazenada. O wm chamará o servidor e pegará essa
	// mensagem.
	
	//if ( x_server_status == 1)
	//{
	//	t = x_server_thread;
	//}


    // #importante
    // Sobre o terminal virtual e o input nos seus processos filhos.
    // A libc não vai pegar digitações de teclado ... 
    // mas as mensagens de teclado serão enviadas para a fila 
    // de mensagens da thread associada com a janela que 
    // tem o foco de entrada.
    // Quando a janela com o foco de entrada for a janela do 
    // terminal, então as mensagens de janelas vão para a 
    // fila de mensagens do processo terminal virtual .... 
    // o terminal coloca essas digitações em um arquivo, 
    // esse mesmo arquivo foi herdado pelo processo filho ... 
    // o processo filho vai chamar esse arquivo de stdin
    // Por fim a libc deve ler no arquivo stdin herdado do 
    // terminal virtual ... arquivo na qual o terminal está 
    // colocando as digitações de teclado.
    // Então se a janela do terminal virtual não tiver o foco 
    // de entrada, então o terminal virtual não receberá as 
    // digitações de teclado e não terá o que enviar para o 
    // processo filho via arquivo herdado.
    // Ainda é preciso abordar questões como par de ttys, 
    // que é uma pty ... e pts que é o sistema de arquivos 
    // pra multiplexar master ... e ptmx que é o multiplexador 
    // de master. ... em pts ficarão os terminais virtuais 
    // multiplexados por ptmx. pts/0 pts/1 ...


    //
    // Message.
    //

    // #importante:
    // A janela com o foco de entrada deve receber input de teclado.
    // Então a mensagem vai para a thread associada com a janela 
    // que tem o foco de entrada.
    // Como o scancode é um char, precisamos converte-lo 
    // em unsigned long.



    //
    // == dispatch event ======================================
    //

    // Mandaremos o evento para 3 lugares possiveis.
    // + para o tty de teclado.
    // + para o procedimento de janela do sistema ou
    // + para a fila na thread em foreground.


    // ===========================

    // #todo
    // Send the message to the TYY,
    // this way the foreground process is able to read it
    // using stdin.
    // See:
    // devmgr.h ps2kbd.c
    // ...
    
    
    if ( current_input_mode == INPUT_MODE_TTY )
    {
         kgws_put_console ( 
             (struct window_d *) Event_Window,
             (int)               Event_Message,
             (unsigned long)     Event_LongASCIICode,
             (unsigned long)     Event_LongRawByte );

        // #bugbug: O retorno deve ser o mesmo do diálogo acima.
        return 0;
    } 


    // Se o caso não é enviar para o tty,
    // então vamos enviar para o procedimento do sistema
    // ou para a thread em foreground, que recebemos como
    // parametro.
    
    // mesmo que tenhamos enviado para a tty,
    // ainda não vamos retornar,
    // pois talvez tenhamos que chamar o 
    // procedimento de janelas do sistema

    // #todo
    // Check tid.

    //if (tid<0){
    //    debug_print("KGWS_SEND_KEYBOARD_MESSAGE: tid\n");
    //    return -1;
    //}


    // #bugbug
    // Bem, na verdade esse tipo de input pode ser usado para
    // além do ambiente de setup. Podemos usar também
    // nos window server e seus clientes.

    if ( current_input_mode == INPUT_MODE_SETUP )
    {
        kgws_event_dialog ( 
            (int) tid,
            (struct window_d *) Event_Window,
            (int)               Event_Message,
            (unsigned long)     Event_LongASCIICode,
            (unsigned long)     Event_LongRawByte );
        
        // #bugbug: O retorno deve ser o mesmo do diálogo acima.
        return 0;
    }


    return -1;
}



/*
 ****************************** 
 * kgws_mouse_scan_windows:
 *     Com essa função o window server pega uma mensagem vinda do
 * driver de mouse e escaneia as janelas pra comparar com o 
 * posicionamento do ponteiro do mouse.
 * 
 * #todo
 * Por enquando o próprio handler do mouse está chamando essa rotina.
 */

// #bugbug
// Essa funçao perdeu seu proposito aqui no ws dentro do kernel
// Podemos copiar ela para o gwssrv.bin em ring3.


// #bugbug
// Algumas variáveis usadas aqui estão no driver de mouse ps2
// Precisamos delas aqui, pois não possuem utilidade lá.
// aqui o servidor de janelas escaneia as janelas para saber 
// se o mouse está sobre alguma ... durante a rotina
// são solicitadas informações diretamente no driver de mouse ps2.

// #obs
// Isso é chamado pelo mouse em ps2mouse.c

// Estamos mandando o evento para a thread associada `a
// janela 'a qual o mouse esta passando por cima.
// Isso nao muda a thread que esta em foreground.

int kgws_mouse_scan_windows (void)
{
    // #importante:
    // Essa será a thread que receberá a mensagem.

    struct thread_d *t;

	// #importante:
	// Essa será a janela afetada por qualquer evento de mouse.
	// ID de janela.

    struct window_d *Window;
    int wID = -1;


    //
    // Chamar o driver de mouse ps2 pra pegar as informações
    // sobre o mouse;
    //
    
    // #todo
    // Temos que pegar um pacote com todas as informações de uma vez.

    // Pegando as informações.
    kgws_mouse_event_saved_mouse_x      = ps2_mouse_get_info (1);
    kgws_mouse_event_saved_mouse_y      = ps2_mouse_get_info (2);
    kgws_mouse_event_mouse_x            = ps2_mouse_get_info (3);
    kgws_mouse_event_mouse_y            = ps2_mouse_get_info (4);
    kgws_mouse_event_moving             = ps2_mouse_get_info (5);
    //kgws_mouse_event_drag_status      = ps2_mouse_get_info (6);
    kgws_mouse_event_button_action      = ps2_mouse_get_info (7);
    kgws_mouse_event_mouse_buttom_1     = ps2_mouse_get_info (8);
    kgws_mouse_event_mouse_buttom_2     = ps2_mouse_get_info (9);
    kgws_mouse_event_mouse_buttom_3     = ps2_mouse_get_info (10);
    kgws_mouse_event_old_mouse_buttom_1 = ps2_mouse_get_info (11);
    kgws_mouse_event_old_mouse_buttom_2 = ps2_mouse_get_info (12);
    kgws_mouse_event_old_mouse_buttom_3 = ps2_mouse_get_info (13);
    //kgws_mouse_event_button_pressed   = ps2_mouse_get_info (14);
    // ...


    //printf ("b=%d ",kgws_mouse_event_mouse_buttom_1);

	// #refletindo: 
	// ?? E no caso de apenas considerarmos que o mouse está se movendo, 
	// mandaremos para janela over. ???
	
	// #refletindo:
	// Obs: A mensagem over pode ser enviada apenas uma vez. 
	// será usada para 'capturar' o mouse ... 
	// e depois tem a mensagem para 'descapturar'.
	
	
    // ## Sem escaneamento de janelas por enquanto, apenas mostre e mova o ponteiro ##
	
	//## então não enviaremos mensagens para a thread ###
	
	//
	//  ## Scan ##
	//
	
	//===========
	// (capture) - On mouse over. 
	//

	// wID = ID da janela.
	// Escaneamos para achar qual janela bate com os valores indicados.
	// Ou seja. Sobre qual janela o mouse está passando.
	
	// #BUGBUG
	// O problema nessa técnica são as sobreposição de janelas.
	// Quando uma janela está dentro da outr, então duas janelas
	// estão áptas a serem selecionadas.
	// Talvez devamos filtrar e só aceitarmos sondar procurando 
	// por controles.

	// #IMPORTANTE
	// Se for válido e diferente da atual, significa que 
	// estamos dentro de uma janela.
	// -1 significa que ouve algum problema no escaneamento.
	
	//wID = (int) windowScan ( mouse_x, mouse_y );

    
	//#importante:
	//Ja que não passamos em cima de um botão ou editbox,
	//então vamos ver se estamos em cima de uma janela overlapped.
    //#obs: isso ficou bom ... estamos testando
    
    // #bugbug
    // Com isso o sistema trava quando tentamos mover o mouse
    // no programa gdeshell, que é fullscreen.
    //Podemos tentar desabilitar o mouse quando entrarmos em fullscreen
    // no gdeshell(teste)?
    
    //#todo: 
    //Não há porque sondar janelas se tivermos em full screen.
    //pois somente teremos a área de cliente de uma das janelas.

    int __saved = 0;
    
    
    /*
    wID = (int) windowOverLappedScan ( kgws_mouse_event_mouse_x, kgws_mouse_event_mouse_y );
    __saved = wID;
    
    //se pegamos uma overlapped, vamos tentar pegar um botão ou editbox.
    if ( wID != -1 )
    {
        wID = (int) windowScan ( kgws_mouse_event_mouse_x, kgws_mouse_event_mouse_y );
    
        //Se não pegamos um botão ou editbox.
        // então ficaremos com a janela overlapped salva.
        if ( wID == -1)
        {
            wID = __saved;
        }
    }
    */    
    

    // #test
    // Estamos em cima de qual janela?
    
    wID = (int) top_at ( 
                    kgws_mouse_event_mouse_x, 
                    kgws_mouse_event_mouse_y );


    // #bugbug
    // Estamos sempre recebendo a janela gui->screen

    //================
    // -1 = Se não temos uma janela.
    // if ( wID < 0 )
    if ( wID == -1 )
    { 
		//printf ("x");

		// Essa flag indica que podemos fazer o refresh da mouse ouver,
		// mas somente uma vez.
        if ( flagRefreshMouseOver == 1 )
        {
            Window = (struct window_d *) windowList[mouseover_window];

			//#bugbug:
			//precisamos checar a validade da estrutura antes de usa-la.

			//#importante:
			//isso apaga o que pintamos na janela, o valor foi salvo logo abaixo.

            if ( (void *) Window != NULL )
            {
                //refresh_rectangle ( Window->left, Window->top, 20, 20 );
                //refresh_rectangle ( savedmouseoverwindowX, savedmouseoverwindowY, 20, 20 );

            }

			// Não podemos mais fazer refresh.
            flagRefreshMouseOver = 0;

			//#importante inicializa.
			//isso é global do sistema?
            mouseover_window = 0;
        }
     
        return -1;
     };


    //++
	// Se não houve problema no escaneamento de janela ou seja, se encontramos 
	// uma janela. Então essa janela deve estar associada à uma thread para qual 
	// mandaremos a mensagem. Caso a thread for null ... apenas não enviamos.
	// A janela tem uma thread de controle, igual ao processo.
	
	// #importante
	// Mandaremos mensagem para a thread de controle da janela
	// ao qual o mouse está passando por cima.
	// Isso está funcionando. Mas qual é a thread das janelas filhas?
	// Elas herdam a thread de controle ??

    //============================ 
    //Se estamos sobre uma janela válida.
    if ( wID >= 0 )  //if ( wID > -1 )
    {
		//printf ("w ");

        Window = (struct window_d *) windowList[wID];

        if ( (void *) Window == NULL ) { return -1; }
        if ( Window->used != 1 || Window->magic != 1234){ return -1; }


		//#importante:
		//Nesse momento temos uma janela válida, então devemos 
		//pegar a thread associada à essa janela, dessa forma 
		//enviaremos a mensagem para a thread do aplicativo ao qual 
		//a janela pertence.
		//E se a janela for um botão? será a mesma thread de controle
		//da janela overlapped ao qual ela é filha?

        t = (void *) Window->control;

        if ( (void *) t == NULL ){ return -1; }
        if ( t->used != 1 || t->magic != 1234 ){ return -1; }

		//#bugbug 
		//#todo:
		// Deveriamos aqui checarmos a validade da estrutura ??

        //
        // ==== Button events ====
        //
 
		// #importante
		// Se um botão foi pressionado ou liberado, então enviaremos uma 
		// mensagem relativa ao estado do botão, caso contrário, enviaremos 
		// uma mensagem sobre a movimentação do mouse.

		//Qual botão mudou seu estado??
		//Checaremos um por um.


		//===============================================
		// ***Se houve mudança em relação ao estado anterior.
		// Nesse momento um drag pode terminar
        if ( kgws_mouse_event_button_action == 1 )
        {
			//printf ("[Action ");
			
			 //debug
			 //if( Window->type == WT_OVERLAPPED)
             //{ printf ("[Action overlapped "); refresh_screen(); }
              
			// >> BOTÃO 1 ==================
			//Igual ao estado anterior
            if ( kgws_mouse_event_mouse_buttom_1 == kgws_mouse_event_old_mouse_buttom_1 )
            {
				//...
			
			//Diferente do estado anterior.
            }else{
				
				//printf ("Dif ");
				
				// down - O botão 1 foi pressionado.
                if ( kgws_mouse_event_mouse_buttom_1 == 1 )
                {
					//printf ("Press\n");
					 
					//clicou
					// se o old estava em 0 então o atual está em um.
                    if ( kgws_mouse_event_old_mouse_buttom_1 == 0 )
                    {
						// flag: um botão foi pressionado.
						kgws_mouse_event_button_pressed = 1;
						
						// Enviaremos a mensagem para a thread atual.
						// houve alteração no estado do botão 1 e estamos em cima de uma janela.
                        if ( (void *) Window != NULL )
                        {
							//ps2mouse_change_and_show_pointer_bmp(4); //folder bmp
							//pegamos o total tick
                            kgws_current_totalticks = (unsigned long) get_systime_totalticks();
                            kgws_delta_totalticks = (kgws_current_totalticks - kgws_last_totalticks); 
                            //printf ( "x=%d l=%d d=%d \n",
                               //kgws_current_totalticks, kgws_last_totalticks, kgws_delta_totalticks ); 
                               //refresh_screen();
                            kgws_last_totalticks = kgws_current_totalticks;
                            
                            // Kernel single event.
                            // #bugbug: 
                            // Não estamos usando esse tipo de mensagem,
                            // somente a fila.


                            // New way. Use this one!
                            t->window_list[ t->tail_pos ] = Window;
                            t->msg_list[ t->tail_pos ]    = MSG_MOUSEKEYDOWN;
                            t->long1_list[ t->tail_pos ]  = 1;
                            t->long2_list[ t->tail_pos ]  = 0;

                            // Modifying event type.
                            if (kgws_delta_totalticks < 1000) //2000
                            {
                                t->ke_msg = MSG_MOUSE_DOUBLECLICKED; 
                                t->msg_list[ t->tail_pos ] = MSG_MOUSE_DOUBLECLICKED;
                                kgws_delta_totalticks=8000; // delta inválido.
                            }

                            t->tail_pos++;
                            if ( t->tail_pos >= 31 )
                                t->tail_pos = 0;

							//estamos carregando o objeto
							//kgws_mouse_event_drag_status = 1;                        
                        }
                        //else: // houve alteração no estado do botão 1 mas não estamos em cima de uma janela.
                        
                        
						//Atualiza o estado anterior.
                        //kgws_mouse_event_old_mouse_buttom_1 = 1;
                        kgws_mouse_event_old_mouse_buttom_1 = kgws_mouse_event_mouse_buttom_1;
                    }

				// up - O botão 1 foi liberado.
                }else{
					
					//printf ("Rel\n");

				    // flag: um botão foi liberado.
				    kgws_mouse_event_button_pressed = 0;
						
					// #importante 
					// Enviaremos a mensagem para a thread atual.
                    if ( (void *) Window != NULL )
                    { 
                        // New way. Use this one!
                        t->window_list[ t->tail_pos ] = Window;
                        t->msg_list[ t->tail_pos ]    = MSG_MOUSEKEYUP;
                        t->long1_list[ t->tail_pos ]  = 1;
                        t->long2_list[ t->tail_pos ]  = 0;
                        t->tail_pos++;
                        if ( t->tail_pos >= 31 )
                           t->tail_pos = 0;
                      
                        // Old way. Delete it!
                        //t->window = Window;
                        //t->msg = MSG_MOUSEKEYUP;
                        //t->long1 = 1;
                        //t->long2 = 0;
                        //t->newmessageFlag = 1;
                    
                        //é up, mas se estamos carregando então é drop.
                        //if ( kgws_mouse_event_drag_status == 1 )
                        //{
                            //t->window = Window;
                            //t->msg = MSG_MOUSE_DROP;
                            //t->long1 = 1;
                            //t->long2 = 0;
                            //t->newmessageFlag = 1;
                        //}
						// Não estamos mais carregando um objeto.
						kgws_mouse_event_drag_status = 0;
                    }

                    //kgws_mouse_event_old_mouse_buttom_1 = 0;
                    kgws_mouse_event_old_mouse_buttom_1 = kgws_mouse_event_mouse_buttom_1;
                };
            }; 

       
       
			// >> BOTÃO 2 ==================
			// Igual ao estado anterior
            if ( kgws_mouse_event_mouse_buttom_2 == kgws_mouse_event_old_mouse_buttom_2 )
            {
				//...

			// Diferente do estado anterior.
            }else{

				// down - O botão 2 foi pressionado.
                if ( kgws_mouse_event_mouse_buttom_2 == 1 )
                {

					//clicou
                    if ( kgws_mouse_event_old_mouse_buttom_2 == 0 )
                    {
						// flag: um botão foi pressionado.
						kgws_mouse_event_button_pressed = 1;
						
						// houve alteração no estado do botão 2 e estamos em cima de uma janela.
                        if ( (void *) Window != NULL )
                        {
							//pegamos o total tick
							kgws_current_totalticks = (unsigned long) get_systime_totalticks();
                            kgws_delta_totalticks = (kgws_current_totalticks - kgws_last_totalticks); 
                            //printf ( "x=%d l=%d d=%d \n",
                               //kgws_current_totalticks, kgws_last_totalticks, kgws_delta_totalticks ); 
                               //refresh_screen();
                            kgws_last_totalticks = kgws_current_totalticks;
                            
                            
                            // New way. Use this one!
                            t->window_list[ t->tail_pos ] = Window;
                            t->msg_list[ t->tail_pos ] = MSG_MOUSEKEYDOWN;
                            if (kgws_delta_totalticks < 1000){
                                t->msg_list[ t->tail_pos ] = MSG_MOUSE_DOUBLECLICKED; 
                                kgws_delta_totalticks=8000; // delta inválido.
                            }
                            t->long1_list[ t->tail_pos ] = 2;
                            t->long2_list[ t->tail_pos ] = 0;
                            t->tail_pos++;
                            if ( t->tail_pos >= 31 )
                                t->tail_pos = 0;

							
							//estamos carregando o objeto
							//kgws_mouse_event_drag_status = 1;
                        }
                        //else: // houve alteração no estado do botão 2 mas não estamos em cima de uma janela.

						// atualiza o estado anterior.
                        //kgws_mouse_event_old_mouse_buttom_2 = 1;
                        kgws_mouse_event_old_mouse_buttom_2 = kgws_mouse_event_mouse_buttom_2;
                    }

				// up - O botão 2 foi liberado.
                }else{

				    // flag: um botão foi liberado.
				    kgws_mouse_event_button_pressed = 0;
				    
                   if ( (void *) Window != NULL )
                   {

                        // New way. Use this one!
                        t->window_list[ t->tail_pos ] = Window;
                        t->msg_list[ t->tail_pos ]    = MSG_MOUSEKEYUP;
                        t->long1_list[ t->tail_pos ]  = 2;
                        t->long2_list[ t->tail_pos ]  = 0;
                        t->tail_pos++;
                        if ( t->tail_pos >= 31 )
                           t->tail_pos = 0;


						// Não estamos mais carregando um objeto.
						kgws_mouse_event_drag_status = 0;                        
                    }

                    //kgws_mouse_event_old_mouse_buttom_2 = 0;
                    kgws_mouse_event_old_mouse_buttom_2 = kgws_mouse_event_mouse_buttom_2;
                }
            }; 
            


			// >> BOTÃO 3 ==================
			// Igual ao estado anterior
            if ( kgws_mouse_event_mouse_buttom_3 == kgws_mouse_event_old_mouse_buttom_3 )
            {
				//...

			// Diferente do estado anterior.
            }else{

				// down - O botão 3 foi pressionado.
                if ( kgws_mouse_event_mouse_buttom_3 == 1 )
                {
					//clicou
                    if ( kgws_mouse_event_old_mouse_buttom_3 == 0 )
                    {
						// flag: um botão foi pressionado.
						kgws_mouse_event_button_pressed = 1;
						
                        // houve alteração no estado do botão 3 e estamos em cima de uma janela.
                        if ( (void *) Window != NULL )
                        {
							//pegamos o total tick
							kgws_current_totalticks = (unsigned long) get_systime_totalticks();
                            kgws_delta_totalticks = (kgws_current_totalticks - kgws_last_totalticks); 
                            //printf ( "x=%d l=%d d=%d \n",
                               //kgws_current_totalticks, kgws_last_totalticks, kgws_delta_totalticks ); 
                               //refresh_screen();
                            kgws_last_totalticks = kgws_current_totalticks;
                            

                            // New way. Use this one!
                            t->window_list[ t->tail_pos ] = Window;
                            t->msg_list[ t->tail_pos ]    = MSG_MOUSEKEYDOWN;
                            if (kgws_delta_totalticks < 1000){
                                t->msg_list[ t->tail_pos ] = MSG_MOUSE_DOUBLECLICKED; 
                                kgws_delta_totalticks=8000; // delta inválido.
                            }
                            t->long1_list[ t->tail_pos ] = 3;
                            t->long2_list[ t->tail_pos ] = 0;
                            t->tail_pos++;
                            if ( t->tail_pos >= 31 )
                                t->tail_pos = 0;


							//estamos carregando o objeto
							//kgws_mouse_event_drag_status = 1;
                        }
                        //else: // houve alteração no estado do botão 1 mas não estamos em cima de uma janela.

						// Atualiza o estado anterior.
                        //kgws_mouse_event_old_mouse_buttom_3 = 1;
                        kgws_mouse_event_old_mouse_buttom_3 = kgws_mouse_event_mouse_buttom_3;
                    }

				// up - O botão 3 foi liberado.
                }else{

				    // flag: um botão foi liberado.
				    kgws_mouse_event_button_pressed = 0;
				    
                    if ( (void *) Window != NULL )
                    {


                        // New way. Use this one!
                        t->window_list[ t->tail_pos ] = Window;
                        t->msg_list[ t->tail_pos ]    = MSG_MOUSEKEYUP;
                        t->long1_list[ t->tail_pos ]  = 3;
                        t->long2_list[ t->tail_pos ]  = 0;
                        t->tail_pos++;
                        if ( t->tail_pos >= 31 )
                           t->tail_pos = 0;


						// Não estamos mais carregando um objeto.
						kgws_mouse_event_drag_status = 0;                        
                    }

                    //kgws_mouse_event_old_mouse_buttom_3 = 0;
                    kgws_mouse_event_old_mouse_buttom_3 = kgws_mouse_event_mouse_buttom_3;
                }
            }; 


			// Ação concluída.
            kgws_mouse_event_button_action = 0;
            return 0;
        };



        //===============================================
        // *** Se NÃO ouve alteração no estado dos botões, então apenas 
        // enviaremos a mensagem de movimento do mouse e sinalizamos 
        // qual é a janela que o mouse está em cima.
        // Não houve alteração no estado dos botões, mas o mouse
        // pode estar se movendo com o botão pressionado.
        //a não ser que quando pressionamos o botão ele envie várias
        //interrupções, igual no teclado.

        if ( kgws_mouse_event_button_action == 0 )
        {
			//printf ("[ No Action \n");

			// #importante
			// Lembrando que estamos dentro de uma janela ...
			// por isso a mensagem é over e não move.

			//Obs: Se a janela for a mesma que capturou o mouse,
			//então não precisamos reenviar a mensagem.
			//Mas se o mouse estiver em cima de uma janela diferente da 
			//que ele estava anteriormente, então precisamos enviar uma 
			//mensagem pra essa nova janela.

			//#bugbug:
			//estamos acessando a estrutura, mas precisamos antes saber se ela é válida.

            //estamos em cima de uma janela e não houve alteração no estado dos botões
            if ( (void *) Window != NULL )
            {
				//estamos em cima da janela que estávamos antes.
                //então estamos apenas se movendo
				if ( Window->id == mouseover_window )
				{

                    // New way. Use this one!
                    t->window_list[ t->tail_pos ] = Window;
                    t->msg_list[ t->tail_pos ]    = MSG_MOUSEMOVE;
                    t->long1_list[ t->tail_pos ]  = 0;
                    t->long2_list[ t->tail_pos ]  = 0;
                    t->tail_pos++;
                    if ( t->tail_pos >= 31 )
                        t->tail_pos = 0;

                    
                    if ( Window->type == WT_EDITBOX )
                    {
                        ps2mouse_change_and_show_pointer_bmp(6); //cursor
                    }
                    if ( kgws_mouse_event_drag_status == 1 )
                    {

                        // New way. Use this one!
                        t->window_list[ t->tail_pos ] = Window;
                        t->msg_list[ t->tail_pos ]    = MSG_MOUSE_DRAG;
                        t->long1_list[ t->tail_pos ]  = 0;
                        t->long2_list[ t->tail_pos ]  = 0;
                        t->tail_pos++;
                        if ( t->tail_pos >= 31 )
                            t->tail_pos = 0;

                    }
                }

                // Não estamos em cima da janela que estávamos antes.
                // Então estamos em cima de outra janela.
                // OU seja, um mouse over novo.
                // devemos enviar mensagem de mouse over somente nessa
                //situação.
                if ( Window->id != mouseover_window )
                {
					//Temos então uma nova mouse over.
                    mouseover_window = Window->id;
                   
                   
                    // New way. Use this one!
                    t->window_list[ t->tail_pos ] = (struct window_d *) windowList[mouseover_window];
                    t->msg_list[ t->tail_pos ]    = MSG_MOUSEOVER;
                    t->long1_list[ t->tail_pos ]  = 0;
                    t->long2_list[ t->tail_pos ]  = 0;
                    t->tail_pos++;
                    if ( t->tail_pos >= 31 )
                        t->tail_pos = 0;


                   //#bugbug
                   //aqui entraria a fila de mensagens.
                   //onde diríamos que também saímos de uma janela.
                   //MSG_MOUSEEXITED;

					//#importante:
					//flag que ativa o refresh do mouseover somente uma vez.
                    flagRefreshMouseOver = 1;

					// Já que entramos em uma nova janela, vamos mostra isso.

					//botão.
					//#provisório ...
					//Isso é um sinalizador quando mouse passa por cima.
					//#test: Vamos tentar modificar as características do botão.

                    //#ok isso funciona, vamos deixar oapp fazer isso.
                    //faremos isso somente para os botões do sistema.  
                    //if ( Window->isButton == 1 )
                    //{
						//isso funciona.
                        //bmpDisplayCursorBMP ( fileIconBuffer, Window->left, Window->top );
						//#test
                        //update_button ( (struct button_d *) Window->button,
                            //(unsigned char *) Window->button->string,
                            //(int) Window->button->style,
                            //(int) BS_HOVER,
                            //(int) Window->button->type,
                            //(unsigned long) Window->button->x, 
                            //(unsigned long) Window->button->y, 
                            //(unsigned long) Window->button->width, 
                            //(unsigned long) Window->button->height, 
                            //(unsigned long) Window->button->color );
						//redraw_button ( (struct button_d *) Window->button );
						//show_window_rect (Window);
					//};
					

				    //não botão.
				    //if ( Window->isButton == 0 )
				    //{
				    //    bmpDisplayCursorBMP ( folderIconBuffer, Window->left, Window->top );
				    //};


				    //nova mouse over
                    //mouseover_window = Window->id;

					//#importante:
					//flag que ativa o refresh do mouseover somente uma vez.
                    //flagRefreshMouseOver = 1;
                    

					// Agora enviamos uma mensagem pra a nova janela que 
					// o mouse está passando por cima.
                    //#todo: reagir a isso lá nos apps.
                    
                    //t->window = Window;
                    //t->msg = MSG_MOUSEOVER;
                    //t->long1 = 0;
                    //t->long2 = 0;
                    //t->newmessageFlag = 1;
                    
                    //return 0;

                // É mouse over window.
                // não estamos em cima de uma janela e não houve alteração no estado dos botões
                }
                
            };

			// Ação concluída.
			// Para o caso de um valor incostante na flag.
            kgws_mouse_event_button_action = 0;
            return 0;
        };
    };
    //--
    
    //fail!
    return -1;
}



// ?? Not used yet ??
// Registrar um window server.
int kgwsRegisterWindowServer (int pid)
{

    int Status = 0;

    // ?? Where ??
    if ( kgws_status != 1 )
    {
        Status = 1;
        goto fail;

    }else{

        kgws_ws_PID = (int) pid;
        kgws_ws_status = 1;
        goto done;
    };


fail:
    printf("kgwsRegisterWindowServer: fail\n");

done:
    return 0;
}


/*
 *************************************************
 * kgws_send_to_controlthread_of_currentwindow:
 * 
 * 
 */

// Send a message to the thread associated with the
// window with focus.

// Called by KEYBOARD_SEND_MESSAGE() in ps2kbd.c.

// #todo:
// We need to associate the current thread and the current tty.
// tty->control
// window->control

int
kgws_send_to_controlthread_of_currentwindow ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{

    struct window_d *w;
    struct thread_d *t;
    
    unsigned long tmp_msg=0;
    unsigned long tmp_ch=0;
    unsigned long tmp_sc=0;    
    
   //
   // Window with focus.
   //

    w = (void *) windowList[window_with_focus];

    if ( (void *) w == NULL ){
        panic ("kgws_send_to_controlthread_of_currentwindow: w");

    }else{
        if ( w->used != 1 || w->magic != 1234 ){
            panic ("kgws_send_to_controlthread_of_currentwindow: w validation");
        }
        
      
        //
        // Thread.
        //

        t = (void *) w->control;

        if ( (void *) t == NULL ){
            panic ("kgws_send_to_controlthread_of_currentwindow: t \n");
        }

        if ( t->used != 1 || t->magic != 1234 ){
            panic ("kgws_send_to_controlthread_of_currentwindow: t validation \n");
        } 


        tmp_msg = (unsigned long) msg;
        tmp_msg = (unsigned long) ( tmp_msg & 0x0000FFFF );

        tmp_ch = (unsigned long) long1;
        tmp_ch = (unsigned long) ( tmp_ch & 0x000000FF );
   
        // Scan code.
        tmp_sc = (unsigned long) long2;
        tmp_sc = (unsigned long) ( tmp_sc & 0x000000FF );
    
        
        //Send system message to the thread.
        t->window_list[ t->tail_pos ]  = window;
        t->msg_list[ t->tail_pos ]     = tmp_msg;
        t->long1_list[ t->tail_pos ]   = tmp_ch;
        t->long2_list[ t->tail_pos ]   = tmp_sc;

        t->tail_pos++;
        if ( t->tail_pos >= 31 )
            t->tail_pos = 0;
    
        //ok
        return 0;
    };

    // fail
    return -1;
}


//==========
/*
 *************************************************
 * kgws_send_to_controlthread_of_currentwindow:
 * 
 * 
 */

// Send a message to the thread associated with the
// window with focus.

// Called by KEYBOARD_SEND_MESSAGE() in ps2kbd.c.

// #todo:
// We need to associate the current thread and the current tty.
// tty->control
// window->control

// #bugbug
// Only keyboard messages,
// long1 and long2 will mask to single byte.
// IN: tid, window, message code, ascii code, raw byte.

int
kgws_send_to_tid ( 
    int tid, 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{

    //struct window_d *w;
    struct thread_d *t;
    
    unsigned long tmp_msg=0;
    unsigned long tmp_ch=0;
    unsigned long tmp_sc=0;    
    

    if ( tid<0 ){
        goto fail;
    }

    //
    // Pega a thread alvo. 
    //

    t = (struct thread_d *) threadList[tid];

    if ( (void *) t == NULL ){
        panic ("kgws_send_to_controlthread_of_currentwindow: t \n");
    }

    if ( t->used != 1 || t->magic != 1234 ){
        panic ("kgws_send_to_controlthread_of_currentwindow: t validation \n");
    } 

    tmp_msg = (unsigned long) msg;
    tmp_msg = (unsigned long) ( tmp_msg & 0x0000FFFF );

    tmp_ch = (unsigned long) long1;
    tmp_ch = (unsigned long) ( tmp_ch & 0x000000FF );
   
    // Scan code.
    tmp_sc = (unsigned long) long2;
    tmp_sc = (unsigned long) ( tmp_sc & 0x000000FF );
    
    //Send system message to the thread.
    t->window_list[ t->tail_pos ]  = window;
    t->msg_list[ t->tail_pos ]     = tmp_msg;
    t->long1_list[ t->tail_pos ]   = tmp_ch;
    t->long2_list[ t->tail_pos ]   = tmp_sc;

    t->tail_pos++;
    if ( t->tail_pos >= 31 )
        t->tail_pos = 0;

    //ok
    return 0;

fail:
    // fail
    return -1;
}

int
kgws_send_to_foreground_thread ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{

    if( foreground_thread <0 )
        return -1;

    return (int) kgws_send_to_tid( 
                     foreground_thread,
                     window,
                     msg,
                     long1,
                     long2 );
}


int register_ws_process ( pid_t pid ){

    if (pid<0 || pid >= PROCESS_COUNT_MAX ){
        debug_print("register_ws_process: pid fail\n");
        return -1;
    }

    if ( __gpidWindowServer != 0 ){
        debug_print("register_ws_process:\n");
        return -1;
    }

    __gpidWindowServer = (pid_t) pid;

    return 0;
}


// called by x86/x86init.c
int KGWS_initialize(void)
{
    // Logon. 
    // Cria Background, main window, navigation bar.
    // de acordo com predefinição.
    // See:
    // windows/logon.c

    if ( g_useGUI != 1 ){
        panic("KGWS_initialize: NO GUI");
    }
    
    printf ("KGWS_initialize: calling init_logon_manager ...\n");
    init_logon_manager();

    return 0;
}


//
// End.
//






