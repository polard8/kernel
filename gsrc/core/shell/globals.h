/*
 * File: globals.h
 * 
 * Global variables.
 *
 * History:
 *     2018 - Created by Fred Nora.
 */
 
 


/*
#define BLACK       0
#define RED         1
#define GREEN       2
#define BROWN       3
#define BLUE        4
#define MAGENTA     5
#define CYAN        6
#define LIGHTGRAY   7
#define DARKGRAY    8
#define LIGHTRED    9
#define LIGHTGREEN  10
#define YELLOW      11
#define LIGHTBLUE   12
#define PINK        13
#define LIGHTCYAN   14
#define WHITE       15 
*/ 
 
 
 
//#ifndef whitespace
//#define whitespace(c) (((c) == ' ') || ((c) == '\t'))
//#endif 


//#ifndef digit
//#define digit(c)  ((c) >= '0' && (c) <= '9')
//#endif

//#ifndef isletter
//#define isletter(c) (((c) >= 'A' && (c) <= 'Z') || ((c) >= 'a' && (c) <= 'z'))
//#endif

//#ifndef digit_value
//#define digit_value(c) ((c) - '0')
//#endif
 
 
//#define NEWLINE '\n' 
//#define TAB '\t'
//#define SPACE 0x020
 
//
// Buffer support.
// 


//
//  ** SCREEN BUFFER ***
//

//Uma tela igual a vga, com caracteres e atributos.

char screen_buffer[SCREEN_BUFFER_SIZE]; 
unsigned long screen_buffer_pos; 
unsigned long screen_buffer_x; 
unsigned long screen_buffer_y; 
//unsigned long shell_buffer_width;  //Largura dada em número de caracteres.
//unsigned long shell_buffer_height; //Altura dada em número de caracteres.
//...
//Buffer size.
int shellScreenBufferMaxColumns;  //80
int shellScreenBufferMaxRows;     //25



//
// Estrutura para mainpular linhas dentro do screen_buffer[]
//


#define MAGIC_NORMALLINE 1234
//...

#define LINE_SIZE_MAX 80

typedef struct line_d line_t;
struct line_d
{
	int id;     //identificação da linha.
	
	int used;
	int magic;  //Validade e característica da estrutura.
	
	int Start;
	int End;
	
	//Deslocamentos em relação ao Start.
	int LeftOffset;    //Onde começa o texto dentro da linha.   
	int RightOffset;   //Onde termina o texto dentro da linha.
	
	// Continua
	// ...
	
	int SizeInChars;  // Quantos chars tem na linha.
	int SizeInBytes;  // Quantos bytes tem na linha. (char + atrr)	
	
    struct line_d *next;	
};

#define LINE_COUNT_MAX 2048

//Conterá ponteiros para estruturas de linha.
unsigned long lineList[LINE_COUNT_MAX];


//
// Estrutura de suporte ao screen buffer.
//

typedef struct screen_buffer_d screen_buffer_t;
struct screen_buffer_d
{
	int id;
	
	int used;
	int magic;
	
	char *name;
	char *description;
	
		
    //
    // Current line support.
    //
	
	int current_line_id;              //id.
	struct line_d *current_line;   //struct 
	//...
	
    //
    // lines.
    //	
	
	struct line_d *first_line;
	struct line_d *last_line;
	//...
	
	
	//Continua ...
	
	//Número total de linhas no buffer.
	int total_lines;
	
	struct screen_buffer_d *next;
};


#define SCREENBUFFER_COUNT_MAX 8

//Conterá ponteiros para estruturas de linha.
unsigned long screenbufferList[8];

//
// Metrics.
//


//Screen size.
int shellMaxColumns;       //80   
int shellMaxRows;          //25
int shellScreenWidth;      //800 
int shellScreenHeight;     //600


//linux style.

//Screen start and screen end.

//SCREEN_START;
static unsigned long origin = (unsigned long) &screen_buffer[0];                         
//SCREEN_START+LINES*COLUMNS*2;
static unsigned long scr_end = (unsigned long) (&screen_buffer[0] + (LINES * COLUMNS));  

static unsigned long pos;    //posição dentro do buffer
static unsigned long x, y;
static unsigned long top = 0, bottom = LINES;
static unsigned long lines = LINES,columns = COLUMNS;
static unsigned long state = 0;
static unsigned long npar, par[NPAR];
static unsigned long ques = 0;
static unsigned char attr = 0x07;
static unsigned long saved_x = 0;
static unsigned long saved_y = 0;
//...


//
// WINDOW SUPPORT
//



//...
unsigned long shell_window_x;
unsigned long shell_window_y;
int shellWindowWidth;      //80*8
int shellWindowHeight;     //25*8

//
// Colors
// 
 
//cores do texto. 
unsigned long backgroung_color;  //pano de fundo.
unsigned long foregroung_color;  //texto.


