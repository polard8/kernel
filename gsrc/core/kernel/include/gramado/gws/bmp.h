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
 
/* ## Cancelada ! ## */
static unsigned long cga_16colors_palette[1] = { 0x000000, };

/* ## Cancelada ! ## */
static unsigned long vga_256colors_palette[1] = { 0x00000000, };



/* "MB" */ 
#define BMP_TYPE 0x4D42             

//OFFSETS
#define BMP_OFFSET_WIDTH 18
#define BMP_OFFSET_HEIGHT 22
#define BMP_OFFSET_BITPLANES 26
#define BMP_OFFSET_BITCOUNT 28
//...


/*
 * bmp_header_d:
 *     Header.
 */
typedef struct bmp_header_d bmp_header_t;   
struct bmp_header_d                     
{
    unsigned short bmpType;           /* Magic number for file */
    unsigned long  bmpSize;           /* Size of file */
    unsigned short bmpReserved1;      /* Reserved */
    unsigned short bmpReserved2;      /* ... */
    unsigned long  bmpOffBits;        /* Offset to bitmap data */
};


/*
 * bmp_infoheader_d:
 *     Info header. 
 */
typedef struct bmp_infoheader_d bmp_infoheader_t;   
struct bmp_infoheader_d                     
{
    unsigned long  bmpSize;           /* Size of info header */
    unsigned long  bmpWidth;          /* Width of image */
    unsigned long  bmpHeight;         /* Height of image */
    unsigned short bmpPlanes;         /* Number of color planes */
    unsigned short bmpBitCount;       /* Number of bits per pixel */
    unsigned long  bmpCompression;    /* Type of compression to use */
    unsigned long  bmpSizeImage;      /* Size of image data */
    unsigned long  bmpXPelsPerMeter;  /* X pixels per meter */
    unsigned long  bmpYPelsPerMeter;  /* Y pixels per meter */
    unsigned long  bmpClrUsed;        /* Number of colors used */
    unsigned long  bmpClrImportant;   /* Number of important colors */
};
 
 

/*
 ******************************************************
 * bmpDisplayBMP:
 *
 * Mostra na tela uma imagem bmp carregada na memória.
 * 
 * IN:
 *     address = endereço base
 *     x       = posicionamento 
 *     y       = posicionamento
 *
 */
int bmpDisplayBMP( char *address, 
                   unsigned long x, 
				   unsigned long y );
				   
int bmpDisplayMousePointerBMP( char *address, 
                               unsigned long x, 
				               unsigned long y );
					
						   
//
// End.
//


