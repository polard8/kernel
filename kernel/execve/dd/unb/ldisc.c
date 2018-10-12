/*
 * File: unb\ldisc.c
 *
 * Descrição:
 *    Esse será o gerenciador de Line Discipline.
 *    Ficará dentro do kernel base e receberá as entradas 
 * dos dispositivos de caractere e enviará para as filas apropriadas.
 *    Por enquanto os scancodes de teclado são tratados e enviados 
 * para a fila de mensagem da janela apropriada. Principalmente a janela 
 * com o foco de entrada. 
 *
 */


#include <kernel.h>


 
//=======================================================
//++ Usadas pelo mouse.
// hardwarelib.inc
//
#define MOUSE_X_SIGN	0x10
#define MOUSE_Y_SIGN	0x20

//Coordenadas do cursor.
extern int mouse_x;
extern int mouse_y;

//Bytes do controlador.
extern char mouse_packet_data;
extern char mouse_packet_x;
extern char mouse_packet_y;
//extern char mouse_packet_scroll;
 
extern void update_mouse();


//Estado dos botões do mouse
int mouse_buttom_1; 
int mouse_buttom_2;
int mouse_buttom_3;

//Estado anterior dos botões do mouse.
int old_mouse_buttom_1; 
int old_mouse_buttom_2;
int old_mouse_buttom_3;

//se ouve alguma modificação no estado 
//dos botões.
int mouse_button_action;

//--
//=========================================================



//?? usado pelo mouse
#define outanyb(p) __asm__ __volatile__( "outb %%al,%0" : : "dN"((p)) : "eax" )


//
// Imported functions.
//

//
// Definições para uso interno do módulo.
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


//issso pertence à inicialização do teclado. deve ficar no driver de teclado.
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
//variáveis usadas pelo line discipline para controlar o estado das teclas de controle.
unsigned long key_status;
unsigned long escape_status;
unsigned long tab_status;
unsigned long winkey_status;  // >> Winkey shotcuts. #super
unsigned long ctrl_status;
unsigned long alt_status;
unsigned long shift_status;
unsigned long capslock_status;
unsigned long numlock_status;
unsigned long scrolllock_status;
//...

//
// ** kernel Winkey shotcuts **
//

/*
 WINKEY+
 ...
 */

//
// Mouse support
//

//bytes do controlador.
char mouse_status;
char delta_x;
char delta_y;

//coordenadas.
int mouse_pos_x;
int mouse_pos_y;


//unsigned char *mousemsg;


//@todo: fazer rotina de get status algumas dessas variáveis.


//Se há uma nova mensagem de teclado. 
int kbMsgStatus;



//
// keyboardMessage
//     Estrutura interna para mensagens.
//
struct keyboardMessage 
{
    unsigned char scancode;

    //??
    //@todo: Na verdade todo driver usará estrutura de janela descrita na API 
    //que o driver use.

    //? hwnd;  
    int message;
    unsigned long long1;
    unsigned long long2;
};


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

	//Nothing.

    return (unsigned long) State;		
};


/*
 * keyboardEnable:
 *     Enable keyboard.
 */
void keyboardEnable (){
	
	//Wait for bit 1 of status reg to be zero.
    
	while ( (inportb(0x64) & 2) != 0 )
	{
		//Nothing.
	};
	
	//Send code for setting Enable command.
    outportb(0x60,0xF4);
    //sleep(100);
};


/*
 * keyboardDisable:
 *     Disable keyboard.
 */
void keyboardDisable (){
	
	//Wait for bit 1 of status reg to be zero.
    
	while ( (inportb(0x64) & 2) != 0 )
	{
		//Nothing.
	};
	
	//Send code for setting disable command.
    outportb(0x60,0xF5);
    //sleep(100);
};


/*
 * keyboard_set_leds:
 *     Set keyboard flags.
 *     ED = Set led.
 */
