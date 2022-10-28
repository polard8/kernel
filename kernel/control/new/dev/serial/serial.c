
// serial.c

#include <kernel.h>

//see: serial.h
struct serial_port_info_d SerialPortInfo;

static int serial_init_port(uint16_t port, uint16_t divisor);

// ---------------------------

void serial1_handler (void)
{
    debug_print("serial1_handler:\n");
}

void serial2_handler (void)
{
    debug_print("serial2_handler:\n");
}

void serial3_handler (void)
{
    debug_print("serial3_handler:\n");
}

void serial4_handler (void)
{
    debug_print("serial4_handler:\n");
}


//=====================================
unsigned int serial_in(unsigned int base, int offset)
{
    return (unsigned int) in8(base + offset);
}

void serial_out(unsigned int base, int offset, int value)
{
    out8(value, base + offset);
}
//====================================


// # We don't have debug messages in this routine. 
static int serial_init_port(uint16_t port, uint16_t divisor)
{
    int PortBase = (int) (port & 0xFFFF);

    //unsigned long value = 115200;

// #todo
// Isso sera usado mais abaixo para configurarmos o baud rate.
    uint16_t divisorShort = (uint16_t) divisor;
    char divisorLoByte = (char) (divisorShort & 0xFF);
    char divisorHiByte = (char) ((divisorShort >> 8) & 0xFF);

    //#test
    if(PortBase == COM1_PORT)
    {
        SerialPortInfo.com1.port_number = (uint16_t) port;
        SerialPortInfo.com1.divisor = (uint16_t) divisorShort;
        SerialPortInfo.com1.divisorLoByte = (char) divisorLoByte;
        SerialPortInfo.com1.divisorHiByte = (char) divisorHiByte;
        if(divisorShort>0){
            SerialPortInfo.com1.baudrate = (unsigned long) (115200/divisorShort);
        }
    }
    //#test
    if(PortBase == COM2_PORT)
    {
        SerialPortInfo.com2.port_number = (uint16_t) port;
        SerialPortInfo.com2.divisor = (uint16_t) divisorShort;
        SerialPortInfo.com2.divisorLoByte = (char) divisorLoByte;
        SerialPortInfo.com2.divisorHiByte = (char) divisorHiByte;
        if(divisorShort>0){
            SerialPortInfo.com2.baudrate = (unsigned long) (115200/divisorShort);
        }
    }
    //#test
    if(PortBase == COM3_PORT)
    {
        SerialPortInfo.com3.port_number = (uint16_t) port;
        SerialPortInfo.com3.divisor = (uint16_t) divisorShort;
        SerialPortInfo.com3.divisorLoByte = (char) divisorLoByte;
        SerialPortInfo.com3.divisorHiByte = (char) divisorHiByte;
        if(divisorShort>0){
            SerialPortInfo.com3.baudrate = (unsigned long) (115200/divisorShort);
        }
    }
    //#test
    if(PortBase == COM4_PORT)
    {
        SerialPortInfo.com4.port_number = (uint16_t) port;
        SerialPortInfo.com4.divisor = (uint16_t) divisorShort;
        SerialPortInfo.com4.divisorLoByte = (char) divisorLoByte;
        SerialPortInfo.com4.divisorHiByte = (char) divisorHiByte;
        if(divisorShort>0){
            SerialPortInfo.com4.baudrate = (unsigned long) (115200/divisorShort);
        }
    }


// Se não é alguma das bases possiveis.
// #todo: Existem máquinas com mais do que 4 portas seriais?

    if ( PortBase != COM1_PORT &&
         PortBase != COM2_PORT &&
         PortBase != COM3_PORT &&
         PortBase != COM4_PORT )
    {
        // #bugbug
        // E se falhar aqui ???
        // We can't use panic yet.
        // We have no serial debug.
        
        return (int) (-1);
    }

// Disable all interrupts
    out8 (PortBase + 1, 0x00);  

// Set baud rate.
// Baud Rate
// The serial controller (UART) has an internal clock 
// which runs at 115200 ticks per second and a clock divisor 
// which is used to control the baud rate. 
// This is exactly the same type of system used by 
// the Programmable Interrupt Timer (PIT).
// In order to set the speed of the port, 
// calculate the divisor required for the given baud rate and 
// program that in to the divisor register. 
// For example, a divisor of 1 will give 115200 baud, 
// a divisor of 2 will give 57600 baud, 3 will give 38400 baud, etc.
// Do not be tempted to use a divisor of 0.
// =============
// To set the divisor to the controller:
// > Set the most significant bit of the Line Control Register. 
//   This is the DLAB bit, 
//   and allows access to the divisor registers.
// > Send the least significant byte of the divisor value to [PORT + 0].
// > Send the most significant byte of the divisor value to [PORT + 1].
// > Clear the most significant bit of the Line Control Register. 
// #define LCR  3
// See: serial.h
// credits: https://wiki.osdev.org/Serial_Ports

// Enable DLAB (set baud rate divisor)
    out8 (PortBase + LCR, 0x80);  


// #todo:
// Colocar aqui os bytes do divisor.
// Cuidade para não colocar invertido.
// Set divisor to 3 (lo byte) 38400 baud (hi byte)
    out8 (PortBase + 0, divisorLoByte);  // low ? 
    out8 (PortBase + 1, divisorHiByte);  // hi?
    //out8 (PortBase + 0, 0x03);  // low  ? 
    //out8 (PortBase + 1, 0x00);  // hi ?


// In the next command we will clear the msb of the LCR.
// ======================

// Line Protocol
// These days you could consider 
// 8N1 (8 bits, no parity, one stop bit) pretty much the default. 
// 8 bits, no parity, one stop bit
    out8 (PortBase + LCR, 0x03);  

// Enable FIFO, clear then with 14-byte threshold
// #define FCR  2
    out8 (PortBase + FCR, 0xC7);  

// IRQs enables, RTS/DSR set
// modem control register
// #define MCR   4 
    out8 (PortBase + MCR, 0x0B);  

    return 0;
}


