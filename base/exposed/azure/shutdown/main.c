
// 'shutdown' command for Gramado.
// It shuts down the machine via i/o ports
// if we are running on qemu.
// Environment: ring 3 application.
// Created by Fred Nora.

#include <rtl/gramado.h>
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <libio.h>

// #test
// Finding the size of a disk.

#define DRDY  0x40
#define BSY   0x80
#define HOB   0x80

#define Sector_Count    2

#define LBA_Low         3
#define LBA_Mid         4
#define LBA_High        5
#define Device          6

#define Status          7
#define Command         7

#define Device_Control  2

#define is_qemu  rtl_is_qemu


//
// private functions: prototypes ==============
//

static void __serial_write_char (unsigned char data);
static void test_disk_size(void);
void do_via_qemu(void);
  
// ===================================

// Vai escrever em uma porta ja inicializada pelo kernel.
static void __serial_write_char (unsigned char data) 
{
    while (( libio_inport8(0x3F8 + 5) & 0x20 ) == 0)
    {
    };

    libio_outport8 ( 0x3F8, (unsigned char) data );
}


// #
// Essa rotina funcionou no qemu, mas não em minha máquina real.
// Devemos mover ela para dentro do driver em ring0
// e testar novamente.

static void test_disk_size(void)
{
    unsigned int d=0x1F0;   //for example
    unsigned int dd=0x3F4;
    // 0-Master 1-Slave
    char Dev=0; 
    char LBA48=0;
    unsigned long Max_LBA=0;

// ====================================

// Select Device and set LBA.

    libio_outport8(
        (unsigned short) (d+6), 
        (unsigned char) (Dev << 4) + (1 << 6) ); 

// Test device is ready to do comand.
    while (libio_inport8(d+Status) &  DRDY == 0)
    {
    };

    if (LBA48 != 0)
    {
        // READ NATIVE MAX ADDRESS EXT.
        libio_outport8(
            (unsigned short) d+Command, 
            (unsigned char) 0x27 ); 

        // wait command completed
        while (libio_inport8(d+Status) &  BSY != 0)
        {
        };

        Max_LBA =  (unsigned long )libio_inport8(d+LBA_Low);
        Max_LBA += (unsigned long )libio_inport8(d+LBA_Mid)  << 8;
        Max_LBA += (unsigned long )libio_inport8(d+LBA_High) << 16;

        // Set HOB to 1
        libio_outport8(
            dd+Device_Control, 
            HOB ); 

        Max_LBA += (unsigned long )libio_inport8(d+LBA_Low)  << 24;
        Max_LBA += (unsigned long )libio_inport8(d+LBA_Mid)  << 32;
        Max_LBA += (unsigned long )libio_inport8(d+LBA_High) << 40;

    }
    else
    {
        // READ NATIVE MAX ADDRESS
        libio_outport8(
            d+Command, 
            0xF8 ); 
        
        // wait command completed
        while (libio_inport8 (d+Status) &  BSY != 0)
        {
        };

        Max_LBA  = (unsigned long )libio_inport8(d+LBA_Low);
        Max_LBA += (unsigned long )libio_inport8(d+LBA_Mid)  << 8;
        Max_LBA += (unsigned long )libio_inport8(d+LBA_High) << 16;

        Max_LBA += ((unsigned long )libio_inport8(d+Device) & 0xF) <<24;
    }

    printf ("Size {%d}\n",Max_LBA);
}


void do_via_qemu(void)
{
    debug_print ("SHUTDOWN.BIN: [QEMU] Shutting down\n");
    libio_outport16(
        (unsigned short) 0x604, 
        (unsigned short) 0x2000 );
}

// main:
// #test
// Testing shutdown in virtual machines.
// #todo:
// We can ask the system if we are in qemu or not.
// See: https://wiki.osdev.org/Shutdown

int main ( int argc, char *argv[] )
{

// #todo: parameters.
// Or maybe we need a application called poweroff.bin.

/*
 // #test: disk size.
    printf("shutdown:\n");
    test_disk_size();
    printf("done\n");
    while(1){}
*/

// Na verdade essa rotina precisa ser em ring0.
// Pois tem que checar a permissão de superuser,
// acionar os locks, sincronizar os sistemas de arquivo
// montados, etc ...

// #todo
// Podemos testar para outros hv, como kvm ...

    static int isQEMU = FALSE;
    //int isVirtualBox = FALSE;
    //int isBochs      = FALSE;
    

// ==============================
// qemu
// In newer versions of QEMU, you can do shutdown with:
    isQEMU = (int) is_qemu();
    if (isQEMU == TRUE){
        do_via_qemu();
    }

// =========================
// virtualbox
// In Virtualbox, you can do shutdown with:
    //if (isVirtualBox == TRUE){
    //    libio_outport16(0x4004, 0x3400);
    //}

    // bochs
    // In Bochs, and older versions of QEMU(than 2.0), you can do the following:
    //if (isBochs == TRUE){
    //    libio_outport16(0xB004, 0x2000);
    //}

fail:
    printf ("shutdown: [FAIL] Not running on qemu.\n");
    exit(0);
    return (int) (-1);
}


