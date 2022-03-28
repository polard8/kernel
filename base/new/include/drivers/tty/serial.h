// serial.h


#ifndef ____SERIAL_H
#define ____SERIAL_H

// COM ports
#define COM1_PORT  0x3F8 
#define COM2_PORT  0x2F8
#define COM3_PORT  0x3E8
#define COM4_PORT  0x2E8

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

//
// == prototypes ==============================================
//

void serial1_handler (void);
void serial2_handler (void);
void serial3_handler (void);
void serial4_handler (void);

int serial_init_port ( uint16_t port );
int serial_init (void);

char serial_read_char (unsigned int port);
void serial_write_char (unsigned int port, char data);

void serial_print (unsigned int port, char *data );

void debug_print_string ( char *data );

unsigned int serial_in(unsigned int base, int offset);
void serial_out(unsigned int base, int offset, int value);

int serial_ioctl ( int fd, unsigned long request, unsigned long arg );

#endif    


















