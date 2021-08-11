/*
 * File: bmp.h
 *
 *    Header para rotinas de BMP.
 *
 * History:
 *    2015 - Created by Fred Nora.
 *           24bpp support. 
 *    2018 - 4bpp, 8bpp, 32bpp support.
 */
 
 
/* "MB" */ 
#define BMP_TYPE 0x4D42        
 
#define  BMP_CHANGE_COLOR_NULL  0
#define  BMP_CHANGE_COLOR_TRANSPARENT  1000
#define  BMP_CHANGE_COLOR_SUBSTITUTE   2000
//...
  
 
//flag que avisa que dve haver alguma mudança nas cores. 
int bmp_change_color_flag; 
 
//salva-se aqui uma cor para substituir outra. 
unsigned long bmp_substitute_color; 
 
//cor selecionada para ser substituída ou ignorada. 
unsigned long bmp_selected_color; 








//
// ## BMP support ##
//

#define GWS_BMP_TYPE 0x4D42             /* "MB" */

//OFFSETS
#define GWS_BMP_OFFSET_WIDTH 18
#define GWS_BMP_OFFSET_HEIGHT 22
#define GWS_BMP_OFFSET_BITPLANES 26
#define GWS_BMP_OFFSET_BITCOUNT 28
//...

//typedef struct bmp_header_d bmp_header_t;   
struct gws_bmp_header_d                     
{
    unsigned short bmpType;           /* Magic number for file */
    unsigned long  bmpSize;           /* Size of file */
    unsigned short bmpReserved1;      /* Reserved */
    unsigned short bmpReserved2;      /* ... */
    unsigned int   bmpOffBits;        /* Offset to bitmap data */
};

//typedef struct bmp_infoheader_d bmp_infoheader_t;   
struct gws_bmp_infoheader_d                     
{
    unsigned int  bmpSize;           /* Size of info header */
    unsigned int  bmpWidth;          /* Width of image */
    unsigned int  bmpHeight;         /* Height of image */
    unsigned short bmpPlanes;         /* Number of color planes */
    unsigned short bmpBitCount;       /* Number of bits per pixel */
    unsigned int  bmpCompression;    /* Type of compression to use */
    unsigned int  bmpSizeImage;      /* Size of image data */
    unsigned int  bmpXPelsPerMeter;  /* X pixels per meter */
    unsigned int  bmpYPelsPerMeter;  /* Y pixels per meter */
    unsigned int  bmpClrUsed;        /* Number of colors used */
    unsigned int  bmpClrImportant;   /* Number of important colors */
};
 


//
// Pointer.
//

char *gwssrv_bmp_cursor_pointer;
char *gwssrv_bmp_mouse_pointer;
// ...




/*
 ******************************************************
 * bmpDisplayBMP:
 *
 * Mostra na tela uma imagem bmp carregada na memória. no backbuffer()
 * 
 * IN:
 *     address = endereço base
 *     x       = posicionamento 
 *     y       = posicionamento
 */
 
int 
bmpDisplayBMP ( 
    char *address, 
    unsigned long x, 
    unsigned long y );



void *gwssrv_get_system_icon(int n);

//void __test_load_bmp2(void);
int gwssrv_display_system_icon ( int index, unsigned long x, unsigned long y );


//
// End.
//


