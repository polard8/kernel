
//#importante:
//Essas coisas não pertencem ao sheel e irão 
//para os lugarem que darão suporte ao terminal;(console)


//
// ## Text support #@#
//


//#importante. 
//rect info
//retângulo da área de cliente onde aparecerão os caracteres.
typedef struct terminal_rect_info_d terminal_rect_info_t; 
struct terminal_rect_info_d
{
	unsigned long top;
	unsigned long left;
	unsigned long width;
	unsigned long height;
	//...
};
struct terminal_rect_info_d terminal_rect; 


struct shell_line
{
    char CHARS[80];
    char ATTRIBUTES[80];	
	
	//início e fim da string dentro da linha.
	//o resto é espaço.
	int left;
	int right;
	
	//posição do cursor dentro da linha.
	int pos;
};

//PROVISÓRIO
//O TEXTO TEM 32 LINHAS NO MÁXIMO.
//ESSA É A PARTE DO TEXTO QUE PODERÁ SER MANIPULADA,
//O RESTO DO TEXTO DEVERÁ FICAR ESPERANDO NO BUFFER.
//#IMPORTANTE: 25 DESSAS 32 LINHAS SERÃO VISÍVEIS.
struct shell_line LINES[32]; 


//linha e coluna atuais
int textCurrentRow;
int textCurrentCol;
//#importante:
//Linhas visíveis.
//número da linha
//isso será atualizado na hora do scroll.
int textTopRow;  //Top nem sempre será '0'.
int textBottomRow;

int wlMaxColumns;
int wlMaxRows;

int textSavedRow;
int textSavedCol;

//delta para rolagem do texto.
int textWheelDelta; 
int textMinWheelDelta;  //mínimo que se pode rolar o texto
int textMaxWheelDelta;  //máximo que se pode rolar o texto
//...

//
// ## prototypes ##
//

void shellInsertNextChar(char c);

//refresh do char que está na posição usada pelo input.
void shellRefreshCurrentChar(); 

//scroll dentro da screen_buffer. (VGA emulada)
void shellScroll();

void testChangeVisibleArea();
void updateVisibleArea( int direction );
void shellRefreshVisibleArea();
void shellSetCursor(unsigned long x, unsigned long y);

void move_to( unsigned long x, unsigned long y);
void testShowLines();

void shellClearBuffer();

void shellShowScreenBuffer();

//copia o conteúdo do buffer para a tela. (dentro da janela)
void shellRefreshScreen(); 

void shellRefreshLine ( int line_number );

void shellRefreshChar ( int line_number, int col_number );

static void del(void);
static void cr(void);
static void ri(void);
static void lf(void);

static void save_cur(void);
static void restore_cur(void);

void shellInsertCharXY(unsigned long x, unsigned long y, char c);

char 
shellGetCharXY ( unsigned long x, 
                 unsigned long y );
				 
void shellInsertCR();
void shellInsertLF();
void shellInsertNullTerminator();


// testes de scroll.
void testScrollChar();

void clearLine ( int line_number );

//row support
void textSetTopRow ( int number );
void textSetBottomRow ( int number );
int textGetTopRow ();
int textGetBottomRow ();


