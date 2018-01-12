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
 
 

#define LDISC_KEY_RELEASED  0x80
#define LDISC_KEY_MASK  0x7F
#define LDISC_FULL      1
#define LDISC_EMPTY     0
#define LDISC_OBF       0x01    //Output buffer flag.
 
 
//variável de ambiente. 
#define KEYBOARD_DRIVER_PATHNAME "/root/drivers/keyboard.bin" 
//... 
 
// Keyboard LEDs
#define LED_SCROLLLOCK  1
#define LED_NUMLOCK     2
#define LED_CAPSLOCK    4
 
 



/*
Table 1.  Consumer Page audio controls supported in Windows 2000.
Usage	Usage Name	Usage Type
0xE0	Volume*	Linear Control (LC)
0xE2	Mute*	On/Off Control (OOC)
0xE3	Bass	Linear Control (LC)
0xE4	Treble	Linear Control (LC)
0xE5	Bass Boost*	On/Off Control (OOC)
0xE7	Loudness	On/Off Control (OOC)
0xE9	Volume Increment*	Re-trigger Control (RTC)
0xEA	Volume Decrement*	Re-trigger Control (RTC)
0x152	Bass Increment	Re-trigger Control (RTC)
0x153	Bass Decrement	Re-trigger Control (RTC)
0x154	Treble Increment	Re-trigger Control (RTC)
0x155	Treble Decrement	Re-trigger Control (RTC)
*/


// Enumerando os tipos de teclados.
typedef enum {
    KEYBOARD_VIRTUAL,
    KEYBOARD_PS2,
    KEYBOARD_USB,
    //...
}keyboard_type_t;

//
// @todo: estrutura de dispositivo:
//        nela tem informações sobre o driver.
//


//char keyboardString[] = "Generic keyboard";


/*
 * Keyboard global variables.
 */


//
// @todo: Sondando scancode. (provisório.)
//
int scStatus;


//
// Driver handler support.
//

unsigned long keyboard_handler_address;
 
//@todo: Variável que identifique o driver. seu nome e pathname.

//int KeyboardObjectNumber;
//char *keybaord_driver_name;
//char *keybaord_driver_pathname;


/*
* encapsulando em kernel.c
//status
unsigned long key_status;
unsigned long escape_status;
unsigned long tab_status;
unsigned long winkey_status;
unsigned long ctrl_status;
unsigned long alt_status;
unsigned long shift_status;
*/


unsigned long ambiente;
unsigned long destroy_window;
unsigned long quit_message;



//
// Sobre charmaps:
// ?? quem deve possuir o char map ??
// Obviamente o kernel base precis de algum controle sobre isso.
// sujerindo alterações conforme a conveniência do usuário.
// Se a intenção é que o driver de teclado passe para a line discipline 
// somente o scancode, então não há a necessidade de o driver de teclado 
// ter um char map, ele apenas passa o scancode.
//

 

//
// structure for hardware keyboard info.
//  As informações sobre o hardware de teclado devem ser mantidas 
// pelo kernel base, mas não é aqui o lugagr dessa estrutura.
//

typedef struct keyboard_d keyboard_t;
struct keyboard_d
{
	object_type_t objectType;
	object_class_t objectClass;

	keyboard_type_t type;
	//...
	int dummy;
	//int VendorId;
	//...

    //unsigned long normal_charmap_address;
    //unsigned long shift_charmap_address;
    //unsigned long control_charmap_address;

	//unsigned long keyboard_handler_address;

};
//keyboard_t *Keyboard;


//
// Prototypes.
//

//Pega o status das teclas de modificação.
unsigned long keyboardGetKeyState(unsigned char key);

//@todo: função para mudar o handler.
//o kernel deve oferecer o serviço de trocar o handler
//de todo driver.


//Enable and disable keyboard.
void keyboardEnable();
void keyboardDisable();

/*
 * Prototypes for keyboard support.
 */

//Set flags.
void keyboard_set_leds(char flag); 


//get status 
int get_alt_status();
int get_ctrl_status();
int get_shift_status();
//...




 

void init_keyboard();

/*
 * Get window procedure parameters.
 */
void *KdGetWindowPointer(int tid); 
int KbGetMessage(int tid);
unsigned long KbGetLongParam1(int tid);
unsigned long KbGetLongParam2(int tid);


//input pega caracteres digitados.
unsigned long input(unsigned long ch);

/*
 * Reboot via Keyboard port.
 */
void reboot();

//
// ********************** mouse ************************
//

unsigned long g_mousepointer_width;
unsigned long g_mousepointer_height;

void *mouseBMPBuffer; //buffer para o bmp

int init_mouse();
void mouse_write(unsigned char write);
unsigned char mouse_read();
void kbdc_wait(unsigned char type);
void mouseHandler(); 
static unsigned char inPort60(void);
static void outPort60(unsigned char value);
static void outPort64(unsigned char value);
static unsigned char getMouseData(void);
void kernelPS2MouseDriverReadData(void);
int load_mouse_bmp();


//
// *****************  ps/2 ***********************
//

void P8042_install();
void ps2();

//
//*************************** line discipline ***********************
//

//LINE DISCIPLINE ...@TODO: ISSO DEVE FICAR DENTRO DO KERNEL BASE.
//Esse será o ponto de entrada do line discipline no kernel base,
//o kernelbase receberá uma mensagem do driver de teclado enviando o scancode
//esse scacode passará por essa rotina, então o kernel base deve chamar essa rotina
//apos ter recebido o scacode do driver de teclado.
void LINE_DISCIPLINE(unsigned char SC);


//
// End.
//
