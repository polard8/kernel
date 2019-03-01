
// serial.c

// osdev stuff 

//COM Port	IO Port
//COM1	0x3F8
//COM2	0x2F8
//COM3	0x3E8
//COM4	0x2E8

#define PORT 0x3f8   /* COM1 */
 
 
//Initialization 
void init_serial() {
   outb(PORT + 1, 0x00);    // Disable all interrupts
   outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
   outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
   outb(PORT + 1, 0x00);    //                  (hi byte)
   outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
   outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
   outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}

//Receiving data

int serial_received() {
   return inb(PORT + 5) & 1;
}
 
char read_serial() {
   while (serial_received() == 0);
 
   return inb(PORT);
}



//Sending data

int is_transmit_empty() {
   return inb(PORT + 5) & 0x20;
}
 
void write_serial(char a) {
   while (is_transmit_empty() == 0);
 
   outb(PORT,a);
}


//
// =======================================
//

//again 

//
// SERIAL
//
//

extern void serialirq();


unsigned int serial_received(unsigned short PORT) 
{
   return inportb(PORT + 5) & 1;
}
 
unsigned char read_serial(unsigned short PORT) 
{
   while (serial_received(PORT) == 0);
 
   return inportb(PORT);
}

int is_transmit_empty(unsigned short PORT) {
   return inportb(PORT + 5) & 0x20;
}
 
void write_serial(char a,unsigned short PORT) {
   while (is_transmit_empty(PORT) == 0);
 
   outportb(PORT,a);
}


//You use IRQ #4 for COM ports 1 or 3, 
//and IRQ #3 for COM ports 2 or 4 
//(you can tell which port sent the interrupt when you receive the interrupt).
void irq_serial ()
{
	
	//port1
	unsigned char binnengekomen = read_serial(0x3f8);
	putc(binnengekomen);
	outportb(0x20,0x20);
}

void init_serial_device  (unsigned short PORT){
	
   outportb(PORT + 1, 0x00);    // Disable all interrupts
   outportb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
   outportb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
   outportb(PORT + 1, 0x00);    //                  (hi byte)
   outportb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
   outportb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
   outportb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
   outportb(PORT + 1, 1);
   
   setNormalInt ( 4, (unsigned long) serialirq );
};

void init_serial(){
	init_serial_device(0x3f8);
}


///=======


void init_serial_port ( int n )
{
	if ( n < 1 || n > 4 )
	    return;

    switch (n)
	{
		case 1:
		    init_serial_device(0x3f8);
		    break;
			
		case 2:
		    init_serial_device(0x2F8);
			break;

		case 3:
		    init_serial_device(0x3E8);
		    break;

		case 4:
		    init_serial_device(0x2E8);
		    break;

	}	
};



