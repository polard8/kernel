

#ifndef __HALVID_H
#define __HALVID_H    1



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

    // basically the same as above.
    struct screen_d *screen;

    //...
};

// Te info comes from the gramado boot loader.
struct display_device_d *GramadoDisplayDevice;
//struct display_device_d *QemuDisplayDevice;


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


void vsync (void);

#endif    


