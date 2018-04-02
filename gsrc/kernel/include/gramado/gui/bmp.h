/*
 * File: bmp.h
 *
 * Descrição:
 *     Header para rotinas de bmp.
 *
 *    Versão 2015.
 */
 
#define BMP_TYPE 0x4D42             /* "MB" */

//OFFSETS
#define BMP_OFFSET_WIDTH 18
#define BMP_OFFSET_HEIGHT 22
#define BMP_OFFSET_BITPLANES 26
#define BMP_OFFSET_BITCOUNT 28
//...

typedef struct bmp_header_d bmp_header_t;   
struct bmp_header_d                     
{
    unsigned short bmpType;           /* Magic number for file */
    unsigned long  bmpSize;           /* Size of file */
    unsigned short bmpReserved1;      /* Reserved */
    unsigned short bmpReserved2;      /* ... */
    unsigned long  bmpOffBits;        /* Offset to bitmap data */
};

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
 
 

//mostra na tela uma imagem bmp carregada na memória. 
void bmpDisplayBMP( void *address, unsigned long x, unsigned long y, int width, int height );

void load_bitmap_16x16( unsigned long ax, 
                        unsigned long bx, 
						unsigned long cx, 
						unsigned long dx );
						
void carrega_bitmap_16x16( unsigned long ax, 
                           unsigned long bx, 
						   unsigned long cx, 
						   unsigned long dx );
						   
//
//fim.
//


