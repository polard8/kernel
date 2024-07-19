// serial.c
// This is the serial port driver, embedded into the kernel base.
// Created by Fred Nora.

// credits: 
// https://wiki.osdev.org/Serial_Ports

#include <kernel.h>

//see: serial.h
struct serial_port_info_d SerialPortInfo;
static int serial_init_port(uint16_t port, uint16_t divisor);

// ---------------------------

void serial1_handler(void)
{
    debug_print("serial1_handler:\n");
}

void serial2_handler(void)
{
    debug_print("serial2_handler:\n");
}

void serial3_handler(void)
{
    debug_print("serial3_handler:\n");
}

void serial4_handler(void)
{
    debug_print("serial4_handler:\n");
}

unsigned int serial_in(unsigned int base, int offset)
{
    return (unsigned int) in8(base + offset);
}

void serial_out(unsigned int base, int offset, int value)
{
    out8(value, base + offset);
}

// Initialize a single port.
// # We don't have debug messages in this routine. 
static int serial_init_port(uint16_t port, uint16_t divisor)
{
    int PortBase = (int) (port & 0xFFFF);
    uint16_t divisorShort = (uint16_t) divisor;
    char divisorLoByte = (char) (divisorShort & 0xFF);
    char divisorHiByte = (char) ((divisorShort >> 8) & 0xFF);

// Is it an invalid port number?
// We do not have support por error messages.
// We can't use panic yet.
// #todo: Check if we can use x_panic.
    if ( PortBase != COM1_PORT && 
         PortBase != COM2_PORT &&
         PortBase != COM3_PORT &&
         PortBase != COM4_PORT )
    {
        return (int) FALSE;
    }

// Null divisor or out of range.
// Use default divisor value.
// 115200/3 = 38400;
    if (divisorShort == 0 || divisorShort > SERIAL_DEV_FREQ)
    {
        divisorShort = 3;
        divisorLoByte = (char) (divisorShort & 0xFF);
        divisorHiByte = (char) ((divisorShort >> 8) & 0xFF);
    }

// COM1
    if (PortBase == COM1_PORT){
        SerialPortInfo.com1.port_number = (uint16_t) port;
        SerialPortInfo.com1.divisor = (uint16_t) divisorShort;
        SerialPortInfo.com1.divisorLoByte = (char) divisorLoByte;
        SerialPortInfo.com1.divisorHiByte = (char) divisorHiByte;
        SerialPortInfo.com1.dev_freq = SERIAL_DEV_FREQ; //115200
        if (divisorShort>0){
            SerialPortInfo.com1.baudrate = 
                (unsigned long) (SERIAL_DEV_FREQ/divisorShort);
        }
    }
// COM2
    if (PortBase == COM2_PORT){
        SerialPortInfo.com2.port_number = (uint16_t) port;
        SerialPortInfo.com2.divisor = (uint16_t) divisorShort;
        SerialPortInfo.com2.divisorLoByte = (char) divisorLoByte;
        SerialPortInfo.com2.divisorHiByte = (char) divisorHiByte;
        SerialPortInfo.com2.dev_freq = SERIAL_DEV_FREQ; //115200
        if (divisorShort>0){
            SerialPortInfo.com2.baudrate = 
                (unsigned long) (SERIAL_DEV_FREQ/divisorShort);
        }
    }
// COM3
    if (PortBase == COM3_PORT){
        SerialPortInfo.com3.port_number = (uint16_t) port;
        SerialPortInfo.com3.divisor = (uint16_t) divisorShort;
        SerialPortInfo.com3.divisorLoByte = (char) divisorLoByte;
        SerialPortInfo.com3.divisorHiByte = (char) divisorHiByte;
        SerialPortInfo.com3.dev_freq = SERIAL_DEV_FREQ; //115200
        if (divisorShort>0){
            SerialPortInfo.com3.baudrate = 
                (unsigned long) (SERIAL_DEV_FREQ/divisorShort);
        }
    }
// COM4
    if (PortBase == COM4_PORT){
        SerialPortInfo.com4.port_number = (uint16_t) port;
        SerialPortInfo.com4.divisor = (uint16_t) divisorShort;
        SerialPortInfo.com4.divisorLoByte = (char) divisorLoByte;
        SerialPortInfo.com4.divisorHiByte = (char) divisorHiByte;
        SerialPortInfo.com4.dev_freq = SERIAL_DEV_FREQ; //115200
        if (divisorShort>0){
            SerialPortInfo.com4.baudrate = 
                (unsigned long) (SERIAL_DEV_FREQ/divisorShort);
        }
    }

// #todo
// Explain this routine.
// See: tty/serial.h

// Disable all interrupts
    out8 (PortBase + 1, 0x00);  // IER ?
// Set baud rate.
// Enable DLAB (set baud rate divisor)
    out8 (PortBase + LCR, 0x80);  
// Set divisor bytes.
    out8 (PortBase + 0, divisorLoByte);  //low 
    out8 (PortBase + 1, divisorHiByte);  //hi
// In the next command we will clear the msb of the LCR.
// Line Protocol
    out8 (PortBase + LCR, 0x03);
// Enable FIFO, clear then with 14-byte threshold
    out8 (PortBase + FCR, 0xC7);
// IRQs enables, RTS/DSR set and modem control register.
    out8 (PortBase + MCR, 0x0B);
    return TRUE;
}

// serial_write_char:
// NOT tested yet.
char serial_read_char(unsigned int port) 
{

// #todo
// Check the port validation.

    while ( (in8(port + 5) & 1) == 0 )
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

// #todo
// Parameters:
    if (fd < 0){
        goto fail;
    }
// ...

// #todo: ...

    //switch (xxx)
    //{
    // ...
    //};

fail:
    return (int) -1;
}


// DDINIT_serial:
// inicializa todas as portas.
// #IMPORTANT:
// We can't use debug in this first initialization.
// We can't use serial debug. It's because the serial port support
// is not working yet. :)
// # We don't have debug messages in this routine.
// OUT: TRUE or FALSE.
int DDINIT_serial(void)
{
// Called by preinit_Serial() in main.c

    int Status = FALSE;
    uint16_t DefaultDivisor = 3;  // 115200/3 = 38400;

    Initialization.is_serial_log_initialized = FALSE;

    //__breaker_com1_initialized = 0;
    //__breaker_com2_initialized = 0;
    //__breaker_com3_initialized = 0;
    //__breaker_com4_initialized = 0;

    Status = serial_init_port(COM1_PORT,DefaultDivisor);
    if (Status != TRUE){
        goto fail;
    }
    Status = serial_init_port(COM2_PORT,DefaultDivisor);
    if (Status != TRUE){
        goto fail;
    }
    Status = serial_init_port(COM3_PORT,DefaultDivisor);
    if (Status != TRUE){
        goto fail;
    }
    Status = serial_init_port(COM4_PORT,DefaultDivisor);
    if (Status != TRUE){
        goto fail;
    }

    //__breaker_com1_initialized = 1;
    //__breaker_com2_initialized = 1;
    //__breaker_com3_initialized = 1;
    //__breaker_com4_initialized = 1;

    Initialization.is_serial_log_initialized = TRUE;
    return TRUE;
fail:
    return FALSE;
}

//
// End
//

