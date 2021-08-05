
// kgws.c

#include <kernel.h>  


//keyboard support
#define LDISC_KEY_RELEASED  0x80
#define LDISC_KEY_MASK  0x7F
#define LDISC_FULL      1
#define LDISC_EMPTY     0
#define LDISC_OBF       0x01    //Output buffer flag.


static int EnableKGWS = TRUE;

int kgws_status;
int kgws_ws_PID;
int kgws_ws_status;





// ==================================
// sendto_eventqueue:
// keyboard events.
// Envia eventos para a fila na thread em foreground.
// Chama um diálogo local para algumas combinações de teclas.

// Called by UserInput_SendKeyboardMessage in this document.

int 
sendto_eventqueue ( 
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



    //if (current_input_mode != INPUT_MODE_EVENTS)
    if ( IOControl.useEventQueue != TRUE )
    {
        panic("sendto_eventqueue: [ERROR] Wrong input mode\n");
    }


    if ( tid<0 ){
        debug_print("sendto_eventqueue: tid\n");
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
                           debug_print ("sendto_eventqueue: >>>> [MSG_SYSKEYUP] to system procedure\n"); 
                        
                            __kgwm_ps2kbd_procedure ( 
                                Event_Window, 
                                (int)           Event_Message, 
                                (unsigned long) Event_LongASCIICode, 
                                (unsigned long) Event_LongRawByte );
                        
                        debug_print("out of sysm procedure\n");
                        return 0;
                        }
                        // caso nenhuma tecla de controle esteja pressionada,
                        // enviaremos a tecla de funçao para a alicaçao.
                        //if (current_input_mode == INPUT_MODE_SETUP)
                        if ( IOControl.useEventQueue == TRUE )
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
                                
                            debug_print ("sendto_eventqueue: >>>> [MSG_SYSKEYUP.function] to wwf\n");        
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
                    //if (current_input_mode == INPUT_MODE_SETUP)
                    if ( IOControl.useEventQueue == TRUE )
                    {
                        kgws_send_to_tid (  tid,
                                            Event_Window,
                            (int)           Event_Message, 
                            (unsigned long) Event_LongASCIICode, 
                            (unsigned long) Event_LongRawByte );
                        debug_print ("sendto_eventqueue: >>>> [MSG_SYSKEYUP.function] to wwf\n");        
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
           //if (current_input_mode == INPUT_MODE_SETUP)
           if ( IOControl.useEventQueue == TRUE )
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
                   
               debug_print ("sendto_eventqueue: >>>> [default] to wwf\n");
            
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
 * UserInput_SendKeyboardMessage:
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
UserInput_SendKeyboardMessage (
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

    // true for keyup and false for keydown.
    // int Break = TRUE;

    if (tid<0){
        debug_print("UserInput_SendKeyboardMessage: tid\n");
        return (int) (-1);
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


// ==========
// Step 2
// Tratar as mensagens.
// Traduzir rawbyte em evento.


    // ================================================
    // Se a tecla for (liberada).
    // ligado. tecla liberada.
    if ( (Keyboard_RawByte & LDISC_KEY_RELEASED) != 0 ) // liberada.
    {
        // Break = TRUE;
        
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
    //  Tecla (pressionada) ...........
    // bit desligado. tecla pressionada.
    if ( (Keyboard_RawByte & LDISC_KEY_RELEASED) == 0 )  // pressionada.
    {
        // Break = FALSE;
        
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



// == Dispatch =======================================================

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

    if ( IOControl.initialized != TRUE ){
        panic ("UserInput_SendKeyboardMessage: IO Control not initialized\n");
    }

    if ( IOControl.useTTY != TRUE && 
         IOControl.useEventQueue != TRUE )
    {
        panic ("UserInput_SendKeyboardMessage: [IO Control] No valid mode\n");
    }

//
// Destination!
//

    // Mandaremos o evento para 3 lugares possiveis.
    // + para o tty de teclado.
    // + para o procedimento de janela do sistema ou
    // + para a fila na thread em foreground.


// ===========================
// INPUT_MODE_TTY
    
    // #todo
    // Send the message to the TYY,
    // this way the foreground process is able to read it
    // using stdin.
    // See:
    // devmgr.h ps2kbd.c
    // ...


    //if ( current_input_mode == INPUT_MODE_TTY )
    if ( IOControl.useTTY == TRUE )
    {
         panic ("UserInput_SendKeyboardMessage: [FIXME] File permission issue\n");

         //sendto_tty (   
         //    (struct tty_d *)    PS2KeyboardDeviceTTY,
         //    (struct window_d *) Event_Window,
         //    (int)               Event_Message,
         //    (unsigned long)     Event_LongASCIICode,
         //    (unsigned long)     Event_LongRawByte );

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


// ===========================
// INPUT_MODE_SETUP

    // #bugbug
    // Bem, na verdade esse tipo de input pode ser usado para
    // além do ambiente de setup. Podemos usar também
    // nos window server e seus clientes.

    //if ( current_input_mode == INPUT_MODE_SETUP )
    if ( IOControl.useEventQueue == TRUE )
    {
        sendto_eventqueue ( 
            (int) tid,
            (struct window_d *) Event_Window,
            (int)               Event_Message,
            (unsigned long)     Event_LongASCIICode,
            (unsigned long)     Event_LongRawByte );

        // #bugbug: O retorno deve ser o mesmo do diálogo acima.
        return 0;
    }


// ===========================
// INPUT_MODE_WS


    // #todo
    // This is a work in progress
    // We're gonna send messages to the applications
    // on an environment with a loadable window server.
    
    //if ( current_input_mode == INPUT_MODE_WS )
    //{
    //    panic("KGWS_SEND_KEYBOARD_MESSAGE: [TODO] INPUT_MODE_WS input mode\n");
    //}

    return (int) (-1);
}


//==========
/*
 *************************************************
 * kgws_send_to_tid:
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




// ==========================================================

void kgws_enable(void)
{
    debug_print("kgws_enable: Enable KGWS\n");
         printf("kgws_enable: Enable KGWS\n");
    refresh_screen();
    
    // Sending event messages to the thread associated with the wwf.
    //current_input_mode = INPUT_MODE_SETUP;
    IOControl.useEventQueue = TRUE;
    
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
    // current_input_mode = INPUT_MODE_TTY;
    
    // #bugbug: This is a test yet.
    //IOControl.useEventQueue = FALSE;
    
    EnableKGWS = FALSE;
}




// called by x86_64/x64init.c
// #todo
// Maybe we can use some parametes here.

int KGWS_initialize(void)
{
    debug_print("KGWS_initialize:[TODO]\n");

    //#todo
    init_logon_manager();
    
    return 0;
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

// Registrando o processo do window server.
// See: gpid.h
int register_ws_process ( pid_t pid )
{

    if ( pid<0 || pid >= PROCESS_COUNT_MAX )
    {
        debug_print("register_ws_process: [FAIL] pid\n");
        return -1;
    }

    if ( __gpidWindowServer != 0 ){
        debug_print("register_ws_process: [FAIL] __gpidWindowServer\n");
        return -1;
    }

    __gpidWindowServer = (pid_t) pid;

    return 0;
}












