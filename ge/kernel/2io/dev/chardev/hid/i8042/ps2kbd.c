/*
 * File: ps2kbd.c
 *
 *     Keyboard controller support.     
 *     Ring 0. Kernel base persistent code.
 *
 * Credits:
 *     2018 - Nelson Cole.
 *     2019 - Fred Nora.
 */


// See:
// http://www.brokenthorn.com/Resources/OSDev19.html



#include <kernel.h>


// local
void ps2kbd_drain(void);
void ps2kbd_drain(void)
{
    int i=0;
    char _byte=0;
    
    for(i=0; i<9; i++)
        _byte = (char) in8(60);
}



/*
  //Credits: serenity os
#define IRQ_KEYBOARD 1
#define I8042_BUFFER 0x60
#define I8042_STATUS 0x64
#define I8042_ACK 0xFA
#define I8042_BUFFER_FULL 0x01
#define I8042_WHICH_BUFFER 0x20
#define I8042_MOUSE_BUFFER 0x20
#define I8042_KEYBOARD_BUFFER 0x00
 */

//vamos apenas carregar um arquivo qualquer.
void __load_path_test(void)
{
    int status = -1;
    
    void *__address = 0;
    
    // Endereço para carregar o arquivo
    // 400 KB.

    __address = (void *) kmalloc(400*1024);
    //__address = (void *) kmalloc(600*1024);


    //fs_load_path ("/ETC/HELLO.CPP",(unsigned long) __address);
    //fs_load_path ("/ETC/NEWDIR/HELLO.CPP",(unsigned long) __address);
    status = fs_load_path ("/ETC/NEWDIR/LASTDIR/HELLO.CPP",(unsigned long) __address);

    if ( status < 0 )
        printf ("__load_path_test: load_path fail\n");


    // Show file.

    if ( status == 0 )
        printf("%s \n",__address);    
    
    refresh_screen();
}





/*
enum KYBRD_ENCODER_IO {
 
	KYBRD_ENC_INPUT_BUF	=	0x60,
	KYBRD_ENC_CMD_REG	=	0x60
};
 
enum KYBRD_CTRL_IO {
 
	KYBRD_CTRL_STATS_REG	=	0x64,
	KYBRD_CTRL_CMD_REG	=	0x64
};
*/


// Keyboard Encoder Commands
/*
Command	Descripton
0xED	Set LEDs
0xEE	Echo command. Returns 0xEE to port 0x60 as a diagnostic test
0xF0	Set alternate scan code set
0xF2	Send 2 byte keyboard ID code as the next two bytes to be read from port 0x60
0xF3	Set autrepeat delay and repeat rate
0xF4	Enable keyboard
0xF5	Reset to power on condition and wait for enable command
0xF6	Reset to power on condition and begin scanning keyboard
0xF7	Set all keys to autorepeat (PS/2 only)
0xF8	Set all keys to send make code and break code (PS/2 only)
0xF9	Set all keys to generate only make codes
0xFA	Set all keys to autorepeat and generate make/break codes
0xFB	Set a single key to autorepeat
0xFC	Set a single key to generate make and break codes
0xFD	Set a single key to generate only break codes
0xFE	Resend last result
0xFF	Reset keyboard to power on state and start self test
*/


//Return Codes
/*
Value	Descripton
0x0	Internal buffer overrun
0x1-0x58, 0x81-0xD8	Keypress scan code
0x83AB	Keyboard ID code returned from F2 command
0xAA	Returned during Basic Assurance Test (BAT) after reset. Also L. shift key make code
0xEE	Returned from the ECHO command
0xF0	Prefix of certain make codes (Does not apply to PS/2)
0xFA	Keyboard acknowledge to keyboard command
0xFC	Basic Assurance Test (BAT) failed (PS/2 only)
0xFD	Diagonstic failure (Except PS/2)
0xFE	Keyboard requests for system to resend last command
0xFF	Key error (PS/2 only)
*/



// Onboard Keyboard Controller Commands
// Command Listing
/*
Command	Descripton
Common Commands
0x20	Read command byte
0x60	Write command byte
0xAA	Self Test
0xAB	Interface Test
0xAD	Disable Keyboard
0xAE	Enable Keyboard
0xC0	Read Input Port
0xD0	Read Output Port
0xD1	Write Output Port
0xE0	Read Test Inputs
0xFE	System Reset
0xA7	Disable Mousr Port
0xA8	Enable Mouse Port
0xA9	Test Mouse Port
0xD4	Write To Mouse
Non Standard Commands
0x00-0x1F	Read Controller RAM
0x20-0x3F	Read Controller RAM
0x40-0x5F	Write Controller RAM
0x60-0x7F	Write Controller RAM
0x90-0x93	Synaptics Multiplexer Prefix
0x90-0x9F	Write port 13-Port 10
0xA0	Read Copyright
0xA1	Read Firmware Version
0xA2	Change Speed
0xA3	Change Speed
0xA4	Check if password is installed
0xA5	Load Password
0xA6	Check Password
0xAC	Disagnostic Dump
0xAF	Read Keyboard Version
0xB0-0xB5	Reset Controller Line
0xB8-0xBD	Set Controller Line
0xC1	Continuous input port poll, low
0xC2	Continuous input port poll, high
0xC8	Unblock Controller lines P22 and P23
0xC9	Block Controller lines P22 and P23
0xCA	Read Controller Mode
0xCB	Write Controller Mode
0xD2	Write Output Buffer
0xD3	Write Mouse Output Buffer
0xDD	Disable A20 address line
0xDF	Enable A20 address line
0xF0-0xFF	Pulse output bit
*/


//
// Propotypes
//


int BAT_TEST (void);




/*
 ******************************************************************* 
 * __local_ps2kbd_procedure:
 * 
 *       This function handle the emergency keys F5, F6, F6 and F8.
 *       MSG_SYSKEYUP only.
 */

// Local function.

