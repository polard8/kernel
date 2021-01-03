
#ifndef __TERMINAL__
#define __TERMINAL__





//#todo: fazer estrutura para gerenciar a sequencia.
int __sequence_status = 0;

//
// CSI support
// 

//#test
//Control Sequence Introducer

#define CSI_BUFFER_SIZE 128
char CSI_BUFFER[ CSI_BUFFER_SIZE ];

int __csi_buffer_tail = 0;
int __csi_buffer_head = 0;


//
// Structures
//

//#importante
//vamos tentar copiar as estruturas usadas pelo terminal gramado/st

enum term_mode {
	MODE_WRAP	     = 1,
	MODE_INSERT      = 2,
	MODE_APPKEYPAD   = 4,
	MODE_ALTSCREEN   = 8,
	MODE_CRLF	     = 16,
	MODE_MOUSEBTN    = 32,
	MODE_MOUSEMOTION = 64,
	MODE_MOUSE       = 32|64,
	MODE_REVERSE     = 128,
	MODE_KBDLOCK     = 256,
	MODE_HIDE	     = 512,
	MODE_ECHO	     = 1024,
	MODE_APPCURSOR	 = 2048,
	MODE_MOUSESGR    = 4096,
};

enum escape_state {
	
	ESC_START = 1,
	ESC_CSI	= 2,
	ESC_STR	= 4,         /* DSC, OSC, PM, APC */
	ESC_ALTCHARSET = 8,
	ESC_STR_END = 16,    /* a final string was encountered */
	ESC_TEST = 32,       /* Enter in test mode */
	
};


// #importante
// Colocaremos aqui dentro elementos que apontem para
//variáveis que já usavamos antes de criarmos essa estrutura.
/* Internal representation of the screen */
typedef struct {
	
	//int row;	/* nb row */
	//int col;	/* nb col */
	//Line *line;	/* screen */
	//Line *alt;	/* alternate screen */
	//bool *dirty;	/* dirtyness of lines */
	//TCursor c;	/* cursor */
	//int top;	/* top    scroll limit */
	//int bot;	/* bottom scroll limit */
	int mode;	/* terminal mode flags */
	int esc;	/* escape state flags */
	//bool numlock;	/* lock numbers in keyboard */
	//bool *tabs;
} Term;

//Sem ponteiro.
static Term term;



#define ESC_BUF_SIZ 32 //(128*UTF_SIZ)
#define ESC_ARG_SIZ 16
#define STR_BUF_SIZ   ESC_BUF_SIZ
#define STR_ARG_SIZ ESC_ARG_SIZ



// 
// Escape sequence
//

/* CSI Escape sequence structs */
/* ESC '[' [[ [<priv>] <arg> [;]] <mode>] */
typedef struct {

    char buf[ESC_BUF_SIZ];    /* raw string */
    int len;                  /* raw string length */
    char priv;
    int arg[ESC_ARG_SIZ];
    int narg;                 /* nb of args */
    char mode;

} CSIEscape;

static CSIEscape csiescseq;





/* STR Escape sequence structs */
/* ESC type [[ [<priv>] <arg> [;]] <mode>] ESC '\' */
typedef struct {
	char type;	     /* ESC type ... */
	char buf[STR_BUF_SIZ]; /* raw string */
	int len;	       /* raw string length */
	char *args[STR_ARG_SIZ]; // ponteiro duplo.
	int narg;	      /* nb of args */
} STREscape;
static STREscape strescseq;



/*
 * credits: linux 0.1.
 * this is what the terminal answers to a ESC-Z or csi0c
 * query (= vt100 response).
 */
#define RESPONSE "\033[?1;2c"

#define VT102_ID "\033[?6c"







//==============================================================

// isso será usado em terminal.bin
// principalmente para gerenciamento de caracteres ... linhas 
// é o básico.

//todo: colocar as rotinas de terminal virtual aqui,
//separadas do shell

