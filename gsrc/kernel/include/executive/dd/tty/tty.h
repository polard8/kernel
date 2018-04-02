/*
 * File: tty.h 
 * Header para o gerenciado de fluxo de caractere.
 */

 
#define TTYCHARS_COUNT_MAX 25    //80 
#define TTYLINES_COUNT_MAX 25    //25 

//#define DEVELOPER_TTYCHARS_MAX 25    //80
//#define DEVELOPER_TTYLINES_MAX 25    //25 
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
	
	//fazendo uma lista dos caracteres que ficarão dentro da linha.
	char c[TTYCHARS_COUNT_MAX];
	//
	
	
	//A estrutura de texto que é dona dessa linha.
	struct ttytext_d *owner_text;
	
	//Proxima linhas.
	struct ttyline_d *next;
};
ttyline_t *input_line;
//...

//ttyline_t *developer_ttylines[TTYLINES_COUNT_MAX];
//ttyline_t *developer_ttylines[DEVELOPER_TTYLINES_MAX];
//ttyline_t *developer_ttylines[DEVELOPER_TTYLINES_MAX];
//ttyline_t *developer_ttylines[DEVELOPER_TTYLINES_MAX];
//... 

typedef struct ttytext_d ttytext_t;
struct ttytext_d
{
	//@todo: Object type.
	
	int used;
	int magic;
	int empty;    //Se está vazia.
	
	//fazendo uma lista de ponteiros para estruturas de linhas.
	unsigned long l[TTYLINES_COUNT_MAX];
	//	
	
	//próximo texto.
	struct ttytext_d *next;
};
 
 
 

void *createTTYLine(); 
int ttyInit();


