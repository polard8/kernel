
// see:
// https://wiki.osdev.org/VGA_Hardware

// The VGA hardware interface is very complex, 
// consisting of five controllers and 
// over a hundred hardware registers accessible 
// from the Port I/O address space.
// See: http://www.brokenthorn.com/Resources/OSDevVid2.html

// :::: 
// CRT Controller, 
// Sequencer, 
// Graphics Controller, 
// RAMDAC,
// Video memory, 
// Attribute Controller.

/*
Graphics Registers -- 
    Control the way the CPU accesses video RAM.
Sequencer Registers -- 
    Control how video data is sent to the DAC.
Attribute Controller Registers -- 
    Selects the 16 color and 64 color palettes used for EGA/CGA compatibility.
CRT Controller Registers -- 
    Control how the video is output to the display.
Color Registers -- 
    Selects the 256 color palette from the maximum possible colors.
External Registers -- 
    Miscellaneous registers used to control video operation.
// see: http://www.osdever.net/FreeVGA/vga/vga.htm
*/


// Super vga?
// In order for us to support SuperVGA devices we have only two options:
// + Write a device driver for each type of display device we want to support.
// + Use Vesa Bios Extensions (VBE).


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

#include "vgad.h"




// --------------------------------------

//
// The vga identifiers.
//

// w, h, bpp.
unsigned int VGA_width=0;
unsigned int VGA_height=0;
unsigned int VGA_bpp=0;

// ---------------------------------------------

// Address
unsigned char *VGA_address;


// ===============================================================

/*
 * CREATE THE REGISTER ARRAY 
 * TAKEN FROM http://wiki.osdev.org/VGA_Hardware
 */