// serial_init:
// inicializa todas as portas.
// #IMPORTANT:
// We can't use debug in this first initialization.
// We can't use serial debug. It's because the serial port support
// is not working yet. :)
// # We don't have debug messages in this routine.

int serial_init(void)
{
    int Status = -1;

    Initialization.serial_log = FALSE;

    //__breaker_com1_initialized = 0;
    //__breaker_com2_initialized = 0;
    //__breaker_com3_initialized = 0;
    //__breaker_com4_initialized = 0;

    Status = serial_init_port(COM1_PORT,3);
    if (Status != 0){
        return -1;
    }
    Status = serial_init_port(COM2_PORT,3);
    if (Status != 0){
        return -1;
    }
    Status = serial_init_port(COM3_PORT,3);
    if (Status != 0){
        return -1;
    }
    Status = serial_init_port(COM4_PORT,3);
    if (Status != 0){
        return -1;
    }

    //__breaker_com1_initialized = 1;
    //__breaker_com2_initialized = 1;
    //__breaker_com3_initialized = 1;
    //__breaker_com4_initialized = 1;

    Initialization.serial_log = TRUE;
    return 0;
}


// serial_write_char:
// NOT tested yet.
char serial_read_char(unsigned int port) 
{

// #todo
// Check the port validation.

    while ( ( in8(port + 5) & 1 ) == 0 )
    {
        // Nothing
    };

    return (char) in8(port);
}


// serial_write_char:
void serial_write_char(unsigned int port, char data) 
{

// #todo
// Check the port validation.

    while (( in8(port + 5) & 0x20 ) == 0)
    {
        // Nothing
    };

    out8(port,data);
}


// Print string
// IN: port, string pointer.
void serial_print (unsigned int port, char *data )
{
    register int i=0;

// #todo
// Check the port validation.

    for ( i=0; data[i] != '\0'; i++ )
    {
        serial_write_char ( port ,data[i] );
    };
}


// Only COM1_PORT.
void debug_print_string(char *data)
{
    register int i=0;

    for ( i=0; data[i] != '\0'; i++ )
    {
        serial_write_char( COM1_PORT ,data[i] );
    };
}


// #todo
// We need a ioctl for serial devices.
int serial_ioctl ( int fd, unsigned long request, unsigned long arg )
{
    debug_print("serial_ioctl: [TODO]\n");

    if(fd<0){
        return -1;
    }

    return -1;
}

