

#ifndef __DC_H
#define __DC_H    1


/*
// Losethos colors.
public BGREntry vga_palette4_std[16] = {
    0x000000,0x0000AA,0x00AA00,0x00AAAA,
    0xAA0000,0xAA00AA,0xAA5500,0xAAAAAA,
    0x555555,0x5555FF,0x55FF55,0x55FFFF,
    0xFF5555,0xFF55FF,0xFFFF55,0xFFFFFF };


public BGREntry vga_palette4_gray[16] = {
    0x000000,0x111111,0x222222,0x333333,
    0x444444,0x555555,0x666666,0x777777,
    0x888888,0x999999,0xAAAAAA,0xBBBBBB,
    0xCCCCCC,0xDDDDDD,0xEEEEEE,0xFFFFFF };
*/

#define PALETTE_COUNT_MAX    16

// ===========================

//flags
#define DCF_USE_PALETTE     1
#define DCF_RECORD_EXTENTS  2
#define DCF_CLIPPING        4   // Clipping to a given window.
#define DCF_DONT_DRAW       8
// ...

struct dc_d
{
    int used;
    int magic;

// Buffer
    unsigned char *data;

// z-buffer
    unsigned long *depth_buffer;

    struct gws_display_d *display;

    unsigned long flags;

    unsigned long left;
    unsigned long top;
    unsigned long width;
    unsigned long height;

    unsigned long right;
    unsigned long bottom;

// virtual screen ?
// Record extents.
    unsigned long min_x;
    unsigned long max_x;
    unsigned long min_y;
    unsigned long max_y;


    unsigned long palette[PALETTE_COUNT_MAX];
};

struct dc_d *gr_dc;
struct dc_d *gr_dc1;
struct dc_d *gr_dc2;
// ...

#endif    