unsigned long 
__local_ps2kbd_procedure ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{

   // #test
   // Testando uma rotina de pintura que usa escape sequence.
   // Queremos que ela funcione na máquina real.
   // Vamos testar os ponteiros.


    char buffer[128];
    sprintf (buffer,"My super \x1b[8C string!!\n"); 

    int Status = -1;


    if (msg<0)
        return 0;


    switch (msg){

        // Pressionadas: teclas de funçao
        case MSG_SYSKEYDOWN: 
            switch (long1)  
            {

                case VK_F1:
                    if (ctrl_status == 1){
                        printf ("__local_ps2kbd_procedure: control + f1\n");
                        refresh_screen();
                    }
                    if (alt_status == 1){
                        printf ("__local_ps2kbd_procedure: alt + f1\n");
                        refresh_screen();
                    }
                    if (shift_status == 1){
                        printf ("__local_ps2kbd_procedure: shift + f1\n");
                        console_switch_to(1);
                        refresh_screen();
                    }
                    return 0;
                    break;

                case VK_F2:
                    if (ctrl_status == 1){
                        printf ("__local_ps2kbd_procedure: control + f2\n");
                        refresh_screen();
                    }
                    if (alt_status == 1){
                        printf ("__local_ps2kbd_procedure: alt + f2\n");
                        refresh_screen();
                    }
                    if (shift_status == 1){
                        printf ("__local_ps2kbd_procedure: shift + f2\n");
                        console_switch_to(2);
                        refresh_screen();
                    }
                    return 0;
                    break;

                case VK_F3:
                    if (ctrl_status == 1){
                        printf ("__local_ps2kbd_procedure: control + f3\n");
                        refresh_screen();
                    }
                    if (alt_status == 1){
                        printf ("__local_ps2kbd_procedure: alt + f3\n");
                        refresh_screen();
                    }
                    if (shift_status == 1){
                        printf ("__local_ps2kbd_procedure: shift + f3\n");
                        console_switch_to(3);
                        refresh_screen();
                    }
                    return 0;
                    break;

                case VK_F4:
                    if (ctrl_status == 1){
                        printf ("__local_ps2kbd_procedure: control + f4\n");
                        refresh_screen();
                    }
                    if (alt_status == 1){
                        printf ("__local_ps2kbd_procedure: alt + f4\n");
                        refresh_screen();
                    }
                    if (shift_status == 1){
                        printf ("__local_ps2kbd_procedure: shift + f4\n");
                        refresh_screen();
                    }
                    return 0;
                    break;


                // Reboot
                case VK_F5:
                    if (ctrl_status == 1){
                    reboot();
                    //__load_path_test(); //local ok
                    //do_clone_execute_process ("init2.bin");
                    }
                    if (alt_status == 1){
                        printf ("__local_ps2kbd_procedure: alt + f5\n");
                        refresh_screen();
                    }
                    if (shift_status == 1){
                        printf ("__local_ps2kbd_procedure: shift + f5\n");
                        refresh_screen();
                    }
                    return 0;
                    break;

                // 
                case VK_F6:
                    if (ctrl_status == 1){
                    ws_show_info();
                    //initialize_frame_table();
                    //printf (">> %x \n", get_new_frame() );
                    //pages_calc_mem();
                    //testNIC();
                    // #se o processo não existe vai dar problema.
                    //tty_send_message (103,buffer, 32, 444, 0, 0);
                    //tty_send_message (104,buffer, 32, 444, 0, 0);
                    //refresh_screen();
                    }
                    if (alt_status == 1){
                        printf ("__local_ps2kbd_procedure: alt + f6\n");
                        refresh_screen();
                    }
                    if (shift_status == 1){
                        printf ("__local_ps2kbd_procedure: shift + f6\n");
                        refresh_screen();
                    }
                    return 0;
                    break;

                // Test 1.
                case VK_F7:
                    if (ctrl_status == 1){
                    //fs_show_file_info(stdin);
                    //fs_show_file_info(stdout);
                    //fs_show_file_info(stderr);
                    fs_show_file_table();
                    fs_show_inode_table();
                   
                    
                    //bg_load_image(); //ok
                    //console_write (0, buffer,62);
                    //Status = (int) KiSearchFile ( "GRAMADO TXT", VOLUME1_ROOTDIR_ADDRESS );
                    //Status = (int) KiSearchFile ( "GRAMADOxTXT", VOLUME1_ROOTDIR_ADDRESS );
                    //if (Status == 1){
                    //    printf("found\n");
                    //}else{
                    //    printf("not found\n");
                    //};
                    //refresh_screen();
                    }
                    if (alt_status == 1){
                        printf ("__local_ps2kbd_procedure: alt + f7\n");
                        refresh_screen();
                    }
                    if (shift_status == 1){
                        printf ("__local_ps2kbd_procedure: shift + f7\n");
                        refresh_screen();
                    }
                    return 0;
                    break;

                // Test 2.
                case VK_F8:
                    if (ctrl_status == 1){
                    //printf (">> %x \n", get_new_frame() );
                    //refresh_screen();
                    // testNIC ();
                    //pciInfo ();
                    // ahciSATAInitialize (1);
                    //refresh_screen();
                    }
                    if (alt_status == 1){
                        printf ("__local_ps2kbd_procedure: alt + f8\n");
                        refresh_screen();
                    }
                    if (shift_status == 1){
                        printf ("__local_ps2kbd_procedure: shift + f8\n");
                        refresh_screen();
                    }
                    return 0;
                    break;

                case VK_F9:
                    if (ctrl_status == 1){
                        printf ("__local_ps2kbd_procedure: control + f9\n");
                        refresh_screen();
                    }
                    if (alt_status == 1){
                        printf ("__local_ps2kbd_procedure: alt + f9\n");
                        refresh_screen();
                    }
                    if (shift_status == 1){
                        printf ("__local_ps2kbd_procedure: shift + f9\n");
                        refresh_screen();
                    }
                    return 0;
                    break;

                case VK_F10:
                    if (ctrl_status == 1){
                        printf ("__local_ps2kbd_procedure: control + f10\n");
                        refresh_screen();
                    }
                    if (alt_status == 1){
                        printf ("__local_ps2kbd_procedure: alt + f10\n");
                        refresh_screen();
                    }
                    if (shift_status == 1){
                        printf ("__local_ps2kbd_procedure: shift + f10\n");
                        refresh_screen();
                    }
                    return 0;
                    break;

                case VK_F11:
                    if (ctrl_status == 1){
                        printf ("__local_ps2kbd_procedure: control + f11\n");
                        refresh_screen();
                    }
                    if (alt_status == 1){
                        printf ("__local_ps2kbd_procedure: alt + f11\n");
                        refresh_screen();
                    }
                    if (shift_status == 1){
                        printf ("__local_ps2kbd_procedure: shift + f11\n");
                        refresh_screen();
                    }
                    return 0;
                    break;

                case VK_F12:
                    if (ctrl_status == 1){
                        printf ("__local_ps2kbd_procedure: control + f12\n");
                        refresh_screen();
                    }
                    if (alt_status == 1){
                        printf ("__local_ps2kbd_procedure: alt + f12\n");
                        refresh_screen();
                    }
                    if (shift_status == 1){
                        printf ("__local_ps2kbd_procedure: shift + f12\n");
                        refresh_screen();
                    }
                    return 0;
                    break;

                default:
                    // nothing
                    return 0;
            
            }
    };

    refresh_screen();
    return 0;
}









