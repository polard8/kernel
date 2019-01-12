


#define COM1_PORT 0x3F8				// COM ports
#define COM2_PORT 0x2F8
#define COM3_PORT 0x3E8
#define COM4_PORT 0x2E8

//#include </types.h>


void serial_write_char ( char data );

// Method to init an serial port (for debugging)
void init_serial ( uint16_t port );	


