/*
 * File: cursor.h
 *
 * Descrição:
 *     Suporte ao cursor para textos e inputs.    
 *
 * Obs: 
 * Essas variáveis de posicionamento de cursor tem sido muito úteis
 * nas rotinas de texto.
 *
 * @todo: colocar aqui informações sobre cursor.
 */


/* cursor */
#define CURSOR_DRAW     (1)
#define CURSOR_ERASE    (2)
#define CURSOR_MOVE     (3) 
//...

//
//Obs: Temos usado variáveis globais até agora, mas o ideal
//é usarmos a estrutura de cursor criada abaixo.
//

//Cursor. (disciplica de linhas).
unsigned long g_cursor_x;
unsigned long g_cursor_y;
unsigned long g_cursor_left;  //margem esquerda dada em linhas
unsigned long g_cursor_top;   //margem superior dada em linhas
unsigned long g_cursor_right;  //margem direita dada em linhas
unsigned long g_cursor_bottom;   //margem inferior dada em linhas

//*IMPORTANTE: Isso é ótimo, por permitira escolher uma posição dentro do terminal.


typedef enum {
	cursorTypeDefault,  //Arrow left.
	cursorTypeText,     // '|' 
	cursorTypeWait,     //Ampulheta.
	cursorTypeVerticalResize,
	cursorTypeHorizontalResize,
	cursorTypeDiagonalResize1,
	cursorTypeDiagonalResize2,
	cursorTypeUnavailable,
	cursorTypePrecision,
	cursorTypeXXXX,
    //...	
}cursor_type_t;

/*
 * Estrutura de suporte à cursor.
 */
typedef struct cursor_d cursor_t;
struct cursor_d
{
	//Object.
	object_type_t objectType;
	object_class_t objectClass;	
	
	//Posicionamento.
	unsigned long x;
	unsigned long y;
	
	//Imagem usada como cursor.
	void *imageBuffer;
	void *imagePathName;
	FILE cursorFile;

	//Tipo. 
	cursor_type_t cursorType;
	
	//...
};
cursor_t *Cursor;
cursor_t *CurrentCursor;
//...


//Cursor.
void set_up_cursor(unsigned long x, unsigned long y);
unsigned long get_cursor_x();
unsigned long get_cursor_y();

//
// End.
//


