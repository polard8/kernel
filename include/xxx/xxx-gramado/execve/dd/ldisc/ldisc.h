/*
 * File: ldisc.h 
 *
 * Descrição:
 *     >> header para o módulo ldisc do kernel base.
 *
 *     Header do driver de teclado presente dentro do kernel. 
 *     Manter aqui parâmetros gerais, que possam ser úteis pra qualquer 
 * driver de teclado.
 *     Coisas como estrutura para identificação do modele, nome do driver,
 *      pathname do driver.
 *
 * Ambiente:
 *     Kernel mode (Ring 0).
 *
 * Ports:
 * =====
 *  060-06F  = 8042 Keyboard Controller (AT, PS/2).
 *	060      = 8042 Keyboard input/output buffer register.
 *	061      = 8042 system control port (for compatability with 8255).
 *	064      = 8042 Keyboard command/status register.
 *
 *
 * Keyboard Controller Commands:
 * =============================
 * Commands are sent to the keyboard controller by writing to port 0x64.  
 * Command parameters are written to port 0x60 after teh command is sent.  
 * Results are returned on port 0x60.  Always test the 
 * OBF ("Output Buffer Full") 
 * flag before writing commands or parameters to the 8042.
 *
 * 0x20 (Read Command Byte) - Returns command byte.  (See "Write Command Byte" below).
 * 0x60 (Write Command Byte) - Stores parameter as command byte.  
 * Command byte defined as follows:
 *
 * More ...
 *
 * ?0x90-0x9F (Write to output port) - Writes command's lower nibble to 
 * lower nibble of output port (see Output Port definition.)
 * ?0xA1 (Get version number) - Returns firmware version number.
 * ?0xA4 (Get password) - Returns 0xFA if password exists; otherwise, 0xF1.
 * ?0xA5 (Set password) - Set the new password by sending a null-terminated 
 * string of scan codes as this command's parameter.
 * ?0xA6 (Check password) - Compares keyboard input with current password.
 * 0xA7 (Disable mouse interface) - PS/2 mode only.  
 * Similar to "Disable keyboard interface" (0xAD) command.
 * 0xA8 (Enable mouse interface) - PS/2 mode only.  
 * Similar to "Enable keyboard interface" (0xAE) command. 
 * 0xA9 (Mouse interface test) - Returns 0x00 if okay, 0x01 if Clock line 
 * stuck low, 0x02 if clock line stuck high, 0x03 if data line stuck low, 
 * and 0x04 if data line stuck high.
 * 0xAA (Controller self-test) - Returns 0x55 if okay.
 * 0xAB (Keyboard interface test) - Returns 0x00 if okay, 
 * 0x01 if Clock line stuck low, 0x02 if clock line stuck high, 0x03 if data 
 * line stuck low, and 0x04 if data line stuck high.
 * 0xAD (Disable keyboard interface) - Sets bit 4 of command byte and disables all 
 * communication with keyboard.
 * 0xAE (Enable keyboard interface) - Clears bit 4 of command byte and re-enables 
 * communication with keyboard.
 * 0xAF (Get version)
 * 0xC0 (Read input port) - Returns values on input port (see Input Port definition.)
 * 0xC1 (Copy input port LSn) - PS/2 mode only. 
 * Copy input port's low nibble to Status register (see Input Port definition)
 * 0xC2 (Copy input port MSn) - PS/2 mode only. 
 * Copy input port's high nibble to Status register (see Input Port definition.)
 * 0xD0 (Read output port) - Returns values on output port (see Output Port definition.) 
 * 0xD1 (Write output port) - Write parameter to output port (see Output Port definition.)
 * 0xD2 (Write keyboard buffer) - Parameter written to input buffer as if 
 * received from keyboard.
 * 0xD3 (Write mouse buffer) - Parameter written to input buffer as if received from mouse.
 * 0xD4 (Write mouse Device) - Sends parameter to the auxillary PS/2 device.
 * 0xE0 (Read test port) - Returns values on test port (see Test Port definition.)
 * 0xF0-0xFF (Pulse output port) - Pulses command's lower nibble onto lower nibble 
 * of output port (see Output Port definition.)
 *
 * Histórico:
 *     Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *     Versão 1.0, 2016 - Aprimoramento geral das rotinas básicas.
 *     //...
 */ 
 
 
//?? Não sei quem usa isso. 
//size should always be a power of 2
#define QUEUE_INITIAL_SIZE 32 //16 
 
 
//keyboard support
#define LDISC_KEY_RELEASED  0x80
#define LDISC_KEY_MASK  0x7F
#define LDISC_FULL      1
#define LDISC_EMPTY     0
#define LDISC_OBF       0x01    //Output buffer flag.
 
//msg - dialog 
#define LDISC_NULL 0
#define LDISC_GET_ALT_STATUS 1
#define LDISC_GET_CTRL_STATUS 2
#define LDISC_GET_SHIFT_STATUS 3
#define LDISC_GET_WINKEY_STATUS 4
#define LDISC_GET_CAPITAL_STATUS 5
#define LDISC_GET_NUMLOCK_STATUS 6
#define LDISC_CHANGE_MESSAGE1 7     //use long1 como mensagem
#define LDISC_CHANGE_MESSAGE2 8     //use long2 como mensagem

//pega a próxima mensagem da fila fifo. circular.
#define LDISC_GET_NEXT_MESSAGE 9    

//pega o próximo scancode da fila fifo. circular.
#define LDISC_GET_NEXT_SCANCODE 10  

//Um endereço em usermode espera pelos 4 argumentos da mensagem.	
#define LDISC_RECEIVE_MESSAGE   11  
#define LDISC_LOAD_ARGS   12
//...
 
 
 
//variável de ambiente. 
#define KEYBOARD_DRIVER_PATHNAME "/root/drivers/keyboard.bin" 
//... 
 
// Keyboard LEDs
#define LED_SCROLLLOCK  1
#define LED_NUMLOCK     2
#define LED_CAPSLOCK    4
 
 


 




//
// @todo: Sondando scancode. (provisório.)
//

//ldisc
int scStatus;



 
 
//??ldisc
unsigned long ambiente;
unsigned long destroy_window;
unsigned long quit_message;



//
// Prototypes.
//

 

 

//#bugbug
//?? Onde está essa função ??
//Não lembro onde está a função desse protótipo.
//input pega caracteres digitados.
unsigned long input(unsigned long ch);



 


//
//*************************** line discipline ***********************
//


// #importante:
// Essa é a rotina genérica do line discipline
// Qualquer input pode chama-la e enviar mensagem para 
// a thread de input da janela com foco de entrada.

int 
LINE_DISCIPLINE ( struct window_d *window, 
                  int msg, 
				  unsigned long long1, 
				  unsigned long long2 );



// Keyboard.				  
// Usada para receber input do dispositivo teclado,
// a único argumento aceito é o 'Scan Code'.
				  
int KEYBOARD_LINE_DISCIPLINE ( unsigned char SC );



// Mouse 
// A entrada é um ponteiro para um buffer que contenha os 
// 3 chars usados pelo mouse.

int MOUSE_LINE_DISCIPLINE ( void *buffer );


// #todo
// Outros esquemas de input podem ser criados aqui.

//
// End.
//
