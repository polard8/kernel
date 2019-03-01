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


 

 
/*
//estrutura para tty
//uma estrutura de tty deve estar associado a
//uma janela de terminal virual.
struct tty_struct_d
{
    //in support
	unsigned long IN[320];
    int head; //coloca.
	int tail; //pega.
	
	//out support	
	unsigned long OUT[320];
	
	//continua ...
	
	//#obs: olhar o do minix
	
	//Id da janela do terminal virtual associado
	//ao tty
    int windowID;	
	
}TTYLIST[8];
*/


//void *createTTYLine(); 
int ttyInit();


