// libata.h


#ifndef __DD_HDD_H
#define __DD_HDD_H    1


/*
// #test: Not in use.
struct hdd_d
{
    int dummy;
};
*/


// --------------------------

// White lba on ide device.
void write_lba( unsigned long address, unsigned long lba );
// Read lba on ide device.
void read_lba( unsigned long address, unsigned long lba );

void 
my_read_hd_sector ( 
    unsigned long ax, 
    unsigned long bx, 
    unsigned long cx, 
    unsigned long dx ); 

void 
my_write_hd_sector ( 
    unsigned long ax, 
    unsigned long bx, 
    unsigned long cx, 
    unsigned long dx ); 

// Read or write a sector using PIO mode.
int 
pio_rw_sector ( 
    unsigned long buffer, 
    unsigned long lba, 
    int rw, 
    int port,
    int slave ); 

#endif   

