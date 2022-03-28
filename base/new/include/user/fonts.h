
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


typedef enum {
	FONTNULL,
	FONT8X8,
	FONT8X16
    // ...
}font_type_t;


//
// == prototypes ============================
//

int gwsGetCurrentFontCharWidth (void);
void gwsSetCurrentFontCharWidth (int width);

int gwsGetCurrentFontCharHeight (void);
void gwsSetCurrentFontCharHeight (int height);

// ====

unsigned long gwsGetCurrentFontAddress (void);
void gwsSetCurrentFontAddress ( unsigned long address );

int gwsInstallFont ( char *file_name );

#endif    



