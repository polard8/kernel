
//esse será o ldisc

/*
 * File: hal\unblocked\keyboard.c
 *
 * Descrição:
 *     Driver de teclado presente dentro do Kernel Base.
 *     Esse driver não é para um modelo específico de teclado.
 *
 * Ambiente: 
 *     Kernel mode.
 *
 * Teclados usados:
 *     +Microsoft wired keyboard 600, abnt2. (usb).
 *     +Padrão americano.
 *
 * @todo: Fazer rotinas para identificar fabricante e modelo.
 *
 * @todo:
 *     Gerenciamento de caracteres, linhas e listas de linhas. Como acontece
 * no Unix, os caracteres recebidos aqui devem prosseguir até seu destino
 * final. O que envolve, algum tipo de disciplina de linhas, lista encadeadas 
 * de linha, emulador de terminal, fila do dispositivo gráfico, fila do
 * processo.
 * Obs: As listas de linhas ficam em lista encadeada, que provavelmente
 * pertence ao processo que está manipulando linhas.
 * Obs: A disciplica de linhas dentro do kernel serve também para movimentar
 * linhas de caracteres entre kernel mode e user mode, alimentar buffers de
 * dispositivos ou pegar linhas de caracteres nos buffers de dispositivos
 * como NIC, (placa de rede).
 *
 * >>>>>>> Não é responsabilidade do driver de teclado
 * encontrar o destino certo da mensagem, ele só precisa entregar ela pro
 * serviço de sistema responsável.
 *     
 * Teclado: Microsoft Wired keyboard 600 - ABNT2.
 *
 * Histórico: 
 *     Obs: Provavelmente criado entre 2005 e 2013.
 *     Versão 1.0, 2013 - Esse arquivo foi criado por Fred Nora.
 *     Versão 1.0, 2014 - Criação de rotinas básicas.
 *     Versão 1.0, 2015 - Criação de rotinas básicas.
 *     Versão 1.0, 2016 - Aprimoramento geral de rotinas básicas.
 *     ...
 */


#include <kernel.h>


//
// Imported functions.
//


extern void asm_reboot();    //Reboot.

//
// Definições para uso interno do módulo.
//
 
#define KEYBOARD_DRIVER_VERSION "1.0"

#define KEY_RELEASED 0x80

#define KEY_MASK 0x7F
#define CHEIO 1
#define VAZIO 0
#define OBF   0x01    //Output buffer flag.


//
// Ports:
// =====
//     The entire range for the keyboard is 60-6F,
//     a total of 16 values (a 16bit range).
//
//  @todo:
//      As portas do controlador ainda estão subutilizadas.
//      fazer um driver mais completo utilizando melhor o controlador.
//


//
//Command Listing:
//================
//Command	Descripton
//0xED	Set LEDs
//0xEE	Echo command. Returns 0xEE to port 0x60 as a diagnostic test
//0xF0	Set alternate scan code set
//0xF2	Send 2 byte keyboard ID code as the next two bytes to be read from port 0x60
//0xF3	Set autrepeat delay and repeat rate
//0xF4	Enable keyboard
//0xF5	Reset to power on condition and wait for enable command
//0xF6	Reset to power on condition and begin scanning keyboard
//0xF7	Set all keys to autorepeat (PS/2 only)
//0xF8	Set all keys to send make code and break code (PS/2 only)
//0xF9	Set all keys to generate only make codes
//0xFA	Set all keys to autorepeat and generate make/break codes
//0xFB	Set a single key to autorepeat
//0xFC	Set a single key to generate make and break codes
//0xFD	Set a single key to generate only break codes
//0xFE	Resend last result
//0xFF	Reset keyboard to power on state and start self test


/* Keyboard Commands */
#define KBD_CMD_SET_LEDS	    0xED	// Set keyboard leds.
#define KBD_CMD_ECHO     	    0xEE
#define KBD_CMD_GET_ID 	        0xF2	// get keyboard ID.
#define KBD_CMD_SET_RATE	    0xF3	// Set typematic rate.
#define KBD_CMD_ENABLE		    0xF4	// Enable scanning.
#define KBD_CMD_RESET_DISABLE	0xF5	// reset and disable scanning.
#define KBD_CMD_RESET_ENABLE   	0xF6    // reset and enable scanning.
#define KBD_CMD_RESET		    0xFF	// Reset.
//#define RESET  0xFE


/*
enum KYBRD_CTRL_STATS_MASK {
 
	KYBRD_CTRL_STATS_MASK_OUT_BUF	=	1,		//00000001
	KYBRD_CTRL_STATS_MASK_IN_BUF	=	2,		//00000010
	KYBRD_CTRL_STATS_MASK_SYSTEM	=	4,		//00000100
	KYBRD_CTRL_STATS_MASK_CMD_DATA	=	8,		//00001000
	KYBRD_CTRL_STATS_MASK_LOCKED	=	0x10,		//00010000
	KYBRD_CTRL_STATS_MASK_AUX_BUF	=	0x20,		//00100000
	KYBRD_CTRL_STATS_MASK_TIMEOUT	=	0x40,		//01000000
	KYBRD_CTRL_STATS_MASK_PARITY	=	0x80		//10000000
};

//! sets leds
void keyboard_set_leds( int num, int caps, int scroll) 
{ 
	char data = 0;
 
	//! set or clear the bit
	data = (char) (scroll) ? (data | 1) : (data & 1);
	data = (char) (num)    ? (num | 2)  : (num & 2);
	data = (char) (caps)   ? (num | 4)  : (num & 4);
 
	//! send the command -- update keyboard Light Emetting Diods (LEDs)
	kybrd_enc_send_cmd (KYBRD_ENC_CMD_SET_LED);
	kybrd_enc_send_cmd (data);
	
done:
    return;
};

//! send command byte to keyboard encoder
void kybrd_enc_send_cmd (uint8_t cmd) {
 
	//! wait for kkybrd controller input buffer to be clear
	while (1)
		if ( (kybrd_ctrl_read_status () & KYBRD_CTRL_STATS_MASK_IN_BUF) == 0)
			break;
 
	//! send command byte to kybrd encoder
	outportb (KYBRD_ENC_CMD_REG, cmd);
}
//! read status from keyboard controller
uint8_t kybrd_ctrl_read_status () {
 
	return inportb (KYBRD_CTRL_STATS_REG);
}
*/


