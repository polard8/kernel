/*
 * File: dd/nhid/serial/serial.c
 *
 * Credits: 
 *     Chicago OS. (Ítalo Lima Marconato Matias). 
 *   
 *     2019 - Document created by Fred Nora.
 */

// #remember:
// We can connect some server to a serial port.

#include <kernel.h>



void serial1_handler (void)
{

    // Se a porta não estiver inicializado !
    if ( __breaker_com1_initialized == 0 )
        return;
	
	
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
}


//#todo
void serial4_handler (void)
{
	// Se a porta não estiver inicializado !
    if ( __breaker_com4_initialized == 0 )
        return;

}



/*
 * serial_write_char:
 *     #bugbug:
 *     It writes only in the port COM1_PORT.
 *     Maybe we can select the port.
 */

void 
serial_write_char ( char data ) 
{

    while (( in8(COM1_PORT + 5) & 0x20 ) == 0);

    out8 (COM1_PORT, data);
}

/*
void 
serial_write_char ( int port, char data ) 
{

    //#check
    //if ( port ...

    while (( in8(port + 5) & 0x20 ) == 0) ;
    
    out8 (port, data);
}
*/


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
        return -1;
    }


    // ??
    // Qual foi inicializada ??
    
    out8 (PortBase + 1, 0x00);  // Disable all interrupts
    out8 (PortBase + 3, 0x80);  // Enable DLAB (set baud rate divisor)
    out8 (PortBase + 0, 0x03);  // Set divisor to 3 (lo byte) 38400 baud (hi byte)


    out8 (PortBase + 1, 0x00);
    out8 (PortBase + 3, 0x03);  // 8 bits, no parity, one stop bit
    out8 (PortBase + 2, 0xC7);  // Enable FIFO, clear then with 14-byte threshold


    out8 (PortBase + 4, 0x0B);  // IRQs enables, RTS/DSR set
    
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


/*
int 
serial_ioctl ( 
    int fd, 
    unsigned long request, 
    unsigned long arg );
int 
serial_ioctl ( 
    int fd, 
    unsigned long request, 
    unsigned long arg )
{
}
*/

//
// End.
//