/*
 ***************
 * KEYBOARD_SEND_MESSAGE:
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


int KEYBOARD_SEND_MESSAGE (unsigned char SC){

    struct process_d  *__p;
    struct thread_d   *t;

    struct window_d   *w;

    // Step 0 
    // Declarações de variáveis.

    //Variáveis para tecla digitada.
    unsigned char scancode=0;
    unsigned long tmp_sc=0;
    unsigned char key=0;         //Tecla (uma parte do scancode).  

    //int fakewin;             //arg1
    int message=0;             //arg2.
    unsigned long ch=0;        //arg3 - (O caractere convertido para ascii).
    unsigned long status=0;    //arg4.  
    
    int msg_status = -1;
    
    int save_pos = 0;




    // Step1
    // Pegar o scancode.
    // O driver pegou o scancode e passou para a disciplina de linha 
    // através de parâmetro.

    scancode = SC;


	// Obs: 
	// Observe que daqui pra frente todas as rotinas poderiam 
	// estar em user mode.


    // #debug.
    // Show the scancode if the flag is enabled.

    if (scStatus == 1){
        kprintf ("{%d,%x} ", scancode, scancode );
        // Refresh screen?
    }


    // Step 2
    // Tratar as mensagens.


    // ================================================
    // Se a tecla for (liberada).
    // ligado. tecla liberada.
    if ( (scancode & LDISC_KEY_RELEASED) != 0 ) // liberada.
    {
        // Desativando o bit de paridade caso esteja ligado.

        key = scancode;
        key &= LDISC_KEY_MASK;    

		// Configurando se é do sistema ou não.
		// #todo: 
		// Aqui podemos chamar uma rotina interna que faça essa checagem.

        switch (key)
        {
			//Os primeiros 'case' é quando libera tecla do sistema.
			//O case 'default' é pra quando libera tecla que não é do sistema.

			//left Shift liberado.
            case VK_LSHIFT: 
                shift_status = 0;  message = MSG_SYSKEYUP;
                printf ("VK_LSHIFT: Liberada\n"); refresh_screen();
                break;

			//Left Control liberado.
            case VK_LCONTROL:
                ctrl_status = 0;  message = MSG_SYSKEYUP;
                printf ("VK_LCONTROL: Liberada\n"); refresh_screen();
                break;

			//left Winkey liberada.
            case VK_LWIN:
                winkey_status = 0;  message = MSG_SYSKEYUP;
                printf ("VK_LWIN: Liberada\n"); refresh_screen();
                break;

			//Left Alt liberado.
            case VK_LMENU:
                alt_status = 0;  message = MSG_SYSKEYUP;
                printf ("VK_LMENU: Liberada\n"); refresh_screen();
                break;

			//right winkey liberada.
            case VK_RWIN:
                winkey_status = 0;  message = MSG_SYSKEYUP;
                printf ("VK_RWIN: Liberada\n"); refresh_screen();
                break;

			//control menu.
            case VK_CONTROL_MENU:
                //controlmenu_status = 0; //@todo
                message = MSG_SYSKEYUP;
                printf ("VK_CONTROL_MENU: Liberada\n"); refresh_screen();
                break;

            //right control liberada.
            case VK_RCONTROL:
                ctrl_status = 0;  message = MSG_SYSKEYUP;
                printf ("VK_RCONTROL: Liberada\n"); refresh_screen();
                break;

			//right Shift liberado.
            case VK_RSHIFT:
                shift_status = 0;  message = MSG_SYSKEYUP;
                printf ("VK_RSHIFT: Liberada\n"); refresh_screen();
                break;

            // Funções liberadas.
            case VK_F1: case VK_F2: case VK_F3: case VK_F4:
            case VK_F5: case VK_F6: case VK_F7: case VK_F8:
            case VK_F9: case VK_F10: case VK_F11: case VK_F12:
                message = MSG_SYSKEYUP;
                break;

			// ...

			// A tecla liberada NÃO é do sistema.
            default:
                message = MSG_KEYUP;
                break;
        };

		// Selecionando o char para os casos de tecla liberada.

		// Analiza: Se for tecla normal, pega o mapa de caracteres apropriado.
		// minúscula
		// Nenhuma tecla de modificação ligada.
        if (message == MSG_KEYUP)
        {
            // Minúsculas.
            if (capslock_status == 0)
            { ch = map_abnt2[key];   goto done; }
            // Maiúsculas.
            if (capslock_status == 1)
            { ch = shift_abnt2[key]; goto done; }
            // ...
        }

        // Analiza: Se for do sistema usa o mapa de caracteres apropriado. 
        // Normal.
        if (message == MSG_SYSKEYUP)
        {   
            // se liberada teclas de sistema como capslock ligado
            if (capslock_status == 0)
            { ch = map_abnt2[key];   goto done; }
            // se liberada teclas de sistema como capslock desligado
            if (capslock_status == 1)
            { ch = shift_abnt2[key]; goto done; }
            // ...
        }


        // Nothing.
        goto done;
    };

    // ================================================
    // * Tecla (pressionada) ...........
    // bit desligado. tecla pressionada.
    if ( (scancode & LDISC_KEY_RELEASED) == 0 )  // pressionada.
    { 
        key = scancode;
        key &= LDISC_KEY_MASK; //Desativando o bit de paridade caso esteja ligado.

		//O Último bit é zero para key press.
		//Checando se é a tecla pressionada é o sistema ou não.
		//@todo: Aqui podemos chamar uma rotina interna que faça essa checagem.
		
        switch (key)
        {
			//back space será tratado como tecla normal
			
			//@todo: tab,
            //?? tab será tratado como tecla normal por enquanto.
			
			//caps lock keydown
            case VK_CAPITAL:
                //muda o status do capslock não importa o anterior.
                if (capslock_status == 0)
                { 
                    capslock_status = 1; message = MSG_SYSKEYDOWN; 
                    break; 
                }
                if (capslock_status == 1)
                { 
                    capslock_status = 0; message = MSG_SYSKEYDOWN; 
                    break; 
                }
                break; 

			//Left shift pressionada.
            case VK_LSHIFT:
            //case KEY_SHIFT:
                shift_status = 1; message = MSG_SYSKEYDOWN;
                printf ("VK_LSHIFT: Pressionada\n"); refresh_screen();
                break;

			//left control pressionada.
			//case KEY_CTRL:
            case VK_LCONTROL:
                ctrl_status = 1; message = MSG_SYSKEYDOWN;
                printf ("VK_LCONTROL: Pressionada\n"); refresh_screen();
                break;

			//Left Winkey pressionada.
            case VK_LWIN:
                winkey_status = 1; message = MSG_SYSKEYDOWN;
                printf ("VK_LWIN: Pressionada\n"); refresh_screen();
                break;

            //left Alt pressionada.
            case VK_LMENU:
                alt_status = 1;  message = MSG_SYSKEYDOWN;
                printf ("VK_LMENU: Pressionada\n"); refresh_screen();
                break;

			//@todo alt gr.	

			//Right Winkey pressionada.
            case VK_RWIN:
                winkey_status = 1;  message = MSG_SYSKEYDOWN;
                printf ("VK_RWIN: Pressionada\n"); refresh_screen();
                break;

            //@todo: Control menu.
            
			//Right control pressionada.
            case VK_RCONTROL:
                ctrl_status = 1; message = MSG_SYSKEYDOWN;
                printf ("VK_RCONTROL: Pressionada\n"); refresh_screen();
                break;

			//Right shift pressionada.
            case VK_RSHIFT:
                shift_status = 1; message = MSG_SYSKEYDOWN;
                printf ("VK_RSHIFT: Pressionada\n"); refresh_screen();
                break;

            case VK_F1: case VK_F2: case VK_F3: case VK_F4:
            case VK_F5: case VK_F6: case VK_F7: case VK_F8:
            case VK_F9: case VK_F10: case VK_F11: case VK_F12:
                message = MSG_SYSKEYDOWN;
                break;


            // Num Lock.
            case VK_NUMLOCK:
                // Muda o status do numlock não importa o anterior.
                if (numlock_status == 0){
                    numlock_status = 1; message = MSG_SYSKEYDOWN;
                    break;
                }
                if (numlock_status == 1){ 
                    numlock_status = 0; message = MSG_SYSKEYDOWN; 
                    break; 
                }
                break;

            // Scroll Lock.
            case VK_SCROLL:
                // Muda o status do numlock não importa o anterior.
                if (scrolllock_status == 0){  
                    scrolllock_status = 1; message = MSG_SYSKEYDOWN;
                    break;
                }
                if (scrolllock_status == 1){ 
                    scrolllock_status = 0; message = MSG_SYSKEYDOWN; 
                    break; 
                }
                break;

            //...

            // A tecla pressionada não é do sistema.
            default:
                // printf("keyboard debug: default: MSG_KEYDOWN\n");
                message = MSG_KEYDOWN;
                break;
        };

        // ==============================
        // Teclas de digitaçao
        // Uma tecla normal foi pressionada.
        // mensagem de digitação.	
        if (message == MSG_KEYDOWN)
        {
            // Minúsculas.
            if (capslock_status == 0)
            { ch = map_abnt2[key];   goto done; }
            // Maiúsculas.
            if (capslock_status == 1)
            { ch = shift_abnt2[key]; goto done; }
            // ...
        }

        // ==============================
        // Teclas de sistema
        // Uma tecla do sistema foi pressionada.
        if (message == MSG_SYSKEYDOWN)
        {   
            // se pressionamos teclas de sistema como capslock ligado
            if (capslock_status == 0)
            { ch = map_abnt2[key];   goto done; }
            // se pressionamos teclas de sistema como capslock desligado
            if (capslock_status == 1)
            { ch = shift_abnt2[key]; goto done; }
            // ...
        }

        // Nothing.
        goto done;
        
    };  // Fim do else


    //
    // Done.
    //

	// Para finalizar, 
	// vamos enviar a mensagem para fila certa.
    
done:

    // Fixing the Scan code.
    tmp_sc = (unsigned long) scancode;
    tmp_sc = (unsigned long) ( tmp_sc & 0x000000FF );


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
    
    if ( (void *) PS2KeyboardDeviceTTY != NULL )
    {
       // ok. This is a valid tty pointer.
       
       // #test
       // Let's write something ...
       event_buffer[0] = 0;        // window 
       event_buffer[1] = message;  // msg
       event_buffer[2] = ch;       // char
       event_buffer[3] = tmp_sc;   // sc
       
       // it is gonna write in the base of the buffer.
       __tty_write ( 
           (struct tty_d *) PS2KeyboardDeviceTTY, 
           (char *) event_buffer, 
           (int) (4*4) );  //16 bytes 
    }
   
        
    switch (message){
       
        // Para os dois casos.
        // quando o control ou a tecla de funçao forem pressionadas ou liberadas.
        case MSG_SYSKEYDOWN: 
        case MSG_SYSKEYUP:
            switch (ch){

                // function key
                // Quando pressionarmos uma tecla de funçao.
                // no metodo olharemos control ou alt.
                case VK_F1:  case VK_F2:  case VK_F3:  case VK_F4:
                case VK_F5:  case VK_F6:  case VK_F7:  case VK_F8:
                case VK_F9:  case VK_F10:  case VK_F11:  case VK_F12:
                    // For all the input modes.
                    if (message == MSG_SYSKEYDOWN)
                    {
                       // se alguma tecla de controle esta pressionada, chamaremos o procedimento local.
                       if ( shift_status == 1 || ctrl_status == 1 || alt_status == 1 )
                       {
                           debug_print ("KEYBOARD_SEND_MESSAGE: >>>> [MSG_SYSKEYUP] to system procedure\n"); 
                            __local_ps2kbd_procedure ( 
                            w, 
                            (int) message, 
                            (unsigned long) ch, 
                            (unsigned long) tmp_sc );
                        debug_print("out of sysm procedure\n");
                        return 0;
                        }
                        // caso nenhuma tecla de controle esteja pressionada,
                        //enviaremos a tecla de funçao para a alicaçao.
                        if (current_input_mode == INPUT_MODE_SETUP)
                        {
                            kgws_send_to_controlthread_of_currentwindow ( 
                                w,
                                (int) message, 
                                (unsigned long) ch, 
                                (unsigned long) tmp_sc );
                            debug_print ("KEYBOARD_SEND_MESSAGE: >>>> [MSG_SYSKEYUP.function] to wwf\n");        
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
                        kgws_send_to_controlthread_of_currentwindow ( 
                             w,
                            (int) message, 
                            (unsigned long) ch, 
                            (unsigned long) tmp_sc );
                        debug_print ("KEYBOARD_SEND_MESSAGE: >>>> [MSG_SYSKEYUP.function] to wwf\n");        
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
               kgws_send_to_controlthread_of_currentwindow ( 
                   w,
                   (int) message, 
                   (unsigned long) ch, 
                   (unsigned long) tmp_sc );
               debug_print ("KEYBOARD_SEND_MESSAGE: >>>> [default] to wwf\n");
            
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


/*
 *************************************** 
 * xxx_keyboard_write: 
 * 
 */

