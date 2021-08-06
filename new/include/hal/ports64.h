


#ifndef __PORTS64_H
#define __PORTS64_H    1


// IO Delay.
#define io_delay() asm("out %%al,$0x80"::);

unsigned char in8 (unsigned int port);
unsigned short in16 (unsigned int port);
unsigned int in32 (unsigned int port);
void out8 ( unsigned int port, unsigned char data );
void out16 (unsigned int port, unsigned short data);
void out32 ( unsigned int port, unsigned int data );


void __x86_io_delay (void);

void wait_ns(int count);

//
// para acesso via user mode.
//

unsigned int portsx86_IN ( int bits, unsigned int port );
void 
portsx86_OUT ( 
    int bits, 
    unsigned int port, 
    unsigned int value );




#endif   


