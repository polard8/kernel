
// fonts.h
// Fonts support.
// ring 0.

#ifndef  __FONTS_H
#define  __FONTS_H    1

// Fontes: 
// Endereços das fonts presentes no CMOS BIOS. 
// Esse enderço esta abaixo de 2MB, então
// temos identidade 1:1

#define BIOSFONT8X8  0x00000000000FFA6E    //8x8
//#define BIOSFONT8X8 0x000FFA6E
//#define BIOSFONT8X8 0x000FFA6E
//#define BIOSFONT8X8 0x000FFA6E
//...

// # char support # 
#define CHAR_WIDTH   8
#define CHAR_HEIGHT  8 
#define DEFAULT_CHAR_WIDTH   8
#define DEFAULT_CHAR_HEIGHT  8
//...


// see: font.c
extern unsigned long gws_currentfont_address;
extern unsigned long g8x8fontAddress;          // 8×8, 80×25,CGA, EGA
extern unsigned long g8x14fontAddress;         // 8x14,80×25,EGA
extern unsigned long g8x16fontAddress;         // ??
extern unsigned long g9x14fontAddress;         // 9x14,80×25,MDA, Hercules
extern unsigned long g9x16fontAddress;         // 9x16,80×25,VGA
//...

extern int gfontSize;

typedef enum {
    FONTNULL,
    FONT8X8,
    FONT8X16
    // ...
}font_type_t;

//
// == prototypes ============================
//

int gwsInitializeDefaultKernelFont(void);
int gwsGetCurrentFontCharWidth (void);
void gwsSetCurrentFontCharWidth (int width);
int gwsGetCurrentFontCharHeight (void);
void gwsSetCurrentFontCharHeight (int height);

unsigned long fontGetCurrentAddress(void);
void fontSetCurrentAddress(unsigned long address);

int gwsInstallFont ( char *file_name );

#endif    



