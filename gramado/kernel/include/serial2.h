// serial.
// Cuidado. Acho que tem outro arquivo com esse nome.


#ifndef ____KDRIVERS_SERIAL_H
#define ____KDRIVERS_SERIAL_H



// COM ports
#define COM1_PORT 0x3F8 
#define COM2_PORT 0x2F8
#define COM3_PORT 0x3E8
#define COM4_PORT 0x2E8



void serial1_handler (void);
void serial2_handler (void);
void serial3_handler (void);
void serial4_handler (void);

void serial_write_char ( char data );

// Method to init an serial port (for debugging)
void serial_init_port ( uint16_t port );	

int serial_init (void);


#endif   


