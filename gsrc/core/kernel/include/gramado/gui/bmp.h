/*
 * File: bmp.h
 *
 * Descrição:
 *     Header para rotinas de bmp.
 *
 *    Versão 2015.
 */
 
/*

// Hardware text mode color constants.
enum vga_color {
    COLOR_BLACK             = 0,
    COLOR_BLUE              = 1,
    COLOR_GREEN             = 2,
    COLOR_CYAN              = 3,
    COLOR_RED               = 4,
    COLOR_MAGENTA           = 5,
    COLOR_BROWN             = 6,
    COLOR_LIGHT_GREY        = 7,
    COLOR_DARK_GREY         = 8,
    COLOR_LIGHT_BLUE        = 9,
    COLOR_LIGHT_GREEN       = 10,
    COLOR_LIGHT_CYAN        = 11,
    COLOR_LIGHT_RED         = 12,
    COLOR_LIGHT_MAGENTA     = 13,
    COLOR_LIGHT_BROWN       = 14,
    COLOR_WHITE             = 15,
};
 
*/ 
 
/* 
#define COLOR_BLACK 
#define COLOR_BLUE 
#define COLOR_GREEN 
#define COLOR_CYAN 
#define COLOR_RED 
#define COLOR_MAGENTA 
#define COLOR_BROWN 
#define COLOR_LIGHT_GREY 

#define COLOR_DARK_GREY 
#define COLOR_LIGHT_BLUE 
#define COLOR_LIGHT_GREEN 
#define COLOR_LIGHT_CYAN 
#define COLOR_LIGHT_RED 
#define COLOR_LIGHT_MAGENTA 
#define COLOR_LIGHT_BROWN 
#define COLOR_WHITE 
*/ 

static unsigned long cga_16colors_palette[16] = {
	
	//Paleta do paint para 4bpp
	0x00000000, // 
	0x80000000, // 
	0x00800000, // 
	0x80800000, // 
	0x00008000, // 
	0x80008000, // 
	0x00808000, // 
	0x80808000, // 
	
	0xC0C0C000, // 
	0xFF000000, // 
	0x00FF0000, // 
	0xFFFF0000, // 
	0x0000FF00, // 
	0xFF00FF00, // 
	0x00FFFF00, // 
	0xFFFFFF00  // 
};