// Esta função será usada para escrever dados do teclado 
// na porta 0x60, fora do IRQ1.

void xxx_keyboard_write (uint8_t data)
{
    kbdc_wait(1);

    out8 ( 0x60, data );

    wait_ns(400);
}


/*
 *************************************** 
 * xxx_keyboard_read: 
 * 
 */

// Esta função será usada para ler dados do teclado na 
// porta 0x60, fora do IRQ1.

uint8_t xxx_keyboard_read (void)
{
    kbdc_wait (0);

    uint8_t val = in8(0x60);
    
    wait_ns(400);
    
    return (uint8_t) val;
}



// Esta rotina faz o Auto-teste 0xaa êxito, 0xfc erro
// Credits: Nelson Cole.

int BAT_TEST (void){

    int val = -1;
    int i=0;

	// #todo:
	// Cuidado.
	// Diminuir isso se for possivel.
	// Nao funciona na maquina reala sem esse delay.

    for (i=0; i<99000; i++)
    {
        wait_ns (400);
    };


    for ( i=0; i<999; i++ )
    {
        val = (int) xxx_keyboard_read();

		//Ok funcionou o auto teste
        if(val == 0xAA)
		{
			printf ("ps2kbd.c: BAT_TEST OK\n");
			return (int) 0;
		
		//falhou
		}else if ( val == 0xFC ){
        
			printf ("ps2kbd.c: BAT_TEST fail\n");
            return (int) -1; 
        }
    
		// #bugbug
		// Tentar novamente, indefinidas vezes.
        // Esse é o problema. Vamos tentar apenas algumas vezes e falhar se não der certo.
		// Reenviar o comando. 
        // obs: este comando não é colocado em buffer
        
        //printf ("ps2kbd.c: BAT_TEST %d\n", i);
        xxx_keyboard_write (0xFE);       
    };


    // Fail
    printf ("ps2kbd.c: BAT_TEST %d times\n",i);
    return (int) -1; 
}



