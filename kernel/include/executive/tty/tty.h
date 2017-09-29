/*
 *   File: tty.h 
 *	 Header para o gerenciado de fluxo de caractere.
 */

 
 

#define DEVELOPER_TTYCHARS_MAX 25    //80
#define DEVELOPER_TTYLINES_MAX 40    //25 
//... 

//Contador de linhas usados na hora da criação de linhas.
int ttyLineCounter;

//Cursor.
int ttyCurrentX;
int ttyCurrentY;

typedef struct ttyline_d ttyline_t;
struct ttyline_d
{
	//@todo: Object type.
	
	int used;
	int magic;
	int empty;    //Se está vazia.
	
	char c[DEVELOPER_TTYCHARS_MAX];
	//
};
ttyline_t *input_line;
//...

ttyline_t *developer_ttylines[DEVELOPER_TTYLINES_MAX];
//ttyline_t *developer_ttylines[DEVELOPER_TTYLINES_MAX];
//ttyline_t *developer_ttylines[DEVELOPER_TTYLINES_MAX];
//ttyline_t *developer_ttylines[DEVELOPER_TTYLINES_MAX];
//... 
 

void *createTTYLine(); 
int ttyInit();


