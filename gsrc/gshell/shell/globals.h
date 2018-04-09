/*
 * File: globals.h
 * 
 * Global variables.
 *
 * History:
 *     2018 - Created by Fred Nora.
 */

 
//
// Buffer support.
// 

char shell_buffer[SHELL_BUFFER_SIZE]; //buffer de output
unsigned long shell_buffer_pos; 
unsigned long shell_buffer_x; 
unsigned long shell_buffer_y; 
//unsigned long shell_buffer_width;  //Largura dada em número de caracteres.
//unsigned long shell_buffer_height; //Altura dada em número de caracteres.
//...
//Buffer size.
int shellBufferMaxColumns;  //80
int shellBufferMaxRows;     //25*4 (4 vistas) 


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
static unsigned long origin = (unsigned long) &shell_buffer[0];                         
//SCREEN_START+LINES*COLUMNS*2;
static unsigned long scr_end = (unsigned long) (&shell_buffer[0] + (LINES * COLUMNS));  

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

int shellWindowWidth;      //80*8
int shellWindowHeight;     //25*8

//...
unsigned long shell_window_x;
unsigned long shell_window_y;


//
// Colors
// 
 
//cores do texto. 
unsigned long backgroung_color;  //pano de fundo.
unsigned long foregroung_color;  //texto.


