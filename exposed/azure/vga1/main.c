// 'reboot' command for Gramado.

// rtl
#include <rtl/gramado.h>
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// libio
#include <libio.h>


//define the ports , taken from http://files.osdev.org/mirrors/geezer/osd/graphics/modes.c
#define   VGA_AC_INDEX      0x3C0
#define   VGA_AC_WRITE      0x3C0
#define   VGA_AC_READ         0x3C1
#define   VGA_MISC_WRITE      0x3C2
#define VGA_SEQ_INDEX      0x3C4
#define VGA_SEQ_DATA      0x3C5
#define   VGA_DAC_READ_INDEX   0x3C7
#define   VGA_DAC_WRITE_INDEX   0x3C8
#define   VGA_DAC_DATA      0x3C9
#define   VGA_MISC_READ      0x3CC
#define VGA_GC_INDEX       0x3CE
#define VGA_GC_DATA       0x3CF
#define VGA_CRTC_INDEX      0x3D4      /* 0x3B4 */
#define VGA_CRTC_DATA      0x3D5      /* 0x3B5 */
#define   VGA_INSTAT_READ      0x3DA
#define   VGA_NUM_SEQ_REGS   5
#define   VGA_NUM_CRTC_REGS   25
#define   VGA_NUM_GC_REGS      9
#define   VGA_NUM_AC_REGS      21
#define   VGA_NUM_REGS      (1+VGA_NUM_SEQ_REGS+VGA_NUM_CRTC_REGS+VGA_NUM_GC_REGS+VGA_NUM_AC_REGS)


//the vga identifiers
unsigned int VGA_width=0;
unsigned int VGA_height=0;
unsigned int VGA_bpp=0;
unsigned char *VGA_address;

/**
* CREATE THE REGISTER ARRAY TAKEN FROM http://wiki.osdev.org/VGA_Hardware
*/

unsigned char mode_320_200_256[] = {

   /* MISC
    *
    * 0x63 => 01100011
    * 7 6 5 4 3 2 1 0
    * 1 1 0 0 0 1 1 0
    * VSP HSP - - CS CS ERAM IOS
    * 7,6 - 480 lines
    * 5,4 - free
    * 3,2 - 28,322 MHZ Clock
    * 1 - Enable Ram
    * 0 - Map 0x3d4 to 0x3b4
    */
   0x63,
   /* SEQ */
   /**
    * index 0x00 - Reset
    * 0x03 = 11
    * Bits 1,0 Synchronous reset
    */
   0x03,
   /**
    * index 0x01
    * Clocking mode register
    * 8/9 Dot Clocks
    */
   0x01,
   /**
    * Map Mask Register, 0x02
    * 0x0F = 1111
    * Enable all 4 Maps Bits 0-3
    * chain 4 mode
    */
   0x0F,
   /**
    * map select register, 0x03
    * no character map enabled
    */
   0x00,
   /**
    * memory mode register 0x04
    * enables ch4,odd/even,extended memory
    */
   0x0E,
   /* CRTC */
   0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
   0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x9C, 0x0E, 0x8F, 0x28,   0x40, 0x96, 0xB9, 0xA3,
   0xFF,
   /* GC */
   0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,
   0xFF,
   /* AC */
   0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
   0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
   0x41, 0x00, 0x0F, 0x00,   0x00
};

// ============================================================
static void serial_write_char (char data);

// vga
void write_registers(unsigned char *regs);
void VGA_clear_screen(void);
void VGA_init(int width, int height, int bpp);
// ============================================================


// #todo: 
// The DAC is still in an undefined state. 
void write_registers(unsigned char *regs)
{
    unsigned int i;

    printf ("write_registers:\n");

/* write MISCELLANEOUS reg */
   libio_outport8(VGA_MISC_WRITE, *regs);
   regs++;

/* write SEQUENCER regs */
   for (i=0; i < VGA_NUM_SEQ_REGS; i++)
   {
      libio_outport8(VGA_SEQ_INDEX, i);
      libio_outport8(VGA_SEQ_DATA, *regs);
      regs++;
   }

/* unlock CRTC registers */
   libio_outport8(VGA_CRTC_INDEX, 0x03);
   libio_outport8(VGA_CRTC_DATA, libio_inport8(VGA_CRTC_DATA) | 0x80);
   libio_outport8(VGA_CRTC_INDEX, 0x11);
   libio_outport8(VGA_CRTC_DATA, libio_inport8(VGA_CRTC_DATA) & ~0x80);
/* make sure they remain unlocked */
   regs[0x03] |= 0x80;
   regs[0x11] &= ~0x80;

/* write CRTC regs */
   for(i = 0; i < VGA_NUM_CRTC_REGS; i++)
   {
      libio_outport8(VGA_CRTC_INDEX, i);
      libio_outport8(VGA_CRTC_DATA, *regs);
      regs++;
   }

/* write GRAPHICS CONTROLLER regs */
   for(i = 0; i < VGA_NUM_GC_REGS; i++)
   {
      libio_outport8(VGA_GC_INDEX, i);
      libio_outport8(VGA_GC_DATA, *regs);
      regs++;
   }

/* write ATTRIBUTE CONTROLLER regs */
   for(i = 0; i < VGA_NUM_AC_REGS; i++)
   {
      (void)libio_inport8(VGA_INSTAT_READ);
      libio_outport8(VGA_AC_INDEX, i);
      libio_outport8(VGA_AC_WRITE, *regs);
      regs++;
   }
   
/* 
 * lock 16-color palette and unblank display 
 */
   (void)libio_inport8(VGA_INSTAT_READ);
   libio_outport8(VGA_AC_INDEX, 0x20);

// colors?
    //libio_outport8(0x3c8,0x00);
    //libio_outport8(0x3c9,0x3f);
    //libio_outport8(0x3c9,0x3f);
    //libio_outport8(0x3c9,0x3f);
}