static unsigned long vga_256colors_palette[256] = {
	
//black
0x00000000, 
0x00000000, 
0x00000000, 
0x00000000, 
0x00000000, 
0x00000000, 
0x00000000, 
0x00000000, 
0x00000000, 
0x00000000, 
0x00000000, 
0x00000000, 
0x00000000, 
0x00000000, 
0x00000000, 
0x00000000, 
	
	
//blue	
0x0000CC00, 
0x0000CD00,	
0x0000D000,	
0x0000D100,	
0x0000D200,	
0x0000D300,	
0x0000D400,	
0x0000D500,	
0x0000D600,
0x0000D700,
0x0000D800,
0x0000D900,
0x0000DA00,
0x0000DB00,
0x0000DC00,
0x0000DD00,	
	
	
	
 //green
0x00CC0000, 
0x00CD0000,	
0x00D00000,	
0x00D10000,	
0x00D20000,	
0x00D30000,	
0x00D40000,	
0x00D50000,	
0x00D60000,
0x00D70000,
0x00D80000,
0x00D90000,
0x00DA0000,
0x00DB0000,
0x00DC0000,
0x00DD0000,	



0x00AAAA00, //cyan 
0x00AAAA00, //cyan 
0x00AAAA00, //cyan 
0x00AAAA00, //cyan 	
0x00AAAA00, //cyan 
0x00AAAA00, //cyan 
0x00AAAA00, //cyan 
0x00AAAA00, //cyan 	
0x00AAAA00, //cyan 
0x00AAAA00, //cyan 
0x00AAAA00, //cyan 
0x00AAAA00, //cyan 	
0x00AAAA00, //cyan 
0x00AAAA00, //cyan 
0x00AAAA00, //cyan 
0x00AAAA00, //cyan 	


	
//red	
0xCC000000, 
0xCD000000,	
0xD0000000,	
0xD1000000,	
0xD2000000,	
0xD3000000,	
0xD4000000,	
0xD5000000,	
0xD6000000,
0xD7000000,
0xD8000000,
0xD9000000,
0xDA000000,
0xDB000000,
0xDC000000,
0xDD000000,	
	
	
	
	
	
0xAA00AA00, //magenta
0xAA00AA00, //magenta
0xAA00AA00, //magenta
0xAA00AA00, //magenta
0xAA00AA00, //magenta
0xAA00AA00, //magenta
0xAA00AA00, //magenta
0xAA00AA00, //magenta
0xAA00AA00, //magenta
0xAA00AA00, //magenta
0xAA00AA00, //magenta
0xAA00AA00, //magenta
0xAA00AA00, //magenta
0xAA00AA00, //magenta
0xAA00AA00, //magenta
0xAA00AA00, //magenta


0xAA550000,  //brown
0xAA550000,  //brown
0xAA550000,  //brown
0xAA550000,  //brown
0xAA550000,  //brown
0xAA550000,  //brown
0xAA550000,  //brown
0xAA550000,  //brown
0xAA550000,  //brown
0xAA550000,  //brown
0xAA550000,  //brown
0xAA550000,  //brown
0xAA550000,  //brown
0xAA550000,  //brown
0xAA550000,  //brown
0xAA550000,  //brown


0xAAAAAA00,  //light gray
0xAAAAAA00,  //light gray
0xAAAAAA00,  //light gray
0xAAAAAA00,  //light gray
0xAAAAAA00,  //light gray
0xAAAAAA00,  //light gray
0xAAAAAA00,  //light gray
0xAAAAAA00,  //light gray
0xAAAAAA00,  //light gray
0xAAAAAA00,  //light gray
0xAAAAAA00,  //light gray
0xAAAAAA00,  //light gray
0xAAAAAA00,  //light gray
0xAAAAAA00,  //light gray
0xAAAAAA00,  //light gray
0xAAAAAA00,  //light gray

	
	//gray
0x00000000, //#define xCOLOR_BLACK   //preto
0x20202000, //#define xCOLOR_GRAY1   //cinza mais escuro
0x40404000, //#define xCOLOR_GRAY2   //cinza
0x60606000, //#define xCOLOR_GRAY3   //cinza
0x80808000, //#define xCOLOR_GRAY4   //cinza
0xa0a0a000, //#define xCOLOR_GRAY5   //cinza
0xb0b0b000,
0xc0c0c000, //#define xCOLOR_GRAY6   //cinza
0xd8d8d800,
0xd9d9d900,
0xdadada00,
0xdbdbdb00,
0xdcdcdc00,
0xdddddd00,
0xe0e0e000, //#define xCOLOR_GRAY7   //cinza mais clarinho
0xffffff00, //#define xCOLOR_WHITE   //branco 	
	

	
//light blue
0x5555CB00, 
0x5555CC00,
0x5555D000,
0x5555D100,
0x5555D200,
0x5555D300,
0x5555D400,
0x5555D500,
0x5555D600,
0x5555D700,
0x5555D800,
0x5555D900,
0x5555DA00,	
0x5555DB00,
0x5555DC00,
0x5555DD00,	
	
	
//light green	
0x55CB5500, 
0x55CC5500,
0x55D05500,
0x55D15500,
0x55D25500,
0x55D35500,
0x55D45500,
0x55D55500,
0x55D65500,
0x55D75500,
0x55D85500,
0x55D95500,
0x55DA5500,	
0x55DB5500,
0x55DC5500,
0x55DD5500,	
	
	
	
		
	0x55FFFF00, //light cyan
	0x55FFFF00, //light cyan
	0x55FFFF00, //light cyan
	0x55FFFF00, //light cyan
	0x55FFFF00, //light cyan
	0x55FFFF00, //light cyan
	0x55FFFF00, //light cyan
	0x55FFFF00, //light cyan
	0x55FFFF00, //light cyan
	0x55FFFF00, //light cyan
	0x55FFFF00, //light cyan
	0x55FFFF00, //light cyan
	0x55FFFF00, //light cyan
	0x55FFFF00, //light cyan
	0x55FFFF00, //light cyan
	0x55FFFF00, //light cyan
	
	
//light red
0xCB555500, 
0xCC555500,
0xD0555500,
0xD1555500,
0xD2555500,
0xD3555500,
0xD4555500,
0xD5555500,
0xD6555500,
0xD7555500,
0xD8555500,
0xD9555500,
0xDA555500,	
0xDB555500,
0xDC555500,
0xDD555500,	
	
	
	
0xFF55FF00, //light magenta
0xFF55FF00, //light magenta
0xFF55FF00, //light magenta
0xFF55FF00, //light magenta
0xFF55FF00, //light magenta
0xFF55FF00, //light magenta
0xFF55FF00, //light magenta
0xFF55FF00, //light magenta
0xFF55FF00, //light magenta
0xFF55FF00, //light magenta
0xFF55FF00, //light magenta
0xFF55FF00, //light magenta
0xFF55FF00, //light magenta
0xFF55FF00, //light magenta
0xFF55FF00, //light magenta
0xFF55FF00, //light magenta


0xFFFF5500, //yellow
0xFFFF5500, //yellow
0xFFFF5500, //yellow
0xFFFF5500, //yellow
0xFFFF5500, //yellow
0xFFFF5500, //yellow
0xFFFF5500, //yellow
0xFFFF5500, //yellow
0xFFFF5500, //yellow
0xFFFF5500, //yellow
0xFFFF5500, //yellow
0xFFFF5500, //yellow
0xFFFF5500, //yellow
0xFFFF5500, //yellow
0xFFFF5500, //yellow
0xFFFF5500, //yellow



0xFFFFFF00, //white
0xFFFFFF00, //white
0xFFFFFF00, //white
0xFFFFFF00, //white
0xFFFFFF00, //white
0xFFFFFF00, //white
0xFFFFFF00, //white
0xFFFFFF00, //white
0xFFFFFF00, //white
0xFFFFFF00, //white
0xFFFFFF00, //white
0xFFFFFF00, //white
0xFFFFFF00, //white
0xFFFFFF00, //white
0xFFFFFF00, //white
0xFFFFFF00 //white

};



 
 
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
 
 

/*
 ********************************************************
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
					
					
	
						
 
						   
//
// End.
//