void keyboard_set_leds (char flag){
	
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
	
	//@todo mudar o status.
    //switch(flag)
    //{
		
	//}	
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
 ***************
 * LINE DISCIPLINE
 * Funciona como um filtro.
 * Obs: Essa é a rotina principal desse arquivo, 
 * todo o resto poderá encontrar um lugar melhor.
 *
 */
 
int LINE_DISCIPLINE ( unsigned char SC, int type ){
	
    //
    // Step 0 - Declarações de variáveis.
    //

    //Variáveis para tecla digitada.
    unsigned char scancode;
    unsigned char key;         //Tecla (uma parte do scancode).  
    unsigned long mensagem;    //arg2.	
    unsigned long ch;          //arg3 - (O caractere convertido para ascii).
    unsigned long status;      //arg4.  

    // Text mode support.
	// Tela para debug em RING 0.
    // unsigned char *screen = (unsigned char *) 0x000B8000;   
    //unsigned char *screen = (unsigned char *) SCREEN_START;    //Virtual.   
    //...
	
	//Window.
    struct window_d *wFocus;	


    //
    // Step1 - Pegar o scancode.
    //

    //O driver pegou o scancode e passou para a disciplina de linha 
    //através de parâmetro.	
	scancode = SC;
	

	//Obs: Observe que daqui pra frente todas as rotinas poderiam estar
	//     em user mode.


	//Debug stuff.
    //Show the scancode if the flag is enabled.	
	if (scStatus == 1){
	    printf("{%d,%x}\n",scancode,scancode);
	};
	
	
    //
    // Step 2 - Tratar as mensagens.
    //

    //Se a tecla for (liberada).
	//Dá '0' se o bit de paridade for '0'.
    if( (scancode & LDISC_KEY_RELEASED) == 0 )
	{
	    key = scancode;
		key &= LDISC_KEY_MASK;    //Desativando o bit de paridade caso esteja ligado.

		//Configurando se é do sistema ou não.
		//@todo: Aqui podemos chamar uma rotina interna que faça essa checagem.
		switch(key)
		{
			//Os primeiros 'case' é quando libera tecla do sistema.
			//O case 'default' é pra quando libera tecla que não é do sistema.
			
			//left Shift liberado.
			case VK_LSHIFT:
				shift_status = 0;
				mensagem = MSG_SYSKEYUP;
			    break;

			//Left Control liberado.			
			case VK_LCONTROL:
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
			
			//right winkey liberada.
			case VK_RWIN:
			    winkey_status = 0;
                mensagem = MSG_SYSKEYUP;
				break;

			//control menu.
			case VK_CONTROL_MENU:
			    //controlmenu_status = 0; //@todo
			    mensagem = MSG_SYSKEYUP;
			    break;

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
		};

		//Analiza: Se for tecla normal, pega o mapa de caracteres apropriado.
		if(mensagem == MSG_KEYUP)
		{
		    //checar os mudificadores para maiúscula.
		    //if(shift_status == 1 || capslock_status == 1)
			//{	
			//    ch = shift_abnt2[key];	
			//	goto done;
			//};
			
			//minúscula
			//Nenhuma tecla de modificação ligada.
			ch = map_abnt2[key];
			goto done;
			
            //Nothing.
		};
        //Nothing.
		goto done;
	};
	
	// * Tecla (pressionada) ...........	
	if( (scancode & LDISC_KEY_RELEASED) != 0 )
	{ 
		key = scancode;
		key &= LDISC_KEY_MASK; //Desativando o bit de paridade caso esteja ligado.

		//O Último bit é zero para key press.
		//Checando se é a tecla pressionada é o sistema ou não.
		//@todo: Aqui podemos chamar uma rotina interna que faça essa checagem.
		switch(key)
		{
			//back space será tratado como tecla normal
			
			//@todo: tab,
            //?? tab será tratado como tecla normal por enquanto.
			
			//caps lock keydown
			case VK_CAPITAL:
			    //muda o status do capslock não importa o anterior.
				if(capslock_status == 0){ 
				    capslock_status = 1; 
					mensagem = MSG_SYSKEYDOWN; 
					break; 
				};
				if(capslock_status == 1){ 
				    capslock_status = 0; 
					mensagem = MSG_SYSKEYDOWN; 
					break; 
				};
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
				if(numlock_status == 0){
		            numlock_status = 1;
					mensagem = MSG_SYSKEYDOWN;
					break;
				};
				if(numlock_status == 1){ 
				    numlock_status = 0;
                    mensagem = MSG_SYSKEYDOWN; 					
					break; 
				};
			    break;
				
			//Scroll Lock.	
		    case VK_SCROLL:
			    //muda o status do numlock não importa o anterior.
				if(scrolllock_status == 0){
		            scrolllock_status = 1;
					mensagem = MSG_SYSKEYDOWN;
					break;
				};
				if(scrolllock_status == 1){ 
				    scrolllock_status = 0;
                    mensagem = MSG_SYSKEYDOWN; 					
					break; 
				};
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
			//uma tecla do sistema foi pressionada.
            //poderiamos ter opções dependendo do status das modificadoras.
			ch = map_abnt2[key];
            goto done;
		};

		if(mensagem == MSG_KEYDOWN)
		{
			//uma tecla normal foi pressionada.
			//mensagem de diitação.
			
			//Se os shift o capslock estiverem acionado ela vira maiúscula.
		    //if(shift_status == 1 || capslock_status == 1)
			//{
			//    ch = shift_abnt2[key];
			//    goto done;
			//};

			//minúsculas.
		    ch = map_abnt2[key];
			goto done;
			
            //Nothing.
		};
		//Nothing.
		goto done;
	};//fim do else

    //Nothing.
	
	// Para finalizar, vamos enviar a mensagem para fila certa.
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
			
	
		//Uma opção aqui, é enviar para o aplicativo uma mensagem de reboot.
		//como o aplicativo não trata esse tipo de mensagem ele apenas reecaminha 
		//para o procedimentod e janelas do sistema.
	
	if( (ctrl_status == 1) && (alt_status == 1) && (ch == KEY_DELETE) ){
		services( SYS_REBOOT, 0, 0, 0);
		//system_procedure ...
		// @todo: Chamar o aplicativo REBOOT.BIN.
	};

	
	//
	// Nesse momento temos duas opções:
	// Devemos saber se a janela com o foco de entrada é um terminal ou não ...
	// se ela for um terminal chamaremos o porcedimento de janelas de terminal 
	// se ela não for um terminal chamaremos o procedimento de janela de edit box. 
	// que é o procedimento de janela do sistema.
	// *IMPORTANTE: ENQUANTO O PROCEDIMENTO DE JANELA DO SISTEMA TIVER ATIVO,
	// MUITOS COMANDOS NÃO VÃO FUNCIONAR ATE QUE SAIAMOS DO MODO TERMINAL.
	//
	//
	
		//
		// *importante:
		// Passamos a mensagem de teclado para o procedimento de janela do sistema.
		// que deverá passar chamar o procedimento de janela da janela com o focod eentrada.
		//
		
		//
		// *importante:
		// Quem é o 'first responder' para evento de teclado.
		// A janela com o foco de entrada é o first responder para 
		// eventos de teclado, mas não para todo tipo de envento.		
		//
	
	
    //
	// #importante
	// Ok. A ideia agora é enviar a mensagem para a fila de mensagens do sistema.
	//
	
	// Envia as mensagens para os aplicativos intercepta-las
	// so mandamos mensagem para um aplicativo no estavo válido.	

	
	// Apenas checando a validade da janela com o foco de entrada.
	// Janela com o foco de entrada. (first responder ??)
	
	struct window_d *w;    
	w = (void *) windowList[window_with_focus];
	
	if ( (void *) w == NULL )
	{
		printf("LINE_DISCIPLINE: w");
		die();
		
	}else{
		
		if ( w->used != 1 || w->magic != 1234 )
		{
			printf("LINE_DISCIPLINE: w magic");
			die();
		}
		
		// Aqui temos uma janela válida.
		// Vamos enviar a mensagem para ela.
		
        windowSendMessage( (unsigned long) w, (unsigned long) mensagem, 
		    (unsigned long) ch, (unsigned long) ch );
	};
	
 
	//
	// ## Test ##
	//
 
    //Estamos chamado o procedimento de janelas do kernel 
	//para todos os casos. Mas isso deve ser um procedimento chamado pelo 
	//aplicativo depois que ele trata as mensagens que quer.
		
	//Chamando o procedimento de janelas do sistema.
	//Talvez isso seja apenas por enquanto...
	//O motivo disso é para no caso de erro do mecanismo de fila
	//tenhamos ainda algum evento de teclado sendo tratado pelo 
	//procedimento do sistema.
	//O procedimento de janelas do sistema vai tratar poucas teclas.
	//Obs: #importante. Isso talvez deva ser chamado depois do 
	//procedimento de janelas do aplicativo. Ou seja, chamado em user mode.
	
	// sm\sys\proc.c
	
	
	//o procedimento tratará as mensagens de sistema, colocará o cham no 
	//stdin e imprimirá o char na tela.
	system_procedure(  w, (int) mensagem, 
		(unsigned long) ch, (unsigned long) ch ); 
 
	//?? porque -1.
    return (int) -1;
};


/*
 * KdGetWindowPointer:
 *     Retorna o ponteiro da estrutura de janela que pertence a thread.
 *     Dado o id de uma thread, retorna o ponteiro de estrutura da janela 
 * à qual a thread pertence.
 */
void *KdGetWindowPointer (int tid){
	
	struct thread_d *t;

	//@todo: filtrar argumento. 
	
	if ( tid < 0 )
        return NULL;
        
		
	// Structure.
	t = (void *) threadList[tid];

	if ( (void *) t == NULL )
	{
        return NULL;        
	};
	
	return (void *) t->window;
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
 */
int KbGetMessage (int tid){
	
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

// Done.
//done:

	WindowProcedure->msgStatus = 0;    //Muda o status.
	return (int) ret_val;              //Retorna a mensagem.
};


/*
 * KbGetLongParam1:
 *    Pega o parametro "long1" do procedimento de janela de uma thread.
 */
unsigned long KbGetLongParam1 (int tid){
   	
	struct thread_d *t;
	
	// Structure.
	t = (void *) threadList[tid];

	if ( (void *) t == NULL)
	{
        return (unsigned long) 0;    //@todo: fail;
	};

// Done.
//done:
    return (unsigned long) t->long1;
};

/*
 * KbGetLongParam2:
 *     Pega o parametro "long2" do procedimento de janela de uma thread.
 */
unsigned long KbGetLongParam2 (int tid){
	
	struct thread_d *t;
	
	// Structure.
	t = (void *) threadList[tid];

	if ( (void *) t == NULL)
	{
        return (unsigned long) 0;    //@todo: fail;
	};

// Done.
//done:
    return (unsigned long) t->long2;
};


/*
 * reboot: 
 *     @todo: essa rotina poderá ter seu próprio arquivo.
 *     Reboot system via keyboard port.
 *     ?? #bugbug Por que o reboot está aqui ??
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
 */
void reboot (){
    
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

//done:

    hal_reboot ();
	die ();
};


//Get alt Status.
int get_alt_status (){
	
    return (int) alt_status;
};


//Get control status.
int get_ctrl_status (){
	
    return (int) ctrl_status;
};

 
int get_shift_status (){
	
    return (int) shift_status;	
};
 

/*
 * init_keyboard:
 *     ??
 *     Inicializa o driver de teclado.
 *
 *  @todo: enviar para o driver de teclado o que for de lá.
 *         criar a variável keyboard_type ;;; ABNT2 
 */
// void keyboardInit()
void init_keyboard (){
	
	//user.h
	ioControl_keyboard = (struct ioControl_d *) malloc( sizeof(struct ioControl_d) );
	
	if ( (void *) ioControl_keyboard == NULL )
	{
		printf("ldsic-init_keyboard: ioControl_keyboard fail");
		die();
	}else{
	    
	    ioControl_keyboard->id = 0;
	    ioControl_keyboard->used = 1;
	    ioControl_keyboard->magic = 1234;
	    
		ioControl_keyboard->tid = 0;  //qual threa está usando o dispositivo.
	    //ioControl_keyboard->
	};
	
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
	scrolllock_status = 0;
	numlock_status = 0;
	//...

	//AE    Enable Keyboard Interface: clears Bit 4 of command register
	//      enabling keyboard interface.
	kbdc_wait(1);
	outportb(0x64,0xAE);   // Activar a primeira porta PS/2
	
	//reset
	kbdc_wait(1);
	outportb(0x60,0xFF);


	//Leds.
	//LED_SCROLLLOCK 
	//LED_NUMLOCK 
	//LED_CAPSLOCK  	
	keyboard_set_leds(LED_NUMLOCK);
	
	//...
	
	
	//Debug support.
	scStatus = 0;

    g_driver_keyboard_initialized = (int) 1;
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
// ********************** Mouse ************************
//

//
// Obs: 
// Precisamos de um lugar para as rotinas de mouse. Elas não devem ficar aqui.
// @todo: mouse.c 
//



/*
 ***********************************************
 * init_mouse:
 *     Inicializando o mouse no controlador 8042.
 *     Carregando o bmp para o curso do mouse.
 */		
int init_mouse (){
	
    unsigned char response = 0;
    unsigned char deviceId = 0;
    int i; 
	int bruto = 1;  //Método.
	int mouse_ret;
	
	
	//user.h
	ioControl_mouse = (struct ioControl_d *) malloc( sizeof(struct ioControl_d) );
	
	if ( (void *) ioControl_mouse == NULL )
	{
		printf("ldsic-init_mouse: ioControl_mouse fail");
		die();
	}else{
	    
	    ioControl_mouse->id = 0;
	    ioControl_mouse->used = 1;
	    ioControl_mouse->magic = 1234;
	    
		//Qual thread está usando o dispositivo.
		ioControl_mouse->tid = 0;  
	    //ioControl_mouse->
	};	
	
	//
	// Estamos espaço para o buffer de mensagens de mouse.
	// mousemsg = ( unsigned char *) malloc(32);

		
	//Inicializando as variáveis usadas na rotina em Assemly
    //em hardwarelib.inc
    
	//Coordenadas do cursor.
	g_mousepointer_x = (unsigned long) 0;
    g_mousepointer_y = (unsigned long) 0;	
    mouse_x = 0;
    mouse_y = 0;
	
	//mouse_x = 0;
	//mouse_y = 0;
	
	//#bugbug: Essa inicialização está travando o mouse.
	//fazer com cuidado.
	
	//#bugbug. Cuidado com essa inicializaçao.
	g_mousepointer_width = 16;
	g_mousepointer_height = 16;
	


    //Bytes do controlador.
   // mouse_packet_data = 0;
   // mouse_packet_x = 0;
    //mouse_packet_y = 0;
    //mouse_packet_scroll = 0;
	
	
	//Mostraremos essa mensagem somente no ambiente de debug.
	
#ifdef KERNEL_VERBOSE	
    MessageBox(gui->screen, 1, "init_mouse:","initializing!");
#endif   
	
	//
	// Poderemos tentar de mais de um modo.
	// Obs: O modo bruto está funcionando. 
	//
	
	
//tryModoBruto:	
	
	//Modo bruto.
	//Obs: Esse modo está funcionando.
	/*
	if(bruto == 1){
	    mouse_write(0xFF);
	    mouse_write(0xF6); 
	    mouse_write(0xF4); 
		//while(!0xFA)mouse_read();
		while (mouse_read() != 0xfa);   // ACK
	};
	*/
	
 // Reseta mouse (reset ? lento!)...
  // Espero pelo byte 0xaa que encerra a sequ?ncia
  // de reset!
  kbdc_wait(1);
  mouse_write(0xff);
  while (mouse_read() != 0xaa);

  // Restaura defaults do PS/2 mouse.
  kbdc_wait(1);
  mouse_write(0xf6);
  while (mouse_read() != 0xfa);


// TODO: Pode ser interessante diminuir a sensibilidade do mouse
  // aqui!!!

  // Habilita o mouse streaming
  // Interessante notar que, no modo streaming,
  // 1 byte recebido do PS/2 mouse gerar  uma IRQ...
  // Talvez valha a pena DESABILITAR o modo streaming
  // para colher os 3 dados de uma s¢ vez na IRQ!
  kbdc_wait(1);
  mouse_write(0xf4);
  while (mouse_read() != 0xfa);         // ACK
  
	
	//
	// Aqui podemos tentar outros modos mais completos.
	//
	
//done:

    // Reabilitando as duas portas.
	
	// Ativar a primeira porta PS/2.
	kbdc_wait(1);
	outportb(0x64,0xAE);   

	// Ativar a segunda porta PS/2.
	kbdc_wait(1);
	outportb(0x64,0xA8); 


	//
	// ## BMP ##
	//
	
	//
	// Carregando o bmp do disco para a memória
	// e apresentando pela primeira vez.
	//
	
	// ## test ##
	//susenso. Isso funciona.
    
	mouse_ret = (int) load_mouse_bmp ();	
	if (mouse_ret != 0)
	{
		printf("ldisc-init_mouse: load_mouse_bmp");
		die();
	}
	
#ifdef KERNEL_VERBOSE		
    MessageBox(gui->screen, 1, "init_mouse:","Mouse initialized!");   
#endif  

    //initialized = 1;
    //return (kernelDriverRegister(mouseDriver, &defaultMouseDriver));	
	return (int) 0;
};


/*
 * mouse_write:
 *     Envia um byte para a porta 0x60.
 *     (Nelson Cole) 
 */
void mouse_write (unsigned char write){
	
	kbdc_wait(1);
	outportb (0x64,0xD4);
	
	kbdc_wait(1);
	outportb (0x60,write);
};


/*
 * mouse_read:
 *     Pega um byte na porta 0x60.
 *     (Nelson Cole) 
 */
unsigned char mouse_read (){
	
	kbdc_wait(0);
	
	return inportb(0x60);
};


/*
 * kbdc_wait:
 *     Espera por flag de autorização para ler ou escrever.
 *     (Nelson Cole) 
 */
void kbdc_wait (unsigned char type){
	
	if (type==0)
	{
		//#bugbug rever
        while ( !inportb(0x64) & 1 )
		{
			outanyb (0x80);
		};
		
    }else{
		
        while ( inportb(0x64) & 2 )
		{
			outanyb (0x80);
		};
	};
};


/*
//rotina interna de suporta ao mouseHandler 
#define _MOUSE_X_SIGN 0x10
#define _MOUSE_Y_SIGN 0x20

void
update_mouse1()
{

char x = (mouse_packet_data & _MOUSE_X_SIGN);
char y = ( mouse_packet_data & _MOUSE_Y_SIGN );


//do_x:
	    //x 
		//checando o sinal para x.
		//se for diferente de 0 então x é negativo
		if(x != 0)
		{
			//complemento de 2.
			mouse_packet_x = ~mouse_packet_x + 1;
			mouse_x = mouse_x - mouse_packet_x;
		}else{

			mouse_x = mouse_x + mouse_packet_x;
		}

		
//do_y:		
		//y
		//se for diferente de 0 então y é negativo
		if(y != 0)
		{
			//complemento de 2.
			mouse_packet_y = ~mouse_packet_y + 1;
			mouse_y = mouse_y + mouse_packet_y;
		}else{
			mouse_y = mouse_y - mouse_packet_y;
		};		
		
    return;		
};
*/



/*
 **************
 * mouseHandler:
 *     Handler de mouse. 
 *
 * *Importante: 
 *     Se estamos aqui é porque os dados disponíveis no 
 * controlador 8042 pertencem ao mouse.
 *
 * @todo: Essa rotina não pertence ao line discipline.
 * Obs: Temos externs no início desse arquivo.
 * 
 */ 
#define MOUSE_DATA_BIT 1
#define MOUSE_SIG_BIT  2
#define MOUSE_F_BIT  0x20
#define MOUSE_V_BIT  0x08 

//contador
static int count_mouse = 0;

// Buffer.
static char buffer_mouse[3];
	
void mouseHandler (){
		
    // Coordenadas do mouse.
    // Obs: Isso pode ser global.
    // O tratador em assembly tem as variáveis globais do posicionamento.
    
	int posX=0;
    int posY=0;	

    //Char para o cursor provisório.
	//#todo: Isso foi subtituido por uma bmp. Podemos deletar.
    //static char mouse_char[] = "T";

	char *_byte;


	// Lendo um char no controlador.
	
	*_byte = (char) mouse_read();
	
	
	// #importante:
	// Contagem de interruções:
	// Obs: Precisamos esperar 3 interrupções.
	
	//#bugbug essa variável está inicializando toda vez que 
	//se chama o handler porque ela é interna. ??
	
	switch ( count_mouse )
	{
		// Essa foi a primeira interrupção.
		case 0:
		    //Pegamos o primeiro char.
		    buffer_mouse[0] = (char) *_byte;
            if(*_byte & MOUSE_V_BIT)
                count_mouse++;
		    break;
			
		// Essa foi a segunda interrupção.	
		case 1:
		    //Pegamos o segundo char.
		    buffer_mouse[1] = (char) *_byte;
			count_mouse++;
		    break;
			
		// Essa foi a terceira interrupção.	
		case 2:
		    //Pegamos o terceiro char.
            buffer_mouse[2] = (char) *_byte;
			count_mouse = 0;
			
			//#importante:
			//A partir de agora já temos os três chars.
			
			//??
			//Colocando os três chars em variáveis globais.
            //Isso ficará assim caso não aja overflow ...
			mouse_packet_data = buffer_mouse[0];
	 	    mouse_packet_x = buffer_mouse[1];       
		    mouse_packet_y = buffer_mouse[2];
            
			// #importante:
			// #todo: Isso está em Assembly, lá em hwlib.inc, 
			// mas queremos que seja feito em C.
			// #obs: Uma rotina interna aqui nesse arquivo está tentando isso.
			
			update_mouse();			
			
		    // #importante:
			// Agora vamos manipular os valores obtidos através da 
			// função de atualização dos valores.
			
			mouse_x = (mouse_x & 0x00000FFF ); 
		    mouse_y = (mouse_y & 0x00000FFF );
		
		    // Checando limites.
            // #todo: Os valores foram determinados. 
			// Precisamos usar variáveis.
			
			if( mouse_x < 1 ){ mouse_x = 1; }	
		    if(	mouse_y < 1 ){ mouse_y = 1; }
		    if(	mouse_x > (800-16) ){ mouse_x = (800-16); }
		    if(	mouse_y > (600-16) ){ mouse_y = (600-16); }

		    // # Draw BMP #
		    // Isso está funcionando bem.
			// #todo: precisamos colocar no backbuffer o retãngulo salvo previamente.
            // #todo: Precisamos salvar o conteúdo de um retângulo 
			// que está no backbuffer, para depois pintarmos o mouse.
			
			//#todo: Criar essas funções e variáveis.
			//ex: display_saved_rect( saved_rect_Buffer, old_mouse_x, old_mouse_y );
            //ex: save_rect(x,y);
			
			bmpDisplayMousePointerBMP ( mouseBMPBuffer, mouse_x, mouse_y );
		    refresh_rectangle ( mouse_x, mouse_y, 16, 16 );	

            //nova técnica.
            //+ copia no LFB um retângulo do backbuffer para apagar o ponteiro antigo.
            //+ decodifica o mouse diretamente no LFB.			
			
            break;

        default:
		    count_mouse = 0;
            break;		
	};
	
	
	// #importante 
	// Por outro lado o mouse deve confrontar seu posicionamento com 
	// todas as janelas, para saber se as coordenadas atuais estão passando 
	// por alguma das janelas. Se estiver, então enviaremos mensagens para essa 
	// janela que o mouse passou por cima. Ela deve ser sinalizada como hover,
	// 
	// #importante:
	// Se houver um click, o elemento com mousehover será afetado, e 
	// enviaremos mesagens para ele, se apertarem enter ou application key, 
	// quem recebe a mensagem é o first responder, ou seja, a janela com o 
	// foco de entrada.
    // Se clicarmos com o botão da direita, quem recebe a mensagem é 
    // a janela que o mouse está passando por cima.	
	
	
	//
	//  ## Button ##
	//
	
	// ===
	//Apenas obtendo o estado dos botões.
	
	mouse_buttom_1 = 0;
	mouse_buttom_2 = 0;
	mouse_buttom_3 = 0;
	
	if( ( mouse_packet_data & 0x01 ) == 0 )
	{
		//liberada.
		mouse_buttom_1 = 0;
	}else if( ( mouse_packet_data & 0x01 ) != 0 )
	    {
		    //pressionada.
		    //Não tem como pressionar mais de um botão por vez.
	        mouse_buttom_1 = 1;
	        mouse_buttom_2 = 0;
	        mouse_buttom_3 = 0;		  
	    }
			  

	if( ( mouse_packet_data & 0x02 ) == 0 )
	{
	    //liberada.
	    mouse_buttom_2 = 0;
	}else if( ( mouse_packet_data & 0x02 ) != 0 )
	    {
		    //pressionada.
		    //Não tem como pressionar mais de um botão por vez.
	        mouse_buttom_1 = 0;
	        mouse_buttom_2 = 1;
	        mouse_buttom_3 = 0;		  			 
	    }
			  
	if( ( mouse_packet_data & 0x04 ) == 0 )
	{
	    //liberada.
	    mouse_buttom_3 = 0;
	}else if( ( mouse_packet_data & 0x04 ) != 0 )
	    {
	        //pressionada.
		    //Não tem como pressionar mais de um botão por vez.			 
	        mouse_buttom_1 = 0;
	        mouse_buttom_2 = 0;
	        mouse_buttom_3 = 1;		  			
	    }			
	
	
    // ===	
	// Confrontando o estado atual com o estado anterior para saber se ouve 
	// alguma alteração ou não.
	// 1 = ouve alteração.
	
	if( mouse_buttom_1 != old_mouse_buttom_1 ||
	    mouse_buttom_2 != old_mouse_buttom_2 ||
		mouse_buttom_3 != old_mouse_buttom_3 )
	{
		mouse_button_action = 1;
	}else{
		mouse_button_action = 0;
	};
	
	// #refletindo: 
	// ?? E no caso de apenas considerarmos que o mouse está se movendo, 
	// mandaremos para janela over. ???
	
	// #refletindo:
	// Obs: A mensagem over pode ser enviada apenas uma vez. 
	// será usada para 'capturar' o mouse ... 
	// e depois tem a mensagem para 'descapturar'.
	
	//
	//  ## Scan ##
	//
	
	//===========
	// (capture) - On mouse over. 
	//

	struct window_d *wScan;
	
	// wID = ID da janela.
	// Escaneamos para achar qual janela bate com os valores indicados.
	// Ou seja. Sobre qual janela o mouse está passando.

	// #IMPORTANTE
	// Se for válido e diferente da atual, significa que 
	// estamos dentro de uma janela.
	// -1 significa que ouve algum problema no escaneamento.
	
	int wID; 
	
	wID = (int) windowScan ( mouse_x, mouse_y );	
	
	if ( wID == -1 )
	{ 
        // Nothing.
		
    }else{
		
		wScan = (struct window_d *) windowList[wID];
		
		//#bugbug 
		//#todo:
		// Deveriamos aqui checarmos a validade da estrutura ??
		
		//redraw_window(wScan);
        
        // #importante
		// Se um botão foi pressionado ou liberado, então enviaremos uma 
		// mensagem relativa ao estado do botão, caso contrário, enviaremos 
		// uma mensagem sobre a movimentação do mouse.
		
		//#importante
		// Se houve mudança em relação ao estado anterior.
		if ( mouse_button_action == 1 )
		{
			//Qual botão mudou seu estado??
			//Checaremos um por um.
			
			//1
			//Igual ao estado anterior
			if( mouse_buttom_1 == old_mouse_buttom_1 )
			{
				//...
			
			//Diferente do estado anterior.
			}else{
				
				//down
				if ( mouse_buttom_1 == 1 )
				{                
					
					//clicou
					if ( old_mouse_buttom_1 == 0 ){
						
                        windowSendMessage ( (unsigned long) wScan, 
					        (unsigned long) MSG_MOUSEKEYDOWN, 
							(unsigned long) 1, 
							(unsigned long) 0 );  						
				    
					    //atualiza o estado anterior.
					    old_mouse_buttom_1 = 1;
					}
					
				}else{
					
					//up
			        windowSendMessage ( (unsigned long) wScan, 
					    (unsigned long) MSG_MOUSEKEYUP, 
						(unsigned long) 1, 
						(unsigned long) 0 );
					old_mouse_buttom_1 = 0;	
				}
			}; 
			
			
			//2
			//Igual ao estado anterior
			if ( mouse_buttom_2 == old_mouse_buttom_2 )
			{
				//...
				
			//Diferente do estado anterior.	
			}else{
				
				//down
				if ( mouse_buttom_2 == 1 )
				{
					
					//clicou
					if( old_mouse_buttom_2 == 0 ){
						
                        windowSendMessage ( (unsigned long) wScan, 
					        (unsigned long) MSG_MOUSEKEYDOWN, 
							(unsigned long) 2, 
							(unsigned long) 0 );  						
				    
					    //atualiza o estado anterior.
					    old_mouse_buttom_2 = 1;
					}

                }else{
					
					//up
			        windowSendMessage ( (unsigned long) wScan, 
					    (unsigned long) MSG_MOUSEKEYUP, 
						(unsigned long) 2, 
						(unsigned long) 0 );
						
					old_mouse_buttom_2 = 0;
				}
			}; 
			
			
			//3
			//Igual ao estado anterior
			if ( mouse_buttom_3 == old_mouse_buttom_3 )
			{
				//...
				
				
			//Diferente do estado anterior.	
			}else{
				
				//down
				if ( mouse_buttom_3 == 1 )
				{
					//clicou
					if ( old_mouse_buttom_3 == 0 ){
                        
						windowSendMessage( (unsigned long) wScan, 
					        (unsigned long) MSG_MOUSEKEYDOWN, 
							(unsigned long) 3, 
							(unsigned long) 0 );  						
				    
					    //atualiza o estado anterior.
					    old_mouse_buttom_3 = 1;
					}

                }else{
					
					//up
			        windowSendMessage( (unsigned long) wScan, 
					    (unsigned long) MSG_MOUSEKEYUP, 
						(unsigned long) 3, 
						(unsigned long) 0 );
						
					old_mouse_buttom_3 = 0;
				}
			}; 
			
			//Ação concluída.
			mouse_button_action = 0;
			
			
		// Se NÃO ouve alteração no estado dos botões, então apenas 
		// enviaremos a mensagem de movimento do mouse e sinalizamos 
		// qual é a janela que o mouse está em cima.
			
		}else{
			
			// #importante
			// Lembrando que estamos dentro de uma janela ...
			// por isso a mensagem é over e não move.
			
            //Obs: Se a janela for a mesma que capturou o mouse,
			//então não precisamos reenviar a mensagem.
			//Mas se o mouse estiver em cima de uma janela diferente da 
			//que ele estava anteriormente, então precisamos enviar uma 
			//mensagem pra essa nova janela.
			
			if ( wScan->id != mouseover_window )
			{				
				//Agora enviamos uma mensagem pra a nova janela que o mouse 
				//está passando por cima.
				mouseover_window = wScan->id;
				
                windowSendMessage ( (unsigned long) wScan, 
		            (unsigned long) MSG_MOUSEOVER, 
			        (unsigned long) mouseover_window, 
			        (unsigned long) mouseover_window );
				
			}else{ 
			    
				//nothing ...
				//não precisamos reenviar a mensagem, poi o mouse 
				//continua na mesma janela que antes.
			};
			
			
			//Ação concluída.
			//Para o caso de um valor incostante na flag.
			mouse_button_action = 0;			
		};
		
		// #debug. (+)
		// Isso coloca o (+) no frontbuffer.
		draw_text ( wScan, 0, 0, COLOR_YELLOW, "+" );
		refresh_rectangle ( wScan->left, wScan->top, 8, 8 );
	};

    // EOI.		
    outportb ( 0xa0, 0x20 ); 
    outportb ( 0x20, 0x20 );
};


// Input.
// Input a value from the keyboard controller's data port, after checking
// to make sure that there's some data there for us.
static unsigned char inPort60 (void){
	
    unsigned char data = 0;

    while (!(data & 0x01))
        kernelProcessorInPort8(0x64, data);

    kernelProcessorInPort8(0x60, data);
	
    return (data);
};


// Output.
// Output a value to the keyboard controller's data port, after checking
// to make sure it's ready for the data.
static void outPort60 (unsigned char value){
	
    unsigned char data;
  
    // Wait for the controller to be ready
    data = 0x02;
    while (data & 0x02)
        kernelProcessorInPort8(0x64, data);
  
    data = value;
    kernelProcessorOutPort8(0x60, data);
 
    return;
};


// Output.
// Output a value to the keyboard controller's command port, after checking
// to make sure it's ready for the command
static void outPort64 (unsigned char value){
	
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
 * Input a value from the keyboard controller's data port, after checking
 * to make sure that there's some mouse data there for us.
 */
static unsigned char getMouseData (void){
	
    unsigned char data = 0;

    while ((data & 0x21) != 0x21)
        kernelProcessorInPort8(0x64, data);

    kernelProcessorInPort8(0x60, data);
	
	return (data);
};


/*
 * kernelPS2MouseDriverReadData:  
 *     Pega os bytes e salva em um array.
 *     Exibe um caractere na tela, dado as cordenadas.
 *     This gets called whenever there is a mouse interrupt
 *     @todo: Rever as entradas no array.         
 */
void kernelPS2MouseDriverReadData (void){
    //#suspensa !	
};


/* 
 * **************
 * P8042_install:
 *     Configurando o controlador PS/2, 
 *     e activar a segunda porta PS/2 (mouse).
 *     (Nelson Cole)
 */
void P8042_install (){
	
	unsigned char status;

    // Desativar dispositivos PS/2 , isto evita que os dispositivos PS/2 
	// envie dados no momento da configuração.

//desablePorts:
	
	// Desativar a primeira porta PS/2.
  	kbdc_wait(1);
	outportb(0x64,0xAD);  
	
	// Desativar a segunda porta PS/2, 
	// hahaha por default ela já vem desativada, só para constar
	kbdc_wait(1);
	outportb(0x64,0xA7); 

//goAhead:
	
	 // Defina a leitura do byte actual de configuração do controlador PS/2.
	kbdc_wait(1);    
	outportb(0x64,0x20);    

	// Activar o segundo despositivo PS/2, modificando o status de 
	// configuração do controlador PS/2. 
	// Lembrando que o bit 1 é o responsável por habilitar, desabilitar o 
	// segundo despositivo PS/2  ( o rato). 
	// Só para constar se vedes aqui fizemos duas coisas lemos ao mesmo tempo 
	// modificamos o byte de configuração do controlador PS/2 
	
	kbdc_wait(0);
	status = inportb(0x60)|2;  
	
	// defina, a escrita  de byte de configuração do controlador PS/2.
	kbdc_wait(1);
	outportb(0x64,0x60);  

	// devolvemos o byte de configuração modificado.
	kbdc_wait(1);
	outportb(0x60,status);  

	// Obs:
	// Agora temos dois dispositivos seriais teclado e mouse (PS/2).

    // Reabilitando portas.
	
//enablePorts:
	
	// Ativar a primeira porta PS/2.
	kbdc_wait(1);
	outportb(0x64,0xAE);   

	// Ativar a segunda porta PS/2.
	kbdc_wait(1);
	outportb(0x64,0xA8);  

    // Done!
	
	// espera.
	// ?? Pra que isso ??
	kbdc_wait(1);  
    
    // NOTA. 
	// Esta configuração discarta do teste do controlador PS/2 e de seus dispositivos. 
	// Depois façamos a configuração decente e minuciosa do P8042.
};



/*
 **********************************************************
 * load_mouse_bmp:  ## teste ##
 *     Carregando o arquivo MOUSE.BMP que é o ponteiro de mouse.
 *     Usar isso na inicialização do mouse.
 *     #bugbug isso pode ir para windowLoadGramadoIcons
 */
int load_mouse_bmp (){
	
	int Status = 1;
	int Index;
    struct page_frame_d *pf;
	unsigned long fileret;
	
#ifdef KERNEL_VERBOSE
	printf("load_mouse_bmp:\n");
#endif	
	
	// #Importante
	// Fizemos um teste e funcionou com 500 páginas.
	// Foi suficiente para testarmos um pano de fundo.
	// Ret = (void*) allocPageFrames(500);  
	
    // Alocando duas páginas para um BMP pequeno. 8KB.	
	mouseBMPBuffer = (void *) allocPageFrames(2);
	//mouseBMPBuffer = (void*) allocPageFrames(10);
	//mouseBMPBuffer = (void*) allocPageFrames(100);  //400KB
	
	if ( (void *) mouseBMPBuffer == NULL ){
		
	    printf("unblocked-ldisc-load_mouse_bmp: mouseBMPBuffer\n");
		goto fail;		
	};
	
	
	// #debug
	//printf("\n");
	//printf("BaseOfList={%x} Showing #32 \n",mouseBMPBuffer);
    //for(Index = 0; Index < 32; Index++)   	
	//{  
    //    pf = (void*) pageframeAllocList[Index]; 
	//	
	//	if( (void*) pf == NULL ){
	//	    printf("null\n");	 
	//	}
	//   if( (void*) pf != NULL ){
	//	    printf("id={%d} used={%d} magic={%d} free={%d} handle={%x} next={%x}\n",
	//          pf->id ,pf->used ,pf->magic ,pf->free ,pf ,pf->next ); 	
	//	}
	//}
	
	//
	// ## Loading ...  ##
	//
	
	//read_fntos( (char *) arg1);
	
	
	//===================================
	// MOUSE
	fileret = (unsigned long) fsLoadFile( "MOUSE   BMP", 
	                            (unsigned long) mouseBMPBuffer );
								  
	if( fileret != 0 )
	{
		printf("MOUSE.BMP FAIL\n");		
		// Escrevendo string na janela.
		//draw_text( gui->main, 10, 500, COLOR_WINDOWTEXT, "MOUSE.BMP FAIL");
		goto fail;	
	};
	
	// Render BMP file on backbuffer.
	//bmpDisplayBMP( mouseBMPBuffer, 20, 20 );
	//refresh_rectangle( 20, 20, 16, 16 );	
    //===================================							
	
	
	//===================================
	//DENNIS
	//fileret = (unsigned long) fsLoadFile( "DENNIS  BMP", 
	//                              (unsigned long) mouseBMPBuffer );
								  
	//if( fileret != 0 )
	//{
	//	printf("DENNIS  BMP FAIL\n");		
		// Escrevendo string na janela.
		//draw_text( gui->main, 10, 500, COLOR_WINDOWTEXT, "MOUSE.BMP FAIL");
	//	goto fail;	
	//};
	
	// Render BMP file on backbuffer.
	//bmpDisplayBMP( mouseBMPBuffer, 0, 0 );
    //refresh_rectangle( 0, 0, 800, 600 );	
	//refresh_rectangle( 20, 40, 400, 400 );
	//===================================
	
	
//refresh_rectangle:

	//Isso funcionou ...
	//refresh_rectangle( 20, 20, 16, 16 );
	Status = (int) 0;
	goto done;
	
fail:
    printf("fail\n");
    Status = (int) 1;		
done:

#ifdef KERNEL_VERBOSE
    printf("done\n");
#endif	
	//refresh_screen();
    return (int) Status;	
};


/*
 ***************
 * ps2:
 *     Essa rotina de inicialização do controladro 
 * poderá ter seu próprio módulo.
 *     Inicializa o controlador ps2.
 *     Inicializa a porta do teclado no controlador.
 *     Inicializa a porta do mouse no controlador.
 *     Obs: *importante: A ordem precisa ser respeitada.
 *     As vezes os dois não funcionam ao mesmo tempo se a 
 *     inicialização não for feita desse jeito. 
 */
void ps2 (){
	
	//deverá ir para ps2.c @todo: criar arquivo.
    
	P8042_install();  
	
	//@todo: isso deveria se chamar init_ps2_mouse ...
    //?? quem inicializará a porta do teclado ?? o driver ??
	//?? quem inicializará a porta do mouse ?? o driver ??
	 
	init_keyboard();  
	init_mouse();	 
};


void set_current_keyboard_responder ( int i ){
	
	current_keyboard_responder = i;
};


int get_current_keyboard_responder (){
	
	return (int) current_keyboard_responder;
};


void set_current_mouse_responder ( int i ){
	
    current_mouse_responder = i;	
};


int get_current_mouse_responder (){
	
    return (int) current_mouse_responder;	
};


//inicializando a fila de mensagens do sistema
//com ponteiros para estruturas de mensagens ...
//es estruturas serão reutilizáveis.
void initialize_system_message_queue (){
	
	struct message_d *m;
	
	int i;
	
	for ( i=0; i<SYSTEM_MESSAGE_QUEUE_MAX; i++ )
	{
		
		m = (void *) malloc ( sizeof(struct message_d) );
		
		if ( (void *) m == NULL )
		{
			printf("unblocked-ldisc-initialize_system_message_queue:");
			die();
		}else{
			
			m->objectType = ObjectTypeMessage;
			m->objectClass = ObjectClassKernelObjects;
		    m->used = 1;
			m->magic = 1234;
			m->empty = 1;
            system_message_queue[i] = (unsigned long) m;		
		}; 
	};
	
	system_message_write = 0;
	system_message_read = 0;
};


// Inicializa o status das teclas de modificação.
// são usadas em comjunto com outras teclas para criar atalhos.
// modificam temporariamente a função de outra tecla.
void ldisc_init_modifier_keys (){
	
	// Modifier keys.
	
	// Shift.
	shift_status = 0;
	
	// Control.
	ctrl_status = 0;
	
	// Win key.
	winkey_status = 0;
    
	// Alternate.
    alt_status = 0;

	// Alternate Graphic.
    //altgr_status = 0; //@todo
    
	// Function.
	//fn_status = 0;  //@todo
	
	//...
};


// modificam permanentemente a função de outra tecla.
//ativa as teclas extendidas.
void ldisc_init_lock_keys (){
	
    // Capital Lock.	
	capslock_status = 0;
	
	// Scrolling Lock.
	scrolllock_status = 0;
	
	// Number Lock.
	numlock_status = 0;	
};


//
// End.
//

