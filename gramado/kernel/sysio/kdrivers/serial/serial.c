// credits: Ítalo Lima Marconato Matias


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




void serial_write_char ( char data ) {
	
	while (( in8(COM1_PORT + 5) & 0x20 ) == 0) ;
	
	out8 (COM1_PORT, data);
}


void serial_init_port ( uint16_t port ){

    // ??
    // Qual foi inicializada ??
    
    out8 (port + 1, 0x00);								// Disable all interrupts
    out8 (port + 3, 0x80);								// Enable DLAB (set baud rate divisor)
    out8 (port + 0, 0x03);								// Set divisor to 3 (lo byte) 38400
															// baud (hi byte)
    out8 (port + 1, 0x00);
    out8 (port + 3, 0x03);								// 8 bits, no parity, one stop bit
    out8 (port + 2, 0xC7);								// Enable FIFO, clear then with
															// 14-byte threshold
    out8 (port + 4, 0x0B);								// IRQs enables, RTS/DSR set

}


// inicializa todas as portas.
int serial_init (void)
{

    __breaker_com1_initialized = 0;
    __breaker_com2_initialized = 0;
    __breaker_com3_initialized = 0;
    __breaker_com4_initialized = 0;
    
    serial_init_port (COM1_PORT);
    serial_init_port (COM2_PORT);
    serial_init_port (COM3_PORT);
    serial_init_port (COM4_PORT);


    __breaker_com1_initialized = 1;
    __breaker_com2_initialized = 1;
    __breaker_com3_initialized = 1;
    __breaker_com4_initialized = 1;

    return 0;
}





