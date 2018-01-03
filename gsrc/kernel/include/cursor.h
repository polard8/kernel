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
// ** Usar essas variáveis globais.
//    Os valores são retirados das estruturas dos objetos
// gráficos onde o cursor esta inserido e passadas para cá.
// Os manipuladores de cursor deve se atentar à essas globais.
// @todo: Essas globais serão substituidas pelos valores da 
// estrutura do cursor atual. 'CurrentCursor'.
// Cada objeto gráfico poderá ter uma estrutura de cursor associada à ele.
// #bugbug: estamos tendo problemas com o uso dessa estrutura. Cuidado.
// deixe pra depois, vai usado as globais.
//

//Cursor. (disciplica de linhas).
unsigned long g_cursor_x;
unsigned long g_cursor_y;
unsigned long g_cursor_color;
unsigned long g_cursor_left;     // margem esquerda dada em linhas
unsigned long g_cursor_top;      // margem superior dada em linhas
unsigned long g_cursor_right;    // margem direita dada em linhas
unsigned long g_cursor_bottom;   // margem inferior dada em linhas

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
 * Essa estrutura deve ser incluída na estrutura de janela.
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
	
    //unsigned long left;     // margem esquerda dada em linhas
    //unsigned long top;      // margem superior dada em linhas
    //unsigned long right;    // margem direita dada em linhas
    //unsigned long bottom;   // margem inferior dada em linhas
	
	//struct window_d *window;
	//struct rect_d *rect;
	
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
cursor_t *DeveloperWindowCursor; //test?? Cursor da janela do desenvolvedor.
//...


//Cursor.
void set_up_cursor(unsigned long x, unsigned long y);
unsigned long get_cursor_x();
unsigned long get_cursor_y();

//
// End.
//