int ps2kbd_globals_initialize (void){


    int i=0;
    
	//user.h
    ioControl_keyboard = (struct ioControl_d *) kmalloc ( sizeof(struct ioControl_d) );

    if ( (void *) ioControl_keyboard == NULL )
    {
        panic ("ps2_keyboard_initialize: ioControl_keyboard fail");

    } else {

	    ioControl_keyboard->id = 0;
	    ioControl_keyboard->used = 1;
	    ioControl_keyboard->magic = 1234;

		//qual thread está usando o dispositivo.
		ioControl_keyboard->tid = 0;  
	    //ioControl_keyboard->
    };


    //int Type = 0;

	// #todo: 
	// Checar se o teclado é do tipo abnt2.   
	// É necessário sondar parâmetros de hardware,
	// como fabricante, modelo para configirar estruturas e variáveis.


/*
    switch(Type)
	{
	    //NULL
		case 0:	
		    break;
			
	    //Americano.
		case 1:	
		    break;

		//pt-ABNT2	
	    case 2:	
		    break;
			
		//...
		
		//Modelo americano
		default:	
		    break;
	}
	
*/
	
	//#debug
	//Tentando suprimir esse delay. OK
	//printf ("ps2_keyboard_initialize: 2\n");
	//refresh_screen();	




    int slot=-1;  //slot na file table.



    //
    // == _rbuffer =========================================
    //

    // Raw input buffer.
    
    file *current_stdin;

    slot = get_free_slots_in_the_file_table();
    if(slot<0 || slot >=NUMBER_OF_FILES)
        panic("ps2kbd_globals_initialize: current_stdin file slot");
   
    current_stdin = file_table[slot];
    current_stdin->filetable_index = slot;
    current_stdin->____object = ObjectTypeFile; //Regular file (tty buffer)
    current_stdin->used = 1;
    current_stdin->magic = 1234;
    current_stdin->_flags = (__SWR | __SRD); 
    
    // Struct.
    // Allocate memory for the struct.
    unsigned char *current_stdin_struct_buffer;
    current_stdin_struct_buffer = (unsigned char *) newPage ();
    current_stdin = (file *) &current_stdin_struct_buffer[0];

    // Buffer.
    // Allocate memory for the buffer.
    unsigned char *current_stdin_data_buffer;
    current_stdin_data_buffer   = (unsigned char *) newPage ();
    current_stdin->_base = (unsigned char *) &current_stdin_data_buffer[0];
    current_stdin->_bf._base = current_stdin->_base;
    current_stdin->_lbfsize = 128;
    current_stdin->_p = (unsigned char *) &current_stdin_data_buffer[0];    
    current_stdin->_r = 0;
    current_stdin->_w = 0;
    current_stdin->_cnt = 128;  //Limitando. na verdade e' 4KB.
    current_stdin->_tmpfname = "KBDIN   TXT";
    current_stdin->fd_counter = 1;

    // #test
    // Inicializando o buffer de teclado.
    // #bugbug Esses offsets são inicializados em wm também.
    // Elees deveriam estar dentro da estrutura de tty.
    for ( i=0; i< current_stdin->_cnt; i++ ){
        current_stdin->_base[i] = (char) 0;
    };
    keybuffer_head = 0;
    keybuffer_tail = 0;


    // Exportando o buffer para o driver usar.
    // Acessível através da tty.
    PS2keyboardTTY._rbuffer = current_stdin;



    //
    // == _obuffer =========================================
    //
    
    // Output buffer.

    file *current_stdout;

    slot = get_free_slots_in_the_file_table();
    if(slot<0 || slot >=NUMBER_OF_FILES)
        panic("ps2kbd_globals_initialize: current_stdout file slot");
   
    current_stdout = file_table[slot];
    current_stdout->filetable_index = slot;
    current_stdout->____object = ObjectTypeFile; //Regular file (tty buffer)
    current_stdout->used = 1;
    current_stdout->magic = 1234;
    current_stdout->_flags = (__SWR | __SRD); 
    
    // Struct.
    // Allocate memory for the struct.
    unsigned char *current_stdout_struct_buffer;
    current_stdout_struct_buffer = (unsigned char *) newPage ();
    current_stdout = (file *) &current_stdout_struct_buffer[0];

    // Buffer.
    // Allocate memory for the buffer.
    unsigned char *current_stdout_data_buffer;
    current_stdout_data_buffer   = (unsigned char *) newPage ();
    current_stdout->_base = (unsigned char *) &current_stdout_data_buffer[0];
    current_stdout->_bf._base = current_stdout->_base;
    current_stdout->_lbfsize = 128;
    current_stdout->_p = (unsigned char *) &current_stdout_data_buffer[0];    
    current_stdout->_r = 0;
    current_stdout->_w = 0;
    current_stdout->_cnt = 128;  //Limitando. na verdade e' 4KB.
    current_stdout->_tmpfname = "KBDOUT  TXT";
    current_stdout->fd_counter = 1;

    PS2keyboardTTY._obuffer = current_stdout;



	//
	// Set abnt2.
	//

    abnt2 = (int) 1;

    //Checar quem está tentando inicializar o módulo.    

	//model.
	
	//handler.


    //Key status.
    key_status = 0;
    escape_status = 0;
    tab_status = 0;
    winkey_status = 0;
    ctrl_status = 0;
    alt_status = 0;
    shift_status = 0;
    capslock_status = 0;
    scrolllock_status = 0;
    numlock_status = 0;
    //...


	//Debug support.
	scStatus = 0;    
    
    return 0;
}

