
// serial.h


#ifndef ____SERIAL_H
#define ____SERIAL_H


// See:
// https://wiki.osdev.org/Serial_Ports
// https://wiki.osdev.org/Serial_Port

// glossary:
// UART
// for Universal Asynchronous Receiver/Transceiver: 
// the chip that picks a byte a send it bit per bit on the serial line 
// and vice versa. 


/*
UART (Universal Asynchronous Receiver/Transmitter), 
 A UART transforma em serial a saída paralela do barramento do computador, 
 para realizar a transmissão via porta serial. 
 
 A maioria dos chips UART possui um buffer embutido entre 16 e 64 kilobytes.
 
 Portas seriais de alta velocidade como a Enhanced Serial Port (ESP) e a 
 Super Enhanced Serial Port (Super ESP) 
 
O conector externo para uma porta serial pode ser tanto de 9 como de 25 pinos.
 Originalmente, a utilização principal de uma porta serial era conectar um modem ao computador. 
 As funções dos pinos refletem isso. 



Conector de 9 pinos:
1. Detector de portadora (carrier detect) - determina se o modem está conectado a uma linha telefônica em operação. 
2. Recebimento de dados (receive data) - o computador recebe as informações enviadas pelo modem. 
3. Transmissão de dados (transmit data) - o computador envia informações ao modem. 
4. Terminal pronto (data terminal ready) - o computador avisa ao modem que está pronto para se comunicar. 
5. Sinal de terra (signal ground) - pino ligado a terra. 
6. Modem pronto (data set ready) - o modem avisa ao computador que está pronto para se comunicar. 
7. Solicitação de envio (request to send) - o computador pergunta ao modem se pode enviar informações. 
8. Pronto para enviar (clear to send) - o modem avisa ao computador que as informações podem ser enviadas. 
9. Indicador de sinal (ring indicator) - assim que a ligação é estabelecida, 
o computador reconhece o aviso (enviado pelo modem) que indica que o sinal foi detectado.


controle de fluxo?

*/


/*
  Headless Server viar Serial Port:
  =================================
  
  A headless system is a computer system or device that has been configured to 
  operate without a monitor (the missing "head"), keyboard, and mouse. 
  A headless system is typically controlled via a network connection, 
  although some headless system devices require a serial connection to be made 
  via RS-232 for administration of the device. Headless operation of a server is 
  typically employed to reduce operating costs.
  Obs: RS-232  Serial port.
  
 Headless computers and other remotely controlled hardware devices often operate 
 using network control models.

 */





// COM ports
#define COM1_PORT  0x3F8 
#define COM2_PORT  0x2F8
#define COM3_PORT  0x3E8
#define COM4_PORT  0x2E8



//static unsigned long early_serial_base = 0x3f8;  /* ttyS0 */
//static unsigned long early_serial_base = COM1_PORT;  /* ttyS0 */


#define XMTRDY          0x20
#define DLAB            0x80
#define TXR             0       /*  Transmit register (WRITE) */
#define RXR             0       /*  Receive register  (READ)  */
#define IER             1       /*  Interrupt Enable          */
#define IIR             2       /*  Interrupt ID              */
#define FCR             2       /*  FIFO control              */
#define LCR             3       /*  Line control              */
#define MCR             4       /*  Modem control             */
#define LSR             5       /*  Line Status               */
#define MSR             6       /*  Modem Status              */
#define DLL             0       /*  Divisor Latch Low         */
#define DLH             1       /*  Divisor latch High        */

//Offset |Setting of DLAB |Register mapped to this port
//+0      0                Data register. 
                           // Reading this registers read from the Receive buffer. 
                           // Writing to this register writes to the Transmit buffer.
//+1      0                Interrupt Enable Register.
//+0      1                With DLAB set to 1, 
                           // this is the least significant byte of the divisor value for setting the baud rate.
//+1      1                With DLAB set to 1, 
                           // this is the most significant byte of the divisor value.
//+2      -                Interrupt Identification and FIFO control registers
//+3      -                Line Control Register. The most significant bit of this register is the DLAB.
//+4      -                Modem Control Register.
//+5      -                Line Status Register.
//+6      -                Modem Status Register.
//+7      -                Scratch Register. 



// #define SERIAL_INTERNAL_CLOCK_HZ 115200
// #define DEFAULT_BAUD 9600


/*
typedef struct serial_port_d serial_port_t;
struct serial_port_d
{
	//Object.
	object_type_t objectType;
	object_class_t objectClass;
	
	int z;
	
	//...
	
	unsigned long flag;  //f
	unsigne dlong error; //e
	
    struct serial_port_d *next;	
};
serial_port_t *SerialPort;
//...
*/



int serialportError;
//...



//
// == prototypes ==============================================
//

void serial1_handler (void);
void serial2_handler (void);
void serial3_handler (void);
void serial4_handler (void);

//===================

unsigned int serial_in(unsigned int base, int offset);
void serial_out(unsigned int base, int offset, int value);

//==========================

char serial_read_char (unsigned int port);
void serial_write_char (unsigned int port, char data);

void serial_print (unsigned int port, char *data );


// Method to init an serial port (for debugging)
int serial_init_port ( uint16_t port );	

int serial_init (void);

int serial_ioctl ( int fd, unsigned long request, unsigned long arg );


#endif   



//
// End.
//


