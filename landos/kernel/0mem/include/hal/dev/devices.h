
// #order
// Organizar os dispositivos na seguintem ordem
// Character devices, Block devices and Network interfaces


#ifndef ____DEVICES_H
#define ____DEVICES_H


//
//    ==== Character devices ====
//

// Serial.
//struct tty_d *ttyS0;
//struct tty_d *ttyS1;
//struct tty_d *ttyS2;
//struct tty_d *ttyS3;


// Virtual consoles.
//struct tty_d *tty0;
//struct tty_d *tty1;


// ps2keyboard
// ps2mouse


//
//    ==== Block devices ====
//


// vfs
// ata


//
//    ==== Network interfaces ====
//

//e1000


#define MAJOR(a) (((unsigned)(a))>>8)
#define MINOR(a) ((a)&0xff)


#endif    