//
// SCREEN SUPPORT
//

#define DEFAULT_WINDOW_X 0
#define DEFAULT_WINDOW_Y 0



// Obs: 
// aumentar essas constantes aumenta o tamanho da janela.

// Isso é o máximo que se pode exibir na tela.
#define DEFAULT_MAX_COLUMNS 80   //80
#define DEFAULT_MAX_ROWS    25   //50  
  


//linux 
//#define SCREEN_START 0xb8000
//#define SCREEN_END   0xc0000
//#define LINES 25
//#define COLUMNS 80
//#define NPAR 16




//
// BUFFER SUPPORT
//

//
// Screen Buffer: 
// Igual a tela do vga, com caracteres e atributos.
// @todo: O buffer deve ser maior, com várias vistas para rolagem.
// mas apenas uma parte do buffer será mostrada na tela por vez.
//

// Isso é o buffer de arquivo. ele pode ser maior que
// a quantidade de linhas que a área de cliente pode mostrar.
#define DEFAULT_BUFFER_MAX_COLUMNS DEFAULT_MAX_COLUMNS  //80
#define DEFAULT_BUFFER_MAX_ROWS    32                   //25
#define SCREEN_BUFFER_SIZE ( ((DEFAULT_BUFFER_MAX_COLUMNS*DEFAULT_BUFFER_MAX_ROWS)*2)+1)


#define TAB_SIZE 8


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
 



//usado para test
unsigned long __tmp_x;
unsigned long __tmp_y;



// Colors
 
 
//cores do texto. 
unsigned long backgroung_color;  //pano de fundo.
unsigned long foregroung_color;  //texto.




//
// ## Text support #@#
//

struct terminal_line
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

// #importante
// É nesse buffer que estamos escrevendo. É como um arquivo.

// PROVISÓRIO
// O TEXTO TEM 32 LINHAS NO MÁXIMO.
// ESSA É A PARTE DO TEXTO QUE PODERÁ SER MANIPULADA,
// O RESTO DO TEXTO DEVERÁ FICAR ESPERANDO NO BUFFER.
// #IMPORTANTE: 25 DESSAS 32 LINHAS SERÃO VISÍVEIS.
// #importante: O início dessas estruturas pode representar o inpicio de 
// um arquivo.
// Esse arquivo pode ser um buffer
// Um arquivo no servidor de recursos gráficos pode ser usado para escrevermos 
// nele usando as rotinas da libc.

struct terminal_line LINES[32]; //DEFAULT_BUFFER_MAX_ROWS



//
// ==========

//
// Estrutura para mainpular linhas dentro do screen_buffer[]
//


#define MAGIC_NORMALLINE 1234
//...

#define LINE_SIZE_MAX 80

#define LINE_COUNT_MAX 2048


#define SCREENBUFFER_COUNT_MAX 8
//



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

//Conterá ponteiros para estruturas de linha.
unsigned long screenbufferList[8];


//
// ====
//


//marcador do cursor.
unsigned long screen_buffer_pos;    //(offset) 

unsigned long screen_buffer_x;      //current col 
unsigned long screen_buffer_y;      //current row

static unsigned long screen_buffer_saved_x = 0;
static unsigned long screen_buffer_saved_y = 0;


//
// =====
//



#define CalculateRowScanLine(WindowY,CharHeight) \
    ( WindowY * CharHeight )


#define CalculateColumnScanLine(WindowX,CharWidth) \
    ( WindowX * CharWidth )
	
//
// =====
//

// Comunicação Cliente/Servidor:
// Número da mensagem enviada pelo terminal virtual.
// São apenas mensagens usadas pelo terminal virtual 
// em modo texto, relativas a input e output de textos.

