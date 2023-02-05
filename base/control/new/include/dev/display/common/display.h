
// display.h
// Display device support.

#ifndef __COMMON_DISPLAY_H
#define __COMMON_DISPLAY_H    1

// Local boot structure.
struct x_boot_block_d
{
    int initialized;
    unsigned long lfb_pa;
    unsigned long deviceWidth;    // in pixels
    unsigned long deviceHeight;   // in pixels
    unsigned long bpp;            // bytes per pixel
    unsigned long last_valid_pa;  // Last valid physical address.
    unsigned long gramado_mode;   // system mode.
    // ...
};

// see: globals.c, init.c, bldisp.c
extern struct x_boot_block_d  xBootBlock;


struct display_device_d
{
    int used;
    int magic;
    // The file to handle this device.
    file *_file;
    //char name[64];
//
// LFB - Linear Frame Buffer
//
    unsigned long framebuffer_pa;
    unsigned long framebuffer_va;
    unsigned long framebuffer_width;
    unsigned long framebuffer_height;
    unsigned long framebuffer_bpp;
    // How many bytes in a single row.
    unsigned long framebuffer_pitch;
    // used for allocations.
    unsigned long framebuffer_size_in_bytes;

    // FILE *fp;

    //...    

    struct display_device_d *next;
};



/*
  * Video mode:
 *     Modo de vídeo usado.
 *     //@todo: se estamos encapsulando no módulo, retirar o G de global.
 */

unsigned long g_video_mode;    


//
// Graphic mode support.
//
 
typedef struct tagGraphics Graphics_t;
struct tagGraphics
{
    unsigned long LFB;
    //unsigned long Backbuffer;
    //...
};
Graphics_t *Graphics;


//
// Video support
//

/*
 * video_d:
 *     Estrutura para informações sobre parâmetros de vídeo.
 */

typedef struct video_d VideoBlock_t;
typedef struct video_d video_t;

struct video_d
{
    object_type_t  objectType;
    object_class_t objectClass;

	//call back ;d

    int useGui;   //se estamos ou não usando gui. text mode, video mode.
    int vgaMode;  //número do modo de vídeo se estiver usando vga.
    int vesaMode; //número do modo vesa.
	//int 
	//...

	//unsigned long flag;  //
	//unsigned long error; //

    // currente video memory. 
    // Ponteiro para a base atual da memoria de video em text mode.
    unsigned long currentVM; 
    char ch;           //caractere.
    char chAtrib;      //atributo do caractere. 
	//...    

    //unsigned long Display[32];    //Ponteiros para as telas.
};
struct video_d  VideoBlock;
//video_t VideoBlock;
//...


//
// == prototypes =================================
//

#endif    