/*
 **********************************
 * ps2kbd_initialize_device
 *     Inicializa o driver de teclado.
 *
 * #todo: 
 * Enviar para o driver de teclado o que for de lá.
 * Criar a variável keyboard_type ;;; ABNT2 
 * 2018 - Fred Nora.
 */

void ps2kbd_initialize_device (void)
{
    // register device.
    file *__file;   //device object
    char __tmpname[64];
    char *newname;



    __breaker_ps2keyboard_initialized = 0;


    ps2kbd_globals_initialize ();

//
// ==========================================
//


//__reset_keyboard:

    //++
    //=================================================
    
    // #obs:
    // A rotina abaixo reseta o teclado.
    
    wait_then_write ( 0x60, 0xFF );

	// ACK
    wait_ns (400);
    wait_ns (400);
    while ( xxx_keyboard_read() != 0xFA );  // #bugbug: Danger, Danger !!

    //=================================================
    //--


//__BasicAssuranceTest:

    //++
    //=================================================
        
    // #obs:
    // Essa é uma rotina de auto-teste.
    // Conhecida como: Basic Assurance Test - (BAT).

    if ( BAT_TEST () != 0 ){
        printf ("[WARMING] ps2kbd.c:  BAT_TEST ignored\n");
    }  

    //=================================================
    //--



//__BasicAssuranceTest:

    //++
    //=================================================

    // #obs:
    // Configurando leds do teclado.
    
	//Leds.
	//LED_SCROLLLOCK 
	//LED_NUMLOCK 
	//LED_CAPSLOCK 
	//keyboard_set_leds(LED_NUMLOCK);

    //=================================================
    //--



//__empty_buffer:

    //++
    //=================================================

    // Clean buffer
    
    //while (IO::in8(I8042_STATUS) & I8042_BUFFER_FULL)
        //IO::in8(I8042_BUFFER);

    //=================================================
    //--

    // Wait for nothing!
    kbdc_wait (1);
    kbdc_wait (1);
    kbdc_wait (1);
    kbdc_wait (1);

//
// ==========================================
//

    //
    // name
    //
    
    //#test
    // isso não é o ponto de montagem.
    sprintf( (char *) &__tmpname[0], "/DEV_I8042_KEYBOARD");
    newname = (char *) kmalloc (64);
    if ( (void*) newname == NULL )
        panic("ps2kbd_initialize_device: newname");
    strcpy (newname,__tmpname);



    // Agora registra o dispositivo pci na lista genérica
    // de dispositivos.
    // #importante: ele precisa de um arquivo 'file'.
    
    int register_status = -1;
    
    __file = (file *) kmalloc ( sizeof(file) );
    
    if ( (void *) __file == NULL ){
        panic ("ps2kbd_initialize_device: __file fail, can't register device");
    }else{
        __file->used = 1;
        __file->magic = 1234;
        __file->isDevice = 1;


        //
        // Register.
        //

        // #importante
        // Essa é a tabela de montagem de dispositivos.
        // O nome do dispositivo deve ser um pathname.
        // Mas podemos ter mais de um nome.
        // vamos criar uma string aqui usando sprint e depois duplicala.
     
        register_status = devmgr_register_device ( 
            (file *) __file,             // file
             newname,                    // device name.                  
             0,                          //class (char, block, network)
             1,                          //type (pci, legacy
             (struct pci_device_d *) 0,  //pci device
             NULL );                     //tty driver
    
        if (register_status<0){
            panic("ps2kbd_initialize_device: devmgr_register_device fail");
        }
        
        // object
        PS2KeyboardDeviceObject = (file *) __file;               // object file
        if ( (void *) PS2KeyboardDeviceObject == NULL ){
           panic("ps2kbd_initialize_device: PS2KeyboardDeviceObject fail");   
        }

        //device
        PS2KeyboardDevice = (struct device_d *) __file->device;  // device struct
        if ( (void *) PS2KeyboardDevice == NULL ){
           panic("ps2kbd_initialize_device: PS2KeyboardDevice fail");   
        }

        //driver
        //PS2KeyboardDeviceTTYDriver = (struct ttydrv_d *) __file->device->ttydrv; // driver struct.
        //if ( (void *) PS2KeyboardDeviceTTYDriver == NULL ){
        //   panic("ps2kbd_initialize_device: PS2KeyboardDeviceTTYDriver fail");   
        //}

        
        // #hackhack
        // Actually we need to create a tty for all the devices.
        // And it needs to be done in devmgr_register_device
        // But we do not have all these resources roght now.

        // tty
        PS2KeyboardDeviceTTY = (struct tty_d *) tty_create();
        if ( (void *) PS2KeyboardDeviceTTY == NULL ){
           panic("ps2kbd_initialize_device: PS2KeyboardDeviceTTY fail");   
        }

        // ...
    };


    // #test
    // Drain the output buffer for the first time. Residual.
    ps2kbd_drain();

//
// ==========================================
//

    g_driver_ps2keyboard_initialized = (int) 1;
    
    __breaker_ps2keyboard_initialized = 1;
}


/*
 ************************ 
 * keyboardGetKeyState: 
 * 
 */