//
// Variáveis internas
//
//int keyboardStatus;
//int keyboardError;
//...


//Status
//@todo: Status pode ser (int).
unsigned long key_status;
unsigned long escape_status;
unsigned long tab_status;
unsigned long winkey_status;  // >> Winkey shotcuts. #super
unsigned long ctrl_status;
unsigned long alt_status;
unsigned long shift_status;
unsigned long capslock_status;
unsigned long numlock_status;
//...

//
// ** kernel Winkey shotcuts **
//

/*
 WINKEY+
 ...
 */


 //mouse support
unsigned char *mousemsg;
unsigned char buffer_mouse[3];
unsigned char mouse_status;
unsigned char delta_x;
unsigned char delta_y;
int count_mouse;

//@todo: fazer rotina de get status algumas dessas variáveis.


//Se há uma nova mensagem de teclado. 
int kbMsgStatus;



//
// keyboardMessage
//     estrutura interna para mensagens.
//
struct keyboardMessage 
{
	unsigned char scancode;
	
	//hwnd;  //@todo: na verdade todo driver usará estrutura de janela descrita na API que o driver use.
	int message;
	unsigned long long1;
	unsigned long long2;
};


//Pega o status das teclas de modificação.
unsigned long keyboardGetKeyState(unsigned char key)
{
	unsigned long State = 0;
	
	switch(key)
	{   
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
			
		//...
	};

	//Nothing.
	
Done:
    return (unsigned long) State;		
}


/*
 * keyboardEnable:
 *     Enable keyboard.
 */
void keyboardEnable()
{
	//Wait for bit 1 of status reg to be zero.
    while( (inportb(0x64) & 2) != 0 ){
		//Nothing.
	};
	//Send code for setting Enable command.
    outportb(0x60,0xF4);
    //sleep(100);

done:
	return;
};


/*
 * keyboardDisable:
 *     Disable keyboard.
 */
void keyboardDisable()
{
	//Wait for bit 1 of status reg to be zero.
    while( (inportb(0x64) & 2) != 0 ){
		//Nothing.
	};
	//Send code for setting disable command.
    outportb(0x60,0xF5);
    //sleep(100);
	
done:
	return;
};


/*
 * keyboard_set_leds:
 *     Set keyboard flags.
 *     ED = Set led.
 */

// void keyboardSetLEDs(cahr flag)

void keyboard_set_leds(char flag)
{
	//@todo: filtro.

	//Wait for bit 1 of status reg to be zero.
    while( (inportb(0x64) & 2) != 0 ){
		//Nothing.
	};
	//Send code for setting the flag.
    outportb(0x60,0xED);            
    sleep(100);

	//Wait for bit 1 of status reg to be zero.
	while( (inportb(0x64) & 2) != 0 ){
	    //Nothing.	
	};
    //Send flag. 
	outportb(0x60,flag);
	sleep(100);

done:
	return;
};


 

/*
void keyboard();
void keyboard()
{
	//@todo: Create global.
	if(gKeyboardType == 1){
		abnt2_keyboard_handler();
	}
	//...
	return;
}
*/





/*
 ***********************************************
 *        LINE DISCIPLINE
 * funciona como um filtro.
 */