typedef enum terminal_api_message_number_d {
	
	terminalNull,          // 0
	terminalOpenTerminal,  // Inicia a estrutura de terminal virtual.
    terminalCloseTerminal, // Fecha a estrutura de terminal.
	terminalGetWindow,     //
    terminalGetMessage,    //
    terminalGetLong1,      //
    terminalGetLong2, 	   //
    terminalScreenWidth,
    terminalScreenHeight,
    terminalCursorWidth,
    terminalCursorHeight,
    terminalCharWidth,
    terminalCharHeight	
	
}terminal_api_message_number_t;





//
// Main struct
//

struct terminal_d
{
    int client_fd;
    
    int window_id;
 
    int pid;
    int uid;
    int gid;
    
    // ...
};
// The man structure.
struct terminal_d Terminal;



//
// ## System Metrics ##
//

int smScreenWidth;                   //1 
int smScreenHeight;                  //2
unsigned long smCursorWidth;         //3
unsigned long smCursorHeight;        //4
unsigned long smMousePointerWidth;   //5
unsigned long smMousePointerHeight;  //6
unsigned long smCharWidth;           //7
unsigned long smCharHeight;          //8
//...




//
//======
//

//
// ## Window limits ##
//

//full screen support
unsigned long wlFullScreenLeft;
unsigned long wlFullScreenTop;
unsigned long wlFullScreenWidth;
unsigned long wlFullScreenHeight;

//limite de tamanho da janela.
unsigned long wlMinWindowWidth;
unsigned long wlMinWindowHeight;
unsigned long wlMaxWindowWidth;
unsigned long wlMaxWindowHeight;



//
// Linhas
//

//quantidade de linhas e colunas na área de cliente.
int wlMinColumns;
int wlMinRows;

int __wlMaxColumns;
int __wlMaxRows;


//
//  ## Window size ##
//

unsigned long wsWindowWidth;
unsigned long wsWindowHeight;
//...


//
//  ## Window position ##
//

unsigned long wpWindowLeft;
unsigned long wpWindowTop;
//..



//=======================================
//               Cursor                //  
//=======================================

//linha e coluna atuais
int textCurrentRow;
int textCurrentCol;


//#importante:
//Linhas visíveis.
//número da linha
//isso será atualizado na hora do scroll.
int textTopRow;  //Top nem sempre será '0'.
int textBottomRow;


int textSavedRow;
int textSavedCol;

int textWheelDelta;     //delta para rolagem do texto.
int textMinWheelDelta;  //mínimo que se pode rolar o texto
int textMaxWheelDelta;  //máximo que se pode rolar o texto
//...


//
// ===
//


    //
    // Bg window.
    // 
 
     unsigned long __bgleft;
     unsigned long __bgtop;
     unsigned long __bgwidth;
     unsigned long __bgheight;
 
     unsigned long __barleft;
     unsigned long __bartop;
     unsigned long __barwidth;
     unsigned long __barheight;



//
// prototypes.
//

void terminal_write_char (int fd, int window, int c);

void terminalInsertNextChar (char c);
void terminalInsertNullTerminator (void);
void terminalInsertCR (void);
void terminalInsertLF (void);

void lf (void);
void cr (void);
void ri (void);
void del (void);

//#test
//void tputc (int fd,char *c, int len);
void tputc (int fd, int window, int c, int len);



char 
terminalGetCharXY ( 
    unsigned long x, 
    unsigned long y );
                    
                    
void 
terminalInsertCharXY ( 
    unsigned long x, 
    unsigned long y, 
    char c );
                   

static void save_cur (void);
static void restore_cur (void);
void terminalClearBuffer (void);


void textSetTopRow ( int number );
int textGetTopRow (void);
void textSetBottomRow ( int number );
int textGetBottomRow (void);    
void textSetCurrentRow ( int number );          
int textGetCurrentRow (void);           
void textSetCurrentCol ( int number );           
int textGetCurrentCol (void);

void move_to ( unsigned long x, unsigned long y );


int pad_to (int count, char *string);
                   
#endif   



