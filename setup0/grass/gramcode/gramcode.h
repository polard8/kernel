

// gramcode.h


// rtl
#include <types.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <rtl/gramado.h> 


#include <api.h>


#include "sbar.h"


// # file support #
char *file_name;
char *file_buffer;
size_t file_size;


// ## System Metrics ##
int smScreenWidth;                   //1 
int smScreenHeight;                  //2
unsigned long smCursorWidth;         //3
unsigned long smCursorHeight;        //4
unsigned long smMousePointerWidth;   //5
unsigned long smMousePointerHeight;  //6
unsigned long smCharWidth;           //7
unsigned long smCharHeight;          //8
//...


// ## Window limits ##
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
//quantidade de linhas e colunas na área de cliente.
int wlMinColumns;
int wlMinRows;
int wlMaxColumns;
int wlMaxRows;
//  ## Window size ##
unsigned long wsWindowWidth;
unsigned long wsWindowHeight;
//...
//  ## Window position ##
unsigned long wpWindowLeft;
unsigned long wpWindowTop;
//..



//
// ## Text support ##
//

struct teditor_line
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
struct teditor_line LINES[32]; 

//precisamos colocar os caracteres aqui na hora de salvar o arquivo.
//80 chars * 32 lines.
char RAW_TEXT[80*32+1];



//#importante:
//Linhas visíveis.
//número da linha
//isso será atualizado na hora do scroll.
int textTopRow;  //Top nem sempre será '0'.
int textBottomRow;
//linha e coluna atuais
int textCurrentRow;
int textCurrentCol;
int textSavedRow;
int textSavedCol;
int textWheelDelta; //delta para rolagem do texto.
int textMinWheelDelta;  //mínimo que se pode rolar o texto
int textMaxWheelDelta;  //máximo que se pode rolar o texto
//...



//
// == prototypes =======================
//


int saveCreateButton (void);