unsigned char mode_800_480[] = {

//
// #bugbug
// Actually this configuration is (800x480)
//  Considering multiples of 10 width and 10 height.
//


/* MISC
 * Miscellaneous Output Register
 * 0x63 => 0110 0011
 * 7 6 5 4 3 2 1 0
 * 1 1 0 0 0 1 1 0
 * VSP HSP - - CS CS ERAM IOS
 * 7,6 - 480 lines
 * 5,4 - free
 * 3,2 - 28,322 MHZ Clock (Clock selection)
 * 1 - Enable Ram
 * 0 - Map 0x3d4 to 0x3b4. (if cleared)
 */
// 0xE3 - mode 12h (640x480 planar 16 color mode)
// 0x63 - mode 13h (320x200 linear 256-color mode)
// 0xE3 - mode X   (320x240 planar 256 color mode)

    //0x63,    // 0110 0011     // xlines, free, hz, enable ram, do use the other port.
    0xE3,  // 1100 0011   // 480, free, hz, enable ram, do use the other port.

//-----------------------------
/* SEQ */
/**
 * Index 0x00: - (Reset).
 * 0x03 = 11
 * Bits 1,0 - Synchronous reset.
 */
    0x03,
/**
 * Index 0x01: (Clocking mode).
 * bit 0: (8/9 Dot Clocks).
 * Each character equals 8 (9/8 Dot Mode is set) or 
 * 9 (9/8 Dot Mode is clear) pixels.
 */
    0x01,
/**
 * Index 0x02: (Plane write)(map mask).
 * 0x0F = 1111
 * Enable all 4 Maps Bits 0-3
 * chain 4 mode
 */
    0x0F,
/**
 *  Index 0x03: (Character map).
 * no character map enabled
 */
    0x00,
/**
 * Index 0x04: (Sequencer Memory mode).
 * Enables ch4, odd/even, extended memory
 */
    0x0E,

//-----------------------------
/* CRTC */
// http://martin.hinner.info/vga/timing.html
// By programming this unit you can control the resolution of your monitor, 
// as well as some hardware overlay and panning effects.
// Registers 0-7 of 0x3D4 
// are 'write protected' by the protect bit (bit 7 of index 0x11).
// ----------------
// Horizontal:
// Registers involved in horizontal timing: 
// (0x00~0x05)
// Horizontal timings are based on character clocks (multiples of 8 or 9 pixels)
// ----------------
// Vertical:
// Registers involved in vertical timing:
// (0x06,0x07,0x09,0x10,0x11,0x12,0x15,0x16)
// Vertical timings are per-scanline.
// Since these easily exceed the 255 limit of one byte, 
// the Overflow Register is used to store the high-order bits.

// ----------------
// Horizontal:
// Char width is '10'.

// h  0x00
// Horizontal Total
    0x5F,
// h1 0x01  
// Horizontal Display Enable End 
// (40*8)=320 | (80*8)=640 |(640/8) = 80 = 0x50 (vm) <<<----
// 0x39 ... 64*8=512.
    0x4F,
// h2 0x02  
// Horizontal Blanking Start  
    0x50,
// h  0x03  
// Horizontal Blanking End | 
// Horizontal Display Skew (5.6) | 
// Horizontal Blanking End (bits 0..4) 
// 1000 0010
// '100' '00010'
    0x82,  
// h3 0x04  
// Horizontal retrace pulse start
    0x54,
// h  0x05  
// Horizontal retrace end | 
// H. Blanking End (bit 5) 7? | 
// Horizontal Retrace End (0..4)   1000 0000
    0x80,  

// ----------------
// Vertical:
// Char width is '?'.


    0xBF,  // 0x06 v  vertical total
    0x1F,  // 0x07 v  overflow
    0x00,  // 0x08    present row scan
    0x41,  // 0x09 v  maximum scanline
    0x00,  // 0x0A    cursor start
    0x00,  // 0x0B    cursor end
    0x00,  // 0x0C    start address high  (#bugbug)
    0x00,  // 0x0D    start address low   (#bugbug)
    0x00,  // 0x0E    cursor location high
    0x00,  // 0x0F    cursor location low
    0x9C,  // 0x10 v3 Vertical Retrace Start (bits 0..7)
    0x0E,  // 0x11 v  Vertical Retrace End
// 0x12 v1 
// Vertical Display Enable End 
// (bits 0..7) (vm) <<<----
// 0x39 ... 64*8=512.
// 0x19 ... 32*8=256.
    0x19, //0x39,  //0x8F,  
    0x28,  // 0x13    offset
    0x40,  // 0x14    underline location
    0x96,  // 0x15 v2 Vertical Blanking Start (bits 0..7)
    0xB9,  // 0x16 v  Vertical Blanking End (bits 0..6)
    0xA3,  // 0x17    CRT mode control
    0xFF,  // 0x18    line compare

//-----------------------------
/* GC */
    0x00,  // 0x00  Set/Reset (bits 0~3)
    0x00,  // 0x01  Enable Set/Reset (bits 0~3)
    0x00,  // 0x02  color compare
    0x00,  // 0x03  data rotate
    0x00,  // 0x04  read map select
    0x40,  // 0x05  graphics mode: 256-Color Shift (bit6) | Interleaved Shift (bit 5).
    0x05,  // 0x06  Miscellaneous
    0x0F,  // 0x07  color don't care
    0xFF,  // 0x08  Bit Mask

//-----------------------------
/* AC */
// 0-15: Palette entry register
    0x00,  // 0x00  | start of palette stuff
    0x01,  // 0x01
    0x02,  // 0x02
    0x03,  // 0x03
    0x04,  // 0x04
    0x05,  // 0x05
    0x06,  // 0x06
    0x07,  // 0x07
    0x08,  // 0x08
    0x09,  // 0x09
    0x0A,  // 0x0A
    0x0B,  // 0x0B
    0x0C,  // 0x0C
    0x0D,  // 0x0D
    0x0E,  // 0x0E
    0x0F,  // 0x0F  | end of palette stuff
    0x41,  // 0x10  Mode control
    0x00,  // 0x11  Overscan color Register
    0x0F,  // 0x12  Color Plane Enable
    0x00,  // 0x13  Horizontal Pixel Panning
    0x00   // 0x14  Color Select
};


// ===============================================================

/*
 * CREATE THE REGISTER ARRAY 
 * TAKEN FROM http://wiki.osdev.org/VGA_Hardware
 */