//Pega o status das teclas de modificação.
unsigned long keyboardGetKeyState ( unsigned char key ){
	
	unsigned long State = 0;
	
	switch (key){
		
		case VK_LSHIFT: 
		    State = shift_status; 
			break;

	    case VK_LCONTROL:
		    State = ctrl_status;
		    break;

	    case VK_LWIN:
		    State = winkey_status;
		    break;

	    case VK_LMENU:
		    State = alt_status;
		    break;

	    case VK_RWIN:
		    State = winkey_status;
		    break;

	    case VK_RCONTROL:
		    State = ctrl_status;
		    break;
			
	    case VK_RSHIFT:
		    State = shift_status;
		    break;

	    case VK_CAPITAL:
		    State = capslock_status;
		    break;

	    case VK_NUMLOCK:
		    State = numlock_status;
		    break;
			
		case VK_SCROLL:
            State = scrolllock_status;
            break;			
			
		//...
	};


    return (unsigned long) State;
}


/*
 ************* 
 * ldisc_init_modifier_keys: 
 * 
 */

// #todo
// Rever esse nome. 

// Inicializa o status das teclas de modificação.
// são usadas em comjunto com outras teclas para criar atalhos.
// modificam temporariamente a função de outra tecla.

void ldisc_init_modifier_keys (void){
	
	// Modifier keys.
	
	shift_status = 0;
	ctrl_status = 0;
	winkey_status = 0;
    
	// Alternate.
    alt_status = 0;

	// Alternate Graphic.
    //altgr_status = 0; //@todo
    
	// Function.
	//fn_status = 0;  //@todo
	
	//...
}



/*
 ************* 
 * ldisc_init_lock_keys: 
 * 
 */

// #todo
// Rever esse nome. 

// modificam permanentemente a função de outra tecla.
//ativa as teclas extendidas.

void ldisc_init_lock_keys (void){
	
    // Capital Lock.	
	capslock_status = 0;
	
	// Scrolling Lock.
	scrolllock_status = 0;
	
	// Number Lock.
	numlock_status = 0;	
}


/*
 **********************************
 * keyboardEnable:
 *     Enable keyboard.
 */

void keyboardEnable (void){


    // #bugbug
    // Dizem que isso pode travar o sistema.

	// Wait for bit 1 of status reg to be zero.
    while ( ( in8 (0x64) & 2) != 0 )
    {
		//Nothing.
    };

	//Send code for setting Enable command.
    out8 (0x60,0xF4);
    //sleep(100);
}


/*
 * keyboardDisable:
 *     Disable keyboard.
 */

// Wait for bit 1 of status reg to be zero.
// Send code for setting disable command.
    
void keyboardDisable (void){

    while ( ( in8 (0x64) & 2) != 0 )
    { 
         // Nothing.
    };

    out8 (0x60,0xF5);
    //sleep(100);
}


/*
 ***************************************
 * keyboard_set_leds:
 *     Set keyboard flags.
 *     ED = Set led.
 */

void keyboard_set_leds (char flag){

    //#todo: Filtro.

    // Wait for bit 1 of status reg to be zero.
    while ( ( in8 (0x64) & 2) != 0 )
    {
        // Nothing.
    };
    // Send code for setting the flag.
    out8 (0x60,0xED); 
    sleep (100);


    // Wait for bit 1 of status reg to be zero.
    while ( ( in8 (0x64) & 2) != 0 )
    {
        // Nothing.
    };
    // Send flag. 
    out8 (0x60,flag);
    sleep (100);

    // #todo: Mudar o status.
    // switch(flag){}
}



/*
 * KdGetWindowPointer:
 *     Retorna o ponteiro da estrutura de janela que pertence a thread.
 *     Dado o id de uma thread, retorna o ponteiro de estrutura da janela 
 * à qual a thread pertence.
 */


// #bugbug
// Um driver de teclado não tem essa relação com janela.


void *KdGetWindowPointer (int tid)
{
    tid=0;
    panic("KdGetWindowPointer: Deprecated");
    return NULL;

    /* 
    struct thread_d *t;

    // #todo: 
    // Filtrar argumento. 

    if ( tid < 0 )
        return NULL;


    // Structure.
    t = (void *) threadList[tid];

    if ( (void *) t == NULL ){ return NULL; }

    return (void *) t->window;

    */
}


/*
 * KbGetMessage:
 *     Pega a mensagem na fila de mensagens na estrutura da thread
 * com foco de entrada.
 *
 * Na estrutura da thread com foco de entrada tem uma fila de mensagens.
 * Pegar a mensagem.
 * 
 * Para falha, retorna -1.
 *
 * @todo: bugbug: A mensagem deve estar na fila do processo, na
 *                estrutura do proceso. (Talvez não na thread e nem na janela.)
 */

int KbGetMessage (int tid)
{
    tid=0;
    panic("KbGetMessage: Deprecated");
    return -1;

    /*
	int ret_val;
	struct thread_d *t;
	
	// Structure.
	t = (void*) threadList[tid];

	if ( (void *) t != NULL )
	{
        ret_val = (int) t->msg;
	}else{
	    ret_val = (int) -1;    //Fail.
	};

	WindowProcedure->msgStatus = 0;    //Muda o status.
	return (int) ret_val;              //Retorna a mensagem.
	
	*/
}


/*
 * KbGetLongParam1:
 *    Pega o parametro "long1" do procedimento de janela de uma thread.
 */

unsigned long KbGetLongParam1 (int tid)
{

    tid=0;
    panic("KbGetLongParam1: Deprecated");
    return 0;

    /*
	struct thread_d *t;
	
	// Structure.
	t = (void *) threadList[tid];

    if ( (void *) t == NULL){
        return (unsigned long) 0; 
    }

    return (unsigned long) t->long1;
    
    */
}


/*
 * KbGetLongParam2:
 *     Pega o parametro "long2" do procedimento de janela de uma thread.
 */
unsigned long KbGetLongParam2 (int tid){

    tid=0;
    panic("KbGetLongParam2: Deprecated");
    return 0;

    /*
	struct thread_d *t;
	
	// Structure.
	t = (void *) threadList[tid];

    if ( (void *) t == NULL){
        return (unsigned long) 0; 
    }

    return (unsigned long) t->long2;
    */
}



// Get alt Status.
int get_alt_status (void)
{
    return (int) alt_status;
}


// Get control status.
int get_ctrl_status (void)
{
    return (int) ctrl_status;
}
 
 
//Get shift status.
int get_shift_status (void)
{
    return (int) shift_status;
}


/*
 *********************
 * kbdc_wait:
 *     Espera por flag de autorização para ler ou escrever.
 */


// Espera para ler ou para escrever!

