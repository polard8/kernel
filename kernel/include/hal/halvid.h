

#ifndef __HALVID_H
#define __HALVID_H    1

// #bugbug: We have new addresses
// 
//#define LFB_BASE        0xC0400000 
//#define BACKBUFFER_BASE 0xC0800000

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