unsigned char mode_320_200[] = {

//
//  Considering multiples of 10 width and 10 height.
//


/* MISC
 * Miscellaneous Output Register
 * 0x63 => 0110 0011
 * 7 6 5 4 3 2 1 0
 * 1 1 0 0 0 1 1 0
 * VSP HSP - - CS CS ERAM IOS
 * 7,6 - 480 lines
 * 5,4 - free
 * 3,2 - 28,322 MHZ Clock (Clock selection)
 * 1 - Enable Ram
 * 0 - Map 0x3d4 to 0x3b4. (if cleared)
 */
// 0xE3 - mode 12h (640x480 planar 16 color mode)
// 0x63 - mode 13h (320x200 linear 256-color mode)
// 0xE3 - mode X   (320x240 planar 256 color mode)

    //0x63,    // 0110 0011     // xlines, free, hz, enable ram, do use the other port.
    0xE3,  // 1100 0011   // 480, free, hz, enable ram, do use the other port.

//-----------------------------
/* SEQ */
/**
 * Index 0x00: - (Reset).
 * 0x03 = 11
 * Bits 1,0 - Synchronous reset.
 */
    0x03,
/**
 * Index 0x01: (Clocking mode).
 * bit 0: (8/9 Dot Clocks).
 * Each character equals 8 (9/8 Dot Mode is set) or 
 * 9 (9/8 Dot Mode is clear) pixels.
 */
    0x01,
/**
 * Index 0x02: (Plane write)(map mask).
 * 0x0F = 1111
 * Enable all 4 Maps Bits 0-3
 * chain 4 mode
 */
    0x0F,
/**
 *  Index 0x03: (Character map).
 * no character map enabled
 */
    0x00,
/**
 * Index 0x04: (Sequencer Memory mode).
 * Enables ch4, odd/even, extended memory
 */
    0x0E,

//-----------------------------
/* CRTC */
// http://martin.hinner.info/vga/timing.html
// By programming this unit you can control the resolution of your monitor, 
// as well as some hardware overlay and panning effects.
// Registers 0-7 of 0x3D4 
// are 'write protected' by the protect bit (bit 7 of index 0x11).
// ----------------
// Horizontal:
// Registers involved in horizontal timing: 
// (0x00~0x05)
// Horizontal timings are based on character clocks (multiples of 8 or 9 pixels)
// ----------------
// Vertical:
// Registers involved in vertical timing:
// (0x06,0x07,0x09,0x10,0x11,0x12,0x15,0x16)
// Vertical timings are per-scanline.
// Since these easily exceed the 255 limit of one byte, 
// the Overflow Register is used to store the high-order bits.

// ----------------
// Horizontal:
// Char width is '10'.

// h  0x00
// Horizontal Total
    0x5F,
// h1 0x01  
// Horizontal Display Enable End 
// (40*8)=320 | (80*8)=640 |(640/8) = 80 = 0x50 (vm) <<<----
// 0x39 ... 64*8=512.
// 0x4F = 800, considering granularity of 10 in width.
// 0x41 = 640, considering granularity of 10 in width.
    0x41,

// h2 0x02  
// Horizontal Blanking Start  
    0x50,
// h  0x03  
// Horizontal Blanking End | 
// Horizontal Display Skew (5.6) | 
// Horizontal Blanking End (bits 0..4) 
// 1000 0010
// '100' '00010'
    0x82,  
// h3 0x04  
// Horizontal retrace pulse start
    0x54,
// h  0x05  
// Horizontal retrace end | 
// H. Blanking End (bit 5) 7? | 
// Horizontal Retrace End (0..4)   1000 0000
    0x80,  

// ----------------
// Vertical:
// Char width is '?'.


    0xBF,  // 0x06 v  vertical total
    0x1F,  // 0x07 v  overflow
    0x00,  // 0x08    present row scan
    // 0x41 = 640, considering granularity of 10 in height.
    // 0x30 = 480, considering granularity of 10 in height.
    // Isso mudou a resolução para h=48 h=0x30
    0x30,  // 0x09 v  maximum scanline
    0x00,  // 0x0A    cursor start
    0x00,  // 0x0B    cursor end
    0x00,  // 0x0C    start address high  (#bugbug)
    0x00,  // 0x0D    start address low   (#bugbug)
    0x00,  // 0x0E    cursor location high
    0x00,  // 0x0F    cursor location low
    0x9C,  // 0x10 v3 Vertical Retrace Start (bits 0..7)
    0x0E,  // 0x11 v  Vertical Retrace End
// 0x12 v1 
// Vertical Display Enable End 
// (bits 0..7) (vm) <<<----
// 0x39 ... 64*8=512.
// 0x19 ... 32*8=256.
    0x19, //0x39,  //0x8F,  
    0x28,  // 0x13    offset
    0x40,  // 0x14    underline location
    0x96,  // 0x15 v2 Vertical Blanking Start (bits 0..7)
    0xB9,  // 0x16 v  Vertical Blanking End (bits 0..6)
    0xA3,  // 0x17    CRT mode control
    0xFF,  // 0x18    line compare

//-----------------------------
/* GC */
    0x00,  // 0x00  Set/Reset (bits 0~3)
    0x00,  // 0x01  Enable Set/Reset (bits 0~3)
    0x00,  // 0x02  color compare
    0x00,  // 0x03  data rotate
    0x00,  // 0x04  read map select
    0x40,  // 0x05  graphics mode: 256-Color Shift (bit6) | Interleaved Shift (bit 5).
    0x05,  // 0x06  Miscellaneous
    0x0F,  // 0x07  color don't care
    0xFF,  // 0x08  Bit Mask

//-----------------------------
/* AC */
// 0-15: Palette entry register
    0x00,  // 0x00  | start of palette stuff
    0x01,  // 0x01
    0x02,  // 0x02
    0x03,  // 0x03
    0x04,  // 0x04
    0x05,  // 0x05
    0x06,  // 0x06
    0x07,  // 0x07
    0x08,  // 0x08
    0x09,  // 0x09
    0x0A,  // 0x0A
    0x0B,  // 0x0B
    0x0C,  // 0x0C
    0x0D,  // 0x0D
    0x0E,  // 0x0E
    0x0F,  // 0x0F  | end of palette stuff
    0x41,  // 0x10  Mode control
    0x00,  // 0x11  Overscan color Register
    0x0F,  // 0x12  Color Plane Enable
    0x00,  // 0x13  Horizontal Pixel Panning
    0x00   // 0x14  Color Select
};