void LINE_DISCIPLINE(unsigned char SC)
{
    /*
	 * Step 0 - Declarações de variáveis.
	 */

	//Variáveis para tecla digitada.
    unsigned char scancode;
	unsigned char key;         //Tecla (uma parte do scancode).  
    unsigned long mensagem;    //arg2.	
    unsigned long ch;          //arg3 - (O caractere convertido para ascii).
    unsigned long status;      //arg4.  
	 
	struct window_d *wFocus;

	//Tela para debug em RING 0.
    //unsigned char *screen = (unsigned char *) 0x000B8000;   
    unsigned char *screen = (unsigned char *) SCREEN_START;    //Virtual.   
	//...
	
	
    /*
     * Step1 - Pegar o scancode.
     */

	//scancode = inportb(0x60);    //@todo: usar constante. (retorno).
    
	scancode = SC;
	

	//Obs: Observe que daqui pra frente todas as rotinas poderiam estar
	//     em user mode.


    //Show the scancode if the flag is enabled. 
	if(scStatus == 1){
	    printf("{%d,%x}\n",scancode,scancode);
	};
	
	
    /*
     *  Step 2 - Tratar as mensagens.
     */

    //Se a tecla for liberada.
	//DÁ '0' se o bit de paridade fo '0'.
    if( (scancode & KEY_RELEASED) == 0 )
	{
	    key = scancode;
		key &= KEY_MASK;    //Desativando o bit de paridade caso esteja ligado.

		//Configurando se é do sistema ou não.
		//@todo: Aqui podemos chamar uma rotina interna que faça essa checagem.
		switch(key)
		{
			//Os primeiros 'case' é quando libera tecla do sistema.
			//O case 'default' é pra quando libera tecla que não é do sistema.

			//@todo: Tab, capslock.
			
			//left Shift liberado.
			case VK_LSHIFT:
			//case KEY_SHIFT:
				shift_status = 0;
				mensagem = MSG_SYSKEYUP;
			    break;

			//Left Control liberado.			
			case VK_LCONTROL:
			//case KEY_CTRL:
				ctrl_status = 0;
				mensagem = MSG_SYSKEYUP;
				break;

			//left Winkey liberada.
			case VK_LWIN:
			    winkey_status = 0;
                mensagem = MSG_SYSKEYUP;
				break;

			//Left Alt liberado.
            case VK_LMENU:
				alt_status = 0;
				mensagem = MSG_SYSKEYUP;
			    break;

			//@todo: alt gr.

			//right winkey liberada.
			case VK_RWIN:
			    winkey_status = 0;
                mensagem = MSG_SYSKEYUP;
				break;

			//@todo: control menu.

            //right control liberada.
			case VK_RCONTROL:
				ctrl_status = 0;
				mensagem = MSG_SYSKEYUP;
				break;
				
			//right Shift liberado.
			case VK_RSHIFT:
				shift_status = 0;
				mensagem = MSG_SYSKEYUP;
			    break;

			//Funções liberadas.
            case VK_F1:
            case VK_F2:
            case VK_F3:
            case VK_F4:
            case VK_F5:
            case VK_F6:
            case VK_F7:
            case VK_F8:
            case VK_F9:
            case VK_F10:
            case VK_F11:
            case VK_F12:
			    mensagem = MSG_SYSKEYUP;
			    break;


			//...
				
			//A tecla liberada NÃO é do sistema.
			default:
			    mensagem = MSG_KEYUP;
				break;
		};

		//Selecionando o char para os casos de tecla liberada.

        //Analiza: Se for do sistema usa o mapa de caracteres apropriado. 
   		if(mensagem == MSG_SYSKEYUP)
		{
			//Normal.
			ch = map_abnt2[key];

			//@todo: aqui deve acionar o shift?
            //Talvez um switch.
		};

		//Analiza: Se for tecla normal, pega o mapa de caracteres apropriado.
		if(mensagem == MSG_KEYUP)
		{
		    //Normal.
			ch = map_abnt2[key];

			//Shift.
		    if(shift_status == 1){
			    ch = shift_abnt2[key];
			};

			//Control.
		    if(ctrl_status == 1){
			    ch = ctl_abnt2[key];
			};
            //Nothing.
		};
        //Nothing.
		goto done;
	}
	//else    // * Tecla pressionada ...........	
	
	
	if( (scancode & KEY_RELEASED) != 0 )
	{ 
		key = scancode;
		key &= KEY_MASK; //Desativando o bit de paridade caso esteja ligado.

		//O Último bit é zero para key press.
		//Checando se é a tecla pressionada é o sistema ou não.
		//@todo: Aqui podemos chamar uma rotina interna que faça essa checagem.
		switch(key)
		{
			//@todo: tab,

			case VK_CAPITAL:
			    //muda o status do capslock não importa o anterior.
				if(capslock_status == 0)
				{ 
				    capslock_status = 1;
					keyboard_set_leds(LED_CAPSLOCK);
					break; 
				};
				if(capslock_status == 1){ capslock_status = 0; break; };
				break; 

			//Left shift pressionada.
			case VK_LSHIFT:
			//case KEY_SHIFT:
				shift_status = 1;
				mensagem = MSG_SYSKEYDOWN;
			    break;

			//left control pressionada.
			case VK_LCONTROL:
			//case KEY_CTRL:
				ctrl_status = 1;
				mensagem = MSG_SYSKEYDOWN;
				break;

			//Left Winkey pressionada.
			case VK_LWIN:
			    winkey_status = 1;
				mensagem = MSG_SYSKEYDOWN;
				break;

            //left Alt pressionada.
            case VK_LMENU:
				alt_status = 1;
				mensagem = MSG_SYSKEYDOWN;
			    break;

			//@todo alt gr.	

			//Right Winkey pressionada.
			case VK_RWIN:
			    winkey_status = 1;
				mensagem = MSG_SYSKEYDOWN;
				break;
			
            //@todo: Control menu.
            
			//Right control pressionada.
			case VK_RCONTROL:
				ctrl_status = 1;
				mensagem = MSG_SYSKEYDOWN;
				break;

			//Right shift pressionada.
			case VK_RSHIFT:
				shift_status = 1;
				mensagem = MSG_SYSKEYDOWN;
			    break;


            case VK_F1:
            case VK_F2:
            case VK_F3:
            case VK_F4:
            case VK_F5:
            case VK_F6:
            case VK_F7:
            case VK_F8:
            case VK_F9:
            case VK_F10:
            case VK_F11:
            case VK_F12:
			    mensagem = MSG_SYSKEYDOWN;
			    break;


			//Num Lock.	
		    case VK_NUMLOCK:
			    //muda o status do numlock não importa o anterior.
				if(numlock_status == 0)
				{
				    numlock_status = 1;
					keyboard_set_leds(LED_NUMLOCK);  //@retorno.
					break;
				};
				if(numlock_status == 1){ numlock_status = 0; break; };
			    break;

            //...

			//A tecla pressionada não é do sistema.
			default:
			    //printf("keyboard debug: default: MSG_KEYDOWN\n");
			    mensagem = MSG_KEYDOWN;
				break;
		};

		if(mensagem == MSG_SYSKEYDOWN)
		{
			if(abnt2 == 1){
		        ch = map_abnt2[key];
			};

            //@todo acionar status. 
		};

		if(mensagem == MSG_KEYDOWN)
		{
			if(abnt2 == 1){
		        ch = map_abnt2[key];
			};

		    if(shift_status == 1 || capslock_status == 1){
			    ch = shift_abnt2[key];
			};

		    if(ctrl_status == 1){
			    ch = ctl_abnt2[key];
			};
            //Nothing.
		};
		//Nothing.
		goto done;
	};//fim do else

    //Nothing.

//Done.
done:

	/*
	 * Debug:
     *     No caso de modo texto.
	 *
	 * Coloca o scancode na tela
     * set_up_cursor(0,4);
	 * printf("       "); 	
     * set_up_cursor(0,4);
	 * printf("%d ",(unsigned char) (key & 0xff) );
     * Coloca o caractere na tela
	 * screen[76] = (char) ch;
	 * screen[77] = (char) 0x09;  //azul no preto
	 */


	//Debug:
	//Canto direito da primeira linha.
	//screen[76] = (char) ch;
	//screen[77] = (char) 0x09;    //Azul no preto.

	//
	// Control + Alt + Del.
	//

		//Opções:
		//@todo: Chamar a interface do sistema para reboot.
		//@todo: Opção chamar utilitário para gerenciador de tarefas.
		//@todo: Abre um desktop para operações com usuário, senha, logoff, gerenciador de tarefas.

		//Chamando o módulo /sm diretamente.
		//mas não é o driver de teclado que deve chamar o reboot.
		//o driver de teclado deve enviar o comando para o console, /sm,
		//e o console chama a rotina de reboot do teclado.
		//Uma mensagem de reboot pode ser enviada para o procedimento do sistema.
		//Pois o teclado envia mensagens e não trata as mensagens.
	
	    //Um driver não deve chamar rotinas de interface. como as rotians de serviço.	
		//A intenção é que essa mensagem chegue no procedimento do sistema.
		//Porem o sistema tambem deve saber quem está enviando esse pedido.@todo.
		//@todo: podemos O reboot pode ser feito através de um utilitário em user mode.
	if( (ctrl_status == 1) && (alt_status == 1) && (ch == KEY_DELETE) )
	{
		//Uma opção aqui, é enviar para o aplicativo uma mensagem de reboot.
		//como o aplicativo não trata esse tipo de mensagem ele apenas reecaminha 
		//para o procedimentod e janelas do sistema.
		services( SYS_REBOOT, 0, 0, 0);
	};

	
	//
	// ?? Dúvida: E se o aplicativo em user mode não tem janela,
	// para onde vai as mensagens de digitações que são recebidas 
	// pelas rotinas de input dos aplicativos ?? Onde as rotinas 
	// de input dos aplcativos de console pegam suas mensagens??
	// ?? Ou seja: ?? Qual é a janela que recebe mensagens quando 
	// o aplicativo que está rodando é um aplicativo de console??
	// >>> A solução seria enviar a mensagem para a janela de terminal
	// criada pelo kernel para o aplicativo de console... Desse modo 
	// até um aplicativo de console terá uma janela de associada a ele.
	// podendo enviar mensagens para ela, e receber mensagens através da
	// fila de mensagens da janela.
	// Obs: Quando um aplicativo de console recebe tempo de processamento,
	// sua janela pode ou não estar com o foco de entrada, pois aplicativos 
	// podem rodar em segundo plano, até mesmo minimizados.
	// ?? Pergunta: ?? como fazer então para enviar mensagens para janelas de 
	// aplicativos que estão rodando em segundo plano, sem o foco de entrada??
	// >> As mensagens que vem com o destinatário explicitado são mais fáceis de 
    // serem enviadas. Para isso podemos utilizar canais de mensagens que 
	// indiquem quem são as janelas do emissor e do receptor. 
	// No caso de mensagens enviadas entre processos, os processos serão 
	// os emossores e receptores da mensagem, nesse caso então a mensagem 
	// será enviada à janela principal do processo emissor. Para isso 
	// na estrutura de processo deve ter um ponteiro para a janela principal,
	// que será responsávem por receber as emnsagens no caso de uma comunicação entre 
	// processos... Até mesmo para os casos mais simples onde o kernel envia mensagens 
	// para  ajanela de um processo, poderíamos abrir um canal de comunicação, 
	// onde o processo kernel seria o emissor da mensagem.
	//
	//
	
	//
    // Obs: NÃO É ATRIBUIÇÃO DO DRIVER DE TECLADO SABER INFORMAÇÕES
    // SOBRE AS JANELAS, ENTÃO UM DRIVER DE TECLADO DEVE ENVIAR A
    // MENSAGEM PARA UM GERENCIADOR DE MENSAGENS QUE COLOCARÁ A MENSAGEM
    // EM SEU DEVIDO LUGAR. (Fila de mensagens da janela com o foco de entrada.)
    // o GERENTE DE JANELAS (window.c) ENCONTRA A JANELA COM O FOCO DE ENTRADA.
	// >>>> Um driver de teclado deve enviar a mensagem para um serviço do sistema
	// que decidirá o que fazer com ela. Não é responsabilidade do driver de teclado
	// encontrar o destino certo da mensagem, ele só precisa entregar ela pro
	//serviço de sistema responsável.
	//

	// 
    //>>>>isso é o que um driver deve fazer.. apenas solicitar o serviço.
	//
	
	//driver de teclado >> serviço do kernel >> classe do serviço.
	
	//Obs: um teclado virtual pode simular essas mensagens
	//apenas chamando essa rotina de serviços.
	
	
	//test. TEM QUE MOSTRAR PARA TERMINAR O DRIVER DE TECLADO.
	//printf("%c", ch);
	
	//Escrevendo na tela do desenvolvedor.
	//Isso será portado para outro módulo. está aqui para teste. 
	
	/*
	if( (void*) gui->DEVELOPERSCREEN == NULL)
	{
        printf("abnt2_keyboard_handler: gui->DEVELOPERSCREEN");	
        refresh_screen();
        while(1){}		
	}else{
		
		//Cursor.
		//g_cursor_x = gui->DEVELOPERSCREEN->cursor_x;
		//g_cursor_y = gui->DEVELOPERSCREEN->cursor_y;
		//printf("%c", ch);
		//@todo: Não está incrementando a escrita ...
	};
	*/
	
	//69 ??
	//Enviando mensagem pra janela com o foco de entrada.
	//#bugbug Error: O driver de teclado não deve saber qual é a janela com foco de 
	//entrada.. ele deve enviar essa mensagem para o kernel e o kernel 
	//decide quem é a janela com o foco de entrada e encameinha a mensagem para 
	//a fila da janela com o o foco de entrada.
	
	//services( 69, (unsigned long) mensagem, (unsigned long) ch, (unsigned long) ch);

	//
	// Obs: estamos enviando a messagem para 2 procedimentos,
	// mas o procedimento do sistema não trada digitações de teclas comuns. 
	// Obs: O que estamos fazendo aqui é chamarmos o procedimento de janela do sistema
	//e em seguida colocarmos a mensagem na fila da janela com o foco de entrada.
	// Obs: Uma opção seria não chamarmos o procedimento de janela do sistema agora e
	// e sim apenas colocarmos a mensagem na fila da janela com o foco de entrada.
	// Daí então, quando o aplicativo em user mode receber a mensagem, ele trata a 
	// a mensagem ou reencaminha para o procedimento de janela do sistema através de uma 
	// system call.
	// *Importante; Uma chamada ao procedimento de janela do sistema nesse momento,
	// so atrasa o recebimento da mensagem por parte do aplicativo em user mode.
    // bom seria que o aplicativo rebece a mensagem antes de chamar o procedimento de 
    // de janela para tratar as mensagens de sistema. Isso privilegia as teclas de digitação
	// em detrimento das teclas de acionamento de controles.
	//
	//
	
	//
	// ?? PORQUE O HANDLE DE JANELA É NULO AQUI ??
	//
	// DEVEMOS CHAMAR O PROCEDIMENTO DO SISTEMA PARA ATUAR EM ALGUMA JANELA.
	//
	
	
	//teste:
	// o procedimento de janela do sistema afetara a janela com o foco de entrada.
	
    //#bugbug : ?? o ldisc deveria ter essa informação toda sobre janelas ??
	struct window_d *wwf;
	wwf = (void *) windowList[window_with_focus];
	
	if( (void*) wwf != NULL ){
	    system_procedure( wwf, (int) mensagem, (unsigned long) ch, (unsigned long) ch );
    }					 
	
	
	//test
	//@todo: #bugbug Lembrando que um driver ainda não tem acesso abertos
	//a essa função... uma chada à essa função deve ser criada na API usada pelo driver.
	//windowSendMessage( (unsigned long) 0,
	//		           (unsigned long) mensagem, //msg
	//				   (unsigned long) ch,
	//				   (unsigned long) ch );
	

	//*Importante: se nenhuma janela tem o foco de entrada, não há porque 
	//enviar uma mensagem para a janela com o foco de entrada.
	
	
	/*
	 * Importante: Nesse caso podemos abrir um canal de comunicação,
	 * onde o kernel é o emissor da mensagem.
	 */
	
	struct window_d *w;
	
	w = (void*) windowList[window_with_focus];
	
	//Somente destituimos o foco se a janela for válida.
    //Isso envia uma mensagem para a janela com o foco de entrada.
	//se nenhuma janela tem o foco de entrada então apenas retorna.			
	if( (void*) w != NULL )
	{	    
		if( w->used == 1 && w->magic == 1234 ){
	        windowSendMessage( 0, mensagem, ch, ch);
		};			    	
	};		
	
    //
    // @todo: ENVIANDO A MENSAGEM PARA O GERENCIADOR DE MENSAGENS.
    //	

	/*
	 * Quem é o cliente?
	 * ================
	 *     O cliente é o processo que é o dono da janela com o
	 * foco de entrada.
	 *     Identificando a janela com o foco de entrada, sabemos
	 * quem é o processo cliente.
	 *  Obs: A janela com o foco de entrada nem sempre é a janela ativa,
	 * pode ser também uma janela filha da janela ativa.
	 * Mas até mesmo a janela filha de uma janela ativa está vinculada
	 * ao processo cliente.
	 */

    /*
	 * Sobre a fila de mensagem da janela com o foco de entrada:
     * ========================================================
     *  *IMPORTANTE: 
	 *      O que importa é qual janela está com o foco de entrada.
	 *      Quando sabemos qual janela está com o foco de entrada, então
	 * sabemos qual é a janela que é a área de cliente, sabemos e provavelmente
	 * a sua janela mãe é a janela ativa, se ela mesma não for a janela ativa.
	 *      Uma mensagem pode ser enviada para a janela com o foco de entrada,
	 * e a mensagem afetará apenas a janela com o foco de entrada.
	 *      Se a janela que receber a mensagem for a janela ativa, ela não
	 * terá janela mãe, nessa caso uma mensagem para fechar uma janela ativa
	 * implica em fechar o processo ao qual ela está vinculada.
	 *      Não importa qual processo foi interrompida pela interrupção de 
	 * teclado. A mensagem deve ir para a fila de mensagens da janela com o foco
	 * de entrada.
	 */


	/*
	 * Sobre a escolha do procedimento de janela:
	 * =========================================
     * Procedimento de janela.
	 *     Se o próximo procedimento for o procedimento do sistema
	 *     dispacha para ele.
	 *     Chama o próximo procedimento, passando os argumentos pra ele.
	 *     *IMPORTANTE: É importante saber qual é a janela ativa
	 *     pra enviar a mensagem para o procedimento de janela certo
	 *     e enviar todos os 4 parametros.
     */




    //
	// @todo:
	// Obs: Aqui estamos enviando diretamente para um procedimento de janela,
 	//     mas o certo é colocar na fila da janela com o foco de entrada.    
	//

	//Se for o procedimento padrão. 
	//if( g_next_proc == (unsigned long) &system_procedure )
	//{
	//	//@todo: Aqui janela tem que ser NULL.
	//	system_procedure( NULL, (int) mensagem, (unsigned long) ch, 0);
	//    //goto eoi;
	//};

	//Se NÃO for o procedimento padrão. 
	//if( g_next_proc != (unsigned long) &system_procedure )
	//{

		//
		// @todo: 
		// Na verdade, aqui tem que mandar a mensage para a janela com o foco 
		// de entrada, mesmo que seja uma janela filha.
		// 

	//	wFocus = (void *) WindowWithFocus;
	//	CurrentWindow = (void *) WindowWithFocus;

		//
		// A janela atual, seria a janela ativa ?
		//

		//
		// Estamos apenas enviando para a janela com foco de entrada.
		//

    //    if( (void*) wFocus == NULL ){			
    //        system_dispatch_to_procedure( NULL, (int) mensagem, (unsigned long) ch, 0);
	//	}else{

			//Valida a estrutura da janela com o foco de entrada.
	//		if( wFocus->used == 1 && wFocus->magic == 1234 )
	//		{		
				//Estamos enviando a mensagem para a estrutura da janela 
				//com o foco de entrada.
	//			wFocus->msg_window = (void*) wFocus;
	//			wFocus->msg = (int)	mensagem;
	//			wFocus->long1 = (unsigned long) ch;
	//			wFocus->long2 = (unsigned long)0;  //Ainda não implementada.

				//...

				//@todo: Precisamos identificar que é a janela mãe
				//e qual é processo ao qual essa janela está vinvulada.

	//		} 	

	//		system_dispatch_to_procedure( wFocus, (int) mensagem, (unsigned long) ch, 0);
	//	}

		//Nothing.

		//goto eoi;
	//};


	/*
	 * IPC stuffs
	 * enviando para uma area de memoria compartilhada.
	 * ipc_dispatch_message( WindowProcedure->window,
			                 WindowProcedure->msg,
							 WindowProcedure->long1,
							 WindowProcedure->long2 );
	 */

eoi:
    outportb(0x20, 0x20);    //EOI.
    return;
};


