/*
 * File: dd/nhid/serial/serial.c
 *
 * Credits: 
 *     Chicago OS. (Ítalo Lima Marconato Matias). 
 *   
 *     2019 - Document created by Fred Nora.
 */


// See:
// https://wiki.osdev.org/Serial_Ports
// ...


//COM Port IO Port
//COM1     0x3F8
//COM2     0x2F8
//COM3     0x3E8
//COM4     0x2E8 


// #remember:
// We can connect some server to a serial port.

#include <kernel.h>




void serial1_handler (void)
{

    // Se a porta não estiver inicializado !
    if ( __breaker_com1_initialized == 0 )
        return;


    // #test
    // IN: device type and data.
    // 1=keyboard
    // 2=COM port
    console_interrupt(
        foreground_thread,
        CONSOLE_DEVICE_SERIAL,
        0 );
    
    //
    // profiler
    //
    
	// Contando as interrupções desse tipo.
    g_profiler_ints_irq4++;
}


void serial2_handler (void)
{
	// Se a porta não estiver inicializado !
    if ( __breaker_com2_initialized == 0 )
        return;


    // #test
    // IN: device type and data.
    // 1=keyboard
    // 2=COM port
    console_interrupt(
        foreground_thread,
        CONSOLE_DEVICE_SERIAL,
        0 );

    //
    // profiler
    //
    
	// Contando as interrupções desse tipo.
    g_profiler_ints_irq3++;	
}


//#todo
void serial3_handler (void)
{
	// Se a porta não estiver inicializado !
    if ( __breaker_com3_initialized == 0 )
        return;

    // #test
    // IN: device type and data.
    // 1=keyboard
    // 2=COM port
    console_interrupt(
        foreground_thread,
        CONSOLE_DEVICE_SERIAL,
        0);
}


//#todo
void serial4_handler (void)
{
	// Se a porta não estiver inicializado !
    if ( __breaker_com4_initialized == 0 )
        return;

    // #test
    // IN: device type and data.
    // 1=keyboard
    // 2=COM port
    console_interrupt(foreground_thread,CONSOLE_DEVICE_SERIAL,0);
}

//=====================================


unsigned int serial_in(unsigned int base, int offset)
{
    return (unsigned int) in8 (base + offset);
}

void serial_out(unsigned int base, int offset, int value)
{
    out8 (value, base + offset);
}
//====================================


/*
 * serial_write_char:
 *     NOT tested yet.
 */

char serial_read_char (unsigned int port) 
{
    while (( in8(port + 5) & 1 ) == 0);

    return (char) in8 (port);
}


/*
 * serial_write_char:
 * 
 */

void serial_write_char (unsigned int port, char data) 
{
    while (( in8(port + 5) & 0x20 ) == 0);

    out8 (port, data);
}


void serial_print (unsigned int port, char *data )
{
    register int i=0;
    
    for ( i=0; data[i] != '\0'; i++ )
    {
        serial_write_char ( port ,data[i] );
    };
}



/*
// Write something from tty to a serial port.
void serial_write ( struct tty_d * tty, int port );
void serial_write ( struct tty_d * tty, int port )
{
    char data;
    
    //#todo: Get char from tty.
    //data = tty->
    
    serial_write_char ( (int) port, (char) data ); 
}
*/



/*
 ******************************
 * serial_init_port:
 * 
 */

// #bugbug
// #IMPORTANTE
// Essa função apresenta problemas de compilação
// quando incluímos mais código.

// See:
// See the type for the argument in the function out8.
// gramado/kernel/bottom/hal/arch/x86/portsx86.c

int serial_init_port ( uint16_t port ){

    int PortBase=0;
    
    PortBase = (int) port;


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
        
        return -1;
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

    // Set divisor to 3 (lo byte) 38400 baud (hi byte)
    out8 (PortBase + 0, 0x03);  
    out8 (PortBase + 1, 0x00);
    
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



/*
 ******************
 * serial_init:
 * 
 */
 
// inicializa todas as portas.

// #IMPORTANT:
// We can't use debug in this first initialization.
// We can't use serial debug. It's because the serial port support
// is not working yet. :)

int serial_init (void){

    int Status = -1;
    
    __breaker_com1_initialized = 0;
    __breaker_com2_initialized = 0;
    __breaker_com3_initialized = 0;
    __breaker_com4_initialized = 0;

    Status = serial_init_port (COM1_PORT);
    if (Status != 0)
        return -1;
    
    Status = serial_init_port (COM2_PORT);
    if (Status != 0)
        return -1;
    
    Status = serial_init_port (COM3_PORT);
    if (Status != 0)
        return -1;
    
    Status = serial_init_port (COM4_PORT);
    if (Status != 0)
        return -1;

    __breaker_com1_initialized = 1;
    __breaker_com2_initialized = 1;
    __breaker_com3_initialized = 1;
    __breaker_com4_initialized = 1;

    return 0;
}




// #todo
// We need a ioctl for serial devices.
int serial_ioctl ( int fd, unsigned long request, unsigned long arg )
{
    debug_print("serial_ioctl: [TODO]\n");
    return -1;
}




/*
//credits: osdev
//Initialization
#define PORT 0x3f8  //COM1
void init_serial() {
   outb(PORT + 1, 0x00);    // Disable all interrupts
   outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
   outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
   outb(PORT + 1, 0x00);    //                  (hi byte)
   outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
   outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
   outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}
*/



//
// End.
//