// ============================================================
static void serial_write_char (char data);

// vga
static void write_registers(void);
void VGA_clear_screen(void);
void VGA_init(int width, int height, int bpp);
// ============================================================


// ======================================================

// isso eh uma rotina de test
// Vai escrever em uma porta ja inicializada pelo kernel.
static void serial_write_char (char data) 
{
    while (( libio_inport8(0x3F8 + 5) & 0x20 ) == 0);

    libio_outport8 (0x3F8, data);
}

// #todo: 
// The DAC is still in an undefined state. 
static void write_registers(void)
{
    unsigned int i=0;


// #todo
// + Create a system message for 'resolution change notification'
// + Send it to the kernel and the kernel send it to the display server.
// #todo
// Or maybe we can connect this driver with the display server,
// and send requests to the server.

// #tests
    unsigned char *regs = (unsigned char *) &mode_800_480[0];
    //unsigned char *regs = (unsigned char *) &mode_320_200[0];

    printf ("write_registers:\n");

// ===============================
// Step1:
// Write MISCELLANEOUS reg.
// 0x3C2

    printf ("Step 1\n");

    // 0xE3 (640x480)
    libio_outport8(VGA_MISC_WRITE, *regs);
    regs++;

// ===============================
// Step2:
// Write SEQUENCER regs.
// 0x3C4 0x3C5

    printf ("Step 2\n");

   for (i=0; i < VGA_NUM_SEQ_REGS; i++)
   {
      libio_outport8(VGA_SEQ_INDEX, i);
      libio_outport8(VGA_SEQ_DATA, *regs);
      regs++;
   };

// ===============================
// Step3:
// CRTC
/* unlock CRTC registers */

    printf ("Step 3\n");

   libio_outport8(VGA_CRTC_INDEX, 0x03);
   libio_outport8(VGA_CRTC_DATA, libio_inport8(VGA_CRTC_DATA) | 0x80);
   libio_outport8(VGA_CRTC_INDEX, 0x11);
   libio_outport8(VGA_CRTC_DATA, libio_inport8(VGA_CRTC_DATA) & ~0x80);
/* make sure they remain unlocked */
   // #bugbug:  <<< ---
   // #danger_danger
   // Take care about this indexes.
   // What is exactly the 'positions' we are changing the values.
   regs[0x03] |= 0x80;
   regs[0x11] &= ~0x80;
/* write CRTC regs */
   for(i = 0; i < VGA_NUM_CRTC_REGS; i++)
   {
      libio_outport8(VGA_CRTC_INDEX, i);
      libio_outport8(VGA_CRTC_DATA, *regs);
      regs++;
   };

// ===============================
// Step4:
// Write GRAPHICS CONTROLLER regs.

    printf ("Step 4\n");

    for(i = 0; i < VGA_NUM_GC_REGS; i++)
    {
        libio_outport8(VGA_GC_INDEX, i);
        libio_outport8(VGA_GC_DATA, *regs);
        regs++;
    };

// ===============================
// Step5:
// Write ATTRIBUTE CONTROLLER regs.
// This port is a confusing one: 
// You write both the index and data bytes to the same port.

    printf ("Step 5\n");

    for(i = 0; i < VGA_NUM_AC_REGS; i++)
    {
        (void)libio_inport8(VGA_INSTAT_READ);
        libio_outport8(VGA_AC_INDEX, i);
        libio_outport8(VGA_AC_WRITE, *regs);
        regs++;
     };
// Lock 16-color palette and unblank display 
    (void)libio_inport8(VGA_INSTAT_READ);
    libio_outport8(VGA_AC_INDEX, 0x20);

// DAC - pallete
// 0x3c8 - write index.
// 0x3c9 - data.
// To write a color, write the color index to port 0x3C8, 
// then write 3 bytes to 0x3C9 in the order red, green, blue.
    //libio_outport8(0x3c8,0x00); // Color index in the pallete.
    //libio_outport8(0x3c9,0x3f); // r
    //libio_outport8(0x3c9,0x3f); // g
    //libio_outport8(0x3c9,0x3f); // b
}