/**
* Clears the VGA screen
*/
void VGA_clear_screen(void)
{
   unsigned int x=0;
   unsigned int y=0;

    printf ("VGA_clear_screen:\n");
    
    for(y=0; y<VGA_height; y++)
    {
        for (x=0; x<VGA_width; x++)
        {
            VGA_address[ VGA_width*y+x ] = 0x0f;
        };
    };
}


/**
* Note here the vga struct must have 
* the width 320 and 
* height of 200
* color mode is 256.
*/

void 
VGA_init(
    int width, 
    int height, 
    int bpp )
{
    printf ("VGA_init:\n");
    
   //setup the vga struct
   VGA_width  = (unsigned int) (width & 0xFFFF);
   VGA_height = (unsigned int) (height & 0xFFFF);
   VGA_bpp    = (bpp & 0xFF);

   VGA_address = 0xA0000;

//enables the mode 13 state
   write_registers( mode_320_200_256 );

   //clears the screen
   //VGA_clear_screen();
}


// ======================================================

// isso eh uma rotina de test
// Vai escrever em uma porta ja inicializada pelo kernel.
static void serial_write_char (char data) 
{
    while (( libio_inport8(0x3F8 + 5) & 0x20 ) == 0);

    libio_outport8 (0x3F8, data);
}


//
// main
//

int main ( int argc, char *argv[] )
{
    char *env_host;
    char *env_user;
    unsigned char good=0;

    //gramado_system_call(65,'3',0,0);

    printf ("VGA1.BIN:\n");

    VGA_init(320,200,256);

    while(1){}
    //asm("int $3");




   /*
   //=================
   // testing read() stdin
    char buf[32];
    int n;
    while(1){

       //sprintf(buf,"durty");
       //write(0,buf,5);

       n = read(0,buf,1);
       if(n>0)
           printf(">>>>%c\n",buf[0]);
    }
   //=================
   */


    // ==============================================


    // #test
    // Testing shutdown in virtual machines.
    // #todo:
    // We can ask the system if we are in qemu or not.
    // See: https://wiki.osdev.org/Shutdown


     //int isQEMU = FALSE;
     //isQEMU = rtl_get_system_metrics(300);


    // In Bochs, and older versions of QEMU(than 2.0), you can do the following:
    // outw(0xB004, 0x2000);
    // libio_outport16(0xB004, 0x2000);

    // In newer versions of QEMU, you can do shutdown with:
    //if (isQEMU==TRUE){
        // outw(0x604, 0x2000);
    //    libio_outport16(0x604, 0x2000);
    //}


    // In Virtualbox, you can do shutdown with:
    // outw(0x4004, 0x3400);
    // libio_outport16(0x4004, 0x3400);


    // #status
    // OK. it is working on qemu. 
    
    // ==============================================

    //testing serial port
    //ok isso funcionou.
    serial_write_char('r');
    serial_write_char('e');
    serial_write_char('b');
    serial_write_char('o');
    serial_write_char('o');
    serial_write_char('t');
    serial_write_char('i');
    serial_write_char('n');
    serial_write_char('g');
    serial_write_char('.');
    serial_write_char('.');
    serial_write_char('.');


    puts        ("\n");
    printf      ("REBOOT.BIN: Rebooting ...\n");
    debug_print ("REBOOT.BIN: Rebooting ...\n");
    
    // #test
    // using the stadard method.
    goto via_rtl;
    //goto via_libio;


    // get info from crt0.o

    env_host = (char *) getenv("HOSTNAME");
    env_user = (char *) getenv("USER");

    // Showing the info.
    
    if ( (void *) env_host != NULL ){
        printf ("Host name:  %s \n", env_host);
    }

    if ( (void *) env_user != NULL ){
        printf ("User:       %s \n", env_user);
    }

    printf ("Good Bye!\n");


    //===================================
    // reboot via libio.
via_libio:
    printf ("reboot via libio\n");
    good = 0x02;
    while (good & 0x02){
        good = libio_inport8(0x64);
    };

    debug_print("reboot.bin: Go!\n");
         printf("reboot.bin: Go!\n");
    
    libio_outport8(0x64, 0xFE);
    //halt();       
     
    debug_print("reboot.bin: via_libio fail\n");
         printf("reboot.bin: via_libio fail\n");


    //===================================
    // reboot via rtl
via_rtl:
    printf ("reboot via rtl\n");
    debug_print("reboot.bin: Go!\n");
         printf("reboot.bin: Go!\n");
    rtl_reboot();
    exit(1);

    return (int) (-1);
}