/*
 * KdGetWindowPointer:
 *     Retorna o ponteiro da estrutura de janela que pertence a thread.
 *     Dado o id de uma thread, retorna o ponteiro de estrutura da janela 
 * à qual a thread pertence.
 */
void *KdGetWindowPointer(int tid)
{
	struct thread_d *t;

	//@todo: filtrar argumento. Mudar para tid.
	//if(thread_id<0){}

	// Structure.
	t = (void*) threadList[tid];

	if( (void*) t == NULL ){
        return NULL;        //@todo: fail;
	};
// Done.
done:
	return (void*) t->window;
};


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
 *
 */
int KbGetMessage(int tid)
{   
	int ret_val;
	struct thread_d *t;
	
	//
	// Structure.
	t = (void*) threadList[tid];

	if( (void*) t != NULL ){
        ret_val = (int) t->msg;
	}else{
	    ret_val = (int) -1;    //Fail.
	};

// Done.
done:
	WindowProcedure->msgStatus = 0;    //Muda o status.
	return (int) ret_val;              //Retorna a mensagem.
};


/*
 * KbGetLongParam1:
 *    Pega o parametro "long1" do procedimento de janela de uma thread.
 */
unsigned long KbGetLongParam1(int tid)
{   	
	struct thread_d *t;
	
	// Structure.
	t = (void*) threadList[tid];

	if( (void*) t == NULL){
        return (unsigned long) 0;    //@todo: fail;
	};

// Done.
done:
    return (unsigned long) t->long1;
};

