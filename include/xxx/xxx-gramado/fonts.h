
// fonts.h 

// header do gerenciador de fonts usados pelo módulo /gramado

// @todo:
// fontes pode ser compartilhada com outros sistemas
// operacionais então deve ir para shared/fonts.h

// # fontes # 
//Endereços das fonts presentes no CMOS BIOS. 
#define BIOSFONT8X8 0x000FFA6E    //8x8
//#define BIOSFONT8X8 0x000FFA6E
//#define BIOSFONT8X8 0x000FFA6E
//#define BIOSFONT8X8 0x000FFA6E
//...


typedef enum {
	FONTNULL,
	FONT8X8,
	FONT8X16
    //...	
}font_type_t;