/**
* Clears the VGA screen
*/
void VGA_clear_screen(void)
{

// #bugbug
// We're a ring 3 application.
// We can't write in this memory address.

   unsigned int x=0;
   unsigned int y=0;

    //#debug
    printf ("VGA_clear_screen: #todo\n");
    return;

/*
    for(y=0; y<VGA_height; y++)
    {
        for (x=0; x<VGA_width; x++)
        {
            VGA_address[ VGA_width*y+x ] = 0x0f;
        };
    };
*/

}


/*
 * ------------------------------------------------------------------
 * VGA_init:
 *     320x200x256.
 *     Note here the vga struct must have 
 *     the width 320 and 
 *     height of 200
 *    color mode is 256.
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

// #bugbug
// We can't write on this address from ring3.
   VGA_address = 0xA0000;

// Enables the mode 13 state
   write_registers();


// Clears the screen
   //VGA_clear_screen();
}

// ======================================================
// main

int main(int argc, char *argv[])
{
    char *env_host;
    char *env_user;
    unsigned char good=0;

    //gramado_system_call(65,'3',0,0);
    printf ("VGAD.BIN:\n");

// #test
// In Virtualbox: 
// + It only changes the height to 300.
// + Tested on VBoxVGA only.
// #todo: 
// Test on VMSVGA.
// QEMU/QEMUkvm: 
// It doesn't change the resolution at all.

    VGA_init(320,200,256);


// Return
    printf ("VGAD.BIN: Done\n");    
    return 0;

    printf ("VGA1.BIN: Done #hang\n");
    while(1){
    };


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