/*
 * KbGetLongParam2:
 *     Pega o parametro "long2" do procedimento de janela de uma thread.
 */
unsigned long KbGetLongParam2(int tid)
{
	struct thread_d *t;
	
	// Structure.
	t = (void*) threadList[tid];

	if( (void*) t == NULL){
        return (unsigned long) 0;    //@todo: fail;
	};

// Done.
done:
    return (unsigned long) t->long2;
};


/*
 * reboot: 
 *     Reboot system via keyboard port.
 *
 * *IMPORTANTE: a interface fechou o que tinha qe fechar,
 * hal chamou essa hotina para efetuar a parte de hardware reboot apenas.
 * @todo: Atribuições.
 *
 * Atribuições: 
 *     + Desabilitar as interrupções.
 *     + Salvar registros.
 *     + Salvar programas abertos e não salvos.
 *     + Fechar todas tarefas antes.
 *     + Efetuar o tipo de reboot especificado.
 *    + Outras ...
 *
 */
void reboot()
{
    //
    //@todo: 
	// +criar uma variavel global que especifique o tipo de reboot.
    // +criar um switch para efetuar os tipos de reboot.
	// +criar rota de fuga para reboot abortado.
	// +Identificar o uso da gui antes de apagar a tela.
	//  modo grafico ou modo texto.
	//
	
	//
	// Video.
	//
	

	
	/*
	sleep(2000);
	//kclear(9);
    set_up_cursor(0,0);	
    set_up_text_color(0x0f, 0x09);
	printf("\n\n REBOOTING ...\n\n");


	//
	// Scheduler stuffs.
	//
	
	sleep(1000);
	printf("locking scheduler ...\n");
	scheduler_lock();
	
	//
	// Tasks.
	//
	
	//@todo: fazer função com while. semelhante ao dead task collector.
	
	sleep(1000);
	printf("killing tasks ...\n");
	//kill_thread(current_task); 
	
	//
	// Final message.
	//
	
	sleep(1000);
	printf("turning off ...\n");
    
	
	refresh_screen();
	
	//
	// Interruoções.
	//
	
	sleep(7000);
	asm("cli");
	
	*/
	
	
	// @todo: disable();
	
//
// Done.
//

done:
    //Obs o driver de teclado não chama o assembly do kernel,
	//na verdade o driver de teclado nem fará parte do kernel base.
	//apenas algumas rotinas ficarão aqui.
    hal_reboot();
	
    //asm_reboot(); 
	
	//asm("hlt");
	//while(1){};
	
	//	
	// No return!
	//
};