void kbdc_wait (unsigned char type){

    if (type==0){

        while ( !in8(0x64) & 1 )
        {
            outanyb (0x80);
            outanyb (0x80);
            outanyb (0x80);
            outanyb (0x80);

            wait_ns (400);
        };

    }else{

        while ( in8(0x64) & 2 )
        {
            outanyb (0x80);
            outanyb (0x80);
            outanyb (0x80);
            outanyb (0x80);

            wait_ns (400);
        };
    };
}


// events.h
void set_current_keyboard_responder ( int i )
{
    current_keyboard_responder = i;
}


// events.h
int get_current_keyboard_responder (void)
{
    return (int) current_keyboard_responder;
}



//
// ===========================================================
//


/*
 *********************** 
 * __do_35: 
 *     Getting message from thread's queue.
 */

    // #todo: 
    // 35 - Getting message from the thread's queue. 
    // Vamos pegar uma mensagem na fila de mesagens da thread
    // e colocarmos nos elementos de single message para 
    // o aplicativo pegar.


void *__do_35 ( unsigned long buffer )
{

    panic ("__do_32: #todo");

    return NULL;

    /*
    unsigned long *message_address = (unsigned long *) buffer;
    
    unsigned char SC=0;
    
    struct thread_d *t;

    struct msg_d *msg;


    // ==================================
    //             STOPPED !!!
    // ==================================

    // #todo
    // Trabalhando nessa rotina de servir uma mensagem que está na fila.
    // Ainda nem existe a rotina que coloca a mensagem na fila.
    
    // #debug breakpoint.
    panic ("gde_serv-__do_32: #todo");

    // ==================================
    //             STOPPED !!!
    // ==================================
  
    
    
    if ( (void *) t == NULL ){
         panic ("__do_35: t");
    }


    //
    // Trying ...
    //

    
    
    //
    // #todo
    //
    
    // Vamos pegar uma mensagem na fila de mesagens da thread
    // e colocarmos nos elementos de single message para o aplicativo pegar.    
    // msg = (struct msg_d *) t->MsgQueue[ t->MsgQueueHead++ ]
    
    
    // pega o ponteiro da estrutura.
    msg = ( struct msg_d * ) t->MsgQueue[ t->MsgQueueHead ];
    

    // Ok temos uma mensagem
    // ja pegamos vamos limpar a fila, mesmo que a mensagem não preste.

    //limpa elemento da fila.
    t->MsgQueue[ t->MsgQueueHead ] = (unsigned long) 0;
    
    // avança
    t->MsgQueueHead++;
    
    // circula.
    if ( t->MsgQueueHead >= 32 )
    {
        t->MsgQueueHead = 0;
    }

    
    // #todo
    // Checar validade da estrutura de mensagem.
    // Checar validade da estrutura de thread;.    
    
    // A estrutura é inválida ou não há mensagens
    if ( (void *) msg == NULL )
    {
        return NULL;
    } else {
    
        if ( msg->used != 1 || msg->magic != 1234 )
        {
            panic ("__do_35: msg struct");
        }
        

        // #todo
        // Se o head for igual ao tail, então o processo não está respondendo.
        // Exceto na inicialização.
    
        // #todo
        // Pegar os elementos da estrutura de mensagem e colocar
        // no buffer me single message usado para pegar uma mensagem.
    
	    //padrão
	    message_address[0] = (unsigned long) msg->window;
	    message_address[1] = (unsigned long) msg->msg;
	    message_address[2] = (unsigned long) msg->long1;
	    message_address[3] = (unsigned long) msg->long2;
 
	    //sinalizamos que a mensagem foi consumida.
	    //#todo: nesse momento a estrutura da thread também precisa ser limpa.
        t->newmessageFlag = 0;    
        return (void *) 1;    
    };
    
    */
}


/*
 *********************** 
 * __do_111: 
 *     Getting single system message from the process queue.
 */

// Getting single message.
// No queue.
// See: thread structure.

	// #importante:
	// Esse é o get message usado pelos aplicativos.
	// O aplicativo envia um endereço de array e devemos colocar 4 longs 
	// como mensagem.
	// Isso funcionou. 
	// Esse será o padrão até usarmos ponteiro para estrutura.
	// A intenção agora é pegar a mensagem na estrutura de thread atual.
	// Desse modo cada aplicativo, quando estiver rodando, pegará as 
	// suas mensagens em sua própria fila.  
	// Se não houver mensagem na estrutura da thread, então tentaremos colocar alguma.
	// Vamos colocar alguma coisa do buffer de teclado.

// #todo
// Trocar por 'ubuf'

// #bugbug
// Isso eh valido para todos os tipos de mensagens nao somente teclado
// isso deveria sair daqui desse arquivo.

void *__do_111 ( unsigned long buffer ){

    struct thread_d *t;

    unsigned long *message_address = (unsigned long *) buffer;


    // Buffer
    // Se o buffer for inválido, não há o que fazer.
    if ( buffer == 0 ){ 
        panic ("__do_111: buffer"); 
    }


   // Again. 
   // Se o buffer for inválido.
   if ( &message_address[0] == 0 )
   {
       panic ("__do_111: buffer");

   }else{

        t = (void *) threadList[current_thread];

        if ( (void *) t == NULL ){
            panic ("__do_111: Invalid thread calling \n");
        }

        if ( t->used != 1 || t->magic != 1234 ){
            panic ("__do_111: Validation. Invalid thread calling \n");
        }

        // Get system message.
        message_address[0] = (unsigned long) t->window_list[ t->head_pos ];
        message_address[1] = (unsigned long) t->msg_list[ t->head_pos ];
        message_address[2] = (unsigned long) t->long1_list[ t->head_pos ];
        message_address[3] = (unsigned long) t->long2_list[ t->head_pos ];

        // Extra. 
        // Usado pelos servidores e drivers.
        message_address[4] = (unsigned long) t->long3_list[ t->head_pos ];
        message_address[5] = (unsigned long) t->long4_list[ t->head_pos ];

        // Clean
        t->window_list[ t->head_pos ] = NULL;
        t->msg_list[ t->head_pos ]    = 0;
        t->long1_list[ t->head_pos ]  = 0;
        t->long2_list[ t->head_pos ]  = 0;
        t->long3_list[ t->head_pos ]  = 0;
        t->long4_list[ t->head_pos ]  = 0;
        //...
        

        // Circula
        t->head_pos++;
        if ( t->head_pos >= 31 )
            t->head_pos = 0;
   
        //Sinaliza que há mensagem
        return (void *) 1; 
    };

    // No message.
    return NULL;
} 







//
// End.
//