//Get alt Status.
int get_alt_status(){
    return (int) alt_status;
};

//Get control status.
int get_ctrl_status(){
    return (int) ctrl_status;
};

 

int get_shift_status(){
    return (int) shift_status;	
}
 



/*
 * init_keyboard:
 *     Inicializa o driver de teclado.
 */
 
// void keyboardInit()
 
void init_keyboard()
{
    //int Type = 0;

    //
    // @todo: 
	//     Checar se o teclado é do tipo abnt2.   
	//     É necessário sondar parâmetros de hardware,
	//     como fabricante, modelo para configirar estruturas 
	//     e variáveis.
	//


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
	//
	// Set abnt2.
	//

	abnt2 = (int) 1;

    //Checar quem está tentando inicializar o módulo.    

	//model.
	
	//handler.
	
	//...

    //Key status.
	key_status = 0;
    escape_status = 0;
    tab_status = 0;
    winkey_status = 0;
    ctrl_status = 0;
    alt_status = 0;
    shift_status = 0;
	capslock_status = 0;
	numlock_status = 0;
	//...

	//AE    Enable Keyboard Interface: clears Bit 4 of command register
	//      enabling keyboard interface.
	kbdc_wait(1);
	outportb(0x64,0xAE);   // Activar a primeira porta PS/2

	//Leds.
	//LED_SCROLLLOCK 
	//LED_NUMLOCK 
	//LED_CAPSLOCK  	
	keyboard_set_leds(LED_NUMLOCK);
	
	//...
	
	
	//Debug support.
	scStatus = 0;

done:
    g_driver_keyboard_initialized = (int) 1;
    return;
};


/*
 * Constructor.
int keyboardKeyboard(){
	;
};
*/


/*
 obs: definido acima.
int keyboardInit(){
	;
};
*/


//
// ********************** mouse ************************
//

// ??? estraanho
//??? usado pelo mouse
#define outanyb(p) __asm__ __volatile__(\
		"outb %%al,%0"::"dN"((p)) :"eax"\
		)  /* Valeu Fred */
		

/*
 * init_mouse:
 *     Inicializando o mouse no controlador 8042.
 */		
int init_mouse()
{
    unsigned char response = 0;
    unsigned char deviceId = 0;
    int i;
    
	int bruto = 1;
	
	mousemsg = ( unsigned char *) malloc(32);
	
    mouse_status = 0;
    delta_x = 0;
    delta_y = 0;
    count_mouse = 0;
	
	
	//configurar ps2 antes de tudo.
    //P8042_install(); //@todo: deletar .. isso foi chamado em hal.c
	
	
    // Talk to the keyboard controller a little bit to initialize the mouse
   
   /*
    Wait for ACK from Mouse:
    It is required to wait until the mouse sends back the 0xFA acknowledgement byte 
    after each command or data byte before sending the next byte 
    (Note: reset commands might not be ACK'ed -- wait for the 0xAA after a reset). 
    A few commands require an additional data byte, and both bytes will generate an ACK.	
   */	
	
	//printf("Initializing mouse ...\n");
    MessageBox(gui->screen, 1, "init_mouse:","initializing!");

	
	if(bruto == 1)
	{
        //modo bruto
	    mouse_write(0xFF);
	    mouse_write(0xF6); 
	    mouse_write(0xF4); 
        while(1)	
	    {
	        response = (unsigned char) mouse_read();	
	        if(response != 0xFA){
			    //goto InterruptStuff;
                goto done;				
		    }
            //Nothing.		
	    };
        //nothing.		
	};
	
	
	
/*	
//Disable Packet Streaming	The mouse stops sending automatic packets.
Disabledatareporting:
	printf("Disable data reporting ...\n");
	refresh_screen();
    mouse_write(0xF5);
    while(1)	
	{
	    response = (unsigned char) mouse_read();	
	    if (response != 0xFA){
			goto reset;
		}
        //Nothing.		
	};	
	
*/
	
/*	
//Reset	The mouse probably sends ACK (0xFA) plus several more bytes, then resets itself, and always sends 0xAA.	
reset:
	printf("reseting ...\n");
    refresh_screen();
    mouse_write(0xFF);
	while(1)	
	{
	    response = (unsigned char) mouse_read();	
	    if (response != 0xAA){
			goto SetDefaults;
		}
        //Nothing.		
	};
*/
 
/* 
//Set Defaults	Disables streaming, sets the packet rate to 100 per second, and resolution to 4 pixels per mm. 
SetDefaults:
	printf("set defaults ...\n"); 
    refresh_screen();
	mouse_write(0xF6); 
	while(1)	
	{
	    response = (unsigned char) mouse_read();	
	    if (response != 0xFA){
			goto EnablePacketStreaming;
		}
        //Nothing.		
	};
*/

/* 
//Enable Packet Streaming	The mouse starts sending automatic packets when the mouse moves or is clicked. 
EnablePacketStreaming:
	printf("enable streaming...\n");
    refresh_screen();
	mouse_write(0xF4); 
    while(1)	
	{
	    response = (unsigned char) mouse_read();	
	    if (response != 0xFA){
			goto InterruptStuff;
		}
        //Nothing.		
	};
*/ 

/**
//?? 
// Disable the mouse line
//Disablethemouseline:
//    outPort64(0xA7);
  

//??  
// Enable the mouse line
//    outPort64(0xA8);
 **/    

 
/**
// Get the device ID.  0x00 for normal PS/2 mouse
deviceId = inPort60();
**/
 
/**
// Set scaling to 2:1
mouse_write(0xE7);
**/

    //
	//  ?? Interrupt ??
	//
	
/*	
//you need to enable the aux port to generate IRQ12. 
//You need to send the command byte 0x20 ("Get Compaq Status Byte") to the PS2 controller on port 0x64.
// This command does not generate a 0xFA ACK byte.
//The very next byte returned should be the Status byte.
//After you get the Status byte, 
// you need to set bit number 1 (value=2, Enable IRQ12), and 
//clear bit number 5 (value=0x20, Disable Mouse Clock).
// Then send command byte 0x60 ("Set Compaq Status") to port 0x64,
//followed by the modified Status byte to port 0x60.
//This might generate a 0xFA ACK byte from the keyboard.
//
InterruptStuff:
	printf(" enable the aux port to generate IRQ12 (Compaq stuff) ...\n");
    refresh_screen();
    // Tell the controller to issue mouse interrupts
    outPort64(0x20);
    response = inPort60();
    response |= 0x02;     //Enable IRQ12
	//response |= 0x22;  //teste.?? Disable Mouse Clock
    outPort64(0x60); 
    outPort60(response);
    while(1)	
	{
	    response = (unsigned char) mouse_read();	
	    if (response != 0xFA){
			goto done;
		}
        //Nothing.		
	};
*/


done:

    // Reabilitando as duas portas.
	
	kbdc_wait(1);
	outportb(0x64,0xAE);   // Activar a primeira porta PS/2

	kbdc_wait(1);
	outportb(0x64,0xA8);  // activar a segunda porta PS/2
	
  //initialized = 1;
  //return (kernelDriverRegister(mouseDriver, &defaultMouseDriver));
    MessageBox(gui->screen, 1, "init_mouse:","Mouse initialized!");    	
	return (int) 0;
};

/*
 * mouse_write:
 *     Envia um byte para a porta 0x60.
 *     (Nelson Cole) 
 */
void mouse_write(unsigned char write)
{
	kbdc_wait(1);
	outportb(0x64,0xD4);
	kbdc_wait(1);
	outportb(0x60,write);
};


/*
 * mouse_read:
 *     Pega um byte na porta 0x60.
 *     (Nelson Cole) 
 */
unsigned char mouse_read()
{
	kbdc_wait(0);
	return inportb(0x60);

};


/*
 * kbdc_wait:
 *     Espera por flag de autorização para ler ou escrever.
 *     (Nelson Cole) 
 */
void kbdc_wait(unsigned char type)
{
	if(type==0)
	{
        while(!inportb(0x64)&1)outanyb(0x80);
    }
    else 
	{
        while(inportb(0x64)&2)outanyb(0x80);
	};
};


/*
 * mouseHandler:
 *     handler de teclado. A _irq0 chama essa rotina.
 *     *Importante: Se estamos aqui é porque os dados disponíveis
 * no controlador 8042 pertencem ao mouse.
 */
void mouseHandler()
{
    
	buffer_mouse[count_mouse++] = mouse_read();
	
	if( count_mouse >= 3 )
	{
        mouse_status = buffer_mouse[0];
        
		delta_x = buffer_mouse[1];
	    delta_y = buffer_mouse[2];
		
        //printf("ocorreram 3 irq12 !\n");
        //kernelPS2MouseDriverReadData(); //bugbug
		printf("mouseStatus={%d} deltaX={%d} deltaY={%d} \n",mouse_status,delta_x,delta_y);
		refresh_screen();
		
	    //printf("#"); //teste
	    //MessageBox(gui->screen, 1, "mouseHandler:","Testing Mouse interrupt");
	    //kernelPS2MouseDriverReadData();
		
		count_mouse=0;
    };
	//return;
};



static unsigned char inPort60(void)
{
  // Input a value from the keyboard controller's data port, after checking
  // to make sure that there's some data there for us

  unsigned char data = 0;

  while (!(data & 0x01))
    kernelProcessorInPort8(0x64, data);

  kernelProcessorInPort8(0x60, data);
  return (data);
}


static void outPort60(unsigned char value)
{
  // Output a value to the keyboard controller's data port, after checking
  // to make sure it's ready for the data

  unsigned char data;
  
  // Wait for the controller to be ready
  data = 0x02;
  while (data & 0x02)
    kernelProcessorInPort8(0x64, data);
  
  data = value;
  kernelProcessorOutPort8(0x60, data);
  return;
}


static void outPort64(unsigned char value)
{
  // Output a value to the keyboard controller's command port, after checking
  // to make sure it's ready for the command

  unsigned char data;
  
  // Wait for the controller to be ready
  data = 0x02;
  while (data & 0x02)
    kernelProcessorInPort8(0x64, data);

  data = value;
  kernelProcessorOutPort8(0x64, data);
  return;
};


/*
 * getMouseData:
 *     Essa função é usada pela rotina kernelPS2MouseDriverReadData.
 */
static unsigned char getMouseData(void)
{
  // Input a value from the keyboard controller's data port, after checking
  // to make sure that there's some mouse data there for us

  unsigned char data = 0;

  while ((data & 0x21) != 0x21)
    kernelProcessorInPort8(0x64, data);

  kernelProcessorInPort8(0x60, data);
  return (data);
}



/*
 * kernelPS2MouseDriverReadData:  
 *     Pega os bytes e salva em um array.
 *     Exibe um caractere na tela, dado as cordenadas.
 *     @todo: Rever as entradas no array.
 *         
 */
void kernelPS2MouseDriverReadData(void)
{
    // This gets called whenever there is a mouse interrupt

    

    static volatile int button1, button2, button3;
    unsigned char byte1 = 0, byte2 = 0, byte3 = 0;
    int xChange, yChange;
	
	mousemsg[9] = 0; //zera o sestatdo do mouse 

    // Disable keyboard output here, because our data reads are not atomic
    outPort64(0xAD);

    // The first byte contains button information and sign information
    // for the next two bytes
    //byte1 = getMouseData();
    byte1 = mouse_status;
	
    // The change in X position
    //byte2 = getMouseData();
    byte2 = delta_x;
	
    // The change in Y position
    //byte3 = getMouseData();
    byte3 = delta_y;
	
    // Re-enable keyboard output
    outPort64(0xAE);

    if ((byte1 & 0x01) != button1)
    {
        // kernelMouseButtonChange(1, button1 = (byte1 & 0x01));
        mousemsg[2] = 1;
        mousemsg[9] = MSG_MOUSEKEYDOWN; // clicado ou nao
        return;
    }else if((byte1 & 0x04) != button2)
          {
              //  kernelMouseButtonChange(2, button2 = (byte1 & 0x04));
              mousemsg[2]= 2;
              mousemsg[9] = MSG_MOUSEKEYDOWN; // clicado ou nao                                      
              return;
          }else if((byte1 & 0x02) != button3)
                {
                    //  kernelMouseButtonChange(3, button3 = (byte1 & 0x02));
                    mousemsg[2]= 3;
                    mousemsg[9] = MSG_MOUSEKEYDOWN; // clicado ou nao                                      
                    return;
                }
				else
				{
                    
					// Sign them
                    if(byte1 & 0x10){
	                    xChange = (int) ((256 - byte2) * -1);
                    }else{ xChange = (int) byte2; 
					};

                    if (byte1 & 0x20){
                        yChange = (int) (256 - byte3);
                    }else{
                	    yChange = (int) (byte3 * -1);
                    };

                    //  char_blt(xChange * 8,yChange * 8,55,'A'); 
                    //  kernelMouseMove(xChange, yChange);
                    //  mousemove(xChange, yChange);
                    
					my_buffer_char_blt( xChange, yChange, COLOR_PINK, 'T');
					
					mousemsg[0]= xChange;
                    mousemsg[1]= yChange;
                };
  return;
}


/* 
 * P8042_install:
 *     Configurando o controlador PS/2, 
 *     e activar a segunda porta PS/2 (mouse).
 *     (Nelson Cole)
 */
void P8042_install()
{
	
	unsigned char status;


/* Desativar dispositivos PS/2 , isto envita que os dispositivos PS/2 envie dados no momento da configuração.
 */

  	kbdc_wait(1);
	outportb(0x64,0xAD);  // Desativar a primeira porta PS/2
	kbdc_wait(1);
	outportb(0x64,0xA7);  /* Desativar a segunda porta PS/2, hahaha por default ela já vem desativada, só para constar */

	kbdc_wait(1);    
	outportb(0x64,0x20);     // defina a leitura do byte actual de configuração do controlador PS/2

	kbdc_wait(0);
	status=inportb(0x60)|2;  /* Activar o segundo despositivo PS/2, modificando o status de configuração do controlador PS/2. 
				Lembrando que o bit 1 é o responsável por habilitar, desabilitar o segundo despositivo PS/2  ( o rato). Só 					para constar se vedes aqui fizemos duas coisas lemos ao mesmo tempo modificamos o byte 
				de configuração do controlador PS/2 
			     */

	
	kbdc_wait(1);
	outportb(0x64,0x60);  // defina, a escrita  de byte de configuração do controlador PS/2

	
	kbdc_wait(1);
	outportb(0x60,status);  // devolvemos o byte de configuração modificado

	// Agora temos dois dispositivos sereais teclado e mouse (PS/2).
	


	kbdc_wait(1);
	outportb(0x64,0xAE);   // Activar a primeira porta PS/2

	kbdc_wait(1);
	outportb(0x64,0xA8);  // activar a segunda porta PS/2

     kbdc_wait(1); //espera 

/* NOTA. Esta configuração discata do teste do controlador PS/2 e de seus dispositivos. Depois façamos a configuração decente e minuciosa do P8042.
 
*/

}

//
// End.
//

